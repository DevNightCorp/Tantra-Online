#include <windows.h>
#include <ERRNO.H>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h> 

#include "Basedef.h"
#include "CPSock.h"
//#include "ItemEffect.h"

#include "CUser.h"
#include "CFileDB.h"
#include "MD5Checksum.h"

extern HWND hWndMain;
extern CUser pUser[MAX_SERVERNUMBER];
extern CUser pAdmin[MAX_ADMIN];
extern void DisableAccount(int conn,char * account);
extern void EnableAccount(int conn,char * account);

extern STRUCT_MOB g_pBaseSet[MAX_CLASS];
//extern int errno;
extern void Log                  ( char * String1, char * String2 ,unsigned int ss);
extern int				ServerIndex;
extern int				TransperCharacter;
extern int				GuildID;
extern CPSock			AdminClient; // transperserver용
extern E_COUNTRY_ID		g_eCountryID;

BOOL ProcessRecord(int conn,char * str);

//#define DECREASE_SLEEPING_ACCOUNTS_BP

//////////////////////////////////////////////////////////////////////////
//
//             CFileDB,  ~CFileDB
//
// 1.모드 초기화
//  
//////////////////////////////////////////////////////////////////////////

CFileDB::CFileDB()
{	

	for (int i=0;i<MAX_DBACCOUNT;i++)
	{
		pAccountList[i].Login =  0;
        pAccountList[i].Slot  = -1;
		memset(&pAccountList[i].File,0,sizeof(pAccountList[i].File));
	}

	for(i=0; i<5; i++)
	{
		for(int j=0; j<24; j++) m_iTrimuriti[3][24] = 0;
	}
}

CFileDB::~CFileDB()
{
}

void CFileDB::InitGuild()
{
	STRUCT_GUILD guild; 
	for(int i=0; i<GuildID; i++)
	{	//strupr(user);
		memset(&guild, 0, sizeof(STRUCT_GUILD));
		int nID=0; int ret = ReadGuildFile(i,&guild);	
		if (ret==FALSE) continue;;
		for	(int k=0;k<MAX_GUILD_MEMBER-1;k++)
		{	if	(guild.Member[k].MemberName[0] == 0) continue;
			for(int j=k+1; j<MAX_GUILD_MEMBER; j++)
			{	if	(guild.Member[j].MemberName[0] == 0) continue;
				if	(!strcmp(guild.Member[k].MemberName, guild.Member[j].MemberName)) 
				{	memset(&(guild.Member[j]),0,sizeof(STRUCT_GUILD_MEMBER));
				}
			}
			if(guild.Member[nID].GuildRank<guild.Member[k].GuildRank ||  
				(guild.Member[nID].GuildRank==guild.Member[k].GuildRank && guild.Member[nID].byLevel<guild.Member[k].byLevel)) nID=k;
			if(nID!=k && guild.Member[k].GuildRank==eGuildMaster) guild.Member[k].GuildRank=eGuildMember;
		}
		guild.Member[nID].GuildRank=eGuildMaster;
		WriteGuildFile(i,&guild);

		char guilfile[256]; sprintf(guilfile,"G:\\name\\%s.dat", guild.GuildName);
		FILE * fp = fopen(guilfile,"wb"); if(fp==NULL) continue; 
		char pID[128]={0,}; sprintf(pID, "%d", i);
		fwrite(pID,strlen(pID),1,fp); fclose(fp);
	}
}

BOOL CFileDB::AddAccount(char *id,char*pass,int ssn1,int ssn2)
{

	char check[128];
	strncpy(check,id,ACCOUNTNAME_LENGTH); strupr(check);
	if	(check[0]=='C'&&check[1]=='O'&&check[2]=='M'&&check[3]>=48&&check[3]<=57&&check[4]==0)	return FALSE;
	if	(check[0]=='L'&&check[1]=='P'&&check[2]=='T'&&check[3]>=48&&check[3]<=57&&check[4]==0)	return FALSE;


      char temp[128]; char First[128];BASE_GetFirstKey(id,First);
	  sprintf(temp,"./account/%s/%s.TAD",First,id);

    int Handle = open( temp, _O_RDONLY | _O_BINARY , NULL );
	if (Handle!=-1)
	{ 	close(Handle);
		STRUCT_ACCOUNTFILE  file; strncpy(file.AccountName,id,ACCOUNTNAME_LENGTH);
		DBReadAccount(&file);
		if ( g_eCountryID != eCountryKorea )
		{
			char szMD5Pass[36] = {0, };
			strlwr(pass);
			CMD5Checksum::GetMD5((byte*)pass,strlen(pass),szMD5Pass);
			strcpy(file.AccountPass,szMD5Pass);
		}
		else
		{
			strcpy(file.AccountPass,pass);
		}
	
		file.ssn1 = ssn1;
		file.ssn2 = ssn2;
		DBWriteAccount(&file);
		return TRUE;
	}
	close(Handle);
	  

      STRUCT_ACCOUNTFILE  file;
	  memset(&file,0,sizeof(file));
	  strcpy(file.AccountName,id);
	  if ( g_eCountryID != eCountryKorea )
	  {
		  char szMD5Pass[36] = {0, };
		  strlwr(pass);
		  CMD5Checksum::GetMD5((byte*)pass,strlen(pass),szMD5Pass);
		  strcpy(file.AccountPass,szMD5Pass);
	  }
	  else
	  {
		  strcpy(file.AccountPass,pass);
	  }	
	  file.ssn1 = ssn1;
	  file.ssn2 = ssn2;
	  

 
      int ret = DBWriteAccount(&file); // 어카운트 파일을 통째로 쓴다.
      if  (ret==FALSE) return FALSE;
	  return TRUE;
}


BOOL CFileDB::UpdateAccount(char *id,char*pass,int ssn1,int ssn2)
{

	char check[128];
	strncpy(check,id,ACCOUNTNAME_LENGTH); strupr(check);
	if	(check[0]=='C'&&check[1]=='O'&&check[2]=='M'&&check[3]>=48&&check[3]<=57&&check[4]==0)	return FALSE;
	if	(check[0]=='L'&&check[1]=='P'&&check[2]=='T'&&check[3]>=48&&check[3]<=57&&check[4]==0)	return FALSE;

      char temp[128]; char First[128];BASE_GetFirstKey(id,First);
	  sprintf(temp,"./account/%s/%s.TAD",First,id);

      int Handle = open( temp, _O_RDONLY | _O_BINARY , NULL );
	  if (Handle==-1)
	  {  close(Handle);
		 return FALSE;
	  }
	  close(Handle);

      int idx = GetIndex(id);
	  if  (idx!=-1)
	  {   strcpy(pAccountList[idx].File.AccountPass,pass);
	  }

	  STRUCT_ACCOUNTFILE  file;
	  strncpy(file.AccountName,id,ACCOUNTNAME_LENGTH);
      int ret =DBReadAccount(&file);
      if  (ret==FALSE)
	  {	  Log("err updateaccount read fail",id,0);
		  return FALSE;
	  }

	  char szMD5Pass[36] = {0, };
	  if ( g_eCountryID != eCountryKorea )
	  {
		  strlwr(pass);
		  CMD5Checksum::GetMD5((byte*)pass,strlen(pass),szMD5Pass);
		  strcpy(file.AccountPass,szMD5Pass);
	  }
	  else
	  {
		  strcpy(file.AccountPass,pass);
	  }

	  file.ssn1 = ssn1;
	  file.ssn2 = ssn2;
	  ret = DBWriteAccount(&file); // 어카운트 파일을 통째로 쓴다.
      if  (ret==FALSE)
	  {   Log("err updateAccount write fail",id,0);
		  return FALSE;
	  }
      // 접속중이면 pass 부분을 변경한다.
      int IdxName = GetIndex(file.AccountName);
      if  (IdxName > 0  && IdxName < MAX_DBACCOUNT)
	  {   if ( g_eCountryID != eCountryKorea ) strcpy(pAccountList[IdxName].File.AccountPass,szMD5Pass);
		  else strcpy(pAccountList[IdxName].File.AccountPass,pass);
	  }
	  //

	  return TRUE;
}

BOOL ProcessRecord(int conn,char * str)
{
	// Record파일에다가 쓴다.
	// Daemon이 읽어 가므로 주의한다.
	char file[256];
	struct tm when;
	time_t now;
	time(&now); when= *localtime(&now);
    sprintf(file,"RC%4.4d_%2.2d_%2.2d_%2.2d_%2.2d_%2d.txt",when.tm_year-100,when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,when.tm_sec,conn);
	char filetemp[236];
    sprintf(filetemp,"S:/export/record%d/%s",ServerIndex,file);
	FILE * fp = fopen(filetemp,"wt");
	if	(fp==NULL)	return FALSE;
	

	fprintf(fp,"%s",str);
	fclose(fp);
	return TRUE;
}
BOOL CFileDB::ReadGuildFile(int gid,STRUCT_GUILD* guild)
{
	char file[256]; sprintf(file,"G:\\%7.7d.dat",gid);
	FILE * fp = fopen(file,"rb");	if (fp==NULL)	return FALSE;
	fread(guild,sizeof(STRUCT_GUILD),1,fp);
	fclose(fp);

	return TRUE;
}
BOOL CFileDB::WriteGuildFile(int gid,STRUCT_GUILD * guild)
{
	char file[256]; sprintf(file,"G:\\%7.7d.dat",gid);
	FILE * fp = fopen(file,"wb");	if (fp==NULL)	return FALSE;
	fwrite(guild,sizeof(STRUCT_GUILD),1,fp);
	fclose(fp);
	return TRUE;
}

