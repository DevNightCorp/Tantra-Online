#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htguild.h"

#define		_GUILD_EMBLEM_NUM					72
#define		_GUILD_TITLE_NUM					84
#define		_GUILD_COLOR_NUM					72

#define		GUILD_CREATE_NEED_MONEY				300000 // 길드 창설에 필요한 돈
#define		GUILD_MARK_NEED_MONEY				3000000 // 길드 마크 만들때 필요한 돈

#define		_GUILD_RECORD_NUM					9
#define		_GUILD_TABLE_NUM					5

#define		_DISPLAYMEMBERCOUNT					9

#define		_GUILD_EDIT_ORI_COLOR	HT_COLOR(221.0f/255.0f, 205.0f/255.0f, 163.0f/255.0f, 100.0f/100.0f)
#define		_GUILD_EDIT_SEL_COLOR	HT_COLOR(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 100.0f/100.0f)


HTGuild::HTGuild(void)
{
	m_iGuild_SlideBarCurPos = 0;
	m_bGuild_SlideBarBtn = HT_FALSE;
	//----------LL 초기화---------//
	this->HT_LL_vInitList();

	m_iEmblem = -1;
	m_iTitle = -1;
	m_iColor = -1;

	m_nGuildConnectMsg = 0;
	m_nAshuramGuildJoinMode = 0;
	m_iMyStrongGuildIndex = -1;

	//	내가 요새를 보우하고 있는지 확인
	m_bMyStrongGuild = HT_FALSE;
	//	MessageBox Type
	m_iGuild_MsgBoxType = 0;
	//	CargoUse
	m_bAshramCargoUseSw = HT_FALSE;
}

HTGuild::~HTGuild(void)
{
	HT_DELETE( m_pGuildList_Head );
	HT_DELETE( m_pGuildList_Tail );

	g_cUIManager->HT_DeleteWindow( _DIALOG_ASHRAMINFO );
	g_cUIManager->HT_DeleteWindow( _DIALOG_ASHRAMMEMBERLISET );
	g_cUIManager->HT_DeleteWindow( _DIALOG_AMBLEM );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SETLEVELASHCAGO );
	g_cUIManager->HT_DeleteWindow( _DIALOG_SANCTIONASHCAGO );
	g_cUIManager->HT_DeleteWindow( _DIALOG_ASHRAMCAGO );
}

//	데이타 삭제
HTvoid HTGuild::HT_vGuild_Delete()
{
	//g_cUIManager->HT_DeleteWindow( _DIALOG_DISCONNECTSERVER );
    //----------LL 데이타 전부 지우기---------//
	this->HT_LL_hrDeleteAll();
}

//	초기 데이타 셋팅
HTvoid HTGuild::HT_vGuild_Init()
{
	//	Create Window
	this->HT_vGuild_CreateWindow();

	//	확인 단계
	m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_NONE;
	//	확인 버튼 눌렸는지 체크
	m_bGuild_ConfirmDlgBoxSw = HT_FALSE;
	//	길드 장인지 아닌지.
	m_byGuild_GuilAuthority = GUILD_AUTHORITY_NONE;
	m_dwGuild_EmblemID = 0;
	//	선택된 길드원 초기화
	m_strGuild_ListSelectdName.HT_hrCleanUp();
	//	길드이름 초기화
	m_strGuild_GuildName.HT_hrCleanUp();

	g_bGuildMarkShow = HT_TRUE;

	for( HTint i=0 ; i<2 ; i++ )
	{
		m_strAlliedGuildName[i] = _T(" ");
		m_strEnemyGuildName[i] = _T(" ");
	}

	//	Ashram Cargo Extence Type
	m_byAshramCargoExtenceType = 1;
	//	Ashram Cargo
	m_iPageOfAshramCargo = 0;
	m_iPrevPageOfAshramCargo = 0;

	for( i=0 ; i<120 ; i++ )
	{
		ZeroMemory( &m_arrItemOfAshramCargo[0][i], sizeof(STRUCT_ITEM) );
		ZeroMemory( &m_arrItemOfAshramCargo[1][i], sizeof(STRUCT_ITEM) );
		ZeroMemory( &m_arrItemOfAshramCargo[2][i], sizeof(STRUCT_ITEM) );
	}
}

//	Create Window
HTvoid HTGuild::HT_vGuild_CreateWindow()
{
	CHTString strTemp;
	CHTString strMessage;

	int i, j;
	//	[_DIALOG_ASHRAMINFO]
	//	Window
	g_cUIManager->HT_SetScriptMessage( eMsgAshramTitle, &strMessage, _T(""), _T("") );	//	Ashram
	g_cUIManager->HT_CreateWindow( _DIALOG_ASHRAMINFO, strMessage, 330, 466, g_cGuildSystem->HT_vGuild_InputCheckForAshramInfo, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_ASHRAMINFO, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 1, 8, 3, 36, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 2, 8, 3, 148, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 3, 8, 3, 285, 1400, 323, 6 );
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 4, 8, 3, 330, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 5, 8, 3, 375, 1400, 323, 6 );
	//	Texture 아쉬람정보
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 6, 9, 39, 30, 1400, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramInfo, &strMessage, _T(""), _T("") );	//	아쉬람정보
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 19 );
	//	Texture 공지 사항
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 7, 9, 39, 143, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramNotice, &strMessage, _T(""), _T("") );	//	공지 사항
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 143, 152, 19 );
	//	Texture 연합 아쉬람
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 8, 9, 39, 280, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramUnionAshram, &strMessage, _T(""), _T("") );	//	연합 아쉬람
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 8, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 280, 152, 19 );
	//	Texture 적대 아쉬람
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 9, 9, 39, 325, 1400, 152, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 9, _T("적대 아쉬람"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 325, 152, 19 );
	//	Texture 아쉬람 명
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 10, 9, 92, 68, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramAshramName, &strMessage, _T(""), _T("") );	//	아쉬람 명
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 68, 152, 19 );
	//	Texture 소유물
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 11, 10, 92, 79, 1400, 79, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 11, _T("소유물"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 79, 79, 19 );
	//	Texture 등록인원
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 12, 10, 92, 96, 1400, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramResigstMember, &strMessage, _T(""), _T("") );	//	등록인원
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 96, 79, 19 );
	//	Texture 접속인원
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 13, 10, 92, 119, 1400, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramConnectMember, &strMessage, _T(""), _T("") );	//	접속인원
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 119, 79, 19 );
	//	Texture 만다라 요새
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 14, 9, 173, 79, 1400, 152, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 14, _T("만다라 요새"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 173, 79, 152, 19 );
	//	Texture 등록인원 값
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 15, 9, 173, 99, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 15, _T("0/0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 173, 99, 79, 19 );
	//	Texture 접속인원 값
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 16, 9, 173, 119, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 16, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 173, 119, 79, 19 );
	//	Only Label 공지 사항
	g_cUIManager->HT_SetScriptMessage( eMsgAshramExplainNotice, &strMessage, _T(""), _T("") );	//	공지사항입니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 17, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 167, 310, 100 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_ASHRAMINFO, 17, 7 );
	//	Only Label 연합 아쉬람 정보
	g_cUIManager->HT_SetScriptMessage( eMsgAshramNoUnionAshram, &strMessage, _T(""), _T("") );	//	연합 아쉬람이 없습니다.
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 18, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 305, 310, 16 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_ASHRAMINFO, 18, 7 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 19, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 340, 310, 16 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_ASHRAMINFO, 19, 7 );
	//	Only Label 적대 아쉬람 정보
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 19, _T("적대 아쉬람이 없습니다."), 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 350, 310, 16 );
	//g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_ASHRAMINFO, 19, 7 );
	//	Button 구성인원
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMINFO, 20, 9, 129, 37, 0, 0, 1500, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramOrganizationMember, &strMessage, _T(""), _T("") );	//	구성인원
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 129, 37, 90, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMINFO, 20 );
	if( g_iInationalType == INATIONALTYPE_KOREA )
	{
		//	Button 홈피제작
		g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMINFO, 21, 159, 125, 418, 160, 161, 1500, 79, 19 );
		g_cUIManager->HT_SetScriptMessage( eMsgAshramMakeBlog, &strMessage, _T(""), _T("") );	//	홈피제작
		g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 21, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 125, 418, 79, 19 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMINFO, 21 );
		//	Button 홈피입장
		g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMINFO, 22, 159, 227, 418, 160, 161, 1500, 79, 19 );
		g_cUIManager->HT_SetScriptMessage( eMsgAshramEnterBlog, &strMessage, _T(""), _T("") );	//	홈피입장
		g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 22, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 227, 418, 79, 19 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMINFO, 22 );
		//	Button 미니블로그
		g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMINFO, 27, 159, 23, 418, 160, 161, 1500, 79, 19 );
		g_cUIManager->HT_SetScriptMessage( eMsgAshramMiniBlog, &strMessage, _T(""), _T("") );	//	미니블로그
		g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 27, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 23, 418, 79, 19 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMINFO, 27 );
	}
	//	Texture 작은 박스
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 0, 66, 292, 46, 1400, 32, 32 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 23, 0, 294, 48, 1410, 1, 1 );
	//	Texture 큰 박스
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 0, 66, 12, 58, 1400, 74, 77 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 24, 0, 17, 63, 1401, 1, 1);
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 25, 0, 17, 63, 1402, 1, 1);
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 26, 0, 33, 79, 1403, 1, 1);

	//	[_DIALOG_ASHRAMMEMBERLISET]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_ASHRAMMEMBERLISET, _T(""), 330, 466, g_cGuildSystem->HT_vGuild_InputCheckForAshramMemberList, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_ASHRAMMEMBERLISET, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 1, 8, 3, 36, 1400, 323, 6 );
	//	Texture 구성인원
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 2, 9, 129, 30, 1400, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramOrganizationMember, &strMessage, _T(""), _T("") );	//	구성인원
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 129, 30, 90, 19 );
	//	Texture 종족
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 3, 9, 4, 56, 1400, 32, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressTribe, &strMessage, _T(""), _T("") );	//	종족
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 4, 56, 34, 19 );
	//	Texture 이름
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 4, 9, 40, 56, 1400, 134, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressName, &strMessage, _T(""), _T("") );	//	이름
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 56, 137, 19 );
	//	Texture 레벨
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 5, 9, 178, 56, 1400, 31, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramLevel, &strMessage, _T(""), _T("") );	//	레벨
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 177, 56, 34, 19 );
	//	Texture 직위
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 6, 9, 213, 56, 1400, 61, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramPosition, &strMessage, _T(""), _T("") );	//	직위
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 212, 56, 64, 19 );
	//	Texture 접속
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 7, 9, 278, 56, 1400, 31, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressConnect, &strMessage, _T(""), _T("") );	//	접속
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 277, 56, 34, 19 );
	//	Schroll
	g_cUIManager->HT_AddScrollBarControl( _DIALOG_ASHRAMMEMBERLISET, 8, 312, 77, 350, 50 );
	//	Loop
	for( i=0 ; i<_DISPLAYMEMBERCOUNT ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 0, 66, 5, 77+(i*39) );
		g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 10+i, 0, 13, 83+(i*39), 1402, 32, 32 );
		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_ASHRAMMEMBERLISET, 10+i, HT_FALSE );
		g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 10+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 77+(i*39), 137, 31 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 20+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 177, 77+(i*39), 34, 31 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 30+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 212, 77+(i*39), 64, 31 );
		g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 40+i, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 277, 77+(i*39), 34, 31 );
		g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMMEMBERLISET, 10+i, 0, 2, 77+(i*39), 202, 0, 1500, 291, 32 );
	}
	//	Button 아쉬람정보
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMMEMBERLISET, 50, 9, 39, 37, 0, 0, 1500, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramInfo, &strMessage, _T(""), _T("") );	//	아쉬람정보
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 50, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 37, 90, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMMEMBERLISET, 50 );
	//	Button 가입
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMMEMBERLISET, 51, 159, 82, 430, 160, 161 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonJoin, &strMessage, _T(""), _T("") );	//	가입
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 51, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 82, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMMEMBERLISET, 51 );
	//	Button 탈퇴
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMMEMBERLISET, 52, 159, 201, 430, 160, 161 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonSecede, &strMessage, _T(""), _T("") );	//	탈퇴
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 52, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 201, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMMEMBERLISET, 52 );

	// 앰블럼 제작창
	// 윈도우 생성 (탭 = 1, 2, 3)
	g_cUIManager->HT_CreateWindow(_DIALOG_AMBLEM, "Emblem", 330, 345, g_cGuildSystem->HT_vGuild_InputCheckForEmblemSelecting, 2);
	g_cUIManager->HT_WindowArrangement(_DIALOG_AMBLEM, 5);
	g_cUIManager->HT_AddTextureControl(_DIALOG_AMBLEM, 0, 8, 3, 37, 1400, 324, 6);

	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 1, 159, 10, 31, 160, 161, 1500, 69, 19);
	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 2, 159, 80, 31, 160, 161, 1500, 69, 19);
	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 3, 159, 150, 31, 160, 161, 1500, 69, 19);
	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 4, 159, 220, 31, 160, 161, 1500, 69, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgAshramBackMark, &strMessage, _T(""), _T("") );	//	배경문양
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 1, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 31, 69, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgAshramMark, &strMessage, _T(""), _T("") );	//	문양
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 2, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 31, 69, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgAshramMark, &strMessage, _T(""), _T("") );	//	문양2
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 3, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 31, 69, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgAshramBackColor, &strMessage, _T(""), _T("") );	//	배경색
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 4, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 220, 31, 69, 19);

	// 앰블램 11, 12, 13
	g_cUIManager->HT_AddTextureControl(_DIALOG_AMBLEM, 11, 0, 25, 80, 1401, 64, 64);
	g_cUIManager->HT_AddTextureControl(_DIALOG_AMBLEM, 12, 0, 25, 80, 1402, 64, 64);
	g_cUIManager->HT_AddTextureControl(_DIALOG_AMBLEM, 13, 0, 25+16, 80+16, 1403, 32, 32);

	// 텍스처 시작 인덱스 101~ 112, 버튼도 동일
	int id = 0;
	for( i = 0; i < 7; ++i )
	{
		for( j = 0; j < 6; ++j )
		{
			id = 9;
			g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 100+j+(i*6), 0, 114+(32*j), 83+(32*i), 0, 0, 1500, 32, 32);
			g_cUIManager->HT_AddTextureControl(_DIALOG_AMBLEM, 100+j+(i*6), 0, 114+(32*j), 83+(32*i), 1400, 32, 32);
		}
	}

	// 앰블럼 버튼 (200 = 확인, 201 = 취소)
	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM,200, 159, 74, 315,  160, 161, 64, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	확인
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 1, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 74, 315, 64, 19);
	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM,201, 159, 188, 315,  160, 161, 64, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	취소
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 1, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 188, 315, 64, 19);

	m_iTabNo = 1;m_iBackIndex = 0;m_iTitleIndex = 0;m_iBackColor = 0;
	this->HT_vGuild_DialogBoxDrawTab(1);
	this->HT_bGuild_DialogBoxDrawEmblem(0);

	//	[_DIALOG_ASHRAMCAGO]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_ASHRAMCAGO, _T(""), 370, 540, g_cGuildSystem->HT_vGuild_InputCheckForAshramCago, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_ASHRAMCAGO, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMCAGO, 0, 8, 2, 36, 1400, 367, 6 );
	//	Texture 아쉬람 창고
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMCAGO, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramAshramCargo, &strMessage, _T(""), _T("") );	//	아쉬람창고
	strTemp.HT_szFormat( strMessage, 1 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMCAGO, 5, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Button 창고1
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMCAGO, 1, 159, 45, 55, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	창고
	strTemp.HT_szFormat( strMessage, 1 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMCAGO, 1, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 45, 55, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMCAGO, 1 );
	//	Button 창고2
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMCAGO, 2, 159, 153, 55, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	창고
	strTemp.HT_szFormat( strMessage, 2 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMCAGO, 2, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 153, 55, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMCAGO, 2 );
	//	Button 창고3
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMCAGO, 3, 159, 262, 55, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	창고
	strTemp.HT_szFormat( strMessage, 3 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMCAGO, 3, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 262, 55, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMCAGO, 3 );
	////	Button 창고사용
	//g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMCAGO, 4, 159, 283, 55, 160, 161, 1500, 64, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMCAGO, 4, _T("창고사용"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 283, 55, 64, 19 );
	//g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMCAGO, 4 );
	//	loop
	//	세로
	for( i=0 ; i<11 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMCAGO, 0, 1, 3+(i*36), 82, 1400, 3, 432 );
	}
	//	가로
	for( i=0 ; i<13 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMCAGO, 0, 2, 3, 82+(i*36), 1400, 360, 3 );
	}
	//	Slot Inven
	for( i=0 ; i<10 ; i++ )
	{
		for( j=0 ; j<12 ; j++ )
		{
			g_cUIManager->HT_AddSlotBoxControl( _DIALOG_ASHRAMCAGO, 10+((j*_GOODSKEEP_INVEN_WIDTH)+i), 0, 3+(i*36), 83+(j*36) );
		}
	}

	//	[_DIALOG_SANCTIONASHCAGO]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SANCTIONASHCAGO, _T(""), 420, 200, g_cGuildSystem->HT_vGuild_InputCheckForSanctionAshramCago, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SANCTIONASHCAGO, 5 );
	//	Texture 아쉬람 창고
	g_cUIManager->HT_SetScriptMessage( eMsgAshramExplainCargo01, &strMessage, _T(""), _T("") );	//	◐ 창고사용기간확인및과금 ◐
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 15, 420, 17 );
	//	창고명
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargoName, &strMessage, _T(""), _T("") );	//	창고명
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 50, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	창고명
	strTemp.HT_szFormat( strMessage, 1 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 90, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	창고명
	strTemp.HT_szFormat( strMessage, 2 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 120, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	창고명
	strTemp.HT_szFormat( strMessage, 3 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 150, 80, 17 );
	//	사용여부
	g_cUIManager->HT_SetScriptMessage( eMsgAshramUseYesOrNo, &strMessage, _T(""), _T("") );	//	사용여부
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 80, 50, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramNotUse, &strMessage, _T(""), _T("") );	//	사용중아님
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 80, 90, 80, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 80, 120, 80, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 80, 150, 80, 17 );
	//	만료기간
	g_cUIManager->HT_SetScriptMessage( eMsgAshramEnddate, &strMessage, _T(""), _T("") );	//	만료기간
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 140, 50, 120, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramEnd, &strMessage, _T(""), _T("") );	//	만료
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 140, 90, 120, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 14, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 140, 120, 120, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 15, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 140, 150, 120, 17 );
	//	D-day
	g_cUIManager->HT_SetScriptMessage( eMsgAshramDDay, &strMessage, _T(""), _T("") );	//	D-day
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 230, 50, 100, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 16, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 230, 90, 100, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 17, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 230, 120, 100, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 18, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 230, 150, 100, 17 );
	//	Button 창고1 사용료 지불
	g_cUIManager->HT_AddButtonControl( _DIALOG_SANCTIONASHCAGO, 1, 159, 320, 90, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramPayCargo, &strMessage, _T(""), _T("") );	//	사용료지불
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 320, 90, 79, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SANCTIONASHCAGO, 1 );
	//	Button 창고2 사용료 지불
	g_cUIManager->HT_AddButtonControl( _DIALOG_SANCTIONASHCAGO, 2, 159, 320, 120, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 320, 120, 79, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SANCTIONASHCAGO, 2 );
	//	Button 창고3 사용료 지불
	g_cUIManager->HT_AddButtonControl( _DIALOG_SANCTIONASHCAGO, 3, 159, 320, 150, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 320, 150, 79, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SANCTIONASHCAGO, 3 );

	//	[_DIALOG_SETLEVELASHCAGO]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SETLEVELASHCAGO, _T(""), 370, 190, g_cGuildSystem->HT_vGuild_InputCheckForSetLevelAshramCago, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SETLEVELASHCAGO, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_SETLEVELASHCAGO, 0, 8, 2, 36, 1400, 367, 6 );
	//	Texture 아쉬람 창고
	g_cUIManager->HT_AddTextureControl( _DIALOG_SETLEVELASHCAGO, 0, 9, 39, 30, 1400, 150, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramSetAshramRight, &strMessage, _T(""), _T("") );	//	아쉬람창고권한설정
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 150, 17 );
	//	창고명
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	창고명
	strTemp.HT_szFormat( strMessage, 1 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 100, 60, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	창고명
	strTemp.HT_szFormat( strMessage, 2 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 180, 60, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	창고명
	strTemp.HT_szFormat( strMessage, 3 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 260, 60, 80, 17 );
	//	아쉬람 등급
	g_cUIManager->HT_SetScriptMessage( eMsgCommonGuildRaja, &strMessage, _T(""), _T("") );	//	라자
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 80, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonGuildPrubaja, &strMessage, _T(""), _T("") );	//	푸르바자
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 100, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonGuildDandeca, &strMessage, _T(""), _T("") );	//	단디카
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 120, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonGuildTapasa, &strMessage, _T(""), _T("") );	//	타파사
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 140, 80, 17 );
	//	Slot Inven
	for( i=0 ; i<3 ; i++ )
	{
		for( j=0 ; j<4 ; j++ )
		{
			g_cUIManager->HT_AddTextureControl( _DIALOG_SETLEVELASHCAGO, 0, 63, 110+(i*80), 78+(j*20), 1400, 64, 19 );
			g_cUIManager->HT_AddTextureControl( _DIALOG_SETLEVELASHCAGO, 10+(i*4)+j, 175, 140+(i*80), 81+(j*20), 1402 );
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_SETLEVELASHCAGO, 10+(i*4)+j, HT_FALSE );
			g_cUIManager->HT_AddButtonControl( _DIALOG_SETLEVELASHCAGO, 10+(i*4)+j, 0, 110+(i*80), 78+(j*20), 65, 64, 1500, 64, 19 );
		}
	}
}

