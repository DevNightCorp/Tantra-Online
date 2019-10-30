#include <windows.h>
#include "Quest.h"
#include "BaseDef.h"
#include "CMob.h"
#include "CUser.h"
#include "Server.h"
#include "SendFunc.h"
#include "HTParamMgr.h"
#include "TFPercentMixer.h"
#include "Yut.h"
#include "GetFunc.h"
#include "Language.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

extern CMob				pMob[MAX_MOB];
extern CUser			pUser[MAX_USER];
extern CHTParameterMgr	g_ParamMgr;
extern CTFPercentMixer	g_QuestTable;

extern int				g_iHalfGridX;
extern int				g_iHalfGridY;
extern int				g_irgSetting[MAX_SETTING] ;
extern E_COUNTRY_ID		g_eCountryID;
extern int              g_irgGod[2][5];

extern short            g_srgItemGroup[eRwd_ItemGroup][eRwd_ItemGroupCount] ;
extern short			g_srgGroupItemCount[eRwd_ItemGroup] ;

extern CYut				g_Yut;

static char				temp[256];

enum E_QUEST_LEVEL
{
	eTutorialInitial	= 0,
	eTutorialA			= 1,
	eTutorialB			= 2,
	eTutorialC			= 3,
	eTutorialD			= 4,
	eTutorialE			= 5,
	eChangeClass1		= 6,

	eScenarioA			= 11,
	eScenarioB			= 12,
	eScenarioC			= 13,
	eScenarioD			= 14,
	eScenarioE			= 15,
	eScenarioF			= 16,
	eScenarioG			= 17,
	eScenarioH			= 18,
	eScenarioI			= 19,
	eScenarioJ			= 20,

	eScenario2A			= 21,
	eScenario2B			= 22,
	eScenario2B1		= 23,
	eScenario2C			= 24,
	eScenario2D			= 25,
	eScenario2E			= 26,
	eScenario2F			= 27,
	eScenario2G			= 28,
	eScenario2H			= 29,
	eScenario2I			= 30,

	eChangeClass2		= 31,
	eChangeClass2A		= 32,
	eChangeClass2B		= 33,
	eChangeClass2C		= 34,
	eChangeClass2D		= 35,

	eJinaA				= 36,
	eJinaB				= 37,
	eJinaC				= 38,
	eJinaD				= 39,
	eJinaE				= 40,

	eExileA				= 41,
	eExileB				= 42,
	eExileC				= 43,
	eExileD				= 44,
	eExileE				= 45,

	eBukduA				= 46,
	eBukduB				= 47,
	eBukduC				= 48,
	eBukduD				= 49,
	eBukduE				= 50,

	eScenario3A			= 51,
	eScenario3B			= 52,
	eScenario3C			= 53,
	eScenario3D			= 54,
	eScenario3E			= 55,

	eIndepChakra		= 81,
	eIndepSkill			= 82,

	eMonsterKill1		= 91,
	eMonsterKill2		= 92,
	e2ndClassType		= 93,

	eQuestTemp1			= 95,
	eQuestTemp2			= 96,
	eQuestTemp3			= 97,
	eQuestTemp4			= 98,
	eQuestTemp5			= 99
};

enum E_DIALOG_INDEX
{
	eDialogInit			= 0,
	eTutorialRestart	= 1
};

enum E_DIALOG_RESULT
{
	eResultOK			= 0,
	eResultREJECT		= 1
};

enum E_NPC_INDEX
{
	eNPCAbhey				= 1001,
	eNPCKumar				= 1002,
	eNPCHajit				= 1003,
	eNPCAnuBoy				= 1004,
	eNPCAnjali				= 1005,
	eNPCAnuGirl				= 1006,
	eNPCBartan				= 1101,
	eNPCGirika				= 1102,
	eNPCAshuri				= 1103,
	eNPCVananta				= 1104,
	eNPCBhuvan				= 1105,
	eNPCRahul				= 1106,
	eNPCKaran				= 1107,
	eNPCAbbas				= 1108,
	eNPCBibban				= 1109,
	eNPCSaranew				= 1110,
	eNPCNara				= 1111,
	eNPCAmar				= 1112,
	eNPCMahomat				= 1113,
	eNPCBaba				= 1114,
	eNPCKananda				= 1115,
	eNPCBadur				= 1116,
	eNPCLostBoy				= 1117,
	eNPCMonk				= 1118,
	eNPCShankar				= 1119,
	eNPCPriest				= 1120,
	eNPCWanttaopo			= 1127,
	eNPCIttungtasheo		= 1128,
	eNPCJangno				= 1129,
	eNPCJjoungkui			= 1132,
	eNPCOuyez				= 1133,
	eNPCRuishan				= 1134,
	eNPCBohrer				= 1138,
	eNPCRuipuwei			= 1146,
	eNPCHidungtasheo		= 1141,
	eNPCWuShong				= 1143,
	eNPCRuizshen			= 1142,
	eNPCShunelnyang			= 1149,
	eNPCShunnongs			= 1148,
	eNPCYasda				= 1297,
	eNPCUmay				= 1298,
	eNPCSato				= 1299,
	eNPCMamor				= 1300,
	eNPCGubo				= 1301,
	eNPCOda					= 1302,
	eNPCToyongJangin		= 1304,
	eNPCToyoug				= 1305,
	eNPCBukduJjuangz		= 1306,
	eNPCDrunker				= 1437,
	eNPCYury				= 1438,
	eNPCNaoki				= 1439,
	eNPCMusa1				= 1440,		//	전쟁터 폐허지역의 무사
	eNPCMusa2				= 1441,		//	버려진 요새의 무사
	eNPCMusa3				= 1442,		//	갓파부락의 무사
	eNPCMusa4				= 1443,		//	광산지역의 무사
	eNPCVaruna				= 1459,

	// PC방 전용서버 NPC 인덱스
	eNPCAbhey_1				= 1201,
	eNPCKumar_1				= 1202,
	eNPCHajit_1				= 1203,
	eNPCAnjali_1			= 1204,
	eNPCBartan_1			= 1205,
	eNPCGirika_1			= 1206,
	eNPCAshuri_1			= 1207,
	eNPCVananta_1			= 1208,
	eNPCBhuvan_1			= 1209,
	eNPCRahul_1				= 1210,
	eNPCKaran_1				= 1211,
	eNPCAbbas_1				= 1212,
	eNPCKananda_1			= 1213,
	eNPCBadur_1				= 1214,
	eNPCLostBoy_1			= 1215,
	// PC방 전용서버 NPC 인덱스
	eNPCAbhey_2				= 1231,
	eNPCKumar_2				= 1232,
	eNPCHajit_2				= 1233,
	eNPCAnjali_2			= 1234,
	eNPCBartan_2			= 1235,
	eNPCGirika_2			= 1236,
	eNPCAshuri_2			= 1237,
	eNPCVananta_2			= 1238,
	eNPCBhuvan_2			= 1239,
	eNPCRahul_2				= 1240,
	eNPCKaran_2				= 1241,
	eNPCAbbas_2				= 1242,
	eNPCKananda_2			= 1243,
	eNPCBadur_2				= 1244,
	eNPCLostBoy_2			= 1245,

	eVashabum				= 2001,
	eVashabumKaura			= 2002,
	eVashabumKlapra			= 2003,
	eMullecha				= 2004,
	eMullechaKaura			= 2005,
	eVruka					= 2132,
	eVrukaDara				= 2133,
	eAfraBarahaRaja			= 2008,
	eMullechaKarmana		= 2138,
	eCobra					= 2139,
	eUlkamulka				= 2011,
	eUlkamulkaKaura			= 2012,
	eHeruka					= 2014,
	eAnanga					= 2016,
	eJarcu					= 2032,
	eJarcuRudhira			= 2033,
	eGhorayogi				= 2034,
	eNagamudra				= 2035,
	eKaulitara				= 2019,
	eMeghamalin				= 2072,
	eHwanGeosu				= 2085,
	eTiger					= 2076,
	eWhiteTiger				= 2077,
	eJeoparyung				= 2082,
	eJeoparyungGeosu		= 2083,
	eMangRyang				= 2144,
	eBrahmaScout1			= 2070,// fors_debug 2瘻競뻣
	eBrahmaScout2			= 2024,
	eVishuneScout1			= 2081,
	eVishuneScout2			= 2082,
	eSivaScout1				= 2031,
	eSivaScout2				= 2030,
	eStadiumMurderer		= 2957,
	eJagoi					= 2074,
	eJagoiGeosu				= 2075,
	eSingoi					= 2078,
	eGoldSoldier			= 2105,			//	금귀갑병
	eJinmoin				= 2143,
	eJinmoinGeosu			= 2145,
	eGuihwasang				= 2080,
	eVirginGhost			= 2167,
	eGraveChief				= 2226,
	eGraver1				= 2224,
	eGraver2				= 2225,
	eSwordMan				= 2370,
	eSangmunsa				= 2236,
	eSangmungwan			= 2237,
	ePungsusa				= 2239,
	ePungsugwan				= 2240,
	eBukduSunggun			= 2371,
	eChunMyungSa1			= 2242,
	eChunMyungSa2			= 2257,
	eChunMyungGwan			= 2243,
	eChungMyungDaekwan		= 2244,
	eSiksichug				= 2268,			//	식시충
	eScorpion 				= 2285,			//	고대전갈
	eGutpa1					= 2403,			//	갓파광부1
	eGutpa2					= 2404,			//	갓파광부2
	eSsauabi				= 2411,			//	싸울아비 전사
	eChumGgun				= 2413,			//	춤꾼
	eWildPig				= 2532,			//	멧돼지(퀘스트용)
	eScarecrow				= 2421,			//	허수아비
	eGutpaFarmer1			= 2405,			//	갓파농부1
	eGutpaFarmer2			= 2406,			//	갓파농부2
	eGutpaSoldier1			= 2401,			//	갓파전사1
	eGutpaSoldier2			= 2402,			//	갓파전사2
	eNaokiSsauabi			= 2533,			//	나오키 싸울아비		
	eSarparaja				= 2027,			//	사르파라자
	eWhagui					= 2093,			//	화귀
	ePangwho				= 2094,			//	팽후
	eChunho					= 2092,			//	천호
	eYummabung				= 2096			//	염마병

};

enum E_ITEM_INDEX
{
	eDipailla				= 6504,
	eIlla					= 6501,
	eSurapa					= 6503,
	eAzis					= 6502

};

enum E_TASK_REWARD_TYPE
{
	eTaskRewardItem			= 1,
	eTaskRewardRupiah		= 2,
	eTaskRewardPrana		= 3,
	eTaskRewardKarma		= 4,
	eTaskRewardGroupItem	= 5
};

enum E_TASK_RESULT
{
	eTaskResultSuccess		= 0,
	eTaskResultWrongIndex	= 1,
	eTaskResultWrongNPC		= 2,
	eTaskResultNeedItem		= 3,
	eTaskResultInvenLack	= 4,
	eTaskResultNeedMoney	= 5,
	eTaskResultNPCDistance	= 6,
	eTaskResultProbability	= 7,
	eTaskResultNullEvent	= 8,
	eTaskResultKarmaLack	= 9,
	eTaskResultLevel		= 10
};

std::map< int, TASK_INFO > g_mapTask;

BOOL IsPartyMember( int nUser );
BOOL GiveMoney( int nUser, int nMoney );
void NotifyQuestLevel( int nUser, short snNPCIndex, DWORD dwQuestIndex, byte byQuestLevel );
void NotifyDialog( int nUser, short snDialog );
BOOL IsNight();
BOOL GetProbability( int nPercent );
BOOL GetProbability_10000( int nRate );
void SendTaskResult( int nUser, int nTaskIndex, int nResult );
BOOL QUEST_OnExileCKillMonster( int nUser, int nEvent, short snNPCIndex, int nItemIndex );
BOOL SummonMonster( int nNPCID, int nMonsterID, int nClass, int nClan, int nX=0, int nY=0, int nLifeTime=3000 );
void GivePartyPrana( int nUser, int nPrana );
void RepairEquips( int nUser );
void RepairPartyEquips( int nUser );

#define QUEST_LEVEL(quest_flag) ( pMob[nUser].MOB.byQuest[quest_flag] )
#define QUEST_SCRIPTLEVEL() ( pUser[nUser].m_byQuestLevel )

#define CHECK_QUEST(quest_flag) if ( pMob[nUser].MOB.byQuest[quest_flag] != 0 && pMob[nUser].MOB.byQuest[quest_flag] != 255 )
#define CHECK_SCRIPTQUEST(quest_flag) if ( (pUser[nUser].m_snQuestID == quest_flag) && ( pUser[nUser].m_byQuestLevel != 0 && pUser[nUser].m_byQuestLevel != 255 ))
#define CHECK_QUEST_LEVEL(quest_flag,level) if ( pMob[nUser].MOB.byQuest[quest_flag] != 0 && pMob[nUser].MOB.byQuest[quest_flag] != 255 && pMob[nUser].MOB.byLevel >= level )
#define EMPTY_INVEN_TEST(empty_count) if ( GetEmptyInvenCount( nUser ) < empty_count ) { NotifyDialog( nUser, 1 ); return TRUE; }
#define IN_KOREA(imple) if ( g_eCountryID == eCountryKorea || g_eCountryID == eCountryTaiwan ) { imple; }
#define CHECK_DIALOG_QUEST_CHECK(quest_flag) if ( QUEST_LEVEL(quest_flag) != 1 && QUEST_LEVEL(quest_flag) != 3 ) break
#define CHECK_DIALOG_SCRIPTQUEST_CHECK(quest_flag) if ( pUser[nUser].m_snQuestID != quest_flag || ( QUEST_SCRIPTLEVEL() != 1 && QUEST_SCRIPTLEVEL() != 3 )) break


