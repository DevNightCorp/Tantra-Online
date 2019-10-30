#ifndef _HTSERVERSETTING_H_
#define _HTSERVERSETTING_H_

#include "BaseDef.h"
#include "HT.h"
#include "HTString.h"

class CHTXMLParser;
class CHTFile ;

struct HTIDLevel2
{
	HTIDLevel2();
	~HTIDLevel2();
	HTIDLevel2( const HTIDLevel2& oIDLevel );
	int		iID;
	byte	byteLevel;
};



class CHTBaseSSettingTable
{
public:
	CHTBaseSSettingTable();
	~CHTBaseSSettingTable();

	virtual bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) = 0;
	virtual bool	HT_bLoad( CHTFile* pFile ) = 0;
	virtual bool	HT_bSave( CHTFile* pFile ) = 0;

	// 여기서부터 로드하는 각 항목당 로드하는 함수를 짜 넣는다. 다음은 예제-_- 이다.
	// virtual bool		HT_bGetItemLevel( const int id, byte* pbyteLevel );
	// virtual bool		HT_bGetItemLevel( byte* pbyteLevel );

protected:
	unsigned short	m_nItems;
};

// 아래는 예제다. 이와 같이 위의 Base 클래스에서 상속 받는다.
//class CHTMonsterTalk : public CHTBaseSSettingTable
//{
//};

// 총 25개의 sheet로 구분될 것이다. 따라서 25개의 세분된 class로 나눠질 것이다.
class CHTAIListTable : public CHTBaseSSettingTable
{
public :
	CHTAIListTable() : m_pParam(NULL) {} ;
	~CHTAIListTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;
	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public:
    // Item with ID
	bool	HT_bGetAIListRest( const int id, int* piRest ) ;
	bool	HT_bGetAIListMove( const int id, int* piMove ) ;
	bool	HT_bGetAIListStart( const int id, int* piStart ) ;
	bool	HT_bGetAIListArrive( const int id, int* piArrive ) ;
	bool	HT_bGetAIListDetect( const int id, int* piDetect ) ;
	bool	HT_bGetAIListHelp1( const int id, int* piHelp1 ) ;
	bool	HT_bGetAIListLink1( const int id, int* piLink1 ) ;
	bool	HT_bGetAIListGuard( const int id, int* piGuard ) ;
	bool	HT_bGetAIListBeKilled1( const int id, int* piBeKilled1 ) ;
	bool	HT_bGetAIListUnderAttack1( const int id, int* piUnderAttack1 ) ;
	bool	HT_bGetAIListAttack( const int id, int* piAttack ) ;
	bool	HT_bGetAIListHit( const int id, int* piHit ) ;
	bool	HT_bGetAIListMiss( const int id, int* piMiss ) ;
	bool	HT_bGetAIListBeHitted( const int id, int* piBeHitted ) ;
	bool	HT_bGetAIListDodge( const int id, int* piDodge ) ;
	bool	HT_bGetAIListTrace( const int id, int* piTrace ) ;
	bool	HT_bGetAIListGiveUpToTrace( const int id, int* piGiveUpToTrace ) ;
	bool	HT_bGetAIListKillEnemy( const int id, int* piKillEnemy ) ;
	bool	HT_bGetAIListHelp2( const int id, int* piHelp2 ) ;
	bool	HT_bGetAIListLink2( const int id, int* piLink2 ) ;
	bool	HT_bGetAIListGuard2( const int id, int* piGuard2 ) ;
	bool	HT_bGetAIListBeKilled2( const int id, int* piBeKilled2 ) ;
	bool	HT_bGetAIListUnderAttack2( const int id, int* piUnderAttack2 ) ;
	bool	HT_bGetAIListCantTrace( const int id, int* piCantTrace ) ;
	bool	HT_bGetAIListStopToAttack( const int id, int* piStopToAttack ) ;
	bool	HT_bGetAIListReturn( const int id, int* piReturn ) ;
	bool	HT_bGetAIListFlee( const int id, int* piFlee ) ;
	bool	HT_bGetAIListLead( const int id, int* piLead ) ;
	bool	HT_bGetAIListPop( const int id, int* piPop ) ;
	bool	HT_bGetAIListDialog1( const int id, int* piDialog1 ) ;
	bool	HT_bGetAIListDialog2( const int id, int* piDialog2 ) ;
	bool	HT_bGetAIListDialog3( const int id, int* piDialog3 ) ;
	bool	HT_bGetAIListDialog4( const int id, int* piDialog4 ) ;

	// Item without ID
	bool	HT_bGetAIListRest( int* piRest ) ;
	bool	HT_bGetAIListMove( int* piMove ) ;
	bool	HT_bGetAIListStart( int* piStart ) ;
	bool	HT_bGetAIListArrive( int* piArrive ) ;
	bool	HT_bGetAIListDetect( int* piDetect ) ;
	bool	HT_bGetAIListHelp1( int* piHelp1 ) ;
	bool	HT_bGetAIListLink1( int* piLink1 ) ;
	bool	HT_bGetAIListGuard( int* piGuard ) ;
	bool	HT_bGetAIListBeKilled1( int* piBeKilled1 ) ;
	bool	HT_bGetAIListUnderAttack1( int* piUnderAttack1 ) ;
	bool	HT_bGetAIListAttack( int* piAttack ) ;
	bool	HT_bGetAIListHit( int* piHit ) ;
	bool	HT_bGetAIListMiss( int* piMiss ) ;
	bool	HT_bGetAIListBeHitted( int* piBeHitted ) ;
	bool	HT_bGetAIListDodge( int* piDodge ) ;
	bool	HT_bGetAIListTrace( int* piTrace ) ;
	bool	HT_bGetAIListGiveUpToTrace( int* piGiveUpToTrace ) ;
	bool	HT_bGetAIListKillEnemy( int* piKillEnemy ) ;
	bool	HT_bGetAIListHelp2( int* piHelp2 ) ;
	bool	HT_bGetAIListLink2( int* piLink2 ) ;
	bool	HT_bGetAIListGuard2( int* piGuard2 ) ;
	bool	HT_bGetAIListBeKilled2( int* piBeKilled2 ) ;
	bool	HT_bGetAIListUnderAttack2( int* piUnderAttack2 ) ;
	bool	HT_bGetAIListCantTrace( int* piCantTrace ) ;
	bool	HT_bGetAIListStopToAttack( int* piStopToAttack ) ;
	bool	HT_bGetAIListReturn( int* piReturn ) ;
	bool	HT_bGetAIListFlee( int* piFlee ) ;
	bool	HT_bGetAIListLead( int* piLead ) ;
	bool	HT_bGetAIListPop( int* piPop ) ;
	bool	HT_bGetAIListDialog1( int* piDialog1 ) ;
	bool	HT_bGetAIListDialog2( int* piDialog2 ) ;
	bool	HT_bGetAIListDialog3( int* piDialog3 ) ;
	bool	HT_bGetAIListDialog4( int* piDialog4 ) ;

private :
	struct HTAIList
	{
		//int iID ; // id
		int iRest ;
		int iMove ;
		int iStart ;
		int iArrive ;
		int iDetect ;
		int iHelp1 ;
		int iLink1 ;
		int iGuard1 ;
		int iBeKilled1 ;
		int iUnderAttack1 ;
		int iAttack ;
		int iHit ;
		int iMiss ;
		int iBeHitted ;
		int iDodge ;
		int iTrace ;
		int iGiveUpToTrace ;
		int iKillEnemy ;
		int iHelp2 ;
		int iLink2 ;
		int iGuard2 ;
		int iBeKilled2 ;
		int iUnderAttack2 ;
		int iCantTrace ;
		int iStopToAttack ;
		int iReturn ;
		int iFlee ;
		int iLead ;
		int iPop ;
		int iDialog1 ;
		int iDialog2 ;
		int iDialog3 ;
		int iDialog4 ;
	};

	typedef std::map<int,HTAIList*>				HTAIList_Map;
	typedef std::map<int,HTAIList*>::value_type	HTAIList_Value;
	typedef std::map<int,HTAIList*>::iterator	HTAIList_It;

	HTAIList_Map				m_mapTable;
	HTAIList*					m_pParam;
};



class CHTActionTable : public CHTBaseSSettingTable
{
public :
	CHTActionTable() : m_pParam(NULL) {} ;
	~CHTActionTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetActionSpeak( const int id, int* piSpeak ) ;
	bool	HT_bGetActionGroup( const int id, int* piGroup ) ;
	bool	HT_bGetActionAction( const int id, int* piAction ) ;
	bool	HT_bGetActionSkill( const int id, int* piSkill ) ;
	bool	HT_bGetActionState( const int id, int* piState ) ;
	bool	HT_bGetActionEvent( const int id, int* piEvent ) ;
	// Item without ID
	bool	HT_bGetActionRest( int* piRest ) ;
	bool	HT_bGetActionGroup( int* piGroup ) ;
	bool	HT_bGetActionAction( int* piAction ) ;
	bool	HT_bGetActionSkill( int* piSkill ) ;
	bool	HT_bGetActionState( int* piState ) ;
	bool	HT_bGetActionEvent( int* piEvent ) ;

private :
	struct HTAction
	{
		//int iID ;
		int iSpeak ;
		int iGroup ;
		int iAction ;
		int iSkill ;
		int iState ;
		int iEvent ;
	};

	typedef std::map<int,HTAction*>				HTAction_Map;
	typedef std::map<int,HTAction*>::value_type	HTAction_Value;
	typedef std::map<int,HTAction*>::iterator	HTAction_It;

	HTAction_Map				m_mapTable;
	HTAction*					m_pParam;
};



class CHTActionListTable : public CHTBaseSSettingTable
{
public :
	CHTActionListTable() : m_pParam(NULL) {} ;
	~CHTActionListTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetActionListAction1( const int id, int* piAction1 ) ;
	bool	HT_bGetActionListAction2( const int id, int* piAction2 ) ;
	bool	HT_bGetActionListAction3( const int id, int* piAction3 ) ;
    // Item without ID
	bool	HT_bGetActionListAction1( int* piAction1 ) ;
	bool	HT_bGetActionListAction2( int* piAction2 ) ;
	bool	HT_bGetActionListAction3( int* piAction3 ) ;

private :
	struct HTActionList
	{
		//int iID ;
		int iAction1 ;
		int iAction2 ;
		int iAction3 ;
	};

	typedef std::map<int,HTActionList*>				HTActionList_Map;
	typedef std::map<int,HTActionList*>::value_type	HTActionList_Value;
	typedef std::map<int,HTActionList*>::iterator	HTActionList_It;

	HTActionList_Map				m_mapTable;
	HTActionList*					m_pParam;
};



class CHTSpeechContentTable : public CHTBaseSSettingTable
{
public :
	CHTSpeechContentTable() : m_pParam(NULL) {} ;
	~CHTSpeechContentTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetSpeechContentComment1( const int id, int* piComment1 ) ;
	bool	HT_bGetSpeechContentComment2( const int id, int* piComment2 ) ;
	bool	HT_bGetSpeechContentComment3( const int id, int* piComment3 ) ;
	bool	HT_bGetSpeechContentComment4( const int id, int* piComment4 ) ;
	bool	HT_bGetSpeechContentComment5( const int id, int* piComment5 ) ;
	bool	HT_bGetSpeechContentType1( const int id, int* piType1 ) ;
	bool	HT_bGetSpeechContentType2( const int id, int* piType2 ) ;
	bool	HT_bGetSpeechContentType3( const int id, int* piType3 ) ;
	bool	HT_bGetSpeechContentType4( const int id, int* piType4 ) ;
	bool	HT_bGetSpeechContentType5( const int id, int* piType5 ) ;

    // Item without ID
	bool	HT_bGetSpeechContentComment1( int* piComment1 ) ;
	bool	HT_bGetSpeechContentComment2( int* piComment2 ) ;
	bool	HT_bGetSpeechContentComment3( int* piComment3 ) ;
	bool	HT_bGetSpeechContentComment4( int* piComment4 ) ;
	bool	HT_bGetSpeechContentComment5( int* piComment5 ) ;
	bool	HT_bGetSpeechContentType1( int* piType1 ) ;
	bool	HT_bGetSpeechContentType2( int* piType2 ) ;
	bool	HT_bGetSpeechContentType3( int* piType3 ) ;
	bool	HT_bGetSpeechContentType4( int* piType4 ) ;
	bool	HT_bGetSpeechContentType5( int* piType5 ) ;

private :
	struct HTSpeechContent
	{
		//int iID ; // id
		int iComment1 ;
		int iComment2 ;
		int iComment3 ;
		int iComment4 ;
		int iComment5 ;
		int iType1 ;
		int iType2 ;
		int iType3 ;
		int iType4 ;
		int iType5 ;
	};

	typedef std::map<int,HTSpeechContent*>				HTSpeechContent_Map;
	typedef std::map<int,HTSpeechContent*>::value_type	HTSpeechContent_Value;
	typedef std::map<int,HTSpeechContent*>::iterator	HTSpeechContent_It;

	HTSpeechContent_Map				m_mapTable;
	HTSpeechContent*				m_pParam;
};



class CHTSpeechCommentTable : public CHTBaseSSettingTable
{
public :
	CHTSpeechCommentTable() : m_pParam(NULL) {} ;
	~CHTSpeechCommentTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetSpeechCommentComment( const int id, char* pComment ) ;
    // Item without ID

private :
	enum { eCmmt_Size = 101, } ;
	struct HTSpeechComment
	{
		//int iID ; // id
		char szComment[eCmmt_Size] ;
	};

	typedef std::map<int,HTSpeechComment*>				HTSpeechComment_Map;
	typedef std::map<int,HTSpeechComment*>::value_type	HTSpeechComment_Value;
	typedef std::map<int,HTSpeechComment*>::iterator	HTSpeechComment_It;

	HTSpeechComment_Map				m_mapTable;
	HTSpeechComment*				m_pParam;
};



class CHTLevelUpTable : public CHTBaseSSettingTable
{
public :
	CHTLevelUpTable() : m_pParam(NULL) {} ;
	~CHTLevelUpTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetLevelUpPrana( const int id, int* piPrana ) ;

    // Item without ID
	bool	HT_bGetLevelUpPrana( int* piPrana ) ;

private :
	struct HTLevelUp
	{
		//int iLevel ;
		int iPrana ;
	};

	typedef std::map<int,HTLevelUp*>				HTLevelUp_Map;
	typedef std::map<int,HTLevelUp*>::value_type	HTLevelUp_Value;
	typedef std::map<int,HTLevelUp*>::iterator		HTLevelUp_It;

