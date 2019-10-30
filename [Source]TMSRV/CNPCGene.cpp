#include <stdlib.h>
#include <stdio.h>
#include "CNPCGene.h"
#include "Basedef.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

extern HWND hWndMain;

BOOL ReadMob(STRUCT_MOB * mob,char * Directory);

CNPCGenerator::CNPCGenerator()
{     
    NumList =0;
	memset(pList,0,sizeof(NPCGENLIST)*MAX_NPCGENERATOR);
}
CNPCGenerator::~CNPCGenerator()
{
}

CNPCSummon::CNPCSummon()
{     
}
CNPCSummon::~CNPCSummon()
{
}

void CNPCSummon::Initialize(void)
{   BOOL ret = 0;
	BASE_InitModuleDir();


}


void CNPCGenerator::VerifyData()
{
	for( int iIdx = 0; iIdx < MAX_NPCGENERATOR; ++iIdx )
	{
		for( int i = 1; i < MAX_SEGMENT; ++i )
		{
			if( (0 >= pList[iIdx].SegmentListX[i]) || (0 >= pList[iIdx].SegmentListY[i]) ) pList[iIdx].SegmentListY[i] = pList[iIdx].SegmentListY[i-1];
		}
	}
}

//#define REWRITE 1

BOOL CNPCGenerator::ReadNPCGenerator(void)
{
	/////////////////////////////////////////////////////  NPC제네레이터 로딩  汎

	//memset(pList,0,sizeof(pList));
//#ifdef REWRITE
//     FILE *wfp; wfp=fopen("NPCGener.new.txt","wt"); 
//#endif

	FILE *fp; fp=fopen("NPCGener.txt","rt");
	if (fp==NULL) {MessageBox(hWndMain,"NPCGener.txt가 없습니다.","초기화 실패",NULL);return FALSE;}
	char temp[256];
	int i=-1;
	while(1)
	{	char * ret = fgets((char*)temp,255,fp);
		if (ret==NULL) break;
		#ifdef REWRITE
		if	(temp[0]=='/') 
		{   char temp1[256]; char temp2[256]; temp1[0]=0;temp2[0]=0;
			sscanf(temp,"%s %s",temp1,temp2);
			if (temp2[0]==0) continue;	
			//if (temp2[0]!=0&&temp2[0]!='*') fprintf(wfp,"\n\n%s",temp);
			continue;
		}
		#endif
		if	(temp[0]=='#')
		{	i++; 
			for (int k=0;k<MAX_SEGMENT;k++)
			{   pList[i].SegmentListX[k]=0;
				pList[i].SegmentListY[k]=0;
			}
			//#ifdef REWRITE
			//fprintf(wfp,"// ********************************************\n");
			//if (temp[1]=='*')	fprintf(wfp,"#*	[%4d]\n",i); 
			//else				fprintf(wfp,"#	[%4d]\n",i); 
			//#endif
	  		continue;
		}
		if (temp[0]==13) continue;
		int rrr = ParseString(i,temp);
		//#ifdef REWRITE
		//if	(rrr)
		//{	char temp1[256]; char temp2[256]; temp1[0]=0;temp2[0]=0;
		//	sscanf(temp,"%s %s",temp1,temp2);
		//	int len1=strlen(temp1);
		//	if (len1<=8)  fprintf(wfp,"	%s		%s\n",temp1,temp2);
		//	else		  fprintf(wfp,"	%s	%s\n",temp1,temp2);
		//}
		//#endif

	   //if (i<0||i>=MAX_NPCGENERATOR) {MessageBox(hWndMain,"NPCGener.txt 파일 오류","초기화 실패",NULL); return 0;}
	};
	NumList = i;
	fclose(fp);
//#ifdef REWRITE
//	fclose(wfp);
//#endif

	return TRUE;
}


