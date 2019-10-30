
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
	// HK : �޸� ���̿÷��̼��� �����ϱ� ���� �޸� ������ �յڿ� padding������ ���δ�.
	HTlong* plBeginning = (HTlong*)m_pvActualAddress;
	HTlong* plEnding = (HTlong*)((HTchar*)m_pvActualAddress + m_ActualSize - m_usPaddingSize * sizeof(HTlong));
	
	for ( HTushort us = 0; us < m_usPaddingSize; ++us )
	{
		plBeginning[us] = plEnding[us] = HT_PADDING;
	}

	// HK : �޸� ������ �ʱ�ȭ �Ѵ�. Ȥ�� ������ �ʴ� ������ ��츦 �˾ƺ��� ����
	plBeginning = (HTlong*)m_pvReportedAddress;
	HTuint nLength = m_ReportedSize / sizeof(HTlong);
	
	HTuint i;
	
	for ( i = 0; i < nLength; ++i )
	{
		plBeginning[i] = lBody;
	}
	
	HTchar* szString = (HTchar*)(&plBeginning[i]);
	nLength = m_ReportedSize - nLength * sizeof(HTlong);
	
	for ( i = 0; i < nLength; ++i )	// HK : HTlong������ �ʱ�ȭ ���� ���� �޸� ������ HTchar������ �ʱ�ȭ �Ѵ�.
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

HTvoid CHTMemoryManager::HT_vInitialize()	// HK : �̰����� CHTMemoryManager���� ���Ǵ� �޸𸮸� �ʱ�ȭ�Ѵ�.
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

HTvoid CHTMemoryManager::HT_vRelease()	// HK : CHTMemoryManager�� release�Ѵ�. log������ dump�ϰ�, ���� �޸𸮸� �������´�.
{	
	HT_vDumpLogReport();	// HK : ������ �޸� ���� ������ �α����Ͽ� �����Ѵ�.

	// HK : �޸� ������ �ִ� ��� CHTMemoryManager�� ���� �޸� ������ �����Ѵ�.
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
					free( pMemoryNode->m_pvActualAddress );		// HK : ���� ���� ���� ���� �޸𸮸� �������ش�
					free( pMemoryNode );						// HK : �޸� ��� ��ü�� ������ �ش�.
				}
			}
		}
	}

	// HK : ���ÿ� �����ִ� �޸𸮵� ���� ������ �ش�.
	while ( !m_TopStack.HT_bEmpty() )
	{
		free( m_TopStack.HT_pGetHead() );
		m_TopStack.HT_pPop();
	}

	// HK : �޸� ĳ�� ���� ������ �ش�.
	HTMemoryNode* pMemoryNode;
	while ( m_pMemoryCache )
	{
		pMemoryNode = m_pMemoryCache;
		m_pMemoryCache = pMemoryNode->m_pNext;
		if ( m_pMemoryCache != HT_NULL ) free( pMemoryNode );
	}
}

HTvoid CHTMemoryManager::HT_vInsertMemoryNode( HTMemoryNode* pMemoryNode )	// HK : �޸� ���� �ؽ� ���̺� �����Ǵµ� �� �ؽ� ���̺� �޸𸮸� �����ϴ� ������ �ϴ� �Լ�
{
	HTint iHashIndex = HT_iGetHashIndex( pMemoryNode->m_pvReportedAddress );
	pMemoryNode->m_pNext = m_ppHashTable[iHashIndex];
	pMemoryNode->m_pPrev = HT_NULL;

	if ( m_ppHashTable[iHashIndex] ) m_ppHashTable[iHashIndex]->m_pPrev = pMemoryNode;

	m_ppHashTable[iHashIndex] = pMemoryNode;
	
	// HK : �޸𸮸� �����ϴ� �迡 ��� ������ ����Ѵ�.
	m_nNumHashEntryAllocations++;

	m_nAllocatedMemory += pMemoryNode->m_ReportedSize;

	if ( m_nAllocatedMemory > m_nPeakMemoryAllocation )
					m_nPeakMemoryAllocation = m_nAllocatedMemory;
	if ( m_nNumHashEntryAllocations > m_nPeakTotalNumAllocations )
					m_nPeakTotalNumAllocations = m_nNumHashEntryAllocations;

	m_nTotalMemoryAllocated += pMemoryNode->m_ReportedSize;
	m_iTotalMemoryAllocations++;
}