	HTLevelUp_Map				m_mapTable;
	HTLevelUp*					m_pParam;
};



class CHTBramanPointTable : public CHTBaseSSettingTable
{
public :
	CHTBramanPointTable() : m_pParam(NULL) {} ;
	~CHTBramanPointTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	//bool	HT_bGetBramanPointCaste( const int id, int* piCaste ) ;
	bool	HT_bGetBramanPointPoint( const int id, int* piPoint ) ;
    // Item without ID
	//bool	HT_bGetBramanPointCaste( int* piCaste ) ;
	bool	HT_bGetBramanPointPoint( int* piPoint ) ;


private :
	struct HTBramanPoint
	{
		//int iCaste ; // id
		int iPoint ;
	};

	typedef std::map<int,HTBramanPoint*>				HTBramanPoint_Map;
	typedef std::map<int,HTBramanPoint*>::value_type	HTBramanPoint_Value;
	typedef std::map<int,HTBramanPoint*>::iterator		HTBramanPoint_It;

	HTBramanPoint_Map				m_mapTable;
	HTBramanPoint*					m_pParam;
};



class CHTAttackTypeVSArmorTypeTable : public CHTBaseSSettingTable
{
public :
	CHTAttackTypeVSArmorTypeTable() : m_pParam(NULL) {} ;
	~CHTAttackTypeVSArmorTypeTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	//bool	HT_bGetAttackTypeVSArmorTypeArmor( const int id, int* piArmor ) ;
	bool	HT_bGetAttackTypeVSArmorTypeDagger( const int id, int* piDagger ) ;
	bool	HT_bGetAttackTypeVSArmorTypeSword( const int id, int* piSword ) ;
	bool	HT_bGetAttackTypeVSArmorTypeTwoHandSword( const int id, int* piTwoHandSword ) ;
	bool	HT_bGetAttackTypeVSArmorTypeAxe( const int id, int* piAxe ) ;
	bool	HT_bGetAttackTypeVSArmorTypeTwoHandAxe( const int id, int* piTwoHandAxe ) ;
	bool	HT_bGetAttackTypeVSArmorTypeSpear( const int id, int* piSpear ) ;
	bool	HT_bGetAttackTypeVSArmorTypeBow( const int id, int* piBow ) ;	
	bool	HT_bGetAttackTypeVSArmorTypeClaw( const int id, int* piClaw ) ;	
	bool	HT_bGetAttackTypeVSArmorTypeBlunt( const int id, int* piBlunt ) ;
	bool	HT_bGetAttackTypeVSArmorTypeMagic( const int id, int* piMagic ) ;
	bool	HT_bGetAttackTypeVSArmorTypeAnimal( const int id, int* piAnimal ) ;
	bool	HT_bGetAttackTypeVSArmorTypeDemon( const int id, int* piDemon ) ;
	bool	HT_bGetAttackTypeVSArmorTypeGolem( const int id, int* piGolem ) ;
	bool	HT_bGetAttackTypeVSArmorTypeUndead( const int id, int* piUndead ) ;
	bool	HT_bGetAttackTypeVSArmorTypePlant( const int id, int* piPlant ) ;
	bool	HT_bGetAttackTypeVSArmorTypeInsect( const int id, int* piInsect ) ;
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid1( const int id, int* piHumanoid1 ) ;
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid2( const int id, int* piHumanoid2 ) ;
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid3( const int id, int* piHumanoid3 ) ;
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid4( const int id, int* piHumanoid4 ) ;

	// Item without ID
	//bool	HT_bGetAttackTypeVSArmorTypeArmor( int* piArmor ) ;
	bool	HT_bGetAttackTypeVSArmorTypeDagger( int* piDagger ) ;
	bool	HT_bGetAttackTypeVSArmorTypeSword( int* piSword ) ;
	bool	HT_bGetAttackTypeVSArmorTypeTwoHandSword( int* piTwoHandSword ) ;
	bool	HT_bGetAttackTypeVSArmorTypeAxe( int* piAxe ) ;
	bool	HT_bGetAttackTypeVSArmorTypeTwoHandAxe( int* piTwoHandAxe ) ;
	bool	HT_bGetAttackTypeVSArmorTypeSpear( int* piSpear ) ;
	bool	HT_bGetAttackTypeVSArmorTypeBow( int* piBow ) ;	
	bool	HT_bGetAttackTypeVSArmorTypeClaw( int* piClaw ) ;	
	bool	HT_bGetAttackTypeVSArmorTypeBlunt( int* piBlunt ) ;
	bool	HT_bGetAttackTypeVSArmorTypeMagic( int* piMagic ) ;
	bool	HT_bGetAttackTypeVSArmorTypeAnimal( int* piAnimal ) ;
	bool	HT_bGetAttackTypeVSArmorTypeDemon( int* piDemon ) ;
	bool	HT_bGetAttackTypeVSArmorTypeGolem( int* piGolem ) ;
	bool	HT_bGetAttackTypeVSArmorTypeUndead( int* piUndead ) ;
	bool	HT_bGetAttackTypeVSArmorTypePlant( int* piPlant ) ;
	bool	HT_bGetAttackTypeVSArmorTypeInsect( int* piInsect ) ;
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid1( int* piHumanoid1 ) ;
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid2( int* piHumanoid2 ) ;
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid3( int* piHumanoid3 ) ;
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid4( int* piHumanoid4 ) ;

private :
	struct HTAttackTypeVSArmorType
	{
		//int iArmor ; // id
		int iDagger ;
		int iSword ;
		int iTwoHandSword ;
		int iAxe ;
		int iTwoHandAxe ;
		int iSpear ;
		int iBow ;
		int iClaw ;
		int iBlunt ;
		int iMagic ;
		int iAnimal ;
		int iDemon ;
		int iGolem ;
		int iUndead ;
		int iPlant ;
		int iInsect ;
		int iHumanoid1 ;
		int iHumanoid2 ;
		int iHumanoid3 ;
		int iHumanoid4 ;
	};

	typedef std::map<int,HTAttackTypeVSArmorType*>				HTAttackTypeVSArmorType_Map;
	typedef std::map<int,HTAttackTypeVSArmorType*>::value_type	HTAttackTypeVSArmorType_Value;
	typedef std::map<int,HTAttackTypeVSArmorType*>::iterator	HTAttackTypeVSArmorType_It;

	HTAttackTypeVSArmorType_Map				m_mapTable;
	HTAttackTypeVSArmorType*				m_pParam;
};



class CHTCoefficientByClassTable : public CHTBaseSSettingTable
{
public :
	CHTCoefficientByClassTable() : m_pParam(NULL) {} ;
	~CHTCoefficientByClassTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetCoefficientByClassClass1( const int id, int* piClass1 ) ;
	bool	HT_bGetCoefficientByClassClass2( const int id, int* piClass2 ) ;
	bool	HT_bGetCoefficientByClassDagger( const int id, int* piDagger ) ;
	bool	HT_bGetCoefficientByClassSword( const int id, int* piSword ) ;
	bool	HT_bGetCoefficientByClassTwoHandSword( const int id, int* piTwoHandSword ) ;
	bool	HT_bGetCoefficientByClassAxe( const int id, int* piAxe ) ;
	bool	HT_bGetCoefficientByClassTwoHandAxe( const int id, int* piTwoHandAxe ) ;
	bool	HT_bGetCoefficientByClassBlunt( const int id, int* piBlunt ) ;
	bool	HT_bGetCoefficientByClassSpear( const int id, int* piSpear ) ;
	bool	HT_bGetCoefficientByClassStaff( const int id, int* piStaff ) ;
	bool	HT_bGetCoefficientByClassClaw( const int id, int* piClaw ) ;
	bool	HT_bGetCoefficientByClassBow( const int id, int* piBow ) ;
	bool	HT_bGetCoefficientByClassThrowing( const int id, int* piThrowing ) ;
	bool	HT_bGetCoefficientByClassBare( const int id, int* piBare ) ;
	bool	HT_bGetCoefficientByClassShield( const int id, int* piShield ) ;
	bool	HT_bGetCoefficientByClassHP( const int id, int* piHP ) ;
	bool	HT_bGetCoefficientByClassTP( const int id, int* piTP ) ;
	bool	HT_bGetCoefficientByClassRecvry( const int id, int* piRecvry ) ;
	bool	HT_bGetCoefficientByClassAC( const int id, int* piAC ) ;
	bool	HT_bGetCoefficientByClassResist( const int id, int* piResist ) ;
	bool	HT_bGetCoefficientByClassAttackRate( const int id, int* piAttackRate ) ;
	bool	HT_bGetCoefficientByClassDodgeRate( const int id, int* piDodgeRate ) ;
	bool	HT_bGetCoefficientByClassAttackSpeed( const int id, int* piAttackSpeed ) ;
	bool	HT_bGetCoefficientByClassCastSpeed( const int id, int* piCastSpeed ) ;
	bool	HT_bGetCoefficientByClassDodgeSpeed( const int id, int* piDodgeSpeed ) ;

    // Item without ID
	bool	HT_bGetCoefficientByClassClass1( int* piClass1 ) ;
	bool	HT_bGetCoefficientByClassClass2( int* piClass2 ) ;
	bool	HT_bGetCoefficientByClassDagger( int* piDagger ) ;
	bool	HT_bGetCoefficientByClassSword( int* piSword ) ;
	bool	HT_bGetCoefficientByClassTwoHandSword( int* piTwoHandSword ) ;
	bool	HT_bGetCoefficientByClassAxe( int* piAxe ) ;
	bool	HT_bGetCoefficientByClassTwoHandAxe( int* piTwoHandAxe ) ;
	bool	HT_bGetCoefficientByClassBlunt( int* piBlunt ) ;
	bool	HT_bGetCoefficientByClassSpear( int* piSpear ) ;
	bool	HT_bGetCoefficientByClassStaff( int* piStaff ) ;
	bool	HT_bGetCoefficientByClassClaw( int* piClaw ) ;
	bool	HT_bGetCoefficientByClassBow( int* piBow ) ;
	bool	HT_bGetCoefficientByClassThrowing( int* piThrowing ) ;
	bool	HT_bGetCoefficientByClassBare( int* piBare ) ;
	bool	HT_bGetCoefficientByClassShield( int* piShield ) ;
	bool	HT_bGetCoefficientByClassHP( int* piHP ) ;
	bool	HT_bGetCoefficientByClassTP( int* piTP ) ;
	bool	HT_bGetCoefficientByClassRecvry( int* piRecvry ) ;
	bool	HT_bGetCoefficientByClassAC( int* piAC ) ;
	bool	HT_bGetCoefficientByClassResist( int* piResist ) ;
	bool	HT_bGetCoefficientByClassAttackRate( int* piAttackRate ) ;
	bool	HT_bGetCoefficientByClassDodgeRate( int* piDodgeRate ) ;
	bool	HT_bGetCoefficientByClassAttackSpeed( int* piAttackSpeed ) ;
	bool	HT_bGetCoefficientByClassCastSpeed( int* piCastSpeed ) ;
	bool	HT_bGetCoefficientByClassDodgeSpeed( int* piDodgeSpeed ) ;

private :
	struct HTCoefficientByClass
	{
		//int iID ;
		int iClass1 ; // 전직 level
		int iClass2 ; // specialized class
		int iDagger ;
		int iSword ;
		int iTwoHandSword ;
		int iAxe ;
		int iTwoHandAxe ;
		int iBlunt ;
		int iSpear ;
		int iStaff ;
		int iClaw ;
		int iBow ;
		int iThrowing ;
		int iBare ;
		int iShield ;
		int iHP ;
		int iTP ;
		int iRecvry ;
		int iAC ;
		int iResist ;
		int iAttackRate ;
		int iDodgeRate ;
		int iAttackSpeed ;
		int iCastSpeed ;
		int iDodgeSpeed ;
	};

	typedef std::map<int,HTCoefficientByClass*>				HTCoefficientByClass_Map;
	typedef std::map<int,HTCoefficientByClass*>::value_type	HTCoefficientByClass_Value;
	typedef std::map<int,HTCoefficientByClass*>::iterator	HTCoefficientByClass_It;

	HTCoefficientByClass_Map				m_mapTable;
	HTCoefficientByClass*					m_pParam;
};


class CHTJudgeCombatTable : public CHTBaseSSettingTable
{
public :
	CHTJudgeCombatTable() : m_pParam(NULL) {} ;
	~CHTJudgeCombatTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetJudgeCombatCriticalPCvsPC( const int id, int* piCriticalPCvsPC ) ;
	bool	HT_bGetJudgeCombatNormalPCvsPC( const int id, int* piNormalPCvsPC ) ;
	bool	HT_bGetJudgeCombatMissPCvsPC( const int id, int* piMissPCvsPC ) ;
	bool	HT_bGetJudgeCombatCriticalPCvsNPC( const int id, int* piCriticalPCvsNPC ) ;
	bool	HT_bGetJudgeCombatNormalPCvsNPC( const int id, int* piNormalPCvsNPC ) ;
	bool	HT_bGetJudgeCombatMissPCvsNPC( const int id, int* piMissPCvsNPC ) ;
	bool	HT_bGetJudgeCombatCriticalNPCvsPC( const int id, int* piCriticalNPCvsPC ) ;
	bool	HT_bGetJudgeCombatNormalNPCvsPC( const int id, int* piNormalNPCvsPC ) ;
	bool	HT_bGetJudgeCombatMissNPCvsPC( const int id, int* piMissNPCvsPC ) ;
	bool	HT_bGetJudgeCombatCriticalNPCvsNPC( const int id, int* piCriticalNPCvsNPC ) ;
	bool	HT_bGetJudgeCombatNormalNPCvsNPC( const int id, int* piNormalNPCvsNPC ) ;
	bool	HT_bGetJudgeCombatMissNPCvsNPC( const int id, int* piMissNPCvsNPC ) ;

