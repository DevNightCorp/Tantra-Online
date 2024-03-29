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

#define STORE_MESSAGE_MAX_SIZE				51 // 한글 24자

#define HT_STORE_SELL_ITEM_COUNT_BASIC		(MAX_MOBSTORE/2) // 상점에 등록할 수 있는 아이템 기본 개수

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

	// 판매할 목록
	ZeroMemory( m_sStoreItem, sizeof( MOBSTOREITEM )*MAX_MOBSTORE );
	m_byStoreItemNum = 0;
	m_byMaxStoreItemCount = HT_STORE_SELL_ITEM_COUNT_BASIC;

	// 구입할 목록
	for( HTint i = 0 ; i < MAX_MOBSTORE; ++i )
		m_iBuyItem[i] = -1;
	m_byBuyItemNum = 0;
	ZeroMemory( m_iStoreItemKeyID, sizeof( HTint)*MAX_MOBSTORE );

	//	3분에 한번씩 채팅 메시지 날리기 위해
	m_dwAutoChatMsgStartTime = GetTickCount();

	// 사용내역 프리미엄서비스의 체크버튼을 모두 활성화 상태로 시작
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
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND1, 0, 8, 2, 36, 1400, 276, 6 );
	//	Texture 개인상점
	g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND1, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgInvenPrivateShop, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );//	개인상점
	//	Label 판매
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgShopSale, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 33, 64, 50, 18 );//	판매
	//	Label 판매총액
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgShopSaleTotalPrice, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 122, 265, 60, 17 );//	판매총액
	//	Label 소지금액
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgShopCarryRupia, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 122, 282, 60, 17 );//	소지금액
	//	Label 확장기한 표시
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 1, eMsgShopExpanceDate, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 115, 64, 137, 17 );//	확장기한
	//	Label 판매총액 액수
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 2, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 184, 265, 75, 17 );
	//	Label 소지금액 액수
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 3, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 184, 282, 75, 17 );
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_INDIVIDUALWND1, 5, 159, 56, 326, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 56, 326, 89, 19 );//	확인
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_INDIVIDUALWND1, 5 );
	//	Button 취소
	g_cUIManager->HT_AddButtonControl( _DIALOG_INDIVIDUALWND1, 6, 159, 157, 326, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 157, 326, 89, 19 );//	취소
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_INDIVIDUALWND1, 6 );
	//	Label 메시지
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND1, 7, eMsgShopMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 33, 247, 50, 17 );//	메시지
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_INDIVIDUALWND1, 7,  7 );
	//	Edit 판매 메시지
	g_cUIManager->HT_AddEditBoxControl( _DIALOG_INDIVIDUALWND1, 8, 9, 75, 245, 175, 17 );
	//	세로
	for( i=0 ; i<7 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND1, 0, 1, 33+(i*36), 87, 1400, 3, 143 );
	}
	//	가로
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
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND2, 0, 8, 2, 36, 1400, 276, 6 );
	//	Texture 명령
	g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND2, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 0, eMsgInvenPrivateShop, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );//	개인상점
	//	Label 구매총액
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 0, eMsgShopBuyTotalPrice, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 120, 390, 60, 17 );//	구매총액
	//	Label 소지금액
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 0, eMsgShopCarryRupia, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 120, 406, 60, 17 );//	소지금액
	//	Label 판매자
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 1, eMsgShopTrader, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 33, 56, 200, 15 );//	판매자
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_INDIVIDUALWND2, 1, 4 );
	//	Label 구매자
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 2, eMsgShopBuyer, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 33, 220, 200, 15 );//	구매자
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_INDIVIDUALWND2, 2, 4 );
	//	Label 구매총액 액수
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 3, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 184, 390, 75, 17 );
	//	Label 소지금액 액수
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 4, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 184, 406, 75, 17 );
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_INDIVIDUALWND2, 5, 159, 71, 441, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 71, 441, 89, 19 );//	확인
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_INDIVIDUALWND2, 5 );
	//	Button 취소
	g_cUIManager->HT_AddButtonControl( _DIALOG_INDIVIDUALWND2, 6, 159, 172, 441, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_INDIVIDUALWND2, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 172, 441, 89, 19 );//	취소
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_INDIVIDUALWND2, 6 );
	//	판매자
	//	세로
	for( i=0 ; i<7 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND2, 0, 1, 32+(i*36), 74, 1400, 3, 141 );
	}
	//	가로
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
	//	구매자
	//	세로
	for( i=0 ; i<7 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_INDIVIDUALWND2, 0, 1, 32+(i*36), 242, 1400, 3, 141 );
	}
	//	가로
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
	//	*****선택하신 아이템 구매 내역입니다.*****
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgShopExplain01, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 20, 360, 25 );//	*****선택하신 아이템 구매 내역입니다.*****
	//	***구매내역에 동의하시면 확인 버튼을 눌러 주세요***
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgShopExplain02, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 235, 360, 25 );//	***구매내역에 동의하시면 확인 버튼을 눌러 주세요***
	//	(Page 0/0)
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 30, _T("(Page1/1)"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 200, 50, 70, 20 );
	//	합계
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgShopSubTotal, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 200+12, 200, 20 );//	합계
	//	합계 겟수
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 31, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 220, 200+12, 50, 20 );
	//	합계 돈
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 32, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 250, 200+12, 100, 20 );
	//	아이템 목록
	for( i=1 ; i<7 ; i++ )
	{
		g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, (i*3)+1, _T(" "), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 70+((i-1)*23), 200, 25 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, (i*3)+2, _T(" "), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 220, 70+((i-1)*23), 50, 25 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, (i*3)+3, _T(" "), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 250, 70+((i-1)*23), 100, 25 );
	}
	//	Button 확인
	g_cUIManager->HT_AddButtonControl( _DIALOG_BYELISTWND, 1, 159, 90, 260, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgCommonConfirm, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 90, 260, 89, 19 );//	확인
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_BYELISTWND, 1 );
	//	Button 취소
	g_cUIManager->HT_AddButtonControl( _DIALOG_BYELISTWND, 2, 159, 220, 260, 160, 161, 1500, 89, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgCommonCancel, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 220, 260, 89, 19 );//	취소
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_BYELISTWND, 2 );
	//	좌 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_BYELISTWND, 3, 159, 270, 50, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgShopLeft, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 270, 50, 50, 19 );//	좌
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_BYELISTWND, 3 );
	//	우 버튼
	g_cUIManager->HT_AddButtonControl( _DIALOG_BYELISTWND, 4, 159, 325, 50, 160, 161, 1500, 50, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_BYELISTWND, 0, eMsgShopRight, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 325, 50, 50, 19 );//	우
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_BYELISTWND, 4 );


	// _DIALOG_MY_USEINFO_V3
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_MY_USEINFO_V3, _T("MyCash"), 459, 283, g_cIndividualStore->HT_vEI_InputCheckForMyUseInfo, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_MY_USEINFO_V3, 5 );

	// 1,37,456,37
	g_cUIManager->HT_AddTextureControl(_DIALOG_MY_USEINFO_V3, 0, 8, 3, 37, 1400, 452, 6);
	g_cUIManager->HT_AddTextureControl(_DIALOG_MY_USEINFO_V3, 0, 9, 39, 31);
	g_cUIManager->HT_AddLabelControl(_DIALOG_MY_USEINFO_V3, 99, eMsgShopExplain03, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 39, 31, 152, 19);//	프리미엄 서비스 이용내역
	
	// 라벨 & 버튼
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

	g_cUIManager->HT_AddLabelControl( _DIALOG_MY_USEINFO_V3, 36, eMsgShopExplain04, 0, HT_COLOR(1,0.5,0.25,1), HT_COLOR(1,1,1,1), 18, 230, 436, 19);//	프리미엄 서비스의 추가 신청시 적용기간이 늘어납니다.
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_MY_USEINFO_V3, 36, 7);
	g_cUIManager->HT_AddLabelControl( _DIALOG_MY_USEINFO_V3, 37, eMsgShopExplain05, 0, HT_COLOR(1,0.5,0.25,1), HT_COLOR(1,1,1,1), 18, 250, 436, 19);//	효과가 OFF인 상태인 경우라도 만료기간이 연장되지는 않습니다.
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
			// 판매시작 요청했거나 판매중이었다면 판매 종료를 서버에 보낸다
			if( g_cIndividualStore->m_byStoreProcess == STORE_PROCESS_STORE || g_cIndividualStore->m_byStoreProcess == STORE_PROCESS_REQ_START ) 
			{
				g_cIndividualStore->m_byStoreProcess = STORE_PROCESS_REQ_END;
				g_cIndividualStore->HT_vNetWork_CSP_Req_Store();
			}
			// 상점모드 해제
			g_cIndividualStore->HT_vIndividualStore_StoreModeEnd();
			// 판매창 닫기
			g_cIndividualStore->HT_vIndividualStore_Close();
		}
		//	확인
		else if( iTargetID == 5 )
		{
			// 판매를 위해 선택한 아이템이 있을 경우
			if( g_cIndividualStore->m_byStoreProcess == STORE_PROCESS_NONE && g_cIndividualStore->m_byStoreItemNum > 0 )
			{
				g_cIndividualStore->m_byStoreProcess = STORE_PROCESS_REQ_START;
				// 확인버튼 누른 상태 - 다시 누를 수 없게 함
				// 제한을 넘어간 메시지는 잘라냄 (버그 수정 2004. 10. 18 선영범)
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
		//	아이콘 없애기
		if( _STORE_SELL_BEGIN <= iTargetID && iTargetID <= _STORE_PREMIUM_SELL_END)
		{
			HTint iPos = ( iTargetID - _STORE_SELL_BEGIN )/* % _STORE_WIDTH*/;
			g_cIndividualStore->HT_vIndividualStore_DeleteSellItem( iPos );
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		// 판매개수 입력 창
		if( g_cIndividualStore->m_iStore_MsgBoxType == STORE_MSGTYPE_ITEMINPUT )
		{
			//	X버튼일때 창 지우기
           	if( iTargetID == 0 )
			{
				g_cIndividualStore->m_iPrice = 0;
			}
			// 확인 버튼
			else
			{
				g_cIndividualStore->m_iPackCount = iTargetID;
				// 개수 오류
				if( g_cIndividualStore->m_iPackCount <= 0 || 
					g_cIndividualStore->m_iPackCount > g_cItemSystem->HT_iItemSystem_GetItemCount( g_cIndividualStore->m_dwSelectKeyID ) ) 
				{
					CHTString szMessage;
					if( g_pMessageMgr->HT_bGetMessage( eMsgItemUnpackCountErr, &szMessage ) == true )
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, szMessage );
				}
				else
				{
					// 판매 가격 입력창 띄우기
					g_cIndividualStore->HT_vIndividualStore_PriceWin_Active();
				}
			}
		}
		// 판매 가격 입력창
		else if( g_cIndividualStore->m_iStore_MsgBoxType == STORE_MSGTYPE_RUPIAINPUT )
		{
			//	X버튼일때 창 지우기
           	if( iTargetID == 0 )
			{
				g_cIndividualStore->m_iPrice = 0;
			}
			// 확인 버튼
			else
			{
				g_cIndividualStore->m_iPrice = iTargetID;
				// 개수 오류
				if( g_cIndividualStore->m_iPackCount <= 0 || 
					g_cIndividualStore->m_iPackCount > g_cItemSystem->HT_iItemSystem_GetItemCount( g_cIndividualStore->m_dwSelectKeyID ) ) 
				{
					CHTString szMessage;
					if( g_pMessageMgr->HT_bGetMessage( eMsgItemUnpackCountErr, &szMessage ) == true )
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, szMessage );
				}
				else
				{
					// 아이템 뛰우기
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
			// 구매창 닫기
			g_cIndividualStore->HT_vIndividualStore_Close();
			g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		}
		else if( iTargetID == 5 )
		{
			// 구매할 아이템이 있을 경우
			if( g_cIndividualStore->m_byStoreProcess == STORE_PROCESS_BUY && g_cIndividualStore->m_byBuyItemNum > 0 )
			{
				g_cIndividualStore->m_byStoreProcess = STORE_PROCESS_REQ_BUY;
				// 확인버튼 누른 상태 - 다시 누를 수 없게 함
				// 한국어 버젼에서만 구매 리스트 띄움
				if (g_iInationalType == 0 ) 
				{
					// 구매 확인 리스트 띄움
					g_cUIManager->HT_ShowWindow( _DIALOG_BYELISTWND );
					g_cIndividualStore->m_iMaxPage = g_cIndividualStore->m_iNowPage = 1;
					g_cIndividualStore->HT_vIndividualStore_ButtonCheckForBuyListOutPut(g_cIndividualStore->m_iNowPage);
				}
				// 그렇지 않으면 바로 구매요청
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
			// 구입하려는 목록
			if( iPos >= MAX_MOBSTORE )
				g_cIndividualStore->HT_vIndividualStore_DeleteBuyItem( iPos-MAX_MOBSTORE );
			// 상점 목록
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
			// 구매창 닫기
			g_cIndividualStore->HT_vIndividualStore_Close();
		}
		//	확인창
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
			g_cIndividualStore->HT_vNetWork_CSP_Req_Store_Buy();
		}
		//	좌
		else if(iTargetID == 3)
		{
			if( g_cIndividualStore->m_iNowPage <= 1 ) g_cIndividualStore->m_iNowPage = g_cIndividualStore->m_iMaxPage+1;
			g_cIndividualStore->HT_vIndividualStore_ButtonCheckForBuyListOutPut(--g_cIndividualStore->m_iNowPage);
		}
		//	우
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

		g_cIndividualStore->m_iTabNo = iTargetID;	// 버튼넘버 얻기
		HTPoint pPt; pPt.x = 0; pPt.y = 0;
		g_cIndividualStore->HT_hrCheckBox( pPt );
	}
}

//-----------------------------------------------------------------
// 3분에 한번씩 채팅 메시지 날리기 위해
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
			// [판매]%s[%d,%d]
			if( g_pMessageMgr->HT_bGetMessage( eMsgShopNamePublicity, &szMessage ) == true )
			{
				HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition(); // 캐릭터 위치
				szPos.HT_szFormat("%d,%d", pPt.x, pPt.y );
				
				strTemp.HT_szFormat( szMessage.HT_szGetString(), m_szBuyMessage.HT_szGetString(), szPos.HT_szGetString() );
				//	3분에 한번씩 채팅 메시지 날리기 위해
				m_dwAutoChatMsgStartTime = GetTickCount();
				g_cChatting->HT_vSetData_Normal( strTemp );
			}
		}
	}
}
// 판매창/구입창 띄우기
HTvoid
CHTIndividualStore::HT_vIndividualStore_Active( HTint iStoreID )
{

	// 해당 지역의 일부 영역에서는 개인상점을 오픈할 수 없다. // 578 400 ~ 630 444 
	HTPoint pMainCharPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();

	if (g_wResentZoneServerID == 17 &&							// 비류성
		pMainCharPt.x > 578 && pMainCharPt.x < 630 &&			// 위탁상점 위치
		pMainCharPt.y > 400 && pMainCharPt.y < 444)
	{
		//HT_g_Script_SetMessage( eMsgExplanPremiumItem01, &strTemp, _T("") );		//	"해당 위치에서는 개인상점을 오픈할 수 없습니다.
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, "해당 위치에서는 개인상점을 오픈할 수 없습니다.");
		return;
	}


	// NPC와 작업하고 있는 경우|제련 하던 중일 경우 | 트레이드창이 떠있을 경우 처리 안함
	if( g_cNPCControl->HT_iNPCControl_ActiveNPCIndex() != 0 || 
		g_cUIManager->HT_isShowWindow( _DIALOG_REFINE ) || 
		g_cUIManager->HT_isShowWindow( _DIALOG_TRADEWND ) || 
		g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) ||
		g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) ) 
		return;

	// 나의 상태가 스턴이나 슬립일 경우 처리 안함
	if( g_cMainCharacter->HT_iMAinChar_GetAffections() & eTNVSAfn_Stun || 
		g_cMainCharacter->HT_iMAinChar_GetAffections() & eTNVSAfn_Sleep )
		return;

	// 주신전 지역일 경우 처리 안함
	if( HT_SUCCEED( HT_IS_TRIMURITIZONE( g_wResentZoneServerID ) ) )
		return;

	HTint iDlgNo;
	CHTString str;
	HTint iPCMoney;
	// 소지 금액
	iPCMoney = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();
	str = g_cUIManager->HT_strSetRestMark( iPCMoney );

	//	KeyID 비교하여
	// 구입창 띄우기
	if( iStoreID != g_cMainCharacter->HT_iMainChar_GetKeyID() )
	{
		m_iStoreID = iStoreID;
		iDlgNo = _DIALOG_INDIVIDUALWND2;

		// 소지 금액				
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 4, str.HT_szGetString() );
		// 구매 총액 초기화
		m_iTotalPrice = 0;
		str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice);
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 3, str.HT_szGetString() );
		// 판매자 이름 쓰기
		str = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID( iStoreID );
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 1, str.HT_szGetString() );
		// 구매자 이름 쓰기
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 2, g_oMainCharacterInfo.szCharName );
		//	보물상자 애니매이션을 위하여 ^^;;
		if( g_cSystem->HT_bSystem_GetShopModelMode() )
            g_cOtherObjectSystem->HT_vOtherObjectSystem_SetChangeAnimation( iStoreID, CHARACTER_ANISTATE_WLK, 1 );

			//	창 켬
		g_cUIManager->HT_ShowWindow( iDlgNo );
		g_cUIManager->HT_FocusOnEditBoxControl( iDlgNo, 8 );

	}
	// 판매창 띄우기
	else
	{
		m_iStoreID = 0;
		iDlgNo = _DIALOG_INDIVIDUALWND1;
		// 아이템 등록 최대 개수 확인

		time_t timeTime;
		if( g_cMainCharacter->HT_bMainChar_GetTimeStamp( eTime_Store, timeTime ) == HT_FALSE )
			return;
		// 확장 서비스를 신청해본 적이 없음
		if( timeTime <= 0 || g_cIndividualStore->m_iCheckUse[1] == HT_FALSE)
			HT_vRenewalPossibleBar( HT_FALSE );
		else
		{
			// 현재 시간 변환
			time_t now; time( &now );

			// 현재 시간과 확장 서비스 기한 비교
			if( now <= timeTime )
			{
				HT_vRenewalPossibleBar( HT_TRUE ); // 확장공간 사용 가능

				// 확장기한 표시하기
				CHTString szTime;
				g_cMainCharacter->HT_vMainChar_GetTimeStamp( 255, szTime );
				g_cUIManager->HT_SetTextLabelControl( iDlgNo, 1, szTime.HT_szGetString() );
			}
			else
				HT_vRenewalPossibleBar( HT_FALSE ); // 확장공간 사용 불가능
		}
		// 소지 금액
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 3, str.HT_szGetString() );
		// 판매 총액 초기화
		str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice);
		g_cUIManager->HT_SetTextLabelControl( iDlgNo, 2, str.HT_szGetString() );
		//	Init Edit Box
		g_cUIManager->HT_SetTextEditBoxControl( iDlgNo, 8, _T("") );

		//	창 켬
		g_cUIManager->HT_ShowWindow( iDlgNo );
		g_cUIManager->HT_FocusOnEditBoxControl( iDlgNo, 8 );

		//	IME String Init
		g_cImeMgr.vImeMgr_SetLanguage( HT_TRUE, 0 );
		g_cImeMgr.vHTImeMgr_Setm_szInputTextStr( "" );
		g_cImeMgr.InputString();
	}

	//	인벤토리 켬
	if( !g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) )
		g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();
}

