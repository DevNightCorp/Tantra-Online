#ifndef _CFILEDB_
#define _CFILEDB_
#include <windows.h>
#include "BaseDef.h"


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//                  USERFILE
//
// account : 어카운트 DB 폴더
// char    : 캐랙터 DB 폴더
//
//  
// account 와 char-name 은 ex-filename 이 가능한 한도에서 지원.
// ( * ? " ~ `) 불가 ,  ( ' ) 는 가능.       
// ID
// PASS
// 기타 프로파일
// 과금정보
// MOB Index
// 
// MOB1    // 1 K //
// MOB2    // 1 K //
// MOB3    // 1 K //
// MOB4    // 1 K //
// MOB5    // 1 K //
// MOB6    // 1 K //
//
//            total : 8K
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
/*
typedef struct 
{
////////// MSG_DBNewAccount
        char AccountName[ACCOUNTNAME_LENGTH];
	    char AccountPass[ACCOUNTPASS_LENGTH];
	    char RealName[REALNAME_LENGTH];
        unsigned int SSN1;
	    unsigned int SSN2;
        char Email[EMAIL_LENGTH];
        char Telephone[TELEPHONE_LENGTH];
        char Address[ADDRESS_LENGTH];
////////// 위 부분은 항상 BaseDEF의 MSG_DBNewAccount 와 일치시켜야 한다 .
		unsigned short GameServer;// conn이 게임서버인덱스다. 게임서버가 날리는 값은 무시하고 conn을 저장한다.
        char MobName[MOB_PER_ACCOUNT][MOBNAME_LENGTH];
		unsigned short Login;
}  STRUCT_ACCOUNT; 
*/

typedef struct _HTStr
{
	template<typename PtrType>
		bool operator()( PtrType pStr1, PtrType pStr2 ) const
	{
		int i = _stricmp( pStr1, pStr2 );
		if ( i < 0 )
			return ( TRUE );
		else
			return ( FALSE );
	}
} HTStr;

typedef struct
{    int  Login;
     int  Slot;
     STRUCT_ACCOUNTFILE File;
} STRUCT_ACCOUNTLIST;

class CFileDB
{
private:
	int m_iTrimuriti[3][25];	//	3주신의 24시간 접속자수(시간마다 체크한다), 25번째는 합계를 저장.

public:
    STRUCT_ACCOUNTLIST pAccountList[MAX_DBACCOUNT];
	//std::map<char*, int, HTStr> m_mapAccTable;
	//std::map<char*, int, HTStr> m_mapCharTable;

   	CFileDB();
	~CFileDB();
	void	InitGuild();
	BOOL   ProcessMessage			(char * Msg, int User);
    void   Remove					(void);
	BOOL   SendDBMessage			(int svr,unsigned short id, char * Msg);
	BOOL   SendDBSignal				(int svr,unsigned short id,unsigned short signal);
	BOOL   SendDBSignalParm			(int svr,unsigned short id, unsigned short signal,int parm);
	BOOL   SendDBSignalParm2		(int svr,unsigned short id, unsigned short signal,int parm1,int parm2);
	BOOL   SendDBSignalParm3		(int svr,unsigned short id, unsigned short signal,int parm1,int parm2,int parm3);

	BOOL   AddAccount(char *id,char*pass,int ssn1,int ssn2);
	BOOL   UpdateAccount(char *id,char*pass,int ssn1,int ssn2);
	BOOL	DBExportAccount(STRUCT_ACCOUNTFILE * account);
     
	int    GetIndex                  (char * account);                                  // -1 : 일치하는 어카운트 없음.
	int    GetIndex                  (int server ,int id);
	int	   GetIndexFromName			 (char * szMob);
    void   AddAccountList            (int Idx);   // -1 : fail, empty를 찾아 채우고 idx리턴
	void   RemoveAccountList         (int Idx);
	void   SendDBSavingQuit          (int Idx,int mode);
     
	// 사용자 계정 (account 디렉토리)
	BOOL   DBWriteAccount            (STRUCT_ACCOUNTFILE * account);
    BOOL   DBReadAccount             (STRUCT_ACCOUNTFILE * account,time_t *ptLastWrite = NULL);

	// Account의 MOB을 Charactor라 명명. ( char 디렉토리)
    BOOL   DBCheckImpleName          (char **source,char * name);
    void   DBGetSelChar              (S_SSP_RESP_CHAR_LIST * sel,STRUCT_ACCOUNTFILE * file);
	void   InitAccountList           (int idx);
    
	BOOL   CreateCharacter( char *account, char * character);
    BOOL   DeleteCharacter( char *account, char * character);
	void   GetAccountByChar(char *acc, char *cha);

    void	SetNewCharacter( STRUCT_MOB *pMob, S_SSP_REQ_CHAR_CREATE * pData );
	void	SendToAll(MSG_STANDARD * msg);
	BOOL	ReadGuildFile		(int gid,	STRUCT_GUILD* guild);
	BOOL	WriteGuildFile		(int gid,	STRUCT_GUILD* guild);
	BOOL	CreateGuildFile		(int gid,	MSG_CreateGuild* pData);
	BOOL	AddGuildMember		(int gid,	MSG_AddGuildMember * pData);
	int		RemoveGuildMember	(int gid,	char * user, char* pMaster);
	BOOL	UpdateGuild			(int gid,	MSG_GuildUpdate * pData);
	BOOL	UpdateGuildMember	(int gid,	MSG_GuildUpdateMember * pData);
	BOOL	UpdateGuildMark(int gid, MSG_GuildUpdateMark * pData);
	BOOL	UpdateGuildMemberRank(int gid, MSG_GuildSetRanking * pData);
	int		GetGuildID			(char* pName);
	void	CheckTrimuriti();
	BOOL	UpdateGuildCargoLevel	(int nID, BYTE byLevel1, BYTE byLevel2, BYTE byLevel3);
	BOOL	UpdateGuildCargoTime	(int nID, DWORD dwTime1, DWORD dwTime2, DWORD dwTime3);
	BOOL	UpdateGuildCargoItem	(int nID, int nIndex, STRUCT_ITEM* pstItem);
};


#endif