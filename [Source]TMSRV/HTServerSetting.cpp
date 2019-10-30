#include "StdAfx.h"
#include "HTServerSetting.h"

//
#include "HTFile.h"
#include "HTString.h"
#include "HTXMLParser.h"


HTIDLevel2::HTIDLevel2() { iID = 0; byteLevel = 0; }
HTIDLevel2::~HTIDLevel2() {}
HTIDLevel2::HTIDLevel2( const HTIDLevel2& oIDLevel ) { iID = oIDLevel.iID; byteLevel = oIDLevel.byteLevel; }

#define HT_LOADCELL( szCell, Value, DataType ) \
{ strCell = (szCell); pXML->HT_hrGetTableValue( strTable, strCell, i, &iTemp ); Value = (DataType)iTemp; }

#define HT_LANGUAGE_KOREAN			_T("Korean")
#define HT_LANGUAGE_CHINESE			_T("Chinese")		// 중국
#define HT_LANGUAGE_PHILIPPINE		_T("Philippine")	// 필리핀
#define HT_LANGUAGE_INDONESIA		_T("Indonesia")		// 인도네시아
#define HT_LANGUAGE_JAPANESE		_T("Japanese")		// 일본어

CHTBaseSSettingTable::CHTBaseSSettingTable() :
	m_nItems	( 0 )
{}

CHTBaseSSettingTable::~CHTBaseSSettingTable()
{}


CHTSSettingMgr::CHTSSettingMgr()
{
	//memset( m_arrParamTable, 0, sizeof(CHTBaseSSettingTable*) * 255 );
}

CHTSSettingMgr::~CHTSSettingMgr()
{}


