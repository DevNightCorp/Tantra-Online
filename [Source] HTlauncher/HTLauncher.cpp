// HTLauncher.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "HTextern.h"
#include "HTWindowManager.h"
#include "HTEngineHandler.h"
#include "resource.h"

DWORD GetFileCheckSum( char* strFile )
{
	DWORD dwCheckSum = 0;
	FILE* fp;
	UINT nBuf;

	if ( fp = fopen( strFile, "r" ) )
	{
		while ( !feof(fp) )
		{
			fread( &nBuf, sizeof(UINT), 1, fp );
			dwCheckSum += nBuf;
		}

		dwCheckSum = (dwCheckSum >> 16) + (dwCheckSum & 0xffff);
		dwCheckSum += (dwCheckSum >>16);
		dwCheckSum = ~dwCheckSum;

		fclose( fp );
	}

	return ( dwCheckSum );
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     HTint     nCmdShow)
{ 
	g_iGameSequnce = 0;
    
	// 네트웍 초기화
	g_pNetWorkMgr					= NULL;
	g_pNetWorkMgr					= new TNNetworkManager;
	//	WinSocket 초기화
	g_cCPSock.WSAInitialize();
	g_cCPSock.SetServerSecret();
	
	//	메인게임 루프 한번만 업데이트
	g_bOneTimeUpdate				= GAMESEQUNCE_MAINGAME_NONE;

	//	서버 리스트 가져오기
	HTint iType, iContryType;
	BASE_InitializeServerList_Client( &iType, &iContryType );
	//  서버가 테스트서버인지 메인서버인지 구분
	if( iType == 0 )        g_gServerType = SERVERTYPE_TEST;
	else					g_gServerType = SERVERTYPE_MAIN;
	//	국가 타입 알아오기
	g_iInationalType = iContryType;

	if( g_iInationalType == INATIONALTYPE_KOREA )
        setlocale( LC_ALL, "kor" );
	else if( g_iInationalType == INATIONALTYPE_CHINA )
		setlocale( LC_ALL, "chs" );
	else if( g_iInationalType == INATIONALTYPE_JAPEN )
		setlocale( LC_ALL, "japanese" );
	else if( g_iInationalType == INATIONALTYPE_TAIWAN )
		setlocale( LC_ALL, "chinese-traditional" );
	else
		setlocale( LC_ALL, "English" );

	// "-netscript" 옵션에 따라서 개발중인 모드로 설정한다.
	//if( strncmp( lpCmdLine, "-v3goodluck", strlen("-v3goodluck") ) == 0)
    //    g_bDevelopingMode = HT_TRUE;
	// 유저들이 실행하는("-netscript"옵션이 없는) 경우에는 이렇게...
//	else
		g_bDevelopingMode = HT_FALSE;
	g_bTransparencyMode = HT_FALSE;

	char szConnect[100];
	char szVer[100];
	sscanf( lpCmdLine, "%s %s", szConnect, szVer );

	//	버젼이 맞지 않을경우 리턴
	if( !g_bDevelopingMode )
	{
		if( atoi(szConnect) == 0 )
		{
			// TANTRA.EXE 파일을 통하여 실행하여 주십시오.
			MessageBox( NULL, "You must the game with Tantra.exe.", "Warning !", MB_OK | MB_ICONEXCLAMATION );
			exit(0);
		}
	}

	// Update.exe로부터 받은 패치상태의 클라이언트 버전과 지금 실행하는 버전과 비교하여 이전 버전을 실행하지 못하게 한다.
	//	런쳐에서 버젼정보를 읽어온다.
	void* pBuffer = HT_NULL; 
	VS_FIXEDFILEINFO *pFixedInfo;
	UINT uVersionLen;
	char strVersion[100];
	DWORD dwHandle;     
	DWORD dwDataSize = ::GetFileVersionInfoSize((LPTSTR)"HTLauncher.exe", &dwHandle); 
	pBuffer = malloc(dwDataSize); 
	if (pBuffer)
	{
		GetFileVersionInfo((LPTSTR)"HTLauncher.exe", dwHandle, dwDataSize, pBuffer);
		VerQueryValue(pBuffer,_T("\\"),(void**)&pFixedInfo,(UINT *)&uVersionLen);  

		sprintf(strVersion, "%u.%u.%u.%u", 
			HIWORD (pFixedInfo->dwFileVersionMS),
			LOWORD (pFixedInfo->dwFileVersionMS),
			HIWORD (pFixedInfo->dwFileVersionLS),
			LOWORD (pFixedInfo->dwFileVersionLS)); 
		free(pBuffer);

		sscanf( strVersion, "%d.%d.%d.%d", &g_snVersionCheck[0], &g_snVersionCheck[1], &g_snVersionCheck[2], &g_snVersionCheck[3] );
	}

	if( !g_bDevelopingMode )
	{
		//	매개변수로 들어온 버젼과 비교한다.
		if ( stricmp( szVer, strVersion ) != 0 )
		{
			// 클라이언트 버전이 맞지 않습니다.
			MessageBox( NULL, "Client Version Error!", "Warning !", MB_OK | MB_ICONEXCLAMATION );
			exit(0);
		}
	}

	//	Open Debug File
	HT_g_vOpenDebugFile();

	//	Make Window
	g_CGame = new CHTWindowManager;

	//----------------------------------------------------------------------------------
	//	Game Roop
	//----------------------------------------------------------------------------------
	HTRESULT bGameResult;
	bGameResult = g_CGame->Initialize(hInstance, hPrevInstance, lpCmdLine, nCmdShow);


	//	최초 데이타 초기화가 성공하면 게임속으로 진임힌다.
	if( bGameResult == HT_OK )
	{
		//	전체 게임 루프
		while( 1 )
		{
			//	Intro Part
			bGameResult = g_CGame->ReadyGameLoop();
			if( bGameResult == RETURNTYPE_EXIT_INTRO )
			{
				// 인트로메니져 클리어
				HT_DELETE( g_cIntroManager );
				break;
			}
			else
			{
				// 인트로메니져 클리어
				HT_DELETE( g_cIntroManager );
				g_CGame->HT_hrMainLoopBeforeInit();
			}

			//	MainGame Part
			bGameResult = g_CGame->MainGameLoop();
			if( g_byReStartCode == 3 )
			{
				break;
			}
		}
	}

	//-----엔진 클린업 하기-----//
	g_CGame->Finalize();
	HT_DELETE( g_CGame );

	// HK : 20040823
	// 종료시에 결제 중 사용되는 쿠키 정보를 클리어 하는 웹 페이지를 한번 호출해줘야 할 필요가 있다.
	// HK : 20041125
	// 종료시 이것을 불러줘야 하나 이 함수 안에 웹주소가 HTMessage 포인터를 통해 접근해야 한다. 따라서 HTMessage 를 삭제하기 전에 호출해 준다.
	//g_pEngineHandler->HT_hrClearWebCookies();

	return 0;
}