BOOL QUEST_OnEvent( int nUser, int nEvent, short snNPCIndex, int nItemIndex, BOOL bMonsterKill )
{
	if ( nUser <= 0 || nUser >= MAX_USER ) return TRUE;

	if ( pMob[nUser].MOB.byQuest[eExileC] >= 5 && pMob[nUser].MOB.byQuest[eExileC] < 57 && bMonsterKill == TRUE )
	{
		if ( QUEST_OnExileCKillMonster( nUser, nEvent, snNPCIndex, nItemIndex ) ) return TRUE;
	}

	struct tm when;
	struct tm when_now;
	time_t now; time(&now);

	switch ( nEvent )
	{
	case eNPCMusa1:		//	전쟁터 폐허지역의 무사	
		{	
			CHECK_QUEST(eScenario3E)
			{
				switch( QUEST_LEVEL(eScenario3E) )
				{
				case 2:
					QUEST_LEVEL(eScenario3E) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 4:
					EMPTY_INVEN_TEST(1);

					if( RemoveItem( nUser, 7394, 20) )			//	무사모자 
					{
						GiveItem( nUser, 8127, 1);				//	팔왕의 흔적1
						pMob[nUser].AcquirePrana( 1000000 );
						QUEST_LEVEL(eScenario3E) = 5;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3E, 4 );
					}	else
					{
						NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					}
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 5 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCMusa2:		//	버려진 요새의 무사
		{
			CHECK_QUEST(eScenario3E)
			{
				switch( QUEST_LEVEL(eScenario3E) )
				{
				case 11:
					QUEST_LEVEL(eScenario3E) = 12;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 12:
					EMPTY_INVEN_TEST(1);

					if( FindItem (nUser, 7400, 20)!=MAX_INVEN && FindItem( nUser, 7395, 30)!=MAX_INVEN)	//	찢어진 가죽, 부러진 손톱
					{
						RemoveItem(nUser, 7400, 20);
						RemoveItem( nUser, 7395, 30);
						GiveItem( nUser, 8130, 1);									//	팔왕의 흔적4
						pMob[nUser].AcquirePrana( 1000000 );
						QUEST_LEVEL(eScenario3E) = 13;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3E, 4 );
					}	else
					{
						NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					}
					return TRUE;
				case 13:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 5 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCMusa3:		//	갓파부락의 무사
		{
			CHECK_QUEST(eScenario3E)
			{
				switch( QUEST_LEVEL(eScenario3E) )
				{
				case 8:
					QUEST_LEVEL(eScenario3E) = 9;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 9:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				case 10:
					if( RemoveItem( nUser, 8138, 1) )			//	소마
					{
						GiveItem( nUser, 8129, 1);
						pMob[nUser].AcquirePrana( 1000000 );	//	팔왕의 흔적3
						QUEST_LEVEL(eScenario3E) = 11;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3E, 4 );
						return TRUE;
					}	
				case 11:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 5 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCMusa4:		//	광산지역의 무사
		{
			CHECK_QUEST(eScenario3E)
			{
				switch( QUEST_LEVEL(eScenario3E) )
				{
				case 5:
					QUEST_LEVEL(eScenario3E) = 6;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 6:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				case 7:
					if( RemoveItem( nUser, 8108, 1) )			//	금두꺼비
					{
						GiveItem( nUser, 8128, 1);				//	팔왕의 흔적2
						pMob[nUser].AcquirePrana( 1000000 );
						QUEST_LEVEL(eScenario3E) = 8;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3E, 4 );
						return TRUE;
					}
				case 8:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 5 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCNaoki:
		{
			CHECK_QUEST(eScenario3D)
			{
				switch( QUEST_LEVEL(eScenario3D) )
				{
				case 12:
					pMob[nUser].AcquirePrana( 1500000 );
					QUEST_LEVEL(eScenario3D) = 13;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 1 );
					return TRUE;
				case 13:
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 2 );
					return TRUE;
				case 14:
					if( RemoveItem( nUser, 8137, 1) )
					{
						GiveItem( nUser, 8125, 1 );
						pMob[nUser].AcquirePrana( 2000000 );
						QUEST_LEVEL(eScenario3D) = 15;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3D, 4 );
						return TRUE;
					}
				case 15:
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 5 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCYury:
		{
			CHECK_QUEST(eScenario3D)
			{
				switch( QUEST_LEVEL(eScenario3D) )
				{
				case 10:
					EMPTY_INVEN_TEST(1);

					SummonMonster( nUser, eNaokiSsauabi, eTNCls_Warrior, eTNClan_CastleOwner, 843, 112 );
					GiveItem( nUser, 8126, 1);
					QUEST_LEVEL(eScenario3D) = 11;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 1 );
					return TRUE;
				case 11:
					SummonMonster( nUser, eNaokiSsauabi, eTNCls_Warrior, eTNClan_CastleOwner, 843, 112 );
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCOda:
		{
			CHECK_QUEST_LEVEL( eScenario3D, 78 )
			{
				switch( QUEST_LEVEL(eScenario3D) )
				{
				case 17:
					pMob[nUser].AcquirePrana( 20000000 );
					GiveMoney( nUser, 2000000 );
					QUEST_LEVEL(eScenario3D) = 255;
					QUEST_LEVEL(eScenario3E) = 1;
					SendQuestHistory( nUser );
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario3D );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
				case 1:
				case 2:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eScenario3D, QUEST_LEVEL(eScenario3D) );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCDrunker:
		{
			CHECK_QUEST(eScenario3B)
			{
				switch( QUEST_LEVEL(eScenario3B)  )
				{
                case 10:
					QUEST_LEVEL(eScenario3B) = 11;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 1 );
					return TRUE;
				case 11:
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 2 );
					return TRUE;
				case 15:
					if ( RemoveItem( nUser, 8112, 1 ) )
					{
						GiveItem(nUser, 8114, 1);
						QUEST_LEVEL(eScenario3B) = 16;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3B, 4 );
						return TRUE;
					}
				case 16:
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 5 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCMamor:
		{	
			CHECK_QUEST(eScenario3B)
			{
				switch( QUEST_LEVEL(eScenario3B)  )
				{
                case 2:
					if ( RemoveItem( nUser, 7400, 30 ) )
					{
						GiveMoney(nUser, 500000);
						pMob[nUser].AcquirePrana( 1000000 );
						QUEST_LEVEL(eScenario3B) = 4;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3B, 1 );
						return TRUE;
					}					
				case 4:
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCUmay:
		{
			CHECK_QUEST(eScenario3A)
			{
				switch( QUEST_LEVEL(eScenario3A) )
				{
				case 11:
                    if ( RemoveItem( nUser, 8109, 1 ) )
					{
						QUEST_LEVEL(eScenario3A) = 12;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3A, 1 );
						return TRUE;
					}
				case 12:
					if ( RemoveItem( nUser, 7391, 20 ) )
					{
						pMob[nUser].AcquirePrana( 1000000 );
						QUEST_LEVEL(eScenario3A) = 13;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3A, 4 );
					}	else
					{	NotifyQuestLevel( nUser, nEvent, eScenario3A, 2 );
					}
					return TRUE;
				case 13:
					if ( FindItem( nUser, 6502, 3 ) != MAX_INVEN && FindItem( nUser, 6503, 2 ) != MAX_INVEN)
					{
						RemoveItem( nUser, 6502, 3 );		//	아지스 3개
						RemoveItem( nUser, 6503, 2 );		//	수라파 2개
						GiveItem(nUser, 8110, 1);			//	수리된 목걸이
						QUEST_LEVEL(eScenario3A) = 14;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3A, 6 );
					}	else
					{	NotifyQuestLevel( nUser, nEvent, eScenario3A, 5 );
					}
					return TRUE;
				case 14:
					NotifyQuestLevel( nUser, nEvent, eScenario3A, 7 );
					return TRUE;
				}
			}

			CHECK_QUEST_LEVEL( eScenario3C, 77 )
			{
				switch( QUEST_LEVEL(eScenario3C) )
				{
				case 1:
				case 2:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eScenario3C, QUEST_LEVEL(eScenario3C) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario3D)		//	유메이
			{
				switch( QUEST_LEVEL(eScenario3D) )
				{
				case 7:
					QUEST_LEVEL(eScenario3D) = 8;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 1 );
					return TRUE;
				case 8:
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 2 );
					return TRUE;
				case 9:
					if( FindItem(nUser, 8123, 1)!=MAX_INVEN && FindItem(nUser, 8124, 1)!=MAX_INVEN && FindItem(nUser, 8122, 1)!=MAX_INVEN )	//	색색의 쌀가루, 연꽃, 청순한 달빛
					{
						RemoveItem(nUser, 8123, 1);
						RemoveItem(nUser, 8124, 1);
						RemoveItem(nUser, 8122, 1);
						QUEST_LEVEL(eScenario3D) = 10;
						pMob[nUser].AcquirePrana( 2000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3D, 4 );
					}
					return TRUE;
				case 10:
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 5 );
					return TRUE;
				case 15:
					if( FindItem(nUser, 8126, 1)!=MAX_INVEN && FindItem(nUser, 8125, 1)!=MAX_INVEN )		//	유리의 증표, 나오키의 증표
					{
						RemoveItem(nUser, 8126, 1);
						RemoveItem(nUser, 8125, 1);
						QUEST_LEVEL(eScenario3D) = 16;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3D, 6 );
					}
					return TRUE;
				case 16:
					if( RemoveItem(nUser, 7402, 3) )		//	아디즈
					{
						switch( pMob[nUser].MOB.snTribe )	//	복원된 라마의 반지를 지급한다.
						{
						case TRIBE_NAGA:
						case TRIBE_KINNARA:
							GiveItem( nUser, 6469, 1 );
							break;
						case TRIBE_ASURA:
						case TRIBE_RAKSHASA:
							GiveItem( nUser, 6470, 1 );
							break;
						case TRIBE_YAKSA:
						case TRIBE_GANDHARVA:
							GiveItem( nUser, 6471, 1 );
							break;
						case TRIBE_DEVA:
						case TRIBE_GARUDA:
							GiveItem( nUser, 6472, 1 );
							break;
						}
						QUEST_LEVEL(eScenario3D) = 17;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3D, 8 );
					}	else
					{
						NotifyQuestLevel( nUser, nEvent, eScenario3D, 7 );
					}
					return TRUE;
				case 17:
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 9 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCGubo:
		{
			CHECK_QUEST(eScenario3A)
			{
				switch( QUEST_LEVEL(eScenario3A) )
				{
				case 8:
					QUEST_LEVEL(eScenario3A) = 9;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3A, 1 );
					return TRUE;
				case 9:
					NotifyQuestLevel( nUser, nEvent, eScenario3A, 2 );
					return TRUE;
				case 10:
					QUEST_LEVEL(eScenario3A) = 11;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3A, 4 );
					return TRUE;
				case 11:
					NotifyQuestLevel( nUser, nEvent, eScenario3A, 5 );
					return TRUE;
				case 14:
					if ( RemoveItem( nUser, 8110, 1 ) )
					{
						pMob[nUser].AcquirePrana( 20000000 );
						GiveMoney( nUser, 500000 );
						GiveItem( nUser, 7034, 1 );
						QUEST_LEVEL(eScenario3A) = 255;
						QUEST_LEVEL(eScenario3B) = 1;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3A, 255 );
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario3A );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						return TRUE;
					}
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCSato:
		{
			CHECK_QUEST(eScenario3A)
			{
				switch( QUEST_LEVEL(eScenario3A) )
				{
				case 4:
					{	DWORD dwMoney = g_Yut.HT_GetMoney( pMob[nUser].MOB.szName );
						QUEST_LEVEL(eQuestTemp1) = (byte)((dwMoney & 0xFF000000) >> 24);
						QUEST_LEVEL(eQuestTemp2) = (byte)((dwMoney & 0x00FF0000) >> 16);
						QUEST_LEVEL(eQuestTemp3) = (byte)((dwMoney & 0x0000FF00) >> 8);
						QUEST_LEVEL(eQuestTemp4) = (byte)(dwMoney & 0x000000FF);
						QUEST_LEVEL(eScenario3A) = 5;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3A, 1 );
						return TRUE;
					}
				case 5:		
					{	DWORD dwFrom = QUEST_LEVEL(eQuestTemp4);
						dwFrom += (QUEST_LEVEL(eQuestTemp1) << 24);
						dwFrom += (QUEST_LEVEL(eQuestTemp2) << 16);
						dwFrom += (QUEST_LEVEL(eQuestTemp3) << 8); 
						DWORD dwTo = g_Yut.HT_GetMoney( pMob[nUser].MOB.szName );
						if ( (dwTo - dwFrom) >= 1000 )
						{
							QUEST_LEVEL(eScenario3A) = 6;
							SendQuestHistory( nUser );
							NotifyQuestLevel( nUser, nEvent, eScenario3A, 4 );
							QUEST_LEVEL(eQuestTemp1) = 0;
							QUEST_LEVEL(eQuestTemp2) = 0;
							QUEST_LEVEL(eQuestTemp3) = 0;
							QUEST_LEVEL(eQuestTemp4) = 0;
						}	else
						{	NotifyQuestLevel( nUser, nEvent, eScenario3A, 2 );					
						}
						return TRUE;
					}
				case 6:
					if ( RemoveItem( nUser, 7399, 30 ) )
					{
						pMob[nUser].AcquirePrana( 1000000 );
						GiveMoney( nUser, 500000 );
						QUEST_LEVEL(eScenario3A) = 7;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3A, 6 );
					}	else
					{	NotifyQuestLevel( nUser, nEvent, eScenario3A, 5 );
					}
					return TRUE;
				case 7:
					NotifyQuestLevel( nUser, nEvent, eScenario3A, 7 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		}	break;
	case eNPCYasda:
		{

			if ( QUEST_LEVEL(eBukduE) == 255 && pMob[nUser].MOB.byLevel >= 75  && QUEST_LEVEL(eScenario3A) != 255 )
			{
				if ( QUEST_LEVEL(eScenario3A) == 0 ) QUEST_LEVEL(eScenario3A) = 1;

				switch( QUEST_LEVEL(eScenario3A) )
				{
				case 2:
					if ( FindItem( nUser, 7393, 20 ) != MAX_INVEN && FindItem( nUser, 7392, 20 ) != MAX_INVEN )
					{
						pMob[nUser].AcquirePrana( 1000000 );
						RemoveItem( nUser, 7393, 20 );
						RemoveItem( nUser, 7392, 20 );
						QUEST_LEVEL(eScenario3A) = 4;
						SendQuestHistory( nUser );
					}
				case 1:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eScenario3A, QUEST_LEVEL(eScenario3A) );
					return TRUE;
				case 4:
					NotifyQuestLevel( nUser, nEvent, eScenario3A, 5 );
					return TRUE;
				case 7:
					QUEST_LEVEL(eScenario3A) = 8;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3A, 6 );
					return TRUE;
				case 8:
					NotifyQuestLevel( nUser, nEvent, eScenario3A, 7 );
					return TRUE;
				}
			}


			CHECK_QUEST_LEVEL( eScenario3B, 76 )
			{
				switch( QUEST_LEVEL(eScenario3B) )
				{
				case 1:
				case 2:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eScenario3B, QUEST_LEVEL(eScenario3B) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario3C)
			{
				switch( QUEST_LEVEL(eScenario3C) )
				{
				case 2:
					QUEST_LEVEL(eScenario3C) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3C, 1 );
					TriggerEvent( 0, 168, 0, 0, 0 );
					return TRUE;
				case 4:
					TriggerEvent( 0, 168, 0, 0, 0 );
					NotifyQuestLevel( nUser, nEvent, eScenario3C, 2 );
					return TRUE;
				case 5:
					TriggerEvent( 0, 168, 0, 0, 0 );
					NotifyQuestLevel( nUser, nEvent, eScenario3C, 2 );
					return TRUE;
				case 6:
					pMob[nUser].AcquirePrana( 2000000 );
					QUEST_LEVEL(eScenario3C) = 7;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3C, 4 );
					return TRUE;
				case 7:
					NotifyQuestLevel( nUser, nEvent, eScenario3C, 5 );
					return TRUE;
				}
			}

			CHECK_QUEST_LEVEL( eScenario3E, 79 )
			{
				switch( QUEST_LEVEL(eScenario3E) )
				{
				case 1:
				case 2:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, QUEST_LEVEL(eScenario3E) );
					return TRUE;
				case 13:
					QUEST_LEVEL(eScenario3E) = 14;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 4 );
					return TRUE;
				case 14:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 5 );
					return TRUE;
				case 46:
					GiveMoney( nUser, 2000000 );
					pMob[nUser].AcquirePrana( 22000000 );
					QUEST_LEVEL(eScenario3E) = 255;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 255 );
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario3E );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					return TRUE;
				}			
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCAbhey: // 압헤이에게 말을 걸었을때.
	case eNPCAbhey_1:
	case eNPCAbhey_2:
		{
			CHECK_QUEST(eScenarioA)
			{	// SCENARIO A ///////////////////////////////////////////////////////////////////////////
				NotifyQuestLevel( nUser, nEvent, eScenarioA, QUEST_LEVEL(eScenarioA) );
				return TRUE;
			}
			CHECK_QUEST(eScenarioD)
			{	// SCENARIO D ///////////////////////////////////////////////////////////////////////////
				NotifyQuestLevel( nUser, nEvent, eScenarioD, QUEST_LEVEL(eScenarioD) );
				return TRUE;
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCKumar: // 쿠마르에게 말을 걸었을때.
	case eNPCKumar_1:
	case eNPCKumar_2:
		{
			CHECK_QUEST(eScenarioA)
			{	// SCENARIO A ///////////////////////////////////////////////////////////////////////////
				NotifyQuestLevel( nUser, nEvent, eScenarioA, QUEST_LEVEL(eScenarioA) );
				return TRUE;
			}
			CHECK_QUEST(eScenario3B)
			{	
				switch( QUEST_LEVEL(eScenario3B) )
				{
				case 9:
					RemoveItem( nUser, 8111, 1);
					QUEST_LEVEL(eScenario3B) = 10;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 1 );
					return TRUE;
				case 10:
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 2 );
					return TRUE;
				case 11:
					QUEST_LEVEL(eScenario3B) = 12;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 4 );
					return TRUE;
				case 12:
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 5 );
					return TRUE;
				case 16:
					if ( RemoveItem( nUser, 8114, 1 ) )
					{
						GiveItem( nUser, 8136, 1 );		//	복원전 라마의 반지
						GiveMoney( nUser, 1000000 );
						pMob[nUser].AcquirePrana( 20000000 );
						QUEST_LEVEL(eScenario3B) = 255;
						QUEST_LEVEL(eScenario3C) = 1;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3B, 255 );
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario3B );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						return TRUE;
					}
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCHajit: // 하지트에게 말을 걸었을때.
	case eNPCHajit_1:
	case eNPCHajit_2:
		{
			CHECK_QUEST(eScenarioD)
			{	// SCENARIO D ///////////////////////////////////////////////////////////////////////////
				NotifyQuestLevel( nUser, nEvent, eScenarioD, QUEST_LEVEL(eScenarioD) );
				return TRUE;
			}
			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCAnuBoy:	// 아누 마을 여자아이에게 말을 걸었을때.
		{
			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCAnjali: // 안잘리에게 말을 걸었을때.
	case eNPCAnjali_1:
	case eNPCAnjali_2:
		{	// SCENARIO A ///////////////////////////////////////////////////////////////////////////
			if ( QUEST_LEVEL(eScenarioA) != 255 )
			{
				switch( QUEST_LEVEL(eScenarioA) )
				{	
				case 0:
				case 1:
					if ( QUEST_LEVEL(eTutorialE) == 255 || QUEST_LEVEL(eTutorialInitial) == 0 )
					{
						NotifyQuestLevel( nUser, nEvent, eScenarioA, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 2:
				case 3:
				case 255:
					NotifyQuestLevel( nUser, nEvent, eScenarioA, QUEST_LEVEL(eScenarioA) );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario2B1)
			{	// SCENARIO 2B-1 ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2B1) )
				{
				case 2:
					if ( RemoveItem( nUser, 8020, 1 ) )
					{
						QUEST_LEVEL(eScenario2B1) = 4;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario2B1, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 4:
					NotifyQuestLevel( nUser, nEvent, eScenario2B1, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 ); 
			return TRUE;
		} break;
	case eNPCAnuGirl:	// 아누 마을 여자아이에게 말을 걸었을때.
		{
			CHECK_QUEST(eChangeClass2C)
			{
				switch ( QUEST_LEVEL(eChangeClass2C) )
				{
				case 2:
					NotifyQuestLevel( nUser, nEvent, eChangeClass2C, 1 );
					return TRUE;
				case 6:
					NotifyQuestLevel( nUser, nEvent, eChangeClass2C, 4 );
					return TRUE;
				case 4:
				case 5:
					NotifyQuestLevel( nUser, nEvent, eChangeClass2C, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0);
			return TRUE;
		} break;
	case eNPCBartan: // 바르탄에게 말을 걸었을때.
	case eNPCBartan_1:
	case eNPCBartan_2:
		{
			CHECK_QUEST(eTutorialA)
			{	// TUTORIAL A  ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eTutorialA) )
				{
				case 1:	// 바르탄에게 말을 걸었을때.
					QUEST_LEVEL(eTutorialA) = 2;
					NotifyQuestLevel( nUser, nEvent, eTutorialA, 1 );
					SendQuestHistory( nUser );
					return TRUE;
				case 2: // 말을 건 이후. 바사붐의 뿔을 4개 가져왔는지 확인한다.
					EMPTY_INVEN_TEST( 2 )
					if ( !RemoveItem( nUser, 7101, 3 ) )
					{
						NotifyQuestLevel( nUser, nEvent, eTutorialA, 2 );
						return TRUE;
					}
					GiveMoney( nUser, 200 );
					GiveItem( nUser, 7001, 10 );
					GiveItem( nUser, 5499, 1 );

					QUEST_LEVEL(eTutorialA) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eTutorialA );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					QUEST_LEVEL(eTutorialB) = 1;
					NotifyQuestLevel( nUser, nEvent, eTutorialA, 255 );
					SendQuestHistory( nUser );
					return TRUE;
				} 
			}

			CHECK_QUEST(eScenarioB)
			{	// SCENARIO B ///////////////////////////////////////////////////////////////////////////
				NotifyQuestLevel( nUser, nEvent, eScenarioB, QUEST_LEVEL(eScenarioB) );				
				return TRUE;
			}

			CHECK_QUEST(eScenarioD)
			{	// SCENARIO D ///////////////////////////////////////////////////////////////////////////
				switch( QUEST_LEVEL(eScenarioD) )
				{
				case 2:
					if ( RemoveItem( nUser, 7142, 5) )
					{
						QUEST_LEVEL(eScenarioD) = 4;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenarioD, 4 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eScenarioD, 2 );
					}
					return TRUE;
				case 4:
				case 5:
					EMPTY_INVEN_TEST( 2 );

					if ( RemoveItem( nUser, 7143, 5 ) )
					{
						GiveItem( nUser, 4291, 1 );
						IN_KOREA( GiveItem( nUser, 7025, 5 ) );
						QUEST_LEVEL(eScenarioD) = 255;
						QUEST_LEVEL(eScenarioE) = 1;
						GiveMoney( nUser, 2000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenarioD, 6 );
					}
					else
					{
						QUEST_LEVEL(eScenarioD) = 5;
						NotifyQuestLevel( nUser, nEvent, eScenarioD, 5 );
					}
					return TRUE;
				case 6:
					QUEST_LEVEL(eScenarioD) = 255;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenarioD, QUEST_LEVEL(eScenarioD) );
					break;
				default:
					NotifyQuestLevel( nUser, nEvent, eScenarioD, QUEST_LEVEL(eScenarioD) );
					return TRUE;
				}
			}

			if ( QUEST_LEVEL(eScenarioH) != 0 
				&& QUEST_LEVEL(eScenarioH) != 255 
				&& pMob[nUser].MOB.snTribe == TRIBE_YAKSA )
			{	// SCENARIO H ///////////////////////////////////////////////////////////////////////////
				if ( pMob[nUser].MOB.byLevel < 15 )
				{
					NotifyQuestLevel( nUser, nEvent, 0, 0 );
					return TRUE;
				}

				if ( QUEST_LEVEL(eScenarioH) == 9 ) 
				{
					EMPTY_INVEN_TEST( 1	);
					if ( RemoveItem( nUser, 7108, 10 ) )
					{
						QUEST_LEVEL(eScenarioH) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioH );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						if( QUEST_LEVEL(eScenarioI) == 0 ) QUEST_LEVEL(eScenarioI) = 1;
						pMob[nUser].AcquirePrana( 5000 );
						GiveMoney( nUser, 5000 );
						GiveItem( nUser, 5003, 1 );
						SendQuestHistory( nUser );
					}
				}

				NotifyQuestLevel( nUser, nEvent, eScenarioH, QUEST_LEVEL(eScenarioH) );
				return TRUE;
			}

			CHECK_QUEST(eScenario2D)
			{	// SCENARIO 2D ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2D) )				
				{
				case 5:
					if ( FindItem( nUser, 8042, 1 ) != MAX_INVEN && FindItem( nUser, 8019, 1 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 8042, 1 );
						RemoveItem( nUser, 8019, 1 );
						QUEST_LEVEL(eScenario2D) = 6;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario2D, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 6:
					NotifyQuestLevel( nUser, nEvent, eScenario2D, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3E)	//	대장장이 바르탄
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 31:
					QUEST_LEVEL(eScenario3E) = 32;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 32:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCGirika:	// 기리카에게 말을 걸었을때
	case eNPCGirika_1:
	case eNPCGirika_2:
		{
			CHECK_QUEST(eTutorialD)
			{	// TUTORIAL D  ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eTutorialD) )
				{
				case 1: // 기리카에게 처음 말을 걸었을때
					QUEST_LEVEL(eTutorialD) = 2;
					QUEST_LEVEL(eQuestTemp1) = pMob[nUser].MOB.nBramanPoint;
					NotifyQuestLevel( nUser, nEvent, eTutorialD, 1 );
					SendQuestHistory( nUser );
					return TRUE;
				case 2:
					NotifyQuestLevel( nUser, nEvent, eTutorialD, 2 );
					return TRUE;
				case 3: // 주신 포인트를 얻고 왔을때
					// 주신 포인트가 올라갔으면.
					QUEST_LEVEL(eTutorialD) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eTutorialD );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					QUEST_LEVEL(eTutorialE) = 1;
					QUEST_LEVEL(eQuestTemp1) = 0;
					GiveMoney( nUser, 500 );
					GiveItem( nUser, 5249, 1 );
					NotifyQuestLevel( nUser, nEvent, eTutorialD, 255 );
					SendQuestHistory( nUser );
					return TRUE;
				}
			}

			if ( QUEST_LEVEL(eScenarioH) != 0 
				&& QUEST_LEVEL(eScenarioH) != 255 
				&& pMob[nUser].MOB.snTribe == TRIBE_GARUDA )
			{	// SCENARIO H  ///////////////////////////////////////////////////////////////////////////
				if ( pMob[nUser].MOB.byLevel < 15 )
				{
					NotifyQuestLevel( nUser, nEvent, 0, 0 );
					return TRUE;
				}

				if ( QUEST_LEVEL(eScenarioH) ==  4 ) 
				{
					if ( RemoveItem( nUser, 8014, 1 ) )
					{
						QUEST_LEVEL(eScenarioH) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioH );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						if ( QUEST_LEVEL(eScenarioI) == 0 ) QUEST_LEVEL(eScenarioI) = 1;
						pMob[nUser].AcquirePrana( 5000 );
						GiveMoney( nUser, 5000 );
						GiveItem( nUser, 5003, 1 );
						SendQuestHistory( nUser );
					}
				}

				NotifyQuestLevel( nUser, nEvent, eScenarioH, QUEST_LEVEL(eScenarioH) );
				return TRUE;
			}
			CHECK_QUEST(eScenario2B)
			{	// SCENARIO 2B  ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2B) )
				{
				case 4:
					EMPTY_INVEN_TEST( 1 );

					GiveItem( nUser, 8018, 1 );
					QUEST_LEVEL(eScenario2B) = 5;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario2B, 1 );
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eScenario2B, 2 );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario2E)
			{	// SCENARIO 2E  ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2E) )
				{
				case 4:
					if ( FindItem( nUser, 8021, 1 ) != MAX_INVEN && FindItem( nUser, 8022, 1 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 8021, 1 );
						RemoveItem( nUser, 8022, 1 );
						GiveItem( nUser, 8023, 1 );
						GiveItem( nUser, 8045, 1 );
						QUEST_LEVEL(eScenario2E) = 5;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario2E, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eScenario2E, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST(eBukduB)
			{
				switch( QUEST_LEVEL(eBukduB) )
				{
				case 5:
					EMPTY_INVEN_TEST( 1 );
					if ( RemoveItem( nUser, 7322, 10 ) )
					{
						GiveItem( nUser, 8102, 1 );
						QUEST_LEVEL(eBukduB) = 6;
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduB, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 6:
					NotifyQuestLevel( nUser, nEvent, eBukduB, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3E)	//	공예사 기리카
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 30:
					QUEST_LEVEL(eScenario3E) = 31;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 31:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCAshuri:
	case eNPCAshuri_1:
	case eNPCAshuri_2:
		{
			if ( QUEST_LEVEL(eScenarioH) != 0 
				&& QUEST_LEVEL(eScenarioH) != 255 
				&& pMob[nUser].MOB.snTribe == TRIBE_GANDHARVA )
			{	// SCENARIO H ///////////////////////////////////////////////////////////////////////////
				if ( pMob[nUser].MOB.byLevel < 15 )
				{
					NotifyQuestLevel( nUser, nEvent, 0, 0 );
					return TRUE;
				}

				if ( QUEST_LEVEL(eScenarioH) == 8 ) 
				{
					if ( RemoveItem( nUser, 8016, 1 ) )
					{
						QUEST_LEVEL(eScenarioH) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioH );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						if ( QUEST_LEVEL(eScenarioI) == 0 ) QUEST_LEVEL(eScenarioI) = 1;
						pMob[nUser].AcquirePrana( 5000 );
						GiveMoney( nUser, 5000 );
						GiveItem( nUser, 5003, 1 );
						SendQuestHistory( nUser );
					}
				}

				NotifyQuestLevel( nUser, nEvent, eScenarioH, QUEST_LEVEL(eScenarioH) );
				return TRUE;
			}
			CHECK_QUEST(eScenario3E)	//	보석상 아슈리
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 29:
					QUEST_LEVEL(eScenario3E) = 30;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 30:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}


			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCVananta: // 바난타에게 말을 걸었을때.
	case eNPCVananta_1:
	case eNPCVananta_2:
		{
			CHECK_QUEST( eChangeClass1 )
			{
				switch ( QUEST_LEVEL(eChangeClass1) )
				{
				case 2:
					QUEST_LEVEL(eChangeClass1) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eChangeClass1, 1 );
					break;
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
					NotifyQuestLevel( nUser, nEvent, eChangeClass1, 2 );
					break;
				case 11:
					EMPTY_INVEN_TEST( 1 );
					GiveItem( nUser, 8107, 1 );
					QUEST_LEVEL(eChangeClass1) = 12;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eChangeClass1, 4 );
					break;
				case 12:
					NotifyQuestLevel( nUser, nEvent, eChangeClass1, 5 );
					break;
				default:
					NotifyQuestLevel( nUser, nEvent, 0, 0 );
					break;
				}
				return TRUE;
			}
			if ( QUEST_LEVEL(eTutorialInitial) == 0 && QUEST_LEVEL(eScenarioA) <= 1 )
			{	// TUTORIAL INITIAL /////////////////////////////////////////////////////////////////////
				NotifyQuestLevel( nUser, nEvent, 0, 1 );
				return TRUE;
			}
			if ( QUEST_LEVEL(eTutorialD) == 2)
			{	// TUTORIAL D ///////////////////////////////////////////////////////////////////////////
				if ( GetEmptyInven( nUser ) != MAX_INVEN ) 
				{
					if ( RemoveItem( nUser, 7102, 3 ) )
					{
						pMob[nUser].AcquirePrana( 100 );
						GiveItem( nUser, 7001, 10 );
						QUEST_LEVEL(eTutorialD) = 3;

						NotifyQuestLevel( nUser, nEvent, eTutorialD, 255 );
						SendQuestHistory( nUser );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				}
				else
				{
					NotifyDialog( nUser, 1 );
					NotifyQuestLevel( nUser, nEvent, 0, 0 );
					return TRUE;
				}
			}
			if ( QUEST_LEVEL(eScenarioH) != 0 
				&& QUEST_LEVEL(eScenarioH) != 255 
				&& pMob[nUser].MOB.snTribe == TRIBE_DEVA )
			{	// SCENARIO H ///////////////////////////////////////////////////////////////////////////
				if ( pMob[nUser].MOB.byLevel < 15 )
				{
					NotifyQuestLevel( nUser, nEvent, 0, 0 );
					return TRUE;
				}

				if ( QUEST_LEVEL(eScenarioH) == 6 ) 
				{
					if ( RemoveItem( nUser, 8015, 1 ) )
					{
						QUEST_LEVEL(eScenarioH) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioH );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						if ( QUEST_LEVEL(eScenarioI) == 0 ) QUEST_LEVEL(eScenarioI) = 1;
						pMob[nUser].AcquirePrana( 5000 );
						GiveMoney( nUser, 5000 );
						GiveItem( nUser, 5003, 1 );
						SendQuestHistory( nUser );
					}
				}

				NotifyQuestLevel( nUser, nEvent, eScenarioH, QUEST_LEVEL(eScenarioH) );
				return TRUE;
			}
			CHECK_QUEST(eScenario2I)
			{	// SCENARIO 2I /////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2I) )
				{
				case 8:
					if ( RemoveItem( nUser, 8035, 1 ) )
					{
						GiveItem( nUser, 8036, 1 );
						QUEST_LEVEL(eScenario2I) = 9;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario2I, 1 );
					}
					else NotifyQuestLevel( nUser, nEvent, eScenario2I, 0 );
					return TRUE;
				case 9:
					NotifyQuestLevel( nUser, nEvent, eScenario2I, 2 );
					return TRUE;
				case 10:
					EMPTY_INVEN_TEST( 3 );

					if ( RemoveItem( nUser, 8040, 1 ) )
					{
						GiveItem( nUser, 6243, 1 );
						IN_KOREA( GiveItem( nUser, 6801, 60 ) );
						IN_KOREA( GiveItem( nUser, 6802, 60 ) );
						IN_KOREA( GiveItem( nUser, 7031, 1 ) );
						QUEST_LEVEL(eScenario2I) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario2I );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						pMob[nUser].AcquirePrana( 150000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario2I, 255 );
					}
					return TRUE;
				}
			}
			CHECK_QUEST(eExileC)
			{
				switch( QUEST_LEVEL(eExileC) )
				{
				case 2:
					QUEST_LEVEL(eExileC) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileC, 1 );
					return TRUE;
				case 4:
					NotifyQuestLevel( nUser, nEvent, eExileC, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST(eBukduB)
			{
				switch( QUEST_LEVEL(eBukduB) )
				{
				case 4:
					EMPTY_INVEN_TEST( 1 );
					if ( RemoveItem( nUser, 7321, 10 ) )
					{
						GiveItem( nUser, 8101, 1 );
						QUEST_LEVEL(eBukduB) = 5;
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduB, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eBukduB, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST(eBukduC)
			{
				switch ( QUEST_LEVEL(eBukduC) )
				{
				case 4:
					QUEST_LEVEL(eBukduC) = 5;
					pMob[nUser].AcquirePrana( 4000000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduC, 1 );
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eBukduC, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST( eScenario3E )		//	제사장 바난타
			{
				switch ( QUEST_LEVEL( eScenario3E ) )
				{
				case 15:
					QUEST_LEVEL(eScenario3E) = 16;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					QUEST_LEVEL(eQuestTemp1) = 0;
					QUEST_LEVEL(eQuestTemp2) = 0;
					QUEST_LEVEL(eQuestTemp3) = 0;
					QUEST_LEVEL(eQuestTemp4) = 0;
					return TRUE;
				case 16:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				case 17:
					EMPTY_INVEN_TEST(1);

					GiveItem( nUser, 8132, 1 );
					QUEST_LEVEL(eScenario3E) = 18;
					pMob[nUser].AcquirePrana( 1000000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 4 );
					return TRUE;
				case 18:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 5 );
					return TRUE;
				case 27:
					QUEST_LEVEL(eScenario3E) = 28;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 6 );
					return TRUE;
				}
				case 28:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 7 );
					return TRUE;
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCBhuvan:	// 교역관 부반에게 말을 걸었을때
	case eNPCBhuvan_1:
	case eNPCBhuvan_2:
		{
			CHECK_QUEST(eTutorialC)
			{	// TUTORIAL C ///////////////////////////////////////////////////////////////////////////
				int nInven = MAX_INVEN;
				short snDur = 0;
				g_ParamMgr.HT_bGetItemMaxDurability( 8043, &snDur );

				switch ( QUEST_LEVEL(eTutorialC) )
				{
				case 1: // 부반에게 처음 말을 걸었을때
					if ( ( nInven = GiveItem( nUser, 8043, 1 ) ) == MAX_INVEN )
					{
						NotifyDialog( nUser, 1 );
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
						return TRUE;
					}

					pMob[nUser].MOB.Inven[nInven].snDurability = 0;
					S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;
					sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_INVEN;
					sm.byIndex=nInven; sm.sitem=pMob[nUser].MOB.Inven[nInven];
					pUser[nUser].cSock.AddMessage((char*)&sm,sizeof(sm));

					GiveMoney( nUser, 100 );
					NotifyQuestLevel( nUser, nEvent, eTutorialC, 1 );
					QUEST_LEVEL(eTutorialC) = 2;
					SendQuestHistory( nUser );
					return TRUE;
				case 2: 
					// 기리카의 루차카를 받는다.
					// 아타누 암리타 3개를 받는다.
					if ( GetEmptyInven( nUser ) == MAX_INVEN || 
						( nInven = FindItem( nUser, 8043, 1 ) ) == MAX_INVEN || 
						pMob[nUser].MOB.Inven[nInven].snDurability != snDur ||
						!RemoveItem( nUser, 8043, 1 ) )
					{
						NotifyQuestLevel( nUser, nEvent, eTutorialC, 2 );
						return TRUE;
					}

					GiveItem( nUser, 5399, 1 );
					GiveItem( nUser, 7001, 10 );

					QUEST_LEVEL(eTutorialC) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eTutorialC );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					QUEST_LEVEL(eTutorialD) = 1;
					NotifyQuestLevel( nUser, nEvent, eTutorialC, 255 );
					SendQuestHistory( nUser );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, nEvent, eTutorialC, 255 );
					return TRUE;
				}
			}

			CHECK_QUEST_LEVEL(eScenarioC,8)
			{	// SCENARIO C ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenarioC) )
				{
				case 4:
					RemoveItem( nUser, 8010, 1 );
					QUEST_LEVEL(eScenarioC) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioC );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					QUEST_LEVEL(eScenarioD) = 1;

					GiveMoney( nUser, 2000 );
					switch( pMob[nUser].MOB.snTribe )
					{
					case TRIBE_NAGA:
					case TRIBE_KINNARA:
						GiveItem( nUser, 4029, 1 );
						break;
					case TRIBE_ASURA:
					case TRIBE_RAKSHASA:
						GiveItem( nUser, 4004, 1 );
						break;
					case TRIBE_YAKSA:
					case TRIBE_GANDHARVA:
						GiveItem( nUser, 4330, 1 );
						break;
					case TRIBE_DEVA:
					case TRIBE_GARUDA:
						GiveItem( nUser, 4114, 1 );
						break;
					}

					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenarioC, 255 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, nEvent, eScenarioC, QUEST_LEVEL(eScenarioC) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenarioF)
			{	// SCENARIO F ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenarioF) )
				{
				case 4:
					EMPTY_INVEN_TEST( 2 );

					RemoveItem( nUser, 8011, 1 );
					GiveItem( nUser, 8012, 1 );
					GiveItem( nUser, 6501, 1 );
					GiveMoney( nUser, 3000 );
					QUEST_LEVEL(eScenarioF) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioF );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					QUEST_LEVEL(eScenarioG) = 1;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenarioF, 255 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, nEvent, eScenarioF, QUEST_LEVEL(eScenarioF) );
					return TRUE;
				}
			}

			if ( QUEST_LEVEL(eScenarioH) != 0 
				&& QUEST_LEVEL(eScenarioH) != 255 
				&& ( pMob[nUser].MOB.snTribe == TRIBE_ASURA || pMob[nUser].MOB.snTribe == TRIBE_RAKSHASA ) )
			{	// SCENARIO H ///////////////////////////////////////////////////////////////////////////
				if ( pMob[nUser].MOB.byLevel < 15 )
				{
					NotifyQuestLevel( nUser, nEvent, 0, 0 );
					return TRUE;
				}

				if ( QUEST_LEVEL(eScenarioH) == 12 ) 
				{
					if ( RemoveItem( nUser, 8010, 1 ) )
					{
						GiveItem( nUser, 5003, 1 );
						GiveMoney( nUser, 5000 );
						pMob[nUser].AcquirePrana( 5000 );

						QUEST_LEVEL(eScenarioH) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioH );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						if ( QUEST_LEVEL(eScenarioI) == 0 ) QUEST_LEVEL(eScenarioI) = 1;
						SendQuestHistory( nUser );
					}
				}

				NotifyQuestLevel( nUser, nEvent, eScenarioH, QUEST_LEVEL(eScenarioH) );
				return TRUE;
			}
			CHECK_QUEST(eScenario3E)	//	교역관부반
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 28:
					QUEST_LEVEL(eScenario3E) = 29;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 29:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCRahul:
	case eNPCRahul_1:
	case eNPCRahul_2:
		{
			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCKaran: // 카란에게 말을 걸었을때.
	case eNPCKaran_1:
	case eNPCKaran_2:
		{
			CHECK_QUEST(eScenarioJ)
			{	// SCENARIO J ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenarioJ) )
				{
				case 1:
					NotifyQuestLevel( nUser, nEvent, eScenarioJ, 1 );
					return TRUE;
				case 2:
					if ( FindItem( nUser, 7110, 10 ) != MAX_INVEN )
					{
						EMPTY_INVEN_TEST( 2 );

						RemoveItem( nUser, 7110, 10 );
						QUEST_LEVEL(eScenarioJ) = 255;
						QUEST_LEVEL(eScenario2A) = 1;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioJ );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						GiveMoney( nUser, 10000 );
						pMob[nUser].AcquirePrana( 8000 );

						switch ( pMob[nUser].MOB.snTribe )
						{
						case TRIBE_NAGA:
						case TRIBE_KINNARA:
							GiveItem( nUser, 6606, 2 );
							break;
						case TRIBE_ASURA:
						case TRIBE_RAKSHASA:
							GiveItem( nUser, 6607, 2 );
							break;
						case TRIBE_YAKSA:
						case TRIBE_GANDHARVA:
							GiveItem( nUser, 6606, 2 );
							break;
						case TRIBE_DEVA:
						case TRIBE_GARUDA:
							GiveItem( nUser, 6609, 2 );
							break;
						}
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenarioJ, 255 );
					} 
					else
					{
						NotifyQuestLevel( nUser, nEvent, eScenarioJ, 2 );
					}
					return TRUE;
				default:
					NotifyQuestLevel( nUser, nEvent, eScenarioJ, QUEST_LEVEL(eScenarioJ) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario2G)
			{	// SCENARIO 2G ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2G) )
				{
				case 6:
					QUEST_LEVEL(eScenario2G) = 7;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario2G, 1 );
					return TRUE;
				case 7:
					if ( FindItem( nUser, 7008, 10 ) != MAX_INVEN && FindItem( nUser, 8046, 1 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 7008, 10 );
						RemoveItem( nUser, 8046, 1 );
						GiveItem( nUser, 8047, 1 );
						QUEST_LEVEL(eScenario2G) = 8;
						pMob[nUser].AcquirePrana( 50000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario2G, 255 );
					}
					else NotifyQuestLevel( nUser, nEvent, eScenario2G, 2 );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario2H)
			{	// SCENARIO 2H ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2H) )
				{
				case 2:
					if ( RemoveItem( nUser, 8026, 1 ) )
					{
						GiveItem( nUser, 8027, 1 );
						pMob[nUser].AcquirePrana( 100000 );
						GiveMoney( nUser, 30000 );
						QUEST_LEVEL(eScenario2H) = 4;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario2H, 1 );
					}
					else NotifyQuestLevel( nUser, nEvent, eScenario2H, 0 );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario2I)
			{	// SCENARIO 2I ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2I) )
				{
				case 1:
				case 2:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eScenario2I, QUEST_LEVEL(eScenario2I) );
					return TRUE;
				case 5:
					EMPTY_INVEN_TEST( 1 );

					GiveItem( nUser, 8031, 1 );
					QUEST_LEVEL(eScenario2I) = 6;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario2I, 4 );
					return TRUE;
				case 6:
					NotifyQuestLevel( nUser, nEvent, eScenario2I, 5 );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario3B)	//	카란
			{	
				switch ( QUEST_LEVEL(eScenario3B) )
				{
				case 12:
					QUEST_LEVEL(eScenario3B) = 13;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 1 );
					return TRUE;
				case 13:
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 2 );
					return TRUE;
				case 14:			//	우타라 파나카, 아스파라긴산
					if( FindItem( nUser, 7010, 10 ) != MAX_INVEN && FindItem( nUser, 8113, 1 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 7010, 10 );
						RemoveItem( nUser, 8113, 1 );
						GiveItem( nUser, 8112, 1);
						pMob[nUser].AcquirePrana( 1000000 );
						QUEST_LEVEL(eScenario3B) = 15;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3B, 4 );
					}	else
					{	NotifyQuestLevel( nUser, nEvent, eScenario3B, 2 );
					}
					return TRUE;
				case 15:
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 5 );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario3C)	//	카란
			{	
				switch ( QUEST_LEVEL(eScenario3C) )
				{
				case 12:
					QUEST_LEVEL(eScenario3C) = 13;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3C, 1 );
					return TRUE;
				case 13:
					if( RemoveItem( nUser, 7191, 20 ) )		//	마라원액20개
					{
						pMob[nUser].AcquirePrana( 1000000 );
						QUEST_LEVEL(eScenario3C) = 14;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3C, 4 );
					}	else
						NotifyQuestLevel( nUser, nEvent, eScenario3C, 2 );
					return TRUE;
				case 14:
					NotifyQuestLevel( nUser, nEvent, eScenario3C, 5 );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3E)	//	약재상 카란
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 32:
					QUEST_LEVEL(eScenario3E) = 33;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 33:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCAbbas:	// 압바스에게 말을 걸었을때
	case eNPCAbbas_1:
	case eNPCAbbas_2:
		{
			// 1차전직
			if ( pMob[nUser].MOB.byClass1 == 0 && pMob[nUser].MOB.byLevel >= 10 && QUEST_LEVEL(eChangeClass1) != 255 )
			{
				switch ( QUEST_LEVEL(eChangeClass1) )
				{
				case 0:
				case 1:
					QUEST_LEVEL(eChangeClass1) = 1;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eChangeClass1, 1 );
					return TRUE;
				case 2:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eChangeClass1, QUEST_LEVEL(eChangeClass1) );
					return TRUE;
				case 12:
					{
						EMPTY_INVEN_TEST( 5 );

						pMob[nUser].MOB.byClass1 = CLASS_LEVEL1;
						switch ( pMob[nUser].MOB.snTribe )
						{
						case TRIBE_NAGA:
						case TRIBE_KINNARA:
							pMob[nUser].MOB.byClass2 = CLASS_SATVAN;
							break;
						case TRIBE_ASURA:
						case TRIBE_RAKSHASA:
							pMob[nUser].MOB.byClass2 = CLASS_DHVANTA;
							break;
						case TRIBE_YAKSA:
						case TRIBE_GANDHARVA:
							pMob[nUser].MOB.byClass2 = CLASS_NIRVANA;
							break;
						case TRIBE_DEVA:
						case TRIBE_GARUDA:
							pMob[nUser].MOB.byClass2 = CLASS_MANTRIKA;
							break;
						}

						int nX=pMob[nUser].TargetX; int nZ=pMob[nUser].TargetY;
						MSG_CLASS m;
						m.wType = _MSG_CLASS;
						m.wPDULength = sizeof( MSG_CLASS ) - sizeof( HEADER );
						m.nID=nUser;
						m.byClass1=pMob[nUser].MOB.byClass1;
						m.byClass2=pMob[nUser].MOB.byClass2;
						GridMulticast(nX,nZ,(MSG_STANDARD*)&m,0,30);

						RemoveItem( nUser, 8107, 1 );
						switch( pMob[nUser].MOB.snTribe )
						{
						case TRIBE_NAGA:
						case TRIBE_KINNARA:
							GiveItem( nUser, 4048, 1 );
							break;
						case TRIBE_ASURA:
						case TRIBE_RAKSHASA:
							GiveItem( nUser, 4004, 1 );
							break;
						case TRIBE_YAKSA:
						case TRIBE_GANDHARVA:
							GiveItem( nUser, 4341, 1 );
							break;
						case TRIBE_DEVA:
						case TRIBE_GARUDA:
							GiveItem( nUser, 4122, 1 );
							break;
						}
						GiveItem( nUser, 7025, 10 );
						GiveItem( nUser, 6007, 1 );
						GiveItem( nUser, 6107, 1 );
						GiveItem( nUser, 6207, 1 );
						GiveItem( nUser, 6407, 1 );
						QUEST_LEVEL(eChangeClass1) = 255;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eChangeClass1, 255 );

						TriggerEvent( nUser, 56, pMob[nUser].TargetX, pMob[nUser].TargetY, g_irgGod[0][eTNClan_Brahma], 1300 );
						pMob[nUser].UpdateEquipmentPoints();
						pMob[nUser].NotifyUpdateUIMsg();

						//	길드원들에게 전직을 전송한다.
						DBUpdateGuildMember(nUser);

						sprintf( temp, "qst %s Complete 1st ChangeOfEmployeement from %d to %d", pMob[nUser].MOB.szName, pMob[nUser].MOB.snTribe, pMob[nUser].MOB.byClass2);
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					}

					return TRUE;
				default:
					NotifyQuestLevel( nUser, nEvent, 0, 0 );
					return TRUE;
				}
			}

			CHECK_QUEST(eTutorialB)
			{	// TUTORIAL B  ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eTutorialB) )
				{
				case 1:	// 압바스에게 처음 말을 걸었을때
					QUEST_LEVEL(eTutorialB) = 2;
					QUEST_LEVEL(eQuestTemp1) = pMob[nUser].MOB.byLevel;
					NotifyQuestLevel( nUser, nEvent, eTutorialB, 1 );
					SendQuestHistory( nUser );
					return TRUE;
				case 2:
					if ( pMob[nUser].MOB.byLevel > QUEST_LEVEL(eQuestTemp1) )	// 레벨이 1 이상 올랐으면
					{
						EMPTY_INVEN_TEST( 3 );

						pMob[nUser].AcquirePrana( 50 );
						GiveItem( nUser, 5699, 1 );
						GiveItem( nUser, 7001, 10 );
						IN_KOREA( GiveItem( nUser, 7029, 5 ) );
						QUEST_LEVEL(eQuestTemp1) = 0;
						QUEST_LEVEL(eTutorialB) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eTutorialB );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						QUEST_LEVEL(eTutorialC) = 1;
						NotifyQuestLevel( nUser, nEvent, eTutorialB, 255 );
						SendQuestHistory( nUser );
						return TRUE;
					}

					NotifyQuestLevel( nUser, nEvent, eTutorialB, 2 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, nEvent, eTutorialB, QUEST_LEVEL(eTutorialB) );
					return TRUE;
				}

			}

			CHECK_QUEST(eTutorialE)
			{	// TUTORIAL E ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eTutorialE) )
				{
				case 1:
					QUEST_LEVEL(eTutorialE) = 2;
					NotifyQuestLevel( nUser, nEvent, eTutorialE, 1 );
					SendQuestHistory( nUser );
					return TRUE;
				case 4:
					EMPTY_INVEN_TEST( 3 );

					QUEST_LEVEL(eMonsterKill1) = 0;
					QUEST_LEVEL(eTutorialE) = 255;
					QUEST_LEVEL(eScenarioA) = 1;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eTutorialE );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					pMob[nUser].AcquirePrana( 200 );
					GiveMoney( nUser, 500 );
					GiveItem( nUser, 5149, 1 );
					GiveItem( nUser, 7001, 10 );
					IN_KOREA( GiveItem( nUser, 7038, 1 ) );
					NotifyQuestLevel( nUser, nEvent, eTutorialE, 255 );
					SendQuestHistory( nUser );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, nEvent, eTutorialE, QUEST_LEVEL(eTutorialE) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenarioE)
			{	// SCENARIO E ///////////////////////////////////////////////////////////////////////////
				switch( QUEST_LEVEL(eScenarioE) )
				{
				case 1:
					//if ( QUEST_LEVEL(eScenarioD) != 255 )
					//{
						//QUEST_LEVEL(eScenarioD) = 255;
						//sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioD );
						//Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						//SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenarioE, 1 );
						return TRUE;
					//} 
				case 5:
				case 6:
					if ( RemoveItem( nUser, 8009, 2 ) ) 
					{
						QUEST_LEVEL(eScenarioF) = 1;
						QUEST_LEVEL(eScenarioE) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioE );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						pMob[nUser].AcquirePrana( 2000 );
						GiveItem( nUser, 7002, 10 );
						GiveItem( nUser, 7002, 10 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenarioE, 255 );
						return TRUE;
					} 
				}

				NotifyQuestLevel( nUser, nEvent, eScenarioE, QUEST_LEVEL(eScenarioE) );
				return TRUE;
			}

			if ( QUEST_LEVEL(eScenarioH) != 0 
				&& QUEST_LEVEL(eScenarioH) != 255
				&& ( pMob[nUser].MOB.snTribe == TRIBE_NAGA || pMob[nUser].MOB.snTribe == TRIBE_KINNARA ) )
			{	// SCENARIO H ///////////////////////////////////////////////////////////////////////////
				if ( pMob[nUser].MOB.byLevel < 15 )
				{
					NotifyQuestLevel( nUser, nEvent, 0, 0 );
					return TRUE;
				}


				if ( QUEST_LEVEL(eScenarioH) == 10 && RemoveItem( nUser, 7108, 10 ) ) 
				{
					GiveItem( nUser, 5003, 1 );
					GiveMoney( nUser, 5000 );
					pMob[nUser].AcquirePrana( 5000 );
					QUEST_LEVEL(eScenarioH) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioH );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					if ( QUEST_LEVEL(eScenarioI) == 0 ) QUEST_LEVEL(eScenarioI) = 1;
					SendQuestHistory( nUser );
				}

				NotifyQuestLevel( nUser, nEvent, eScenarioH, QUEST_LEVEL(eScenarioH) );
				return TRUE;
			}

			CHECK_QUEST(eScenarioI)
			{	// SCENARIO I ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenarioI) )
				{
				case 1:
				case 2:
					NotifyQuestLevel( nUser, nEvent, eScenarioI, QUEST_LEVEL(eScenarioI) );
					return TRUE;
				case 5:
					QUEST_LEVEL(eScenarioI) = 6;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenarioI, 4 );
					return TRUE;
				case 6:
					if ( FindItem( nUser, 7109, 10 ) != MAX_INVEN )
					{
						if ( GiveItem( nUser, 6608, 2 ) != MAX_INVEN )
						{
							RemoveItem( nUser, 7109, 10 );
							QUEST_LEVEL(eScenarioI) = 255;
							sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioI );
							Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
							if ( QUEST_LEVEL(eScenarioJ) == 0 ) QUEST_LEVEL(eScenarioJ) = 1;
							pMob[nUser].AcquirePrana( 7000 );
							GiveMoney( nUser, 7000 );
							SendQuestHistory( nUser );
							NotifyQuestLevel( nUser, nEvent, eScenarioI, 255 );
						}
						else NotifyDialog( nUser, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eScenarioI, 5 );
					}
					return TRUE;
				default:
					NotifyQuestLevel( nUser, nEvent, eScenarioI, QUEST_LEVEL(eScenarioI) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenarioG)
			{	// SCENARIO G ///////////////////////////////////////////////////////////////////////////
				switch( QUEST_LEVEL(eScenarioG) )
				{
				case 1:
					if ( FindItem( nUser, 8012, 1 ) != MAX_INVEN )
					{
						NotifyQuestLevel( nUser, nEvent, eScenarioG, 2 );
						return TRUE;
					}
					return TRUE;
				case 2:
					RemoveItem( nUser, 8013, 1 );
					QUEST_LEVEL(eScenarioG) = 255;
					if ( QUEST_LEVEL(eScenarioH) == 0 ) QUEST_LEVEL(eScenarioH) = 1;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioG );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					GiveItem( nUser, 6501, 1 );
					pMob[nUser].AcquirePrana( 3000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenarioG, 255 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, nEvent, eScenarioG, QUEST_LEVEL(eScenarioG) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario2B)
			{	// SCENARIO 2B ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2B) )
				{
				case 2:
					if ( RemoveItem( nUser, 8017, 1 ) )
					{
						QUEST_LEVEL(eScenario2B) = 4;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario2B, 1 );
					}
					else NotifyQuestLevel( nUser, nEvent, 0, 0 );
					return TRUE;
				case 4:
					NotifyQuestLevel( nUser, nEvent, eScenario2B, 2 );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario3B)
			{	// SCENARIO I ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario3B) )
				{
				case 7:
					QUEST_LEVEL(eScenario3B) = 8;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 1 );
					return TRUE;
				case 8:
					if ( FindItem( nUser, 7167, 20 ) != MAX_INVEN && FindItem( nUser, 7168, 30 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 7167, 20 );
						RemoveItem( nUser, 7168, 30 );
						pMob[nUser].AcquirePrana( 1000000 );
						QUEST_LEVEL(eScenario3B) = 9;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3B, 4 );
					}	else
					{	NotifyQuestLevel( nUser, nEvent, eScenario3B, 2 );
					}
					return TRUE;
				case 9:
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 5 );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3E)	//	수비대장 압바스
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 33:
					QUEST_LEVEL(eScenario3E) = 34;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 34:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCBibban: // 비브반에게 말을 걸었을때.
		{	
			CHECK_QUEST(eScenario2D)
			{	// SCENARIO 2D ///////////////////////////////////////////////////////////////////////////
				if ( pMob[nUser].MOB.byLevel < 30 )
				{
					NotifyQuestLevel( nUser, eNPCBibban, 0, 0 );
					return TRUE;
				}

				int nItem = MAX_INVEN;
				switch ( QUEST_LEVEL(eScenario2D) )
				{
				case 1:
					//if ( ( nItem = FindItem( nUser, 4291, 1) ) == MAX_INVEN ) break;
					NotifyQuestLevel( nUser, eNPCBibban, eScenario2D, 1 );
					return TRUE;
				case 4:
					EMPTY_INVEN_TEST( 1 );

					GiveItem( nUser, 8019, 1 );
					QUEST_LEVEL(eScenario2D) = 5;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCBibban, eScenario2D, 4 );
					return TRUE;
				case 6:
					EMPTY_INVEN_TEST( 2 );

					GiveItem( nUser, 6502, 1 );
					GiveItem( nUser, 7009, 20 );
					GiveMoney( nUser, 100000 );
					pMob[nUser].AcquirePrana( 100000 );
					QUEST_LEVEL(eScenario2D) = 255;
					QUEST_LEVEL(eScenario2E) = 1;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario2D );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCBibban, eScenario2D, 255 );
					return TRUE;

				default:
					NotifyQuestLevel( nUser, eNPCBibban, eScenario2D,  QUEST_LEVEL(eScenario2D) );
					return TRUE;
				}
			}

			CHECK_QUEST_LEVEL(eScenario2G,35)
			{	// SCENARIO 2G  ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2G) )
				{
				case 5:
					QUEST_LEVEL(eScenario2G) = 6;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCBibban, eScenario2G, 4 );
					return TRUE;
				case 6:
					NotifyQuestLevel( nUser, eNPCBibban, eScenario2G, 5 );
					return TRUE;
				case 8:
					if ( FindItem( nUser, 8047, 1 ) != MAX_INVEN)
					{
						QUEST_LEVEL(eScenario2G) = 9;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCBibban, eScenario2G, 6 );
					}
					else
					{
						NotifyQuestLevel( nUser, eNPCBibban, eScenario2G, 0 );
					}
					return TRUE;
				case 9:
					EMPTY_INVEN_TEST( 1 );

					if ( FindItem( nUser, 8047, 1 ) != MAX_INVEN && FindItem( nUser, 7013, 1 ) != MAX_INVEN && FindItem( nUser, 7119, 10 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 8047, 1 );
						RemoveItem( nUser, 7013, 1 );
						RemoveItem( nUser, 7119, 10 );
						GiveItem( nUser, 5749, 1 );
						IN_KOREA( GiveItem( nUser, 6804, 60 ) );
						QUEST_LEVEL(eScenario2G) = 255;
						QUEST_LEVEL(eScenario2H) = 1;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario2G );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						pMob[nUser].AcquirePrana( 50000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCBibban, eScenario2G, 255 );
					}
					else NotifyQuestLevel( nUser, eNPCBibban, eScenario2G, 7 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCBibban, eScenario2G, QUEST_LEVEL(eScenario2G) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario2H)
			{	// SCENARIO 2H ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2H) )
				{
				case 8:
					QUEST_LEVEL(eScenario2H) = 9;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCBibban, eScenario2H, 1 );
					return TRUE;
				case 9:
					NotifyQuestLevel( nUser, eNPCBibban, eScenario2H, 2 );
					return TRUE;
				case 10:
					if ( FindItem( nUser, 8002, 1 ) != MAX_INVEN && FindItem( nUser, 8048, 1 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 8002, 1 );
						RemoveItem( nUser, 8048, 1 );
						GiveItem( nUser, 8049, 1 );
						pMob[nUser].AcquirePrana( 100000 );
						GiveMoney( nUser, 50000 );
						QUEST_LEVEL(eScenario2H) = 11;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCBibban, eScenario2H, 255 );
					}
					else NotifyQuestLevel( nUser, eNPCBibban, eScenario2H, 0 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCBibban, eScenario2H, 0 );
					return TRUE;
				}
			}
			CHECK_QUEST(eJinaE)
			{
				switch ( QUEST_LEVEL(eJinaE) )
				{
				case 2:
					QUEST_LEVEL(eJinaE) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaE, 1 );
					return TRUE;
				case 4:
					if ( RemoveItem( nUser, 7161, 20 ) )
					{
						QUEST_LEVEL(eJinaE) = 5;
						GiveMoney( nUser, 50000 );
						pMob[nUser].AcquirePrana( 200000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eJinaE, 4 );
					}
					else NotifyQuestLevel( nUser, nEvent, eJinaE, 2 );
					return TRUE;
				case 5:
					if ( RemoveItem( nUser, 7162, 20 ) )
					{
						QUEST_LEVEL(eJinaE) = 6;
						GiveMoney( nUser, 75000 );
						pMob[nUser].AcquirePrana( 240000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eJinaE, 6 );
					}
					else NotifyQuestLevel( nUser, nEvent, eJinaE, 5 );
					return TRUE;
				}
			}
			CHECK_QUEST(eExileA)
			{
				switch( QUEST_LEVEL(eExileA) )
				{
				case 2:
					QUEST_LEVEL(eExileA) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileA, 1 );
					return TRUE;
				case 4:
					EMPTY_INVEN_TEST( 1 );
					if ( RemoveItem( nUser, 7131, 66 ) )
					{
						QUEST_LEVEL(eExileA) = 5;
						GiveItem( nUser, 8041, 1 );
						GiveMoney( nUser, 500000 );
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eExileA, 4 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eExileA, 2 );
					}
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eExileA, 5 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, eNPCBibban, 0, 0 );
			return TRUE;
		} break;
	case eNPCSaranew: // 사라뉴에게 말을 걸었을때.
		{
			CHECK_QUEST_LEVEL(eScenario2E, 35)
			{	// SCENARIO 2E  ///////////////////////////////////////////////////////////////////////////
				switch( QUEST_LEVEL(eScenario2E) )
				{
				case 1:
					if ( pMob[nUser].MOB.byLevel < 25 )
					{
						NotifyQuestLevel( nUser, eNPCSaranew, 0, 0 );
						return TRUE;
					}
					NotifyQuestLevel( nUser, eNPCSaranew, eScenario2E, 1 );
					return TRUE;
				case 2:
					if ( FindItem( nUser, 7119, 10 ) != MAX_INVEN )
					{
						EMPTY_INVEN_TEST( 2 );

						RemoveItem( nUser, 7119, 10 );
						GiveItem( nUser,8021, 1 );
						GiveItem( nUser,8022, 1 );
						QUEST_LEVEL(eScenario2E) = 4;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCSaranew, eScenario2E, 4 );
						return TRUE;
					}

					NotifyQuestLevel( nUser, eNPCSaranew, eScenario2E, 2 );
					return TRUE;
				case 4:
					NotifyQuestLevel( nUser, eNPCSaranew, eScenario2E, 5 );
					return TRUE;
				case 5:
					EMPTY_INVEN_TEST( 3 );

					if ( RemoveItem( nUser, 8023, 1 ) )
					{
						switch ( pMob[nUser].MOB.snTribe )
						{
						case TRIBE_NAGA:
						case TRIBE_KINNARA:
							GiveItem( nUser, 5275, 1 );
							break;
						case TRIBE_ASURA:
						case TRIBE_RAKSHASA:
							GiveItem( nUser, 5276, 1 );
							break;
						case TRIBE_YAKSA:
						case TRIBE_GANDHARVA:
							GiveItem( nUser, 5277, 1 );
							break;
						case TRIBE_DEVA:
						case TRIBE_GARUDA:
							GiveItem( nUser, 5278, 1 );
							break;
						}
						pMob[nUser].AcquirePrana( 100000 );
						GiveMoney( nUser, 50000 );
						IN_KOREA( GiveItem( nUser, 6802, 60 ) );
						IN_KOREA( GiveItem( nUser, 6801, 60 ) );
						QUEST_LEVEL(eScenario2E) = 255;
						if ( QUEST_LEVEL(eScenario2F) == 0 ) QUEST_LEVEL(eScenario2F) = 1;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario2E );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCSaranew, eScenario2E, 255 );
						return TRUE;
					}

					NotifyQuestLevel( nUser, eNPCSaranew, eScenario2E, 0 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCSaranew, eScenario2E, QUEST_LEVEL(eScenario2E) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario2G)
			{	// SCENARIO 2G ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2G) )
				{
				case 2:
					QUEST_LEVEL(eScenario2G) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCSaranew, eScenario2G, 1 );
					return TRUE;
				case 4:
					EMPTY_INVEN_TEST( 1 );

					if ( FindItem( nUser, 7115, 5 ) != MAX_INVEN && pMob[nUser].MOB.nRupiah >= 12500 )
					{
						RemoveItem( nUser, 7115, 5 );
						GiveMoney( nUser, -12500 );
						GiveItem( nUser, 8046, 1);
						QUEST_LEVEL(eScenario2G) = 5;
						pMob[nUser].AcquirePrana( 50000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCSaranew, eScenario2G, 255 );
						return TRUE;
					}

					NotifyQuestLevel( nUser, eNPCSaranew, eScenario2G, 2 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCSaranew, eScenario2G, 0 );
					return TRUE;
				}
			}

			CHECK_QUEST_LEVEL(eScenario2H, 40)
			{	// SCENARIO 2H ///////////////////////////////////////////////////////////////////////////

				switch ( QUEST_LEVEL(eScenario2H) )
				{
				case 4:
					if ( FindItem( nUser, 8027, 1 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 8027, 1 );
						GiveMoney( nUser, 30000 );
						pMob[nUser].AcquirePrana( 100000 );
						QUEST_LEVEL(eScenario2H) = 5;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCSaranew, eScenario2H, 4 );
						return TRUE;
					}

					NotifyQuestLevel( nUser, eNPCSaranew, 0, 0 );
					return TRUE;
				case 11:
					QUEST_LEVEL(eScenario2H) = 12;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCSaranew, eScenario2H, 6 );
					return TRUE;
				case 12:
					NotifyQuestLevel( nUser, eNPCSaranew, eScenario2H, 7 );
					return TRUE;
				case 13:
					if ( FindItem( nUser, 8004, 1 ) != MAX_INVEN && FindItem( nUser, 8049, 1 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eScenario2H) = 14;
						SendQuestHistory( nUser );
						RemoveItem( nUser, 8004, 1 );
						RemoveItem( nUser, 8049, 1 );
						GiveItem( nUser, 8050, 1 );
						pMob[nUser].AcquirePrana( 100000 );
						GiveMoney( nUser, 50000 );
						NotifyQuestLevel( nUser, eNPCSaranew, eScenario2H, 255 );
					}
					else NotifyQuestLevel( nUser, eNPCSaranew, 0, 0 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCSaranew, eScenario2H, QUEST_LEVEL(eScenario2H) );
					return TRUE;
				}
			}

			CHECK_QUEST(eChangeClass2B)
			{	// 2nd Change class Quest ////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eChangeClass2B) )
				{
				case 5:
					QUEST_LEVEL(eChangeClass2B) = 6;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCSaranew, eChangeClass2B, 1 );
					return TRUE;
				case 6:
					EMPTY_INVEN_TEST( 1 );

					if ( RemoveItem( nUser, 7146, 10 ) )
					{
						QUEST_LEVEL(eChangeClass2B) = 7;
						GiveItem( nUser, 8077, 1 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCSaranew, eChangeClass2B, 255 );
					}
					else
					{
						NotifyQuestLevel( nUser, eNPCSaranew, eChangeClass2B, 2 );
					}
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCSaranew, eChangeClass2B, 0 );
					return TRUE;
				}
			}

			if ( QUEST_LEVEL(eJinaD) == 6 )
			{
				if ( !RemoveItem( nUser, 8083, 1 ) ) return TRUE;
				QUEST_LEVEL(eJinaD) = 7;
				SendQuestHistory( nUser );
				NotifyQuestLevel( nUser, nEvent, eJinaD, 1 );
				return TRUE;
			}

			CHECK_QUEST(eJinaE)
			{
				switch ( QUEST_LEVEL(eJinaE) )
				{
				case 12:
					if ( RemoveItem( nUser, 8084, 1 ) )
					{
						QUEST_LEVEL(eJinaE) = 13;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eJinaE, 1 );
					}
					else NotifyQuestLevel( nUser, nEvent, 0, 0 );
					return TRUE;
				case 13:
					NotifyQuestLevel( nUser, nEvent, eJinaE, 2 );
					return TRUE;
				case 14:
					QUEST_LEVEL(eJinaE) = 15;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaE, 4 );
					return TRUE;
				}
			}
			CHECK_QUEST(eBukduB)
			{
				switch( QUEST_LEVEL(eBukduB) )
				{
				case 7:
					EMPTY_INVEN_TEST( 1 );
					if ( RemoveItem( nUser, 7325, 10 ) )
					{
						GiveItem( nUser, 8104, 1 );
						QUEST_LEVEL(eBukduB) = 8;
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduB, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 8:
					NotifyQuestLevel( nUser, nEvent, eBukduB, 2 );
					return TRUE;
				}
			}
			//	재단사 사라뉴
			CHECK_QUEST( eScenario3E )		
			{
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 18:
					QUEST_LEVEL(eScenario3E) =19;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 19:
					EMPTY_INVEN_TEST(1);

					if( RemoveItem( nUser, 7135, 30) )		//	나가무드라의 용의 비늘
					{
						GiveItem( nUser, 8133, 1 );
						QUEST_LEVEL(eScenario3E) = 20;
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3E, 4 );
					}	else
						NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				case 20:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 5 );
					return TRUE;
				case 35:
					QUEST_LEVEL(eScenario3E) =36;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 6 );
					return TRUE;
				case 36:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 7 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, eNPCSaranew, 0, 0 );
			return TRUE;
		} break;
	case eNPCNara: // 나라에게 말을 걸었을때.
		{
			CHECK_QUEST(eScenario2F)
			{	// SCENARIO 2F ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2F) )
				{
				case 1:
					if ( FindItem( nUser, 8045, 1 ) == MAX_INVEN )
					{
						NotifyQuestLevel( nUser, eNPCNara, 0, 0 );
					}
					else
					{
						NotifyQuestLevel( nUser, eNPCNara, eScenario2F, 1 );
					}
					return TRUE;
				case 2:
					EMPTY_INVEN_TEST( 1 );

					if ( ( FindItem( nUser, 7118, 10 ) != MAX_INVEN ) 
						&& ( FindItem( nUser, 8045, 1 ) != MAX_INVEN ) 
						&& ( pMob[nUser].MOB.nRupiah >= 10000 ) )
					{
						RemoveItem( nUser, 7118, 10 );
						for ( int i = 0 ; i < 10 ; i++ ) RemoveItem( nUser, 8045, 1 );
						GiveItem( nUser, 6222, 1 );
						GiveMoney( nUser, -10000 );
						QUEST_LEVEL(eScenario2F) = 255;
						if ( QUEST_LEVEL(eScenario2G) == 0 ) QUEST_LEVEL(eScenario2G) = 1;
						pMob[nUser].AcquirePrana( 50000 );
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario2F );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						SendQuestHistory( nUser );
					}
					else
					{
						NotifyQuestLevel( nUser, eNPCNara, eScenario2F, 2 );
						return TRUE;
					}

					NotifyQuestLevel( nUser, eNPCNara, eScenario2F, 255 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCNara, eScenario2F, QUEST_LEVEL(eScenario2F) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario2H)
			{	// SCENARIO 2H ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2H) )
				{
				case 5:
					QUEST_LEVEL(eScenario2H) = 6;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCNara, eScenario2H, 1 );
					return TRUE;
				case 6:
					NotifyQuestLevel( nUser, eNPCNara, eScenario2H, 2 );
					return TRUE;
				case 7:
					EMPTY_INVEN_TEST( 1 );

					if ( RemoveItem( nUser, 8001, 1 ) )
					{
						QUEST_LEVEL(eScenario2H) = 8;
						GiveItem( nUser, 8048, 1 );
						GiveMoney( nUser, 50000 );
						pMob[nUser].AcquirePrana( 100000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCNara, eScenario2H, 255 );
					}
					else NotifyQuestLevel( nUser, eNPCNara, eScenario2H, 0 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCNara, eScenario2H, 0 );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario2I)
			{	// SCENARIO 2I ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2I) )
				{
				case 4:
					if ( RemoveItem( nUser, 8039, 1 ) )
					{
						pMob[nUser].AcquirePrana( 150000 );
						QUEST_LEVEL(eScenario2I) = 5;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCNara, eScenario2I, 1 );
					}
					else NotifyQuestLevel( nUser, eNPCNara, eScenario2I, 0 );
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, eNPCNara, eScenario2I, 2 );
					return TRUE;
				case 7:
					if ( FindItem( nUser, 8031, 1 ) != MAX_INVEN && FindItem( nUser, 8030, 1 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 8031, 1 );
						RemoveItem( nUser, 8030, 1 );
						GiveItem( nUser, 8035, 1 );
						pMob[nUser].AcquirePrana( 150000 );
						QUEST_LEVEL(eScenario2I) = 8;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCNara, eScenario2I, 4 );
					}
					else NotifyQuestLevel( nUser, eNPCNara, eScenario2I, 0 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCNara, eScenario2I, 0 );
					return TRUE;
				}
			}

			CHECK_QUEST(eJinaB)
			{
				if ( QUEST_LEVEL(eJinaB) == 13 )
				{
					EMPTY_INVEN_TEST( 2 );

					if ( RemoveItem( nUser, 8081, 1 ) )
					{
						GiveItem( nUser, 6197, 1 );
						IN_KOREA( GiveItem( nUser, 6802, 60 ) );
						IN_KOREA( GiveItem( nUser, 6821, 60 ) );
						pMob[nUser].AcquirePrana( 100000 );
						QUEST_LEVEL( eJinaB ) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eJinaB );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						QUEST_LEVEL( eJinaC ) = 1;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eJinaB, 1 );
						return TRUE;
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
				}
			}
			CHECK_QUEST(eScenario3E)	//	보석상 나라
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 36:
					QUEST_LEVEL(eScenario3E) = 37;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 37:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, eNPCNara, 0, 0 );
			return TRUE;
		} break;
	case eNPCAmar: // 아마르에게 말을 걸었을때.
		{	
			CHECK_QUEST(eChangeClass2A)
			{	// 2nd Class Change ///////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eChangeClass2A) )
				{
				case 2:
					RemoveItem( nUser, 8070, 1 );
					QUEST_LEVEL(eChangeClass2A) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCAmar, eChangeClass2A, 1 );
					return TRUE;
				case 4:
					NotifyQuestLevel( nUser, eNPCAmar, eChangeClass2A, 2 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCAmar, eChangeClass2A, 0 );
					return TRUE;
				}
			}

			if ( QUEST_LEVEL(eScenario2A) != 255 && QUEST_LEVEL(eScenarioJ) == 255 )
			{	// SCENARIO 2A ///////////////////////////////////////////////////////////////////////////
				if ( pMob[nUser].MOB.byLevel < 20 ) 
				{
					NotifyQuestLevel( nUser, eNPCAmar, 0, 0 );
					return TRUE;
				}

				if ( QUEST_LEVEL(eScenario2A) == 0 ) QUEST_LEVEL(eScenario2A) = 1;

				switch ( QUEST_LEVEL(eScenario2A) )
				{
				case 1:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2A, 1 );
					return TRUE;
				case 2:
				case 4:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2A, 2 );
					return TRUE;
				case 5:
					QUEST_LEVEL(eScenario2A) = 6;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2A, 4 );
					return TRUE;
				case 6:
				case 7:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2A, 5 );
					return TRUE;
				case 8:
					EMPTY_INVEN_TEST( 2 );

					GiveItem( nUser, 7008, 20 );
					IN_KOREA( GiveItem( nUser, 7034, 1 ) );
					GiveMoney( nUser, 30000 );
					pMob[nUser].AcquirePrana( 20000 );
					QUEST_LEVEL(eScenario2A) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario2A );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					QUEST_LEVEL(eScenario2B) = 1;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2A, 255);
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2A, QUEST_LEVEL(eScenario2A) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario2B)
			{	// SCENARIO 2B ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2B) )
				{
				case 1:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2B, 1 );
					return TRUE;
				case 2:
				case 4:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2B, 2 );
				case 5:
					EMPTY_INVEN_TEST( 1 );

					if ( RemoveItem( nUser, 8018 ,1) == FALSE )
					{
						NotifyQuestLevel( nUser, eNPCAmar, 0, 0 );
						return TRUE;
					}
					GiveItem( nUser, 5503, 1 );
					GiveMoney( nUser, 50000 );
					QUEST_LEVEL(eScenario2B) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario2B );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					QUEST_LEVEL(eScenario2B1) = 1;
					pMob[nUser].AcquirePrana( 20000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2B, 255 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2B, QUEST_LEVEL(eScenario2B) );
					return TRUE;
				}

				NotifyQuestLevel( nUser, eNPCAmar, 0, 0 );
				return TRUE;
			}

			CHECK_QUEST_LEVEL(eScenario2C,25)
			{	// SCENARIO 2C ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2C) )
				{
				case 2:
				case 4:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2C, 2 );
					return TRUE;
				case 5:
					EMPTY_INVEN_TEST( 1 );

					GiveMoney( nUser, 30000 );
					GiveItem( nUser, 6502, 1 );
					QUEST_LEVEL(eScenario2C) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario2C );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					QUEST_LEVEL(eScenario2D) = 1;
					pMob[nUser].AcquirePrana( 20000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2C, 255 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2C, QUEST_LEVEL(eScenario2C) );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario2H)
			{	// SCENARIO 2H ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario2H) )
				{
				case 14:
					QUEST_LEVEL(eScenario2H) = 15;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2H, 1 );
					return TRUE;
				case 15:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2H, 2 );
					return TRUE;
				case 16:
					if ( FindItem( nUser, 8003, 1 ) != MAX_INVEN && FindItem( nUser, 8050, 1 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 8003, 1 );
						RemoveItem( nUser, 8050, 1 );
						GiveItem( nUser, 6441, 1 );
						GiveMoney( nUser, 50000 );
						QUEST_LEVEL(eScenario2H) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario2H );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						QUEST_LEVEL(eScenario2I) = 1;
						pMob[nUser].AcquirePrana( 100000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCAmar, eScenario2H, 255 );
					}
					else NotifyQuestLevel( nUser, eNPCAmar, eScenario2H, 0 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario2H, 0 );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3B)
			{	// 2nd Class Change ///////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenario3B) )
				{
				case 5:
					QUEST_LEVEL(eScenario3B) = 6;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCAmar, eScenario3B, 1 );
					return TRUE;
				case 6:		//	그흐라요기의 고대 주술서
					if ( RemoveItem( nUser, 7134, 30 ) )
					{
						pMob[nUser].AcquirePrana( 1000000 );
						QUEST_LEVEL(eScenario3B) = 7;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3B, 4 );
					}	else
					{	NotifyQuestLevel( nUser, nEvent, eScenario3B, 2 );
					}
					return TRUE;
				case 7:
					NotifyQuestLevel( nUser, eNPCAmar, eScenario3B, 5 );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3E)	//	용장 아마르
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 34:
					QUEST_LEVEL(eScenario3E) = 35;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 35:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, eNPCAmar, 0, 0 );
			return TRUE;
		} break;
	case eNPCMahomat: // 마호멧에게 말을 걸었을때.
		{	// SCENARIO 2B-1 ///////////////////////////////////////////////////////////////////////////
			CHECK_QUEST(eScenario2B1)
			{
				switch( QUEST_LEVEL(eScenario2B1) )
				{
				case 4:
					EMPTY_INVEN_TEST( 1 );

					GiveItem( nUser, 6196, 1 );
					GiveMoney( nUser, 30000 );
					pMob[nUser].AcquirePrana( 20000 );
					QUEST_LEVEL(eScenario2B1) = 255;
					QUEST_LEVEL(eScenario2C) = 1;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario2B1 );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCMahomat, eScenario2B1, 255 );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCMahomat, eScenario2B1, QUEST_LEVEL(eScenario2B1) );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, eNPCMahomat, 0, 0 );
			return TRUE;
		} break;
	case eNPCBaba: // 바바에게 말을 걸었을때.
		{
			CHECK_QUEST( eJinaB )
			{
				switch ( QUEST_LEVEL(eJinaB) )
				{
				case 6:
					QUEST_LEVEL(eJinaB) = 7;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaB, 1 );
					return TRUE;
				case 10:
					if ( RemoveItem( nUser, 8080, 1 ) )
					{
						pMob[nUser].AcquirePrana( 200000 );
						QUEST_LEVEL(eJinaB) = 11;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eJinaB, 2 );
					}
					else
					{
						NotifyQuestLevel( nUser, 0, 0, 0 );
					}
					return TRUE;
				case 12:
					QUEST_LEVEL(eJinaB) = 13;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaB, 4 );
					return TRUE;
				}
			}
			CHECK_QUEST( eJinaC )
			{
				switch ( QUEST_LEVEL(eJinaC) )
				{
				case 10:
					QUEST_LEVEL(eJinaC) = 11;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaC, 1 );
					return TRUE;
				case 11:
					NotifyQuestLevel( nUser, nEvent, eJinaC, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST_LEVEL( eJinaD, 51 )
			{
				switch ( QUEST_LEVEL(eJinaD) )
				{
				case 1:
					NotifyQuestLevel( nUser, nEvent, eJinaD, 1 );
					return TRUE;
				case 2:
					NotifyQuestLevel( nUser, nEvent, eJinaD, 2 );
					return TRUE;
				case 3:
					NotifyQuestLevel( nUser, nEvent, eJinaD, 3 );
					return TRUE;
				}
			}
			NotifyQuestLevel( nUser, eNPCBaba, 0, 0 );
		} break;
	case eNPCKananda: // 카난다에게 말을 걸었을때.
	case eNPCKananda_1:
	case eNPCKananda_2:
		{	// SCENARIO E  ///////////////////////////////////////////////////////////////////////////
			if ( QUEST_LEVEL(eScenarioE) != 2 && QUEST_LEVEL(eScenarioE) != 4 )
			{
				NotifyQuestLevel( nUser, nEvent, 0, 0 );
				return TRUE;
			}

			if ( QUEST_LEVEL(eQuestTemp1) != 1 )
			{
				RemoveItem( nUser, 8008, 1 );
				GiveItem( nUser, 8009, 1 );
				QUEST_LEVEL(eScenarioE) = ( QUEST_LEVEL(eScenarioE) == 2 ) ? 4 : 5;
				//if ( QUEST_LEVEL(eScenarioE) == 5 ) QUEST_LEVEL(eScenarioE) = 6;
				QUEST_LEVEL(eQuestTemp1) = ( QUEST_LEVEL(eScenarioE) == 5 ) ? 255 : 1;
				SendQuestHistory( nUser );
				NotifyQuestLevel( nUser, nEvent, eScenarioE, 1 );
				return TRUE;
			}
			else
			{
				NotifyQuestLevel( nUser, nEvent, eScenarioE, 2 );
				return TRUE;
			}
		} break;
	case eNPCBadur: // 바두르에게 말을 걸었을때.
	case eNPCBadur_1:
	case eNPCBadur_2:
		{	// SCENARIO E  ///////////////////////////////////////////////////////////////////////////
			if ( QUEST_LEVEL(eScenarioE) != 2 && QUEST_LEVEL(eScenarioE) != 4 )
			{
				NotifyQuestLevel( nUser, nEvent, 0, 0 );
				return TRUE;
			}

			if ( QUEST_LEVEL(eQuestTemp1) != 2 )
			{
				RemoveItem( nUser, 8008, 1 );
				GiveItem( nUser, 8009, 1 );
				QUEST_LEVEL(eScenarioE) = ( QUEST_LEVEL(eScenarioE) == 2 ) ? 4 : 5;
				//if ( QUEST_LEVEL(eScenarioE) == 5 ) QUEST_LEVEL(eScenarioE) = 6;
				QUEST_LEVEL(eQuestTemp1) = ( QUEST_LEVEL(eScenarioE) == 5 ) ? 255 : 2;
				SendQuestHistory( nUser );
				NotifyQuestLevel( nUser, nEvent, eScenarioE, 1 );
				return TRUE;
			}
			else
			{
				NotifyQuestLevel( nUser, nEvent, eScenarioE, 2 );
				return TRUE;
			}
		} break;
	case eNPCLostBoy: // 길잃은소년에게 말을 걸었을때.
	case eNPCLostBoy_1:
	case eNPCLostBoy_2:
		{
			CHECK_QUEST(eScenarioG)
			{	// SCENARIO G ///////////////////////////////////////////////////////////////////////////
				switch ( QUEST_LEVEL(eScenarioG) )
				{
				case 1:
					if ( FindItem( nUser, 8012, 1 ) == MAX_INVEN )
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
						return TRUE;
					}
					NotifyQuestLevel( nUser, nEvent, eScenarioG, QUEST_LEVEL(eScenarioG) );
					return TRUE;
				default:
					NotifyQuestLevel( nUser, nEvent, eScenarioG, QUEST_LEVEL(eScenarioG) );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCMonk: // 수행승려에게 말을 걸었을때.
		{
			CHECK_QUEST(eExileC)
			{
				switch ( QUEST_LEVEL(eExileC) )
				{
				case 4:
					QUEST_LEVEL(eExileC) = 5;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileC, 1 );
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eExileC, 2 );
					return TRUE;
				case 57:
					EMPTY_INVEN_TEST( 4 );
					GiveItem( nUser, 7360, 4 );
					pMob[nUser].AcquirePrana( 10000000 );
					QUEST_LEVEL(eExileC) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eExileC );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					QUEST_LEVEL(eExileD) = 1;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileC, 255 );
					return TRUE;
				}
			}
			CHECK_QUEST(eBukduB)
			{
				switch( QUEST_LEVEL(eBukduB) )
				{
				case 6:
					EMPTY_INVEN_TEST( 1 );
					if ( RemoveItem( nUser, 7324, 10 ) )
					{
						GiveItem( nUser, 8103, 1 );
						QUEST_LEVEL(eBukduB) = 7;
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduB, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 7:
					NotifyQuestLevel( nUser, nEvent, eBukduB, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, eNPCMonk, 0, 0 );
			return TRUE;
		} break;
	case eNPCShankar: // 샹카르에게 말을 걸었을때.
		{
			NotifyQuestLevel( nUser, eNPCShankar, 0, 0 );
			return TRUE;
		} break;
	case eNPCPriest: // 여사제에게 말을 걸었을때.
		{
			NotifyQuestLevel( nUser, eNPCPriest, 0, 0 );
			return TRUE;
		} break;
	case eNPCWanttaopo:	// 왕따오포에게 말을 걸었을때.
		{
			CHECK_QUEST(eChangeClass2D)
			{
				switch ( QUEST_LEVEL(eChangeClass2D) )
				{
				case 1:
					QUEST_LEVEL(eChangeClass2D) = 2;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCWanttaopo, eChangeClass2D, 1 );
					return TRUE;
				case 2:
					NotifyQuestLevel( nUser, eNPCWanttaopo, eChangeClass2D, 2 );
					return TRUE;
				case 4:
					if ( GiveItem( nUser, 8069, 1 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eChangeClass2D) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eChangeClass2D );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCWanttaopo, eChangeClass2D, 255 );
					}
					else NotifyDialog( nUser, 1 );
					return TRUE;
				}
			}
			CHECK_QUEST(eJinaA)
			{
				switch( QUEST_LEVEL(eJinaA) )
				{
				case 10:
					if ( RemoveItem( nUser, 8009, 1) )
					{
						QUEST_LEVEL(eJinaA) = 11;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eJinaA, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 11:
					NotifyQuestLevel( nUser, nEvent, eJinaA, 2 );
					return TRUE;
				case 12:
					EMPTY_INVEN_TEST( 3 );

					if ( RemoveItem( nUser, 8079, 1 ) )
					{
						GiveItem( nUser, 7229, 40 );
						GiveItem( nUser, 7232, 40 );
						IN_KOREA( GiveItem( nUser, 6809, 60 ) );
						GiveMoney( nUser, 50000 );
						pMob[nUser].AcquirePrana( 200000 );
						QUEST_LEVEL(eJinaA) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eJinaA );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						QUEST_LEVEL(eJinaB) = 1;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eJinaA, 255 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				}
			}
			CHECK_QUEST(eJinaB)
			{
				switch ( QUEST_LEVEL(eJinaB) )
				{
				case 2:
					QUEST_LEVEL(eJinaB) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaB, 1 );
					return TRUE;
				case 4:
					if ( FindItem( nUser, 7154, 20 ) != MAX_INVEN && FindItem( nUser, 7118, 20 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eJinaB) = 5;
						SendQuestHistory( nUser );
						GiveMoney( nUser, 50000 );
						RemoveItem( nUser, 7154, 20 );
						RemoveItem( nUser, 7118, 20 );
						pMob[nUser].AcquirePrana( 200000 );
						NotifyQuestLevel( nUser, nEvent, eJinaB, 4 );
					}
					else NotifyQuestLevel( nUser, nEvent, eJinaB, 2 );
					return TRUE;
				case 5:
					if ( FindItem( nUser, 7154, 30 ) != MAX_INVEN && FindItem( nUser, 7118, 30 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eJinaB) = 6;
						SendQuestHistory( nUser );
						GiveMoney( nUser, 75000 );
						RemoveItem( nUser, 7154, 30 );
						RemoveItem( nUser, 7118, 30 );
						pMob[nUser].AcquirePrana( 300000 );
						NotifyQuestLevel( nUser, nEvent, eJinaB, 6 );
					}
					else NotifyQuestLevel( nUser, nEvent, eJinaB, 5 );
					return TRUE;
				case 7:
					QUEST_LEVEL(eJinaB) = 8;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaB, 7 );
					return TRUE;
				}
			}
			CHECK_QUEST(eBukduA)
			{
				switch ( QUEST_LEVEL(eBukduA) )
				{
				case 7:
					QUEST_LEVEL(eBukduA) = 8;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduA, 1 );
					return TRUE;
				case 8:
					NotifyQuestLevel( nUser, nEvent, eBukduA, 2 );
					return TRUE;
				case 9:
					EMPTY_INVEN_TEST( 1 );
					GiveItem( nUser, 8099, 1 );
					QUEST_LEVEL(eBukduA) = 10;
					pMob[nUser].AcquirePrana( 1000000 );
                    SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduA, 4 );
					return TRUE;
				case 10:
					NotifyQuestLevel( nUser, nEvent, eBukduA, 5 );
					return TRUE;
				}
			}
			CHECK_QUEST(eBukduB)
			{
				switch ( QUEST_LEVEL(eBukduB) )
				{
				case 9:
					EMPTY_INVEN_TEST( 1 );
					if ( RemoveItem( nUser, 7328, 10 ) )
					{
						GiveItem( nUser, 8106, 1 );
						QUEST_LEVEL(eBukduB) = 10;
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduB, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 10:
					NotifyQuestLevel( nUser, nEvent, eBukduB, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, eNPCWanttaopo, 0, 0 );
			return TRUE;
		} break;
	case eNPCIttungtasheo:	// 이떵따셔에게 말을 걸었을때.
		{
			CHECK_QUEST(eChangeClass2A)
			{
				switch ( QUEST_LEVEL(eChangeClass2A) )
				{
				case 1:
					if ( GiveItem( nUser, 8070, 1 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eChangeClass2A) = 2;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCIttungtasheo, eChangeClass2A, 1 );
					}
					else NotifyDialog( nUser, 1 );
					return TRUE;
				case 2:
					NotifyQuestLevel( nUser, eNPCIttungtasheo, eChangeClass2A, 2 );
					return TRUE;
				case 5:
					{
						int nItemCount = 0;
						if ( FindItem( nUser, 8063, 1 ) != MAX_INVEN ) nItemCount++;
						if ( FindItem( nUser, 8064, 1 ) != MAX_INVEN ) nItemCount++;
						if ( FindItem( nUser, 8065, 1 ) != MAX_INVEN ) nItemCount++;

						if ( nItemCount >= 2 )
						{
							RemoveItem( nUser, 8063, 1 );
							RemoveItem( nUser, 8064, 1 );
							RemoveItem( nUser, 8065, 1 );
							GiveItem( nUser, 8066, 1 );
							QUEST_LEVEL(eChangeClass2A) = 255;
							sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eChangeClass2A );
							Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
							SendQuestHistory( nUser );
							NotifyQuestLevel( nUser, eNPCIttungtasheo, eChangeClass2A, 255 );
						}
						else
						{
							NotifyQuestLevel( nUser, eNPCIttungtasheo, eChangeClass2A, 2 );
						}
					}
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCIttungtasheo, 0, 0 );
					return TRUE;
				}
			}
			CHECK_QUEST(eJinaA)
			{
				switch ( QUEST_LEVEL(eJinaA) )
				{
				case 2:
					QUEST_LEVEL(eJinaA) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaA, 1 );
					return TRUE;
				case 4:
				case 5:
					NotifyQuestLevel( nUser, nEvent, eJinaA, 2 );
					return TRUE;
				case 6:
					EMPTY_INVEN_TEST( 3 );

					QUEST_LEVEL(eJinaA) = 7;
					SendQuestHistory( nUser );
					GiveItem( nUser, 7010, 60 );
					GiveMoney( nUser, 50000 );
					pMob[nUser].AcquirePrana( 200000 );
					NotifyQuestLevel( nUser, nEvent, eJinaA, 4 );
					return TRUE;
				case 7:
					NotifyQuestLevel( nUser, nEvent, eJinaA, 5 );
					return TRUE;
				case 8:
					QUEST_LEVEL(eJinaA) = 9;
					SendQuestHistory( nUser );
					GiveMoney( nUser, 100000 );
					pMob[nUser].AcquirePrana( 200000 );
					NotifyQuestLevel( nUser, nEvent, eJinaA, 6 );
					return TRUE;
				}
			}
			CHECK_QUEST(eJinaE)
			{
				switch ( QUEST_LEVEL(eJinaE) )
				{
				case 6:
					QUEST_LEVEL(eJinaE) = 7;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaE, 1 );
					return TRUE;
				case 7:
				case 8:
					NotifyQuestLevel( nUser, nEvent, eJinaE, 2 );
					return TRUE;
				case 9:
					QUEST_LEVEL(eJinaE) = 10;
					SendQuestHistory( nUser );
					pMob[nUser].AcquirePrana( 240000 );
					NotifyQuestLevel( nUser, nEvent, eJinaE, 4 );
					return TRUE;
				case 15:
					if ( RemoveItem( nUser, 8087, 1 ) )
					{
						GiveItem( nUser, 6097, 1 );
						QUEST_LEVEL(eJinaE) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eJinaE );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						SendQuestHistory( nUser );
						pMob[nUser].AcquirePrana( 300000 );
						NotifyQuestLevel( nUser, nEvent, eJinaE, 5 );

						QUEST_LEVEL(eExileA) = 1;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eExileA, 1 );
					}
					else NotifyDialog( nUser, 1 );
					return TRUE;
				}
			}
			CHECK_QUEST(eExileB)
			{
				switch( QUEST_LEVEL(eExileB) )
				{
				case 5:
					QUEST_LEVEL(eExileB) = 6;
					pMob[nUser].AcquirePrana( 300000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileB, 1);
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, eNPCIttungtasheo, 0, 0 );
			return TRUE;
		} break;
	case eNPCJangno:
		{
			if ( QUEST_LEVEL(eChangeClass2) == 0 && pMob[nUser].MOB.byClass1 != 0 )
			{
				NotifyQuestLevel( nUser, eNPCJangno, eChangeClass2, 1 );
				return TRUE;
			}

			if ( QUEST_LEVEL(eChangeClass2) == 2 )
			{
				int nTestCompleteCount = 0;
				for ( int i = eChangeClass2A ; i <= eChangeClass2D ; i++ )
				{
					if ( QUEST_LEVEL(i) == 255 ) nTestCompleteCount++;
				}

				if ( nTestCompleteCount < 3 )
				{
					NotifyQuestLevel( nUser, eNPCJangno, eChangeClass2, 2 );
					return TRUE;
				}

				MSG_CLASS sm; sm.wType = _MSG_CLASS; sm.wPDULength = sizeof(MSG_CLASS) - sizeof(HEADER);
				sm.nID = nUser;
				sm.byClass1 = CLASS_LEVEL2;
				switch ( pMob[nUser].MOB.snTribe )
				{
				case TRIBE_NAGA:
				case TRIBE_KINNARA:
					if ( FindItem( nUser, 8055, 1 ) != MAX_INVEN )
					{	// 2차전직 - 사트야로 전직한다.
						sm.byClass2 = CLASS_SATVAN1;
						RemoveItem( nUser, 8055, 1 );					
					}
					else if ( FindItem( nUser, 8056, 1 ) != MAX_INVEN )
					{	// 2차전직 - 바나르로 전직한다.
						sm.byClass2 = CLASS_SATVAN2;
						RemoveItem( nUser, 8056, 1 );
					}
					else 
					{
						sprintf( temp, "qst Error class change %s", pMob[nUser].MOB.szName );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						return TRUE;
					}
					break;
				case TRIBE_ASURA:
				case TRIBE_RAKSHASA:
					if ( FindItem( nUser, 8057, 1 ) != MAX_INVEN )
					{	// 2차전직 - 드루카로 전직한다.
						sm.byClass2 = CLASS_DHVANTA1;
						RemoveItem( nUser, 8057, 1 );
					}
					else if ( FindItem( nUser, 8058, 1 ) != MAX_INVEN )
					{	// 2차전직 - 카르야로 전직한다.
						sm.byClass2 = CLASS_DHVANTA2;
						RemoveItem( nUser, 8058, 1 );
					}
					else
					{
						sprintf( temp, "qst Error class change %s", pMob[nUser].MOB.szName );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						return TRUE;
					}
					break;
				case TRIBE_YAKSA:
				case TRIBE_GANDHARVA:
					if ( FindItem( nUser, 8059, 1 ) != MAX_INVEN )
					{	// 2차전직 - 나카유다로 전직한다.
						sm.byClass2 = CLASS_NIRVANA1;
						RemoveItem( nUser, 8059, 1 );
					}
					else if ( FindItem( nUser, 8060, 1 ) != MAX_INVEN )
					{	// 2차전직 - 바이드야로 전직한다.
						sm.byClass2 = CLASS_NIRVANA2;
						RemoveItem( nUser, 8060, 1 );
					}
					else
					{
						sprintf( temp, "qst Error class change %s", pMob[nUser].MOB.szName );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						return TRUE;
					}
					break;
				case TRIBE_DEVA:
				case TRIBE_GARUDA:
					if ( FindItem( nUser, 8061, 1 ) != MAX_INVEN )
					{	// 2차전직 - 아비카라로 전직한다.
						sm.byClass2 = CLASS_MANTRIKA1;
						RemoveItem( nUser, 8061, 1 );
					}
					else if ( FindItem( nUser, 8062, 1 ) != MAX_INVEN )
					{	// 2차전직 - 사마바트로 전직한다.
						sm.byClass2 = CLASS_MANTRIKA2;
						RemoveItem( nUser, 8062, 1 );
					}
					else
					{
						sprintf( temp, "qst Error class change %s", pMob[nUser].MOB.szName );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						return TRUE;
					}
					break;
				}
				RemoveItem( nUser, 8066, 1 );
				RemoveItem( nUser, 8067, 1 );
				RemoveItem( nUser, 8068, 1 );
				RemoveItem( nUser, 8069, 1 );
				// 2차 전직을 시켜준다. 
				pMob[nUser].MOB.byClass1 = sm.byClass1;
				pMob[nUser].MOB.byClass2 = sm.byClass2;
				GridMulticast( pMob[nUser].TargetX, pMob[nUser].TargetY, (MSG_STANDARD*)&sm, 0, 30 );
				pMob[nUser].UpdateEquipmentPoints() ;
				pMob[nUser].NotifyUpdateUIMsg() ;
				// 스킬 리셋
				pMob[nUser].ResetSkill();
				QUEST_LEVEL(eChangeClass2) = 255;
				sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eChangeClass2 );
				Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
				SendQuestHistory( nUser );
				NotifyQuestLevel( nUser, eNPCJangno, eChangeClass2, 255 );
				return TRUE;
			}
			if ( pMob[nUser].MOB.byLevel >= 45 
				&& pMob[nUser].MOB.byClass1 == CLASS_LEVEL2
				&& QUEST_LEVEL(eScenario2I) == 255 
				&& QUEST_LEVEL(eJinaA) == 0 )
			{
				QUEST_LEVEL(eJinaA) = 1;
				SendQuestHistory( nUser );
				NotifyQuestLevel( nUser, nEvent, eJinaA, 1 );
				return TRUE;
			}
			CHECK_QUEST_LEVEL(eJinaA, 45)
			{
				switch( QUEST_LEVEL(eJinaA) )
				{
				case 1:
					NotifyQuestLevel( nUser, nEvent, eJinaA, 1 );
					return TRUE;
				case 2:
					NotifyQuestLevel( nUser, nEvent, eJinaA, 2 );
					return TRUE;
				case 3:
					NotifyQuestLevel( nUser, nEvent, eJinaA, 3 );
					return TRUE;
				case 9:
					if ( RemoveItem( nUser, 8008, 1 ) )
					{
						GiveItem( nUser, 8009, 1);
						QUEST_LEVEL(eJinaA) = 10;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eJinaA, 4 );
						return TRUE;
					}
				case 10:
					NotifyQuestLevel( nUser, nEvent, eJinaA, 5 );
					break;
				}
			}
			CHECK_QUEST_LEVEL(eJinaB, 47)
			{
				switch ( QUEST_LEVEL(eJinaB) )
				{
				case 1:
					NotifyQuestLevel( nUser, nEvent, eJinaB, 1 );
					return TRUE;
				case 2:
					NotifyQuestLevel( nUser, nEvent, eJinaB, 2 );
					return TRUE;
				case 3:
					NotifyQuestLevel( nUser, nEvent, eJinaB, 3 );
					return TRUE;
				}
			}
			CHECK_QUEST(eJinaD)
			{
				switch( QUEST_LEVEL(eJinaD) )
				{
				case 2:
					QUEST_LEVEL(eJinaD) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaD, 1 );
					return TRUE;
				case 4:
					NotifyQuestLevel( nUser, nEvent, eJinaD, 2 );
					return TRUE;
				case 7:
					QUEST_LEVEL(eJinaD) = 8;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaD, 4 );
					return TRUE;
				case 8:
					NotifyQuestLevel( nUser, nEvent, eJinaD, 5 );
					return TRUE;
				}
			}
			CHECK_QUEST(eExileA)
			{
				switch( QUEST_LEVEL(eExileA) )
				{
				case 5:
					QUEST_LEVEL(eExileA) = 6;
					pMob[nUser].AcquirePrana( 300000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileA, 1 );
					return TRUE;
				case 6:
					NotifyQuestLevel( nUser, nEvent, eExileA, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST(eExileB)
			{
				switch( QUEST_LEVEL(eExileB) )
				{
				case 6:
					QUEST_LEVEL(eExileB) = 7;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileB, 1);
					return TRUE;
				}
			}
			CHECK_QUEST_LEVEL(eBukduC, 69)
			{
				switch ( QUEST_LEVEL(eBukduC) )
				{
				case 1:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eBukduC, QUEST_LEVEL(eBukduC) );
					return TRUE;
				case 2:
					if ( FindItem( nUser, 7323, 10 ) != MAX_INVEN 
						&& FindItem( nUser, 7326, 10 ) != MAX_INVEN 
						&& FindItem( nUser, 7329, 10 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 7323, 10 );
						RemoveItem( nUser, 7326, 10 );
						RemoveItem( nUser, 7329, 10 );
						QUEST_LEVEL(eBukduC) = 4;
						pMob[nUser].AcquirePrana( 4000000 );
						SendQuestHistory( nUser );
					}
					NotifyQuestLevel( nUser, nEvent, eBukduC, QUEST_LEVEL(eBukduC) );
					return TRUE;
				case 4:
					NotifyQuestLevel( nUser, nEvent, eBukduC, 5 );
					return TRUE;
				case 6:
					QUEST_LEVEL(eBukduC) = 7;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduC, 6 );
					return TRUE;
				case 7:
					EMPTY_INVEN_TEST( 1 );
					if ( pMob[nUser].MOB.nRupiah >= 1000000
						&& FindItem( nUser, 6502, 5 ) != MAX_INVEN
						&& FindItem( nUser, 6503, 1 ) != MAX_INVEN
						&& FindItem( nUser, 7116, 10 ) != MAX_INVEN
						&& FindItem( nUser, 7114, 10 ) != MAX_INVEN
						&& FindItem( nUser, 7132, 10 ) != MAX_INVEN
						&& FindItem( nUser, 7134, 10 ) != MAX_INVEN )
					{
						pMob[nUser].DecGold( 1000000 );
						RemoveItem( nUser, 6502, 5 );
						RemoveItem( nUser, 6503, 1 );
						RemoveItem( nUser, 7116, 10 );
						RemoveItem( nUser, 7114, 10 );
						RemoveItem( nUser, 7132, 10 );
						RemoveItem( nUser, 7134, 10 );
						QUEST_LEVEL(eBukduC) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eBukduC );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						QUEST_LEVEL(eBukduD) = 1;
						pMob[nUser].AcquirePrana( 8000000 );
						int nItem = rand() % 4;
						switch ( nItem )
						{
						case 0: GiveItem( nUser, 6047, 1 ); break;
						case 1: GiveItem( nUser, 6052, 1 ); break;
						case 2: GiveItem( nUser, 6155, 1 ); break;
						case 3: GiveItem( nUser, 6097, 1 ); break;
						}
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduC, 255 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eBukduC, 6 );
					}
					return TRUE;
				}
			}
			CHECK_QUEST_LEVEL(eBukduE, 73)
			{
				switch ( QUEST_LEVEL(eBukduE) )
				{
				case 1:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eBukduE, QUEST_LEVEL(eBukduE) );
					return TRUE;
				case 2:
					EMPTY_INVEN_TEST( 1 );
					if( FindItem( nUser, 7336, 1 ) != MAX_INVEN 
						&& FindItem( nUser, 7337, 1 ) != MAX_INVEN 
						&& FindItem( nUser, 7338, 1 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 7336, 1 );
						RemoveItem( nUser, 7337, 1 );
						RemoveItem( nUser, 7338, 1 );
						QUEST_LEVEL(eBukduE) = 4;
						pMob[nUser].AcquirePrana( 5000000 );
						SendQuestHistory( nUser );
						GiveItem( nUser, 8100, 1 );
					}
					NotifyQuestLevel( nUser, nEvent, eBukduE, QUEST_LEVEL(eBukduE) );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3C)		//	장노 쭈앙즈
			{
				switch ( QUEST_LEVEL(eScenario3C) )
				{
				case 7:
					QUEST_LEVEL(eScenario3C) = 8;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3C, 1 );
					return TRUE;
				case 8:
					NotifyQuestLevel( nUser, nEvent, eScenario3C, 2 );
					return TRUE;
				}
			}		//	장노 쭈앙즈
			CHECK_QUEST( eScenario3E )		
			{
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 20:
					QUEST_LEVEL(eScenario3E) = 21;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 21:
					EMPTY_INVEN_TEST(1);

					if( RemoveItem( nUser, 7173, 15 ) )
					{
						QUEST_LEVEL(eScenario3E) = 22;
						GiveItem( nUser, 8135, 1 );
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3E, 4 );
					}	else
						NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				case 22:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 5 );
					return TRUE;
				case 45:		//	사리스바티의 조각상
					if( FindItem( nUser, 8131, 1)!=MAX_INVEN && pMob[nUser].MOB.nRupiah>=1000000 )
					{
						QUEST_LEVEL(eScenario3E) =46;
						RemoveItem ( nUser, 8131, 1);
						GiveMoney( nUser, -1000000 );
						GiveMoney( nUser, 50000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3E, 6 );
						return TRUE;
					}
					break;
				case 46:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 7 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, eNPCJangno, 0, 0 );
			return TRUE;
		} break;
	case eNPCJjoungkui:	// 쫑쿠이에게 말을 걸었을때.
		{
			CHECK_QUEST(eChangeClass2C)
			{
				switch ( QUEST_LEVEL(eChangeClass2C) )
				{
				case 1:
					QUEST_LEVEL(eChangeClass2C) = 2;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCJjoungkui, eChangeClass2C, 1 );
					return TRUE;
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					NotifyQuestLevel( nUser, eNPCJjoungkui, eChangeClass2C, 2 );
					return TRUE;
				case 7:
					if ( RemoveItem( nUser, 8071, 1 ) )
					{
						GiveItem( nUser, 8068, 1 );
						QUEST_LEVEL(eChangeClass2C) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eChangeClass2C );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCJjoungkui, eChangeClass2C, 255 );
					}
					else
					{
						NotifyQuestLevel( nUser, eNPCJjoungkui, eChangeClass2C, 2 );
					}
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCJjoungkui, eChangeClass2C, 0 );
					return TRUE;
				}
			}
			if ( QUEST_LEVEL(eJinaD) == 8 )
			{
				EMPTY_INVEN_TEST( 4 );

				GiveItem( nUser, 6503, 1 );
				GiveItem( nUser, 7029, 20 );
				GiveItem( nUser, 7010, 20 );
				IN_KOREA( GiveItem( nUser, 7034, 1 ) );
				QUEST_LEVEL(eJinaD) = 255;
				sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eJinaD );
				Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
				QUEST_LEVEL(eJinaE) = 1;
				SendQuestHistory( nUser );
				NotifyQuestLevel( nUser, nEvent, eJinaD, 1 );
			}
			CHECK_QUEST_LEVEL(eJinaE, 53)
			{
				switch ( QUEST_LEVEL(eJinaE) )
				{
				case 1:
					NotifyQuestLevel( nUser, nEvent, eJinaE, 1 );
					return TRUE;
				case 2:
					NotifyQuestLevel( nUser, nEvent, eJinaE, 2 );
					return TRUE;
				case 3:
					NotifyQuestLevel( nUser, nEvent, eJinaE, 3 );
					return TRUE;
				}
			}
			CHECK_QUEST(eExileD)
			{
				switch ( QUEST_LEVEL(eExileD) )
				{
				case 5:
					if ( FindItem( nUser, 8088, 1 ) != MAX_INVEN && FindItem( nUser, 8089, 1 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eExileD) = 6;
						RemoveItem( nUser, 8088, 1 );
						RemoveItem( nUser, 8089, 1 );
						GiveItem( nUser, 8090, 1 );
						pMob[nUser].AcquirePrana( 300000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eExileD, 1 );
					}
					return TRUE;
				case 6:
				case 7:
					NotifyQuestLevel( nUser, nEvent, eExileD, 2 );
					return TRUE;
				case 8:
					if ( RemoveItem( nUser, 8091, 1 ) )
					{
						QUEST_LEVEL(eExileD) = 9;
						pMob[nUser].AcquirePrana( 500000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eExileD, 4 );
					}
					return TRUE;
				}
			}
			CHECK_QUEST_LEVEL(eBukduD,71)
			{
				switch ( QUEST_LEVEL(eBukduD) )
				{
				case 1:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eBukduD, QUEST_LEVEL(eBukduD) );
					return TRUE;
				case 2:
				case 4:
				case 5:
				case 6:
					NotifyQuestLevel( nUser, nEvent, eBukduD, 2 );
					return TRUE;
				case 7:
					RemoveItem( nUser, 8094, 1 );
					RemoveItem( nUser, 8095, 1 );
					RemoveItem( nUser, 8096, 1 );
					RemoveItem( nUser, 8097, 1 );
					QUEST_LEVEL(eBukduD) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eBukduD );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					pMob[nUser].AcquirePrana( 8000000 );
					GiveItem( nUser, 6505, 1 );
					GiveItem( nUser, 7401, 1 );
					QUEST_LEVEL(eBukduE) = 1;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduD, 255 );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3B)
			{
				switch ( QUEST_LEVEL(eScenario3B) )
				{
                case 4:
					EMPTY_INVEN_TEST( 1 );

					GiveItem(nUser, 8111, 1);
					QUEST_LEVEL(eScenario3B) = 5;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 1 );
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eScenario3B, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3C)		//	쫑쿠이
			{
				switch ( QUEST_LEVEL(eScenario3C) )
				{
                case 9:
					if( RemoveItem(nUser, 8115, 1) )	//	라마야나
					{
						pMob[nUser].AcquirePrana( 1500000 );
						QUEST_LEVEL(eScenario3C) = 10;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3C, 1 );
						return TRUE;
					}
				case 10:
					NotifyQuestLevel( nUser, nEvent, eScenario3C, 2 );
					return TRUE;
				case 11:
					if( RemoveItem(nUser, 8116, 1) )	//	수그리바의 증표
					{
						pMob[nUser].AcquirePrana( 1000000 );
						QUEST_LEVEL(eScenario3C) = 12;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3C, 4 );
						return TRUE;
					}
				case 12:
					NotifyQuestLevel( nUser, nEvent, eScenario3C, 5 );
					return TRUE;
				case 15:
					if( FindItem(nUser, 8117, 1)!=MAX_INVEN && FindItem(nUser, 8118, 1)!=MAX_INVEN && FindItem(nUser, 8119, 1)!=MAX_INVEN && FindItem(nUser, 8120, 1)!=MAX_INVEN )
					{
						RemoveItem(nUser, 8117, 1);
						RemoveItem(nUser, 8118, 1);
						RemoveItem(nUser, 8119, 1);
						RemoveItem(nUser, 8120, 1);
						RemoveItem(nUser, 8136, 1);			//	복원전 라마의 반지를 제거하고,

						pMob[nUser].AcquirePrana( 20000000 );
						GiveMoney( nUser, 1000000 );

						switch( pMob[nUser].MOB.snTribe )	//	복원된 라마의 반지를 지급한다.
						{
						case TRIBE_NAGA:
						case TRIBE_KINNARA:
							GiveItem( nUser, 6469, 1 );
							break;
						case TRIBE_ASURA:
						case TRIBE_RAKSHASA:
							GiveItem( nUser, 6470, 1 );
							break;
						case TRIBE_YAKSA:
						case TRIBE_GANDHARVA:
							GiveItem( nUser, 6471, 1 );
							break;
						case TRIBE_DEVA:
						case TRIBE_GARUDA:
							GiveItem( nUser, 6472, 1 );
							break;
						}

						QUEST_LEVEL(eScenario3C) = 255;
						QUEST_LEVEL(eScenario3D) = 1;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3C, 255 );
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenario3C );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						return TRUE;
					}
				}
			}

			CHECK_QUEST( eScenario3E )	//	쫑쿠이
			{
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 14:	//	팔왕의 흔적1~4
					RemoveItem( nUser, 8127, 1);
					RemoveItem( nUser, 8128, 1);
					RemoveItem( nUser, 8129, 1);
					RemoveItem( nUser, 8130, 1);
					QUEST_LEVEL(eScenario3E) = 15;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 15:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				case 26:	//	야주르 베다 ~ 리그베다
					RemoveItem( nUser, 8132, 1);
					RemoveItem( nUser, 8133, 1);
					RemoveItem( nUser, 8134, 1);
					RemoveItem( nUser, 8135, 1);
					GiveItem( nUser, 8131, 1 );		//	사라스바티의 조각상
					QUEST_LEVEL(eScenario3E) = 27;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 4 );

					return TRUE;
				case 27:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 5 );
					return TRUE;
				case 37:
					QUEST_LEVEL(eScenario3E) = 38;
					GiveMoney(nUser, 50000);
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 6 );
					return TRUE;
				case 38:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 7 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, eNPCJjoungkui, 0, 0 );
			return TRUE;
		} break;
	case eNPCOuyez:	// 오우예즈에게 말을 걸었을때.
		{
			CHECK_QUEST(eChangeClass2B)
			{
				switch ( QUEST_LEVEL(eChangeClass2B) )
				{
				case 1:
					QUEST_LEVEL(eChangeClass2B) = 2;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, eNPCOuyez, eChangeClass2B, 1 );
					return TRUE;
				case 2:
					NotifyQuestLevel( nUser, eNPCOuyez, eChangeClass2B, 2 );
					return TRUE;
				case 4:
					if (	FindItem( nUser, 8073, 1 ) != MAX_INVEN &&	FindItem( nUser, 8074, 1 ) != MAX_INVEN
						&&	FindItem( nUser, 8075, 1 ) != MAX_INVEN &&	FindItem( nUser, 8076, 1 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 8073, 1 );
						RemoveItem( nUser, 8074, 1 );
						RemoveItem( nUser, 8075, 1 );
						RemoveItem( nUser, 8076, 1 );
						QUEST_LEVEL(eChangeClass2B) = 5;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCOuyez, eChangeClass2B, 4 );
					}
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, eNPCOuyez, eChangeClass2B, 5 );
					return TRUE;
				case 7:
					if ( RemoveItem( nUser, 8077, 1 ) )
					{
						GiveItem( nUser, 8067, 1 );
						QUEST_LEVEL(eChangeClass2B) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eChangeClass2B );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, eNPCOuyez, eChangeClass2B, 255 );
					}
					else
					{
						NotifyQuestLevel( nUser, eNPCOuyez, eChangeClass2B, 6 );
					}
					return TRUE;
				default:
					NotifyQuestLevel( nUser, eNPCOuyez, eChangeClass2B, 0 );
					return TRUE;
				}
			}

			CHECK_QUEST(eJinaC)
			{
				switch ( QUEST_LEVEL(eJinaC) )
				{
				case 2:
					QUEST_LEVEL(eJinaC) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaC, 1 );
					return TRUE;
				case 4:
				case 5:
					NotifyQuestLevel( nUser, nEvent, eJinaC, 2 );
					return TRUE;
				case 6:
					QUEST_LEVEL(eJinaC) = 7;
					SendQuestHistory( nUser );
					GiveMoney( nUser, 50000 );
					pMob[nUser].AcquirePrana( 200000 );
					NotifyQuestLevel( nUser, nEvent, eJinaC, 4 );
					return TRUE;
				case 7:
				case 8:
					NotifyQuestLevel( nUser, nEvent, eJinaC, 5 );
					return TRUE;
				case 9:
					QUEST_LEVEL(eJinaC) = 10;
					SendQuestHistory( nUser );
					GiveMoney( nUser, 75000 );
					pMob[nUser].AcquirePrana( 300000 );
					NotifyQuestLevel( nUser, nEvent, eJinaC, 6 );
					return TRUE;
				case 11:
					NotifyQuestLevel( nUser, nEvent, eJinaC, 7 );
					return TRUE;
				case 12:
					EMPTY_INVEN_TEST( 1 );

					if ( RemoveItem( nUser, 8082, 1 ) )
					{
						QUEST_LEVEL(eJinaC) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eJinaC );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						QUEST_LEVEL(eJinaD) = 1;
						SendQuestHistory( nUser );
						GiveItem( nUser, 6096, 1 );
						IN_KOREA( GiveItem( nUser, 6810, 240 ) );
						pMob[nUser].AcquirePrana( 200000 );
						NotifyQuestLevel( nUser, nEvent, eJinaC, 8 );
					}
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3E)	//	무기상인 오우예즈
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 38:
					QUEST_LEVEL(eScenario3E) = 39;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 39:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, eNPCOuyez, 0, 0 );
			return TRUE;
		} break;
	case eNPCRuishan:
		{
			CHECK_QUEST(eJinaB)
			{
				switch ( QUEST_LEVEL(eJinaB) )
				{
				case 8:
					QUEST_LEVEL(eJinaB) = 9;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaB, 1 );
					return TRUE;
				case 9:
					if ( FindItem( nUser, 7155, 20 ) != MAX_INVEN )
					{
						EMPTY_INVEN_TEST( 1 );

						QUEST_LEVEL(eJinaB) = 10;
						SendQuestHistory( nUser );
						RemoveItem( nUser, 7155, 20 );
						GiveItem( nUser, 8080, 1 );
						NotifyQuestLevel( nUser, nEvent, eJinaB, 4 );
					}
					else NotifyQuestLevel( nUser, nEvent, eJinaB, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST_LEVEL(eJinaC,49)
			{
				switch ( QUEST_LEVEL(eJinaC) )
				{
				case 1:
					NotifyQuestLevel( nUser, nEvent, eJinaC, 1 );
					return TRUE;
				case 2:
					NotifyQuestLevel( nUser, nEvent, eJinaC, 2 );
					return TRUE;
				case 3:
					NotifyQuestLevel( nUser, nEvent, eJinaC, 3 );
					return TRUE;
				}
			}
			CHECK_QUEST(eJinaD)
			{
				switch ( QUEST_LEVEL(eJinaD) )
				{
				case 4:
					QUEST_LEVEL(eJinaD) = 5;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaD, 1 );
					return TRUE;
				case 5:
					if ( FindItem( nUser, 7166, 15 ) != MAX_INVEN && FindItem( nUser, 7156, 20 ) != MAX_INVEN )
					{
						EMPTY_INVEN_TEST( 1 );

						QUEST_LEVEL(eJinaD) = 6;
						SendQuestHistory( nUser );
						RemoveItem( nUser, 7166, 15 );
						RemoveItem( nUser, 7156, 20 );
						GiveItem( nUser, 8083, 1 );
						GiveMoney( nUser, 100000 );
						pMob[nUser].AcquirePrana( 300000 );
						NotifyQuestLevel( nUser, nEvent, eJinaD, 4 );
					}
					else NotifyQuestLevel( nUser, nEvent, eJinaD, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST(eJinaE)
			{
				switch ( QUEST_LEVEL(eJinaE) )
				{
				case 10:
					QUEST_LEVEL(eJinaE) = 11;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eJinaE, 1 );
					return TRUE;
				case 11:
					if ( FindItem( nUser, 7165, 10 ) != MAX_INVEN 
						&& FindItem( nUser, 7118, 20 ) != MAX_INVEN 
						&& GiveItem( nUser, 8084, 1 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eJinaE) = 12;
						SendQuestHistory( nUser );
						pMob[nUser].AcquirePrana( 300000 );
						RemoveItem( nUser, 7165, 10 );
						RemoveItem( nUser, 7118, 20 );
						NotifyQuestLevel( nUser, nEvent, eJinaE, 4 );
					}
					else NotifyQuestLevel( nUser, nEvent, eJinaE, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST(eExileA)
			{
				switch( QUEST_LEVEL(eExileA) )
				{
				case 6:
					QUEST_LEVEL(eExileA) = 7;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileA, 1 );
					return TRUE;
				case 7:
					NotifyQuestLevel( nUser, nEvent, eExileA, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST(eBukduA)
			{
				switch( QUEST_LEVEL(eBukduA) )
				{
				case 5:
					QUEST_LEVEL(eBukduA) = 6;
					pMob[nUser].AcquirePrana( 1000000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduA, 1 );
					return TRUE;
				case 6:
					if ( RemoveItem( nUser, 7319, 40 ) )
					{
						QUEST_LEVEL(eBukduA) = 7;
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduA, 4 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eBukduA, 2 );
					}
					return TRUE;
				case 7:
				case 8:
				case 9:
					NotifyQuestLevel( nUser, nEvent, eBukduA, 5);
					return TRUE;
				case 10:
					EMPTY_INVEN_TEST( 1 );
					if ( RemoveItem( nUser, 7320, 1 ) )
					{
						QUEST_LEVEL(eBukduA) = 11;
						RemoveItem( nUser, 8099, 1 );
						GiveItem( nUser, 8098, 1 );
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduA, 6 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eBukduA, 5 );
					}
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3E)	//	잡화상인 뤼산
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 39:
					QUEST_LEVEL(eScenario3E) = 40;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 40:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
			return TRUE;
		} break;
	case eNPCBohrer:
		{
			//CHECK_QUEST_LEVEL(eExileA,55)
			if ( QUEST_LEVEL(eJinaE) == 255 && pMob[nUser].MOB.byLevel >= 55  && QUEST_LEVEL(eExileA) <= 3 )
			{
				if ( QUEST_LEVEL(eExileA) == 0 ) QUEST_LEVEL(eExileA) = 1;
				switch( QUEST_LEVEL(eExileA) )
				{
				case 1:
				case 2:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eExileA, QUEST_LEVEL(eExileA) );
					return TRUE;
				}
			}
			CHECK_QUEST( eExileD )
			{
				switch( QUEST_LEVEL(eExileD) )
				{
				case 2:
					QUEST_LEVEL(eExileD) = 4;
					pMob[nUser].AcquirePrana( 300000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileD, 1 );
					return TRUE;
				case 4:
					EMPTY_INVEN_TEST( 2 );

					if ( RemoveItem( nUser, 7174, 30 ) )
					{
						GiveMoney( nUser, 500000 );
						pMob[nUser].AcquirePrana( 500000 );
						QUEST_LEVEL(eExileD) = 5;
						GiveItem( nUser, 8088, 1 );
						GiveItem( nUser, 8089, 1 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eExileD, 4 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eExileD, 2 );
					}
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eExileD, 5 );
					return TRUE;
				case 6:
					QUEST_LEVEL(eExileD) = 7;
					RemoveItem( nUser, 8090, 1 );
					pMob[nUser].AcquirePrana( 300000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileD, 6 );
					return TRUE;
				case 7:
					EMPTY_INVEN_TEST( 1 );
					if ( FindItem( nUser, 7174, 30 ) != MAX_INVEN && FindItem( nUser, 7175, 20 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 7174, 30 );
						RemoveItem( nUser, 7175, 20 );
						GiveItem( nUser, 8091, 1 );
						GiveMoney( nUser, 500000 );
						pMob[nUser].AcquirePrana( 1000000 );
						QUEST_LEVEL(eExileD) = 8;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eExileD, 8 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eExileD, 7 );
					}
					return TRUE;
				case 8:
					NotifyQuestLevel( nUser, nEvent, eExileD, 9 );
					return TRUE;
				case 9:
					QUEST_LEVEL(eExileD) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eExileD );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					QUEST_LEVEL(eExileE) = 1;
					GiveMoney( nUser, 500000 );
					pMob[nUser].AcquirePrana( 500000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileD, 255 );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3E)	//	창고지기 보오러
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 40:
					QUEST_LEVEL(eScenario3E) = 41;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 41:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
		} break;
	case eNPCRuipuwei:
		{
			CHECK_QUEST(eExileA)
			{
				switch( QUEST_LEVEL(eExileA) )
				{
				case 7:
					QUEST_LEVEL(eExileA) = 8;
					pMob[nUser].AcquirePrana( 300000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileA, 1 );
					return TRUE;
				case 8:
					NotifyQuestLevel( nUser, nEvent, eExileA, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST(eExileE)
			{
				switch( QUEST_LEVEL(eExileE) )
				{
				case 2:
					QUEST_LEVEL(eExileE) = 4;
					pMob[nUser].AcquirePrana( 300000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileE, 1 );
					return TRUE;
				case 4:
					EMPTY_INVEN_TEST( 1 );
					if ( FindItem( nUser, 7176, 40 ) != MAX_INVEN && FindItem( nUser, 7177, 10 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eExileE) = 5;
						RemoveItem( nUser, 7176, 40 );
						RemoveItem( nUser, 7177, 10 );
						GiveItem( nUser, 8092, 1 );
						GiveMoney( nUser, 500000 );
						pMob[nUser].AcquirePrana( 500000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eExileE, 4 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eExileE, 2 );
					}
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eExileE, 5 );
					return TRUE;
				}
			}
			CHECK_QUEST(eBukduA)
			{
				switch ( QUEST_LEVEL(eBukduA) )
				{
				case 8:
					if ( RemoveItem( nUser, 7318, 20 ) )
					{
						QUEST_LEVEL(eBukduA) = 9;
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduA, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 9:
					NotifyQuestLevel( nUser, nEvent, eBukduA, 2 );
					return TRUE;
				}
			}
			CHECK_QUEST_LEVEL(eBukduB, 67)
			{
                switch ( QUEST_LEVEL(eBukduB) )
				{
				case 1:
					NotifyQuestLevel( nUser, nEvent, eBukduB, 1 );
					return TRUE;
				case 2:
					if ( FindItem( nUser, 7321, 10 ) != MAX_INVEN
						&& FindItem ( nUser, 7322, 10 ) != MAX_INVEN
						&& FindItem ( nUser, 7324, 10 ) != MAX_INVEN
						&& FindItem ( nUser, 7325, 10 ) != MAX_INVEN
						&& FindItem ( nUser, 7327, 10 ) != MAX_INVEN
						&& FindItem ( nUser, 7328, 10 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eBukduB) = 4;

						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduB, 4 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eBukduB, 2 );
					}
					return TRUE;
				case 3:
					NotifyQuestLevel( nUser, nEvent, eBukduB, 3 );
					return TRUE;
				case 10:
					RemoveItem( nUser, 8101, 1 );
					RemoveItem( nUser, 8102, 1 );
					RemoveItem( nUser, 8103, 1 );
					RemoveItem( nUser, 8104, 1 );
					RemoveItem( nUser, 8105, 1 );
					RemoveItem( nUser, 8106, 1 );
					QUEST_LEVEL(eBukduB) = 11; 
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduB, 5 );
					return TRUE;
				case 11:
					if ( FindItem( nUser, 7005, 10 ) != MAX_INVEN 
						&& FindItem( nUser, 7010, 10 ) != MAX_INVEN 
						&& FindItem( nUser, 7115, 10 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 7005, 10 );
						RemoveItem( nUser, 7010, 10 );
						RemoveItem( nUser, 7115, 10 );
						QUEST_LEVEL(eBukduB) = 12;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduB, 6 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eBukduB, 5 );
					}
					return TRUE;
				case 12:
					NotifyQuestLevel( nUser, nEvent, eBukduB, 7 );
					return TRUE;
				case 15:
					if ( RemoveItem( nUser, 8093, 1 ) )
					{
						QUEST_LEVEL(eBukduB) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eBukduB );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						QUEST_LEVEL(eBukduC) = 1;
						pMob[nUser].AcquirePrana( 6000000 );
						GiveItem( nUser, 6731, 1 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduB, 255 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eBukduB, 7 );
					}
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3E)	//	잡화상인 뤼뿌웨
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 42:
					QUEST_LEVEL(eScenario3E) = 43;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 43:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
		} break;
	case eNPCHidungtasheo: // 하이등따셔에게 말을 걸었을때.
		{
			CHECK_QUEST(eExileA)
			{
				switch( QUEST_LEVEL(eExileA) )
				{
				case 8:
					QUEST_LEVEL(eExileA) = 9;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileA, 1 );
					return TRUE;
				case 9:
					if ( FindItem( nUser, 7169, 40 ) != MAX_INVEN && FindItem( nUser, 7170, 20 ) != MAX_INVEN )
					{
						RemoveItem( nUser, 7169, 40 );
						RemoveItem( nUser, 7170, 20 );
						QUEST_LEVEL(eExileA) = 10;
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eExileA, 4 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eExileA, 2 );
					}
					return TRUE;
				case 10:
					if ( RemoveItem( nUser, 8041, 1 ) )
					{
						QUEST_LEVEL(eExileA) = 255;
						sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eExileA );
						Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
						QUEST_LEVEL(eExileB) = 1;
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eExileA, 255 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, eExileA, 5 );
					}
					return TRUE;
				}
			}
			CHECK_QUEST(eExileB)
			{
				switch( QUEST_LEVEL(eExileB) )
				{
				case 4:
					QUEST_LEVEL(eExileB) = 5;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileB, 1 );
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eExileB, 2 );
					return TRUE;
				case 7:
					QUEST_LEVEL(eExileB) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eExileB );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					QUEST_LEVEL(eExileC) = 1;
					pMob[nUser].AcquirePrana( 300000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileB, 255 );
					return TRUE;
				}
			}
			CHECK_QUEST_LEVEL(eExileC, 59)
			{
				switch( QUEST_LEVEL(eExileC) )
				{
				case 1:
				case 2:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eExileC, QUEST_LEVEL(eExileC) );
					return TRUE;
				}
			}
			if ( QUEST_LEVEL(eExileE) == 255 && pMob[nUser].MOB.byLevel >= 65 ) // 북두퀘스트 A 시작
			{
				switch( QUEST_LEVEL(eBukduA) )
				{
				case 0:
					QUEST_LEVEL(eBukduA) = 1;
					SendQuestHistory( nUser );
				case 1:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eBukduA, QUEST_LEVEL(eBukduA) );
					return TRUE;
				case 2:
				case 4:
				case 5:
					if ( FindItem( nUser, 7320, 1 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eBukduA) = 5;
						SendQuestHistory( nUser );
					}
					NotifyQuestLevel( nUser, nEvent, eBukduA, QUEST_LEVEL(eBukduA) );
					return TRUE;
				case 11:
					RemoveItem( nUser, 8098, 1 );
					QUEST_LEVEL(eBukduA) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eBukduA );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					pMob[nUser].AcquirePrana( 4600000 );
					GiveItem( nUser, 7383, 100 );
					QUEST_LEVEL(eBukduB) = 1;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduA, 255 );
					return TRUE;
				}
			}
			CHECK_QUEST(eBukduB)
			{
				switch( QUEST_LEVEL(eBukduB) )
				{
				case 8:
					EMPTY_INVEN_TEST( 1 );
					if ( RemoveItem( nUser, 7327, 10 ) )
					{
						GiveItem( nUser, 8105,1  );
						QUEST_LEVEL(eBukduB) = 9;
						pMob[nUser].AcquirePrana( 1000000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eBukduB, 1 );
					}
					else
					{
						NotifyQuestLevel( nUser, nEvent, 0, 0 );
					}
					return TRUE;
				case 9:
					NotifyQuestLevel( nUser, nEvent, eBukduB, 2 );
					return TRUE;
				}
			}

			CHECK_QUEST(eScenario3D)
			{
				switch( QUEST_LEVEL(eScenario3D) )
				{
				case 2:
					QUEST_LEVEL(eScenario3D) = 4;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 1 );
					return TRUE;
				case 4:
					{
						if(FindItem(nUser, 7319, 15)!=MAX_INVEN)	//	 && FindItem(nUser, 7334, 15)!=MAX_INVEN)	//	검은화약, 고급한지
						{
							int nItemCount1 = GetItemCount(nUser, 7334 - HT_PARAMTYPE_ITEM_START + 1);
							int nItemCount2 = GetItemCount(nUser, 7329 - HT_PARAMTYPE_ITEM_START + 1);

							if((nItemCount1+nItemCount2) >= 20)
							{
								RemoveItem(nUser, 7319, 15);
								if(nItemCount1>=20)
								{   RemoveItem(nUser, 7334, 20);
								}	else
								{	RemoveItem(nUser, 7334, nItemCount1);
									RemoveItem(nUser, 7329, 20-nItemCount1);
								}

								QUEST_LEVEL(eScenario3D) = 5;
								pMob[nUser].AcquirePrana( 1500000 );
								SendQuestHistory( nUser );
								NotifyQuestLevel( nUser, nEvent, eScenario3D, 4 );
								return TRUE;
							}
						}
						
						NotifyQuestLevel( nUser, nEvent, eScenario3D, 2 );
						return TRUE;
					}
					return TRUE;
				case 5:
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 5 );
					return TRUE;
				case 6:
					if(RemoveItem(nUser, 8121, 1))	//	달빛
					{
						GiveItem(nUser, 8122, 1);	//	청순한 달
						QUEST_LEVEL(eScenario3D) = 7;
						pMob[nUser].AcquirePrana( 1500000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eScenario3D, 6 );
						return TRUE;
					}
				case 7:
					NotifyQuestLevel( nUser, nEvent, eScenario3D, 7 );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3E)	//	장노 하이등따
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 41:
					QUEST_LEVEL(eScenario3E) = 42;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 42:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
		} break;
	case eNPCWuShong:
		{
			CHECK_QUEST_LEVEL(eExileB, 57)
			{
				switch( QUEST_LEVEL(eExileB) )
				{
				case 1:
				case 2:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eExileB, QUEST_LEVEL(eExileB) );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
		} break;
	case eNPCRuizshen:
		{
			CHECK_QUEST(eExileB)
			{
				switch( QUEST_LEVEL(eExileB) )
				{
				case 2:
					QUEST_LEVEL(eExileB) = 4;
					pMob[nUser].AcquirePrana( 300000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileB, 1 );
					return TRUE;
				case 4:
					NotifyQuestLevel( nUser, nEvent, eExileB, 2 );
					return TRUE;
				}
			}

			NotifyQuestLevel( nUser, nEvent, 0, 0 );
		} break;
	case eNPCShunelnyang:
		{
			CHECK_QUEST_LEVEL(eExileD, 61)
			{
				switch( QUEST_LEVEL(eExileD) )
				{
				case 1:
				case 2:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eExileD, QUEST_LEVEL(eExileD) );
					return TRUE;
				}
			}
			CHECK_QUEST(eExileE)
			{
				switch( QUEST_LEVEL(eExileE) )
				{
				case 2:
				case 3:
				case 4:
				case 5:
					NotifyQuestLevel( nUser, nEvent, eExileE, 1 );
					return TRUE;
				case 6:
					EMPTY_INVEN_TEST( 3 );
					QUEST_LEVEL(eExileE) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eExileE );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					GiveMoney( nUser, 1000000 );
					pMob[nUser].AcquirePrana( 1000000 );
					GiveItem( nUser, 7068, 100 );
					GiveItem( nUser, 7070, 100 );
					int nItem = rand() % 3;
					switch ( nItem )
					{
						case 0: GiveItem( nUser, 6047, 1 ); break;
						case 1: GiveItem( nUser, 6052, 1 ); break;
						case 2: GiveItem( nUser, 6155, 1 ); break;
					}

					QUEST_LEVEL(eBukduA) = 1;

					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eExileE, 255 );
					return TRUE;
				}
			}		//	아낙네 쑨얼냥
			CHECK_QUEST( eScenario3E )		
			{
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 22:
					QUEST_LEVEL(eMonsterKill1) = 0; 
					QUEST_LEVEL(eScenario3E) = 23;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 23:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				case 25:
					EMPTY_INVEN_TEST(1);

					QUEST_LEVEL(eScenario3E) = 26;
					GiveItem( nUser, 8134, 1 );
					pMob[nUser].AcquirePrana( 1000000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 4 );
					return TRUE;
				case 26:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 5 );
					return TRUE;
				case 44:
					QUEST_LEVEL(eScenario3E) = 45;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 6 );
					return TRUE;
				case 45:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 7 );
					return TRUE;
				}
			}


			NotifyQuestLevel( nUser, nEvent, 0, 0 );
		} break;
	case eNPCShunnongs:
		{
			CHECK_QUEST_LEVEL(eExileE, 63)
			{
				switch ( QUEST_LEVEL(eExileE) )
				{
				case 1:
				case 2:
				case 3:
					NotifyQuestLevel( nUser, nEvent, eExileE, QUEST_LEVEL(eExileE) );
					return TRUE;
				case 5:
					if ( RemoveItem( nUser, 8092, 1 ) )
					{
						QUEST_LEVEL(eExileE) = 6;
						GiveMoney( nUser, 100000 );
						pMob[nUser].AcquirePrana( 500000 );
						SendQuestHistory( nUser );
						NotifyQuestLevel( nUser, nEvent, eExileE, 4 );
					}
					return TRUE;
				case 6:
					NotifyQuestLevel( nUser, nEvent, eExileE, 5 );
					return TRUE;
				}
			}
			CHECK_QUEST(eScenario3E)	//	농부 션농쓰
			{	
				switch ( QUEST_LEVEL(eScenario3E) )
				{
				case 43:
					QUEST_LEVEL(eScenario3E) = 44;
					GiveMoney( nUser, 50000 );
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 1 );
					return TRUE;
				case 44:
					NotifyQuestLevel( nUser, nEvent, eScenario3E, 2 );
					return TRUE;
				}
			}

            NotifyQuestLevel( nUser, nEvent, 0, 0 );
		} break;
	case eNPCToyongJangin:
		{
			CHECK_QUEST(eBukduB)
			{
				switch ( QUEST_LEVEL(eBukduB) )
				{
				case 12:
					SummonMonster( nUser, eSwordMan, eTNCls_Warrior, eTNClan_Neutral );
					QUEST_LEVEL(eBukduB) = 13;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduB, 1 );
                    return TRUE;
				case 13:
					NotifyQuestLevel( nUser, nEvent, eBukduB, 2 );
					SummonMonster( nUser, eSwordMan, eTNCls_Warrior, eTNClan_Neutral );
					return TRUE;
				case 14:
					EMPTY_INVEN_TEST( 1 );
					GiveItem( nUser, 8093, 1 );
					QUEST_LEVEL(eBukduB) = 15;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduB, 4 );
					return TRUE;
				case 15:
					NotifyQuestLevel( nUser, nEvent, eBukduB, 5 );
					return TRUE;
				}
			}
			NotifyQuestLevel( nUser, nEvent, 0, 0 );
		} break;
	case eNPCBukduJjuangz:
		{
			CHECK_QUEST(eBukduE)
			{
				switch ( QUEST_LEVEL(eBukduE) )
				{
				case 4:
					SummonMonster( nUser ,eBukduSunggun, eTNCls_NPC, eTNClan_NPC );
					RemoveItem( nUser, 8100, 1 );
					GiveItem( nUser, 4292, 1 );
					QUEST_LEVEL(eBukduE) = 5;
					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduE, 1 );
					return TRUE;
				case 5:
					SummonMonster( nUser,eBukduSunggun, eTNCls_NPC, eTNClan_NPC );
					NotifyQuestLevel( nUser, nEvent, eBukduE, 2 );
					return TRUE;
				case 6:
					EMPTY_INVEN_TEST( 2 );
					QUEST_LEVEL(eBukduE) = 255;
					sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eBukduE );
					Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
					switch ( pMob[nUser].MOB.snTribe )
					{
					case TRIBE_NAGA:
					case TRIBE_KINNARA:
						if ( GetProbability( 10 ) ) { GiveItem( nUser, 5042, 1 ); break; }
						if ( GetProbability( 10 ) ) { GiveItem( nUser, 5187, 1 ); break; }
						if ( GetProbability( 40 ) ) { GiveItem( nUser, 5437, 1 ); break; }
						GiveItem( nUser, 5608, 1 );
						break;
					case TRIBE_ASURA:
					case TRIBE_RAKSHASA:
						if ( GetProbability( 10 ) ) { GiveItem( nUser, 5043, 1 ); break; }
						if ( GetProbability( 10 ) ) { GiveItem( nUser, 5188, 1 ); break; }
						if ( GetProbability( 40 ) ) { GiveItem( nUser, 5438, 1 ); break; }
						GiveItem( nUser, 5609, 1 );
						break;
					case TRIBE_YAKSA:
					case TRIBE_GANDHARVA:
						if ( GetProbability( 10 ) ) { GiveItem( nUser, 5044, 1 ); break; }
						if ( GetProbability( 10 ) ) { GiveItem( nUser, 5189, 1 ); break; }
						if ( GetProbability( 40 ) ) { GiveItem( nUser, 5439, 1 ); break; }
						GiveItem( nUser, 5610, 1 );
						break;
					case TRIBE_DEVA:
					case TRIBE_GARUDA:
						if ( GetProbability( 10 ) ) { GiveItem( nUser, 5045, 1 ); break; }
						if ( GetProbability( 10 ) ) { GiveItem( nUser, 5190, 1 ); break; }
						if ( GetProbability( 40 ) ) { GiveItem( nUser, 5440, 1 ); break; }
						GiveItem( nUser, 5611, 1 );
						break;
					}
					GiveItem( nUser, 5553, 1 );

					QUEST_LEVEL(eScenario3A) = 1;

					SendQuestHistory( nUser );
					NotifyQuestLevel( nUser, nEvent, eBukduE, 255 );
					return TRUE;
				}
			}
		} break;
	///////////////////// 여기서부터는 몬스터 ///////////////////////////
	case eVashabum:
		{
            if ( !bMonsterKill ) return TRUE;
			if ( QUEST_LEVEL(eChangeClass1) != 4 ) return TRUE;

			QUEST_LEVEL(eMonsterKill1)++;
			if ( QUEST_LEVEL(eMonsterKill1) >= 3 )
			{
				QUEST_LEVEL(eChangeClass1) = 5;
				QUEST_LEVEL(eMonsterKill1) = 0;
			}

			SendQuestHistory( nUser );
		} break;
	case eVashabumKaura:
		{
			if ( !bMonsterKill ) return TRUE;
			if ( QUEST_LEVEL(eChangeClass1) == 5 )
			{
				QUEST_LEVEL(eMonsterKill1)++;
				if ( QUEST_LEVEL(eMonsterKill1) >= 3 )
				{
					QUEST_LEVEL(eChangeClass1) = 6;
					QUEST_LEVEL(eMonsterKill1) = 0;
				}

				SendQuestHistory( nUser );
			}
		} break;
	case eMullecha:
		{	// TUTORIAL E
			if ( !bMonsterKill ) return TRUE;
            if ( QUEST_LEVEL(eTutorialE) == 2 || QUEST_LEVEL(eTutorialE) == 3 )
			{
				QUEST_LEVEL(eTutorialE) = 3;
				QUEST_LEVEL(eMonsterKill1)++;
				if ( QUEST_LEVEL(eMonsterKill1) >= 10 )
				{
					QUEST_LEVEL(eMonsterKill1) = 0;
					QUEST_LEVEL(eTutorialE) = 4;
				}

				SendQuestHistory( nUser );
			}

			if ( QUEST_LEVEL(eChangeClass1) == 6 )
			{
				QUEST_LEVEL(eMonsterKill1)++;
				if ( QUEST_LEVEL(eMonsterKill1) >= 3 )
				{
					QUEST_LEVEL(eChangeClass1) = 7;
					QUEST_LEVEL(eMonsterKill1) = 0;
				}

				SendQuestHistory( nUser );
			}
			return TRUE;
		} break;
	case eVashabumKlapra:
		{
			if ( !bMonsterKill ) return TRUE;
			if ( QUEST_LEVEL(eChangeClass1) != 7 ) return TRUE;

			QUEST_LEVEL(eMonsterKill1)++;
			if ( QUEST_LEVEL(eMonsterKill1) >= 3 )
			{
				QUEST_LEVEL(eChangeClass1) = 8;
				QUEST_LEVEL(eMonsterKill1) = 0;
			}

			SendQuestHistory( nUser );
		} break;
	case eMullechaKaura:
		{	// SCENARIO C
			if ( !bMonsterKill ) return TRUE;
			if ( QUEST_LEVEL(eScenarioC) == 2 )
			{
				if ( QUEST_LEVEL(eQuestTemp1) < 3 )
				{
					QUEST_LEVEL(eQuestTemp1)++;
				}
				else
				{
					if ( GiveItem( nUser, 8010, 1 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eScenarioC) = 4;
						QUEST_LEVEL(eQuestTemp1) = 0;
						SendQuestHistory( nUser );
					}
				}
			}

			if ( QUEST_LEVEL(eChangeClass1) == 8 )
			{
				QUEST_LEVEL(eMonsterKill1)++;
				if ( QUEST_LEVEL(eMonsterKill1) >= 3 )
				{
					QUEST_LEVEL(eChangeClass1) = 9;
					QUEST_LEVEL(eMonsterKill1) = 0;
				}

				SendQuestHistory( nUser );
			}

			return TRUE;
		} break;
	case eVruka:
		{
			if ( !bMonsterKill ) return TRUE;
			if ( QUEST_LEVEL(eChangeClass1) != 9 ) return TRUE;

			QUEST_LEVEL(eMonsterKill1)++;
			if ( QUEST_LEVEL(eMonsterKill1) >= 3 )
			{
				QUEST_LEVEL(eChangeClass1) = 10;
				QUEST_LEVEL(eMonsterKill1) = 0;
			}

			SendQuestHistory( nUser );
		} break;
	case eVrukaDara:
		{
			if ( !bMonsterKill ) return TRUE;
			if ( QUEST_LEVEL(eChangeClass1) != 10 ) return TRUE;

			QUEST_LEVEL(eMonsterKill1)++;
			if ( QUEST_LEVEL(eMonsterKill1) >= 3 )
			{
				QUEST_LEVEL(eChangeClass1) = 11;
				QUEST_LEVEL(eMonsterKill1) = 0;
			}

			SendQuestHistory( nUser );
		} break;
	case eMullechaKarmana:
		{	// SCENARIO F
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenarioF) != 2 ) break;

			if ( QUEST_LEVEL(eQuestTemp1) < 3 )
			{
				QUEST_LEVEL(eQuestTemp1)++;
			}
			else
			{
				if ( GiveItem( nUser, 8011, 1 ) != MAX_INVEN )
				{
					QUEST_LEVEL(eScenarioF) = 4;
					QUEST_LEVEL(eQuestTemp1) = 0;
					SendQuestHistory( nUser );
				}
			}
		} break;
	case eAfraBarahaRaja:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenarioH) == 2
				|| QUEST_LEVEL(eScenarioH) == 5
				|| QUEST_LEVEL(eScenarioH) == 7
				|| QUEST_LEVEL(eScenarioH) == 11 )
			{
				// SCENARIO H  ///////////////////////////////////////////////////////////////////////////
				if ( QUEST_LEVEL(eQuestTemp1) < 3 )
				{
					QUEST_LEVEL(eQuestTemp1)++;
				}
				else
				{	
					switch ( pMob[nUser].MOB.snTribe )
					{
					case TRIBE_GARUDA:
						if ( GiveItem( nUser, 8014, 1 ) == MAX_INVEN ) break;
						QUEST_LEVEL(eScenarioH) = 4;
						break;
					case TRIBE_DEVA:
						if ( GiveItem( nUser, 8015, 1 ) == MAX_INVEN ) break;
						QUEST_LEVEL(eScenarioH) = 6;
						break;
					case TRIBE_GANDHARVA:
						if ( GiveItem( nUser, 8016, 1 ) == MAX_INVEN ) break;
						QUEST_LEVEL(eScenarioH) = 8;
						break;
					case TRIBE_RAKSHASA:
					case TRIBE_ASURA:
						if ( GiveItem( nUser, 8010, 1 ) == MAX_INVEN ) break;
						QUEST_LEVEL(eScenarioH) = 12;
						break;
					}
					QUEST_LEVEL(eQuestTemp1) = 0;
					SendQuestHistory( nUser );
				}
			}
		} break;
	case eCobra:
		{	// SCENARIO I  ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenarioI) == 2 || QUEST_LEVEL(eScenarioI) == 4 ) 
			{
				QUEST_LEVEL(eScenarioI) = 4;
				QUEST_LEVEL(eMonsterKill1)++;

				if ( QUEST_LEVEL(eMonsterKill1) >= 10 )
				{
					QUEST_LEVEL(eScenarioI) = 5;
					QUEST_LEVEL(eMonsterKill1) = 0;
				}
				SendQuestHistory( nUser );
			}

		} break;
	case eUlkamulka:
		{	// SCENARIO 2A ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario2A) != 2 && QUEST_LEVEL(eScenario2A) != 4 ) break;
			if ( QUEST_LEVEL(eScenario2A) == 2 ) QUEST_LEVEL(eScenario2A) = 4;
			QUEST_LEVEL(eMonsterKill1)++;

			if ( QUEST_LEVEL(eMonsterKill1) >= 30 )
			{
				QUEST_LEVEL(eScenario2A) = 5;
				QUEST_LEVEL(eMonsterKill1) = 0;
			}
			SendQuestHistory( nUser );
		} break;
	case eUlkamulkaKaura:
		{	// SCENARIO 2A ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario2A) != 6 && QUEST_LEVEL(eScenario2A) != 7 ) break;
			if ( QUEST_LEVEL(eScenario2A) == 6 ) QUEST_LEVEL(eScenario2A) = 7;
			QUEST_LEVEL(eMonsterKill1)++;

			if ( QUEST_LEVEL(eMonsterKill1) >= 15 )
			{
				QUEST_LEVEL(eScenario2A) = 8;
				QUEST_LEVEL(eMonsterKill1) = 0;
			}
			SendQuestHistory( nUser );
		} break;
	case eHeruka:
		{	// SCENARIO 2C ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario2C) != 2 && QUEST_LEVEL(eScenario2C) != 4 ) break;
			if ( QUEST_LEVEL(eScenario2C) == 2 ) QUEST_LEVEL(eScenario2C) = 4;
			QUEST_LEVEL(eMonsterKill1)++;

			if ( QUEST_LEVEL(eMonsterKill1) >= 30 )
			{
				QUEST_LEVEL(eScenario2C) = 5;
				QUEST_LEVEL(eMonsterKill1) = 0;
			}
			SendQuestHistory( nUser );
		} break;
	case eAnanga:
		{	// SCENARIO 2D ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario2D) == 2 )
			{
				QUEST_LEVEL(eQuestTemp1)++;
				if ( QUEST_LEVEL(eQuestTemp1) >= 20 )
				{
					if ( GiveItem( nUser, 8042, 1 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eScenario2D) = 4;
						QUEST_LEVEL(eQuestTemp1) = 0;
						SendQuestHistory( nUser );
					}
				}
			}

			if ( QUEST_LEVEL(eChangeClass2C) == 4 || QUEST_LEVEL(eChangeClass2C) == 5 )
			{
				QUEST_LEVEL(eMonsterKill1)++;
				switch ( QUEST_LEVEL(eChangeClass2C) )
				{
				case 4:
					QUEST_LEVEL(eChangeClass2C) = 5;
					break;
				case 5:
					if ( QUEST_LEVEL(eMonsterKill1) >= 20 )
					{
						QUEST_LEVEL(eMonsterKill1) = 0;
						QUEST_LEVEL(eChangeClass2C) = 6;
					}
					break;
				}
				SendQuestHistory( nUser );
			}
		} break;
	case eJarcu:
		{	// SCENARIO 2H ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario2H) == 6 )
			{	if ( GetProbability( 5 ) )
				{	if ( GiveItem( nUser, 8001, 1 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eScenario2H) = 7;
						SendQuestHistory( nUser );
					}
				}
			}
		} break;
	case eJarcuRudhira:
		{	// SCENARIO 2H ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario2H) == 9 )
			{	if ( GetProbability( 4 ) )
				{	if ( GiveItem( nUser, 8002, 1 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eScenario2H) = 10;
						SendQuestHistory( nUser );
					}
				}
			}
		} break;
	case eNagamudra:
		{	// SCENARIO 2H ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario2H) != 15 ) break;
			if ( !GetProbability( 2 ) ) break;

			if ( GiveItem( nUser, 8003, 1 ) != MAX_INVEN )
			{
				QUEST_LEVEL(eScenario2H) = 16;
				SendQuestHistory( nUser );
			}
		} break;
	case eKaulitara:
		{	// SCENARIO 2I ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario2I) != 2 ) break;
			if ( !GetProbability( 2 ) ) break;

			if ( GiveItem( nUser, 8039, 1 ) != MAX_INVEN )
			{
				QUEST_LEVEL(eScenario2I) = 4;
				SendQuestHistory( nUser );
			}
		} break;
	case eGhorayogi:
		{	// SCENARIO 2I ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario2H) == 12 )
			{
				if ( !GetProbability( 3 ) ) break;
				if ( GiveItem( nUser, 8004, 1 ) != MAX_INVEN )
				{
					QUEST_LEVEL(eScenario2H) = 13;
					SendQuestHistory( nUser );
				}
			}
			else if ( QUEST_LEVEL(eScenario2I) == 6 )
			{
				if ( !GetProbability( 2 ) ) break;
				if ( GiveItem( nUser, 8030, 1 ) != MAX_INVEN )
				{
					QUEST_LEVEL(eScenario2I) = 7;
					SendQuestHistory( nUser );
				}
			}

		} break;
	case eMeghamalin:
		{	// SCENARIO 2I ///////////////////////////////////////////////////////////////////////////
			if ( QUEST_LEVEL(eScenario2I) != 9 ) break;

			if ( RemoveItem( nUser, 8036, 1) )
			{
				GiveItem( nUser, 8040, 1 );
				QUEST_LEVEL(eScenario2I) = 10;
				SendQuestHistory( nUser );
			}
		} break;
	case eBrahmaScout1:
	case eBrahmaScout2:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eChangeClass2A) == 4 && QUEST_LEVEL(eQuestTemp2) == 0 )
			{
				if ( GiveItem( nUser, 8064, 1 ) == MAX_INVEN ) break;

				QUEST_LEVEL(eQuestTemp2) =1;
				if ( QUEST_LEVEL(eQuestTemp3) == 1 || QUEST_LEVEL(eQuestTemp4) == 1 )
				{
					QUEST_LEVEL(eChangeClass2A) = 5;
					QUEST_LEVEL(eQuestTemp2) = 0;
					QUEST_LEVEL(eQuestTemp3) = 0;
					QUEST_LEVEL(eQuestTemp4) = 0;
					SendQuestHistory( nUser );
				}
			}
		} break;
	case eVishuneScout1:
	case eVishuneScout2:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eChangeClass2A) == 4 && QUEST_LEVEL(eQuestTemp3) == 0 )
			{
				if ( GiveItem( nUser, 8065, 1 ) == MAX_INVEN ) break;

				QUEST_LEVEL(eQuestTemp3) = 1;
				if ( QUEST_LEVEL(eQuestTemp2) == 1 || QUEST_LEVEL(eQuestTemp4) == 1 )
				{
					QUEST_LEVEL(eChangeClass2A) = 5;
					QUEST_LEVEL(eQuestTemp2) = 0;
					QUEST_LEVEL(eQuestTemp3) = 0;
					QUEST_LEVEL(eQuestTemp4) = 0;
					SendQuestHistory( nUser );
				}
			}
		} break;
	case eSivaScout1:
	case eSivaScout2:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eChangeClass2A) == 4 && QUEST_LEVEL(eQuestTemp4) == 0 )
			{
				if ( GiveItem( nUser, 8063, 1 ) == MAX_INVEN ) break;

				QUEST_LEVEL(eQuestTemp4) = 1;
				if ( QUEST_LEVEL(eQuestTemp2) == 1 || QUEST_LEVEL(eQuestTemp3) == 1 )
				{
					QUEST_LEVEL(eChangeClass2A) = 5;
					QUEST_LEVEL(eQuestTemp2) = 0;
					QUEST_LEVEL(eQuestTemp3) = 0;
					QUEST_LEVEL(eQuestTemp4) = 0;
					SendQuestHistory( nUser );
				}
			}
		} break;
	case eHwanGeosu:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eChangeClass2B) == 2 && QUEST_LEVEL(eQuestTemp2) == 0 )
			{
				if( !GetProbability( 30 ) ) break;
				if ( GiveItem( nUser, 8073, 1 ) == MAX_INVEN ) break;

				QUEST_LEVEL(eQuestTemp2) = 1;
				if ( QUEST_LEVEL(eQuestTemp3) == 1 && QUEST_LEVEL(eQuestTemp4) == 1 && QUEST_LEVEL(eQuestTemp5) == 1 )
				{
					QUEST_LEVEL(eChangeClass2B) = 4;
					SendQuestHistory( nUser );
				}
			}
		} break;
	case eTiger:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eJinaC) == 11 )
			{
				if ( !GetProbability_10000( 100 ) ) break;
				if ( GiveItem( nUser, 8082, 1 ) == MAX_INVEN ) break;
				QUEST_LEVEL(eJinaC) = 12;
				SendQuestHistory( nUser );
			}
		} break;
	case eWhiteTiger:
		{
			if ( !bMonsterKill ) break;

			if ( QUEST_LEVEL(eChangeClass2B) == 2 && QUEST_LEVEL(eQuestTemp3) == 0 )
			{
				if( !GetProbability( 30 ) ) break;
				if ( GiveItem( nUser, 8074, 1 ) == MAX_INVEN ) break;

				QUEST_LEVEL(eQuestTemp3) = 1;
				if ( QUEST_LEVEL(eQuestTemp2) == 1 && QUEST_LEVEL(eQuestTemp4) == 1 && QUEST_LEVEL(eQuestTemp5) == 1 )
				{
					QUEST_LEVEL(eChangeClass2B) = 4;
					SendQuestHistory( nUser );
				}
			}
			if ( QUEST_LEVEL(eJinaC) == 11 )
			{
				if ( !GetProbability_10000( 200 ) ) break;
				if ( GiveItem( nUser, 8082, 1 ) == MAX_INVEN ) break;
				QUEST_LEVEL(eJinaC) = 12;
				SendQuestHistory( nUser );
			}
		} break;
	case eJeoparyungGeosu:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eChangeClass2B) == 2 && QUEST_LEVEL(eQuestTemp4) == 0 )
			{
				if( !GetProbability( 30 ) ) break;
				if ( GiveItem( nUser, 8075, 1 ) == MAX_INVEN ) break;

				QUEST_LEVEL(eQuestTemp4) = 1;
				if ( QUEST_LEVEL(eQuestTemp2) == 1 && QUEST_LEVEL(eQuestTemp3) == 1 && QUEST_LEVEL(eQuestTemp5) == 1 )
				{
					QUEST_LEVEL(eChangeClass2B) = 4;
					SendQuestHistory( nUser );
				}
			}
		} break;
	case eMangRyang:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eChangeClass2B) == 2 && QUEST_LEVEL(eQuestTemp5) == 0 )
			{
				if( !GetProbability( 30 ) ) break;
				if ( GiveItem( nUser, 8076, 1 ) == MAX_INVEN ) break;

				QUEST_LEVEL(eQuestTemp5) = 1;
				if ( QUEST_LEVEL(eQuestTemp2) == 1 && QUEST_LEVEL(eQuestTemp3) == 1 && QUEST_LEVEL(eQuestTemp4) == 1 )
				{
					QUEST_LEVEL(eChangeClass2B) = 4;
					SendQuestHistory( nUser );
				}
			}
		} break;
	case eStadiumMurderer:
		{
			if ( !bMonsterKill ) break;
			if ( !IsPartyMember( nUser ) ) break;
			if ( QUEST_LEVEL(eChangeClass2D) == 2 )
			{
				QUEST_LEVEL(eChangeClass2D) = 4;
				SendQuestHistory( nUser );
			}
		} break;
	case eJagoi:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eJinaA) == 4 )
			{
				QUEST_LEVEL(eMonsterKill1) = 1;
				QUEST_LEVEL(eJinaA) = 5;
				SendQuestHistory( nUser );
			}
			else if ( QUEST_LEVEL(eJinaA) == 5 )
			{
				if ( ( ++QUEST_LEVEL(eMonsterKill1) ) >= 28 )
				{
					QUEST_LEVEL(eJinaA) = 6;
					QUEST_LEVEL(eMonsterKill1) = 0;
				}
				SendQuestHistory( nUser );
			}
		} break;
	case eJagoiGeosu:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eJinaA) == 7 )
			{
				if ( !GetProbability_10000( 200 ) ) break;
				if ( GiveItem( nUser, 8008, 1 ) == MAX_INVEN ) break;
				QUEST_LEVEL(eJinaA) = 8;
				SendQuestHistory( nUser );
				break;
			}
			if ( QUEST_LEVEL(eJinaA) == 11 )
			{
				if ( !GetProbability_10000( 200 ) ) break;
				if ( GiveItem( nUser, 8079, 1 ) == MAX_INVEN ) break;
				QUEST_LEVEL(eJinaA) = 12;
				SendQuestHistory( nUser );
				break;
			}
		} break;
	case eSingoi:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eJinaB) == 11 )
			{
				if ( !GetProbability_10000( 200 ) ) break;
				if ( GiveItem( nUser, 8081, 1 ) == MAX_INVEN ) break;
				QUEST_LEVEL(eJinaB) = 12;
				SendQuestHistory( nUser );
				break;
			}
		} break;
	case eJinmoin:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eJinaC) == 4 )
			{
				QUEST_LEVEL(eMonsterKill1) = 1;
				QUEST_LEVEL(eJinaC) = 5;
				SendQuestHistory( nUser );
			}
			else if ( QUEST_LEVEL(eJinaC) == 5 )
			{
				if ( ++QUEST_LEVEL(eMonsterKill1) >= 10 )
				{
					QUEST_LEVEL(eMonsterKill1) = 0;
					QUEST_LEVEL(eJinaC) = 6;
				}
				SendQuestHistory( nUser );
			}
		} break;
	case eJinmoinGeosu:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eJinaC) == 7 )
			{
				QUEST_LEVEL(eMonsterKill1) = 1;
				QUEST_LEVEL(eJinaC) = 8;
				SendQuestHistory( nUser );
			}
			else if ( QUEST_LEVEL(eJinaC) == 8 )
			{
				if ( ++QUEST_LEVEL(eMonsterKill1) >= 15 )
				{
					QUEST_LEVEL(eMonsterKill1) = 0;
					QUEST_LEVEL(eJinaC) = 9;
				}
				SendQuestHistory( nUser );
			}
		} break;
	case eGuihwasang:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eJinaE) == 7 )
			{
				QUEST_LEVEL(eMonsterKill1) = 1;
				QUEST_LEVEL(eJinaE) = 8;
				SendQuestHistory( nUser );
			}
			else if ( QUEST_LEVEL(eJinaE) == 8 )
			{
				if ( ++QUEST_LEVEL(eMonsterKill1) >= 30 )
				{
					QUEST_LEVEL(eMonsterKill1) = 0;
					QUEST_LEVEL(eJinaE) = 9;
				}
				SendQuestHistory( nUser );
			}
		} break;
	case eVirginGhost:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eJinaE) == 13 && GetProbability_10000(200) && GiveItem( nUser, 8087, 1 ) != MAX_INVEN )
			{
				QUEST_LEVEL(eJinaE) = 14;
				SendQuestHistory( nUser );
			}
		} break;
	case eGraveChief:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eBukduA) == 2 )
			{
				if ( FindItem( nUser, 7320, 1 ) == MAX_INVEN )
				{
					GiveItem( nUser, 7320, 1 );
					QUEST_LEVEL(eBukduA)  = 4;
					SendQuestHistory( nUser );
				}
			}
		} break;
	case eGraver1:
	case eGraver2:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eBukduA) == 2 )
			{
				if ( FindItem( nUser, 7320, 1 ) == MAX_INVEN && GetProbability_10000( 50 ) )
				{
					if ( GiveItem( nUser, 7320, 1 ) != MAX_INVEN )
					{
						QUEST_LEVEL(eBukduA) = 4;
						SendQuestHistory( nUser );
					}
				}
			}
		} break;
	case eSwordMan:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eBukduB) == 13 )
			{
				QUEST_LEVEL(eBukduB) = 14;
				SendQuestHistory( nUser );
			}
		} break;
	case ePungsusa:
	case ePungsugwan:
		{	
			if ( !bMonsterKill ) break;
			CHECK_QUEST(eScenario3C)
			{
				if ( QUEST_LEVEL(eScenario3C) != 8 ) break;
				if ( !GetProbability( 10 ) ) break;

				if(FindItem(nUser, 8115, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
				{
					if(GiveItem(nUser, 8115, 1)==MAX_INVEN) 
						break;									//	지급 실패시 리턴
				}
				QUEST_LEVEL(eScenario3C) = 9;
				SendQuestHistory( nUser );

//				Party_ClearQuestAndGiveItem(nUser, eScenario3C, 8115, 1);
			}
		}
	case eSangmunsa:
	case eSangmungwan:
		{
			switch ( QUEST_LEVEL(eBukduD) )
			{
			case 2:
				if ( GiveItem( nUser, 8094, 1 ) != MAX_INVEN )
				{
					QUEST_LEVEL(eBukduD) = 4;
					pMob[nUser].AcquirePrana( 3000000 );
					GivePartyPrana( nUser, 500000 );
					RepairEquips( nUser );
					RepairPartyEquips( nUser );
					SendQuestHistory( nUser );
				}
				return TRUE;
			case 4:
				if ( GiveItem( nUser, 8095, 1 ) != MAX_INVEN )
				{
					QUEST_LEVEL(eBukduD) = 5;
					pMob[nUser].AcquirePrana( 3000000 );
					GivePartyPrana( nUser, 500000 );
					RepairEquips( nUser );
					RepairPartyEquips( nUser );
					SendQuestHistory( nUser );
				}
				return TRUE;
			case 5:
				if ( GiveItem( nUser, 8096, 1 ) != MAX_INVEN )
				{
					QUEST_LEVEL(eBukduD) = 6;
					pMob[nUser].AcquirePrana( 3000000 );
					GivePartyPrana( nUser, 500000 );
					RepairEquips( nUser );
					RepairPartyEquips( nUser );
					SendQuestHistory( nUser );
				}
				return TRUE;
			case 6:
				if ( GiveItem( nUser, 8097, 1 ) != MAX_INVEN )
				{
					QUEST_LEVEL(eBukduD) = 7;
					pMob[nUser].AcquirePrana( 3000000 );
					GivePartyPrana( nUser, 500000 );
					RepairEquips( nUser );
					RepairPartyEquips( nUser );
					SendQuestHistory( nUser );
				}
				return TRUE;
			}
		} break;
	case eBukduSunggun:
		{
			//if ( !bMonsterKill ) return FALSE;
			if ( QUEST_LEVEL(eBukduE) == 5 )
			{
				QUEST_LEVEL(eBukduE) = 6;
				pMob[nUser].AcquirePrana( 20000000 );
				SendQuestHistory( nUser );
				return TRUE;
			}
			else return FALSE;
		} break;
	case eChunMyungSa1:
	case eChunMyungSa2:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eBukduE) != 2 ) break;
			if ( FindItem( nUser, 7336, 1 ) != MAX_INVEN ) break;
			GiveItem( nUser, 7336, 1 );
		} break;
	case eChunMyungGwan:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eBukduE) != 2 ) break;
			if ( FindItem( nUser, 7337, 1 ) != MAX_INVEN ) break;
			GiveItem( nUser, 7337, 1 );
		} break;
	case eChungMyungDaekwan:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eBukduE) != 2 ) break;
			if ( FindItem( nUser, 7338, 1 ) != MAX_INVEN ) break;
			GiveItem( nUser, 7338, 1 );
		} break;
	case eWildPig:
		{
 			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3C) == 4 )
			{
				QUEST_LEVEL(eMonsterKill1) = 1;
				QUEST_LEVEL(eScenario3C) = 5;
				SendQuestHistory( nUser );
			}
			else if ( QUEST_LEVEL(eScenario3C) == 5 )
			{
				if ( ++QUEST_LEVEL(eMonsterKill1) >= 10 )
				{
					QUEST_LEVEL(eMonsterKill1) = 0;
					QUEST_LEVEL(eScenario3C) = 6;
				}
				SendQuestHistory( nUser );
			}
		} break;
	case eYummabung:
		{
 			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3E) == 23 )
			{
				QUEST_LEVEL(eMonsterKill1) = 1;
				QUEST_LEVEL(eScenario3E) = 24;
				SendQuestHistory( nUser );
			}
			else if ( QUEST_LEVEL(eScenario3E) == 24 )
			{
				if ( ++QUEST_LEVEL(eMonsterKill1) >= 30 )
				{
					QUEST_LEVEL(eMonsterKill1) = 0;
					QUEST_LEVEL(eScenario3E) = 25;
				}
				SendQuestHistory( nUser );
			}
		} break;
	case eChumGgun:
		{	// eScenario3A ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;

			CHECK_QUEST(eScenario3A)
			{
				if ( QUEST_LEVEL(eScenario3A) != 9 ) break;
				if ( !GetProbability( 1 ) ) break;

				if(FindItem(nUser, 8109, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
				{
					if(GiveItem(nUser, 8109, 1)==MAX_INVEN) 
						break;									//	지급 실패시 리턴
				}
				QUEST_LEVEL(eScenario3A) = 10;
				SendQuestHistory( nUser );

//				Party_ClearQuestAndGiveItem(nUser, eScenario3A, 8109, 1);
			}
			CHECK_QUEST(eScenario3D)
			{
				if ( QUEST_LEVEL(eScenario3D) != 8 ) break;
				if ( !GetProbability( 1 ) ) break;
				
				if(FindItem(nUser, 8124, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
				{
					if(GiveItem(nUser, 8124, 1)==MAX_INVEN) 
						break;									//	지급 실패시 리턴
				}

				if( FindItem(nUser, 8123, 1) != MAX_INVEN && FindItem(nUser, 8124, 1) != MAX_INVEN )
				{
					pMob[nUser].MOB.byQuest[eScenario3D] = 9;
					SendQuestHistory( nUser );
				}

//				Party_ClearQuestAndGiveItem(nUser, eScenario3D, 8124, 1, false);

				//int fol = 0;
				//int nLeader = pMob[nUser].Leader;
				//if(nLeader==0) nLeader = nUser;

				//for (int i=0;i<MAX_PARTY+1;i++)
				//{   if (i==0) fol = nLeader;
				//	else      fol = pMob[nLeader].m_irgParty[i-1];
   	// 				if	(fol<=0||fol>=MAX_USER) continue;
				//	if ( pMob[fol].MOB.byQuest[eScenario3D] != 8) continue;
				//	if( FindItem(fol, 8123, 1) != MAX_INVEN && FindItem(fol, 8124, 1) != MAX_INVEN )
				//	{
				//		pMob[fol].MOB.byQuest[eScenario3D] = 9;
				//		SendQuestHistory( fol );
				//		continue;
				//	}
				//}
			}
		} break;
	case eSarparaja:
		{	// eScenario3B ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3B) != 13 ) break;
			if ( !GetProbability( 1 ) ) break;

			if(FindItem(nUser, 8113, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
			{
				if(GiveItem(nUser, 8113, 1)==MAX_INVEN) 
					break;									//	지급 실패시 리턴
			}
			QUEST_LEVEL(eScenario3B) = 14;
			SendQuestHistory( nUser );

//			Party_ClearQuestAndGiveItem(nUser, eScenario3B, 8113, 1);
		} break;
	case eGoldSoldier:
		{	// eScenario3C ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3C) != 10 ) break;
			if ( !GetProbability( 5 ) ) break;

			if(FindItem(nUser, 8116, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
			{
				if(GiveItem(nUser, 8116, 1)==MAX_INVEN) 
					break;									//	지급 실패시 리턴
			}
			QUEST_LEVEL(eScenario3C) = 11;
			SendQuestHistory( nUser );

//			Party_ClearQuestAndGiveItem(nUser, eScenario3C, 8116, 1);
		} break;
	case eWhagui:
		{	// eScenario3C ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3C) != 14 ) break;
			if ( !GetProbability( 1 ) ) break;

			if(FindItem(nUser, 8117, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
			{
				if(GiveItem(nUser, 8117, 1)==MAX_INVEN) 
					break;									//	지급 실패시 리턴
			}

			if( FindItem(nUser, 8117, 1) != MAX_INVEN && FindItem(nUser, 8118, 1) != MAX_INVEN && FindItem(nUser, 8119, 1) != MAX_INVEN && FindItem(nUser, 8120, 1) != MAX_INVEN )
			{
				pMob[nUser].MOB.byQuest[eScenario3C] = 15;
				SendQuestHistory( nUser );
			}
//			Party_ClearQuestAndGiveItem(nUser, eScenario3C, 8117, 1, false);

/*			int fol = 0;
			int nLeader = pMob[nUser].Leader;
			if(nLeader==0) nLeader = nUser;

			for (int i=0;i<MAX_PARTY+1;i++)
			{   if (i==0) fol = nLeader;
				else      fol = pMob[nLeader].m_irgParty[i-1];
   	 			if	(fol<=0||fol>=MAX_USER) continue;
				if ( pMob[fol].MOB.byQuest[eScenario3C] != 14) continue;
				if( FindItem(fol, 8117, 1) != MAX_INVEN && FindItem(fol, 8118, 1) != MAX_INVEN && FindItem(fol, 8119, 1) != MAX_INVEN && FindItem(fol, 8120, 1) != MAX_INVEN )
				{
					pMob[fol].MOB.byQuest[eScenario3C] = 15;
					SendQuestHistory( fol );
					continue;
				}
			}
			*/
		} break;
	case ePangwho:
		{	// eScenario3C ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3C) != 14 ) break;
			if ( !GetProbability( 1 ) ) break;

			if(FindItem(nUser, 8118, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
			{
				if(GiveItem(nUser, 8118, 1)==MAX_INVEN) 
					break;									//	지급 실패시 리턴
			}
			if( FindItem(nUser, 8117, 1) != MAX_INVEN && FindItem(nUser, 8118, 1) != MAX_INVEN && FindItem(nUser, 8119, 1) != MAX_INVEN && FindItem(nUser, 8120, 1) != MAX_INVEN )
			{
				pMob[nUser].MOB.byQuest[eScenario3C] = 15;
				SendQuestHistory( nUser );
			}


//			Party_ClearQuestAndGiveItem(nUser, eScenario3C, 8118, 1, false);

/*			int fol = 0;
			int nLeader = pMob[nUser].Leader;
			if(nLeader==0) nLeader = nUser;

			for (int i=0;i<MAX_PARTY+1;i++)
			{   if (i==0) fol = nLeader;
				else      fol = pMob[nLeader].m_irgParty[i-1];
   	 			if	(fol<=0||fol>=MAX_USER) continue;
				if ( pMob[fol].MOB.byQuest[eScenario3C] != 14) continue;
				if( FindItem(fol, 8117, 1) != MAX_INVEN && FindItem(fol, 8118, 1) != MAX_INVEN && FindItem(fol, 8119, 1) != MAX_INVEN && FindItem(fol, 8120, 1) != MAX_INVEN )
				{
					pMob[fol].MOB.byQuest[eScenario3C] = 15;
					SendQuestHistory( fol );
					continue;
				}
			}
			*/
		} break;
	case eChunho:
		{	// eScenario3C ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3C) != 14 ) break;
			if ( !GetProbability( 1 ) ) break;

			if(FindItem(nUser, 8119, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
			{
				if(GiveItem(nUser, 8119, 1)==MAX_INVEN) 
					break;									//	지급 실패시 리턴
			}
			if( FindItem(nUser, 8117, 1) != MAX_INVEN && FindItem(nUser, 8118, 1) != MAX_INVEN && FindItem(nUser, 8119, 1) != MAX_INVEN && FindItem(nUser, 8120, 1) != MAX_INVEN )
			{
				pMob[nUser].MOB.byQuest[eScenario3C] = 15;
				SendQuestHistory( nUser );
			}
//			Party_ClearQuestAndGiveItem(nUser, eScenario3C, 8119, 1, false);

/*			int fol = 0;
			int nLeader = pMob[nUser].Leader;
			if(nLeader==0) nLeader = nUser;

			for (int i=0;i<MAX_PARTY+1;i++)
			{   if (i==0) fol = nLeader;
				else      fol = pMob[nLeader].m_irgParty[i-1];
   	 			if	(fol<=0||fol>=MAX_USER) continue;
				if ( pMob[fol].MOB.byQuest[eScenario3C] != 14) continue;
				if( FindItem(fol, 8117, 1) != MAX_INVEN && FindItem(fol, 8118, 1) != MAX_INVEN && FindItem(fol, 8119, 1) != MAX_INVEN && FindItem(fol, 8120, 1) != MAX_INVEN )
				{
					pMob[fol].MOB.byQuest[eScenario3C] = 15;
					SendQuestHistory( fol );
					continue;
				}
			}
			*/
		} break;
	case eSiksichug:
		{	// eScenario3C ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3C) != 14 ) break;
			if ( !GetProbability( 3 ) ) break;

			if(FindItem(nUser, 8120, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
			{
				if(GiveItem(nUser, 8120, 1)==MAX_INVEN) 
					break;									//	지급 실패시 리턴
			}
			if( FindItem(nUser, 8117, 1) != MAX_INVEN && FindItem(nUser, 8118, 1) != MAX_INVEN && FindItem(nUser, 8119, 1) != MAX_INVEN && FindItem(nUser, 8120, 1) != MAX_INVEN )
			{
				pMob[nUser].MOB.byQuest[eScenario3C] = 15;
				SendQuestHistory( nUser );
			}
//			Party_ClearQuestAndGiveItem(nUser, eScenario3C, 8120, 1, false);

/*			int fol = 0;
			int nLeader = pMob[nUser].Leader;
			if(nLeader==0) nLeader = nUser;

			for (int i=0;i<MAX_PARTY+1;i++)
			{   if (i==0) fol = nLeader;
				else      fol = pMob[nLeader].m_irgParty[i-1];
   	 			if	(fol<=0||fol>=MAX_USER) continue;
				if ( pMob[fol].MOB.byQuest[eScenario3C] != 14) continue;
				if( FindItem(fol, 8117, 1) != MAX_INVEN && FindItem(fol, 8118, 1) != MAX_INVEN && FindItem(fol, 8119, 1) != MAX_INVEN && FindItem(fol, 8120, 1) != MAX_INVEN )
				{
					pMob[fol].MOB.byQuest[eScenario3C] = 15;
					SendQuestHistory( fol );
					continue;
				}
			}
			*/
		} break;
	case eScorpion:
		{	// eScenario3D ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3D) != 5 ) break;
			if ( !GetProbability( 1 ) ) break;

			if(FindItem(nUser, 8121, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
			{
				if(GiveItem(nUser, 8121, 1)==MAX_INVEN) 
					break;									//	지급 실패시 리턴
			}
			QUEST_LEVEL(eScenario3D) = 6;
			SendQuestHistory( nUser );

//			Party_ClearQuestAndGiveItem(nUser, eScenario3D, 8121, 1);
		} break;
	case eScarecrow:
		{	// eScenario3D ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3D) != 8 ) break;
			if ( !GetProbability( 1 ) ) break;

			if(FindItem(nUser, 8123, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
			{
				if(GiveItem(nUser, 8123, 1)==MAX_INVEN) 
					break;									//	지급 실패시 리턴
			}
			if( FindItem(nUser, 8124, 1) != MAX_INVEN )
			{
				pMob[nUser].MOB.byQuest[eScenario3D] = 9;
				SendQuestHistory( nUser );
			}
//			Party_ClearQuestAndGiveItem(nUser, eScenario3D, 8123, 1, false);

/*			int fol = 0;
			int nLeader = pMob[nUser].Leader;
			if(nLeader==0) nLeader = nUser;

			for (int i=0;i<MAX_PARTY+1;i++)
			{   if (i==0) fol = nLeader;
				else      fol = pMob[nLeader].m_irgParty[i-1];
   	 			if	(fol<=0||fol>=MAX_USER) continue;
				if ( pMob[fol].MOB.byQuest[eScenario3D] != 8) continue;
				if( FindItem(fol, 8124, 1) != MAX_INVEN )
				{
					pMob[fol].MOB.byQuest[eScenario3D] = 9;
					SendQuestHistory( fol );
					continue;
				}
			}
			*/
		} break;
	case eSsauabi:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3D) != 13 ) break;
			if ( !GetProbability( 10 ) ) break;

			if(FindItem(nUser, 8137, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
			{
				if(GiveItem(nUser, 8137, 1)==MAX_INVEN) 
					break;									//	지급 실패시 리턴
			}
			QUEST_LEVEL(eScenario3D) = 14;
			SendQuestHistory( nUser );

//			Party_ClearQuestAndGiveItem(nUser, eScenario3D, 8137, 1);
		}	break;
	case eNaokiSsauabi:
		{	// eScenario3D ///////////////////////////////////////////////////////////////////////////
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3D) != 11 ) break;
			QUEST_LEVEL(eScenario3D) = 12;
			SendQuestHistory( nUser );
		} break;
	case eGutpa1:
	case eGutpa2:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3E) != 6 ) break;
			if ( !GetProbability( 1 ) ) break;

			if(FindItem(nUser, 8108, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
			{
				if(GiveItem(nUser, 8108, 1)==MAX_INVEN) 
					break;									//	지급 실패시 리턴
			}
			QUEST_LEVEL(eScenario3E) = 7;
			SendQuestHistory( nUser );

//			Party_ClearQuestAndGiveItem(nUser, eScenario3E, 8108, 1);
		} break;
	case eGutpaFarmer1:
	case eGutpaFarmer2:
	case eGutpaSoldier1:
	case eGutpaSoldier2:
		{
			if ( !bMonsterKill ) break;
			if ( QUEST_LEVEL(eScenario3E) != 9 ) break;
			if ( !GetProbability( 1 ) ) break;

			if(FindItem(nUser, 8138, 1)==MAX_INVEN)			//	해당아이템이 없을 경우 지급한다
			{
				if(GiveItem(nUser, 8138, 1)==MAX_INVEN) 
					break;									//	지급 실패시 리턴
			}
			QUEST_LEVEL(eScenario3E) = 10;
			SendQuestHistory( nUser );

//			Party_ClearQuestAndGiveItem(nUser, eScenario3E, 8138, 1);
		} break;
	default:
		{
			if ( CHTParamIDCheck::HT_bIsNPC(snNPCIndex) ) NotifyQuestLevel( nUser, snNPCIndex, 0, 0 );
		} break;
	}
	return TRUE;
}

BOOL QUEST_OnDialog( int nUser, short snDialog, byte byResult )
{
	if ( nUser <= 0 || nUser >= MAX_USER ) return TRUE;
	CMob *pCurMob = &pMob[nUser];
	STRUCT_MOB *pS_Mob = &pCurMob->MOB;

	struct tm when;
	time_t now; time(&now);

	switch( snDialog )
	{
	case eDialogInit:
		{
			if ( byResult != eResultOK ) 
			{
				QUEST_LEVEL(eTutorialInitial) = 0;
				QUEST_LEVEL(eScenarioA) = 1;
			}
			else
			{
				QUEST_LEVEL(eTutorialInitial) = 255;
				sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eTutorialInitial );
				Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
				QUEST_LEVEL(eTutorialA) = 1;
			}
			SendQuestHistory( nUser );
		} break;
	case eTutorialRestart:
		{
			if ( byResult != eResultOK ) break;
			QUEST_LEVEL(eTutorialInitial) = 255;
			sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eTutorialInitial );
			Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
			QUEST_LEVEL(eTutorialA) = 1;
			SendQuestHistory( nUser );
		} break;
	case eChangeClass1:
		{
			if ( byResult != eResultOK ) break;
			QUEST_LEVEL( eChangeClass1 ) = 2;
			SendQuestHistory( nUser );
		} break;
	case eScenarioA:
		{
			if ( QUEST_LEVEL(eScenarioA) == 255 ) break;

			if ( byResult == eResultOK )
			{
				QUEST_LEVEL(eScenarioA) = 2;
				QUEST_LEVEL(eScenarioB) = 1;
			}
			else
			{
				QUEST_LEVEL(eScenarioA) = 3;
			}
			SendQuestHistory( nUser );
		} break;
	case eScenarioB:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenarioB);

			if ( byResult == eResultOK )
			{
				QUEST_LEVEL(eScenarioA) = 255;
				sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioA );
				Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
				QUEST_LEVEL(eScenarioB) = 2;
				QUEST_LEVEL(eScenarioC) = 1;
			}
			else
			{
				QUEST_LEVEL(eScenarioB) = 3;
			}
			SendQuestHistory( nUser );
		} break;
	case eScenarioC:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenarioC);

			if ( byResult == eResultOK )	
			{
				QUEST_LEVEL(eScenarioC) = 2;
				QUEST_LEVEL(eScenarioB) = 255;
				sprintf( temp, "qst %s Complete %d", pMob[nUser].MOB.szName, eScenarioB );
				Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
			}
			else QUEST_LEVEL(eScenarioC) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenarioD:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenarioD);

			if ( byResult == eResultOK )	
			{
				QUEST_LEVEL(eScenarioD) = 2;
			}
			else QUEST_LEVEL(eScenarioD) = 3;

			SendQuestHistory( nUser );
		} break;
	case eScenarioE:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenarioE);

			if ( byResult == eResultOK )
			{
				if ( GiveItem( nUser, 8008, 2 ) != MAX_INVEN )
				{
					QUEST_LEVEL(eScenarioE) = 2;
					SendQuestHistory( nUser );
				}
				else
				{
					NotifyDialog( nUser, 1 );
					break;
				}
			}
			else QUEST_LEVEL(eScenarioE) = 3;

			SendQuestHistory( nUser );
		} break;
	case eScenarioF:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenarioF);

			if ( byResult == eResultOK )	
			{
				QUEST_LEVEL(eScenarioF) = 2;
				QUEST_LEVEL(eQuestTemp1) = 0;
			}
			else
			{
				QUEST_LEVEL(eScenarioF) = 3; 
			}
			SendQuestHistory( nUser );
		} break;
	case eScenarioG:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenarioG);

			if ( byResult == eResultOK )	
			{
				QUEST_LEVEL(eScenarioG) = 2;
				RemoveItem(nUser, 8012, 1);
				GiveItem(nUser, 8013, 1);
			}
			else							
			{
				QUEST_LEVEL(eScenarioG) = 3; 
			}

			SendQuestHistory( nUser );
		} break;
	case eScenarioH:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenarioH);

			if ( byResult == eResultOK )
			{
				switch ( pMob[nUser].MOB.snTribe )
				{
				case TRIBE_NAGA:
				case TRIBE_KINNARA:
					QUEST_LEVEL(eScenarioH) = 10;
					break;
				case TRIBE_ASURA:
				case TRIBE_RAKSHASA:
					QUEST_LEVEL(eScenarioH) = 11;
					break;
				case TRIBE_YAKSA:
					QUEST_LEVEL(eScenarioH) = 9;
					break;
				case TRIBE_GANDHARVA:
					QUEST_LEVEL(eScenarioH) = 7;
					break;
				case TRIBE_GARUDA:
					QUEST_LEVEL(eScenarioH) = 2;
					break;
				case TRIBE_DEVA:
					QUEST_LEVEL(eScenarioH) = 5;
					break;
				}
			}
			else QUEST_LEVEL(eScenarioH) = 3; 
			QUEST_LEVEL(eQuestTemp1) = 0;
			SendQuestHistory( nUser );
		} break;
	case eScenarioI:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenarioI);

			if ( byResult == eResultOK )	QUEST_LEVEL(eScenarioI) = 2;
			else							QUEST_LEVEL(eScenarioI) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenarioJ:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenarioJ);

			if ( byResult == eResultOK )	QUEST_LEVEL(eScenarioJ) = 2;
			else							QUEST_LEVEL(eScenarioJ) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario2A:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario2A);

			if ( byResult == eResultOK )	
			{
				QUEST_LEVEL(eScenario2A) = 2;
				QUEST_LEVEL(eMonsterKill1) = 0;
			}
			else							QUEST_LEVEL(eScenario2A) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario2B:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario2B);

			if ( byResult == eResultOK )
			{
				EMPTY_INVEN_TEST( 1 );
				GiveItem( nUser, 8017, 1 );
				QUEST_LEVEL(eScenario2B) = 2;
			}
			else							QUEST_LEVEL(eScenario2B) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario2B1:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario2B1);

			if ( byResult == eResultOK )
			{
				EMPTY_INVEN_TEST( 1 );
				GiveItem( nUser, 8020, 1 );
				QUEST_LEVEL(eScenario2B1) = 2;
			}
			else							QUEST_LEVEL(eScenario2B1) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario2C:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario2C);

			if ( byResult == eResultOK )	QUEST_LEVEL(eScenario2C) = 2;
			else							QUEST_LEVEL(eScenario2C) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario2D:
		{
			if ( QUEST_LEVEL(eScenario2D) == 255 ) break;

			if ( byResult == eResultOK )	
			{
				//if ( FindItem( nUser, 4291, 1 ) != MAX_INVEN )
				//{
					QUEST_LEVEL(eScenario2D) = 2;
				//}
			}
			else							QUEST_LEVEL(eScenario2D) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario2E:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario2E);

			if ( byResult == eResultOK )	QUEST_LEVEL(eScenario2E) = 2;
			else							QUEST_LEVEL(eScenario2E) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario2F:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario2F);

			if ( byResult == eResultOK )	QUEST_LEVEL(eScenario2F) = 2;
			else							QUEST_LEVEL(eScenario2F) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario2G:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario2G);

			if ( byResult == eResultOK )	QUEST_LEVEL(eScenario2G) = 2;
			else							QUEST_LEVEL(eScenario2G) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario2H:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario2H);

			if ( byResult == eResultOK )	
			{
				EMPTY_INVEN_TEST( 1 );
				QUEST_LEVEL(eScenario2H) = 2;
				GiveItem( nUser, 8026, 1 );
			}
			else							QUEST_LEVEL(eScenario2H) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario2I:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario2I);

			if ( byResult == eResultOK )	QUEST_LEVEL(eScenario2I) = 2;
			else							QUEST_LEVEL(eScenario2I) = 3;
			SendQuestHistory( nUser );
		} break;
	case eChangeClass2:
		{
			if ( QUEST_LEVEL(eChangeClass2) != 0 ) break;
			EMPTY_INVEN_TEST( 1 );

			if ( byResult == 0 ) QUEST_LEVEL(eChangeClass2A) = 1;
			else QUEST_LEVEL(eChangeClass2B) = 1;
			QUEST_LEVEL(eChangeClass2) = 2;
			QUEST_LEVEL(eChangeClass2C) = 1;
			QUEST_LEVEL(eChangeClass2D) = 1;
			QUEST_LEVEL(eQuestTemp2) = 0;
			QUEST_LEVEL(eQuestTemp3) = 0;
			QUEST_LEVEL(eQuestTemp4) = 0;
			QUEST_LEVEL(eQuestTemp5) = 0;

			switch ( pMob[nUser].MOB.snTribe )
			{
			case TRIBE_NAGA:
			case TRIBE_KINNARA:
				if ( byResult == 0 ) GiveItem( nUser, 8056, 1 );
				else GiveItem( nUser, 8055, 1 );
				break;
			case TRIBE_ASURA:
			case TRIBE_RAKSHASA:
				if ( byResult == 0 ) GiveItem( nUser, 8057, 1 );
				else GiveItem( nUser, 8058, 1 );
				break;
			case TRIBE_YAKSA:
			case TRIBE_GANDHARVA:
				if ( byResult == 0 ) GiveItem( nUser, 8059, 1 );
				else GiveItem( nUser, 8060, 1 );
				break;
			case TRIBE_DEVA:
			case TRIBE_GARUDA:
				if ( byResult == 0 ) GiveItem( nUser, 8061, 1 );
				else GiveItem( nUser, 8062, 1 );
				break;
			}
			SendQuestHistory( nUser );
		} break;
	case eChangeClass2C:
		{
			if ( QUEST_LEVEL(eChangeClass2C) == 255 ) break;

			switch ( byResult )
			{
			case 1:
				if ( GiveItem( nUser, 8071, 1 ) != MAX_INVEN )
				{
					QUEST_LEVEL(eChangeClass2C) = 7;
					SendQuestHistory( nUser );
				}
				else
				{
					NotifyDialog( nUser, 1 );
				}
				break;
			case 2:
				QUEST_LEVEL(eChangeClass2C) = 4;
				SendQuestHistory( nUser );
				break;
			}
		} break;
	case eJinaA:
		{
			CHECK_DIALOG_QUEST_CHECK(eJinaA);
			if ( byResult == eResultOK )	QUEST_LEVEL(eJinaA) = 2;
			else							QUEST_LEVEL(eJinaA) = 3;
			SendQuestHistory( nUser );
		} break;
	case eJinaB:
		{
			CHECK_DIALOG_QUEST_CHECK(eJinaB);
			if ( byResult == eResultOK )	QUEST_LEVEL(eJinaB) = 2;
			else							QUEST_LEVEL(eJinaB) = 3;
			SendQuestHistory( nUser );
		} break;
	case eJinaC:
		{
			CHECK_DIALOG_QUEST_CHECK(eJinaC);
			if ( byResult == eResultOK )	QUEST_LEVEL(eJinaC) = 2;
			else							QUEST_LEVEL(eJinaC) = 3;
			SendQuestHistory( nUser );
		} break;
	case eJinaD:
		{
			CHECK_DIALOG_QUEST_CHECK(eJinaD);
			if ( byResult == eResultOK )	QUEST_LEVEL(eJinaD) = 2;
			else							QUEST_LEVEL(eJinaD) = 3;
			SendQuestHistory( nUser );
		} break;
	case eJinaE:
		{
			CHECK_DIALOG_QUEST_CHECK(eJinaE);
			if ( byResult == eResultOK )	QUEST_LEVEL(eJinaE) = 2;
			else							QUEST_LEVEL(eJinaE) = 3;
			SendQuestHistory( nUser );
		} break;
	case eExileA:
		{
			CHECK_DIALOG_QUEST_CHECK(eExileA);
			if ( byResult == eResultOK )	QUEST_LEVEL(eExileA) = 2;
			else							QUEST_LEVEL(eExileA) = 3;
			SendQuestHistory( nUser );
		} break;
	case eExileB:
		{
			CHECK_DIALOG_QUEST_CHECK(eExileB);
			if ( byResult == eResultOK )	
			{
				if ( pMob[nUser].MOB.nRupiah >= 100000 )
				{
					GiveMoney( nUser, -100000 );
					QUEST_LEVEL(eExileB) = 2;
				}
			}
			else							QUEST_LEVEL(eExileB) = 3;
			SendQuestHistory( nUser );
		} break;
	case eExileC:
		{
			CHECK_DIALOG_QUEST_CHECK(eExileC);
			if ( byResult == eResultOK )	QUEST_LEVEL(eExileC) = 2;
			else							QUEST_LEVEL(eExileC) = 3;
			SendQuestHistory( nUser );
		} break;
	case eExileD:
		{
			CHECK_DIALOG_QUEST_CHECK(eExileD);
			if ( byResult == eResultOK )	QUEST_LEVEL(eExileD) = 2;
			else							QUEST_LEVEL(eExileD) = 3;
			SendQuestHistory( nUser );
		} break;
	case eExileE:
		{
			CHECK_DIALOG_QUEST_CHECK(eExileE);
			if ( byResult == eResultOK )	QUEST_LEVEL(eExileE) = 2;
			else							QUEST_LEVEL(eExileE) = 3;
			SendQuestHistory( nUser );
		} break;
	case eBukduA:
		{
			if ( QUEST_LEVEL( eBukduA ) == 255 ) break;
			if ( byResult == eResultOK )	QUEST_LEVEL(eBukduA) = 2;
			else							QUEST_LEVEL(eBukduA) = 3;
			SendQuestHistory( nUser );
		} break;
	case eBukduB:
		{
			CHECK_DIALOG_QUEST_CHECK(eBukduB);
			if ( byResult == eResultOK )	QUEST_LEVEL(eBukduB) = 2;
			else							QUEST_LEVEL(eBukduB) = 3;
			SendQuestHistory( nUser );
		} break;
	case eBukduC:
		{
			CHECK_DIALOG_QUEST_CHECK(eBukduC);
			if ( byResult == eResultOK )	QUEST_LEVEL(eBukduC) = 2;
			else							QUEST_LEVEL(eBukduC) = 3;
			SendQuestHistory( nUser );
		} break;
	case eBukduD:
		{
			CHECK_DIALOG_QUEST_CHECK(eBukduD);
			if ( byResult == eResultOK )	QUEST_LEVEL(eBukduD) = 2;
			else							QUEST_LEVEL(eBukduD) = 3;
			SendQuestHistory( nUser );
		} break;
	case eBukduE:
		{
			CHECK_DIALOG_QUEST_CHECK(eBukduE);
			if ( byResult == eResultOK )	QUEST_LEVEL(eBukduE) = 2;
			else							QUEST_LEVEL(eBukduE) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario3A:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario3A);
			if ( byResult == eResultOK )	QUEST_LEVEL(eScenario3A) = 2;
			else							QUEST_LEVEL(eScenario3A) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario3B:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario3B);
			if ( byResult == eResultOK )	QUEST_LEVEL(eScenario3B) = 2;
			else							QUEST_LEVEL(eScenario3B) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario3C:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario3C);
			if ( byResult == eResultOK )	QUEST_LEVEL(eScenario3C) = 2;
			else							QUEST_LEVEL(eScenario3C) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario3D:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario3D);
			if ( byResult == eResultOK )	QUEST_LEVEL(eScenario3D) = 2;
			else							QUEST_LEVEL(eScenario3D) = 3;
			SendQuestHistory( nUser );
		} break;
	case eScenario3E:
		{
			CHECK_DIALOG_QUEST_CHECK(eScenario3E);
			if ( byResult == eResultOK )	QUEST_LEVEL(eScenario3E) = 2;
			else							QUEST_LEVEL(eScenario3E) = 3;
			SendQuestHistory( nUser );
		} break;
	}

	return TRUE;
}

