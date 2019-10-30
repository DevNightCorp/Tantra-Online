#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"

#include "htindividualstore.h"

#define STORE_PROCESS_NONE					0
#define STORE_PROCESS_REQ_START				1
#define STORE_PROCESS_STORE					2
#define STORE_PROCESS_REQ_END				3
#define STORE_PROCESS_REQ_BUY_LIST			4
#define STORE_PROCESS_BUY					5
#define STORE_PROCESS_REQ_BUY				6

#define INPUT_WIN_XPOS		400
#define INPUT_WIN_YPOS		300

#define STORE_MESSAGE_MAX_SIZE				51 // ÇÑ±Û 24ÀÚ

#define HT_STORE_SELL_ITEM_COUNT_BASIC		(MAX_MOBSTORE/2) // »óÁ¡¿¡ µî·ÏÇÒ ¼ö ÀÖ´Â ¾ÆÀÌÅÛ ±âº» °³¼ö

#define STORE_MSGTYPE_NONE					0
#define STORE_MSGTYPE_RUPIAINPUT			1
#define STORE_MSGTYPE_ITEMINPUT				2

CHTIndividualStore::CHTIndividualStore(void)
{
}

CHTIndividualStore::~CHTIndividualStore(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_INDIVIDUALWND1 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_INDIVIDUALWND2 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_BYELISTWND );
	g_cUIManager->HT_DeleteWindow( _DIALOG_MY_USEINFO_V3 );
}

HTvoid
CHTIndividualStore::HT_vIndividualStore_CleanUp()
{
}

HTvoid
CHTIndividualStore::HT_vIndividualStore_Init()
{
	//	Create Window
	this->HT_vIndividualStore_CreateWindow();

	m_byStoreProcess = STORE_PROCESS_NONE;
	m_iStoreID = 0;
	m_dwSelectKeyID = 0;

	m_szBuyMessage.HT_hrCleanUp();
	m_iTotalPrice = 0;
	m_iPrice = 0;
	m_iPackCount = 0;

	// ÆÇ¸ÅÇÒ ¸ñ·Ï
	ZeroMemory( m_sStoreItem, sizeof( MOBSTOREITEM )*MAX_MOBSTORE );
	m_byStoreItemNum = 0;
	m_byMaxStoreItemCount = HT_STORE_SELL_ITEM_COUNT_BASIC;

	// ±¸ÀÔÇÒ ¸ñ·Ï
	for( HTint i = 0 ; i < MAX_MOBSTORE; ++i )
		m_iBuyItem[i] = -1;
	m_byBuyItemNum = 0;
	ZeroMemory( m_iStoreItemKeyID, sizeof( HTint)*MAX_MOBSTORE );

	//	3ºÐ¿¡ ÇÑ¹ø¾¿ Ã¤ÆÃ ¸Þ½ÃÁö ³¯¸®±â À§ÇØ
	m_dwAutoChatMsgStartTime = GetTickCount();

	// »ç¿ë³»¿ª ÇÁ¸®¹Ì¾ö¼­ºñ½ºÀÇ Ã¼Å©¹öÆ°À» ¸ðµÎ È°¼ºÈ­ »óÅÂ·Î ½ÃÀÛ
	for (HTint i = 0; i < 6; i++)
	{
		m_iCheckUse[i] = 1;
	}

	//	MessageBox Type
	m_iStore_MsgBoxType = STORE_MSGTYPE_NONE;
}

//	Create Window
HTvoid CHTIndividualStore::	HT_vIndividualStore_CreateWindow()
{
	CHTString strMessage;
	HTint i,j;
	//	[_DIALOG_INDIVIDUALWND1]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_INDIVIDUALWND1, _T(""), 280, 356, g_cIndividualStore->HT_vEI_InputCheckForIndividualStore1, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_INDIVIDUALWND1, 5 );
	//	ÁÙ	Á¦¸ñ Ç¥½ÃÁÙ
	g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND1, 0, 8, 2, 36, 1400, 276, 6 );
	//	Texture °³ÀÎ»óÁ¡
	g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND1, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgInvenPrivateShop, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );//	°³ÀÎ»óÁ¡
	//	Label ÆÇ¸Å
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgShopSale, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 33, 64, 50, 18 );//	ÆÇ¸Å
	//	Label ÆÇ¸ÅÃÑ¾×
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgShopSaleTotalPrice, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 122, 265, 60, 17 );//	ÆÇ¸ÅÃÑ¾×
	//	Label ¼ÒÁö±Ý¾×
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgShopCarryRupia, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 122, 282, 60, 17 );//	¼ÒÁö±Ý¾×
	//	Label È®Àå±âÇÑ Ç¥½Ã
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 1, eMsgShopExpanceDate, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 115, 64, 137, 17 );//	È®Àå±âÇÑ
	//	Label ÆÇ¸ÅÃÑ¾× ¾×¼ö
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 2, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 184, 265, 75, 17 );
	//	Label ¼ÒÁö±Ý¾× ¾×¼ö
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 3, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 184, 282, 75, 17 );
	//	Button È®ÀÎ
	g_cUIManager->HT_AddButtonControl( _DIALOG_INDIVIDUALWND1, 5, 159, 56, 326, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 326, 89, 19 );//	È®ÀÎ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_INDIVIDUALWND1, 5 );
	//	Button Ãë¼Ò
	g_cUIManager->HT_AddButtonControl( _DIALOG_INDIVIDUALWND1, 6, 159, 157, 326, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 157, 326, 89, 19 );//	Ãë¼Ò
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_INDIVIDUALWND1, 6 );
	//	Label ¸Þ½ÃÁö
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 7, eMsgShopMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 33, 247, 50, 17 );//	¸Þ½ÃÁö
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_INDIVIDUALWND1, 7,  7 );
	//	Edit ÆÇ¸Å ¸Þ½ÃÁö
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_INDIVIDUALWND1, 8, 9, 75, 245, 175, 17 );
	//	¼¼·Î
	for( i=0 ; i<7 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND1, 0, 1, 33+(i*36), 87, 1400, 3, 143 );
	}
	//	°¡·Î
	for( i=0 ; i<5 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND1, 0, 2, 33, 87+(i*36), 1400, 218, 3 );
	}
	//	Slot Inven
	for( i=0 ; i<6 ; i++ )
	{
		for( j=0 ; j<4 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_INDIVIDUALWND1, 10+((j*6)+i), 0, 34+(i*36), 87+(j*36) );
			g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_INDIVIDUALWND1, 10+((j*6)+i), HT_TRUE );
		}
	}

	//	[_DIALOG_INDIVIDUALWND2]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_INDIVIDUALWND2, _T(""), 280, 490, g_cIndividualStore->HT_vEI_InputCheckForIndividualStore2, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_INDIVIDUALWND2, 5 );
	//	ÁÙ	Á¦¸ñ Ç¥½ÃÁÙ
	g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND2, 0, 8, 2, 36, 1400, 276, 6 );
	//	Texture ¸í·É
	g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND2, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 0, eMsgInvenPrivateShop, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );//	°³ÀÎ»óÁ¡
	//	Label ±¸¸ÅÃÑ¾×
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 0, eMsgShopBuyTotalPrice, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 120, 390, 60, 17 );//	±¸¸ÅÃÑ¾×
	//	Label ¼ÒÁö±Ý¾×
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 0, eMsgShopCarryRupia, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 120, 406, 60, 17 );//	¼ÒÁö±Ý¾×
	//	Label ÆÇ¸ÅÀÚ
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 1, eMsgShopTrader, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 33, 56, 200, 15 );//	ÆÇ¸ÅÀÚ
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_INDIVIDUALWND2, 1, 4 );
	//	Label ±¸¸ÅÀÚ
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 2, eMsgShopBuyer, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 33, 220, 200, 15 );//	±¸¸ÅÀÚ
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_INDIVIDUALWND2, 2, 4 );
	//	Label ±¸¸ÅÃÑ¾× ¾×¼ö
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 3, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 184, 390, 75, 17 );
	//	Label ¼ÒÁö±Ý¾× ¾×¼ö
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 4, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 184, 406, 75, 17 );
	//	Button È®ÀÎ
	g_cUIManager->HT_AddButtonControl( _DIALOG_INDIVIDUALWND2, 5, 159, 71, 441, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 71, 441, 89, 19 );//	È®ÀÎ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_INDIVIDUALWND2, 5 );
	//	Button Ãë¼Ò
	g_cUIManager->HT_AddButtonControl( _DIALOG_INDIVIDUALWND2, 6, 159, 172, 441, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 172, 441, 89, 19 );//	Ãë¼Ò
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_INDIVIDUALWND2, 6 );
	//	ÆÇ¸ÅÀÚ
	//	¼¼·Î
	for( i=0 ; i<7 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND2, 0, 1, 32+(i*36), 74, 1400, 3, 141 );
	}
	//	°¡·Î
	for( i=0 ; i<5 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND2, 0, 2, 32, 71+(i*36), 1400, 218, 3 );
	}
	//	Slot Inven
	for( i=0 ; i<6 ; i++ )
	{
		for( j=0 ; j<4 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_INDIVIDUALWND2, 10+((j*6)+i), 0, 34+(i*36), 74+(j*36) );
			g_cUIManager->HT_SetSlotBoxControlPosImage(_DIALOG_INDIVIDUALWND2, 10+((j*6)+i), 2, 1);
			g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_INDIVIDUALWND2, 10+((j*6)+i), HT_TRUE );
		}
	}
	//	±¸¸ÅÀÚ
	//	¼¼·Î
	for( i=0 ; i<7 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND2, 0, 1, 32+(i*36), 242, 1400, 3, 141 );
	}
	//	°¡·Î
	for( i=0 ; i<5 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND2, 0, 2, 32, 242+(i*36), 1400, 218, 3 );
	}
	//	Slot Inven
	for( i=0 ; i<6 ; i++ )
	{
		for( j=0 ; j<4 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_INDIVIDUALWND2, 34+((j*6)+i), 0, 34+(i*36), 245+(j*36) );
			g_cUIManager->HT_SetSlotBoxControlPosImage(_DIALOG_INDIVIDUALWND2, 34+((j*6)+i), 2, 1);
			g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_INDIVIDUALWND2, 34+((j*6)+i), HT_TRUE );
		}
	}

	//	[_DIALOG_BYELISTWND]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_BYELISTWND, _T(""), 400, 300, g_cIndividualStore->HT_vEI_InputCheckForByeListWnd, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_BYELISTWND, 5 );
	//	*****¼±ÅÃÇÏ½Å ¾ÆÀÌÅÛ ±¸¸Å ³»¿ªÀÔ´Ï´Ù.*****
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgShopExplain01, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 20, 360, 25 );//	*****¼±ÅÃÇÏ½Å ¾ÆÀÌÅÛ ±¸¸Å ³»¿ªÀÔ´Ï´Ù.*****
	//	***±¸¸Å³»¿ª¿¡ µ¿ÀÇÇÏ½Ã¸é È®ÀÎ ¹öÆ°À» ´­·¯ ÁÖ¼¼¿ä***
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgShopExplain02, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 235, 360, 25 );//	***±¸¸Å³»¿ª¿¡ µ¿ÀÇÇÏ½Ã¸é È®ÀÎ ¹öÆ°À» ´­·¯ ÁÖ¼¼¿ä***
	//	(Page 0/0)
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 30, _T("(Page1/1)"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 200, 50, 70, 20 );
	//	ÇÕ°è
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgShopSubTotal, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 200+12, 200, 20 );//	ÇÕ°è
	//	ÇÕ°è °Ù¼ö
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 31, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 220, 200+12, 50, 20 );
	//	ÇÕ°è µ·
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 32, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 250, 200+12, 100, 20 );
	//	¾ÆÀÌÅÛ ¸ñ·Ï
	for( i=1 ; i<7 ; i++ )
	{
		g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, (i*3)+1, _T(" "), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 70+((i-1)*23), 200, 25 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, (i*3)+2, _T(" "), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 220, 70+((i-1)*23), 50, 25 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, (i*3)+3, _T(" "), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 250, 70+((i-1)*23), 100, 25 );
	}
	//	Button È®ÀÎ
	g_cUIManager->HT_AddButtonControl( _DIALOG_BYELISTWND, 1, 159, 90, 260, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 90, 260, 89, 19 );//	È®ÀÎ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_BYELISTWND, 1 );
	//	Button Ãë¼Ò
	g_cUIManager->HT_AddButtonControl( _DIALOG_BYELISTWND, 2, 159, 220, 260, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 220, 260, 89, 19 );//	Ãë¼Ò
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_BYELISTWND, 2 );
	//	ÁÂ ¹öÆ°
	g_cUIManager->HT_AddButtonControl( _DIALOG_BYELISTWND, 3, 159, 270, 50, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgShopLeft, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 270, 50, 50, 19 );//	ÁÂ
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_BYELISTWND, 3 );
	//	¿ì ¹öÆ°
	g_cUIManager->HT_AddButtonControl( _DIALOG_BYELISTWND, 4, 159, 325, 50, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgShopRight, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 325, 50, 50, 19 );//	¿ì
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_BYELISTWND, 4 );


	// _DIALOG_MY_USEINFO_V3
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_MY_USEINFO_V3, _T("MyCash"), 459, 283, g_cIndividualStore->HT_vEI_InputCheckForMyUseInfo, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_MY_USEINFO_V3, 5 );

	// 1,37,456,37
	g_cUIManager->HT_AddTextureControl(_DIALOG_MY_USEINFO_V3, 0, 8, 3, 37, 1400, 452, 6);
	g_cUIManager->HT_AddTextureControl(_DIALOG_MY_USEINFO_V3, 0, 9, 39, 31);
	g_cUIManager->HT_AddLabelControl(_DIALOG_MY_USEINFO_V3, 99, eMsgShopExplain03, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 39, 31, 152, 19);//	ÇÁ¸®¹Ì¾ö ¼­ºñ½º ÀÌ¿ë³»¿ª
	
	// ¶óº§ & ¹öÆ°
	int y= 63;
	for (int i=0; i<7; ++i)
	{
		g_cUIManager->HT_AddLabelControl( _DIALOG_MY_USEINFO_V3, (i*5), "", 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 12, y+(20*i), 130, 19);
		g_cUIManager->HT_AddLabelControl( _DIALOG_MY_USEINFO_V3, (i*5)+1, "", 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 139, y+(20*i), 60, 19);
		g_cUIManager->HT_AddLabelControl( _DIALOG_MY_USEINFO_V3, (i*5)+2, "", 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 200, y+(20*i), 144, 19);
		g_cUIManager->HT_AddLabelControl( _DIALOG_MY_USEINFO_V3, (i*5)+3, "", 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 345, y+(20*i), 40, 19);
		g_cUIManager->HT_AddLabelControl( _DIALOG_MY_USEINFO_V3, (i*5)+4, "", 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 383, y+(20*i), 50, 19);
	}

	y = 83;
	for (int i=0; i<6; ++i)
		g_cUIManager->HT_AddButtonControl( _DIALOG_MY_USEINFO_V3, i+1, 63, 384, y+(20*i), 65, 64, 1500, 50, 17);

	g_cUIManager->HT_AddLabelControl( _DIALOG_MY_USEINFO_V3, 36, eMsgShopExplain04, 0, HT_COLOR(1,0.5,0.25,1), HT_COLOR(1,1,1,1), 18, 230, 436, 19);//	ÇÁ¸®¹Ì¾ö ¼­ºñ½ºÀÇ Ãß°¡ ½ÅÃ»½Ã Àû¿ë±â°£ÀÌ ´Ã¾î³³´Ï´Ù.
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_MY_USEINFO_V3, 36, 7);
	g_cUIManager->HT_AddLabelControl( _DIALOG_MY_USEINFO_V3, 37, eMsgShopExplain05, 0, HT_COLOR(1,0.5,0.25,1), HT_COLOR(1,1,1,1), 18, 250, 436, 19);//	È¿°ú°¡ OFFÀÎ »óÅÂÀÎ °æ¿ì¶óµµ ¸¸·á±â°£ÀÌ ¿¬ÀåµÇÁö´Â ¾Ê½À´Ï´Ù.
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_MY_USEINFO_V3, 37, 7);
}

