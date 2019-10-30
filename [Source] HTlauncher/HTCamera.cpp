
#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTCamera.h"

CHTCamera::CHTCamera()
{
}

CHTCamera::~CHTCamera()
{
}

HTRESULT CHTCamera::HT_CameraInit()
{
	m_fEyeLookDistance				= 100.0f;
	m_fEyeLookAngle					= 5.7f;//5.13f;
	m_fZoomINOut					= 100.0f;//-91.58f;
	m_fCameraUpDown					= 100.0f;
	m_fCameraAngle					= HT_PI;
	m_vCamera_STraightSw			= HT_FALSE;
	m_fCamera_STraightHight			= 10.0f;

	m_fTransDirect					= HT_PI;
	m_iCameraMode					= CAMERATYPE_LOOK_CENTERCHARACTER;

	m_iCamera_Type					= CAMERATYPE_EYE_DEFINECAMERA;
	m_vCamera_ResentEye				= HTvector3( 0, 0, 100 );
	m_vCamera_ResentLook			= HTvector3( 0, 0, 0 );

	m_fCamera_CharHightTrans		= 0.0f;
	m_fCamera_CharHightTransValue	= 0.80f;

	// 처음에는 비 활성화 상태로 한다.
	HT_vCamera_Initialize();

	return HT_OK;
}

//----------메인게임 돌입후 한번만 업데이트----------//
HTvoid CHTCamera::HT_vCamera_SetOneTimeInit( HTfloat fChrHight )
{
	m_fCamera_CharHeight		= g_pEngineHandler->HT_fGetObjHeight( g_cMainCharacter->HT_vMainChar_GetModelID() )+5;
	m_fCamera_CharHalfHeight	= m_fCamera_CharHeight/2;
	m_fCamera_CharCorrectHeight	= 0.0f;
	//	캐릭터 y값에 따른 카메라 높이 변화_캐릭터가 계단을 이용할때 갑자기 튀는것을 막기위해
	this->HT_vCamera_SetCharHightTrans( fChrHight );
}

//------------카메라 전체적인 컨트롤을 담당---------------//
HTvoid CHTCamera::HT_vCameraUpdate( HTvector3 vecCharPos, HTfloat fAngle, HTfloat fElapsedTime )
{
	HTvector3 vecTempPos = m_vCamera_ResentEye;
	m_vPosCharacter.x = vecCharPos.x;
	m_vPosCharacter.z = vecCharPos.z;
	if( m_iCameraMode == CAMERATYPE_EYE_CENTERCHARACTER || m_iCameraMode == CAMERATYPE_EYE_BACKVIEW || m_iCameraMode == CAMERATYPE_EYE_FRONTVIEW )
        m_vPosCharacter.y = HT_vCamera_GetCharHightTrans( vecCharPos.y );
	else
		m_vPosCharacter.y = vecCharPos.y;

	//------------카메라 앵글 체크---------------//
	if( m_iCameraMode == CAMERATYPE_EYE_BACKVIEW ||
		m_iCameraMode == CAMERATYPE_EYE_FRONTVIEW )
	{
		this->HT_vCameraAngleTransing();
	}

	//------------카메라 Look/Eye의 액션---------------//
	this->HT_vCamera_LookEyeUpdate( fAngle, fElapsedTime );

	//if( m_iCamera_Type != CAMERATYPE_EYE_DEFINECAMERA )
	{
		if( vecTempPos.x != m_vCamera_ResentEye.x ||
			vecTempPos.y != m_vCamera_ResentEye.y ||
			vecTempPos.z != m_vCamera_ResentEye.z )
		{
			//g_imsi_button[1] = m_vCamera_ResentEye.x;
			//g_imsi_button[2] = m_vCamera_ResentEye.y;
			//g_imsi_button[3] = m_vCamera_ResentEye.z;

			//g_imsi_button[4] = m_vCamera_ResentLook.x;
			//g_imsi_button[5] = m_vCamera_ResentLook.y;
			//g_imsi_button[6] = m_vCamera_ResentLook.z;

			//----------지면의 아래로 카메라가 내려가지 앉게----------//
			g_pEngineHandler->HT_hrSetEye( HT_vUpdateEye_TerrainCheck( m_vCamera_ResentEye, m_vPosCharacter.y ) );
			g_pEngineHandler->HT_hrSetLookAt( m_vCamera_ResentLook );
		}
	}
}

