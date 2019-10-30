#include "StdAfx.h"
#include "HTEngineHandler.h"
#include "HTFlocking.h"

   
CHTFlockingUnit::CHTFlockingUnit()
{
	id = -1;
	dwNPC = 0;
	vecCurPos	= HTvector3( 0.0f, 0.0f, 0.0f );
	vecVel		= HTvector3( 0.0f, 0.0f, 0.0f );
    eFlyingType = FLYING_CIRCLE;
}

CHTFlockingUnit::~CHTFlockingUnit()
{}

CHTFlockingUnit::CHTFlockingUnit( const CHTFlockingUnit& B )
{
	id          = B.id;
	dwNPC       = B.dwNPC;
	vecCurPos	= B.vecCurPos;
	vecVel		= B.vecVel;
    eFlyingType = B.eFlyingType;
}

  
CHTFlocking::CHTFlocking()
{}

CHTFlocking::~CHTFlocking()
{
	HTint iNumHawks = (HTint)m_vectorFlocking.size();
	for ( HTint i=0; i < iNumHawks; ++i )
	{
		CHTFlockingUnit* pHawk = m_vectorFlocking[i];
		HT_DELETE( pHawk );
	}

	m_vectorFlocking.clear();
}

HTRESULT
CHTFlocking::HT_hrCreate( HTint iNum )
{
	m_vectorFlocking.reserve( iNum );

	return HT_OK;
}

HTvoid
CHTFlocking::HT_vPushOne( HTdword dwNPC, HTvector3& vecBasePos )
{
	CHTFlockingUnit *pFlock = new CHTFlockingUnit;
    pFlock->SetNPC(dwNPC);
	pFlock->SetId(g_pEngineHandler->HT_iCreateNPC( dwNPC, vecBasePos ));
	pFlock->SetCurPos(vecBasePos);

	g_pEngineHandler->HT_hrStartAnimation( pFlock->GetId(), pFlock->GetNPC(), HT_ANISTATE_WLK, -1 );

	//m_vectorFlocking.push_back( std::vector<HTFlockingOne>::value_type( pFlock ) );
	m_vectorFlocking.push_back( pFlock );
}

HTRESULT
CHTFlocking::HT_hrUpdate( HTfloat fElapsedTime )
{
/*
    HTvector3 vectorToTarget;
    HTvector3& rCurVel = it->curVel;

    CHTVector::HT_pvecVec3Subtract(&vectorToTarget, &vecTarget, &vecPos);
    CHTVector::HT_pvecVec3Normalize( &vectorToTarget, &vectorToTarget );
#if 0
    //rCurVel.x = (vectorToTarget.x + ((VECTOR_CORRECTION_FACTOR-1) * rCurVel.x)) / VECTOR_CORRECTION_FACTOR;
    //rCurVel.y = (vectorToTarget.y + ((VECTOR_CORRECTION_FACTOR-1) * rCurVel.y)) / VECTOR_CORRECTION_FACTOR;
    //rCurVel.z = (vectorToTarget.z + ((VECTOR_CORRECTION_FACTOR-1) * rCurVel.z)) / VECTOR_CORRECTION_FACTOR;
#else
    HTvector3 temp;
    CHTVector::HT_pvecVec3Scale(&temp, &rCurVel,(VECTOR_CORRECTION_FACTOR-1));
    CHTVector::HT_pvecVec3Add(&temp, &temp, &vectorToTarget);
    CHTVector::HT_pvecVec3Scale(&rCurVel, &temp,(1.0f/VECTOR_CORRECTION_FACTOR));
#endif
    CHTVector::HT_pvecVec3Scale(&rCurVel, &rCurVel, (MAX_SPEED)); //CHTVector::HT_pvecVec3Scale(&rCurVel, &rCurVel, (fElapsedTime * MAX_SPEED));
    CHTVector::HT_pvecVec3Add(&vecPos, &vecPos, &rCurVel);
 */
	//g_pEngineHandler->HT_hrChangeAnimation(
	//g_pEngineHandler->HT_hrMoveObject(
	//g_pEngineHandler->HT_hrRotateObject(

/*
    // 规过1
    HTint iNumFlocking = (HTint)m_vectorFlocking.size();
    for ( HTint iFlocking; iFlocking < iNumFlocking; ++iFlocking )
    {
        HTFlockingOne& FlockingOne = m_vectorFlocking[iFlocking];
    }

    // 规过 2
    std::vector<HTFlockingOne>::iterator it;
    it = m_vectorFlocking.begin();

    while ( it != m_vectorFlocking.end() )
    {
        HTFlockingOne& FlockingOne = (*it);

        ++it;
    }
*/    


 //   HTint iNumHawks = (HTint)m_vectorFlocking.size();

 //   for ( HTint i=0; i < iNumHawks; ++i )
 //   {
 //       CHTFlockingUnit *pHawk = m_vectorFlocking[i];
	//	//HTvector3 vectorToTarget;
	////	HTvector3& rCurVel = pHawk->GetVel();

	////	CHTVector::HT_pvecVec3Subtract(&vectorToTarget, &vecTarget, &vecPos);
	////	CHTVector::HT_pvecVec3Normalize( &vectorToTarget, &vectorToTarget );
	////#if 0
	////	//rCurVel.x = (vectorToTarget.x + ((VECTOR_CORRECTION_FACTOR-1) * rCurVel.x)) / VECTOR_CORRECTION_FACTOR;
	////	//rCurVel.y = (vectorToTarget.y + ((VECTOR_CORRECTION_FACTOR-1) * rCurVel.y)) / VECTOR_CORRECTION_FACTOR;
	////	//rCurVel.z = (vectorToTarget.z + ((VECTOR_CORRECTION_FACTOR-1) * rCurVel.z)) / VECTOR_CORRECTION_FACTOR;
	////#else
	////	HTvector3 temp;
	////	CHTVector::HT_pvecVec3Scale(&temp, &rCurVel,(VECTOR_CORRECTION_FACTOR-1));
	////	CHTVector::HT_pvecVec3Add(&temp, &temp, &vectorToTarget);
	////	CHTVector::HT_pvecVec3Scale(&rCurVel, &temp,(1.0f/VECTOR_CORRECTION_FACTOR));
	////#endif
	////	CHTVector::HT_pvecVec3Scale(&rCurVel, &rCurVel, (MAX_SPEED)); //CHTVector::HT_pvecVec3Scale(&rCurVel, &rCurVel, (fElapsedTime * MAX_SPEED));
	////	CHTVector::HT_pvecVec3Add(&vecPos, &vecPos, &rCurVel);

	//	g_pEngineHandler->HT_hrMoveObject(pHawk->GetId(), pHawk->GetCurPos()); 
	//	//g_pEngineHandler->HT_hrMoveObject(pFlockingOne->id, &pFlockingOne->vecCurPos); 
 //   }




	return HT_OK;
}