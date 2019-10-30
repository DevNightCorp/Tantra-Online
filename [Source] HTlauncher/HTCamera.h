

#ifndef __HTCAMERA_H__
#define __HTCAMERA_H__


class CHTCamera
{
public:
	CHTCamera();
	~CHTCamera();

	HTRESULT		HT_CameraInit();

	//----------메인게임 돌입후 한번만 업데이트----------//
	HTvoid			HT_vCamera_SetOneTimeInit( HTfloat fChrHight );


	//----------메인게임에서 카메라 바꾸기----------//
	HTvoid			HT_vCamera_TransView( HTint iKey );

	//----------카메라 줌 인/아웃,로테이트,업다운 컨트롤 함수들----------//
	//----------셋팅_인풋 스위치----------//
	HTvoid			HT_vCamera_Initialize();
	HTvoid			HT_vCamera_SetInput_On( HTPoint pPt );
	HTvoid			HT_vCamera_SetInput_Off();
	HTbool			HT_vCamera_GetInputSw();
	//----------셋팅_줌인/아웃----------//
	HTvoid			HT_vCamera_ZoomInAndOut( HTint, HTfloat fElapsedTime );
	//----------셋팅_줌인/아웃----------//
	HTvoid			HT_vCamera_ZoomInAndOutTrans( HTfloat fElapsedTime );
	//----------셋팅_줌인/아웃 고려해야 할 여러가지 사항----------//
	HTvoid			HT_vCamera_ZoomInAndOutTrans_Check();
	//----------셋팅_업/다운/회전----------//
	HTvoid			HT_vCamera_SetUpDownRotate( HTPoint pPt, HTfloat fElapsedTime );
	//----------셋팅_업/다운----------//
	HTvoid			HT_vCamera_SetUpDown( HTfloat fValue );
	//----------셋팅_업/다운시에 고려해야 할 여러가지 사항----------//
	HTvoid			HT_vUpdateEye_UpDownTerrainCheck( HTfloat fValue );
	//----------셋팅_회전----------//
	HTvoid			HT_vCamera_SetRotate( HTfloat fValue );

	//----------셋팅_게임 시작전에 초기 카메라 위치 셋팅----------//
	HTvoid			HT_vCamera_SetInitMainGameCamera();

	HTvoid			HT_vCameraUpdate( HTvector3 vecCharPos, HTfloat fAngle, HTfloat fElapsedTime );
	HTvoid			HT_vCamera_LookEyeUpdate( HTfloat fAngle, HTfloat fElapsedTime );
	HTvoid			HT_vCameraAngleTransing();
	HTint			HT_nCamera_GetCameraTypeEye();

	HTvoid			HT_vUpdateEye_SetCameraType( HTint, HTvector3, HTfloat, HTfloat );
	HTvoid			HT_vUpdateEye_SetPositon( HTvector3 );
	HTvoid			HT_vUpdateEye_TransValueEye();
	HTvoid			HT_vUpdateEye_StraightMove( HTfloat fElapsedTime );
	HTvoid			HT_vUpdateEye_CenterCharacter( HTvector3 );
	HTvoid			HT_vUpdateEye_BackView( HTvector3, HTfloat );
	HTvoid			HT_vUpdateEye_FrontView( HTvector3, HTfloat );
	HTvoid			HT_vUpdataEye_FollowWeapon( HTvector3 );
	HTvoid			HT_vUpdataEye_Death();
	HTvoid			HT_vUpdataEye_StartGamePlay();
	
	HTvoid			HT_vUpdateLook_SetCameraType( HTint, HTvector3, HTfloat, HTfloat );
	HTvoid			HT_vUpdateLook_SetPositon( HTvector3 );
	HTvoid			HT_vUpdateEye_TransValueLook();
	HTvoid			HT_vUpdateLook_StraightMove( HTfloat fElapsedTime );
	HTvoid			HT_vUpdateLook_CenterCharacter( HTvector3 );
	HTvoid			HT_vUpdateLook_BackView( HTvector3, HTfloat );
	HTvoid			HT_vUpdateLook_FrontView( HTvector3, HTfloat );
	HTvoid			HT_vUpdataLook_FollowWeapon( HTvector3 );
	HTvoid			HT_vUpdataLook_Death();
	HTvoid			HT_vUpdataLook_StartGamePlay();

