#include "stdafx.h"
#include "HTControlDef.h"
#include "HTextern.h"
#include "HTEngineHandler.h"
#include "htguild.h"

#define		_GUILD_EMBLEM_NUM					72
#define		_GUILD_TITLE_NUM					84
#define		_GUILD_COLOR_NUM					72

#define		GUILD_CREATE_NEED_MONEY				300000 // ��� â���� �ʿ��� ��
#define		GUILD_MARK_NEED_MONEY				3000000 // ��� ��ũ ���鶧 �ʿ��� ��

#define		_GUILD_RECORD_NUM					9
#define		_GUILD_TABLE_NUM					5

#define		_DISPLAYMEMBERCOUNT					9

#define		_GUILD_EDIT_ORI_COLOR	HT_COLOR(221.0f/255.0f, 205.0f/255.0f, 163.0f/255.0f, 100.0f/100.0f)
#define		_GUILD_EDIT_SEL_COLOR	HT_COLOR(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 100.0f/100.0f)


HTGuild::HTGuild(void)
{
	m_iGuild_SlideBarCurPos = 0;
	m_bGuild_SlideBarBtn = HT_FALSE;
	//----------LL �ʱ�ȭ---------//
	this->HT_LL_vInitList();

	m_iEmblem = -1;
	m_iTitle = -1;
	m_iColor = -1;

	m_nGuildConnectMsg = 0;
	m_nAshuramGuildJoinMode = 0;
	m_iMyStrongGuildIndex = -1;

	//	���� ����� �����ϰ� �ִ��� Ȯ��
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

//	����Ÿ ����
HTvoid HTGuild::HT_vGuild_Delete()
{
	//g_cUIManager->HT_DeleteWindow( _DIALOG_DISCONNECTSERVER );
    //----------LL ����Ÿ ���� �����---------//
	this->HT_LL_hrDeleteAll();
}

//	�ʱ� ����Ÿ ����
HTvoid HTGuild::HT_vGuild_Init()
{
	//	Create Window
	this->HT_vGuild_CreateWindow();

	//	Ȯ�� �ܰ�
	m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_NONE;
	//	Ȯ�� ��ư ���ȴ��� üũ
	m_bGuild_ConfirmDlgBoxSw = HT_FALSE;
	//	��� ������ �ƴ���.
	m_byGuild_GuilAuthority = GUILD_AUTHORITY_NONE;
	m_dwGuild_EmblemID = 0;
	//	���õ� ���� �ʱ�ȭ
	m_strGuild_ListSelectdName.HT_hrCleanUp();
	//	����̸� �ʱ�ȭ
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
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 1, 8, 3, 36, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 2, 8, 3, 148, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 3, 8, 3, 285, 1400, 323, 6 );
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 4, 8, 3, 330, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 5, 8, 3, 375, 1400, 323, 6 );
	//	Texture �ƽ�������
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 6, 9, 39, 30, 1400, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramInfo, &strMessage, _T(""), _T("") );	//	�ƽ�������
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 19 );
	//	Texture ���� ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 7, 9, 39, 143, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramNotice, &strMessage, _T(""), _T("") );	//	���� ����
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 7, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 143, 152, 19 );
	//	Texture ���� �ƽ���
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 8, 9, 39, 280, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramUnionAshram, &strMessage, _T(""), _T("") );	//	���� �ƽ���
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 8, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 280, 152, 19 );
	//	Texture ���� �ƽ���
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 9, 9, 39, 325, 1400, 152, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 9, _T("���� �ƽ���"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 325, 152, 19 );
	//	Texture �ƽ��� ��
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 10, 9, 92, 68, 1400, 152, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramAshramName, &strMessage, _T(""), _T("") );	//	�ƽ��� ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 68, 152, 19 );
	//	Texture ������
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 11, 10, 92, 79, 1400, 79, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 11, _T("������"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 79, 79, 19 );
	//	Texture ����ο�
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 12, 10, 92, 96, 1400, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramResigstMember, &strMessage, _T(""), _T("") );	//	����ο�
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 96, 79, 19 );
	//	Texture �����ο�
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 13, 10, 92, 119, 1400, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramConnectMember, &strMessage, _T(""), _T("") );	//	�����ο�
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 92, 119, 79, 19 );
	//	Texture ���ٶ� ���
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 14, 9, 173, 79, 1400, 152, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 14, _T("���ٶ� ���"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 173, 79, 152, 19 );
	//	Texture ����ο� ��
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 15, 9, 173, 99, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 15, _T("0/0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 173, 99, 79, 19 );
	//	Texture �����ο� ��
	//g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 16, 9, 173, 119, 1400, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 16, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 173, 119, 79, 19 );
	//	Only Label ���� ����
	g_cUIManager->HT_SetScriptMessage( eMsgAshramExplainNotice, &strMessage, _T(""), _T("") );	//	���������Դϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 17, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 167, 310, 100 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_ASHRAMINFO, 17, 7 );
	//	Only Label ���� �ƽ��� ����
	g_cUIManager->HT_SetScriptMessage( eMsgAshramNoUnionAshram, &strMessage, _T(""), _T("") );	//	���� �ƽ����� �����ϴ�.
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 18, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 305, 310, 16 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_ASHRAMINFO, 18, 7 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 19, _T(""), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 340, 310, 16 );
	g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_ASHRAMINFO, 19, 7 );
	//	Only Label ���� �ƽ��� ����
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 19, _T("���� �ƽ����� �����ϴ�."), 1, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 350, 310, 16 );
	//g_cUIManager->HT_SetArrangementLabelControl( _DIALOG_ASHRAMINFO, 19, 7 );
	//	Button �����ο�
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMINFO, 20, 9, 129, 37, 0, 0, 1500, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramOrganizationMember, &strMessage, _T(""), _T("") );	//	�����ο�
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 20, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 129, 37, 90, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMINFO, 20 );
	if( g_iInationalType == INATIONALTYPE_KOREA )
	{
		//	Button Ȩ������
		g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMINFO, 21, 159, 125, 418, 160, 161, 1500, 79, 19 );
		g_cUIManager->HT_SetScriptMessage( eMsgAshramMakeBlog, &strMessage, _T(""), _T("") );	//	Ȩ������
		g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 21, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 125, 418, 79, 19 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMINFO, 21 );
		//	Button Ȩ������
		g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMINFO, 22, 159, 227, 418, 160, 161, 1500, 79, 19 );
		g_cUIManager->HT_SetScriptMessage( eMsgAshramEnterBlog, &strMessage, _T(""), _T("") );	//	Ȩ������
		g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 22, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 227, 418, 79, 19 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMINFO, 22 );
		//	Button �̴Ϻ�α�
		g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMINFO, 27, 159, 23, 418, 160, 161, 1500, 79, 19 );
		g_cUIManager->HT_SetScriptMessage( eMsgAshramMiniBlog, &strMessage, _T(""), _T("") );	//	�̴Ϻ�α�
		g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMINFO, 27, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 23, 418, 79, 19 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMINFO, 27 );
	}
	//	Texture ���� �ڽ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 0, 66, 292, 46, 1400, 32, 32 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 23, 0, 294, 48, 1410, 1, 1 );
	//	Texture ū �ڽ�
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 0, 66, 12, 58, 1400, 74, 77 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 24, 0, 17, 63, 1401, 1, 1);
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 25, 0, 17, 63, 1402, 1, 1);
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMINFO, 26, 0, 33, 79, 1403, 1, 1);

	//	[_DIALOG_ASHRAMMEMBERLISET]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_ASHRAMMEMBERLISET, _T(""), 330, 466, g_cGuildSystem->HT_vGuild_InputCheckForAshramMemberList, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_ASHRAMMEMBERLISET, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 1, 8, 3, 36, 1400, 323, 6 );
	//	Texture �����ο�
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 2, 9, 129, 30, 1400, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramOrganizationMember, &strMessage, _T(""), _T("") );	//	�����ο�
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 129, 30, 90, 19 );
	//	Texture ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 3, 9, 4, 56, 1400, 32, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressTribe, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 4, 56, 34, 19 );
	//	Texture �̸�
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 4, 9, 40, 56, 1400, 134, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressName, &strMessage, _T(""), _T("") );	//	�̸�
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 4, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 56, 137, 19 );
	//	Texture ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 5, 9, 178, 56, 1400, 31, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramLevel, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 5, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 177, 56, 34, 19 );
	//	Texture ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 6, 9, 213, 56, 1400, 61, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramPosition, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 6, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 212, 56, 64, 19 );
	//	Texture ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMMEMBERLISET, 7, 9, 278, 56, 1400, 31, 19 );
	g_cUIManager->HT_SetScriptMessage( sMsgAddressConnect, &strMessage, _T(""), _T("") );	//	����
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
	//	Button �ƽ�������
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMMEMBERLISET, 50, 9, 39, 37, 0, 0, 1500, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramInfo, &strMessage, _T(""), _T("") );	//	�ƽ�������
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 50, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 37, 90, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMMEMBERLISET, 50 );
	//	Button ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMMEMBERLISET, 51, 159, 82, 430, 160, 161 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonJoin, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 51, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 82, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMMEMBERLISET, 51 );
	//	Button Ż��
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMMEMBERLISET, 52, 159, 201, 430, 160, 161 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonSecede, &strMessage, _T(""), _T("") );	//	Ż��
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMMEMBERLISET, 52, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 201, 430, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMMEMBERLISET, 52 );

	// �ں� ����â
	// ������ ���� (�� = 1, 2, 3)
	g_cUIManager->HT_CreateWindow(_DIALOG_AMBLEM, "Emblem", 330, 345, g_cGuildSystem->HT_vGuild_InputCheckForEmblemSelecting, 2);
	g_cUIManager->HT_WindowArrangement(_DIALOG_AMBLEM, 5);
	g_cUIManager->HT_AddTextureControl(_DIALOG_AMBLEM, 0, 8, 3, 37, 1400, 324, 6);

	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 1, 159, 10, 31, 160, 161, 1500, 69, 19);
	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 2, 159, 80, 31, 160, 161, 1500, 69, 19);
	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 3, 159, 150, 31, 160, 161, 1500, 69, 19);
	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM, 4, 159, 220, 31, 160, 161, 1500, 69, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgAshramBackMark, &strMessage, _T(""), _T("") );	//	��湮��
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 1, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 31, 69, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgAshramMark, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 2, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 31, 69, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgAshramMark, &strMessage, _T(""), _T("") );	//	����2
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 3, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 31, 69, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgAshramBackColor, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 4, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 220, 31, 69, 19);

	// �ں� 11, 12, 13
	g_cUIManager->HT_AddTextureControl(_DIALOG_AMBLEM, 11, 0, 25, 80, 1401, 64, 64);
	g_cUIManager->HT_AddTextureControl(_DIALOG_AMBLEM, 12, 0, 25, 80, 1402, 64, 64);
	g_cUIManager->HT_AddTextureControl(_DIALOG_AMBLEM, 13, 0, 25+16, 80+16, 1403, 32, 32);

	// �ؽ�ó ���� �ε��� 101~ 112, ��ư�� ����
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

	// �ں� ��ư (200 = Ȯ��, 201 = ���)
	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM,200, 159, 74, 315,  160, 161, 64, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgCommonConfirm, &strMessage, _T(""), _T("") );	//	Ȯ��
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 1, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 74, 315, 64, 19);
	g_cUIManager->HT_AddButtonControl(_DIALOG_AMBLEM,201, 159, 188, 315,  160, 161, 64, 19);
	g_cUIManager->HT_SetScriptMessage( eMsgCommonCancel, &strMessage, _T(""), _T("") );	//	���
	g_cUIManager->HT_AddLabelControl(_DIALOG_AMBLEM, 1, strMessage, 0, HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f),  HT_COLOR(1.0f, 1.0f, 1.0f, 1.0f), 188, 315, 64, 19);

	m_iTabNo = 1;m_iBackIndex = 0;m_iTitleIndex = 0;m_iBackColor = 0;
	this->HT_vGuild_DialogBoxDrawTab(1);
	this->HT_bGuild_DialogBoxDrawEmblem(0);

	//	[_DIALOG_ASHRAMCAGO]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_ASHRAMCAGO, _T(""), 370, 540, g_cGuildSystem->HT_vGuild_InputCheckForAshramCago, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_ASHRAMCAGO, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMCAGO, 0, 8, 2, 36, 1400, 367, 6 );
	//	Texture �ƽ��� â��
	g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMCAGO, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramAshramCargo, &strMessage, _T(""), _T("") );	//	�ƽ���â��
	strTemp.HT_szFormat( strMessage, 1 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMCAGO, 5, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Button â��1
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMCAGO, 1, 159, 45, 55, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	â��
	strTemp.HT_szFormat( strMessage, 1 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMCAGO, 1, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 45, 55, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMCAGO, 1 );
	//	Button â��2
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMCAGO, 2, 159, 153, 55, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	â��
	strTemp.HT_szFormat( strMessage, 2 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMCAGO, 2, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 153, 55, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMCAGO, 2 );
	//	Button â��3
	g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMCAGO, 3, 159, 262, 55, 160, 161, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	â��
	strTemp.HT_szFormat( strMessage, 3 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMCAGO, 3, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 262, 55, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMCAGO, 3 );
	////	Button â����
	//g_cUIManager->HT_AddButtonControl( _DIALOG_ASHRAMCAGO, 4, 159, 283, 55, 160, 161, 1500, 64, 19 );
	//g_cUIManager->HT_AddLabelControl( _DIALOG_ASHRAMCAGO, 4, _T("â����"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 283, 55, 64, 19 );
	//g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_ASHRAMCAGO, 4 );
	//	loop
	//	����
	for( i=0 ; i<11 ; i++ )
	{
		g_cUIManager->HT_AddTextureControl( _DIALOG_ASHRAMCAGO, 0, 1, 3+(i*36), 82, 1400, 3, 432 );
	}
	//	����
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
	//	Texture �ƽ��� â��
	g_cUIManager->HT_SetScriptMessage( eMsgAshramExplainCargo01, &strMessage, _T(""), _T("") );	//	�� â����ⰣȮ�ιװ��� ��
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 0, 15, 420, 17 );
	//	â���
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargoName, &strMessage, _T(""), _T("") );	//	â���
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 50, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	â���
	strTemp.HT_szFormat( strMessage, 1 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 90, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	â���
	strTemp.HT_szFormat( strMessage, 2 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 120, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	â���
	strTemp.HT_szFormat( strMessage, 3 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 10, 150, 80, 17 );
	//	��뿩��
	g_cUIManager->HT_SetScriptMessage( eMsgAshramUseYesOrNo, &strMessage, _T(""), _T("") );	//	��뿩��
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 80, 50, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramNotUse, &strMessage, _T(""), _T("") );	//	����߾ƴ�
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 10, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 80, 90, 80, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 11, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 80, 120, 80, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 12, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 80, 150, 80, 17 );
	//	����Ⱓ
	g_cUIManager->HT_SetScriptMessage( eMsgAshramEnddate, &strMessage, _T(""), _T("") );	//	����Ⱓ
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 140, 50, 120, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramEnd, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 13, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 140, 90, 120, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 14, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 140, 120, 120, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 15, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 140, 150, 120, 17 );
	//	D-day
	g_cUIManager->HT_SetScriptMessage( eMsgAshramDDay, &strMessage, _T(""), _T("") );	//	D-day
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 230, 50, 100, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 16, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 230, 90, 100, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 17, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 230, 120, 100, 17 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 18, _T("0"), 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 230, 150, 100, 17 );
	//	Button â��1 ���� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_SANCTIONASHCAGO, 1, 159, 320, 90, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramPayCargo, &strMessage, _T(""), _T("") );	//	��������
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 1, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 320, 90, 79, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SANCTIONASHCAGO, 1 );
	//	Button â��2 ���� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_SANCTIONASHCAGO, 2, 159, 320, 120, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 2, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 320, 120, 79, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SANCTIONASHCAGO, 2 );
	//	Button â��3 ���� ����
	g_cUIManager->HT_AddButtonControl( _DIALOG_SANCTIONASHCAGO, 3, 159, 320, 150, 160, 161, 1500, 79, 19 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SANCTIONASHCAGO, 3, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 320, 150, 79, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_SANCTIONASHCAGO, 3 );

	//	[_DIALOG_SETLEVELASHCAGO]
	//	Window
	g_cUIManager->HT_CreateWindow( _DIALOG_SETLEVELASHCAGO, _T(""), 370, 190, g_cGuildSystem->HT_vGuild_InputCheckForSetLevelAshramCago, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_SETLEVELASHCAGO, 5 );
	//	��	���� ǥ����
	g_cUIManager->HT_AddTextureControl( _DIALOG_SETLEVELASHCAGO, 0, 8, 2, 36, 1400, 367, 6 );
	//	Texture �ƽ��� â��
	g_cUIManager->HT_AddTextureControl( _DIALOG_SETLEVELASHCAGO, 0, 9, 39, 30, 1400, 150, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramSetAshramRight, &strMessage, _T(""), _T("") );	//	�ƽ���â����Ѽ���
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 150, 17 );
	//	â���
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	â���
	strTemp.HT_szFormat( strMessage, 1 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 100, 60, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	â���
	strTemp.HT_szFormat( strMessage, 2 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 180, 60, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgAshramCargo, &strMessage, _T(""), _T("") );	//	â���
	strTemp.HT_szFormat( strMessage, 3 );
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strTemp, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 260, 60, 80, 17 );
	//	�ƽ��� ���
	g_cUIManager->HT_SetScriptMessage( eMsgCommonGuildRaja, &strMessage, _T(""), _T("") );	//	����
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 80, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonGuildPrubaja, &strMessage, _T(""), _T("") );	//	Ǫ������
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 100, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonGuildDandeca, &strMessage, _T(""), _T("") );	//	�ܵ�ī
	g_cUIManager->HT_AddLabelControl( _DIALOG_SETLEVELASHCAGO, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 20, 120, 80, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommonGuildTapasa, &strMessage, _T(""), _T("") );	//	Ÿ�Ļ�
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

