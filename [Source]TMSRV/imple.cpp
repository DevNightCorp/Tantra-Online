#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "GetFunc.h"
#include "SendFunc.h"
#include "CMob.h"
#include "CUser.h"
#include "CItem.h"
#include "ItemEffect.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

extern HWND                   hWndMain;
extern CUser                  pUser    [MAX_USER];
extern CMob                   pMob     [MAX_MOB];
extern CItem                  pItem    [MAX_ITEM];
extern CPSock                 BillServerSocket;
extern int g_pDropBonus[64];
extern unsigned char LocalIP1[4];
extern unsigned int         CurrentTime;
extern unsigned short       pMobGrid [MAX_GRIDX][MAX_GRIDY];
extern unsigned short       pItemGrid  [MAX_GRIDY][MAX_GRIDX];
extern unsigned char        NPCRandomProgress[10];
extern char                 BillServerAddress[32];
extern int                  ServerDown;
extern int                  BillServerPort;
extern int                  BILLING;  // 0:프리  1:빌링바인팅(초기화만)    2:빌링 각제집행   3:빌링테스트.
extern int                  DecayValue;
extern int                  CurrentWeather;
extern int                  WeekMode;
extern int                  ForceWeekMode;
extern int                  GuildDay;
extern int                  GuildHour;
extern int                  NewbieHour;
extern int                  FREEEXP;
extern int                  CHARSELBILL;
extern int					POTIONCOUNT;	
extern int					PARTYBONUS;	
extern int					GUILDBOARD;	
extern int                  DOUBLEMODE;
extern int                  DUNGEONEVENT;
extern int					DEADPOINT;
extern int					StatSapphire;
extern int                  BRItem;

// 이벤트 관련 코드 ////////////////////////////////////////////////////////
extern int evStartIndex;     // 드롭시작번호
extern int evEndIndex;       // 드롭끝번호
extern int evCurrentIndex;   // 현재 드롭된 번호
extern int evRate;           // 떨어질확률 1000이면 1/1000
extern int evItem;           // 이벤트 아이템은 코드
extern int evIndex;          // 아이템에 유닉코드가 붙는가.
extern int evOn;             // 아이템이 떨어지고 있는가 1이면 떨어지고 있음.
extern int evDelete;         // 1 이벤트 아이템 삭제중
extern int evNotice;         // 공지가 뜨는지

                          // 0 삭제안함
////////////////////////////////////////////////////////////////////////////










void Log                    ( char * String1, char * String2 ,unsigned int ip);
void StartLog               ( void );
void ReadGuild              ( void );
void SaveAll                ( void );
void CharLogOut             ( int conn );
void SetItemBonus           (STRUCT_ITEM * item,int dlevel,int sanc,int bonus);
void WriteGuild             (void);
//void DoTeleport             (int mob,int x,int y);
void DoSummon               (int target,int x, int y);

int  GetUserByName			(char *name);
void RebuildGenerator		(void);
void SummonGuild			(int Guild,int x,int y,int max,int village); // x,y지점으로 길드원을 전원 소환한다.
void DrawConfig(int isFile);
void GenerateMob(int idx,int xfix,int yfix);
int CreateMob(char * name,int xfix,int yfix,char *folder);
void CloseUser            (int conn);


void SaveAll(void)
{
	 for (int i=0;i<MAX_USER;i++)
	 {   if (pUser[i].Mode!=USER_PLAY) continue;
         CharLogOut(i);
		 Log("saveall",pUser[i].AccountName,pUser[i].IP);
	 }
	 return;

}