HTMemoryNode* CHTMemoryManager::HT_pGetMemoryNode( HTvoid* pvAddress )	// HK : �޸� ��带 �ؽ����̺�κ��� ã�Ƽ� �� �޸��� �����͸� �����ϴ� �Լ�. �ش� �޸� ��尡 �������� �ʴ� ��� HT_NULL�� �����Ѵ�.
{
	HTMemoryNode *pMemoryNode = m_ppHashTable[HT_iGetHashIndex( pvAddress )];
	
	while ( pMemoryNode && pMemoryNode->m_pvReportedAddress != pvAddress )
	{
		pMemoryNode = pMemoryNode->m_pNext;
	}
	
	return pMemoryNode;
}

HTMemoryNode* CHTMemoryManager::HT_pRemoveMemoryNode( HTvoid* pvAddress )	// HK : HT_pGetMemoryNode�� ���� ������ �ϴ� �Լ�. �� �� �Լ��� �ؽ� ���̺�� ���� �ش� ��带 �����ϴ� ���ұ��� �Ѵ�.
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

		// HK : ���� ����
		m_nNumHashEntryAllocations--;
		m_nAllocatedMemory -= pMemoryNode->m_ReportedSize;
	}
	return pMemoryNode;

}

HTbool CHTMemoryManager::HT_bValidateMemoryUnit( HTMemoryNode* pMemoryNode )	// HK : �ش� �޸𸮿� Bound Violation�� �߻��Ͽ����� �ƴ����� Ȯ���ϰ�
{																				// HK : ���� ���Ǵ� �޸� ������ �󸶿������� ����ϴ� ������ �Ѵ�. 
	HTbool bSuccess = HT_TRUE;													// HK : �� �Լ��� �޸� ��尡 �����Ǳ� ���� �ҷ���� �Ѵ�.
																				// HK : HT_TRUE�� ��ȯ�ϴ� ��� Bound Violation�� �߻��� ���, �׷��� ���� ��� HT_FALSE�� ��ȯ�Ѵ�.
	HTuint nTotalBytesUsed = 0;
	HTuint nBoundViolations = 0;

	// HK : Bound Violation�� �߻��Ͽ������� üũ�ϴ� �κ�.
	HTlong* plBeginning = (HTlong*)pMemoryNode->m_pvActualAddress;
	HTlong* plEnding = (HTlong*)((HTchar*)pMemoryNode->m_pvActualAddress + pMemoryNode->m_ActualSize - pMemoryNode->m_usPaddingSize * sizeof(HTlong) );
	HTuint n;
	for ( n = 0; n < pMemoryNode->m_usPaddingSize; ++n )
	{
		if ( plBeginning[n] != HT_PADDING || plEnding[n] != HT_PADDING)
		{
			bSuccess = HT_FALSE;  // HK : �� if�� ���� ���� ���� Bound Violation�� �߻��� ����̴�.
			nBoundViolations++;
		}
	}

	if ( !bSuccess ) m_nNumBoundsViolations++;

	// HK : �Ҵ�� �޸� �������� ������ �󸶳� ���Ǿ������� üũ�ϴ� �κ��̴�.
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

	// HK : �޸� ��뷮�� %�� ����� ���� �ϴ� �κ�
	if ( m_bLogAlways && (nTotalBytesUsed != pMemoryNode->m_ReportedSize) )
	{
		HT_vLogError(
			"Unused Memory Detected   : %-40s %8s(0x%08p) : %s",
			CHTMemoryManagerGlobal::HT_szFormatOwnerString( pMemoryNode->m_szSourceFile, pMemoryNode->m_usSourceLine ),
			HT_ALLOCATION_TYPE[pMemoryNode->m_AllocationType],
			pMemoryNode->m_pvReportedAddress,
			CHTMemoryManagerGlobal::HT_szMemorySizeString( pMemoryNode->m_ReportedSize - nTotalBytesUsed ) );
	}

	// HK : Bounds Violation�� üũ�� ���� �ϴ� �κ�
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

HTvoid CHTMemoryManager::HT_vDeAllocateMemory( HTMemoryNode* pMemoryNode )	// HK : �������� ����� ���� �޸� ��带 ĳ���ϴ� �κ�
{
	m_nOverheadMemoryCost -= (pMemoryNode->m_usPaddingSize * 2 * sizeof(HTlong) );
	pMemoryNode->m_pNext = m_pMemoryCache;
	m_pMemoryCache = pMemoryNode;
//	m_pMemoryCache->m_pNext = HT_NULL;
}

HTMemoryNode* CHTMemoryManager::HT_pAllocateMemory()	// HK : �޸� ĳ���� �����ϸ� �׳���  ĳ������ ����� �����ϰ�,
{														// HK : �޸� ĳ���� �������� ������ ���ο� �޸� ��带 ����� �����Ѵ�.
	if (!m_pMemoryCache)	// HK : �޸� ĳ���� �������� �ʴ� ���
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

HTvoid CHTMemoryManager::HT_vDumpLogReport()	// HK : �޸� ���� ���� ��� ������ log ���Ͽ� ��� �����ϴ� �κ�.
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
	fprintf( pFile, "                            ��   �� �� ��  �� �� ��                              \r\n" );
	fprintf( pFile, "-------------------------------------------------------------------------------- \r\n" );
	fprintf( pFile, "                   ���� �� �������� �޸� ���� Ƚ��: %10s ��\r\n", CHTMemoryManagerGlobal::HT_szInsertCommas( m_iTotalMemoryAllocations ) );
	fprintf( pFile, "                        ���α׷����� ���� �޸𸮷�: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalMemoryAllocated ) );
	fprintf( pFile, "     (����� ��忡��) ���׷��� ���� ����� �޸𸮷�: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalOverHeadMemoryCost + m_nTotalMemoryAllocated ) );
	fprintf( pFile, "      �޸� ��뷮 üũ �� Ʈ��ŷ�� ���� �޸𸮷�: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalOverHeadMemoryCost ) );
	fprintf( pFile, "\r\n");
	fprintf( pFile, "\r\n");

	fprintf( pFile, "                           �� ��  �� �� ��  �� �� ��                             \r\n");
	fprintf( pFile, "-------------------------------------------------------------------------------- \r\n");
	fprintf( pFile, "                        �޸� ���� ������ �ִ� Ƚ��: %10s ��\r\n", CHTMemoryManagerGlobal::HT_szInsertCommas( m_nPeakTotalNumAllocations ) );
	fprintf( pFile, "                       ���α׷��� �ִ� �޸� ��뷮: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nPeakMemoryAllocation ) );
	fprintf( pFile, "(����� ��忡��) ���׷��� ���� ����� �ִ� �޸𸮷�: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nPeakOverHeadMemoryCost + m_nPeakMemoryAllocation ) );
	fprintf( pFile, " �޸� ��뷮 üũ �� Ʈ��ŷ�� ���� �ִ� �޸𸮷�: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nPeakOverHeadMemoryCost ) );
	fprintf( pFile, "\r\n");
	fprintf( pFile, "\r\n");

	fprintf( pFile, "              �� �� ��  �� �� �� ��  �� �� �� ��  �� ��  �� �� ��                \r\n");
	fprintf( pFile, "-------------------------------------------------------------------------------- \r\n");
	fprintf( pFile, "       ���� �Ҵ�� �޸� ���� �� ������ ���� ����: %10.2f %%\r\n", (HTfloat)(1 - (m_nTotalMemoryAllocated - m_nTotalMemoryUsed) / (HTfloat)iTotalMemoryDivider) * 100 );
	fprintf( pFile, "            ���� �Ҵ�� �޸� �� ������ ���� ����: %10.2f %%\r\n", (HTfloat)(m_nTotalMemoryAllocated - m_nTotalMemoryUsed) / (HTfloat)iTotalMemoryDivider * 100 );
	fprintf( pFile, "    ���� �Ҵ��� �Ǿ����� ���� ������ ���� �޸𸮷�: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalMemoryAllocated - m_nTotalMemoryUsed ) );
	fprintf( pFile, "\r\n");
	fprintf( pFile, "\r\n");

	fprintf( pFile, "           �� ��  �� �� ��  �� ��  �� �� ��  Ƚ �� (Bounds Violation)            \r\n");
	fprintf( pFile, "-------------------------------------------------------------------------------- \r\n");
	fprintf( pFile, "                        �Ҵ� ������ �Ѿ� ���� Ƚ��: %10s ��\r\n", CHTMemoryManagerGlobal::HT_szInsertCommas( m_nNumBoundsViolations ) );
	fprintf( pFile, "\r\n");
	fprintf( pFile, "\r\n");

	fprintf( pFile, "                              �� �� ��  �� ��                                     \r\n");
	fprintf( pFile, "-------------------------------------------------------------------------------- \r\n");
	fprintf( pFile, "                               �޸� ���� �߻� Ƚ��: %10s ��\r\n", CHTMemoryManagerGlobal::HT_szInsertCommas( m_nNumHashEntryAllocations ) );
	fprintf( pFile, "      �������� �Ҵ�Ǿ����� ������Ű�� ���� �޸𸮷�: %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( iMemoryLeak ) );
	fprintf( pFile, "    ���� �Ҵ�� �޸𸮿� ������Ų �޸��� ��ȣ ����: %10.2f %%\r\n", (HTfloat)(1 - (m_nTotalMemoryAllocated - iMemoryLeak) / (HTfloat)iTotalMemoryDivider) * 100 );
	fprintf( pFile, "( new[]�� �Ҵ� �ް� delete�� ������ ��쿡�� �޸� ������ �Ǵܵ��� ������ ���� )\r\n");
	fprintf( pFile, "\r\n");
	fprintf( pFile, "\r\n");

	OutputDebugString(	"\n-----------------------------------------------------------------\n");
	OutputDebugString(	"                   �� �� ��  �� ��  �� ��\n");
	OutputDebugString(	"-----------------------------------------------------------------\n");
	HTchar szS0[1024];
	sprintf( szS0,		"* ���α׷��� ���� ����� �޸𸮷� :           %s\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalMemoryAllocated ) );
	OutputDebugString( szS0 );

	HTchar szS1[1024];
	sprintf( szS1,		"* ���α׷��� �ִ� �޸� ��뷮 :             %s\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nPeakMemoryAllocation ) );	
	OutputDebugString( szS1 );

	HTchar szS2[1024];
	sprintf( szS2,		"* �Ҵ��� �Ǿ����� ������ ���� �޸𸮷� :    %s\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( m_nTotalMemoryAllocated - m_nTotalMemoryUsed ) );	
	OutputDebugString( szS2 );
	
	HTchar szS3[1024];
	sprintf( szS3,		"* Bounds Violation�� �߻�ȯ Ƚ�� :                     %s ��\n", CHTMemoryManagerGlobal::HT_szInsertCommas( m_nNumBoundsViolations ) );	
	OutputDebugString( szS3 );

	HTchar szS4[1024];
	sprintf( szS4,		"* �Ҵ�� �޸𸮿� ������ �޸� ��ȣ ���� :   %10.2f %%\n", (HTfloat)(1 - (m_nTotalMemoryAllocated - iMemoryLeak) / (HTfloat)iTotalMemoryDivider) * 100 );	
	OutputDebugString( szS4 );

	OutputDebugString(	"-----------------------------------------------------------------\n");
	HTchar szS5[1024];
	OutputDebugString(	"            �޸� Ʈ��ŷ�� ����  ���� ������\n" );
	sprintf( szS5,		"   ���� ���� ������ %s ������ �����ϼ���.\n", g_szLogFileName );
	OutputDebugString( szS5 );
	OutputDebugString(	"-----------------------------------------------------------------\n");


	if ( m_nNumHashEntryAllocations != 0 )	// HK : �޸� ������ �����ϴ� ��쿡��
	{
		fclose( pFile );
		HT_vDumpMemoryAllocations();		// HK : �޸� ������ ���� �����Ѵ�.
	}
	else
	{
		fclose( pFile );
	}
}

HTvoid CHTMemoryManager::HT_vDumpMemoryAllocations()	// HK : ���� �Ҵ�Ǿ� �ִ� �޸𸮿� ���� �����ϴ� ������ �Ѵ�.
{														// HK : ���� �ؽ� ���̺� �ִ� ������ ��� �����ϴ� ���� ������ �����ϴ� ����̴�.
	if ( m_bCleanLogFileOnFirstRun )
	{
		unlink( g_szLogFileName );
		m_bCleanLogFileOnFirstRun = HT_FALSE;
	}

	FILE* pFile;
	if ( !(pFile = fopen( g_szLogFileName, "ab" )) ) return;
	
	fprintf( pFile, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \r\n" );
	fprintf( pFile, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \r\n" );
	fprintf( pFile, "           (���α׷��� ����Ǵ� �����ӿ���) �������� �ʰ� ���� �޸�           \r\n" );
	fprintf( pFile, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \r\n" );

	for ( HTint i = 0, j = 1; i < HT_HASH_SIZE; ++i )
	{
		for ( HTMemoryNode* pMemoryNode = m_ppHashTable[i]; pMemoryNode; pMemoryNode = pMemoryNode->m_pNext)
		{
			fprintf( pFile, "------------------------------------------------------------------------------- \r\n" );
			fprintf( pFile, "�޸� ���� %2d ��°\r\n", j++ );
			fprintf( pFile, "������ �޸𸮷� : %s\r\n", CHTMemoryManagerGlobal::HT_szMemorySizeString( pMemoryNode->m_ReportedSize, HT_FALSE ) );
			fprintf( pFile, "�ҽ� ����       : %s\r\n", pMemoryNode->m_szSourceFile  );
			fprintf( pFile, "�ҽ� ����       : %d\r\n", pMemoryNode->m_usSourceLine );
			fprintf( pFile, "�Ҵ� Ÿ��       : %s\r\n", HT_ALLOCATION_TYPE[pMemoryNode->m_AllocationType] );
			fprintf( pFile, "------------------------------------------------------------------------------- \r\n" );

			HTtchar szLog[HT_MAX_STR];
			sprintf( szLog, "\n�ҽ� ���� %s��\n%d ��° �ٿ���\n%s �������� �Ҵ�� %d bytes �������� �޸𸮰� ���� �������� �ʾҽ��ϴ�.\n", pMemoryNode->m_szSourceFile, pMemoryNode->m_usSourceLine, HT_ALLOCATION_TYPE[pMemoryNode->m_AllocationType], pMemoryNode->m_ReportedSize );
			//MessageBox( HT_NULL, szLog, "�޸� ���� ���", MB_ICONSTOP | MB_OK );
//			OutputDebugString( szLog );
		}
	}

	fprintf( pFile, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \r\n" );
	fprintf( pFile, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \r\n" );
	fprintf( pFile, "\r\n" );

	fclose( pFile );
}

HTvoid CHTMemoryManager::HT_vLogError( HTchar* szIn, ... )	// HK : printf�� ���� ������� �Էµ� ��Ʈ���� log file�� ������Ű�� ������ �Ѵ�.
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
	va_end( List );						// HK : szIn �̶�� �Է� ��Ʈ���� ��¥(?) ��Ʈ������ ����� �ִ� �κ�.

	FILE* pFile = fopen( g_szLogFileName, "ab" );
	if ( !pFile ) return;

	fprintf( pFile, "%s\r\n", szBuffer );
	fclose( pFile );
}

HTint CHTMemoryManager::HT_iGetHashIndex( HTvoid* pvAddress )
{
	return ((HTuint)pvAddress >> 4) & (HT_HASH_SIZE -1);
}

HTint CHTMemoryManager::HT_iCalculateUnAllocatedMemory()	// HK : �Ҵ���� ���� �޸𸮷��� ��ȯ�ϴ� �Լ� (����: Bytes)
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
{											// HK : �޸� �Ҵ� ��ƾ
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
		pMemoryNode = g_pMemoryManager->HT_pAllocateMemory();	// HK : �޸𸮸� Ʈ���ϱ� ���� ���ο� ���� �����Ѵ�.
		InsertSimpleBreak( pMemoryNode != HT_NULL );						// HK : ������ ����� Ȯ���Ѵ�.
		
		if ( pMemoryNode == HT_NULL )
		{
			g_pMemoryManager->HT_vLogError( "Could not allocate memory for memory tracking.  Out of memory." );
			MessageBox( HT_NULL, "�޸� ������ �����߽��ϴ�.", "Out of Memory", MB_ICONSTOP | MB_OK );
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

	InsertSimpleBreak( pMemoryNode->m_pvActualAddress );		// HK : ������ �޸� Ȯ��
	if ( !pMemoryNode->m_pvActualAddress )
	{
		g_pMemoryManager->HT_vLogError( "Request for allocation failed.  Out of memory." );
	}

	if ( AllocType == HT_MM_CALLOC) pMemoryNode->HT_vInitializeMemory( 0x00000000 );
	else							pMemoryNode->HT_vInitializeMemory( 0xBAADC0DE );	// Initialize the memory allocated for tracking upon deallocation
  
	g_pMemoryManager->HT_vInsertMemoryNode( pMemoryNode );	// HK : ������ �޸� ��带 �ؽ� ���̺� �����Ͽ� ���� ������ �����ϰ� �Ѵ�.

	return pMemoryNode->m_pvReportedAddress;
}

HTvoid CHTMemoryManagerGlobal::HT_vDeAllocateMemory( HTvoid* pvAddress, ALLOC_TYPE AllocType )
{								// HK :	�޸𸮸� �����ϴ� ����.
	if ( (!g_pMemoryManager) && (!HT_bInitializeMemoryManager()) )	// HK : ���� �޸� �޴����� �ʱ�ȭ�� �ȵǾ��ٸ� ���⼭ �ʱ�ȭ �Ѵ�.
	{
		free( pvAddress ); 
		if ( g_nNumMemoryAllocations != 0 )
		{
			HT_vLog( "The Memory Manager has already been released from memory, however a deallocation was requested" );
		}
		return;
	}

	// HK : ���� ž���� �ҽ����� �̸��̳� ���� ���� ���� ������ ����� �ִ�.
	HTStackNode* pInfo = g_pMemoryManager->m_TopStack.HT_bEmpty() ?
							HT_NULL : g_pMemoryManager->m_TopStack.HT_pGetHead();

	// HK : �޸� �޴����� �ؽ� ���̺� �޸𸮷� ������ ����ִ°�?
	HTMemoryNode* pMemoryNode = g_pMemoryManager->HT_pRemoveMemoryNode( pvAddress );
	if ( !pMemoryNode )			// HK : ������ �Ҵ�� �޸𸮸� Ȯ���Ѵ�.
	{							// HK : �޸� �޴����� ���� �αװ� �ȵǾ� �ִ� ��� ���� �޸𸮸� ������Ű�� �����Ѵ�.
		free( pvAddress );		// HK : �̴� ���� release ��忡�� �� �޸� �޴����� ���ŵǴ��� �� �۵��ϰ� �ϱ� ���� ��ġ��.
		return;
	}

	InsertSimpleBreak( pInfo != HT_NULL );

	if ( g_pMemoryManager->m_bLogAlways )	// HK : �޸� ������ �α��Ѵ�.
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
	g_pMemoryManager->HT_bValidateMemoryUnit( pMemoryNode );	// HK : �޸𸮿� ������ �߻����� �ʾҴ��� Ȯ���Ѵ�.
																// HK : ���� �߻��ߴٸ� HT_bValidateMemoryUnit���� �α� ���Ͽ� ����� ���̴�.
	/*
	InsertSimpleBreak(	AllocType == HT_MM_DELETE       && pMemoryNode->m_AllocationType == HT_MM_NEW       ||
				AllocType == HT_MM_DELETE_ARRAY && pMemoryNode->m_AllocationType == HT_MM_NEW_ARRAY ||
				AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_MALLOC    ||
				AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_CALLOC    ||
				AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_REALLOC );	// HK : �޸𸮸� �Ҵ��ϴ� ���İ� �޸𸮸� �����ϴ� ������ ���� ������ Ȯ���Ѵ�.
	*/
	 if (	AllocType == HT_MM_DELETE       && pMemoryNode->m_AllocationType == HT_MM_NEW       ||
			AllocType == HT_MM_DELETE_ARRAY && pMemoryNode->m_AllocationType == HT_MM_NEW_ARRAY ||
			AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_MALLOC    ||
			AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_CALLOC    ||
			AllocType == HT_MM_FREE         && pMemoryNode->m_AllocationType == HT_MM_REALLOC );
	else
	{
		g_pMemoryManager->HT_vLogError( "!!�޸� �Ҵ�� ������ ���� ���� �ʽ��ϴ� : %s (%d)", pMemoryNode->m_szSourceFile, pMemoryNode->m_usSourceLine );
		
		HTtchar szLog[HT_MAX_STR];
		sprintf( szLog, "\n%s (%d) ���� %s �������� ������ �޸𸮰�\n%s (%d)\n���� %s �������� �����ǰ� �ֽ��ϴ�.\n",
			pMemoryNode->m_szSourceFile, pMemoryNode->m_usSourceLine,
			HT_ALLOCATION_TYPE[pMemoryNode->m_AllocationType],
			pInfo->m_szFileName, pInfo->m_usLineNumber,
			HT_ALLOCATION_TYPE[AllocType] );
		MessageBox( HT_NULL, szLog, "�޸� ������ ���� ����ġ ���", MB_ICONSTOP | MB_OK );
	}
	////////////////////////////////////////////////////////////////////////////////////
	// HK : ���⼭ User Break Point�� �ɷȴٸ�, new[]�� �Ҵ��ϰ�, delete�� ����� ����//
	// HK : �Ҵ� ���İ� ���� ������ �ٸ����̴�. �ڵ带 �ٽ� ���� ���ƾ� �Ѵ�. **^-^** //
	// HK : �� ��� �޸� ���� �߻��ص� �α� ���Ͽ��� üũ�� ���� ������ ��������!!  //
	////////////////////////////////////////////////////////////////////////////////////

	InsertSimpleBreak( (pMemoryNode->m_cOptions & HT_BREAK_ON_DEALLOC) == 0x0 );	  // HK : Break on Deallocation�� Set�� �Ǿ� �ִ��� Ȯ���Ѵ�.

	free( pMemoryNode->m_pvActualAddress );

	g_pMemoryManager->HT_vDeAllocateMemory( pMemoryNode );	// HK : �޸� ��带 �����Ѵ�.

	if ( pInfo )	// HK : �����̸��� line�� ������ �ִ� �޸� �޴����� �����Ѵ�.
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

HTvoid CHTMemoryManagerGlobal::HT_vSetOwner( const HTtchar *szFileName, HTint iLine )	// HK : ������ �̸��� ���μ��� äũ�ϱ� ���� ��.
{
	if ( g_pMemoryManager )
	{
		HTStackNode* pStackNode = (HTStackNode*)malloc( sizeof(HTStackNode) );
		pStackNode->m_szFileName = szFileName;
		pStackNode->m_usLineNumber = iLine;
		g_pMemoryManager->m_TopStack.HT_vPush( pStackNode );
	}
}

HTbool CHTMemoryManagerGlobal::HT_bInitializeMemoryManager()	// HK : �޸� �޴����� �����ϴ� ������ �Ѵ�. �̹� �����ϰų� �� ��������ٸ� HT_TRUE�� ��ȯ�ϰ�
{																// HK : ���ſ� ����������� ����� ��� HT_FALSE�� ��ȯ�Ѵ�.
	static HTbool bHasBeenInitialized = HT_FALSE;				// HK : ��ǥ�� �޸� �޴����� ���ʿ� �����ǰ� ���Ŀ� ���ŵǴ� ������ �����ϴ� ���̴�.

	if ( g_pMemoryManager )				// HK : �޸� �޴����� �̹� �����ϴ� ���.
	{
		return HT_TRUE;
	}
	else if ( bHasBeenInitialized )		// HK : �޸� �޴����� �̹� �ʱ�ȭ�� �Ǿ��� ���
	{									// HK : �̹� �����ϴ����� üũ�Ͽ����Ƿ� ��������� �޸� �޴����� ������ �ʱ�ȭ�� �Ǿ��ٴ� ���̹Ƿ� ����� ������� �ؼ� ���ŵǾ��ٴ� ��.
		return HT_FALSE;
	}
	else								// HK : �Ϲ����� ���� �� �Լ��� ���� ������ �޸� �޴��� �ʱ�ȭ.
	{
		g_pMemoryManager = (CHTMemoryManager*)malloc( sizeof(CHTMemoryManager) );
		g_pMemoryManager->HT_vInitialize();
		atexit( HT_vReleaseMemoryManager );		// HK : ���α׷��� ����Ǳ� ���� �� �Լ��� ���� �α׸� �����.
		bHasBeenInitialized = HT_TRUE;
		return HT_TRUE;
	}
}

HTvoid CHTMemoryManagerGlobal::HT_vReleaseMemoryManager()	// HK : ���α׷��� ����� �� �ڵ����� �Ҹ��� �Լ�.
{															// HK : ��� �Լ� �߿� ���� �������� �ҷ����°� ���� �߿��ϴ�.
	g_nNumMemoryAllocations = g_pMemoryManager->m_nNumHashEntryAllocations;
	g_pMemoryManager->HT_vRelease();						// HK : �α� ����Ʈ�� �ۼ��ϰ� ���� �޸𸮸� �����Ѵ�.
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

HTvoid CHTMemoryManagerGlobal::HT_vLog( HTchar* szIn, ... )	// HK : ���α׷� �۵� �߿� �߻��ϴ� ������ �α��ϴ� ��.
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

HTtchar* CHTMemoryManagerGlobal::HT_szInsertCommas( HTulong lValue )	// HK : 23456�� 23,456���� �ٲٴ� ��.
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
