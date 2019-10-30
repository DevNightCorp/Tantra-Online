#ifndef _HTFXRESMGR_H_
#define _HTFXRESMGR_H_

class CHTXMLParser;

//-------------------------------------------------------------------------------------
// 이름 : 역참조 비교연산자형 선언
// 설명 : STL의 map에 첫번째인 키값이 스트링포인터이기때문에 비교형이 선언되어야
// 제대로 값들이 정렬되어 들어가고, 찾을 수 있다. 그렇지 않으면 포인터값으로
// 비교를 하게되는 상황이 벌어진다. 
typedef struct _HTFXDerefLessStr
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
} HTFXDerefLessStr;

class CHTFXBaseResTable
{
public:
	CHTFXBaseResTable();
	virtual ~CHTFXBaseResTable();

	virtual HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable ) = 0;
	virtual HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable ) = 0;
	virtual HTRESULT	HT_hrSave( CHTFile* pFile ) = 0;
	virtual HTdword		HT_dwGetIDByIndex( HTuint idxRow ) = 0;

	// For PC Skill, Monster Skill
	virtual	HTbool		HT_bGetSkillID( HTdword dwID, HTdword& dwSkillID );
	virtual HTbool		HT_bGetUI( HTdword dwID, HTdword& dwUI );
	virtual HTbool		HT_bGetReadyFX( HTdword dwID, HTdword& dwFX );
	virtual HTbool		HT_bGetCastFX( HTdword dwID, HTdword& dwFX );
	virtual HTbool		HT_bGetActivateFX( HTdword dwID, HTdword& dwFX );
	virtual HTbool		HT_bGetFollowFX( HTdword dwID, HTdword& dwFX );
	virtual HTbool		HT_bGetImpactFX( HTdword dwID, HTdword& dwFX );
	virtual HTbool		HT_bGetStateFX( HTdword dwID, HTdword& dwFX );
	virtual HTbool		HT_bGetIsWeaponBack( HTdword dwID, HTbool& bIsWeaponBack );
	virtual HTbool		HT_bGetSkillActionAniReadyMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniCastMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniActivateMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniReadyMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniCastMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniActivateMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniReadyMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniCastMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniActivateMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniReadyManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniCastManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniActivateManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniReadyWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniCastWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniActivateWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniReadyWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniCastWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniActivateWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniReadyWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniCastWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniActivateWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniReadyWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniCastWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniActivateWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActionAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );

	virtual HTbool		HT_bGetSkillActionSoundActivateMan( HTdword dwID, HTdword& dwSound );
	virtual HTbool		HT_bGetSkillActionSoundActivateWom( HTdword dwID, HTdword& dwSound );

	virtual HTbool		HT_bGetSkillActiveAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );	
	virtual HTbool		HT_bGetSkillActiveAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActiveAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActiveAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActiveAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	virtual HTbool		HT_bGetSkillActiveAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );

	virtual HTbool		HT_bGetSkillType( HTdword dwID, HTdword& dwType );
	virtual HTbool		HT_bGetSkillAni( HTdword dwID, HTdword& dwAni );

	// For PC FX
	virtual HTbool		HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwCategory, HTdword& dwWhereAttach, HTdword& dwPriority );

	// For String
	virtual HTbool		HT_bGetName( HTdword dwID, CHTString& strName );
	virtual HTbool		HT_bGetDesc( HTdword dwID, CHTString& strDesc );

	// For Monster Effect
	virtual HTbool		HT_bGetBornFX( HTdword dwID, HTdword& dwFX );
	virtual HTbool		HT_bGetDieActivateFX( HTdword dwID, HTdword& dwFX );
	virtual HTbool		HT_bGetAlwaysFX( HTdword dwID, HTdword& dwFX );

	// For Monster FX, Field FX
	virtual HTbool		HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwWhereAttach, HTdword& dwPriority );

			HTuint		HT_nGetItemCount()		{ return m_nItems; };
			CHTString&	HT_strGetTableName()	{ return m_strTable; };

protected:
	CHTString			m_strTable;
	HTuint				m_nItems;
};

