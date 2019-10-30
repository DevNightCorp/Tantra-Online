
#include "Basedef.h"
#include "Server.h"
#include "CPSock.h"
#include "Language.h"

#include "CUser.h"
#include "CMob.h"
#include "CItem.h"
#include "SendFunc.h"
#include "GetFunc.h"
#include "HTParamMgr.h"
#include "TNKalaSystem.h"
#include "TNSiege.h"







void HelpGameMaster( int a_iHandle, char* a_pCmd, bool a_bCheckGM )
{
	if( 0 >= a_iHandle || MAX_USER <= a_iHandle ) return;    
    if( NULL == a_pCmd ) return;
    if( '/' != a_pCmd[0] ) return;

	int iZoneID = ServerIndex + 1;

	#ifndef __TN_LOCAL_SERVER_SWITCH__
	if( a_bCheckGM && (eTNClan_GM != pMob[a_iHandle].m_byClan) && strncmp(pUser[a_iHandle].AccountName, Developer, ACCOUNTNAME_LENGTH)!=0 ) return;
	#endif

    // 모든 command를 log로 남긴다. 시간 + 누가 + 메시지
    int iLength = strlen( a_pCmd );
    if( g_iCmdMaxLength < iLength ) return;
    
    char szCmd[128] = { 0,0,0, };
    char szArgument1[256] = { 0,0,0, };
    char szArgument2[256] = { 0,0,0, };
	char szArgument3[256] = { 0,0,0, };
	char szArgument4[256] = { 0,0,0, };
	char szArgument5[256] = { 0,0,0, };
    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0;
    
	sscanf( a_pCmd, "%s %s %s %s %s %s", szCmd, szArgument1, szArgument2, szArgument3, szArgument4, szArgument5  );   
	iArgument1	=atoi(szArgument1);
	iArgument2	=atoi(szArgument2);
	iArgument3	=atoi(szArgument3);
	iArgument4	=atoi(szArgument4);
	iArgument5	=atoi(szArgument5);

    if( '/' != szCmd[0] ) return;

	S_SCP_RESP_WHISPER_CHAT kMsg; 
	kMsg.wType = SCP_RESP_WHISPER_CHAT;	
	kMsg.byResult = REPLY_ACK_OK;
	strncpy( kMsg.szName, "System", SZNAME_LENGTH );
	kMsg.byTextColor = 14; kMsg.byBgColor = 0; // 나중에 반전 색으로 바꾼다. 눈에 잘 띄게	
	    
    // g_iCmdMaxLength를 늘릴 수 있게 하는 command가 필요하다.
    // 몬스터 log 찍게하는 level도 조정할 수 있게 해야한다.
    // 중요한 monster는 누가 죽였고 어떤 reward를 줬는지 항상 log로 남겨야한다.(이런 형태에 맞게 log 출력부분 조정)
	//SYSTEMTIME st;
	//GetLocalTime( &st );
    
	#ifdef __TN_TOP_LOG__
	{
		if(strncmp(pUser[a_iHandle].AccountName, Developer, ACCOUNTNAME_LENGTH) != 0)
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "[%d월%d일 %d시%d분%d초] %s  %s \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, pMob[a_iHandle].MOB.szName, a_pCmd );
			WriteLog( chBuf, ".\\Event\\HelpGM.txt" );
		}
	}
	#endif
  

    // switch/case 문을 테스트 해본다.
	char szResult[1024] = { 0,0,0, };
	strncpy( szResult, a_pCmd, iLength );

    if( !strcmp( szCmd, "/stat" ) || !strcmp( szCmd, "/스탯" ) )// ok
    {

		int iTarget = iArgument1; // mobile handle
		//int iTarget = GetMOBID( szArguments );
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{	
			sprintf( szResult, "%s> Account:%s, Lvl:%d, TChakra(%d,%d,%d,%d), PChakra(%d,%d,%d,%d), HP(%d/%d), TP(%d/%d), DMG(Ph%d~%d,F%d,C%d;L%d,Po%d), DF:%d(AC:%d), Rst(%d,%d,%d,%d), AR:%d, DG:%d, Mv:%d, AtkSpd:%d, Trimu:%d, cla(%d,%d), Gold:%d, kar:%d, BP:%d, Guld:%d"
				, a_pCmd, pUser[iTarget].AccountName, pMob[iTarget].MOB.byLevel, pMob[iTarget].m_kChakra.sMuscle, pMob[iTarget].m_kChakra.sNerves, pMob[iTarget].m_kChakra.sHeart, pMob[iTarget].m_kChakra.sMind
				, pMob[iTarget].MOB.sMuscle, pMob[iTarget].MOB.sNerves, pMob[iTarget].MOB.sHeart, pMob[iTarget].MOB.sMind
				, pMob[iTarget].MOB.nHP, pMob[iTarget].m_iMaxHP, pMob[iTarget].MOB.nTP, pMob[iTarget].m_iMaxTP
				, pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Right].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPoison[0]
				, pMob[iTarget].m_kCombatFactors.iDefense, pMob[iTarget].m_kCombatFactors.iAC
				, pMob[iTarget].m_kCombatFactors.irgResist[0], pMob[iTarget].m_kCombatFactors.irgResist[1], pMob[iTarget].m_kCombatFactors.irgResist[2], pMob[iTarget].m_kCombatFactors.irgResist[3]
				, pMob[iTarget].m_kCombatFactors.iAttackRate, pMob[iTarget].m_kCombatFactors.iDodgeRate
				, pMob[iTarget].m_iMoveSpeed, pMob[iTarget].m_iAttackSpeed
				, pMob[iTarget].m_byClan, pMob[iTarget].MOB.byClass1, pMob[iTarget].MOB.byClass2
				, pMob[iTarget].MOB.nRupiah, pMob[iTarget].MOB.snKarma, pMob[iTarget].MOB.nBramanPoint, pMob[iTarget].MOB.nGuildID								
				);
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );   		    
		}        
    }
    else if( !strcmp( szCmd, "/카스트" ) )// ok
    {
		int iCaste = iArgument1; // 

		pMob[a_iHandle].m_iCaste = iCaste;

		pMob[a_iHandle].CalCasteSkillPoint();

		sprintf( szResult, "%s> User(%d)'s caste:%d, caste sp : %d"
			, a_pCmd, a_iHandle, pMob[a_iHandle].m_iCaste, pMob[a_iHandle].m_kCasteSPRemaining.get_Cur() );
	}
	//	임시코드 테스트용
    else if( !strcmp( szCmd, "/이벤트발동" ) )// ok
    {
		int iEvent = iArgument1; // 
		int iParam = iArgument2;
		DWORD dwFlag = 0x00000001;

		if(iEvent<1 || iEvent>8) return;
		dwFlag = dwFlag << (iEvent-1);
		SetGameEvent(a_iHandle, dwFlag & pUser[a_iHandle].m_dwEvent, &iParam);

		sprintf( szResult, "%s> User(%d)'s EVENT:%08X, caste flag : %d"
			, a_pCmd, a_iHandle, pUser[a_iHandle].m_dwEvent, dwFlag );
	}
    else if( !strcmp( szCmd, "/stat2" ) )// ok
    {
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{	
			sprintf( szResult, "%s> Account:%s, Lvl:%d, HP(%d/%d), TP(%d/%d), DMG(Ph%d~%d,F%d,C%d;L%d,Po%d), DF:%d(AC:%d), Rst(%d,%d,%d,%d), AR:%d, DG:%d, Mv:%d, AtkSpd:%d, Trimu:%d, cla(%d,%d), Gold:%d, kar:%d, BP:%d, Guld:%d"
				, a_pCmd, pUser[iTarget].AccountName, pMob[iTarget].MOB.byLevel
				, pMob[iTarget].MOB.nHP, pMob[iTarget].m_iMaxHP, pMob[iTarget].MOB.nTP, pMob[iTarget].m_iMaxTP
				, pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Right].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPoison[0]
				, pMob[iTarget].m_kCombatFactors.iDefense, pMob[iTarget].m_kCombatFactors.iAC
				, pMob[iTarget].m_kCombatFactors.irgResist[0], pMob[iTarget].m_kCombatFactors.irgResist[1], pMob[iTarget].m_kCombatFactors.irgResist[2], pMob[iTarget].m_kCombatFactors.irgResist[3]
				, pMob[iTarget].m_kCombatFactors.iAttackRate, pMob[iTarget].m_kCombatFactors.iDodgeRate
				, pMob[iTarget].m_iMoveSpeed, pMob[iTarget].m_iAttackSpeed
				, pMob[iTarget].m_byClan, pMob[iTarget].MOB.byClass1, pMob[iTarget].MOB.byClass2
				, pMob[iTarget].MOB.nRupiah, pMob[iTarget].MOB.snKarma, pMob[iTarget].MOB.nBramanPoint, pMob[iTarget].MOB.nGuildID								
				);
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );   		    
		}        
    }
    else if( !strcmp( szCmd, "/stat3" ) )// ok
    {
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_MOB > iTarget )	//	동일지역내 상대방 존재
		{
			pMob[iTarget].UpdateDamage( eTNEqu_OneHandWeapon );
			pMob[iTarget].UpdateDamage( eTNEqu_Shield );
			pMob[iTarget].UpdateEquipmentPoints();

			sprintf( szResult, "%s> Right-Hand(Ph%d~%d,F%d,C%d;L%d,Po%d), Left-Hand(Ph%d~%d,F%d,C%d;L%d,Po%d)"
				, a_pCmd
				, pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Right].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPoison[0]
				, pMob[iTarget].m_krgDamage[eHnd_Left].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Left].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Left].irgPoison[0]
				);
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );   		    
		}        
    }
    else if( !strcmp( szCmd, "/stat4" ) )// ok
    {
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_MOB > iTarget )	//	동일지역내 상대방 존재
		{
			sprintf( szResult, "%s> Immu:%u, Aff:%u, clan:%d"
				, a_pCmd
				, pMob[iTarget].m_iImmunity, pMob[iTarget].m_iAffections, pMob[iTarget].m_byClan
				);
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );   		    
		}        
    }
	else if( !strcmp( szCmd, "/refresh" ) || !strcmp( szCmd, "/재스탯" ) )
	{
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{	
			pMob[iTarget].Init( iTarget );
			sprintf( szResult, "%s> Lvl:%d, TChakra(%d,%d,%d,%d), PChakra(%d,%d,%d,%d), HP(%d/%d), TP(%d/%d), DMG(Ph%d~%d,F%d,C%d;L%d,Po%d), DF:%d(AC:%d), Rst(%d,%d,%d,%d), AR:%d, DG:%d, Mv:%d, AtkSpd:%d, Trimu:%d, cla(%d,%d), Gold:%d, kar:%d, BP:%d, Guld:%d"
				, a_pCmd, pMob[iTarget].MOB.byLevel, pMob[iTarget].m_kChakra.sMuscle, pMob[iTarget].m_kChakra.sNerves, pMob[iTarget].m_kChakra.sHeart, pMob[iTarget].m_kChakra.sMind
				, pMob[iTarget].MOB.sMuscle, pMob[iTarget].MOB.sNerves, pMob[iTarget].MOB.sHeart, pMob[iTarget].MOB.sMind
				, pMob[iTarget].MOB.nHP, pMob[iTarget].m_iMaxHP, pMob[iTarget].MOB.nTP, pMob[iTarget].m_iMaxTP
				, pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPhy[1], pMob[iTarget].m_krgDamage[eHnd_Right].irgFire[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgCold[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgLightning[0], pMob[iTarget].m_krgDamage[eHnd_Right].irgPoison[0]
				, pMob[iTarget].m_kCombatFactors.iDefense, pMob[iTarget].m_kCombatFactors.iAC
				, pMob[iTarget].m_kCombatFactors.irgResist[0], pMob[iTarget].m_kCombatFactors.irgResist[1], pMob[iTarget].m_kCombatFactors.irgResist[2], pMob[iTarget].m_kCombatFactors.irgResist[3]
				, pMob[iTarget].m_kCombatFactors.iAttackRate, pMob[iTarget].m_kCombatFactors.iDodgeRate
				, pMob[iTarget].m_iMoveSpeed, pMob[iTarget].m_iAttackSpeed
				, pMob[iTarget].m_byClan, pMob[iTarget].MOB.byClass1, pMob[iTarget].MOB.byClass2
				, pMob[iTarget].MOB.nRupiah, pMob[iTarget].MOB.snKarma, pMob[iTarget].MOB.nBramanPoint, pMob[iTarget].MOB.nGuildID
								
				);
		}
		else
		{
		    sprintf( szResult, "%s>  invalid user ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/mv" ) || !strcmp( szCmd, "/이" ) )// ok
	{
		int x = iArgument1, y = iArgument2;
		int tret = GetEmptyMobGrid( a_iHandle, &x, &y );
		if( FALSE == tret )
		{
			sprintf( szResult, "%s> can't move to (%d,%d)", a_pCmd, iArgument1, iArgument2 );
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return;
		}

		MSG_Action sm;
		GetAction( a_iHandle, x, y, &sm );
		sm.Effect = 5;

		pUser[a_iHandle].nPreX = x; pUser[a_iHandle].nPreY = y;
		if( a_iHandle < MAX_USER ) pUser[a_iHandle].cSock.AddMessage( (char*)&sm, sizeof(sm) );
		GridMulticast( a_iHandle, x, y, (MSG_STANDARD*)&sm, 100, ACTION_WARP );

/*
		// 자신의 정보를 이동할 지역에 있는 기존의 애들한테 뿌려준다.
		S_SCP_INIT_OTHER_MOB m;
		GetCreateMob( a_iHandle, &m );
		GridMulticast( x, y, (MSG_STANDARD*)&m, a_iHandle, 20 );
*/
	}
    else if( !strcmp( szCmd, "/movepc" ) || !strcmp( szCmd, "/소환" ) )// ok
    {
		int iMobID = GetMOBID( szArgument1 );
		int x = iArgument2, y = iArgument3;
		if(x==0 && y==0) 
		{ x = pMob[a_iHandle].TargetX; y = pMob[a_iHandle].TargetY; }

		int tret = GetEmptyMobGrid( iMobID, &x, &y );
		if( FALSE == tret )
		{
			sprintf( szResult, "%s> can't move to (%d,%d)", a_pCmd, iArgument2, iArgument3 );
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return;
		}

		if( 0 < iMobID && MAX_USER > iMobID )	//	동일지역내 상대방 존재
		{	
			MSG_Action sm;
			GetAction( iMobID, x, y, &sm );
			sm.Effect = 5;
			pUser[iMobID].nPreX = x; pUser[iMobID].nPreY = y;
			pUser[iMobID].cSock.AddMessage( (char*)&sm, sizeof(sm) );
			GridMulticast( iMobID, x, y, (MSG_STANDARD*)&sm, 100,ACTION_WARP );

			/*
			// 자신의 정보를 이동할 지역에 있는 기존의 애들한테 뿌려준다.
			S_SCP_INIT_OTHER_MOB m;
			GetCreateMob( iMobID, &m );
			GridMulticast( x, y, (MSG_STANDARD*)&m, iMobID, 20 );
			*/
		}
		else
		{
			MSG_Warp sm; sm.wType = _MSG_Warp;
			strncpy(sm.szName, szArgument1, sizeof(sm.szName));
			sm.byType = CONNECT_TYPE_GMRECALL;
			sm.nID = a_iHandle; sm.dwPlace = ServerIndex+1;
			if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
			{	Log("err /movepc DB-SEND",pUser[a_iHandle].AccountName,pUser[a_iHandle].IP);
			}  		    
		}        
    }
	else if( !strcmp( szCmd, "/moveother" ) )// ok
	{
		int iMobID = iArgument1; // 옮길 mob ID

		if( 0 >= iMobID || MAX_MOB <= iMobID )
		{
			sprintf( szResult, "%s> Invalid ID", a_pCmd );
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return;
		}

		int x = iArgument2, y = iArgument3;
		int tret = GetEmptyMobGrid( iMobID, &x, &y );
		if( FALSE == tret )
		{
			sprintf( szResult, "%s> can't move to (%d,%d)", a_pCmd, iArgument2, iArgument3 );
			strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
			pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
			return;
		}

		if( eTNMob_NPC == pMob[iMobID].m_eMobType )
		{
			if( MOB_COMBAT == pMob[iMobID].Mode ) // 전투 중이었다.
			{
				pMob[iMobID].Mode = MOB_PEACE;
				pMob[iMobID].CurrentTarget = 0;
				//memset( pMob[iMobID].EnemyList, 0, sizeof( pMob[iMobID].EnemyList ) );
			}
		}
		MSG_Action sm;
		GetAction( iMobID, x, y, &sm );
		sm.Effect = 5; // teleport
		if( iMobID < MAX_USER ) 
		{
			pUser[iMobID].nPreX = x; pUser[iMobID].nPreY = y;
			pUser[iMobID].cSock.AddMessage( (char*)&sm, sizeof(sm) );
		}
		GridMulticast( iMobID, x, y, (MSG_STANDARD*)&sm, 100, ACTION_WARP );
/*
		// 자신의 정보를 이동할 지역에 있는 기존의 애들한테 뿌려준다.
		S_SCP_INIT_OTHER_MOB m;
		GetCreateMob( iMobID, &m );
		GridMulticast( x, y, (MSG_STANDARD*)&m, iMobID, 20 );
*/
	}
	else if( !strcmp( szCmd, "/mvzone" ) || !strcmp( szCmd, "/존이동" ) )
	{	
		char temp[512] = { 0,0,0, };
		S_CSP_REQ_MOVE_PORTAL kMsg;
		kMsg.wEndPortalID = iArgument1;

		S_SCP_RESP_MOVE_PORTAL sm; sm.wType=SCP_RESP_MOVE_PORTAL;

		bool bRet=true;
		DWORD dwServerID=0; short snStartX=0; short snStartZ=0; short snEndX=0; short snEndZ=0; DWORD dwZoneLevel=0;
		bRet &= g_ParamMgr.HT_bGetPortalInfo( kMsg.wEndPortalID, &dwServerID, &dwZoneLevel, &snStartX, &snStartZ, &snEndX, &snEndZ );
/*
		if(!bRet) 
		{
			sprintf( szResult, "%s> 존이동 실패> zone ID 확인 요망", a_pCmd );
		}

		{	sprintf(temp,"dbg CSP_REQ_MOVE_PORTAL find portal data error startp:%d endp:%d", kMsg.wStartPortalID, kMsg.wEndPortalID);
			Log(temp, pUser[a_iHandle].AccountName, pUser[a_iHandle].IP);
			sm.byResult=REPLY_MOVE_PORTAL_FAIL; 
			pUser[a_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL)); return;
		}
*/
		BYTE byMoveZone = (BYTE)( dwServerID - HT_MAP_START + 1 );
		if( bRet && (byMoveZone != (ServerIndex+1)) && (ServerDown==-1000) )	//	다른 존이면, ...
		{
			//sprintf(temp,"dbg char:%s move portal to other zone:%d", pMob[a_iHandle].MOB.szName, byMoveZone );
			//Log( temp, pUser[a_iHandle].AccountName, pUser[a_iHandle].IP );
			pMob[a_iHandle].m_kWaitAction.iAction = eWaitAct_ZonePortal;

			sm.byResult=REPLY_MOVE_PORTAL_OUTAREA; 
			sm.byZone=byMoveZone; sm.nMoney=pMob[a_iHandle].MOB.nRupiah;
			pUser[a_iHandle].cSock.SendOneMessage((char*)&sm, sizeof(S_SCP_RESP_MOVE_PORTAL));
			
			pMob[a_iHandle].m_eFSM = eTNFsm_Stand;
			pMob[a_iHandle].m_kLastTime.uiSitted = 0;
			sprintf( szResult, "%s> succeeded to move the other zone", a_pCmd );
		}
		else
		{
			sprintf( szResult, "%s> faild to move the other zone> check the portal ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/hold" ) || !strcmp( szCmd, "/정지" ) )
	{
		int iTarget = iArgument1;				// mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{	
			if( !strcmp( "off", szArgument2 ) )// hold를 turn off 시켜준다.
			{
				pMob[iTarget].TurnOffAffection( eTNAfn_Hold2 );
				sprintf( szResult, "%s> hold is debuffered on a target.", a_pCmd );
			}
			else
			{
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_Hold2;
				kEffect.iDuration = 600000;
				kEffect.iParam1 = 100;
				kEffect.iParam2 = 0;
				pMob[iTarget].AddEffect( kEffect, a_iHandle, a_iHandle );
				pMob[iTarget].BroadcastUpdateStatusMsg();
				pUser[iTarget].cSock.SendMessage();

				sprintf( szResult, "%s> hold is affected on a target", a_pCmd );
			}
		}
		else
		{
		    sprintf( szResult, "%s>  invalid user ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/follow" ) )
	{
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			if( !strcmp( "off", szArgument2 ) )
			{
				pMob[iTarget].m_iPassenger = 0; // follow를 turn off 시켜준다.
				sprintf( szResult, "%s> I will stop to follow %d", a_pCmd, iTarget );
			}
			else
			{
				pMob[iTarget].m_iPassenger = a_iHandle;
				sprintf( szResult, "%s> I will follow %d", a_pCmd, iTarget );
			}			
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/buffer" ) )
	{
		int iTarget = iArgument1; // mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			char szNormalInfo[1024] = { 0,0,0, };
			sprintf( szNormalInfo, "\r\n\r\nMob:%d/%s \r\n", iTarget, pMob[iTarget].MOB.szName );
			WriteLog( szNormalInfo, ".\\monster_log\\[DEBUG]PrintBuffer.txt" );

			for( int i = 0; i < TN_MAX_VARIATION_COUNT; ++i )
			{
				char szBuf[1024] = { 0,0,0, };
				sprintf( szBuf, "Index:%d, Equip(%d,%d), Passive(%d,%d), Activ(%d,%d) \r\n"
					, i
					, pMob[iTarget].m_krgVariation[i][eVar_Equipment].iPPlus, pMob[iTarget].m_krgVariation[i][eVar_Equipment].iPlus					
					, pMob[iTarget].m_krgVariation[i][eVar_PassiveSkill].iPPlus, pMob[iTarget].m_krgVariation[i][eVar_PassiveSkill].iPlus
					, pMob[iTarget].m_krgVariation[i][eVar_Skill].iPPlus, pMob[iTarget].m_krgVariation[i][eVar_Skill].iPlus
					);
				WriteLog( szBuf, ".\\monster_log\\[DEBUG]PrintBuffer.txt" );
			}
		}
		else
		{
			sprintf( szResult, "%s> Error> Invalid handle!", a_pCmd );
		}

	}
	else if( !strcmp( szCmd, "/speed" ) || !strcmp( szCmd, "/스피드" ) )
	{
		if( 1 <= iArgument1 && 100 >= iArgument1 )
		{	
			TNEFFECT kEffect;
			kEffect.iID = eTNAfn_MoveSpeedPlus;
			kEffect.iDuration = 3600000; // 60 분
			kEffect.kFunc.iData = 0;
			kEffect.iParam1 = iArgument1;
			kEffect.iParam2 = 0;
			pMob[a_iHandle].AddEffect( kEffect, a_iHandle, a_iHandle );
			pMob[a_iHandle].NotifyUpdateUIMsg();
			pUser[a_iHandle].cSock.SendMessage();

			sprintf( szResult, "%s> the speed of move is %d", a_pCmd, pMob[a_iHandle].m_iMoveSpeed );
		}
		else
		{
		    sprintf( szResult, "%s> the value of speed is invalid. valid value(5~100)", a_pCmd );
		}
	}
#ifdef __TN_PLAYMOVIE__
	else if( !strcmp( szCmd, "/공성상징물" ) )
	{
		if( 1 == iArgument1 ) g_kSiege.InstallSymbols();
		else g_kSiege.DestroySymbols();
	}
	else if( !strcmp( szCmd, "/방향전환" ) )
	{
		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				pMob[iMob].Direction = iArgument1;

				MSG_Action sm; GetAction( iMob, pMob[iMob].TargetX, pMob[iMob].TargetY, &sm);
				sm.Effect = 1; // stand
				GridMulticast( iMob, pMob[iMob].TargetX, pMob[iMob].TargetY, (MSG_STANDARD*)&sm );
			}
		}
	}
	else if( !strcmp( szCmd, "/가로정렬" ) )
	{// x, y, length
		int x = iArgument1;
		int y = iArgument2;
		int iLen = iArgument3;

		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				Teleport( iMob, x, y );
				x += 2;
			}

			if( (x-iArgument1) > iLen )
			{
				++y;
				x = iArgument1 + 1;
			}
		}
	}
	else if( !strcmp( szCmd, "/세로정렬" ) )
	{
		int x = iArgument1;
		int y = iArgument2;
		int iLen = iArgument3;

		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				Teleport( iMob, x, y );
				y += 2;
			}

			if( (y-iArgument2) > iLen )
			{
				++x;
				y = iArgument2 + 1;
			}
		}		// teleport를 사용
	}
	else if( !strcmp( szCmd, "/로봇이동" ) )
	{ //0/1
		// teleport를 사용
		if( 1 == iArgument1 ) pMob[a_iHandle].m_iAIOption = pMob[a_iHandle].m_iAIOption | eTNAIO_Follow;
		else
		{
			if( eTNAIO_Follow & pMob[a_iHandle].m_iAIOption ) pMob[a_iHandle].m_iAIOption = pMob[a_iHandle].m_iAIOption ^ eTNAIO_Follow;
		}
	}	
	else if( !strcmp( szCmd, "/robot" ) )
	{ // iPC, count, Direction, range		
		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				DeleteMob(iMob,645, 0, eTNPrdt_RemoveNormal, 240);
				pMob[iMob].Mode = MOB_EMPTY;
			}
		}

		if( 0 < iArgument1 && 1000 > iArgument1 )
		{
			HS2D_COORD krgPos[8];
			int iBodyRadius = 1;//pMob[a_iHandle].m_byBodyRadius;
			int iSize = 4;//iBodyRadius + iBodyRadius + 1;
			if( 0 < iArgument4 ) iSize = iArgument4;
			//if( 0 >= iSize ) return;
			HS2D_COORD kCur;
			kCur.x = pMob[a_iHandle].TargetX;
			kCur.y = pMob[a_iHandle].TargetY;
			krgPos[0].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[0].y = kCur.y - ( iSize + iBodyRadius );
			krgPos[1].x = kCur.x - ( iBodyRadius );
			krgPos[1].y = kCur.y - ( iSize + iBodyRadius );
			krgPos[2].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[2].y = kCur.y - ( iSize + iBodyRadius );

			krgPos[3].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[3].y = kCur.y - ( iBodyRadius );
			krgPos[4].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[4].y = kCur.y - ( iBodyRadius );

			krgPos[5].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[5].y = kCur.y + ( iBodyRadius + iBodyRadius );
			krgPos[6].x = kCur.x - ( iBodyRadius );
			krgPos[6].y = kCur.y + ( iBodyRadius + iBodyRadius );
			krgPos[7].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[7].y = kCur.y + ( iBodyRadius + iBodyRadius );

            // 소환할 때

            //int iMonsterDataIndex = a_kSkill.krgEffect[i].iParam1 - 2000; // the index of monster data
            int iSummonCount = iArgument2; // 소환되는 수
			int iFormation = 0;
			if( 7 < iSummonCount ) iFormation = 1;
			int iIndex = 0;
			int iSummoned = 0;
            for( int iCount = 0; iCount < iSummonCount; ++iCount )
            {
				int x = 0, y = 0;
				if( 1 == iFormation )
				{
					x = krgPos[iIndex].x + rand() % iSize;
					y = krgPos[iIndex].y + rand() % iSize;
					++iIndex;
					if( 7 < iIndex ) iIndex = 0;
				}
				else
				{// random하게 한 곳에서 태어난다.
					iIndex = rand() % 8;
					x = krgPos[iIndex].x + rand() % iSize;
					y = krgPos[iIndex].y + rand() % iSize;
				}

				
				int iMob = pMob[a_iHandle].SummonRobot( iArgument1, x, y, iArgument3 );
				if( 0 < iMob )
				{
					pMob[a_iHandle].m_irgRobot[iSummoned] = iMob;
					++iSummoned;
				}
				//if( ROBOT_START <= iMob && ROBOT_END >= iMob )  ++iSummoned;
            }  
		}
		else
		{
			sprintf( szResult, "%s> [USAGE] /summon [MONSTER-ID] [POP_COUNT] [8|9] (MONSTER-ID:2001~2999, 8:neutral, 9:aggressive)", a_pCmd );
		}

		
	}
	else if( !strcmp( szCmd, "/a" ) || !strcmp( szCmd, "/로봇공격" ) )
	{
		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				pMob[iMob].ClearCurrentTarget();
				pMob[iMob].ClearAttacker( 0 );
				pMob[iMob].MemorizeAttacker( 0, 1, iArgument1 );			
			}
		}
	}
	else if( !strcmp( szCmd, "/f" ) || !strcmp( szCmd, "/로봇멈춤" ) )
	{
		for( int i = 0; i < eRobot_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgRobot[i];
			if ( MOB_EMPTY != pMob[iMob].Mode )
			{
				pMob[iMob].ClearCurrentTarget();
				pMob[iMob].ClearAttacker( 0 );
				pMob[iMob].Mode = MOB_PEACE;
				pMob[iMob].OnFollow( a_iHandle );
			}
		}
	}
