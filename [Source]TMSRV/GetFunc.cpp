#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Basedef.h"
#include "GetFunc.h"
#include "CMob.h"
#include "CItem.h"
#include "ItemEffect.h"
#include "CUser.h"
#include "CGuild.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

extern CUser pUser[];


extern CMob                          pMob     [MAX_MOB];
extern CItem                         pItem    [MAX_ITEM];
extern TNCELL              g_krgCell[MAX_GRIDY][MAX_GRIDX] ;
extern unsigned int                  CurrentTime;
extern unsigned short                pMobGrid [MAX_GRIDX][MAX_GRIDY];
extern unsigned short                pItemGrid  [MAX_GRIDY][MAX_GRIDX];
extern unsigned char                 NPCRandomProgress[10];
extern void Log                  ( char * String1, char * String2,unsigned int ip );
extern STRUCT_ITEMLIST   g_pItemList[MAX_ITEMLIST];
extern CGuild						pGuild[MAX_USER];
extern int							g_iViewGridX ;
extern int							g_iViewGridY ;
extern int							g_iHalfGridX ;
extern int							g_iHalfGridY ;
extern DWORD						g_dwUserConnect;
extern _S_TRIMURITY_AREA			TrimurityArea;
extern short						g_pDetectEnemyRadius[eRds_MaxDetectEnemy+1] ;
extern char							g_pDetectEnemyTable[ePos_MaxPosCount][2] ;
extern HS2D_COORD					g_stPosStronghold[eStronghold_MaxCount];
extern g_irgSetting[MAX_SETTING];

int GetMatchCombine(STRUCT_ITEM *item)
{
	/*
	int target	= item[0].sIndex;if	(target<=0	||	target>=MAX_ITEMLIST)	return 0;
	int	stone	= item[1].sIndex;if	(stone<=0	||	stone>=MAX_ITEMLIST)	return 0;
	if	(g_pItemList[target].nUnique<41 ||g_pItemList[target].nUnique>49 )	return 0;
	if	(g_pItemList[target].nExtra<=0 )	return 0;

	int rate = 1;
	for	(int j=2;j<MAX_COMBINE;j++)
	{	int idx = item[j].sIndex;if	(idx<=0||idx>=MAX_ITEMLIST) continue;
		int eq = BASE_GetItemAbility(&item[j],EF_POS);
		if	(eq==0) return 0;// 재료에 장착불가한것이 들어있다
		int	sa = BASE_GetItemSanc(&item[j]);
		if	(sa==7)	{rate=rate+2;continue;}
		if	(sa==8)	{rate=rate+4;continue;}
		if	(sa==9)	{rate=rate+10;continue;}
		return 0;
	}
	return rate;
	*/
	return 0;
}
int GetUserInArea(int x1,int y1,int x2,int y2,char *first)	// rece내의 유저 명수를 구한다
{/*

	int	num=0;
    for (int i=0;i<MAX_USER;i++)
	{
		if (pUser[i].Mode!=USER_PLAY) continue;
		if (pMob[i].Mode == MOB_EMPTY) continue;
		if (pMob[i].TargetX < x1 || pMob[i].TargetX > x2 || pMob[i].TargetY < y1 || pMob[i].TargetY > y2 ) continue;
		strcpy(first,pMob[i].MOB.MobName);
		num++;
	}
	return num;
	*/
	return 0;
}


int GetParryRate(STRUCT_MOB * mob,int add)
{
	/*
	if	(add>100)	add=100;
	if	(add<0)	add=0;
	int	parryrate1 = mob->CurrentScore.Dex;		if (parryrate1>200) parryrate1=200;
	int parryrate2 = mob->CurrentScore.Dex-200;	if (parryrate2<0)	parryrate2=0;	if (parryrate2>300)	parryrate2=300;
	int parryrate = parryrate1 + parryrate2/2 + add;
	
	if	(mob->Rsv&RSV_PARRY) parryrate+=100;
	if	(mob->Rsv&RSV_HASTE) parryrate+=50;
	if	(mob->Rsv&RSV_BLOCK) parryrate+=50;
	return parryrate;
	*/
	return 0;
}

int GetEmptyAffect(int mob,int type)
{
/*
	for (int i=0;i<MAX_AFFECT;i++)  if (pMob[mob].Affect[i].Type == type ) return i;
	for (    i=0;i<MAX_AFFECT;i++)  if (pMob[mob].Affect[i].Type == 0  ) return i;
*/
	return -1; // ReturnValue = -1; 
}
BOOL GetHide(int mob)
{
/*
	 if (mob<=0||mob>=MAX_USER) return FALSE;
     if (pMob[mob].Affect[0].Type==28||pMob[mob].Affect[1].Type==28||pMob[mob].Affect[2].Type==28||pMob[mob].Affect[3].Type==28) return TRUE;
*/
     return FALSE;
}
BOOL GetInView(int a,int b)
{	if	(pMob[a].TargetX < pMob[b].TargetX-g_iViewGridX  ||  pMob[a].TargetX > pMob[b].TargetX+g_iViewGridX  || 
		pMob[a].TargetY < pMob[b].TargetY-g_iViewGridY  ||  pMob[a].TargetY > pMob[b].TargetY+g_iViewGridY)	return FALSE;
	return TRUE;
}
BOOL GetInHalf(int a,int b)
{	if	(pMob[a].TargetX < pMob[b].TargetX-g_iHalfGridX  ||  pMob[a].TargetX > pMob[b].TargetX+g_iHalfGridX  || 
		pMob[a].TargetY < pMob[b].TargetY-g_iHalfGridY  ||  pMob[a].TargetY > pMob[b].TargetY+g_iHalfGridY)	return FALSE;
	return TRUE;
}
void GetTeleportPosition(int * x, int * y)
{
	int xv=(*x)&0xFFFC;
	int yv=(*y)&0xFFFC;
	
	if	(xv==2116 && yv==2100)	{*x = 2480+rand()%4;	*y = 1716+rand()%4;	}	else // 아르미아-아즈란
	if	(xv==2480 && yv==1716)	{*x = 2116+rand()%4;	*y = 2100+rand()%4;	}	else
	if	(xv==2140 && yv==2068)	{*x = 2588+rand()%4;	*y = 2096+rand()%4;	}	// 아르미아필드
	if	(xv==2468 && yv==1716)	{*x = 2248+rand()%4;	*y = 1556+rand()%4;	} // 아즈란필드	
	if	(xv==2364 && yv==2284)	{*x =  144+rand()%4;	*y = 3788+rand()%4;	}	else // 1층입구1
	if	(xv== 144 && yv==3788)	{*x = 2364+rand()%4;	*y = 2284+rand()%4;	}	else
	if	(xv==2668 && yv==2156)	{*x =  144+rand()%4;	*y = 3772+rand()%4;	}	else // 1층입구2	
	if	(xv== 144 && yv==3772)	{*x = 2668+rand()%4;	*y = 2156+rand()%4;	}   else

	if	(xv== 148 && yv==3780)	{*x = 1004+rand()%4;	*y = 4028+rand()%4;	}   else // 1층 중앙	
	if	(xv== 144 && yv==3780)	{*x = 1004+rand()%4;	*y = 4028+rand()%4;	}   else // 1층 중앙	
	if	(xv==1004 && yv==4028)	{*x =  148+rand()%4;	*y = 3780+rand()%4;	}   else

	if	(xv== 408 && yv==4072)	{*x = 1004+rand()%4;	*y = 4064+rand()%4;	}   else // 2층입구1
	if	(xv==1004 && yv==4064)	{*x =  408+rand()%4;	*y = 4072+rand()%4;	}   else
	if	(xv== 744 && yv==3820)	{*x = 1004+rand()%4;	*y = 3992+rand()%4;	}   else // 2층입구2
	if	(xv==1004 && yv==3992)	{*x =  744+rand()%4;	*y = 3820+rand()%4;	}   else
	if	(xv== 680 && yv==4076)	{*x =  916+rand()%4;	*y = 3820+rand()%4;	}   else // 3층입구1
	if	(xv== 916 && yv==3820)	{*x =  680+rand()%4;	*y = 4076+rand()%4;	}   else
	if	(xv== 876 && yv==3872)	{*x =  932+rand()%4;	*y = 3820+rand()%4;	}   else // 3층입구2
	if	(xv== 932 && yv==3820)	{*x =  876+rand()%4;	*y = 3872+rand()%4;	}   else

	if	(xv== 188 && yv== 188)	{*x =  2548+rand()%4;	*y = 1740+rand()%4;	}   else // 콜로세움관전장
	if	(xv==2548 && yv==1740)	{*x =  188+rand()%4;	*y = 188+rand()%4;	}   else 

	if	(xv==1824 && yv==1772)	{*x = 1172+rand()%4;	*y = 4080+rand()%4;	}   else // 아즈란필드 - 지저 1층
	if	(xv==1172 && yv==4080)	{*x = 1824+rand()%4;	*y = 1772+rand()%4;	}   else	

	if	(xv==1516 && yv==3996)	{*x = 1304+rand()%4;	*y = 3816+rand()%4;	}   else // 지저1층 - 지저 2층
	if	(xv==1304 && yv==3816)	{*x = 1516+rand()%4;	*y = 3996+rand()%4;	}   else	
	if	(xv==2452 && yv==1716)	{*x = 1968+rand()%4;	*y = 1708+rand()%4;	}		 // 아즈란- 왕국입구	

	if	(xv==2452 && yv==1988)	{*x = 1964+rand()%4;	*y = 1592+rand()%4;	}	 // 스테이블 - 아즈란



}

