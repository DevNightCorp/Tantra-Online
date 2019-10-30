
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

	// ó������ �� Ȱ��ȭ ���·� �Ѵ�.
	HT_vCamera_Initialize();

	return HT_OK;
}

//----------���ΰ��� ������ �ѹ��� ������Ʈ----------//
HTvoid CHTCamera::HT_vCamera_SetOneTimeInit( HTfloat fChrHight )
{
	m_fCamera_CharHeight		= g_pEngineHandler->HT_fGetObjHeight( g_cMainCharacter->HT_vMainChar_GetModelID() )+5;
	m_fCamera_CharHalfHeight	= m_fCamera_CharHeight/2;
	m_fCamera_CharCorrectHeight	= 0.0f;
	//	ĳ���� y���� ���� ī�޶� ���� ��ȭ_ĳ���Ͱ� ����� �̿��Ҷ� ���ڱ� Ƣ�°��� ��������
	this->HT_vCamera_SetCharHightTrans( fChrHight );
}

//------------ī�޶� ��ü���� ��Ʈ���� ���---------------//
HTvoid CHTCamera::HT_vCameraUpdate( HTvector3 vecCharPos, HTfloat fAngle, HTfloat fElapsedTime )
{
	HTvector3 vecTempPos = m_vCamera_ResentEye;
	m_vPosCharacter.x = vecCharPos.x;
	m_vPosCharacter.z = vecCharPos.z;
	if( m_iCameraMode == CAMERATYPE_EYE_CENTERCHARACTER || m_iCameraMode == CAMERATYPE_EYE_BACKVIEW || m_iCameraMode == CAMERATYPE_EYE_FRONTVIEW )
        m_vPosCharacter.y = HT_vCamera_GetCharHightTrans( vecCharPos.y );
	else
		m_vPosCharacter.y = vecCharPos.y;

	//------------ī�޶� �ޱ� üũ---------------//
	if( m_iCameraMode == CAMERATYPE_EYE_BACKVIEW ||
		m_iCameraMode == CAMERATYPE_EYE_FRONTVIEW )
	{
		this->HT_vCameraAngleTransing();
	}

	//------------ī�޶� Look/Eye�� �׼�---------------//
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

			//----------������ �Ʒ��� ī�޶� �������� �ɰ�----------//
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

//----------���ΰ��ӿ��� ī�޶� �ٲٱ�----------//
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

//------------������ ȸ����Ű��---------------//
HTvoid CHTCamera::HT_vCameraAngleTransing()
{
	if ( g_cMainCharacter )	m_fTransDirect = g_cMainCharacter->HT_fMainChar_GetShowAngle();
}

//----------ī�޶� �� ��/�ƿ�,������Ʈ,���ٿ� ��Ʈ�� �Լ���----------//
//----------����_��ǲ ����ġ----------//
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

//----------����_����/�ƿ�----------//
HTvoid CHTCamera::HT_vCamera_ZoomInAndOut( HTint nType, HTfloat fElapsedTime )
{
	if( nType < 0 )
	{
		// 20030304Tenma_test
		//----------����_����/�ƿ�----------//
		HT_vCamera_ZoomInAndOutTrans( fElapsedTime*100.0f );
	}
	else if( nType > 0 )
	{
		// 20030304Tenma_test
		//----------����_����/�ƿ�----------//
		HT_vCamera_ZoomInAndOutTrans( -(fElapsedTime*100.0f) );
	}
}

//----------����_��/�ٿ�/ȸ��----------//
HTvoid CHTCamera::HT_vCamera_SetUpDownRotate( HTPoint pPt, HTfloat fElapsedTime )
{
	// �����ϴ� ���콺 ��ġ�� ������ �ʾ����� ������Ʈ���� ����
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
		//----------����_��/�ٿ�----------//
		HT_vCamera_SetUpDown( fHight );
	}
	else if( fHight < 0 )
	{
		//----------����_��/�ٿ�----------//
		HT_vCamera_SetUpDown( fHight );
	}

	if( fWidth > 0 )
	{
		//----------����_ȸ��----------//
		HT_vCamera_SetRotate( fWidth );
	}
	else if( fWidth < 0 )
	{
		//----------����_ȸ��----------//
		HT_vCamera_SetRotate( fWidth );
	}
}