void QUEST_OnContributeItem( int nUser, int nItemIndex )
{
	switch( nItemIndex )
	{
	case eDipailla:
		if( QUEST_LEVEL(eScenario3E) == 16)
		{
			if(QUEST_LEVEL(eQuestTemp1)<2) 
			{
				QUEST_LEVEL(eQuestTemp1)++;
				if( QUEST_LEVEL(eQuestTemp1)>=2 && QUEST_LEVEL(eQuestTemp2)>=2 && QUEST_LEVEL(eQuestTemp3)>=3 && QUEST_LEVEL(eQuestTemp4)>=3)
				{
					QUEST_LEVEL(eScenario3E) = 17;
					SendQuestHistory( nUser );
					QUEST_LEVEL(eQuestTemp1) = 0;
					QUEST_LEVEL(eQuestTemp2) = 0;
					QUEST_LEVEL(eQuestTemp3) = 0;
					QUEST_LEVEL(eQuestTemp4) = 0;
				}
			}
		}
		break;
	case eIlla:
		if( QUEST_LEVEL(eScenario3E) == 16)
		{
			if(QUEST_LEVEL(eQuestTemp2)<2) 
			{
				QUEST_LEVEL(eQuestTemp2)++;
				if( QUEST_LEVEL(eQuestTemp1)>=2 && QUEST_LEVEL(eQuestTemp2)>=2 && QUEST_LEVEL(eQuestTemp3)>=3 && QUEST_LEVEL(eQuestTemp4)>=3)
				{
					QUEST_LEVEL(eScenario3E) = 17;
					SendQuestHistory( nUser );
					QUEST_LEVEL(eQuestTemp1) = 0;
					QUEST_LEVEL(eQuestTemp2) = 0;
					QUEST_LEVEL(eQuestTemp3) = 0;
					QUEST_LEVEL(eQuestTemp4) = 0;
				}
			}
		}
		break;
	case eSurapa:
		if( QUEST_LEVEL(eScenario3E) == 16)
		{
			if(QUEST_LEVEL(eQuestTemp3)<3) 
			{
				QUEST_LEVEL(eQuestTemp3)++;
				if( QUEST_LEVEL(eQuestTemp1)>=2 && QUEST_LEVEL(eQuestTemp2)>=2 && QUEST_LEVEL(eQuestTemp3)>=3 && QUEST_LEVEL(eQuestTemp4)>=3)
				{
					QUEST_LEVEL(eScenario3E) = 17;
					SendQuestHistory( nUser );
					QUEST_LEVEL(eQuestTemp1) = 0;
					QUEST_LEVEL(eQuestTemp2) = 0;
					QUEST_LEVEL(eQuestTemp3) = 0;
					QUEST_LEVEL(eQuestTemp4) = 0;
				}
			}
		}
		break;
	case eAzis:
		if( QUEST_LEVEL(eScenario3E) == 16)
		{
			if(QUEST_LEVEL(eQuestTemp4)<3) 
			{
				QUEST_LEVEL(eQuestTemp4)++;
				if( QUEST_LEVEL(eQuestTemp1)>=2 && QUEST_LEVEL(eQuestTemp2)>=2 && QUEST_LEVEL(eQuestTemp3)>=3 && QUEST_LEVEL(eQuestTemp4)>=3)
				{
					QUEST_LEVEL(eScenario3E) = 17;
					SendQuestHistory( nUser );
					QUEST_LEVEL(eQuestTemp1) = 0;
					QUEST_LEVEL(eQuestTemp2) = 0;
					QUEST_LEVEL(eQuestTemp3) = 0;
					QUEST_LEVEL(eQuestTemp4) = 0;
				}
			}
		}
		break;
	}
}