int	GetExpApply(int exp, int attacker, int target)
{
	if	(attacker>=MAX_LEVEL || target>=MAX_LEVEL || attacker<0 || target<0)	return exp;
	//if	(target>=210)	target=target+42;
	attacker++;
	target++;
    int	multiexp = target*100/attacker;		//  0-100 // 100-200
	if	(multiexp<80 && attacker>=50)	multiexp = ((multiexp-80)*2)+60; else 
	if  (multiexp>200)					multiexp = 200;
	if	(multiexp<0)					multiexp=0;
	exp=exp*multiexp / 100;
	return exp ;
}

extern int BrState;
int  GetCreateMob(int mob,S_SCP_INIT_OTHER_MOB * sm)
{
	sm->wType = SCP_INIT_OTHER_MOB;
	sm->wPDULength = sizeof(S_SCP_INIT_OTHER_MOB) - sizeof(HEADER);
	sm->nID = mob;      
	strncpy(sm->szName,pMob[mob].MOB.szName,SZNAME_LENGTH);
	sm->nGuildID = pMob[mob].MOB.nGuildID;
	sm->byMember = 0;
	sm->byFace = pMob[mob].MOB.byFace; 
	sm->byHead = pMob[mob].MOB.byHead;
	sm->byTrimuriti = pMob[mob].MOB.byTrimuriti;
	sm->snTribe = pMob[mob].MOB.snTribe;      
	sm->byCastClass = 0;
	sm->byCastGrade = 0;
	sm->bySpecialName = 0;
	sm->dwStatus = 0; 
	sm->byGMStatus = 0; 
	//sm->nMaxHP = pMob[mob].MOB.snChakra[CHAKRA_PART_HEART] * 2;
	sm->nMaxHP = pMob[mob].get_MaxHP() ;
	sm->nCurHP = pMob[mob].MOB.nHP;
	sm->byType = 0;
	sm->byDir = pMob[mob].m_iDirection ; 
	sm->snTargetX = pMob[mob].TargetX;    
	sm->snTargetZ = pMob[mob].TargetY;
	sm->dwActionSkill = 0;//(DWORD)pMob[mob].m_uiMonsterID ;
	sm->byActionLevel = 0;
	sm->byLevel = pMob[mob].MOB.byLevel;
	sm->iAffections = pMob[mob].m_iAffections ;
	sm->snKarma = pMob[mob].MOB.snKarma;
	sm->byGMStatus = pMob[mob].MOB.byGMStatus;
	sm->byClass1 = pMob[mob].MOB.byClass1;
	sm->byClass2 = pMob[mob].MOB.byClass2;
	sm->byClan = pMob[mob].m_byClan ;
	sm->byTradeMode = 0 ; 
	sm->byPopType = eTNPrdt_PopNormal ;
	memset( sm->szTrade, 0, SZTRADE_LENGTH ) ;

	if(mob>0 && mob<MAX_USER)
	{
		sm->dwEvent = pUser[mob].m_dwEvent;
		if(pUser[mob].byTradeMode == 1)
		{
			time_t now; time(&now);
			if(now>(int)pUser[mob].m_time[eTime_Store] || pUser[mob].m_snTimeMode&0x4000)
				sm->byTradeMode = 1;
			else
				sm->byTradeMode = 2;
		}
		else
            sm->byTradeMode = pUser[mob].byTradeMode;

		strncpy(sm->szTrade, pUser[mob].szTrade, SZTRADE_LENGTH);
		strncpy(sm->szAccount,pUser[mob].AccountName,ACCOUNTNAME_LENGTH);

		int nIndex = pUser[mob].nGuildIndex;
		if(nIndex>0 && nIndex<MAX_USER)
		{	sm->dwGuildMark = pGuild[nIndex].GUILD.Mark;
			strncpy(sm->szGuild, pGuild[nIndex].GUILD.GuildName, GUILDNAME_LENGTH);
		}	else
		{	sm->dwGuildMark = 0 ;
			strcpy(sm->szGuild,"");
		}
	}

	if(mob<=MAX_USER) 
	{	memcpy(sm->Equip, pMob[mob].ViewEquip, sizeof(STRUCT_ITEMVIEW)*VISUAL_EQUIP);
	}
	else
	{	ZeroMemory(&sm->Equip, VISUAL_EQUIP*sizeof(STRUCT_ITEMVIEW));
	}

	sm->byCaste = pMob[mob].m_iCaste;
	
/*	//sprintf(sm->MobName,"%d",mob);
	sm->PosX = pMob[mob].TargetX;
	sm->PosY = pMob[mob].TargetY;
	sm->Size = sizeof(MSG_CreateMob);
	sm->ID   = ESCENE_FIELD;
	sm->MobID= mob;
	sm->Tick = CurrentTime;
	sm->Score= pMob[mob].MOB.CurrentScore;
	sm->Guild= pMob[mob].MOB.Guild;
	if	(pMob[mob].GuildDisable==1) {sm->Guild=0;}
	if	(mob>=MAX_USER)
	{	if	(pMob[mob].MOB.Clan==4)	sm->Score.Ac=0;
		else						sm->Score.Ac=1;
	}


	sm->CreateType = 0;
	if (pMob[mob].MOB.GuildLevel==2) sm->CreateType = sm->CreateType | 0x8000;
	if (pMob[mob].MOB.GuildLevel==1) sm->CreateType = sm->CreateType | 0x4000;
	int selfdead=0;
	for (int i=0;i<MAX_EQUIP;i++)
	{	sm->Equip[i] = pMob[mob].MOB.Equip[i].sIndex;
		//if	(i==12 && pMob[mob].GuildDisable==0) {sm->Equip[i]=0;continue;}
		if	(i==14 && sm->Equip[i]>=2360 && sm->Equip[i]<2390 && pMob[mob].MOB.Equip[i].stEffect[0].sValue<=0)
		{	sm->Equip[i]=0;
			selfdead=1;
			continue;
		}	
		if	(i==14 && sm->Equip[i]>=2360&&sm->Equip[i]<2390 )
		{	
			int sanc = pMob[mob].MOB.Equip[i].stEffect[1].cEffect;
			sanc=sanc/10;	if	(sanc>9) sanc=9;	if	(sanc<0) sanc=0;
			sanc=sanc<<12;
			sm->Equip[i]=sm->Equip[i]+sanc;
			continue;
		}	
		int sanc = BASE_GetItemSanc(&pMob[mob].MOB.Equip[i]);
		sanc=sanc<<12;
		sm->Equip[i]=sm->Equip[i]+sanc;
	}
	GetAffect(sm->Affect,pMob[mob].Affect);

	if	(BrState!=0 )
	{	int xx = pMob[mob].TargetX;
		int yy = pMob[mob].TargetY;
		if	(xx>=2604 && yy>=1708 && xx<=2648 && yy<=1744)
		{	memset(sm->MobName,0,MOBNAME_LENGTH);
			strcpy(sm->MobName,"??????");
			sm->Equip[15]=0;
			sm->CreateType=sm->CreateType&0x7FFF;
			sm->Guild=0;
		}
	}
	return selfdead;
	*/
	return TRUE;
}
int GetCreateMobTrade(int mob,MSG_CreateMobTrade * sm)
{
	/*
	sm->Type = _MSG_CreateMobTrade;
    strcpy(sm->MobName,pMob[mob].MOB.MobName);
	if	(mob<MAX_USER)
	{	int ck = GetCurKill(mob);
		int tk = GetTotKill(mob);
		unsigned char cv= ck;
		unsigned char cv1=tk%256;
		unsigned char cv2=tk/256;
		sm->MobName[13]=cv;
		sm->MobName[14]=cv1;
		sm->MobName[15]=cv2;
		int chaos = GetPKPoint(mob);
		cv = chaos;
		sm->MobName[12] = cv;

	}

	//sprintf(sm->MobName,"%d",mob);
	sm->PosX = pMob[mob].TargetX;
	sm->PosY = pMob[mob].TargetY;
	sm->Size = sizeof(MSG_CreateMobTrade);
	sm->ID   = ESCENE_FIELD;
	sm->MobID= mob;
	sm->Tick = CurrentTime;
	sm->Score = pMob[mob].MOB.CurrentScore;
	sm->Guild = pMob[mob].MOB.Guild;
	if	(pMob[mob].GuildDisable==1) {sm->Guild=0;}
	if	(mob>=MAX_USER)
	{	if	(pMob[mob].MOB.Clan==4)	sm->Score.Ac=0;
		else						sm->Score.Ac=1;
	}
	sm->CreateType = 0;
	if (pMob[mob].MOB.GuildLevel==2) sm->CreateType = sm->CreateType | 0x8000;
	if (pMob[mob].MOB.GuildLevel==1) sm->CreateType = sm->CreateType | 0x4000;

	int selfdead=0;
	for (int i=0;i<MAX_EQUIP;i++)
	{	sm->Equip[i] = pMob[mob].MOB.Equip[i].sIndex;
		//if	(i==12 && pMob[mob].GuildDisable==1) {sm->Equip[i]=0;continue;}
		if	(i==14 && sm->Equip[i]>=2360&&sm->Equip[i]<2390 && pMob[mob].MOB.Equip[i].stEffect[0].sValue<=0)
		{	sm->Equip[i]=0;
			selfdead=1;
			continue;
		}	
		int sanc = BASE_GetItemSanc(&pMob[mob].MOB.Equip[i]);
		sanc=sanc<<12;
		sm->Equip[i]=sm->Equip[i]+sanc;
	}
	strcpy(sm->Desc,pUser[mob].Desc);
	GetAffect(sm->Affect,pMob[mob].Affect);
	return selfdead;
	*/
	return 0;
}