// �ش� �ܹ�ȣ�� ���� �ٺ�â�� �׸��ϴ�.
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

// ������ ������ �Է¹޾� �����쿡 �׷��ݴϴ�. (��帶ũ ����â)
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

// ������ ������ �Է¹޾� �����쿡 �׷��ݴϴ�. (��帶ũ ����â)
HTvoid	HTGuild::HT_bGuild_DialogBoxDrawEmblem(int iIndex)
{
	int max = this->HT_bGuild_GetDialogBoxEmblemMaxButton();
	if (iIndex >= max) return;

	// ���� ������ �ܿ� ���� �ε����� �����մϴ�.
	switch(m_iTabNo)
	{
	case 1:	m_iBackIndex = iIndex;	break;
	case 2:	m_iTitleIndex = iIndex;	break;
	case 3:	m_iTitleIndex = iIndex+42;	break;
	case 4:	m_iBackColor = iIndex;	break;
	}

	// ������ �׷� ��帶ũ�� �ϼ��մϴ�.
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

// ���� ���ý� ó��
HTvoid HTGuild::HT_bGuild_DialogBoxEmblemSelect()
{
	// ������ �ֽſ� ���� �ε����� �޸� ���
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
	
	//	��帶ũ ���� ��û
	if (this->m_iSelectWindow == 0)
		this->HT_vNetWork_CSP_MSG_GuildUpdateMark( 1 );
	else //	���� ��� ��ũ�� ������ ȣ��
		this->HT_vNetWork_CSP_MSG_GuildUpdateMark( 2 );

	// NPC ��ȭ���� ����
	g_cNPCControl->HT_vNPCControl_Create_GuildMark();
}

// ������ ���� �õ��� ȣ�� (�̰����� �Է���ġ�κ��� ���� ������ ó���Ѵ�.)
void HTGuild::HT_vGuild_InputCheckForEmblemSelecting(int iAction, int iTarget, int iTargetID)
{
	switch(iTarget)
	{
	case UI_TARGET_BUTTON:	// ��ư�� ��� ó��
		switch(iTargetID)
		{
		case -2:// ��׶��� �ٿ��
			break;
		case -1:// �����ư
		case 201:	// ��ҹ�ư
			g_cUIManager->HT_HideWindow(_DIALOG_AMBLEM);
			break;
		case 200: // Ȯ�ι�ư
			g_cGuildSystem->HT_bGuild_DialogBoxEmblemSelect();
			break;
		case 1:	// �� ��ư = ��湮��
		case 2: // ����
		case 3: // ����
		case 4: // ����
			g_cGuildSystem->HT_vGuild_DialogBoxDrawTab(iTargetID);
			break;
		}

		if (iTargetID >= 100 && iTargetID < 142)	// �ں� ��ư Ŭ����
			g_cGuildSystem->HT_bGuild_DialogBoxDrawEmblem(iTargetID-100);
		break;
	}
}


//	�Է� �޼��� ó��
//	AshramInfo
void HTGuild::HT_vGuild_InputCheckForAshramInfo(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cUIManager->HT_HideWindow(_DIALOG_ASHRAMINFO);
		}
		//	Button �����ο�
		else if( iTargetID == 20 )
		{
			HTint iPosX, iPosY;
			g_cUIManager->HT_GetWindowPos( _DIALOG_ASHRAMINFO, iPosX, iPosY );
			g_cUIManager->HT_HideWindow( _DIALOG_ASHRAMINFO );
			g_cUIManager->HT_ShowWindow( _DIALOG_ASHRAMMEMBERLISET );
			g_cUIManager->HT_MoveWindow( _DIALOG_ASHRAMMEMBERLISET, iPosX, iPosY );
		}
		//	Button Ȩ������
		else if( iTargetID == 21 )
		{
			CHTString strString;
			if ( g_cGuildSystem->m_oGuildInfo.GuildID != 0 && g_cGuildSystem->m_byGuild_GuilAuthority == GUILD_AUTHORITY_MAHARAJA )
			{
				if ( g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogOpenWarning, &strString ) )
				{
					// �ش� ��αװ� ��ü ȭ������ Ȱ��ȭ �˴ϴ�. ����Ͻðڽ��ϱ�?
					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 1 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_MAKEBLOG;
				}
			}
			else
			{
				if ( g_pMessageMgr->HT_bGetMessage( eMsgGuildBlogMakeErr, &strString ) )
				{
					// �ƽ����� ���ԵǾ� ���� �ʰų� ���϶��ڰ� �ƴ� ��� �ƽ��� ��α� ������ �� �� �����ϴ�.
					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 0 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_NONE;
				}
			}
		}
		//	Button Ȩ������
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
					// �ƽ����� ���ԵǾ� ���� ���� ��� �ƽ��� ��α׿� ������ �� �����ϴ�.
					g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMINFO, strString.HT_szGetString(), 0 );
					//	MessageBox Type
					g_cGuildSystem->m_iGuild_MsgBoxType = GUILDTYPE_CONFIRM_NONE;
				}
			}						
		}
		//	Button ���κ�α�
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
		//	Ȯ��
		if( iTargetID == 2 )
		{
			//	MessageBox Type
			if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_MAKEBLOG )
			{
				HTint iServer = 0;
				if ( g_gServerType == SERVERTYPE_TEST ) iServer = 0;	// Test Server : 0
				else
				{
					// Main Server : ���� �ϵ� �ڵ�
					// ������ - 1, ��߳� - 2, ũ���� - 3, ��Ʈ�� - 4, ������ - 5
					if ( g_strSelectServerName == _T("������") )		{ iServer = 1; }
					else if ( g_strSelectServerName == _T("��߳�") )	{ iServer = 2; }
					else if ( g_strSelectServerName == _T("ũ����") )	{ iServer = 3; }
					else if ( g_strSelectServerName == _T("��Ʈ��") )	{ iServer = 4; }
					else if ( g_strSelectServerName == _T("������") )	{ iServer = 5; }
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
					//				(HTtchar*)g_strLoginID, (HTtchar*)g_strLgoinPasswordMD5,	// Log In ����
					//				(HTtchar*)g_strLoginID,										// ������ ���̵� (nm_master)
					//				(HTtchar*)g_cGuildSystem->HT_strGuild_GetGuildName(),		// �ƽ����� (nm_ashiram)
					//				g_cMainCharacter->m_iGuildSerial,							// �ƽ���������ȣ (no_ashiram)
					//				iServer );													// ������ȣ (no_server)
				}

				HTRESULT hResult = HT_OK;
				if ( HT_FAILED( hResult = g_pEngineHandler->HT_hrOpenWebWithPost( g_hWnd, strWeb, strWebParam, 10 ) ) )
				{
					CHTString strString;

					// ��α� ������ �������� �ʽ��ϴ�. ��� �Ŀ� �ٽ� �õ��� �ֽñ� �ٶ��ϴ�.
					// ��α� ������ �����ϱ� ���� ���α׷� �ʱ�ȭ�� �����߽��ϴ�.
					// ��α� ���� ���� �ʱ�ȭ�� �����߽��ϴ�.
					// ��α� ���� ������ ���� ���α׷� �˻��� �����߽��ϴ�.
					// ��α� ������ �� �� ���� ������ �˷��Խ��ϴ�.
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
					// Main Server : ���� �ϵ� �ڵ�
					// ������ - 1, ��߳� - 2, ũ���� - 3, ��Ʈ�� - 4, ������ - 5
					if ( g_strSelectServerName == _T("������") )		{ iServer = 1; }
					else if ( g_strSelectServerName == _T("��߳�") )	{ iServer = 2; }
					else if ( g_strSelectServerName == _T("ũ����") )	{ iServer = 3; }
					else if ( g_strSelectServerName == _T("��Ʈ��") )	{ iServer = 4; }
					else if ( g_strSelectServerName == _T("������") )	{ iServer = 5; }
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
						(HTtchar*)g_strLgoinPasswordMD5 );	// Log In ����
						
						//strWebParam.HT_szFormat( _T("returnurl=http://home.hanbiton.com/guild/game.aspx&nm_game=tantra&userid=%s&userpw=%s&nm_ashiram=%s&no_ashiram=%d&no_server=%d"),
						//			(HTtchar*)g_strLoginID, (HTtchar*)g_strLgoinPasswordMD5,	// Log In ����
						//			(HTtchar*)g_cGuildSystem->HT_strGuild_GetGuildName(),		// �ƽ����� (nm_ashiram)
						//			g_cMainCharacter->m_iGuildSerial,							// �ƽ���������ȣ (no_ashiram)
						//			iServer );													// ������ȣ (no_server)
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
				strWebParam.HT_szFormat( _T("returnurl=http://home.hanbiton.com/minible/home/main.aspx&nm_game=tantra&userid=%s&userpw=%s&id=%s"), (HTtchar*)g_strLoginID, (HTtchar*)g_strLgoinPasswordMD5, (HTtchar*)g_strLoginID );	// ����� ���̵� (userid)

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
					strWebParam.HT_szFormat( _T("returnurl=http://home.hanbiton.com/minible/home/main.aspx&nm_game=tantra&userid=%s&userpw=%s&id=%s"), (HTtchar*)g_strLoginID, (HTtchar*)g_strLgoinPasswordMD5, (HTtchar*)strClickAccount );	// ����� ���̵� (userid)

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
				strWebParam.HT_szFormat( _T("returnurl=http://home.hanbiton.com/h_game/h_space/main.aspx&nm_game=tantra&userid=%s&userpw=%s"), (HTtchar*)g_strLoginID, (HTtchar*)g_strLgoinPasswordMD5 );	// ����� ���̵� (userid)
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
            //	���� �ƽ��� ��û
			else if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_REQALLIANCE )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg2, &strString, g_cGuildSystem->m_strAshuramGuildJoin_SendCharName.HT_szGetString() );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				// ������ ��Ŷ �����ϱ�
				g_cGuildSystem->HT_vGuildNet_CSP_AshuramGuild(1,1,0);
				// ����
				g_cGuildSystem->m_byAshuramGuildJoin_ResponseReason = 1;
			}
			//	���� �ƽ��� ��û�� ���� ����
			else if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_RECIVEALLIANCE )
			{
				// ������ ��Ŷ �����ϱ� (������)
				g_cGuildSystem->HT_vGuildNet_CSP_AshuramGuild(1,1,1);
				// ����
				g_cGuildSystem->m_byAshuramGuildJoin_ResponseReason = 1;
			}
		}
		else if( iTargetID == 3 )
		{
			//	���� �ƽ��� ��û
			if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_REQALLIANCE )
			{
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg8, &strString );
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				g_cGuildSystem->m_byAshuramGuildJoin_ResponseReason = 0;	// ���
			}
			//	���� �ƽ��� ��û�� ���� ����
			else if( g_cGuildSystem->m_iGuild_MsgBoxType == GUILDTYPE_CONFIRM_RECIVEALLIANCE )
			{
				// ������ ��Ŷ �����ϱ� (�ź���)
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
		//	Button ���
		else if( iTargetID>=10 && iTargetID<20 )
		{
			g_cGuildSystem->m_strGuild_ListSelectdName = g_cUIManager->HT_GetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, iTargetID );
			//	�ӼӸ� ���·� ����� �ְ�..
			g_cChatting->HT_vChatting_SetWisper( g_cGuildSystem->m_strGuild_ListSelectdName );
		}
		//	Button �ƽ�������
		else if( iTargetID == 50 )
		{
			HTint iPosX, iPosY;
			g_cUIManager->HT_GetWindowPos( _DIALOG_ASHRAMMEMBERLISET, iPosX, iPosY );
			g_cUIManager->HT_HideWindow( _DIALOG_ASHRAMMEMBERLISET );
			g_cUIManager->HT_ShowWindow( _DIALOG_ASHRAMINFO );
			g_cUIManager->HT_MoveWindow( _DIALOG_ASHRAMINFO, iPosX, iPosY );
		}
		//	Button ����
		else if( iTargetID == 51 )
		{
			g_cGuildSystem->m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_JOIN;
			//	������ ����� �ٲ�� ������ �ش�.
		}
		//	Button Ż��
		else if( iTargetID == 52 )
		{
			if( !g_cGuildSystem->m_strGuild_GuildName.HT_bIsEmpty() )
			{
				CHTString strTemp;
				//	��帶�����̰�, ������ �̸���  ������
				if( !g_cGuildSystem->m_strGuild_ListSelectdName.HT_bIsEmpty() &&
					g_cGuildSystem->m_byGuild_GuilAuthority == GUILD_AUTHORITY_MAHARAJA )
				{
					//	������ �̸��� ���ڽ��� �ƴҶ�
					if( g_cGuildSystem->m_strGuild_ListSelectdName.HT_iStringCompare( g_oMainCharacterInfo.szCharName ) != 0 )
					{
						g_cGuildSystem->m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_EXPEL;
						// %s ���� ��忡�� ���� �Ͻðڽ��ϱ�?
						HT_g_Script_SetMessage( eMsgGuildReqDelMemberQuestion, &strTemp, g_cGuildSystem->m_strGuild_ListSelectdName.HT_szGetString() );
						g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, strTemp.HT_szGetString(), 1 );
					}
					else
					{
						// ���վƽ����� ���� ���¿��� Ż�� �Ұ�
						if (strcmp(g_cGuildSystem->m_strAlliedGuildName[0].HT_szGetString(), " ") != 0)
						{
							HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg13, &strTemp, g_cGuildSystem->m_strAshuramGuildJoin_SendCharName.HT_szGetString() );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
						}
						else
						{
							g_cGuildSystem->m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_DESTROY;
							// ���� ��忡�� Ż���Ͻ÷ƴϱ�?
							HT_g_Script_SetMessage( eMsgGuildReqSecessionQuestion, &strTemp, _T("") );
							g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, strTemp.HT_szGetString(), 1 );
						}
					}
				}
				else
				{
					if( g_cGuildSystem->m_byGuild_GuilAuthority == GUILD_AUTHORITY_MAHARAJA )
					{
						// ���� �ƽ����� ���� ���¿��� Ż�� �Ұ�
						if (strcmp(g_cGuildSystem->m_strAlliedGuildName[0].HT_szGetString(), " ") != 0)
						{
							HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg13, &strTemp, g_cGuildSystem->m_strAshuramGuildJoin_SendCharName.HT_szGetString() );
							g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
						}
						else
						{
							g_cGuildSystem->m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_DESTROY;
							// ���� ��忡�� Ż���Ͻ÷ƴϱ�?
							HT_g_Script_SetMessage( eMsgGuildReqSecessionQuestion, &strTemp, _T("") );
							g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, strTemp.HT_szGetString(), 1 );
						}
					}
					else
					{
						g_cGuildSystem->m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_SECEDE;
						// ���� ��忡�� Ż���Ͻ÷ƴϱ�?
						HT_g_Script_SetMessage( eMsgGuildReqSecessionQuestion, &strTemp, _T("") );
						g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, strTemp.HT_szGetString(), 1 );
					}
				}
			}
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		//	Ȯ��
		if( iTargetID == 2 )
		{
			switch( g_cGuildSystem->m_byGuild_ConfirmGrade )
			{
				//	���Կ�û�� �˷���
				case GUILDTYPE_CONFIRM_JOINNOTIFY :
					//	��� ���� ����
					g_cGuildSystem->HT_vNetWork_CSP_CNFGuild();
					break;
				//	Ż��, ����, ��ü
				case GUILDTYPE_CONFIRM_SECEDE :
				case GUILDTYPE_CONFIRM_EXPEL :
				case GUILDTYPE_CONFIRM_DESTROY :
					g_cGuildSystem->HT_vNetWork_CSP_Remove_GuildMember();
					break;
			}
		}
		//	Ȯ�� �ܰ�
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

		//	�������� ��� ������ ���� Ŭ��������
		if( iTargetID == -1 || iTargetID == -2 )
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
		//	�������� Ŭ���ϴ� �������� �̺�Ʈ�� �߻��� ��� �� �׷��� Ŭ���� �������� �˾��Ҽ� �ִ��� Ȯ���ϴ� ������ �ʿ��� �ϴ��� ����� �д�.
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
		//	������ ���Կ� �������� ������ �������� �ʰ� ó��
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
			//	���� ������ ���Ǿ� üũ
			if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < 2000000 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgAshramFaildShortOfRupia, &strMessage, _T(""), _T("") );	//	���Ǿư� �����Ͽ� ��û�Ͻ� �۾��� �����Ҽ� �����ϴ�.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage );
				return;
			}
			//	Ashram Cargo Extence Type
			g_cGuildSystem->m_byAshramCargoExtenceType = 1;
			g_cUIManager->HT_SetScriptMessage( eMsgAshramReqNeedRupia, &strMessage, _T(""), _T("") );	//	�����Ͻ� �ƽ��� â��� 200�� ���Ǿư� �ʿ��մϴ�.\n ���� ����Ͻðڽ��ϱ�?
			strTemp.HT_szFormat( strMessage, 200 );
			g_cUIManager->HT_MessageBox( _DIALOG_SANCTIONASHCAGO, strTemp, 1 );
		}
		else if( iTargetID == 2 )
		{
			//	���� ������ ���Ǿ� üũ
			if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < 3000000 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgAshramFaildShortOfRupia, &strMessage, _T(""), _T("") );	//	���Ǿư� �����Ͽ� ��û�Ͻ� �۾��� �����Ҽ� �����ϴ�.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage );
				return;
			}
			//	Ashram Cargo Extence Type
			g_cGuildSystem->m_byAshramCargoExtenceType = 2;
			g_cUIManager->HT_SetScriptMessage( eMsgAshramReqNeedRupia, &strMessage, _T(""), _T("") );	//	�����Ͻ� �ƽ��� â��� 300�� ���Ǿư� �ʿ��մϴ�.\n ���� ����Ͻðڽ��ϱ�?
			strTemp.HT_szFormat( strMessage, 300 );
			g_cUIManager->HT_MessageBox( _DIALOG_SANCTIONASHCAGO, strTemp, 1 );
		}
		else if( iTargetID == 3 )
		{
			//	���� ������ ���Ǿ� üũ
			if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < 3500000 )
			{
				g_cUIManager->HT_SetScriptMessage( eMsgAshramFaildShortOfRupia, &strMessage, _T(""), _T("") );	//	���Ǿư� �����Ͽ� ��û�Ͻ� �۾��� �����Ҽ� �����ϴ�.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage );
				return;
			}
			//	Ashram Cargo Extence Type
			g_cGuildSystem->m_byAshramCargoExtenceType = 3;
			g_cUIManager->HT_SetScriptMessage( eMsgAshramReqNeedRupia, &strMessage, _T(""), _T("") );	//	�����Ͻ� �ƽ��� â��� 350�� ���Ǿư� �ʿ��մϴ�.\n ���� ����Ͻðڽ��ϱ�?
			strTemp.HT_szFormat( strMessage, 350 );
			g_cUIManager->HT_MessageBox( _DIALOG_SANCTIONASHCAGO, strTemp, 1 );
		}
	}
	else if( iTarget == UI_TARGET_MESSAGEBOX )
	{
		//	Ȯ�� ��ư
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
		//	â��1 ����
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
		//	â��2 ����
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
		//	â��3 ����
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


// ���â�� �ƽ��� �� �ֽŸ�ũ ���̱�
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

//	��ȭ���� Ȱ��ȭ/��Ȱ��ȭ
HTvoid HTGuild::HT_vGuild_DialogBoxActive()
{
	//	GM�̸� ��ŵ
	if( g_oMainCharacterInfo.snTribe == 0x09 )
		return;

	//	������� â�� ���� ������ ������� â�� �ݰ�
	if( g_cUIManager->HT_isShowWindow( _DIALOG_ASHRAMMEMBERLISET ) )
	{
		g_cUIManager->HT_HideWindow( _DIALOG_ASHRAMMEMBERLISET );
	}
	//	��� ����â�� ���� ������ ��� ����â�� �ݴ´�.
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
//	��ȭ���� ��Ȱ��ȭ
HTvoid HTGuild::HT_vGuild_DialogBoxAntiActive()
{
}

//	â��
HTvoid HTGuild::HT_vGuild_Create()
{
	//	�ٳ�Ÿ���Լ��� ��带 â�� �� �� �ֵ���
	if( g_cNPCControl->HT_bNPCControl_IsGuilCreateStep() == HT_TRUE )
	{
		if( m_strGuild_GuildName.HT_bIsEmpty() )							//	��尡 ��������...
		{
			//	Set Language
			g_cChatting->HT_vChatting_SetOpenMessageItem( 1, 0, 0 );
		}
		else
		{
			CHTString szMessage;
			// ��忡 ���ԵǾ� ���� �������� â�� �����մϴ�.
			HT_vGuild_SetMessage( eMsgGuildCreateOtherJoinErr, &szMessage );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		}
	}
}

// ��� ��ũ �����ϴ� â ����
HTvoid HTGuild::HT_vGuild_AmblemMakeActive()
{
	if( m_strGuild_GuildMasterName.HT_iStringCompare( g_oMainCharacterInfo.szCharName ) == 0 && //	��� �����Ͱ� �ƴϸ� ����
		g_cEquipInventory->HT_iEquipInventory_GetPCMoney() >= GUILD_MARK_NEED_MONEY )	//	�� üũ_���Ǿ� 3000000 �̻��϶��� ��������
	{
		this->m_iSelectWindow = 0;	// �Ϲ� �ƽ��� ����� â���� ����
		this->HT_vGuild_DialogBoxDrawTab(1);
		this->HT_bGuild_DialogBoxDrawEmblem(0);
		g_cUIManager->HT_ShowWindow(_DIALOG_AMBLEM);
	}
	else
	{
		CHTString szMessage;
		// ���Ǿ� 3000000�̻��϶��� ��帶���͸��� ��帶ũ�� �����Ҽ� �ֽ��ϴ�.
		HT_vGuild_SetMessage( eMsgGuildMarkConditionErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
	}
}

//	����
HTRESULT HTGuild::HT_vGuild_JoinGuild( HTint iObjectID )
{
	//	��� ���� ��ư�� ���� ���°� �ƴϸ� ��ŵ
	if( m_byGuild_ConfirmGrade != GUILDTYPE_CONFIRM_JOIN )
		return HT_FAIL;
		
	//	���� ������� �ƴϸ� ��ŵ
	byte byAuthority =  g_cGuildSystem->HT_byGuild_GetAuthority();
	if(! (byAuthority == GUILD_AUTHORITY_MAHARAJA || byAuthority == GUILD_AUTHORITY_RAJA || byAuthority == GUILD_AUTHORITY_PROOBAJA) )
		return HT_FAIL;
//	if( m_strGuild_GuildMasterName.HT_iStringCompare( g_oMainCharacterInfo.szCharName ) != 0 )
//		return HT_FAIL;

	// NPC�� ��ȭ���̰ų� �ٸ� ����� Ʈ���̵带 �ϰ� �ִ� ���̸� ó�� ���� ����
	if( g_cUIManager->HT_isShowWindow( _DIALOG_NPCWINDOW ) )
		return HT_FAIL;

	//	������ Ű���̵� �˾ƿ��� 
	m_dwGuild_JoinGuildKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( iObjectID );

	if( m_dwGuild_JoinGuildKeyID == 0 )
	   return HT_FAIL;

	//	������ �ֽ��� ���� �ֽŰ� �������� ������ ��ŵ
	if( g_oMainCharacterInfo.byTrimuriti != g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTrimuriti(m_dwGuild_JoinGuildKeyID) )
		return HT_FAIL;

	//----------��� ���� ��û----------//
	this->HT_vNetWork_CSP_REQGuild();
	// ��� ���� ��û �Ŀ� ������ ĳ���Ϳ��� �ٸ� �䱸�� �� �� �ֵ��� �ϱ� ���ؼ�
	// ��� ���� ��ư�� ������ ���� ���·� �ʱ�ȭ �Ѵ�.
	m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_NONE;

	return HT_OK;
}

//	��� �ʱ� ������ �޽��ϴ�.
HTvoid HTGuild::HT_vNetWork_SCP_INIT_GUILD( MSG_GuildInfo* info )
{
	HTint i;
	CHTString strTemp;

	m_strAlliedGuildName[0] = info->AlliedGuildName1;					// ���� ��� �̸�1
	m_strAlliedGuildName[1] = info->AlliedGuildName2;					// ���� ��� �̸�2
	m_strEnemyGuildName[0] = info->EnemyGuildName1;					// ���� ��� �̸�1

	for( i=0 ; i<2 ; i++ )
	{
		if( m_strAlliedGuildName[i].HT_bIsEmpty() )
            m_strAlliedGuildName[i] = _T(" ");
		if( m_strEnemyGuildName[i].HT_bIsEmpty() )
            m_strEnemyGuildName[i] = _T(" ");
	}

	if( info->GuildID == -1 )
	{
		//	�޽���â �ٿ��
		m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_ERROR;
		CHTString szMessage;
		// �ƽ��� â���� �����߽��ϴ�
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
		//	����
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 10, m_oGuildInfo.GuildName );
		//	��� ����
		g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 17, m_oGuildInfo.GuildMessage );

		this->HT_hrGetGuildMark(info->Mark, &m_iColor, &m_iTitle, &m_iEmblem);
		
		for( i=0 ; i<MAX_GUILD_MEMBER ; i++ )
		{
			CHTString strTempName = m_oGuildInfo.Member[i].MemberName;
			if( !strTempName.HT_bIsEmpty() )
			{
				//	�ٸ� ĳ���Ϳ��� ��� ��ũ ���� �ϱ�
				g_cOtherObjectSystem->HT_vOtherObjectSystem_SetGuildMarkID( strTempName, m_dwGuild_EmblemID, m_strGuild_GuildName.HT_szGetString() );
				//	��� ����Ʈ�� ����
				S_GUILD_DATA* psNewNode;
				psNewNode = new S_GUILD_DATA;
				memcpy( &psNewNode->info, &info->Member[i], sizeof(STRUCT_GUILD_MEMBER) );
				this->HT_LL_hrInsertAfter( psNewNode );
				HT_DELETE( psNewNode );

				//	���� ��峻 ������ ����
				strTempName = m_oGuildInfo.Member[i].MemberName;
				if( strTempName.HT_iStringCompare(g_oMainCharacterInfo.szCharName) == 0 )
                    m_byGuild_GuilAuthority = m_oGuildInfo.Member[i].GuildRank;

				//	��帶��Ʈ�� �̸� ����
				if( m_oGuildInfo.Member[i].GuildRank == GUILD_AUTHORITY_MAHARAJA )
				{
					m_strGuild_GuildMasterName = m_oGuildInfo.Member[i].MemberName;
				}
			}
		}

		// ��带 ó�� �������� �� NPC�� ��ȭ�� �ٲٱ� ���ؼ�
		g_cNPCControl->HT_vNPCControl_Create_Guild();
	}

	//	UI�� ����
	this->HT_vGuild_Display();

	if( m_dwGuild_EmblemID > 0 )
	{
		//	��� ��ũ ǥ�� �ϱ�
		this->HT_vGuild_EmblemOn();
		//	��� ��ũ ǥ�� �ϱ�
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowGuildMark();
	}

	if( m_oGuildInfo.GuildMessage[0] != '\0' )
	{
		HT_vGuild_SetMessage( eMsgCommonSystemAshuram, &strTemp ); // [�ƽ���]
		strTemp += m_oGuildInfo.GuildMessage;
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strTemp );
	}

	//	���� ������ ����� �ִ��� �ľ�
	m_iMyStrongGuildIndex = -1;
	for( i=0 ; i<eStronghold_MaxCount ; i++ )
	{
		if( m_strGuild_GuildName.HT_iStringCompare( m_strStrongGuildName[i].HT_szGetString() ) == 0 ||
			m_strAlliedGuildName[0].HT_iStringCompare( m_strStrongGuildName[i] ) == 0 ||
			m_strAlliedGuildName[1].HT_iStringCompare( m_strStrongGuildName[i] ) == 0 )
		{
			m_bMyStrongGuild = TRUE;
			m_iMyStrongGuildIndex = i;
			//	���� ������ ���
			if( m_strGuild_GuildName.HT_iStringCompare( m_strStrongGuildName[i].HT_szGetString() ) == 0 )
			{
				HT_vGuild_SetMessage( eMsgCommonDurga0 + m_iMyStrongGuildIndex, &strTemp );
				//	Display Ashram Name
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, strTemp.HT_szGetString() );
			}
			//	���� �ƽ����� ������ ���
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

//	��� ������ ��û�Ѵ�.
HTRESULT HTGuild::HT_hrNetWork_CSP_REQ_CREATE_GUILD( CHTString strAshramName )
{
	//	�ֽ� üũ
	if( g_oMainCharacterInfo.byTrimuriti == 0 )
	{
		CHTString szMessage;
		// �ֽ� ���� �Ŀ� �ƽ����� ������ �� �ֽ��ϴ�.
		HT_vGuild_SetMessage( eMsgGuildCreateNoTrimuritiErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		return HT_FAIL;
	}
    //	�� üũ_���Ǿ� 300000 �̻��϶��� ��������
	if( g_cEquipInventory->HT_iEquipInventory_GetPCMoney() < GUILD_CREATE_NEED_MONEY )
	{
		CHTString szMessage;
		// �ƽ����� ����� ���ؼ��� 300000 ���Ǿư� �ʿ��մϴ�.
		HT_vGuild_SetMessage( eMsgGuildCreateNeedMoneyErr, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );
		return HT_FAIL;
	}
	//	���ڰ� ��������
	if( strAshramName.HT_nGetSize() < 4 ||
		strAshramName.HT_nGetSize() > 18 )
	{
		CHTString szMessage;
		// �ƽ������� ���̴� ������� 4�ں��� ����� �� �ֽ��ϴ�.
		HT_vGuild_SetMessage( eMsgGuildMarkConditionErr2, &szMessage );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, szMessage );

		return HT_FAIL;
	}

	//	%��ȣ�� ������ ��ŵ
	if( strAshramName.HT_bFind( "%" ) )
		return HT_FAIL;

	m_strGuild_GuildName = strAshramName;

	//	����ġ ���� �ܾ ��� �������� �ٷ� ��ŵ �� ������. �޽����� �־���� �Ұ͵� ������ ��..
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

//	�ű� ������ ������ �����鿡�� �����Ѵ�.
HTvoid HTGuild::HT_vNetWork_SCP_AddGuildMember( MSG_AddGuildMember* info )
{
	S_GUILD_DATA* psNewNode;
	psNewNode = new S_GUILD_DATA;
	memcpy( &psNewNode->info, &info->Member, sizeof(STRUCT_GUILD_MEMBER) );
	//	ĳ���� ���� ����
	this->HT_LL_hrInsertAfter( psNewNode );
	HT_DELETE( psNewNode );

	//	UI�� ����
	this->HT_vGuild_Display();

	//	�ٸ� ĳ���Ϳ��� ��� ��ũ ���� �ϱ�
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetGuildMarkID( info->Member.MemberName, m_dwGuild_EmblemID, m_strGuild_GuildName.HT_szGetString() );
	//	��� ��ũ ǥ�� �ϱ�
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowGuildMark();
	//	��� ��ũ ǥ�� �ϱ�
	this->HT_vGuild_EmblemOn();
}

//	��� Ż��/��ü/������ ��û�Ѵ�.
HTvoid HTGuild::HT_vNetWork_CSP_Remove_GuildMember()
{
	MSG_RemoveGuildMember* info = HT_NULL;
	info = new MSG_RemoveGuildMember;
	info->GuildID = m_oGuildInfo.GuildID;

	switch( m_byGuild_ConfirmGrade )
	{
		//	Ż��
		case GUILDTYPE_CONFIRM_SECEDE :
			info->byRemoveType = 1;
			CHTString::HT_hrStringCopy( info->CharacterName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH);
			break;
		//	����
		case GUILDTYPE_CONFIRM_EXPEL :
			info->byRemoveType = 2;
			CHTString::HT_hrStringCopy( info->CharacterName, m_strGuild_ListSelectdName, SZNAME_LENGTH);
			break;
		//	��ü
		case GUILDTYPE_CONFIRM_DESTROY :
			info->byRemoveType = 3;
			CHTString::HT_hrStringCopy( info->CharacterName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH);
			break;
	}

	g_pNetWorkMgr->ReqestGuildDisbandMsg( info );
	HT_DELETE( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_Guild_Remove" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

HTvoid HTGuild::HT_vNetWork_SCP_RemoveGuildMember( MSG_RemoveGuildMember* info )
{
	CHTString strTempName = g_oMainCharacterInfo.szCharName;
	if( strTempName.HT_iStringCompare( info->CharacterName ) == 0 )
	{
		//	��� ����Ʈ�� �ο��� ���� ����
		this->HT_LL_hrDeleteAll();
		//	�޽���â �ٿ��
		m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_ERROR;
		
		CHTString szMessage;
		// �ƽ����� ��ü�Ǿ����ϴ�.
		HT_vGuild_SetMessage( eMsgGuildDissolutionOK, &szMessage );
		g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, szMessage.HT_szGetString(), 0 );
		//	����̸� Ŭ����
		m_strGuild_GuildName.HT_hrCleanUp();
		//	��� ��ũ ǥ�� ���ϱ�
		this->HT_vGuild_EmblemOff();
		m_dwGuild_EmblemID = 0;
		memcpy( &m_oGuildInfo, info, sizeof(MSG_GuildInfo) );

		// ��� ����â�� ���� ���� 2004. 11. 10 ������
		//g_bGuildMarkShow = HT_FALSE;
		m_iEmblem = -1;
		m_iTitle = -1;
		m_iColor = -1;

		// ��帶ũ �ʱ�ȭ
		g_cUIManager->HT_SetTextureControlColor(_DIALOG_ASHRAMINFO, 24, HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f));
		g_cUIManager->HT_SetTextureControlColor(_DIALOG_ASHRAMINFO, 25, HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f));
		g_cUIManager->HT_SetTextureControlColor(_DIALOG_ASHRAMINFO, 26, HT_COLOR(1.0f, 1.0f, 1.0f, 0.0f));

		m_byGuild_GuilAuthority = GUILD_AUTHORITY_NONE;

	}
	else
	{
		//----------LL ����Ÿ �����_�̸�����---------//
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetInitGuild( info->CharacterName );
		this->HT_LL_hrDeleteNode( info->CharacterName );
	}
}

//	��� ������ ��û�Ѵ�.
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

//	��� ������ ��û�� �޴´�.
HTvoid HTGuild::HT_vNetWork_SCP_REQGuild( MSG_REQGuild* info )
{
	m_byGuild_ConfirmGrade = GUILDTYPE_CONFIRM_JOINNOTIFY;
	CHTString strTempMsg;
	m_iGuild_TempGuildID = info->GuildID;
	// %s��忡�� ��� ������ ��û�߽��ϴ�.
	m_szMsgSting = info->GuildName;
	HT_vGuild_SetMessage( eMsgGuildReqReceive, &strTempMsg );
	g_cUIManager->HT_MessageBox( _DIALOG_ASHRAMMEMBERLISET, strTempMsg.HT_szGetString(), 1 );
}
//	��� ���� ��û ����� ������ �����Ѵ�.
HTvoid HTGuild::HT_vNetWork_CSP_CNFGuild()
{
	MSG_CNFGuild* info = HT_NULL;
	info = new MSG_CNFGuild;
	info->GuildID = m_iGuild_TempGuildID;
	strncpy( info->CharacterName, g_oMainCharacterInfo.szCharName, SZNAME_LENGTH );
	g_pNetWorkMgr->ReqestGuildCNFGuild( info );
	HT_DELETE( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqCnfGuild" );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;
}

//	������ ������
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
 
	//	UI�� ����
	this->HT_vGuild_Display();
/*
	// ������ ������ (ó���� ���Ӹ���Ʈ�� �ڽ��� ���ӿ� ���� ��� ��Ŷ�� �����Ƿ�, �ڽ��� �̸��� �ι� ȣ��Ǳ� �������� �� �޽����� ������� �ʴ´�.)
	// 2005. 1. 17 ������ (�߰� ��û)
	if (m_nGuildConnectMsg > 1) // ó�� ������ ��� ���� ���º��� ��� ����
	{
		if (strcmp(m_strGuild_CharacterName, g_oMainCharacterInfo.szCharName) == 0 ) // �ڽŰ� ĳ���� �̸��� ���ٸ� �÷��׺��� 1����
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
	if (strcmp(m_strGuild_CharacterName, g_oMainCharacterInfo.szCharName) == 0) // �ڽŰ� ĳ���� �̸��� ���ٸ� �÷��׺��� 1����
		m_nGuildConnectMsg++;
*/
}

//	������ ������ ����
HTvoid HTGuild::HT_vNetWork_SCP_GuildMemberout( MSG_GuildMemberout* info )
{
	if( m_strGuild_GuildName.HT_bIsEmpty() )
		return;

	//	��� ����Ʈ�� ����
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
 
	//	UI�� ����
	this->HT_vGuild_Display();

	// �� �޽����� ������ �ڽ��� ������ �ٸ� ������ ��� 
	// �ణ�� ���� �ð��� �ξ� �����ߴ��� ���ߴ����� üũ�ؾ� �Ѵ�.

	/*
	// ������ �����̽��ϴ�.
	CHTString szMessage;
	HT_vGuild_SetMessage( eMsgCommonGuildExit, &szMessage );
	g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, szMessage.HT_szGetString() );
	*/
}

//	��帶ũ ����
HTvoid HTGuild::HT_vNetWork_CSP_MSG_GuildUpdateMark( HTbyte byCostType )
{
	MSG_GuildUpdateMark* info = HT_NULL;
	info = new MSG_GuildUpdateMark;

	info->GuildID = m_oGuildInfo.GuildID;
	info->Mark = m_dwGuild_EmblemID;
	info->byCostType = byCostType;

	g_pNetWorkMgr->ReqestGuildMarkCreateMsg( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_GuildMarkCreate:%d, %d, costType = %d", info->Mark, info->byCostType, info->byCostType );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	��帶ũ ���� ���
HTvoid HTGuild::HT_vNetWork_SCP_MSG_GuildUpdateMark( MSG_GuildUpdateMark* info )
{
	if( info->byResult == REPLY_ACK_OK )
	{
		m_dwGuild_EmblemID = info->Mark;

		//	��� ��ũ ǥ�� �ϱ�
		this->HT_vGuild_EmblemOn();
		
		if( info->byCostType == 1 )
		{
			g_cEquipInventory->HT_vEquipInventory_SetPCMoney( info->nMoney );	// ���Ǿ� ����	2004. 11. 10 ������
		}

		//	��� ��ũ ǥ�� �ϱ�
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowGuildMark();
	}
	else if( info->byResult == REPLY_GUILDMARK_PARAM )
	{
		// �������� ����Ÿ�Դϴ�.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonSystemInvalidData, &strTemp, _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
	}
	else if( info->byResult == REPLY_GUILDMARK_RIGHT )
	{
		// ��ũ ���� ������ �����ϴ�.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonSystemNoRight, &strTemp, _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
	}
	else if( info->byResult == REPLY_GUILDMARK_MONEY )
	{
		if( info->byCostType == 1 )
		{
			// ���Ǿư� �����մϴ�.
			CHTString strTemp;
			HT_g_Script_SetMessage( eMsgCommonServerMoreRupia, &strTemp, _T("") );
            g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
		}
		else if( info->byCostType == 2 )
		{
			// Ÿ�ϰ� �����մϴ�.
			CHTString strTemp;
			HT_g_Script_SetMessage( eMsgCommonServerMoreTani, &strTemp, _T("") );
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
		}
	}
	else if( info->byResult == REPLY_UNKNOWN )
	{
		// ��ũ ���濡 ���� �߽��ϴ�.
		CHTString strTemp;
		HT_g_Script_SetMessage( eMsgCommonServerFaild, &strTemp, _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
	}
}

//	��������Ʈ_CSP
HTvoid HTGuild::HT_vNetWork_CSP_MSG_GuildUpdate( CHTString strMessage )
{
	//	�ѹ�3������ ���� ����
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

//	��������Ʈ_SCP
HTvoid HTGuild::HT_vNetWork_SCP_MSG_GuildUpdate( MSG_GuildUpdate* info )
{
    //	��� ��������1
	strncpy( m_oGuildInfo.GuildMessage, info->GuildMessage, GUILDMESSAGE_LENGTH );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 17, info->GuildMessage );

	if( strcmp(info->AlliedGuildName1, _T("")) == 0)
		strcpy(info->AlliedGuildName1, _T(" "));
	if( strcmp(info->AlliedGuildName2, _T("")) == 0)
		strcpy(info->AlliedGuildName2, _T(" "));
	if( strcmp(info->EnemyGuildName1, _T("")) == 0)
		strcpy(info->EnemyGuildName1, _T(" "));

	// �� ������Ʈ �޽����� ���� ��û�� ����, �ƽ����������� ���濡 ���� �����´�. ������ ��쿡�� ����Ǿ��ٴ� �޽����� �߰� ����ϵ��� �Ѵ�.
	if (! (strcmp( m_strAlliedGuildName[0].HT_szGetString(), info->AlliedGuildName1 ) == 0 &&
		strcmp( m_strAlliedGuildName[1].HT_szGetString(), info->AlliedGuildName2 ) == 0 &&
		strcmp( m_strEnemyGuildName[0].HT_szGetString(), info->EnemyGuildName1 ) == 0 ) )
	{
		if (strcmp(m_strAlliedGuildName[0].HT_szGetString(), " ") != 0)
		{
			CHTString strString;
			HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg8, &strString );	// �ƽ��� ���� ������ ���� �Ǿ����ϴ�.
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
		}
		else
		{
			CHTString strString;
			HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg9, &strString );	// �ƽ��� ���� ���谡 ���� �Ǿ����ϴ�.
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
		}
	}

	m_strAlliedGuildName[0] = info->AlliedGuildName1;				// ���� ��� �̸�1
	m_strAlliedGuildName[1] = info->AlliedGuildName2;				// ���� ��� �̸�2
	m_strEnemyGuildName[0] = info->EnemyGuildName1;					// ���� ��� �̸�1

	//	[���� ����1] [���� ����2]
	//	[%s] m_strAlliedGuildName[1].HT_szGetString()
	CHTString strTemp;
	strTemp.HT_szFormat( "[%s]", m_strAlliedGuildName[0].HT_szGetString() );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 18, strTemp.HT_szGetString() );

	//	���� ��忡�� Ż���� ���¶��,
	if( m_strAlliedGuildName[0].HT_iStringCompare( _T(" ") ) == 0 )
	{
		//	���� ��� ����� �����ߴ��� Ȯ���ϰ� �������� �ʾҴٸ� ���� ������ -1�� �����Ѵ�.
		BOOL bTrue = HT_FALSE;
		for(HTint i=0 ; i<4 ; i++ )
		{
			if( m_strGuild_GuildName.HT_iStringCompare( m_strStrongGuildName[i].HT_szGetString() ) == 0 )
				bTrue = HT_TRUE;
		}
		if( !bTrue )
			m_iMyStrongGuildIndex = -1;
	}
	//	���ý��ۿ� �����Ѵ�.
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetStrongAshiram( m_strAlliedGuildName[0].HT_szGetString(), m_strAlliedGuildName[1].HT_szGetString() );
	//	Setting	Targetting
	g_cOtherObjectSystem->HT_vOtherObjectSystem_SetTargetting();
}

//	��� ��� ������Ʈ_SCP
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

//	��� ��ŷ ������Ʈ_CSP
HTvoid HTGuild::HT_vNetWork_CSP_MSG_GuildSetRanking( CHTString strTemp )
{
	//	���� ������϶��� ����
	//if( m_byGuild_GuilAuthority != eGuildMaster )
	//	return;

	char chName[SZNAME_LENGTH];
	char chRank[SZNAME_LENGTH];
	// �޽����� �ִ� ���̿� ID�� �ִ� ���̰� �ִٸ� �߰� �� ��.
	HTchar tokenMsg[MAX_CHAT_LENGTH] = "\0";
	strncpy( tokenMsg, strTemp, MAX_CHAT_LENGTH );
	sscanf( tokenMsg, "%s %s", chName, chRank );

	MSG_GuildSetRanking* info;
	info = new MSG_GuildSetRanking;

	info->nGuildID = m_oGuildInfo.GuildID;
	strncpy( info->CharacterName, chName, SZNAME_LENGTH );
	CHTString strRank = chRank;

	CHTString szRaja, szPrubaja, szDandeca, szTapasa;
	HT_vGuild_SetMessage( eMsgCommonGuildRaja	, &szRaja );	// ����
	HT_vGuild_SetMessage( eMsgCommonGuildPrubaja, &szPrubaja ); // �������
	HT_vGuild_SetMessage( eMsgCommonGuildDandeca, &szDandeca ); // �ܵ�ī
	HT_vGuild_SetMessage( eMsgCommonGuildTapasa	, &szTapasa );	// Ÿ�Ļ�
	
	if( strRank.HT_iStringCompare( szRaja.HT_szGetString() ) == 0 ) // ����
		info->GuildRank = eGuildSubMaster;
	else if( strRank.HT_iStringCompare( szPrubaja.HT_szGetString() ) == 0 ) // �������
		info->GuildRank = eGuildThird;
	else if( strRank.HT_iStringCompare( szDandeca.HT_szGetString() ) == 0 ) // �ܵ�ī
		info->GuildRank = eGuildForth;
	else if( strRank.HT_iStringCompare( szTapasa.HT_szGetString() ) == 0 ) // Ÿ�Ļ�
		info->GuildRank = eGuildMember;

	g_pNetWorkMgr->ReqestGuildSetRanking( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_GuildSetGuildRank:%s,%s", chName, chRank );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	��� ��ŷ ������Ʈ_SCP
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

				// ������ ����� ������.
				if( m_strGuild_GuildMasterName.HT_iStringCompare(g_oMainCharacterInfo.szCharName) == 0 )
					m_byGuild_GuilAuthority = eGuildMaster;
				
			}
			return;
		}
		t = t->pNextNode;
	}

	this->HT_vGuild_Display();
}

