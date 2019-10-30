/****************************************************************************

	파일명 : TNDebug.h

	작성자 : 정재웅(spencerj@korea.com)
	작성일 : 2003-11-22

	Tab size : 4 spaces
	프로젝트명 : Tantra


	설명 : 
		-  
		- 

****************************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <time.h> 
#include "TNDebug.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

void WriteLog( char* pLog, char* chFileName )
{	
	HANDLE		hFile;
	DWORD		dwRetWrite;
	int			nBufLength;

	CreateDirectory( "\\Data", NULL) ;
	nBufLength	= (int)strlen(pLog);
	hFile = CreateFile(chFileName,					  // file name
                                GENERIC_WRITE|GENERIC_READ,   // open for writing 
                                FILE_SHARE_WRITE,             // do not share 
                                NULL,                         // no security 
                                OPEN_ALWAYS,                  // open or create 
                                FILE_ATTRIBUTE_NORMAL,        // normal file 
                                NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
	}
	else
	{
		SetFilePointer(hFile, 0, NULL, FILE_END);
		WriteFile(hFile, pLog, nBufLength, &dwRetWrite, NULL);
		CloseHandle(hFile);
	}
}

void TimeWriteLog( char* pLog, char* chFileName )
{	
	HANDLE		hFile;
	DWORD		dwRetWrite;
	int			nBufLength;

	struct tm when;
	time_t now;
	time(&now); when= *localtime(&now);
	char LogTemp[512]; memset(LogTemp,0,512);
    sprintf(LogTemp,"%2.2d%2.2d%2.2d %2.2d%2.2d%2.2d    ",when.tm_year-100,when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,when.tm_sec);

	CreateDirectory( "\\Data", NULL) ;
	nBufLength	= (int)strlen(pLog);
	hFile = CreateFile(chFileName,					  // file name
                                GENERIC_WRITE|GENERIC_READ,   // open for writing 
                                FILE_SHARE_WRITE,             // do not share 
                                NULL,                         // no security 
                                OPEN_ALWAYS,                  // open or create 
                                FILE_ATTRIBUTE_NORMAL,        // normal file 
                                NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
	}
	else
	{
		SetFilePointer(hFile, 0, NULL, FILE_END);
		WriteFile(hFile, LogTemp, (int)strlen(LogTemp), &dwRetWrite, NULL);
		WriteFile(hFile, pLog, nBufLength, &dwRetWrite, NULL);
		CloseHandle(hFile);
	}
}




