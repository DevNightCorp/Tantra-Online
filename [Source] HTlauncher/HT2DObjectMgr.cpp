
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"


//----------------------------------------------------------------------------//
//	파일 이름	: HT2DObject
//
//	파일 설명 	: 
//		- 각 모듈에 있는 이미지 접근 변수에서 집적 컨트롤 한다.
//			-> ID
//			-> 좌표
//
//	작성자		:
//		- 2002/05/17, Created by Jung Eui Kyu
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//
CHT2DObject::CHT2DObject()
{
}

//----------2D 스프라이트 삭제----------//
CHT2DObject::~CHT2DObject()
{
	g_pEngineHandler->HT_vDestroyObject( m_iImageID, 32 );
}

//----------2D 스프라이트 생성----------//
HTRESULT CHT2DObject::HT_2DObjectCreate( HTint nImageIndex, HTvector3 vecPos )
{
	m_vecPos = vecPos;
	m_iImageID = g_pEngineHandler->HT_iCreate2DSprite( nImageIndex, m_vecPos );
	m_bAciveSw = HT_FALSE;

	return HT_OK;
}

//----------2D 스프라이트 그리기----------//
HTvoid CHT2DObject::HT_2DObjectRender()
{
	g_pEngineHandler->HT_hrRenderObject( m_iImageID );
}



//----------------------------------------------------------------------------//
//	파일 이름	: HT2DObjectMgr
//
//	파일 설명 	: 
//		- 각 모듈에 있는 이미지 접근 변수에서 집적 컨트롤 하는 클래스를 관리
//			-> ID
//			-> 좌표
//
//	작성자		:
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

//----------초기화 및 리소스 초기 생성----------//
HTRESULT CHT2DObjectMgr::HT_2DObjectMgrInit()
{
	HT_LL_vInitList();

	return HT_OK;
}

//----------2D Sprite 생성----------//
HTint CHT2DObjectMgr::HT_2DObjectMgrCreate( HTint nImageIndex, HTvector3 vecPos )
{
	HTint iID = HT_LL_hrInsertAfter( nImageIndex, vecPos );

	return iID;
}

//----------2D Sprite 삭제----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrDelete( HTint iID )
{
	HT_LL_hrDeleteNode( iID );
}

//----------2D Sprite 활성화----------//
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

//----------2D Sprite 비 활성화----------//
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

//----------2D Sprite 리스트의 가장 뒤로 가져감----------//
HTvoid CHT2DObjectMgr::HT_2DObjectMgrSetBackSequence( HTint iID )
{
	HT_LL_hrChangeBackSequence( iID );
}

//----------ID를 반환----------//
HTint CHT2DObjectMgr::HT_2DObjectMgrGetID()
{
	return 1;
}

//----------위치지정 및 이동----------//
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

//----------확대 및 축소----------//
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

//----------확대 및 축소----------//
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


//----------확대 및 축소----------//
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


//----------회전----------//
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


//----------그리기----------//
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


//----------링커드 리스트----------//
//----------초기화----------//
HTvoid CHT2DObjectMgr::HT_LL_vInitList()
{
	m_s2DObjectHead = NULL;
	m_s2DObjectTail = NULL;

	m_s2DObjectHead = new HT_2DObject_NODE;
	m_s2DObjectTail = new HT_2DObject_NODE;

	m_s2DObjectHead->next = m_s2DObjectTail;
	m_s2DObjectTail->next = m_s2DObjectTail;
}

//----------삽입----------//
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


//----------하나 삭제----------//
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


//----------리스트의 가장 뒤로 가져가기----------//
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

//----------전부 삭제----------//
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

