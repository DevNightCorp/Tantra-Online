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

#include "Basedef.h"
#include "CPSock.h"
#include "TNDebug.h"
//#include "CMob.h"
#include "CUser.h"
#include "CFileDB.h"
#include "DrawInfo.h"

unsigned char	LocalIP[4]={0,};
int				LocalPort;
unsigned		LocalIPBin=0;
unsigned char	GMLocalIP[4]={0,};
int				GMLocalPort;
unsigned		GMLocalIPBin=0;
int				LastUserCountDay = -1;
int				MaxDayUserCount = 0;
E_COUNTRY_ID	g_eCountryID = eCountryChina;
// 모든 전체 공유 리소스는 이곳에서 정의.

//  Item은 
//  1.ItemList에 세부 데이터가 있고, Object,SysnZone은 Index만 가지는 방식
//  2.Item하나 하나가 pItem 에 생성되며 원본의 데이터를 카피해가는 방식
//  3.1과2의 절충으로 디스크립만 인덱스로 리스트에서 가져오는 방식
//

// MOB는 NPC,PC 모두 세부 테이터가 있는 스트럭쳐를 가진다.
#define     TIMER_SEC    0
#define     TIMER_MIN    1

//CMob			pMob [MAX_MOB];
CUser			pUser[MAX_SERVERNUMBER]; // Server가 5개면 MAX_SERVER는 최소 6이상 선언.
CUser			pAdmin[MAX_ADMIN];
unsigned int	pAdminIP[MAX_ADMIN];
CUser			TempUser; // ACCEPT시 일단 Temp에 받았다가, 동일 IP기접속 소켓이 있으면.
int				SecCounter		=0;
int				MinCounter		=0;
int				HourCounter		=0;
int				ServerIndex		=-1;
int				TransperCharacter=0;
int				GuildID			=0;	
//CItem			pItem[MAX_ITEM];



int        UserConnection[MAX_SERVERNUMBER] = {0,};
HINSTANCE  hInst;     
HWND    hWndMain;
unsigned int CurrentTime;
unsigned int LastSendTime;
HMENU   hMainMenu;
CPSock  ListenSocket[MAX_SERVERNUMBER];
CPSock  AdminSocket;
CPSock  AdminClient; //
CFileDB cFileDB;
int		AdminLevel[MAX_ADMIN] = 
{ 
	0, 0, 0,										// ROOT: 0 ~ 2
	1,												// SUPERVISOR: 3
	2, 2, 2, 2, 2,									// GOP: 4 ~ 8
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,	// GM: 9 ~ 23
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 // GMS: 24 ~ 50
};
enum ADMIN_LEVEL_DESC
{
	eAdminRoot			= 0,
	eAdminSupervisor	= 1,
	eAdminGOP			= 2,
	eAdminGM			= 3,
	eAdminGMS			= 4
};

LONG APIENTRY MainWndProc(HWND, UINT, UINT, LONG);

void ProcessClientMessage ( int conn , char*msg);
int ProcessAdminMessage  (int conn,char*msg);

void ProcessSecTimer    ( void );
void ProcessMinTimer    ( void );
void ImportUser         ( void );
void UpdateUser         ( void );

int  GetUserFromSocket  ( int Sock );
int  GetAdminFromSocket ( int Sock );

int  GetEmptyUser       ( void );
int  GetEmptyAdmin		(void);
void StartLog           ( char * cccc );
void ImportItem         ( void );

void DisableAccount		(int conn,char * account);
void EnableAccount		(int conn,char * account);
void SetValidUser		(int ServerNum, int AdminNum);

void SendUserCount		(int conn);

void Log                  ( char * String1, char * String2 ,unsigned int ip);
FILE * fLogFile = NULL;

void ProcessUser(void);

int  g_HeightWidth  = MAX_GRIDX;
int  g_HeightHeight = MAX_GRIDY;
int  g_HeightPosX   = 0;
int  g_HeightPosY   = 0;
STRUCT_MOB g_pBaseSet[MAX_CLASS];
char temp[256];

BOOL SendAdminSignal(int svr,unsigned short id, unsigned short signal)
{	MSG_STANDARD sm; sm.wType = signal;
	sm.nID = id; sm.wPDULength = sizeof(sm) - sizeof(HEADER);
	pAdmin[svr].cSock.SendOneMessage((char*)&sm,sizeof(sm));
	return TRUE;
}
BOOL SendAdminMessage(int svr,unsigned short id, char * message)
{    
	MSG_NPNotice sm; sm.wType = _MSG_NPNotice;
	sm.nID = id; sm.wPDULength = sizeof(sm) - sizeof(HEADER);
	strcpy(sm.String,message);
	pAdmin[svr].cSock.SendOneMessage((char*)&sm,sizeof(sm));
	return TRUE;
}

BOOL SendAdminParm(int svr,unsigned short id, unsigned short signal,int parm)
{    /*MSG_STANDARDPARM sm; sm.wType = signal;
     sm.nID = id;          sm.wPDULength = sizeof(sm) - sizeof(HEADER);
	 sm.Parm = parm;
     pAdmin[svr].cSock.SendOneMessage((char*)&sm,sizeof(sm));*/
	 return TRUE;
}
BOOL SendAdminState(int svr,unsigned short id, unsigned short signal,char * pass)
{    MSG_STANDARDPARM sm; sm.wType = signal;
     sm.wPDULength = sizeof(MSG_STANDARDPARM) - sizeof(HEADER);
	 sm.Parm = 0;
	 if (pass[0]=='@') sm.Parm = 1;
	 if (pass[0]=='_') sm.Parm = 2;
	 if (pass[0]=='#') sm.Parm = 3;
     pAdmin[svr].cSock.SendOneMessage((char*)&sm,sizeof(MSG_STANDARDPARM));
	 return TRUE;
}

//2191360
BOOL InitApplication(HANDLE hInstance)   
{    WNDCLASS  wc;  wc.style = CS_VREDRAW|CS_HREDRAW|CS_DBLCLKS;    
     wc.lpfnWndProc = (WNDPROC)MainWndProc;  wc.cbClsExtra = 0;  wc.cbWndExtra = 0;                    
     wc.hIcon = (HICON)LoadIcon ((HINSTANCE)hInstance, "MAINICON");
     wc.hInstance = (HINSTANCE) hInstance;  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
     wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);  wc.lpszMenuName =  NULL;           
     wc.lpszClassName = "MainClass"; if(!RegisterClass(&wc)) return RegisterClass(&wc);
     return TRUE;
}

BOOL InitInstance( HANDLE hInstance, int nCmdShow)  
{    hMainMenu = CreateMenu();
 	 hWndMain = CreateWindow(   "MainClass",  "DB Server", 
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN ,    // Window style. 
        CW_USEDEFAULT,   CW_USEDEFAULT, 640+8,   480,            // W,H[Menu합치면 480]
        NULL,    hMainMenu,  (HINSTANCE)hInstance,   NULL     );
     if (!hWndMain) return (FALSE);
     ShowWindow(hWndMain, nCmdShow);  
     UpdateWindow(hWndMain);          
   return (TRUE);     
}

void UpdateConnection(void)
{
     char temp[256];
  	 sprintf(temp,"R:/serv%2.2d.htm",ServerIndex);
     FILE * fp = fopen(temp,"wt");
     if (fp==NULL) return;
	 for (int i=0;i<MAX_SERVER;i++)
	 {
		 if (pUser[i].Mode==USER_EMPTY) 
		 {  fprintf(fp,"-1\n");
		    continue;
		 }
		 if (UserConnection[i]<pUser[i].Count) UserConnection[i] = pUser[i].Count;
		 fprintf(fp,"%d\n",pUser[i].Count);
	 }
	 fclose(fp);
}

void UpdateConnectionData(void)
{
 	 char temp[256];
	 sprintf(temp,"R:/data%2.2d.csv",ServerIndex);
	 FILE * fp = fopen(temp,"a+");
     if (fp==NULL) return;

     
   	 struct tm when;
	 time_t now;
	 time(&now); when= *localtime(&now);
     sprintf(temp,"%4.4d_%2.2d_%2.2d_%2.2d ",when.tm_year+1900,when.tm_mon+1,when.tm_mday,when.tm_hour);


	 fprintf(fp,temp);
     if (fp==NULL) return;
     int total = 0;
	 for (int i=0;i<MAX_SERVER;i++)
	 {
		 int ret = UserConnection[i];
		 total=total+ret;
		 fprintf(fp,",%4d  ",ret);
		 UserConnection[i]=0;
	 }
	 fprintf(fp,",%4d  ",total);
	 fprintf(fp,"\n");

	 fclose(fp);
}

void ReadAdmin()
{
 	 char temp[256];
	 sprintf(temp,"Admin.txt");
	 FILE * fp = fopen(temp,"r");
     if (fp==NULL) return;
   
	 while(1)
	 {
 	    int a,b,c,d;
	    a=b=c=d=0;
		char * ret = fgets((char*)temp,127,fp);    if (ret==NULL) break;
	    int idx=-1;
		for (int i=0;i<255;i++) if (temp[i]=='.') temp[i]=' ';
        sscanf(temp,"%d %d %d %d %d",&idx,&a,&b,&c,&d);
        unsigned int ip = (d<<24) + (c<<16) +  (b<<8) + a; 
	    if (idx<0 ||idx>=MAX_ADMIN) continue;
        pAdminIP[idx]=ip;
    };
    fclose(fp);
}
int	ReadConfig(void)
{	char temp[256];
	GuildID=0;
	FILE * fp=fopen("Config.txt","rt");if(fp==NULL) { MessageBox(hWndMain,"cant find Config.txt","BOOTING ERROR",NULL);return FALSE; }
	fscanf(fp,"%s %d\n",temp,&GuildID);
	if(GuildID==0) { MessageBox(hWndMain,"cant read current guild id in Config.txt","BOOTING ERROR",NULL);return FALSE; }
	fclose(fp);
	return TRUE;
}

