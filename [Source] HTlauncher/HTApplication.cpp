//---------------------------------------------------------------------------//
// Name: HTApplication.cpp
//
//
// Description:
//		- Implimentation of CHTApplication
//---------------------------------------------------------------------------//

#include "stdafx.h"
#include "HTextern.h"
#include "HTConfigSystem.h"
#include "HTApplication.h"
#include "resource.h"
#include "HTOption.h"
#include "HTEngineHandler.h"
#include "HTWindowManager.h"
#include "HTConsole.h"


extern CHTWindowManager* g_CGame;


CHTApplication::CHTApplication()
{
	m_bActive			= HT_FALSE;
    m_bMinimized        = HT_FALSE;
    m_bMaximized        = HT_FALSE;

	m_pTimer = HT_NULL;
	g_pEngineHandler = HT_NULL;
	m_fElapsedTime = 0.0f;

	m_iFadeEntireScreenType = FADE_NONE;
	
	// 초기 페이드 컬러는 흰색이지만 투명한 색(결국 적용 안함)
	m_cFadeColor = HT_COLOR( 0.0f, 0.0f, 0.0f, 1.0f );	

	// 초기 페이드 인 벨류는 0.0f(투명, 결국 적용 안함)
	m_fFadeIn_value = 0.0f;

	// 초기 페이드 되는 전체 시간은 0.5초로 셋팅
	m_fFadeElapsedTime = 0.5f;

	// Pause rendering until we're ready to render
	HT_vPause( HT_TRUE );

    // When m_bClipCursorWhenFullscreen is true, the cursor is limited to
    // the device window when the app goes fullscreen.  This prevents users
    // from accidentally clicking outside the app window on a multimon system.
    // This flag is turned off by default for debug builds, since it makes 
    // multimon debugging difficult.
#if defined(_DEBUG) || defined(DEBUG)
    m_bClipCursorWhenFullscreen = false;
#else
    m_bClipCursorWhenFullscreen = true;
#endif
}


CHTApplication::~CHTApplication()
{
	//UnregisterClass(m_strClassName, m_hInstance);
}


HTRESULT CHTApplication::HT_hrCreate( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
								  HWND parenthwnd, LPSTR lpszCmdLine, HTint nCmdShow )
{
	g_pCfgSys->HT_hrGetValue( _T("RENDERER"), _T("screenwidth"),	&m_nScreenWidth );
	g_pCfgSys->HT_hrGetValue( _T("RENDERER"), _T("screenheight"),	&m_nScreenHeight );
	g_pCfgSys->HT_hrGetValue( _T("RENDERER"), _T("windowed"),		&m_bWindowed );

	// 제일 먼저 클라이언트에서 엔진에 대한 조종을 할 수 있게 하는 핸들러를 생성한다.
	g_pEngineHandler = new CHTEngineHandler;

	g_pEngineHandler->m_pUserSettings = new CHTUserSetting;
	HTtchar szUserSetting[HT_MAX_STR] = "HTUserSetting.sys";
	HTbool bLoadedUserSetting = g_pEngineHandler->m_pUserSettings->HT_bLoad( szUserSetting );
	if ( bLoadedUserSetting )
	{
		m_nScreenWidth = g_pEngineHandler->m_pUserSettings->HT_iGetScreenWidth();
		m_nScreenHeight = g_pEngineHandler->m_pUserSettings->HT_iGetScreenHeight();
	}
	else
	{
		HT_DELETE( g_pEngineHandler->m_pUserSettings );
	}

	if ( !this->HT_bCreate( hInstance, hPrevInstance, parenthwnd, lpszCmdLine, 
		nCmdShow, m_nScreenWidth, m_nScreenHeight, m_bWindowed) )
	{
		return HT_FAIL;
	}

	// 이 창으로 포커스를 이동시킨다.
	if(SetForegroundWindow(m_hWnd) == 0)
	{
		// SetForegroundWindow()가 제대로 동작하지 않는 경우에는 다른 방법으로도 시도한다.
		ShowWindow(m_hWnd, SW_HIDE);		// 이렇게 하면 창이 사라졌다가...
		ShowWindow(m_hWnd, SW_MINIMIZE);	// 안보이면서 minimize니까 계속 사라져 있다가...
		ShowWindow(m_hWnd, SW_RESTORE);		// 다시 팍 하면서 focus 된 상태로 된다.
	}

	// 3D 환경 및 엔진을 초기화시킨다.
	if( HT_FAILED(g_pEngineHandler->HT_hrInit( g_pCfgSys, m_hWnd )) )
	{
		MessageBox( HT_NULL, _T("Engine Initialization failed!"), _T("g_pLauncher"), MB_OK );
		return HT_FAIL;
	}

	// 윈도우 생성 크기와 실제 풀화면 크기는 다를 수 있다.
	m_nScreenWidth = g_pEngineHandler->HT_iGetScreenWidth();
	m_nScreenHeight = g_pEngineHandler->HT_iGetScreenHeight();

    // Confine cursor to fullscreen window
    if( m_bClipCursorWhenFullscreen )
    {
        if ( !m_bWindowed )
        {
			RECT rcClient;
			GetScreenRect( &rcClient );
            ClipCursor( &rcClient );
        }
        else
        {
            ClipCursor( NULL );
        }
    }

	// 맵 로드 전에 필요한 리소스들을 로드한다_1. fors_debug open client first error
	if( HT_FAILED(g_pEngineHandler->HT_hrPreload( g_pCfgSys )) )
	{
		MessageBox( HT_NULL, _T("Configuration file preloading failed!"), _T("g_pLauncher"), MB_OK );
		return HT_FAIL;
	} 

	m_pTimer = new CHTTimer;
	m_pTimer->Do( HT_TIMER_START );

	// We're ready to render!
	HT_vPause( HT_FALSE );

	return HT_OK;
}

