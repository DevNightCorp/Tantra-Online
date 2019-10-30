/****************************************************************************

	���ϸ� : TNArena.cpp

	�ۼ��� : �����(spencerj@korea.com)
	�ۼ��� : 2005-05-19

	Tab size : 4 spaces
	������Ʈ�� : Tantra


	���� : 
		- 
		- 

****************************************************************************/
#include <stdlib.h>
#include <string.h>

#include "CUser.h"
#include "Basedef.h"
#include "Server.h"
#include "TNArena.h"
#include "TNDebug.h"
#include "Language.h"
#include "SendFunc.h"


extern unsigned short         pMobGrid   [MAX_GRIDY][MAX_GRIDX];
extern CMob					pMob     [MAX_MOB];
extern CUser					pUser    [MAX_USER];


TNArena g_kArena ;


TNArena::TNArena() : m_bIsProgressed(false), m_iWinner(0), m_iGoldToAward(0), m_iEntryCount(0)
{
}



TNArena::~TNArena()
{
}


// �Ʒ��� �����̹� �̺�Ʈ�� ������ ��, �� �ʱ�ȭ�� �����ش�.
void TNArena::Init( int a_iGold )
{
	m_bIsProgressed = true ;
	m_iWinner = 0 ;
	m_iGoldToAward = a_iGold ;
	m_iEntryCount = 0 ;
	memset( m_irgEntry, 0, sizeof(m_irgEntry) ) ;
	memset( m_irgAwarder, 0, sizeof(m_irgAwarder) );
}


void TNArena::Start( int a_iGold )
{
	Init( a_iGold ) ;

	char chBuf[512] = { 0,0,0, } ;
	sprintf( chBuf, "Arena survival event is started. reward: %d\r\n"
		, a_iGold
		) ;
	WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ArenaEvent] );

	TriggerEvent( 0, 66, 0, 0, 0, 1111 ) ;
}


void TNArena::Award()
{
	if( 0 >= m_iWinner || MAX_USER <= m_iWinner ) return ;

	int iCount = 0;
	//for( int w = 0 ; w < MAX_PARTY ; ++w )
	//{
	//	if( 0 < m_irgAwarder[w] && MAX_USER > m_irgAwarder[w] )
	//	{
	//		if( USER_PLAY == pUser[m_irgAwarder[w]].Mode )	++iCount;
	//	}
	//}

	iCount = pMob[m_iWinner].CountPartyMember();
	int iGold = 0;
	iGold = m_iGoldToAward / iCount;

	pMob[m_iWinner].IncGold( iGold ) ;
	pMob[m_iWinner].NotifyUpdateUIMsg() ;

	char chBuf[512] = { 0,0,0, } ;
	sprintf( chBuf, "%s gets award(%d->%d)\r\n"
		, pMob[m_iWinner].MOB.szName, pMob[m_iWinner].MOB.nRupiah, pMob[m_iWinner].MOB.nRupiah+iGold
		) ;
	WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ArenaEvent] );

	for( int i = 0; i < MAX_PARTY; ++i )
	{
		int iPC = pMob[m_iWinner].m_irgParty[i];
		if( USER_PLAY == pUser[iPC].Mode )
		{
			char chBuf[512] = { 0,0,0, } ;
			sprintf( chBuf, "%s gets award(%d->%d)\r\n"
				, pMob[iPC].MOB.szName, pMob[iPC].MOB.nRupiah, pMob[iPC].MOB.nRupiah+iGold
				) ;
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ArenaEvent] );

			pMob[iPC].IncGold( iGold );
			pMob[iPC].NotifyUpdateUIMsg();
		}
	}

	//for( int w = 0 ; w < MAX_PARTY ; ++w )
	//{
	//	int iAwarder = m_irgAwarder[w];
	//	if( 0 < iAwarder && MAX_USER > iAwarder )
	//	{
	//		if( USER_PLAY == pUser[iAwarder].Mode )
	//		{
	//			pMob[iAwarder].IncGold( iGold );
	//			pMob[iAwarder].NotifyUpdateUIMsg() ;
	//			WriteLog( "\r\nRewarded!!!\r\n", g_szrgLogFileName[eLogFileName_ArenaEvent] ) ;
	//		}
	//	}
	//}

	#ifdef __TN_TOP_LOG__
	{
		//SYSTEMTIME st ;
		//GetLocalTime( &st ) ;
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\r\n[%dMM%dDD %dH%dM%dS] %s is awarded %d at the survival event!!!(User-Mode:%d, Mode:%d, FSM:%d, coord(%d,%d), n:%d, gold:%d, total gold:%d\r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, pMob[m_iWinner].MOB.szName, m_iGoldToAward, pUser[m_iWinner].Mode, pMob[m_iWinner].Mode, pMob[m_iWinner].m_eFSM
			, pMob[m_iWinner].TargetX, pMob[m_iWinner].TargetY
			, iCount, iGold, m_iGoldToAward
			) ;
		WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ArenaEvent] ) ;
	}
	#endif  

	//if( USER_PLAY == pUser[m_iWinner].Mode )
	//{
	//	if( 0 == strcmp( m_szAwarder, pMob[m_iWinner].MOB.szName ) )
	//	{
	//		int iHap = m_iGoldToAward + pMob[m_iWinner].MOB.nRupiah;
	//		if(iHap<0 || iHap>MAX_INT)
	//		{
	//			WriteLog( "\r\nRewarded but money full !!!\r\n", g_szrgLogFileName[eLogFileName_ArenaEvent] ) ;
	//		}
	//		else
	//		{
	//			pMob[m_iWinner].IncGold( m_iGoldToAward ) ;
	//			pMob[m_iWinner].NotifyUpdateUIMsg() ;
	//			WriteLog( "\r\nRewarded!!!\r\n", g_szrgLogFileName[eLogFileName_ArenaEvent] ) ;
	//		}
	//	}
	//}
	
	m_bIsProgressed = false ; // ������ �ϸ� �Ʒ��� �����̹� �̺�Ʈ�� ����� ������ �Ǵ��Ѵ�.
}