//	IndividualStore1
void CHTIndividualStore::HT_vEI_InputCheckForIndividualStore1(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	Close Button
		if( iTargetID == -1 || iTargetID == 6 )
		{
			// ÆÇ¸Å½ÃÀÛ ¿äÃ»Çß°Å³ª ÆÇ¸ÅÁßÀÌ¾ú´Ù¸é ÆÇ¸Å Á¾·á¸¦ ¼­¹ö¿¡ º¸³½´Ù
			if( g_cIndividualStore->m_byStoreProcess == STORE_PROCESS_STORE || g_cIndividualStore->m_byStoreProcess == STORE_PROCESS_REQ_START ) 
			{
				g_cIndividualStore->m_byStoreProcess = STORE_PROCESS_REQ_END;
				g_cIndividualStore->HT_vNetWork_CSP_Req_Store();
			}
			// »óÁ¡¸ðµå ÇØÁ¦
			g_cIndividualStore->HT_vIndividualStore_StoreModeEnd();
			// ÆÇ¸ÅÃ¢ ´Ý±â
			g_cIndividualStore->HT_vIndividualStore_Close();
		}
		//	È®ÀÎ
		else if( iTargetID == 5 )
		{
			// ÆÇ¸Å¸¦ À§ÇØ ¼±ÅÃÇÑ ¾ÆÀÌÅÛÀÌ ÀÖÀ» °æ¿ì
			if( g_cIndividualStore->m_byStoreProcess == STORE_PROCESS_NONE && g_cIndividualStore->m_byStoreItemNum > 0 )
			{
				g_cIndividualStore->m_byStoreProcess = STORE_PROCESS_REQ_START;
				// È®ÀÎ¹öÆ° ´©¸¥ »óÅÂ - ´Ù½Ã ´©¸¦ ¼ö ¾ø°Ô ÇÔ
				// Á¦ÇÑÀ» ³Ñ¾î°£ ¸Þ½ÃÁö´Â Àß¶ó³¿ (¹ö±× ¼öÁ¤ 2004. 10. 18 ¼±¿µ¹ü)
				g_cIndividualStore->m_szBuyMessage = g_cUIManager->HT_GetTextEditBoxControl( _DIALOG_INDIVIDUALWND1, 8 );
				char itemp[500];
				CHTString::HT_hrStringCopy( itemp, g_cIndividualStore->m_szBuyMessage.HT_szGetString(), STORE_MESSAGE_MAX_SIZE-1 );
				itemp[ STORE_MESSAGE_MAX_SIZE-1 ] = '\0';
				g_cIndividualStore->m_szBuyMessage.HT_szFormat("%s",itemp);
				g_cIndividualStore->HT_vNetWork_CSP_Req_Store();
			}
			else if( g_cIndividualStore->m_byStoreProcess == STORE_PROCESS_REQ_START || g_cIndividualStore->m_byStoreProcess == STORE_PROCESS_STORE )
				return;
			else
				g_cIndividualStore->HT_vIndividualStore_Close();
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		g_cUIManager->HT_RefuseSlotImageMoving();
		//	¾ÆÀÌÄÜ ¾ø¾Ö±â
		if( _STORE_SELL_BEGIN <= iTargetID && iTargetID <= _STORE_PREMIUM_SELL_END)
		{
			HTint iPos = ( iTargetID - _STORE_SELL_BEGIN )/* % _STORE_WIDTH*/;
			g_cIndividualStore->HT_vIndividualStore_DeleteSellItem( iPos );
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		// ÆÇ¸Å°³¼ö ÀÔ·Â Ã¢
		if( g_cIndividualStore->m_iStore_MsgBoxType == STORE_MSGTYPE_ITEMINPUT )
		{
			//	X¹öÆ°ÀÏ¶§ Ã¢ Áö¿ì±â
           	if( iTargetID == 0 )
			{
				g_cIndividualStore->m_iPrice = 0;
			}
			// È®ÀÎ ¹öÆ°
			else
			{
				g_cIndividualStore->m_iPackCount = iTargetID;
				// °³¼ö ¿À·ù
				if( g_cIndividualStore->m_iPackCount <= 0 || 
					g_cIndividualStore->m_iPackCount > g_cItemSystem->HT_iItemSystem_GetItemCount( g_cIndividualStore->m_dwSelectKeyID ) ) 
				{
					CHTString szMessage;
					if( g_pMessageMgr->HT_bGetMessage( eMsgItemUnpackCountErr, &szMessage ) == true )
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, szMessage );
				}
				else
				{
					// ÆÇ¸Å °¡°Ý ÀÔ·ÂÃ¢ ¶ç¿ì±â
					g_cIndividualStore->HT_vIndividualStore_PriceWin_Active();
				}
			}
		}
		// ÆÇ¸Å °¡°Ý ÀÔ·ÂÃ¢
		else if( g_cIndividualStore->m_iStore_MsgBoxType == STORE_MSGTYPE_RUPIAINPUT )
		{
			//	X¹öÆ°ÀÏ¶§ Ã¢ Áö¿ì±â
           	if( iTargetID == 0 )
			{
				g_cIndividualStore->m_iPrice = 0;
			}
			// È®ÀÎ ¹öÆ°
			else
			{
				g_cIndividualStore->m_iPrice = iTargetID;
				// °³¼ö ¿À·ù
				if( g_cIndividualStore->m_iPackCount <= 0 || 
					g_cIndividualStore->m_iPackCount > g_cItemSystem->HT_iItemSystem_GetItemCount( g_cIndividualStore->m_dwSelectKeyID ) ) 
				{
					CHTString szMessage;
					if( g_pMessageMgr->HT_bGetMessage( eMsgItemUnpackCountErr, &szMessage ) == true )
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, szMessage );
				}
				else
				{
					// ¾ÆÀÌÅÛ ¶Ù¿ì±â
					g_cIndividualStore->HT_vIndividualStore_AddSellItem( );
				}
			}
		}
	}
}
//	IndividualStore2
void CHTIndividualStore::HT_vEI_InputCheckForIndividualStore2(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	Close Button
		if( iTargetID == -1 || iTargetID == 6 )
		{
			// ±¸¸ÅÃ¢ ´Ý±â
			g_cIndividualStore->HT_vIndividualStore_Close();
			g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		}
		else if( iTargetID == 5 )
		{
			// ±¸¸ÅÇÒ ¾ÆÀÌÅÛÀÌ ÀÖÀ» °æ¿ì
			if( g_cIndividualStore->m_byStoreProcess == STORE_PROCESS_BUY && g_cIndividualStore->m_byBuyItemNum > 0 )
			{
				g_cIndividualStore->m_byStoreProcess = STORE_PROCESS_REQ_BUY;
				// È®ÀÎ¹öÆ° ´©¸¥ »óÅÂ - ´Ù½Ã ´©¸¦ ¼ö ¾ø°Ô ÇÔ
				// ÇÑ±¹¾î ¹öÁ¯¿¡¼­¸¸ ±¸¸Å ¸®½ºÆ® ¶ç¿ò
				if (g_iInationalType == 0 ) 
				{
					// ±¸¸Å È®ÀÎ ¸®½ºÆ® ¶ç¿ò
					g_cUIManager->HT_ShowWindow( _DIALOG_BYELISTWND );
					g_cIndividualStore->m_iMaxPage = g_cIndividualStore->m_iNowPage = 1;
					g_cIndividualStore->HT_vIndividualStore_ButtonCheckForBuyListOutPut(g_cIndividualStore->m_iNowPage);
				}
				// ±×·¸Áö ¾ÊÀ¸¸é ¹Ù·Î ±¸¸Å¿äÃ»
				else
					g_cIndividualStore->HT_vNetWork_CSP_Req_Store_Buy();
			}
			else if( g_cIndividualStore->m_byStoreProcess == STORE_PROCESS_REQ_BUY )
				return;
			else
				g_cIndividualStore->HT_vIndividualStore_Close();
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		g_cUIManager->HT_RefuseSlotImageMoving();
		if( _STORE_BUY_BEGIN <= iTargetID && iTargetID <= _STORE_BUY_MY_END )
		{
			HTint iPos = iTargetID - _STORE_BUY_BEGIN ;
			// ±¸ÀÔÇÏ·Á´Â ¸ñ·Ï
			if( iPos >= MAX_MOBSTORE )
				g_cIndividualStore->HT_vIndividualStore_DeleteBuyItem( iPos-MAX_MOBSTORE );
			// »óÁ¡ ¸ñ·Ï
			else
				g_cIndividualStore->HT_vIndividualStore_AddBuyItem( iPos );
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		g_cUIManager->HT_RefuseSlotImageMoving();
	}
}

//	Bye List Wnd
void CHTIndividualStore::HT_vEI_InputCheckForByeListWnd(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		//	Close Button
		if( iTargetID == -1 || iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
			// ±¸¸ÅÃ¢ ´Ý±â
			g_cIndividualStore->HT_vIndividualStore_Close();
		}
		//	È®ÀÎÃ¢
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
			g_cIndividualStore->HT_vNetWork_CSP_Req_Store_Buy();
		}
		//	ÁÂ
		else if(iTargetID == 3)
		{
			if( g_cIndividualStore->m_iNowPage <= 1 ) g_cIndividualStore->m_iNowPage = g_cIndividualStore->m_iMaxPage+1;
			g_cIndividualStore->HT_vIndividualStore_ButtonCheckForBuyListOutPut(--g_cIndividualStore->m_iNowPage);
		}
		//	¿ì
		else if(iTargetID == 4)
		{
			if(g_cIndividualStore->m_iNowPage >= g_cIndividualStore->m_iMaxPage) g_cIndividualStore->m_iNowPage = 0;
			g_cIndividualStore->HT_vIndividualStore_ButtonCheckForBuyListOutPut(++g_cIndividualStore->m_iNowPage);
		}
	}
}