HTRESULT CHTApplication::HT_hrCleanup()
{
	// Stop rendering
	HT_vPause( HT_TRUE );

	// Unload data
	// By HK : 문제를 해결하기 보다는 피해가는 부분이기에... 많은 변명을 적는다.
	// 내부에서는 아무것도 안하는 g_cLoading->HT_hrUnloadAll() 에서 많은 Crash가 발생한다.
	// 20030721 의 Crash 보고 파일을 분석해 본 결과
	// 어떤 이유(?)에 의해 g_cLoading pointer가 NULL 인 경우에 생기는 문제로 추측된다.
	// 그래서 아래의 if문 비교 부분을 견디어낼 수 있는 NT 계열에서는 문제가 없으나
	// 그렇지 못한 9X 계열에서는 많은 문제가 생기는 것으로 추측된다.
	// 따라서 현재 사실상 필요 없는 다음의 g_cLoading->HT_hrUnloadAll() 함수를 호출하지 않는다.
	
	if ( g_cLoading )
	{
		g_pEngineHandler->HT_vDestory_LoadingBGImage();
		g_cLoading->HT_hrUnloadAll();
		HT_DELETE( g_cLoading );
	}

	//g_pEngineHandler->HT_hrUnLoadETCData();

	HT_DELETE( m_pTimer );
	
	HT_DELETE( g_pEngineHandler );

	return HT_OK;
}

HTRESULT CHTApplication::HT_hrUpdate()
{
	if (m_pTimer && g_pEngineHandler)
	{
		m_fElapsedTime = m_pTimer->Do( HT_TIMER_GETELAPSEDTIME );
		HT_CHECK( g_pEngineHandler->HT_hrUpdate( m_fElapsedTime ) );
	}

	return HT_OK;
}

HTRESULT CHTApplication::HT_hrRender()
{
	return HT_OK;
}

// 랜더링 전에 한번씩 호출
HTRESULT CHTApplication::HT_hrBeforeRender()
{
	switch( g_pEngineHandler->HT_hrCheckScreen() )
	{
		// The device is lost and cannot be restored at the current time, so rendering is not possible.
		// Minimized, Ctrl + Alt + Tab etc.
		case D3DERR_DEVICELOST:
			return HT_FAIL;
			break;

		// Alt + Tab
		case D3DERR_DEVICENOTRESET:
			// Confine cursor to fullscreen window
			if( m_bClipCursorWhenFullscreen )
			{
				if ( !m_bWindowed )
				{
					RECT rcClient;
					GetScreenRect( &rcClient );
					ClipCursor( &rcClient );
				}
				else
				{
					ClipCursor( NULL );
				}
			}
			break;

		default:;
	}
		
	HT_COLOR clrScreen = HT_COLOR( 0.0f, 0.0f, 0.0f, 0.0f );
	g_pEngineHandler->HT_hrClearScreen( clrScreen );
	
	return HT_OK;
}

HTRESULT CHTApplication::HT_hrWorldRender()
{
	HT_CHECK( g_pEngineHandler->HT_hrRenderWorld() );

	return HT_OK;
}