//	���� ����Ʈ ��ȭ���ڿ� ǥ���ϱ�
HTvoid HTGuild::HT_vGuild_Display()
{
	//	�����̴� ��ȣ�� �˾ƿ´�.
	if( g_cUIManager->HT_isShowWindow( _DIALOG_ASHRAMMEMBERLISET ) )
	{
		m_iGuild_SlideBarCurPos = g_cUIManager->HT_GetScrollBarValue( _DIALOG_ASHRAMMEMBERLISET, 8 );
	}
	else
	{
		m_iGuild_SlideBarCurPos = 0;
	}

	//	��� ī��Ʈ�� ����
	HTint iMemberTotalCount;
	HTint iCurMember;
	CHTString strTemp;
	strTemp.HT_hrCleanUp();

	//	��帮��Ʈâ�� ǥ���ϱ� ����
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
		//	���ӿ���
		if( t->info.GuildState == 1 )
			iCurMember++;

		t = t->pNextNode;
	}

	//	���� ��� �ο� ǥ��
	strTemp.HT_szFormat( "%d/50", iMemberTotalCount );
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 15, strTemp.HT_szGetString() );
	//	���� ���� �ο� ǥ��
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
			//	���� �̸�
			strMemberName[iInsertCount] = t->info.MemberName;
			//	����
			strMemberLevel[iInsertCount].HT_szFormat( "%d", t->info.byLevel );

			//	����
			if( t->info.GuildRank == eGuildMaster )			// ���϶���
				HT_vGuild_SetMessage( eMsgCommonGuildMahaRaja, &strMemberAuthority[iInsertCount] );
			else if( t->info.GuildRank == eGuildSubMaster ) // ����
				HT_vGuild_SetMessage( eMsgCommonGuildRaja, &strMemberAuthority[iInsertCount] );
			else if( t->info.GuildRank == eGuildThird )		// ������
				HT_vGuild_SetMessage( eMsgCommonGuildPrubaja, &strMemberAuthority[iInsertCount] );
			else if( t->info.GuildRank == eGuildForth )		// �ܵ�ī
				HT_vGuild_SetMessage( eMsgCommonGuildDandeca, &strMemberAuthority[iInsertCount] );
			else // Ÿ�Ļ�
				HT_vGuild_SetMessage( eMsgCommonGuildTapasa, &strMemberAuthority[iInsertCount] );

			//	����
			if( t->info.snTribe == TRIBE_NAGA )				// ����
			{
				HT_vGuild_SetMessage( eMsgCommonTribeNaga, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23642;
			}
			else if( t->info.snTribe == TRIBE_KINNARA )		// Ų����
			{
				HT_vGuild_SetMessage( eMsgCommonTribeKimnara, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23650;
			}
			else if( t->info.snTribe == TRIBE_ASURA )		// �Ƽ���
			{
				HT_vGuild_SetMessage( eMsgCommonTribeAsura, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23644;
			}
			else if( t->info.snTribe == TRIBE_RAKSHASA )	// ������
			{
				HT_vGuild_SetMessage( eMsgCommonTribeRakshasa, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23652;
			}
			else if( t->info.snTribe == TRIBE_YAKSA )		// ��ũ��
			{
				HT_vGuild_SetMessage( eMsgCommonTribeYaksha, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23646;
			}
			else if( t->info.snTribe == TRIBE_GANDHARVA )	// ���ٸ���
			{
				HT_vGuild_SetMessage( eMsgCommonTribeGandharva, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23654;
			}
			else if( t->info.snTribe == TRIBE_DEVA )		// ����
			{
				HT_vGuild_SetMessage( eMsgCommonTribeDeva, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23648;
			}
			else if( t->info.snTribe == TRIBE_GARUDA )		// �����
			{
				HT_vGuild_SetMessage( eMsgCommonTribeGaruda, &strMemberTribe[iInsertCount] );
				iMemberTribeCode[iInsertCount] = 23656;
			}

			//	���ӿ���
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
			//	���� �̸�
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 10+i, strMemberName[i].HT_szGetString() );
			//	����
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 20+i, strMemberLevel[i].HT_szGetString() );
			//	����
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 30+i, strMemberAuthority[i].HT_szGetString() );
			//	���ӿ���
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
			//	����
			g_cUIManager->HT_SetTextureControlImage( _DIALOG_ASHRAMMEMBERLISET, 10+i, iMemberTribeCode[i] );
			g_cUIManager->HT_SetTextureControlScale( _DIALOG_ASHRAMMEMBERLISET, 10+i, 0, 0 );
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_ASHRAMMEMBERLISET, 10+i, HT_TRUE );
		}
		else
		{
			//	���� �̸�
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 10+i, _T("") );
			//	����
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 20+i, _T("") );
			//	����
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 30+i, _T("") );
			//	���ӿ���
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMMEMBERLISET, 40+i, _T("") );
			//	����
			g_cUIManager->HT_SetTextureControlImage( _DIALOG_ASHRAMMEMBERLISET, 10+i, 0 );
			g_cUIManager->HT_SetTextureControlDisplay( _DIALOG_ASHRAMMEMBERLISET, 10+i, HT_FALSE );
		}
	}
}

