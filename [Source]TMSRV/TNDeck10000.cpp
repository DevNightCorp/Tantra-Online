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

#include "TNDeck10000.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__


TNDeck10000::TNDeck10000() : m_iIndex(0)//, m_iSize(10000)
{
	Init() ;
}



TNDeck10000::~TNDeck10000()
{
}


void TNDeck10000::Init()
{
	//m_iSize = 10000 ;
	m_iIndex = 0 ;
	memset( m_byrgCard, 0, sizeof(m_byrgCard) ) ;
}


void TNDeck10000::AddCard( byte a_byNum, int a_iCount )
{
	if( 0 > m_iIndex ) m_iIndex = 0 ;
	for( int i = 0 ; i < a_iCount ; ++i )
	{
		if( 10000 <= m_iIndex ) return ;
		m_byrgCard[m_iIndex] = a_byNum ;
		++m_iIndex ;
	}
}


void TNDeck10000::Shuffle()
{
	//srand( rand() /*timeGetTime()*/ ) ;
	for( int i = 0 ; i < 10000 ; ++i )
	{
		int iLoc = rand() % 10000 ;
		char chTemp = m_byrgCard[i] ;
		m_byrgCard[i] = m_byrgCard[iLoc] ;
		m_byrgCard[iLoc] = chTemp ;
	}
	m_iIndex = 0 ;
}


byte TNDeck10000::Random()
{
	if( 0 > m_iIndex || 10000 <= m_iIndex ) Shuffle() ;
	byte byCard = m_byrgCard[m_iIndex] ;
	++m_iIndex ;
	return byCard ;
}


void TNDeck10000::ClearCards()
{
	memset( m_byrgCard, 0, sizeof(m_byrgCard) ) ;
	//m_iSize = 10000 ;
	m_iIndex = 0 ;
}