// 해당 텝번호를 통해 앨블럼창을 그립니다.
HTvoid	HTGuild::HT_vGuild_DialogBoxDrawTab(int iTabNo)
{ 
	m_iTabNo = iTabNo;
	
	g_cUIManager->HT_DelButtonControl(_DIALOG_AMBLEM, 1);
	g_cUIManager->HT_DelButtonControl(_DIALOG_AMBLEM, 2);
	g_cUIManager->HT_DelButtonControl(_DIALOG_AMBLEM, 3);
	g_cUIManager->HT_DelButtonControl(_DIALOG_AMBLEM, 4);

	switch(iTabNo)
	{
	case 1:
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 1, 160, 10, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 2, 159, 80, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 3, 159, 150, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 4, 159, 220, 31, 160, 161, 1500, 69, 19);
		break;
	case 2:
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 1, 159, 10, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 2, 160, 80, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 3, 159, 150, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 4, 159, 220, 31, 160, 161, 1500, 69, 19);
		break;
	case 3:
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 1, 159, 10, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 2, 159, 80, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 3, 160, 150, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 4, 159, 220, 31, 160, 161, 1500, 69, 19);
		break;
	case 4:
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 1, 159, 10, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 2, 159, 80, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 3, 159, 150, 31, 160, 161, 1500, 69, 19);
		g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 4, 160, 220, 31, 160, 161, 1500, 69, 19);
		break;
	}

	int max = this->HT_bGuild_GetDialogBoxEmblemMaxButton();

	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < 6; ++j)
		{
			if (max <= (i*6)+j) 
			{
				iTabNo = 5;
				g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j+(i*6), 0);
				g_cUIManager->HT_SetTextureControlColor(UI_WINDOW_EMBLEM, 100+j+(i*6), HT_COLOR(0,0,0,0));
			}

			switch (iTabNo)
			{
			case 1:
				switch(this->m_iSelectWindow)
				{
				case 0:
					g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j+(i*6), UI_GUILD_BACKTEX_N + (j + (i*6)));
					break;
				case 1:
					g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j+(i*6), UI_GUILD_BACKTEX_B + (j + (i*6)));
					break;
				case 2:
					g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j+(i*6), UI_GUILD_BACKTEX_V + (j + (i*6)));
					break;
				case 3:
					g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j+(i*6), UI_GUILD_BACKTEX_S + (j + (i*6)));
					break;
				}
				g_cUIManager->HT_SetTextureControlScale(UI_WINDOW_EMBLEM, 100+j+(i*6), 32, 32, 64, 64);
				g_cUIManager->HT_SetTextureControlColor(UI_WINDOW_EMBLEM, 100+j+(i*6), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			case 2:
				g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j+(i*6), UI_GUILD_TITLETEX + (j +(i*6)));
				g_cUIManager->HT_SetTextureControlScale(UI_WINDOW_EMBLEM, 100+j+(i*6), 32, 32, 32, 32);
				g_cUIManager->HT_SetTextureControlColor(UI_WINDOW_EMBLEM, 100+j+(i*6), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			case 3:
				g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j+(i*6), UI_GUILD_TITLETEX + (j +(i*6) + 42));
				g_cUIManager->HT_SetTextureControlScale(UI_WINDOW_EMBLEM, 100+j+(i*6), 32, 32, 32, 32);
				g_cUIManager->HT_SetTextureControlColor(UI_WINDOW_EMBLEM, 100+j+(i*6), HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			case 4:
				g_cUIManager->HT_SetTextureControlImage(UI_WINDOW_EMBLEM, 100+j+(i*6), 0 );
				g_cUIManager->HT_SetTextureControlScale(UI_WINDOW_EMBLEM, 100+j+(i*6), 32, 32, 32, 32);
				
				switch(this->m_iSelectWindow)
				{
				case 0:
					g_cUIManager->HT_SetTextureControlColor(UI_WINDOW_EMBLEM, 100+j+(i*6), AMBLEM_COLOR[j+(i*6)]);
					break;
				case 1:
					g_cUIManager->HT_SetTextureControlColor(UI_WINDOW_EMBLEM, 100+j+(i*6), AMBLEM_COLOR[j+(i*6)+12]);
					break;
				case 2:
					g_cUIManager->HT_SetTextureControlColor(UI_WINDOW_EMBLEM, 100+j+(i*6), AMBLEM_COLOR[j+(i*6)+32]);
					break;
				case 3:
					g_cUIManager->HT_SetTextureControlColor(UI_WINDOW_EMBLEM, 100+j+(i*6), AMBLEM_COLOR[j+(i*6)+52]);
					break;
				}
				break;
			}
		}
}

// 선택한 엠블럼을 입력받아 윈도우에 그려줍니다. (길드마크 제작창)
HTint HTGuild::HT_bGuild_GetDialogBoxEmblemMaxButton()
{
	int max;
	if ( this->m_iSelectWindow == 0 ) 
	{ 
		switch (m_iTabNo)
		{
		case 1: max = 12; break;
		case 2:	max = 24; break;
		case 3:	max = 0; break;
		case 4:	max = 12; break;
		}
	} 
	else 
	{ 
		switch (m_iTabNo)
		{
		case 1:	max = 20; break;
		case 2: max = 42; break;
		case 3:	max = 42; break;
		case 4:	max = 20; break;
		}
	}

	return max;
}

// 선택한 엠블럼을 입력받아 윈도우에 그려줍니다. (길드마크 제작창)
HTvoid	HTGuild::HT_bGuild_DialogBoxDrawEmblem(int iIndex)
{
	int max = this->HT_bGuild_GetDialogBoxEmblemMaxButton();
	if (iIndex >= max) return;

	// 현재 설정된 텝에 따라 인덱스를 저장합니다.
	switch(m_iTabNo)
	{
	case 1:	m_iBackIndex = iIndex;	break;
	case 2:	m_iTitleIndex = iIndex;	break;
	case 3:	m_iTitleIndex = iIndex+42;	break;
	case 4:	m_iBackColor = iIndex;	break;
	}

	// 조합을 그려 길드마크를 완성합니다.
	switch(this->m_iSelectWindow)
	{
	case 0:
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 11, UI_GUILD_EMBLEMTEX_N + m_iBackIndex );
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 12, UI_GUILD_BACKTEX_N + m_iBackIndex );
		g_cUIManager->HT_SetTextureControlColor( UI_WINDOW_EMBLEM, 11, AMBLEM_COLOR[m_iBackColor]);
		break;
	case 1:
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 11, UI_GUILD_EMBLEMTEX_B + m_iBackIndex );
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 12, UI_GUILD_BACKTEX_B + m_iBackIndex );
		g_cUIManager->HT_SetTextureControlColor( UI_WINDOW_EMBLEM, 11, AMBLEM_COLOR[m_iBackColor+12]);
		break;
	case 2:
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 11, UI_GUILD_EMBLEMTEX_V + m_iBackIndex );
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 12, UI_GUILD_BACKTEX_V + m_iBackIndex );
		g_cUIManager->HT_SetTextureControlColor( UI_WINDOW_EMBLEM, 11, AMBLEM_COLOR[m_iBackColor+32]);
		break;
	case 3:
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 11, UI_GUILD_EMBLEMTEX_S + m_iBackIndex );
		g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 12, UI_GUILD_BACKTEX_S + m_iBackIndex );
		g_cUIManager->HT_SetTextureControlColor( UI_WINDOW_EMBLEM, 11, AMBLEM_COLOR[m_iBackColor+52]);
		break;
	}
	g_cUIManager->HT_SetTextureControlImage( UI_WINDOW_EMBLEM, 13, UI_GUILD_TITLETEX + m_iTitleIndex );
}

// 엠블램 선택시 처리
HTvoid HTGuild::HT_bGuild_DialogBoxEmblemSelect()
{
	// 본인의 주신에 따라 인덱스값 달리 계산
	if (this->m_iSelectWindow != 0)
	{
		switch( g_oMainCharacterInfo.byTrimuriti )
		{
			case TRIMURITI_BRAHMA:
				m_iBackIndex += 12;
				m_iBackColor += 12;
				break;
			case TRIMURITI_VISHNU: 
				m_iBackIndex += 32;
				m_iBackColor += 32;
				break;
			case TRIMURITI_SIVA: 
				m_iBackIndex += 52;
				m_iBackColor += 52;
				break;
			default: 
				break;;
		}
	}

	m_dwGuild_EmblemID = g_pEngineHandler->HT_dwConvertGuildMarkIdenty(m_iBackIndex+1, m_iTitleIndex+1, m_iBackColor+1);
	g_cUIManager->HT_HideWindow(_DIALOG_AMBLEM);
	
	//	길드마크 생성 요청
	if (this->m_iSelectWindow == 0)
		this->HT_vNetWork_CSP_MSG_GuildUpdateMark( 1 );
	else //	유료 길드 마크는 다음을 호출
		this->HT_vNetWork_CSP_MSG_GuildUpdateMark( 2 );

	// NPC 대화내용 변경
	g_cNPCControl->HT_vNPCControl_Create_GuildMark();
}

// 윈도우 제어 시도시 호출 (이곳에서 입력장치로부터 들어온 정보를 처리한다.)
void HTGuild::HT_vGuild_InputCheckForEmblemSelecting(int iAction, int iTarget, int iTargetID)
{
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:	// 버튼의 경우 처리
		switch(iTargetID)
		{
		case -2:// 백그라운드 다운시
			break;
		case -1:// 종료버튼
		case 201:	// 취소버튼
			g_cUIManager->HT_HideWindow(_DIALOG_AMBLEM);
			break;
		case 200: // 확인버튼
			g_cGuildSystem->HT_bGuild_DialogBoxEmblemSelect();
			break;
		case 1:	// 텝 버튼 = 배경문양
		case 2: // 문양
		case 3: // 문양
		case 4: // 배경색
			g_cGuildSystem->HT_vGuild_DialogBoxDrawTab(iTargetID);
			break;
		}

		if (iTargetID >= 100 && iTargetID < 142)	// 앰블럼 버튼 클릭시
			g_cGuildSystem->HT_bGuild_DialogBoxDrawEmblem(iTargetID-100);
		break;
	}
}


