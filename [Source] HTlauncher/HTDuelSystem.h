#pragma once

class HTDuelSystem
{
public:
	HTDuelSystem(void);
	~HTDuelSystem(void);

	//	Update
	HTvoid		HT_vDuel_Update();
	//	Update Wait Mode Check
	HTvoid		HT_vDuel_Update_WaitModeCheck();
	//	Update Remain Time Check
	HTvoid		HT_vDuel_Update_RemainTimeCheck();

	//	Dlg Check For ReConfirm
	HTvoid		HT_vDuel_LButtonCheckForReConfirm( HTint iProp, HTint iButtonNo );

	//	Pick Check From OtherObject
	HTRESULT	HT_hrDuel_PickCheckFromOtherObject( HTint iObjectID );

	//	Get
	//	Get Duel_Mode
	HTbyte		HT_byDuel_GetDuelMode()		{	return	m_byDuel_Mode;	};
	//	Get Duel_Other Name
	CHTString	HT_strDuel_GetOtherName()	{	return	m_strDuel_SendCharName.HT_szGetString();	};
	//	Get Duel Character KeyID
	HTint		HT_iDuel_GetDuelCharKeyID()	{	return	m_iDuel_DuelCharKeyID;	};
	//	Get Wait Mode
	HTbool		HT_bDuel_GetWaitMode()		{	return	m_bDuel_WaitMode;	};

	// Set Empty Place Mode
	HTvoid		HT_vSet_EmptyPlace();

	//	Set
	//	Set Init
	HTvoid		HT_vDuel_SetInit();
	//	Set Duel Mode
	HTvoid		HT_vDuel_SetDuelMode();
	//	Set Wait Mode Cancel From KeyInput
	HTvoid		HT_vDuel_SetWaitModeCancelFromKeyInput();

	//	Net
	//	Request Challenger
	HTvoid		HT_vDuelNet_CSP_Challenger();
	//	Recive Challenger
	HTvoid		HT_vDuelNet_SCP_Challenger( Msg_Challenger* info );

private:
	HTbyte		m_byDuel_Mode;
	HTbyte		m_byDuel_ResponseReason;
	CHTString	m_strDuel_SendCharName;
	HTint		m_iDuel_SendCharKeyID;

	HTbool		m_bDuel_WaitMode;
	HTdword		m_dwDuel_WaitTime;

	HTbool		m_bDuel_AutoOK;
	HTdword		m_dwDuel_AutoWaitTime;

	HTint		m_iDuel_DuelCharKeyID;
	CHTString	m_strDuel_DuelCharName;
	DWORD		m_dwDuel_RequestTime;
};