void QUEST_OnContribute( int nUser, int nRupia )
{
	if ( QUEST_LEVEL(eBukduC) == 5)
	{
		if ( nRupia >= 1000000 )
		{
			QUEST_LEVEL(eBukduC) = 6;
			SendQuestHistory( nUser );
		}
	}
}

static const g_nExiltCMonsterKillCount = 52;
static const short g_snExileCMonstKillTable[g_nExiltCMonsterKillCount] =
{
	2001, 2002, 2004, 2003, 2005, 2138, 2132, 2133, 2006, 2139, 
	2007, 2134, 2008, 2009, 2011, 2010, 2012, 2013, 2140, 2135,
	2136, 2014, 2137, 2015, 2016, 2017, 2018, 2146, 2019, 2074,
	2075, 2142, 2144, 2084, 2143, 2085, 2078, 2076, 2082, 2145,
	2077, 2083, 2079, 2080, 2081, 2167, 2030, 2031, 2088, 2089,
	2090, 2092
};

BOOL QUEST_OnExileCKillMonster( int nUser, int nEvent, short snNPCIndex, int nItemIndex )
{
	for ( int nLevel = 0 ; nLevel < g_nExiltCMonsterKillCount ; nLevel++ )
	{
		if ( g_snExileCMonstKillTable[nLevel] == nEvent ) break;
	}
	if ( nLevel >= g_nExiltCMonsterKillCount ) return FALSE;

	nLevel += 5;
	if ( pMob[nUser].MOB.byQuest[eExileC] == nLevel ) ++pMob[nUser].MOB.byQuest[eMonsterKill1];
	else return FALSE;

	if ( pMob[nUser].MOB.byQuest[eMonsterKill1] >= 10 )
	{
		pMob[nUser].MOB.byQuest[eExileC]++;
		pMob[nUser].MOB.byQuest[eMonsterKill1] = 0;
	}
	SendQuestHistory( nUser );
	return TRUE;
}

