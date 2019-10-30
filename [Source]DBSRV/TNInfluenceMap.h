/****************************************************************************

	파일명 : TNGridMap.h

	작성자 : 정재웅(spencerj@korea.com)
	작성일 : 2003-10-15

	Tab size : 4 spaces
	프로젝트명 : Tantra


	설명 : 영향력 분포도
		- 원래는 TNGridMap class가 있고 이를 TNInfluenceMap class가 상속을 하는 구조이면 좋을 것 같다.
		  (현재 Grip에 대해서 추가적이 요구 사항이 없어 간단하게 끝내고 말았으나 추후에 충분히 확장하기 쉽다.)
		- 

****************************************************************************/
#ifndef	__TNGridMap_h__
#define __TNGridMap_h__

#define TN_MAP_WIDTH	1024
#define TN_GRID_SIZE	4 // 한 GRID에 포함되는 CELL 개수 4*4
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
	int m_irgGrid[TN_GRID_WIDTH][TN_GRID_HEIGHT] ; // 원래는 grid 객체로 해야하나 요구사항이 없으므로 최대한 간단히 한다.
	int m_iMaxX ;
	int m_iMaxY ;
} ;


//extern TNInfluenceMap g_kInfluenceMap ; 



#endif // __TNGridMap_h__
