#include "stdafx.h"
#include "Imm.h"
#include "HTextern.h"
#include "htimemgr.h"
#include "WinAble.h"

HTImeMgr::HTImeMgr(void)
{
	//	ÀÏº»¾î¸¦ À§ÇÑ Àü°¢ ¹Ý°¢ ¸ðµå
	m_bEmForJapan = FALSE;
	//	ÀÌÈÄ ¸î¹ÙÀÌÆ®±îÁö´Â ¹ÞÁö ¸»¾Æ ´Þ¶ó°í....¿äÃ»
	m_byLimitRecivewParam = 0;
}

HTImeMgr::~HTImeMgr(void)
{
}

int HTImeMgr::GetIMEName(void)
{
	//	Set Init String
	this->InitString();

	HKL hHkl = GetKeyboardLayout( 0 );
	memset(m_szInputLang, 0 , sizeof(m_szInputLang));
	int n = ImmGetDescription( hHkl, m_szInputLang, sizeof(m_szInputLang));

	//ÊäÈë·¨Ãû×Ö
	g_strImeName = m_szInputLang;

	//	CompStrÀ» Ç¥ÇöÇÒ°ÍÀÏÁö Á¤ÇÔ ÀÏ´Ü ÇÑ±ÛÀº Ç¥Çö 
	if( g_iInationalType == INATIONALTYPE_KOREA )//|| 
		//g_iInationalType == INATIONALTYPE_JAPEN )
	{
		g_bShowCompStrSw = HT_TRUE;
	}
	else
	{
		g_bShowCompStrSw = HT_FALSE;
	}

	return 0;
}

//
//	Display the IME¡¡
//
int HTImeMgr::InputString()
{
	//Êµ¼ÊÊäÈëµÄ×Ö´®
	g_strResultText		= m_szInputTextStr;
	g_strCompStr		= m_szCompStr; 
	g_strCompReadStr	= m_szCompReadStr; 
	g_iCandiSelectionNo	= m_dwCandiSelectionNo % 9;
	g_idwCandidateListNo = m_dwCandidateListNo % 10;

	//ºóÑ¡¿ò
	//if (m_dwCandidateListNo > 0)
	{
		char list[1024]="";
		char list2[100]="";

		for(DWORD i=0 ; i<m_dwCandidateListNo ; i++)
		{
			sprintf(list2, "%d : %s, ", i%9+1, m_szCandidateStr[i]);
			strcat(list, list2);
			g_strCandidateList[i] = list2;
		}

		if( m_dwCandidateListNo>=0 && m_dwCandidateListNo<9 )
		{
			for( i=m_dwCandidateListNo ; i<9 ; i++ )
			{
				g_strCandidateList[i].HT_hrCleanUp();
			}
		}
	}

	//	UI¿¡ ±ÛÀÚÃâ·Â
	g_cUIManager->HT_UpdateEditBoxText(_T(""));

	return 0;
}


//
//	È¡³öµ±Ç°µÄºóÑ¡×ÖÁÐ±í
//
int HTImeMgr::GetIMECandidate(void)
{
	HIMC			hIMC		= ImmGetContext(m_hWnd);
	DWORD			dwSize		= 0;
	DWORD			dwListCount = 0;
	LPCANDIDATELIST lpC;

	dwSize = ImmGetCandidateList(hIMC, 0x0, NULL, 0);
	SetIMEPos(hIMC);	

	if( dwSize )
	{
		lpC = (LPCANDIDATELIST)new TCHAR[dwSize];
		ImmGetCandidateList(hIMC, 0x0, lpC, dwSize);
		
		m_dwCandiCount			= lpC->dwCount;
		m_dwCandiSelectionNo	= lpC->dwSelection;
		
		// some IME has maxinum candilist for 10
		m_dwPageStartNo			= (m_dwCandiSelectionNo/9)*9;
		m_dwPageSize			= (m_dwCandiCount-m_dwPageStartNo);
		if( m_dwPageSize >= 9 )
			m_dwPageSize = 9;
		else
			m_dwPageSize = m_dwPageSize % 9;

		for (int id=0, i=m_dwPageStartNo ; i<(int)(m_dwPageStartNo+m_dwPageSize) ; id++, i++)
		{
			//	´õÅ©¸é »Ï·Î·Õ ³ª°£´Ù~
			if( i>=(int)m_dwCandiCount )
				break;

			LPSTR lpStr = (LPSTR)lpC + lpC->dwOffset[i];
			if( lpStr)
				strcpy( m_szCandidateStr[id], lpStr );
		}

		m_dwCandidateListNo = id;//curry candidate list number

		if(lpC)
		{
			delete[](lpC); 
			(lpC)=0;
		}
	}

	ImmReleaseContext(m_hWnd, hIMC);

	return 0;
}