	HTvoid			HT_vUpdata_GoStraightControl( HTfloat fElapsedTime );
	HTvoid			HT_vUpdata_FollowWeaponControl();

	//	캐릭터 y값에 따른 카메라 높이 변화_캐릭터가 계단을 이용할때 갑자기 튀는것을 막기위해
	HTvoid			HT_vCamera_SetCharHightTrans( HTfloat );
	HTfloat		    HT_vCamera_GetCharHightTrans( HTfloat );
	//----------지면의 아래로 카메라가 내려가지 앉게----------//
	HTvector3		HT_vUpdateLook_TerrainCheck( HTvector3, HTfloat );
	HTvector3		HT_vUpdateEye_TerrainCheck( HTvector3, HTfloat );

	//----------반환----------//
	//----------카메라의 각도----------//
	HTfloat			HT_vCamera_GetAngle();
	//----------카메라 눈의 위치----------//
	HTvoid			HT_vCamera_GetEyePosition( HTvector3* );
	//----------카메라의 변화값----------//
	HTfloat			HT_vCamera_GetTransValue();
	HTfloat			HT_fCamera_GetEyeLookAngle()		{ return m_fEyeLookAngle;	};
	HTfloat			HT_fCamera_GetEyeLookDistance()		{ return m_fEyeLookDistance;	};

	//	카메라 초기값 셋팅
	HTvoid			HT_vCamera_SetInitCameraMode();
	
private:

	HTbool			m_bCameraInput_Sw;
	HTPoint			m_pMemoryMousePt;
	HTPoint			m_pSourceMousePt;

	HTint			m_iCameraMode;
	HTint			m_iBeforeCameraMode;
	//	카메라 Eye와 바닥과의 높이
	HTfloat			m_fCameraUpDown;
	//	Zoon In/Out
	HTfloat			m_fZoomINOut;
	//	카메라 Look 와 Eye 의 거리
	HTfloat			m_fEyeLookDistance;
	//	카메라 Look 와 Eye 의 각도
	HTfloat			m_fEyeLookAngle;
	//	y축을 기준으로 한 카메라 각도, 일반적인 모드일때
	HTfloat			m_fCameraAngle;
	//	y축을 기준으로 한 카메라 각도, 캐릭터 바로 뒤에서 따라갈때
	HTfloat			m_fTransDirect;

	HTint			m_iCamera_Type;
	HTvector3		m_vCamera_ResentEye;
	HTvector3		m_vCamera_StartEye;
	HTvector3		m_vCamera_EndEye;
	HTfloat			m_vCamera_TransValueEye;
	HTfloat			m_vCamera_TransGradeEye;

	HTvector3		m_vCamera_ResentLook;
	HTvector3		m_vCamera_StartLook;
	HTvector3		m_vCamera_EndLook;
	HTfloat			m_vCamera_TransValueLook;
	HTfloat			m_vCamera_TransGradeLook;

	//	카메라 Look의 y값을 계산하기 위한 변수들
	HTfloat			m_fCamera_CharHeight;
	HTfloat			m_fCamera_CharHalfHeight;
	HTfloat			m_fCamera_CharCorrectHeight;

	HTbool			m_vCamera_STraightSw;
	HTint			m_vCamera_STraightCount;
	HTfloat			m_fCamera_STraightHight;

	HTvector3		m_vPosCharacter;
	
	//	캐릭터 y값에 따른 카메라 높이 변화
	HTfloat			m_fCamera_CharMemoryY;
	HTfloat			m_fCamera_CharEndHight;
	HTfloat			m_fCamera_CharHightTerm;
	HTfloat			m_fCamera_CharHightTrans;
	HTfloat			m_fCamera_CharHightTransValue;

	HTfloat			m_fCamera_StaticCameraHight;
};


#endif