// 사용 불가능한 표시 다시 그리기
HTvoid
CHTIndividualStore::HT_vRenewalPossibleBar( HTbool bUsable )
{
	if( bUsable == HT_TRUE ) // 확장된 공간 사용 가능
	{
		// 등록할 수 있는 아이템 최대개수 설정
		m_byMaxStoreItemCount = MAX_MOBSTORE;
		// 이전 사용 불가능 표시 지우기
		HT_vDelPossibleBar();
	}
	else // 확장된 공간 사용 불가능
	{
		// 등록할 수 있는 아이템 최대개수 설정
		m_byMaxStoreItemCount = HT_STORE_SELL_ITEM_COUNT_BASIC;
		// 사용 불가능한 부분의 Bitmap색을 바꾼다
		for( HTint x = _STORE_PREMIUM_SELL_BEGIN ; x <= _STORE_PREMIUM_SELL_END ; ++x )
		{
			g_cUIManager->HT_SetSlotBoxControlEnable( _DIALOG_INDIVIDUALWND1, x, HT_FALSE );
		}
	}
}

// 사용 불가능한 표시 삭제
HTvoid
CHTIndividualStore::HT_vDelPossibleBar( )
{
	HTint iColNo = 0;
	HTint iSizeX = _INVEN_WIDTH;

	// 사용 불가능한 인벤토리 부분의 Bitmap 색을 원래 색으로 바꾼다
	for( HTint x = _STORE_PREMIUM_SELL_BEGIN ; x <= _STORE_PREMIUM_SELL_END ; ++x )
	{
		g_cUIManager->HT_SetSlotBoxControlEnable( _DIALOG_INDIVIDUALWND1, x, HT_TRUE );
	}
}

