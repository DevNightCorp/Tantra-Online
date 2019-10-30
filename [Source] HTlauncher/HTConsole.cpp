#include "stdafx.h"
#include "HTEngineHandler.h"
#include "HTConsole.h"

CHTConsole g_oConsole;

CHTConsole::CHTConsole()
{
	m_bActivate	= HT_FALSE;

	m_eInputTextFont = HT_FONT_ARIAL_20;
	m_clrInputText = HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	m_strInputText = _T("");
	m_rcInputText.left = 0;
	m_rcInputText.top = 20;
	m_rcInputText.right = 1024;
	m_rcInputText.bottom = 40;

	m_eOutputTextFont = HT_FONT_ARIAL_20;
	m_clrOutputText = HT_COLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	m_strOutputText = _T("");
	m_rcOutputText.left = 0;
	m_rcOutputText.top = 40;
	m_rcOutputText.right = 1024;
	m_rcOutputText.bottom = 60;

	m_mapConsoleVariables.clear();
}

CHTConsole::~CHTConsole()
{
	std::map< string, HT_CONSOLE_VARIABLE* >::iterator it = m_mapConsoleVariables.begin();
	while ( it != m_mapConsoleVariables.end() )
	{
		HT_DELETE( it->second );

		it = m_mapConsoleVariables.erase( it );
	}
}

HTRESULT CHTConsole::HT_hrActivateOrNot()
{
	if ( m_bActivate )
		m_bActivate = HT_FALSE;
	else
		m_bActivate = HT_TRUE;

	return ( HT_OK );
}

HTRESULT CHTConsole::HT_hrRender()
{
	if ( !m_bActivate )
		return ( HT_OK );

	CHTString strPlusCarot;
	strPlusCarot = m_strInputText + _T("_");
	g_pEngineHandler->HT_hrRenderText( m_eInputTextFont, (HTtchar*)strPlusCarot, m_clrInputText, m_rcInputText, 
		TEXT_FORMATING_MULTILINE_VTOP_LEFT_CLIP );

	if ( !m_strOutputText.HT_bIsEmpty() )
		g_pEngineHandler->HT_hrRenderText( m_eOutputTextFont, (HTtchar*)m_strOutputText, m_clrOutputText, m_rcOutputText, 
			TEXT_FORMATING_MULTILINE_VTOP_LEFT_CLIP );

	return ( HT_OK );
}

HTRESULT CHTConsole::HT_hrInput( WPARAM wParam )
{
	if ( !m_bActivate )
		return ( HT_OK );

	switch ( wParam ) 
	{
	case VK_BACK:
		m_strInputText--;
		break;
	case VK_OEM_3:
		m_bActivate = HT_FALSE;
		break;
	case VK_RETURN:
		return ( HT_hrProcessInput() );
	case VK_OEM_PERIOD:
		m_strInputText += ".";
		break;
	default:
		m_strInputText += (HTtchar)wParam;
	}

	return ( HT_OK );
}

HTRESULT CHTConsole::HT_hrRegisterVariable( HTtchar* szCommand, HTfloat* pVariable )
{
	HT_CONSOLE_VARIABLE* pItem = new HT_CONSOLE_VARIABLE;
	pItem->m_byType = HT_CVTYPE_FLOAT;
	pItem->m_pVariable = pVariable;

	m_mapConsoleVariables.insert( std::map< string, HT_CONSOLE_VARIABLE* >::value_type( szCommand, pItem ) );

	return ( HT_OK );
}

HTRESULT CHTConsole::HT_hrRegisterVariable( HTtchar* szCommand, HTint* pVariable )
{
	HT_CONSOLE_VARIABLE* pItem = new HT_CONSOLE_VARIABLE;
	pItem->m_byType = HT_CVTYPE_INT;
	pItem->m_pVariable = pVariable;

	m_mapConsoleVariables.insert( std::map< string, HT_CONSOLE_VARIABLE* >::value_type( szCommand, pItem ) );

	return ( HT_OK );
}

HTRESULT CHTConsole::HT_hrProcessInput()
{
	HTtchar seps[] = " ,\t\n";
	HTtchar *pszCommand = HT_NULL, *pszValue = HT_NULL;

	pszCommand = _tcstok( (HTtchar*)m_strInputText, seps );
	if ( pszCommand != HT_NULL )
	{
		pszValue = _tcstok( NULL, seps );
	}

	std::map< string, HT_CONSOLE_VARIABLE* >::iterator it;
	it = m_mapConsoleVariables.find( pszCommand );
	if ( it != m_mapConsoleVariables.end() )
	{
		if ( it->second )
		{
			if ( pszValue )
			{
				switch ( it->second->m_byType )
				{
				case HT_CVTYPE_FLOAT:
					*(HTfloat*)(it->second->m_pVariable) = (HTfloat)_tstof( pszValue );
					m_strOutputText.HT_szFormat( "%s = %f", (HTtchar*)m_strInputText, *(HTfloat*)(it->second->m_pVariable) );
					break;
				case HT_CVTYPE_INT:
					*(HTint*)(it->second->m_pVariable) = (HTint)_tstoi( pszValue );
					m_strOutputText.HT_szFormat( "%s = %d", (HTtchar*)m_strInputText, *(HTint*)(it->second->m_pVariable) );
					break;
				default:
					break;
				}
			}
			else
			{
				switch ( it->second->m_byType )
				{
				case HT_CVTYPE_FLOAT:
					m_strOutputText.HT_szFormat( "%s = %f", pszCommand, *(HTfloat*)(it->second->m_pVariable) );
					break;
				case HT_CVTYPE_INT:
					m_strOutputText.HT_szFormat( "%s = %d", pszCommand, *(HTint*)(it->second->m_pVariable) );
					break;
				default:
					break;
				}
			}
		}
	}
	else
	{
		m_strOutputText.HT_hrCleanUp();
	}

	return ( HT_OK );
}