BOOL CFileDB::CreateGuildFile(int gid,MSG_CreateGuild* pData)
{	
	char guilfile[256]; sprintf(guilfile,"G:\\name\\%s.dat", pData->GuildName);
	FILE * fp = fopen(guilfile, "r");
	if(fp!=NULL) return false;

	STRUCT_GUILD guild; memset(&guild,0,sizeof(guild));
	guild.GuildID = gid;
	guild.Mark=pData->GuildMark;
	strncpy(guild.GuildName, pData->GuildName, SZNAME_LENGTH);
	guild.Member[0]=pData->Member;
	WriteGuildFile(gid,&guild);
	fp = fopen(guilfile,"wb"); if(fp==NULL) return FALSE; 
	char pID[128]={0,}; sprintf(pID, "%d", gid);
	fwrite(pID,strlen(pID),1,fp); fclose(fp);
	return TRUE;
}
BOOL CFileDB::AddGuildMember(int gid,MSG_AddGuildMember * pData)
{	STRUCT_GUILD guild;
	//strupr(user);
	int ret = ReadGuildFile(gid,&guild);	
	if (ret==FALSE) return FALSE;
	for	(int i=0;i<MAX_GUILD_MEMBER;i++)
	{	if	(!strcmp(guild.Member[i].MemberName, pData->Member.MemberName)) return FALSE;
	}
	for	(int i=0;i<MAX_GUILD_MEMBER;i++)
	{	if	(guild.Member[i].MemberName[0]==0) break;
	}
	if	(i==MAX_GUILD_MEMBER) return FALSE;
	guild.Member[i] = pData->Member;
	ret = WriteGuildFile(gid,&guild);
	if (ret==FALSE) return FALSE;
	return TRUE;
}
int CFileDB::RemoveGuildMember(int gid,char * user, char* pMaster)
{	STRUCT_GUILD guild;
	int ret = ReadGuildFile(gid,&guild);		
	if (ret==FALSE) return -1;
	int i=0;	int nMaster=MAX_GUILD_MEMBER;			//	 nMaster=MAX_GUILD_MEMBER(길드장이 안바뀌엇을 경우)
	for	(i=0;i<MAX_GUILD_MEMBER;i++)
	{	if	(!strncmp(guild.Member[i].MemberName,user,SZNAME_LENGTH)) break;
	}
	if	(i==MAX_GUILD_MEMBER) return -1;				//	해당멤버가 존재하지 않을경우
	if	(guild.Member[i].GuildRank==eGuildMaster)		//	길드장 탈퇴시 길드장권한 이양
	{	int temp=0; int ntempLevel = 0;
		for	(int m=0;m<MAX_GUILD_MEMBER;m++)
		{	if	(guild.Member[m].GuildRank>temp && guild.Member[m].GuildRank!=eGuildMaster) { nMaster=m; temp=guild.Member[m].GuildRank; ntempLevel=guild.Member[m].byLevel; }
			else if(guild.Member[m].GuildRank==temp && guild.Member[m].byLevel>ntempLevel) { nMaster=m; temp=guild.Member[m].GuildRank; ntempLevel=guild.Member[m].byLevel; }
		}
		if(nMaster>=0 && nMaster<MAX_GUILD_MEMBER)
			if(guild.Member[nMaster].MemberName[0]!=0) 
			{	guild.Member[nMaster].GuildRank=eGuildMaster;
				strncpy(pMaster, guild.Member[nMaster].MemberName, SZNAME_LENGTH);
			}
	}

	memset(&guild.Member[i],0,sizeof(STRUCT_GUILD_MEMBER));
	// 탈퇴된 계정의 정보도 업데이트 해준다.
	char szAccount[ACCOUNTNAME_LENGTH] = {0, 0, };
	GetAccountByChar( szAccount, user );
	if ( szAccount[0] != 0 ) // 어카운트 정보가 존재하면,
	{	STRUCT_ACCOUNTFILE acc;
		ZeroMemory( &acc, sizeof(STRUCT_ACCOUNTFILE) );
		strncpy( acc.AccountName, szAccount, ACCOUNTNAME_LENGTH );
		if ( DBReadAccount( &acc ) )
		{	for ( int i=0;i<MOB_PER_ACCOUNT;i++)
			{	if ( strncmp( acc.Char[i].szName, user, SZNAME_LENGTH ) == 0 )
				{	acc.Char[i].nGuildID = 0;
					DBWriteAccount( &acc );
					DBExportAccount( &acc );
				}
			}
		}
	}

	ret = WriteGuildFile(gid,&guild);	
	if (ret==FALSE) return -1;
	return nMaster;
}
BOOL CFileDB::UpdateGuild(int gid,MSG_GuildUpdate * pData)
{	STRUCT_GUILD guild;
	//strupr(user);
	int ret = ReadGuildFile(gid,&guild);	
	if (ret==FALSE) return FALSE;

	strncpy(guild.AlliedGuildName1, pData->AlliedGuildName1, SZNAME_LENGTH);
	strncpy(guild.AlliedGuildName2, pData->AlliedGuildName2, SZNAME_LENGTH);
	strncpy(guild.EnemyGuildName1, pData->EnemyGuildName1, SZNAME_LENGTH);
	strncpy(guild.GuildMessage, pData->GuildMessage, GUILDMESSAGE_LENGTH);

	ret = WriteGuildFile(gid,&guild);
	if (ret==FALSE) return FALSE;
	return TRUE;
}
BOOL CFileDB::UpdateGuildMember(int gid,MSG_GuildUpdateMember * pData)
{	STRUCT_GUILD guild;
	//strupr(user);
	int ret = ReadGuildFile(gid,&guild);	
	if(ret==FALSE) return FALSE;
	for	(int i=0;i<MAX_GUILD_MEMBER;i++)
	{	if(!strcmp(guild.Member[i].MemberName, pData->Member.MemberName)) break;
	}
	if	(i==MAX_GUILD_MEMBER) return FALSE;
	BYTE byRank = guild.Member[i].GuildRank;
	guild.Member[i] = pData->Member;
	if(byRank!=guild.Member[i].GuildRank)		//	존서버의 길드정보가 이상함.
	{	char temp[256];
		sprintf(temp,"err Update GuildMember GuildID:%d char:[%s] oRank:%d xRank:%d",gid, pData->Member.MemberName, byRank, guild.Member[i].GuildRank);
		Log(temp,"-system",0);

		guild.Member[i].GuildRank = byRank;
		if(pData!=NULL) pData->Member.GuildRank = byRank;
	}
	ret = WriteGuildFile(gid,&guild);
	if (ret==FALSE) return FALSE;
	return TRUE;
}

BOOL CFileDB::UpdateGuildMark(int gid, MSG_GuildUpdateMark * pData)
{	STRUCT_GUILD guild;
	//strupr(user);
	int ret = ReadGuildFile(gid,&guild);	
	if(ret==FALSE) return FALSE;
	guild.Mark=pData->Mark;
	ret = WriteGuildFile(gid,&guild);
	if (ret==FALSE) return FALSE;
	return TRUE;
}

BOOL CFileDB::UpdateGuildMemberRank(int gid, MSG_GuildSetRanking * pData)
{	STRUCT_GUILD guild;
	//strupr(user);
	int ret = ReadGuildFile(gid,&guild);	
	if(ret==FALSE) return FALSE;
	for	(int i=0;i<MAX_GUILD_MEMBER;i++)
	{	if(!strcmp(guild.Member[i].MemberName, pData->CharacterName)) break;
	}
	if	(i==MAX_GUILD_MEMBER) return FALSE;
	guild.Member[i].GuildRank = pData->GuildRank;
	ret = WriteGuildFile(gid,&guild);
	if (ret==FALSE) return FALSE;
	return TRUE;
}

int CFileDB::GetGuildID(char* pName)
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

BOOL CFileDB::UpdateGuildCargoLevel(int nID, BYTE byLevel1, BYTE byLevel2, BYTE byLevel3)
{
	STRUCT_GUILD guild;

	int ret = ReadGuildFile(nID, &guild);	
	if(ret==FALSE) return FALSE;

	guild.byCargoLevel[0] = byLevel1;
	guild.byCargoLevel[1] = byLevel2;
	guild.byCargoLevel[2] = byLevel3;

	ret = WriteGuildFile(nID, &guild);
	if (ret==FALSE) return FALSE;

	return TRUE;
}

BOOL CFileDB::UpdateGuildCargoTime(int nID, DWORD dwTime1, DWORD dwTime2, DWORD dwTime3)
{
	STRUCT_GUILD guild;

	int ret = ReadGuildFile(nID, &guild);	
	if(ret==FALSE) return FALSE;

	guild.dwTime[0] = dwTime1;
	guild.dwTime[1] = dwTime2;
	guild.dwTime[2] = dwTime3;

	ret = WriteGuildFile(nID, &guild);
	if (ret==FALSE) return FALSE;

	return TRUE;
}

BOOL CFileDB::UpdateGuildCargoItem(int nID, int nIndex, STRUCT_ITEM* pstItem)
{
	STRUCT_GUILD guild;

	int ret = ReadGuildFile(nID, &guild);	
	if(ret==FALSE) return FALSE;

	guild.Repository[nIndex] = *pstItem;

	ret = WriteGuildFile(nID, &guild);
	if (ret==FALSE) return FALSE;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
//             CFileDB,  ~CFileDB
//
// 1.모드 초기화
//  
//////////////////////////////////////////////////////////////////////////
// 어카운트 마다 어카운트네임으로 파일 1개만 가진다.
// 캐랙터 읽기와 MOB 읽기는 완전히 분리된다.
extern int Sapphire;
extern int WriteConfig(void);
BOOL CFileDB::ProcessMessage(char * Msg,int conn)
{    MSG_STANDARD *std= (MSG_STANDARD *)Msg;
     switch (std->wType)    
	 {
	 case _Msg_GuildCargoUsingLevel:
		 {	Msg_GuildCargoUsingLevel * m = (Msg_GuildCargoUsingLevel*)Msg;

			char temp[256];
			int ret = UpdateGuildCargoLevel(m->nGuildID, m->byCargoLevel[0], m->byCargoLevel[1], m->byCargoLevel[2]);
			if	(ret==FALSE)	
			{	sprintf(temp,"err _Msg_GuildCargoUsingLevel GuildID:%d level[0]:%d, level[1]:%d, level[2]:%d", m->nGuildID, m->byCargoLevel[0], m->byCargoLevel[1], m->byCargoLevel[2]);
				return TRUE;
			}

			sprintf(temp,"_Msg_GuildCargoUsingLevel GuildID:%d level[0]:%d, level[1]:%d, level[2]:%d", m->nGuildID, m->byCargoLevel[0], m->byCargoLevel[1], m->byCargoLevel[2]);

			SendToAll((MSG_STANDARD*)m);
		 }	break;
	 case _Msg_GuildCargoTime:
		 {	Msg_GuildCargoTime * m = (Msg_GuildCargoTime*)Msg;

			char temp[256];
			int ret = UpdateGuildCargoTime(m->nGuildID, m->dwTime[0], m->dwTime[1], m->dwTime[2]);
			if	(ret==FALSE)	
			{	sprintf(temp,"err _Msg_GuildCargoTime GuildID:%d Time[0]:%d, Time[1]:%d, Time[2]:%d", m->nGuildID, m->dwTime[0], m->dwTime[1], m->dwTime[2]);
				return TRUE;
			}

			sprintf(temp,"_Msg_GuildCargoTime GuildID:%d Time[0]:%d, Time[1]:%d, Time[2]:%d", m->nGuildID, m->dwTime[0], m->dwTime[1], m->dwTime[2]);

			SendToAll((MSG_STANDARD*)m);
		 }	break;
	 case _Msg_GuildItemUpdate:
		 {	Msg_GuildItemUpdate * m = (Msg_GuildItemUpdate*)Msg;

			char temp[256];
//			int ret = UpdateGuildCargoItem(m->nGuildID, m->nCargoIndex, &(m->item));
			int ret = UpdateGuildCargoItem(m->nGuildID, m->nToIndex, &(m->item));
			if	(ret==FALSE)	
			{	sprintf(temp,"err _Msg_GuildItemUpdate GuildID:%d CIndex:%d, IIndex:%d", m->nGuildID, m->nToIndex, (m->item.snIndex)+4000);
				return TRUE;
			}

			sprintf(temp,"_Msg_GuildItemUpdate GuildID:%d CIndex:%d, IIndex:%d,", m->nGuildID, m->nToIndex, (m->item.snIndex)+4000);

			pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));
		 }	break;
	 case _MSG_Warp:
		 {	MSG_Warp * m = (MSG_Warp*) Msg;
			
			if(m->nID<0 || m->nID>=MAX_USER) break;

			int nOheridx	= GetIndexFromName(m->szName);
			if(nOheridx == 0)	//	상대방이 비접속중일때
			{	m->byResult = S_FALSE;
			}
			else				//	상대방이 접속중일때
			{	m->byResult = S_OK;

				int nServer = nOheridx/MAX_USER;
				pUser[nServer].cSock.SendOneMessage((char*)m, sizeof(*m));	//	상대를 호출한다
			}
			if(m->nID != 0) pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m));			//	호출자에게 결과을 전송한다.
		 }	break;
