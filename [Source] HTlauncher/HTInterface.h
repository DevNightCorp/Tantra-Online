#pragma once

// Interface.h
#ifndef _HTINTERFACE_H
#define _HTINTERFACE_H

#define _INTERFACE_VERSION		2005
#define _INTERFACE_SAVE_FILE_NAME	_T("resource\\UI\\Interface.sys")		// 인트로 관련 구성 파일 이름

// Message Procedure Define
typedef void func_t(int, int, int);		// 본 UI System에서 사용하는 함수포인터 (메시지 프로시져 함수형)

// iAction Type
#define	UI_ACTION_MOUSE_L_DOWN		0		// 마우스 L다운시
#define	UI_ACTION_MOUSE_L_UP		1		// 마우스 L업시
#define	UI_ACTION_MOUSEMOVE			2		// 마우스 무브시
#define	UI_ACTION_MOUSE_R_DOWN		3		// 마우스 R다운시
#define	UI_ACTION_MOUSE_R_UP		4		// 마우스 R업시
#define	UI_ACTION_MOUSE_LBCLK		5		// 마우스 L더블클릭시
#define	UI_ACTION_MOUSE_RBCLK		6		// 마우스 R더블클릭시
#define	UI_ACTION_MOUSE_LCLK		7		// 마우스 L클릭
#define	UI_ACTION_MOUSE_RCLK		8		// 마우스 R클릭

// iTarget Type
#define	UI_TARGET_BUTTON		0		// 버튼
#define	UI_TARGET_EDITBOX		1		// 에디터박스
#define	UI_TARGET_SCROLLBAR		2		// 스크롤바
#define	UI_TARGET_MESSAGEBOX	3		// 메시지박스
#define	UI_TARGET_SLOTBOX		4		// 슬롯박스
#define	UI_TARGET_TIMER			5		// 타이머


// MessageBox STYLE 정의
#define	UI_MESSAGEBOX_CONFIRM		0		// 확인창  (확인 = 2)
#define	UI_MESSAGEBOX_RECONFIRM		1		// 재확인창 (확인 = 2 / 취소 = 3)
#define	UI_MESSAGEBOX_NUMBERINPUT	2		// 숫자입력창
#define	UI_MESSAGEBOX_INPUT			3		// 입력창
#define	UI_MESSAGEBOX_CONFIRM_ENTER_NO 4	// 엔터기능 안먹히는 확인창
#define	UI_MESSAGEBOX_COUPON		5		// 쿠폰입력창


// EditBox STYLE 정의
#define	UI_EDITBOX_NORMAL			0		// 일반모드
#define UI_EDITBOX_SMALLCHARACTER	1		// 소문자입력모드
#define UI_EDITBOX_LARGECHARACTER	2		// 대문자입력모드
#define UI_EDITBOX_ONLYNUMBER		3		// 오직 숫자만 입력가능모드

//EditBox Mode 정의
#define	UI_EDITBOX_NORMALMODE		0		// 일반모드
#define UI_EDITBOX_PASSWORDMODE		1		// 패스워드 입력모드

//Magnet State 정의
#define UI_MAGNET_DISTANCE			20		// 자석 기능이 발생되는 픽셀 거리
#define UI_MAGNET_DISTANCE_EXIT		25		// 자석 상태로 부터 떨어져 나올 수 있는 픽셀 거리

//
// >> UITexture를 구성하는 최소단위 <<
//
typedef struct _UITexture
{
	int					PosX;					// Texture PosX (Local Coordinate)
	int					PosY;					// Texture PosY (Local Coordinate)
	int					SizeX;					// Output Texture Size X
	int					SizeY;					// Output Texture Size Y

	int					TextureID;				// Texture ID
	unsigned short		Layer;					// Layer (Z_ODER)
	HT_COLOR			VertexClr;				// Vertex Color

} UITexture;


// 
// >> UIText를 구성하는 최소단위 <<
// 
typedef struct _UIText
{
	HT_FONT_TYPE		Font;					// Font Kinds
	int					FontMode;				// Font Style
	HT_TEXT_FORMATING	TextFormating;			// Text Formating
	CHTString			strTitle;				// String
	HT_RECT				TextPos;				// Font Location (Local Coordinate - RECT)
	HT_COLOR			TextColor;				// Fore Color
	HT_COLOR			TextShadowColor;		// Background Color (Shadow Color)

} UIText;

// 
// >> Expand UIText를 구성하는 최소단위 <<
// 
typedef struct _UILongText
{
	HT_FONT_TYPE		Font;					// Font Kinds
	int					FontMode;				// Font Style
	HT_TEXT_FORMATING	TextFormating;			// Text Formating
	HTtchar				strTitle[1000];			// String
	HT_RECT				TextPos;				// Font Location (Local Coordinate - RECT)
	HT_COLOR			TextColor;				// Fore Color
	HT_COLOR			TextShadowColor;		// Background Color (Shadow Color)

} UILongText;

