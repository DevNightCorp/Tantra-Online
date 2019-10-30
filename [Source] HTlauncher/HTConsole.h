//----------------------------------------------------------------------------//
//																			  //
//	Project : Console box editing and command proc							  //
//	File	: HTConsole.h      												  //
//	Author	: Assrada														  //
//	History : 2003/08/06, Initiated by Assrada 								  //
//				- init                                         				  //
//																			  //
//  Copyright (c) 2000-2003 Hanbitsoft Corp.  All rights reserved.			  //
//----------------------------------------------------------------------------//

#ifndef _HTCONSOLE_H_
#define _HTCONSOLE_H_

enum HT_CONSOLE_VARIABLE_TYPE
{
	HT_CVTYPE_FLOAT	= 0,
	HT_CVTYPE_INT	= 1,
};

typedef struct _HT_CONSOLE_VARIABLE
{
	HTbyte		m_byType;
	HTvoid*		m_pVariable;
} HT_CONSOLE_VARIABLE;

class CHTConsole
{
public:
				CHTConsole();
				~CHTConsole();

	HTRESULT	HT_hrActivateOrNot();
	HTbool		HT_bIsActivate()	{ return ( m_bActivate ); }

	HTRESULT	HT_hrRender();
	HTRESULT	HT_hrInput( WPARAM wParam );

	HTRESULT	HT_hrRegisterVariable( HTtchar* szCommand, HTfloat* pVariable );
	HTRESULT	HT_hrRegisterVariable( HTtchar* szCommand, HTint* pVariable );

private:
	HTRESULT	HT_hrProcessInput();

private:
	HTbool			m_bActivate;

	// Input Edit Text
	HT_FONT_TYPE	m_eInputTextFont;
	HT_COLOR		m_clrInputText;
	CHTString		m_strInputText;
	HT_RECT			m_rcInputText;

	// Console Command
	std::map< string, HT_CONSOLE_VARIABLE* > m_mapConsoleVariables;

	// Output Text
	HT_FONT_TYPE	m_eOutputTextFont;
	HT_COLOR		m_clrOutputText;
	CHTString		m_strOutputText;
	HT_RECT			m_rcOutputText;

};

extern CHTConsole g_oConsole;

#endif	// #ifndef _HTCONSOLE_H_