HTvoid CHTCamera::HT_vCamera_LookEyeUpdate( HTfloat fAngle, HTfloat fElapsedTime )
{
	switch( m_iCamera_Type )
	{
		case CAMERATYPE_EYE_DEFINECAMERA :
			break;
		case CAMERATYPE_EYE_STRAIGHTMOVE :
		case CAMERATYPE_EYE_LINEMOVE :
			HT_vUpdata_GoStraightControl( fElapsedTime );
			break;
		case CAMERATYPE_EYE_CENTERCHARACTER :
			HT_vUpdateEye_CenterCharacter( m_vPosCharacter );
			HT_vUpdateLook_CenterCharacter( m_vPosCharacter );
			break;
		case CAMERATYPE_EYE_BACKVIEW :
			HT_vUpdateEye_BackView( m_vPosCharacter, fAngle );
			HT_vUpdateLook_BackView( m_vPosCharacter, fAngle );
			break;
		case CAMERATYPE_EYE_FRONTVIEW :
			HT_vUpdateEye_FrontView( m_vPosCharacter, fAngle );
			HT_vUpdateLook_FrontView( m_vPosCharacter, fAngle );
			break;
		case CAMERATYPE_EYE_FOLLOWWEAPON :
			HT_vUpdata_FollowWeaponControl();
			break;
		case CAMERATYPE_EYE_DEATH :
			HT_vUpdataEye_Death();
			HT_vUpdateLook_CenterCharacter( m_vPosCharacter );
			break;
		case CAMERATYPE_EYE_STARTGAMEPLAY :
			HT_vUpdataEye_StartGamePlay();
			HT_vUpdataLook_StartGamePlay();
            break;
	}
}

//----------메인게임에서 카메라 바꾸기----------//
HTvoid CHTCamera::HT_vCamera_TransView( HTint iKey )
{
	if( iKey == 12 )
	{
		if( m_iCameraMode == CAMERATYPE_LOOK_CENTERCHARACTER )
		{
			m_iCameraMode	= CAMERATYPE_LOOK_BACKVIEW;
			m_iCamera_Type	= CAMERATYPE_EYE_BACKVIEW;

			HT_vUpdateEye_SetCameraType( m_iCameraMode, m_vCamera_ResentEye, 1, 0.90f );
			HT_vUpdateLook_SetCameraType( m_iCameraMode, m_vCamera_ResentLook, 1, 0.90f );
		}
		else if( m_iCameraMode == CAMERATYPE_LOOK_BACKVIEW ||
			     m_iCameraMode == CAMERATYPE_LOOK_FRONTVIEW )
		{
			m_iCameraMode		= CAMERATYPE_LOOK_CENTERCHARACTER;
			m_iCamera_Type	= CAMERATYPE_EYE_CENTERCHARACTER;

			HT_vUpdateEye_SetCameraType( m_iCameraMode, m_vCamera_ResentEye, 1, 0.90f );
			HT_vUpdateLook_SetCameraType( m_iCameraMode, m_vCamera_ResentLook, 1, 0.90f );
		}
	}
}

//------------각도를 회전시키기---------------//
HTvoid CHTCamera::HT_vCameraAngleTransing()
{
	if ( g_cMainCharacter )	m_fTransDirect = g_cMainCharacter->HT_fMainChar_GetShowAngle();
}

//----------카메라 줌 인/아웃,로테이트,업다운 컨트롤 함수들----------//
//----------셋팅_인풋 스위치----------//
HTvoid CHTCamera::HT_vCamera_Initialize()
{
	m_bCameraInput_Sw = HT_FALSE;
	POINT ptCursPoint;
	ptCursPoint.x = 0;
	ptCursPoint.y = 0;
	ClientToScreen( g_hWnd, &ptCursPoint );
}

HTvoid CHTCamera::HT_vCamera_SetInput_On( HTPoint pPt )
{
//	ShowCursor( false );
	m_pSourceMousePt.x = m_pMemoryMousePt.x = pPt.x;
	m_pSourceMousePt.y = m_pMemoryMousePt.y = pPt.y;
	m_bCameraInput_Sw = HT_TRUE;

}

