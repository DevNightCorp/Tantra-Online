#pragma once

//	2003.03.14�� ���Ǳ԰� ����
//	�� Ŭ������ ���� ����Ʈ�� �Ͼ �������� �����Ͽ� 
#define ATTACKPROCESS_NONE					1000
#define ATTACKPROCESS_ATTACKPOINT			1001
#define ATTACKPROCESS_FOLLOWEFFET			1002
#define ATTACKPROCESS_HITCOUNT				1003
#define ATTACKPROCESS_DAETH					1004

#define MAINCHAR_ATTACKTYPE_NONE					0
#define MAINCHAR_ATTACKTYPE_AUTOATTACK				1
#define MAINCHAR_ATTACKTYPE_SKILL					2
#define MAINCHAR_ATTACKTYPE_PRANA					3		//	���� ���Ƶ��̴� ��


#define FOLLOWTYPE_NORMAL						1
#define FOLLOWTYPE_JKSHOMER						2


#define MAX_SPEED (100.0f)
#define VECTOR_CORRECTION_FACTOR (5.0f)

//jks �߰��� attribute
struct HTFollowFX
{
	HTFollowFX()
	{
		idModel = -1;
		idFX = -1;
		vecTarget = HTvector3( 0.0f, 0.0f, 0.0f );
		vecPos = HTvector3( 0.0f, 0.0f, 0.0f );
		curVel = HTvector3( 0.0f, 0.0f, 0.0f );
		fTime = 0.0f;
	}

	HTint idModel;
	HTint idFX;
	HTvector3 vecTarget;
	HTvector3 vecPos;
	HTvector3 curVel; // jks - current velocity  
	HTfloat fTime;
};


//----------------------------------------------------------------------------//
//	Class �̸�	: HTAttack
//
//	Class ���� 	: 
//		- �� Object�� ���� ����� �����Ѵ�.
//
//	�ۼ���		:
//		- 20032/11/25, Created by Jung Eui Kyu
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//
class HTAttack
{
public:
	HTAttack(void);
	~HTAttack(void);

	//	�ʱ� ����Ÿ ����
    HTvoid			HT_vAttack_SetInitData( P_ATTACK_FACTOR info );
	
	//	�κ��͸� �̿��Ͽ� ���� ���� ���´�.		A:���� ����, B:�� ����
	HTfloat			HT_fAttackGetAngle( HTvector3 A, HTvector3 B );
		
	//	���� ��Ʈ��
	HTvoid			HT_vAttack_Control( HTfloat fElapsedTime );

	//	���� ����Ʈ���� ����
	HTvoid			HT_vAttack_AttackPoint();
	//	���� ����Ʈ���� ����_�ȷο찡���� ���� ����
	HTvoid			HT_vAttack_SetWithOutFollow();
    //	���� ����Ʈ���� ����_���� �Ÿ� ���
	HTvoid			HT_vAttack_DistanceCheck();
	// jks - Init part              
	// ������ �ʿ��� init �κ�
	HTvoid			HT_vAttack_Set_JKS_FlyingObject_Homer();
    //	���� ����Ʈ���� ����_�ȷο� ���� ����
	HTvoid			HT_vAttack_SetWithFollow();
	
	//	�ȷο� ����Ʈ ��Ʈ��
	HTvoid			HT_vAttack_AttackFollowEffect( HTfloat fElapsedTime );
	//	�ȷο� ����Ʈ go
	HTvoid			HT_vAttack_AttackFollowEffectGo( HTfloat fElapsedTime );
	//	jks - code for homing flying object.
	HTvoid			HT_vAttack_AttackFollow_FlyingObject_JKS_Homer( HTfloat fElapsedTime );
	//	����Ÿ���� �ȷο��϶� �� ��ǥ�� �ɸ��� �𸶴� ������ �ø�
	HTvoid			HT_vAttack_AttackFollow_TargetCheck();
	//	���� üũ
	HTvoid			HT_vAttack_AttackFollow_AngleCheck();

	//	�ȷο� ����Ʈ_üũ
	HTvoid			HT_vAttack_AttackFollowCheck();
	//	�ȷο� ����Ʈ_üũ
	HTvoid			HT_vAttack_AttackGuidedMislFollowCheck();