//
//	È¡µÃµ±Ç°×é×Ö¿òÖÐµÄÄÚÈÝ
//
int HTImeMgr::GetIMEComposition(void)
{
	HIMC hIMC = ImmGetContext(m_hWnd);
	SetIMEPos(hIMC);

	//GCS_COMPSTR
	m_dwCompStrLen = MyImmGetCompositionString(hIMC,GCS_COMPSTR,m_szCompStr,sizeof(m_szCompStr));
	m_dwCompStrLen /= sizeof(MYCHAR);
	m_szCompStr[m_dwCompStrLen] = MYTEXT('\0');

	//GCS_COMPREADSTR
	m_dwCompReadStrLen = MyImmGetCompositionString(hIMC,GCS_COMPREADSTR,m_szCompReadStr,sizeof(m_szCompReadStr));
	m_dwCompReadStrLen /= sizeof(MYCHAR);
	m_szCompReadStr[m_dwCompReadStrLen] = MYTEXT('\0');
    
	ImmReleaseContext(m_hWnd, hIMC);

	return 0;
}

int HTImeMgr::OnChar(WPARAM wParam, LPARAM lParam)
{
	//	ÄÁÆ®·ÑÅ°°¡ ´­·¯Á® ÀÖÀÀ »óÅÂ¶ó¸é ½ºÅµÇÑ´Ù.
	if( GetAsyncKeyState( VK_CONTROL ) < 0 )
		return 1;

	//	ÀÌÈÄ ¸î¹ÙÀÌÆ®±îÁö´Â ¹ÞÁö ¸»¾Æ ´Þ¶ó°í....¿äÃ»
	if( m_byLimitRecivewParam > 0 )
	{
		m_byLimitRecivewParam--;
		return 1;
	}

	m_wParam = wParam;
	switch(wParam)
	{
		//	CTRL+ENTER ¸¦ Ä¡¸é °³ÇàµÇ´Â°ÍÀ» ¸·±âÀ§ÇØ »ðÀÔÇÑ ÄÚµå, '10'µðÆÄÀÎ º¯¼ö¸¦ ªOÁö¸øÇØ ±×³É ¼ýÀÚ·Î ÄÚµùÇÑ´Ù.
		//case 10:
		//	break;
		//	¿¹¿ÜÃ³¸®
		case VK_ESCAPE:
			this->InitString();
			break;
		case VK_TAB:
			break;
		case VK_RETURN:

			ClearCandidateList();

			//memset(m_szInputTextStr, 0, sizeof(m_szInputTextStr));
			//m_dwInputTextlen = 0;

			//this->InitString();
			return 1;

		case VK_BACK:

			if ( m_dwInputTextlen <= 0)
			{
				m_dwInputTextlen = 0;
				memset(m_szInputTextStr, 0, sizeof(m_szInputTextStr));
			}
			else
			{
				int iResult = _ismbstrail( (unsigned char*)m_szInputTextStr, (unsigned char*)(&m_szInputTextStr[m_dwInputTextlen-1]) );

				while ( iResult < 0 ) // ¸¶Áö¸· ¹ÙÀÌÆ®°¡ ±ÛÀÚÀÇ ½ÃÀÛÀÌ ¾Æ´Ñ°æ¿ì¿¡´Â
				{
					--m_dwInputTextlen;
					iResult = _ismbstrail( (unsigned char*)m_szInputTextStr, (unsigned char*)(&m_szInputTextStr[m_dwInputTextlen-1]) );
				}

				--m_dwInputTextlen;
			}

			m_szInputTextStr[m_dwInputTextlen]	= MYTEXT('\0');

			break;

		default:

			if( m_dwInputTextlen < 512 )
			{
				m_szInputTextStr[m_dwInputTextlen]	= (char)wParam;
				m_dwInputTextlen++;
				m_szInputTextStr[m_dwInputTextlen]	= MYTEXT('\0');
			}

			break;
	}

	return 0;
}