class CHTFXResTablePCSkill : public CHTFXBaseResTable
{
public:
	CHTFXResTablePCSkill();
	~CHTFXResTablePCSkill();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );

	HTRESULT	HT_hrSave( CHTFile* pFile );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetDesc( HTdword dwID, CHTString& strDesc );
	HTbool		HT_bGetSkillID( HTdword dwID, HTdword& dwSkillID );
	HTbool		HT_bGetUI( HTdword dwID, HTdword& dwUI );

private:
	typedef struct _HTResTablePCSkillLS
	{
		HTtchar		szName[100];
		HTtchar		szDesc[100];
		HTdword		dwSkillID;
        HTdword		dwUI;
	} HTResTablePCSkillLS;

	typedef struct _HTResTablePCSkill
	{
		CHT_DATA_STR	strName;
		CHT_DATA_STR	strDesc;
		HTdword			dwSkillID;
        HTdword			dwUI;
	} HTResTablePCSkill;

	typedef std::map<HTdword,HTResTablePCSkill*>				HTResTablePCSkill_Map;
	typedef std::map<HTdword,HTResTablePCSkill*>::value_type	HTResTablePCSkill_Value;
	typedef std::map<HTdword,HTResTablePCSkill*>::iterator		HTResTablePCSkill_It;

	HTResTablePCSkill_Map m_mapTable;
};

class CHTFXResTablePCSkillAction : public CHTFXBaseResTable
{
public:
	CHTFXResTablePCSkillAction();
	~CHTFXResTablePCSkillAction();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetSkillType( HTdword dwID, HTdword& dwType );
	HTbool		HT_bGetReadyFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetCastFX( HTdword dwID, HTdword& dwCastFX );
	HTbool		HT_bGetActivateFX( HTdword dwID, HTdword& dwActivateFX );
	HTbool		HT_bGetFollowFX( HTdword dwID, HTdword& dwFollowFX );
	HTbool		HT_bGetImpactFX( HTdword dwID, HTdword& dwImpactFX );
	HTbool		HT_bGetIsWeaponBack( HTdword dwID, HTbool& bIsWeaponBack );
	// 한손
	HTbool		HT_bGetSkillActionAniReadyMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	// 양손 장검
	HTbool		HT_bGetSkillActionAniReadyMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	// 양손 도끼
	HTbool		HT_bGetSkillActionAniReadyMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	// 활
	HTbool		HT_bGetSkillActionAniReadyManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	// 주먹
	HTbool		HT_bGetSkillActionAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	// 한손
	HTbool		HT_bGetSkillActionAniReadyWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	// 양손 장검
	HTbool		HT_bGetSkillActionAniReadyWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	// 양손 도끼
	HTbool		HT_bGetSkillActionAniReadyWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	// 활
	HTbool		HT_bGetSkillActionAniReadyWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	// 주먹
	HTbool		HT_bGetSkillActionAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );

	// 사운드
	HTbool		HT_bGetSkillActionSoundActivateMan( HTdword dwID, HTdword& dwSound );
	HTbool		HT_bGetSkillActionSoundActivateWom( HTdword dwID, HTdword& dwSound );

