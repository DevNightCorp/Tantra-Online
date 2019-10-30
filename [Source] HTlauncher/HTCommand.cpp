#include "stdafx.h"
#include "HTextern.h"
#include "HTControlDef.h"
#include "HTEngineHandler.h"
#include "htcommand.h"


//#define COMMAND_QUICKSLOT_EXCHANGE			5
//#define COMMAND_QUICKSLOT_SHOP				9
//#define COMMAND_QUICKSLOT_BLOG				14


//#define		SIEGEBUTTON_FORJAPAN


HTCommand::HTCommand(void)
{
}

HTCommand::~HTCommand(void)
{
	g_cUIManager->HT_DeleteWindow( _DIALOG_COMMANDWND );
}

//	명령_초기화
HTvoid HTCommand::HT_vCommand_Init()
{
	//	명령_Create Window
	this->HT_vCommand_CreateWnd();

	m_bCommand_WndSw = HT_FALSE;
	m_iCommand_BeforeTargetID = 0;
	m_iCommand_CmdIconStatus = ICON_STATUS_NONE;
	m_bCommand_Assist = HT_FALSE;
	m_iCommand_AssistTargetID = 0;
}
//	명령_Create Window
HTvoid HTCommand::HT_vCommand_CreateWnd()
{
	CHTString strMessage;
	//	[Command]
	//	Window
	g_cUIManager->HT_SetScriptMessage( eMsgCommandTitle, &strMessage, _T(""), _T("") );	//	Command
	g_cUIManager->HT_CreateWindow( _DIALOG_COMMANDWND, strMessage, 330, 466, g_cCommand->HT_hrCommand_InputCheckCommand, 2 );
	g_cUIManager->HT_WindowArrangement( _DIALOG_COMMANDWND, 5 );
	//	줄	제목 표시줄
	g_cUIManager->HT_AddTextureControl( _DIALOG_COMMANDWND, 0, 8, 3, 36, 1400, 323, 6 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_COMMANDWND, 0, 8, 3, 66, 1400, 323, 5 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_COMMANDWND, 0, 1, 110, 71, 1400, 3, 396 );
	g_cUIManager->HT_AddTextureControl( _DIALOG_COMMANDWND, 0, 1, 219, 71, 1400, 3, 396 );
	//	Texture 명령
	g_cUIManager->HT_AddTextureControl( _DIALOG_COMMANDWND, 0, 9, 39, 30, 1400, 90, 17 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommadnSubTitle, &strMessage, _T(""), _T("") );	//	명령
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 39, 30, 90, 17 );
	//	Texture 행동관련
	g_cUIManager->HT_AddTextureControl( _DIALOG_COMMANDWND, 0, 9, 12, 60, 1400, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommadnAboutAction, &strMessage, _T(""), _T("") );	//	행동관련
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 12, 60, 90, 19 );
	//	Texture 그룹관련
	g_cUIManager->HT_AddTextureControl( _DIALOG_COMMANDWND, 0, 9, 121, 60, 1400, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommadnAboutGroup, &strMessage, _T(""), _T("") );	//	그룹관련
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 121, 60, 90, 19 );
	//	Texture 모션관련
	g_cUIManager->HT_AddTextureControl( _DIALOG_COMMANDWND, 0, 9, 230, 60, 1400, 90, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommadnAboutMotion, &strMessage, _T(""), _T("") );	//	모션관련
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, 0, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 230, 60, 90, 19 );
	//	행동관련
	//	Button 앉기
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIT, 9, 44, 85, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandSitDown, &strMessage, _T(""), _T("") );	//	앉기
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIT, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 44, 85, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIT );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIT, 66, 6, 85 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIT, 23811 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIT, 2,2 );
	//	Button 걷기
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_WLK, 9, 44, 128, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandWalk, &strMessage, _T(""), _T("") );	//	걷기
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_WLK, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 44, 128, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_WLK );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_WLK, 66, 6, 128 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_WLK, 23812 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_WLK, 2,2 );
	//	Button 줍기
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PICKUP, 9, 44, 171, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandPickUp, &strMessage, _T(""), _T("") );	//	줍기
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PICKUP, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 44, 171, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PICKUP );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PICKUP, 66, 6, 171 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PICKUP, 23819 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PICKUP, 2,2 );
	//	Button 타겥
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_TARGET, 9, 44, 214, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandTarget, &strMessage, _T(""), _T("") );	//	타겟
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_TARGET, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 44, 214, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_TARGET );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_TARGET, 66, 6, 214 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_TARGET, 23818 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_TARGET, 2,2 );
	//	Button 공격
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ATK, 9, 44, 256, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandAttack, &strMessage, _T(""), _T("") );	//	공격
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ATK, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 44, 256, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ATK );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ATK, 66, 6, 256 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ATK, 23813 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ATK, 2,2 );
	//	Button 결투
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DUEL, 9, 44, 299, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandDuel, &strMessage, _T(""), _T("") );	//	결투
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DUEL, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 44, 299, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DUEL );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DUEL, 66, 6, 299 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DUEL, 23021 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DUEL, 2,2 );
	//	Button 지시
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DIRECTIONS, 9, 44, 341, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommadDirections, &strMessage, _T(""), _T("") );	//	지시
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DIRECTIONS, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 44, 341, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DIRECTIONS );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DIRECTIONS, 66, 6, 341 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DIRECTIONS, 22697 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_DIRECTIONS, 2,2 );
	//	Button 멈춤
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_STOP, 9, 44, 383, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommadStop, &strMessage, _T(""), _T("") );	//	멈춤
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_STOP, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 44, 383, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_STOP );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_STOP, 66, 6, 383 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_STOP, 22223 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_STOP, 2,2 );

	//	그룹관련
	//	Button 파티
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTY, 9, 153, 85, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandParty, &strMessage, _T(""), _T("") );	//	파티
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTY, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 153, 85, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTY );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTY, 66, 115, 85 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTY, 23295 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTY, 2,2 );
	//	Button 파티탈퇴
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTYWITHDRAW, 9, 153, 128, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandPartyDrop, &strMessage, _T(""), _T("") );	//	파티탈퇴
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTYWITHDRAW, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 153, 128, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTYWITHDRAW );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTYWITHDRAW, 66, 115, 128 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTYWITHDRAW, 23300 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PARTYWITHDRAW, 2,2 );
	//	Button 도움
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ASSIST, 9, 153, 171, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandSupport, &strMessage, _T(""), _T("") );	//	도움
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ASSIST, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 153, 171, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ASSIST );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ASSIST, 66, 115, 171 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ASSIST, 22928 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_ASSIST, 2,2 );
	//	Button 개인상점
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SHOP, 9, 153, 214, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandShop, &strMessage, _T(""), _T("") );	//	개인상점
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SHOP, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 153, 214, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SHOP );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SHOP, 66, 115, 214 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SHOP, 23189 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SHOP, 2,2 );
	//	Button 교환
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_EXCHANGE, 9, 153, 257, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandTrade, &strMessage, _T(""), _T("") );	//	교환
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_EXCHANGE, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 153, 257, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_EXCHANGE );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_EXCHANGE, 66, 115, 257 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_EXCHANGE, 23816 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_EXCHANGE, 2,2 );
#ifndef SIEGEBUTTON_FORJAPAN
	//	Button 공성전
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIEGE, 9, 153, 299, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommadSiege, &strMessage, _T(""), _T("") );	//	공성전
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIEGE, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 153, 299, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIEGE );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIEGE, 66, 115, 299 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIEGE, 23101 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_SIEGE, 2,2 );
#endif

	//	모션관련
	//	Button 도발
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PROVOKE, 9, 262, 85, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandProvocation, &strMessage, _T(""), _T("") );	//	도발
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PROVOKE, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 262, 85, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PROVOKE );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PROVOKE, 66, 224, 85 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PROVOKE, 23328 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_PROVOKE, 2,2 );
	//	Button 인사
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_GREET, 9, 262, 128, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandGreeting, &strMessage, _T(""), _T("") );	//	인사
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_GREET, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 262, 128, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_GREET );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_GREET, 66, 224, 128 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_GREET, 23329 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_GREET, 2,2 );
	//	Button 돌격
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_RUSH, 9, 262, 171, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandRush, &strMessage, _T(""), _T("") );	//	돌격
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_RUSH, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 262, 171, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_RUSH );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_RUSH, 66, 224, 171 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_RUSH, 23327 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_RUSH, 2,2 );
	//	Button 외출
	g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_AWAY, 9, 262, 214, 0, 0, 1500, 64, 19 );
	g_cUIManager->HT_SetScriptMessage( eMsgCommandWait, &strMessage, _T(""), _T("") );	//	외출
	g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_AWAY, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 262, 214, 64, 19 );
	g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_AWAY );
	g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_AWAY, 66, 224, 214 );
	g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_AWAY, 23036 );
	g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_AWAY, 2,2 );
	
	if( g_iInationalType == INATIONALTYPE_KOREA )
	{
		//	Button 블로그
		g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG, 9, 262, 257, 0, 0, 1500, 64, 19 );
		g_cUIManager->HT_SetScriptMessage( eMsgCommandBlog, &strMessage, _T(""), _T("") );	//	블로그
		g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 262, 257, 64, 19 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG );
		g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG, 66, 224, 257 );
		g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG, 22929 );
		g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG, 2,2 );
	}