// 상점 열기
HTvoid
CHTIndividualStore::HT_vIndividualStore_StoreModeStart() //fors_debug 역�絹嫄牙��絹慰愧�,옵뤠隣槨긴��?
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
			// 캐릭터 멀리 보내버리고 상점 캐릭터 위치 시키기
			HTvector3 vecTempPos = g_cMainCharacter->HT_vecGetPosition();
			g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ModelID, HTvector3( vecTempPos.x,vecTempPos.y-200.0f,vecTempPos.z ) );
			g_pEngineHandler->HT_hrMoveObject( g_cMainCharacter->m_iMainChar_ShopCharID, vecTempPos );
		}
	}
}

// 상점 닫기
HTvoid
CHTIndividualStore::HT_vIndividualStore_StoreModeEnd()
{
	// 상점 닫기 요청 결과를 받았거나 물건이 모두 팔렸을 경우
	if( m_byStoreProcess == STORE_PROCESS_REQ_END || m_byStoreItemNum == 0 )
	{
		// 상점모드 해제
		if( !g_cSystem->HT_bSystem_GetShopModelMode() )
		{
			if( g_cMainCharacter->HT_bMainChar_GetSitDownState() == HT_TRUE )
				g_cMainCharacter->HT_vMainChar_SetSit(); // 서기
		}
		else
		{
			// 캐릭터 멀리 보내버리고 상점 캐릭터 위치 시키기
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
			case 0: // 인벤토리 초기 설정
				if( !g_cUIManager->HT_isShowWindow(_DIALOG_EQUPINVENTORY) )
				{
					g_cEquipInventory->HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH, HT_FALSE ); // Bag2 사용 불가능;
					HT_g_Script_SetMessage( eMsgInventoryExpansionDisabled, &strTemp, _T("") );	//	인벤토리 확장 기능이 해제 되었습니다.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				}
				else
				{
					HT_g_Script_SetMessage( eMsgCloseInvendowWindowTry, &strTemp, _T("") );	//	인벤토리 창을 닫은후 다시 시도해 주십시오
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
					return HT_OK;
				}
				break;
			case 1:	// 개인상점확장
				if( !g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) )
				{
					HT_g_Script_SetMessage( eMsgPrivateStoreExpansionDisabled, &strTemp, _T("") );	//	개인상점 확장 기능이 해제 되었습니다.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				}
				else
				{
					HT_g_Script_SetMessage( eMsgClosePrivateStoreTry, &strTemp, _T("") );	//	개인상점 창을 닫은후 다시 시도하여 주십시오.
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
					return HT_OK;
				}
				break;
			case 2:	// 루피아 자동 습득
				HT_g_Script_SetMessage( eMsgAutomaticRupiaDisabled, &strTemp, _T("") );		//	"루피아 자동 습득 기능이 해제 되었습니다."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 3:	// 한달 아누바바
				HT_g_Script_SetMessage( eMsgAnubabaEffectDisabled, &strTemp, _T("") );		//	"아누바바 효과가 해제 되었습니다."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 4:	// 한달 아트만
				HT_g_Script_SetMessage( eMsgAtmanEffectDisabled, &strTemp, _T("") );		//	"아트만 효과가 해제 되었습니다."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 5:	// 한달 모든 차크라 상승
				HT_g_Script_SetMessage( eMsgAllChakraUpgradeDisabled, &strTemp, _T("") );		//	"모든 차크라 상승효과가 해제 되었습니다."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			}

			m_iCheckUse[iButtonNo] = 0;
		}
		else
		{
			switch(iButtonNo)
			{
			case 0: // 인벤토리 초기 설정
				if( !g_cUIManager->HT_isShowWindow(_DIALOG_EQUPINVENTORY) )
				{
					g_cEquipInventory->HT_vRenewalPossibleBar(ITEM_LOCATION_PC_BAG2, _INVEN_WIDTH); // Bag2 사용가능
					HT_g_Script_SetMessage( eMsgInventoryExpansionEnabled, &strTemp, _T("") );		//	"인벤토리 확장 기능이 적용 되었습니다."
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				}
				else
				{
					HT_g_Script_SetMessage( eMsgCloseInvendowWindowTry, &strTemp, _T("") );		//	"인벤토리 창을 닫은후 다시 시도해 주십시오."
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
					return HT_OK;
				}
				break;
			case 1:	// 개인상점확장
				if( !g_cUIManager->HT_isShowWindow(_DIALOG_INDIVIDUALWND1) )
				{
					HT_g_Script_SetMessage( eMsgPrivateStoreExpansionEnabled, &strTemp, _T("") );		//	"개인상점 확장 기능이 적용 되었습니다."
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				}
				else
				{
					HT_g_Script_SetMessage( eMsgClosePrivateStoreTry, &strTemp, _T("") );		//	"개인상점 창을 닫은후 다시 시도하여 주십시오."
					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
					return HT_OK;
				}
				break;
			case 2:	// 루피아 자동 습득
				HT_g_Script_SetMessage( eMsgAutomaticRupiaEnabled, &strTemp, _T("") );		//	"루피아 자동 습득 기능이 적용 되었습니다."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 3:	// 한달 아누바바
				HT_g_Script_SetMessage( eMsgAnubabaEffectEnabled, &strTemp, _T("") );		//	"아누바바 효과가 적용 되었습니다."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 4:	// 한달 아트만
				HT_g_Script_SetMessage( eMsgAtmanEffectEnabled, &strTemp, _T("") );		//	"아트만 효과가 적용 되었습니다."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			case 5:	// 한달 모든 차크라 상승
				HT_g_Script_SetMessage( eMsgAllChakraUpgradeEnabled, &strTemp, _T("") );		//	"모든 차크라 상승효과가 적용 되었습니다."
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp );
				break;
			}
			
			m_iCheckUse[iButtonNo] = 1;
		}
		HT_vIndividualStore_ButtonCheckForUseListOutPut();
		
		//서버로 패킷을 보낸다.
		g_cIndividualStore->HT_vNetWork_CSP_Req_TimeMode( g_cIndividualStore->PrimiumService_UseList() );
	}
	return HT_OK;
}