HTvoid HTGuild::HT_vGuild_SetEmblemID( DWORD dwEmblemID )
{
	m_dwGuild_EmblemID = dwEmblemID;
	//	��� ��ũ ǥ�� �ϱ�
	this->HT_vGuild_EmblemOn();
}

//	��� ��ũ ǥ�� �ϱ�
HTvoid HTGuild::HT_vGuild_EmblemOn()
{
	if( g_bGuildMarkShow )
	{
        g_pEngineHandler->HT_hrAttachGuildMark( g_cMainCharacter->HT_vMainChar_GetModelID(), m_dwGuild_EmblemID );
	}
}

//	��� ��ũ ǥ�� ���ϱ�
HTvoid HTGuild::HT_vGuild_EmblemOff()
{
	g_pEngineHandler->HT_hrDestroyGuildMark( g_cMainCharacter->HT_vMainChar_GetModelID() );
}

//	��� ��ũ ǥ�� ó��
HTvoid HTGuild::HT_vGuild_EmblemSwitch( CHTString strMessage )
{
	if( g_bGuildMarkShow == HT_TRUE )
	{
		g_bGuildMarkShow = HT_FALSE;
		//	��� ��ũ ǥ�� ���ϱ�
		this->HT_vGuild_EmblemOff();
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetHideGuildMark();
	}
	else
	{
		g_bGuildMarkShow = HT_TRUE;
		//	��� ��ũ ǥ�� �ϱ�
		this->HT_vGuild_EmblemOn();
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowGuildMark();
	}
}

