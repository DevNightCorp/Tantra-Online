#include "stdafx.h"
#include "HTextern.h"
#include "htinformationwin.h"

#define HT_EXTRA_NOTIFY_DLG_START_NUM	88 // 여분의 공지사항창 시작 번호

CHTInformationWin::CHTInformationWin(void) : m_bInformationWin_DlgSw(HT_FALSE)
{
	for( HTint i = 0; i < HT_INFORMATIONWIN_NUM_MAX ; ++i )
	{
		m_bInformationWin_Dlg[i].bInformationWin_Dlg = HT_FALSE;
		m_bInformationWin_Dlg[i].iInductNo = -1;
	}
}

CHTInformationWin::~CHTInformationWin(void)
{
}

//	공지창 켬
HTvoid CHTInformationWin::HT_vInformationWin_SetActive( HTchar* pStr, HTint iInductNo )
{
	m_bInformationWin_DlgSw = HT_TRUE;
	
	for( HTint i = 0; i < HT_INFORMATIONWIN_NUM_MAX ; ++i )
	{
		if( m_bInformationWin_Dlg[i].bInformationWin_Dlg == HT_FALSE )
		{
			m_bInformationWin_Dlg[i].bInformationWin_Dlg = HT_TRUE;
			m_bInformationWin_Dlg[i].iInductNo = iInductNo;
            
			HTint iDlgNo = -1;
			switch( i )
			{
				case 0 : iDlgNo = _DIALOG_INFORMATION1;	break;
				case 1 : iDlgNo = _DIALOG_INFORMATION2;	break;
				case 2 : iDlgNo = _DIALOG_INFORMATION3;	break;
				case 3 : iDlgNo = _DIALOG_INFORMATION4;	break;
				default : break;
			}
			if( iDlgNo != -1 )
			{
				g_cMainUISystem->HT_hrAddDraw( iDlgNo, iInductNo );
				g_cMainUISystem->HT_vSetLongText( iDlgNo, 0, pStr );
			}

			return;
		}
	}
}

//	공지창 끔
HTvoid CHTInformationWin::HT_vInformationWin_SetAntiActive( HTint iDlgNo )
{
	if( m_bInformationWin_DlgSw == HT_TRUE )
	{
		HTint iActiveDlgNo=0;
		for( HTint i = 0; i < HT_INFORMATIONWIN_NUM_MAX; ++i )
		{ 
			switch( i )
			{
				case 0 : iActiveDlgNo = _DIALOG_INFORMATION1;	break;
				case 1 : iActiveDlgNo = _DIALOG_INFORMATION2;	break;
				case 2 : iActiveDlgNo = _DIALOG_INFORMATION3;	break;
				case 3 : iActiveDlgNo = _DIALOG_INFORMATION4;	break;
				default : return;
			}
			if( iActiveDlgNo == iDlgNo )
			{
				m_bInformationWin_Dlg[i].bInformationWin_Dlg = HT_FALSE;
				m_bInformationWin_Dlg[i].iInductNo = -1;
				break;
			}
		}
		g_cMainUISystem->HT_hrDelDraw( iDlgNo );
		
		HTbool bRes = HT_FALSE;
		for( HTint i = 0; i < HT_INFORMATIONWIN_NUM_MAX; ++i )
			bRes |= m_bInformationWin_Dlg[i].bInformationWin_Dlg;
		m_bInformationWin_DlgSw = bRes;
	}
}

HTvoid CHTInformationWin::HT_vInformationWin_SetAntiActiveWithInductNo( HTint iInductNo )
{
	if( iInductNo <= 0 ) // default가 -1이기 때문
		return;

	if( m_bInformationWin_DlgSw == HT_TRUE )
	{
		for( HTint i = 0; i < HT_INFORMATIONWIN_NUM_MAX; ++i )
		{
			if( m_bInformationWin_Dlg[i].iInductNo == iInductNo )
			{
				m_bInformationWin_Dlg[i].bInformationWin_Dlg = HT_FALSE;
				m_bInformationWin_Dlg[i].iInductNo = -1;
				break;
			}
		}
		if( i == HT_INFORMATIONWIN_NUM_MAX ) // Dlg를 찾지 못했을 경우
			return;

		HTint iDlgNo = 0;
		// 창 닫기
		switch( i )
		{
			case 0 : iDlgNo = _DIALOG_INFORMATION1;	break;
			case 1 : iDlgNo = _DIALOG_INFORMATION2;	break;
			case 2 : iDlgNo = _DIALOG_INFORMATION3;	break;
			case 3 : iDlgNo = _DIALOG_INFORMATION4;	break;
			default : return;
		}
		g_cMainUISystem->HT_hrDelDraw( iDlgNo, iInductNo );

		HTbool bRes = HT_FALSE;
		for( HTint i = 0; i < HT_INFORMATIONWIN_NUM_MAX; ++i )
			bRes |= m_bInformationWin_Dlg[i].bInformationWin_Dlg;
		m_bInformationWin_DlgSw = bRes;
	}
}

HTRESULT
CHTInformationWin::HT_hrInformationWin_DlgCheck( HTint iDlgNo, HTint iProp )
{
	if( m_bInformationWin_DlgSw == HT_FALSE )
		return HT_FAIL;

	if( iProp == _PROP_PUSHBTN_IN_DLG )
	{
		this->HT_vInformationWin_SetAntiActive( iDlgNo );
	}

	return HT_OK;
}