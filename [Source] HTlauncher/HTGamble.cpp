#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "HTGamble.h"


HTshort g_srgSymbolForSiege[11][3] = 
{
	202,150, 3,			//	3상징물
	124,147, 2,			//	2상징물
	198,207, 2,			//	2상징물
	151,212, 1,
	101,203, 1,
	90,154, 1,
	123,86, 1,
	88,63, 1,
	159,77, 1,
	191,69, 1,
	158,28, 1,
} ;

int m_PosArrayX[YUT_MAX_NUMBER] = {343, 343, 343, 343, 343, 343, 288, 231, 174, 118, 62, 62, 62, 62, 62, 62, 118, 174, 231, 288, 116, 165, 205, 246, 288, 288, 246, 165, 116 };
int m_PosArrayY[YUT_MAX_NUMBER] = {350, 296, 241, 185, 132, 78, 78, 78, 78, 78, 78, 133, 187, 241, 296, 350, 350, 350, 350, 350, 133, 176, 215, 251, 297, 134, 176, 251, 296 };

HTint g_iSiegeMark[5] = {86,82,84,83,85};
HTint g_iSiegeUnionMark[5] = {191,188,189,190,192};

HTfloat g_fYutPercent[30] = { 1.0f, 1.8f, 1.0f, 1.0f, 1.2f, 1.0f, 1.5f, 2.0f, 2.0f, 1.8f, 2.0f, 2.5f, 3.0f, 3.5f, 3.0f, 2.0f, 1.8f, 2.0f, 1.8f, 1.8f, 8.0f, 5.0f, 1.5f, 3.0f, 2.4f, 4.0f, 2.3f, 3.5f, 3.8f };


// HTGamble.cpp 에서만 쓰이는 상수 정의

const int UI_WINDOW_GAMBLE = _DIALOG_GAMBLE_YUT;	// IMAGE TYPE GAMBLE WINDOW NUMBER (그림 형식 윈도우)
const int UI_WINDOW_GAMBLE2 = 6;	// STATE TYPE GAMBLE WINDOW NUMBER (표 형식 윈도우) - 미사용


const int GOLD_ITEM_ID	= 7383;	// 갬블에서 사용하는 금편 아이디
//
// 실제 외부에서 쓰이는 함수들입니다. (Public Type)
//
HTGamble::HTGamble(void) {}
HTGamble::~HTGamble(void)
{
	g_cUIManager->HT_DeleteWindow( UI_WINDOW_GAMBLE );
}

// 처음 한번만 실행됨 (이곳에서 UI Window 생성 및 필요한 컨트롤을 생성한다) 
// 컨트롤 배치를 위해 약간의 노가다 필요;; (조만간 UI 툴 개발예정임)
HTvoid HTGamble::HT_vGamble_Init()
{
	CHTString strMessage;

	// 윈도우를 생성합니다.
	g_cUIManager->HT_SetScriptMessage( eMsgYutTitle, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_CreateWindow(UI_WINDOW_GAMBLE, strMessage, 450, 510, g_cGamble->HT_hrGamble_InputCheck, 2);
	g_cUIManager->HT_MoveWindow(UI_WINDOW_GAMBLE, 150, 150);
	//g_cUIManager->HT_ShowWindow(UI_WINDOW_GAMBLE);

	// 외각 테두리 꾸밈
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 17, 15, 22); for (int i = 1; i < 12; ++i) g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 18, 15 + (32*i), 22);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 19, 15 + (32*12), 22); for (int i = 1; i < 12; ++i) g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 20, 15 + (32*12), 22 + (32*i));
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 16, 15 + (32*12), 22 + (32*12)); for (int i = 1; i < 12; ++i) g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 18, 15 + (32*i), 22 + (32*12));
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 21, 15, 22 + (32*12)); for (int i = 1; i < 12; ++i) g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 20, 15, 22 + (32*i));
	
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 163, 382, 358, 1500, 18, 30);
	
	// 주춧돌 버튼 생성 (파란색)
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 1, 194, 342, 352); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 1, 22, 342+7, 352+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 1);	// 노란색 1 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 2, 194, 342, 296); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 2, 23, 342+7, 296+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 2);	// 노란색 2 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 3, 194, 342, 242); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 3, 24, 342+7, 242+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 3);	// 노란색 3 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 4, 194, 342, 187); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 4, 25, 342+7, 187+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 4);	// 노란색 4 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 5, 194, 342, 134); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 5, 26, 342+7, 134+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 5);	// 노란색 5 버튼
	
	// 주춧돌 버튼 생성 (하늘색)
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 6, 193, 342, 80); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 6, 22, 342+7, 80+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 6);	// 빨간색 1 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 7, 193, 287, 80); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 7, 23, 287+7, 80+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 7);	// 빨간색 2 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 8, 193, 230, 80); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 8, 24, 230+7, 80+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 8);	// 빨간색 3 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 9, 193, 174, 80); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 9, 25, 174+7, 80+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 9);	// 빨간색 4 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 10, 193, 117, 80); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 10, 26, 117+7, 80+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 10);	// 빨간색 5 버튼

	// 주춧돌 버튼 생성 (노란색)
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 11, 195, 61, 79); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 11, 22, 61+7, 79+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 11);	// 파란색 1 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 12, 195, 61, 134); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 12, 23, 61+7, 134+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 12);	// 파란색 2 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 13, 195, 61, 188); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 13, 24, 61+7, 188+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 13);	// 파란색 3 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 14, 195, 61, 242); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 14, 25, 61+7, 242+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 14);	// 파란색 4 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 15, 195, 61, 297); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 15, 26, 61+7, 297+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 15);	// 파란색 5 버튼

	// 주춧돌 버튼 생성 (빨간색)
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 16, 196, 61, 352); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 16, 22, 61+7, 352+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 16);	// 하늘색 1 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 17, 196, 117, 352); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 17, 23, 117+7, 352+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 17);	// 하늘색 2 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 18, 196, 174, 352); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 18, 24, 174+7, 352+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 18);	// 하늘색 3 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 19, 196, 230, 352); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 19, 25, 230+7, 352+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 19);	// 하늘색 4 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 20, 196, 287, 352); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 20, 26, 287+7, 352+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 20);	// 하늘색 5 버튼

	// 주춧돌 버튼 생성 (연두색)
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 25, 197, 287, 297); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 25, 26, 287+7, 297+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 25);	// 연두색 1 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 24, 197, 245, 252); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 24, 27, 245+7, 252+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 24);	// 연두색 2 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 27, 197, 245, 177); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 27, 28, 245+7, 177+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 27);	// 연두색 3 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 26, 197, 287, 134); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 26, 29, 287+7, 134+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 26);	// 연두색 4 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 21, 197, 115, 134); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 21, 22, 115+7, 134+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 21);	// 연두색 5 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 22, 197, 164, 177); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 22, 23, 164+7, 177+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 22);	// 연두색 6 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 29, 197, 115, 297); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 29, 25, 115+7, 297+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 29);	// 연두색 7 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 28, 197, 163, 252); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 28, 24, 163+7, 252+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 28);	// 연두색 8 버튼
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 23, 197, 204, 216); g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 23, 30, 204+7, 216+7); g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 23);	// 연두색 9 버튼

	// 새로고침 버튼
    g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 30, 159 , 124, 474, 160, 161, 1500, 104, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_GAMBLE, 0, eMsgCommonReFresh, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 124, 474, 104, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgYutExplain01, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_SetButtonToolTip(UI_WINDOW_GAMBLE, 30, strMessage);
	g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 30);
	
	// 당첨금 지급 버튼
	g_cUIManager->HT_AddButtonControl(UI_WINDOW_GAMBLE, 31, 159 , 244, 474, 160, 161, 1500, 104, 19);	
	g_cUIManager->HT_SetScriptMessage( eMsgYutUrgentAllotment, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_GAMBLE, 0, strMessage, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 244, 474, 104, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgYutExplainAllotment, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_SetButtonToolTip(UI_WINDOW_GAMBLE, 31, strMessage);
	g_cUIManager->HT_SetButtonToolTipOn(UI_WINDOW_GAMBLE, 31);

	// 내 적립액 및 총 적립액 출력
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 1, 8, 444, 1400, 3, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 1, 81, 444, 1400, 3, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 1, 221, 444, 1400, 3, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 1, 296, 444, 1400, 3, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 1, 435, 444, 1400, 3, 19);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 2, 7, 444, 1400, 430, 3);
	g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, 0, 2, 7, 463, 1400, 430, 3);
	g_cUIManager->HT_SetScriptMessage( eMsgYutBuildMoney, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_GAMBLE, 0, strMessage, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 8, 446, 74, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgYutTotalMoney, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_GAMBLE, 0, strMessage, 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 222, 446, 74, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_GAMBLE, 1, "0", 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 83, 446, 134, 19);
	g_cUIManager->HT_AddLabelControl(UI_WINDOW_GAMBLE, 2, "0", 0, HT_COLOR(1,1,1,1), HT_COLOR(1,1,1,1), 299, 446, 134, 19);

}

// 처음 화면 팝업시 호출 (UI 기본작업)
HTvoid HTGamble::HT_vGamble_WindowPopup()
{
	// 서버로 부터 내 정보 요청 패킷을 보낸다. (받으면 전체 정보 패킷 요청후 받으면 그때서야 창 띄움)
	this->HT_vNetWork_CSP_Req_YutMyMoney();
	// 지금은 임시 버전으로 가지고 있는 모든 금편이 배팅되게 됩니다. 배팅할 만큼 구입해서 테스트 부탁드립니다.
	//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, _T("지금은 임시 버전으로 가지고 있는 모든 금편이 배팅되게 됩니다. 배팅할 만큼 구입해서 테스트 부탁드립니다."));
}

