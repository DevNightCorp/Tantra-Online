/****************************************************************************

	파일명 : TNDeck100.cpp

	작성자 : 정재웅(spencerj@korea.com)
	작성일 : 2003-09-15

	Tab size : 4 spaces
	프로젝트명 : Tantra


	설명 : 
		- 
		- 

****************************************************************************/
#include <stdlib.h>
#include <string.h>

#include "TNDeck100.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

TNDeck100::TNDeck100() : m_iIndex(0)//, m_iSize(eDeck_MaxSize)
{
	Init() ;
}



TNDeck100::~TNDeck100()
{
}


void TNDeck100::Init()
{
	//m_iSize = 100 ;
	m_iIndex = 0 ;
	memset( m_byrgCard, 0, sizeof(m_byrgCard) ) ;
}


void TNDeck100::AddCard( byte a_byNum, int a_iCount )
{
	if( 0 > m_iIndex ) m_iIndex = 0 ;
	for( int i = 0 ; i < a_iCount ; ++i )
	{
		if( 100 <= m_iIndex ) return ;
		m_byrgCard[m_iIndex] = a_byNum ;
		++m_iIndex ;
	}
}


// 동일한 종류의 card가 여러 장 겹쳐 나오는 경향이 크다.
// 아주 잘 섞일 방법은 없는가?
void TNDeck100::Shuffle()
{
	//srand( rand() /*timeGetTime()*/ ) ;

	for( int i = 1 ; i < 100 ; i = i+3 )
	{
		int iLoc = rand() % 100 ;
		char chTemp = m_byrgCard[i] ;
		m_byrgCard[i] = m_byrgCard[iLoc] ;
		m_byrgCard[iLoc] = chTemp ;
	}

	for( int i = 3 ; i < 97 ; ++i )
	{
		char chCard = m_byrgCard[i] ;
		if( chCard == m_byrgCard[i-2] && chCard == m_byrgCard[i-1] && chCard == m_byrgCard[i+1] && chCard == m_byrgCard[i+2] ) // 연속 5개의 카드가 동일하다면, 아래쪽(배열위치상 뒤쪽)에 있는 카드와 섞는다.
		{
			for( int k = 0 ; k < 3 ; ++k )
			{
				int iLoc = rand() % (100-i) ;
				iLoc += i ;
				if( 0 > iLoc || 99 < iLoc ) continue ;
				if( chCard == m_byrgCard[iLoc] ) continue ;
				m_byrgCard[i] = m_byrgCard[iLoc] ;
				m_byrgCard[iLoc] = chCard ;
				break ;
			}
		}
	}
	
	for( int i = 1 ; i < 99 ; i = i+5 )
	{
		byte byCard = m_byrgCard[i] ;
		m_byrgCard[i] = m_byrgCard[99-i] ;
		m_byrgCard[99-i] = byCard ;
	}

	if( 0 == m_byrgCard[0] )
	{// 맨앞의 카드가 0(실패)일때, 성공으로 바꿔준다.
		byte byTemp = 0 ;
		for( int i = 50 ; i < 99 ; ++i )
		{
			if( 0 < m_byrgCard[i] )
			{
				byTemp = m_byrgCard[i] ;
				m_byrgCard[i] = 0 ;
				m_byrgCard[0] = byTemp ;
				break ;
			}
		}
	}

	#ifdef __TN_LOCAL_SERVER_SWITCH__
	{
		char chBuf[256] = { 0,0,0, } ;
		sprintf(chBuf, "%d %d %d %d %d %d %d %d %d %d %d \r\n"
			, m_byrgCard[0], m_byrgCard[1], m_byrgCard[2], m_byrgCard[3], m_byrgCard[4], m_byrgCard[5], m_byrgCard[6], m_byrgCard[7], m_byrgCard[8], m_byrgCard[9], m_byrgCard[10]
			) ;
		WriteLog( chBuf, ".\\Event\\[Log]Deck100.txt" ) ;
	}
	#endif


	//int iLoc = rand() % 100 ;
	//m_byrgCard[0]

	m_iIndex = 0 ;
}



byte TNDeck100::Random()
{
	if( 0 > m_iIndex || 100 <= m_iIndex ) Shuffle() ; ;
	byte byCard = m_byrgCard[m_iIndex] ;
	++m_iIndex ;
	return byCard ;
}



void TNDeck100::ClearCards()
{
	memset( m_byrgCard, 0, sizeof(m_byrgCard) ) ;
	//m_iSize = eDeck_MaxSize ;
	m_iIndex = 0 ;
}

