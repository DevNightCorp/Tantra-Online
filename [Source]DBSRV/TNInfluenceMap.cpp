/****************************************************************************

	���ϸ� : TNInfluenceMap.cpp

	�ۼ��� : �����(spencerj@korea.com)
	�ۼ��� : 2003-10-1TN_GRID_SPARE

	Tab size : 4 spaces
	������Ʈ�� : Tantra


	���� : 
		- 
		- 

****************************************************************************/
#include "stdafx.h"
#include "stdio.h"
#include "Basedef.h"
#include "TNDebug.h"

#include "TNInfluenceMap.h"





TNInfluenceMap::TNInfluenceMap()
{
}



TNInfluenceMap::~TNInfluenceMap()
{
}



// ��� grid�� 0 ����� ���� ���Ľ�Ű�� �׸��� spare grid ������ ���ؼ� ���� ���� ������ �������ش�.
void TNInfluenceMap::Init()
{
	int iInfluence = 0 ;

	m_iMaxX = TN_GRID_WIDTH - TN_GRID_SPARE - 1 ;
	m_iMaxY = TN_GRID_HEIGHT - TN_GRID_SPARE - 1 ;

	HS2D_COORD kCoord ;
	for( kCoord.y = 0 ; kCoord.y < TN_GRID_HEIGHT ; ++ kCoord.y )
		for( kCoord.x = 0 ; kCoord.x < TN_GRID_WIDTH ; ++kCoord.x )
		{
			if( IsInValid( kCoord ) ) iInfluence = eInfl_Forbidden ;
			else iInfluence = eInfl_None ;

			m_irgGrid[kCoord.y][kCoord.x] = iInfluence ;

			/*#ifdef __TN_INFLUENCE_MAP_LOG__
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "[TNInfluenceMap::Init()] Grid(%d,%d), �����:%d\r\n", kCoord.x, kCoord.y, iInfluence ) ;
				PNWrite( chBuf, ".\\MONSTER_LOG\\[Log]InfluenceMap.txt" ) ;
			}
			#endif*/
		}
}



HS2D_COORD TNInfluenceMap::get_VirtualGridCoord( int a_iX, int a_iY )
{
	HS2D_COORD KGrid ;
	KGrid.x = a_iX / TN_GRID_SIZE + TN_GRID_SPARE ;
	KGrid.y = a_iY / TN_GRID_SIZE + TN_GRID_SPARE ;

	return KGrid ;
}



HS2D_COORD TNInfluenceMap::get_RealGridCoord( HS2D_COORD& a_kCoord )
{
	HS2D_COORD KGrid ;
	KGrid.x = a_kCoord.x - TN_GRID_SPARE ;
	KGrid.y = a_kCoord.y - TN_GRID_SPARE ;

	return KGrid ;
}



bool TNInfluenceMap::IsInValid( HS2D_COORD& a_kCoord )
{
	if( TN_GRID_SPARE > a_kCoord.x || TN_GRID_SPARE > a_kCoord.y || a_kCoord.x > m_iMaxX || a_kCoord.y > m_iMaxY ) return true ;

	return false ;
}