// 사용내역의 스위치 값을 반환한다.
HTushort
CHTIndividualStore::PrimiumService_UseList()
{
	// 패킷값 생성
	HTushort sMode = 0;
	if (m_iCheckUse[0]) sMode += 0x8000;
	if (m_iCheckUse[1]) sMode += 0x4000;
	if (m_iCheckUse[2]) sMode += 0x2000;
	if (m_iCheckUse[3]) sMode += 0x1000;
	if (m_iCheckUse[4]) sMode += 0x0800;
	if (m_iCheckUse[5]) sMode += 0x0400;

	// 1이 켜는거구, 0이 끄는거란다. 그러니 XOR 연산을 해버린다.
	sMode = sMode ^ 0xFC00;

	return sMode;
}

// 사용 내역 리스트 창 Output
HTvoid
CHTIndividualStore::HT_vIndividualStore_ButtonCheckForUseListOutPut()
{
	CHTString strTemp;
	const int WIDTH_NUM = 5;

	HT_g_Script_SetMessage( eMsgPremiumServiceName, &strTemp, _T("") );		//	"프리미엄 서비스명"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, 0, strTemp);
	HT_g_Script_SetMessage( eMsgWordInUse, &strTemp, _T("") );		//	"사용여부"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, 1, strTemp);
	HT_g_Script_SetMessage( eMsgWordExpireDate, &strTemp, _T("") );		//	"만료기간"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, 2, strTemp);
	HT_g_Script_SetMessage( eMsgWordDDay, &strTemp, _T("") );		//	"D-day"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, 3, strTemp);
	HT_g_Script_SetMessage( eMsgWordEffect, &strTemp, _T("") );		//	"효과"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, 4, strTemp);

	HT_g_Script_SetMessage( eMsgWordInvenExpansion, &strTemp, _T("") );		//	"인벤토리 확장"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*1, strTemp);
	HT_g_Script_SetMessage( eMsgWordPrivateStoreExpansion, &strTemp, _T("") );		//	"개인상점 확장"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*2, strTemp);
	HT_g_Script_SetMessage( eMsgAutomaticRupiaAcquisition, &strTemp, _T("") );		//	"루피아 자동습득"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*3, strTemp);
	HT_g_Script_SetMessage( eMsgWordAnubabaCharm, &strTemp, _T("") );		//	"아누바바 부적"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*4, strTemp);
	HT_g_Script_SetMessage( eMsgWordAtmanCharm, &strTemp, _T("") );		//	"아트만 부적"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*5, strTemp);
	HT_g_Script_SetMessage( eMsgAllChakraPlus15, &strTemp, _T("") );		//	"모든 차크라 15 증가"
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*6, strTemp);
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*7, "");
	g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, WIDTH_NUM*8, "");

	for (HTint iIndex=0; iIndex<6; ++iIndex)
		HT_vIndividualStore_GetUseListOutPut(iIndex+1);

	return;
}