// 윈도우 정보 갱신시 호출 (이곳에서 UI Widnow의 컨트롤 정보들 셋팅 및 배치를 한다.)
HTvoid HTGamble::HT_vGamble_SetInfo()
{
	// 간단히 버튼의 툴팁 내용을 갱신하여 볼 수 있도록 한다
	CHTString str;
	for (int i = 0; i<YUT_MAX_NUMBER; ++i)
	{
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100));		// 하 1
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100)+1);	// 하 2
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100)+2);	// 하 3
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100)+3);	// 중 1
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100)+4);	// 중 2
		g_cUIManager->HT_DelTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100)+5);	// 상 1

		g_cUIManager->HT_DelTextureControl(UI_WINDOW_GAMBLE, i+107);		// 꾸밈이미지
 
		if (m_MyStatus[i] > 0)	// 자신의 배팅액이 1루피아 이상 적립되어 있는 주춧돌이라면 주변 꾸밈 박스 출력
		{		
			g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, i+107, 210, m_PosArrayX[i]-5, m_PosArrayY[i]-3, 1568);
		}

		int a = 0;	// 적립률
		if (m_TotalMyMoney != 0)
		{
			a = (m_MyStatus[i] / m_TotalMyMoney) * 100;
		}

		CHTString strTemp1,strTemp2,strTemp3,strTemp4;
		g_cUIManager->HT_SetScriptMessage( eMsgYutExplainMoney1, &strTemp1, _T(""), _T("") );
		g_cUIManager->HT_SetScriptMessage( eMsgYutExplainMoney2, &strTemp2, _T(""), _T("") );
		g_cUIManager->HT_SetScriptMessage( eMsgYutExplainMoney3, &strTemp3, _T(""), _T("") );
		g_cUIManager->HT_SetScriptMessage( eMsgYutExplainMoney4, &strTemp4, _T(""), _T("") );
		sprintf(str, "[%d] %s:%d, %s:%3.1fx, %s:%d, %s:%d", i, strTemp1.HT_szGetString(), m_MyStatus[i], strTemp4.HT_szGetString(), g_fYutPercent[i], strTemp2.HT_szGetString(), m_AllStatus[i], strTemp3.HT_szGetString(), a);
		// (적립률 : 0, 보너스 : 3.0배, 내적립 : 0, 적립액 : 0)
		//sprintf(str, "[%d] 내적립:%d, 적립액:%d, 적립률:%d, 보너스:%3.1f배", i, m_MyStatus[i], m_AllStatus[i], a, g_fYutPercent[i] );
		g_cUIManager->HT_SetButtonToolTip(UI_WINDOW_GAMBLE, i+1, str);

		HTvector3 pos = g_cUIManager->HT_GetTextureControlPos(UI_WINDOW_GAMBLE, i+1);
	
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100),	72, (int)pos.x+4, (int)pos.y+21, 1561);	// 하 1
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100)+1, 72, (int)pos.x+11, (int)pos.y+21, 1562);// 하 2
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100)+2, 72, (int)pos.x+19, (int)pos.y+21, 1563);// 하 3
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100)+3, 72, (int)pos.x+9, (int)pos.y+14, 1564);	// 중 1
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100)+4, 72, (int)pos.x+16, (int)pos.y+14, 1565);// 중 2
		g_cUIManager->HT_AddTextureControl(UI_WINDOW_GAMBLE, ((i+1)*100)+5, 72, (int)pos.x+14, (int)pos.y+7, 1566);	// 상 1

		g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100), false);
		g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+1, false);
		g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+2, false);
		g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+3, false);
		g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+4, false);
		g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+5, false);

		// 누적 금액에 따라 금편량 출력
		if (m_AllStatus[i] > 0 && m_AllStatus[i] <= 10000L)
		{
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100), true);
		}
		else if (m_AllStatus[i] > 10000L && m_AllStatus[i] <= 50000L)
		{
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100), true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+1, true);
		}
		else if (m_AllStatus[i] > 50000L && m_AllStatus[i] <= 100000L)
		{
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100), true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+1, true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+2, true);
		}
		else if (m_AllStatus[i] > 100000L && m_AllStatus[i] <= 300000L)
		{
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100), true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+1, true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+2, true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+3, true);
		}
		else if (m_AllStatus[i] > 300000L && m_AllStatus[i] <= 500000L)
		{
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100), true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+1, true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+2, true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+3, true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+4, true);
		}
		else if (m_AllStatus[i] > 500000L)
		{
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100), true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+1, true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+2, true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+3, true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+4, true);
			g_cUIManager->HT_SetTextureControlDisplay(UI_WINDOW_GAMBLE, ((i+1)*100)+5, true);
		}
	}

	// 내적립액
	str = g_cUIManager->HT_strSetRestMark(m_TotalMyMoney);
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_GAMBLE, 1, str);

	// 총적립액
	str = g_cUIManager->HT_strSetRestMark(m_TotalAllMoney);
	g_cUIManager->HT_SetTextLabelControl(UI_WINDOW_GAMBLE, 2, str);
}

// 윈도우 제어 시도시 호출 (이곳에서 입력장치로부터 들어온 정보를 처리한다.)
void HTGamble::HT_hrGamble_InputCheck(int iAction, int iTarget, int iTargetID)
{ 
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:
		{
			if (iTargetID == -2) return;
			if (iTargetID == -1)	// 종료버튼 클릭시 창 닫음
			{
				g_cUIManager->HT_HideWindow(UI_WINDOW_GAMBLE);
				return;
			}

			if (iTargetID > 0 && iTargetID < 30) // 주춧돌판 버튼은 배팅을 시도하도록 한다.
			{
				CHTString strMessage2;
				g_cGamble->m_Position = iTargetID - 1;	// 버튼 인덱스보다 1 작다.
				g_cUIManager->HT_SetScriptMessage( eMsgYutExplain02, &strMessage2, _T(""), _T("") );
				g_cUIManager->HT_MessageBox(UI_WINDOW_GAMBLE, strMessage2, 2);
				break;
			}

			if (iTargetID == 30 )	// 새로고침 버튼 클릭시
				g_cGamble->HT_vNetWork_CSP_Req_YutMyMoney();
				//g_cGamble->HT_vNetWork_CSP_Req_YutStatus();		// 전체 배팅 정보 요청

			if (iTargetID == 31 ) // 당첨금 지급 버튼 클릭시
				g_cGamble->HT_vNetWork_CSP_Req_YutGetMoney();		// 당첨금 지급 요청
		}
		break;
	case UI_TARGET_MESSAGEBOX:
		{
			if (iTargetID <= 0) return;
/*
			// Step 2) 인벤토리를 조사해서 
			int iAddValue = 0;
			for (int i = 0; i < 48; ++i)  {g_cGamble->m_Count[i] = 0;}
			for (int i = 0; i < 48; ++i)
			{
				g_cGamble->m_Count[i] = g_cItemSystem->HT_bItemSystem_GetPossible2( GOLD_ITEM_ID, i );
				iAddValue += g_cGamble->m_Count[i];

				// 만약 입력 갯수보다 더 많은 금편이 들어왔다면, 현 인벤에서 오버한만큼을 뺀다.
				if (iAddValue >= iTargetID) 
				{
					g_cGamble->m_Count[i] -= (iAddValue - iTargetID);

					// Step 3) 서버로 배팅 요청을 시도한다. 
					g_cGamble->HT_vNetWork_CSP_Req_YutBet();
					// 자신의 배팅정보 요청
					g_cGamble->HT_vNetWork_CSP_Req_YutMyMoney();
					return;
				}
			}
*/

			// 배팅하기 위한 충분한 루피아가 있는지 조사 
			if (g_cEquipInventory->HT_iEquipInventory_GetPCMoney() >= iTargetID)
			{ 
				g_cGamble->m_nTotalRupia = iTargetID;

				// Step 3) 서버로 배팅 요청을 시도한다. 
				g_cGamble->HT_vNetWork_CSP_Req_YutBet();

				// 자신의 배팅정보 요청
				g_cGamble->HT_vNetWork_CSP_Req_YutMyMoney();
			}
			else
			{
				CHTString strMessage2;
				g_cUIManager->HT_SetScriptMessage( eMsgCommonServerMoreRupia, &strMessage2, _T(""), _T("") );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage2);
			}
		}
		break;
	}
}



//
// Network Functions (Public)
//

// 자신의 배팅 정보를 요청합니다.
HTvoid	HTGamble::HT_vNetWork_CSP_Req_YutMyMoney()
{
	Msg_YutMyMoney* info = new Msg_YutMyMoney;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_YutMyMoney ) );

	g_pNetWorkMgr->RequestMsgYutMyMoney( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_YutMyMoney Req Message...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// 전체 배팅 정보를 요청합니다.
HTvoid	HTGamble::HT_vNetWork_CSP_Req_YutStatus()
{
	Msg_YutStatus* info = new Msg_YutStatus;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_YutStatus ) );

	g_pNetWorkMgr->RequestMsgYutStatus( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_YutStatus Req Message...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// 배팅을 요청합니다.
HTvoid	HTGamble::HT_vNetWork_CSP_Req_YutBet()
{
	Msg_YutBet* info = new Msg_YutBet;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_YutBet ) );

	// 패킷 정보를 만들어서 배팅 요청을 보낸다.
	/*
	HTint iKeyID = 0, iTotalCount = 0;
	
	for (int i = 0; i < 48; ++i)
	{
		info->wCount[i] = m_Count[i];
		iTotalCount += g_cGamble->m_Count[i];
	}
	if (iTotalCount < 1) // 금편이 없다면...
	{
		CHTString strMessage;
		g_cUIManager->HT_SetScriptMessage( eMsgYutExplain02, &strMessage, _T(""), _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage );
	}
	*/

	info->iBetMoney = m_nTotalRupia;
	info->byPosition = m_Position;
	if (m_Position > 29) return;

	g_pNetWorkMgr->RequestMsgYutBet( info );
	
	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_YutBet req : Positon = %d, Gold = %d", info->byPosition, m_nTotalRupia);
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// 당첨금을 요청 합니다.
HTvoid	HTGamble::HT_vNetWork_CSP_Req_YutGetMoney()
{
	Msg_YutGetMoney* info = new Msg_YutGetMoney;
	if( info == HT_NULL ) return;
	ZeroMemory( info, sizeof( Msg_YutGetMoney ) );

	g_pNetWorkMgr->RequestMsgYutGetMoney( info );
	m_nTotalRupia = g_cEquipInventory->HT_iEquipInventory_GetPCMoney();

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_YutGetMoney req...");
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

// 자신의 배팅 정보를 받습니다. (YutMyMoney)
HTvoid HTGamble::HT_vGamble_NetWorkYutMyMoney( Msg_YutMyMoney* info )
{
	// 자신의 배팅 정보를 저장하고, 전체 배팅정보를 요청 합니다.
	m_TotalMyMoney = 0;
	for (int i = 0; i<YUT_MAX_NUMBER; ++i)
	{
		m_MyStatus[i] = info->dwPositionMoney[i];
		m_TotalMyMoney += m_MyStatus[i];
	}
	
	this->HT_vNetWork_CSP_Req_YutStatus();
}

// 모든 사람의 배팅 정보를 받습니다. (Msg_YutStatus)
HTvoid HTGamble::HT_vGamble_NetWorkYutStatus( Msg_YutStatus* info )
{
	// 전체 배팅정보를 저장하고 UI 정보 갱신후 화면에 출력합니다.
	m_TotalAllMoney = 0;
	for (int i = 0; i<YUT_MAX_NUMBER; ++i)
	{
		m_AllStatus[i] = info->dwPositionMoney[i];
		m_TotalAllMoney += m_AllStatus[i];
	}

	this->HT_vGamble_SetInfo();
	
	g_cUIManager->HT_ShowWindow(UI_WINDOW_GAMBLE);
}

// 배팅 결과를 받습니다. (Msg_YutBet)
HTvoid HTGamble::HT_vGamble_NetWorkYutBet( Msg_YutBet* info )
{
	// 성공시 모든 사람의 배팅정보 재요청하여 자동 갱신 한다.
	if (info->byResult == 0)
	{
		// 아이템 사용하는 소리가 난다.
		//g_pEngineHandler->HT_hrPlaySound( 33010, 1 );

		HTint iKeyID = 0, iTotalCount = 0;
		/*
		for (int i = 0; i < 48; ++i)
		{
			//g_cGamble->m_Count[i] = g_cItemSystem->HT_bItemSystem_GetPossible2( GOLD_ITEM_ID, i );
			//iTotalCount += g_cGamble->m_Count[i];

			// 아이템 KeyID 알아내서 삭제하기
			if (g_cGamble->m_Count[i] > 0 )
			{
				BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_INVEN, i, iKeyID );
				
				if(g_cGamble->m_Count[i] == g_cItemSystem->HT_bItemSystem_GetPossible2( GOLD_ITEM_ID, i ))
				{
					g_cItemSystem->HT_vItemSystem_DeleteItem( iKeyID );			// 아이템 삭제
				}
				else
				{
					g_cItemSystem->HT_vItemSystem_SetOverlapItemCount( iKeyID, (g_cItemSystem->HT_bItemSystem_GetPossible2( GOLD_ITEM_ID, i ) - g_cGamble->m_Count[i]) );
					break;
				}
			}
		}
		*/

		// 내 적립은 서버에 의존하지 않고 직접 계산한다.
		//g_cGamble->m_MyStatus[g_cGamble->m_Position] += iTotalCount;
		g_cGamble->m_MyStatus[g_cGamble->m_Position] += m_nTotalRupia;
		g_cEquipInventory->HT_vEquipInventory_SetPCMoney( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() - m_nTotalRupia);
		
		m_TotalMyMoney = 0;
		for (int i = 0; i<YUT_MAX_NUMBER; ++i) // 자신의 배팅 정보를 갱신합니다.
			m_TotalMyMoney += m_MyStatus[i];

		this->HT_vNetWork_CSP_Req_YutStatus();
		CHTString strMessage;
		g_cUIManager->HT_SetScriptMessage( eMsgYutExplain03, &strMessage, _T(""), _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		return;
	}
	else
	{
		// 실패시 에러메시지를 출력해준다. 여기선 임시로 창을 닫아버린다.
		CHTString strMessage;
		g_cUIManager->HT_SetScriptMessage( eMsgYutExplain04, &strMessage, _T(""), _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage );
		//g_cUIManager->HT_HideWindow(UI_WINDOW_GAMBLE);
	}
}

// 결과를 받습니다. 당첨금 받기
HTvoid HTGamble::HT_vGamble_NetWorkYutGetMoney( Msg_YutGetMoney* info )
{
	if (info->byResult == 0)
	{
		int giftmoney = info->iMoney - g_cEquipInventory->HT_iEquipInventory_GetPCMoney();

		CHTString strMessage, strMessage2;
		g_cUIManager->HT_SetScriptMessage( eMsgYutExplain05, &strMessage2, _T(""), _T("") );
		//g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		sprintf( strMessage, strMessage2, giftmoney );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
		g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->iMoney );
	}
	else
	{
		CHTString strMessage;
		g_cUIManager->HT_SetScriptMessage( eMsgYutExplain06, &strMessage, _T(""), _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage);
	}
}


//
// 그외 본 클래스 내에서만 쓰이는 함수들은 이곳에 작성합니다. (Private Type)
//


////////////////////////////////////////////////////////////////////
//
//					공성전
//
////////////////////////////////////////////////////////////////////
HTSiege::HTSiege(void)
{
	m_iGetMoneyType = 0;
	m_iGetMoneyAction = 0;
	m_iGetMoneyYut = 0;
}
HTSiege::~HTSiege(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGE1 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGE2 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGE3 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGE4 );
	
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGEHELP_1 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGEHELP_2 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGEHELP_3 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGEHELP_4 );
	
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGEJOININFO_0 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGEJOININFO_1 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGEJOININFO_2 );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SIEGEJOININFO_3 );
}

