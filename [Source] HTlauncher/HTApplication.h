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
	// Window �ʱ�ȭ, ������
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
	// Window state ���� �Լ���
	//----------------------------------------------------------------------
	HTbool			HT_bIsActive()	{ return(m_bActive); }
	HTvoid			HT_vPause( HTbool bPause );
	HTvoid			HT_vSetActive(HTbool bFlag)	{ m_bActive = bFlag; }
	LRESULT			HT_OnClose(WPARAM wParam, LPARAM lParam);
	LRESULT			HT_OnDestroy(WPARAM wParam, LPARAM lParam);
	LRESULT			HT_OnSize(WPARAM wParam, LPARAM lParam);
	LRESULT			HT_OnEnterSizeMove(WPARAM wParam, LPARAM lParam);
	LRESULT			HT_OnExitSizeMove(WPARAM wParam, LPARAM lParam);
	HTRESULT		HT_hrToggleScreen();			// ��üȭ��-â��� ��ȯ
	RECT			GetScreenRect();				// Ŭ���̾�Ʈ�� ������ ��´�.
	RECT			GetScreenRect(RECT* rv);		// Ŭ���̾�Ʈ�� ������ ��´�.

public:
	//----------------------------------------------------------------------
	// Window state ���� ������
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
	// ȭ�� fade in fade out ���� ������
	//----------------------------------------------------------------------
	// õü ��ũ�� ���̵� Ÿ���� ����
	HTint			m_iFadeEntireScreenType;
	// ���̵带 ������Ʈ �� ������ �ð��� üũ
	HTfloat			m_fLastCheckedTime;
	// ���̵� �ϰ� �ִ� ��
	HTfloat			m_fFadeIn_value;
	// ���̵� �Ǵ� ��ü �ð�
	HTfloat			m_fFadeElapsedTime;
	// ���̵带 �� �÷�
	HT_COLOR		m_cFadeColor;
};

//----------------------------------------------------------------------
// ȭ�� fade in fade out ���� �Լ���
//----------------------------------------------------------------------
#define FADE_NONE						0		// ���̵� �ۿ� ����
#define FADE_BLACK_INCREASE				1		// �� ���̵�			(����ȭ�� -> ��ο� ȭ��)
#define FADE_BLACK_DECREASE				2		// �� ���̵� ����		(��ο� ȭ�� -> ���� ȭ��)
#define FADE_WHITE_INCREASE				4		// ȭ��Ʈ ���̵�		(���� ȭ�� -> �Ͼ� ȭ��)
#define FADE_WHITE_DECREASE				8		// ȭ��Ʈ ���̵� ����	(�Ͼ� ȭ�� -> ���� ȭ��)
#define FADE_CUTIN						16		// ȭ�� ������ 16:9
#define FADE_CUTOUT						32		// ȭ�� ������ 4:3

#define FADED_ALPHA_MAX					1.0f	// �ִ�� ���̵� �Ǿ��� ����� ���İ�
#define FADED_ALPHA_MIN					0.0f	// �ּҷ� ���̵� �Ǿ��� ����� ���İ�

#endif	// #ifndef _HTAPPLICATION_H_

