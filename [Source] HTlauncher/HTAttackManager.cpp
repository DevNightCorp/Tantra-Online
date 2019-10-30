#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htattackmanager.h"


#define FOLLOWATTACK_NONE				0
#define FOLLOWATTACK_FOLLOWSKILL		1 
#define FOLLOWATTACK_FOLLOWDART			2

#define FOLLOWEFFECT_KEEPTIME			3.0f

#define FOLLOWMODEL_SPEED				10
#define FOLLOWMODEL_HIGHSPEED			20

//	ķ���� ID
HTint g_nCamjitterID[3] = { HT_FX_CAMJITTER_01, HT_FX_CAMJITTER_02, HT_FX_CAMJITTER_03 };

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
HTAttack::HTAttack(void)
{
	m_dwAttack_SkillType = 0;
	m_nAttack_LiveTime = GetTickCount(); //	�� Ŭ������ ����� ���� ������ ������ġ->������
	m_pFactor = HT_NULL;
	m_iAttack_FolowType = -1;
	m_bAttack_PursuitSw = HT_FALSE;
	m_byAttack_PursuitCount = 0;
	m_fAttack_EOTransValue = 0.0f;
	m_fAttack_TimeTransValue = 0.0f;
	m_fAttack_TotalTime = 0.0f;
	m_fAttack_CorrectSpeed = 0.0f;
	m_byAttack_PiercingCellCount = 0;
	for ( HTint i = 0; i < TN_MAX_TARGET_COUNT; ++i ) m_pAttack_PiercingData[i] = 0;
	m_bAttack_GoodHit = HT_FALSE;
	m_dwAttack_FollowTime = 0;
	m_iAttack_ModelSpeed = FOLLOWMODEL_SPEED;
	m_iAttack_HomerSpeed = MAX_SPEED;
}

HTAttack::~HTAttack(void)
{
	//	�� ���̵� �����
	if( m_oFollowFX.idModel > 0 )		//	�θ� / ��ô�����
	{
        g_pEngineHandler->HT_vDestroyObject( m_oFollowFX.idModel, 16 );
		m_oFollowFX.idModel = -1;
	}
	if( m_oFollowFX.idFX > 0 )		//	����Ʈ ���̵�
	{
		g_pEngineHandler->HT_hrStopSFX( m_oFollowFX.idFX );
	}

	HT_DELETE( m_pFactor );
}

//	�ʱ� ����Ÿ ����
HTvoid HTAttack::HT_vAttack_SetInitData( P_ATTACK_FACTOR info )
{
	//	ĳ���� ���� ����
	m_pFactor = HT_NULL;
	m_pFactor = new S_ATTACK_FACTOR;
    memcpy( m_pFactor, info, sizeof(S_ATTACK_FACTOR) );

	m_pFactor->byAttackSkillIDLevel = 1;
	m_dwAttack_SkillType		= 0;
	m_nAttack_Process			= ATTACKPROCESS_ATTACKPOINT;

	//	�⺻ �ȷο� Ÿ��
	m_iAttack_FolowType	= FOLLOWTYPE_NORMAL;
	//	���� �ȵǰ�
	m_bAttack_PursuitSw = HT_FALSE;
	m_byAttack_PursuitCount = 0;
	//	�ȷο찡 ���� ���ݽ� ������ ����
	m_bAttack_GoodHit = HT_TRUE;
	
	if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_PRANA )		//	���� ������ ���̸�
	{
		//	Get Target
		if( m_pFactor->dwTargetKeyID != -1 )
		{
			if( m_pFactor->dwTargetKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
				m_pFactor->vecTargetPos = g_cMainCharacter->HT_vecGetPosition();
			else
				m_pFactor->vecTargetPos = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( m_pFactor->dwTargetKeyID );
		}
		m_iAttack_FolowType	= FOLLOWTYPE_JKSHOMER;
	}

	//	�����Ӽ� ����
	if( m_pFactor->nAttackSkillID == 3162 ||		//	�Ƽ��� �����ī
		m_pFactor->nAttackSkillID == 3306 )			//	���� ���
	{
		m_bAttack_PursuitSw = HT_TRUE;
		m_iAttack_FolowType	= FOLLOWTYPE_JKSHOMER;
	}

	//	y �� ����
	m_pFactor->vecSourcePos.y += 12;
	m_pFactor->vecTargetPos.y += 12;
}

//	�κ��͸� �̿��Ͽ� ���� ���� ���´�.		A:���� ����, B:�� ����
HTfloat HTAttack::HT_fAttackGetAngle(HTvector3 A, HTvector3 B)
{
	float sp= A.x*B.x + A.z*B.z;					//	�������ϱ� -> ������ ����(����)�� �˱� ����
	float sqrt_A = (float)sqrt(A.x*A.x + A.z*A.z);	//  A ������ ���밪(����) ���ϱ� 
	float sqrt_B = (float)sqrt(B.x*B.x + B.z*B.z);	//  B ������ ���밪(����) ���ϱ� 
	if ( sqrt_A * sqrt_B < HT_EPSILON )
		return ( HT_PI );
	float cos = sp / (sqrt_A * sqrt_B);				//  ������ �̿��ؼ� ���� ���ϱ�

	HTfloat acos = acosf( cos );					//	�ڻ��ΰ��� ���Ȱ� �ٲٱ�
	float direction = A.z*B.x - B.z*A.x;			//	���� ������ ��
	if(direction < 0)								//	dirction ���̸� ���� , ���̸� ������
		acos *= -1;
	return acos;
}

