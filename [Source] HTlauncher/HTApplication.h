//---------------------------------------------------------------------------//
// Name: HTApplication.h
//
//
// Description:
//		- Inherit CHTWin32Window
//		- Windows Message Handling
//---------------------------------------------------------------------------//

#ifndef _HTAPPLICATION_H_
#define _HTAPPLICATION_H_

#include "HTWin32Window.h"

class CHTWin32Window;
class CHTTimer;
class CHTEngineHandler;
class CHTConfigSystem;

class CHTApplication : public CHTWin32Window  
{
public:
					CHTApplication();
					~CHTApplication();

	//----------------------------------------------------------------------
	// Window 초기화, 렌더링
	//----------------------------------------------------------------------
	HTRESULT		HT_hrInitEnvironment();
	HTRESULT		HT_hrCreate( HINSTANCE hInstance, HINSTANCE hPrevInstance, HWND parenthwnd, LPSTR lpszCmdLine, HTint nCmdShow );
	HTRESULT		HT_hrCleanup();
	HTRESULT		HT_hrUpdate();
	HTRESULT		HT_hrRender();
	HTRESULT		HT_hrBeforeRender();
	HTRESULT		HT_hrWorldRender();
	HTRESULT		HT_hrAfterRender();
	
	//----------------------------------------------------------------------
	// Window state 관련 함수군
	//----------------------------------------------------------------------
	HTbool			HT_bIsActive()	{ return(m_bActive); }
	HTvoid			HT_vPause( HTbool bPause );
	HTvoid			HT_vSetActive(HTbool bFlag)	{ m_bActive = bFlag; }
	LRESULT			HT_OnClose(WPARAM wParam, LPARAM lParam);
	LRESULT			HT_OnDestroy(WPARAM wParam, LPARAM lParam);
	LRESULT			HT_OnSize(WPARAM wParam, LPARAM lParam);
	LRESULT			HT_OnEnterSizeMove(WPARAM wParam, LPARAM lParam);
	LRESULT			HT_OnExitSizeMove(WPARAM wParam, LPARAM lParam);
	HTRESULT		HT_hrToggleScreen();			// 전체화면-창모드 전환
	RECT			GetScreenRect();				// 클라이언트의 영역을 얻는다.
	RECT			GetScreenRect(RECT* rv);		// 클라이언트의 영역을 얻는다.

public:
	//----------------------------------------------------------------------
	// Window state 관련 변수군
	//----------------------------------------------------------------------
	HTbool			m_bActive;
	HTbool			m_bMinimized;
	HTbool			m_bMaximized;
	HTbool			m_bWindowed;
	DWORD			m_dwWindowStyle;
	HTbool			m_bClipCursorWhenFullscreen;
	
	HTfloat			m_fElapsedTime;
	CHTTimer*		m_pTimer;

protected:
	HTuint			m_nScreenWidth, m_nScreenHeight;

public:
	//----------------------------------------------------------------------
	// 화면 fade in fade out 관련 변수군
	//----------------------------------------------------------------------
	// 천체 스크린 페이드 타입을 지정
	HTint			m_iFadeEntireScreenType;
	// 페이드를 업데이트 한 마지막 시간을 체크
	HTfloat			m_fLastCheckedTime;
	// 페이드 하고 있는 값
	HTfloat			m_fFadeIn_value;
	// 페이드 되는 전체 시간
	HTfloat			m_fFadeElapsedTime;
	// 페이드를 할 컬러
	HT_COLOR		m_cFadeColor;
};

//----------------------------------------------------------------------
// 화면 fade in fade out 관련 함수군
//----------------------------------------------------------------------
#define FADE_NONE						0		// 페이드 작용 없음
#define FADE_BLACK_INCREASE				1		// 블랙 페이드			(정상화면 -> 어두운 화면)
#define FADE_BLACK_DECREASE				2		// 블랙 페이드 해제		(어두운 화면 -> 정상 화면)
#define FADE_WHITE_INCREASE				4		// 화이트 페이드		(정상 화면 -> 하얀 화면)
#define FADE_WHITE_DECREASE				8		// 화이트 페이드 해제	(하얀 화면 -> 정상 화면)
#define FADE_CUTIN						16		// 화면 비율을 16:9
#define FADE_CUTOUT						32		// 화면 비율을 4:3

#define FADED_ALPHA_MAX					1.0f	// 최대로 페이드 되었을 경우의 알파값
#define FADED_ALPHA_MIN					0.0f	// 최소로 페이드 되었을 경우의 알파값

#endif	// #ifndef _HTAPPLICATION_H_

