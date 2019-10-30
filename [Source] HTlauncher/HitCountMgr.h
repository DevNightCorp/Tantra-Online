#pragma once

//	Effect Type
#define EFFECTTYPE_NONE				0
#define EFFECTTYPE_ONLYUP			1
#define EFFECTTYPE_ONLYRIGHT		2
#define EFFECTTYPE_UPDOWN			3
#define EFFECTTYPE_EXPANSION		4

//	MAX NUMBER COUNT
#define MAXNUMBERCOUNT				10


//----------------------------------------------------------------------------//
//	Class �̸�	: HitCount
//
//	Class ���� 	: 
//		- �� Demage ��ġ�� ǥ��
//
//	�ۼ���		:
//		- 20032/11/26, Created by Jung Eui Kyu
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//
class HitCount
{
public:
	HitCount();
	~HitCount();

public:
	//	Input
	HTvoid			HT_vHitCount_Input( HTbyte byAttacker, short snRes, HTint iHitCount, HTvector3 vecTargetPos, HTint iTimeCount, HTbool bContinue );
	//	���� ���� ���� �پ��ֱ�
	HTvoid			HT_vHitCount_HitCount_Control();
	//	���� �� ����_�׼� ���� ����
	HTvoid			HT_vHitCount_HitCount_SetStartAction();
	//	���� �� ����_�Լ� ����
	HTvoid			HT_vHitCount_HitCountSetFun();
	//	���� �� ����_ī�޶���� �Ÿ� ���
	HTvoid			HT_vHitCount_GetCameraEyeDistance();
	//	���� �� ����_�����
	HTvoid			HT_vHitCount_SetHitNumberMake( HTint nCount );
	//	���� �� ����_�׼�
	HTvoid			HT_vHitCount_SetHitNumberAction();
	//	���� �� ����_üũ
	HTvoid			HT_vHitCount_SetHitNumberCheck();

	//	�� Ŭ������ ����� ���� ������ ������ġ->������
	HTvoid			HT_vHitCount_LiveTimeControl();

public:
	//	Delay Time
	DWORD			m_dwDelayTime;
	DWORD			m_dwStartDelayTime;
    //	�� ī��Ʈ �ѷ��ֱ�
	HTint			m_iHitCount_Demage;
	//	0 : PC -> Mon		:	White
	//	1 : Mon -> PC		:	Red
	//	2 : PC -> Mon Cri	:	Yellow
	//	3 : Mon-> PC Cri	:	Red
	//	4 : PC -> Mon Miss	:	Red
	//	5 : Mon -> PC Miss	:	White
    BYTE			m_byHitCount_NumberType;
	HTvector2		m_pHitCount_JudgmentPos;		//	�� ī��Ʈ ��ǥ
	HTint			m_nHitCount_PosSw;				//	�� ī��Ʈ ��ǥ ����� �޾Ҵ��� üũ
	
	HTint			m_nHitCount_NumberCount;
	HTint			m_nHitCount_NumberImageID[MAXNUMBERCOUNT];

	HTvector3		m_vecHitCount_TargetPos;

	//	���μ��� End Check
	HTbool			m_bHitCount_EndCheck;
	HTint			m_iHitCount_LiveTime;
	int             m_iHitCount_CombatResult;

	//	Effect	Type
    HTbyte			m_byHitCount_EffectType;
	HTfloat			m_fHitCount_ActionValue[MAXNUMBERCOUNT];
	HTfloat			m_fHitCount_LimitValue[MAXNUMBERCOUNT];
	HTint			m_iHitCount_Direct[MAXNUMBERCOUNT];
	HTdword			m_dwHitCount_EffectTime;
	//	���� ���������� �ľ�
	HTbool			m_bHitCount_Continue;
	//	������ ��Ƽ������ ���� �ȶٿ�� ���Ͽ�
	HTbool			m_bHitCount_HideNumber;
};


//----------------------------------------------------------------------------//
//	Class �̸�	: HitCountMgr
//
//	Class ���� 	: 
//		- �� Demage ��ġ�� ǥ���ϴ� Ŭ������ ����
//
//	�ۼ���		:
//		- 20032/11/26, Created by Jung Eui Kyu
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//

//	���� ��ũ�帮��Ʈ�� �����ϱ� ���� ����ü���ϴ�.
typedef struct _HT_HITCOUNT_NODE
{
	HitCount						cHitCount;
	struct _HT_HITCOUNT_NODE		*next;

} HT_HITCOUNT_NODE;


class HitCountMgr
{
public:
	HitCountMgr(void);
	~HitCountMgr(void);

	//	���� Ŭ���� ����
	//	byAttacker 0:Main,1:Other,2:Monster
	//	snRes 0:Normal, 1:Cri
	HTvoid					HT_vHitCountMgr_Create( HTbyte byAttacker, short snRes, HTint iHitCount, HTvector3 vecTargetPos, HTint iTimeCount, HTbool bContinue );
	//	���� Ŭ���� ��Ʈ��
	HTvoid					HT_vHitCountMgr_Control( HTfloat fElapsedTime );
	//	��ü ���� ����Ʈ ����
	HTvoid					HT_vHitCountMgr_AllDelete();

private:
	HTvoid					HT_LL_vInitList();
	HTvoid					HT_LL_hrInsertAfter( HTbyte byAttacker, short snRes, HTint iHitCount, HTvector3 vecTargetPos, HTint iTimeCount, HTbool bContinue );
	HTRESULT				HT_LL_hrDeleteNode();
	HTvoid					HT_LL_hrDeleteAll();

public:

private:
	HT_HITCOUNT_NODE*		m_sHitCounHead;
	HT_HITCOUNT_NODE*		m_sHitCounTail;

};