/*
	if( g_iInationalType == INATIONALTYPE_KOREA )
	{
		//	Button 블로그
		g_cUIManager->HT_AddButtonControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG, 9, 262, 257, 0, 0, 1500, 64, 19 );
		g_cUIManager->HT_SetScriptMessage( eMsgCommandBlog, &strMessage, _T(""), _T("") );	//	블로그
		g_cUIManager->HT_AddLabelControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG, strMessage, 0, HT_COLOR(1.0f,1.0f,1.0f,1.0f), HT_COLOR(1.0f,1.0f,1.0f,1.0f), 262, 257, 64, 19 );
		g_cUIManager->HT_SetButtonToolTipOff( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG );
		g_cUIManager->HT_AddSlotBoxControl( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG, 66, 224, 257 );
		g_cUIManager->HT_SetSlotImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG, 22929 );
		g_cUIManager->HT_SetSlotBoxControlPosImage( _DIALOG_COMMANDWND, COMMAND_QUICKSLOT_BLOG, 2,2 );
	}
	*/
}

//	명령_입력함수 처리
void HTCommand::HT_hrCommand_InputCheckCommand(int iAction, int iTarget, int iTargetID)
{
	if( iTarget == UI_TARGET_BUTTON )
	{
		if( iTargetID == -1 )
		{
			g_cCommand->HT_vCommand_WndActiveSw();
		}
		else if( iTargetID == COMMAND_QUICKSLOT_SIT )
			g_cCommand->HT_vCommand_Sit();
		else if( iTargetID == COMMAND_QUICKSLOT_WLK )
			g_cCommand->HT_vCommand_Walk();
		else if( iTargetID == COMMAND_QUICKSLOT_ATK )
			g_cCommand->HT_vCommand_Attack();
		else if( iTargetID == COMMAND_QUICKSLOT_TARGET )
			g_cCommand->HT_vCommand_Target();
		else if( iTargetID == COMMAND_QUICKSLOT_EXCHANGE )
			g_cCommand->HT_vCommand_Exchange();
		else if( iTargetID == COMMAND_QUICKSLOT_PICKUP )
			g_cCommand->HT_vCommand_PickUp();
		else if( iTargetID == COMMAND_QUICKSLOT_PARTY )
			g_cCommand->HT_vCommand_Party();
		else if( iTargetID == COMMAND_QUICKSLOT_PARTYWITHDRAW )
			g_cCommand->HT_vCommand_PartyWithDraw();
		else if( iTargetID == COMMAND_QUICKSLOT_SHOP )
			g_cCommand->HT_vCommand_Shop();
		else if( iTargetID == COMMAND_QUICKSLOT_PROVOKE )
			g_cCommand->HT_vCommand_Provoke();
		else if( iTargetID == COMMAND_QUICKSLOT_GREET )
			g_cCommand->HT_vCommand_Greet();
		else if( iTargetID == COMMAND_QUICKSLOT_RUSH )
			g_cCommand->HT_vCommand_Rush();
		else if( iTargetID == COMMAND_QUICKSLOT_DIRECTIONS )
			g_cCommand->HT_vCommand_Directions(1);
		else if( iTargetID == COMMAND_QUICKSLOT_STOP )
			g_cCommand->HT_vCommand_Directions(2);
		else if( iTargetID == COMMAND_QUICKSLOT_AWAY )
			g_cCommand->HT_vCommand_EmptyPlace();
		else if( iTargetID == COMMAND_QUICKSLOT_DUEL )
			g_cCommand->HT_vCommand_Duel();
		else if( iTargetID == COMMAND_QUICKSLOT_SHOP )		
			g_cCommand->HT_vCommand_Shop();
		else if( iTargetID == COMMAND_QUICKSLOT_EXCHANGE )		
			g_cCommand->HT_vCommand_Exchange();
		else if( iTargetID == COMMAND_QUICKSLOT_BLOG )
			g_cCommand->HT_vCommand_Blog();
		else if( iTargetID == COMMAND_QUICKSLOT_SIEGE )
			g_cCommand->HT_vCommand_Siege();
	}
	else if( iTarget == UI_TARGET_SLOTBOX )
	{
		//	아이콘을 들고 엉뚱한 곳에 클릭했을때
		if( iTargetID == -1 || iTargetID == -2)
		{
			g_cUIManager->HT_RefuseSlotImageMoving();
			return;
		}
	}
}
//	명령_명령창 활성화/비활성화
HTvoid HTCommand::HT_vCommand_WndActiveSw()
{
	if( m_bCommand_WndSw )
	{
		m_bCommand_WndSw = HT_FALSE;
		g_cUIManager->HT_HideWindow(_DIALOG_COMMANDWND);
	}
	else
	{
		m_bCommand_WndSw = HT_TRUE;
		g_cUIManager->HT_ShowWindow(_DIALOG_COMMANDWND);
	}
}
//	명령_앉기
HTvoid HTCommand::HT_vCommand_Sit()
{
	g_cMainCharacter->HT_vMainChar_SetSit();
}
//	명령_걷기
HTvoid HTCommand::HT_vCommand_Walk()
{
	g_cMainCharacter->HT_vMainChar_SetMoveType();
}
//	명령_공격
HTvoid HTCommand::HT_vCommand_Attack()
{
	HTint iAttackTargetID = g_cMainCharacter->HT_iMainChar_GetAttackTargetKeyID();
	if( g_cOtherObjectSystem->HT_bOtherObjectSystem_GetLiveFromKeyID( iAttackTargetID ) )
	{
		g_cMainCharacter->HT_vMainChar_SetAttackStatus( -1, -1, HT_TRUE );
		g_cOtherObjectSystem->HT_vOtherObjectSystem_SetAttackTargetting( iAttackTargetID );
	}
}
//	명령_타겥
HTvoid HTCommand::HT_vCommand_Target()
{
	HTbool bTrue = HT_TRUE;
	if( g_cMainCharacter->HT_bMainChar_GetAttackSw() )
	{
		if( g_cMainCharacter->HT_iMainChar_GetAnimationStatus() != CHARACTER_ANISTATE_WLK &&
			g_cMainCharacter->HT_iMainChar_GetAnimationStatus() != CHARACTER_ANISTATE_RUN )
		{
			bTrue = HT_FALSE;
		}
	}

	if( g_cMainCharacter->HT_iMAinChar_GetAffections() & eTNVSAfn_Blind )
		bTrue = HT_FALSE;

	if( bTrue )
	{
		HTint iTargetKeyID = 0;
		HTint iObjectID;
		iTargetKeyID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetObjectKeyIDMostNearMainChar( m_iCommand_BeforeTargetID );
		if( iTargetKeyID )
		{
			iObjectID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( iTargetKeyID );
			g_cMainCharacter->HT_vMainChar_SetAttackStatus( iTargetKeyID, iObjectID, HT_FALSE );
		}
	}
}
//	명령_추적
HTvoid HTCommand::HT_vCommand_Pursuit()
{
}
//	명령_지원
HTvoid HTCommand::HT_vCommand_Support()
{
}
//	명령_교환
HTvoid HTCommand::HT_vCommand_Exchange()
{
	g_cExchangeSystem->HT_vExchange_SetClickTradeButton( HT_TRUE );
}
//	명령_줍기
HTvoid HTCommand::HT_vCommand_PickUp()
{
	if( g_cMainCharacter->HT_bMainChar_GetAttackSw() )			return;
	//	가장 근접한 아이템 KeyID 얻기
	HTint iItemKeyID = g_cItemSystem->HT_iItemSystem_GetItemKeyIDMostNearMainChar();
	if( iItemKeyID )
	{
		HT_CELL_COORD cellPos = g_cItemSystem->HT_cellItemSystem_GetMapCellPosForKeyID( iItemKeyID );
		g_cItemControl->HT_vItemControl_SetTargetItem( (HTdword)iItemKeyID );
		g_cMainCharacter->HT_vMainChar_MouseLButtonUpCheck( cellPos, HT_FALSE );
		g_cItemSystem->HT_vItemSystem_SetItemTargettingEffect( iItemKeyID );
	}
}
//	명령_파티
HTvoid HTCommand::HT_vCommand_Party()
{
	g_cParty->HT_bParty_Command_Party();
}
//	명령_탈퇴
HTvoid HTCommand::HT_vCommand_PartyWithDraw()
{
	g_cParty->HT_bParty_Command_PartyWithDraw();
}
//	명령_개인상점
HTvoid HTCommand::HT_vCommand_Shop()
{
	g_cIndividualStore->HT_vIndividualStore_Active( g_cMainCharacter->HT_iMainChar_GetKeyID() );
}
//	명령_도발
HTvoid HTCommand::HT_vCommand_Provoke()
{
	HTint iMainCharAni = g_cMainCharacter->HT_iMainChar_GetAnimationStatus();
	if( iMainCharAni == CHARACTER_ANISTATE_STD ||
		iMainCharAni == CHARACTER_ANISTATE_IDL )
	{
		HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		g_cMainCharacter->HT_vNetWork_Send_MSGAction( 8, pPt.x, pPt.y );
	}
}
//	명령_인사
HTvoid HTCommand::HT_vCommand_Greet()
{
	HTint iMainCharAni = g_cMainCharacter->HT_iMainChar_GetAnimationStatus();
	if( iMainCharAni == CHARACTER_ANISTATE_STD ||
		iMainCharAni == CHARACTER_ANISTATE_IDL )
	{
		HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		g_cMainCharacter->HT_vNetWork_Send_MSGAction( 9, pPt.x, pPt.y );
	}
}
//	명령_돌격
HTvoid HTCommand::HT_vCommand_Rush()
{
	HTint iMainCharAni = g_cMainCharacter->HT_iMainChar_GetAnimationStatus();
	if( iMainCharAni == CHARACTER_ANISTATE_STD ||
		iMainCharAni == CHARACTER_ANISTATE_IDL )
	{
		HTPoint pPt = g_cMainCharacter->HT_ptMainChar_GetCellPosition();
		g_cMainCharacter->HT_vNetWork_Send_MSGAction( 10, pPt.x, pPt.y );
	}
}