/////////////////////////////////////////////////////////////////////
//       캐랙터 이전
/////////////////////////////////////////////////////////////////////
		case	SSP_REQ_ZONE_INIT:
		{	for	(int i=conn*MAX_USER;i<(conn+1)*MAX_USER;i++)
			{	memset(&pAccountList[i],0,sizeof(pAccountList[i]));
			}
		}	break;
		case	_MSG_CreateGuild:
		{	MSG_CreateGuild * m = (MSG_CreateGuild*)Msg;
			int ret = CreateGuildFile(GuildID,m);
			if	(ret==FALSE)
			{	m->GuildID = -1;	//	길드생성실패를 알린다.
				pUser[conn].cSock.SendOneMessage((char*)m, sizeof(*m)); return TRUE;
			}

			char temp[256];sprintf(temp,"create Guild:[%s] by char:[%s] ID:%d",m->GuildName, m->Member.MemberName, m->GuildID);
			Log(temp,"-system",0);

			m->GuildID = GuildID;
			SendToAll((MSG_STANDARD*)m);
			GuildID++;
			WriteConfig();
		}	break;
		case _MSG_AddGuildMember:
		{	MSG_AddGuildMember * m = (MSG_AddGuildMember*)Msg;
			int ret = AddGuildMember(m->GuildID,m);
			if	(ret==FALSE)	
			{	m->nID = MAX_USER;
				pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
				return TRUE;
			}

			char temp[256];sprintf(temp,"Add Guildmember:[%s] GuildID:%d",m->Member.MemberName, m->GuildID);
			Log(temp,pAccountList[m->nID].File.AccountName,0);

			SendToAll((MSG_STANDARD*)m);
		}	break;
		case _MSG_RemoveGuildMember:
		{	MSG_RemoveGuildMember * m = (MSG_RemoveGuildMember*)Msg;
			char pMaster[SZNAME_LENGTH] = {0,0,0,};
			int	ret = RemoveGuildMember(m->GuildID,m->CharacterName,pMaster);
			if	(ret==-1)	return TRUE;

			if(ret!=MAX_GUILD_MEMBER)		//	길드장이 바뀌었을 경우
			{	MSG_GuildSetRanking sm; sm.wType=_MSG_GuildSetRanking;
				sm.wPDULength=sizeof(MSG_GuildSetRanking)-sizeof(HEADER);
				strncpy(sm.CharacterName, pMaster, SZNAME_LENGTH);
				sm.nGuildID=m->GuildID; sm.GuildRank=eGuildMaster;
				sm.byDummy=0; sm.snDummy=0;
				SendToAll((MSG_STANDARD*)&sm);
				char temp[256];sprintf(temp,"Change Guildmaster to [%s] GuildID:%d",pMaster, m->GuildID);
				Log(temp,"-system",0);
			}

			char temp[256];sprintf(temp,"Remove Guildmember:[%s] GuildID:%d",m->CharacterName, m->GuildID);
			Log(temp,"-system",0);

			SendToAll((MSG_STANDARD*)m);
		}	break;
		case _MSG_GuildMemberin:
		case _MSG_GuildMemberout:
		{	SendToAll((MSG_STANDARD*)Msg);
		}	break;
		case _MSG_GuildUpdate:
		{	MSG_GuildUpdate * m = (MSG_GuildUpdate *)Msg;
			int ret = UpdateGuild(m->GuildID,m);
			if	(ret==FALSE)	
			{	m->nID = MAX_USER;
				pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
				return TRUE;
			}
			char temp[256];sprintf(temp,"Update Guild:[%d]", m->GuildID);
			Log(temp,pAccountList[m->nID].File.AccountName,0);

			SendToAll((MSG_STANDARD*)m);
		}	break;
		case _MSG_GuildUpdateMember:
		{	MSG_GuildUpdateMember * m = (MSG_GuildUpdateMember *)Msg;
			int ret = UpdateGuildMember(m->GuildID,m);
			if	(ret==FALSE)	
			{	m->nID = MAX_USER;
				pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
				return TRUE;
			}
			char temp[256];sprintf(temp,"Update Guildmember:[%s] GuildID:%d",m->Member.MemberName, m->GuildID);
			Log(temp,"-system",0);
			SendToAll((MSG_STANDARD*)m);

		}	break;
		case _MSG_GuildUpdateMark:
		{	MSG_GuildUpdateMark * m = (MSG_GuildUpdateMark *)Msg;
			int ret = UpdateGuildMark(m->GuildID,m);
			if	(ret==FALSE) return TRUE;
			char temp[256];sprintf(temp,"Update Guilmark GuildID:%d mark:%08X type:%d",m->GuildID, m->Mark, m->byCostType);
			Log(temp,"-system",0);
			SendToAll((MSG_STANDARD*)m);
		}	break;
		case _MSG_GuildSetRanking:
		{	MSG_GuildSetRanking * m = (MSG_GuildSetRanking *)Msg;
			int ret = UpdateGuildMemberRank(m->nGuildID,m);
			if	(ret==FALSE)	
			{	m->nID = MAX_USER;
				pUser[conn].cSock.SendOneMessage((char*)m, (m->wPDULength)+sizeof(HEADER));
				return TRUE;
			}
			char temp[256];sprintf(temp,"SetRank:[%s] GuildID:%d to Rank:%d",m->CharacterName, m->nGuildID, m->GuildRank);
			Log(temp,pAccountList[m->nID].File.AccountName,0);
			SendToAll((MSG_STANDARD*)m);
		}	break;
		// select character list request reply
		case SSP_REQ_CHAR_LIST:
		{	S_SSP_REQ_CHAR_LIST *m = (S_SSP_REQ_CHAR_LIST *) Msg;
			S_SSP_RESP_CHAR_LIST sm; sm.nID = m->nID; sm.wType = SSP_RESP_CHAR_LIST;
			sm.wPDULength = sizeof(S_SSP_RESP_CHAR_LIST)-sizeof(HEADER);
			int idx=GetIndex(conn,m->nID);
            DBGetSelChar(&sm,&pAccountList[idx].File);
			sm.nID=m->nID;
			pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SSP_RESP_CHAR_LIST));
		}	break;
/////////////////////////////////////////////////////////////////////
		case	_MSG_MessageDBImple:
		{
			MSG_MessageDBImple *m = (MSG_MessageDBImple *) Msg;
			m->nID = 0;
			m->String[MESSAGE_LENGTH-1]=0;
			m->String[MESSAGE_LENGTH-2]=0;
			for (int i=0;i<MAX_SERVER;i++)
			{	if	(pUser[i].Mode==USER_EMPTY)	continue;
				if	(pUser[i].cSock.Sock==NULL)	continue;
				pUser[i].cSock.SendOneMessage((char*)m,sizeof(*m));
			}
		}	break;
/////////////////////////////////////////////////////////////////////
//       어카운트 로그인
/////////////////////////////////////////////////////////////////////
		case	SSP_REQ_MOVE_ZONE_SERVER:
		{	S_SSP_REQ_MOVE_ZONE_SERVER* m=(S_SSP_REQ_MOVE_ZONE_SERVER*)Msg;
			strupr(m->AccountName);
			char *ac = m->AccountName;

			S_SSP_RESP_MOVE_ZONE_SERVER sm; sm.wType = SSP_RESP_MOVE_ZONE_SERVER; sm.nID=m->nID;
			strcpy(sm.AccountName,m->AccountName);
			sm.nResult = REPLY_ACK_OK;

			int Idx=GetIndex(conn,m->nID);
			int IdxName = GetIndex(m->AccountName);
			STRUCT_ACCOUNTFILE file;
			memcpy(file.AccountName,m->AccountName,ACCOUNTNAME_LENGTH);
			time_t tLastWrite;
			int ret = DBReadAccount(&file,&tLastWrite);
			if  (ret == FALSE)
			{	sm.nResult = REPLY_INVALID_USER; // 계정이 존재하지 않음
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SSP_RESP_MOVE_ZONE_SERVER));
				return TRUE;
			}
			if (file.Coin<0) file.Coin =0;
			// 일단 무조건 파일에서 비번을 검사한다.
			strupr(file.AccountPass);
			strupr(m->AccountPass);
			if  (strcmp(m->AccountPass,file.AccountPass))
			{	sm.nResult = REPLY_INVALID_PASSWD; // 비번이 틀림
				pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SSP_RESP_MOVE_ZONE_SERVER));
				return TRUE;
			}
			// 이하 비번이 맞고 계정이 있으면 
			// IdxName==Idx 같은 게임서버의 같은 슬롯(클라이언트)에서 Login이 2번 날아온경우. 씹는다.
			if (IdxName==Idx) return TRUE;
			// 접속중인지 체크한다.
			if	(IdxName != 0 )
			{	//Idx==IdxName => 같은 슬롯에서 AccountLogin이 2번 날아온경우 ??
				Log("err disconnect previous connection",m->AccountName,0);
				{	sm.nResult = REPLY_ALREADY_LOGIN; // 이미 접속되어 있는 캐릭터
					pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SSP_RESP_MOVE_ZONE_SERVER));
					// 접속을 끊고 다시 접속하라는 처리 부분 있어야함.

					//SendDBSignal(conn,m->ID,_MSG_DBStillPlaying);
					SendDBSavingQuit(IdxName,0); //게임서버에, DB서버에게 저장을 요청
					return TRUE;
				}
			}

#ifdef DECREASE_SLEEPING_ACCOUNTS_BP
			// 휴면계정의 주신 포인트를 깎는다. 2005년 5월 29일이 기준.
			time_t tNow = time( NULL );
			time_t tStartTime = 1117292400; // 2005년 5월 29일...
			if ( tLastWrite < tStartTime ) tLastWrite = tStartTime; // 5월 29일 이전이었으면 5월 29일부터 계산
			time_t tElapsed = tNow - tLastWrite;
			int nTerms = tElapsed / 5184000; // 60 * 24 * 60 * 60 = 5184000 : 60일 간격으로 며칠이나 지났는지...
			int nPercent = nTerms * 20; // 주신포인트 감소 퍼센트
			if ( nPercent > 100 ) nPercent = 100;
#endif //DECREASE_SLEEPING_ACCOUNTS_BP

			for(int i=0; i<MOB_PER_ACCOUNT; i++)
			{	file.Char[i].byStatus = 0;
#ifdef DECREASE_SLEEPING_ACCOUNTS_BP
				file.Char[i].nBramanPoint *= ( 100 - nPercent ) / 100; // 휴면 계정의 주신 포인트를 감소시킨다.
#endif //DECREASE_SLEEPING_ACCOUNTS_BP
			}

			strupr(file.AccountName);
			// pAccountList 에 카피하기 전에 미리 캐랙터 이름 swap을 하고 저장까지 한다.
			STRUCT_ACCOUNTFILE * pfile = &pAccountList[Idx].File;
			memcpy(pfile,&file,sizeof(file));
   			AddAccountList(Idx);
			
			// 서버별 리스트가 할당되어 있으나, 그 슬롯이 DB서버 입장에서, Login상태면, 문제가 있다.
			// AddAccountList 덮어쓰기를 시도 하면 이전 데이터를 DB서버가 저장해 주고 ERROR메시지를 표시한다.
 			// Slot = -1; AddAccountList에서 한다.
			// 게임서버가 USER_LOGIN 상태이므로  USER_SELCHAR 상태로 바꾸어 줄 시그널을 보내야 한다.
			// account login success
			strcpy(sm.AccountName,file.AccountName);

			// char select info
			S_SSP_RESP_CHAR_LIST sel;
			DBGetSelChar(&sel,&file);
			sel.nID = m->nID; 
			pUser[conn].cSock.AddMessage((char*)&sel, sizeof(S_SSP_RESP_CHAR_LIST));

			sm.ssn1 = file.ssn1; sm.ssn2 = file.ssn2;
			pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SSP_RESP_MOVE_ZONE_SERVER));
		}	break;
