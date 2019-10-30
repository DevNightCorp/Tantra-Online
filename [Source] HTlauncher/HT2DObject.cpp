
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HT2DObject.h"


CHT2DObject::CHT2DObject()
{
}

//----------2D ��������Ʈ ����----------//
CHT2DObject::~CHT2DObject()
{
	g_pEngineHandler->HT_vDestroyObject( m_iImageID );
}

//----------2D ��������Ʈ ����----------//
HTRESULT CHT2DObject::HT_2DObjectCreate( HTint nImageIndex, HTvector3 vecPos )
{
	m_vecPos = vecPos;
	m_iImageID = g_pEngineHandler->HT_iCreate2DSprite( nImageIndex, m_vecPos );
	m_bAciveSw = HT_FALSE;

	return HT_OK;
}

//----------2D ��������Ʈ �׸���----------//
HTvoid CHT2DObject::HT_2DObjectRender()
{
	g_pEngineHandler->HT_hrRenderObject( m_iImageID );
}