//	�ֽ� ��ũ ǥ�� �ϱ� �ϱ�
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

//	�ֽ� ��ũ ǥ�� �ϱ� ���ϱ�
HTvoid HTGuild::HT_vTrimutiri_MarkOff()
{
	g_pEngineHandler->HT_hrDetachGodMark( g_cMainCharacter->HT_vMainChar_GetModelID() );
}

//	�ֽ� ��ũ ǥ�� ó��
HTvoid HTGuild::HT_vTrimutiri_MarkSwitch( CHTString strMessage )
{
	CHTString szCommand, szToken;
	HT_vGuild_SetMessage( eMsgCommonCommandTrimuritiMark, &szCommand );
	szToken = szCommand + _T(" %d"); // /�ֽŸ�ũ %d

	// �޽����� �ִ� ���̿� ID�� �ִ� ���̰� �ִٸ� �߰� �� ��.
	char tokenMsg[MAX_CHAT_LENGTH] = "\0";
	HTint iTrimuritiSw;
	CHTString::HT_hrStringCopy( tokenMsg, strMessage, MAX_CHAT_LENGTH );
	//sscanf( tokenMsg, "/�ֽŸ�ũ %d", &iTrimuritiSw );
	sscanf( tokenMsg, szToken.HT_szGetString(), &iTrimuritiSw );

	if( iTrimuritiSw == 0 )
	{
		g_bTrimuritiShow = HT_FALSE;
		//	��� ��ũ ǥ�� ���ϱ�
		this->HT_vTrimutiri_MarkOff();
		
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetHideTrimuritiMark();
	}
	else if( iTrimuritiSw == 1 )
	{
		g_bTrimuritiShow = HT_TRUE;
		//	��� ��ũ ǥ�� �ϱ�
		this->HT_vTrimutiri_MarkOn();
		
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetShowTrimuritiMark();
	}
}