//	입력 메세지 처리
//	AshramInfo
void HTGuild::HT_vGuild_InputCheckForAshramInfo(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_ASHRAMINFO);
		}
		//	Button 구성인원
		else if( iTargetID == 20 )
		{
			HTint iPosX, iPosY;
			g_cUIManager->HT_GetWindowPos( _DIALOG_ASHRAMINFO, iPosX, iPosY );
			g_cUIManager->HT_HideWindow( _DIALOG_ASHRAMINFO );
			g_cUIManager->HT_ShowWindow( _DIALOG_ASHRAMMEMBERLISET );
			g_cUIManager->HT_MoveWindow( _DIALOG_ASHRAMMEMBERLISET, iPosX, iPosY );
		}
		//	Button 홈피제작
		else if( iTargetID == 21 )
		{
			CHTString strString;
			if ( g_cGuildSystem->m_oGuildInfo.GuildID != 0 && g_cGuildSystem->m_byGuild_GuilAuthority == GUILD_AUTHORITY_MAHARAJA )
			{
				if ( g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenWarning, &strString ) )
				{
					// 해당 블로그가 전체 화면으로 활성화 됩니다. 계속하시겠습니까?
					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 1 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_MAKEBLOG;
				}
			}
			else
			{
				if ( g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogMakeErr, &strString ) )
				{
					// 아쉬람에 가입되어 있지 않거나 마하라자가 아닌 경우 아쉬람 블로그 제작을 할 수 없습니다.
					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 0 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_NONE;
				}
			}
		}
		//	Button 홈피입장
		else if( iTargetID == 22 )
		{
			CHTString strString;
			if ( g_cMainCharacter->m_iGuildSerial > 0 )
			{
				if ( g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenWarning, &strString ) )
				{
					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 1 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_ENTERBLOG;
				}
			}
			else
			{
				if ( g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogErr, &strString ) )
				{
					// 아쉬람에 가입되어 있지 않은 경우 아쉬람 블로그에 접근할 수 없습니다.
					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 0 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_NONE;
				}
			}						
		}
		//	Button 개인블로그
		else if( iTargetID == 27 )
		{
			CHTString strString;
			if ( g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenWarning, &strString ) )
			g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 1 );
			//	MessageBox Type
			g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_PERSONALBLOG;
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		//	확인
		if( iTargetID == 2 )
		{
			//	MessageBox Type
			if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_MAKEBLOG )
			{
				HTint iServer = 0;
				if ( g_gServerType == SERVERTYPE_TEST ) iServer = 0;	// Test Server : 0
				else
				{
					// Main Server : 졸라 하드 코딩
					// 마나스 - 1, 디야나 - 2, 크리야 - 3, 아트만 - 4, 수리야 - 5
					if ( g_strSelectServerName == _T("마나스") )		{ iServer = 1; }
					else if ( g_strSelectServerName == _T("디야나") )	{ iServer = 2; }
					else if ( g_strSelectServerName == _T("크리야") )	{ iServer = 3; }
					else if ( g_strSelectServerName == _T("아트만") )	{ iServer = 4; }
					else if ( g_strSelectServerName == _T("수리야") )	{ iServer = 5; }
					else { iServer = 6; }
				}

				CHTString strWeb( _T("http://www.hanbiton.com/h_game/h_tantra/guild_make.aspx") );
				//CHTString strWeb( _T("http://login.hanbiton.com/h_help/tantra_login.aspx") );
				CHTString strWebParam;
				{
					strWebParam.HT_szFormat( _T("returnurl=http://home.hanbiton.com/guild/game.aspx&GuildID=%d&World=%d&nm_game=tantra&userid=%s&userpw=%s"),
							g_cGuildSystem->m_oGuildInfo.GuildID, 
							iServer,
							(HTtchar*)g_strLoginID, 
							(HTtchar*)g_strLgoinPasswordMD5 );
					//strWebParam.HT_szFormat( 
					//				_T("returnurl=http://home.hanbiton.com/h_game/h_space/h_make/make01.aspx&nm_game=tantra&userid=%s&userpw=%s&nm_master=%s&nm_ashiram=%s&no_ashiram=%d&no_server=%d"),
					//				(HTtchar*)g_strLoginID, (HTtchar*)g_strLgoinPasswordMD5,	// Log In 정보
					//				(HTtchar*)g_strLoginID,										// 마스터 아이디 (nm_master)
					//				(HTtchar*)g_cGuildSystem->HT_strGuild_GetGuildName(),		// 아쉬람명 (nm_ashiram)
					//				g_cMainCharacter->m_iGuildSerial,							// 아쉬람고유번호 (no_ashiram)
					//				iServer );													// 서버번호 (no_server)
				}

				HTRESULT hResult = HT_OK;
				if ( HT_FAILED( hResult = g_pEngineHandler->HT_hrOpenWebWithPost( g_hWnd, strWeb, strWebParam, 10 ) ) )
				{
					CHTString strString;

					// 블로그 서버가 응답하지 않습니다. 잠시 후에 다시 시도해 주시기 바랍니다.
					// 블로그 서버에 연결하기 위한 프로그램 초기화에 실패했습니다.
					// 블로그 서버 연결 초기화에 실패했습니다.
					// 블로그 서버 연결을 위한 프로그램 검색에 실패했습니다.
					// 블로그 서버가 알 수 없는 오류를 알려왔습니다.
					if ( hResult == HT_FAIL )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError1, &strString );
					else if ( hResult == 1 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError2, &strString );
					else if ( hResult == 2 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError3, &strString );
					else if ( hResult == 3 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError4, &strString );
					else						g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError5, &strString );

					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 0 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_NONE;
				}
			}
			else if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_ENTERBLOG )
			{
				HTint iServer = 0;
				if ( g_gServerType == SERVERTYPE_TEST ) iServer = 0;	// Test Server : 0
				else
				{
					// Main Server : 졸라 하드 코딩
					// 마나스 - 1, 디야나 - 2, 크리야 - 3, 아트만 - 4, 수리야 - 5
					if ( g_strSelectServerName == _T("마나스") )		{ iServer = 1; }
					else if ( g_strSelectServerName == _T("디야나") )	{ iServer = 2; }
					else if ( g_strSelectServerName == _T("크리야") )	{ iServer = 3; }
					else if ( g_strSelectServerName == _T("아트만") )	{ iServer = 4; }
					else if ( g_strSelectServerName == _T("수리야") )	{ iServer = 5; }
					else { iServer = 6; }
				}

				HTRESULT hResult = HT_OK;
				CHTString strWeb( _T("http://www.hanbiton.com/h_game/h_tantra/guild_enter.aspx") );
				//CHTString strWeb( _T("http://login.hanbiton.com/h_help/tantra_login.aspx") );
				CHTString strWebParam;
				{
						strWebParam.HT_szFormat( _T("returnurl=http://home.hanbiton.com/guild/game.aspx&GuildID=%d&World=%d&nm_game=tantra&userid=%s&userpw=%s"),
						g_cGuildSystem->m_oGuildInfo.GuildID, 
						iServer,
						(HTtchar*)g_strLoginID, 
						(HTtchar*)g_strLgoinPasswordMD5 );	// Log In 정보
						
						//strWebParam.HT_szFormat( _T("returnurl=http://home.hanbiton.com/guild/game.aspx&nm_game=tantra&userid=%s&userpw=%s&nm_ashiram=%s&no_ashiram=%d&no_server=%d"),
						//			(HTtchar*)g_strLoginID, (HTtchar*)g_strLgoinPasswordMD5,	// Log In 정보
						//			(HTtchar*)g_cGuildSystem->HT_strGuild_GetGuildName(),		// 아쉬람명 (nm_ashiram)
						//			g_cMainCharacter->m_iGuildSerial,							// 아쉬람고유번호 (no_ashiram)
						//			iServer );													// 서버번호 (no_server)
				}
				
				if ( HT_FAILED( hResult = g_pEngineHandler->HT_hrOpenWebWithPost( g_hWnd, strWeb, strWebParam, 10 ) ) )
				{
					CHTString strString;
					if ( hResult == HT_FAIL )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError1, &strString );
					else if ( hResult == 1 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError2, &strString );
					else if ( hResult == 2 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError3, &strString );
					else if ( hResult == 3 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError4, &strString );
					else						g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError5, &strString );
					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 0 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_NONE;
				}
			}
			else if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_PERSONALBLOG )
			{
				HTRESULT hResult = HT_OK;
				CHTString strWeb( _T("http://www.hanbiton.com/h_game/h_tantra/minibl.aspx") );
				//CHTString strWeb( _T("http://login.hanbiton.com/h_help/blog_login.aspx") );

				CHTString strWebParam;
				strWebParam.HT_szFormat( _T("returnurl=http://home.hanbiton.com/minible/home/main.aspx&nm_game=tantra&userid=%s&userpw=%s&id=%s"), (HTtchar*)g_strLoginID, (HTtchar*)g_strLgoinPasswordMD5, (HTtchar*)g_strLoginID );	// 사용자 아이디 (userid)

				if ( HT_FAILED( hResult = g_pEngineHandler->HT_hrOpenWebWithPost( g_hWnd, strWeb, strWebParam, 10 ) ) )
				{
					CHTString strString;

					if ( hResult == HT_FAIL )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError1, &strString );
					else if ( hResult == 1 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError2, &strString );
					else if ( hResult == 2 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError3, &strString );
					else if ( hResult == 3 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError4, &strString );
					else						g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError5, &strString );

					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 0 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_NONE;
				}
			}
			else if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_OTHERBLOG )
			{
				CHTString strClickAccount;
				if ( HT_SUCCEED( g_cOtherObjectSystem->HT_hrGetCharacterAccount( g_iBlogClickedChar, &strClickAccount) ) )
				{
					HTRESULT hResult = HT_OK;
					CHTString strWeb( _T("http://www.hanbiton.com/h_game/h_tantra/minibl.aspx") );
					//CHTString strWeb( _T("http://login.hanbiton.com/h_help/blog_login.aspx") );

					CHTString strWebParam;
					strWebParam.HT_szFormat( _T("returnurl=http://home.hanbiton.com/minible/home/main.aspx&nm_game=tantra&userid=%s&userpw=%s&id=%s"), (HTtchar*)g_strLoginID, (HTtchar*)g_strLgoinPasswordMD5, (HTtchar*)strClickAccount );	// 사용자 아이디 (userid)

					if ( HT_FAILED( hResult = g_pEngineHandler->HT_hrOpenWebWithPost( g_hWnd, strWeb, strWebParam, 10 ) ) )
					{
						CHTString strString;
						if ( hResult == HT_FAIL )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError1, &strString );
						else if ( hResult == 1 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError2, &strString );
						else if ( hResult == 2 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError3, &strString );
						else if ( hResult == 3 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError4, &strString );
						else						g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError5, &strString );
						g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 0 );
						//	MessageBox Type
						g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_NONE;
					}
				}
			}
			else if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_PERSONALBOARD )
			{
				HTRESULT hResult = HT_OK;
				CHTString strWeb( _T("http://www.hanbiton.com/h_game/h_tantra/guild.aspx") );
				//CHTString strWeb( _T("http://login.hanbiton.com/h_help/game_login.aspx") );

				CHTString strWebParam;
				strWebParam.HT_szFormat( _T("returnurl=http://home.hanbiton.com/h_game/h_space/main.aspx&nm_game=tantra&userid=%s&userpw=%s"), (HTtchar*)g_strLoginID, (HTtchar*)g_strLgoinPasswordMD5 );	// 사용자 아이디 (userid)
				if ( HT_FAILED( hResult = g_pEngineHandler->HT_hrOpenWebWithPost( g_hWnd, strWeb, strWebParam, 10 ) ) )
				{
					CHTString strString;
					if ( hResult == HT_FAIL )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError1, &strString );
					else if ( hResult == 1 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError2, &strString );
					else if ( hResult == 2 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError3, &strString );
					else if ( hResult == 3 )	g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError4, &strString );
					else						g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenError5, &strString );
					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 0 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_NONE;
				}
			}
            //	연합 아쉬람 요청
			else if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_REQALLIANCE )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg2, &strString, g_cGuildSystem->m_strAshuramGuildJoin_SendCharName.HT_szGetString() );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				// 서버에 패킷 전송하기
				g_cGuildSystem->HT_vGuildNet_CSP_AshuramGuild(1,1,0);
				// 수락
				g_cGuildSystem->m_byAshuramGuildJoin_ResponseReason = 1;
			}
			//	연합 아쉬람 요청에 대한 응답
			else if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_RECIVEALLIANCE )
			{
				// 서버에 패킷 전송하기 (수락함)
				g_cGuildSystem->HT_vGuildNet_CSP_AshuramGuild(1,1,1);
				// 수락
				g_cGuildSystem->m_byAshuramGuildJoin_ResponseReason = 1;
			}
		}
		else if( iTargetID == 3 )
		{
			//	연합 아쉬람 요청
			if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_REQALLIANCE )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg8, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				g_cGuildSystem->m_byAshuramGuildJoin_ResponseReason = 0;	// 취소
			}
			//	연합 아쉬람 요청에 대한 응답
			else if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_RECIVEALLIANCE )
			{
				// 서버에 패킷 전송하기 (거부함)
				g_cGuildSystem->HT_vGuildNet_CSP_AshuramGuild(1,1,5);

				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg8, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
			}
		}
	}
}
//	AshramMemberList
void HTGuild::HT_vGuild_InputCheckForAshramMemberList(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_ASHRAMMEMBERLISET);
		}
		//	Button 멤버
		else if( iTargetID>=10 && iTargetID<20 )
		{
			g_cGuildSystem->m_strGuild_ListSelectdName = g_cUIManager->HT_GetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, iTargetID );
			//	귓속말 상태로 만들어 주고..
			g_cChatting->HT_vChatting_SetWisper( g_cGuildSystem->m_strGuild_ListSelectdName );
		}
		//	Button 아쉬람정보
		else if( iTargetID == 50 )
		{
			HTint iPosX, iPosY;
			g_cUIManager->HT_GetWindowPos( _DIALOG_ASHRAMMEMBERLISET, iPosX, iPosY );
			g_cUIManager->HT_HideWindow( _DIALOG_ASHRAMMEMBERLISET );
			g_cUIManager->HT_ShowWindow( _DIALOG_ASHRAMINFO );
			g_cUIManager->HT_MoveWindow( _DIALOG_ASHRAMINFO, iPosX, iPosY );
		}
		//	Button 가입
		else if( iTargetID == 51 )
		{
			g_cGuildSystem->m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_JOIN;
			//	아이콘 모양이 바뀌게 설정해 준다.
		}
		//	Button 탈퇴
		else if( iTargetID == 52 )
		{
			if( !g_cGuildSystem->m_strGuild_GuildName.HT_bIsEmpty() )
			{
				CHTString strTemp;
				//	길드마스터이고, 선택한 이름이  같을때
				if( !g_cGuildSystem->m_strGuild_ListSelectdName.HT_bIsEmpty() &&
					g_cGuildSystem->m_byGuild_GuilAuthority == GUILD_AUTHORITY_MAHARAJA )
				{
					//	선택한 이름이 나자신이 아닐때
					if( g_cGuildSystem->m_strGuild_ListSelectdName.HT_iStringCompare( g_oMainCharacterInfo.szCharName ) != 0 )
					{
						g_cGuildSystem->m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_EXPEL;
						// %s 님을 길드에서 제명 하시겠습니까?
						HT_g_Script_SetMessage( eMsgGuildReqDelMemberQuestion, &strTemp, g_cGuildSystem->m_strGuild_ListSelectdName.HT_szGetString() );
						g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, strTemp.HT_szGetString(), 1 );
					}
					else
					{
						// 연합아쉬람을 맺은 상태에선 탈퇴 불가
						if (strcmp(g_cGuildSystem->m_strAlliedGuildName[0].HT_szGetString(), " ") != 0)
						{
							HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg13, &strTemp, g_cGuildSystem->m_strAshuramGuildJoin_SendCharName.HT_szGetString() );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
						}
						else
						{
							g_cGuildSystem->m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_DESTROY;
							// 정말 길드에서 탈퇴하시렵니까?
							HT_g_Script_SetMessage( eMsgGuildReqSecessionQuestion, &strTemp, _T("") );
							g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, strTemp.HT_szGetString(), 1 );
						}
					}
				}
				else
				{
					if( g_cGuildSystem->m_byGuild_GuilAuthority == GUILD_AUTHORITY_MAHARAJA )
					{
						// 연합 아쉬람을 맺은 상태에선 탈퇴 불가
						if (strcmp(g_cGuildSystem->m_strAlliedGuildName[0].HT_szGetString(), " ") != 0)
						{
							HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg13, &strTemp, g_cGuildSystem->m_strAshuramGuildJoin_SendCharName.HT_szGetString() );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
						}
						else
						{
							g_cGuildSystem->m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_DESTROY;
							// 정말 길드에서 탈퇴하시렵니까?
							HT_g_Script_SetMessage( eMsgGuildReqSecessionQuestion, &strTemp, _T("") );
							g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, strTemp.HT_szGetString(), 1 );
						}
					}
					else
					{
						g_cGuildSystem->m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_SECEDE;
						// 정말 길드에서 탈퇴하시렵니까?
						HT_g_Script_SetMessage( eMsgGuildReqSecessionQuestion, &strTemp, _T("") );
						g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, strTemp.HT_szGetString(), 1 );
					}
				}
			}
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		//	확인
		if( iTargetID == 2 )
		{
			switch( g_cGuildSystem->m_byGuild_ConfirmGrade )
			{
				//	가입요청을 알려옴
				case GUILDTYPE_CONFIRM_JOINNOTIFY :
					//	길드 참여 승인
					g_cGuildSystem->HT_vNetWork_CSP_CNFGuild();
					break;
				//	탈퇴, 제명, 해체
				case GUILDTYPE_CONFIRM_SECEDE :
				case GUILDTYPE_CONFIRM_EXPEL :
				case GUILDTYPE_CONFIRM_DESTROY :
					g_cGuildSystem->HT_vNetWork_CSP_Remove_GuildMember();
					break;
			}
		}
		//	확인 단계
		g_cGuildSystem->m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_NONE;
	}
	else if( iTarget == UI_TARGET_SCROLLBAR )
	{
		g_cGuildSystem->HT_vGuild_Display();
	}
}
//	AshramCago
void HTGuild::HT_vGuild_InputCheckForAshramCago(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_ASHRAMCAGO);
		}
		else if( iTargetID == 1 )
		{
			if( g_cUIManager->m_bSlotBoxMoving )
				g_cUIManager->HT_RefuseSlotImageMoving();
			g_cGuildSystem->m_iPrevPageOfAshramCargo = g_cGuildSystem->m_iPageOfAshramCargo;
			g_cGuildSystem->m_iPageOfAshramCargo = 0;
			g_cGuildSystem->HT_vAshram_CSPAshramItem();
		}
		else if( iTargetID == 2 )
		{
			if( g_cUIManager->m_bSlotBoxMoving )
				g_cUIManager->HT_RefuseSlotImageMoving();
			g_cGuildSystem->m_iPrevPageOfAshramCargo = g_cGuildSystem->m_iPageOfAshramCargo;
			g_cGuildSystem->m_iPageOfAshramCargo = 1;
			g_cGuildSystem->HT_vAshram_CSPAshramItem();
		}
		else if( iTargetID == 3 )
		{
			if( g_cUIManager->m_bSlotBoxMoving )
				g_cUIManager->HT_RefuseSlotImageMoving();
			g_cGuildSystem->m_iPrevPageOfAshramCargo = g_cGuildSystem->m_iPageOfAshramCargo;
			g_cGuildSystem->m_iPageOfAshramCargo = 2;
			g_cGuildSystem->HT_vAshram_CSPAshramItem();
		}
		else if( iTargetID == 4 )
		{
			g_cGuildSystem->m_iPageOfAshramCargo = 2;
		}
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		unsigned int iWIndex, iCIndex;
		int iTextureId;
		g_cUIManager->HT_GetSlotBoxControlSourInfo( iWIndex, iCIndex, iTextureId );

		//	아이콘을 들고 엉뚱한 곳에 클릭했을때
		if( iTargetID == -1 || iTargetID == -2 )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
		//	아이콘을 클릭하는 순간에도 이벤트가 발생해 줘야 함 그래서 클릭한 아이콘을 팝업할수 있는지 확인하는 절차가 필요함 일단은 여기다 둔다.
		if( HT_FAILED( g_cItemControl->HT_bItemControl_ButtonCheck_SwitchOn( iWIndex, iCIndex, _DIALOG_ASHRAMCAGO, iTargetID ) ) )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return; 
		}
		if( HT_FAILED( g_cItemControl->HT_vItemControl_ButtonCheck_SwitchOff( _DIALOG_ASHRAMCAGO, iTargetID ) ) )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
		//	기존의 슬롯에 아이템이 있으면 덮어지지 않게 처리
		if( g_cItemSystem->HT_dwItemSystem_ItemSerch(ITEM_LOCATION_ASHRAMCARGO, ITEM_LOCATION_ASHRAMCARGO_BAG1, iTargetID) == 0 )
		{
			g_cUIManager->HT_AcceptSlotImageMoving();
			g_cUIManager->HT_SetSlotImage( _DIALOG_ASHRAMCAGO, iTargetID , 0 );
		}
		else
		{
			g_cUIManager->HT_AcceptSlotImageMoving();
		}
	}
}
//	Sanction Ashram Cago
void HTGuild::HT_vGuild_InputCheckForSanctionAshramCago(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		CHTString strMessage;
		CHTString strTemp;

		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SANCTIONASHCAGO);
		}
		else if( iTargetID == 1 )
		{
			//	현재 보유한 루피아 체크
			if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < 2000000 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgAshramFaildShortOfRupia, &strMessage, _T(""), _T("") );	//	루피아가 부족하여 요청하신 작업을 수행할수 없습니다.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage );
				return;
			}
			//	Ashram Cargo Extence Type
			g_cGuildSystem->m_byAshramCargoExtenceType = 1;
			g_cUIManager->HT_SetScriptMessage( eMsgAshramReqNeedRupia, &strMessage, _T(""), _T("") );	//	선택하신 아쉬람 창고는 200만 루피아가 필요합니다.\n 정말 사용하시겠습니까?
			strTemp.HT_szFormat( strMessage, 200 );
			g_cUIManager->HT_MessageBox( _DIALOG_SANCTIONASHCAGO, strTemp, 1 );
		}
		else if( iTargetID == 2 )
		{
			//	현재 보유한 루피아 체크
			if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < 3000000 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgAshramFaildShortOfRupia, &strMessage, _T(""), _T("") );	//	루피아가 부족하여 요청하신 작업을 수행할수 없습니다.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage );
				return;
			}
			//	Ashram Cargo Extence Type
			g_cGuildSystem->m_byAshramCargoExtenceType = 2;
			g_cUIManager->HT_SetScriptMessage( eMsgAshramReqNeedRupia, &strMessage, _T(""), _T("") );	//	선택하신 아쉬람 창고는 300만 루피아가 필요합니다.\n 정말 사용하시겠습니까?
			strTemp.HT_szFormat( strMessage, 300 );
			g_cUIManager->HT_MessageBox( _DIALOG_SANCTIONASHCAGO, strTemp, 1 );
		}
		else if( iTargetID == 3 )
		{
			//	현재 보유한 루피아 체크
			if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < 3500000 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgAshramFaildShortOfRupia, &strMessage, _T(""), _T("") );	//	루피아가 부족하여 요청하신 작업을 수행할수 없습니다.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage );
				return;
			}
			//	Ashram Cargo Extence Type
			g_cGuildSystem->m_byAshramCargoExtenceType = 3;
			g_cUIManager->HT_SetScriptMessage( eMsgAshramReqNeedRupia, &strMessage, _T(""), _T("") );	//	선택하신 아쉬람 창고는 350만 루피아가 필요합니다.\n 정말 사용하시겠습니까?
			strTemp.HT_szFormat( strMessage, 350 );
			g_cUIManager->HT_MessageBox( _DIALOG_SANCTIONASHCAGO, strTemp, 1 );
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		//	확인 버튼
		if( iTargetID == 2 )
		{
			if( g_cGuildSystem->m_byAshramCargoExtenceType == 1 )
				g_cGuildSystem->HT_vAshram_CSPGuildCargoTimeExtension( 1 );
			else if( g_cGuildSystem->m_byAshramCargoExtenceType == 2 )
				g_cGuildSystem->HT_vAshram_CSPGuildCargoTimeExtension( 2 );
			else if( g_cGuildSystem->m_byAshramCargoExtenceType == 3 )
				g_cGuildSystem->HT_vAshram_CSPGuildCargoTimeExtension( 3 );
		}
	}
}
//	SetLevel Ashram Cago
void HTGuild::HT_vGuild_InputCheckForSetLevelAshramCago(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_SETLEVELASHCAGO);
		}
		//	창고1 권한
		else if( iTargetID == 10 || iTargetID == 11 || iTargetID == 12 || iTargetID == 13 )
		{
			HTbyte byLevel;
			HTint iLevel = iTargetID-10;
			//for( HTint i=0 ; i<4 ; i++ )
			//{
			//	if( iLevel>=i )		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_SETLEVELASHCAGO, 10+(0*4)+i, HT_TRUE );
			//	else				g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_SETLEVELASHCAGO, 10+(0*4)+i, HT_FALSE );
			//}
			if( iLevel == 0 )		byLevel = eGuildSubMaster;
			else if( iLevel == 1 )	byLevel = eGuildThird;
			else if( iLevel == 2 )	byLevel = eGuildForth;
			else if( iLevel == 3 )	byLevel = eGuildMember;
			g_cGuildSystem->HT_vAshram_CSPSetLevelAshramCargo( 0, byLevel );
		}
		//	창고2 권한
		else if( iTargetID == 14 || iTargetID == 15 || iTargetID == 16 || iTargetID == 17 )
		{
			HTbyte byLevel;
			HTint iLevel = iTargetID-14;
			//for( HTint i=0 ; i<4 ; i++ )
			//{
			//	if( iLevel>=i )		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_SETLEVELASHCAGO, 10+(1*4)+i, HT_TRUE );
			//	else				g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_SETLEVELASHCAGO, 10+(1*4)+i, HT_FALSE );
			//}
			if( iLevel == 0 )		byLevel = eGuildSubMaster;
			else if( iLevel == 1 )	byLevel = eGuildThird;
			else if( iLevel == 2 )	byLevel = eGuildForth;
			else if( iLevel == 3 )	byLevel = eGuildMember;
			g_cGuildSystem->HT_vAshram_CSPSetLevelAshramCargo( 1, byLevel );
		}
		//	창고3 권한
		else if( iTargetID == 18 || iTargetID == 19 || iTargetID == 20 || iTargetID == 21 )
		{
			HTbyte byLevel;
			HTint iLevel = iTargetID-18;
			//for( HTint i=0 ; i<4 ; i++ )
			//{
			//	if( iLevel>=i )		g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_SETLEVELASHCAGO, 10+(2*4)+i, HT_TRUE );
			//	else				g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_SETLEVELASHCAGO, 10+(2*4)+i, HT_FALSE );
			//}
			if( iLevel == 0 )		byLevel = eGuildSubMaster;
			else if( iLevel == 1 )	byLevel = eGuildThird;
			else if( iLevel == 2 )	byLevel = eGuildForth;
			else if( iLevel == 3 )	byLevel = eGuildMember;
			g_cGuildSystem->HT_vAshram_CSPSetLevelAshramCargo( 2, byLevel );
		}
	}
}


