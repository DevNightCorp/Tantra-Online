/****************************************************************************************

	�ۼ��� : �����(spencerj@korea.com)
	�ۼ��� : 2004-09-08

	������ :
	������ :

	������Ʈ�� : 

	���� : 

****************************************************************************************/
#ifndef __TNCombo_h__
#define __TNCombo_h__



class TNCombo
{
public :
	TNCombo() ;
	~TNCombo() ;
	
	void Init( int a_iSkill1, int a_iSkill2, int a_iSkill3, int a_iSkill4=0, int a_iSkill5=0 ) ;

//Public Operations
public :
	inline int get_Phase() { return m_iPhase ; }
	void Input( int a_iSkill ) ;


private :
	enum { eCmbo_MaxCount = 5, } ;

	int m_irgSkill[eCmbo_MaxCount] ;
	int m_iPhase ;
};


#endif