//------------------------------------------------------------------------------
// Data manipulation functions
//------------------------------------------------------------------------------
//----------��ũ�� ����Ʈ ������ �κ�---------//
//----------LL �ʱ�ȭ---------//
HTvoid HTGuild::HT_LL_vInitList()
{
	m_pGuildList_Head = NULL;
	m_pGuildList_Tail = NULL;

	m_pGuildList_Head = new S_GUILD_DATA;
	m_pGuildList_Tail = new S_GUILD_DATA;
	
	m_pGuildList_Head->pNextNode = m_pGuildList_Tail;
}
//----------LL ����Ÿ ����-���� �̸��� ģ���� ������ �������� ������ ��� �ٷ� �ڿ�---------//
HTvoid HTGuild::HT_LL_hrInsertAfter( S_GUILD_DATA* info )
{
	S_GUILD_DATA *t;
	
	t = this->HT_LL_hrSerchNode( info->info.MemberName );

	//	����Ʈ�� ���̸�!
	if( t == m_pGuildList_Tail )
	{
		S_GUILD_DATA *s;
		s = NULL;
		s = new S_GUILD_DATA;
		memcpy( &s->info, &info->info, sizeof(STRUCT_GUILD_MEMBER) );
		s->pNextNode = m_pGuildList_Head->pNextNode;
		m_pGuildList_Head->pNextNode = s;
	}
	//	�ƴϸ�
	else
	{
		memcpy( &t->info, &info->info, sizeof(STRUCT_GUILD_MEMBER) );
	}
}
//----------LL ����Ÿ �����_�̸�����---------//
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
//----------LL ����Ÿ �����_�O��_�̸�����---------//
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
//----------LL ����Ÿ ���� ����_�ִ��� ������ �̸����� ����---------//
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
//----------LL ����Ÿ ���� �����---------//
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

	// ������ 3�� �� ��
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
	// ������ 2�� �� ��
	else if( sParam1 != eMsgParamNone && sParam2 != eMsgParamNone )
	{
		CHTString szOut1, szOut2;

		// sParam1
		HT_vGuild_SetParamTextForMessage( sParam1, &szOut1 );
		// sParam2
		HT_vGuild_SetParamTextForMessage( sParam2, &szOut2 );
		
		pstrMessage->HT_szFormat( szString.HT_szGetString(), szOut1.HT_szGetString(), szOut2.HT_szGetString() );
	}
	// ������ 1�� �� ��
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
		// �ٸ�ĳ���� �̸�
		case eMsgParamOthercharName	:
			*pszParam = m_strGuild_ListSelectdName;
			break;
		// �ʿ��� ��
		case eMsgParamNeedMoney:
			if( g_cNPCControl->HT_bNPCControl_IsGuilCreateStep( ) ) // ��� â��
				pszParam->HT_szFormat( "%d", GUILD_CREATE_NEED_MONEY );
			else // ��� ��ũ ����
				pszParam->HT_szFormat( "%d", GUILD_MARK_NEED_MONEY );
			break;
		// ��� �̸�
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