//	���� ��Ʈ��
HTvoid HTAttack::HT_vAttack_Control( HTfloat fElapsedTime )
{
	switch( m_nAttack_Process )
	{
		case ATTACKPROCESS_ATTACKPOINT :
			HT_vAttack_AttackPoint();
			break;
		case ATTACKPROCESS_FOLLOWEFFET :
			HT_vAttack_AttackFollowEffect( fElapsedTime );
			break;
		default :
			break;
	}

	//	�� Ŭ������ ����� ���� ������ ������ġ->������
	HT_vAttack_LiveTimeControl();
}

//	���� ����Ʈ���� ����
HTvoid HTAttack::HT_vAttack_AttackPoint()
{
	//	���ư��� �θ�/ǥâ ����
	if( HT_IS_ITEM_DART( m_pFactor->nAttackItemID ) )
	{
		this->HT_vAttack_SetWithFollow();
		return;
	}

	//	Ȱ�� ����Ҷ�
	if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_AUTOATTACK )
	{
		if( CHTParamIDCheck::HT_bIsItemWeaponThrow( m_pFactor->nAttackItemID ) )
		{
			this->HT_vAttack_SetWithFollow();
			return;
		}
	}

	//	�׼� ��ų Ÿ���� ���´�.
	m_dwAttack_SkillType = g_pEngineHandler->HT_dwGetSkillType( m_pFactor->nAttackSkillID );

	//	�ȷο� �� �ӵ�
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
        m_iAttack_ModelSpeed = FOLLOWMODEL_HIGHSPEED;
	
	//	PC��ų���� Monster��ų���� �ľ�!
	if( SERVEROBJECT_IS_CHARACTER( m_pFactor->dwAttackKeyID ) )
	{
		if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_LONG_WITHFOLLOW ||
			m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW ||
			m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
		{
			this->HT_vAttack_SetWithFollow();				//	�ȷο찡 �ִ� ����
		}
		else
		{
			this->HT_vAttack_SetWithOutFollow();			//	�ȷο� ���� ����
		}
	}
	else
	{
		if( m_dwAttack_SkillType == HT_SKILL_TYPE_ACTION_NOCAST_LONG || 
			m_dwAttack_SkillType == HT_SKILL_TYPE_ACTION_YESCAST_LONG ||
			m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_PRANA )
		{
			this->HT_vAttack_SetWithFollow();				//	�ȷο찡 �ִ� ����
		}
		else
		{
			this->HT_vAttack_SetWithOutFollow();			//	�ȷο� ���� ����
		}
	}
}

//	���� ����Ʈ���� ����_�ȷο찡���� ���� ����
HTvoid HTAttack::HT_vAttack_SetWithOutFollow()
{
	//	�ȷο찡 ���� ���ݽ� ������ ����
	m_bAttack_GoodHit = HT_TRUE;

	//if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_SKILL )
	//{
	//	HTint iTempEffectID;
	//	m_oFollowFX.idModel = g_pEngineHandler->HT_iCreateNullModel( m_pFactor->vecTargetPos );
	//	g_pEngineHandler->HT_hrStartSFX( &iTempEffectID, m_pFactor->nAttackSkillID, HT_SFX_WHEN_IMPACT, m_oFollowFX.idModel, HT_FALSE );
	//}

	//	���ݴ�󿡰� ����� �Ұ͵�
	if( m_pFactor->dwTargetKeyID )
	{
		if( m_pFactor->nAttackType != MAINCHAR_ATTACKTYPE_PRANA )
		{
			if( m_pFactor->dwTargetKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
				g_cMainCharacter->HT_vMainChar_SetDisAttackCheck( m_pFactor->nAttackSkillID, m_pFactor->nAttackItemID, m_pFactor->nCharModelID );
			else
				g_cOtherObjectSystem->HT_vOtherObjectSystem_EffectHitAction( m_pFactor->dwTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->nAttackItemID, m_pFactor->nCharModelID, m_pFactor->dwAttackKeyID );
		}
	}

	//	���ݴ�󿡰� ���ؾ��� �׼ǵ�
	this->HT_vAttack_SetAttackPoint();
}

//	���� ����Ʈ���� ����_���� �Ÿ� ���
HTvoid HTAttack::HT_vAttack_DistanceCheck()
{
	HTint iAOE;
	//	����Ÿ���� PIERCING�϶�
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
	{
		m_byAttack_PiercingCellCount = 0;
		for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
			m_pAttack_PiercingData[i] = 0;

		//	���� ���ǵ�
		m_fAttack_CorrectSpeed = CHARACTER_SPEED_FOLLOWCORRECT*0.5f;
		//	�ȷο� �Ÿ� +Alpha ���
		g_pParamMgr->HT_bGetPCSkillAreaOfEffect( m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillIDLevel, &iAOE );
		iAOE = 10;
	}
	else
	{
		//	���� ���ǵ�
		m_fAttack_CorrectSpeed = CHARACTER_SPEED_FOLLOWCORRECT*0.75f;
		//	�ȷο� �Ÿ� +Alpha ���
		iAOE = 2;
	}

	//	�ȷο� �Ÿ� +Alpha ���
	HTfloat fx, fz;
	HTvector3	vecVector = m_pFactor->vecTargetPos - m_pFactor->vecSourcePos;
	HTfloat		fDirect = HT_fAttackGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector );
	fx = sinf( fDirect ) * ( iAOE*MAP_CELL_SIZE );
	fz = cosf( fDirect ) * ( iAOE*MAP_CELL_SIZE );
	m_pFactor->vecTargetPos.x += fx;
	m_pFactor->vecTargetPos.z += fz;

	//	���� ��ġ ����
	m_oFollowFX.vecPos = m_pFactor->vecSourcePos;
	//	��ǥ��ġ ����
	m_oFollowFX.vecTarget = m_pFactor->vecTargetPos;
	//	���� �� �Ÿ�
	HTfloat fDistance = (float)sqrt( double( ( (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) * (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) ) + ( (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) * (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) ) ) );

	//	������� ��ȭ��
	m_fAttack_EOTransValue		= 1;
	//	�ð� ��ȭ��
	m_fAttack_TimeTransValue	= 0;
	//	��ü �ð�
	m_fAttack_TotalTime			= fDistance * MAP_CELL_SIZE;
	//	�ð� ����
	m_oFollowFX.fTime = 0.0f;

	//	���ư��� Ÿ��
	switch( m_iAttack_FolowType )
	{
		case FOLLOWTYPE_NORMAL :
			break;
		case FOLLOWTYPE_JKSHOMER :
			this->HT_vAttack_Set_JKS_FlyingObject_Homer();
			break;
	}
}

