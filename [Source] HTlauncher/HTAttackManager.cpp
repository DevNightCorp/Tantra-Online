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

//	캠지터 ID
HTint g_nCamjitterID[3] = { HT_FX_CAMJITTER_01, HT_FX_CAMJITTER_02, HT_FX_CAMJITTER_03 };

//----------------------------------------------------------------------------//
//	Class 이름	: HTAttack
//
//	Class 설명 	: 
//		- 각 Object의 전투 명령을 수행한다.
//
//	작성자		:
//		- 20032/11/25, Created by Jung Eui Kyu
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//
HTAttack::HTAttack(void)
{
	m_dwAttack_SkillType = 0;
	m_nAttack_LiveTime = GetTickCount(); //	이 클래스를 지우기 위한 마지막 보안장치->딜레이
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
	//	모델 아이디 지우기
	if( m_oFollowFX.idModel > 0 )		//	널모델 / 투척무기용
	{
        g_pEngineHandler->HT_vDestroyObject( m_oFollowFX.idModel, 16 );
		m_oFollowFX.idModel = -1;
	}
	if( m_oFollowFX.idFX > 0 )		//	이펙트 아이디
	{
		g_pEngineHandler->HT_hrStopSFX( m_oFollowFX.idFX );
	}

	HT_DELETE( m_pFactor );
}

//	초기 데이타 셋팅
HTvoid HTAttack::HT_vAttack_SetInitData( P_ATTACK_FACTOR info )
{
	//	캐릭터 정보 셋팅
	m_pFactor = HT_NULL;
	m_pFactor = new S_ATTACK_FACTOR;
    memcpy( m_pFactor, info, sizeof(S_ATTACK_FACTOR) );

	m_pFactor->byAttackSkillIDLevel = 1;
	m_dwAttack_SkillType		= 0;
	m_nAttack_Process			= ATTACKPROCESS_ATTACKPOINT;

	//	기본 팔로우 타입
	m_iAttack_FolowType	= FOLLOWTYPE_NORMAL;
	//	유도 안되게
	m_bAttack_PursuitSw = HT_FALSE;
	m_byAttack_PursuitCount = 0;
	//	팔로우가 없는 공격시 무조건 적중
	m_bAttack_GoodHit = HT_TRUE;
	
	if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_PRANA )		//	프라나 빨리는 것이면
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

	//	유도속성 셋팅
	if( m_pFactor->nAttackSkillID == 3162 ||		//	아수라 프라니카
		m_pFactor->nAttackSkillID == 3306 )			//	데바 라라마
	{
		m_bAttack_PursuitSw = HT_TRUE;
		m_iAttack_FolowType	= FOLLOWTYPE_JKSHOMER;
	}

	//	y 값 보정
	m_pFactor->vecSourcePos.y += 12;
	m_pFactor->vecTargetPos.y += 12;
}

//	두벡터를 이용하여 라디안 값을 얻어온다.		A:기준 벡터, B:비교 벡터
HTfloat HTAttack::HT_fAttackGetAngle(HTvector3 A, HTvector3 B)
{
	float sp= A.x*B.x + A.z*B.z;					//	내적구하기 -> 벡터의 관계(각도)를 알기 위해
	float sqrt_A = (float)sqrt(A.x*A.x + A.z*A.z);	//  A 벡터의 절대값(길이) 구하기 
	float sqrt_B = (float)sqrt(B.x*B.x + B.z*B.z);	//  B 벡터의 절대값(길이) 구하기 
	if ( sqrt_A * sqrt_B < HT_EPSILON )
		return ( HT_PI );
	float cos = sp / (sqrt_A * sqrt_B);				//  세값을 이용해서 각도 구하기

	HTfloat acos = acosf( cos );					//	코사인값을 라디안값 바꾸기
	float direction = A.z*B.x - B.z*A.x;			//	왼쪽 오른쪽 비교
	if(direction < 0)								//	dirction 음이면 왼쪽 , 양이면 오른쪽
		acos *= -1;
	return acos;
}

//	공격 컨트롤
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

	//	이 클래스를 지우기 위한 마지막 보안장치->딜레이
	HT_vAttack_LiveTimeControl();
}

