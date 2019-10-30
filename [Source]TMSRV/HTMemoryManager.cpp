
//#include <string.h>           // It is important to note here the order in which the files are
//#include <stdarg.h>           // included to avoid syntax and linking errors.  First you should
//#include <stdio.h>            // include all of the required standard header files followed by
//#include <time.h>             // the MemoryManager.h header.  All other custom file should be
//#include <assert.h>           // included after the MemoryManager.h header. 
#include "StdAfx.h"
#include "HTMemoryManager.h"

#ifdef HT_ACTIVATE_MEMORY_MANAGER

#include "HTNew_Off.h"

HTvoid HTMemoryNode::HT_vInitializeMemory( HTlong lBody ) 
{
	// HK : 메모리 바이올레이션을 감지하기 위해 메모리 영역의 앞뒤에 padding영역을 붙인다.
	HTlong* plBeginning = (HTlong*)m_pvActualAddress;
	HTlong* plEnding = (HTlong*)((HTchar*)m_pvActualAddress + m_ActualSize - m_usPaddingSize * sizeof(HTlong));
	
	for ( HTushort us = 0; us < m_usPaddingSize; ++us )
	{
		plBeginning[us] = plEnding[us] = HT_PADDING;
	}

	// HK : 메모리 영역을 초기화 한다. 혹시 사용되지 않는 영역인 경우를 알아보기 위해
	plBeginning = (HTlong*)m_pvReportedAddress;
	HTuint nLength = m_ReportedSize / sizeof(HTlong);
	
	HTuint i;
	
	for ( i = 0; i < nLength; ++i )
	{
		plBeginning[i] = lBody;
	}
	
	HTchar* szString = (HTchar*)(&plBeginning[i]);
	nLength = m_ReportedSize - nLength * sizeof(HTlong);
	
	for ( i = 0; i < nLength; ++i )	// HK : HTlong형으로 초기화 되지 않은 메모리 영역을 HTchar형으로 초기화 한다.
	{
		szString[i] = (HTchar)lBody;
	}

	m_lPredefinedBody = lBody;
}

//////////////
//////////////
//////////////
//////////////
//////////////
//////////////

CHTMemoryManagerInitialize::CHTMemoryManagerInitialize()
{
	CHTMemoryManagerGlobal::HT_bInitializeMemoryManager();
}

//////////////
//////////////
//////////////
//////////////
//////////////
//////////////

CHTMemoryManager::CHTMemoryManager()
{
}

CHTMemoryManager::~CHTMemoryManager()
{
}

HTvoid CHTMemoryManager::HT_vInitialize()	// HK : 이것저것 CHTMemoryManager에서 사용되는 메모리를 초기화한다.
{
	m_iBreakOnAllocationCount	= -1;
	m_nPaddingSize				= 4;
	m_bLogAlways				= HT_TRUE;
	m_bCleanLogFileOnFirstRun	= HT_TRUE;

	m_nTotalMemoryAllocated = m_nTotalMemoryUsed = m_iTotalMemoryAllocations  = 0;
	m_nPeakMemoryAllocation = m_nNumHashEntryAllocations = m_nPeakTotalNumAllocations = 0;
	m_nOverheadMemoryCost = m_nTotalOverHeadMemoryCost = m_nPeakOverHeadMemoryCost = 0;
	m_nAllocatedMemory = m_nNumBoundsViolations = 0;

	for ( HTint n = 0; n < HT_HASH_SIZE; ++n )
	{
		m_ppHashTable[n] = HT_NULL;
	}

	m_TopStack.HT_vInit();
	m_pMemoryCache = HT_NULL;
}

HTvoid CHTMemoryManager::HT_vRelease()	// HK : CHTMemoryManager를 release한다. log파일을 dump하고, 사용된 메모리를 돌리놓는다.
{	
	HT_vDumpLogReport();	// HK : 수집된 메모리 관련 정보를 로그파일에 덤프한다.

	// HK : 메모리 누수가 있는 경우 CHTMemoryManager에 의해 메모리 누수를 제거한다.
	if ( m_nNumHashEntryAllocations != 0 )
	{
		for ( HTint n = 0; n < HT_HASH_SIZE; ++n )
		{
			while ( m_ppHashTable[n] )
			{
				HTMemoryNode* pMemoryNode = m_ppHashTable[n];
				m_ppHashTable[n] = m_ppHashTable[n]->m_pNext;
				if ( m_ppHashTable[n] != HT_NULL )
				{
					free( pMemoryNode->m_pvActualAddress );		// HK : 아직 제거 되지 않은 메모리를 제거해준다
					free( pMemoryNode );						// HK : 메모리 노드 자체도 제거해 준다.
				}
			}
		}
	}

	// HK : 스택에 남아있는 메모리도 역시 제거해 준다.
	while ( !m_TopStack.HT_bEmpty() )
	{
		free( m_TopStack.HT_pGetHead() );
		m_TopStack.HT_pPop();
	}

	// HK : 메모리 캐쉬 역시 제거해 준다.
	HTMemoryNode* pMemoryNode;
	while ( m_pMemoryCache )
	{
		pMemoryNode = m_pMemoryCache;
		m_pMemoryCache = pMemoryNode->m_pNext;
		if ( m_pMemoryCache != HT_NULL ) free( pMemoryNode );
	}
}