BOOL QUEST_LoadTask()
{
	TASK_INFO sTaskInfo; ZeroMemory( &sTaskInfo, sizeof(TASK_INFO) );

	for ( int nTaskNumber = HT_PARAMTYPE_TASKQUEST_START ; nTaskNumber <= HT_PARAMTYPE_TASKQUEST_END ; nTaskNumber++ )
	{
		if ( !g_ParamMgr.HT_bLockID( nTaskNumber ) )
		{
			g_ParamMgr.HT_bUnLockID( nTaskNumber );
			continue;
		}

		if (	!g_ParamMgr.HT_bGetTaskSource1( &sTaskInfo.bySourceType[0], &sTaskInfo.snSourceIndex[0], &sTaskInfo.nSourceCount[0] ) 
			||	!g_ParamMgr.HT_bGetTaskSource2( &sTaskInfo.bySourceType[1], &sTaskInfo.snSourceIndex[1], &sTaskInfo.nSourceCount[1] )
			||	!g_ParamMgr.HT_bGetTaskSource3( &sTaskInfo.bySourceType[2], &sTaskInfo.snSourceIndex[2], &sTaskInfo.nSourceCount[2] )
			||	!g_ParamMgr.HT_bGetTaskSource4( &sTaskInfo.bySourceType[3], &sTaskInfo.snSourceIndex[3], &sTaskInfo.nSourceCount[3] )
			||	!g_ParamMgr.HT_bGetTaskSource5( &sTaskInfo.bySourceType[4], &sTaskInfo.snSourceIndex[4], &sTaskInfo.nSourceCount[4] )
			||	!g_ParamMgr.HT_bGetTaskSource6( &sTaskInfo.bySourceType[5], &sTaskInfo.snSourceIndex[5], &sTaskInfo.nSourceCount[5] )
			||	!g_ParamMgr.HT_bGetTaskReward1( &sTaskInfo.byRewardPriority[0], &sTaskInfo.byRewardType[0], &sTaskInfo.snRewardRate[0], &sTaskInfo.snRewardIndex[0], &sTaskInfo.nRewardCount[0] )
			||	!g_ParamMgr.HT_bGetTaskReward2( &sTaskInfo.byRewardPriority[1], &sTaskInfo.byRewardType[1], &sTaskInfo.snRewardRate[1], &sTaskInfo.snRewardIndex[1], &sTaskInfo.nRewardCount[1] )
			||	!g_ParamMgr.HT_bGetTaskReward3( &sTaskInfo.byRewardPriority[2], &sTaskInfo.byRewardType[2], &sTaskInfo.snRewardRate[2], &sTaskInfo.snRewardIndex[2], &sTaskInfo.nRewardCount[2] ) 
			||	!g_ParamMgr.HT_bGetTaskReward4( &sTaskInfo.byRewardPriority[3], &sTaskInfo.byRewardType[3], &sTaskInfo.snRewardRate[3], &sTaskInfo.snRewardIndex[3], &sTaskInfo.nRewardCount[3] ) 
			||	!g_ParamMgr.HT_bGetTaskReward5( &sTaskInfo.byRewardPriority[4], &sTaskInfo.byRewardType[4], &sTaskInfo.snRewardRate[4], &sTaskInfo.snRewardIndex[4], &sTaskInfo.nRewardCount[4] ) 
			||	!g_ParamMgr.HT_bGetTaskNPCID( &sTaskInfo.snNPCID[0], &sTaskInfo.snNPCID[1], &sTaskInfo.snNPCID[2], &sTaskInfo.snNPCID[3], &sTaskInfo.snNPCID[4] ) 
			||	!g_ParamMgr.HT_bGetTaskLevel( &sTaskInfo.byMinLevel, &sTaskInfo.byMaxLevel ) )
		{	// 에러메시지 보내고 종료
			g_ParamMgr.HT_bUnLockID( nTaskNumber );
			continue;
		}
		g_ParamMgr.HT_bUnLockID( nTaskNumber );
		g_mapTask[nTaskNumber] = sTaskInfo;
	}

	return TRUE;
}

