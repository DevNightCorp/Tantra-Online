/****************************************************************************

	파일명 : TNDeck.cpp

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

#include "TNDeck.h"


TNDeck::TNDeck() : m_iIndex(0), m_iSize(0)
{
}



TNDeck::~TNDeck()
{
	//if( NULL != m_irgCard ) delete [] m_irgCard;
}


void TNDeck::Init( int a_iMax )
{
	if( eDeck_MaxSize < a_iMax ) a_iMax = eDeck_MaxSize;
	m_iSize = a_iMax;
	m_iIndex = m_iSize - 1;
	memset( m_irgCard, 0, sizeof(m_irgCard) );
}


void TNDeck::AddCard( int a_iCard, int a_iCount )
{
	//if( m_iIndex >= m_iSize ) return;
	for( int i = 0; i < a_iCount; ++i )
	{
		m_irgCard[m_iIndex--] = a_iCard;
		if( 0 > m_iIndex ) return;
	}
	//m_iSize = m_iIndex;
}


void TNDeck::Shuffle( bool a_bFixed )
{
	m_iIndex = 0;
	if( 0 >= m_iSize ) return;
	if( a_bFixed ) return;

	//이제부터 섞기를 시작한다.
	for( int i = 0; i < m_iSize; ++i )
	{
		int iLoc = rand() % m_iSize;
		int iTemp = m_irgCard[i];
		m_irgCard[i] = m_irgCard[iLoc];
		m_irgCard[iLoc] = iTemp;
	}	
}



int TNDeck::Random()
{
	if( 0 >= m_iSize ) return 0;
	if( 0 > m_iIndex || m_iIndex >= m_iSize ) return 0;

	int iCard = m_irgCard[m_iIndex];
	++m_iIndex;
	if( m_iIndex >= m_iSize ) Shuffle();
	return iCard;
}


void TNDeck::ClearCards()
{
	memset( m_irgCard, 0, sizeof(m_irgCard) );
	m_iSize = 0;
	m_iIndex = 0;
}

