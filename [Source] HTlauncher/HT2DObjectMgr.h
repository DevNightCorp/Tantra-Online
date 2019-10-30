
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
#ifndef __HT2DOBJECTMGR_H__
#define __HT2DOBJECTMGR_H__

//----------������ LL ������ ���� ����ü----------//
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
	HTvoid					HT_2DObjectMgrSetScale( HTint nID, HTvector3 fScale );	//	Ȯ�� �� ���
	HTvoid					HT_2DObjectMgrSetScale( HTint nID, HTint iX, HTint iY );//	Ȯ�� �� ���
	HTvoid					HT_2DObjectMgrSetClip( HTint nID, HTint iLTX, HTint iLTY, HTint iRBX, HTint iRBY ); // Clipping
	HTvoid					HT_2DObjectMgrSetRotate( HTint nID, HTfloat fDegree );	//	ȸ��
	HTint					HT_2DObjectMgrCreate( HTint, HTvector3 vecPos );	//	2D Sprite ����
	HTvoid					HT_2DObjectMgrDelete( HTint );			//	2D Sprite ����
	HTvoid					HT_2DObjectMgrSetActive( HTint );		//	2D Sprite Ȱ��ȭ
	HTvoid					HT_2DObjectMgrSetAntiActive( HTint );	//	2D Sprite �� Ȱ��ȭ
	HTvoid					HT_2DObjectMgrSetBackSequence( HTint );	//	2D Sprite ����Ʈ�� ���� �ڷ� ������

	
	HTvoid					HT_2DObjectMgrRender();

private:
	HTvoid					HT_LL_vInitList();						//	�ʱ�ȭ
	HTvoid					HT_LL_hrDeleteNode( HTint iID );			//	����
	HTint					HT_LL_hrInsertAfter( HTint, HTvector3 );	//	����
	HTbool					HT_LL_hrChangeBackSequence( HTint );	//	��Ŀ�� ����Ʈ�� ���� �ڷ� ��������
	HTvoid					HT_LL_hrDeleteAll();					//	��ü ����


private:
	HT_2DObject_NODE*		m_s2DObjectHead;
	HT_2DObject_NODE*		m_s2DObjectTail;
	
};


#endif