//	공격 포인트에서 할일
HTvoid HTAttack::HT_vAttack_AttackPoint()
{
	//	날아가는 널모델/표창 생성
	if( HT_IS_ITEM_DART( m_pFactor->nAttackItemID ) )
	{
		this->HT_vAttack_SetWithFollow();
		return;
	}

	//	활을 사용할때
	if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_AUTOATTACK )
	{
		if( CHTParamIDCheck::HT_bIsItemWeaponThrow( m_pFactor->nAttackItemID ) )
		{
			this->HT_vAttack_SetWithFollow();
			return;
		}
	}

	//	액션 스킬 타입을 얻어온다.
	m_dwAttack_SkillType = g_pEngineHandler->HT_dwGetSkillType( m_pFactor->nAttackSkillID );

	//	팔로우 모델 속도
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
        m_iAttack_ModelSpeed = FOLLOWMODEL_HIGHSPEED;
	
	//	PC스킬인지 Monster스킬인지 파악!
	if( SERVEROBJECT_IS_CHARACTER( m_pFactor->dwAttackKeyID ) )
	{
		if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_LONG_WITHFOLLOW ||
			m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW ||
			m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
		{
			this->HT_vAttack_SetWithFollow();				//	팔로우가 있는 공격
		}
		else
		{
			this->HT_vAttack_SetWithOutFollow();			//	팔로우 없이 공격
		}
	}
	else
	{
		if( m_dwAttack_SkillType == HT_SKILL_TYPE_ACTION_NOCAST_LONG || 
			m_dwAttack_SkillType == HT_SKILL_TYPE_ACTION_YESCAST_LONG ||
			m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_PRANA )
		{
			this->HT_vAttack_SetWithFollow();				//	팔로우가 있는 공격
		}
		else
		{
			this->HT_vAttack_SetWithOutFollow();			//	팔로우 없이 공격
		}
	}
}

//	공격 포인트에서 할일_팔로우가없는 공격 셋팅
HTvoid HTAttack::HT_vAttack_SetWithOutFollow()
{
	//	팔로우가 없는 공격시 무조건 적중
	m_bAttack_GoodHit = HT_TRUE;

	//if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_SKILL )
	//{
	//	HTint iTempEffectID;
	//	m_oFollowFX.idModel = g_pEngineHandler->HT_iCreateNullModel( m_pFactor->vecTargetPos );
	//	g_pEngineHandler->HT_hrStartSFX( &iTempEffectID, m_pFactor->nAttackSkillID, HT_SFX_WHEN_IMPACT, m_oFollowFX.idModel, HT_FALSE );
	//}

	//	공격대상에게 해줘야 할것들
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

	//	공격대상에게 취해야할 액션들
	this->HT_vAttack_SetAttackPoint();
}

//	공격 포인트에서 할일_공격 거리 계산
HTvoid HTAttack::HT_vAttack_DistanceCheck()
{
	HTint iAOE;
	//	공격타입이 PIERCING일때
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
	{
		m_byAttack_PiercingCellCount = 0;
		for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
			m_pAttack_PiercingData[i] = 0;

		//	보정 스피드
		m_fAttack_CorrectSpeed = CHARACTER_SPEED_FOLLOWCORRECT*0.5f;
		//	팔로우 거리 +Alpha 계산
		g_pParamMgr->HT_bGetPCSkillAreaOfEffect( m_pFactor->nAttackSkillID, m_pFactor->byAttackSkillIDLevel, &iAOE );
		iAOE = 10;
	}
	else
	{
		//	보정 스피드
		m_fAttack_CorrectSpeed = CHARACTER_SPEED_FOLLOWCORRECT*0.75f;
		//	팔로우 거리 +Alpha 계산
		iAOE = 2;
	}

	//	팔로우 거리 +Alpha 계산
	HTfloat fx, fz;
	HTvector3	vecVector = m_pFactor->vecTargetPos - m_pFactor->vecSourcePos;
	HTfloat		fDirect = HT_fAttackGetAngle( HTvector3( 0.0f, 0.0f, 1.0f ), vecVector );
	fx = sinf( fDirect ) * ( iAOE*MAP_CELL_SIZE );
	fz = cosf( fDirect ) * ( iAOE*MAP_CELL_SIZE );
	m_pFactor->vecTargetPos.x += fx;
	m_pFactor->vecTargetPos.z += fz;

	//	시작 위치 셋팅
	m_oFollowFX.vecPos = m_pFactor->vecSourcePos;
	//	목표위치 셋팅
	m_oFollowFX.vecTarget = m_pFactor->vecTargetPos;
	//	공격 갈 거리
	HTfloat fDistance = (float)sqrt( double( ( (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) * (m_pFactor->vecTargetPos.x - m_oFollowFX.vecPos.x) ) + ( (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) * (m_pFactor->vecTargetPos.z - m_oFollowFX.vecPos.z) ) ) );

	//	상대적인 변화량
	m_fAttack_EOTransValue		= 1;
	//	시간 변화량
	m_fAttack_TimeTransValue	= 0;
	//	전체 시간
	m_fAttack_TotalTime			= fDistance * MAP_CELL_SIZE;
	//	시간 셋팅
	m_oFollowFX.fTime = 0.0f;

	//	날아가는 타입
	switch( m_iAttack_FolowType )
	{
		case FOLLOWTYPE_NORMAL :
			break;
		case FOLLOWTYPE_JKSHOMER :
			this->HT_vAttack_Set_JKS_FlyingObject_Homer();
			break;
	}
}