/////////////////////////////////////////////////////////////////////
//       캐랙터 만들기     캐랙터를 만들기를 성공하면 반드시 그 캐랙터로 로그인 된다.
/////////////////////////////////////////////////////////////////////
     	case SSP_REQ_CHAR_CREATE:
		{
			S_SSP_REQ_CHAR_CREATE * m = (S_SSP_REQ_CHAR_CREATE *) Msg;
            S_SSP_RESP_CHAR_CREATE sm; sm.wType = SSP_RESP_CHAR_CREATE; sm.nID=m->nID;
			int nSlot = -1;
			int Idx=GetIndex(conn,m->nID);
			STRUCT_MOB *mob = NULL;
			int i;
			for	(i=0;i<MOB_PER_ACCOUNT;i++)
			{	mob=&pAccountList[Idx].File.Char[i];
				if	(mob->szName[0]==0)
				{	nSlot=i;break;
				}
			}
			int	nTot = m->byChakraHeart + m->byChakraMuscle + m->byChakraNerve + m->byChakraSoul;
			if(nTot > MAX_BASE_CHAKRA)
			{	Log("err newchar slot out of range",pAccountList[m->nID].File.AccountName,0);
				sm.byResult=REPLY_CHAR_CREATE_CHAKRA_OVER;	//	차크라초과오류
				pUser[conn].cSock.SendOneMessage((char *)&sm,sizeof(S_SSP_RESP_CHAR_CREATE));
				return TRUE;
			}
			if	(nSlot==-1)
			{	Log("err newchar slot out of range",pAccountList[m->nID].File.AccountName,0);
				sm.byResult=REPLY_CHAR_CREATE_CHAR_FULL;	//	캐릭터 다 있음
				pUser[conn].cSock.SendOneMessage((char *)&sm,sizeof(S_SSP_RESP_CHAR_CREATE));
				return TRUE;
			}
			 if (m->snTribe< 1||m->snTribe> 128)	//	잘못된 주신
			 {  Log("err newchar - class out of range",pAccountList[m->nID].File.AccountName,0);
				sm.byResult=REPLY_CHAR_CREATE_FAIL;
				pUser[conn].cSock.SendOneMessage((char *)&sm,sizeof(S_SSP_RESP_CHAR_CREATE));
				return TRUE;
			 }
			 ZeroMemory( mob, sizeof( STRUCT_MOB ) );
			 mob->szName[SZNAME_LENGTH-1]=0;
			 mob->szName[SZNAME_LENGTH-2]=0;
			 m->szCharName[SZNAME_LENGTH-1]=0;
			 m->szCharName[SZNAME_LENGTH-2]=0;
			 int len = strlen(m->szCharName);
			 for (i=0;i<len;i++)
			 {   if  (m->szCharName[i]==-95 && m->szCharName[i+1]==-95)
			     {	sm.byResult=REPLY_CHAR_CREATE_CHR_CHAR_FAIL;	//캐릭터이름 부적합
					pUser[conn].cSock.SendOneMessage((char *)&sm,sizeof(S_SSP_RESP_CHAR_CREATE));
					return TRUE;
			     }		  
			 }
			 ////////////////////////////////////////////////////////////////////////
             int ret = CreateCharacter(pAccountList[Idx].File.AccountName,m->szCharName);
			 if  (ret==FALSE)
			 {	sm.byResult=REPLY_CHAR_CREATE_ALREADY_EXIST;
				pUser[conn].cSock.SendOneMessage((char *)&sm,sizeof(S_SSP_RESP_CHAR_CREATE));
				return TRUE;
			 }
			 ////////////////////////////////////////////////////////////////////////
			 SetNewCharacter( mob, m );
             memcpy(mob->szName,m->szCharName,SZNAME_LENGTH);
             ret = DBWriteAccount(&pAccountList[Idx].File);
             if  (ret==FALSE)
			 {	sm.byResult=REPLY_CHAR_CREATE_FAIL;
				pUser[conn].cSock.SendOneMessage((char *)&sm,sizeof(S_SSP_RESP_CHAR_CREATE));
				return TRUE;
			 }
			 char temp[256];sprintf(temp,"create character [%s]",mob->szName);
			 Log(temp,pAccountList[Idx].File.AccountName,0);

			 ////////////////////////////////////////////////////////////////////////
			 sm.byResult=REPLY_ACK_OK; sm.bySlot=nSlot;
			 strncpy( sm.szCharName, m->szCharName, SZNAME_LENGTH );
			 pUser[conn].cSock.AddMessage((char *)&sm,sizeof(S_SSP_RESP_CHAR_CREATE));

 			S_SSP_RESP_CHAR_LIST sel;
			DBGetSelChar(&sel,&pAccountList[Idx].File);
			sel.nID = m->nID; 
			pUser[conn].cSock.SendOneMessage((char*)&sel, sizeof(S_SSP_RESP_CHAR_LIST));

		} break;
		case _MSG_Status:
		{	MSG_Status * m = (MSG_Status*) Msg;
			if(m->nID<=0 || m->nID>=MAX_USER) break;
			int Idx=GetIndex(conn,m->nID);
			int slot = pAccountList[Idx].Slot;
			pAccountList[Idx].File.Char[slot].byStatus = m->byStatus;
		}	break;
		/////////////////////////////////////////////////////////////////////
		//       캐랙터 로그인   getimmconversion
		/////////////////////////////////////////////////////////////////////
		case SSP_REQ_CHAR_INIT:
		{	S_SSP_REQ_CHAR_INIT * m = (S_SSP_REQ_CHAR_INIT *) Msg; 
			int nSlot = m->bySlot;
			if	(nSlot<0 || nSlot>=MOB_PER_ACCOUNT) break;

			int idx=GetIndex(conn,m->nID);
			//for(int i=0;i<MOB_PER_ACCOUNT;i++)
			//{	
				if	(strcmp(m->szCharName,pAccountList[idx].File.Char[nSlot].szName)) break;
			//}

			S_SSP_RESP_CHAR_INIT sm; sm.wType = SSP_RESP_CHAR_INIT; sm.nID=m->nID;            
			sm.nSlot = nSlot; sm.byConnType = m->byConnType;
			sm.byConnPos = m->byConnPos; sm.wPortalID = m->wPortalID;
			sm.wPDULength = sizeof(S_SSP_RESP_CHAR_INIT) - sizeof(HEADER);
			sm.bySlot = nSlot;
			if	(nSlot==-1)
			{	sm.byResult = 8; //데이터 로딩 에러
				pUser[conn].cSock.SendOneMessage((char *)&sm,sizeof(S_SSP_RESP_CHAR_INIT));
				return TRUE;
			}
			pAccountList[idx].Slot = nSlot;
//			m_mapCharTable.insert( std::map<char*,int,HTStr>::value_type( pAccountList[idx].File.Char[nSlot].szName, idx ) );

			sm.byResult = 0;//데이터 로딩 성공
			memcpy(sm.szTargetName, m->szTargetName, SZNAME_LENGTH);
			memcpy(&sm.sChar,&pAccountList[idx].File.Char[nSlot],sizeof(STRUCT_MOB));
			memcpy(&sm.sNpcInven,pAccountList[idx].File.Cargo,sizeof(STRUCT_ITEM)*MAX_CARGO);
			memcpy(sm.dwTimeStamp,pAccountList[idx].File.dwTimeStamp,sizeof(sm.dwTimeStamp));
			sm.nNpcMoney=pAccountList[idx].File.Coin;
			pUser[conn].cSock.SendOneMessage((char *)&sm,sizeof(S_SSP_RESP_CHAR_INIT));
			// 캐랙터 로그인에 또는 Account Login에 Cargo를 날려야 한다.
			return TRUE;
		}	break;
		/////////////////////////////////////////////////////////////////////
		//       SavingQuit 리턴 처리
		/////////////////////////////////////////////////////////////////////
		case _MSG_DBNoNeedSave:
		{	MSG_STANDARD * m = (MSG_STANDARD*) Msg;
			if	(m->nID<0||m->nID>MAX_SERVER*MAX_USER) return TRUE;
			int Idx = GetIndex(conn,m->nID);
			char acc[128]; strncpy(acc,pAccountList[Idx].File.AccountName,ACCOUNTNAME_LENGTH);
			RemoveAccountList(Idx);
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			for (int i=0;i<MAX_ADMIN;i++)
			{	if (pAdmin[i].Level<=2 || pAdmin[i].DisableID==0) continue;
				if (pAdmin[i].DisableID==Idx) {DisableAccount(i,acc);break;}// Disable Account // 
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}	break;
		case _MSG_DBSaveMob:
		{
			MSG_DBSaveMob *m = (MSG_DBSaveMob*) Msg;
		    int Idx = GetIndex(conn,m->nID);
            pAccountList[Idx].File.AccountName[ACCOUNTNAME_LENGTH-1]=0;
			pAccountList[Idx].File.AccountName[ACCOUNTNAME_LENGTH-2]=0;
			char acc[128]; strncpy(acc,pAccountList[Idx].File.AccountName,ACCOUNTNAME_LENGTH);
			m->AccountName[ACCOUNTNAME_LENGTH-1]=0;
			m->AccountName[ACCOUNTNAME_LENGTH-2]=0;
			//pAccountList[Idx].Slot
			//	int serverslot = pAccountList[Idx].Slot;
			//	if	(m->Slot<0||m->Slot>=MOB_PER_ACCOUNT|| serverslot<0||serverslot>=MOB_PER_ACCOUNT) error.
			//	if	(m->Slot!=serverslot) error.
			//  if	(!strcmp(m->CharacterName,pAccountList[Idx].File.Char[serverslot].szName)
			int Slot = -1; bool bContinue=false;
			for(int n=0; n<MOB_PER_ACCOUNT; n++)
			{
				if(strcmp(m->MOB.szName, pAccountList[Idx].File.Char[n].szName) == 0) Slot = n;
			}
			if (Slot<0||Slot>=MOB_PER_ACCOUNT )
			{	char temp[128]; sprintf(temp,"err savemob1 %d %d %d %s %s",m->nID,Slot,m->Slot,acc,m->AccountName);
				Log(temp,"-system",0);
				return TRUE;
			}
			if	(Slot != m->Slot || Slot != pAccountList[Idx].Slot)
			{	char temp[128]; sprintf(temp,"err savemob2 %d %d %d %d %s %s",m->nID,Slot,m->Slot,pAccountList[Idx].Slot,acc,m->AccountName);
				Log(temp,"-system",0);
			}
			if	(pAccountList[Idx].Login==FALSE)
			{	char temp[128]; sprintf(temp,"err savemob3 %d %d %d %s %s",m->nID,Slot,m->Slot,acc,m->AccountName);
				return TRUE; // 가능함.
			}
			while(1)
			{
    //            if(pAccountList[Idx].File.Char[Slot].snTribe!=m->MOB.snTribe) break;				//	게임중 종족이 바뀔수는 없다
				//if(pAccountList[Idx].File.Char[Slot].byFace!=m->MOB.byFace) break;					//  게임중 얼굴이 바뀔수는 없다.
				//if(pAccountList[Idx].File.Char[Slot].byHead!=m->MOB.byHead) break;					//  게임중 머리모양이 바뀔수는 없다
				if(m->MOB.sHeart<0||m->MOB.sMind<0||m->MOB.sMuscle<0||m->MOB.sNerves<0) break;		//	게임중 차크라가 0보다 작아질 수는 없다
				if(m->MOB.byLevel<0) break;	// 게임중 레벨이 0보다 작아질수는 없다
				bContinue=true; break;
			}
			if(bContinue) pAccountList[Idx].File.Char[Slot]=m->MOB;						//	정상적일 경우 케릭터의 데이터를 저장한다.
			else
			{	char temp[128]; sprintf(temp,"err savenquit3 Broken data %d %d %d %s %s",m->nID,Slot,m->Slot,acc,m->AccountName);
				Log(temp,"-system",0);
			}
            memcpy(pAccountList[Idx].File.Cargo,m->Cargo, sizeof(m->Cargo));
			memcpy(pAccountList[Idx].File.dwTimeStamp, m->dwTimeStamp, sizeof(pAccountList[Idx].File.dwTimeStamp));
			pAccountList[Idx].File.Coin = m->Coin;

			DBWriteAccount(&pAccountList[Idx].File);
		}	break;
		case SSP_REQ_SAVE_QUIT:
		{   S_SSP_REQ_SAVE_QUIT *m = (S_SSP_REQ_SAVE_QUIT*) Msg;
			
			int Idx = GetIndex(conn,m->nID);
			pAccountList[Idx].File.AccountName[ACCOUNTNAME_LENGTH-1]=0;
			pAccountList[Idx].File.AccountName[ACCOUNTNAME_LENGTH-2]=0;
			char acc[128]; strncpy(acc,pAccountList[Idx].File.AccountName,ACCOUNTNAME_LENGTH);
	
		    
			int Slot = -1; bool bContinue=false;
			for(int n=0; n<MOB_PER_ACCOUNT; n++)
			{	if(strcmp(m->MOB.szName, pAccountList[Idx].File.Char[n].szName) == 0) Slot = n;
			}
			if	(Slot<0||Slot>=MOB_PER_ACCOUNT)
			{	char temp[128]; sprintf(temp,"err savenquit2 %d %d %d %s %s",m->nID,Slot,m->Slot,acc,m->AccountName);
				Log(temp,"-system",0);
                RemoveAccountList(Idx);
				return TRUE;
			}
			
			m->AccountName[ACCOUNTNAME_LENGTH-1]=0;
			m->AccountName[ACCOUNTNAME_LENGTH-2]=0;
			if (strncmp(m->AccountName,acc,ACCOUNTNAME_LENGTH))
			{  char temp[128]; sprintf(temp,"err savenquit1 %d %d %d %s %s",m->nID,Slot,m->Slot,acc,m->AccountName);
				Log(temp,"-system",0);
				//원래는 이부분에서 해당 파일을 열고, 해당 슬롯과 카고를 저장하거나 저장하지 말아야 한다.
                RemoveAccountList(Idx);
				return TRUE;
			}
			if	(pAccountList[Idx].Login==FALSE)
			{	char temp[128]; sprintf(temp,"err savenquit3 %d %d %d %s %s",m->nID,Slot,m->Slot,acc,m->AccountName);
				Log(temp,"-system",0);
				return TRUE;
			}

			while(1)
			{
    //            if(pAccountList[Idx].File.Char[Slot].snTribe!=m->MOB.snTribe) break;				//	게임중 종족이 바뀔수는 없다
				//if(pAccountList[Idx].File.Char[Slot].byFace!=m->MOB.byFace) break;					//  게임중 얼굴이 바뀔수는 없다.
				//if(pAccountList[Idx].File.Char[Slot].byHead!=m->MOB.byHead) break;					//  게임중 머리모양이 바뀔수는 없다
				if(m->MOB.sHeart<0||m->MOB.sMind<0||m->MOB.sMuscle<0||m->MOB.sNerves<0) break;		//	게임중 차크라가 0보다 작아질 수는 없다
				if(m->MOB.byLevel<0) break;	// 게임중 레벨이 0보다 작아질수는 없다
				bContinue=true; break;
			}

			if(bContinue) pAccountList[Idx].File.Char[Slot]=m->MOB;						//	정상적일 경우 케릭터의 데이터를 저장한다.
			else
			{	char temp[128]; sprintf(temp,"err savenquit3 Broken data %d %d %d %s %s",m->nID,Slot,m->Slot,acc,m->AccountName);
				Log(temp,"-system",0);
			}

			memcpy(pAccountList[Idx].File.Cargo,m->Cargo, sizeof(STRUCT_ITEM) * MAX_CARGO);
			memcpy(pAccountList[Idx].File.dwTimeStamp, m->dwTimeStamp, sizeof(pAccountList[Idx].File.dwTimeStamp));
			pAccountList[Idx].File.Coin = m->Coin;
			DBWriteAccount(&pAccountList[Idx].File);
			DBExportAccount(&pAccountList[Idx].File);

            RemoveAccountList(Idx);
			SendDBSignal(conn,m->nID,SSP_RESP_SAVE_QUIT);  
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			for (int i=0;i<MAX_ADMIN;i++)
			{   if ( /*pAdmin[i].Level<=2 || */ pAdmin[i].DisableID==0) continue;
	  		    if (pAdmin[i].DisableID==Idx) {DisableAccount(i,acc);break;}// Disable Account // 
			}

             /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} break;
		/////////////////////////////////////////////////////////////////////
		//       캐랙터 삭제                           
		/////////////////////////////////////////////////////////////////////
		case SSP_REQ_CHAR_REMOVE:
		{    
			S_SSP_REQ_CHAR_REMOVE * m = (S_SSP_REQ_CHAR_REMOVE *) Msg;
            S_SSP_RESP_CHAR_REMOVE sm; sm.wType = SSP_RESP_CHAR_REMOVE; sm.nID = m->nID;
			sm.wPDULength = sizeof(S_SSP_RESP_CHAR_REMOVE) - sizeof(HEADER);
            int Idx  = GetIndex(conn,m->nID);
			int nSlot = -1;
			STRUCT_MOB *mob = NULL;
			for(int i=0;i<MOB_PER_ACCOUNT;i++)
			{	mob = &pAccountList[Idx].File.Char[i];
			if(!strcmp(mob->szName,m->szCharName))
			{	nSlot=i;
				break;
			}
			}
			if (nSlot == -1)
			{	sm.byResult = 2;//캐릭터 삭제실패
				pUser[conn].cSock.SendOneMessage((char *)&sm,sizeof(sm));
				return TRUE;
			}
			char Temp[255];
			if(mob->nGuildID)	//	길드가입시 자동탈퇴 시킨다.
			{	char pMaster[SZNAME_LENGTH] = {0,0,0,};
				int	ret = RemoveGuildMember(mob->nGuildID,mob->szName,pMaster);
				if	(ret!=-1)
				{	MSG_RemoveGuildMember sm; sm.wType=_MSG_RemoveGuildMember;
					sm.byRemoveType=eGuild_Remove_me; sm.GuildID=mob->nGuildID;
					sm.wPDULength=sizeof(MSG_RemoveGuildMember)-sizeof(HEADER);
					strncpy(sm.CharacterName, mob->szName, SZNAME_LENGTH);
					if(ret!=MAX_GUILD_MEMBER)		//	길드장이 바뀌었을 경우
					{	MSG_GuildSetRanking nm; nm.wType=_MSG_GuildSetRanking;
						nm.wPDULength=sizeof(MSG_GuildSetRanking)-sizeof(HEADER);
						strncpy(nm.CharacterName, pMaster, SZNAME_LENGTH);
						nm.nGuildID=mob->nGuildID; nm.GuildRank=eGuildMaster;
						nm.byDummy=0; nm.snDummy=0;
						SendToAll((MSG_STANDARD*)&nm);
						char temp[256];sprintf(temp,"Change Guildmaster to [%s] GuildID:%d",pMaster, mob->nGuildID);
						Log(temp,"-system",0);
					}

					char temp[256];sprintf(temp,"Remove Guildmember:[%s] GuildID:%d",mob->szName, mob->nGuildID);
					Log(temp,"-system",0);
					SendToAll((MSG_STANDARD*)&sm);
				}
			}

			DeleteCharacter(mob->szName,pAccountList[Idx].File.AccountName);
			sprintf(Temp,"delete char [%s]",mob->szName);
			Log(Temp,pAccountList[Idx].File.AccountName,0);
			memset(mob, 0, sizeof(STRUCT_MOB));
			DBWriteAccount(&pAccountList[Idx].File);
			sm.byResult = 0;//캐릭터 삭제성공
			pUser[conn].cSock.AddMessage((char *)&sm,sizeof(sm));

			S_SSP_RESP_CHAR_LIST sel;
			DBGetSelChar(&sel,&pAccountList[Idx].File);
			sel.nID = m->nID; 
			pUser[conn].cSock.SendOneMessage((char*)&sel, sizeof(S_SSP_RESP_CHAR_LIST));
		}	break;
		case SSP_REQ_WHISPER_CHAT:
		{	S_SSP_REQ_WHISPER_CHAT * m = (S_SSP_REQ_WHISPER_CHAT *) Msg;

			int nOheridx	= GetIndexFromName(m->szDestName);
			S_SSP_RESP_WHISPER_CHAT sm;	sm.wType=SSP_RESP_WHISPER_CHAT;
			sm.nID=m->nID; sm.byTrimuriti=m->byTrimuriti;
			strncpy(sm.szName, m->szDestName, SZNAME_LENGTH);

			if(nOheridx == 0)	//	상대방이 비접속중일때
			{	sm.byResult = REPLY_WHISPER_CHAR_FAIL;
			}
			else				//	상대방이 접속중일때
			{	int slot = pAccountList[nOheridx].Slot;
				int nStatus = (int)pAccountList[nOheridx].File.Char[slot].byStatus;
				if(nStatus & 0x01) 
				{	sm.byResult = REPLY_WHISPER_REJECT;
				}
				else
				{
					S_SSP_NOTIFY_WHISPER_CHAT nm;	nm.wType=SSP_NOTIFY_WHISPER_CHAT;
					int nServer = nOheridx/MAX_USER;	nm.nID=nOheridx%MAX_USER;
					strncpy(nm.szName, m->szSourName, SZNAME_LENGTH);
					strncpy((char*)nm.szMsg, (char*)m->szMsg, MAX_CHAT_LENGTH);
					nm.byTextColor=m->byTextColor; nm.byBgColor=m->byBgColor;
					nm.byTrimuriti=m->byTrimuriti;
					pUser[nServer].cSock.SendOneMessage((char*)&nm, sizeof(nm));

					sm.byResult=REPLY_ACK_OK;	
					sm.byTextColor=m->byTextColor; sm.byBgColor=m->byBgColor;
					strncpy((char*)sm.szMsg, (char*)m->szMsg, MAX_CHAT_LENGTH);
				}
			}

			pUser[conn].cSock.SendOneMessage((char*)&sm, sizeof(S_SSP_RESP_WHISPER_CHAT));
		}	break;
		//case SSP_REQ_BROADCAST:
		//{	S_SSP_REQ_BROADCAST * m = (S_SSP_REQ_BROADCAST *) Msg;

		//	int idx  = GetIndex(conn,m->nID);
		//	S_SSP_NOTIFY_BROADCAST sm; sm.wType=SSP_NOTIFY_BROADCAST;
		//	sm.byMsgType=m->byMsgType; sm.wPDULength = sizeof(S_SSP_NOTIFY_BROADCAST)-sizeof(HEADER);
		//	sm.byTextColor=m->byTextColor; sm.byBgColor=m->byBgColor; sm.byTrimuriti=m->byTrimuriti;
		//	strncpy((char*)sm.szMsg, (char*)m->szMsg, MAX_NOTIFY_LENGTH);
		//	strncpy(sm.szName, pAccountList[idx].File.Char[pAccountList[idx].Slot].szName, SZNAME_LENGTH);

		//	SendToAll((MSG_STANDARD *) &sm);
		//}	break;
		case _MSG_Chat:
		case _MSG_Broadcast:
		{	SendToAll(std);
		}	break;
		case SSP_REQ_APPEAL_CHAT:
		{	S_SSP_REQ_APPEAL_CHAT * m = ( S_SSP_REQ_APPEAL_CHAT * ) Msg;
			MSG_NPAppeal sm; sm.wType = _MSG_NPAppeal;
			int idx  = GetIndex(conn,m->nID);
			strncpy(sm.szAccountName,pAccountList[idx].File.AccountName,ACCOUNTNAME_LENGTH);
			strncpy(sm.szCharName,pAccountList[idx].File.Char[pAccountList[idx].Slot].szName,SZNAME_LENGTH);
			strncpy(sm.szMsg,m->szMsg,MAX_CHAT_LENGTH);
			
			BOOL bResult = FALSE;
			for ( int i = 0 ; i < MAX_ADMIN ; i++ )
			{
				bResult |= pAdmin[i].cSock.SendOneMessage((char*)&sm,sizeof(MSG_NPAppeal));
			}

			S_SSP_RESP_APPEAL_CHAT rm; rm.wType = SSP_RESP_APPEAL_CHAT;rm.nID = m->nID;
			rm.byResult = (bResult) ? 0 : 1;
			strncpy(rm.szMsg,m->szMsg,MAX_CHAT_LENGTH);
			pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SSP_RESP_WHISPER_CHAT));
		}	break;
		case SSP_REQ_CHARACTER_SEARCH:
		{	S_SSP_REQ_CHARACTER_SEARCH * m = ( S_SSP_REQ_CHARACTER_SEARCH * ) Msg;
			S_SSP_RESP_CHARACTER_SEARCH sm; sm.wType = SSP_RESP_CHARACTER_SEARCH;
			sm.nID = m->nID;

			int idx = GetIndexFromName(m->szCharName);
			if ( idx == 0 ) sm.byResult = 1;
			else
			{
				sm.byResult = 0;
				sm.byZone = ( idx / MAX_USER ) + 1;
				strncpy(sm.szAccountID,pAccountList[idx].File.AccountName,ACCOUNTNAME_LENGTH);
				strncpy(sm.szCharName,m->szCharName,SZNAME_LENGTH);
			}

			pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(S_SSP_RESP_CHARACTER_SEARCH));
		}	break;
		case _MSG_GMMode:
		{	MSG_GMMode* m = (MSG_GMMode*)Msg;

			//	대상자가 접속하지 않았을 경우
			int idx = GetIndexFromName(m->szCharName);
			if ( idx == 0 ) 
			{	m->byResult = S_FALSE;
				pUser[conn].cSock.SendOneMessage((char*)m,sizeof(MSG_GMMode));
				return FALSE;
			}

			//	대상자가 접속하고 있을 경우
			int nServer=( idx / MAX_USER ) + 1;
			MSG_GMMode_Notify sm; sm.wType=_MSG_GMMode_Notify;
			sm.byGMMode=m->byGMMode; sm.nID=idx%MAX_USER;
			pUser[nServer].cSock.SendOneMessage((char*)&sm,sizeof(MSG_GMMode_Notify));
		}	break;
		case _MSG_GMMoveToPlayer:
		{	MSG_GMMoveToPlayer* m = (MSG_GMMoveToPlayer*)Msg;

			//	대상자가 접속하지 않았을 경우
			int idx = GetIndexFromName(m->szCharName);
			if ( idx == 0 ) 
			{	m->byZone = 0;
				pUser[conn].cSock.SendOneMessage((char*)m,sizeof(MSG_GMMoveToPlayer));
				return FALSE;
			}

			//	대상자가 접속하고 있을 경우
			m->byZone=( idx / MAX_USER ) + 1;
			pUser[conn].cSock.SendOneMessage((char*)m,sizeof(MSG_GMMoveToPlayer));
		}	break;
		case _MSG_GMKickPlayer:
		{	MSG_GMKickPlayer* m = (MSG_GMKickPlayer*)Msg;
			int idx = GetIndexFromName(m->szCharName);
            if ( idx == 0 )
			{	m->nResult = 1;
				pUser[conn].cSock.SendOneMessage((char*)m,sizeof(MSG_GMKickPlayer));
				return FALSE;
			}
			m->nResult = 0;
			pUser[conn].cSock.SendOneMessage((char*)m,sizeof(MSG_GMKickPlayer));
			SendDBSavingQuit(idx,0);
		}	break;
		case _Msg_TrimuritiStatus:
		{	Msg_TrimuritiStatus* m = (Msg_TrimuritiStatus*)Msg;

			m->iTrimuritiCount[0] = m_iTrimuriti[0][24];
			m->iTrimuritiCount[1] = m_iTrimuriti[1][24];
			m->iTrimuritiCount[2] = m_iTrimuriti[2][24];
			
			pUser[conn].cSock.SendOneMessage((char*)m,sizeof(Msg_TrimuritiStatus));
		}	break;
		case _Msg_BramanBonus:
		{	SendToAll((MSG_STANDARD*)Msg);
		}	break;

