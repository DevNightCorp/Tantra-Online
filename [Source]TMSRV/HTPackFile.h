#ifndef _HTPACKFILE_H_
#define _HTPACKFILE_H_

#define HT_PACKFILEHANDLE_BASE	50000
#define HT_PACKFILEHANDLE_STEP	10000		// NOTICE: 한 팩파일당 10000개 이상의 파일이 
											// 있으면 이 부분을 수정해야 한다!
#define HT_MAX_FILENAME			40

typedef struct _HT_PACKFILE_INFO
{
	TCHAR				szFileName[HT_MAX_FILENAME];
	unsigned int		uOffset;			//	from body
	unsigned int		uSize;
	HTint				idFile;
} HT_PACKFILE_INFO;

typedef struct _HT_PACKFILE_HEADER
{
	int		iVersion;
	int		iFileCount;
	int		iHeaderSize;
} HT_PACKFILE_HEADER;

struct SHTLessStr
{
	template<typename PtrType>
		HTbool operator()( PtrType pStr1, PtrType pStr2 ) const
	{
		HTint i = stricmp( pStr1, pStr2 );
		if ( i < 0 )
			return ( HT_TRUE );
		else
			return ( HT_FALSE );
	}
};

typedef std::map<HTtchar*,HTbyte*,SHTLessStr>::value_type	HT_PackFile_Value;
typedef std::map<HTtchar*,HTbyte*,SHTLessStr>::iterator		HT_PackFile_It;
typedef std::map<HTint,HTtchar*>::value_type	HT_IDFileTable_Value;
typedef std::map<HTint,HTtchar*>::iterator		HT_IDFileTable_It;

class CHTPackFile
{
public:
						CHTPackFile();
						~CHTPackFile();

	HTRESULT			HT_hrOpen( CHTString& strFile, HTbool bUseMem );
	HTRESULT			HT_hrClose();
	HTbool				HT_bIsThereFile( HTtchar* szFile );
	CHTString&			HT_strGetName()	{ return ( m_strName );	}
	HTint				HT_iOpenFile( HTtchar* pFileName, HTword wOpenFlags );
	HTbool				HT_bCloseFile( HTint iFileHandle );

	HTbool				HT_bRead( HTint iFileHandle, HTvoid* pBuf, const HTuint uCount );	
	HTbool				HT_bRead( HTint iFileHandle, HTbyte* pReadBuf );
	HTbool				HT_bRead( HTint iFileHandle, HTint* pReadBuf );
	HTbool				HT_bRead( HTint iFileHandle, HTfloat* pReadBuf );
	HTbool				HT_bReadString( HTint iFileHandle, HTtchar* pReadBuf, const HTuint uCount, const HTtchar cSep = '\0' );

	HTbool				HT_bSeek( HTint iFileHandle, HTlong lOff, HTuint nFrom );
	HTvoid				HT_vSeekToBegin( HTint iFileHandle );
	HTvoid				HT_dwSeekToEnd( HTint iFileHandle );
	HTdword				HT_dwGetLength( HTint iFileHandle );
	HTdword				HT_dwGetPosition( HTint iFileHandle );
	HTbool				HT_bIsEOF( HTint iFileHandle );
	HTint				HT_iFlush( HTint iFileHandle );

	HTvoid*				HT_vpGetPointerToFileInMemory( HTtchar* szFile );
	HTvoid				HT_vCloseFileInMemory( HTtchar* szFile );

	HTuint				HT_nGetFileSize( HTtchar* szFile );

private:
	HT_PACKFILE_HEADER	m_oHeader;
	std::map<HTtchar*,HT_PACKFILE_INFO*,SHTLessStr>	m_mapFileInfos;
	CHTString			m_strName;
	HTbyte**			m_ppFileMemory;
	HT_PACKFILE_INFO*	m_arrInfos;
	HTbool				m_bUseMem;

	std::map<HTtchar*,HTbyte*,SHTLessStr>	m_mapFiles;
	std::map<HTint,HTtchar*>				m_mapIDFileTable;

};

typedef std::map<HTuint,CHTPackFile*>::iterator HT_PackFileMgr_It;
typedef std::map<HTuint,CHTPackFile*>::value_type HT_PackFileMgr_Value;

class CHTPackFileMgr
{
public:
						CHTPackFileMgr();
						~CHTPackFileMgr();

	HTRESULT			HT_hrOpenPackFile( CHTString& strFile, HTbool bUseMem = HT_TRUE );
	HTRESULT			HT_hrClosePackFile( CHTString& strFile );
	HTbool				HT_bIsThereFile( HTtchar* szFile );
	HTint				HT_iOpenFile( HTtchar* pFileName, HTword wOpenFlags );
	HTbool				HT_bCloseFile( HTint iFileHandle );

	// 아래의 두 함수는 쌍으로 다녀야 메모리가 줄어든다.
	HTvoid*				HT_vpGetPointerToFileInMemory( HTtchar* szFile );
	HTvoid				HT_vCloseFileInMemory( HTtchar* szFile );

	HTuint				HT_nGetFileSize( HTtchar* szFile );

	HTbool				HT_bRead( HTint iFileHandle, HTvoid* pBuf, const HTuint uCount );	
	HTbool				HT_bRead( HTint iFileHandle, HTbyte* pReadBuf );
	HTbool				HT_bRead( HTint iFileHandle, HTint* pReadBuf );
	HTbool				HT_bRead( HTint iFileHandle, HTfloat* pReadBuf );
	HTbool				HT_bReadString( HTint iFileHandle, HTtchar* pReadBuf, const HTuint uCount, const HTtchar cSep = '\0' );

	HTbool				HT_bSeek( HTint iFileHandle, HTlong lOff, HTuint nFrom );
	HTvoid				HT_vSeekToBegin( HTint iFileHandle );
	HTvoid				HT_dwSeekToEnd( HTint iFileHandle );
	HTdword				HT_dwGetLength( HTint iFileHandle );
	HTdword				HT_dwGetPosition( HTint iFileHandle );
	HTbool				HT_bIsEOF( HTint iFileHandle );
	HTint				HT_iFlush( HTint iFileHandle );

private:
	std::map<HTuint,CHTPackFile*>	m_mapPackFiles;
	HTint							m_idPacks;

};


#endif	// #ifndef _HTPACKFILE_H_