// 길드창에 아쉬람 및 주신마크 붙이기
HTvoid HTGuild::HT_vGuild_DialogBoxActiveOutput(void)
{
	HTint iToBmp1, iToBmp2;

	g_cUIManager->HT_SetTextureControlColor( _DIALOG_ASHRAMINFO, 23, HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f));
	g_cUIManager->HT_SetTextureControlColor( _DIALOG_ASHRAMINFO, 24, HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f));
	g_cUIManager->HT_SetTextureControlColor( _DIALOG_ASHRAMINFO, 25, HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f));
	g_cUIManager->HT_SetTextureControlColor( _DIALOG_ASHRAMINFO, 26, HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f));

	if (g_oMainCharacterInfo.byTrimuriti == 0) return;

	if ( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA ) iToBmp1 = 23659;
	else if ( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU ) iToBmp1 = 23658;
	else if ( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA ) iToBmp1 = 23660;
	
	g_cUIManager->HT_SetTextureControlImage( _DIALOG_ASHRAMINFO, 23, iToBmp1 );
	g_cUIManager->HT_SetTextureControlScale( _DIALOG_ASHRAMINFO, 23, 32, 32, 32, 32);

	if (g_bGuildMarkShow == HT_FALSE || m_iEmblem == -1 || m_iTitle == -1 || m_iColor == -1 ) return;

	if( m_iEmblem > 12 )
	{
		if ( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_BRAHMA )
			iToBmp1 = UI_GUILD_EMBLEMTEX_B + (m_iEmblem - 12), iToBmp2 = UI_GUILD_BACKTEX_B + (m_iEmblem - 12);
		else if ( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_VISHNU )
			iToBmp1 = UI_GUILD_EMBLEMTEX_V + (m_iEmblem - 12), iToBmp2 = UI_GUILD_BACKTEX_V + (m_iEmblem - 12);
		else if ( g_oMainCharacterInfo.byTrimuriti == TRIMURITI_SIVA )
			iToBmp1 = UI_GUILD_EMBLEMTEX_S + (m_iEmblem - 12), iToBmp2 = UI_GUILD_BACKTEX_S + (m_iEmblem - 12);
	}
	else
	{
		iToBmp1 = UI_GUILD_EMBLEMTEX_N + m_iEmblem,	iToBmp2 = UI_GUILD_BACKTEX_N + m_iEmblem;
	}

	g_cUIManager->HT_SetTextureControlImage( _DIALOG_ASHRAMINFO, 24, iToBmp1-1 );
	g_cUIManager->HT_SetTextureControlImage( _DIALOG_ASHRAMINFO, 25, iToBmp2-1 );
	g_cUIManager->HT_SetTextureControlImage( _DIALOG_ASHRAMINFO, 26, UI_GUILD_TITLETEX + m_iTitle - 1 );
	g_cUIManager->HT_SetTextureControlScale( _DIALOG_ASHRAMINFO, 24, 64, 64, 64, 64);
	g_cUIManager->HT_SetTextureControlScale( _DIALOG_ASHRAMINFO, 25, 64, 64, 64, 64);
	g_cUIManager->HT_SetTextureControlScale( _DIALOG_ASHRAMINFO, 26, 32, 32, 32, 32);
	g_cUIManager->HT_SetTextureControlColor( _DIALOG_ASHRAMINFO, 24, AMBLEM_COLOR[m_iColor-1]);
	g_cUIManager->HT_SetTextureControlColor( _DIALOG_ASHRAMINFO, 25, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f));
	g_cUIManager->HT_SetTextureControlColor( _DIALOG_ASHRAMINFO, 26, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//	대화상자 활성화/비활성화
HTvoid HTGuild::HT_vGuild_DialogBoxActive()
{
	//	GM이면 스킵
	if( g_oMainCharacterInfo.snTribe == 0x09 )
		return;

	//	구성요소 창이 열려 있으면 구성요소 창을 닫고
	if( g_cUIManager->HT_isShowWindow( _DIALOG_ASHRAMMEMBERLISET ) )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_ASHRAMMEMBERLISET );
	}
	//	길드 정보창이 열려 있으면 길드 정보창을 닫는다.
	else if( g_cUIManager->HT_isShowWindow( _DIALOG_ASHRAMINFO ) )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_ASHRAMINFO );
	}
	else
	{
		g_cUIManager->HT_ShowWindow( _DIALOG_ASHRAMINFO );
		this->HT_vGuild_DialogBoxActiveOutput();
	}
}
//	대화상자 비활성화
HTvoid HTGuild::HT_vGuild_DialogBoxAntiActive()
{
}

//	창설
HTvoid HTGuild::HT_vGuild_Create()
{
	//	바난타에게서만 길드를 창설 할 수 있도록
	if( g_cNPCControl->HT_bNPCControl_IsGuilCreateStep() == HT_TRUE )
	{
		if( m_strGuild_GuildName.HT_bIsEmpty() )							//	길드가 없을때만...
		{
			//	Set Language
			g_cChatting->HT_vChatting_SetOpenMessageItem( 1, 0, 0 );
		}
		else
		{
			CHTString szMessage;
			// 길드에 가입되어 있지 않을때만 창설 가능합니다.
			HT_vGuild_SetMessage( eMsgGuildCreateOtherJoinErr, &szMessage );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		}
	}
}