HTvoid CHTMemoryManager::HT_vInsertMemoryNode( HTMemoryNode* pMemoryNode )	// HK : 메모리 노드는 해쉬 테이블에 관리되는데 이 해쉬 테이블에 메모리를 삽입하는 역할을 하는 함수
{
	HTint iHashIndex = HT_iGetHashIndex( pMemoryNode->m_pvReportedAddress );
	pMemoryNode->m_pNext = m_ppHashTable[iHashIndex];
	pMemoryNode->m_pPrev = HT_NULL;

	if ( m_ppHashTable[iHashIndex] ) m_ppHashTable[iHashIndex]->m_pPrev = pMemoryNode;

	m_ppHashTable[iHashIndex] = pMemoryNode;
	
	// HK : 메모리를 삽입하는 김에 몇몇 정보도 기록한다.
	m_nNumHashEntryAllocations++;

	m_nAllocatedMemory += pMemoryNode->m_ReportedSize;

	if ( m_nAllocatedMemory > m_nPeakMemoryAllocation )
					m_nPeakMemoryAllocation = m_nAllocatedMemory;
	if ( m_nNumHashEntryAllocations > m_nPeakTotalNumAllocations )
					m_nPeakTotalNumAllocations = m_nNumHashEntryAllocations;

	m_nTotalMemoryAllocated += pMemoryNode->m_ReportedSize;
	m_iTotalMemoryAllocations++;
}

HTMemoryNode* CHTMemoryManager::HT_pGetMemoryNode( HTvoid* pvAddress )	// HK : 메모리 노드를 해쉬테이블로부터 찾아서 그 메모리의 포인터를 리턴하는 함수. 해당 메모리 노드가 존재하지 않는 경우 HT_NULL을 리턴한다.
{
	HTMemoryNode *pMemoryNode = m_ppHashTable[HT_iGetHashIndex( pvAddress )];
	
	while ( pMemoryNode && pMemoryNode->m_pvReportedAddress != pvAddress )
	{
		pMemoryNode = pMemoryNode->m_pNext;
	}
	
	return pMemoryNode;
}

HTMemoryNode* CHTMemoryManager::HT_pRemoveMemoryNode( HTvoid* pvAddress )	// HK : HT_pGetMemoryNode와 같은 역할을 하는 함수. 단 이 함수는 해쉬 테이블로 부터 해당 노드를 삭제하는 역할까지 한다.
{
	HTint iHashIndex = HT_iGetHashIndex( pvAddress );
	
	if ( iHashIndex == 17 ) HTint ttt = 0;	//?
	
	HTMemoryNode* pMemoryNode = m_ppHashTable[iHashIndex];
	
	while ( pMemoryNode && pMemoryNode->m_pvReportedAddress != pvAddress)
	{
		pMemoryNode = pMemoryNode->m_pNext;
	}

	if ( pMemoryNode )
	{
		if ( pMemoryNode->m_pNext ) pMemoryNode->m_pNext->m_pPrev = pMemoryNode->m_pPrev;
		if ( pMemoryNode->m_pPrev ) pMemoryNode->m_pPrev->m_pNext = pMemoryNode->m_pNext;
		else						m_ppHashTable[iHashIndex] = pMemoryNode->m_pNext;

		// HK : 정보 정리
		m_nNumHashEntryAllocations--;
		m_nAllocatedMemory -= pMemoryNode->m_ReportedSize;
	}
	return pMemoryNode;

}

HTbool CHTMemoryManager::HT_bValidateMemoryUnit( HTMemoryNode* pMemoryNode )	// HK : 해당 메모리에 Bound Violation이 발생하였는지 아닌지를 확인하고
{																				// HK : 실제 사용되는 메모리 영역이 얼마였는지를 계산하는 역할을 한다. 
	HTbool bSuccess = HT_TRUE;													// HK : 이 함수는 메모리 노드가 삭제되기 전에 불러줘야 한다.
																				// HK : HT_TRUE를 반환하는 경우 Bound Violation이 발생한 경우, 그렇지 않은 경우 HT_FALSE를 반환한다.
	HTuint nTotalBytesUsed = 0;
	HTuint nBoundViolations = 0;

	// HK : Bound Violation이 발생하였는지를 체크하는 부분.
	HTlong* plBeginning = (HTlong*)pMemoryNode->m_pvActualAddress;
	HTlong* plEnding = (HTlong*)((HTchar*)pMemoryNode->m_pvActualAddress + pMemoryNode->m_ActualSize - pMemoryNode->m_usPaddingSize * sizeof(HTlong) );
	HTuint n;
	for ( n = 0; n < pMemoryNode->m_usPaddingSize; ++n )
	{
		if ( plBeginning[n] != HT_PADDING || plEnding[n] != HT_PADDING)
		{
			bSuccess = HT_FALSE;  // HK : 이 if문 내에 들어온 경우는 Bound Violation이 발생한 경우이다.
			nBoundViolations++;
		}
	}

	if ( !bSuccess ) m_nNumBoundsViolations++;

	// HK : 할당된 메모리 영역에서 실제로 얼마나 사용되었는지를 체크하는 부분이다.
	HTlong* plReportedAddress = (HTlong*)pMemoryNode->m_pvReportedAddress;
	HTuint iLength = pMemoryNode->m_ReportedSize / sizeof(HTlong);
	HTuint nn;
	for ( nn = 0; nn < iLength; ++nn )
	{
		if ( plReportedAddress[nn] != pMemoryNode->m_lPredefinedBody ) nTotalBytesUsed += sizeof(HTlong);
	}
	HTchar* szString = (HTchar*)(&plReportedAddress[nn]);
	iLength = pMemoryNode->m_ReportedSize - iLength * sizeof(HTlong);
	for ( nn = 0; nn < iLength; ++nn )
	{
		if ( szString[nn] != (HTchar)pMemoryNode->m_lPredefinedBody ) nTotalBytesUsed++;
	}

	m_nTotalMemoryUsed += nTotalBytesUsed;

	// HK : 메모리 사용량을 %로 계신해 보고 하는 부분
	if ( m_bLogAlways && (nTotalBytesUsed != pMemoryNode->m_ReportedSize) )
	{
		HT_vLogError(
			"Unused Memory Detected   : %-40s %8s(0x%08p) : %s",
			CHTMemoryManagerGlobal::HT_szFormatOwnerString( pMemoryNode->m_szSourceFile, pMemoryNode->m_usSourceLine ),
			HT_ALLOCATION_TYPE[pMemoryNode->m_AllocationType],
			pMemoryNode->m_pvReportedAddress,
			CHTMemoryManagerGlobal::HT_szMemorySizeString( pMemoryNode->m_ReportedSize - nTotalBytesUsed ) );
	}

	// HK : Bounds Violation을 체크해 보고 하는 부분
	if ( m_bLogAlways && !bSuccess )
	{
		HT_vLogError(
			"Bounds Violation Detected: %-40s %8s(0x%08p)",
			CHTMemoryManagerGlobal::HT_szFormatOwnerString( pMemoryNode->m_szSourceFile, pMemoryNode->m_usSourceLine ),
			HT_ALLOCATION_TYPE[pMemoryNode->m_AllocationType],
			pMemoryNode->m_ReportedSize );
	}

	return bSuccess;
}