    // Item without ID
	bool	HT_bGetJudgeCombatCriticalPCvsPC( int* piCriticalPCvsPC ) ;
	bool	HT_bGetJudgeCombatNormalPCvsPC( int* piNormalPCvsPC ) ;
	bool	HT_bGetJudgeCombatMissPCvsPC( int* piMissPCvsPC ) ;
	bool	HT_bGetJudgeCombatCriticalPCvsNPC( int* piCriticalPCvsNPC ) ;
	bool	HT_bGetJudgeCombatNormalPCvsNPC( int* piNormalPCvsNPC ) ;
	bool	HT_bGetJudgeCombatMissPCvsNPC( int* piMissPCvsNPC ) ;
	bool	HT_bGetJudgeCombatCriticalNPCvsPC( int* piCriticalNPCvsPC ) ;
	bool	HT_bGetJudgeCombatNormalNPCvsPC( int* piNormalNPCvsPC ) ;
	bool	HT_bGetJudgeCombatMissNPCvsPC( int* piMissNPCvsPC ) ;
	bool	HT_bGetJudgeCombatCriticalNPCvsNPC( int* piCriticalNPCvsNPC ) ;
	bool	HT_bGetJudgeCombatNormalNPCvsNPC( int* piNormalNPCvsNPC ) ;
	bool	HT_bGetJudgeCombatMissNPCvsNPC( int* piMissNPCvsNPC ) ;

private :
	struct HTJudgeCombat
	{
		// int iID ;  // id
		int iCriticalPCvsPC ;
		int iNormalPCvsPC ;
		int iMissPCvsPC ;
		int iCriticalPCvsNPC ;
		int iNormalPCvsNPC ;
		int iMissPCvsNPC ;
		int iCriticalNPCvsPC ;
		int iNormalNPCvsPC ;
		int iMissNPCvsPC ;
		int iCriticalNPCvsNPC ;
		int iNormalNPCvsNPC ;
		int iMissNPCvsNPC ;
	};

	typedef std::map<int,HTJudgeCombat*>				HTJudgeCombat_Map;
	typedef std::map<int,HTJudgeCombat*>::value_type	HTJudgeCombat_Value;
	typedef std::map<int,HTJudgeCombat*>::iterator		HTJudgeCombat_It;

	HTJudgeCombat_Map				m_mapTable;
	HTJudgeCombat*					m_pParam;
};



class CHTConsiderTable : public CHTBaseSSettingTable
{
public :
	CHTConsiderTable() : m_pParam(NULL) {} ;
	~CHTConsiderTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetConsiderDFPCvsPC( const int id, int* piDFPCvsPC ) ;
	bool	HT_bGetConsiderRSPCvsPC( const int id, int* piRSPCvsPC ) ;
	bool	HT_bGetConsiderDGPCvsPC( const int id, int* piDGPCvsPC ) ;
	bool	HT_bGetConsiderDFPCvsNPC( const int id, int* piDFPCvsNPC ) ;
	bool	HT_bGetConsiderRSPCvsNPC( const int id, int* piRSPCvsNPC ) ;
	bool	HT_bGetConsiderDGPCvsNPC( const int id, int* piDGPCvsNPC ) ;
	bool	HT_bGetConsiderDFNPCvsPC( const int id, int* piDFNPCvsPC ) ;
	bool	HT_bGetConsiderRSNPCvsPC( const int id, int* piRSNPCvsPC ) ;
	bool	HT_bGetConsiderDGNPCvsPC( const int id, int* piDGNPCvsPC ) ;
	bool	HT_bGetConsiderDFNPCvsNPC( const int id, int* piDFNPCvsNPC ) ;
	bool	HT_bGetConsiderRSNPCvsNPC( const int id, int* piRSNPCvsNPC ) ;
	bool	HT_bGetConsiderDGNPCvsNPC( const int id, int* piDGNPCvsNPC ) ;

    // Item without ID
	bool	HT_bGetConsiderDFPCvsPC( int* piDFPCvsPC ) ;
	bool	HT_bGetConsiderRSPCvsPC( int* piRSPCvsPC ) ;
	bool	HT_bGetConsiderDGPCvsPC( int* piDGPCvsPC ) ;
	bool	HT_bGetConsiderDFPCvsNPC( int* piDFPCvsNPC ) ;
	bool	HT_bGetConsiderRSPCvsNPC( int* piRSPCvsNPC ) ;
	bool	HT_bGetConsiderDGPCvsNPC( int* piDGPCvsNPC ) ;
	bool	HT_bGetConsiderDFNPCvsPC( int* piDFNPCvsPC ) ;
	bool	HT_bGetConsiderRSNPCvsPC( int* piRSNPCvsPC ) ;
	bool	HT_bGetConsiderDGNPCvsPC( int* piDGNPCvsPC ) ;
	bool	HT_bGetConsiderDFNPCvsNPC( int* piDFNPCvsNPC ) ;
	bool	HT_bGetConsiderRSNPCvsNPC( int* piRSNPCvsNPC ) ;
	bool	HT_bGetConsiderDGNPCvsNPC( int* piDGNPCvsNPC ) ;


private :
	struct HTConsider
	{
		//int iLevel ; // id라고 생각하면 될 것이다. 0~99
		int iDFPCvsPC ;
		int iRSPCvsPC ;
		int iDGPCvsPC ;
		int iDFPCvsNPC ;
		int iRSPCvsNPC ;
		int iDGPCvsNPC ;
		int iDFNPCvsPC ;
		int iRSNPCvsPC ;
		int iDGNPCvsPC ;
		int iDFNPCvsNPC ;
		int iRSNPCvsNPC ;
		int iDGNPCvsNPC ;
	};

	typedef std::map<int,HTConsider*>				HTConsider_Map;
	typedef std::map<int,HTConsider*>::value_type	HTConsider_Value;
	typedef std::map<int,HTConsider*>::iterator		HTConsider_It;

	HTConsider_Map				m_mapTable;
	HTConsider*					m_pParam;
};