//	최초 촉기화
HTvoid HTSiege::HT_vSiege_Init()
{
	//	윈도우 생성
	this->HT_vSiege_CreateWindow();

	//	Brodcast Siege Time
	m_iSiege_SiegeTime = 1;
	//	Siege Ashram info, if 0 then empty
	for( HTint i=0 ; i<8 ; i++ )
        m_iSiege_GuildID[i] = 0;
	//	선택 아쉬람 정보창 페이지
	for( i=0 ; i<4 ; i++ )
	{
        m_iSiege_AshramWndPage[i] = 0;
		m_strSiege_Alliance[i].HT_hrCleanUp();
	}
	//	Castle Ashram ID
	m_iSiege_CastleAshramID = 0;
	//	세금 비율
	m_bySiege_MoneyRate = 0;
}
//	윈도우 생성
HTvoid HTSiege::HT_vSiege_CreateWindow()
{
	CHTString strMessage;
	CHTString strTemp;

	//	[Siege1_참가아쉬람]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGE1, _T(""), 330, 466, g_pSiege->HT_vSiege_InputCheckSiege1, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGE1, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE1, 1, 8, 3, 36, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE1, 2, 2, 3, 336, 1400, 323, 3 );
	//	Button 참가아쉬람
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE1, 1, 9, 29, 30, 0, 0, 1500, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeUnionAshram, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE1, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 29, 30, 90, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE1, 1 );
	//	Button 공성전상황
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE1, 2, 9, 119, 43, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeState, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE1, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 119, 43, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE1, 2 );
	//	Button 공성전선포
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE1, 3, 9, 183, 43, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeDeclare, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE1, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 183, 43, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE1, 3 );
	//	Button 비류성관리
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE1, 4, 9, 247, 43, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeCastleMgr, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE1, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 247, 43, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE1, 4 );
	//	Button 도움말
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE1, 5, 159, 17, 393, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeHelp, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE1, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 393, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE1, 5 );
	//	Button 수성 연맹
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE1, 6, 63, 65, 100, 65, 64, 1500, 224, 18 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeDefenseUnion, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE1, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 65, 100, 224, 18 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE1, 6 );
	//	Button 공성 연맹1
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 1 );
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE1, 7, 63, 65, 144, 65, 64, 1500, 224, 18 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE1, 7, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 65, 144, 224, 18 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE1, 7 );
	//	Button 공성 연맹2
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE1, 8, 63, 65, 188, 65, 64, 1500, 224, 18 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 2 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE1, 8, _T("공성 연맹2"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 65, 188, 224, 18 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE1, 8 );
	//	Button 공성 연맹3
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE1, 9, 63, 65, 232, 65, 64, 1500, 224, 18 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 3 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE1, 9, _T("공성 연맹3"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 65, 232, 224, 18 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE1, 9 );
	//	Button 무소속 연합
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE1, 10, 63, 65, 277, 65, 64, 1500, 224, 18 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeEmptyUnion, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE1, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 65, 277, 224, 18 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE1, 10 );
	//	Imgae Loop
	for( HTint i=0 ; i<5 ; i++ )
	{
		g_cUIManager->HT_AddSlotBoxControl( _DIALOG_SIEGE1, 1+i, 66, 17, 92+(46*i) );
		g_cUIManager->HT_SetSlotBoxImageFixed( _DIALOG_SIEGE1, 1+i, HT_TRUE );
		g_cUIManager->HT_SetSlotImage( _DIALOG_SIEGE1, 1+i, g_iSiegeUnionMark[i] );
		g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_SIEGE1, 1+i, 2, 2 );
	}

	//	[Siege2_공성전 상황]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGE2, _T(""), 330, 466, g_pSiege->HT_vSiege_InputCheckSiege2, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGE2, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE2, 1, 8, 3, 36, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE2, 2, 2, 3, 336, 1400, 323, 3 );
	//	Button 참가아쉬람
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE2, 1, 9, 29, 43, 0, 0, 1500, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeUnionAshram, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE2, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 29, 43, 90, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE2, 1 );
	//	Button 공성전상황
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE2, 2, 9, 119, 30, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeState, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE2, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 119, 30, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE2, 2 );
	//	Button 공성전선포
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE2, 3, 9, 183, 43, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeDeclare, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE2, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 183, 43, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE2, 3 );
	//	Button 비류성관리
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE2, 4, 9, 247, 43, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE2, 4, eMsgSiegeCastleMgr, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 247, 43, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE2, 4 );
	//	Button 새로고침
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE2, 6, 159, 29, 345, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonReFresh, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE2, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 29, 345, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE2, 6 );
	//	Image 지도
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE2, 3, 81, 37, 68 );
	for( HTint i=0 ; i<11 ;i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE2, 10+i, 0, 0, 0 );
	}
	//	점수표시, 수서, 공성1, 공성2, 공성3
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeScoreDefenseUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 0 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE2, 10, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 29, 370, 270, 15 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGE2, 10,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeScoreAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 0 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE2, 11, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 29, 385, 270, 15 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGE2, 11,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeScoreAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 0 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE2, 12, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 29, 400, 270, 15 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGE2, 12,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeScoreAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 0 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE2, 13, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 29, 415, 270, 15 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGE2, 13,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeScoreEmptyUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 0 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE2, 14, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 29, 430, 270, 15 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGE2, 14,  7 );

	//	[Siege3_공성전 선포]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGE3, _T(""), 330, 466, g_pSiege->HT_vSiege_InputCheckSiege3, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGE3, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE3, 1, 8, 3, 36, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE3, 2, 2, 3, 336, 1400, 323, 3 );
	//	Button 참가아쉬람
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE3, 1, 9, 29, 43, 0, 0, 1500, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeUnionAshram, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 29, 43, 90, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE3, 1 );
	//	Button 공성전상황
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE3, 2, 9, 119, 43, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeState, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 119, 43, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE3, 2 );
	//	Button 공성전선포
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE3, 3, 9, 183, 30, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeDeclare, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 183, 30, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE3, 3 );
	//	Button 비류성관리
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE3, 4, 9, 247, 43, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeCastleMgr, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 247, 43, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE3, 4 );
	//	Button 공성전선포
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE3, 5, 159, 28, 297, 160, 161, 1500, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeDeclare, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 297, 90, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE3, 5 );
	//	Button 금요일 저녁 8시
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE3, 6, 63, 28, 157, 65, 64, 1500, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeFriEve8, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 157, 152, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE3, 6 );
	//	Button 금요일 저녁 10시
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE3, 7, 63, 28, 182, 65, 64, 1500, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeFriEve10, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 182, 152, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE3, 7 );
	//	Button 토요일 저녁 8시
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE3, 8, 63, 28, 207, 65, 64, 1500, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSatEve8, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 8, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 207, 152, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE3, 8 );
	//	Button 토요일 저녁 10시
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE3, 9, 63, 28, 233, 65, 64, 1500, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSatEve10, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 9, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 233, 152, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE3, 9 );
	//	Button 일요일 저녁 8시
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE3, 10, 63, 28, 259, 65, 64, 1500, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSunEve8, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 28, 259, 152, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE3, 10 );
	//	Label
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain01, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 27, 73, 290, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGE3, 20,  7 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain02, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 21, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 27, 109, 290, 50 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGE3, 21,  7 );
	//	Button 시간 문의
	//g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE3, 11, 63, 135, 297, 65, 64, 1500, 90, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 11, _T("시간 문의"), 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 135, 297, 90, 19 );
	//g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE3, 11 );
	//	시간 알려줌
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE3, 12, 9, 70, 370, 1400, 200, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSatEve10, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE3, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 70, 370, 200, 19 );

	//	[Siege4_비류성 관리]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGE4, _T(""), 330, 466, g_pSiege->HT_vSiege_InputCheckSiege4, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGE4, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE4, 1, 8, 3, 36, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE4, 2, 2, 3, 336, 1400, 323, 3 );
	//	Button 참가아쉬람
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE4, 1, 9, 29, 43, 0, 0, 1500, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeUnionAshram, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 29, 43, 90, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE4, 1 );
	//	Button 공성전상황
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE4, 2, 9, 119, 43, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeState, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 119, 43, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE4, 2 );
	//	Button 공성전선포
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE4, 3, 9, 183, 43, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeDeclare, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 183, 43, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE4, 3 );
	//	Button 비류성관리
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE4, 4, 9, 247, 30, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeCastleMgr, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 247, 30, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE4, 4 );
	//	Button 적용
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE4, 5, 99, 247, 170, 97, 98, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeApply, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 247, 170, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE4, 5 );
	//	Button 회수
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE4, 6, 99, 247, 202, 97, 98, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeCollect, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 247, 202, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE4, 6 );

	//	Only Label
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain03, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 90, 300, 40 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGE4, 7, 7 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeChageRate, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 7, 170, 80, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeCollectRate, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 7, 270, 80, 19 );
	//g_cUIManager->HT_SetScriptMessage( eMsgSiegeTrustShopRate, &strMessage, _T(""), _T("") );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 7, 230, 80, 19 );
	//	Only Label 루피아
	g_cUIManager->HT_SetScriptMessage( eMsgItemInfoPrice, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 0 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 8, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 120, 200, 100, 19 );
	//	Scroll 세율변경
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 9, _T("%"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 140, 145, 50, 19 );
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_SIEGE4, 0, 80, 170, 160, 100, 1 );
	////	Button 비율문의
	//g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE4, 10, 99, 247, 180, 97, 98, 1500, 64, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 10, _T("비율문의"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 247, 180, 64, 19 );
	//g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE4, 10 );
	//	Scroll 위탁상점 세율
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 11, _T("%"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 140, 220, 50, 19 );
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_SIEGE4, 1, 80, 230, 160, 7, 1 );
	//	Button 적용
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE4, 12, 99, 247, 230, 97, 98, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeApply, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 247, 230, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE4, 12 );
	//	Button 회수
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGE4, 13, 99, 247, 270, 97, 98, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeCollect, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 247, 270, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGE4, 13 );
	// 루피아
	g_cUIManager->HT_SetScriptMessage( eMsgItemInfoPrice, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 0 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGE4, 14, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 120, 270, 100, 19 );

	//	[Siege_아쉬람별 연맹 아쉬람 리스트0]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGEJOININFO_0, _T(""), 330, 466, g_pSiege->HT_vSiege_InputCheckJoinInfo0, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGEJOININFO_0, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_0, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button 참가아쉬람
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_0, 1, 9, 39, 30, 0, 0, 1500, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeInfoDefenseUnion, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_0, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_0, 1 );
	//	Button 뒤로
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_0, 2, 159, 17, 415, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeNextPage, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_0, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 415, 79, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_0, 2 );
	//	Page No
	g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 0 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_0, 3, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 110, 415, 100, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_0, 3,  7 );
	//	연맹 이름
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeDefenseUnion, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_0, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 66, 200, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_0, 4, 7 );
	//	Button 새로고침
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_0, 5, 159, 225, 415, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonReFresh, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_0, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 415, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_0, 5 );
	//	Loop
	for( i=0 ; i<8 ; i++ )
	{
		//	아쉬람 명
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_0, 0, 66, 17, 91+(39*i) );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_0, 10+(i*3), 0, 17, 91+(39*i),1401 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_0, 11+(i*3), 0, 17, 91+(39*i),1402 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_0, 12+(i*3), 0, 25, 99+(39*i),1403 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_0, 0, 9, 65, 99+(39*i), 1400, 152, 19 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_0, 10+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 67, 100+(39*i), 152, 19 );
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_0, 10+i,  7 );
		//	Button 연맹가입
		//	짝수일때만 연맹가입창을 뛰어준다.
		if( i%2 == 0 )
		{
			g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_0, 10+i, 159, 225, 99+(39*i), 160, 161, 1500, 64, 19 );
			g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_0, 10+i );
			if( i == 0 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgCommadAutoJoin, &strMessage, _T(""), _T("") );//	자동가입
				g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_0, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 99+(39*i), 64, 19 );
			}
			else
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeJoinUnion, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_0, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 99+(39*i), 64, 19 );
			}
		}
	}
	//	[Siege_아쉬람별 연맹 아쉬람 리스트1]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGEJOININFO_1, _T(""), 330, 466, g_pSiege->HT_vSiege_InputCheckJoinInfo1, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGEJOININFO_1, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_1, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button 참가아쉬람
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_1, 1, 9, 39, 30, 0, 0, 1500, 100, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeInfoAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 1 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_1, 1, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 100, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_1, 1 );
	//	Button 뒤로
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_1, 2, 159, 17, 415, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeNextPage, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_1, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 415, 79, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_1, 2 );
	//	Page No
	g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 0 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_1, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 110, 415, 100, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_1, 3,  7 );
	//	연맹 이름
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 1 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_1, 4, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 66, 200, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_1, 4, 7 );
	//	Button 새로고침
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_1, 5, 159, 225, 415, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonReFresh, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_1, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 415, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_1, 5 );
	//	Loop
	for( i=0 ; i<8 ; i++ )
	{
		//	아쉬람 명
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_1, 0, 66, 17, 91+(39*i) );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_1, 10+(i*3), 0, 17, 91+(39*i),1401 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_1, 11+(i*3), 0, 17, 91+(39*i),1402 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_1, 12+(i*3), 0, 25, 99+(39*i),1403 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_1, 0, 9, 65, 99+(39*i), 1400, 152, 19 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_1, 10+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 67, 100+(39*i), 152, 19 );
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_1, 10+i,  7 );
		//	Button 연맹가입
		//	짝수일때만 연맹가입창을 뛰어준다.
		if( i%2 == 0 )
		{
			g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_1, 10+i, 159, 225, 99+(39*i), 160, 161, 1500, 64, 19 );
			g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_1, 10+i );
			if( i == 0 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeRequestUnionMaster, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_1, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 99+(39*i), 64, 19 );
			}
			else
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeJoinUnion, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_1, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 99+(39*i), 64, 19 );
			}
		}
	}
	//	[Siege_아쉬람별 연맹 아쉬람 리스트2]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGEJOININFO_2, _T(""), 330, 466, g_pSiege->HT_vSiege_InputCheckJoinInfo2, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGEJOININFO_2, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_2, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button 참가아쉬람
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_2, 1, 9, 39, 30, 0, 0, 1500, 100, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeInfoAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 2 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_2, 1, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 100, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_2, 1 );
	//	Button 뒤로
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_2, 2, 159, 17, 415, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeNextPage, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_2, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 415, 79, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_2, 2 );
	//	Page No
	g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 0 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_2, 3, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 110, 415, 100, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_2, 3,  7 );
	//	연맹 이름
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 2 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_2, 4, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 66, 200, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_2, 4, 7 );
	//	Button 새로고침
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_2, 5, 159, 225, 415, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonReFresh, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_2, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 415, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_2, 5 );
	//	Loop
	for( i=0 ; i<8 ; i++ )
	{
		//	아쉬람 명
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_2, 0, 66, 17, 91+(39*i) );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_2, 10+(i*3), 0, 17, 91+(39*i),1401 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_2, 11+(i*3), 0, 17, 91+(39*i),1402 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_2, 12+(i*3), 0, 25, 99+(39*i),1403 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_2, 0, 9, 65, 99+(39*i), 1400, 152, 19 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_2, 10+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 67, 100+(39*i), 152, 19 );
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_2, 10+i,  7 );
		//	Button 연맹가입
		//	짝수일때만 연맹가입창을 뛰어준다.
		if( i%2 == 0 )
		{
			g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_2, 10+i, 159, 225, 99+(39*i), 160, 161, 1500, 64, 19 );
			g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_2, 10+i );
			if( i == 0 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeRequestUnionMaster, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_2, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 99+(39*i), 64, 19 );
			}
			else
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeJoinUnion, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_2, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 99+(39*i), 64, 19 );
			}
		}
	}
	//	[Siege_아쉬람별 연맹 아쉬람 리스트3]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGEJOININFO_3, _T(""), 330, 466, g_pSiege->HT_vSiege_InputCheckJoinInfo3, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGEJOININFO_3, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_3, 1, 8, 3, 36, 1400, 323, 6 );
	//	Button 참가아쉬람
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_3, 1, 9, 39, 30, 0, 0, 1500, 100, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeInfoAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 3 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_3, 1, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 100, 17 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_3, 1 );
	//	Button 뒤로
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_3, 2, 159, 17, 415, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeNextPage, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_3, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 415, 79, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_3, 2 );
	//	Page No
	g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 0 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_3, 3, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 110, 415, 100, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_3, 3,  7 );
	//	연맹 이름
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeAttackUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, 3 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_3, 4, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 66, 200, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_3, 4, 7 );
	//	Button 새로고침
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_3, 5, 159, 225, 415, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonReFresh, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_3, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 415, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_3, 5 );
	//	Loop
	for( i=0 ; i<8 ; i++ )
	{
		//	아쉬람 명
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_3, 0, 66, 17, 91+(39*i) );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_3, 10+(i*3), 0, 17, 91+(39*i),1401 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_3, 11+(i*3), 0, 17, 91+(39*i),1402 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_3, 12+(i*3), 0, 25, 99+(39*i),1403 );
		g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEJOININFO_3, 0, 9, 65, 99+(39*i), 1400, 152, 19 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_3, 10+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 67, 100+(39*i), 152, 19 );
		g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEJOININFO_3, 10+i,  7 );
		//	Button 연맹가입
		//	짝수일때만 연맹가입창을 뛰어준다.
		if( i%2 == 0 )
		{
			g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEJOININFO_3, 10+i, 159, 225, 99+(39*i), 160, 161, 1500, 64, 19 );
			g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEJOININFO_3, 10+i );
			if( i == 0 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeRequestUnionMaster, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_3, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 99+(39*i), 64, 19 );
			}
			else
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeJoinUnion, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEJOININFO_3, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 225, 99+(39*i), 64, 19 );
			}
		}
	}

	//	[_DIALOG_SIEGEHELP_1]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGEHELP_1, _T(""), 329, 465, g_pSiege->HT_vSiege_InputCheckHelp1, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGEHELP_1, 5 );
	//	줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEHELP_1, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button 공성신청
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_1, 1, 9, 17, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeRequestSiege, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_1, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_1, 1 );
	//	Button 공성아이템
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_1, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeItem, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_1, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_1, 2 );
	//	Button 공성전승자
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_1, 3, 9, 169, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeWiner, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_1, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_1, 3 );
	//	Button 성주의권한
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_1, 4, 9, 245, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeRightCastleMaster, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_SIEGEHELP_1, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_1, 4 );
	//	Title1
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain04, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_1, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 85, 250, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEHELP_1, 10,  7 );
	//	explain1
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain05, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_SIEGEHELP_1, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 110, 250, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_SIEGEHELP_1, 11, 7 );
	//	Title2
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain06, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_1, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 220, 250, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEHELP_1, 12,  7 );
	//	explain2
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain07, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_SIEGEHELP_1, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 245, 250, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_SIEGEHELP_1, 13, 7 );

	//	[_DIALOG_SIEGEHELP_2]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGEHELP_2, _T(""), 329, 465, g_pSiege->HT_vSiege_InputCheckHelp2, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGEHELP_2, 5 );
	//	줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEHELP_2, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button 공성신청
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_2, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeRequestSiege, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_2, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_2, 1 );
	//	Button 공성아이템
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_2, 2, 9, 93, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeItem, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_2, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_2, 2 );
	//	Button 공성전승자
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_2, 3, 9, 169, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeWiner, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_2, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_2, 3 );
	//	Button 성주의권한
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_2, 4, 9, 245, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeRightCastleMaster, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_2, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_2, 4 );
	//	Title1	//	공성전 아이템 아디즈
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain12, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_2, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 85, 250, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEHELP_2, 10,  7 );
	//	explain1
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain13, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_SIEGEHELP_2, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 110, 250, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_SIEGEHELP_2, 11, 7 );
	//	explain2
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain14, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_SIEGEHELP_2, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 225, 250, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_SIEGEHELP_2, 12, 7 );

	//	[_DIALOG_SIEGEHELP_3]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGEHELP_3, _T(""), 329, 465, g_pSiege->HT_vSiege_InputCheckHelp3, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGEHELP_3, 5 );
	//	줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEHELP_3, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button 공성신청
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_3, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeRequestSiege, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_3, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_3, 1 );
	//	Button 공성아이템
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_3, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeItem, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_3, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_3, 2 );
	//	Button 공성전승자
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_3, 3, 9, 169, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeWiner, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_3, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_3, 3 );
	//	Button 성주의권한
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_3, 4, 9, 245, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeRightCastleMaster, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_3, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_3, 4 );
	//	Title1
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain15, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_3, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 85, 250, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEHELP_3, 10,  7 );
	//	explain1
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain16, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_SIEGEHELP_3, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 110, 250, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_SIEGEHELP_3, 11, 7 );
	//	Title2
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain17, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_3, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 220, 250, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEHELP_3, 12,  7 );
	//	explain2
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain18, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_SIEGEHELP_3, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 245, 250, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_SIEGEHELP_3, 13, 7 );

    //	[_DIALOG_SIEGEHELP_4]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SIEGEHELP_4, _T(""), 329, 465, g_pSiege->HT_vSiege_InputCheckHelp4, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SIEGEHELP_4, 5 );
	//	줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGEHELP_4, 0, 8, 3, 36, 1400, 323, 6 );
	//	Button 공성신청
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_4, 1, 9, 17, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeRequestSiege, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_4, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 17, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_4, 1 );
	//	Button 공성아이템
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_4, 2, 9, 93, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeItem, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_4, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 93, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_4, 2 );
	//	Button 공성전승자
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_4, 3, 9, 169, 43, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeWiner, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_4, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 169, 43, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_4, 3 );
	//	Button 성주의권한
	g_cUIManager->HT_AddButtonControl( _DIALOG_SIEGEHELP_4, 4, 9, 245, 30, 0, 0, 1500, 75, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeRightCastleMaster, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_4, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 245, 30, 75, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SIEGEHELP_4, 4 );
	//	Title1
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain19, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_4, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 85, 250, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEHELP_4, 10,  7 );
	//	explain1
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain20, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_SIEGEHELP_4, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 110, 250, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_SIEGEHELP_4, 11, 7 );
	//	Title2
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain21, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SIEGEHELP_4, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,0.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 220, 250, 19 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_SIEGEHELP_4, 12,  7 );
	//	explain2
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain22, &strMessage, _T(""), _T("") );
	g_cUIManager->HT_AddLongLabelControl( _DIALOG_SIEGEHELP_4, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 35, 245, 250, 80 );
	g_cUIManager->HT_SetArrangementLongLabelControl( _DIALOG_SIEGEHELP_4, 13, 7 );
}
//	입력함수 처리 참가아쉬람
void HTSiege::HT_vSiege_InputCheckSiege1(int iAction, int iTarget, int iTargetID)
{
    if( iTarget == UI_TARGET_BUTTON )
	{
		CHTString strMessage;
		CHTString strTemp;

		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_SIEGE1, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE1);
		}
		//	Button 공성전상황
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE1);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE2);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE2, iPosX, iPosY );
			//	CSP State of the siege
			g_pSiege->HT_vSiege_NetworkCSPStateOfTheSiege();
		}
		//	Button 공성전선포
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE1);
			//	Brodcast Siege Time
			g_pSiege->m_iSiege_SiegeTime = 1;
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE3);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE3, iPosX, iPosY );
			//	공성전 시간확인
			g_pSiege->HT_vSiege_NetworkCSP_FixDataOfSiege( 0, 0 );
		}
		//	Button 비류성관리
		else if( iTargetID == 4 )
		{
			if( g_pSiege->HT_vSiege_GetOwerOfCastle() &&  g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_MAHARAJA || g_oMainCharacterInfo.snTribe == 0x09 )
			{
				g_cUIManager->HT_HideWindow(_DIALOG_SIEGE1);
				g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE4);
				g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE4, iPosX, iPosY );
				//	세율 문의
				g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );
				g_cRentalStore->HT_RequestRentalTex(1);

				// 적립된 루피아 문의
				g_pSiege->m_iGetMoneyType = 3;	// 상점에 있는 세금 회수
				g_pSiege->m_iGetMoneyAction = 1;	// 찾기 요청
				g_pSiege->HT_vSiege_NetworkCSP_GetMoney();
			}
		}
		//	Button 도우말
		else if( iTargetID == 5 )
		{
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_1);
		}
		//	Button 수성연맹1
		else if( iTargetID == 6 )
		{
			if( !g_cUIManager->HT_isShowWindow( _DIALOG_SIEGEJOININFO_0 ) )
                g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEJOININFO_0);
			//	선택 아쉬람 정보창 페이지
			g_pSiege->m_iSiege_AshramWndPage[0] = 0;
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 0, 0 );
			//	Page No
			g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
			strTemp.HT_szFormat( strMessage, 0 );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_0, 3, strTemp );
		}
		//	Button 공성연맹1
		else if( iTargetID == 7 )
		{
			if( !g_cUIManager->HT_isShowWindow( _DIALOG_SIEGEJOININFO_1 ) )
				g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEJOININFO_1);
			//	선택 아쉬람 정보창 페이지
			g_pSiege->m_iSiege_AshramWndPage[1] = 0;
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 1, 0 );
			//	Page No
			g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
			strTemp.HT_szFormat( strMessage, 0 );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_1, 3, strTemp );
		}
		//	Button 공성연맹2
		else if( iTargetID == 8 )
		{
			if( !g_cUIManager->HT_isShowWindow( _DIALOG_SIEGEJOININFO_2 ) )
				g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEJOININFO_2);
			//g_cUIManager->HT_HideWindow(_DIALOG_SIEGE1);
			//	선택 아쉬람 정보창 페이지
			g_pSiege->m_iSiege_AshramWndPage[2] = 0;
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 2, 0 );
			//	Page No
			g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
			strTemp.HT_szFormat( strMessage, 0 );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_2, 3, strTemp );
		}
		//	Button 공성연맹3
		else if( iTargetID == 9 )
		{
			if( !g_cUIManager->HT_isShowWindow( _DIALOG_SIEGEJOININFO_3 ) )
				g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEJOININFO_3);
			//	선택 아쉬람 정보창 페이지
			g_pSiege->m_iSiege_AshramWndPage[3] = 0;
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 3, 0 );
			//	Page No
			g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
			strTemp.HT_szFormat( strMessage, 0 );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_3, 3, strTemp );
		}
		//	Button 무소속 연합
		//else if( iTargetID == 10 )
	}
}
//	입력함수 처리 공성전상황
void HTSiege::HT_vSiege_InputCheckSiege2(int iAction, int iTarget, int iTargetID)
{
    if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_SIEGE2, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE2);
		}
		//	Button 참가아쉬람
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE2);
            g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE1);
            g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE1, iPosX, iPosY );
			//	참가 아쉬람 정보 신청
			g_pSiege->HT_vSiege_RequestJoinAshramInfo();
		}
		//	Button 공성전선포
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE2);
			//	Brodcast Siege Time
			g_pSiege->m_iSiege_SiegeTime = 1;
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE3);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE3, iPosX, iPosY );
			//	공성전 시간확인
			g_pSiege->HT_vSiege_NetworkCSP_FixDataOfSiege( 0, 0 );
		}
		//	Button 비류성관리
		else if( iTargetID == 4 )
		{
			if( g_pSiege->HT_vSiege_GetOwerOfCastle() && g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_MAHARAJA || g_oMainCharacterInfo.snTribe == 0x09 )
			{
				g_cUIManager->HT_HideWindow(_DIALOG_SIEGE2);
				g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE4);
				g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE4, iPosX, iPosY );
				//	세율 문의
				g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );

				// 적립된 루피아 문의
				g_pSiege->m_iGetMoneyType = 3;	// 상점에 있는 세금 회수
				g_pSiege->m_iGetMoneyAction = 1;	// 찾기 요청
				g_pSiege->HT_vSiege_NetworkCSP_GetMoney();
			}
		}
		//	Button 도움말
		else if( iTargetID == 5 )
		{
		}
		//	Button 새로고침
		else if( iTargetID == 6 )
		{
			//	CSP State of the siege
			g_pSiege->HT_vSiege_NetworkCSPStateOfTheSiege();
		}
	}
}
//	입력함수 처리 공성전선포
void HTSiege::HT_vSiege_InputCheckSiege3(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_SIEGE3, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE3);
		}
		//	Button 참가아쉬람
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE3);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE1);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE1, iPosX, iPosY );
			//	참가 아쉬람 정보 신청
			g_pSiege->HT_vSiege_RequestJoinAshramInfo();
		}
		//	Button 공성전상황
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE3);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE2);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE2, iPosX, iPosY );
			//	CSP State of the siege
			g_pSiege->HT_vSiege_NetworkCSPStateOfTheSiege();
		}
		//	Button 비류성관리
		else if( iTargetID == 4 )
		{
			if( g_pSiege->HT_vSiege_GetOwerOfCastle() && g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_MAHARAJA || g_oMainCharacterInfo.snTribe == 0x09 )
			{
				g_cUIManager->HT_HideWindow(_DIALOG_SIEGE3);
				g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE4);
				g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE4, iPosX, iPosY );
				//	세율 문의
				g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );
				g_cRentalStore->HT_RequestRentalTex(1);
				// 적립된 루피아 문의
				g_pSiege->m_iGetMoneyType = 3;	// 상점에 있는 세금 회수
				g_pSiege->m_iGetMoneyAction = 1;	// 찾기 요청
				g_pSiege->HT_vSiege_NetworkCSP_GetMoney();
			}
		}
		//	Button 공성전 선포
		else if( iTargetID == 5 )
		{
			g_pSiege->HT_vSiege_NetworkCSP_FixDataOfSiege( 1, g_pSiege->m_iSiege_SiegeTime );
		}
		////	Button 공성전 시간 확인
		//else if( iTargetID == 11 )
		//{
		//	g_pSiege->HT_vSiege_NetworkCSP_FixDataOfSiege( 0, 0 );
		//}
		//	Button 공성전 날짜 셋팅
		else if( iTargetID>=6 && iTargetID<=10 )
		{
			g_pSiege->m_iSiege_SiegeTime = iTargetID-5;
		}
	}
}
//	입력함수 처리 비류성관리
void HTSiege::HT_vSiege_InputCheckSiege4(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_SIEGE4, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE4);
		}
		//	Button 참가아쉬람
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE4);

			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE1);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE1, iPosX, iPosY );
			//	참가 아쉬람 정보 신청
			g_pSiege->HT_vSiege_RequestJoinAshramInfo();
		}
		//	Button 공성전상황
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE4);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE2);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE2, iPosX, iPosY );
			//	CSP State of the siege
			g_pSiege->HT_vSiege_NetworkCSPStateOfTheSiege();
		}
		//	Button 공성전선포
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGE4);
			//	Brodcast Siege Time
			g_pSiege->m_iSiege_SiegeTime = 1;
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE3);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGE3, iPosX, iPosY );
			//	공성전 시간확인
			g_pSiege->HT_vSiege_NetworkCSP_FixDataOfSiege( 0, 0 );
		}
		//	Button 세금 비율 적용
		else if( iTargetID == 5 )
		{
			g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 2, g_cUIManager->HT_GetScrollBarValue( _DIALOG_SIEGE4, 0 ) );
		}
		//	Button 세금 회수
		else if( iTargetID == 6 )
		{
			g_pSiege->m_iGetMoneyType = 2;	// 상점에 있는 세금 회수
			g_pSiege->m_iGetMoneyAction = 2;	// 찾기 요청
			g_pSiege->HT_vSiege_NetworkCSP_GetMoney();
		}
		//	Button 비율 문의
		else if( iTargetID == 10 )
		{
			g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );
		}
		//	세율 변경
		else if( iTargetID == 12 )
		{
			//g_pSiege->HT_vSiege_NetworkCSP_SetSalesRate( 1, 0 );
			g_cRentalStore->m_iTex = g_cUIManager->HT_GetScrollBarValue( _DIALOG_SIEGE4, 1 );
			g_cRentalStore->HT_RequestRentalTex(2);
		}
		//	세금 회수
		else if( iTargetID == 13 )
		{
			g_pSiege->m_iGetMoneyType = 3;	// 상점에 있는 세금 회수
			g_pSiege->m_iGetMoneyAction = 2;	// 찾기 요청
			g_pSiege->HT_vSiege_NetworkCSP_GetMoney();
		}
	}
	else if( iTarget == UI_TARGET_SCROLLBAR )
	{
		if (iTargetID == 0)
		{
			CHTString strTemp;
			HTint iRate = g_cUIManager->HT_GetScrollBarValue( _DIALOG_SIEGE4, 0 );
			strTemp.HT_szFormat( "%d %%", iRate );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE4, 9, strTemp.HT_szGetString() );
		}
		else if (iTargetID == 1)
		{
			CHTString strTemp;
			HTint iRate = g_cUIManager->HT_GetScrollBarValue( _DIALOG_SIEGE4, 1 );
			strTemp.HT_szFormat( "%d %%", iRate );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE4, 11, strTemp.HT_szGetString() );
		}
	}
}
//	입력함수 처리 선택 아쉬람 정보0
void HTSiege::HT_vSiege_InputCheckJoinInfo0(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEJOININFO_0);
		}
		//	뒤로
		else if( iTargetID == 2 )
		{
			//	선택 아쉬람 정보창 페이지
			g_pSiege->m_iSiege_AshramWndPage[0]++;
			if( g_pSiege->m_iSiege_AshramWndPage[0] == 5 )
				g_pSiege->m_iSiege_AshramWndPage[0] = 0;
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 0, g_pSiege->m_iSiege_AshramWndPage[0] );
			CHTString strTemp;
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
			strTemp.HT_szFormat( strMessage, g_pSiege->m_iSiege_AshramWndPage[0] );
			//	Page No
            g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_0, 3, strTemp.HT_szGetString() );
			//	이름 바꿈
			if( g_pSiege->m_iSiege_AshramWndPage[0] == 0 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgCommadAutoJoin, &strMessage, _T(""), _T("") );//	자동가입
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_0, 20, strMessage );
			}
			else
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeJoinUnion, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_0, 20, strMessage );
			}
		}
		//	새로고침
		else if( iTargetID == 5 )
		{
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 0, g_pSiege->m_iSiege_AshramWndPage[0] );
		}
		//	연맹가입
		else if( iTargetID>=10 && iTargetID<=18 )
		{
			//	연맹장이 있는지 체크
			if( g_pSiege->m_iSiege_AshramWndPage[0] == 0 )
			{
				if( iTargetID == 10 )
					return;
				CHTString strTemp = g_cUIManager->HT_GetTextLabelControl( _DIALOG_SIEGEJOININFO_0, 10 );
				if( strTemp.HT_bIsEmpty() )
					return;
			}

			//	마하라자만이 사용할수 있다.
			if( g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_MAHARAJA ||
				g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_RAJA )
			{
				g_pSiege->HT_vSiege_NetworkApplySiege( 0, iTargetID-10 );
			}
		}
	}
}
//	입력함수 처리 선택 아쉬람 정보1
void HTSiege::HT_vSiege_InputCheckJoinInfo1(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEJOININFO_1);
		}
		//	뒤로
		else if( iTargetID == 2 )
		{
			//	선택 아쉬람 정보창 페이지
			g_pSiege->m_iSiege_AshramWndPage[1]++;
			if( g_pSiege->m_iSiege_AshramWndPage[1] == 5 )
				g_pSiege->m_iSiege_AshramWndPage[1] = 0;
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 1, g_pSiege->m_iSiege_AshramWndPage[1] );
			CHTString strTemp;
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
			strTemp.HT_szFormat( strMessage, g_pSiege->m_iSiege_AshramWndPage[1] );
			//	Page No
            g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_1, 3, strTemp.HT_szGetString() );
			//	이름 바꿈
			if( g_pSiege->m_iSiege_AshramWndPage[1] == 0 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeRequestUnionMaster, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_1, 20, strMessage );
			}
			else
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeJoinUnion, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_1, 20, strMessage );
			}
		}
		//	새로고침
		else if( iTargetID == 5 )
		{
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 1, g_pSiege->m_iSiege_AshramWndPage[1] );
		}
		//	연맹가입
		else if( iTargetID>=10 && iTargetID<=18 )
		{
			//	연맹장이 있는지 체크
			if( g_pSiege->m_iSiege_AshramWndPage[1] == 0 )
			{
				if( iTargetID > 10 )
				{
					CHTString strTemp = g_cUIManager->HT_GetTextLabelControl( _DIALOG_SIEGEJOININFO_1, 10 );
					if( strTemp.HT_bIsEmpty() )
						return;
				}
			}

			//	마하라자만이 사용할수 있다.
			if( g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_MAHARAJA ||
				g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_RAJA )
			{
				//CHTString strTemp = g_cUIManager->HT_GetTextLabelControl( _DIALOG_SIEGEJOININFO_1, 10 );
				//if( !strTemp.HT_bIsEmpty() )
                    g_pSiege->HT_vSiege_NetworkApplySiege( 1, iTargetID-10 );
			}
		}
	}
}
//	입력함수 처리 선택 아쉬람 정보2
void HTSiege::HT_vSiege_InputCheckJoinInfo2(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEJOININFO_2);
		}
		//	뒤로
		else if( iTargetID == 2 )
		{
			//	선택 아쉬람 정보창 페이지
			g_pSiege->m_iSiege_AshramWndPage[2]++;
			if( g_pSiege->m_iSiege_AshramWndPage[2] == 5 )
				g_pSiege->m_iSiege_AshramWndPage[2] = 0;
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 2, g_pSiege->m_iSiege_AshramWndPage[2] );
			CHTString strTemp;
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
			strTemp.HT_szFormat( strMessage, g_pSiege->m_iSiege_AshramWndPage[2] );
			//	Page No
            g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_2, 3, strTemp.HT_szGetString() );
			//	이름 바꿈
			if( g_pSiege->m_iSiege_AshramWndPage[2] == 0 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeRequestUnionMaster, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_2, 20, strMessage );
			}
			else
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeJoinUnion, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_2, 20, strMessage );
			}
		}
		//	새로고침
		else if( iTargetID == 5 )
		{
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 2, g_pSiege->m_iSiege_AshramWndPage[2] );
		}
		//	연맹가입
		else if( iTargetID>=10 && iTargetID<=18 )
		{
			//	연맹장이 있는지 체크
			if( g_pSiege->m_iSiege_AshramWndPage[2] == 0 )
			{
				if( iTargetID > 10 )
				{
					CHTString strTemp = g_cUIManager->HT_GetTextLabelControl( _DIALOG_SIEGEJOININFO_2, 10 );
					if( strTemp.HT_bIsEmpty() )
						return;
				}
			}

			//	마하라자만이 사용할수 있다.
			if( g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_MAHARAJA ||
				g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_RAJA )
			{
				g_pSiege->HT_vSiege_NetworkApplySiege( 2, iTargetID-10 );
			}
		}
	}
}
//	입력함수 처리 선택 아쉬람 정보3
void HTSiege::HT_vSiege_InputCheckJoinInfo3(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEJOININFO_3);
		}
		//	뒤로
		else if( iTargetID == 2 )
		{
			//	선택 아쉬람 정보창 페이지
			g_pSiege->m_iSiege_AshramWndPage[3]++;
			if( g_pSiege->m_iSiege_AshramWndPage[3] == 5 )
				g_pSiege->m_iSiege_AshramWndPage[3] = 0;
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 3, g_pSiege->m_iSiege_AshramWndPage[3] );
			CHTString strTemp;
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgSiegePageNo, &strMessage, _T(""), _T("") );
			strTemp.HT_szFormat( strMessage, g_pSiege->m_iSiege_AshramWndPage[3] );
			//	Page No
            g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_3, 3, strTemp.HT_szGetString() );
			//	이름 바꿈
			if( g_pSiege->m_iSiege_AshramWndPage[3] == 0 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeRequestUnionMaster, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_3, 20, strMessage );
			}
			else
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeJoinUnion, &strMessage, _T(""), _T("") );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGEJOININFO_3, 20, strMessage );
			}
		}
		//	새로고침
		else if( iTargetID == 5 )
		{
			//	Request Seige Entry
			g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( 3, g_pSiege->m_iSiege_AshramWndPage[3] );
		}
		//	연맹가입
		else if( iTargetID>=10 && iTargetID<=18 )
		{
			//	연맹장이 있는지 체크
			if( g_pSiege->m_iSiege_AshramWndPage[3] == 0 )
			{
				if( iTargetID > 10 )
				{
					CHTString strTemp = g_cUIManager->HT_GetTextLabelControl( _DIALOG_SIEGEJOININFO_3, 10 );
					if( strTemp.HT_bIsEmpty() )
						return;
				}
			}

			//	마하라자만이 사용할수 있다.
			if( g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_MAHARAJA ||
				g_cGuildSystem->HT_byGuild_GetAuthority() == GUILD_AUTHORITY_RAJA )
			{
				g_pSiege->HT_vSiege_NetworkApplySiege( 3, iTargetID-10 );
			}
		}
	}
}
//	입력함수 처리 선택 도움말1
void HTSiege::HT_vSiege_InputCheckHelp1(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_SIEGEHELP_1, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_1);
		}
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_1);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_1);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_1, iPosX, iPosY );
		}
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_1);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_2);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_2, iPosX, iPosY );
		}
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_1);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_3);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_3, iPosX, iPosY );
		}
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_1);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_4);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_4, iPosX, iPosY );
		}
	}
}
//	입력함수 처리 선택 도움말2
void HTSiege::HT_vSiege_InputCheckHelp2(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_SIEGEHELP_2, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_2);
		}
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_2);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_1);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_1, iPosX, iPosY );
		}
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_2);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_2);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_2, iPosX, iPosY );
		}
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_2);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_3);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_3, iPosX, iPosY );
		}
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_2);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_4);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_4, iPosX, iPosY );
		}
	}
}
//	입력함수 처리 선택 도움말3
void HTSiege::HT_vSiege_InputCheckHelp3(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_SIEGEHELP_3, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_3);
		}
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_3);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_1);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_1, iPosX, iPosY );
		}
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_3);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_2);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_2, iPosX, iPosY );
		}
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_3);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_3);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_3, iPosX, iPosY );
		}
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_3);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_4);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_4, iPosX, iPosY );
		}
	}
}
//	입력함수 처리 선택 도움말4
void HTSiege::HT_vSiege_InputCheckHelp4(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		HTint iPosX, iPosY;
		g_cUIManager->HT_GetWindowPos( _DIALOG_SIEGEHELP_4, iPosX, iPosY );

		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_4);
		}
		else if( iTargetID == 1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_4);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_1);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_1, iPosX, iPosY );
		}
		else if( iTargetID == 2 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_4);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_2);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_2, iPosX, iPosY );
		}
		else if( iTargetID == 3 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_4);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_3);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_3, iPosX, iPosY );
		}
		else if( iTargetID == 4 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SIEGEHELP_4);
			g_cUIManager->HT_ShowWindow(_DIALOG_SIEGEHELP_4);
			g_cUIManager->HT_MoveWindow(_DIALOG_SIEGEHELP_4, iPosX, iPosY );
		}
	}
}