void  GetAffect(unsigned short *out, STRUCT_AFFECT * affect)
{
	/*
	for (int i=0;i<MAX_AFFECT;i++)
	{   
		int type  = affect[i].Type;
		int value = affect[i].Time;
		value = value;
		if (value>255) value = 255;              // 시간을 0-7로 표시해서는 안된다. 7*4=28 이라 28초이상 표시 불가.
		unsigned short tout = (type<<8) + (value&0xFF);  //12 :1
		out[i]=tout;
	}
	*/
}


void  GetCreateItem(int idx,S_SCP_MAP_ITEM_APPEAR* sm)
{
	sm->wType = SCP_MAP_ITEM_APPEAR;
	sm->wPDULength = sizeof(S_SCP_MAP_ITEM_APPEAR) - sizeof(HEADER);
	sm->dwIndex = pItem[idx].ITEM.snIndex;
	sm->nItemID = idx;
	sm->snX = pItem[idx].PosX;
	sm->snZ = pItem[idx].PosY;
}


void GetAction(int mob,int targetx,int targety,MSG_Action*sm)
{
    //sm->ID		= mob;
	//sm->Tick		= CurrentTime;
	//sm->Size		= sizeof(MSG_Action);
	sm->dwKeyID		= mob;
	sm->wType		= _MSG_Action;
	sm->wPDULength	= sizeof(MSG_Action) - sizeof(HEADER);	
	
	sm->TargetX		= targetx;
	sm->TargetY		= targety; 
	sm->Direction	= pMob[mob].m_iDirection;
	sm->Effect		= 3;//pMob[mob].State;
	//sm->Route[0]	= 0; // GetRoute
	sm->Speed		= pMob[mob].m_iMoveSpeed;
	sm->PosX		= pMob[mob].TargetX;
	sm->PosY		= pMob[mob].TargetY;
}
unsigned char  GetAttribute(int x,int y)
{
	  //if (x<0 || x>MAX_GRIDX || y<0 || x>MAX_GRIDY)	return 0;
	  //int xx = x/4; xx=xx&0x3FF;
	  //int yy = y/4; yy=yy&0x3FF;
	  //
	  //unsigned char ret= g_pAttribute[yy][xx];
	  //return ret;
	return 0;
}


void GetAttack(int mob,int target,MSG_AttackOne*sm)
{
	sm->wType		= _MSG_AttackOne;
	sm->AttackerID	= mob;
	sm->wPDULength	= sizeof(MSG_AttackOne)-sizeof(HEADER);
	sm->dwClientTick= CurrentTime;
	sm->PosX		= pMob[mob].TargetX;
	sm->PosY		= pMob[mob].TargetY;
	sm->TargetX		= pMob[target].TargetX;
	sm->TargetY     = pMob[target].TargetY;
	
	
	sm->DoubleCritical   = 0;
	sm->CurrentMp	= -1;
	sm->ReqMp		= -1;

	sm->Dam[0].TargetID=0;
	sm->Dam[0].Damage=0;

	//memset(sm->TargetID,0,sizeof(sm->TargetID));
	//memset(sm->Damage,0,sizeof(sm->Damage));
	sm->Dam[0].TargetID = target;
	int	Resist		= -1;   // 0:불 1:얼음 2:신성 3:번개
 	sm->SkillParm	= 0;
	sm->SkillIndex	= -1;
	sm->Motion		=  0;
	sm->Dam[0].Damage   = pMob[mob].MOB.sMuscle;
}
extern int ServerIndex;
//void GetGuild(int conn)
//{
//	/*
//	STRUCT_ITEM * item = &pMob[conn].MOB.Equip[12];
//	int guild = BASE_GetGuild(item);
//    //int gs = guild>>12;
//	//if (gs!=ServerIndex) {pMob[conn].MOB.Guild;return;}
//
//    pMob[conn].MOB.Guild = guild;
//	if	(conn>=0 && conn<MAX_USER && item->sIndex==509)
//	{	pMob[conn].MOB.GuildLevel = 2;
//		for	(int i=0;i<MAX_GUILDZONE;i++)
//		{	if (g_pGuildZone[i].ChargeGuild==guild) {GuildMasterID[i]=conn;}
//		}
//	}	else
//	if	(conn>=0 && conn<MAX_USER && (item->sIndex>=526 &&item->sIndex<=531) )	// 서브길드
//	{	pMob[conn].MOB.GuildLevel = 1;
//	}	else
//	{	pMob[conn].MOB.GuildLevel = 0;
//	}
//	
//   return;
//   */
//}
//int GetGuild(STRUCT_ITEM* item)
//{
//	/*
//	int guild = BASE_GetGuild(item);
//	return guild;
//	*/
//	return 0;
//}


