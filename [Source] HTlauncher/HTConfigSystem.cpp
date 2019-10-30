#include "stdafx.h"
#include "HTConfigSystem.h"
#include "HTConsole.h"

CHTConfigSystem::CHTConfigSystem()
{
}

CHTConfigSystem::~CHTConfigSystem()
{
	std::map<string,HT_CONFIGCLASS*>::iterator itClasses;
	for ( itClasses = m_mapClasses.begin(); itClasses != m_mapClasses.end(); )
	{
		if ( itClasses->second )
		{
			itClasses->second->mapItemBool.clear();
			itClasses->second->mapItemInt.clear();
			itClasses->second->mapItemFloat.clear();
			itClasses->second->mapItemString.clear();

			HT_DELETE( itClasses->second );
		}

		itClasses = m_mapClasses.erase( itClasses );
	}
}

HTRESULT CHTConfigSystem::HT_hrLoad( HTtchar* pFileName )
{
	CHTFile oCfgFile;

	if ( !oCfgFile.HT_bOpen( pFileName, HT_FILEOPT_TEXT | HT_FILEOPT_READONLY ) )
		return ( HT_FAIL );

	HTtchar szReadBuf[HT_MAX_STR];
	HTtchar *pszToken = HT_NULL;
	CHTString strLine, strItem, strValue, strClass, strConsoleCommand;
	HT_CONFIGCLASS* pCfgClass = HT_NULL;
	HTint iVal;
	HTfloat fVal;

	while ( !oCfgFile.HT_bIsEOF() )
	{
		oCfgFile.HT_bReadString( szReadBuf, HT_MAX_STR, '\n' );
		strLine = szReadBuf;

		if ( strLine.HT_bFind( "[" ) && strLine.HT_bFind( "]" ))
		{
			strClass = _tcstok( (HTtchar*)strLine, "[]" );
			pCfgClass = new HT_CONFIGCLASS;
			m_mapClasses.insert( std::map<string,HT_CONFIGCLASS*>::value_type( (HTtchar*)strClass, pCfgClass ) );
		}
		else if ( strLine.HT_bFind( "=" ) )
		{
			if ( !pCfgClass )
			{
				MessageBox( NULL, "Config File Error!", "No class!", MB_OK );
				break;
			}

			if ( strLine.HT_bFind( "#" ) )
			{
				strConsoleCommand = _tcstok( (HTtchar*)strLine, "#" );
				strItem = _tcstok( HT_NULL, "=" );
				strValue = _tcstok( HT_NULL, "\n" );

				pCfgClass->mapItemConsoleCommand.insert( std::map<string,string>::value_type( (HTtchar*)strItem, (HTtchar*)strConsoleCommand ) );
			}
			else
			{
				strConsoleCommand.HT_hrCleanUp();
				strItem = _tcstok( (HTtchar*)strLine, "=" );
				strValue = _tcstok( HT_NULL, "\n" );
			}

			iVal = strValue.HT_iToInt();
			fVal = strValue.HT_fToFloat();

			if ( strValue.HT_bFind( "." ) )
				iVal = 0;
			else
				fVal = 0.0f;

			if ( strValue.HT_iStringCompare( "true" ) == 0 )
			{
				pCfgClass->mapItemBool.insert( std::map<string,HTbool>::value_type( (HTtchar*)strItem, HT_TRUE ) );
			}
			else if ( strValue.HT_iStringCompare( "false" ) == 0 )
			{
				pCfgClass->mapItemBool.insert( std::map<string,HTbool>::value_type( (HTtchar*)strItem, HT_FALSE ) );
			}
			else if ( fVal != 0.0f || strValue.HT_iStringCompare( "0.0" ) == 0 )
			{
				pCfgClass->mapItemFloat.insert( std::map<string,HTfloat>::value_type( (HTtchar*)strItem, fVal ) );
			}
			else if ( iVal != 0 || strValue.HT_iStringCompare( "0" ) == 0 )
			{
				pCfgClass->mapItemInt.insert( std::map<string,HTint>::value_type( (HTtchar*)strItem, iVal ) );
			}
			else
			{
				pCfgClass->mapItemString.insert( std::map<string,string>::value_type( (HTtchar*)strItem, (HTtchar*)strValue ) );
			}
		}
	}
	
	oCfgFile.HT_vClose();

	return ( HT_OK );
}

