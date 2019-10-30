#ifndef __HTCUTSCENE_H__
#define __HTCUTSCENE_H__

#include <dshow.h>

class CHTCutScene
{
public:
	CHTCutScene();
	~CHTCutScene();
	HTbool			isPlaying();
	HRESULT			Run(LPTSTR szMovie, HWND hWnd, HINSTANCE hInstance, HTbool bFullScreen);
	HRESULT			PlayCutScene(LPTSTR szMovie, HWND hWnd, HINSTANCE hInstance, HTbool bFullScreen);
	HTvoid			CloseCutscene();
	
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND			m_hWnd;
	HTbool			m_bContinue;
	HTbool			m_bFullScreen;
	// Save Prevous WndProc
	LONG			m_prevWinProc;

	HRESULT			PlayMedia(LPTSTR lpszMovie, HINSTANCE hInstance);
	HRESULT			GetInterfaces(HTvoid);
	HRESULT			SetScreen(HTvoid);
	HTvoid			CleanupInterfaces(HTvoid);
	HTvoid			Msg(TCHAR *szFormat, ...);

public:
	IGraphBuilder  *m_pGB;
	IMediaControl  *m_pMC;
	IVideoWindow   *m_pVW;
	IMediaEventEx  *m_pME;
};

#endif