// ������ �ʿ��� init �κ�
HTvoid HTAttack::HT_vAttack_Set_JKS_FlyingObject_Homer()
{
	// jks - �ʱ� �ӵ� ���� 
    // jks - �ʱ� �ӵ� ���� 
	//	�����Ӽ��϶�
	if( m_bAttack_PursuitSw )
	{
		//oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
		// get random number between (-2.0f ~ 2.0f)
		m_oFollowFX.curVel.x = 0.0f; //jks
		// get random number between (-2.0f ~ 2.0f)
		m_oFollowFX.curVel.z = 0.0f; //jks
		// get random number between (0.0f ~ 4.0f)
		m_oFollowFX.curVel.y = (rand()%2) + (rand() / (HTfloat)RAND_MAX); //jks
		//oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
	}
	//	�Ϲ����ΰ�
	else
	{
		//oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
		// get random number between (-2.0f ~ 2.0f)
		m_oFollowFX.curVel.x = 2 - ((rand()%4) + (rand() / (HTfloat)RAND_MAX)); //jks
		// get random number between (-2.0f ~ 2.0f)
		m_oFollowFX.curVel.z = 2 - ((rand()%4) + (rand() / (HTfloat)RAND_MAX)); //jks
		// get random number between (0.0f ~ 4.0f)
		m_oFollowFX.curVel.y = (rand()%2) + (rand() / (HTfloat)RAND_MAX); //jks
		//oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
	}
}

//	���� ����Ʈ���� ����_�ȷο찡 �ִ� ���� ����
HTvoid HTAttack::HT_vAttack_SetWithFollow()
{
	//	���������϶��� ������ ���� ����
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW )
		m_bAttack_GoodHit = HT_TRUE;
	//	�������� �ϴ� ���� ����
	else
        m_bAttack_GoodHit = HT_FALSE;

	//	Follow(�Ѿ�) ���
	this->HT_vAttack_DistanceCheck();

	//	�ȷο� �� �ļ�
	if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_AUTOATTACK )
	{
		if( HT_IS_ITEM_DART( m_pFactor->nAttackItemID ) )
		{
			m_oFollowFX.idModel = g_pEngineHandler->HT_iCreateFieldItem( m_pFactor->nAttackItemID, m_oFollowFX.vecPos );
		}
		else if( CHTParamIDCheck::HT_bIsItemWeaponThrow( m_pFactor->nAttackItemID ) )
		{
			m_oFollowFX.idModel = g_pEngineHandler->HT_iCreateFieldItem( HT_ITEM_ARROW_MODELID, m_oFollowFX.vecPos );
			g_pEngineHandler->HT_hrStartSFX( &m_oFollowFX.idFX, HT_FX_ARROWFOLLOW, m_oFollowFX.idModel, HT_TRUE );
		}
		//	���� üũ
        this->HT_vAttack_AttackFollow_AngleCheck();
	}
	else
	{
		//	��ų�̶� ȭ���϶��� ȭ���� ũ�������� ��Ŵ
		if( CHTParamIDCheck::HT_bIsItemWeaponThrow( m_pFactor->nAttackItemID ) &&
			m_bAttack_PursuitSw == HT_FALSE )
		{
			m_oFollowFX.idModel = g_pEngineHandler->HT_iCreateFieldItem( HT_ITEM_ARROW_MODELID, m_oFollowFX.vecPos );

			//	Ȱ�Ƽ��� ���� ���� ��ų�϶��� 
			if( m_pFactor->nAttackSkillID == 3117 )
			{
				m_fAttack_CorrectSpeed *= 1.4f;
				m_iAttack_HomerSpeed *= 1.4f;
			}
			//	Ȱ��ų�϶��� �ӵ��� �ι�� ����Ŵ
			else
			{
				m_fAttack_CorrectSpeed *= 2.0f;
				m_iAttack_HomerSpeed *= 2.0f;
			}
		}
		else
		{
			m_oFollowFX.idModel = g_pEngineHandler->HT_iCreateNullModel( m_oFollowFX.vecPos );

			//	Ȱ��ų�϶��� �ӵ��� �ι�� ����Ŵ,	�Ƽ��� �����ī
			if( m_pFactor->nAttackSkillID == 3162 )
			{
				m_fAttack_CorrectSpeed *= 1.4f;
				m_iAttack_HomerSpeed *= 1.4f;
			}
		}
		//	���� üũ
		this->HT_vAttack_AttackFollow_AngleCheck();
		g_pEngineHandler->HT_hrStartSFX( &m_oFollowFX.idFX, m_pFactor->nAttackSkillID, HT_SFX_WHEN_FOLLOW, m_oFollowFX.idModel, HT_TRUE, m_pFactor->byAttackSkillIDLevel );
	}

	//	���μ��� �ȷο�� �ѱ�
	m_nAttack_Process = ATTACKPROCESS_FOLLOWEFFET;

	//	ī�޶� ���� ���� ���ư�
	if( g_bGoAttackCamera )//rand()%10 == 0 )
	{
		if( m_pFactor->dwAttackKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
		{
			g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_FOLLOWWEAPON, HTvector3( 0, 10, 10) , 1, 0.75f);
			g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_FOLLOWWEAPON, HTvector3( 0, 100, 100) , 1, 0.75f);
		}
	}

	//	�ȷο� ���ݽ� ���ư� �ð��� ����
	m_dwAttack_FollowTime = timeGetTime();
}