/*
BOOL GetEmptyItemGrid(int * gridx, int * gridy)  // true면 gridx,gridy을 깂이 유효, false면 빈자리 없음.
{
	if (pItemGrid[*gridy][*gridx]==0) return TRUE;

	for (int y=(*gridy)-1;y<=(*gridy)+1;y++)
	{
		for (int x=(*gridx)-1;x<=(*gridx)+1;x++)
		{
			if (x<0||y<0||x>=MAX_GRIDX||y>=MAX_GRIDY) continue;
            if (pItemGrid[y][x]==0)
			{  *gridy=y;*gridx=x;return TRUE;
			}
		}
	}
	return FALSE;
}
*/
BOOL GetEmptyItemGrid(int * gridx, int * gridy)  // true면 gridx,gridy을 깂이 유효, false면 빈자리 없음.
{
	if( (0 == pItemGrid[*gridy][*gridx]) && (0 == (eTNCell_Blocked & g_krgCell[*gridy][*gridx].usProperty )) ) return TRUE;
	int x, y ;
	for( y=(*gridy)-1;y<=(*gridy)+1;y++)
	{
		for( x=(*gridx)-1;x<=(*gridx)+1;x++)
		{
			if (x<0||y<0||x>=MAX_GRIDX||y>=MAX_GRIDY) continue;
            if ( 0 != pItemGrid[y][x] ) continue ; 
			if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) continue ;
			*gridy=y;
			*gridx=x;
			return TRUE;
		}
	}

	int iCenterX = *gridx ;
	int iCenterY = *gridy ;
	int iMaxIndex = g_pDetectEnemyRadius[eRds_MaxDetectEnemy] ;	
	for( int i = 0 ; i < iMaxIndex ; ++i )
	{
		x = iCenterX + g_pDetectEnemyTable[i][0] ;
		y = iCenterY + g_pDetectEnemyTable[i][1] ;
		if	( x<0 || y<0 || x>MAX_GRIDX || y>MAX_GRIDY ) continue;
		if ( 0 != pItemGrid[y][x] ) continue ; 
		if( eTNCell_Blocked & g_krgCell[y][x].usProperty ) continue ;
		*gridy=y;
		*gridx=x;
		return TRUE;
	}

	return FALSE;
}



//-------------------------------------------------------------------------------------------
//int IsPathCleared( int a_iFromX, int a_iFromY, int a_iToX, int a_iToY, int a_iDistance )
// 원거리 공격시, projectile이 지나게 되는 path 중간 중간의 점을 검사한다.
// 완벽한 검사는 아닐지라도 표본 검사를 통한 빠른 확인을 할 수 있다.
//@Param
//	- a_iFromX, a_iFromY : 원거리 공격자의 위치, 즉 source 좌표
//	- a_iToX, a_iToY : 목표물의 위치, destination 좌표
//	- a_iDistance : 두 지점 사이의 거리
//@Return
//	- 만약 날라가는 경로가 올바르다면 0을 return하고, 그렇지 않다면, 1값을 return한다.
//-------------------------------------------------------------------------------------------
int IsPathCleared( int a_iFromX, int a_iFromY, int a_iToX, int a_iToY, int a_iDistance )
{
	if( 0 >= a_iDistance ) return eTNRes_Succeeded ;

	int iDifferenceX = a_iToX - a_iFromX ;
	int iDifferenceY = a_iToY - a_iFromY ;

	HS2D_COORD krgPath[5] ;
	memset( krgPath, 0, sizeof(krgPath) ) ;

	int iPathCount = 0 ;

	if( 5 > a_iDistance )
	{
		krgPath[0].x = a_iFromX + iDifferenceX / 2 ;
		krgPath[0].y = a_iFromY + iDifferenceY / 2 ;
		iPathCount = 1 ;

		//krgPath[0].x = a_iFromX + (iDifferenceX*1) / 3 ;
		//krgPath[0].y = a_iFromY + (iDifferenceY*1) / 3 ;
		//krgPath[1].x = a_iFromX + (iDifferenceX*2) / 3 ;
		//krgPath[1].y = a_iFromY + (iDifferenceY*2) / 3 ;
		//iPathCount = 1 ;
	}
	else if( 10 > a_iDistance )
	{
		krgPath[0].x = a_iFromX + (iDifferenceX*2) / 10 ;
		krgPath[0].y = a_iFromY + (iDifferenceY*2) / 10 ;
		krgPath[1].x = a_iFromX + (iDifferenceX*4) / 10 ;
		krgPath[1].y = a_iFromY + (iDifferenceY*4) / 10 ;
		krgPath[2].x = a_iFromX + (iDifferenceX*6) / 10 ;
		krgPath[2].y = a_iFromY + (iDifferenceY*6) / 10 ;
		krgPath[3].x = a_iFromX + (iDifferenceX*8) / 10 ;
		krgPath[3].y = a_iFromY + (iDifferenceY*8) / 10 ;

		iPathCount = 4 ;
	}
	else if( 20 > a_iDistance )
	{
		krgPath[0].x = a_iFromX + (iDifferenceX*2) / 20 ;
		krgPath[0].y = a_iFromY + (iDifferenceY*2) / 20 ;
		krgPath[1].x = a_iFromX + (iDifferenceX*6) / 20 ;
		krgPath[1].y = a_iFromY + (iDifferenceY*6) / 20 ;
		krgPath[2].x = a_iFromX + (iDifferenceX*10) / 20 ;
		krgPath[2].y = a_iFromY + (iDifferenceY*10) / 20 ;
		krgPath[3].x = a_iFromX + (iDifferenceX*14) / 20 ;
		krgPath[3].y = a_iFromY + (iDifferenceY*14) / 20 ;
		krgPath[4].x = a_iFromX + (iDifferenceX*18) / 20 ;
		krgPath[4].y = a_iFromY + (iDifferenceY*18) / 20 ;
		iPathCount = 5 ;
	}
	else
	{
		krgPath[0].x = a_iFromX + (iDifferenceX*5) / 30 ;
		krgPath[0].y = a_iFromY + (iDifferenceY*5) / 30 ;
		krgPath[1].x = a_iFromX + (iDifferenceX*10) / 30 ;
		krgPath[1].y = a_iFromY + (iDifferenceY*10) / 30 ;
		krgPath[2].x = a_iFromX + (iDifferenceX*15) / 30 ;
		krgPath[2].y = a_iFromY + (iDifferenceY*15) / 30 ;
		krgPath[3].x = a_iFromX + (iDifferenceX*20) / 30 ;
		krgPath[3].y = a_iFromY + (iDifferenceY*20) / 30 ;
		krgPath[4].x = a_iFromX + (iDifferenceX*25) / 30 ;
		krgPath[4].y = a_iFromY + (iDifferenceY*25) / 30 ;

		iPathCount = 5 ;
	}

	int iFromHeight = g_krgCell[a_iFromY][a_iFromX].usHeight ;
	int iToHeight = g_krgCell[a_iToY][a_iToX].usHeight ;

	//unsigned short usPreviousHeight = g_krgCell[krgPath[0].y][krgPath[0].x].usHeight;
	int iCountHeightDiff = 0;
	for( int i = 0 ; i < iPathCount ; ++i )
	{
		if( krgPath[i].x<=0 || krgPath[i].y<=0 || krgPath[i].x>=MAX_GRIDX || krgPath[i].y>=MAX_GRIDY ) continue ;
		// (x,y) 지점이 cleared되어 있는가? blocked되어 있는가? 높이 차가 많이 나는가?
		if( eTNCell_Blocked & g_krgCell[krgPath[i].y][krgPath[i].x].usProperty )
		{
			if( !(eTNCell_AttackThrough & g_krgCell[krgPath[i].y][krgPath[i].x].usProperty) ) return eTNRes_CellBlocked ; // 아주 얇게 색칠해져 있어서 탐지되지 않을 가능성이 높다.
			//if( (g_krgCell[krgPath[i].y][krgPath[i].x].usHeight - usFromHeight) > 100 ) return eTNRes_Failed ; // 아주 얇게 색칠해져 있어서 탐지되지 않을 가능성이 높다.
			//if( (g_krgCell[krgPath[i].y][krgPath[i].x].usHeight - usFromHeight) > 200 ) return eTNRes_Failed ; // 중간의 임의의 좌표가 현재보다 높이가 200(캐릭터 키) 초과일 경우 날라가질 못한다.
		}

		int iHeight = g_krgCell[krgPath[i].y][krgPath[i].x].usHeight;

		if( (iHeight - iToHeight) > g_irgSetting[eCnst_ObstacleHeight] ) // default 100
			if( (iHeight - iFromHeight) > g_irgSetting[eCnst_ObstacleHeight] ) return eTNRes_Obstacle ; // 중간의 임의의 좌표가 현재보다 높이가 90(허리위) 초과일 경우 날라가질 못한다.

		//usPreviousHeight = usHeight;
			/* 

			// 크루마 높이 상태, 성벽 기준


								 +----+           => 16000
								 |    |
							 	 |    |
								 |    |
					 			 |    |
				    -------------+    +---------  => 15160

					840(=16000-15160)의 높이차가 난다.

					캐릭터의 기본 높이는 170~200이라고 가정
					허리 높이는 80~90정도 된다. 따라서 높이차가 90 아래쪽이면 장애물 위쪽으로 통과 가능한 것이다.
					90을 1cell 정도로 생각한다. 그럼 성벽위까지는 대충 9~10cell 정도 거리차가 있는 것이다.


			*/


		if( (iHeight-g_irgSetting[eCnst_CharacterHeight]) > iFromHeight ) ++iCountHeightDiff;
		if( 1 < iCountHeightDiff ) return eTNRes_TooHigh; // 높이 차가 2회 이상 크게 차이가 나는 경우 => 성벽 위의 안쪽에 서 있을 가능성이 높다.

	}

	return eTNRes_Succeeded ;
}



