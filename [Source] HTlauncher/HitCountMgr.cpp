#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "hitcountmgr.h"

//	0 : PC -> Mon		:	White
//	1 : Mon -> PC		:	Red
//	2 : PC -> Mon Cri	:	Yellow
//	3 : Mon-> PC Cri	:	Red
//	4 : PC -> Mon Miss	:	Red
//	5 : Mon -> PC Miss	:	White
HTint g_iHitNumber[6][10] = { 26044, 26045, 26046, 26047, 26048, 26049, 26050, 26051, 26052, 26053,
							  26054, 26055, 26056, 26057, 26058, 26059, 26060, 26061, 26062, 26063,
							  26034, 26035, 26036, 26037, 26038, 26039, 26040, 26041, 26042, 26043,

							  26054, 26055, 26056, 26057, 26058, 26059, 26060, 26061, 26062, 26063, 
							  26054, 26055, 26056, 26057, 26058, 26059, 26060, 26061, 26062, 26063, 
							  26044, 26045, 26046, 26047, 26048, 26049, 26050, 26051, 26052, 26053	};

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
HitCount::HitCount(void)
{
	m_iHitCount_CombatResult = 0;
	m_nHitCount_NumberCount		= 0;
    for( HTint i=0 ; i<10 ; i++ )
        m_nHitCount_NumberImageID[i] = -1;
	//	최초의 셋티에서는 숫자 안뛰우기 위하여
	m_bHitCount_HideNumber = HT_FALSE;
}

HitCount::~HitCount(void)
{
	for( HTint i=0 ; i<10 ; i++ )
	{
        if( m_nHitCount_NumberImageID[i] != -1 )
			g_2DObjectMgr->HT_2DObjectMgrDelete( m_nHitCount_NumberImageID[i] );
	}
}

//	Input
HTvoid HitCount::HT_vHitCount_Input( HTbyte byAttacker, short snRes, HTint iHitCount, HTvector3 vecTargetPos, HTint iTimeCount, HTbool bContinue )
{
	//	Delay Time
	m_dwDelayTime = iTimeCount * 300;
	m_dwStartDelayTime = timeGetTime();

    //	데미지 값
	m_iHitCount_Demage = iHitCount;
	//	프로세스 End Check
	m_bHitCount_EndCheck = HT_TRUE;
	m_iHitCount_LiveTime = timeGetTime();
	//	목표 좌표
	m_vecHitCount_TargetPos = vecTargetPos;
	m_iHitCount_CombatResult = snRes;
	//	연속 데이지인지 파악
	m_bHitCount_Continue = bContinue;

	//	공격 실패일때
	if( snRes == 0 || 
		snRes == 1 )
	{
		if( byAttacker == 0 || byAttacker == 1 )
		{
			if( snRes == 0 )
				m_byHitCount_NumberType = 0;
			else
				m_byHitCount_NumberType = 2;
		}
		else if( byAttacker == 2 )
		{
			if( snRes == 0 )
				m_byHitCount_NumberType = 1;
			else
				m_byHitCount_NumberType = 3;
		}
	}
	else if( snRes == 2 )
	{
		if( byAttacker == 0 || byAttacker == 1 )
		{
			m_byHitCount_NumberType = 5;
		}
		else
			m_byHitCount_NumberType = 4;
	}

	if( iTimeCount == 0 )
	{
		this->HT_vHitCount_HitCount_SetStartAction();
	}
}

//	공격 맞은 숫자 뛰어주기
HTvoid HitCount::HT_vHitCount_HitCount_Control()
{
	//	Set Start
	if( m_dwStartDelayTime != 0 )
	{
		this->HT_vHitCount_HitCount_SetStartAction();
	}
	else
	{
		//	맞은 힛 숫자_액션
		this->HT_vHitCount_SetHitNumberCheck();
		//	맞은 힛 숫자 체크
		this->HT_vHitCount_SetHitNumberAction();
		//	이 클래스를 지우기 위한 마지막 보안장치->딜레이
		this->HT_vHitCount_LiveTimeControl();
		//	최초의 셋팅에서는 숫자 안뛰우기 위하여
		if( !m_bHitCount_HideNumber )
		{
			m_bHitCount_HideNumber = HT_TRUE;
			for( HTint i=0 ; i<10 ; i++ )
			{ 
				if( m_nHitCount_NumberImageID[i] != -1 )
					g_2DObjectMgr->HT_2DObjectMgrSetActive( m_nHitCount_NumberImageID[i] );
			}
		}
	}
}

//	맞은 힛 숫자_액션 시작 셋팅
HTvoid HitCount::HT_vHitCount_HitCount_SetStartAction()
{
	DWORD dwPassTime = timeGetTime();
	if( dwPassTime >= (m_dwStartDelayTime+m_dwDelayTime) )
	{
		m_dwStartDelayTime = 0;
		//	맞은 힛 숫자_함수 셋팅
		this->HT_vHitCount_HitCountSetFun();
	}
}