HTvoid CHTMemoryManager::HT_vDeAllocateMemory( HTMemoryNode* pMemoryNode )	// HK : 다음번의 사용을 위해 메모리 노드를 캐쉬하는 부분
{
	m_nOverheadMemoryCost -= (pMemoryNode->m_usPaddingSize * 2 * sizeof(HTlong) );
	pMemoryNode->m_pNext = m_pMemoryCache;
	m_pMemoryCache = pMemoryNode;
//	m_pMemoryCache->m_pNext = HT_NULL;
}

HTMemoryNode* CHTMemoryManager::HT_pAllocateMemory()	// HK : 메모리 캐쉬가 존재하면 그놈을  캐쉬에서 빼내어서 리턴하고,
{														// HK : 메모리 캐쉬가 존재하지 않으면 새로운 메모리 노드를 만들어 리턴한다.
	if (!m_pMemoryCache)	// HK : 메모리 캐쉬가 존재하지 않는 경우
	{
		HTint iOverHead = m_nPaddingSize * 2 * sizeof(HTlong) + sizeof(HTMemoryNode);
		m_nOverheadMemoryCost += iOverHead;
		m_nTotalOverHeadMemoryCost += iOverHead;

		if ( m_nOverheadMemoryCost > m_nPeakOverHeadMemoryCost )
		{
			m_nPeakOverHeadMemoryCost =  m_nOverheadMemoryCost;
		}

		return (HTMemoryNode*)malloc( sizeof(HTMemoryNode) );
	}
	else
	{
		HTint iOverHead = m_nPaddingSize * 2 * sizeof(HTlong);
		m_nOverheadMemoryCost += iOverHead;
		m_nTotalOverHeadMemoryCost += iOverHead;

		if ( m_nOverheadMemoryCost > m_nPeakOverHeadMemoryCost )
		{
			m_nPeakOverHeadMemoryCost =  m_nOverheadMemoryCost;
		}

		HTMemoryNode* pMemoryNode = m_pMemoryCache;
		m_pMemoryCache = m_pMemoryCache->m_pNext;
		
		return pMemoryNode;
	}
}