private:
	typedef struct _HTResTablePCSkillAction
	{
		HTdword		dwType;
		HTdword		dwReadyFX;
		HTdword		dwCastFX;
		HTdword		dwActivateFX;
		HTdword		dwFollowFX;
		HTdword		dwImpactFX;
		HTbool		bIsWeaponBack;
		// 한손	
		HTdword		dwAniMan1HReady;
		HTdword		dwAniMan1HReadyFApron;
		HTdword		dwAniMan1HReadyBApron;
		HTdword		dwAniMan1HCast;
		HTdword		dwAniMan1HCastFApron;
		HTdword		dwAniMan1HCastBApron;
		HTdword		dwAniMan1HAtv;
		HTdword		dwAniMan1HAtvFApron;
		HTdword		dwAniMan1HAtvBApron;
		// 두손 장검
		HTdword		dwAniMan2HSwordReady;
		HTdword		dwAniMan2HSwordReadyFApron;
		HTdword		dwAniMan2HSwordReadyBApron;
		HTdword		dwAniMan2HSwordCast;
		HTdword		dwAniMan2HSwordCastFApron;
		HTdword		dwAniMan2HSwordCastBApron;
		HTdword		dwAniMan2HSwordAtv;
		HTdword		dwAniMan2HSwordAtvFApron;
		HTdword		dwAniMan2HSwordAtvBApron;
		// 두손 도끼
		HTdword		dwAniMan2HAxeReady;
		HTdword		dwAniMan2HAxeReadyFApron;
		HTdword		dwAniMan2HAxeReadyBApron;
		HTdword		dwAniMan2HAxeCast;
		HTdword		dwAniMan2HAxeCastFApron;
		HTdword		dwAniMan2HAxeCastBApron;
		HTdword		dwAniMan2HAxeAtv;
		HTdword		dwAniMan2HAxeAtvFApron;
		HTdword		dwAniMan2HAxeAtvBApron;
		// 활
		HTdword		dwAniManBowReady;
		HTdword		dwAniManBowReadyFApron;
		HTdword		dwAniManBowReadyBApron;
		HTdword		dwAniManBowCast;
		HTdword		dwAniManBowCastFApron;
		HTdword		dwAniManBowCastBApron;
		HTdword		dwAniManBowAtv;
		HTdword		dwAniManBowAtvFApron;
		HTdword		dwAniManBowAtvBApron;
		// 주먹
		HTdword		dwAniManFistReady;
		HTdword		dwAniManFistReadyFApron;
		HTdword		dwAniManFistReadyBApron;
		HTdword		dwAniManFistCast;
		HTdword		dwAniManFistCastFApron;
		HTdword		dwAniManFistCastBApron;
		HTdword		dwAniManFistAtv;
		HTdword		dwAniManFistAtvFApron;
		HTdword		dwAniManFistAtvBApron;
		// 한손
		HTdword		dwAniWom1HReady;
		HTdword		dwAniWom1HReadyFApron;
		HTdword		dwAniWom1HReadyBApron;
		HTdword		dwAniWom1HCast;
		HTdword		dwAniWom1HCastFApron;
		HTdword		dwAniWom1HCastBApron;
		HTdword		dwAniWom1HAtv;
		HTdword		dwAniWom1HAtvFApron;
		HTdword		dwAniWom1HAtvBApron;
		// 두손 장검
		HTdword		dwAniWom2HSwordReady;
		HTdword		dwAniWom2HSwordReadyFApron;
		HTdword		dwAniWom2HSwordReadyBApron;
		HTdword		dwAniWom2HSwordCast;
		HTdword		dwAniWom2HSwordCastFApron;
		HTdword		dwAniWom2HSwordCastBApron;
		HTdword		dwAniWom2HSwordAtv;
		HTdword		dwAniWom2HSwordAtvFApron;
		HTdword		dwAniWom2HSwordAtvBApron;
		// 두손 도끼
		HTdword		dwAniWom2HAxeReady;
		HTdword		dwAniWom2HAxeReadyFApron;
		HTdword		dwAniWom2HAxeReadyBApron;
		HTdword		dwAniWom2HAxeCast;
		HTdword		dwAniWom2HAxeCastFApron;
		HTdword		dwAniWom2HAxeCastBApron;
		HTdword		dwAniWom2HAxeAtv;
		HTdword		dwAniWom2HAxeAtvFApron;
		HTdword		dwAniWom2HAxeAtvBApron;
		// 활
		HTdword		dwAniWomBowReady;
		HTdword		dwAniWomBowReadyFApron;
		HTdword		dwAniWomBowReadyBApron;
		HTdword		dwAniWomBowCast;
		HTdword		dwAniWomBowCastFApron;
		HTdword		dwAniWomBowCastBApron;
		HTdword		dwAniWomBowAtv;
		HTdword		dwAniWomBowAtvFApron;
		HTdword		dwAniWomBowAtvBApron;
		// 주먹
		HTdword		dwAniWomFistReady;
		HTdword		dwAniWomFistReadyFApron;
		HTdword		dwAniWomFistReadyBApron;
		HTdword		dwAniWomFistCast;
		HTdword		dwAniWomFistCastFApron;
		HTdword		dwAniWomFistCastBApron;
		HTdword		dwAniWomFistAtv;
		HTdword		dwAniWomFistAtvFApron;
		HTdword		dwAniWomFistAtvBApron;

		// 공격시 나는 사운드
		HTdword		dwSoundManActivate;
		HTdword		dwSoundWomActivate;
	} HTResTablePCSkillAction;

	typedef std::map<HTdword,HTResTablePCSkillAction*>				HTResTablePCSkillAction_Map;
	typedef std::map<HTdword,HTResTablePCSkillAction*>::value_type	HTResTablePCSkillAction_Value;
	typedef std::map<HTdword,HTResTablePCSkillAction*>::iterator	HTResTablePCSkillAction_It;

	HTResTablePCSkillAction_Map m_mapTable;
};