HTvoid CHTCamera::HT_vCamera_SetInput_Off()
{
//	ShowCursor( true );
	m_bCameraInput_Sw = HT_FALSE;
	POINT ptCursPoint;
	ptCursPoint.x = 0;
	ptCursPoint.y = 0;
	ClientToScreen( g_hWnd, &ptCursPoint );
	SetCursorPos( ptCursPoint.x+m_pSourceMousePt.x, ptCursPoint.y+m_pSourceMousePt.y );
}

HTbool CHTCamera::HT_vCamera_GetInputSw()
{
	return m_bCameraInput_Sw;
}

//----------셋팅_줌인/아웃----------//
HTvoid CHTCamera::HT_vCamera_ZoomInAndOut( HTint nType, HTfloat fElapsedTime )
{
	if( nType < 0 )
	{
		// 20030304Tenma_test
		//----------셋팅_줌인/아웃----------//
		HT_vCamera_ZoomInAndOutTrans( fElapsedTime*100.0f );
	}
	else if( nType > 0 )
	{
		// 20030304Tenma_test
		//----------셋팅_줌인/아웃----------//
		HT_vCamera_ZoomInAndOutTrans( -(fElapsedTime*100.0f) );
	}
}

//----------셋팅_업/다운/회전----------//
HTvoid CHTCamera::HT_vCamera_SetUpDownRotate( HTPoint pPt, HTfloat fElapsedTime )
{
	// 조절하는 마우스 위치가 변하지 않았으면 업데이트하지 않음
	if( pPt.x == m_pMemoryMousePt.x && pPt.y == m_pMemoryMousePt.y ) return;

	HTfloat fWidth = (HTfloat)( pPt.x - m_pMemoryMousePt.x );
    HTfloat fHight = (HTfloat)( pPt.y - m_pMemoryMousePt.y );
	fHight =  ( 0.12f * ( fHight/50 ) );
	fWidth =  ( 0.15f * ( fWidth/50 ) );

	POINT ptCursPoint;
	ptCursPoint.x = 0;
	ptCursPoint.y = 0;
	ClientToScreen( g_hWnd, &ptCursPoint );
	SetCursorPos( ptCursPoint.x+m_pSourceMousePt.x, ptCursPoint.y+m_pSourceMousePt.y );

	if( fHight > 0 )
	{
		//----------셋팅_업/다운----------//
		HT_vCamera_SetUpDown( fHight );
	}
	else if( fHight < 0 )
	{
		//----------셋팅_업/다운----------//
		HT_vCamera_SetUpDown( fHight );
	}

	if( fWidth > 0 )
	{
		//----------셋팅_회전----------//
		HT_vCamera_SetRotate( fWidth );
	}
	else if( fWidth < 0 )
	{
		//----------셋팅_회전----------//
		HT_vCamera_SetRotate( fWidth );
	}
}

//----------셋팅_줌인/아웃----------//
HTvoid CHTCamera::HT_vCamera_ZoomInAndOutTrans( HTfloat fElapsedTime )
{
	m_fEyeLookDistance += fElapsedTime;

	if( m_fEyeLookDistance > 150 )
	{
		m_fEyeLookDistance			= 150;
		m_fCamera_CharCorrectHeight = 0.0f;
	}
	else
	{
		if( m_fEyeLookDistance < m_fCamera_CharHeight )
		{
			m_fEyeLookDistance = m_fCamera_CharHeight;
		}
	}

	m_fZoomINOut	= m_fEyeLookDistance * sinf(m_fEyeLookAngle);
	m_fCameraUpDown = m_fEyeLookDistance * cosf(m_fEyeLookAngle);

	//----------셋팅_줌인/아웃 고려해야 할 여러가지 사항----------//
    this->HT_vCamera_ZoomInAndOutTrans_Check();
}