//----------����_����/�ƿ�----------//
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

	//----------����_����/�ƿ� ����ؾ� �� �������� ����----------//
    this->HT_vCamera_ZoomInAndOutTrans_Check();
}

//----------����_����/�ƿ� ����ؾ� �� �������� ����----------//
HTvoid CHTCamera::HT_vCamera_ZoomInAndOutTrans_Check()
{
	//	ĳ���͸� �߽����� ī�޶��� ��ġ�� ���ϰ�
	HTvector3 vecPos = g_cMainCharacter->HT_vecGetPosition();
	vecPos = HTvector3( vecPos.x+( m_fZoomINOut*sinf(m_fCameraAngle) ), vecPos.y+m_fCameraUpDown, vecPos.z+( m_fZoomINOut*cosf(m_fCameraAngle) ) );
	//	������ ���̸� ���ϰ�
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

//----------����_��/�ٿ�----------//
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

	//----------����_��/�ٿ�ÿ� ����ؾ� �� �������� ����----------//
	HT_vUpdateEye_UpDownTerrainCheck( fValue );

	m_fZoomINOut	= m_fEyeLookDistance * sinf(m_fEyeLookAngle);
	m_fCameraUpDown = m_fEyeLookDistance * cosf(m_fEyeLookAngle);
}

//----------����_��/�ٿ�ÿ� ����ؾ� �� �������� ����----------//
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
		//----------����_����/�ƿ�----------//
		HT_vCamera_ZoomInAndOutTrans( -100*fValue );
	}
}


//----------����_ȸ��----------//
HTvoid CHTCamera::HT_vCamera_SetRotate( HTfloat fValue )
{
	m_fCameraAngle += fValue;

	if( m_fCameraAngle >= HT_PIX2+HT_PI )
		m_fCameraAngle = HT_PI;
	else if( m_fCameraAngle <= HT_PI )
		m_fCameraAngle = HT_PIX2+HT_PI;
}

//----------����_���� �������� �ʱ� ī�޶� ��ġ ����----------//
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

//----------��ȯ----------//
//------------ī�޶� ��带 ����---------------//
HTint CHTCamera::HT_nCamera_GetCameraTypeEye()
{
    return m_iCamera_Type;
}

//----------ī�޶��� ����----------//
HTfloat CHTCamera::HT_vCamera_GetAngle()
{
	if( m_iCamera_Type == CAMERATYPE_EYE_BACKVIEW ||
		m_iCamera_Type == CAMERATYPE_EYE_FRONTVIEW )
        return m_fTransDirect;
	else
        return m_fCameraAngle;
}

//----------ī�޶� ���� ��ġ----------//
HTvoid CHTCamera::HT_vCamera_GetEyePosition( HTvector3* vPos )
{
	*vPos = m_vCamera_ResentEye;
}

//----------ī�޶��� ��ȭ��----------//
HTfloat CHTCamera::HT_vCamera_GetTransValue()
{
	return m_vCamera_TransValueEye;
}

//	ī�޶� �ʱⰪ ����
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

	//	ī�޶� ���� ��ŸƮ ����
	HTvector3 vecPos = g_cMainCharacter->HT_vecGetPosition();
	this->HT_vUpdateEye_SetCameraType( CAMERATYPE_LOOK_CENTERCHARACTER, vecPos, 1, 0.7f);
	vecPos.x += 0.0f;
	vecPos.y += 70.0f; 
	vecPos.z += 100;
	this->HT_vUpdateLook_SetCameraType( CAMERATYPE_EYE_CENTERCHARACTER, vecPos, 1, 0.7f);
}

//-----------------------------------------------------------------------------//
//  Eye�� ��Ʈ��
//-----------------------------------------------------------------------------//
//------------ī�޶� �׼��� ����---------------//
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

	//	ī�޶� ������ ��ġ ����
	if( g_bMainCharacterInitialized )
	{
		//m_fCameraAngle = HT_PIX2;
		HT_vCamera_ZoomInAndOut( 1, 0.0f );
	}

	//	ī�޶� �̵���Ȳ�� üũ����
	g_bCameraMove = HT_TRUE;
}