class CHTFXResTablePCSkillActive : public CHTFXBaseResTable
{
public:
	CHTFXResTablePCSkillActive();
	~CHTFXResTablePCSkillActive();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetSkillType( HTdword dwID, HTdword& dwType );
	HTbool		HT_bGetReadyFX( HTdword dwID, HTdword& dwReadyFX );
	HTbool		HT_bGetCastFX( HTdword dwID, HTdword& dwCastFX );
	HTbool		HT_bGetActivateFX( HTdword dwID, HTdword& dwActivateFX );
	HTbool		HT_bGetStateFX( HTdword dwID, HTdword& dwStateFX );
	HTbool		HT_bGetSkillActiveAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActiveAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActiveAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActiveAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActiveAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActiveAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );

private:
	typedef struct _HTResTablePCSkillActive
	{
		HTdword		dwType;
		HTdword		dwReadyFX;
		HTdword		dwCastFX;
		HTdword		dwActivateFX;
		HTdword		dwStateFX;
		HTdword		dwAniManFistReady;
		HTdword		dwAniManFistReadyFApron;
		HTdword		dwAniManFistReadyBApron;
		HTdword		dwAniManFistCast;
		HTdword		dwAniManFistCastFApron;
		HTdword		dwAniManFistCastBApron;
		HTdword		dwAniManFistActivate;
		HTdword		dwAniManFistActivateFApron;
		HTdword		dwAniManFistActivateBApron;
		HTdword		dwAniWomFistReady;
		HTdword		dwAniWomFistReadyFApron;
		HTdword		dwAniWomFistReadyBApron;
		HTdword		dwAniWomFistCast;
		HTdword		dwAniWomFistCastFApron;
		HTdword		dwAniWomFistCastBApron;
		HTdword		dwAniWomFistActivate;
		HTdword		dwAniWomFistActivateFApron;
		HTdword		dwAniWomFistActivateBApron;
	} HTResTablePCSkillActive;

	typedef std::map<HTdword,HTResTablePCSkillActive*>				HTResTablePCSkillActive_Map;
	typedef std::map<HTdword,HTResTablePCSkillActive*>::value_type	HTResTablePCSkillActive_Value;
	typedef std::map<HTdword,HTResTablePCSkillActive*>::iterator	HTResTablePCSkillActive_It;

	HTResTablePCSkillActive_Map m_mapTable;
};

class CHTFXResTablePCFX : public CHTFXBaseResTable
{
public:
	CHTFXResTablePCFX();
	~CHTFXResTablePCFX();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwCategory, HTdword& dwWhereAttach, HTdword& dwPriority );

private:
	typedef struct _HTResTablePCFX
	{
		HTdword		dwCategory;
		CHTString	strFXName;
		HTdword		dwWhereAttach;
		HTdword		dwPriority;
	} HTResTablePCFX;

	typedef std::map<HTdword,HTResTablePCFX*>				HTResTablePCFX_Map;
	typedef std::map<HTdword,HTResTablePCFX*>::value_type	HTResTablePCFX_Value;
	typedef std::map<HTdword,HTResTablePCFX*>::iterator		HTResTablePCFX_It;

	HTResTablePCFX_Map m_mapTable;
};

class CHTFXResTableString : public CHTFXBaseResTable
{
public:
	CHTFXResTableString();
	~CHTFXResTableString();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetName( HTdword dwID, CHTString& strName );

private:
	typedef struct _HTResTableString
	{
		CHTString	strName;
	} HTResTableString;