void TNArena::StartSurvival()
{
	// �����̹� �̺�Ʈ ���� ����
	#ifdef __TN_TOP_LOG__
	{
		//SYSTEMTIME st ;
		//GetLocalTime( &st ) ;
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\r\n[%dMM%dDD %dH%dM%dS] The survival game is started!!!(entrant: %d)\r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, m_iEntryCount
			) ;
		WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ArenaEvent] ) ;
	}
	#endif  

	for( int y = 677 ; y < 736 ; ++y )
	{
		for( int x = 285 ; x < 345 ; ++x )
		{
            int iPC = pMobGrid[y][x] ;
			if( 0 < iPC && MAX_USER > iPC )
			{
				if( eTNClan_GM == pMob[iPC].MOB.byTrimuriti ) continue ;
				int iRes = AddEntrant( iPC ) ;
				if( iRes ) ReturnPCToSaveZone( iPC ) ; // ���и� �ߴٸ�, save zone���� �Űܳ��´�.
			}
		}
	}

	int iCount = 0 ;
	for( int i = 0 ; i < eMaxEntry ; ++i )
	{
		if( 0 >= m_irgEntry[i] ) continue ;

		int iMob = m_irgEntry[i] ;
		++iCount ;
		#ifdef __TN_TOP_LOG__
		{
			char chBuf[512] = { 0,0,0, } ;				
			if( 0 == (iCount % 5) ) sprintf(chBuf, " %s \r\n", pMob[iMob].MOB.szName ) ;
			else sprintf(chBuf, " %s,", pMob[iMob].MOB.szName ) ;
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ArenaEvent] ) ;
		}
		#endif  
	}
}


int TNArena::OutputWinners( char* a_pBuf )
{
	int i = 0;
	for( int w = 0 ; w < MAX_PARTY ; ++w )
	{
		int iWinner = m_irgEntry[w] ;
		if( 0 < iWinner && MAX_USER > iWinner )
		{
			strcat( a_pBuf, pMob[iWinner].MOB.szName ) ;
			strcat( a_pBuf, " " ) ;

			m_irgAwarder[i] = iWinner;
			++i;
		}
	}

	return strlen( a_pBuf ) ;
}



