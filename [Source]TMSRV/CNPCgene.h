#include <windows.h>
#include "basedef.h"

#define NPCG_EMPTY   0
#define NPCG_CHARGED 1

struct NPCGENLIST
{
		//int  Mode;
		int  MinuteGenerate;                     // ��� �������� ����� ���ΰ�. CheckFrequency
		//int  MaxNumMob;                          // �� ���׷����͸� ���� ����ɼ� �ִ� �ִ� ��
		//int  CurrentNumMob;                      // �� ���׷����͸� ���� ����� ��.
		//int  MinGroup;                           // �ѹ��� ����� ������ �ִ��    
		//int  MaxGroup;                           // �ּ�ġ
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

		//STRUCT_MOB   Leader;                    // ���� ���� ����.
		//STRUCT_MOB   Follower;                  // �ʸ��� ���γ���

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
            int iPopCountPerTime ; // �ð��� Pop ��ü��
            int iReadyMobCount ; // ���� �غ�� ��ü��
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
	STRUCT_MOB        Mob[MAX_SUMMONLIST];                    // ���� ���� ����.
};

class CNPCGenerator 
{	public:
	NPCGENLIST pList[MAX_NPCGENERATOR];
	int NumOld[MAX_NPCGENERATOR];
	CNPCGenerator();  //��Ʈ���� ��ü�� ����Ʈ ���� ü���.
	~CNPCGenerator();
	int NumList;
	BOOL ReadNPCGenerator(void);
	BOOL ParseString(int i, char * str);
	void VerifyData();

	void RebuildAreaData() ;
};
//    ��: MaxNumMob �� 100�ε� ���� 5������ 20��Ʈ�� ����Ǿ� �ִٰ�,
//     ���ε��� 3������ �׾��� ���.
//     MinGenerate�� 3 �̸��̸� ������� ����.