	typedef std::map<HTdword,HTResTableString*>				HTResTableString_Map;
	typedef std::map<HTdword,HTResTableString*>::value_type	HTResTableString_Value;
	typedef std::map<HTdword,HTResTableString*>::iterator	HTResTableString_It;

	HTResTableString_Map m_mapTable;
};

class CHTFXResTableMONSkill : public CHTFXBaseResTable
{
public:
	CHTFXResTableMONSkill();
	~CHTFXResTableMONSkill();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetSkillType( HTdword dwID, HTdword& dwType );
	HTbool		HT_bGetCastFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetActivateFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetFollowFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetImpactFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetStateFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetSkillAni( HTdword dwID, HTdword& dwAni );

private:
	typedef struct _HTResTableMONSkill
	{
		HTdword		dwType;
		HTdword		dwCastFX;
		HTdword		dwActivateFX;
		HTdword		dwFollowFX;
		HTdword		dwImpactFX;
		HTdword		dwStateFX;
		HTdword		dwSkillAni;
	} HTResTableMONSkill;

	typedef std::map<HTdword,HTResTableMONSkill*>				HTResTableMONSkill_Map;
	typedef std::map<HTdword,HTResTableMONSkill*>::value_type	HTResTableMONSkill_Value;
	typedef std::map<HTdword,HTResTableMONSkill*>::iterator		HTResTableMONSkill_It;

	HTResTableMONSkill_Map m_mapTable;
};

class CHTFXResTableMONEffect : public CHTFXBaseResTable
{
public:
	CHTFXResTableMONEffect();
	~CHTFXResTableMONEffect();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetBornFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetDieActivateFX( HTdword dwID, HTdword& dwFX );
	// Die Effect는 Activate, Follow, Die로 구성된다.
	// FollowFXID = ActivateFXID + 1, ImpactFXID = ActivateFXID + 2;
	HTbool		HT_bGetAlwaysFX( HTdword dwID, HTdword& dwFX );

private:
	typedef struct _HTResTableMONEffect
	{
		HTdword		dwBornFX;
		HTdword		dwAlwaysFX;
		HTdword		dwDieFX;
	} HTResTableMONEffect;

	typedef std::map<HTdword,HTResTableMONEffect*>				HTResTableMONEffect_Map;
	typedef std::map<HTdword,HTResTableMONEffect*>::value_type	HTResTableMONEffect_Value;
	typedef std::map<HTdword,HTResTableMONEffect*>::iterator	HTResTableMONEffect_It;

	HTResTableMONEffect_Map m_mapTable;
};

class CHTFXResTableMONFX : public CHTFXBaseResTable
{
public:
	CHTFXResTableMONFX();
	~CHTFXResTableMONFX();

	HTRESULT	HT_hrLoad( CHTXMLParser* pXML, CHTString& strTable );
	HTRESULT	HT_hrLoad( CHTFile* pFile, CHTString& strTable );
	HTRESULT	HT_hrSave( CHTFile* pFile );
	HTdword		HT_dwGetIDByIndex( HTuint idxRow );

	HTbool		HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwWhereAttach, HTdword& dwPriority );

private:
	typedef struct _HTResTableMONFX
	{
		CHTString	strFXName;
		HTdword		dwWhereAttach;
		HTdword		dwPriority;
	} HTResTableMONFX;

	typedef std::map<HTdword,HTResTableMONFX*>				HTResTableMONFX_Map;
	typedef std::map<HTdword,HTResTableMONFX*>::value_type	HTResTableMONFX_Value;
	typedef std::map<HTdword,HTResTableMONFX*>::iterator	HTResTableMONFX_It;

	HTResTableMONFX_Map m_mapTable;
};

typedef std::map<HTtchar*,CHTFXBaseResTable*,HTFXDerefLessStr>				HTFXResTable_Map;
typedef std::map<HTtchar*,CHTFXBaseResTable*,HTFXDerefLessStr>::value_type	HTFXResTable_Value;
typedef std::map<HTtchar*,CHTFXBaseResTable*,HTFXDerefLessStr>::iterator	HTFXResTable_It;

class CHTFXPCResMgr
{
public:
	CHTFXPCResMgr();
	~CHTFXPCResMgr();