int TNArena::OutputSurvivals( char* a_pBuf, int a_iJudge )
{
	char szSurvival[256] = { 0,0,0, } ;	
	for( int w = 0 ; w < MAX_PARTY ; ++w )
	{
		int iParty = 0 ;
		int iSurvival = m_irgEntry[w] ;
		if( 0 < iSurvival && MAX_USER > iSurvival )
		{
			if( 0 >= pMob[iSurvival].Leader ) iParty = iSurvival ;
			else iParty = pMob[iSurvival].Leader ;

			if( 0 == a_iJudge ) sprintf( szSurvival, "%s, ", pMob[iSurvival].MOB.szName ) ;
			else if( 1 == a_iJudge ) sprintf( szSurvival, "%d. %s:%d, ", iSurvival, pMob[iSurvival].MOB.szName, iParty ) ;

			strcat( a_pBuf, szSurvival ) ;
		}
	}

	return strlen( a_pBuf ) ;
}


int TNArena::AddEntrant( int a_iPC )
{
	if( 0 >= a_iPC || MAX_USER <= a_iPC ) return eTNRes_InvalidHandle ;
	if( IsFull() ) return eTNRes_Failed ;

	m_irgEntry[m_iEntryCount] = a_iPC ;
	++m_iEntryCount ; // �����ڼ� 1 ����
	pMob[a_iPC].m_bIsInArenaEntry = true ;

	#ifdef __TN_TOP_LOG__
	{
		char chBuf[512] = { 0,0,0, } ;				
		sprintf(chBuf, "%d. %s(%d) is entered to survial game. (survival:%d)\r\n", m_iEntryCount-1, pMob[a_iPC].MOB.szName, a_iPC, m_iEntryCount ) ;
		WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ArenaEvent] ) ;
	}
	#endif 

	return eTNRes_Succeeded ;
}



int TNArena::RemoveEntrant( int a_iPC )
{
	if( 0 >= a_iPC || MAX_USER <= a_iPC ) return eTNRes_InvalidHandle ;
	if( 0 >= m_iEntryCount ) eTNRes_Failed ;

	pMob[a_iPC].m_bIsInArenaEntry = false ;

	for( int i = 0 ; i < eMaxEntry ; ++i )
	{
		if( a_iPC == m_irgEntry[i] )
		{
			m_irgEntry[i] = 0 ;
			--m_iEntryCount ;

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, } ;				
				sprintf(chBuf, "\r\n%d. %s(%d) is failed to survial. (survival:%d)", i, pMob[a_iPC].MOB.szName, a_iPC, m_iEntryCount ) ;
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ArenaEvent] ) ;
			}
			#endif 

			// ���� ���϶��� sort, 100��, 50��, 7��
			int iRes = CheckWinner() ;
			if( !iRes ) // �Ʒ��� �����̹� ���ڰ� �����Ǿ���. ���� �̺�Ʈ�� trigger
			{
				TriggerEvent(0, 68, 0, 0, 0 ) ; // �Ʒ��� �����̹� �̺�Ʈ ����
			}

			return eTNRes_Succeeded ;
		}
	}

	return eTNRes_Failed ;
}