// 확장기한 표시하기
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
		if( timeTime <= 0 ) // 사용안함
		{
			clr.a = 1.0f; clr.r = 0.8f; clr.g = 0.8f; clr.b = 0.8f;
			HT_g_Script_SetMessage( eMsgNotPurchased, &strTemp, _T("") );		//	"미구입"
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+1, strTemp);
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+1, clr);
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+2, "");
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+3, "");
		}
		else if( now <= timeTime ) // 사용중
		{
			timeTime -= now;
			if (timeTime <= 86400) timeTime = 0;
			else
				timeTime /= 86400;
			szDay.HT_szFormat("%d", timeTime);

			g_cMainCharacter->HT_vMainChar_GetTimeStamp( index-1, szTime );

			clr.a = 1.0f; clr.r = 1.0f; clr.g = 0.5f; clr.b = 0.25f;
			HT_g_Script_SetMessage( eMsgWordInUseing, &strTemp, _T("") );		//	"사용중"
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+1, strTemp);
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+1, clr);
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+2, szTime);
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+2, clr);
			g_cUIManager->HT_SetTextLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+3, szDay);
			g_cUIManager->HT_SetTextColorLabelControl(_DIALOG_MY_USEINFO_V3, (index*WIDTH_NUM)+3, clr);
			m_iCheckEnable[index-1] = 1;
		}
		else	// 기간 만료
		{
			timeTime -= now;
			if (timeTime <= 86400) timeTime = 0;
			else
				timeTime /= 86400;
			szDay.HT_szFormat("%d", timeTime);

			g_cMainCharacter->HT_vMainChar_GetTimeStamp( index-1, szTime );

			clr.a = 1.0f; clr.r = 1.0f; clr.g = 0.4f; clr.b = 0.4f;
			HT_g_Script_SetMessage( eMsgWordExpired, &strTemp, _T("") );		//	"기간만료"
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

	// 사용여부에 따른 ON or OFF 체크
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

// 구입 리스트 확인 창 Output
HTvoid CHTIndividualStore::HT_vIndividualStore_ButtonCheckForBuyListOutPut( HTint iPage)
{ 
	CHTString strTemp;
	CHTString str;

	for (int i=1; i<7; i++)	// 목록 지움
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

	//	아이템 겟수
	str.HT_szFormat( "%d", m_byBuyItemNum );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_BYELISTWND, 31 , str.HT_szGetString() );

	//	아이템 액수
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
	// 퀘스트 전용 아이템은 상점에 등록하지 못하게 한다.
	HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( dwItemKeyID );
	if( dwItemIndex <= 0 || CHTParamIDCheck::HT_bIsItemQuestOnly( dwItemIndex ) )
		return;

	HTint iCount = g_cItemSystem->HT_iItemSystem_GetItemCount( dwItemKeyID );
	if( iCount < 0 )
		return;

	CHTString strTemp;
	// 일부 아이템은 언패킹 할 수 없다. 2004. 11. 11 선영범 
	m_bTimeItem = HT_FALSE;
	if (g_cItemControl->HT_bItemControl_IsItemTimeItem(dwItemIndex) == HT_FALSE)
	{
		// 시간제 아이템은 최대 중첩갯수와 같을때만이 판매가 가능하도록 설정
		if (g_cItemSystem->HT_wItemSystem_GetItemMaxPackCount(dwItemKeyID) == iCount)
		{
			m_bTimeItem = HT_TRUE;
			m_dwSelectKeyID = dwItemKeyID;
			m_iPackCount = iCount;
			HT_vIndividualStore_PriceWin_Active();
		}
		else
		{
			HT_g_Script_SetMessage( eMsgExplanPremiumItem01, &strTemp, _T("") );		//	"사용전의 유효시간을 갖고 있는 아이템만 판매할 수 있습니다."
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
			return;
		}
	}
	else if (dwItemIndex == 7068 || dwItemIndex == 7070 )	//fors_debug add 6828// 이벤트 우타라 암리타
	{
		// 시간제 아이템은 최대 중첩갯수와 같을때만이 판매가 가능하도록 설정
		if (g_cItemSystem->HT_wItemSystem_GetItemMaxPackCount(dwItemKeyID) == iCount)
		{
			m_bTimeItem = HT_TRUE;
			m_dwSelectKeyID = dwItemKeyID;
			m_iPackCount = iCount;
			HT_vIndividualStore_PriceWin_Active();
		}
		else
		{
			HT_g_Script_SetMessage( eMsgExplanPremiumItem02, &strTemp, _T("") );		//	"최소 한묶음(250개) 단위로만 판매할 수 있습니다"
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp);
			return;
		}
	}
	else
	{
		m_dwSelectKeyID = dwItemKeyID;
		if( iCount > 1 ) // 판매 개수 입력 
			HT_vIndividualStore_PackingWin_Active();
		else	// 판매 가격 입력
		{
			m_iPackCount = 1;
			HT_vIndividualStore_PriceWin_Active();
		}
	}
}