//------------ī�޶� Eye�� ��ġ�� ����---------------//
HTvoid CHTCamera::HT_vUpdateEye_SetPositon( HTvector3 vPos )
{
	m_vCamera_ResentEye = vPos;
}

//------------��ȭ�� ��ȭ---------------//
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

//------------�����̵��� �ϴ� ī�޶�---------------//
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
		//	ī�޶� �̵���Ȳ�� üũ����
		g_bCameraMove = HT_FALSE;
	}
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------ĳ���� �߽����� ī�޶�(���ͺ�)---------------//
HTvoid CHTCamera::HT_vUpdateEye_CenterCharacter( HTvector3 vPos )
{
	HT_vUpdateEye_TransValueEye();
	m_vCamera_EndEye = HTvector3( vPos.x+( m_fZoomINOut*sinf(m_fCameraAngle) ), vPos.y+m_fCameraUpDown, vPos.z+( m_fZoomINOut*cosf(m_fCameraAngle) ) );
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------ĳ������ �ڿ���---------------//
HTvoid CHTCamera::HT_vUpdateEye_BackView( HTvector3 vPos, HTfloat fAngle )
{
	HT_vUpdateEye_TransValueEye();
	m_vCamera_EndEye = HTvector3( vPos.x+(m_fZoomINOut*sinf(m_fTransDirect)), vPos.y+m_fCameraUpDown, vPos.z+(m_fZoomINOut*cosf(m_fTransDirect)));
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------ĳ������ �տ���---------------//
HTvoid CHTCamera::HT_vUpdateEye_FrontView( HTvector3 vPos, HTfloat fAngle )
{
	HT_vUpdateEye_TransValueEye();
	m_vCamera_EndEye = HTvector3( vPos.x+(sinf(m_fTransDirect)), vPos.y+(m_fCamera_CharHalfHeight*1.5f), vPos.z+(cosf(m_fTransDirect)));
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------���ư��� ���� ���󰡱�---------------//
HTvoid CHTCamera::HT_vUpdataEye_FollowWeapon( HTvector3 vecPos )
{
	HT_vUpdateEye_TransValueEye();
	m_vCamera_EndEye = vecPos;
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------ĳ���Ͱ� �׾�����---------------//
HTvoid CHTCamera::HT_vUpdataEye_Death()
{
	HT_vUpdateEye_TransValueEye();
	m_vCamera_ResentEye = ( m_vCamera_TransValueEye*m_vCamera_StartEye ) + ( (1-m_vCamera_TransValueEye)*m_vCamera_EndEye );
}

//------------���� ó�� ������ ��---------------//
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
//  Look�� ��Ʈ��
//-----------------------------------------------------------------------------//
//------------ī�޶� �׼��� ����---------------//
HTvoid CHTCamera::HT_vUpdateLook_SetCameraType( HTint iType, HTvector3 vPos, HTfloat fValue, HTfloat fGrade )
{
	m_vCamera_StartLook = m_vCamera_ResentLook;
	m_vCamera_EndLook = vPos;

	m_vCamera_TransValueLook = fValue;
	m_vCamera_TransGradeLook = fGrade;

	//	ī�޶� ������ ��ġ ����
	if( g_bMainCharacterInitialized )
        HT_vCamera_ZoomInAndOut( 1, 0.0f );
}

//------------ī�޶� Look�� ��ġ�� ����---------------//
HTvoid CHTCamera::HT_vUpdateLook_SetPositon( HTvector3 vPos )
{
	m_vCamera_ResentLook = vPos;
}

//------------��ȭ�� ��ȭ---------------//
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

//------------�����̵��� �ϴ� ī�޶�---------------//
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

//------------ĳ���� �߽����� ī�޶�(���ͺ�)---------------//
HTvoid CHTCamera::HT_vUpdateLook_CenterCharacter( HTvector3 vPos )
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_EndLook = HTvector3( vPos.x, vPos.y+ m_fCamera_CharHalfHeight + m_fCamera_CharCorrectHeight, vPos.z );
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}

//------------ĳ������ �ڿ���---------------//
HTvoid CHTCamera::HT_vUpdateLook_BackView( HTvector3 vPos, HTfloat fAngle )
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_EndLook = HTvector3( vPos.x+sinf(m_fTransDirect), vPos.y+ m_fCamera_CharHalfHeight +m_fCamera_CharCorrectHeight, vPos.z+cosf(m_fTransDirect) );
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}

//------------ĳ������ �տ���---------------//
HTvoid CHTCamera::HT_vUpdateLook_FrontView( HTvector3 vPos, HTfloat fAngle )
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_EndLook = HTvector3( vPos.x+(30*sinf(m_fTransDirect)), vPos.y+ (m_fCamera_CharHalfHeight*1.6f), vPos.z+(30*cosf(m_fTransDirect)) );
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}

//------------���ư��� ���� ���󰡱�---------------//
HTvoid CHTCamera::HT_vUpdataLook_FollowWeapon( HTvector3 vecPos )
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_EndLook = vecPos;
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}

