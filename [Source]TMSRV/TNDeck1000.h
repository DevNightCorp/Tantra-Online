/****************************************************************************************

	�ۼ��� : �����(spencerj@korea.com)
	�ۼ��� : 2003-09-09

	������ :
	������ :

	������Ʈ�� : 

	���� : TNDeck class�� size 1000���θ� �����ؼ� static���� �������� ��.

****************************************************************************************/
#ifndef __TNDeck1000_h__
#define __TNDeck1000_h__

#include <windows.h>

class TNDeck1000
{
public :
	TNDeck1000() ;
	~TNDeck1000() ;
	
	void Init() ;

	enum { eDeck_MaxSize = 1000, };
//Public Operations
public :
	byte Random() ;
	void Shuffle() ;
	void AddCard( byte a_byNum, int a_iCount ) ;
	void ClearCards() ;
	

private :
	int m_iIndex ;
	//int m_iSize ;

	byte m_byrgCard[1000] ;
};




#endif