//  명령_블로그
HTvoid HTCommand::HT_vCommand_Blog()
{
	g_eBlogAccessStatus = HT_BLOGACCESSSTATUS_READY;
	g_cInterfaceCheck->HT_vSetCursor( CURSOR_BLOG_ANI );
}

//  명령_공성전
HTvoid HTCommand::HT_vCommand_Siege()
{
	//	일본에 공성전 버틍이 빠져 있으면 이것을 실행한다.
#ifdef SIEGEBUTTON_FORJAPAN
	if( g_iInationalType == INATIONALTYPE_JAPEN )
	{
		// 1월에 적용 예정입니다.
		CHTString strMessage;
		g_cUIManager->HT_SetScriptMessage( eMsgCommonOurPlanJanuary, &strMessage, _T(""), _T("") );
		g_BasicLoadingInfo->HT_vNetWorkMessageSetHistory( HISTORY_MESSAGE_TYPE_NORMAL, strMessage );
		return;
	}
#endif

	if( HT_SUCCEED( HT_IS_BIRYUCASTLE( g_wResentZoneServerID ) ) )
	{
		g_cUIManager->HT_ShowWindow(_DIALOG_SIEGE1);
		//	참가 아쉬람 정보 신청
		g_pSiege->HT_vSiege_RequestJoinAshramInfo();
	}
}