//	맞은 힛 숫자_함수 셋팅
HTvoid HitCount::HT_vHitCount_HitCountSetFun()
{
	//	숫자 만들기
	//	숫자 만들기_거리계산
	this->HT_vHitCount_GetCameraEyeDistance();
	//	맞은 힛 숫자 만들기
	this->HT_vHitCount_SetHitNumberMake( m_iHitCount_Demage );

	//	Effect	Type
	if( m_iHitCount_CombatResult == eCmbt_Dodge || 
		m_bHitCount_Continue )								m_byHitCount_EffectType = EFFECTTYPE_ONLYUP;
	else if( m_iHitCount_CombatResult == eCmbt_Critical )   m_byHitCount_EffectType = EFFECTTYPE_EXPANSION;
	else													m_byHitCount_EffectType = EFFECTTYPE_UPDOWN;

	//	Init Trans Value
	for( HTint i=0 ; i<MAXNUMBERCOUNT ; i++ )
	{
		if( m_byHitCount_EffectType == EFFECTTYPE_UPDOWN )
		{
			m_fHitCount_ActionValue[i] = 0.0f;
			m_fHitCount_LimitValue[i] = 20;
			if( i%2 == 0 )
			{
				m_iHitCount_Direct[i] = 1;
			}
			else
			{
				m_iHitCount_Direct[i] = -1;
			}
		}
		else if( m_byHitCount_EffectType == EFFECTTYPE_EXPANSION )
		{
			m_fHitCount_ActionValue[i] = 80.0f;
		}
		else
		{
			m_fHitCount_ActionValue[i] = 1.0f;
		}
	}
}

//---------맞은 힛 숫자_액션----------//
HTvoid HitCount::HT_vHitCount_SetHitNumberCheck()
{
	HTvector3 vecTemp;
	HTfloat fPosX, fPosY;
	HTfloat fWeight, fHight;

	for( HTint i=0 ; i<m_nHitCount_NumberCount ; i++ )
	{
		if( m_byHitCount_EffectType == EFFECTTYPE_ONLYUP )
		{
			fWeight = 0;
			fHight = ( (1-m_fHitCount_ActionValue[i]) * 120 )+100;
			fPosX = m_pHitCount_JudgmentPos.x - ( i * 30 );
			fPosY = m_pHitCount_JudgmentPos.y - fHight - 100;
		}
		else if( m_byHitCount_EffectType == EFFECTTYPE_ONLYRIGHT )
		{
			fWeight = ( (1-m_fHitCount_ActionValue[i]) * 120 );
			fPosX = m_pHitCount_JudgmentPos.x - ( i * 30 ) + fWeight;
			fPosY = m_pHitCount_JudgmentPos.y - 120;
		}
		else if( m_byHitCount_EffectType == EFFECTTYPE_UPDOWN )
		{
			fHight = m_fHitCount_ActionValue[i]+120;
			fPosX = m_pHitCount_JudgmentPos.x - ( i * 30 );
			fPosY = m_pHitCount_JudgmentPos.y - fHight;
		}
		else if( m_byHitCount_EffectType == EFFECTTYPE_EXPANSION )
		{
			fHight = 120+(m_fHitCount_ActionValue[i]/2);
			fPosX = m_pHitCount_JudgmentPos.x - ( i * (30+(m_fHitCount_ActionValue[i]*0.9f)) );
			fPosY = m_pHitCount_JudgmentPos.y - fHight;
		}

		//	Set Apply Engine
		g_2DObjectMgr->HT_2DObjectMgrSetPosition( m_nHitCount_NumberImageID[i], HTvector3( fPosX, fPosY, 0 ) );
		if( m_byHitCount_EffectType == EFFECTTYPE_EXPANSION )
		{
			g_2DObjectMgr->HT_2DObjectMgrSetScale( m_nHitCount_NumberImageID[i], 32.0f+m_fHitCount_ActionValue[i], 32.0f+m_fHitCount_ActionValue[i] );
		}
	}
}

