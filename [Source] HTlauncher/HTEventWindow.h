#ifndef _HTEventWindow_H
#define _HTEventWindow_H

#pragma once

class CHTEventWindow
{
public:
	CHTEventWindow(void);
	~CHTEventWindow(void);

	//	Create Window
	HTvoid		HT_vEventWnd_CreateWindow();
	//	입력 메세지 처리
	//	Event Window
	static void		HT_vEventWnd_InputCheckForAttendanceCheck(int iAction, int iTarget, int iTargetID);
	//	Win Event
	static void		HT_vEventWnd_InputCheckForWinEvent(int iAction, int iTarget, int iTargetID);
	//	Win2 Event
	static void		HT_vEventWnd_InputCheckForWin2Event(int iAction, int iTarget, int iTargetID);

	//	Network Message
	//	Request Attendance
	HTvoid		HT_vEventWindow_ReqAttendance();
	//	Check Game Event
	HTvoid		HT_vEventWnd_ReqCheckGameEvent( HTdword dwEvent );
	//	Check Game Event
	HTvoid		HT_vEventWnd_ReqChangeTribe( HTbyte byTribe );
	//	Request Msg Game Event
	HTvoid		HT_vEventWnd_ReqMsgGameEvent( HTshort snAction, HTint iID, HTint iData0 );
	HTvoid		HT_vEventWnd_ReqMsgGameEvent( HTshort snAction, HTint iID, HTchar pData[16] );
	//	Recive	Msg Game Event
	HTvoid		HT_vEventWnd_ReciveMsgGameEvent( Msg_GameEvent* info );

private:
	HTbool		m_bEventWin_DlgSw;
	//	Today Dete
	HTint		m_iTodayDete;
};

#endif // #ifndef _HTEventWindow_H