//  명령_결투
HTvoid HTCommand::HT_vCommand_Duel()
{
	g_pDuelSystem->HT_vDuel_SetDuelMode();
}

//  명령_자리비움
HTvoid HTCommand::HT_vCommand_EmptyPlace()
{
	g_pDuelSystem->HT_vSet_EmptyPlace();
}

//  명령_도움
HTvoid HTCommand::HT_vCommand_Assist()
{
	//	내가 파티원이 아니면 스킵
	if( !(g_cParty->HT_iParty_GetPartyMemberCount() > 0) )
		return;

	//	내가 파티원이고 파티장이 아닐때만 파티장의 타겥으로 자동 선택된다.
	if( !g_cParty->HT_bParty_IsPartyJang( g_cMainCharacter->HT_iMainChar_GetKeyID() ) )
	{
		if( g_cOtherObjectSystem->HT_byOtherObjectSystem_GetLevel( m_iCommand_AssistTargetID ) > 0 )
		{
			//	Setting Init Targetting
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetInitTargetting();
			g_pEngineHandler->HT_hrPlaySound( 33524, 1 );	// Click Sound
			HTint iObjectID = g_cOtherObjectSystem->HT_iOtherObjectSystem_GetModelID( m_iCommand_AssistTargetID );
            g_cMainCharacter->HT_vMainChar_SetAttackStatus( m_iCommand_AssistTargetID, iObjectID, HT_TRUE );
			g_cOtherObjectSystem->HT_vOtherObjectSystem_SetAttackTargetting( m_iCommand_AssistTargetID );
		}
	}
}