// 생성시 필요한 init 부분
HTvoid HTAttack::HT_vAttack_Set_JKS_FlyingObject_Homer()
{
	// jks - 초기 속도 설정 
    // jks - 초기 속도 설정 
	//	유도속성일때
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
	//	일반적인것
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

//	공격 포인트에서 할일_팔로우가 있는 공격 셋팅
HTvoid HTAttack::HT_vAttack_SetWithFollow()
{
	//	범위마법일때는 무조건 성공 판정
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW )
		m_bAttack_GoodHit = HT_TRUE;
	//	나머지는 일단 실패 판정
	else
        m_bAttack_GoodHit = HT_FALSE;

	//	Follow(총알) 계산
	this->HT_vAttack_DistanceCheck();

	//	팔로우 모델 셍성
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
		//	각도 체크
        this->HT_vAttack_AttackFollow_AngleCheck();
	}
	else
	{
		//	스킬이라도 화살일때는 화살을 크리에이터 시킴
		if( CHTParamIDCheck::HT_bIsItemWeaponThrow( m_pFactor->nAttackItemID ) &&
			m_bAttack_PursuitSw == HT_FALSE )
		{
			m_oFollowFX.idModel = g_pEngineHandler->HT_iCreateFieldItem( HT_ITEM_ARROW_MODELID, m_oFollowFX.vecPos );

			//	활아수라 관통 나스 스킬일때는 
			if( m_pFactor->nAttackSkillID == 3117 )
			{
				m_fAttack_CorrectSpeed *= 1.4f;
				m_iAttack_HomerSpeed *= 1.4f;
			}
			//	활스킬일때는 속도를 두배로 향상시킴
			else
			{
				m_fAttack_CorrectSpeed *= 2.0f;
				m_iAttack_HomerSpeed *= 2.0f;
			}
		}
		else
		{
			m_oFollowFX.idModel = g_pEngineHandler->HT_iCreateNullModel( m_oFollowFX.vecPos );

			//	활스킬일때는 속도를 두배로 향상시킴,	아수라 프라니카
			if( m_pFactor->nAttackSkillID == 3162 )
			{
				m_fAttack_CorrectSpeed *= 1.4f;
				m_iAttack_HomerSpeed *= 1.4f;
			}
		}
		//	각도 체크
		this->HT_vAttack_AttackFollow_AngleCheck();
		g_pEngineHandler->HT_hrStartSFX( &m_oFollowFX.idFX, m_pFactor->nAttackSkillID, HT_SFX_WHEN_FOLLOW, m_oFollowFX.idModel, HT_TRUE, m_pFactor->byAttackSkillIDLevel );
	}

	//	프로세스 팔로우로 넘김
	m_nAttack_Process = ATTACKPROCESS_FOLLOWEFFET;

	//	카메라가 모델을 따라 날아감
	if( g_bGoAttackCamera )//rand()%10 == 0 )
	{
		if( m_pFactor->dwAttackKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
		{
			g_cCamera.HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_FOLLOWWEAPON, HTvector3( 0, 10, 10) , 1, 0.75f);
			g_cCamera.HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_FOLLOWWEAPON, HTvector3( 0, 100, 100) , 1, 0.75f);
		}
	}

	//	팔로우 공격시 날아간 시간을 저장
	m_dwAttack_FollowTime = timeGetTime();
}