#endif
	else if( !strcmp( szCmd, "/summon" ) )	// monster ID, Pop Count, class
	{
		if( 1 > iArgument2 || 10 < iArgument2 ) iArgument2 = 1;
		if( eTNCls_Warrior != iArgument3 && eTNCls_NPC != iArgument3 && eTNCls_Event != iArgument3 ) iArgument3 = eTNCls_Warrior;
		// eTNCls_NPC(19) 일 경우는 NPC-Monster의 형태를 취한다.

		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			TNSKILL_DATA kSkill; // 소환자의 clan이 상속된다.
			kSkill.krgEffect[0].iID = eTNAfn_Summon; // 
			kSkill.krgEffect[0].kFunc.iData = iArgument3; // class1
			kSkill.krgEffect[0].iDuration = eTNPrdt_PopRaise; // pop type
			kSkill.krgEffect[0].iParam1 = iArgument1; // monster ID
			kSkill.krgEffect[0].iParam2 = iArgument2; // count

			pMob[a_iHandle].CastOnly( kSkill );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/summon2" ) || !strcmp( szCmd, "/서" ) )	// monster ID, Pop Count, 8|9(clan) range
	{
		if( 1 > iArgument2 || 10 < iArgument2 ) iArgument2 = 1;
		if( 0 >= iArgument2 ) iArgument2 = 1;
		if( 0 >= iArgument3 ) iArgument3 = eTNClan_Neutral;

		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			HS2D_COORD krgPos[8];
			int iBodyRadius = pMob[a_iHandle].m_byBodyRadius;
			int iSize = iBodyRadius + iBodyRadius + 1;
			if( 0 < iArgument4 ) iSize = iArgument4;
			//if( 0 >= iSize ) return;
			HS2D_COORD kCur;
			kCur.x = pMob[a_iHandle].TargetX;
			kCur.y = pMob[a_iHandle].TargetY;
			krgPos[0].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[0].y = kCur.y - ( iSize + iBodyRadius );
			krgPos[1].x = kCur.x - ( iBodyRadius );
			krgPos[1].y = kCur.y - ( iSize + iBodyRadius );
			krgPos[2].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[2].y = kCur.y - ( iSize + iBodyRadius );

			krgPos[3].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[3].y = kCur.y - ( iBodyRadius );
			krgPos[4].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[4].y = kCur.y - ( iBodyRadius );

			krgPos[5].x = kCur.x - ( iSize + iBodyRadius );
			krgPos[5].y = kCur.y + ( iBodyRadius + iBodyRadius );
			krgPos[6].x = kCur.x - ( iBodyRadius );
			krgPos[6].y = kCur.y + ( iBodyRadius + iBodyRadius );
			krgPos[7].x = kCur.x + ( iBodyRadius + iBodyRadius );
			krgPos[7].y = kCur.y + ( iBodyRadius + iBodyRadius );

            // 소환할 때

            //int iMonsterDataIndex = a_kSkill.krgEffect[i].iParam1 - 2000; // the index of monster data
            int iSummonCount = iArgument2; // 소환되는 수
			int iFormation = 0;
			if( 7 < iSummonCount ) iFormation = 1;
			int iIndex = 0;
            for( int iCount = 0; iCount < iSummonCount; ++iCount )
            {
				int x = 0, y = 0;
				if( 1 == iFormation )
				{
					x = krgPos[iIndex].x + rand() % iSize;
					y = krgPos[iIndex].y + rand() % iSize;
					++iIndex;
					if( 7 < iIndex ) iIndex = 0;
				}
				else
				{// random하게 한 곳에서 태어난다.
					iIndex = rand() % 8;
					x = krgPos[iIndex].x + rand() % iSize;
					y = krgPos[iIndex].y + rand() % iSize;
				}

				int iMob = pMob[a_iHandle].Summon( iArgument1, iArgument2, eTNPrdt_PopRaise, eTNCls_Warrior, 0, iArgument3, 0, x, y, 0, false, 0, 0, 14 );

				if( 0 == iMob ) ++iSummonCount;
				if( 30 <= iSummonCount ) break;
            }  
		}
		else
		{
			sprintf( szResult, "%s> [USAGE] /summon [MONSTER-ID] [POP_COUNT] [8|9] (MONSTER-ID:2001~2999, 8:neutral, 9:aggressive)", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/summon3" ) )	// monster ID, x, y, class1, clan
	{
		if	( iArgument2<0 || iArgument3<0 || iArgument2>MAX_GRIDX || iArgument3>MAX_GRIDY ) return;
		if( eTNCls_Warrior > iArgument4 || eTNCls_NPC < iArgument4 ) iArgument4 = eTNCls_Warrior;
		if( eTNClan_NPC < iArgument5 || eTNClan_NoTrimuritiy > iArgument5 ) return;
		// eTNCls_NPC(19) 일 경우는 NPC-Monster의 형태를 취한다.

		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			pMob[a_iHandle].Summon( iArgument1/*tribe*/, 1/*pop#*/, eTNPrdt_PopRaise, iArgument4/*class1*/, eTNCls2_Basic/*class2*/, iArgument5/*clan*/, 0/*Direction*/, iArgument2, iArgument3, 0/*Enemy*/, false, 0, 0, 15 );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/summonpet" ) )	// monster ID, clan, duration(second)
	{
		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			int iClan = iArgument2;
			int iDuration = iArgument3;
			pMob[a_iHandle].Summon( iArgument1, 1, eTNPrdt_PopRaise, eTNCls_Summoned, eTNCls2_Pet, iClan, 0/*Direction*/, pMob[a_iHandle].TargetX, pMob[a_iHandle].TargetY, 0/*Enemy*/, false, iDuration, 0, 16 );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/summonInteractor" ) )	// monster ID, class1, clan, duration(second)
	{
		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			int iClass1 = iArgument2;
			int iClan = iArgument3;
			int iDuration = iArgument4;
			pMob[a_iHandle].Summon( iArgument1, 1, eTNPrdt_PopRaise, iClass1, eTNCls2_Basic, iClan, 0/*Direction*/, pMob[a_iHandle].TargetX, pMob[a_iHandle].TargetY, 0/*Enemy*/, false, iDuration, 0, 17 );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/height" ) )	// mob handle
	{
		int iTarget = iArgument1;				// mobile handle
		if( 0 < iTarget && MAX_MOB > iTarget )
		{	
			int x, y;
			x = pMob[iTarget].TargetX;
			y = pMob[iTarget].TargetY;
			int iHeight = g_krgCell[y][x].usHeight;
			sprintf( szResult, "height:%d(%d,%d), mob:%d", iHeight, x, y, iTarget );
		}
		else
		{
		    sprintf( szResult, "%s>  invalid mobile handle", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/SetHeight" ) )	// obstacle, character
	{
		int iOld = g_irgSetting[eCnst_ObstacleHeight];
		g_irgSetting[eCnst_ObstacleHeight] = iArgument1; // obstacle
		g_irgSetting[eCnst_CharacterHeight] = iArgument2; // character

		sprintf( szResult, "The height of a obstacle:%d(old:%d)", g_irgSetting[eCnst_ObstacleHeight], iOld );
	}
	else if( !strcmp( szCmd, "/army" ) )
	{
		if( 1 > iArgument2 ) iArgument2 = 1;
		if( 20 < iArgument2 ) iArgument2 = 20;
		if( 2000 < iArgument1 && 3000 > iArgument1 )
		{
			HS2D_COORD krgPos[8];
			int iSize = 1;
			int iBodyRadius = 1;
			if( 0 >= iSize ) return;

			krgPos[0].x = pMob[a_iHandle].TargetX - ( iSize + iBodyRadius );
			krgPos[0].y = pMob[a_iHandle].TargetY - ( iSize + iBodyRadius );
			krgPos[1].x = pMob[a_iHandle].TargetX - ( iBodyRadius );
			krgPos[1].y = pMob[a_iHandle].TargetY - ( iSize + iBodyRadius );
			krgPos[2].x = pMob[a_iHandle].TargetX + ( iBodyRadius + iBodyRadius );
			krgPos[2].y = pMob[a_iHandle].TargetY - ( iSize + iBodyRadius );

			krgPos[3].x = pMob[a_iHandle].TargetX - ( iSize + iBodyRadius );
			krgPos[3].y = pMob[a_iHandle].TargetY - ( iBodyRadius );
			krgPos[4].x = pMob[a_iHandle].TargetX + ( iBodyRadius + iBodyRadius );
			krgPos[4].y = pMob[a_iHandle].TargetY - ( iBodyRadius );

			krgPos[5].x = pMob[a_iHandle].TargetX - ( iSize + iBodyRadius );
			krgPos[5].y = pMob[a_iHandle].TargetY + ( iBodyRadius + iBodyRadius );
			krgPos[6].x = pMob[a_iHandle].TargetX - ( iBodyRadius );
			krgPos[6].y = pMob[a_iHandle].TargetY + ( iBodyRadius + iBodyRadius );
			krgPos[7].x = pMob[a_iHandle].TargetX + ( iBodyRadius + iBodyRadius );
			krgPos[7].y = pMob[a_iHandle].TargetY + ( iBodyRadius + iBodyRadius );

			if( eFollower_MaxCount < iArgument2 ) iArgument2 = eFollower_MaxCount;
			if( 1 > iArgument2 ) iArgument2 = 1;
			int iIndex = 0;
			int iClan = 0;
			if( 0 == iArgument3 ) iClan = pMob[a_iHandle].m_byClan;
			if( eTNClan_GM == iClan ) iClan = eTNClan_Neutral;

            for( int iCount = 0; iCount < iArgument2; ++iCount )
            {
				int x = 0, y = 0;
				x = krgPos[iIndex].x + rand() % iSize;
				y = krgPos[iIndex].y + rand() % iSize;
				++iIndex;
				if( 7 < iIndex ) iIndex = 0;
				int iFollower = pMob[a_iHandle].m_irgFollower[iCount];
				if( MAX_USER <= iFollower && MAX_MOB > iFollower ) KillMonster( iFollower ); //pMob[iFollower].MOB.nHP = 0;
				pMob[a_iHandle].m_irgFollower[iCount] = pMob[a_iHandle].Summon( iArgument1, iArgument2, eTNPrdt_PopRaise, eTNCls_Follower, 0, iClan, 0, x, y, 0, false, 0, 0, 18 );
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster ID", a_pCmd );   		    
		}
	}
	else if( !strcmp( szCmd, "/releaseArmy" ) )
	{
		for( int i = 0; i < eFollower_MaxCount; ++i )
		{
			int iMob = pMob[a_iHandle].m_irgFollower[i];
			KillMonster( iMob );
			/*
			pMob[iMob].MOB.nHP = 0; 
			pMob[iMob].CurrentTarget = 0;
			pMob[iMob].m_eFSM = eTNFsm_Dead;
			*/
		}

		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/account" ) )		// target ID
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			sprintf( szResult, "%s> Account:%s", a_pCmd, pUser[iArgument1].AccountName );		
		}
		else
		{
			sprintf( szResult, "%s> invalid ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/atk" ) )
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			for( int iIndex = 0; iIndex < eFollower_MaxCount; ++iIndex )
			{
				int iFollowerIndex = pMob[a_iHandle].m_irgFollower[iIndex];
				if( MAX_USER > iFollowerIndex || MAX_MOB <= iFollowerIndex ) continue;
				pMob[iFollowerIndex].m_kLastTime.uiSelectTarget = CurrentTime + 5000;
				pMob[iFollowerIndex].CurrentTarget = iArgument1;
				pMob[iFollowerIndex].OnUnderAttack( iArgument1 );
			}
		}
		else if( 0 == iArgument1 )
		{ // 산개하여 주위의 모든 mob(berserk는 제외)을 공격한다. // berserk 성향으로 바꾼다.

		}
		else
		{
			sprintf( szResult, "%s> invalid target ID", a_pCmd );   		    
		}
	}
	else if( !strcmp( szCmd, "/truesight" ) || !strcmp( szCmd, "/투시" ) )
	{
		TNEFFECT kEffect;
		kEffect.iID = eTNAfn_WizardEyes;
		kEffect.iDuration = 3600000; // 60분
		kEffect.iParam1 = 0;
		kEffect.iParam2 = 0;
		pMob[a_iHandle].AddEffect( kEffect, a_iHandle, a_iHandle );
		pMob[a_iHandle].NotifyUpdateStatusMsg();
		pUser[a_iHandle].cSock.SendMessage();

		sprintf( szResult, "%s> truesight is activated.", a_pCmd );
	}
	else if( !strcmp( szCmd, "/강퇴" ) || !strcmp( szCmd, "/kickout" ) )
	{
		int iTarget = iArgument1;				// mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			MSG_Broadcast kMsg; ZeroMemory(&kMsg, sizeof(kMsg));
			kMsg.wType = _MSG_Broadcast;
			kMsg.wPDULength = sizeof(MSG_Broadcast)-sizeof(HEADER);

			kMsg.byMsgType = MESSAGE_SERVERMSG;
			kMsg.byBgColor = 14;
			kMsg.byTextColor = 15;
			kMsg.byMsgType = 1; 

			if( eCountryKorea == g_eCountryID ) strncpy( kMsg.szMsg, g_pMessageStringTable[_DisconnectedToServer], sizeof(kMsg.szMsg));			
			else strncpy( kMsg.szMsg, g_pMessageStringTable[_KickedByGM], sizeof(kMsg.szMsg));			
			strncpy( kMsg.szName, pMob[a_iHandle].MOB.szName, SZNAME_LENGTH );
			kMsg.byTrimuriti = eTNClan_GM;
			pUser[iTarget].cSock.AddMessage((char*)&kMsg, sizeof(kMsg));

			CloseUser( iTarget );
			sprintf( szResult, "%s> The target user will be disconnected in 15 seconds", a_pCmd );
		}
		else
		{
		    sprintf( szResult, "%s> invalid user ID", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/위치" ) || !strcmp( szCmd, "/where" ) )// ok
    {
		int iTarget = GetMOBID( szArgument1 );
		if( 0 < iTarget )	//	동일지역내 상대방 존재
		{	
			if( MAX_USER <= iTarget ) return;		  
		    int x = pMob[iTarget].TargetX;
		    int y = pMob[iTarget].TargetY;
			sprintf( szResult, "%s> x:%d, y:%d", a_pCmd, x, y );
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/whereid" ) )// ok
    {
		int iTarget = GetMOBIDFromID( szArgument1 );
		if( 0 < iTarget )	//	동일지역내 상대방 존재
		{	
			if( MAX_USER <= iTarget ) return;		  
		    int x = pMob[iTarget].TargetX;
		    int y = pMob[iTarget].TargetY;
			sprintf( szResult, "ID:%s> x:%d, y:%d", a_pCmd, x, y );
		}
		else
		{
			sprintf( szResult, "ID:%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/wheremob" ) )// ok
    {
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_MOB > iTarget )	//	동일지역내 상대방 존재
		{	
		    int x = pMob[iTarget].TargetX;
		    int y = pMob[iTarget].TargetY;
			sprintf( szResult, "%s> x:%d, y:%d", a_pCmd, x, y );
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
    }
    else if( !strcmp( szCmd, "/equip" ) || !strcmp( szCmd, "/장비" ) )
    {
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{			
			STRUCT_ITEM krgItem[MAX_EQUIP];
			memcpy( krgItem, pMob[iTarget].MOB.Equip, sizeof(krgItem) );

			for( int i = 0; i < MAX_EQUIP; ++i )
			{
				if( 0 < krgItem[i].snIndex ) krgItem[i].snIndex += (HT_PARAMTYPE_ITEM_START - 1);
				if( 0 < krgItem[i].snDurability ) krgItem[i].snDurability = krgItem[i].snDurability / 100 + 1;
			}

			sprintf( szResult, "%s> Helmet:%d(%d,%d),EarR:%d,EarL:%d,Neck:%d,Armor:%d(%d,%d), Belt:%d(%d,%d),HandR:%d(%d,%d),HandL:%d(%d,%d), Boots:%d(%d,%d),Gloves:%d(%d,%d),Pants:%d(%d,%d), BraR:%d,BraL:%d,RingR:%d,RingL:%d"
				, a_pCmd, krgItem[eTNEqu_Helmet].snIndex, krgItem[eTNEqu_Helmet].byRefineLevel, krgItem[eTNEqu_Helmet].snDurability
				, krgItem[eTNEqu_EarringRight].snIndex, krgItem[eTNEqu_EarringLeft].snIndex
				, krgItem[eTNEqu_Necklace].snIndex
				, krgItem[eTNEqu_Armor].snIndex, krgItem[eTNEqu_Armor].byRefineLevel, krgItem[eTNEqu_Armor].snDurability
				, krgItem[eTNEqu_Belt].snIndex, krgItem[eTNEqu_Belt].byRefineLevel, krgItem[eTNEqu_Belt].snDurability
				, krgItem[eTNEqu_OneHandWeapon].snIndex, krgItem[eTNEqu_OneHandWeapon].byRefineLevel, krgItem[eTNEqu_OneHandWeapon].snDurability
				, krgItem[eTNEqu_Shield].snIndex, krgItem[eTNEqu_Shield].byRefineLevel, krgItem[eTNEqu_Shield].snDurability
				, krgItem[eTNEqu_Boots].snIndex, krgItem[eTNEqu_Boots].byRefineLevel, krgItem[eTNEqu_Boots].snDurability
				, krgItem[eTNEqu_Gloves].snIndex, krgItem[eTNEqu_Gloves].byRefineLevel, krgItem[eTNEqu_Gloves].snDurability
				, krgItem[eTNEqu_Pants].snIndex, krgItem[eTNEqu_Pants].byRefineLevel, krgItem[eTNEqu_Pants].snDurability
				, krgItem[eTNEqu_BraceletRight].snIndex, krgItem[eTNEqu_BraceletLeft].snIndex
				, krgItem[eTNEqu_RingRight].snIndex, krgItem[eTNEqu_RignLeft].snIndex
				);
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}        
    }
	else if( !strcmp( szCmd, "/weapon" ) || !strcmp( szCmd, "/무기" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_OneHandWeapon];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);       
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/armor" ) || !strcmp( szCmd, "/갑옷" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Armor];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);       
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/pants" ) || !strcmp( szCmd, "/바지" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Pants];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);       
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/helmet" ) || !strcmp( szCmd, "/투구" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Helmet];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);     
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/shield" ) || !strcmp( szCmd, "/방패" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Shield];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);            
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/gloves" ) || !strcmp( szCmd, "/장갑" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Gloves];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);      
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/boots" ) || !strcmp( szCmd, "/신발" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			STRUCT_ITEM kItem;
			kItem = pMob[iTarget].MOB.Equip[eTNEqu_Boots];
			if( 0 < kItem.snIndex ) kItem.snIndex += (HT_PARAMTYPE_ITEM_START - 1);
			if( 0 < kItem.snDurability ) kItem.snDurability = kItem.snDurability / 100 + 1;

			sprintf( szResult, "%s> ID:%d dur:%d, refine:%d, elemental(%d %d %d %d %d %d %d %d %d %d)"
				, a_pCmd
				, kItem.snIndex, kItem.snDurability, kItem.byRefineLevel
				, (kItem.bySubRefine[0])>>4, (kItem.bySubRefine[0])&0x0F
				, (kItem.bySubRefine[1])>>4, (kItem.bySubRefine[1])&0x0F
				, (kItem.bySubRefine[2])>>4, (kItem.bySubRefine[2])&0x0F
				, (kItem.bySubRefine[3])>>4, (kItem.bySubRefine[3])&0x0F
				, (kItem.bySubRefine[4])>>4, (kItem.bySubRefine[4])&0x0F
				);      
		}
		else
		{
		    sprintf( szResult, "%s> not found in this zone", a_pCmd );
		}
	}
	else if( (!strcmp( szCmd, "/JudgeSurvival" )) || !strcmp( szCmd, "/서바이벌판정" )  )		// mob handle, HP
	{
		if( eZone_Stronghold != g_iZoneID ) return;

		char szSurvivals[512] = { 0,0,0, };
		if( 1 == iArgument1 )
		{
			g_kArena.OutputSurvivals( szSurvivals, 0 );			
			PostMessageToZone( szSurvivals );
		}
		else if( 0 == iArgument1 ) g_kArena.OutputSurvivals( szSurvivals, 1 ); // 영자에게만 결과를 보여준다.

		//g_kArena.CheckWinner( 1 ); // winner를 검사하고, 파티원이 아닌 유저를 알린다.
		sprintf( szResult, "%s> %s", a_pCmd, szSurvivals );
	}
	else if( !strcmp( szCmd, "/Bless" ) )		// mob handle
	{
		if( eZone_Cruma != g_iZoneID ) return;

		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			//TriggerEvent( iArgument1, 25, pMob[iArgument1].TargetX, pMob[iArgument1].TargetY, g_irgGod[pMob[iArgument1].m_byClan], 112 );
			//pMob[iArgument1].MOB.nHP = iArgument2;

			int iLeader = pMob[iArgument1].Leader;
			if( 0 >= iLeader ) iLeader = iArgument1; // 자신이 리더이다.

			if( !pMob[iLeader].IsDead() )
			{
				if( !(eTNVSAfn_HaveKalaCore & pMob[iLeader].m_iAffections) ) 
					TriggerEvent( iLeader, 25, pMob[iLeader].TargetX, pMob[iLeader].TargetY, g_irgGod[pMob[iLeader].m_byClan], 111 );
			}

			// 파티원들 소환
			for( int d = 0; d < MAX_PARTY; ++d )
			{   
				int fol = pMob[iLeader].m_irgParty[d];

				if( 0 > fol || MAX_USER <= fol ) continue;
				if( pMob[fol].IsDead() ) continue;
				if( eTNVSAfn_HaveKalaCore & pMob[fol].m_iAffections ) continue;

				TriggerEvent( fol, 25, pMob[fol].TargetX, pMob[fol].TargetY, g_irgGod[pMob[fol].m_byClan], 110 );
			}

			sprintf( szResult, "%s> %s(%d) is blessed!!!", a_pCmd, pMob[iArgument1].MOB.szName, iArgument1 );
		}
		else sprintf( szResult, "%s> invalid handle!!!", a_pCmd );   		    
	}
	else if( !strcmp( szCmd, "/ChangeHP" ) )		// mob handle, HP
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].MOB.nHP = iArgument2;
			sprintf( szResult, "%s> HP:%d", a_pCmd, pMob[iArgument1].MOB.nHP );
		}
		else sprintf( szResult, "%s> invalid handle!!!", a_pCmd );   		    
	}
	else if( !strcmp( szCmd, "/SearchMonsterHandle" ) )
	{
		iArgument1 = iArgument1;

		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			for( int i = MAX_USER; i < MAX_MOB; ++i )
			{
				if( iArgument1 == pMob[i].MOB.snTribe ) break;
			}

			if( MAX_MOB != i ) sprintf( szResult, "%s> Monster ID: %d",  a_pCmd, i ); // 찾았다면, ...
			else sprintf( szResult, "Monster(%d) don't live this zone",  iArgument1 );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );   		    
		}
	}
	else if( !strcmp( szCmd, "/PrintMonsterStat" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{

			sprintf( szResult, "%s> Lvl:%d, Trimu:%d, AI:%d, FSM:%d, HP:%d/%d, AR:%d, DR:%d, DF:%d(AC:%d), Resist(%d,%d,%d,%d)", a_pCmd
				, pMob[iArgument1].MOB.byLevel, pMob[iArgument1].m_byClan, pMob[iArgument1].MOB.byQuest[eMonPrty_AI]
				, pMob[iArgument1].m_eFSM, pMob[iArgument1].MOB.nHP, pMob[iArgument1].m_iMaxHP
				, pMob[iArgument1].m_kCombatFactors.iAttackRate, pMob[iArgument1].m_kCombatFactors.iDodgeRate
				, pMob[iArgument1].m_kCombatFactors.iDefense, pMob[iArgument1].m_kCombatFactors.iAC, pMob[iArgument1].m_kCombatFactors.irgResist[0], pMob[iArgument1].m_kCombatFactors.irgResist[1]
				, pMob[iArgument1].m_kCombatFactors.irgResist[2], pMob[iArgument1].m_kCombatFactors.irgResist[3]
				);
		}
		else
		{
			sprintf( szResult, "%s> invalid Argumenteter1. argument1:%d~%d", a_pCmd, MAX_USER, MAX_MOB );
		}
	}
	else if( !strcmp( szCmd, "/PrintMonsterData" ) ) // 간단한 monster 정보를 화면에 출력
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 ) // npc only
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;

			sprintf( szResult, "%s> Lvl:%d, Trimu:%d, AI:%d, HP:%d, AR:%d, DR:%d, AC:%d, Resist(%d,%d,%d,%d), ArmorType:%d", a_pCmd
				, pMonsterData[iIndex].byLevel, pMonsterData[iIndex].byTrimuriti, pMonsterData[iIndex].byQuest[eMonPrty_AI], pMonsterData[iIndex].nHP
				, pMonsterData[iIndex].sMuscle, pMonsterData[iIndex].sNerves, pMonsterData[iIndex].sHeart  // AR/DR/AC
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability, pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy  // resist
				, pMonsterData[iIndex].byQuest[eMonPrty_ArmorType]
				);
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/RecordMonsterData" ) ) // detail한 정보를 서버 log file에 기록
	{
		if( 2000 <= iArgument1 && 3000 > iArgument1 ) // npc only
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;

			char chBuf[1024] = { 0,0,0, };
			sprintf(chBuf, "\r\n=> ID:%d, Lvl:%d, Trimu:%d, AI:%d, Class:%d, BlockedCell:%d, HP:%d, AR:%d, DR:%d, AC:%d, Sight(%d,%d), CantDetect:%d, Movement:%d, MvSpeed(%d,%d), Resist(%d,%d,%d,%d), Size:%d, Speech(%d/%d), HPRecv:%d, Cond(%d,%d,%d), cond2(%d,%d,%d,%d,%d,%d), PopDelay(%d,%d), skill(%d,%d,%d,%d,%d,%d,%d,%d), sklPtrn(%d,%d,%d,%d / DefaultOnly:%d), SelectTarget(Time:%d, %d,%d,%d,%d / DefaultOnly:%d), Immu(%d,%d), ArmorType:%d	\
							   \r\n\t RewPrana:%d, RewBraman:%d, RewGold:%d, RewItem0(%d,%d) RewItem1(%d,%d), RewItem2(%d,%d), RewItem3(%d,%d), RewItem4(%d,%d), RewItem5(%d,%d), RewItem6(%d,%d), RewItem7(%d,%d), RewItem8(%d,%d), RewItem9(%d,%d), Reserved(0:%d, 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d) \r\n"
, pMonsterData[iIndex].snTribe, pMonsterData[iIndex].byLevel, pMonsterData[iIndex].byTrimuriti, pMonsterData[iIndex].byQuest[eMonPrty_AI], pMonsterData[iIndex].byQuest[eMonPrty_Class], pMonsterData[iIndex].Equip[eMonPrty_BlockedCell].snIndex, pMonsterData[iIndex].nHP, pMonsterData[iIndex].sMuscle, pMonsterData[iIndex].sNerves, pMonsterData[iIndex].sHeart
, pMonsterData[iIndex].byQuest[eMonPrty_NormalSight], pMonsterData[iIndex].byQuest[eMonPrty_CombatSight], pMonsterData[iIndex].Equip[eMonPrty_CantDetect].snIndex, pMonsterData[iIndex].byQuest[eMonPrty_Movement], pMonsterData[iIndex].byQuest[eMonPrty_WalkSpeed], pMonsterData[iIndex].byQuest[eMonPrty_RunSpeed]
, pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability, pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy  // resist
, pMonsterData[iIndex].byQuest[eMonPrty_Size], pMonsterData[iIndex].byQuest[eMonPrty_SpeechRate], pMonsterData[iIndex].byQuest[eMonPrty_SpeechAI], pMonsterData[iIndex].byQuest[eMonPrty_HPRecovery]
, pMonsterData[iIndex].byQuest[eMonPrty_AggrCond], pMonsterData[iIndex].byQuest[eMonPrty_TraceCond], pMonsterData[iIndex].byQuest[eMonPrty_StepBackCond]  // cond1
, pMonsterData[iIndex].byQuest[eMonPrty_HelpCond], pMonsterData[iIndex].byQuest[eMonPrty_HelpCondCount], pMonsterData[iIndex].byQuest[eMonPrty_LinkCond], pMonsterData[iIndex].byQuest[eMonPrty_LinkCondCount], pMonsterData[iIndex].byQuest[eMonPrty_FleeCond], pMonsterData[iIndex].byQuest[eMonPrty_FleeCondCount] // cond2
, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMin].snIndex, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMax].snIndex // pop delay
, pMonsterData[iIndex].Equip[0].snIndex, pMonsterData[iIndex].Equip[1].snIndex, pMonsterData[iIndex].Equip[2].snIndex, pMonsterData[iIndex].Equip[3].snIndex, pMonsterData[iIndex].Equip[4].snIndex, pMonsterData[iIndex].Equip[5].snIndex, pMonsterData[iIndex].Equip[6].snIndex, pMonsterData[iIndex].Equip[7].snIndex // skill
, pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn0], pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn1], pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn2], pMonsterData[iIndex].byQuest[eMonPrty_SklPtrn3], pMonsterData[iIndex].byQuest[eMonPrty_UseDefaultSkillOnly]  // skill pattern
, pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetTime], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget0], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget1], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget2], pMonsterData[iIndex].byQuest[eMonPrty_SelectTarget3], pMonsterData[iIndex].byQuest[eMonPrty_SelectTargetComplexly]  // select target
, pMonsterData[iIndex].nGuildID, pMonsterData[iIndex].byQuest[eMonPrty_ResistEffectConst]
, pMonsterData[iIndex].byQuest[eMonPrty_ArmorType]
, pMonsterData[iIndex].nPrana, pMonsterData[iIndex].nBramanPoint, pMonsterData[iIndex].nRupiah
, pMonsterData[iIndex].Inven[0].snIndex, g_krgRewardItemRate[iIndex][0].get_Rate()
, pMonsterData[iIndex].Inven[1].snIndex, g_krgRewardItemRate[iIndex][1].get_Rate()
, pMonsterData[iIndex].Inven[2].snIndex, g_krgRewardItemRate[iIndex][2].get_Rate()
, pMonsterData[iIndex].Inven[3].snIndex, g_krgRewardItemRate[iIndex][3].get_Rate()
, pMonsterData[iIndex].Inven[4].snIndex, g_krgRewardItemRate[iIndex][4].get_Rate()
, pMonsterData[iIndex].Inven[5].snIndex, g_krgRewardItemRate[iIndex][5].get_Rate()
, pMonsterData[iIndex].Inven[6].snIndex, g_krgRewardItemRate[iIndex][6].get_Rate()
, pMonsterData[iIndex].Inven[7].snIndex, g_krgRewardItemRate[iIndex][7].get_Rate()
, pMonsterData[iIndex].Inven[8].snIndex, g_krgRewardItemRate[iIndex][8].get_Rate()
, pMonsterData[iIndex].Inven[9].snIndex, g_krgRewardItemRate[iIndex][9].get_Rate()
, pMonsterData[iIndex].byQuest[eMonPrty_Reserved0], pMonsterData[iIndex].byQuest[eMonPrty_Reserved1], pMonsterData[iIndex].byQuest[eMonPrty_Reserved2]
, pMonsterData[iIndex].byQuest[eMonPrty_Reserved3], pMonsterData[iIndex].byQuest[eMonPrty_Reserved4], pMonsterData[iIndex].byQuest[eMonPrty_Reserved5]
, pMonsterData[iIndex].byQuest[eMonPrty_Reserved6], pMonsterData[iIndex].byQuest[eMonPrty_Reserved7]
);
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadMonsterData.txt" );
			sprintf( szResult, "%s> The system write the specific monster data to the log file sussessfully.", a_pCmd);
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 2000, 2999 );   		    
		}
	}
	else if( !strcmp( szCmd, "/PrintMonsterStatus" ) )		// mob id
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 ) // npc only
		{
			int iDist = CalDistance( iArgument1, pMob[iArgument1].CurrentTarget );
			char chBuf[1024] = { 0,0,0, };
			//sprintf(chBuf, "\r\n=> ID:%s, Mode:%d, CurrentTarget:%d, iDist:%d, EnemyList(%d,%d,%d,%d,%d), AttackerList(%d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d)
			sprintf(chBuf, "\r\n=> ID:%s, Mode:%d, CurrentTarget:%d, iDist:%d, AttackerCount:%d, AttackerList(%d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d), AttackerList2(%d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d, %d/%d) \
								\r\nCantTraceTarget:%d, AtkCount:%d, TraceCount:%d, TotalTrace:%d, eStatus:%d, Affections:%h, CastCount:%d, Now:%u, ActionLock:%u, m_kLastTime.uiSelectTarget:%u \
								\r\nLvl:%d, Trimu:%d, Class:%d, BlockedCell:%d, Sight(%d,%d), MvSpeed(%d), HP:%d(%d), AR:%d, DR:%d, DF:%d,, Resist(%d,%d,%d,%d), Immunity:%d, skill(%d,%d,%d,%d,%d), m_iSkillCharged:%d \
								\r\n"
, pMob[iArgument1].MOB.szName
, pMob[iArgument1].Mode, pMob[iArgument1].CurrentTarget, iDist//, pMob[iArgument1].EnemyList[0], pMob[iArgument1].EnemyList[1], pMob[iArgument1].EnemyList[2], pMob[iArgument1].EnemyList[3], pMob[iArgument1].EnemyList[4], pMob[iArgument1].EnemyList[5]
, pMob[iArgument1].m_iAttackerCount
, pMob[iArgument1].m_krgAttacker[0].iID, pMob[iArgument1].m_krgAttacker[0].iScore, pMob[iArgument1].m_krgAttacker[1].iID, pMob[iArgument1].m_krgAttacker[1].iScore, pMob[iArgument1].m_krgAttacker[2].iID, pMob[iArgument1].m_krgAttacker[2].iScore, pMob[iArgument1].m_krgAttacker[3].iID, pMob[iArgument1].m_krgAttacker[3].iScore
, pMob[iArgument1].m_krgAttacker[4].iID, pMob[iArgument1].m_krgAttacker[4].iScore, pMob[iArgument1].m_krgAttacker[5].iID, pMob[iArgument1].m_krgAttacker[5].iScore, pMob[iArgument1].m_krgAttacker[6].iID, pMob[iArgument1].m_krgAttacker[6].iScore, pMob[iArgument1].m_krgAttacker[7].iID, pMob[iArgument1].m_krgAttacker[7].iScore
, pMob[iArgument1].m_krgAttacker[8].iID, pMob[iArgument1].m_krgAttacker[8].iScore, pMob[iArgument1].m_krgAttacker[9].iID, pMob[iArgument1].m_krgAttacker[9].iScore, pMob[iArgument1].m_krgAttacker[10].iID, pMob[iArgument1].m_krgAttacker[10].iScore, pMob[iArgument1].m_krgAttacker[11].iID, pMob[iArgument1].m_krgAttacker[11].iScore
, pMob[iArgument1].m_krgAttacker[12].iID, pMob[iArgument1].m_krgAttacker[12].iScore, pMob[iArgument1].m_krgAttacker[13].iID, pMob[iArgument1].m_krgAttacker[13].iScore, pMob[iArgument1].m_krgAttacker[14].iID, pMob[iArgument1].m_krgAttacker[14].iScore, pMob[iArgument1].m_krgAttacker[15].iID, pMob[iArgument1].m_krgAttacker[15].iScore
, pMob[iArgument1].m_iCantTraceTarget, pMob[iArgument1].m_iAttackCount, pMob[iArgument1].m_iTraceCount, pMob[iArgument1].m_iTotalTraceCount, pMob[iArgument1].m_eStatus, (int)pMob[iArgument1].m_iAffections, pMob[iArgument1].m_iCastCount
, CurrentTime, pMob[iArgument1].m_uiActionLock, pMob[iArgument1].m_kLastTime.uiSelectTarget
, pMob[iArgument1].MOB.byLevel, pMob[iArgument1].m_byClan, pMob[iArgument1].MOB.byClass1, pMob[iArgument1].m_iBlockedCell
, pMob[iArgument1].m_kSight.sPeace, pMob[iArgument1].m_kSight.sCombat, pMob[iArgument1].m_iMoveSpeed
, pMob[iArgument1].MOB.nHP, pMob[iArgument1].m_irgHPRecovery[0], pMob[iArgument1].m_kCombatFactors.iAttackRate, pMob[iArgument1].m_kCombatFactors.iDodgeRate, pMob[iArgument1].m_kCombatFactors.iDefense
, pMob[iArgument1].m_kCombatFactors.irgResist[eRst_Fire], pMob[iArgument1].m_kCombatFactors.irgResist[eRst_Cold], pMob[iArgument1].m_kCombatFactors.irgResist[eRst_Lightning], pMob[iArgument1].m_kCombatFactors.irgResist[eRst_Poison], pMob[iArgument1].m_iImmunity
, pMob[iArgument1].m_krgSkill[0].iIndex-500, pMob[iArgument1].m_krgSkill[1].iIndex-500, pMob[iArgument1].m_krgSkill[2].iIndex-500, pMob[iArgument1].m_krgSkill[3].iIndex-500, pMob[iArgument1].m_krgSkill[4].iIndex-500, pMob[iArgument1].m_iSkillCharged

);
			WriteLog( chBuf, ".\\monster_log\\[Log]LoadMonsterData.txt" );
			sprintf( szResult, "%s> The system write the specific monster data to the log file sussessfully.", a_pCmd);
		}
	}
	else if( !strcmp( szCmd, "/PrintMonsterMode" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			sprintf( szResult, "Monster(%d) Mode:%d",  iArgument1, pMob[iArgument1].Mode );
		}
	}
	else if( !strcmp( szCmd, "/checkmonster" ) )
	{
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			sprintf( szResult, "%s> ",  a_pCmd );
			int iCount = 0;
			for( int i = MAX_USER; i < MAX_MOB; ++i )
			{
				if( iArgument1 == pMob[i].MOB.snTribe )
				{
					char szMonsterID[128] = { 0,0,0, };
					sprintf( szMonsterID, "%d: %d, ",  iCount, i );
					strcat( szResult, szMonsterID );
					++iCount;				
				}
				if( 20 < iCount ) break;
			}

			if( 0 == iCount ) sprintf( szResult, "Monster(%d) don't live this zone",  iArgument1 );
		}
		else		
		{
			sprintf( szResult, "%s> invalid the monster tribe. tribe:2001~2999", a_pCmd );   		    
		}
	}
	else if( !strcmp( szCmd, "/ResetKalaSystem" ) )
	{
		// 운반하고 있는 모든 kala-core 제거
		// 땅에 떨어져 있는 모든 kala-core 제거
		// altar에 있는 모든 kala monster 제거
		// rewarder NPC 중립화
		// 차투랑가 portal NPC 중립화
		// 기록 파일 갱신
	}
	else if( !strcmp( szCmd, "/printkalacoreinfo" ) )
	{
		if( SERVER_KRUMA_HIGH != iZoneID ) return;
		g_kKalaSystem.DropKalaCoreInPC();
		g_kKalaSystem.CheckCountNRecovery();
		g_kKalaSystem.PrintScreen( szResult );
		MoveKalaRewarder();		
	}
	else if( !strcmp( szCmd, "/removekalacore" ) )
	{
		int iTarget = iArgument1;
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{
			RemoveKalaCoreInInventory( iTarget );
			sprintf( szResult, "%s> the command is completed successfully.", a_pCmd );
		}
		else
		{
			sprintf( szResult, "%s> invalid ID.", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/dropkalacore" ) )
	{	
		return;
		if( SERVER_KRUMA_HIGH != iZoneID ) return;
		if( (eKalaCore_Brahma == iArgument1) || (eKalaCore_Vishnu == iArgument1) || (eKalaCore_Siva == iArgument1) ) 
		{
			STRUCT_ITEM kItem;
			memset( &kItem, 0, sizeof(kItem) );
			kItem.snIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1;
			kItem.snDurability = eDur_Indestructible;
			kItem.byCount = 1;

			int iCoordX, iCoordY;
			iCoordX = pMob[a_iHandle].TargetX-1;
			iCoordY = pMob[a_iHandle].TargetY-1;
			CreateItem( iCoordX, iCoordY, &kItem, 0, 0, 0, 0 );

			{
				//SYSTEMTIME st;
				//GetLocalTime( &st );
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, ">>> GM %s drop a kala-core(%d) at L(%d,%d) - [%dmm%ddd %dhh%dmi%dss]\r\n", pMob[a_iHandle].MOB.szName, iArgument1, pMob[a_iHandle].TargetX-1, pMob[a_iHandle].TargetY-1, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_KalaSystem] );
			}
			NotifyRvRStatus();
		}
		else		
		{
			sprintf( szResult, "%s> invalid kala-core ID. id: brahma:8051, vishnu:8052, siva:8053 ", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/KickOutAllPlayers" ) )
	{
		for( int i = 1; i < MAX_USER; ++i )
		{
			if( USER_PLAY != pUser[i].Mode ) continue;
			ReturnPCToSaveZone( i );
		}

		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/CountMonster" ) )
	{
		if( eTNClan_BrahmaSoldier <= iArgument1 && eTNClan_SivaSoldier >= iArgument1 )
		{
			int iCount = 0;
			for( int i = MAX_USER; i < MAX_MOB; ++i )
			{
				if( iArgument1 == pMob[i].m_byClan )
				{
					if( 0 < pMob[i].MOB.nHP ) ++iCount;
				}
			}

			sprintf( szResult, "%s> count:%d ", a_pCmd, iCount );
		}
		else sprintf( szResult, "%s> Invalid ID. brahma:5, vishnu:6, siva:7 ", a_pCmd );
	}
	else if( !strcmp( szCmd, "/KillMonsterAll" ) )
	{
		for( int i = MAX_USER; i < MAX_MOB; ++i )
		{
			if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue;
			if( eTNCls_Event == pMob[i].MOB.byClass1 ) continue;

			KillMonster( i );
		}

		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/KillClanMonster" ) )
	{
		if( (eTNClan_BrahmaSoldier <= iArgument1 && eTNClan_SivaSoldier >= iArgument1) || (eTNClan_Stronghold1 <= iArgument1 && eTNClan_Stronghold4 >= iArgument1) )
		{
			for( int i = MAX_USER; i < MAX_MOB; ++i )
			{
				if( eTNCls_NPC == pMob[i].MOB.byClass1 ) continue;
				if( eTNCls_Event == pMob[i].MOB.byClass1 ) continue;

				if( iArgument1 == pMob[i].m_byClan )
				{
					KillMonster( i );
				}
			}

			sprintf( szResult, "%s> successful", a_pCmd );
		}
		else sprintf( szResult, "%s> Invalid ID. brahma:5, vishnu:6, siva:7 ", a_pCmd );
	}
	else if( !strcmp( szCmd, "/killkala" ) )
	{
		/*
		iArgument1 = atoi( szArguments );
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			if( eKala_Brahma == pMob[iArgument1].MOB.snTribe || eKala_Vishnu == pMob[iArgument1].MOB.snTribe || eKala_Siva == pMob[iArgument1].MOB.snTribe )
			{
				KillMonster( iArgument1 );
				//MoveKalaRewarder();

				int iAltarIndex = 0;
				for(; iAltarIndex < eKalaAltar_MaxCount; ++iAltarIndex )
				{ // 칼라 제단에 위치하고 있는, ...
					int iMobHandle = g_irgKalaAltar[iAltarIndex];
					if( MAX_USER <= iMobHandle && MAX_MOB > iMobHandle )
					{
						if(iArgument1 == iMobHandle )
						{
							g_irgKalaAltar[iAltarIndex] = 0;
							break;
						}
					}
				}

				{
					SYSTEMTIME st;
					GetLocalTime( &st );
					char chBuf[512] = { 0,0,0, };
					sprintf( chBuf, "GM destroied the kala(%d) at altar(%d) - [%dmm%ddd %dhh%dmi%dss]\r\n", pMob[iArgument1].MOB.snTribe, iAltarIndex, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond );
					WriteLog( chBuf, g_szrgLogFileName[eLogFileName_KalaSystem] );
				}
			}
			else sprintf( szResult, "%s> %d is not the kala.", a_pCmd, iArgument1 );   		    
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );   		    
		}
		*/
	}
	else if( !strcmp( szCmd, "/방향" ) )
	{ // mob id, direction(new)
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			int iMob = iArgument1;
			int iOldDir = pMob[iMob].m_iDirection;
			pMob[iMob].m_iDirection = iArgument2;
			S_SCP_INIT_OTHER_MOB sm;
			GetCreateMob( iMob, &sm );
			GridMulticast( pMob[iMob].TargetX, pMob[iMob].TargetY, (MSG_STANDARD*)&sm, 0, 100 );
			
			sprintf( szResult, "%s> Mob:%d, Dir:%d->%d", a_pCmd, iMob, iOldDir, pMob[iMob].m_iDirection );
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );
		}
	}
	else if( !strcmp( szCmd, "/sp" ) || !strcmp( szCmd, "/말" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].DeliverComment( &a_pCmd[9] );
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );
		}
	}
	else if( !strcmp( szCmd, "/TriggerEvent" ) )		// event ID, NPC ID
	{
		if( 0 < a_iHandle && MAX_USER > a_iHandle )
			TriggerEvent( a_iHandle, iArgument1, pMob[a_iHandle].TargetX, pMob[a_iHandle].TargetY, iArgument2, 100 );
		else TriggerEvent( 0, iArgument1, 0, 0, iArgument2, 101 );	    

		sprintf( szResult, "%s> successful~ ", a_pCmd  );
	}
	else if( !strcmp( szCmd, "/attack" ) || !strcmp( szCmd, "/공격" ) )		// id, target
	{
		if( ( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 ) && ( 0 < iArgument2 && MAX_MOB > iArgument2 ) )
		{
			pMob[iArgument1].m_kLastTime.uiSelectTarget = CurrentTime + 10000;
			pMob[iArgument1].CurrentTarget = iArgument2;
			pMob[iArgument1].OnUnderAttack( iArgument2 );
		}
		else
		{
			sprintf( szResult, "%s> invalid the monster ID(%d) or invalid target handle(%d).", a_pCmd, iArgument1, iArgument2 );   		    
		}
	}
	else if( !strcmp( szCmd, "/attack2" ) || !strcmp( szCmd, "/공격2" ) )
	{
		if( 0 >= a_iHandle || MAX_USER <= a_iHandle) return;
		if( MAX_USER <= iArgument1 && MAX_MOB >= iArgument1 )
		{
			int TargetX = pMob[a_iHandle].TargetX;
			int TargetY = pMob[a_iHandle].TargetY;
			int iMaxIndex = g_pDetectEnemyRadius[eRds_MaxDetectEnemy];
			int x, y;
			for( int i = 0; i < iMaxIndex; ++i )
			{
				x = TargetX + g_pDetectEnemyTable[i][0];
				y = TargetY + g_pDetectEnemyTable[i][1];
				if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
				int tmob = pMobGrid[y][x];  if ( 0 == tmob ) continue;
				if	(pMob[tmob].MOB.nHP <=0) continue;
				if  (pMob[tmob].Mode==MOB_EMPTY)	continue;
				pMob[tmob].m_kLastTime.uiSelectTarget = CurrentTime + 10000;
				pMob[tmob].CurrentTarget = iArgument1;
				pMob[tmob].OnUnderAttack( iArgument1 );
			}
		}
		else
		{
			sprintf( szResult, "%s> Invalid target handle(%d).", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/killmonster" ) || !strcmp( szCmd, "/킬몬" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			if( eKala_Brahma == pMob[iArgument1].MOB.snTribe || eKala_Vishnu == pMob[iArgument1].MOB.snTribe || eKala_Siva == pMob[iArgument1].MOB.snTribe )
			{
				sprintf( szResult, "%s> can't kill the kala!!! use /killkala command.", a_pCmd );  
			}
			else
			{
				KillMonster( iArgument1 );
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );   		    
		}
	}
	else if( !strcmp( szCmd, "/bufnpc" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			TNEFFECT kEffect;
			kEffect.iID = eTNAfn_HealPlus;
			kEffect.iDuration = 1800000;
			kEffect.iParam1 = iArgument2;
			pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle );

			TNEFFECT kEffect2;
			kEffect2.iID = eTNAfn_RecoverTPPlus;
			kEffect2.iDuration = 1800000;
			kEffect2.iParam1 = iArgument3;
			pMob[iArgument1].AddEffect( kEffect2, a_iHandle, a_iHandle );

			TNEFFECT kEffect3;
			kEffect3.iID = eTNAfn_MaxHPPlus2;
			kEffect3.iDuration = 1800000;
			kEffect3.iParam1 = iArgument4;
			pMob[iArgument1].AddEffect( kEffect3, a_iHandle, a_iHandle );

			TNEFFECT kEffect4;
			kEffect4.iID = eTNAfn_MaxTPPlus2;
			kEffect4.iDuration = 1800000;
			kEffect4.iParam1 = iArgument5;
			pMob[iArgument1].AddEffect( kEffect4, a_iHandle, a_iHandle );

		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d", a_pCmd, 0, MAX_USER );   		    
		}
	}
	else if( !strcmp( szCmd, "/DebugDur" ) )
	{
		iArgument2 *= 60000; // 1분단위
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument3 ) )
			{
				pMob[iArgument1].m_iDebugFlag2 = 0;
			}
			else 
			{
				pMob[iArgument1].m_iDebugFlag2 = 1;
				sprintf( szResult, "%s> write log for ID(%d), dur:10 minutes.", a_pCmd, iArgument1 );				
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/Log" ) || !strcmp( szCmd, "/log" ) ) // /log 15 => 10분동안 log를 남긴다, /log 15 60 => 60분동안 log를 남긴다.
	{
		iArgument2 *= 60000; // 1분단위
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument3 ) )
			{
				pMob[iArgument1].RemoveEffect( eTNAfn_Log );
			}
			else 
			{
				DumpMobile( iArgument1 );
				if( 0 >= iArgument2 || 3600000 < iArgument2 ) iArgument2 = 600000; // 10분에서 1시간
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_Log;
				kEffect.iDuration = iArgument2;
				kEffect.iParam1 = 0;
				kEffect.iParam2 = 0;
				pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle );
				sprintf( szResult, "%s> write log for ID(%d), dur:10 minutes.", a_pCmd, iArgument1 );				
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeIntervalHackCount" ) ) //
	{ // obstacle, character
		g_irgSetting[eCnst_SkillCastIntervalHack] = iArgument1;

		sprintf( szResult, "%s> Hack interval for casting a skill, limit count:%d", a_pCmd, g_irgSetting[eCnst_SkillCastIntervalHack] );
	}
	else if( !strcmp( szCmd, "/ChangeHeightSetting" ) ) //
	{ // obstacle, character
		g_irgSetting[eCnst_ObstacleHeight] = iArgument1;
		g_irgSetting[eCnst_CharacterHeight] = iArgument2;

		sprintf( szResult, "%s> Height > Obstacle:%d, Character:%d", a_pCmd, g_irgSetting[eCnst_ObstacleHeight], g_irgSetting[eCnst_CharacterHeight] );
	}
	else if( !strcmp( szCmd, "/logx" ) ) // /log 15 => 10분동안 log를 남긴다, /log 15 60 => 60분동안 log를 남긴다.
	{// mob handle, debug type, duration(10분), on/off(on)
		int iDebugType = eTNDbg_None;
		iArgument3 *= 60000; // 1분단위
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument4 ) )
			{
				pMob[iArgument1].RemoveEffect( eTNAfn_Debug );
			}
			else 
			{
				DumpMobile( iArgument1 );
				if( 1 == iArgument2 ) iDebugType = eTNDbg_Combat;
				else if( 2 == iArgument2 ) iDebugType = eTNDbg_Pet;
				else if( 3 == iArgument2 ) iDebugType = eTNDbg_Immunity;
				else if( 4 == iArgument2 ) iDebugType = eTNDbg_Affection;

				if( 0 >= iArgument3 || 3600000 < iArgument3 ) iArgument3 = 600000; // 10분에서 1시간
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_Debug;
				kEffect.iDuration = iArgument3;
				kEffect.iParam1 = iDebugType;
				kEffect.iParam2 = 0;
				pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle );
				sprintf( szResult, "%s> debug ID(%d), debug type:%d, dur:10 minutes.", a_pCmd, iArgument1, iArgument2 );				
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/logimmu" ) ) // /log 15 => 10분동안 log를 남긴다, /log 15 60 => 60분동안 log를 남긴다.
	{// mob hndl
		iArgument2 *= 60000; // 1분단위
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			if( !strcmp( "off", szArgument3 ) )
			{
				pMob[iArgument1].RemoveEffect( eTNAfn_LogImmu );
			}
			else 
			{
				if( 0 >= iArgument2 || 3600000 < iArgument2 ) iArgument2 = 600000; // 10분 설정
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_LogImmu;
				kEffect.iDuration = iArgument2;
				kEffect.iParam1 = 0;
				kEffect.iParam2 = 0;
				pMob[iArgument1].AddEffect( kEffect, a_iHandle, a_iHandle );
				sprintf( szResult, "%s> write log immunity for ID(%d), dur:10 minutes. Immunity:%d(%h)", a_pCmd, iArgument1, pMob[iArgument1].m_iImmunity, pMob[iArgument1].m_iImmunity );
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/ResetStat" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetStat();
		}
	}
	else if( !strcmp( szCmd, "/ResetSkill" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetSkill();
		}
	}
	else if( !strcmp( szCmd, "/SwitchOffEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_Off;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration );
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/SwitchOnEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_On;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration );
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/eventlog" ) )
	{
		if( !strcmp( "on", szArgument1 ) ) g_iSwitch = g_iSwitch | eTNSwitch_EventLog;
		else
		{
			if( eTNSwitch_EventLog & g_iSwitch ) g_iSwitch = eTNSwitch_EventLog ^ eTNSwitch_EventLog;
		}
		sprintf( szResult, "%s> successful~, g_iSwitch:%d", a_pCmd, (eTNSwitch_EventLog & g_iSwitch) );
	}
	else if( !strcmp( szCmd, "/contactnpclog" ) )
	{
		if( !strcmp( "on", szArgument1 ) ) g_iSwitch = g_iSwitch | eTNSwitch_ContactNPC;
		else
		{
			if( eTNSwitch_ContactNPC & g_iSwitch ) g_iSwitch = g_iSwitch ^ eTNSwitch_ContactNPC;
		}

		sprintf( szResult, "%s> successful~, g_iSwitch:%d", a_pCmd, (eTNSwitch_ContactNPC & g_iSwitch) );
	}
	else if( !strcmp( szCmd, "/PopMonster" ) )
	{
		/*
		iArgument1 = atoi( szArguments );
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].m_kLastTime.uiKilled = 0; 
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );   		    
		}
		*/
	}
	else if( !strcmp( szCmd, "/recoverkalasystem" ) )
	{
		if( !strcmp( "on", szArgument1 ) ) g_iSwitch = g_iSwitch | eTNSwitch_RecvKalaSystem;
		else g_iSwitch = g_iSwitch ^ eTNSwitch_RecvKalaSystem;
		sprintf( szResult, "%s> successful~, g_iSwitch:%d", a_pCmd, (eTNSwitch_RecvKalaSystem & g_iSwitch) );
	}
	else if( !strcmp( szCmd, "/DecPrana" ) ) // ok
	{
		if( !strcmp( "off", szArgument1 ) ) g_bDecPrana = true;
		else g_bDecPrana = false;
		sprintf( szResult, "%s> %d(if the value is equal to 1, the system don't decrease prana when PC is killed.)", a_pCmd, g_bDecPrana );
/*
	    iArgument1 = atoi( szArguments );
		if( !strcmp( "off", szArguments ) ) g_iSwitch = g_iSwitch | eTNSwitch_DecPrana; //g_bDecPrana = true;
		else g_iSwitch = g_iSwitch ^ eTNSwitch_DecPrana; // on
		sprintf( szResult, "%s> %d(1이 포함되어 있으면 스위치는 off, 죽어도 프라나가 줄지 않는다.)", a_pCmd, g_iSwitch );
*/
	}
	/*
	else if( !strcmp( szCmd, "/ResetSkill" ) ) // ok
	{
	    iArgument1 = atoi( szArguments );
		if( !strcmp( "off", szArguments ) ) g_iSwitch = g_iSwitch | eTNSwitch_ResetSkill; // off
		else g_iSwitch = g_iSwitch ^ eTNSwitch_ResetSkill;		 // on
		sprintf( szResult, "%s> %d(2가 포함되어 있으면, 스위치는 off, 스킬리셋이 동작하지 않는다.)", a_pCmd, g_iSwitch );
	}
	*/
/*
	else if( !strcmp( szCmd, "/cc" ) )
	{
		iArgument1 = atoi( szArguments ); // index
		if( 0 < iArgument1 && eTNSpch_MaxCommentCount > iArgument1 )
		{
			memcpy( g_szrgComment[iArgument1], &a_pCmd[8], 100 );
            sprintf( szResult, "%s> [%d] %s", a_pCmd, iArgument1, g_szrgComment[iArgument1] );
		}
		else
		{
			sprintf( szResult, "%s> index:%d ", a_pCmd, iArgument1 );
		}
	}		   szResult
*/
	else if( !strcmp( szCmd, "/PrintRwdCorrect" ) )
	{
		sprintf( szResult, "%s> Prana:%f, Gold:%f, BP:%f", a_pCmd, g_dRwdPranaCorrect, g_dRwdGoldCorrect, g_dRwdBramanCorrect );
	}
	else if( !strcmp( szCmd, "/ChangeRwdCorrect" ) ) // prana, gold, braman
	{
		ChangeRwdCorrect( iArgument1, iArgument2, iArgument3 ); // prana, gold, BP

		sprintf( szResult, "%s> Prana:%f, Gold:%f, BP:%f", a_pCmd, g_dRwdPranaCorrect, g_dRwdGoldCorrect, g_dRwdBramanCorrect );
	}
	else if( !strcmp( szCmd, "/kickouto" ) )
	{
		TriggerEvent( 0, 30, 0, 0, 0, 102 );
		sprintf( szResult, "%s> successful~ ", a_pCmd  );
	}
	else if( !strcmp( szCmd, "/kickoutx" ) )
	{
		TriggerEvent( 0, 31, 0, 0, 0, 103 );
		sprintf( szResult, "%s> successful~ ", a_pCmd  );
	}
	else if( !strcmp( szCmd, "/RefiningRate" ) )		//	FORMAT ===> $REFINING UP,DOWN COUNT
	{	
		if(!strcmp(szArgument1,"Up"))
		{	g_ItemRefineGMScale += iArgument2;
			sprintf( szResult, "%s> Successfully", a_pCmd ); 
		}
		else if(!strcmp(szArgument1,"Down"))
		{	g_ItemRefineGMScale -= iArgument2;
			sprintf( szResult, "%s> Successfully", a_pCmd ); 
		}
		else if(!strcmp(szArgument1,"Search"))
		{	if(iArgument2>0 && iArgument2<100)
			{	char chBuf[256]={0,};
				if(g_RefineTable.GetValue2(iArgument2)>0) sprintf(szResult, "RefiningRate %d[Percent] will be succeed..", iArgument2);
				else sprintf(szResult, "RefiningRate %d[Percent] will be fail..", iArgument2);
			}	else
			{	char chBuf[256]={0,};
				sprintf(szResult, "RefiningRate's up by GM : %d", g_ItemRefineGMScale);
			}
		}
	}
	else if( !strcmp( szCmd, "/Money" ) )
	{
		pMob[a_iHandle].IncGold(iArgument1);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/Prana" ) )
	{
		int nID = GetMOBID(szArgument1);
		if( (nID<=0) || (nID>=MAX_USER) ) return;
		pMob[nID].AcquirePrana(iArgument2);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/PreventWhisper" ) )
	{	
		MSG_Status sm; sm.wType = _MSG_Status;
		sm.nID = a_iHandle;
		if(!strcmp(szArgument1,"ON") || !strcmp(szArgument1,"on"))
		{	pMob[a_iHandle].MOB.byStatus |= 0x01;
			sm.byStatus = pMob[a_iHandle].MOB.byStatus;
			if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
			{	Log("err charstatus DB-SEND",pUser[a_iHandle].AccountName,pUser[a_iHandle].IP);
			}
		}
		else if(!strcmp(szArgument1,"OFF") || !strcmp(szArgument1,"off"))
		{	pMob[a_iHandle].MOB.byStatus &= 0xFE;
			sm.byStatus = pMob[a_iHandle].MOB.byStatus;
			if(!DBServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
			{	Log("err charstatus DB-SEND",pUser[a_iHandle].AccountName,pUser[a_iHandle].IP);
			}
		}
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/LogDump" ) )
	{
		fflush(fLogFile);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/MSGLogDump" ) )
	{
		MSG_ServerCommand sm; ZeroMemory(&sm, sizeof(sm));
		sm.wType = _MSG_ServerCommand; sm.byCommandType=eCommandDump;
		if(!MSGServerSocket.SendOneMessage((char*)&sm,sizeof(sm)))
		{	Log("err charstatus MSG-SEND",pUser[a_iHandle].AccountName,pUser[a_iHandle].IP);
		}
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/Exchange" ) )						//	For Test(in china)
	{
		_AUTH_GAME2 bm; ZeroMemory(&bm, sizeof(bm));
		bm.Packet_result = 0; bm.Time_Exchanged = 340;
		bm.ItemNo = 0;
		SendBilling3(a_iHandle, &bm, _Msg_BillTimeEx);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/DropItm" ) )
	{
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			STRUCT_ITEM kItem;
			memset( &kItem, 0, sizeof(kItem) );
			kItem.snIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1;
			kItem.snDurability = 10;
			kItem.byCount = 1;
			kItem.byRefineLevel = 9;

			int iCoordX, iCoordY;
			iCoordX = pMob[a_iHandle].TargetX-1;
			iCoordY = pMob[a_iHandle].TargetY-1;

			if( 0 < a_iHandle && MAX_USER > a_iHandle )
				CreateItem( iCoordX, iCoordY, &kItem, 0, 0, 0, 0 );
		}
		else
		{
			sprintf( szResult, "%s> invalid item ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/Card" ) )
	{
		_AUTH_GAME2 bm; ZeroMemory(&bm, sizeof(bm));				//	For Test(in china)
		bm.Packet_result = 0;
		strncpy( bm.cardNumber, "23434634456353241", 20 );
		strncpy( bm.cardPassword, "33453638584785678567857812345", 20 );
		bm.cardNumber[18]=0; bm.cardNumber[19]=0;
		bm.cardPassword[18]=0; bm.cardPassword[19]=0;
		SendBilling3(a_iHandle, &bm, _Msg_BillCard);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/Dress" ) )
	{
		_AUTH_GAME2 bm; ZeroMemory(&bm, sizeof(bm)); 
		bm.Packet_result = 0; bm.article_number = 2342;
		bm.Dressed = 1;
		SendBilling3(a_iHandle, &bm, _Msg_BillDress);
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/Connect" ) )
	{
		if(!strcmp(szArgument1,"BILL"))
		{	int * pip = (int*)LocalIP1;
			if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP2;			//	필리핀은 빌링을 인라인사용한다
			int ret = BillServerSocket.ConnectBillServer(BillServerAddress,BillServerPort ,*pip, WSA_READBILL, hWndMain);
			if	(ret==0)
			{	Log("err Reconnect BILL Server(x2) fail.","-system",0);
				BILLING=0;//무료모드로 계속한다.
			}	else
			{	_AUTH_GAME sm;memset(&sm,0,sizeof(sm));
				SendBilling2(&sm,4);
				sprintf( szResult, "%s> Successfully", a_pCmd ); 
			}
		}
		else if(!strcmp(szArgument1,"MSG"))
		{	int * pip = (int*)LocalIP2;
			if(g_eCountryID == eCountryPhilippines) pip = (int*)LocalIP1;		//	필리핀은 MSG Public사용
			int ret = MSGServerSocket.ConnectServer(MSGServerAddress,MSGServerPort ,*pip, WSA_READMSG, hWndMain);
			if	(ret==0)
			{	Log("err Reconnect MSG Server(x2) fail.","-system",0);
			}
		}
	}
	else if( !strcmp( szCmd, "/View" ) )
	{
		int nID = GetMOBID(szArgument1);
		if(nID<0 || nID>=MAX_USER)
		{	sprintf(szResult, g_pMessageStringTable[_Not_Find_Others]);
			return;
		}

		int nGuildIndex = pUser[nID].nGuildIndex;
		sprintf(szResult, "Char:%s, Level:%d, Tribe:%d, MaxHP:d, CurHP:%d, Guild:%s, Trim:%d, byGMStatus:%d, Karma:%d, Class1:%d, Class2:%d, snX:%d, snZ:%d",
			szArgument1, pMob[nID].MOB.byLevel, pMob[nID].MOB.snTribe, pMob[nID].m_iMaxHP, pMob[nID].MOB.nHP, pGuild[nGuildIndex].GUILD.GuildName, pMob[nID].MOB.byTrimuriti, pMob[nID].MOB.byGMStatus,
			pMob[nID].MOB.snKarma, pMob[nID].MOB.byClass1, pMob[nID].MOB.byClass2, pMob[nID].TargetX, pMob[nID].TargetY);
	}
	else if( !strcmp( szCmd, "/IWantIt" ) )
	{
		g_GameEvent.m_IWantIt.GetRankUser(szResult);
		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/Report" ) )
	{
		if(!strcmp(szArgument1,"Transparency"))		//	크루마에서 칼리아 입장 오브잭트가 생겻다고 신고 들어올 경우
		{
			int nID = iArgument2;
			if(g_bIsKaliaOpend) return;				//	칼리아던전이 오픈시간이면 당연히 보여야 한다.
			if(nID>MAX_USER && nID<MAX_MOB)
			{
				sprintf(temp, "dbg GateMob:[%d] Discoverd at pos(%d, %d), and mob is at pos(%d, %d)",
					nID, pMob[a_iHandle].TargetX, pMob[a_iHandle].TargetY, pMob[nID].TargetX, pMob[nID].TargetY);
			}
			else
			{
				sprintf(temp, "dbg unkowned modid : %d", nID);
			}

			Log(temp, pUser[a_iHandle].AccountName, pUser[a_iHandle].IP);
			sprintf( szResult, "%s> Successfully", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/yutbet" ) )
	{
		int iPos = iArgument1;
		int iMoney = iArgument2;

		g_Yut.HT_wUserBet(pMob[a_iHandle].MOB.szName, (WORD)iPos, iMoney);
	}
	else if( !strcmp( szCmd, "/yutmoney" ) )
	{
		int iMoney = iArgument1;
		g_Yut.HT_SetYutMoney(pMob[a_iHandle].MOB.szName, iMoney);
	}
	else if( !strcmp( szCmd, "/공성날짜예약상황확인" ) )
	{
		sprintf( szResult, "%s> Friday20HH:%d, Friday22HH:%d, Saturday20HH:%d, Satuday22HH:%d, Sunday20HH:%d"
			, a_pCmd
			, g_krgEventList[100].iDuration, g_krgEventList[101].iDuration, g_krgEventList[102].iDuration, g_krgEventList[103].iDuration, g_krgEventList[104].iDuration
			);
	}
	else if( !strcmp( szCmd, "/공성날짜결정" ) )
	{
		// 성주인지 확인 단계 필요
		int iSelected = iArgument1;
		g_kSiege.SelectDate( iSelected, false );

		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/공성상태" ) )
	{
		sprintf( szResult, "%s> ", a_pCmd );
	}
	else if( !strcmp( szCmd, "/dump공성엔트리" ) )
	{
		g_kSiege.SaveData( szArgument1 );
		sprintf( szResult, "%s> completed successfully.", a_pCmd );
	}
	else if( !strcmp( szCmd, "/reload공성엔트리" ) )
	{
		g_kSiege.Init();
		g_kSiege.LoadData();
		sprintf( szResult, "%s> completed successfully.", a_pCmd );
	}
	else if( !strcmp( szCmd, "/ChangeClanForSiege" ) )
	{
		if( !g_kSiege.get_Started() ) return;

		#ifdef __TN_TOP_LOG__
		{
			char chBuf[512] = { 0,0,0, };
			sprintf(chBuf, "[eTNAct_ChangeClanForSiege] %dYY%dMM%dDD %2dHH%2dMI%2dSS> \r\n"
				, g_kSystemTime.wYear, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
				); 
			WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
		}
		#endif


		for( int i = 1; i < MAX_USER; ++i )
		{
			if( eTNClan_GM == pMob[i].m_byClan ) continue;
			//if( eTNClan_CastleOwner <= pMob[i].m_byClan && eTNClan_Siege4 >= pMob[i].m_byClan ) continue;
			if( USER_PLAY != pUser[i].Mode ) continue;

			byte byOld = pMob[i].m_byClan;

			int iFlag = g_kSiege.SearchEntry( pMob[i].MOB.nGuildID );
			if( -1 == iFlag ) pMob[i].m_byClan = eTNClan_Siege4;
			else pMob[i].m_byClan = iFlag;

			MSG_SET_ZONE_SETTINGS kZoneSettingMsg;
			kZoneSettingMsg.wType = MSG_SET_ZONE_SETTINGS_ID;
			kZoneSettingMsg.wPDULength = sizeof(MSG_SET_ZONE_SETTINGS)-sizeof(HEADER);
			kZoneSettingMsg.snSiege = 1; //g_kSiege.get_Started(); 공성종료
			pUser[i].cSock.AddMessage( (char*)&kZoneSettingMsg, sizeof(MSG_SET_ZONE_SETTINGS) );

			S_SCP_INIT_OTHER_MOB sm;
			GetCreateMob( i, &sm );
			GridMulticast( pMob[i].TargetX, pMob[i].TargetY, (MSG_STANDARD*)&sm, i);

			MSG_CHANGE_CLAN kMsg;
			kMsg.wType = MSG_CHANGE_CLAN_ID;
			kMsg.wPDULength = sizeof(MSG_CHANGE_CLAN)-sizeof(HEADER);
			kMsg.snKeyID = i;
			kMsg.byClan = pMob[i].m_byClan;
			pUser[i].cSock.AddMessage( (char*)&kMsg, sizeof(MSG_CHANGE_CLAN) );

			pUser[i].cSock.SendMessage();

			#ifdef __TN_TOP_LOG__
			{
				char chBuf[512] = { 0,0,0, };
				sprintf(chBuf, "[eTNAct_ChangeClanForSiege] PC(%d, Name:%s, Guild:%d), clan(now:%d, old:%d) \r\n"
					,i , pMob[i].MOB.szName, pMob[i].MOB.nGuildID
					, pMob[i].m_byClan, byOld
					); 
				WriteLog( chBuf, g_szrgLogFileName[eLogFileName_Castle] );
			}
			#endif
		}

		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/InsertToSiegeEntry" ) )
	{
		int iClanSlot = iArgument1;
		int iExpandedSlot = iArgument2;
		int iGuildID = iArgument3;

		g_kSiege.RegisterEntry( iGuildID, iClanSlot, iExpandedSlot, 1);
		g_kSiege.RefreshEntry();

		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/RemoveSiegeEntry" ) )
	{// guild ID
		int iGuildID = iArgument1;

		g_kSiege.RemoveEntry( iGuildID );
		g_kSiege.RefreshEntry();

		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/RefreshEntry" ) )
	{
		g_kSiege.RefreshEntry();
		sprintf( szResult, "%s> successful", a_pCmd );
	}
	else if( !strcmp( szCmd, "/공성신청" ) )
	{// PC handle clanSlot expandSlot]
		// NPC와의 거리 검사가 있어야 한다.
		if( (0 < iArgument1 && MAX_USER > iArgument1) || g_kSiege.get_Started() )
		{			
			bool bBreak = false;
			if( 0 == iArgument2 ) if( TNSiege::eApplyFee_Defense > pMob[iArgument1].get_Gold() ) bBreak = true;
			else if( 1 == iArgument2 ) if( TNSiege::eApplyFee_Siege1 > pMob[iArgument1].get_Gold() ) bBreak = true;
			else if( 2 == iArgument2 ) if( TNSiege::eApplyFee_Siege2 > pMob[iArgument1].get_Gold() ) bBreak = true;
			else if( 3 == iArgument2 ) if( TNSiege::eApplyFee_Siege3 > pMob[iArgument1].get_Gold() ) bBreak = true;

			if( bBreak )
			{// 돈이 부족하다는 메시지				
				SendClientMessage( iArgument1, g_pMessageStringTable[_HaveNotEnoughGold] );
				return;
			}

			char szNofity[512] = { 0,0,0, };
			int iGuildID = pMob[iArgument1].MOB.nGuildID;
			int iGuildIndex = pUser[iArgument1].nGuildIndex;

			int iRes = g_kSiege.RegisterEntry( iGuildID, iArgument2, iArgument3, iArgument1 ); // guild ID, clan slot, expand slot, applier
			if( iRes )
			{
				if( eTNRes_AlreadyRegisteredInSiegeEntry == iRes ) sprintf( szResult, "%s> 이미 등록되어 있음", a_pCmd );	
				else if( eTNRes_ExpiryOftheTerm == iRes ) sprintf( szResult, "%s> 공성 신청 기간이 마감되었음", a_pCmd );	
				else if( eTNRes_Failed == iRes ) sprintf( szResult, "%s> 입력 오류", a_pCmd );	
			}
			else
			{
				sprintf( szResult, "%s> 공성전 등록 완료1", a_pCmd );				
				sprintf( szNofity, g_pMessageStringTable[_CompletedToApplySiege], pGuild[iGuildIndex].GUILD.GuildName );
				SendClientMessage( iArgument1, szNofity );
			}

			int iAllyGuildID = pGuild[iGuildIndex].nAlliedID;

			iRes = g_kSiege.RegisterEntry( iAllyGuildID, iArgument2, iArgument3+1, iArgument1 );
			if( iRes )
			{
				if( eTNRes_AlreadyRegisteredInSiegeEntry == iRes ) sprintf( szResult, "%s> 연합길드(%d)가 이미 등록되어 있음", a_pCmd, iAllyGuildID );	
				else if( eTNRes_ExpiryOftheTerm == iRes ) sprintf( szResult, "%s> 공성 신청 기간이 마감되었음", a_pCmd );	
				else if( eTNRes_Failed == iRes ) sprintf( szResult, "%s> 연합길드 관련 입력 오류", a_pCmd );	
			}
			else
			{
				sprintf( szResult, "%s> 공성전 등록 완료2", a_pCmd );
				sprintf( szNofity, g_pMessageStringTable[_CompletedToApplySiege], g_pMessageStringTable[_AllyGuild] );
				SendClientMessage( iArgument1, szNofity );
			}

			//g_kSiege.SaveData();
		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d. or 공성전 진행 중", a_pCmd, 0, MAX_USER );
		}
	}
	else if( !strcmp( szCmd, "/공성참가확인" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			int iRes = g_kSiege.SearchEntry( pMob[iArgument1].MOB.nGuildID );

			sprintf( szResult, "%s> clan:%d, guild:%d, successfully.", a_pCmd, iRes, pMob[iArgument1].MOB.nGuildID );

			//if( -1 == iRes ) SendClientMessage( iArgument1, g_pMessageStringTable[_YourGuildIsNotRegistered] );
			//else SendClientMessage( iArgument1, g_pMessageStringTable[_YourGuildIsRegistered] );
		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d", a_pCmd, 0, MAX_USER );
		}		
	}
	else if( !strcmp( szCmd, "/공성신청마감" ) )
	{
		g_kSiege.set_ExpiryOftheTerm( iArgument1 ); // 1이면 기간만료(공성신청불가), 0이면 기간중(공성신청가능)
		sprintf( szResult, "%s> completed successfully. => 1이면 기간만료, 0이면 신청가능 기간중", a_pCmd );
	}
	else if( !strcmp( szCmd, "/공성전설정" ) )
	{
		g_kSiege.set_Started( iArgument1 ); // 1이면 공성전 설정, 0이면 공성전 설정 해제
		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/클랜변경" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].m_byClan = iArgument2;

			MSG_CHANGE_TRIMURITI kChangeMsg;
			kChangeMsg.wType = MSG_CHANGE_TRIMURITI_ID;
			kChangeMsg.wPDULength = sizeof(MSG_CHANGE_TRIMURITI)-sizeof(HEADER);
			kChangeMsg.snKeyID = iArgument1;
			kChangeMsg.byTrimuriti = pMob[iArgument1].m_byClan;
			pUser[iArgument1].cSock.AddMessage( (char*)&kChangeMsg, sizeof(MSG_CHANGE_TRIMURITI) );	

			sprintf( szResult, "%s> Successfully", a_pCmd );
		}
		else
		{
			sprintf( szResult, "%s> invalid PC ID. id:%d~%d", a_pCmd, 0, MAX_USER );
		}	
	}
	else if( !strcmp( szCmd, "/공성상징물상태" ) )
	{
		g_kSiege.Print();
		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/공성엔트리확인" ) )
	{// iClanSlot, page
		MSG_SIEGE_ENTRY kEntryMsg;
		memset( &kEntryMsg, 0 , sizeof(kEntryMsg) );
		kEntryMsg.wType = MSG_SIEGE_ENTRY_ID;
		kEntryMsg.wPDULength = sizeof(MSG_SIEGE_ENTRY)-sizeof(HEADER);
		kEntryMsg.byDate = 1;
		kEntryMsg.byClanSlot = iArgument1;
		kEntryMsg.byPage = iArgument2;
		const int iElementCount = 8;
		int iExpandSlot = iArgument2 * iElementCount;
		int iEnd = iExpandSlot + iElementCount;
		int iIndex = 0;
		for(; iExpandSlot < iEnd; ++iExpandSlot )
		{
			TNGUILD_INFO kGuild;
			g_kSiege.GetEntry( iArgument1, iExpandSlot, kGuild );
			kEntryMsg.irgGuildID[iIndex] = kGuild.iID;
			kEntryMsg.dwrgGuildMark[iIndex] = kGuild.dwMark;
			strncpy( kEntryMsg.szrgGuildName[iIndex], kGuild.szName, SZGUILD_LENGTH );
			++iIndex;
		}
	}
	/*
	else if( !strcmp( szCmd, "/팻공격" ) )
	{
		int iMob = pMob[a_iHandle].m_irgSummoned[eTNCls2_Retainer];
		if( MAX_USER > iMob || MAX_MOB <= iMob ) return;

		pMob[iMob].ClearCurrentTarget();
		pMob[iMob].ClearAttacker( 0 );
		pMob[iMob].MemorizeAttacker( 0, 1, iArgument1 );
	}
	else if( !strcmp( szCmd, "/팻멈춤" ) )
	{
		int iMob = pMob[a_iHandle].m_irgSummoned[eTNCls2_Retainer];
		if( MAX_USER > iMob || MAX_MOB <= iMob ) return;

		pMob[iMob].ClearCurrentTarget();
		pMob[iMob].ClearAttacker( 0 );
		pMob[iMob].Mode = MOB_PEACE;
		pMob[iMob].OnFollow( a_iHandle );

		//pMob[iMob].MemorizeAttacker( 0, 1, iArgument1 );
	}
	else if( !strcmp( szCmd, "/스킬초기화" ) )
	{
		pMob[a_iHandle].ResetSkill();
		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/LearnSkill" ) )
	{
		pMob[a_iHandle].LearnSkill( iArgument1, iArgument2 ); //( short a_sSkillID, int a_iLevel )
		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/스탯변경" ) )
	{
		pMob[a_iHandle].MOB.sMind = iArgument4;
		pMob[a_iHandle].MOB.sHeart = iArgument3;
		pMob[a_iHandle].MOB.sMuscle = iArgument1;
		pMob[a_iHandle].MOB.sNerves = iArgument2;

		pMob[a_iHandle].UpdatePoints();
		pMob[a_iHandle].NotifyUpdateUIMsg();

		sprintf( szResult, "%s> Successfully", a_pCmd );
	}
	else if( !strcmp( szCmd, "/CastSkill" ) )
	{
		S_CSP_CAST_AREA_SKILL kMsg;
		memset( &kMsg, 0, sizeof(S_CSP_CAST_AREA_SKILL) );
		kMsg.snSkillID = iArgument1;
		kMsg.bySkillLevel = iArgument2; // monster 스킬들은 모두 1 level이다.

		kMsg.snCasterKeyID = (short)a_iHandle;				
		kMsg.snMapX = (short)pMob[a_iHandle].TargetX;
		kMsg.snMapZ = (short)pMob[a_iHandle].TargetY;
		kMsg.snRes = 1;
		kMsg.krgTarget[0].snKeyID = iArgument3;
		int iTargetCount = 1;
		if( 0 < iArgument4 )
		{
			kMsg.krgTarget[1].snKeyID = iArgument4;
			iTargetCount = 2;
		}

		int iRes = pMob[a_iHandle].CastSkill( &kMsg, 1 );
		sprintf( szResult, "%s> Res:%d Successfully", a_pCmd, iRes );
	}
	else if( !strcmp( szCmd, "/TestEffect" ) )
	{
		int iTarget = iArgument1;				// mobile handle
		if( 0 < iTarget && MAX_USER > iTarget )	//	동일지역내 상대방 존재
		{	
				TNEFFECT kEffect;
				kEffect.iID = iArgument2;
				kEffect.kFunc.iData = iArgument3;
				kEffect.iDuration = 30000;
				kEffect.iParam1 = iArgument4;
				kEffect.iParam2 = iArgument5;
				pMob[iTarget].AddEffect( kEffect, a_iHandle, a_iHandle );
				pMob[iTarget].BroadcastUpdateStatusMsg();
				pUser[iTarget].cSock.SendMessage();

				sprintf( szResult, "%s> Buffer %d effect to %d", a_pCmd, iArgument2, iArgument1 );
		}
		else
		{
		    sprintf( szResult, "%s>  invalid user ID", a_pCmd );
		}
	}
	*/


	strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
    pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));
}



void ControlSystem( int a_iHandle, char* a_pCmd, bool a_bCheckGM )
{	
    if( NULL == a_pCmd ) return;
    if( '/' != a_pCmd[0] ) return;

	#ifndef __TN_LOCAL_SERVER_SWITCH__
	if( 0 < a_iHandle && MAX_USER > a_iHandle )	if( a_bCheckGM && (eTNClan_GM != pMob[a_iHandle].m_byClan) ) return;
	#endif

    // 모든 command를 log로 남긴다. 시간 + 누가 + 메시지
    int iLength = strlen( a_pCmd );
    if( g_iCmdMaxLength < iLength ) return;
    
    char szCmd[256] = { 0,0,0, };
    char szArgument1[256] = { 0,0,0, };
    char szArgument2[256] = { 0,0,0, };
	char szArgument3[256] = { 0,0,0, };
	char szArgument4[256] = { 0,0,0, };
	char szArgument5[256] = { 0,0,0, };
	char szArgument6[256] = { 0,0,0, };
	char szArgument7[256] = { 0,0,0, };
    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0, iArgument6 = 0, iArgument7 = 0;
    
	sscanf( a_pCmd, "%s %s %s %s %s %s %s %s", szCmd, szArgument1, szArgument2, szArgument3, szArgument4, szArgument5, szArgument6, szArgument7  );
	iArgument1 = atoi( szArgument1 );
	iArgument2 = atoi( szArgument2 );
	iArgument3 = atoi( szArgument3 );
	iArgument4 = atoi( szArgument4 );
	iArgument5 = atoi( szArgument5 );   
	iArgument6 = atoi( szArgument6 );
	iArgument7 = atoi( szArgument7 );

    if( '/' != szCmd[0] ) return;

	S_SCP_RESP_WHISPER_CHAT kMsg; 
	kMsg.wType = SCP_RESP_WHISPER_CHAT;	
	kMsg.byResult = REPLY_ACK_OK;
	strncpy( kMsg.szName, ".", SZNAME_LENGTH );
	kMsg.byTextColor = 14; kMsg.byBgColor = 0; // 나중에 반전 색으로 바꾼다. 눈에 잘 띄게	
	    
    // g_iCmdMaxLength를 늘릴 수 있게 하는 command가 필요하다.
    // 몬스터 log 찍게하는 level도 조정할 수 있게 해야한다.
    // 중요한 monster는 누가 죽였고 어떤 reward를 줬는지 항상 log로 남겨야한다.(이런 형태에 맞게 log 출력부분 조정)
	#ifdef __TN_TOP_LOG__
	if( 0 <= a_iHandle && MAX_USER > a_iHandle )
	{
		//SYSTEMTIME st;
		//GetLocalTime( &st );
		char chBuf[512] = { 0,0,0, };
		sprintf(chBuf, "[%d월%d일 %d시%d분%d초] %s  %s \r\n", g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond, pMob[a_iHandle].MOB.szName, a_pCmd );
		WriteLog( chBuf, ".\\Event\\ControlSystem.txt" );
	}
	#endif    

  
    // switch/case 문을 테스트 해본다.
	char szResult[1024] = { 0,0,0, };
	strncpy( szResult, a_pCmd, iLength );
    

	if( !strcmp( szCmd, "/loadfix" ) )
	{
		FILE* fp;
		fp = fopen( "loadfix.txt", "rt" );
		if(NULL == fp )
		{
			sprintf( szResult, "%s> failed", a_pCmd );
		}
		else
		{
			char szLine[1024] = { 0,0,0, };
			while(1)
			{	char* ret = fgets( (char*)szLine, 255, fp );
				if(ret == NULL) break;
				//HelpGameMaster( a_iHandle, szLine );
				ControlSystem( 0, szLine, false );
			}	
			sprintf( szResult, "%s> successful~", a_pCmd );
			fclose( fp );
		}
	}
	else if( !strcmp( szCmd, "/ChangeRwdCorrect" ) ) // prana, gold, braman
	{
		ChangeRwdCorrect( iArgument1, iArgument2, iArgument3 );
		sprintf( szResult, "%s> Prana:%f, Gold:%f, BP:%f, Item:%f", a_pCmd, g_dRwdPranaCorrect, g_dRwdGoldCorrect, g_dRwdBramanCorrect, g_dRwdItemCorrect );
	}
	else if( !strcmp( szCmd, "/killmonster2" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			if( eKala_Brahma == pMob[iArgument1].MOB.snTribe || eKala_Vishnu == pMob[iArgument1].MOB.snTribe || eKala_Siva == pMob[iArgument1].MOB.snTribe )
			{
				sprintf( szResult, "%s> can't kill the kala!!! use /killkala command.", a_pCmd );  
			}
			else
			{
				KillMonster( iArgument1 );
			}
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB );   		    
		}
	}
	else if( !strcmp( szCmd, "/cc" ) )
	{
		if( 0 < iArgument1 && eTNSpch_MaxCommentCount > iArgument1 )
		{
			memcpy( g_szrgComment[iArgument1], &a_pCmd[8], 100 );
            sprintf( szResult, "%s> [%d] %s", a_pCmd, iArgument1, g_szrgComment[iArgument1] );
		}
		else
		{
			sprintf( szResult, "%s> index:%d ", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/DropItem" ) )
	{
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			STRUCT_ITEM kItem;
			memset( &kItem, 0, sizeof(kItem) );
			kItem.snIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1;
			kItem.snDurability = eDur_Indestructible;
			kItem.byCount = 1;

			int iCoordX, iCoordY;
			iCoordX = pMob[a_iHandle].TargetX-1;
			iCoordY = pMob[a_iHandle].TargetY-1;

			if( 0 < a_iHandle && MAX_USER > a_iHandle )
				CreateItem( iCoordX, iCoordY, &kItem, 0, 0, 0, 0 );
		}
		else
		{
			sprintf( szResult, "%s> invalid item ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeImmunity" ) )	 // mob handle, Immunity
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].m_iImmunity = iArgument2;
			sprintf( szResult, "%s> Immunity:%d", a_pCmd, pMob[iArgument1].m_iImmunity );
		}
	}
	else if( !strcmp( szCmd, "/ChangeTrimuriti" ) )	// mob id, trimuriti
	{
		if( 0 < iArgument1 && MAX_MOB > iArgument1 ) // mob all
		{
			pMob[iArgument1].MOB.byTrimuriti = (byte)iArgument2;
			pMob[iArgument1].m_byClan = (byte)iArgument2;
			pMob[iArgument1].NotifyUpdateUIMsg();
			sprintf( szResult, "%s> change the trimuriti of %d to %d", a_pCmd, iArgument1, iArgument2 );
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeLevel" ) )
	{
		if( (0 < iArgument1 && MAX_MOB > iArgument1) && ( 0 < iArgument2 && 100 >= iArgument2 ) )
		{
			pMob[iArgument1].MOB.byLevel = iArgument2;
			sprintf( szResult, "%s> level:%d", a_pCmd, pMob[iArgument1].MOB.byLevel );
			pMob[iArgument1].NotifyUpdateUIMsg();
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, 1, MAX_MOB-1 );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeClass" ) )		// mob handle, class1, class2
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].MOB.byClass1 = iArgument2;
			pMob[iArgument1].MOB.byClass2 = iArgument3;

			pMob[iArgument1].NotifyUpdateUIMsg();
		}
	}
	else if( !strcmp( szCmd, "/ResetStat" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetStat();
		}
	}
	else if( !strcmp( szCmd, "/ResetSkill" ) )
	{
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			pMob[iArgument1].ResetSkill();
		}
	}
	else if( !strcmp( szCmd, "/SwitchOffEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_Off;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration );
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/SwitchOnEvent") )		// event index
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].iDuration = eEvntSwitch_On;
			sprintf( szResult, "%s> g_krgEventList[%d]:%d", a_pCmd, iArgument1, g_krgEventList[iArgument1].iDuration );
		}
		else
		{
			sprintf( szResult, "%s> failed~~~(event ID%d)", a_pCmd, iArgument1 );
		}
	}
	else if( !strcmp( szCmd, "/ChangeEventSetting" ) )	// event index, count, cool-down time, sProceedType, duration
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].sCount = iArgument2;
			g_krgEventList[iArgument1].uiCoolDownTime = iArgument3;
			g_krgEventList[iArgument1].sProceedType = iArgument4;
			//g_krgEventList[iArgument1].iDuration = iArgument5;

			sprintf( szResult, "%s> event index:%d, count:%d, cool-down time:%d, enable:%d", a_pCmd, iArgument1
				, g_krgEventList[iArgument1].sCount, g_krgEventList[iArgument1].uiCoolDownTime, g_krgEventList[iArgument1].sProceedType );
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~%d)", a_pCmd, eEvent_MaxCount );
		}
	}
	else if( !strcmp( szCmd, "/ChangeEventTask" ) )		// event index, task1, task2, task3, task4
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].srgTask[0] = iArgument2;
			g_krgEventList[iArgument1].srgTask[1] = iArgument3;
			g_krgEventList[iArgument1].srgTask[2] = iArgument4;
			g_krgEventList[iArgument1].srgTask[3] = iArgument5;

			sprintf( szResult, "%s> event index:%d, task(%d,%d,%d,%d,%d)", a_pCmd, iArgument1
				, g_krgEventList[iArgument1].srgTask[0], g_krgEventList[iArgument1].srgTask[1]
				, g_krgEventList[iArgument1].srgTask[2], g_krgEventList[iArgument1].srgTask[3], g_krgEventList[iArgument1].srgTask[4]
				); 
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~%d)", a_pCmd, eEvent_MaxCount );
		}
	}
	else if( !strcmp( szCmd, "/ChangeEventTask2" ) )	// event index, task5
	{
		if( 0 <= iArgument1 && eEvent_MaxCount > iArgument1 )
		{
			g_krgEventList[iArgument1].srgTask[4] = iArgument2;

			sprintf( szResult, "%s> event index:%d, task(%d,%d,%d,%d,%d)", a_pCmd, iArgument1
				, g_krgEventList[iArgument1].srgTask[0], g_krgEventList[iArgument1].srgTask[1]
				, g_krgEventList[iArgument1].srgTask[2], g_krgEventList[iArgument1].srgTask[3], g_krgEventList[iArgument1].srgTask[4]
				); 
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~%d)", a_pCmd, eEvent_MaxCount );
		}
	}
	else if( !strcmp( szCmd, "/ChangeTaskSetting" ) )		// task index, action ID, param1, param2, param3
	{
		if( 0 <= iArgument1 && eTask_MaxCount > iArgument1 )
		{
			g_krgTaskList[iArgument1].iActionID = iArgument2;
			g_krgTaskList[iArgument1].irgParam[0] = iArgument3;
			g_krgTaskList[iArgument1].irgParam[1] = iArgument4;
			g_krgTaskList[iArgument1].irgParam[2] = iArgument5;

			sprintf( szResult, "%s> task index:%d, action ID:%d, param(%d,%d,%d,%d,%d)", a_pCmd, iArgument1, g_krgTaskList[iArgument1].iActionID
				, g_krgTaskList[iArgument1].irgParam[0], g_krgTaskList[iArgument1].irgParam[1], g_krgTaskList[iArgument1].irgParam[2]
				, g_krgTaskList[iArgument1].irgParam[3], g_krgTaskList[iArgument1].irgParam[4]
				);
		}
		else
		{
			sprintf( szResult, "%s> invalid task index(0~%d)", a_pCmd, eTask_MaxCount );
		}
	}
	else if( !strcmp( szCmd, "/ChangeTaskSetting2" ) )		// task index, param4, param5, 미정, 미정
	{
		if( 0 <= iArgument1 && eTask_MaxCount > iArgument1 )
		{			
			g_krgTaskList[iArgument1].irgParam[3] = iArgument2;
			g_krgTaskList[iArgument1].irgParam[4] = iArgument3;

			sprintf( szResult, "%s> task index:%d, action ID:%d, param(%d,%d,%d,%d,%d)", a_pCmd, iArgument1, g_krgTaskList[iArgument1].iActionID
				, g_krgTaskList[iArgument1].irgParam[0], g_krgTaskList[iArgument1].irgParam[1], g_krgTaskList[iArgument1].irgParam[2]
				, g_krgTaskList[iArgument1].irgParam[3], g_krgTaskList[iArgument1].irgParam[4]
				);
		}
		else
		{
			sprintf( szResult, "%s> invalid task index(0~%d)", a_pCmd, eTask_MaxCount );
		}
	}
	else if( !strcmp( szCmd, "/ChangeEvent" ) )		// monster handle, event ID // 입력이 없으면, 현재 set된 event 번호를 출력해준다.
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			if( 0 < iArgument2 ) pMob[iArgument1].MOB.snBagIndex = iArgument2; //
			sprintf( szResult, "%s> the event of monster(%d): %d", a_pCmd, iArgument1, pMob[iArgument1].MOB.snBagIndex ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid monster ID(handle;%d~%d)", a_pCmd, MAX_USER, MAX_MOB );
		}
	}
	else if( !strcmp( szCmd, "/InitEvent" ) ) // event 설정을 초기화 한다.
	{
		int iEvent = iArgument1; // event index

		if( 0 >= iEvent || eEvent_MaxCount <= iEvent ) sprintf( szResult, "%s> invalid event ID(handle;%d~%d)", a_pCmd, 0, eEvent_MaxCount );
		else
		{
			g_krgEventList[iEvent].uiAvailableTime = 0;
			g_krgEventList[iEvent].sClan = eEvntClan_All;
			g_krgEventList[iEvent].iDuration = eEvntSwitch_On;

			sprintf( szResult, "%s> the event(%d) is initialized.", a_pCmd, iEvent ); 
		}
	}
	else if( !strcmp( szCmd, "/AddEventToScheduler" ) ) // event를 time scheduler에 등록한다.	// time slot, event
	{
		int iFlag = 1;
		if( 0 <= iArgument1 && eTS_MaxSlot > iArgument1 )
		{
			if( 0 <= iArgument2 && eEvent_MaxCount > iArgument2 ) // 0 일때는 remove
			{
				g_srgTimeSchedule[iArgument1] = iArgument2;
				sprintf( szResult, "%s> the event(%d) is registered at slot(%d).", a_pCmd, iArgument2, iArgument1 ); 
				iFlag = 0;
			}
		}

		if( iFlag ) sprintf( szResult, "%s> failed", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/RemoveEventAtScheduler" ) )
	{
		for( int i = 0; i < eTS_MaxSlot; ++i )
		{
			if( iArgument1 == g_srgTimeSchedule[i] ) g_srgTimeSchedule[i] = 0;
		}

		sprintf( szResult, "%s> the event(%d) is removed all.", a_pCmd, iArgument1 ); 
	}	
	else if( !strcmp( szCmd, "/ChangeMonsterHP" ) ) // raw data 수정		// monster ID, Max HP, HP recovery
	{// Monster ID, HP, HPRecovery
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].nHP = iArgument2;
			pMonsterData[iIndex].byQuest[eMonPrty_HPRecovery] = iArgument3;

			sprintf( szResult, "%s> Monster(idx:%d) Max HP:%d(recv:%d)", a_pCmd, iIndex, pMonsterData[iIndex].nHP, pMonsterData[iIndex].byQuest[eMonPrty_HPRecovery] ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterImmunity" ) ) // raw data 수정			// monster ID, Immunity
	{// Monster ID, Immunity
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].nGuildID = iArgument2;

			sprintf( szResult, "%s> Monster(idx:%d) Immu:%d", a_pCmd, iIndex, pMonsterData[iIndex].nGuildID ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterARDG" ) )		// monster id, Attack rate, Dodge rate
	{// Monster ID, Attack Rate, Dodge Rate
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].sMuscle = iArgument2;
			pMonsterData[iIndex].sNerves = iArgument3;
			sprintf( szResult, "%s> Monster(idx:%d) AR:%d, DG:%d", a_pCmd, iIndex, pMonsterData[iIndex].sMuscle, pMonsterData[iIndex].sNerves ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterAC" ) )		// monster ID, AC
	{// Monster ID, AC
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].sHeart = iArgument2;
			sprintf( szResult, "%s> Monster(idx:%d) AC:%d", a_pCmd, iIndex, pMonsterData[iIndex].sHeart ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterMR" ) )		// monster ID, fire, cold, lightning, poison
	{// Monster ID, Fire R, Cold R, Lightning R, Poison R
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex = iArgument2;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability = iArgument3;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial = iArgument4;
			pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy = iArgument5;

			sprintf( szResult, "%s> Monster(idx:%d) FR:%d, CR:%d, LR:%d, PR:%d ", a_pCmd, iIndex
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snIndex
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDurability
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].wSerial
				, pMonsterData[iIndex].Equip[eMonPrty_Resist].snDummy ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSkillEffect" ) ) 
	{// skill ID, Index of the effect,  Effect ID, function, duration, parameter1, parameter2
		if( HT_PARAMTYPE_MONSTERSKILL_START <= iArgument1 && HT_PARAMTYPE_MONSTERSKILL_END >= iArgument1 && 0 <= iArgument2 && 5 > iArgument2 )
		{
			int iIndex = iArgument1 + 500;
			pSkillData[iIndex].krgEffect[iArgument2].iID = iArgument3;
			pSkillData[iIndex].krgEffect[iArgument2].kFunc.iData = iArgument4;
			pSkillData[iIndex].krgEffect[iArgument2].iDuration = iArgument5;
			pSkillData[iIndex].krgEffect[iArgument2].iParam1 = iArgument6;
			pSkillData[iIndex].krgEffect[iArgument2].iParam2 = iArgument7;

			memset( &(pSkillData[iIndex].kDamage), 0, sizeof(pSkillData[iIndex].kDamage) );
			for( int i = 0; i < TN_MAX_EFFECT_COUNT; ++i )
			{
				if( 0 >= pSkillData[iIndex].krgEffect[i].iID ) continue;

				if( eTNSklD_Instant == pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
				else pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection;
				//else if( eTNSklD_Instant < pSkillData[iIndex].krgEffect[i].iDuration ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Affection;
				if( (eTNAfn_DamageSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_FireSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_PoisonSplash == pSkillData[iIndex].krgEffect[i].iID)
					|| (eTNAfn_ColdSplash == pSkillData[iIndex].krgEffect[i].iID) || (eTNAfn_LightningSplash == pSkillData[iIndex].krgEffect[i].iID) ) pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Splash;

				if( eTNSklD_Instant != pSkillData[iIndex].krgEffect[i].iDuration ) continue;

				switch( pSkillData[iIndex].krgEffect[i].iID )
				{
				case eTNAfn_Damage :
				case eTNAfn_DamageSplash :
					pSkillData[iIndex].kDamage.irgPhy[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgPhy[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_PierceDamage :
					pSkillData[iIndex].kDamage.irgPierce[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgPierce[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					break;
				case eTNAfn_Fire :
				case eTNAfn_FireSplash :
					pSkillData[iIndex].kDamage.irgFire[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgFire[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_Cold :
				case eTNAfn_ColdSplash :
					pSkillData[iIndex].kDamage.irgCold[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgCold[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_Lightning :
				case eTNAfn_LightningSplash :
					pSkillData[iIndex].kDamage.irgLightning[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgLightning[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				case eTNAfn_Poison :
				case eTNAfn_PoisonSplash :
					pSkillData[iIndex].kDamage.irgPoison[0] += pSkillData[iIndex].krgEffect[i].iParam1;
					pSkillData[iIndex].kDamage.irgPoison[1] += pSkillData[iIndex].krgEffect[i].iParam2;
					//pSkillData[iIndex].sSkillType = pSkillData[iIndex].sSkillType | eTNSklT_Instant;
					break;
				} // end of switch
			}

			sprintf( szResult, "%s> Monster Skill(idx:%d) Effect: ID:%d, Func:%d, Dur:%d, Param1:%d, Param2:%d)"
				, a_pCmd, iIndex
				, pSkillData[iIndex].krgEffect[iArgument2].iID, pSkillData[iIndex].krgEffect[iArgument2].kFunc.iData, pSkillData[iIndex].krgEffect[iArgument2].iDuration
				, pSkillData[iIndex].krgEffect[iArgument2].iParam1, pSkillData[iIndex].krgEffect[iArgument2].iParam2				
				); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d or Invalid index of the effect.", a_pCmd, HT_PARAMTYPE_MONSTERSKILL_START, HT_PARAMTYPE_MONSTERSKILL_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSkill" ) )
	{// Skill ID, Attack Speed, Cooldown time, Range, AOE, Allowed Target
		if( HT_PARAMTYPE_MONSTERSKILL_START <= iArgument1 && HT_PARAMTYPE_MONSTERSKILL_END >= iArgument1 )
		{
			int iIndex = iArgument1 + 500;
			pSkillData[iIndex].iAttackSpeed = iArgument2;
			pSkillData[iIndex].iActivateTime = iArgument3;
			pSkillData[iIndex].iRange = iArgument4 + 2;
			pSkillData[iIndex].iAOE = iArgument5 + 2;
			pSkillData[iIndex].iAllowedTargets = iArgument6;

			sprintf( szResult, "%s> Monster Skill(idx:%d) AttackSpeed:%d, Cooldown:%d, Range:%d, AOE:%d, AllowedTarget:%d)"
				, a_pCmd, iIndex
				, pSkillData[iIndex].iAttackSpeed, pSkillData[iIndex].iActivateTime, pSkillData[iIndex].iRange, pSkillData[iIndex].iAOE, pSkillData[iIndex].iAllowedTargets
				); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTERSKILL_START, HT_PARAMTYPE_MONSTERSKILL_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSight" ) )		// id, normal, combat
	{// Monster ID, Normal Sight, Combat Sight
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].byQuest[eMonPrty_NormalSight] = iArgument2;
			pMonsterData[iIndex].byQuest[eMonPrty_CombatSight] = iArgument3;

			sprintf( szResult, "%s> Monster(idx:%d) Sight(%d, %d)"
				, a_pCmd, iIndex, pMonsterData[iIndex].byQuest[eMonPrty_NormalSight], pMonsterData[iIndex].byQuest[eMonPrty_CombatSight] ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterPopDelay" ) )	// id, minium pop delay, maxium pop delay
	{// Monster ID, Min delay, Max delay
		if( HT_PARAMTYPE_MONSTER_START <= iArgument1 && HT_PARAMTYPE_MONSTER_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_MONSTER_START + 1;
			pMonsterData[iIndex].Equip[eMonPrty_PopDelayMin].snIndex = iArgument2;
			pMonsterData[iIndex].Equip[eMonPrty_PopDelayMax].snIndex = iArgument3;

			sprintf( szResult, "%s> Monster(idx:%d) PopDelay(%d, %d)"
				, a_pCmd, iIndex, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMin].snIndex, pMonsterData[iIndex].Equip[eMonPrty_PopDelayMax].snIndex ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTER_START, HT_PARAMTYPE_MONSTER_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeItemCP" ) ) // item combat phase
	{		
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1;
			pItemData[iIndex].sCombatPhase = iArgument2;
			sprintf( szResult, "%s> Item(idx:%d) CombatPhase:%d", a_pCmd, iIndex, pItemData[iIndex].sCombatPhase ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeItemEffect" ) ) // item combat phase		// item id, effect index, effect id, effect dur
	{		
		if( HT_PARAMTYPE_ITEM_START <= iArgument1 && HT_PARAMTYPE_ITEM_END >= iArgument1 )
		{
			int iIndex = iArgument1 - HT_PARAMTYPE_ITEM_START + 1;
			if( 0 > iArgument2 || 4 < iArgument2 ) return;
			pItemData[iIndex].krgEffect[iArgument2].iID = iArgument3;
			pItemData[iIndex].krgEffect[iArgument2].iDuration = iArgument4;
			sprintf( szResult, "%s> Item(idx:%d) effectIdx:%d, effectID:%d, effectDur:%d", a_pCmd, iIndex, iArgument2, pItemData[iIndex].krgEffect[iArgument2].iID, pItemData[iIndex].krgEffect[iArgument2].iDuration ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_ITEM_START, HT_PARAMTYPE_ITEM_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeSkillCP" ) ) // PC skill combat phase
	{		
		if( HT_PARAMTYPE_PCSKILL_START <= iArgument1 && HT_PARAMTYPE_PCSKILL_END >= iArgument1 )
		{
			int iIndex = 0;
			for( int iLevel = 1; iLevel < 11; ++iLevel )
			{
				iIndex = (iArgument1 - HT_PARAMTYPE_PCSKILL_START )*10 + iLevel;
				pSkillData[iIndex].sCombatPhase = iArgument2;
			}
			sprintf( szResult, "%s> PC Skill(idx:%d) CombatPhase:%d", a_pCmd, iIndex, pSkillData[iIndex].sCombatPhase ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_PCSKILL_START, HT_PARAMTYPE_PCSKILL_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeMonsterSkillCP" ) ) // Monster skill combat phase		// monster skill ID, combat phase
	{		
		if( HT_PARAMTYPE_MONSTERSKILL_START <= iArgument1 && HT_PARAMTYPE_MONSTERSKILL_END >= iArgument1 )
		{
			int iIndex = iArgument1 + 500;
			pSkillData[iIndex].sCombatPhase = iArgument2;

			sprintf( szResult, "%s> Monster Skill(idx:%d) CombatPhase:%d", a_pCmd, iIndex, pSkillData[iIndex].sCombatPhase ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid ID. id:%d~%d", a_pCmd, HT_PARAMTYPE_MONSTERSKILL_START, HT_PARAMTYPE_MONSTERSKILL_END );   		    
		}
	}
	else if( !strcmp( szCmd, "/offcsh" ) ) // speed hack 관련
	{
		if( 0 == iArgument1 ) g_irgSpeedConsider[5] = 0;
		else g_irgSpeedConsider[5] = 1;

		sprintf( szResult, "%s> switch on/off :%d(0:on, 1:off)", g_irgSpeedConsider[5] );
	}
	else if( !strcmp( szCmd, "/ChangeSpeedFactor" ) ) // speed hack 관련		// time slice, over time, correct, crack point, log level
	{
		if( 0 < iArgument1 )
		{
			g_irgSpeedConsider[0] = iArgument1;
			g_irgSpeedConsider[1] = iArgument2;
			g_irgSpeedConsider[2] = iArgument3;
			g_irgSpeedConsider[3] = iArgument4;
			g_irgSpeedConsider[4] = iArgument5;
			g_irgSpeedConsider[5] = 0;
		}
        
		sprintf( szResult, "%s> time slice:%d, over time:%d, correct:%d, crack point:%d, log level:%d", a_pCmd, g_irgSpeedConsider[0], g_irgSpeedConsider[1], g_irgSpeedConsider[2], g_irgSpeedConsider[3], g_irgSpeedConsider[4] ); 
	}
	else if( !strcmp( szCmd, "/LoadSettingAll" ) )
	{
		LoadZoneSettings();
		LoadWorldSettings();
		//	LoadSettings();
		LoadSettingTxl();
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/LoadSettingsMdb" ) )
	{
		LoadSettings();
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/LoadSettingTxl" ) )
	{
		LoadSettingTxl();
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/LoadZoneSetting" ) )
	{
		LoadZoneSettings();
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/LoadWorldSetting" ) )
	{
		LoadWorldSettings();
		sprintf( szResult, "%s> Successfully", a_pCmd ); 
	}
	else if( !strcmp( szCmd, "/ChangeWorldSetting" ) )		// index, data
	{
		if( 0 <= iArgument1 && 100 > iArgument1 )
		{
			g_irgSetting[iArgument1] = iArgument2;

			sprintf( szResult, "%s> g_irgSetting[%d] : %d", a_pCmd, iArgument1, g_irgSetting[iArgument1] ); 
		}
		else
		{
			sprintf( szResult, "%s> invalid index(0~99)", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/printpos" ) )
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			sprintf( szResult, "%s> Now(%d,%d), 0:(%d,%d), 1:(%d,%d), 2(%d,%d), 3(%d,%d), 4(%d,%d)"
				, a_pCmd, pMob[iArgument1].SegmentX, pMob[iArgument1].SegmentY
				, pMob[iArgument1].SegmentListX[0], pMob[iArgument1].SegmentListY[0]
				, pMob[iArgument1].SegmentListX[1], pMob[iArgument1].SegmentListY[1]
				, pMob[iArgument1].SegmentListX[2], pMob[iArgument1].SegmentListY[2]
				, pMob[iArgument1].SegmentListX[3], pMob[iArgument1].SegmentListY[3]
				, pMob[iArgument1].SegmentListX[4], pMob[iArgument1].SegmentListY[4]
				);
		}
		else		
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB ); 		    
		}
	}
	else if( !strcmp( szCmd, "/changepos" ) )		// monster id, segment x, segment y
	{
		if( MAX_USER <= iArgument1 && MAX_MOB > iArgument1 )
		{
			pMob[iArgument1].SegmentX = iArgument2;
			pMob[iArgument1].SegmentY = iArgument3;
			pMob[iArgument1].SegmentListX[0] = pMob[iArgument1].SegmentListX[1] = pMob[iArgument1].SegmentListX[2] = pMob[iArgument1].SegmentListX[3] = pMob[iArgument1].SegmentListX[4] = iArgument2;
			pMob[iArgument1].SegmentListY[0] = pMob[iArgument1].SegmentListY[1] = pMob[iArgument1].SegmentListY[2] = pMob[iArgument1].SegmentListY[3] = pMob[iArgument1].SegmentListY[4] = iArgument3;

			sprintf( szResult, "%s> Now(%d,%d), 0:(%d,%d), 1:(%d,%d), 2(%d,%d), 3(%d,%d), 4(%d,%d)"
				, a_pCmd, pMob[iArgument1].SegmentX, pMob[iArgument1].SegmentY
				, pMob[iArgument1].SegmentListX[0], pMob[iArgument1].SegmentListY[0]
				, pMob[iArgument1].SegmentListX[1], pMob[iArgument1].SegmentListY[1]
				, pMob[iArgument1].SegmentListX[2], pMob[iArgument1].SegmentListY[2]
				, pMob[iArgument1].SegmentListX[3], pMob[iArgument1].SegmentListY[3]
				, pMob[iArgument1].SegmentListX[4], pMob[iArgument1].SegmentListY[4]
				);
		}
		else		
		{
			sprintf( szResult, "%s> invalid monster ID. id:%d~%d", a_pCmd, MAX_USER, MAX_MOB ); 		    
		}
	}
	else if( !strcmp( szCmd, "/ChangeHalfGrid" ) ) // ok
	{
		if( 31 < iArgument1 )
		{
			g_iHalfGridX = g_iHalfGridY = iArgument1;
			g_iViewGridX = g_iViewGridY = g_iHalfGridX + g_iHalfGridY + 1;	
		}

		sprintf( szResult, "%s> ViewGrid:%d, HalfGrid:%d", a_pCmd, g_iViewGridX, g_iHalfGridX );
	}
	else if( !strcmp( szCmd, "/ChangePopArea" ) ) // index, start x, end x, start z, end z
	{
		if( 0 > iArgument1 || 4 <= iArgument1 ) return;
		TrimurityArea.pArea[iArgument1][0].snStartX = iArgument2;
		TrimurityArea.pArea[iArgument1][0].snEndX = iArgument3;
		TrimurityArea.pArea[iArgument1][0].snStartZ = iArgument4;			
		TrimurityArea.pArea[iArgument1][0].snEndZ = iArgument5;
	}


	if( 0 < a_iHandle && MAX_USER > a_iHandle )
	{
		strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
		pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       
	}
}



void AssistPlayMovie( int a_iHandle, char* a_pCmd ) // play a movie를 위한 
{
	#ifdef __TN_PLAYMOVIE__
	if( 0 >= a_iHandle || MAX_USER <= a_iHandle ) return;    
    if( NULL == a_pCmd ) return;
    if( '/' != a_pCmd[0] ) return;

    // 모든 command를 log로 남긴다. 시간 + 누가 + 메시지
    int iLength = strlen( a_pCmd );
    if( g_iCmdMaxLength < iLength ) return;
    
    char szCmd[128] = { 0,0,0, };
	char szArguments[512] = { 0,0,0, };
    char szArgument1[256] = { 0,0,0, };
    char szArgument2[256] = { 0,0,0, };
	char szArgument3[256] = { 0,0,0, };
	char szArgument4[256] = { 0,0,0, };
	char szArgument5[256] = { 0,0,0, };
    int iArgument1 = 0, iArgument2 = 0, iArgument3 = 0, iArgument4 = 0, iArgument5 = 0;
    
	sscanf( a_pCmd, "%s %s", szCmd, szArguments );    
    if( '/' != szCmd[0] ) return;
    if( 0 == szCmd[0] ) return;

	S_SCP_RESP_WHISPER_CHAT kMsg; 
	kMsg.wType = SCP_RESP_WHISPER_CHAT;	
	kMsg.byResult = REPLY_ACK_OK;
	strncpy( kMsg.szName, "System", SZNAME_LENGTH );
	kMsg.byTextColor = 14; kMsg.byBgColor = 0; // 나중에 반전 색으로 바꾼다. 눈에 잘 띄게	
	    
    // g_iCmdMaxLength를 늘릴 수 있게 하는 command가 필요하다.
    // 몬스터 log 찍게하는 level도 조정할 수 있게 해야한다.
    // 중요한 monster는 누가 죽였고 어떤 reward를 줬는지 항상 log로 남겨야한다.(이런 형태에 맞게 log 출력부분 조정)

  
    // switch/case 문을 테스트 해본다.
	char szResult[1024] = { 0,0,0, };
	strncpy( szResult, a_pCmd, iLength );  

	if( !strcmp( szCmd, "/nokillall" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1);
		// szArgument1 : on/off

		int iFlag = 0;
		if( !strcmp( szArgument1, "on" ) ) iFlag = 1;
		else iFlag = 0;

		for( int i = 1; i < MAX_USER; ++i ) pMob[i].m_irgFlag[0] = iFlag;

		sprintf( szResult, "%s> successful~", a_pCmd );
	}
	else if( !strcmp( szCmd, "/nokill" ) )
	{
		sscanf( a_pCmd, "%s %s %s %s", szCmd, szArgument1, szArgument2 );
		iArgument1 = atoi( szArgument1 ); // mob ID
		// argument2 : on/off

		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			int iFlag = 0;
			if( !strcmp( szArgument2, "on" ) ) iFlag = 1;
			else iFlag = 0;

			pMob[iArgument1].m_irgFlag[0] = iFlag;
			sprintf( szResult, "%s> successful~, pMob[%d].m_irgFlag[0]:%d", a_pCmd, iArgument1, pMob[iArgument1].m_irgFlag[0] );
		}
	}
	else if( !strcmp( szCmd, "/nokill2" ) )
	{
		sscanf( a_pCmd, "%s %s %s", szCmd, szArgument1, szArgument2 );
		// szArgument1 : 캐릭터명
		// szArgument2 : on/off
		int iArgument1 = GetMOBID( szArgument1 );
		if( 0 < iArgument1 && MAX_USER > iArgument1 )
		{
			int iFlag = 0;
			if( !strcmp( szArgument2, "on" ) ) iFlag = 1;
			else iFlag = 0;

			pMob[iArgument1].m_irgFlag[0] = iFlag;
			sprintf( szResult, "%s> successful~, pMob[%d].m_irgFlag[0]:%d", a_pCmd, iArgument1, pMob[iArgument1].m_irgFlag[0] );
		}
	}
	else if( !strcmp( szCmd, "/nostun" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1);
		// szArgument1 : on/off

		if( !strcmp( szArgument1, "on" ) ) 
			for( int i = 1; i < MAX_USER; ++i ) pMob[i].m_iImmunity = pMob[i].m_iImmunity | eTNImm_Stun;
		else 
			for( int i = 1; i < MAX_USER; ++i ) pMob[i].m_iImmunity = 0;

		sprintf( szResult, "%s> successful~", a_pCmd );
	}
	else if( !strcmp( szCmd, "/holdall" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1);
		// szArgument1 : on/off

		if( !strcmp( szArgument1, "on" ) ) 
		{
			for( int i = 1; i < MAX_USER; ++i )
			{			
				TNEFFECT kEffect;
				kEffect.iID = eTNAfn_Hold;
				kEffect.iDuration = 600000;
				kEffect.iParam1 = 100;
				kEffect.iParam2 = 0;
				pMob[i].AddEffect( kEffect, a_iHandle, a_iHandle );
				pMob[i].BroadcastUpdateStatusMsg();
				pUser[i].cSock.SendMessage();
			}
		}
		else 
			for( int i = 1; i < MAX_USER; ++i ) pMob[i].m_iImmunity = 0;

		sprintf( szResult, "%s> successful~", a_pCmd );
	}
	else if( !strcmp( szCmd, "/mvspd" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 );
		iArgument1 = atoi( szArgument1 ); // move speed

		g_irgFlag[1] = iArgument1; // 0 이하 값을 입력하면 원래의 상태로 돌아간다.
		for( int i = 1; i < MAX_USER; ++i )
		{ 
			pMob[i].UpdateSpeed();
			//pMob[i].NotifyUpdateStatusMsg();
			pMob[i].NotifyUpdateUIMsg();
			pUser[i].cSock.SendMessage();
		}
		sprintf( szResult, "%s> successful~, g_irgFlag[1]:%d", a_pCmd, g_irgFlag[1] );
	}
	else if( !strcmp( szCmd, "/killpc" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 );
		// szArgument1 : 캐릭터명
		int iMobID = GetMOBID( szArgument1 );
		if( 0 < iMobID && MAX_USER > iMobID )	//	동일지역내 상대방 존재
		{	
			pMob[iMobID].MOB.nHP = 0;
			pMob[iMobID].CurrentTarget = 0;
			pMob[iMobID].m_eFSM = eTNFsm_Dead;
			pMob[iMobID].NotifyUpdateStatusMsg();
			pMob[iMobID].OnKilled( a_iHandle, 10 );
			sprintf( szResult, "%s> successful~", a_pCmd );
		}
		else
		{
			sprintf( szResult, "%s> failed~", a_pCmd );
		}	
	}
	else if( !strcmp( szCmd, "/killmonsterall" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 );
		// szArgument1 : 캐릭터명
		for( int i = MAX_USER; i < MAX_MOB; ++i )
		{
			KillMonster( i );
			/*
			pMob[i].MOB.nHP = 0;
			pMob[i].CurrentTarget = 0;
			pMob[i].m_eFSM = eTNFsm_Dead;
			*/
		}

		sprintf( szResult, "%s> successful~", a_pCmd );
	}
	else if( !strcmp( szCmd, "/hpup" ) )
	{
		sscanf( a_pCmd, "%s %s %s %s", szCmd, szArgument1, szArgument2 );
		iArgument1 = atoi( szArgument1 ); // mob ID
		iArgument2 = atoi( szArgument2 ); // plus heart points

		if( (0 < iArgument1) && (MAX_USER > iArgument1) && ( 0 < iArgument2 ) )
		{
			pMob[iArgument1].MOB.sHeart += iArgument2;
			pMob[iArgument1].UpdatePoints();
			pMob[iArgument1].NotifyUpdateUIMsg();
			pUser[iArgument1].cSock.SendMessage();

			sprintf( szResult, "%s> successful~, pMob[iArgument1].MOB.sHeart:%d", a_pCmd, iArgument1, pMob[iArgument1].MOB.sHeart );
		}
		else
		{
			sprintf( szResult, "%s> failed~", a_pCmd );
		}
	}
	else if( !strcmp( szCmd, "/loadscene" ) )
	{
		sscanf( a_pCmd, "%s %s", szCmd, szArgument1 );
		// szArgument1 : filename

		FILE* fp;
		fp = fopen( szArgument1, "rt" );
		if(NULL == fp )
		{
			sprintf( szResult, "%s> failed", a_pCmd );
		}
		else
		{
			char szLine[1024] = { 0,0,0, };
			while(1)
			{	char* ret = fgets( (char*)szLine, 255, fp );
				if(ret == NULL) break;
				HelpGameMaster( a_iHandle, szLine );
				AssistPlayMovie( a_iHandle, szLine );
				ControlSystem( a_iHandle, szLine, false );
			}	

			sprintf( szResult, "%s> successful~", a_pCmd );
			fclose( fp );
		}
	}

    strncpy( (char*)kMsg.szMsg, szResult, MAX_CHAT_LENGTH );
    pUser[a_iHandle].cSock.SendOneMessage((char*)&kMsg, sizeof(S_SCP_RESP_WHISPER_CHAT));       

	#endif
}
