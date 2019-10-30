#ifndef _CGUILD_
#define _CGUILD_
#include <windows.h>

#include "Basedef.h"
#include "CPSock.h"

//----------------------------------------------------------------------------------------------------------
#define GUILD_EMPTY     0   // 비어있다.
#define GUILD_CHARGED	1



class CGuild
{
public:
	public:
	int Mode;

	STRUCT_GUILD GUILD;

	// temporary values

	char  szGuildMaster[SZNAME_LENGTH];
	char  szCargoMember[SZNAME_LENGTH];
	short pMemberIndex[MAX_GUILD_MEMBER]; // #define MAX_GUILD_MEMBER 50

	int nAlliedID;

   public:
   	CGuild();
	~CGuild();

	void	Initialize();
	int		CreateGuild(int nLeader, MSG_CreateGuild* pData);

	int		GetEmptyGuild();
	char	GetLevel(char* pName);
	int		AddGuildMember(MSG_AddGuildMember* pData);
	int		RemoveGuildMember(char* szName);
	int		UpdateGuildMember(MSG_GuildUpdateMember* pData);
	int		UpdateGuildMemberRank(MSG_GuildSetRanking* pData);
	void	CheckGuildMaster();
	void	SetCargoLevel(BYTE byCargo1, BYTE byCargo2, BYTE byCargo3); 
	BOOL	IsUsableCargo(BYTE byLevel, WORD wIndex);
	void	GetCargoTime(DWORD* pdwTime1, DWORD* pdwTime2, DWORD* pdwTime3); 
	void	SetCargoTime(DWORD dwTime1, DWORD dwTime2, DWORD dwTime3); 
	bool	IsGuildManager( char* a_szName );
};

int GetGuildID				(char* pName);
int GetGuild				(int GuildID, bool bFlag=true);
int	ReadGuildFile			(int GuildID, CGuild* pstGuild);
int IsGuildMemberIn			(int nGuildID);

#endif