int CalDistance( int a_iMob1, int a_iMob2 )
{
	if	( a_iMob1<=0 || a_iMob1>=MAX_MOB ) return 10000 ;
	if	( a_iMob2<=0 || a_iMob2>=MAX_MOB ) return 10000 ;

	HS2D_COORD kMyPos, kTargetPos ;
	pMob[a_iMob1].get_Coord( kMyPos ) ;
	pMob[a_iMob2].get_Coord( kTargetPos ) ;
	int iDist = CalDistance( kMyPos, kTargetPos, pMob[a_iMob1].get_BodyRadius(), pMob[a_iMob2].get_BodyRadius() ) ;
	return iDist ;
}


int CalDistance( HS2D_COORD& a_kSrc, HS2D_COORD& a_kDest, byte a_nSrcBodyRadius, byte a_nDestBodyRadius )
{
	int iTempX = a_kSrc.x - a_kDest.x ;
	int iTempY = a_kSrc.y - a_kDest.y ;

	double dRealDist = sqrt((double)(iTempX*iTempX + iTempY*iTempY) ) ;
	int iDistance = (int)dRealDist ;
	if( 0.5 <= (dRealDist - (double)iDistance) ) ++iDistance ;
	iDistance -= a_nSrcBodyRadius ;
	iDistance -= a_nDestBodyRadius ;
	if( 0 > iDistance ) iDistance = 0 ;
	else
	{
/*
		int iHeight = g_krgCell[a_kSrc.y][a_kSrc.x].usHeight - g_krgCell[a_kDest.y][a_kDest.x].usHeight ;
		if( 0 > iHeight ) iHeight = 0 - iHeight ; // 음수일 경우 양수로 변경을 한다.		
		if( 200 < iHeight )  // 이 높이차는 test해보면서 이상하게 느끼지 않을 정도로 수정을 한다.
		{
			iHeight = iHeight / 100 ;
			iDistance = (int)sqrt((double)(iDistance*iDistance + iHeight*iHeight) ) ;
		}
*/
	}
	return iDistance ;
}


BOOL GetAttackPos( int mob, HS2D_COORD& a_kDest, HS2D_COORD& a_kSrc )
{
	if  (a_kDest.x<0||a_kDest.y<0||a_kDest.x>=MAX_GRIDX||a_kDest.y>=MAX_GRIDY)
	{   Log("err GetEmptyMobGrid Out of range","-system",0);  
        return FALSE;
	}

	if	(pMobGrid[a_kDest.y][a_kDest.x]==mob) return TRUE;	

	if( 0 == pMobGrid[a_kDest.y][a_kDest.x] ) 
		if( 0 == (g_krgCell[a_kDest.y][a_kDest.x].usProperty & pMob[mob].m_iBlockedCell) ) return TRUE;
    
	HS2D_COORD krgPos[25] ;
	int iShortestDist = 1000 ;
	int iShortestPos = 0 ;
	int iSize = 0 ;
	int y=0;
	int x=0;
	for	( y=(a_kDest.y)-1; y<=(a_kDest.y)+1; y++ )
	{   for	(x=(a_kDest.x)-1;x<=(a_kDest.x)+1; x++ )
		{	if(x<0||y<0||x>=MAX_GRIDX||y>=MAX_GRIDY) continue ;
            if( 0 != pMobGrid[y][x] ) continue ; // 다른 mob이 자리잡고 있다.
			if( pMob[mob].m_iBlockedCell & g_krgCell[y][x].usProperty )	continue ;
			krgPos[iSize].x = x ;
			krgPos[iSize].y = y ;
			++iSize ;
			if( 25 <= iSize ) iSize = 24 ;
			//a_kDest.y=y;a_kDest.x=x;return TRUE;
		}
	}
	if( 0 < iSize )
	{
		int iDist = 0 ;
		for( int i = 0 ; i < iSize ; ++i )
		{
			iDist = CalDistance( a_kSrc, krgPos[i], 0, 0 ) ;
			if( iDist < iShortestDist )
			{
				iShortestDist = iDist ;
				iShortestPos = i ;
			}
			else if( iDist == iShortestDist )
			{
				if( 50 < rand() % 100 )
				{
					iShortestPos = i ;
				}
			}
		}
		a_kDest = krgPos[iShortestPos] ;
		return TRUE ;
	}

	iShortestPos = 0 ;
	iShortestDist = 1000 ;
	iSize = 0 ;
	for	( y=(a_kDest.y)-2; y<=(a_kDest.y)+2; y++)
	{	for ( x=(a_kDest.x)-2; x<=(a_kDest.x)+2; x++)
		{	if(x<0||y<0||x>=MAX_GRIDX||y>=MAX_GRIDY) continue ;
            if( 0 != pMobGrid[y][x] ) continue ; // 다른 mob이 자리잡고 있다.
			if( pMob[mob].m_iBlockedCell & g_krgCell[y][x].usProperty )	continue ;
			krgPos[iSize].x = x ;
			krgPos[iSize].y = y ;
			++iSize ;
			if( 25 <= iSize ) iSize = 24 ;
			//a_kDest.y=y;a_kDest.x=x;return TRUE;
		}
	}
	if( 0 < iSize )
	{
		int iDist = 0 ;
		for( int i = 0 ; i < iSize ; ++i )
		{
			iDist = CalDistance( a_kSrc, krgPos[i], 0, 0 ) ;
			if( iDist < iShortestDist )
			{
				iShortestDist = iDist ;
				iShortestPos = i ;
			}
		}
		a_kDest = krgPos[iShortestPos] ;
		return TRUE ;
	}

	//char temp[256]; sprintf(temp,"err can't get empty pos name:%s x:%d y:%d",pMob[mob].MOB.szName, a_kDest.x,a_kDest.y);
    //Log(temp,"-system",0);

	return FALSE;
}