/////////////////////////////////////////////////////////////////////
	 } 

     return TRUE;
}




//////////////////////////////////////////////////////////////////////////
//
//             FUNCTIONS
//
//  SendDBMessage (conn,클라이언트ID,메시지)     : 클라이언트에게 메시지 직접 통과 
//  
//////////////////////////////////////////////////////////////////////////

BOOL CFileDB::SendDBSignal(int svr,unsigned short id, unsigned short signal)
{    MSG_STANDARD sm; sm.wType = signal;
     sm.nID = id;      sm.wPDULength = sizeof(sm) - sizeof(HEADER);
     pUser[svr].cSock.SendOneMessage((char*)&sm,sizeof(sm));
	 return TRUE;
}
BOOL CFileDB::SendDBSignalParm(int svr,unsigned short id, unsigned short signal,int parm)
{    MSG_STANDARDPARM sm; sm.wType = signal;
     sm.nID = id;          sm.wPDULength = sizeof(sm) - sizeof(HEADER);
	 sm.Parm = parm;
     pUser[svr].cSock.SendOneMessage((char*)&sm,sizeof(sm));
	 return TRUE;
}
BOOL CFileDB::SendDBSignalParm2(int svr,unsigned short id, unsigned short signal,int parm1,int parm2)
{    MSG_STANDARDPARM2 sm; sm.wType = signal;
     sm.nID = id;          sm.wPDULength = sizeof(sm) - sizeof(HEADER);
	 sm.Parm1 = parm1;
	 sm.Parm2 = parm2;
     pUser[svr].cSock.SendOneMessage((char*)&sm,sizeof(sm));
	 return TRUE;
}
BOOL CFileDB::SendDBSignalParm3(int svr,unsigned short id, unsigned short signal,int parm1,int parm2,int parm3)
{    MSG_STANDARDPARM3 sm; sm.wType = signal;
     sm.nID = id;          sm.wPDULength = sizeof(sm) - sizeof(HEADER);
	 sm.Parm1 = parm1;
	 sm.Parm2 = parm2;
	 sm.Parm3 = parm3;
     pUser[svr].cSock.SendOneMessage((char*)&sm,sizeof(sm));
	 return TRUE;
}