//----------셋팅_줌인/아웃 고려해야 할 여러가지 사항----------//
HTvoid CHTCamera::HT_vCamera_ZoomInAndOutTrans_Check()
{
	//	캐릭터를 중심으로 카메라의 위치를 구하고
	HTvector3 vecPos = g_cMainCharacter->HT_vecGetPosition();
	vecPos = HTvector3( vecPos.x+( m_fZoomINOut*sinf(m_fCameraAngle) ), vecPos.y+m_fCameraUpDown, vecPos.z+( m_fZoomINOut*cosf(m_fCameraAngle) ) );
	//	지면의 높이를 구하고
	HTfloat	fy = g_pEngineHandler->HT_fGetTerrainHeight( vecPos.x, vecPos.z );

	HTint nLoopCount = 0;
	HTfloat fConnectHight = ( m_fEyeLookDistance-20 ) * 0.07f;
	while( vecPos.y < fy + fConnectHight && nLoopCount<10 )
	{
		nLoopCount++;
		m_fEyeLookAngle +=0.01f;
		if( m_fEyeLookAngle >= HT_PIX2-0.2f )
			m_fEyeLookAngle = HT_PIX2-0.2f;
			
		m_fZoomINOut	= m_fEyeLookDistance * sinf(m_fEyeLookAngle);
		m_fCameraUpDown = m_fEyeLookDistance * cosf(m_fEyeLookAngle);
	}
}

//----------셋팅_업/다운----------//
HTvoid CHTCamera::HT_vCamera_SetUpDown( HTfloat fValue )
{
	m_fEyeLookAngle				+= fValue;
	m_fCamera_CharCorrectHeight	= 0.0f;

	if( m_fEyeLookAngle >= HT_PIX2-0.2f )
	{
		m_fEyeLookAngle = HT_PIX2-0.2f;
		m_fCamera_CharCorrectHeight = 0.0f;
		return;
	}
	else if( m_fEyeLookAngle > 0 && m_fEyeLookAngle < HT_PIX2-0.2f )
	{
		m_fCamera_CharCorrectHeight = (m_fCamera_CharHeight) - (m_fEyeLookAngle*((m_fCamera_CharHeight)/(5.7f)));
		if( m_fCamera_CharCorrectHeight > 0 )
		{
            m_fCamera_CharCorrectHeight *= 3.0f;
		}
	}

	//----------셋팅_업/다운시에 고려해야 할 여러가지 사항----------//
	HT_vUpdateEye_UpDownTerrainCheck( fValue );

	m_fZoomINOut	= m_fEyeLookDistance * sinf(m_fEyeLookAngle);
	m_fCameraUpDown = m_fEyeLookDistance * cosf(m_fEyeLookAngle);
}

//----------셋팅_업/다운시에 고려해야 할 여러가지 사항----------//
HTvoid CHTCamera::HT_vUpdateEye_UpDownTerrainCheck( HTfloat fValue )
{
	HTvector3 vecPos = g_cMainCharacter->HT_vecGetPosition();
	HTfloat fTempCameraUpDown = m_fEyeLookDistance * cosf(m_fEyeLookAngle);
	vecPos = HTvector3( vecPos.x+( m_fZoomINOut*sinf(m_fCameraAngle) ), vecPos.y+fTempCameraUpDown, vecPos.z+( m_fZoomINOut*cosf(m_fCameraAngle) ) );
	HTfloat	fy = g_pEngineHandler->HT_fGetTerrainHeight( vecPos.x, vecPos.z );

	HTfloat fConnectHight = ( m_fEyeLookDistance-20 ) * 0.07f;
	if( vecPos.y < fy + fConnectHight )
	{
		if( fValue < 0 )	fValue *= -1;
		m_fEyeLookAngle += fValue;
		//----------셋팅_줌인/아웃----------//
		HT_vCamera_ZoomInAndOutTrans( -100*fValue );
	}
}


//----------셋팅_회전----------//
HTvoid CHTCamera::HT_vCamera_SetRotate( HTfloat fValue )
{
	m_fCameraAngle += fValue;

	if( m_fCameraAngle >= HT_PIX2+HT_PI )
		m_fCameraAngle = HT_PI;
	else if( m_fCameraAngle <= HT_PI )
		m_fCameraAngle = HT_PIX2+HT_PI;
}

//----------셋팅_게임 시작전에 초기 카메라 위치 셋팅----------//
HTvoid CHTCamera::HT_vCamera_SetInitMainGameCamera()
{
    m_fEyeLookDistance				= 122.0f;
	m_fEyeLookAngle					= 5.2f;//5.13f;
	m_fZoomINOut					= 100.0f;//-91.58f;
	m_fCameraUpDown					= 70.0f;//40.15f;
	m_fCameraAngle					= HT_PI;
	m_vCamera_STraightSw			= HT_FALSE;
	m_fCamera_STraightHight			= 10.0f;
}