// 길드 마크 생성하는 창 띄우기
HTvoid HTGuild::HT_vGuild_AmblemMakeActive()
{
	if( m_strGuild_GuildMasterName.HT_iStringCompare( g_oMainCharacterInfo.szCharName ) == 0 && //	길드 마스터가 아니면 리턴
		g_cEquipInventory->HT_iEquipInventory_GetPCMoney() >= GUILD_MARK_NEED_MONEY )	//	돈 체크_루피아 3000000 이상일때만 생성가능
	{
		this->m_iSelectWindow = 0;	// 일반 아쉬람 만들기 창으로 셋팅
		this->HT_vGuild_DialogBoxDrawTab(1);
		this->HT_bGuild_DialogBoxDrawEmblem(0);
		g_cUIManager->HT_ShowWindow(_DIALOG_AMBLEM);
	}
	else
	{
		CHTString szMessage;
		// 루피아 3000000이상일때와 길드마스터만이 길드마크를 제작할수 있습니다.
		HT_vGuild_SetMessage( eMsgGuildMarkConditionErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
	}
}

//	가입
HTRESULT HTGuild::HT_vGuild_JoinGuild( HTint iObjectID )
{
	//	길드 가입 버튼을 누른 상태가 아니면 스킵
	if( m_byGuild_ConfirmGrade != GUILDTYPE_CONFIRM_JOIN )
		return HT_FAIL;
		
	//	내가 길드장이 아니면 스킵
	byte byAuthority =  g_cGuildSystem->HT_byGuild_GetAuthority();
	if(! (byAuthority == GUILD_AUTHORITY_MAHARAJA || byAuthority == GUILD_AUTHORITY_RAJA || byAuthority == GUILD_AUTHORITY_PROOBAJA) )
		return HT_FAIL;
//	if( m_strGuild_GuildMasterName.HT_iStringCompare( g_oMainCharacterInfo.szCharName ) != 0 )
//		return HT_FAIL;

	// NPC와 대화중이거나 다른 사람과 트레이드를 하고 있는 중이면 처리 하지 않음
	if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) )
		return HT_FAIL;

	//	상대방의 키아이디를 알아오고 
	m_dwGuild_JoinGuildKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( iObjectID );

	if( m_dwGuild_JoinGuildKeyID == 0 )
	   return HT_FAIL;

	//	상대바의 주신의 나의 주신과 동일하지 않으면 스킵
	if( g_oMainCharacterInfo.byTrimuriti != g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTrimuriti(m_dwGuild_JoinGuildKeyID) )
		return HT_FAIL;

	//----------길드 참여 요청----------//
	this->HT_vNetWork_CSP_REQGuild();
	// 길드 참여 요청 후에 선택한 캐릭터에게 다른 요구를 할 수 있도록 하기 위해서
	// 길드 가입 버튼을 누르지 않은 상태로 초기화 한다.
	m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_NONE;

	return HT_OK;
}

//	길드 초기 정보를 받습니다.
HTvoid HTGuild::HT_vNetWork_SCP_INIT_GUILD( MSG_GuildInfo* info )
{
	HTint i;
	CHTString strTemp;

	m_strAlliedGuildName[0] = info->AlliedGuildName1;					// 연합 길드 이름1
	m_strAlliedGuildName[1] = info->AlliedGuildName2;					// 연합 길드 이름2
	m_strEnemyGuildName[0] = info->EnemyGuildName1;					// 적대 길드 이름1

	for( i=0 ; i<2 ; i++ )
	{
		if( m_strAlliedGuildName[i].HT_bIsEmpty() )
            m_strAlliedGuildName[i] = _T(" ");
		if( m_strEnemyGuildName[i].HT_bIsEmpty() )
            m_strEnemyGuildName[i] = _T(" ");
	}

	if( info->GuildID == -1 )
	{
		//	메시지창 뛰우기
		m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_ERROR;
		CHTString szMessage;
		// 아쉬람 창설에 실패했습니다
		HT_vGuild_SetMessage( eMsgGuildCreateFail, &szMessage );
		g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, szMessage.HT_szGetString(), 0 );
		g_cNPCControl->m_iResent = 1;
		m_strGuild_GuildName.HT_hrCleanUp();
		return;
	}

	//	Display Ashram Name
	strTemp.HT_szFormat( "%s  %s", m_strAlliedGuildName[0].HT_szGetString(), m_strAlliedGuildName[1].HT_szGetString() );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 18, strTemp.HT_szGetString() );

	memcpy( &m_oGuildInfo, info, sizeof(MSG_GuildInfo) );	
	m_strGuild_GuildName = m_oGuildInfo.GuildName;
	m_dwGuild_EmblemID = m_oGuildInfo.Mark;

	if( !m_strGuild_GuildName.HT_bIsEmpty() )
	{
		//	길드명
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 10, m_oGuildInfo.GuildName );
		//	길드 공지
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 17, m_oGuildInfo.GuildMessage );

		this->HT_hrGetGuildMark(info->Mark, &m_iColor, &m_iTitle, &m_iEmblem);
		
		for( i=0 ; i<MAX_GUILD_MEMBER ; i++ )
		{
			CHTString strTempName = m_oGuildInfo.Member[i].MemberName;
			if( !strTempName.HT_bIsEmpty() )
			{
				//	다른 캐릭터에게 길드 마크 셋팅 하기
				g_cOtherObjectSystem->HT_vOtherObjectSystem_SetGuildMarkID( strTempName, m_dwGuild_EmblemID, m_strGuild_GuildName.HT_szGetString() );
				//	길드 리스트에 삽입
				S_GUILD_DATA* psNewNode;
				psNewNode = new S_GUILD_DATA;
				memcpy( &psNewNode->info, &info->Member[i], sizeof(STRUCT_GUILD_MEMBER) );
				this->HT_LL_hrInsertAfter( psNewNode );
				HT_DELETE( psNewNode );

				//	나의 길드내 지위를 저장
				strTempName = m_oGuildInfo.Member[i].MemberName;
				if( strTempName.HT_iStringCompare(g_oMainCharacterInfo.szCharName) == 0 )
                    m_byGuild_GuilAuthority = m_oGuildInfo.Member[i].GuildRank;

				//	길드마스트의 이름 저장
				if( m_oGuildInfo.Member[i].GuildRank == GUILD_AUTHORITY_MAHARAJA )
				{
					m_strGuild_GuildMasterName = m_oGuildInfo.Member[i].MemberName;
				}
			}
		}

		// 길드를 처음 생성했을 때 NPC의 대화를 바꾸기 위해서
		g_cNPCControl->HT_vNPCControl_Create_Guild();
	}

	//	UI에 적용
	this->HT_vGuild_Display();

	if( m_dwGuild_EmblemID > 0 )
	{
		//	길드 마크 표현 하기
		this->HT_vGuild_EmblemOn();
		//	길드 마크 표현 하기
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowGuildMark();
	}

	if( m_oGuildInfo.GuildMessage[0] != '\0' )
	{
		HT_vGuild_SetMessage( eMsgCommonSystemAshuram, &strTemp ); // [아쉬람]
		strTemp += m_oGuildInfo.GuildMessage;
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
	}

	//	내가 보유한 요새가 있는지 파악
	m_iMyStrongGuildIndex = -1;
	for( i=0 ; i<eStronghold_MaxCount ; i++ )
	{
		if( m_strGuild_GuildName.HT_iStringCompare( m_strStrongGuildName[i].HT_szGetString() ) == 0 ||
			m_strAlliedGuildName[0].HT_iStringCompare( m_strStrongGuildName[i] ) == 0 ||
			m_strAlliedGuildName[1].HT_iStringCompare( m_strStrongGuildName[i] ) == 0 )
		{
			m_bMyStrongGuild = TRUE;
			m_iMyStrongGuildIndex = i;
			//	나의 소유성 출력
			if( m_strGuild_GuildName.HT_iStringCompare( m_strStrongGuildName[i].HT_szGetString() ) == 0 )
			{
				HT_vGuild_SetMessage( eMsgCommonDurga0 + m_iMyStrongGuildIndex, &strTemp );
				//	Display Ashram Name
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, strTemp.HT_szGetString() );
			}
			//	연합 아쉬람의 소유성 출력
			else
			{
				CHTString strStrongGuild;
				HT_g_Script_SetMessage( eMsgCommonCommandUnionAshuram, &strTemp, _T("") );
				//	Display Ashram Name
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, strTemp.HT_szGetString() );
			}
			break;
		}
	}

	static Msg_GuildCargoTime oData;
	ZeroMemory( &oData, sizeof(Msg_GuildCargoTime) );
	oData.dwTime[0] = info->dwTime[0];
	oData.dwTime[1] = info->dwTime[1];
	oData.dwTime[2] = info->dwTime[2];
	this->HT_vAshram_SCPGuildCargoTime( &oData );

	static Msg_GuildCargoUsingLevel sData;
	ZeroMemory( &sData, sizeof(Msg_GuildCargoUsingLevel) );
	sData.byCargoLevel[0] = info->byCargoLevel[0];
	sData.byCargoLevel[1] = info->byCargoLevel[1];
	sData.byCargoLevel[2] = info->byCargoLevel[2];
	this->HT_vAshram_SCPSetLevelAshramCargo( &sData );
}

//	길드 생성을 요청한다.
HTRESULT HTGuild::HT_hrNetWork_CSP_REQ_CREATE_GUILD( CHTString strAshramName )
{
	//	주신 체크
	if( g_oMainCharacterInfo.byTrimuriti == 0 )
	{
		CHTString szMessage;
		// 주신 선택 후에 아쉬람을 생성할 수 있습니다.
		HT_vGuild_SetMessage( eMsgGuildCreateNoTrimuritiErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		return HT_FAIL;
	}
    //	돈 체크_루피아 300000 이상일때만 생성가능
	if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < GUILD_CREATE_NEED_MONEY )
	{
		CHTString szMessage;
		// 아쉬람을 만들기 위해서는 300000 루피아가 필요합니다.
		HT_vGuild_SetMessage( eMsgGuildCreateNeedMoneyErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		return HT_FAIL;
	}
	//	글자가 있을때만
	if( strAshramName.HT_nGetSize() < 4 ||
		strAshramName.HT_nGetSize() > 18 )
	{
		CHTString szMessage;
		// 아쉬람명의 길이는 영어기준 4자부터 만드실 수 있습니다.
		HT_vGuild_SetMessage( eMsgGuildMarkConditionErr2, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );

		return HT_FAIL;
	}

	//	%기호가 있으면 스킵
	if( strAshramName.HT_bFind( "%" ) )
		return HT_FAIL;

	m_strGuild_GuildName = strAshramName;

	//	적절치 못한 단어가 들어 있을때는 바로 스킵 해 버린다. 메시지를 넣어줘야 할것도 같은데 흠..
    for( HTint i=0 ; i<NOTCHARANDGUILDNAME_COUNT ; i++ )
	{
		if( m_strGuild_GuildName.HT_bFind( g_szNotCharAndGuildName[i] ) == HT_TRUE )
			return HT_FAIL;
	}
	if( m_strGuild_GuildName.HT_bFind( "," ) == HT_TRUE )
		return HT_FAIL;

	MSG_CreateGuild* info = HT_NULL;
	info = new MSG_CreateGuild;
	info->GuildMark = m_dwGuild_EmblemID;
	info->Trimurity = g_oMainCharacterInfo.byTrimuriti;
	CHTString::HT_hrStringCopy( info->GuildName, m_strGuild_GuildName, SZGUILD_LENGTH);
	g_pNetWorkMgr->ReqestGuildCreateMsg( info );
	HT_DELETE( info );

	return HT_OK;
}

//	신규 길드원의 정보를 길드원들에게 전송한다.
HTvoid HTGuild::HT_vNetWork_SCP_AddGuildMember( MSG_AddGuildMember* info )
{
	S_GUILD_DATA* psNewNode;
	psNewNode = new S_GUILD_DATA;
	memcpy( &psNewNode->info, &info->Member, sizeof(STRUCT_GUILD_MEMBER) );
	//	캐릭터 정보 셋팅
	this->HT_LL_hrInsertAfter( psNewNode );
	HT_DELETE( psNewNode );

	//	UI에 적용
	this->HT_vGuild_Display();

	//	다른 캐릭터에게 길드 마크 셋팅 하기
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetGuildMarkID( info->Member.MemberName, m_dwGuild_EmblemID, m_strGuild_GuildName.HT_szGetString() );
	//	길드 마크 표현 하기
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowGuildMark();
	//	길드 마크 표현 하기
	this->HT_vGuild_EmblemOn();
}

//	길드 탈퇴/해체/제명을 요청한다.
HTvoid HTGuild::HT_vNetWork_CSP_Remove_GuildMember()
{
	MSG_RemoveGuildMember* info = HT_NULL;
	info = new MSG_RemoveGuildMember;
	info->GuildID = m_oGuildInfo.GuildID;

	switch( m_byGuild_ConfirmGrade )
	{
		//	탈퇴
		case GUILDTYPE_CONFIRM_SECEDE :
			info->byRemoveType = 1;
			CHTString::HT_hrStringCopy( info->CharacterName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH);
			break;
		//	제명
		case GUILDTYPE_CONFIRM_EXPEL :
			info->byRemoveType = 2;
			CHTString::HT_hrStringCopy( info->CharacterName, m_strGuild_ListSelectdName, SZNAME_LENGTH);
			break;
		//	해체
		case GUILDTYPE_CONFIRM_DESTROY :
			info->byRemoveType = 3;
			CHTString::HT_hrStringCopy( info->CharacterName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH);
			break;
	}

	g_pNetWorkMgr->ReqestGuildDisbandMsg( info );
	HT_DELETE( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Guild_Remove" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid HTGuild::HT_vNetWork_SCP_RemoveGuildMember( MSG_RemoveGuildMember* info )
{
	CHTString strTempName = g_oMainCharacterInfo.szCharName;
	if( strTempName.HT_iStringCompare( info->CharacterName ) == 0 )
	{
		//	길드 리스트의 인원을 전부 삭제
		this->HT_LL_hrDeleteAll();
		//	메시지창 뛰우기
		m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_ERROR;
		
		CHTString szMessage;
		// 아쉬람이 해체되었습니다.
		HT_vGuild_SetMessage( eMsgGuildDissolutionOK, &szMessage );
		g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, szMessage.HT_szGetString(), 0 );
		//	길드이름 클린업
		m_strGuild_GuildName.HT_hrCleanUp();
		//	길드 마크 표현 안하기
		this->HT_vGuild_EmblemOff();
		m_dwGuild_EmblemID = 0;
		memcpy( &m_oGuildInfo, info, sizeof(MSG_GuildInfo) );

		// 길드 정보창의 내용 삭제 2004. 11. 10 선영범
		//g_bGuildMarkShow = HT_FALSE;
		m_iEmblem = -1;
		m_iTitle = -1;
		m_iColor = -1;

		// 길드마크 초기화
		g_cUIManager->HT_SetTextureControlColor(_DIALOG_ASHRAMINFO, 24, HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f));
		g_cUIManager->HT_SetTextureControlColor(_DIALOG_ASHRAMINFO, 25, HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f));
		g_cUIManager->HT_SetTextureControlColor(_DIALOG_ASHRAMINFO, 26, HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f));

		m_byGuild_GuilAuthority = GUILD_AUTHORITY_NONE;

	}
	else
	{
		//----------LL 데이타 지우기_이름으로---------//
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetInitGuild( info->CharacterName );
		this->HT_LL_hrDeleteNode( info->CharacterName );
	}
}

//	길드 참여를 요청한다.
HTvoid HTGuild::HT_vNetWork_CSP_REQGuild()
{
	MSG_REQGuild* info = HT_NULL;
	info = new MSG_REQGuild;
	info->GuildID = m_oGuildInfo.GuildID;
	strncpy( info->CharacterName, g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(m_dwGuild_JoinGuildKeyID), SZNAME_LENGTH );
	strncpy( info->GuildName, m_oGuildInfo.GuildName, SZNAME_LENGTH );
	g_pNetWorkMgr->ReqestGuildJoinMsg( info );
	HT_DELETE( info );
}