int HTImeMgr::ClearComposition(void)
{
	m_dwCompStrLen = 0;
	m_dwCompReadStrLen = 0;

	memset(m_szCompStr, 0, sizeof(m_szCompStr));
	memset(m_szCompReadStr, 0, sizeof(m_szCompReadStr));
	return 0;
}

int HTImeMgr::ClearCandidateList(void)
{
	m_dwCandidateListNo = 0;

	memset(m_szCandidateStr, 0, sizeof(m_szCandidateStr));
	memset(g_strCandidateList, 0, sizeof(g_strCandidateList));

	return 0;
}

int HTImeMgr::OnInputLangChange(WPARAM wParam, LPARAM lParam)
{
	GetIMEName();

	return 0;
}


//
//	when WM_IME_STARTCOMPOSITION
//
int HTImeMgr::OnStartComposition(WPARAM wParam, LPARAM lParam)
{
	return 0;
}


//
//	when WM_IME_ENDCOMPOSITION
//
int HTImeMgr::OnEndComposition(WPARAM wParam, LPARAM lParam)
{
	ClearComposition();

	return 0;
}


//
//	when WM_IME_COMPOSITION
//
int HTImeMgr::OnComposition(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	ClearComposition();
	GetIMEComposition();

	if( g_iInationalType == INATIONALTYPE_KOREA || g_iInationalType == INATIONALTYPE_JAPEN )
	{
		if (lParam & GCS_RESULTSTR)
		{
			HIMC hIMC = ImmGetContext(m_hWnd);
			DWORD dwLen = ::ImmGetCompositionString(hIMC,GCS_RESULTSTR,NULL,0L);
			if(dwLen)
			{
				LPSTR	pszResult;
				pszResult =  new char[ dwLen + sizeof(TCHAR) * 4];

				if (pszResult)
				{
					dwLen = ::ImmGetCompositionString(hIMC,GCS_RESULTSTR,pszResult,dwLen);
					pszResult[dwLen] = 0;
				}

				strncpy( m_szInputTextStr+m_dwInputTextlen, pszResult, dwLen );
				m_dwInputTextlen += dwLen;
				m_szInputTextStr[m_dwInputTextlen] = MYTEXT('\0');

				////×ª³ÉWM_CHARÏûÏ¢
				//LPBYTE p = (LPBYTE)pszResult;
				//while( *p )
				//	PostMessage(hWnd, WM_CHAR, (WPARAM)*p++, 1);//×ª³ÉWM_CHARÏûÏ¢
				
				delete [] pszResult;
			}
			ImmReleaseContext(m_hWnd, hIMC);
		}
	}

	return 0;
}

//
//	when WM_IME_NOTIFY
//
LRESULT HTImeMgr::OnImeNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
    {
        case IMN_OPENSTATUSWINDOW:
        case IMN_CLOSESTATUSWINDOW:
        case IMN_SETOPENSTATUS:
			break;

        case IMN_SETCONVERSIONMODE://The IMN_SETCONVERSIONMODE command is sent when the conversion mode of the input context is updated. 
			
			this->GetIMEName(); 

			break;

        case IMN_OPENCANDIDATE:
			
			if( lParam == 0x01 )
			{
				this->GetIMECandidate();
				this->InputString();
			}
				
			break;

        case IMN_CHANGECANDIDATE:
			
			if( lParam == 0x01 )
			{
				this->GetIMECandidate();
				this->InputString();
			}

			//return (DefWindowProc(hWnd, message, wParam, lParam));
			//this->GetIMECandidate();
			break;

        case IMN_CLOSECANDIDATE:

			if( lParam == 0x01 )
			{
				this->ClearCandidateList();
				this->InputString();
			}
			//return(DefWindowProc(hWnd, message, wParam, lParam));

            break;			
    }

    return 0;
}