//  명령_지시
HTvoid HTCommand::HT_vCommand_Directions( HTint iAction )
{
	MSG_PET_COMMAND* info = HT_NULL;
	info = new MSG_PET_COMMAND;

	info->iAction = iAction;
	info->iParam1 = g_cMainCharacter->HT_iMainChar_GetAttackTargetKeyID();
	g_pNetWorkMgr->RequestMsgPatCommand( info );

	//-----디버깅 테스트를 위하여-----//
	//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqPatCommand : Action:%d, Param:%d", info->iAction, info->iParam1 );
	//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

	HT_DELETE( info );
}

//	명령_Set 퀵슬롯에서 명령사용 요청
HTvoid HTCommand::HT_vCommand_SetQuickSlotCmdUse( HTint iQuickSlotNo )
{
	switch( iQuickSlotNo )
	{
		case COMMAND_QUICKSLOT_SIT:
			this->HT_vCommand_Sit();
			break;
		case COMMAND_QUICKSLOT_WLK:
			this->HT_vCommand_Walk();
			break;
		case COMMAND_QUICKSLOT_ATK:
			this->HT_vCommand_Attack();
			break;
		case COMMAND_QUICKSLOT_EXCHANGE:
			this->HT_vCommand_Exchange();
			break;
		case COMMAND_QUICKSLOT_TARGET:
			this->HT_vCommand_Target();
			break;
		case COMMAND_QUICKSLOT_PICKUP:
			this->HT_vCommand_PickUp();
			break;
		case COMMAND_QUICKSLOT_PARTY:
			this->HT_vCommand_Party();
			break;
		case COMMAND_QUICKSLOT_PARTYWITHDRAW:
			this->HT_vCommand_PartyWithDraw();
			break;
		case COMMAND_QUICKSLOT_SHOP:
			this->HT_vCommand_Shop();
			break;
		case COMMAND_QUICKSLOT_PROVOKE :
			this->HT_vCommand_Provoke();
			break;
		case COMMAND_QUICKSLOT_GREET :
			this->HT_vCommand_Greet();
			break;
		case COMMAND_QUICKSLOT_RUSH :
			this->HT_vCommand_Rush();
			break;
		case COMMAND_QUICKSLOT_BLOG :
			this->HT_vCommand_Blog();
			break;
		case COMMAND_QUICKSLOT_DUEL :
			this->HT_vCommand_Duel();
			break;
		case COMMAND_QUICKSLOT_AWAY :
			this->HT_vCommand_EmptyPlace();
			break;
		case COMMAND_QUICKSLOT_ASSIST :
			this->HT_vCommand_Assist();
			break;
		case COMMAND_QUICKSLOT_DIRECTIONS :
			this->HT_vCommand_Directions(1);
			break;
		case COMMAND_QUICKSLOT_STOP :
			this->HT_vCommand_Directions(2);
			break;
		case COMMAND_QUICKSLOT_SIEGE :
			g_cCommand->HT_vCommand_Siege();
			break;
	}
}

