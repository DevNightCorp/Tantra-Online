
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
#ifndef __HT2DOBJECT_H__
#define __HT2DOBJECT_H__


class CHT2DObject
{
public:
	CHT2DObject();
	~CHT2DObject();

	HTRESULT				HT_2DObjectCreate( HTint, HTvector3 );
	HTvoid					HT_2DObjectRender();


private:

public:
	HTint					m_iImageID;
	HTbool					m_bAciveSw;
	HTvector3				m_vecPos;

};

#endif



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
#ifndef __HT2DOBJECTMGR_H__
#define __HT2DOBJECTMGR_H__

//----------아이템 LL 구현을 위한 구조체----------//
typedef struct _HT_2DObject_NODE
{
	CHT2DObject						c2DObject;
	struct _HT_2DObject_NODE		*next;

} HT_2DObject_NODE;


class CHT2DObjectMgr
{
public:
	CHT2DObjectMgr();
	~CHT2DObjectMgr();
	HTvoid					HT_2DObjectMgrCleanUp();


	HTRESULT				HT_2DObjectMgrInit();

	HTint					HT_2DObjectMgrGetID();
	HTvoid					HT_2DObjectMgrSetPosition( HTint nID, HTvector3 vecPos );
	HTvoid					HT_2DObjectMgrSetScale( HTint nID, HTvector3 fScale );	//	확대 및 축소
	HTvoid					HT_2DObjectMgrSetScale( HTint nID, HTint iX, HTint iY );//	확대 및 축소
	HTvoid					HT_2DObjectMgrSetClip( HTint nID, HTint iLTX, HTint iLTY, HTint iRBX, HTint iRBY ); // Clipping
	HTvoid					HT_2DObjectMgrSetRotate( HTint nID, HTfloat fDegree );	//	회전
	HTint					HT_2DObjectMgrCreate( HTint, HTvector3 vecPos );	//	2D Sprite 생성
	HTvoid					HT_2DObjectMgrDelete( HTint );			//	2D Sprite 삭제
	HTvoid					HT_2DObjectMgrSetActive( HTint );		//	2D Sprite 활성화
	HTvoid					HT_2DObjectMgrSetAntiActive( HTint );	//	2D Sprite 비 활성화
	HTvoid					HT_2DObjectMgrSetBackSequence( HTint );	//	2D Sprite 리스트의 가장 뒤로 가져감

	
	HTvoid					HT_2DObjectMgrRender();

private:
	HTvoid					HT_LL_vInitList();						//	초기화
	HTvoid					HT_LL_hrDeleteNode( HTint iID );			//	삭제
	HTint					HT_LL_hrInsertAfter( HTint, HTvector3 );	//	삽입
	HTbool					HT_LL_hrChangeBackSequence( HTint );	//	링커드 리스트의 가장 뒤로 가져가기
	HTvoid					HT_LL_hrDeleteAll();					//	전체 지움


private:
	HT_2DObject_NODE*		m_s2DObjectHead;
	HT_2DObject_NODE*		m_s2DObjectTail;
	
};


#endif