//	Bye List Wnd
void CHTIndividualStore::HT_vEI_InputCheckForMyUseInfo(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if (iTargetID == -1) 
		{
			g_cUIManager->HT_HideWindow(_DIALOG_MY_USEINFO_V3);
			return;
		}

		g_cIndividualStore->m_iTabNo = iTargetID;	// ¹öÆ°³Ñ¹ö ¾ò±â
		HTPoint pPt; pPt.x = 0; pPt.y = 0;
		g_cIndividualStore->HT_hrCheckBox( pPt );
	}
}

//-----------------------------------------------------------------
// 3ºÐ¿¡ ÇÑ¹ø¾¿ Ã¤ÆÃ ¸Þ½ÃÁö ³¯¸®±â À§ÇØ
//-----------------------------------------------------------------
HTvoid
CHTIndividualStore::HT_vIndividualStore_Control_Chatting()
{
	if( m_byStoreProcess == STORE_PROCESS_STORE )
	{
		DWORD dwPassTime = GetTickCount();
        if( dwPassTime > m_dwAutoChatMsgStartTime + 180000 )
		{
			CHTString strTemp, szMessage, szPos;
			// [ÆÇ¸Å]%s[%d,%d]
			if( g_pMessageMgr->HT_bGetMessage( eMsgShopNamePublicity, &szMessage ) == true )
			{
				HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition(); // Ä³¸¯ÅÍ À§Ä¡
				szPos.HT_szFormat("%d,%d", pPt.x, pPt.y );
				
				strTemp.HT_szFormat( szMessage.HT_szGetString(), m_szBuyMessage.HT_szGetString(), szPos.HT_szGetString() );
				//	3ºÐ¿¡ ÇÑ¹ø¾¿ Ã¤ÆÃ ¸Þ½ÃÁö ³¯¸®±â À§ÇØ
				m_dwAutoChatMsgStartTime = GetTickCount();
				g_cChatting->HT_vSetData_Normal( strTemp );
			}
		}
	}
}
// ÆÇ¸ÅÃ¢/±¸ÀÔÃ¢ ¶ç¿ì±â
HTvoid
CHTIndividualStore::HT_vIndividualStore_Active( HTint iStoreID )
{

	// ÇØ´ç Áö¿ªÀÇ ÀÏºÎ ¿µ¿ª¿¡¼­´Â °³ÀÎ»óÁ¡À» ¿ÀÇÂÇÒ ¼ö ¾ø´Ù. // 578 400 ~ 630 444 
	HTPoint pMainCharPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	if (g_wResentZoneServerID == 17 &&							// ºñ·ù¼º
		pMainCharPt.x > 578 && pMainCharPt.x < 630 &&			// À§Å¹»óÁ¡ À§Ä¡
		pMainCharPt.y > 400 && pMainCharPt.y < 444)
	{
		//HT_g_Script_SetMessage( eMsgExplanPremiumItem01, &strTemp, _T("") );		//	"ÇØ´ç À§Ä¡¿¡¼­´Â °³ÀÎ»óÁ¡À» ¿ÀÇÂÇÒ ¼ö ¾ø½À´Ï´Ù.
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "ÇØ´ç À§Ä¡¿¡¼­´Â °³ÀÎ»óÁ¡À» ¿ÀÇÂÇÒ ¼ö ¾ø½À´Ï´Ù.");
		return;
	}


	// NPC¿Í ÀÛ¾÷ÇÏ°í ÀÖ´Â °æ¿ì|Á¦·Ã ÇÏ´ø ÁßÀÏ °æ¿ì | Æ®·¹ÀÌµåÃ¢ÀÌ ¶°ÀÖÀ» °æ¿ì Ã³¸® ¾ÈÇÔ
	if( g_cNPCControl->HT_iNPCControl_ActiveNPCIndex() != 0 || 
		g_cUIManager->HT_isShowWindow( _DIALOG_REFINE ) || 
		g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) || 
		g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) ||
		g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) ) 
		return;

	// ³ªÀÇ »óÅÂ°¡ ½ºÅÏÀÌ³ª ½½¸³ÀÏ °æ¿ì Ã³¸® ¾ÈÇÔ
	if( g_cMainCharacter->HT_iMAinChar_GetAffections() & eTNVSAfn_Stun || 
		g_cMainCharacter->HT_iMAinChar_GetAffections() & eTNVSAfn_Sleep )
		return;

	// ÁÖ½ÅÀü Áö¿ªÀÏ °æ¿ì Ã³¸® ¾ÈÇÔ
	if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		return;

	HTint iDlgNo;
	CHTString str;
	HTint iPCMoney;
	// ¼ÒÁö ±Ý¾×
	iPCMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
	str = g_cUIManager->HT_strSetRestMark( iPCMoney );

	//	KeyID ºñ±³ÇÏ¿©
	// ±¸ÀÔÃ¢ ¶ç¿ì±â
	if( iStoreID != g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		m_iStoreID = iStoreID;
		iDlgNo = _DIALOG_INDIVIDUALWND2;

		// ¼ÒÁö ±Ý¾×				
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 4, str.HT_szGetString() );
		// ±¸¸Å ÃÑ¾× ÃÊ±âÈ­
		m_iTotalPrice = 0;
		str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice);
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 3, str.HT_szGetString() );
		// ÆÇ¸ÅÀÚ ÀÌ¸§ ¾²±â
		str = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( iStoreID );
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 1, str.HT_szGetString() );
		// ±¸¸ÅÀÚ ÀÌ¸§ ¾²±â
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 2, g_oMainCharacterInfo.szCharName );
		//	º¸¹°»óÀÚ ¾Ö´Ï¸ÅÀÌ¼ÇÀ» À§ÇÏ¿© ^^;;
		if( g_cSystem->HT_bSystem_GetShopModelMode() )
            g_cOtherObjectSystem->HT_vOtherObjectSystem_SetChangeAnimation( iStoreID, CHARACTER_ANISTATE_WLK, 1 );

			//	Ã¢ ÄÔ
		g_cUIManager->HT_ShowWindow( iDlgNo );
		g_cUIManager->HT_FocusOnEditBoxControl( iDlgNo, 8 );

	}
	// ÆÇ¸ÅÃ¢ ¶ç¿ì±â
	else
	{
		m_iStoreID = 0;
		iDlgNo = _DIALOG_INDIVIDUALWND1;
		// ¾ÆÀÌÅÛ µî·Ï ÃÖ´ë °³¼ö È®ÀÎ

		time_t timeTime;
		if( g_cMainCharacter->HT_bMainChar_GetTimeStamp( eTime_Store, timeTime ) == HT_FALSE )
			return;
		// È®Àå ¼­ºñ½º¸¦ ½ÅÃ»ÇØº» ÀûÀÌ ¾øÀ½
		if( timeTime <= 0 || g_cIndividualStore->m_iCheckUse[1] == HT_FALSE)
			HT_vRenewalPossibleBar( HT_FALSE );
		else
		{
			// ÇöÀç ½Ã°£ º¯È¯
			time_t now; time( &now );

			// ÇöÀç ½Ã°£°ú È®Àå ¼­ºñ½º ±âÇÑ ºñ±³
			if( now <= timeTime )
			{
				HT_vRenewalPossibleBar( HT_TRUE ); // È®Àå°ø°£ »ç¿ë °¡´É

				// È®Àå±âÇÑ Ç¥½ÃÇÏ±â
				CHTString szTime;
				g_cMainCharacter->HT_vMainChar_GetTimeStamp( 255, szTime );
				g_cUIManager->HT_SetTextLabelControl( iDlgNo, 1, szTime.HT_szGetString() );
			}
			else
				HT_vRenewalPossibleBar( HT_FALSE ); // È®Àå°ø°£ »ç¿ë ºÒ°¡´É
		}
		// ¼ÒÁö ±Ý¾×
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 3, str.HT_szGetString() );
		// ÆÇ¸Å ÃÑ¾× ÃÊ±âÈ­
		str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice);
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 2, str.HT_szGetString() );
		//	Init Edit Box
		g_cUIManager->HT_SetTextEditBoxControl( iDlgNo, 8, _T("") );

		//	Ã¢ ÄÔ
		g_cUIManager->HT_ShowWindow( iDlgNo );
		g_cUIManager->HT_FocusOnEditBoxControl( iDlgNo, 8 );

		//	IME String Init
		g_cImeMgr.vImeMgr_SetLanguage( HT_TRUE, 0 );
		g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
		g_cImeMgr.InputString();
	}

	//	ÀÎº¥Åä¸® ÄÔ
	if( !g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) )
		g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
}