//	참가 아쉬람 정보 신청
HTvoid HTSiege::HT_vSiege_RequestJoinAshramInfo()
{
	for( HTint i=0 ; i<4 ; i++ )
	{
		g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( i, 0 );
	}
}

//	아쉬람 마크 붙이기
HTvoid HTSiege::HT_vSiege_SetAhsramMark( HTint iDlgNo, HTint iSlotNo, HTint iGuildNo )
{
	if( iGuildNo == 0 )
	{
		g_cUIManager->HT_SetTextureControlDisplay( iDlgNo, 10+(iSlotNo*3), HT_FALSE );
		g_cUIManager->HT_SetTextureControlDisplay( iDlgNo, 11+(iSlotNo*3), HT_FALSE );
		g_cUIManager->HT_SetTextureControlDisplay( iDlgNo, 12+(iSlotNo*3), HT_FALSE );
		return;
	}

	HTint iToBmp1, iToBmp2;
	HTint iColor, iTitle, iEmblem;
	g_cGuildSystem->HT_hrGetGuildMark(iGuildNo, &iColor, &iTitle, &iEmblem);

	iToBmp1 = iToBmp2 = 0;
	if( iEmblem == -1 || iTitle == -1 || iColor == -1 )
	{
		g_cUIManager->HT_SetTextureControlDisplay( iDlgNo, 10+(iSlotNo*3), HT_FALSE );
		g_cUIManager->HT_SetTextureControlDisplay( iDlgNo, 11+(iSlotNo*3), HT_FALSE );
		g_cUIManager->HT_SetTextureControlDisplay( iDlgNo, 12+(iSlotNo*3), HT_FALSE );
		return;
	}

	if( iEmblem > 12 )
	{
		//if ( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )
			iToBmp1 = UI_GUILD_EMBLEMTEX_B + (iEmblem - 12), iToBmp2 = UI_GUILD_BACKTEX_B + (iEmblem - 12);
		//else if ( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )
		//	iToBmp1 = UI_GUILD_EMBLEMTEX_V + (iEmblem - 12), iToBmp2 = UI_GUILD_BACKTEX_V + (iEmblem - 12);
		//else if ( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )
		//	iToBmp1 = UI_GUILD_EMBLEMTEX_S + (iEmblem - 12), iToBmp2 = UI_GUILD_BACKTEX_S + (iEmblem - 12);
	}
	else
	{
		iToBmp1 = UI_GUILD_EMBLEMTEX_N + iEmblem,	iToBmp2 = UI_GUILD_BACKTEX_N + iEmblem;
	}

	g_cUIManager->HT_SetTextureControlDisplay( iDlgNo, 10+(iSlotNo*3), HT_TRUE );
	g_cUIManager->HT_SetTextureControlDisplay( iDlgNo, 11+(iSlotNo*3), HT_TRUE );
	g_cUIManager->HT_SetTextureControlDisplay( iDlgNo, 12+(iSlotNo*3), HT_TRUE );

	g_cUIManager->HT_SetTextureControlImage( iDlgNo, 10+(iSlotNo*3), iToBmp1-1 );
	g_cUIManager->HT_SetTextureControlImage( iDlgNo, 11+(iSlotNo*3), iToBmp2-1 );
	g_cUIManager->HT_SetTextureControlImage( iDlgNo, 12+(iSlotNo*3), UI_GUILD_TITLETEX + iTitle - 1 );
	g_cUIManager->HT_SetTextureControlScale( iDlgNo, 10+(iSlotNo*3), 32, 32, 64, 64);
	g_cUIManager->HT_SetTextureControlScale( iDlgNo, 11+(iSlotNo*3), 32, 32, 64, 64);
	g_cUIManager->HT_SetTextureControlScale( iDlgNo, 12+(iSlotNo*3), 16, 16, 32, 32);
	g_cUIManager->HT_SetTextureControlColor( iDlgNo, 10+(iSlotNo*3), AMBLEM_COLOR[iColor-1]);
	g_cUIManager->HT_SetTextureControlColor( iDlgNo, 11+(iSlotNo*3), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f));
	g_cUIManager->HT_SetTextureControlColor( iDlgNo, 12+(iSlotNo*3), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//	Get
//	Get Owner of Castle
HTbool HTSiege::HT_vSiege_GetOwerOfCastle()
{ 
	if( g_cGuildSystem->HT_iGuild_GetGuildID() == m_iSiege_CastleAshramID )
		return HT_TRUE;
	else
		return HT_FALSE;
}

//	Network
//	ApplySiege
HTvoid HTSiege::HT_vSiege_NetworkApplySiege( HTbyte byClanSlot, HTbyte byExpandSlot )
{
	MSG_APPLY_SIEGE* info = HT_NULL;
	info = new MSG_APPLY_SIEGE;

	info->byClanSlot = byClanSlot;
	info->byExpandSlot = byExpandSlot+(m_iSiege_AshramWndPage[byClanSlot]*8);

	// Send to server
	g_pNetWorkMgr->RequestMsgApplySiege( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ApplySiege %d", info->byClanSlot );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	SCP ApplySiege
HTvoid HTSiege::HT_vSiege_NetworkSCP_ApplySiege( MSG_APPLY_SIEGE* info )
{
	//	결과값 0일때
	if( info->snResult == 0 )
	{
		this->HT_vSiege_NetworkCheckSiegeEntry( info->byClanSlot, info->byExpandSlot );
	}
}
//	CheckSiegeEntry
HTvoid HTSiege::HT_vSiege_NetworkCheckSiegeEntry( HTint iClanSlot, HTint iPage )
{
	MSG_CHECK_SIEGE_ENTRY* info = HT_NULL;
	info = new MSG_CHECK_SIEGE_ENTRY;

	info->byClanSlot = iClanSlot;
	info->byPage = iPage;

	// Send to server
	g_pNetWorkMgr->RequestMsgCheckSiegeEntry( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_CheckSiegeEntry %d, %d", info->byClanSlot, info->byPage );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	Siege Entry
HTvoid HTSiege::HT_vSiege_NetworkSiegeEntry( MSG_SIEGE_ENTRY* info )
{
	//	DLG No
	int iDlgNo = _DIALOG_SIEGEJOININFO_0;
    if( info->byClanSlot == 0 )			iDlgNo = _DIALOG_SIEGEJOININFO_0;
	else if( info->byClanSlot == 1 )	iDlgNo = _DIALOG_SIEGEJOININFO_1;
	else if( info->byClanSlot == 2 )    iDlgNo = _DIALOG_SIEGEJOININFO_2;
	else if( info->byClanSlot == 3 )    iDlgNo = _DIALOG_SIEGEJOININFO_3;
	else								iDlgNo = _DIALOG_SIEGEJOININFO_0;

	for( HTint i=0 ; i<8 ; i++ )
	{
		m_iSiege_GuildID[i] = info->irgGuildID[i];
		//	아쉬람 명
		if( m_iSiege_GuildID[i] > 0 )
		{
			g_cUIManager->HT_SetTextLabelControl( iDlgNo, 10+i, info->szrgGuildName[i] );
			this->HT_vSiege_SetAhsramMark( iDlgNo, i, info->dwrgGuildMark[i] );
		}
		else
		{
			g_cUIManager->HT_SetTextLabelControl( iDlgNo, 10+i, _T("") );
			this->HT_vSiege_SetAhsramMark( iDlgNo, i, 0 );
		}
	}
	//	[Siege1_참가아쉬람]에 입력
	if( info->byPage == 0 )
	{
		CHTString strMessage;
		if( info->byClanSlot == 0 )
		{
			g_cUIManager->HT_SetScriptMessage( eMsgSiegeNameDefenseUnion, &strMessage, _T(""), _T("") );
			m_strSiege_Alliance[0].HT_szFormat( strMessage, info->szrgGuildName[0] );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE1, 6, m_strSiege_Alliance[0].HT_szGetString() );
			g_cUIManager->HT_SetTextLabelControl( iDlgNo, 4, m_strSiege_Alliance[0].HT_szGetString() );
		}
		else if( info->byClanSlot == 1 )
		{
			g_cUIManager->HT_SetScriptMessage( eMsgSiegeNameAttackUnion, &strMessage, _T(""), _T("") );
			m_strSiege_Alliance[1].HT_szFormat( strMessage, info->szrgGuildName[0] );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE1, 7, m_strSiege_Alliance[1].HT_szGetString() );
			g_cUIManager->HT_SetTextLabelControl( iDlgNo, 4, m_strSiege_Alliance[1].HT_szGetString() );
		}
		else if( info->byClanSlot == 2 )
		{
			g_cUIManager->HT_SetScriptMessage( eMsgSiegeNameAttackUnion, &strMessage, _T(""), _T("") );
			m_strSiege_Alliance[2].HT_szFormat( strMessage, info->szrgGuildName[0] );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE1, 8, m_strSiege_Alliance[2].HT_szGetString() );
			g_cUIManager->HT_SetTextLabelControl( iDlgNo, 4, m_strSiege_Alliance[2].HT_szGetString() );
		}
		else if( info->byClanSlot == 3 )
		{
			g_cUIManager->HT_SetScriptMessage( eMsgSiegeNameAttackUnion, &strMessage, _T(""), _T("") );
			m_strSiege_Alliance[3].HT_szFormat( strMessage, info->szrgGuildName[0] );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE1, 9, m_strSiege_Alliance[3].HT_szGetString() );
			g_cUIManager->HT_SetTextLabelControl( iDlgNo, 4, m_strSiege_Alliance[3].HT_szGetString() );
		}
	}
	//	연맹가입시의 에러 처리를 위해
	if( m_iSiege_GuildID[0] < 0 )
	{
		g_pSiege->HT_vSiege_NetworkCheckSiegeEntry( info->byClanSlot, g_pSiege->m_iSiege_AshramWndPage[info->byClanSlot] );
	}
}
//	CSP State of the siege
HTvoid HTSiege::HT_vSiege_NetworkCSPStateOfTheSiege()
{
	MSG_STATE_OF_THE_SIEGE* info = HT_NULL;
	info = new MSG_STATE_OF_THE_SIEGE;

	// Send to server
	g_pNetWorkMgr->RequestMsgStateOfTheSiege( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("StateOfTheSiege" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	SCP State of the siege
HTvoid HTSiege::HT_vSiege_NetworkSCPStateOfTheSiege( MSG_STATE_OF_THE_SIEGE* info )
{
	HTint iScore[5];
	for( HTint i=0 ; i<5 ; i++ )
		iScore[i] = 0;

	for( i=0 ; i<11 ; i++ )
	{
		if( info->irgClan[i]>=19 && info->irgClan[i]<=23 )
		{
			g_cUIManager->HT_DelTextureControl( _DIALOG_SIEGE2, 10+i );
			g_cUIManager->HT_AddTextureControl( _DIALOG_SIEGE2, 10+i, g_iSiegeMark[info->irgClan[i]-19], g_srgSymbolForSiege[i][0]+37-10, g_srgSymbolForSiege[i][1]+68-10, HT_COLOR(1,1,1,1), 16, 16 );
			//	Check Score
			iScore[info->irgClan[i]-19] += g_srgSymbolForSiege[i][2];
		}
	}

	CHTString strTemp;
	CHTString strMessage;
	g_cUIManager->HT_SetScriptMessage( eMsgCommonScore, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( "%s : %d %s", m_strSiege_Alliance[0].HT_szGetString(), iScore[0], strMessage.HT_szGetString() );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE2, 10, strTemp.HT_szGetString() );
	strTemp.HT_szFormat( "%s : %d %s", m_strSiege_Alliance[1].HT_szGetString(), iScore[1], strMessage.HT_szGetString() );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE2, 11, strTemp.HT_szGetString() );
	strTemp.HT_szFormat( "%s : %d %s", m_strSiege_Alliance[2].HT_szGetString(), iScore[2], strMessage.HT_szGetString() );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE2, 12, strTemp.HT_szGetString() );
	strTemp.HT_szFormat( "%s : %d %s", m_strSiege_Alliance[3].HT_szGetString(), iScore[3], strMessage.HT_szGetString() );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE2, 13, strTemp.HT_szGetString() );
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeScoreEmptyUnion, &strMessage, _T(""), _T("") );
	strTemp.HT_szFormat( strMessage, iScore[4] );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE2, 14, strTemp.HT_szGetString() );
}
//	CSP Fix Data of Siege
HTvoid HTSiege::HT_vSiege_NetworkCSP_FixDataOfSiege( HTbyte byWhat, HTbyte byDate )
{
	MSG_FIX_DATE_OF_SIEGE* info = HT_NULL;
	info = new MSG_FIX_DATE_OF_SIEGE;

	info->byWhat = byWhat;
	info->byDate = byDate;

	// Send to server
	g_pNetWorkMgr->RequestMsgFixDataOfSiege( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_FixDateOfSiege What:%d, Data:%d", info->byWhat, info->byDate );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	SCP Fix Data Of Siege	무슨 버그인지 모르겠다.
HTvoid HTSiege::HT_vSiege_NetworkSCP_FixDataOfSiege( MSG_FIX_DATE_OF_SIEGE* info )
{
	CHTString strTemp;
	CHTString strMessage1;
	CHTString strMessage2;
	g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeTime, &strMessage1, _T(""), _T("") );
	if( info->byDate == 1 )
	{
		g_cUIManager->HT_SetScriptMessage( eMsgSiegeFriEve8, &strMessage1, strMessage2, _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE3, 12, strMessage1 );
	}
	else if( info->byDate == 2 )
	{
		g_cUIManager->HT_SetScriptMessage( eMsgSiegeFriEve10, &strMessage1, strMessage2, _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE3, 12, strMessage1 );
	}
	else if( info->byDate == 3 )
	{
		g_cUIManager->HT_SetScriptMessage( eMsgSiegeSatEve8, &strMessage1, strMessage2, _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE3, 12, strMessage1 );
	}
	else if( info->byDate == 4 )
	{
		g_cUIManager->HT_SetScriptMessage( eMsgSiegeSatEve10, &strMessage1, strMessage2, _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE3, 12, strMessage1 );
	}
	else if( info->byDate == 5 )
	{
		g_cUIManager->HT_SetScriptMessage( eMsgSiegeSunEve8, &strMessage1, strMessage2, _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE3, 12, strMessage1 );
	}
	else
	{
		g_cUIManager->HT_SetScriptMessage( eMsgSiegeSiegeNoTime, &strMessage1, strMessage2, _T("") );
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE3, 12, strMessage1 );
	}
}
//	CSP Set SalesRate
HTvoid HTSiege::HT_vSiege_NetworkCSP_SetSalesRate( HTbyte byType, HTbyte byRate )
{
	Msg_SetSalesRate* info = HT_NULL;
	info = new Msg_SetSalesRate;

	info->byType = byType;
	info->byRate = byRate;

	// Send to server
	g_pNetWorkMgr->RequestMsgSetSalesRate( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_SetSalesRate Type:%d, Rate:%d", info->byType, info->byRate );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	SCP Set SalesRate
HTvoid HTSiege::HT_vSiege_NetworkSCP_SetSalesRate( Msg_SetSalesRate* info )
{
    //	세금 비율
	g_cRentalStore->m_iTex = m_bySiege_MoneyRate = info->byRate;

	CHTString strTemp;
	CHTString strMessage;
	strTemp.HT_szFormat( "%d %%", m_bySiege_MoneyRate );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE4, 9, strTemp.HT_szGetString() );
	g_cUIManager->HT_SetScrollBarControl( _DIALOG_SIEGE4, 0, m_bySiege_MoneyRate );

	//	회수할수 있는 돈
	g_cUIManager->HT_SetScriptMessage( eMsgItemInfoPrice, &strMessage, _T(""), _T("") );
	if (info->dwMoney < 0 || info->dwMoney > 2100000000L ) 
	{
		strTemp.HT_szFormat( "MAX" );
	}
	else
	{
		g_cUIManager->HT_SetScriptMessage( eMsgItemInfoPrice, &strMessage, _T(""), _T("") );
		strTemp.HT_szFormat( strMessage, info->dwMoney );
	}
	//strTemp = g_cUIManager->HT_strSetRestMark(info->dwMoney);
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE4, 8, strTemp.HT_szGetString() );
}
//	CSP Get Money
HTvoid HTSiege::HT_vSiege_NetworkCSP_GetMoney()
{
	Msg_GetMoney* info = HT_NULL;
	info = new Msg_GetMoney;

	info->nType = m_iGetMoneyType;
	info->byAction = m_iGetMoneyAction;

	// Send to server
	g_pNetWorkMgr->RequestMsgGetMoney( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_GetMoney Type:%d", info->nType );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	SCP Get Money
HTvoid HTSiege::HT_vSiege_NetworkSCP_GetMoney( Msg_GetMoney* info )
{
	CHTString strMessage;
	switch(m_iGetMoneyType)
	{
	case 1:		// Yut
		if (m_iGetMoneyAction == 1)	// 조회시 값저장
		{
			m_iGetMoneyYut = info->dwMoney;
//			g_cNPCControl->HT_vNPCControl_GetNextStep(1);
		}
		else if (m_iGetMoneyAction == 2)	// 요청시 적립액 주기
		{
			if (m_iGetMoneyYut <= 0)
			{
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeNoBuildRupia, &strMessage, _T(""), _T("") );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage );
				g_cNPCControl->HT_vNPCControl_DialogWin_AntiActive(); // NPC 창 닫기
			}
			else
			{
				CHTString str, str2;
				str2 = g_cUIManager->HT_strSetRestMark(m_iGetMoneyYut);
				g_cUIManager->HT_SetScriptMessage( eMsgSiegeExplain23, &strMessage, _T(""), _T("") );
				str.HT_szFormat(strMessage, str2.HT_szGetString());
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, str);
				g_cNPCControl->HT_vNPCControl_DialogWin_AntiActive();// NPC 창 닫기
			}
		}
		break;
	case 2:		// 상점
		{
			CHTString str;
			g_cUIManager->HT_SetScriptMessage( eMsgItemInfoPrice, &strMessage, _T(""), _T("") );
			str.HT_szFormat( strMessage, 0 );
			//	Only Label 루피아
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE4, 8, str );
			//	Set Inventory
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->dwMoney );
		}
		break;
	case 3:		// 대여상점
		{
			if (m_iGetMoneyAction == 2)	 // 조회시 값저장
			{
				CHTString str;
				g_cUIManager->HT_SetScriptMessage( eMsgItemInfoPrice, &strMessage, _T(""), _T("") );
				str.HT_szFormat( strMessage, 0 );
				//	Only Label 루피아
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE4, 14, str );
				//	Set Inventory
				g_cEquipInventory->HT_vEquipInventory_SetPCMoney(info->dwMoney );
			}
			else 
			{
				CHTString strMessage, strTemp;

				//	회수할수 있는 돈
				g_cUIManager->HT_SetScriptMessage( eMsgItemInfoPrice, &strMessage, _T(""), _T("") );
				strTemp.HT_szFormat( strMessage, info->dwMoney );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SIEGE4, 14, strTemp.HT_szGetString() );
			}
		}
		break;
	default:
		break;
	}

}
//	SCP Castle
HTvoid HTSiege::HT_vSiege_NetworkSCP_SetCastle( HTint iAshramID )
{
	//	Castle Ashram ID
	m_iSiege_CastleAshramID = iAshramID;
}
