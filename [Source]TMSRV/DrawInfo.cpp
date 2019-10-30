#include <stdio.h>
#include "BaseDef.h"
#include "DrawInfo.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

#define TEXT_ROW_POINTS 18

int g_nCurrentTextY = 10;

extern unsigned char LocalIP1[4];
extern unsigned short LocalPort;

extern double g_drgRwdCorrect[eSiz_RwdCorrect][eSiz_Type];
//extern double g_dRwdPranaCorrect;
//extern double g_dRwdGoldCorrect;
//extern double g_drgRwdCorrect[eRwd_Item][eRwd_Total];

extern int g_nGiftItemIndex;
extern int g_nGiftItemMaxCount;
extern int g_nGiftItemCount;
extern int g_nGiftItemFirstCount;
extern short  g_snGiftItemGenTime;

extern int g_iViewGridX;
extern int g_iViewGridY;
extern int g_iHalfGridX;
extern int g_iHalfGridY;

extern int ServerGroup;
extern int ServerIndex;

extern int	g_ItemRefineScale;
extern int	g_ItemRefineGMScale;

extern E_COUNTRY_ID g_eCountryID;

void PrintText( HDC hDC, COLORREF crText, char *pszFormat, ... );
void LineFeed();

void DrawInformations( HDC hDC )
{
	if ( hDC == NULL ) return;
	PrintText( hDC, RGB( 128, 0, 128 ), "ZONE SERVER'S INFORMATIONS" ); 
	LineFeed();
	PrintText( hDC, RGB( 0, 0, 255 ), "SERVER SETTINGS" );
	PrintText( hDC, 0, "Server: ZONE SERVER" );
	PrintText( hDC, 0, "World: %d, Zone: %d, CountryID: %d", ServerGroup, ServerIndex+1, (int)g_eCountryID );
	PrintText( hDC, 0, "IP: %d.%d.%d.%d, Port: %d", LocalIP1[0], LocalIP1[1], LocalIP1[2], LocalIP1[3], LocalPort );
	LineFeed();
	PrintText( hDC, RGB( 0, 0, 255 ), "GRID SETTINGS" ); 
	PrintText( hDC, 0, "ViewGrid( %d, %d )", g_iViewGridX, g_iViewGridY );
	PrintText( hDC, 0, "HalfGrid( %d, %d )", g_iHalfGridX, g_iHalfGridY );
	LineFeed();
	PrintText( hDC, RGB( 0, 0, 255 ), "REWARD CONSTANTS SETTINGS" ); 
	//PrintText( hDC, 0, "Reward brahman point multiplied by %1.3f", g_drgRwdCorrect[eRwd_Braman][eRwd_Total] );
	PrintText( hDC, 0, "Reward prana multiplied by %1.3f", g_drgRwdCorrect[eRwd_Prana][eRwd_Total]);
	PrintText( hDC, 0, "Reward gold drop multiplied by %1.3f", g_drgRwdCorrect[eRwd_Gold][eRwd_Total]);
	//PrintText( hDC, 0, "Reward item drop rate multiplied by %1.3f",g_drgRwdCorrect[eRwd_Item][eRwd_Total] );
	LineFeed();
	PrintText( hDC, RGB( 0, 0, 255 ), "ITEM REFINING SCALE");
	PrintText( hDC, 0, "Item Refine Scale: %d", g_ItemRefineScale);
	PrintText( hDC, 0, "Item Refine GM Scale: %d", g_ItemRefineGMScale );
	LineFeed();
	PrintText( hDC, RGB( 0, 0, 255 ), "EVENT STATUS");
	PrintText( hDC, 0, "Event-Item Index: %d", g_nGiftItemIndex);
	PrintText( hDC, 0, "Event-Item Max-Count: %d, Event-Item Remain-Count: %d,", g_nGiftItemFirstCount, g_nGiftItemCount );
	PrintText( hDC, 0, "Event-Item Create Time Interval: %d,", g_snGiftItemGenTime );
}			

void PrintText( HDC hDC, COLORREF crText, char *pszFormat, ... )
{
	static char szText[512] = {0,};
	static COLORREF crCur = RGB( 0, 0, 0 );

	va_list vl;
	va_start( vl, pszFormat );
    vsprintf( szText, pszFormat, vl );
	if ( crText != crCur ) 
	{
		SetTextColor( hDC, crText );
		crCur = crText;
	}
	TextOut( hDC, 10, g_nCurrentTextY, szText, strlen(szText) );
	va_end( vl );

	g_nCurrentTextY += TEXT_ROW_POINTS;
}

void LineFeed()
{
	g_nCurrentTextY += TEXT_ROW_POINTS;
}