class CHTRvRPKConsiderTable : public CHTBaseSSettingTable
{
public :
	CHTRvRPKConsiderTable() : m_pParam(NULL) {} ;
	~CHTRvRPKConsiderTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetRvRPKConsiderRewardBP( const int id, int* piRewardBP ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste0( const int id, int* piAttackerCaste0 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste1( const int id, int* piAttackerCaste1 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste2( const int id, int* piAttackerCaste2 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste3( const int id, int* piAttackerCaste3 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste4( const int id, int* piAttackerCaste4 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste5( const int id, int* piAttackerCaste5 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste6( const int id, int* piAttackerCaste6 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste7( const int id, int* piAttackerCaste7 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste8( const int id, int* piAttackerCaste8 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste9( const int id, int* piAttackerCaste9 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste10( const int id, int* piAttackerCaste10 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste11( const int id, int* piAttackerCaste11 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste12( const int id, int* piAttackerCaste12 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste13( const int id, int* piAttackerCaste13 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste14( const int id, int* piAttackerCaste14 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste15( const int id, int* piAttackerCaste15 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste16( const int id, int* piAttackerCaste16 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste17( const int id, int* piAttackerCaste17 ) ;

    // Item without ID
	bool	HT_bGetRvRPKConsiderRewardBP( int* piRewardBP ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste0( int* piAttackerCaste0 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste1( int* piAttackerCaste1 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste2( int* piAttackerCaste2 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste3( int* piAttackerCaste3 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste4( int* piAttackerCaste4 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste5( int* piAttackerCaste5 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste6( int* piAttackerCaste6 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste7( int* piAttackerCaste7 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste8( int* piAttackerCaste8 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste9( int* piAttackerCaste9 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste10( int* piAttackerCaste10 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste11( int* piAttackerCaste11 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste12( int* piAttackerCaste12 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste13( int* piAttackerCaste13 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste14( int* piAttackerCaste14 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste15( int* piAttackerCaste15 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste16( int* piAttackerCaste16 ) ;
	bool	HT_bGetRvRPKConsiderAttackerCaste17( int* piAttackerCaste17 ) ;

private :
	struct HTRvRPKConsider
	{
		//int iDefenderCaste ; // id
		int iRewardBP ;
		int iAttackerCaste0 ;
		int iAttackerCaste1 ;
		int iAttackerCaste2 ;
		int iAttackerCaste3 ;
		int iAttackerCaste4 ;
		int iAttackerCaste5 ;
		int iAttackerCaste6 ;
		int iAttackerCaste7 ;
		int iAttackerCaste8 ;
		int iAttackerCaste9 ;
		int iAttackerCaste10 ;
		int iAttackerCaste11 ;
		int iAttackerCaste12 ;
		int iAttackerCaste13 ;
		int iAttackerCaste14 ;
		int iAttackerCaste15 ;
		int iAttackerCaste16 ;
		int iAttackerCaste17 ;
	};

	typedef std::map<int,HTRvRPKConsider*>				HTRvRPKConsider_Map;
	typedef std::map<int,HTRvRPKConsider*>::value_type	HTRvRPKConsider_Value;
	typedef std::map<int,HTRvRPKConsider*>::iterator	HTRvRPKConsider_It;

	HTRvRPKConsider_Map				m_mapTable;
	HTRvRPKConsider*				m_pParam;
};



class CHTEffectToleranceTable : public CHTBaseSSettingTable
{
public :
	CHTEffectToleranceTable() : m_pParam(NULL) {} ;
	~CHTEffectToleranceTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetEffectToleranceClass1( const int id, int* piClass1 ) ;
	bool	HT_bGetEffectToleranceClass2( const int id, int* piClass2 ) ;
	bool	HT_bGetEffectToleranceHold( const int id, int* piHold ) ;
	bool	HT_bGetEffectToleranceStun( const int id, int* piStun ) ;
	bool	HT_bGetEffectToleranceSleep( const int id, int* piSleep ) ;
	bool	HT_bGetEffectToleranceBlind( const int id, int* piBlind ) ;
	bool	HT_bGetEffectToleranceTerror( const int id, int* piTerror ) ;
	bool	HT_bGetEffectToleranceTaunt( const int id, int* piTaunt ) ;
	bool	HT_bGetEffectToleranceSlowMove( const int id, int* piSlowMove ) ;
	bool	HT_bGetEffectToleranceSlowAttack( const int id, int* piSlowAttack ) ;

    // Item without ID
	bool	HT_bGetEffectToleranceClass1( int* piClass1 ) ;
	bool	HT_bGetEffectToleranceClass2( int* piClass2 ) ;
	bool	HT_bGetEffectToleranceHold( int* piHold ) ;
	bool	HT_bGetEffectToleranceStun( int* piStun ) ;
	bool	HT_bGetEffectToleranceSleep( int* piSleep ) ;
	bool	HT_bGetEffectToleranceBlind( int* piBlind ) ;
	bool	HT_bGetEffectToleranceTerror( int* piTerror ) ;
	bool	HT_bGetEffectToleranceTaunt( int* piTaunt ) ;
	bool	HT_bGetEffectToleranceSlowMove( int* piSlowMove ) ;
	bool	HT_bGetEffectToleranceSlowAttack( int* piSlowAttack ) ;

private :
	struct HTEffectTolerance
	{
		//int iID ; //id
		int iClass1 ;
		int iClass2 ;
		int iHold ;
		int iStun ;
		int iSleep ;
		int iBlind ;
		int iTerror ;
		int iTaunt ;
		int iSlowMove ;
		int iSlowAttack ;
	};

	typedef std::map<int,HTEffectTolerance*>				HTEffectTolerance_Map;
	typedef std::map<int,HTEffectTolerance*>::value_type	HTEffectTolerance_Value;
	typedef std::map<int,HTEffectTolerance*>::iterator		HTEffectTolerance_It;

	HTEffectTolerance_Map				m_mapTable;
	HTEffectTolerance*					m_pParam;
};



class CHTItemByLevelTable : public CHTBaseSSettingTable
{
public :
	CHTItemByLevelTable() : m_pParam(NULL) {} ;
	~CHTItemByLevelTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetItemByLevelLvl1( const int id, int* piLvl1 ) ;
	bool	HT_bGetItemByLevelLvl2( const int id, int* piLvl2 ) ;
	bool	HT_bGetItemByLevelLvl3( const int id, int* piLvl3 ) ;
	bool	HT_bGetItemByLevelLvl4( const int id, int* piLvl4 ) ;
	bool	HT_bGetItemByLevelLvl5( const int id, int* piLvl5 ) ;
	bool	HT_bGetItemByLevelLvl6( const int id, int* piLvl6 ) ;
	bool	HT_bGetItemByLevelLvl7( const int id, int* piLvl7 ) ;
	bool	HT_bGetItemByLevelLvl8( const int id, int* piLvl8 ) ;
	bool	HT_bGetItemByLevelLvl9( const int id, int* piLvl9 ) ;
	bool	HT_bGetItemByLevelLvl10( const int id, int* piLvl10 ) ;
	bool	HT_bGetItemByLevelLvl11( const int id, int* piLvl11 ) ;
	bool	HT_bGetItemByLevelLvl12( const int id, int* piLvl12 ) ;
	bool	HT_bGetItemByLevelLvl13( const int id, int* piLvl13 ) ;
	bool	HT_bGetItemByLevelLvl14( const int id, int* piLvl14 ) ;
	bool	HT_bGetItemByLevelLvl15( const int id, int* piLvl15 ) ;
	bool	HT_bGetItemByLevelLvl16( const int id, int* piLvl16 ) ;
	bool	HT_bGetItemByLevelLvl17( const int id, int* piLvl17 ) ;
	bool	HT_bGetItemByLevelLvl18( const int id, int* piLvl18 ) ;
	bool	HT_bGetItemByLevelLvl19( const int id, int* piLvl19 ) ;
	bool	HT_bGetItemByLevelLvl20( const int id, int* piLvl20 ) ;

	// Item without ID
	bool	HT_bGetItemByLevelLvl1( int* piLvl1 ) ;
	bool	HT_bGetItemByLevelLvl2( int* piLvl2 ) ;
	bool	HT_bGetItemByLevelLvl3( int* piLvl3 ) ;
	bool	HT_bGetItemByLevelLvl4( int* piLvl4 ) ;
	bool	HT_bGetItemByLevelLvl5( int* piLvl5 ) ;
	bool	HT_bGetItemByLevelLvl6( int* piLvl6 ) ;
	bool	HT_bGetItemByLevelLvl7( int* piLvl7 ) ;
	bool	HT_bGetItemByLevelLvl8( int* piLvl8 ) ;
	bool	HT_bGetItemByLevelLvl9( int* piLvl9 ) ;
	bool	HT_bGetItemByLevelLvl10( int* piLvl10 ) ;
	bool	HT_bGetItemByLevelLvl11( int* piLvl11 ) ;
	bool	HT_bGetItemByLevelLvl12( int* piLvl12 ) ;
	bool	HT_bGetItemByLevelLvl13( int* piLvl13 ) ;
	bool	HT_bGetItemByLevelLvl14( int* piLvl14 ) ;
	bool	HT_bGetItemByLevelLvl15( int* piLvl15 ) ;
	bool	HT_bGetItemByLevelLvl16( int* piLvl16 ) ;
	bool	HT_bGetItemByLevelLvl17( int* piLvl17 ) ;
	bool	HT_bGetItemByLevelLvl18( int* piLvl18 ) ;
	bool	HT_bGetItemByLevelLvl19( int* piLvl19 ) ;
	bool	HT_bGetItemByLevelLvl20( int* piLvl20 ) ;

private :
	struct HTItemByLevel
	{
		//int iCategory ; // id
		int iLvl1 ;
		int iLvl2 ;
		int iLvl3 ;
		int iLvl4 ;
		int iLvl5 ;
		int iLvl6 ;
		int iLvl7 ;
		int iLvl8 ;
		int iLvl9 ;
		int iLvl10 ;
		int iLvl11 ;
		int iLvl12 ;
		int iLvl13 ;
		int iLvl14 ;
		int iLvl15 ;
		int iLvl16 ;
		int iLvl17 ;
		int iLvl18 ;
		int iLvl19 ;
		int iLvl20 ;
	};

	typedef std::map<int,HTItemByLevel*>				HTItemByLevel_Map;
	typedef std::map<int,HTItemByLevel*>::value_type	HTItemByLevel_Value;
	typedef std::map<int,HTItemByLevel*>::iterator		HTItemByLevel_It;

	HTItemByLevel_Map				m_mapTable;
	HTItemByLevel*					m_pParam;
};



class CHTItemGroupTable : public CHTBaseSSettingTable
{
public :
	CHTItemGroupTable() : m_pParam(NULL) {} ;
	~CHTItemGroupTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetItemGroupGroup( const int id, int* piGroup ) ;
	bool	HT_bGetItemGroupItemID( const int id, int* piItemID ) ;
    // Item without ID
	bool	HT_bGetItemGroupGroup( int* piGroup ) ;
	bool	HT_bGetItemGroupItemID( int* piItemID ) ;

private :
	struct HTItemGroup
	{
		//int iID ; // id
		int iGroup ;
		int iItemID ;
	};

	typedef std::map<int,HTItemGroup*>				HTItemGroup_Map;
	typedef std::map<int,HTItemGroup*>::value_type	HTItemGroup_Value;
	typedef std::map<int,HTItemGroup*>::iterator	HTItemGroup_It;

	HTItemGroup_Map				m_mapTable;
	HTItemGroup*					m_pParam;
};



class CHTItemRateByMonLevelTable : public CHTBaseSSettingTable
{
public :
	CHTItemRateByMonLevelTable() : m_pParam(NULL) {} ;
	~CHTItemRateByMonLevelTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetItemRateByMonLevelLvl1( const int id, int* piLvl1 ) ;
	bool	HT_bGetItemRateByMonLevelLvl2( const int id, int* piLvl2 ) ;
	bool	HT_bGetItemRateByMonLevelLvl3( const int id, int* piLvl3 ) ;
	bool	HT_bGetItemRateByMonLevelLvl4( const int id, int* piLvl4 ) ;
	bool	HT_bGetItemRateByMonLevelLvl5( const int id, int* piLvl5 ) ;
	bool	HT_bGetItemRateByMonLevelLvl6( const int id, int* piLvl6 ) ;
	bool	HT_bGetItemRateByMonLevelLvl7( const int id, int* piLvl7 ) ;
	bool	HT_bGetItemRateByMonLevelLvl8( const int id, int* piLvl8 ) ;
	bool	HT_bGetItemRateByMonLevelLvl9( const int id, int* piLvl9 ) ;
	bool	HT_bGetItemRateByMonLevelLvl10( const int id, int* piLvl10 ) ;
	bool	HT_bGetItemRateByMonLevelLvl11( const int id, int* piLvl11 ) ;
	bool	HT_bGetItemRateByMonLevelLvl12( const int id, int* piLvl12 ) ;
	bool	HT_bGetItemRateByMonLevelLvl13( const int id, int* piLvl13 ) ;
	bool	HT_bGetItemRateByMonLevelLvl14( const int id, int* piLvl14 ) ;
	bool	HT_bGetItemRateByMonLevelLvl15( const int id, int* piLvl15 ) ;
	bool	HT_bGetItemRateByMonLevelLvl16( const int id, int* piLvl16 ) ;
	bool	HT_bGetItemRateByMonLevelLvl17( const int id, int* piLvl17 ) ;
	bool	HT_bGetItemRateByMonLevelLvl18( const int id, int* piLvl18 ) ;
	bool	HT_bGetItemRateByMonLevelLvl19( const int id, int* piLvl19 ) ;
	bool	HT_bGetItemRateByMonLevelLvl20( const int id, int* piLvl20 ) ;

	// Item without ID
	bool	HT_bGetItemRateByMonLevelLvl1( int* piLvl1 ) ;
	bool	HT_bGetItemRateByMonLevelLvl2( int* piLvl2 ) ;
	bool	HT_bGetItemRateByMonLevelLvl3( int* piLvl3 ) ;
	bool	HT_bGetItemRateByMonLevelLvl4( int* piLvl4 ) ;
	bool	HT_bGetItemRateByMonLevelLvl5( int* piLvl5 ) ;
	bool	HT_bGetItemRateByMonLevelLvl6( int* piLvl6 ) ;
	bool	HT_bGetItemRateByMonLevelLvl7( int* piLvl7 ) ;
	bool	HT_bGetItemRateByMonLevelLvl8( int* piLvl8 ) ;
	bool	HT_bGetItemRateByMonLevelLvl9( int* piLvl9 ) ;
	bool	HT_bGetItemRateByMonLevelLvl10( int* piLvl10 ) ;
	bool	HT_bGetItemRateByMonLevelLvl11( int* piLvl11 ) ;
	bool	HT_bGetItemRateByMonLevelLvl12( int* piLvl12 ) ;
	bool	HT_bGetItemRateByMonLevelLvl13( int* piLvl13 ) ;
	bool	HT_bGetItemRateByMonLevelLvl14( int* piLvl14 ) ;
	bool	HT_bGetItemRateByMonLevelLvl15( int* piLvl15 ) ;
	bool	HT_bGetItemRateByMonLevelLvl16( int* piLvl16 ) ;
	bool	HT_bGetItemRateByMonLevelLvl17( int* piLvl17 ) ;
	bool	HT_bGetItemRateByMonLevelLvl18( int* piLvl18 ) ;
	bool	HT_bGetItemRateByMonLevelLvl19( int* piLvl19 ) ;
	bool	HT_bGetItemRateByMonLevelLvl20( int* piLvl20 ) ;

private :
	struct HTItemRateByMonLevel
	{
		//int iMonLevel ; // id
		int iLvl1 ;
		int iLvl2 ;
		int iLvl3 ;
		int iLvl4 ;
		int iLvl5 ;
		int iLvl6 ;
		int iLvl7 ;
		int iLvl8 ;
		int iLvl9 ;
		int iLvl10 ;
		int iLvl11 ;
		int iLvl12 ;
		int iLvl13 ;
		int iLvl14 ;
		int iLvl15 ;
		int iLvl16 ;
		int iLvl17 ;
		int iLvl18 ;
		int iLvl19 ;
		int iLvl20 ;
	};

	typedef std::map<int,HTItemRateByMonLevel*>				HTItemRateByMonLevel_Map;
	typedef std::map<int,HTItemRateByMonLevel*>::value_type	HTItemRateByMonLevel_Value;
	typedef std::map<int,HTItemRateByMonLevel*>::iterator	HTItemRateByMonLevel_It;

	HTItemRateByMonLevel_Map				m_mapTable;
	HTItemRateByMonLevel*					m_pParam;
};



class CHTItemRateByMonLevelForTestSrvTable : public CHTBaseSSettingTable
{
public :
	CHTItemRateByMonLevelForTestSrvTable() : m_pParam(NULL) {} ;
	~CHTItemRateByMonLevelForTestSrvTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl1( const int id, int* piLvl1 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl2( const int id, int* piLvl2 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl3( const int id, int* piLvl3 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl4( const int id, int* piLvl4 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl5( const int id, int* piLvl5 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl6( const int id, int* piLvl6 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl7( const int id, int* piLvl7 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl8( const int id, int* piLvl8 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl9( const int id, int* piLvl9 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl10( const int id, int* piLvl10 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl11( const int id, int* piLvl11 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl12( const int id, int* piLvl12 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl13( const int id, int* piLvl13 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl14( const int id, int* piLvl14 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl15( const int id, int* piLvl15 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl16( const int id, int* piLvl16 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl17( const int id, int* piLvl17 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl18( const int id, int* piLvl18 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl19( const int id, int* piLvl19 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl20( const int id, int* piLvl20 ) ;

	// Item without ID
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl1( int* piLvl1 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl2( int* piLvl2 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl3( int* piLvl3 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl4( int* piLvl4 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl5( int* piLvl5 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl6( int* piLvl6 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl7( int* piLvl7 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl8( int* piLvl8 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl9( int* piLvl9 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl10( int* piLvl10 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl11( int* piLvl11 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl12( int* piLvl12 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl13( int* piLvl13 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl14( int* piLvl14 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl15( int* piLvl15 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl16( int* piLvl16 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl17( int* piLvl17 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl18( int* piLvl18 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl19( int* piLvl19 ) ;
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl20( int* piLvl20 ) ;

private :
	struct HTItemRateByMonLevelForTestSrv
	{
		// int iMonLevel ; // id
		int iLvl1 ;
		int iLvl2 ;
		int iLvl3 ;
		int iLvl4 ;
		int iLvl5 ;
		int iLvl6 ;
		int iLvl7 ;
		int iLvl8 ;
		int iLvl9 ;
		int iLvl10 ;
		int iLvl11 ;
		int iLvl12 ;
		int iLvl13 ;
		int iLvl14 ;
		int iLvl15 ;
		int iLvl16 ;
		int iLvl17 ;
		int iLvl18 ;
		int iLvl19 ;
		int iLvl20 ;
	};

	typedef std::map<int,HTItemRateByMonLevelForTestSrv*>				HTItemRateByMonLevelForTestSrv_Map;
	typedef std::map<int,HTItemRateByMonLevelForTestSrv*>::value_type	HTItemRateByMonLevelForTestSrv_Value;
	typedef std::map<int,HTItemRateByMonLevelForTestSrv*>::iterator		HTItemRateByMonLevelForTestSrv_It;

	HTItemRateByMonLevelForTestSrv_Map				m_mapTable;
	HTItemRateByMonLevelForTestSrv*					m_pParam;
};



class CHTKalaAltarTable : public CHTBaseSSettingTable
{
public :
	CHTKalaAltarTable() : m_pParam(NULL) {} ;
	~CHTKalaAltarTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetKalaAltarZone( const int id, int* piZone ) ;
	bool	HT_bGetKalaAltarClan( const int id, int* piClan ) ;
	bool	HT_bGetKalaAltarX( const int id, int* piX ) ;
	bool	HT_bGetKalaAltarY( const int id, int* piY ) ;

    // Item without ID
	bool	HT_bGetKalaAltarZone( int* piZone ) ;
	bool	HT_bGetKalaAltarClan( int* piClan ) ;
	bool	HT_bGetKalaAltarX( int* piX ) ;
	bool	HT_bGetKalaAltarY( int* piY ) ;

private :
	struct HTKalaAltar
	{
		//int iSequence ;
		//int iID ; // id
		int iZone ;
		int iClan ;
		int iX ;
		int iY ;
	};

	typedef std::map<int,HTKalaAltar*>				HTKalaAltar_Map;
	typedef std::map<int,HTKalaAltar*>::value_type	HTKalaAltar_Value;
	typedef std::map<int,HTKalaAltar*>::iterator	HTKalaAltar_It;

	HTKalaAltar_Map				m_mapTable;
	HTKalaAltar*				m_pParam;
};



class CHTKalaRewarderPositionTable : public CHTBaseSSettingTable
{
public :
	CHTKalaRewarderPositionTable() : m_pParam(NULL) {} ;
	~CHTKalaRewarderPositionTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetRewarderPositionZone( const int id, int* piZone ) ;
	bool	HT_bGetRewarderPositionNPCIndex( const int id, int* piNPCIndex ) ;
	bool	HT_bGetRewarderPositionClan( const int id, int* piClan ) ;
	bool	HT_bGetRewarderPositionX( const int id, int* piX ) ;
	bool	HT_bGetRewarderPositionY( const int id, int* piY ) ;

    // Item without ID
	bool	HT_bGetRewarderPositionZone( int* piZone ) ;
	bool	HT_bGetRewarderPositionNPCIndex( int* piNPCIndex ) ;
	bool	HT_bGetRewarderPositionClan( int* piClan ) ;
	bool	HT_bGetRewarderPositionX( int* piX ) ;
	bool	HT_bGetRewarderPositionY( int* piY ) ;


private :
	struct HTKalaRewarderPosition
	{
		//int iID ;
		int iZone ;
		int iNPCIndex ;
		int iClan ;
		int iX ;
		int iY ;
	};

	typedef std::map<int,HTKalaRewarderPosition*>				HTKalaRewarderPosition_Map;
	typedef std::map<int,HTKalaRewarderPosition*>::value_type	HTKalaRewarderPosition_Value;
	typedef std::map<int,HTKalaRewarderPosition*>::iterator		HTKalaRewarderPosition_It;

	HTKalaRewarderPosition_Map				m_mapTable;
	HTKalaRewarderPosition*					m_pParam;
};



class CHTRateByItemCategoryTable : public CHTBaseSSettingTable
{
public :
	CHTRateByItemCategoryTable() : m_pParam(NULL) {} ;
	~CHTRateByItemCategoryTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetRateByItemCategoryRate( const int id, int* piRate ) ;

    // Item without ID
	bool	HT_bGetRateByItemCategoryRate( int* piRate ) ;

private :
	struct HTRateByItemCategory
	{
		//int iCategory ;
		int iRate ;
	};

	typedef std::map<int,HTRateByItemCategory*>				HTRateByItemCategory_Map;
	typedef std::map<int,HTRateByItemCategory*>::value_type	HTRateByItemCategory_Value;
	typedef std::map<int,HTRateByItemCategory*>::iterator	HTRateByItemCategory_It;

	HTRateByItemCategory_Map				m_mapTable;
	HTRateByItemCategory*					m_pParam;
};



class CHTEventListTable : public CHTBaseSSettingTable
{
public :
	CHTEventListTable() : m_pParam(NULL) {} ;
	~CHTEventListTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetEventListZone( const int id, int* piZone ) ;
	bool	HT_bGetEventListEventID( const int id, int* piEventID ) ;
	bool	HT_bGetEventListTask1( const int id, int* piTask1 ) ;
	bool	HT_bGetEventListTask2( const int id, int* piTask2 ) ;
	bool	HT_bGetEventListTask3( const int id, int* piTask3 ) ;
	bool	HT_bGetEventListTask4( const int id, int* piTask4 ) ;
	bool	HT_bGetEventListTask5( const int id, int* piTask5 ) ;
	bool	HT_bGetEventListCoolDownTime( const int id, int* puiCoolDownTime ) ;
	bool	HT_bGetEventListCount( const int id, int* piCount ) ;
	bool	HT_bGetEventListProceedType( const int id, int* piProceedType ) ;
	bool	HT_bGetEventListDuration( const int id, int* piDuration ) ;	

    // Item without ID
	bool	HT_bGetEventListZone( int* piZone ) ;
	bool	HT_bGetEventListEventID( int* piEventID ) ;
	bool	HT_bGetEventListTask1( int* piTask1 ) ;
	bool	HT_bGetEventListTask2( int* piTask2 ) ;
	bool	HT_bGetEventListTask3( int* piTask3 ) ;
	bool	HT_bGetEventListTask4( int* piTask4 ) ;
	bool	HT_bGetEventListTask5( int* piTask5 ) ;
	bool	HT_bGetEventListCoolDownTime( int* puiCoolDownTime ) ;
	bool	HT_bGetEventListCount( int* piCount ) ;
	bool	HT_bGetEventListProceedType( int* piProceedType ) ;
	bool	HT_bGetEventListDuration( int* piDuration ) ;

private :
	struct HTEventList
	{
		int iZone ;
		int iEventID ;
		int iTask1 ;
		int iTask2 ;
		int iTask3 ;
		int iTask4 ;
		int iTask5 ;
		unsigned int uiCoolDownTime ;
		int iCount ;
		int iProceedType ;
		int iDuration ;
	};

	typedef std::map<int,HTEventList*>				HTEventList_Map;
	typedef std::map<int,HTEventList*>::value_type	HTEventList_Value;
	typedef std::map<int,HTEventList*>::iterator	HTEventList_It;

	HTEventList_Map				m_mapTable;
	HTEventList*				m_pParam;
};



class CHTTaskListTable : public CHTBaseSSettingTable
{
public :
	CHTTaskListTable() : m_pParam(NULL) {} ;
	~CHTTaskListTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetTaskListZone( const int id, int* piZone ) ;
	bool	HT_bGetTaskListTaskID( const int id, int* piTaskID ) ;
	bool	HT_bGetTaskListActionID( const int id, int* piActionID ) ;
	bool	HT_bGetTaskListParam1( const int id, int* piParam1 ) ;
	bool	HT_bGetTaskListParam2( const int id, int* piParam2 ) ;
	bool	HT_bGetTaskListParam3( const int id, int* piParam3 ) ;
	bool	HT_bGetTaskListParam4( const int id, int* piParam4 ) ;
	bool	HT_bGetTaskListParam5( const int id, int* piParam5 ) ;
	bool	HT_bGetTaskListParam6( const int id, int* piParam6 ) ;
    // Item without ID
	bool	HT_bGetTaskListZone( int* piZone ) ;
	bool	HT_bGetTaskListTaskID( int* piTaskID ) ;
	bool	HT_bGetTaskListActionID( int* piActionID ) ;
	bool	HT_bGetTaskListParam1( int* piParam1 ) ;
	bool	HT_bGetTaskListParam2( int* piParam2 ) ;
	bool	HT_bGetTaskListParam3( int* piParam3 ) ;
	bool	HT_bGetTaskListParam4( int* piParam4 ) ;
	bool	HT_bGetTaskListParam5( int* piParam5 ) ;
	bool	HT_bGetTaskListParam6( int* piParam6 ) ;

private :
	struct HTTaskList
	{
		int iZoneID ;
		int iTaskID ;
		int iActionID ;
		int iParam1 ;
		int iParam2 ;
		int iParam3 ;
		int iParam4 ;
		int iParam5 ;
		int iParam6 ;
	};

	typedef std::map<int,HTTaskList*>				HTTaskList_Map;
	typedef std::map<int,HTTaskList*>::value_type	HTTaskList_Value;
	typedef std::map<int,HTTaskList*>::iterator		HTTaskList_It;

	HTTaskList_Map				m_mapTable;
	HTTaskList*					m_pParam;
};



class CHTEventScheduleTable : public CHTBaseSSettingTable
{
public :
	CHTEventScheduleTable() : m_pParam(NULL) {} ;
	~CHTEventScheduleTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetEventScheduleZone( const int id, int* piZone ) ; // sequence id
	bool	HT_bGetEventScheduleMin( const int id, int* piMin ) ;
	bool	HT_bGetEventScheduleSec( const int id, int* piSec ) ;
	bool	HT_bGetEventScheduleEvent( const int id, int* piEvent ) ;

    // Item without ID
	bool	HT_bGetEventScheduleZone( int* piZone ) ;
	bool	HT_bGetEventScheduleMin( int* piMin ) ;
	bool	HT_bGetEventScheduleSec( int* piSec ) ;
	bool	HT_bGetEventScheduleEvent( int* piEvent ) ;

private :
	struct HTEventSchedule
	{
		int iZoneID ;
		int iMin ;
		int iSec ;
		int iEvent ;
	};

	typedef std::map<int,HTEventSchedule*>				HTEventSchedule_Map;
	typedef std::map<int,HTEventSchedule*>::value_type	HTEventSchedule_Value;
	typedef std::map<int,HTEventSchedule*>::iterator		HTEventSchedule_It;

	HTEventSchedule_Map				m_mapTable;
	HTEventSchedule*					m_pParam;
};




class CHTSetItemTable : public CHTBaseSSettingTable
{
public :
	CHTSetItemTable() : m_pParam(NULL) {} ;
	~CHTSetItemTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetSetItemID( const int id, int* piParam ) ;
	bool	HT_bGetSetItemHelmet( const int id, int* piParam ) ;
	bool	HT_bGetSetItemNecklace( const int id, int* piParam ) ;
	bool	HT_bGetSetItemArmor( const int id, int* piParam ) ;
	bool	HT_bGetSetItemBelt( const int id, int* piParam ) ;
	bool	HT_bGetSetItemWeapon( const int id, int* piParam ) ;
	bool	HT_bGetSetItemShield( const int id, int* piParam ) ;
	bool	HT_bGetSetItemBoots( const int id, int* piParam ) ;
	bool	HT_bGetSetItemGloves( const int id, int* piParam ) ;
	bool	HT_bGetSetItemPants( const int id, int* piParam ) ;
	bool	HT_bGetSetItemEffectItem( const int id, int* piParam ) ;
	bool	HT_bGetSetItemEffectItem2( const int id, int* piParam ) ;
#ifndef __BEFORE_SET_ITEM_EXPANDED__
	bool	HT_bGetSetItemEffectItem3( const int id, int* piParam ) ;
#endif

    // Item without ID
	bool	HT_bGetSetItemID( int* piParam ) ;
	bool	HT_bGetSetItemHelmet( int* piParam ) ;
	bool	HT_bGetSetItemNecklace( int* piParam ) ;
	bool	HT_bGetSetItemArmor( int* piParam ) ;
	bool	HT_bGetSetItemBelt( int* piParam ) ;
	bool	HT_bGetSetItemWeapon( int* piParam ) ;
	bool	HT_bGetSetItemShield( int* piParam ) ;
	bool	HT_bGetSetItemBoots( int* piParam ) ;
	bool	HT_bGetSetItemGloves( int* piParam ) ;
	bool	HT_bGetSetItemPants( int* piParam ) ;
	bool	HT_bGetSetItemEffectItem( int* piParam ) ;
	bool	HT_bGetSetItemEffectItem2( int* piParam ) ;
#ifndef __BEFORE_SET_ITEM_EXPANDED__
	bool	HT_bGetSetItemEffectItem3( int* piParam ) ;
#endif

private :
	struct HTSetItem
	{//iID	iHelmet	iNecklace	iArmor	iBelt	iWeapon	iShield	iBoots	iGloves	iPants	iEffectItem	iEffectItem2
		int iID;
		int iHelmet;
		int iNecklace;
		int iArmor;
		int iBelt;
		int iWeapon;
		int iShield;
		int iBoots;
		int iGloves;
		int iPants;
		int iEffectItem;
		int iEffectItem2;
#ifndef __BEFORE_SET_ITEM_EXPANDED__
		int iEffectItem3;
#endif
	};

	typedef std::map<int,HTSetItem*>				HTSetItem_Map;
	typedef std::map<int,HTSetItem*>::value_type	HTSetItem_Value;
	typedef std::map<int,HTSetItem*>::iterator	HTSetItem_It;

	HTSetItem_Map			m_mapTable;
	HTSetItem*				m_pParam;
};




class CHTGameEventTable : public CHTBaseSSettingTable
{
public :
	CHTGameEventTable() : m_pParam(NULL) {} ;
	~CHTGameEventTable() ;
	bool	HT_bLoad( CHTXMLParser* pXML, CHTString& strTable, CHTString& strLanguage ) ;
	bool	HT_bLoad( CHTFile* pFile ) ;
	bool	HT_bSave( CHTFile* pFile ) ;

	bool HT_bGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) ;

	// SetID
	bool	HT_bLockID( const int id, const byte iLevel = 0 );
	bool	HT_bUnLockID( const int id, const byte iLevel = 0 );

public :
    // Item with ID
	bool	HT_bGetGameEventID	   ( const int id, int* piEventID) ;
	bool	HT_bGetGameEventType   ( const int id, int* piType) ;
	bool	HT_bGetGameEventTarget ( const int id, int* piTarget) ;
	bool	HT_bGetGameEventZone   ( const int id, int* piZone ) ;
	bool	HT_bGetGameEventAction1( const int id, int* piAction) ;
	bool	HT_bGetGameEventParam11( const int id, int* piParam ) ;
	bool	HT_bGetGameEventParam12( const int id, int* piParam ) ;
	bool	HT_bGetGameEventAction2( const int id, int* piAction ) ;
	bool	HT_bGetGameEventParam21( const int id, int* piParam ) ;
	bool	HT_bGetGameEventParam22( const int id, int* piParam ) ;
	bool	HT_bGetGameEventAction3( const int id, int* piAction ) ;
	bool	HT_bGetGameEventParam31( const int id, int* piParam ) ;
	bool	HT_bGetGameEventParam32( const int id, int* piParam ) ;
	bool	HT_bGetGameEventAction4( const int id, int* piAction ) ;
	bool	HT_bGetGameEventParam41( const int id, int* piParam ) ;
	bool	HT_bGetGameEventParam42( const int id, int* piParam ) ;
	bool	HT_bGetGameEventAction5( const int id, int* piAction ) ;
	bool	HT_bGetGameEventParam51( const int id, int* piParam ) ;
	bool	HT_bGetGameEventParam52( const int id, int* piParam ) ;
	bool	HT_bGetGameEventAction6( const int id, int* piAction ) ;
	bool	HT_bGetGameEventParam61( const int id, int* piParam ) ;
	bool	HT_bGetGameEventParam62( const int id, int* piParam ) ;

    // Item without ID
	bool	HT_bGetGameEventAction1( int* piAction) ;
	bool	HT_bGetGameEventParam11( int* piParam ) ;
	bool	HT_bGetGameEventParam12( int* piParam ) ;
	bool	HT_bGetGameEventAction2( int* piAction ) ;
	bool	HT_bGetGameEventParam21( int* piParam ) ;
	bool	HT_bGetGameEventParam22( int* piParam ) ;
	bool	HT_bGetGameEventAction3( int* piAction ) ;
	bool	HT_bGetGameEventParam31( int* piParam ) ;
	bool	HT_bGetGameEventParam32( int* piParam ) ;
	bool	HT_bGetGameEventAction4( int* piAction ) ;
	bool	HT_bGetGameEventParam41( int* piParam ) ;
	bool	HT_bGetGameEventParam42( int* piParam ) ;
	bool	HT_bGetGameEventAction5( int* piAction ) ;
	bool	HT_bGetGameEventParam51( int* piParam ) ;
	bool	HT_bGetGameEventParam52( int* piParam ) ;
	bool	HT_bGetGameEventAction6( int* piAction ) ;
	bool	HT_bGetGameEventParam61( int* piParam ) ;
	bool	HT_bGetGameEventParam62( int* piParam ) ;

private :
	struct HTGameEvent
	{
		int iEventID;
		int	iType;
		int iTarget;
		int iZone;
		int iAction1;
		int iParam11;
		int iParam12;
		int iAction2;
		int iParam21;
		int iParam22;
		int iAction3;
		int iParam31;
		int iParam32;
		int iAction4;
		int iParam41;
		int iParam42;
		int iAction5;
		int iParam51;
		int iParam52;
		int iAction6;
		int iParam61;
		int iParam62;
	};

	typedef std::map<int,HTGameEvent*>				HTGameEvent_Map;
	typedef std::map<int,HTGameEvent*>::value_type	HTGameEvent_Value;
	typedef std::map<int,HTGameEvent*>::iterator	HTGameEvent_It;

	HTGameEvent_Map				m_mapTable;
	HTGameEvent*				m_pParam;
};




class CHTSSettingMgr
{
public:
	CHTSSettingMgr() ;
	~CHTSSettingMgr() ;

	bool		HT_bLoad( CHTString& strFile );
	bool		HT_bLoadXML( CHTString& strFile );
	bool		HT_bSave( CHTString& strFile );
	bool		HT_bTestSave( CHTString& strFile );

	void		HT_vSetLanguage( CHTString szLanguage ) { m_szLanguage = szLanguage; }

public :
	bool		HT_bAIListGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kAIList.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bActionGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kAction.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bActionListGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kActionList.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bSpeechContentGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kSpeechContent.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bSpeechCommentGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kSpeechComment.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bLevelUpGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kLevelUp.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bBramanPointGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kBramanPoint.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bAttackTypeVSArmorTypeGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kAttackTypeVSArmorType.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bCoefficientByClassGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kCoefficientByClass.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bJudgeCombatGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kJudgeCombat.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bConsiderGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kConsider.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bRvRPKConsiderGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kRvRPKConsider.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bEffectToleranceGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kEffectTolerance.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bItemByLevelGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kItemByLevel.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bItemRateByMonLevelGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kItemRateByMonLevel.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bItemRateByMonLevelForTestSrvGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kItemRateByMonLevelForTestSrv.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bItemGroupGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kItemGroup.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bRateByItemCategoryGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kRateByItemCategory.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bKalaAltarGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kKalaAltar.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bRewarderPositionGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kKalaRewarderPosition.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bEventListGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kEventList.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bTaskListGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kTaskList.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bEventScheduleGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kEventSchedule.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bGameEventGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kGameEvent.HT_bGetAllID( pvectorIDLevel ) ; }
	bool		HT_bSetItemGetAllID( std::vector<HTIDLevel2>* pvectorIDLevel ) { return m_kSetItem.HT_bGetAllID( pvectorIDLevel ) ; }
	
private:
	void		HT_vTestAIList( FILE* pFile);
	void		HT_vTestActionList( FILE* pFile);
	void		HT_vTestAction( FILE* pFile);
	void		HT_vTestSpeechContent( FILE* pFile);
	void		HT_vTestSpeechComment( FILE* pFile);
	void		HT_vTestLevelUp( FILE* pFile);
	void		HT_vTestBramanPoint( FILE* pFile);
	void		HT_vTestAttackTypeVSArmorType( FILE* pFile);
	void		HT_vTestCoefficientByClass( FILE* pFile);
	void		HT_vTestJudgeCombat( FILE* pFile);
	void		HT_vTestConsider( FILE* pFile);
	void		HT_vTestRvRPKConsider( FILE* pFile);
	void		HT_vTestEffectTolerance( FILE* pFile);
	void		HT_vTestItemByLevel( FILE* pFile);
	void		HT_vTestItemRateByMonLevel( FILE* pFile);
	void		HT_vTestItemRateByMonLevelForTestSrv( FILE* pFile);
	void		HT_vTestItemGroup( FILE* pFile);
	void		HT_vTestKalaAltar( FILE* pFile);
	void		HT_vTestRewarderPosition( FILE* pFile);
	void		HT_vTestRateByItemCategory( FILE* pFile);
	void		HT_vTestEventList( FILE* pFile);
	void		HT_vTestTaskList( FILE* pFile);
	void		HT_vTestEventSchedule( FILE* pFile);
	void		HT_vTestGameEvent( FILE* pFile);
	void		HT_vTestSetItem( FILE* pFile );
	

public:
	// AI List
	bool	HT_bGetAIListRest( const int id, int* piRest ) { return m_kAIList.HT_bGetAIListRest( id, piRest ) ; }
	bool	HT_bGetAIListMove( const int id, int* piMove )  { return m_kAIList.HT_bGetAIListMove( id, piMove ) ; }
	bool	HT_bGetAIListStart( const int id, int* piStart )  { return m_kAIList.HT_bGetAIListStart( id, piStart ) ; }
	bool	HT_bGetAIListArrive( const int id, int* piArrive )  { return m_kAIList.HT_bGetAIListArrive( id, piArrive ) ; }
	bool	HT_bGetAIListDetect( const int id, int* piArrive )  { return m_kAIList.HT_bGetAIListDetect( id, piArrive ) ; }	
	bool	HT_bGetAIListHelp1( const int id, int* piHelp1 )  { return m_kAIList.HT_bGetAIListHelp1( id, piHelp1 ) ; }
	bool	HT_bGetAIListLink1( const int id, int* piLink1 )  { return m_kAIList.HT_bGetAIListLink1( id, piLink1 ) ; }
	bool	HT_bGetAIListGuard( const int id, int* piGuard )  { return m_kAIList.HT_bGetAIListGuard( id, piGuard ) ; }
	bool	HT_bGetAIListBeKilled1( const int id, int* piBeKilled1 )  { return m_kAIList.HT_bGetAIListBeKilled1( id, piBeKilled1 ) ; }
	bool	HT_bGetAIListUnderAttack1( const int id, int* piUnderAttack1 )  { return m_kAIList.HT_bGetAIListUnderAttack1( id, piUnderAttack1 ) ; }
	bool	HT_bGetAIListAttack( const int id, int* piAttack )  { return m_kAIList.HT_bGetAIListAttack( id, piAttack ) ; }
	bool	HT_bGetAIListHit( const int id, int* piHit )  { return m_kAIList.HT_bGetAIListHit( id, piHit ) ; }
	bool	HT_bGetAIListMiss( const int id, int* piMiss )  { return m_kAIList.HT_bGetAIListMiss( id, piMiss ) ; }
	bool	HT_bGetAIListBeHitted( const int id, int* piBeHitted )  { return m_kAIList.HT_bGetAIListBeHitted( id, piBeHitted ) ; }
	bool	HT_bGetAIListDodge( const int id, int* piDodge )  { return m_kAIList.HT_bGetAIListDodge( id, piDodge ) ; }
	bool	HT_bGetAIListTrace( const int id, int* piTrace )  { return m_kAIList.HT_bGetAIListTrace( id, piTrace ) ; }
	bool	HT_bGetAIListGiveUpToTrace( const int id, int* piGiveUpToTrace )  { return m_kAIList.HT_bGetAIListGiveUpToTrace( id, piGiveUpToTrace ) ; }
	bool	HT_bGetAIListKillEnemy( const int id, int* piKillEnemy )  { return m_kAIList.HT_bGetAIListKillEnemy( id, piKillEnemy ) ; }
	bool	HT_bGetAIListHelp2( const int id, int* piHelp2 )  { return m_kAIList.HT_bGetAIListHelp2( id, piHelp2 ) ; }
	bool	HT_bGetAIListLink2( const int id, int* piLink2 )  { return m_kAIList.HT_bGetAIListLink2( id, piLink2 ) ; }
	bool	HT_bGetAIListGuard2( const int id, int* piGuard2 )  { return m_kAIList.HT_bGetAIListGuard2( id, piGuard2 ) ; }
	bool	HT_bGetAIListBeKilled2( const int id, int* piBeKilled2 )  { return m_kAIList.HT_bGetAIListBeKilled2( id, piBeKilled2 ) ; }
	bool	HT_bGetAIListUnderAttack2( const int id, int* piUnderAttack2 )  { return m_kAIList.HT_bGetAIListUnderAttack2( id, piUnderAttack2 ) ; }
	bool	HT_bGetAIListCantTrace( const int id, int* piCantTrace )  { return m_kAIList.HT_bGetAIListCantTrace( id, piCantTrace ) ; }
	bool	HT_bGetAIListStopToAttack( const int id, int* piStopToAttack )  { return m_kAIList.HT_bGetAIListStopToAttack( id, piStopToAttack ) ; }
	bool	HT_bGetAIListReturn( const int id, int* piReturn )  { return m_kAIList.HT_bGetAIListReturn( id, piReturn ) ; }
	bool	HT_bGetAIListFlee( const int id, int* piFlee )  { return m_kAIList.HT_bGetAIListFlee( id, piFlee ) ; }
	bool	HT_bGetAIListLead( const int id, int* piLead )  { return m_kAIList.HT_bGetAIListLead( id, piLead ) ; }
	bool	HT_bGetAIListPop( const int id, int* piPop )  { return m_kAIList.HT_bGetAIListPop( id, piPop ) ; }
	bool	HT_bGetAIListDialog1( const int id, int* piDialog1 )  { return m_kAIList.HT_bGetAIListDialog1( id, piDialog1 ) ; }
	bool	HT_bGetAIListDialog2( const int id, int* piDialog2 )  { return m_kAIList.HT_bGetAIListDialog2( id, piDialog2 ) ; }
	bool	HT_bGetAIListDialog3( const int id, int* piDialog3 )  { return m_kAIList.HT_bGetAIListDialog3( id, piDialog3 ) ; }
	bool	HT_bGetAIListDialog4( const int id, int* piDialog4 )  { return m_kAIList.HT_bGetAIListDialog4( id, piDialog4 ) ; }

	// Action
	bool	HT_bGetActionSpeak( const int id, int* piSpeak )  { return m_kAction.HT_bGetActionSpeak( id, piSpeak ) ; }
	bool	HT_bGetActionGroup( const int id, int* piGroup )  { return m_kAction.HT_bGetActionGroup( id, piGroup ) ; }
	bool	HT_bGetActionAction( const int id, int* piAction )  { return m_kAction.HT_bGetActionAction( id, piAction ) ; }
	bool	HT_bGetActionSkill( const int id, int* piSkill )  { return m_kAction.HT_bGetActionSkill( id, piSkill ) ; }
	bool	HT_bGetActionState( const int id, int* piState )  { return m_kAction.HT_bGetActionState( id, piState ) ; }
	bool	HT_bGetActionEvent( const int id, int* piEvent )  { return m_kAction.HT_bGetActionEvent( id, piEvent ) ; }

	// Action List
	bool	HT_bGetActionListAction1( const int id, int* piAction1 )  { return m_kActionList.HT_bGetActionListAction1( id, piAction1 ) ; }
	bool	HT_bGetActionListAction2( const int id, int* piAction2 )  { return m_kActionList.HT_bGetActionListAction2( id, piAction2 ) ; }
	bool	HT_bGetActionListAction3( const int id, int* piAction3 )  { return m_kActionList.HT_bGetActionListAction3( id, piAction3 ) ; }

	// Speech Content
	bool	HT_bGetSpeechContentComment1( const int id, int* piComment1 )  { return m_kSpeechContent.HT_bGetSpeechContentComment1( id, piComment1 ) ; }
	bool	HT_bGetSpeechContentComment2( const int id, int* piComment2 )  { return m_kSpeechContent.HT_bGetSpeechContentComment2( id, piComment2 ) ; }
	bool	HT_bGetSpeechContentComment3( const int id, int* piComment3 )  { return m_kSpeechContent.HT_bGetSpeechContentComment3( id, piComment3 ) ; }
	bool	HT_bGetSpeechContentComment4( const int id, int* piComment4 )  { return m_kSpeechContent.HT_bGetSpeechContentComment4( id, piComment4 ) ; }
	bool	HT_bGetSpeechContentComment5( const int id, int* piComment5 )  { return m_kSpeechContent.HT_bGetSpeechContentComment5( id, piComment5 ) ; }
	bool	HT_bGetSpeechContentType1( const int id, int* piType1 )  { return m_kSpeechContent.HT_bGetSpeechContentType1( id, piType1 ) ; }
	bool	HT_bGetSpeechContentType2( const int id, int* piType2 )  { return m_kSpeechContent.HT_bGetSpeechContentType2( id, piType2 ) ; }
	bool	HT_bGetSpeechContentType3( const int id, int* piType3 )  { return m_kSpeechContent.HT_bGetSpeechContentType3( id, piType3 ) ; }
	bool	HT_bGetSpeechContentType4( const int id, int* piType4 )  { return m_kSpeechContent.HT_bGetSpeechContentType4( id, piType4 ) ; }
	bool	HT_bGetSpeechContentType5( const int id, int* piType5 )  { return m_kSpeechContent.HT_bGetSpeechContentType5( id, piType5 ) ; }

	// Speech Comment
	bool	HT_bGetSpeechCommentComment( const int id, char* pComment )  { return m_kSpeechComment.HT_bGetSpeechCommentComment( id, pComment ) ; }

	bool	HT_bGetLevelUpPrana( const int id, int* piPrana )  { return m_kLevelUp.HT_bGetLevelUpPrana( id, piPrana ) ; }
	bool	HT_bGetBramanPointPoint( const int id, int* piPoint )  { return m_kBramanPoint.HT_bGetBramanPointPoint( id, piPoint ) ; }

	// Attack type VS Armor type
	bool	HT_bGetAttackTypeVSArmorTypeDagger( const int id, int* piDagger )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeDagger( id, piDagger ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeSword( const int id, int* piSword )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeSword( id, piSword ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeTwoHandSword( const int id, int* piTwoHandSword )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeTwoHandSword( id, piTwoHandSword ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeAxe( const int id, int* piAxe )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeAxe( id, piAxe ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeTwoHandAxe( const int id, int* piTwoHandAxe )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeTwoHandAxe( id, piTwoHandAxe ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeSpear( const int id, int* piSpear )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeSpear( id, piSpear ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeBow( const int id, int* piBow )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeBow( id, piBow ) ; }	
	bool	HT_bGetAttackTypeVSArmorTypeClaw( const int id, int* piClaw )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeClaw( id, piClaw ) ; }	
	bool	HT_bGetAttackTypeVSArmorTypeBlunt( const int id, int* piBlunt )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeBlunt( id, piBlunt ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeMagic( const int id, int* piMagic )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeMagic( id, piMagic ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeAnimal( const int id, int* piAnimal )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeAnimal( id, piAnimal ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeDemon( const int id, int* piDemon )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeDemon( id, piDemon ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeGolem( const int id, int* piGolem )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeGolem( id, piGolem ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeUndead( const int id, int* piUndead )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeUndead( id, piUndead ) ; }
	bool	HT_bGetAttackTypeVSArmorTypePlant( const int id, int* piPlant )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypePlant( id, piPlant ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeInsect( const int id, int* piInsect )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeInsect( id, piInsect ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid1( const int id, int* piHumanoid1 )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeHumanoid1( id, piHumanoid1 ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid2( const int id, int* piHumanoid2 )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeHumanoid2( id, piHumanoid2 ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid3( const int id, int* piHumanoid3 )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeHumanoid3( id, piHumanoid3 ) ; }
	bool	HT_bGetAttackTypeVSArmorTypeHumanoid4( const int id, int* piHumanoid4 )  { return m_kAttackTypeVSArmorType.HT_bGetAttackTypeVSArmorTypeHumanoid4( id, piHumanoid4 ) ; }

	// Coefficient by Class
	bool	HT_bGetCoefficientByClassClass1( const int id, int* piClass1 )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassClass1( id, piClass1 ) ; }
	bool	HT_bGetCoefficientByClassClass2( const int id, int* piClass2 )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassClass2( id, piClass2 ) ; }
	bool	HT_bGetCoefficientByClassDagger( const int id, int* piDagger )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassDagger( id, piDagger ) ; }
	bool	HT_bGetCoefficientByClassSword( const int id, int* piSword )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassSword( id, piSword ) ; }
	bool	HT_bGetCoefficientByClassTwoHandSword( const int id, int* piTwoHandSword )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassTwoHandSword( id, piTwoHandSword ) ; }
	bool	HT_bGetCoefficientByClassAxe( const int id, int* piAxe )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassAxe( id, piAxe ) ; }
	bool	HT_bGetCoefficientByClassTwoHandAxe( const int id, int* piTwoHandAxe )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassTwoHandAxe( id, piTwoHandAxe ) ; }
	bool	HT_bGetCoefficientByClassBlunt( const int id, int* piBlunt )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassBlunt( id, piBlunt ) ; }
	bool	HT_bGetCoefficientByClassSpear( const int id, int* piSpear )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassSpear( id, piSpear ) ; }
	bool	HT_bGetCoefficientByClassStaff( const int id, int* piStaff )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassStaff( id, piStaff ) ; }
	bool	HT_bGetCoefficientByClassClaw( const int id, int* piClaw )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassClaw( id, piClaw ) ; }
	bool	HT_bGetCoefficientByClassBow( const int id, int* piBow )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassBow( id, piBow ) ; }
	bool	HT_bGetCoefficientByClassThrowing( const int id, int* piThrowing )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassThrowing( id, piThrowing ) ; }
	bool	HT_bGetCoefficientByClassBare( const int id, int* piBare )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassBare( id, piBare ) ; }
	bool	HT_bGetCoefficientByClassShield( const int id, int* piShield )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassShield( id, piShield ) ; }
	bool	HT_bGetCoefficientByClassHP( const int id, int* piHP )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassHP( id, piHP ) ; }
	bool	HT_bGetCoefficientByClassTP( const int id, int* piTP )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassTP( id, piTP ) ; }
	bool	HT_bGetCoefficientByClassRecvry( const int id, int* piRecvry )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassRecvry( id, piRecvry ) ; }
	bool	HT_bGetCoefficientByClassAC( const int id, int* piAC )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassAC( id, piAC ) ; }
	bool	HT_bGetCoefficientByClassResist( const int id, int* piResist )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassResist( id, piResist ) ; }
	bool	HT_bGetCoefficientByClassAttackRate( const int id, int* piAttackRate )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassAttackRate( id, piAttackRate ) ; }
	bool	HT_bGetCoefficientByClassDodgeRate( const int id, int* piDodgeRate )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassDodgeRate( id, piDodgeRate ) ; }
	bool	HT_bGetCoefficientByClassAttackSpeed( const int id, int* piAttackSpeed )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassAttackSpeed( id, piAttackSpeed ) ; }
	bool	HT_bGetCoefficientByClassCastSpeed( const int id, int* piCastSpeed )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassCastSpeed( id, piCastSpeed ) ; }
	bool	HT_bGetCoefficientByClassDodgeSpeed( const int id, int* piDodgeSpeed )  { return m_kCoefficientByClass.HT_bGetCoefficientByClassDodgeSpeed( id, piDodgeSpeed ) ; }

	// Judge combat
	bool	HT_bGetJudgeCombatCriticalPCvsPC( const int id, int* piCriticalPCvsPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatCriticalPCvsPC( id, piCriticalPCvsPC ) ; }
	bool	HT_bGetJudgeCombatNormalPCvsPC( const int id, int* piNormalPCvsPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatNormalPCvsPC( id, piNormalPCvsPC ) ; }
	bool	HT_bGetJudgeCombatMissPCvsPC( const int id, int* piMissPCvsPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatMissPCvsPC( id, piMissPCvsPC ) ; }
	bool	HT_bGetJudgeCombatCriticalPCvsNPC( const int id, int* piCriticalPCvsNPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatCriticalPCvsNPC( id, piCriticalPCvsNPC ) ; }
	bool	HT_bGetJudgeCombatNormalPCvsNPC( const int id, int* piNormalPCvsNPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatNormalPCvsNPC( id, piNormalPCvsNPC ) ; }
	bool	HT_bGetJudgeCombatMissPCvsNPC( const int id, int* piMissPCvsNPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatMissPCvsNPC( id, piMissPCvsNPC ) ; }
	bool	HT_bGetJudgeCombatCriticalNPCvsPC( const int id, int* piCriticalNPCvsPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatCriticalNPCvsPC( id, piCriticalNPCvsPC ) ; }
	bool	HT_bGetJudgeCombatNormalNPCvsPC( const int id, int* piNormalNPCvsPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatNormalNPCvsPC( id, piNormalNPCvsPC ) ; }
	bool	HT_bGetJudgeCombatMissNPCvsPC( const int id, int* piMissNPCvsPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatMissNPCvsPC( id, piMissNPCvsPC ) ; }
	bool	HT_bGetJudgeCombatCriticalNPCvsNPC( const int id, int* piCriticalNPCvsNPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatCriticalNPCvsNPC( id, piCriticalNPCvsNPC ) ; }
	bool	HT_bGetJudgeCombatNormalNPCvsNPC( const int id, int* piNormalNPCvsNPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatNormalNPCvsNPC( id, piNormalNPCvsNPC ) ; }
	bool	HT_bGetJudgeCombatMissNPCvsNPC( const int id, int* piMissNPCvsNPC )  { return m_kJudgeCombat.HT_bGetJudgeCombatMissNPCvsNPC( id, piMissNPCvsNPC ) ; }

	// Consider
	bool	HT_bGetConsiderDFPCvsPC( const int id, int* piDFPCvsPC )  { return m_kConsider.HT_bGetConsiderDFPCvsPC( id, piDFPCvsPC ) ; }
	bool	HT_bGetConsiderRSPCvsPC( const int id, int* piRSPCvsPC )  { return m_kConsider.HT_bGetConsiderRSPCvsPC( id, piRSPCvsPC ) ; }
	bool	HT_bGetConsiderDGPCvsPC( const int id, int* piDGPCvsPC )  { return m_kConsider.HT_bGetConsiderDGPCvsPC( id, piDGPCvsPC ) ; }
	bool	HT_bGetConsiderDFPCvsNPC( const int id, int* piDFPCvsNPC )  { return m_kConsider.HT_bGetConsiderDFPCvsNPC( id, piDFPCvsNPC ) ; }
	bool	HT_bGetConsiderRSPCvsNPC( const int id, int* piRSPCvsNPC )  { return m_kConsider.HT_bGetConsiderRSPCvsNPC( id, piRSPCvsNPC ) ; }
	bool	HT_bGetConsiderDGPCvsNPC( const int id, int* piDGPCvsNPC )  { return m_kConsider.HT_bGetConsiderDGPCvsNPC( id, piDGPCvsNPC ) ; }
	bool	HT_bGetConsiderDFNPCvsPC( const int id, int* piDFNPCvsPC )  { return m_kConsider.HT_bGetConsiderDFNPCvsPC( id, piDFNPCvsPC ) ; }
	bool	HT_bGetConsiderRSNPCvsPC( const int id, int* piRSNPCvsPC )  { return m_kConsider.HT_bGetConsiderRSNPCvsPC( id, piRSNPCvsPC ) ; }
	bool	HT_bGetConsiderDGNPCvsPC( const int id, int* piDGNPCvsPC )  { return m_kConsider.HT_bGetConsiderDGNPCvsPC( id, piDGNPCvsPC ) ; }
	bool	HT_bGetConsiderDFNPCvsNPC( const int id, int* piDFNPCvsNPC )  { return m_kConsider.HT_bGetConsiderDFNPCvsNPC( id, piDFNPCvsNPC ) ; }
	bool	HT_bGetConsiderRSNPCvsNPC( const int id, int* piRSNPCvsNPC )  { return m_kConsider.HT_bGetConsiderRSNPCvsNPC( id, piRSNPCvsNPC ) ; }
	bool	HT_bGetConsiderDGNPCvsNPC( const int id, int* piDGNPCvsNPC )  { return m_kConsider.HT_bGetConsiderDGNPCvsNPC( id, piDGNPCvsNPC ) ; }

	// RvR PK consider
	bool	HT_bGetRvRPKConsiderRewardBP( const int id, int* piRewardBP )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderRewardBP( id, piRewardBP ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste0( const int id, int* piAttackerCaste0 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste0( id, piAttackerCaste0 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste1( const int id, int* piAttackerCaste1 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste1( id, piAttackerCaste1 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste2( const int id, int* piAttackerCaste2 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste2( id, piAttackerCaste2 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste3( const int id, int* piAttackerCaste3 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste3( id, piAttackerCaste3 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste4( const int id, int* piAttackerCaste4 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste4( id, piAttackerCaste4 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste5( const int id, int* piAttackerCaste5 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste5( id, piAttackerCaste5 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste6( const int id, int* piAttackerCaste6 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste6( id, piAttackerCaste6 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste7( const int id, int* piAttackerCaste7 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste7( id, piAttackerCaste7 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste8( const int id, int* piAttackerCaste8 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste8( id, piAttackerCaste8 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste9( const int id, int* piAttackerCaste9 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste9( id, piAttackerCaste9 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste10( const int id, int* piAttackerCaste10 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste10( id, piAttackerCaste10 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste11( const int id, int* piAttackerCaste11 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste11( id, piAttackerCaste11 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste12( const int id, int* piAttackerCaste12 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste12( id, piAttackerCaste12 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste13( const int id, int* piAttackerCaste13 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste13( id, piAttackerCaste13 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste14( const int id, int* piAttackerCaste14 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste14( id, piAttackerCaste14 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste15( const int id, int* piAttackerCaste15 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste15( id, piAttackerCaste15 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste16( const int id, int* piAttackerCaste16 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste16( id, piAttackerCaste16 ) ; }
	bool	HT_bGetRvRPKConsiderAttackerCaste17( const int id, int* piAttackerCaste17 )  { return m_kRvRPKConsider.HT_bGetRvRPKConsiderAttackerCaste17( id, piAttackerCaste17 ) ; }

	// Effect Tolerance
	bool	HT_bGetEffectToleranceClass1( const int id, int* piClass1 )  { return m_kEffectTolerance.HT_bGetEffectToleranceClass1( id, piClass1 ) ; }
	bool	HT_bGetEffectToleranceClass2( const int id, int* piClass2 )  { return m_kEffectTolerance.HT_bGetEffectToleranceClass2( id, piClass2 ) ; }
	bool	HT_bGetEffectToleranceHold( const int id, int* piHold )  { return m_kEffectTolerance.HT_bGetEffectToleranceHold( id, piHold ) ; }
	bool	HT_bGetEffectToleranceStun( const int id, int* piStun )  { return m_kEffectTolerance.HT_bGetEffectToleranceStun( id, piStun ) ; }
	bool	HT_bGetEffectToleranceSleep( const int id, int* piSleep )  { return m_kEffectTolerance.HT_bGetEffectToleranceSleep( id, piSleep ) ; }
	bool	HT_bGetEffectToleranceBlind( const int id, int* piBlind )  { return m_kEffectTolerance.HT_bGetEffectToleranceBlind( id, piBlind ) ; }
	bool	HT_bGetEffectToleranceTerror( const int id, int* piTerror )  { return m_kEffectTolerance.HT_bGetEffectToleranceTerror( id, piTerror ) ; }
	bool	HT_bGetEffectToleranceTaunt( const int id, int* piTaunt )  { return m_kEffectTolerance.HT_bGetEffectToleranceTaunt( id, piTaunt ) ; }
	bool	HT_bGetEffectToleranceSlowMove( const int id, int* piSlowMove )  { return m_kEffectTolerance.HT_bGetEffectToleranceSlowMove( id, piSlowMove ) ; }
	bool	HT_bGetEffectToleranceSlowAttack( const int id, int* piSlowAttack )  { return m_kEffectTolerance.HT_bGetEffectToleranceSlowAttack( id, piSlowAttack ) ; }
	
	// Item by Level
	bool	HT_bGetItemByLevelLvl1( const int id, int* piLvl1 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl1( id, piLvl1 ) ; }
	bool	HT_bGetItemByLevelLvl2( const int id, int* piLvl2 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl2( id, piLvl2 ) ; }
	bool	HT_bGetItemByLevelLvl3( const int id, int* piLvl3 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl3( id, piLvl3 ) ; }
	bool	HT_bGetItemByLevelLvl4( const int id, int* piLvl4 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl4( id, piLvl4 ) ; }
	bool	HT_bGetItemByLevelLvl5( const int id, int* piLvl5 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl5( id, piLvl5 ) ; }
	bool	HT_bGetItemByLevelLvl6( const int id, int* piLvl6 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl6( id, piLvl6 ) ; }
	bool	HT_bGetItemByLevelLvl7( const int id, int* piLvl7 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl7( id, piLvl7 ) ; }
	bool	HT_bGetItemByLevelLvl8( const int id, int* piLvl8 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl8( id, piLvl8 ) ; }
	bool	HT_bGetItemByLevelLvl9( const int id, int* piLvl9 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl9( id, piLvl9 ) ; }
	bool	HT_bGetItemByLevelLvl10( const int id, int* piLvl10 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl10( id, piLvl10 ) ; }
	bool	HT_bGetItemByLevelLvl11( const int id, int* piLvl11 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl11( id, piLvl11 ) ; }
	bool	HT_bGetItemByLevelLvl12( const int id, int* piLvl12 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl12( id, piLvl12 ) ; }
	bool	HT_bGetItemByLevelLvl13( const int id, int* piLvl13 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl13( id, piLvl13 ) ; }
	bool	HT_bGetItemByLevelLvl14( const int id, int* piLvl14 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl14( id, piLvl14 ) ; }
	bool	HT_bGetItemByLevelLvl15( const int id, int* piLvl15 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl15( id, piLvl15 ) ; }
	bool	HT_bGetItemByLevelLvl16( const int id, int* piLvl16 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl16( id, piLvl16 ) ; }
	bool	HT_bGetItemByLevelLvl17( const int id, int* piLvl17 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl17( id, piLvl17 ) ; }
	bool	HT_bGetItemByLevelLvl18( const int id, int* piLvl18 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl18( id, piLvl18 ) ; }
	bool	HT_bGetItemByLevelLvl19( const int id, int* piLvl19 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl19( id, piLvl19 ) ; }
	bool	HT_bGetItemByLevelLvl20( const int id, int* piLvl20 )  { return m_kItemByLevel.HT_bGetItemByLevelLvl20( id, piLvl20 ) ; }

	// Item rate by Monster Level
	bool	HT_bGetItemRateByMonLevelLvl1( const int id, int* piLvl1 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl1( id, piLvl1 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl2( const int id, int* piLvl2 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl2( id, piLvl2 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl3( const int id, int* piLvl3 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl3( id, piLvl3 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl4( const int id, int* piLvl4 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl4( id, piLvl4 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl5( const int id, int* piLvl5 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl5( id, piLvl5 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl6( const int id, int* piLvl6 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl6( id, piLvl6 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl7( const int id, int* piLvl7 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl7( id, piLvl7 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl8( const int id, int* piLvl8 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl8( id, piLvl8 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl9( const int id, int* piLvl9 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl9( id, piLvl9 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl10( const int id, int* piLvl10 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl10( id, piLvl10 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl11( const int id, int* piLvl11 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl11( id, piLvl11 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl12( const int id, int* piLvl12 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl12( id, piLvl12 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl13( const int id, int* piLvl13 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl13( id, piLvl13 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl14( const int id, int* piLvl14 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl14( id, piLvl14 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl15( const int id, int* piLvl15 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl15( id, piLvl15 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl16( const int id, int* piLvl16 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl16( id, piLvl16 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl17( const int id, int* piLvl17 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl17( id, piLvl17 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl18( const int id, int* piLvl18 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl18( id, piLvl18 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl19( const int id, int* piLvl19 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl19( id, piLvl19 ) ; }
	bool	HT_bGetItemRateByMonLevelLvl20( const int id, int* piLvl20 )  { return m_kItemRateByMonLevel.HT_bGetItemRateByMonLevelLvl20( id, piLvl20 ) ; }

	bool	HT_bGetItemRateByMonLevelForTestSrvLvl1( const int id, int* piLvl1 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl1( id, piLvl1 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl2( const int id, int* piLvl2 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl2( id, piLvl2 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl3( const int id, int* piLvl3 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl3( id, piLvl3 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl4( const int id, int* piLvl4 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl4( id, piLvl4 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl5( const int id, int* piLvl5 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl5( id, piLvl5 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl6( const int id, int* piLvl6 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl6( id, piLvl6 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl7( const int id, int* piLvl7 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl7( id, piLvl7 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl8( const int id, int* piLvl8 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl8( id, piLvl8 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl9( const int id, int* piLvl9 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl9( id, piLvl9 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl10( const int id, int* piLvl10 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl10( id, piLvl10 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl11( const int id, int* piLvl11 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl11( id, piLvl11 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl12( const int id, int* piLvl12 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl12( id, piLvl12 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl13( const int id, int* piLvl13 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl13( id, piLvl13 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl14( const int id, int* piLvl14 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl14( id, piLvl14 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl15( const int id, int* piLvl15 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl15( id, piLvl15 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl16( const int id, int* piLvl16 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl16( id, piLvl16 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl17( const int id, int* piLvl17 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl17( id, piLvl17 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl18( const int id, int* piLvl18 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl18( id, piLvl18 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl19( const int id, int* piLvl19 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl19( id, piLvl19 ) ; }
	bool	HT_bGetItemRateByMonLevelForTestSrvLvl20( const int id, int* piLvl20 )  { return m_kItemRateByMonLevelForTestSrv.HT_bGetItemRateByMonLevelForTestSrvLvl20( id, piLvl20 ) ; }

	// Item Group
	bool	HT_bGetItemGroupGroup( const int id, int* piGroup )  { return m_kItemGroup.HT_bGetItemGroupGroup( id, piGroup ) ; }
	bool	HT_bGetItemGroupItemID( const int id, int* piItemID )  { return m_kItemGroup.HT_bGetItemGroupItemID( id, piItemID ) ; }

	// kala altar
	bool	HT_bGetKalaAltarZone( const int id, int* piZone )  { return m_kKalaAltar.HT_bGetKalaAltarZone( id, piZone ) ; }
	bool	HT_bGetKalaAltarClan( const int id, int* piClan )  { return m_kKalaAltar.HT_bGetKalaAltarClan( id, piClan ) ; }
	bool	HT_bGetKalaAltarX( const int id, int* piX )  { return m_kKalaAltar.HT_bGetKalaAltarX( id, piX ) ; }
	bool	HT_bGetKalaAltarY( const int id, int* piY )  { return m_kKalaAltar.HT_bGetKalaAltarY( id, piY ) ; }

	// rewarder position
	bool	HT_bGetRewarderPositionZone( const int id, int* piZone )  { return m_kKalaRewarderPosition.HT_bGetRewarderPositionZone( id, piZone ) ; }
	bool	HT_bGetRewarderPositionNPCIndex( const int id, int* piNPCIndex )  { return m_kKalaRewarderPosition.HT_bGetRewarderPositionNPCIndex( id, piNPCIndex ) ; }
	bool	HT_bGetRewarderPositionClan( const int id, int* piClan )  { return m_kKalaRewarderPosition.HT_bGetRewarderPositionClan( id, piClan ) ; }
	bool	HT_bGetRewarderPositionX( const int id, int* piX )  { return m_kKalaRewarderPosition.HT_bGetRewarderPositionX( id, piX ) ; }
	bool	HT_bGetRewarderPositionY( const int id, int* piY )  { return m_kKalaRewarderPosition.HT_bGetRewarderPositionY( id, piY ) ; }

	// rate by item category
	bool	HT_bGetRateByItemCategoryRate( const int id, int* piRate )  { return m_kRateByItemCategory.HT_bGetRateByItemCategoryRate( id, piRate ) ; }

	// event list
	bool	HT_bGetEventListZone( const int id, int* piZone )  { return m_kEventList.HT_bGetEventListZone( id, piZone ) ; }
	bool	HT_bGetEventListEventID( const int id, int* piEventID )  { return m_kEventList.HT_bGetEventListEventID( id, piEventID ) ; }
	bool	HT_bGetEventListTask1( const int id, int* piTask1 )  { return m_kEventList.HT_bGetEventListTask1( id, piTask1 ) ; }
	bool	HT_bGetEventListTask2( const int id, int* piTask2 )  { return m_kEventList.HT_bGetEventListTask2( id, piTask2 ) ; }
	bool	HT_bGetEventListTask3( const int id, int* piTask3 )  { return m_kEventList.HT_bGetEventListTask3( id, piTask3 ) ; }
	bool	HT_bGetEventListTask4( const int id, int* piTask4 )  { return m_kEventList.HT_bGetEventListTask4( id, piTask4 ) ; }
	bool	HT_bGetEventListTask5( const int id, int* piTask5 )  { return m_kEventList.HT_bGetEventListTask5( id, piTask5 ) ; }
	bool	HT_bGetEventListCoolDownTime( const int id, int* puiCoolDownTime )  { return m_kEventList.HT_bGetEventListCoolDownTime( id, puiCoolDownTime ) ; }
	bool	HT_bGetEventListCount( const int id, int* piCount )  { return m_kEventList.HT_bGetEventListCount( id, piCount ) ; }
	bool	HT_bGetEventListProceedType( const int id, int* piProceedType )  { return m_kEventList.HT_bGetEventListProceedType( id, piProceedType ) ; }
	bool	HT_bGetEventListDuration( const int id, int* piDuration )  { return m_kEventList.HT_bGetEventListDuration( id, piDuration ) ; }	

	// task list
	bool	HT_bGetTaskListZone( const int id, int* piZone )  { return m_kTaskList.HT_bGetTaskListZone( id, piZone ) ; }
	bool	HT_bGetTaskListTaskID( const int id, int* piTaskID )  { return m_kTaskList.HT_bGetTaskListTaskID( id, piTaskID ) ; }
	bool	HT_bGetTaskListActionID( const int id, int* piActionID )  { return m_kTaskList.HT_bGetTaskListActionID( id, piActionID ) ; }
	bool	HT_bGetTaskListParam1( const int id, int* piParam1 )  { return m_kTaskList.HT_bGetTaskListParam1( id, piParam1 ) ; }
	bool	HT_bGetTaskListParam2( const int id, int* piParam2 )  { return m_kTaskList.HT_bGetTaskListParam2( id, piParam2 ) ; }
	bool	HT_bGetTaskListParam3( const int id, int* piParam3 )  { return m_kTaskList.HT_bGetTaskListParam3( id, piParam3 ) ; }
	bool	HT_bGetTaskListParam4( const int id, int* piParam4 )  { return m_kTaskList.HT_bGetTaskListParam4( id, piParam4 ) ; }
	bool	HT_bGetTaskListParam5( const int id, int* piParam5 )  { return m_kTaskList.HT_bGetTaskListParam5( id, piParam5 ) ; }
	bool	HT_bGetTaskListParam6( const int id, int* piParam6 )  { return m_kTaskList.HT_bGetTaskListParam6( id, piParam6 ) ; }

	// event schedule
	bool	HT_bGetEventScheduleZone( const int id, int* piZone )  { return m_kEventSchedule.HT_bGetEventScheduleZone( id, piZone ) ; } // sequence id
	bool	HT_bGetEventScheduleMin( const int id, int* piMin )  { return m_kEventSchedule.HT_bGetEventScheduleMin( id, piMin ) ; }
	bool	HT_bGetEventScheduleSec( const int id, int* piSec )  { return m_kEventSchedule.HT_bGetEventScheduleSec( id, piSec ) ; }
	bool	HT_bGetEventScheduleEvent( const int id, int* piEvent )  { return m_kEventSchedule.HT_bGetEventScheduleEvent( id, piEvent ) ; }

	// game event schedule
	bool	HT_bGetGameEventID	   ( const int id, int* piEventID)	{ return m_kGameEvent.HT_bGetGameEventID	 ( id, piEventID); }
	bool	HT_bGetGameEventType   ( const int id, int* piType)		{ return m_kGameEvent.HT_bGetGameEventType	 ( id, piType); }
	bool	HT_bGetGameEventTarget ( const int id, int* piTarget)	{ return m_kGameEvent.HT_bGetGameEventTarget ( id, piTarget); }
	bool	HT_bGetGameEventZone   ( const int id, int* piZone )	{ return m_kGameEvent.HT_bGetGameEventZone   ( id, piZone ); }
	bool	HT_bGetGameEventAction1( const int id, int* piAction)	{ return m_kGameEvent.HT_bGetGameEventAction1( id, piAction); }
	bool	HT_bGetGameEventParam11( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam11( id, piParam); }
	bool	HT_bGetGameEventParam12( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam12( id, piParam); }
	bool	HT_bGetGameEventAction2( const int id, int* piAction )	{ return m_kGameEvent.HT_bGetGameEventAction2( id, piAction); }
	bool	HT_bGetGameEventParam21( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam21( id, piParam); }
	bool	HT_bGetGameEventParam22( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam22( id, piParam); }
	bool	HT_bGetGameEventAction3( const int id, int* piAction )	{ return m_kGameEvent.HT_bGetGameEventAction3( id, piAction); }
	bool	HT_bGetGameEventParam31( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam31( id, piParam); }
	bool	HT_bGetGameEventParam32( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam32( id, piParam); }
	bool	HT_bGetGameEventAction4( const int id, int* piAction )	{ return m_kGameEvent.HT_bGetGameEventAction4( id, piAction); }
	bool	HT_bGetGameEventParam41( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam41( id, piParam); }
	bool	HT_bGetGameEventParam42( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam42( id, piParam); }
	bool	HT_bGetGameEventAction5( const int id, int* piAction )	{ return m_kGameEvent.HT_bGetGameEventAction5( id, piAction); }
	bool	HT_bGetGameEventParam51( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam51( id, piParam); }
	bool	HT_bGetGameEventParam52( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam52( id, piParam); }
	bool	HT_bGetGameEventAction6( const int id, int* piAction )	{ return m_kGameEvent.HT_bGetGameEventAction6( id, piAction); }
	bool	HT_bGetGameEventParam61( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam61( id, piParam); }
	bool	HT_bGetGameEventParam62( const int id, int* piParam )	{ return m_kGameEvent.HT_bGetGameEventParam62( id, piParam); }

	// Set item
	bool	HT_bGetSetItemID( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemID( id, piParam); }
	bool	HT_bGetSetItemHelmet( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemHelmet( id, piParam); }
	bool	HT_bGetSetItemNecklace( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemNecklace( id, piParam); }
	bool	HT_bGetSetItemArmor( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemArmor( id, piParam); }
	bool	HT_bGetSetItemBelt( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemBelt( id, piParam); }
	bool	HT_bGetSetItemWeapon( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemWeapon( id, piParam); }
	bool	HT_bGetSetItemShield( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemShield( id, piParam); }
	bool	HT_bGetSetItemBoots( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemBoots( id, piParam); }
	bool	HT_bGetSetItemGloves( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemGloves( id, piParam); }
	bool	HT_bGetSetItemPants( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemPants( id, piParam); }
	bool	HT_bGetSetItemEffectItem( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemEffectItem( id, piParam); }
	bool	HT_bGetSetItemEffectItem2( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemEffectItem2( id, piParam); }
#ifndef __BEFORE_SET_ITEM_EXPANDED__
	bool	HT_bGetSetItemEffectItem3( const int id, int* piParam ) { return m_kSetItem.HT_bGetSetItemEffectItem3( id, piParam); }
#endif

private :
	CHTAIListTable m_kAIList ;
	CHTActionTable m_kAction ;
	CHTActionListTable m_kActionList ;
	CHTSpeechContentTable m_kSpeechContent ;
	CHTSpeechCommentTable m_kSpeechComment ;
	CHTLevelUpTable m_kLevelUp ;
	CHTBramanPointTable m_kBramanPoint ;
	CHTAttackTypeVSArmorTypeTable m_kAttackTypeVSArmorType ;
	CHTCoefficientByClassTable m_kCoefficientByClass ;
	CHTJudgeCombatTable m_kJudgeCombat ;
	CHTConsiderTable m_kConsider ;
	CHTRvRPKConsiderTable m_kRvRPKConsider ;
	CHTEffectToleranceTable m_kEffectTolerance ;
	CHTKalaAltarTable m_kKalaAltar ;
	CHTKalaRewarderPositionTable m_kKalaRewarderPosition ;	
	CHTEventListTable m_kEventList ;
	CHTTaskListTable m_kTaskList ;
	CHTEventScheduleTable m_kEventSchedule ;
	CHTItemRateByMonLevelTable m_kItemRateByMonLevel ;
	CHTItemRateByMonLevelForTestSrvTable m_kItemRateByMonLevelForTestSrv ;
	CHTItemByLevelTable m_kItemByLevel ;
	CHTItemGroupTable m_kItemGroup ;
	CHTRateByItemCategoryTable m_kRateByItemCategory ;
	CHTGameEventTable m_kGameEvent;
	CHTSetItemTable m_kSetItem;


	// 다음 배열은 전체 테이블을 가지고 있는 배열이다.
	//CHTBaseSSettingTable*	m_arrParamTable[255];
	CHTString		m_szLanguage;
};

//extern CHTSSettingMgr* g_pkSettingMgr ;


#endif