//	�ȷο�
HTvoid HTAttack::HT_vAttack_AttackFollowEffect( HTfloat fElapsedTime )
{
	//	��ǥ�� �ɸ����� üũ
    this->HT_vAttack_AttackFollow_TargetCheck();

	//	���ư��� Ÿ��
	switch( m_iAttack_FolowType )
	{
		case FOLLOWTYPE_NORMAL :
			this->HT_vAttack_AttackFollowEffectGo( fElapsedTime );
			break;
		case FOLLOWTYPE_JKSHOMER :
			this->HT_vAttack_AttackFollow_FlyingObject_JKS_Homer( fElapsedTime );
			break;
	}
	
	//	���� üũ
	this->HT_vAttack_AttackFollow_AngleCheck();
	//	�� �̵�
	if ( m_oFollowFX.idModel > 0 )
		g_pEngineHandler->HT_hrMoveObject( m_oFollowFX.idModel, m_oFollowFX.vecPos );
	//	�ȷο� ����Ʈ_üũ
	this->HT_vAttack_AttackFollowCheck();
}

//	�ȷο� ����Ʈ go
HTvoid HTAttack::HT_vAttack_AttackFollowEffectGo( HTfloat fElapsedTime )
{
	if( fElapsedTime <= HT_EPSILON )
		return;

	m_fAttack_TimeTransValue += ( fElapsedTime * m_iAttack_ModelSpeed * MAP_CELL_SIZE * m_fAttack_CorrectSpeed );

	m_fAttack_EOTransValue = 1 - ( m_fAttack_TimeTransValue/m_fAttack_TotalTime );
	if( m_fAttack_EOTransValue < 0 )
		m_fAttack_EOTransValue = 0;

	m_oFollowFX.vecPos = ( m_pFactor->vecSourcePos*m_fAttack_EOTransValue ) + ( m_pFactor->vecTargetPos * (1-m_fAttack_EOTransValue) );
}