// 팔려는 아이템 선택하기
HTvoid
CHTIndividualStore::HT_vIndividualStore_AddSellItem( )
{
	if( m_byStoreProcess != STORE_PROCESS_NONE || m_dwSelectKeyID <= 0 || m_byStoreItemNum >= m_byMaxStoreItemCount )
		return;

	// 총 판매금액 검사

	HTint iTotalPrice;	// 시간제 아이템은 갯수로 나누지 않고(언패킹도 할 수 없음) 파는것이므로 가격을 카운트하지 않는다.
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
				return;	// 이미 들어있는 아이템
		}

		m_sStoreItem[m_byStoreItemNum].nIndex = byInvenPos;
		
		if (m_bTimeItem == HT_TRUE)
			m_sStoreItem[m_byStoreItemNum].nPrice = m_iPrice;
		else
			m_sStoreItem[m_byStoreItemNum].nPrice = m_iPrice * m_iPackCount;

		// 아이템 정보
		HTdword dwItemIndex = g_cItemSystem->HT_dwSystem_GetItemIndex( m_dwSelectKeyID );
		m_sStoreItem[m_byStoreItemNum].item.snIndex = (HTshort)(dwItemIndex - HT_ITEM_INDEX_START);
		m_sStoreItem[m_byStoreItemNum].item.byCount = m_iPackCount;
		m_sStoreItem[m_byStoreItemNum].item.snDurability = g_cItemSystem->HT_sItemSystem_GetCurDurability( m_dwSelectKeyID );
		m_sStoreItem[m_byStoreItemNum].item.byRefineLevel = g_cItemSystem->HT_byItemSystem_GetMainRefineLevel( m_dwSelectKeyID );
		ZeroMemory( m_sStoreItem[m_byStoreItemNum].item.bySubRefine, sizeof(HTbyte)*MAX_SUBMATERIALSIZE);
		g_cItemSystem->HT_iItemSystem_GetSubRefineItemsIndex( m_dwSelectKeyID, m_sStoreItem[m_byStoreItemNum].item.bySubRefine );

		// 이미지 그리기
		HTint nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
		g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND1, _STORE_SELL_BEGIN+m_byStoreItemNum, nXMLID );

		++m_byStoreItemNum;
		// 총 판매금액 갱신 

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

//---------개수 입력 윈도우 띄우기--------//
HTvoid 
CHTIndividualStore::HT_vIndividualStore_PackingWin_Active()
{
	m_iPackCount = 0;
	m_iStore_MsgBoxType = STORE_MSGTYPE_ITEMINPUT;
	CHTString strTemp;
	//	원하는 개수를 입력하세요
	g_cUIManager->HT_SetScriptMessage( eMsgCommonInputYouWantItem, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_MessageBox( _DIALOG_INDIVIDUALWND1, strTemp, UI_MESSAGEBOX_NUMBERINPUT );
}

//---------가격 입력 윈도우 띄우기--------//
HTvoid 
CHTIndividualStore::HT_vIndividualStore_PriceWin_Active()
{
	m_iPrice = 0; 
	m_iStore_MsgBoxType = STORE_MSGTYPE_RUPIAINPUT;
	CHTString strTemp;
	//	원하는 루피아를 입력하세요
	g_cUIManager->HT_SetScriptMessage( eMsgCommonInputYouWantRuphia, &strTemp, _T(""), _T("") );
	g_cUIManager->HT_MessageBox( _DIALOG_INDIVIDUALWND1, strTemp, UI_MESSAGEBOX_NUMBERINPUT );
}

// 팔려는 아이템 지우기
HTvoid
CHTIndividualStore::HT_vIndividualStore_DeleteSellItem( HTint iPos )
{
	if( m_byStoreProcess != STORE_PROCESS_NONE || iPos < 0 || iPos >= m_byStoreItemNum )
		return;

	// 총 판매금액 갱신
	m_iTotalPrice -= m_sStoreItem[iPos].nPrice;
	CHTString str;
	str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_INDIVIDUALWND1, 2, str.HT_szGetString() );

	HTdword dwItemIndex = 0;
	HTint nXMLID = 0;
	HTint i = 0, j = 0;
	// 뒤에 나열되어있던 아이템 앞으로 당기기
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
		// 이미지 그리기
		dwItemIndex = HT_ITEM_INDEX_START + m_sStoreItem[i].item.snIndex;
		nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
		g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND1, _STORE_SELL_BEGIN+i, nXMLID );
	}
	ZeroMemory( &m_sStoreItem[i], sizeof( MOBSTOREITEM ) );
	m_iStoreItemKeyID[i] = 0;
	--m_byStoreItemNum;

	// 이미지 지우기
	g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND1, _STORE_SELL_BEGIN+i, 0 );
}