void QUEST_SetTask( int nTaskNumber, TASK_INFO *pTaskInfo )
{
	g_mapTask[nTaskNumber] = *pTaskInfo;
}

void QUEST_OnTask( int nUser, int nTaskNumber, int nNPCIndex )
{
	if ( !CHTParamIDCheck::HT_bIsTaskQuest( nTaskNumber ) )
	{	// 에러메시지 보내고 종료
		SendTaskResult( nUser, nTaskNumber, eTaskResultWrongIndex );
		return;
	}

	//	NPC와의 거리체크 및 작업가능NPC 여부체크
	int nSource = 0;

	TaskItor itor = g_mapTask.find( nTaskNumber );
	if ( itor == g_mapTask.end() )
	{	// 에러메시지 보내고 종료
		SendTaskResult( nUser, nTaskNumber, eTaskResultWrongIndex );
		return;
	}

	TASK_INFO sTaskInfo = (*itor).second; 

	BOOL bIsExistNPC = FALSE;
	for ( int i = 0 ; i < MAX_TASKNPC_COUNT ; i++ )
	{
		if ( nNPCIndex == sTaskInfo.snNPCID[i] ) 
		{
			bIsExistNPC = TRUE;
			break;
		}
	}

	if ( !bIsExistNPC )
	{	// 에러메시지 보내고 종료
		SendTaskResult( nUser, nTaskNumber, eTaskResultWrongNPC );
		return;
	}

	if ( pMob[nUser].MOB.byLevel < sTaskInfo.byMinLevel || pMob[nUser].MOB.byLevel > sTaskInfo.byMaxLevel )
	{	// 레벨 조건을 만족시키지 못하면, 에러메시지 보내고 종료.
		SendTaskResult( nUser, nTaskNumber, eTaskResultLevel );
		return;
	}

	int nRemainMoney = pMob[nUser].MOB.nRupiah;
	int nSrcIndex;

	for ( int i = 0 ; i < MAX_TASKITEM_SOURCE ; i++ )
	{
		switch ( sTaskInfo.bySourceType[i] )
		{
		case eTaskRewardRupiah:
			nRemainMoney -= sTaskInfo.nSourceCount[i];
			break;
		case eTaskRewardItem:
			if ( ( nSrcIndex = FindItem( nUser, sTaskInfo.snSourceIndex[i], sTaskInfo.nSourceCount[i] ) ) == MAX_INVEN )
			{	// 에러메시지 보내고 종료
				SendTaskResult( nUser, nTaskNumber, eTaskResultNeedItem );
				return;
			}
			if ( pMob[nUser].MOB.Inven[nSrcIndex].byCount <= sTaskInfo.nSourceCount[i] ) nSource++;
			break;
		case eTaskRewardKarma:
			if ( sTaskInfo.nRewardCount[i] == 0 ) continue;
			if ( !GetProbability_10000( sTaskInfo.snRewardRate[i] ) 
				|| pMob[nUser].MOB.snKarma + sTaskInfo.nRewardCount[i] > g_irgSetting[eCnst_MaxKarma] )
			{
				SendTaskResult( nUser, nTaskNumber, eTaskResultKarmaLack );
				return;
			}
			break;
		}
	}

	if ( nRemainMoney < 0 )
	{	// 에러메시지 보내고 종료
		SendTaskResult(nUser, nTaskNumber, eTaskResultNeedMoney );
		return;
	}

	int nRequiredSlots = 0; 	// 인벤의 빈 공간을 확인한다.
	int nRealRewardCount = 0;
	for ( int i = 0 ; i < MAX_TASKITEM_REWARD ; i++ )
	{
		switch ( sTaskInfo.byRewardType[i] )
		{
		case eTaskRewardRupiah:
			if ( sTaskInfo.nRewardCount[i] == 0 ) continue;
			if ( GetProbability_10000( sTaskInfo.snRewardRate[i] ) )
			{
				nRealRewardCount++;
			}
			else
			{
				sTaskInfo.byRewardType[i] = 0;
				sTaskInfo.snRewardIndex[i] = 0;
				sTaskInfo.nRewardCount[i] = 0;
			}
			break;
		case eTaskRewardItem:
			if ( sTaskInfo.nRewardCount[i] == 0 ) continue;
			if ( GetProbability_10000( sTaskInfo.snRewardRate[i] ) )
			{
				nRealRewardCount++;
				byte byMaxCount = 0;
				if ( !g_ParamMgr.HT_bGetItemMaxCount( sTaskInfo.snRewardIndex[i], &byMaxCount ) ) continue;
				nRequiredSlots += ( byMaxCount != 0 ) ? (int)( ( sTaskInfo.nRewardCount[i] - 1 ) /  byMaxCount ) + 1 : 0;
			}
			else
			{
				sTaskInfo.byRewardType[i] = 0;
				sTaskInfo.snRewardIndex[i] = 0;
				sTaskInfo.nRewardCount[i] = 0;
			}
			break;
		case eTaskRewardKarma:
			if ( sTaskInfo.nRewardCount[i] == 0 ) continue;
			if ( GetProbability_10000( sTaskInfo.snRewardRate[i] ) )
			{
				if ( pMob[nUser].MOB.snKarma <= sTaskInfo.nRewardCount[i] )
				{
					SendTaskResult( nUser, nTaskNumber, eTaskResultKarmaLack );
					return;
				}
				nRealRewardCount++;
			}
			else
			{
				sTaskInfo.byRewardType[i] = 0;
				sTaskInfo.snRewardIndex[i] = 0;
				sTaskInfo.nRewardCount[i] = 0;
			}
			break;
		case eTaskRewardPrana:
			if ( sTaskInfo.nRewardCount[i] == 0 ) continue;
			if ( GetProbability_10000( sTaskInfo.snRewardRate[i] ) )
			{
				nRealRewardCount++;
			}
			else
			{
				sTaskInfo.byRewardType[i] = 0;
				sTaskInfo.snRewardIndex[i] = 0;
				sTaskInfo.nRewardCount[i] = 0;
			}
			break;
		case eTaskRewardGroupItem:
			if ( sTaskInfo.nRewardCount[i] == 0 ) continue;
			if ( GetProbability_10000( sTaskInfo.snRewardRate[i] ) )
			{
				nRealRewardCount++;
				nRequiredSlots ++;
			}
			else
			{
				sTaskInfo.byRewardType[i] = 0;
				sTaskInfo.snRewardIndex[i] = 0;
				sTaskInfo.nRewardCount[i] = 0;
			}
			break;
		}
	}

	if( nRequiredSlots > GetEmptyInvenCount( nUser ) )
	{	// 에러메시지 보내고 종료. 인벤이 부족하다.
		SendTaskResult( nUser, nTaskNumber, eTaskResultInvenLack );
		return;
	}

	for ( int i = 0 ; i < MAX_TASKITEM_SOURCE ; i++ ) // 요구 아이템들을 인벤에서 제거한다.
	{
		switch ( sTaskInfo.bySourceType[i] )
		{
		case eTaskRewardRupiah:
			if ( sTaskInfo.nSourceCount[i] == 0 ) break;
			GiveMoney( nUser, -sTaskInfo.nSourceCount[i] );
			break;
		case eTaskRewardItem:
			if ( sTaskInfo.nSourceCount[i] == 0 ) break;
			RemoveItem( nUser, sTaskInfo.snSourceIndex[i], sTaskInfo.nSourceCount[i] );
			break;
		case eTaskRewardPrana:
			pMob[nUser].DecPrana( sTaskInfo.nSourceCount[i] );
			break;
		case eTaskRewardKarma:
			pMob[nUser].MOB.snKarma += sTaskInfo.nSourceCount[i];
			if( g_irgSetting[eCnst_MaxKarma] < pMob[nUser].MOB.snKarma ) pMob[nUser].MOB.snKarma = g_irgSetting[eCnst_MaxKarma] ;
			pMob[nUser].NotifyUpdateUIMsg();
			pMob[nUser].BroadcastUpdateStatusMsg();
			break;
		}
	}

	if ( nRealRewardCount == 0 )
	{	// 에러메시지 보내고 종료. 확률상 아무 보상도 못받는다.
		sprintf( temp, "task User %s Index %d Failed by probability", pMob[nUser].MOB.szName, nTaskNumber );
		Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
		SendTaskResult( nUser, nTaskNumber, eTaskResultProbability );
		return;
	}

	// 보상을 한다.
	BOOL bPriorRewarded = FALSE;
	for ( int nPrior = 0 ; nPrior < MAX_TASKITEM_PRIORITY ; nPrior++ )
	{
		for( int i = 0 ; i < MAX_TASKITEM_REWARD ; i++ )
		{
			if ( nPrior != sTaskInfo.byRewardPriority[i] ) continue;
			if ( sTaskInfo.nRewardCount[i] == 0 ) continue;

			bPriorRewarded = TRUE;
			switch ( sTaskInfo.byRewardType[i] )
			{
			case eTaskRewardRupiah:
				GiveMoney( nUser, sTaskInfo.nRewardCount[i] );
				break;
			case eTaskRewardItem:
				GiveItem( nUser, sTaskInfo.snRewardIndex[i], sTaskInfo.nRewardCount[i] );
				break;
			case eTaskRewardPrana:
				pMob[nUser].AcquirePrana( sTaskInfo.nRewardCount[i] );
				break;
			case eTaskRewardKarma:
				pMob[nUser].MOB.snKarma -= sTaskInfo.nRewardCount[i];
				if( sTaskInfo.nRewardCount[i] > pMob[nUser].MOB.snKarma ) pMob[nUser].MOB.snKarma = sTaskInfo.nRewardCount[i];
				pMob[nUser].NotifyUpdateUIMsg();
				pMob[nUser].BroadcastUpdateStatusMsg();
				break;
			case eTaskRewardGroupItem:
				GiveGroupItem( nUser, sTaskInfo.snRewardIndex[i], sTaskInfo.nRewardCount[i] );
				break;
			}
		}
		if ( bPriorRewarded ) break;
	}

	// 타스크 퀘스트 성공 메시지를 보내준다.
	sprintf( temp, "task User %s Index %d Success", pMob[nUser].MOB.szName, nTaskNumber );
	Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
	SendTaskResult( nUser, nTaskNumber, eTaskResultSuccess );
}