//	Net_Req Assist
HTvoid HTCommand::HT_vCommand_NetReqAssist( HTint iTargetKeyID )
{
	//	내가 파티장일때만 타겥키를 보낸다.
	if( g_cParty->HT_bParty_IsPartyJang( g_cMainCharacter->HT_iMainChar_GetKeyID() ) )
	{
		MSG_CHANGE_TARGET* info = HT_NULL;
		info = new MSG_CHANGE_TARGET;

		info->snTarget = iTargetKeyID;
		g_pNetWorkMgr->RequestMsgChangeTarget( info );

		//-----디버깅 테스트를 위하여-----//
		//g_DebugingFont[g_DebugingFont_Count++].HT_szFormat("Send_ReqChangeTarget : %d", info->snTarget );
		//if( g_DebugingFont_Count == 10 )	g_DebugingFont_Count = 0;

		HT_DELETE( info );
	}
}

//	Net_Set Assist
HTvoid HTCommand::HT_vCommand_NetReciveAssist( HTint iTargetKeyID )
{
    m_iCommand_AssistTargetID = iTargetKeyID;
}

//	Get	BeforeTargetID
HTint HTCommand::HT_iCommand_GetBeforeTargetID()
{
	int iSavedTargetID = m_iCommand_BeforeTargetID;
	m_iCommand_BeforeTargetID = 0;

	return iSavedTargetID;
}