// 구입하려는 아이템 선택 하기
HTvoid
CHTIndividualStore::HT_vIndividualStore_AddBuyItem( HTint iPos )
{
	if( m_byStoreProcess != STORE_PROCESS_BUY || iPos < 0 || iPos >= MAX_MOBSTORE || m_byBuyItemNum >= MAX_MOBSTORE )
		return;

	// 이미 팔린 아이템은 선택되지 않게 한다. (버그 수정 2004. 10. 18 월요일 선영범)
	if (m_sStoreItem[iPos].item.snIndex == 0) return; 

	if( m_byBuyItemNum > 0 )	// 같은 아이템이 있는지 검사
	{
		for(HTint i = 0 ; i < m_byBuyItemNum ; ++i )
		{
			if( m_iBuyItem[i] == iPos )
				return;
		}
	}

	m_iBuyItem[m_byBuyItemNum] = iPos;
	// 구매 총액 갱신
	m_iTotalPrice += m_sStoreItem[iPos].nPrice;
	CHTString str;
    str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_INDIVIDUALWND2, 3, str.HT_szGetString() );

	// 이미지 그리기
	HTdword dwItemIndex = HT_ITEM_INDEX_START + m_sStoreItem[iPos].item.snIndex;
	HTint nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
	g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND2, _STORE_BUY_MY_BEGIN+m_byBuyItemNum, nXMLID );
	++m_byBuyItemNum;
}
 
// 구입하려는 아이템 지우기
HTvoid
CHTIndividualStore::HT_vIndividualStore_DeleteBuyItem( HTint iPos )
{
	if( m_byStoreProcess != STORE_PROCESS_BUY || iPos < 0 || iPos >= m_byBuyItemNum )
		return;

	if( m_iBuyItem[iPos] > -1 )
	{
		// 구매총액 갱신
        m_iTotalPrice -= m_sStoreItem[ m_iBuyItem[iPos] ].nPrice;
		CHTString str;
		str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_INDIVIDUALWND2, 3, str.HT_szGetString() );

		// 뒤에 있던 아이템 목록 앞으로 당기기
		HTdword dwItemIndex = 0;
		HTint nXMLID = 0;
		for( HTint i = iPos ; i < (m_byBuyItemNum-1) ; ++i )
		{
			m_iBuyItem[i] = m_iBuyItem[i+1];
			
			// 이미지 그리기
			dwItemIndex = HT_ITEM_INDEX_START + m_sStoreItem[ m_iBuyItem[i+1] ].item.snIndex;
			nXMLID = g_pEngineHandler->HT_dwGetItemUIID( dwItemIndex );
			g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND2, _STORE_BUY_MY_BEGIN+i, nXMLID );
		}
		m_iBuyItem[i] = -1;

		// 이미지 지우기
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
		// 판매 창 
		if( g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) )
		{
			// 이미지 지우기
			if( m_sStoreItem[i].item.snIndex > 0 )
				g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND1, _STORE_SELL_BEGIN+i, 0 );
		}
		// 구입 창
		else
		{
			// 이미지 지우기
			// 판매창
			if( m_sStoreItem[i].nPrice > 0 )
				g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND2, _STORE_SELL_BEGIN+i, 0 );
			// 구매창
			if( m_iBuyItem[i] >= 0 )
				g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND2, _STORE_BUY_MY_BEGIN+i, 0 );
			// 개인상점 구입창의 판매 목록
			if(  m_iStoreItemKeyID[i] > 0 )
				g_cItemSystem->HT_vItemSystem_DeleteItem( m_iStoreItemKeyID[i] );
			m_iBuyItem[i] = -1;
		}
	}
	ZeroMemory( m_sStoreItem, sizeof(MOBSTOREITEM)*MAX_MOBSTORE );
	m_byStoreItemNum = 0;
	m_byBuyItemNum = 0;
	ZeroMemory( m_iStoreItemKeyID, sizeof(HTint)*MAX_MOBSTORE );

	// 판매 창 닫기
	if( g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND1 ) )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND1 );
		//	입력을 받음으로 해서 자동 대기모드 취소
		g_pDuelSystem->HT_vDuel_SetWaitModeCancelFromKeyInput();
	}
	// 확인버튼 다시 누를 수 있게 설정
	// 구입 창 닫기
	if( g_cUIManager->HT_isShowWindow( _DIALOG_INDIVIDUALWND2 ) )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_INDIVIDUALWND2 );
		g_cUIManager->HT_HideWindow( _DIALOG_BYELISTWND );
		//	보물상자 애니매이션을 위하여 ^^;;
		if( g_cSystem->HT_bSystem_GetShopModelMode() )
            g_cOtherObjectSystem->HT_vOtherObjectSystem_SetChangeAnimation( iSaveStoreID, CHARACTER_ANISTATE_STD, -1 );
	}
	// 확인버튼 다시 누를 수 있게 설정
	// 경고창 닫기
}

// 구매창에 등록된 아이템 KeyID 구하기
HTint 
CHTIndividualStore::HT_iIndividualStore_GetKeyIDInBuyWin( HTint iPos )
{
	if( iPos<_STORE_BUY_BEGIN || iPos>_STORE_BUY_MY_END )
		return 0;
	//int a = m_iBuyItem[iPos-_STORE_BUY_BEGIN];
	//if (a = -1) return 0;
	return m_iStoreItemKeyID[iPos-_STORE_BUY_BEGIN] ;
}

// 판매창에 등록된 아이템 KeyID 구하기
HTint 
CHTIndividualStore::HT_iIndividualStore_GetKeyIDInSellWin( HTint iPos )
{
	if( iPos<_STORE_SELL_BEGIN || iPos>_STORE_PREMIUM_SELL_END )
		return -0;

	return m_iStoreItemKeyID[ iPos-_STORE_BUY_BEGIN ] ;
}

// 판매목록의 아이템 가격 구하기
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

// 판매목록의 아이템 개수 구하기
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
// 네트워크 함수
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
		// 상점 메세지
		if( m_szBuyMessage.HT_nGetSize() == 0 )
			g_pMessageMgr->HT_bGetMessage( eMsgShopDefaultName, &m_szBuyMessage ); // 물건사세요

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
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqStore : %d-%s:mode%d-%d", 
	//											info->nID, info->szTrade, info->byMode, m_byStoreItemNum);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

HTvoid
CHTIndividualStore::HT_vNetWork_SCP_Resp_Status( MSG_MobStatus* info )
{
	//	OtherObjectSystem에 알려줌
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTradeMode( info );
	// 내가 물품목록을 보고 있는 캐릭터의 상점이 닫혔을 경우
	if( info->nID == m_iStoreID && info->byTradeMode == HT_STORE_MODE_END )
		HT_vIndividualStore_Close(); // 구매창 닫기
}