// 렌더링 후에 한번씩 호출
HTRESULT CHTApplication::HT_hrAfterRender()
{
	if ( g_bShowFPS.g_bShowFPS )
	{
		static HTfloat fLastTime = 0.0f;
		static HTdword dwFrames  = 0L;
		++dwFrames;
		static HTfloat fCurrentTime, fFPS;
		fCurrentTime = m_pTimer->Do( HT_TIMER_GETABSOLUTETIME );
		if( fCurrentTime - fLastTime > 1.0f )
		{
			fFPS = dwFrames / (fCurrentTime - fLastTime);
			fLastTime = fCurrentTime;
			dwFrames  = 0L;
		}

		HT_CHECK( g_pEngineHandler->HT_hrRenderFPS( fFPS ) );
	}

	if( g_bHelp_Text == HT_TRUE )
	{ 
		static CHTString String;

		String.HT_szFormat( _T("%d -> 0:%.02f, 1:%.02f, 2:%.02f, 3:%.02f, 4:%.02f, 5:%.02f, 6:%.02f"), 
				g_button_count, g_imsi_button[0], g_imsi_button[1], g_imsi_button[2], 
				g_imsi_button[3], g_imsi_button[4], g_imsi_button[5], g_imsi_button[6] );
		g_pEngineHandler->HT_hrRenderText( HT_FONT_ARIAL_20, String, HTvector3( 0.0f, 20.0f, 0.0f ), HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );

		HTint count;
		for( HTint i=0 ; i<10 ; i++ )
		{
			count = g_DebugingFont_Count-1;
			if( count == -1 )
				count = 9;

			if( count == i )
				g_pEngineHandler->HT_hrRenderText( HT_FONT_ARIAL_20, g_DebugingFont[i], HTvector3( 0.0f, 40.0f+ (i*20.0f), 0.0f ), HT_COLOR( 1.0f, 0.0f, 0.0f, 1.0f ) );
			else
				g_pEngineHandler->HT_hrRenderText( HT_FONT_ARIAL_20, g_DebugingFont[i], HTvector3( 0.0f, 40.0f+ (i*20.0f), 0.0f ), HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
		}
	}

	if ( g_bDevelopingMode )
		g_oConsole.HT_hrRender();

	// 화면 버퍼를 전환
	g_pEngineHandler->HT_hrFlipScreen();

	return HT_OK;
}

// 클라이언트의 화면 영역(렌더링 영역)을 구하는 함수
RECT CHTApplication::GetScreenRect()
{
	RECT rc;
	rc.left		= 0;
	rc.top		= 0;
	rc.right	= this->m_nScreenWidth;
	rc.bottom	= this->m_nScreenHeight;

	return rc;
}

// 클라이언트의 화면 영역(렌더링 영역)을 구하는 함수
RECT CHTApplication::GetScreenRect( RECT* rv )
{
	RECT rc;
	rv->left	= rc.left		= 0;
	rv->top		= rc.top		= 0;
	rv->right	= rc.right		= this->m_nScreenWidth;
	rv->bottom	= rc.bottom		= this->m_nScreenHeight;

	return rc;
}

//=====      윈도우 관련 함수      =====//
LRESULT CHTApplication::HT_OnClose(WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}


//=====      윈도우 관련 함수      =====//
LRESULT CHTApplication::HT_OnDestroy(WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}


//=====		풀스크린 모드를 토글한다.     =====//
HTRESULT CHTApplication::HT_hrToggleScreen()
{
	if( HT_FAILED( g_pEngineHandler->HT_hrToggleScreen() ) )
    {
		MessageBox( HT_NULL, _T("HT_hrToggleScreen FAIL!"), _T("CHTApplication"), MB_OK );
		PostQuitMessage(0);
        return 0;
    }

	return HT_TRUE;
}

LRESULT CHTApplication::HT_OnSize(WPARAM wParam, LPARAM lParam)
{
    // Pick up possible changes to window style due to maximize, etc.
    if( m_bWindowed && m_hWnd != NULL )
        m_dwWindowStyle = GetWindowLong( m_hWnd, GWL_STYLE );

    if( SIZE_MINIMIZED == wParam )
    {
        if( m_bClipCursorWhenFullscreen && !m_bWindowed )
            ClipCursor( NULL );
        HT_vPause( true ); // Pause while we're minimized
        m_bMinimized = true;
        m_bMaximized = false;
    }
    else if( SIZE_MAXIMIZED == wParam )
    {
        if( m_bMinimized )
            HT_vPause( false ); // Unpause since we're no longer minimized
        m_bMinimized = false;
        m_bMaximized = true;
    }
    else if( SIZE_RESTORED == wParam )
    {
        if( m_bMaximized )
        {
            m_bMaximized = false;
        }
        else if( m_bMinimized)
        {
            HT_vPause( false ); // Unpause since we're no longer minimized
            m_bMinimized = false;
        }
        else
        {
            // If we're neither maximized nor minimized, the window size 
            // is changing by the user dragging the window edges.  In this 
            // case, we don't reset the device yet -- we wait until the 
            // user stops dragging, and a WM_EXITSIZEMOVE message comes.
        }
    }

	return HT_TRUE;
}


LRESULT CHTApplication::HT_OnEnterSizeMove(WPARAM wParam, LPARAM lParam)
{
	// Pause rendering
	HT_vPause( HT_TRUE );
	return HT_TRUE;
}


LRESULT CHTApplication::HT_OnExitSizeMove(WPARAM wParam, LPARAM lParam)
{
	// Resize 3D environment
	g_pEngineHandler->HT_hrResize();

	// Resume rendering
	HT_vPause( HT_FALSE );
	return HT_TRUE;
}


//-----------------------------------------------------------------------------
// Name: HT_vPause()
// Desc: Pause application's rendering process when bPause is true,
//		 Resume recdering when bPacuse is false.
//		 must be called by pair. (or application does not render)
//-----------------------------------------------------------------------------
HTvoid CHTApplication::HT_vPause( HTbool bPause )
{
    static HTdword dwAppPausedCount = 0L;

    dwAppPausedCount += ( bPause ? +1 : -1 );
    m_bActive         = ( dwAppPausedCount ? HT_FALSE : HT_TRUE );
}

