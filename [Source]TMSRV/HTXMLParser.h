#ifndef _HTXMLPARSER_H_
#define _HTXMLPARSER_H_

//#include "HTNew_Off.h"

#include <atlbase.h>
#include <atlcom.h>

#import "msxml3.dll"
using namespace MSXML2;

//#include "HTNew_On.h"

inline HTvoid HT_TESTHR( HRESULT _hr ) 
   { if FAILED(_hr) throw(_hr); }


class CHTXMLParser
{
public:
						CHTXMLParser();
						~CHTXMLParser();

	HTRESULT			HT_hrOpen( CHTString& strFile );
	HTRESULT			HT_hrClose();
	HTuint				HT_nGetTableRowCount( CHTString& strTable );
	HTbool				HT_isThereTable( CHTString& strTable );
	HTuint				HT_nGetTableCount()		{ return ( m_lTableCount ); }

	HTRESULT			HT_hrGetTableValue( CHTString& strTable, CHTString& strField, 
		HTuint idxRow, HTint* pVal );
	HTRESULT			HT_hrGetTableValue( CHTString& strTable, CHTString& strField, 
		HTuint idxRow, HTtchar* pVal );

private:
	MSXML2::IXMLDOMDocument2Ptr	m_docPtr;
	MSXML2::IXMLDOMNodeListPtr	m_pNodeList;
	HTlong						m_lTableCount;


	MSXML2::IXMLDOMNode*		HT_pGetTableNode( CHTString& strTable );

};

/*
 * AnsiToUnicode converts the ANSI string pszA to a Unicode string
 * and returns the Unicode string through ppszW. Space for the
 * the converted string is allocated by AnsiToUnicode.
 */
inline HRESULT __fastcall AnsiToUnicode(LPCSTR pszA, LPOLESTR* ppszW)
{
   ULONG cCharacters;
   DWORD dwError;

   // If input is null then just return the same.
   if (NULL == pszA)
   {
      *ppszW = NULL;
      return NOERROR;
   }

   // Determine number of wide characters to be allocated for the
   // Unicode string.
   cCharacters =  strlen(pszA)+1;

   // Use of the OLE allocator is required if the resultant Unicode
   // string will be passed to another COM component and if that
   // component will free it. Otherwise you can use your own allocator.
   *ppszW = (LPOLESTR) CoTaskMemAlloc(cCharacters*2);
   if (NULL == *ppszW)
      return E_OUTOFMEMORY;

   // Covert to Unicode.
   if (0 == MultiByteToWideChar(CP_ACP, 0, pszA, cCharacters,
                                *ppszW, cCharacters))
   {
      dwError = GetLastError();
      CoTaskMemFree(*ppszW);
      *ppszW = NULL;
      return HRESULT_FROM_WIN32(dwError);
   }

   return NOERROR;
}


/*
 * UnicodeToAnsi converts the Unicode string pszW to an ANSI string
 * and returns the ANSI string through ppszA. Space for the
 * the converted string is allocated by UnicodeToAnsi.
 */
inline HRESULT __fastcall UnicodeToAnsi(LPCOLESTR pszW, LPSTR* ppszA)
{
   ULONG cbAnsi, cCharacters;
   DWORD dwError;

   // If input is null then just return the same.
   if (pszW == NULL)
   {
       *ppszA = NULL;
       return NOERROR;
   }

   cCharacters = wcslen(pszW)+1;
   // Determine number of bytes to be allocated for ANSI string. An
   // ANSI string can have at most 2 bytes per character (for Double
   // Byte Character Strings.)
   cbAnsi = cCharacters*2;

   // Use of the OLE allocator is not required because the resultant
   // ANSI string will never be passed to another COM component. You
   // can use your own allocator.
   *ppszA = (LPSTR) CoTaskMemAlloc(cbAnsi);
   if (NULL == *ppszA)
      return E_OUTOFMEMORY;

   // Convert to ANSI.
   if (0 == WideCharToMultiByte(CP_ACP, 0, pszW, cCharacters, *ppszA,
                                cbAnsi, NULL, NULL))
   {
      dwError = GetLastError();
      CoTaskMemFree(*ppszA);
      *ppszA = NULL;
      return HRESULT_FROM_WIN32(dwError);
   }

   return NOERROR;
}

#endif	// #ifndef _HTXMLPARSER_H_