/****************************************************************************************

	�ۼ��� : �����(spencerj@korea.com)
	�ۼ��� : 2003-09-09

	������ :
	������ :

	������Ʈ�� : 

	���� : TNDeck class�� size 100���θ� �����ؼ� static���� �������� ��.

****************************************************************************************/
#ifndef __TNDeck100_h__
#define __TNDeck100_h__

#include <windows.h>

class TNDeck100
{
public :
	TNDeck100() ;
	~TNDeck100() ;
	
	void Init() ;
	enum { eDeck_MaxSize = 100, };

//Public Operations
public :
	byte Random() ;
	void Shuffle() ;
	void AddCard( byte a_byNum, int a_iCount ) ;
	void ClearCards() ;
	

private :
	int m_iIndex ;
	//int m_iSize ;

	byte m_byrgCard[100] ;
};




#endif