//	길드 참여를 요청을 받는다.
HTvoid HTGuild::HT_vNetWork_SCP_REQGuild( MSG_REQGuild* info )
{
	m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_JOINNOTIFY;
	CHTString strTempMsg;
	m_iGuild_TempGuildID = info->GuildID;
	// %s길드에서 길드 가입을 요청했습니다.
	m_szMsgSting = info->GuildName;
	HT_vGuild_SetMessage( eMsgGuildReqReceive, &strTempMsg );
	g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, strTempMsg.HT_szGetString(), 1 );
}
//	길드 참여 요청 결과를 서버에 전송한다.
HTvoid HTGuild::HT_vNetWork_CSP_CNFGuild()
{
	MSG_CNFGuild* info = HT_NULL;
	info = new MSG_CNFGuild;
	info->GuildID = m_iGuild_TempGuildID;
	strncpy( info->CharacterName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH );
	g_pNetWorkMgr->ReqestGuildCNFGuild( info );
	HT_DELETE( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqCnfGuild" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	길드원이 접속함
HTvoid HTGuild::HT_vNetWork_SCP_GuildMemberin( MSG_GuildMemberin* info )
{
	if( m_strGuild_GuildName.HT_bIsEmpty() )
		return;

	CHTString strName;
	m_strGuild_CharacterName = 	strName = info->CharacterName;
	S_GUILD_DATA* t;
	t = m_pGuildList_Head->pNextNode;
	while( t != m_pGuildList_Tail )
	{
		if( strName.HT_iStringCompare( t->info.MemberName ) == 0 )
		{
			t->info.GuildState = 1;
			break;
		}
		t = t->pNextNode;
	}
 
	//	UI에 적용
	this->HT_vGuild_Display();
/*
	// 길드원이 접속함 (처음에 접속리스트와 자신의 접속에 대한 모든 패킷을 받으므로, 자신의 이름이 두번 호출되기 전까지는 이 메시지를 출력하지 않는다.)
	// 2005. 1. 17 선영범 (추가 요청)
	if (m_nGuildConnectMsg > 1) // 처음 접속이 모두 끝난 상태부터 출력 시작
	{
		if (strcmp(m_strGuild_CharacterName, g_oMainCharacterInfo.szCharName) == 0 ) // 자신과 캐릭터 이름이 같다면 플래그변수 1증가
		{
			m_nGuildConnectMsg = 0;
		}
		else
		{
			CHTString szMessage;
			HT_vGuild_SetMessage( eMsgCommonGuildConnect, &szMessage );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage.HT_szGetString() );
			m_nGuildConnectMsg = 2;
		}
	}
	if (strcmp(m_strGuild_CharacterName, g_oMainCharacterInfo.szCharName) == 0) // 자신과 캐릭터 이름이 같다면 플래그변수 1증가
		m_nGuildConnectMsg++;
*/
}

//	길드원이 접속을 끊음
HTvoid HTGuild::HT_vNetWork_SCP_GuildMemberout( MSG_GuildMemberout* info )
{
	if( m_strGuild_GuildName.HT_bIsEmpty() )
		return;

	//	길드 리스트에 삽입
	CHTString strName;
	m_strGuild_CharacterName = strName = info->CharacterName;
	S_GUILD_DATA* t;
	t = m_pGuildList_Head->pNextNode;
	while( t != m_pGuildList_Tail )
	{
		if( strName.HT_iStringCompare( t->info.MemberName ) == 0 )
		{
			t->info.GuildState = 2;
			break;
		}
		t = t->pNextNode;
	}
 
	//	UI에 적용
	this->HT_vGuild_Display();

	// 이 메시지를 받으면 자신을 제외한 다른 길드원일 경우 
	// 약간의 여유 시간을 두어 접속했는지 안했는지를 체크해야 한다.

	/*
	// 길드원이 나가셨습니다.
	CHTString szMessage;
	HT_vGuild_SetMessage( eMsgCommonGuildExit, &szMessage );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage.HT_szGetString() );
	*/
}

//	길드마크 생성
HTvoid HTGuild::HT_vNetWork_CSP_MSG_GuildUpdateMark( HTbyte byCostType )
{
	MSG_GuildUpdateMark* info = HT_NULL;
	info = new MSG_GuildUpdateMark;

	info->GuildID = m_oGuildInfo.GuildID;
	info->Mark = m_dwGuild_EmblemID;
	info->byCostType = byCostType;

	g_pNetWorkMgr->ReqestGuildMarkCreateMsg( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_GuildMarkCreate:%d, %d, costType = %d", info->Mark, info->byCostType, info->byCostType );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	길드마크 생성 결과
HTvoid HTGuild::HT_vNetWork_SCP_MSG_GuildUpdateMark( MSG_GuildUpdateMark* info )
{
	if( info->byResult == REPLY_ACK_OK )
	{
		m_dwGuild_EmblemID = info->Mark;

		//	길드 마크 표현 하기
		this->HT_vGuild_EmblemOn();
		
		if( info->byCostType == 1 )
		{
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->nMoney );	// 루피아 갱신	2004. 11. 10 선영범
		}

		//	길드 마크 표현 하기
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowGuildMark();
	}
	else if( info->byResult == REPLY_GUILDMARK_PARAM )
	{
		// 부적절한 데이타입니다.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonSystemInvalidData, &strTemp, _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
	}
	else if( info->byResult == REPLY_GUILDMARK_RIGHT )
	{
		// 마크 변경 권한이 없습니다.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonSystemNoRight, &strTemp, _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
	}
	else if( info->byResult == REPLY_GUILDMARK_MONEY )
	{
		if( info->byCostType == 1 )
		{
			// 루피아가 부족합니다.
			CHTString strTemp;
			HT_g_Script_SetMessage( eMsgCommonServerMoreRupia, &strTemp, _T("") );
            g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
		}
		else if( info->byCostType == 2 )
		{
			// 타니가 부족합니다.
			CHTString strTemp;
			HT_g_Script_SetMessage( eMsgCommonServerMoreTani, &strTemp, _T("") );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
		}
	}
	else if( info->byResult == REPLY_UNKNOWN )
	{
		// 마크 변경에 실패 했습니다.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonServerFaild, &strTemp, _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
	}
}

//	길드업데이트_CSP
HTvoid HTGuild::HT_vNetWork_CSP_MSG_GuildUpdate( CHTString strMessage )
{
	//	넘버3까지만 공지 가능
	if( m_byGuild_GuilAuthority == eGuildMaster ||
		m_byGuild_GuilAuthority == eGuildSubMaster ||
		m_byGuild_GuilAuthority == eGuildThird )
	{
		MSG_GuildUpdate* info;
		info = new MSG_GuildUpdate;
		memset( info, 0, sizeof( MSG_GuildUpdate ) );
		info->GuildID = m_oGuildInfo.GuildID;
		strncpy( info->GuildMessage, strMessage.HT_szGetString(), GUILDMESSAGE_LENGTH );

		g_pNetWorkMgr->ReqestGuildUpdateMsg( info );

		HT_DELETE( info );
	}
}

//	길드업데이트_SCP
HTvoid HTGuild::HT_vNetWork_SCP_MSG_GuildUpdate( MSG_GuildUpdate* info )
{
    //	길드 공지사항1
	strncpy( m_oGuildInfo.GuildMessage, info->GuildMessage, GUILDMESSAGE_LENGTH );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 17, info->GuildMessage );

	if( strcmp(info->AlliedGuildName1, _T("")) == 0)
		strcpy(info->AlliedGuildName1, _T(" "));
	if( strcmp(info->AlliedGuildName2, _T("")) == 0)
		strcpy(info->AlliedGuildName2, _T(" "));
	if( strcmp(info->EnemyGuildName1, _T("")) == 0)
		strcpy(info->EnemyGuildName1, _T(" "));

	// 이 업데이트 메시지는 정보 요청에 의해, 아쉬람연합정보 변경에 의해 내려온다. 후자의 경우에는 변경되었다는 메시지를 추가 출력하도록 한다.
	if (! (strcmp( m_strAlliedGuildName[0].HT_szGetString(), info->AlliedGuildName1 ) == 0 &&
		strcmp( m_strAlliedGuildName[1].HT_szGetString(), info->AlliedGuildName2 ) == 0 &&
		strcmp( m_strEnemyGuildName[0].HT_szGetString(), info->EnemyGuildName1 ) == 0 ) )
	{
		if (strcmp(m_strAlliedGuildName[0].HT_szGetString(), " ") != 0)
		{
			CHTString strString;
			HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg8, &strString );	// 아쉬람 연합 설정이 해제 되었습니다.
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
		}
		else
		{
			CHTString strString;
			HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg9, &strString );	// 아쉬람 연합 관계가 설정 되었습니다.
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
		}
	}

	m_strAlliedGuildName[0] = info->AlliedGuildName1;				// 연합 길드 이름1
	m_strAlliedGuildName[1] = info->AlliedGuildName2;				// 연합 길드 이름2
	m_strEnemyGuildName[0] = info->EnemyGuildName1;					// 적대 길드 이름1

	//	[연합 길드명1] [연합 길드명2]
	//	[%s] m_strAlliedGuildName[1].HT_szGetString()
	CHTString strTemp;
	strTemp.HT_szFormat( "[%s]", m_strAlliedGuildName[0].HT_szGetString() );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 18, strTemp.HT_szGetString() );

	//	연합 길드에서 탈퇴한 상태라면,
	if( m_strAlliedGuildName[0].HT_iStringCompare( _T(" ") ) == 0 )
	{
		//	내가 길드 요새를 소유했는지 확인하고 소유하지 않았다면 소유 유새를 -1로 셋팅한다.
		BOOL bTrue = HT_FALSE;
		for(HTint i=0 ; i<4 ; i++ )
		{
			if( m_strGuild_GuildName.HT_iStringCompare( m_strStrongGuildName[i].HT_szGetString() ) == 0 )
				bTrue = HT_TRUE;
		}
		if( !bTrue )
			m_iMyStrongGuildIndex = -1;
	}
	//	딴시스템에 적용한다.
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetStrongAshiram( m_strAlliedGuildName[0].HT_szGetString(), m_strAlliedGuildName[1].HT_szGetString() );
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();
}

//	길드 멤버 업데이트_SCP
HTvoid HTGuild::HT_vNetWork_SCP_MSG_GuildUpdateMember( MSG_GuildUpdateMember* info )
{
	CHTString strName;
	strName = info->Member.MemberName;
	S_GUILD_DATA* t;
	t = m_pGuildList_Head->pNextNode;
	while( t != m_pGuildList_Tail )
	{
		if( strName.HT_iStringCompare( t->info.MemberName ) == 0 )
		{
			t->info.GuildRank = info->Member.GuildRank;
			if( t->info.GuildRank == eGuildMaster )
				m_strGuild_GuildMasterName = info->Member.MemberName;
			t->info.byLevel = info->Member.byLevel;
			//t->info.GuildState = info->Member.GuildState;
			t->info.snTribe = info->Member.snTribe;
			return;
		}
		t = t->pNextNode;
	}

	this->HT_vGuild_Display();
}

//	길드 랭킹 업데이트_CSP
HTvoid HTGuild::HT_vNetWork_CSP_MSG_GuildSetRanking( CHTString strTemp )
{
	//	내가 길드장일때만 가능
	//if( m_byGuild_GuilAuthority != eGuildMaster )
	//	return;

	char chName[SZNAME_LENGTH];
	char chRank[SZNAME_LENGTH];
	// 메시지의 최대 길이와 ID의 최대 길이가 있다면 추가 할 것.
	HTchar tokenMsg[MAX_CHAT_LENGTH] = "\0";
	strncpy( tokenMsg, strTemp, MAX_CHAT_LENGTH );
	sscanf( tokenMsg, "%s %s", chName, chRank );

	MSG_GuildSetRanking* info;
	info = new MSG_GuildSetRanking;

	info->nGuildID = m_oGuildInfo.GuildID;
	strncpy( info->CharacterName, chName, SZNAME_LENGTH );
	CHTString strRank = chRank;

	CHTString szRaja, szPrubaja, szDandeca, szTapasa;
	HT_vGuild_SetMessage( eMsgCommonGuildRaja	, &szRaja );	// 라자
	HT_vGuild_SetMessage( eMsgCommonGuildPrubaja, &szPrubaja ); // 프루바자
	HT_vGuild_SetMessage( eMsgCommonGuildDandeca, &szDandeca ); // 단디카
	HT_vGuild_SetMessage( eMsgCommonGuildTapasa	, &szTapasa );	// 타파사
	
	if( strRank.HT_iStringCompare( szRaja.HT_szGetString() ) == 0 ) // 라자
		info->GuildRank = eGuildSubMaster;
	else if( strRank.HT_iStringCompare( szPrubaja.HT_szGetString() ) == 0 ) // 프루바자
		info->GuildRank = eGuildThird;
	else if( strRank.HT_iStringCompare( szDandeca.HT_szGetString() ) == 0 ) // 단디카
		info->GuildRank = eGuildForth;
	else if( strRank.HT_iStringCompare( szTapasa.HT_szGetString() ) == 0 ) // 타파사
		info->GuildRank = eGuildMember;

	g_pNetWorkMgr->ReqestGuildSetRanking( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_GuildSetGuildRank:%s,%s", chName, chRank );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	길드 랭킹 업데이트_SCP
HTvoid HTGuild::HT_vNetWork_SCP_MSG_GuildSetRanking( MSG_GuildSetRanking* info )
{
	CHTString strName;
	strName = info->CharacterName;
	S_GUILD_DATA* t;
	t = m_pGuildList_Head->pNextNode;
	while( t != m_pGuildList_Tail )
	{
		if( strName.HT_bFind( t->info.MemberName ) == HT_TRUE )
		{
			t->info.GuildRank = info->GuildRank;
			if( t->info.GuildRank == eGuildMaster )
			{
				m_strGuild_GuildMasterName = t->info.MemberName;

				// 본인의 등급을 저장함.
				if( m_strGuild_GuildMasterName.HT_iStringCompare(g_oMainCharacterInfo.szCharName) == 0 )
					m_byGuild_GuilAuthority = eGuildMaster;
				
			}
			return;
		}
		t = t->pNextNode;
	}

	this->HT_vGuild_Display();
}

//	길드원 리스트 대화상자에 표현하기
HTvoid HTGuild::HT_vGuild_Display()
{
	//	슬라이더 번호를 알아온다.
	if( g_cUIManager->HT_isShowWindow( _DIALOG_ASHRAMMEMBERLISET ) )
	{
		m_iGuild_SlideBarCurPos = g_cUIManager->HT_GetScrollBarValue( _DIALOG_ASHRAMMEMBERLISET, 8 );
	}
	else
	{
		m_iGuild_SlideBarCurPos = 0;
	}

	//	멤버 카운트를 위해
	HTint iMemberTotalCount;
	HTint iCurMember;
	CHTString strTemp;
	strTemp.HT_hrCleanUp();

	//	길드리스트창에 표현하기 위해
	CHTString strMemberName[_DISPLAYMEMBERCOUNT];
	CHTString strMemberLevel[_DISPLAYMEMBERCOUNT];
	CHTString strMemberAuthority[_DISPLAYMEMBERCOUNT];
	CHTString strMemberTribe[_DISPLAYMEMBERCOUNT];
	HTint	  iMemberTribeCode[_DISPLAYMEMBERCOUNT];
	CHTString strMemberConnect[_DISPLAYMEMBERCOUNT];

	for( HTint i=0 ; i<_DISPLAYMEMBERCOUNT ; i++ )
	{
		strMemberName[i].HT_hrCleanUp();
		iMemberTribeCode[i] = 0;
	}

	S_GUILD_DATA* t;
	iMemberTotalCount = 0;
	iCurMember = 0;
	t = m_pGuildList_Head->pNextNode;
	while( t != m_pGuildList_Tail )
	{
		iMemberTotalCount++;
		//	접속여부
		if( t->info.GuildState == 1 )
			iCurMember++;

		t = t->pNextNode;
	}

	//	현재 등록 인원 표시
	strTemp.HT_szFormat( "%d/50", iMemberTotalCount );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 15, strTemp.HT_szGetString() );
	//	현재 접속 인원 표시
	strTemp.HT_szFormat( "%d", iCurMember );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 16, strTemp.HT_szGetString() );

	if( m_iGuild_SlideBarCurPos < 0 )
	{
		if( iMemberTotalCount >= _DISPLAYMEMBERCOUNT )
            m_iGuild_SlideBarCurPos = iMemberTotalCount-_DISPLAYMEMBERCOUNT;
		else
			m_iGuild_SlideBarCurPos = 0;
	}

	HTbool bType;
	HTint iMemberCount = 0;
	HTint iNextCount = 0;
	HTint iInsertCount;
	t = m_pGuildList_Head->pNextNode;
	while( t != m_pGuildList_Tail )
	{
		if( iMemberTotalCount <= _DISPLAYMEMBERCOUNT )
		{
			bType = HT_TRUE;
			iInsertCount = iMemberTotalCount-iNextCount-1;
		}
		else
		{
			if( (iMemberTotalCount-m_iGuild_SlideBarCurPos )-iNextCount > 0 && (iMemberTotalCount-m_iGuild_SlideBarCurPos )-iNextCount <= _DISPLAYMEMBERCOUNT )
			{
				bType = HT_TRUE;
				iInsertCount = (iMemberTotalCount-m_iGuild_SlideBarCurPos )-iNextCount-1;
			}
			else
			{
				bType = HT_FALSE;
			}
		}

		if( bType )
		{
			//	길드원 이름
			strMemberName[iInsertCount] = t->info.MemberName;
			//	레벨
			strMemberLevel[iInsertCount].HT_szFormat( "%d", t->info.byLevel );

			//	직위
			if( t->info.GuildRank == eGuildMaster )			// 마하라자
				HT_vGuild_SetMessage( eMsgCommonGuildMahaRaja, &strMemberAuthority[iInsertCount] );
			else if( t->info.GuildRank == eGuildSubMaster ) // 라자
				HT_vGuild_SetMessage( eMsgCommonGuildRaja, &strMemberAuthority[iInsertCount] );
			else if( t->info.GuildRank == eGuildThird )		// 브루바자
				HT_vGuild_SetMessage( eMsgCommonGuildPrubaja, &strMemberAuthority[iInsertCount] );
			else if( t->info.GuildRank == eGuildForth )		// 단디카
				HT_vGuild_SetMessage( eMsgCommonGuildDandeca, &strMemberAuthority[iInsertCount] );
			else // 타파사
				HT_vGuild_SetMessage( eMsgCommonGuildTapasa, &strMemberAuthority[iInsertCount] );

			//	직업
			if( t->info.snTribe == TRIBE_NAGA )				// 나가
			{
				HT_vGuild_SetMessage( eMsgCommonTribeNaga, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23642;
			}
			else if( t->info.snTribe == TRIBE_KINNARA )		// 킨나라
			{
				HT_vGuild_SetMessage( eMsgCommonTribeKimnara, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23650;
			}
			else if( t->info.snTribe == TRIBE_ASURA )		// 아수라
			{
				HT_vGuild_SetMessage( eMsgCommonTribeAsura, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23644;
			}
			else if( t->info.snTribe == TRIBE_RAKSHASA )	// 략샤사
			{
				HT_vGuild_SetMessage( eMsgCommonTribeRakshasa, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23652;
			}
			else if( t->info.snTribe == TRIBE_YAKSA )		// 약크샤
			{
				HT_vGuild_SetMessage( eMsgCommonTribeYaksha, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23646;
			}
			else if( t->info.snTribe == TRIBE_GANDHARVA )	// 간다르바
			{
				HT_vGuild_SetMessage( eMsgCommonTribeGandharva, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23654;
			}
			else if( t->info.snTribe == TRIBE_DEVA )		// 데바
			{
				HT_vGuild_SetMessage( eMsgCommonTribeDeva, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23648;
			}
			else if( t->info.snTribe == TRIBE_GARUDA )		// 가루다
			{
				HT_vGuild_SetMessage( eMsgCommonTribeGaruda, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23656;
			}

			//	접속여부
			if( t->info.GuildState == 1 ||
				strMemberName[iInsertCount].HT_iStringCompare( g_oMainCharacterInfo.szCharName ) == 0 )
				strMemberConnect[iInsertCount] = _T("ON");
			else
				strMemberConnect[iInsertCount] = _T("OFF");

			iMemberCount++;
		}
		if( iMemberCount >= _DISPLAYMEMBERCOUNT )
			break;

		iNextCount++;
		t = t->pNextNode;
	}

	for( i=0 ; i<_DISPLAYMEMBERCOUNT ; ++i )
	{
		if( !strMemberName[i].HT_bIsEmpty() )
		{
			//	길드원 이름
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 10+i, strMemberName[i].HT_szGetString() );
			//	레벨
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 20+i, strMemberLevel[i].HT_szGetString() );
			//	직위
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 30+i, strMemberAuthority[i].HT_szGetString() );
			//	접속여부
			if( strMemberConnect[i].HT_bFind( _T("ON") ) )
			{
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 40+i, strMemberConnect[i].HT_szGetString() );
				g_cUIManager->HT_SetTextColorLabelControl( _DIALOG_ASHRAMMEMBERLISET, 40+i, g_ColorTable[12] );
			}
			else
			{
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 40+i, strMemberConnect[i].HT_szGetString() );
				g_cUIManager->HT_SetTextColorLabelControl( _DIALOG_ASHRAMMEMBERLISET, 40+i, g_ColorTable[11] );
			}
			//	종족
			g_cUIManager->HT_SetTextureControlImage( _DIALOG_ASHRAMMEMBERLISET, 10+i, iMemberTribeCode[i] );
			g_cUIManager->HT_SetTextureControlScale( _DIALOG_ASHRAMMEMBERLISET, 10+i, 0, 0 );
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_ASHRAMMEMBERLISET, 10+i, HT_TRUE );
		}
		else
		{
			//	길드원 이름
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 10+i, _T("") );
			//	레벨
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 20+i, _T("") );
			//	직위
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 30+i, _T("") );
			//	접속여부
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 40+i, _T("") );
			//	종족
			g_cUIManager->HT_SetTextureControlImage( _DIALOG_ASHRAMMEMBERLISET, 10+i, 0 );
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_ASHRAMMEMBERLISET, 10+i, HT_FALSE );
		}
	}
}