int HTImeMgr::InitInput(HWND hWnd)
{
	m_dwProperty = ImmGetProperty(GetKeyboardLayout(0), IGP_PROPERTY);
	m_hWnd = hWnd;

	//³õÊ¼»¯Êµ¼ÊÕ¼ÓÃµÄ×ÖÊý£¬Ã¿¸ö×ÖÕ¼ÓÃµÄ×Ö½ÚÊý
	//for(int i=0; i<512; i++)
	//	m_nPerCharLen[i] = 0;

	m_dwInputTextlen = 0;
	m_dwCompStrLen = 0;
	m_dwCompReadStrLen = 0;
		
	m_dwCandiCount = 0;
	m_dwCandiSelectionNo = -1;
	m_dwPageStartNo = -1;
	m_dwPageSize = 0;
	m_dwCandidateListNo=0;

	//	Set Init String
	//	IMEÀº °èÈ¤º¸¿©¾ß ÇÏ±â ¶§¹®¿¡ ÃÖÃÊ ÇÑ¹ø¸¸ Init
	g_strImeName.HT_hrCleanUp();
	this->InitString();

	//g_cImeMgr.GetIMEName();

	return 0;
}

void HTImeMgr::InitString()
{
	//-----------------------------------------------------------------------------//
	//  ¼³¸í : IME String
	//  ÀÛ¼ºÀÏÀÚ / ÀÛ¼ºÀÚ : 2004.06.22 Á¤ÀÇ±Ô
	//-----------------------------------------------------------------------------//
	g_strResultText.HT_hrCleanUp();
	g_strCompStr.HT_hrCleanUp();
	g_strCompReadStr.HT_hrCleanUp();
	for( HTint i=0 ; i<10 ; i++ )
        g_strCandidateList[i].HT_hrCleanUp();
}

// Set IME Attribute
int HTImeMgr::SetIMEPos(HIMC hIMC)
{
	return 0;

	/*
	POINT pt={6000,6000};
	RECT rt={6000,6000,6001,6001};

	COMPOSITIONFORM csf;
	csf.dwStyle = CFS_FORCE_POSITION;
	csf.ptCurrentPos = pt;
	csf.rcArea =rt; 

	CANDIDATEFORM cdf;
	cdf.dwIndex = 0;
	cdf.dwStyle = CFS_CANDIDATEPOS;
	cdf.ptCurrentPos = pt;
	cdf.rcArea = rt;

	ImmSetCompositionWindow(hIMC, &csf);
	ImmSetCandidateWindow(hIMC, &cdf);
	ImmSetStatusWindowPos(hIMC, &pt);

	//ImmSetOpenStatus(hIMC, FALSE);
	//ImmSetConversionStatus(hIMC,IME_CMODE_SOFTKBD,IME_SMODE_NONE);
	return 0;
	//*/
}

//	
WPARAM HTImeMgr::wImeMgr_WPARAM()
{
	WPARAM wParam = m_wParam;
	m_wParam = 0;
	return wParam;
}

void HTImeMgr::vHTImeMgr_Setm_szInputTextStr( MYCHAR* szText )
{
	if( g_iInationalType == INATIONALTYPE_JAPEN )
	{
		HIMC hImc = ImmGetContext( g_hWnd );
		ImmNotifyIME( hImc, NI_COMPOSITIONSTR, CPS_CANCEL, 0 );
		ImmReleaseContext(g_hWnd, hImc);
	}

	memset( m_szCompStr, 0, 512 );
	memset( m_szCompReadStr, 0, 512 );
	strcpy( m_szInputTextStr, szText );
	m_dwInputTextlen = strlen( m_szInputTextStr );
	m_szInputTextStr[m_dwInputTextlen] = MYTEXT('\0');
}

void HTImeMgr::SetIMEWndPos()
{
	if( g_cUIManager )
	{
		HIMC				hIMC;
		COMPOSITIONFORM		Composition;
		//	Get Cursor Pos
		HTvector3 vecCursorPos = g_cUIManager->HT_GetEditBoxCursorPos();

		// Set composition window position
		Composition.dwStyle = CFS_POINT;
		Composition.ptCurrentPos.x = vecCursorPos.x;
		Composition.ptCurrentPos.y = vecCursorPos.y+3;
		ImmSetCompositionWindow(hIMC, &Composition);
		ImmReleaseContext(g_hWnd,hIMC);
	}
}