void SetAct(char * dest,char * act)
{
	if  (strlen(act)>=79) {MessageBox(hWndMain,act,"NPC Generater's Action can't be larger than 80.",NULL);return;}
    strcpy(dest,act);
}

BOOL CNPCGenerator::ParseString(int i,char * str)
{
	
	 char str1[128];str1[0]=0;
	 char str2[128];str2[0]=0;
	 char str3[128];str3[0]=0;
	 str1[0]=0;
	 str2[0]=0;
	 int  value=0;
	 int secondvalue=0;
	 sscanf(str,"%s %s %s",str1,str2,str3);
	 if (str1[0]=='/') return FALSE;
	 if (str1[0]==0) return FALSE;
	 value = atoi(str2);
	 secondvalue = atoi(str3);

	 if(strlen(str2)>SZNAME_LENGTH) return FALSE;

	 ///////////////////////////////////////////  기본 생성 정보  /////////////////////////////////////////////////////////////////////
	 if (!strcmp(str1,"CheckFrequency:")){  pList[i].MinuteGenerate  = value;		}  else
     if (!strcmp(str1,"Group:")) 	 {  pList[i].iGroup              = value;		}  else  	 	 
	 if (!strcmp(str1,"Monster0:")) 
	 {	
		 if (!strcmp(str2,"0")) return false ;
		 strcpy( pList[i].krgMonsterList[0].kMobData.szName,str2);
	    BOOL ret = ReadMob(&pList[i].krgMonsterList[0].kMobData, "npc");    	
		if (ret==FALSE) MessageBox(hWndMain,str2,"Can't read NPC file in NPCGener.txt",NULL);
		else
		{
			pList[i].krgCommand[0].iCommand = eCmd_PopMonster ;
			pList[i].krgCommand[0].iIndex = 0 ;
		}
	 }  else
	 if (!strcmp(str1,"MaxPopCnt0:"))     {  pList[i].krgMonsterList[0].iMaxPopCount = value; if( 10 < pList[i].krgMonsterList[0].iMaxPopCount ) pList[i].krgMonsterList[0].iMaxPopCount = 10 ; }  else
	 if (!strcmp(str1,"PopCntPerTime0:"))  	 {  pList[i].krgMonsterList[0].iPopCountPerTime = value;       }  else
     if (!strcmp(str1,"Monster1:")) 
     {	
		 if (!strcmp(str2,"0")) return false ;
		 strcpy(pList[i].krgMonsterList[1].kMobData.szName, str2);	 
 	    BOOL ret = ReadMob(&pList[i].krgMonsterList[1].kMobData, "npc");   
		if (ret==FALSE) MessageBox(hWndMain,str2,"Can't read NPC file in NPCGener.txt",NULL);
		else
		{
			pList[i].krgCommand[1].iCommand = eCmd_PopMonster ;
			pList[i].krgCommand[1].iIndex = 1 ;
		}
	 }  else 
	 if (!strcmp(str1,"MaxPopCnt1:"))     {  pList[i].krgMonsterList[1].iMaxPopCount = value; if( 10 < pList[i].krgMonsterList[1].iMaxPopCount ) pList[i].krgMonsterList[1].iMaxPopCount = 10 ;      }  else
	 if (!strcmp(str1,"PopCntPerTime1:"))  	 {  pList[i].krgMonsterList[1].iPopCountPerTime = value;       }  else
     if (!strcmp(str1,"Monster2:")) 
     {	
		 if (!strcmp(str2,"0")) return false ;
		 strcpy(pList[i].krgMonsterList[2].kMobData.szName, str2);	 
 	    BOOL ret = ReadMob(&pList[i].krgMonsterList[2].kMobData, "npc");   
		if (ret==FALSE) MessageBox(hWndMain,str2,"Can't read NPC file in NPCGener.txt",NULL);
		else
		{
			pList[i].krgCommand[2].iCommand = eCmd_PopMonster ;
			pList[i].krgCommand[2].iIndex = 2 ;
		}
	 }  else 
	 if (!strcmp(str1,"MaxPopCnt2:"))     {  pList[i].krgMonsterList[2].iMaxPopCount = value; if( 10 < pList[i].krgMonsterList[2].iMaxPopCount ) pList[i].krgMonsterList[2].iMaxPopCount = 10 ;      }  else
	 if (!strcmp(str1,"PopCntPerTime2:"))  	 {  pList[i].krgMonsterList[2].iPopCountPerTime = value;       }  else
     if (!strcmp(str1,"Monster3:")) 
     {	
		 if (!strcmp(str2,"0")) return false ;
		 strcpy(pList[i].krgMonsterList[3].kMobData.szName, str2);	 
 	    BOOL ret = ReadMob(&pList[i].krgMonsterList[3].kMobData, "npc");   
		if (ret==FALSE) MessageBox(hWndMain,str2,"Can't read NPC file in NPCGener.txt",NULL);
		else
		{
			pList[i].krgCommand[3].iCommand = eCmd_PopMonster ;
			pList[i].krgCommand[3].iIndex = 3 ;
		}
	 }  else 
	 if (!strcmp(str1,"MaxPopCnt3:"))     {  pList[i].krgMonsterList[3].iMaxPopCount = value;if( 10 < pList[i].krgMonsterList[3].iMaxPopCount ) pList[i].krgMonsterList[3].iMaxPopCount = 10 ;       }  else
	 if (!strcmp(str1,"PopCntPerTime3:"))  	 {  pList[i].krgMonsterList[3].iPopCountPerTime = value;       }  else
     if (!strcmp(str1,"Monster4:")) 
     {	
		 if (!strcmp(str2,"0")) return false ;
		 strcpy(pList[i].krgMonsterList[4].kMobData.szName, str2);	 
 	    BOOL ret = ReadMob(&pList[i].krgMonsterList[4].kMobData, "npc");   
		if (ret==FALSE) MessageBox(hWndMain,str2,"Can't read NPC file in NPCGener.txt",NULL);
		else
		{
			pList[i].krgCommand[4].iCommand = eCmd_PopMonster ;
			pList[i].krgCommand[4].iIndex = 4 ;
		}
	 }  else 
	 if (!strcmp(str1,"MaxPopCnt4:"))     {  pList[i].krgMonsterList[4].iMaxPopCount = value; if( 10 < pList[i].krgMonsterList[4].iMaxPopCount ) pList[i].krgMonsterList[4].iMaxPopCount = 10 ;      }  else
	 if (!strcmp(str1,"PopCntPerTime4:"))  	 {  pList[i].krgMonsterList[4].iPopCountPerTime = value;       }  else
     if (!strcmp(str1,"Monster5:")) 
     {	
		 if (!strcmp(str2,"0")) return false ;
		 strcpy(pList[i].krgMonsterList[5].kMobData.szName, str2);	 
 	    BOOL ret = ReadMob(&pList[i].krgMonsterList[5].kMobData, "npc");   
		if (ret==FALSE) MessageBox(hWndMain,str2,"Can't read NPC file in NPCGener.txt",NULL);
		else
		{
			pList[i].krgCommand[5].iCommand = eCmd_PopMonster ;
			pList[i].krgCommand[5].iIndex = 5 ;
		}
	 }  else 
	 if (!strcmp(str1,"MaxPopCnt5:"))     {  pList[i].krgMonsterList[5].iMaxPopCount = value; if( 10 < pList[i].krgMonsterList[5].iMaxPopCount ) pList[i].krgMonsterList[5].iMaxPopCount = 10 ;       }  else
	 if (!strcmp(str1,"PopCntPerTime5:"))  	 {  pList[i].krgMonsterList[5].iPopCountPerTime = value;       }  else

     ////////////////////////////////////////////  라우팅 정보   /////////////////////////////////////////////////////////////////////////
  	 if (!strcmp(str1,"RouteType:")) 	 {  pList[i].RouteType       = value;		}  else
  	 if (!strcmp(str1,"Formation:")) 	 {  pList[i].Formation       = value;		}  else  	 
  	 //
 	 if (!strcmp(str1,"Segment0Range:")) 	 {  pList[i].SegmentRange[0] = value;		}  else
	 if (!strcmp(str1,"Segment0X:"))  	     {  pList[i].SegmentListX[0] = value;       }  else
	 if (!strcmp(str1,"Segment0Y:")) 	     {  pList[i].SegmentListY[0] = value;       }  else
     if (!strcmp(str1,"Segment0Wait:"))     {  pList[i].SegmentWait[0]  = value;       }  else
        //
	 if (!strcmp(str1,"Segment1Range:")) {  pList[i].SegmentRange[1] = value;		}  else
	 if (!strcmp(str1,"Segment1X:"))     {  pList[i].SegmentListX[1] = value;		}  else
	 if (!strcmp(str1,"Segment1Y:"))     {  pList[i].SegmentListY[1] = value;		}  else
     if (!strcmp(str1,"Segment1Wait:"))  {  pList[i].SegmentWait[1]  = value;		}  else
     //
	 if (!strcmp(str1,"Segment2Range:")) {  pList[i].SegmentRange[2] = value;		}  else
	 if (!strcmp(str1,"Segment2X:"))     {  pList[i].SegmentListX[2] = value;		}  else
	 if (!strcmp(str1,"Segment2Y:"))     {  pList[i].SegmentListY[2] = value;		}  else
     if (!strcmp(str1,"Segment2Wait:"))  {  pList[i].SegmentWait[2]  = value;		}  else
     //
	 if (!strcmp(str1,"Segment3Range:")) {  pList[i].SegmentRange[3] = value;		}  else
	 if (!strcmp(str1,"Segment3X:"))     {  pList[i].SegmentListX[3] = value;		}  else
	 if (!strcmp(str1,"Segment3Y:"))     {  pList[i].SegmentListY[3] = value;		}  else
     if (!strcmp(str1,"Segment3Wait:"))  {  pList[i].SegmentWait[1]  = value;		}  else
     //
	 if (!strcmp(str1,"Segment4Range:")) 	 {  pList[i].SegmentRange[4] = value;		}  else
	 if (!strcmp(str1,"Segment4X:"))  	     {  pList[i].SegmentListX[4] = value;		}  else
	 if (!strcmp(str1,"Segment4Y:")) 	     {  pList[i].SegmentListY[4] = value;		}  else
     if (!strcmp(str1,"Segment4Wait:"))      {  pList[i].SegmentWait[4]  = value;		}  else
     ///////////////////////////////////////////////////////// MOB FILE LOAD /////////////////////////////////////////////////////////////////
	 {  //MessageBox(hWndMain,str,"Can't parse string in NPCGener.txt",NULL);
	    return FALSE;
	 }

	 if( (5 == pList[i].RouteType) || (6 == pList[i].RouteType) || (7 == pList[i].RouteType) || (9 == pList[i].RouteType) ) pList[i].RouteType = eTNRout_MoveNRoam ;
	 if( (eTNRout_MoveNRoam > pList[i].RouteType) || (eTNRout_FixPosition < pList[i].RouteType) ) pList[i].RouteType = eTNRout_MoveNRoam ;
	 

	 return TRUE;
     ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


void CNPCGenerator::RebuildAreaData()
{
    for( int i = 0 ; i <= NumList ; ++i )
    {
        if( eCmd_PopMonster == pList[i].krgCommand[0].iCommand ) pList[i].krgCommand[0].iCount = pList[i].krgMonsterList[0].iPopCountPerTime ;
		if( eCmd_PopMonster == pList[i].krgCommand[1].iCommand ) pList[i].krgCommand[1].iCount = pList[i].krgMonsterList[1].iPopCountPerTime ;
    }
   
}
