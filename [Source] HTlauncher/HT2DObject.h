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