	HTRESULT	HT_hrLoad( CHTString& strFile );
	HTRESULT	HT_hrUnload();
	HTRESULT	HT_hrSave( CHTString& strFile );

	HTtchar*	HT_pGetTableName( HTdword dwID );
	CHTFXBaseResTable* HT_pGetTable( HTdword dwID );

	HTdword		HT_dwGetIDByIndex( CHTString& strTable, HTuint idxRow );
	HTuint		HT_nGetItemCount( CHTString& strTable );

	HTbool		HT_bGetSkillType( HTdword dwID, HTdword& dwType );
	HTbool		HT_bGetSkillName( HTdword dwID, CHTString& strSkillName );
	HTbool		HT_bGetSkillDesc( HTdword dwID, CHTString& strSkillDesc );
	HTbool		HT_bGetSkillID( HTdword dwID, HTdword& dwSkillID );
	HTbool		HT_bGetReadyFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetCastFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetActivateFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetFollowFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetImpactFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetStateFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetUI( HTdword dwID, HTdword& dwUI );
	HTbool		HT_bGetIsWeaponBack( HTdword dwID, HTbool& bIsWeaponBack );
	HTbool		HT_bGetSkillActionAniReadyMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateMan1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniReadyMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateMan2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniReadyMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateMan2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniReadyManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateManBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniReadyWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateWom1H( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniReadyWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateWom2HSword( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniReadyWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateWom2HAxe( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniReadyWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateWomBow( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActionSoundActivateMan( HTdword dwID, HTdword& dwSound );
	HTbool		HT_bGetSkillActionSoundActivateWom( HTdword dwID, HTdword& dwSound );

	HTbool		HT_bGetSkillActiveAniReadyManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActiveAniCastManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActiveAniActivateManFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActiveAniReadyWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActiveAniCastWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );
	HTbool		HT_bGetSkillActiveAniActivateWomFist( HTdword dwID, HTdword& dwAni, HTdword& dwAniFApron, HTdword& dwAniBApron );

	HTbool		HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwCategory, HTdword& dwWhereAttach, HTdword& dwPriority );

	HTbool		HT_bGetModelName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetTextureName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetAnimationName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetSoundName( HTdword dwID, CHTString& strName );

private:
	HTRESULT	HT_hrLoadXML( CHTString& strFile );
	HTRESULT	HT_hrLoadTXL( CHTString& strFile );

	HTFXResTable_Map m_mapTables;
};

class CHTFXMAPResMgr
{
public:
	CHTFXMAPResMgr();
	~CHTFXMAPResMgr();

	HTRESULT	HT_hrLoad( CHTString& strFile );
	HTRESULT	HT_hrUnload();
	HTRESULT	HT_hrSave( CHTString& strFile );

	HTtchar*	HT_pGetTableName( HTdword dwID );
	CHTFXBaseResTable* HT_pGetTable( HTdword dwID );

	HTdword		HT_dwGetIDByIndex( CHTString& strTable, HTuint idxRow );
	HTuint		HT_nGetItemCount( CHTString& strTable );

	HTbool		HT_bGetSkillType( HTdword dwID, HTdword& dwType );
	HTbool		HT_bGetCastFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetActivateFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetFollowFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetImpactFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetStateFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetSkillAni( HTdword dwID, HTdword& dwAni );

	HTbool		HT_bGetBornFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetDieActivateFX( HTdword dwID, HTdword& dwFX );
	HTbool		HT_bGetAlwaysFX( HTdword dwID, HTdword& dwFX );

	HTbool		HT_bGetFX( HTdword dwID, CHTString& strFXName, HTdword& dwWhereAttach, HTdword& dwPriority );

	HTbool		HT_bGetModelName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetTextureName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetAnimationName( HTdword dwID, CHTString& strName );
	HTbool		HT_bGetSoundName( HTdword dwID, CHTString& strName );

private:
	HTRESULT	HT_hrLoadXML( CHTString& strFile );
	HTRESULT	HT_hrLoadTXL( CHTString& strFile );

	HTFXResTable_Map m_mapTables;
};

#endif