// »ç¿ë ºÒ°¡´ÉÇÑ Ç¥½Ã ´Ù½Ã ±×¸®±â
HTvoid
CHTIndividualStore::HT_vRenewalPossibleBar( HTbool bUsable )
{
	if( bUsable == HT_TRUE ) // È®ÀåµÈ °ø°£ »ç¿ë °¡´É
	{
		// µî·ÏÇÒ ¼ö ÀÖ´Â ¾ÆÀÌÅÛ ÃÖ´ë°³¼ö ¼³Á¤
		m_byMaxStoreItemCount = MAX_MOBSTORE;
		// ÀÌÀü »ç¿ë ºÒ°¡´É Ç¥½Ã Áö¿ì±â
		HT_vDelPossibleBar();
	}
	else // È®ÀåµÈ °ø°£ »ç¿ë ºÒ°¡´É
	{
		// µî·ÏÇÒ ¼ö ÀÖ´Â ¾ÆÀÌÅÛ ÃÖ´ë°³¼ö ¼³Á¤
		m_byMaxStoreItemCount = HT_STORE_SELL_ITEM_COUNT_BASIC;
		// »ç¿ë ºÒ°¡´ÉÇÑ ºÎºÐÀÇ Bitmap»öÀ» ¹Ù²Û´Ù
		for( HTint x = _STORE_PREMIUM_SELL_BEGIN ; x <= _STORE_PREMIUM_SELL_END ; ++x )
		{
			g_cUIManager->HT_SetSlotBoxControlEnable( _DIALOG_INDIVIDUALWND1, x, HT_FALSE );
		}
	}
}

// »ç¿ë ºÒ°¡´ÉÇÑ Ç¥½Ã »èÁ¦
HTvoid
CHTIndividualStore::HT_vDelPossibleBar( )
{
	HTint iColNo = 0;
	HTint iSizeX = _INVEN_WIDTH;

	// »ç¿ë ºÒ°¡´ÉÇÑ ÀÎº¥Åä¸® ºÎºÐÀÇ Bitmap »öÀ» ¿ø·¡ »öÀ¸·Î ¹Ù²Û´Ù
	for( HTint x = _STORE_PREMIUM_SELL_BEGIN ; x <= _STORE_PREMIUM_SELL_END ; ++x )
	{
		g_cUIManager->HT_SetSlotBoxControlEnable( _DIALOG_INDIVIDUALWND1, x, HT_TRUE );
	}
}

// »óÁ¡ ¿­±â
HTvoid
CHTIndividualStore::HT_vIndividualStore_StoreModeStart() //fors_debug ¿ªÉÌµê±ä³ÉÉÌµêÐÎ×´,¿É·ñ×öÎª±äÉí?
{
	if( m_byStoreProcess == STORE_PROCESS_REQ_START )
	{
		m_byStoreProcess = STORE_PROCESS_STORE;
		if( !g_cSystem->HT_bSystem_GetShopModelMode() )
		{
			if( g_cMainCharacter->HT_bMainChar_GetSitDownState() != HT_TRUE )
				g_cMainCharacter->HT_vMainChar_SetSit();
		}
		else
		{
			// Ä³¸¯ÅÍ ¸Ö¸® º¸³»¹ö¸®°í »óÁ¡ Ä³¸¯ÅÍ À§Ä¡ ½ÃÅ°±â
			HTvector3 vecTempPos = g_cMainCharacter->HT_vecGetPosition();
			g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ModelID, HTvector3( vecTempPos.x,vecTempPos.y-200.0f,vecTempPos.z ) );
			g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ShopCharID, vecTempPos );
		}
	}
}

// »óÁ¡ ´Ý±â
HTvoid
CHTIndividualStore::HT_vIndividualStore_StoreModeEnd()
{
	// »óÁ¡ ´Ý±â ¿äÃ» °á°ú¸¦ ¹Þ¾Ò°Å³ª ¹°°ÇÀÌ ¸ðµÎ ÆÈ·ÈÀ» °æ¿ì
	if( m_byStoreProcess == STORE_PROCESS_REQ_END || m_byStoreItemNum == 0 )
	{
		// »óÁ¡¸ðµå ÇØÁ¦
		if( !g_cSystem->HT_bSystem_GetShopModelMode() )
		{
			if( g_cMainCharacter->HT_bMainChar_GetSitDownState() == HT_TRUE )
				g_cMainCharacter->HT_vMainChar_SetSit(); // ¼­±â
		}
		else
		{
			// Ä³¸¯ÅÍ ¸Ö¸® º¸³»¹ö¸®°í »óÁ¡ Ä³¸¯ÅÍ À§Ä¡ ½ÃÅ°±â
			HTvector3 vecTempPos = g_cMainCharacter->HT_vecGetPosition();
			g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ShopCharID, HTvector3( 10,10,10 ) );
			g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ModelID, vecTempPos );
		}
	}
}

HTRESULT
CHTIndividualStore::HT_hrCheckBox( HTPoint pPt )
{
	HTint iButtonNo = m_iTabNo-1;

	if (!m_iCheckEnable[iButtonNo] == HT_TRUE)
		return HT_OK;

	CHTString strTemp;

	//	Button
	{
		if (m_iCheckUse[iButtonNo] == HT_TRUE )
		{
			switch(iButtonNo)
			{
			case 0: // ÀÎº¥Åä¸® ÃÊ±â ¼³Á¤
				if( !g_cUIManager->HT_isShowWindow(_DIALOG_EQUPINVENTORY) )
				{
					g_cEquipInventory->HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH, HT_FALSE ); // Bag2 »ç¿ë ºÒ°¡´É;
					HT_g_Script_SetMessage( eMsgInventoryExpansionDisabled, &strTemp, _T("") );	//	ÀÎº¥Åä¸® È®Àå ±â´ÉÀÌ ÇØÁ¦ µÇ¾ú½À´Ï´Ù.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				}
				else
				{
					HT_g_Script_SetMessage( eMsgCloseInvendowWindowTry, &strTemp, _T("") );	//	ÀÎº¥Åä¸® Ã¢À» ´ÝÀºÈÄ ´Ù½Ã ½ÃµµÇØ ÁÖ½Ê½Ã¿À
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
					return HT_OK;
				}
				break;
			case 1:	// °³ÀÎ»óÁ¡È®Àå
				if( !g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) )
				{
					HT_g_Script_SetMessage( eMsgPrivateStoreExpansionDisabled, &strTemp, _T("") );	//	°³ÀÎ»óÁ¡ È®Àå ±â´ÉÀÌ ÇØÁ¦ µÇ¾ú½À´Ï´Ù.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				}
				else
				{
					HT_g_Script_SetMessage( eMsgClosePrivateStoreTry, &strTemp, _T("") );	//	°³ÀÎ»óÁ¡ Ã¢À» ´ÝÀºÈÄ ´Ù½Ã ½ÃµµÇÏ¿© ÁÖ½Ê½Ã¿À.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
					return HT_OK;
				}
				break;
			case 2:	// ·çÇÇ¾Æ ÀÚµ¿ ½Àµæ
				HT_g_Script_SetMessage( eMsgAutomaticRupiaDisabled, &strTemp, _T("") );		//	"·çÇÇ¾Æ ÀÚµ¿ ½Àµæ ±â´ÉÀÌ ÇØÁ¦ µÇ¾ú½À´Ï´Ù."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 3:	// ÇÑ´Þ ¾Æ´©¹Ù¹Ù
				HT_g_Script_SetMessage( eMsgAnubabaEffectDisabled, &strTemp, _T("") );		//	"¾Æ´©¹Ù¹Ù È¿°ú°¡ ÇØÁ¦ µÇ¾ú½À´Ï´Ù."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 4:	// ÇÑ´Þ ¾ÆÆ®¸¸
				HT_g_Script_SetMessage( eMsgAtmanEffectDisabled, &strTemp, _T("") );		//	"¾ÆÆ®¸¸ È¿°ú°¡ ÇØÁ¦ µÇ¾ú½À´Ï´Ù."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 5:	// ÇÑ´Þ ¸ðµç Â÷Å©¶ó »ó½Â
				HT_g_Script_SetMessage( eMsgAllChakraUpgradeDisabled, &strTemp, _T("") );		//	"¸ðµç Â÷Å©¶ó »ó½ÂÈ¿°ú°¡ ÇØÁ¦ µÇ¾ú½À´Ï´Ù."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			}

			m_iCheckUse[iButtonNo] = 0;
		}
		else
		{
			switch(iButtonNo)
			{
			case 0: // ÀÎº¥Åä¸® ÃÊ±â ¼³Á¤
				if( !g_cUIManager->HT_isShowWindow(_DIALOG_EQUPINVENTORY) )
				{
					g_cEquipInventory->HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH); // Bag2 »ç¿ë°¡´É
					HT_g_Script_SetMessage( eMsgInventoryExpansionEnabled, &strTemp, _T("") );		//	"ÀÎº¥Åä¸® È®Àå ±â´ÉÀÌ Àû¿ë µÇ¾ú½À´Ï´Ù."
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				}
				else
				{
					HT_g_Script_SetMessage( eMsgCloseInvendowWindowTry, &strTemp, _T("") );		//	"ÀÎº¥Åä¸® Ã¢À» ´ÝÀºÈÄ ´Ù½Ã ½ÃµµÇØ ÁÖ½Ê½Ã¿À."
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
					return HT_OK;
				}
				break;
			case 1:	// °³ÀÎ»óÁ¡È®Àå
				if( !g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) )
				{
					HT_g_Script_SetMessage( eMsgPrivateStoreExpansionEnabled, &strTemp, _T("") );		//	"°³ÀÎ»óÁ¡ È®Àå ±â´ÉÀÌ Àû¿ë µÇ¾ú½À´Ï´Ù."
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				}
				else
				{
					HT_g_Script_SetMessage( eMsgClosePrivateStoreTry, &strTemp, _T("") );		//	"°³ÀÎ»óÁ¡ Ã¢À» ´ÝÀºÈÄ ´Ù½Ã ½ÃµµÇÏ¿© ÁÖ½Ê½Ã¿À."
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
					return HT_OK;
				}
				break;
			case 2:	// ·çÇÇ¾Æ ÀÚµ¿ ½Àµæ
				HT_g_Script_SetMessage( eMsgAutomaticRupiaEnabled, &strTemp, _T("") );		//	"·çÇÇ¾Æ ÀÚµ¿ ½Àµæ ±â´ÉÀÌ Àû¿ë µÇ¾ú½À´Ï´Ù."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 3:	// ÇÑ´Þ ¾Æ´©¹Ù¹Ù
				HT_g_Script_SetMessage( eMsgAnubabaEffectEnabled, &strTemp, _T("") );		//	"¾Æ´©¹Ù¹Ù È¿°ú°¡ Àû¿ë µÇ¾ú½À´Ï´Ù."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 4:	// ÇÑ´Þ ¾ÆÆ®¸¸
				HT_g_Script_SetMessage( eMsgAtmanEffectEnabled, &strTemp, _T("") );		//	"¾ÆÆ®¸¸ È¿°ú°¡ Àû¿ë µÇ¾ú½À´Ï´Ù."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 5:	// ÇÑ´Þ ¸ðµç Â÷Å©¶ó »ó½Â
				HT_g_Script_SetMessage( eMsgAllChakraUpgradeEnabled, &strTemp, _T("") );		//	"¸ðµç Â÷Å©¶ó »ó½ÂÈ¿°ú°¡ Àû¿ë µÇ¾ú½À´Ï´Ù."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			}
			
			m_iCheckUse[iButtonNo] = 1;
		}
		HT_vIndividualStore_ButtonCheckForUseListOutPut();
		
		//¼­¹ö·Î ÆÐÅ¶À» º¸³½´Ù.
		g_cIndividualStore->HT_vNetWork_CSP_Req_TimeMode( g_cIndividualStore->PrimiumService_UseList() );
	}
	return HT_OK;
}