//	팔로우
HTvoid HTAttack::HT_vAttack_AttackFollowEffect( HTfloat fElapsedTime )
{
	//	좌표에 걸리는지 체크
    this->HT_vAttack_AttackFollow_TargetCheck();

	//	날아가는 타입
	switch( m_iAttack_FolowType )
	{
		case FOLLOWTYPE_NORMAL :
			this->HT_vAttack_AttackFollowEffectGo( fElapsedTime );
			break;
		case FOLLOWTYPE_JKSHOMER :
			this->HT_vAttack_AttackFollow_FlyingObject_JKS_Homer( fElapsedTime );
			break;
	}
	
	//	각도 체크
	this->HT_vAttack_AttackFollow_AngleCheck();
	//	모델 이동
	if ( m_oFollowFX.idModel > 0 )
		g_pEngineHandler->HT_hrMoveObject( m_oFollowFX.idModel, m_oFollowFX.vecPos );
	//	팔로우 이펙트_체크
	this->HT_vAttack_AttackFollowCheck();
}

//	팔로우 이펙트 go
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
	//	나이계산
	m_oFollowFX.fTime += fElapsedTime;
	{
		//oxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxoxoxoxoxoxox
		HTvector3   instVelocity;					// new code//////////////////
		HTvector3   vectorToTarget;					// jks - vector from source to destination
        HTvector3   temp;							// jks - temporary vector

		//	정팀장의 요청으로 만든 타겥포지션 실시간 포착
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

//	공격타입이 PIERCING일때 내 좌표에 걸리는 놈마다 서버에 올림
HTvoid HTAttack::HT_vAttack_AttackFollow_TargetCheck()
{
	//	체크안해야될때
	if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_PRANA ||						//	프라나 날아오는것일때
		m_pFactor->dwAttackKeyID != g_cMainCharacter->HT_iMainChar_GetKeyID() ||	//	타겥이 나일때
		m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW )		//	팔로우가 있는 전체 범위 마법일때
		return;

	HTint iTargetKeyID;
	//	셀좌표로 캐릭터 키아디를 알아온다_OtherChar 검색
	iTargetKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyIDFromCellForPiercing( m_dwAttack_SkillType, m_oFollowFX.vecPos, m_pAttack_PiercingData );
	if( iTargetKeyID > 0 )
	{
		//	피어싱일때는 계속 저장하고
		if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
		{
			g_cOtherObjectSystem->HT_vOtherObjectSystem_EffectHitAction( iTargetKeyID, m_pFactor->nAttackSkillID, m_pFactor->nAttackItemID, m_pFactor->nCharModelID, m_pFactor->dwAttackKeyID );
			m_pAttack_PiercingData[m_byAttack_PiercingCellCount] = iTargetKeyID;
			m_byAttack_PiercingCellCount++;
			//	팔로우 공격시 상대방이 맞았는지 판정
			m_bAttack_GoodHit = HT_TRUE;
		}
		else
		{
			//	팔로우 정지
			m_fAttack_EOTransValue = 0;
			//	팔로우 공격시 상대방이 맞았는지 판정
			m_bAttack_GoodHit = HT_TRUE;
		}
	}
}

//	각도 체크
HTvoid HTAttack::HT_vAttack_AttackFollow_AngleCheck()
{
	// 활 전용입니다~
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

//	팔로우 이펙트_체크
HTvoid HTAttack::HT_vAttack_AttackFollowCheck()
{
	HTbool bType = HT_FALSE;
	//	날아가는 타입
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
			//	적중했냐?
			if( m_pFactor->nAttackType != MAINCHAR_ATTACKTYPE_PRANA )
			{
				if( m_bAttack_GoodHit )
					bType = HT_TRUE;
			}
			break;
	}

    if( bType )
	{
		//	널 모델 지우기
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

		//	상대방이 맞았을 때
		if( m_bAttack_GoodHit )
		{
			if( m_dwAttack_SkillType != HT_PCSKILLTYPE_ACTION_PIERCING &&		//	공격타입이 PIERCING일때는 수행하지 않는다.
				m_pFactor->nAttackType != MAINCHAR_ATTACKTYPE_PRANA )			//	공격타입이 PRANA일때는 수행하지 않는다.
			{        
				//	공격대상이 Object 일때
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
				//	범위공격일때
				else
				{
					HTint iTempEffectID;
					g_pEngineHandler->HT_hrStartSFX( &iTempEffectID, m_pFactor->nAttackSkillID, HT_SFX_WHEN_IMPACT, m_oFollowFX.idModel, HT_FALSE );
				}
			}
		}
		//	적이 맞았을때 취해야 할 액션들
		this->HT_vAttack_SetAttackPoint();
	}
}