extern int ServerIndex;
void BuildList(void);
void ProcessImple(int conn,int level,char * str)
{
	/*
	char cmd[128];
	char sval1[128];
    char sval2[128];
	char sval3[128];
	int  ival1=0;
	int  ival2=0;
	int  ival3=0;

	sscanf(str+1,"%s %s %s %s",cmd,sval1,sval2,sval3);
	ival1=atoi(sval1);
	ival2=atoi(sval2);
	ival3=atoi(sval3);


	char logtemp[256];
	sprintf(logtemp,"adm %s",str);
	if	(conn!=0)	Log(logtemp,pUser[conn].AccountName,pUser[conn].IP);	
	else			Log(logtemp,"system",0);	

////////////////////////////////////////////////////////////////////////////////////////////////
	if (level>=8)    // 레벨5 어드민 
	{	
		if	(conn<=0 && conn>=MAX_USER) return;
		if  (!strcmp(cmd,"set"))
		{
			if  (!strcmp(sval1,"sanc"))
			{
				if (pMob[conn].MOB.Equip[0].sIndex!=0) {pMob[conn].MOB.Equip[0].stEffect[0].cEffect=EF_SANC; pMob[conn].MOB.Equip[0].stEffect[0].cValue=ival2; }
				if (pMob[conn].MOB.Equip[1].sIndex!=0) {pMob[conn].MOB.Equip[1].stEffect[0].cEffect=EF_SANC; pMob[conn].MOB.Equip[1].stEffect[0].cValue=ival2; }
				if (pMob[conn].MOB.Equip[2].sIndex!=0) {pMob[conn].MOB.Equip[2].stEffect[0].cEffect=EF_SANC; pMob[conn].MOB.Equip[2].stEffect[0].cValue=ival2; }
				if (pMob[conn].MOB.Equip[3].sIndex!=0) {pMob[conn].MOB.Equip[3].stEffect[0].cEffect=EF_SANC; pMob[conn].MOB.Equip[3].stEffect[0].cValue=ival2; }
				if (pMob[conn].MOB.Equip[4].sIndex!=0) {pMob[conn].MOB.Equip[4].stEffect[0].cEffect=EF_SANC; pMob[conn].MOB.Equip[4].stEffect[0].cValue=ival2; }
				if (pMob[conn].MOB.Equip[5].sIndex!=0) {pMob[conn].MOB.Equip[5].stEffect[0].cEffect=EF_SANC; pMob[conn].MOB.Equip[5].stEffect[0].cValue=ival2; }
				if (pMob[conn].MOB.Equip[6].sIndex!=0) {pMob[conn].MOB.Equip[6].stEffect[0].cEffect=EF_SANC; pMob[conn].MOB.Equip[6].stEffect[0].cValue=ival2; }
				if (pMob[conn].MOB.Equip[7].sIndex!=0) {pMob[conn].MOB.Equip[7].stEffect[0].cEffect=EF_SANC; pMob[conn].MOB.Equip[7].stEffect[0].cValue=ival2; }
				SendClientMessage(conn,"set sanc");
			}   else
			if	(!strcmp(sval1,"buildhtml"))
			{	BuildList();
				SendClientMessage(conn,"html built");
			}	else
			if	(!strcmp(sval1,"clearquest"))
			{	pMob[conn].MOB.Quest = 0;
				SendClientMessage(conn,"set clearquest");
			}	else
			if	(!strcmp(sval1,"clearskill"))
			{	pMob[conn].MOB.LearnedSkill = 0;
				SendClientMessage(conn,"set clearskill");
			}   else
			if  (!strcmp(sval1,"level"))
			{	if (ival2>1010) ival2=1010;
				pMob[conn].MOB.BaseScore.Level  = ival2;
				SendClientMessage(conn,"set level");
			}   else
			if  (!strcmp(sval1,"hp"))
			{	pMob[conn].MOB.BaseScore.MaxHp  = pMob[conn].MOB.BaseScore.Hp = ival2;
				pMob[conn].MOB.CurrentScore.MaxHp  = pMob[conn].MOB.CurrentScore.Hp = ival2;
				SendClientMessage(conn,"set hp");
			}   else
			if	(!strcmp(sval1,"mp"))
			{	pMob[conn].MOB.BaseScore.MaxMp  = pMob[conn].MOB.BaseScore.Mp = ival2;
				pMob[conn].MOB.CurrentScore.MaxMp  = pMob[conn].MOB.CurrentScore.Mp = ival2;
				SendClientMessage(conn,"set mp");
			}   else
			if  (!strcmp(sval1,"ac"))
			{   pMob[conn].MOB.BaseScore.Ac     = ival2;
				SendClientMessage(conn,"set ac");
			}   else
			if  (!strcmp(sval1,"dam"))
			{   pMob[conn].MOB.BaseScore.Damage = ival2;
				SendClientMessage(conn,"set dam");
			}   else
			if  (!strcmp(sval1,"exp"))
			{	pMob[conn].MOB.Exp    = ival2;
				SendClientMessage(conn,"set exp");
				SendEtc(conn);
				pMob[conn].CheckGetLevel();
			}    else
			if	(!strcmp(sval1,"str"))
			{	pMob[conn].MOB.BaseScore.Str    = ival2;
				SendClientMessage(conn,"set str");
			}   else
			if  (!strcmp(sval1,"int"))
			{   pMob[conn].MOB.BaseScore.Int    = ival2;
				SendClientMessage(conn,"set int");
			}	else
			if	(!strcmp(sval1,"dex"))
			{	pMob[conn].MOB.BaseScore.Dex    = ival2;
				SendClientMessage(conn,"set dex");
			}	else
			if  (!strcmp(sval1,"con"))
			{	pMob[conn].MOB.BaseScore.Con    = ival2;
				SendClientMessage(conn,"set con");
			}   else  
			if	(!strcmp(sval1,"coin"))
			{	pMob[conn].MOB.Coin             = ival2;
				SendClientMessage(conn,"set coin");
			}	else  
			if	(!strcmp(sval1,"merchant"))
			{	pMob[conn].MOB.Merchant         = ival2;
				SendClientMessage(conn,"set merchant");
			}   else
			if	(!strcmp(sval1,"skillbonus"))
			{	pMob[conn].MOB.SkillBonus      = ival2;
				SendClientMessage(conn,"set skillbonus");
			}   else
			if  (!strcmp(sval1,"special0"))
			{   pMob[conn].MOB.BaseScore.Special[0]      = ival2;
				SendClientMessage(conn,"set special 0");
			}   else
			if  (!strcmp(sval1,"special1"))
			{	pMob[conn].MOB.BaseScore.Special[1]      = ival2;
				SendClientMessage(conn,"set special 1");
			}   else
			if	(!strcmp(sval1,"special2"))
			{	pMob[conn].MOB.BaseScore.Special[2]      = ival2;
				SendClientMessage(conn,"set special 2");
			}   else
			if  (!strcmp(sval1,"special3"))
			{   pMob[conn].MOB.BaseScore.Special[3]      = ival2;
				SendClientMessage(conn,"set special 3");
			}   else
			if  (!strcmp(sval1,"scorebonus"))
			{	pMob[conn].MOB.ScoreBonus      = ival2;
				SendClientMessage(conn,"set scorebonus");
			}   else
			if  (!strcmp(sval1,"attackrun"))
			{	pMob[conn].MOB.BaseScore.AttackRun       = ival2;
				SendClientMessage(conn,"set AttackRun");
			}
			if	(!strcmp(sval1,"critical"))
			{   pMob[conn].MOB.Critical            = ival2;
				SendClientMessage(conn,"set Critical");
			}   else
			if	(!strcmp(sval1,"special"))
			{	pMob[conn].MOB.SpecialBonus            = ival2;
				SendClientMessage(conn,"set Special");
			}
  		    //  Resist와 Special은 일단 생략
			if  (ival1>=1 && ival1<=MAX_EQUIP)
			{	memset(&(pMob[conn].MOB.Equip[ival1-1]),0,sizeof(STRUCT_ITEM));
				pMob[conn].MOB.Equip[ival1-1].sIndex = ival2; 
				if	(ival2>=2330 && ival2<2390)
				{	pMob[conn].MOB.Equip[ival1-1].stEffect[0].sValue=2000;
					pMob[conn].MOB.Equip[ival1-1].stEffect[1].cEffect=9;
					pMob[conn].MOB.Equip[ival1-1].stEffect[1].cValue=100;
				}
				SetItemBonus(&pMob[conn].MOB.Equip[ival1-1],250,0,0); 
			}  
			pMob[conn].GetCurrentScore(conn);
			SendEquip(conn,conn);
			SendScore(conn);
			SendEtc(conn);
			for (int j=0;j<MAX_EQUIP;j++)
			{   SendItem(conn,0,j,&pMob[conn].MOB.Equip[j]);
			} 
		}	else
		if	(!strcmp(cmd,"save") && conn!=0)
		{	char temp[256]; strcpy(temp,"./npc/");
			pMob[conn].GetCurrentScore(conn);
			strcat(temp,sval1);
			int handle =  _open( temp, _O_CREAT | _O_RDWR | _O_BINARY , _S_IREAD | _S_IWRITE );
			if	(handle==-1)
			{	SendClientMessage(conn,"fail - save file");
				return;
			}
			_write(handle,(void*)&pMob[conn].MOB,sizeof(pMob[conn].MOB));
			_close(handle);
			sprintf(temp,"npc: %s saved",sval1);
			SendClientMessage(conn,temp);
		}	else
		if  (!strcmp(cmd,"read") && conn!=0)
		{	char temp[256]; strcpy(temp,"./npc/");
			strcat(temp,sval1);
			int handle =  _open( temp, _O_RDONLY | _O_BINARY, NULL);
			if (handle==-1){SendClientMessage(conn,"fail - open file");return;} 
			_read(handle,(void*)&pMob[conn].MOB,sizeof(pMob[conn].MOB));
			_close(handle);
			sprintf(temp,"npc: %s red.",sval1);
			SendClientMessage(conn,temp);
			for (int j=0;j<MAX_EQUIP;j++)
			{   SendItem(conn,0,j,&pMob[conn].MOB.Equip[j]);
			}
			strcpy(pMob[conn].MOB.MobName,sval1); 
			pMob[conn].MOB.BaseScore = pMob[conn].MOB.CurrentScore;
			pMob[conn].GetCurrentScore(conn);
			SendScore(conn);
			SendEtc(conn);
		}   else
		if	(!strcmp(sval1,"name") && conn!=0)
		{	strcpy(pMob[conn].MOB.MobName,sval2);
			SendClientMessage(conn,"set name");
		} 
	}  
	*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	if (level>=3)
	{
		if  (!strcmp(cmd,"timer"))
		{
			if	(ival1<5000) 
			{	SendClientMessage(conn,"SET TIMER can't be less than 5 sec");
				return;
			}
			SetTimer(hWndMain, TIMER_MIN, ival1,NULL); 
			SendClientMessage(conn,"SET TIMER");
		}	else
		if	(!strcmp(cmd,"saveall"))
		{	SaveAll();
			SendClientMessage(conn,"SAVEALL");
		}	else
		if	(!strcmp(cmd,"decay"))
		{	DecayValue = ival1;
			SendClientMessage(conn,"set decay");
		}	else
		if	(!strcmp(cmd,"set"))
		{	
			if  (!strcmp(sval1,"billmode"))
			{
				if	(ival2==2 || ival2==3)
				{  
					if	(BillServerSocket.Sock==NULL)
					{	SendClientMessage(conn,"not connected to billing server.+billconnect first");
						return;
					}
				}
				BILLING = ival2;
				SendClientMessage(conn,"set billing");
				DrawConfig(1);
			}	else
			if  (!strcmp(sval1,"billfree"))
			{   FREEEXP = ival2;
				SendClientMessage(conn,"SET FREE LEVEL");
				DrawConfig(1);
			}	else
			if  (!strcmp(sval1,"charselbill"))
			{   CHARSELBILL = ival2;
				SendClientMessage(conn,"SET CHARSELL BILL");
				DrawConfig(1);
			}	else
			if  (!strcmp(sval1,"potioncount"))
			{	POTIONCOUNT = ival2;
				SendClientMessage(conn,"SET POTIONCOUNT BILL");
				DrawConfig(1);
			}	else
			if  (!strcmp(sval1,"partybonus"))
			{	PARTYBONUS = ival2;
				SendClientMessage(conn,"SET PARTYBONUS");
				DrawConfig(1);
			}	else
			if  (!strcmp(sval1,"guildboard"))
			{	GUILDBOARD = ival2;
				SendClientMessage(conn,"SET PARTYBONUS");
				DrawConfig(1);
			}

		}
	}  
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (level>=2)
	{
		if	(!strcmp(cmd,"reboot"))
		{	ServerDown = 1;
		}	else
		if	(!strcmp(cmd,"delayreboot"))
		{	ServerDown = -1 * ServerIndex * (ival1*2); //  ival1 이 10이면  1섭은 -1*0*20=0  2섭은 -20,즉 10초 게임섭당 10초의 딜레이가 있다.
			if	(ServerDown>1||ServerDown<-1000) ServerDown=1;
		}	else
		if	(!strcmp(cmd,"generate"))
		{	
			if	(ival1<=0||ival1>mNPCGen.NumList)
			{	SendClientMessage(conn,"generation index wrong");
				return;
			}
			if	(conn<=0||conn>=MAX_USER) return; // ++ not support
			GenerateMob(ival1,pMob[conn].TargetX,pMob[conn].TargetY);
		}	else
		if	(!strcmp(cmd,"create"))
		{
			int ret = CreateMob(sval1,pMob[conn].TargetX,pMob[conn].TargetY,"boss");
			if	(ret== 1)	SendClientMessage(conn,"Create mob success");
			if	(ret== 0)	SendClientMessage(conn,"No monster file in boss directory");
			if	(ret==-1)	SendClientMessage(conn,"No empty mob");
			if	(ret==-2)	SendClientMessage(conn,"No empty mob grid");
		}	else
		if	(!strcmp(cmd,"log"))
		{	StartLog();
			SendClientMessage(conn,"RESTART LOG");
		}	else
		if	(!strcmp(cmd,"guildday"))
		{
	  		if	(ival1>=0&&ival1<=6)
			{	GuildDay = ival1;
				SendClientMessage(conn,"SET GUILD BATTLE DAY");
			}
		}   else
		if	(!strcmp(cmd,"guildhour"))
		{	if	(ival1>=0&&ival1<=23)
			{	GuildHour = ival1;
				SendClientMessage(conn,"SET GUILD BATTLE HOUR");
			}
		}	else
		if	(!strcmp(cmd,"newbiehour"))
		{	if	(ival1>=0&&ival1<=23)
			{	NewbieHour = ival1;
				SendClientMessage(conn,"SET NEWBIE BATTLE HOUR");
			}
		}	else
		if	(!strcmp(cmd,"weekmode"))
		{	if	(ival1>=0&&ival1<=5)
			{	ForceWeekMode = ival1;
				WeekMode = ival1-1;
				if (WeekMode==-1) WeekMode = 5;
				SendClientMessage(conn,"FORCE GUILD MODE");
				return;
			}
			ForceWeekMode=-1; 
			SendClientMessage(conn,"WEEKLY GUILD MODE");
		}	else
		if	(!strcmp(cmd,"reloadnpc"))
		{	mNPCGen.ReadNPCGenerator();
			SendClientMessage(conn,"RELOADNPC");
		}   else
		if  (!strcmp(cmd,"reloadguild"))
		{	ReadGuild();
			SendClientMessage(conn,"RELOADGUILD");
		}	else
		if  (!strcmp(cmd,"readguildname"))
		{   BASE_InitializeGuildName();
			SendClientMessage(conn,"READ GUILD NAME");
		}   else
		if	(!strcmp(cmd,"trtarget"))
		{	
			if	(ival1<1||ival1>8)	{SendClientMessage(conn,"err: +treasure (1-8) (1-5) (item)");return;}
			if	(ival2<1||ival2>5)	{SendClientMessage(conn,"err: +treasure (1-8) (1-5) (item)");return;}
			int idx = ival1-1;
			int tgt = ival2-1;
			int iv1=0;	int iv2=0;	int iv3=0;	int iv4=0;	int iv5=0;
			sscanf(str+1,"%s %s %s %d %d %d %d %d",cmd,sval1,sval2,&iv1,&iv2,&iv3,&iv4,&iv5);
			g_pTreasure[idx].Target[tgt].sIndex = iv1;
			g_pTreasure[idx].Target[tgt].stEffect[0].cEffect = iv2;
			g_pTreasure[idx].Target[tgt].stEffect[0].cValue  = iv3;
			g_pTreasure[idx].Target[tgt].stEffect[1].cEffect = iv4;
			g_pTreasure[idx].Target[tgt].stEffect[1].cValue  = iv5;
			g_pTreasure[idx].Target[tgt].stEffect[2].cEffect = 0;
			g_pTreasure[idx].Target[tgt].stEffect[2].cValue  = 0;
			DrawConfig(1);
			SendClientMessage(conn,"+troktarget success");
		}	else
		if	(!strcmp(cmd,"trsource"))
		{	
			if	(ival1<1||ival1>8)	{SendClientMessage(conn,"err: +source (1-8) (item)");return;}
			int idx = ival1-1;
			g_pTreasure[idx].Source = ival2;
			DrawConfig(1);
			SendClientMessage(conn,"+trsource success");
		}	else
		if	(!strcmp(cmd,"trrate"))
		{	
			if	(ival1<1||ival1>8)	{SendClientMessage(conn,"err: +trrate (1-8) (item)");return;}
			if	(ival2<1||ival2>5)	{SendClientMessage(conn,"err: +trrate (1-8) (1-5) (item)");return;}
			int idx = ival1-1;
			int tgt = ival2-1;

			g_pTreasure[idx].Rate[tgt] = ival3;
			DrawConfig(1);
			SendClientMessage(conn,"+trrate success");
		}	else
		if	(!strcmp(cmd,"statsapphire"))
		{	if	(ival1<0) {SendClientMessage(conn,"err: +statsapphire (0-64)");return;}
			StatSapphire = ival1;
			SendClientMessage(conn,"CHANGE STAT SAPPHIRE");
			DrawConfig(TRUE);
		}	else
		if	(!strcmp(cmd,"battleroyal"))
		{	if	(ival1<0) {SendClientMessage(conn,"err: +battleroyal (1-max_itemlist)");return;}
			BRItem = ival1;
			SendClientMessage(conn,"CHANGE BATTLE ROYAL REWARD");
			DrawConfig(TRUE);
		}	else

		if  (!strcmp(cmd,"set"))
		{	
			if	(!strcmp(sval1,"evstart"))
			{	evStartIndex = evCurrentIndex = ival2;
				char temp[256];sprintf(temp,"item:%d index:%d-%d(%d) rate:1/%d [I:%d D:%d O:%d N:%d]",evItem,evStartIndex,evEndIndex,evCurrentIndex,evRate,evIndex,evDelete,evOn,evNotice);
				SendClientMessage(conn,temp);
				DrawConfig(TRUE);
			}   else
			if	(!strcmp(sval1,"evend"))
			{	evEndIndex = ival2;
				char temp[256];sprintf(temp,"item:%d index:%d-%d(%d) rate:1/%d [I:%d D:%d O:%d N:%d]",evItem,evStartIndex,evEndIndex,evCurrentIndex,evRate,evIndex,evDelete,evOn,evNotice);
				SendClientMessage(conn,temp);
				DrawConfig(TRUE);
			}	else
			if	(!strcmp(sval1,"evitem"))
			{	evItem = ival2;
				char temp[256];sprintf(temp,"item:%d index:%d-%d(%d) rate:1/%d [I:%d D:%d O:%d N:%d]",evItem,evStartIndex,evEndIndex,evCurrentIndex,evRate,evIndex,evDelete,evOn,evNotice);
				SendClientMessage(conn,temp);
				DrawConfig(TRUE);
			}	else
			if	(!strcmp(sval1,"evrate"))
			{	evRate = ival2;
 				char temp[256];sprintf(temp,"item:%d index:%d-%d(%d) rate:1/%d [I:%d D:%d O:%d N:%d]",evItem,evStartIndex,evEndIndex,evCurrentIndex,evRate,evIndex,evDelete,evOn,evNotice);
				SendClientMessage(conn,temp);
				DrawConfig(TRUE);
			}   else
			if	(!strcmp(sval1,"evindex"))
			{	evIndex = ival2;
				char temp[256];sprintf(temp,"item:%d index:%d-%d(%d) rate:1/%d [I:%d D:%d O:%d N:%d]",evItem,evStartIndex,evEndIndex,evCurrentIndex,evRate,evIndex,evDelete,evOn,evNotice);
				SendClientMessage(conn,temp);
				DrawConfig(TRUE);
			}	else
			if	(!strcmp(sval1,"evdelete"))
			{	evDelete = ival2;
				char temp[256];sprintf(temp,"item:%d index:%d-%d(%d) rate:1/%d [I:%d D:%d O:%d N:%d]",evItem,evStartIndex,evEndIndex,evCurrentIndex,evRate,evIndex,evDelete,evOn,evNotice);
				SendClientMessage(conn,temp);
				DrawConfig(TRUE);
			}   else
			if	(!strcmp(sval1,"evon"))
			{	
				if	(ival2&& (evStartIndex==0||evEndIndex==0||evRate==0||evItem==0) )
				{	char temp[256];sprintf(temp,"item:%d index:%d-%d(%d) rate:1/%d [I:%d D:%d O:%d N:%d]",evItem,evStartIndex,evEndIndex,evCurrentIndex,evRate,evIndex,evDelete,evOn,evNotice);
					SendClientMessage(conn,temp);
					return;
				} 
				evOn = ival2;
				char temp[256];sprintf(temp,"item:%d index:%d-%d(%d) rate:1/%d [I:%d D:%d O:%d N:%d]",evItem,evStartIndex,evEndIndex,evCurrentIndex,evRate,evIndex,evDelete,evOn,evNotice);
				SendClientMessage(conn,temp);
				DrawConfig(TRUE);
			}   else
			if	(!strcmp(sval1,"evnotice"))
			{	evNotice = ival2;
 				char temp[256];sprintf(temp,"item:%d index:%d-%d(%d) rate:1/%d [I:%d D:%d O:%d N:%d]",evItem,evStartIndex,evEndIndex,evCurrentIndex,evRate,evIndex,evDelete,evOn,evNotice);
				SendClientMessage(conn,temp);
				DrawConfig(TRUE);
			}   else

			if	(!strcmp(sval1,"double"))
			{	DOUBLEMODE = ival2;
				SendClientMessage(conn,"SET DOUBLEMODE");
				DrawConfig(TRUE);
			}	else 
			if	(!strcmp(sval1,"deadpoint"))
			{	DEADPOINT = ival2;
				if (DEADPOINT)	SendClientMessage(conn,"SET DEADPOINT 1");
				else			SendClientMessage(conn,"SET DEADPOINT 0");
				DrawConfig(TRUE);
			}	else 
			if	(!strcmp(sval1,"dungeonevent"))
			{	DUNGEONEVENT = ival2;
				if	(DUNGEONEVENT)	SendClientMessage(conn,"SET DUNGEON EVENT ON");
				else					SendClientMessage(conn,"SET DUNGEON EVENT OFF");
				DrawConfig(TRUE);
			}	else 
			if  (!strcmp(sval1,"champ"))
			{	if	(conn<=0 && conn>=MAX_USER) return;
				if	(ival2>=0 && ival2<MAX_GUILDZONE)
				{	g_pGuildZone[ival2].ChargeGuild= ival3;
					char temp[256];
					sprintf(temp,"Set Champion Guild - Zone:%d Guild %d",ival2,ival3);
					SendClientMessage(conn,temp);
					WriteGuild();
				}
			}	else
			if	(!strcmp(sval1,"chall"))
			{	if	(conn<=0 && conn>=MAX_USER) return;
				if	(ival2>=0 && ival2<MAX_GUILDZONE)
				{	g_pGuildZone[ival2].ChallangeGuild= ival3;
					char temp[256]; sprintf(temp,"Set Challanger Guild - Zone:%d Guild %d",ival2,ival3);
					SendClientMessage(conn,temp);
					WriteGuild();
				}
			}   else
			if	(!strcmp(sval1,"drop"))
			{
				if	(ival3<50||ival3>300)
				{	SendClientMessage(conn,"Wrong Drop Bonus Rate");
					return;
				}
				if (ival2==16)
				{	for (int i=0;i<64;i++)
					{	int idx = i;
						g_pDropBonus[idx] = ival3;
					}
				}	else
				if	(ival2>=1 && ival2<=7)
				{	for (int i=0;i<8;i++)
					{	int idx = (ival2-1)*8+i;
						g_pDropBonus[idx] = ival3;
					}
				}	else
				if	(ival2>=8 && ival2<=15)
				{	int idx = 56+(ival2-8);
					g_pDropBonus[idx] = ival3;
				}	else
				{	SendClientMessage(conn,"Wrong Drop Position");
					return;
				}
				SendClientMessage(conn,"SET DROP BONUS");
				DrawConfig(TRUE);
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if	(level>=1)
	{
		if	(!strcmp(cmd,"weather"))
		{	CurrentWeather = ival2;
			SendWeather();
		}	else
		if	(!strcmp(cmd,"billconnect"))
		{  
			if (BillServerSocket.Sock!=NULL) {SendClientMessage(conn,"already connected"); return;	}
			FILE * fp = fopen("biserver.txt","rt");if (fp==NULL){SendClientMessage(conn,"no biserver.txt"); return;	}
			fscanf(fp,"%s %d",BillServerAddress,&BillServerPort);fclose(fp);
			int * pip = (int*)LocalIP1;
			if(g_eCountryID == eCountryIndonesia) pip = (int*)LocalIP2;			//	인도네시아는 빌링을 인라인사용한다
			int	ret =	BillServerSocket.ConnectBillServer(BillServerAddress,BillServerPort ,*pip,WSA_READBILL);
			if	(ret==NULL)
			{	SendClientMessage(conn,"set connect fails");
				return;
			}
			BILLING = 3;
			SendClientMessage(conn,"set connect billing");
			DrawConfig(1);
		}
	}	
	if	(level>=0) ////////////////// 0이하면 여기 들어오지를 않는다.//////////////////////////////////////////////////////////////
	{
		if  (!strcmp(cmd,"notice"))
		{	char temp[256];
			memcpy(temp,str+7,MESSAGE_LENGTH);
			SendNotice(temp);
			return;
		}	else
		if  (!strcmp(cmd,"chiefnotice"))
		{	char temp[256];
			memcpy(temp,str+12,MESSAGE_LENGTH);
			SendNoticeChief(temp);
			SendClientMessage(conn,"CHIEFNOTICE");
			return;
		}	else
		if	(!strcmp(cmd,"chiefsummon") && conn>0 && conn<MAX_USER)
		{	SendSummonChief();
			SendClientMessage(conn,"CHIEFSUMMON");
		}	else
		if	(!strcmp(cmd,"rebuild"))
		{	RebuildGenerator();
			SendClientMessage(conn,"REBUILDGENERATOR");
		}	else
		if  (!strcmp(cmd,"snoop"))
		{ 	if	(conn<=0 && conn>=MAX_USER) return;
			if	(pMob[conn].MOB.Merchant&MSV_SNOOP)
			{	pMob[conn].MOB.Merchant = pMob[conn].MOB.Merchant & 0xFE; // Snoop 제거
				SendClientMessage(conn,"SNOOP OFF");
			}	else
			{	pMob[conn].MOB.Merchant = pMob[conn].MOB.Merchant | MSV_SNOOP; // Snoop 제거
				SendClientMessage(conn,"SNOOP ON");
			}
			pMob[conn].GetCurrentScore(conn);
			SendScore(conn);
			return;
		}   else
		if  (!strcmp(cmd,"event"))
		{   char temp[256];sprintf(temp,"item:%d index:%d-%d(%d) rate:1/%d [I:%d D:%d O:%d] %d",evItem,evStartIndex,evEndIndex,evCurrentIndex,evRate,evIndex,evDelete,evOn, DOUBLEMODE);
		    SendClientMessage(conn,temp);
		}   else
		if  (!strcmp(cmd,"teleport"))
		{   if (ival1<100) ival1 = ival1 * 128 + 64;
			if (ival2<100) ival2 = ival2 * 128 + 64;
			if (ival1>=0 && ival1<MAX_GRIDX&&ival2>=0 && ival2<MAX_GRIDY)
		    {	DoTeleport(conn,ival1,ival2);
		    }
		}   else
		if  (!strcmp(cmd,"kick"))
		{	if	(sval1[0]==0) return;
			sval1[MOBNAME_LENGTH-1]=0;
			sval1[MOBNAME_LENGTH-2]=0;
			int tid = GetUserByName(sval1);
			if	(tid==0) {SendClientMessage(conn,"Can't find user.");return;}
			if	(pUser[tid].Mode!=USER_PLAY) return;
			if	(pMob[tid].MOB.CurrentScore.Level>=pMob[conn].MOB.CurrentScore.Level)
			{	SendClientMessage(conn,"Can't kick equal or high level admin");
				return;
			}
			//CharLogOut(tid);
			CloseUser(tid);
		}	else
		if	(!strcmp(cmd,"gsummon"))
		{	if	(conn<=0 && conn>=MAX_USER) return;
			SummonGuild( ival1   , pMob[conn].TargetX,pMob[conn].TargetY , 48, -1);// 48명까지만 소환이 된다
		}	else
		if	(!strcmp(cmd,"config"))
		{	
			FILE * fp = NULL;
			fp = fopen("gameconfig.txt","rt");
			if	(fp==NULL) 
			{	SendClientMessage(conn,"can't find gameconfig.txt");
				return;
			}
			char logtemp[256];
			for (int i=0;i<28;i++)
			{	char * ret = fgets(logtemp,255,fp);
				if (ret==NULL){fclose(fp);return;}
				SendClientMessage(conn,logtemp);
			}
			fclose(fp);
			
		}
	}
	*/
	return;
}