// 
// >> UI Resource 관리 구조체
//
typedef struct _UIResource
{
	int					XMLID;					// XML ID
	int					RealSizeX;				// Real Output Region Image SizeX
	int					RealSizeY;				// Real Output Region Image SizeY

} UIResource;

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Texture Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UITextureControl
{
private:
	// Texture Information
	UITexture			m_Texture;				// 텍스처 기본 정보들
	HTvector3			m_fScale;				// 결정된 텍스처 스케일비율
	int					m_iWidth;				// 실제 텍스처 사이즈X
	int					m_iHeight;				// 실제 텍스처 사이즈Y
	int					m_iEObjID;				// Engine으로 부터 부여 받은 텍스처 고유 ID값

	// Process
	int					RealSizeX;				// Real Output Region Image SizeX
	int					RealSizeY;				// Real Output Region Image SizeY
	bool				m_bCheckRegion;			// 제어 영역에 마우스무브 중인지 여부
	bool				m_bCheckMouseDown;		// 제어 영역에 마우스다운 중인지 여부
	bool				m_bCheckMouseRDown;		// 제어 영역에 마우스다운 중인지 여부

	bool				m_bEnable;				// true = 입력 처리가능 / false = 입력 처리무시
	bool				m_bDisplay;				// true = 출력 가능 / false = 출력 안함

public:
	unsigned int		m_nIndex;				// 컨트롤 고유 인덱스


	UITextureControl();
	virtual ~UITextureControl();

	// 생성
	void		CreateUITextureControl(unsigned int nIndex, UITexture oTexture);	// UI Object 생성
	UITexture	GetUITextureControl();				// 텍스처 정보 얻기

	// 출력
	void		Render(int iWindowPosX = 0, int iWindowPosY = 0);	
	// 영역 검사
	bool		CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);
	// 이동
	void		Move(int iXpos, int iYpos, int iType = 0);				// 원하는 위치로 이동
	// 제어
	void		Show() {m_bDisplay = true;}							// 보여줍니다.
	void		Hide() {m_bDisplay = false;}						// 숨깁니다.
	void		EnableOn() {m_bEnable = true;}						// 동작하게 합니다.
	void		EnableOff() {m_bEnable = false;}					// 동작하지 않게 합니다.
	void		CheckRegion(bool val) {m_bCheckRegion = val;}		// 제어영역 감지여부 셋팅
	void		CheckMouseDown(bool val) {m_bCheckMouseDown = val;}	// 제어영역 감지여부 셋팅
	void		CheckMouseRDown(bool val) {m_bCheckMouseRDown = val;}	// 제어영역 감지여부 셋팅
	void		SetScale(int iSizeX, int iSizeY, int iOSizeX = 1, int iOSizeY = 1);	// 원하는 크기로 조절
	void		SetColor(HT_COLOR clr);						// 텍스처 컬러 변경
	void		GetScale(int &iSizeX, int &iSizeY);					// 현재 크기 반환

	// 정보제공
	bool		isRegion() {return m_bCheckRegion;}					// 현재 영역이 반응중인가?
	bool		isMouseDown() {return m_bCheckMouseDown;}			// 현재 영역이 반응중인가?
	bool		isMouseRDown() {return m_bCheckMouseRDown;}			// 현재 영역이 반응중인가?
	bool		isEnableOn() {return m_bEnable;}
	bool		isDisplay() {return m_bDisplay;}
	HTvector3	GetUITextureControlPos();							// 위치를 얻어온다.
	int			GetTextureID() {return m_Texture.TextureID;}		// 텍스처 아이디를 얻어온다.
	
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Label Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UILabelControl
{
private:
	// Texture Information
	UIText				m_Text;					// Text 정보

	bool				m_bEnable;				// true = 입력 처리가능 / false = 입력 처리무시
	bool				m_bDisplay;				// true = 출력 가능 / false = 출력 안함

	bool				m_bCheckRegion;			// 제어 영역에 마우스무브 중인지 여부
	bool				m_bCheckMouseDown;		// 제어 영역에 마우스다운 중인지 여부

	int					TextPosX;				// 옵션 적용된 최종 텍스트 위치X
	int					TextPosY;				// 옵션 적용된 최종 텍스트 위치Y
	int					m_Direction;			// 배치방식

	void		SetTextArrangement(int iDirection);								// 해당범위 내에서 원하는 방향으로 배치합니다.

public:
	unsigned int		m_nIndex;				// 컨트롤 고유 인덱스

	UILabelControl();
	virtual ~UILabelControl();

	// 생성
	void		CreateUILabelControl(unsigned int nIndex, UIText oText);		// UI Object 생성
	// 출력
	void		Render(int iWindowPosX = 0, int iWindowPosY = 0);				// Render
	// 영역 검사
	bool		CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);// 현재 영역에 위치하였는가?
	// 이동
	void		Move(int iXpos, int iYpos);										// 원하는 위치로 이동
	// 제어
	
	void		SetScale(int SizeX, int SizeY);									// 사이즈를 변경합니다.
	void		Show() {m_bDisplay = true;}										// 버튼을 보여줍니다.
	void		Hide() {m_bDisplay = false;}									// 버튼을 숨깁니다.
	void		EnableOn() {m_bEnable = true;}									// 버튼을 동작하게 합니다.
	void		EnableOff() {m_bEnable = false;}								// 버튼을 동작하지 않게 합니다.
	void		CheckRegion(bool val) {m_bCheckRegion = val;}					// 제어영역 감지여부 셋팅
	void		CheckMouseDown(bool val) {m_bCheckMouseDown = val;}				// 제어영역 감지여부 셋팅
	HT_RECT		GetUILabelControlPos();											// 위치를 얻어온다.
	CHTString	GetText() {return m_Text.strTitle;}								// 문자열을 반환한다. 
	void		SetText(CHTString str);											// 문자열을 설정한다.
	void		SetTextColor(HT_COLOR clr)	{m_Text.TextColor = clr;}			// 문자열 색상을 설정한다.
	void		SetTextShadowColor(HT_COLOR clr) {m_Text.TextShadowColor = clr;}// 문자열 그림자 색상을 설정한다.
	void		SetArrangement(int iDirection) {m_Direction = iDirection; SetTextArrangement(iDirection);}		// 문자열을 원하는 방향으로 배치합니다.

	// 정보제공
	bool		isRegion() {return m_bCheckRegion;}					// 현재 영역이 반응중인가?
	bool		isMouseDown() {return m_bCheckMouseDown;}			// 현재 영역이 반응중인가?

};

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Long Label Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UILongLabelControl
{
private:
	// Texture Information
	UILongText			m_Text;					// Text 정보

	bool				m_bEnable;				// true = 입력 처리가능 / false = 입력 처리무시
	bool				m_bDisplay;				// true = 출력 가능 / false = 출력 안함

	bool				m_bCheckRegion;			// 제어 영역에 마우스무브 중인지 여부
	bool				m_bCheckMouseDown;		// 제어 영역에 마우스다운 중인지 여부

	int					TextPosX;				// 옵션 적용된 최종 텍스트 위치X
	int					TextPosY;				// 옵션 적용된 최종 텍스트 위치Y
	int					m_Direction;			// 배치방식

	void		SetTextArrangement(int iDirection);								// 해당범위 내에서 원하는 방향으로 배치합니다.

public:
	unsigned int		m_nIndex;				// 컨트롤 고유 인덱스

	UILongLabelControl();
	virtual ~UILongLabelControl();

	// 생성
	void		CreateUILabelControl(unsigned int nIndex, UILongText oText);		// UI Object 생성
	// 출력
	void		Render(int iWindowPosX = 0, int iWindowPosY = 0);				// Render
	// 영역 검사
	bool		CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);// 현재 영역에 위치하였는가?
	// 이동
	void		Move(int iXpos, int iYpos);										// 원하는 위치로 이동
	// 제어
	
	void		SetScale(int SizeX, int SizeY);									// 사이즈를 변경합니다.
	void		Show() {m_bDisplay = true;}										// 버튼을 보여줍니다.
	void		Hide() {m_bDisplay = false;}									// 버튼을 숨깁니다.
	void		EnableOn() {m_bEnable = true;}									// 버튼을 동작하게 합니다.
	void		EnableOff() {m_bEnable = false;}								// 버튼을 동작하지 않게 합니다.
	void		CheckRegion(bool val) {m_bCheckRegion = val;}					// 제어영역 감지여부 셋팅
	void		CheckMouseDown(bool val) {m_bCheckMouseDown = val;}				// 제어영역 감지여부 셋팅
	HT_RECT		GetUILabelControlPos();											// 위치를 얻어온다.
	HTtchar*	GetText() {return m_Text.strTitle;}								// 문자열을 반환한다. 
	void		SetText(HTtchar str[]);											// 문자열을 설정한다.
	void		SetTextColor(HT_COLOR clr)	{m_Text.TextColor = clr;}			// 문자열 색상을 설정한다.
	void		SetTextShadowColor(HT_COLOR clr) {m_Text.TextShadowColor = clr;}// 문자열 그림자 색상을 설정한다.
	void		SetArrangement(int iDirection) {m_Direction = iDirection; SetTextArrangement(iDirection);}		// 문자열을 원하는 방향으로 배치합니다.

	// 정보제공
	bool		isRegion() {return m_bCheckRegion;}					// 현재 영역이 반응중인가?
	bool		isMouseDown() {return m_bCheckMouseDown;}			// 현재 영역이 반응중인가?

};

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI ToolTip Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UIToolTipControl
{
private:
	bool				m_bEnable;				// true = 입력 처리가능 / false = 입력 처리무시
	bool				m_bDisplay;				// true = 출력 가능 / false = 출력 안함
	DWORD				m_dToolTipDelayTime;	// 툴팁 출력되는 시간 설정
	DWORD				m_dToolTipStartTime;	// 툴팁 시작시간 저장
	unsigned int		m_iLineIndex;			// 라인 인덱스 (문자열 갯수)

	int					m_SizeX;				// 툴팁 사이즈 X
	int					m_SizeY;				// 툴팁 사이즈 Y

	UITextureControl*	Body;					// 백그라운드 영역
	//UILabelControl*		Text;					// 툴팁 설명 텍스트

	std::list<UILabelControl*> m_UIToolTipLabelControl;		// 툴팁 설명 텍스트 (복수개를 가진다- 확장 버전)
	

public:
	// [Button]
	unsigned int		m_nIndex;				// 툴팁 고유 인덱스

	// [함수]
	UIToolTipControl();
	virtual ~UIToolTipControl();

	// 생성
	void CreateUIToolTipControl(unsigned int nIndex, int iXPos, int iYPos, CHTString str );	// 툴팁을 생성합니다.
	// 출력
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);	// 툴팁을 출력합니다. (텍스처)
	void RenderText(int iWindowPosX = 0, int iWindowPosY = 0);	// 툴팁을 출력합니다. (텍스트)
	// 영역 검사
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// 영역 검사
	// 이동
	void Move(int iXpos, int iYpos);			// 툴팁을 이동시킵니다.
	// 제어
	void SetStartTime();						// 툴팁 시간 카운트를 시작합니다.
	void SetText(CHTString str, int nIndex = 1);// 툴팁의 내용을 변경합니다.
	bool CheckOutputTime();						// 툴팁을 출력해도 되는지 여부알림
	void Show() {m_bDisplay = true; this->SetStartTime();}			// 툴팁을 보여줍니다.
	void Hide() {m_bDisplay = false;}			// 툴팁을 숨깁니다.
	void EnableOn() {m_bEnable = true;}			// 툴팁을 동작하게 합니다.
	void EnableOff() {m_bEnable = false;}		// 툴팁을 동작하지 않게 합니다.

	//확장툴팁
	void CreateLabelControl(unsigned int nIndex, UIText oText);			// 라벨 컨트롤 생성
	void DeleteLabelControl(unsigned int nIndex);						// 라벨 컨트롤 제거
	void SetTextLabelControl(unsigned int nIndex, CHTString str);		// 라벨 컨트롤의 텍스트 변경
	void SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr);	// 라벨 컨트롤의 텍스트컬러 변경
	void SetTextLabelControlIndex(unsigned int nIndex);					// 인덱스 강제 설정


	//void SetToolTipStr(int Index, CHTString str, HT_COLOR clr);		// 해당 라인의 툴팁 내용과 색상을 변경합니다.
	//void AddToolTipStr(int Index);									// 특정 스트링 라인 하나를 추가합니다.
	//void DelToolTipStr(int Index);									// 특정 스트링 라인 하나를 뺍니다.

};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Button Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UIButtonControl
{
private:
	
	bool				m_bDisplay;				// true = 출력 가능 / false = 출력 안함
	bool				m_bToolTip;				// true = 툴팁 사용 / false = 툴팁 사용안함
	bool				m_bEnter;				// true = 엔터 사용 / false = 엔터 사용안함
	int					m_iButtonState;			// 0 = Normal상태, 1 = 항상 켜짐 상태, 2 = 항상 꺼짐 상태, 3 = 깜박이는 상태, 4 = 박스버튼용 (생성시 TextureID를 -1로 설정할것)

	UITextureControl*	ButtonNormal;			// 일반상태
	UITextureControl*	ButtonOver;				// 마우스 위치 타겟시
	UITextureControl*	ButtonDown;				// 마우스 버튼 다운시

	DWORD				m_dFlashButtonOnDelayTime;	// 커서 켜지는 시간 0.5초후 발동
	DWORD				m_dFlashButtonOffDelayTime;	// 커서 꺼지는 시간 1초후 발동
public:
	bool				m_bEnable;				// true = 입력 처리가능 / false = 입력 처리무시
	UIToolTipControl*	ToolTip;				// 버튼 툴팁 제공

	// [Button]
	unsigned int		m_nIndex;				// 버튼 고유 인덱스
	int					m_nMode;				// 출력모드 ( 0 = 일반 버튼처럼 동작, 1 = 미사용 )
	int					m_nButtonState;			// 출력모드 ( 0 = 노말, 1 = 오버, 2= 다운)
	DWORD				m_dFlashButtonStartTime;	// 깜박임 버튼 시작시간

	// [함수]
	UIButtonControl();
	virtual ~UIButtonControl();

	// 생성
	void CreateUIButtonControl(unsigned int nIndex, UITexture oTexture[3] );	// 버튼을 생성합니다.
	// 출력
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);	// 버튼을 출력합니다. (텍스처)
	void RenderTextureToolTip(int iWindowPosX = 0, int iWindowPosY = 0);	// 툴팁을 출력합니다. (텍스처)
	void RenderText(int iWindowPosX = 0, int iWindowPosY = 0);	// 버튼을 출력합니다. (텍스트)

	// 영역 검사
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// 영역 검사
	// 이동
	void Move(int iXpos, int iYpos);				// 버튼을 이동시킵니다.
	void SetScale(int iSizeX, int iSizeY);			// 원하는 크기로 조절
	// 제어
	void Show() {m_bDisplay = true;}				// 버튼을 보여줍니다.
	void Hide() {m_bDisplay = false;}				// 버튼을 숨깁니다.
	void EnableOn() {m_bEnable = true;}				// 버튼을 동작하게 합니다.
	void EnableOff() {m_bEnable = false;}			// 버튼을 동작하지 않게 합니다.

	void SetButtonNormal();
	void SetButtonOver();
	void SetButtonDown();
	
	void SetButtonState(int iCheck) {m_iButtonState = iCheck;}	// 버튼상태를 변경합니다.
	void SetToolTipMove(int iXPos, int iYPos);		// 툴팁의 출력위치를 변경합니다.
	void SetToolTipStr(CHTString str);				// 툴팁의 내용을 변경합니다.
	void SetToolTipOn() {ToolTip->EnableOn();}		// 툴팁을 나오게 합니다.
	void SetToolTipOff() {ToolTip->EnableOff();}	// 툴팁을 나오지 않게 합니다.
	void SetTextLabelControl(unsigned int nIndex, CHTString str) {ToolTip->SetTextLabelControl(nIndex, str);}
	void SetTextLabelControlIndex(unsigned int nIndex) {ToolTip->SetTextLabelControlIndex(nIndex);}
	void SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr) {ToolTip->SetTextColorLabelControl(nIndex, clr);}

	void SetEnterOn() {m_bEnter = true;}			// 엔터키로 누르는 효과를 발생시킵니다.
	void SetEnterOff() {m_bEnter = false;}			// 엔터키로 누르는 효과를 끕니다.


	// 정보제공
	bool isBackgroundMouseDown() {return this->ButtonNormal->isRegion();}
	bool isEnterOn() {return m_bEnter;}
	bool isEnableOn() {return m_bEnable;}
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI ScrollBar Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UIScrollBarControl
{
private:
	bool				m_bEnable;				// true = 입력 처리가능 / false = 입력 처리무시
	bool				m_bDisplay;				// true = 출력 가능 / false = 출력 안함

	UITextureControl*	Line;					// 라인 텍스처
	UITextureControl*	Image;					// 스크롤바

public:
	UIButtonControl*	Arrow1;					// 화살표1
	UIButtonControl*	Arrow2;					// 화살표2

	unsigned int		m_nPosX;				// 길이 X
	unsigned int		m_nPosY;				// 길이 Y
	unsigned int		m_nLengthX;				// 길이 X
	unsigned int		m_nLengthY;				// 길이 Y

	unsigned int		m_nValue;				// 현재 값
	unsigned int		m_nMaxValue;			// 최대 값

	unsigned int		m_nIndex;				// 버튼 고유 인덱스
	int					m_nType;				// 출력모드 ( 0 = 수직, 1 = 수평 )

	// [함수]
	UIScrollBarControl();
	virtual ~UIScrollBarControl();

	// 생성
	void CreateUIScrollBarControl(unsigned int nIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType);
	// 출력
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);
	void RenderText(int iWindowPosX = 0, int iWindowPosY = 0);										// 버튼을 출력합니다. (텍스처)
	void RenderTextureToolTip(int iWindowPosX = 0, int iWindowPosY = 0);
	
	// 영역 검사
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// 영역 검사
	// 이동
	void Move(int iXpos, int iYpos);															// 스크롤바를 이동시킵니다.
	void MoveImage(int iXPos, int iYPos);

	void MoveBar(int iXpos, int iYpos);															// 스크롤바 버튼만 이동시킵니다.

	// 제어
	void Show() {m_bDisplay = true;}															// 스크롤바를 보여줍니다.
	void Hide() {m_bDisplay = false;}															// 스크롤바를 숨깁니다.
	void EnableOn() {m_bEnable = true;}															// 스크롤바를 동작하게 합니다.
	void EnableOff() {m_bEnable = false;}														// 스크롤바를 동작하지 않게 합니다.
	
	void SetMaxValue(int iValue) {m_nMaxValue = iValue; UpdateScrollBar();}
	int	 GetMaxValue() {return m_nMaxValue;}
	void SetValue(int iValue) {m_nValue = iValue; UpdateScrollBar();}
	int	 GetValue() {return m_nValue;}
	void UpdateScrollBar();

	void CheckRegion(bool val) {Image->CheckRegion(val);}		// 제어영역 감지여부 셋팅
	void CheckMouseDown(bool val) {Image->CheckMouseDown(val);}	// 제어영역 감지여부 셋팅
	//void SetSlotBoxControl(int iTextureID);						// 해당 텍스처로 셋팅합니다.

	// 정보제공
	bool		isRegion() {return Image->isRegion();}					// 현재 영역이 반응중인가?
	bool		isMouseDown() {return Image->isMouseDown();}			// 현재 영역이 반응중인가?
	HTvector3	GetUIScrollBarControlPos();							// 위치를 얻어온다.
	int			GetType() {return m_nType;}							// 위치를 얻어온다.
	//int			GetUISlotTextureID() {return Image->GetTextureID();}	// 텍스처 아이디를 얻어온다.

};




// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI SlotBox Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UISlotBoxControl
{
private:
	bool				m_bEnable;				// true = 입력 처리가능 / false = 입력 처리무시
	bool				m_bDisplay;				// true = 출력 가능 / false = 출력 안함
	bool				m_bFirstMove;			// true = 처음 움직임 시도함 / false = 움직이고 있는중
	bool				m_bMouseOver;			// true = 마우스가 오버됨	/ false = 마우스가 오버되지 않음
	bool				m_bToolTip;				// true = 툴팁 사용 / false = 툴팁 사용안함
	bool				m_bFixedIcon;			// true = 고정됨 / false = 움직임 가능

	UITextureControl*	Slot;					// 슬롯 (투명)
	UITextureControl*	Fx;						// 쿨타임 시각효과 이미지
	UITextureControl*	Enable;					// 사용여부에 따른 화면 표시 이미지
	UITextureControl*	Image;					// 슬롯에 들어갈 텍스처

	UIToolTipControl*	ToolTip;				// 버튼 툴팁 제공

//	int					m_SourWindowNo;

	DWORD				dwDealyTime;					// 딜레이 타임
	DWORD				dwSetTime;						// 카운트 시작 시간 설정
	DWORD				dwFrameTime;					// 쿨타임 이미지 한장 보여줄 시간
	DWORD				dwTotalFrameTime;				// 쿨타임 누적시간 (내부계산용)
	int					iCoolTimePos;					// 쿨타임 내부처리용
	bool				m_bCoolTime;					// 쿨타임 여부

	int					m_AddPosX;						// 슬롯박스에서 추가 이동된 X좌표
	int					m_AddPosY;						// 슬롯박스에서 추가 이동된 Y좌표


public:
	bool				m_bEnableCheck;			// 사용불가 체크시 화면에 출력여부 결정 (true = 붉은색 출력, false = 없음)
	int					m_nIndex;

		// [함수]
	UISlotBoxControl();
	virtual ~UISlotBoxControl();

	// 생성
	void CreateUISlotBoxControl(unsigned int nIndex, UITexture oTexture);// 슬롯박스를 생성합니다.
	// 출력
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);				// 슬롯박스를 출력합니다.
	void RenderTextureToolTip(int iWindowPosX = 0, int iWindowPosY = 0);	// 툴팁을 출력합니다. (텍스처)
	void RenderText(int iWindowPosX = 0, int iWindowPosY = 0);	// 버튼을 출력합니다. (텍스트)

	// 영역 검사
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// 영역 검사
	// 이동
	void Move(int iXpos, int iYpos);									// 슬롯박스를 이동시킵니다.
	void MoveImage(int iXpos, int iYpos);								// 슬롯박스를 이동시킵니다.

	// 제어
	void Show() {m_bDisplay = true;}									// 슬롯박스를 보여줍니다.
	void Hide() {m_bDisplay = false;}									// 슬롯박스를 숨깁니다.
	void EnableOn() {m_bEnable = true;}									// 슬롯박스를 동작하게 합니다.
	void EnableOff() {m_bEnable = false;}								// 슬롯박스를 동작하지 않게 합니다.
	void CheckRegion(bool val) {Slot->CheckRegion(val);}				// 제어영역 감지여부 셋팅
	void CheckMouseDown(bool val) {Slot->CheckMouseDown(val);}			// 제어영역 감지여부 셋팅
	void CheckMouseRDown(bool val) {Slot->CheckMouseRDown(val);}		// 제어영역 감지여부 셋팅
	void CheckFirstMove(bool val) {m_bFirstMove = val;}					// 처음 움직임을 시도하는가 여부체크
	void CheckMouseOver(bool val) {m_bMouseOver = val;}					// 마우스 오버 됨, 오버 안됨 체크
	void SetSlotBoxControl(int iTextureID, int iLayer = 2050 );// 해당 텍스처로 셋팅합니다.
	void SetSlotBoxCoolTime(DWORD DealyTime, DWORD PastTime = 0);		// 슬롯박스의 쿨타임 설정
	void SetSlotBoxCoolTimeCancel();									// 슬롯박스의 쿨타임 해제
	bool isSlotBoxCoolTime();											// 슬롯박스가 쿨타임중인지?
	bool isEnableOn() {return m_bEnable;}								// 현재 사용가능한가?
	bool isFirstMove() {return m_bFirstMove;}
	bool isMouseOver() {return m_bMouseOver;}
	bool isFixedIcon() {return m_bFixedIcon;}
	void SetSlotBoxImageFixed(bool bFixedIcon) {m_bFixedIcon = bFixedIcon;}
	bool CheckTime();													// 시간을 체크하여 시간에 맞게 랜더이미지를 생성합니다.
	void SetSlotBoxControlPosImage(int iPosX, int iPosY );				// 슬롯박스의 아이콘 위치 재설정
	void SetSlotBoxControlEnable(bool bEnable);							// 슬롯박스 사용여부 결정

	// 툴팁 관련
	void SetTextLabelControl(unsigned int nIndex, CHTString str) {ToolTip->SetTextLabelControl(nIndex, str);}
	void SetTextLabelControlIndex(unsigned int nIndex) {ToolTip->SetTextLabelControlIndex(nIndex);}
	void SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr) {ToolTip->SetTextColorLabelControl(nIndex, clr);}
	void SetToolTipOn() {ToolTip->EnableOn();}		// 툴팁을 나오게 합니다.
	void SetToolTipOff() {ToolTip->EnableOff();}	// 툴팁을 나오지 않게 합니다.
	void ToolTipHide();
	void ToolTipShow();

	// 정보제공
	bool		isRegion() {return Slot->isRegion();}					// 현재 영역이 반응중인가?
	bool		isMouseDown() {return Slot->isMouseDown();}				// 현재 영역이 반응중인가?
	bool		isMouseRDown() {return Slot->isMouseRDown();}			// 현재 영역이 반응중인가?
	HTvector3	GetUISlotBoxControlPos();								// 위치를 얻어온다.
	HTvector3	GetUISlotImageControlPos();								// 위치를 얻어온다.
	int			GetUISlotTextureID() {return Image->GetTextureID();}	// 텍스처 아이디를 얻어온다.
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI EditBox Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UIEditBoxControl
{
private:
	bool				m_bEnable;						// true = 입력 처리가능 / false = 입력 처리무시
	bool				m_bDisplay;						// true = 출력 가능 / false = 출력 안함
	bool				m_bFocus;						// true = 포커스 잡힙 / false = 포커스 꺼짐
	bool				m_bCursor;						// true = 커서 온 / false = 커서 오프


	DWORD				dwDealyTime;					// 딜레이 타임
	DWORD				dwSetTime;						// 카운트 시작 시간 설정

	int					m_Xpos;							// 커서 X위치
	int					m_YPos;							// 커서 Y위치
	int					m_nMode;						// 모드 (0 = 일반 모드, 1 = 패스워드 출력 모드)

	DWORD				m_dEditBoxCursorOnDelayTime;	// 에디터 박스 커서 온 시간 설정
	DWORD				m_dEditBoxCursorOffDelayTime;	// 에디터 박스 커서 오프 시간 설정
	DWORD				m_dEditBoxStartTime;			// 현재 시간

	UITextureControl*	Body;							// 에디트 박스 배경 (고정)
	UITextureControl*	Cursor;							// 커서 텍스처 (고정)
	UITextureControl*	ShiftRegion;					// 쉬프트 영역 텍스처 (고정)
	UILabelControl*		Text;							// 타이틀 스트링
	
	void OutputText();
	//HWND				g_hEdit;						// 에디트 핸들

public:
	CHTString			m_str;							// 에디트박스내 실제 문자열 str
	bool				m_bRegion;						// true = 커서 온 / false = 커서 오프
	int					m_XPibot;						// 커서 X피봇
	int					m_ImeNo;						// 포커스 활성화시 입력모드
	int					m_iLimitTextSize;				// 글자 길이 제한 사이즈

	// [함수]
	UIEditBoxControl();
	virtual ~UIEditBoxControl();

	unsigned int		m_nIndex;						// 버튼 고유 인덱스
	
	// 생성
	void CreateUIEditBoxControl(unsigned int nIndex, UITexture oTexture, UIText oText, int iStyle = 0);	// 에디터박스를 생성합니다.

	// 제어
	void Show() {m_bDisplay = true;}										// 에디터박스를 보여줍니다.
	void Hide() {m_bDisplay = false;}										// 에디터박스를 숨깁니다.
	void EnableOn() {m_bEnable = true;}										// 에디터박스를 동작하게 합니다.
	void EnableOff() {m_bEnable = false;}									// 에디터박스를 동작하지 않게 합니다.
	void SetFocusOn();														// 에디터박스를 입력상태로 만듭니다.
	void SetFocusOff();														// 에디터박스를 입력불가 상태로 만듭니다.
	void SetCursorOn() {m_bCursor = true;}									// 에디터박스의 커서가 보이는 상태
	void SetCursorOff() {m_bCursor = false;}								// 에디터박스의 커서가 안보이는 상태
	void SetStartTime()	;													// 커서 깜박임 시간 측정 함수
	bool CheckOutputTime();													// 커서를 출력해도 되는지 여부알림
	void SetText(CHTString str);											// 텍스트를 삽입합니다.
	void UpdateText(CHTString strMsg);										// 내부 컨트롤의 정보를 업데이트합니다.
	void SetTextColor(HT_COLOR clr) {Text->SetTextColor(clr);}				// 텍스트 색상 변경 
	void SetTextShadowColor(HT_COLOR clr) {Text->SetTextShadowColor(clr);}	// 텍스트 그림자색상 변경
	CHTString GetText() {return m_str;}										// 텍스트를 가지고 옵니다.
	void SetMode(int iMode = 0) { m_nMode = iMode; }						// 에디트 모드를 설정합니다.
	void SetLimitText(unsigned int uiSize);									// 입력 글자 길이를 제한합니다.
	void SetFocusOnIME(int iIME);											// 0 = 영어, 1 = 한국어, 2 = 미사용

	// 이동
	void Move(int iXpos, int iYpos);										// 에디터박스를 이동시킵니다.
	void MoveCursor(int iXpos, int iYpos);									// 커서를 이동시킵니다.
	
	// 영역 검사 및 출력
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// 영역 검사
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);			// 에디터박스 출력합니다. (텍스처)
	void RenderText(int iWindowPosX = 0, int iWindowPosY = 0);				// 에디터박스 출력합니다. (텍스트)
	
	// 정보제공
	bool isFocusOn() {return m_bFocus;}										// 현재 입력 상태인가?
	bool isCursorOn() {return m_bCursor;}									// 현재 입력 상태인가?
	bool isBackgroundMouseDown() {return Body->isRegion();}					// 현재 영역에 들어와 있는가?
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Timer Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UITimerControl
{
private:
	bool				m_bEnable;						// true = 입력 처리가능 / false = 입력 처리무시

public:
	bool				m_OnlyOne;						// true = 한번만 실행됨 // false = 반복됨
	DWORD				dwDealyTime;					// 딜레이 타임
	DWORD				dwSetTime;						// 카운트 시작 시간 설정
	unsigned int		m_nIndex;						// 타이머 고유 인덱스

	UITimerControl();
	virtual ~UITimerControl();
	
	// 생성
	void CreateUITimerControl(unsigned int nIndex, DWORD dwSetTime, int iStyle = 0);	// 타이머를 생성합니다.
	void EnableOn() {m_bEnable = true; dwSetTime = timeGetTime();}						// 타이머를 동작하게 합니다.
	void EnableOff() {m_bEnable = false;}												// 타이머를 동작하지 않게 합니다.
	bool CheckTime(); 
	void SetRepeat(bool OnlyOne) {m_OnlyOne = OnlyOne;}									// 반복할지 여부 결정
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI CheckBox Control
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UICheckBoxControl
{
private:
	bool				m_bEnable;						// true = 입력 처리가능 / false = 입력 처리무시
	bool				m_bDisplay;						// true = 보임 / false = 보이지않음
	
	UITextureControl*	Body;							// 체크박스 이미지 / 영역
	UITextureControl*	Check;							// 체크 이미지

public:
	int					m_nIndex;
	bool				m_bValue;						// 체크 여부

	UICheckBoxControl();
	virtual ~UICheckBoxControl();
	
	// 생성, 제어
	void CreateUICheckBoxControl(unsigned int nIndex, int XPos, int YPos, bool bValue = false, int BorderTextureID = 143, int CheckTextureID = 175, int SizeX = 14, int SizeY = 14);	// 체크박스를 생성합니다.
	void EnableOn() {m_bEnable = true;}								// 체크박스 사용가능
	void EnableOff() {m_bEnable = false;}							// 체크박스 사용불가
	void Show() {m_bDisplay = true;}								// 체크박스 출력
	void Hide() {m_bDisplay = false;}								// 체크박스 출력안함
	bool GetValue() {return m_bValue;}								// 현재 값 여부 알기
	void SetValue(bool bValue);										// 현재 값 셋팅

	// 이동, 출력
	void Move(int iXpos, int iYpos);															// 이동
	bool CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// 영역검사
	bool isMouseDown() {return Body->isMouseDown();}
	void CheckMouseDown(bool bCheck) {Body->CheckMouseDown(bCheck);}
	void RenderTexture(int iWindowPosX = 0, int iWindowPosY = 0);								// 랜더

};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Window
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class UIWindow
{
private:
	unsigned int		m_nMaxTextureControl;
	unsigned int		m_nMaxButtonControl;
	unsigned int		m_nMaxLabelControl;
	unsigned int		m_nMaxEditBoxControl;

	bool				m_bEnable;						// true = 입력 처리가능 / false = 입력 처리무시
	bool				m_bDisplay;						// true = 출력 가능 / false = 출력 안함
	bool				m_bFocus;						// 현재 활성화 상태인지 아닌지 구별한다.
	bool				m_bSlotBox;						// true = 슬롯박스 이동중 / false = 이동없음
	bool				m_bMovingRegionUsing;			// 추가 움직임 가능영역 사용 여부 

	
	UITextureControl*	MovingRegion;					// 움직임 가능영역 
	UITextureControl*	TitleBar;						// 타이틀바 영역 객체 (윈도우를 움직일 수 있는 부분 - 고정)
	UITextureControl*	ScaleBar;						// 윈도우 영역 객체 (고정)
	UIButtonControl*	CloseButton;					// 창닫기 버튼 (고정)
	UILabelControl*		TitleStr;						// 타이틀 스트링

	// [Add Controls]
	std::list<UITextureControl*> m_UITextureControl;	// Picture Box Controls
	std::list<UIButtonControl*> m_UIButtonControl;		// Button Controls
	std::list<UILabelControl*> m_UILabelControl;		// Label Controls
	std::list<UILongLabelControl*> m_UILongLabelControl;// Long Label Controls
	std::list<UIEditBoxControl*> m_UIEditBoxControl;	// EditBox Controls
	std::list<UISlotBoxControl*> m_UISlotBoxControl;	// SlotBox Controls
	std::list<UIScrollBarControl*> m_UIScrollBarControl;// ScrollBar Controls
	std::list<UITimerControl*> m_UITimerControl;		// Timer Controls
	std::list<UICheckBoxControl*> m_UICheckBoxControl;	// CheckBox Controls


	// [출력 정보]
	int					iMouseButtonDownXPos;			// 해당 윈도우내의 마우스 좌표값X
	int					iMouseButtonDownYPos;			// 해당 윈도우내의 마우스 좌표값Y
	int					iMouseButtonDownXPosTail;		// 해당 윈도우내의 마우스 좌표값X (끝좌표로부터 시작)
	int					iMouseButtonDownYPosTail;		// 해당 윈도우내의 마우스 좌표값Y (끝좌표로부터 시작)
	int					m_nMode;						// 출력모드 ( 0 = 보디만, 1 = 일반창(보더) )
	func_t*				m_ptr;							// 윈도우 메시지처리를 위한 함수 포인터

	std::list<unsigned int> m_UIMagnetIndex;				// 자신을 자석으로 사용하는 다른 윈도우들
	bool					m_bMagnet;						// 자석기능 사용 여부
	bool					m_bMagnetUsingPro;					// 내부 처리용
	bool					m_bMagnetUsing;					// 현재 자석 작동중인지?
	int						m_iMagnetWindowIndex;			// 자석으로 작용하는 윈도우 인덱스

public:
	UITextureControl*	Body;							// 윈도우 영역 객체 (고정)

	// 배경색
	int BackgroundMove;

	// [Window]
	bool					m_bBackgroundDownEnable;		// 윈도우 배경 클릭 가능여부 결정
	int						m_posX, m_posY;					// 자석기능 위치 계산을 위한 변수
	int						AdxPosX, AdxPosY;				// 무빙시 얼마나 움직였는지 그양을 저장하는 벡터
	int						AdxPosX2, AdxPosY2;

	unsigned int		m_nIndex;						// 윈도우 고유 인덱스
	int					iWindowPosX;					// 해당 윈도우 시작 좌표값X
	int					iWindowPosY;					// 해당 윈도우 시작 좌표값Y

	// [함수]
	UIWindow();
	virtual ~UIWindow();

	void CreateUIWindow(unsigned int nIndex, CHTString str, int iPosX, int iPosY, int iSizeX, int iSizeY, HT_COLOR dwColor, func_t* ptr, int nMode = 0);	// 윈도우를 생성합니다.
	func_t* GetMessageProcedure();									// 메시지 프로시져인 함수 포인터를 반환합니다.
	void SetBorderTexture(int iSizeX, int iSizeY, int nType = 0);	// 윈도우의 기본 테두리 스케일을 설정합니다.
	void Render();													// 윈도우를 출력합니다.
	void Render_ToolTip();											// 2차 랜더 함수 (툴팁같은 최상위 윈도우를 랜더합니다.)
	void MoveWindow(int iXpos, int iYpos);							// 윈도우를 이동시킵니다.
	void ScaleWindow(int iSizeX, int iSizeY);						// 윈도우의 사이즈를 조절합니다.
	void Show() {m_bDisplay = true;}								// 윈도우를 보여줍니다.
	void Hide() {m_bDisplay = false;}								// 윈도우를 숨깁니다.
	void EnableOn() {m_bEnable = true;}								// 윈도우를 동작하게 합니다.
	void EnableOff() {m_bEnable = false;}							// 윈도우를 동작하지 않게 합니다.
	bool isDisplay() {return m_bDisplay;}							// 윈도우의 디스플레이 상태를 리턴합니다.
	bool isEnable() {return m_bEnable;}								// 윈도우의 동작상태를 리턴합니다.

	void SetBackgroundColor(HT_COLOR clr);							// 윈도우의 배경색을 설정합니다.
	
	// Magnet
	void SetMagnet(unsigned int nTargetIndex);						// 자석기능 설정 (0 = 취소, -1 = 바탕화면)
	void MagnetMgr(unsigned int nTargetIndex, bool bInsert);		// 타겟 윈도우 bInsert = true 삽입 false = 삭제
	void SetMagnetProcessing();										// 타겟 윈도우에 붙는지 처리한다.
	void SetChildMagnetProcessing();								// 자신에게 붙은 윈도우들을 처리한다.
	bool GetMagnetState() {return m_bMagnetUsing;}					// 자석상태중인지 아닌지를 반환한다.
	void SetMagnetState(bool bState) {m_bMagnetUsing = bState;}		// 현재 상태를 강제 변경합니다.

	// Texture
	void CreateTextureControl(unsigned int nIndex, UITexture oTexture);	// 컨트롤을 생성합니다.
	void DeleteTextureControl(unsigned int nIndex);												// 컨트롤을 삭제합니다.
	void SetRegionTextureControl(unsigned int nIndex, int iXpos, int iYpos, int iSizeX, int iSizeY);
	void SetTextureControlScale(unsigned int nIndex, int iSizeX = 0, int iSizeY = 0, int iOSizeX = 1, int iOSizeY = 1);
	void SetTextureControlImage(unsigned int nIndex, int iTextureID );				// 텍스처를 변경합니다.
	void SetTextureColor(unsigned int nIndex, HT_COLOR clr );						// 텍스처 컬러를 변경합니다.
	void SetTextureControlDisplay(unsigned int nControlIndex, bool bOn);					// 텍스처 출력 온오프 설정 (true = 온 . false = 오프)
	HTvector3 GetTextureControlPos(unsigned int nControlIndex);							// 텍스처 컨트롤 좌표를 얻어옵니다.

	// CheckBox
	void CreateCheckBoxControl(unsigned int nIndex, int XPos, int YPos, bool bValue = false, int BorderTextureID = 143, int CheckTextureID = 175, int SizeX = 14, int SizeY = 14);	// 체크박스를 생성합니다.
	void DeleteCheckBoxControl(unsigned int nIndex);												// 컨트롤을 삭제합니다.
	void SetCheckBoxControl(unsigned int nIndex, bool bCheck);		// 체크박스에 값을 설정
	bool GetCheckBoxControl(unsigned int nIndex);					// 체크박스의 값을 얻음

	// Label
	void CreateLabelControl(unsigned int nIndex, UIText oText);
	void DeleteLabelControl(unsigned int nIndex);
	void SetTextLabelControl(unsigned int nIndex, CHTString str);
	CHTString GetTextLabelControl(unsigned int nIndex);
	void SetTextColorLabelControl(unsigned int nIndex, HT_COLOR clr);
	void SetTextShadowColorLabelControl(unsigned int nIndex, HT_COLOR clr);
	void SetArrangementLabelControl(unsigned int nIndex, int iDirection);		// 문자열을 원하는 방향으로 배치합니다.

	// LongLabel
	void CreateLongLabelControl(unsigned int nIndex, UILongText oText);
	void DeleteLongLabelControl(unsigned int nIndex);
	void SetTextLongLabelControl(unsigned int nIndex, HTtchar str[]);
	HTtchar* GetTextLongLabelControl(unsigned int nIndex);
	void SetTextColorLongLabelControl(unsigned int nIndex, HT_COLOR clr);
	void SetTextShadowColorLongLabelControl(unsigned int nIndex, HT_COLOR clr);
	void SetArrangementLongLabelControl(unsigned int nIndex, int iDirection);		// 문자열을 원하는 방향으로 배치합니다.

	// EditBox
	void CreateEditBoxControl(unsigned int nIndex, UITexture oTexture, UIText oText, int iStyle = 0);
	void DeleteEditBoxControl(unsigned int nIndex);
	void SetTextEditBoxControl(unsigned int nIndex, CHTString str);				// 에디터 박스에 문자를 삽입합니다.
	CHTString GetTextEditBoxControl(unsigned int nIndex);						// 에디터 박스의 문자를 가지고 옵니다.
	void SetEditBoxControlMode(unsigned int nIndex, int iMode = 0);				// 에디트 모드를 설정합니다.
	void SetEditBoxControlLimitText(unsigned int nIndex, unsigned int uiSize);	// 에디트 박스의 문자길이를 제한합니다.
	void SetTextColorEditBoxControl(unsigned int nIndex, HT_COLOR clr);
	void SetTextShadowColorEditBoxControl(unsigned int nIndex, HT_COLOR clr);
	void EditBoxFocusAllOff();
	void EditBoxFocusOff(unsigned int nIndex);
	void EditBoxFocusOn(unsigned int nIndex);
	bool isEditBoxFocusOn(unsigned int nIndex);
	void SetEditBoxFocusOnIME(unsigned int nIndex, int iIME);				// 에디트박스에 포커스가 잡혀있을시 입력모드를 설정변경합니다.

	// SlotBox
	void CreateSlotBoxControl(unsigned int nIndex, UITexture oTexture);
	void DeleteSlotBoxControl(unsigned int nIndex);
	void SetSlotBoxControl(unsigned int nIndex, int TextureID, int iLayer = 2050);
	int	 CheckRegionWithSlotBoxPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// 내부처리용 (현재 위치에 슬롯이 존재하는가?)
	int	 GetUISlotTextureID(unsigned int nIndex);
	void SetSlotBoxCoolTime(unsigned int nIndex, DWORD DealyTime, DWORD PastTime = 0);	// 슬롯박스의 쿨타임 설정
	void SetSlotBoxCoolTimeCancel(unsigned int nIndex);	// 슬롯박스의 쿨타임 해제
	bool isSlotBoxCoolTime(unsigned int nIndex);		// 슬롯박스가 쿨타임중인지?
	void SetSlotBoxToolTipOn(unsigned int nControlIndex);// 슬롯박스 컨트롤에서 툴팁을 사용합니다.
	void SetSlotBoxToolTipOff(unsigned int nControlIndex);// 슬롯박스 컨트롤에서 툴팁을 사용하지 않습니다.
	void SetSlotBoxControlToolTipText(unsigned int nControlIndex, unsigned int nIndex, CHTString str);// 슬롯박스 툴팁의 해당 텍스트 설정(라인별)
	void SetSlotBoxControlTextIndex(unsigned int nControlIndex, unsigned int nIndex);// 슬롯박스 툴팁의 해당 출력 라인 인덱스 설정 (해당 라인까지만 출력함)
	void SetSlotBoxControlToolTipTextColor(unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr);// 슬롯박스 툴팁 해당 라인 텍스트 색상 변경
	void SetSlotBoxControlPosImage(unsigned int nControlIndex, int iPosX = 3, int iPosY = 3);	// 슬롯박스의 아이콘 위치를 재설정합니다.
	void SetSlotBoxImageFixed(unsigned int nControlIndex, bool bFixedIcon);	// 슬롯박스 아이콘 움직임 고정 여부 설정
	void CancelSlotBoxImageMoving();
	void SetSlotBoxControlEnable(unsigned int nControlIndex, bool bEnable);	// 슬롯박스 사용여부 결정


	// ScrollBar
	void CreateScrollBarControl(unsigned int nIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType);
	void DeleteScrollBarControl(unsigned int nIndex);
	void SetScrollBarValue(unsigned int nIndex, int iValue);
	void SetScrollBarMaxValue(unsigned int nIndex, int iValue);
	int GetScrollBarValue(unsigned int nIndex);

	// Button
	void SetButtonToolTip(unsigned int nControlIndex, CHTString str);
	void SetButtonToolTipOn(unsigned int nControlIndex);
	void SetButtonToolTipOff(unsigned int nControlIndex);
	void SetButtonControlToolTipText(unsigned int nControlIndex, unsigned int nIndex, CHTString str);
	void SetButtonControlTextIndex(unsigned int nControlIndex, unsigned int nIndex);
	void SetButtonControlToolTipTextColor(unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr);
	void SetButtonEnterOn(unsigned int nControlIndex);				// 해당 버튼의 엔터기능을 킵니다.
	void SetButtonEnterOff(unsigned int nControlIndex);				// 해당 버튼의 엔터기능을 끕니다.
	void SetButtonEnable(unsigned int nControlIndex, bool bEnable);
	void CreateButtonControl(unsigned int nIndex, UITexture oTexture[3]);
	void DeleteButtonControl(unsigned int nIndex);
	void SetButtonControlState(unsigned int nIndex, int iCheck);
	
	// Input Interface
	int OnLButtonDown(int iXPos, int iYPos);
	int OnLButtonUp(int iXPos, int iYPos);
	bool OnRButtonDown(int iXPos, int iYPos);
	bool OnRButtonUp(int iXPos, int iYPos);
	bool OnKeyDown(WPARAM wParam);
	bool OnKeyUp(WPARAM wParam);
	bool OnChar(WPARAM wParam);
	bool OnMouseWheel(WPARAM wParam);
	bool OnSysCommand(WPARAM wParam);
	void OnMouseMove(int iXPos, int iYPos);
	void OnMouseMoveOnlyTop(int iXPos, int iYPos);
	
	// Timer
	void CreateTimerControl(unsigned int nIndex, DWORD dwSetTime, int iStyle = 0);
	void DeleteTimerControl(unsigned int nIndex);
	void EnableOnTimerControl(unsigned int nIndex);
	void EnableOffTimerControl(unsigned int nIndex);

	// Etc...
	void FocusOn();
	void FocusOff();

	// Window Region
	void SetMovingRegion(bool isOn, int iPosX, int iPosY, int iSizeX, int iSizeY);
	bool isBackgroundMouseDown() {return this->Body->isRegion();}
	bool CheckRegionWithPoint(int iXPos, int iYPos);	// 현재 영역에 위치하였는가?
	HTvector3	GetWindowPos();							// 위치를 얻어온다.
	HTvector3	GetWindowSize();						// 사이즈를 얻어온다.

};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << MessageBox Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
const int UI_WINDOW_MESSAGEBOX = 999;	// 메시지박스 인덱스 선언
class CHTUIMessageBox
{
private:

public:
	unsigned int	m_nIndex;								// 메시지 박스 인덱스
	unsigned int	m_nWindowIndex;							// 윈도우 인덱스

	int				m_nMode;								// 메시지박스 스타일

	CHTUIMessageBox(void);
	~CHTUIMessageBox(void);
	
	void		HT_vMessageBox(unsigned int nIndex, CHTString str, int nMode = 0);		// nMode = 0 확인버튼만, 1 = 확인/취소 버튼, 2 = 미사용...	
	static void HT_hrMessageBox_InputCheck(int iAction, int iTarget, int iTargetID);	// 입력 처리 함수 (UI 입력제어부)
	void		HT_vCloseMessageBox(int iTargetID);										// 메시지박스 제거관련 함수
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Status Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

const int UI_WINDOW_STATUS = _DIALOG_STATUS;	// 상태창 윈도우 인덱스 선언
class CHTUIStatus
{

private:
	static void DrawStatusLabel(int x, int y, int id, CHTString str);					// 편하게 작업하기 위한 함수(내부 디자인)
	void		HT_vNetWork_CSP_REQ_Increase_Chakra(int iBtnNo);						// 차크라 증가 요청 네트워크 함수
	
	PS_SCP_CHAR_PARAMS_CHANGE	m_sStatus_CharParms;
	S_SCP_RESP_UPDATE_UI		m_sStatus_CharInfo;

public:
	int					m_MessageBoxType;
	CHTUIStatus(void);
	~CHTUIStatus(void);

	void		HT_vStatus_Init();														// 처음 구동시 한번만 실행 (UI 생성부)
	void		HT_vStatus_WindowPopup();												// 처음 화면 팝업시 호출 (외부에서 필요할때 호출하는 함수)
	void		HT_vStatus_SetInfo();													// 화면 갱신시 호출 (UI 갱신부)
	static void HT_hrStatus_InputCheck(int iAction, int iTarget, int iTargetID);		// 입력 처리 함수 (UI 입력제어부)
	static void HT_hrStatus_InputCheck2(int iAction, int iTarget, int iTargetID);		// 입력 처리 함수 (UI 입력제어부)
	
	HTint		HT_nGetTotalPureChakra();		// 순수 총 차크라를 얻어옵니다.
	HTint		HT_nGetTotalChakra();			// 총 차크라를 얻어옵니다.

	void		HT_hrStatus_IncreaseChakra(int iBtnNo);									// 차크라 증가버튼 클릭시 호출되는 함수(예외처리는 이곳에)
	void		HT_vStatus_ChangeParams( PS_SCP_RESP_UPDATE_UI info );					// 스테이터스 갱신시 받음

	CHTString	HT_szStatus_GetTrimuriti(int iTrimuriti);								// 주신 스트링 얻기
	CHTString	HT_szStatus_GetCastClass(int iCaste);									// 카스트 스트링 얻기
	CHTString	HT_szStatus_GetJobName(int iClass1, int iClass2);						// 직업 스트링 얻기
	CHTString	HT_szStatus_GetTribe(int iTribe);										// 종족 스트링 얻기
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << NPC Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

const int UI_WINDOW_NPCWINDOW = _DIALOG_NPCWINDOW;	// 상태창 윈도우 인덱스 선언
class CHTUINPCWindow
{
private:
public:
	int				m_MessageBoxNo;
	int				m_StartPosY;
	int m_iButton;
	CHTUINPCWindow(void);
	~CHTUINPCWindow(void);

	void		HT_vNPCWindow_Init();														// 처음 구동시 한번만 실행 (UI 생성부)
	void		HT_vNPCWindow_WindowPopup();												// 처음 화면 팝업시 호출 (외부에서 필요할때 호출하는 함수)
	void		HT_vNPCWindow_SetInfo();													// 화면 갱신시 호출 (UI 갱신부)
	int			HT_vGetNPCWindow_ButtonNo() {return m_iButton;}								// 버튼값을 리턴합니다.
	static void HT_hrNPCWindow_InputCheck(int iAction, int iTarget, int iTargetID);			// 입력 처리 함수 (UI 입력제어부)
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Skill Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
typedef struct _SKILL_ICON
{
	HTint						m_iSkillIconNo1[6][4];
	HTint						m_iSkillIconNo2[6][4];
	HTint						m_iSkillIconNo3[6][4];
	HTint						m_iSkillIconNo4[6][4];
	
} _SKILL_ICON;

typedef struct _SKILL_ARROW
{
	HTint						m_iSkillArrow1[6][4];
	HTint						m_iSkillArrow2[6][4];
	HTint						m_iSkillArrow3[6][4];	
	HTint						m_iSkillArrow4[6][4];

} _SKILL_ARROW;

typedef struct _SKILL_INDEX
{
	HTint						m_iSkillIndex1[6][4];
	HTint						m_iSkillIndex2[6][4];
	HTint						m_iSkillIndex3[6][4];	
	HTint						m_iSkillIndex4[6][4];	

} _SKILL_INDEX;

const int UI_WINDOW_SKILL = _DIALOG_SKILL;	// 스킬창 윈도우 인덱스 선언
class CHTUISkillWindow
{
private:
	CHTString	m_strTitle[4];									// 텝 이름 (4개의 이름들)
	CHTString	m_strTribe;										// 텝 종족

public:
	int							m_SkillTabNo;					// 현재 스킬 텝 번호
	_SKILL_ICON					m_oSkillIcon;					// 스킬아이콘 배열구조체
	_SKILL_ARROW				m_oSkillArrow;					// 스킬화살표 배열구조체
	_SKILL_INDEX				m_oSkillIndex;					// 스킬인덱스 배열구조체
	int							m_ExtraSkillPoint;				// 잔여 스킬포인트
	int							m_ExtraTrimutiritiSkillPoint;	// 잔여 주신 스킬포인트
	int							m_byLevel;						// 스킬레벨
	int							m_byPlusLevel;					// 추가레벨 (효과로 인한)
	int							m_iSkillIcon;					// 스킬아이콘ID
	int							m_iSkillArrow;					// 스킬 화살표 ID
	CHTString					m_strSkillName;					// 스킬이름
	CHTString					m_strSkillContents;				// 스킬설명
	CHTString					m_strSkillType;					// 스킬타입 (패시브 / 액티브)

	CHTUISkillWindow(void);
	~CHTUISkillWindow(void);

	void		HT_vSkillWindow_Init();														// 처음 구동시 한번만 실행 (UI 생성부)
	void		HT_vSkillWindow_WindowPopup();												// 처음 화면 팝업시 호출 (외부에서 필요할때 호출하는 함수)
	void		HT_vSkillWindow_SetInfo();													// 화면 갱신시 호출 (UI 갱신부)
	static void HT_hrSkillWindow_InputCheck(int iAction, int iTarget, int iTargetID);			// 입력 처리 함수 (UI 입력제어부)
	
	bool		HT_vSetSkillInfoblank();					// 스킬정보 0으로 셋팅
	void		HT_vSkillDrawSkill(int iIndex, int iLevel, CHTString strName, CHTString strContemts, CHTString strType);
	void		HT_vSkillDrawTitle(int iIndex);
	void		HT_vSkillSetTitle(int iTribe);
	bool		HT_vGetSkillInfo(int iIndex);
	int			HT_vGetSkillLevel(DWORD iIndex);
	void		HT_vSkillUpdate(int iIndex);
	
	HTint		HT_nGetSkillPoint();						// 스킬 포인트를 얻어옵니다.
	HTint		HT_nGetGodSkillPoint();						// 주신 스킬 포인트를 얻어옵니다.

	DWORD		HT_vGetSkillIndex(int iSlotNo);				// 슬롯번호로 스킬 인덱스를 얻어옵니다.
	int			HT_vGetSkillIcon(DWORD iIndex);				// 인덱스로 스킬 아이콘을 얻어옵니다.
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Refine Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

const int UI_WINDOW_REFINE = _DIALOG_REFINE;	// 제련창 윈도우 인덱스 선언
class CHTUIRefineWindow
{
private:

public:
	int			m_SetItemNumber;
	int			m_iWindowIndex[5];
	int			m_iControlIndex[5];

	int			m_iRefineAniNo;				// 제련 애니메이션 인덱스 값
	int			m_nMessageBoxNo;						// 팝업된 메시지 박스는?

	CHTUIRefineWindow(void);
	~CHTUIRefineWindow(void);

	void		HT_vRefineWindow_WindowHide();												// 제련창 윈도우를 닫을때는 이 함수를 사용한다.
	void		HT_vRefineWindow_Init();														// 처음 구동시 한번만 실행 (UI 생성부)
	void		HT_vRefineWindow_WindowPopup();												// 처음 화면 팝업시 호출 (외부에서 필요할때 호출하는 함수)
	void		HT_vRefineWindow_SetInfo();													// 화면 갱신시 호출 (UI 갱신부)
	static void HT_hrRefineWindow_InputCheck(int iAction, int iTarget, int iTargetID);			// 입력 처리 함수 (UI 입력제어부)
};


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Quest Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#define	QUEST_MAX_NUM					60	// 현재 45까지 사용
#define QUEST_DESCRIPTION_MAXNUM		60	// 현재 58까지 사용

typedef struct _HT_QUEST_DESCRIPTION
{
	BYTE		byIndex;		// 퀘스트 번호
	CHTString	szTitle;		// 퀘스트 제목
	HTint		nStepNo;		// 단계 개수
	HTint		nStepNum[QUEST_DESCRIPTION_MAXNUM];		// 단계
	CHTString	szStepMsg[QUEST_DESCRIPTION_MAXNUM];	// 단계별 UI창에 나타내는 말
} HT_QUEST_DESCRIPTION;


const int UI_WINDOW_QUEST = _DIALOG_QUEST;	// 퀘스트 인덱스 선언
class CHTUIQuestWindow
{
private:
	HT_QUEST_DESCRIPTION		m_sQuestText[QUEST_MAX_NUM];		// 모든 퀘스트 이름과 단계별 설명 저장 변수

	CHTString					m_ProgressStr[QUEST_MAX_NUM];		// 수행중인 퀘스트명 저장
	CHTString					m_ProgressResultStr[QUEST_MAX_NUM];	// 수행중인 퀘스트명 보상내용 저장

	CHTString					m_CompleteStr[QUEST_MAX_NUM];		// 완료한 퀘스트명 저장
	CHTString					m_CompleteResultStr[QUEST_MAX_NUM];	// 수행중인 퀘스트명 보상내용 저장
	
	void		vSetInfo(int iTab);									// 화면 정보 갱신
	int			SetMonsterKillNo(HTint iIndex, HTint StepNo);		// 몬스터 숫자세어주는 함수
	
public:
	int							m_FocusIndex;						// 내용 보여줄 목록 인덱스
	bool						m_bFalshState;						// 메인바 퀘스트 버튼 깜박임 체크
	HTbyte						m_byQuest[MAX_EVENT_FLAG];
	int							m_iLastProgressIndex;				// 마지막 진행한 퀘스트 넘버
	bool						m_bReQuestItemUsingOne;				// 퀘스트 초기화 단독 사용 여부 체크

	bool						g_bMoonBang;						// 특정 퀘스트 깻는지 여부 저장 (외부에서 쓰기위함)

	CHTUIQuestWindow(void);
	~CHTUIQuestWindow(void);

	void		HT_vNetWork_CSP_REQ_Quest_DIALOG(DWORD dwDialogIndex, BYTE byResult);		// 튜토리얼 퀘스트 수행 요청 / 2차전직 요청
	void		HT_vNetWork_SCP_RESP_Quest_Dialog( PS_SCP_QUEST_DIALOG info );				// 퀘스트 관련 에러정보 받음
	void		HT_vNetWork_SCP_RESP_Quest_History( HTbyte byQuest[MAX_EVENT_FLAG] );		// 서버로부터 퀘스트정보 받음
	

	void		HT_vQuestWindow_Init();														// 처음 구동시 한번만 실행 (UI 생성부)
	void		HT_vQuestWindow_WindowPopup();												// 처음 화면 팝업시 호출 (외부에서 필요할때 호출하는 함수)
	void		HT_vQuestWindow_SetInfo();													// 화면 갱신시 호출 (UI 갱신부)
	static void HT_hrQuestWindow_InputCheck(int iAction, int iTarget, int iTargetID);		// 입력 처리 함수 (UI 입력제어부)
	void		HT_vQuest_TutorialMsgLoading();												// 퀘스트 메시지 데이터 로딩
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Merchant Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
const int UI_WINDOW_MERCHANT = _DIALOG_MERCHANT;	// 구입창 윈도우 인덱스 선언 (일반 상점 윈도우)
const int UI_WINDOW_MERCHANT_PREMIUM = _DIALOG_MERCHANT_PREMIUM;	// 구입창 윈도우 인덱스 선언 (프리미엄 윈도우)

class CHTUIMerchantWindow
{
private:
	
public:
	bool		m_bWindowType;			// True = 프리미엄 상점 / False = 일반 상점
	CHTString	m_strTopic;				// 프리미엄꾸러미 텝 설명
	CHTString	m_strTitle[5];			// 스트링 타이틀
	int			m_iTabNo;				// 프리미엄 윈도우 텝 인덱스
	int			m_iScrollValue;			// 프리미엄 윈도우 스크롤바 값

	int			m_ItemIndex[60];		// 판매할 아이템 리스트의 인덱스 저장 변수
	int			m_iNPCIndex;			// 해당 NPC 인덱스
	int			m_dwBuyItem;			// 구매할 아이템 인덱스
	int			m_dwSellItem;			// 구매할 아이템 인덱스
	int			m_dwBuyItemCount;		// 구매할 아이템 갯수
	int			m_ItemCash;				// 선택한 아이템 가격 (루피아 / 캐쉬)
	int			m_MyCash;				// 내가 가지고 있는 돈 (루피아 / 캐쉬)

	int			m_MessageCode;			// 메시지 박스 구분을 위한 변수 (내부 처리용)

	// [Initialize Functions]
	CHTUIMerchantWindow(void);
	virtual ~CHTUIMerchantWindow(void);

	void		HT_CheckWindowType(bool bType) {m_bWindowType = bType;}							// 타입 셋팅
	bool		HT_isWindowType() {return m_bWindowType;}										// 윈도우 타입 얻기
	
	void		HT_vMerchantWindow_DrawTab(int iTabNo);											// 텝그리기

	void		HT_vMerchantWindow_Init();														// 처음 구동시 한번만 실행 (UI 생성부)
	void		HT_vMerchantWindow_WindowPopup();												// 처음 화면 팝업시 호출 (외부에서 필요할때 호출하는 함수)
	void		HT_vMerchantWindow_SetInfo();													// 화면 갱신시 호출 (UI 갱신부)
	static void HT_hrMerchantWindow_InputCheck(int iAction, int iTarget, int iTargetID);		// 입력 처리 함수 (UI 입력제어부)
	
	void		HT_vMerchantWindow_SetBuyList();												// 구매리스트 생성
	void		HT_vMerchantWindow_SetBuy(int SlotNo);											// 해당 아이템 구매하기
	void		HT_vMerchantWindow_ProcessBuy(int iCount);										// 구매 갯수 입력후 부터 다시 처리.

	void		HT_vNetWork_CSP_Req_Item_Buy();													// 구매요청
	void		HT_vNetWork_SCP_Resp_Item_Buy( PS_SCP_RESP_ITEM_BUY info );						// 구매응답
	void		HT_vNetWork_CSP_Req_Item_Sell();												// 판매요청
	void		HT_vNetWork_SCP_Resp_Item_Sell( PS_SCP_RESP_ITEM_SELL info );					// 판매응답
};

/*
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << MessageBox Processing Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
const int UI_WINDOW_MESSAGEBOX = _DIALOG_MESSAGEBOX_MGR;	// 메시지박스 처리 윈도우

class CHTUIMessageBoxWindow
{
private:
public:
	int			m_iMesageNo;
		// [Initialize Functions]
	CHTUIEmblemWindow(void);
	virtual ~CHTUIEmblemWindow(void);

	void		HT_vMessageBoxWindow_Init();														// 처음 구동시 한번만 실행 (UI 생성부)
	void		HT_vMessageBoxWindow_WindowPopup();												// 처음 화면 팝업시 호출 (외부에서 필요할때 호출하는 함수)
	void		HT_vMEssageBoxWindow_SetInfo();													// 화면 갱신시 호출 (UI 갱신부)
	static void HT_hrMessageBoxWindow_InputCheck(int iAction, int iTarget, int iTargetID);		// 입력 처리 함수 (UI 입력제어부)
}
*/

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI << Emblem Window >>
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
const int UI_WINDOW_EMBLEM = _DIALOG_AMBLEM;	// 앰블럼 제작 윈도우

class CHTUIEmblemWindow
{
private:
public:
	int			m_iTabNo;
	int			m_Index;
	int			m_ScrollBar;

	int			m_GuildMark;
	int			m_Back1;
	int			m_Back2;
	int			m_Title;
	HT_COLOR	m_Color;

	// [Initialize Functions]
	CHTUIEmblemWindow(void);
	virtual ~CHTUIEmblemWindow(void);

	void		HT_vEmblemWindow_Init();														// 처음 구동시 한번만 실행 (UI 생성부)
	void		HT_vEmblemWindow_WindowPopup();												// 처음 화면 팝업시 호출 (외부에서 필요할때 호출하는 함수)
	void		HT_vEmblemWindow_SetInfo();													// 화면 갱신시 호출 (UI 갱신부)
	static void HT_hrEmblemWindow_InputCheck(int iAction, int iTarget, int iTargetID);		// 입력 처리 함수 (UI 입력제어부)
};



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// UI Manager
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class CHTUIManager
{
private:
	std::list<UIWindow*> m_UIList;	// Window 관리 리스트입니다.

	// 입력 외부 함수 처리를 위한 정보 저장
	int m_iAction;
	int m_iTarget;
	int m_iTargetID;

	void		RegisterTextureID(unsigned int nIndex, int XMLID, int RealSizeX, int RealSizeY);	// 텍스처 등록
	
public:

	// [환경 정보]
	int m_iScreenX;				// 게임해상도 X
	int m_iScreenY;				// 게임해상도 Y
	int m_iNationalCode;		// 국가코드: 0 = KOREA, 1 = CHINA, 2 = INDONESIA, 3 = PHILIPPINE, 4 = JAPAN, 5 = TAIWAN
	int m_iConnectingServer;	// 접속서버: 0 = TEST SERVER, 1 = MAIN SERVER
	int	m_iGameMode;			// 게임모드: 0 = 정식모드, 1 = 개발자모드

	int m_MousePosX;
	int m_MousePosY;

	int m_nAlphaColor;			// 윈도우 배경색 투명도 조절값
	

	// [Slot Box Info]
	bool				m_bDrawInfoWindow;				// 정보창이 그려지고 있는중인지 조사
	unsigned int		m_nSlotBoxWindowIndex;		
	unsigned int		m_nSlotBoxControlIndex;
	unsigned int		m_nSlotBoxTextureID;
	bool				m_bSlotBoxMoving;
	unsigned int		m_nSlotBoxTargetControlIndex;
	unsigned int		m_nSlotBoxTargetWindowIndex;

	// [EditBox Info]
	bool				m_InputState;					// 현재 UI가 입력상태인지 여부 저장

	bool				m_bBackgroundPos;				// 마우스 위치 백그라운드 면 트루, 윈도우면 펄스
	bool				m_bCheckRender;					// UI 랜더 온 오프 결정
	bool				HT_isRenderOn() {return m_bCheckRender;}	// 랜더중인가?
	void				HT_RenderOn();					// UI 랜더하기
	void				HT_RenderOff();					// UI 랜더하지 말기

	UIWindow*	FindWindowPointer(unsigned int nIndex);	// 인덱스값을 인자로 해당 Window Pointer 반환
	void		TopWindow(unsigned int nIndex);			// 해당 인덱스 윈도우를 탑(가장 앞의 윈도우)으로 보냅니다.
	void		BottomWindow(unsigned int nIndex);		// 해당 인덱스 윈도우를 보텀(가장 뒤의 윈도우)로 보냅니다.

	// [NPC & MOB]
	HTvector3					iRenderNPCPos;
	CHTString					strRenderNPCName;
	bool						bRenderNPC;				// 마우스 오버시 몬스터나 NPC 이름 출력 여부 결정

	// [MessageBox]
	CHTString					m_strMessageBoxText;			// 입력 텍스트 내용

	// [Windows]
	CHTUIMessageBox				UIMessageBoxMgr;				// 메시지 박스 관리 클래스

	//CHTUISlotInformationWindow	g_cUISlotInformationWindow;		// 슬롯 정보창 (TOOLTIP 확장)

	// [Initialize Functions]
	CHTUIManager(void);
	virtual ~CHTUIManager(void);

	void HTSetGameEnvironment(int iScreenX, int iScreenY, int iNationalCode, int iConnectingServer, int iGameMode, int iResource = 0);


	// [UI OutPut Functions]
	void HT_Render();								// 모든 윈도우를 설정대로 출력합니다. (랜더가 필요한 부분 마지막에 삽입합니다.)


	// [Window Functions]
	void HT_CreateWindow(unsigned int nIndex, CHTString str, int iSizeX, int iSizeY, func_t* ptr, int nMode);
	void HT_CreateWindow(unsigned int nIndex, CHTString str, int iSizeX, int iSizeY, func_t* ptr, int nMode, HT_COLOR clrBackground);
	void HT_DeleteWindow(unsigned int nIndex);		// 해당 윈도우를 제거합니다.
	bool HT_isShowWindow(unsigned int nIndex);		// 해당 윈도우가 현재 출력중인가?
	bool HT_isBackgroundDownEnable(unsigned int nIndex);	// 백그라운드 영역 맵으로 픽 가능 상태인가?
	void HT_SetBackgroundDownEnable(unsigned int nIndex, bool bEnable);	// 백그라운드 영역 맵으로 픽 가능여부 설정
	void HT_SetBackgroundColor(unsigned int nIndex, HT_COLOR clr);		// 윈도우의 배경색을 설정합니다.

	// [Texture Control Processing Functions]
	void HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture);	// 텍스처 컨트롤을 추가합니다.
	void HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iLayer = 1400, int iSizeX = 0, int iSizeY = 0);	// 텍스처컨트롤을 추가합니다.
	void HT_AddTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, HT_COLOR clr, int iSizeX = 0, int iSizeY = 0, int iLayer = 1400);	// 텍스처컨트롤을 추가합니다.
	void HT_SetTextureControlScale(unsigned int nWindowIndex, unsigned int nControlIndex, int iSizeX = 0, int iSizeY = 0, int iOSizeX = 1, int iOSizeY = 1);	// 텍스처컨트롤을 추가합니다.
	void HT_SetTextureControlImage(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID );				// 텍스처를 변경합니다.
	void HT_SetTextureControlColor(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr );				// 텍스처의 색상을 변경합니다.
	void HT_SetTextureControlDisplay(unsigned int nWindowIndex, unsigned int nControlIndex, bool bOn);					// 텍스처 출력 온오프 설정 (true = 온 . false = 오프)
	void HT_DelTextureControl(unsigned int nWindowIndex, unsigned int nControlIndex);	// 컨트롤을 삭제합니다.
	HTvector3 HT_GetTextureControlPos(unsigned int nWindowIndex, unsigned int nControlIndex);	// 컨트롤의 위치를 얻어옵니다.

	
	// [SlotBox Control Processing Functions]
	void HT_AddSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture);	// 슬롯박스 컨트롤을 추가합니다.
	void HT_AddSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iLayer = 2000, int iSizeX = 0, int iSizeY = 0);	// 슬롯박스 컨트롤을 추가합니다.
	void HT_DelSlotBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);			// 슬롯박스 컨트롤을 삭제합니다.
	void HT_GetSlotBoxControlSourInfo(unsigned int &nWindowIndex, unsigned int &nControlIndex, int &TextureID);		// 슬롯박스가 옮겨지기전 원래 위치의 정보를 가지고 옵니다.
	void HT_SetSlotImage(unsigned int nWindowIndex, unsigned int nControlIndex, int TextureID, int iLayer = 2050);		// 원하는 슬롯박스에 이미지를 붙입니다.
	bool CheckRegionWithSlotBoxPoint(unsigned int nWindowIndex, unsigned int nControlIndex, int iXPos, int iYPos, int iTargetID);	// 슬롯이미지가 어떤 윈도우 슬롯에 가있는지 조사합니다. (내부처리용)
	void HT_SetSlotBoxCoolTime(unsigned int nWindowIndex, unsigned int nControlIndex, DWORD DealyTime, DWORD PastTime = 0);	// 슬롯박스의 쿨타임 설정
	void HT_SetSlotBoxCoolTimeCancel(unsigned int nWindowIndex, unsigned int nControlIndex);	// 슬롯박스의 쿨타임 해제
	bool HT_isSlotBoxCoolTime(unsigned int nWindowIndex, unsigned int nControlIndex);		// 슬롯박스가 쿨타임중인지?
	void HT_AcceptSlotImageMoving();		// 슬롯박스의 이미지 옮기기 수락
	void HT_RefuseSlotImageMoving();		// 슬롯박스의 이미지 옮기기 거절
	void HT_SetSlotBoxToolTipOn(unsigned int nWindowIndex, unsigned int nControlIndex);// 해당 윈도우의 슬롯박스 컨트롤에서 툴팁을 킵니다.
	void HT_SetSlotBoxToolTipOff(unsigned int nWindowIndex, unsigned int nControlIndex);// 해당 윈도우의 슬롯박스 컨트롤에서 툴팁을 끕니다.
	void HT_SetSlotBoxControlToolTipText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, CHTString str);// 슬롯박스 툴팁의 해당 텍스트 설정(라인별)
	void HT_SetSlotBoxControlTextIndex(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex);// 슬롯박스 툴팁의 해당 출력 라인 인덱스 설정 (해당 라인까지만 출력함)
	void HT_SetSlotBoxControlToolTipTextColor(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr);// 슬롯박스 툴팁 해당 라인 텍스트 색상 변경
	void HT_SetSlotBoxControlPosImage(unsigned int nWindowIndex, unsigned int nControlIndex, int iPosX = 3, int iPosY = 3);	// 슬롯박스의 아이콘 위치를 재설정합니다.
	void HT_SetSlotBoxImageFixed(unsigned int nWindowIndex, unsigned int nControlIndex, bool bFixedIcon);	// 슬롯박스 아이콘 움직임 고정 여부 설정
	void HT_CancelSlotBoxImageMoving();						// 슬롯 아이콘 무빙중을 원래상태로 되돌립니다.
	void HT_SetSlotBoxControlEnable(unsigned int nWindowIndex, unsigned int nControlIndex, bool bEnable);	// 슬롯박스의 사용여부 결정 (0=사용불가, 1=사용가능)



	// [ScrollBar Control Processing Functions]
	void HT_AddScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTImage, UITexture oTLine, UITexture oTArrow1[3], UITexture oTArrow2[3], int iMaxValue, int iType = 0);
	void HT_AddScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iPosX, int iPosY, int iLength, int iMaxValue = 100, int iType = 0, int iStyle = 0);	// 스크롤바 컨트롤을 추가합니다.
	void HT_SetScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iValue);	// 스크롤바 컨트롤에 값을 넣습니다.
	void HT_SetScrollBarControlMaxValue(unsigned int nWindowIndex, unsigned int nControlIndex, int iValue);	// 스크롤바 컨트롤에 최대 값을 변경 합니다.
	int HT_GetScrollBarValue(unsigned int nWindowIndex, unsigned int nControlIndex);				// 스크롤바 컨트롤의 값을 가지고 옵니다.
	void HT_DelScrollBarControl(unsigned int nWindowIndex, unsigned int nControlIndex);			// 스크롤바 컨트롤을 삭제합니다.


	// [Label Control Processing Functions]
	void HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str, int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY);	// 라벨을 추가합니다.
	void HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iStringNo, int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY);
	void HT_AddLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, UIText oText);			// 라벨을 추가합니다.
	void HT_DelLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex);							// 라벨을 삭제합니다.
	void HT_SetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str);		// 라벨의 문자열을 삽입합니다.
	void HT_SetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int strindex);
	CHTString HT_GetTextLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex);				// 해당 윈도우의 라벨컨트롤로 부터 스트링을 얻어옵니다.
	void HT_SetArrangementLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iDirection);		// 라벨의 문자열을 원하는 방향으로 배치 합니다.
	void HT_SetTextColorLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr);
	void HT_SetTextShadowColorLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr);

	// [Long Label Control Processing Functions]
	void HT_AddLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HTtchar str[], int iFontMode, HT_COLOR clr, HT_COLOR sclr, int iPosX, int iPosY, int iSizeX, int iSizeY);	// 라벨을 추가합니다.
	void HT_AddLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, UILongText oText);			// 라벨을 추가합니다.
	void HT_DelLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex);							// 라벨을 삭제합니다.
	void HT_SetTextLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HTtchar str[]);		// 라벨의 문자열을 삽입합니다.
	HTtchar* HT_GetTextLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex);				// 해당 윈도우의 라벨컨트롤로 부터 스트링을 얻어옵니다.
	void HT_SetArrangementLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iDirection);		// 라벨의 문자열을 원하는 방향으로 배치 합니다.
	void HT_SetTextColorLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr);
	void HT_SetTextShadowColorLongLabelControl(unsigned int nWindowIndex, unsigned int nControlIndex, HT_COLOR clr);


	// [EditBox Control Processing Functions]
	void HT_AddEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iSizeX = 0, int iSizeY = 0, int iStyle = 0, int iLayer = 1500);	// 에디터박스를 생성합니다.
	void HT_AddEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture, UIText oText, int iStyle = 0);	// 에디터 박스를 생성합니다.
	void HT_DelEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);									// 에디터 박스를 제거합니다.
	void HT_SetTextEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str);				// 에디터박스에 글자를 삽입합니다.
	void HT_SetTextColorEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str);			// 에디터박스의 글자색상을 변경합니다.
	void HT_SetTextShadowColorEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str);		// 에디터박스의 글자 그림자색상을 변경합니다.
	void HT_SetModeEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iMode = 0);				// 에디터박스의 출력모드를 변경합니다. ( 0 = 일반(기본) , 1 = *모양(패스워드 입력방식), 2 = 숫자입력시 자동 콤마 삽입모드 )
	void HT_FocusOffEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);
	void HT_FocusOnEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);
	bool HT_isFocusOnEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);
	CHTString HT_GetTextEditBoxControl(unsigned int nWindowIndex, unsigned int nControlIndex);							// 에디터박스로 부터 입력된 문자열을 가지고 옵니다.
	void HT_SetEditBoxControlLimitText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int uiSize);		// 에디터박스의 입력글자길이를 제한합니다.
	void CheckEditBoxFocusOn(bool bCheck) {	m_InputState = bCheck;}		// 현재 입력상태 여부 저장
	bool HT_isFocusOnEditBoxControl() {return m_InputState;}			// 현재 UI 상태가 입력상태인가?
	void HT_SetEditBoxFocusOnIME(unsigned int nWindowIndex, unsigned int nControlIndex, int iIME); // 해당 윈도우의 컨트롤 포커스활성화시 지정한 입력모드 상태를 변경하여 적용되도록 합니다. 0 = 영어 1 = 한국어


	// [Button Control Processing Functions]
	void HT_AddButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex, int iTextureID, int iPosX, int iPosY, int iTextureID2 = 0, int iTextureID3 = 0, int iLayer = 1500, int iSizeX = 0, int iSizeY = 0);	// 버튼을 생성합니다.
	void HT_AddButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex, UITexture oTexture[3]);	// 버튼을 생성합니다.
	void HT_SetButtonToolTip(unsigned int nWindowIndex, unsigned int nControlIndex, CHTString str);	// 해당 버튼의 툴팁 내용을 변경합니다.
	void HT_SetButtonToolTipOn(unsigned int nWindowIndex, unsigned int nControlIndex);				// 해당 버튼의 툴팁을 킵니다.
	void HT_SetButtonToolTipOff(unsigned int nWindowIndex, unsigned int nControlIndex);				// 해당 버튼의 툴팁을 끕니다.
	void HT_SetButtonEnterOn(unsigned int nWindowIndex, unsigned int nControlIndex);				// 해당 버튼의 엔터기능을 킵니다.
	void HT_SetButtonEnterOff(unsigned int nWindowIndex, unsigned int nControlIndex);				// 해당 버튼의 엔터기능을 끕니다.
	void HT_DelButtonControl(unsigned int nWindowIndex, unsigned int nControlIndex);				// 해당 버튼의 컨트롤을 제거 합니다.
	void HT_SetButtonControlToolTipText(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, CHTString str);	// 버튼 툴팁의 해당 텍스트 설정(라인별)
	void HT_SetButtonControlTextIndex(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex);// 버튼 툴팁의 해당 출력 라인 인덱스 설정 (해당 라인까지만 출력함)
	void HT_SetButtonControlToolTipTextColor(unsigned int nWindowIndex, unsigned int nControlIndex, unsigned int nIndex, HT_COLOR clr);// 버튼 툴팁 해당 라인 텍스트 색상 변경
	void HT_SetButtonEnable(unsigned int nWindowIndex, unsigned int nControlIndex, bool bEnable);
	void HT_SetButtonControlState(unsigned int nWindowIndex, unsigned int nControlIndex, int iSetNo);	// 해당 버턴의 출력상태를 변경합니다. 0=노말, 1=항상켜짐, 2=항상꺼짐, 3=깜박임

	// [Timer Control Processing Functions]
	void HT_AddTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex, DWORD dwSetTime, int iStyle = 0);
	void HT_DelTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex);
	void HT_EnableOnTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex);
	void HT_EnableOffTimerControl(unsigned int nWindowIndex, unsigned int nControlIndex);

	// [Cehck Box Control Functions]
	void HT_AddCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex, int XPos, int YPos, bool bValue = false, int BorderTextureID = 143, int CheckTextureID = 175, int SizeX = 14, int SizeY = 14);	// 체크박스를 생성합니다.
	void HT_DelCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex);				// 컨트롤을 삭제합니다.
	void HT_SetCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex, bool bCheck);	// 체크박스에 값을 설정
	bool HT_GetCheckBoxControl(unsigned int nWindowIndex, unsigned int nIndex);					// 체크박스의 값을 얻음

	// [MessageBox Control Processing Functions]
	void HT_MessageBox(unsigned int nWindowIndex, CHTString str, int nStyle = 0);					// nMode = 0 확인버튼만, 1 = 확인/취소 버튼, 2 = 미사용...	
	void HT_MessageBox(unsigned int nWindowIndex, int index, int nStyle = 0);
	bool HT_isShowMessageBox();																		// 메시지 박스가 띄어져 있는지 조사합니다.
	void HT_CallMessageBoxFunction(unsigned int nWindowIndex, int iTargetID);

	// [Window Basic Functions]
	void HT_ShowWindow(unsigned int nIndex);														// 해당 윈도우를 보여줍니다.
	void HT_HideWindow(unsigned int nIndex);														// 해당 윈도우를 숨깁니다.
	void HT_EnableOnWindow(unsigned int nIndex);													// 해당 윈도우를 동작하게 합니다.
	void HT_EnableOffWindow(unsigned int nIndex);													// 해당 윈도우를 동작하지 않게 합니다.
	void HT_FocusOnWindow(unsigned int nIndex);														// 해당 윈도우의 포커스를 킵니다.
	void HT_FocusOffWindow(unsigned int nIndex);													// 해당 윈도우를 포커스를 끕니다.
	void HT_MoveWindow(unsigned int nIndex, int iPosX, int iPosY, int iType = 0);					// 해당 위치로 이동합니다 [iType = 0 이동, 1이면 현재위치에서 추가이동]
	void HT_WindowArrangement(unsigned int nIndex, int iDirection);									// 해당 방향으로 윈도우를 이동 시킵니다. [숫자 키패드의 1~9의 방향으로 이동_해상도에 따라 자동갱신]
	void HT_GetWindowPos(unsigned int nIndex, int &PosX, int &PosY);								// 해당 윈도우의 위치값을 얻어옵니다.
	HTvector3 HT_GetWindowSize(unsigned int nIndex);												// 해당 윈도우의 사이즈를 얻어옵니다.
	void HT_SetMovingRegion(unsigned int nIndex, bool isOn, int iPosX = 0, int iPosY = 0, int iSizeX = 1, int iSizeY = 1);// 윈도우 영역에 추가로 윈도우를 움직일 수 있는 영역을 설정합니다. 첫번째 인자는 참으로 해야하며, 영역을 끄려면 거짓으로 셋팅합니다.
	void HT_SetMagnet(unsigned int nWindowIndex, unsigned int nTargetIndex);						// 자석기능 설정 (0 = 취소, -1 = 바탕화면)
	void MagnetMgr(unsigned int nWindowIndex, unsigned int nTargetIndex, bool bInsert);				// 해당 윈도우 자석기능에 삽입 / 삭제 (내부처리용)
	bool HT_GetMagnetState(unsigned int nWindowIndex);												// 해당 윈도우의 자석상태를 알아온다.
	CHTString HT_strSetRestMark(HTint iNumber);														// 루피아 찍을때 콤마 마크 찍을수 있도록 셋팅
	void HT_SetMagnetState(unsigned int nWindowIndex, bool bState);									// 해당 윈도우의 자석상태를 수동 셋팅합니다. (상속된 윈도우에 한해서만 정상동작 합니다.)
	bool HT_CloseWindow();																			// 최상위 윈도우를 제거합니다. (임시용 사용금지)

	// 에디터박스 처리 관련
	void HT_UpdateEditBoxText(CHTString str);
	HTvector3 HT_GetEditBoxCursorPos();

	// [Input Functions]
	bool OnMouseWheel(WPARAM wParam, LPARAM lParam);
	bool OnLButtonDown(int iXPos, int iYPos);
	bool OnLButtonUp(int iXPos, int iYPos);
	bool OnRButtonDown(int iXPos, int iYPos);
	bool OnRButtonUp(int iXPos, int iYPos);
	bool OnKeyDown(WPARAM wParam);
	bool OnKeyUp(WPARAM wParam);
	bool OnChar(WPARAM wParam);
	bool OnMouseMove(int iXPos, int iYPos);
	bool OnSysCommand(WPARAM wParam);

	// UI 저장 및 불러오기
	void HT_vSaveDialogPos(CHTString strFilePath);
	void HT_vOpenDialogPos(CHTString strFilePath);

	unsigned int HT_CheckRegionWithPoint(int iXPos, int iYPos, int iWindowPosX = 0, int iWindowPosY = 0);	// 해당 위치의 윈도우 번호 반환 (없으면 0)
	void HT_SetScriptMessage( HTint idMessage, CHTString* pszMessage, CHTString strInputItem1, CHTString strInputItem2 );
	void HT_SetWindowBackgroundColor(unsigned int nIndex);								// 모든 윈도우의 배경색 투명도를 조절 합니다. (0 ~ 100);

	// 임시용 선언변수 (v2 -> v3로 가기위한 과도기적 함수들)
	void ChattingNotify(int iMessageID);								// 채팅창에 공지 알림 (채팅창 존재시에만 올바르게 동작함) 임시용


	// [Message Procedure]
	static void ActionTarget(int iAction, int iTarget, int iTargetID);	// 입력 처리 함수
};

#endif