// »ç¿ë³»¿ªÀÇ ½ºÀ§Ä¡ °ªÀ» ¹ÝÈ¯ÇÑ´Ù.
HTushort
CHTIndividualStore::PrimiumService_UseList()
{
	// ÆÐÅ¶°ª »ý¼º
	HTushort sMode = 0;
	if (m_iCheckUse[0]) sMode += 0x8000;
	if (m_iCheckUse[1]) sMode += 0x4000;
	if (m_iCheckUse[2]) sMode += 0x2000;
	if (m_iCheckUse[3]) sMode += 0x1000;
	if (m_iCheckUse[4]) sMode += 0x0800;
	if (m_iCheckUse[5]) sMode += 0x0400;

	// 1ÀÌ ÄÑ´Â°Å±¸, 0ÀÌ ²ô´Â°Å¶õ´Ù. ±×·¯´Ï XOR ¿¬»êÀ» ÇØ¹ö¸°´Ù.
	sMode = sMode ^ 0xFC00;

	return sMode;
}

// »ç¿ë ³»¿ª ¸®½ºÆ® Ã¢ Output
HTvoid
CHTIndividualStore::HT_vIndividualStore_ButtonCheckForUseListOutPut()
{
	CHTString strTemp;
	const int WIDTH_NUM = 5;

	HT_g_Script_SetMessage( eMsgPremiumServiceName, &strTemp, _T("") );		//	"ÇÁ¸®¹Ì¾ö ¼­ºñ½º¸í"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, 0, strTemp);
	HT_g_Script_SetMessage( eMsgWordInUse, &strTemp, _T("") );		//	"»ç¿ë¿©ºÎ"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, 1, strTemp);
	HT_g_Script_SetMessage( eMsgWordExpireDate, &strTemp, _T("") );		//	"¸¸·á±â°£"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, 2, strTemp);
	HT_g_Script_SetMessage( eMsgWordDDay, &strTemp, _T("") );		//	"D-day"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, 3, strTemp);
	HT_g_Script_SetMessage( eMsgWordEffect, &strTemp, _T("") );		//	"È¿°ú"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, 4, strTemp);

	HT_g_Script_SetMessage( eMsgWordInvenExpansion, &strTemp, _T("") );		//	"ÀÎº¥Åä¸® È®Àå"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*1, strTemp);
	HT_g_Script_SetMessage( eMsgWordPrivateStoreExpansion, &strTemp, _T("") );		//	"°³ÀÎ»óÁ¡ È®Àå"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*2, strTemp);
	HT_g_Script_SetMessage( eMsgAutomaticRupiaAcquisition, &strTemp, _T("") );		//	"·çÇÇ¾Æ ÀÚµ¿½Àµæ"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*3, strTemp);
	HT_g_Script_SetMessage( eMsgWordAnubabaCharm, &strTemp, _T("") );		//	"¾Æ´©¹Ù¹Ù ºÎÀû"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*4, strTemp);
	HT_g_Script_SetMessage( eMsgWordAtmanCharm, &strTemp, _T("") );		//	"¾ÆÆ®¸¸ ºÎÀû"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*5, strTemp);
	HT_g_Script_SetMessage( eMsgAllChakraPlus15, &strTemp, _T("") );		//	"¸ðµç Â÷Å©¶ó 15 Áõ°¡"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*6, strTemp);
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*7, "");
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*8, "");

	for (HTint iIndex=0; iIndex<6; ++iIndex)
		HT_vIndividualStore_GetUseListOutPut(iIndex+1);

	return;
}

// È®Àå±âÇÑ Ç¥½ÃÇÏ±â
HTvoid
CHTIndividualStore::HT_vIndividualStore_GetUseListOutPut(HTint index)
{
	CHTString strTemp;
	const int WIDTH_NUM = 5;
	time_t now, timeTime; time( &now );
	HT_COLOR clr;

	m_iCheckEnable[index-1] = 0;

	CHTString szTime, szDay; 
	if( g_cMainCharacter->HT_bMainChar_GetTimeStamp( index-1, timeTime ) == HT_TRUE )
	{
		if( timeTime <= 0 ) // »ç¿ë¾ÈÇÔ
		{
			clr.a = 1.0f; clr.r = 0.8f; clr.g = 0.8f; clr.b = 0.8f;
			HT_g_Script_SetMessage( eMsgNotPurchased, &strTemp, _T("") );		//	"¹Ì±¸ÀÔ"
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+1, strTemp);
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+1, clr);
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+2, "");
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+3, "");
		}
		else if( now <= timeTime ) // »ç¿ëÁß
		{
			timeTime -= now;
			if (timeTime <= 86400) timeTime = 0;
			else
				timeTime /= 86400;
			szDay.HT_szFormat("%d", timeTime);

			g_cMainCharacter->HT_vMainChar_GetTimeStamp( index-1, szTime );

			clr.a = 1.0f; clr.r = 1.0f; clr.g = 0.5f; clr.b = 0.25f;
			HT_g_Script_SetMessage( eMsgWordInUseing, &strTemp, _T("") );		//	"»ç¿ëÁß"
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+1, strTemp);
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+1, clr);
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+2, szTime);
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+2, clr);
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+3, szDay);
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+3, clr);
			m_iCheckEnable[index-1] = 1;
		}
		else	// ±â°£ ¸¸·á
		{
			timeTime -= now;
			if (timeTime <= 86400) timeTime = 0;
			else
				timeTime /= 86400;
			szDay.HT_szFormat("%d", timeTime);

			g_cMainCharacter->HT_vMainChar_GetTimeStamp( index-1, szTime );

			clr.a = 1.0f; clr.r = 1.0f; clr.g = 0.4f; clr.b = 0.4f;
			HT_g_Script_SetMessage( eMsgWordExpired, &strTemp, _T("") );		//	"±â°£¸¸·á"
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+1, strTemp);
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+1, clr);
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+2, szTime);
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+2, clr);
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+3, szDay);
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+3, clr);
		}
	}
	else
	{
		g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+1, "");
		g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+2, "");
		g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+3, "");
	}

	// »ç¿ë¿©ºÎ¿¡ µû¸¥ ON or OFF Ã¼Å©
	if (m_iCheckEnable[index-1] == HT_TRUE)
	{

		if (m_iCheckUse[index-1] == HT_TRUE)
		{
			clr.a = 1.0f; clr.r = 1.0f; clr.g = 1.0f; clr.b = 1.0f;
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+4, "ON");
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+4, clr);
		}
		else
		{
			clr.a = 1.0f; clr.r = 1.0f; clr.g = 0.4f; clr.b = 0.4f;
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+4, "OFF");
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+4, clr);
		}
	}
	else
	{
		clr.a = 1.0f; clr.r = 0.8f; clr.g = 0.8f; clr.b = 0.8f;
		g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+4, "-");
		g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+4, clr);
	}

	return;
}

// ±¸ÀÔ ¸®½ºÆ® È®ÀÎ Ã¢ Output
HTvoid CHTIndividualStore::HT_vIndividualStore_ButtonCheckForBuyListOutPut( HTint iPage)
{ 
	CHTString strTemp;
	CHTString str;

	for (int i=1; i<7; i++)	// ¸ñ·Ï Áö¿ò
	{
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_BYELISTWND, (i*3)+1 , _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_BYELISTWND, (i*3)+2 , _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_BYELISTWND, (i*3)+3 , _T("") );
	}

	// Compute Page
	m_iMaxPage = int((m_byBuyItemNum-1) / 6)+1;
	m_iNowPage = iPage;

	HTint MaxPr, iPcode = 0;
	(m_iNowPage == m_iMaxPage) ? MaxPr = ((m_byBuyItemNum-1) % 6) + 1 : MaxPr = 6;

	for (int i=0; i<MaxPr; i++)
	{
		if ((m_sStoreItem[m_iBuyItem[i+iPage*6-6]].item.snIndex) == 0)
			continue;

		g_pParamMgr->HT_bGetItemName( HT_ITEM_INDEX_START + m_sStoreItem[m_iBuyItem[i+iPage*6-6]].item.snIndex, &str );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_BYELISTWND, ((i+1)*3)+1 , str.HT_szGetString() );

		str = g_cUIManager->HT_strSetRestMark(m_sStoreItem[m_iBuyItem[i+iPage*6-6]].item.byCount);
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_BYELISTWND, ((i+1)*3)+2 , str.HT_szGetString() );

		//str = g_cUIManager->HT_strSetRestMark(HT_iIndividualStore_GetRupiah(HT_iIndividualStore_GetKeyIDInBuyWin(i+iPage*6-6+10)));
		str = g_cUIManager->HT_strSetRestMark(HT_iIndividualStore_GetRupiah(m_iStoreItemKeyID[m_iBuyItem[i+iPage*6-6]]));
		
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_BYELISTWND, ((i+1)*3)+3 , str.HT_szGetString() );
	}

	//	¾ÆÀÌÅÛ °Ù¼ö
	str.HT_szFormat( "%d", m_byBuyItemNum );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_BYELISTWND, 31 , str.HT_szGetString() );

	//	¾ÆÀÌÅÛ ¾×¼ö
	str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_BYELISTWND, 32 , str.HT_szGetString() );

	// Page Output
	str.HT_szFormat("(Page %d/%d)",m_iNowPage, m_iMaxPage);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_BYELISTWND, 30 , str.HT_szGetString() );
}



