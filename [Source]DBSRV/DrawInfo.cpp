#include <stdio.h>
#include "Basedef.h"
#include "DrawInfo.h"
#include "CUser.h"

#define TEXT_ROW_POINTS 20

int g_nCurrentTextY = 10;

extern unsigned char LocalIP[4];
extern unsigned short LocalPort;

extern int		ServerIndex;
extern CUser	pUser[MAX_SERVERNUMBER];
extern char		g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];

void PrintText( HDC hDC, char *pszFormat, ... );

void DrawInformations( HDC hDC )
{
	if ( hDC == NULL ) return;
	int nIndex=0; g_nCurrentTextY = 10;
	PrintText( hDC, "DB Server");
	PrintText( hDC, "Server Zone Status" );
	for(int i=0; i<MAX_SERVER; i++)
	{	if(pUser[i].Mode==USER_EMPTY) continue;
		PrintText( hDC, "%d   -   World: %d,   Zone: %d,   IP: %s,   User:%d", nIndex++, ServerIndex+1, i+1, g_pServerList[ServerIndex][i+1], pUser[i].Count );
	}
}

void PrintText( HDC hDC, char *pszFormat, ... )
{
	static char szText[512] = {0,};

	va_list vl;
	va_start( vl, pszFormat );
    vsprintf( szText, pszFormat, vl );
	TextOut( hDC, 10, g_nCurrentTextY, szText, strlen(szText) );
	va_end( vl );

	g_nCurrentTextY += TEXT_ROW_POINTS;
}