bool
CHTSSettingMgr::HT_bLoadXML( CHTString& strFile )
{
	bool bReturn = true;
	CHTString strTable;
	CHTXMLParser oXML;

	if ( HT_FAILED( oXML.HT_hrOpen( strFile ) ) ) return false;

	strTable = _T("AIList");
	if( m_kAIList.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("ActionList");
	if( m_kActionList.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("Action");
	if( m_kAction.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("SpeechContent");
	if( m_kSpeechContent.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("SpeechComment");
	if( m_kSpeechComment.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("LevelUp");
	if( m_kLevelUp.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("BramanPoint");
	if( m_kBramanPoint.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("AttackTypeVSArmorType");
	if( m_kAttackTypeVSArmorType.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("Coefficient");
	if( m_kCoefficientByClass.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("JudgeCombat");
	if( m_kJudgeCombat.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("Consider");
	if( m_kConsider.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("RvRPKConsider");
	if( m_kRvRPKConsider.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("EffectTolerance");
	if( m_kEffectTolerance.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("KalaAltar");
	if( m_kKalaAltar.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("KalaRewarderPosition");
	if( m_kKalaRewarderPosition.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("EventList");
	if( m_kEventList.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("TaskList");
	if( m_kTaskList.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("EventSchedule");
	if( m_kEventSchedule.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}


	strTable = _T("SetItem");
	if( m_kSetItem.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}


	strTable = _T("ItemRateByMonLevel");
	if( m_kItemRateByMonLevel.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("ItemRateByMonLevelForTestSrv");
	if( m_kItemRateByMonLevelForTestSrv.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("ItemByLevel");
	if( m_kItemByLevel.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("ItemGroup");
	if( m_kItemGroup.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("RateByItemCategory");
	if( m_kRateByItemCategory.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}

	strTable = _T("GameEvent");
	if( m_kGameEvent.HT_bLoad( &oXML, strTable, m_szLanguage ) )
	{
		bReturn &= true;
	}
	else
	{
		bReturn &= false;
	}
	

	// 탭의 이름
	// strTable = _T("Monster");

	// 배열의 인덱싱과.. 그에 합당하는 new
	// m_arrParamTable[HT_PARAMTYPE_MONSTER] = new CHTMonsterParamTable;

	// 해당하는 Load를 부름
	//if ( m_arrParamTable[HT_PARAMTYPE_MONSTER]->HT_bLoad( &oXML, strTable ) )
	//{
	//	bReturn &= true;
	//}
	//else
	//{
	//	bReturn &= false;
	//}

	// 원하는 탭의 수만큼 반복....

	return bReturn;
}

bool
CHTSSettingMgr::HT_bSave( CHTString& strFile )
{
	// Save
	CHTFile oSaveFile;
	if ( !oSaveFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_WRITEONLY ) )
		return false;

	bool bReturn = true;

	bReturn &= m_kAIList.HT_bSave( &oSaveFile );
	bReturn &= m_kAction.HT_bSave( &oSaveFile );
	bReturn &= m_kActionList.HT_bSave( &oSaveFile );
	bReturn &= m_kSpeechContent.HT_bSave( &oSaveFile );
	bReturn &= m_kSpeechComment.HT_bSave( &oSaveFile );
	bReturn &= m_kLevelUp.HT_bSave( &oSaveFile );
	bReturn &= m_kBramanPoint.HT_bSave( &oSaveFile );
	bReturn &= m_kAttackTypeVSArmorType.HT_bSave( &oSaveFile );
	bReturn &= m_kCoefficientByClass.HT_bSave( &oSaveFile );
	bReturn &= m_kJudgeCombat.HT_bSave( &oSaveFile );
	bReturn &= m_kConsider.HT_bSave( &oSaveFile );
	bReturn &= m_kRvRPKConsider.HT_bSave( &oSaveFile );
	bReturn &= m_kEffectTolerance.HT_bSave( &oSaveFile );
	bReturn &= m_kItemByLevel.HT_bSave( &oSaveFile );
	bReturn &= m_kItemRateByMonLevel.HT_bSave( &oSaveFile );
	bReturn &= m_kItemRateByMonLevelForTestSrv.HT_bSave( &oSaveFile );
	bReturn &= m_kItemGroup.HT_bSave( &oSaveFile );
	bReturn &= m_kRateByItemCategory.HT_bSave( &oSaveFile );
	bReturn &= m_kKalaAltar.HT_bSave( &oSaveFile );
	bReturn &= m_kKalaRewarderPosition.HT_bSave( &oSaveFile );	
	bReturn &= m_kEventList.HT_bSave( &oSaveFile );
	bReturn &= m_kTaskList.HT_bSave( &oSaveFile );
	bReturn &= m_kEventSchedule.HT_bSave( &oSaveFile );	
	bReturn &= m_kGameEvent.HT_bSave( &oSaveFile );
	bReturn &= m_kSetItem.HT_bSave( &oSaveFile );

	oSaveFile.HT_vClose();
	return true;
}

bool
CHTSSettingMgr::HT_bLoad( CHTString& strFile )
{
	CHTFile oLoadFile;
	if ( !oLoadFile.HT_bOpen( strFile, HT_FILEOPT_BINARY | HT_FILEOPT_READONLY ) ) return false;

	// 각각의 인덱싱에 적당한 new를 해줌
	//m_arrParamTable[HT_PARAMTYPE_MONSTER]		= new CHTMonsterParamTable;

	bool bReturn = true;

	CHTString strTable;
	//bReturn &= m_arrParamTable[HT_PARAMTYPE_MONSTER]->HT_bLoad( &oLoadFile );
	bReturn &= m_kAIList.HT_bLoad( &oLoadFile );
	bReturn &= m_kAction.HT_bLoad( &oLoadFile );
	bReturn &= m_kActionList.HT_bLoad( &oLoadFile );
	bReturn &= m_kSpeechContent.HT_bLoad( &oLoadFile );
	bReturn &= m_kSpeechComment.HT_bLoad( &oLoadFile );
	bReturn &= m_kLevelUp.HT_bLoad( &oLoadFile );
	bReturn &= m_kBramanPoint.HT_bLoad( &oLoadFile );
	bReturn &= m_kAttackTypeVSArmorType.HT_bLoad( &oLoadFile );
	bReturn &= m_kCoefficientByClass.HT_bLoad( &oLoadFile );
	bReturn &= m_kJudgeCombat.HT_bLoad( &oLoadFile );
	bReturn &= m_kConsider.HT_bLoad( &oLoadFile );
	bReturn &= m_kRvRPKConsider.HT_bLoad( &oLoadFile );
	bReturn &= m_kEffectTolerance.HT_bLoad( &oLoadFile );
	bReturn &= m_kItemByLevel.HT_bLoad( &oLoadFile );
	bReturn &= m_kItemRateByMonLevel.HT_bLoad( &oLoadFile );
	bReturn &= m_kItemRateByMonLevelForTestSrv.HT_bLoad( &oLoadFile );	
	bReturn &= m_kItemGroup.HT_bLoad( &oLoadFile );
	bReturn &= m_kRateByItemCategory.HT_bLoad( &oLoadFile );
	bReturn &= m_kKalaAltar.HT_bLoad( &oLoadFile );
	bReturn &= m_kKalaRewarderPosition.HT_bLoad( &oLoadFile );
	bReturn &= m_kEventList.HT_bLoad( &oLoadFile );
	bReturn &= m_kTaskList.HT_bLoad( &oLoadFile );
	bReturn &= m_kEventSchedule.HT_bLoad( &oLoadFile );	
	bReturn &= m_kGameEvent.HT_bLoad( &oLoadFile );
	bReturn &= m_kSetItem.HT_bLoad( &oLoadFile );

	return bReturn;
}


bool
CHTSSettingMgr::HT_bTestSave( CHTString& strFile )
{
	// XML 은 잘못 읽는 경우가 많이 생기므로..
	FILE* pFile;
	if ( pFile = fopen( (HTtchar*)strFile, "wt" ) )
	{		

		HT_vTestAIList( pFile );
		HT_vTestActionList( pFile );
		HT_vTestAction( pFile );
		HT_vTestSpeechContent( pFile );
		HT_vTestSpeechComment( pFile );
		HT_vTestLevelUp( pFile );
		HT_vTestBramanPoint( pFile );
		HT_vTestAttackTypeVSArmorType( pFile );
		HT_vTestCoefficientByClass( pFile );
		HT_vTestJudgeCombat( pFile );
		HT_vTestConsider( pFile );
		HT_vTestRvRPKConsider( pFile );
		HT_vTestEffectTolerance( pFile );
		HT_vTestItemByLevel( pFile );
		HT_vTestItemRateByMonLevel( pFile );
		HT_vTestItemRateByMonLevelForTestSrv( pFile );
		HT_vTestItemGroup( pFile );
		HT_vTestRateByItemCategory( pFile );
		HT_vTestKalaAltar( pFile );
		HT_vTestRewarderPosition( pFile );
		HT_vTestEventList( pFile );
		HT_vTestTaskList( pFile );
		HT_vTestEventSchedule( pFile );		
		HT_vTestSetItem( pFile );		
//		HT_vTestGameEvent( pFile );	

		fclose( pFile );

		return true;
	}
	else
	{
		return false;
	}

	return true;
}


void		CHTSSettingMgr::HT_vTestAIList( FILE* pFile )
{
	int index;
	int id;
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "---------------------------------------");
	fprintf( pFile, "\n\t\tAI List");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kAIList.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetAIListRest( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListRest : %d", iOut );
			if ( this->HT_bGetAIListMove( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListMove : %d", iOut );
			if ( this->HT_bGetAIListStart( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListStart : %d", iOut );
			if ( this->HT_bGetAIListArrive( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListArrive : %d", iOut );
			if ( this->HT_bGetAIListDetect( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDetect : %d", iOut );
			if ( this->HT_bGetAIListHelp1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListHelp1 : %d", iOut );
			if ( this->HT_bGetAIListLink1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListLink1 : %d", iOut );
			if ( this->HT_bGetAIListGuard( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListGuard : %d", iOut );
			if ( this->HT_bGetAIListBeKilled1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListBeKilled1 : %d", iOut );
			if ( this->HT_bGetAIListUnderAttack1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListUnderAttack1 : %d", iOut );
			if ( this->HT_bGetAIListAttack( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListAttack : %d", iOut );
			if ( this->HT_bGetAIListHit( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListHit : %d", iOut );
			if ( this->HT_bGetAIListMiss( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListMiss : %d", iOut );
			if ( this->HT_bGetAIListBeHitted( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListBeHitted : %d", iOut );
			if ( this->HT_bGetAIListDodge( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDodge : %d", iOut );
			if ( this->HT_bGetAIListTrace( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListTrace : %d", iOut );
			if ( this->HT_bGetAIListGiveUpToTrace( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListGiveUpToTrace : %d", iOut );
			if ( this->HT_bGetAIListKillEnemy( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListKillEnemy : %d", iOut );
			if ( this->HT_bGetAIListHelp2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListHelp2 : %d", iOut );
			if ( this->HT_bGetAIListLink2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListLink2 : %d", iOut );
			if ( this->HT_bGetAIListGuard2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListGuard2 : %d", iOut );
			if ( this->HT_bGetAIListBeKilled2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListBeKilled2 : %d", iOut );
			if ( this->HT_bGetAIListUnderAttack2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListUnderAttack2 : %d", iOut );
			if ( this->HT_bGetAIListCantTrace( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListCantTrace : %d", iOut );
			if ( this->HT_bGetAIListStopToAttack( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListStopToAttack : %d", iOut );
			if ( this->HT_bGetAIListReturn( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListReturn : %d", iOut );
			if ( this->HT_bGetAIListFlee( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListFlee : %d", iOut );
			if ( this->HT_bGetAIListPop( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListPop : %d", iOut );
			if ( this->HT_bGetAIListDialog1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDialog1 : %d", iOut );
			if ( this->HT_bGetAIListDialog2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDialog2 : %d", iOut );
			if ( this->HT_bGetAIListDialog3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDialog3 : %d", iOut );
			if ( this->HT_bGetAIListDialog4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDialog4 : %d", iOut );

			fflush( pFile ) ;
			++vec_It ;
		}
	}
}

//void		CHTSSettingMgr::HT_vTestAIList( FILE* pFile )
void		CHTSSettingMgr::HT_vTestAction( FILE* pFile )
{
	int index;
	int id;
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tAction");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kAction.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetActionSpeak( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSpeak : %d", iOut );
			if ( this->HT_bGetActionGroup( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionGroup : %d", iOut );
			if ( this->HT_bGetActionAction( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionAction : %d", iOut );
			if ( this->HT_bGetActionSkill( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSkill : %d", iOut );
			if ( this->HT_bGetActionState( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionState : %d", iOut );
			if ( this->HT_bGetActionEvent( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionEvent : %d", iOut );

			fflush( pFile ) ;
			++vec_It ;
		}
	}
}

//void		CHTSSettingMgr::HT_vTestActionList( FILE* pFile )
void		CHTSSettingMgr::HT_vTestActionList( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tAction List");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kActionList.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetActionListAction1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionListAction1 : %d", iOut );
			if ( this->HT_bGetActionListAction2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionListAction2 : %d", iOut );
			if ( this->HT_bGetActionListAction3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionListAction3 : %d", iOut );

			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestAction( FILE* pFile )
void		CHTSSettingMgr::HT_vTestSpeechContent( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tSpeech Content");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kSpeechContent.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetSpeechContentComment1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSpeak : %d", iOut );
			if ( this->HT_bGetSpeechContentComment2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionGroup : %d", iOut );
			if ( this->HT_bGetSpeechContentComment3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionAction : %d", iOut );
			if ( this->HT_bGetSpeechContentComment4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSkill : %d", iOut );
			if ( this->HT_bGetSpeechContentComment5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionState : %d", iOut );
			if ( this->HT_bGetSpeechContentType1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSpeak : %d", iOut );
			if ( this->HT_bGetSpeechContentType2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionGroup : %d", iOut );
			if ( this->HT_bGetSpeechContentType3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionAction : %d", iOut );
			if ( this->HT_bGetSpeechContentType4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSkill : %d", iOut );
			if ( this->HT_bGetSpeechContentType5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionState : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestSpeechContent( FILE* pFile )
void		CHTSSettingMgr::HT_vTestSpeechComment( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tSpeech Comment");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kSpeechComment.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			fprintf( pFile, "\n    : ID(%d)", id );
	
			char szComment[128] = { 0,0,0, } ;
			if ( this->HT_bGetSpeechCommentComment( id, szComment ) ) fprintf( pFile, "\nHT_bGetSpeechCommentComment : %s", szComment );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestSpeechComment( FILE* pFile )
void		CHTSSettingMgr::HT_vTestLevelUp( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tLevel Up");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kLevelUp.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetLevelUpPrana( id, &iOut ) ) fprintf( pFile, "\nHT_bGetLevelUpPrana : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}

//void		CHTSSettingMgr::HT_vTestLevelUp( FILE* pFile )
void		CHTSSettingMgr::HT_vTestBramanPoint( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tBraman Point");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kBramanPoint.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetBramanPointPoint( id, &iOut ) ) fprintf( pFile, "\nHT_bGetBramanPointPoint : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}

//void		CHTSSettingMgr::HT_vTestBramanPoint( FILE* pFile )
void		CHTSSettingMgr::HT_vTestAttackTypeVSArmorType( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tAttackType VS Armor Type");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kAttackTypeVSArmorType.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetAttackTypeVSArmorTypeDagger( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeDagger : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeSword( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeSword : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeTwoHandSword( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeTwoHandSword : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeAxe( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeAxe : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeTwoHandAxe( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeTwoHandAxe : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeSpear( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeSpear : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeBow( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeBow : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeClaw( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeClaw : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeBlunt( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeBlunt : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeMagic( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeMagic : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeAnimal( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeAnimal : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeDemon( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeDemon : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeGolem( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeGolem : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeUndead( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeUndead : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypePlant( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypePlant : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeInsect( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeInsect : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeHumanoid1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeHumanoid1 : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeHumanoid2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeHumanoid2 : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeHumanoid3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeHumanoid3 : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeHumanoid4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeHumanoid4 : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestAttackTypeVSArmorType( FILE* pFile )
void		CHTSSettingMgr::HT_vTestCoefficientByClass( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tCoefficient By Class");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kCoefficientByClass.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetCoefficientByClassClass1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassClass1 : %d", iOut );
			if ( this->HT_bGetCoefficientByClassClass2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassClass2 : %d", iOut );
			if ( this->HT_bGetCoefficientByClassDagger( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassDagger : %d", iOut );
			if ( this->HT_bGetCoefficientByClassSword( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassSword : %d", iOut );
			if ( this->HT_bGetCoefficientByClassTwoHandSword( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassTwoHandSword : %d", iOut );
			if ( this->HT_bGetCoefficientByClassAxe( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassAxe : %d", iOut );
			if ( this->HT_bGetCoefficientByClassTwoHandAxe( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassTwoHandAxe : %d", iOut );
			if ( this->HT_bGetCoefficientByClassBlunt( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassBlunt : %d", iOut );
			if ( this->HT_bGetCoefficientByClassSpear( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassSpear : %d", iOut );
			if ( this->HT_bGetCoefficientByClassStaff( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassStaff : %d", iOut );
			if ( this->HT_bGetCoefficientByClassClaw( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassClaw : %d", iOut );
			if ( this->HT_bGetCoefficientByClassBow( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassBow : %d", iOut );
			if ( this->HT_bGetCoefficientByClassThrowing( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassThrowing : %d", iOut );
			if ( this->HT_bGetCoefficientByClassBare( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassBare : %d", iOut );
			if ( this->HT_bGetCoefficientByClassShield( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassShield : %d", iOut );
			if ( this->HT_bGetCoefficientByClassHP( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassHP : %d", iOut );
			if ( this->HT_bGetCoefficientByClassTP( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassTP : %d", iOut );
			if ( this->HT_bGetCoefficientByClassRecvry( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassRecvry : %d", iOut );
			if ( this->HT_bGetCoefficientByClassAC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassAC : %d", iOut );
			if ( this->HT_bGetCoefficientByClassResist( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassResist : %d", iOut );
			if ( this->HT_bGetCoefficientByClassAttackRate( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassAttackRate : %d", iOut );
			if ( this->HT_bGetCoefficientByClassDodgeRate( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassDodgeRate : %d", iOut );
			if ( this->HT_bGetCoefficientByClassAttackSpeed( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassAttackSpeed : %d", iOut );
			if ( this->HT_bGetCoefficientByClassCastSpeed( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassCastSpeed : %d", iOut );
			if ( this->HT_bGetCoefficientByClassDodgeSpeed( id, &iOut ) ) fprintf( pFile, "\nHT_bGetCoefficientByClassDodgeSpeed : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestCoefficientByClass( FILE* pFile )
void		CHTSSettingMgr::HT_vTestJudgeCombat( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tJudge Combat");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kJudgeCombat.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetJudgeCombatCriticalPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatCriticalPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatNormalPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatNormalPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatMissPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatMissPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatCriticalPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatCriticalPCvsNPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatNormalPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatNormalPCvsNPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatMissPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatMissPCvsNPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatCriticalNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatCriticalNPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatNormalNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatNormalNPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatMissNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatMissNPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatCriticalNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatCriticalNPCvsNPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatNormalNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatNormalNPCvsNPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatMissNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatMissNPCvsNPC : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestJudgeCombat( FILE* pFile )
void		CHTSSettingMgr::HT_vTestConsider( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tConsider");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kConsider.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetConsiderDFPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDFPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderRSPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderRSPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderDGPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDGPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderDFPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDFPCvsNPC : %d", iOut );
			if ( this->HT_bGetConsiderRSPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderRSPCvsNPC : %d", iOut );
			if ( this->HT_bGetConsiderDGPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDGPCvsNPC : %d", iOut );
			if ( this->HT_bGetConsiderDFNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDFNPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderRSNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderRSNPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderDGNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDGNPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderDFNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDFNPCvsNPC : %d", iOut );
			if ( this->HT_bGetConsiderRSNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderRSNPCvsNPC : %d", iOut );
			if ( this->HT_bGetConsiderDGNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDGNPCvsNPC : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestConsider( FILE* pFile )
void		CHTSSettingMgr::HT_vTestRvRPKConsider( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tRvR PK Consider");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kRvRPKConsider.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetRvRPKConsiderRewardBP( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderRewardBP : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste0( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste0 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste1 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste2 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste3 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste4 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste5 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste6( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste6 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste7( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste7 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste8( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste8 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste9( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste9 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste10( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste10 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste11( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste11 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste12( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste12 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste13( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste13 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste14( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste14 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste15( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste15 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste16( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste16 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste17( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste17 : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestRvRPKConsider( FILE* pFile )
void		CHTSSettingMgr::HT_vTestEffectTolerance( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tEffect Tolerance");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kEffectTolerance.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetEffectToleranceClass1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceClass1 : %d", iOut );
			if ( this->HT_bGetEffectToleranceClass2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceClass2 : %d", iOut );
			if ( this->HT_bGetEffectToleranceHold( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceHold : %d", iOut );
			if ( this->HT_bGetEffectToleranceStun( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceStun : %d", iOut );
			if ( this->HT_bGetEffectToleranceSleep( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceSleep : %d", iOut );
			if ( this->HT_bGetEffectToleranceBlind( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceBlind : %d", iOut );
			if ( this->HT_bGetEffectToleranceTerror( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceTerror : %d", iOut );
			if ( this->HT_bGetEffectToleranceTaunt( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceTaunt : %d", iOut );
			if ( this->HT_bGetEffectToleranceSlowMove( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceSlowMove : %d", iOut );
			if ( this->HT_bGetEffectToleranceSlowAttack( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceSlowAttack : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestEffectTolerance( FILE* pFile )
void		CHTSSettingMgr::HT_vTestItemByLevel( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tItem By Level");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kItemByLevel.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetItemByLevelLvl1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl1 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl2 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl3 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl4 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl5 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl6( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl6 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl7( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl7 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl8( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl8 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl9( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl9 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl10( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl10 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl11( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl11 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl12( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl12 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl13( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl13 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl14( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl14 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl15( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl15 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl16( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl16 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl17( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl17 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl18( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl18 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl19( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl19 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl20( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl20 : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}



//void		CHTSSettingMgr::HT_vTestItemByLevel( FILE* pFile )
void		CHTSSettingMgr::HT_vTestItemRateByMonLevel( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tItem Rate By Monster level");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kItemRateByMonLevel.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetItemRateByMonLevelLvl1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl1 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl2 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl3 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl4 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl5 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl6( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl6 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl7( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl7 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl8( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl8 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl9( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl9 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl10( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl10 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl11( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl11 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl12( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl12 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl13( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl13 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl14( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl14 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl15( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl15 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl16( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl16 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl17( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl17 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl18( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl18 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl19( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl19 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl20( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl20 : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestItemRateByMonLevel( FILE* pFile )
void		CHTSSettingMgr::HT_vTestItemRateByMonLevelForTestSrv( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tItem Rate By Monster Level for Test Server");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kItemRateByMonLevelForTestSrv.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;

			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl1 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl2 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl3 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl4 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl5 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl6( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl6 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl7( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl7 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl8( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl8 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl9( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl9 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl10( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl10 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl11( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl11 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl12( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl12 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl13( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl13 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl14( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl14 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl15( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl15 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl16( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl16 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl17( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl17 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl18( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl18 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl19( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl19 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl20( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl20 : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestItemRateByMonLevelForTestSrv( FILE* pFile )
void		CHTSSettingMgr::HT_vTestItemGroup( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tItem Group");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kItemGroup.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetItemGroupGroup( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemGroupGroup : %d", iOut );
			if ( this->HT_bGetItemGroupItemID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemGroupItemID : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestItemGroup( FILE* pFile )
void		CHTSSettingMgr::HT_vTestKalaAltar( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tKala Altar");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kKalaAltar.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetKalaAltarZone( id, &iOut ) ) fprintf( pFile, "\nHT_bGetKalaAltarZone : %d", iOut );
			if ( this->HT_bGetKalaAltarClan( id, &iOut ) ) fprintf( pFile, "\nHT_bGetKalaAltarClan : %d", iOut );
			if ( this->HT_bGetKalaAltarX( id, &iOut ) ) fprintf( pFile, "\nHT_bGetKalaAltarX : %d", iOut );
			if ( this->HT_bGetKalaAltarY( id, &iOut ) ) fprintf( pFile, "\nHT_bGetKalaAltarY : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestKalaAltar( FILE* pFile )

void		CHTSSettingMgr::HT_vTestRewarderPosition( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tRewarder Position");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kKalaRewarderPosition.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
			
			if ( this->HT_bGetRewarderPositionZone( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRewarderPositionZone : %d", iOut );
			if ( this->HT_bGetRewarderPositionNPCIndex( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRewarderPositionNPCIndex : %d", iOut );
			if ( this->HT_bGetRewarderPositionClan( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRewarderPositionClan : %d", iOut );
			if ( this->HT_bGetRewarderPositionX( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRewarderPositionX : %d", iOut );
			if ( this->HT_bGetRewarderPositionY( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRewarderPositionY : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}


//void		CHTSSettingMgr::HT_vTestRewarderPosition( FILE* pFile )
void		CHTSSettingMgr::HT_vTestRateByItemCategory( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tRate by Item Category");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kRateByItemCategory.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetRateByItemCategoryRate( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRateByItemCategoryRate : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestRateByItemCategory( FILE* pFile )
void		CHTSSettingMgr::HT_vTestEventList( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tEvent List");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kEventList.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;

			if ( this->HT_bGetEventListZone( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListZone : %d", iOut );
			if ( this->HT_bGetEventListEventID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListEventID : %d", iOut );
			if ( this->HT_bGetEventListTask1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListTask1 : %d", iOut );
			if ( this->HT_bGetEventListTask2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListTask2 : %d", iOut );
			if ( this->HT_bGetEventListTask3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListTask3 : %d", iOut );
			if ( this->HT_bGetEventListTask4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListTask4 : %d", iOut );
			if ( this->HT_bGetEventListTask5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListTask5 : %d", iOut );
			if ( this->HT_bGetEventListCoolDownTime( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListCoolDownTime : %d", iOut );
			if ( this->HT_bGetEventListCount( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListCount : %d", iOut );
			if ( this->HT_bGetEventListProceedType( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListProceedType : %d", iOut );
			if ( this->HT_bGetEventListDuration( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListDuration : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestEventList( FILE* pFile )
void		CHTSSettingMgr::HT_vTestTaskList( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tTask List");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kTaskList.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetTaskListZone( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListZone : %d", iOut );
			if ( this->HT_bGetTaskListTaskID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListTaskID : %d", iOut );
			if ( this->HT_bGetTaskListActionID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListActionID : %d", iOut );
			if ( this->HT_bGetTaskListParam1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListParam1 : %d", iOut );
			if ( this->HT_bGetTaskListParam2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListParam2 : %d", iOut );
			if ( this->HT_bGetTaskListParam3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListParam3 : %d", iOut );
			if ( this->HT_bGetTaskListParam4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListParam4 : %d", iOut );
			if ( this->HT_bGetTaskListParam5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListParam5 : %d", iOut );
			if ( this->HT_bGetTaskListParam6( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListParam6 : %d", iOut );

			fflush( pFile ) ;
			++vec_It ;
		}
	}
}

void		CHTSSettingMgr::HT_vTestEventSchedule( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tEvent Schedule");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kEventSchedule.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;

			if ( this->HT_bGetEventScheduleZone( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventScheduleZone : %d", iOut );
			if ( this->HT_bGetEventScheduleMin( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventScheduleMin : %d", iOut );
			if ( this->HT_bGetEventScheduleSec( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventScheduleSec : %d", iOut );
			if ( this->HT_bGetEventScheduleEvent( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventScheduleEvent : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}





void CHTSSettingMgr::HT_vTestSetItem( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tSet Item");
	fprintf( pFile, "\n---------------------------------------");


	if( m_kSetItem.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;

			if ( this->HT_bGetSetItemID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemID : %d", iOut );
			if ( this->HT_bGetSetItemHelmet( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemHelmet : %d", iOut );
			if ( this->HT_bGetSetItemNecklace( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemNecklace : %d", iOut );
			if ( this->HT_bGetSetItemArmor( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemArmor : %d", iOut );
			if ( this->HT_bGetSetItemBelt( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemBelt : %d", iOut );
			if ( this->HT_bGetSetItemWeapon( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemWeapon : %d", iOut );
			if ( this->HT_bGetSetItemShield( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemShield : %d", iOut );
			if ( this->HT_bGetSetItemBoots( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemBoots : %d", iOut );
			if ( this->HT_bGetSetItemGloves( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemGloves : %d", iOut );
			if ( this->HT_bGetSetItemPants( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemPants : %d", iOut );
			if ( this->HT_bGetSetItemEffectItem( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemEffectItem : %d", iOut );
			if ( this->HT_bGetSetItemEffectItem2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemEffectItem2 : %d", iOut );
#ifndef __BEFORE_SET_ITEM_EXPANDED__
			if ( this->HT_bGetSetItemEffectItem3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetSetItemEffectItem3 : %d", iOut );
#endif
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}



/*
////////////////////////////////////////////////////////////////////////////////////////////////////*
void		CHTSSettingMgr::HT_vLoadAIList( int* a_pData )
{
	int index;
	int id;
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "---------------------------------------");
	fprintf( pFile, "\n\t\tAI List");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kAIList.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;
			a_pData[id

			if ( this->HT_bGetAIListRest( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListRest : %d", iOut );
			if ( this->HT_bGetAIListMove( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListMove : %d", iOut );
			if ( this->HT_bGetAIListStart( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListStart : %d", iOut );
			if ( this->HT_bGetAIListArrive( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListArrive : %d", iOut );
			if ( this->HT_bGetAIListDetect( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDetect : %d", iOut );
			if ( this->HT_bGetAIListHelp1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListHelp1 : %d", iOut );
			if ( this->HT_bGetAIListLink1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListLink1 : %d", iOut );
			if ( this->HT_bGetAIListGuard( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListGuard : %d", iOut );
			if ( this->HT_bGetAIListBeKilled1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListBeKilled1 : %d", iOut );
			if ( this->HT_bGetAIListUnderAttack1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListUnderAttack1 : %d", iOut );
			if ( this->HT_bGetAIListAttack( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListAttack : %d", iOut );
			if ( this->HT_bGetAIListHit( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListHit : %d", iOut );
			if ( this->HT_bGetAIListMiss( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListMiss : %d", iOut );
			if ( this->HT_bGetAIListBeHitted( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListBeHitted : %d", iOut );
			if ( this->HT_bGetAIListDodge( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDodge : %d", iOut );
			if ( this->HT_bGetAIListTrace( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListTrace : %d", iOut );
			if ( this->HT_bGetAIListGiveUpToTrace( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListGiveUpToTrace : %d", iOut );
			if ( this->HT_bGetAIListKillEnemy( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListKillEnemy : %d", iOut );
			if ( this->HT_bGetAIListHelp2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListHelp2 : %d", iOut );
			if ( this->HT_bGetAIListLink2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListLink2 : %d", iOut );
			if ( this->HT_bGetAIListGuard2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListGuard2 : %d", iOut );
			if ( this->HT_bGetAIListBeKilled2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListBeKilled2 : %d", iOut );
			if ( this->HT_bGetAIListUnderAttack2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListUnderAttack2 : %d", iOut );
			if ( this->HT_bGetAIListCantTrace( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListCantTrace : %d", iOut );
			if ( this->HT_bGetAIListStopToAttack( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListStopToAttack : %d", iOut );
			if ( this->HT_bGetAIListReturn( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListReturn : %d", iOut );
			if ( this->HT_bGetAIListFlee( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListFlee : %d", iOut );
			if ( this->HT_bGetAIListPop( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListPop : %d", iOut );
			if ( this->HT_bGetAIListDialog1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDialog1 : %d", iOut );
			if ( this->HT_bGetAIListDialog2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDialog2 : %d", iOut );
			if ( this->HT_bGetAIListDialog3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDialog3 : %d", iOut );
			if ( this->HT_bGetAIListDialog4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAIListDialog4 : %d", iOut );

			fflush( pFile ) ;
			++vec_It ;
		}
	}
}

//void		CHTSSettingMgr::HT_vTestAIList( FILE* pFile )
void		CHTSSettingMgr::HT_vLoadAction( int* a_pData )
{
	int index;
	int id;
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tAction");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kAction.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetActionSpeak( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSpeak : %d", iOut );
			if ( this->HT_bGetActionGroup( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionGroup : %d", iOut );
			if ( this->HT_bGetActionAction( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionAction : %d", iOut );
			if ( this->HT_bGetActionSkill( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSkill : %d", iOut );
			if ( this->HT_bGetActionState( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionState : %d", iOut );
			if ( this->HT_bGetActionEvent( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionEvent : %d", iOut );

			fflush( pFile ) ;
			++vec_It ;
		}
	}
}

//void		CHTSSettingMgr::HT_vTestActionList( int* a_pData )
void		CHTSSettingMgr::HT_vLoadActionList( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tAction List");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kActionList.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetActionListAction1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionListAction1 : %d", iOut );
			if ( this->HT_bGetActionListAction2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionListAction2 : %d", iOut );
			if ( this->HT_bGetActionListAction3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionListAction3 : %d", iOut );

			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vTestAction( int* a_pData )
void		CHTSSettingMgr::HT_vLoadSpeechContent( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tSpeech Content");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kSpeechContent.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetSpeechContentComment1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSpeak : %d", iOut );
			if ( this->HT_bGetSpeechContentComment2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionGroup : %d", iOut );
			if ( this->HT_bGetSpeechContentComment3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionAction : %d", iOut );
			if ( this->HT_bGetSpeechContentComment4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSkill : %d", iOut );
			if ( this->HT_bGetSpeechContentComment5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionState : %d", iOut );
			if ( this->HT_bGetSpeechContentType1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSpeak : %d", iOut );
			if ( this->HT_bGetSpeechContentType2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionGroup : %d", iOut );
			if ( this->HT_bGetSpeechContentType3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionAction : %d", iOut );
			if ( this->HT_bGetSpeechContentType4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionSkill : %d", iOut );
			if ( this->HT_bGetSpeechContentType5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetActionState : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadSpeechContent( int* a_pData )
void		CHTSSettingMgr::HT_vLoadSpeechComment( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tSpeech Comment");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kSpeechComment.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			fprintf( pFile, "\n    : ID(%d)", id );
	
			char szComment[128] = { 0,0,0, } ;
			if ( this->HT_bGetSpeechCommentComment( id, szComment ) ) fprintf( pFile, "\nHT_bGetSpeechCommentComment : %s", szComment );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadSpeechComment( int* a_pData )
void		CHTSSettingMgr::HT_vLoadLevelUp( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tLevel Up");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kLevelUp.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetLevelUpPrana( id, &iOut ) ) a_pData[id-1] = iOut ;
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}

//void		CHTSSettingMgr::HT_vLoadLevelUp( int* a_pData )
void		CHTSSettingMgr::HT_vLoadBramanPoint( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tBraman Point");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kBramanPoint.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetBramanPointPoint( id, &iOut ) ) a_pData[id] = iOut ;
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}

//void		CHTSSettingMgr::HT_vLoadBramanPoint( int* a_pData )
void		CHTSSettingMgr::HT_vLoadAttackTypeVSArmorType( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tAttackType VS Armor Type");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kAttackTypeVSArmorType.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetAttackTypeVSArmorTypeDagger( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeDagger : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeSword( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeSword : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeTwoHandSword( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeTwoHandSword : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeAxe( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeAxe : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeTwoHandAxe( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeTwoHandAxe : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeSpear( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeSpear : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeDagger( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeDagger : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeSword( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeSword : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeTwoHandSword( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeTwoHandSword : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeAxe( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeAxe : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeTwoHandAxe( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeTwoHandAxe : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeSpear( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeSpear : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeBow( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeBow : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeClaw( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeClaw : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeBlunt( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeBlunt : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeMagic( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeMagic : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeAnimal( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeAnimal : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeDemon( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeDemon : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeGolem( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeGolem : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeUndead( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeUndead : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypePlant( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypePlant : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeInsect( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeInsect : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeHumanoid1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeHumanoid1 : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeHumanoid2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeHumanoid2 : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeHumanoid3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeHumanoid3 : %d", iOut );
			if ( this->HT_bGetAttackTypeVSArmorTypeHumanoid4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetAttackTypeVSArmorTypeHumanoid4 : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}

void		CHTSSettingMgr::HT_vLoadCoefficientByClass( int** a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tCoefficient By Class");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kCoefficientByClass.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;			

			int iOut;
			int iClass1 = 0 ;
			int iClass2 = 0 ;

			this->HT_bGetCoefficientByClassClass1( id, &iClass1 ) ;
			this->HT_bGetCoefficientByClassClass2( id, &iClass2 ) ;
			if ( this->HT_bGetCoefficientByClassDagger( id, &iOut ) ) a_pData[iClass1][iClass2].iDagger = iOut ;
			if ( this->HT_bGetCoefficientByClassSword( id, &iOut ) ) a_pData[iClass1][iClass2].iSword = iOut ;
			if ( this->HT_bGetCoefficientByClassTwoHandSword( id, &iOut ) ) a_pData[iClass1][iClass2].iTwoHandSword = iOut ;
			if ( this->HT_bGetCoefficientByClassAxe( id, &iOut ) ) a_pData[iClass1][iClass2].iAxe = iOut ;
			if ( this->HT_bGetCoefficientByClassTwoHandAxe( id, &iOut ) ) a_pData[iClass1][iClass2].iTwoHandAxe = iOut ;
			if ( this->HT_bGetCoefficientByClassBlunt( id, &iOut ) ) a_pData[iClass1][iClass2].iBlunt = iOut ;
			if ( this->HT_bGetCoefficientByClassSpear( id, &iOut ) ) a_pData[iClass1][iClass2].iSpear = iOut ;
			if ( this->HT_bGetCoefficientByClassStaff( id, &iOut ) ) a_pData[iClass1][iClass2].iStaff = iOut ;
			if ( this->HT_bGetCoefficientByClassClaw( id, &iOut ) ) a_pData[iClass1][iClass2].iClaw = iOut ;
			if ( this->HT_bGetCoefficientByClassBow( id, &iOut ) ) a_pData[iClass1][iClass2].iBow = iOut ;
			if ( this->HT_bGetCoefficientByClassThrowing( id, &iOut ) ) a_pData[iClass1][iClass2].iThrowing = iOut ;
			if ( this->HT_bGetCoefficientByClassBare( id, &iOut ) ) a_pData[iClass1][iClass2].iBare = iOut ;
			if ( this->HT_bGetCoefficientByClassShield( id, &iOut ) ) a_pData[iClass1][iClass2].iShield = iOut ;
			if ( this->HT_bGetCoefficientByClassHP( id, &iOut ) ) a_pData[iClass1][iClass2].iHP = iOut ;
			if ( this->HT_bGetCoefficientByClassTP( id, &iOut ) ) a_pData[iClass1][iClass2].iTP = iOut ;
			if ( this->HT_bGetCoefficientByClassRecvry( id, &iOut ) ) a_pData[iClass1][iClass2].iRecvry = iOut ;
			if ( this->HT_bGetCoefficientByClassAC( id, &iOut ) ) a_pData[iClass1][iClass2].iAC = iOut ;
			if ( this->HT_bGetCoefficientByClassResist( id, &iOut ) ) a_pData[iClass1][iClass2].iResist = iOut ;
			if ( this->HT_bGetCoefficientByClassAttackRate( id, &iOut ) ) a_pData[iClass1][iClass2].iAttackRate = iOut ;
			if ( this->HT_bGetCoefficientByClassDodgeRate( id, &iOut ) ) a_pData[iClass1][iClass2].iDodgeRate = iOut ;
			if ( this->HT_bGetCoefficientByClassAttackSpeed( id, &iOut ) ) a_pData[iClass1][iClass2].iAttackSpeed = iOut ;
			if ( this->HT_bGetCoefficientByClassCastSpeed( id, &iOut ) ) a_pData[iClass1][iClass2].iCastSpeed = iOut ;
			if ( this->HT_bGetCoefficientByClassDodgeSpeed( id, &iOut ) ) a_pData[iClass1][iClass2].iDodgeSpeed = iOut ;
			
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadCoefficientByClass( int* a_pData )
void		CHTSSettingMgr::HT_vLoadJudgeCombat( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tJudge Combat");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kJudgeCombat.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetJudgeCombatCriticalPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatCriticalPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatNormalPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatNormalPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatMissPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatMissPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatCriticalPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatCriticalPCvsNPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatNormalPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatNormalPCvsNPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatMissPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatMissPCvsNPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatCriticalNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatCriticalNPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatNormalNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatNormalNPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatMissNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatMissNPCvsPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatCriticalNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatCriticalNPCvsNPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatNormalNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatNormalNPCvsNPC : %d", iOut );
			if ( this->HT_bGetJudgeCombatMissNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetJudgeCombatMissNPCvsNPC : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadJudgeCombat( int* a_pData )
void		CHTSSettingMgr::HT_vLoadConsider( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tConsider");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kConsider.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetConsiderDFPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDFPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderRSPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderRSPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderDGPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDGPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderDFPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDFPCvsNPC : %d", iOut );
			if ( this->HT_bGetConsiderRSPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderRSPCvsNPC : %d", iOut );
			if ( this->HT_bGetConsiderDGPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDGPCvsNPC : %d", iOut );
			if ( this->HT_bGetConsiderDFNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDFNPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderRSNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderRSNPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderDGNPCvsPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDGNPCvsPC : %d", iOut );
			if ( this->HT_bGetConsiderDFNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDFNPCvsNPC : %d", iOut );
			if ( this->HT_bGetConsiderRSNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderRSNPCvsNPC : %d", iOut );
			if ( this->HT_bGetConsiderDGNPCvsNPC( id, &iOut ) ) fprintf( pFile, "\nHT_bGetConsiderDGNPCvsNPC : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadConsider( int* a_pData )
void		CHTSSettingMgr::HT_vLoadRvRPKConsider( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tRvR PK Consider");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kRvRPKConsider.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetRvRPKConsiderRewardBP( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderRewardBP : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste0( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste0 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste1 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste2 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste3 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste4 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste5 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste6( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste6 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste7( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste7 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste8( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste8 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste9( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste9 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste10( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste10 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste11( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste11 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste12( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste12 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste13( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste13 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste14( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste14 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste15( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste15 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste16( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste16 : %d", iOut );
			if ( this->HT_bGetRvRPKConsiderAttackerCaste17( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRvRPKConsiderAttackerCaste17 : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadRvRPKConsider( int* a_pData )
void		CHTSSettingMgr::HT_vLoadEffectTolerance( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tEffect Tolerance");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kEffectTolerance.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetEffectToleranceClass1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceClass1 : %d", iOut );
			if ( this->HT_bGetEffectToleranceClass2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceClass2 : %d", iOut );
			if ( this->HT_bGetEffectToleranceHold( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceHold : %d", iOut );
			if ( this->HT_bGetEffectToleranceStun( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceStun : %d", iOut );
			if ( this->HT_bGetEffectToleranceSleep( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceSleep : %d", iOut );
			if ( this->HT_bGetEffectToleranceBlind( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceBlind : %d", iOut );
			if ( this->HT_bGetEffectToleranceTerror( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceTerror : %d", iOut );
			if ( this->HT_bGetEffectToleranceTaunt( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceTaunt : %d", iOut );
			if ( this->HT_bGetEffectToleranceSlowMove( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceSlowMove : %d", iOut );
			if ( this->HT_bGetEffectToleranceSlowAttack( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEffectToleranceSlowAttack : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadEffectTolerance( int* a_pData )
void		CHTSSettingMgr::HT_vLoadItemByLevel( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tItem By Level");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kItemByLevel.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetItemByLevelLvl1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl1 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl2 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl3 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl4 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl5 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl6( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl6 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl7( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl7 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl8( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl8 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl9( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl9 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl10( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl10 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl11( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl11 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl12( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl12 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl13( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl13 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl14( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl14 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl15( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl15 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl16( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl16 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl17( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl17 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl18( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl18 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl19( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl19 : %d", iOut );
			if ( this->HT_bGetItemByLevelLvl20( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemByLevelLvl20 : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}



//void		CHTSSettingMgr::HT_vLoadItemByLevel( int* a_pData )
void		CHTSSettingMgr::HT_vLoadItemRateByMonLevel( int* a_pData )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tItem Rate By Monster level");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kItemRateByMonLevel.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetItemRateByMonLevelLvl1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl1 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl2 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl3 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl4 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl5 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl6( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl6 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl7( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl7 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl8( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl8 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl9( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl9 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl10( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl10 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl11( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl11 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl12( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl12 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl13( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl13 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl14( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl14 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl15( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl15 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl16( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl16 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl17( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl17 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl18( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl18 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl19( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl19 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelLvl20( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelLvl20 : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadItemRateByMonLevel( int* a_pData )
void		CHTSSettingMgr::HT_vLoadItemRateByMonLevelForTestSrv( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tItem Rate By Monster Level for Test Server");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kItemRateByMonLevelForTestSrv.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;

			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl1 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl2 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl3 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl4 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl5 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl6( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl6 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl7( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl7 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl8( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl8 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl9( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl9 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl10( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl10 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl11( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl11 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl12( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl12 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl13( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl13 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl14( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl14 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl15( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl15 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl16( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl16 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl17( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl17 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl18( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl18 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl19( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl19 : %d", iOut );
			if ( this->HT_bGetItemRateByMonLevelForTestSrvLvl20( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemRateByMonLevelForTestSrvLvl20 : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadItemRateByMonLevelForTestSrv( FILE* pFile )
void		CHTSSettingMgr::HT_vLoadItemGroup( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tItem Group");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kItemGroup.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetItemGroupGroup( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemGroupGroup : %d", iOut );
			if ( this->HT_bGetItemGroupItemID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetItemGroupItemID : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadItemGroup( FILE* pFile )
void		CHTSSettingMgr::HT_vLoadKalaAltar( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tKala Altar");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kKalaAltar.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetKalaAltarZone( id, &iOut ) ) fprintf( pFile, "\nHT_bGetKalaAltarZone : %d", iOut );
			if ( this->HT_bGetKalaAltarClan( id, &iOut ) ) fprintf( pFile, "\nHT_bGetKalaAltarClan : %d", iOut );
			if ( this->HT_bGetKalaAltarX( id, &iOut ) ) fprintf( pFile, "\nHT_bGetKalaAltarX : %d", iOut );
			if ( this->HT_bGetKalaAltarY( id, &iOut ) ) fprintf( pFile, "\nHT_bGetKalaAltarY : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadKalaAltar( FILE* pFile )

void		CHTSSettingMgr::HT_vLoadRewarderPosition( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tRewarder Position");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kKalaRewarderPosition.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
			
			if ( this->HT_bGetRewarderPositionZone( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRewarderPositionZone : %d", iOut );
			if ( this->HT_bGetRewarderPositionNPCIndex( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRewarderPositionNPCIndex : %d", iOut );
			if ( this->HT_bGetRewarderPositionClan( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRewarderPositionClan : %d", iOut );
			if ( this->HT_bGetRewarderPositionX( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRewarderPositionX : %d", iOut );
			if ( this->HT_bGetRewarderPositionY( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRewarderPositionY : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}


//void		CHTSSettingMgr::HT_vLoadRewarderPosition( FILE* pFile )
void		CHTSSettingMgr::HT_vLoadRateByItemCategory( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tRate by Item Category");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kRateByItemCategory.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetRateByItemCategoryRate( id, &iOut ) ) fprintf( pFile, "\nHT_bGetRateByItemCategoryRate : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadRateByItemCategory( FILE* pFile )
void		CHTSSettingMgr::HT_vLoadEventList( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tEvent List");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kEventList.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;

			if ( this->HT_bGetEventListZone( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListZone : %d", iOut );
			if ( this->HT_bGetEventListEventID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListEventID : %d", iOut );
			if ( this->HT_bGetEventListTask1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListTask1 : %d", iOut );
			if ( this->HT_bGetEventListTask2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListTask2 : %d", iOut );
			if ( this->HT_bGetEventListTask3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListTask3 : %d", iOut );
			if ( this->HT_bGetEventListTask4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListTask4 : %d", iOut );
			if ( this->HT_bGetEventListTask5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListTask5 : %d", iOut );
			if ( this->HT_bGetEventListCoolDownTime( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListCoolDownTime : %d", iOut );
			if ( this->HT_bGetEventListCount( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListCount : %d", iOut );
			if ( this->HT_bGetEventListProceedType( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListProceedType : %d", iOut );
			if ( this->HT_bGetEventListDuration( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventListDuration : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
//void		CHTSSettingMgr::HT_vLoadEventList( FILE* pFile )
void		CHTSSettingMgr::HT_vLoadTaskList( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tTask List");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kTaskList.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;
			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;
		//	unsigned int uiOut;

			if ( this->HT_bGetTaskListZone( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListZone : %d", iOut );
			if ( this->HT_bGetTaskListTaskID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListTaskID : %d", iOut );
			if ( this->HT_bGetTaskListActionID( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListActionID : %d", iOut );
			if ( this->HT_bGetTaskListParam1( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListParam1 : %d", iOut );
			if ( this->HT_bGetTaskListParam2( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListParam2 : %d", iOut );
			if ( this->HT_bGetTaskListParam3( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListParam3 : %d", iOut );
			if ( this->HT_bGetTaskListParam4( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListParam4 : %d", iOut );
			if ( this->HT_bGetTaskListParam5( id, &iOut ) ) fprintf( pFile, "\nHT_bGetTaskListParam5 : %d", iOut );

			fflush( pFile ) ;
			++vec_It ;
		}
	}
}

////////////////////////////////////////////////////////////////////////







//void		CHTSSettingMgr::HT_vLoadTaskList( FILE* pFile )
void		CHTSSettingMgr::HT_vLoadEventSchedule( FILE* pFile )
{
	int index;
	int id;
	
	CHTString str;

	std::vector<HTIDLevel2> vectorIDLevel;
	vector<HTIDLevel2>::iterator vec_It;

	index = 0;

	fprintf( pFile, "\n\n\n---------------------------------------");
	fprintf( pFile, "\n\t\tEvent Schedule");
	fprintf( pFile, "\n---------------------------------------");

	if( m_kEventSchedule.HT_bGetAllID( &vectorIDLevel ) ) // 모든 아이디를 구함
	{
		vec_It = vectorIDLevel.begin();
		while ( vec_It != vectorIDLevel.end() )
		{
			id = vec_It->iID;			

			fprintf( pFile, "\n    : ID(%d)", id );
			int iOut;

			if ( this->HT_bGetEventScheduleZone( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventScheduleZone : %d", iOut );
			if ( this->HT_bGetEventScheduleMin( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventScheduleMin : %d", iOut );
			if ( this->HT_bGetEventScheduleSec( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventScheduleSec : %d", iOut );
			if ( this->HT_bGetEventScheduleEvent( id, &iOut ) ) fprintf( pFile, "\nHT_bGetEventScheduleEvent : %d", iOut );
			
			fflush( pFile ) ;
			++vec_It ;
		}
	}
}
*/


CHTAIListTable::~CHTAIListTable()
{
	HTAIList_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTAIListTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTAIList* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTAIList;

		HT_LOADCELL( _T("iID"),				iID,						int );
		HT_LOADCELL( _T("iRest"), 			pRecord->iRest,				int ); 
        HT_LOADCELL( _T("iMove"), 			pRecord->iMove,				int ); 
		HT_LOADCELL( _T("iStart"), 			pRecord->iStart,			int );  
		HT_LOADCELL( _T("iArrive"), 		pRecord->iArrive,			int );
		HT_LOADCELL( _T("iDetect"), 		pRecord->iDetect,			int );
		HT_LOADCELL( _T("iHelp1"),			pRecord->iHelp1,			int );
		HT_LOADCELL( _T("iLink1"),			pRecord->iLink1,			int );
		HT_LOADCELL( _T("iGuard1"),			pRecord->iGuard1,			int );
		HT_LOADCELL( _T("iBeKilled1"),		pRecord->iBeKilled1,		int );
		HT_LOADCELL( _T("iUnderAttack1"),	pRecord->iUnderAttack1,		int );
		HT_LOADCELL( _T("iAttack"), 		pRecord->iAttack,			int );
		HT_LOADCELL( _T("iHit"), 			pRecord->iHit,				int );
		HT_LOADCELL( _T("iMiss"),			pRecord->iMiss,				int );
		HT_LOADCELL( _T("iBeHitted"), 		pRecord->iBeHitted,			int );
		HT_LOADCELL( _T("iDodge"), 			pRecord->iDodge,			int );
		HT_LOADCELL( _T("iTrace"), 			pRecord->iTrace,			int );
		HT_LOADCELL( _T("iGiveUpToTrace"), 	pRecord->iGiveUpToTrace,	int );
		HT_LOADCELL( _T("iKillEnemy"), 		pRecord->iKillEnemy,		int );
		HT_LOADCELL( _T("iHelp2"), 			pRecord->iHelp2,			int );
		HT_LOADCELL( _T("iLink2"), 			pRecord->iLink2,			int );
		HT_LOADCELL( _T("iGuard2"), 		pRecord->iGuard2,			int );
		HT_LOADCELL( _T("iBeKilled2"), 		pRecord->iBeKilled2,		int );
		HT_LOADCELL( _T("iUnderAttack2"), 	pRecord->iUnderAttack2,		int );
		HT_LOADCELL( _T("iCantTrace"), 		pRecord->iCantTrace,		int );
		HT_LOADCELL( _T("iStopToAttack"), 	pRecord->iStopToAttack,		int );
		HT_LOADCELL( _T("iReturn"), 		pRecord->iReturn,			int );	
		HT_LOADCELL( _T("iFlee"), 			pRecord->iFlee,				int );
		HT_LOADCELL( _T("iLead"), 			pRecord->iLead,				int );
		HT_LOADCELL( _T("iPop"), 			pRecord->iPop,				int );
		HT_LOADCELL( _T("iDialog1"), 		pRecord->iDialog1,			int );
		HT_LOADCELL( _T("iDialog2"), 		pRecord->iDialog2,			int );
		HT_LOADCELL( _T("iDialog3"), 		pRecord->iDialog3,			int );
		HT_LOADCELL( _T("iDialog4"), 		pRecord->iDialog4,			int );

		m_mapTable.insert( HTAIList_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTAIListTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTAIList* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTAIList;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTAIList) );

		m_mapTable.insert( HTAIList_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTAIListTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTAIList_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTAIList) );

		itTable++;
	}

	return true;
}


bool	CHTAIListTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTAIList_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}
									

bool	CHTAIListTable::HT_bGetAIListRest( const int id, int* piRest )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piRest = (itTable->second)->iRest;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListMove( const int id, int* piMove )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piMove = (itTable->second)->iMove;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListStart( const int id, int* piStart )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piStart = (itTable->second)->iStart;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListArrive( const int id, int* piArrive )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piArrive = (itTable->second)->iArrive;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListDetect( const int id, int* piDetect )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDetect = (itTable->second)->iDetect;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListHelp1( const int id, int* piHelp1 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piHelp1 = (itTable->second)->iHelp1;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListLink1( const int id, int* piLink1 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLink1 = (itTable->second)->iLink1;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListGuard( const int id, int* piGuard1 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piGuard1 = (itTable->second)->iGuard1;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListBeKilled1( const int id, int* piBeKilled1 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piBeKilled1 = (itTable->second)->iBeKilled1;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListUnderAttack1( const int id, int* piUnderAttack1 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piUnderAttack1 = (itTable->second)->iUnderAttack1;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListAttack( const int id, int* piAttack )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttack = (itTable->second)->iAttack;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListHit( const int id, int* piHit )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piHit = (itTable->second)->iHit;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListMiss( const int id, int* piMiss )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piMiss = (itTable->second)->iMiss;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListBeHitted( const int id, int* piBeHitted )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piBeHitted = (itTable->second)->iBeHitted;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListDodge( const int id, int* piDodge )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDodge = (itTable->second)->iDodge;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListTrace( const int id, int* piTrace )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTrace = (itTable->second)->iTrace;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListGiveUpToTrace( const int id, int* piGiveUpToTrace )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piGiveUpToTrace = (itTable->second)->iGiveUpToTrace;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListKillEnemy( const int id, int* piKillEnemy )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piKillEnemy = (itTable->second)->iKillEnemy;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListHelp2( const int id, int* piHelp2 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piHelp2 = (itTable->second)->iHelp2;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListLink2( const int id, int* piLink2 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLink2 = (itTable->second)->iLink2;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListGuard2( const int id, int* piGuard2 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piGuard2 = (itTable->second)->iGuard2;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListBeKilled2( const int id, int* piBeKilled2 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piBeKilled2 = (itTable->second)->iBeKilled2;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListUnderAttack2( const int id, int* piUnderAttack2 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piUnderAttack2 = (itTable->second)->iUnderAttack2;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListCantTrace( const int id, int* piCantTrace )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCantTrace = (itTable->second)->iCantTrace;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListStopToAttack( const int id, int* piStopToAttack )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piStopToAttack = (itTable->second)->iStopToAttack;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListReturn( const int id, int* piReturn )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piReturn = (itTable->second)->iReturn;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListFlee( const int id, int* piFlee )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piFlee = (itTable->second)->iFlee;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListLead( const int id, int* piLead )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLead = (itTable->second)->iLead;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListPop( const int id, int* piPop )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piPop = (itTable->second)->iPop;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListDialog1( const int id, int* piDialog1 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDialog1 = (itTable->second)->iDialog1;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListDialog2( const int id, int* piDialog2 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDialog2 = (itTable->second)->iDialog2;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListDialog3( const int id, int* piDialog3 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDialog3 = (itTable->second)->iDialog3;
			return true;
		}
	}
	return false;
}

bool	CHTAIListTable::HT_bGetAIListDialog4( const int id, int* piDialog4 )
{
	HTAIList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDialog4 = (itTable->second)->iDialog4;
			return true;
		}
	}
	return false;
}


CHTActionTable::~CHTActionTable()
{
	HTAction_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTActionTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTAction* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTAction;

		HT_LOADCELL( _T("iID"),				iID,						int );
        HT_LOADCELL( _T("iSpeak"), 			pRecord->iSpeak,			int ); 
		HT_LOADCELL( _T("iGroup"), 			pRecord->iGroup,			int );  
		HT_LOADCELL( _T("iAction"), 		pRecord->iAction,			int );
		HT_LOADCELL( _T("iSkill"), 			pRecord->iSkill,			int );
		HT_LOADCELL( _T("iState"),			pRecord->iState,			int );
		HT_LOADCELL( _T("iEvent"),			pRecord->iEvent,			int );

		m_mapTable.insert( HTAction_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTActionTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTAction* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTAction;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTAction) );

		m_mapTable.insert( HTAction_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTActionTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTAction_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTAction) );

		itTable++;
	}

	return true;
}

bool	CHTActionTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTAction_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool	CHTActionTable::HT_bGetActionSpeak( const int id, int* piSpeak )
{
	HTAction_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSpeak = (itTable->second)->iSpeak;
			return true;
		}
	}
	return false;
}

bool	CHTActionTable::HT_bGetActionGroup( const int id, int* piGroup )
{
	HTAction_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piGroup = (itTable->second)->iGroup;
			return true;
		}
	}
	return false;
}

bool	CHTActionTable::HT_bGetActionAction( const int id, int* piAction )
{
	HTAction_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAction = (itTable->second)->iAction;
			return true;
		}
	}
	return false;
}

bool	CHTActionTable::HT_bGetActionSkill( const int id, int* piSkill )
{
	HTAction_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSkill = (itTable->second)->iSkill;
			return true;
		}
	}
	return false;
}

bool	CHTActionTable::HT_bGetActionState( const int id, int* piState )
{
	HTAction_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piState = (itTable->second)->iState;
			return true;
		}
	}
	return false;
}

bool	CHTActionTable::HT_bGetActionEvent( const int id, int* piEvent )
{
	HTAction_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEvent = (itTable->second)->iEvent;
			return true;
		}
	}
	return false;
}



CHTActionListTable::~CHTActionListTable()
{
	HTActionList_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTActionListTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTActionList* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTActionList;

		HT_LOADCELL( _T("iID"),				iID,						int );
        HT_LOADCELL( _T("iAction1"), 		pRecord->iAction1,			int ); 
		HT_LOADCELL( _T("iAction2"), 		pRecord->iAction2,			int );  
		HT_LOADCELL( _T("iAction3"), 		pRecord->iAction3,			int );

		m_mapTable.insert( HTActionList_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTActionListTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTActionList* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTActionList;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTActionList) );

		m_mapTable.insert( HTActionList_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTActionListTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTActionList_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTActionList) );

		itTable++;
	}

	return true;
}


bool	CHTActionListTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTActionList_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool	CHTActionListTable::HT_bGetActionListAction1( const int id, int* piAction1 )
{
	HTActionList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAction1 = (itTable->second)->iAction1;
			return true;
		}
	}
	return false;
}

bool	CHTActionListTable::HT_bGetActionListAction2( const int id, int* piAction2 )
{
	HTActionList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAction2 = (itTable->second)->iAction2;
			return true;
		}
	}
	return false;
}

bool	CHTActionListTable::HT_bGetActionListAction3( const int id, int* piAction3 )
{
	HTActionList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAction3 = (itTable->second)->iAction3;
			return true;
		}
	}
	return false;
}


CHTSpeechContentTable::~CHTSpeechContentTable()
{
	HTSpeechContent_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTSpeechContentTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTSpeechContent* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTSpeechContent;

		HT_LOADCELL( _T("iID"),				iID,						int );
        HT_LOADCELL( _T("iComment1"), 		pRecord->iComment1,			int ); 
		HT_LOADCELL( _T("iComment2"), 		pRecord->iComment2,			int );  
		HT_LOADCELL( _T("iComment3"), 		pRecord->iComment3,			int );
		HT_LOADCELL( _T("iComment4"), 		pRecord->iComment4,			int );
		HT_LOADCELL( _T("iComment5"),		pRecord->iComment5,			int );
		HT_LOADCELL( _T("iType1"),			pRecord->iType1,			int );
		HT_LOADCELL( _T("iType2"),			pRecord->iType2,			int );
		HT_LOADCELL( _T("iType3"),			pRecord->iType3,			int );
		HT_LOADCELL( _T("iType4"),			pRecord->iType4,			int );
		HT_LOADCELL( _T("iType5"),			pRecord->iType5,			int );

		m_mapTable.insert( HTSpeechContent_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTSpeechContentTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTSpeechContent* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTSpeechContent;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTSpeechContent) );

		m_mapTable.insert( HTSpeechContent_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTSpeechContentTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTSpeechContent_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTSpeechContent) );

		itTable++;
	}

	return true;
}


bool	CHTSpeechContentTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTSpeechContent_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool	CHTSpeechContentTable::HT_bGetSpeechContentComment1( const int id, int* piComment1 )
{
	HTSpeechContent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piComment1 = (itTable->second)->iComment1;
			return true;
		}
	}
	return false;
}

bool	CHTSpeechContentTable::HT_bGetSpeechContentComment2( const int id, int* piComment2 )
{
	HTSpeechContent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piComment2 = (itTable->second)->iComment2;
			return true;
		}
	}
	return false;
}

bool	CHTSpeechContentTable::HT_bGetSpeechContentComment3( const int id, int* piComment3 )
{
	HTSpeechContent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piComment3 = (itTable->second)->iComment3;
			return true;
		}
	}
	return false;
}

bool	CHTSpeechContentTable::HT_bGetSpeechContentComment4( const int id, int* piComment4 )
{
	HTSpeechContent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piComment4 = (itTable->second)->iComment4;
			return true;
		}
	}
	return false;
}

bool	CHTSpeechContentTable::HT_bGetSpeechContentComment5( const int id, int* piComment5 )
{
	HTSpeechContent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piComment5 = (itTable->second)->iComment5;
			return true;
		}
	}
	return false;
}

bool	CHTSpeechContentTable::HT_bGetSpeechContentType1( const int id, int* piType1 )
{
	HTSpeechContent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piType1 = (itTable->second)->iType1;
			return true;
		}
	}
	return false;
}

bool	CHTSpeechContentTable::HT_bGetSpeechContentType2( const int id, int* piType2 )
{
	HTSpeechContent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piType2 = (itTable->second)->iType2;
			return true;
		}
	}
	return false;
}

bool	CHTSpeechContentTable::HT_bGetSpeechContentType3( const int id, int* piType3 )
{
	HTSpeechContent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piType3 = (itTable->second)->iType3;
			return true;
		}
	}
	return false;
}

bool	CHTSpeechContentTable::HT_bGetSpeechContentType4( const int id, int* piType4 )
{
	HTSpeechContent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piType4 = (itTable->second)->iType4;
			return true;
		}
	}
	return false;
}

bool	CHTSpeechContentTable::HT_bGetSpeechContentType5( const int id, int* piType5 )
{
	HTSpeechContent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piType5 = (itTable->second)->iType5;
			return true;
		}
	}
	return false;
}


CHTSpeechCommentTable::~CHTSpeechCommentTable()
{
	HTSpeechComment_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTSpeechCommentTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTSpeechComment* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;
	char strText[eCmmt_Size];

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTSpeechComment;

		HT_LOADCELL( _T("iID"),				iID,						int );

		if( strLanguage == HT_LANGUAGE_CHINESE )
			strCell = _T("szChinese");
		else if( strLanguage == HT_LANGUAGE_PHILIPPINE )
			strCell = _T("szPhilippine");
		else if( strLanguage == HT_LANGUAGE_INDONESIA )
			strCell = _T("szIndonesian");
		else if( strLanguage == HT_LANGUAGE_JAPANESE )
			strCell = _T("szJapanese");
		else
			strCell = _T("szKorean");
		
		pXML->HT_hrGetTableValue( strTable, strCell, i, strText );
		strncpy( pRecord->szComment, strText, eCmmt_Size ) ;

		m_mapTable.insert( HTSpeechComment_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTSpeechCommentTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTSpeechComment* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTSpeechComment;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTSpeechComment) );

		m_mapTable.insert( HTSpeechComment_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTSpeechCommentTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTSpeechComment_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTSpeechComment) );

		itTable++;
	}

	return true;
}


bool	CHTSpeechCommentTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTSpeechComment_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool	CHTSpeechCommentTable::HT_bGetSpeechCommentComment( const int id, char* pComment )
{
	HTSpeechComment_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			strncpy( pComment, (itTable->second)->szComment, eCmmt_Size );
			return true;
		}
	}
	return false;
}


CHTLevelUpTable::~CHTLevelUpTable()
{
	HTLevelUp_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTLevelUpTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTLevelUp* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTLevelUp;

		HT_LOADCELL( _T("iLevel"),			iID,						int );
        HT_LOADCELL( _T("iPrana"), 			pRecord->iPrana,			int ); 

		m_mapTable.insert( HTLevelUp_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTLevelUpTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTLevelUp* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTLevelUp;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTLevelUp) );

		m_mapTable.insert( HTLevelUp_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTLevelUpTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTLevelUp_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTLevelUp) );

		itTable++;
	}

	return true;
}


bool	CHTLevelUpTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTLevelUp_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool	CHTLevelUpTable::HT_bGetLevelUpPrana( const int id, int* piPrana )
{
	HTLevelUp_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piPrana = (itTable->second)->iPrana;
			return true;
		}
	}
	return false;
}

CHTBramanPointTable::~CHTBramanPointTable()
{
	HTBramanPoint_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTBramanPointTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTBramanPoint* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTBramanPoint;

		HT_LOADCELL( _T("iCaste"),			iID,						int );
        HT_LOADCELL( _T("iPoint"), 			pRecord->iPoint,			int ); 

		m_mapTable.insert( HTBramanPoint_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTBramanPointTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTBramanPoint* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTBramanPoint;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTBramanPoint) );

		m_mapTable.insert( HTBramanPoint_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTBramanPointTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTBramanPoint_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTBramanPoint) );

		itTable++;
	}

	return true;
}


bool	CHTBramanPointTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTBramanPoint_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTBramanPointTable::HT_bGetBramanPointPoint( const int id, int* piPoint )
{
	HTBramanPoint_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piPoint = (itTable->second)->iPoint;
			return true;
		}
	}
	return false;
}


CHTAttackTypeVSArmorTypeTable::~CHTAttackTypeVSArmorTypeTable()
{
	HTAttackTypeVSArmorType_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTAttackTypeVSArmorType* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTAttackTypeVSArmorType;

		HT_LOADCELL( _T("iArmorType"),		iID,						int );
        HT_LOADCELL( _T("iDagger"), 		pRecord->iDagger,			int ); 
		HT_LOADCELL( _T("iSword"), 			pRecord->iSword,			int );  
		HT_LOADCELL( _T("iTwoHandSword"), 	pRecord->iTwoHandSword,		int );
		HT_LOADCELL( _T("iAxe"), 			pRecord->iAxe,				int );
		HT_LOADCELL( _T("iTwoHandAxe"),		pRecord->iTwoHandAxe,		int );
		HT_LOADCELL( _T("iSpear"),			pRecord->iSpear,			int );
		HT_LOADCELL( _T("iBow"),			pRecord->iBow,				int );
		HT_LOADCELL( _T("iClaw"),			pRecord->iClaw,				int );
		HT_LOADCELL( _T("iBlunt"),			pRecord->iBlunt,			int );
		HT_LOADCELL( _T("iMagic"),			pRecord->iMagic,			int );
        HT_LOADCELL( _T("iAnimal"),			pRecord->iAnimal,			int );
		HT_LOADCELL( _T("iDemon"),			pRecord->iDemon,			int );
		HT_LOADCELL( _T("iGolem"),			pRecord->iGolem,			int );
		HT_LOADCELL( _T("iUndead"),			pRecord->iUndead,			int );
		HT_LOADCELL( _T("iPlant"),			pRecord->iPlant,			int );
		HT_LOADCELL( _T("iInsect"),			pRecord->iInsect,			int );
		HT_LOADCELL( _T("iHumanoid1"),		pRecord->iHumanoid1,		int );
		HT_LOADCELL( _T("iHumanoid2"),		pRecord->iHumanoid2,		int );
		HT_LOADCELL( _T("iHumanoid3"),		pRecord->iHumanoid3,		int );
		HT_LOADCELL( _T("iHumanoid4"),		pRecord->iHumanoid4,		int );

		m_mapTable.insert( HTAttackTypeVSArmorType_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTAttackTypeVSArmorType* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTAttackTypeVSArmorType;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTAttackTypeVSArmorType) );

		m_mapTable.insert( HTAttackTypeVSArmorType_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTAttackTypeVSArmorType_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTAttackTypeVSArmorType) );

		itTable++;
	}

	return true;
}


bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTAttackTypeVSArmorType_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeDagger( const int id, int* piDagger )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDagger = (itTable->second)->iDagger;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeSword( const int id, int* piSword )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSword = (itTable->second)->iSword;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeTwoHandSword( const int id, int* piTwoHandSword )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTwoHandSword = (itTable->second)->iTwoHandSword;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeAxe( const int id, int* piAxe )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAxe = (itTable->second)->iAxe;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeTwoHandAxe( const int id, int* piTwoHandAxe )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTwoHandAxe = (itTable->second)->iTwoHandAxe;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeSpear( const int id, int* piSpear )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSpear = (itTable->second)->iSpear;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeBow( const int id, int* piBow )	
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piBow = (itTable->second)->iBow;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeClaw( const int id, int* piClaw )	
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piClaw = (itTable->second)->iClaw;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeBlunt( const int id, int* piBlunt )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piBlunt = (itTable->second)->iBlunt;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeMagic( const int id, int* piMagic )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piMagic = (itTable->second)->iMagic;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeAnimal( const int id, int* piAnimal )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAnimal = (itTable->second)->iAnimal;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeDemon( const int id, int* piDemon )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDemon = (itTable->second)->iDemon;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeGolem( const int id, int* piGolem )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piGolem = (itTable->second)->iGolem;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeUndead( const int id, int* piUndead )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piUndead = (itTable->second)->iUndead;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypePlant( const int id, int* piPlant )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piPlant = (itTable->second)->iPlant;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeInsect( const int id, int* piInsect )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piInsect = (itTable->second)->iInsect;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeHumanoid1( const int id, int* piHumanoid1 )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piHumanoid1 = (itTable->second)->iHumanoid1;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeHumanoid2( const int id, int* piHumanoid2 )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piHumanoid2 = (itTable->second)->iHumanoid2;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeHumanoid3( const int id, int* piHumanoid3 )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piHumanoid3 = (itTable->second)->iHumanoid3;
			return true;
		}
	}
	return false;
}

bool	CHTAttackTypeVSArmorTypeTable::HT_bGetAttackTypeVSArmorTypeHumanoid4( const int id, int* piHumanoid4 )
{
	HTAttackTypeVSArmorType_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piHumanoid4 = (itTable->second)->iHumanoid4;
			return true;
		}
	}
	return false;
}


CHTCoefficientByClassTable::~CHTCoefficientByClassTable()
{
	HTCoefficientByClass_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTCoefficientByClassTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTCoefficientByClass* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTCoefficientByClass;

		HT_LOADCELL( _T("iID"),				iID,						int );
        HT_LOADCELL( _T("iClass1"), 		pRecord->iClass1,			int ); 
		HT_LOADCELL( _T("iClass2"), 		pRecord->iClass2,			int );  
		HT_LOADCELL( _T("iDagger"), 		pRecord->iDagger,			int );
		HT_LOADCELL( _T("iSword"), 			pRecord->iSword,			int );
		HT_LOADCELL( _T("iTwoHandSword"),	pRecord->iTwoHandSword,		int );
		HT_LOADCELL( _T("iAxe"),			pRecord->iAxe,				int );
        HT_LOADCELL( _T("iTwoHandAxe"), 	pRecord->iTwoHandAxe,		int ); 
		HT_LOADCELL( _T("iBlunt"), 			pRecord->iBlunt,			int );  
        HT_LOADCELL( _T("iSpear"), 			pRecord->iSpear,			int ); 
		HT_LOADCELL( _T("iStaff"), 			pRecord->iStaff,			int );  
        HT_LOADCELL( _T("iClaw"), 			pRecord->iClaw,				int ); 
		HT_LOADCELL( _T("iBow"), 			pRecord->iBow,				int );  
        HT_LOADCELL( _T("iThrowing"), 		pRecord->iThrowing,			int ); 
		HT_LOADCELL( _T("iBare"), 			pRecord->iBare,				int );  
        HT_LOADCELL( _T("iShield"), 		pRecord->iShield,			int ); 
		HT_LOADCELL( _T("iHP"), 			pRecord->iHP,				int );  
        HT_LOADCELL( _T("iTP"), 			pRecord->iTP,				int ); 
		HT_LOADCELL( _T("iRecvry"), 		pRecord->iRecvry,			int );  
        HT_LOADCELL( _T("iAC"), 			pRecord->iAC,				int ); 
		HT_LOADCELL( _T("iResist"), 		pRecord->iResist,			int );  
        HT_LOADCELL( _T("iAttackRate"), 	pRecord->iAttackRate,		int ); 
		HT_LOADCELL( _T("iDodgeRate"), 		pRecord->iDodgeRate,		int ); 
        HT_LOADCELL( _T("iAttackSpeed"),	pRecord->iAttackSpeed,		int ); 
		HT_LOADCELL( _T("iCastSpeed"), 		pRecord->iCastSpeed,		int ); 
        HT_LOADCELL( _T("iDodgeSpeed"), 	pRecord->iDodgeSpeed,		int ); 

		m_mapTable.insert( HTCoefficientByClass_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTCoefficientByClassTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTCoefficientByClass* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTCoefficientByClass;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTCoefficientByClass) );

		m_mapTable.insert( HTCoefficientByClass_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTCoefficientByClassTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTCoefficientByClass_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTCoefficientByClass) );

		itTable++;
	}

	return true;
}

bool	CHTCoefficientByClassTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTCoefficientByClass_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassClass1( const int id, int* piClass1 )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piClass1 = (itTable->second)->iClass1;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassClass2( const int id, int* piClass2 )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piClass2 = (itTable->second)->iClass2;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassDagger( const int id, int* piDagger )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDagger = (itTable->second)->iDagger;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassSword( const int id, int* piSword )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSword = (itTable->second)->iSword;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassTwoHandSword( const int id, int* piTwoHandSword )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTwoHandSword = (itTable->second)->iTwoHandSword;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassAxe( const int id, int* piAxe )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAxe = (itTable->second)->iAxe;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassTwoHandAxe( const int id, int* piTwoHandAxe )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTwoHandAxe = (itTable->second)->iTwoHandAxe;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassBlunt( const int id, int* piBlunt )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piBlunt = (itTable->second)->iBlunt;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassSpear( const int id, int* piSpear )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSpear = (itTable->second)->iSpear;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassStaff( const int id, int* piStaff )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piStaff = (itTable->second)->iStaff;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassClaw( const int id, int* piClaw )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piClaw = (itTable->second)->iClaw;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassBow( const int id, int* piBow )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piBow = (itTable->second)->iBow;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassThrowing( const int id, int* piThrowing )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piThrowing = (itTable->second)->iThrowing;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassBare( const int id, int* piBare )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piBare = (itTable->second)->iBare;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassShield( const int id, int* piShield )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piShield = (itTable->second)->iShield;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassHP( const int id, int* piHP )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piHP = (itTable->second)->iHP;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassTP( const int id, int* piTP )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTP = (itTable->second)->iTP;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassRecvry( const int id, int* piRecvry )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piRecvry = (itTable->second)->iRecvry;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassAC( const int id, int* piAC )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAC = (itTable->second)->iAC;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassResist( const int id, int* piResist )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piResist = (itTable->second)->iResist;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassAttackRate( const int id, int* piAttackRate )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackRate = (itTable->second)->iAttackRate;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassDodgeRate( const int id, int* piDodgeRate )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDodgeRate = (itTable->second)->iDodgeRate;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassAttackSpeed( const int id, int* piAttackSpeed )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackSpeed = (itTable->second)->iAttackSpeed;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassCastSpeed( const int id, int* piCastSpeed )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCastSpeed = (itTable->second)->iCastSpeed;
			return true;
		}
	}
	return false;
}

bool	CHTCoefficientByClassTable::HT_bGetCoefficientByClassDodgeSpeed( const int id, int* piDodgeSpeed )
{
	HTCoefficientByClass_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDodgeSpeed = (itTable->second)->iDodgeSpeed;
			return true;
		}
	}
	return false;
}



CHTJudgeCombatTable::~CHTJudgeCombatTable()
{
	HTJudgeCombat_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTJudgeCombatTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTJudgeCombat* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTJudgeCombat;

		HT_LOADCELL( _T("iID"),						iID,							int );
        HT_LOADCELL( _T("iCriticalPCvsPC"), 		pRecord->iCriticalPCvsPC,		int ); 
		HT_LOADCELL( _T("iNormalPCvsPC"), 			pRecord->iNormalPCvsPC,			int );  
		HT_LOADCELL( _T("iMissPCvsPC"), 			pRecord->iMissPCvsPC,			int );
		HT_LOADCELL( _T("iCriticalPCvsNPC"), 		pRecord->iCriticalPCvsNPC,		int );
		HT_LOADCELL( _T("iNormalPCvsNPC"),			pRecord->iNormalPCvsNPC,		int );
		HT_LOADCELL( _T("iMissPCvsNPC"),			pRecord->iMissPCvsNPC,			int );
		HT_LOADCELL( _T("iCriticalNPCvsPC"),		pRecord->iCriticalNPCvsPC,		int );
		HT_LOADCELL( _T("iNormalNPCvsPC"),			pRecord->iNormalNPCvsPC,		int );
		HT_LOADCELL( _T("iMissNPCvsPC"),			pRecord->iMissNPCvsPC,			int );
		HT_LOADCELL( _T("iCriticalNPCvsNPC"),		pRecord->iCriticalNPCvsNPC,		int );
		HT_LOADCELL( _T("iNormalNPCvsNPC"),			pRecord->iNormalNPCvsNPC,		int );
		HT_LOADCELL( _T("iMissNPCvsNPC"),			pRecord->iMissNPCvsNPC,			int );

		m_mapTable.insert( HTJudgeCombat_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTJudgeCombatTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTJudgeCombat* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTJudgeCombat;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTJudgeCombat) );

		m_mapTable.insert( HTJudgeCombat_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTJudgeCombatTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTJudgeCombat_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTJudgeCombat) );

		itTable++;
	}

	return true;
}


bool	CHTJudgeCombatTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTJudgeCombat_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTJudgeCombatTable::HT_bGetJudgeCombatCriticalPCvsPC( const int id, int* piCriticalPCvsPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCriticalPCvsPC = (itTable->second)->iCriticalPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTJudgeCombatTable::HT_bGetJudgeCombatNormalPCvsPC( const int id, int* piNormalPCvsPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piNormalPCvsPC = (itTable->second)->iNormalPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTJudgeCombatTable::HT_bGetJudgeCombatMissPCvsPC( const int id, int* piMissPCvsPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piMissPCvsPC = (itTable->second)->iMissPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTJudgeCombatTable::HT_bGetJudgeCombatCriticalPCvsNPC( const int id, int* piCriticalPCvsNPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCriticalPCvsNPC = (itTable->second)->iCriticalPCvsNPC;
			return true;
		}
	}
	return false;
}

bool	CHTJudgeCombatTable::HT_bGetJudgeCombatNormalPCvsNPC( const int id, int* piNormalPCvsNPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piNormalPCvsNPC = (itTable->second)->iNormalPCvsNPC;
			return true;
		}
	}
	return false;
}

bool	CHTJudgeCombatTable::HT_bGetJudgeCombatMissPCvsNPC( const int id, int* piMissPCvsNPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piMissPCvsNPC = (itTable->second)->iMissPCvsNPC;
			return true;
		}
	}
	return false;
}

bool	CHTJudgeCombatTable::HT_bGetJudgeCombatCriticalNPCvsPC( const int id, int* piCriticalNPCvsPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCriticalNPCvsPC = (itTable->second)->iCriticalNPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTJudgeCombatTable::HT_bGetJudgeCombatNormalNPCvsPC( const int id, int* piNormalNPCvsPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piNormalNPCvsPC = (itTable->second)->iNormalNPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTJudgeCombatTable::HT_bGetJudgeCombatMissNPCvsPC( const int id, int* piMissNPCvsPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piMissNPCvsPC = (itTable->second)->iMissNPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTJudgeCombatTable::HT_bGetJudgeCombatCriticalNPCvsNPC( const int id, int* piCriticalNPCvsNPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCriticalNPCvsNPC = (itTable->second)->iCriticalNPCvsNPC;
			return true;
		}
	}
	return false;
}

bool	CHTJudgeCombatTable::HT_bGetJudgeCombatNormalNPCvsNPC( const int id, int* piNormalNPCvsNPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piNormalNPCvsNPC = (itTable->second)->iNormalNPCvsNPC;
			return true;
		}
	}
	return false;
}

bool	CHTJudgeCombatTable::HT_bGetJudgeCombatMissNPCvsNPC( const int id, int* piMissNPCvsNPC )
{
	HTJudgeCombat_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piMissNPCvsNPC = (itTable->second)->iMissNPCvsNPC;
			return true;
		}
	}
	return false;
}


CHTConsiderTable::~CHTConsiderTable()
{
	HTConsider_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTConsiderTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTConsider* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTConsider;

		HT_LOADCELL( _T("iLevel"),			iID,						int );
        HT_LOADCELL( _T("iDFPCvsPC"), 		pRecord->iDFPCvsPC,			int ); 
		HT_LOADCELL( _T("iRSPCvsPC"), 		pRecord->iRSPCvsPC,			int );  
		HT_LOADCELL( _T("iDGPCvsPC"), 		pRecord->iDGPCvsPC,			int );
        HT_LOADCELL( _T("iDFPCvsNPC"), 		pRecord->iDFPCvsNPC,		int ); 
		HT_LOADCELL( _T("iRSPCvsNPC"), 		pRecord->iRSPCvsNPC,		int );  
		HT_LOADCELL( _T("iDGPCvsNPC"), 		pRecord->iDGPCvsNPC,		int );
        HT_LOADCELL( _T("iDFNPCvsPC"), 		pRecord->iDFNPCvsPC,		int ); 
		HT_LOADCELL( _T("iRSNPCvsPC"), 		pRecord->iRSNPCvsPC,		int );  
		HT_LOADCELL( _T("iDGNPCvsPC"), 		pRecord->iDGNPCvsPC,		int );
        HT_LOADCELL( _T("iDFNPCvsNPC"), 	pRecord->iDFNPCvsNPC,		int ); 
		HT_LOADCELL( _T("iRSNPCvsNPC"), 	pRecord->iRSNPCvsNPC,		int );  
		HT_LOADCELL( _T("iDGNPCvsNPC"), 	pRecord->iDGNPCvsNPC,		int );

		m_mapTable.insert( HTConsider_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTConsiderTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTConsider* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTConsider;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTConsider) );

		m_mapTable.insert( HTConsider_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTConsiderTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTConsider_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTConsider) );

		itTable++;
	}

	return true;
}


bool	CHTConsiderTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTConsider_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTConsiderTable::HT_bGetConsiderDFPCvsPC( const int id, int* piDFPCvsPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDFPCvsPC = (itTable->second)->iDFPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTConsiderTable::HT_bGetConsiderRSPCvsPC( const int id, int* piRSPCvsPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piRSPCvsPC = (itTable->second)->iRSPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTConsiderTable::HT_bGetConsiderDGPCvsPC( const int id, int* piDGPCvsPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDGPCvsPC = (itTable->second)->iDGPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTConsiderTable::HT_bGetConsiderDFPCvsNPC( const int id, int* piDFPCvsNPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDFPCvsNPC = (itTable->second)->iDFPCvsNPC;
			return true;
		}
	}
	return false;
}

bool	CHTConsiderTable::HT_bGetConsiderRSPCvsNPC( const int id, int* piRSPCvsNPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piRSPCvsNPC = (itTable->second)->iRSPCvsNPC;
			return true;
		}
	}
	return false;
}

bool	CHTConsiderTable::HT_bGetConsiderDGPCvsNPC( const int id, int* piDGPCvsNPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDGPCvsNPC = (itTable->second)->iDGPCvsNPC;
			return true;
		}
	}
	return false;
}

bool	CHTConsiderTable::HT_bGetConsiderDFNPCvsPC( const int id, int* piDFNPCvsPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDFNPCvsPC = (itTable->second)->iDFNPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTConsiderTable::HT_bGetConsiderRSNPCvsPC( const int id, int* piRSNPCvsPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piRSNPCvsPC = (itTable->second)->iRSNPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTConsiderTable::HT_bGetConsiderDGNPCvsPC( const int id, int* piDGNPCvsPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDGNPCvsPC = (itTable->second)->iDGNPCvsPC;
			return true;
		}
	}
	return false;
}

bool	CHTConsiderTable::HT_bGetConsiderDFNPCvsNPC( const int id, int* piDFNPCvsNPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDFNPCvsNPC = (itTable->second)->iDFNPCvsNPC;
			return true;
		}
	}
	return false;
}

bool	CHTConsiderTable::HT_bGetConsiderRSNPCvsNPC( const int id, int* piRSNPCvsNPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piRSNPCvsNPC = (itTable->second)->iRSNPCvsNPC;
			return true;
		}
	}
	return false;
}

bool	CHTConsiderTable::HT_bGetConsiderDGNPCvsNPC( const int id, int* piDGNPCvsNPC )
{
	HTConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDGNPCvsNPC = (itTable->second)->iDGNPCvsNPC;
			return true;
		}
	}
	return false;
}


CHTRvRPKConsiderTable::~CHTRvRPKConsiderTable()
{
	HTRvRPKConsider_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTRvRPKConsiderTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTRvRPKConsider* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTRvRPKConsider;

		HT_LOADCELL( _T("iDefenderCaste"),			iID,							int );
        HT_LOADCELL( _T("iRewardBP"), 				pRecord->iRewardBP,				int ); 
		HT_LOADCELL( _T("iAttackerCaste0"), 		pRecord->iAttackerCaste0,		int );  
		HT_LOADCELL( _T("iAttackerCaste1"), 		pRecord->iAttackerCaste1,		int );  
		HT_LOADCELL( _T("iAttackerCaste2"), 		pRecord->iAttackerCaste2,		int );  
		HT_LOADCELL( _T("iAttackerCaste3"), 		pRecord->iAttackerCaste3,		int );  
		HT_LOADCELL( _T("iAttackerCaste4"), 		pRecord->iAttackerCaste4,		int );  
		HT_LOADCELL( _T("iAttackerCaste5"), 		pRecord->iAttackerCaste5,		int );  
		HT_LOADCELL( _T("iAttackerCaste6"), 		pRecord->iAttackerCaste6,		int );  
		HT_LOADCELL( _T("iAttackerCaste7"), 		pRecord->iAttackerCaste7,		int );  
		HT_LOADCELL( _T("iAttackerCaste8"), 		pRecord->iAttackerCaste8,		int );  
		HT_LOADCELL( _T("iAttackerCaste9"), 		pRecord->iAttackerCaste9,		int );  
		HT_LOADCELL( _T("iAttackerCaste10"), 		pRecord->iAttackerCaste10,		int );  
		HT_LOADCELL( _T("iAttackerCaste11"), 		pRecord->iAttackerCaste11,		int );  
		HT_LOADCELL( _T("iAttackerCaste12"), 		pRecord->iAttackerCaste12,		int );  
		HT_LOADCELL( _T("iAttackerCaste13"), 		pRecord->iAttackerCaste13,		int );  
		HT_LOADCELL( _T("iAttackerCaste14"), 		pRecord->iAttackerCaste14,		int );  
		HT_LOADCELL( _T("iAttackerCaste15"), 		pRecord->iAttackerCaste15,		int );  
		HT_LOADCELL( _T("iAttackerCaste16"), 		pRecord->iAttackerCaste16,		int );  
		HT_LOADCELL( _T("iAttackerCaste17"), 		pRecord->iAttackerCaste17,		int );  

		m_mapTable.insert( HTRvRPKConsider_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTRvRPKConsiderTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTRvRPKConsider* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTRvRPKConsider;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTRvRPKConsider) );

		m_mapTable.insert( HTRvRPKConsider_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTRvRPKConsiderTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTRvRPKConsider_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTRvRPKConsider) );

		itTable++;
	}

	return true;
}


bool	CHTRvRPKConsiderTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTRvRPKConsider_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderRewardBP( const int id, int* piRewardBP )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piRewardBP = (itTable->second)->iRewardBP;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste0( const int id, int* piAttackerCaste0 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste0 = (itTable->second)->iAttackerCaste0;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste1( const int id, int* piAttackerCaste1 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste1 = (itTable->second)->iAttackerCaste1;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste2( const int id, int* piAttackerCaste2 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste2 = (itTable->second)->iAttackerCaste2;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste3( const int id, int* piAttackerCaste3 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste3 = (itTable->second)->iAttackerCaste3;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste4( const int id, int* piAttackerCaste4 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste4 = (itTable->second)->iAttackerCaste4;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste5( const int id, int* piAttackerCaste5 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste5 = (itTable->second)->iAttackerCaste5;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste6( const int id, int* piAttackerCaste6 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste6 = (itTable->second)->iAttackerCaste6;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste7( const int id, int* piAttackerCaste7 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste7 = (itTable->second)->iAttackerCaste7;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste8( const int id, int* piAttackerCaste8 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste8 = (itTable->second)->iAttackerCaste8;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste9( const int id, int* piAttackerCaste9 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste9 = (itTable->second)->iAttackerCaste9;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste10( const int id, int* piAttackerCaste10 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste10 = (itTable->second)->iAttackerCaste10;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste11( const int id, int* piAttackerCaste11 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste11 = (itTable->second)->iAttackerCaste11;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste12( const int id, int* piAttackerCaste12 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste12 = (itTable->second)->iAttackerCaste12;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste13( const int id, int* piAttackerCaste13 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste13 = (itTable->second)->iAttackerCaste13;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste14( const int id, int* piAttackerCaste14 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste14 = (itTable->second)->iAttackerCaste14;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste15( const int id, int* piAttackerCaste15 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste15 = (itTable->second)->iAttackerCaste15;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste16( const int id, int* piAttackerCaste16 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste16 = (itTable->second)->iAttackerCaste16;
			return true;
		}
	}
	return false;
}

bool	CHTRvRPKConsiderTable::HT_bGetRvRPKConsiderAttackerCaste17( const int id, int* piAttackerCaste17 )
{
	HTRvRPKConsider_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAttackerCaste17 = (itTable->second)->iAttackerCaste17;
			return true;
		}
	}
	return false;
}


CHTEffectToleranceTable::~CHTEffectToleranceTable()
{
	HTEffectTolerance_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTEffectToleranceTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTEffectTolerance* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTEffectTolerance;

		HT_LOADCELL( _T("iID"),				iID,						int );
        HT_LOADCELL( _T("iClass1"), 		pRecord->iClass1,			int ); 
		HT_LOADCELL( _T("iClass2"), 		pRecord->iClass2,			int );  
		HT_LOADCELL( _T("iHold"), 			pRecord->iHold,				int );
		HT_LOADCELL( _T("iStun"), 			pRecord->iStun,				int );
		HT_LOADCELL( _T("iSleep"),			pRecord->iSleep,			int );
		HT_LOADCELL( _T("iBlind"),			pRecord->iBlind,			int );
		HT_LOADCELL( _T("iTerror"), 		pRecord->iTerror,			int );
		HT_LOADCELL( _T("iTaunt"), 			pRecord->iTaunt,			int );
		HT_LOADCELL( _T("iSlowMove"),		pRecord->iSlowMove,			int );
		HT_LOADCELL( _T("iSlowAttack"),		pRecord->iSlowAttack,		int );

		m_mapTable.insert( HTEffectTolerance_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTEffectToleranceTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTEffectTolerance* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTEffectTolerance;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTEffectTolerance) );

		m_mapTable.insert( HTEffectTolerance_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTEffectToleranceTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTEffectTolerance_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTEffectTolerance) );

		itTable++;
	}

	return true;
}


bool	CHTEffectToleranceTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTEffectTolerance_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTEffectToleranceTable::HT_bGetEffectToleranceClass1( const int id, int* piClass1 )
{
	HTEffectTolerance_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piClass1 = (itTable->second)->iClass1;
			return true;
		}
	}
	return false;
}

bool	CHTEffectToleranceTable::HT_bGetEffectToleranceClass2( const int id, int* piClass2 )
{
	HTEffectTolerance_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piClass2 = (itTable->second)->iClass2;
			return true;
		}
	}
	return false;
}

bool	CHTEffectToleranceTable::HT_bGetEffectToleranceHold( const int id, int* piHold )
{
	HTEffectTolerance_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piHold = (itTable->second)->iHold;
			return true;
		}
	}
	return false;
}

bool	CHTEffectToleranceTable::HT_bGetEffectToleranceStun( const int id, int* piStun )
{
	HTEffectTolerance_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piStun = (itTable->second)->iStun;
			return true;
		}
	}
	return false;
}

bool	CHTEffectToleranceTable::HT_bGetEffectToleranceSleep( const int id, int* piSleep )
{
	HTEffectTolerance_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSleep = (itTable->second)->iSleep;
			return true;
		}
	}
	return false;
}

bool	CHTEffectToleranceTable::HT_bGetEffectToleranceBlind( const int id, int* piBlind )
{
	HTEffectTolerance_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piBlind = (itTable->second)->iBlind;
			return true;
		}
	}
	return false;
}

bool	CHTEffectToleranceTable::HT_bGetEffectToleranceTerror( const int id, int* piTerror )
{
	HTEffectTolerance_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTerror = (itTable->second)->iTerror;
			return true;
		}
	}
	return false;
}

bool	CHTEffectToleranceTable::HT_bGetEffectToleranceTaunt( const int id, int* piTaunt )
{
	HTEffectTolerance_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTaunt = (itTable->second)->iTaunt;
			return true;
		}
	}
	return false;
}

bool	CHTEffectToleranceTable::HT_bGetEffectToleranceSlowMove( const int id, int* piSlowMove )
{
	HTEffectTolerance_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSlowMove = (itTable->second)->iSlowMove;
			return true;
		}
	}
	return false;
}

bool	CHTEffectToleranceTable::HT_bGetEffectToleranceSlowAttack( const int id, int* piSlowAttack )
{
	HTEffectTolerance_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSlowAttack = (itTable->second)->iSlowAttack;
			return true;
		}
	}
	return false;
}


CHTItemByLevelTable::~CHTItemByLevelTable()
{
	HTItemByLevel_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTItemByLevelTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTItemByLevel* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTItemByLevel;

		HT_LOADCELL( _T("iCategory"),		iID,						int );
        HT_LOADCELL( _T("iLvl1"), 			pRecord->iLvl1,				int ); 
		HT_LOADCELL( _T("iLvl2"), 			pRecord->iLvl2,				int );  
		HT_LOADCELL( _T("iLvl3"), 			pRecord->iLvl3,				int );
		HT_LOADCELL( _T("iLvl4"), 			pRecord->iLvl4,				int );
		HT_LOADCELL( _T("iLvl5"),			pRecord->iLvl5,				int );
		HT_LOADCELL( _T("iLvl6"),			pRecord->iLvl6,				int );
        HT_LOADCELL( _T("iLvl7"), 			pRecord->iLvl7,				int ); 
		HT_LOADCELL( _T("iLvl8"), 			pRecord->iLvl8,				int );  
		HT_LOADCELL( _T("iLvl9"), 			pRecord->iLvl9,				int );
		HT_LOADCELL( _T("iLvl10"), 			pRecord->iLvl10,			int );
		HT_LOADCELL( _T("iLvl11"),			pRecord->iLvl11,			int );
		HT_LOADCELL( _T("iLvl12"),			pRecord->iLvl12,			int );
        HT_LOADCELL( _T("iLvl13"), 			pRecord->iLvl13,			int ); 
		HT_LOADCELL( _T("iLvl14"), 			pRecord->iLvl14,			int );  
		HT_LOADCELL( _T("iLvl15"), 			pRecord->iLvl15,			int );
		HT_LOADCELL( _T("iLvl16"), 			pRecord->iLvl16,			int );
		HT_LOADCELL( _T("iLvl17"),			pRecord->iLvl17,			int );
		HT_LOADCELL( _T("iLvl18"),			pRecord->iLvl18,			int );
        HT_LOADCELL( _T("iLvl19"), 			pRecord->iLvl19,			int ); 
		HT_LOADCELL( _T("iLvl20"), 			pRecord->iLvl20,			int );  

		m_mapTable.insert( HTItemByLevel_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTItemByLevelTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTItemByLevel* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTItemByLevel;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTItemByLevel) );

		m_mapTable.insert( HTItemByLevel_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTItemByLevelTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTItemByLevel_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTItemByLevel) );

		itTable++;
	}

	return true;
}


bool	CHTItemByLevelTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTItemByLevel_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl1( const int id, int* piLvl1 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl1 = (itTable->second)->iLvl1;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl2( const int id, int* piLvl2 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl2 = (itTable->second)->iLvl2;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl3( const int id, int* piLvl3 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl3 = (itTable->second)->iLvl3;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl4( const int id, int* piLvl4 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl4 = (itTable->second)->iLvl4;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl5( const int id, int* piLvl5 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl5 = (itTable->second)->iLvl5;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl6( const int id, int* piLvl6 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl6 = (itTable->second)->iLvl6;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl7( const int id, int* piLvl7 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl7 = (itTable->second)->iLvl7;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl8( const int id, int* piLvl8 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl8 = (itTable->second)->iLvl8;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl9( const int id, int* piLvl9 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl9 = (itTable->second)->iLvl9;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl10( const int id, int* piLvl10 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl10 = (itTable->second)->iLvl10;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl11( const int id, int* piLvl11 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl11 = (itTable->second)->iLvl11;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl12( const int id, int* piLvl12 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl12 = (itTable->second)->iLvl12;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl13( const int id, int* piLvl13 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl13 = (itTable->second)->iLvl13;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl14( const int id, int* piLvl14 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl14 = (itTable->second)->iLvl14;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl15( const int id, int* piLvl15 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl15 = (itTable->second)->iLvl15;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl16( const int id, int* piLvl16 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl16 = (itTable->second)->iLvl16;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl17( const int id, int* piLvl17 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl17 = (itTable->second)->iLvl17;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl18( const int id, int* piLvl18 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl18 = (itTable->second)->iLvl18;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl19( const int id, int* piLvl19 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl19 = (itTable->second)->iLvl19;
			return true;
		}
	}
	return false;
}

bool	CHTItemByLevelTable::HT_bGetItemByLevelLvl20( const int id, int* piLvl20 )
{
	HTItemByLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl20 = (itTable->second)->iLvl20;
			return true;
		}
	}
	return false;
}


CHTItemGroupTable::~CHTItemGroupTable()
{
	HTItemGroup_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTItemGroupTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTItemGroup* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTItemGroup;

		HT_LOADCELL( _T("iID"),				iID,						int );
        HT_LOADCELL( _T("iGroup"), 			pRecord->iGroup,			int ); 
		HT_LOADCELL( _T("iItemID"), 		pRecord->iItemID,			int );  

		m_mapTable.insert( HTItemGroup_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTItemGroupTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTItemGroup* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTItemGroup;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTItemGroup) );

		m_mapTable.insert( HTItemGroup_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTItemGroupTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTItemGroup_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTItemGroup) );

		itTable++;
	}

	return true;
}


bool	CHTItemGroupTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTItemGroup_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool	CHTItemGroupTable::HT_bGetItemGroupGroup( const int id, int* piGroup )
{
	HTItemGroup_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piGroup = (itTable->second)->iGroup;
			return true;
		}
	}
	return false;
}

bool	CHTItemGroupTable::HT_bGetItemGroupItemID( const int id, int* piItemID )
{
	HTItemGroup_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piItemID = (itTable->second)->iItemID;
			return true;
		}
	}
	return false;
}


CHTItemRateByMonLevelTable::~CHTItemRateByMonLevelTable()
{
	HTItemRateByMonLevel_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTItemRateByMonLevelTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTItemRateByMonLevel* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTItemRateByMonLevel;

		HT_LOADCELL( _T("iMonLevel"),		iID,						int );
        HT_LOADCELL( _T("iLvl1"), 			pRecord->iLvl1,				int ); 
		HT_LOADCELL( _T("iLvl2"), 			pRecord->iLvl2,				int );  
		HT_LOADCELL( _T("iLvl3"), 			pRecord->iLvl3,				int );
		HT_LOADCELL( _T("iLvl4"), 			pRecord->iLvl4,				int );
		HT_LOADCELL( _T("iLvl5"),			pRecord->iLvl5,				int );
		HT_LOADCELL( _T("iLvl6"),			pRecord->iLvl6,				int );
        HT_LOADCELL( _T("iLvl7"), 			pRecord->iLvl7,				int ); 
		HT_LOADCELL( _T("iLvl8"), 			pRecord->iLvl8,				int );  
		HT_LOADCELL( _T("iLvl9"), 			pRecord->iLvl9,				int );
		HT_LOADCELL( _T("iLvl10"), 			pRecord->iLvl10,			int );
		HT_LOADCELL( _T("iLvl11"),			pRecord->iLvl11,			int );
		HT_LOADCELL( _T("iLvl12"),			pRecord->iLvl12,			int );
        HT_LOADCELL( _T("iLvl13"), 			pRecord->iLvl13,			int ); 
		HT_LOADCELL( _T("iLvl14"), 			pRecord->iLvl14,			int );  
		HT_LOADCELL( _T("iLvl15"), 			pRecord->iLvl15,			int );
		HT_LOADCELL( _T("iLvl16"), 			pRecord->iLvl16,			int );
		HT_LOADCELL( _T("iLvl17"),			pRecord->iLvl17,			int );
		HT_LOADCELL( _T("iLvl18"),			pRecord->iLvl18,			int );
        HT_LOADCELL( _T("iLvl19"), 			pRecord->iLvl19,			int ); 
		HT_LOADCELL( _T("iLvl20"), 			pRecord->iLvl20,			int );

		m_mapTable.insert( HTItemRateByMonLevel_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTItemRateByMonLevelTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTItemRateByMonLevel* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTItemRateByMonLevel;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTItemRateByMonLevel) );

		m_mapTable.insert( HTItemRateByMonLevel_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTItemRateByMonLevelTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTItemRateByMonLevel_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTItemRateByMonLevel) );

		itTable++;
	}

	return true;
}


bool	CHTItemRateByMonLevelTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTItemRateByMonLevel_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl1( const int id, int* piLvl1 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl1 = (itTable->second)->iLvl1;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl2( const int id, int* piLvl2 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl2 = (itTable->second)->iLvl2;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl3( const int id, int* piLvl3 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl3 = (itTable->second)->iLvl3;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl4( const int id, int* piLvl4 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl4 = (itTable->second)->iLvl4;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl5( const int id, int* piLvl5 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl5 = (itTable->second)->iLvl5;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl6( const int id, int* piLvl6 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl6 = (itTable->second)->iLvl6;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl7( const int id, int* piLvl7 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl7 = (itTable->second)->iLvl7;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl8( const int id, int* piLvl8 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl8 = (itTable->second)->iLvl8;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl9( const int id, int* piLvl9 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl9 = (itTable->second)->iLvl9;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl10( const int id, int* piLvl10 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl10 = (itTable->second)->iLvl10;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl11( const int id, int* piLvl11 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl11 = (itTable->second)->iLvl11;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl12( const int id, int* piLvl12 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl12 = (itTable->second)->iLvl12;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl13( const int id, int* piLvl13 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl13 = (itTable->second)->iLvl13;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl14( const int id, int* piLvl14 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl14 = (itTable->second)->iLvl14;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl15( const int id, int* piLvl15 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl15 = (itTable->second)->iLvl15;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl16( const int id, int* piLvl16 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl16 = (itTable->second)->iLvl16;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl17( const int id, int* piLvl17 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl17 = (itTable->second)->iLvl17;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl18( const int id, int* piLvl18 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl18 = (itTable->second)->iLvl18;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl19( const int id, int* piLvl19 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl19 = (itTable->second)->iLvl19;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelTable::HT_bGetItemRateByMonLevelLvl20( const int id, int* piLvl20 )
{
	HTItemRateByMonLevel_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl20 = (itTable->second)->iLvl20;
			return true;
		}
	}
	return false;
}


CHTItemRateByMonLevelForTestSrvTable::~CHTItemRateByMonLevelForTestSrvTable()
{
	HTItemRateByMonLevelForTestSrv_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTItemRateByMonLevelForTestSrv* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTItemRateByMonLevelForTestSrv;

		HT_LOADCELL( _T("iMonLevel"),		iID,						int );
        HT_LOADCELL( _T("iLvl1"), 			pRecord->iLvl1,				int ); 
		HT_LOADCELL( _T("iLvl2"), 			pRecord->iLvl2,				int );  
		HT_LOADCELL( _T("iLvl3"), 			pRecord->iLvl3,				int );
		HT_LOADCELL( _T("iLvl4"), 			pRecord->iLvl4,				int );
		HT_LOADCELL( _T("iLvl5"),			pRecord->iLvl5,				int );
		HT_LOADCELL( _T("iLvl6"),			pRecord->iLvl6,				int );
        HT_LOADCELL( _T("iLvl7"), 			pRecord->iLvl7,				int ); 
		HT_LOADCELL( _T("iLvl8"), 			pRecord->iLvl8,				int );  
		HT_LOADCELL( _T("iLvl9"), 			pRecord->iLvl9,				int );
		HT_LOADCELL( _T("iLvl10"), 			pRecord->iLvl10,			int );
		HT_LOADCELL( _T("iLvl11"),			pRecord->iLvl11,			int );
		HT_LOADCELL( _T("iLvl12"),			pRecord->iLvl12,			int );
        HT_LOADCELL( _T("iLvl13"), 			pRecord->iLvl13,			int ); 
		HT_LOADCELL( _T("iLvl14"), 			pRecord->iLvl14,			int );  
		HT_LOADCELL( _T("iLvl15"), 			pRecord->iLvl15,			int );
		HT_LOADCELL( _T("iLvl16"), 			pRecord->iLvl16,			int );
		HT_LOADCELL( _T("iLvl17"),			pRecord->iLvl17,			int );
		HT_LOADCELL( _T("iLvl18"),			pRecord->iLvl18,			int );
        HT_LOADCELL( _T("iLvl19"), 			pRecord->iLvl19,			int ); 
		HT_LOADCELL( _T("iLvl20"), 			pRecord->iLvl20,			int );  

		m_mapTable.insert( HTItemRateByMonLevelForTestSrv_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTItemRateByMonLevelForTestSrv* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTItemRateByMonLevelForTestSrv;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTItemRateByMonLevelForTestSrv) );

		m_mapTable.insert( HTItemRateByMonLevelForTestSrv_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTItemRateByMonLevelForTestSrv_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTItemRateByMonLevelForTestSrv) );

		itTable++;
	}

	return true;
}


bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl1( const int id, int* piLvl1 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl1 = (itTable->second)->iLvl1;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl2( const int id, int* piLvl2 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl2 = (itTable->second)->iLvl2;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl3( const int id, int* piLvl3 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl3 = (itTable->second)->iLvl3;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl4( const int id, int* piLvl4 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl4 = (itTable->second)->iLvl4;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl5( const int id, int* piLvl5 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl5 = (itTable->second)->iLvl5;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl6( const int id, int* piLvl6 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl6 = (itTable->second)->iLvl6;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl7( const int id, int* piLvl7 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl7 = (itTable->second)->iLvl7;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl8( const int id, int* piLvl8 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl8 = (itTable->second)->iLvl8;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl9( const int id, int* piLvl9 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl9 = (itTable->second)->iLvl9;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl10( const int id, int* piLvl10 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl10 = (itTable->second)->iLvl10;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl11( const int id, int* piLvl11 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl11 = (itTable->second)->iLvl11;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl12( const int id, int* piLvl12 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl12 = (itTable->second)->iLvl12;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl13( const int id, int* piLvl13 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl13 = (itTable->second)->iLvl13;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl14( const int id, int* piLvl14 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl14 = (itTable->second)->iLvl14;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl15( const int id, int* piLvl15 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl15 = (itTable->second)->iLvl15;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl16( const int id, int* piLvl16 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl16 = (itTable->second)->iLvl16;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl17( const int id, int* piLvl17 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl17 = (itTable->second)->iLvl17;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl18( const int id, int* piLvl18 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl18 = (itTable->second)->iLvl18;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl19( const int id, int* piLvl19 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl19 = (itTable->second)->iLvl19;
			return true;
		}
	}
	return false;
}

bool	CHTItemRateByMonLevelForTestSrvTable::HT_bGetItemRateByMonLevelForTestSrvLvl20( const int id, int* piLvl20 )
{
	HTItemRateByMonLevelForTestSrv_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piLvl20 = (itTable->second)->iLvl20;
			return true;
		}
	}
	return false;
}


CHTKalaAltarTable::~CHTKalaAltarTable()
{
	HTKalaAltar_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTKalaAltarTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTKalaAltar* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTKalaAltar;

		HT_LOADCELL( _T("iID"),				iID,					int );
        HT_LOADCELL( _T("iZone"), 			pRecord->iZone,			int ); 
		HT_LOADCELL( _T("iClan"), 			pRecord->iClan,			int );  
		HT_LOADCELL( _T("iX"), 				pRecord->iX,			int );
		HT_LOADCELL( _T("iY"), 				pRecord->iY,			int );

		m_mapTable.insert( HTKalaAltar_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTKalaAltarTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTKalaAltar* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTKalaAltar;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTKalaAltar) );

		m_mapTable.insert( HTKalaAltar_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTKalaAltarTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTKalaAltar_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTKalaAltar) );

		itTable++;
	}

	return true;
}


bool	CHTKalaAltarTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTKalaAltar_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTKalaAltarTable::HT_bGetKalaAltarZone( const int id, int* piZone )
{
	HTKalaAltar_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piZone = (itTable->second)->iZone;
			return true;
		}
	}
	return false;
}

bool	CHTKalaAltarTable::HT_bGetKalaAltarClan( const int id, int* piClan )
{
	HTKalaAltar_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piClan = (itTable->second)->iClan;
			return true;
		}
	}
	return false;
}

bool	CHTKalaAltarTable::HT_bGetKalaAltarX( const int id, int* piX )
{
	HTKalaAltar_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piX = (itTable->second)->iX;
			return true;
		}
	}
	return false;
}

bool	CHTKalaAltarTable::HT_bGetKalaAltarY( const int id, int* piY )
{
	HTKalaAltar_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piY = (itTable->second)->iY;
			return true;
		}
	}
	return false;
}


CHTKalaRewarderPositionTable::~CHTKalaRewarderPositionTable()
{
	HTKalaRewarderPosition_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTKalaRewarderPositionTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTKalaRewarderPosition* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTKalaRewarderPosition;

		HT_LOADCELL( _T("iID"),				iID,					int );
        HT_LOADCELL( _T("iZone"), 			pRecord->iZone,			int ); 
		HT_LOADCELL( _T("iNPCIndex"), 		pRecord->iNPCIndex,		int );  
		HT_LOADCELL( _T("iClan"), 			pRecord->iClan,			int );
		HT_LOADCELL( _T("iX"), 				pRecord->iX,			int );
		HT_LOADCELL( _T("iY"),				pRecord->iY,			int );

		m_mapTable.insert( HTKalaRewarderPosition_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTKalaRewarderPositionTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTKalaRewarderPosition* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTKalaRewarderPosition;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTKalaRewarderPosition) );

		m_mapTable.insert( HTKalaRewarderPosition_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTKalaRewarderPositionTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTKalaRewarderPosition_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTKalaRewarderPosition) );

		itTable++;
	}

	return true;
}


bool	CHTKalaRewarderPositionTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTKalaRewarderPosition_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool	CHTKalaRewarderPositionTable::HT_bGetRewarderPositionZone( const int id, int* piZone )
{
	HTKalaRewarderPosition_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piZone = (itTable->second)->iZone;
			return true;
		}
	}
	return false;
}

bool	CHTKalaRewarderPositionTable::HT_bGetRewarderPositionNPCIndex( const int id, int* piNPCIndex )
{
	HTKalaRewarderPosition_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piNPCIndex = (itTable->second)->iNPCIndex;
			return true;
		}
	}
	return false;
}

bool	CHTKalaRewarderPositionTable::HT_bGetRewarderPositionClan( const int id, int* piClan )
{
	HTKalaRewarderPosition_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piClan = (itTable->second)->iClan;
			return true;
		}
	}
	return false;
}

bool	CHTKalaRewarderPositionTable::HT_bGetRewarderPositionX( const int id, int* piX )
{
	HTKalaRewarderPosition_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piX = (itTable->second)->iX;
			return true;
		}
	}
	return false;
}

bool	CHTKalaRewarderPositionTable::HT_bGetRewarderPositionY( const int id, int* piY )
{
	HTKalaRewarderPosition_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piY = (itTable->second)->iY;
			return true;
		}
	}
	return false;
}


CHTRateByItemCategoryTable::~CHTRateByItemCategoryTable()
{
	HTRateByItemCategory_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTRateByItemCategoryTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTRateByItemCategory* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTRateByItemCategory;

		HT_LOADCELL( _T("iCategory"),		iID,					int );
        HT_LOADCELL( _T("iRate"), 			pRecord->iRate,			int ); 

		m_mapTable.insert( HTRateByItemCategory_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTRateByItemCategoryTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTRateByItemCategory* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTRateByItemCategory;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTRateByItemCategory) );

		m_mapTable.insert( HTRateByItemCategory_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTRateByItemCategoryTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTRateByItemCategory_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTRateByItemCategory) );

		itTable++;
	}

	return true;
}



bool	CHTRateByItemCategoryTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTRateByItemCategory_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTRateByItemCategoryTable::HT_bGetRateByItemCategoryRate( const int id, int* piRate )
{
	HTRateByItemCategory_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piRate = (itTable->second)->iRate;
			return true;
		}
	}
	return false;
}


CHTEventListTable::~CHTEventListTable()
{
	HTEventList_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTEventListTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTEventList* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTEventList;

		HT_LOADCELL( _T("iID"),				iID,						int );
        HT_LOADCELL( _T("iZone"), 			pRecord->iZone,				int ); 
		HT_LOADCELL( _T("iEventID"), 		pRecord->iEventID,			int );  
		HT_LOADCELL( _T("iTask1"), 			pRecord->iTask1,			int );
		HT_LOADCELL( _T("iTask2"), 			pRecord->iTask2,			int );
		HT_LOADCELL( _T("iTask3"), 			pRecord->iTask3,			int );
		HT_LOADCELL( _T("iTask4"), 			pRecord->iTask4,			int );
		HT_LOADCELL( _T("iTask5"), 			pRecord->iTask5,			int );
		HT_LOADCELL( _T("uiCoolDownTime"), 	pRecord->uiCoolDownTime,	unsigned int );
		HT_LOADCELL( _T("iCount"),			pRecord->iCount,			int );
		HT_LOADCELL( _T("iProceedType"),	pRecord->iProceedType,		int );
		HT_LOADCELL( _T("iDuration"),		pRecord->iDuration,			int );

		m_mapTable.insert( HTEventList_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTEventListTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTEventList* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTEventList;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTEventList) );

		m_mapTable.insert( HTEventList_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTEventListTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTEventList_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTEventList) );

		itTable++;
	}

	return true;
}


bool	CHTEventListTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTEventList_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTEventListTable::HT_bGetEventListZone( const int id, int* piZone )
{
	HTEventList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piZone = (itTable->second)->iZone;
			return true;
		}
	}
	return false;
}

bool	CHTEventListTable::HT_bGetEventListEventID( const int id, int* piEventID )
{
	HTEventList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEventID = (itTable->second)->iEventID;
			return true;
		}
	}
	return false;
}

bool	CHTEventListTable::HT_bGetEventListTask1( const int id, int* piTask1 )
{
	HTEventList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTask1 = (itTable->second)->iTask1;
			return true;
		}
	}
	return false;
}

bool	CHTEventListTable::HT_bGetEventListTask2( const int id, int* piTask2 )
{
	HTEventList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTask2 = (itTable->second)->iTask2;
			return true;
		}
	}
	return false;
}

bool	CHTEventListTable::HT_bGetEventListTask3( const int id, int* piTask3 )
{
	HTEventList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTask3 = (itTable->second)->iTask3;
			return true;
		}
	}
	return false;
}

bool	CHTEventListTable::HT_bGetEventListTask4( const int id, int* piTask4 )
{
	HTEventList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTask4 = (itTable->second)->iTask4;
			return true;
		}
	}
	return false;
}

bool	CHTEventListTable::HT_bGetEventListTask5( const int id, int* piTask5 )
{
	HTEventList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTask5 = (itTable->second)->iTask5;
			return true;
		}
	}
	return false;
}

bool	CHTEventListTable::HT_bGetEventListCoolDownTime( const int id, int* puiCoolDownTime )
{
	HTEventList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*puiCoolDownTime = (itTable->second)->uiCoolDownTime;
			return true;
		}
	}
	return false;
}

bool	CHTEventListTable::HT_bGetEventListCount( const int id, int* piCount )
{
	HTEventList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piCount = (itTable->second)->iCount;
			return true;
		}
	}
	return false;
}

bool	CHTEventListTable::HT_bGetEventListProceedType( const int id, int* piProceedType )
{
	HTEventList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piProceedType = (itTable->second)->iProceedType;
			return true;
		}
	}
	return false;
}

bool	CHTEventListTable::HT_bGetEventListDuration( const int id, int* piDuration )
{
	HTEventList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piDuration = (itTable->second)->iDuration;
			return true;
		}
	}
	return false;
}


CHTTaskListTable::~CHTTaskListTable()
{
	HTTaskList_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTTaskListTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTTaskList* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTTaskList;

		HT_LOADCELL( _T("iID"),					iID,						int );
        HT_LOADCELL( _T("iZone"), 				pRecord->iZoneID,			int ); 
		HT_LOADCELL( _T("iTaskID"), 			pRecord->iTaskID,			int );  
		HT_LOADCELL( _T("iActionID"), 			pRecord->iActionID,			int );
		HT_LOADCELL( _T("iParam1"), 			pRecord->iParam1,			int );
		HT_LOADCELL( _T("iParam2"), 			pRecord->iParam2,			int );
		HT_LOADCELL( _T("iParam3"), 			pRecord->iParam3,			int );
		HT_LOADCELL( _T("iParam4"), 			pRecord->iParam4,			int );
		HT_LOADCELL( _T("iParam5"), 			pRecord->iParam5,			int );
		HT_LOADCELL( _T("iParam6"), 			pRecord->iParam6,			int );

		m_mapTable.insert( HTTaskList_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTTaskListTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTTaskList* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTTaskList;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTTaskList) );

		m_mapTable.insert( HTTaskList_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTTaskListTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTTaskList_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTTaskList) );

		itTable++;
	}

	return true;
}


bool	CHTTaskListTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTTaskList_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTTaskListTable::HT_bGetTaskListZone( const int id, int* piZone )
{
	HTTaskList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piZone = (itTable->second)->iZoneID;
			return true;
		}
	}
	return false;
}

bool	CHTTaskListTable::HT_bGetTaskListTaskID( const int id, int* piTaskID )
{
	HTTaskList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTaskID = (itTable->second)->iTaskID;
			return true;
		}
	}
	return false;
}

bool	CHTTaskListTable::HT_bGetTaskListActionID( const int id, int* piActionID )
{
	HTTaskList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piActionID = (itTable->second)->iActionID;
			return true;
		}
	}
	return false;
}

bool	CHTTaskListTable::HT_bGetTaskListParam1( const int id, int* piParam1 )
{
	HTTaskList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam1 = (itTable->second)->iParam1;
			return true;
		}
	}
	return false;
}

bool	CHTTaskListTable::HT_bGetTaskListParam2( const int id, int* piParam2 )
{
	HTTaskList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam2 = (itTable->second)->iParam2;
			return true;
		}
	}
	return false;
}

bool	CHTTaskListTable::HT_bGetTaskListParam3( const int id, int* piParam3 )
{
	HTTaskList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam3 = (itTable->second)->iParam3;
			return true;
		}
	}
	return false;
}

bool	CHTTaskListTable::HT_bGetTaskListParam4( const int id, int* piParam4 )
{
	HTTaskList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam4 = (itTable->second)->iParam4;
			return true;
		}
	}
	return false;
}

bool	CHTTaskListTable::HT_bGetTaskListParam5( const int id, int* piParam5 )
{
	HTTaskList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam5 = (itTable->second)->iParam5;
			return true;
		}
	}
	return false;
}


bool	CHTTaskListTable::HT_bGetTaskListParam6( const int id, int* piParam6 )
{
	HTTaskList_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam6 = (itTable->second)->iParam6;
			return true;
		}
	}
	return false;
}



CHTEventScheduleTable::~CHTEventScheduleTable()
{
	HTEventSchedule_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTEventScheduleTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTEventSchedule* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTEventSchedule;

		HT_LOADCELL( _T("iID"),				iID,						int );
        HT_LOADCELL( _T("iZone"), 			pRecord->iZoneID,			int ); 
		HT_LOADCELL( _T("iMin"), 			pRecord->iMin,				int );  
		HT_LOADCELL( _T("iSec"), 			pRecord->iSec,				int );
		HT_LOADCELL( _T("iEvent"), 			pRecord->iEvent,			int );

		m_mapTable.insert( HTEventSchedule_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTEventScheduleTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTEventSchedule* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTEventSchedule;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTEventSchedule) );

		m_mapTable.insert( HTEventSchedule_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTEventScheduleTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTEventSchedule_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTEventSchedule) );

		itTable++;
	}

	return true;
}


bool	CHTEventScheduleTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTEventSchedule_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTEventScheduleTable::HT_bGetEventScheduleZone( const int id, int* piZone )
{
	HTEventSchedule_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piZone = (itTable->second)->iZoneID;
			return true;
		}
	}
	return false;
}

bool	CHTEventScheduleTable::HT_bGetEventScheduleMin( const int id, int* piMin )
{
	HTEventSchedule_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piMin = (itTable->second)->iMin;
			return true;
		}
	}
	return false;
}

bool	CHTEventScheduleTable::HT_bGetEventScheduleSec( const int id, int* piSec )
{
	HTEventSchedule_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piSec = (itTable->second)->iSec;
			return true;
		}
	}
	return false;
}

bool	CHTEventScheduleTable::HT_bGetEventScheduleEvent( const int id, int* piEvent )
{
	HTEventSchedule_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEvent = (itTable->second)->iEvent;
			return true;
		}
	}
	return false;
}



CHTGameEventTable::~CHTGameEventTable()
{
	HTGameEvent_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTGameEventTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTGameEvent* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iID, iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{
		pRecord = new HTGameEvent;

		HT_LOADCELL( _T("iID"),					iID,						int );
		HT_LOADCELL( _T("iEventID"), 			pRecord->iEventID,			int ); 
		HT_LOADCELL( _T("iType"), 				pRecord->iType,				int ); 
		HT_LOADCELL( _T("iTarget"), 			pRecord->iTarget,			int ); 
		HT_LOADCELL( _T("iZone"), 				pRecord->iZone,				int ); 
		HT_LOADCELL( _T("iAction1"), 			pRecord->iAction1,			int ); 
		HT_LOADCELL( _T("iParam11"), 			pRecord->iParam11,			int );  
		HT_LOADCELL( _T("iParam12"), 			pRecord->iParam12,			int );
		HT_LOADCELL( _T("iAction2"), 			pRecord->iAction2,			int ); 
		HT_LOADCELL( _T("iParam21"), 			pRecord->iParam21,			int );  
		HT_LOADCELL( _T("iParam22"), 			pRecord->iParam22,			int );
		HT_LOADCELL( _T("iAction3"), 			pRecord->iAction3,			int ); 
		HT_LOADCELL( _T("iParam31"), 			pRecord->iParam31,			int );  
		HT_LOADCELL( _T("iParam32"), 			pRecord->iParam32,			int );
		HT_LOADCELL( _T("iAction4"), 			pRecord->iAction4,			int ); 
		HT_LOADCELL( _T("iParam41"), 			pRecord->iParam41,			int );  
		HT_LOADCELL( _T("iParam42"), 			pRecord->iParam42,			int );
		HT_LOADCELL( _T("iAction5"), 			pRecord->iAction5,			int ); 
		HT_LOADCELL( _T("iParam51"), 			pRecord->iParam51,			int );  
		HT_LOADCELL( _T("iParam52"), 			pRecord->iParam52,			int );
		HT_LOADCELL( _T("iAction6"), 			pRecord->iAction6,			int ); 
		HT_LOADCELL( _T("iParam61"), 			pRecord->iParam61,			int );  
		HT_LOADCELL( _T("iParam62"), 			pRecord->iParam62,			int );

		m_mapTable.insert( HTGameEvent_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTGameEventTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTGameEvent* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTGameEvent;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTGameEvent) );

		m_mapTable.insert( HTGameEvent_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTGameEventTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTGameEvent_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTGameEvent) );

		itTable++;
	}

	return true;
}


bool	CHTGameEventTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTGameEvent_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}

bool	CHTGameEventTable::HT_bGetGameEventID( const int id, int* piEventID)
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piEventID = (itTable->second)->iEventID;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventType   ( const int id, int* piType)
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piType = (itTable->second)->iType;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventTarget ( const int id, int* piTarget)
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piTarget = (itTable->second)->iTarget;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventZone   ( const int id, int* piZone )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piZone = (itTable->second)->iZone;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventAction1( const int id, int* piAction)
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAction = (itTable->second)->iAction1;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam11( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam11;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam12( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam12;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventAction2( const int id, int* piAction)
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAction = (itTable->second)->iAction2;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam21( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam21;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam22( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam22;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventAction3( const int id, int* piAction)
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAction = (itTable->second)->iAction3;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam31( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam31;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam32( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam32;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventAction4( const int id, int* piAction)
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAction = (itTable->second)->iAction4;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam41( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam41;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam42( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam42;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventAction5( const int id, int* piAction)
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAction = (itTable->second)->iAction5;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam51( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam51;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam52( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam52;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventAction6( const int id, int* piAction)
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piAction = (itTable->second)->iAction6;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam61( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam61;
			return true;
		}
	}
	return false;
}

bool	CHTGameEventTable::HT_bGetGameEventParam62( const int id, int* piParam )
{
	HTGameEvent_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iParam62;
			return true;
		}
	}
	return false;
}




CHTSetItemTable::~CHTSetItemTable()
{
	HTSetItem_It it = m_mapTable.begin();
	while ( it != m_mapTable.end() )
	{
		if ( it->second ) delete (it->second);
		it = m_mapTable.erase( it );
	}
}

bool	CHTSetItemTable::HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage )
{
	if ( !pXML || !pXML->HT_isThereTable( strTable ) ) return false;

	HTSetItem* pRecord = 0 ;

	//HTMonsterParam* pRecord = 0;
	int iTemp;
	CHTString strCell;

	m_nItems = pXML->HT_nGetTableRowCount( strTable );
	--m_nItems; // 제일 윗줄은 뺀다.

	for ( unsigned int i = 0; i < m_nItems; ++i )
	{// iID	iHelmet	iNecklace	iArmor	iBelt	iWeapon	iShield	iBoots	iGloves	iPants	iEffectItem	iEffectItem2
		pRecord = new HTSetItem;

		HT_LOADCELL( _T("iID"),					pRecord->iID,				int );
		HT_LOADCELL( _T("iHelmet"),				pRecord->iHelmet,			int ); 
		HT_LOADCELL( _T("iNecklace"),			pRecord->iNecklace,			int ); 
		HT_LOADCELL( _T("iArmor"), 				pRecord->iArmor,			int ); 
		HT_LOADCELL( _T("iBelt"),				pRecord->iBelt,				int ); 
		HT_LOADCELL( _T("iWeapon"), 			pRecord->iWeapon,			int ); 
		HT_LOADCELL( _T("iShield"), 			pRecord->iShield,			int ); 
		HT_LOADCELL( _T("iBoots"), 				pRecord->iBoots,			int ); 
		HT_LOADCELL( _T("iGloves"), 			pRecord->iGloves,			int ); 
		HT_LOADCELL( _T("iPants"), 				pRecord->iPants,			int ); 
		HT_LOADCELL( _T("iEffectItem"), 		pRecord->iEffectItem,		int ); 
		HT_LOADCELL( _T("iEffectItem2"), 		pRecord->iEffectItem2,		int ); 
#ifndef __BEFORE_SET_ITEM_EXPANDED__
		HT_LOADCELL( _T("iEffectItem3"), 		pRecord->iEffectItem3,		int ); 
#endif

		m_mapTable.insert( HTSetItem_Value( pRecord->iID, pRecord ) );
	}

	return true;
}

bool	CHTSetItemTable::HT_bLoad( CHTFile* pFile )
{
	if ( !pFile ) return false;

	int iRecordCount;
	pFile->HT_bRead( &iRecordCount );
	m_nItems = iRecordCount;

	HTSetItem* pRecord = NULL;
	int iID;
	for ( HTuint i = 0; i < m_nItems; i++ )
	{
		pRecord = new HTSetItem;

		pFile->HT_bRead( &iID );
		pFile->HT_bRead( pRecord, sizeof(HTSetItem) );

		m_mapTable.insert( HTSetItem_Value( iID, pRecord ) );
	}

	return true;
}

bool	CHTSetItemTable::HT_bSave( CHTFile* pFile )
{
	if ( !pFile ) return false;

	HTSetItem_It itTable;
	itTable = m_mapTable.begin();

	int iRecordCount;
	iRecordCount = (int)m_mapTable.size();
	pFile->HT_bWrite( iRecordCount );

	int iID;
	while ( itTable != m_mapTable.end() )
	{
		iID = itTable->first;
		pFile->HT_bWrite( iID );
		pFile->HT_bWrite( itTable->second, sizeof(HTSetItem) );

		itTable++;
	}

	return true;
}


bool	CHTSetItemTable::HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel )
{
	std::vector<HTIDLevel2>& vectorIDLevel = *pvectorIDLevel;
	vectorIDLevel.clear();

	HTSetItem_It itTable = m_mapTable.begin();

	while ( itTable != m_mapTable.end() )
	{
		HTIDLevel2 oIDLevel;
		oIDLevel.iID = itTable->first;
		oIDLevel.byteLevel = 0;
		vectorIDLevel.push_back( std::vector<HTIDLevel2>::value_type( oIDLevel ) );

		++itTable;
	}

	return true;
}


bool	CHTSetItemTable::HT_bGetSetItemID( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iID;
			return true;
		}
	}
	return false;
}


bool	CHTSetItemTable::HT_bGetSetItemHelmet( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iHelmet;
			return true;
		}
	}
	return false;
}


bool	CHTSetItemTable::HT_bGetSetItemNecklace( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iNecklace;
			return true;
		}
	}
	return false;
}


bool	CHTSetItemTable::HT_bGetSetItemArmor( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iArmor;
			return true;
		}
	}
	return false;
}


bool	CHTSetItemTable::HT_bGetSetItemBelt( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iBelt;
			return true;
		}
	}
	return false;
}

bool	CHTSetItemTable::HT_bGetSetItemWeapon( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iWeapon;
			return true;
		}
	}
	return false;
}

bool	CHTSetItemTable::HT_bGetSetItemShield( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iShield;
			return true;
		}
	}
	return false;
}


bool	CHTSetItemTable::HT_bGetSetItemPants( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iPants;
			return true;
		}
	}
	return false;
}


bool	CHTSetItemTable::HT_bGetSetItemGloves( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iGloves;
			return true;
		}
	}
	return false;
}


bool	CHTSetItemTable::HT_bGetSetItemBoots( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iBoots;
			return true;
		}
	}
	return false;
}


bool	CHTSetItemTable::HT_bGetSetItemEffectItem( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iEffectItem;
			return true;
		}
	}
	return false;
}


bool	CHTSetItemTable::HT_bGetSetItemEffectItem2( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iEffectItem2;
			return true;
		}
	}
	return false;
}

#ifndef __BEFORE_SET_ITEM_EXPANDED__
bool	CHTSetItemTable::HT_bGetSetItemEffectItem3( const int id, int* piParam )
{
	HTSetItem_It itTable = m_mapTable.find( id );
	if ( itTable != m_mapTable.end() )
	{
		if ( itTable->second )
		{
			*piParam = (itTable->second)->iEffectItem3;
			return true;
		}
	}
	return false;
}
#endif