HTvoid
CHTIndividualStore::HT_vIndividualStore_SelectItemForSell( HTdword dwItemKeyID )
{
	if( m_byStoreProcess != STORE_PROCESS_NONE || dwItemKeyID <= 0  )
		return;
	// Äù½ºÆ® Àü¿ë ¾ÆÀÌÅÛÀº »óÁ¡¿¡ µî·ÏÇÏÁö ¸øÇÏ°Ô ÇÑ´Ù.
	HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwItemIndex <= 0 || CHTParamIDCheck::HT_bIsItemQuestOnly( dwItemIndex ) )
		return;

	HTint iCount = g_cItemSystem->HT_iItemSystem_GetItemCount( dwItemKeyID );
	if( iCount < 0 )
		return;

	CHTString strTemp;
	// ÀÏºÎ ¾ÆÀÌÅÛÀº ¾ðÆÐÅ· ÇÒ ¼ö ¾ø´Ù. 2004. 11. 11 ¼±¿µ¹ü 
	m_bTimeItem = HT_FALSE;
	if (g_cItemControl->HT_bItemControl_IsItemTimeItem(dwItemIndex) == HT_FALSE)
	{
		// ½Ã°£Á¦ ¾ÆÀÌÅÛÀº ÃÖ´ë ÁßÃ¸°¹¼ö¿Í °°À»¶§¸¸ÀÌ ÆÇ¸Å°¡ °¡´ÉÇÏµµ·Ï ¼³Á¤
		if (g_cItemSystem->HT_wItemSystem_GetItemMaxPackCount(dwItemKeyID) == iCount)
		{
			m_bTimeItem = HT_TRUE;
			m_dwSelectKeyID = dwItemKeyID;
			m_iPackCount = iCount;
			HT_vIndividualStore_PriceWin_Active();
		}
		else
		{
			HT_g_Script_SetMessage( eMsgExplanPremiumItem01, &strTemp, _T("") );		//	"»ç¿ëÀüÀÇ À¯È¿½Ã°£À» °®°í ÀÖ´Â ¾ÆÀÌÅÛ¸¸ ÆÇ¸ÅÇÒ ¼ö ÀÖ½À´Ï´Ù."
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
			return;
		}
	}
	else if (dwItemIndex == 7068 || dwItemIndex == 7070 )	//fors_debug add 6828// ÀÌº¥Æ® ¿ìÅ¸¶ó ¾Ï¸®Å¸
	{
		// ½Ã°£Á¦ ¾ÆÀÌÅÛÀº ÃÖ´ë ÁßÃ¸°¹¼ö¿Í °°À»¶§¸¸ÀÌ ÆÇ¸Å°¡ °¡´ÉÇÏµµ·Ï ¼³Á¤
		if (g_cItemSystem->HT_wItemSystem_GetItemMaxPackCount(dwItemKeyID) == iCount)
		{
			m_bTimeItem = HT_TRUE;
			m_dwSelectKeyID = dwItemKeyID;
			m_iPackCount = iCount;
			HT_vIndividualStore_PriceWin_Active();
		}
		else
		{
			HT_g_Script_SetMessage( eMsgExplanPremiumItem02, &strTemp, _T("") );		//	"ÃÖ¼Ò ÇÑ¹­À½(250°³) ´ÜÀ§·Î¸¸ ÆÇ¸ÅÇÒ ¼ö ÀÖ½À´Ï´Ù"
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
			return;
		}
	}
	else
	{
		m_dwSelectKeyID = dwItemKeyID;
		if( iCount > 1 ) // ÆÇ¸Å °³¼ö ÀÔ·Â 
			HT_vIndividualStore_PackingWin_Active();
		else	// ÆÇ¸Å °¡°Ý ÀÔ·Â
		{
			m_iPackCount = 1;
			HT_vIndividualStore_PriceWin_Active();
		}
	}
}

// ÆÈ·Á´Â ¾ÆÀÌÅÛ ¼±ÅÃÇÏ±â
HTvoid
CHTIndividualStore::HT_vIndividualStore_AddSellItem( )
{
	if( m_byStoreProcess != STORE_PROCESS_NONE || m_dwSelectKeyID <= 0 || m_byStoreItemNum >= m_byMaxStoreItemCount )
		return;

	// ÃÑ ÆÇ¸Å±Ý¾× °Ë»ç

	HTint iTotalPrice;	// ½Ã°£Á¦ ¾ÆÀÌÅÛÀº °¹¼ö·Î ³ª´©Áö ¾Ê°í(¾ðÆÐÅ·µµ ÇÒ ¼ö ¾øÀ½) ÆÄ´Â°ÍÀÌ¹Ç·Î °¡°ÝÀ» Ä«¿îÆ®ÇÏÁö ¾Ê´Â´Ù.
	if (m_bTimeItem == HT_TRUE)
		iTotalPrice = m_iTotalPrice + m_iPrice;
	else
		iTotalPrice = m_iTotalPrice + m_iPrice * m_iPackCount;

	if( iTotalPrice < 0 )
	{
		CHTString szMessage;
		if( g_pMessageMgr->HT_bGetMessage( eMsgShopTotalPriceOverflow, &szMessage ) == true )
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, szMessage );
		return;
	}

	HT_ITEMSETTING_FLAG sLocRoom;
	if( g_cItemSystem->HT_bItemSystem_GetItemPos( m_dwSelectKeyID, sLocRoom ) == HT_TRUE 
			&& sLocRoom.nLocation == ITEM_LOCATION_PC )
	{
		HTbyte byInvenPos = (sLocRoom.pCellPos.x * _INVEN_HEIGHT + sLocRoom.pCellPos.y)
												+ (sLocRoom.nInventory * _INVEN_WIDTH * _INVEN_HEIGHT);
		for( HTint i = 0; i < m_byStoreItemNum ; ++i )
		{
			if( m_sStoreItem[i].nIndex == byInvenPos )
				return;	// ÀÌ¹Ì µé¾îÀÖ´Â ¾ÆÀÌÅÛ
		}

		m_sStoreItem[m_byStoreItemNum].nIndex = byInvenPos;
		
		if (m_bTimeItem == HT_TRUE)
			m_sStoreItem[m_byStoreItemNum].nPrice = m_iPrice;
		else
			m_sStoreItem[m_byStoreItemNum].nPrice = m_iPrice * m_iPackCount;

		// ¾ÆÀÌÅÛ Á¤º¸
		HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwSelectKeyID );
		m_sStoreItem[m_byStoreItemNum].item.snIndex = (HTshort)(dwItemIndex - HT_ITEM_INDEX_START);
		m_sStoreItem[m_byStoreItemNum].item.byCount = m_iPackCount;
		m_sStoreItem[m_byStoreItemNum].item.snDurability = g_cItemSystem->HT_sItemSystem_GetCurDurability( m_dwSelectKeyID );
		m_sStoreItem[m_byStoreItemNum].item.byRefineLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( m_dwSelectKeyID );
		ZeroMemory( m_sStoreItem[m_byStoreItemNum].item.bySubRefine, sizeof(HTbyte)*MAX_SUBMATERIALSIZE);
		g_cItemSystem->HT_iItemSystem_GetSubRefineItemsIndex( m_dwSelectKeyID, m_sStoreItem[m_byStoreItemNum].item.bySubRefine );

		// ÀÌ¹ÌÁö ±×¸®±â
		HTint nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
		g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND1, _STORE_SELL_BEGIN+m_byStoreItemNum, nXMLID );

		++m_byStoreItemNum;
		// ÃÑ ÆÇ¸Å±Ý¾× °»½Å 

		if (m_bTimeItem == HT_TRUE)
			m_iTotalPrice += m_iPrice;
		else
			m_iTotalPrice += m_iPrice * m_iPackCount;

		CHTString str;
		str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_INDIVIDUALWND1, 2, str.HT_szGetString() );

		m_iStoreItemKeyID[i] = m_dwSelectKeyID;
		m_dwSelectKeyID = 0;
	}
}

//---------°³¼ö ÀÔ·Â À©µµ¿ì ¶ç¿ì±â--------//
HTvoid 
CHTIndividualStore::HT_vIndividualStore_PackingWin_Active()
{
	m_iPackCount = 0;
	m_iStore_MsgBoxType = STORE_MSGTYPE_ITEMINPUT;
	CHTString strTemp;
	//	¿øÇÏ´Â °³¼ö¸¦ ÀÔ·ÂÇÏ¼¼¿ä
	g_cUIManager->HT_SetScriptMessage( eMsgCommonInputYouWantItem, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_MessageBox( _DIALOG_INDIVIDUALWND1, strTemp, UI_MESSAGEBOX_NUMBERINPUT );
}

//---------°¡°Ý ÀÔ·Â À©µµ¿ì ¶ç¿ì±â--------//
HTvoid 
CHTIndividualStore::HT_vIndividualStore_PriceWin_Active()
{
	m_iPrice = 0; 
	m_iStore_MsgBoxType = STORE_MSGTYPE_RUPIAINPUT;
	CHTString strTemp;
	//	¿øÇÏ´Â ·çÇÇ¾Æ¸¦ ÀÔ·ÂÇÏ¼¼¿ä
	g_cUIManager->HT_SetScriptMessage( eMsgCommonInputYouWantRuphia, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_MessageBox( _DIALOG_INDIVIDUALWND1, strTemp, UI_MESSAGEBOX_NUMBERINPUT );
}

// ÆÈ·Á´Â ¾ÆÀÌÅÛ Áö¿ì±â
HTvoid
CHTIndividualStore::HT_vIndividualStore_DeleteSellItem( HTint iPos )
{
	if( m_byStoreProcess != STORE_PROCESS_NONE || iPos < 0 || iPos >= m_byStoreItemNum )
		return;

	// ÃÑ ÆÇ¸Å±Ý¾× °»½Å
	m_iTotalPrice -= m_sStoreItem[iPos].nPrice;
	CHTString str;
	str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_INDIVIDUALWND1, 2, str.HT_szGetString() );

	HTdword dwItemIndex = 0;
	HTint nXMLID = 0;
	HTint i = 0, j = 0;
	// µÚ¿¡ ³ª¿­µÇ¾îÀÖ´ø ¾ÆÀÌÅÛ ¾ÕÀ¸·Î ´ç±â±â
	for( i = iPos ; i < (m_byStoreItemNum-1) ; ++i )
	{
		m_sStoreItem[i].nIndex = m_sStoreItem[i+1].nIndex;
		m_sStoreItem[i].nPrice = m_sStoreItem[i+1].nPrice;

		m_sStoreItem[i].item.byCount = m_sStoreItem[i+1].item.byCount;
		m_sStoreItem[i].item.snIndex = m_sStoreItem[i+1].item.snIndex;
		m_sStoreItem[i].item.snDurability = m_sStoreItem[i+1].item.snDurability;
		m_sStoreItem[i].item.byRefineLevel = m_sStoreItem[i+1].item.byRefineLevel;
		for( j = 0 ; j <= MAX_SUBMATERIALSIZE ; ++j )
			m_sStoreItem[i].item.bySubRefine[j] = m_sStoreItem[i+1].item.bySubRefine[j];

		m_iStoreItemKeyID[i] = m_iStoreItemKeyID[i+1];
		// ÀÌ¹ÌÁö ±×¸®±â
		dwItemIndex = HT_ITEM_INDEX_START + m_sStoreItem[i].item.snIndex;
		nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
		g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND1, _STORE_SELL_BEGIN+i, nXMLID );
	}
	ZeroMemory( &m_sStoreItem[i], sizeof( MOBSTOREITEM ) );
	m_iStoreItemKeyID[i] = 0;
	--m_byStoreItemNum;

	// ÀÌ¹ÌÁö Áö¿ì±â
	g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND1, _STORE_SELL_BEGIN+i, 0 );
}

// ±¸ÀÔÇÏ·Á´Â ¾ÆÀÌÅÛ ¼±ÅÃ ÇÏ±â
HTvoid
CHTIndividualStore::HT_vIndividualStore_AddBuyItem( HTint iPos )
{
	if( m_byStoreProcess != STORE_PROCESS_BUY || iPos < 0 || iPos >= MAX_MOBSTORE || m_byBuyItemNum >= MAX_MOBSTORE )
		return;

	// ÀÌ¹Ì ÆÈ¸° ¾ÆÀÌÅÛÀº ¼±ÅÃµÇÁö ¾Ê°Ô ÇÑ´Ù. (¹ö±× ¼öÁ¤ 2004. 10. 18 ¿ù¿äÀÏ ¼±¿µ¹ü)
	if (m_sStoreItem[iPos].item.snIndex == 0) return; 

	if( m_byBuyItemNum > 0 )	// °°Àº ¾ÆÀÌÅÛÀÌ ÀÖ´ÂÁö °Ë»ç
	{
		for(HTint i = 0 ; i < m_byBuyItemNum ; ++i )
		{
			if( m_iBuyItem[i] == iPos )
				return;
		}
	}

	m_iBuyItem[m_byBuyItemNum] = iPos;
	// ±¸¸Å ÃÑ¾× °»½Å
	m_iTotalPrice += m_sStoreItem[iPos].nPrice;
	CHTString str;
    str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_INDIVIDUALWND2, 3, str.HT_szGetString() );

	// ÀÌ¹ÌÁö ±×¸®±â
	HTdword dwItemIndex = HT_ITEM_INDEX_START + m_sStoreItem[iPos].item.snIndex;
	HTint nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
	g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND2, _STORE_BUY_MY_BEGIN+m_byBuyItemNum, nXMLID );
	++m_byBuyItemNum;
}
 