//-------------------------------------------
// ���ڰ� �����Ǿ����� Ȯ���� �Ѵ�.
//-------------------------------------------
int TNArena::CheckWinner( int a_iPost )
{
	// �����ڸ� ��˻��Ѵ�.
	m_iEntryCount = 0 ;

	int iLoc = 0 ;
	for( int j = 0 ; j < eMaxEntry ; ++j )
	{// ���ڵ��� �������� �ű��.
		int iMob = m_irgEntry[j] ;
		if( 0 == iMob ) continue ;
		if( 0 >= iMob || MAX_USER <= iMob ) m_irgEntry[j] = 0 ;
		if( pMob[iMob].IsDead() ) m_irgEntry[j] = 0 ;
		if( !pMob[iMob].m_bIsInArenaEntry ) m_irgEntry[j] = 0 ; // ���Ӱ� login�� �ؼ� ����PC�� handle�� ����ϴ� ��츦 ����ϱ� ����
		if( 285 > pMob[iMob].TargetX || 345 < pMob[iMob].TargetX ) m_irgEntry[j] = 0 ; // Ȥ � ������� 
		if( 677 > pMob[iMob].TargetY || 736 < pMob[iMob].TargetY ) m_irgEntry[j] = 0 ;		

		if( 0 < m_irgEntry[j] )
		{
			++ m_iEntryCount ;
			m_irgEntry[iLoc] = m_irgEntry[j] ;
			if( iLoc < j ) m_irgEntry[j] = 0 ;
			++iLoc ;
		}

		//if( iLoc == m_iEntryCount ) break ;
	}

	if( MAX_PARTY < m_iEntryCount ) return eTNRes_Failed ;

	//SYSTEMTIME st ;
	//GetLocalTime( &st ) ;

	if( 1 >= m_iEntryCount )
	{		
		m_iWinner = m_irgEntry[0] ;
	}
	else // ������ party�ΰ��� �˻��Ѵ�.
	{
		bool bIsParty = true ;
		int iPartyLeader = 0 ;
		int iVictim = 0 ;

		for( int i = 0 ; i < iLoc ; ++i )
		{
			int iPC = m_irgEntry[i] ;
			if( 0 >= iPC || MAX_USER <= iPC ) continue ;

			int iLeader = pMob[m_irgEntry[i]].Leader ;

            if( 0 >= iLeader ) // �����̳� ��Ƽ���̴�.
			{
				if( 0 == iPartyLeader ) iPartyLeader = m_irgEntry[i] ;
				else
				{
					if( iPartyLeader != m_irgEntry[i] )
					{
						bIsParty = false ; // ������ �ٸ� leader�� �����Ƿ� ���� party�� �ƴϴ�.
						iVictim = m_irgEntry[i] ;
					}
				}
			}
			else // ��Ƽ���̴�. ���� Leader���� ���� handle�� ����ִ�.
			{
				if( 0 == iPartyLeader ) iPartyLeader = iLeader ;
				else
				{
					if( iPartyLeader != iLeader )
					{
						bIsParty = false ; // ������ �ٸ� leader�� �����Ƿ� ���� party�� �ƴϴ�.
						iVictim = m_irgEntry[i] ;
					}
				}
			}

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, } ;				
				sprintf(chBuf, "%d. PC(%d//%s, Ldr:%d), bIsParty:%d \r\n", i, iPC, pMob[iPC].MOB.szName, iLeader, bIsParty ) ;
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ArenaEvent] ) ;
			}
			#endif  

			if( false == bIsParty )
			{
				return eTNRes_Failed ; // ���� party�� �ƴϴ�. ��� �ο��� �Ѵ�.
			}
		}

		m_iWinner = iPartyLeader ; // party leader�� ����Ѵ�.
		//strcpy( m_szAwarder, pMob[m_iWinner].MOB.szName ) ;
	}

	strcpy( m_szAwarder, pMob[m_iWinner].MOB.szName ) ;

	#ifdef __TN_TOP_LOG__
	{
		char chBuf[512] = { 0,0,0, } ;
		sprintf(chBuf, "\r\n\r\n[%dMM%dDD %dH%dM%dS] The survival game is ended!!!( award:%d, survival:%d, winners:%d,%s(%s) )\r\n"
			, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
			, m_iGoldToAward, m_iEntryCount
			, m_iWinner, pMob[m_iWinner].MOB.szName, m_szAwarder
			) ;
		WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ArenaEvent] ) ;
	}
	#endif  

	/*
	int iCount = 0 ;
	for( int i = 0 ; i < eMaxEntry ; ++i )
	{
		if( 0 >= m_irgEntry[i] ) continue ;

		int iMob = m_irgEntry[i] ;
		++iCount ;
		#ifdef __TN_TOP_LOG__
		{
			char chBuf[512] = { 0,0,0, } ;				
			if( 0 == (iCount % 5) ) sprintf(chBuf, " %s \r\n", pMob[iMob].MOB.szName ) ;
			else sprintf(chBuf, " %s,", pMob[iMob].MOB.szName ) ;
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_ArenaEvent] ) ;
		}
		#endif  
	}
	*/

	// ���ڰ� �����Ǿ���	
	return eTNRes_Succeeded ;
}