//----------반환----------//
//------------카메라 모드를 리턴---------------//
HTint CHTCamera::HT_nCamera_GetCameraTypeEye()
{
    return m_iCamera_Type;
}

//----------카메라의 각도----------//
HTfloat CHTCamera::HT_vCamera_GetAngle()
{
	if( m_iCamera_Type == CAMERATYPE_EYE_BACKVIEW ||
		m_iCamera_Type == CAMERATYPE_EYE_FRONTVIEW )
        return m_fTransDirect;
	else
        return m_fCameraAngle;
}

//----------카메라 눈의 위치----------//
HTvoid CHTCamera::HT_vCamera_GetEyePosition( HTvector3* vPos )
{
	*vPos = m_vCamera_ResentEye;
}

//----------카메라의 변화값----------//
HTfloat CHTCamera::HT_vCamera_GetTransValue()
{
	return m_vCamera_TransValueEye;
}

//	카메라 초기값 셋팅
HTvoid CHTCamera::HT_vCamera_SetInitCameraMode()
{
	m_fEyeLookDistance				= 100.0f;
	m_fEyeLookAngle					= 5.3f;
	m_fZoomINOut					= 100.0f;
	m_fCameraUpDown					= 100.0f;
	m_fCameraAngle					= HT_PI;
	m_vCamera_STraightSw			= HT_FALSE;
	m_fCamera_STraightHight			= 10.0f;

	m_fTransDirect					= HT_PI;
	m_iCameraMode					= CAMERATYPE_LOOK_CENTERCHARACTER;

	//	카메라 게임 스타트 연출
	HTvector3 vecPos = g_cMainCharacter->HT_vecGetPosition();
	this->HT_vUpdateEye_SetCameraType( CAMERATYPE_LOOK_CENTERCHARACTER, vecPos, 1, 0.7f);
	vecPos.x += 0.0f;
	vecPos.y += 70.0f; 
	vecPos.z += 100;
	this->HT_vUpdateLook_SetCameraType( CAMERATYPE_EYE_CENTERCHARACTER, vecPos, 1, 0.7f);
}

//-----------------------------------------------------------------------------//
//  Eye쪽 컨트롤
//-----------------------------------------------------------------------------//
//------------카메라 액션을 셋팅---------------//
HTvoid CHTCamera::HT_vUpdateEye_SetCameraType( HTint iType, HTvector3 vPos, HTfloat fValue, HTfloat fGrade )
{
	m_iCamera_Type = iType;
	m_vCamera_StartEye = m_vCamera_ResentEye;
	m_vCamera_EndEye = vPos;

	m_vCamera_TransValueEye = fValue;
	m_vCamera_TransGradeEye = fGrade;

	if( m_iCamera_Type == CAMERATYPE_EYE_STRAIGHTMOVE )
	{
		m_vCamera_STraightCount = 0;
		m_vCamera_STraightSw = HT_FALSE;
	}

	//	카메라 각도및 위치 보정
	if( g_bMainCharacterInitialized )
	{
		//m_fCameraAngle = HT_PIX2;
		HT_vCamera_ZoomInAndOut( 1, 0.0f );
	}

	//	카메라 이동상황을 체크해줌
	g_bCameraMove = HT_TRUE;
}

//------------카메라 Eye의 위치를 셋팅---------------//
HTvoid CHTCamera::HT_vUpdateEye_SetPositon( HTvector3 vPos )
{
	m_vCamera_ResentEye = vPos;
}

//------------변화값 변화---------------//
HTvoid CHTCamera::HT_vUpdateEye_TransValueEye()
{
	if( m_vCamera_TransValueEye == 0.0f )
		return;

	if( m_iCamera_Type == CAMERATYPE_EYE_LINEMOVE )
		m_vCamera_TransValueEye -= m_vCamera_TransGradeEye;
	else
        m_vCamera_TransValueEye *= m_vCamera_TransGradeEye;
	
	if( m_vCamera_TransValueEye <= 0.01f )
	{
		m_vCamera_TransValueEye = 0.0f;
	}
}