HTvoid
CHTIndividualStore::HT_vNetWork_SCP_Resp_Store( MSG_MobStore* info )
{
	if( m_byStoreProcess == STORE_PROCESS_REQ_START )
	{
		// 상점모드 시작
		HT_vIndividualStore_StoreModeStart();
	}
	else if( m_byStoreProcess == STORE_PROCESS_REQ_END )
	{
		// 상점모드 해제
		HT_vIndividualStore_StoreModeEnd();
		HT_vIndividualStore_Close();
	}
	else if( m_byStoreProcess == STORE_PROCESS_REQ_BUY_LIST )
	{
		// 상점구매를 신청했을 경우
		HTdword dwItemIndex = 0;
		HTint nXMLID = 0;

		m_byStoreItemNum = m_iTotalPrice = 0;

		HTint i = 0, j = 0, iKeyID = 0;
		for( i = 0 ; i < MAX_MOBSTORE ; ++i )
		{
			if( info->TradeItem[i].item.snIndex > 0 )
			{
				// 이미지 갱신
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
// 상점의 목록 중 선택한 아이템 사기 요청
HTvoid
CHTIndividualStore::HT_vNetWork_CSP_Req_Store_Buy()
{
	MSG_MobStore_Buy* info = HT_NULL;
	info = new MSG_MobStore_Buy;
	if( info == HT_NULL ) return;
	
	info->nID = m_iStoreID;	// 상점을 열고 있는 캐릭터의 아이디

	ZeroMemory( info->byIndex, sizeof(BYTE)*MAX_MOBSTORE );

	for( HTint i = 0 ; i < MAX_MOBSTORE ; ++i )
	{
		if( m_iBuyItem[i] >= 0 )
			info->byIndex[ m_iBuyItem[i] ] = HT_TRUE;
	}
	
	g_pNetWorkMgr->RequestStoreBuy( info );
	//-----디버깅 테스트를 위하여-----//
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
			if( m_byStoreProcess == STORE_PROCESS_REQ_BUY ) // 구매자
			{	
				// 물건을 산 경우
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
				// 산 물건 총 비용 갱신
				iBuyRupiah += m_sStoreItem[i].nPrice;
			}
		}
		else	
		{
			if( m_byStoreProcess == STORE_PROCESS_STORE ) // 판매자
			{	
				// 팔린 물건
				if( m_iStoreItemKeyID[i] > 0 )
				{
					if( m_sStoreItem[i].item.snIndex > 0 )
					{
						idMessage = eMsgItemSellSuccess;
						g_pParamMgr->HT_bGetItemName( HT_ITEM_INDEX_START + m_sStoreItem[i].item.snIndex, &szItemName );
						szParam1.HT_szFormat("%d", m_sStoreItem[i].nPrice );
					}

					// 아이템 변경 적용
					HTint iCurCount = g_cItemSystem->HT_iItemSystem_GetItemCount( m_iStoreItemKeyID[i] );
					if( iCurCount == m_sStoreItem[i].item.byCount )
						g_cItemSystem->HT_vItemSystem_DeleteItem( m_iStoreItemKeyID[i] );
					else
						g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( m_iStoreItemKeyID[i], iCurCount-m_sStoreItem[i].item.byCount );
					// 총 판매금액 갱신
					m_iTotalPrice -= m_sStoreItem[i].nPrice; 
					// 내 돈 갱신
					HTint iRupiah = g_cEquipInventory->HT_iEquipInventory_GetPCMoney() + m_sStoreItem[i].nPrice;
					HT_Trace("\n[%d]물건팔림 %d원:%d\n", i, m_sStoreItem[i].nPrice, iRupiah );
					g_cEquipInventory->HT_vEquipInventory_SetPCMoney( iRupiah );

					ZeroMemory( &m_sStoreItem[i], sizeof(MOBSTOREITEM) );
					--m_byStoreItemNum;
					m_iStoreItemKeyID[i] = 0;
				}
				g_cUIManager->HT_SetSlotImage( _DIALOG_INDIVIDUALWND1, _STORE_SELL_BEGIN+i, 0 );
			}
			else										// 구매자
			{
				// 사지 못한 물건
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
			if( idMessage == eMsgItemBuySeveralNumOK ) // %s를 %s루피아로 %s개 구입했습니다.
				szMsgResult.HT_szFormat( szMessage.HT_szGetString(),
										szItemName.HT_szGetString(), szParam1.HT_szGetString(), szParam2.HT_szGetString() );
			// %s를 %s루피아로 구입했습니다.
			else if( idMessage == eMsgItemBuyOneOK ) 
				szMsgResult.HT_szFormat( szMessage.HT_szGetString(), szItemName.HT_szGetString(), szParam1.HT_szGetString() );
			// %s루피아에 %s가 판매되었습니다.
			else if( idMessage == eMsgItemSellSuccess ) 
				szMsgResult.HT_szFormat( szMessage.HT_szGetString(), szParam1.HT_szGetString(), szItemName.HT_szGetString() );
			else // %s를 구입하지 못했습니다.
				szMsgResult.HT_szFormat( szMessage.HT_szGetString(), szItemName.HT_szGetString() );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_ITEM, szMsgResult );
		}
	} // end of for( i = 0 ; i < MAX_MOBSTORE ; ++i )

	if( m_byStoreProcess == STORE_PROCESS_STORE ) // 상점을 열고 있는 중일 경우
	{
		// 판매창의 판매 총액 갱신
		CHTString str;
		str = g_cUIManager->HT_strSetRestMark( m_iTotalPrice );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_INDIVIDUALWND1, 2, str.HT_szGetString() );
		// 판매창의 소지 금액 갱신
		str = g_cUIManager->HT_strSetRestMark( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_INDIVIDUALWND1, 3, str.HT_szGetString() );
		// 물품이 모두 팔렸을 경우 - 상점 닫기
		if( m_byStoreItemNum == 0 ) 
		{
			HT_vIndividualStore_StoreModeEnd();
			HT_vIndividualStore_Close();
		}
	}
	else // 구매한 결과
	{
		// 돈 갱신
		HTint iRemainRupiah = g_cEquipInventory->HT_iEquipInventory_GetPCMoney() - iBuyRupiah;
		HT_Trace("\n구매결과: 소지 %d 소비 %d\n", g_cEquipInventory->HT_iEquipInventory_GetPCMoney(), iBuyRupiah );
		g_cEquipInventory->HT_vEquipInventory_SetPCMoney( iRemainRupiah );

		HT_vIndividualStore_Close();
	}
}

HTvoid
CHTIndividualStore::HT_vNetWork_CSP_Req_TimeMode(HTushort Mode)
{
	static Msg_TimeMode info;
	info.snDummy = 0;
	info.snMode = Mode;	// 모드설정하여 보내준다.

	g_pNetWorkMgr->RequestTimeMode( &info );
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqTimeMode : %x", Mode);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}