//---------맞은 힛 숫자 체크----------//
HTvoid HitCount::HT_vHitCount_SetHitNumberAction()
{
	for( HTint i=0 ; i<MAXNUMBERCOUNT ; i++ )
	{
		if( m_byHitCount_EffectType == EFFECTTYPE_ONLYUP ||
			m_byHitCount_EffectType == EFFECTTYPE_ONLYRIGHT )
		{
			m_fHitCount_ActionValue[i] *= 0.85f;
			if( m_fHitCount_ActionValue[i] <= 0.05f )
			{
				//	프로세스 End Check
				m_bHitCount_EndCheck = HT_FALSE;
			}
		}
		else if( m_byHitCount_EffectType == EFFECTTYPE_UPDOWN )
		{
			if( m_iHitCount_Direct[i] == 1 )
			{
				m_fHitCount_ActionValue[i] += (m_fHitCount_LimitValue[i]);
				if( m_fHitCount_ActionValue[i] >= m_fHitCount_LimitValue[i] )
				{
					m_iHitCount_Direct[i] *= -1;
					m_fHitCount_LimitValue[i] /= 2;
					if( m_fHitCount_LimitValue[i] <= 0.5f )
					{
						//	프로세스 End Check
						m_bHitCount_EndCheck = HT_FALSE;
					}
				}
			}
			else if( m_iHitCount_Direct[i] == -1 )
			{
				m_fHitCount_ActionValue[i] -= (m_fHitCount_LimitValue[i]);
				if( m_fHitCount_ActionValue[i] <= -m_fHitCount_LimitValue[i] )
				{
					m_iHitCount_Direct[i] *= -1;
					m_fHitCount_LimitValue[i] /= 2;
				}
			}
		}
		else if( m_byHitCount_EffectType == EFFECTTYPE_EXPANSION )
		{
			m_fHitCount_ActionValue[i] *= 0.70f;
			if( m_fHitCount_ActionValue[i] <= 0.1f )
			{
				//	프로세스 End Check
				m_bHitCount_EndCheck = HT_FALSE;
			}
		}
	}
}

//	맞은 힛 숫자_카메라와의 거리 계산
HTvoid HitCount::HT_vHitCount_GetCameraEyeDistance()
{
	//	판정 뿌려줄 위치 가져오기
	m_nHitCount_PosSw = g_pEngineHandler->HT_hrGetScreenCoordFrom3DCoord( m_vecHitCount_TargetPos, m_pHitCount_JudgmentPos );
}

//---------맞은 힛 숫자 만들기----------//
HTvoid HitCount::HT_vHitCount_SetHitNumberMake( HTint nCount )
{
	if( m_nHitCount_PosSw == HT_FAIL )
		return;

	HTvector3 vecPos;
	HTint nTempNumber;
	m_nHitCount_NumberCount = 0;

	//	타격이 있을때
	if( (eCmbt_Normal == m_iHitCount_CombatResult) || (eCmbt_Critical == m_iHitCount_CombatResult) ) // 공격 성공일 때, ...
	{
		//	타격이 있을때
		if( nCount > 0 )
		{ // damage 숫자를 출력한다.
			while( nCount > 0 )
			{
				nTempNumber = nCount%10;
				vecPos.x = m_pHitCount_JudgmentPos.x - ( m_nHitCount_NumberCount * 10 );
				vecPos.y = m_pHitCount_JudgmentPos.y;
				vecPos.z = 0;

				m_nHitCount_NumberImageID[m_nHitCount_NumberCount] = g_2DObjectMgr->HT_2DObjectMgrCreate( g_iHitNumber[m_byHitCount_NumberType][nTempNumber], vecPos );
				g_2DObjectMgr->HT_2DObjectMgrSetPosition( m_nHitCount_NumberImageID[m_nHitCount_NumberCount], vecPos );
				//g_2DObjectMgr->HT_2DObjectMgrSetActive( m_nHitCount_NumberImageID[m_nHitCount_NumberCount] );

				nCount = nCount/10;
				m_nHitCount_NumberCount++;
				if( m_nHitCount_NumberCount > 9 )
					break;
			}
		}
		else
		{// success 이미지를 출력한다.
			vecPos.x = m_pHitCount_JudgmentPos.x - 50;
			vecPos.y = m_pHitCount_JudgmentPos.y;
			vecPos.z = 0;
			
			enum { eSucc_Blue = 26077, eSucc_Red, eSucc_White, eSucc_Yellow, } ; // success 2D 이미지 - 26077(blue), 26078(red), 26079(white), 26080(yellow)
			m_nHitCount_NumberImageID[m_nHitCount_NumberCount] = g_2DObjectMgr->HT_2DObjectMgrCreate( eSucc_Yellow, vecPos ); // 26064(파란색 0)으로 임시 처리

			g_2DObjectMgr->HT_2DObjectMgrSetPosition( m_nHitCount_NumberImageID[m_nHitCount_NumberCount], vecPos );
			//g_2DObjectMgr->HT_2DObjectMgrSetActive( m_nHitCount_NumberImageID[m_nHitCount_NumberCount] );
			m_nHitCount_NumberCount++;

		}
	}
	//	Miss일때
	else if( eCmbt_Dodge == m_iHitCount_CombatResult )
	{
		vecPos.x = m_pHitCount_JudgmentPos.x - 50;
		vecPos.y = m_pHitCount_JudgmentPos.y;
		vecPos.z = 0;

		if( m_byHitCount_NumberType == 4 )
		{
            m_nHitCount_NumberImageID[m_nHitCount_NumberCount] = g_2DObjectMgr->HT_2DObjectMgrCreate( 26074, vecPos );
		}
		else
		{
			m_nHitCount_NumberImageID[m_nHitCount_NumberCount] = g_2DObjectMgr->HT_2DObjectMgrCreate( 26075, vecPos );
		}

		g_2DObjectMgr->HT_2DObjectMgrSetPosition( m_nHitCount_NumberImageID[m_nHitCount_NumberCount], vecPos );
		//g_2DObjectMgr->HT_2DObjectMgrSetActive( m_nHitCount_NumberImageID[m_nHitCount_NumberCount] );
		m_nHitCount_NumberCount++;
	}
}