HTRESULT CHTConfigSystem::HT_hrSave( HTtchar* pFileName )
{
	return ( HT_OK );
}

HTRESULT CHTConfigSystem::HT_hrGetValue( HTtchar* szClassName, 
									HTtchar* szItemName, HTint* pValue )
{
	std::map<string,HT_CONFIGCLASS*>::iterator itClasses;
	itClasses = m_mapClasses.find( szClassName );
	if ( itClasses != m_mapClasses.end() )
	{
		std::map<string,HTint>::iterator itItems;
		itItems = (itClasses)->second->mapItemInt.find( szItemName ); 

		if ( itItems != (itClasses)->second->mapItemInt.end() )
		{
			*pValue = itItems->second;

			std::map<string,string>::iterator itConsoleCommand = (itClasses)->second->mapItemConsoleCommand.find( szItemName );
			if ( itConsoleCommand != (itClasses)->second->mapItemConsoleCommand.end() )
			{
				g_oConsole.HT_hrRegisterVariable( (HTtchar*)itConsoleCommand->second.c_str(), pValue );
			}

			return ( HT_OK );
		}

		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

HTRESULT CHTConfigSystem::HT_hrGetValue( HTtchar* szClassName, 
									HTtchar* szItemName, HTfloat* pValue )
{
	std::map<string,HT_CONFIGCLASS*>::iterator itClasses;
	itClasses = m_mapClasses.find( szClassName );
	if ( itClasses != m_mapClasses.end() )
	{
		std::map<string,HTfloat>::iterator itItems;
		itItems = (itClasses)->second->mapItemFloat.find( szItemName ); 

		if ( itItems != (itClasses)->second->mapItemFloat.end() )
		{
			*pValue = itItems->second;

			std::map<string,string>::iterator itConsoleCommand = (itClasses)->second->mapItemConsoleCommand.find( szItemName );
			if ( itConsoleCommand != (itClasses)->second->mapItemConsoleCommand.end() )
			{
				g_oConsole.HT_hrRegisterVariable( (HTtchar*)itConsoleCommand->second.c_str(), pValue );
			}

			return ( HT_OK );
		}

		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

HTRESULT CHTConfigSystem::HT_hrGetValue( HTtchar* szClassName, 
									HTtchar* szItemName, HTtchar* pValue )
{
	std::map<string,HT_CONFIGCLASS*>::iterator itClasses;
	itClasses = m_mapClasses.find( szClassName );
	if ( itClasses != m_mapClasses.end() )
	{
		std::map<string,string>::iterator itItems;
		itItems = (itClasses)->second->mapItemString.find( szItemName ); 

		if ( itItems != (itClasses)->second->mapItemString.end() )
		{
			_tcscpy( pValue, itItems->second.c_str() );

			return ( HT_OK );
		}

		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

HTRESULT CHTConfigSystem::HT_hrGetValue( HTtchar* szClassName, 
									HTtchar* szItemName, HTbool* pValue )
{
	std::map<string,HT_CONFIGCLASS*>::iterator itClasses;
	itClasses = m_mapClasses.find( szClassName );
	if ( itClasses != m_mapClasses.end() )
	{
		std::map<string,HTbool>::iterator itItems;
		itItems = (itClasses)->second->mapItemBool.find( szItemName ); 

		if ( itItems != (itClasses)->second->mapItemBool.end() )
		{
			*pValue = itItems->second;
			return ( HT_OK );
		}

		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

HTRESULT CHTConfigSystem::HT_hrGetValue( HTtchar* szClassName, 
									HTtchar* szItemName, HTuint* pValue )
{
	std::map<string,HT_CONFIGCLASS*>::iterator itClasses;
	itClasses = m_mapClasses.find( szClassName );
	if ( itClasses != m_mapClasses.end() )
	{
		std::map<string,HTint>::iterator itItems;
		itItems = (itClasses)->second->mapItemInt.find( szItemName ); 

		if ( itItems != (itClasses)->second->mapItemInt.end() )
		{
			*pValue = itItems->second;	// TODO : 손실이 일어날 수 있을 정도로 숫자들이 크지 않다고 가정한다.
			return ( HT_OK );
		}

		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

HTRESULT CHTConfigSystem::HT_hrSetValue( HTtchar* szClassName, 
									HTtchar* szItemName, const HTint iValue )
{
	std::map<string,HT_CONFIGCLASS*>::iterator itClasses;
	itClasses = m_mapClasses.find( szClassName );
	if ( itClasses != m_mapClasses.end() )
	{
		std::map<string,HTint>::iterator itItems;
		itItems = (itClasses)->second->mapItemInt.find( szItemName ); 

		if ( itItems != (itClasses)->second->mapItemInt.end() )
		{
			itItems->second = iValue;
			return ( HT_OK );
		}

		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

HTRESULT CHTConfigSystem::HT_hrSetValue( HTtchar* szClassName, 
									HTtchar* szItemName, const HTfloat fValue )
{
	std::map<string,HT_CONFIGCLASS*>::iterator itClasses;
	itClasses = m_mapClasses.find( szClassName );
	if ( itClasses != m_mapClasses.end() )
	{
		std::map<string,HTfloat>::iterator itItems;
		itItems = (itClasses)->second->mapItemFloat.find( szItemName ); 

		if ( itItems != (itClasses)->second->mapItemFloat.end() )
		{
			itItems->second = fValue;
			return ( HT_OK );
		}

		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

HTRESULT CHTConfigSystem::HT_hrSetValue( HTtchar* szClassName, 
									HTtchar* szItemName, const HTtchar* pValue )
{
	std::map<string,HT_CONFIGCLASS*>::iterator itClasses;
	itClasses = m_mapClasses.find( szClassName );
	if ( itClasses != m_mapClasses.end() )
	{
		std::map<string,string>::iterator itItems;
		itItems = (itClasses)->second->mapItemString.find( szItemName ); 

		if ( itItems != (itClasses)->second->mapItemString.end() )
		{
			itItems->second = pValue;
			return ( HT_OK );
		}

		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

HTRESULT CHTConfigSystem::HT_hrSetValue( HTtchar* szClassName, 
									HTtchar* szItemName, const HTbool bValue )
{
	std::map<string,HT_CONFIGCLASS*>::iterator itClasses;
	itClasses = m_mapClasses.find( szClassName );
	if ( itClasses != m_mapClasses.end() )
	{
		std::map<string,HTbool>::iterator itItems;
		itItems = (itClasses)->second->mapItemBool.find( szItemName ); 

		if ( itItems != (itClasses)->second->mapItemBool.end() )
		{
			itItems->second = bValue;
			return ( HT_OK );
		}

		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

HTRESULT CHTConfigSystem::HT_hrSetValue( HTtchar* szClassName, 
									HTtchar* szItemName, const HTuint nValue )
{
	std::map<string,HT_CONFIGCLASS*>::iterator itClasses;
	itClasses = m_mapClasses.find( szClassName );
	if ( itClasses != m_mapClasses.end() )
	{
		std::map<string,HTint>::iterator itItems;
		itItems = (itClasses)->second->mapItemInt.find( szItemName ); 

		if ( itItems != (itClasses)->second->mapItemInt.end() )
		{
			itItems->second = nValue;
			return ( HT_OK );
		}

		return ( HT_FAIL );
	}

	return ( HT_FAIL );
}

