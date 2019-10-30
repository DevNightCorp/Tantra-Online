//------------------------------------------------------------------------------
// File: CutScene.cpp
//
// Desc: DirectShow sample code - simple interactive movie player.  Plays
//       a movie or game cutscene in fullscreen mode.  Supports simple user
//       input to enable ESC, spacebar, or ENTER to quit.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------
#include "stdafx.h"
#include <dshow.h>
#include <stdio.h>
 
//#include "..\HTUtilLib\HTNew_Off.h"

#include <atlbase.h>
#include <atlcom.h>

//#include "..\HTUtilLib\HTNew_On.h"

#include "HTCutScene.h"

#define KEYBOARD_SAMPLE_FREQ  100  // Sample user input on an interval
#define WM_GRAPHNOTIFY  WM_USER+13

//
// Helper Macros (Jump-If-Failed, Log-If-Failed)
//
#define RELEASE(i) {if (i) i->Release(); i = NULL;}

#define JIF(x) if (FAILED(hr=(x))) \
    {Msg(_T("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr); goto CLEANUP;}

#define LIF(x) if (FAILED(hr=(x))) \
    {Msg(_T("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr); return hr;}


// global value
CHTCutScene* g_pcCutScene = NULL;


CHTCutScene::CHTCutScene(){
	// Initialize
	m_pGB = NULL;
	m_pMC = NULL;
	m_pVW = NULL;
	m_pME = NULL;
	m_hWnd=0;
	m_bContinue = HT_TRUE;

	if(!g_pcCutScene)g_pcCutScene = this;
}


CHTCutScene::~CHTCutScene(){
}

HRESULT CHTCutScene::Run(LPTSTR szMovie, HWND hWnd, HINSTANCE hInstance, HTbool bFullScreen)
{
	m_hWnd = hWnd;
	m_bFullScreen = bFullScreen;

	if(g_pcCutScene!=this){
		Msg("CHTCutScene::Run() Could not initialize!");
		return HT_FAIL;
	}

	// Return HT_FAIL if m_hWnd is not initialized
	if(!m_hWnd){
		Msg("CHTCutScene::Run() Cannot be used without initialize!");
		return HT_FAIL;
	}
	// Save Current WndProc
	m_prevWinProc = GetWindowLong( m_hWnd, GWL_WNDPROC);
	if(!m_prevWinProc){
		Msg("CHTCutScene::Run() Cannot get information about WndProc");
		return HT_FAIL;
	}

	// Set new WndProc
	SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)WndProc);

	this->PlayCutScene(szMovie, m_hWnd, hInstance, m_bFullScreen);	

	// Restore WndProc
	if(!SetWindowLong( m_hWnd, GWL_WNDPROC, m_prevWinProc)){
		Msg("CHTCutScene::Run() Cannot restore WndProc");
		return HT_FAIL;
	}
	return HT_OK;
}


HRESULT CHTCutScene::PlayCutScene(LPTSTR szMovie, HWND hWnd, HINSTANCE hInstance, HTbool bFullScreen)	
{
    HRESULT hr;
	m_hWnd = hWnd;
	m_bFullScreen = bFullScreen;

    if (!szMovie)
        return E_POINTER;


    // Initialize COM
    if (FAILED(hr = CoInitialize(NULL)))
        return hr;

    // Get DirectShow interfaces
    if (FAILED(hr = GetInterfaces()))
    {
        CoUninitialize();
        return hr;
    }

	// Play the movie / cutscene
    hr = PlayMedia(szMovie, hInstance);

    // Release DirectShow interfaces
    CleanupInterfaces();
    CoUninitialize();

    return hr;
}


HRESULT CHTCutScene::GetInterfaces()
{
    HRESULT hr = S_OK;

    // Instantiate filter graph interface
    JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, 
                         IID_IGraphBuilder, (void **)&m_pGB));

    // Get interfaces to control playback & screensize
    JIF(m_pGB->QueryInterface(IID_IMediaControl,  (void **)&m_pMC));
    JIF(m_pGB->QueryInterface(IID_IVideoWindow,   (void **)&m_pVW));

    // Get interface to allow the app to wait for completion of playback
    JIF(m_pGB->QueryInterface(IID_IMediaEventEx,  (void **)&m_pME));

    return S_OK;

    // In case of failure, the helper macro jumps here
CLEANUP:
    CleanupInterfaces();
    return(hr);
}


void CHTCutScene::CleanupInterfaces()
{
    // Release the DirectShow interfaces
    RELEASE(m_pGB);
    RELEASE(m_pMC);
    RELEASE(m_pVW);
    RELEASE(m_pME);
}


void CHTCutScene::CloseCutscene()
{
    // Stop playback and exit
    if (m_pMC)
        m_pMC->Stop();

    m_bContinue = FALSE;
}


HRESULT CHTCutScene::PlayMedia(LPTSTR lpszMovie, HINSTANCE hInstance)
{
    USES_CONVERSION;

    HRESULT hr = S_OK;
    WCHAR wFileName[MAX_PATH];
    BOOL bSleep=TRUE;

    if (!lpszMovie)
        return E_POINTER;

    // Convert filename to wide character string
    wcsncpy(wFileName, T2W(lpszMovie), MAX_PATH-1);
    wFileName[MAX_PATH - 1] = 0;

    // Allow DirectShow to create the FilterGraph for this media file
    hr = m_pGB->RenderFile(wFileName, NULL);
    if (FAILED(hr)) {
        Msg(TEXT("Failed(0x%08lx) in RenderFile(%s)!\r\n"), hr, lpszMovie);
        return hr;
    }

    // Set the message drain of the video window to point to our hidden
    // application window.  This allows keyboard input to be transferred
    // to our main window for processing.
    //
    // If this is an audio-only or MIDI file, then put_MessageDrain will fail.
    //
    hr = m_pVW->put_MessageDrain((OAHWND) m_hWnd);
    if (FAILED(hr))
    {
        Msg(TEXT("Failed(0x%08lx) to set message drain for %s.\r\n\r\n")
            TEXT("This sample is designed to play videos, but the file selected ")
            TEXT("has no video component."), hr, lpszMovie);
        return hr;
    }



    // Set screen
    hr = SetScreen();
    if (FAILED(hr)) {
        Msg(TEXT("Failed(%08lx) to set fullscreen!\r\n"), hr);
        return hr;
    }

    // Display first frame of the movie
    hr = m_pMC->Pause();
    if (FAILED(hr)) {
        Msg(TEXT("Failed(%08lx) in Pause()!\r\n"), hr);
        return hr;
    }

    // Start playback
    hr = m_pMC->Run();
    if (FAILED(hr)) {
        Msg(TEXT("Failed(%08lx) in Run()!\r\n"), hr);
        return hr;
    }

    // Update state variables
    m_bContinue = TRUE;

    // Enter a loop of checking for events and sampling keyboard i6nput
    while (m_bContinue)
    {
        MSG msg;
        long lEventCode, lParam1, lParam2;

        // Reset sleep flag
        bSleep = TRUE;

        // Has there been a media event?  Look for end of stream condition.
        if(E_ABORT != m_pME->GetEvent(&lEventCode, (LONG_PTR *) &lParam1, 
                                    (LONG_PTR *) &lParam2, 0))
        {
            // Is this the end of the movie?
            if (lEventCode == EC_COMPLETE)
            {
                m_bContinue = FALSE;
                bSleep = FALSE;
            }

            // Free the media event resources
            hr = m_pME->FreeEventParams(lEventCode, lParam1, lParam2);
            if (FAILED(hr))
            {
                Msg(TEXT("Failed(%08lx) to free event params (%s)!\r\n"),
                    hr, lpszMovie);
            }
        }

        // Give system threads time to run (and don't sample user input madly)
        if (bSleep)
            Sleep(KEYBOARD_SAMPLE_FREQ);

        // Check and process window messages (like our keystrokes)
        while (PeekMessage (&msg, m_hWnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return hr;
}

// 수정 되어야 함.!!!!
HRESULT CHTCutScene::SetScreen(void)
{
    HRESULT hr=S_OK;
    static HWND hDrain=0;

    if (!m_pVW)
        return S_FALSE;

	LIF(m_pME->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0));

	if(m_bFullScreen){
		// Save current message drain
		LIF(m_pVW->get_MessageDrain((OAHWND *) &hDrain));

		// Set message drain to application main window
		LIF(m_pVW->put_MessageDrain((OAHWND) m_hWnd));

		// Switch to full-screen mode
		LIF(m_pVW->put_FullScreenMode(OATRUE));

		// Set parent, the application window 
		LIF(m_pVW->put_Owner((OAHWND)m_hWnd));
	}
	else{
		RECT rect;
		GetClientRect(m_hWnd, &rect);
		LIF(m_pVW->SetWindowPosition(rect.left, rect.top, rect.right, rect.bottom));

		LIF(m_pVW->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN));
		
		// Switch to windowed mode
		LIF(m_pVW->put_FullScreenMode(OAFALSE));

		// Set parent, the application window 
		LIF(m_pVW->put_Owner((OAHWND)m_hWnd));

		// Undo change of message drain
		LIF(m_pVW->put_MessageDrain((OAHWND)hDrain));

		// Set message drain to application main window
		LIF(m_pVW->SetWindowForeground(-1));

		UpdateWindow(m_hWnd);
		SetForegroundWindow(m_hWnd);
		SetFocus(m_hWnd);
	}
    return hr;
}


HTvoid CHTCutScene::Msg(TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;

    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);

    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    _vsntprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');

    // This sample uses a simple message box to convey warning and error
    // messages.   You may want to display a debug string or suppress messages
    // altogether, depending on your application.
	if( m_hWnd )MessageBox(m_hWnd, szBuffer, TEXT("PlayCutscene Error"), MB_OK);
	else MessageBox(NULL, szBuffer, TEXT("PlayCutscene Error"), MB_OK);
}

HTbool CHTCutScene::isPlaying()
{
	return m_bContinue;
}

LRESULT CALLBACK CHTCutScene::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch( uMsg )
    {
        // Monitor keystrokes for manipulating video window
        // and program options
        case WM_KEYDOWN:
            switch( wParam )
            {
                case VK_ESCAPE:
                case VK_SPACE:
                case VK_RETURN:
					if(g_pcCutScene){
						g_pcCutScene->CloseCutscene();
					}
                    break;
            }
            break;

        case WM_DESTROY:
        case WM_CLOSE:
			if(g_pcCutScene){
				g_pcCutScene->CloseCutscene();
			}
			DestroyWindow(hWnd);
			PostQuitMessage(0);
			exit(0);
            break;
    }

    // Pass this message to the video window for notification of system changes
	if(g_pcCutScene){
		if(g_pcCutScene->m_pVW)
			g_pcCutScene->m_pVW->NotifyOwnerMessage((LONG_PTR) hWnd, uMsg, wParam, lParam);
	}

    return (LONG) DefWindowProc(hWnd, uMsg, wParam, lParam);
}