BOOL PickFreeMobGrid( int mob, int* tx, int* ty, int a_iAdditionalBlockedCellPrty )  // true면 gridx,gridy을 깂이 유효, false면 빈자리 없음.
{
	if  (*tx<=0||*ty<=0||*tx>=MAX_GRIDX||*ty>=MAX_GRIDY)
	{   Log("err GetEmptyMobGrid Out of range","-system",0);  
        return FALSE;
	}

	int iBlockedCell = pMob[mob].m_iBlockedCell | a_iAdditionalBlockedCellPrty ;

	if(pMobGrid[*ty][*tx]==mob) return TRUE;
	if( 0 == pMobGrid[*ty][*tx] )
		if( 0 == ( iBlockedCell & g_krgCell[*ty][*tx].usProperty ) ) return TRUE ;

	int iRadius = 10 ;
	int iMaxIndex = g_pDetectEnemyRadius[iRadius] ;
	int x, y ;
	for( int i = 0 ; i < iMaxIndex ; ++i )
	{
		x = *tx + g_pDetectEnemyTable[i][0] ;
		y = *ty + g_pDetectEnemyTable[i][1] ;
		if(x<0||y<0||x>=MAX_GRIDX||y>=MAX_GRIDY) continue;
        if( 0 != pMobGrid[y][x] ) continue ; // mob이 그 자리를 차지하고 있으면, ...
		if( iBlockedCell & g_krgCell[y][x].usProperty )	continue;			
		*ty=y ;
		*tx=x ;

		return TRUE ;
	}

	return FALSE ;
}


//@Param
//	- a_iAdditionalBlockedCellPrty : 빈 자리를 찾을 때 배제해야할 추가적인 cell property
//BOOL GetEmptyMobGrid(int mob, int * tx, int * ty, int a_iSkip, int a_iRadius )  // true면 gridx,gridy을 깂이 유효, false면 빈자리 없음.
BOOL GetEmptyMobGrid(int mob, int * tx, int * ty, int a_iAdditionalBlockedCellPrty )  // true면 gridx,gridy을 깂이 유효, false면 빈자리 없음.
{
	if  (*tx<0||*ty<0||*tx>=MAX_GRIDX||*ty>=MAX_GRIDY)
	{   Log("err GetEmptyMobGrid Out of range","-system",0);  
        return FALSE;
	}

	int iBlockedCell = pMob[mob].m_iBlockedCell | a_iAdditionalBlockedCellPrty ;

	if(pMobGrid[*ty][*tx]==mob) return TRUE;
	if( 0 == pMobGrid[*ty][*tx] )
		if( 0 == ( iBlockedCell & g_krgCell[*ty][*tx].usProperty ) ) return TRUE ;
    
	//if( 1 >= a_iRadius ) return FALSE ;

	int y=0;
	int x=0;
	for	( y=(*ty)-1; y<=(*ty)+1; y++ )
	{   for	(x=(*tx)-1;x<=(*tx)+1; x++ )
		{	if(x<0||y<0||x>=MAX_GRIDX||y>=MAX_GRIDY) continue;
            if( 0 != pMobGrid[y][x] ) continue ; // mob이 그 자리를 차지하고 있으면, ...
			if( iBlockedCell & g_krgCell[y][x].usProperty )	continue;			
			*ty=y ;
			*tx=x ;
			return TRUE ;
		}
	}
	for	( y=(*ty)-2; y<=(*ty)+2; y++)
	{	for ( x=(*tx)-2; x<=(*tx)+2; x++)
		{	if(x<0||y<0||x>=MAX_GRIDX||y>=MAX_GRIDY) continue ;
            if( 0 != pMobGrid[y][x] ) continue ; // mob이 그 자리를 차지하고 있으면, ...
			if( iBlockedCell & g_krgCell[y][x].usProperty ) continue ;
			*ty=y ;
			*tx=x ;
			return TRUE ;
		}
	}

	for ( y=(*ty)-3;y<=(*ty)+3;y++)
	{	for (int x=(*tx)-3;x<=(*tx)+3;x++)
		{	if(x<0||y<0||x>=MAX_GRIDX||y>=MAX_GRIDY) continue ;
            if( 0 != pMobGrid[y][x] ) continue ; // mob이 그 자리를 차지하고 있으면, ...
			if( iBlockedCell & g_krgCell[y][x].usProperty )	continue ;
			*ty=y ;
			*tx=x ;
			return TRUE ;
		}
	}

	for ( y=(*ty)-4;y<=(*ty)+4;y++)
	{	for (int x=(*tx)-4;x<=(*tx)+4;x++)
		{	if(x<0||y<0||x>=MAX_GRIDX||y>=MAX_GRIDY) continue ;
            if( 0 != pMobGrid[y][x] ) continue ; // mob이 그 자리를 차지하고 있으면, ...
			if( iBlockedCell & g_krgCell[y][x].usProperty )	continue ;
			*ty=y ;
			*tx=x ;
			return TRUE ;
		}
	}

	for ( y=(*ty)-5;y<=(*ty)+5;y++)
	{	for (int x=(*tx)-5;x<=(*tx)+5;x++)
		{	if(x<0||y<0||x>=MAX_GRIDX||y>=MAX_GRIDY) continue ;
            if( 0 != pMobGrid[y][x] ) continue ; // mob이 그 자리를 차지하고 있으면, ...
			if( iBlockedCell & g_krgCell[y][x].usProperty )	continue ;
			*ty=y ;
			*tx=x ;
			return TRUE ;
		}
	}

	if(mob>0 && mob<MAX_USER)
	{	char temp[256]; sprintf(temp,"err can't get empty pos name:%s x:%d y:%d BC:%08X PP:%08X",pMob[mob].MOB.szName, *tx,*ty,iBlockedCell, g_krgCell[y][x].usProperty);
		Log(temp,"-system",0);
	}

	return FALSE;
}

