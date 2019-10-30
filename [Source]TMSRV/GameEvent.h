#ifndef __GAMEEVENT_H__
#define __GAMEEVENT_H__

#include <set>
#include "IWantIt.h"
#include "Gamers.h"
#include "MicroSound.h"

#define __IWANTIT__

class CGameEvent
{
private:
	std::set<char*, HTStr>	m_setUser[MAX_EVENT];
	std::set<char*, HTStr>	m_setUserDone[MAX_EVENT];

public:
	CGameEvent();
	~CGameEvent();

	void Initialize(int iZone, STGAMEEVENT* pEventList);
	void CloseEvent();
	bool ReadEvent(DWORD dwEvent, int iTarget);
	DWORD GetEventID(DWORD dwWebEvent, char* pAccount, char* pChar, char* pGuild);
	void RemoveEvent(DWORD dwIndex, char* pUser);
	bool ReadEventDone(DWORD dwEvent, int iTarget);
	bool CheckDate(char* pData, bool bIsAccount = true);

	CIWantIt		m_IWantIt;
	CGamers			m_Coupon;
	CMicroSound		m_MicroSound;
	DWORD			m_dwEvent;
	bool			m_bIsFromWeb[MAX_EVENT];
	STGAMEEVENT		m_kEvent[MAX_EVENT];
	BOOL			IsServerEventMember(char* pTarger, DWORD dwEvent);

};

#endif	//	__GAMEEVENT_H__