//	jks - code for homing flying object.
HTvoid HTAttack::HT_vAttack_AttackFollow_FlyingObject_JKS_Homer( HTfloat fElapsedTime )
{
	//	���̰��
	m_oFollowFX.fTime += fElapsedTime;
	{
		//oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
		HTvector3   instVelocity;					// new code//////////////////
		HTvector3   vectorToTarget;					// jks - vector from source to destination
        HTvector3   temp;							// jks - temporary vector

		//	�������� ��û���� ���� Ÿ�������� �ǽð� ����
		if( m_pFactor->dwTargetKeyID != -1 )
		{
			if( m_pFactor->dwTargetKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
			{
				m_oFollowFX.vecTarget = g_cMainCharacter->HT_vecGetPosition();
			}
			else
			{
				m_oFollowFX.vecTarget = g_cOtherObjectSystem->HT_vecOtherObjectSystem_GetCurCoordPosFromKeyID( m_pFactor->dwTargetKeyID );
			}
			m_oFollowFX.vecTarget.y += 12;
		}
		
        // jks - get direction(from source to dest.) vector 
        CHTVector::HT_pvecVec3Subtract(&vectorToTarget, &m_oFollowFX.vecTarget, &m_oFollowFX.vecPos);
		CHTVector::HT_pvecVec3Normalize( &vectorToTarget, &vectorToTarget );
        // jks - velocity correction 
        CHTVector::HT_pvecVec3Scale(&temp, &m_oFollowFX.curVel,(VECTOR_CORRECTION_FACTOR-1));
        CHTVector::HT_pvecVec3Add(&temp, &temp, &vectorToTarget);
        CHTVector::HT_pvecVec3Scale(&m_oFollowFX.curVel, &temp, (1.0f/VECTOR_CORRECTION_FACTOR));
		#if 0
        // jks - apply speed 
        //CHTVector::HT_pvecVec3Scale(&m_oFollowFX.curVel, &m_oFollowFX.curVel, (MAX_SPEED));
        // jks - update flying object position
        //CHTVector::HT_pvecVec3Add(&m_oFollowFX.vecPos, &m_oFollowFX.vecPos, &m_oFollowFX.curVel);
		#else
		// new code//////////////////
        CHTVector::HT_pvecVec3Scale(&instVelocity, &m_oFollowFX.curVel, (fElapsedTime * m_iAttack_HomerSpeed));
        CHTVector::HT_pvecVec3Add(&m_oFollowFX.vecPos, &m_oFollowFX.vecPos, &instVelocity);
		#endif
		//oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
	}
}

//	����Ÿ���� PIERCING�϶� �� ��ǥ�� �ɸ��� �𸶴� ������ �ø�
HTvoid HTAttack::HT_vAttack_AttackFollow_TargetCheck()
{
	//	üũ���ؾߵɶ�
	if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_PRANA ||						//	���� ���ƿ��°��϶�
		m_pFactor->dwAttackKeyID != g_cMainCharacter->HT_iMainChar_GetKeyID() ||	//	Ÿ���� ���϶�
		m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW )		//	�ȷο찡 �ִ� ��ü ���� �����϶�
		return;

	HTint iTargetKeyID;
	//	����ǥ�� ĳ���� Ű�Ƶ� �˾ƿ´�_OtherChar �˻�
	iTargetKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyIDFromCellForPiercing( m_dwAttack_SkillType, m_oFollowFX.vecPos, m_pAttack_PiercingData );
	if( iTargetKeyID > 0 )
	{
		//	�Ǿ���϶��� ��� �����ϰ�
		if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
		{
			g_cOtherObjectSystem->HT_vOtherObjectSystem_EffectHitAction( iTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->nAttackItemID, m_pFactor->nCharModelID, m_pFactor->dwAttackKeyID );
			m_pAttack_PiercingData[m_byAttack_PiercingCellCount] = iTargetKeyID;
			m_byAttack_PiercingCellCount++;
			//	�ȷο� ���ݽ� ������ �¾Ҵ��� ����
			m_bAttack_GoodHit = HT_TRUE;
		}
		else
		{
			//	�ȷο� ����
			m_fAttack_EOTransValue = 0;
			//	�ȷο� ���ݽ� ������ �¾Ҵ��� ����
			m_bAttack_GoodHit = HT_TRUE;
		}
	}
}

//	���� üũ
HTvoid HTAttack::HT_vAttack_AttackFollow_AngleCheck()
{
	// Ȱ �����Դϴ�~
	HTvector3 vecY( 0.0f, 1.0f, 0.0f );				
	HTvector3 vecU, vecV, vecN;
	vecU = m_pFactor->vecTargetPos - m_pFactor->vecSourcePos;
	CHTVector::HT_pvecVec3Normalize( &vecU, &vecU );

	CHTVector::HT_pvecVec3Cross( &vecN, &vecY, &vecU );
	CHTVector::HT_pvecVec3Normalize( &vecN, &vecN );

	CHTVector::HT_pvecVec3Cross( &vecV, &vecN, &vecU );
	CHTVector::HT_pvecVec3Normalize( &vecV, &vecV );

	HTfloat fRadianX, fRadianY, fRadianZ;

	fRadianX = asinf( -vecN.y );
	if ( fRadianX < HT_PIDIV2 )
	{
		if ( fRadianX > -HT_PIDIV2 )
		{
			fRadianY = atan2f( vecN.x, vecN.z );
			fRadianZ = atan2f( vecU.y, vecV.y );
			//fRadianZ = 0.0f;
		}
		else
		{
			fRadianY = -atan2f( -vecV.x, vecU.x );
			fRadianZ = 0.0f;
		}
	}
	else
	{
		fRadianY = atan2f( -vecV.x, vecU.x );
		fRadianZ = 0.0f;
	}

	HTfloat fDegreeRotationX = HT_RADIAN_TO_DEGREE( fRadianX );
	HTfloat fDegreeRotationY = HT_RADIAN_TO_DEGREE( fRadianY );
	HTfloat fDegreeRotationZ = HT_RADIAN_TO_DEGREE( fRadianZ );
	g_pEngineHandler->HT_hrRotateObject( m_oFollowFX.idModel, HTvector3( fDegreeRotationX, fDegreeRotationY, fDegreeRotationZ ) );
}