void SendTaskResult( int nUser, int nTaskIndex, int nResult )
{
	MSG_STANDARDPARM sm; sm.wType = _MSG_Quest; sm.wPDULength = sizeof(MSG_STANDARDPARM) - sizeof(HEADER);
	sm.nID = nTaskIndex;
	sm.Parm = nResult;
	pUser[nUser].cSock.AddMessage( (char*)&sm, sizeof(MSG_STANDARDPARM) );
}

void NotifyQuestLevel( int nUser, short snNPCIndex, DWORD dwQuestIndex, byte byQuestLevel )
{
	S_SCP_QUEST_NOTIFY_LEVEL sm; sm.wType = SCP_QUEST_NOTIFY_LEVEL;
	sm.wPDULength = sizeof(S_SCP_QUEST_NOTIFY_LEVEL)-sizeof(HEADER);
	sm.snNPCIndex = snNPCIndex;
	memcpy(&sm.byIndex, &dwQuestIndex, sizeof(sm.byIndex));
	sm.byLevel = byQuestLevel;

	pUser[nUser].cSock.AddMessage( (char*)&sm, sizeof(S_SCP_QUEST_NOTIFY_LEVEL) );
}

void SendQuestHistory( int nUser )
{
	S_SCP_RESP_QUEST_HISTORY sm; sm.wType = SCP_RESP_QUEST_HISTORY;
	sm.wPDULength = sizeof(S_SCP_RESP_QUEST_HISTORY)-sizeof(HEADER);
	memcpy( sm.byQuest, pMob[nUser].MOB.byQuest, sizeof(BYTE) * MAX_EVENT_FLAG );

	pUser[nUser].cSock.AddMessage( (char*)&sm, sizeof(S_SCP_RESP_QUEST_HISTORY) );
}