//------------직선이동을 하는 카메라---------------//
HTvoid CHTCamera::HT_vUpdateEye_StraightMove( HTfloat fElapsedTime )
{
	//if( m_vCamera_TransValueEye == 0.0f )
	//	return;

	//HTfloat fVel = 1 - ( fElapsedTime*(m_vCamera_TransGradeEye*3.0f) );//m_vCamera_TransGradeEye
	//if( fVel >= 0.95f )
	//	fVel = 0.95f;
 //   else if( fVel <= 0.55f )
	//	fVel = 0.55f;
	//m_vCamera_TransValueEye *= fVel;

	this->HT_vUpdateEye_TransValueEye();

	if( m_vCamera_TransValueEye <= 0.0f )
	{
		m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
		m_vCamera_STraightSw = HT_FALSE;
		HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_DEFINECAMERA, m_vCamera_ResentLook, 0, 0.0f );
		HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_DEFINECAMERA, m_vCamera_ResentEye, 0, 0.0f );
		//	카메라 이동상황을 체크해줌
		g_bCameraMove = HT_FALSE;
	}
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------캐릭터 중심적인 카메라(쿼터뷰)---------------//
HTvoid CHTCamera::HT_vUpdateEye_CenterCharacter( HTvector3 vPos )
{
	HT_vUpdateEye_TransValueEye();
	m_vCamera_EndEye = HTvector3( vPos.x+( m_fZoomINOut*sinf(m_fCameraAngle) ), vPos.y+m_fCameraUpDown, vPos.z+( m_fZoomINOut*cosf(m_fCameraAngle) ) );
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------캐릭터의 뒤에서---------------//
HTvoid CHTCamera::HT_vUpdateEye_BackView( HTvector3 vPos, HTfloat fAngle )
{
	HT_vUpdateEye_TransValueEye();
	m_vCamera_EndEye = HTvector3( vPos.x+(m_fZoomINOut*sinf(m_fTransDirect)), vPos.y+m_fCameraUpDown, vPos.z+(m_fZoomINOut*cosf(m_fTransDirect)));
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------캐릭터의 앞에서---------------//
HTvoid CHTCamera::HT_vUpdateEye_FrontView( HTvector3 vPos, HTfloat fAngle )
{
	HT_vUpdateEye_TransValueEye();
	m_vCamera_EndEye = HTvector3( vPos.x+(sinf(m_fTransDirect)), vPos.y+(m_fCamera_CharHalfHeight*1.5f), vPos.z+(cosf(m_fTransDirect)));
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------날아가는 무기 따라가기---------------//
HTvoid CHTCamera::HT_vUpdataEye_FollowWeapon( HTvector3 vecPos )
{
	HT_vUpdateEye_TransValueEye();
	m_vCamera_EndEye = vecPos;
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------캐릭터가 죽었을때---------------//
HTvoid CHTCamera::HT_vUpdataEye_Death()
{
	HT_vUpdateEye_TransValueEye();
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------게임 처음 시작할 때---------------//
HTvoid CHTCamera::HT_vUpdataEye_StartGamePlay()
{
	HT_vUpdateEye_TransValueEye();
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );

	if( m_vCamera_TransValueEye < 0.1f )
	{
		g_CGame->HT_vSetStartMainGamePlay();
	}
}

//-----------------------------------------------------------------------------//
//  Look쪽 컨트롤
//-----------------------------------------------------------------------------//
//------------카메라 액션을 셋팅---------------//
HTvoid CHTCamera::HT_vUpdateLook_SetCameraType( HTint iType, HTvector3 vPos, HTfloat fValue, HTfloat fGrade )
{
	m_vCamera_StartLook = m_vCamera_ResentLook;
	m_vCamera_EndLook = vPos;

	m_vCamera_TransValueLook = fValue;
	m_vCamera_TransGradeLook = fGrade;

	//	카메라 각도및 위치 보정
	if( g_bMainCharacterInitialized )
        HT_vCamera_ZoomInAndOut( 1, 0.0f );
}

//------------카메라 Look의 위치를 셋팅---------------//
HTvoid CHTCamera::HT_vUpdateLook_SetPositon( HTvector3 vPos )
{
	m_vCamera_ResentLook = vPos;
}

//------------변화값 변화---------------//
HTvoid CHTCamera::HT_vUpdateEye_TransValueLook()
{
	if( m_vCamera_TransValueLook == 0.0f )
		return;

	if( m_iCamera_Type == CAMERATYPE_LOOK_LINEMOVE )
		m_vCamera_TransValueLook -= m_vCamera_TransGradeLook;
	else
        m_vCamera_TransValueLook *= m_vCamera_TransGradeLook;
	
	if( m_vCamera_TransValueLook <= 0.01f )
	{
		m_vCamera_TransValueLook = 0.0f;
	}
}

//------------직선이동을 하는 카메라---------------//
HTvoid CHTCamera::HT_vUpdateLook_StraightMove( HTfloat fElapsedTime )
{
	//if( m_vCamera_TransValueLook == 0.0f )
	//	return;

	//HTfloat fVel = 1 - ( fElapsedTime*(m_vCamera_TransGradeLook*3.0f) );//m_vCamera_TransGradeEye;
	//if( fVel >= 1.0f )
	//	fVel = 0.99f;
	//else if( fVel <= 0.0f )
	//	fVel = 0.01f;
	//m_vCamera_TransValueLook *= fVel;

	this->HT_vUpdateEye_TransValueLook();

	if( m_vCamera_TransValueLook <= 0.01f )
	{
		m_vCamera_TransValueLook = 0.0f;
	}
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}

//------------캐릭터 중심적인 카메라(쿼터뷰)---------------//
HTvoid CHTCamera::HT_vUpdateLook_CenterCharacter( HTvector3 vPos )
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_EndLook = HTvector3( vPos.x, vPos.y+ m_fCamera_CharHalfHeight + m_fCamera_CharCorrectHeight, vPos.z );
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}

//------------캐릭터의 뒤에서---------------//
HTvoid CHTCamera::HT_vUpdateLook_BackView( HTvector3 vPos, HTfloat fAngle )
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_EndLook = HTvector3( vPos.x+sinf(m_fTransDirect), vPos.y+ m_fCamera_CharHalfHeight +m_fCamera_CharCorrectHeight, vPos.z+cosf(m_fTransDirect) );
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}

//------------캐릭터의 앞에서---------------//
HTvoid CHTCamera::HT_vUpdateLook_FrontView( HTvector3 vPos, HTfloat fAngle )
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_EndLook = HTvector3( vPos.x+(30*sinf(m_fTransDirect)), vPos.y+ (m_fCamera_CharHalfHeight*1.6f), vPos.z+(30*cosf(m_fTransDirect)) );
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}

//------------날아가는 무기 따라가기---------------//
HTvoid CHTCamera::HT_vUpdataLook_FollowWeapon( HTvector3 vecPos )
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_EndLook = vecPos;
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}

