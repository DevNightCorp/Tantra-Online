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
    
	// ��Ʈ�� �ʱ�ȭ
	g_pNetWorkMgr					= NULL;
	g_pNetWorkMgr					= new TNNetworkManager;
	//	WinSocket �ʱ�ȭ
	g_cCPSock.WSAInitialize();
	g_cCPSock.SetServerSecret();
	
	//	���ΰ��� ���� �ѹ��� ������Ʈ
	g_bOneTimeUpdate				= GAMESEQUNCE_MAINGAME_NONE;

	//	���� ����Ʈ ��������
	HTint iType, iContryType;
	BASE_InitializeServerList_Client( &iType, &iContryType );
	//  ������ �׽�Ʈ�������� ���μ������� ����
	if( iType == 0 )        g_gServerType = SERVERTYPE_TEST;
	else					g_gServerType = SERVERTYPE_MAIN;
	//	���� Ÿ�� �˾ƿ���
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

	// "-netscript" �ɼǿ� ���� �������� ���� �����Ѵ�.
	//if( strncmp( lpCmdLine, "-v3goodluck", strlen("-v3goodluck") ) == 0)
    //    g_bDevelopingMode = HT_TRUE;
	// �������� �����ϴ�("-netscript"�ɼ��� ����) ��쿡�� �̷���...
//	else
		g_bDevelopingMode = HT_FALSE;
	g_bTransparencyMode = HT_FALSE;

	char szConnect[100];
	char szVer[100];
	sscanf( lpCmdLine, "%s %s", szConnect, szVer );

	//	������ ���� ������� ����
	if( !g_bDevelopingMode )
	{
		if( atoi(szConnect) == 0 )
		{
			// TANTRA.EXE ������ ���Ͽ� �����Ͽ� �ֽʽÿ�.
			MessageBox( NULL, "You must the game with Tantra.exe.", "Warning !", MB_OK | MB_ICONEXCLAMATION );
			exit(0);
		}
	}

	// Update.exe�κ��� ���� ��ġ������ Ŭ���̾�Ʈ ������ ���� �����ϴ� ������ ���Ͽ� ���� ������ �������� ���ϰ� �Ѵ�.
	//	���Ŀ��� ���������� �о�´�.
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
		//	�Ű������� ���� ������ ���Ѵ�.
		if ( stricmp( szVer, strVersion ) != 0 )
		{
			// Ŭ���̾�Ʈ ������ ���� �ʽ��ϴ�.
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


	//	���� ����Ÿ �ʱ�ȭ�� �����ϸ� ���Ӽ����� ��������.
	if( bGameResult == HT_OK )
	{
		//	��ü ���� ����
		while( 1 )
		{
			//	Intro Part
			bGameResult = g_CGame->ReadyGameLoop();
			if( bGameResult == RETURNTYPE_EXIT_INTRO )
			{
				// ��Ʈ�θ޴��� Ŭ����
				HT_DELETE( g_cIntroManager );
				break;
			}
			else
			{
				// ��Ʈ�θ޴��� Ŭ����
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

	//-----���� Ŭ���� �ϱ�-----//
	g_CGame->Finalize();
	HT_DELETE( g_CGame );

	// HK : 20040823
	// ����ÿ� ���� �� ���Ǵ� ��Ű ������ Ŭ���� �ϴ� �� �������� �ѹ� ȣ������� �� �ʿ䰡 �ִ�.
	// HK : 20041125
	// ����� �̰��� �ҷ���� �ϳ� �� �Լ� �ȿ� ���ּҰ� HTMessage �����͸� ���� �����ؾ� �Ѵ�. ���� HTMessage �� �����ϱ� ���� ȣ���� �ش�.
	//g_pEngineHandler->HT_hrClearWebCookies();

	return 0;
}