// �ƽ��� ���� �Ⱦ� ó��
HTRESULT HTGuild::HT_hrGuild_PickCheckFromOtherObject( HTint iObjectID )
{
	if( m_nAshuramGuildJoinMode == 1 )
	{

		m_iAshuramGuildJoin_SendCharKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetKeyID( iObjectID );

		// Step 1. ��� �ֽ��� �ڽ��� �ֽŰ� ���ƾ� ����
		if ( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetTrimuriti(m_iAshuramGuildJoin_SendCharKeyID) != g_oMainCharacterInfo.byTrimuriti )
		{
			CHTString strString;
			HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg12, &strString );	// ���� �ֽ��� ��븸 ������ �� �ֽ��ϴ�.
			g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );

			return HT_OK;
		}

		// Step 2. �ڽŰ� ��� ��� ����� �����ϰ� �ִ� ���¶�� �����޽��� ���
		if (m_bMyStrongGuild == HT_TRUE)
		{
			// ������ ���� ����
			CHTString GuildName = g_cOtherObjectSystem->HT_strOtherObjectSystem_GetAshiramNameFromKeyID(m_iAshuramGuildJoin_SendCharKeyID);

			if (GuildName.HT_szGetString() != NULL)
				for (HTint i=0; i<4; ++i)	// ������ ��� 4������ ���� ��
					if (strcmp(m_strStrongGuildName[i].HT_szGetString(), GuildName.HT_szGetString()) == 0)
					{
						CHTString strString;
						HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg17, &strString );	// ����� ������ �ƽ��������� ������ ���� �� �����ϴ�.
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
	info->byType = byType;	// 1 = ���� , 2 = ����
	info->byAct = byAct;	// 1 = �Ἲ , 2 = ��ü(���)
	info->byResult = byResult;	// 0 = ��û, 1~ = ����

	g_pNetWorkMgr->RequestMsgAshuramGuild( info );

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_AshuramGuild : nID = %d, byType = %d, byAct = %d, byResult = %d", info->nID, info->byType, info->byAct, info->byResult );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	Recive Challenger
HTvoid HTGuild::HT_vGuildNet_SCP_AshuramGuild( Msg_GuildAlliance* info )
{
	switch(int(info->byResult))
	{
		case 0:	// �ƽ������� ��û�� ���� ����ó��
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
//					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg3, &strString, m_strAshuramGuildJoin_SendCharName.HT_szGetString() );	// %s���� �ƽ��� ���� ��û�� �޾Ƶ鿴���ϴ�.
//					g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
				}
				else // 2
				{
//					CHTString strString;
//					HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg8, &strString );	// %s���� �ƽ��� ���� ��û�� �޾Ƶ鿴���ϴ�.
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
			{						// ���
				CHTString strString;
				HT_g_Script_SetMessage( eMsgCommonAshuramGuildMsg4, &strString, m_strAshuramGuildJoin_SendCharName.HT_szGetString() );	// %s���� �ƽ��� ���� ��û�� �޾Ƶ鿴���ϴ�.
				g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strString );
			}
			break;
	}
}