//------------캐릭터가 죽었을때---------------//
HTvoid CHTCamera::HT_vUpdataLook_Death()
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}

//------------게임 처음 시작할 때---------------//
HTvoid CHTCamera::HT_vUpdataLook_StartGamePlay()
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}



//----------카메라 움직임에 있어서 컨트롤 해야 하는 부분----------//
//------------카메라가 직선방향 이동하는거 체크---------------//
HTvoid CHTCamera::HT_vUpdata_GoStraightControl( HTfloat fElapsedTime )
{
	HT_vUpdateLook_StraightMove( fElapsedTime );
	HT_vUpdateEye_StraightMove( fElapsedTime );
}

//------------날라가는 무기 따라가기---------------//
HTvoid CHTCamera::HT_vUpdata_FollowWeaponControl()
{
	HTvector3 vecFrontPos, vecBackPos;
	if( HT_FAILED( g_cAttackMgr->HT_hrAttackMgr_GetFollowModel( vecFrontPos, vecBackPos ) ) )
	{
		HTvector3 vecPos = g_cMainCharacter->HT_vecGetPosition();
		HT_vUpdateLook_SetCameraType( CAMERATYPE_LOOK_CENTERCHARACTER, g_cMainCharacter->HT_vecGetPosition(), 1.0f, 0.75f );
		HT_vUpdateEye_SetCameraType( CAMERATYPE_EYE_CENTERCHARACTER, g_cMainCharacter->HT_vecGetPosition(), 1.0f, 0.75f );
		return;
	}
	else
	{
		this->HT_vUpdataLook_FollowWeapon( vecFrontPos );
		this->HT_vUpdataEye_FollowWeapon( vecBackPos );
	}
}