//------------ĳ���Ͱ� �׾�����---------------//
HTvoid CHTCamera::HT_vUpdataLook_Death()
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}

//------------���� ó�� ������ ��---------------//
HTvoid CHTCamera::HT_vUpdataLook_StartGamePlay()
{
	HT_vUpdateEye_TransValueLook();
	m_vCamera_ResentLook = ( m_vCamera_TransValueLook*m_vCamera_StartLook ) + ( (1-m_vCamera_TransValueLook)*m_vCamera_EndLook );
}



//----------ī�޶� �����ӿ� �־ ��Ʈ�� �ؾ� �ϴ� �κ�----------//
//------------ī�޶� �������� �̵��ϴ°� üũ---------------//
HTvoid CHTCamera::HT_vUpdata_GoStraightControl( HTfloat fElapsedTime )
{
	HT_vUpdateLook_StraightMove( fElapsedTime );
	HT_vUpdateEye_StraightMove( fElapsedTime );
}

//------------���󰡴� ���� ���󰡱�---------------//
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

//	ĳ���� y���� ���� ī�޶� ���� ��ȭ_ĳ���Ͱ� ����� �̿��Ҷ� ���ڱ� Ƣ�°��� ��������
HTvoid CHTCamera::HT_vCamera_SetCharHightTrans( HTfloat fCharHight )
{
	m_fCamera_CharMemoryY = fCharHight;
	m_fCamera_CharEndHight = fCharHight;
	m_fCamera_CharHightTrans = 0.0f;
	m_fCamera_CharHightTransValue = 0.80f;
}
HTfloat CHTCamera::HT_vCamera_GetCharHightTrans( HTfloat fCharHight )
{
	//	���� ĳ������ ���̿� �ٸ��� ��->�ٸ��� ���̸� ����
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

	//	Y���� �����ؾ��ϸ� ����
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


//----------������� ��������----------//
//----------������ �Ʒ��� ī�޶� �������� �ɰ�----------//
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
	//	ī�޶� Eye�� y ����
	HTfloat	fy = g_pEngineHandler->HT_fGetTerrainHeight( vPos.x, vPos.z );

	//	ĳ���Ϳ� �Ÿ��� ������ ī�޶� Eye�� y ����
	m_fCamera_StaticCameraHight = m_fEyeLookDistance * cosf(m_fEyeLookAngle) + m_vPosCharacter.y;

	if( fy < m_fCamera_StaticCameraHight )
	{
		m_fCameraUpDown = m_fEyeLookDistance * cosf(m_fEyeLookAngle);
		return vPos;
	}
	//	fy���� �͹��� ���� ���� ���Դٸ� ���⼭ 200.0f�� �������� ��
	else if( fy > m_fCamera_StaticCameraHight+100.0f )
	{
		m_fCameraUpDown = m_fEyeLookDistance * cosf(m_fEyeLookAngle);
		vPos.y = m_fCamera_StaticCameraHight;
		return vPos;
	}

	HTfloat fConnectHight = m_fEyeLookDistance * 0.07f;
	//	ī�޶� ������ �Ʒ��� ���������� üũ
	//	�ȳ��������� �׷��� ����
	if( fy + fConnectHight < vPos.y )
	{
		return vPos;
	}
	//	���������� ��������
	else
	{
		vPos.y = fy + fConnectHight;
		return vPos;
	}
}

