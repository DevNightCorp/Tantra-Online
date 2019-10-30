
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTAOI.h"


HTAOI::HTAOI()
{
}	

HTAOI::~HTAOI()
{
}

//----------AOI영역 초기화----------//
HTRESULT HTAOI::HT_AOI_Init()
{
	m_Level1_Size = 2;
	m_Level2_Size = 4;
	m_Level3_Size = 8;
	m_Level4_Size = 16;
	m_Level5_Size = 32;
	m_Level6_Size = 35;
	m_Level7_Size = 64;
	m_Level8_Size = 128;

	return HT_OK;
}

//----------AOI레벨 반환----------//
BYTE HTAOI::HT_AOI_Level( HTPoint ptCell )
{
	HTPoint ptMainCharCell = g_cMainCharacter->m_cMainCharMove->HT_ptGetCellPosition();

	if( ptMainCharCell.x>=ptCell.x-m_Level1_Size && ptMainCharCell.x<=ptCell.x+m_Level1_Size &&
		ptMainCharCell.y>=ptCell.y-m_Level1_Size && ptMainCharCell.y<=ptCell.y+m_Level1_Size )
	{
		return AOI_LEVEL_1;
	}
	else if( ptMainCharCell.x>=ptCell.x-m_Level2_Size && ptMainCharCell.x<=ptCell.x+m_Level2_Size &&
			 ptMainCharCell.y>=ptCell.y-m_Level2_Size && ptMainCharCell.y<=ptCell.y+m_Level2_Size )
	{
		return AOI_LEVEL_2;
	}
	else if( ptMainCharCell.x>=ptCell.x-m_Level3_Size && ptMainCharCell.x<=ptCell.x+m_Level3_Size &&
			 ptMainCharCell.y>=ptCell.y-m_Level3_Size && ptMainCharCell.y<=ptCell.y+m_Level3_Size )
	{
		return AOI_LEVEL_3;
	}
	else if( ptMainCharCell.x>=ptCell.x-m_Level4_Size && ptMainCharCell.x<=ptCell.x+m_Level4_Size &&
			 ptMainCharCell.y>=ptCell.y-m_Level4_Size && ptMainCharCell.y<=ptCell.y+m_Level4_Size )
	{
		return AOI_LEVEL_4;
	}
	else if( ptMainCharCell.x>=ptCell.x-m_Level5_Size && ptMainCharCell.x<=ptCell.x+m_Level5_Size &&
			 ptMainCharCell.y>=ptCell.y-m_Level5_Size && ptMainCharCell.y<=ptCell.y+m_Level5_Size )
	{
		return AOI_LEVEL_5;
	}
	else if( ptMainCharCell.x>=ptCell.x-m_Level6_Size && ptMainCharCell.x<=ptCell.x+m_Level6_Size &&
			 ptMainCharCell.y>=ptCell.y-m_Level6_Size && ptMainCharCell.y<=ptCell.y+m_Level6_Size )
	{
		return AOI_LEVEL_6;
	}
	else if( ptMainCharCell.x>=ptCell.x-m_Level7_Size && ptMainCharCell.x<=ptCell.x+m_Level7_Size &&
			 ptMainCharCell.y>=ptCell.y-m_Level7_Size && ptMainCharCell.y<=ptCell.y+m_Level7_Size )
	{
		return AOI_LEVEL_7;
	}
	else if( ptMainCharCell.x>=ptCell.x-m_Level8_Size && ptMainCharCell.x<=ptCell.x+m_Level8_Size &&
			 ptMainCharCell.y>=ptCell.y-m_Level8_Size && ptMainCharCell.y<=ptCell.y+m_Level8_Size )
	{
		return AOI_LEVEL_8;
	}
	else
	{
		return AOI_LEVEL_NONE;
	}
}

//----------공격할수 있는 범위를 체크----------//
BYTE HTAOI::HT_AOI_AttackRange_Level( BYTE bType, DWORD iID, HTPoint pCell, BYTE bySize )
{
	HTPoint MainCharCell	= g_cMainCharacter->HT_ptMainChar_GetCellPosition();
//	BYTE byRange_of_Fire;
	HTint iRange_of_Fire;
	HTPoint bCellTerm;
	bCellTerm.x				= pCell.x - MainCharCell.x;
	bCellTerm.y				= pCell.y - MainCharCell.y;
	if( bCellTerm.x < 0 )	bCellTerm.x *= -1;
	if( bCellTerm.y < 0 )	bCellTerm.y *= -1;
	bCellTerm.x -= (HTint)( bySize/2 );
	bCellTerm.y -= (HTint)( bySize/2 );

	if( bType == 0x00 )			//	스킬
	{
		BYTE byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( iID );
							//		SKILL_BASIC_PARAMS*	 sSkillBasic = g_pclsEditorsData->SearchSkillParam( iID, byLevel );
							//		bRange_of_Fire			= sSkillBasic->byShootRange;
		//------------------------------------------------------------------
		// New Param - 선미
		//------------------------------------------------------------------
		//g_pParamMgr->HT_bGetPCSkillAttackDistance(iID, byLevel, &byRange_of_Fire);
		g_pParamMgr->HT_bGetPCSkillRange(iID, byLevel, &iRange_of_Fire);
		//------------------------------------------------------------------
	}
	else if( bType == 0x01 )	//	아이템( 투척무기 )
	{
							//		ITEM_BASIC_PARAM* sItemBasic = g_pclsEditorsData->SearchItemParam( iID );
							//		bRange_of_Fire			= sItemBasic->byAttackDistance;
		//------------------------------------------------------------------
		// New Param - 선미
		//------------------------------------------------------------------
		HTbyte byRange = 0;
		g_pParamMgr->HT_bGetItemRange(iID, &byRange);
		iRange_of_Fire = byRange;
		//------------------------------------------------------------------
	}
	else if( bType == 0x02 )	//	
	{
		iRange_of_Fire = 0;
	}

	if( iRange_of_Fire == 0 )
	{
		if( bCellTerm.x <= 1 || bCellTerm.y <= 1 )
			return 0x01;
	}
	else
	{
		if( bCellTerm.x<iRange_of_Fire && bCellTerm.y<iRange_of_Fire )
			return 0x01;
	}

	return 0x00;
}

BYTE HTAOI::HT_AOI_OtherChar_Request( HTint nX, HTint nZ )
{
	HTPoint MainCharCell = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	if( MainCharCell.x>=nX-10 && MainCharCell.x<=nX+10 &&
		MainCharCell.y>=nZ-10 && MainCharCell.y<=nZ+10 )
	{
		return 1;
	}
	
	return 0;
}