// ±¸ÀÔÇÏ·Á´Â ¾ÆÀÌÅÛ Áö¿ì±â
HTvoid
CHTIndividualStore::HT_vIndividualStore_DeleteBuyItem( HTint iPos )
{
	if( m_byStoreProcess != STORE_PROCESS_BUY || iPos < 0 || iPos >= m_byBuyItemNum )
		return;

	if( m_iBuyItem[iPos] > -1 )
	{
		// ±¸¸ÅÃÑ¾× °»½Å
        m_iTotalPrice -= m_sStoreItem[ m_iBuyItem[iPos] ].nPrice;
		CHTString str;
		str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_INDIVIDUALWND2, 3, str.HT_szGetString() );

		// µÚ¿¡ ÀÖ´ø ¾ÆÀÌÅÛ ¸ñ·Ï ¾ÕÀ¸·Î ´ç±â±â
		HTdword dwItemIndex = 0;
		HTint nXMLID = 0;
		for( HTint i = iPos ; i < (m_byBuyItemNum-1) ; ++i )
		{
			m_iBuyItem[i] = m_iBuyItem[i+1];
			
			// ÀÌ¹ÌÁö ±×¸®±â
			dwItemIndex = HT_ITEM_INDEX_START + m_sStoreItem[ m_iBuyItem[i+1] ].item.snIndex;
			nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
			g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND2, _STORE_BUY_MY_BEGIN+i, nXMLID );
		}
		m_iBuyItem[i] = -1;

		// ÀÌ¹ÌÁö Áö¿ì±â
		g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND2, _STORE_BUY_MY_BEGIN+i, 0 );
		--m_byBuyItemNum;
	}
}

HTvoid
CHTIndividualStore::HT_vIndividualStore_Close() 
{
    m_byStoreProcess = STORE_PROCESS_NONE;
	HTint iSaveStoreID = m_iStoreID;
	m_iTotalPrice = m_iStoreID = 0;

	HTint i = 0;
	for( i = 0 ; i < MAX_MOBSTORE ; ++i )
	{
		// ÆÇ¸Å Ã¢ 
		if( g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) )
		{
			// ÀÌ¹ÌÁö Áö¿ì±â
			if( m_sStoreItem[i].item.snIndex > 0 )
				g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND1, _STORE_SELL_BEGIN+i, 0 );
		}
		// ±¸ÀÔ Ã¢
		else
		{
			// ÀÌ¹ÌÁö Áö¿ì±â
			// ÆÇ¸ÅÃ¢
			if( m_sStoreItem[i].nPrice > 0 )
				g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND2, _STORE_SELL_BEGIN+i, 0 );
			// ±¸¸ÅÃ¢
			if( m_iBuyItem[i] >= 0 )
				g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND2, _STORE_BUY_MY_BEGIN+i, 0 );
			// °³ÀÎ»óÁ¡ ±¸ÀÔÃ¢ÀÇ ÆÇ¸Å ¸ñ·Ï
			if(  m_iStoreItemKeyID[i] > 0 )
				g_cItemSystem->HT_vItemSystem_DeleteItem( m_iStoreItemKeyID[i] );
			m_iBuyItem[i] = -1;
		}
	}
	ZeroMemory( m_sStoreItem, sizeof(MOBSTOREITEM)*MAX_MOBSTORE );
	m_byStoreItemNum = 0;
	m_byBuyItemNum = 0;
	ZeroMemory( m_iStoreItemKeyID, sizeof(HTint)*MAX_MOBSTORE );

	// ÆÇ¸Å Ã¢ ´Ý±â
	if( g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND1 );
		//	ÀÔ·ÂÀ» ¹ÞÀ½À¸·Î ÇØ¼­ ÀÚµ¿ ´ë±â¸ðµå Ãë¼Ò
		g_pDuelSystem->HT_vDuel_SetWaitModeCancelFromKeyInput();
	}
	// È®ÀÎ¹öÆ° ´Ù½Ã ´©¸¦ ¼ö ÀÖ°Ô ¼³Á¤
	// ±¸ÀÔ Ã¢ ´Ý±â
	if( g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
		g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		//	º¸¹°»óÀÚ ¾Ö´Ï¸ÅÀÌ¼ÇÀ» À§ÇÏ¿© ^^;;
		if( g_cSystem->HT_bSystem_GetShopModelMode() )
            g_cOtherObjectSystem->HT_vOtherObjectSystem_SetChangeAnimation( iSaveStoreID, CHARACTER_ANISTATE_STD, -1 );
	}
	// È®ÀÎ¹öÆ° ´Ù½Ã ´©¸¦ ¼ö ÀÖ°Ô ¼³Á¤
	// °æ°íÃ¢ ´Ý±â
}

// ±¸¸ÅÃ¢¿¡ µî·ÏµÈ ¾ÆÀÌÅÛ KeyID ±¸ÇÏ±â
HTint 
CHTIndividualStore::HT_iIndividualStore_GetKeyIDInBuyWin( HTint iPos )
{
	if( iPos<_STORE_BUY_BEGIN || iPos>_STORE_BUY_MY_END )
		return 0;
	//int a = m_iBuyItem[iPos-_STORE_BUY_BEGIN];
	//if (a = -1) return 0;
	return m_iStoreItemKeyID[iPos-_STORE_BUY_BEGIN] ;
}

// ÆÇ¸ÅÃ¢¿¡ µî·ÏµÈ ¾ÆÀÌÅÛ KeyID ±¸ÇÏ±â
HTint 
CHTIndividualStore::HT_iIndividualStore_GetKeyIDInSellWin( HTint iPos )
{
	if( iPos<_STORE_SELL_BEGIN || iPos>_STORE_PREMIUM_SELL_END )
		return -0;

	return m_iStoreItemKeyID[ iPos-_STORE_BUY_BEGIN ] ;
}

// ÆÇ¸Å¸ñ·ÏÀÇ ¾ÆÀÌÅÛ °¡°Ý ±¸ÇÏ±â
HTint
CHTIndividualStore::HT_iIndividualStore_GetRupiah( HTdword dwKeyID )
{
	for( HTint i = 0 ; i < MAX_MOBSTORE ; ++i )
	{
		if( m_iStoreItemKeyID[i] == dwKeyID )
			return m_sStoreItem[i].nPrice; 
	}

	return 0;
}

// ÆÇ¸Å¸ñ·ÏÀÇ ¾ÆÀÌÅÛ °³¼ö ±¸ÇÏ±â
HTint
CHTIndividualStore::HT_iIndividualStore_GetPackCount( HTdword dwKeyID )
{
	for( HTint i = 0 ; i < MAX_MOBSTORE ; ++i )
	{
		if( m_iStoreItemKeyID[i] == dwKeyID )
			return m_sStoreItem[i].item.byCount; 
	}

	return 0;
}

HTbool
CHTIndividualStore::HT_bIndividualStore_IsStoreMode()
{
	if( m_byStoreProcess == STORE_PROCESS_STORE )
		return HT_TRUE;
	else
		return HT_FALSE;
}