//	이 클래스를 지우기 위한 마지막 보안장치->딜레이
HTvoid HitCount::HT_vHitCount_LiveTimeControl()
{
	DWORD dwPassTime = GetTickCount();
	if( dwPassTime > (DWORD)(m_iHitCount_LiveTime+10000) )
	{
		m_bHitCount_EndCheck = HT_FALSE;
	}	
}


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
HitCountMgr::HitCountMgr(void)
{
	this->HT_LL_vInitList();
}

HitCountMgr::~HitCountMgr(void)
{
	HT_DELETE( m_sHitCounHead );
	HT_DELETE( m_sHitCounTail );
}

//	클래스 생성
//	byAttacker 0:Main,1:Other,2:Monster
//	snRes 0:Normal, 1:Cri
HTvoid HitCountMgr::HT_vHitCountMgr_Create( HTbyte byAttacker, short snRes, HTint iHitCount, HTvector3 vecTargetPos, HTint iTimeCount, HTbool bContinue )
{
	this->HT_LL_hrInsertAfter( byAttacker, snRes, iHitCount, vecTargetPos, iTimeCount, bContinue );
}

//	클래스 컨트롤
HTvoid HitCountMgr::HT_vHitCountMgr_Control( HTfloat fElapsedTime )
{
	//-----NPC 노드에서 체크-----//
	HT_HITCOUNT_NODE *t;
	
	t = m_sHitCounHead->next;
	while( t != m_sHitCounTail )
	{
		t->cHitCount.HT_vHitCount_HitCount_Control();
        t = t->next;
	}
	//----------LL 데이타 지우기---------//
	this->HT_LL_hrDeleteNode();
}

//	전체 공격 리스트 삭제
HTvoid HitCountMgr::HT_vHitCountMgr_AllDelete()
{
}

//----------링크드 리스트 구현한 부분---------//
//----------LL 초기화---------//
HTvoid HitCountMgr::HT_LL_vInitList()
{
	m_sHitCounHead = NULL;
	m_sHitCounTail = NULL;

	m_sHitCounHead = new HT_HITCOUNT_NODE;
	m_sHitCounTail = new HT_HITCOUNT_NODE;

	m_sHitCounHead->next = m_sHitCounTail;
	m_sHitCounTail->next = m_sHitCounTail;
}

//----------LL 데이타 삽입-헤드 바로 뒤에---------//
HTvoid HitCountMgr::HT_LL_hrInsertAfter( HTbyte byAttacker, short snRes, HTint iHitCount, HTvector3 vecTargetPos, HTint iTimeCount, HTbool bContinue )
{
	HT_HITCOUNT_NODE *s;
	s = NULL;
	s = new HT_HITCOUNT_NODE;
	s->cHitCount.HT_vHitCount_Input( byAttacker, snRes, iHitCount, vecTargetPos, iTimeCount, bContinue );
	s->next = m_sHitCounHead->next;
	m_sHitCounHead->next = s;
}

//----------LL 데이타 지우기---------//
HTRESULT HitCountMgr::HT_LL_hrDeleteNode()
{
	HT_HITCOUNT_NODE *s;
	HT_HITCOUNT_NODE *p;

	p = m_sHitCounHead;
	s = p->next;
	while( s->cHitCount.m_bHitCount_EndCheck != HT_FALSE && s != m_sHitCounTail )
	{
		p = p->next;
		s = p->next;
	}

	if( s != m_sHitCounTail )
	{
		p->next = s->next;
		HT_DELETE( s );
		return HT_TRUE;
	}
	else
		return HT_FALSE;
}

//----------LL 데이타 전부 지우기---------//
HTvoid HitCountMgr::HT_LL_hrDeleteAll()
{
	HT_HITCOUNT_NODE *s;
	HT_HITCOUNT_NODE *t;
	
	t = m_sHitCounHead->next;
	while( t != m_sHitCounTail )
	{
		s = t;
		t = t->next;
		HT_DELETE( s );
	}

	m_sHitCounHead->next = m_sHitCounTail;
}

