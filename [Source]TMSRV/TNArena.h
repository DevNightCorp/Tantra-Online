/****************************************************************************************

	작성자 : 정재웅(spencerj@korea.com)
	작성일 : 2005-05-19

	수정자 :
	수정일 :

	프로젝트명 : 

	설명 : 

****************************************************************************************/
#ifndef __TNArena_h__
#define __TNArena_h__


class TNArena
{
public :
	TNArena() ;
	~TNArena() ;
	

	void Init( int a_iGold ) ;

// Public Operations
public :
	void Start( int a_iGold ) ; // 아레나 전체 일정을 시작한다.
	void StartSurvival() ; // 아레나 서바이벌 이벤트를 시작한다.
	int AddEntrant( int a_iPC ) ;
	int RemoveEntrant( int a_iPC ) ;
	void Award() ;
	int OutputWinners( char* a_pBuf ) ;
	int OutputSurvivals( char* a_pBuf, int a_iJudge=0 ) ;
	int CheckWinner( int a_iPost=0 ) ; // winner가 결정되었는지를 판별한다.

// Private Operations
private :
	
	
// Public Properties
public :
	bool IsProgressed() { return m_bIsProgressed ; }
	bool IsFull() { if( eArena_MaxEntry <= m_iEntryCount ) return true ; return false ; } 
	int get_GoldToAward() { return m_iGoldToAward ; }


// Attributes
private :
	enum { eMaxEntry = 200 , } ;

	bool m_bIsProgressed ; // 아레나가 열려있는지 검사
	int m_iGoldToAward ;
	int	m_iWinner ;
	char m_szAwarder[128] ;
	int m_irgAwarder[MAX_PARTY];

	int m_iEntryCount ;
	int m_irgEntry[eMaxEntry] ;
} ;

extern TNArena g_kArena ;


#endif