//	�ȷο� ����Ʈ_üũ
HTvoid HTAttack::HT_vAttack_AttackFollowCheck()
{
	HTbool bType = HT_FALSE;
	//	���ư��� Ÿ��
	switch( m_iAttack_FolowType )
	{
		case FOLLOWTYPE_NORMAL :
			if( m_fAttack_EOTransValue == 0 )
				bType = HT_TRUE;
			break;
		case FOLLOWTYPE_JKSHOMER :
			//	TimeOver
			if( m_oFollowFX.fTime > FOLLOWEFFECT_KEEPTIME )
                bType = HT_TRUE;
			//	�����߳�?
			if( m_pFactor->nAttackType != MAINCHAR_ATTACKTYPE_PRANA )
			{
				if( m_bAttack_GoodHit )
					bType = HT_TRUE;
			}
			break;
	}

    if( bType )
	{
		//	�� �� �����
		if ( m_oFollowFX.idModel > 0 )
		{
			g_pEngineHandler->HT_vDestroyObject( m_oFollowFX.idModel, 17 );
			m_oFollowFX.idModel = -1;
		}

		if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_SKILL || m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_PRANA )
		{
			g_pEngineHandler->HT_hrStopSFX( m_oFollowFX.idFX );
			m_oFollowFX.idFX = -1;
		}

		//	������ �¾��� ��
		if( m_bAttack_GoodHit )
		{
			if( m_dwAttack_SkillType != HT_PCSKILLTYPE_ACTION_PIERCING &&		//	����Ÿ���� PIERCING�϶��� �������� �ʴ´�.
				m_pFactor->nAttackType != MAINCHAR_ATTACKTYPE_PRANA )			//	����Ÿ���� PRANA�϶��� �������� �ʴ´�.
			{        
				//	���ݴ���� Object �϶�
				if( m_pFactor->dwTargetKeyID )
				{
					if( m_pFactor->dwTargetKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
					{
						if( m_pFactor->nAttackType != MAINCHAR_ATTACKTYPE_PRANA )
							g_cMainCharacter->HT_vMainChar_SetDisAttackCheck( m_pFactor->nAttackSkillID, m_pFactor->nAttackItemID, m_pFactor->nCharModelID );
					}
					else
					{
						g_cOtherObjectSystem->HT_vOtherObjectSystem_EffectHitAction( m_pFactor->dwTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->nAttackItemID, m_pFactor->nCharModelID, m_pFactor->dwAttackKeyID );
					}
				}
				//	���������϶�
				else
				{
					HTint iTempEffectID;
					g_pEngineHandler->HT_hrStartSFX( &iTempEffectID, m_pFactor->nAttackSkillID, HT_SFX_WHEN_IMPACT, m_oFollowFX.idModel, HT_FALSE );
				}
			}
		}
		//	���� �¾����� ���ؾ� �� �׼ǵ�
		this->HT_vAttack_SetAttackPoint();
	}
}

//	���� �¾����� ���ؾ� �� �׼ǵ�
HTvoid HTAttack::HT_vAttack_SetAttackPoint()
{
	//	�����ڰ� ����ĳ�����϶� ������ ������ �˷��ش�.
	if( m_pFactor->dwAttackKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		//	������ �¾��� ��
        this->HT_vNetWork_CSP_MSG_Attack();
	}

	//----------Ÿ�� ���� Ʋ���ֱ�----------//
	if( SERVEROBJECT_IS_CHARACTER( m_pFactor->dwAttackKeyID ) )
	{
		if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_AUTOATTACK ||
			m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_SHORT )
		{
			g_pEngineHandler->HT_hrPlayAttackOKSound( m_pFactor->byTribe, m_pFactor->nAttackItemID );
		}
	}

	//	���� �� ����Ʈ Ʋ���ش�
	if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_PRANA )
	{
		//	Get Target ModelID
		HTint iTargetModelID;
		if( m_pFactor->dwTargetKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
			iTargetModelID = g_cMainCharacter->HT_vMainChar_GetModelID();
		else
			iTargetModelID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( m_pFactor->dwTargetKeyID );
		
		if( SERVEROBJECT_IS_MONSTER( m_pFactor->dwTargetKeyID ) )
		{
			HTint nTempID;
			g_pEngineHandler->HT_hrStartSFX( &nTempID, g_pEngineHandler->HT_dwConvrtMonsterID2MonFXID(m_pFactor->nAttackItemID), HT_SFX_WHEN_IMPACT, iTargetModelID, HT_FALSE );
		}
	}

	//	�� ���� Ŭ���� ����Ʈ���� ����
	m_nAttack_Process = ATTACKPROCESS_DAETH;
}

//	�� Ŭ������ ����� ���� ������ ������ġ->������
HTvoid HTAttack::HT_vAttack_LiveTimeControl()
{
	DWORD dwPassTime = GetTickCount();
	if( dwPassTime > m_nAttack_LiveTime+10000 )
	{
		m_nAttack_Process = ATTACKPROCESS_DAETH;
	}	
}



//-------------------------------------------------------------
//			������ ���� ��û��
//-------------------------------------------------------------
HTvoid HTAttack::HT_vNetWork_CSP_MSG_Attack()
{
	//	���÷��� �����϶��� üũ
	if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_SKILL )
	{
		g_pParamMgr->HT_bGetPCSkillEffect1ID( m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillIDLevel, &m_iAttck_SplashIndex );
		if( m_iAttck_SplashIndex == 2  ||
			m_iAttck_SplashIndex == 14 ||
			m_iAttck_SplashIndex == 15 ||
			m_iAttck_SplashIndex == 16 ||
			m_iAttck_SplashIndex == 17 )
		{
			m_iAttck_SplashIndex = 1;
		}
		else
		{
			m_iAttck_SplashIndex = 0;
		}
	}

	//	�������� �϶��� ���÷��� �϶�
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHOUTFOLLOW ||
		m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW ||
		m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING ||
		m_iAttck_SplashIndex == 1 )
	{
		//	������ ��ų(����) ���� ��û
		this->HT_vNetWork_CSP_Cast_Area_Cast();
	}
	//	�������� �ƴҶ�
	else
	{
		this->HT_vNetWork_CSP_Cast_Unit_Cast( (short)m_pFactor->nAttackSkillID, (short)m_pFactor->dwAttackKeyID, (short)m_pFactor->dwTargetKeyID, m_pFactor->vecTargetPos );
	}
}

