#include <windows.h>
#include <stdio.h>
#include "CGuild.h"
#include "TNDebug.h"
#include "server.h"

//int GetGuild(int GuildID, bool bFlag=true);
//int	ReadGuildFile(int GuildID, STRUCT_GUILD * stGuild);

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__



extern CGuild pGuild[MAX_USER];

int GetGuildID(char* pName)
{
	if(strlen(pName)>GUILDNAME_LENGTH) return -1;

	int nID=0; char temp[256] = {0,};
	char guilfile[256]; sprintf(guilfile,"G:\\name\\%s.dat", pName);
	FILE * fp=fopen(guilfile,"rt"); 
	if(fp==NULL) 
	{	sprintf(temp,"err GetGuildID:[%s]", pName);
		Log(temp,"-system",0); return -1;
	}
	fscanf(fp,"%d",&nID);
	fclose(fp);

	sprintf(temp,"GetGuildID:[%s] ID:%d", pName, nID);
	Log(temp,"-system",0);

	return nID;
}

int GetGuild(int GuildID, bool bFlag)
{
	// 이미 GuildIndex기등록되어 있는지
	if	(GuildID==0) return 0;
	int empty = -1;
	for	(int i=1;i<MAX_USER;i++)
	{
		if	(pGuild[i].GUILD.GuildID==GuildID) 
		{	//	길드마스터(길드마크포함)가 사라지는 문제발생
			pGuild[i].CheckGuildMaster();

			return i;
		}
		if	(pGuild[i].Mode==GUILD_EMPTY) empty = i;
	}
	if	(empty==-1)
	{	// unhandled error	
		return 0;
	}

	if(!bFlag) return GUILD_EMPTY;
	if(!ReadGuildFile(GuildID, &pGuild[empty])) return -1;
	
	return empty;
}

int	ReadGuildFile(int GuildID, CGuild* pstGuild)
{	
	if(pstGuild==0) FALSE;

	pstGuild->Initialize();

	char file[256];
	sprintf(file,"G:\\%7.7d.dat",GuildID);
	FILE * fp = fopen(file,"rb");	
	if	(fp==NULL) return FALSE;
	fread(&(pstGuild->GUILD),sizeof(STRUCT_GUILD),1,fp);
	fclose(fp);

#ifdef __LOG_GUILD__
	char chBuf[2048] = { 0,0,0, } ;
	sprintf(chBuf, "[ReadGuildFile] GuildID:%d GuildMark:%d GuildMembers : \r\n", GuildID, pstGuild->GUILD.Mark);
	for(int i=0; i<MAX_GUILD_MEMBER; i++)
	{	if(pstGuild->GUILD.Member[i].MemberName[0] == 0) continue;
		if(pstGuild->GUILD.Member[i].GuildRank == eGuildMaster)
		{	strncpy(pstGuild->szGuildMaster, pstGuild->GUILD.Member[i].MemberName, SZNAME_LENGTH);
		}
		char chData[128] = {0,0,0, };
		sprintf(chData, "%s %d    ", pstGuild->GUILD.Member[i].MemberName, pstGuild->GUILD.Member[i].GuildRank);
		strcat(chBuf, chData);
	}

	char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
	TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
#else
	for(int i=0; i<MAX_GUILD_MEMBER; i++)
	{	if(pstGuild->GUILD.Member[i].MemberName[0] == 0) continue;
		if(pstGuild->GUILD.Member[i].GuildRank == eGuildMaster)
		{	strncpy(pstGuild->szGuildMaster, pstGuild->GUILD.Member[i].MemberName, SZNAME_LENGTH);
		}
	}
#endif	//	#ifdef __LOG_GUILD__

	pstGuild->Mode = GUILD_CHARGED;
	pstGuild->nAlliedID = GetGuildID(pstGuild->GUILD.AlliedGuildName1);

	return TRUE;
}

int IsGuildMemberIn(int nGuildID)
{
	for(int nIndex=0; nIndex<MAX_USER; nIndex++)
	{	if(pGuild[nIndex].Mode!= GUILD_CHARGED) continue;
		if(pGuild[nIndex].GUILD.GuildID==nGuildID) return nIndex;
	}

	return 0;
}

/////////////////////////////    Class Function   //////////////////////////
CGuild::CGuild()
{
	memset(&GUILD,0,sizeof(STRUCT_GUILD));
	memset (pMemberIndex,0,sizeof(pMemberIndex));
	memset (szGuildMaster,0,sizeof(szGuildMaster));
	Mode = 0;
}
CGuild::~CGuild()
{
}

void CGuild::Initialize()
{
	memset(&GUILD,0,sizeof(STRUCT_GUILD));
	memset (pMemberIndex,0,sizeof(pMemberIndex));
	memset(szGuildMaster,0,sizeof(szGuildMaster));
	Mode = 0;
	nAlliedID = 0;
}

int CGuild::GetEmptyGuild()
{	int empty = 0;
	for	(int i=1;i<MAX_USER;i++)
	{
		if(pGuild[i].Mode==GUILD_EMPTY) { empty=i; break; }
	}

	return empty;
}

