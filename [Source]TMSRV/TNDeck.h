/****************************************************************************************

	작성자 : 정재웅(spencerj@korea.com)
	작성일 : 2003-09-09

	수정자 :
	수정일 :

	프로젝트명 : 

	설명 : 

****************************************************************************************/
#ifndef __TNDeck_h__
#define __TNDeck_h__


class TNDeck
{
public :
	TNDeck();
	~TNDeck();
	
	enum { eDeck_MaxSize = 100, };

	void Init( int a_iMax );
	

//Public Operations
public :
	int Random();
	void Shuffle( bool a_bFixed = false );
	void AddCard( int a_iCard/*unsigned char a_uchCard*/, int a_iCount );
	void ClearCards();
	

private :
	int m_iIndex;
	int m_iSize;

	int m_irgCard[eDeck_MaxSize];
};




#endif