int	WriteConfig(void)
{
	FILE * fp=fopen("Config.txt","wt");if(fp==NULL) { /*MessageBox(hWndMain,"cant write Config.txt","BOOTING ERROR",NULL);*/return FALSE; }
	fprintf(fp,"GuildID %d\n",GuildID);
	fclose(fp);
	return TRUE;
}

//#define REPORT 1
char adminclientid[256];
char adminclientpass[256];
WINAPI WinMain(  HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{   MSG msg;
    UNREFERENCED_PARAMETER( lpCmdLine );
    hInst = hInstance;
    if (!hPrevInstance)
	if (!InitApplication(hInstance)) return (FALSE);             
    if (!InitInstance(hInstance, nCmdShow)) return (FALSE);

	SetValidUser( MAX_SERVERNUMBER, MAX_ADMIN );

	int n = sizeof(STRUCT_ACCOUNTFILE);

	////////////////////////////////////////////////
	BASE_InitModuleDir();
	BASE_InitializeServerList();
	////////////////////////////////////////////////
	StartLog("A");
	Log("start log","-system",0);
	ReadConfig();
	CreateDirectory( "Delete_Backup", NULL );

	cFileDB.InitGuild();
	cFileDB.CheckTrimuriti();

#ifdef REPORT
    ProcessUser();
    if (fLogFile) fclose(fLogFile); 
	return TRUE;
#endif 
	int ret = ListenSocket[0].WSAInitialize();
	if (ret==NULL)
	{  Log("err wsainitialize fail","-system",0);
	   return FALSE;
    }
  	//SetTimer(hWndMain, TIMER_SEC,  4000,NULL); 
   	//SetTimer(hWndMain, TIMER_MIN, 60000,NULL); 

    /////////////SetLocalAddress////////////////////////////////////////

    char name[255];
    //PHOSTENT hostinfo;
	FILE * fp = fopen("localip.txt","rt");
	if	(fp) 
	{	fscanf(fp,"%s %d",name, &LocalPort);fclose(fp);
	}	else	
	{	MessageBox(hWndMain,"Can't find localip.txt","REBOOTING ERROR",NULL);
	}
	int r1,r2,r3,r4;
	sscanf(name,"%d.%d.%d.%d",&r1,&r2,&r3,&r4);
	LocalIP[0]=r1;	LocalIP[1]=r2;	LocalIP[2]=r3;	LocalIP[3]=r4;	

	fp = fopen("GMlocalip.txt","rt");
	if	(fp) 
	{	memset(name, 0, sizeof(name));
		fscanf(fp,"%s %d",name, &GMLocalPort);fclose(fp);
		sscanf(name,"%d.%d.%d.%d",&r1,&r2,&r3,&r4);
		GMLocalIP[0]=r1;	GMLocalIP[1]=r2;	GMLocalIP[2]=r3;	GMLocalIP[3]=r4;	
	}	else	
	{	//	MessageBox(hWndMain,"Can't find GMlocalip.txt","REBOOTING ERROR",NULL);
		GMLocalIP[0]=r1;	GMLocalIP[1]=r2;	GMLocalIP[2]=r3;	GMLocalIP[3]=r4;
		GMLocalPort=ADMIN_PORT;
	}
	fp = fopen("CountryID.txt","rt");
	if	(fp)
	{	fscanf(fp,"%d",&g_eCountryID);fclose(fp);
	}
/*
    if (gethostname ( name, sizeof(name)) == 0)
    {	if ((hostinfo = gethostbyname(name)) != NULL)
		{
			char * tmp = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
			sscanf(tmp,"%d.%d.%d.%d",&LocalIP[0],&LocalIP[1],&LocalIP[2],&LocalIP[3]);
			strcpy(name,tmp);
		}
	}
	if (LocalIP[0]==0){MessageBox(NULL,"Can't get local address","Reboot error",MB_OK); return 0;}
*/
    // g_pServerList와 대조하여 ServerIndex를 구한다.
	unsigned * tmp = (unsigned*)LocalIP;
	LocalIPBin = *tmp;
	int i=0;
    for (i=0;i<MAX_SERVERGROUP;i++)
	{   
        if (!strcmp(g_pServerList[i][0],name)) {ServerIndex=i;break;}
	}
    if (ServerIndex==-1)
    {	MessageBox(hWndMain,"Can't get Server Group Index LocalIP:",name,MB_OK|MB_SYSTEMMODAL);
		MessageBox(hWndMain,"Can't get Server Group Index TestServerIP:",g_pServerList[i][0],MB_OK|MB_SYSTEMMODAL);
	   return TRUE;
    }
	//ImportItem();
	
	for	(i=1;i<MAX_SERVER+1;i++)	//	for zone server
	{	ListenSocket[i].StartListen( hWndMain, LocalIPBin, g_pServerListPort[ServerIndex][i]+1000, WSA_ACCEPT);
	}
	
	//	for sql deamon
	ListenSocket[INDEXOFDAEMON].StartListen( hWndMain, LocalIPBin, g_pServerListPort[ServerIndex][INDEXOFDAEMON]+1000, WSA_ACCEPT);

	tmp = (unsigned*)GMLocalIP;
	GMLocalIPBin = *tmp;
	AdminSocket.StartListen( hWndMain, GMLocalIPBin, GMLocalPort, WSA_ACCEPTADMIN );

//////AdminClient/////////////////////////////////////////////////////////////////////////////////////
	fp = fopen("redirect.txt","rt");
	if	(fp)	
	{	char sip[256];
		int  port;
		fscanf(fp,"%s %d %s %s",sip,&port,adminclientid,adminclientpass);
		fclose(fp);
		ret = AdminClient.ConnectServer(sip,port,INADDR_ANY,WSA_READADMINCLIENT,hWndMain);
        if	(ret==NULL)
		{	MessageBox(hWndMain,"there's redirect.txt but can't connect","BOOTING ERROR",NULL);
			return FALSE;		
		}	else
		{	Log("sys redirection server connected","-system",0);
			TransperCharacter = 1;
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    SetTimer(hWndMain, TIMER_SEC, 1000,NULL); 
	SetTimer(hWndMain, TIMER_MIN, 60000,NULL); 

    while (GetMessage(&msg, NULL, 0, 0))
    {     TranslateMessage(&msg);
          DispatchMessage(&msg); 
    }
    return (msg.wParam);  
}

int ProcessAdminClientMessage(char*msg)
{

	MSG_STANDARD *std= (MSG_STANDARD *)msg;

	//if	(!(std->wType&FLAG_NP2DB)  ||  (std->nID<0) || (std->nID>=MAX_DBACCOUNT) )
	//{	char temp[128]; sprintf(temp,"err adminclient_packet:%d ID:%d Size:%d ",std->wType,std->nID,std->wPDULength);
	//	Log(temp,"-system",0);
	//	return FALSE;
	//} 
/*
    switch (std->Type)    
	{
		case _MSG_NPCreateCharacter_Reply:	// redirect source의 생성결과 처리
		{	MSG_NPCreateCharacter_Reply* m = (MSG_NPCreateCharacter_Reply*) msg;
			char * account	= m->Account;
			int slot		= m->Slot;
			int result		= m->Result;
			int IdxName		= cFileDB.GetIndex(m->Account);
			int	svr			= IdxName/MAX_USER;
			int	id			= IdxName%MAX_USER;
			MSG_ReqTransper sm; memset(&sm,0,sizeof(sm));
			sm.Type = _MSG_ReqTransper; 
			sm.Size = sizeof(sm);
			sm.ID	= id;
			sm.Slot = slot;
			sm.Result=m->Result;

			// 일단 회신받자마자 Enable부터 시킨다.
			EnableAccount(-1,account);
			//strcpy(sm.Account,m->Account); 게임서버에서도 어카운트 체크를 한번 해야 더 정확하다.
			if	(m->Result==0)//; //0: Success Delete Parm2
			{	
				STRUCT_ACCOUNTFILE file;
				memcpy(file.AccountName,m->Account,ACCOUNTNAME_LENGTH);
				int ret = cFileDB.DBReadAccount(&file);
				if  (ret == FALSE)
				{	// 이전을 요청했는데 원본이 없다?
					char tt[256]; sprintf(tt,"etc tranper_FAILED!!!!!(read) %s %s",m->Account,m->szName);
					Log(tt,file.AccountName,0);
					if	(IdxName)	{sm.Result = 4;pUser[svr].cSock.SendOneMessage((char*)&sm,sm.Size);}
					return TRUE;
				}
				char tt[256]; sprintf(tt,"etc tranper_success(deleted) %s %s",m->Account,m->szName);
				Log(tt,file.AccountName,0);
				memset(&file.Char[slot],0,sizeof(STRUCT_MOB));
				strupr(file.AccountName);
				ret=cFileDB.DBWriteAccount(&file);
	            if  (ret==FALSE)
				{	char tt[256]; sprintf(tt,"etc tranper_FAILED!!!!!(write) %s %s",m->Account,m->szName);
					Log(tt,file.AccountName,0);
					if	(IdxName)	{sm.Result = 4;	pUser[svr].cSock.SendOneMessage((char*)&sm,sm.Size);}
					return TRUE;
				}

				if	(IdxName)
				{	pUser[svr].cSock.SendOneMessage((char*)&sm,sm.Size);
					memset( &(cFileDB.pAccountList[IdxName].File.Char[slot]),0,sizeof(STRUCT_MOB));
				}
				//  현재 접속중이면, 해당 캐랙터를 제거한다
				//  접속을 했던 하지 않않던 Account를 읽어서 캐랙터를 지우고 저장한다
			}
			if	(result==1)		//1: Threre's Same Name Already
			{	if	(IdxName)	pUser[svr].cSock.SendOneMessage((char*)&sm,sm.Size);
			}	else
			if	(result==2)		//2: No character space. delete first.
			{	if	(IdxName)	pUser[svr].cSock.SendOneMessage((char*)&sm,sm.Size);
			}	else
			if	(result==3)		//3: That account is playing
			{	if	(IdxName)	pUser[svr].cSock.SendOneMessage((char*)&sm,sm.Size);
			}
		}	break;	
	}
	*/
	return TRUE;
}

LONG APIENTRY MainWndProc( HWND hWnd, UINT message, UINT wParam, LONG lParam) 
{
	switch (message)    
	{
		case WM_TIMER:
		{ 
			if (wParam==TIMER_SEC) ProcessSecTimer(); else
			if (wParam==TIMER_MIN) ProcessMinTimer(); 
		}	break;
		case WSA_READADMINCLIENT:
		{
		    if	(WSAGETSELECTEVENT(lParam) != FD_READ)
  	        {	Log("adminclient close fd read","-system",0);
				AdminClient.CloseSocket();
				break;
			}
			if	(AdminClient.Receive()!=1)
			{	Log("adminclient %d close receive","-system",0);
				break;
			}
			char temp[256];	int Error;	int ErrorCode;
            while(1)
			{	char * Msg = AdminClient.ReadMessage(&Error,&ErrorCode); if (Msg==NULL) break;
				///////////////////
				if	(Error==1|| Error==2)
				{	sprintf(temp,"err wsa_ReadadminClient (%d),%d",Error,ErrorCode );
					Log(temp,"-system",0);
					break;
				}
				int ret = ProcessAdminClientMessage(Msg);// , Manage.ReceiveSize);

			};
		}	break;
		case WSA_READADMIN:
		{
			int User = GetAdminFromSocket(wParam);  
			if	(User == -1)
			{	closesocket(wParam);
				Log("err wsa_read unregistered sever socket","-system",0);
				break;
			} 
            //
		    if	(WSAGETSELECTEVENT(lParam) != FD_READ)
  	        {	char temp[256];sprintf(temp,"admin close fd %d",User);
				Log(temp,"-system",0);
				pAdmin[User].cSock.CloseSocket();
				pAdmin[User].Mode=USER_EMPTY;
				pAdmin[User].Name[0]=0;
				break;
			} 
		 	CurrentTime = timeGetTime();
			if	(pAdmin[User].cSock.Receive()!=1)
			{	char temp[256];sprintf(temp,"admin %d close receive",User);
				Log(temp,"-system",0);
				break;
			}

			char temp[256];
			int Error;
			int ErrorCode;
            while(1)                    //   ReadMessage fors_debug to 뗍혤GMTOOS句口
			{	char * Msg = pAdmin[User].cSock.ReadClientMessage(&Error,&ErrorCode);   //     ReadMessage(&Error,&ErrorCode); 
				if (Msg==NULL) break;
				////////////////////////////////
	            #ifdef  _PACKET_DEBUG
				MSG_STANDARD * debug = (MSG_STANDARD*) Msg;
		//		if	(BASE_CheckPacket(debug))
				{	sprintf(temp,"err packet Type:%d Size:%d",debug->wType,debug->wPDULength);
					Log(temp,"-system",0);
				}
				#endif
				///////////////////
				if	(Error==1|| Error==2)
				{	sprintf(temp,"err wsa_Readadmin (%d),%d",Error,ErrorCode );
					Log(temp,"-system",0);
					break;
				}
				int ret = ProcessAdminMessage(User,Msg);// , Manage.ReceiveSize);
				if	(ret==FALSE) 
				{	pAdmin[User].cSock.CloseSocket();
					pAdmin[User].Mode = USER_EMPTY;
					pAdmin[User].Name[0]=0;
					break;
				}
			}; 
		}     break;
		case WSA_READ:
		{
			int User = GetUserFromSocket(wParam);  
			if	(User == -1)
			{	
				//Sleep(100);
				closesocket(wParam);
				SendUserCount(-1);
				Log("err wsa_read unregistered game server socket","-system",0);
				break;
			}
            //
			if	(WSAGETSELECTEVENT(lParam) != FD_READ)
			{	//Sleep(100);
				char temp[256];sprintf(temp,"clo server fd zone :%d",User+1);
				Log(temp,"-system",0);
				pUser[User].cSock.CloseSocket();
				//pUser[User].Count = 0;
				pUser[User].Mode=USER_EMPTY;
				SendUserCount(-1);
				// ACCEPT에서는 IP가 동일한 User슬롯에 접속시킨다.
				break;
			}
			CurrentTime = timeGetTime();

			if	(pUser[User].cSock.Receive()!=1)
			{	char temp[256];sprintf(temp,"clo server receive %d",User);
				Log(temp,"-system",0);

				pUser[User].cSock.CloseSocket();
				//pUser[User].Count = 0;
				pUser[User].Mode=USER_EMPTY;
				SendUserCount(-1);

				// pUser[User].ModepUser[User].cSock.=MODE_SAVEEMPTY;
				// DB 서버에 REQ_SAVE를 날리고 
				// MODE를 REQ_SAVE로 바꾼다.
				// Confirm이 오면  MODE_EMPTY
				break;
			}

			char temp[256];
			int Error;
			int ErrorCode;
			do 
			{	char * Msg = pUser[User].cSock.ReadMessage(&Error,&ErrorCode); 
				if (Msg==NULL) break;
				////////////////////////////////
				#ifdef  _PACKET_DEBUG
				MSG_STANDARD * debug = (MSG_STANDARD*) Msg;
				if	(BASE_CheckPacket(debug))
				{	sprintf(temp,"**PACKET_DEBUG** Type:%d Size:%d",debug->Type,debug->Size);
					Log(temp,"-system",0);
				}
				#endif
				///////////////////
				if	(Error==1 || Error==2)
				{	sprintf(temp,"err wsa_read (%d),%d",Error,ErrorCode );
					Log(temp,"-system",0);
					break;
				} 
				ProcessClientMessage(User,Msg);// , Manage.ReceiveSize);
			} while(1);
		}	break;     
		case WSA_ACCEPTADMIN:
		{	ReadAdmin();
			if	(WSAGETSELECTERROR( lParam ) == 0) 
			{	TempUser.AcceptUser(AdminSocket.Sock,WSA_READADMIN);
				unsigned char *cIP  = (unsigned char *) &(TempUser.IP);
				int User=-1;
				int i=0;
				//	아무거나 빈거를 고른다 // 다유저 버전
				//for (i=0;i<=MAX_ADMIN;i++)
				//{   if (pAdmin[User].Mode==USER_EMPTY) {User=i;break;}
				//}
				//
				///*
				// 기접속자의 IP와 중복되는것을 검사한다. // 원유저 버전
				User=-1;
				//for (i=0;i<=MAX_ADMIN;i++)
				//{   if	(pAdmin[i].IP == TempUser.IP) {User=i;break;}
				//}
				DWORD dwFlag = 0x000000FF; 
				DWORD dwAdmin = 0; 
				DWORD dwUser = TempUser.IP & 0xFFFFFF00;
				if  (User==-1) // 기 접속 서버중 일치하는 아이피가 없다.
				{
					for	(i=0;i<MAX_ADMIN;i++)
					{	int a,b,c,d; a=b=c=d=0;
						if (pAdminIP[i]==0) continue;
						DWORD dwAdmin = pAdminIP[i] & 0x000000FF;
						if(dwAdmin)
						{	if (pAdminIP[i]==TempUser.IP) {User=i;break;}
						}	else
						{	if (pAdminIP[i]==dwUser) {User=i;break;}
						}
					}
					if	(i==MAX_ADMIN)
					{	TempUser.cSock.CloseSocket();
						char temp[256];   
						sprintf(temp,"err wsa_acceptadmin request accept from  %d.%d.%d.%d",cIP[0],cIP[1],cIP[2],cIP[3] );
						Log(temp,"-system",0);
					}
				} 
				//*/
				if	(User>=0 && User<MAX_ADMIN)
				{
					 if	(pAdmin[User].Mode!=USER_EMPTY)
					{	char temp[256];
						sprintf(temp,"err wsa_acceptadmin not empty previous slot %d",i );
						Log(temp,"-system",0);
						TempUser.cSock.CloseSocket();
						// 이전접속도 끊어버린다.
						pAdmin[User].cSock.CloseSocket();
						pAdmin[User].Mode=USER_EMPTY;
						break;
					} 
				}   else
				{   Log("err accept_admin unknown attempt","-system",0);
					TempUser.cSock.CloseSocket();
					break;
				}

				User = GetEmptyAdmin();

				if	(User==-1)
				{	Log("err accept_admin no empty","-system",0);
					break;
				} 
				//pAdmin[User].Level               = -1; // Not Authrized
				pAdmin[User].Level               = AdminLevel[User];
				pAdmin[User].DisableID           = 0;
				pAdmin[User].IP                  = TempUser.IP;
				pAdmin[User].Mode                = TempUser.Mode;
				pAdmin[User].Name[0]			 = 0;
				pAdmin[User].cSock.Sock          = TempUser.cSock.Sock;
				pAdmin[User].cSock.nRecvPosition = TempUser.cSock.nRecvPosition;
				pAdmin[User].cSock.nProcPosition = TempUser.cSock.nProcPosition;
				pAdmin[User].cSock.nSendPosition = TempUser.cSock.nSendPosition ;
				pAdmin[User].cSock.ucRecvSeq = pAdmin[User].cSock.ucSendSeq = pAdmin[User].cSock.oldRecvChecksum = pAdmin[User].cSock.oldSendChecksum = 0;
				cIP = (unsigned char *) &(pAdmin[User].IP);
				char tmp[100]; sprintf(tmp,"sys wsa_acceptadmin %d.%d.%d.%d <%d>",cIP[0],cIP[1],cIP[2],cIP[3],User);
				Log(tmp,"-system",0);
			}	else 
			{	Log("err accept_admin accepting fails","-system",0);
			}
		}
		break;
		case WSA_ACCEPT:
		{
			int i=0;
			if	(WSAGETSELECTERROR( lParam )) 
			{	Log("err WSAGETSELECTERROR - accepting new client.","-system",0);
				break;
			}
					
			int index = -1;
			for	(i=0;i<MAX_SERVERNUMBER;i++)
			{	if	(wParam == ListenSocket[i].Sock)	{index=i; break;}
			}
			if	(index<0||index>MAX_SERVERNUMBER)
			{	Log("invalid server listen socket","-system",0);
				return TRUE;
			}
			TempUser.AcceptUser(ListenSocket[index].Sock,WSA_READ);
			TempUser.cSock.Port = ListenSocket[index].Port;
			unsigned char  *cIP    = (unsigned char *) &(TempUser.IP);
			char sIP[256]; sprintf(sIP,"%d.%d.%d.%d",cIP[0],cIP[1],cIP[2],cIP[3]);
			//TempUser.IP 가 동일한 끊어진 pUser[User].IP를 조회.  있으면 그녀석에게 User를 할당 그렇지 않으면,
			// IP가 비어 있는 User을 idx를 User에할당.
			int User=-1;
			for (i=0;i<MAX_SERVERNUMBER;i++)
			{   if (pUser[i].IP==TempUser.IP && pUser[i].cSock.Port == ListenSocket[index].Port-1000) {User=i;break;}
			}
	//		User=22;
			if  (User==-1) // 기 접속 서버중 일치하는 아이피가 없다.
			{ 
				for (i=1;i<MAX_SERVERNUMBER;i++)
				{	if ((!strcmp(g_pServerList[ServerIndex][i],sIP)) && ((g_pServerListPort[ServerIndex][i]+1000)==ListenSocket[index].Port)) break;
				}
				if	(i==MAX_SERVERNUMBER)
				{	TempUser.cSock.CloseSocket();
					char temp[256];   
					sprintf(temp,"err wsa_accept request from  %s",sIP );
					Log(temp,"-system",0);
					break;
				}
				User=i-1;
			}   else
			if  (User>=0 && User<MAX_SERVERNUMBER)
			{   if	(pUser[User].Mode!=USER_EMPTY)
				{	char temp[256];
					sprintf(temp,"err wsa_accept no previous slot %d",User );
					Log(temp,"-system",0);
					TempUser.cSock.CloseSocket();
					break;
				}
			}   else
			{	Log("err wsa_accept unknown attempt","-system",0);
				TempUser.cSock.CloseSocket();
			}
			if	(User==-1)
			{	Log("err wsa_accept no empty","-system",0);
				break;
			}
			pUser[User].IP                  = TempUser.IP;
			pUser[User].Mode                = TempUser.Mode;
			pUser[User].cSock.Sock          = TempUser.cSock.Sock;
			pUser[User].cSock.Port          = TempUser.cSock.Port;
			pUser[User].cSock.nRecvPosition = TempUser.cSock.nRecvPosition;
			pUser[User].cSock.nProcPosition = TempUser.cSock.nProcPosition;
			pUser[User].cSock.nSendPosition = TempUser.cSock.nSendPosition ;
			pUser[User].cSock.ucRecvSeq = pUser[User].cSock.ucSendSeq = pUser[User].cSock.oldRecvChecksum = pUser[User].cSock.oldSendChecksum = 0;
			char temp[256];sprintf(temp,"sys new connection from %d.%d.%d.%d - zone :%d",cIP[0],cIP[1],cIP[2],cIP[3],User+1);
			SendUserCount(-1);
			Log(temp,"-system",0);
			// 일단은 Error만 Log를 만든다.
		}	break;
		case WM_PAINT:
			PAINTSTRUCT ps;
			BeginPaint(hWnd,&ps);
			DrawInformations(ps.hdc);
			EndPaint(hWnd,&ps);
			break; 
		case WM_CLOSE:
		{	for(int i=0; i<MAX_SERVER; i++)
			{	if(pUser[i].Mode!=USER_EMPTY)
				{	int rret = MessageBox(hWndMain,"Zone Server is Connected. Do you want to close DBA Server?","Warning!! - Close Server",MB_OKCANCEL);
					if	(rret==1)
					{	if (fLogFile) fclose(fLogFile); 
						break;
					}	else
						return true;
				}
			}
			DefWindowProc(hWnd,message,wParam,lParam);
		}	break;
		case WM_DESTROY:
			WSACleanup();
			PostQuitMessage(0);
			break;
		default:                      
			return (DefWindowProc(hWnd, message, wParam, lParam));
		break;
	}
	return (0);
}


void ProcessClientMessage(int conn,char*msg)
{
	cFileDB.ProcessMessage(msg,conn);
}

void DisableAccount(int conn,char * account)
{
	// 파일을 읽어서 패스워드 선단에 #을 붙여서 저장하고, NP에게 Disable을 날린다.
	account[ACCOUNTNAME_LENGTH-1]=0;
	account[ACCOUNTNAME_LENGTH-2]=0;
	strupr(account);
	STRUCT_ACCOUNTFILE file;
	memcpy(file.AccountName,account,ACCOUNTNAME_LENGTH);
	int iret = cFileDB.DBReadAccount(&file);  
	if	(iret==FALSE) 
	{	if	(conn>=0) SendAdminSignal(conn,0,_MSG_NPNotFound);
		if	(conn>=0) SendAdminMessage(conn,0,"There's no account with that account name");
		return;
	}
	// 비번에 #추가.
	if	(file.AccountPass[0]==1) 
	{	if	(conn>=0) SendAdminState(conn,0,_MSG_NPState,file.AccountPass);
		return;
	}
	file.AccountPass[ACCOUNTPASS_LENGTH-1]=0;
	file.AccountPass[ACCOUNTPASS_LENGTH-2]=0;
	char temp[256];sprintf(temp,"#%s",file.AccountPass);temp[0]=1;
	strcpy(file.AccountPass,temp);
	cFileDB.DBWriteAccount(&file);
	if	(conn>=0)
	{	int idx = pAdmin[conn].DisableID;
		MSG_NPReqAccount sm; sm.wType= _MSG_NPReqAccount; sm.wPDULength = sizeof(MSG_NPReqAccount) - sizeof(HEADER);
		strncpy(sm.Account,account,ACCOUNTNAME_LENGTH);
		sm.Char[0]=0;
		ProcessAdminMessage(conn,(char*)&sm);
		pAdmin[conn].DisableID=0;
	}
}
void EnableAccount(int conn,char * account)
{	
	account[ACCOUNTNAME_LENGTH-1]=0;
	account[ACCOUNTNAME_LENGTH-2]=0;
	strupr(account);
	// 파일을 읽어서 패스워드 선단에 #을 붙여서 저장하고, NP에게 Disable을 날린다.
	STRUCT_ACCOUNTFILE file;
  	memcpy(file.AccountName,account,ACCOUNTNAME_LENGTH);
	int iret = cFileDB.DBReadAccount(&file);  
	if	(iret==FALSE) 
	{	if	(conn>=0) SendAdminSignal(conn,0,_MSG_NPNotFound);
		if	(conn>=0) SendAdminMessage(conn,0,"There's no account with that account name");
		return;
	}
	// 비번에 #추가.
	if	(file.AccountPass[0]!=1) 
	{	if	(conn>=0) SendAdminState(conn,0,_MSG_NPState,file.AccountPass);
		return;
	}
	file.AccountPass[ACCOUNTPASS_LENGTH-1]=0;
	file.AccountPass[ACCOUNTPASS_LENGTH-2]=0;
	char temp[256];sprintf(temp,"%s",file.AccountPass+1);
	strcpy(file.AccountPass,temp);
	cFileDB.DBWriteAccount(&file);
	if	(conn>=0)
	{	int idx = pAdmin[conn].DisableID;
		MSG_NPReqAccount sm; sm.wType= _MSG_NPReqAccount; sm.wPDULength = sizeof(MSG_NPReqAccount) - sizeof(HEADER);
		strncpy(sm.Account,account,ACCOUNTNAME_LENGTH);
		sm.Char[0]=0;
		ProcessAdminMessage(conn,(char*)&sm);
	}
	return ;
}
int GetAdminLevel(char*szName,char*szPassword)
{
//	return 0;
		char szFile[256] ={0,};
	sprintf( szFile, "./GMPermission/%s.bin", szName);
	FILE* fpBin = fopen( szFile, "rb" );
	if ( fpBin != NULL ) 
	{
		char szServerBin[64];
		char szPass[64];
		int nLevel = 0;
		char szList[65] ="ㄱㄴㄷㄹㅁㅂㅅㅇㅈㅊㅋㅌㅍㅎㅏㅑㅓㅕㅗㅛㅜㅠㅡㅣㅏㅔㅣㅗㅜ가나다";			
		fread( szServerBin, 1, 64, fpBin );
		for( int i = 0 ; i < 64 ; i++ ) 
		{
			szServerBin[i] -= szList[63 - i];
		}
		sscanf( szServerBin, "%s %d", szPass, &nLevel );
		fclose(fpBin);
		if(strcmp(szPassword, szPass)!=0) return -1;
		return nLevel;
	}
	else
	{
		return -1;
	}
	
}
int ProcessAdminMessage(int conn,char*msg)
{	MSG_STANDARD * std= (MSG_STANDARD*)msg;

	switch(std->wType)
	{
		case _MSG_NPReqAccount:
		{   MSG_NPReqAccount *m = (MSG_NPReqAccount *) msg;
			m->Account[ACCOUNTNAME_LENGTH - 1] = 0;
			m->Account[ACCOUNTNAME_LENGTH - 2] = 0;
			m->Char[SZNAME_LENGTH - 1] = 0;
			m->Char[SZNAME_LENGTH - 2] = 0;
			strupr(m->Account);
			if (m->Char[0]!=0)		{ cFileDB.GetAccountByChar(m->Account,m->Char); }
			if	(m->Account[0]==0) // 캐랙터로도  못찾았음. 
			{	SendAdminSignal(conn,0,_MSG_NPNotFound);
				SendAdminMessage(conn,0,"Cannot find account from this character.");
				return TRUE;
			}  
			STRUCT_ACCOUNTFILE file;
			memcpy(file.AccountName,m->Account,ACCOUNTNAME_LENGTH);
			int iret = cFileDB.DBReadAccount(&file);  
			if	(iret==FALSE) // 어카운트로 못찾았음
			{	SendAdminSignal(conn,0,_MSG_NPNotFound);
				SendAdminMessage(conn,0,"Account not found.");
				return TRUE;
			}
			MSG_NPAccountInfo sm; sm.wType = _MSG_NPAccountInfo; sm.wPDULength = sizeof(MSG_NPAccountInfo) - sizeof(HEADER); 
			sm.account = file; sm.Session = cFileDB.GetIndex(m->Account);
			file.Char[0].szName[SZNAME_LENGTH-1]=0;file.Char[0].szName[SZNAME_LENGTH-2]=0;
			file.Char[1].szName[SZNAME_LENGTH-1]=0;file.Char[1].szName[SZNAME_LENGTH-2]=0;
			file.Char[2].szName[SZNAME_LENGTH-1]=0;file.Char[2].szName[SZNAME_LENGTH-2]=0;
			file.AccountName[ACCOUNTNAME_LENGTH-1]=0;file.AccountName[ACCOUNTNAME_LENGTH-2]=0;
			char temp[256]; sprintf(temp,"Account Info: %s<%s|%s|%s>\n%s : %d",
				file.AccountName,file.Char[0].szName,
				file.Char[1].szName,
				file.Char[2].szName,
				( sm.Session == 0 ) ? "Not connected" : "Connected",
				sm.Session / MAX_USER +	1 );
			if (sm.Session != 0) sprintf(temp,"%s (char:%s)",temp,file.Char[cFileDB.pAccountList[sm.Session].Slot].szName);
			temp[MESSAGE_LENGTH-1]=0; temp[MESSAGE_LENGTH-2]=0;
			SendAdminMessage(conn,0,temp); // Account Name setting
			sm.State = 0;
			if (sm.account.AccountPass[0]=='@') sm.State = 1; // 정지
			if (sm.account.AccountPass[0]=='_') sm.State = 2; // 삭제
			if (sm.account.AccountPass[0]==1) sm.State = 3; // Disable
			pAdmin[conn].cSock.SendOneMessage((char*)&sm,sizeof(MSG_NPAccountInfo));
		} break;
		case _MSG_NPReqSaveAccount:
		{	MSG_NPAccountInfo * m = (MSG_NPAccountInfo *) msg;
			if ( m->wPDULength != sizeof(MSG_NPAccountInfo) - sizeof(HEADER) )
			{
				SendAdminMessage(conn,0,"You have wrong GM-Tool");
				return TRUE;
			}
			char pchLog[512]={0,}; in_addr sIP;  
			sIP.S_un.S_addr = pAdmin[conn].IP;
			int IdxName = cFileDB.GetIndex(m->account.AccountName);
			if  (IdxName!=0)
			{	SendAdminMessage(conn,0,"Account already connected. Cannot save account.");
				return TRUE;
			}
			cFileDB.DBWriteAccount(&m->account);
			cFileDB.DBExportAccount(&m->account);
			char temp[256]; sprintf(temp,"[%s] Account saving is completed.", m->account.AccountName);
			SendAdminMessage(conn,0,temp);
			if(!strcmp(m->account.AccountName, Developer)) break;
			sprintf(pchLog,"From %d.%d.%d.%d    %s written \r\n", sIP.S_un.S_un_b.s_b1, sIP.S_un.S_un_b.s_b2, sIP.S_un.S_un_b.s_b3, sIP.S_un.S_un_b.s_b4, m->account.AccountName);
			sprintf(pchLog,"%s %s\r\n", pchLog, m->Memo);
			TimeWriteLog(pchLog, ".\\LOG\\EditHistory.txt");  
		} break;
		case _MSG_NPDisable:
		{	MSG_NPEnable * m = (MSG_NPEnable *) msg;
			m->AccountName[ACCOUNTNAME_LENGTH-1]=0;
			m->AccountName[ACCOUNTNAME_LENGTH-2]=0;
			strupr(m->AccountName);
			int IdxName = cFileDB.GetIndex(m->AccountName);
			if  (IdxName==0)
			{	DisableAccount(conn,m->AccountName);
				return TRUE;
			}	else
			{	// 해당 유저에게 "계정 복구를 위해서 잠시 접속을 끊겠습니다."
				cFileDB.SendDBSavingQuit(IdxName,1);
				pAdmin[conn].DisableID = IdxName;
			}
		} break;
		case _MSG_NPEnable:
		{	
			//if (pAdmin[conn].Level<=2) return TRUE; // 유저 접속종료 1이상
			MSG_NPEnable * m = (MSG_NPEnable *) msg;
			m->AccountName[ACCOUNTNAME_LENGTH-1]=0;
			m->AccountName[ACCOUNTNAME_LENGTH-2]=0;
			strupr(m->AccountName);
			int IdxName = cFileDB.GetIndex(m->AccountName);
			if  (IdxName!=0)
			{	char temp[256]; sprintf(temp, "Account (%s) is already connected.", m->AccountName);
				SendAdminMessage(conn,0,temp);
				return TRUE;
			}
			EnableAccount(conn,m->AccountName);
		} break;
		case _MSG_NPNotice:  // 특정사용자 또는 전서버에 공지
		{	MSG_NPNotice *m = (MSG_NPNotice *) msg;
			m->AccountName[ACCOUNTNAME_LENGTH-1]=0;
			m->AccountName[ACCOUNTNAME_LENGTH-2]=0;
			m->String[MAX_NOTIFY_LENGTH-1]=0;
			m->String[MAX_NOTIFY_LENGTH-2]=0;
			if	(m->AccountName[0]==0 && m->Parm1==1)  // 전서버 공지
			{	//if (pAdmin[conn].Level<=2) return TRUE;
				MSG_Broadcast sm; sm.wType = _MSG_Broadcast;
				sm.wPDULength = sizeof(MSG_Broadcast) - sizeof(HEADER); 
				sm.byMsgType=2; sm.byBgColor=0; sm.byTextColor=14;
				strncpy(sm.szName,"<<GM>>",SZNAME_LENGTH);
				strncpy(sm.szMsg,m->String,MAX_NOTIFY_LENGTH);
				if (m->Parm2 != -1 ) // 특정 존에만 공지
				{	if  (m->Parm2>=MAX_SERVER) return TRUE;
					if	(pUser[m->Parm2].Mode==USER_EMPTY) return TRUE;
					if	(pUser[m->Parm2].cSock.Sock==NULL)	return TRUE;
					pUser[m->Parm2].cSock.SendOneMessage((char*)&sm,sizeof(sm));
					return TRUE;
				}
				for (int i=0;i<MAX_SERVER;i++)
				{	if	(pUser[i].Mode==USER_EMPTY) continue;
					if	(pUser[i].cSock.Sock==NULL)	continue;
					pUser[i].cSock.SendOneMessage((char*)&sm,sizeof(sm));
				}
				return TRUE;
			}
			// 개인공지.
			//if (pAdmin[conn].Level<=0) return TRUE;
			int IdxName = cFileDB.GetIndexFromName(m->AccountName);
			if (IdxName==0)
			{   SendAdminMessage(conn,0,"User not found. Cannot send message.");
				return TRUE;
			}
			int svr  = IdxName/MAX_USER;
			int id   = IdxName%MAX_USER;
			if	(svr<0||svr>=MAX_SERVER||id<=0||id>=MAX_USER)
			{	SendAdminMessage(conn,0,"Wrong SVR and ID");
				return TRUE;
			}
			S_SSP_NOTIFY_WHISPER_CHAT sm; sm.wType = SSP_NOTIFY_WHISPER_CHAT;
			sm.nID = id; sm.wPDULength = sizeof(S_SSP_NOTIFY_WHISPER_CHAT) - sizeof(HEADER);
			sm.byBgColor=0;sm.byTextColor=14;
			strcpy(sm.szName,"<<GM>>");
			strncpy(sm.szMsg,m->String,MESSAGE_LENGTH);
			pUser[svr].cSock.SendOneMessage((char*)&sm,sizeof(sm));
			return TRUE;
		} break;
		case _MSG_COMMAND:
		{	MSG_COMMAND *m = (MSG_COMMAND *) msg;
			m->szName[ACCOUNTNAME_LENGTH-1]=0;
			m->szName[ACCOUNTNAME_LENGTH-2]=0;
			m->szMsg[MAX_NOTIFY_LENGTH-1]=0;
			m->szMsg[MAX_NOTIFY_LENGTH-2]=0;
			if (m->byMsgType != 255 ) // 특정 존에만 공지
			{	if  (m->byMsgType>=MAX_SERVER) return TRUE;
				if	(pUser[m->byMsgType].Mode==USER_EMPTY) return TRUE;
				if	(pUser[m->byMsgType].cSock.Sock==NULL)	return TRUE;
				pUser[m->byMsgType].cSock.SendOneMessage((char*)m,sizeof(MSG_COMMAND));
				break;
			}
			for (int i=0;i<MAX_SERVER;i++)
			{	if	(pUser[i].Mode==USER_EMPTY) continue;
				if	(pUser[i].cSock.Sock==NULL)	continue;
				pUser[i].cSock.SendOneMessage((char*)m,sizeof(MSG_COMMAND));
			}
        } break;
		case _MSG_NPUserCount:
		{
			SendUserCount(conn);
		} break;
		case SSP_REQ_SHUTDOWN:
		{	MSG_STANDARD *m = (MSG_STANDARD*) msg;
			MSG_STANDARD sm; sm.wType = SSP_REQ_SHUTDOWN;
			sm.wPDULength = sizeof(MSG_STANDARD)-sizeof(HEADER);
			if ( m->nID == -1 )
			{	for(int i=0;i<MAX_SERVER;i++) 
				{	if	(pUser[i].Mode==USER_EMPTY) continue;
					if	(pUser[i].cSock.Sock==NULL)	continue;
					pUser[i].cSock.SendOneMessage( (char*)&sm, sizeof(MSG_STANDARD));
				}
			}
			else
			{	if (m->nID >= MAX_SERVER) break;
				if (pUser[m->nID].Mode==USER_EMPTY||pUser[m->nID].cSock.Sock==NULL) break;
				pUser[m->nID].cSock.SendOneMessage( (char*)&sm, sizeof(MSG_STANDARD));
			}
		} break;
		case _MSG_NPCreateCharacter:
		{	MSG_NPCreateCharacter *m = (MSG_NPCreateCharacter*) msg;
			m->szAccountName[ACCOUNTNAME_LENGTH-1]=0;
			m->szAccountName[ACCOUNTNAME_LENGTH-2]=0;
			m->szCharName[SZNAME_LENGTH-1]=0;
			m->szCharName[SZNAME_LENGTH-2]=0;
			int IdxName = cFileDB.GetIndex(m->szAccountName);
			if  (IdxName!=0)
			{	char temp[256]; sprintf(temp, "Account (%s) is already connected.", m->szAccountName);
				SendAdminMessage(conn,0,temp);
				return TRUE;
			}
			STRUCT_ACCOUNTFILE file;
			strncpy( file.AccountName, m->szAccountName, ACCOUNTNAME_LENGTH );
			int iret = cFileDB.DBReadAccount(&file);  
			if	(iret==FALSE) // 어카운트로 못찾았음
			{	SendAdminSignal(conn,0,_MSG_NPNotFound);
				SendAdminMessage(conn,0,"Account not found.");
				return TRUE;
			}
			int nSlot = -1;
			STRUCT_MOB *pMob;
			for	(int i=0;i<MOB_PER_ACCOUNT;i++)
			{	pMob=&file.Char[i];
				if	(pMob->szName[0]==0)
				{	nSlot=i;break;
				}
			}
			if ( nSlot == -1 )
			{	SendAdminMessage(conn,0,"There is no empty space to create character.");
				return TRUE;
			}
			BOOL bret = cFileDB.CreateCharacter( m->szAccountName, m->szCharName );
			if ( bret == FALSE )
			{	SendAdminMessage(conn,0,"This character name is already created.");
				return TRUE;
			}
			memcpy( &file.Char[nSlot], &m->MOB, sizeof(STRUCT_MOB) );
			cFileDB.DBWriteAccount( &file );

			MSG_NPReqAccount sm; sm.wType= _MSG_NPReqAccount; sm.wPDULength = sizeof(MSG_NPReqAccount) - sizeof(HEADER);
			strncpy(sm.Account,m->szAccountName,ACCOUNTNAME_LENGTH);
			sm.Char[0]=0;
			ProcessAdminMessage(conn,(char*)&sm);
		} break;
		case _MSG_NPDeleteCharacter:
		{
			MSG_NPDeleteCharacter *m = (MSG_NPDeleteCharacter*) msg;
			m->szAccountName[ACCOUNTNAME_LENGTH-1]=0;
			m->szAccountName[ACCOUNTNAME_LENGTH-2]=0;
			m->szCharName[SZNAME_LENGTH-1]=0;
			m->szCharName[SZNAME_LENGTH-2]=0;
			int IdxName = cFileDB.GetIndex(m->szAccountName);
			if  (IdxName!=0)
			{	char temp[256]; sprintf(temp, "Account (%s) is already connected.", m->szAccountName);
				SendAdminMessage(conn,0,temp);
				return TRUE;
			}
			STRUCT_ACCOUNTFILE file;
			strncpy( file.AccountName, m->szAccountName, ACCOUNTNAME_LENGTH );
			int iret = cFileDB.DBReadAccount(&file);  
			if	(iret==FALSE) // 어카운트로 못찾았음
			{	SendAdminSignal(conn,0,_MSG_NPNotFound);
				SendAdminMessage(conn,0,"Account not found.");
				return TRUE;
			}
			if ( strncmp( file.Char[m->nSlot].szName, m->szCharName, SZNAME_LENGTH ) != 0 )
			{	SendAdminMessage(conn,0,"Character name is not allowed.");
				return TRUE;
			}
			BOOL bret = cFileDB.DeleteCharacter( m->szCharName, m->szAccountName );
			if ( bret == FALSE )
			{	SendAdminMessage(conn,0,"Character file is not found.");
				return TRUE;
			}
			ZeroMemory( &file.Char[m->nSlot], sizeof(STRUCT_MOB) );
			cFileDB.DBWriteAccount( &file );

			MSG_NPReqAccount sm; sm.wType= _MSG_NPReqAccount; sm.wPDULength = sizeof(MSG_NPReqAccount) - sizeof(HEADER);
			strncpy(sm.Account,m->szAccountName,ACCOUNTNAME_LENGTH);
			sm.Char[0]=0;
			ProcessAdminMessage(conn,(char*)&sm);
		} break;
		case _MSG_NPReqGuildInfo:
		{	MSG_NPReqGuildInfo *m = (MSG_NPReqGuildInfo*) msg;
			STRUCT_GUILD guild; ZeroMemory(&guild,sizeof(STRUCT_GUILD));
            if(m->GuildName[0]!=0) m->nGuildID=cFileDB.GetGuildID(m->GuildName);
			int nGuildID = cFileDB.ReadGuildFile(m->nGuildID, &guild) ? m->nGuildID : 0;
			MSG_NPGuildInfo sm; sm.wType = _MSG_NPGuildInfo; sm.wPDULength = sizeof(MSG_NPGuildInfo)-sizeof(HEADER);
			memcpy(&sm.GuildInfo,&guild,sizeof(MSG_NPGuildInfo));sm.nGuildID=m->nGuildID;
			pAdmin[conn].cSock.SendOneMessage((char*)&sm,sizeof(MSG_NPGuildInfo));
		} break;
		case _MSG_NPIDPASS:
		{	MSG_NPIDPASS *m = (MSG_NPIDPASS*)msg;
			MSG_NPAdminLevel sm; sm.wType = _MSG_NPAdminLevel; sm.wPDULength = sizeof(MSG_NPAdminLevel)-sizeof(HEADER);
			sm.nUser = conn; sm.nLevel = GetAdminLevel(m->Account,m->Pass);
			pAdmin[conn].cSock.SendOneMessage((char*)&sm,sizeof(MSG_NPAdminLevel));
			//pAdmin[conn].cSock.AddMessage((char*)&sm,sizeof(MSG_NPAdminLevel)); //fors_debug return to gmtools
		} break;
		case _MSG_NPTaskInfo:
		{	MSG_NPTaskInfo *m = (MSG_NPTaskInfo*)msg;
			for (int i=0;i<MAX_SERVER;i++)
			{	if	(pUser[i].Mode==USER_EMPTY) continue;
				if	(pUser[i].cSock.Sock==NULL)	continue;
				pUser[i].cSock.SendOneMessage((char*)m,sizeof(MSG_NPTaskInfo));
			}
		} break;
		case _MSG_NPGiftInfo:
		{	MSG_NPGiftInfo *m = (MSG_NPGiftInfo*)msg;
			if ( m->snZone < 0 || m->snZone >= MAX_SERVER )
			{
				SendAdminMessage( conn, 0, "Wrong Zone Number" );
				break;
			}

			if ( pUser[m->snZone].Mode==USER_EMPTY )
			{
				SendAdminMessage( conn, 0, "The Zone Server is not working" );
				break;
			}
			pUser[m->snZone].cSock.SendOneMessage((char*)m,sizeof(MSG_NPGiftInfo));
			SendAdminMessage( conn, 0, "Gift setting complete" );
		} break;
	}

/*

	if	(std->Type==_MSG_NPCreateCharacter)		// redirect destination의 캐랙터 생성 
	{	
		MSG_NPCreateCharacter* m = (MSG_NPCreateCharacter*) msg;
		// Reply패킷준비	
		MSG_NPCreateCharacter_Reply	sm; sm.Type = _MSG_NPCreateCharacter_Reply;
		sm.Size		= sizeof(sm);
		sm.Slot		= m->Slot;
		sm.ID		= m->ID;
		sm.Result	= 0;
		strncpy(sm.Account,m->Account,ACCOUNTNAME_LENGTH);
//		strncpy(sm.szName,m->Mob.szName,szName_LENGTH);

		// 1. 원본 어카운트를 읽어온다. 어카운트가 없으면 디폴트 어카운트를 생성한다 ? => 에러코드3을 리턴한다.
		char * account	= m->Account;
		int slot		= m->Slot;
		int IdxName		= cFileDB.GetIndex(m->Account);
		if	(IdxName!=0)	{sm.Result = 3;pAdmin[conn].cSock.SendOneMessage((char*)&sm,sm.Size);return TRUE;}

		STRUCT_ACCOUNTFILE file;
		memcpy(file.AccountName,m->Account,ACCOUNTNAME_LENGTH);
		int ret = cFileDB.DBReadAccount(&file);
		if  (ret == FALSE)
		{	// 이전을 요청했는데 원본이 없다?
			char tt[256]; sprintf(tt,"etc tranper_FAILED!!!!!(read) %s %s",m->Account,m->Mob.szName);
			Log(tt,file.AccountName,0);
			sm.Result = 4;pAdmin[conn].cSock.SendOneMessage((char*)&sm,sm.Size);
			return TRUE;
		}
		
		for (int empty=0;empty<MOB_PER_ACCOUNT;empty++) 
		{	if	(file.Char[empty].szName[0]==0) break;
		}
		if	(empty==MOB_PER_ACCOUNT)	{sm.Result = 2;pAdmin[conn].cSock.SendOneMessage((char*)&sm,sm.Size);return TRUE;}
		//	동일이름 검사
		ret = cFileDB.CreateCharacter(m->Account,m->Mob.szName);
		if	(ret==FALSE)
		{	sm.Result = 1;pAdmin[conn].cSock.SendOneMessage((char*)&sm,sm.Size);
			return TRUE;
		}
		//

		char tt[256]; sprintf(tt,"etc tranper_success(deleted) %s %s",m->Account,m->Mob.szName);
		Log(tt,file.AccountName,0);
		memcpy(&file.Char[slot],&(m->Mob),sizeof(STRUCT_MOB));
		strupr(file.AccountName);
		ret=cFileDB.DBWriteAccount(&file);
		if  (ret==FALSE)
		{	char tt[256]; sprintf(tt,"etc tranper_FAILED!!!!!(write) %s %s",m->Account,m->Mob.szName);
			Log(tt,file.AccountName,0);
			sm.Result = 4;pAdmin[conn].cSock.SendOneMessage((char*)&sm,sm.Size);
			return TRUE;
		}
		sm.Result = 0;pAdmin[conn].cSock.SendOneMessage((char*)&sm,sm.Size);
	}	else
	if	(std->Type==_MSG_NPIDPASS)
	{	MSG_NPIDPASS *m = (MSG_NPIDPASS *) msg;
		strupr(m->Account);
		//BASE_Decrypt(m->Account,m->Pass,m->Encode1,m->Encode2);
		if (pAdmin[conn].Encode1!=m->Encode1 || pAdmin[conn].Encode2!=m->Encode2) return FALSE;
		if (pAdmin[conn].Level!=-1) return TRUE;
		STRUCT_ACCOUNTFILE file;
		memcpy(file.AccountName,m->Account,ACCOUNTNAME_LENGTH);
		int iret = cFileDB.DBReadAccount(&file);  
		if (iret==FALSE) return TRUE;
		if (file.AccountPass[0]=='_') return FALSE;  // 원래는 계정이 없는게 아니고, 사용할수 없는거(해지된 계정)
		if (file.AccountPass[0]=='@') return FALSE;   // 원래는 계정이 없는게 아니고, 사용할수 없는거(해지된 계정)
		char *p = (char*)file.AccountPass;
		iret = strncmp(m->Pass,p,ACCOUNTNAME_LENGTH);		 
		if (iret) return FALSE;
  
		int maxlevel=0;
		for (int i=0;i<MOB_PER_ACCOUNT;i++)
		{   if (file.Char[i].szName[0]!=0 && file.Char[i].BaseScore.Level>maxlevel) maxlevel = file.Char[i].BaseScore.Level;
		}
		if (maxlevel<1000) return FALSE;
		int admin = maxlevel-1000;
		pAdmin[conn].Level = admin; // 현재는 무조건 슈퍼  // 원래는 Char의 4개의 최고레벨 (Level-1024) 이 레벨
		pAdmin[conn].DisableID = 0;
		strncpy(pAdmin[conn].Name,m->Account,ACCOUNTNAME_LENGTH);
		char temp[256];
		sprintf(temp,"sys Admin Login Success - Level: %d",admin);
		Log(temp,pAdmin[conn].Name,pAdmin[conn].IP);  
		SendAdminMessage(conn,0,temp);
	}   */
   return TRUE;
}


void ProcessSecTimer( void )
{
	ImportUser();
	UpdateUser();
	SecCounter++;

	// AccountLogin에 딜레이를 주기 위한 코드?

	//
	//if	(SecCounter%120==0) ImportItem(); // Once per 2 min.
}


void ProcessMinTimer( void )
{
	//int nTotalWorldUserCount = 0;
	//for( int i = 0 ; i < MAX_SERVER ; i++ )
	//{	if(pUser[i].cSock.Sock == 0) continue;
	//	nTotalWorldUserCount += pUser[i].Count;
	//}
	//if (nTotalWorldUserCount>MaxDayUserCount) MaxDayUserCount=nTotalWorldUserCount;
	//struct tm when; time_t now;
	//time(&now); when= *localtime(&now);
	//if( LastUserCountDay!=when.tm_mday )
	//{	if ( LastUserCountDay==-1 )
	//	{	LastUserCountDay=when.tm_mday;
	//		return;
	//	}
	//	char Temp[256]={0,};
	//	sprintf(Temp,"UserCount %s",MaxDayUserCount);
	//	Log(Temp, "-system", 0);
	//}

	UpdateConnection();
	MinCounter++;
		
	if(MinCounter%30==0) UpdateConnectionData();

	if(MinCounter%60==0) cFileDB.CheckTrimuriti();

	HDC hDC = GetDC(hWndMain);
	if(hDC!=NULL) DrawInformations(hDC);
}


/////////////////////////////////////////////////////////////////////////////////
//
//  로그 파일 관련 펑션 StartLog(), Log()
//
//////////////////////////////////////////////////////////////////////////////////
void StartLog ( char * cccc )
{
	 char Temp[256];
     if (fLogFile!=NULL)
	 {  int ret=fclose(fLogFile);
	    if (ret) Log("Logfile close fail!!","-system",0);
	 }
	 struct tm when;
	 time_t now;
	 time(&now); when= *localtime(&now);
     sprintf(Temp,".\\Log\\DB%4.4d_%2.2d_%2.2d_%2.2d_%2.2d%s.txt",when.tm_year+1900,when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,cccc);
   	 fLogFile=fopen(Temp,"wt");
}		   

void Log(char * str1,char * str2,unsigned int ip)
{	 
	 struct tm when;
	 time_t now;
	 time(&now); when= *localtime(&now);
	 char LogTemp[512];
     sprintf(LogTemp,"%2.2d%2.2d%2.2d %2.2d%2.2d%2.2d %8.8x",when.tm_year-100,when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,when.tm_sec,ip);
     //int size=strlen(LogTemp);LogTemp[size-1]=0;
     sprintf(LogTemp,"%s %s %s \n",LogTemp,str2,str1);
	 if (fLogFile)
	 {  fprintf(fLogFile,LogTemp);
	 }
	 SetWindowText(hWndMain,LogTemp);
}



int GetUserFromSocket(int Sock)
{   for (int i=0;i<MAX_SERVERNUMBER;i++)
    {   if (pUser[i].cSock.Sock==(unsigned)Sock) return i;
	}
	return -1;
}

int GetAdminFromSocket(int Sock)
{   for (int i=0;i<MAX_ADMIN;i++)
    {   if (pAdmin[i].cSock.Sock==(unsigned)Sock) return i;
	}
	return -1;
}


int GetEmptyUser()
{
	for (int i=0;i<MAX_SERVERNUMBER;i++)   // 서버는 항상 0 부터 매핑 시킨다.
	{   if (pUser[i].Mode == USER_EMPTY) return i;
	}
	return -1;
}

int GetEmptyAdmin()
{
	for (int i=0;i<MAX_ADMIN;i++)   // 서버는 항상 0 부터 매핑 시킨다.
	{   if (pAdmin[i].Mode == USER_EMPTY) return i;
	}
	return -1;
}

void UpdateUser(void)
{
	char movefile[256];
	char filename[256];
	char temp[256];
	sprintf(temp,"Q:/serv%2.2d/update/*.*",ServerIndex);
	struct _finddata_t c_file;
	int hFindFile = _findfirst( temp, &c_file);
    if (hFindFile == -1L) return;
    char * ret;
	FILE *fp;
	int ssn1=0, ssn2=0;
	int count=0;
	do
	{
		 char id[128];
		 char pass[128];
		
		 if  (c_file.name[0]=='.')
		 {   int ret = _findnext(hFindFile, &c_file);
			 if (ret != 0) break;
			 continue;  
		 }
     	 //sprintf(filename,"Q:/serv%2.2d/update/*.*",ServerIndex,c_file.name);
		 sprintf(filename,"Q:/serv%2.2d/update/%s",ServerIndex,c_file.name);
		 sprintf(movefile,"Q:/serv%2.2d/err/%s",ServerIndex,c_file.name);
		 fp = fopen(filename,"rt");
         if  (fp!=NULL)
		 {  
             int len=0;
			 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
             ret = fgets(temp,127,fp);    if (ret==0) {fclose(fp);int ret = _findnext(hFindFile, &c_file);if (ret != 0) break;continue;}
			 sscanf(temp,"%s",id);len=strlen(id);
			 if (len==0||len>=ACCOUNTNAME_LENGTH)   {fclose(fp);int ret=_findnext(hFindFile, &c_file);if (ret != 0) break;	continue;}
			 strupr(id);
			 id[ACCOUNTNAME_LENGTH-1]=0;id[ACCOUNTNAME_LENGTH-2]=0;       
			 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
             ret = fgets(temp,127,fp);  if (ret==0) {fclose(fp);int ret=_findnext(hFindFile, &c_file);if (ret != 0) break;continue;}
			 sscanf(temp,"%s",pass);len=strlen(pass);
			 if (len==0||len>=ACCOUNTPASS_LENGTH)   {fclose(fp);int ret=_findnext(hFindFile, &c_file);if (ret != 0) break;continue;}
			 pass[ACCOUNTPASS_LENGTH-1]=0;pass[ACCOUNTPASS_LENGTH-2]=0;   
             /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			 ret = fgets(temp,127,fp);	if (ret==0) {fclose(fp);int ret=_findnext(hFindFile, &c_file);if (ret != 0) break;continue;}
			 sscanf(temp,"%d",&ssn1);
			 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			 ret = fgets(temp,127,fp);	if (ret==0) {fclose(fp);int ret=_findnext(hFindFile, &c_file);if (ret != 0) break;continue;}
			 sscanf(temp,"%d",&ssn2);
			 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
             fclose(fp);


			 int ret = 0;
			 ret = cFileDB.UpdateAccount(id,pass,ssn1,ssn2);
			 // 기접속중이면 AccountList도 수정.
			 /////////////////////////////////////////////////////////////////////
			 if (ret) ret =DeleteFile(filename);
			 else		MoveFile(filename,movefile);
			 //else {  Log("UpdateUser fail.",id); }
		 }
		 int ret = _findnext(hFindFile, &c_file);
		 if (ret != 0) break;
		 count++;
		 if (count>10) break;
	 } while(1);
	if (hFindFile!=-1L) _findclose(hFindFile);
     
	 return;
}	

void ProcessUser(void)
{
/*
char folder[27][16] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","etc"};
for (int fol=0;fol<27;fol++)
{
	

	 char temp[256];
	 sprintf(temp,"./account/%s/*.*",folder[fol]);
	 struct _finddata_t c_file;
	 int hFindFile = _findfirst( temp, &c_file);
     if (hFindFile == -1L) return;
	 char account[256];
	 FILE *fp;
	 do
	 {
		char filename[256];
		if	(c_file.name[0]=='.')
		{   int ret = _findnext(hFindFile, &c_file);
			if (ret != 0) break;
			continue;  
		}
		strcpy(account,c_file.name);
        strupr(account);
	 	sprintf(filename,"./account/%s/%s",folder[fol],c_file.name);
		fp = fopen(filename,"rb");
        if  (fp!=NULL)
		{	int coin = 0;
		    char ttt[256];
			STRUCT_ACCOUNTFILE  file;
           	int ret = fread(&file,sizeof(STRUCT_ACCOUNTFILE),1,fp);
            fclose(fp);
			for (int i=0;i<MOB_PER_ACCOUNT;i++)
			{
				if (file.Char[i].szName[0]==0) continue;
				coin = coin + file.Char[i].Coin;
				int moblvl = file.Char[i].BaseScore.Level;
		  		if	(file.Char[i].Guild!=0 &&file.Char[i].GuildLevel==0) 
				{	sprintf(ttt,",GUILD,%s, %4d, 0,0, 0,0,  0,0,",file.Char[i].szName, file.Char[i].Guild);
					Log(ttt,file.AccountName,0);
				}
		  		if	(file.Char[i].Guild!=0 &&file.Char[i].GuildLevel!=0) 
				{	sprintf(ttt,",GMASTER,%s, %4d, 0,0, 0,0,  0,0,",file.Char[i].szName, file.Char[i].Guild);
					Log(ttt,file.AccountName,0);
				}
				if	(file.Char[i].CurrentScore.Level>=29)
				{	sprintf(ttt,",LEVEL,%s, %d, %d,0, %d,0, 0,0, ", file.Char[i].szName,file.Char[i].CurrentScore.Level,file.Char[i].Class,0);
					Log(ttt,file.AccountName,0);
				}
                   //////////////////////////////////////////////////////////////////////////////////////
				for (int j=0;j<MAX_EQUIP;j++)
				{	STRUCT_ITEM * itm = &file.Char[i].Equip[j]; if (BASE_NeedLog(itm,0)==FALSE) continue;
					sprintf(ttt,",ITEM,Equip%d, %4d, %2d,%2d, %2d,%2d,  %2d,%2d,",j, itm->nIndex,itm->stEffect[0].cEffect,itm->stEffect[0].cValue,itm->stEffect[1].cEffect,itm->stEffect[1].cValue,itm->stEffect[2].cEffect,itm->stEffect[2].cValue);
					Log(ttt,file.AccountName,0);
				}
				for ( j=0;j<MAX_CARRY;j++)
				{	STRUCT_ITEM * itm = &file.Char[i].Carry[j];	if (BASE_NeedLog(itm,0)==FALSE) continue;
					sprintf(ttt,",ITEM,Carry%d, %4d, %2d,%2d, %2d,%2d,  %2d,%2d,",j, itm->nIndex,itm->stEffect[0].cEffect,itm->stEffect[0].cValue,itm->stEffect[1].cEffect,itm->stEffect[1].cValue,itm->stEffect[2].cEffect,itm->stEffect[2].cValue);
					Log(ttt,file.AccountName,0);
				}
			}
			coin = coin + file.Coin;
			for (int j=0;j<MAX_CARGO;j++)
			{	STRUCT_ITEM * itm = &file.Cargo[j];if (BASE_NeedLog(itm,0)==FALSE) continue;;
				sprintf(ttt,",6ITEM,Cargo%d, %4d, %2d,%2d, %2d,%2d,  %2d,%2d,",j, itm->nIndex,itm->stEffect[0].cEffect,itm->stEffect[0].cValue,itm->stEffect[1].cEffect,itm->stEffect[1].cValue,itm->stEffect[2].cEffect,itm->stEffect[2].cValue);
				Log(ttt,file.AccountName,0);
			}
			if  (coin>5000000) 
			{	sprintf(ttt,",MONEY,5,000,000, %8d,  0,0,  0,0, 0,0,",coin);
				Log(ttt,file.AccountName,0);
			}
		}
		int ret = _findnext(hFindFile, &c_file);
		if (ret != 0) break;
	}	while(1);
	if (hFindFile!=-1L) _findclose(hFindFile);
};
	return;
*/
}

void ImportUser(void)
{

	char movefile[256];
	char temp[256];
	sprintf(temp,"Q:/serv%2.2d/new/*.*",ServerIndex);
	 struct _finddata_t c_file;
	 int hFindFile = _findfirst( temp, &c_file);
     if (hFindFile == -1L) return;
     char * ret;
	 FILE *fp;
	 int count = 0;
	 do
	 {
		 char filename[256];
		 char id[128];
		 char pass[128];
		 int ssn1=0;
		 int ssn2=0;
		 if  (c_file.name[0]=='.')
		 {   int ret = _findnext(hFindFile, &c_file);
			 if (ret != 0) break;
			 continue;  
		 }
	 	 sprintf(filename,"Q:/serv%2.2d/new/%s",ServerIndex,c_file.name);
		 sprintf(movefile,"Q:/serv%2.2d/err/%s",ServerIndex,c_file.name);
		 fp = fopen(filename,"rt");
         if  (fp!=NULL)
		 {  
             int len=0;
			 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
             ret = fgets(temp,127,fp);    if (ret==0) {fclose(fp);int ret = _findnext(hFindFile, &c_file);if (ret != 0) break;continue;}
			 sscanf(temp,"%s",id);len=strlen(id);
			 if (len==0||len>=ACCOUNTNAME_LENGTH)   {fclose(fp);int ret=_findnext(hFindFile, &c_file);if (ret != 0) break;	continue;}
			 strupr(id);
			 id[ACCOUNTNAME_LENGTH-1]=0;id[ACCOUNTNAME_LENGTH-2]=0;       
			 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
             ret = fgets(temp,127,fp);  if (ret==0) {fclose(fp);int ret=_findnext(hFindFile, &c_file);if (ret != 0) break;continue;}
			 sscanf(temp,"%s",pass);len=strlen(pass);
			 if (len==0||len>=ACCOUNTPASS_LENGTH)   {fclose(fp);int ret=_findnext(hFindFile, &c_file);if (ret != 0) break;continue;}
			 pass[ACCOUNTPASS_LENGTH-1]=0;pass[ACCOUNTPASS_LENGTH-2]=0;   
             /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
             ret = fgets(temp,127,fp);  if (ret==0) {fclose(fp);int ret=_findnext(hFindFile, &c_file);if (ret != 0) break;continue;}
			 sscanf(temp,"%d",&ssn1);

			 ret = fgets(temp,127,fp);  if (ret==0) {fclose(fp);int ret=_findnext(hFindFile, &c_file);if (ret != 0) break;continue;}
			 sscanf(temp,"%d",&ssn2);



             /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
             fclose(fp);
			 int ret = cFileDB.AddAccount(id,pass,ssn1,ssn2);
			 /////////////////////////////////////////////////////////////////////
			 if (ret) ret =DeleteFile(filename);
			 else		MoveFile(filename,movefile);
		 }
		 int ret = _findnext(hFindFile, &c_file);
		 if (ret != 0) break;
		 count++;
		 if ( count>10 ) break;
	 } while(1);
	 if (hFindFile!=-1L) _findclose(hFindFile);
     
	 return;

}

void SetValidUser( int ServerNum, int AdminNum )
{	
	for	(int i=0;i<MAX_SERVERNUMBER;i++)
	{
		if	(i<ServerNum)
		{
			if	(pUser[i].cSock.pSendBuffer==NULL) pUser[i].cSock.pSendBuffer = (char*)malloc(SEND_BUFFER_SIZE);
			if	(pUser[i].cSock.pSendBuffer==NULL) 
			{	sprintf(temp,"err,get send buffer fail %d",i);
				Log(temp,"system",0);
			}
			if	(pUser[i].cSock.pRecvBuffer==NULL) pUser[i].cSock.pRecvBuffer = (char*)malloc(RECV_BUFFER_SIZE);
			if	(pUser[i].cSock.pRecvBuffer==NULL) 
			{	sprintf(temp,"err,get send buffer fail %d",i);
				Log(temp,"system",0);
			}
		}	else
		{	if	(pUser[i].cSock.pSendBuffer!=NULL) {free(pUser[i].cSock.pSendBuffer);pUser[i].cSock.pSendBuffer=NULL;}
			if	(pUser[i].cSock.pRecvBuffer!=NULL) {free(pUser[i].cSock.pRecvBuffer);pUser[i].cSock.pRecvBuffer=NULL;}
		}
	}

	for	(i=0;i<MAX_ADMIN;i++)
	{
		if	(i<AdminNum)
		{
			if	(pAdmin[i].cSock.pSendBuffer==NULL) pAdmin[i].cSock.pSendBuffer = (char*)malloc(SEND_BUFFER_SIZE);
			if	(pAdmin[i].cSock.pSendBuffer==NULL) 
			{	sprintf(temp,"err,get send buffer fail %d",i);
				Log(temp,"system",0);
			}
			if	(pAdmin[i].cSock.pRecvBuffer==NULL) pAdmin[i].cSock.pRecvBuffer = (char*)malloc(RECV_BUFFER_SIZE);
			if	(pAdmin[i].cSock.pRecvBuffer==NULL) 
			{	sprintf(temp,"err,get send buffer fail %d",i);
				Log(temp,"system",0);
			}
		}	else
		{	if	(pAdmin[i].cSock.pSendBuffer!=NULL) {free(pAdmin[i].cSock.pSendBuffer);pAdmin[i].cSock.pSendBuffer=NULL;}
			if	(pAdmin[i].cSock.pRecvBuffer!=NULL) {free(pAdmin[i].cSock.pRecvBuffer);pAdmin[i].cSock.pRecvBuffer=NULL;}
		}
	}
}

void SendUserCount(int conn)
{
	MSG_NPUserCount sm; sm.wType = _MSG_NPUserCount;
	sm.wPDULength = sizeof(MSG_NPUserCount)-sizeof(HEADER);

	for(int i=0;i<MAX_SERVER;i++) sm.nUserCount[i]=(pUser[i].cSock.Sock == 0 ) ? -1 : pUser[i].Count;
	
	int nConn = conn;
	if ( nConn == -1 )
	{	
		for( nConn = 0 ; nConn < MAX_ADMIN ; nConn++ )
		{	
			pAdmin[nConn].cSock.SendOneMessage((char*)&sm,sizeof(MSG_NPUserCount));
		}
	}
	else pAdmin[conn].cSock.SendOneMessage((char*)&sm,sizeof(MSG_NPUserCount));
}