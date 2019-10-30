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
//	Class 이름	: HitCount
//
//	Class 설명 	: 
//		- 각 Demage 수치를 표시
//
//	작성자		:
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
	//	공격 맞은 숫자 뛰어주기
	HTvoid			HT_vHitCount_HitCount_Control();
	//	맞은 힛 숫자_액션 시작 셋팅
	HTvoid			HT_vHitCount_HitCount_SetStartAction();
	//	맞은 힛 숫자_함수 셋팅
	HTvoid			HT_vHitCount_HitCountSetFun();
	//	맞은 힛 숫자_카메라와의 거리 계산
	HTvoid			HT_vHitCount_GetCameraEyeDistance();
	//	맞은 힛 숫자_만들기
	HTvoid			HT_vHitCount_SetHitNumberMake( HTint nCount );
	//	맞은 힛 숫자_액션
	HTvoid			HT_vHitCount_SetHitNumberAction();
	//	맞은 힛 숫자_체크
	HTvoid			HT_vHitCount_SetHitNumberCheck();

	//	이 클래스를 지우기 위한 마지막 보안장치->딜레이
	HTvoid			HT_vHitCount_LiveTimeControl();

public:
	//	Delay Time
	DWORD			m_dwDelayTime;
	DWORD			m_dwStartDelayTime;
    //	힛 카운트 뿌려주기
	HTint			m_iHitCount_Demage;
	//	0 : PC -> Mon		:	White
	//	1 : Mon -> PC		:	Red
	//	2 : PC -> Mon Cri	:	Yellow
	//	3 : Mon-> PC Cri	:	Red
	//	4 : PC -> Mon Miss	:	Red
	//	5 : Mon -> PC Miss	:	White
    BYTE			m_byHitCount_NumberType;
	HTvector2		m_pHitCount_JudgmentPos;		//	힛 카운트 좌표
	HTint			m_nHitCount_PosSw;				//	힛 카운트 좌표 제대로 받았는지 체크
	
	HTint			m_nHitCount_NumberCount;
	HTint			m_nHitCount_NumberImageID[MAXNUMBERCOUNT];

	HTvector3		m_vecHitCount_TargetPos;

	//	프로세스 End Check
	HTbool			m_bHitCount_EndCheck;
	HTint			m_iHitCount_LiveTime;
	int             m_iHitCount_CombatResult;

	//	Effect	Type
    HTbyte			m_byHitCount_EffectType;
	HTfloat			m_fHitCount_ActionValue[MAXNUMBERCOUNT];
	HTfloat			m_fHitCount_LimitValue[MAXNUMBERCOUNT];
	HTint			m_iHitCount_Direct[MAXNUMBERCOUNT];
	HTdword			m_dwHitCount_EffectTime;
	//	연속 데이지인지 파악
	HTbool			m_bHitCount_Continue;
	//	최초의 셋티에서는 숫자 안뛰우기 위하여
	HTbool			m_bHitCount_HideNumber;
};


//----------------------------------------------------------------------------//
//	Class 이름	: HitCountMgr
//
//	Class 설명 	: 
//		- 각 Demage 수치를 표시하는 클래스를 관리
//
//	작성자		:
//		- 20032/11/26, Created by Jung Eui Kyu
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//

//	공격 링크드리스트를 구현하기 위한 구조체랍니다.
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

	//	어택 클래스 생성
	//	byAttacker 0:Main,1:Other,2:Monster
	//	snRes 0:Normal, 1:Cri
	HTvoid					HT_vHitCountMgr_Create( HTbyte byAttacker, short snRes, HTint iHitCount, HTvector3 vecTargetPos, HTint iTimeCount, HTbool bContinue );
	//	어택 클래스 컨트롤
	HTvoid					HT_vHitCountMgr_Control( HTfloat fElapsedTime );
	//	전체 공격 리스트 삭제
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
