#ifndef _HTFILE_H_
#define _HTFILE_H_

#include "HTString.h"

class CHTPackFileMgr;

//--------------------------------------------------------------------
// 경고 : 파일 라이브러리 임에 불구하고 exception handling이 전혀 안 
//			되어 있는 관계로 누군가가 필히 이부분을 넣어야 할 것이다!

//--------------------------------------------------------------------
// 파일 오프셋 기준 정의
#define HT_FILE_SEEK_SET	0
#define HT_FILE_SEEK_CUR	1
#define HT_FILE_SEEK_END	2

//--------------------------------------------------------------------
// 파일 속성
// CFile의 GetStatus의 Attribute에 정의되어 있는 것을 재정의 한것이다.
// 현재(2002/04/07)는 사용하지 않지만, 나중에 파일에 관한 세부적인 속성을 위해
// 남겨놓는다.
typedef enum _HT_FILEATTRIBUTE
{
	HT_FILEATT_NORMAL		= 0x00,
	HT_FILEATT_READONLY		= 0x01,
	HT_FILEATT_HIDDEN		= 0x02,
	HT_FILEATT_SYSTEM		= 0x04,
	HT_FILEATT_VOLUME		= 0x08,
	HT_FILEATT_DIRECTORY	= 0x10,
	HT_FILEATT_ARCHIVE		= 0x20

} HT_FILEATTRIBUTE;

//--------------------------------------------------------------------
// 파일 열기 옵션
typedef enum _HT_FILECREATEOPTION
{
	HT_FILEOPT_TEXT			= 10,
	HT_FILEOPT_BINARY		= 20,

	HT_FILEOPT_READWRITE	= 0,
	HT_FILEOPT_READONLY		= 1,
	HT_FILEOPT_WRITEONLY	= 2,
	HT_FILEOPT_APPENDONLY	= 3,

} HT_FILECREATEOPTION;

//--------------------------------------------------------------------
// 파일 상태 구조체
typedef struct _HT_FILESTATUS
{
	HTdword				dwFileLen;		// file size
	HTlong				lAccessTime;	// last access date/time of file
	HTlong				lModifyTime;	// last modification date/time of file
	HTlong				lCreateTime;	// creation date/time of file

} HT_FILESTATUS;


//--------------------------------------------------------------------
// 이름 : CHTFile
// 설명 : 파일 유틸리티 클래스 
class CHTFile
{
public:
	// Constructs a CTFile object from a path or file handle.
					CHTFile();
					CHTFile( CHTPackFileMgr* pMgr );
	virtual			~CHTFile();

	// Safely opens a file 
	HTbool			HT_bOpen( HTtchar* pFileName, HTword wOpenFlags );
	HTbool			HT_bOpen( CHTString& rstrFileName, HTword wOpenFlags );

	// Closes a file 
	HTvoid			HT_vClose();					

	// Reads (unbuffered) data from a file at the current file position.
	HTbool			HT_bRead( HTvoid* pBuf, const HTuint uCount );	
	HTbool			HT_bRead( HTbyte* pReadBuf );
	HTbool			HT_bRead( HTint* pReadBuf );
	HTbool			HT_bRead( HTfloat* pReadBuf );
	HTbool			HT_bReadString( HTtchar* pReadBuf, const HTuint uCount, const HTtchar cSep = '\0' );

	// writes (unbuffered) data in a file to the current file position.
	HTbool			HT_bWrite( const HTvoid* pvBuf, HTint iSize );
	HTbool			HT_bWrite( const HTbyte cItem );
	HTbool			HT_bWrite( const HTint iItem );
	HTbool			HT_bWrite( const HTfloat fItem );
	HTbool			HT_bWriteNewLine();

	HTbool			HT_bSeek(HTlong lOff, HTuint nFrom);	// Positions the current file pointer.	
	HTvoid			HT_vSeekToBegin();						// Positions the current file pointer at the beginning of the file.
	HTvoid 			HT_dwSeekToEnd();						// Positions the current file pointer at the end of the file.

	HTdword			HT_dwGetLength();					// Retrieves the length of the file.
	HTdword			HT_dwGetPosition() const;			// Retrieves the current file pointer.
	
	//test for end-of-file
	HTbool			HT_bIsEOF();					

 	HTtchar*		HT_pGetFileName();					// Retrieves the filename.
 	HTtchar*		HT_pGetFilePath();					// Retrieves the file path.
	HTbool			HT_bGetFullFileName(HTtchar* pFullName);// Retrieves the full file path of the selected file.

	// Retrieves the status of this open file.
	HT_FILESTATUS	HT_eGetStatus();				

	// Flushes any data yet to be written.
	HTint			HT_iFlush();							
	
	HTbool			HT_bLock( HTlong lBytes );		// Locks a range of bytes in a file
	HTbool			HT_bUnLock( HTlong lBytes );	// Unlocks a range of bytes in a file

	// set pack file mgr
	HTvoid			HT_vSetPackMgr( CHTPackFileMgr* pMgr )
	{ 
		m_pPackFileMgr = pMgr; 
	}


private:
	HTint			m_iFileHandle;						// file handle
	HTtchar			m_szFileName[HT_MAX_STR];		// only file name
	HTtchar			m_szFilePath[HT_MAX_STR];		// file path
	HT_FILESTATUS	m_eFileStatus;						// file status
	HTbool			m_bOpen;							// whether did open file

	CHTPackFileMgr*	m_pPackFileMgr;
	
private:
	HTvoid			HT_vSeparatePath(HTtchar* pFilePath);

};

#endif	// #ifndef _HTFILE_H_