//-----------------------------------------------------------------
// ³×Æ®¿öÅ© ÇÔ¼ö
//-----------------------------------------------------------------
HTvoid
CHTIndividualStore::HT_vNetWork_CSP_Req_Store( HTint iStoreID )
{
	MSG_MobStore* info = HT_NULL;
	info = new MSG_MobStore;
	if( info == HT_NULL ) return;

	ZeroMemory( info, sizeof( MSG_MobStore ) );
	if( m_byStoreProcess == STORE_PROCESS_REQ_START )
	{
		info->nID = g_cMainCharacter->HT_iMainChar_GetKeyID();
		info->byMode = HT_STORE_MODE_START;
		// »óÁ¡ ¸Þ¼¼Áö
		if( m_szBuyMessage.HT_nGetSize() == 0 )
			g_pMessageMgr->HT_bGetMessage( eMsgShopDefaultName, &m_szBuyMessage ); // ¹°°Ç»ç¼¼¿ä

		CHTString::HT_hrStringCopy( info->szTrade, m_szBuyMessage.HT_szGetString(), STORE_MESSAGE_MAX_SIZE-1 );
		info->szTrade[ STORE_MESSAGE_MAX_SIZE-1 ] = '\0';

		HTint i = 0, j = 0;
		for( i = 0 ; i < MAX_MOBSTORE ; ++i )
		{
			if( m_sStoreItem[i].item.snIndex == 0 )
                info->TradeItem[i].nIndex = -1;
			else
				info->TradeItem[i].nIndex = m_sStoreItem[i].nIndex;
			info->TradeItem[i].nPrice = m_sStoreItem[i].nPrice;

			info->TradeItem[i].item.byCount = m_sStoreItem[i].item.byCount;
			info->TradeItem[i].item.snIndex = m_sStoreItem[i].item.snIndex;
			info->TradeItem[i].item.snDurability = m_sStoreItem[i].item.snDurability;
			info->TradeItem[i].item.byRefineLevel = m_sStoreItem[i].item.byRefineLevel;
			for( j = 0 ; j <= MAX_SUBMATERIALSIZE ; ++j )
				info->TradeItem[i].item.bySubRefine[j] = m_sStoreItem[i].item.bySubRefine[j];
		}
	}
	else if( m_byStoreProcess == STORE_PROCESS_REQ_END )
	{
		info->nID = g_cMainCharacter->HT_iMainChar_GetKeyID();
		info->byMode = HT_STORE_MODE_END;
	}
	else //if( m_byStoreProcess == STORE_PROCESS_REQ_BUY_LIST )
	{
		info->nID = m_iStoreID = iStoreID ;
		info->byMode = HT_STORE_MODE_START;

		m_byStoreProcess = STORE_PROCESS_REQ_BUY_LIST;
	}

	g_pNetWorkMgr->RequestStore( info );
	
	//-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqStore : %d-%s:mode%d-%d", 
	//											info->nID, info->szTrade, info->byMode, m_byStoreItemNum);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid
CHTIndividualStore::HT_vNetWork_SCP_Resp_Status( MSG_MobStatus* info )
{
	//	OtherObjectSystem¿¡ ¾Ë·ÁÁÜ
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTradeMode( info );
	// ³»°¡ ¹°Ç°¸ñ·ÏÀ» º¸°í ÀÖ´Â Ä³¸¯ÅÍÀÇ »óÁ¡ÀÌ ´ÝÇûÀ» °æ¿ì
	if( info->nID == m_iStoreID && info->byTradeMode == HT_STORE_MODE_END )
		HT_vIndividualStore_Close(); // ±¸¸ÅÃ¢ ´Ý±â
}

HTvoid
CHTIndividualStore::HT_vNetWork_SCP_Resp_Store( MSG_MobStore* info )
{
	if( m_byStoreProcess == STORE_PROCESS_REQ_START )
	{
		// »óÁ¡¸ðµå ½ÃÀÛ
		HT_vIndividualStore_StoreModeStart();
	}
	else if( m_byStoreProcess == STORE_PROCESS_REQ_END )
	{
		// »óÁ¡¸ðµå ÇØÁ¦
		HT_vIndividualStore_StoreModeEnd();
		HT_vIndividualStore_Close();
	}
	else if( m_byStoreProcess == STORE_PROCESS_REQ_BUY_LIST )
	{
		// »óÁ¡±¸¸Å¸¦ ½ÅÃ»ÇßÀ» °æ¿ì
		HTdword dwItemIndex = 0;
		HTint nXMLID = 0;

		m_byStoreItemNum = m_iTotalPrice = 0;

		HTint i = 0, j = 0, iKeyID = 0;
		for( i = 0 ; i < MAX_MOBSTORE ; ++i )
		{
			if( info->TradeItem[i].item.snIndex > 0 )
			{
				// ÀÌ¹ÌÁö °»½Å
				dwItemIndex = HT_ITEM_INDEX_START + info->TradeItem[i].item.snIndex;
				nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );

				m_sStoreItem[i].nPrice = info->TradeItem[i].nPrice;
				m_sStoreItem[i].item.byCount = info->TradeItem[i].item.byCount;
				m_sStoreItem[i].item.snIndex = info->TradeItem[i].item.snIndex;

				PS_SCP_RESP_ITEM_SET item = new S_SCP_RESP_ITEM_SET;
				item->byType = SET_ITEM_CREATE;
				item->byPlace = ITEM_PLACE_STORE;
				item->byIndex = i;
				item->sitem.snIndex = info->TradeItem[i].item.snIndex;
				item->sitem.byCount = info->TradeItem[i].item.byCount;
				item->sitem.byRefineLevel = info->TradeItem[i].item.byRefineLevel;
				item->sitem.snDurability = info->TradeItem[i].item.snDurability;

				for( j = 0 ; j < MAX_SUBMATERIALSIZE ; ++j )
					item->sitem.bySubRefine[j] = info->TradeItem[i].item.bySubRefine[j];

				g_cItemSystem->HT_vItemSystem_ItemSet( item );
				HT_DELETE( item );

				g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND2, _STORE_BUY_BEGIN+i, nXMLID );

				BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_STORE, i, iKeyID);
				m_iStoreItemKeyID[i] = iKeyID;

				++m_byStoreItemNum;
			}
			else
			{
				g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND2, _STORE_BUY_BEGIN+i, 0 );
				m_iStoreItemKeyID[i] = 0;
			}
		} // end of for( i = 0 ; i < MAX_MOBSTORE ; ++i )

        m_byStoreProcess = STORE_PROCESS_BUY;
		HT_vIndividualStore_Active( m_iStoreID );
	} // end of else if( m_byStroeProcess == STORE_PROCESS_REQ_BUY_LIST )
}
// »óÁ¡ÀÇ ¸ñ·Ï Áß ¼±ÅÃÇÑ ¾ÆÀÌÅÛ »ç±â ¿äÃ»
HTvoid
CHTIndividualStore::HT_vNetWork_CSP_Req_Store_Buy()
{
	MSG_MobStore_Buy* info = HT_NULL;
	info = new MSG_MobStore_Buy;
	if( info == HT_NULL ) return;
	
	info->nID = m_iStoreID;	// »óÁ¡À» ¿­°í ÀÖ´Â Ä³¸¯ÅÍÀÇ ¾ÆÀÌµð

	ZeroMemory( info->byIndex, sizeof(BYTE)*MAX_MOBSTORE );

	for( HTint i = 0 ; i < MAX_MOBSTORE ; ++i )
	{
		if( m_iBuyItem[i] >= 0 )
			info->byIndex[ m_iBuyItem[i] ] = HT_TRUE;
	}
	
	g_pNetWorkMgr->RequestStoreBuy( info );
	//-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqStoreBuy : Store %d-Num %d", m_iStoreID, m_byBuyItemNum);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid
CHTIndividualStore::HT_vNetWork_SCP_Resp_Store_Buy( MSG_MobStore_Buy* info )
{
	CHTString szMessage, szItemName, szParam1, szParam2, szMsgResult;
	HTint idMessage = eMsgParamNone, i = 0, j = 0;

	HTint iBuyRupiah = 0;
	for( i = 0 ; i < MAX_MOBSTORE ; ++i )
	{
		idMessage = eMsgParamNone;
		szMessage.HT_hrCleanUp(); szItemName.HT_hrCleanUp(); szMsgResult.HT_hrCleanUp();

		if( info->byIndex[i] == HT_TRUE )
		{
			if( m_byStoreProcess == STORE_PROCESS_REQ_BUY ) // ±¸¸ÅÀÚ
			{	
				// ¹°°ÇÀ» »ê °æ¿ì
				if( m_sStoreItem[i].item.snIndex > 0 )	
				{
					g_pParamMgr->HT_bGetItemName( HT_ITEM_INDEX_START + m_sStoreItem[i].item.snIndex, &szItemName );
					szParam1.HT_szFormat("%d", m_sStoreItem[i].nPrice );
					
					if( m_sStoreItem[i].item.byCount > 1 )
					{
						idMessage = eMsgItemBuySeveralNumOK;
						szParam2.HT_szFormat("%d", m_sStoreItem[i].item.byCount );
					}
					else
						idMessage = eMsgItemBuyOneOK;
				}
				// »ê ¹°°Ç ÃÑ ºñ¿ë °»½Å
				iBuyRupiah += m_sStoreItem[i].nPrice;
			}
		}
		else	
		{
			if( m_byStoreProcess == STORE_PROCESS_STORE ) // ÆÇ¸ÅÀÚ
			{	
				// ÆÈ¸° ¹°°Ç
				if( m_iStoreItemKeyID[i] > 0 )
				{
					if( m_sStoreItem[i].item.snIndex > 0 )
					{
						idMessage = eMsgItemSellSuccess;
						g_pParamMgr->HT_bGetItemName( HT_ITEM_INDEX_START + m_sStoreItem[i].item.snIndex, &szItemName );
						szParam1.HT_szFormat("%d", m_sStoreItem[i].nPrice );
					}

					// ¾ÆÀÌÅÛ º¯°æ Àû¿ë
					HTint iCurCount = g_cItemSystem->HT_iItemSystem_GetItemCount( m_iStoreItemKeyID[i] );
					if( iCurCount == m_sStoreItem[i].item.byCount )
						g_cItemSystem->HT_vItemSystem_DeleteItem( m_iStoreItemKeyID[i] );
					else
						g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( m_iStoreItemKeyID[i], iCurCount-m_sStoreItem[i].item.byCount );
					// ÃÑ ÆÇ¸Å±Ý¾× °»½Å
					m_iTotalPrice -= m_sStoreItem[i].nPrice; 
					// ³» µ· °»½Å
					HTint iRupiah = g_cEquipInventory->HT_iEquipInventory_GetPCMoney() + m_sStoreItem[i].nPrice;
					HT_Trace("\n[%d]¹°°ÇÆÈ¸² %d¿ø:%d\n", i, m_sStoreItem[i].nPrice, iRupiah );
					g_cEquipInventory->HT_vEquipInventory_SetPCMoney( iRupiah );

					ZeroMemory( &m_sStoreItem[i], sizeof(MOBSTOREITEM) );
					--m_byStoreItemNum;
					m_iStoreItemKeyID[i] = 0;
				}
				g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND1, _STORE_SELL_BEGIN+i, 0 );
			}
			else										// ±¸¸ÅÀÚ
			{
				// »çÁö ¸øÇÑ ¹°°Ç
				for( j = 0; j < m_byBuyItemNum ; ++j )
				{
					if( m_iBuyItem[j] == i )
					{
						idMessage = eMsgItemBuyDoNot;
						if( m_sStoreItem[i].item.snIndex > 0 )			
							g_pParamMgr->HT_bGetItemName( HT_ITEM_INDEX_START + m_sStoreItem[i].item.snIndex, &szItemName );
						break;
					}
				}
			}
		}

		if( idMessage != eMsgParamNone && g_pMessageMgr->HT_bGetMessage( idMessage, &szMessage ) == true )
		{
			if( idMessage == eMsgItemBuySeveralNumOK ) // %s¸¦ %s·çÇÇ¾Æ·Î %s°³ ±¸ÀÔÇß½À´Ï´Ù.
				szMsgResult.HT_szFormat( szMessage.HT_szGetString(),
										szItemName.HT_szGetString(), szParam1.HT_szGetString(), szParam2.HT_szGetString() );
			// %s¸¦ %s·çÇÇ¾Æ·Î ±¸ÀÔÇß½À´Ï´Ù.
			else if( idMessage == eMsgItemBuyOneOK ) 
				szMsgResult.HT_szFormat( szMessage.HT_szGetString(), szItemName.HT_szGetString(), szParam1.HT_szGetString() );
			// %s·çÇÇ¾Æ¿¡ %s°¡ ÆÇ¸ÅµÇ¾ú½À´Ï´Ù.
			else if( idMessage == eMsgItemSellSuccess ) 
				szMsgResult.HT_szFormat( szMessage.HT_szGetString(), szParam1.HT_szGetString(), szItemName.HT_szGetString() );
			else // %s¸¦ ±¸ÀÔÇÏÁö ¸øÇß½À´Ï´Ù.
				szMsgResult.HT_szFormat( szMessage.HT_szGetString(), szItemName.HT_szGetString() );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, szMsgResult );
		}
	} // end of for( i = 0 ; i < MAX_MOBSTORE ; ++i )

	if( m_byStoreProcess == STORE_PROCESS_STORE ) // »óÁ¡À» ¿­°í ÀÖ´Â ÁßÀÏ °æ¿ì
	{
		// ÆÇ¸ÅÃ¢ÀÇ ÆÇ¸Å ÃÑ¾× °»½Å
		CHTString str;
		str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_INDIVIDUALWND1, 2, str.HT_szGetString() );
		// ÆÇ¸ÅÃ¢ÀÇ ¼ÒÁö ±Ý¾× °»½Å
		str = g_cUIManager->HT_strSetRestMark( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_INDIVIDUALWND1, 3, str.HT_szGetString() );
		// ¹°Ç°ÀÌ ¸ðµÎ ÆÈ·ÈÀ» °æ¿ì - »óÁ¡ ´Ý±â
		if( m_byStoreItemNum == 0 ) 
		{
			HT_vIndividualStore_StoreModeEnd();
			HT_vIndividualStore_Close();
		}
	}
	else // ±¸¸ÅÇÑ °á°ú
	{
		// µ· °»½Å
		HTint iRemainRupiah = g_cEquipInventory->HT_iEquipInventory_GetPCMoney() - iBuyRupiah;
		HT_Trace("\n±¸¸Å°á°ú: ¼ÒÁö %d ¼Òºñ %d\n", g_cEquipInventory->HT_iEquipInventory_GetPCMoney(), iBuyRupiah );
		g_cEquipInventory->HT_vEquipInventory_SetPCMoney( iRemainRupiah );

		HT_vIndividualStore_Close();
	}
}

HTvoid
CHTIndividualStore::HT_vNetWork_CSP_Req_TimeMode(HTushort Mode)
{
	static Msg_TimeMode info;
	info.snDummy = 0;
	info.snMode = Mode;	// ¸ðµå¼³Á¤ÇÏ¿© º¸³»ÁØ´Ù.

	g_pNetWorkMgr->RequestTimeMode( &info );
	//-----µð¹ö±ë Å×½ºÆ®¸¦ À§ÇÏ¿©-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqTimeMode : %x", Mode);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}