//	������ ��ų(�ܼ�) ���� ��û
HTvoid HTAttack::HT_vNetWork_CSP_Cast_Unit_Cast( short snAttackSkillID, short snAttackerKeyID, short snTargetKeyID, HTvector3 vecTargetPos )
{
	//	�� ��ġ
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( vecTargetPos, crdCell );
	HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	PS_CSP_CAST_UNIT_SKILL info = HT_NULL;
    info = new S_CSP_CAST_UNIT_SKILL;

	memset( info, 0, sizeof(S_CSP_CAST_UNIT_SKILL) );

    info->snRes = 0;
	info->snSkillID		= snAttackSkillID;		// cast�� skill ID		
	info->snCasterKeyID = snAttackerKeyID;		// Caster handle
	info->kTarget.snKeyID = snTargetKeyID;		// Target handle
	//	ȭ���� �����ϰ� ������ �ʱⰪ�� �������� ���� �����ϱ� ����
	info->snPackCount	= -1;

	info->snCasterX		= pPt.x;				// Caster�� ���� x ��ǥ
	info->snCasterZ		= pPt.y;				// Caster�� ���� y ��ǥ
	info->snMapX		= crdCell.x;
	info->snMapZ		= crdCell.y;

	//	�ȷο� ���ݽ� ���ư� �ð��� ����
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_LONG_WITHFOLLOW || 
		m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW || 
		m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING ||
		CHTParamIDCheck::HT_bIsItemWeaponThrow( m_pFactor->nAttackItemID ) )
	{
		if( m_dwAttack_FollowTime != 0 )
		{
			info->dwFireHitGapTime = timeGetTime() - m_dwAttack_FollowTime;
		}
	}

	g_pNetWorkMgr->RequestSkillCastUnitSkill( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Skill_Cast_Unit_Skill : %d, %d", info->snSkillID , info->kTarget.snKeyID );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	������ ��ų(����) ���� ��û
HTvoid HTAttack::HT_vNetWork_CSP_Cast_Area_Cast()
{
	//	�� ��ġ fors_debug Ⱥ������Ŀ��ĵط�
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_pFactor->vecTargetPos, crdCell );
    HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	HTint	iElement[TN_MAX_TARGET_COUNT];
	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )		iElement[i] = 0;
	//	����Ÿ���� PIERCING�϶�	
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
		memcpy( &iElement, &m_pAttack_PiercingData, sizeof(int)*TN_MAX_TARGET_COUNT );
	else
	{
		HTbyte byGoodType;
		g_pParamMgr->HT_bGetPCSkillType( m_pFactor->nAttackSkillID, 1, &byGoodType );

		HTint iAOE;
		if( m_iAttck_SplashIndex == 1 )
		{
			//	���÷��� ���������� ���� ���� �������� �Ծ�� �Ҿִ� ���ڽ��̱� ������
			iElement[0] = (short)m_pFactor->dwTargetKeyID;		// Target handle
			iAOE = 4;
		}
		else
		{
            g_pParamMgr->HT_bGetPCSkillAreaOfEffect( m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillIDLevel, &iAOE );
		}

        g_cOtherObjectSystem->HT_vOtherObjectSystem_GetTerritoryArea( m_pFactor->vecTargetPos, (HTfloat)(iAOE*MAP_CELL_SIZE), m_pFactor->nAttackSkillID, m_pFactor->nCharModelID, m_pFactor->dwAttackKeyID, byGoodType, iElement );
	}

	PS_CSP_CAST_AREA_SKILL info = HT_NULL;
    info = new S_CSP_CAST_AREA_SKILL;

	memset( info, 0, sizeof(S_CSP_CAST_AREA_SKILL) );

	info->snRes = 0;
	info->snSkillID		= (short)m_pFactor->nAttackSkillID;		// cast�� skill ID		
	info->snCasterKeyID = (short)m_pFactor->dwAttackKeyID;		// Caster handle

	info->snCasterX		= pPt.x;									// Caster�� ���� x ��ǥ
	info->snCasterZ		= pPt.y;									// Caster�� ���� y ��ǥ
	info->snMapX		= crdCell.x;							// Map�� ���� x ��ǥ
	info->snMapZ		= crdCell.y;							// Map�� ���� y ��ǥ

	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
	{
        info->krgTarget[i].snKeyID = iElement[i]; //this is good right
     //    info->krgTarget[i].snKeyID = -12323948;
	//	 info->krgTarget[i].iAffection=-1329230230;
	//	 info->krgTarget[i].iDamage=-18281291l;
	}

	//	�ȷο� ���ݽ� ���ư� �ð��� ����
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_LONG_WITHFOLLOW || 
		m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW || 
		m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING ||
		CHTParamIDCheck::HT_bIsItemWeaponThrow( m_pFactor->nAttackItemID ) )
	{
		if( m_dwAttack_FollowTime != 0 )
		{
			info->dwFireHitGapTime = timeGetTime() - m_dwAttack_FollowTime;
		}
	}

	g_pNetWorkMgr->RequestSkillCastAreaSkill( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Skill_Cast_Area_Skill:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
	//	info->krgTarget[0].snKeyID, info->krgTarget[1].snKeyID, info->krgTarget[2].snKeyID, info->krgTarget[3].snKeyID, info->krgTarget[4].snKeyID,
	//	info->krgTarget[5].snKeyID, info->krgTarget[6].snKeyID, info->krgTarget[7].snKeyID, info->krgTarget[8].snKeyID, info->krgTarget[9].snKeyID,
	//	info->krgTarget[10].snKeyID, info->krgTarget[11].snKeyID, info->krgTarget[12].snKeyID, info->krgTarget[13].snKeyID, info->krgTarget[14].snKeyID,
	//	info->krgTarget[15].snKeyID );
	//HT_g_vLogFile( g_DebugingFont[g_DebugingFont_Count-1] );
	//HT_g_vLogFile( "\n" );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}



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
HTAttackManager::HTAttackManager()
{
	m_nAttackMaxDemage = 0;
	HT_LL_vInitList();
}

HTAttackManager::~HTAttackManager()
{
	HT_DELETE( m_sAttackHead );
	HT_DELETE( m_sAttackTail );
}

//	���� Ŭ���� ����
HTvoid HTAttackManager::HT_vAttackMgr_Create( P_ATTACK_FACTOR info )
{
	//----------LL ����Ÿ ����-��� �ٷ� �ڿ�---------//
	HT_LL_hrInsertAfter( info );
}

//	���� Ŭ���� ��Ʈ��
HTvoid HTAttackManager::HT_vAttackMgr_Control( HTfloat fElapsedTime )
{
	//-----NPC ��忡�� üũ-----//
	HT_ATTACK_NODE *t;
	
    t = m_sAttackHead->next;
	while( t != m_sAttackTail )
	{
		t->cAttack.HT_vAttack_Control( fElapsedTime );
        t = t->next;
	}
	//----------LL ����Ÿ �����---------//
	HT_LL_hrDeleteNode();
}

//	��ü ���� ����Ʈ ����
HTvoid HTAttackManager::HT_vAttackMgr_AllDelete()
{
	//----------LL ����Ÿ ���� �����---------//
	//HT_LL_hrDeleteAll();

	m_nAttackMaxDemage = 0;
}

//----------��ũ�� ����Ʈ ������ �κ�---------//
//----------LL �ʱ�ȭ---------//
HTvoid HTAttackManager::HT_LL_vInitList()
{
	m_sAttackHead = NULL;
	m_sAttackTail = NULL;

	m_sAttackHead = new HT_ATTACK_NODE;
	m_sAttackTail = new HT_ATTACK_NODE;

	m_sAttackHead->next = m_sAttackTail;
	m_sAttackTail->next = m_sAttackTail;
}

//----------LL ����Ÿ ����-��� �ٷ� �ڿ�---------//
HTvoid HTAttackManager::HT_LL_hrInsertAfter( P_ATTACK_FACTOR info )
{
    HT_ATTACK_NODE *s;
	s = NULL;
	s = new HT_ATTACK_NODE;
	s->cAttack.HT_vAttack_SetInitData( info );
	s->next = m_sAttackHead->next;
	m_sAttackHead->next = s;
}

//----------LL ����Ÿ �����---------//
HTRESULT HTAttackManager::HT_LL_hrDeleteNode()
{
	HT_ATTACK_NODE *s;
	HT_ATTACK_NODE *p;

	p = m_sAttackHead;
	s = p->next;
	while( s->cAttack.m_nAttack_Process != ATTACKPROCESS_DAETH && s != m_sAttackTail )
	{
		p = p->next;
		s = p->next;
	}

	if( s != m_sAttackTail )
	{
		p->next = s->next;
		HT_DELETE( s );
		return HT_TRUE;
	}
	else
		return HT_FALSE;
}

//----------LL ����Ÿ ���� �����---------//
HTvoid HTAttackManager::HT_LL_hrDeleteAll()
{
	HT_ATTACK_NODE *s;
	HT_ATTACK_NODE *t;
	
	t = m_sAttackHead->next;
	while( t != m_sAttackTail )
	{
		s = t;
		t = t->next;
		HT_DELETE( s );
	}

	m_sAttackHead->next = m_sAttackTail;
}

//	����ĳ���� �ȷο� ���� ��ġ�� �޾ƿ�
HTRESULT HTAttackManager::HT_hrAttackMgr_GetFollowModel( HTvector3& vecFront, HTvector3& vecBack )
{
	//-----NPC ��忡�� üũ-----//
	HT_ATTACK_NODE *t;
	
    t = m_sAttackHead->next;
	while( t != m_sAttackTail )
	{
		if( t->cAttack.m_pFactor->dwAttackKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
		{
			if( t->cAttack.m_nAttack_Process == ATTACKPROCESS_FOLLOWEFFET )
			{
				vecFront	= t->cAttack.m_oFollowFX.vecTarget;
				vecBack		= t->cAttack.m_oFollowFX.vecPos;
				return HT_OK;
			}
			else
			{
				return HT_FAIL;
			}
		}
        t = t->next;
	}

	return HT_FAIL;
}
