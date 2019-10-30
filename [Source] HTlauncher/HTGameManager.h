
#ifndef __HTGAMEMANAGER_H__
#define __HTGAMEMANAGER_H__

#include "HTApplication.h"
#include "HTIntroManager.h"
#include "HTMonsterSystem.h"
#include "HTNPCSystem.h"
#include "HTCamera.h"
#include "HTChatting.h"

#define PMSTRUCT_UNITYVER

class CHTGameManager : public CHTApplication
{
public:
	CHTGameManager();
	~CHTGameManager();
	//-----GM 데이타 클린업 하기-----//
	HTvoid				HT_vGMDataCleanUp();
	HTvoid				HT_vCleanUpGameDataForPortal();
	HTvoid				HT_vCleanUpGameDataForReStart();

	//	게임 데이터를 초기화
	HTvoid				HT_hrMainLoopBeforeInit();			//	메인게임 루프에서 
	//---------게임시작 셋팅----------//
	HTvoid				HT_vSetStartMainGamePlay();

protected:

	//-----초기 데이타 로드 / 로고인 / 월드선택 / 캐릭터 선택 / 메인 데이타 로딩-----//
	HTRESULT			HT_hrGMInit();
	HTRESULT			HT_hrReadyGameControl();
	HTRESULT			HT_hrRender_Ready();
	HTvoid				HT_vIntro_End();
	
	//-----클래스 비우기-----//
	HTvoid				HT_hrMainGameDestory();

	HTRESULT			HT_hrMainInit();
	HTRESULT			HT_hrMainDataLoad();

	//-----메인 게임에서 - 업데이트-----//
	HTvoid				HT_vMainGame_OneTimetUpdate();	//	메인게임 루프 한번만 업데이트
	HTvoid				HT_hrMainGameSetCamera();
	HTRESULT			HT_hrMainGameControl();
	HTvoid				HT_hrMainGamefreInit();			//	메인게임 루프최초 단기 초기화
	HTvoid				HT_hrMainGameEndClean();		//	메인게임 루프최후 단기 삭제

	HTvoid				HT_vMainGame_RequestCharPing();	//	캐릭터가 살아 있음을 서버에 계속 알림
        
	//-----Render-----//
	HTRESULT			HT_hrMainGameRender();
	//-----Render_서버에서 초기화를 받았는지 체크-----//
	HTvoid				HT_vMainGameServerConntionRender();
	//	ReStart or GameEnd Check
	HTvoid				HT_vMainGamReStartOrGameendRender( DWORD dwRemainTime );

	// 존 서버 전환을 체크한다.
	HTvoid				HT_vCheckZoneServerSwitching();
	//	서버 연결 끊어졌는지 체크한다.
	HTvoid				HT_vCheckZoneServerDisConnect();

protected:
	
private:
	DWORD				m_bCharInitDelay;
	DWORD				m_dPassTime;
	//	캐릭터가 살아 있음을 서버에 계속 알림
	DWORD				m_bRequestCharPingDelay;
	//	Bot Check
	DWORD				m_bBotCheckDelay;
	//	캐릭터 restart 시에 딜레이
	DWORD				m_dwReStartStartTime;
	//	캐릭터 restart 시에 딜레이
	DWORD				m_dwReStartRemainTime;

	CHTTimer*			m_cGMTimer;
	HTfloat				m_fElapsedTime;

	//	서버 연결 끊어졌는지 체크한다.
	HTbool				m_bZoneServerDisConnectCheck;

public:
	
};


#endif