BOOL GetMovableMobGrid(int mob, int * tx, int * ty )  
{
	if  (*tx<0||*ty<0||*tx>=MAX_GRIDX||*ty>=MAX_GRIDY)
	{   Log("err GetEmptyMobGrid Out of range","-system",0);  
        return FALSE;
	}

	int iBlockedCell = pMob[mob].m_iBlockedCell;

	int y=0; int x=0;
	int	nSize = 0;
	HS2D_COORD				pMovableGrid[16];

	ZeroMemory(pMovableGrid, sizeof(HS2D_COORD)*16);

	y=(*ty)-2;
	for( x=(*tx)-2;x<=(*tx)+2; x++ )
	{	if(!CheckGrid(x, y, iBlockedCell)) continue; 		
		pMovableGrid[nSize].x = x;
		pMovableGrid[nSize].y = y; nSize++;
	}
		
	x=(*tx)-2;
	for( y=(*ty)-1;y<=(*ty)+1; y++ )
	{	if(!CheckGrid(x, y, iBlockedCell)) continue; 		
		pMovableGrid[nSize].x = x;
		pMovableGrid[nSize].y = y; nSize++;
	}

	x=(*tx)+2;
	for( y=(*ty)-1;y<=(*ty)+1; y++ )
	{	if(!CheckGrid(x, y, iBlockedCell)) continue; 		
		pMovableGrid[nSize].x = x;
		pMovableGrid[nSize].y = y; nSize++;
	}

	y=(*ty)+2; 
	for( x=(*tx)-2;x<=(*tx)+2; x++ )
	{	if(!CheckGrid(x, y, iBlockedCell)) continue; 		
		pMovableGrid[nSize].x = x;
		pMovableGrid[nSize].y = y; nSize++;
	}

	int nPos = GetRandom(0, nSize);
	if(nPos<0 || nPos>=nSize)
	{	char temp[256]; sprintf(temp,"err can't get empty pos1 name:%s x:%d y:%d BC:%08X PP:%08X",pMob[mob].MOB.szName, *tx,*ty,iBlockedCell, g_krgCell[y][x].usProperty);
		Log(temp,"-system",0); return FALSE;
	}

	if(nSize<=0)
	{	char temp[256]; sprintf(temp,"err can't get empty pos2 name:%s x:%d y:%d BC:%08X PP:%08X",pMob[mob].MOB.szName, *tx,*ty,iBlockedCell, g_krgCell[y][x].usProperty);
		Log(temp,"-system",0); return FALSE;
	}

	*ty = pMovableGrid[nPos].y;
	*tx = pMovableGrid[nPos].x;

	return TRUE;
}

bool CheckGrid(int x, int y, int iBlocked)
{
	if(x<0||y<0||x>=MAX_GRIDX||y>=MAX_GRIDY) return false;
    if( 0 != pMobGrid[y][x] ) return false ; // mob이 그 자리를 차지하고 있으면, ...
	if( iBlocked & g_krgCell[y][x].usProperty )	return false;

	return true;
}

int GetCurKill(int conn)
{
	/*
	if	(conn<=0||conn>=MAX_USER) return 0;
	unsigned char cv=pMob[conn].MOB.Carry[KILL_MARK].stEffect[0].cValue;
	int ret = cv;
	return ret;
	*/
	return FALSE;
}
int GetTotKill(int conn)
{
	/*
	if	(conn<=0||conn>=MAX_USER) return 0;
	unsigned char cv1=pMob[conn].MOB.Carry[KILL_MARK].stEffect[1].cValue;
	unsigned char cv2=pMob[conn].MOB.Carry[KILL_MARK].stEffect[2].cValue;
	int ret = cv1+cv2*256;
	return ret;
	*/
	return 0;
}
void SetCurKill(int conn,int value)
{
	/*
	if	(conn<=0||conn>=MAX_USER) return;
	if	(value<0) value=0;
	if	(value>200) value=200;
	unsigned char cv = value;
	pMob[conn].MOB.Carry[KILL_MARK].stEffect[0].cValue=cv;
	*/
}
void SetTotKill(int conn,int value)
{	/*
	if	(conn<=0||conn>=MAX_USER) return;
	if	(value<0) value=0;
	if	(value>9999) value=9999;
	unsigned char cv1 = value%256;
	unsigned char cv2 = value/256;
	pMob[conn].MOB.Carry[KILL_MARK].stEffect[1].cValue=cv1;
	pMob[conn].MOB.Carry[KILL_MARK].stEffect[2].cValue=cv2;
	*/
}
int	GetPKPoint(int conn)
{	/*
	unsigned char cv = pMob[conn].MOB.Carry[KILL_MARK].stEffect[0].cEffect;
	int ret = cv;
	return ret;
	*/
	return 0;
}
int GetGuilty(int conn)
{
	/*
	unsigned char cv = pMob[conn].MOB.Carry[KILL_MARK].stEffect[1].cEffect;
	int ret = cv;
	if	(ret>50) {pMob[conn].MOB.Carry[KILL_MARK].stEffect[1].cEffect=0;ret=0;}
	return ret;
	*/
	return 0;
}
void SetGuilty(int conn,int value)
{
	/*
	if	(conn<=0||conn>=MAX_USER) return;
	if	(value<0)	value=0;
	if	(value>50)	value=50;
	unsigned char cv = value;
	pMob[conn].MOB.Carry[KILL_MARK].stEffect[1].cEffect=cv;
	*/
}


void SetPKPoint(int conn,int value)
{
	/*
	if	(conn<=0||conn>=MAX_USER) return;
	if	(value<1) value=1;
	if	(value>150) value=150;
	unsigned char cv = value;
	pMob[conn].MOB.Carry[KILL_MARK].stEffect[0].cEffect=cv;
	*/
}

int GetMOBID(char* pszName)
{
	int nID = 0;
	//char pName[SZNAME_LENGTH]; ZeroMemory(pName, SZNAME_LENGTH);
	//strncpy(pName, pszName, SZNAME_LENGTH); strupr(pName);
	for(int i=0; i<MAX_USER; i++)
	{	//char pMember[SZNAME_LENGTH]; ZeroMemory(pMember, SZNAME_LENGTH);
		//strncpy(pMember, pMob[i].MOB.szName, SZNAME_LENGTH); strupr(pMember);
		if(strncmp(pszName, pMob[i].MOB.szName, SZNAME_LENGTH) == 0) 
		{	if(pUser[i].Mode!=USER_PLAY) return 0;
			nID=i; break;
		}
	}

	return nID;
}

int GetMOBIDFromID(char* pszAccount)
{
	int nID = 0;
	//char pName[SZNAME_LENGTH]; ZeroMemory(pName, SZNAME_LENGTH);
	//strncpy(pName, pszName, SZNAME_LENGTH); strupr(pName);
	for(int i=0; i<MAX_USER; i++)
	{	//char pMember[SZNAME_LENGTH]; ZeroMemory(pMember, SZNAME_LENGTH);
		//strncpy(pMember, pMob[i].MOB.szName, SZNAME_LENGTH); strupr(pMember);
		if(strncmp(pszAccount, pUser[i].AccountName, ACCOUNTNAME_LENGTH) == 0) 
		{	if(pUser[i].Mode!=USER_PLAY) return 0;
			nID=i; break;
		}
	}

	return nID;
}

