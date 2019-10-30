#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h> 
#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <string.h>        
#include <time.h> 
#include <math.h>
#include <errno.h>
#include <string.h>
#include "basedef.h"
#include "CPSock.h"
#include "ItemEffect.h"
#include "Language.h"
#include "SendFunc.h"
#include "GetFunc.h"
#include "CUser.h"
#include "CMob.h"
#include "CItem.h"
#include "CGuild.h"
#include "Server.h"
#include "CrackType.h"
#include "Config.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

extern unsigned int		CurrentTime;
extern CMob				pMob     [MAX_MOB];
extern CUser			pUser    [MAX_USER];
extern CItem			pItem    [MAX_ITEM];
extern unsigned short	pMobGrid [MAX_GRIDY][MAX_GRIDX];
extern unsigned short	pItemGrid[MAX_GRIDY][MAX_GRIDX];
extern CGuild			pGuild[MAX_USER];
extern int                     g_iViewGridX ;
extern int                     g_iViewGridY ;
extern int                     g_iHalfGridX ;
extern int                     g_iHalfGridY ;
extern TNSTRONGHOLD				g_krgStronghold[eStronghold_MaxCount] ;
extern int						g_iCastleOwner;
extern CConfig					g_Config;
extern int						g_iBrahmaCount;
extern int						g_iVishnuCount;
extern int						g_iSivaCount;

extern void				Log( char * String1, char * String2 ,unsigned int ip );
extern BOOL				AddCrackError(int conn,int val,int Type);

/////////////////////////////////////////////////////////////////////////////////
//
//  SendClientMessage 
//
/////////////////////////////////////////////////////////////////////////////////
void SendClientMessage(int conn, char * msg)
{
	if (conn<=0 || conn>=MAX_USER) return;
    MSG_MessagePanel sm; sm.wType= _MSG_MessagePanel;
	sm.nID = 0;  
	memcpy(sm.String,msg,MESSAGE_LENGTH);
	sm.String[MESSAGE_LENGTH-1]=0;
	sm.String[MESSAGE_LENGTH-2]=0;
	pUser[conn].cSock.AddMessage((char*)&sm,sizeof(MSG_MessagePanel));
}

void SendClientResult(int conn, WORD wType, BYTE byResult)
{
	if (conn<=0 || conn>=MAX_USER) return;
	S_RESULT sm; sm.wType = wType+0x8000;
	sm.nResult = (int)byResult;

	pUser[conn].cSock.AddMessage((char*)&sm,sizeof(MSG_MessagePanel));
}

/////////////////////////////////////////////////////////////////////////////////
//
//  SendNotice
//
/////////////////////////////////////////////////////////////////////////////////
void SendNotice (char *str)
{
	for (int i=0;i<MAX_USER;i++)
	{   if (pUser[i].Mode!=USER_PLAY) continue;
		SendClientMessage(i,str);
	}

}

void SendToAll(MSG_STANDARD * msg)
{
	 for (int i=0;i<MAX_USER;i++)
	 {   if (pUser[i].Mode!=USER_PLAY) continue;
         pUser[i].cSock.AddMessage((char*)msg,msg->wPDULength+sizeof(HEADER));
	 }
}

void SendTrimuriti(BYTE byTrimuriti, MSG_STANDARD * msg)
{
	 for (int i=0;i<MAX_USER;i++)
	 {  if (pUser[i].Mode!=USER_PLAY) continue;
		if (pMob[i].MOB.byTrimuriti!=byTrimuriti) continue;
        pUser[i].cSock.AddMessage((char*)msg,msg->wPDULength+sizeof(HEADER));
	 }
}


/////////////////////////////////////////////////////////////////////////////////
//  SendClientSignal
void SendClientSignal(int conn,int id, unsigned short signal)
{
	if (conn<=0 || conn>=MAX_USER) return;
     MSG_STANDARD sm; sm.wType= signal;
	 //sm.ID=id;
	 pUser[conn].cSock.AddMessage((char*)&sm,sizeof(  MSG_STANDARD));
}

/////////////////////////////////////////////////////////////////////////////////
//  SendCreateMob
void SendCreateMob(int dest, int sour, BOOL bSend)
{
     if (dest<=0 || dest>=MAX_USER) return;
	 S_SCP_INIT_OTHER_MOB sm;
	 GetCreateMob(sour,&sm);
	 pUser[dest].cSock.AddMessage((char*)&sm,sizeof(S_SCP_INIT_OTHER_MOB));
	 if (bSend) pUser[dest].cSock.SendMessage();
}

/////////////////////////////////////////////////////////////////////////////////
//  SendCreateItem
void SendCreateItem(int conn, int item, BOOL bSend)
{
	if (conn<=0 || conn>=MAX_USER) return;
	S_SCP_MAP_ITEM_APPEAR sm; GetCreateItem(item,&sm); sm.nMobIndex=0;
    pUser[conn].cSock.AddMessage((char*)&sm,sizeof(S_SCP_MAP_ITEM_APPEAR)); 
	if (bSend) pUser[conn].cSock.SendMessage();
}

void SendRemoveMob(int dest, int sour, BOOL Type,int bSend)
{
	if (dest<=0 || dest>=MAX_USER) return;
	S_SCP_RESP_REMOVE_MOB sm; sm.wType = SCP_RESP_REMOVE_MOB; 
	sm.nID=sour; sm.byResult = Type; sm.dwKillerID = 0 ; sm.byRemoveType = 0 ;
	pUser[dest].cSock.AddMessage((char*)&sm,sizeof(S_SCP_RESP_REMOVE_MOB));
	if (bSend)	pUser[dest].cSock.SendMessage();
}

