

#ifndef __HTCAMERA_H__
#define __HTCAMERA_H__


class CHTCamera
{
public:
	CHTCamera();
	~CHTCamera();

	HTRESULT		HT_CameraInit();

	//----------���ΰ��� ������ �ѹ��� ������Ʈ----------//
	HTvoid			HT_vCamera_SetOneTimeInit( HTfloat fChrHight );


	//----------���ΰ��ӿ��� ī�޶� �ٲٱ�----------//
	HTvoid			HT_vCamera_TransView( HTint iKey );

	//----------ī�޶� �� ��/�ƿ�,������Ʈ,���ٿ� ��Ʈ�� �Լ���----------//
	//----------����_��ǲ ����ġ----------//
	HTvoid			HT_vCamera_Initialize();
	HTvoid			HT_vCamera_SetInput_On( HTPoint pPt );
	HTvoid			HT_vCamera_SetInput_Off();
	HTbool			HT_vCamera_GetInputSw();
	//----------����_����/�ƿ�----------//
	HTvoid			HT_vCamera_ZoomInAndOut( HTint, HTfloat fElapsedTime );
	//----------����_����/�ƿ�----------//
	HTvoid			HT_vCamera_ZoomInAndOutTrans( HTfloat fElapsedTime );
	//----------����_����/�ƿ� ����ؾ� �� �������� ����----------//
	HTvoid			HT_vCamera_ZoomInAndOutTrans_Check();
	//----------����_��/�ٿ�/ȸ��----------//
	HTvoid			HT_vCamera_SetUpDownRotate( HTPoint pPt, HTfloat fElapsedTime );
	//----------����_��/�ٿ�----------//
	HTvoid			HT_vCamera_SetUpDown( HTfloat fValue );
	//----------����_��/�ٿ�ÿ� ����ؾ� �� �������� ����----------//
	HTvoid			HT_vUpdateEye_UpDownTerrainCheck( HTfloat fValue );
	//----------����_ȸ��----------//
	HTvoid			HT_vCamera_SetRotate( HTfloat fValue );

	//----------����_���� �������� �ʱ� ī�޶� ��ġ ����----------//
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

	//	ĳ���� y���� ���� ī�޶� ���� ��ȭ_ĳ���Ͱ� ����� �̿��Ҷ� ���ڱ� Ƣ�°��� ��������
	HTvoid			HT_vCamera_SetCharHightTrans( HTfloat );
	HTfloat		    HT_vCamera_GetCharHightTrans( HTfloat );
	//----------������ �Ʒ��� ī�޶� �������� �ɰ�----------//
	HTvector3		HT_vUpdateLook_TerrainCheck( HTvector3, HTfloat );
	HTvector3		HT_vUpdateEye_TerrainCheck( HTvector3, HTfloat );

	//----------��ȯ----------//
	//----------ī�޶��� ����----------//
	HTfloat			HT_vCamera_GetAngle();
	//----------ī�޶� ���� ��ġ----------//
	HTvoid			HT_vCamera_GetEyePosition( HTvector3* );
	//----------ī�޶��� ��ȭ��----------//
	HTfloat			HT_vCamera_GetTransValue();
	HTfloat			HT_fCamera_GetEyeLookAngle()		{ return m_fEyeLookAngle;	};
	HTfloat			HT_fCamera_GetEyeLookDistance()		{ return m_fEyeLookDistance;	};

	//	ī�޶� �ʱⰪ ����
	HTvoid			HT_vCamera_SetInitCameraMode();
	
private:

	HTbool			m_bCameraInput_Sw;
	HTPoint			m_pMemoryMousePt;
	HTPoint			m_pSourceMousePt;

	HTint			m_iCameraMode;
	HTint			m_iBeforeCameraMode;
	//	ī�޶� Eye�� �ٴڰ��� ����
	HTfloat			m_fCameraUpDown;
	//	Zoon In/Out
	HTfloat			m_fZoomINOut;
	//	ī�޶� Look �� Eye �� �Ÿ�
	HTfloat			m_fEyeLookDistance;
	//	ī�޶� Look �� Eye �� ����
	HTfloat			m_fEyeLookAngle;
	//	y���� �������� �� ī�޶� ����, �Ϲ����� ����϶�
	HTfloat			m_fCameraAngle;
	//	y���� �������� �� ī�޶� ����, ĳ���� �ٷ� �ڿ��� ���󰥶�
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

	//	ī�޶� Look�� y���� ����ϱ� ���� ������
	HTfloat			m_fCamera_CharHeight;
	HTfloat			m_fCamera_CharHalfHeight;
	HTfloat			m_fCamera_CharCorrectHeight;

	HTbool			m_vCamera_STraightSw;
	HTint			m_vCamera_STraightCount;
	HTfloat			m_fCamera_STraightHight;

	HTvector3		m_vPosCharacter;
	
	//	ĳ���� y���� ���� ī�޶� ���� ��ȭ
	HTfloat			m_fCamera_CharMemoryY;
	HTfloat			m_fCamera_CharEndHight;
	HTfloat			m_fCamera_CharHightTerm;
	HTfloat			m_fCamera_CharHightTrans;
	HTfloat			m_fCamera_CharHightTransValue;

	HTfloat			m_fCamera_StaticCameraHight;
};


#endif