BOOL CFileDB::SendDBMessage(int svr,unsigned short id, char * msg)
{    MSG_MessagePanel sm; sm.wType = _MSG_DBMessagePanel;  
     sm.nID = id;          sm.wPDULength = sizeof(MSG_MessagePanel) - sizeof(HEADER);
     strcpy(sm.String,msg);
     pUser[svr].cSock.SendOneMessage((char*)&sm,sizeof(MSG_MessagePanel));
	 return TRUE;
}

//void CFileDB:endDBSavingQuit(int Idx,int mode)
//{
//	int conn = Idx/MAX_USER;
//	int id   = Idx%MAX_USER;
//	// Idx바운터리 채크 
//    MSG_DBSavingQuit sm; sm.Type = _MSG_DBSavingQuit;
//	sm.ID = id;      sm.Size = sizeof(MSG_DBSavingQuit);
//	sm.Mode = mode;
//    memcpy(sm.AccountName,pAccountList[Idx].File.Account.AccountName,ACCOUNTNAME_LENGTH);
//    pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(MSG_DBSavingQuit));
//    return;
//}

/*
BOOL CFileDB::SendDBCloseNothing(int svr,unsigned short id)
{    MSG_STANDARD sm; sm.Type= _MSG_DBCloseNothing;
     sm.ID = id;            sm.Size = sizeof(MSG_DBCloseNothing);
	 pUser[svr].cSock.SendOneMessage((char*)&sm,sizeof(MSG_STANDBCloseNothing));
	 return TRUE;
}
*/
void CFileDB::AddAccountList(int Idx )
{ 
	if (pAccountList[Idx].Login==TRUE)
	{  Log("err addAccountlist - already added",pAccountList[Idx].File.AccountName,0);
	return ;
	}

    int conn = Idx/MAX_USER;
	pUser[conn].Count++;


	pAccountList[Idx].Login = TRUE;
	pAccountList[Idx].Slot  = -1;
	//Log("AddAccountList","Slot = -1");
	//File은 update하지 않는다. (Add를 부르기 전에 기 세팅했어야 한다.)

	//m_mapAccTable.insert( std::map<char*,int,HTStr>::value_type( pAccountList[Idx].File.AccountName, Idx ) );

	return;
}

void CFileDB::RemoveAccountList(int Idx)
{ 
	if (pAccountList[Idx].Login==FALSE) 
	{  //Log("어카운트 리스트 지운거 또지우기 발생!","처리하지 않았음");
	//Log("RemoveAccount를 시도했으나 이미 LOGOFF상태임",pAccountList[Idx].File.AccountName);
	return;
	}

	int slot = pAccountList[Idx].Slot;
	//if	(slot>=0&&slot<MOB_PER_ACCOUNT) 
	//{	std::map<char*,int,HTStr>::iterator it = m_mapCharTable.find( pAccountList[Idx].File.Char[slot].szName );
	//	if ( it != m_mapCharTable.end() )
	//	{	m_mapCharTable.erase( it );
	//	}
	//}

	//std::map<char*,int,HTStr>::iterator it = m_mapAccTable.find( pAccountList[Idx].File.AccountName );
	//if ( it != m_mapAccTable.end() )
	//{	m_mapAccTable.erase( it );
	//}

	// 사실 이건 발생할수 있다.
	// 접속해 있을때 다른곳에서 끊기를 요청.
	// 게임서버에게 SavingQuit을 요청해서 게임서버가 SaveMobAndQuit를 날리고,
	// 이게 처리되어서 Empty가 되는 순간,
    // 사용자의 재요청에 의한 SaveMobAndQuit가 도착하면 
    int conn = Idx/MAX_USER;
	pUser[conn].Count--;


	pAccountList[Idx].Login = FALSE;
	pAccountList[Idx].Slot  = -1;
    //Log("RemoveAccountList","Slot = -1");
	memset(&pAccountList[Idx].File,0,sizeof(pAccountList[Idx].File));
	return;
}

BOOL CFileDB::CreateCharacter(char * ac, char *ch)
{
	
     char temp[128]; char First[128];BASE_GetFirstKey(ch,First);
	 sprintf(temp,"./char/%s/%s.TCD",First,ch);
     int Handle = open( temp, _O_RDONLY | _O_BINARY , NULL );
	 if (Handle!=-1)
	 {  close(Handle);
	    return FALSE;
	 }
	 close(Handle);
     
     Handle = open( temp, _O_CREAT | _O_RDWR | _O_TEXT , _S_IREAD | _S_IWRITE );
	 if  (Handle==-1)
	 {   if (errno==EEXIST) {Log("err createchar EEXIST",ch,0);return FALSE;}  // _O_EXCL 일때 이미 파일이 있는경우
         if (errno==EACCES) {Log("err createchar EACCES",ch,0);return FALSE;}  // readonly를 쓰려고 한경우, 쉐어모드가 불가인경우, 디렉토리가 invalid
         if (errno==EINVAL) {Log("err createchar EINVAL",ch,0);return FALSE;}  // invalid oflag or pmode argument
	     if (errno==EMFILE) {Log("err createchar EMFILE",ch,0);return FALSE;}  // 파일 핸들이 없다.
	     if (errno==ENOENT) {Log("err createchar ENOENT",ch,0);return FALSE;}  // File or Path not found
		 Log("err createchar UNKNOWN",ch,0);
         return FALSE;
	 }
	 write(Handle,ac,ACCOUNTNAME_LENGTH);
	 close(Handle);
	 return TRUE;
}

BOOL CFileDB::DeleteCharacter(char * ch, char *account)
{
	 char temp[128]; char First[128];BASE_GetFirstKey(ch,First);
	 sprintf(temp,"./char/%s/%s.TCD",First,ch);

	 WIN32_FIND_DATA oFindData;
	 HANDLE hFindFile = FindFirstFile( temp, &oFindData );
     
	 if ( hFindFile == INVALID_HANDLE_VALUE ) return FALSE;
	 FindClose( hFindFile );

	 if ( g_eCountryID == eCountryTaiwan )
	 {
		 //////////////////////////////////////////////////////////////////////////
		 FILETIME ftLocal;
		 SYSTEMTIME sysTime;
		 GetSystemTime( &sysTime );
		 SystemTimeToFileTime( &sysTime, &ftLocal );
		 ULONGLONG ulCreate, ulNow;
		 memcpy ( &ulNow, &ftLocal, sizeof(ULARGE_INTEGER) );
		 memcpy ( &ulCreate, &oFindData.ftCreationTime, sizeof( ULARGE_INTEGER ) );
		 if ( ulNow < ulCreate + 2592000000 ) return FALSE;
		 //////////////////////////////////////////////////////////////////////////
	 }

	 int ret = DeleteFile(temp);

	 if ( ret == TRUE )
	 {	char szOldFilename[128], szNewFilename[128];
		struct tm when;
		time_t now;
		time(&now); when= *localtime(&now);
		BASE_GetFirstKey(account,First);
		sprintf(szOldFilename,"./account/%s/%s.TAD",First,account);
		sprintf(szNewFilename, "./Delete_Backup/%s%02d%02d%02d_%02d%02d%02d.TAD", ch, when.tm_year, when.tm_mon, when.tm_mday, when.tm_hour, when.tm_min, when.tm_sec);
		CopyFile(szOldFilename, szNewFilename, FALSE);
	 }

	 return ret;
}


int CFileDB::GetIndex(int server, int id)
{
    int ret = server * MAX_USER + id;
	return ret;
}

int CFileDB::GetIndex(char * account)
{
	//std::map<char*,int,HTStr>::iterator it = m_mapAccTable.find( account );
	//if ( it != m_mapAccTable.end() ) return it->second;

    for (int i=0;i<MAX_DBACCOUNT;i++)
	{   if (pAccountList[i].Login==0) continue;
		if (!strcmp(pAccountList[i].File.AccountName, account)) 
		{	/*char temp[256];
			sprintf(temp, "err GetIndex:%s not find in map, but find in loop", account);
			Log(temp, account, 0);*/
			return i;
		}
	}

	return 0;
}

int CFileDB::GetIndexFromName(char * szMob)
{
	//std::map<char*,int,HTStr>::iterator it = m_mapCharTable.find( szMob );
	//if ( it != m_mapCharTable.end() ) return it->second;

    for (int i=0;i<MAX_DBACCOUNT;i++)
	{   if (pAccountList[i].Login==0) continue;
		int slot = pAccountList[i].Slot;
		if	(slot<0||slot>=MOB_PER_ACCOUNT) continue;
        if	(!strcmp(pAccountList[i].File.Char[slot].szName, szMob)) 
		{	/*char temp[256];
			sprintf(temp, "err GetIndexFromName:%s not find in map, but find in loop", szMob);
			Log(temp, pAccountList[i].File.AccountName, 0);*/
			return i;
		}
	}

	return 0;
}