void SendRemoveItem(int dest, int nID, int bSend)
{
	if (dest<=0 || dest>=MAX_USER) return;
	S_SCP_MAP_ITEM_DISAPPEAR itemdisappear;
	itemdisappear.wType = SCP_MAP_ITEM_DISAPPEAR;
	itemdisappear.wPDULength = sizeof(S_SCP_MAP_ITEM_DISAPPEAR)-sizeof(HEADER);
	itemdisappear.nItemID = nID; ZeroMemory(itemdisappear.szName, SZNAME_LENGTH);
	pUser[dest].cSock.AddMessage((char*)&itemdisappear, sizeof(S_SCP_RESP_REMOVE_MOB));
	if (bSend)	pUser[dest].cSock.SendMessage();
}

void SendGridMob(int conn)
{
	if (conn<=0 || conn>=MAX_USER) return;

	int xx = pMob[conn].TargetX;
	int yy = pMob[conn].TargetY;
	int sx1,sy1,sx2,sy2;        // Source Rect
	
	int SizeY  = g_iViewGridY;
	int SizeX  = g_iViewGridX;
	int StartX = xx - g_iHalfGridX; //23/2 = 11         -11 ~   +11
	int StartY = yy - g_iHalfGridY;
	if  (StartX+SizeX >= MAX_GRIDX)   {SizeX=SizeX-(StartX+SizeX-MAX_GRIDX);}
	if  (StartY+SizeY >= MAX_GRIDY)   {SizeY=SizeY-(StartY+SizeY-MAX_GRIDY);}
	if  (StartX<0)                    {StartX=0; SizeX=SizeX+StartX;}
	if  (StartY<0)                    {StartY=0; SizeY=SizeY+StartY;}
	sx1=StartX;
	sy1=StartY;
    sx2=StartX+SizeX;
	sy2=StartY+SizeY;
	if	(SizeX<=0 || SizeY<=0 ||SizeX>g_iViewGridX || SizeY>g_iViewGridY) return;
	for (int y=sy1 ;y<sy2;y++)
	{	for (int x=sx1;x<sx2;x++)
		{
			int tmob = pMobGrid[y][x];
			int titem = pItemGrid[y][x];
			if  (tmob>0 && tmob<MAX_MOB && tmob!=conn) 
			{	if (pMob[tmob].Mode==MOB_EMPTY)  pMobGrid[y][x]=0;
				else  
				SendCreateMob(conn,tmob,FALSE); 
			}
			if	(titem>0 && titem<MAX_ITEM) 
			{	if (pItem[titem].Mode==0) pItemGrid[y][x] = 0;
				else 
				SendCreateItem(conn,titem,FALSE); 
			}
		}
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////
//	좌표 GridMulticast	부하통제용
#define _do_multicast												\
		int tmob = pMobGrid[ty][tx];								\
		if  (tmob<=0 || tmob==skip || tmob>=MAX_USER)	continue;	\
		if  (pMob[tmob].Mode==MOB_EMPTY)				continue;	\
		pUser[tmob].cSock.AddMessage((char*)msg,msg->wPDULength+sizeof(HEADER));	\
		count++;if	(count>=max) return;
#define SAFEGRID	(MAX_GRIDX-g_iHalfGridX-1)
void	GridMulticast(int tx,int ty,MSG_STANDARD * msg,int skip,int max)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //	오류검사
	if	(msg==NULL)
	{	char temp[256];sprintf(temp,"err gridmulticast(point) null x:%d y:%d",tx,ty);Log(temp,"-system",0);
		return;
	}
	if	(max<=0||max>200)
	{	char temp[256];sprintf(temp,"err gridmulticast(point) max x:%d y:%d max:%d",tx,ty,max);Log(temp,"-system",0);
		return;
	}
	if	(tx<=g_iHalfGridX)	tx=g_iHalfGridX+1;
	if	(ty<=g_iHalfGridY)	ty=g_iHalfGridY+1;
	if	(tx>=SAFEGRID)	tx=SAFEGRID-1;
	if	(ty>=SAFEGRID)	ty=SAFEGRID-1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	골뱅이 선착순 max musticast
	int leng	= 1;
	int count	= 0;
	int i		= 0;

	int tmob = pMobGrid[ty][tx];							
	if  (tmob>0 && tmob!=skip && tmob<MAX_USER && pMob[tmob].Mode!=MOB_EMPTY)
	{	pUser[tmob].cSock.AddMessage((char*)msg,msg->wPDULength+sizeof(HEADER));
	}

	while(true)
	{	for	(i=0;i<leng;i++)	
		{	tx++;
			int tmob = pMobGrid[ty][tx];							
			if  (tmob<=0 || tmob==skip || tmob>=MAX_USER)	continue;
			if  (pMob[tmob].Mode==MOB_EMPTY)				continue;
			pUser[tmob].cSock.AddMessage((char*)msg,msg->wPDULength+sizeof(HEADER));
			count++;
			if	(count>=max) 
			return;
		}
		if	(leng>=g_iViewGridX) break;
		for	(i=0;i<leng;i++)
		{	ty++;
			int tmob = pMobGrid[ty][tx];							
			if  (tmob<=0 || tmob==skip || tmob>=MAX_USER)	continue;
			if  (pMob[tmob].Mode==MOB_EMPTY)				continue;
			pUser[tmob].cSock.AddMessage((char*)msg,msg->wPDULength+sizeof(HEADER));
			count++;
			if	(count>=max) 
			return;
		}
		leng++;
		for	(i=0;i<leng;i++)
		{	tx--;
			int tmob = pMobGrid[ty][tx];							
			if  (tmob<=0 || tmob==skip || tmob>=MAX_USER)	continue;
			if  (pMob[tmob].Mode==MOB_EMPTY)				continue;
			pUser[tmob].cSock.AddMessage((char*)msg,msg->wPDULength+sizeof(HEADER));
			count++;
			if	(count>=max) 
			return;
		}
		for	(i=0;i<leng;i++)
		{	ty--;
			int tmob = pMobGrid[ty][tx];							
			if  (tmob<=0 || tmob==skip || tmob>=MAX_USER)	continue;
			if  (pMob[tmob].Mode==MOB_EMPTY)				continue;
			pUser[tmob].cSock.AddMessage((char*)msg,msg->wPDULength+sizeof(HEADER));
			count++;
			if	(count>=max) 
			return;
		}
		leng++;
	};
}
/////////////////////////////////////////////////////////////////////////////////////////////
//	동선 GridMulticast	부하통제용
void  GridMulticast(int mob,int tx,int ty,MSG_STANDARD * msg, int max, BYTE byType)
{     
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //	오류검사
	if  (mob<=0	|| mob>=MAX_MOB)
	{   char temp[256];sprintf(temp,"err gridmulticast(line) mob:%d",mob);Log(temp,"-system",0);
	    return;
	} 
	if	(msg==NULL)
	{	char temp[256];sprintf(temp,"err gridmulticast(line) null mob:%d",mob);Log(temp,"-system",0);
		return;
	}
	if	(max<=0||max>200)
	{	char temp[256];sprintf(temp,"err gridmulticast(line) max mob:%d max:%d",mob,max);Log(temp,"-system",0);
		return;
	}
	//if	(tx<=g_iHalfGridX || ty<=g_iHalfGridY || tx>=SAFEGRID || ty>=SAFEGRID)//  전체 영역의 가장자리는 사용하지 않는다.
	//{	char temp[256];sprintf(temp,"err gridmulticast(line) position mob:%d max:%d x:%d y:%d",mob,max,tx,ty);Log(temp,"-system",0);
	//	return;
	//}
	int mobx	=	pMob[mob].TargetX;
	int moby	=	pMob[mob].TargetY;
	if	(mobx<0 || mobx>=MAX_GRIDX || moby<0 || moby>=MAX_GRIDY) 
	{	char temp[256];	sprintf(temp,"err gridmulticast(line) position mob:%d x:%d y:%d",mob,mobx,moby);
		Log(temp,"-system",0);
		return;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  자신의 이전 그리드를 삭제한다. 그리드가 다른 맙을 가지고 있으면 놔둔다.
	int currentgrid = pMobGrid[moby][mobx];
	if  (currentgrid!=mob && pMobGrid[moby][mobx]!=0) 
	{	char temp[256];	sprintf(temp,"err MOB grid not match, deleting mobgrid mob:%d grid:%d",mob,currentgrid);
		Log(temp,"-system",0);
		//MessageBox(NULL, "error_GRIDMUL1", "error", MB_OK);
	}
	pMobGrid[moby][mobx]=0;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  이동할 맙 그리드에 자신을 세팅한다.
	if  (pMobGrid[ty][tx]!=mob && pMobGrid[ty][tx]!=0) 
	{	char temp[256];	sprintf(temp,"err MOB grid not match, placing mobgrid mob:%d grid:%d",mob,pMobGrid[ty][tx]);
		Log(temp,"-system",0);
		//MessageBox(NULL, "error_GRIDMUL2", "error", MB_OK);
	}
	pMobGrid[ty][tx]=mob;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //     소스 릭트 설정.  (sx1,sx2,sy1,sy2)
	int sx1 = pMob[mob].TargetX - g_iHalfGridX; //23/2 = 11         -11 ~   +11
	int sy1 = pMob[mob].TargetY - g_iHalfGridY;
	int sx2 = sx1+g_iViewGridX;
	int sy2 = sy1+g_iViewGridY;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //     데스트 릭트 설정  (sx1,sx2,sy1,sy2)
	int dx1 = tx - g_iHalfGridX; //23/2 = 11         -11 ~   +11
	int dy1 = ty - g_iHalfGridY;
	int dx2 = dx1+g_iViewGridX;
	int dy2 = dy1+g_iViewGridY;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//	좌표영역 보정
	if(sx1<0) sx1=0;
	if(sy1<0) sy1=0;
	if(dx1<0) dx1=0;
	if(dy1<0) dy1=0;
	if(sx2>MAX_GRIDX) sx2=MAX_GRIDX-1; // #define SAFEGRID	(MAX_GRIDX-g_iHalfGridX-1)  1024-128-1
	if(sy2>MAX_GRIDX) sy2=MAX_GRIDX-1;
	if(dx2>MAX_GRIDX) dx2=MAX_GRIDX-1;
	if(dy2>MAX_GRIDX) dy2=MAX_GRIDX-1;

    //   Dest를 제외한 소스 영역에서 RemoveMob을 날린다.
	for (int y=sy1 ;y<sy2;y++)
	{	for (int x=sx1;x<sx2;x++)
		{	if	(x>=dx1 && x < dx2 && y>=dy1 && y < dy2) continue;

			int titem = pItemGrid[y][x];		//	Delete Item
			if  (titem>0 && titem<MAX_ITEM && pItem[titem].Mode!=0 && pItem[titem].ITEM.snIndex!=0 && mob<MAX_USER)
			{	SendRemoveItem(mob,titem,FALSE);
			}

			int tmob = pMobGrid[y][x];			//	Delete Mob
			if  (tmob==0 || tmob==mob ) continue;
			if	(tmob<MAX_USER)	
				SendRemoveMob(tmob,mob,0,0);
			if	(mob<MAX_USER)	
				SendRemoveMob(mob,tmob,0,0);   
		}
	}

	if(byType==ACTION_WARP)
	{	pMob[mob].TargetX=tx; pMob[mob].TargetY=ty;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//   소스를 제외한 Dest 영역에서 CreateMob을 날린다.
	for (   y=dy1 ;y<dy2;y++)
	{   for (int   x=dx1;x<dx2;x++)
		{	if  (x>=sx1 && x < sx2 && y>=sy1 && y < sy2) continue;
			// item
			int titem = pItemGrid[y][x];
			if  (titem>0 && titem<MAX_ITEM && pItem[titem].Mode!=0 && pItem[titem].ITEM.snIndex!=0 && mob<MAX_USER)
			{	SendCreateItem(mob,titem,FALSE);
			}
			// mob
			int tmob  = pMobGrid[y][x];
			if  (tmob==mob || tmob<=0 || tmob>=MAX_MOB) continue;// 자신이거나  맙이 없으면 처리할것 없음  .
			if	(pMob[tmob].Mode==MOB_EMPTY)
			{	pMobGrid[y][x]=0;
			 //   CloseUser(tmob);//fors_debug 瞳mob grid侶긋璟딜왕돨mob
				Log("err MOB GRID HAS EMPTY MOB","-system",0);
				continue;
			}
			if  (tmob>0 && tmob<MAX_USER)	SendCreateMob(tmob,mob,FALSE);  
   	   	    if	(mob>0 && mob<MAX_USER)		SendCreateMob(mob,tmob,FALSE);  
			 
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// 중앙. 이동 패킷
	int midx = (pMob[mob].TargetX+tx)/2;
	int midy = (pMob[mob].TargetY+ty)/2;
	//GridMulticast(midx,midy,msg,mob,max);
	GridMulticast(midx,midy,msg,mob,max);
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // MOB에게 최후 Action 정보를 저장한다.
	if(byType == ACTION_YUT)
	{
		pMob[mob].TargetX = tx;
		pMob[mob].TargetY = ty;
		return;
	}

	MSG_Action * act    = (MSG_Action*)msg;
	pMob[mob].LastTime  = act->dwClientTick;
	pMob[mob].LastSpeed = act->Speed;
	pMob[mob].LastX     = act->PosX;
    pMob[mob].LastY     = act->PosY;
	pMob[mob].TargetX = tx;
    pMob[mob].TargetY = ty;

	if(mob>0 && mob<MAX_USER && pMob[mob].m_byClan!=eTNClan_GM)
	{
		if(act->dwClientTick-pUser[mob].m_dwLastTickTime > 2000)	//	이전 거리체크시와 2초이상의 시간이 경과했을 경우(재체크)
		{
			int nDistanceX = pMob[mob].TargetX-pUser[mob].nPreX;
			int nDistanceY = pMob[mob].TargetY-pUser[mob].nPreY;
			int nDistance = (int)sqrt( (double)(nDistanceX*nDistanceX + nDistanceY*nDistanceY) ) ;
			//	if(nDistance > 추정가능최대이동거리) 스핵판정
			if((pMob[mob].m_iMoveSpeed<=5 && nDistance>25) || (pMob[mob].m_iMoveSpeed>5 && nDistance>40)) 
			{	
/*				char pSpeed[256] = {0,};
				sprintf(pSpeed, "Char:[%s] move Distance:%d per 4sec at speed:%d \r\n", pMob[mob].MOB.szName, nDistance, pMob[mob].m_iMoveSpeed);
				TimeWriteLog(pSpeed, ".\\Event\\[Log]Move.txt" );	*/						
				AddCrackError(mob, 10, CRACK_SPEED_HACK4); 
			}
			pUser[mob].nPreX = pMob[mob].TargetX;
			pUser[mob].nPreY = pMob[mob].TargetY;	
			pUser[mob].m_dwLastTickTime = act->dwClientTick;
		}
	}
}
//
////단지 Action에서만 사용된다.
//void  GridMulticast(int mob,int tx,int ty,MSG_STANDARD * msg/*, int Priority = 100*/)
//{     
//	int SizeX,SizeY,StartX,StartY;
//	int sx1,sy1,sx2,sy2;        // Source Rect
//    int dx1,dy1,dx2,dy2;        // Dest Rect
// 	if  (mob==0||pMob[mob].TargetX==0)
//	{   Log("err GridMulticast mobidx,pos","-system",0);
//	    return;
//	} 
//	int mobx	=	pMob[mob].TargetX;
//	int moby	=	pMob[mob].TargetY;
//	if	(mobx<0||mobx>=MAX_GRIDX||moby<0||moby>=MAX_GRIDY) return;
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //  자신의 이전 그리드를 삭제한다. 그리드가 다른 맙을 가지고 있으면 놔둔다.
//	int currentgrid = pMobGrid[moby][mobx];
//	if  (currentgrid!=mob && currentgrid!=0) 
//	{	  if (mob>=MAX_USER)   // 자신의 TargetX , TargetY에 자신이 없다. Player들은 중간 워프를 하므로 가능 mob은 불가
//		{  Log("NPC do not have his own grid","-system",0);
//		}  else
//        {  Log("PC do not have his own grid","-system",0);
//		}
//	    pMobGrid[moby][mobx]=0;
//	}   else 
//	{	 pMobGrid[moby][mobx]=0;
//	}
//    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //  이동할 맙 그리드에 자신을 세팅한다.
//  	if  (pMobGrid[ty][tx]!=mob && pMobGrid[ty][tx]!=0) 
//	{   if (mob>=MAX_USER)
//		{  Log("NPC charge other mob's grid","-system",0);
//		}  else 
//		{  Log("PC step in other mob's grid","-system",0);
//		}
//	    pMobGrid[ty][tx]=mob;
//	}   else
//	{   pMobGrid[ty][tx]=mob;
//	}
//
//    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //     소스 릭트 설정.  (sx1,sx2,sy1,sy2)
//	SizeY  = g_iViewGridY;
//    SizeX  = g_iViewGridX;
//    StartX = pMob[mob].TargetX - g_iHalfGridX; //23/2 = 11         -11 ~   +11
//    StartY = pMob[mob].TargetY - g_iHalfGridY;
//	if  (StartX+SizeX >= MAX_GRIDX)   {SizeX=SizeX-(StartX+SizeX-MAX_GRIDX);}
//	if  (StartY+SizeY >= MAX_GRIDY)   {SizeY=SizeY-(StartY+SizeY-MAX_GRIDY);}
//	if  (StartX<0)                    {StartX=0; SizeX=SizeX+StartX;}
//    if  (StartY<0)                    {StartY=0; SizeY=SizeY+StartY;}
//    sx1=StartX;
//    sy1=StartY;
//    sx2=StartX+SizeX;
//    sy2=StartY+SizeY;
//
//
//    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //     데스트 릭트 설정  (sx1,sx2,sy1,sy2)
//    SizeY  = g_iViewGridY;
//	SizeX  = g_iViewGridX;
//	StartX = tx - g_iHalfGridX; 
//	StartY = ty - g_iHalfGridY;
//	if  (StartX+SizeX >= MAX_GRIDX)   {SizeX=SizeX-(StartX+SizeX-MAX_GRIDX);}
//	if  (StartY+SizeY >= MAX_GRIDY)   {SizeY=SizeY-(StartY+SizeY-MAX_GRIDY);}
//	if  (StartX<0)                    {StartX=0; SizeX=SizeX+StartX;}
//    if  (StartY<0)                    {StartY=0; SizeY=SizeY+StartY;}
// 	dx1=StartX;
//	dy1=StartY;
//	dx2=StartX+SizeX;
//	dy2=StartY+SizeY;
//
//    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //   Dest를 제외한 소스 영역에서 RemoveMob을 날린다.
//	for (int y=sy1 ;y<sy2;y++)
//	{	for (int x=sx1;x<sx2;x++)
//		{
//			int tmob = pMobGrid[y][x];
//			if  (tmob==0 || tmob==mob) continue;
//			if  (msg&&tmob<MAX_USER) pUser[tmob].cSock.AddMessage((char*)msg,msg->wPDULength+sizeof(HEADER));// 쏘스 영역 전체 - 메시지가 있으면 멀티 케스팅 한다.
//			if	((x<dx1 || x >= dx2 || y<dy1 || y >= dy2)&&tx!=0) //  소스의 독자적인 부분
//			{   if	(tmob<MAX_USER)
//				{	SendRemoveMob(tmob,mob,0,0);   
//				}
//				if (mob<MAX_USER)
//				{	SendRemoveMob(mob,tmob,0,0);   
//				}
//			}
//		}
//	}
//
//	pMob[mob].TargetX = tx;
//	pMob[mob].TargetY = ty;
//
//    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //   소스를 제외한 Dest 영역에서 CreateMob을 날린다.
//	for (   y=dy1 ;y<dy2;y++)
//	{   for (int   x=dx1;x<dx2;x++)
//		{ 
//            int titem = pItemGrid[y][x];
//		    int tmob  = pMobGrid[y][x];
//
//            if  (x<sx1 || x >= sx2 || y<sy1 || y >= sy2)  // 데스트의 독자적인 부분.
//			{ 
//				//  item 생성
//				if  (titem>0 && titem<MAX_ITEM && pItem[titem].Mode!=0 && pItem[titem].ITEM.snIndex!=0 && mob<MAX_USER)  
//				{   if (pItem[titem].Mode==0) pItemGrid[y][x] = 0;
//				    else SendCreateItem(mob,titem,FALSE);
//				}
//                if  (tmob==mob||tmob==0) continue;// 자신이거나  맙이 없으면 처리할것 없음  .
//				if (pMob[tmob].Mode==MOB_EMPTY)
//				{  pMobGrid[y][x]=0;
//					Log("MOB GRID HAS EMPTY MOB","-system",0);
//					continue;
//				}
//				if  ( tmob<MAX_USER)  
//				{   if (pMob[mob].Mode==MOB_EMPTY)  pMobGrid[y][x]=0;
//				    else SendCreateMob(tmob,mob,FALSE);  
//				}
//   	   	        if  ( mob<MAX_USER)   
//				{	  if (pMob[tmob].Mode==MOB_EMPTY)  pMobGrid[y][x]=0;
//					else SendCreateMob(mob,tmob,FALSE);  
//				}
//				if (msg&&tmob<MAX_USER) 
//					pUser[tmob].cSock.AddMessage((char*)msg,msg->wPDULength+sizeof(HEADER));     //<< 새로운 지역의 mob에게 msg를 multicast
//
//				
//			} 
//			// else는 쏘스와 쳡치는 부분인데 위에서 처리 했다.
//		}
//	}
//    ////////////////////////////////////////////////////////////////////////////////////////////////////
//    // MOB에게 최후 Action 정보를 저장한다.
//	MSG_Action * act    = (MSG_Action*)msg;
//	pMob[mob].LastTime  = act->dwClientTick;
//	pMob[mob].LastSpeed = act->Speed;
//	pMob[mob].LastX     = act->PosX;
//    pMob[mob].LastY     = act->PosY;
//	pMob[mob].TargetX = tx;
//    pMob[mob].TargetY = ty;
//}


void SendAddParty(int target,int whom,int leader)
{    
	 if (target<=0 || target>=MAX_USER) return;

	 MSG_AddParty sm;
	 sm.nLeaderID		=  leader;
	 sm.wType			= _MSG_AddParty;
	 sm.wPDULength		= sizeof(sm)-sizeof(HEADER);
	 sm.Party.nID		= whom;
	 sm.Party.byLevel	= pMob[whom].MOB.byLevel;
	 sm.Party.nMaxHP	= pMob[whom].m_iMaxHP;
	 sm.Party.nCurHP	= pMob[whom].MOB.nHP;
	 sm.Party.nMaxTP	= pMob[whom].m_iMaxTP;
	 sm.Party.nCurTP	= pMob[whom].MOB.nTP;
	 sm.Party.nAffections	= pMob[whom].m_iAffections;
	 sm.Party.byRootingMode = pMob[whom].byRootingMode;
	 strcpy ( sm.Party.Name , pMob[whom].MOB.szName);

     pUser[target].cSock.AddMessage((char*)&sm,sizeof(sm));
}

void SendReqParty(int target, int leader)
{    
	if (target<=0 || target>=MAX_USER) return;
	 MSG_REQParty sm;
	 sm.wType = _MSG_REQParty;
	 sm.Leader.byLevel			= pMob[leader].MOB.byLevel; 
	 sm.Leader.nMaxHP			= pMob[leader].m_iMaxHP;
	 sm.Leader.nCurHP			= pMob[leader].MOB.nHP;
	 sm.Leader.nMaxTP			= pMob[leader].m_iMaxTP;
	 sm.Leader.nCurTP			= pMob[leader].MOB.nTP;
	 sm.Leader.nAffections		= pMob[leader].m_iAffections;
	 sm.Leader.nID      = leader;
	 sm.TargetID       = leader;
	 strcpy ( sm.Leader.Name , pMob[leader].MOB.szName);

     pUser[target].cSock.AddMessage((char*)&sm,sizeof(sm));
}

void SendRemoveParty(int target, int whom)
{
	int nLeader = pMob[target].Leader;
	if(nLeader==0) nLeader=target;

	MSG_RemoveParty sm; sm.nLeaderID = nLeader;
	sm.wType = _MSG_RemoveParty;  sm.nTargetID = whom;
	if ( 0 < target && target<MAX_USER) pUser[target].cSock.AddMessage((char*)&sm,sizeof(sm));
}

void SendUpdateParty(int Source)
{
	int leader = 0;
	S_SCP_RESP_UPDATE_PARTY	sm;	sm.wType = SCP_RESP_UPDATE_PARTY;
	sm.Party.byLevel		= pMob[Source].MOB.byLevel;
	sm.Party.nAffections	= pMob[Source].m_iAffections;
	strcpy(sm.Party.Name, pMob[Source].MOB.szName);
	sm.Party.nMaxHP			= pMob[Source].m_iMaxHP;
	sm.Party.nCurHP			= pMob[Source].MOB.nHP;
	sm.Party.nMaxTP			= pMob[Source].m_iMaxTP;
	sm.Party.nCurTP			= pMob[Source].MOB.nHP;
	sm.Party.nID			= Source;

	if(pMob[Source].Leader == 0)
	{	leader = Source;
	}	else
	{	leader = pMob[Source].Leader;
		if( 0 < leader && MAX_USER > leader )  pUser[leader].cSock.AddMessage((char*)&sm, sizeof(sm));
	}

	for(int i=0; i<MAX_PARTY;i++)
	{	int fol = pMob[leader].m_irgParty[i];
		if(fol<=0 || fol>=MAX_USER) pMob[leader].m_irgParty[i]=0;	//	파티원리스트에 알수없는 값이 들어있을 경우 초기화한다.
		if(fol == 0 || pUser[fol].Mode!=USER_PLAY) continue;		//	비어있거나 플레이상태가 아닐경우
		if(fol == Source) continue;									//	자신에게는 업데이트를 보낼필요가 없다.
		pUser[fol].cSock.AddMessage((char*)&sm, sizeof(sm));
	}
}

void SendPartyMessage(int nPartyLeader, MSG_STANDARD* msg)
{	int nMember=0;
	int nCount = 0;

	for(int i=0; i<MAX_PARTY; i++)
	{	nMember=pMob[nPartyLeader].m_irgParty[i];
		if(nMember==0 || pUser[nMember].Mode!=USER_PLAY) continue;
		if( nMember == nPartyLeader ) continue ;
		if( 0 >= nMember || MAX_USER <= nMember) continue ;
		nCount++;
	}

	if(nCount==0) return;				//	파티원이 없을경우

	pUser[nPartyLeader].cSock.SendOneMessage((char*)msg, (msg->wPDULength)+sizeof(HEADER));
	for(int i=0; i<MAX_PARTY; i++)
	{	nMember=pMob[nPartyLeader].m_irgParty[i];
		if(nMember==0 || pUser[nMember].Mode!=USER_PLAY) continue;
		if( nMember == nPartyLeader ) continue ;
		if( 0 >= nMember || MAX_USER <= nMember) continue ;
		pUser[nMember].cSock.SendOneMessage((char*)msg, (msg->wPDULength)+sizeof(HEADER));
	}
}

void SendGuildMessage(int nGuildIndex, MSG_STANDARD* pMsg)
{
	int nMember=0;
	for (int i=0;i<MAX_GUILD_MEMBER;i++)
	{   nMember=pGuild[nGuildIndex].pMemberIndex[i];
		if (nMember<=0 || nMember>=MAX_USER || pUser[nMember].Mode!=USER_PLAY) continue; 
		pUser[nMember].cSock.SendOneMessage((char*)pMsg,(pMsg->wPDULength)+sizeof(HEADER)); 
	}

 	return;
}

void SendGuildChat(int conn,int gid,char * str,unsigned char bg,unsigned char text)
{
	//if	(conn<=0 || conn>=MAX_USER || pUser[conn].Mode!=USER_PLAY)	return;
	//S_SCP_NOTIFY_BROADCAST sm; sm.wType =SCP_NOTIFY_BROADCAST;
	//sm.wPDULength	= sizeof(sm)-sizeof(HEADER);
	//sm.byMsgType	= 1;		//	파티(0), 길드(1), 존(2), 월드(3), 게임(4)	
	//sm.byBgColor	= bg;		// 채팅 메세지 배경색                                              
	//sm.byTextColor	= text;		// 채팅 메세지 글자색  
	//strncpy(sm.szName, pMob[conn].MOB.szName, SZNAME_LENGTH); 
	//strncpy(sm.szMsg,  str, MAX_NOTIFY_LENGTH);
	//int sz = sizeof(sm); int user=0;
	//for	(int i=0;i<MAX_GUILD_MEMBER;i++)
	//{	user = pGuild[gid].pMemberIndex[i];
	//	if(user<=0||user>=MAX_USER||pUser[user].Mode!=USER_PLAY)	continue;
	//	pUser[user].cSock.AddMessage((char*)&sm,sz);
	//}
}

void SendGuildInfo(int conn,int nGuildIndex)
{
	MSG_GuildInfo sm; sm.wType=_MSG_GuildInfo;
	if(nGuildIndex==-1) 
	{	sm.GuildID=-1; 
		pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(sm)); return; 
	}

	sm.GuildID = pGuild[nGuildIndex].GUILD.GuildID;
	sm.Mark = pGuild[nGuildIndex].GUILD.Mark;
	sm.dwTime[0] = pGuild[nGuildIndex].GUILD.dwTime[0];
	sm.dwTime[1] = pGuild[nGuildIndex].GUILD.dwTime[1];
	sm.dwTime[2] = pGuild[nGuildIndex].GUILD.dwTime[2];
	sm.byCargoLevel[0] = pGuild[nGuildIndex].GUILD.byCargoLevel[0];
	sm.byCargoLevel[1] = pGuild[nGuildIndex].GUILD.byCargoLevel[1];
	sm.byCargoLevel[2] = pGuild[nGuildIndex].GUILD.byCargoLevel[2];

	strncpy(sm.GuildName, pGuild[nGuildIndex].GUILD.GuildName, SZNAME_LENGTH);
	strncpy(sm.GuildMessage, pGuild[nGuildIndex].GUILD.GuildMessage, GUILDMESSAGE_LENGTH);
	strncpy(sm.AlliedGuildName1, pGuild[nGuildIndex].GUILD.AlliedGuildName1, SZNAME_LENGTH);
	strncpy(sm.AlliedGuildName2, pGuild[nGuildIndex].GUILD.AlliedGuildName2, SZNAME_LENGTH);
	strncpy(sm.EnemyGuildName1, pGuild[nGuildIndex].GUILD.EnemyGuildName1, SZNAME_LENGTH);
	memcpy(sm.Member, pGuild[nGuildIndex].GUILD.Member, sizeof(STRUCT_GUILD_MEMBER)*MAX_GUILD_MEMBER);

	pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(sm));
}

void SendItemDisappear(int tx, int ty, int nID, int nMOBID)
{
	if(nMOBID<0 || nMOBID>=MAX_USER) return;
	S_SCP_MAP_ITEM_DISAPPEAR itemdisappear;
	itemdisappear.wType = SCP_MAP_ITEM_DISAPPEAR;
	itemdisappear.wPDULength = sizeof(S_SCP_MAP_ITEM_DISAPPEAR)-sizeof(HEADER);
	itemdisappear.nItemID = nID; 
	if(nMOBID>0) strncpy(itemdisappear.szName, pMob[nMOBID].MOB.szName, SZNAME_LENGTH);
	else ZeroMemory(itemdisappear.szName, SZNAME_LENGTH);

	GridMulticast(tx,ty,(MSG_STANDARD *)&itemdisappear,0,100);

	pItemGrid[ty][tx]	= 0;
	pItem[nID].Mode		= 0;
}

void SendHpMode(int conn)
{
	/*
     MSG_SetHpMode sm;
     sm.Type = _MSG_SetHpMode; sm.Size=sizeof(sm);
     sm.ID = conn;  sm.Hp =pMob[conn].MOB.CurrentScore.Hp;
	 sm.Mode = pUser[conn].Mode;
     pUser[conn].cSock.AddMessage((char *)&sm,sm.Size);
	 */
}

void SendStrongHoldData(int conn)
{
    Msg_StrongHoldInit sm; 
    sm.wType = _Msg_StrongHoldInit; 
	for(int i=0; i<eStronghold_MaxCount; i++)
	{
		strncpy(sm.szGuildName[i], g_krgStronghold[i].szGuildName, SZGUILD_LENGTH);
		sm.dwMark[i] = g_krgStronghold[i].dwMark;
	}
    pUser[conn].cSock.SendOneMessage((char *)&sm,sizeof(sm));
}

void SendCastleData(int iHandle)
{
    Msg_CastleInit sm; 
    sm.wType = _Msg_CastleInit; 
	sm.iCastleOwner = g_iCastleOwner;

    pUser[iHandle].cSock.SendOneMessage((char *)&sm,sizeof(sm));
}

void SendWhoMessage(int conn) //fors_debug msg_here 1
{
	Msg_Who sm;	ZeroMemory(&sm, sizeof(sm));
	sm.wType = _Msg_Who; sm.wPDULength = sizeof(sm)-sizeof(HEADER);
	memcpy(&sm.wDummy, pUser[conn].cSock.pRecvBuffer, sizeof(sm.pszPassword));
	sm.applytime = 0;
	sm.byteLevel=0;
	sm.skillid=0;
	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));

	pUser[conn].cSock.m_byWhoCount = 20;
}

bool RecvWhoMessage(int conn, char* pWho)
{
	
	if(pUser[conn].cSock.m_iWhoTick==0)
	{
		return false;
	}

	if(memcmp(pWho, pUser[conn].cSock.m_pszWho, sizeof(pUser[conn].cSock.m_pszWho))==0) 
	{
		pUser[conn].cSock.m_iWhoTick = 0;
		ZeroMemory(pUser[conn].cSock.m_pszWho, sizeof(pUser[conn].cSock.m_pszWho));

		return true;
	}

	return false;
}

void SendQuiz(int conn, int nQuiz)
{
	if(conn<=0 || conn>=MAX_USER || pUser[conn].Mode!= USER_PLAY) return;

	int nQuizIndex = nQuiz;
	if(nQuizIndex == 0)
	{
		int nMaxQuiz = g_Config.GetMaxQuiz();
		if(nMaxQuiz>0 && nMaxQuiz<MAX_QUIZCOUNT) 
		{
			nQuizIndex = CurrentTime % nMaxQuiz;
			if(nQuizIndex == 0) nQuizIndex = nMaxQuiz;
		}
		else
			return;		//	데이터가 없을 경우 실행되지 않는다(nMaxQuiz == 0)
	}

	DWORD dwLimitTime = g_Config.GetQuizCount()*1000;

	Msg_Quiz sm; ZeroMemory(&sm, sizeof(sm));
	sm.wType = _Msg_Quiz;
	g_Config.GetQuiz(nQuizIndex, &sm, &pUser[conn].m_dwQuiz);
	pUser[conn].m_dwQuizCount = CurrentTime + dwLimitTime;

	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
}

void BroadCastTrimuritiSelection(int conn)
{
	MSG_Broadcast sm; sm.wType = _MSG_Broadcast;
	sm.wPDULength = sizeof(MSG_Broadcast) - sizeof(HEADER);
	sm.byBgColor		= 14;			    // 채팅 메세지 배경색
	sm.byTextColor		= 14;			    // 채팅 메세지 배경색
	sm.byMsgType		= MESSAGE_ZONE;
	sm.byTrimuriti		= pMob[conn].MOB.byTrimuriti;

	char pTri[16] = {0,};
	if(pMob[conn].MOB.byTrimuriti==eTNClan_Brahma) sprintf(pTri, g_pMessageStringTable[_Brahma]);
	if(pMob[conn].MOB.byTrimuriti==eTNClan_Vishnu) sprintf(pTri, g_pMessageStringTable[_Vishnu]);
	if(pMob[conn].MOB.byTrimuriti==eTNClan_Siva) sprintf(pTri, g_pMessageStringTable[_Siva]);
	sprintf(sm.szMsg, g_pMessageStringTable[_Change_Trimuriti], pMob[conn].MOB.szName, pTri);
	SendToAll((MSG_STANDARD*)&sm);		//	존내에 주신선택을 공지한다.

	MSG_TrimuritySelect nm; nm.wType = _MSG_TrimuritySelect;
	nm.wPDULength = sizeof(MSG_TrimuritySelect) - sizeof(HEADER);
	nm.byType = 1;	nm.byTrimuriti = pMob[conn].MOB.byTrimuriti;
	strncpy(nm.CharName, pMob[conn].MOB.szName, SZNAME_LENGTH);
	nm.dwMoney = pMob[conn].MOB.nRupiah;
	SendToAll((MSG_STANDARD*)&nm);		//	존내에 주신선택을 알린다.

	pMob[conn].m_byBramanRank = 0;
	pMob[conn].CheckCaste();
	pMob[conn].CalCasteSkillPoint();
}

void SendTrimuritiCount(int conn)
{
	MSG_TrimuritiCount sm; ZeroMemory(&sm, sizeof(sm));
	sm.wType = _MSG_TrimuritiCount;
	sm.dwBrahma = g_iBrahmaCount;
	sm.dwVishunu = g_iVishnuCount;
	sm.dwSiva = g_iSivaCount;
	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
}

void SendYutBroadcast(short snX, short snY, int iNPC, int iMsg)
{
	if(iMsg<0 || iMsg>=400) return;

	MSG_Broadcast sm; sm.wType = _MSG_Broadcast;						//	존내 전광판공지
	sm.byMsgType = MESSAGE_POSTTOWORLD;
	sm.byTextColor = 12;
	sm.wPDULength = sizeof(MSG_Broadcast) - sizeof(HEADER);
	strncpy(sm.szMsg, g_pMessageStringTable[iMsg], sizeof(sm.szMsg));
	strncpy(sm.szName, g_pMessageStringTable[_YutNPCName], sizeof(sm.szName)); 
	SendToAll((MSG_STANDARD*)&sm);

	S_SCP_NOTIFY_CHAT nm;	nm.wType = SCP_NOTIFY_CHAT;					//	NPC Chat
	nm.wPDULength = sizeof(S_SCP_NOTIFY_CHAT) - sizeof(HEADER);
	nm.nID=10000+iNPC;													//	NPC + 10000(NPC의 경우 +10000하기로함)
	nm.byTextColor=12; nm.byBgColor = 0; nm.byTrimuriti=0;				//	차후 정해지면 변경
	nm.byWhere = eTNSpchLoc_All;
	strncpy(nm.szMsg, g_pMessageStringTable[iMsg], sizeof(nm.szMsg));
	GridMulticast(snX, snY, (MSG_STANDARD*)&nm, 0, 200);
}

void SendScriptQuestHistory(int conn, int nNPC)
{
	Msg_ScriptQuest sm; sm.wType = _Msg_ScriptQuest;
	sm.nNPCID = nNPC; sm.nTime = pUser[conn].m_dwQuestClearData;
	sm.byLevel = pUser[conn].m_byQuestLevel;
	sm.snQuestID = pUser[conn].m_snQuestID;
	memcpy(sm.byKill, pUser[conn].m_byQuestKill, sizeof(sm.byKill));
	pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(sm));
}