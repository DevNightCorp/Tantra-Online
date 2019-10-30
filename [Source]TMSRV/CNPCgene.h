#include <windows.h>
#include "basedef.h"

#define NPCG_EMPTY   0
#define NPCG_CHARGED 1

struct NPCGENLIST
{
		//int  Mode;
		int  MinuteGenerate;                     // 몇분 간격으로 생산될 것인가. CheckFrequency
		//int  MaxNumMob;                          // 이 제네레이터를 통해 생산될수 있는 최대 맙
		//int  CurrentNumMob;                      // 이 제네레이터를 통행 생산된 맙.
		//int  MinGroup;                           // 한번에 생산될 맙들의 최대와    
		//int  MaxGroup;                           // 최소치
		int  SegmentListX[MAX_SEGMENT];
		int  SegmentListY[MAX_SEGMENT];
		int  SegmentRange[MAX_SEGMENT];
		int  SegmentWait[MAX_SEGMENT];
		//char SegmentAction[MAX_SEGMENT][80];
		//char FightAction[4][80];
		//char FleeAction[4][80];
		//char DieAction[4][80];
		int  Formation;
		int  RouteType;
		//int	 Offset;

		//STRUCT_MOB   Leader;                    // 맙의 세부 내용.
		//STRUCT_MOB   Follower;                  // 똘마니 세부내용

		int iGroup ;
        struct AREA_COMMAND
        {
            int iCommand ; // 1: eCmd_PopMonster, 2:eCmd_DropItem
            int iIndex ;
            int iCount ;            
        } ;

        AREA_COMMAND krgCommand[eCmd_MaxCount] ;

        struct MONSTER_LIST
        {
            STRUCT_MOB kMobData ;
            int iMaxPopCount ;
            int iCurPopCount ;
            int iPopCountPerTime ; // 시간당 Pop 개체수
            int iReadyMobCount ; // 현재 준비된 개체수
            short srgReadyMobList[10][2] ;
        } ;

        MONSTER_LIST krgMonsterList[eArea_MaxMobListCount] ; // or 3
};





class CNPCSummon
{
	public:
	CNPCSummon(); 
	~CNPCSummon();
	void Initialize(void);
	STRUCT_MOB        Mob[MAX_SUMMONLIST];                    // 맙의 세부 내용.
};

class CNPCGenerator 
{	public:
	NPCGENLIST pList[MAX_NPCGENERATOR];
	int NumOld[MAX_NPCGENERATOR];
	CNPCGenerator();  //스트럭쳐 전체에 디폴트 값을 체운다.
	~CNPCGenerator();
	int NumList;
	BOOL ReadNPCGenerator(void);
	BOOL ParseString(int i, char * str);
	void VerifyData();

	void RebuildAreaData() ;
};
//    주: MaxNumMob 이 100인데 현재 5마리씩 20세트가 생산되어 있다가,
//     따로따로 3마리가 죽었을 경우.
//     MinGenerate가 3 미만이면 생산되지 않음.