//	적이 맞았을때 취해야 할 액션들
HTvoid HTAttack::HT_vAttack_SetAttackPoint()
{
	//	공격자가 메인캐릭터일때 서버에 정보를 알려준다.
	if( m_pFactor->dwAttackKeyID == g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		//	상대방이 맞았을 때
        this->HT_vNetWork_CSP_MSG_Attack();
	}

	//----------타격 사운드 틀어주기----------//
	if( SERVEROBJECT_IS_CHARACTER( m_pFactor->dwAttackKeyID ) )
	{
		if( m_pFactor->nAttackType == MAINCHAR_ATTACKTYPE_AUTOATTACK ||
			m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_SHORT )
		{
			g_pEngineHandler->HT_hrPlayAttackOKSound( m_pFactor->byTribe, m_pFactor->nAttackItemID );
		}
	}

	//	프라나 업 이펙트 틀어준다
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

	//	이 공격 클래스 리스트에서 삭제
	m_nAttack_Process = ATTACKPROCESS_DAETH;
}

//	이 클래스를 지우기 위한 마지막 보안장치->딜레이
HTvoid HTAttack::HT_vAttack_LiveTimeControl()
{
	DWORD dwPassTime = GetTickCount();
	if( dwPassTime > m_nAttack_LiveTime+10000 )
	{
		m_nAttack_Process = ATTACKPROCESS_DAETH;
	}	
}



//-------------------------------------------------------------
//			서버에 공격 요청함
//-------------------------------------------------------------
HTvoid HTAttack::HT_vNetWork_CSP_MSG_Attack()
{
	//	스플래쉬 공격일때를 체크
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

	//	범위마법 일때와 스플래쉬 일때
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHOUTFOLLOW ||
		m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_TERRITORY_WITHFOLLOW ||
		m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING ||
		m_iAttck_SplashIndex == 1 )
	{
		//	서버에 스킬(복수) 적용 요청
		this->HT_vNetWork_CSP_Cast_Area_Cast();
	}
	//	범위마법 아닐때
	else
	{
		this->HT_vNetWork_CSP_Cast_Unit_Cast( (short)m_pFactor->nAttackSkillID, (short)m_pFactor->dwAttackKeyID, (short)m_pFactor->dwTargetKeyID, m_pFactor->vecTargetPos );
	}
}