//	캐릭터 y값에 따른 카메라 높이 변화_캐릭터가 계단을 이용할때 갑자기 튀는것을 막기위해
HTvoid CHTCamera::HT_vCamera_SetCharHightTrans( HTfloat fCharHight )
{
	m_fCamera_CharMemoryY = fCharHight;
	m_fCamera_CharEndHight = fCharHight;
	m_fCamera_CharHightTrans = 0.0f;
	m_fCamera_CharHightTransValue = 0.80f;
}
HTfloat CHTCamera::HT_vCamera_GetCharHightTrans( HTfloat fCharHight )
{
	//	이전 캐릭터의 높이와 다른지 비교->다르면 차이를 구함
	if( m_fCamera_CharEndHight != fCharHight )
	{
		if( HT_DIFF(m_fCamera_CharEndHight,fCharHight) > 100 )
		{
			m_fCamera_CharHightTerm = fCharHight - m_fCamera_CharEndHight;
			m_fCamera_CharEndHight = fCharHight;
			m_fCamera_CharHightTrans = 0.01f;
		}
		else
		{
			m_fCamera_CharHightTerm = fCharHight - m_fCamera_CharEndHight;
			m_fCamera_CharEndHight = fCharHight;
			m_fCamera_CharHightTrans = 1.0f;
		}
	}

	//	Y값을 변경해야하면 변경
	if( m_fCamera_CharHightTrans > 0.1f )
	{
		m_fCamera_CharHightTrans *= m_fCamera_CharHightTransValue;
		m_fCamera_CharMemoryY = m_fCamera_CharEndHight - (m_fCamera_CharHightTrans * m_fCamera_CharHightTerm);
	}
	else if( m_fCamera_CharHightTrans != 0.0f )
	{
		m_fCamera_CharHightTrans = 0.0f;
		m_fCamera_CharMemoryY = m_fCamera_CharEndHight - (m_fCamera_CharHightTrans * m_fCamera_CharHightTerm);
	}

	return m_fCamera_CharMemoryY;
}


//----------지면과의 연관관계----------//
//----------지면의 아래로 카메라가 내려가지 앉게----------//
HTvector3 CHTCamera::HT_vUpdateLook_TerrainCheck( HTvector3 vPos, HTfloat fHight )
{
	if( g_cMainCharacter->HT_bMainChar_GetSitDownState() )
	{
		vPos.y -= m_fCamera_CharHeight/2;
	}

	return vPos;
}

HTvector3 CHTCamera::HT_vUpdateEye_TerrainCheck( HTvector3 vPos, HTfloat fHight )
{
	//	카메라 Eye의 y 높이
	HTfloat	fy = g_pEngineHandler->HT_fGetTerrainHeight( vPos.x, vPos.z );

	//	캐릭터와 거리를 감안한 카메라 Eye의 y 높이
	m_fCamera_StaticCameraHight = m_fEyeLookDistance * cosf(m_fEyeLookAngle) + m_vPosCharacter.y;

	if( fy < m_fCamera_StaticCameraHight )
	{
		m_fCameraUpDown = m_fEyeLookDistance * cosf(m_fEyeLookAngle);
		return vPos;
	}
	//	fy값이 터무니 없이 높이 놔왔다면 여기서 200.0f는 임의적인 값
	else if( fy > m_fCamera_StaticCameraHight+100.0f )
	{
		m_fCameraUpDown = m_fEyeLookDistance * cosf(m_fEyeLookAngle);
		vPos.y = m_fCamera_StaticCameraHight;
		return vPos;
	}

	HTfloat fConnectHight = m_fEyeLookDistance * 0.07f;
	//	카메락 지형의 아래로 내려갔는지 체크
	//	안내려갔으면 그래도 리턴
	if( fy + fConnectHight < vPos.y )
	{
		return vPos;
	}
	//	내려갔으면 보정해줌
	else
	{
		vPos.y = fy + fConnectHight;
		return vPos;
	}
}