HTvoid CHTMemoryManager::HT_vDumpLogReport()	// HK : 메모리 관련 여러 통계 내용을 log 파일에 적어서 보고하는 부분.
{
	if ( m_bCleanLogFileOnFirstRun )
	{
		unlink( g_szLogFileName );
		m_bCleanLogFileOnFirstRun = HT_FALSE;
	}

	FILE* pFile;
	if ( !(pFile = fopen( g_szLogFileName, "ab" )) ) return;

	time_t	t		= time( HT_NULL );
	tm*		time	= localtime( &t );
	
	HTint iMemoryLeak = HT_iCalculateUnAllocatedMemory();
	HTint iTotalMemoryDivider = m_nTotalMemoryAllocated != 0 ? m_nTotalMemoryAllocated : 1;

	// HK : Header Information
	fprintf( pFile, "\r\n" );
	fprintf( pFile, "******************************************************************************* \r\n");
	fprintf( pFile, "*********           Memory report for: %04d/%02d/%02d %02d:%02d:%02d            ********* \r\n", time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,  time->tm_hour, time->tm_min, time->tm_sec );
	fprintf( pFile, "******************************************************************************* \r\n");
	fprintf( pFile, "\r\n" );

	// HK : Report summary
	fprintf( pFile, "                            총   메 모 리  사 용 량                              \r\n" );
	fprintf( pFile, "-------------------------------------------------------------------------------- \r\n" );
	fprintf( pFile, "                   실행 중 동적으로 메모리 생성 횟수: %10s 번\r\n", CHTMemoryManagerGlobal::HT_szInsertCommas( m_iTotalMemoryAllocations ) );
	fprintf( pFile, "                        프로그램에서 사용된 메모리량: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalMemoryAllocated ) );
	fprintf( pFile, "     (디버그 모드에서) 프그램이 실제 사용한 메모리량: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalOverHeadMemoryCost + m_nTotalMemoryAllocated ) );
	fprintf( pFile, "      메모리 사용량 체크 및 트랙킹에 사용된 메모리량: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalOverHeadMemoryCost ) );
	fprintf( pFile, "\r\n");
	fprintf( pFile, "\r\n");

	fprintf( pFile, "                           최 대  메 모 리  사 용 량                             \r\n");
	fprintf( pFile, "-------------------------------------------------------------------------------- \r\n");
	fprintf( pFile, "                        메모리 동적 생성의 최대 횟수: %10s 번\r\n", CHTMemoryManagerGlobal::HT_szInsertCommas( m_nPeakTotalNumAllocations ) );
	fprintf( pFile, "                       프로그램의 최대 메모리 사용량: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nPeakMemoryAllocation ) );
	fprintf( pFile, "(디버그 모드에서) 프그램이 실제 사용한 최대 메모리량: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nPeakOverHeadMemoryCost + m_nPeakMemoryAllocation ) );
	fprintf( pFile, " 메모리 사용량 체크 및 트랙킹에 사용된 최대 메모리량: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nPeakOverHeadMemoryCost ) );
	fprintf( pFile, "\r\n");
	fprintf( pFile, "\r\n");

	fprintf( pFile, "              할 당 은  되 었 으 나  사 용 되 지  않 은  메 모 리                \r\n");
	fprintf( pFile, "-------------------------------------------------------------------------------- \r\n");
	fprintf( pFile, "       동적 할당된 메모리 공간 중 실제로 사용된 비율: %10.2f %%\r\n", (HTfloat)(1 - (m_nTotalMemoryAllocated - m_nTotalMemoryUsed) / (HTfloat)iTotalMemoryDivider) * 100 );
	fprintf( pFile, "            동적 할당된 메모리 중 사용되지 않은 비율: %10.2f %%\r\n", (HTfloat)(m_nTotalMemoryAllocated - m_nTotalMemoryUsed) / (HTfloat)iTotalMemoryDivider * 100 );
	fprintf( pFile, "    동적 할당은 되었으나 실제 사용되지 않은 메모리량: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalMemoryAllocated - m_nTotalMemoryUsed ) );
	fprintf( pFile, "\r\n");
	fprintf( pFile, "\r\n");

	fprintf( pFile, "           할 당  영 역 을  넘 어  사 용 된  횟 수 (Bounds Violation)            \r\n");
	fprintf( pFile, "-------------------------------------------------------------------------------- \r\n");
	fprintf( pFile, "                        할당 영역을 넘어 사용된 횟수: %10s 번\r\n", CHTMemoryManagerGlobal::HT_szInsertCommas( m_nNumBoundsViolations ) );
	fprintf( pFile, "\r\n");
	fprintf( pFile, "\r\n");

	fprintf( pFile, "                              메 모 리  누 수                                     \r\n");
	fprintf( pFile, "-------------------------------------------------------------------------------- \r\n");
	fprintf( pFile, "                               메모리 누수 발생 횟수: %10s 번\r\n", CHTMemoryManagerGlobal::HT_szInsertCommas( m_nNumHashEntryAllocations ) );
	fprintf( pFile, "      동적으로 할당되었으나 해제시키지 않은 메모리량: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( iMemoryLeak ) );
	fprintf( pFile, "    동적 할당된 메모리와 해제시킨 메모리의 상호 비율: %10.2f %%\r\n", (HTfloat)(1 - (m_nTotalMemoryAllocated - iMemoryLeak) / (HTfloat)iTotalMemoryDivider) * 100 );
	fprintf( pFile, "( new[]로 할당 받고 delete로 해제한 경우에는 메모리 누수로 판단되지 않음에 유의 )\r\n");
	fprintf( pFile, "\r\n");
	fprintf( pFile, "\r\n");

	OutputDebugString(	"\n-----------------------------------------------------------------\n");
	OutputDebugString(	"                   메 모 리  사 용  정 보\n");
	OutputDebugString(	"-----------------------------------------------------------------\n");
	HTchar szS0[1024];
	sprintf( szS0,		"* 프로그램이 실제 사용한 메모리량 :           %s\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalMemoryAllocated ) );
	OutputDebugString( szS0 );

	HTchar szS1[1024];
	sprintf( szS1,		"* 프로그램의 최대 메모리 사용량 :             %s\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nPeakMemoryAllocation ) );	
	OutputDebugString( szS1 );

	HTchar szS2[1024];
	sprintf( szS2,		"* 할당은 되었으나 사용되지 않은 메모리량 :    %s\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalMemoryAllocated - m_nTotalMemoryUsed ) );	
	OutputDebugString( szS2 );
	
	HTchar szS3[1024];
	sprintf( szS3,		"* Bounds Violation이 발생환 횟수 :                     %s 번\n", CHTMemoryManagerGlobal::HT_szInsertCommas( m_nNumBoundsViolations ) );	
	OutputDebugString( szS3 );

	HTchar szS4[1024];
	sprintf( szS4,		"* 할당된 메모리와 해제된 메모리 상호 비율 :   %10.2f %%\n", (HTfloat)(1 - (m_nTotalMemoryAllocated - iMemoryLeak) / (HTfloat)iTotalMemoryDivider) * 100 );	
	OutputDebugString( szS4 );

	OutputDebugString(	"-----------------------------------------------------------------\n");
	HTchar szS5[1024];
	OutputDebugString(	"            메모리 트랙킹에 관한  새부 정보는\n" );
	sprintf( szS5,		"   실행 파일 폴더의 %s 파일을 참조하세요.\n", g_szLogFileName );
	OutputDebugString( szS5 );
	OutputDebugString(	"-----------------------------------------------------------------\n");


	if ( m_nNumHashEntryAllocations != 0 )	// HK : 메모리 누수가 존재하는 경우에는
	{
		fclose( pFile );
		HT_vDumpMemoryAllocations();		// HK : 메모리 누수에 대해 보고한다.
	}
	else
	{
		fclose( pFile );
	}
}

HTvoid CHTMemoryManager::HT_vDumpMemoryAllocations()	// HK : 현재 할당되어 있는 메모리에 대해 보고하는 역할을 한다.
{														// HK : 현재 해쉬 테이블에 있는 내용을 모두 보고하는 것이 역할을 수행하는 방법이다.
	if ( m_bCleanLogFileOnFirstRun )
	{
		unlink( g_szLogFileName );
		m_bCleanLogFileOnFirstRun = HT_FALSE;
	}

	FILE* pFile;
	if ( !(pFile = fopen( g_szLogFileName, "ab" )) ) return;
	
	fprintf( pFile, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \r\n" );
	fprintf( pFile, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \r\n" );
	fprintf( pFile, "           (프로그램이 종료되는 시점임에도) 해제되지 않고 남은 메모리           \r\n" );
	fprintf( pFile, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \r\n" );

	for ( HTint i = 0, j = 1; i < HT_HASH_SIZE; ++i )
	{
		for ( HTMemoryNode* pMemoryNode = m_ppHashTable[i]; pMemoryNode; pMemoryNode = pMemoryNode->m_pNext)
		{
			fprintf( pFile, "------------------------------------------------------------------------------- \r\n" );
			fprintf( pFile, "메모리 누수 %2d 번째\r\n", j++ );
			fprintf( pFile, "누수된 메모리량 : %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( pMemoryNode->m_ReportedSize, HT_FALSE ) );
			fprintf( pFile, "소스 파일       : %s\r\n", pMemoryNode->m_szSourceFile  );
			fprintf( pFile, "소스 라인       : %d\r\n", pMemoryNode->m_usSourceLine );
			fprintf( pFile, "할당 타입       : %s\r\n", HT_ALLOCATION_TYPE[pMemoryNode->m_AllocationType] );
			fprintf( pFile, "------------------------------------------------------------------------------- \r\n" );

			HTtchar szLog[HT_MAX_STR];
			sprintf( szLog, "\n소스 파일 %s의\n%d 번째 줄에서\n%s 형식으로 할당된 %d bytes 사이즈의 메모리가 아직 해제되지 않았습니다.\n", pMemoryNode->m_szSourceFile, pMemoryNode->m_usSourceLine, HT_ALLOCATION_TYPE[pMemoryNode->m_AllocationType], pMemoryNode->m_ReportedSize );
			//MessageBox( HT_NULL, szLog, "메모리 누수 경고", MB_ICONSTOP | MB_OK );
//			OutputDebugString( szLog );
		}
	}

	fprintf( pFile, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \r\n" );
	fprintf( pFile, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \r\n" );
	fprintf( pFile, "\r\n" );

	fclose( pFile );
}

HTvoid CHTMemoryManager::HT_vLogError( HTchar* szIn, ... )	// HK : printf와 같은 방식으로 입력된 스트링을 log file에 덤프시키는 역할을 한다.
{
	if ( m_bCleanLogFileOnFirstRun )
	{
		unlink( g_szLogFileName );
		m_bCleanLogFileOnFirstRun = HT_FALSE;
	}

	static HTchar szBuffer[2048];
	va_list	List;
	va_start( List, szIn );
	vsprintf( szBuffer, szIn, List );
	va_end( List );						// HK : szIn 이라는 입력 스트링을 진짜(?) 스트링으로 만들어 주는 부분.

	FILE* pFile = fopen( g_szLogFileName, "ab" );
	if ( !pFile ) return;

	fprintf( pFile, "%s\r\n", szBuffer );
	fclose( pFile );
}

HTint CHTMemoryManager::HT_iGetHashIndex( HTvoid* pvAddress )
{
	return ((HTuint)pvAddress >> 4) & (HT_HASH_SIZE -1);
}

HTint CHTMemoryManager::HT_iCalculateUnAllocatedMemory()	// HK : 할당되지 않은 메모리량을 반환하는 함수 (단위: Bytes)
{
	HTint iMemory = 0;
	
	for ( HTint i = 0; i < HT_HASH_SIZE; ++i )
	{
		for ( HTMemoryNode* pMemoryNode = m_ppHashTable[i]; pMemoryNode; pMemoryNode = pMemoryNode->m_pNext)
		{
			iMemory += pMemoryNode->m_ReportedSize;
		}
	}
	return iMemory;
}

//
//
//
//
//

HTvoid*	CHTMemoryManagerGlobal::HT_pvAllocateMemory( const HTtchar* szFileName, HTint iLine, size_t Size, ALLOC_TYPE AllocType, HTvoid* vAddress )
{											// HK : 메모리 할당 루틴
	HTMemoryNode* pMemoryNode;

	if ( (!g_pMemoryManager) && (!HT_bInitializeMemoryManager()) )	
	{
		if ( g_nNumMemoryAllocations != 0 )
		{
			HT_vLog( "The Memory Manager has already been released from memory, however an allocation was requested" );
			HT_vLog( "\t%-40s", HT_szFormatOwnerString( szFileName, iLine ) );
		}
		return malloc( Size );
	}

	if ( Size == 0 ) Size = 1;		// ANSI states that allocation requests of size 0 should return a valid pointer.
		
	
	InsertSimpleBreak( g_pMemoryManager->m_iTotalMemoryAllocations != g_pMemoryManager->m_iBreakOnAllocationCount );	// Has the user requested to break on the N-th allocation.

	InsertSimpleBreak( AllocType != HT_MM_UNKNOWN );		// If the type is UNKNOWN then this allocation was made from a source not set up to 
												// use memory tracking, include the MemoryManager header within the source to elimate this error.
	if ( AllocType == HT_MM_REALLOC )
	{
		HTMemoryNode* pMemoryNode = g_pMemoryManager->HT_pRemoveMemoryNode( vAddress );

		InsertSimpleBreak( pMemoryNode );	// Validate that the memory exists
		
		if ( !pMemoryNode ) g_pMemoryManager->HT_vLogError( "Request to reallocate RAM that was never allocated." );
		
		InsertSimpleBreak(	pMemoryNode->m_AllocationType == HT_MM_MALLOC ||
					pMemoryNode->m_AllocationType == HT_MM_CALLOC ||
					pMemoryNode->m_AllocationType == HT_MM_REALLOC );		// Validate that there is not a allocation/reallocation mismatch

		InsertSimpleBreak( (pMemoryNode->m_cOptions & HT_BREAK_ON_REALLOC) == 0x0 );	// Validate that a break point on reallocation has not been requested.

		pMemoryNode->m_ActualSize		= Size + g_pMemoryManager->m_nPaddingSize * sizeof(HTlong) * 2;
		pMemoryNode->m_ReportedSize		= Size;
		pMemoryNode->m_pvActualAddress	= realloc( pMemoryNode->m_pvActualAddress, pMemoryNode->m_ActualSize );
	}
	else
	{
		pMemoryNode = g_pMemoryManager->HT_pAllocateMemory();	// HK : 메모리를 트랙하기 위한 새로운 블럭을 생성한다.
		InsertSimpleBreak( pMemoryNode != HT_NULL );						// HK : 생성된 블록을 확인한다.
		
		if ( pMemoryNode == HT_NULL )
		{
			g_pMemoryManager->HT_vLogError( "Could not allocate memory for memory tracking.  Out of memory." );
			MessageBox( HT_NULL, "메모리 생성에 실패했습니다.", "Out of Memory", MB_ICONSTOP | MB_OK );
		}

		pMemoryNode->m_ActualSize		= Size + g_pMemoryManager->m_nPaddingSize * sizeof(HTlong) * 2;
		pMemoryNode->m_ReportedSize		= Size;
		pMemoryNode->m_pvActualAddress	= malloc( pMemoryNode->m_ActualSize );
		pMemoryNode->m_cOptions			= 0;
	}

	pMemoryNode->m_pvReportedAddress	= (HTchar*)pMemoryNode->m_pvActualAddress + g_pMemoryManager->m_nPaddingSize * sizeof(HTlong);
	pMemoryNode->m_usSourceLine			= iLine;
	pMemoryNode->m_usPaddingSize		= g_pMemoryManager->m_nPaddingSize;
	pMemoryNode->m_AllocationType		= AllocType;

	strncpy( pMemoryNode->m_szSourceFile, HT_szSourceFileStripper( szFileName ), 30 );

	if ( g_pMemoryManager->m_bLogAlways )
	{
//		g_pMemoryManager->HT_vLogError(
//			"Memory Allocation        : %-40s %8s(0x%08p) : %s",
//			HT_szFormatOwnerString( szFileName, iLine ),
//			HT_ALLOCATION_TYPE[AllocType],
//			pMemoryNode->m_pvReportedAddress,
//			HT_szMemorySizeString( Size ) );
	}

	InsertSimpleBreak( pMemoryNode->m_pvActualAddress );		// HK : 생성된 메모리 확인
	if ( !pMemoryNode->m_pvActualAddress )
	{
		g_pMemoryManager->HT_vLogError( "Request for allocation failed.  Out of memory." );
	}

	if ( AllocType == HT_MM_CALLOC) pMemoryNode->HT_vInitializeMemory( 0x00000000 );
	else							pMemoryNode->HT_vInitializeMemory( 0xBAADC0DE );	// Initialize the memory allocated for tracking upon deallocation
  
	g_pMemoryManager->HT_vInsertMemoryNode( pMemoryNode );	// HK : 생성된 메모리 노드를 해쉬 테이블에 삽입하여 이후 접근이 용이하게 한다.

	return pMemoryNode->m_pvReportedAddress;
}

HTvoid CHTMemoryManagerGlobal::HT_vDeAllocateMemory( HTvoid* pvAddress, ALLOC_TYPE AllocType )
{								// HK :	메모리를 해제하는 역할.
	if ( (!g_pMemoryManager) && (!HT_bInitializeMemoryManager()) )	// HK : 아직 메모리 메니져가 초기화가 안되었다면 여기서 초기화 한다.
	{
		free( pvAddress ); 
		if ( g_nNumMemoryAllocations != 0 )
		{
			HT_vLog( "The Memory Manager has already been released from memory, however a deallocation was requested" );
		}
		return;
	}

	// HK : 스택 탑에는 소스파일 이름이나 라인 수와 같은 내용이 담겨져 있다.
	HTStackNode* pInfo = g_pMemoryManager->m_TopStack.HT_bEmpty() ?
							HT_NULL : g_pMemoryManager->m_TopStack.HT_pGetHead();

	// HK : 메모리 메니져에 해쉬 테이블에 메모리로 정보가 들어있는가?
	HTMemoryNode* pMemoryNode = g_pMemoryManager->HT_pRemoveMemoryNode( pvAddress );
	if ( !pMemoryNode )			// HK : 이전에 할당된 메모리를 확인한다.
	{							// HK : 메모리 메니져에 의해 로그가 안되어 있는 경우 그저 메모리를 프리시키고 리턴한다.
		free( pvAddress );		// HK : 이는 이후 release 모드에서 이 메모리 메니져가 제거되더라도 잘 작동하게 하기 위한 장치다.
		return;
	}

	InsertSimpleBreak( pInfo != HT_NULL );

	if ( g_pMemoryManager->m_bLogAlways )	// HK : 메모리 해제를 로깅한다.
	{
//		g_pMemoryManager->HT_vLogError(
//			"Memory Deallocation      : %-40s %8s(0x%08p) : %s",
//			HT_szFormatOwnerString( pInfo->m_szFileName, pInfo->m_usLineNumber ),
//			HT_ALLOCATION_TYPE[AllocType],
//			pvAddress,
//			HT_szMemorySizeString( pMemoryNode->m_ReportedSize ) );
	}

	InsertSimpleBreak( AllocType != HT_MM_UNKNOWN );						// If the type is UNKNOWN then this allocation was made from a source not set up to 
																// use memory tracking, include the MemoryManager header within the source to elimate
																// this error.
	g_pMemoryManager->HT_bValidateMemoryUnit( pMemoryNode );	// HK : 메모리에 에러가 발생하지 않았는지 확인한다.
																// HK : 만약 발생했다면 HT_bValidateMemoryUnit에서 로그 파일에 기록할 것이다.
	/*
	InsertSimpleBreak(	AllocType == HT_MM_DELETE       && pMemoryNode->m_AllocationType == HT_MM_NEW       ||
				AllocType == HT_MM_DELETE_ARRAY && pMemoryNode->m_AllocationType == HT_MM_NEW_ARRAY ||
				AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_MALLOC    ||
				AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_CALLOC    ||
				AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_REALLOC );	// HK : 메모리를 할당하는 형식과 메모리를 해제하는 형식이 서로 같은지 확인한다.
	*/
	 if (	AllocType == HT_MM_DELETE       && pMemoryNode->m_AllocationType == HT_MM_NEW       ||
			AllocType == HT_MM_DELETE_ARRAY && pMemoryNode->m_AllocationType == HT_MM_NEW_ARRAY ||
			AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_MALLOC    ||
			AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_CALLOC    ||
			AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_REALLOC );
	else
	{
		g_pMemoryManager->HT_vLogError( "!!메모리 할당과 해제가 서로 맞지 않습니다 : %s (%d)", pMemoryNode->m_szSourceFile, pMemoryNode->m_usSourceLine );
		
		HTtchar szLog[HT_MAX_STR];
		sprintf( szLog, "\n%s (%d) 에서 %s 형식으로 생성된 메모리가\n%s (%d)\n에서 %s 형식으로 해제되고 있습니다.\n",
			pMemoryNode->m_szSourceFile, pMemoryNode->m_usSourceLine,
			HT_ALLOCATION_TYPE[pMemoryNode->m_AllocationType],
			pInfo->m_szFileName, pInfo->m_usLineNumber,
			HT_ALLOCATION_TYPE[AllocType] );
		MessageBox( HT_NULL, szLog, "메모리 생성과 해제 비일치 경고", MB_ICONSTOP | MB_OK );
	}
	////////////////////////////////////////////////////////////////////////////////////
	// HK : 여기서 User Break Point에 걸렸다면, new[]로 할당하고, delete로 지우는 등의//
	// HK : 할당 형식과 해제 형식이 다른것이다. 코드를 다시 살펴 보아야 한다. **^-^** //
	// HK : 이 경우 메모리 릭이 발생해도 로그 파일에는 체크가 되지 않음을 유의하자!!  //
	////////////////////////////////////////////////////////////////////////////////////

	InsertSimpleBreak( (pMemoryNode->m_cOptions & HT_BREAK_ON_DEALLOC) == 0x0 );	  // HK : Break on Deallocation이 Set이 되어 있는지 확인한다.

	free( pMemoryNode->m_pvActualAddress );

	g_pMemoryManager->HT_vDeAllocateMemory( pMemoryNode );	// HK : 메모리 노드를 해제한다.

	if ( pInfo )	// HK : 파일이름과 line을 가지고 있던 메모리 메니져를 해제한다.
	{
		g_pMemoryManager->m_TopStack.HT_pPop();
		free( pInfo );
	}
}

HTvoid CHTMemoryManagerGlobal::HT_vDeAllocateMemory( const HTtchar* szFileName, HTint iLine, HTvoid* pvAddress, ALLOC_TYPE AllocType )
{
	HT_vSetOwner( szFileName, iLine );
	HT_vDeAllocateMemory( pvAddress, AllocType );
}

HTvoid CHTMemoryManagerGlobal::HT_vSetOwner( const HTtchar *szFileName, HTint iLine )	// HK : 파일의 이름과 라인수를 채크하기 위한 놈.
{
	if ( g_pMemoryManager )
	{
		HTStackNode* pStackNode = (HTStackNode*)malloc( sizeof(HTStackNode) );
		pStackNode->m_szFileName = szFileName;
		pStackNode->m_usLineNumber = iLine;
		g_pMemoryManager->m_TopStack.HT_vPush( pStackNode );
	}
}

HTbool CHTMemoryManagerGlobal::HT_bInitializeMemoryManager()	// HK : 메모리 메니져를 생성하는 역할을 한다. 이미 존재하거나 잘 만들어졌다면 HT_TRUE를 반환하고
{																// HK : 과거에 만들어졌으나 사라진 경우 HT_FALSE를 반환한다.
	static HTbool bHasBeenInitialized = HT_FALSE;				// HK : 목표는 메모리 메니져가 최초에 생성되고 최후에 제거되는 놈임을 보장하는 것이다.

	if ( g_pMemoryManager )				// HK : 메모리 메니져가 이미 존재하는 경우.
	{
		return HT_TRUE;
	}
	else if ( bHasBeenInitialized )		// HK : 메모리 메니져가 이미 초기화가 되었던 경우
	{									// HK : 이미 존재하는지를 체크하였으므로 결과적으로 메모리 메니져는 없으나 초기화가 되었다는 것이므로 현재는 어찌어찌 해서 제거되었다는 것.
		return HT_FALSE;
	}
	else								// HK : 일반적인 경우로 이 함수에 들어온 목적인 메모리 메니져 초기화.
	{
		g_pMemoryManager = (CHTMemoryManager*)malloc( sizeof(CHTMemoryManager) );
		g_pMemoryManager->HT_vInitialize();
		atexit( HT_vReleaseMemoryManager );		// HK : 프로그램이 종료되기 전에 이 함수에 대한 로그를 남긴다.
		bHasBeenInitialized = HT_TRUE;
		return HT_TRUE;
	}
}

HTvoid CHTMemoryManagerGlobal::HT_vReleaseMemoryManager()	// HK : 프로그램이 종료될 때 자동으로 불리는 함수.
{															// HK : 모든 함수 중에 가장 마지막에 불려지는게 아주 중요하다.
	g_nNumMemoryAllocations = g_pMemoryManager->m_nNumHashEntryAllocations;
	g_pMemoryManager->HT_vRelease();						// HK : 로그 레포트를 작성하고 남은 메모리를 해제한다.
	free( g_pMemoryManager );
	g_pMemoryManager = HT_NULL;
}

HTtchar* CHTMemoryManagerGlobal::HT_szFormatOwnerString( const HTchar* szFileName, HTint iLine )
{
	static HTchar szString[90];
	memset( szString, '\0', sizeof(szString) );
	sprintf( szString, "%s(%05d)", HT_szSourceFileStripper( szFileName ), iLine );
	return szString;
}

HTtchar* CHTMemoryManagerGlobal::HT_szSourceFileStripper( const HTchar* szSourceFileName )
{
	if ( !szSourceFileName ) return HT_NULL;
	HTchar* szPtr = strrchr( szSourceFileName, '\\' );
	
	if ( szPtr ) return (szPtr + 1);
	szPtr = strrchr( szSourceFileName, '/' );
	
	if ( szPtr ) return (szPtr + 1);
	
	return (HTchar*)szSourceFileName;
}

HTvoid CHTMemoryManagerGlobal::HT_vLog( HTchar* szIn, ... )	// HK : 프로그램 작동 중에 발생하는 에러를 로깅하는 놈.
{
	static HTchar szBuffer[2048];
	va_list	List;
	va_start( List, szIn );
	vsprintf( szBuffer, szIn, List );
	va_end( List );

	FILE* pFile;
	
	if ( (pFile = fopen( g_szLogFileName, "ab" )) ) return;

	fprintf( pFile, "%s\r\n", szBuffer );
	fclose( pFile );
}

HTtchar* CHTMemoryManagerGlobal::HT_szInsertCommas( HTulong lValue )	// HK : 23456을 23,456으로 바꾸는 놈.
{
	static HTtchar szString[30];
	for ( HTint ii = 0; ii < 30; ++ii ) szString[ii] = HT_NULL;
	
	sprintf(szString, "%d", lValue);
	
	if ( strlen( szString ) > 3 )
	{
		memmove( &szString[strlen(szString)-3], &szString[strlen(szString)-4], 4 );
		szString[strlen( szString ) - 4] = ',';
	}
	if ( strlen( szString ) > 7 )
	{
		memmove( &szString[strlen(szString)-7], &szString[strlen(szString)-8], 8 );
		szString[strlen(szString) - 8] = ',';
	}
	if ( strlen( szString ) > 11 )
	{
		memmove( &szString[strlen(szString)-11], &szString[strlen(szString)-12], 12 );
		szString[strlen(szString) - 12] = ',';
	}
	return szString;
}

HTtchar* CHTMemoryManagerGlobal::HT_szMemorySizeString( HTulong lSize, HTbool bLengthenString )
{
	static HTchar szString[90];
	if (bLengthenString)
	{
		if ( lSize > (1024*1024) )	sprintf( szString, "%10s (%7.2fM)", HT_szInsertCommas( lSize ), lSize / (1024.0f * 1024.0f) );
		else if ( lSize > 1024 )	sprintf( szString, "%10s (%7.2fK)", HT_szInsertCommas( lSize ), lSize / 1024.0f );
		else						sprintf( szString, "%10s bytes     ", HT_szInsertCommas( lSize ), lSize );
	}
	else
	{
		if ( lSize > (1024*1024) )	sprintf(szString, "%s (%7.2fM)", HT_szInsertCommas( lSize ), lSize / (1024.0f * 1024.0f) );
		else if ( lSize > 1024 )	sprintf(szString, "%s (%7.2fK)", HT_szInsertCommas( lSize ), lSize / 1024.0f );
		else						sprintf(szString, "%s bytes     ", HT_szInsertCommas( lSize ), lSize );
	}
	return szString;
}

#endif // #ifdef HT_ACTIVATE_MEMORY_MANAGER
