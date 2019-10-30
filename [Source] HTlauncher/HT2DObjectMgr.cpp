
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"


//----------------------------------------------------------------------------//
//	���� �̸�	: HT2DObject
//
//	���� ���� 	: 
//		- �� ��⿡ �ִ� �̹��� ���� �������� ���� ��Ʈ�� �Ѵ�.
//			-> ID
//			-> ��ǥ
//
//	�ۼ���		:
//		- 2002/05/17, Created by Jung Eui Kyu
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//
CHT2DObject::CHT2DObject()
{
}

//----------2D ��������Ʈ ����----------//
CHT2DObject::~CHT2DObject()
{
	g_pEngineHandler->HT_vDestroyObject( m_iImageID, 32 );
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



//----------------------------------------------------------------------------//
//	���� �̸�	: HT2DObjectMgr
//
//	���� ���� 	: 
//		- �� ��⿡ �ִ� �̹��� ���� �������� ���� ��Ʈ�� �ϴ� Ŭ������ ����
//			-> ID
//			-> ��ǥ
//
//	�ۼ���		:
//		- 2003/11/25, Created by Jung Eui Kyu
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//
CHT2DObjectMgr::CHT2DObjectMgr()
{
}

CHT2DObjectMgr::~CHT2DObjectMgr()
{
}

HTvoid CHT2DObjectMgr::HT_2DObjectMgrCleanUp()
{
	HT_LL_hrDeleteAll();
	HT_DELETE( m_s2DObjectHead );
	HT_DELETE( m_s2DObjectTail );
}

//----------�ʱ�ȭ �� ���ҽ� �ʱ� ����----------//
HTRESULT CHT2DObjectMgr::HT_2DObjectMgrInit()
{
	HT_LL_vInitList();

	return HT_OK;
}

//----------2D Sprite ����----------//
HTint CHT2DObjectMgr::HT_2DObjectMgrCreate( HTint nImageIndex, HTvector3 vecPos )
{
	HTint iID = HT_LL_hrInsertAfter( nImageIndex, vecPos );

	return iID;
}

//----------2D Sprite ����----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrDelete( HTint iID )
{
	HT_LL_hrDeleteNode( iID );
}

//----------2D Sprite Ȱ��ȭ----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrSetActive( HTint iID )
{
	HT_2DObject_NODE *t;
	
	t = m_s2DObjectHead->next;
	while( t != m_s2DObjectTail )
	{
		if( t->c2DObject.m_iImageID == iID )
		{
			t->c2DObject.m_bAciveSw = HT_TRUE;
			break;
		}
		t = t->next;
	}

	HT_2DObjectMgrSetBackSequence( iID );
}

//----------2D Sprite �� Ȱ��ȭ----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrSetAntiActive( HTint iID )
{
	HT_2DObject_NODE *t;
	
	t = m_s2DObjectHead->next;
	while( t != m_s2DObjectTail )
	{
		if( t->c2DObject.m_iImageID == iID )
		{
			t->c2DObject.m_bAciveSw = HT_FALSE;
			break;
		}
		t = t->next;
	}
}

//----------2D Sprite ����Ʈ�� ���� �ڷ� ������----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrSetBackSequence( HTint iID )
{
	HT_LL_hrChangeBackSequence( iID );
}

//----------ID�� ��ȯ----------//
HTint CHT2DObjectMgr::HT_2DObjectMgrGetID()
{
	return 1;
}

//----------��ġ���� �� �̵�----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrSetPosition( HTint iID, HTvector3 vecPos )
{
	HT_2DObject_NODE *t;
	
	t = m_s2DObjectHead->next;
	while( t != m_s2DObjectTail )
	{
		if( t->c2DObject.m_iImageID == iID )
		{
			t->c2DObject.m_vecPos = vecPos;
			g_pEngineHandler->HT_hrMoveObject( t->c2DObject.m_iImageID, t->c2DObject.m_vecPos );

			break;
		}
		t = t->next;
	}
}

//----------Ȯ�� �� ���----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrSetScale( HTint nID, HTvector3 fScale )
{
	HT_2DObject_NODE *t;
	
	t = m_s2DObjectHead->next;
	while( t != m_s2DObjectTail )
	{
		if( t->c2DObject.m_iImageID == nID )
		{
			g_pEngineHandler->HT_hrScaleObject( nID, fScale );
			break;
		}
		t = t->next;
	}
}

//----------Ȯ�� �� ���----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrSetScale( HTint nID, HTint iX, HTint iY )
{
	HT_2DObject_NODE *t;
	
	t = m_s2DObjectHead->next;
	while( t != m_s2DObjectTail )
	{
		if( t->c2DObject.m_iImageID == nID )
		{
			g_pEngineHandler->HT_hrScaleObject( nID, iX, iY );
			break;
		}
		t = t->next;
	}
}


//----------Ȯ�� �� ���----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrSetClip( HTint nID, HTint iLTX, HTint iLTY, HTint iRBX, HTint iRBY ) // Clipping
{
	HT_2DObject_NODE *t;
	
	t = m_s2DObjectHead->next;
	while( t != m_s2DObjectTail )
	{
		if( t->c2DObject.m_iImageID == nID )
		{
			g_pEngineHandler->HT_hrClipObject( nID, iLTX, iLTY, iRBX, iRBY );
			break;
		}
		t = t->next;
	}
}


//----------ȸ��----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrSetRotate( HTint nID, HTfloat fDegree )
{
	HT_2DObject_NODE *t;
	
	t = m_s2DObjectHead->next;
	while( t != m_s2DObjectTail )
	{
		if( t->c2DObject.m_iImageID == nID )
		{
			g_pEngineHandler->HT_hrRotateObject( nID, fDegree );
			break;
		}
		t = t->next;
	}
}


//----------�׸���----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrRender()
{
	HT_2DObject_NODE *t;
	
	t = m_s2DObjectHead->next;
	while( t != m_s2DObjectTail )
	{
		if( t->c2DObject.m_bAciveSw == HT_TRUE )
			t->c2DObject.HT_2DObjectRender();
		t = t->next;
	}
}


//----------��Ŀ�� ����Ʈ----------//
//----------�ʱ�ȭ----------//
HTvoid CHT2DObjectMgr::HT_LL_vInitList()
{
	m_s2DObjectHead = NULL;
	m_s2DObjectTail = NULL;

	m_s2DObjectHead = new HT_2DObject_NODE;
	m_s2DObjectTail = new HT_2DObject_NODE;

	m_s2DObjectHead->next = m_s2DObjectTail;
	m_s2DObjectTail->next = m_s2DObjectTail;
}

//----------����----------//
HTint CHT2DObjectMgr::HT_LL_hrInsertAfter( HTint nImageIndex, HTvector3 vecPos )
{
	HT_2DObject_NODE *s;
	s = HT_NULL;
	s = new HT_2DObject_NODE;

	s->c2DObject.HT_2DObjectCreate( nImageIndex, vecPos );

	s->next = m_s2DObjectHead->next;
	m_s2DObjectHead->next = s;
	
	return s->c2DObject.m_iImageID;
}


//----------�ϳ� ����----------//
HTvoid CHT2DObjectMgr::HT_LL_hrDeleteNode( HTint iID )
{
	HT_2DObject_NODE *s;
	HT_2DObject_NODE *p;

	p = m_s2DObjectHead;
	s = p->next;
	while( s->c2DObject.m_iImageID != iID && s != m_s2DObjectTail )
	{
		p = p->next;
		s = p->next;
	}

	if( s != m_s2DObjectTail )
	{
		p->next = s->next;
		HT_DELETE( s );
	}
}


//----------����Ʈ�� ���� �ڷ� ��������----------//
HTbool CHT2DObjectMgr::HT_LL_hrChangeBackSequence( HTint iID )
{
	HT_2DObject_NODE *s;
	HT_2DObject_NODE *p;

	p = m_s2DObjectHead;
	s = p->next;
	while( s->c2DObject.m_iImageID != iID && s != m_s2DObjectTail )
	{
		p = p->next;
		s = p->next;
	}

	if( s != m_s2DObjectTail )
	{
		p->next = s->next;

		while( p->next != m_s2DObjectTail )
		{
			p = p->next;
		}

		p->next = s;
		s->next = m_s2DObjectTail;
	}

	return HT_TRUE;
}

//----------���� ����----------//
HTvoid CHT2DObjectMgr::HT_LL_hrDeleteAll()
{
	HT_2DObject_NODE *s;
	HT_2DObject_NODE *t;
	
	t = m_s2DObjectHead->next;
	while( t != m_s2DObjectTail )
	{
		s = t;
		t = t->next;
		HT_DELETE( s );
	}

	m_s2DObjectHead->next = m_s2DObjectTail;
}