	//	ĳ���� ���� ����Ʈ���� ����
	HTvoid			HT_vAttack_SetAttackPoint();
	//	�� Ŭ������ ����� ���� ������ ������ġ->������
	HTvoid			HT_vAttack_LiveTimeControl();

	//	������ ���� ��û��
	HTvoid			HT_vNetWork_CSP_MSG_Attack();
	//	������ ��ų(�ܼ�) ���� ��û
	HTvoid			HT_vNetWork_CSP_Cast_Unit_Cast( short snAttackSkillID, short snAttackerKeyID, short snTargetKeyID, HTvector3 vecTargetPos );
	//	������ ��ų(����) ���� ��û
	HTvoid			HT_vNetWork_CSP_Cast_Area_Cast();

public:
	HTint			m_nAttack_Process;				//	���� ���μ���

	//	JKS For Homer (Flying Object)
	HTFollowFX		m_oFollowFX;

	//	��ų ���� Ÿ��
	HTdword			m_dwAttack_SkillType;
	//	�� Ŭ������ ����� ���� ������ ������ġ->������
	DWORD			m_nAttack_LiveTime;
	//	Ŭ������ �����µ� �ʿ��� ����
	P_ATTACK_FACTOR	m_pFactor;
	//	���ư��� Ÿ��
	HTint			m_iAttack_FolowType;
	HTbool			m_bAttack_PursuitSw;		//	�����ǥ�� ������ ������?
	BYTE			m_byAttack_PursuitCount;

	HTfloat			m_fAttack_EOTransValue;		//	������� ��ȭ��
	HTfloat			m_fAttack_TimeTransValue;	//	�ð� ��ȭ��
	HTfloat			m_fAttack_TotalTime;		//	��ü �ð�

	//	�ȷο� �� ���� ���ǵ�
	HTfloat			m_fAttack_CorrectSpeed;

	//	����Ÿ���� PIERCING �������� ���缿�� ���ϱ� ����
	BYTE			m_byAttack_PiercingCellCount;
	HTint			m_pAttack_PiercingData[TN_MAX_TARGET_COUNT];

	//	�ȷο� ���ݽ� ������ �¾Ҵ��� ����
	HTbool			m_bAttack_GoodHit;

	//	���÷��� �����϶�
	HTint			m_iAttck_SplashIndex;

	//	�ȷο� ���ݽ� ���ư� �ð��� ����
	HTdword			m_dwAttack_FollowTime;
	//	�ȷο� �� �ӵ�
	HTint			m_iAttack_ModelSpeed;
	//	Homer Speed
	HTint			m_iAttack_HomerSpeed;
};


//----------------------------------------------------------------------------//
//	Class �̸�	: HTAttackManager
//
//	Class ���� 	: 
//		- �� Object�� ���� ����� �����ϴ� Ŭ������ ����
//
//	�ۼ���		:
//		- 20032/11/25, Created by Jung Eui Kyu
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//


//	���� ��ũ�帮��Ʈ�� �����ϱ� ���� ����ü���ϴ�.
typedef struct _HT_ATTACK_NODE
{
	HTAttack						cAttack;
	struct _HT_ATTACK_NODE			*next;

} HT_ATTACK_NODE;


class HTAttackManager
{
public:
	HTAttackManager(void);
	~HTAttackManager(void);

	//	���� Ŭ���� ����
	HTvoid					HT_vAttackMgr_Create( P_ATTACK_FACTOR );
	//	���� Ŭ���� ��Ʈ��
	HTvoid					HT_vAttackMgr_Control( HTfloat fElapsedTime );
	//	��ü ���� ����Ʈ ����
	HTvoid					HT_vAttackMgr_AllDelete();
	
	//	����ĳ���� �ȷο� ���� ��ġ�� �޾ƿ�
	HTRESULT				HT_hrAttackMgr_GetFollowModel( HTvector3& vecFront, HTvector3& vecBack );

private:
	HTvoid					HT_LL_vInitList();
	HTvoid					HT_LL_hrInsertAfter( P_ATTACK_FACTOR info );
	HTRESULT				HT_LL_hrDeleteNode();
	HTvoid					HT_LL_hrDeleteAll();

public:

private:
	HT_ATTACK_NODE*		m_sAttackHead;
	HT_ATTACK_NODE*		m_sAttackTail;

	HTint				m_nAttackMaxDemage;
};
