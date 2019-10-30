//----------------------------------------------------------------------------//
//	파일 이름	: HTString.h
//	파일 설명 	: 
//		- String Handle 하는 클래스
//	작성자		:
//		- 2002/04/09, Created by HK (Reference to (Assrada & Heoraki)'s Cstr)
//
//  Copyright (c) 2000-2002 Hanbitsoft Corp.  All rights reserved.
//----------------------------------------------------------------------------//

#ifndef _HTSTRING_H_
#define _HTSTRING_H_

#include "ht.h"

class CHTString
{
public:
				CHTString();
				CHTString( CHTString& rszIn );
				CHTString( const HTtchar* szIn );
				~CHTString();

	HTint		HT_nGetSize();
	HTtchar*	HT_szGetString();
	HTbool		HT_bIsEmpty();
	HTRESULT	HT_hrCleanUp();

	HTtchar*	HT_szFormat( HTtchar* szIn, ... );

	HTtchar		HT_cGetAt( const HTuint nIndex );
	HTRESULT	HT_hrSetAt( const HTuint nIndex, const HTtchar cIn );
	HTRESULT	HT_hrSetAt( const HTuint nIndex, const HTtchar* szIn );
	HTRESULT	HT_hrSetAt( const HTuint nIndex, CHTString& rsIn );

	CHTString	HT_strFind( HTtchar* szIn );
	CHTString	HT_strFind( CHTString& rstrIn );
	HTbool		HT_bFind( HTtchar* szIn );

	HTbool		HT_bIsExtension( HTtchar* szIn );		// HK : HT_TRUE 이면 확장자가 szIn인 것.
	HTbool		HT_bIsExtension( CHTString& rstrIn );	// HK : HT_TRUE 이면 확장자가 rstrIn인 것.

	CHTString	HT_strGetExtention();

	HTRESULT	HT_hrDeletePath();
	HTRESULT	HT_hrExtractPath();
	
	CHTString&	operator=( CHTString& rsIn );
	CHTString&	operator=( const HTtchar* szIn );
	CHTString&	operator+=( CHTString& rsIn );
	CHTString&	operator+=( const HTtchar* szIn );
	CHTString&	operator+=( const HTtchar cIn );
	
	CHTString	operator+( CHTString& rsIn );
	CHTString	operator+( const HTtchar* szIn );
	CHTString	operator+( const HTtchar cIn );

	HTbool		operator==( CHTString& rsIn );
	HTbool		operator==( const HTtchar* szIn );
	HTbool		operator!=( CHTString& rsIn );
	HTbool		operator!=( const HTtchar* szIn );

	HTtchar&	operator[]( const HTint iIndex );
				operator HTtchar*();

	CHTString&	operator--();		// 앞에 한글자를 없앤다.
	CHTString&	operator--(HTint);	// 뒤에 한글자를 없앤다.

	HTRESULT	HT_hrDeleteCharFromFront( HTint iNum );	//후치 : 앞에 iNum만큼 글자를 없앤다.
	HTRESULT	HT_hrDeleteCharFromBack( HTint iNum );	//후치 : 뒤에 iNum만큼 글자를 없앤다.

	HTint		HT_iToInt();
	HTfloat		HT_fToFloat();

	inline static HTRESULT	HT_hrStringCopy( HTtchar* szDestination, const HTtchar* szSource, HTuint nDestinationByte )
	{
		if ( nDestinationByte == 0 || szSource == HT_NULL ) return HT_FAIL;
		
		_tcsncpy( szDestination, szSource, nDestinationByte );

		szDestination[nDestinationByte-1] = '\0';

		return HT_OK;
	};
	inline static HTRESULT	HT_hrStringCat( HTtchar* szDestination, const HTtchar* szSource, HTuint nDestinationByte )
	{
		HTint iDestinationSize, iSourceSize;

		iDestinationSize	= HT_iStringLength( szDestination );
		iSourceSize			= HT_iStringLength( szSource );

		if ( nDestinationByte == 0 ||
			szDestination == HT_NULL ||
			szSource == HT_NULL ||
			(HTint)nDestinationByte < (iSourceSize + iDestinationSize) ) return HT_FAIL;

		_tcsncat( szDestination, szSource, iSourceSize );

		szDestination[nDestinationByte-1] = '\0';

		return HT_OK;
	};

	// 두개의 CHTString을 입력받아 내용을 비교한다.
	inline static HTint		HT_iStringCompare( const HTtchar* szIn0, const HTtchar* szIn1 )
	{
		return _tcsicmp( szIn0, szIn1 );
	};
	// 자기 자신과 하나의 CHTString을 입력받아 내용을 비교한다.
	inline  HTint		HT_iStringCompare( const HTtchar* szIn1 )
	{
		return _tcsicmp( m_szString, szIn1 );
	};
	inline static HTint		HT_iStringLength( const HTtchar* szIn )
	{
		return ((HTint)_tcslen( szIn ));
	};
	inline static HTtchar*	HT_szSearchCharBackward( const HTtchar* szIn, HTtchar cIn )
	{
		return _tcsrchr( szIn, cIn );
	};
	inline static HTtchar*	HT_szSearchCharForward( const HTtchar* szIn, HTtchar cIn )
	{
		return _tcschr( szIn, cIn );
	};
	inline static HTfloat	HT_fASCIItoFloat( const HTtchar* szIn )
	{
		return (HTfloat)atof( szIn );
	};
	inline static HTint		HT_iASCIItoInt( const HTtchar* szIn )
	{
		return _ttoi( szIn );
	};
	
private:
	HTbool		HT_bIsDoubleByte( const HTtchar cIn );	// 2Byte면 HT_TRUE를 반환, 1Byte면 HT_FALSE를 반환

public:
private:
	HTtchar	m_szString[HT_MAX_STR];
};

CHTString operator+( HTtchar* szIn, CHTString& rsIn );

#endif // #ifdef _HTSTRING_H_