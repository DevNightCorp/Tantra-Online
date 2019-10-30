#pragma once

//	2003.03.14에 정의규가 만듬
//	이 클래스는 공격 포인트가 일어난 시점부터 시작하여 
#define ATTACKPROCESS_NONE					1000
#define ATTACKPROCESS_ATTACKPOINT			1001
#define ATTACKPROCESS_FOLLOWEFFET			1002
#define ATTACKPROCESS_HITCOUNT				1003
#define ATTACKPROCESS_DAETH					1004

#define MAINCHAR_ATTACKTYPE_NONE					0
#define MAINCHAR_ATTACKTYPE_AUTOATTACK				1
#define MAINCHAR_ATTACKTYPE_SKILL					2
#define MAINCHAR_ATTACKTYPE_PRANA					3		//	프라나 빨아들이는 것


#define FOLLOWTYPE_NORMAL						1
#define FOLLOWTYPE_JKSHOMER						2


#define MAX_SPEED (100.0f)
#define VECTOR_CORRECTION_FACTOR (5.0f)

//jks 추가된 attribute
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
class HTAttack
{
public:
	HTAttack(void);
	~HTAttack(void);

	//	초기 데이타 셋팅
    HTvoid			HT_vAttack_SetInitData( P_ATTACK_FACTOR info );
	
	//	두벡터를 이용하여 라디안 값을 얻어온다.		A:기준 벡터, B:비교 벡터
	HTfloat			HT_fAttackGetAngle( HTvector3 A, HTvector3 B );
		
	//	공격 컨트롤
	HTvoid			HT_vAttack_Control( HTfloat fElapsedTime );

	//	공격 포인트에서 할일
	HTvoid			HT_vAttack_AttackPoint();
	//	공격 포인트에서 할일_팔로우가없는 공격 셋팅
	HTvoid			HT_vAttack_SetWithOutFollow();
    //	공격 포인트에서 할일_공격 거리 계산
	HTvoid			HT_vAttack_DistanceCheck();
	// jks - Init part              
	// 생성시 필요한 init 부분
	HTvoid			HT_vAttack_Set_JKS_FlyingObject_Homer();
    //	공격 포인트에서 할일_팔로우 공격 셋팅
	HTvoid			HT_vAttack_SetWithFollow();
	
	//	팔로우 이펙트 컨트롤
	HTvoid			HT_vAttack_AttackFollowEffect( HTfloat fElapsedTime );
	//	팔로우 이펙트 go
	HTvoid			HT_vAttack_AttackFollowEffectGo( HTfloat fElapsedTime );
	//	jks - code for homing flying object.
	HTvoid			HT_vAttack_AttackFollow_FlyingObject_JKS_Homer( HTfloat fElapsedTime );
	//	공격타입이 팔로우일때 내 좌표에 걸리는 놈마다 서버에 올림
	HTvoid			HT_vAttack_AttackFollow_TargetCheck();
	//	각도 체크
	HTvoid			HT_vAttack_AttackFollow_AngleCheck();

	//	팔로우 이펙트_체크
	HTvoid			HT_vAttack_AttackFollowCheck();
	//	팔로우 이펙트_체크
	HTvoid			HT_vAttack_AttackGuidedMislFollowCheck();

	//	캐릭터 공격 포인트에서 할일
	HTvoid			HT_vAttack_SetAttackPoint();
	//	이 클래스를 지우기 위한 마지막 보안장치->딜레이
	HTvoid			HT_vAttack_LiveTimeControl();

	//	서버에 공격 요청함
	HTvoid			HT_vNetWork_CSP_MSG_Attack();
	//	서버에 스킬(단수) 적용 요청
	HTvoid			HT_vNetWork_CSP_Cast_Unit_Cast( short snAttackSkillID, short snAttackerKeyID, short snTargetKeyID, HTvector3 vecTargetPos );
	//	서버에 스킬(복수) 적용 요청
	HTvoid			HT_vNetWork_CSP_Cast_Area_Cast();

public:
	HTint			m_nAttack_Process;				//	공격 프로세스

	//	JKS For Homer (Flying Object)
	HTFollowFX		m_oFollowFX;

	//	스킬 공격 타입
	HTdword			m_dwAttack_SkillType;
	//	이 클래스를 지우기 위한 마지막 보안장치->딜레이
	DWORD			m_nAttack_LiveTime;
	//	클래스를 돌리는데 필요한 정보
	P_ATTACK_FACTOR	m_pFactor;
	//	날아가는 타입
	HTint			m_iAttack_FolowType;
	HTbool			m_bAttack_PursuitSw;		//	상대좌표를 추적해 가느냐?
	BYTE			m_byAttack_PursuitCount;

	HTfloat			m_fAttack_EOTransValue;		//	상대적인 변화량
	HTfloat			m_fAttack_TimeTransValue;	//	시간 변화량
	HTfloat			m_fAttack_TotalTime;		//	전체 시간

	//	팔로우 모델 보정 스피드
	HTfloat			m_fAttack_CorrectSpeed;

	//	공격타입이 PIERCING 이전셀과 현재셀을 비교하기 위해
	BYTE			m_byAttack_PiercingCellCount;
	HTint			m_pAttack_PiercingData[TN_MAX_TARGET_COUNT];

	//	팔로우 공격시 상대방이 맞았는지 판정
	HTbool			m_bAttack_GoodHit;

	//	스플래쉬 공격일때
	HTint			m_iAttck_SplashIndex;

	//	팔로우 공격시 날아간 시간을 저장
	HTdword			m_dwAttack_FollowTime;
	//	팔로우 모델 속도
	HTint			m_iAttack_ModelSpeed;
	//	Homer Speed
	HTint			m_iAttack_HomerSpeed;
};


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


//	공격 링크드리스트를 구현하기 위한 구조체랍니다.
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

	//	어택 클래스 생성
	HTvoid					HT_vAttackMgr_Create( P_ATTACK_FACTOR );
	//	어택 클래스 컨트롤
	HTvoid					HT_vAttackMgr_Control( HTfloat fElapsedTime );
	//	전체 공격 리스트 삭제
	HTvoid					HT_vAttackMgr_AllDelete();
	
	//	메인캐릭터 팔로우 모델의 위치를 받아옴
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
