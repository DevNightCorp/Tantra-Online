
#include "stdafx.h"
         // 이 헤더를 포함시킨다 (유니코드 처리를 위해)
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTInterface.h"


// 폰트 꾸밈 설정
#define	UI_FONT_NORMAL		0		// 일반 글씨체
#define	UI_FONT_BORD		1		// 굵게
#define	UI_FONT_BORDER		2		// 윤곽선
#define	UI_FONT_SHADOW		3		// 그림자
#define	UI_FONT_NORMAL_NOENTER	4	// 일반 글씨체이나 개행이 안되는 것이 특징

// Texture ID
//#define UI_TEXTURE_NONE						27023	// 흰색 이미지 (내부처리용) IntroUI
//#define UI_TEXTURE_NONE						23899	// 흰색 이미지 (내부처리용) MainUI
#define UI_TEXTURE_REGION					0	// 배경영역으로 사용시
#define UI_TEXTURE_HEIGHT_LINE				1	// 새로선 이미지
#define UI_TEXTURE_WIDTH_LINE				2	// 가로선 이미지
#define UI_TEXTURE_TITLEBAR					3	// 타이틀바
#define	UI_TEXTURE_SCALEBAR_ON				4	// 스케일바
#define UI_TEXTURE_EDGE_BUTTON_NORMAL		5	// 모서리 버튼 (일반)
#define UI_TEXTURE_EDGE_BUTTON_OVER			6	// 모서리 버튼 (오버)
#define UI_TEXTURE_EDGE_BUTTON_DOWN			7	// 모서리 버튼 (다운)
#define UI_TEXTURE_WIDTH_LINE02				8	// 꾸밈이미지
#define UI_TEXTURE_BOX01					9	// 라벨에 사용되는 꾸밈 이미지
#define UI_TEXTURE_BOX02					10
#define UI_TEXTURE_BOX03					11
#define	UI_TEXTURE_SCALEBAR_OFF				12	// 스케일바 Off 상태 이미지
#define UI_TEXTURE_BUTTON04_NORMAL			13	// 상태창등 13*13 버튼 이미지
#define UI_TEXTURE_BUTTON04_OVER			14
#define UI_TEXTURE_BUTTON04_DOWN			15

#define UI_TEXTURE_IMAGE01_SE				16
#define UI_TEXTURE_IMAGE01_NW				17
#define UI_TEXTURE_IMAGE01_NN				18
#define UI_TEXTURE_IMAGE01_NE				19
#define UI_TEXTURE_IMAGE01_EE				20
#define UI_TEXTURE_IMAGE01_SW				21

#define UI_TEXTURE_CURSOR					22	// 커서 이미지

// 윈도우 스케일 조절시 최소 제한 사이즈 설정
#define	UI_MIN_RESIZEX		160
#define UI_MIN_RESIZEY		50

// 툴팁 정의
#define	UI_TOOLTIP_EXTRASIZE_X				20		// 글씨 출력후 여분 사이즈 X
#define	UI_TOOLTIP_EXTRASIZE_Y				10		// 글씨 출력후 여분 사이즈 Y
#define	UI_TOOLTIP_POS_X					20		// 해당 컨트롤로부터 +-되어 출력되는 위치 X
#define	UI_TOOLTIP_POS_Y					20		// 해당 컨트롤로부터 +-되어 출력되는 위치 Y

#define	UI_TOOLTIP_MULTILINE_MAX			35		// 멀티라인 총 갯수
#define	UI_TOOLTIP_HEIGHT_SIZE				14		// 자간 사이즈 설정

// 폰트 종류 설정
#define	UI_MAIN_FONT						HT_FONT_GULIM_12

// 에디터 박스 아이디 정의 
#define	ID_EDIT								100
int				g_Pibot;								// 피봇 위치
bool			g_Shift;								// 쉬프트 눌림상태
bool			g_Control;								// 쉬프트 눌림상태
bool			g_RegionCheck;							// 영역 작동 여부

int				g_EditBoxFocusWindow = 0;				// 포커스 잡혀있는 윈도우 (전역 저장)
int				g_EditBoxFocusControl = 0;				// 포커스 잡혀 있는 컨트롤 (전역 저장)
int				g_EditBoxCursorPosX = 0;
int				g_EditBoxCursorPosY = 0;

// UI 관련 클래스에서 사용하는 구조체
UIResource	g_oUIResource[300];	

//WNDPROC				PreEditProc;			// 서브클래싱 하기위한 메시지 콜백 함수 선언

//
// UI Texture Control Class 맴버 함수를 모아놓았습니다.
//

UITextureControl::UITextureControl()
{
	m_Texture.Layer = 2000;			// 텍스처 기본 정보들
	m_Texture.PosX = 0;				// 텍스처 기본 정보들
	m_Texture.PosY = 0;				// 텍스처 기본 정보들
	m_Texture.SizeX = 0;			// 텍스처 기본 정보들
	m_Texture.SizeY = 0;			// 텍스처 기본 정보들
	m_Texture.TextureID = 0;		// 텍스처 기본 정보들
	m_Texture.VertexClr = HT_COLOR(1,1,1,0);	// 텍스처 기본 정보들
	m_fScale.x = 0;					// 결정된 텍스처 스케일비율
	m_fScale.y = 0;					// 결정된 텍스처 스케일비율
	m_iWidth = 0;					// 실제 텍스처 사이즈X
	m_iHeight = 0;					// 실제 텍스처 사이즈Y
	m_iEObjID = 0;					// Engine으로 부터 부여 받은 텍스처 고유 ID값

	// Process
	RealSizeX = 0;					// Real Output Region Image SizeX
	RealSizeY = 0;					// Real Output Region Image SizeY
	m_bCheckRegion = false;			// 제어 영역에 마우스무브 중인지 여부
	m_bCheckMouseDown = false;		// 제어 영역에 마우스다운 중인지 여부
	m_bCheckMouseRDown = false;		// 제어 영역에 마우스다운 중인지 여부

	m_bEnable = false;				// true = 입력 처리가능 / false = 입력 처리무시
	m_bDisplay = false;				// true = 출력 가능 / false = 출력 안함

	m_nIndex = 0;
}

UITextureControl::~UITextureControl()
{
	if (m_iEObjID == 0) return;

	g_pEngineHandler->HT_vDestroyObject( m_iEObjID, 18);
}

// 윈도우에 출력할 텍스처를 생성합니다.
void UITextureControl::CreateUITextureControl(unsigned int nIndex, UITexture oTexture)
{
	// 입력정보 저장
	m_Texture = oTexture;
	m_nIndex = nIndex;

	// ID가 2만이 넘어가면 클라리소스의 아이디를 사용한다. 그리고 싸이즈는 무조건 32*32로 인식

	// Engine에 등록 요청
	if (m_Texture.TextureID == 0)	
	{
			m_iEObjID = g_pEngineHandler->HT_iCreate2DWindowUISprite( g_oUIResource[m_Texture.TextureID].XMLID, 0, 0, 1, 1, m_Texture.VertexClr );	//픽셀23899
	}
	else
	{
		if (m_Texture.TextureID >= 20000)	
            m_iEObjID = g_pEngineHandler->HT_iCreate2DUISprite( m_Texture.TextureID, HTvector3( 0.0f, 0.0f, 0.0f) ); //이미지
		else
			m_iEObjID = g_pEngineHandler->HT_iCreate2DUISprite( g_oUIResource[m_Texture.TextureID].XMLID, HTvector3( 0.0f, 0.0f, 0.0f) ); //이미지
	}

	if (m_iEObjID < 0)
	{
		m_iWidth		= g_pEngineHandler->HT_iGetWidth(m_iEObjID);
	}

	// 정확한 스케일 적용 및 출력을 위해 원본 사이즈를 알아야 한다.
	m_iWidth		= g_pEngineHandler->HT_iGetWidth(m_iEObjID);
	m_iHeight		= g_pEngineHandler->HT_iGetHeight(m_iEObjID);

	// 출력할 사이즈값을 제대로 입력하지 않으면, 사이즈는 원본과 동일하게 설정된다.
	if (m_Texture.SizeX <= 0.0f || m_Texture.SizeY <= 0.0f)	
	{
		if (m_Texture.TextureID >= HT_ID_UI_MAIN_START && m_Texture.TextureID <= HT_ID_UI_MAIN_END || 
			m_Texture.TextureID >= HT_ID_UI_INTRO_START && m_Texture.TextureID <= HT_ID_UI_INTRO_END)
		{
			m_Texture.SizeX = 32;
			m_Texture.SizeY = 32;
		}
		else if (m_Texture.TextureID <= 1000)
		{
			m_Texture.SizeX = g_oUIResource[m_Texture.TextureID].RealSizeX;
			m_Texture.SizeY = g_oUIResource[m_Texture.TextureID].RealSizeY;
		}
	}

	this->SetScale(m_Texture.SizeX, m_Texture.SizeY);

	// 그외 초기상태 설정
	m_bCheckRegion = false;
	m_bCheckMouseDown = false;
	m_bEnable = true;
	m_bDisplay = true;
}

// 화면상에 텍스처를 출력합니다.
void UITextureControl::Render(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true)
	{
		// 로컬 좌표값에 윈도우 위치값을 더해서 출력한다.
		HTvector3 fPos;
		fPos.x = ( (float) m_Texture.PosX + (float) iWindowPosX );
		fPos.y = ( (float) m_Texture.PosY + (float) iWindowPosY );
		fPos.z = 0.0f;

		g_pEngineHandler->HT_hrScaleObject(m_iEObjID, m_fScale);
		g_pEngineHandler->HT_hrMoveObject(m_iEObjID, fPos);
		g_pEngineHandler->HT_hrRenderObject(m_iEObjID, m_Texture.Layer);

	}
}

// 해당 영역에 마우스가 있는지 검사합니다.
bool UITextureControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// 조건 검사를 위해 로컬 좌표값만을 빼낸다.
	int PosX = iWindowPosX + m_Texture.PosX;
	int PosY = iWindowPosY + m_Texture.PosY;

	if(iXPos >= PosX && iXPos <= PosX + m_Texture.SizeX)
		if (iYPos >= PosY && iYPos <= PosY + m_Texture.SizeY)
			return true;
	return false;
}

// 원하는 위치로 컨트롤을 이동시킵니다.
void UITextureControl::Move(int iXPos, int iYPos, int iType)
{
	m_Texture.PosX = iXPos;
	m_Texture.PosY = iYPos;
}

// 스케일을 설정합니다.
void UITextureControl::SetScale(int iSizeX, int iSizeY, int iOSizeX, int iOSizeY)
{ 
	m_Texture.SizeX = iSizeX;
	m_Texture.SizeY = iSizeY;

	// 스케일 비율 재설정
	if (m_Texture.TextureID >= HT_ID_UI_MAIN_START && m_Texture.TextureID <= HT_ID_UI_MAIN_END || 
		m_Texture.TextureID >= HT_ID_UI_INTRO_START && m_Texture.TextureID <= HT_ID_UI_INTRO_END)
	{
		m_fScale.x = ( (float) m_Texture.SizeX / 32.0f);
		m_fScale.y = ( (float) m_Texture.SizeY / 32.0f);
		m_fScale.z = 0.0f;		// 미사용
	}
	else if (m_Texture.TextureID <= 1000)
	{
		m_fScale.x = ( (float) m_Texture.SizeX / (float) g_oUIResource[m_Texture.TextureID].RealSizeX);
		m_fScale.y = ( (float) m_Texture.SizeY / (float) g_oUIResource[m_Texture.TextureID].RealSizeY);
		m_fScale.z = 0.0f;		// 미사용
	}
	else if (iOSizeX != 1 && iOSizeX != 1)
	{
		m_fScale.x = ( (float) m_Texture.SizeX / (float) iOSizeX);
		m_fScale.y = ( (float) m_Texture.SizeY / (float) iOSizeY);
		m_fScale.z = 1.0f;
	}
	else
	{
		m_fScale.x = 1.0f;
		m_fScale.y = 1.0f;
		m_fScale.z = 1.0f;
	}
}

// 스케일값을 반환합니다.
void UITextureControl::GetScale(int &iSizeX, int &iSizeY)
{
	iSizeX = m_Texture.SizeX;
	iSizeY = m_Texture.SizeY;
}

// 색상을 변경합니다.
void UITextureControl::SetColor(HT_COLOR clr)
{
	g_pEngineHandler->HT_hrChangeColor( m_iEObjID, clr);
}

// UITextureControl의 위치를 반환한다.
HTvector3 UITextureControl::GetUITextureControlPos()
{
	HTvector3 fPos;
	fPos.x = (float)m_Texture.PosX;
	fPos.y = (float)m_Texture.PosY;
	fPos.z = 0.0f;

	return fPos;
}

// 텍스처 모든 정보를 얻어 옵니다.
UITexture UITextureControl::GetUITextureControl()
{
	return m_Texture;
}


//
// UI Label Control Class 맴버 함수를 모아놓았습니다.
//

UILabelControl::UILabelControl()
{
	m_Text.Font = UI_MAIN_FONT;					// Text 정보
	m_Text.FontMode = 0;
	m_Text.strTitle = "";
	m_Text.TextColor = HT_COLOR(1,1,1,1);
	m_Text.TextFormating = TEXT_FORMATING_ONELINE_VCENTER_CENTER_CLIP;
	m_Text.TextPos.bottom = 0;
	m_Text.TextPos.left = 0;
	m_Text.TextPos.right = 0;
	m_Text.TextPos.top = 0;
	m_Text.TextShadowColor = HT_COLOR(1,1,1,1);


	m_bEnable = false;				// true = 입력 처리가능 / false = 입력 처리무시
	m_bDisplay = false;				// true = 출력 가능 / false = 출력 안함

	m_bCheckRegion = false;			// 제어 영역에 마우스무브 중인지 여부
	m_bCheckMouseDown = false;		// 제어 영역에 마우스다운 중인지 여부

	TextPosX = 0;					// 옵션 적용된 최종 텍스트 위치X
	TextPosY = 0;					// 옵션 적용된 최종 텍스트 위치Y
	m_Direction = 0;				// 배치방식
	m_nIndex = 0;				// 컨트롤 고유 인덱스
}

UILabelControl::~UILabelControl()
{
}

// 윈도우에 출력할 텍스처를 생성합니다.
void UILabelControl::CreateUILabelControl(unsigned int nIndex, UIText oText)	// UI Object 생성
{
	// 입력정보 저장
	m_Text = oText;
	m_nIndex = nIndex;

	m_Direction = 5;

	TextPosX = 0; TextPosY = 0;
	SetArrangement(5);					// 문자열을 가운데 배치

	// 그외 초기상태 설정
	m_bCheckRegion = false;
	m_bCheckMouseDown = false;
	m_bEnable = true;
	m_bDisplay = true;
}

// 글자 정렬들에 따른 추가 위치 변경 변수의 값을 설정합니다. (글자 배치 방법 변경시 호출해야합니다.)
void UILabelControl::SetTextArrangement(int iDirection)	
{
	// 먼저 스트링의 문자열 길이를 구해온다.
	int strlength = g_pEngineHandler->HT_iGetTextWidth( m_Text.Font, m_Text.strTitle );

	switch (iDirection)
	{
	case 1:	case 4:	case 7:	TextPosX = 0;	break;
	case 2:	case 5: case 8:	TextPosX = ( m_Text.TextPos.right - strlength) / 2;	break;
	case 3:	case 6:	case 9:	TextPosX = ( m_Text.TextPos.right - strlength);	break;
	default: TextPosX = 0; break;
	}

	switch (iDirection)
	{
	case 7:	case 8:	case 9:	TextPosY = 0; break;
	case 4: case 5: case 6:	TextPosY = ( m_Text.TextPos.bottom - 13) / 2;	break;
	case 1:	case 2:	case 3:	TextPosY = ( m_Text.TextPos.bottom - 13);	break;
	default: TextPosY = 0; break;
	}
}

// 화면상에 텍스처를 출력합니다.
void UILabelControl::Render(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true)
	{
		HT_RECT temp;
		
		// 텍스트 출력 위치 결정
		temp.left = m_Text.TextPos.left + iWindowPosX + TextPosX;
		temp.top =  m_Text.TextPos.top + iWindowPosY + TextPosY;
		temp.right = m_Text.TextPos.left + m_Text.TextPos.right + iWindowPosX;
		temp.bottom = m_Text.TextPos.top + m_Text.TextPos.bottom + iWindowPosY;

		// 원하는 모드로 출력가능
		switch (m_Text.FontMode)
		{
		case UI_FONT_BORD: // 두껍게
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_BORDER: // 외곽선
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left-=2;temp.top++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left+=2;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left-=2;temp.top++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--; temp.top--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_SHADOW: // 그림자
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_NORMAL_NOENTER:	// >>나 엔터기능 안먹히는 일반 글자
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_NORMAL: // 기본 모드
		default:
			{
				float fTextHeight;
				temp.left++; g_pEngineHandler->HT_hrRenderText( m_Text.Font, m_Text.strTitle.HT_szGetString(), HT_COLOR(0,0,0,1), (HTfloat)(temp.left), (HTfloat)(temp.top), (HTfloat)(temp.right - temp.left), 15.0f, &fTextHeight );
				temp.left--; temp.top++; g_pEngineHandler->HT_hrRenderText( m_Text.Font, m_Text.strTitle.HT_szGetString(), HT_COLOR(0,0,0,1), (HTfloat)(temp.left), (HTfloat)(temp.top), (HTfloat)(temp.right - temp.left), 15.0f, &fTextHeight );
				temp.top--; g_pEngineHandler->HT_hrRenderText( m_Text.Font, m_Text.strTitle.HT_szGetString(), m_Text.TextColor, (HTfloat)(temp.left), (HTfloat)(temp.top), (HTfloat)(temp.right - temp.left), 15.0f, &fTextHeight );
			}
			break;
		}
	}
}

// 해당 영역에 마우스가 있는지 검사합니다.
bool UILabelControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// 조건 검사를 위해 로컬 좌표값만을 빼낸다.
	int PosX = iWindowPosX + m_Text.TextPos.left;
	int PosY = iWindowPosY + m_Text.TextPos.top;

	if(iXPos >= PosX && iXPos <= PosX + m_Text.TextPos.right)
		if (iYPos >= PosY && iYPos <= PosY + m_Text.TextPos.bottom)
			return true;
	return false;
}

// 원하는 위치로 컨트롤을 이동시킵니다.
void UILabelControl::Move(int iXPos, int iYPos)
{
	m_Text.TextPos.left = iXPos;
	m_Text.TextPos.top = iYPos;
}

// 텍스트를 재설정 합니다.
void UILabelControl::SetText(CHTString str)
{
	m_Text.strTitle = str;
	SetTextArrangement(m_Direction);	// 문자열을 가운데 배치
}

// UILabelControl의 위치 및 사이즈를 반환한다.
HT_RECT UILabelControl::GetUILabelControlPos()
{
	return m_Text.TextPos;
}

// 글자 출력 영역의 사이즈를 변경합니다.
void UILabelControl::SetScale(int iSizeX, int iSizeY)
{
	m_Text.TextPos.right = iSizeX;
	m_Text.TextPos.bottom = iSizeY;
	SetTextArrangement(m_Direction);	// 문자열을 가운데 배치
}


//
// UI Long Label Control Class 맴버 함수를 모아놓았습니다.
//

UILongLabelControl::UILongLabelControl()
{
	m_Text.Font = UI_MAIN_FONT;					// Text 정보
	m_Text.FontMode = 0;
	m_Text.strTitle[0] = NULL;
	m_Text.TextColor = HT_COLOR(1,1,1,1);
	m_Text.TextFormating = TEXT_FORMATING_ONELINE_VCENTER_CENTER_CLIP;
	m_Text.TextPos.bottom = 0;
	m_Text.TextPos.left = 0;
	m_Text.TextPos.right = 0;
	m_Text.TextPos.top = 0;
	m_Text.TextShadowColor = HT_COLOR(1,1,1,1);


	m_bEnable = false;				// true = 입력 처리가능 / false = 입력 처리무시
	m_bDisplay = false;				// true = 출력 가능 / false = 출력 안함

	m_bCheckRegion = false;			// 제어 영역에 마우스무브 중인지 여부
	m_bCheckMouseDown = false;		// 제어 영역에 마우스다운 중인지 여부

	TextPosX = 0;					// 옵션 적용된 최종 텍스트 위치X
	TextPosY = 0;					// 옵션 적용된 최종 텍스트 위치Y
	m_Direction = 0;				// 배치방식
	m_nIndex = 0;				// 컨트롤 고유 인덱스
}

UILongLabelControl::~UILongLabelControl()
{
}

// 윈도우에 출력할 텍스처를 생성합니다.
void UILongLabelControl::CreateUILabelControl(unsigned int nIndex, UILongText oText)	// UI Object 생성
{
	// 입력정보 저장
	m_Text = oText;
	m_nIndex = nIndex;

	TextPosX = 0; TextPosY = 0;
	SetArrangement(5);					// 문자열을 가운데 배치

	// 그외 초기상태 설정
	m_bCheckRegion = false;
	m_bCheckMouseDown = false;
	m_bEnable = true;
	m_bDisplay = true;
}

// 글자 정렬들에 따른 추가 위치 변경 변수의 값을 설정합니다. (글자 배치 방법 변경시 호출해야합니다.)
void UILongLabelControl::SetTextArrangement(int iDirection)	
{
	// 먼저 스트링의 문자열 길이를 구해온다.
	int strlength = g_pEngineHandler->HT_iGetTextWidth( m_Text.Font, m_Text.strTitle );

	switch (iDirection)
	{
	case 1:	case 4:	case 7:	TextPosX = 0;	break;
	case 2:	case 5: case 8:	TextPosX = ( m_Text.TextPos.right - strlength) / 2;	break;
	case 3:	case 6:	case 9:	TextPosX = ( m_Text.TextPos.right - strlength);	break;
	}

	switch (iDirection)
	{
	case 7:	case 8:	case 9:	TextPosY = 0; break;
	case 4: case 5: case 6:	TextPosY = ( m_Text.TextPos.bottom - 13) / 2;	break;
	case 1:	case 2:	case 3:	TextPosY = ( m_Text.TextPos.bottom - 13);	break;
	}
}

// 화면상에 텍스처를 출력합니다.
void UILongLabelControl::Render(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true)
	{
		HT_RECT temp;
		
		// 텍스트 출력 위치 결정
		temp.left = m_Text.TextPos.left + iWindowPosX + TextPosX;
		temp.top =  m_Text.TextPos.top + iWindowPosY + TextPosY;
		temp.right = m_Text.TextPos.left + m_Text.TextPos.right + iWindowPosX;
		temp.bottom = m_Text.TextPos.top + m_Text.TextPos.bottom + iWindowPosY;

		// 원하는 모드로 출력가능
		switch (m_Text.FontMode)
		{
		case UI_FONT_BORD: // 두껍게
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_BORDER: // 외곽선
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left-=2;temp.top++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left+=2;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left-=2;temp.top++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--; temp.top--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_SHADOW: // 그림자
			temp.left++;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextShadowColor, temp, m_Text.TextFormating);
			temp.left--;
			g_pEngineHandler->HT_hrRenderText(m_Text.Font, m_Text.strTitle, m_Text.TextColor, temp, m_Text.TextFormating);
			break;

		case UI_FONT_NORMAL: // 기본 모드
		default:
			{
				float fTextHeight;
				g_pEngineHandler->HT_hrRenderText( m_Text.Font, m_Text.strTitle, m_Text.TextColor, (HTfloat)(temp.left), (HTfloat)(temp.top), (HTfloat)(temp.right - temp.left), 15.0f, &fTextHeight );
			}
			break;
		}
	}
}

// 해당 영역에 마우스가 있는지 검사합니다.
bool UILongLabelControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// 조건 검사를 위해 로컬 좌표값만을 빼낸다.
	int PosX = iWindowPosX + m_Text.TextPos.left;
	int PosY = iWindowPosY + m_Text.TextPos.top;

	if(iXPos >= PosX && iXPos <= PosX + m_Text.TextPos.right)
		if (iYPos >= PosY && iYPos <= PosY + m_Text.TextPos.bottom)
			return true;
	return false;
}

// 원하는 위치로 컨트롤을 이동시킵니다.
void UILongLabelControl::Move(int iXPos, int iYPos)
{
	m_Text.TextPos.left = iXPos;
	m_Text.TextPos.top = iYPos;
}

// 텍스트를 재설정 합니다.
void UILongLabelControl::SetText(HTtchar str[])
{
	strcpy(m_Text.strTitle, str);
	SetTextArrangement(m_Direction);	// 문자열을 가운데 배치
}

// UILabelControl의 위치 및 사이즈를 반환한다.
HT_RECT UILongLabelControl::GetUILabelControlPos()
{
	return m_Text.TextPos;
}

// 글자 출력 영역의 사이즈를 변경합니다.
void UILongLabelControl::SetScale(int iSizeX, int iSizeY)
{
	m_Text.TextPos.right = iSizeX;
	m_Text.TextPos.bottom = iSizeY;
	SetTextArrangement(m_Direction);	// 문자열을 가운데 배치
}



//
// UIToolTipControl Class 맴버 함수를 모아놓았습니다.
//

UIToolTipControl::UIToolTipControl()
{
	Body = new UITextureControl;

	m_dToolTipDelayTime = 200;	// 마우스 오버시 0.2초후 발동
	m_iLineIndex = 0;
	m_SizeX = 0;
	m_SizeY = 0;

	m_bEnable = false;
	m_bDisplay = false;
}

UIToolTipControl::~UIToolTipControl()
{
	delete Body;

	if (m_UIToolTipLabelControl.empty()) return;	// 그외 라벨 컨트롤 들을 제거한다.
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end();)
	{
		HT_DELETE ( *ZOder );
		ZOder = m_UIToolTipLabelControl.erase( ZOder );
	}
}

// 윈도우내에 툴팁을 생성합니다.
void UIToolTipControl::CreateUIToolTipControl(unsigned int nIndex, int iXPos, int iYPos, CHTString str )
{
	UITexture oTexture;
	UIText	oText;
	HT_COLOR clr;	// 배경색 지정
	clr.r = 1.0f / 255.0f; clr.g = 1.0f / 255.0f; clr.b = 1.0f / 255.0f; clr.a = 80.0f / 100.0f;


	// ToolTip의 사이즈는 텍스트의 길이에 맞춰서 계산된다.
	int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str );
	
	m_SizeX = strlength + UI_TOOLTIP_EXTRASIZE_X;
	m_SizeY = UI_TOOLTIP_HEIGHT_SIZE*m_iLineIndex + UI_TOOLTIP_EXTRASIZE_Y;

	oTexture.PosX = iXPos; oTexture.PosY = iYPos; oTexture.SizeX = m_SizeX; oTexture.SizeY = m_SizeY;
	oTexture.VertexClr = clr; oTexture.Layer = 2300; 
	oTexture.TextureID = UI_TEXTURE_REGION; 

	oText.strTitle = str; oText.Font = UI_MAIN_FONT; oText.FontMode = UI_FONT_NORMAL; oText.TextFormating = TEXT_FORMATING_ONELINE_VCENTER_CENTER_CLIP; /*TEXT_FORMATING_MULTILINE_VTOP_LEFT_CLIP;*/
	oText.TextPos.left = oTexture.PosX; oText.TextPos.top = oTexture.PosY; oText.TextPos.right = oTexture.SizeX; oText.TextPos.bottom = oTexture.SizeY;
	oText.TextColor.r = 1.0f; oText.TextColor.g = 1.0f; oText.TextColor.b = 1.0f; oText.TextColor.a = 1.0f;
	oText.TextShadowColor.r = 1.0f; oText.TextShadowColor.g = 0.8f; oText.TextShadowColor.b = 0.7f; oText.TextShadowColor.a = 1.0f;
	
	Body->CreateUITextureControl( 0, oTexture );		// 보디 영역
	
	// 미리 텍스트 생성은 해둔다.
	oText.TextPos.top+=(UI_TOOLTIP_EXTRASIZE_Y/2);
	for (int i = 1; i< UI_TOOLTIP_MULTILINE_MAX; ++i)
	{
		CreateLabelControl(i, oText);
		oText.TextPos.top+=UI_TOOLTIP_HEIGHT_SIZE;
		oText.TextPos.bottom = oText.TextPos.top + UI_TOOLTIP_HEIGHT_SIZE;
	}
}

// 화면상에 툴팁을 출력합니다.
void UIToolTipControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true && this->CheckOutputTime() && m_bEnable == true && m_iLineIndex > 0)
	{
		// 만약 사이즈가 해당 스크린을 넘어간다면 그만큼 - 해주어 출력한다.
		int iSizeX, iSizeY;
		Body->GetScale(iSizeX, iSizeY);

		HTvector3 pos = Body->GetUITextureControlPos();

		// 해상도 보다 더 길다면 긴만큼 옆으로 당김
		if (iSizeX + (int)pos.x + iWindowPosX + UI_TOOLTIP_POS_X > g_cUIManager->m_iScreenX)
			iWindowPosX -= (iSizeX + (int)pos.x + iWindowPosX + UI_TOOLTIP_POS_X - g_cUIManager->m_iScreenX + UI_TOOLTIP_POS_X);
		// 해상도 보다 더 길다면 긴만큼 옆으로 당김
		if (iSizeY + (int)pos.y + iWindowPosY + UI_TOOLTIP_POS_Y > g_cUIManager->m_iScreenY)
			iWindowPosY -= (iSizeY + (int)pos.y + iWindowPosY + UI_TOOLTIP_POS_Y - g_cUIManager->m_iScreenY + UI_TOOLTIP_POS_Y);

		Body->Render(iWindowPosX + UI_TOOLTIP_POS_X, iWindowPosY + UI_TOOLTIP_POS_Y);					// 영역 랜더
	}
}

// 화면상에 툴팁을 출력합니다.
void UIToolTipControl::RenderText(int iWindowPosX, int iWindowPosY)
{ 
	unsigned int index = 0;
	if (m_bDisplay == true && this->CheckOutputTime() == true && m_bEnable == true)
		if (m_UIToolTipLabelControl.empty() != true )	// 라벨
			for (int i = 1; i <= UI_TOOLTIP_MULTILINE_MAX; ++i)
				for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
				{
					if ((*ZOder)->m_nIndex == i)
					{
						// 만약 사이즈가 해당 스크린을 넘어간다면 그만큼 - 해주어 출력한다.
						int iSizeX, iSizeY;
						Body->GetScale(iSizeX, iSizeY);
						
						HTvector3 pos = Body->GetUITextureControlPos();

						if (index >= m_iLineIndex) return;

						// 해상도 보다 더 길다면 긴만큼 옆으로 당김
						if (iSizeX + (int)pos.x + iWindowPosX + UI_TOOLTIP_POS_X > g_cUIManager->m_iScreenX)
							iWindowPosX -= (iSizeX + (int)pos.x + iWindowPosX + UI_TOOLTIP_POS_X - g_cUIManager->m_iScreenX + UI_TOOLTIP_POS_X);
	
						// 해상도 보다 더 길다면 긴만큼 옆으로 당김
						if (iSizeY + (int)pos.y + iWindowPosY + UI_TOOLTIP_POS_Y > g_cUIManager->m_iScreenY)
							iWindowPosY -= (iSizeY + (int)pos.y + iWindowPosY + UI_TOOLTIP_POS_Y - g_cUIManager->m_iScreenY + UI_TOOLTIP_POS_Y);

						(*ZOder)->Render(iWindowPosX + UI_TOOLTIP_POS_X, iWindowPosY + UI_TOOLTIP_POS_Y);
						++index;
					}
				}
}


// 원하는 위치로 툴팁을 이동시킵니다.
void UIToolTipControl::Move(int iXPos, int iYPos)
{
	Body->Move(iXPos, iYPos);
	
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
		(*ZOder)->Move(iXPos, iYPos);
}

// 백그라운드 윈도우 영역에 마우스가 있는지 검사합니다.
bool UIToolTipControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// 노말 버튼으로만 체크함
	return Body->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY);
}

// 툴팁 시간 카운트를 시작합니다.
void UIToolTipControl::SetStartTime()	
{
	m_dToolTipStartTime = timeGetTime();
}

// 툴팁을 출력해도 되는지 여부알림
bool UIToolTipControl::CheckOutputTime()
{
	DWORD 	ToolTipNowTime = timeGetTime(); //GetTickCount();
	if (m_dToolTipStartTime + m_dToolTipDelayTime <= ToolTipNowTime)
		return true;
	return false;
}


// 툴팁의 내용을 변경합니다.
void UIToolTipControl::SetText(CHTString str, int nIndex)
{
	SetTextLabelControl(nIndex, str);
}


// 라벨 컨트롤 생성
void UIToolTipControl::CreateLabelControl(unsigned int nIndex, UIText oText)
{
	UILabelControl* pUILabelControl = new UILabelControl;
	pUILabelControl->m_nIndex = nIndex;
	pUILabelControl->CreateUILabelControl(nIndex, oText);
	this->m_UIToolTipLabelControl.push_back(pUILabelControl);
}

// 라벨 컨트롤 제거
void UIToolTipControl::DeleteLabelControl(unsigned int nIndex)
{ 
	if (m_UIToolTipLabelControl.empty()) return;	// 그외 라벨 컨트롤 들을 제거한다.
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UIToolTipLabelControl.erase( ZOder );
			break;
		}
}

// 라벨 컨트롤의 텍스트 변경
void UIToolTipControl::SetTextLabelControl(unsigned int nIndex, CHTString str)
{
	int MaxStrLength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str);

	if (nIndex > m_iLineIndex) m_iLineIndex = nIndex;
	if (nIndex > UI_TOOLTIP_MULTILINE_MAX) m_iLineIndex = nIndex = UI_TOOLTIP_MULTILINE_MAX;	// 맥스라인 고정

	// 먼저 존재하는 모든 라벨 텍스트 길이중 가장 긴것의 사이즈를 얻는다.
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
	{
		/// ToolTip의 사이즈는 텍스트의 길이에 맞춰서 계산된다.
		int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, (*ZOder)->GetText());
		// 아주 긴것들은 더이상 늘어나지않도록 고정시킨다.
		if (strlength > 500) strlength = 210;
		if (MaxStrLength <= strlength) MaxStrLength = strlength;
	}

	// 사이즈 재갱신 및 정렬
	for(std::list<UILabelControl*>::iterator ZOder2 = m_UIToolTipLabelControl.begin(); ZOder2 != m_UIToolTipLabelControl.end(); ++ZOder2)
		(*ZOder2)->SetScale(MaxStrLength+UI_TOOLTIP_EXTRASIZE_X, UI_TOOLTIP_HEIGHT_SIZE);	// 영역 재설정

	for(std::list<UILabelControl*>::iterator ZOder3 = m_UIToolTipLabelControl.begin(); ZOder3 != m_UIToolTipLabelControl.end(); ++ZOder3)
		if ((*ZOder3)->m_nIndex == nIndex)
		{
			// Step 1) 텍스트 사이즈를 재조정한다.
			Body->SetScale(MaxStrLength + UI_TOOLTIP_EXTRASIZE_X, UI_TOOLTIP_HEIGHT_SIZE * m_iLineIndex + UI_TOOLTIP_EXTRASIZE_Y);
			// Step 2) 글 내용을 변경한다.
			(*ZOder3)->SetText(str);	// 해당 영역에 한해 문자열 삽입

			int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, (*ZOder3)->GetText());
            if ((*ZOder3)->m_nIndex == 3 && strlength > 500)
				(*ZOder3)->SetArrangement(7);
			else
				(*ZOder3)->SetArrangement(8);

			break;
		}
}

// 라벨 컨트롤의 텍스트 변경
void UIToolTipControl::SetTextLabelControlIndex(unsigned int nIndex)
{
	int MaxStrLength = 0;

	m_iLineIndex = nIndex;	// 인덱스 재설정

	for (int i = nIndex+1; i < UI_TOOLTIP_MULTILINE_MAX; ++i) 
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == i)
			(*ZOder)->SetText(" ");
	
	// 먼저 존재하는 모든 라벨 텍스트 길이중 가장 긴것의 사이즈를 얻는다.
	for(std::list<UILabelControl*>::iterator ZOder2 = m_UIToolTipLabelControl.begin(); ZOder2 != m_UIToolTipLabelControl.end(); ++ZOder2)
	{
		/// ToolTip의 사이즈는 텍스트의 길이에 맞춰서 계산된다.
		int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, (*ZOder2)->GetText());
		if (strlength > 500) strlength = 210;
		if (MaxStrLength <= strlength) MaxStrLength = strlength;
	}

	// 사이즈 재갱신 및 정렬
	for(std::list<UILabelControl*>::iterator ZOder3 = m_UIToolTipLabelControl.begin(); ZOder3 != m_UIToolTipLabelControl.end(); ++ZOder3)
		(*ZOder3)->SetScale(MaxStrLength+UI_TOOLTIP_EXTRASIZE_X, UI_TOOLTIP_HEIGHT_SIZE);	// 영역 재설정

	// 아주 긴 문자열은 강제로 셋팅한다.
	for(std::list<UILabelControl*>::iterator ZOder4 = m_UIToolTipLabelControl.begin(); ZOder4 != m_UIToolTipLabelControl.end(); ++ZOder4)
	{
		int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, (*ZOder4)->GetText());
		if (strlength > 500) 
			(*ZOder4)->SetScale(210+UI_TOOLTIP_EXTRASIZE_X, UI_TOOLTIP_HEIGHT_SIZE);	// 영역 재설정
	}

	Body->SetScale(MaxStrLength + UI_TOOLTIP_EXTRASIZE_X, UI_TOOLTIP_HEIGHT_SIZE * m_iLineIndex + UI_TOOLTIP_EXTRASIZE_Y);

}

// 라벨 컨트롤의 텍스트컬러 변경
void UIToolTipControl::SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UIToolTipLabelControl.begin(); ZOder != m_UIToolTipLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextColor(clr);
			break;
		}
}



//
// UIButtonControl Class 맴버 함수를 모아놓았습니다.
//

UIButtonControl::UIButtonControl()
{
	ButtonNormal = new UITextureControl;
	ButtonOver	= new UITextureControl;
	ButtonDown	= new UITextureControl;
	ToolTip = new UIToolTipControl;

	m_bEnable = true;
	m_bDisplay = true;
	m_bToolTip = true;
	m_bEnter = false;
	m_iButtonState = 0;
	m_nButtonState = 0;

	m_dFlashButtonOnDelayTime = 700;	// 커서 꺼지는 시간 0.75초후 발동
	m_dFlashButtonOffDelayTime = 1000;	// 커서 켜지는 시간 1초후 발동
	m_dFlashButtonStartTime = 0;
}

UIButtonControl::~UIButtonControl()
{
	delete ButtonNormal;
	delete ButtonOver;
	delete ButtonDown;
	delete ToolTip;
}

// 윈도우내에 버튼을 생성합니다.
void UIButtonControl::CreateUIButtonControl(unsigned int nIndex, UITexture oTexture[3] )
{
	ButtonNormal->CreateUITextureControl(0, oTexture[0]);// 노말 상태로 생성
	ButtonNormal->Show();
	ButtonOver->CreateUITextureControl(0, oTexture[1]);	// 오버 상태로 생성
	ButtonOver->Hide();
	ButtonDown->CreateUITextureControl(0, oTexture[2]);	// 다운 상태로 생성
	ButtonDown->Hide();
	ToolTip->CreateUIToolTipControl(0, oTexture[0].PosX, oTexture[0].PosY, _T(" "));	// 툴팁 컨트롤 생성
}

// 화면상에 윈도우를 출력합니다.
void UIButtonControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
	{
		// 텍스처 랜더 (깜박임 모드라면 여기서 처리)
		if (m_iButtonState == 3)
		{
			if (m_nButtonState == 0)
			{
				DWORD 	FlashButtonNowTime = timeGetTime();//GetTickCount();
		
				if (m_dFlashButtonStartTime + m_dFlashButtonOnDelayTime >= FlashButtonNowTime)
				{ButtonNormal->Hide(); ButtonOver->Show(); ButtonDown->Hide();}
				else if (m_dFlashButtonStartTime + m_dFlashButtonOffDelayTime >= FlashButtonNowTime)
				{ButtonNormal->Hide(); ButtonOver->Hide(); ButtonDown->Show();}
				else {m_dFlashButtonStartTime = timeGetTime();}
			}
			else if (m_nButtonState == 1)
			{m_dFlashButtonStartTime = timeGetTime();}
		}

		ButtonNormal->Render(iWindowPosX, iWindowPosY);					// 영역 랜더
		ButtonOver->Render(iWindowPosX, iWindowPosY);
		ButtonDown->Render(iWindowPosX, iWindowPosY);
	}
}


// 화면상에 윈도우를 출력합니다.
void UIButtonControl::RenderTextureToolTip(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
		if (m_bToolTip) 
			ToolTip->RenderTexture(iWindowPosX, iWindowPosY);
}

// 화면상에 텍스트를 출력합니다.
void UIButtonControl::RenderText(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
		if (m_bToolTip) 
			ToolTip->RenderText(iWindowPosX, iWindowPosY);
}

// 원하는 위치로 윈도우를 이동시킵니다.
void UIButtonControl::Move(int iXPos, int iYPos)
{
	ButtonNormal->Move(iXPos, iYPos);
	ButtonOver->Move(iXPos, iYPos);	
	ButtonDown->Move(iXPos, iYPos);	
	ToolTip->Move(iXPos, iYPos);
}

// 원하는 크기로 조절
void UIButtonControl::SetScale(int iSizeX, int iSizeY)
{
	ButtonNormal->SetScale(iSizeX, iSizeY);
	ButtonOver->SetScale(iSizeX, iSizeY);	
	ButtonDown->SetScale(iSizeX, iSizeY);	
}

// 백그라운드 윈도우 영역에 마우스가 있는지 검사합니다.
bool UIButtonControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// 노말 버튼으로만 체크함
	if (ButtonNormal->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
	{ return true; }
	else
	{ return false; }
}

void UIButtonControl::SetButtonNormal()
{
	ToolTip->Hide();m_nButtonState = 0;

	switch (m_iButtonState)
	{
	case 0:	case 3: ButtonNormal->Show(); ButtonOver->Hide(); ButtonDown->Hide(); return;	// 보통상태
	case 1:	ButtonNormal->Hide(); ButtonOver->Show(); ButtonDown->Hide(); return;	// 켜짐상태
	case 2: ButtonNormal->Hide(); ButtonOver->Hide(); ButtonDown->Show(); return;	// 꺼짐상태
	}
}

void UIButtonControl::SetButtonOver()
{
	ToolTip->Show();m_nButtonState = 1;
	ButtonNormal->Hide(); ButtonOver->Show(); ButtonDown->Hide();
}

void UIButtonControl::SetButtonDown()
{
	ToolTip->Hide(); m_nButtonState = 2;
	ButtonNormal->Hide(); ButtonOver->Hide(); ButtonDown->Show();
}

// 툴팁을 해당위치로 이동시킵니다.
void UIButtonControl::SetToolTipMove(int iXPos, int iYPos)
{
	ToolTip->Move(iXPos, iYPos);	
}


// 툴팁의 내용을 변경합니다.
void UIButtonControl::SetToolTipStr(CHTString str)
{
	ToolTip->SetText(str);
}





//
// UIEditBoxControl Class 맴버 함수를 모아놓았습니다.
//

UIEditBoxControl::UIEditBoxControl()
{
	Body = new UITextureControl;
	Cursor = new UITextureControl;
	ShiftRegion = new UITextureControl;
	Text = new UILabelControl;

	m_dEditBoxCursorOnDelayTime = 500;	// 커서 켜지는 시간 0.5초후 발동
	m_dEditBoxCursorOffDelayTime = 1000;	// 커서 꺼지는 시간 1초후 발동

	m_Xpos = 0;
	m_XPibot = 0;

	m_bEnable = true;
	m_bDisplay = true;
	m_bFocus = false;
	m_bRegion = false;
	m_ImeNo = 0;	// 처음 입력모드는 영문
	m_iLimitTextSize = 0;
}

UIEditBoxControl::~UIEditBoxControl()
{
	delete Body;
	delete Text;
	delete Cursor;
	delete ShiftRegion;
}

// 에디트컨트롤 제어 (전역 선언)
LRESULT CALLBACK NowEditSubProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return NULL;
}

// 윈도우내에 에디트박스를 생성합니다.
void UIEditBoxControl::CreateUIEditBoxControl(unsigned int nIndex, UITexture oTexture, UIText oText, int iStyle)
{
	Body->CreateUITextureControl( 0, oTexture );						// 에디트박스 텍스처 생성

	// 커서 셋팅
	oTexture.TextureID = 199;											// 커서 텍스처 생성
	oTexture.Layer = 2500;												// 커서 레이아웃 설정 (현재 윈도우에서 최상위로 한다)
	oTexture.PosX += 5;
	oTexture.SizeX = 0;
	oTexture.SizeY = 0;

	oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Cursor->CreateUITextureControl( 0, oTexture );						// 커서를 만든다.

	// 에디터 박스 셋팅
	oTexture.TextureID = 0;												// 커서 텍스처 생성
	oTexture.Layer = 2550;												// 커서 레이아웃 설정 (현재 윈도우에서 최상위로 한다)
	oTexture.SizeX = 0;
	oTexture.SizeY = 0;
	
	oTexture.VertexClr = HT_COLOR(0.2f, 0.2f, 0.2f, 0.7f);
	ShiftRegion->CreateUITextureControl( 0, oTexture );						// 영역 텍스처를 만든다.

	// 텍스트 셋팅
	oText.TextPos.left += 5; oText.TextPos.right -= 5;
	Text->CreateUILabelControl(0, oText);								// 텍스트 컨트롤을 생성한다.
	Text->SetArrangement(4);											// 글자는 왼쪽 가운데 정렬모드로 셋팅
	m_nMode = 0;														// 처음엔 일반모드로 셋팅 ( 1 = 패스워드 출력형식)
}


// 포커스 온시 셋팅될 IME 상태
void UIEditBoxControl::SetFocusOnIME(int iIME)
{
	if( g_iInationalType == INATIONALTYPE_JAPEN )
		return;


	HIMC hIMC = ImmGetContext(g_hWnd);
	DWORD dwInationallanguageCode;

	if (iIME == 1)
	{
		//	Set Language
		if( g_iInationalType == INATIONALTYPE_KOREA )
			dwInationallanguageCode = IME_CMODE_HANGUL;
		else if( g_iInationalType == INATIONALTYPE_CHINA )
			dwInationallanguageCode = IME_CMODE_CHINESE;
		else if( g_iInationalType == INATIONALTYPE_INDONESIA )
			dwInationallanguageCode = IME_CMODE_ALPHANUMERIC;
		else if( g_iInationalType == INATIONALTYPE_PHILIPPINE )
			dwInationallanguageCode = IME_CMODE_ALPHANUMERIC;
		else if( g_iInationalType == INATIONALTYPE_JAPEN )
			dwInationallanguageCode = IME_CMODE_JAPANESE;
		else if( g_iInationalType == INATIONALTYPE_TAIWAN )
			dwInationallanguageCode = IME_CMODE_NATIVE;
		else
			dwInationallanguageCode = IME_CMODE_ALPHANUMERIC;
	}
	else
	{
		dwInationallanguageCode = IME_CMODE_ALPHANUMERIC;
	}

	ImmSetConversionStatus(hIMC, dwInationallanguageCode, 1);
	ImmReleaseContext(g_hWnd, hIMC);
}

// 화면상에 윈도우를 출력합니다.
void UIEditBoxControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true)
	{
		Body->Render(iWindowPosX, iWindowPosY);					// 영역 랜더
		
		if (this->isFocusOn())
		{
			this->CheckOutputTime();
			Cursor->Render(iWindowPosX, iWindowPosY);					// 커서 랜더
			
			if (m_bRegion == true)
				ShiftRegion->Render(iWindowPosX, iWindowPosY);				// 영역 랜더도 같이함
		}
	}
}


// 화면상에 윈도우를 출력합니다.
void UIEditBoxControl::RenderText(int iWindowPosX, int iWindowPosY)
{
	Text->Render(iWindowPosX, iWindowPosY);
}


// 원하는 위치로 윈도우를 이동시킵니다.
void UIEditBoxControl::Move(int iXPos, int iYPos)
{
	Body->Move(iXPos, iYPos);
	Text->Move(iXPos, iYPos);
}

// 백그라운드 윈도우 영역에 마우스가 있는지 검사합니다.
bool UIEditBoxControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	return Body->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY);
}

// 커서깜박임 시간 카운트를 시작합니다.
void UIEditBoxControl::SetStartTime()	
{
	m_dEditBoxStartTime = timeGetTime();//GetTickCount();
}

// 커서 깜박임을 출력해도 되는지 여부알림
bool UIEditBoxControl::CheckOutputTime()
{
	DWORD 	EditBoxNowTime = timeGetTime();//GetTickCount();
	
	if (m_dEditBoxStartTime + m_dEditBoxCursorOnDelayTime >= EditBoxNowTime)
		Cursor->Show();
	else if (m_dEditBoxStartTime + m_dEditBoxCursorOffDelayTime >= EditBoxNowTime)
		Cursor->Hide();
	else
		SetStartTime();
	return false;
}

// 에디트박스에 출력할 문자열 생성 (피봇값에 의해 결정)
void UIEditBoxControl::OutputText()
{
	return;	// 사용안함
}


// 문자열 삽입 (커서 위치 갱신도 같이 한다.)
void UIEditBoxControl::SetText(CHTString str)
{
	// 컨트롤로부터 값얻기
	this->UpdateText( str );
}


// 문자열 삽입 (커서 위치 갱신도 같이 한다.)
void UIEditBoxControl::UpdateText( CHTString strMsg )
{
	// 컨트롤로부터 값얻기
	CHTString str, str2;

	// 실제 버퍼로 부터 문자열 얻기
	//GetWindowText(g_hEdit, str, 256);
	if( strMsg.HT_bIsEmpty() )
	{
		str = g_strResultText;
		if( g_bShowCompStrSw )	str += g_strCompStr;
	}
	//	Clean이 들어오면 걍 비운다.
	else if( strMsg.HT_iStringCompare(_T("CleanBox") ) == 0 )
	{
		str.HT_hrCleanUp();
	}
	else
	{
		str = strMsg;
	}

	// 첫문자가 0으로 시작되고 숫자입력 모드라면 0을 빼준다.
	char temp[256];
	strcpy(temp, str);
	if (temp[0] == '0' && m_nMode == 2) 
		--str;

	//	글자수 제한
	int iStringLen = strlen(str);
	if( iStringLen > m_iLimitTextSize && m_iLimitTextSize != 0 )
	{
		CHTString strTemp;
		strTemp.HT_hrCleanUp();
		strncpy( strTemp, str, m_iLimitTextSize );
		g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( strTemp );

		// 오리지널 텍스트 백업 (m_str)
		str = m_str = strTemp;
		//this->UpdateText(m_str);
	}
	else
	{
		// 오리지널 텍스트 백업 (m_str)
		m_str = str;
	}

	// 모드에 따라 결과물 달리 저장
	switch(m_nMode)	
	{
	case 1:	// 패스워드 모드 (별표로 변경)
		{
			CHTString passwordstr = "";
	
			for (int i=0; i < ((int) strlen(str)); ++i)
				strcat(passwordstr, "*");

			str = passwordstr;
		}
		break;
	case 2:	// 숫자입력 모드 (콤마 자동생성)
		{
			CHTString numberstr = "";
			
			//	0만 연이어 입력했다면 0으로 초기화
			if (atoi(str) == 0 && strlen(str) > 1)
			{
				g_strResultText = "0";
				g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( g_strResultText.HT_szGetString() );
			}

			//	10억 이상의 숫자가 들어오면 999999999
			//	마지막 문자가 숫자가 아니면 0으로 처리
			char szNumber[256];
			ZeroMemory( szNumber, 256 );
			HTint iSize = str.HT_nGetSize();
			strncpy( szNumber, str, iSize );

			//	10억 이상
			if( iSize > 9 )
			{
				//if (atoi(str) > 1999999999)
				if( szNumber[iSize-1]>'1') 
					g_strResultText = "1999999999";
				else
					if( iSize > 10 ) g_strResultText = "1999999999";
				g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( g_strResultText.HT_szGetString() );
				m_str = str = g_strResultText;
			}
			//	마지막 문자가 숫자가 아님
			else if( szNumber[iSize-1]<'0' || szNumber[iSize-1]>'9' )
			{
				g_strResultText = "0";
				g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( g_strResultText.HT_szGetString() );
				m_str = str = g_strResultText;
			}

			m_str = str;
			numberstr = g_cUIManager->HT_strSetRestMark(atoi(str));
			str = numberstr;
		}
		break;
	}

	// 변형된 텍스트 내용 백업 (str2)
	str2 = str;

	// CString -> wchar_t 형으로 변환하여 문자 갯수 추출
	CComBSTR bstr = str;
	wchar_t *pVal, wcs[256], TailCutStr[256] = L"";
	
	pVal = bstr;
	int iTotalPibot = wcslen(pVal);
	wcscpy(wcs, pVal);
	
	// 피봇 추출
	if (g_Pibot > iTotalPibot) 	g_Pibot = iTotalPibot;
	if (g_Pibot < 0) g_Pibot = 0;

	iTotalPibot -= g_Pibot;
	
	// 커서 위치까지만 문자열 얻어옴 저장은 wchar_t -> CString
	wcsncpy(TailCutStr, wcs, iTotalPibot);
	wcstombs(str2, TailCutStr, 256 );

	// 문자열의 처음부터 피봇까지만 픽셀 거리 구함
	HT_RECT pos = Text->GetUILabelControlPos();
	int strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str2 );
	//Cursor->Move((int)pos.left + strlength, (int)pos.top);

	// 마지막 피봇 위치를 중심으로 에디터박스 컨트롤 영역에 맞춰 앞 문자열 자름
	bool bType = false;
	strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str2 );
	int strlength2 = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str );

	if ( strlength > pos.right - 16)  bType = true;

	if ( bType == true)	// 피봇까지만의 문자열을 가지고 처리
		str = str2;

	// 영역을 벗어나는 문자열이나 피봇이 영역 이내에 위치할 경우에는 영역을 중심으로 앞부분만 복사하여 출력
	int AddPibot = 0;
	if ( bType == false && strlength2 > pos.right - 16 )
	{
		int i = 0;
		char tempstr[256] = _T("");
		strlength2 = 0;

		do  // 영역 사이즈보다 작을때까지 순서대로 문자열 복사 
		{ 
			i++;
			strncpy(tempstr, str, i);
			strlength2 = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, tempstr ); 

		} while ( strlength2 <= pos.right - 16);

		strcpy(str, tempstr);
	}
	else
	{
		int strtemp = strlength;
		while ( strlength > pos.right - 16) // 영역 사이즈보다 작을때까지 앞의 문자열 자름
		{ 
			--str; strlength = g_pEngineHandler->HT_iGetTextWidth( UI_MAIN_FONT, str ); 

			AddPibot += (strtemp - strlength);
			strtemp = strlength;
			if (AddPibot > m_XPibot)	// 쉬프트 중이였다면 제거한 문자 길이만큼 m_XPibot 좌표 감소 
			{
				// 만약, 0 보다 작아진다면 0 유지
				AddPibot = m_XPibot;
			}
		}
	}

	
	// 쉬프트 눌림 시작이라면 쉬프트 시작 피봇 저장
	if (g_Shift == true && m_XPibot == -1)
	{
		m_bRegion = true;
		m_XPibot = strlength;
	}
	else if (g_Shift == false && m_XPibot == -2)
	{
		m_bRegion = false;
	}


	g_EditBoxCursorPosX = (int)pos.left + strlength;
	g_EditBoxCursorPosY = (int)pos.top;

	Cursor->Move((int)pos.left + strlength, (int)pos.top);

	Text->SetText(str);

	// 영역 박스 (Shift) 그리기
	if (g_Shift == true) 
	{
		ShiftRegion->Move((int)pos.left + m_XPibot - AddPibot, (int)pos.top);
		ShiftRegion->SetScale(strlength - m_XPibot + AddPibot, 16);
	}

	//MoveCursor(hr, 0);
	//OutputText();
}

// 에디터박스를 입력상태로 만듭니다.
void UIEditBoxControl::SetFocusOn() 
{ 
	g_cUIManager->CheckEditBoxFocusOn(true);
	m_bFocus = true;
	//SetFocus(g_hEdit);
	SetFocusOnIME(m_ImeNo);	// 입력상태를 정의한 상태로 변경
	g_Pibot = -1;
	m_XPibot = -2;
	g_Shift = false;								// 쉬프트 눌림상태
	g_Control = false;								// 쉬프트 눌림상태
	g_RegionCheck = false;	
	//SendMessage(g_hEdit, WM_KEYDOWN, VK_END, 0);
	
	this->SetStartTime();	// 커서 출력 시작
}	

// 에디터박스를 입력불가상태로 만듭니다.
void UIEditBoxControl::SetFocusOff() 
{
	g_EditBoxFocusWindow = 0; // 포커스 잡혀있는 윈도우 없음
	g_EditBoxFocusControl = 0;	// 포커스 잡혀 있는 컨트롤 없음

	g_cUIManager->CheckEditBoxFocusOn(false);
	m_bFocus = false;
	SetFocusOnIME(0);	// 입력상태를 영문상태로 변경
	//SetFocus(g_hWnd);
}

// 에디터박스를 입력불가상태로 만듭니다.
void UIEditBoxControl::SetLimitText(unsigned int uiSize) 
{
	m_iLimitTextSize = uiSize;
	//SendMessage(g_hEdit, EM_LIMITTEXT, (WPARAM) uiSize, 0);
}

// 커서를 이동시킵니다.
void UIEditBoxControl::MoveCursor(int iXpos, int iYpos)
{	
	return;	//사용안함
}




//
// UI Timer Control Class 맴버 함수를 모아놓았습니다.
//

UITimerControl::UITimerControl() {}
UITimerControl::~UITimerControl() {}
	
// 타이머를 생성합니다.
void UITimerControl::CreateUITimerControl(unsigned int nIndex, DWORD dwSetTime, int iStyle)
{
	dwDealyTime = dwSetTime;
	m_nIndex = nIndex;
	dwSetTime = timeGetTime();
	m_bEnable = false;

	switch(iStyle)
	{
	case 0:	// 계속 반복
		m_OnlyOne = false;
		break;
	case 1:	// 한번만 실행
		m_OnlyOne = true;
		break;
	}
}

// 시간을 체크합니다.
bool UITimerControl::CheckTime()
{
	DWORD nowTime = timeGetTime();
	if (m_bEnable == true && dwSetTime + dwDealyTime <= nowTime)
	{
		if (m_OnlyOne == false) EnableOn(); else EnableOff();
		return true;
	}
	else
	{
		return false;
	}
}



//
// UI CheckBox Control Class 맴버 함수를 모아놓았습니다.
//

UICheckBoxControl::UICheckBoxControl() 
{
	Body = new UITextureControl;
	Check = new UITextureControl;

	m_bEnable = true;
	m_bDisplay = true;
	m_bValue = false;
}

UICheckBoxControl::~UICheckBoxControl()
{
	delete Body;
	delete Check;
}


// 체크박스를 생성합니다.
void UICheckBoxControl::CreateUICheckBoxControl(unsigned int nIndex, int XPos, int YPos, bool bValue, int BorderTextureID, int CheckTextureID, int SizeX, int SizeY)
{
	m_nIndex = nIndex;
	m_bEnable = true;
	m_bDisplay = true;
	m_bValue = bValue;

	UITexture oTexture;	// 텍스처 생성
	oTexture.Layer = 1450;
	oTexture.PosX = XPos;
	oTexture.PosY = YPos;
	oTexture.SizeX = SizeX;
	oTexture.SizeY = SizeY;
	oTexture.TextureID = BorderTextureID;
	oTexture.VertexClr = HT_COLOR(1,1,1,1);

	if (BorderTextureID == 0)
	{
		BorderTextureID = 0;
		oTexture.VertexClr = HT_COLOR(1,1,1,0);
	}

	Body->CreateUITextureControl( 0, oTexture );
	
	oTexture.TextureID = CheckTextureID;
	oTexture.VertexClr = HT_COLOR(1,1,1,1);

	Check->CreateUITextureControl( 0, oTexture );
}

// 체크박스 값을 변경합니다.
void UICheckBoxControl::SetValue(bool bValue)
{
	m_bValue = bValue;
}

// 화면상에 윈도우를 출력합니다.
void UICheckBoxControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay == true)
	{
		Body->Render(iWindowPosX, iWindowPosY);					// 영역 랜더
		
		if (m_bValue == true)
		{
			Check->Render(iWindowPosX, iWindowPosY);					// 체크박스 랜더
		}
	}
}

// 원하는 위치로 윈도우를 이동시킵니다.
void UICheckBoxControl::Move(int iXPos, int iYPos)
{
	Body->Move(iXPos, iYPos);
	Check->Move(iXPos, iYPos);
}

// 백그라운드 윈도우 영역에 마우스가 있는지 검사합니다.
bool UICheckBoxControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	return Body->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY);
}


//
// UI Slot Control Class 맴버 함수를 모아놓았습니다.
//

UISlotBoxControl::UISlotBoxControl()
{
	ToolTip = new UIToolTipControl;
	Slot = new UITextureControl;
	Image = new UITextureControl;
	Fx = new UITextureControl;
	Enable = new UITextureControl;
	
	m_bFirstMove = true;
	m_bMouseOver = false;
	m_bToolTip = true;
	m_bDisplay = true;
	m_bEnable = true;
	m_bFixedIcon = false;
	m_bEnableCheck = false;

	m_AddPosX = 3;	// 슬롯박스에 추가 이동하여 출력할 이미지 X, Y 좌표
	m_AddPosY = 3;
}

UISlotBoxControl::~UISlotBoxControl()
{
	delete ToolTip;
	delete Slot;
	delete Image;
	delete Fx;
	delete Enable;
}

// 윈도우에 출력할 텍스처를 생성합니다.
void UISlotBoxControl::CreateUISlotBoxControl(unsigned int nIndex, UITexture oTexture)
{
	oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f);

	if (oTexture.TextureID == 0) 
	{
		oTexture.SizeX = 32;
		oTexture.SizeY = 32;
	}

	Slot->CreateUITextureControl(nIndex, oTexture);
	ToolTip->CreateUIToolTipControl(0, oTexture.PosX, oTexture.PosY, _T("ToolTip"));	// 툴팁 컨트롤 생성
	ToolTip->EnableOn();

	// 이미지 초기화
	oTexture.PosX+=m_AddPosX;
	oTexture.PosY+=m_AddPosY;
	oTexture.TextureID = 0;
	oTexture.SizeX = 32;
	oTexture.SizeY = 32;
	oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Image->CreateUITextureControl(nIndex, oTexture);
	Image->Hide();
	
	// FX 초기화
	oTexture.Layer = 2051;
	oTexture.TextureID = 23661;
	oTexture.SizeX = 32;
	oTexture.SizeY = 32;
	oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Fx->CreateUITextureControl(nIndex, oTexture);

	oTexture.Layer = 2051;
	oTexture.TextureID = 0;
	oTexture.SizeX = 32;
	oTexture.SizeY = 32;
	oTexture.VertexClr = HT_COLOR(0.0f, 0.0f, 0.0f, 0.6f);
	Enable->CreateUITextureControl(nIndex, oTexture);
	m_bCoolTime = false;
}

// 화면상에 텍스처를 출력합니다.
void UISlotBoxControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
	{
		Slot->Render(iWindowPosX, iWindowPosY);
		Image->Render(iWindowPosX, iWindowPosY);
		
		if (m_bCoolTime)
		{
			CheckTime();
			Fx->Render(iWindowPosX, iWindowPosY);
		}

		if (m_bEnableCheck)
		{
			Enable->Render(iWindowPosX, iWindowPosY);
		}
	}
}

// 화면상에 윈도우를 출력합니다.
void UISlotBoxControl::RenderTextureToolTip(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
		if (m_bToolTip) 
			ToolTip->RenderTexture(iWindowPosX, iWindowPosY);
}

// 화면상에 텍스트를 출력합니다.
void UISlotBoxControl::RenderText(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
		if (m_bToolTip) 
			ToolTip->RenderText(iWindowPosX, iWindowPosY);
}

// 해당 영역에 마우스가 있는지 검사합니다.
bool UISlotBoxControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// 조건 검사를 위해 로컬 좌표값만을 빼낸다.
	return Slot->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY);
}

// 원하는 위치로 컨트롤을 이동시킵니다.
void UISlotBoxControl::Move(int iXPos, int iYPos)
{
	Slot->Move(iXPos, iYPos);
	Image->Move(iXPos, iYPos);
	Fx->Move(iXPos, iYPos);
	ToolTip->Move(iXPos, iYPos);
	Enable->Move(iXPos, iYPos);
}

// 원하는 위치로 컨트롤을 이동시킵니다.
void UISlotBoxControl::MoveImage(int iXPos, int iYPos)
{
	Image->Move(iXPos, iYPos);
}

// UISlotBoxControl의 위치를 반환한다.
HTvector3 UISlotBoxControl::GetUISlotBoxControlPos()
{
	HTvector3 fPos = Slot->GetUITextureControlPos();
	return fPos;
}

// UISlotBoxControl의 위치를 반환한다.
HTvector3 UISlotBoxControl::GetUISlotImageControlPos()
{
	HTvector3 fPos = Image->GetUITextureControlPos();
	return fPos;
}

// 해당 텍스처로 재설정합니다.
void UISlotBoxControl::SetSlotBoxControl(int iTextureID, int iLayer)
{
	UITexture oTexture;
	HTvector3 fPos = Slot->GetUITextureControlPos();
	
	delete Image;
	Image = new UITextureControl;

	if (iTextureID == 0)
	{
		Image->Hide();
		m_bEnable = false;

		oTexture.TextureID = 0;
		oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f);
		oTexture.PosX = (int) fPos.x + m_AddPosX;
		oTexture.PosY = (int) fPos.y + m_AddPosX;
		oTexture.Layer = iLayer;
		oTexture.SizeX = 32;
		oTexture.SizeY = 32;
	}
	else
	{
		Image->Show();
		m_bEnable = true;
		
		oTexture.TextureID = iTextureID;
		oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
		oTexture.PosX = (int) fPos.x + m_AddPosX;
		oTexture.PosY = (int) fPos.y + m_AddPosX;
		oTexture.Layer = iLayer;
		oTexture.SizeX = 32;
		oTexture.SizeY = 32;
	}

	Image->CreateUITextureControl(m_nIndex, oTexture);
}

// 슬롯박스의 쿨타임 설정
void UISlotBoxControl::SetSlotBoxCoolTime(DWORD DealyTime, DWORD PastTime)
{
	dwSetTime = timeGetTime();
	dwDealyTime = DealyTime - PastTime;
	m_bCoolTime = true;
	m_bEnable = true;

	SetSlotBoxControlEnable(false);

	// 쿨타임 이미지 생성
	// 32 Frame로 만든다. 
	dwFrameTime = DWORD( (float)(DealyTime) / 16.0f);
	dwTotalFrameTime = dwSetTime;
	iCoolTimePos = 0;
	HTvector3 pos = Slot->GetUITextureControlPos();
	
	Fx->Move((int)pos.x + m_AddPosX, (int)pos.y + m_AddPosY);
	Fx->SetScale(32,32);

	if (PastTime > 0)
	{
		HTvector3 pos = Slot->GetUITextureControlPos();
		iCoolTimePos = DWORD( (float)(PastTime) / dwFrameTime);
		Fx->Move((int)pos.x + (iCoolTimePos) + m_AddPosX , (int)pos.y + (iCoolTimePos) + m_AddPosY);
		Fx->SetScale(32-(iCoolTimePos*2), 32-(iCoolTimePos*2));
	}

}

// 슬롯박스의 쿨타임 해제
void UISlotBoxControl::SetSlotBoxCoolTimeCancel()
{
	m_bCoolTime = false;
	SetSlotBoxControlEnable(true);
}

// 슬롯박스가 쿨타임중인지?
bool UISlotBoxControl::isSlotBoxCoolTime()
{
	return m_bCoolTime;
}

// 슬롯박스의 아이콘 위치 재설정
void UISlotBoxControl::SetSlotBoxControlPosImage(int iPosX, int iPosY )
{
	m_AddPosX = iPosX;
	m_AddPosY = iPosY;

	this->SetSlotBoxControl(GetUISlotTextureID());
}

// 슬롯박스 사용여부 결정
void UISlotBoxControl::SetSlotBoxControlEnable(bool bEnable)
{
	HTvector3 pos = Slot->GetUITextureControlPos();

	Enable->Move((int)pos.x + m_AddPosX, (int)pos.y + m_AddPosY);
	Enable->SetScale(32,32);

	if (bEnable == false)
	{
		Enable->Show();
		m_bEnableCheck = true;
	}
	else
	{
		Enable->Hide();
		m_bEnableCheck = false;
	}
}

// 시간을 체크합니다.
bool UISlotBoxControl::CheckTime()
{
	if (m_bCoolTime == true)
	{
		DWORD nowTime = timeGetTime();
	
		if ( dwSetTime + dwDealyTime <= nowTime )	// 쿨타임 시간이 지나면 쿨타임 상태를 끝낸다.
		{
			m_bCoolTime = false;
			m_bEnable = true;
			SetSlotBoxControlEnable(true);
			return true;
		}
		else
		{
			if (dwTotalFrameTime + dwFrameTime <= nowTime)
			{
				dwTotalFrameTime+=dwFrameTime; // 다음 시간 누적
				iCoolTimePos++;// 다음 프레임 이미지 생성
				HTvector3 pos = Slot->GetUITextureControlPos();
				Fx->Move((int)pos.x + (iCoolTimePos) + m_AddPosX, (int)pos.y + (iCoolTimePos) + m_AddPosY);
				Fx->SetScale(32-(iCoolTimePos*2), 32-(iCoolTimePos*2));
			}
			return false;
		}
	}
	return false;
}

// 툴팁을 감춥니다.
void UISlotBoxControl::ToolTipHide()
{
	ToolTip->Hide();
}

// 툴팁을 보입니다.
void UISlotBoxControl::ToolTipShow()
{
	ToolTip->Show();
}



//
// UI ScrollBar Control Class 맴버 함수를 모아놓았습니다.
//

UIScrollBarControl::UIScrollBarControl()
{
	Arrow1 = new UIButtonControl;					// 화살표1
	Arrow2 = new UIButtonControl;					// 화살표2
	Image = new UITextureControl;					// 스크롤바
	Line = new UITextureControl;					// 라인 텍스처

	m_bEnable = true;
	m_bDisplay = true;

}
UIScrollBarControl::~UIScrollBarControl()
{
	delete Arrow1;
	delete Arrow2;
	delete Image;
	delete Line;
}

// 윈도우에 출력할 텍스처를 생성합니다.
void UIScrollBarControl::CreateUIScrollBarControl(unsigned int nIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType)
{  
	Arrow1->CreateUIButtonControl(0, oTArrow1);
	Arrow2->CreateUIButtonControl(0, oTArrow2);
	Image->CreateUITextureControl(0, oTImage);
	Line->CreateUITextureControl(0, oTLine);

	m_nPosX = oTLine.PosX;
	m_nPosY = oTLine.PosY;
	m_nLengthX = oTLine.SizeX;
	m_nLengthY = oTLine.SizeY;

	m_nValue = 0;
	m_nType = iType;
	m_nMaxValue = iMaxValue;
}

// 화면상에 텍스처를 출력합니다.
void UIScrollBarControl::RenderTexture(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
	{
		Arrow1->RenderTexture(iWindowPosX, iWindowPosY);
		Arrow2->RenderTexture(iWindowPosX, iWindowPosY);
		Image->Render(iWindowPosX, iWindowPosY);
		Line->Render(iWindowPosX, iWindowPosY);
	}
}

// 화면상에 윈도우를 출력합니다.
void UIScrollBarControl::RenderTextureToolTip(int iWindowPosX, int iWindowPosY)
{
	if (m_bDisplay)
	{
		Arrow1->RenderTextureToolTip(iWindowPosX, iWindowPosY);
		Arrow2->RenderTextureToolTip(iWindowPosX, iWindowPosY);
	}
}

// 화면상에 텍스트를 출력합니다.
void UIScrollBarControl::RenderText(int iWindowPosX, int iWindowPosY)
{
	Arrow1->RenderText(iWindowPosX, iWindowPosY);
	Arrow2->RenderText(iWindowPosX, iWindowPosY);
}

// 해당 영역에 마우스가 있는지 검사합니다.
bool UIScrollBarControl::CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	// 조건 검사를 위해 로컬 좌표값만을 빼낸다.
	return Image->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY);
}

// 원하는 위치로 컨트롤을 이동시킵니다.
void UIScrollBarControl::Move(int iXPos, int iYPos)
{
	Arrow1->Move(iXPos, iYPos);
	Arrow2->Move(iXPos, iYPos);
	Image->Move(iXPos, iYPos);
	Line->Move(iXPos, iYPos);
}

// 원하는 위치로 컨트롤을 이동시킵니다.
void UIScrollBarControl::MoveImage(int iXPos, int iYPos)
{
	Image->Move(iXPos, iYPos);
}

// UIScrollBarControl의 위치를 반환한다.
HTvector3 UIScrollBarControl::GetUIScrollBarControlPos()
{
	return Image->GetUITextureControlPos();
}

// 현재 값과 맥심엄값을 계산하여 스크롤바 위치를 업데이트 합니다.
void UIScrollBarControl::UpdateScrollBar()
{
	float iPersent =  ( (float) (m_nValue) / (float) m_nMaxValue );
	int XPos = 0, YPos = 0;

	switch(m_nType)
	{
	case 0:	// 수직
		YPos = int ( (float(m_nLengthY) - 14) * iPersent );
		Image->Move(m_nPosX - 6 , m_nPosY + YPos);
		break;
	case 1: // 수평
		XPos = int ( (float(m_nLengthX) - 14) * iPersent );
		Image->Move(m_nPosX + XPos , m_nPosY + YPos - 6);
		break;
	}
}


//
// UIWindow Class 맴버 함수를 모아놓았습니다.
//

UIWindow::UIWindow()
{
	Body = new UITextureControl;
	ScaleBar = new UITextureControl;
	TitleBar = new UITextureControl;
	CloseButton = new UIButtonControl;
	TitleStr = new UILabelControl;
	MovingRegion = new UITextureControl;

	m_bEnable = true;
	m_bDisplay = false;
	m_bMovingRegionUsing = false;
	m_bMagnet = false;
	m_bMagnetUsing = false;
	m_bBackgroundDownEnable = false;

	m_nMaxTextureControl = 6;
	m_nMaxLabelControl = 0;
	m_nMaxButtonControl = 0;
	m_bMagnetUsingPro = false;
}

UIWindow::~UIWindow()
{
	delete Body;
	delete TitleBar;
	delete ScaleBar;
	delete CloseButton;
	delete TitleStr;
	delete MovingRegion;

	if (m_UITextureControl.empty() != true) // 할당된 텍스처 컨트롤도 제거한다.
		for(std::list<UITextureControl*>::iterator pUITextureControl = m_UITextureControl.begin(); pUITextureControl != m_UITextureControl.end();)
		{
			HT_DELETE( *pUITextureControl );
			pUITextureControl = m_UITextureControl.erase( pUITextureControl );
		}

	if (m_UIButtonControl.empty() != true)	// 할당된 버튼 컨트롤들도 제거한다.
		for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UIButtonControl.erase( ZOder );
		}

	if (m_UILabelControl.empty() != true)	// 그외 라벨 컨트롤 들을 제거한다.
		for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UILabelControl.erase( ZOder );
		}

	if (m_UILongLabelControl.empty() != true)	// 그외 라벨 컨트롤 들을 제거한다.
		for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UILongLabelControl.erase( ZOder );
		}

	if (m_UIEditBoxControl.empty() != true)	// 그외 에디터 박스 컨트롤 들을 제거한다
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UIEditBoxControl.erase( ZOder );
		}

	if (m_UISlotBoxControl.empty() != true)	// 그외 슬롯박스 제거한다
		for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UISlotBoxControl.erase( ZOder );
		}

	if (m_UIScrollBarControl.empty() != true)	// 그외 스크롤바를 제거한다
		for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UIScrollBarControl.erase( ZOder );
		}

	if (m_UITimerControl.empty() != true)	// 그외 타이머를 제거한다.
		for(std::list<UITimerControl*>::iterator ZOder = m_UITimerControl.begin(); ZOder != m_UITimerControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UITimerControl.erase( ZOder );
		}
	
	if (m_UICheckBoxControl.empty() != true)	// 체크박스
		for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end();)
		{
			HT_DELETE( *ZOder );
			ZOder = m_UICheckBoxControl.erase( ZOder );
		}
}

// 화면상에 출력할 윈도우를 생성하는 함수입니다.
void UIWindow::CreateUIWindow(unsigned int nIndex, CHTString str, int iPosX, int iPosY, int iSizeX, int iSizeY, HT_COLOR dwColor, func_t* ptr, int nMode)
{
	
	UITexture oTexture;
	UIText oText;
	UITexture ot[3];

	m_nMode = nMode; m_nIndex = nIndex;
	iWindowPosX = iPosX; iWindowPosY = iPosY;
	//m_posX = iWindowPosX;
	//m_posY = iWindowPosY;
	m_ptr = ptr;	// 함수 포인터 삽입

	oTexture.PosX = 0; oTexture.PosY = 0; oTexture.SizeX = 1; oTexture.SizeY = 1;oTexture.VertexClr = dwColor; oTexture.Layer = 1300; 
	oTexture.TextureID = UI_TEXTURE_REGION; Body->CreateUITextureControl( 0, oTexture );		// 보디 영역
	oTexture.TextureID = UI_TEXTURE_REGION; TitleBar->CreateUITextureControl( 0, oTexture );	// 타이틀바 영역
	oTexture.TextureID = UI_TEXTURE_REGION; ScaleBar->CreateUITextureControl( 0, oTexture );	// 크기조절바 영역

	//TEXT_FORMATING_ONELINE_VCENTER_CENTER_CLIP
	oText.strTitle = str; oText.Font = UI_MAIN_FONT; oText.FontMode = UI_FONT_BORDER; oText.TextFormating = TEXT_FORMATING_ONELINE_VCENTER_CENTER_CLIP; /*TEXT_FORMATING_MULTILINE_VTOP_LEFT_CLIP;*/
	oText.TextPos.left = 20; oText.TextPos.top = 2; oText.TextPos.right = 110; oText.TextPos.bottom = UI_TOOLTIP_HEIGHT_SIZE;
	//oText.TextColor.r = 1.0f; oText.TextColor.g = 1.0f; oText.TextColor.b = 1.0f; oText.TextColor.a = 1.0f;
	oText.TextColor.r = 0.0f; oText.TextColor.g = 0.0f; oText.TextColor.b = 0.0f; oText.TextColor.a = 1.0f;
	oText.TextShadowColor.r = 1.0f; oText.TextShadowColor.g = 0.8f; oText.TextShadowColor.b = 0.7f; oText.TextShadowColor.a = 1.0f;
	TitleStr->CreateUILabelControl(0, oText);

	switch(nMode)	// 윈도우를 어떻게 그릴지 결정
	{
	case 0:	// 보더 없음
		break;
	case 1:	// 보더 있고, 스케일바 가동됨
		oTexture.TextureID = UI_TEXTURE_HEIGHT_LINE; oTexture.Layer = 1310; this->CreateTextureControl( 10001, oTexture );	// 외각선 좌
		oTexture.TextureID = UI_TEXTURE_HEIGHT_LINE; this->CreateTextureControl( 10002, oTexture );	// 외각선 우
		oTexture.TextureID = UI_TEXTURE_WIDTH_LINE; oTexture.Layer = 1320; 	this->CreateTextureControl( 10003, oTexture );	// 외각선 상
		oTexture.TextureID = UI_TEXTURE_WIDTH_LINE; this->CreateTextureControl(10004, oTexture );	// 외각선 하
		oTexture.TextureID = UI_TEXTURE_TITLEBAR; oTexture.Layer = 1330; 	this->CreateTextureControl(10005, oTexture );	// 타이틀바 텍스처
		oTexture.TextureID = UI_TEXTURE_SCALEBAR_ON; this->CreateTextureControl(10006, oTexture );		// 스케일바

		ot[0].Layer = 1340; ot[0].TextureID = UI_TEXTURE_EDGE_BUTTON_NORMAL; ot[0].VertexClr = dwColor; 
		ot[0].PosX = iSizeX - 28; ot[0].PosY = 0; ot[0].SizeX = 28; ot[0].SizeY = 25;	ot[2] = ot[1] = ot[0];
		ot[2].TextureID = UI_TEXTURE_EDGE_BUTTON_DOWN;	ot[1].TextureID = UI_TEXTURE_EDGE_BUTTON_OVER;
		CloseButton->CreateUIButtonControl(0, ot);	// 종료버튼 생성
		break;
	case 2:	// 보더 있고, 스케일바 가동안됨
		oTexture.TextureID = UI_TEXTURE_HEIGHT_LINE; oTexture.Layer = 1310; this->CreateTextureControl( 10001, oTexture );	// 외각선 좌
		oTexture.TextureID = UI_TEXTURE_HEIGHT_LINE; this->CreateTextureControl( 10002, oTexture );	// 외각선 우
		oTexture.TextureID = UI_TEXTURE_WIDTH_LINE; oTexture.Layer = 1320; 	this->CreateTextureControl( 10003, oTexture );	// 외각선 상
		oTexture.TextureID = UI_TEXTURE_WIDTH_LINE; this->CreateTextureControl(10004, oTexture );	// 외각선 하
		oTexture.TextureID = UI_TEXTURE_TITLEBAR; oTexture.Layer = 1330; 	this->CreateTextureControl(10005, oTexture );	// 타이틀바 텍스처
		oTexture.TextureID = UI_TEXTURE_SCALEBAR_OFF; this->CreateTextureControl(10006, oTexture );		// 스케일바

		ot[0].Layer = 1340; ot[0].TextureID = UI_TEXTURE_EDGE_BUTTON_NORMAL; ot[0].VertexClr = dwColor; 
		ot[0].PosX = iSizeX - 28; ot[0].PosY = 0; ot[0].SizeX = 28; ot[0].SizeY = 25;	ot[2] = ot[1] = ot[0];
		ot[2].TextureID = UI_TEXTURE_EDGE_BUTTON_DOWN;	ot[1].TextureID = UI_TEXTURE_EDGE_BUTTON_OVER;
		CloseButton->CreateUIButtonControl(0, ot);	// 종료버튼 생성
		break;
	}

	// 컨트롤 자동 배치
	this->SetMagnet(-1);	// 기본으로 바탕화면에 대해 자석기능 활성화
	this->SetBorderTexture(iSizeX, iSizeY);
}

// 함수 포인터를 반환합니다.
func_t* UIWindow::GetMessageProcedure()
{
	return m_ptr;
}

// 윈도우의 배경색을 설정합니다.
void UIWindow::SetBackgroundColor(HT_COLOR clr)
{
	Body->SetColor(clr);
}

// 윈도우의 기본 테두리 스케일을 설정합니다.
void UIWindow::SetBorderTexture(int iSizeX, int iSizeY, int nType)
{
	Body->SetScale(iSizeX, iSizeY);	// 보디

	if (m_nMode)
	{
		TitleBar->Move(0,0); TitleBar->SetScale(128, 16); TitleStr->Move(20, 2);// 타이틀바
		ScaleBar->Move(iSizeX - 19, iSizeY - 18); 	ScaleBar->SetScale(19, 18);	// 스케일바
		// 주변 컨트롤의 배치설정을 다시 갱신한다.
		this->SetRegionTextureControl( 10001, 0, 32, 3, iSizeY-32);	// 외각선 좌
		this->SetRegionTextureControl( 10002, iSizeX-3, 25, 3, iSizeY-25);		// 외각선 우
		this->SetRegionTextureControl( 10003, 128, 0, iSizeX-156, 3);		// 외각선 상
		this->SetRegionTextureControl( 10004, 0, iSizeY-3, iSizeX-1, 3);		// 외각선 하
		this->SetRegionTextureControl( 10005, 0, 0, 128, 32);		// 타이틀바
		this->SetRegionTextureControl( 10006, iSizeX-19, iSizeY-18, 19, 18);		// 스케일바
		CloseButton->Move(iSizeX-28, 0); CloseButton->SetScale(28, 25);	// 종료버튼
	}
}


// 화면상에 윈도우를 출력합니다.
void UIWindow::Render()
{
	if (m_bDisplay == true)
	{
		// 텍스처 랜더
		Body->Render();					// 영역 랜더 (타이틀바, 크기조절바 영역은 랜더하지 않는다)

		if (m_UITextureControl.empty() != true)	// 텍스처
			for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
				(*ZOder)->Render(iWindowPosX, iWindowPosY);

		if (m_UIEditBoxControl.empty() != true)	// 에디터 박스
			for(std::list<UIEditBoxControl*>::iterator ZOder2 = m_UIEditBoxControl.begin(); ZOder2 != m_UIEditBoxControl.end(); ++ZOder2)
				(*ZOder2)->RenderTexture(iWindowPosX, iWindowPosY);

		if (m_UISlotBoxControl.empty() != true)	// 슬롯박스
			for(std::list<UISlotBoxControl*>::iterator ZOder3 = m_UISlotBoxControl.begin(); ZOder3 != m_UISlotBoxControl.end(); ++ZOder3)
				(*ZOder3)->RenderTexture(iWindowPosX, iWindowPosY);

		if (m_UIScrollBarControl.empty() != true)	// 스크롤바
			for(std::list<UIScrollBarControl*>::iterator ZOder4 = m_UIScrollBarControl.begin(); ZOder4 != m_UIScrollBarControl.end(); ++ZOder4)
				(*ZOder4)->RenderTexture(iWindowPosX, iWindowPosY);

		if (m_UIButtonControl.empty() != true)	// 버튼
			for(std::list<UIButtonControl*>::iterator ZOder5 = m_UIButtonControl.begin(); ZOder5 != m_UIButtonControl.end(); ++ZOder5)
				(*ZOder5)->RenderTexture(iWindowPosX, iWindowPosY);

		if (m_UICheckBoxControl.empty() != true)	// 체크박스
			for(std::list<UICheckBoxControl*>::iterator ZOder6 = m_UICheckBoxControl.begin(); ZOder6 != m_UICheckBoxControl.end(); ++ZOder6)
				(*ZOder6)->RenderTexture(iWindowPosX, iWindowPosY);

		// 버튼 텍스처 랜더
		if (m_nMode != 0)
			CloseButton->RenderTexture(iWindowPosX, iWindowPosY);

		g_pEngineHandler->HT_hrRender2DUI(); 	// 글자 출력전 랜더 마지막에 수행

		// 텍스트 랜더
		TitleStr->Render(iWindowPosX, iWindowPosY);

		if (m_UILabelControl.empty() != true)	// 라벨
			for(std::list<UILabelControl*>::iterator ZOder7 = m_UILabelControl.begin(); ZOder7 != m_UILabelControl.end(); ++ZOder7)
				(*ZOder7)->Render(iWindowPosX, iWindowPosY);

		if (m_UILongLabelControl.empty() != true)	// 라벨
			for(std::list<UILongLabelControl*>::iterator ZOder8 = m_UILongLabelControl.begin(); ZOder8 != m_UILongLabelControl.end(); ++ZOder8)
				(*ZOder8)->Render(iWindowPosX, iWindowPosY);

		if (m_UIEditBoxControl.empty() != true)	// 에디터 박스
			for(std::list<UIEditBoxControl*>::iterator ZOder9 = m_UIEditBoxControl.begin(); ZOder9 != m_UIEditBoxControl.end(); ++ZOder9)
				(*ZOder9)->RenderText(iWindowPosX, iWindowPosY);

		if (m_UITimerControl.empty() != true)	// 타이머 시간체크
			for(std::list<UITimerControl*>::iterator ZOder10 = m_UITimerControl.begin(); ZOder10 != m_UITimerControl.end(); ++ZOder10)
				if ((*ZOder10)->CheckTime())	// 만약 정해진 시간이 되었다면 다음 함수 호출
				{
						func_t* ptr = GetMessageProcedure();		// 함수 포인터를 얻어온다.
						ptr(0, 5, (*ZOder10)->m_nIndex);				// 해당 메시지 프로시져 실행
				}

	}
}

// 화면상에 윈도우를 출력합니다.
void UIWindow::Render_ToolTip()
{
	if (m_bDisplay == true)
	{
		// 2차 출력 (툴팁부분은 랜더후 재랜더가 필요하다)
		if (m_UIButtonControl.empty() != true || m_UIScrollBarControl.empty() != true || m_UISlotBoxControl.empty() != true)	// 버튼이나 스크롤바
		{
			// 버튼 텍스처 랜더
			if (m_nMode != 0)
				CloseButton->RenderTextureToolTip(iWindowPosX, iWindowPosY);

			for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
				(*ZOder)->RenderTextureToolTip(iWindowPosX, iWindowPosY);
			
			for(std::list<UIScrollBarControl*>::iterator ZOder2 = m_UIScrollBarControl.begin(); ZOder2 != m_UIScrollBarControl.end(); ++ZOder2)
				(*ZOder2)->RenderTextureToolTip(iWindowPosX, iWindowPosY);

			for(std::list<UISlotBoxControl*>::iterator ZOder3 = m_UISlotBoxControl.begin(); ZOder3 != m_UISlotBoxControl.end(); ++ZOder3)
				(*ZOder3)->RenderTextureToolTip(iWindowPosX, iWindowPosY);

			g_pEngineHandler->HT_hrRender2DUI(); 	// 글자 출력전 랜더 마지막에 수행

			for(std::list<UIScrollBarControl*>::iterator ZOder4 = m_UIScrollBarControl.begin(); ZOder4 != m_UIScrollBarControl.end(); ++ZOder4)
				(*ZOder4)->RenderText(iWindowPosX, iWindowPosY);

			for(std::list<UIButtonControl*>::iterator ZOder5 = m_UIButtonControl.begin(); ZOder5 != m_UIButtonControl.end(); ++ZOder5)
				(*ZOder5)->RenderText(iWindowPosX, iWindowPosY);

			for(std::list<UISlotBoxControl*>::iterator ZOder6 = m_UISlotBoxControl.begin(); ZOder6 != m_UISlotBoxControl.end(); ++ZOder6)
				(*ZOder6)->RenderText(iWindowPosX, iWindowPosY);

			if (m_nMode != 0)
				CloseButton->RenderText(iWindowPosX, iWindowPosY);
		}
	}
}

// 원하는 위치로 윈도우를 이동시킵니다.
void UIWindow::MoveWindow(int iXPos, int iYPos)
{
	Body->Move(iXPos, iYPos);	// 보디와 타이틀바 이동
	iWindowPosX = iXPos;
	iWindowPosY = iYPos;
}

// 원하는 크기로 윈도우 사이즈를 조절합니다.
void UIWindow::ScaleWindow(int iSizeX, int iSizeY)
{
	// 기본 텍스처들의 출력위치를 설정합니다.
	this->SetBorderTexture(iSizeX, iSizeY);
}

// 현재 윈도우 크기를 반환합니다.
HTvector3	UIWindow::GetWindowSize()
{
	int iSizeX, iSizeY;
	Body->GetScale(iSizeX, iSizeY);
	HTvector3 pos;
	pos.x = (float) iSizeX;
	pos.y = (float) iSizeY;

	return pos;
}


int UIWindow::OnLButtonDown(int iXPos, int iYPos)
{
	AdxPosX = g_cUIManager->m_MousePosX;
	AdxPosY = g_cUIManager->m_MousePosY;

	if (Body->CheckRegionWithPoint(iXPos, iYPos) && this->isEnable() == true)	// 바디를 조건으로 검사하되
	{
		int hr = 0;

		Body->CheckMouseDown(true);

		// 해당 윈도우 내에서 거리 얻기
		HTvector3 Pos = Body->GetUITextureControlPos();
		iMouseButtonDownXPos = ((int)Pos.x - iXPos);
		iMouseButtonDownYPos = ((int)Pos.y - iYPos);

		// 타이틀을 누르면 바로 이동가능하게 체크하고
		if (TitleBar->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY)) 
		{ 	TitleBar->CheckMouseDown(true); hr = -2;	}
		// 무빙영역이 켜져있다면 이것도 검사
		if (m_bMovingRegionUsing == true && MovingRegion->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY)) 
		{ 	MovingRegion->CheckMouseDown(true); hr = -2;	}
	
		// 그외의 경우, 포커스가 꺼저있는 상태였다면 무조건 리턴한다.
		if ( m_bFocus == false) hr = -2;

		// 버튼이 눌렸다면 각 객체들에 대한 처리를 해준다.
		if (m_nMode != 0)
			if (CloseButton->m_nButtonState == 1) { CloseButton->SetButtonDown(); hr = -2; }
		
		if (m_UIButtonControl.empty() != true) 	// 그외 버튼 컨트롤 처리
			for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
				if ((*ZOder)->m_nButtonState == 1 && (*ZOder)->isEnableOn() == true) { (*ZOder)->SetButtonDown(); hr = -2; }

		// 체크박스 처리
		if (m_UICheckBoxControl.empty() != true) 	// 그외 버튼 컨트롤 처리
			for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end(); ++ZOder)
				if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
					{ 	(*ZOder)->CheckMouseDown(true); hr = -2;	}
					

		// 슬롯박스 처리 (존재하는 모든 슬롯을 검사하여 눌리면 윈도우에서 슬롯무빙모드로 변경)
		if (m_UISlotBoxControl.empty() != true)
			for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
			{
				if ( (*ZOder)->isEnableOn() == true && (*ZOder)->m_bEnableCheck == false)
				{
					if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY) )
					{
						int index = (*ZOder)->m_nIndex;
						(*ZOder)->CheckMouseDown(true);
						break;
					}
				}
				hr = -2;
			}

		// 스크롤바 처리 (존재하는 모든 스크롤바를 검사하여 눌린 이미지에 대해 윈도우에서 이미지 무빙모드로 변경)
		if (m_UIScrollBarControl.empty() != true)
			for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
			{
				if ((*ZOder)->Arrow1->m_nButtonState == 1) { (*ZOder)->Arrow1->SetButtonDown(); hr = -2; }
				if ((*ZOder)->Arrow2->m_nButtonState == 1) { (*ZOder)->Arrow2->SetButtonDown(); hr = -2; }

				if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
				{
					(*ZOder)->CheckMouseDown(true);
				}
			}

		if (m_UIEditBoxControl.empty() != true)	// 에디터 박스 처리
			for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
				if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
				{
					// 다른 모든 포커스는 꺼준다.
					for(std::list<UIEditBoxControl*>::iterator ZOder2 = m_UIEditBoxControl.begin(); ZOder2 != m_UIEditBoxControl.end(); ZOder2++)
						if ((*ZOder2)->isFocusOn() == true)
							(*ZOder2)->SetFocusOff();

					g_EditBoxFocusWindow = this->m_nIndex;
					g_EditBoxFocusControl = (*ZOder)->m_nIndex;
					g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( (*ZOder)->m_str );
					g_cImeMgr.InputString();
					//g_cImeMgr.vImeMgr_SetLanguage( HT_TRUE, 0 );

					(*ZOder)->SetFocusOn();
                    hr = -2;

					//	에디터가 채팅 윈도우에 있을떄 채팅 윈도우 를 뛰어준다.
					if( m_nIndex == _DIALOG_CHATTINGBOX ||
						m_nIndex == _DIALOG_CHATTING2BOX ||
						m_nIndex == _DIALOG_CHATTING3BOX )
					{
						if ((*ZOder)->m_nIndex == 1)
						{
							//	기존에 입력됐던 문자열을 지운다.
							g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
							g_cImeMgr.InputString();
						}
					}

					break;
				}

		// 만약 스케일바 컨트롤 가능상태의 윈도우 모드이고, 스케일조정을 시도했다면 스케일을 변경가능하도록 만든다.
		if (m_nMode == 1 && ScaleBar->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
		{
			// 해당 윈도우 내에서 거리 얻기
			HTvector3 Pos = Body->GetUITextureControlPos();

			int iSizeX, iSizeY;
			Body->GetScale(iSizeX, iSizeY);

			iMouseButtonDownXPosTail = ((int)Pos.x+iSizeX - iXPos);
			iMouseButtonDownYPosTail = ((int)Pos.y+iSizeY - iYPos);

			ScaleBar->CheckMouseDown(true);
			hr =  -2;	
		}

		return hr;
	}

	return 0; 
}

int UIWindow::OnLButtonUp(int iXPos, int iYPos)	
{
	int iCheck = 0;
	Body->CheckMouseDown(false);
	m_bMagnetUsingPro = false;

	if (TitleBar->isMouseDown() == true) { 	TitleBar->CheckMouseDown(false); iCheck = -2;}
	if (MovingRegion->isMouseDown() == true) { MovingRegion->CheckMouseDown(false); iCheck = -2;}

	// [버튼 컨트롤 처리부]
	// 종료버튼은 -1의 반환값을 리턴해 UIManager에서 별도 처리가 가능하도록 해준다.
	if (m_nMode != 0)
	{
		if (CloseButton->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ))
		{ 
			CloseButton->SetButtonOver(); 
			
			func_t* ptr = GetMessageProcedure();						// 함수 포인터를 얻어온다.
			ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_BUTTON, -1);												// 해당 메시지 프로시져 실행
			
			if (g_cUIManager->m_bSlotBoxMoving)
			{
				iCheck = -1;
			}
			else
			{
				return -1; 
			}
		}
		else
		{ CloseButton->SetButtonNormal(); }
	}

	// 체크박스 처리
	if (m_UICheckBoxControl.empty() != true) 	// 그외 버튼 컨트롤 처리
		for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end(); ++ZOder)
			if ((*ZOder)->isMouseDown() == true)
			{ 	
				(*ZOder)->CheckMouseDown(false); 

				// 현재 상태에 따라 토글되게 처리
				if ((*ZOder)->GetValue() == true) 
					(*ZOder)->SetValue(false);
				else
					(*ZOder)->SetValue(true);

				if (g_cUIManager->m_bSlotBoxMoving)
				{
					iCheck = -2;
					break;
				}
				else
				{
                    return -2;
				}
			}

	
	if (m_UIButtonControl.empty() != true) 	// 그외 버튼 컨트롤 처리
		for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
			if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ) && (*ZOder)->isEnableOn() == true)
			{ 
				(*ZOder)->SetButtonOver(); 
				unsigned int index = (*ZOder)->m_nIndex;

				func_t* ptr = GetMessageProcedure();						// 함수 포인터를 얻어온다.
				ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_BUTTON, (*ZOder)->m_nIndex);								// 해당 메시지 프로시져 실행

				if (g_cUIManager->m_bSlotBoxMoving)
				{
					iCheck = index;
					break;
				}
				else
				{
                    return index;
				}
			}
			else 
			{ (*ZOder)->SetButtonNormal(); }

	// 타이틀바 및 스케일바가 눌린 경우에는 UI에서만 처리하면 되므로 3D 엔진으로 입력 메시지를 전송할 필요가 없다.
	if (ScaleBar->isMouseDown() == true) {	ScaleBar->CheckMouseDown(false); return -2; }

	// 슬롯 박스 처리
	bool bCheck = false;
	if (m_UISlotBoxControl.empty() != true) 	// 그외 버튼 컨트롤 처리
		for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		{
			if ((*ZOder)->isMouseDown() == true)
			{ 
				g_cUIManager->m_bSlotBoxMoving = false;
				(*ZOder)->CheckMouseDown(false); 
				(*ZOder)->CheckFirstMove(true);
				(*ZOder)->ToolTipHide();
				
				// 우선적으로 현 윈도우에 놓았다면 거절 모드로 변경
				// Step1) 현재 놓은 위치가 해당 윈도우의 슬롯인지 조사하여 맞다면 푸쉬후 해당윈도우의 함수 호출
				if ((*ZOder)->GetUISlotTextureID() == 0) return -2; // 빈슬롯은 통과
				g_cUIManager->CheckRegionWithSlotBoxPoint(m_nIndex, (*ZOder)->m_nIndex, iXPos, iYPos, (*ZOder)->GetUISlotTextureID());
				return -2;
			}

			if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY) )
				bCheck = true;
		}
	if (bCheck == true) return -2;
	
	// 스크롤바 처리
	if (m_UIScrollBarControl.empty() != true)
		for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		{
			if (!(*ZOder)->isMouseDown())
			{ 
				// 버튼 1 처리
				if ((*ZOder)->Arrow1->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ))
				{ 
					(*ZOder)->Arrow1->SetButtonOver(); 
					int iValue = (*ZOder)->GetValue();
					
					if (iValue > 0 )
					{
						(*ZOder)->SetValue(iValue-1);
						(*ZOder)->UpdateScrollBar();

						func_t* ptr = GetMessageProcedure();		// 함수 포인터를 얻어온다.
						ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// 해당 메시지 프로시져 실행
						return -2;
					}
					return -2;
				}
				else 
				{ (*ZOder)->Arrow1->SetButtonNormal(); }

				// 버튼 2 처리
				if ((*ZOder)->Arrow2->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ))
				{ 
					(*ZOder)->Arrow2->SetButtonOver(); 
					int iValue = (*ZOder)->GetValue();

					if (iValue < (*ZOder)->GetMaxValue())
					{
						(*ZOder)->SetValue(iValue+1);
						(*ZOder)->UpdateScrollBar();
		
						func_t* ptr = GetMessageProcedure();		// 함수 포인터를 얻어온다.
						ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// 해당 메시지 프로시져 실행
						return -2;
					}
					return -2;
				}
				else 
				{ (*ZOder)->Arrow1->SetButtonNormal(); }
			}

			// 움직임 이미지 처리
			if ((*ZOder)->isMouseDown())
			{ 
				(*ZOder)->CheckMouseDown(false); 
				
				return -2; 
			}
		}

	if (m_UIEditBoxControl.empty() != true)	// 에디터 박스 랜더
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
			if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
				return (*ZOder)->m_nIndex;

	if (iCheck == -2) return -2;

	// 컨트롤이 아닌 백그라운드영역만 클릭했다면 0을 리턴하여, 엔진에서 픽(Pick)등의 처리가 가능하게 한다.
	if (m_bBackgroundDownEnable == true)
	{
		if (m_nIndex == _DIALOG_CHATTINGBOX || m_nIndex == _DIALOG_CHATTING2BOX || m_nIndex == _DIALOG_CHATTING3BOX)
		{
			g_cUIManager->HT_HideWindow(_DIALOG_WHISPERLISTWND);
			g_cUIManager->HT_HideWindow(_DIALOG_CHATCONFIG);
		}

		return 0;
	}
	else
	{
		if (Body->CheckRegionWithPoint(iXPos, iYPos) && this->isEnable() == true)
			return -2;

		return 0;
	}
}

void UIWindow::FocusOn()	// 탑 상태가 될때 처리 되는 함수
{
	//TitleStr->SetText("Focus On");
	m_bFocus = true;
	HT_COLOR clr;
	clr.r = 1.0f; clr.g = 1.0f; clr.b = 1.0f; clr.a = 0.5f;
	TitleStr->SetTextShadowColor(clr);
}

void UIWindow::FocusOff()	// 탑상태에서 물러설때 처리 되는 함수
{
	//TitleStr->SetText("Focus Off");
	m_bFocus = false;
	HT_COLOR clr;
	clr.r = 0.3f; clr.g = 0.3f; clr.b = 0.3f; clr.a = 0.5f;
	TitleStr->SetTextShadowColor(clr);
}

// 에디터박스 해당 컨트롤의 포커스 온
void UIWindow::EditBoxFocusOn(unsigned int nIndex)	
{
	if (m_UIEditBoxControl.empty() != true)	// 에디터 박스
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
			if ((*ZOder)->m_nIndex == nIndex)
			{
				// 다른 모든 포커스는 꺼준다.
				for(std::list<UIEditBoxControl*>::iterator ZOder2 = m_UIEditBoxControl.begin(); ZOder2 != m_UIEditBoxControl.end(); ZOder2++)
					if ((*ZOder)->isFocusOn() == true)
						(*ZOder2)->SetFocusOff();

				g_EditBoxFocusWindow = this->m_nIndex;
				g_EditBoxFocusControl = (*ZOder)->m_nIndex;
				g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( (*ZOder)->m_str );
				g_cImeMgr.InputString();

				(*ZOder)->SetFocusOn();
			}
}

// 에디터박스 해당 컨트롤의 포커스 오프
void UIWindow::EditBoxFocusOff(unsigned int nIndex)	
{
	if (m_UIEditBoxControl.empty() != true)	// 에디터 박스
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
			if ((*ZOder)->m_nIndex == nIndex)
			{
				(*ZOder)->SetFocusOff();
				return;
			}
}

// 에디터박스 모든 컨트롤의 포커스 오프
void UIWindow::EditBoxFocusAllOff()
{
	if (m_UIEditBoxControl.empty() != true)	// 에디터 박스
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
			if ((*ZOder)->isFocusOn() == true) 
				(*ZOder)->SetFocusOff();
}

// 포커스 활성화시 입력될 모드 설정변경 (기본은 0 = 영문)
void UIWindow::SetEditBoxFocusOnIME(unsigned int nIndex, int iIME)
{
	if (m_UIEditBoxControl.empty() != true)	// 에디터 박스
		for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
			if ((*ZOder)->m_nIndex == nIndex)
			{
				(*ZOder)->m_ImeNo = iIME;	// 입력상태를 정의한 상태로 변경

				if ((*ZOder)->isFocusOn() == true)	// 현재 입력상태라면 바로적용
					(*ZOder)->SetFocusOnIME(iIME);

				break;
			}
}

// 마우스 R버튼 다운
bool UIWindow::OnRButtonDown(int iXPos, int iYPos)
{
	if (Body->CheckRegionWithPoint(iXPos, iYPos) && this->isEnable() == true)	// 바디를 조건으로 검사하되
	{
		// 슬롯박스 처리 (존재하는 모든 슬롯을 검사하여 눌리면 윈도우에서 슬롯무빙모드로 변경)
		if (m_UISlotBoxControl.empty() != true)
			for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
				if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
				{
					(*ZOder)->CheckMouseRDown(true);
				}
		return true;
	}

	return false;
}

// 마우스 R버튼 업
bool UIWindow::OnRButtonUp(int iXPos, int iYPos)
{
	if (Body->CheckRegionWithPoint(iXPos, iYPos) && this->isEnable() == true)	// 바디를 조건으로 검사하되
	{
		// 슬롯박스 처리 (존재하는 모든 슬롯을 검사하여 눌리면 윈도우에서 슬롯무빙모드로 변경)
		if (m_UISlotBoxControl.empty() != true)
			for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
				if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY) && (*ZOder)->isMouseRDown() == true)
				{
					(*ZOder)->CheckMouseRDown(false);
					(*ZOder)->ToolTipHide();

					int index = (*ZOder)->GetUISlotTextureID();
					if (index == 0) return false;

					g_cUIManager->m_nSlotBoxWindowIndex = m_nIndex;
					g_cUIManager->m_nSlotBoxControlIndex = (*ZOder)->m_nIndex;
					g_cUIManager->m_nSlotBoxTextureID = index;

					func_t* ptr = GetMessageProcedure();		// 함수 포인터를 얻어온다.
					ptr(UI_ACTION_MOUSE_RCLK, UI_TARGET_SLOTBOX, (*ZOder)->m_nIndex);	// 해당 메시지 프로시져 실행
				}
	}

	return false;
}

// 키보드 다운
bool UIWindow::OnKeyDown(WPARAM wParam)
{
	if (m_bFocus == true)
	{
	// 현재 윈도우의 에디터 박스가 활성화 상태하면 오프 시킴
	if (m_UIEditBoxControl.empty() != true)	// 에디터 박스 랜더
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->isFocusOn())
		{
            switch(wParam)
			{
				//case VK_CONTROL:
				//	g_Control = true;
				//	return true;
				//case VK_SHIFT:	// 쉬프트 다운시 
				//	g_RegionCheck = true;
				//	g_Shift = true;
				//	(*ZOder)->m_XPibot = -1;
				//	(*ZOder)->UpdateText();
				//	return true;
				case VK_ESCAPE:	// ESC키 다운시
					g_Shift = false;
					(*ZOder)->m_bRegion = false;
					 (*ZOder)->SetFocusOff(); 
					 return true;
				case VK_RETURN:	// 엔터시
					 //SetFocus(g_hWnd);									// 에디터박스 컨트롤 포커스 해제
					 //(*ZOder)->SetFocusOff();
					 //this->FocusOff();

					if (m_UIButtonControl.empty() != true)	// 버튼중에서 엔터키로 반응하는 버튼이 발견되면 동작시킴
						for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
						if ((*ZOder)->isEnterOn())
						{
							func_t* ptr = GetMessageProcedure();						// 함수 포인터를 얻어온다.
							ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_BUTTON, (*ZOder)->m_nIndex);								// 해당 메시지 프로시져 실행
							return true;
						}
						return true;
				case VK_TAB:	// 텝키 다운시 포커스 전환
					g_Shift = false;
					// 현재 포커스를 기준으로 다음 활성화되지 않은 포커스를 찾는다.
					for(std::list<UIEditBoxControl*>::iterator ZOder2 = ZOder; ZOder2 != m_UIEditBoxControl.end(); ZOder2++)
						if ((*ZOder2)->isFocusOn() == false)
						{
							(*ZOder)->SetFocusOff();
							
							g_EditBoxFocusWindow = this->m_nIndex;
							g_EditBoxFocusControl = (*ZOder2)->m_nIndex;
							g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( (*ZOder2)->GetText() );
							g_cImeMgr.InputString();

							(*ZOder2)->SetFocusOn();
							return true;
						}

					// 끝까지 다 찾았는데 없다면 다시 처음부터 현재 에디터 박스 전 까지 다시 조사한다.
					for(std::list<UIEditBoxControl*>::iterator ZOder2 = m_UIEditBoxControl.begin(); ZOder2 != ZOder; ZOder2++)
						if ((*ZOder2)->isFocusOn() == false)
						{
							(*ZOder)->SetFocusOff();

							g_EditBoxFocusWindow = this->m_nIndex;
							g_EditBoxFocusControl = (*ZOder2)->m_nIndex;
							g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( (*ZOder2)->GetText() );
							g_cImeMgr.InputString();

							(*ZOder2)->SetFocusOn();
							return true;
						}


					break;
				//case VK_LEFT:
				//	g_Pibot++;
				//	
				//	if (g_Shift != true)
				//		(*ZOder)->m_XPibot = -2;

				//	(*ZOder)->UpdateText();
				//	(*ZOder)->SetStartTime();
				//	return true;
				//case VK_RIGHT:
				//	g_Pibot--;

				//	if (g_Shift != true)
				//		(*ZOder)->m_XPibot = -2;

				//	(*ZOder)->SetStartTime();
				//	(*ZOder)->UpdateText();
				//	return true;
				//case VK_END:
				//	g_Pibot = -1;

				//	if (g_Shift != true)
				//		(*ZOder)->m_XPibot = -2;

				//	(*ZOder)->SetStartTime();
				//	(*ZOder)->UpdateText();
				//	return true;
				//case VK_HOME:
				//	g_Pibot = 10000;

				//	if (g_Shift != true)
				//		(*ZOder)->m_XPibot = -2;

				//	(*ZOder)->SetStartTime();
				//	(*ZOder)->UpdateText();
				//	return true;
				//case VK_DELETE:
				//	g_Shift = false;
				//	g_Pibot--;
				//	(*ZOder)->SetStartTime();
				//	(*ZOder)->UpdateText();
				//	return true;
				case VK_UP:
				case VK_DOWN:
				case VK_PRIOR:
				case VK_NEXT:
					break;

				default:
					//if (g_Shift == true)
					(*ZOder)->m_XPibot = -2;
			}
			break;
		}

	switch(wParam)
	{
		case VK_RETURN:	// 엔터시
			if (m_UIButtonControl.empty() != true)	// 버튼중에서 엔터키로 반응하는 버튼이 발견되면 동작시킴
			for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
				if ((*ZOder)->isEnterOn())
				{
					func_t* ptr = GetMessageProcedure();						// 함수 포인터를 얻어온다.
					ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_BUTTON, (*ZOder)->m_nIndex);								// 해당 메시지 프로시져 실행
					return true;
				}
	}
	}
	return false;
}

// 키보드 업
bool UIWindow::OnKeyUp(WPARAM wParam)
{
	if (m_bFocus == true)
	{
	// 현재 윈도우의 에디터 박스가 활성화 상태하면 오프 시킴
	if (m_UIEditBoxControl.empty() != true)	// 에디터 박스 랜더
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->isFocusOn())
		{
		}
	}

	return false;
}

// 키보드 문자 받음
bool UIWindow::OnChar(WPARAM wParam)
{/*
	if (m_bFocus == true)
	{
	// 현재 윈도우의 에디터 박스가 활성화 상태하면 오프 시킴
	if (m_UIEditBoxControl.empty() != true)	// 에디터 박스 랜더
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->isFocusOn())
		{
            switch(wParam)
			{
				default:
					if (g_Shift == true)
					{
						
						(*ZOder)->UpdateText();
					}
			}
		}
	}
*/
	return false;
}

bool UIWindow::OnMouseWheel(WPARAM wParam)
{
	// 스크롤바 처리
	if (!(m_nIndex == _DIALOG_SKILL || m_nIndex == _DIALOG_CHATLOG1 || m_nIndex == _DIALOG_CHATLOG2))
		return false;

	if (m_UIScrollBarControl.empty() != true)
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
	{
		if( (int)wParam > 0 )
		{
			// 버튼 1 처리
			//(*ZOder)->Arrow1->SetButtonOver(); 
			int iValue = (*ZOder)->GetValue();
			
			if (iValue > 0 )
			{
				(*ZOder)->SetValue(iValue-1);
				(*ZOder)->UpdateScrollBar();
				func_t* ptr = GetMessageProcedure();		// 함수 포인터를 얻어온다.
				ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// 해당 메시지 프로시져 실행
				return true;
			}
			return true;
		}
		else if( (int)wParam < 0 )
		{
			// 버튼 2 처리
			//(*ZOder)->Arrow2->SetButtonOver(); 
			int iValue = (*ZOder)->GetValue();

			if (iValue < (*ZOder)->GetMaxValue())
			{
				(*ZOder)->SetValue(iValue+1);
				(*ZOder)->UpdateScrollBar();
				func_t* ptr = GetMessageProcedure();		// 함수 포인터를 얻어온다.
				ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// 해당 메시지 프로시져 실행
				return true;
			}
			return true;
		}
	}
	return false;
}

// 윈도우 명령 메시지 처리
bool UIWindow::OnSysCommand(WPARAM wParam)
{
	//CHTString str = "";

	//switch (LOWORD(wParam))
	//{
	//case ID_EDIT:
	//	switch (HIWORD(wParam))
	//	{
	//	case EN_KILLFOCUS:	// 알트 탭이나 기타 설정등으로 포커스를 잃어버렸다면 게임상에서도 커서를 꺼준다.
	//		if (m_UIEditBoxControl.empty() != true)	// 에디터 박스 랜더
	//			for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
	//				if ((*ZOder)->isFocusOn())
	//				{
	//					(*ZOder)->SetFocusOff();
	//					this->FocusOff();
	//					return true;
	//				}
	//	case EN_CHANGE:
	//		// 에디터 박스가 존재 한다면 활성화 되어 있는지 조사하여, 활성화 되어 있다면 기존 문자열에 추가 삽입한다.
	//		if (m_UIEditBoxControl.empty() != true)	// 에디터 박스 랜더
	//			for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
	//				if ((*ZOder)->isFocusOn())
	//				{
	//					(*ZOder)->UpdateText();		// 내부 컨트롤이 갱신되면 눈에 보이는 에디터박스도 갱신합니다.
	//					return true;
	//				}
	//	}
	//}
	return false;
}

// 모든 윈도우의 무브에 대해서 처리해줘야 할 부분
void UIWindow::OnMouseMove(int iXPos, int iYPos)
{
	//
	// Step 1) 마우스 오버상태중 윈도우 밖으로 나갈 경우는 버튼 오버상태를 노말로 바꿔주는 예외처리가 필요하다.
	//
	if (m_nMode != 0)
	{
		if (!CloseButton->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ))
		{ if (CloseButton->m_nButtonState != 0) CloseButton->SetButtonNormal(); }
		else
		{ if (CloseButton->m_nButtonState == 0) CloseButton->SetButtonOver();}
	}

	if (m_UIButtonControl.empty() != true) 	// 그 외의 버튼들이 있다면 같은 방법으로 처리
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if (!(*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY )) 
		{ if ((*ZOder)->m_nButtonState != 0) (*ZOder)->SetButtonNormal(); }
		else
		{ 
			if ((*ZOder)->m_nButtonState == 0)
			{
				if (m_bEnable == true) 
				{
					(*ZOder)->SetButtonOver();
				}
				else
				{
					(*ZOder)->SetButtonNormal();
				}
			}
		}

	if (m_bEnable == false)
		return;

	if (m_UIScrollBarControl.empty() != true) 	// 스크롤바의 버튼 처리
	{
		for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		{
			if (!(*ZOder)->isMouseDown()) // 스크롤바를 누르지 않고 있을때에만 처리
			{
				if (!(*ZOder)->Arrow1->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY )) 
				{ if ((*ZOder)->Arrow1->m_nButtonState != 0) (*ZOder)->Arrow1->SetButtonNormal(); }
				else
				{ if ((*ZOder)->Arrow1->m_nButtonState == 0) (*ZOder)->Arrow1->SetButtonOver(); }
			
				if (!(*ZOder)->Arrow2->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY )) 
				{ if ((*ZOder)->Arrow2->m_nButtonState != 0) (*ZOder)->Arrow2->SetButtonNormal(); }
				else
				{ if ((*ZOder)->Arrow2->m_nButtonState == 0) (*ZOder)->Arrow2->SetButtonOver(); }
			}
		}
	}

	// 슬롯박스 컨트롤이 무빙중이라면 이동시키고 리턴.
	if (m_UISlotBoxControl.empty() != true) 	// 그 외의 버튼들이 있다면 같은 방법으로 처리
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
	{
		if ((*ZOder)->isMouseDown())
		{
			if ((*ZOder)->isFixedIcon() == false )
			{
				if ((*ZOder)->isFirstMove() == true ) // 처음 드레그 엔 드롭을 시도하는 것이라면 레이어 최상으로 셋팅
				{
					g_cUIManager->m_bSlotBoxMoving = true;
					g_cUIManager->m_nSlotBoxWindowIndex = m_nIndex;
					g_cUIManager->m_nSlotBoxControlIndex = (*ZOder)->m_nIndex;
					g_cUIManager->m_nSlotBoxTextureID = (*ZOder)->GetUISlotTextureID();

					(*ZOder)->CheckMouseOver(false);
					(*ZOder)->ToolTipHide();
					(*ZOder)->CheckFirstMove(false);
					(*ZOder)->SetSlotBoxControl((*ZOder)->GetUISlotTextureID(), 2060);
				}

				if (g_cUIManager->m_bSlotBoxMoving == false)	// 이동이 정지되어 있는데 마우스다운 처리 되어 있다면 원래상태로 되돌린다.
					CancelSlotBoxImageMoving();

				HTvector3 fPos;
				fPos = Body->GetUITextureControlPos(); // 이미지 이동시에는 레이어 최상으로 재설정

				(*ZOder)->MoveImage(iXPos - 16 - (int)fPos.x, iYPos - 16 - (int)fPos.y);
				return;
			}
		}


		if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ) == false && (*ZOder)->isMouseOver() == true)
		{
			(*ZOder)->CheckMouseOver(false);
			(*ZOder)->ToolTipHide();
			break;
		}

	}

	// 정보창 띄움 여부 체크 (2 Pass 를 통해 셋 되어 있는 슬롯을 모두 닫고, 다시 쇼 윈도우 한다.
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY ) == true && (*ZOder)->isMouseOver() == false)
		{
			int hr = g_cUIManager->HT_CheckRegionWithPoint(iXPos, iYPos); 
			if (hr == m_nIndex) // 현재 가장 앞에 있는 창에만 정보 보여줌
			{
				if (g_cUIManager->m_bSlotBoxMoving == true)	// 아이템 무빙중이라면 보여주지 않는다.
					return;

				(*ZOder)->CheckMouseOver(true);
				
				if (g_cObjectInfo)
					g_cObjectInfo->HT_vObjectInfo_InfoCheck( this->m_nIndex, (*ZOder)->m_nIndex );	// 슬롯박스 정보 출력
				
				(*ZOder)->ToolTipShow();
				//g_cUIManager->HT_ShowWindow(m_nIndex);
				return;
			}
		}


	// 무빙영역이 사용중이고 무빙중이라면 윈도우를 움직여준다.
	if (m_bMovingRegionUsing == true && MovingRegion->isMouseDown())
	{
		AdxPosX = AdxPosX - g_cUIManager->m_MousePosX;
		AdxPosY = AdxPosY - g_cUIManager->m_MousePosY;

//		if (AdxPosY > 100 || AdxPosY < -100) AdxPosY = 0;
//		if (AdxPosX > 100 || AdxPosX < -100) AdxPosX = 0;

		this->MoveWindow(iXPos+iMouseButtonDownXPos, iYPos+iMouseButtonDownYPos);

		// 만약 무빙중 자석 기능의 윈도우에 근접하면 붙는다. 또는 붙은 상태에서 움직이면 자석기능이 해제된다.
		if (m_bMagnet == true) 
			this->SetMagnetProcessing();

		// 차일드 윈도우들도 처리해준다. (자석기능으로 붙은 주변 윈도우들도 같이 움직인다.)
		this->SetChildMagnetProcessing();

		AdxPosX = g_cUIManager->m_MousePosX;
		AdxPosY = g_cUIManager->m_MousePosY;
	}
}

// 무빙중인 해당 윈도우의 슬롯 이미지를 복귀합니다.
void UIWindow::CancelSlotBoxImageMoving()
{
	if (m_UISlotBoxControl.empty() != true) 	// 그 외의 버튼들이 있다면 같은 방법으로 처리
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->isMouseDown()) 
		{
			(*ZOder)->CheckMouseDown(false); 
			(*ZOder)->CheckFirstMove(true);
			(*ZOder)->ToolTipHide();
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
}

// 탑 윈도우가 되었을때만 처리해야 할 부분
void UIWindow::OnMouseMoveOnlyTop(int iXPos, int iYPos)
{
	// 스크롤바가 무빙중이라면 이동시키고 리턴. 타입에 따라 수직이동인지 수평이동인지 처리한다.
	if (m_UIScrollBarControl.empty() != true) 	// 그 외의 버튼들이 있다면 같은 방법으로 처리
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		if ((*ZOder)->isMouseDown()) 
		{
			HTvector3 fWindowPos = Body->GetUITextureControlPos();

			// 스크롤바가 수직인지 수평인지에 따라 움직이는 좌표 한쪽 고정
			if ((*ZOder)->GetType() == 0)	// 수직이면 수직이동
			{
				// 스크롤바 위치 계산
				float fPos = ((float)(iYPos - 7) - fWindowPos.y) - (float)(*ZOder)->m_nPosY;
				float fMaxPos = (float)(*ZOder)->m_nMaxValue;
				float fRatio = ((float)(*ZOder)->m_nLengthY - 14.0f) / fMaxPos;

				int iValue = (int)(fPos / fRatio);
				int iPreValue = (*ZOder)->GetValue();

				// 만약 이동범위를 넘어가면 고정한다.
				if (iValue < 0) iValue = 0;
				if (iValue > (int)fMaxPos) iValue = (int)fMaxPos;
			
				// 값의 변화가 있을때만 갱신 및 호출
				if (iPreValue != iValue)	
				{
					(*ZOder)->SetValue(iValue);
					(*ZOder)->UpdateScrollBar();

					func_t* ptr = GetMessageProcedure();		// 함수 포인터를 얻어온다.
					ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// 해당 메시지 프로시져 실행
					return;
				}
			}
			else	// 수평이면 수평이동
			{
				// 스크롤바 위치 계산
				float fPos = ((float)(iXPos - 7) - fWindowPos.x) - (float)(*ZOder)->m_nPosX;
				float fMaxPos = (float)(*ZOder)->m_nMaxValue;
				float fRatio = ((float)(*ZOder)->m_nLengthX - 14.0f) / fMaxPos;

				int iValue = (int)(fPos / fRatio);
				int iPreValue = (*ZOder)->GetValue();

				// 만약 이동범위를 넘어가면 고정한다.
				if (iValue < 0) iValue = 0;
				if (iValue > (int)fMaxPos) iValue = (int)fMaxPos;
			
				// 값의 변화가 있을때만 갱신 및 호출
				if (iPreValue != iValue)	
				{
					(*ZOder)->SetValue(iValue);
					(*ZOder)->UpdateScrollBar();

					func_t* ptr = GetMessageProcedure();		// 함수 포인터를 얻어온다.
					ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SCROLLBAR, (*ZOder)->m_nIndex);							// 해당 메시지 프로시져 실행
					return;
				}
				
			}
			return;
		}

	//
	// Step 2) 그외의 경우에는 속도향상을 위해 탑 윈도우 영역 밖에서의 반응은 무조건 리턴한다.
	//
	if (Body->CheckRegionWithPoint(iXPos, iYPos) == false && Body->isMouseDown() == false)
		return;

	//
	// Step 3) 타이틀 영역을 다운했을 경우에만 이동이 가능하다.
	//
	if (TitleBar->isMouseDown())	// 타이틀 무브다운일경우에만 전체 이동 (무브처리는 보디만 해준다 나머진 랜더에서 자동처리)
	{
		AdxPosX = AdxPosX - g_cUIManager->m_MousePosX;
		AdxPosY = AdxPosY - g_cUIManager->m_MousePosY;

//		if (AdxPosY > 100 || AdxPosY < -100) AdxPosY = 0;
//		if (AdxPosX > 100 || AdxPosX < -100) AdxPosX = 0;

		this->MoveWindow(iXPos+iMouseButtonDownXPos, iYPos+iMouseButtonDownYPos);

		// 만약 무빙중 자석 기능의 윈도우에 근접하면 붙는다. 또는 붙은 상태에서 움직이면 자석기능이 해제된다.
		if (m_bMagnet == true) 
			this->SetMagnetProcessing();

		// 차일드 윈도우들도 처리해준다. (자석기능으로 붙은 주변 윈도우들도 같이 움직인다.)
		this->SetChildMagnetProcessing();

		AdxPosX = g_cUIManager->m_MousePosX;
		AdxPosY = g_cUIManager->m_MousePosY;
	}

	//
	// Step 4) 스케일바 영역을 다운했을 경우 사이즈 조절 가능
	//
	if (ScaleBar->isMouseDown())
	{
		HTvector3 fPos;
		fPos = Body->GetUITextureControlPos();
		// 최소 영역보다 작게 설정하려고 할 경우 무시한다.
		int RealX, RealY;
		RealX =  iXPos + iMouseButtonDownXPosTail - (int)fPos.x;
		RealY =  iYPos + iMouseButtonDownYPosTail - (int)fPos.y;

		if ( RealX < UI_MIN_RESIZEX) RealX = UI_MIN_RESIZEX;
		if ( RealY < UI_MIN_RESIZEY) RealY = UI_MIN_RESIZEY;

		this->ScaleWindow(RealX, RealY);
	}
}

// 자신에게 붙은 윈도우들 처리 (같이 움직여 준다.)
void UIWindow::SetChildMagnetProcessing()
{
	// 자석상태인 윈도우들을 조사해서 움직인 만큼만 무빙시켜준다.
	for(std::list<unsigned int>::iterator ZOder = m_UIMagnetIndex.begin(); ZOder != m_UIMagnetIndex.end(); ++ZOder)
		if (g_cUIManager->HT_GetMagnetState((*ZOder)))	// 해당 윈도우의 자석상태 얻기
		{
			g_cUIManager->HT_MoveWindow((*ZOder), -AdxPosX, -AdxPosY, 1);	// 타겟위치에서 이동한양만큼 셋팅해서 무빙시킨다.
			// 상속된 윈도우에 대해서 다시 상속 처리를 하고 싶다면 재귀호출을 하면 된다. 하지만 상속관계가 원이 될경우 무한 루프에 빠지므로 주의
		}
}

// 매그닛 처리 함수
void UIWindow::SetMagnetProcessing()
{
	// 자신의 위치는 알고 있으므로 타겟 윈도우의 위치를 얻어온다.
	int TposX, TposY; HTvector3 Tpos;

	// 현 윈도우의 사이즈를 얻어온다.
	HTvector3 WindowSize = this->GetWindowSize();
	HTvector3 WindowPos = this->GetWindowPos();
	
	//m_bMagnetUsing = true;

	bool bCheck = false, bCheck2 = false;
	if (m_iMagnetWindowIndex != -1)	// 윈도우에 상속된 경우라면 해당 윈도우 외각라인으로 자석처리
	{
		// 현 윈도우의 사이즈를 얻어온다.
		g_cUIManager->HT_GetWindowPos(m_iMagnetWindowIndex, TposX, TposY);
		HTvector3 TWindowSize = g_cUIManager->HT_GetWindowSize(m_iMagnetWindowIndex);

		if (WindowPos.x >= TposX + TWindowSize.x && WindowPos.x < TposX + TWindowSize.x + UI_MAGNET_DISTANCE_EXIT
			&& WindowPos.y + WindowSize.y >= TposY && WindowPos.y < TposY + TWindowSize.y) 
		{
			if ( AdxPosX > 0 || m_bMagnetUsingPro == true) 
			{ 
				bCheck2 = true; WindowPos.x = TposX + TWindowSize.x; m_bMagnetUsingPro = true; 

				if (m_bMagnetUsingPro == true)
					AdxPosX = 0;
			}
			else
			{ AdxPosX = 0;}
		}
		else if (WindowPos.x + WindowSize.x <= TposX && WindowPos.x + WindowSize.x > TposX - UI_MAGNET_DISTANCE_EXIT
			&& WindowPos.y + WindowSize.y >= TposY && WindowPos.y < TposY + TWindowSize.y) 
		{
			if ( AdxPosX < 0 || m_bMagnetUsingPro == true) 
			{ 
				bCheck2 = true; WindowPos.x = TposX - WindowSize.x; m_bMagnetUsingPro = true;	

				if (m_bMagnetUsingPro == true)
					AdxPosX = 0;
			}
			else
			{ AdxPosX = 0;}
		}
		else
		{	bCheck = true;	}

		if (WindowPos.y + WindowSize.y <= TposY && WindowPos.y + WindowSize.y > TposY - UI_MAGNET_DISTANCE_EXIT
			&& WindowPos.x + WindowSize.x >= TposX && WindowPos.x < TposX + TWindowSize.x) 
		{
			if ( AdxPosY < 0 || m_bMagnetUsingPro == true) 
			{ 
				bCheck2 = true; WindowPos.y = TposY - WindowSize.y; m_bMagnetUsingPro = true; 

				if (m_bMagnetUsingPro == true)
					AdxPosY = 0;
			
			}
			else
			{ AdxPosY = 0;}
		}
		else if (WindowPos.y >= TposY + TWindowSize.y && WindowPos.y < TposY + TWindowSize.y + UI_MAGNET_DISTANCE_EXIT
			&& WindowPos.x + WindowSize.x >= TposX && WindowPos.x < TposX + TWindowSize.x)  
		{
			if ( AdxPosY > 0 || m_bMagnetUsingPro == true)	
			{ 
				bCheck2 = true; WindowPos.y = TposY + TWindowSize.y; m_bMagnetUsingPro = true; 

				if (m_bMagnetUsingPro == true)
					AdxPosY = 0;
			}
			else
			{ AdxPosY = 0;}
		}
		else
		{
			if (bCheck == true) m_bMagnetUsingPro = false;	
		}
		
		m_bMagnetUsing = bCheck2;

		this->MoveWindow((int)WindowPos.x, (int)WindowPos.y);
		m_posX = (int)WindowPos.x;
		m_posY = (int)WindowPos.y;
		return;
	}
	
	// 일반의 경우에는 해상도 외각에서 자석처리됨

	if (WindowPos.x < UI_MAGNET_DISTANCE_EXIT && WindowPos.x >= 1) 
	{
		if ( AdxPosX > 0 || m_bMagnetUsingPro == true) 
		{ 
			bCheck2 = true; WindowPos.x = 1; m_bMagnetUsingPro = true; 
			AdxPosX2 = -1;
		}
	}
	else if (WindowPos.x + WindowSize.x > g_cUIManager->m_iScreenX - UI_MAGNET_DISTANCE_EXIT && WindowPos.x + WindowSize.x <= g_cUIManager->m_iScreenX) 
	{
		if ( AdxPosX < 0 || m_bMagnetUsingPro == true) 
		{ 
			bCheck2 = true; WindowPos.x = g_cUIManager->m_iScreenX - WindowSize.x; m_bMagnetUsingPro = true;
			AdxPosX2 = 1;
		}
	}
	else
	{	
		bCheck = true;	
		AdxPosX2 = 0;
	}

	if (WindowPos.y < UI_MAGNET_DISTANCE_EXIT && WindowPos.y >= 1) 
	{
		if ( AdxPosY > 0 || m_bMagnetUsingPro == true) 
		{ 
			bCheck2 = true; WindowPos.y = 1; m_bMagnetUsingPro = true; 
			AdxPosY2 = -1;
		}
	}
	else if (WindowPos.y + WindowSize.y > g_cUIManager->m_iScreenY - UI_MAGNET_DISTANCE_EXIT - 17 && WindowPos.y + WindowSize.y <= g_cUIManager->m_iScreenY - 17) 
	{
		if ( AdxPosY < 0 || m_bMagnetUsingPro == true)	
		{ 
			bCheck2 = true; WindowPos.y = g_cUIManager->m_iScreenY - WindowSize.y - 17; m_bMagnetUsingPro = true;	
			AdxPosX2 = 1;
		}
	}
	else
	{
		if (bCheck == true) m_bMagnetUsingPro = false;	
		AdxPosY2 = 0;
	}
	
	m_bMagnetUsing = bCheck2;

	this->MoveWindow((int)WindowPos.x, (int)WindowPos.y);
}

// 무빙영역 사용여부 설정
void UIWindow::SetMovingRegion(bool isOn, int iPosX, int iPosY, int iSizeX, int iSizeY)
{
	UITexture oTexture;

	if (isOn)
	{
		m_bMovingRegionUsing = true;
		
		delete MovingRegion;
		MovingRegion = new UITextureControl;
		oTexture.Layer = 1400; oTexture.PosX = iPosX; oTexture.PosY = iPosY; oTexture.SizeX = iSizeX; oTexture.SizeY = iSizeY; oTexture.TextureID = 0; oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
		MovingRegion->CreateUITextureControl(0, oTexture);
		return;
	}

	m_bMovingRegionUsing = false;
}

// 체크박스 컨트롤 생성
void UIWindow::CreateCheckBoxControl(unsigned int nIndex, int XPos, int YPos, bool bValue, int BorderTextureID, int CheckTextureID, int SizeX, int SizeY)
{
	UICheckBoxControl* pUICheckBoxControl = new UICheckBoxControl;
	pUICheckBoxControl->m_nIndex = nIndex;
	pUICheckBoxControl->CreateUICheckBoxControl(nIndex, XPos, YPos, bValue, BorderTextureID, CheckTextureID, SizeX, SizeY);
	m_UICheckBoxControl.push_front(pUICheckBoxControl);
}

// 체크박스 컨트롤 제거
void UIWindow::DeleteCheckBoxControl(unsigned int nIndex)
{
	for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UICheckBoxControl.erase( ZOder );
			return;
		}
}

// 체크박스에 값을 설정
void UIWindow::SetCheckBoxControl(unsigned int nIndex, bool bCheck)
{
	for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetValue(bCheck);
		}
}

// 체크박스의 값을 얻음
bool UIWindow::GetCheckBoxControl(unsigned int nIndex)
{
	for(std::list<UICheckBoxControl*>::iterator ZOder = m_UICheckBoxControl.begin(); ZOder != m_UICheckBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			return (*ZOder)->GetValue();
		}
	return NULL;
}



// 텍스처 컨트롤 생성
void UIWindow::CreateTextureControl(unsigned int nIndex, UITexture oTexture )
{
	UITextureControl* pUITextureControl = new UITextureControl;
	pUITextureControl->m_nIndex = nIndex;
	pUITextureControl->CreateUITextureControl(nIndex, oTexture);
	m_UITextureControl.push_front(pUITextureControl);
}

// 텍스처 컨트롤 제거
void UIWindow::DeleteTextureControl(unsigned int nIndex)
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UITextureControl.erase( ZOder );
			break;
		}
}

// 텍스처 출력 온오프 설정 (true = 온 . false = 오프)
void UIWindow::SetTextureControlDisplay(unsigned int nControlIndex, bool bOn)
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			if (bOn == true)
				(*ZOder)->Show();
			else
				(*ZOder)->Hide();
		}
}

// 텍스처를 변경합니다.
void UIWindow::SetTextureControlImage(unsigned int nIndex, int iTextureID )
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			bool m_bCheckRegion = (*ZOder)->isRegion();
			bool m_bCheckMouseDown = (*ZOder)->isMouseDown();
			bool m_bCheckMouseRDown = (*ZOder)->isMouseRDown();
			bool m_bEnable = (*ZOder)->isEnableOn();
			bool m_bDisplay = (*ZOder)->isDisplay();

			UITexture oTexture = (*ZOder)->GetUITextureControl();
			oTexture.TextureID = iTextureID;

			HT_DELETE( *ZOder );
			m_UITextureControl.erase( ZOder );

			UITextureControl* pUITextureControl = new UITextureControl;
			pUITextureControl->m_nIndex = nIndex;
			pUITextureControl->CreateUITextureControl(nIndex, oTexture);
			m_UITextureControl.push_front(pUITextureControl);
			
			pUITextureControl->CheckRegion(m_bCheckRegion); 
			pUITextureControl->CheckMouseDown(m_bCheckMouseDown);
			pUITextureControl->CheckMouseRDown(m_bCheckMouseRDown);
			if (m_bEnable) pUITextureControl->EnableOn(); else pUITextureControl->EnableOff();
			if (m_bDisplay) pUITextureControl->Show(); else pUITextureControl->Hide();
			return;
		}
}

// 텍스처 컨트롤의 좌표를 얻어옵니다.
HTvector3 UIWindow::GetTextureControlPos(unsigned int nControlIndex)
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			return (*ZOder)->GetUITextureControlPos();
	return NULL;
}

// 텍스처 색상을 변경합니다.
void UIWindow::SetTextureColor(unsigned int nIndex, HT_COLOR clr )
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetColor(clr);
			return;
		}
}

// 슬롯박스 컨트롤 생성
void UIWindow::CreateSlotBoxControl(unsigned int nIndex, UITexture oTexture)
{
	UISlotBoxControl* pUISlotBoxControl = new UISlotBoxControl;
	pUISlotBoxControl->m_nIndex = nIndex;
	pUISlotBoxControl->CreateUISlotBoxControl(nIndex, oTexture);
	m_UISlotBoxControl.push_front(pUISlotBoxControl);
}

// 슬롯박스 컨트롤 제거
void UIWindow::DeleteSlotBoxControl(unsigned int nIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UISlotBoxControl.erase( ZOder );
			return;
		}
}

// 자석기능 설정 (0 = 취소, -1 = 바탕화면)
void UIWindow::SetMagnet(unsigned int nTargetIndex)
{
	m_bMagnetUsing = false;
	m_iMagnetWindowIndex = nTargetIndex;

	if (nTargetIndex == 0)
	{
		m_bMagnet = false;	// 설정 취소
		g_cUIManager->MagnetMgr(nTargetIndex, m_nIndex, false);
	}
	else
	{
		m_bMagnet = true;	// 설정
		g_cUIManager->MagnetMgr(nTargetIndex, m_nIndex, true);
	}
}

// 타겟 윈도우 bInsert = true 삽입 false = 삭제
void UIWindow::MagnetMgr(unsigned int nTargetIndex, bool bInsert)
{
	if (bInsert == true)	// 삽입
	{
		m_UIMagnetIndex.push_back(nTargetIndex);
	}
	else	// 삭제
	{
		for(std::list<unsigned int>::iterator ZOder = m_UIMagnetIndex.begin(); ZOder != m_UIMagnetIndex.end(); ++ZOder)
			if ((*ZOder) == nTargetIndex)
			{
				m_UIMagnetIndex.erase(ZOder);
				return;
			}
	}
}


// 슬롯박스 컨트롤 값삽입
void UIWindow::SetSlotBoxControl(unsigned int nIndex, int TextureID, int iLayer)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ( (*ZOder)->m_nIndex == nIndex )
		{
			(*ZOder)->SetSlotBoxControl(TextureID, iLayer);
			return;
		}
}

// 슬롯박스의 아이콘 위치를 재설정합니다.
void UIWindow::SetSlotBoxControlPosImage(unsigned int nControlIndex, int iPosX, int iPosY )
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ( (*ZOder)->m_nIndex == nControlIndex )
		{
			(*ZOder)->SetSlotBoxControlPosImage(iPosX, iPosY);
			return;
		}
}

// 내부처리용 (현재 위치에 슬롯이 존재하는가? 존재한다면 )
int UIWindow::CheckRegionWithSlotBoxPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY )
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos, iWindowPosX, iWindowPosY))
			return (*ZOder)->m_nIndex;
	return 0;
}

// 해당 슬롯의 텍스처ID 얻기
int	UIWindow::GetUISlotTextureID(unsigned int nIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			return (*ZOder)->GetUISlotTextureID();
	return 0;
}

// 슬롯박스의 쿨타임 설정
void UIWindow::SetSlotBoxCoolTime(unsigned int nIndex, DWORD DealyTime, DWORD PastTime)
{	
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetSlotBoxCoolTime(DealyTime, PastTime);
			return;
		}
}

// 슬롯박스의 쿨타임 해제
void UIWindow::SetSlotBoxCoolTimeCancel(unsigned int nIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetSlotBoxCoolTimeCancel();
			return;
		}
}

// 슬롯박스가 쿨타임중인지?
bool UIWindow::isSlotBoxCoolTime(unsigned int nIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			return (*ZOder)->isSlotBoxCoolTime();
	return false;
}

// 슬롯박스 컨트롤에서 툴팁을 사용합니다.
void UIWindow::SetSlotBoxToolTipOn(unsigned int nControlIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetToolTipOn();
			return;
		}
}

// 슬롯박스 컨트롤에서 툴팁을 사용하지 않습니다.
void UIWindow::SetSlotBoxToolTipOff(unsigned int nControlIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetToolTipOff();
			return;
		}
}

// 슬롯박스 툴팁의 해당 텍스트 설정(라인별)
void UIWindow::SetSlotBoxControlToolTipText(unsigned int nControlIndex, unsigned int nIndex, CHTString str)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextLabelControl(nIndex, str);
			return;
		}
}

// 슬롯박스 툴팁의 해당 출력 라인 인덱스 설정 (해당 라인까지만 출력함)
void UIWindow::SetSlotBoxControlTextIndex(unsigned int nControlIndex, unsigned int nIndex)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextLabelControlIndex(nIndex);
			return;
		}
}

// 슬롯박스 아이콘 움직임 고정 여부 설정
void UIWindow::SetSlotBoxImageFixed(unsigned int nControlIndex, bool bFixedIcon)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetSlotBoxImageFixed(bFixedIcon);
			return;
		}
}

// 슬롯박스 툴팁 해당 라인 텍스트 색상 변경
void UIWindow::SetSlotBoxControlToolTipTextColor(unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextColorLabelControl(nIndex, clr);
			return;
		}
}

// 슬롯박스 사용여부 결정
void UIWindow::SetSlotBoxControlEnable(unsigned int nControlIndex, bool bEnable)
{
	for(std::list<UISlotBoxControl*>::iterator ZOder = m_UISlotBoxControl.begin(); ZOder != m_UISlotBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetSlotBoxControlEnable(bEnable);
			return;
		}
}


// 스크롤바 컨트롤 생성
void UIWindow::CreateScrollBarControl(unsigned int nIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType)
{
	UIScrollBarControl* pUIScrollBarControl = new UIScrollBarControl;
	pUIScrollBarControl->m_nIndex = nIndex;
	pUIScrollBarControl->CreateUIScrollBarControl(nIndex, oTImage, oTLine, oTArrow1, oTArrow2, iMaxValue, iType);
	m_UIScrollBarControl.push_front(pUIScrollBarControl);
}

// 스크롤바 컨트롤 제거
void UIWindow::DeleteScrollBarControl(unsigned int nIndex)
{
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UIScrollBarControl.erase( ZOder );
			return;
		}
}

// 해당 스크롤바의 값을 설정합니다.
void UIWindow::SetScrollBarValue(unsigned int nIndex, int iValue)
{
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetValue(iValue);
			return;
		}
}

// 해당 스크롤바의 최대 값을 설정합니다.
void UIWindow::SetScrollBarMaxValue(unsigned int nIndex, int iValue)
{
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetMaxValue(iValue);
			return;
		}
}

// 해당 스크롤바의 값을 얻어옵니다.
int UIWindow::GetScrollBarValue(unsigned int nIndex)
{
	for(std::list<UIScrollBarControl*>::iterator ZOder = m_UIScrollBarControl.begin(); ZOder != m_UIScrollBarControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			return (*ZOder)->GetValue();
	return 0;
}

// 타이머 컨트롤 생성
void UIWindow::CreateTimerControl(unsigned int nIndex, DWORD dwSetTime, int iStyle)
{
	UITimerControl* pUITimerControl = new UITimerControl;
	pUITimerControl->m_nIndex = nIndex;
	pUITimerControl->CreateUITimerControl(nIndex, dwSetTime, iStyle);
	m_UITimerControl.push_front(pUITimerControl);
}

// 타이머 컨트롤 제거
void UIWindow::DeleteTimerControl(unsigned int nIndex)
{
	for(std::list<UITimerControl*>::iterator ZOder = m_UITimerControl.begin(); ZOder != m_UITimerControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UITimerControl.erase( ZOder );
			break;
		}
}

// 타이머 온
void UIWindow::EnableOnTimerControl(unsigned int nIndex)
{
	for(std::list<UITimerControl*>::iterator ZOder = m_UITimerControl.begin(); ZOder != m_UITimerControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			(*ZOder)->EnableOn();
}

// 타이머 오프
void UIWindow::EnableOffTimerControl(unsigned int nIndex)
{
		for(std::list<UITimerControl*>::iterator ZOder = m_UITimerControl.begin(); ZOder != m_UITimerControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			(*ZOder)->EnableOff();
}

// 라벨 컨트롤 생성
void UIWindow::CreateLabelControl(unsigned int nIndex, UIText oText)
{
	UILabelControl* pUILabelControl = new UILabelControl;
	pUILabelControl->m_nIndex = nIndex;
	pUILabelControl->CreateUILabelControl(nIndex, oText);
	m_UILabelControl.push_front(pUILabelControl);
}

// 라벨 컨트롤 제거
void UIWindow::DeleteLabelControl(unsigned int nIndex)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UILabelControl.erase( ZOder );
			break;
		}
}

// 라벨 컨트롤의 텍스트 변경
void UIWindow::SetTextLabelControl(unsigned int nIndex, CHTString str)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetText(str);
			break;
		}
}

// 라벨 컨트롤의 텍스트 얻기
CHTString UIWindow::GetTextLabelControl(unsigned int nIndex)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
	if ((*ZOder)->m_nIndex == nIndex)
		return (*ZOder)->GetText();

	CHTString str = "";
	return str;
}

// 라벨 컨트롤의 텍스트컬러 변경
void UIWindow::SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextColor(clr);
			break;
		}
}

// 라벨 컨트롤의 텍스트쉐도우컬러 변경
void UIWindow::SetTextShadowColorLabelControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextShadowColor(clr);
			break;
		}
}

// 라벨 컨트롤의 글자 배치를 변경합니다.
void UIWindow::SetArrangementLabelControl(unsigned int nIndex, int iDirection)
{
	for(std::list<UILabelControl*>::iterator ZOder = m_UILabelControl.begin(); ZOder != m_UILabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetArrangement(iDirection);
			break;
		}
}

// 롱라벨 컨트롤 생성
void UIWindow::CreateLongLabelControl(unsigned int nIndex, UILongText oText)
{
	UILongLabelControl* pUILongLabelControl = new UILongLabelControl;
	pUILongLabelControl->m_nIndex = nIndex;
	pUILongLabelControl->CreateUILabelControl(nIndex, oText);
	m_UILongLabelControl.push_front(pUILongLabelControl);
}

// 롱라벨 컨트롤 제거
void UIWindow::DeleteLongLabelControl(unsigned int nIndex)
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UILongLabelControl.erase( ZOder );
			break;
		}
}

// 롱라벨 컨트롤의 텍스트 변경
void UIWindow::SetTextLongLabelControl(unsigned int nIndex, HTtchar str[])
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetText(str);
			break;
		}
}

// 롱라벨 컨트롤의 텍스트 얻기
HTtchar* UIWindow::GetTextLongLabelControl(unsigned int nIndex)
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
	if ((*ZOder)->m_nIndex == nIndex)
		return (*ZOder)->GetText();

	CHTString str = "";
	return str;
}

// 롱라벨 컨트롤의 텍스트컬러 변경
void UIWindow::SetTextColorLongLabelControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextColor(clr);
			break;
		}
}

// 롱라벨 컨트롤의 텍스트쉐도우컬러 변경
void UIWindow::SetTextShadowColorLongLabelControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextShadowColor(clr);
			break;
		}
}

// 롱라벨 컨트롤의 글자 배치를 변경합니다.
void UIWindow::SetArrangementLongLabelControl(unsigned int nIndex, int iDirection)
{
	for(std::list<UILongLabelControl*>::iterator ZOder = m_UILongLabelControl.begin(); ZOder != m_UILongLabelControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetArrangement(iDirection);
			break;
		}
}


// 에디터박스 컨트롤 생성
void UIWindow::CreateEditBoxControl(unsigned int nIndex, UITexture oTexture, UIText oText, int iStyle)
{
	UIEditBoxControl* pUIEditBoxControl = new UIEditBoxControl;
	pUIEditBoxControl->m_nIndex = nIndex;
	pUIEditBoxControl->CreateUIEditBoxControl(nIndex, oTexture, oText, iStyle);
	m_UIEditBoxControl.push_front(pUIEditBoxControl);
}

// 에디터박스 컨트롤 제거
void UIWindow::DeleteEditBoxControl(unsigned int nIndex)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UIEditBoxControl.erase( ZOder );
			break;
		}
}

// 에디터박스 컨트롤의 텍스트 변경
void UIWindow::SetTextEditBoxControl(unsigned int nIndex, CHTString str)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetText(str);
			break;
		}
}

// 에디트박스의 모드를 설정합니다
void UIWindow::SetEditBoxControlMode(unsigned int nIndex, int iMode)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetMode(iMode);
			break;
		}
}

// 에디터박스 컨트롤의 텍스트컬러 변경
void UIWindow::SetTextColorEditBoxControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextColor(clr);
			break;
		}
}

// 에디터박스 컨트롤의 텍스트쉐도우컬러 변경
void UIWindow::SetTextShadowColorEditBoxControl(unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetTextShadowColor(clr);
			break;
		}
}

// 에디터박스 컨트롤 모드 변경
CHTString UIWindow::GetTextEditBoxControl(unsigned int nIndex)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
			return (*ZOder)->GetText();
	return NULL;
}

// 에디터박스 컨트롤의 입력글자 길이를 제한합니다.
void UIWindow::SetEditBoxControlLimitText(unsigned int nControlIndex, unsigned int uiSize)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetLimitText(uiSize);
}


// 에디터박스 컨트롤이 지금 포커스가 켜져있는지 꺼져있는지 조사합니다.
bool UIWindow::isEditBoxFocusOn(unsigned int nControlIndex)
{
	for(std::list<UIEditBoxControl*>::iterator ZOder = m_UIEditBoxControl.begin(); ZOder != m_UIEditBoxControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			return (*ZOder)->isFocusOn();
	return false;
}

// 버튼 컨트롤의 상태를 변경합니다.
void UIWindow::SetButtonControlState(unsigned int nIndex, int iCheck)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetButtonState(iCheck);

			if (iCheck == 3)	// 만약 플래쉬 버튼이라면 시간체크
				(*ZOder)->m_dFlashButtonStartTime = timeGetTime();

			switch((*ZOder)->m_nButtonState)
			{
				case 1:	(*ZOder)->SetButtonNormal(); return;
				case 2:	(*ZOder)->SetButtonOver(); return;
				case 3:	(*ZOder)->SetButtonDown(); return;
				default: (*ZOder)->SetButtonNormal(); return;
			}
		}
}


// 버튼 컨트롤에서 툴팁 내용을 변경합니다.
void UIWindow::SetButtonToolTip(unsigned int nControlIndex, CHTString str)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetToolTipStr(str);
}

// 버튼 컨트롤에서 툴팁을 사용합니다.
void UIWindow::SetButtonToolTipOn(unsigned int nControlIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetToolTipOn();
}

// 버튼 컨트롤에서 툴팁을 사용하지 않습니다.
void UIWindow::SetButtonToolTipOff(unsigned int nControlIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetToolTipOff();
}

// 버튼 툴팁의 해당 텍스트 설정(라인별)
void UIWindow::SetButtonControlToolTipText(unsigned int nControlIndex, unsigned int nIndex, CHTString str)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextLabelControl(nIndex, str);
			break;
		}
}

// 버튼 툴팁의 해당 출력 라인 인덱스 설정 (해당 라인까지만 출력함)
void UIWindow::SetButtonControlTextIndex(unsigned int nControlIndex, unsigned int nIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextLabelControlIndex(nIndex);
			break;
		}
}

// 버튼 툴팁 해당 라인 텍스트 색상 변경
void UIWindow::SetButtonControlToolTipTextColor(unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			(*ZOder)->SetTextColorLabelControl(nIndex, clr);
			break;
		}
}


// 해당 버튼의 엔터기능을 킵니다.
void UIWindow::SetButtonEnterOn(unsigned int nControlIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetEnterOn();
}

// 해당 버튼의 엔터기능을 끕니다.
void UIWindow::SetButtonEnterOff(unsigned int nControlIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
			(*ZOder)->SetEnterOff();
}

// 버튼 활성화 상태 설정
void UIWindow::SetButtonEnable(unsigned int nControlIndex, bool bEnable)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nControlIndex)
		{
			if ( bEnable == true)
			{
				(*ZOder)->EnableOn();
				(*ZOder)->Show();
			}
			else
			{
				(*ZOder)->EnableOff();
				(*ZOder)->Hide();
			}
		}
}


// 버튼 컨트롤 생성
void UIWindow::CreateButtonControl(unsigned int nIndex, UITexture oTexture[3])
{
	UIButtonControl* pUIButtonControl = new UIButtonControl;
	pUIButtonControl->m_nIndex = nIndex;
	pUIButtonControl->CreateUIButtonControl(nIndex, oTexture);
	m_UIButtonControl.push_front(pUIButtonControl);
}


// 버튼 컨트롤 제거
void UIWindow::DeleteButtonControl(unsigned int nIndex)
{
	for(std::list<UIButtonControl*>::iterator ZOder = m_UIButtonControl.begin(); ZOder != m_UIButtonControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UIButtonControl.erase( ZOder );
			break;
		}
}


// 해당 텍스처 컨트롤의 정보값 변경
void UIWindow::SetRegionTextureControl(unsigned int nIndex, int iXpos, int iYpos, int iSizeX, int iSizeY)
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->Move(iXpos, iYpos);
			(*ZOder)->SetScale(iSizeX, iSizeY);
			break;
		}
}

// 해당 텍스처의 스케일을 변경합니다.
void UIWindow::SetTextureControlScale(unsigned int nIndex, int iSizeX, int iSizeY, int iOSizeX, int iOSizeY)
{
	for(std::list<UITextureControl*>::iterator ZOder = m_UITextureControl.begin(); ZOder != m_UITextureControl.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			(*ZOder)->SetScale(iSizeX, iSizeY, iOSizeX, iOSizeY);
			break;
		}
}

// 윈도우의 위치를 반환한다.
HTvector3 UIWindow::GetWindowPos()
{
	HTvector3 fPos;
	return fPos = Body->GetUITextureControlPos();
}


// 현재 윈도우의 영역에 위치 하였는가??
bool UIWindow::CheckRegionWithPoint(int iXPos, int iYPos)
{
	if (Body->CheckRegionWithPoint(iXPos, iYPos))
		return true;
	return false;
}


//
// CHTUIMessageBox Class 맴버 함수를 모아놓았습니다.
//

CHTUIMessageBox::CHTUIMessageBox() {}
CHTUIMessageBox::~CHTUIMessageBox() {}

// nMode = 0 확인버튼만, 1 = 확인/취소 버튼, 2 = 미사용...
void CHTUIMessageBox::HT_vMessageBox(unsigned int nIndex, CHTString str, int nMode)
{
	CHTString strMessage;
	// 윈도우 생성
	// 현재 메시지 박스가 팝업된 상태라면 팝업된 메시지 박스를 닫아버린다.
	if (g_cUIManager->HT_isShowMessageBox() == true)
	{
		g_cUIManager->HT_FocusOffEditBoxControl(m_nWindowIndex, 1); 
		g_cUIManager->HT_EnableOnWindow(m_nWindowIndex);
		g_cUIManager->HT_DeleteWindow(m_nIndex);
	}

	// 메시지가 팝업 되었으므로 해당 윈도우에 Enable을 off 상태로 만들어 반응하지 않게 한다.
	m_nIndex = UI_WINDOW_MESSAGEBOX + nIndex;	// 메시지박스는 한 윈도우에 하나만 뜬다. (아이디 설정은 기존 윈도우 Index에 추가되어 결정된다.)
	m_nWindowIndex = nIndex;					// 윈도우 인덱스도 가지고 있습니다.
	m_nMode = nMode;

	g_cUIManager->HT_CreateWindow(m_nIndex, _T("Message"), 329, 125, g_cUIManager->UIMessageBoxMgr.HT_hrMessageBox_InputCheck, 2, HT_COLOR(0.0f, 0.0f, 0.0f, 0.8f));
	g_cUIManager->HT_WindowArrangement(m_nIndex, 5);	
	
	switch (nMode) // 모드에 따라 다양한 메시지박스를 만들어 봅니다.
	{
	case UI_MESSAGEBOX_CONFIRM:	// 전형적인 메시지박스입니다. 확인버튼만 있는...
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLongLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 218, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//확   인
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_SetButtonEnterOn(m_nIndex, 2);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	case UI_MESSAGEBOX_RECONFIRM: // 확인 버튼과 취소 버튼이 있는 재확인창 이라고 할 수 있겠습니다.
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLongLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 115, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 115, 92, 64, 19);//확   인
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 3, 159, 218, 92, 160, 161);
		g_cUIManager->HT_AddLabelControl(m_nIndex, 3, eMsgCommonCancel, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//취   소
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 3, 5);
		g_cUIManager->HT_SetButtonEnterOn(m_nIndex, 2);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 3);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	case UI_MESSAGEBOX_NUMBERINPUT:	// 언패킹 윈도우입니다. 숫자를 입력할 수 있는 반환값은 항상 숫자입니다. 취소를 눌렀을땐 0으로 처리하면 되겠습니다. 
		g_strResultText = "";
		g_cUIManager->HT_AddEditBoxControl(m_nIndex, 1, 11, 171, 58, 120, 19);
		g_cUIManager->HT_SetModeEditBoxControl(m_nIndex, 1, 2);
		g_cUIManager->HT_FocusOnEditBoxControl(m_nIndex, 1);
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLongLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 115, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 115, 92, 64, 19);//확   인
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 3, 159, 218, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 3, eMsgCommonCancel, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//취   소
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 3, 5);
		g_cUIManager->HT_SetButtonEnterOn(m_nIndex, 2);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 3);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	case UI_MESSAGEBOX_CONFIRM_ENTER_NO:	// 전형적인 메시지박스입니다. 확인버튼만 있는... 엔터기능이 안먹히는 놈입니다.
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 218, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//확   인
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	case UI_MESSAGEBOX_INPUT: // 일반적인 입력창입니다.
		g_strResultText = "";
		g_cUIManager->HT_AddEditBoxControl(m_nIndex, 1, 11, 171, 58, 120, 19);
		g_cUIManager->HT_FocusOnEditBoxControl(m_nIndex, 1);
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLongLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 115, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 115, 92, 64, 19);//확   인
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 3, 159, 218, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 3, eMsgCommonCancel, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//취   소
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 3, 5);
		g_cUIManager->HT_SetButtonEnterOn(m_nIndex, 2);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 3);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	case UI_MESSAGEBOX_COUPON:		// 쿠폰 입력창
		g_strResultText = "";
		g_cUIManager->HT_AddEditBoxControl(m_nIndex, 1, 11, 171, 58, 120, 19, 2);
		g_cUIManager->HT_FocusOnEditBoxControl(m_nIndex, 1);
		g_cUIManager->HT_AddLongLabelControl(m_nIndex, 1, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 19, 28, 291, 59);
		g_cUIManager->HT_SetArrangementLongLabelControl(m_nIndex, 1, 7);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 2, 159, 115, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 2, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 115, 92, 64, 19);//확   인
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 2, 5);
		g_cUIManager->HT_AddButtonControl(m_nIndex, 3, 159, 218, 92, 160, 161 );
		g_cUIManager->HT_AddLabelControl(m_nIndex, 3, eMsgCommonCancel, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.8f), HT_COLOR(1.0f, 1.0f, 1.0f, 0.5f), 218, 92, 64, 19);//취   소
		g_cUIManager->HT_SetArrangementLabelControl(m_nIndex, 3, 5);
		g_cUIManager->HT_SetButtonEnterOn(m_nIndex, 2);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 3);
		g_cUIManager->HT_SetButtonToolTipOff(m_nIndex, 2);
		break;
	}
	g_cUIManager->HT_EnableOffWindow(nIndex);
	g_cUIManager->HT_ShowWindow(m_nIndex);
}

// 윈도우 제어 시도시 호출 (이곳에서 입력장치로부터 들어온 정보를 처리한다.)
void CHTUIMessageBox::HT_hrMessageBox_InputCheck(int iAction, int iTarget, int iTargetID)
{

	switch(iTargetID)
	{
	case -2:// 백그라운드 다운시
		break;
	case -1:// 종료버튼이나 취소 버튼 클릭시 메시지 박스 제거와 함께 기존 윈도우 락 풀기
	case 2:	// 확인
	case 3:	// 취소
		if (g_cUIManager->UIMessageBoxMgr.m_nMode == 2)
		{
			// 우선 텍스트 내용을 UI메니저에 저장
			g_cUIManager->m_strMessageBoxText = g_cUIManager->HT_GetTextEditBoxControl(g_cUIManager->UIMessageBoxMgr.m_nIndex , 1);

			if (iTargetID == 2)
			{
				CHTString str = g_cUIManager->HT_GetTextEditBoxControl(g_cUIManager->UIMessageBoxMgr.m_nIndex , 1);
				g_cUIManager->UIMessageBoxMgr.HT_vCloseMessageBox(atoi(str.HT_szGetString()));
			}
			else
			{
				g_cUIManager->UIMessageBoxMgr.HT_vCloseMessageBox(0);
				return;
			}
		}
		else if (g_cUIManager->UIMessageBoxMgr.m_nMode == 5 || g_cUIManager->UIMessageBoxMgr.m_nMode == 3)// 일반 메시지 입력모드
		{
			if (iTargetID == -1 || iTargetID == 3)
			{
				g_cUIManager->UIMessageBoxMgr.HT_vCloseMessageBox(iTargetID);
				return;
			}

			// 우선 텍스트 내용을 UI메니저에 저장
			g_cUIManager->m_strMessageBoxText = g_cUIManager->HT_GetTextEditBoxControl(g_cUIManager->UIMessageBoxMgr.m_nIndex , 1);
			g_cUIManager->UIMessageBoxMgr.HT_vCloseMessageBox(0);
		}
		else
		{
			g_cUIManager->UIMessageBoxMgr.HT_vCloseMessageBox(iTargetID);
			return;
		}
		break;
	}
}

void CHTUIMessageBox::HT_vCloseMessageBox(int iTargetID)
{
	g_cUIManager->HT_FocusOffEditBoxControl(m_nIndex, 1); 
	g_cUIManager->HT_EnableOnWindow(m_nWindowIndex);
	g_cUIManager->HT_CallMessageBoxFunction(m_nWindowIndex, iTargetID);	// UI 메니저를 도움으로 외부함수를 호출하게 합니다.
}



//
// CHTUIStatus Class 맴버 함수를 모아놓았습니다.
//

CHTUIStatus::CHTUIStatus() 
{
	m_sStatus_CharParms = HT_NULL;
	m_sStatus_CharParms = new S_SCP_CHAR_PARAMS_CHANGE;
}

CHTUIStatus::~CHTUIStatus() 
{ 
	HT_DELETE( m_sStatus_CharParms ); 
}


void CHTUIStatus::DrawStatusLabel(int x, int y, int id, CHTString str)
{
	int tid = 11;
	if (x == -1)	// 타이틀 출력으로 인식하여 처리
	{
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, 8, 3, y+6, 1400, 36, 6);
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, 9, 40, y, 1400, 152, 19);
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, 8, 192, y+6, 1400, 136, 6);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_STATUS, id, str, 0, HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, y, 152, 19);
		return;
	}

	if (id == 0 ) 
	{
		tid = 10;
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, tid, x, y); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_STATUS, id, str, 0, HT_COLOR(0.8f, 0.8f, 0.8f, 0.9f), HT_COLOR(0.8f, 0.8f, 0.8f, 0.9f), x, y, 79, 19);
	}
	else
	{
		if (strcmp(str, "  ") == 0 ) 
		{
			//g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, 9, x, y);
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_STATUS, id, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.8f, 0.8f, 0.8f, 0.9f), x, y, 79, 19);
		}
		else if (strcmp(str, "   ") == 0 ) 
		{
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_STATUS, id, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.8f, 0.8f, 0.8f, 0.9f), x, y, 152, 19);
		}
		else
		{
			g_cUIManager->HT_AddTextureControl(UI_WINDOW_STATUS, 0, tid, x, y); 
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_STATUS, id, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(0.8f, 0.8f, 0.8f, 0.9f), x, y, 79, 19);
		}
	}

}

// 상태창을 생성합니다.
void CHTUIStatus::HT_vStatus_Init()
{
	CHTString strMessage;

	// 윈도우 생성
	g_cUIManager->HT_CreateWindow(UI_WINDOW_STATUS, _T("Status"), 331, 465, g_cUIStatus->HT_hrStatus_InputCheck, 2);
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_STATUS, 5);

	g_cUIManager->HT_CreateWindow(_DIALOG_BACKGROUND, _T("Message"), 10, 10, g_cUIStatus->HT_hrStatus_InputCheck2, 2);

	//g_cUIManager->HT_SetScriptMessage( eMsgShopExplain04, &strMessage, _T(""), _T("") );	//	프리미엄 서비스의 추가 신청시 적용기간이 늘어납니다.
		
	// 기본 정보
	void (*ptr)(int, int, int, CHTString) = DrawStatusLabel;
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoTitle, &strMessage, _T(""), _T("") );	//	캐릭터 정보
	ptr(-1, 30, 1, strMessage);
	g_cUIManager->HT_SetScriptMessage( eMsgAshramLevel, &strMessage, _T(""), _T("") );	//	레     벨
	ptr(5,  55, 0, strMessage); ptr(85,  55, 2, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoTrimuriti, &strMessage, _T(""), _T("") );	//	주     신
	ptr(166, 55, 0, strMessage); ptr(246, 55, 3, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoTribe, &strMessage, _T(""), _T("") );	//	종     족
	ptr(5,  76, 0, strMessage); ptr(85,  76, 4, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoPointTriburiti, &strMessage, _T(""), _T("") );	//	주신포인트
	ptr(166, 76, 0, strMessage); ptr(246, 76, 5, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoOccupation, &strMessage, _T(""), _T("") );	//	직     업
	ptr(5,  97, 0, strMessage); ptr(85,  97, 6, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoKarma, &strMessage, _T(""), _T("") );	//	카 르 마
	ptr(166, 97, 0, strMessage); ptr(246, 97, 28, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoCast, &strMessage, _T(""), _T("") );	//	카 스 트
	ptr(5, 118, 0, strMessage); ptr(85, 118, 7, _T("   "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoExplainAshram, &strMessage, _T(""), _T("") );	//	아쉬람명
	ptr(5, 139, 0, strMessage); ptr(85, 139, 8, _T("   ")); 
	
	// 능력상태
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoAblitityStatus, &strMessage, _T(""), _T("") );	//	캐릭터 능력상태
	ptr(-1, 166, 1, strMessage); 
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoLifrPower, &strMessage, _T(""), _T("") );	//	생 명 력
	ptr(5, 191, 0, strMessage); ptr(85, 191, 9, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoPhysicsAP, &strMessage, _T(""), _T("") );	//	물리공격력
	ptr(166, 191, 0, strMessage); ptr(246, 191, 10, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoTapas, &strMessage, _T(""), _T("") );	//	타 파 스
	ptr(5, 212, 0, strMessage); ptr(85, 212, 11, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoAttackRate, &strMessage, _T(""), _T("") );	//	공격성공률
	ptr(166, 212, 0, strMessage); ptr(246, 212, 12, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoDefencePower, &strMessage, _T(""), _T("") );	//	방 어 력
	ptr(5, 233, 0, strMessage); ptr(85, 233, 13, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoEvasionRate, &strMessage, _T(""), _T("") );	//	회 피 율
	ptr(166, 233, 0, strMessage); ptr(246, 233, 14, _T("  "));
	
	// 차크라
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoChakra, &strMessage, _T(""), _T("") );	//	차크라
	ptr(-1, 260, 1, strMessage); 
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoMuscle, &strMessage, _T(""), _T("") );	//	근     육
	ptr(5, 285, 0, strMessage); ptr(85, 285, 15, _T("  ")); ptr(166, 285, 16, _T(" "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoNerve, &strMessage, _T(""), _T("") );	//	신     경
	ptr(5, 306, 0, strMessage); ptr(85, 306, 17, _T("  ")); ptr(166, 306, 18, _T(" "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoRemaindChakra, &strMessage, _T(""), _T("") );	//	잔여차크라
	ptr(246, 306, 0, strMessage);
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoHeart, &strMessage, _T(""), _T("") );	//	심     장
	ptr(5, 327, 0, strMessage); ptr(85, 327, 19, _T("  ")); ptr(166, 327, 20, _T(" ")); ptr(246, 327, 21, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoSoul, &strMessage, _T(""), _T("") );	//	정     신
	ptr(5, 348, 0, strMessage); ptr(85, 348, 22, _T("  ")); ptr(166, 348, 23, _T(" "));

	g_cUIManager->HT_AddButtonControl(UI_WINDOW_STATUS, 1, 13, 230, 288, 14, 15);	// 근육 버튼
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_STATUS, 2, 13, 230, 309, 14, 15);	// 신경 버튼
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_STATUS, 3, 13, 230, 330, 14, 15);	// 심장 버튼
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_STATUS, 4, 13, 230, 351, 14, 15);	// 정신 버튼
	
	// 저항력
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoResistancePower, &strMessage, _T(""), _T("") );	//	저항력
	ptr(-1, 375, 1, strMessage);
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoFire, &strMessage, _T(""), _T("") );	//	화     염
	ptr(5,  400, 0, strMessage); ptr(85,  400, 24, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoCold, &strMessage, _T(""), _T("") );	//	냉     기
	ptr(166, 400, 0, strMessage); ptr(246, 400, 25, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoElectric, &strMessage, _T(""), _T("") );	//	전     격
	ptr(5,  421, 0, strMessage); ptr(85,  421, 26, _T("  "));
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoPoison, &strMessage, _T(""), _T("") );	//	독
	ptr(166, 421, 0, strMessage); ptr(246, 421, 27, _T("  "));
}


// 윈도우 정보 갱신시 호출 (이곳에서 UI Widnow의 컨트롤 정보들 셋팅 및 배치를 한다.)
void CHTUIStatus::HT_vStatus_SetInfo()
{
	CHTString str;
	
	///* 이름*/ g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 1, g_oMainCharacterInfo.szCharName ); 
	/* 레벨*/ str.HT_szFormat( "%d", m_sStatus_CharInfo.byLevel ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 2, str);
	/* 주신*/ str = HT_szStatus_GetTrimuriti(g_oMainCharacterInfo.byTrimuriti); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 3, str);
	/* 종족*/ str = HT_szStatus_GetTribe(g_oMainCharacterInfo.snTribe);	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 4, str);
	/* 주신 포인트*/str.HT_szFormat( "%d", g_oMainCharacterInfo.nBrahmanPoint ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 5, str);
	/* 직업*/	str = HT_szStatus_GetJobName(g_oMainCharacterInfo.byClass1, g_oMainCharacterInfo.byClass2);	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 6, str);
	/* 카스트*/	str = HT_szStatus_GetCastClass(g_byteMainCharacterCaste);g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 7, str);
	/* 아쉬람*/	str = g_cGuildSystem->HT_strGuild_GetGuildName(); if( str.HT_bIsEmpty() ) HT_g_Script_SetMessage( eMsgCommonNone, &str); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 8, str);
	/* 체력*/	str.HT_szFormat( "%d / %d", g_cMainCharacter->HT_nMainChar_GetResentHP(), g_cMainCharacter->HT_nMainChar_GetMAXHP() ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 9, str);
	/* 물리공격력*/str.HT_szFormat( "%d - %d", m_sStatus_CharInfo.kDamage.iMin, m_sStatus_CharInfo.kDamage.iMax ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 10, str);
	/* 기력*/	str.HT_szFormat( "%d / %d", g_pMainBar->HT_iMainBar_GetCurTP(), g_pMainBar->HT_iMainBar_GetMaxTP() ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 11, str);
	/* 공격 성공율*/str.HT_szFormat( "%d", m_sStatus_CharInfo.snAttackRate ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 12, str);
	/* 방어력*/str.HT_szFormat( "%d", m_sStatus_CharInfo.snAC ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 13, str);
	/* 회피율*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.snDodgeRate ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 14, str);
	/* 근육*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snMuscle ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 15, str);
	/* plus - 근육*/str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snMuscle-m_sStatus_CharInfo.krgChakra[0].snMuscle ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 16, str);
	/* 신경*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snNerves ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 17, str);
	/* plus - 신경*/str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snNerves-m_sStatus_CharInfo.krgChakra[0].snNerves ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 18, str);
	/* 심장*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snHeart ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 19, str);
	/* plus - 심장*/str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snHeart-m_sStatus_CharInfo.krgChakra[0].snHeart ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 20, str);
	/* 차크라 총 포인트*/str.HT_szFormat( "%d", m_sStatus_CharInfo.snCPRemaining ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 21, str);
	/* 정신*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snMind ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 22, str);
	/* plus - 정신*/str.HT_szFormat( "%d", m_sStatus_CharInfo.krgChakra[1].snMind-m_sStatus_CharInfo.krgChakra[0].snMind );	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 23, str);
	/* 불 */	str.HT_szFormat( "%d", m_sStatus_CharInfo.kResist.snFire ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 24, str);
	/* 얼음*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.kResist.snCold );	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 25, str);
	/* 번개*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.kResist.snLightning  ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 26, str);
	/* 독*/	str.HT_szFormat( "%d", m_sStatus_CharInfo.kResist.snPoison ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 27, str);
	/* 카르마*/	str.HT_szFormat( "%d", g_oMainCharacterInfo.snKarma ); g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_STATUS, 28, str);
}

// 외부에서 띄움 (각 윈도우의 클래스가 UI메니저에 들어간다면 의미없음)
void CHTUIStatus::HT_vStatus_WindowPopup()
{
	g_cUIManager->HT_ShowWindow(UI_WINDOW_STATUS);
}

// 윈도우 제어 시도시 호출 (이곳에서 입력장치로부터 들어온 정보를 처리한다.)
void CHTUIStatus::HT_hrStatus_InputCheck(int iAction, int iTarget, int iTargetID)
{
	switch(iTargetID)
	{
	case -2:// 백그라운드 다운시
		break;
	case -1:// 종료버튼
		g_cUIManager->HT_HideWindow(UI_WINDOW_STATUS);	break;
	case 1:	// 근육버튼
	case 2:	// 신경버튼
	case 3:	// 심장버튼
	case 4:	// 정신버튼
		g_cUIStatus->HT_hrStatus_IncreaseChakra(iTargetID);
		break;
	}
}

// 메시지 박스 처리함수
void CHTUIStatus::HT_hrStatus_InputCheck2(int iAction, int iTarget, int iTargetID)
{
	switch(iTarget)
	{
	case UI_TARGET_MESSAGEBOX:
		switch(g_cUIStatus->m_MessageBoxType)
		{
		case 0:	// 확인창 메시지들 처리
			break;
		case 1:	// // 아이템 사용제한 조건에 의해 사용할 수 없습니다.
			break;
		case 2://  차크라 초기화 아이템일 경우 재확인 메세지 띄우기
			if (iTargetID == 2) 
			{
				g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( g_cItemControl->m_dwUseItemKeyID, 0X01 );
				g_cUIStatus->HT_vStatus_SetInfo();	// UI 갱신
			}
			break;
		case 3:// // 스킬 초기화 아이템일 경우 재확인 메세지 띄우기
			if (iTargetID == 2)
			{
				g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( g_cItemControl->m_dwUseItemKeyID, 0X01 );
				g_cUISkillWindow->HT_vSkillWindow_SetInfo();	// UI 갱신
			}
			break;
		case 4:// 차투랑가 입장권을 사용하시겠습니까? [확인/취소]
			// 차투랑가 입장 여부 재확인창 처리
			if (iTargetID == 2)
			{
                if (g_wResentZoneServerID == 11)
					return;

				g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use( g_cItemControl->m_dwUseItemKeyID, 0X01 );
				g_cPortal->HT_vPortal_Chaturanga_Enter();	// 차투랑가 입장
			} 
			break;
		case 5:// 퀘스트 초기화 아이템 사용시 재확인창 띄움 
			//g_cUIQuestWindow->HT_vQuestWindow_SetInfo();
		case 6://(꾸러미 아이템 포함) 한국버전
		case 7://(꾸러미 아이템 포함)  // 해외버전
			if (iTargetID == 2)
			{
				g_cItemControl->HT_vNetWork_CSP_RESP_Item_Use(g_cItemControl->m_dwSelectedUseItemKeyID,/* sLocRoom.nCellPosx,*/ 0x01 );
			}
			break;
		case 8: // 결투 재확인 창
			if (iTargetID == 2)
				g_pDuelSystem->HT_vDuel_LButtonCheckForReConfirm(13, 1);
			else
				g_pDuelSystem->HT_vDuel_LButtonCheckForReConfirm(13, 0);
			break;
		case 9:
			if (iTargetID == 2)
			{
				g_cNPCControl->HT_vNetWork_CSP_Req_CharacterInitialize(2,6);
				// 여기에 퀘스트 초기화 NPC 확인창의 승낙 패킷을 서버로 보낸다.
			}
			break;
		}
		break;
	}
}

// 차크라 증가버튼 다운시 호출되는 함수
void CHTUIStatus::HT_hrStatus_IncreaseChakra(int iBtnNo)
{
	int iResult = 0;

	// 캐릭터가 살아 있는 경우에 한해서 버튼 클릭 가능함
	if(!g_cMainCharacter->HT_vMainChar_GetCharLive())
		return;

	// 필요한 정보 추출
	int iHeart = m_sStatus_CharInfo.krgChakra[0].snHeart;
	int iNerve = m_sStatus_CharInfo.krgChakra[1].snNerves;
	int iTribe = g_oMainCharacterInfo.snTribe;
		
	// 순수 심장 400 제한
	if (iBtnNo == 3 && iHeart >= 400) iResult = 1;

	// 데바나 가루다에 한해서 신경 350 제한
	if ((iTribe == 4 || iTribe == 8) && iBtnNo == 2 && iNerve >= 350) iResult = 1;

	// 남은 차크라가 있어야 함
	if (m_sStatus_CharInfo.snCPRemaining <= 0) iResult = 2;

	// 결과 처리
	switch(iResult)
	{
		case 0:	// 문제 없음
			g_pEngineHandler->HT_hrStartSFX( &iResult, HT_FX_CHAKRAUPGRADE, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
			HT_vNetWork_CSP_REQ_Increase_Chakra(iBtnNo); // 서버에 요청 (응답은 없음)
			break;
		case 1: // 차크라 제한에 걸림
			g_cUIManager->ChattingNotify(eMsgChakraCannotUpgrade); //	"차크라 제한에 걸려 차크라를 올릴 수 없습니다."
			break;
		default:
			break;
	}
}

HTint CHTUIStatus::HT_nGetTotalPureChakra()
{
	HTint nTotalChakra = m_sStatus_CharInfo.krgChakra[0].snMuscle + 
		m_sStatus_CharInfo.krgChakra[0].snHeart +
		m_sStatus_CharInfo.krgChakra[0].snNerves +
		m_sStatus_CharInfo.krgChakra[0].snMind ;

	return nTotalChakra;
}

HTint CHTUIStatus::HT_nGetTotalChakra()
{
	HTint nTotalChakra = m_sStatus_CharInfo.krgChakra[1].snMuscle + 
		m_sStatus_CharInfo.krgChakra[1].snHeart +
		m_sStatus_CharInfo.krgChakra[1].snNerves +
		m_sStatus_CharInfo.krgChakra[1].snMind ;

	return nTotalChakra;
}


// 차크라 확장 요청
void CHTUIStatus::HT_vNetWork_CSP_REQ_Increase_Chakra(int iBtnNo)
{
	PS_CSP_REQ_INCREASE_CHAKRA info = HT_NULL;
	info = new S_CSP_REQ_INCREASE_CHAKRA;
	
	info->byChakra = iBtnNo;
	g_pNetWorkMgr->RequestIncreaseChakra( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("V3_Send_Req_IncreaseChakra: No = %d", info->byChakra );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// 스테이터스 갱신시 받음
void CHTUIStatus::HT_vStatus_ChangeParams( PS_SCP_RESP_UPDATE_UI info )	
{
	m_sStatus_CharInfo.iTitle					= info->iTitle;					// Title
	m_sStatus_CharInfo.snCPRemaining			= info->snCPRemaining;			// 남은 차크라 포인트
	m_sStatus_CharInfo.byLevel					= info->byLevel;				// 현 Level
	m_sStatus_CharInfo.krgChakra[0].snMuscle	= info->krgChakra[0].snMuscle;	// 근육
	m_sStatus_CharInfo.krgChakra[0].snNerves	= info->krgChakra[0].snNerves;	// 신경
	m_sStatus_CharInfo.krgChakra[0].snHeart		= info->krgChakra[0].snHeart;	// 심장
	m_sStatus_CharInfo.krgChakra[0].snMind		= info->krgChakra[0].snMind;	// 정신
	m_sStatus_CharInfo.krgChakra[1].snMuscle	= info->krgChakra[1].snMuscle;	// 총 근육
	m_sStatus_CharInfo.krgChakra[1].snNerves	= info->krgChakra[1].snNerves;	// 총 신경
	m_sStatus_CharInfo.krgChakra[1].snHeart		= info->krgChakra[1].snHeart;	// 총 심장
	m_sStatus_CharInfo.krgChakra[1].snMind		= info->krgChakra[1].snMind;	// 총 정신
	m_sStatus_CharInfo.snAC						= info->snAC;					// AC
	m_sStatus_CharInfo.snAttackRate				= info->snAttackRate;			// Attack Rate
	m_sStatus_CharInfo.snDodgeRate				= info->snDodgeRate;			// Dodge Rate
	m_sStatus_CharInfo.kResist.snCold			= info->kResist.snCold;			// 콜드 저항
	m_sStatus_CharInfo.kResist.snFire			= info->kResist.snFire;			// 불 저항
	m_sStatus_CharInfo.kResist.snLightning		= info->kResist.snLightning;	// 전격 저항
	m_sStatus_CharInfo.kResist.snPoison			= info->kResist.snPoison;		// 독 저항
	m_sStatus_CharInfo.kDamage.iMin				= info->kDamage.iMin;			// 최소 데미지
	m_sStatus_CharInfo.kDamage.iMax				= info->kDamage.iMax;			// 최대 데미지
	m_sStatus_CharInfo.kDamage.iFire			= info->kDamage.iFire;			// 불 데미지
	m_sStatus_CharInfo.kDamage.iCold			= info->kDamage.iCold;			// 콜드 데미지
	m_sStatus_CharInfo.kDamage.iLightning		= info->kDamage.iLightning;	// 전격 데미지
	m_sStatus_CharInfo.kDamage.iPoison			= info->kDamage.iPoison;		// 독 데미지
	g_oMainCharacterInfo.nBrahmanPoint			= info->iBramanPoint;			// 주신 포인트

	HT_vStatus_SetInfo();	// 윈도우 갱신
}


// 직업 스트링 얻기
CHTString CHTUIStatus::HT_szStatus_GetJobName(int iClass1, int iClass2)
{
	CHTString str;

	switch ( iClass1 )
	{
	case CLASS_LEVEL0: HT_g_Script_SetMessage( eMsgCommonJobBasic, &str, _T("") ); break;// 기본
	case CLASS_LEVEL1:	// 1차 전직
		switch( iClass2 )
		{
			case CLASS_SATVAN	: HT_g_Script_SetMessage( eMsgCommonJobSatvan, &str, _T("") ); break;// 사트반
			case CLASS_DHVANTA	: HT_g_Script_SetMessage( eMsgCommonJobDhvanta, &str, _T("") ); break;// 드반타
			case CLASS_NIRVANA	: HT_g_Script_SetMessage( eMsgCommonJobNirvana, &str, _T("") ); break;//너바나
			case CLASS_MANTRIKA	: HT_g_Script_SetMessage( eMsgCommonJobMantrika, &str, _T("") ); break;//만트리카
			default				: HT_g_Script_SetMessage( eMsgCommonNone, &str, _T("") ); break;// 없음
		}	break;
	case CLASS_LEVEL2:	// 2차 전직
		switch( iClass2 )
		{
			case CLASS_SATVAN1	: HT_g_Script_SetMessage( eMsgCommonJobSatvan1, &str, _T("") ); break;// 사트야
			case CLASS_SATVAN2	: HT_g_Script_SetMessage( eMsgCommonJobSatvan2, &str, _T("") ); break;// 바나르
			case CLASS_DHVANTA1	: HT_g_Script_SetMessage( eMsgCommonJobDhvanta1, &str, _T("") ); break;// 드루타
			case CLASS_DHVANTA2	: HT_g_Script_SetMessage( eMsgCommonJobDhvanta2, &str, _T("") ); break;// 카르야
			case CLASS_NIRVANA1	: HT_g_Script_SetMessage( eMsgCommonJobNirvana1, &str, _T("") ); break;// 나카유다
			case CLASS_NIRVANA2	: HT_g_Script_SetMessage( eMsgCommonJobNirvana2, &str, _T("") ); break;// 바이드야
			case CLASS_MANTRIKA1: HT_g_Script_SetMessage( eMsgCommonJobMantrika1, &str, _T("") ); break;// 아비카라
			case CLASS_MANTRIKA2: HT_g_Script_SetMessage( eMsgCommonJobMantrika2, &str, _T("") ); break;// 사마바트
			default				: HT_g_Script_SetMessage( eMsgCommonNone, &str, _T("") ); break;// 없음
		}	break;
	default:
		HT_g_Script_SetMessage( eMsgCommonNone, &str, _T("") ); break;//없음
		break;
	}
	return str;
}


// 카스트 스트링 얻기
CHTString CHTUIStatus::HT_szStatus_GetCastClass(int iCaste)
{ 
	CHTString str2;	HTint iLevel = (iCaste + 1) % 3;
	switch (iLevel)
	{
	case 0:	str2 = _T("1"); break;
	case 1:	str2 = _T("3"); break;
	case 2:	str2 = _T("2"); break;
	}
	
	CHTString str;

	if (eTNCaste_Sudra3 <= iCaste && eTNCaste_Sudra1 >= iCaste)	
		HT_g_Script_SetMessage( eMsgCommonCastSudra, &str, str2);//수드라
	else if (eTNCaste_Baisha3 <= iCaste && eTNCaste_Baisha1 >= iCaste) 
		HT_g_Script_SetMessage( eMsgCommonCastVaisha, &str, str2 );//바이샤
	else if (eTNCaste_Cushatri3 <= iCaste && eTNCaste_Cushatri1 >= iCaste) 
		HT_g_Script_SetMessage( eMsgCommonCastKshatrya, &str, str2 );//카스트리아
	else if (eTNCaste_Braman3 <= iCaste && eTNCaste_Braman1 >= iCaste) 
		HT_g_Script_SetMessage( eMsgCommonCastBraman, &str, str2 );//브라만
	else if (eTNCaste_Avatara3 <= iCaste && eTNCaste_Avatara1 >= iCaste) 
		HT_g_Script_SetMessage( eMsgCommonCastAvatara, &str, str2);//아바타라
	else if (eTNCaste_MahaRaja3 <= iCaste && eTNCaste_MahaRaja1 >= iCaste)	
		HT_g_Script_SetMessage( eMsgCommonCastReserve, &str, str2 );//마하라자
	else	
		HT_g_Script_SetMessage( eMsgCommonNone, &str, _T("") );

	return str;
}


// 주신 스트링 얻기
CHTString CHTUIStatus::HT_szStatus_GetTrimuriti(int iTrimuriti)
{
	CHTString strTrimuriti;

	switch(iTrimuriti)
	{
	case TRIMURITI_BRAHMA: HT_g_Script_SetMessage( eMsgCommonTrimuritiBrahma, &strTrimuriti, _T("") ); break; // 브라흐마
	case TRIMURITI_VISHNU: HT_g_Script_SetMessage( eMsgCommonTrimuritiVishunu, &strTrimuriti, _T("") ); break; // 비슈느
	case TRIMURITI_SIVA: HT_g_Script_SetMessage( eMsgCommonTrimuritiSiva, &strTrimuriti, _T("") ); break; // 시바
	default: HT_g_Script_SetMessage( eMsgCommonNone, &strTrimuriti, _T("") ); break;	// 없음
	}

	return strTrimuriti;
}

// 종족 스트링 얻기
CHTString CHTUIStatus::HT_szStatus_GetTribe(int iTribe)
{
	CHTString str;

	switch( iTribe )
	{
		case HT_ID_CHARACTER_NAGA		: HT_g_Script_SetMessage( eMsgCommonTribeNaga, &str, _T("") ); break;
		case HT_ID_CHARACTER_ASURA		: HT_g_Script_SetMessage( eMsgCommonTribeAsura, &str, _T("") ); break;
		case HT_ID_CHARACTER_YAKSA		: HT_g_Script_SetMessage( eMsgCommonTribeYaksha, &str, _T("") ); break;
		case HT_ID_CHARACTER_DEVA		: HT_g_Script_SetMessage( eMsgCommonTribeDeva, &str, _T("") ); break;
		case HT_ID_CHARACTER_KIMNARA	: HT_g_Script_SetMessage( eMsgCommonTribeKimnara, &str, _T("") ); break;
		case HT_ID_CHARACTER_RAKSHASA	: HT_g_Script_SetMessage( eMsgCommonTribeRakshasa, &str, _T("") ); break;
		case HT_ID_CHARACTER_GANDHARVA	: HT_g_Script_SetMessage( eMsgCommonTribeGandharva, &str, _T("") ); break;
		case HT_ID_CHARACTER_GARUDA		: HT_g_Script_SetMessage( eMsgCommonTribeGaruda, &str, _T("") ); break;
		default							: HT_g_Script_SetMessage( eMsgCommonNone, &str, _T("") ); break;
	}
	return str;
}



//
// CHTUINPCWindow Class 맴버 함수를 모아놓았습니다.
//

CHTUINPCWindow::CHTUINPCWindow() {}
CHTUINPCWindow::~CHTUINPCWindow() {}

// 상태창을 생성합니다.
void CHTUINPCWindow::HT_vNPCWindow_Init()
{
	// 윈도우 생성
	g_cUIManager->HT_CreateWindow(UI_WINDOW_NPCWINDOW, _T("NPC Chatting"), 330, 466, g_cUINPCWindow->HT_hrNPCWindow_InputCheck, 2);

	int y = 31;	CHTString str = "";
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_NPCWINDOW, 0, 8, 3, y+6, 1400, 36, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_NPCWINDOW, 0, 9, 40, y, 1400, 152, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_NPCWINDOW, 0, 8, 192, y+6, 1400, 135, 6);
	
	// NPC명
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_NPCWINDOW, 1, str, 0, HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, y, 152, 19);
	
	// 설명문
	g_cUIManager->HT_AddLongLabelControl(UI_WINDOW_NPCWINDOW, 2, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 65, 311, 130);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_NPCWINDOW, 0, 11, 8, 52, 1400, 311, 147);
	g_cUIManager->HT_SetArrangementLongLabelControl(UI_WINDOW_NPCWINDOW, 2, 7);
	
	// 선택문
	m_StartPosY = 200;
	HT_vNPCWindow_SetInfo();

	g_cUIManager->HT_WindowArrangement(UI_WINDOW_NPCWINDOW, 4);
	g_cUIManager->HT_MoveWindow(UI_WINDOW_NPCWINDOW, 50, 0, 1);

}


// 윈도우 정보 갱신시 호출 (이곳에서 UI Widnow의 컨트롤 정보들 셋팅 및 배치를 한다.)
void CHTUINPCWindow::HT_vNPCWindow_SetInfo()
{
	for (int i = 1; i <= 10; ++i)
	{
		g_cUIManager->HT_DelLabelControl(UI_WINDOW_NPCWINDOW, i+2);
		g_cUIManager->HT_DelButtonControl(UI_WINDOW_NPCWINDOW, i);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_NPCWINDOW, i+2, "", 0, HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 8, m_StartPosY+(20*(i-1)), 315, 19);
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_NPCWINDOW, i, 0 , 8, m_StartPosY+(20*(i-1)), 9, 9, 1500, 315, 19);
		g_cUIManager->HT_SetButtonToolTipOff(UI_WINDOW_NPCWINDOW, i);
	}

	for (int i = 3; i < 13; ++i)
	{
		g_cUIManager->HT_SetButtonEnable(_DIALOG_NPCWINDOW, i-3, true);
	}
}

// 외부에서 띄움 (각 윈도우의 클래스가 UI메니저에 들어간다면 의미없음)
void CHTUINPCWindow::HT_vNPCWindow_WindowPopup()
{
}

// 윈도우 제어 시도시 호출 (이곳에서 입력장치로부터 들어온 정보를 처리한다.)
void CHTUINPCWindow::HT_hrNPCWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	g_cUINPCWindow->m_iButton = iTargetID;
	//g_cUINPCWindow->HT_vNPCWindow_SetInfo();

	HTPoint pPt; pPt.x = 0; pPt.y = 0;
	g_cNPCControl->HT_vNPCControl_ButtonCheck_Dialog(pPt);	// 외부함수 빌림 임시로..

	switch (iTarget)
	{
	case UI_TARGET_BUTTON:
		switch(iTargetID)
		{
		case -2:// 백그라운드 다운시
			break;
		case -1:// 종료버튼
			g_cNPCControl->HT_vNPCControl_DialogWin_AntiActive();
			//g_cUIManager->HT_HideWindow(UI_WINDOW_NPCWINDOW);	
			break;
		}
		break;
	case UI_TARGET_MESSAGEBOX:
		switch(g_cUINPCWindow->m_MessageBoxNo)
		{
		case -1:	// 확인창들
			break;
		case -3:	// 주신 변경 조건 부족
			g_cNPCControl->HT_vNPCControl_GetNextStep(g_cNPCControl->m_nSelectCount+1);
			break;
		case -2:	// 주신변경 실패 확인
			g_cNPCControl->HT_vNPCControl_GetNextStep(g_cNPCControl->m_nSelectCount+1);
			break;
		case 0:	// 여사제 저장 재확인
			if (iTargetID == 2) // 확인 버튼 클릭시 위치 저장.. 그외에는 창닫음
				g_pNetWorkMgr->ReqSavePosition(g_cNPCControl->m_iNPCIndex);
			break;
		case 1: // 주신변경 재확인
			if (iTargetID == 2) // 확인 버튼 클릭시 다음실행. 그외에는 창닫음
			{
				g_cNPCControl->m_bTrimutiri = 1;
				g_cNPCControl->HT_vNetWork_CSP_Req_Select_Trimuriti(g_cNPCControl->m_bTrimutiri);
			}
			else
			{
				g_cNPCControl->HT_vNPCControl_GetNextStep(g_cNPCControl->m_nSelectCount+1); // 대화상자 대화 바꾸기
			}
			g_cUINPCWindow->m_MessageBoxNo = 0;
				// 주신변경모드가 지나갔음을 구분하기 위해
			break;
		case 2: // 쿠폰 번호 입력창
			{
				if (iTargetID == -1 || iTargetID == 3)
					return;

				CHTString strtemp = g_cUIManager->m_strMessageBoxText;
				char str[16];
				strncpy(str, strtemp.HT_szGetString(), 16);
				g_pEventWindow->HT_vEventWnd_ReqMsgGameEvent( 1, 2, str);
			}
			break;
		}
		break;
	}
}




//
// CHTUISkillWindow Class 맴버 함수를 모아놓았습니다.
//

CHTUISkillWindow::CHTUISkillWindow() {}
CHTUISkillWindow::~CHTUISkillWindow() {}

// 상태창을 생성합니다.
void CHTUISkillWindow::HT_vSkillWindow_Init()
{
	// 윈도우 생성
	g_cUIManager->HT_CreateWindow(UI_WINDOW_SKILL, _T("Skill"), 330, 466, g_cUISkillWindow->HT_hrSkillWindow_InputCheck, 2);
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_SKILL, 5);

	int y = 31;	
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 8, 3, y+6, 1400, 36, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 8, 129, y+6, 1400, 198, 6);

	// 다음 세가지 정보로 모든 스킬정보를 만들어 낸다.
	int m_Tribe = g_oMainCharacterInfo.snTribe;
	int m_Class1 = g_oMainCharacterInfo.byClass1;
	int m_Class2 = g_oMainCharacterInfo.byClass2;

	m_SkillTabNo = 0;	// 처음 시작텝은 0

	// 종족별 타이틀 스트링과 텝 이름 셋팅	
	HT_vSkillSetTitle(m_Tribe);

	// 처음시작 텝 생성
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 101, 65, 40, y, 65, 65, 1550, 88, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 102, 63, 129, y+6, 65, 65, 1550, 65, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 103, 63, 194, y+6, 65, 65, 1550, 65, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 104, 63, 259, y+6, 65, 65, 1550, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, y, 88, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129, y+6, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, y+6, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, y+6, 65, 19);

	// 종족이름 생성
	CHTString str;
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 11, 10, 60, 1400, 79, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoTribe, &str, _T(""), _T("") );	//	종     족
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 0, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 10, 60, 79, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 9, 129, 60, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 4002, m_strTribe, 0, HT_COLOR(1.0f, 0.8f, 0.4f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129, 60, 152, 19);

	//스크롤바
	//g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_SKILL, 1, 313, 78, 320, 24-7);

	// V3 UI에도 정보 삽입
	for (int i=0; i<6; i++)
	{
		for (int j=0; j<4; j++)
		{
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex1[i][j] = 0;
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex2[i][j] = 0;
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex3[i][j] = 0;
			g_cUISkillWindow->m_oSkillIndex.m_iSkillIndex4[i][j] = 0;
			
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo1[i][j] = 0;
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo2[i][j] = 0;
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo3[i][j] = 0;
			g_cUISkillWindow->m_oSkillIcon.m_iSkillIconNo4[i][j] = 0;

			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow1[i][j] = 0;
			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow2[i][j] = 0;
			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow3[i][j] = 0;
			g_cUISkillWindow->m_oSkillArrow.m_iSkillArrow4[i][j] = 0;
		}
	}
/*
	// 기본 정보창 생성
	for (int i = 1; i < 8; ++i)
	{
		if (HT_vGetSkillInfo(i-1) == false) HT_vSetSkillInfoblank();
		g_cUISkillWindow->HT_vSkillDrawSkill(i, (m_byLevel+m_byPlusLevel), m_strSkillName, m_strSkillContents, m_strSkillType);
	}

	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 6; ++y)
		{
			if (HT_vGetSkillInfo(x+(y*4)) == false) HT_vSetSkillInfoblank();
			g_cUISkillWindow->HT_vSkillDrawSkill(x+(y*4), (m_byLevel+m_byPlusLevel), m_strSkillName, m_strSkillContents, m_strSkillType);
		}
*/
	// 잔여 포인트 출력
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 11, 10, 440, 1400, 90, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoSkillPoint, &str, _T(""), _T("") );	//	스킬포인트
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 0, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 10, 440, 90, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 169, 102, 440, 1400, 25, 19);
	str.HT_szFormat("%d", m_ExtraSkillPoint); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 4000, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 102, 440, 25, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 11, 160, 440, 1400, 90, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgCharInfoGodPoint, &str, _T(""), _T("") );	//	주신 스킬
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 0, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 160, 440, 90, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 169, 252, 440, 1400, 25, 19);
	str.HT_szFormat("%d", m_ExtraTrimutiritiSkillPoint); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 4001, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 252, 440, 25, 19);
}

// 해당 위치의 스킬정보를 얻어 옵니다.
bool CHTUISkillWindow::HT_vGetSkillInfo(int iIndex)
{
	// 현재 스킬이 존재하는가를 먼저 조사
	int iSlidePos = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_SKILL, 1);
	int iRealValue = iSlidePos + iIndex;
	int iXpos = iRealValue % 4;
	int iYpos = iRealValue / 4;
	DWORD dwSkillUseType = 0;

	switch (m_SkillTabNo)
	{
	case 0: if (m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] <= 0) return false;
		dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillDesc(m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos], &m_strSkillContents);
		m_byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] );
		//m_byPlusLevel = g_cSkillSystem->HT_bySkillSystem_GetSkillPlusLevel( m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillName( m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos], &m_strSkillName );
		m_iSkillIcon = m_oSkillIcon.m_iSkillIconNo1[iYpos][iXpos];
		m_iSkillArrow = m_oSkillArrow.m_iSkillArrow1[iYpos][iXpos];
		break;
	case 1: if (m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] <= 0) return false;
		dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillDesc(m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos], &m_strSkillContents);
		m_byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] );
		//m_byPlusLevel = g_cSkillSystem->HT_bySkillSystem_GetSkillPlusLevel( m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillName( m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos], &m_strSkillName );
		m_iSkillIcon = m_oSkillIcon.m_iSkillIconNo2[iYpos][iXpos];
		m_iSkillArrow = m_oSkillArrow.m_iSkillArrow2[iYpos][iXpos];
		break;
	case 2: if (m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] <= 0) return false;
		dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillDesc(m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos], &m_strSkillContents);
		m_byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] );
		//m_byPlusLevel = g_cSkillSystem->HT_bySkillSystem_GetSkillPlusLevel( m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillName( m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos], &m_strSkillName );
		m_iSkillIcon = m_oSkillIcon.m_iSkillIconNo3[iYpos][iXpos];
		m_iSkillArrow = m_oSkillArrow.m_iSkillArrow3[iYpos][iXpos];
		break;
	case 3: 
		if (m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] <= 0 ) return false;
		dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillDesc(m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos], &m_strSkillContents);
		m_byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] );
		//m_byPlusLevel = g_cSkillSystem->HT_bySkillSystem_GetSkillPlusLevel( m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] );
		g_pEngineHandler->HT_hrGetPCSkillName( m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos], &m_strSkillName );
		m_iSkillIcon = m_oSkillIcon.m_iSkillIconNo4[iYpos][iXpos];
		m_iSkillArrow = m_oSkillArrow.m_iSkillArrow4[iYpos][iXpos];
		break;
	default: 
		return false;
	}
	/*
	m_strSkillContents = "...";	// 길이 제한때문에 자름

	// 패시브인지 아닌지 알아오기
	if( dwSkillUseType == HT_PCSKILLTYPE_PASSIVE )
		m_strSkillType = "Passive";
	else
		m_strSkillType = "Active";
		*/

	return true;
}

// 스킬인덱스를 인자로 스킬 레벨을 얻어옵니다.
int CHTUISkillWindow::HT_vGetSkillLevel(DWORD iIndex)
{
	int m_byLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( iIndex );
	//int m_byPlusLevel = g_cSkillSystem->HT_bySkillSystem_GetSkillPlusLevel( iIndex );

	return (m_byLevel);//+m_byPlusLevel);
}

DWORD CHTUISkillWindow::HT_vGetSkillIndex(int iSlotNo)
{
	// 현재 스킬이 존재하는가를 먼저 조사
	int iSlidePos = 0;//g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_SKILL, 1);
	int iRealValue = iSlidePos + iSlotNo;// - 1;
	int iXpos = iRealValue % 4;
	int iYpos = iRealValue / 4;
	DWORD dwSkillUseType = 0;

	switch (m_SkillTabNo)
	{
	case 0: if (m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] <= 0) return 0;
		return m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos];
	case 1: if (m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] <= 0) return 0;
		return m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos];
	case 2: if (m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] <= 0) return 0;
		return m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos];
	case 3: if (m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] <= 0) return 0;
		return m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos];
	}
	return 0;
}

int CHTUISkillWindow::HT_vGetSkillIcon(DWORD iIndex)
{
	// 현재 스킬이 존재하는가를 먼저 조사
	for (int iYpos = 0; iYpos < 6; ++iYpos)
		for (int iXpos = 0; iXpos < 4; ++iXpos)
		{
			if (m_oSkillIndex.m_iSkillIndex1[iYpos][iXpos] == iIndex) return m_oSkillIcon.m_iSkillIconNo1[iYpos][iXpos];
			if (m_oSkillIndex.m_iSkillIndex2[iYpos][iXpos] == iIndex) return m_oSkillIcon.m_iSkillIconNo2[iYpos][iXpos];
			if (m_oSkillIndex.m_iSkillIndex3[iYpos][iXpos] == iIndex) return m_oSkillIcon.m_iSkillIconNo3[iYpos][iXpos];
			if (m_oSkillIndex.m_iSkillIndex4[iYpos][iXpos] == iIndex) return m_oSkillIcon.m_iSkillIconNo4[iYpos][iXpos];
		}
	
	return 0;
}

// 스킬정보 0으로 셋팅
bool CHTUISkillWindow::HT_vSetSkillInfoblank()
{
	m_byLevel = 0;
	m_byPlusLevel = 0;
	m_strSkillName = "";
	m_iSkillIcon = 0;
	m_iSkillArrow = 0;
	m_strSkillContents = "";
	m_strSkillType = "";

	return true;
}

// 종족에 따른 스킬명 및 기타 스트링 셋팅
void CHTUISkillWindow::HT_vSkillSetTitle(int iTribe)
{
	CHTString str;

	switch(iTribe)
	{
		case HT_ID_CHARACTER_NAGA :
		case HT_ID_CHARACTER_KIMNARA :
				HT_g_Script_SetMessage( eMsgCommonSkillAttack, &m_strTitle[0], _T("") );	// 공격
				HT_g_Script_SetMessage( eMsgCommonSkillDefence, &m_strTitle[1], _T("") );	// 보조
				HT_g_Script_SetMessage( eMsgCommonSkillAssistance, &m_strTitle[2], _T("") );	// 방어

				HT_g_Script_SetMessage( eMsgCommonTribeNaga, &m_strTribe, _T("") );
				HT_g_Script_SetMessage( eMsgCommonTribeKimnara, &str, _T("") );
				m_strTribe += _T("/") + str;
				break;
		case HT_ID_CHARACTER_ASURA :
		case HT_ID_CHARACTER_RAKSHASA :
				HT_g_Script_SetMessage( eMsgCommonSkillAssassination, &m_strTitle[0], _T("") );	// 공격
				HT_g_Script_SetMessage( eMsgCommonSkillArchery, &m_strTitle[1], _T("") );	// 보조
				HT_g_Script_SetMessage( eMsgCommonSkillAssistance, &m_strTitle[2], _T("") );	// 방어

				HT_g_Script_SetMessage( eMsgCommonTribeAsura, &m_strTribe, _T("") );
				HT_g_Script_SetMessage( eMsgCommonTribeRakshasa, &str, _T("") );
				m_strTribe += _T("/") + str;
				break;
		case HT_ID_CHARACTER_YAKSA :
		case HT_ID_CHARACTER_GANDHARVA :
				HT_g_Script_SetMessage( eMsgCommonSkillAttack, &m_strTitle[0], _T("") );	// 공격
				HT_g_Script_SetMessage( eMsgCommonSkillDefence, &m_strTitle[1], _T("") );	// 보조
				HT_g_Script_SetMessage( eMsgCommonSkillAssistance, &m_strTitle[2], _T("") );	// 방어

				HT_g_Script_SetMessage( eMsgCommonTribeYaksha, &m_strTribe, _T("") );
				HT_g_Script_SetMessage( eMsgCommonTribeGandharva, &str, _T("") );
				m_strTribe += _T("/") + str;
				break;
		case HT_ID_CHARACTER_DEVA :
		case HT_ID_CHARACTER_GARUDA :
				HT_g_Script_SetMessage( eMsgCommonSkillPhysics, &m_strTitle[0], _T("") );
				HT_g_Script_SetMessage( eMsgCommonSkillBlaze, &str, _T("")  );				
				m_strTitle[0] = m_strTitle[0] + _T("/") + str;// 물리/화염
				HT_g_Script_SetMessage( eMsgCommonSkillCold, &m_strTitle[1], _T("") );
				HT_g_Script_SetMessage( eMsgCommonSkillLightning, &str, _T("")  );
				m_strTitle[1] = m_strTitle[1] + _T("/") + str;// 냉기/전격
				HT_g_Script_SetMessage( eMsgCommonSkillMagic, &m_strTitle[2], _T("") );	// 마법
				HT_g_Script_SetMessage( eMsgCommonTribeDeva, &m_strTribe, _T("")  );
				HT_g_Script_SetMessage( eMsgCommonTribeGaruda, &str, _T("")  );
				m_strTribe += _T("/") + str;				// 데바/가루다
				break;
	}
	HT_g_Script_SetMessage( eMsgCommonSkillGod, &m_strTitle[3], _T("") );	// 주신
}

// 스킬윈도우의 텝 역활을 해주는 함수
void CHTUISkillWindow::HT_vSkillDrawTitle(int iIndex)
{

	CHTString str;
	
	// 기존 컨트롤 삭제
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, 101); g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, 102); g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, 103); g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, 104);
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, 101); g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, 102); g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, 103); g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, 104);

	for (int i = 0; i < 24; ++i)
	{
		g_cUIManager->HT_DelSlotBoxControl(UI_WINDOW_SKILL, i);
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, i+1000);
		g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, i+1000);
		g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, i+1000);
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, i+2000);	// 스킬 화살표
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, i+3000);	// 스킬 화살표
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, i+4000);	// 스킬 화살표
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, i+5000);	// 스킬 화살표
	}

	// 재설정
	switch (iIndex)
	{
	case 0:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 101, 65, 40, 31, 65, 64, 1550, 88, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 102, 63, 129, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 103, 63, 194, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 104, 63, 259, 37, 65, 64, 1550, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 31, 88, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19);
		break;
	case 1:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 101, 63, 40, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 102, 65, 129-23, 31, 65, 64, 1550, 88, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 103, 63, 194, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 104, 63, 259, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 31, 88, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19); 
		break;
	case 2:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 101, 63, 40, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 102, 63, 129-23, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 103, 65, 194-23, 31, 65, 64, 1550, 88, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 104, 63, 259, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194-23, 31, 88, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19); 
		break;
	case 3:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 101, 63, 40, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 102, 63, 129-23, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 103, 63, 194-23, 37, 65, 64, 1550, 65, 19); g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, 104, 65, 259-23, 31, 65, 64, 1550, 88, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194-23, 37, 65, 19); g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259-23, 31, 88, 19);
		break;
	}

}

// 스킬윈도우의 스킬 출력을 하는 함수
void CHTUISkillWindow::HT_vSkillDrawSkill(int iIndex, int iLevel, CHTString strName, CHTString strContemts, CHTString strType)
{
//	int y = 80 + ((iIndex-1) * 46); // 출력 Y 위치 결정
//	int x = 0;
	int x = iIndex % 4;
	int y = iIndex / 4;

	y = (y * 60) + 88;
	x = (x * 79) + 10;

	// 현재 스킬 레벨과 스킬의 최대레벨을 조사하여 더이상 올릴 수 없다면 버튼을 출력하지 않는다.
	DWORD dwIndex = HT_vGetSkillIndex(iIndex);
	if (dwIndex == 0) return;

	BYTE byCurLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( dwIndex ); // 현재 스킬 레벨
	BYTE byMaxLevel = 0;
	HTint iOut;
	HTbyte byteOut;
	BYTE byCharLevel = g_cStatus->HT_byGetLevel();

	CHTString str;
	str.HT_szFormat("%d",byCurLevel);

	// 현 스킬을 출력하기 위해 기존 출력된 정보들은 지워줍니다.
	g_cUIManager->HT_DelSlotBoxControl(UI_WINDOW_SKILL, iIndex);
	g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, iIndex+1000);
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_SKILL, iIndex+1000);
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_SKILL, iIndex+1000);
	g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, iIndex+2000);	// 스킬 화살표
	g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, iIndex+3000);	// 스킬 화살표
	g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, iIndex+4000);	// 스킬 화살표
	g_cUIManager->HT_DelTextureControl(UI_WINDOW_SKILL, iIndex+5000);	// 스킬 화살표

	// 스킬 출력을 위해 새롭게 생성합니다.
	//g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_SKILL, iIndex, 0, 5+x, y); //아이콘(5,80)
	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_SKILL, iIndex, 66, 5+x, y); //아이콘(5,80)
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+1000, 169, 41+x, y, 1400, 25, 17);//레벨표시(41,80)
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, iIndex+1000, str, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 41+x, y, 25, 17);

	if( byCurLevel == 0 )
		g_pParamMgr->HT_bGetPCSkillMaxLevel( dwIndex, byCurLevel+1, &byMaxLevel );
	else
		g_pParamMgr->HT_bGetPCSkillMaxLevel( dwIndex, byCurLevel, &byMaxLevel );

	if (byCurLevel < byMaxLevel)
        g_cUIManager->HT_AddButtonControl(UI_WINDOW_SKILL, iIndex+1000, 14, 41+x, y+22, 14, 15);//레벨상승버튼(41,106)

	// 해당 스킬에 한해 화살표를 그립니다.
	if (m_iSkillArrow == 23830)
	{
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+2000, 182, 41+x-20, y+35, 1400);//화살표 표시(41,80)
	}
	else if (m_iSkillArrow == 23831)
	{
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+2000, 182, 41+x-20, y+35, 1400);//화살표 표시(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+3000, 183, 41+x+5-20, y+35+11, 1400);//화살표 표시(41,80)
	}
	else if (m_iSkillArrow == 23832)
	{
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+2000, 182, 41+x-20, y+35, 1400);//화살표 표시(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+3000, 183, 41+x+5-20, y+35+11, 1400);//화살표 표시(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+4000, 183, 41+x+5+79-20, y+35+11, 1400);//화살표 표시(41,80)
	}
	else if (m_iSkillArrow == 23592)
	{
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+2000, 182, 41+x-20, y+35, 1400);//화살표 표시(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+3000, 183, 41+x+5-20, y+35+11, 1400);//화살표 표시(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+4000, 183, 41+x+5+79-20, y+35+11, 1400);//화살표 표시(41,80)
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, iIndex+5000, 183, 41+x+5+79+79-20, y+35+11, 1400);//화살표 표시(41,80)
	}

	// 슬롯박스에 아이콘을 붙입니다.
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_SKILL, iIndex, 2, 2); //아이콘(5,80)
	g_cUIManager->HT_SetSlotImage(UI_WINDOW_SKILL, iIndex, m_iSkillIcon); //아이콘(5,80)

	// 패시브 스킬이거나 스킬레벨이 0인 스킬 아이콘은 드레그가 되지 않습니다.
	DWORD dwSkillUseType = g_pEngineHandler->HT_dwGetSkillActionActivePassive( dwIndex );
	if( dwSkillUseType == HT_PCSKILLTYPE_PASSIVE || byCurLevel == 0)
		g_cUIManager->HT_SetSlotBoxImageFixed(UI_WINDOW_SKILL, iIndex, true);

	// 다른 조건에 의해 레벨을 더이상 올릴 수 없다면 붉은색 처리 합니다.
	if( byCurLevel == 0 && g_pParamMgr->HT_bLockID( dwIndex, byCurLevel+1 ) == true )
	{
		// 요구레벨이 안되면 붉은색 처리
		if( g_pParamMgr->HT_bGetPCSkillReqLevel( &byteOut ) == true && byteOut > 0 )
		{
			if( g_cStatus->HT_byGetLevel() < byteOut ) 
			{
				g_cUIManager->HT_SetSlotBoxControlEnable(UI_WINDOW_SKILL, iIndex, false);
				g_cUIManager->HT_SetSlotBoxImageFixed(UI_WINDOW_SKILL, iIndex, true);
			}

		}// 습득조건 스킬을 익히지 않은 상태라면 붉은색 처리
		if( g_pParamMgr->HT_bGetPCSkillReqSkill1( &iOut ) == true && iOut > 0)
		{
			g_pParamMgr->HT_bGetPCSkillReqSkill1_Lvl( &byteOut );
			HTbyte byReqCurLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( iOut );

			if( byReqCurLevel < byteOut ) 
			{
				g_cUIManager->HT_SetSlotBoxControlEnable(UI_WINDOW_SKILL, iIndex, false);
				g_cUIManager->HT_SetSlotBoxImageFixed(UI_WINDOW_SKILL, iIndex, true);
			}

		}
		if( g_pParamMgr->HT_bGetPCSkillReqSkill2( &iOut ) == true && iOut > 0 )
		{
			g_pParamMgr->HT_bGetPCSkillReqSkill2_Lvl( &byteOut );
			HTbyte byReqCurLevel = g_cSkillSystem->HT_bySkillSystem_GetSkill_Level( iOut );

			if( byReqCurLevel < byteOut ) 
			{
				g_cUIManager->HT_SetSlotBoxControlEnable(UI_WINDOW_SKILL, iIndex, false);
				g_cUIManager->HT_SetSlotBoxImageFixed(UI_WINDOW_SKILL, iIndex, true);
			}
		}
		g_pParamMgr->HT_bUnLockID( dwIndex, byCurLevel+1 );
	}

	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 9, 69, y, 1400, 175, 17);//스킬이름(69,80)
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, iIndex+1000, strName, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 69, y, 175, 17);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 9, 69, y+21, 1400, 175, 17);//스킬설명(69,101)
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, iIndex+2000, strContemts, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 69, y+21, 175, 17);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 10, 246, y, 1400, 68, 17);//스킬시전방식(246,80)    
	//g_cUIManager->HT_AddLabelControl(UI_WINDOW_SKILL, iIndex+3000, strType, 0, HT_COLOR(1.0f, 0.8f, 0.4f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 246, y, 68, 17);
}

// 스킬윈도우의 스킬 재갱신
void CHTUISkillWindow::HT_vSkillUpdate(int iIndex)
{/*
	CHTString str;
	
	str.HT_szFormat("%d",m_byLevel+m_byPlusLevel);
	g_cUIManager->HT_SetSlotImage(UI_WINDOW_SKILL, iIndex, m_iSkillIcon); //아이콘(5,80)
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, iIndex, str);	// 스킬레벨
	//g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, iIndex+1000, m_strSkillName);	// 스킬이름
	//g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, iIndex+2000, m_strSkillContents);	// 스킬설명
	//g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, iIndex+3000, m_strSkillType);		// 스킬타입
*/	
}


// 윈도우 정보 갱신시 호출 (이곳에서 UI Widnow의 컨트롤 정보들 셋팅 및 배치를 한다.)
void CHTUISkillWindow::HT_vSkillWindow_SetInfo()
{/*
	// 현재 위치에 맞게 스킬정보 갱신하여 출력
	for (int i=1; i<8; ++i) 
	{
		if (HT_vGetSkillInfo(i-1) == false) HT_vSetSkillInfoblank();
		HT_vSkillUpdate(i);
	}
*/
	CHTString str;

//	HT_g_vLogFile("_Skill OutPut Start.\n");
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 6; ++y)
		{
			if (HT_vGetSkillInfo(x+(y*4)) == true) 
			{
				HT_vSkillDrawSkill(x+(y*4), (m_byLevel)/*+m_byPlusLevel)*/, m_strSkillName, m_strSkillContents, m_strSkillType);
			}
			else
			{
				HT_vSetSkillInfoblank();
			}

//			str.HT_szFormat("[%s:%d], ", m_strSkillName.HT_szGetString(), m_byLevel);
//			HT_g_vLogFile( str);
		}

//	HT_g_vLogFile("_Skill OutPut End.\n");

	// 잔여포인트 갱신
	//CHTString str;
	str.HT_szFormat("%d", m_ExtraSkillPoint); 
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, 4000, str);
	str.HT_szFormat("%d", m_ExtraTrimutiritiSkillPoint);
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SKILL, 4001, str);
}

// 스킬 포인트를 얻어옵니다.
HTint CHTUISkillWindow::HT_nGetSkillPoint()
{
	return m_ExtraSkillPoint;
}

// 주신 스킬 포인트를 얻어옵니다.
HTint CHTUISkillWindow::HT_nGetGodSkillPoint()
{
	return m_ExtraTrimutiritiSkillPoint;
}

// 외부에서 띄움 (각 윈도우의 클래스가 UI메니저에 들어간다면 의미없음)
void CHTUISkillWindow::HT_vSkillWindow_WindowPopup()
{
	HT_vSkillWindow_SetInfo();
}

// 윈도우 제어 시도시 호출 (이곳에서 입력장치로부터 들어온 정보를 처리한다.)
void CHTUISkillWindow::HT_hrSkillWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	switch(iAction)
	{
		case UI_ACTION_MOUSE_L_UP:
			switch(iTarget)
			{
			case UI_TARGET_BUTTON:	// 버튼의 경우 처리
				switch(iTargetID)
				{
				case -2:// 백그라운드 다운시
					break;
				case -1:// 종료버튼
					g_cUIManager->HT_HideWindow(UI_WINDOW_SKILL);
					break;
				case 101: case 102: case 103: case 104:				// 텝버튼 클릭시 반응
					g_cUISkillWindow->m_SkillTabNo = iTargetID-101;
					g_cUISkillWindow->HT_vSkillDrawTitle(g_cUISkillWindow->m_SkillTabNo);
					g_cUISkillWindow->HT_vSkillWindow_SetInfo();
					break;
				}

				if (iTargetID >= 1000 && iTargetID < 1024)	// 버튼 클릭시 버튼 처리
					g_cSkillInventory->HT_vNetWork_CSP_Skill_LearnSkill( iTargetID - 1000 );
				break;
//			case UI_TARGET_SCROLLBAR:	// 스크롤바의 경우 처리
//				g_cUISkillWindow->HT_vSkillWindow_SetInfo();
//				break;

			case UI_TARGET_SLOTBOX:
				g_cUIManager->HT_RefuseSlotImageMoving();
				break;
			}
		break;
	}
}



//
// CHTUIRefineWindow Class 맴버 함수를 모아놓았습니다.
//

CHTUIRefineWindow::CHTUIRefineWindow() {}
CHTUIRefineWindow::~CHTUIRefineWindow() {}

// 상태창을 생성합니다.
void CHTUIRefineWindow::HT_vRefineWindow_Init()
{
	// 윈도우 생성
	g_cUIManager->HT_CreateWindow(UI_WINDOW_REFINE, _T("Refine"), 330, 238, g_cUIRefineWindow->HT_hrRefineWindow_InputCheck, 2);
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_REFINE, 5);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 8, 3, 37, 1400, 36, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 39, 31, 1400, 89, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRefiningTitle, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 39, 31, 89, 19);//제      련
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 8, 129, 37, 1400, 198, 6);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 146, 56, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRefiningTargetItem, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 146, 56, 152, 19);//제련 대상 아이템

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 146, 122, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRefiningItem, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 146, 122, 152, 19);//제련 재료

	// 바르탄 텍스처 애니메이션 74- 79
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 74 ,17, 59);
	g_cUIManager->HT_AddTimerControl(UI_WINDOW_REFINE, 1, 100);
	g_cUIManager->HT_EnableOnTimerControl(UI_WINDOW_REFINE, 1);

	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE,1, 31 ,17, 59);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 0, 9, 16, 164, 1400, 130, 18);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonRupia, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 164, 58, 19);//루피아

	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 1, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 71, 164, 59, 19);
	g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_REFINE, 1, 5);

	// 제련 슬롯 추가 62
	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,1, 66 ,205, 81);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 1, 2, 2);

	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,2, 66 ,168, 149);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 2, 2, 2);
	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,3, 66 ,205, 149);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 3, 2, 2);
	g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_REFINE,4, 66 ,242, 149);
	g_cUIManager->HT_SetSlotBoxControlPosImage(UI_WINDOW_REFINE, 4, 2, 2);

	// 버튼 99, 97, 98
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_REFINE, 1,  159, 56, 201, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 56, 201, 64, 19);//확     인
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_REFINE, 2,  159, 156, 201, 160, 161);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_REFINE, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 156, 201, 64, 19);//취     소

	m_iRefineAniNo = 0;
	m_SetItemNumber = 0;
	g_cUIRefineWindow->m_iWindowIndex[0] = 0;
	g_cUIRefineWindow->m_iWindowIndex[1] = 0;
	g_cUIRefineWindow->m_iWindowIndex[2] = 0;
	g_cUIRefineWindow->m_iWindowIndex[3] = 0;
	g_cUIRefineWindow->m_iWindowIndex[4] = 0;
}

// 윈도우 정보 갱신시 호출 (이곳에서 UI Widnow의 컨트롤 정보들 셋팅 및 배치를 한다.)
void CHTUIRefineWindow::HT_vRefineWindow_SetInfo()
{

}

// 외부에서 띄움 (각 윈도우의 클래스가 UI메니저에 들어간다면 의미없음)
void CHTUIRefineWindow::HT_vRefineWindow_WindowPopup()
{
}

// 외부에서 띄움 (각 윈도우의 클래스가 UI메니저에 들어간다면 의미없음)
void CHTUIRefineWindow::HT_vRefineWindow_WindowHide()
{
	for (int i = 1; i < 4; ++i)
	{
		g_cUIManager->HT_SetSlotBoxControlEnable(m_iWindowIndex[i], m_iControlIndex[i], true);
	}

	m_SetItemNumber = 0;
	g_cUIRefineWindow->m_iWindowIndex[0] = 0;
	g_cUIRefineWindow->m_iWindowIndex[1] = 0;
	g_cUIRefineWindow->m_iWindowIndex[2] = 0;
	g_cUIRefineWindow->m_iWindowIndex[3] = 0;

	g_cUIManager->HT_HideWindow( UI_WINDOW_REFINE );
}

// 윈도우 제어 시도시 호출 (이곳에서 입력장치로부터 들어온 정보를 처리한다.)
void CHTUIRefineWindow::HT_hrRefineWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:	// 버튼의 경우 처리
		switch(iTargetID)
		{
		case -2:// 백그라운드 다운시
			break;
		case -1:// 종료버튼
		case 2:	// 취소버튼
			// 제련창 위에 있던 아이템 이미지들 지우기
			g_cNPCControl->HT_vNPCControl_ButtonCheck_Work_Delete();
			g_cNPCControl->m_iResent = 0;
			g_cUIRefineWindow->HT_vRefineWindow_WindowHide();
			break;
		case 1:	// 확인버튼
			g_cNPCControl->HT_vNPCControl_ButtonCheck_Work_Ok();
			//g_cUIManager->HT_HideWindow(UI_WINDOW_REFINE);
			break;
    	}
		break;
	case UI_TARGET_TIMER:	// 타이머
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_REFINE, 99); 

		switch(g_cUIRefineWindow->m_iRefineAniNo)
		{
			case 0: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 74 ,17, 59); break;
			case 1: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 75 ,17, 59); break;
			case 2: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 76 ,17, 59); break;
			case 3: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 77 ,17, 59); break;
			case 4: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 78 ,17, 59); break;
			case 5: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 79 ,17, 59); break;
			case 6: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 78 ,17, 59); break;
			case 7: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 77 ,17, 59); break;
			case 8: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 77 ,17, 59); break;
			case 9: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 76 ,17, 59); break;
			case 10: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 75 ,17, 59); break;
			case 11: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 74 ,17, 59); break;
            case 12: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 79 ,17, 59); break;
			case 13: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 78 ,17, 59); break;
            case 14: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 77 ,17, 59); break;
          //  case 15: g_cUIManager->HT_AddTextureControl(UI_WINDOW_REFINE, 99, 76 ,17, 59); break;
		}

		g_cUIRefineWindow->m_iRefineAniNo++;
		if (g_cUIRefineWindow->m_iRefineAniNo > 14) g_cUIRefineWindow->m_iRefineAniNo = 0;
		break;
	case UI_TARGET_MESSAGEBOX:	// 메시지 박스 처리
		switch(iTargetID)
		{
		case 2:	// 확인
			if (g_cUIRefineWindow->m_nMessageBoxNo == 1) // 재확인창이면...
				g_cNPCControl->HT_vNetWork_CSP_REQ_ITEM_REFINING();	// 제련실행
			break;
		default:
			break;
		}
		break;
	case UI_TARGET_SLOTBOX:
		if (iAction == UI_ACTION_MOUSE_L_UP)
		{
			unsigned int	nWindowIndex = 0, nControlIndex = 0;
			int iTextureID = 0;
			g_cUIManager->HT_GetSlotBoxControlSourInfo(nWindowIndex, nControlIndex, iTextureID);

			if (nWindowIndex == _DIALOG_EQUPINVENTORY || nWindowIndex == _DIALOG_INVENTORY2)	// 인벤토리에서 옮긴것만 처리함 나머지는 이동 거절
			{
				// 장비하고 있는 인벤토리 아이템을 옮긴다면 무조걸 이동 실패처리
				if (nControlIndex < _SLOTCURRECT_INVEN) 
				{
					g_cUIManager->HT_RefuseSlotImageMoving();
					return;
				}

				DWORD dwKeyID = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(nControlIndex);
				
				g_cUIRefineWindow->m_iWindowIndex[0] = nWindowIndex;
				g_cUIRefineWindow->m_iControlIndex[0] = nControlIndex;

				if (g_cNPCControl->HT_hrNPCControl_ItemWork_LButtonClick( dwKeyID ) == HT_FAIL)
				{
					g_cUIManager->HT_SetSlotBoxControlEnable(nWindowIndex, nControlIndex, true);
					g_cUIManager->HT_RefuseSlotImageMoving();
				}
			}
			else
			{
				g_cUIManager->HT_RefuseSlotImageMoving();
			}
			break;
		}
	}
}


//
// CHTUIMerchantWindow Class 맴버 함수를 모아놓았습니다.
//

CHTUIMerchantWindow::CHTUIMerchantWindow() {}
CHTUIMerchantWindow::~CHTUIMerchantWindow() 
{
}

// 상태창을 생성합니다.
void CHTUIMerchantWindow::HT_vMerchantWindow_Init()
{
	CHTString strMessage;
	// [일반 구입창]
	// 윈도우 생성
	g_cUIManager->HT_CreateWindow(UI_WINDOW_MERCHANT, _T("Merchant"), 248, 412, g_cUIMerchantWindow->HT_hrMerchantWindow_InputCheck, 2);
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_MERCHANT, 5);

	//	Slot Inven
	for(int i=0 ; i<6 ; i++ )
		for(int j=0 ; j<10 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( UI_WINDOW_MERCHANT, i+(j*6), 66, 12+(i*37), 25+(j*37) );
			g_cUIManager->HT_SetSlotBoxControlPosImage( UI_WINDOW_MERCHANT, i+(j*6), 2, 2);
		}

	// [프리미엄 구입창]
	// 윈도우 생성
	g_cUIManager->HT_CreateWindow(UI_WINDOW_MERCHANT_PREMIUM, _T("Merchant"), 539, 555, g_cUIMerchantWindow->HT_hrMerchantWindow_InputCheck, 2);
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_MERCHANT_PREMIUM, 5);
	
	// 처음 시작 라벨
	m_strTopic = "";
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, m_strTopic, 1, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 7, 65, 508, 35);
	g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, 7);

	// 처음시작 텝 생성
	int y = 31;

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 8, 3, y+6, 1400, 534, 6);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_SKILL, 0, 8, 129, y+6, 1400, 198, 6);


	g_cUIManager->HT_SetScriptMessage( eMsgShopBundle, &strMessage, _T(""), _T("") );	//	꾸러미
	m_strTitle[0] = strMessage;
	g_cUIManager->HT_SetScriptMessage( eMsgShopCharacter, &strMessage, _T(""), _T("") );	//	캐릭터
	m_strTitle[1] = strMessage;
	g_cUIManager->HT_SetScriptMessage( eMsgShopConvenience, &strMessage, _T(""), _T("") );	//	편의성
	m_strTitle[2] = strMessage;
	g_cUIManager->HT_SetScriptMessage( eMsgShopAbility, &strMessage, _T(""), _T("") );	//	기능성
	m_strTitle[3] = strMessage;
	g_cUIManager->HT_SetScriptMessage( eMsgShopspeciality, &strMessage, _T(""), _T("") );	//	특수용
	m_strTitle[4] = strMessage;
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 10, 40, y, 10, 10, 1550, 88, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 10, 129, y+6, 10, 10, 1550, 65, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 10, 194, y+6, 10, 10, 1550, 65, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 10, 259, y+6, 10, 10, 1550, 65, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 10, 324, y+6, 10, 10, 1550, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, y, 88, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129, y+6, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, y+6, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, y+6, 65, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324, y+6, 65, 19);

	// 새로줄
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 1, 9, 102, 1400, 3, 438);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 1, 259, 102, 1400, 3, 438);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 1, 513, 102, 1400, 3, 438);

	// 가로줄
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 102, 1400, 506, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 189, 1400, 506, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 276, 1400, 506, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 363, 1400, 506, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 450, 1400, 506, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 2, 9, 537, 1400, 506, 3);


	// 텝 꾸밈
	g_cUIMerchantWindow->HT_vMerchantWindow_DrawTab(0);
	m_iTabNo = 0;

	// 스크롤바
	g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_MERCHANT_PREMIUM , 1, 522, 44, 174, 5);
	m_iScrollValue = 0;

	//	Slot Inven 8, 101
	for(int i=0 ; i<5 ; i++ )
		for(int j=1 ; j<=2 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl(UI_WINDOW_MERCHANT_PREMIUM, 200+(i*2)+j, 66, 21+(244*(j-1)), 107+(87*i));
			g_cUIManager->HT_SetSlotBoxControlPosImage( UI_WINDOW_MERCHANT_PREMIUM, 200+(i*2)+j, 2, 2);
			g_cUIManager->HT_AddTextureControl(UI_WINDOW_MERCHANT_PREMIUM, 0, 9, 83+(244*(j-1)), 106+(87*i));
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 200+(i*2)+j, " ", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 83+(244*(j-1)), 106+(87*i), 152, 19);
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 300+(i*2)+j, " ", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 64+(244*(j-1)), 127+(87*i), 187, 56);
			g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 300+(i*2)+j, 7);
			g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 400+(i*2)+j, " ", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 142+(244*(j-1)), 169+(87*i), 132, 19);
			g_cUIManager->HT_SetArrangementLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 400+(i*2)+j, 7);
		}
}

// 스킬윈도우의 텝 역활을 해주는 함수
void CHTUIMerchantWindow::HT_vMerchantWindow_DrawTab(int iTabNo)
{
	CHTString str;
	
	// 기존 컨트롤 삭제
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101); 
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102); 
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103); 
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104); 
	g_cUIManager->HT_DelLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105);
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101); 
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102); 
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103); 
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104); 
	g_cUIManager->HT_DelButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105);

	// 재설정
	switch (iTabNo)
	{
	case 0:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 65, 40, 31, 65, 64, 1550, 88, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 63, 129, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 63, 194, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 63, 259, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 63, 324, 37, 65, 64, 1550, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 31, 88, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324, 37, 65, 19);

		HT_g_Script_SetMessage( eMsgExPlanPremiumItem07, &str, _T("") );	//	" 프리미엄 꾸러미 아이템들 입니다. 구입을 원하시는 아이템의 아이콘 또는 구매버튼을 클릭하시면, 구입이 가능합니다."		
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, str);
		break;
	case 1:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 63, 40, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 65, 129-23, 31, 65, 64, 1550, 88, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 63, 194, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 63, 259, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 63, 324, 37, 65, 64, 1550, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 31, 88, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324, 37, 65, 19);
		HT_g_Script_SetMessage( eMsgExPlanPremiumItem04, &str, _T("") );	//	" 캐릭터 향상을 위한 소모성 아이템들 입니다. 구입을 원하시는 아이템의 아이콘 또는 구매버튼을 클릭하시면, 구입이 가능합니다."
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, str);
		break;
	case 2:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 63, 40, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 63, 129-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 65, 194-23, 31, 65, 64, 1550, 88, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 63, 259, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 63, 324, 37, 65, 64, 1550, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194-23, 31, 88, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259, 37, 65, 19);  
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324, 37, 65, 19);
		HT_g_Script_SetMessage( eMsgExPlanPremiumItem05, &str, _T("") );	//	" 편의성 향상을 위한 소모성 아이템들 입니다. 구입을 원하시는 아이템의 아이콘 또는 구매버튼을 클릭하시면, 구입이 가능합니다."
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, str);
		break;
	case 3:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 63, 40, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 63, 129-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 63, 194-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 65, 259-23, 31, 65, 64, 1550, 88, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 63, 324, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259-23, 31, 88, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324, 37, 65, 19);
		HT_g_Script_SetMessage( eMsgExPlanPremiumItem06, &str, _T("") );	//	" 기능성 향상을 위한 소모성 아이템들 입니다. 구입을 원하시는 아이템의 아이콘 또는 구매버튼을 클릭하시면, 구입이 가능합니다."
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, str);
		break;
	case 4:
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 101, 63, 40, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 102, 63, 129-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 103, 63, 194-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 104, 63, 259-23, 37, 65, 64, 1550, 65, 19); 
		g_cUIManager->HT_AddButtonControl(UI_WINDOW_MERCHANT_PREMIUM, 105, 65, 324-23, 31, 65, 64, 1550, 88, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 101, m_strTitle[0], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 40, 37, 65, 19);
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 102, m_strTitle[1], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 129-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 103, m_strTitle[2], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 194-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 104, m_strTitle[3], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 259-23, 37, 65, 19); 
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 105, m_strTitle[4], 0, HT_COLOR(1.0f, 1.0f, 1.0f, 0.9f), HT_COLOR(1.0f, 0.6f, 0.2f, 0.9f), 324-23, 31, 88, 19);
		HT_g_Script_SetMessage( eMsgExPlanPremiumItem08, &str, _T("") );	//	" 특수 기능을 위한 소모성 아이템들 입니다. 구입을 원하시는 아이템의 아이콘 또는 구매버튼을 클릭하시면, 구입이 가능합니다."
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_MERCHANT_PREMIUM, 1, str);
		break;
	}
}

// 윈도우 정보 갱신시 호출 (이곳에서 UI Widnow의 컨트롤 정보들 셋팅 및 배치를 한다.)
void CHTUIMerchantWindow::HT_vMerchantWindow_SetInfo()
{
}

// 외부에서 띄움 (각 윈도우의 클래스가 UI메니저에 들어간다면 의미없음)
void CHTUIMerchantWindow::HT_vMerchantWindow_WindowPopup()
{
}

// 윈도우 제어 시도시 호출 (이곳에서 입력장치로부터 들어온 정보를 처리한다.)
void CHTUIMerchantWindow::HT_hrMerchantWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:	// 버튼의 경우 처리
		switch(iTargetID)
		{
		case -2:// 백그라운드 다운시
			break;
		case -1:// 종료버튼
			g_cUIManager->HT_HideWindow(UI_WINDOW_MERCHANT);
			g_cUIManager->HT_HideWindow(UI_WINDOW_MERCHANT_PREMIUM);
			break;
			// 텝버튼 클릭시 반응
		case 101: case 102: case 103: case 104: case 105:	// 프리미엄 윈도우에만 있음
			g_cUIMerchantWindow->m_iTabNo = iTargetID-101;
			g_cUIMerchantWindow->HT_vMerchantWindow_DrawTab(g_cUIMerchantWindow->m_iTabNo);
			g_cNPCControl->HT_vNPCControl_PrimiumItemListWin_Active(g_cUIMerchantWindow->m_iTabNo, g_cUIMerchantWindow->m_iScrollValue);
			break;
    	}
		break;
	case UI_TARGET_SLOTBOX:	// 슬롯박스 경우의 처리
		switch(iAction)
		{
		case UI_ACTION_MOUSE_RCLK:	// 해당 아이템을 R클릭 했을때 구매가동
			//g_cUIMerchantWindow->HT_vMerchantWindow_SetBuy(iTargetID);
			break;
		case UI_ACTION_MOUSE_L_UP: // 마우스를 끌어서 놓았을 경우
			{
				if (iTargetID == -1 || iTargetID == -2)
					g_cUIManager->HT_RefuseSlotImageMoving();
				
				unsigned int	nWindowIndex = 0, nControlIndex = 0;
				int iTextureID = 0;
				g_cUIManager->HT_GetSlotBoxControlSourInfo(nWindowIndex, nControlIndex, iTextureID);
				if (nWindowIndex != _DIALOG_EQUPINVENTORY || nWindowIndex != _DIALOG_INVENTORY2) // 인벤토리를 제외한 모든 인벤토리로 이동은 금지
					g_cUIManager->HT_RefuseSlotImageMoving();

				// 장착영역은 팔 수 없으므로 반환 _SLOTCURRECT_INVEN
				if (nControlIndex < _SLOTCURRECT_INVEN)
				{
					g_cUIManager->HT_RefuseSlotImageMoving();
					return;
				}

				if (nWindowIndex == _DIALOG_EQUPINVENTORY || nWindowIndex == _DIALOG_INVENTORY2)	// 인벤토리에서 가지고 왔을 경우 판매 모드로 변경
				{

					DWORD KeyID = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation(nControlIndex);
					g_cUIMerchantWindow->m_dwSellItem = g_cItemSystem->HT_dwSystem_GetItemIndex(KeyID);
					g_cUIMerchantWindow->m_MessageCode = 4; 

					CHTString str; 
					if (g_iInationalType != INATIONALTYPE_KOREA)
					{
						g_pMessageMgr->HT_bGetMessage( eMsgItemSellQuestionItem, &str );// 아이템을 판매 하시겠습니까?
						CHTString name; g_pParamMgr->HT_bGetItemName( g_cUIMerchantWindow->m_dwSellItem, &name );
						char str2[1024]; sprintf(str2, str, name.HT_szGetString()); strncpy(str, str2, 250);
					}
					else
					{
						// 한국 버전에서는 두개의 타입으로 나눠서 처리 (루피아, 캐쉬)
						
						int sellrupiah = 0;
						g_pParamMgr->HT_bGetItemSellRupiah(g_cUIMerchantWindow->m_dwSellItem, &sellrupiah);
						CHTString num; num.HT_szFormat("%d", g_cItemSystem->HT_iItemSystem_GetItemCount(KeyID));
						CHTString num2; num2.HT_szFormat("%d", sellrupiah * g_cItemSystem->HT_iItemSystem_GetItemCount(KeyID));

						// 일부 아이템은 판매 할 수 없다. (셀루피아가 -1 일때)
						if (sellrupiah == -1)
						{
							g_cUIMerchantWindow->m_MessageCode = 1;
							g_pMessageMgr->HT_bGetMessage( eMsgItemSellFail, &str );			// 아이템을 판매할 수 없습니다.
							g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
							return;
						}
						
						// 캐쉬인지 루피아인지에 따라 다른 메시지 출력
						if ( !CHTParamIDCheck::HT_bIsChargeNPC(g_cUIMerchantWindow->m_iNPCIndex))
						{
							// %s %s 개를 %s 루피아에 판매 하시겠습니까?
							g_pMessageMgr->HT_bGetMessage( eMsgItemSellMsg1, &str );
							CHTString name; g_pParamMgr->HT_bGetItemName( g_cUIMerchantWindow->m_dwSellItem, &name );
							char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString(), num2.HT_szGetString()); strncpy(str, str2, 250);
						}
						else
						{
							// %s %s 개를 %s 루피아에 판매 하시겠습니까?
							g_pMessageMgr->HT_bGetMessage( eMsgItemSellMsg2, &str );
							CHTString name; g_pParamMgr->HT_bGetItemName( g_cUIMerchantWindow->m_dwSellItem, &name );
							char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString(), num2.HT_szGetString()); strncpy(str, str2, 250);
						}
					}
					g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 1);
					return;
				}
			}
			break;
		case UI_ACTION_MOUSE_LCLK: // 마우스 왼쪽 버튼 클릭
			g_cUIMerchantWindow->HT_vMerchantWindow_SetBuy(iTargetID);
			break;
		}
		break;
	case UI_TARGET_MESSAGEBOX: // 메시지 박스 처리
		//if (g_cUIManager->HT_isShowMessageBox(UI_WINDOW_MERCHANT))
		//	g_cUIManager->HT_CloseMessageBox(UI_WINDOW_MERCHANT);

		switch (g_cUIMerchantWindow->m_MessageCode)
		{
			case 1: // 구입 오류 확인 메시지
				return;
			case 2: // 갯수 입력 받는 부분
				g_cUIMerchantWindow->HT_vMerchantWindow_ProcessBuy(iTargetID);
				return;
			case 3: // 아이템 구입시 재확인 창
				if (iTargetID == 2) // 확인시 서버로 구매요청
					g_cUIMerchantWindow->HT_vNetWork_CSP_Req_Item_Buy();
				return;
			case 4:	// 아이템 판매시 재확인 창
				if (iTargetID == 2)
				{
					g_cUIMerchantWindow->HT_vNetWork_CSP_Req_Item_Sell();
				}
				else
				{
					g_cUIManager->HT_RefuseSlotImageMoving();
				}
				return;
			case 5:	// 아이템 해체 재확인창
				if (iTargetID == 2)
				{}
				else
				{}
				return;
		}
		break;
	case UI_TARGET_SCROLLBAR:	// 스크롤바 처리
		{
			g_cUIMerchantWindow->m_iScrollValue = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_MERCHANT_PREMIUM, 1) * 2;
			g_cNPCControl->HT_vNPCControl_PrimiumItemListWin_Active(g_cUIMerchantWindow->m_iTabNo, g_cUIMerchantWindow->m_iScrollValue);
		}
		break;
	}
}

// 구매리스트를 생성합니다.
void CHTUIMerchantWindow::HT_vMerchantWindow_SetBuyList()
{
	// 다음 단계 설명으로 진행
	g_cNPCControl->HT_vNPCControl_GetNextStep(g_cNPCControl->m_nSelectCount);

	// 목록 지우기
	for(int i=0 ; i<6 ; i++ )
		for(int j=0 ; j<10 ; j++ )
		{
			m_ItemIndex[i+(j*6)] = 0;
			g_cUIManager->HT_SetSlotImage( UI_WINDOW_MERCHANT, i+(j*6), 0);
		}


	// 구매 리스트 생성
	if( g_pParamMgr->HT_bLockID( m_iNPCIndex ) == true )
	{
		int iCount = g_pParamMgr->HT_iGetNPCSellingItemCount( );
		int idItem = 0;
		for ( int i = 0; i < iCount; ++i )
		{
			if ( g_pParamMgr->HT_bGetNPCSellingItem( i, &idItem ) )
			{
				m_ItemIndex[i] = idItem;
				g_cUIManager->HT_SetSlotImage(UI_WINDOW_MERCHANT, i, g_pEngineHandler->HT_dwGetItemUIID(idItem));
			}
		}
		g_pParamMgr->HT_bUnLockID( m_iNPCIndex );
	}

	// 창 띄우기
	g_cUIManager->HT_ShowWindow( UI_WINDOW_MERCHANT );
}

// 구매 리스트에서 선택한 아이템에 대한 구매 처리 (입력갯수 창 띄우기 까지만 수행)
void CHTUIMerchantWindow::HT_vMerchantWindow_SetBuy(int SlotNo)
{
	if (SlotNo >= 200) SlotNo -= 200;	// 프리미엄 아이템의 경우 -200 해줌

	// Step 1) 구입할 아이템 가격 얻기
	if( g_pParamMgr->HT_bLockID( m_ItemIndex[SlotNo] ) == true )
	{
		m_dwBuyItem = m_ItemIndex[SlotNo];
		
		if (CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex))
		g_pParamMgr->HT_bGetItemCash( &m_ItemCash );	// 필요한 돈 ( 캐쉬)
		else
		g_pParamMgr->HT_bGetItemRupiah( &m_ItemCash );	// 필요한 돈 (루피아)
		//g_pParamMgr->HT_bGetItemMaxCount( &byMaxCount );	// 최대 중첩 개수

		if (m_iNPCIndex == 1302)	// 비류성 오다 상인의 경우 적용된 세율에 따라 가격이 변한다.
		{
			HTbyte byteTex = g_pSiege->HT_bySiege_GetMoneyRate();
			double dTex;

			if (byteTex == 0) { dTex = 0;}
			else { dTex = (double)m_ItemCash * (double)byteTex/100.0f; }
			m_ItemCash += int(dTex);
		}

		g_pParamMgr->HT_bUnLockID( m_ItemIndex[SlotNo] );
	}
	
	// Step 2) 자신이 가지고 있는 금액 얻기
	if ( CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex) )
		m_MyCash = g_cNPCControl->m_nCash;
	else
		m_MyCash = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();

	// 돈이 부족하다면 에러메시지 출력
	if (m_MyCash < m_ItemCash) 
	{
		if (m_ItemCash <= 0) return;
	
		m_MessageCode = 1; 

		CHTString str;
		if (CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex))
		{
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonCashErr, &str );
		}
		else
		{
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonMoneyErr, &str );
		}
		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}

	// Step 3) 구입 갯수 입력창 띄움
	m_MessageCode = 2; 
	CHTString str;// = "원하는 개수를 입력하세요."; 
	g_pMessageMgr->HT_bGetMessage( eMsgCommonInputYouWantItem, &str ) ;
	g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 2);

}

// 아이템 갯수 입력 후 부터 구매까지 처리 함수
void CHTUIMerchantWindow::HT_vMerchantWindow_ProcessBuy(int iCount)
{
	int m_nEconomy_Work_LimitRupiah = 0, m_iWorkItemMinCount = 0;

	m_dwBuyItemCount = iCount;
	if (m_dwBuyItemCount <= 0) 
	{
		if (m_dwBuyItemCount == 0) return;

		m_MessageCode = 1; 		// 아이템 개수가 부적합 합니다.
		CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgItemUnpackCountErr, &str ); 
		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}

	// 유료화 아이템의 경우 최소 구입개수 검사
	if( CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) // 유료화 아이템을 파는 NPC일 경우
	{
		m_iWorkItemMinCount = g_cNPCControl->HT_iNPCControl_GetMinCountForChargeItem( m_dwBuyItem );
		if( m_dwBuyItemCount < m_iWorkItemMinCount ) 
		{
			m_MessageCode = 1; 		// 최소 %d개를 구입해야 합니다.
			CHTString str; g_pMessageMgr->HT_bGetMessage( eMsgItemBuyMinCountErr, &str );
			//str.HT_szFormat(str, m_iWorkItemMinCount);
			CHTString num; num.HT_szFormat("%d", m_iWorkItemMinCount);
			char str2[1024]; sprintf(str2, str, num.HT_szGetString()); strncpy(str, str2, 250);

			g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
			return;
		}
	}
	// 소지한 금액과 필요한 금액 검사 
	if(CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) // 유료화 아이템을 파는 NPC일 경우
	{
		m_ItemCash = m_nEconomy_Work_LimitRupiah = g_cNPCControl->HT_iNPCControl_CalPurchasingPriceForChargeItem( m_dwBuyItem, m_dwBuyItemCount );
	}
	else
	{
		if (m_dwBuyItem == 7068) // 특정 물약의 경우에는 개수를 묶음으로 판매
			m_dwBuyItemCount = m_dwBuyItemCount * 250;
		if (m_dwBuyItem == 6828) // 특정 물약의 경우에는 개수를 묶음으로 판매
			m_dwBuyItemCount = m_dwBuyItemCount * 240;

		m_ItemCash =  m_ItemCash * m_dwBuyItemCount;
	}

	if( m_ItemCash < 0 || m_MyCash < m_ItemCash )
	{
		CHTString str; 	m_MessageCode = 1;
		if ( !CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex))
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonMoneyErr, &str );	// 아이템 구입에 필요한 루피아가 부족합니다
		else
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonCashErr, &str );	// 아이템 구입에 필요한 캐쉬가 부족합니다.
		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}

	// 만약 인벤토리 공간이 부족하다면 구입실패
	// Step 1) 구입할 아이템 최대 중첩 갯수 얻기
	byte byteMaxCount = 0;
	int byteMaxCount2 = 0;
	if( g_pParamMgr->HT_bLockID( m_dwBuyItem ) == true )
	{
		g_pParamMgr->HT_bGetItemMaxCount( &byteMaxCount );
		g_pParamMgr->HT_bUnLockID( m_dwBuyItem );
	}

	if (CHTParamIDCheck::HT_bIsItemChargeContinuance( m_dwBuyItem ) == true)	// 시간성 지속 아이템이라면 1로 처리한다.
	{
		if (m_dwBuyItem == 6828) byteMaxCount=240;
		else
		byteMaxCount = 1;
	}

	// Step 2) 현재 인벤토리 빈공간 얻기
	int BlankSpace = g_cItemSystem->HT_iItemAlSetPosInventoryBlankCheck();

	int maxInven;	// 사용하는 인벤토리 공간 갯수 추출
	if (g_cEquipInventory->m_bUsableInventory == false)	{maxInven = 24;} else {maxInven = 48;}

	// Step 3) 인벤토리 모두 조사하여, 해당 아이템과 같은 종류가 있는지 찾고, 중첩이 가능한지 조사하여 해당 갯수만큼 여유공간이 있는지 확인한다.
	int ExtraBlank = 0;

	DWORD KeyID = 0, dwItemIndex = 0;
	for (int i = 0; i < maxInven; ++i) // 사용하는 인벤토리만큼 조사
	{
		KeyID = g_cItemSystem->HT_dwItemSystem_GetItemKeyIDFromInvenLocation( i + _SLOTCURRECT_INVEN );	// 키얻기
		dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( KeyID );				// 아이디 얻기
		if (dwItemIndex == m_dwBuyItem)	// 인벤토리 속에 구입하려는 아이템과 같은 아이템이 존재 한다면 남은 중첩갯수 추출
		{
			if ((CHTParamIDCheck::HT_bIsItemChargeContinuance( m_dwBuyItem ) == false) || (m_dwBuyItem == 6828) )	// 시간성 지속 아이템이 아닐경우에만 처리
			{
				int ExtraSpace = g_cItemSystem->HT_wItemSystem_GetItemMaxPackCount( KeyID ) - g_cItemSystem->HT_iItemSystem_GetItemCount( KeyID );
				ExtraBlank += ExtraSpace;
			} 
		}
	}
	ExtraBlank += (BlankSpace * byteMaxCount); // 마지막으로 남은 공간에 최대갯수로 채워넣음

	// Step 4) 중첩 가능한 충분한 공간이 있다면 구입 가능, 그렇지 못하면 구입 실패
	if (ExtraBlank < iCount)
	{
		// 만약 공간이 부족하면 구입하지 못하게 한다.
		CHTString strString;
		HT_g_Script_SetMessage( eMsgItemCommonInvenLack, &strString );	// 인벤토리 공간이 부족합니다.
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
		return;
	}


	CHTString str; 	m_MessageCode = 3;
	if ( !(CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) )
	{
		if (g_iInationalType != INATIONALTYPE_KOREA)
		{
			g_pMessageMgr->HT_bGetMessage( eMsgItemBuyQuestionItemNum, &str );	// %s개를 구입하시겠습니까?
			CHTString num; num.HT_szFormat("%d", m_dwBuyItemCount);
			CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
			char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString()); strncpy(str, str2, 250);
		}
		else
		{
			// 캐쉬인지 루피아인지에 따라 다른 메시지 출력
			if ( !CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex))
			{
				g_pMessageMgr->HT_bGetMessage( eMsgItemBuyMsg1, &str );	// %s %s개를 %s 루피아에 구입하시겠습니까?
				CHTString num; num.HT_szFormat("%d", m_dwBuyItemCount);
				CHTString num2; num2.HT_szFormat("%d", m_ItemCash); 
				CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
				char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString(), num2.HT_szGetString()); strncpy(str, str2, 250);
			}
			else
			{
				g_pMessageMgr->HT_bGetMessage( eMsgItemBuyMsg2, &str );	// %s %s개를 %s 캐쉬에 구입하시겠습니까?
				CHTString num; num.HT_szFormat("%d", m_dwBuyItemCount);
				CHTString num2; num2.HT_szFormat("%d", m_ItemCash); 
				CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
				char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString(), num2.HT_szGetString()); strncpy(str, str2, 250);
			}
		}
	}
	else
	{
		g_pMessageMgr->HT_bGetMessage( eMsgPremiumBuyQuestion, &str );	// %s개를 %s캐쉬로 구입하시겠습니까?
		CHTString num; num.HT_szFormat("%d", m_dwBuyItemCount);
		CHTString num2; num2.HT_szFormat("%d", m_ItemCash);
		CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
		char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString(), num2.HT_szGetString()); strncpy(str, str2, 250);
	}
	g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 1);
	return;
}
/*
// 수리 요구
HTvoid CHTUIMerchantWindow::HT_vNetWork_CSP_REQ_ITEM_REPAIR()
{
	PS_CSP_REQ_ITEM_REPAIR info = HT_NULL;
	info = new S_CSP_REQ_ITEM_REPAIR;

	info->snNPCIndex = m_iNPCIndex;	// NPC 인덱스
	
	// 아이템이 위치한 장소와 위치 index
	HT_ITEMSETTING_FLAG sLocRoom;
	sLocRoom.nInventory = sLocRoom.nLocation = -1;
	g_cItemSystem->HT_bItemSystem_GetItemPos( m_dwFixDisjointKeyID, sLocRoom );
	if( sLocRoom.nInventory == -1 || sLocRoom.nLocation == -1 )
	{
		HT_DELETE( info );
		return;
	}

	if( sLocRoom.nLocation == ITEM_LOCATION_NPC )
	{
		info->byPlace =	ITEM_PLACE_CARGO ; 
		info->byIndex = ( sLocRoom.pCellPos.y * _GOODSKEEP_INVEN_WIDTH + sLocRoom.pCellPos.x )
							+ ( sLocRoom.nInventory * _GOODSKEEP_INVEN_WIDTH * _GOODSKEEP_INVEN_HEIGHT );
	}
	else if( sLocRoom.nLocation == ITEM_LOCATION_EQUIP )
	{
		info->byPlace =	ITEM_PLACE_EQUIP ;
		info->byIndex = sLocRoom.nInventory;
	}
	else //if( sLocRoom.nLocation == ITEM_LOCATION_PC )
	{
		info->byPlace =	ITEM_PLACE_INVEN ;
		info->byIndex = ( sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y )
							+ ( sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT );
	}

	g_pNetWorkMgr->RequestItemRepair( info );
	
	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemRepair : %d:(%d:%d)", 
													info->snNPCIndex, info->byPlace, info->byIndex );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
 
// 수리 결과
HTvoid CHTUIMerchantWindow::HT_vNetWork_SCP_RESP_ITEM_REPAIR( PS_SCP_RESP_ITEM_REPAIR info )
{
	// KeyID 생성
	HTint iKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID);
	m_dwFixDisjointKeyID = iKeyID;

	if( info->byResult == 0x00 )
	{
		m_bMessage_Error = HT_FALSE;	// 에러 없음

		//---------- 시스템창에 아이템 획득 출력 ------------//
		m_iSpendMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney() - info->nMoney;
		if(m_iSpendMoney < 0 )
			m_iSpendMoney = 0;

		if (info->byDummy == 1)	// 루피아 출력
		{
			// %d루피아를 사용해서 %s이(가) 수리되었습니다.
			HT_vNPCControl_SetMessage( eMsgItemRepairSuccess );
		}
		else
		{
			HT_vNPCControl_SetMessage( eMsgItemRepairOK );
		}
		        
		// 돈 갱신
		if(info->nMoney > 0)
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(info->nMoney);
		else
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(0);

		// 수리된 아이템의 내구도를 갱신한다.
		HTshort sMaxDur = g_cItemSystem->HT_sItemSystem_GetMaxDurability( m_dwFixDisjointKeyID );
		if( 0 <= sMaxDur && sMaxDur < HT_ITEM_INFINITY_DURABILITY )	// 무한내구도는 255
			g_cItemSystem->HT_dwItemSystem_SetCurDurability( m_dwFixDisjointKeyID, sMaxDur);

		// 현재 내구도에 따른 수리 표시
		g_cItemSystem->HT_vItemSystem_RenewalDurabilityWarning( );

		// 대화상자 대화 바꾸기
		// 선택문의 마지막에는 선택문이 아닌 다른 입력에 의해 다음 단계로 넘어갈 때 사용하기 위한 값이 있다
		// 0~m_nSelectCount-1 : 선택문, m_nSelectCount : 확인, m_nSelectCount+1 : 취소
		// 마우스 클릭에 따라서 다음 단계로 넘어간다.
		HT_vNPCControl_GetNextStep(m_nSelectCount);	
	} 
	else 
	{
		// 완료창에 보여줄 메세지
		if( info->byResult == REPLY_ITEM_REPAIR_MONEY_WANT)
            // 수리에 필요한 루피아가 부족합니다. 	
			HT_vNPCControl_SetMessage( eMsgItemCommonMoneyErr );
		else if ( info->byResult == REPLY_ITEM_REPAIR_OUTINDEX )
			// 아이템을 찾을 수 없습니다. 
			HT_vNPCControl_SetMessage( eMsgItemCommonCannotFindInfo );
		else if( info->byResult == REPLY_ITEM_REPAIR_ENOUGH)
			// 수리할 필요가 없는 아이템입니다. 
			HT_vNPCControl_SetMessage( eMsgItemRepairNeedNot );
		else
			// 아이템을 수리하지 못했습니다. 
			HT_vNPCControl_SetMessage( eMsgItemRepairFail );

		m_bMessage_Error = HT_TRUE;	// 에러 있음
		// 완료창 띄움
		m_byMessageWin = NPC_MESSAGE_COMPLETE;
	}
	// 시스템 창에 표시
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, m_szMessage );
}
*/
void CHTUIMerchantWindow::HT_vNetWork_CSP_Req_Item_Buy()
{
	PS_CSP_REQ_ITEM_BUY info = HT_NULL;
	info = new S_CSP_REQ_ITEM_BUY;

	if (CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex) == TRUE)
	{
		info->snNPCIndex = g_cNPCControl->HT_iGetCashNPC(g_cUIMerchantWindow->m_iTabNo);
	}
	else
	{
		info->snNPCIndex = m_iNPCIndex;
	}
	info->snItemIndex = HTshort(m_dwBuyItem - HT_ITEM_INDEX_START);
	// 구입할 개수
	info->snItemCount = m_dwBuyItemCount;

	// 루피아는 서버가 인벤에서 자동으로 뺀다.
	g_pNetWorkMgr->RequestItemBuy( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemBuy : %d:%d-%d개", 
	//												info->snNPCIndex, info->snItemIndex, info->snItemCount );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}
 
void CHTUIMerchantWindow::HT_vNetWork_SCP_Resp_Item_Buy( PS_SCP_RESP_ITEM_BUY info )
{
	m_dwBuyItem = info->snItemIndex + HT_ITEM_INDEX_START ;
	int m_iSpendMoney = 0;

	if( info->byResult == 0x00 )
	{
		if (CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) // 프리미엄 아이템 상인 npc의 경우
		{
			g_cNPCControl->m_iSpendMoney = g_cNPCControl->m_dwNeedValue = g_cNPCControl->m_nCash = info->nMoney;
			m_iSpendMoney = m_ItemCash;	// 캐쉬 갱신 
		}
		else
		{
			m_iSpendMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney() - info->nMoney;
			// 루피아 갱신
			if(info->nMoney > 0)
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->nMoney );
			else
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney(0);
		}
		// 시스템창에 아이템 획득 출력
		if(m_iSpendMoney < 0 )	m_iSpendMoney = 0;

		// 완료창에 보여줄 메세지
		CHTString str; 	m_MessageCode = 1;
		if ((CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) )
		{
			g_pMessageMgr->HT_bGetMessage( eMsgPremiumBuyOK, &str );	// %s을(를) %s캐쉬로 구입했습니다.
			CHTString num; num.HT_szFormat("%d", m_iSpendMoney);
			CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
			char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString()); strncpy(str, str2, 250);
			//g_cNPCControl->HT_vNPCControl_DialogWin_AntiActive();

			HTtchar text[1000] ;
			sprintf(text, g_cNPCControl->m_szQuestion, g_cNPCControl->m_nCash); // 파라미터 값 설정
			g_cUIManager->HT_SetTextLongLabelControl( _DIALOG_NPCWINDOW, 2, text);

		}
		else
		{
			g_pMessageMgr->HT_bGetMessage( eMsgItemBuyOneOK, &str );	// %s을(를) %s루피아로 구입했습니다.
			CHTString num; num.HT_szFormat("%d", m_iSpendMoney);
			CHTString name; g_pParamMgr->HT_bGetItemName(m_dwBuyItem, &name );
			char str2[1024]; sprintf(str2, str, name.HT_szGetString(), num.HT_szGetString()); strncpy(str, str2, 250);
		}
		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );

		return;
 	}
	else
	{
		CHTString str; 	m_MessageCode = 1;
		switch( info->byResult )
		{
			case REPLY_ITEM_BUY_GOLD_WANT :	// 돈 부족
				if ((CHTParamIDCheck::HT_bIsChargeNPC(m_iNPCIndex)) )
					g_pMessageMgr->HT_bGetMessage( eMsgItemCommonCashErr, &str );	// 캐쉬가 부족합니다.
				else
					g_pMessageMgr->HT_bGetMessage( eMsgItemCommonMoneyErr, &str );	// 루피아가 부족합니다.
				break;
			case REPLY_ITEM_BUY_INVENTORY_LACK : // 인벤토리 공간 부족
				g_pMessageMgr->HT_bGetMessage( eMsgItemCommonInvenLack, &str );	// 인벤토리 공간이 부족합니다.
				break;
			case REPLY_ITEM_BUY_MINCOUNT :
				{
					int m_iWorkItemMinCount = g_cNPCControl->HT_iNPCControl_GetMinCountForChargeItem( m_dwBuyItem );
					g_pMessageMgr->HT_bGetMessage( eMsgItemBuyMinCountErr, &str );	 // 최소 구입 개수 오류
					CHTString num; num.HT_szFormat("%d", m_iWorkItemMinCount);
					char str2[1024]; sprintf(str2, str, num.HT_szGetString()); strncpy(str, str2, 250);
				}
				break;
			default:
				g_pMessageMgr->HT_bGetMessage( eMsgItemBuyFail, &str );	 // 아이템을 구입하지 못했습니다.
				break;
		}
		
		// 에러메시지 출력 
		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}

}

// 아이템 판매
void CHTUIMerchantWindow::HT_vNetWork_CSP_Req_Item_Sell()
{
	PS_CSP_REQ_ITEM_SELL info = HT_NULL;
	info = new S_CSP_REQ_ITEM_SELL;

	info->snNPCIndex = m_iNPCIndex;	// NPC 인덱스

	unsigned int	nWindowIndex = 0, nControlIndex = 0;
	int iTextureID = 0;
	g_cUIManager->HT_GetSlotBoxControlSourInfo(nWindowIndex, nControlIndex, iTextureID);

	// x, y 축 변경하여 인덱스 계산
	if (nControlIndex < 124)	// 첫번째 슬롯의 경우
	{
		info->byPlace =	ITEM_PLACE_INVEN ; 
		int x = (nControlIndex - 100) % MAX_INVEN_X; 
		int y = (nControlIndex - 100) / MAX_INVEN_X;
		info->byIndex = y + (x * MAX_INVEN_Y);
	}
	else
	{
		info->byPlace =	ITEM_PLACE_INVEN ; 
		int x = (nControlIndex - 124) % MAX_INVEN_X; 
		int y = (nControlIndex - 124) / MAX_INVEN_X;
		info->byIndex = 24 + y + (x * MAX_INVEN_Y);
	}

	g_pNetWorkMgr->RequestItemSell( info );
	
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqItemSell : %d:(%d:%d)", 
	//													info->snNPCIndex, info->byPlace, info->byIndex );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}


// 판매 결과
void CHTUIMerchantWindow::HT_vNetWork_SCP_Resp_Item_Sell( PS_SCP_RESP_ITEM_SELL info )
{
	// KeyID 생성
	HTint iKeyID = 0;
	BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), info->byPlace, info->byIndex, iKeyID);
	DWORD m_dwFixDisjointKeyID = iKeyID;

	CHTString str; 	m_MessageCode = 1;

	if( info->byResult == 0x00 )
	{
		// 버그수정 2005. 5. 18 선영범 (퀵바에 남아있는 물품 판매시 퀵바에서도 제거)
		//DWORD dwIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( iKeyID );
		//if( g_cQuickSlot->HT_bBeUsedKeyID( dwIndex, iKeyID ) )
		//	g_cQuickSlot->HT_vDeleteIconInResentSlotByIndex( dwIndex, iKeyID );

		//---------- 시스템창에 아이템 획득 출력 ------------//
		int m_iSpendMoney = info->nMoney - g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
		if(m_iSpendMoney < 0 )	m_iSpendMoney = 0;

		g_cItemSystem->HT_vItemSystem_DeleteItem( m_dwFixDisjointKeyID );			// 해체된 아이템 제거
				
		if(info->nMoney > 0)	// 돈 갱신
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(info->nMoney);
		else
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney(0);

		unsigned int	nWindowIndex = 0, nControlIndex = 0;
		int iTextureID = 0;
		g_cUIManager->HT_GetSlotBoxControlSourInfo(nWindowIndex, nControlIndex, iTextureID);
		g_cUIManager->HT_SetSlotImage(nWindowIndex, nControlIndex, 0);

		g_pMessageMgr->HT_bGetMessage( eMsgItemSellSuccess, &str );	// %d루피아에 %s이(가) 판매되었습니다.
		CHTString num; num.HT_szFormat("%d", m_iSpendMoney);
		CHTString name; g_pParamMgr->HT_bGetItemName(m_dwSellItem, &name );
		char str2[1024]; sprintf(str2, str, num.HT_szGetString(), name.HT_szGetString()); strncpy(str, str2, 250);

		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}
    else
	{
		g_cUIManager->HT_RefuseSlotImageMoving();		// 이미지 원래상태로 옮김

		// 완료창에 보여줄 메세지
		if( info->byResult == REPLY_ITEM_SELL_INVENTORY_LACK)
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonInvenLack, &str );		// 인벤토리에 공간이 부족합니다.
		else if(info->byResult == REPLY_ITEM_SELL_NO_INVENTORY)
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonNoInventory, &str );	// PC인벤토리 이외의 공간에 있는 아이템입니다.
		else if( info->byResult == REPLY_ITEM_SELL_OUTINDEX )
			g_pMessageMgr->HT_bGetMessage( eMsgItemCommonCannotFindInfo, &str );// 아이템을 찾을 수 없습니다.
		else
			g_pMessageMgr->HT_bGetMessage( eMsgItemSellFail, &str );			// 아이템을 판매할 수 없습니다.

		g_cUIManager->HT_MessageBox(UI_WINDOW_MERCHANT, str, 0);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
		return;
	}
}



/*
//
// CHTUISlotInformationWindow Class 맴버 함수를 모아놓았습니다.
//

CHTUISlotInformationWindow::CHTUISlotInformationWindow() {}
CHTUISlotInformationWindow::~CHTUISlotInformationWindow() {}

// 상태창을 생성합니다.
void CHTUISlotInformationWindow::HT_vSlotInformationWindow_Init()
{
	// 윈도우 생성
	g_cUIManager->HT_CreateWindow(UI_WINDOW_SLOTINFORMATION, _T("Information"), 258, 252, g_cUIManager->g_cUISlotInformationWindow.HT_hrSlotInformationWindow_InputCheck, 2);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SLOTINFORMATION, 0, "", 1, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 30, 235, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SLOTINFORMATION, 1, "", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 30+(1*20), 235, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_SLOTINFORMATION, 2, "", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 30+(2*20), 235, 45);
	for (int i=3; i<10; ++i)
		g_cUIManager->HT_AddLabelControl(UI_WINDOW_SLOTINFORMATION, i, "", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 30+(i*20), 235, 19);
}

// 윈도우 정보 갱신시 호출 (이곳에서 UI Widnow의 컨트롤 정보들 셋팅 및 배치를 한다.)
void CHTUISlotInformationWindow::HT_vSlotInformationWindow_SetInfo()
{
	for (int i=1; i<20; ++i)
		g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_SLOTINFORMATION, i, "");
}

// 외부에서 띄움 (각 윈도우의 클래스가 UI메니저에 들어간다면 의미없음)
void CHTUISlotInformationWindow::HT_vSlotInformationWindow_WindowPopup()
{
}

// 윈도우 제어 시도시 호출 (이곳에서 입력장치로부터 들어온 정보를 처리한다.)
void CHTUISlotInformationWindow::HT_hrSlotInformationWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	g_cUIManager->HT_HideWindow(UI_WINDOW_SLOTINFORMATION);
}
*/


//
// CHTUIEmblemWindow Class 맴버 함수를 모아놓았습니다.
//

CHTUIEmblemWindow::CHTUIEmblemWindow() {}
CHTUIEmblemWindow::~CHTUIEmblemWindow() {}

// 상태창을 생성합니다.
void CHTUIEmblemWindow::HT_vEmblemWindow_Init()
{
}

// 윈도우 정보 갱신시 호출 (이곳에서 UI Widnow의 컨트롤 정보들 셋팅 및 배치를 한다.)
void CHTUIEmblemWindow::HT_vEmblemWindow_SetInfo()
{
	if (m_Index != 0)	// 앰블럼 꾸미기
	{/*
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 11, m_Back1-1 );
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 12, m_Back2-1 );
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 13, UI_GUILD_TITLETEX + m_Title - 1 );
		g_cUIManager->HT_SetTextureControlColor( UI_WINDOW_EMBLEM, 11, AMBLEM_COLOR[m_iColor-1]);
		*/
	}

	// 메뉴에 있는 엠블럼들 그리기
	for (int i = 1; i <= 2; ++i)
		for (int j = 1; j <= 6; ++j)
		{
			switch(m_iTabNo)
			{
			case 1:
				g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j*i, 28401 + (j * i) - 1);
				break;
			case 2:
				g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j*i, 28001 + (j * i) - 1);
				break;
			case 3:
				g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j*i, 28601 + (j * i) - 1);
				break;
			}
		}
}

// 외부에서 띄움 (각 윈도우의 클래스가 UI메니저에 들어간다면 의미없음)
void CHTUIEmblemWindow::HT_vEmblemWindow_WindowPopup()
{

}

// 윈도우 제어 시도시 호출 (이곳에서 입력장치로부터 들어온 정보를 처리한다.)
void CHTUIEmblemWindow::HT_hrEmblemWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
}




//
// CHTUIQuestWindow Class 맴버 함수를 모아놓았습니다.
//

CHTUIQuestWindow::CHTUIQuestWindow() {}
CHTUIQuestWindow::~CHTUIQuestWindow() {}

// 상태창을 생성합니다.
void CHTUIQuestWindow::HT_vQuestWindow_Init()
{
	CHTString strMessage;
	// 윈도우 생성
	g_cUIManager->HT_SetScriptMessage( eMsgQuest, &strMessage, _T(""), _T("") );	//	Option
	g_cUIManager->HT_CreateWindow(UI_WINDOW_QUEST, strMessage, 330, 468, g_cUIQuestWindow->HT_hrQuestWindow_InputCheck, 2);//Quest
	g_cUIManager->HT_WindowArrangement(UI_WINDOW_QUEST, 5);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 3, 36, 1400, 322, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 9, 40, 30, 1401, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 0, eMsgQuestDiaryQuest, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, 30, 152, 19);//퀘스트 일지
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 9, 172, 58, 1400, 152, 19);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 5, 64, 1400, 3, 380);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 168, 64, 1400, 3, 380);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 58, 1400, 166, 6);
	//g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 444, 1400, 166, 6);

	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 0, eMsgQuestContinueQuest, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 172, 58, 152, 19);//진행중인 퀘스트
	g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_QUEST, 1, 309, 83, 80, 20);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 76, 1400, 322, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 164, 1400, 322, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 5, 82, 1400, 3, 82);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 324, 82, 1400, 3, 82);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 9, 172, 176, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 0, eMsgQuestConditionQuest, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 172, 176, 152, 19);//퀘스트 조건
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 195, 1400, 322, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 319, 1400, 322, 6);
	g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_QUEST, 2, 309, 202, 116, 20);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 5, 201, 1400, 3, 118);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 324, 201, 1400, 3, 118);

	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 9, 172, 332, 1400, 152, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 0, eMsgQuestCompletionQuest, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 172, 332, 152, 19);//완료 퀘스트
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 351, 1400, 322, 6);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 8, 5, 444, 1400, 322, 6);
	g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_QUEST, 3, 309, 358, 85, 20);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 5, 357, 1400, 3, 87);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_QUEST, 0, 1, 324, 357, 1400, 3, 87);

	// 진행 퀘스트 버튼 4개
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 1, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 82, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 2, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 102, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 3, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 122, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 4, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 142, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 1, 0, 8, 82, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 2, 0, 8, 102, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 3, 0, 8, 122, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 4, 0, 8, 142, 9, 9, 1500, 302, 19);
	
	// 완료 퀘스트 버튼 4개
	g_cUIManager->HT_AddLongLabelControl(UI_WINDOW_QUEST, 9, " ", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 206, 285, 80);
	g_cUIManager->HT_SetArrangementLongLabelControl(UI_WINDOW_QUEST, 9, 7);

	// 퀘스트 조건 텍스트
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 5, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 360, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 6, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 380, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 7, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 400, 302, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_QUEST, 8, ".", 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 420, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 5, 0, 8, 360, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 6, 0, 8, 380, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 7, 0, 8, 400, 9, 9, 1500, 302, 19);
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_QUEST, 8, 0, 8, 420, 9, 9, 1500, 302, 19);

	for (int i = 1; i < 9; ++i)
		g_cUIManager->HT_SetButtonToolTipOff(UI_WINDOW_QUEST, i);

	// 퀘스트 스트링 로딩
	m_FocusIndex = 1;
	HT_vQuest_TutorialMsgLoading();
	m_bFalshState = false;
	g_bMoonBang = false;
	m_bFalshState = false;
	m_bReQuestItemUsingOne = true;
}

// 윈도우 정보 갱신시 호출 (이곳에서 UI Widnow의 컨트롤 정보들 셋팅 및 배치를 한다.)
void CHTUIQuestWindow::HT_vQuestWindow_SetInfo()
{
	for (HTint i = 0; i < QUEST_MAX_NUM; ++i)
	{
		m_ProgressResultStr[i] = "";
		m_CompleteResultStr[i] = "";
		m_ProgressStr[i] = "";
		m_CompleteStr[i] = "";
	}

	vSetInfo(1);
	vSetInfo(2);
	vSetInfo(3);
}

// 외부에서 띄움 (각 윈도우의 클래스가 UI메니저에 들어간다면 의미없음)
void CHTUIQuestWindow::HT_vQuestWindow_WindowPopup()
{

}

// 윈도우 제어 시도시 호출 (이곳에서 입력장치로부터 들어온 정보를 처리한다.)
void CHTUIQuestWindow::HT_hrQuestWindow_InputCheck(int iAction, int iTarget, int iTargetID)
{
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:	// 버튼의 경우 처리
		switch(iTargetID)
		{
		case -2:// 백그라운드 다운시
			break;
		case -1:// 종료버튼
			//g_cUIManager->HT_HideWindow(UI_WINDOW_QUEST);
			g_cQuest->HT_vQuest_ActiveSw();
			break;
		case 1:	case 2:	case 3:	case 4:	case 5:	case 6:	case 7:	case 8:
			g_cUIQuestWindow->m_FocusIndex = iTargetID;
			g_cUIQuestWindow->vSetInfo(2);
			break;
    	}
	case UI_TARGET_SCROLLBAR:
		g_cUIQuestWindow->vSetInfo(iTargetID);	// 화면 갱신
		break;
	case UI_TARGET_MESSAGEBOX:
		if (iTargetID == 2)
			g_cUIQuestWindow->HT_vNetWork_CSP_REQ_Quest_DIALOG(0x00, 0x00);	// 승낙
		else
			g_cUIQuestWindow->HT_vNetWork_CSP_REQ_Quest_DIALOG(0x00, 0x01);	// 거절
	}
}

//----------튜토리얼 퀘스트 수행 여부를 서버로 전송---------//
void CHTUIQuestWindow::HT_vNetWork_CSP_REQ_Quest_DIALOG(DWORD dwDialogIndex, BYTE byResult)
{
	PS_CSP_QUEST_DIALOG info = HT_NULL;
	info = new S_CSP_QUEST_DIALOG;

	info->snDialog = (HTshort)dwDialogIndex;
	info->byResult = byResult;

	g_pNetWorkMgr->RequestQuestDialog(info);

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqQuestDialog : %d-%d", dwDialogIndex, byResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
	HT_DELETE( info );
}

//-------------퀘스트 관련 에러 정보---------------//
void CHTUIQuestWindow::HT_vNetWork_SCP_RESP_Quest_Dialog( PS_SCP_QUEST_DIALOG info )
{
	CHTString str;
	HTint idMessage = eMsgParamNone;
 
	switch( info->wIndex)
	{
	case 1:	// 인벤토리 공간이 부족하여 퀘스트를 진행할 수 없습니다. 인벤토리를 비우고 다시 시도 하세요.
		idMessage = eMsgQuestInvenLack;	break;
	case 2:	// 프라나가 부족합니다.
		idMessage = eMsgQuestPranaLack; break;
	case 5:	// 퀘스트를 진행하기 위한 아이템이 없습니다.
		idMessage = eMsgQuestNotExistItem; break;
	case 6:	// 해당 아이템은 판매하거나 타인에게 줄 수 없는 퀘스트용 아이템 입니다.
		idMessage = eMsgQuestQuestOnlyItem; break;
	default:// 퀘스트를 진행할 수 없습니다.
		idMessage = eMsgQuestCannotProgress; break;
	}

	if( idMessage != eMsgParamNone && g_pMessageMgr->HT_bGetMessage( idMessage, &str ) == true )
	{
		//g_cUIManager->HT_MessageBox(UI_WINDOW_QUEST, str, 0);// 완료창 띄움
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_QUEST, str );
	}
}

// 서버로부터 퀘스트 정보 받으면 퀘스트 목록을 생성합니다.
void CHTUIQuestWindow::HT_vNetWork_SCP_RESP_Quest_History( HTbyte byQuest[MAX_EVENT_FLAG] )
{
	int ProgressIndex = 0, CompleteIndex = 0;

	// 퀘스트가 갱신되면 메인바 버튼을 깜박임으로 변경, 단, 처음 받는다면 무시
	bool bcmp = false, bcmpc = false;
	for (int a=0; a<100; ++a)
	{
		if (m_byQuest[a] != byQuest[a])
		{
			bcmp = true;

			if (byQuest[a] == 255)	// 만약 퀘스트 완료라면 체크
				bcmpc = true;
		}
		m_byQuest[a] = byQuest[a];
	}
	if (bcmp == true && m_bFalshState == true)
	{
		// 퀘스트 창이 닫혀 있을때만 깜박임 처리
		if (g_cUIManager->HT_isShowWindow( _DIALOG_QUEST ) == false)
			g_cUIManager->HT_SetButtonControlState( _DIALOG_MAINBAR, 4, 3 );

		// 퀘스트 완료 이펙트
		// 마지막것이 완료라면 완료 이펙트 발동
		if( bcmpc == true )
		{
			HTint idFx;
			g_pEngineHandler->HT_hrStartSFX( &idFx, HT_FX_QUESTCOMPLETE, g_cMainCharacter->HT_vMainChar_GetModelID(), HT_FALSE );
		}
	}
	m_bFalshState = true;

	// 캐릭터 생성후 처음 로그인 시 초보자 퀘스트 수행 여부 질문창을 띄운다.
	if( byQuest[0] == 1 )
	{
		if( g_cTutorialSystem->HT_bTutorial_TrainendSw() == 0 )
		{
			g_cTutorialSystem->HT_vNetWork_SCP_RESP_Quest_HistoryInfoData_Save( byQuest );
			return;
		}
		else
		{
			CHTString str;
			g_pMessageMgr->HT_bGetMessage( eMsgQuestTutorialStartQuestion, &str );
			// 메시지 박스 띄움
			g_cUIManager->HT_MessageBox(UI_WINDOW_QUEST, str, 1);
		}
	}

	for (HTint i = 0; i < QUEST_MAX_NUM; ++i)
	{
		m_ProgressResultStr[i] = "";
		m_ProgressStr[i] = "";
		m_CompleteResultStr[i] = "";
		m_CompleteStr[i] = "";
	}

	for( HTint index = 1; index < 100 ; ++index )	// 일단 퀘스트는 최대 100개로 정의
		if( index < QUEST_MAX_NUM && byQuest[index] != 0 )	// 중간에 진행한 퀘스트가 없다면 루프탈출
		{
			switch(byQuest[index])
			{
			case QUEST_STATUS_FAIL:	// 실패 라면 (254)
				break;
			case QUEST_STATUS_SUCCESS: // 완료된 퀘스트라면 완료-퀘스트목록에 정보를 추가합니다.(255)
				for(int nArrayNo = 0; nArrayNo < QUEST_MAX_NUM ; ++nArrayNo )	// 서브 퀘스트 수행
				{
					if( m_sQuestText[nArrayNo].byIndex == index )
					{
						// 해당 퀘스트 타이틀 얻기
						g_cUIQuestWindow->m_CompleteStr[CompleteIndex] = m_sQuestText[nArrayNo].szTitle;
						g_cUIQuestWindow->m_CompleteResultStr[CompleteIndex] = m_sQuestText[nArrayNo].szStepMsg[m_sQuestText[nArrayNo].nStepNo-1];
						CompleteIndex++;

						// 토용장인이 있으면 삭제후 재생성
						if (index == 47 && g_wResentZoneServerID == 12)
						{
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1305 );

							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1304 );
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1304 );
						}

						// 학문의 즐거움은 끝이 없어라를 마칠시 
						if (index == 49)
						{
							g_bMoonBang = true;
						}

						// 퀘스트를 완료했다면 북두쭈앙쯔 삭제
						if (index == 50)
						{
							if (g_wResentZoneServerID != 12)
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1306 );
						}

						// 낯선 동방의 나라를 완료했을경우 퀘스트 초기화 아이템 사용 불가
						if (index == 51)
						{
							m_bReQuestItemUsingOne = false;
						}

						// 퀘스트를 완료했다면 주정뱅이 삭제
						if (index == 52)
						{
							if (g_wResentZoneServerID == 1)
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1437 );
						}

						// 퀘스트를 완료했다면 나오키와 유리 삭제
						if (index == 54)
						{
							if (g_wResentZoneServerID == 17)
							{
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1438 );	// 유리가 있으면 삭제
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1439 );	// 나오키가 있으면 삭제
							}
						}

						// 퀘스트를 완료했다면 무사들 삭제
						if (index == 55)
						{
							if (g_wResentZoneServerID == 17)
							{
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1440 );	// 전쟁터 폐허의 정찰병이 있으면 삭제
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1441 );	// 버려진 요새의 정찰병이 있으면 삭제
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1442 );	// 갓파부락의 정찰병이 있으면 삭제
								g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1443 );	// 광산지역의 정찰병이 있으면 삭제
							}
						}

						break;
					}	
				}	
				break;
			default: // 진행중인 퀘스트라면 진행중-퀘스트목록에 정보를 추가합니다. (1~253)
				for(int nArrayNo = 0; nArrayNo < QUEST_MAX_NUM ; ++nArrayNo )
				{
					if( m_sQuestText[nArrayNo].byIndex == index )
					{
						// 해당 퀘스트 타이틀 얻기
						g_cUIQuestWindow->m_ProgressResultStr[ProgressIndex] = m_sQuestText[nArrayNo].szStepMsg[byQuest[index]-1];
						g_cUIQuestWindow->m_ProgressStr[ProgressIndex] = m_sQuestText[nArrayNo].szTitle;

						// 퀘스트 진행시 깜박거리게
						//if (m_bFalshState == false)
						//m_iLastProgressIndex = byQuest[index]-1;

						// 몬스터 잡는 부분이라면 숫자 카운트
						int iMobNo = SetMonsterKillNo(index, m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1]);
						if (iMobNo != 0)
							sprintf(g_cUIQuestWindow->m_ProgressResultStr[ProgressIndex], g_cUIQuestWindow->m_ProgressResultStr[ProgressIndex], iMobNo - byQuest[MOB_COUNT_QUEST_INDEX_START]);

						// 특정 NPC
						// 47번 퀘스트중 11번 스텝 진행중이라면 보이게...
						if (index == 47 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 11 && g_wResentZoneServerID == 9)	
						{
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1305 );// 토용이 있으면 삭제후 재생성
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1305 );
						}

						// 47번 퀘스트중 12번 스텝 진행중이라면 보이게...
						if (index == 47 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 12 && g_wResentZoneServerID == 12)	
						{
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1304 );	// 토용장인이 있으면 삭제후 재생성
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1304 );
						}

						// 50번 퀘스트중 4번 스텝 진행중이라면 북두쭈앙즈 보이게...
						if (index == 50 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 4 && g_wResentZoneServerID == 12)	
						{ 
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1306 );	// 북두쭈앙쯔가 있으면 삭제후 재생성
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1306 );
						}

						// 51번 퀘스트중 1번 스텝 이상 진행 한다면 퀘스트 초기화 아이템 단독 사용 불가
						if (index == 51 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 1 )
						{ 
							m_bReQuestItemUsingOne = false;
						}

						// 52번 퀘스트중 10번 스텝 진행중이라면 주정뱅이 보이게...
						if (index == 52 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 10 && g_wResentZoneServerID == 1)	
						{ 
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1437 );	// 주정뱅이가 있으면 삭제후 재생성
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1437 );
						}

						// 54번 퀘스트중 10번 스텝 진행중이라면 유리 보이게...
						if (index == 54 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 10 && g_wResentZoneServerID == 17)	
						{ 
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1438 );	// 유리가 있으면 삭제후 재생성
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1438 );
						}

						// 54번 퀘스트중 12번 스텝 진행중이라면 나오키 보이게...
						if (index == 54 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 12 && g_wResentZoneServerID == 17)	
						{ 
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1439 );	// 나오키가 있으면 삭제후 재생성
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1439 );
						}

						//// 54번 퀘스트중 13번 스텝 진행중이라면 나오키와 유리 안보이게...
						//if (index == 54 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 15 && g_wResentZoneServerID == 17)	
						//{ 
						//	g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1438 );	// 유리가 있으면 삭제
						//	g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1439 );	// 나오키가 있으면 삭제
						//}

						// 55번 퀘스트중 2번 스텝 진행중이라면 야스다의 정찰병들이 보이게...
						if (index == 55 && m_sQuestText[nArrayNo].nStepNum[byQuest[index]-1] >= 2 && g_wResentZoneServerID == 17)	
						{ 
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1440 );	// 전쟁터 폐허의 정찰병이 있으면 삭제후 재생성
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1440 );
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1441 );	// 버려진 요새의 정찰병이 있으면 삭제후 재생성
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1441 );
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1442 );	// 갓파부락의 정찰병이 있으면 삭제후 재생성
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1442 );
							g_sNPCSystem->HT_bNPCSystem_DeleteNPC( 1443 );	// 광산지역의 정찰병이 있으면 삭제후 재생성
							g_sNPCSystem->HT_bNPCSystem_CreateNPC( 1443 );
						}
					
						ProgressIndex++;
						break;
					}	
				}	
				break;
			}
		}

		// 스크롤바 재갱신
		g_cUIManager->HT_DelScrollBarControl(UI_WINDOW_QUEST, 1);
		g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_QUEST, 1, 309, 83, 80, ProgressIndex - 4);
		g_cUIManager->HT_DelScrollBarControl(UI_WINDOW_QUEST, 3);
		g_cUIManager->HT_AddScrollBarControl(UI_WINDOW_QUEST, 3, 309, 358, 85, CompleteIndex - 4);

		// 버튼 활성화 여부 결정
		for (int i = 1; i< 9; ++i)
			g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, i, false);		// 버튼 일단은 비활성화

		// 활성화 할 버튼만 가동
		if (ProgressIndex > 0) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 1, true);
		if (ProgressIndex > 1) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 2, true);
		if (ProgressIndex > 2) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 3, true);
		if (ProgressIndex > 3) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 4, true);

		if (CompleteIndex > 0) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 5, true);
		if (CompleteIndex > 1) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 6, true);
		if (CompleteIndex > 2) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 7, true);
		if (CompleteIndex > 3) g_cUIManager->HT_SetButtonEnable(UI_WINDOW_QUEST, 8, true);

		//g_cUIQuestWindow->m_FocusIndex = 1;
		this->vSetInfo(1);	// 화면 갱신
		this->vSetInfo(3);	// 화면 갱신
		this->vSetInfo(2);	// 화면 갱신
}

// 퀘스트 몬스터 킬 정보 출력
int	CHTUIQuestWindow::SetMonsterKillNo(HTint iIndex, HTint StepNo)
{ 
	switch(iIndex)
	{	// 아직도 하드코딩이지만 예전에 비해 획기적으로 줄였음
	case QUEST_TUTORIAL_5: if (StepNo == 3) return 10; break;	// 믈렉차 숫자
	case QUEST_BASIC_GRADE:	if (StepNo >= 4 && StepNo <= 10) return 3; break;	// 1차 전직
	case QUEST_MANDARA_9: if (StepNo == 4) return 10; break;	// 만다라 보아 사냥
	case QUEST_MANDARA_10: if (StepNo == 4) return 10; break;	// 아프라 바라하 라자 숫자
	case QUEST_SHAMBALA_1: if (StepNo == 4) return 30; if (StepNo == 7) return 15; break;	// 울카무카 & 울카무카 카우라 숫자
	case QUEST_SHAMBALA_4: if (StepNo == 4) return 30; break;	// 헤루카 숫자
	case QUEST_SHAMBALA_14: if (StepNo == 5) return 20; break;	// 아난가 숫자
	case QUEST_JINA_1: if (StepNo == 5) return 28; break;	// 자괴의 숫자
	case QUEST_JINA_3: if (StepNo == 5) return 10; if (StepNo == 8) return 15; break;	// 진모인 & 진모인 거수의 숫자
	case QUEST_JINA_5: if (StepNo == 8) return 30; break;	// 귀화상의 숫자
	case QUEST_JINA2_3: if (StepNo >= 5 && StepNo <= 56) return 10; break;	// 유배지 퀘스트 추가 (몹잡는 부분)
	case QUEST_K3_3: if (StepNo == 5 ) return 10; break; // 멧돼지의 숫자	// HTMessage도 수정해야한다.
	case QUEST_K3_5: if (StepNo == 24 ) return 30; break; // 염라병의 숫자	// HTMessage도 수정해야한다.
	}

	return 0;
}


// 퀘스트 목록에 출력
void	CHTUIQuestWindow::vSetInfo(int iTab)
{
	switch(iTab)
	{
	case 1:	// 첫번째 스크롤바
		{
			int index = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_QUEST, 1);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 1, m_ProgressStr[index]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 2, m_ProgressStr[index+1]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 3, m_ProgressStr[index+2]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 4, m_ProgressStr[index+3]);
			return;
		}
		break;
	case 2:	// 두번째 스크롤바
		break;
	case 3:	// 세번째 스크롤바
		{
			int index = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_QUEST, 3);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 5, m_CompleteStr[index]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 6, m_CompleteStr[index+1]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 7, m_CompleteStr[index+2]);
			g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_QUEST, 8, m_CompleteStr[index+3]);
			return;
		}
		break;
	}		

	// 설명문 갱신
	if (m_FocusIndex < 5)
	{
		int index = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_QUEST, 1);
		g_cUIManager->HT_SetTextLongLabelControl(UI_WINDOW_QUEST, 9, g_cUIQuestWindow->m_ProgressResultStr[index + m_FocusIndex - 1]);
	} 
	else
	{
		int index = g_cUIManager->HT_GetScrollBarValue(UI_WINDOW_QUEST, 3);
		g_cUIManager->HT_SetTextLongLabelControl(UI_WINDOW_QUEST, 9, g_cUIQuestWindow->m_CompleteResultStr[index + (m_FocusIndex-4) - 1]);
	}
}

//---------튜토리얼 메시지 로딩----------//
void CHTUIQuestWindow::HT_vQuest_TutorialMsgLoading()
{
	if( g_pMessageMgr == HT_NULL )
	{
		MessageBox(NULL, _T("HTQuest"), _T("Cannot Load QuestMessage!"), MB_OK);
		return;
	}

	CHTString strBuf;
	HTint	nArrayNo = 0, iID = 0, i = 0;
	HTshort sIndex = 0, sMaxStep = 0, sSubIndex = 0;

	for( iID = HT_MESSAGETYPE_QUESTMSG_START ; iID <= HT_MESSAGETYPE_QUESTMSG_END ; ++iID ) 
	{ 
		// 퀘스트 번호, 퀘스트 내의 UI창에 보여줘야 할 메세지 개수
		if( g_pMessageMgr->HT_bGetParameter( iID, &sIndex, &sMaxStep, &sSubIndex ) == false )
			return;

		// 퀘스트 제목
		if( g_pMessageMgr->HT_bGetMessage( iID, &strBuf ) == false )
			return;

		m_sQuestText[nArrayNo].byIndex = (byte) sIndex;	// 퀘스트 번호
		m_sQuestText[nArrayNo].szTitle = strBuf;	// 퀘스트 제목
		m_sQuestText[nArrayNo].nStepNo = sMaxStep;	// 최대 history 단계
		strBuf.HT_hrCleanUp();
		
		for ( i=0 ; i<sMaxStep ; ++i )
		{
			++iID; // 현재 퀘스트에 해당하는 history를 읽기 위해
			if( g_pMessageMgr->HT_bGetParameter( iID, &sIndex, &sMaxStep, &sSubIndex ) == false )
				return;
			if( g_pMessageMgr->HT_bGetMessage( iID, &strBuf ) == false )
				return;

			m_sQuestText[nArrayNo].nStepNum[i] = sSubIndex;	// 퀘스트 단계 번호
			// 해당하는 메세지를 읽는다.
			// 단계별 UI창에 나타내는 말
			m_sQuestText[nArrayNo].szStepMsg[i] = strBuf;
			strBuf.HT_hrCleanUp();
		}
		// 배열 인덱스 증가
		++nArrayNo;
	}	// end of for( iID = HT_MESSAGETYPE_QUESTMSG_START ; iID <= HT_MESSAGETYPE_QUESTMSG_END ; ++iID ) 
}



//
// CHTUIManager Class 맴버 함수를 모아놓았습니다.
//

CHTUIManager::CHTUIManager()
{
	bRenderNPC = false;
	m_bBackgroundPos = true;
	m_bCheckRender = true;
	m_bSlotBoxMoving = false;
	
	// 전역변수 초기화
	g_Shift = false;
	g_Control = false;
	g_Pibot = 0;
	
	m_bDrawInfoWindow = false;
	m_nSlotBoxWindowIndex = 0;	
	m_nSlotBoxControlIndex = 0;
	m_nSlotBoxTextureID = 0;
	m_nSlotBoxTargetControlIndex = 0;
	m_nSlotBoxTargetWindowIndex = 0;

	m_InputState = false;
	m_nAlphaColor = 34;

	m_bBackgroundPos = false;
	bRenderNPC = true;
	m_strMessageBoxText = "";
	
	srand( (unsigned)time( NULL ) );
	
	m_UIList.clear();
}

// 메모리 반납
CHTUIManager::~CHTUIManager()
{
	if (m_UIList.empty()) return;

	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end();)
	{
		HT_DELETE( *ZOder );
		ZOder = m_UIList.erase( ZOder );
	}

	m_UIList.clear();
}

// 윈도우를 그릴때는 최하위 ZOder 윈도우부터 그린다.
void CHTUIManager::HT_Render()
{
	if (!m_bCheckRender ) return;
	if (m_UIList.empty()) return;

	// 보통때는 모든 윈도우 랜더	
	for(std::list<UIWindow*>::reverse_iterator ZOder = m_UIList.rbegin(); ZOder != m_UIList.rend(); ++ZOder)
		(*ZOder)->Render();

	// 2차 툴팁 랜더
	for(std::list<UIWindow*>::reverse_iterator ZOder2 = m_UIList.rbegin(); ZOder2 != m_UIList.rend(); ++ZOder2)
		(*ZOder2)->Render_ToolTip();

	// NPC, 몬스터 등 특정 오브젝트 마우스 오버시 랜더
	if (bRenderNPC == true)
		g_pEngineHandler->HT_hrRenderText(UI_MAIN_FONT, strRenderNPCName.HT_szGetString(), HTvector3(iRenderNPCPos.x, iRenderNPCPos.y, iRenderNPCPos.z), HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f), HT_COLOR( 0.1f, 0.1f, 0.1f, 0.8f ), 5.0f );
}

// 랜더 상태를 킵니다.
void CHTUIManager::HT_RenderOn()
{
	m_bCheckRender = true;
}

// 랜더 상태를 끕니다.
void CHTUIManager::HT_RenderOff()
{
	m_bCheckRender = false;
}

// 윈도우 생성
void CHTUIManager::HT_CreateWindow(unsigned int nIndex, CHTString str, int iSizeX, int iSizeY, func_t* ptr, int nMode)
{
	// 먼저 해당 인덱스의 윈도우가 존재한다면 에러출력
	UIWindow* pWindowTemp = this->FindWindowPointer(nIndex);
	if (pWindowTemp != NULL)
	{
		if (g_cUIManager->m_iGameMode == 1)
		{
			CHTString str;
			str.HT_szFormat("생성된 윈도우를 다시 생성하려고 하였습니다.(Index = %d)", nIndex);
			MessageBox(NULL, str, _T("Tantra V3"), MB_OK);
		}
		return;
	}
	
	int iPosX = 0, iPosY = 0; // 위치 고정

	HT_COLOR clr;	// 배경색 지정 (nMode = 0 이면 투명)
	
	if (nMode == 0)
	{
		clr.r = 1.0f / 255.0f; clr.g = 1.0f / 255.0f; clr.b = 1.0f / 255.0f; clr.a = 0.0f / 100.0f;
	}
	else
	{
		clr.r = 1.0f / 255.0f; clr.g = 1.0f / 255.0f; clr.b = 1.0f / 255.0f; clr.a = (float)m_nAlphaColor / 100.0f;
	}

	UIWindow* pWindow = new UIWindow;
	pWindow->CreateUIWindow(nIndex, str, iPosX, iPosY, iSizeX, iSizeY, clr, ptr, nMode);
	pWindow->BackgroundMove = nMode;
	pWindow->FocusOn();					// 현재 윈도우 켜짐

	if (m_UIList.empty() == false)
		(m_UIList.front())->FocusOff();				// 최상위 윈도우 포커스 꺼짐

	m_UIList.push_front(pWindow);
}

// 윈도우 생성 (배경 컬러 지정 가능)
void CHTUIManager::HT_CreateWindow(unsigned int nIndex, CHTString str, int iSizeX, int iSizeY, func_t* ptr, int nMode, HT_COLOR clrBackground)
{
	// 먼저 해당 인덱스의 윈도우가 존재한다면 에러출력
	UIWindow* pWindowTemp = this->FindWindowPointer(nIndex);
	if (pWindowTemp != NULL)
	{
		if (g_cUIManager->m_iGameMode == 1)
		{
			CHTString str;
			str.HT_szFormat("생성된 윈도우를 다시 생성하려고 하였습니다.(Index = %d)", nIndex);
			MessageBox(NULL, str, _T("Tantra V3"), MB_OK);
		}
		return;
	}

	int iPosX = 0, iPosY = 0; // 위치 고정

	UIWindow* pWindow = new UIWindow;
	pWindow->CreateUIWindow(nIndex, str, iPosX, iPosY, iSizeX, iSizeY, clrBackground, ptr, nMode);
	pWindow->FocusOn();					// 현재 윈도우 켜짐

	if (m_UIList.empty() == false)
		(m_UIList.front())->FocusOff();				// 최상위 윈도우 포커스 꺼짐

	m_UIList.push_front(pWindow);

}

// 윈도우 제거
void CHTUIManager::HT_DeleteWindow(unsigned int nIndex)
{	
	if (m_UIList.empty()) return;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex)
		{
			HT_DELETE( *ZOder );
			m_UIList.erase( ZOder );
			break;
		} 

	if (m_UIList.empty() != true) 
		(m_UIList.front())->FocusOn();
		
	//g_cUIManager->BottomWindow(nIndex);
	//m_UIList.pop_back();
	return;
}

// 해당 윈도우의 배경색을 변경합니다.
void CHTUIManager::HT_SetBackgroundColor(unsigned int nIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) pWindow->SetBackgroundColor(clr);
}

// 해당 윈도우의 컨트롤을 생성합니다.
void CHTUIManager::HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iLayer, int iSizeX, int iSizeY)
{
	UITexture oTexture;
	HT_COLOR clr; clr.r = 1.0f; clr.g = 1.0; clr.b = 1.0f; clr.a = 1.0f;

	oTexture.Layer = iLayer;
	oTexture.PosX = iPosX;
	oTexture.PosY = iPosY;
	oTexture.SizeX = iSizeX;
	oTexture.SizeY = iSizeY;
	oTexture.TextureID = iTextureID;
	oTexture.VertexClr = clr;

	this->HT_AddTextureControl(nWindowIndex, nControlIndex, oTexture);
}

// 텍스처컨트롤을 추가합니다.
void CHTUIManager::HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, HT_COLOR clr, int iSizeX, int iSizeY, int iLayer)
{
	UITexture oTexture;
	oTexture.Layer = iLayer;
	oTexture.PosX = iPosX;
	oTexture.PosY = iPosY;
	oTexture.SizeX = iSizeX;
	oTexture.SizeY = iSizeY;
	oTexture.TextureID = iTextureID;
	oTexture.VertexClr = clr;

	this->HT_AddTextureControl(nWindowIndex, nControlIndex, oTexture);
}

// 텍스처 컨트롤의 출력 좌표를 반환합니다.
HTvector3 CHTUIManager::HT_GetTextureControlPos(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetTextureControlPos(nControlIndex);

	return NULL;
}

// 텍스처 출력 온오프 설정 (true = 온 . false = 오프)
void CHTUIManager::HT_SetTextureControlDisplay(unsigned int nWindowIndex, unsigned int nControlIndex, bool bOn)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextureControlDisplay(nControlIndex, bOn);
}


// 텍스처를 변경합니다.
void CHTUIManager::HT_SetTextureControlImage(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID )
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextureControlImage(nControlIndex, iTextureID);
}

// 텍스처컨트롤의 스케일을 변경합니다.
void CHTUIManager::HT_SetTextureControlScale(unsigned int nWindowIndex, unsigned int nControlIndex, int iSizeX, int iSizeY, int iOSizeX, int iOSizeY)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextureControlScale(nControlIndex, iSizeX ,iSizeY, iOSizeX, iOSizeY);
}

// 텍스처컨트롤의 색상을 변경합니다.
void CHTUIManager::HT_SetTextureControlColor(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextureColor(nControlIndex, clr);
}

// 해당 윈도우의 컨트롤을 생성합니다.
void CHTUIManager::HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateTextureControl(nControlIndex, oTexture);
}

// 해당 윈도우의 컨트롤을 삭제합니다.
void CHTUIManager::HT_DelTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteTextureControl(nControlIndex);
}

// 슬롯박스 아이콘 움직임 고정 여부 설정
void CHTUIManager::HT_SetSlotBoxImageFixed(unsigned int nWindowIndex, unsigned int nControlIndex, bool bFixedIcon)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxImageFixed(nControlIndex, bFixedIcon);
}

// 슬롯박스 컨트롤을 추가합니다.
void CHTUIManager::HT_AddSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateSlotBoxControl(nControlIndex, oTexture);
}

// 슬롯박스 컨트롤을 추가합니다.
void CHTUIManager::HT_AddSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iLayer, int iSizeX, int iSizeY)
{
	UITexture oTexture;
	HT_COLOR clr; clr.r = 1.0f; clr.g = 1.0; clr.b = 1.0f; clr.a = 1.0f;

	oTexture.Layer = iLayer;
	oTexture.PosX = iPosX;
	oTexture.PosY = iPosY;
	oTexture.SizeX = iSizeX;
	oTexture.SizeY = iSizeY;
	oTexture.TextureID = iTextureID;
	oTexture.VertexClr = clr;

	this->HT_AddSlotBoxControl(nWindowIndex, nControlIndex, oTexture);
}

// 슬롯박스 컨트롤이 아이콘 위치를 재설정 합니다.
void CHTUIManager::HT_SetSlotBoxControlPosImage(unsigned int nWindowIndex, unsigned int nControlIndex, int iPosX, int iPosY)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxControlPosImage(nControlIndex, iPosX, iPosY);
}

// 슬롯박스 컨트롤을 삭제합니다.
void CHTUIManager::HT_DelSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteSlotBoxControl(nControlIndex);
}

// 슬롯이미지가 어떤 윈도우 슬롯에 가있는지 조사하여 슬롯 이미지를 옮기고 처리합니다. (내부처리용)
bool CHTUIManager::CheckRegionWithSlotBoxPoint(unsigned int nWindowIndex, unsigned int nControlIndex, int iXPos, int iYPos, int iTextureID)
{
	m_nSlotBoxWindowIndex = nWindowIndex;
	m_nSlotBoxControlIndex = nControlIndex;
	m_nSlotBoxTextureID = iTextureID;

	if (m_UIList.empty()) return NULL;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->isDisplay() == true && (*ZOder)->isEnable() == true)
		if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos)) // 해당하는 위치에 있는 윈도우라면...
		{
			int nIndex = (*ZOder)->m_nIndex;
			int nTargetControlIndex = (*ZOder)->CheckRegionWithSlotBoxPoint(iXPos, iYPos, (*ZOder)->iWindowPosX, (*ZOder)->iWindowPosY);
			
			// 제자리로 옮기면 실패
			if (nIndex == nWindowIndex && nControlIndex == nTargetControlIndex)
			{
				this->HT_SetSlotImage(nWindowIndex, nControlIndex, iTextureID);
				
				func_t* ptr = (*ZOder)->GetMessageProcedure();							// 함수 포인터를 얻어온다.
				ptr(UI_ACTION_MOUSE_LCLK, UI_TARGET_SLOTBOX, nControlIndex);	// 배경에 놓았을때 본 함수에서 -1로 호출됨
				return true;
			}
				
			// 해당위치에 슬롯이 존재한다면... 
			if (nTargetControlIndex) 
			{
				// 사용자 처리를 위해 원본 정보 저장
				m_nSlotBoxTargetWindowIndex = nIndex;
				m_nSlotBoxTargetControlIndex = nTargetControlIndex;

				// 대상 윈도우 메시지프로시져 호출
				func_t* ptr = (*ZOder)->GetMessageProcedure();	// 해당 윈도우 메시지프로시져 얻기
				ptr(1, 4, nTargetControlIndex);
				return true;
			}
			else // 윈도우에 놓았다면 슬롯이 아닌 윈도우에 놓았다면 -2
			{
				m_nSlotBoxTargetWindowIndex = nWindowIndex;
				m_nSlotBoxTargetControlIndex = nControlIndex;

				UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
				if (pWindow == NULL) return false;

				func_t* ptr = pWindow->GetMessageProcedure();					// 함수 포인터를 얻어온다.
				ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SLOTBOX, -2);		// 배경에 놓았을때 본 함수에서 -1로 호출됨
				return true;
			}
		}
	// 배경에 놓았을경우는 클릭메시지에 타겟아이디 -1로 보낸다.
	m_nSlotBoxTargetWindowIndex = nWindowIndex;
	m_nSlotBoxTargetControlIndex = nControlIndex;

	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow == NULL) return false;

	func_t* ptr = pWindow->GetMessageProcedure();					// 함수 포인터를 얻어온다.
	ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_SLOTBOX, -1);		// 배경에 놓았을때 본 함수에서 -1로 호출됨
	return true;
}

// 슬롯박스의 원본 위치 정보를 얻습니다.
void CHTUIManager::HT_GetSlotBoxControlSourInfo(unsigned int &nWindowIndex, unsigned int &nControlIndex, int &TextureID)
{
	nWindowIndex = m_nSlotBoxWindowIndex;
	nControlIndex = m_nSlotBoxControlIndex;
	TextureID = m_nSlotBoxTextureID;
}

// 슬롯박스에 이미지를 붙입니다.
void CHTUIManager::HT_SetSlotImage(unsigned int nWindowIndex, unsigned int nControlIndex, int TextureID, int iLayer)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) {pWindow->SetSlotBoxControl(nControlIndex, TextureID, iLayer); return;}
}

// 슬롯박스의 이미지 옮기기 수락
void CHTUIManager::HT_AcceptSlotImageMoving()
{
	if (m_bSlotBoxMoving == true)
	{
		// 원본 위치 슬롯 비움
		this->HT_SetSlotImage(m_nSlotBoxWindowIndex, m_nSlotBoxControlIndex, 0);

		// 대상 위치 슬롯 채움
		this->HT_SetSlotImage(m_nSlotBoxTargetWindowIndex, m_nSlotBoxTargetControlIndex, m_nSlotBoxTextureID);

	}
}

// 슬롯박스의 이미지 옮기기 거절
void CHTUIManager::HT_RefuseSlotImageMoving()
{
	// 원본 위치 슬롯 비움
	this->HT_SetSlotImage(m_nSlotBoxWindowIndex, m_nSlotBoxControlIndex, m_nSlotBoxTextureID);
}

// 해당 슬롯박스에 쿨타임 가동
void CHTUIManager::HT_SetSlotBoxCoolTime(unsigned int nWindowIndex, unsigned int nControlIndex, DWORD DealyTime, DWORD PastTime)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxCoolTime(nControlIndex, DealyTime, PastTime);
}

// 해당 슬롯박스에 쿨타임 취소
void CHTUIManager::HT_SetSlotBoxCoolTimeCancel(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxCoolTimeCancel(nControlIndex);
}

// 해당 슬롯박스가 쿨타임 중인지?
bool CHTUIManager::HT_isSlotBoxCoolTime(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->isSlotBoxCoolTime(nControlIndex);
	return false;
}

// 해당 윈도우의 슬롯박스 컨트롤에서 툴팁을 킵니다.
void CHTUIManager::HT_SetSlotBoxToolTipOn(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxToolTipOn(nControlIndex);
}

// 해당 윈도우의 슬롯박스 컨트롤에서 툴팁을 끕니다.
void CHTUIManager::HT_SetSlotBoxToolTipOff(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxToolTipOff(nControlIndex);
}

// 슬롯박스 툴팁의 해당 텍스트 설정(라인별)
void CHTUIManager::HT_SetSlotBoxControlToolTipText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, CHTString str)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxControlToolTipText(nControlIndex, nIndex, str);
}

// 슬롯박스 툴팁의 해당 출력 라인 인덱스 설정 (해당 라인까지만 출력함)
void CHTUIManager::HT_SetSlotBoxControlTextIndex(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxControlTextIndex(nControlIndex, nIndex);
}

// 슬롯박스 툴팁 해당 라인 텍스트 색상 변경
void CHTUIManager::HT_SetSlotBoxControlToolTipTextColor(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxControlToolTipTextColor(nControlIndex, nIndex, clr);
}

// 슬롯박스의 사용여부 결정 (0=사용불가, 1=사용가능)
void CHTUIManager::HT_SetSlotBoxControlEnable(unsigned int nWindowIndex, unsigned int nControlIndex, bool bEnable)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetSlotBoxControlEnable(nControlIndex, bEnable);
}



// 스크롤바 컨트롤을 추가합니다.
void CHTUIManager::HT_AddScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateScrollBarControl(nControlIndex, oTImage, oTLine, oTArrow1, oTArrow2, iMaxValue, iType);
}

// 스크롤바 컨트롤을 추가합니다.
void CHTUIManager::HT_AddScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iPosX, int iPosY, int iLength, int iMaxValue, int iType, int iStyle)
{
	UITexture	oTImage, oTLine, oTArrow1[3], oTArrow2[3];
	
	switch(iStyle)
	{
		case 0: // 기본 형태 스크롤바 이미지 적용
			switch(iType)
			{
			case 0: // 새로 스크롤바
				oTImage.Layer = 1600; oTImage.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f); oTImage.TextureID = 138; oTImage.PosX = iPosX; oTImage.PosY = iPosY+16;
				oTImage.SizeX = 0; oTImage.SizeY = 0;

		
				oTArrow1[0].Layer = oTImage.Layer;	oTArrow1[0].VertexClr = oTImage.VertexClr;	oTArrow1[0].TextureID = 137; oTArrow1[0].SizeX = 0; oTArrow1[0].SizeY = 0; oTArrow1[0].PosX = iPosX; oTArrow1[0].PosY = iPosY;
				oTArrow1[0].SizeX = 0; oTArrow1[0].SizeY = 0;
				oTArrow1[2] = oTArrow1[1] = oTArrow1[0];
				oTArrow1[1].TextureID = 140;	oTArrow1[2].TextureID = 134;
				
				oTArrow2[0].Layer = oTImage.Layer;	oTArrow2[0].VertexClr = oTImage.VertexClr;	oTArrow2[0].TextureID = 136; oTArrow2[0].SizeX = 0; oTArrow2[0].SizeY = 0; oTArrow2[0].PosX = iPosX; oTArrow2[0].PosY = iPosY+iLength-16;
				oTArrow2[2] = oTArrow2[1] = oTArrow2[0];
				oTArrow2[1].TextureID = 139;	oTArrow2[2].TextureID = 133;

				oTLine.Layer = 1590; oTLine.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f); oTLine.TextureID = 1; 
				oTLine.SizeX = 0; oTLine.SizeY = 0;
				oTLine.PosX = iPosX+6; oTLine.PosY = iPosY+16; oTLine.SizeX = 3; oTLine.SizeY = iLength - 32;
				break;
			case 1: // 가로 스크롤바
				oTImage.Layer = 1600; oTImage.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f); oTImage.TextureID = 143; oTImage.PosX = iPosX+16; oTImage.PosY = iPosY;
				oTImage.SizeX = 0; oTImage.SizeY = 0;
		
				oTArrow1[0].Layer = oTImage.Layer;	oTArrow1[0].VertexClr = oTImage.VertexClr;	oTArrow1[0].TextureID = 148; oTArrow1[0].SizeX = 0; oTArrow1[0].SizeY = 0; oTArrow1[0].PosX = iPosX; oTArrow1[0].PosY = iPosY;
				oTArrow1[0].SizeX = 0; oTArrow1[0].SizeY = 0;
				oTArrow1[2] = oTArrow1[1] = oTArrow1[0];
				oTArrow1[1].TextureID = 150;	oTArrow1[2].TextureID = 149;
				
				oTArrow2[0].Layer = oTImage.Layer;	oTArrow2[0].VertexClr = oTImage.VertexClr;	oTArrow2[0].TextureID = 145; oTArrow2[0].SizeX = 0; oTArrow2[0].SizeY = 0; oTArrow2[0].PosX = iPosX+iLength-16; oTArrow2[0].PosY = iPosY;
				oTArrow2[2] = oTArrow2[1] = oTArrow2[0];
				oTArrow2[1].TextureID = 146;	oTArrow2[2].TextureID = 147;

				oTLine.Layer = 1590; oTLine.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f); oTLine.TextureID = 2; 
				oTLine.SizeX = 0; oTLine.SizeY = 0;
				oTLine.PosX = iPosX+16; oTLine.PosY = iPosY+6; oTLine.SizeX = iLength - 32; oTLine.SizeY = 3;
				break;
			}
		break;
	}

	if (iMaxValue < 0) iMaxValue = 1;
	HT_AddScrollBarControl(nWindowIndex, nControlIndex, oTImage, oTLine, oTArrow1, oTArrow2, iMaxValue, iType);
}

// 스크롤바 컨트롤에 값을 넣습니다.
void CHTUIManager::HT_SetScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iValue)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetScrollBarValue(nControlIndex, iValue);
}

// 스크롤바 컨트롤에 최대 값을 변경 합니다.
void CHTUIManager::HT_SetScrollBarControlMaxValue(unsigned int nWindowIndex, unsigned int nControlIndex, int iValue)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetScrollBarMaxValue(nControlIndex, iValue);
}

// 스크롤바 컨트롤의 값을 가지고 옵니다.
int CHTUIManager::HT_GetScrollBarValue(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetScrollBarValue(nControlIndex);
	return 0;
}

// 스크롤바 컨트롤을 삭제합니다.
void CHTUIManager::HT_DelScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteScrollBarControl(nControlIndex);
}

// 타이머 컨트롤을 생성합니다.
void CHTUIManager::HT_AddTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex, DWORD dwSetTime, int iStyle)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateTimerControl(nControlIndex, dwSetTime, iStyle);
}

// 타이머 컨트롤을 제거합니다.
void CHTUIManager::HT_DelTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteTimerControl(nControlIndex);
}

// 타이머 컨트롤을 온합니다.
void CHTUIManager::HT_EnableOnTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->EnableOnTimerControl(nControlIndex);
}

// 타이머 컨트롤 오프합니다.
void CHTUIManager::HT_EnableOffTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->EnableOffTimerControl(nControlIndex);
}

// 해당 윈도우의 컨트롤을 생성합니다. (라벨)
void CHTUIManager::HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str, int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY)
{
	UIText oText;
	oText.Font = UI_MAIN_FONT; oText.FontMode = iFontMode; oText.strTitle = str; 
	oText.TextColor = clr; 
	oText.TextShadowColor = sclr;

	oText.TextPos.left = iPosX;
	oText.TextPos.top = iPosY;
	oText.TextPos.right = iSizeX;
	oText.TextPos.bottom = iSizeY;

	this->HT_AddLabelControl(nWindowIndex, nControlIndex, oText);
}

// 해당 윈도우의 컨트롤을 생성합니다. (라벨)
void CHTUIManager::HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iStringNo, int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY)
{
	CHTString strMessage;
	g_cUIManager->HT_SetScriptMessage( iStringNo, &strMessage, _T(""), _T("") );	//	확인

	UIText oText;
	oText.Font = UI_MAIN_FONT; oText.FontMode = iFontMode; oText.strTitle = strMessage; 
	oText.TextColor = clr; 
	oText.TextShadowColor = sclr;

	oText.TextPos.left = iPosX;
	oText.TextPos.top = iPosY;
	oText.TextPos.right = iSizeX;
	oText.TextPos.bottom = iSizeY;

	this->HT_AddLabelControl(nWindowIndex, nControlIndex, oText);
}

// 해당 윈도우의 컨트롤을 생성합니다. (라벨)
void CHTUIManager::HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, UIText oText)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateLabelControl(nControlIndex, oText);
}

// 해당 윈도우의 컨트롤을 삭제합니다. (라벨)
void CHTUIManager::HT_DelLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteLabelControl(nControlIndex);
}

// 해당 윈도우의 컨트롤 정보를 변경합니다. (라벨)
void CHTUIManager::HT_SetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextLabelControl(nControlIndex, str);
}

// 해당 윈도우의 컨트롤 정보를 변경합니다. (라벨)
void CHTUIManager::HT_SetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int strindex)
{
	CHTString str; 
	g_pMessageMgr->HT_bGetMessage( strindex, &str );

	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextLabelControl(nControlIndex, str);
}

// 해당 윈도우의 컨트를 텍스트를 원하는 방향으로 배치합니다. (라벨)
void CHTUIManager::HT_SetArrangementLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iDirection)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetArrangementLabelControl(nControlIndex, iDirection);
}

// 해당 윈도우의 라벨 컨트롤을 원하는 색상으로 변경합니다. (라벨)
void CHTUIManager::HT_SetTextColorLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextColorLabelControl(nControlIndex, clr);
}

// 해당 윈도우의 라벨 컨트롤을 원하는 그림자 색상으로 변경합니다. (라벨)
void CHTUIManager::HT_SetTextShadowColorLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextShadowColorLabelControl(nControlIndex, clr);
}

// 해당 윈도우의 라벨 컨트롤의 문자를 얻어옵니다. (라벨)
CHTString CHTUIManager::HT_GetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetTextLabelControl(nControlIndex);

	CHTString str = ""; return str;
}


// 해당 윈도우의 컨트롤을 생성합니다. (롱라벨)
void CHTUIManager::HT_AddLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HTtchar str[], int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY)
{
	UILongText oText;
	oText.Font = UI_MAIN_FONT; oText.FontMode = iFontMode; 
	strcpy(oText.strTitle, str); 
	oText.TextColor = clr; 
	oText.TextShadowColor = sclr;

	oText.TextPos.left = iPosX;
	oText.TextPos.top = iPosY;
	oText.TextPos.right = iSizeX;
	oText.TextPos.bottom = iSizeY;

	this->HT_AddLongLabelControl(nWindowIndex, nControlIndex, oText);
}

// 해당 윈도우의 컨트롤을 생성합니다. (롱라벨)
void CHTUIManager::HT_AddLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, UILongText oText)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateLongLabelControl(nControlIndex, oText);
}

// 해당 윈도우의 컨트롤을 삭제합니다. (롱라벨)
void CHTUIManager::HT_DelLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteLongLabelControl(nControlIndex);
}

// 해당 윈도우의 컨트롤 정보를 변경합니다. (롱라벨)
void CHTUIManager::HT_SetTextLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HTtchar str[])
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextLongLabelControl(nControlIndex, str);
}

// 해당 윈도우의 컨트를 텍스트를 원하는 방향으로 배치합니다. (롱라벨)
void CHTUIManager::HT_SetArrangementLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iDirection)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetArrangementLongLabelControl(nControlIndex, iDirection);
}

// 해당 윈도우의 롱라벨 컨트롤을 원하는 색상으로 변경합니다. (롱라벨)
void CHTUIManager::HT_SetTextColorLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextColorLongLabelControl(nControlIndex, clr);
}

// 해당 윈도우의 롱라벨 컨트롤을 원하는 그림자 색상으로 변경합니다. (롱라벨)
void CHTUIManager::HT_SetTextShadowColorLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextShadowColorLongLabelControl(nControlIndex, clr);
}

// 해당 윈도우의 롱라벨 컨트롤의 문자를 얻어옵니다. (롱라벨)
HTtchar* CHTUIManager::HT_GetTextLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetTextLongLabelControl(nControlIndex);

	return NULL;
}

// 해당 윈도우의 컨트롤을 생성합니다. (에디터 박스)
void CHTUIManager::HT_AddEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iSizeX, int iSizeY, int iStyle, int iLayer)
{
	UITexture	oTexture;
	UIText		oText;
	HT_COLOR clr; clr.r = 1.0f; clr.g = 1.0; clr.b = 1.0f; clr.a = 1.0f;

	oTexture.Layer = iLayer;
	oTexture.PosX = iPosX;
	oTexture.PosY = iPosY;
	oTexture.SizeX = iSizeX;
	oTexture.SizeY = iSizeY;
	oTexture.TextureID = iTextureID;
	oTexture.VertexClr = clr;

	// 만약 TextureID가 0이면 투명한 에디터 박스를 생성한다.
	if (iTextureID == 0)
	{
		oTexture.TextureID = 0;
		oTexture.VertexClr = HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f);
	}
	
	// 출력할 사이즈값을 제대로 입력하지 않으면, 사이즈는 원본과 동일하게 설정된다.
	if (iSizeX <= 0 || iSizeY <= 0)	
	{
		iSizeX = g_oUIResource[iTextureID].RealSizeX;
		iSizeY = g_oUIResource[iTextureID].RealSizeY;

		// 단 ID = 0 일 경우에는 임시로 길이 정해줌 (버그 코딩을 막기 위해)
		if (oTexture.TextureID == 0 )
		{
			iSizeX = 120;
			iSizeY = 15;
		}

		if (oTexture.TextureID >= 20000)
		{
			iSizeX = 32;
			iSizeY = 32;
		}
	}

	oText.Font = UI_MAIN_FONT;
	oText.FontMode = 4;
	oText.strTitle = "";
	oText.TextColor = clr;
	oText.TextShadowColor = clr;
	oText.TextPos.left = iPosX;
	oText.TextPos.right = iSizeX;
	oText.TextPos.top = iPosY;
	oText.TextPos.bottom = iSizeY;

	this->HT_AddEditBoxControl(nWindowIndex, nControlIndex, oTexture, oText, iStyle);
}

// 해당 윈도우의 컨트롤을 생성합니다. (에디터박스)
void CHTUIManager::HT_AddEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture, UIText oText, int iStyle)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateEditBoxControl(nControlIndex, oTexture, oText, iStyle);
}

// 해당 윈도우의 컨트롤을 삭제합니다. (에디터박스)
void CHTUIManager::HT_DelEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteEditBoxControl(nControlIndex);
}

// 해당 윈두의 컨트롤 모드를 변경합니다. (에디터박스)
void CHTUIManager::HT_SetModeEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iMode)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) 
	{
		pWindow->SetEditBoxControlMode(nControlIndex, iMode);

		if (iMode == 2)		// 숫자 입력(콤마) 모드일 경우 예외처리
		{
			g_cUIManager->HT_SetEditBoxControlLimitText(nWindowIndex, nControlIndex, 10);//fors_debug 藤속풀�龜瀕캔慢�10E	// 억단위까지만 입력받음
			g_cUIManager->HT_SetTextEditBoxControl(nWindowIndex, nControlIndex, "");	// 처음값은 0으로 셋팅
		}
	}
}

// 해당 윈도우의 컨트롤 정보를 변경합니다. (에디터박스)
void CHTUIManager::HT_SetTextEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetTextEditBoxControl(nControlIndex, str);
}

// 해당 윈도우의 컨트롤 정보를 변경합니다. (에디터박스)
CHTString CHTUIManager::HT_GetTextEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetTextEditBoxControl(nControlIndex);
	return NULL;
}

// 해당 윈도우의 컨트롤 포커스를 오프합니다. (에디터박스)
void CHTUIManager::HT_FocusOffEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) 
	{	
		return pWindow->EditBoxFocusOff(nControlIndex);
	}
}

// 해당 윈도우의 컨트롤 포커스를 온합니다. (에디터박스)
void CHTUIManager::HT_FocusOnEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) 
	{
		return pWindow->EditBoxFocusOn(nControlIndex);
	}
}

// 해당 윈도우의 컨트롤 포커스활성화시 지정한 입력모드 상태를 변경하여 적용되도록 합니다.
void CHTUIManager::HT_SetEditBoxFocusOnIME(unsigned int nWindowIndex, unsigned int nControlIndex, int iIME)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) 
	{
		pWindow->SetEditBoxFocusOnIME(nControlIndex, iIME);
		return;
	}
}

// 해당 윈도우의 컨트롤에서 입력길이를 제한합니다. (에디터박스)
void CHTUIManager::HT_SetEditBoxControlLimitText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int uiSize)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->SetEditBoxControlLimitText(nControlIndex, uiSize);
}

// 해당 윈도우의 컨트롤 포커스 여부를 반환합니다. (에디터박스)
bool CHTUIManager::HT_isFocusOnEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->isEditBoxFocusOn(nControlIndex);
	return false;
}

// 해당 윈도우의 컨트롤을 생성합니다. (버튼)
void CHTUIManager::HT_AddButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iTextureID2, int iTextureID3, int iLayer, int iSizeX, int iSizeY)
{
	UITexture oTexture[3];
	oTexture[0].Layer = iLayer;
	oTexture[0].PosX = iPosX;
	oTexture[0].PosY = iPosY;
	oTexture[0].SizeX = iSizeX;
	oTexture[0].SizeY = iSizeY;
	oTexture[0].TextureID = iTextureID;

	HT_COLOR clr; 
	if (iTextureID == 0) // 만약 ID를 0으로 하면 투명한 버튼이 생성되게 한다.
	{
		clr.r = 1.0f; clr.g = 1.0; clr.b = 1.0f; clr.a = 0.0f;
	}
	else
	{
		clr.r = 1.0f; clr.g = 1.0; clr.b = 1.0f; clr.a = 1.0f;
	}
	oTexture[0].VertexClr = clr;

	oTexture[2] = oTexture[1] = oTexture[0];
	if (iTextureID2) oTexture[1].TextureID = iTextureID2;
	if (iTextureID3) oTexture[2].TextureID = iTextureID3;

	this->HT_AddButtonControl(nWindowIndex, nControlIndex, oTexture);
}

// 해당 윈도우의 버튼 컨트롤에서 툴팁 내용을 변경합니다.
void CHTUIManager::HT_SetButtonToolTip(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonToolTip(nControlIndex, str);
}

// 해당 윈도우의 컨트롤을 생성합니다. (버튼)
void CHTUIManager::HT_AddButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture[3])
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateButtonControl(nControlIndex, oTexture);
}

// 해당 윈도우의 컨트롤을 삭제합니다. (버튼)
void CHTUIManager::HT_DelButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteButtonControl(nControlIndex);
}

// 버튼 활성화 설정
void CHTUIManager::HT_SetButtonEnable(unsigned int nWindowIndex, unsigned int nControlIndex, bool bEnable)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonEnable(nControlIndex, bEnable);
}

// 해당 버튼의 엔터기능을 킵니다.
void CHTUIManager::HT_SetButtonEnterOn(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonEnterOn(nControlIndex);
}

// 해당 버튼의 엔터기능을 끕니다.
void CHTUIManager::HT_SetButtonEnterOff(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonEnterOff(nControlIndex);
}

// 해당 윈도우의 버튼 컨트롤에서 툴팁을 킵니다.
void CHTUIManager::HT_SetButtonToolTipOn(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonToolTipOn(nControlIndex);
}

// 해당 윈도우의 버튼 컨트롤에서 툴팁을 끕니다.
void CHTUIManager::HT_SetButtonToolTipOff(unsigned int nWindowIndex, unsigned int nControlIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonToolTipOff(nControlIndex);
}

// 해당 윈도우의 버튼 컨트롤에서 상태를 변경합니다.
void CHTUIManager::HT_SetButtonControlState(unsigned int nWindowIndex, unsigned int nControlIndex, int iSetNo)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonControlState(nControlIndex, iSetNo);
}

// 버튼 툴팁의 해당 텍스트 설정(라인별)
void CHTUIManager::HT_SetButtonControlToolTipText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, CHTString str)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonControlToolTipText(nControlIndex, nIndex, str);
}

// 버튼 툴팁의 해당 출력 라인 인덱스 설정 (해당 라인까지만 출력함)
void CHTUIManager::HT_SetButtonControlTextIndex(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonControlTextIndex(nControlIndex, nIndex);
}

// 버튼 툴팁 해당 라인 텍스트 색상 변경
void CHTUIManager::HT_SetButtonControlToolTipTextColor(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetButtonControlToolTipTextColor(nControlIndex, nIndex, clr);
}

// 체크박스를 생성합니다.
void CHTUIManager::HT_AddCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex, int XPos, int YPos, bool bValue, int BorderTextureID, int CheckTextureID, int SizeX, int SizeY)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->CreateCheckBoxControl(nIndex, XPos, YPos, bValue, BorderTextureID, CheckTextureID, SizeX, SizeY);
}	

// 컨트롤을 삭제합니다.
void CHTUIManager::HT_DelCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->DeleteCheckBoxControl(nIndex);
}

// 체크박스에 값을 설정
void CHTUIManager::HT_SetCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex, bool bCheck)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetCheckBoxControl(nIndex, bCheck);
}

// 체크박스의 값을 얻음
bool CHTUIManager::HT_GetCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetCheckBoxControl(nIndex);
	return NULL;
}


// 최상위 윈도우 삭제
bool CHTUIManager::HT_CloseWindow()
{
	if (m_UIList.empty()) return false;
	
	// 정해진 몇개의 윈도우를 제외한 나머지 윈도우 순서대로 닫음
	if (g_cUIManager->HT_isShowWindow(_DIALOG_DEATHMSG+999) == true) // 저장 지역에서 다시 부활창이 떠있다면 숨기면 안된다.
		g_cUIManager->HT_ShowWindow(_DIALOG_DEATHMSG+999);
	
	// 몇몇의 윈도우들은 닫혀지면 안되는 것들
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
	{
		if ((*ZOder)->m_nIndex == _DIALOG_CHATTINGBOX || (*ZOder)->m_nIndex == _DIALOG_MAINBAR ||
			(*ZOder)->m_nIndex == _DIALOG_MAINCHARHP ||	(*ZOder)->m_nIndex == _DIALOG_HQUICKSLOT ||
			(*ZOder)->m_nIndex == _DIALOG_WQUICKSLOT || (*ZOder)->m_nIndex == _DIALOG_PRANABAR || 
			(*ZOder)->m_nIndex == _DIALOG_PARTYWND || (*ZOder)->m_nIndex == _DIALOG_OPENMESSAGE ||
			(*ZOder)->m_nIndex == _DIALOG_DISCONNECTSERVER || (*ZOder)->m_nIndex == _DIALOG_DEATHMSGFOTRESS ||
			(*ZOder)->m_nIndex == _DIALOG_DEATHMSG || (*ZOder)->m_nIndex == _DIALOG_REVIVEWND ||
			(*ZOder)->m_nIndex == _DIALOG_ANSWERUSESAMUDABA || (*ZOder)->m_nIndex == _DIALOG_BUFFSKILL ||
			(*ZOder)->m_nIndex == _DIALOG_INDIVIDUALWND1 || (*ZOder)->m_nIndex == _DIALOG_WEBBROWSER || 
			(*ZOder)->m_nIndex == _DIALOG_MINIMAINBAR || (*ZOder)->m_nIndex == _DIALOG_CHATTING2BOX ||
			(*ZOder)->m_nIndex == _DIALOG_CHATTING3BOX || (*ZOder)->m_nIndex == _DIALOG_INDIVIDUALWND1 ||
			(*ZOder)->m_nIndex == _DIALOG_INDIVIDUALWND2 || (*ZOder)->m_nIndex == _DIALOG_TRADEWND || 
			(*ZOder)->m_nIndex >= 999 )
		{
			continue;
		}
		else
		{
			// 그외의 윈도우중 다음과 같은 창들은 HideWindow 함수로 닫으면 안된다. 다음과 같은 닫기 함수들을 사용할것
			if (g_cUIManager->HT_isShowWindow((*ZOder)->m_nIndex) == true)
			{
				if ( (*ZOder)->m_nIndex == _DIALOG_MINIMAPSMALL || (*ZOder)->m_nIndex == _DIALOG_MINIMAPBIG )
				{
					g_cMiniMap->HT_vMiniMap_ESC_CloseWindow();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_NPCWINDOW)
				{
					g_cNPCControl->HT_vNPCControl_DialogWin_AntiActive();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_EQUPINVENTORY || (*ZOder)->m_nIndex == _DIALOG_INVENTORY2 )
				{
					g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_COMMANDWND)
				{
					g_cCommand->HT_vCommand_WndActiveSw();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_SKILL)
				{
					g_cSkillInventory->HT_vSkillInventoryActiveCheck( 0x00 );
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_QUEST)
				{
					g_cQuest->HT_vQuest_ActiveSw();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_CHATROOM)	// 대기실이라면 접속 종료
				{
					g_cChatRoom->HT_vChatRoom_WindowHide();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_CHATROOM_CREATE)	// 방생성창에서 ESC 누름시 자동 갱신
				{
					g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomListRequest();
					g_cUIManager->HT_HideWindow((*ZOder)->m_nIndex);
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_CHATROOM_MSG) // 채팅방이라면 고아웃 요청
				{
					g_cChatRoom->HT_vNetWork_CSP_Req_ChatRoomGoout();
				}
				else if ( (*ZOder)->m_nIndex == _DIALOG_REFINE)	// 제련창도 다음의 함수로 닫는다.
				{
					g_cUIRefineWindow->HT_vRefineWindow_WindowHide();
				}
				else
				{
					// 그외 나머지 함수들은 닫는다.
					g_cUIManager->HT_HideWindow((*ZOder)->m_nIndex);
				}

				return true;
			}
		}
	}
	return false;
}

// 마우스 L버튼 다운 처리
bool CHTUIManager::OnLButtonDown(int iXPos, int iYPos)
{
	// 먼저 탑윈도우를 조사하고 없으면 그 외의 윈도우 조사
	if (m_UIList.empty()) return false;
	
	if ((m_UIList.front())->isDisplay() == true && (m_UIList.front())->CheckRegionWithPoint(iXPos, iYPos))	
	{
		if ((m_UIList.front())->OnLButtonDown(iXPos, iYPos))
		{
			(m_UIList.front())->FocusOn();
			return true;
		}
	}
	else
	{
		// 만약 다른 윈도우가 포커스가 잡힌다면 탑윈도우의 에디터박스 컨트롤은 모두 포커스가 꺼진다.
		(m_UIList.front())->EditBoxFocusAllOff();

		for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
			if ((*ZOder)->isDisplay() == true && (*ZOder)->isEnable() == true)
				if ((*ZOder)->OnLButtonDown(iXPos, iYPos))
				{
					int tindex = (*ZOder)->m_nIndex;
					int tindex2 = (m_UIList.front())->m_nIndex;

					// 처리될 윈도우가 탑이 아니라면 탑으로 이동시킨다.
					if ((*ZOder)->m_nIndex != (m_UIList.front())->m_nIndex) 
						this->TopWindow((*ZOder)->m_nIndex);
					
					return true;
				}
		// 바탕화면 클릭시 포커스 잃음
		(m_UIList.front())->FocusOff();
	}
	return false;
}

// 마우스 L버튼 업 처리
bool CHTUIManager::OnLButtonUp(int iXPos, int iYPos)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnLButtonUp(iXPos, iYPos))	return true;
	return false;
}

// 마우스 R버튼 다운
bool CHTUIManager::OnRButtonDown(int iXPos, int iYPos)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->CheckRegionWithPoint(iXPos, iYPos) )
	{
		if ((m_UIList.front())->OnRButtonDown(iXPos, iYPos))
		{
			(m_UIList.front())->FocusOn();
			return false;
		}
	}
	else
	{
		// 만약 다른 윈도우가 포커스가 잡힌다면 탑윈도우의 에디터박스 컨트롤은 모두 포커스가 꺼진다.
		(m_UIList.front())->EditBoxFocusAllOff();

		for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
			if ((*ZOder)->isDisplay() == true && (*ZOder)->isEnable() == true)
				if ((*ZOder)->OnRButtonDown(iXPos, iYPos))
				{
					// 처리될 윈도우가 탑이 아니라면 탑으로 이동시킨다.
					if ((*ZOder)->m_nIndex != (m_UIList.front())->m_nIndex) 
						this->TopWindow((*ZOder)->m_nIndex);

					return false;
				}
		// 바탕화면 클릭시 포커스 잃음
		(m_UIList.front())->FocusOff();
	}
	return false;
}

// 마우스 R버튼 업
bool CHTUIManager::OnRButtonUp(int iXPos, int iYPos)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnRButtonUp(iXPos, iYPos))	return true;
	return false;
}

// 키보드 다운
bool CHTUIManager::OnKeyDown(WPARAM wParam)
{
	// 우선 활성화 윈도우에 대해 처리합니다.
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true)
		if ((m_UIList.front())->OnKeyDown(wParam))	
			return true;

	// 전역 키다운 처리 부분 (공통적으로 적용될 키처리 부분을 이곳에 코딩합니다.)
	switch(wParam)
	{
		//case 'l': case 'L':	// Status 창 토글
		//	if ( g_cUIManager->HT_isShowWindow( 101 ) ) 
		//		g_cUIManager->HT_HideWindow( 101 ); 
		//	else 
		//		g_cUIManager->HT_ShowWindow( 101 );
		//	break;
		//case 'k': case 'K': // Skill 창 토글
		//	break;
	case VK_TAB:
		if (g_cGameSystem)	// 메인으로 들어갔을때에만 처리됨
		{

			if ( g_cUIManager->HT_isRenderOn() ) 
				g_cUIManager->HT_RenderOff(); 
			else 
				g_cUIManager->HT_RenderOn();
		}
			break;
		//case '2':
		//	g_cUIManager->HT_SetSlotBoxCoolTime(1, 1, 3200);
		//	break;
		//case '3':
		//	g_cUIManager->HT_SetSlotBoxCoolTimeCancel(1, 1);
		//	break;
		case VK_RETURN: // 채팅창의 경우 두번째 입력창이 활성화 되어 있지 않을 경우에만 활성화 시킨다.
		{
			HTint iChatDlgNo = 0;
			if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATTINGBOX ))		iChatDlgNo = _DIALOG_CHATTINGBOX;
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATTING2BOX ))	iChatDlgNo = _DIALOG_CHATTING2BOX;
			else if( g_cUIManager->HT_isShowWindow( _DIALOG_CHATTING3BOX ))	iChatDlgNo = _DIALOG_CHATTING3BOX;

			if (g_cUIManager->HT_isShowWindow(iChatDlgNo) == true)
			if (g_cUIManager->HT_isFocusOnEditBoxControl(iChatDlgNo, 2) == false)
			{
				//g_cUIManager->HT_ShowWindow( iChatDlgNo ); // 활성화 윈도우로 설정
				g_EditBoxFocusWindow = iChatDlgNo;
				g_EditBoxFocusControl = 2;

				g_cChatting->HT_vChatting_SetFocusOn();
				return true;
			}
		}
	}

	//g_cInterfaceCheck->HT_hrInterfaceKeyboard_Input_KeyDown( wParam );

	// 해당사항없다면 다음 처리함수로 넘김
	return false;
}

// 현재 윈도우가 출력 상태인가?
bool CHTUIManager::HT_isShowWindow(unsigned int nIndex)
{
	if (m_UIList.empty()) return false;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex )
			if ((*ZOder)->isDisplay() == true )
				return true;
			else
				return false;

	return false;
}


// 키보드 업
bool CHTUIManager::OnKeyUp(WPARAM wParam)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnKeyUp(wParam)) 
			return true;
	return false;
}

// 키보드 문자 받음
bool CHTUIManager::OnChar(WPARAM wParam)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnChar(wParam)) 
			return true;
	return false;
}

// 마우스 휠 처리
bool CHTUIManager::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnMouseWheel(wParam)) 
			return true;
	return false;
}


// 윈도우 명령 메시지 처리
bool CHTUIManager::OnSysCommand(WPARAM wParam)
{
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		if ((m_UIList.front())->OnSysCommand(wParam)) 
			return true;
	return false;
}


// 마우스 다운 무브 처리
bool CHTUIManager::OnMouseMove(int iXPos, int iYPos)
{
	m_MousePosX = iXPos;
	m_MousePosY = iYPos;

	// Step 1) 윈도우가 없다면 무조건 전역 마우스 무브 처리로 넘긴다.
	if (m_UIList.empty()) return false;
	if ( (m_UIList.front())->isDisplay() == true && (m_UIList.front())->isEnable() == true )
		(m_UIList.front())->OnMouseMoveOnlyTop(iXPos, iYPos);

	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->isDisplay() == true)
			(*ZOder)->OnMouseMove(iXPos, iYPos);

	return false;
}

// 해당 ID로 XMLID와 RealSize 정보를 등록합니다.
void CHTUIManager::RegisterTextureID(unsigned int nIndex, int XMLID, int RealSizeX, int RealSizeY)
{
	g_oUIResource[nIndex].RealSizeX = RealSizeX;
	g_oUIResource[nIndex].RealSizeY = RealSizeY;
	g_oUIResource[nIndex].XMLID = XMLID;
}

// 해당 윈도우를 찾아 윈도우 포인터를 반환해줍니다.
UIWindow* CHTUIManager::FindWindowPointer(unsigned int nIndex)
{
	if (m_UIList.empty()) return NULL;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex) 
			return (*ZOder);
	return NULL;
}

// 해당 윈도우를 찾아 윈도우 포인터를 반환해줍니다.
void CHTUIManager::HT_SetWindowBackgroundColor(unsigned int nIndex)
{
	HT_COLOR clr;

	if (m_UIList.empty()) return;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
	{
		// 다음의 윈도우들은 변화 없음
		if ((*ZOder)->m_nIndex == _DIALOG_MINIMAPSMALL || (*ZOder)->m_nIndex == _DIALOG_MINIMAPBIG)
		{
			clr.r = 1.0f / 255.0f; 
			clr.g = 1.0f / 255.0f; 
			clr.b = 1.0f / 255.0f; 
			clr.a = 10.0f / 100.0f;

			(*ZOder)->Body->SetColor(clr);
		}
		else if ((*ZOder)->BackgroundMove != 0)
		{
			clr.r = 1.0f / 255.0f; 
			clr.g = 1.0f / 255.0f; 
			clr.b = 1.0f / 255.0f; 
			clr.a = (float)nIndex / 100.0f;

			(*ZOder)->Body->SetColor(clr);
		}
	}

	g_cUIManager->HT_SetTextureControlColor( _DIALOG_CHATTINGBOX, 51, clr);
	g_cUIManager->HT_SetTextureControlColor( _DIALOG_CHATTING3BOX, 52, clr);

}

// 해당 윈도우를 탑(가장 앞의 윈도우)으로 보냅니다.
void CHTUIManager::TopWindow(unsigned int nIndex)
{
	if (m_UIList.empty()) return;

	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex) 
		{
			if ((*ZOder) != (m_UIList.front()))	 // 만약 다른 윈도우가 탑이 된다면 원래 탑윈도우의 에디터박스 컨트롤은 모두 포커스가 꺼진다.
				(m_UIList.front())->EditBoxFocusAllOff();

			(m_UIList.front())->FocusOff();			// 최상위 윈도우 포커스 꺼짐
			(*ZOder)->FocusOn();					// 현재 윈도우 켜짐
			m_UIList.push_front(*ZOder);			// 최상위 윈도우에 삽입
			m_UIList.erase(ZOder);					// 기존 위치에 있던 윈도우는 제거

			return;									
		}
}

// 해당 윈도우를 보텀(가장 뒤의 윈도우)으로 보냅니다.
void CHTUIManager::BottomWindow(unsigned int nIndex)
{
	if (m_UIList.empty()) return;

	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex == nIndex) 
		{
			if ((*ZOder) == (m_UIList.front()))	 // 만약 탑 윈도우가 아래로 내려간다면 탑윈도우의 에디터박스 컨트롤은 모두 포커스가 꺼진다.
				(m_UIList.front())->EditBoxFocusAllOff();

			(*ZOder)->FocusOff();					// 현재 윈도우 꺼짐
			m_UIList.push_back(*ZOder);				// 최하위 윈도우에 삽입
			m_UIList.erase(ZOder);					// 기존 위치에 있던 윈도우는 제거
			//(m_UIList.front())->FocusOn();			// 최상위 윈도우 포커스 켜짐
	
			return;									
		}
}

// 해당 윈도우를 원하는 위치로 이동시킵니다.
void CHTUIManager::HT_MoveWindow(unsigned int nIndex, int iPosX, int iPosY, int iType)	// iType = 0 이면 고정이동, 1이면 현재 위치에서 추가이동
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) 
	{
		if (iType == 0 )	// 일반 타입 (0)의 경우라면 요청된 위치로 이동
		{
			//pWindow->m_posX = iPosX;
			//pWindow->m_posY = iPosY;
			pWindow->MoveWindow(iPosX, iPosY);
		}
		else	// 그렇지 않다면 현재 위치에서 추가 이동
		{
			HTvector3 pos;
			pos = pWindow->GetWindowPos();
			//pWindow->m_posX = (int)pos.x + iPosX;
			//pWindow->m_posY = (int)pos.y + iPosY;
			pWindow->MoveWindow((int)pos.x + iPosX, (int)pos.y + iPosY);
		}
	}

}

// 해당 윈도우의 위치값을 얻어옵니다.
void CHTUIManager::HT_GetWindowPos(unsigned int nIndex, int &PosX, int &PosY)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL)
	{
		HTvector3 pos = pWindow->GetWindowPos();
		PosX = (int)pos.x;
		PosY = (int)pos.y;
	}
}

// 해당 윈도우의 사이즈를 얻어옵니다.
HTvector3 CHTUIManager::HT_GetWindowSize(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) return pWindow->GetWindowSize();
	
	HTvector3 pos;
	pos.x = 0; pos.y = 0;
	return pos;
}

// 해당 윈도우를 보여줍니다.
void CHTUIManager::HT_ShowWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) 
	{
		pWindow->Show();
		this->TopWindow(nIndex);
	}
}

// 해당 윈도우를 숨깁니다.
void CHTUIManager::HT_HideWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) 
	{
		// 닫기 전에 메시지 박스가 띄어져 있다면 메시지박스도 닫아준다.
		if (g_cUIManager->HT_isShowWindow(UI_WINDOW_MESSAGEBOX + nIndex) == true)
		{
			g_cUIManager->HT_FocusOffEditBoxControl(nIndex, 1); 
			g_cUIManager->HT_EnableOnWindow(nIndex);
			g_cUIManager->HT_DeleteWindow(nIndex+UI_WINDOW_MESSAGEBOX);
		}

		if (m_bSlotBoxMoving == true)	// 슬롯 이동중이라면 원위치로 재설정
		{
			pWindow->CancelSlotBoxImageMoving();
		}

		pWindow->Hide();
		this->BottomWindow(nIndex);
	}
}


// 슬롯 아이콘 무빙중일때 원래상태로 되돌립니다.
void CHTUIManager::HT_CancelSlotBoxImageMoving()
{
	if (m_UIList.empty()) return;
	if (m_bSlotBoxMoving == true)	
		for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		{
			m_bSlotBoxMoving = false;
			(*ZOder)->CancelSlotBoxImageMoving();
		}
}

// 해당 윈도우를 동작하게 합니다.
void CHTUIManager::HT_EnableOnWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) 
	{
		pWindow->EnableOn(); 
		pWindow->FocusOn();
	}
}

// 해당 윈도우를 동작하지 않게 합니다.
void CHTUIManager::HT_EnableOffWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) 
	{
		pWindow->EnableOff();
		pWindow->FocusOff();
	}
}


// 해당 윈도우의 포커스를 킵니다.
void CHTUIManager::HT_FocusOnWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) pWindow->FocusOn();
}

// 해당 윈도우를 포커스를 끕니다.
void CHTUIManager::HT_FocusOffWindow(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) pWindow->FocusOff();
}


// 해당 방향으로 윈도우를 이동 시킵니다.
void CHTUIManager::HT_WindowArrangement(unsigned int nIndex, int iDirection)
{
	HTvector3	Pos;
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) Pos = pWindow->GetWindowSize();

	int iXpos;	// X 축 계산
	switch (iDirection)
	{
	case 1:	case 4:	case 7:	iXpos = 0;	break;
	case 2:	case 5: case 8:	iXpos = (m_iScreenX - (int) Pos.x) / 2;	break;
	case 3:	case 6:	case 9:	iXpos = (m_iScreenX - (int) Pos.x);	break;
	}

	int iYpos;	// Y 축 계산
	switch (iDirection)
	{
	case 7:	case 8:	case 9:	iYpos = 0; break;
	case 4: case 5: case 6:	iYpos = (m_iScreenY - (int) Pos.y) / 2;	break;
	case 1:	case 2:	case 3:	iYpos = (m_iScreenY - (int) Pos.y);	break;
	}
	
	//pWindow->m_posX = iXpos;
	//pWindow->m_posY = iYpos;
	pWindow->MoveWindow(iXpos, iYpos);
}

// 채팅창에 시스템 알림 메시지를 뿌려준다.
void CHTUIManager::ChattingNotify(int iMessageID)
{
	CHTString strTemp; 
	HT_g_Script_SetMessage( iMessageID, &strTemp, _T("") );		

	if (g_BasicLoadingInfo)
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
}

// 해당 윈도우로 부터 메시지 박스를 띄웁니다. 
void CHTUIManager::HT_MessageBox(unsigned int nWindowIndex, CHTString str, int nStyle)
{
	UIMessageBoxMgr.HT_vMessageBox(nWindowIndex, str, nStyle);
}

// 해당 윈도우로 부터 메시지 박스를 띄웁니다. 
void CHTUIManager::HT_MessageBox(unsigned int nWindowIndex, int index, int nStyle)
{
	CHTString str; g_pMessageMgr->HT_bGetMessage( index, &str );
	UIMessageBoxMgr.HT_vMessageBox(nWindowIndex, str, nStyle);
}

// 메시지 박스가 팝업되어 있는지 조사
bool CHTUIManager::HT_isShowMessageBox()
{
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->m_nIndex >= UI_WINDOW_MESSAGEBOX && (*ZOder)->isDisplay() == true)
			return true;
	return false;
}

// 메시지박스를 통한 함수 호출
void CHTUIManager::HT_CallMessageBoxFunction(unsigned int nWindowIndex, int iTargetID)
{
	// 먼저 할당된 메시지박스는 제거하여 추가처리시 또 이용가능하도록 합니다.
	g_cUIManager->HT_DeleteWindow(nWindowIndex+UI_WINDOW_MESSAGEBOX);

	// 해당 윈도우 메시지 프로시져를 호출하여 추가적인 처리가 가능하도록 해줍니다.
	UIWindow* pWindow = g_cUIManager->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) 
	{
		func_t* ptr = pWindow->GetMessageProcedure(); // 함수 포인터를 얻어온다.
		pWindow->EnableOn(); // 먼저 윈도우 상태를 가능상태로 만듭니다.

		// 해당 메시지 프로시져 실행
		ptr(UI_ACTION_MOUSE_L_UP, UI_TARGET_MESSAGEBOX, iTargetID);
	}

	//	기존에 입력됐던 문자열을 지운다.
	//g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
	//g_cImeMgr.InputString();
}

// 윈도우 영역에 추가로 윈도우를 움직일 수 있는 영역을 설정합니다. 첫번째 인자는 참으로 해야하며, 영역을 끄려면 거짓으로 셋팅합니다.
void CHTUIManager::HT_SetMovingRegion(unsigned int nIndex, bool isOn, int iPosX, int iPosY, int iSizeX, int iSizeY)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) pWindow->SetMovingRegion(isOn, iPosX, iPosY, iSizeX, iSizeY);
}

// 백그라운드 영역 맵으로 픽 가능 상태인가?
bool CHTUIManager::HT_isBackgroundDownEnable(unsigned int nIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) return pWindow->m_bBackgroundDownEnable;
	return false;
}

// 백그라운드 영역 맵으로 픽 가능여부 설정
void CHTUIManager::HT_SetBackgroundDownEnable(unsigned int nIndex, bool bEnable)
{
	UIWindow* pWindow = this->FindWindowPointer(nIndex);
	if (pWindow != NULL) pWindow->m_bBackgroundDownEnable = bEnable;
}

// 영역 검사 (해당 마우스 위치에 존재하는 윈도우 번호 반환)
unsigned int CHTUIManager::HT_CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX, int iWindowPosY)
{
	if (m_UIList.empty()) return 0;
	for(std::list<UIWindow*>::iterator ZOder = m_UIList.begin(); ZOder != m_UIList.end(); ++ZOder)
		if ((*ZOder)->CheckRegionWithPoint(iXPos, iYPos) == true)
			return (*ZOder)->m_nIndex;
	return 0;
}

// 현재 활성화된 에디터박스에 글자를 삽입합니다.
void CHTUIManager::HT_UpdateEditBoxText(CHTString str)
{
	HT_SetTextEditBoxControl(g_EditBoxFocusWindow, g_EditBoxFocusControl, str);
}

// 현재 활성화 된 에디터 박스의 커서 위치를 반환합니다.
HTvector3 CHTUIManager::HT_GetEditBoxCursorPos()
{
	int wposx, wposy;
	g_cUIManager->HT_GetWindowPos(g_EditBoxFocusWindow, wposx, wposy);

	HTvector3 pos;
	pos.x = float(wposx) + float(g_EditBoxCursorPosX);
	pos.y = float(wposy) + float(g_EditBoxCursorPosY);
	return pos;
}

// 입력이 들어왔을경우 호출 되는 함수 (샘플용)
void CHTUIManager::ActionTarget(int iAction, int iTarget, int iTargetID)	// 입력타입, 반응할대상, 해당ID
{
	switch (iTarget)
	{
	case UI_TARGET_BUTTON:
		if (iTargetID == 1)
		{
			g_cUIManager->HT_SetBackgroundColor(1, HT_COLOR(1,1,1,1));
		}
		else if (iTargetID == 2)
		{
			g_cUIManager->HT_SetBackgroundColor(1, HT_COLOR(1,0,0,1));
		}
		else
		{
			g_cUIManager->HT_CloseWindow();
		}
		break;
	case UI_TARGET_SLOTBOX:
		{
			switch(iAction)
			{
			case UI_ACTION_MOUSE_LCLK:
				g_cUIManager->HT_SetSlotBoxCoolTime(1, 1, 1000, 0);
				break;
			}
		}
		break;
	}
	//g_cUIManager->HT_AccptSlotBoxMoving();
	//g_cUIManager->HT_RefuseSlotImageMoving();
	//CHTString str;
	//str.HT_szFormat("%d", g_cUIManager->HT_GetScrollBarValue(1,1));
	//g_cUIManager->HT_SetTextLabelControl(1,1, str);
	return;
}

// 자석기능 설정 (0 = 취소, -1 = 바탕화면)
void CHTUIManager::HT_SetMagnet(unsigned int nWindowIndex, unsigned int nTargetIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->SetMagnet(nTargetIndex);
}

// 해당 윈도우 자석기능에 삽입 / 삭제 (내부처리용)
void CHTUIManager::MagnetMgr(unsigned int nWindowIndex, unsigned int nTargetIndex, bool bInsert)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) pWindow->MagnetMgr(nTargetIndex, bInsert);
}

// 해당 윈도우의 자석상태를 알아온다.
bool CHTUIManager::HT_GetMagnetState(unsigned int nWindowIndex)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->GetMagnetState();
	return false;
}

void CHTUIManager::HT_SetScriptMessage( HTint idMessage, CHTString* pszMessage, CHTString strInputItem1, CHTString strInputItem2 )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
	{
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	}
	else
	{
		szString.HT_hrCleanUp();
	}
	
	// 변수가 3개 일 때
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		//CHTString szOut1, szOut2, szOut3;

		//// sParam1
		//HT_g_Script_SetParamTextForMessage( sParam1, &szOut1 );
		//// sParam2
		//HT_g_Script_SetParamTextForMessage( sParam2, &szOut2 );
		//// sParam3
		//HT_g_Script_SetParamTextForMessage( sParam3, &szOut3 );

		//pszMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		*pszMessage->HT_szFormat( szString.HT_szGetString(), strInputItem1.HT_szGetString(), strInputItem2.HT_szGetString() );
	}
	// 변수가 1개 일 때
	else if( sParam1 != eMsgParamNone  )
	{
		*pszMessage->HT_szFormat( szString.HT_szGetString(), strInputItem1.HT_szGetString() );
	}
	else
	{
		*pszMessage = szString;
	}
}


//	우피아 찍을때 콤마 마크 찍을수 있도록 셋팅
CHTString CHTUIManager::HT_strSetRestMark(HTint iNumber)
{
	CHTString str;
	CHTString strMilliard, strMillion, strThousand, strOne;

	HTint iMilliard = 0, iMillion = 0, iThousand = 0, iOne = 0;

	iMilliard = iNumber/1000000000;
	iMillion = iNumber/1000000 - iMilliard*1000;
	iThousand = iNumber/1000 - iMilliard*1000000 - iMillion*1000;
	iOne = iNumber - iMilliard*1000000000 - iMillion*1000000 - iThousand*1000;

	if (iMilliard!=0)
	{
		if (iMillion<10)							strMillion.HT_szFormat("00%d", iMillion);
		else if (iMillion>=10 && iMillion<100)		strMillion.HT_szFormat("0%d", iMillion);
		else										strMillion.HT_szFormat("%d", iMillion);

		if (iThousand<10)							strThousand.HT_szFormat("00%d", iThousand);
		else if (iThousand>=10 && iThousand<100)	strThousand.HT_szFormat("0%d", iThousand);
		else										strThousand.HT_szFormat("%d", iThousand);

		if (iOne<10)								strOne.HT_szFormat("00%d", iOne);
		else if (iOne>=10 && iOne<100)				strOne.HT_szFormat("0%d", iOne);
		else										strOne.HT_szFormat("%d", iOne);

		str.HT_szFormat( _T("%d"), iMilliard );
		str += _T(",");
		str += strMillion;
		str += _T(",");
		str += strThousand;
		str += _T(",");
		str += strOne;
	}
	else
	{
		if (iMillion!=0)
		{
			if (iThousand<10)							strThousand.HT_szFormat("00%d", iThousand);
			else if (iThousand>=10 && iThousand<100)	strThousand.HT_szFormat("0%d", iThousand);
			else										strThousand.HT_szFormat("%d", iThousand);

			if (iOne<10)								strOne.HT_szFormat("00%d", iOne);
			else if (iOne>=10 && iOne<100)				strOne.HT_szFormat("0%d", iOne);
			else										strOne.HT_szFormat("%d", iOne);

			str.HT_szFormat( _T("%d"), iMillion );
			str += _T(",");
			str += strThousand;
			str += _T(",");
			str += strOne;
		}
		else
		{
			if (iThousand!=0)
			{
				if (iThousand<10)							strThousand.HT_szFormat("00%d", iThousand);
				else if (iThousand>=10 && iThousand<100)	strThousand.HT_szFormat("0%d", iThousand);
				else										strThousand.HT_szFormat("%d", iThousand);

				if (iOne<10)								strOne.HT_szFormat("00%d", iOne);
				else if (iOne>=10 && iOne<100)				strOne.HT_szFormat("0%d", iOne);
				else										strOne.HT_szFormat("%d", iOne);

				str.HT_szFormat( _T("%d"), iThousand );
				str += _T(",");
				str += strOne;
			}
			else
			{
				if (iOne<10)								strOne.HT_szFormat("00%d", iOne);
				else if (iOne>=10 && iOne<100)				strOne.HT_szFormat("0%d", iOne);
				else										strOne.HT_szFormat("%d", iOne);

				str.HT_szFormat( _T("%d"), iOne );
			}
		}
	}
	return str;
	//return _T("");
}

// 해당 윈도우의 자석상태를 수동 셋팅합니다.
void CHTUIManager::HT_SetMagnetState(unsigned int nWindowIndex, bool bState)
{
	UIWindow* pWindow = this->FindWindowPointer(nWindowIndex);
	if (pWindow != NULL) return pWindow->SetMagnetState(bState);
	return;
}


// 환경설정 (UI Image에 대해서만 등록한다. Icon은 32*32 고정이므로 ClientRes ID를 그대로 이용한다.)
void CHTUIManager::HTSetGameEnvironment(int iScreenX, int iScreenY, int iNationalCode, int iConnectingServer, int iGameMode, int iResource)
{
	m_iScreenX = iScreenX;
	m_iScreenY = iScreenY;
	m_iNationalCode = iNationalCode;	
	m_iConnectingServer = iConnectingServer;
	m_iGameMode = iGameMode;

	if (iResource) // MainUI로 읽음
	{
	// MainUI (일단 임시로 이렇게 처리한다. 시간이 되면 최적화 하자)

	// 기본 UI 모음 (라인, 점, 이미지등)
	this->RegisterTextureID(0, 23899, 1, 1);	//흰색점 (블랜딩을 입혀 순수 색상을 만들어냄)
	this->RegisterTextureID(1, 22762, 3, 32);	//UI_HeightLine01_3x32.bmp (윈도우 구성용 새로 라인)
	this->RegisterTextureID(2, 22763, 96, 3);	//UI_WidthLine01_96x3.bmp (윈도우 구성용 가로 라인)
	this->RegisterTextureID(3, 22764, 128, 32);	//UI_TitleBar01_128x32.bmp (타이틀)
	
	this->RegisterTextureID(8, 22766, 64, 6);	//UI_WidthLine02_64X6.bmp (꾸밈용 가로 라인)

	// 꾸밈 박스 모음 (라벨에 사용)
	this->RegisterTextureID(9, 22767, 152, 19);	//UI_Box01_152X19.bmp	긴 푸른 박스
	this->RegisterTextureID(10, 22768, 79, 19);	//UI_Box02_79X19.bmp	보통 푸른 박스
	this->RegisterTextureID(11, 22769, 79, 19);	//UI_Box03_79X19.bmp	보통 갈색 박스

	// 윳판 이미지들 (윷놀이판 테투리 이미지들)
	this->RegisterTextureID(16, 22774, 32, 32);	//UI_Picture01_32X32.bmp
	this->RegisterTextureID(17, 22775, 32, 32);	//UI_Picture02_32X32.bmp
	this->RegisterTextureID(18, 22776, 32, 32);	//UI_Picture03_32X32.bmp
	this->RegisterTextureID(19, 22777, 32, 32);	//UI_Picture04_32X32.bmp
	this->RegisterTextureID(20, 22778, 32, 32);	//UI_Picture05_32X32.bmp
	this->RegisterTextureID(21, 22779, 32, 32);	//UI_Picture06_32X32.bmp

	// 윳판 이미지들 (한자로된 숫자들)
	this->RegisterTextureID(22, 22780, 23, 23); // 1
	this->RegisterTextureID(23, 22781, 23, 23); // 2
	this->RegisterTextureID(24, 22782, 23, 23); // 3
	this->RegisterTextureID(25, 22783, 23, 23); // 4
	this->RegisterTextureID(26, 22784, 23, 23); // 5
	this->RegisterTextureID(27, 22785, 23, 23); // 6
	this->RegisterTextureID(28, 22786, 23, 23); // 7
	this->RegisterTextureID(29, 22787, 23, 23); // 8
	this->RegisterTextureID(30, 22788, 23, 23); // 9
	this->RegisterTextureID(31, 22789, 39, 39);	// 숫자 이미지 외각 꾸밈 박스
	this->RegisterTextureID(32, 22790, 28, 60);	// 말

	// 아이콘 테두리 박스 (얇은 흰색 테두리)
	this->RegisterTextureID(66, 22794, 35, 35);//  	UI_Box06_35X35.bmp

	// 인벤토리 장착창 이미지
	this->RegisterTextureID(67, 22795, 231, 203);//	UI_Box19_231X203.bmp

	// 순서대로 동, 서, 남, 북 글자 이미지
	this->RegisterTextureID(68, 22796, 25, 25);//  	UI_Box22_25X25.bmp
	this->RegisterTextureID(69, 22797, 25, 25);//  	UI_Box23_25X25.bmp
	this->RegisterTextureID(70, 22798, 25, 25);//  	UI_Box24_25X25.bmp
	this->RegisterTextureID(71, 22799, 25, 25);//  	UI_Box25_25X25.bmp

	// 금편 한조각 이미지 (윳판용)
	this->RegisterTextureID(72, 22800, 32, 32);//  	UI_Box40_32X32.bmp

	// 제련 애니메이션 이미지들 
	this->RegisterTextureID(73, 22801, 96, 96);//  	UI_Box47_96X96.bmp
	this->RegisterTextureID(74, 22802, 96, 96);//  	UI_Box41_96X96.bmp
	this->RegisterTextureID(75, 22803, 96, 96);//  	UI_Box42_96X96.bmp
	this->RegisterTextureID(76, 22804, 96, 96);//  	UI_Box43_96X96.bmp
	this->RegisterTextureID(77, 22805, 96, 96);//  	UI_Box44_96X96.bmp
	this->RegisterTextureID(78, 22806, 96, 96);//  	UI_Box45_96X96.bmp
	this->RegisterTextureID(79, 22807, 96, 96);//  	UI_Box46_96X96.bmp

	// 홈피 아이콘 (삭제할것)
	this->RegisterTextureID(80, 22808, 32, 32);//  	UI_Box50_32X32.bmp

	// 공성전 UI 지도 이미지
	this->RegisterTextureID(81, 22809, 256, 256);//  	UI_Box64_256X256.bmp

	// 공성전 지도위의 말들 (빨강, 보라, 흰색, 검은색, 녹색)
	this->RegisterTextureID(82, 22810, 32, 32);//  	UI_Box66_32X32.bmp
	this->RegisterTextureID(83, 22811, 32, 32);//  	UI_Box67_32X32.bmp
	this->RegisterTextureID(84, 22812, 32, 32);//  	UI_Box68_32X32.bmp
	this->RegisterTextureID(85, 22813, 32, 32);//  	UI_Box69_32X32.bmp
	this->RegisterTextureID(86, 22814, 32, 32);//  	UI_Box65_32X32.bmp

	// 상태 게이지 꾸밈 박스 (새로용)
	this->RegisterTextureID(96, 22827, 13, 62);//		UI_Box57_13X62.bmp

	// 게이지 바 (사이즈별로 구별할것)
	this->RegisterTextureID(100, 22831, 16, 59);//		UI_ProgressBar07_16X59.bmp	
	this->RegisterTextureID(101, 22832, 150, 5);//		UI_ProgressBar01_150X5.bmp
	this->RegisterTextureID(102, 22833, 150, 5);//		UI_ProgressBar02_150X5.bmp
	this->RegisterTextureID(103, 22834, 144, 4);//		UI_ProgressBar03_144X4.bmp
	this->RegisterTextureID(104, 22835, 164, 15);//		UI_ProgressBar04_164X15.bmp
	this->RegisterTextureID(105, 22836, 164, 15);//		UI_ProgressBar05_164X15.bmp
	this->RegisterTextureID(106, 22837, 16, 59);//		UI_ProgressBar06_16X59.bmp

	// 프라나 바 (좌,우) 꾸밈
	this->RegisterTextureID(107, 22856, 400, 11);//		UI_Ex01.bmp
	this->RegisterTextureID(108, 22857, 400, 11);//		UI_Ex02.bmp

	this->RegisterTextureID(199, 23895, 7, 16);	 // 커서 이미지

	// 게이지 (몬스터 체력) 
	this->RegisterTextureID(162, 22219, 162, 9);//		UI_ProgressBar08_162X9.bmp

	// 북, 서, 동, 남 화살표
	this->RegisterTextureID(163, 22220, 25, 18);//		UI_Target01_25X18.bmp
	this->RegisterTextureID(164, 22247, 18, 25);//		UI_Target02_18X25.bmp
	this->RegisterTextureID(165, 22248, 18, 25);//		UI_Target03_18X25.bmp
	this->RegisterTextureID(166, 22249, 25, 18);//		UI_Target04_25X18.bmp

	// 푸른색 꾸밈라인 (가로)
	this->RegisterTextureID(167, 22250, 32, 6);//		UI_WidthLine02_32X6.bmp

	// 꾸밈박스 (작은거)
	this->RegisterTextureID(169, 22261, 25, 19);//		UI_Box05_25X19.bmp
	// 퀵슬롯 꾸밈 (새로)
	this->RegisterTextureID(170, 22294, 38, 11);//		UI_Box30_38X11.bmp
	// 메인바 아이콘 테두리
	this->RegisterTextureID(171, 22295, 38, 40);//		UI_Box74_38X40.bmp
	// 퀵슬롯 아이콘 테두리
	this->RegisterTextureID(172, 22296, 39, 39);//		UI_Box59_39X39.bmp
	// 퀵슬롯 꾸밈 (가로)
	this->RegisterTextureID(173, 22302, 11, 38);//		UI_Box51_11X38.bmp
	// 퀵슬롯 버튼 주변 꾸밈
	this->RegisterTextureID(174, 22303, 40, 36);//		UI_Box52_40X36.bmp
	// 체크 모양 (체크박스)
	this->RegisterTextureID(175, 22304, 7, 9);//		UI_Box20_7X9.bmp

	// 공성전 마크 
	this->RegisterTextureID(188, 22314, 64, 64);//  	UI_SiegeMark01.bmp	공성1
	this->RegisterTextureID(189, 22321, 64, 64);//  	UI_SiegeMark02.bmp	공성2
	this->RegisterTextureID(190, 22322, 64, 64);//  	UI_SiegeMark03.bmp	공성3
	this->RegisterTextureID(191, 22328, 64, 64);//  	UI_SiegeMark04.bmp	수성
	this->RegisterTextureID(192, 22329, 64, 64);//  	UI_SiegeMark05.bmp	무소속

	// 윳판 테두리 색깔 이미지
	this->RegisterTextureID(193, 22372, 39, 39); // UI_Box75_39X39.bmp 흰색
	this->RegisterTextureID(194, 22373, 39, 39); // UI_Box76_39X39.bmp 파랑
	this->RegisterTextureID(195, 22374, 39, 39); // UI_Box77_39X39.bmp 노랑
	this->RegisterTextureID(196, 22380, 39, 39); // UI_Box78_39X39.bmp 빨강
	this->RegisterTextureID(197, 22381, 39, 39); // UI_Box79_39X39.bmp 녹색

	// -----------
	//  버튼 모음
	// -----------
	// 종료버튼 (윈도우 최상단 오른쪽에 위치한 기본 구성버튼)
	this->RegisterTextureID(5, 22759, 28, 25);	//UI_Button01_N_28x25.bmp
	this->RegisterTextureID(6, 22760, 28, 25);  //UI_Button01_O_28x25.bmp
	this->RegisterTextureID(7, 22761, 28, 25);  //UI_Button01_D_28x25.bmp
	
	// 윈도우 사이즈 조절 버튼
	this->RegisterTextureID(4, 22765, 19, 18);	//UI_Scale01_19X18.bmp
	this->RegisterTextureID(12, 22770, 19, 18);	//UI_Scale02_19X18.bmp
	
	// 작은 버튼 (스킬, 스텟창등의 수치 증가에 사용)
	this->RegisterTextureID(13, 22771, 13, 13);	//UI_Button04_N_13X13.bmp
	this->RegisterTextureID(14, 22772, 13, 13);	//UI_Button04_O_13X13.bmp
	this->RegisterTextureID(15, 22773, 13, 13);	//UI_Button04_D_13X13.bmp

	// 크리슈나 구입 버튼 (메인바)
	this->RegisterTextureID(34, 22699, 32, 32);//UI_Button31_N_32X32.bmp
	this->RegisterTextureID(35, 22700, 32, 32);//UI_Button31_O_32X32.bmp
	this->RegisterTextureID(33, 22698, 32, 32);//UI_Button31_D_32X32.bmp
	
	// 상태창 버튼 (메인바)
	this->RegisterTextureID(37, 22702, 32, 32);//UI_Button32_N_32X32.bmp
	this->RegisterTextureID(38, 22703, 32, 32);//UI_Button32_O_32X32.bmp
	this->RegisterTextureID(36, 22701, 32, 32);//UI_Button32_D_32X32.bmp
	
	// 인벤토리 버튼 (메인바)
	this->RegisterTextureID(40, 22705, 32, 32);//UI_Button33_N_32X32.bmp
	this->RegisterTextureID(41, 22706, 32, 32);//UI_Button33_O_32X32.bmp
	this->RegisterTextureID(39, 22704, 32, 32);//UI_Button33_D_32X32.bmp
	
	// 퀘스트 버튼 (메인바)
	this->RegisterTextureID(43, 22708, 32, 32);//UI_Button34_N_32X32.bmp
	this->RegisterTextureID(44, 22709, 32, 32);//UI_Button34_O_32X32.bmp
	this->RegisterTextureID(42, 22707, 32, 32);//UI_Button34_D_32X32.bmp
	
	// 스킬창 버튼 (메인바)
	this->RegisterTextureID(46, 22711, 32, 32);//UI_Button35_N_32X32.bmp
	this->RegisterTextureID(47, 22712, 32, 32);//UI_Button35_O_32X32.bmp
	this->RegisterTextureID(45, 22710, 32, 32);//UI_Button35_D_32X32.bmp
	
	// 옵션창 버튼 (메인바)
	this->RegisterTextureID(49, 22714, 32, 32);//UI_Button36_N_32X32.bmp
	this->RegisterTextureID(50, 22715, 32, 32);//UI_Button36_O_32X32.bmp
	this->RegisterTextureID(48, 22713, 32, 32);//UI_Button36_D_32X32.bmp
	
	// 명령창 버튼 (메인바)
	this->RegisterTextureID(52, 22717, 32, 32);//UI_Button37_N_32X32.bmp
	this->RegisterTextureID(53, 22718, 32, 32);//UI_Button37_O_32X32.bmp
	this->RegisterTextureID(51, 22716, 32, 32);//UI_Button37_D_32X32.bmp
	
	// PK 버튼 (메인바)
	this->RegisterTextureID(55, 22720, 32, 32);//UI_Button38_N_32X32.bmp
	this->RegisterTextureID(56, 22721, 32, 32);//UI_Button38_O_32X32.bmp
	this->RegisterTextureID(54, 22719, 32, 32);//UI_Button38_D_32X32.bmp
	
	// 푸른 은색 버튼
	this->RegisterTextureID(63, 22791, 64, 19);// 	UI_Button03_N_64X19.bmp	
	this->RegisterTextureID(65, 22793, 64, 19);//  	UI_Button03_O_64X19.bmp
	this->RegisterTextureID(64, 22792, 64, 19);//  	UI_Button03_D_64X19.bmp

	// 인벤토리 루피아 모양 버튼 (루피아 언패킹을 위한)
	this->RegisterTextureID(87, 22815, 32, 19);//  	UI_Button16_D_32X19.bmp
	this->RegisterTextureID(88, 22816, 32, 19);//  	UI_Button16_N_32X19.bmp
	this->RegisterTextureID(89, 22817, 32, 19);//  	UI_Button16_O_32X19.bmp

	// 인벤토리 가방 2 버튼
	this->RegisterTextureID(90, 22818, 24, 19);//  	UI_Button18_D_24X19.bmp
	this->RegisterTextureID(91, 22819, 24, 19);//  	UI_Button18_N_24X19.bmp
	this->RegisterTextureID(92, 22820, 24, 19);//  	UI_Button18_O_24X19.bmp
	// 인벤토리 가방 1 버튼
	this->RegisterTextureID(184, 22821, 24, 19);//  	UI_Button17_D_24X19.bmp
	this->RegisterTextureID(185, 22822, 24, 19);//  	UI_Button17_N_24X19.bmp
	this->RegisterTextureID(186, 22823, 24, 19);//  	UI_Button17_O_24X19.bmp

	// 상태 게이지 버튼 (새로용)
	this->RegisterTextureID(93, 22824, 32, 29);//		UI_Button28_D_32X29.bmp
	this->RegisterTextureID(94, 22825, 32, 29);//		UI_Button28_N_32X29.bmp
	this->RegisterTextureID(95, 22826, 32, 29);//		UI_Button28_O_32X29.bmp

	// 채워져 있는 갈색 버튼 (메시지 박스등등에 쓰임)
	this->RegisterTextureID(97, 22828, 72, 19);//		UI_Button14_O_72X19.bmp
	this->RegisterTextureID(98, 22829, 72, 19);//		UI_Button14_D_72X19.bmp
	this->RegisterTextureID(99, 22830, 72, 19);//		UI_Button14_N_72X19.bmp

	// 스크롤바 버튼 (가로 새로)
	this->RegisterTextureID(133, 22838, 14, 16);//		UI_ScrollBar_Button01_D_D14X16.bmp
	this->RegisterTextureID(134, 22839, 14, 16);//		UI_ScrollBar_Button01_D_U14X16.bmp
	this->RegisterTextureID(135, 22840, 14, 14);//		UI_ScrollBar_Button01_D_WB14X14.bmp
	this->RegisterTextureID(136, 22841, 14, 16);//		UI_ScrollBar_Button01_N_D14X16.bmp
	this->RegisterTextureID(137, 22842, 14, 16);//		UI_ScrollBar_Button01_N_U14X16.bmp
	this->RegisterTextureID(138, 22843, 14, 14);//		UI_ScrollBar_Button01_N_WB14X14.bmp
	this->RegisterTextureID(139, 22844, 14, 16);//		UI_ScrollBar_Button01_O_D14X16.bmp
	this->RegisterTextureID(140, 22845, 14, 16);//		UI_ScrollBar_Button01_O_U14X16.bmp
	this->RegisterTextureID(141, 22846, 14, 14);//		UI_ScrollBar_Button01_O_WB14X14.bmp
	this->RegisterTextureID(142, 22847, 14, 14);//		UI_ScrollBar_Button02_D_WB14X14.bmp
	this->RegisterTextureID(143, 22848, 14, 14);//		UI_ScrollBar_Button02_N_WB14X14.bmp
	this->RegisterTextureID(144, 22849, 14, 14);//		UI_ScrollBar_Button02_O_WB14X14.bmp
	this->RegisterTextureID(145, 22850, 16, 14);//		UI_ScrollBar_Button01_N_R16X14.bmp
	this->RegisterTextureID(146, 22851, 16, 14);//		UI_ScrollBar_Button01_O_R16X14.bmp
	this->RegisterTextureID(147, 22852, 16, 14);//		UI_ScrollBar_Button01_D_R16X14.bmp
	this->RegisterTextureID(148, 22853, 16, 14);//		UI_ScrollBar_Button01_N_L16X14.bmp
	this->RegisterTextureID(149, 22854, 16, 14);//		UI_ScrollBar_Button01_D_L16X14.bmp
	this->RegisterTextureID(150, 22855, 16, 14);//		UI_ScrollBar_Button01_O_L16X14.bmp

	// 퀵슬롯바 버튼
	this->RegisterTextureID(57, 22119, 25, 24);//		UI_Button23_N_25X24.bmp
	this->RegisterTextureID(58, 22120, 25, 24);//		UI_Button23_O_25X24.bmp
	this->RegisterTextureID(59, 22121, 25, 24);//		UI_Button23_D_25X24.bmp
	// 퀵슬롯바 버튼 (아래)
	this->RegisterTextureID(60, 22122, 14, 14);//		UI_Button24_N_14X14.bmp
	this->RegisterTextureID(61, 22134, 14, 14);//		UI_Button24_O_14X14.bmp
	this->RegisterTextureID(62, 22135, 14, 14);//		UI_Button24_D_14X14.bmp
	// 퀵슬롯바 버튼(위)
	this->RegisterTextureID(151, 22136, 14, 14);//		UI_Button25_N_14X14.bmp
	this->RegisterTextureID(152, 22137, 14, 14);//		UI_Button25_O_14X14.bmp
	this->RegisterTextureID(153, 22149, 14, 14);//		UI_Button25_D_14X14.bmp

	// 퀵슬롯바 버튼 (가로)
	this->RegisterTextureID(154, 22150, 24, 37);//		UI_Button26_N_24X37.bmp
	this->RegisterTextureID(155, 22151, 24, 37);//		UI_Button26_O_24X37.bmp
	this->RegisterTextureID(176, 22172, 24, 37);//		UI_Button26_D_24X37.bmp
	// 퀵슬롯바 버튼 (새로)
	this->RegisterTextureID(177, 22173, 38, 23);//		UI_Button27_N_38X23.bmp
	this->RegisterTextureID(178, 22174, 38, 23);//		UI_Button27_O_38X23.bmp
	this->RegisterTextureID(179, 22175, 38, 23);//		UI_Button27_D_38X23.bmp

	// 게이지 버튼
	this->RegisterTextureID(156, 22203, 32, 29);//		UI_Button28_N_32X29.bmp
	this->RegisterTextureID(157, 22204, 32, 29);//		UI_Button28_O_32X29.bmp
	this->RegisterTextureID(158, 22205, 32, 29);//		UI_Button28_D_32X29.bmp

	// 금속성 버튼
	this->RegisterTextureID(159, 22206, 64, 19);//		UI_Button39_N_64X19.bmp
	this->RegisterTextureID(160, 22217, 64, 19);//		UI_Button39_O_64X19.bmp
	this->RegisterTextureID(161, 22218, 64, 19);//		UI_Button39_D_64X19.bmp

	// GM 이미지 버튼(튜토리얼 진행창)
	this->RegisterTextureID(168, 22260, 60, 62);//		UI_Button40_N_60X62.bmp
	this->RegisterTextureID(180, 22305, 60, 62);//		UI_Button40_O_60X62.bmp
	this->RegisterTextureID(181, 22311, 60, 62);//		UI_Button40_D_60X62.bmp
	
	// 스킬창 화살표
	this->RegisterTextureID(182, 22312, 5, 27);//		UI_WidthLine03_5X27.bmp
	this->RegisterTextureID(183, 22313, 79, 16);//		UI_WidthLine03_79X16.bmp

	// 버튼 Over, Down만 사용 Normal은 0
	this->RegisterTextureID(200, 22397, 1, 3); // UI_WidthLine_EX_12_1X11.bmp
	this->RegisterTextureID(201, 22398, 182, 12); // UI_Box01.bmp	선택박스 (채팅창)
	this->RegisterTextureID(202, 22399, 291, 39); // UI_Box02.bmp	선택박스 (주소록)

	// 프라나바
	this->RegisterTextureID(203, 22400, 1, 3);//		22400	UI_WidthLine03_1X3.bmp

	//채팅창 추가 버튼
	this->RegisterTextureID(204, 22463, 64, 21);//		22463	UI_Button44_N_64X21.bmp
	this->RegisterTextureID(205, 22464, 64, 21);//		22464	UI_Button44_O_64X21.bmp
	this->RegisterTextureID(206, 22485, 64, 21);//		22485	UI_Button44_D_64X21.bmp
	this->RegisterTextureID(207, 22486, 31, 21);//		22486	UI_Button43_N_31X21.bmp
	this->RegisterTextureID(208, 22501, 31, 21);//		22501	UI_Button43_O_31X21.bmp
	this->RegisterTextureID(209, 22722, 31, 21);//		22722	UI_Button43_D_31X21.bmp
	
	this->RegisterTextureID(210, 22724, 47, 47);//		22724	UI_Button45_N_47X47.bmp
	this->RegisterTextureID(211, 22725, 47, 47);//		22725	UI_Button45_O_47X47.bmp
	this->RegisterTextureID(212, 22726, 47, 47);//		22726	UI_Button45_D_47X47.bmp

	this->RegisterTextureID(213, 23104, 19, 19);	//23104	UI_Button48_N_19X19.bmp
	this->RegisterTextureID(214, 23105, 19, 19);	//23105	UI_Button48_O_19X19.bmp
	this->RegisterTextureID(215, 23106, 19, 19);	//23106	UI_Button48_D_19X19.bmp
	this->RegisterTextureID(216, 23107, 64, 19);	//23107	UI_Button47_N_64X19.bmp
	this->RegisterTextureID(217, 23108, 64, 19);	//23108	UI_Button47_O_64X19.bmp
	this->RegisterTextureID(218, 23109, 64, 19);	//23109	UI_Button47_D_64X19.bmp

	this->RegisterTextureID(219, 23110, 31, 21);		//23110	UI_Button42_N_31X21.bmp
	this->RegisterTextureID(220, 23111, 31, 21);		//23111	UI_Button42_O_31X21.bmp
	this->RegisterTextureID(221, 23112, 31, 21);		//23112	UI_Button42_D_31X21.bmp
	}
	else	// Intro Index로 읽음
	{
	// UI 텍스처 정보 등록 (나중에 스킨형태 제공을 위해 파일로 빼낼것임)
	this->RegisterTextureID(0, 27023, 1, 1);
	this->RegisterTextureID(5, 27159, 28, 25);
	this->RegisterTextureID(6, 27160, 28, 25);
	this->RegisterTextureID(7, 27161, 28, 25);
	this->RegisterTextureID(1, 27162, 3, 32);
	this->RegisterTextureID(2, 27163, 96, 3);
	this->RegisterTextureID(3, 27164, 128, 32);
	this->RegisterTextureID(4, 27165, 19, 18);
	this->RegisterTextureID(8, 27166, 64, 6);
	this->RegisterTextureID(9, 27167, 152, 19);
	this->RegisterTextureID(10, 27168, 79, 19);
	this->RegisterTextureID(11, 27169, 79, 19);
	this->RegisterTextureID(12, 27170, 19, 18);
	this->RegisterTextureID(13, 27171, 13, 13);
	this->RegisterTextureID(14, 27172, 13, 13);
	this->RegisterTextureID(15, 27173, 13, 13);
	
	this->RegisterTextureID(16, 27037, 256, 32); // UI_Button Big_1.bmp
	this->RegisterTextureID(17, 27038, 256, 32); // UI_Button Big_2.bmp
	this->RegisterTextureID(18, 27061, 256, 32); // UI_Button Big_3.bmp

	this->RegisterTextureID(19, 27039, 256, 32); // UI_Button large_1.bmp
	this->RegisterTextureID(20, 27040, 256, 32); // UI_Button large_2.bmp
	this->RegisterTextureID(21, 27041, 256, 32); // UI_Button large_3.bmp

	this->RegisterTextureID(22, 27042, 16, 16); // UI_Button right_1.bmp
	this->RegisterTextureID(23, 27043, 16, 16); // UI_Button right_2.bmp
	this->RegisterTextureID(24, 27044, 16, 16); // UI_Button right_3.bmp

	this->RegisterTextureID(25, 27045, 64, 32); // UI_Button small_1.bmp
	this->RegisterTextureID(26, 27046, 64, 32); // UI_Button small_2.bmp
	this->RegisterTextureID(27, 27047, 64, 32); // UI_Button small_3.bmp

	this->RegisterTextureID(28, 27048, 16, 16); // UI_Button up_1.bmp
	this->RegisterTextureID(29, 27049, 16, 16); // UI_Button up_2.bmp
	this->RegisterTextureID(30, 27050, 16, 16); // UI_Button up_3.bmp

	this->RegisterTextureID(31, 27051, 64, 64);	// UI_IN_12.tga
	this->RegisterTextureID(32, 27052, 512, 512);	// UI_IN_Charac_Del_01.tga
	this->RegisterTextureID(33, 27053, 512, 512); // UI_IN_Character_01.tga
	this->RegisterTextureID(34, 27054, 512, 256); // UI_IN_Login_01.tga
	this->RegisterTextureID(35, 27055, 512, 512); // UI_IN_New_Character_01.tga
	this->RegisterTextureID(36, 27056, 512, 512); // UI_IN_Sever_01.tga
	this->RegisterTextureID(37, 27057, 512, 512); // UI_New_Character_03.tga

	this->RegisterTextureID(38, 27058, 16, 16); // UI_Button left_1.bmp
	this->RegisterTextureID(39, 27059, 16, 16); // UI_Button left_2.bmp
	this->RegisterTextureID(40, 27060, 16, 16); // UI_Button left_3.bmp

	this->RegisterTextureID(199, 27022, 7, 16);	 // 커서
	this->RegisterTextureID(100, 26083, 512, 512);	// Tantra V3 Logo800
	this->RegisterTextureID(101, 26084, 1024, 512);	// Tantra V3 Logo1024
	}
}

// UI 관련 정보를 저장합니다.
void CHTUIManager::HT_vSaveDialogPos(CHTString strFilePath)
{
	CHTString	str;
	int			iVersion;
	int			iPosX, iPosY;
	int			iScreenX, iScreenY;

	FILE*	fp;
	fp = fopen(strFilePath, "wb");
	if (!fp) return;

	// 헤더부
	str = _T("HanbitSoft GameDev.Team");	fwrite(&str, sizeof(CHTString), 1, fp);	// 파일 구분
	iVersion = _INTERFACE_VERSION;			fwrite(&iVersion, sizeof(int), 1, fp);	// 버전
	iScreenX	= m_iScreenX;				fwrite(&iScreenX, sizeof(int), 1, fp);	// 해상도 X
	iScreenY	= m_iScreenY;				fwrite(&iScreenY, sizeof(int), 1, fp);	// 해상도 Y

	// 먼저 윈도우 위치 저장
	const int START_COUNT_INDEX = 200; 
	for (HTint i=0; i < 95; i++)
	{
		g_cUIManager->HT_GetWindowPos(START_COUNT_INDEX + i, iPosX, iPosY);
		fwrite(&iPosX, sizeof(int), 1, fp);
		fwrite(&iPosY, sizeof(int), 1, fp);
	}

	// 그외 정보들 저장
	fwrite( &(g_cQuickSlot->m_bVerSlot), sizeof(HTbool), 1, fp);	// 퀵슬롯 상태

	// 옵션 정보 변경
	//- 감마값, 아이디표시, 이펙트, 상점간소화, 사운드, 음악, 채팅모드, 메인바간소화
	//HT_vSystem_InputCheckSystem(int iAction, int iTarget, int iTargetID)
	fwrite( &(g_cSystem->m_iOption0), sizeof(int), 1, fp);	// 퀵슬롯 상태
	fwrite( &(g_cSystem->m_bOption1), sizeof(HTbool), 1, fp);	// 퀵슬롯 상태
	fwrite( &(g_cSystem->m_bOption2), sizeof(HTbool), 1, fp);	// 퀵슬롯 상태
	fwrite( &(g_cSystem->m_bOption3), sizeof(HTbool), 1, fp);	// 퀵슬롯 상태
	fwrite( &(g_cSystem->m_iOption4), sizeof(int), 1, fp);	// 퀵슬롯 상태
	fwrite( &(g_cSystem->m_iOption5), sizeof(int), 1, fp);	// 퀵슬롯 상태

	// 채팅 상태 저장
	fwrite( &(g_cChatting->m_iChatWindowStyle), sizeof(int), 1, fp);

	// 추가 저장
	fwrite( &(g_cSystem->m_bOption6), sizeof(HTbool), 1, fp);	// 퀵슬롯 상태

	// 윈도우 추가 저장
	for (HTint i=95; i < 120; i++)
	{
		g_cUIManager->HT_GetWindowPos(START_COUNT_INDEX + i, iPosX, iPosY);
		fwrite(&iPosX, sizeof(int), 1, fp);
		fwrite(&iPosY, sizeof(int), 1, fp);
	}

	fclose(fp);
}

// UI 관련 정보를 로딩합니다.
void CHTUIManager::HT_vOpenDialogPos(CHTString strFilePath)
{
	CHTString	str;
	int			iVersion;
	int			iPosX, iPosY;
	int			iScreenX, iScreenY;

	FILE*	fp;
	fp = fopen(strFilePath, "rb");
	if (!fp) return;

	// 헤더부
	fread(&str, sizeof(CHTString), 1, fp);	// 파일 구분
	fread(&iVersion, sizeof(int), 1, fp);	// 버전
	fread(&iScreenX, sizeof(int), 1, fp);	// 해상도 X
	fread(&iScreenY, sizeof(int), 1, fp);	// 해상도 Y

	if (iVersion != _INTERFACE_VERSION || iScreenX != m_iScreenX || iScreenY != m_iScreenY) 
	{
		fclose(fp);
		return;
	}
	
	// 먼저 윈도우 위치 저장
	const int START_COUNT_INDEX = 200; 
	for (HTint i=0; i < 95; i++)
	{
		fread(&iPosX, sizeof(int), 1, fp);
		fread(&iPosY, sizeof(int), 1, fp);
		g_cUIManager->HT_MoveWindow(START_COUNT_INDEX + i, iPosX, iPosY);
	}

	// 큇 슬롯의 저장된 가로, 세로 위치 결정하여 출력
	bool bFlag = false;	
	fread( &(bFlag), sizeof(HTbool), 1, fp); g_cQuickSlot->m_bVerSlot = bFlag ;
	

	// 퀵슬롯 셋팅
	if( bFlag == false )
	{
		//	현재 인벤토리의 위치를 구해와서 그기에 팝업한다.
		g_cUIManager->HT_HideWindow( _DIALOG_HQUICKSLOT );
		g_cUIManager->HT_ShowWindow( _DIALOG_WQUICKSLOT );
	}
	else 
	{
		g_cUIManager->HT_HideWindow( _DIALOG_WQUICKSLOT );
		g_cUIManager->HT_ShowWindow( _DIALOG_HQUICKSLOT );
	}

	// 옵션 정보 로딩 후 셋팅
	fread( &(g_cSystem->m_iOption0), sizeof(int), 1, fp);	// 감마값, 
	fread( &(g_cSystem->m_bOption1), sizeof(HTbool), 1, fp);	// 아이디표시, 
	fread( &(g_cSystem->m_bOption2), sizeof(HTbool), 1, fp);	// 이펙트, 
	fread( &(g_cSystem->m_bOption3), sizeof(HTbool), 1, fp);	// 상점간소화, 
	fread( &(g_cSystem->m_iOption4), sizeof(int), 1, fp);	// 사운드, 
	fread( &(g_cSystem->m_iOption5), sizeof(int), 1, fp);	// 음악, 

	// 옵션정보 로딩
	if (g_cSystem->m_bOption1 == true)
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 4);
	else
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 5);

	if (g_cSystem->m_bOption2 == true)
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 6);
	else
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 7);

	if (g_cSystem->m_bOption3 == true)
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 8);
	else
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 9);

	// 옵션 정보 세팅
	if (g_cSystem->m_iOption0 > 100) g_cSystem->m_iOption0 = 20;
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_OPTIONWND, 20, g_cSystem->m_iOption0 );
	g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_SCROLLBAR, 20);
	if (g_cSystem->m_iOption4 > 11) g_cSystem->m_iOption4 = 20;
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_OPTIONWND, 21, g_cSystem->m_iOption4 );
	g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_SCROLLBAR, 21);
	if (g_cSystem->m_iOption5 > 11) g_cSystem->m_iOption5 = 20;
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_OPTIONWND, 22, g_cSystem->m_iOption5 );
	g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_SCROLLBAR, 22);
	
	// 채팅 상태 로딩 
	fread( &(g_cChatting->m_iChatWindowStyle), sizeof(int), 1, fp);

	// 채팅상태 셋팅
	if (g_cChatting->m_iChatWindowStyle < 0 || g_cChatting->m_iChatWindowStyle > 3)
		g_cChatting->m_iChatWindowStyle = 1;
	
	g_cChatting->m_iChatWindowStyle--;
	if (g_cChatting->m_iChatWindowStyle < 0) g_cChatting->m_iChatWindowStyle = 3;
	
	g_cChatting->HT_vChatting_ChangeChatWnd();
	g_cChatting->HT_vChatting_SetFocusOff( false );

	fread( &(g_cSystem->m_bOption6), sizeof(HTbool), 1, fp);	// 슬롯

	// 옵션정보 로딩
	if (g_cSystem->m_bOption6 == true)
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 13);
	else
		g_cSystem->HT_vSystem_InputCheckSystem(0, UI_TARGET_BUTTON, 14);

	// 윈도우 추가 로딩
	for (HTint i=95; i < 120; i++)
	{
		fread(&iPosX, sizeof(int), 1, fp);
		fread(&iPosY, sizeof(int), 1, fp);
		g_cUIManager->HT_MoveWindow(START_COUNT_INDEX + i, iPosX, iPosY);
	}

	//fread( &(m_bChattingMode), sizeof(HTbool), 1, fp);
	//fread( &(m_bMinimapMode), sizeof(HTbool), 1, fp);
	fclose(fp);
}