#include <STDIO.H>
#include "gamers.h"

CGamers::CGamers(void)
{
}

CGamers::~CGamers(void)
{
}

bool CGamers::UseCoupon(char* pData)		//	0:success, 1:already used Num, 2:out of Index, 3:already used User
{
	if(pData==NULL) return false;

	std::map<char*, int, HTStr>::iterator it = m_mapTable.find( pData );
	if ( it != m_mapTable.end() ) 
	{
		int nIndex = it->second;;
		if(m_stCoupon[nIndex].byUsed == 1) return false;

		m_stCoupon[nIndex].byUsed = 1;		//	쿠폰사용
		return true;
	}

	return false;
}

bool CGamers::Initialize()
{
	int nID=0; char pChar[SZCOUPON_LENGTH+1] = {0,};
	FILE * fp=fopen("Data\\Coupon.bin","rt"); 
	if(fp==NULL)		//	data struct file 없을 경우
	{	
		int nCount = 0;
		ZeroMemory(m_stCoupon, sizeof(m_stCoupon));
		fp=fopen("Data\\Coupon.txt","rt");
		if(fp == NULL)
		{
			//MessageBox(NULL,"Can't Read GamersCoupon Files!!!","Error",MB_OK);
			return false;
		}

		while(1)
		{
			ZeroMemory(pChar, SZCOUPON_LENGTH);
			char * ret = fgets((char*)pChar,sizeof(pChar),fp);
			if (ret==NULL) break;
			strncpy(m_stCoupon[nCount++].pstrData, pChar, strlen(pChar)-1);
		}
		WriteCoupon();
	}
	else
	{
		fread(m_stCoupon, sizeof(stCoupon), MAX_COUPONSIZE, fp);
	}

	for(int i=0; i<MAX_COUPONSIZE; i++)
	{
		if(m_stCoupon[i].pstrData[0] == 0)
		{	m_iMaxCoupon = i;
			break;
		}
		m_mapTable.insert( std::map<char*, int, HTStr>::value_type( m_stCoupon[i].pstrData, i ) );
	}

	fclose(fp);

	return true;
}

bool CGamers::WriteCoupon()
{
	FILE * fp = fopen("Data\\Coupon.bin","wt");
	if(fp==NULL)
	{
		MessageBox(NULL,"Can't Write Coupon.bin Files!!!","Error",MB_OK);
		return false;
	}

	fwrite(m_stCoupon, sizeof(stCoupon), MAX_COUPONSIZE, fp);
	fclose(fp);

	return true;
}

void CGamers::CloseEvent()
{
	WriteCoupon();
}
