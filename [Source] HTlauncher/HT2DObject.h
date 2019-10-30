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

