#include "StdAfx.h"
#include "HTFXIDDef.h"
#include "HTFXResMgr.h"
#include "..\..\Engine\HTUtilLib\HTFile.h"
#include "..\..\Engine\HTUtilLib\HTXMLParser.h"

#define HT_FXRESTABLE_PCSKILL		1
#define HT_FXRESTABLE_PCSKILLACTION	2
#define HT_FXRESTABLE_PCSKILLACTIVE	3
#define HT_FXRESTABLE_PCFX			4
#define HT_FXRESTABLE_STRING		5
#define HT_FXRESTABLE_MONSKILL		6
#define HT_FXRESTABLE_MONEFFECT		7
#define HT_FXRESTABLE_MONFX			8

CHTFXBaseResTable::CHTFXBaseResTable() : m_nItems (0) {}
CHTFXBaseResTable::~CHTFXBaseResTable() {}
HTbool CHTFXBaseResTable::HT_bGetSkillID( HTdword dwID, HTdword& dwSkillID ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetUI( HTdword dwID, HTdword& dwUI ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetReadyFX( HTdword dwID, HTdword& dwFX ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetCastFX( HTdword dwID, HTdword& dwFX ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetActivateFX( HTdword dwID, HTdword& dwFX ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetFollowFX( HTdword dwID, HTdword& dwFX ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetImpactFX( HTdword dwID, HTdword& dwFX ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetStateFX( HTdword dwID, HTdword& dwFX ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetIsWeaponBack( HTdword dwID, HTbool& bIsWeaponBack ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniReadyMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniCastMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniActivateMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniReadyMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniCastMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniActivateMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniReadyMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniCastMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniActivateMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniReadyManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniCastManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniActivateManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniReadyWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniCastWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniActivateWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniReadyWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniCastWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniActivateWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniReadyWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniCastWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniActivateWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniReadyWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniCastWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniActivateWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionSoundActivateMan( HTdword dwID, HTdword& dwSound ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActionSoundActivateWom( HTdword dwID, HTdword& dwSound ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActiveAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActiveAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActiveAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActiveAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActiveAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillActiveAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillType( HTdword dwID, HTdword& dwType ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetSkillAni( HTdword dwID, HTdword& dwAni ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwCategory, HTdword& dwWhereAttach, HTdword& dwPriority ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetName( HTdword dwID, CHTString& strName ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetDesc( HTdword dwID, CHTString& strDesc ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetBornFX( HTdword dwID, HTdword& dwFX ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetDieActivateFX( HTdword dwID, HTdword& dwFX ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetAlwaysFX( HTdword dwID, HTdword& dwFX ) { return HT_FALSE; }
HTbool CHTFXBaseResTable::HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwWhereAttach, HTdword& dwPriority ) { return HT_FALSE; }

// -------------------------------------------------------------------------------------
// CHTFXResTablePCSkill
// -------------------------------------------------------------------------------------

CHTFXResTablePCSkill::CHTFXResTablePCSkill(){}
CHTFXResTablePCSkill::~CHTFXResTablePCSkill()
{
	HTResTablePCSkill_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTFXResTablePCSkill::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return HT_FAIL;

	m_strTable = strTable;

	HTResTablePCSkill* pRecord = HT_NULL;
	HTint iID, iTemp;
	CHTString strCell;
	CHTString strBuffer;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ. 

	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTablePCSkill;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Name");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)strBuffer );	pRecord->strName = (HTtchar*)strBuffer;
		strCell = _T("Desc");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)strBuffer );	pRecord->strDesc = (HTtchar*)strBuffer;
		strCell = _T("SkillID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );				pRecord->dwSkillID = (HTdword)iTemp;
		strCell = _T("UIID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );				pRecord->dwUI = (HTdword)iTemp;

		m_mapTable.insert( HTResTablePCSkill_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTablePCSkill::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return HT_FAIL;

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTResTablePCSkillLS oReadBuffer;
	HTResTablePCSkill* pRecord = HT_NULL;

	HTint iID;
	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pFile->HT_bRead( &iID );
		pFile->HT_bRead( &oReadBuffer, sizeof(HTResTablePCSkillLS) );

		pRecord = new HTResTablePCSkill;
		pRecord->dwSkillID = oReadBuffer.dwSkillID;
		pRecord->dwUI = oReadBuffer.dwUI;
		pRecord->strName = oReadBuffer.szName;
		pRecord->strDesc = oReadBuffer.szDesc;

		m_mapTable.insert( HTResTablePCSkill_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTablePCSkill::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return HT_FAIL;

	HTResTablePCSkill_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_FXRESTABLE_PCSKILL;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// ¡Ÿ ºˆ

	HTint iID;
	HTResTablePCSkillLS oWriteBuffer;

	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );

		memset( &oWriteBuffer, 0, sizeof(HTResTablePCSkillLS) );
		oWriteBuffer.dwSkillID = (itTable->second)->dwSkillID;
		oWriteBuffer.dwUI = (itTable->second)->dwUI;
		CHTString::HT_hrStringCopy( oWriteBuffer.szName, (itTable->second)->strName, 100 );
		CHTString::HT_hrStringCopy( oWriteBuffer.szDesc, (itTable->second)->strDesc, 100 );

		pFile->HT_bWrite( &oWriteBuffer, sizeof(HTResTablePCSkillLS) );
		itTable++;
	}

	return ( HT_OK );
}

HTdword
CHTFXResTablePCSkill::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return 0;

	HTResTablePCSkill_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow )
	{
		itTable++;
		++i;
	}

	if ( itTable != m_mapTable.end() ) return itTable->first;

	return 0;
}

HTbool
CHTFXResTablePCSkill::HT_bGetName( HTdword dwID, CHTString& strName )
{
	HTResTablePCSkill_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName = (HTtchar*)((itTable->second)->strName);
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkill::HT_bGetDesc( HTdword dwID, CHTString& strDesc )
{
	HTResTablePCSkill_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strDesc = (HTtchar*)((itTable->second)->strDesc);
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkill::HT_bGetSkillID( HTdword dwID, HTdword& dwSkillID )
{
	HTResTablePCSkill_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwSkillID = (itTable->second)->dwSkillID;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkill::HT_bGetUI( HTdword dwID, HTdword& dwUI )
{
	HTResTablePCSkill_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwUI = (itTable->second)->dwUI;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

// -------------------------------------------------------------------------------------
// CHTFXResTablePCSkillAction
// -------------------------------------------------------------------------------------

CHTFXResTablePCSkillAction::CHTFXResTablePCSkillAction(){}
CHTFXResTablePCSkillAction::~CHTFXResTablePCSkillAction()
{
	HTResTablePCSkillAction_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTFXResTablePCSkillAction::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return HT_FAIL;

	m_strTable = strTable;

	HTResTablePCSkillAction* pRecord = HT_NULL;
	HTint iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ. 

	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTablePCSkillAction;

		strCell = _T("ID");							pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Type");						pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwType = (HTdword)iTemp;
		strCell = _T("Ready");						pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwReadyFX = (HTdword)iTemp;
		strCell = _T("Cast");						pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwCastFX = (HTdword)iTemp;
		strCell = _T("Activate");					pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwActivateFX = (HTdword)iTemp;
		strCell = _T("Follow");						pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwFollowFX = (HTdword)iTemp;
		strCell = _T("Impact");						pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwImpactFX = (HTdword)iTemp;
		strCell = _T("IsWeaponBack");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->bIsWeaponBack = (iTemp == 0) ? HT_FALSE : HT_TRUE;
		// «—º’
		strCell = _T("MAN_1H_Ready");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan1HReady = (HTdword)iTemp;
		strCell = _T("MAN_1H_ReadyFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan1HReadyFApron = (HTdword)iTemp;
		strCell = _T("MAN_1H_ReadyBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan1HReadyBApron = (HTdword)iTemp;
		strCell = _T("MAN_1H_Cast");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan1HCast = (HTdword)iTemp;
		strCell = _T("MAN_1H_CastFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan1HCastFApron = (HTdword)iTemp;
		strCell = _T("MAN_1H_CastBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan1HCastBApron = (HTdword)iTemp;
		strCell = _T("MAN_1H_Atv");					pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan1HAtv = (HTdword)iTemp;
		strCell = _T("MAN_1H_AtvFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan1HAtvFApron = (HTdword)iTemp;
		strCell = _T("MAN_1H_AtvBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan1HAtvBApron = (HTdword)iTemp;
		// µŒº’ ¿Â∞À
		strCell = _T("MAN_2H_SWORD_Ready");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HSwordReady = (HTdword)iTemp;
		strCell = _T("MAN_2H_SWORD_ReadyFApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HSwordReadyFApron = (HTdword)iTemp;
		strCell = _T("MAN_2H_SWORD_ReadyBApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HSwordReadyBApron = (HTdword)iTemp;
		strCell = _T("MAN_2H_SWORD_Cast");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HSwordCast = (HTdword)iTemp;
		strCell = _T("MAN_2H_SWORD_CastFApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HSwordCastFApron = (HTdword)iTemp;
		strCell = _T("MAN_2H_SWORD_CastBApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HSwordCastBApron = (HTdword)iTemp;
		strCell = _T("MAN_2H_SWORD_Atv");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HSwordAtv = (HTdword)iTemp;
		strCell = _T("MAN_2H_SWORD_AtvFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HSwordAtvFApron = (HTdword)iTemp;
		strCell = _T("MAN_2H_SWORD_AtvBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HSwordAtvBApron = (HTdword)iTemp;
		// µŒº’ µµ≥¢
		strCell = _T("MAN_2H_AXE_Ready");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HAxeReady = (HTdword)iTemp;
		strCell = _T("MAN_2H_AXE_ReadyFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HAxeReadyFApron = (HTdword)iTemp;
		strCell = _T("MAN_2H_AXE_ReadyBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HAxeReadyBApron = (HTdword)iTemp;
		strCell = _T("MAN_2H_AXE_Cast");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HAxeCast = (HTdword)iTemp;
		strCell = _T("MAN_2H_AXE_CastFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HAxeCastFApron = (HTdword)iTemp;
		strCell = _T("MAN_2H_AXE_CastBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HAxeCastBApron = (HTdword)iTemp;
		strCell = _T("MAN_2H_AXE_Atv");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HAxeAtv = (HTdword)iTemp;
		strCell = _T("MAN_2H_AXE_AtvFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HAxeAtvFApron = (HTdword)iTemp;
		strCell = _T("MAN_2H_AXE_AtvBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniMan2HAxeAtvBApron = (HTdword)iTemp;
		// »∞
		strCell = _T("MAN_BOW_Ready");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManBowReady = (HTdword)iTemp;
		strCell = _T("MAN_BOW_ReadyFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManBowReadyFApron = (HTdword)iTemp;
		strCell = _T("MAN_BOW_ReadyBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManBowReadyBApron = (HTdword)iTemp;
		strCell = _T("MAN_BOW_Cast");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManBowCast = (HTdword)iTemp;
		strCell = _T("MAN_BOW_CastFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManBowCastFApron = (HTdword)iTemp;
		strCell = _T("MAN_BOW_CastBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManBowCastBApron = (HTdword)iTemp;
		strCell = _T("MAN_BOW_Atv");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManBowAtv = (HTdword)iTemp;
		strCell = _T("MAN_BOW_AtvFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManBowAtvFApron = (HTdword)iTemp;
		strCell = _T("MAN_BOW_AtvBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManBowAtvBApron = (HTdword)iTemp;
		// ¡÷∏‘
		strCell = _T("MAN_FIST_Ready");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistReady = (HTdword)iTemp;
		strCell = _T("MAN_FIST_ReadyFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistReadyFApron = (HTdword)iTemp;
		strCell = _T("MAN_FIST_ReadyBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistReadyBApron = (HTdword)iTemp;
		strCell = _T("MAN_FIST_Cast");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistCast = (HTdword)iTemp;
		strCell = _T("MAN_FIST_CastFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistCastFApron = (HTdword)iTemp;
		strCell = _T("MAN_FIST_CastBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistCastBApron = (HTdword)iTemp;
		strCell = _T("MAN_FIST_Atv");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistAtv = (HTdword)iTemp;
		strCell = _T("MAN_FIST_AtvFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistAtvFApron = (HTdword)iTemp;
		strCell = _T("MAN_FIST_AtvBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistAtvBApron = (HTdword)iTemp;
		// «—º’
		strCell = _T("WOM_1H_Ready");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom1HReady = (HTdword)iTemp;
		strCell = _T("WOM_1H_ReadyFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom1HReadyFApron = (HTdword)iTemp;
		strCell = _T("WOM_1H_ReadyBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom1HReadyBApron = (HTdword)iTemp;
		strCell = _T("WOM_1H_Cast");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom1HCast = (HTdword)iTemp;
		strCell = _T("WOM_1H_CastFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom1HCastFApron = (HTdword)iTemp;
		strCell = _T("WOM_1H_CastBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom1HCastBApron = (HTdword)iTemp;
		strCell = _T("WOM_1H_Atv");					pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom1HAtv = (HTdword)iTemp;
		strCell = _T("WOM_1H_AtvFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom1HAtvFApron = (HTdword)iTemp;
		strCell = _T("WOM_1H_AtvBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom1HAtvBApron = (HTdword)iTemp;
		// µŒº’ ¿Â∞À
		strCell = _T("WOM_2H_SWORD_Ready");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HSwordReady = (HTdword)iTemp;
		strCell = _T("WOM_2H_SWORD_ReadyFApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HSwordReadyFApron = (HTdword)iTemp;
		strCell = _T("WOM_2H_SWORD_ReadyBApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HSwordReadyBApron = (HTdword)iTemp;
		strCell = _T("WOM_2H_SWORD_Cast");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HSwordCast = (HTdword)iTemp;
		strCell = _T("WOM_2H_SWORD_CastFApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HSwordCastFApron = (HTdword)iTemp;
		strCell = _T("WOM_2H_SWORD_CastBApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HSwordCastBApron = (HTdword)iTemp;
		strCell = _T("WOM_2H_SWORD_Atv");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HSwordAtv = (HTdword)iTemp;
		strCell = _T("WOM_2H_SWORD_AtvFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HSwordAtvFApron = (HTdword)iTemp;
		strCell = _T("WOM_2H_SWORD_AtvBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HSwordAtvBApron = (HTdword)iTemp;
		// µŒº’ µµ≥¢
		strCell = _T("WOM_2H_AXE_Ready");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HAxeReady = (HTdword)iTemp;
		strCell = _T("WOM_2H_AXE_ReadyFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HAxeReadyFApron = (HTdword)iTemp;
		strCell = _T("WOM_2H_AXE_ReadyBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HAxeReadyBApron = (HTdword)iTemp;
		strCell = _T("WOM_2H_AXE_Cast");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HAxeCast = (HTdword)iTemp;
		strCell = _T("WOM_2H_AXE_CastFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HAxeCastFApron = (HTdword)iTemp;
		strCell = _T("WOM_2H_AXE_CastBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HAxeCastBApron = (HTdword)iTemp;
		strCell = _T("WOM_2H_AXE_Atv");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HAxeAtv = (HTdword)iTemp;
		strCell = _T("WOM_2H_AXE_AtvFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HAxeAtvFApron = (HTdword)iTemp;
		strCell = _T("WOM_2H_AXE_AtvBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWom2HAxeAtvBApron = (HTdword)iTemp;
		// »∞
		strCell = _T("WOM_BOW_Ready");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomBowReady = (HTdword)iTemp;
		strCell = _T("WOM_BOW_ReadyFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomBowReadyFApron = (HTdword)iTemp;
		strCell = _T("WOM_BOW_ReadyBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomBowReadyBApron = (HTdword)iTemp;
		strCell = _T("WOM_BOW_Cast");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomBowCast = (HTdword)iTemp;
		strCell = _T("WOM_BOW_CastFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomBowCastFApron = (HTdword)iTemp;
		strCell = _T("WOM_BOW_CastBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomBowCastBApron = (HTdword)iTemp;
		strCell = _T("WOM_BOW_Atv");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomBowAtv = (HTdword)iTemp;
		strCell = _T("WOM_BOW_AtvFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomBowAtvFApron = (HTdword)iTemp;
		strCell = _T("WOM_BOW_AtvBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomBowAtvBApron = (HTdword)iTemp;
		// ¡÷∏‘
		strCell = _T("WOM_FIST_Ready");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistReady = (HTdword)iTemp;
		strCell = _T("WOM_FIST_ReadyFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistReadyFApron = (HTdword)iTemp;
		strCell = _T("WOM_FIST_ReadyBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistReadyBApron = (HTdword)iTemp;
		strCell = _T("WOM_FIST_Cast");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistCast = (HTdword)iTemp;
		strCell = _T("WOM_FIST_CastFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistCastFApron = (HTdword)iTemp;
		strCell = _T("WOM_FIST_CastBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistCastBApron = (HTdword)iTemp;
		strCell = _T("WOM_FIST_Atv");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistAtv = (HTdword)iTemp;
		strCell = _T("WOM_FIST_AtvFApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistAtvFApron = (HTdword)iTemp;
		strCell = _T("WOM_FIST_AtvBApron");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistAtvBApron = (HTdword)iTemp;

		strCell = _T("Man_Activate_Sound");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwSoundManActivate = (HTdword)iTemp;
		strCell = _T("Woman_Activate_Sound");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwSoundWomActivate = (HTdword)iTemp;

		m_mapTable.insert( HTResTablePCSkillAction_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTablePCSkillAction::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return HT_FAIL;

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTResTablePCSkillAction* pRecord = HT_NULL;

	HTint iID;
	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTablePCSkillAction;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTResTablePCSkillAction) );

		m_mapTable.insert( HTResTablePCSkillAction_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTablePCSkillAction::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return HT_FAIL;

	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_FXRESTABLE_PCSKILLACTION;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// ¡Ÿ ºˆ

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTResTablePCSkillAction) );
		itTable++;
	}

	return HT_OK;
}

HTdword
CHTFXResTablePCSkillAction::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return 0;

	HTResTablePCSkillAction_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow )
	{
		itTable++;
		++i;
	}

	if ( itTable != m_mapTable.end() ) return itTable->first;

	return 0;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillType( HTdword dwID, HTdword& dwType )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwType = (itTable->second)->dwType;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetReadyFX( HTdword dwID, HTdword& dwReadyFX )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwReadyFX = (itTable->second)->dwReadyFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetCastFX( HTdword dwID, HTdword& dwCastFX )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwCastFX = (itTable->second)->dwCastFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetActivateFX( HTdword dwID, HTdword& dwActivateFX )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwActivateFX = (itTable->second)->dwActivateFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetFollowFX( HTdword dwID, HTdword& dwFollowFX )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFollowFX = (itTable->second)->dwFollowFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetImpactFX( HTdword dwID, HTdword& dwImpactFX )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwImpactFX = (itTable->second)->dwImpactFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetIsWeaponBack( HTdword dwID, HTbool& bIsWeaponBack )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			bIsWeaponBack = (itTable->second)->bIsWeaponBack;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniReadyMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniMan1HReady;
			dwAniFApron = (itTable->second)->dwAniMan1HReadyFApron;
			dwAniBApron = (itTable->second)->dwAniMan1HReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniCastMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniMan1HCast;
			dwAniFApron = (itTable->second)->dwAniMan1HCastFApron;
			dwAniBApron = (itTable->second)->dwAniMan1HCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniActivateMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniMan1HAtv;
			dwAniFApron = (itTable->second)->dwAniMan1HAtvFApron;
			dwAniBApron = (itTable->second)->dwAniMan1HAtvBApron;
			return HT_TRUE;
		}
	}
	
	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniReadyMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniMan2HSwordReady;
			dwAniFApron = (itTable->second)->dwAniMan2HSwordReadyFApron;
			dwAniBApron = (itTable->second)->dwAniMan2HSwordReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniCastMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniMan2HSwordCast;
			dwAniFApron = (itTable->second)->dwAniMan2HSwordCastFApron;
			dwAniBApron = (itTable->second)->dwAniMan2HSwordCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniActivateMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniMan2HSwordAtv;
			dwAniFApron = (itTable->second)->dwAniMan2HSwordAtvFApron;
			dwAniBApron = (itTable->second)->dwAniMan2HSwordAtvBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniReadyMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniMan2HAxeReady;
			dwAniFApron = (itTable->second)->dwAniMan2HAxeReadyFApron;
			dwAniBApron = (itTable->second)->dwAniMan2HAxeReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniCastMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniMan2HAxeCast;
			dwAniFApron = (itTable->second)->dwAniMan2HAxeCastFApron;
			dwAniBApron = (itTable->second)->dwAniMan2HAxeCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniActivateMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniMan2HAxeAtv;
			dwAniFApron = (itTable->second)->dwAniMan2HAxeAtvFApron;
			dwAniBApron = (itTable->second)->dwAniMan2HAxeAtvBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniReadyManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniManBowReady;
			dwAniFApron = (itTable->second)->dwAniManBowReadyFApron;
			dwAniBApron = (itTable->second)->dwAniManBowReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniCastManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniManBowCast;
			dwAniFApron = (itTable->second)->dwAniManBowCastFApron;
			dwAniBApron = (itTable->second)->dwAniManBowCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniActivateManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniManBowAtv;
			dwAniFApron = (itTable->second)->dwAniManBowAtvFApron;
			dwAniBApron = (itTable->second)->dwAniManBowAtvBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}


HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniManFistReady;
			dwAniFApron = (itTable->second)->dwAniManFistReadyFApron;
			dwAniBApron = (itTable->second)->dwAniManFistReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniManFistCast;
			dwAniFApron = (itTable->second)->dwAniManFistCastFApron;
			dwAniBApron = (itTable->second)->dwAniManFistCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniManFistAtv;
			dwAniFApron = (itTable->second)->dwAniManFistAtvFApron;
			dwAniBApron = (itTable->second)->dwAniManFistAtvBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniReadyWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWom1HReady;
			dwAniFApron = (itTable->second)->dwAniWom1HReadyFApron;
			dwAniBApron = (itTable->second)->dwAniWom1HReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniCastWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWom1HCast;
			dwAniFApron = (itTable->second)->dwAniWom1HCastFApron;
			dwAniBApron = (itTable->second)->dwAniWom1HCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniActivateWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWom1HAtv;
			dwAniFApron = (itTable->second)->dwAniWom1HAtvFApron;
			dwAniBApron = (itTable->second)->dwAniWom1HAtvBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniReadyWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWom2HSwordReady;
			dwAniFApron = (itTable->second)->dwAniWom2HSwordReadyFApron;
			dwAniBApron = (itTable->second)->dwAniWom2HSwordReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniCastWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWom2HSwordCast;
			dwAniFApron = (itTable->second)->dwAniWom2HSwordCastFApron;
			dwAniBApron = (itTable->second)->dwAniWom2HSwordCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniActivateWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWom2HSwordAtv;
			dwAniFApron = (itTable->second)->dwAniWom2HSwordAtvFApron;
			dwAniBApron = (itTable->second)->dwAniWom2HSwordAtvBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniReadyWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWom2HAxeReady;
			dwAniFApron = (itTable->second)->dwAniWom2HAxeReadyFApron;
			dwAniBApron = (itTable->second)->dwAniWom2HAxeReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniCastWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWom2HAxeCast;
			dwAniFApron = (itTable->second)->dwAniWom2HAxeCastFApron;
			dwAniBApron = (itTable->second)->dwAniWom2HAxeCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniActivateWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWom2HAxeAtv;
			dwAniFApron = (itTable->second)->dwAniWom2HAxeAtvFApron;
			dwAniBApron = (itTable->second)->dwAniWom2HAxeAtvBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniReadyWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWomBowReady;
			dwAniFApron = (itTable->second)->dwAniWomBowReadyFApron;
			dwAniBApron = (itTable->second)->dwAniWomBowReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniCastWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWomBowCast;
			dwAniFApron = (itTable->second)->dwAniWomBowCastFApron;
			dwAniBApron = (itTable->second)->dwAniWomBowCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniActivateWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWomBowAtv;
			dwAniFApron = (itTable->second)->dwAniWomBowAtvFApron;
			dwAniBApron = (itTable->second)->dwAniWomBowAtvBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWomFistReady;
			dwAniFApron = (itTable->second)->dwAniWomFistReadyFApron;
			dwAniBApron = (itTable->second)->dwAniWomFistReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWomFistCast;
			dwAniFApron = (itTable->second)->dwAniWomFistCastFApron;
			dwAniBApron = (itTable->second)->dwAniWomFistCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwAniWomFistAtv;
			dwAniFApron = (itTable->second)->dwAniWomFistAtvFApron;
			dwAniBApron = (itTable->second)->dwAniWomFistAtvBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionSoundActivateMan( HTdword dwID, HTdword& dwSound )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwSound = (itTable->second)->dwSoundManActivate;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillAction::HT_bGetSkillActionSoundActivateWom( HTdword dwID, HTdword& dwSound )
{
	HTResTablePCSkillAction_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwSound = (itTable->second)->dwSoundWomActivate;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

// -------------------------------------------------------------------------------------
// CHTFXResTablePCSkillActive
// -------------------------------------------------------------------------------------
CHTFXResTablePCSkillActive::CHTFXResTablePCSkillActive(){}
CHTFXResTablePCSkillActive::~CHTFXResTablePCSkillActive()
{
	HTResTablePCSkillActive_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTFXResTablePCSkillActive::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return HT_FAIL;

	m_strTable = strTable;

	HTResTablePCSkillActive* pRecord = HT_NULL;
	HTint iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ. 

	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTablePCSkillActive;

		strCell = _T("ID");							pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Type");						pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwType = (HTdword)iTemp;
		strCell = _T("Ready");						pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwReadyFX = (HTdword)iTemp;
		strCell = _T("Cast");						pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwCastFX = (HTdword)iTemp;
		strCell = _T("Activate");					pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwActivateFX = (HTdword)iTemp;
		strCell = _T("State");						pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwStateFX = (HTdword)iTemp;
		strCell = _T("State");						pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwStateFX = (HTdword)iTemp;

		strCell = _T("MAN_FIST_Ready");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistReady = (HTdword)iTemp;
		strCell = _T("MAN_FIST_ReadyFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistReadyFApron = (HTdword)iTemp;
		strCell = _T("MAN_FIST_ReadyBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistReadyBApron = (HTdword)iTemp;
		strCell = _T("MAN_FIST_Cast");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistCast = (HTdword)iTemp;
		strCell = _T("MAN_FIST_CastFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistCastFApron = (HTdword)iTemp;
		strCell = _T("MAN_FIST_CastBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistCastBApron = (HTdword)iTemp;
		strCell = _T("MAN_FIST_Activate");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistActivate = (HTdword)iTemp;
		strCell = _T("MAN_FIST_ActivateFApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistActivateFApron = (HTdword)iTemp;
		strCell = _T("MAN_FIST_ActivateBApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniManFistActivateBApron = (HTdword)iTemp;
		strCell = _T("WOM_FIST_Ready");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistReady = (HTdword)iTemp;
		strCell = _T("WOM_FIST_ReadyFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistReadyFApron = (HTdword)iTemp;
		strCell = _T("WOM_FIST_ReadyBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistReadyBApron = (HTdword)iTemp;
		strCell = _T("WOM_FIST_Cast");				pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistCast = (HTdword)iTemp;
		strCell = _T("WOM_FIST_CastFApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistCastFApron = (HTdword)iTemp;
		strCell = _T("WOM_FIST_CastBApron");		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistCastBApron = (HTdword)iTemp;
		strCell = _T("WOM_FIST_Activate");			pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistActivate = (HTdword)iTemp;
		strCell = _T("WOM_FIST_ActivateFApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistActivateFApron = (HTdword)iTemp;
		strCell = _T("WOM_FIST_ActivateBApron");	pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAniWomFistActivateBApron = (HTdword)iTemp;

		m_mapTable.insert( HTResTablePCSkillActive_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTablePCSkillActive::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return HT_FAIL;

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTResTablePCSkillActive* pRecord = HT_NULL;

	HTint iID;
	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTablePCSkillActive;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTResTablePCSkillActive) );

		m_mapTable.insert( HTResTablePCSkillActive_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTablePCSkillActive::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return HT_FAIL;

	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_FXRESTABLE_PCSKILLACTIVE;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// ¡Ÿ ºˆ

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTResTablePCSkillActive) );
		itTable++;
	}

	return HT_OK;
}

HTdword
CHTFXResTablePCSkillActive::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return 0;

	HTResTablePCSkillActive_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow )
	{
		itTable++;
		++i;
	}

	if ( itTable != m_mapTable.end() ) return itTable->first;

	return 0;
}

HTbool
CHTFXResTablePCSkillActive::HT_bGetSkillType( HTdword dwID, HTdword& dwType )
{
	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwType = (itTable->second)->dwType;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillActive::HT_bGetReadyFX( HTdword dwID, HTdword& dwReadyFX )
{
	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwReadyFX = (itTable->second)->dwReadyFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillActive::HT_bGetCastFX( HTdword dwID, HTdword& dwCastFX )
{
	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwCastFX = (itTable->second)->dwCastFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillActive::HT_bGetActivateFX( HTdword dwID, HTdword& dwActivateFX )
{
	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwActivateFX = (itTable->second)->dwActivateFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillActive::HT_bGetStateFX( HTdword dwID, HTdword& dwStateFX )
{
	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwStateFX = (itTable->second)->dwStateFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillActive::HT_bGetSkillActiveAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni		= (itTable->second)->dwAniManFistReady;
			dwAniFApron	= (itTable->second)->dwAniManFistReadyFApron;
			dwAniBApron	= (itTable->second)->dwAniManFistReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillActive::HT_bGetSkillActiveAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni		= (itTable->second)->dwAniManFistCast;
			dwAniFApron	= (itTable->second)->dwAniManFistCastFApron;
			dwAniBApron	= (itTable->second)->dwAniManFistCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillActive::HT_bGetSkillActiveAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni		= (itTable->second)->dwAniManFistActivate;
			dwAniFApron	= (itTable->second)->dwAniManFistActivateFApron;
			dwAniBApron	= (itTable->second)->dwAniManFistActivateBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillActive::HT_bGetSkillActiveAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni		= (itTable->second)->dwAniWomFistReady;
			dwAniFApron	= (itTable->second)->dwAniWomFistReadyFApron;
			dwAniBApron	= (itTable->second)->dwAniWomFistReadyBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillActive::HT_bGetSkillActiveAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni		= (itTable->second)->dwAniWomFistCast;
			dwAniFApron	= (itTable->second)->dwAniWomFistCastFApron;
			dwAniBApron	= (itTable->second)->dwAniWomFistCastBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTablePCSkillActive::HT_bGetSkillActiveAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	HTResTablePCSkillActive_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni		= (itTable->second)->dwAniWomFistActivate;
			dwAniFApron	= (itTable->second)->dwAniWomFistActivateFApron;
			dwAniBApron	= (itTable->second)->dwAniWomFistActivateBApron;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

// -------------------------------------------------------------------------------------
// CHTFXResTablePCFX
// -------------------------------------------------------------------------------------

CHTFXResTablePCFX::CHTFXResTablePCFX() {}
CHTFXResTablePCFX::~CHTFXResTablePCFX()
{
	HTResTablePCFX_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTFXResTablePCFX::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return HT_FAIL;

	m_strTable = strTable;

	HTResTablePCFX* pRecord = HT_NULL;
	HTint iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ. 

	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTablePCFX;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Category");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwCategory = (HTdword)iTemp;
		strCell = _T("FXName");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFXName );
		strCell = _T("Where");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwWhereAttach = (HTdword)iTemp;
		strCell = _T("Priority");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwPriority = (HTdword)iTemp;

		m_mapTable.insert( HTResTablePCFX_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTablePCFX::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return HT_FAIL;

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTResTablePCFX* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTablePCFX;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTResTablePCFX) );

		m_mapTable.insert( HTResTablePCFX_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTablePCFX::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return HT_FAIL;

	HTResTablePCFX_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_FXRESTABLE_PCFX;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// ¡Ÿ ºˆ

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTResTablePCFX) );
		itTable++;
	}

	return HT_OK;
}

HTdword
CHTFXResTablePCFX::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return 0;

	HTResTablePCFX_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow )
	{
		itTable++;
		++i;
	}

	if ( itTable != m_mapTable.end() ) return itTable->first;

	return 0;
}

HTbool
CHTFXResTablePCFX::HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwCategory, HTdword& dwWhereAttach, HTdword& dwPriority )
{
	HTResTablePCFX_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFXName		= (itTable->second)->strFXName;
			dwCategory		= (itTable->second)->dwCategory;
			dwWhereAttach	= (itTable->second)->dwWhereAttach;
			dwPriority		= (itTable->second)->dwPriority;
			
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

// -------------------------------------------------------------------------------------
// CHTFXResTableString
// -------------------------------------------------------------------------------------

CHTFXResTableString::CHTFXResTableString() {}
CHTFXResTableString::~CHTFXResTableString()
{
	HTResTableString_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTFXResTableString::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return HT_FAIL;

	m_strTable = strTable;

	HTResTableString* pRecord = HT_NULL;
	HTint iID;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ. 

	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTableString;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("File");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strName );

		m_mapTable.insert( HTResTableString_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTableString::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return HT_FAIL;

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTResTableString* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTableString;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTResTableString) );

		m_mapTable.insert( HTResTableString_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTableString::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return HT_FAIL;

	HTResTableString_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_FXRESTABLE_STRING;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// ¡Ÿ ºˆ

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTResTableString) );
		itTable++;
	}

	return HT_OK;
}

HTdword
CHTFXResTableString::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return 0;

	HTResTableString_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow )
	{
		itTable++;
		++i;
	}

	if ( itTable != m_mapTable.end() ) return itTable->first;

	return 0;
}

HTbool
CHTFXResTableString::HT_bGetName( HTdword dwID, CHTString& strName )
{
	HTResTableString_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strName	= (itTable->second)->strName;			
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

// -------------------------------------------------------------------------------------
// CHTFXResTableMONSkill
// -------------------------------------------------------------------------------------

CHTFXResTableMONSkill::CHTFXResTableMONSkill() {}
CHTFXResTableMONSkill::~CHTFXResTableMONSkill()
{
	HTResTableMONSkill_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTFXResTableMONSkill::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return HT_FAIL;

	m_strTable = strTable;

	HTResTableMONSkill* pRecord = HT_NULL;
	HTint iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ. 

	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTableMONSkill;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("Type");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwType = (HTdword)iTemp;
		strCell = _T("Cast");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwCastFX = (HTdword)iTemp;
		strCell = _T("Activate");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwActivateFX = (HTdword)iTemp;
		strCell = _T("Follow");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwFollowFX = (HTdword)iTemp;
		strCell = _T("Impact");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwImpactFX = (HTdword)iTemp;
		strCell = _T("State");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwStateFX = (HTdword)iTemp;
		strCell = _T("Animation");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwSkillAni = (HTdword)iTemp;

		m_mapTable.insert( HTResTableMONSkill_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTableMONSkill::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return HT_FAIL;

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTResTableMONSkill* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTableMONSkill;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTResTableMONSkill) );

		m_mapTable.insert( HTResTableMONSkill_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTableMONSkill::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return HT_FAIL;

	HTResTableMONSkill_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_FXRESTABLE_MONSKILL;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// ¡Ÿ ºˆ

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTResTableMONSkill) );
		itTable++;
	}

	return HT_OK;
}

HTdword
CHTFXResTableMONSkill::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return 0;

	HTResTableMONSkill_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow )
	{
		itTable++;
		++i;
	}

	if ( itTable != m_mapTable.end() ) return itTable->first;

	return 0;
}

HTbool
CHTFXResTableMONSkill::HT_bGetSkillType( HTdword dwID, HTdword& dwType )
{
	HTResTableMONSkill_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwType = (itTable->second)->dwType;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTableMONSkill::HT_bGetCastFX( HTdword dwID, HTdword& dwFX )
{
	HTResTableMONSkill_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFX = (itTable->second)->dwCastFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTableMONSkill::HT_bGetActivateFX( HTdword dwID, HTdword& dwFX )
{
	HTResTableMONSkill_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFX = (itTable->second)->dwActivateFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTableMONSkill::HT_bGetFollowFX( HTdword dwID, HTdword& dwFX )
{
	HTResTableMONSkill_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFX = (itTable->second)->dwFollowFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTableMONSkill::HT_bGetImpactFX( HTdword dwID, HTdword& dwFX )
{
	HTResTableMONSkill_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFX = (itTable->second)->dwImpactFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTableMONSkill::HT_bGetStateFX( HTdword dwID, HTdword& dwFX )
{
	HTResTableMONSkill_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFX = (itTable->second)->dwStateFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTableMONSkill::HT_bGetSkillAni( HTdword dwID, HTdword& dwAni )
{
	HTResTableMONSkill_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwAni = (itTable->second)->dwSkillAni;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

// -------------------------------------------------------------------------------------
// CHTFXResTableMONEffect
// -------------------------------------------------------------------------------------

CHTFXResTableMONEffect::CHTFXResTableMONEffect() {}
CHTFXResTableMONEffect::~CHTFXResTableMONEffect()
{
	HTResTableMONEffect_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTFXResTableMONEffect::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return HT_FAIL;

	m_strTable = strTable;

	HTResTableMONEffect* pRecord = HT_NULL;
	HTint iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ. 

	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTableMONEffect;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("BornFX");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwBornFX = (HTdword)iTemp;
		strCell = _T("DieFX");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwDieFX = (HTdword)iTemp;
		strCell = _T("AlwaysFX");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwAlwaysFX = (HTdword)iTemp;

		m_mapTable.insert( HTResTableMONEffect_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTableMONEffect::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return HT_FAIL;

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTResTableMONEffect* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTableMONEffect;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTResTableMONEffect) );

		m_mapTable.insert( HTResTableMONEffect_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTableMONEffect::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return HT_FAIL;

	HTResTableMONEffect_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_FXRESTABLE_MONEFFECT;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// ¡Ÿ ºˆ

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTResTableMONEffect) );
		itTable++;
	}

	return HT_OK;
}

HTdword
CHTFXResTableMONEffect::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return 0;

	HTResTableMONEffect_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow )
	{
		itTable++;
		++i;
	}

	if ( itTable != m_mapTable.end() ) return itTable->first;

	return 0;
}

HTbool
CHTFXResTableMONEffect::HT_bGetBornFX( HTdword dwID, HTdword& dwFX )
{
	HTResTableMONEffect_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFX = (itTable->second)->dwBornFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTableMONEffect::HT_bGetDieActivateFX( HTdword dwID, HTdword& dwFX )
{
	HTResTableMONEffect_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFX = (itTable->second)->dwDieFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

HTbool
CHTFXResTableMONEffect::HT_bGetAlwaysFX( HTdword dwID, HTdword& dwFX )
{
	HTResTableMONEffect_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			dwFX = (itTable->second)->dwAlwaysFX;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

// -------------------------------------------------------------------------------------
// CHTFXResTableMONFX
// -------------------------------------------------------------------------------------

CHTFXResTableMONFX::CHTFXResTableMONFX() {}
CHTFXResTableMONFX::~CHTFXResTableMONFX()
{
	HTResTableMONFX_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		HT_DELETE( it->second );
		it = m_mapTable.erase( it );
	}
}

HTRESULT
CHTFXResTableMONFX::HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return HT_FAIL;

	m_strTable = strTable;

	HTResTableMONFX* pRecord = HT_NULL;
	HTint iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // ¡¶¿œ ¿≠¡Ÿ¿∫ ª´¥Ÿ. 

	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTableMONFX;

		strCell = _T("ID");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iID );
		strCell = _T("FXName");
		pXML->HT_hrGetTableValue( strTable, strCell, i, (HTtchar*)pRecord->strFXName );
		strCell = _T("Where");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwWhereAttach = (HTdword)iTemp;
		strCell = _T("Priority");
		pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp );	pRecord->dwPriority = (HTdword)iTemp;

		m_mapTable.insert( HTResTableMONFX_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTableMONFX::HT_hrLoad( CHTFile* pFile, CHTString& strTable )
{
	if ( !pFile ) return HT_FAIL;

	m_strTable = strTable;

	HTint iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTResTableMONFX* pRecord = HT_NULL;
	HTint iID;
	for ( HTuint i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTResTableMONFX;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTResTableMONFX) );

		m_mapTable.insert( HTResTableMONFX_Value( (HTdword)iID, pRecord ) );
	}

	return HT_OK;
}

HTRESULT
CHTFXResTableMONFX::HT_hrSave( CHTFile* pFile )
{
	if ( !pFile ) return HT_FAIL;

	HTResTableMONFX_It itTable;
	itTable = m_mapTable.begin();

	HTbyte bType = HT_FXRESTABLE_MONFX;
	pFile->HT_bWrite( bType );	// class type

	HTint iRecordCount;
	iRecordCount = (HTint)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );	// ¡Ÿ ºˆ

	HTint iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTResTableMONFX) );
		itTable++;
	}

	return HT_OK;
}

HTdword
CHTFXResTableMONFX::HT_dwGetIDByIndex( HTuint idxRow )
{
	if ( idxRow > m_mapTable.size() ) return 0;

	HTResTableMONFX_It itTable = m_mapTable.begin();

	HTuint i = 0;
	while ( i < idxRow )
	{
		itTable++;
		++i;
	}

	if ( itTable != m_mapTable.end() ) return itTable->first;

	return 0;
}

HTbool
CHTFXResTableMONFX::HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwWhereAttach, HTdword& dwPriority )
{
	HTResTableMONFX_It itTable;
	itTable = m_mapTable.find( dwID );

	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strFXName		= (itTable->second)->strFXName;
			dwWhereAttach	= (itTable->second)->dwWhereAttach;
			dwPriority		= (itTable->second)->dwPriority;
			return HT_TRUE;
		}
	}

	return HT_FALSE;
}

// -------------------------------------------------------------------------------------
// CHTFXPCResMgr
// -------------------------------------------------------------------------------------

CHTFXPCResMgr::CHTFXPCResMgr() {}
CHTFXPCResMgr::~CHTFXPCResMgr()
{
	this->HT_hrUnload();
}

HTRESULT
CHTFXPCResMgr::HT_hrLoad( CHTString& strFile )
{
	if ( strFile.HT_bIsExtension( _T("xml") ) )			return this->HT_hrLoadXML( strFile );
	else if ( strFile.HT_bIsExtension( _T("txl") ) )	return this->HT_hrLoadTXL( strFile );
	else												return HT_FAIL;
}

HTRESULT
CHTFXPCResMgr::HT_hrUnload()
{
	HTFXResTable_It it = m_mapTables.begin();
	while ( it != m_mapTables.end() )
	{
		HT_DELETEARRAY( (HTtchar*)it->first );
		HT_DELETE( it->second );
		it = m_mapTables.erase( it );
	}

	return HT_OK;
}

HTRESULT
CHTFXPCResMgr::HT_hrLoadXML( CHTString& strFile )
{
	CHTXMLParser oXML;
	if ( HT_FAILED( oXML.HT_hrOpen( strFile ) ) ) return HT_FAIL;

	CHTFXBaseResTable* pTable = HT_NULL;
	CHTString strTable;

	strTable = HT_FXRES_TABLENAME_PCSKILL;
	pTable = new CHTFXResTablePCSkill;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[20];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), 20 );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_PCSKILLACTION;
	pTable = new CHTFXResTablePCSkillAction;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[20];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), 20 );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_PCSKILLACTIVE;
	pTable = new CHTFXResTablePCSkillActive;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[20];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), 20 );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_FXSKILL;
	pTable = new CHTFXResTablePCFX;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[20];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), 20 );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_FXETC;
	pTable = new CHTFXResTablePCFX;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[20];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), 20 );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_MODEL;
	pTable = new CHTFXResTableString;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[20];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), 20 );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_TEXTURE;
	pTable = new CHTFXResTableString;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[20];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), 20 );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_ANIMATION;
	pTable = new CHTFXResTableString;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[20];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), 20 );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_SOUND;
	pTable = new CHTFXResTableString;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[20];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), 20 );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	oXML.HT_hrClose();

	return HT_OK;
}

HTRESULT
CHTFXPCResMgr::HT_hrLoadTXL( CHTString& strFile )
{
	CHTFile oLoadFile;
	if ( !oLoadFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) ) return HT_FAIL;

	// Version Check
	HTbyte bVersion;
	oLoadFile.HT_bRead( &bVersion );
	if ( bVersion != 1 ) return ( HT_FAIL );

	HTint iSheetCount;
	oLoadFile.HT_bRead( &iSheetCount );

	CHTFXBaseResTable* pTable = HT_NULL;
	CHTString strTable;
	HTbyte bType;

	for ( HTint i = 0; i < iSheetCount; i++ )
	{
		oLoadFile.HT_bRead( (HTtchar*)strTable, HT_MAX_STR );
		oLoadFile.HT_bRead( &bType );
		
		switch( bType )
		{
		case HT_FXRESTABLE_PCSKILL :		pTable = new CHTFXResTablePCSkill;			break;
		case HT_FXRESTABLE_PCSKILLACTION :	pTable = new CHTFXResTablePCSkillAction;	break;
		case HT_FXRESTABLE_PCSKILLACTIVE :	pTable = new CHTFXResTablePCSkillActive;	break;
		case HT_FXRESTABLE_PCFX :			pTable = new CHTFXResTablePCFX;				break;
		case HT_FXRESTABLE_STRING :			pTable = new CHTFXResTableString;			break;
		default :
			oLoadFile.HT_vClose(); return HT_FAIL;
		}

		if ( HT_SUCCEED( pTable->HT_hrLoad( &oLoadFile, strTable ) ) )
		{
			HTtchar* szTableName = new HTtchar[20];
			CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), 20 );
			m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
		}
		else HT_DELETE( pTable );
	}

	oLoadFile.HT_vClose();

	return HT_OK;
}

HTRESULT
CHTFXPCResMgr::HT_hrSave( CHTString& strFile )
{
	CHTFile oSaveFile;
	if ( !oSaveFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_WRITEONLY ) ) return HT_FAIL;

	HTbyte bVersion;
	bVersion = 1;
	oSaveFile.HT_bWrite( bVersion );

	HTint iSheetCount;
	iSheetCount = (HTint)m_mapTables.size();
	oSaveFile.HT_bWrite( iSheetCount );

	HTFXResTable_It it = m_mapTables.begin();
	while ( it != m_mapTables.end() )
	{
		oSaveFile.HT_bWrite( (HTtchar*)it->first, HT_MAX_STR );	// sheet name
		if ( HT_FAILED( (it->second)->HT_hrSave( &oSaveFile ) ) )
		{
			CHTString strDebug;
			strDebug.HT_szFormat( "Can't Save SheetName (%s), Item Count (%d)", (HTtchar*)it->first, (it->second)->HT_nGetItemCount() );
			MessageBox( HT_NULL, (HTtchar*)strDebug, _T("CHTFXPCResMgr::HT_hrSave"), MB_OK );
			return HT_FAIL;
		}
		it++;
	}

	oSaveFile.HT_vClose();

	return HT_OK;
}

HTtchar*
CHTFXPCResMgr::HT_pGetTableName( HTdword dwID )
{
	if ( HT_IS_PCSKILL( dwID ) )				return HT_FXRES_TABLENAME_PCSKILL;
	else if ( HT_IS_PCSKILLACTION( dwID ) )		return HT_FXRES_TABLENAME_PCSKILLACTION;
	else if ( HT_IS_PCSKILLACTIVE( dwID ) )		return HT_FXRES_TABLENAME_PCSKILLACTIVE;
	else if ( HT_IS_FXNAME_PCSKILL( dwID ) )	return HT_FXRES_TABLENAME_FXSKILL;
	else if ( HT_IS_FXNAME_PCEFFECT( dwID ) )	return HT_FXRES_TABLENAME_FXETC;
	else if ( HT_IS_FXMODEL_PC( dwID ) )		return HT_FXRES_TABLENAME_MODEL;
	else if ( HT_IS_FXTEXTURE_PC( dwID ) )		return HT_FXRES_TABLENAME_TEXTURE;
	else if ( HT_IS_FXANIMATION_PC( dwID ) )	return HT_FXRES_TABLENAME_ANIMATION;
	else if ( HT_IS_FXSOUND_PC( dwID ) )		return HT_FXRES_TABLENAME_SOUND;
	else										return HT_NULL;
}

CHTFXBaseResTable*
CHTFXPCResMgr::HT_pGetTable( HTdword dwID )
{
	HTtchar* pTable = HT_pGetTableName( dwID );
	if ( !pTable ) return HT_NULL;

	HTFXResTable_It it = m_mapTables.find( pTable );
	if ( it != m_mapTables.end() ) return ( it->second );

	return HT_NULL;
}

HTdword
CHTFXPCResMgr::HT_dwGetIDByIndex( CHTString& strTable, HTuint idxRow )
{
	HTFXResTable_It it = m_mapTables.find( (HTtchar*)strTable );
	if ( it != m_mapTables.end() )
	{
		if ( it->second ) return (it->second)->HT_dwGetIDByIndex( idxRow );
	}

	return 0;
}

HTuint
CHTFXPCResMgr::HT_nGetItemCount( CHTString& strTable )
{
	HTFXResTable_It it = m_mapTables.find( (HTtchar*)strTable );
	if ( it != m_mapTables.end() )
	{
		if ( it->second ) return (it->second)->HT_nGetItemCount();
	}

	return 0;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillType( HTdword dwID, HTdword& dwType )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillType( dwID, dwType );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillName( HTdword dwID, CHTString& strSkillName )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetName( dwID, strSkillName );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillDesc( HTdword dwID, CHTString& strSkillDesc )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetDesc( dwID, strSkillDesc );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillID( HTdword dwID, HTdword& dwSkillID )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillID( dwID, dwSkillID );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetReadyFX( HTdword dwID, HTdword& dwReadyFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetReadyFX( dwID, dwReadyFX );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetCastFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetCastFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetActivateFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetActivateFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetFollowFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetFollowFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetImpactFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetImpactFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetStateFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetStateFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetUI( HTdword dwID, HTdword& dwUI )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetUI( dwID, dwUI );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetIsWeaponBack( HTdword dwID, HTbool& bIsWeaponBack )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetIsWeaponBack( dwID, bIsWeaponBack );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniReadyMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniReadyMan1H( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniCastMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniCastMan1H( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniActivateMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniActivateMan1H( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniReadyMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniReadyMan2HSword( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniCastMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniCastMan2HSword( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniActivateMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniActivateMan2HSword( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniReadyMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniReadyMan2HAxe( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniCastMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniCastMan2HAxe( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniActivateMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniActivateMan2HAxe( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniReadyManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniReadyManBow( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniCastManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniCastManBow( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniActivateManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniActivateManBow( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniReadyManFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniCastManFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniActivateManFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniReadyWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniReadyWom1H( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniCastWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniCastWom1H( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniActivateWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniActivateWom1H( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniReadyWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniReadyWom2HSword( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniCastWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniCastWom2HSword( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniActivateWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniActivateWom2HSword( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniReadyWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniReadyWom2HAxe( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniCastWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniCastWom2HAxe( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniActivateWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniActivateWom2HAxe( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniReadyWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniReadyWomBow( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniCastWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniCastWomBow( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniActivateWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniActivateWomBow( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniReadyWomFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniCastWomFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionAniActivateWomFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionSoundActivateMan( HTdword dwID, HTdword& dwSound )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionSoundActivateMan( dwID, dwSound );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActionSoundActivateWom( HTdword dwID, HTdword& dwSound )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActionSoundActivateWom( dwID, dwSound );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActiveAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActiveAniReadyManFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActiveAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActiveAniCastManFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActiveAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActiveAniActivateManFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActiveAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActiveAniReadyWomFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActiveAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActiveAniCastWomFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSkillActiveAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillActiveAniActivateWomFist( dwID, dwAni, dwAniFApron, dwAniBApron );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwCategory, HTdword& dwWhereAttach, HTdword& dwPriority )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetFX( dwID, strFXName, dwCategory, dwWhereAttach, dwPriority );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetModelName( HTdword dwID, CHTString& strName )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetName( dwID, strName );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetTextureName( HTdword dwID, CHTString& strName )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetName( dwID, strName );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetAnimationName( HTdword dwID, CHTString& strName )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetName( dwID, strName );
	else			return HT_FALSE;
}

HTbool
CHTFXPCResMgr::HT_bGetSoundName( HTdword dwID, CHTString& strName )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetName( dwID, strName );
	else			return HT_FALSE;
}

// -------------------------------------------------------------------------------------
// CHTFXMAPResMgr
// -------------------------------------------------------------------------------------

CHTFXMAPResMgr::CHTFXMAPResMgr() {}
CHTFXMAPResMgr::~CHTFXMAPResMgr()
{
	this->HT_hrUnload();
}

HTRESULT
CHTFXMAPResMgr::HT_hrLoad( CHTString& strFile )
{
	if ( strFile.HT_bIsExtension( _T("xml") ) )			return this->HT_hrLoadXML( strFile );
	else if ( strFile.HT_bIsExtension( _T("txl") ) )	return this->HT_hrLoadTXL( strFile );
	else												return HT_FAIL;
}

HTRESULT
CHTFXMAPResMgr::HT_hrUnload()
{
	HTFXResTable_It it = m_mapTables.begin();
	while ( it != m_mapTables.end() )
	{
		HT_DELETEARRAY( (HTtchar*)it->first );
		HT_DELETE( it->second );
		it = m_mapTables.erase( it );
	}

	return HT_OK;
}

HTRESULT
CHTFXMAPResMgr::HT_hrLoadXML( CHTString& strFile )
{
	CHTXMLParser oXML;
	if ( HT_FAILED( oXML.HT_hrOpen( strFile ) ) ) return HT_FAIL;

	CHTFXBaseResTable* pTable = HT_NULL;
	CHTString strTable;

	strTable = HT_FXRES_TABLENAME_MONSTERSKILL;
	pTable = new CHTFXResTableMONSkill;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_MONSTEREFFECT;
	pTable = new CHTFXResTableMONEffect;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_FXMONSTERSKILL;
	pTable = new CHTFXResTableMONFX;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );
	
	strTable = HT_FXRES_TABLENAME_FXMONSTERETC;
	pTable = new CHTFXResTableMONFX;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_FXFIELD;
	pTable = new CHTFXResTableMONFX;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_MODEL;
	pTable = new CHTFXResTableString;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_TEXTURE;
	pTable = new CHTFXResTableString;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_ANIMATION;
	pTable = new CHTFXResTableString;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	strTable = HT_FXRES_TABLENAME_SOUND;
	pTable = new CHTFXResTableString;
	if ( HT_SUCCEED( pTable->HT_hrLoad( &oXML, strTable ) ) )
	{
		HTtchar* szTableName = new HTtchar[HT_MAX_STR];
		CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
		m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
	}
	else HT_DELETE( pTable );

	oXML.HT_hrClose();
 
	return HT_OK;
}

HTRESULT
CHTFXMAPResMgr::HT_hrLoadTXL( CHTString& strFile )
{
	CHTFile oLoadFile;
	if ( !oLoadFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) ) return HT_FAIL;

	// Version Check
	HTbyte bVersion;
	oLoadFile.HT_bRead( &bVersion );
	if ( bVersion != 1 ) return ( HT_FAIL );

	HTint iSheetCount;
	oLoadFile.HT_bRead( &iSheetCount );

	CHTFXBaseResTable* pTable = HT_NULL;
	CHTString strTable;
	HTbyte bType;

	for ( HTint i = 0; i < iSheetCount; i++ )
	{
		oLoadFile.HT_bRead( (HTtchar*)strTable, HT_MAX_STR );
		oLoadFile.HT_bRead( &bType );

		switch( bType )
		{
		case HT_FXRESTABLE_MONSKILL :	pTable = new CHTFXResTableMONSkill;		break;
		case HT_FXRESTABLE_MONEFFECT :	pTable = new CHTFXResTableMONEffect;	break;
		case HT_FXRESTABLE_MONFX :		pTable = new CHTFXResTableMONFX;		break;
		case HT_FXRESTABLE_STRING :		pTable = new CHTFXResTableString;		break;
		default :
			oLoadFile.HT_vClose(); return HT_FAIL;
		}

		if ( HT_SUCCEED( pTable->HT_hrLoad( &oLoadFile, strTable ) ) )
		{
			HTtchar* szTableName = new HTtchar[HT_MAX_STR];
			CHTString::HT_hrStringCopy( szTableName, strTable.HT_szGetString(), HT_MAX_STR );
			m_mapTables.insert( HTFXResTable_Value( szTableName, pTable ) );
		}
		else HT_DELETE( pTable );
	}

	oLoadFile.HT_vClose();

	return HT_OK;
}

HTRESULT
CHTFXMAPResMgr::HT_hrSave( CHTString& strFile )
{
	CHTFile oSaveFile;
	if ( !oSaveFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_WRITEONLY ) ) return HT_FAIL;

	HTbyte bVersion;
	bVersion = 1;
	oSaveFile.HT_bWrite( bVersion );

	HTint iSheetCount;
	iSheetCount = (HTint)m_mapTables.size();
	oSaveFile.HT_bWrite( iSheetCount );

	HTFXResTable_It it = m_mapTables.begin();
	while ( it != m_mapTables.end() )
	{
		oSaveFile.HT_bWrite( (HTtchar*)it->first, HT_MAX_STR );	// sheet name
		if ( HT_FAILED( (it->second)->HT_hrSave( &oSaveFile ) ) )
		{
			CHTString strDebug;
			strDebug.HT_szFormat( "Can't Save SheetName (%s), Item Count (%d)", (HTtchar*)it->first, (it->second)->HT_nGetItemCount() );
			MessageBox( HT_NULL, (HTtchar*)strDebug, _T("CHTFXMAPResMgr::HT_hrSave"), MB_OK );
			return HT_FAIL;
		}
		it++;
	}

	oSaveFile.HT_vClose();

	return HT_OK;
}

HTtchar*
CHTFXMAPResMgr::HT_pGetTableName( HTdword dwID )
{
	if ( HT_IS_MONSTERSKILL( dwID ) )				return HT_FXRES_TABLENAME_MONSTERSKILL;
	else if ( HT_IS_MONSTEREFFECT( dwID) )			return HT_FXRES_TABLENAME_MONSTEREFFECT;
	else if ( HT_IS_FXNAME_MONSTERSKILL( dwID ) )	return HT_FXRES_TABLENAME_FXMONSTERSKILL;
	else if ( HT_IS_FXNAME_MONSTERETC( dwID ) )		return HT_FXRES_TABLENAME_FXMONSTERETC;
	else if ( HT_IS_FXNAME_FIELDEFFECT( dwID ) )	return HT_FXRES_TABLENAME_FXFIELD;
	else if ( HT_IS_FXMODEL_MAP( dwID ) )			return HT_FXRES_TABLENAME_MODEL;
	else if ( HT_IS_FXTEXTURE_MAP( dwID ) )			return HT_FXRES_TABLENAME_TEXTURE;
	else if ( HT_IS_FXANIMATION_MAP( dwID ) )		return HT_FXRES_TABLENAME_ANIMATION;
	else if ( HT_IS_FXSOUND_MAP( dwID ) )			return HT_FXRES_TABLENAME_SOUND;
	else											return HT_NULL;
}

CHTFXBaseResTable*
CHTFXMAPResMgr::HT_pGetTable( HTdword dwID )
{
	HTtchar* pTable = HT_pGetTableName( dwID );
	if ( !pTable ) return HT_NULL;

	HTFXResTable_It it = m_mapTables.find( pTable );
	if ( it != m_mapTables.end() ) return ( it->second );

	return HT_NULL;
}

HTdword
CHTFXMAPResMgr::HT_dwGetIDByIndex( CHTString& strTable, HTuint idxRow )
{
	HTFXResTable_It it = m_mapTables.find( (HTtchar*)strTable );
	if ( it != m_mapTables.end() )
	{
		if ( it->second ) return (it->second)->HT_dwGetIDByIndex( idxRow );
	}

	return 0;
}

HTuint
CHTFXMAPResMgr::HT_nGetItemCount( CHTString& strTable )
{
	HTFXResTable_It it = m_mapTables.find( (HTtchar*)strTable );
	if ( it != m_mapTables.end() )
	{
		if ( it->second ) return (it->second)->HT_nGetItemCount();
	}

	return 0;
}

HTbool
CHTFXMAPResMgr::HT_bGetSkillType( HTdword dwID, HTdword& dwType )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillType( dwID, dwType );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetCastFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetCastFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetActivateFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetActivateFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetFollowFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetFollowFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetImpactFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetImpactFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetStateFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetStateFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetSkillAni( HTdword dwID, HTdword& dwAni )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetSkillAni( dwID, dwAni );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetBornFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetBornFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetDieActivateFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetDieActivateFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetAlwaysFX( HTdword dwID, HTdword& dwFX )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetAlwaysFX( dwID, dwFX );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwWhereAttach, HTdword& dwPriority )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetFX( dwID, strFXName, dwWhereAttach, dwPriority );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetModelName( HTdword dwID, CHTString& strName )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetName( dwID, strName );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetTextureName( HTdword dwID, CHTString& strName )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetName( dwID, strName );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetAnimationName( HTdword dwID, CHTString& strName )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetName( dwID, strName );
	else			return HT_FALSE;
}

HTbool
CHTFXMAPResMgr::HT_bGetSoundName( HTdword dwID, CHTString& strName )
{
	CHTFXBaseResTable* pTable = HT_pGetTable( dwID );
	if ( pTable )	return pTable->HT_bGetName( dwID, strName );
	else			return HT_FALSE;
}