HTvoid
HTImeMgr::vImeMgr_SetLanguage( BOOL bAutoSet, DWORD dwLanguageCode )
{
	if( g_iInationalType == INATIONALTYPE_JAPEN )
		return;

	if( bAutoSet )
	{
		DWORD dwInationallanguageCode;
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

		HIMC			hIMC;
		hIMC = ImmGetContext(g_hWnd);
		ImmSetConversionStatus(hIMC, dwInationallanguageCode, 1);
		ImmReleaseContext(g_hWnd, hIMC);
	}
	else
	{
		HIMC			hIMC;
		hIMC = ImmGetContext(g_hWnd);
		ImmSetConversionStatus(hIMC, dwLanguageCode, 1);
		ImmReleaseContext(g_hWnd, hIMC);
	}
}

//	Return Emm for Japan
void 
HTImeMgr::bImeMgr_SetEmForJapan( int iImeIndex )
{
	m_bEmForJapan = iImeIndex;
}

//	Set Ime Mode Cancel
void
HTImeMgr::vImeMgr_SetImeModeCancel()
{
	//	Init Comp Str
	g_strCompStr.HT_hrCleanUp();
	//	Cancel Ime Mode
	HIMC hImc = ImmGetContext( g_hWnd );
	ImmNotifyIME( hImc, NI_COMPOSITIONSTR, CPS_CANCEL, 0 );
	ImmReleaseContext(g_hWnd, hImc);
}
//	ÀÌÈÄ ¸î¹ÙÀÌÆ®±îÁö´Â ¹ÞÁö ¸»¾Æ ´Þ¶ó°í....¿äÃ»
void
HTImeMgr::vImeMgr_SetLimitRecivewParam( BYTE byLimitCount )
{
	m_byLimitRecivewParam = byLimitCount;
}


		//if( dwlanguageCode == IME_CMODE_ALPHANUMERIC )
		//{
		//	//	ÀÏº» IME ¸ðµå¶ó¸é ²¨ÁØ´Ù.
		//	if( m_bEmForJapan )
		//	{
		//		MessageBox( NULL, "1", "Debug", MB_OK );
		//		INPUT Input;
		//		Input.type			= INPUT_KEYBOARD;
		//		Input.ki.dwFlags	= KEYEVENTF_EXTENDEDKEY;
		//		Input.ki.wVk		= VK_OEM_ENLW;
		//		Input.ki.wScan		= VK_OEM_ENLW;;
		//		Input.ki.time		= 0;
		//		
		//		UINT nResult;
		//		nResult = SendInput( 1, &Input, sizeof(INPUT) );
		//		this->bImeMgr_SetEmForJapan( 0 );
		//	}

		//	//HWND hWnd = ImmGetDefaultIMEWnd(GetActiveWindow());
		//	//CloseWindow( hWnd );
		//	//ImmSetConversionStatus(hIMC, dwlanguageCode, 1);
		//	//IME_SMODE_AUTOMATIC
		//}
		//else if( dwlanguageCode == IME_CMODE_JAPANESE )
		//{
			//SendMessage( g_hWnd, WM_KEYUP, VK_OEM_AUTO, NULL );

			//ImmSetConversionStatus(hIMC, dwlanguageCode, 1);
			//ImmSetConversionStatus(hIMC, dwlanguageCode, 1);

			//SendMessage( g_hWnd, VK_OEM_AUTO, NULL, NULL );
			//INPUT Input;
			////Input.type			= INPUT_KEYBOARD;
			////Input.ki.dwFlags	= KEYEVENTF_EXTENDEDKEY;
			////Input.ki.wVk		= VK_OEM_AUTO;
			////Input.ki.wScan		= VK_OEM_AUTO;;
			////Input.ki.time		= 0;
			//
			//UINT nResult;
			////nResult = SendInput( 1, &Input, sizeof(INPUT) );


			////INPUT Input;
			//Input.type			= INPUT_KEYBOARD;
			//Input.ki.dwFlags	= KEYEVENTF_EXTENDEDKEY;
			//Input.ki.wVk		= VK_OEM_ATTN;
			//Input.ki.wScan		= VK_OEM_ATTN;;
			//Input.ki.time		= 0;
			//
			////UINT nResult;
			//nResult = SendInput( 1, &Input, sizeof(INPUT) );

			
			//SendMessage( g_hWnd, WM_KEYUP, VK_OEM_ATTN, VK_OEM_ATTN );
		//}