//	��� ���� �ƽ��� ��Ŷ
HTvoid HTGuild::HT_vGuildNet_SCP_StrongGuildInit( Msg_StrongHoldInit* info )
{
	// ����� ��� ��ũ �־���.
	g_pEngineHandler->HT_hrSetGuildCastleMark( info->dwMark[eStronghold_Northwest], info->dwMark[eStronghold_Northeast], info->dwMark[eStronghold_Southwest], info->dwMark[eStronghold_Southeast] );

	//	������ ���
	m_iMyStrongGuildIndex = -1;
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, _T("") );

	for( int i=0 ; i<eStronghold_MaxCount  ; i++ )
	{
		//	����� ������ ��� �̸�
		m_strStrongGuildName[i] = info->szGuildName[i];

		if( !m_strGuild_GuildName.HT_bIsEmpty() )
		{
			if( m_strGuild_GuildName.HT_iStringCompare( info->szGuildName[i] ) == 0 ||
				m_strAlliedGuildName[0].HT_iStringCompare( info->szGuildName[i] ) == 0 ||
				m_strAlliedGuildName[1].HT_iStringCompare( info->szGuildName[i] ) == 0 )
			{
				m_iMyStrongGuildIndex = i;
				m_bMyStrongGuild = TRUE;

				//	���� ������ ���
				if( m_strGuild_GuildName.HT_iStringCompare( info->szGuildName[i] ) == 0 )
				{
					CHTString strTemp;
					HT_vGuild_SetMessage( eMsgCommonDurga0 + m_iMyStrongGuildIndex, &strTemp ); // [�ƽ���]
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, strTemp.HT_szGetString() );
				}
				//	���� �ƽ����� ������ ���
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

//	��� ���� �ƽ��� ��Ŷ Udate
HTvoid HTGuild::HT_vGuildNet_SCP_StrongGuildUpdate( Msg_StrongHoldUpdate* info )
{
	// ����� ��� ��ũ �־���.
	g_pEngineHandler->HT_hrSetGuildCastleMark( info->dwMark[eStronghold_Northwest], info->dwMark[eStronghold_Northeast], info->dwMark[eStronghold_Southwest], info->dwMark[eStronghold_Southeast] );

	//	������ ���
	m_iMyStrongGuildIndex = -1;
	g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, _T("") );

	for( int i=0 ; i<eStronghold_MaxCount  ; i++ )
	{
		//	����� ������ ��� �̸�
		m_strStrongGuildName[i] = info->szGuildName[i];

		if( !m_strGuild_GuildName.HT_bIsEmpty() )
		{
			if( m_strGuild_GuildName.HT_iStringCompare( info->szGuildName[i] ) == 0 ||
				m_strAlliedGuildName[0].HT_iStringCompare( info->szGuildName[i] ) == 0 ||
				m_strAlliedGuildName[1].HT_iStringCompare( info->szGuildName[i] ) == 0 )
			{
				m_iMyStrongGuildIndex = i;
				m_bMyStrongGuild = TRUE;
				//	���� ������ ���
				if( m_strGuild_GuildName.HT_iStringCompare( info->szGuildName[i] ) == 0 )
				{
					CHTString strTemp;
					HT_vGuild_SetMessage( eMsgCommonDurga0 + m_iMyStrongGuildIndex, &strTemp ); // [�ƽ���]
					g_cUIManager->HT_SetTextLabelControl( _DIALOG_ASHRAMINFO, 19, strTemp.HT_szGetString() );
				}
				//	���� �ƽ����� ������ ���
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

//	���ձ�� 
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

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
	g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Request_AshramItem" );
	if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}
//	Recive Ashram Item
HTvoid HTGuild::HT_vAshram_SCPAshramItem( Msg_GuildItem* info )
{
	g_cUIManager->HT_ShowWindow(_DIALOG_ASHRAMCAGO);
	//	�κ��丮�� Open
	if( !g_cUIManager->HT_isShowWindow( _DIALOG_EQUPINVENTORY ) )
        g_cEquipInventory->HT_hrEquipPcInventoryActiveSw();

	//	�׸��� ���Ӱ� �����Ͽ� �־��ش�.
	memcpy( m_arrItemOfAshramCargo[0], info->arrItem, sizeof(STRUCT_ITEM)*120 );
	memcpy( m_arrItemOfAshramCargo[1], info->arrItem+120, sizeof(STRUCT_ITEM)*120 );
	memcpy( m_arrItemOfAshramCargo[2], info->arrItem+240, sizeof(STRUCT_ITEM)*120 );
	//	���� ������ â�� �������� �����.
	g_cItemSystem->HT_LL_vInsertAfter_ItemDeleteAshramCargo( m_arrItemOfAshramCargo[m_iPrevPageOfAshramCargo], m_iPrevPageOfAshramCargo );
	g_cItemSystem->HT_LL_vInsertAfter_ItemCreateAshramCargo( m_arrItemOfAshramCargo[m_iPageOfAshramCargo], m_iPageOfAshramCargo );
	//	�ƽ��� â�� �̸� ����
	CHTString strTemp;
	CHTString strMessage;
	strTemp.HT_hrCleanUp();
	g_cUIManager->HT_SetScriptMessage( eMsgAshramAshramCargo, &strMessage, _T(""), _T("") );	//	�ƽ���â��
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

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
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

	//-----����� �׽�Ʈ�� ���Ͽ�-----//
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
		g_cUIManager->HT_SetScriptMessage( eMsgAshramInfo, &strMessage, _T(""), _T("") );	//	�ƽ��� â��%d Ȯ�忡 �����Ͽ����ϴ�.
		strTemp.HT_szFormat( strMessage, (HTint)info->byType );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strTemp.HT_szGetString() );
	}
	else if( info->byResult == 1 )
	{
		CHTString strMessage;
		g_cUIManager->HT_SetScriptMessage( eMsgAshramFaildCargoExpance, &strMessage, _T(""), _T("") );	//	�ƽ��� â�� Ȯ�忡 �����Ͽ����ϴ�.
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_CHAKRA, strMessage );
	}
}
//	Recive GuildItemUpdate
HTvoid HTGuild::HT_vAshram_SCPGuildItemUpdate( Msg_GuildItemUpdate* info )
{
    //	���� ������ ����
	if( info->nFromIndex != -1 )
	{
		HTint iKeyID = 0;
		BASE_GetKey( g_cMainCharacter->HT_iMainChar_GetKeyID(), ITEM_PLACE_GUILDCARGO, info->nFromIndex, iKeyID );
		g_cItemSystem->HT_LL_vInsertAfter_ItemDelete( (HTdword)iKeyID );
	}

	//	������ ����
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
				g_cUIManager->HT_SetScriptMessage( eMsgWordInUseing, &strMessage, _T(""), _T("") );	//	�����
				g_cUIManager->HT_SetTextLabelControl( _DIALOG_SANCTIONASHCAGO, 10+i, strMessage );

				tm* psTmTime = localtime( &svTime );

				g_cUIManager->HT_SetScriptMessage( eMsgCommonUntilAshramCargo, &strMessage, _T(""), _T("") );	//	�����
				//szDay.HT_szFormat("%d.%d.%d����", psTmTime->tm_year+1900, psTmTime->tm_mon+1, psTmTime->tm_mday );
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
			g_cUIManager->HT_SetScriptMessage( eMsgAshramNotUse, &strMessage, _T(""), _T("") );	//	����߾ƴ�
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SANCTIONASHCAGO, 10+i, strMessage );
			g_cUIManager->HT_SetScriptMessage( eMsgAshramEnd, &strMessage, _T(""), _T("") );	//	����
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SANCTIONASHCAGO, 13+i, strMessage );
			g_cUIManager->HT_SetTextLabelControl( _DIALOG_SANCTIONASHCAGO, 16+i, _T("0") );
		}
	}
}

