/****************************************************************************************

	�ۼ��� : �����(spencerj@korea.com)
	�ۼ��� : 2005-05-19

	������ :
	������ :

	������Ʈ�� : 

	���� : 

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
	void Start( int a_iGold ) ; // �Ʒ��� ��ü ������ �����Ѵ�.
	void StartSurvival() ; // �Ʒ��� �����̹� �̺�Ʈ�� �����Ѵ�.
	int AddEntrant( int a_iPC ) ;
	int RemoveEntrant( int a_iPC ) ;
	void Award() ;
	int OutputWinners( char* a_pBuf ) ;
	int OutputSurvivals( char* a_pBuf, int a_iJudge=0 ) ;
	int CheckWinner( int a_iPost=0 ) ; // winner�� �����Ǿ������� �Ǻ��Ѵ�.

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

	bool m_bIsProgressed ; // �Ʒ����� �����ִ��� �˻�
	int m_iGoldToAward ;
	int	m_iWinner ;
	char m_szAwarder[128] ;
	int m_irgAwarder[MAX_PARTY];

	int m_iEntryCount ;
	int m_irgEntry[eMaxEntry] ;
} ;

extern TNArena g_kArena ;


#endif