// DES.h: interface for the DES class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DES_H__30E4BD94_DC18_40DA_88E2_7C79D13DF16E__INCLUDED_)
#define AFX_DES_H__30E4BD94_DC18_40DA_88E2_7C79D13DF16E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum    {ENCRYPT,DECRYPT};

class DES  
{
public:
	bool Des_Go(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type);
	DES();
	virtual ~DES();

};

#endif // !defined(AFX_DES_H__30E4BD94_DC18_40DA_88E2_7C79D13DF16E__INCLUDED_)
