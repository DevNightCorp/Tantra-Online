
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
	//-----GM ����Ÿ Ŭ���� �ϱ�-----//
	HTvoid				HT_vGMDataCleanUp();
	HTvoid				HT_vCleanUpGameDataForPortal();
	HTvoid				HT_vCleanUpGameDataForReStart();

	//	���� �����͸� �ʱ�ȭ
	HTvoid				HT_hrMainLoopBeforeInit();			//	���ΰ��� �������� 
	//---------���ӽ��� ����----------//
	HTvoid				HT_vSetStartMainGamePlay();

protected:

	//-----�ʱ� ����Ÿ �ε� / �ΰ��� / ���弱�� / ĳ���� ���� / ���� ����Ÿ �ε�-----//
	HTRESULT			HT_hrGMInit();
	HTRESULT			HT_hrReadyGameControl();
	HTRESULT			HT_hrRender_Ready();
	HTvoid				HT_vIntro_End();
	
	//-----Ŭ���� ����-----//
	HTvoid				HT_hrMainGameDestory();

	HTRESULT			HT_hrMainInit();
	HTRESULT			HT_hrMainDataLoad();

	//-----���� ���ӿ��� - ������Ʈ-----//
	HTvoid				HT_vMainGame_OneTimetUpdate();	//	���ΰ��� ���� �ѹ��� ������Ʈ
	HTvoid				HT_hrMainGameSetCamera();
	HTRESULT			HT_hrMainGameControl();
	HTvoid				HT_hrMainGamefreInit();			//	���ΰ��� �������� �ܱ� �ʱ�ȭ
	HTvoid				HT_hrMainGameEndClean();		//	���ΰ��� �������� �ܱ� ����

	HTvoid				HT_vMainGame_RequestCharPing();	//	ĳ���Ͱ� ��� ������ ������ ��� �˸�
        
	//-----Render-----//
	HTRESULT			HT_hrMainGameRender();
	//-----Render_�������� �ʱ�ȭ�� �޾Ҵ��� üũ-----//
	HTvoid				HT_vMainGameServerConntionRender();
	//	ReStart or GameEnd Check
	HTvoid				HT_vMainGamReStartOrGameendRender( DWORD dwRemainTime );

	// �� ���� ��ȯ�� üũ�Ѵ�.
	HTvoid				HT_vCheckZoneServerSwitching();
	//	���� ���� ���������� üũ�Ѵ�.
	HTvoid				HT_vCheckZoneServerDisConnect();

protected:
	
private:
	DWORD				m_bCharInitDelay;
	DWORD				m_dPassTime;
	//	ĳ���Ͱ� ��� ������ ������ ��� �˸�
	DWORD				m_bRequestCharPingDelay;
	//	Bot Check
	DWORD				m_bBotCheckDelay;
	//	ĳ���� restart �ÿ� ������
	DWORD				m_dwReStartStartTime;
	//	ĳ���� restart �ÿ� ������
	DWORD				m_dwReStartRemainTime;

	CHTTimer*			m_cGMTimer;
	HTfloat				m_fElapsedTime;

	//	���� ���� ���������� üũ�Ѵ�.
	HTbool				m_bZoneServerDisConnectCheck;

public:
	
};


#endif