void CFileDB::SendDBSavingQuit(int Idx,int mode)
{
	int conn = Idx/MAX_USER;
	int id   = Idx%MAX_USER;
	// Idx바운터리 채크 

    MSG_DBSavingQuit sm; sm.wType = _MSG_DBSavingQuit;
	sm.nID = id;     sm.wPDULength = sizeof(MSG_DBSavingQuit) - sizeof(HEADER);
	sm.Mode = mode;
    memcpy(sm.AccountName,pAccountList[Idx].File.AccountName,ACCOUNTNAME_LENGTH);
    pUser[conn].cSock.SendOneMessage((char*)&sm,sizeof(MSG_DBSavingQuit));
    return;
}
// 이것에 대한 CNF (MOB 포함 또는 Login Flag만 Reset)






////////////////////////////////////////////////////////////////////////////////////
// 어카운트 관련 펑션, Create , Update , Read , SetLogin
BOOL CFileDB::DBWriteAccount(STRUCT_ACCOUNTFILE * account)
{
	char *accname = account->AccountName;

	if ( accname[0] == NULL )
	{
		Log("err writeacctount NULL_ACCOUNT", accname, 0);
		return FALSE;
	}

    char temp[128]; char First[128];BASE_GetFirstKey(accname,First);
	sprintf(temp,"./account/%s/%s.TAD",First,accname);

    int Handle = open( temp, _O_CREAT | _O_RDWR | _O_BINARY , _S_IREAD | _S_IWRITE );
	if (Handle==-1)
	{ 
		if (errno==EEXIST) {Log("err writeaccount EEXIST",accname,0);return FALSE;}  // _O_EXCL 일때 이미 파일이 있는경우
		if (errno==EACCES) {Log("err writeaccount EACCES",accname,0);return FALSE;}  // readonly를 쓰려고 한경우, 쉐어모드가 불가인경우, 디렉토리가 invalid
		if (errno==EINVAL) {Log("err writeaccount EINVAL",accname,0);return FALSE;}  // invalid oflag or pmode argument
		if (errno==EMFILE) {Log("err writeaccount EMFILE",accname,0);return FALSE;}  // 파일 핸들이 없다.
		if (errno==ENOENT) {Log("err writeaccount ENOENT",accname,0);return FALSE;}  // File or Path not found
		Log("err writeaccount UNKNOWN",accname,0);
		return FALSE;
	}
	int ret = _lseek(Handle,0,SEEK_SET);
	if (ret==-1)
	{	Log("err writeaccount lseek fail",accname,0);  // _O_EXCL 일때 이미 파일이 있는경우
		close(Handle); 
		return FALSE;
	}
	ret = _write(Handle,account,sizeof(STRUCT_ACCOUNTFILE));  // text모드시 CTRL+Z 는 end-of-file이 된다.
	if (ret==-1)
	{	close(Handle);   // Disk Full 또는 기타 I/O 에러.
		Log("CreateAccount write fail",accname,0);
		if (errno==EEXIST) {Log("CreateAccount EEXIST",accname,0);return FALSE;}  // _O_EXCL 일때 이미 파일이 있는경우
		if (errno==EACCES) {Log("CreateAccount EACCES",accname,0);return FALSE;}  // readonly를 쓰려고 한경우, 쉐어모드가 불가인경우, 디렉토리가 invalid
		if (errno==EINVAL) {Log("CreateAccount EINVAL",accname,0);return FALSE;}  // invalid oflag or pmode argument
		if (errno==EMFILE) {Log("CreateAccount EMFILE",accname,0);return FALSE;}  // 파일 핸들이 없다.
		if (errno==ENOENT) {Log("CreateAccount ENOENT",accname,0);return FALSE;}  // File or Path not found
		return FALSE;
	}
	close(Handle);
	return TRUE;
}
BOOL CFileDB::DBExportAccount(STRUCT_ACCOUNTFILE * account)
{
	if	(pUser[INDEXOFDAEMON-1].cSock.Sock!=NULL)
	{
		MSG_NPAccountInfo sm; ZeroMemory(&sm, sizeof(MSG_NPAccountInfo));
		BYTE byIndex=0; int nBrahmanPoint=0; BYTE byLevel=0;
		for(BYTE i=0;i<MOB_PER_ACCOUNT;i++)
		{	if(account->Char[i].nBramanPoint<nBrahmanPoint || account->Char[i].szName[0] == 0) continue;
			if(account->Char[i].nBramanPoint==nBrahmanPoint && account->Char[i].byLevel<byLevel) continue;
			byIndex=i;
			nBrahmanPoint=account->Char[i].nBramanPoint;
			byLevel=account->Char[i].byLevel;
		}
		if(account->Char[byIndex].nGuildID!=0)
		{	STRUCT_GUILD guild;
			if(ReadGuildFile(account->Char[byIndex].nGuildID,&guild))
			{	strncpy(sm.GuildName,guild.GuildName,GUILDNAME_LENGTH);
			}

			for(int i=0;i<MAX_GUILD_MEMBER;i++)
			{	if(strncmp(account->Char[byIndex].szName,guild.Member[i].MemberName,SZNAME_LENGTH)==0)
				{	sm.GuildRank=guild.Member[i].GuildRank;
				}
			}
		}
		memcpy( &sm.account, account, sizeof(STRUCT_ACCOUNTFILE) );
		sm.wType = _MSG_NPReqSaveAccount;
		sm.wPDULength = sizeof(sm)- sizeof(HEADER);
		// 나머지 값은 다 가비여도 상관없다
		int ret = pUser[INDEXOFDAEMON-1].cSock.SendOneMessage((char*)&sm,sizeof(sm));
		if	(ret==FALSE)
		{	Log("err exporting account",account->AccountName,0);
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CFileDB::DBReadAccount(STRUCT_ACCOUNTFILE * file,time_t *ptLastWrite/*= NULL*/)
{
	// blocking broken or cracked packet.
	 file->AccountName[ACCOUNTNAME_LENGTH-1]=0;
	 file->AccountName[ACCOUNTNAME_LENGTH-2]=0;
	 file->AccountPass[ACCOUNTPASS_LENGTH-1]=0;
	 file->AccountPass[ACCOUNTPASS_LENGTH-2]=0;
    // 다른 개체도 막아야 한다.
 	if(strlen(file->AccountName) < 4) return FALSE;

    char temp[128]; char First[128];BASE_GetFirstKey(file->AccountName,First);
    sprintf(temp,"./account/%s/%s.TAD",First,file->AccountName);

	file->ssn1 = 0;
	file->ssn2 = 0;
	ZeroMemory(file->dwTimeStamp, sizeof(file->dwTimeStamp) );

	if ( ptLastWrite != NULL )
	{	struct _finddata_t tFindData;
		int hFindFile = _findfirst(  temp, &tFindData );
		if ( hFindFile != -1 ) *ptLastWrite = tFindData.time_write;
		_findclose( hFindFile );
	}

    int Handle = open(temp, _O_RDONLY | _O_BINARY, NULL);
	if (Handle==-1)
	{	
#ifdef _ACCOUNTNAME_LENGTH_52BYTES_
		OLD_STRUCT_ACCOUNTFILE oldfile;
		char oldDir[128];
		sprintf(oldDir,"./old_account/%s/%s.TAD",First,file->AccountName);
		int oldhandle = open(oldDir,_O_RDONLY | _O_BINARY, NULL);
		if ( oldhandle == -1 ) return FALSE;
        
		read(oldhandle,&oldfile,sizeof(OLD_STRUCT_ACCOUNTFILE));
		strncpy(file->AccountName,oldfile.AccountName,OLD_ACCOUNTNAME_LENGTH);
		memcpy(file->AccountPass,oldfile.AccountPass,sizeof(OLD_STRUCT_ACCOUNTFILE)-OLD_ACCOUNTNAME_LENGTH);
		close(oldhandle);
		if ( !DBWriteAccount(file) ) return FALSE;
		DeleteFile(oldDir);
		int Handle = open(temp, _O_RDONLY | _O_BINARY, NULL);
#else
		if (errno==EINVAL) {Log("err readaccount EINVAL",file->AccountName,0);return FALSE;}  // invalid oflag or pmode argument
		if (errno==EMFILE) {Log("err readaccount EEMFILE",file->AccountName,0);return FALSE;}  // 파일 핸들이 없다.
		if (errno==ENOENT) {/*Log("ReadAccount ENOENT",file->AccountName);*/return FALSE;}  // File or Path not found
		Log("err readaccount UNKNOWN",file->AccountName,0);
		return FALSE;
#endif
	}
	int	sz = filelength(Handle);
	read(Handle,file,sz);
	close(Handle);
	return TRUE;
}






///////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_ILCHAT 7
char illegulname[NUM_ILCHAT][12] = 
{     "운영자"  ,"관리자"  ,"위드운영자"  ,"위드"  ,"임플",
      "위자드"  ,"어드민"  
};
BOOL CFileDB::DBCheckImpleName(char ** ilchat,char * Str)
{
     for (int j=0;j<NUM_ILCHAT;j++)
	 { 	 for (int i=0;i<ACCOUNTNAME_LENGTH;i++)
	     {   if (Str[i]==0||Str[i+1]==0||Str[i+2]==0||Str[i+3]==0) break;
             if (Str[i]==' '||Str[i+1]==' '||Str[i+2]==' '||Str[i+3]==' ') continue;
	         if (Str[i]==ilchat[j][0] && Str[i+1]==ilchat[j][1] &&
                 Str[i+2]==ilchat[j][2] && Str[i+3]==ilchat[j][3] &&
				 ilchat[j][4]==0) return 1;
			 if (ilchat[j][i+4]==0) continue;
	         if (Str[i]==ilchat[j][0] && Str[i+1]==ilchat[j][1] &&
                 Str[i+2]==ilchat[j][2] && Str[i+3]==ilchat[j][3] &&
                 Str[i+4]==ilchat[j][4] && Str[i+5]==ilchat[j][5] &&
				 ilchat[j][6]==0) return 1;
			 if (ilchat[j][i+6]==0) continue;
	         if (Str[i]==ilchat[j][0] && Str[i+1]==ilchat[j][1] &&
                 Str[i+2]==ilchat[j][2] && Str[i+3]==ilchat[j][3] &&
                 Str[i+4]==ilchat[j][4] && Str[i+5]==ilchat[j][5] &&
                 Str[i+6]==ilchat[j][6] && Str[i+7]==ilchat[j][7] &&
				 ilchat[j][8]==0) return 1;
		 }
	 }
	 return 0;

}



// 어카운트 만들기 관련.

           // 전체 로그인한 Account와 Character 의 어레이를 가진다.
           // [Account]:[Character]:[GameServer][User-IP]
           // Account가 Login되지 않은상태에서는 Character도 로그인 되지 않는다.
           // Character의 User-IP가 Account의 User-IP와 틀려도 로그인 되지 않는다.
           // Account가 Login된 상태에서 다시 Account Login 요청이 들어오면 
           // 이전 접속을 끊도록 게임서버에게 알리고 컨펌후에 끊는다.
           // 캐랙터가 Login된 상태에서 다시 캐랙터 Login이 들어오면 역시 G-Srv에게 
           // 이전 접속을 끊도록 (Char Save) 후 접속을 받는다.
           // Account만 로그인 된 상태에서 Account와 다른 서버로 Char로그인 이 들어와도 역시 접속 불가.

           // 1. account 디렉토리에 계정이 존재하는지 확인한다. // 
		   //    => 존재하면 실패를 게임 서버에 알린다(MSG_DBMESSAGE). (MSG_CLOSENOTHING). 끝(x). 
           //    캐랙터 만들기는 접속 직후, Create를 보내기 때문에, G-Srv가 Client의 접속을 끊어 주어야 한다.
		   //
           // 2. 존재하지 않으면 주민번호중복 여부나 과금 결제 여부를 체크 한다.
           //    => 실패시 상동. 
		   //    주민번호 중복 체크 방법 
           //    1)체크하지 않는다.
		   //    2)SSN 폴더를 만들어서 0Byte파일을 만든다.
		   //    3)MS-SQL을 사용한다. (쓰레딩 풀 필요)
		   //    4)일일히 오픈해서 체크한다.
		   //    5)파일 하나를 SSN테이블 쿼리용으로 만든다.
		   // 3. 리스트에 등록하고 바로 저장한다. (디폴트 값은 채워, CUser 클래스를 통째로 저장한다.)
	    
		   // 1.멀티 스레딩에 대비 파일을 쓰기로 CREATE | EXCL 로 연다.
		
           // 2. 주민번호중복, 과금 결재여부 체크 
           // 생략 
            
		   // 3. 파일 쓰기 성공시 리스트 등록
		   //char AccountName[ACCOUNTNAME_LENGTH];
		   //char AccountPass[ACCOUNTPASS_LENGTH];
		   //char RealName[REALNAME_LENGTH];
           //unsigned int SSN1;
		   //unsigned int SSN2;
           //char Email[EMAIL_LENGTH];
           //char Telephone[TELEPHONE_LENGTH];
           //char Address[ADDRESS_LENGTH];
// 파일을 읽기 전에 [읽고/쓰기]로 오픈 -> Charged
// 후 읽고 닫는다. 
//
// 파일이 이미 쓰기 오픈되어 있으면 읽고 쓰기 오픈이 실패한다.
// 파일 없음과 쓰기 오픈 실패의 구분이 가능한 file open 이 필요.
// CLI:    GSVR에 접속 시도
// GSVR:   DBSVR에 전달 
// DBSVR:  GSVR2에 종료 요청
// CLI:    [취소] -> GSVR: 클라이언트 닫기, DBSVR:이미 GSVR2의 종료는 확정(Nothing)		   
// GSVR:  1.x틱후 (RECONNECT
void CFileDB::DBGetSelChar(S_SSP_RESP_CHAR_LIST * sel,STRUCT_ACCOUNTFILE * file)
{

	memset(sel,0,sizeof(*sel));
	sel->wType = SSP_RESP_CHAR_LIST; 
 	for ( int i = 0 ; i < MOB_PER_ACCOUNT ; i++ )
	{
		memcpy( sel->sData[i].szCharName, file->Char[i].szName, SZNAME_LENGTH );
		if(sel->sData[i].szCharName[0]==0) continue;
		sel->sData[i].byFaceType	= file->Char[i].byFace;
		sel->sData[i].byHeadType	= file->Char[i].byHead;
		sel->sData[i].byTrimuriti	= file->Char[i].byTrimuriti;
		sel->sData[i].snTribe		= file->Char[i].snTribe;
		sel->sData[i].byTrimuritiClass = 0;
		sel->sData[i].nBrahmanPoint = file->Char[i].nBramanPoint;

		sel->sData[i].snChakraMuscle= file->Char[i].sMuscle;
		sel->sData[i].snChakraNerve	= file->Char[i].sNerves;
		sel->sData[i].snChakraHeart = file->Char[i].sHeart;
		sel->sData[i].snChakraSoul	= file->Char[i].sMind;

		sel->sData[i].snKarma		= file->Char[i].snKarma;
		sel->sData[i].byGMStatus	= file->Char[i].byGMStatus;;
		sel->sData[i].byClass1		= file->Char[i].byClass1;
		sel->sData[i].byClass2		= file->Char[i].byClass2;
		sel->sData[i].byLevel		= file->Char[i].byLevel;
		sel->sData[i].snDummy		= 0;

		if ( file->Char[i].byZone == 0 ) 
		{	file->Char[i].byZone = 1;
			file->Char[i].snX = -1;
			file->Char[i].snZ = -1;
		}

		sel->sData[i].LastZone		= file->Char[i].byZone;
		sel->sData[i].LastServerIP.S_un.S_addr = g_pServerListBin[ServerIndex][file->Char[i].byZone];
		sel->sData[i].LastServerPort=GAME_PORT; 

		sel->sData[i].Equip[eVisualEquipHelmet] = file->Char[i].Equip[eTNEqu_Helmet];
		sel->sData[i].Equip[eVisualEquipArmor] = file->Char[i].Equip[eTNEqu_Armor];
		sel->sData[i].Equip[eVisualEquipPants] = file->Char[i].Equip[eTNEqu_Pants];
		sel->sData[i].Equip[eVisualEquipShield] = file->Char[i].Equip[eTNEqu_Shield];
		sel->sData[i].Equip[eVisualEquipOneWeapon] = file->Char[i].Equip[eTNEqu_OneHandWeapon];
		sel->sData[i].Equip[eVisualEquipBoots] = file->Char[i].Equip[eTNEqu_Boots];
		sel->sData[i].Equip[eVisualEquipGloves] = file->Char[i].Equip[eTNEqu_Gloves];
		//memcpy( sel->sData[i].Equip, file->Char[i].Equip, sizeof(STRUCT_ITEM) * VISUAL_EQUIP );
	}
}
void CFileDB::GetAccountByChar(char *acc, char *cha)
{
	 acc[0]=0;
     char temp[128]; char First[128];BASE_GetFirstKey(cha,First);
	 sprintf(temp,"./char/%s/%s.TCD",First,cha);
     int Handle = open( temp, _O_RDONLY | _O_TEXT , NULL );
	 if (Handle==-1)
	 {  close(Handle);
	    return;
	 }
	 read(Handle,acc,ACCOUNTNAME_LENGTH);
	 close(Handle);
     return ;

}

void CFileDB::InitAccountList(int idx)
{	 
	 memset(&pAccountList[idx].File,0,sizeof(pAccountList[idx].File));  
}

void CFileDB::SetNewCharacter(  STRUCT_MOB *pMob, S_SSP_REQ_CHAR_CREATE * pData )
{
	STRUCT_ITEM a_DefItem[4]; ZeroMemory(a_DefItem, sizeof(a_DefItem));
	a_DefItem[0].snIndex = 4026 - HT_PARAMTYPE_ITEM_START + 1;
	a_DefItem[1].snIndex = 4001 - HT_PARAMTYPE_ITEM_START + 1;
	a_DefItem[2].snIndex = 4327 - HT_PARAMTYPE_ITEM_START + 1;
	a_DefItem[3].snIndex = 4111 - HT_PARAMTYPE_ITEM_START + 1;

	a_DefItem[0].byCount = 1; a_DefItem[0].snDurability = 3600;
	a_DefItem[1].byCount = 1; a_DefItem[1].snDurability = 4500;
	a_DefItem[2].byCount = 1; a_DefItem[2].snDurability = 5500;
	a_DefItem[3].byCount = 1; a_DefItem[3].snDurability = 2000;
    
	STRUCT_ITEM DefPotion; ZeroMemory(&DefPotion, sizeof(STRUCT_ITEM));
	DefPotion.snIndex = 7001 - HT_PARAMTYPE_ITEM_START + 1;

	// 일단 하드코딩, 추후에 파일을 만들어서 읽어들여 할 수 있도록 수정한다.
	pMob->byZone = 1;
	pMob->snX = -1;
	pMob->snZ = -1;
	pMob->byTrimuriti = pData->byTrimuriti;
	pMob->snTribe = pData->snTribe;
	pMob->byFace = pData->byFaceType;
	pMob->byHead = pData->byHeadType;
	pMob->byLevel = 1;
	pMob->nRupiah = 0;
	pMob->byInvenBag = 0;
	pMob->bySpecialName = 0;
	pMob->byInvenBag = 0;
	pMob->bySaveZone = 1;
	pMob->snKarma = 0;
	pMob->byGMStatus = 0;
	pMob->byClass1 = 0;
	pMob->byClass2 = 0;

	ZeroMemory( pMob->bySkill, sizeof( pMob->bySkill ) );
	ZeroMemory( pMob->byQuest, sizeof( pMob->byQuest ) );
	ZeroMemory( pMob->Inven, sizeof( pMob->Inven ) );
	ZeroMemory( pMob->Equip, sizeof( pMob->Equip ) );

	// 테스트용.. 일단 스킬 데이터를 다 Level 1로 설정한다.
	//memset( pMob->bySkill, 0x01, MAX_SKILL );

	switch(pData->snTribe)
	{
	case TRIBE_NAGA: // 나가, 킨나라
	case TRIBE_KINNARA:
		pMob->sMuscle = 12;
		pMob->sNerves = 10;
		pMob->sHeart = 11;
		pMob->sMind = 10;
		pMob->Inven[0] = a_DefItem[0];
		break;
	case TRIBE_ASURA: // 아수라, 락샤사
	case TRIBE_RAKSHASA:
		pMob->sMuscle = 11;
		pMob->sNerves = 12;
		pMob->sHeart = 10;
		pMob->sMind = 10;
		pMob->Inven[0] = a_DefItem[1];
		break;
	case TRIBE_YAKSA: // 야크사, 간다르바
	case TRIBE_GANDHARVA:
		pMob->sMuscle = 11;
		pMob->sNerves = 11;
		pMob->sHeart = 11;
		pMob->sMind = 10;
		pMob->Inven[0] = a_DefItem[2];
		break;
	case TRIBE_DEVA: // 데바, 가루다
	case TRIBE_GARUDA:
		pMob->sMuscle = 10;
		pMob->sNerves = 10;
		pMob->sHeart = 10;
		pMob->sMind = 13;
		pMob->Inven[0] = a_DefItem[3];
		break;
	}

	pMob->sMuscle += pData->byChakraMuscle;
	pMob->sNerves += pData->byChakraNerve;
	pMob->sHeart += pData->byChakraHeart;
	pMob->sMind += pData->byChakraSoul;

	pMob->nHP = 1000;
	pMob->nTP = 1000;

	pMob->byQuest[0] = 1;
}

void CFileDB::SendToAll(MSG_STANDARD * msg)
{
	for (int i=0;i<MAX_SERVER;i++)
	{	if	(pUser[i].Mode==USER_EMPTY || pUser[i].cSock.Sock==NULL) continue;
		pUser[i].cSock.SendOneMessage((char*)msg,msg->wPDULength+sizeof(HEADER));
	}
}

void CFileDB::CheckTrimuriti()
{
	int nHour = 0;
	int nSlot = 0;
	int nTri  = 0;

	struct tm when;
	time_t now;
	time(&now); when= *localtime(&now);
    nHour = when.tm_hour;

	FILE * fp = fopen("Trimuriti.dat","r");		//	old data loading
	if (fp==NULL)	//	파일이 없을 경우 파일을 만들어준다.
	{
		fp = fopen("Trimuriti.dat","w");
		if(fp==NULL) return;
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<24; j++) fprintf(fp, "%d ", 0);
			fprintf(fp, "\n", 0);
		}
		fclose(fp);

		for(i=0; i<3; i++) m_iTrimuriti[i][nHour] = 0;
	}	else
	{	
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<24; j++) fscanf(fp, "%d", &m_iTrimuriti[i][j]);
		}
		fclose(fp);
	}

	m_iTrimuriti[0][nHour] = 0;
	m_iTrimuriti[1][nHour] = 0;
	m_iTrimuriti[2][nHour] = 0;
	m_iTrimuriti[0][24]    = 0;
	m_iTrimuriti[1][24]    = 0;
	m_iTrimuriti[2][24]    = 0;

    for (int i=0;i<MAX_DBACCOUNT;i++)				//	hour data update
	{   if (pAccountList[i].Login==0) continue;
		nSlot = pAccountList[i].Slot;
		if(nSlot<0 || nSlot>=MOB_PER_ACCOUNT) continue;
		nTri = pAccountList[i].File.Char[nSlot].byTrimuriti;
		if(nTri<0 || nTri>eTNClan_Siva) continue;
		if(nTri==eTNClan_Brahma) m_iTrimuriti[0][nHour]++;
		else if(nTri==eTNClan_Vishnu) m_iTrimuriti[1][nHour]++;
		else if(nTri==eTNClan_Siva) m_iTrimuriti[2][nHour]++;
	}

	fp = fopen("Trimuriti.dat","w");			//	nem_iTrimuritig
	if (fp==NULL) return;
	
	for(i=0; i<3; i++)
	{
		for(int j=0; j<24; j++) 
		{	m_iTrimuriti[i][24] += m_iTrimuriti[i][j];
			fprintf(fp, "%d ", m_iTrimuriti[i][j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);

	if(nHour==4)		//	하루에 한번 4시가 되면 주신동접 통계를 존서버에로 통보한다.
	{
		Msg_TrimuritiStatus sm; sm.wType = _Msg_TrimuritiStatus;
		sm.iTrimuritiCount[0] = m_iTrimuriti[0][24];
		sm.iTrimuritiCount[1] = m_iTrimuriti[1][24];
		sm.iTrimuritiCount[2] = m_iTrimuriti[2][24];
		SendToAll((MSG_STANDARD*)&sm);
	}
}