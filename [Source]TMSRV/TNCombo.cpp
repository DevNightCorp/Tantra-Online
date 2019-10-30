/****************************************************************************

	파일명 : TNCombo.cpp

	작성자 : 정재웅(spencerj@korea.com)
	작성일 : 2003-09-15

	Tab size : 4 spaces
	프로젝트명 : Tantra


	설명 : 
		- 
		- 

****************************************************************************/
#include <stdlib.h>

#include "TNCombo.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__


TNCombo::TNCombo() : m_iPhase(0)	
{
	m_irgSkill[0] = m_irgSkill[1] = m_irgSkill[2] = m_irgSkill[3] = m_irgSkill[4] = 0 ;
}



TNCombo::~TNCombo()
{
}



void TNCombo::Init( int a_iSkill1, int a_iSkill2, int a_iSkill3, int a_iSkill4, int a_iSkill5 )
{
	m_irgSkill[0] = a_iSkill1 ;
	m_irgSkill[1] = a_iSkill2 ;
	m_irgSkill[2] = a_iSkill3 ;
	m_irgSkill[3] = a_iSkill4 ;
	m_irgSkill[4] = a_iSkill5 ;

	m_iPhase = 0 ;
}



void TNCombo::Input( int a_iSkill )
{
	if( eCmbo_MaxCount <= m_iPhase ) m_iPhase = 0 ;
	if( a_iSkill == m_irgSkill[m_iPhase] ) ++m_iPhase ;
	else
	{
		if( a_iSkill == m_irgSkill[0] ) m_iPhase = 1 ;
	}
}