HTvoid HTGuild::HT_vGuild_SetEmblemID( DWORD dwEmblemID )
{
	m_dwGuild_EmblemID = dwEmblemID;
	//	길드 마크 표현 하기
	this->HT_vGuild_EmblemOn();
}

//	길드 마크 표현 하기
HTvoid HTGuild::HT_vGuild_EmblemOn()
{
	if( g_bGuildMarkShow )
	{
        g_pEngineHandler->HT_hrAttachGuildMark( g_cMainCharacter->HT_vMainChar_GetModelID(), m_dwGuild_EmblemID );
	}
}

//	길드 마크 표현 안하기
HTvoid HTGuild::HT_vGuild_EmblemOff()
{
	g_pEngineHandler->HT_hrDestroyGuildMark( g_cMainCharacter->HT_vMainChar_GetModelID() );
}

//	길드 마크 표현 처리
HTvoid HTGuild::HT_vGuild_EmblemSwitch( CHTString strMessage )
{
	if( g_bGuildMarkShow == HT_TRUE )
	{
		g_bGuildMarkShow = HT_FALSE;
		//	길드 마크 표현 안하기
		this->HT_vGuild_EmblemOff();
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetHideGuildMark();
	}
	else
	{
		g_bGuildMarkShow = HT_TRUE;
		//	길드 마크 표현 하기
		this->HT_vGuild_EmblemOn();
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowGuildMark();
	}
}

//	주신 마크 표현 하기 하기
HTvoid HTGuild::HT_vTrimutiri_MarkOn()
{
	if( g_bTrimuritiShow )
	{
		if( g_oMainCharacterInfo.byTrimuriti > 0 )
		{
			switch( g_oMainCharacterInfo.byTrimuriti )
			{
				case 1 :
					g_pEngineHandler->HT_hrAttachGodMark( g_cMainCharacter->HT_vMainChar_GetModelID() , g_oMainCharacterInfo.snTribe, HT_GODTYPE_BRAHMA, 1 );
					break;
				case 2 :
					g_pEngineHandler->HT_hrAttachGodMark( g_cMainCharacter->HT_vMainChar_GetModelID() , g_oMainCharacterInfo.snTribe, HT_GODTYPE_VISUNU, 1 );
					break;
				case 4 :
					g_pEngineHandler->HT_hrAttachGodMark( g_cMainCharacter->HT_vMainChar_GetModelID() , g_oMainCharacterInfo.snTribe, HT_GODTYPE_SIVA, 1 );
					break;
			}
		}
	}
}

//	주신 마크 표현 하기 안하기
HTvoid HTGuild::HT_vTrimutiri_MarkOff()
{
	g_pEngineHandler->HT_hrDetachGodMark( g_cMainCharacter->HT_vMainChar_GetModelID() );
}

//	주신 마크 표현 처리
HTvoid HTGuild::HT_vTrimutiri_MarkSwitch( CHTString strMessage )
{
	CHTString szCommand, szToken;
	HT_vGuild_SetMessage( eMsgCommonCommandTrimuritiMark, &szCommand );
	szToken = szCommand + _T(" %d"); // /주신마크 %d

	// 메시지의 최대 길이와 ID의 최대 길이가 있다면 추가 할 것.
	char tokenMsg[MAX_CHAT_LENGTH] = "\0";
	HTint iTrimuritiSw;
	CHTString::HT_hrStringCopy( tokenMsg, strMessage, MAX_CHAT_LENGTH );
	//sscanf( tokenMsg, "/주신마크 %d", &iTrimuritiSw );
	sscanf( tokenMsg, szToken.HT_szGetString(), &iTrimuritiSw );

	if( iTrimuritiSw == 0 )
	{
		g_bTrimuritiShow = HT_FALSE;
		//	길드 마크 표현 안하기
		this->HT_vTrimutiri_MarkOff();
		
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetHideTrimuritiMark();
	}
	else if( iTrimuritiSw == 1 )
	{
		g_bTrimuritiShow = HT_TRUE;
		//	길드 마크 표현 하기
		this->HT_vTrimutiri_MarkOn();
		
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowTrimuritiMark();
	}
}


//------------------------------------------------------------------------------
// Data manipulation functions
//------------------------------------------------------------------------------
//----------링크드 리스트 구현한 부분---------//
//----------LL 초기화---------//
HTvoid HTGuild::HT_LL_vInitList()
{
	m_pGuildList_Head = NULL;
	m_pGuildList_Tail = NULL;

	m_pGuildList_Head = new S_GUILD_DATA;
	m_pGuildList_Tail = new S_GUILD_DATA;
	
	m_pGuildList_Head->pNextNode = m_pGuildList_Tail;
}
//----------LL 데이타 삽입-같은 이름의 친구가 있으면 정보갱신 없으면 헤드 바로 뒤에---------//
HTvoid HTGuild::HT_LL_hrInsertAfter( S_GUILD_DATA* info )
{
	S_GUILD_DATA *t;
	
	t = this->HT_LL_hrSerchNode( info->info.MemberName );

	//	리스트의 끝이면!
	if( t == m_pGuildList_Tail )
	{
		S_GUILD_DATA *s;
		s = NULL;
		s = new S_GUILD_DATA;
		memcpy( &s->info, &info->info, sizeof(STRUCT_GUILD_MEMBER) );
		s->pNextNode = m_pGuildList_Head->pNextNode;
		m_pGuildList_Head->pNextNode = s;
	}
	//	아니면
	else
	{
		memcpy( &t->info, &info->info, sizeof(STRUCT_GUILD_MEMBER) );
	}
}
//----------LL 데이타 지우기_이름으로---------//
HTvoid HTGuild::HT_LL_hrDeleteNode( CHTString strName )
{
	HTint nCompare;
	S_GUILD_DATA *s;
	S_GUILD_DATA *p;

	p = m_pGuildList_Head;
	s = p->pNextNode;
	while( s != m_pGuildList_Tail )
	{
		nCompare = strName.HT_iStringCompare( s->info.MemberName );
		if( nCompare == 0 )
			break;

		p = p->pNextNode;
		s = p->pNextNode;
	}

	if( s != m_pGuildList_Tail )
	{
		p->pNextNode = s->pNextNode;
		HT_DELETE( s );
	}

	this->HT_vGuild_Display();
}
//----------LL 데이타 지우기_찿기_이름으로---------//
S_GUILD_DATA* HTGuild::HT_LL_hrSerchNode( CHTString strName )
{
	HTint nCompare;
	S_GUILD_DATA *t;
    	
	t = m_pGuildList_Head->pNextNode;
	while( t != m_pGuildList_Tail )
	{
		nCompare = strName.HT_iStringCompare( t->info.MemberName );
		if( nCompare == 0 )
			return t;
		t = t->pNextNode;
	}

	return t;
}
//----------LL 데이타 에서 조사_있는지 없는지 이름으로 조사---------//
HTRESULT HTGuild::HT_LL_hrExgistCheckName( CHTString strName )
{
	HTint nCompare;
	S_GUILD_DATA *t;

	t = m_pGuildList_Head->pNextNode;
	while( t != m_pGuildList_Tail )
	{
		nCompare = strName.HT_iStringCompare( t->info.MemberName );
		if( nCompare == 0 )
			return HT_OK;
		t = t->pNextNode;
	}

	return HT_FAIL;
}
//----------LL 데이타 전부 지우기---------//
HTvoid HTGuild::HT_LL_hrDeleteAll()
{
	S_GUILD_DATA *s;
	S_GUILD_DATA *t;
	
	t = m_pGuildList_Head->pNextNode;
	while( t != m_pGuildList_Tail )
	{
		s = t;
		t = t->pNextNode;
		HT_DELETE( s );
	}

	m_pGuildList_Head->pNextNode = m_pGuildList_Tail;
	this->HT_vGuild_Display();
}

HTvoid HTGuild::HT_vSetGuildMark(HTint iBackBmpNo, HTint iShapeBmpNo, HTint iColorNo)
{/*
	HTint iGuildBackBmpNo;
	HTint iGuildShapeBmpNo;
	
	iGuildShapeBmpNo = iShapeBmpNo + _GUILD_MARK_TITLE_START - 1;
	iGuildBackBmpNo = iBackBmpNo + _GUILD_MARK_BACK1_START - 1;
	*/
}

HTRESULT HTGuild::HT_hrGetGuildMark(HTdword dwIdentity, HTint* dwColor, HTint* dwTitle, HTint* dwEmblem)
{
	HTint dwGuildEmblem	= (dwIdentity & 0x000000FF);
	HTint dwGuildTitle	= (dwIdentity & 0x0000FF00) >> 8;
	HTint dwGuildColor	= (dwIdentity & 0x00FF0000) >> 16;

	if ( dwGuildEmblem < 1 || dwGuildEmblem > _GUILD_EMBLEM_NUM
		|| dwGuildTitle < 1 || dwGuildTitle > _GUILD_TITLE_NUM 
		|| dwGuildColor < 1 || dwGuildColor > _GUILD_COLOR_NUM ) return HT_FAIL;

	*dwColor = dwGuildColor;
	*dwTitle = dwGuildTitle;
	*dwEmblem = dwGuildEmblem;

	return HT_OK;
}

HTvoid HTGuild::HT_vGuild_SetMessage( HTint idMessage, CHTString* pstrMessage )
{
	CHTString szString, szParam, szParamString;
	HTshort sParam1 = eMsgParamNone, sParam2 = eMsgParamNone, sParam3 = eMsgParamNone;

	if( g_pMessageMgr->HT_bGetMessage( idMessage, &szString ) == true )
		g_pMessageMgr->HT_bGetParameter( idMessage, &sParam1, &sParam2, &sParam3 );
	else
		szString.HT_hrCleanUp();

	// 변수가 3개 일 때
	if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone && sParam3 != eMsgParamNone )
	{
		CHTString szOut1, szOut2, szOut3;

		// sParam1
		HT_vGuild_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vGuild_SetParamTextForMessage( sParam2, &szOut2 );
		// sParam3
		HT_vGuild_SetParamTextForMessage( sParam3, &szOut3 );

		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString(), szOut3.HT_szGetString() );
	}
	// 변수가 2개 일 때
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vGuild_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vGuild_SetParamTextForMessage( sParam2, &szOut2 );
		
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// 변수가 1개 일 때
	else if( sParam1 != eMsgParamNone  )
	{
		CHTString szOut1;

		// sParam1
		HT_vGuild_SetParamTextForMessage( sParam1, &szOut1 );
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString() );
	}
	else
		*pstrMessage = szString;
}

HTvoid HTGuild::HT_vGuild_SetParamTextForMessage( HTshort sParam, CHTString* pszParam )
{
	switch( sParam )
	{
		// 다른캐릭터 이름
		case eMsgParamOthercharName	:
			*pszParam = m_strGuild_ListSelectdName;
			break;
		// 필요한 돈
		case eMsgParamNeedMoney:
			if( g_cNPCControl->HT_bNPCControl_IsGuilCreateStep( ) ) // 길드 창설
				pszParam->HT_szFormat( "%d", GUILD_CREATE_NEED_MONEY );
			else // 길드 마크 제작
				pszParam->HT_szFormat( "%d", GUILD_MARK_NEED_MONEY );
			break;
		// 길드 이름
		case eMsgParamGuildName :
			*pszParam = m_szMsgSting;
			break;

		case eMsgParamGuildConnect :
			pszParam->HT_szFormat( "%s", m_strGuild_CharacterName.HT_szGetString() );
			break;

		default:
			break;
	}
}