STRUCT_ITEM* GetItem(int conn, BYTE byPlace, BYTE byIndex)
{
	char pLog[256] = {0,};
	if	(byPlace==ITEM_PLACE_INVEN)
	{	if (byIndex<0&&byIndex>=MAX_INVEN)  sprintf(pLog, "err sellitem - Inven item index:%d",byIndex);
        return &pMob[conn].MOB.Inven[byIndex];
	}	else
	if	(byPlace==ITEM_PLACE_EQUIP)
	{	if (byIndex<0&&byIndex>=MAX_EQUIP)	 sprintf(pLog, "err sellitem - Equip item index:%d",byIndex);
		return &pMob[conn].MOB.Equip[byIndex];
	}	else
	if	(byPlace==ITEM_PLACE_CARGO)
	{	if (byIndex<0&&byIndex>=MAX_CARGO)	 sprintf(pLog, "err sellitem - Cargo item index:%d",byIndex);
		return &pUser[conn].Cargo[byIndex];
	}	else 
		return 0;

	Log(pLog,pUser[conn].AccountName,pUser[conn].IP);

	return 0;
}

BOOL GetTrimurityArea(int conn, int &nX, int &nZ)
{
	BYTE byTrimuriti=0;	char temp[1024]={0,0,0,};
	switch(pMob[conn].MOB.byTrimuriti)
	{	case eTNClan_Brahma:					//	브라흐마
			byTrimuriti = 1;	
			break;
		case eTNClan_Vishnu:					//	비슈느
			byTrimuriti = 2;
			break;
		case eTNClan_Siva:						//	시바
			byTrimuriti = 3;
			break;	
		case eTNClan_GM:
			byTrimuriti = 1 ; 
			break;
	}

	if(byTrimuriti<0 || byTrimuriti>3) 
	{	sprintf(temp,"clo err regen - Closeuser trimurity:%d",byTrimuriti); Log(temp,pMob[conn].MOB.szName,0);
		return FALSE;
	}

	g_dwUserConnect++;	
	BYTE byCount = TrimurityArea.byTrimuriti[byTrimuriti];
	if(byCount>0 && byCount<=MAX_GENERATION_AREA)		//	주신탄생지역이 존재할경우.
	{	BYTE byIndex = (BYTE)(g_dwUserConnect%byCount);
		nX = GetRandom(TrimurityArea.pArea[byTrimuriti][byIndex].snStartX, TrimurityArea.pArea[byTrimuriti][byIndex].snEndX);
		nZ = GetRandom(TrimurityArea.pArea[byTrimuriti][byIndex].snStartZ, TrimurityArea.pArea[byTrimuriti][byIndex].snEndZ);
	} else
	if(TrimurityArea.byTrimuriti[0]>0 && TrimurityArea.byTrimuriti[0]<=MAX_GENERATION_AREA)
	{	BYTE byIndex = (BYTE)(g_dwUserConnect%(TrimurityArea.byTrimuriti[0]));
		nX = GetRandom(TrimurityArea.pArea[0][byIndex].snStartX, TrimurityArea.pArea[0][byIndex].snEndX);
		nZ = GetRandom(TrimurityArea.pArea[0][byIndex].snStartZ, TrimurityArea.pArea[0][byIndex].snEndZ);
	}	else											//	주신지역과 공동지역이 없을경우
	{	Log("clo err regen - have no regen data - Closeuser",pMob[conn].MOB.szName,0);
		return FALSE;
	}


	//#ifdef __DEBUG_LOG__
	//{
	//	char chBuf[512] = { 0,0,0, };
	//	sprintf(chBuf, "GetTrimurityArea() > conn:%d, coord(%d,%d)\r\n"
	//		//, g_kSystemTime.wMonth, g_kSystemTime.wDay, g_kSystemTime.wHour, g_kSystemTime.wMinute, g_kSystemTime.wSecond
	//		, conn, nX, nZ
	//		); 
	//	WriteLog( chBuf, ".\\Monster_Log\\[Log]StartPosition.txt" );
	//}
	//#endif




	return TRUE;
}

BOOL GetArenaArea(int conn, int &nX, int &nZ)
{
	int iDist = 0; int iTempDist = 0;
	HS2D_COORD pos;
	pos.x = pMob[conn].TargetX; pos.y = pMob[conn].TargetY;

	iTempDist = CalDistance(g_stPosStronghold[eStronghold_Northwest], pos, 0, 0);
	{
		iDist = iTempDist; 
		nX = g_stPosStronghold[eStronghold_Northwest].x; 
		nZ = g_stPosStronghold[eStronghold_Northwest].y;
	}

	iTempDist = CalDistance(g_stPosStronghold[eStronghold_Northeast], pos, 0, 0);
	if(iTempDist<iDist) 
	{
		iDist = iTempDist; 
		nX = g_stPosStronghold[eStronghold_Northeast].x; 
		nZ = g_stPosStronghold[eStronghold_Northeast].y;
	}

	iTempDist = CalDistance(g_stPosStronghold[eStronghold_Southwest], pos, 0, 0);
	if(iTempDist<iDist) 
	{
		iDist = iTempDist; 
		nX = g_stPosStronghold[eStronghold_Southwest].x; 
		nZ = g_stPosStronghold[eStronghold_Southwest].y;
	}

	iTempDist = CalDistance(g_stPosStronghold[eStronghold_Southeast], pos, 0, 0);
	if(iTempDist<iDist) 
	{
		iDist = iTempDist; 
		nX = g_stPosStronghold[eStronghold_Southeast].x; 
		nZ = g_stPosStronghold[eStronghold_Southeast].y;
	}

	return TRUE;
}

int GetRandom(int nStart, int nEnd)
{
	if( nStart > nEnd) 
	{	int nTmp = nEnd;
		nEnd = nStart;
		nStart = nTmp;
	}
	if(nStart<0) nStart=0;

	int iDice = (nEnd - nStart);
	if( 0 >= iDice ) iDice = 1; 

	return rand() % iDice + nStart;
}

int GetItemCount(int conn, short snItemIndex)
{
	if(conn<=0 || conn>=MAX_USER) return 0;

	int snIndex=0;	int iCount=0;
	for(int i=0; i<pMob[conn].byMaxInven; i++)
	{	
		if(pMob[conn].MOB.Inven[i].snIndex == snItemIndex) iCount += pMob[conn].MOB.Inven[i].byCount;
	}

	return iCount;
}

CMob * GetMobFromIndex(unsigned int index)
{	   if (index<0||index>=MAX_MOB)  return NULL;
	   return &pMob[index];
}

int  GetAngle(int x,int y)
{
	 if (x==0||y==0) return 0;
	 double tangle =  atan2( (FLOAT)y, (FLOAT) x);
     int angle = (int) ((tangle*3600)/6.283184);  
     if (angle<0) angle+=3600;
	 if (angle>3600) angle-=3600;
	 return angle;
}

int  GetLength(int x,int y)
{
	 FLOAT valx = (FLOAT)(x*x);
	 FLOAT valy = (FLOAT)(y*y);     
	 FLOAT valxy = valx+valy;
	 if (valxy>100) return 100;
	 if (valxy<=0) return 0;
	 double fout= sqrt(valxy);
     int out = (int) fout;
 
	 return out;
}

byte	GetScriptQuestLevel	(int conn, short snQuestID)
{
	if(snQuestID<100 || snQuestID>355) return 0;	//	100 ~ 355 까지의 ID

	if(pUser[conn].m_snQuestID == snQuestID) return pUser[conn].m_byQuestLevel;

	int nQuest = snQuestID - 100;	//	100번 퀘스트는 0
	int nIndex1 = snQuestID / 32;	//	m_dwQuestHistory[8]의 nIndex1 번째 배열
	int nIndex2 = snQuestID % 32;	//	nIndex2 번째 비트
	DWORD dwFlag = 0x00000001 << nIndex2;

	if(pUser[conn].m_dwQuestHistory[nIndex1] & dwFlag) return 255;

	return 0;
}