int GmGive9Item( int nUser, int nItemIndex, int nItemCount )
{
	byte byMaxCount = 1;
	g_ParamMgr.HT_bGetItemMaxCount( nItemIndex, &byMaxCount );

	if ( byMaxCount == 0 ) byMaxCount = 1;
	int nSplit = nItemCount / byMaxCount;
	if ( nItemCount % byMaxCount != 0 ) nSplit++;

	int nEmpty = 0;
	int nTmpCount = nItemCount;

	for( int i = 0 ; i < pMob[nUser].byMaxInven ; i++ )
	{
		if ( pMob[nUser].MOB.Inven[i].snIndex == 0 ) nEmpty++;
	}
	if ( nEmpty < nSplit ) return MAX_INVEN;

	for ( int i = 0 ; i < nSplit ; i++ )
	{
		nEmpty = GetEmptyInven( nUser );
		ZeroMemory( &pMob[nUser].MOB.Inven[nEmpty], sizeof(STRUCT_ITEM) );

		pMob[nUser].MOB.Inven[nEmpty].snIndex = nItemIndex - HT_PARAMTYPE_ITEM_START + 1;
		pMob[nUser].MOB.Inven[nEmpty].byCount = ( nTmpCount > byMaxCount ) ? byMaxCount : nTmpCount;
		pMob[nUser].MOB.Inven[nEmpty].wSerial = (WORD)rand();
		pMob[nUser].MOB.Inven[nEmpty].byRefineLevel =9;

		short sDur = eDur_Indestructible ;
		g_ParamMgr.HT_bGetItemMaxDurability( nItemIndex, &sDur );
		pMob[nUser].MOB.Inven[nEmpty].snDurability = sDur;

		char szLog[256], szItem[128];
		BASE_GetItemCode( &pMob[nUser].MOB.Inven[nEmpty], szItem );
		sprintf( szLog, "get %s", szItem );
		Log( szLog, pUser[nUser].AccountName, pUser[nUser].IP );

		S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;
		sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_INVEN;
		sm.byIndex=nEmpty; sm.sitem=pMob[nUser].MOB.Inven[nEmpty];
		pUser[nUser].cSock.AddMessage((char*)&sm,sizeof(sm));

		nTmpCount -= byMaxCount;
	}
    SaveUser(nUser,0); //auto_save
	return nEmpty;
}

int GmGive5Item( int nUser, int nItemIndex, int nItemCount )
{
	byte byMaxCount = 1;
	g_ParamMgr.HT_bGetItemMaxCount( nItemIndex, &byMaxCount );

	if ( byMaxCount == 0 ) byMaxCount = 1;
	int nSplit = nItemCount / byMaxCount;
	if ( nItemCount % byMaxCount != 0 ) nSplit++;

	int nEmpty = 0;
	int nTmpCount = nItemCount;

	for( int i = 0 ; i < pMob[nUser].byMaxInven ; i++ )
	{
		if ( pMob[nUser].MOB.Inven[i].snIndex == 0 ) nEmpty++;
	}
	if ( nEmpty < nSplit ) return MAX_INVEN;

	for ( int i = 0 ; i < nSplit ; i++ )
	{
		nEmpty = GetEmptyInven( nUser );
		ZeroMemory( &pMob[nUser].MOB.Inven[nEmpty], sizeof(STRUCT_ITEM) );

		pMob[nUser].MOB.Inven[nEmpty].snIndex = nItemIndex - HT_PARAMTYPE_ITEM_START + 1;
		pMob[nUser].MOB.Inven[nEmpty].byCount = ( nTmpCount > byMaxCount ) ? byMaxCount : nTmpCount;
		pMob[nUser].MOB.Inven[nEmpty].wSerial = (WORD)rand();
		pMob[nUser].MOB.Inven[nEmpty].byRefineLevel =5;

		short sDur = eDur_Indestructible ;
		g_ParamMgr.HT_bGetItemMaxDurability( nItemIndex, &sDur );
		pMob[nUser].MOB.Inven[nEmpty].snDurability = sDur;

		char szLog[256], szItem[128];
		BASE_GetItemCode( &pMob[nUser].MOB.Inven[nEmpty], szItem );
		sprintf( szLog, "get %s", szItem );
		Log( szLog, pUser[nUser].AccountName, pUser[nUser].IP );

		S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;
		sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_INVEN;
		sm.byIndex=nEmpty; sm.sitem=pMob[nUser].MOB.Inven[nEmpty];
		pUser[nUser].cSock.AddMessage((char*)&sm,sizeof(sm));

		nTmpCount -= byMaxCount;
	}
    SaveUser(nUser,0); //auto_save
	return nEmpty;
}


int GiveItem( int nUser, int nItemIndex, int nItemCount )
{
	byte byMaxCount = 1;
	g_ParamMgr.HT_bGetItemMaxCount( nItemIndex, &byMaxCount );

	if ( byMaxCount == 0 ) byMaxCount = 1;
	int nSplit = nItemCount / byMaxCount;
	if ( nItemCount % byMaxCount != 0 ) nSplit++;

	int nEmpty = 0;
	int nTmpCount = nItemCount;

	for( int i = 0 ; i < pMob[nUser].byMaxInven ; i++ )
	{
		if ( pMob[nUser].MOB.Inven[i].snIndex == 0 ) nEmpty++;
	}
	if ( nEmpty < nSplit ) return MAX_INVEN;

	for ( int i = 0 ; i < nSplit ; i++ )
	{
		nEmpty = GetEmptyInven( nUser );
		ZeroMemory( &pMob[nUser].MOB.Inven[nEmpty], sizeof(STRUCT_ITEM) );

		pMob[nUser].MOB.Inven[nEmpty].snIndex = nItemIndex - HT_PARAMTYPE_ITEM_START + 1;
		pMob[nUser].MOB.Inven[nEmpty].byCount = ( nTmpCount > byMaxCount ) ? byMaxCount : nTmpCount;
		pMob[nUser].MOB.Inven[nEmpty].wSerial = (WORD)rand();
		

		short sDur = eDur_Indestructible ;
		g_ParamMgr.HT_bGetItemMaxDurability( nItemIndex, &sDur );
		pMob[nUser].MOB.Inven[nEmpty].snDurability = sDur;

		char szLog[256], szItem[128];
		BASE_GetItemCode( &pMob[nUser].MOB.Inven[nEmpty], szItem );
		sprintf( szLog, "get %s", szItem );
		Log( szLog, pUser[nUser].AccountName, pUser[nUser].IP );

		S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;
		sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_INVEN;
		sm.byIndex=nEmpty; sm.sitem=pMob[nUser].MOB.Inven[nEmpty];
		pUser[nUser].cSock.AddMessage((char*)&sm,sizeof(sm));

		nTmpCount -= byMaxCount;
	}
    SaveUser(nUser,0); //auto_save
	return nEmpty;
}

int GiveGroupItem( int nUser, int nGroupIndex, int nItemCount )
{
	if( 0 > nGroupIndex || eRwd_ItemGroup < nGroupIndex ) return MAX_INVEN; 
	int nGroupItemCount = g_srgGroupItemCount[nGroupIndex];
	if( 0 >= nGroupItemCount && eRwd_ItemGroupCount <= nGroupItemCount ) return MAX_INVEN;

	int nDice = rand() % nGroupItemCount ;
	int nItemIndex = g_srgItemGroup[nGroupIndex][nDice];
	return GiveItem( nUser, nItemIndex, nItemCount );
}

int GetEmptyInvenCount( int nUser )
{
	int nEmptyInven = 0;

	for( int i = 0 ; i < pMob[nUser].byMaxInven ; i++ )
	{
		if ( pMob[nUser].MOB.Inven[i].snIndex == 0 ) nEmptyInven++;
	}
	return nEmptyInven;
}

BOOL RemoveItem( int nUser, int nItemIndex, int nItemCount )
{
	int nSrvItemIndex = nItemIndex - HT_PARAMTYPE_ITEM_START + 1;
	int nSrvItemCount = 0;
	for ( int i = 0 ; i < MAX_INVEN ; i++ )
	{
		if ( pMob[nUser].MOB.Inven[i].snIndex == nSrvItemIndex ) nSrvItemCount += pMob[nUser].MOB.Inven[i].byCount;
	}

	if ( nSrvItemCount < nItemCount ) nItemCount=nSrvItemCount;// return FALSE;

	int nRemainItem = nItemCount;

	for ( int i = 0 ; i < MAX_INVEN && nRemainItem > 0 ; i++ )
	{
		if ( pMob[nUser].MOB.Inven[i].snIndex != nSrvItemIndex ) continue;

		if ( pMob[nUser].MOB.Inven[i].byCount > nRemainItem )
		{
			pMob[nUser].MOB.Inven[i].byCount -= nRemainItem;
			// 인벤 정보가 변경된것을 클라이언트에게 알려준다.
			S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;
			sm.byType=SET_ITEM_CREATE; sm.byPlace = ITEM_PLACE_INVEN;
			sm.byIndex=i; sm.sitem=pMob[nUser].MOB.Inven[i];
			pUser[nUser].cSock.AddMessage((char*)&sm,sizeof(sm));
			break;
		}
		else
		{
			nRemainItem -= pMob[nUser].MOB.Inven[i].byCount;
			// 아이템을 인벤에서 제거하고 클라이언트에게 알려준다.
			S_SCP_RESP_ITEM_SET sm; sm.wType=SCP_RESP_ITEM_SET;
			sm.byType=SET_ITEM_DELETE; sm.byPlace = ITEM_PLACE_INVEN;
			sm.byIndex=i; sm.sitem=pMob[nUser].MOB.Inven[i];
			pUser[nUser].cSock.AddMessage((char*)&sm,sizeof(sm));
			ZeroMemory( &pMob[nUser].MOB.Inven[i], sizeof(STRUCT_ITEM) );
		}
	}
    SaveUser(nUser,0);
	return TRUE;
}

BOOL GiveMoney( int nUser, int nMoney )
{
	if(nUser<=0 || nUser>=MAX_USER) return FALSE;

	if ( nMoney >0 ) pMob[nUser].IncGold(nMoney);
	else pMob[nUser].DecGold(-nMoney);
	MSG_Money_Move m; m.wType = _MSG_Money_Move;
	m.wPDULength = sizeof(MSG_Money_Move) - sizeof(HEADER);
	m.byFromPlace = ITEM_PLACE_QUEST; m.byToPlace = ITEM_PLACE_INVEN;
	m.dwFromMoney = 0; m.dwToMoney = pMob[nUser].MOB.nRupiah;
	pUser[nUser].cSock.AddMessage( (char*)&m, sizeof( MSG_Money_Move ) );

	sprintf( temp, "get money:%d", nMoney );
	Log( temp, pUser[nUser].AccountName, pUser[nUser].IP );
    SaveUser(nUser,0); //auto_save
	return TRUE;
}

int FindItem( int nUser, int nItemIndex, int nItemCount )
{
	int nItemPos = 0;
	int nTmpCount = 0;
	int nSrvIndex = nItemIndex - HT_PARAMTYPE_ITEM_START + 1;
	for ( int i = 0 ; i < MAX_INVEN ; i++ )
	{
		if ( pMob[nUser].MOB.Inven[i].snIndex == nSrvIndex  )
		{
			nItemPos = i;
			nTmpCount += pMob[nUser].MOB.Inven[i].byCount;
		}
	}

	return ( nTmpCount >= nItemCount ) ? nItemPos : MAX_INVEN;
}

BOOL IsPartyMember( int nUser )
{
	if ( pMob[nUser].Leader == 0 )
	{
		for ( int i = 0 ; i < MAX_PARTY ; i++ )
		{
			if ( pMob[nUser].m_irgParty[i] != 0 ) return TRUE;
		}
	}
	else return TRUE;

	return FALSE;
}

void GivePartyPrana( int nUser, int nPrana )
{
	int nLeader = pMob[nUser].Leader;
	if ( nLeader == 0 ) nLeader = nUser;

	for ( int i = 0 ; i < MAX_PARTY ; i++ )
	{
		int nPartyID = 0;
		if ( ( nPartyID = pMob[nLeader].m_irgParty[i] ) != 0 )
		{
			pMob[nPartyID].AcquirePrana( nPrana );
		}
	}
}

//	인벤내에 해당아이템을 보유하고 있을 경우 더이상 지급하지 않는다
bool Party_ClearQuestAndGiveItem( int conn, int nQuest, int nItemIndex, int nCount, bool bLevelUp )
{
	bool bRet = true;
	int nUser = 0;
	int nLevel = pMob[conn].MOB.byQuest[nQuest];
	int nLeader = pMob[conn].Leader;
	if(nLeader==0) nLeader = conn;

	for (int i=0;i<MAX_PARTY+1;i++)
	{   if (i==0) nUser = nLeader;
		else      nUser = pMob[nLeader].m_irgParty[i-1];
   	 	if	(nUser<=0||nUser>=MAX_USER) continue;
		CHECK_QUEST(nQuest)
		{
			if(QUEST_LEVEL(nQuest)==nLevel)
			{
				if(FindItem(nUser, nItemIndex, nCount)!=MAX_INVEN) continue;	//	해당아이템을 이미 가지고 있을 경우
				if(GiveItem(nUser, nItemIndex, nCount)==MAX_INVEN) 
				{	bRet = false;
					continue;		//	인벤이 가득차서 아이템 지급을 못할경우
				}
				if(bLevelUp)
				{	QUEST_LEVEL(nQuest) = nLevel + 1;
					SendQuestHistory( nUser );
				}
				continue;
			}
		}
	}	

	return bRet;
}

void RepairEquips( int nUser )
{
	int nItemIndex = 0;
	short sMaxDur;

	for ( int i=0; i<MAX_EQUIP; i++ )
	{
		S_SCP_RESP_ITEM_REPAIR sm; 
		sm.wType = SCP_RESP_ITEM_REPAIR; 
		sm.byResult=REPLY_ACK_OK; 
		sm.byPlace = ITEM_PLACE_EQUIP; 
		sm.nMoney = pMob[nUser].MOB.nRupiah;

		if ( pMob[nUser].MOB.Equip[i].snIndex==0 ) continue;
		nItemIndex = pMob[nUser].MOB.Equip[i].snIndex + HT_PARAMTYPE_ITEM_START - 1;

		if ( !g_ParamMgr.HT_bGetItemMaxDurability( nItemIndex, &sMaxDur ) ) continue;

		if ( pMob[nUser].MOB.Equip[i].snDurability!=sMaxDur )
		{	
			STRUCT_ITEM tmpItem = pMob[nUser].MOB.Equip[i];
			pMob[nUser].MOB.Equip[i].snDurability = sMaxDur;	//	수리하고
			sm.byIndex=i; sm.byDummy = 0;			//	0:유료아이템으로 수리, 1:루피아로 수리
			pUser[nUser].cSock.AddMessage( (char*)&sm, sizeof(sm) );

			char temp[1024] = {0,};
			char szFrom[256], szTo[256];
			BASE_GetItemCode( &tmpItem, szFrom );
			BASE_GetItemCode( &(pMob[nUser].MOB.Equip[i]), szTo );
			sprintf(temp, "repair Repaired by RepairEquip [from %s To %s]", szFrom, szTo);
			Log(temp, pUser[nUser].AccountName, pUser[nUser].IP);
		}
	}				
}

void RepairPartyEquips( int nUser )
{
	int nLeader = pMob[nUser].Leader;
	if ( nLeader == 0 ) nLeader = nUser;

	for ( int i = 0 ; i < MAX_PARTY ; i++ )
	{
		int nPartyID = 0;
		if ( ( nPartyID = pMob[nLeader].m_irgParty[i] ) != 0 )
		{
			RepairEquips( nPartyID );
		}
	}
}

void NotifyDialog( int nUser, short snDialog )
{
	S_SCP_QUEST_DIALOG sm; sm.wType = SCP_QUEST_DIALOG;
	sm.wIndex = snDialog;

	pUser[nUser].cSock.AddMessage( (char*)&sm, sizeof( S_SCP_QUEST_DIALOG ) );
}

BOOL IsNight()
{
	time_t tmTime = time(0) - 1000; // 초기 시간을 1000이라 가정한다.
	int nHour = (int)((tmTime % 14400) / 600);
	return ( nHour >= 18 );
}

BOOL GetProbability( int nPercent )
{
	if(nPercent<0 || nPercent>100) return FALSE;
	return g_QuestTable.GetValue(nPercent);
}

BOOL GetProbability_10000( int nRate )
{
	if ( nRate < 0 || nRate > 10000 ) return FALSE;
	return ( ( rand() % 10000 ) < nRate );
}

BOOL SummonMonster( int nUser, int nMonsterID, int nClass1, int nClan, int nX, int nY, int nLifeTime )
{
	if ( CountMonster( nMonsterID ) == 0 )
	{
		if(nX==0 && nY==0)
            pMob[1000].Summon( nMonsterID, 1, eTNPrdt_PopNormal, nClass1, eTNCls2_Basic, nClan, 2, 
				pMob[nUser].TargetX+1, pMob[nUser].TargetY+1, 0, false, nLifeTime, 0, 1856 );
		else
            pMob[1000].Summon( nMonsterID, 1, eTNPrdt_PopNormal, nClass1, eTNCls2_Basic, nClan, 2, 
				nX, nY, 0, false, nLifeTime, 0, 1857 );

		return TRUE;
	}
	return FALSE;
}