// �� TN_GRID_SPARE*TN_GRID_SPARE ũ���� grid�� ���ĸ� �Ѵ�.
void TNInfluenceMap::PropagteInfl( int a_iX, int a_iY, int a_iInfluence, int a_iRadius )
{
	HS2D_COORD kCenter = get_VirtualGridCoord( a_iX, a_iY ) ;
	if( IsInValid( kCenter) ) return ;

	m_irgGrid[kCenter.y][kCenter.x] += a_iInfluence ;

	if( 0 < a_iRadius )
	{
		int iHalfInfl = a_iInfluence / 2 ;
		m_irgGrid[kCenter.y-1][kCenter.x-1] += iHalfInfl ;
		m_irgGrid[kCenter.y-1][kCenter.x]	+= iHalfInfl ;
		m_irgGrid[kCenter.y-1][kCenter.x+1] += iHalfInfl ;
		m_irgGrid[kCenter.y][kCenter.x-1]	+= iHalfInfl ;
		m_irgGrid[kCenter.y][kCenter.x+1]	+= iHalfInfl ;
		m_irgGrid[kCenter.y+1][kCenter.x-1] += iHalfInfl ;
		m_irgGrid[kCenter.y+1][kCenter.x]	+= iHalfInfl ;
		m_irgGrid[kCenter.y+1][kCenter.x+1] += iHalfInfl ;
	}

	if( 1 < a_iRadius )
	{
		int iQuarterInfl = a_iInfluence / 4 ;
		m_irgGrid[kCenter.y-2][kCenter.x-2] += iQuarterInfl ;
		m_irgGrid[kCenter.y-2][kCenter.x-1] += iQuarterInfl ;
		m_irgGrid[kCenter.y-2][kCenter.x]	+= iQuarterInfl ;
		m_irgGrid[kCenter.y-2][kCenter.x+1] += iQuarterInfl ;
		m_irgGrid[kCenter.y-2][kCenter.x+2] += iQuarterInfl ;

		m_irgGrid[kCenter.y+2][kCenter.x-2] += iQuarterInfl ;
		m_irgGrid[kCenter.y+2][kCenter.x-1] += iQuarterInfl ;
		m_irgGrid[kCenter.y+2][kCenter.x]	+= iQuarterInfl ;
		m_irgGrid[kCenter.y+2][kCenter.x+1] += iQuarterInfl ;
		m_irgGrid[kCenter.y+2][kCenter.x+2] += iQuarterInfl ;

		m_irgGrid[kCenter.y-1][kCenter.x+2] += iQuarterInfl ;
		m_irgGrid[kCenter.y][kCenter.x+2]	+= iQuarterInfl ;
		m_irgGrid[kCenter.y+1][kCenter.x+2] += iQuarterInfl ;

		m_irgGrid[kCenter.y-1][kCenter.x-2] += iQuarterInfl ;
		m_irgGrid[kCenter.y][kCenter.x-2]	+= iQuarterInfl ;
		m_irgGrid[kCenter.y+1][kCenter.x-2] += iQuarterInfl ;
	}
}


int TNInfluenceMap::BuildInfluenceGrids( int a_iX, int a_iY, HS2D_COORD* a_pGrids, int& a_iSize )
{
	HS2D_COORD kNow = get_VirtualGridCoord( a_iX, a_iY ) ;
	if( IsInValid( kNow ) ) return eTNRes_Failed ;
	short sRadius = 1 ;
	HS2D_COORD kEnd ;
	kEnd.x = kNow.x + sRadius ;
	kEnd.y = kNow.y + sRadius ;

	a_iSize = 0 ;
	HS2D_COORD kPos ;
	for( kPos.y = kNow.y - sRadius ; kPos.y <= kEnd.y ; ++kPos.y )
	{
		for( kPos.x = kNow.x - sRadius ; kPos.x <= kEnd.x ; ++kPos.x )
		{
			if( eInfl_Forbidden < m_irgGrid[kPos.y][kPos.x] )
			{
				a_pGrids[a_iSize] = get_RealGridCoord( kPos ) ;
				a_pGrids[a_iSize].x *= TN_GRID_SIZE ;
				a_pGrids[a_iSize].y *= TN_GRID_SIZE ;
				++a_iSize ;
			}
		}
	}

	return eTNRes_Succeeded ;
}