bool CGuild::IsGuildManager( char* a_szName )
{
	if( NULL == a_szName ) return false;
	for( int i = 0 ; i < MAX_GUILD_MEMBER; ++i )
	{
		if( eGuildSubMaster <= GUILD.Member[i].GuildRank )
		{
			if( 0 == strcmp( GUILD.Member[i].MemberName, a_szName ) ) return true;		
		}
	}
	return false;
}

int CGuild::CreateGuild(int nLeader, MSG_CreateGuild* pData)
{
	int nEmpty = GetEmptyGuild();

	if(nEmpty<=0 || nEmpty>=MAX_USER) return 0;

	pGuild[nEmpty].Mode = GUILD_CHARGED;
	pGuild[nEmpty].pMemberIndex[0] = nLeader;
	pGuild[nEmpty].GUILD.GuildID = pData->GuildID;
	pGuild[nEmpty].GUILD.Mark = pData->GuildMark;
	strncpy(pGuild[nEmpty].GUILD.GuildName, pData->GuildName, SZNAME_LENGTH);
	pGuild[nEmpty].GUILD.Member[0] = pData->Member;

	return nEmpty;
}

char CGuild::GetLevel(char* pName)
{
	for	(int i=0;i<MAX_GUILD_MEMBER;i++)
	{
		if(!strcmp(pName, GUILD.Member[i].MemberName)) return GUILD.Member[i].GuildRank;
	}	

#ifdef __LOG_GUILD__
	char chBuf[256] = { 0,0,0, } ;
	sprintf(chBuf, "[GetLevel] [%s] Get GuildLevel Fail in GuildID:%d \r\n", pName, GUILD.GuildID) ;
	TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ; 
#endif //	#ifdef __LOG_GUILD__

	return 0;
}

int CGuild::AddGuildMember(MSG_AddGuildMember* pData)
{
	int nIndex=0;
	for	(nIndex=0;nIndex<MAX_GUILD_MEMBER;nIndex++)	{if(GUILD.Member[nIndex].MemberName[0]==0) break;}
	
	if(nIndex==MAX_GUILD_MEMBER) return 0;
	GUILD.Member[nIndex] = pData->Member;

	return nIndex;
}

int	CGuild::RemoveGuildMember(char* szName)
{
	bool bFlag = false;
	for	(int i=0;i<MAX_GUILD_MEMBER;i++)
	{	if(!strcmp(GUILD.Member[i].MemberName, szName)) 
		{	ZeroMemory(&GUILD.Member[i], sizeof(STRUCT_GUILD_MEMBER)); 
			bFlag = true; break;
		}
	}

#ifdef __LOG_GUILD__
	if(!bFlag)
	{
		char chBuf[256] = { 0,0,0, } ;
		sprintf(chBuf, "[RemoveGuildMember] [%s] Get GuildLevel Fail in GuildID:%d \r\n", szName, GUILD.GuildID) ;
		TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ; 
	}
#endif	//	#ifdef __LOG_GUILD__

	return 0;
}

int	CGuild::UpdateGuildMember(MSG_GuildUpdateMember* pData)
{
	int nRet = 0;

	for	(int i=0;i<MAX_GUILD_MEMBER;i++)
	{	if(!strcmp(GUILD.Member[i].MemberName, pData->Member.MemberName)) break;
	}
	if	(i==MAX_GUILD_MEMBER) return nRet;
	//if	(GUILD.Member[i].GuildRank != pData->Member.GuildRank) nRet=1;

	//BYTE byRank = GUILD.Member[i].GuildRank;
    GUILD.Member[i] = pData->Member;

	//GUILD.Member[i].GuildRank = byRank;

	return nRet;
}

int CGuild::UpdateGuildMemberRank(MSG_GuildSetRanking* pData)
{
	for	(int i=0;i<MAX_GUILD_MEMBER;i++)
	{	if(!strcmp(GUILD.Member[i].MemberName, pData->CharacterName)) break;
	}
	if	(i==MAX_GUILD_MEMBER) return -1;

	GUILD.Member[i].GuildRank = pData->GuildRank;

	//	길마의 랭킹이 초기화되는 문제발생 => 길드에 길드장이름을 기억시키기로 한다.
	if(pData->GuildRank == eGuildMaster)
	{	strncpy(szGuildMaster, GUILD.Member[i].MemberName, SZNAME_LENGTH);
	}

	return i;
}