//	서버에 스킬(단수) 적용 요청
HTvoid HTAttack::HT_vNetWork_CSP_Cast_Unit_Cast( short snAttackSkillID, short snAttackerKeyID, short snTargetKeyID, HTvector3 vecTargetPos )
{
	//	셀 위치
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( vecTargetPos, crdCell );
	HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	PS_CSP_CAST_UNIT_SKILL info = HT_NULL;
    info = new S_CSP_CAST_UNIT_SKILL;

	memset( info, 0, sizeof(S_CSP_CAST_UNIT_SKILL) );

    info->snRes = 0;
	info->snSkillID		= snAttackSkillID;		// cast한 skill ID		
	info->snCasterKeyID = snAttackerKeyID;		// Caster handle
	info->kTarget.snKeyID = snTargetKeyID;		// Target handle
	//	화살을 착용하고 있을때 초기값이 내려오는 것을 방지하기 위해
	info->snPackCount	= -1;

	info->snCasterX		= pPt.x;				// Caster의 현재 x 좌표
	info->snCasterZ		= pPt.y;				// Caster의 현재 y 좌표
	info->snMapX		= crdCell.x;
	info->snMapZ		= crdCell.y;

	//	팔로우 공격시 날아간 시간을 셋팅
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

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Skill_Cast_Unit_Skill : %d, %d", info->snSkillID , info->kTarget.snKeyID );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	서버에 스킬(복수) 적용 요청
HTvoid HTAttack::HT_vNetWork_CSP_Cast_Area_Cast()
{
	//	셀 위치 fors_debug 횐묑傑땍커깃돨뒈렘
	HT_CELL_COORD crdCell;
	g_pEngineHandler->HT_3DCOORD_TO_CELL( m_pFactor->vecTargetPos, crdCell );
    HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
	HTint	iElement[TN_MAX_TARGET_COUNT];
	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )		iElement[i] = 0;
	//	공격타입이 PIERCING일때	
	if( m_dwAttack_SkillType == HT_PCSKILLTYPE_ACTION_PIERCING )
		memcpy( &iElement, &m_pAttack_PiercingData, sizeof(int)*TN_MAX_TARGET_COUNT );
	else
	{
		HTbyte byGoodType;
		g_pParamMgr->HT_bGetPCSkillType( m_pFactor->nAttackSkillID, 1, &byGoodType );

		HTint iAOE;
		if( m_iAttck_SplashIndex == 1 )
		{
			//	스플레쉬 데미지에서 가장 많으 데미지를 입어야 할애는 그자신이기 때문에
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
	info->snSkillID		= (short)m_pFactor->nAttackSkillID;		// cast한 skill ID		
	info->snCasterKeyID = (short)m_pFactor->dwAttackKeyID;		// Caster handle

	info->snCasterX		= pPt.x;									// Caster의 현재 x 좌표
	info->snCasterZ		= pPt.y;									// Caster의 현재 y 좌표
	info->snMapX		= crdCell.x;							// Map의 현재 x 좌표
	info->snMapZ		= crdCell.y;							// Map의 현재 y 좌표

	for( HTint i=0 ; i<TN_MAX_TARGET_COUNT ; i++ )
	{
        info->krgTarget[i].snKeyID = iElement[i]; //this is good right
     //    info->krgTarget[i].snKeyID = -12323948;
	//	 info->krgTarget[i].iAffection=-1329230230;
	//	 info->krgTarget[i].iDamage=-18281291l;
	}

	//	팔로우 공격시 날아간 시간을 셋팅
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

	//-----디버깅 테스트를 위하여-----//
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
//	Class 이름	: HTAttackManager
//
//	Class 설명 	: 
//		- 각 Object의 전투 명령을 수행하는 클래스를 관리
//
//	작성자		:
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

//	어택 클래스 생성
HTvoid HTAttackManager::HT_vAttackMgr_Create( P_ATTACK_FACTOR info )
{
	//----------LL 데이타 삽입-헤드 바로 뒤에---------//
	HT_LL_hrInsertAfter( info );
}

//	어택 클래스 컨트롤
HTvoid HTAttackManager::HT_vAttackMgr_Control( HTfloat fElapsedTime )
{
	//-----NPC 노드에서 체크-----//
	HT_ATTACK_NODE *t;
	
    t = m_sAttackHead->next;
	while( t != m_sAttackTail )
	{
		t->cAttack.HT_vAttack_Control( fElapsedTime );
        t = t->next;
	}
	//----------LL 데이타 지우기---------//
	HT_LL_hrDeleteNode();
}

//	전체 공격 리스트 삭제
HTvoid HTAttackManager::HT_vAttackMgr_AllDelete()
{
	//----------LL 데이타 전부 지우기---------//
	//HT_LL_hrDeleteAll();

	m_nAttackMaxDemage = 0;
}

//----------링크드 리스트 구현한 부분---------//
//----------LL 초기화---------//
HTvoid HTAttackManager::HT_LL_vInitList()
{
	m_sAttackHead = NULL;
	m_sAttackTail = NULL;

	m_sAttackHead = new HT_ATTACK_NODE;
	m_sAttackTail = new HT_ATTACK_NODE;

	m_sAttackHead->next = m_sAttackTail;
	m_sAttackTail->next = m_sAttackTail;
}

//----------LL 데이타 삽입-헤드 바로 뒤에---------//
HTvoid HTAttackManager::HT_LL_hrInsertAfter( P_ATTACK_FACTOR info )
{
    HT_ATTACK_NODE *s;
	s = NULL;
	s = new HT_ATTACK_NODE;
	s->cAttack.HT_vAttack_SetInitData( info );
	s->next = m_sAttackHead->next;
	m_sAttackHead->next = s;
}

//----------LL 데이타 지우기---------//
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

//----------LL 데이타 전부 지우기---------//
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

//	메인캐릭터 팔로우 모델의 위치를 받아옴
HTRESULT HTAttackManager::HT_hrAttackMgr_GetFollowModel( HTvector3& vecFront, HTvector3& vecBack )
{
	//-----NPC 노드에서 체크-----//
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
