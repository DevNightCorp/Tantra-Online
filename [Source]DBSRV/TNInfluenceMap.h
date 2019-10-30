/****************************************************************************

	���ϸ� : TNGridMap.h

	�ۼ��� : �����(spencerj@korea.com)
	�ۼ��� : 2003-10-15

	Tab size : 4 spaces
	������Ʈ�� : Tantra


	���� : ����� ������
		- ������ TNGridMap class�� �ְ� �̸� TNInfluenceMap class�� ����� �ϴ� �����̸� ���� �� ����.
		  (���� Grip�� ���ؼ� �߰����� �䱸 ������ ���� �����ϰ� ������ �������� ���Ŀ� ����� Ȯ���ϱ� ����.)
		- 

****************************************************************************/
#ifndef	__TNGridMap_h__
#define __TNGridMap_h__

#define TN_MAP_WIDTH	1024
#define TN_GRID_SIZE	4 // �� GRID�� ���ԵǴ� CELL ���� 4*4
#define TN_GRID_SPARE	5
#define TN_GRID_WIDTH	266 // 1024/4 + 5 + 5
#define TN_GRID_HEIGHT	266 // 1024/4 + 5 + 5


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

class TNInfluenceMap
{
// Constructor and Destructor
public :
	TNInfluenceMap() ;
	~TNInfluenceMap() ;

	void Init() ;

	enum { eInfl_None = 0, eInfl_Mon = -8, eInfl_PC = 8, eInfl_Forbidden = -256, eInfl_SaftyZone = -16384 } ;

public :
	void Print() ;
	void PropagteInfl( int a_iX, int a_iY, int a_iInfluence, int a_iRadius = 1 ) ;
	int CompareInfl( int a_iX, int a_iY, HS2D_COORD& a_kHighest, unsigned short a_nRadius ) ;
	int BuildInfluenceGrids( int a_iX, int a_iY, HS2D_COORD* a_pGrids, int& a_iSize ) ;

private :
	HS2D_COORD get_VirtualGridCoord( int a_iX, int a_iY ) ;
	HS2D_COORD get_RealGridCoord( HS2D_COORD& a_kCoord ) ;
	bool IsInValid( HS2D_COORD& a_kCoord ) ;
	void AssignInfluence( int a_iX, int a_iY, int a_iInfluence ) ;

private :
	int m_irgGrid[TN_GRID_WIDTH][TN_GRID_HEIGHT] ; // ������ grid ��ü�� �ؾ��ϳ� �䱸������ �����Ƿ� �ִ��� ������ �Ѵ�.
	int m_iMaxX ;
	int m_iMaxY ;
} ;


//extern TNInfluenceMap g_kInfluenceMap ; 



#endif // __TNGridMap_h__