//	길드마스터가 사라지는 문제발생
//	길드마스터를 강제로 세팅해준다.
void CGuild::CheckGuildMaster()
{
	//	길드마스터체크
	int nMaster=0;
	for	(nMaster=0;nMaster<MAX_GUILD_MEMBER;nMaster++)
	{	if(GUILD.Member[nMaster].GuildRank==eGuildMaster) break;
	}	

	//	길드장이 있을 경우 길드마크체크
	if(nMaster!=MAX_GUILD_MEMBER)
	{	if(GUILD.Mark==0) return;
		
		DWORD dwGuildEmblem	= (GUILD.Mark & 0x000000FF);
		DWORD dwGuildTitle	= (GUILD.Mark & 0x0000FF00) >> 8;
		DWORD dwGuildColor	= (GUILD.Mark & 0x00FF0000) >> 16;

		//	길드장이 존재하고 길드마크가 존재시 정상적인 데이터라고 판단한다.(길드원데이터는 보장못함)
		if (!(dwGuildEmblem < 1 || dwGuildEmblem > 72 || dwGuildTitle < 1 
			|| dwGuildTitle > 84 || dwGuildColor < 1 || dwGuildColor > 72 )) return;
	}

#ifdef __LOG_GUILD__
	char chBuf[2048] = { 0,0,0, }; memset(chBuf,0,2048);	//	잘못된 길드마크를 가진 길드정보를 남긴다
	sprintf(chBuf, "[CheckGuildMaster] Guild broken GuildID:%d GuildMark:%d GuildMembers : \r\n", GUILD.GuildID, GUILD.Mark);
	for(int i=0; i<MAX_GUILD_MEMBER; i++)
	{	if(GUILD.Member[i].MemberName[0] == 0) continue;
		char chData[128] = {0,0,0, };
		sprintf(chData, "%s %d    ", GUILD.Member[i].MemberName, GUILD.Member[i].GuildRank);
		strcat(chBuf, chData);
	}

	char chLine[8]={0,}; sprintf(chLine, "\r\n"); strcat(chBuf, chLine);
	TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
	
	int nResult = ReadGuildFile(GUILD.GuildID, this);
	if(!nResult)			//	길드파일 Read fail
	{	memset(chBuf,0,2048);
		sprintf(chBuf, "err ReadGuildFile fail GuildID:%d \r\n", GUILD.GuildID) ;
		TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
	}
#else
	for(int i=0; i<MAX_GUILD_MEMBER; i++) { if(GUILD.Member[i].MemberName[0] == 0) continue; }
	int nResult = ReadGuildFile(GUILD.GuildID, this);
#endif	//	#ifdef __LOG_GUILD__
	

	//	길드마스터가 있을 경우
	//if(nMaster!=MAX_GUILD_MEMBER) return;

	////	길드마스터가 없을 경우 강제로 세팅해준다.
	//for	(int nMaster=0;nMaster<MAX_GUILD_MEMBER;nMaster++)
	//{	if(GUILD.Member[nMaster].MemberName[0]==0) continue;
	//	if(strcmp(GUILD.Member[nMaster].MemberName, szGuildMaster)) continue;
	//	GUILD.Member[nMaster].GuildRank=eGuildMaster;

	//	char chBuf[256] = { 0,0,0, } ;
	//	sprintf(chBuf, "[MASTER] GuildID:%d have no guildmaster => set [%s] to GuildMaster \r\n", GUILD.GuildID, szGuildMaster) ;
	//	TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
	//	break;
	//}

	//char chBuf[256] = { 0,0,0, } ;
	//sprintf(chBuf, "[ERROR] GuildID:%d have no guildmaster => Cant find Guildmaster \r\n", GUILD.GuildID, szGuildMaster ) ;
	//TimeWriteLog( chBuf, ".\\MONSTER_LOG\\[Log]Guild_Log.txt" ) ;
}

void CGuild::SetCargoLevel(BYTE byCargo1, BYTE byCargo2, BYTE byCargo3)
{
	if(byCargo1<0 || byCargo1>=eGuildMaster) byCargo1 = 10;
	if(byCargo2<0 || byCargo2>=eGuildMaster) byCargo2 = 10;
	if(byCargo3<0 || byCargo3>=eGuildMaster) byCargo3 = 10;

	GUILD.byCargoLevel[0] = byCargo1;
	GUILD.byCargoLevel[1] = byCargo2;
	GUILD.byCargoLevel[2] = byCargo3;
}

BOOL CGuild::IsUsableCargo(BYTE byLevel, WORD wIndex)
{
	if(wIndex<0 || wIndex>=MAX_CARGO*3) return FALSE;
	WORD wCargo = wIndex/MAX_CARGO;

	time_t now; time(&now);
	if(GUILD.dwTime[wCargo]<(DWORD)now) return FALSE;

	return byLevel>=GUILD.byCargoLevel[wCargo];
}

void CGuild::GetCargoTime(DWORD* pdwTime1, DWORD* pdwTime2, DWORD* pdwTime3)
{
	*pdwTime1 = GUILD.dwTime[0];
	*pdwTime2 = GUILD.dwTime[1];
	*pdwTime3 = GUILD.dwTime[2];
}

void CGuild::SetCargoTime(DWORD dwTime1, DWORD dwTime2, DWORD dwTime3)
{
	GUILD.dwTime[0] = dwTime1;
	GUILD.dwTime[1] = dwTime2;
	GUILD.dwTime[2] = dwTime3;
}