// 아쉬람 연합 픽업 처리
HTRESULT HTGuild::HT_hrGuild_PickCheckFromOtherObject( HTint iObjectID )
{
	if( m_nAshuramGuildJoinMode == 1 )
	{

		m_iAshuramGuildJoin_SendCharKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( iObjectID );

		// Step 1. 상대 주신이 자신의 주신과 같아야 가능
		if ( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTrimuriti(m_iAshuramGuildJoin_SendCharKeyID) != g_oMainCharacterInfo.byTrimuriti )
		{
			CHTString strString;
			HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg12, &strString );	// 같은 주신의 상대만 선택할 수 있습니다.
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );

			return HT_OK;
		}

		// Step 2. 자신과 상대 모두 요새를 점령하고 있는 상태라면 에러메시지 출력
		if (m_bMyStrongGuild == HT_TRUE)
		{
			// 상대방의 길드명 추출
			CHTString GuildName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetAshiramNameFromKeyID(m_iAshuramGuildJoin_SendCharKeyID);

			if (GuildName.HT_szGetString() != NULL)
				for (HTint i=0; i<4; ++i)	// 점령한 요새 4군데의 길드명 비교
					if (strcmp(m_strStrongGuildName[i].HT_szGetString(), GuildName.HT_szGetString()) == 0)
					{
						CHTString strString;
						HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg17, &strString );	// 요새를 소유한 아쉬람끼리는 연합을 맺을 수 없습니다.
						g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
	
						return HT_OK;
					}
		}

		m_strAshuramGuildJoin_SendCharName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(m_iAshuramGuildJoin_SendCharKeyID);
		m_byAshuramGuildJoin_ResponseReason = 0;

		//	Get message and set
		CHTString strString;
		HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg1, &strString, m_strAshuramGuildJoin_SendCharName.HT_szGetString() );
		g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 1 );
		m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_REQALLIANCE;

		m_nAshuramGuildJoinMode = 0;
		return HT_OK;
	} 

	return HT_FAIL;
}

HTvoid HTGuild::HT_vGuildNet_CSP_AshuramGuild(BYTE byType, BYTE byAct, BYTE byResult)
{ 
	Msg_GuildAlliance* info = HT_NULL;
	info = new Msg_GuildAlliance;

	info->nID = m_iAshuramGuildJoin_SendCharKeyID ;
	info->byType = byType;	// 1 = 동맹 , 2 = 적대
	info->byAct = byAct;	// 1 = 결성 , 2 = 해체(취소)
	info->byResult = byResult;	// 0 = 요청, 1~ = 응답

	g_pNetWorkMgr->RequestMsgAshuramGuild( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_AshuramGuild : nID = %d, byType = %d, byAct = %d, byResult = %d", info->nID, info->byType, info->byAct, info->byResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	Recive Challenger
HTvoid HTGuild::HT_vGuildNet_SCP_AshuramGuild( Msg_GuildAlliance* info )
{
	switch(int(info->byResult))
	{
		case 0:	// 아쉬람연합 요청에 대한 응답처리
			{
				m_iAshuramGuildJoin_SendCharKeyID = info->nID;
				m_strAshuramGuildJoin_SendCharName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(m_iAshuramGuildJoin_SendCharKeyID);

				//	Get message and set
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg3, &strString, m_strAshuramGuildJoin_SendCharName.HT_szGetString());
				g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 1 );
				m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_RECIVEALLIANCE;
			}
		case 1:		//REPLY_GUILDALLIANCE_SUCCESS
			{
				if (info->byAct == 1)
				{
//					m_iAshuramGuildJoin_SendCharKeyID = info->nID;
//					m_strAshuramGuildJoin_SendCharName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetNameFromKeyID(m_iAshuramGuildJoin_SendCharKeyID);

//					CHTString strString;
//					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg3, &strString, m_strAshuramGuildJoin_SendCharName.HT_szGetString() );	// %s님이 아쉬람 연합 신청을 받아들였습니다.
//					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				}
				else // 2
				{
//					CHTString strString;
//					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg8, &strString );	// %s님이 아쉬람 연합 신청을 받아들였습니다.
//					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				}
			}
			break;
		case 2:		//REPLY_GUILDALLIANCE_ALREADY
			break;
		case 3:		//REPLY_GUILDALLIANCE_DISCONNECT
			break;
		case 4:		//REPLY_GUILDALLIANCE_LEVEL
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg5, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
			}
			break;
		case 5:		//REPLY_GUILDALLIANCE_CANCEL
			{						// 취소
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg4, &strString, m_strAshuramGuildJoin_SendCharName.HT_szGetString() );	// %s님이 아쉬람 연합 신청을 받아들였습니다.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
			}
			break;
	}
}

//	요새 소유 아쉬람 패킷
HTvoid HTGuild::HT_vGuildNet_SCP_StrongGuildInit( Msg_StrongHoldInit* info )
{
	// 요새에 길드 마크 넣어줌.
	g_pEngineHandler->HT_hrSetGuildCastleMark( info->dwMark[eStronghold_Northwest], info->dwMark[eStronghold_Northeast], info->dwMark[eStronghold_Southwest], info->dwMark[eStronghold_Southeast] );

	//	소유성 출력
	m_iMyStrongGuildIndex = -1;
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, _T("") );

	for( int i=0 ; i<eStronghold_MaxCount  ; i++ )
	{
		//	요새를 보유한 길드 이름
		m_strStrongGuildName[i] = info->szGuildName[i];

		if( !m_strGuild_GuildName.HT_bIsEmpty() )
		{
			if( m_strGuild_GuildName.HT_iStringCompare( info->szGuildName[i] ) == 0 ||
				m_strAlliedGuildName[0].HT_iStringCompare( info->szGuildName[i] ) == 0 ||
				m_strAlliedGuildName[1].HT_iStringCompare( info->szGuildName[i] ) == 0 )
			{
				m_iMyStrongGuildIndex = i;
				m_bMyStrongGuild = TRUE;

				//	나의 소유성 출력
				if( m_strGuild_GuildName.HT_iStringCompare( info->szGuildName[i] ) == 0 )
				{
					CHTString strTemp;
					HT_vGuild_SetMessage( eMsgCommonDurga0 + m_iMyStrongGuildIndex, &strTemp ); // [아쉬람]
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, strTemp.HT_szGetString() );
				}
				//	연합 아쉬람의 소유성 출력
				else
				{
					CHTString strStrongGuild;
					CHTString strTemp;
					HT_g_Script_SetMessage( eMsgCommonCommandUnionAshuram, &strTemp, _T("") );
					strStrongGuild.HT_szFormat( "%s(%s)", m_strStrongGuildName[m_iMyStrongGuildIndex].HT_szGetString(), strTemp.HT_szGetString() );
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, strStrongGuild.HT_szGetString() );
				}
				break;
			}
		}
	}
}

//	요새 소유 아쉬람 패킷 Udate
HTvoid HTGuild::HT_vGuildNet_SCP_StrongGuildUpdate( Msg_StrongHoldUpdate* info )
{
	// 요새에 길드 마크 넣어줌.
	g_pEngineHandler->HT_hrSetGuildCastleMark( info->dwMark[eStronghold_Northwest], info->dwMark[eStronghold_Northeast], info->dwMark[eStronghold_Southwest], info->dwMark[eStronghold_Southeast] );

	//	소유성 출력
	m_iMyStrongGuildIndex = -1;
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, _T("") );

	for( int i=0 ; i<eStronghold_MaxCount  ; i++ )
	{
		//	요새를 보유한 길드 이름
		m_strStrongGuildName[i] = info->szGuildName[i];

		if( !m_strGuild_GuildName.HT_bIsEmpty() )
		{
			if( m_strGuild_GuildName.HT_iStringCompare( info->szGuildName[i] ) == 0 ||
				m_strAlliedGuildName[0].HT_iStringCompare( info->szGuildName[i] ) == 0 ||
				m_strAlliedGuildName[1].HT_iStringCompare( info->szGuildName[i] ) == 0 )
			{
				m_iMyStrongGuildIndex = i;
				m_bMyStrongGuild = TRUE;
				//	나의 소유성 출력
				if( m_strGuild_GuildName.HT_iStringCompare( info->szGuildName[i] ) == 0 )
				{
					CHTString strTemp;
					HT_vGuild_SetMessage( eMsgCommonDurga0 + m_iMyStrongGuildIndex, &strTemp ); // [아쉬람]
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, strTemp.HT_szGetString() );
				}
				//	연합 아쉬람의 소유성 출력
				else
				{
					CHTString strStrongGuild;
					CHTString strTemp;
					HT_g_Script_SetMessage( eMsgCommonCommandUnionAshuram, &strTemp, _T("") );
					strStrongGuild.HT_szFormat( "%s(%s)", m_strStrongGuildName[m_iMyStrongGuildIndex].HT_szGetString(), strTemp.HT_szGetString() );
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, strStrongGuild.HT_szGetString() );
				}
				break;
			}
		}
	}

	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetStrongAshiram( m_strAlliedGuildName[0].HT_szGetString(), m_strAlliedGuildName[1].HT_szGetString() );
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();
}

//	연합길드 
CHTString HTGuild::HT_strGuild_AlliedGuildName( HTint iGuildIndex )
{
	return m_strAlliedGuildName[iGuildIndex];
}

//	Ashram Cargo
//	Request Ashram Item
HTvoid HTGuild::HT_vAshram_CSPAshramItem()
{
	Msg_GuildItem* info = HT_NULL;
	info = new Msg_GuildItem;

	// Send to server
	g_pNetWorkMgr->RequestGuildItem( info );

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Request_AshramItem" );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	Recive Ashram Item
HTvoid HTGuild::HT_vAshram_SCPAshramItem( Msg_GuildItem* info )
{
	g_cUIManager->HT_ShowWindow(_DIALOG_ASHRAMCAGO);
	//	인벤토리도 Open
	if( !g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) )
        g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();

	//	그리고 새롭게 셋팅하여 넣어준다.
	memcpy( m_arrItemOfAshramCargo[0], info->arrItem, sizeof(STRUCT_ITEM)*120 );
	memcpy( m_arrItemOfAshramCargo[1], info->arrItem+120, sizeof(STRUCT_ITEM)*120 );
	memcpy( m_arrItemOfAshramCargo[2], info->arrItem+240, sizeof(STRUCT_ITEM)*120 );
	//	먼저 기존의 창고 아이템을 지운다.
	g_cItemSystem->HT_LL_vInsertAfter_ItemDeleteAshramCargo( m_arrItemOfAshramCargo[m_iPrevPageOfAshramCargo], m_iPrevPageOfAshramCargo );
	g_cItemSystem->HT_LL_vInsertAfter_ItemCreateAshramCargo( m_arrItemOfAshramCargo[m_iPageOfAshramCargo], m_iPageOfAshramCargo );
	//	아쉬람 창고 이름 갱신
	CHTString strTemp;
	CHTString strMessage;
	strTemp.HT_hrCleanUp();
	g_cUIManager->HT_SetScriptMessage( eMsgAshramAshramCargo, &strMessage, _T(""), _T("") );	//	아쉬람창고
	strTemp.HT_szFormat( strMessage, m_iPageOfAshramCargo+1 );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMCAGO, 5, strTemp.HT_szGetString() );
}
//	Request Set Level Ashram Cargo
HTvoid HTGuild::HT_vAshram_CSPSetLevelAshramCargo( HTbyte byCargoNo, HTbyte byLevel )
{
	Msg_GuildCargoUsingLevel* info = HT_NULL;
	info = new Msg_GuildCargoUsingLevel;

	info->byCargoLevel[0] = m_byUseCargoLevel[0];
	info->byCargoLevel[1] = m_byUseCargoLevel[1];
	info->byCargoLevel[2] = m_byUseCargoLevel[2];
	info->byCargoLevel[byCargoNo] = byLevel;

	// Send to server
	g_pNetWorkMgr->RequestGuildCargoUsingLevel( info );

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Request_GuildCargoUsingLevel No:%d, Level:%d", byCargoNo, byLevel );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	Recive Set Level Ashram Cargo
HTvoid HTGuild::HT_vAshram_SCPSetLevelAshramCargo( Msg_GuildCargoUsingLevel* info )
{
	for( HTint i=0 ; i<3 ; i++ )
	{
		m_byUseCargoLevel[i] = info->byCargoLevel[i];
		HTbyte byLevel;
		if( info->byCargoLevel[i] == eGuildSubMaster )		byLevel = 0;
		else if( info->byCargoLevel[i] == eGuildThird )		byLevel = 1;
		else if( info->byCargoLevel[i] == eGuildForth )		byLevel = 2;
		else												byLevel = 3;//if( iLevel == eGuildMember )
		for( HTbyte j=0 ; j<4 ; j++ )
		{
			if( byLevel>=j )	g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_SETLEVELASHCAGO, 10+(i*4)+j, HT_TRUE );
			else				g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_SETLEVELASHCAGO, 10+(i*4)+j, HT_FALSE );
		}
	}
}
//	Request GuildCargoTimeExtension
HTvoid HTGuild::HT_vAshram_CSPGuildCargoTimeExtension( HTbyte byType )
{
	Msg_GuildCargoTimeExtension* info = HT_NULL;
	info = new Msg_GuildCargoTimeExtension;

	info->byType = byType;
	// Send to server
	g_pNetWorkMgr->RequestGuildCargoTimeExtension( info );

	//-----디버깅 테스트를 위하여-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Request_GuildCargoTimeExtension Type:%d", byType );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	Recive GuildCargoTimeExtension
HTvoid HTGuild::HT_vAshram_SCPGuildCargoTimeExtension( Msg_GuildCargoTimeExtension* info )
{
	if( info->byResult == 0 )
	{
		CHTString strMessage;
		CHTString strTemp;
		g_cUIManager->HT_SetScriptMessage( eMsgAshramInfo, &strMessage, _T(""), _T("") );	//	아쉬람 창고%d 확장에 성공하였습니다.
		strTemp.HT_szFormat( strMessage, (HTint)info->byType );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
	}
	else if( info->byResult == 1 )
	{
		CHTString strMessage;
		g_cUIManager->HT_SetScriptMessage( eMsgAshramFaildCargoExpance, &strMessage, _T(""), _T("") );	//	아쉬람 창고 확장에 실패하였습니다.
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage );
	}
}
//	Recive GuildItemUpdate
HTvoid HTGuild::HT_vAshram_SCPGuildItemUpdate( Msg_GuildItemUpdate* info )
{
    //	기존 아이템 삭제
	if( info->nFromIndex != -1 )
	{
		HTint iKeyID = 0;
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_GUILDCARGO, info->nFromIndex, iKeyID );
		g_cItemSystem->HT_LL_vInsertAfter_ItemDelete( (HTdword)iKeyID );
	}

	//	아이템 생성
	if( info->nToIndex != -1 )
	{
		if (g_cItemSystem) g_cItemSystem->HT_vItemSystem_CreateAshramCargo( ITEM_PLACE_GUILDCARGO, info->nToIndex, info->item  );
	}
}
//	Recive GuildCargoTime
HTvoid HTGuild::HT_vAshram_SCPGuildCargoTime( Msg_GuildCargoTime* info )
{
	for( HTint i=0 ; i<3 ; i++ )
	{
		if( info->dwTime[i] > 0 )
		{
			time_t svTime = (time_t)info->dwTime[i];
			if( svTime > 0 )
			{
				time_t now; time( &now );
				CHTString szDay;

				CHTString strMessage;
				g_cUIManager->HT_SetScriptMessage( eMsgWordInUseing, &strMessage, _T(""), _T("") );	//	사용중
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SANCTIONASHCAGO, 10+i, strMessage );

				tm* psTmTime = localtime( &svTime );

				g_cUIManager->HT_SetScriptMessage( eMsgCommonUntilAshramCargo, &strMessage, _T(""), _T("") );	//	사용중
				//szDay.HT_szFormat("%d.%d.%d까지", psTmTime->tm_year+1900, psTmTime->tm_mon+1, psTmTime->tm_mday );
				szDay.HT_szFormat(strMessage, psTmTime->tm_year+1900, psTmTime->tm_mon+1, psTmTime->tm_mday );
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SANCTIONASHCAGO, 13+i, szDay.HT_szGetString() );
				
				svTime -= now;
				if (svTime <= 86400)	svTime = 0;
				else					svTime /= 86400;
				szDay.HT_szFormat("%d", svTime);
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_SANCTIONASHCAGO, 16+i, szDay.HT_szGetString() );
			}
		}
		else
		{
			CHTString strMessage;
			g_cUIManager->HT_SetScriptMessage( eMsgAshramNotUse, &strMessage, _T(""), _T("") );	//	사용중아님
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SANCTIONASHCAGO, 10+i, strMessage );
			g_cUIManager->HT_SetScriptMessage( eMsgAshramEnd, &strMessage, _T(""), _T("") );	//	만료
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SANCTIONASHCAGO, 13+i, strMessage );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SANCTIONASHCAGO, 16+i, _T("0") );
		}
	}
}

