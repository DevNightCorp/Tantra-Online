#include "StdAfx.h"
#include <stdlib.h>
#include "TFPercentMixer.h"
#include <stdio.h>
#include "TNDebug.h"

#if defined(__ZONE_SERVER__) && defined(__MEMORYMANAGER__)

#ifndef _HTMEMORYMANAGER_H_
#include "HTMemoryManager.h"
#endif

#endif //__ZONE_SERVER__, __MEMORYMANAGER__

CTFPercentMixer::CTFPercentMixer(void)
{
}

CTFPercentMixer::~CTFPercentMixer(void)
{
}

void CTFPercentMixer::Initialize()
{	
	for(int i=0; i<101; i++)
	{	m_snIndex[i] = 0;
		for(int k=0; k<100; k++)
		{	m_byValues[i][k]=0;
			if(i>k) m_byValues[i][k]=1;
		}
	}
	Reset();
}

void CTFPercentMixer::Reset()
{
	for(int i=0; i<101; i++)
	{
		for(int k=0; k<500; k++)
		{
			int nFirst = rand()%100;
			int nSecone = rand()%100;
			if(nFirst == nSecone) continue;
			int nTemp = m_byValues[i][nFirst];
			m_byValues[i][nFirst] = m_byValues[i][nSecone];
			m_byValues[i][nSecone] = nTemp;
		}
	}
}

void CTFPercentMixer::PartReset(int nPercent)
{
	for(int k=0; k<100; k++)
	{
		int nFirst = rand()%100;
		int nSecone = rand()%100;
		if(nFirst == nSecone) continue;
		int nTemp = m_byValues[nPercent][nFirst];
		m_byValues[nPercent][nFirst] = m_byValues[nPercent][nSecone];
		m_byValues[nPercent][nSecone] = nTemp;
	}

}

char CTFPercentMixer::GetValue(int nPercent)
{
	if(nPercent>100) nPercent=100;
	if(nPercent<0) nPercent=0;

	int snIndex = m_snIndex[nPercent]++;
	char byValue = m_byValues[nPercent][snIndex];

	//char pData[256] = {0,};
	//if(snIndex==0)
	//{	char pTemp[4] = {0,};
	//	sprintf(pData, "Percent Rate:%d	", nPercent);
	//	for(int i=0;i<100; i++)
	//	{	if(i%10) sprintf(pTemp, "%d", m_byValues[nPercent][i]);
	//		else sprintf(pTemp, " %d", m_byValues[nPercent][i]);
	//		strcat(pData, pTemp);
	//	}
	//	WriteLog(pData, ".\\Event\\[Log]Refining.txt");
	//	memset(pData, 0x00, sizeof(pData));
	//}
	//sprintf(pData, "\r\nPercent Index:%d, result:%d \r\n", snIndex, byValue);
	//WriteLog(pData, ".\\Event\\[Log]Refining.txt");

	if(m_snIndex[nPercent]>=100) 
	{
		m_snIndex[nPercent]=0;
		PartReset(nPercent);
	}

	return byValue;
}

char CTFPercentMixer::GetValue2(int nPercent)
{
	if(nPercent>100) nPercent=100;
	if(nPercent<0) nPercent=0;

	int snIndex = m_snIndex[nPercent];
	char byValue = m_byValues[nPercent][snIndex];

	return byValue;
}