int TNInfluenceMap::CompareInfl( int a_iX, int a_iY, HS2D_COORD& a_kHighest, unsigned short a_usRadius )
{
	HS2D_COORD kNow = get_VirtualGridCoord( a_iX, a_iY ) ;
	if( IsInValid( kNow ) ) return 1 ;

	if( 2 < a_usRadius )
	{
		a_kHighest = get_RealGridCoord( kNow ) ;
		return 0 ;
	}

	HS2D_COORD krgGrid[25] ;
	unsigned short usIndex = 0 ;

	int iHighestInfl = 0 ;
	iHighestInfl = m_irgGrid[kNow.y][kNow.x] ;

	#ifdef __TN_INFLUENCE_MAP_LOG__
	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "[CompareInfl] �����:%d, �߽�grid(%d,%d), ������:%d r\n", iHighestInfl, kNow.x, kNow.y, a_usRadius ) ;
		PNWrite( chBuf, ".\\MONSTER_LOG\\[Log]InfluenceMap.txt" ) ;
	}
	#endif

	HS2D_COORD kEnd ;
	kEnd.x = kNow.x + a_usRadius ;
	kEnd.y = kNow.y + a_usRadius ;

	for( int y = kNow.y - a_usRadius ; y <= kEnd.y ; ++y )
	{
		for( int x = kNow.x - a_usRadius ; x <= kEnd.x ; ++x )
		{
			#ifdef __TN_INFLUENCE_MAP_LOG__
			{
				char chBuf[512] = { 0,0,0, } ;
				sprintf(chBuf, "[CompareInfl] �����:%d, ��ġ(%d,%d)\r\n", m_irgGrid[y][x], x, y ) ;
				PNWrite( chBuf, ".\\MONSTER_LOG\\[Log]InfluenceMap.txt" ) ;
			}
			#endif

			if( m_irgGrid[y][x] == iHighestInfl )
			{
				krgGrid[usIndex].x = x ;
				krgGrid[usIndex].y = y ;
				++usIndex ;
			}
			else if( m_irgGrid[y][x] > iHighestInfl ) // ���� ������� ū grid�� ã�Ƴ���.(030712, �����), PC���� ���� ���� ���� ã�´�.
			{
				iHighestInfl = m_irgGrid[y][x] ;

				usIndex = 0 ;
				krgGrid[usIndex].x = x ;
				krgGrid[usIndex].y = y ;
				++usIndex ;
			}
		}
	}

	if( eInfl_Forbidden >= iHighestInfl ) return 2 ;

	int iSelected = 0 ;
	if( 1 < usIndex ) // usIndex�� �ּ� ũ��� 1�̴�. ���� 0�� ������ �ʴ´�.
	{ //
		iSelected = rand() % usIndex ;
	}

	a_kHighest.x = krgGrid[iSelected].x ;
	a_kHighest.y = krgGrid[iSelected].y ;

	a_kHighest = get_RealGridCoord( a_kHighest ) ;

	#ifdef __TN_INFLUENCE_MAP_LOG__
	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "[LookAround] �ּҿ����:%d, �ּҿ����grid����:%d, ��ǥgrid(%d,%d) \r\n\r\n", iHighestInfl, usIndex, a_kHighest.x, a_kHighest.y ) ;
		PNWrite( chBuf, ".\\MONSTER_LOG\\[Log]InfluenceMap.txt" ) ;
	}
	#endif

	return 0 ;
}



// ���� grid ��ǥ�� �̿��� influence�� ���� ����
void TNInfluenceMap::AssignInfluence( int a_iX, int a_iY, int a_iInfluence )
{
	HS2D_COORD kGrid ;
	kGrid.x = a_iX / 4 ;
	kGrid.y = a_iY / 4 ;

	m_irgGrid[kGrid.y][kGrid.x] = a_iInfluence ;
}



void TNInfluenceMap::Print()
{
	int iInfluence = 0 ;
	int iForbiddenRange = eInfl_Forbidden*16 ;
	WriteLog( "\r\n\n\n", ".\\monster_log\\[Log]PrintInfluenceMap.txt" ) ;
	HS2D_COORD kCoord ;
	for( kCoord.y = 0 ; kCoord.y < TN_GRID_HEIGHT ; ++ kCoord.y )
	{
		WriteLog( "\r\n", ".\\monster_log\\[Log]PrintInfluenceMap.txt" ) ;
		for( kCoord.x = 0 ; kCoord.x < TN_GRID_WIDTH ; ++kCoord.x )
		{
			char chCell = 'O' ;
			if( eInfl_Forbidden >= m_irgGrid[kCoord.y][kCoord.x] && iForbiddenRange <= m_irgGrid[kCoord.y][kCoord.x] ) chCell = 'B' ;
			else if( iForbiddenRange > m_irgGrid[kCoord.y][kCoord.x] && eInfl_SaftyZone < m_irgGrid[kCoord.y][kCoord.x] ) chCell = 's' ;
			else if( eInfl_SaftyZone >= m_irgGrid[kCoord.y][kCoord.x] ) chCell = 'S' ;

			{
				char chBuf[128] = { 0,0,0, } ;
				sprintf(chBuf, "%c", chCell ) ;
				WriteLog( chBuf, ".\\monster_log\\[Log]PrintInfluenceMap.txt" ) ;
			}
		}
	}
}
