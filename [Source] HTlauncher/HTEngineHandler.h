#ifndef _HTENGINEHANDLER_H_
#define _HTENGINEHANDLER_H_

#define HT_IS_TANTRA_LAUNCHER

#include "Exdisp.h"

typedef enum _HT_CURRENT_TIME_STATUS
{
	HT_CURRENT_TIME_STATUS_DEFAULT	= 0,
	HT_CURRENT_TIME_STATUS_DAY		= 1,
	HT_CURRENT_TIME_STATUS_NIGHT	= 2
} HT_CURRENT_TIME_STATUS;

#define HT_IS_ATKSTD_ANI( i )	( ( i >= HT_ANISTATE_ATK_STD_S1H ) && ( i <= HT_ANISTATE_ATK_STD_AXE ) ) || ( i == HT_ANISTATE_ATK_STD_FIST ) ? HT_TRUE : HT_FALSE
#define HT_IS_ATKWLK_ANI( i )	( i >= HT_ANISTATE_ATK_WLK_S1H ) && ( i <= HT_ANISTATE_ATK_WLK_AXE ) ? HT_TRUE : HT_FALSE
#define HT_IS_ATKRUN_ANI( i )	( i >= HT_ANISTATE_ATK_RUN_S1H ) && ( i <= HT_ANISTATE_ATK_RUN_AXE ) ? HT_TRUE : HT_FALSE
#define HT_IS_HIT_ANI( i )		( ( i >= HT_ANISTATE_HIT_S1H ) && ( i <= HT_ANISTATE_HIT_AXE ) ) || ( i == HT_ANISTATE_HIT_FIST ) ? HT_TRUE : HT_FALSE

class CHTConfigSystem;
class CHTMapSystem;
class CHTResMgr;
class CHTObjResMgr;
class CHTFXPCResMgr;
class CHTFXMAPResMgr;
class CHTPackFileMgr;
class CHTUserSetting;

#ifdef HT_IS_TANTRA_LAUNCHER
class CHTUISystem;
class HTNPCScriptMgr;
#endif

typedef IHT3DMgr* (*HT_pfnCreate3DMgr)();
typedef HTRESULT (*HT_pfnDestory3DMgr)(IHT3DMgr* p3DMgr);

#define HT_MAX_CHECK_COLLISION 10

class CHTEngineHandler
{
public:
	CHTEngineHandler();
	~CHTEngineHandler();

	HTRESULT				HT_hrInit( CHTConfigSystem* pCfg, HWND hWnd );
	HTRESULT				HT_hrCreateCamera( CHTConfigSystem* pCfg );
	HTRESULT				HT_hrUpdate( HTfloat fElapsedTime );
	HTRESULT				HT_hrRenderWorld();
	HTRESULT				HT_hrRenderFPS( HTfloat fFPS );
	HTRESULT				HT_hrCameraControl( WPARAM wParam, HTfloat fElapsedTime );
	HTRESULT				HT_hrToggleScreen();
	HTRESULT				HT_hrCheckScreen();
	HTRESULT				HT_hrClearScreen( HT_COLOR& clrScreen );
	HTRESULT				HT_hrFlipScreen();
	HTRESULT				HT_hrResize();
	//HTRESULT				HT_hrFadeScreen( HT_COLOR& clrFade, HTfloat fIntensity );
	HTRESULT				HT_hrFadeInScreen( HT_COLOR& clrFrom, HTfloat fTime );	// ���� ȭ���� ����.
	HTRESULT				HT_hrFadeOutScreen( HT_COLOR& clrTo, HTfloat fTime );	// ���� ȭ���� �Ⱥ�����.
	HTint					HT_iGetScreenWidth()	{ return (m_iScreenWidth); }
	HTint					HT_iGetScreenHeight()	{ return (m_iScreenHeight); }

	HTRESULT				HT_hrPrintScreenShot();

	HTRESULT				HT_hrChangeScreenBrightness( HTfloat fFactor );// 0.0 �� ���� ��οﶧ�̰�, 1.0�� ���� �������̴�.

	HTRESULT				HT_hrPick( HTint iX, HTint iY, HTint* idObj, HTIntersectInfo* pInfo, HTbool* bMainObjPick = HT_NULL );		// ���� ����
	HTbool					HT_bCheckCollide( HTvector3& vecStart, HTvector3& vecEnd, HTvector3* pvecCollidePos );
	HTbool					HT_bCheckCollideMainCharToCamera( HTint* arrIDRigidObj, HTint* arrIDSkinnedObj, HTbool* pbTerrain, HTint* piNumRigidObj, HTint* piNumSkinnedObj );

	// �� Object�� BB�� �����Ͽ� �浹�ϸ� HT_TRUE��, �浹���� ������ HT_FALSE �� ��ȯ�Ѵ�.
	HTbool					HT_bCheck2ObjCollide( HTint iObjChar, HTint iObjMon );

	// �� Object�� BB�� �����Ͽ� �浹�ϸ� HT_TRUE��, �浹���� ������ HT_FALSE �� ��ȯ�Ѵ�.
	// �� Main Char�� ID�� �ƴ϶� ��ġ ������ BB�� ũ�⸦ �Է� �޵��� �Ѵ�.
	HTbool					HT_bCheck2ObjCollide( HTint iObjMon, HTvector3& vecPosChar, HTfloat fBBOffset );

	HTbool					HT_bObjectPicked( HTint iX, HTint iY, HTint idObj );	// ������Ʈ�� �ȵǴ��� ����� ��
	HTint					HT_iGetObjectOnMouse( HTint iX, HTint iY );
	HTint					HT_iGetPortalID( HTint idObj );

	HTdword					HT_dwGetIntroBGMID()	{ return ( m_idIntroBGM );	}

	// Pack
	HTRESULT				HT_hrOpenPackFile( CHTString& strFile, HTbool bMemUse );
	HTRESULT				HT_hrClosePackFile( CHTString& strFile );

	// ���� ���� ������ �͵� �� ���������� ���� �� ������
	HTRESULT				HT_hrPick( HTIntersectInfo* pInfo, HTint iX, HTint iY );// �������� �浹��
	HTRESULT				HT_hrPick( HTint iX, HTint iY, HTvector3& vec1, HTvector3& vec2, HTvector3& vec3 ); // ������	
	HTRESULT				HT_hrPick( HTRay oRay, HTvector3& vec1, HTvector3& vec2, HTvector3& vec3 );			// ��ȣ�߰� (20021025)
	HTRESULT				HT_hrPick(HTIntersectInfo* pInfo, HTint idObj, HTbool* bSkinnedModel, HTint iX, HTint iY );

	HTfloat					HT_fGetTerrainHeight( HTfloat fX, HTfloat fZ, HTbool*	bOnObject = HT_NULL );
	HTRESULT				HT_hrSetLookAt( HTvector3& vecPos );
	HTRESULT				HT_hrSetEye( HTvector3& vecPos );
	HTvector3&				HT_rvecGetEye();
	HTRESULT				HT_hrZoomIn( HTfloat f ) { return m_p3DMgr->HT_hrZoomIn( m_idCamera, f ); };
	HTRESULT				HT_hrGetScreenCoordFrom3DCoord( HTvector3& vec3DPos, HTvector2& vec2DPos );
	HTvoid					HT_vGetObjectPoistionInWorldCoord( HTint idObj );

	HTint					HT_iCreateFieldItem( HTdword dwItemID, HTvector3& vecPos );
	HTint					HT_iCreateUIItem( HTdword dwItemID, HTvector3& vecPos );
	HTint					HT_iCreate2DSprite( HTdword dwID, HTvector3& vecPos, HTbyte byForWhat = HT_EOBJ_FOR_UI);
	HTint					HT_iCreateBillboard( HTdword dwID, HTvector3& vecPos );
	HTint					HT_iCreateMapObject( HTdword dwID, HTvector3& vecPos );
	HTint					HT_iCreateNullModel( HTvector3& vecPos );
	HTint					HT_iCreate2DWindowSprite( HTdword dwID, HTint iPosX, HTint iPosY, HTint iSizeX, HTint iSizeY, HT_COLOR& clrBack );
	HTint					HT_iCreate2DWindowUISprite( HTdword dwID, HTint iPosX, HTint iPosY, HTint iSizeX, HTint iSizeY, HT_COLOR& clrBack );
	HTint					HT_iCreate2DWindowUISprite( HTdword dwID, HT_COLOR& clrBack );

	HTint					HT_iCreate2DUISprite( HTdword dwID, HTvector3& vecPos, HTbyte byForWhat = HT_EOBJ_FOR_UI );
	HTint					HT_iCreate2DUIWindowSprite( HTdword dwID, HTint iPosX, HTint iPosY, HTint iSizeX, HTint iSizeY, HT_COLOR& clrBack );
	HTRESULT				HT_hrRender2DUI();
	HTRESULT				HT_hrClearUISpriteVB();

	HTint					HT_iCreateCharacter( HTdword dwID, HTvector3& vecPos, HTint iHairType = HT_HEAD_TYPE_A, HTint iFaceType = HT_HEAD_TYPE_A, HTint idWearItem = 0, HTint idShoesItem = 0 );
	HTint					HT_iCreateNPC( HTdword dwID, HTvector3& vecPos );
	HTint					HT_iCreateMonster( HTdword dwID, HTvector3& vecPos );

	//---------------------------------------------------------------------------------------------
	// HTRESULT				HT_hrChangeColor( HTint idObj, HT_COLOR	clrDiffuse)
	// M : 200308 
	// I : idObj - ���� ������Ʈ ���̵�, clrDiffuse - �ٲ� ��
	//---------------------------------------------------------------------------------------------
	HTRESULT				HT_hrChangeColor( HTint idObj, HT_COLOR	clrDiffuse);

	//---------------------------------------------------------------------------------------------
	// HTint	HT_iCreateMiniMap( HTdword dwID, HTvector3& vecPos, 
	//					HTint iSteps, HTfloat fSpace, HTint iObjDrawSteps, HTint iWidth, HTint iHeight)
	// M : 20021112 Chung,Daeho Hanbitsoft Game Dev.Team
	// I : dwID - ���̵�, vecPos - ��ġ(�Է��ϸ� int�� ��ȯ�Ǿ� ���ȴ�.), iWidth/iHeight - ũ��
	//---------------------------------------------------------------------------------------------
	HTint					HT_iCreateMiniMap( HTdword dwID, HTvector3& vecPos, HTint iSteps, HTfloat fSpace, 
		HTint iObjDrawSteps, HTint iWidth, HTint iHeight);

	//---------------------------------------------------------------------------------------------
	// HTvoid	HT_vSetMiniMapPos( HTvector3& vecPos, HTint iWidth, HTint iHeight)
	// M : 20021112 Chung,Daeho Hanbitsoft Game Dev.Team
	// I : vecPos - ��ġ(�Է��ϸ� int�� ��ȯ�Ǿ� ���ȴ�.), iWidth/iHeight - ũ��
	//---------------------------------------------------------------------------------------------
	HTvoid					HT_vSetMiniMapPos( HTvector3& vecPos, HTint iWidth, HTint iHeight)
	{
		m_vMiniMapPos		= vecPos;
		m_iMiniMapWidth		= iWidth;
		m_iMiniMapHeight	= iHeight;
	};

	//---------------------------------------------------------------------------------------------
	// HTvoid	HT_vChangeMiniMapSize( HTvector3& vecPos, HTint iWidth, HTint iHeight)
	// M : 20021112 Chung,Daeho Hanbitsoft Game Dev.Team
	// I : vecPos - ��ġ(�Է��ϸ� int�� ��ȯ�Ǿ� ���ȴ�.), iWidth/iHeight - ũ��
	//---------------------------------------------------------------------------------------------
	HTvoid					HT_vSetMiniMapDrawOn( HTbool bDrawOn){ m_bMiniMapDrawOn = bDrawOn; };

	//---------------------------------------------------------------------------------------------
	// HTRESULT	HT_hrUpdateMiniMap( HTvector3& vecCharPos )
	// M : 20021112 Chung,Daeho Hanbitsoft Game Dev.Team
	// I : vecPos - ��ġ(�Է��ϸ� int�� ��ȯ�Ǿ� ���ȴ�.), iWidth/iHeight - ũ��
	//---------------------------------------------------------------------------------------------
	HTRESULT				HT_hrUpdateMiniMap( HTint iMiniMapID, HTint iMiniMapLevel, HTint iXPos, HTint iYPos, HTint iWidth, HTint iHeight, HTvector3& vecInterestPos, HTvector3& vecInterestUp, HTfloat fZoom );


	//---------------------------------------------------------------------------------------------
	// HTvoid					HT_vSetMiniMapZoom( HTfloat fZoom)
	// M : 20021112 Chung,Daeho Hanbitsoft Game Dev.Team
	// I : fZoom - �̴ϸ��� �� 
	//				(���������� ĳ������ �󸶳� ���� ī�޶� ���� �̴ϸ� �ؽ��ĸ� �׸����ΰ��� �����ϴ� ��)
	//---------------------------------------------------------------------------------------------
	//HTvoid					HT_vSetMiniMapZoom( HTfloat fZoom){ m_fMinimapZoom = fZoom; };
	HTRESULT				HT_hrLoadObjResMgr( HTdword dwMapID );

	//---------------------------------------------------------------------------------------------
	// HTbool					HT_bGetNearestShoot(HTvector3 vecChar, HTfloat& fRetDist, HTvector3& vecShootPos)
	// M : 20021209 Daeho
	// I : vecChar - ĳ������ ��ġ
	// R : fRetDist - ĳ���ͷκ��� ��������Ʈ������ �ִܰŸ�, vecShootPos - ��������Ʈ�� ��ġ
	//---------------------------------------------------------------------------------------------
	HTbool					HT_bGetNearestShoot(HTvector3 vecChar, HTfloat& fRetDist, HTvector3& vecShootPos);

	//---------------------------------------------------------------------------------------------
	// HTint					HT_dwGetFootSound( HTvector3 vecChar )
	// M : 20021209 Daeho
	// I : vecChar - ĳ������ ��ġ
	// R : �ʿ� �ش��ϴ� �߼Ҹ�
	//---------------------------------------------------------------------------------------------
	HTdword					HT_dwGetFootSound( HTvector3 vecChar, HTint iStatus );

	HTdword					HT_dwGetItemUIID( HTdword dwID );
	HTdword					HT_dwGetSkillUIID( HTdword dwID );

	HTvoid					HT_vDestroyObject( HTint idObj, HTint index );
	HTvoid					HT_vDestroyCharacter( HTint idObj, HTint index );
	HTvoid					HT_vDestroyMonster( HTint idObj, HTint index );
	HTvoid					HT_vDestroyNPC( HTint idObj, HTint index );
	HTvoid					HT_vDestroyFieldItem( HTint idObj, HTint index );

	HTRESULT				HT_hrMoveObject(HTint idObj, HTvector3& vecTo, HTbool bObjMount=TRUE);	// ��ȣ ���� (20021029, HTbool bObjMount=TRUE)
	HTRESULT				HT_hrMoveObject(HTint idObj, HTvector3& vecTo, HTvector3& vecResult);	// �浹�� ����ϴ� ������Ʈ�� ���� �̵�
	HTfloat					HT_fGetObjectHeight( HTvector3& vecPos );

	HTRESULT				HT_hrRotateObject( HTint idObj, HTfloat fDegree );
	HTRESULT				HT_hrRotateObject( HTint idObj, HTvector3& vecDegree );

	HTRESULT				HT_hrStartAnimation( HTint idObj, HTdword dwID, HT_ANIM_STATE eState, HTint iLoop );
	HTRESULT				HT_hrAddAnimation( HTint idObj, HTdword dwID, HT_ANIM_STATE eState, HTint iLoop, HTint idHead = -1, HTint idWearItem = -1, HTfloat fTime = 0.0f );
	HTRESULT				HT_hrStopAnimation( HTint idObj );
	HTRESULT				HT_hrChangeAnimation( HTint idObj, HTdword dwID, HT_ANIM_STATE eState, HTint iLoop, HTint idHead = -1, HTint idWearItem = -1, HTfloat fTime = 0.0f, HTint idItem = -1);
	HTRESULT				HT_hrBlendAnimation( HTint idObj, HTdword dwID, HT_ANIM_STATE eState, HTint iLoop = 1, HTfloat fTime = 0.0f, CHTString* pstrBone = HT_NULL );

	HTRESULT				HT_hrRenderObject( HTint idObj );
	HTRESULT				HT_hrRenderObject( HTint idObj, HTword wLayer );
	HTRESULT				HT_hrRenderText( HT_FONT_TYPE eFont, const HTtchar* pszStr, HTvector3& vecPos, HT_COLOR& clrText );
	HTRESULT				HT_hrRenderText( HT_FONT_TYPE eFont, const HTtchar* pszStr, HTvector3& vecPos, HT_COLOR& clrText, HT_COLOR& clrBack, HTfloat fBackOffset = 0 );
	HTRESULT				HT_hrRenderText( HT_FONT_TYPE eFont, const HTtchar* pszStr, HT_COLOR& clrFont, HT_RECT& Rect, HT_TEXT_FORMATING eTextFormating );
	HTRESULT				HT_hrRenderText( HT_FONT_TYPE eFont, const HTtchar* pszStr, HT_COLOR& clrFont, HTfloat fX, HTfloat fY, HTfloat fWidth, HTfloat fLineSpacing, HTfloat* pfReturnHeight );

	HTRESULT				HT_hrDrawBoundingTriangle( HTvector3& vecPoint1, HTvector3& vecPoint2, HTvector3& vecPoint3, HTmatrix& matTransform );

	HTint					HT_iGetTextWidth( HT_FONT_TYPE eFont, const HTtchar* pszStr );
	HTint					HT_iGetTextHeight( HT_FONT_TYPE eFont, const HTtchar* pszStr, HT_RECT& Rect, HT_TEXT_FORMATING eTextFormating );
	//---------------------------------------------------------------------------
	// HTint					HT_iGetWidth(HTint iEObjectID);
	// D :  �ؽ����� ���� ���ϱ�
	// I : iEObjectID - ����������Ʈ ���̵�
	//---------------------------------------------------------------------------
	HTint					HT_iGetWidth(HTint iEObjectID);	//200302��ȣ

	//---------------------------------------------------------------------------
	// HTint					HT_iGetHeight(HTint iEObjectID);
	// D :  �ؽ����� ���� ���ϱ�
	// I : iEObjectID - ����������Ʈ ���̵�
	//---------------------------------------------------------------------------
	HTint					HT_iGetHeight(HTint iEObjectID);//200302��ȣ


	HTRESULT				HT_hrRenderRectangle( HTvector3& vec1, HTvector3& vec2, HTvector3& vec3, HTvector3& vec4, HT_COLOR& clrText );
	HTRESULT				HT_hrRenderLine( HTvector3& vec1, HTvector3& vec2, HT_COLOR& clrText );
	HTRESULT				HT_hrScaleObject( HTint idObj, HTvector3& vecScale );
	HTRESULT				HT_hrScaleObject( HTint idObj, HTint iX, HTint iY );
	HTRESULT				HT_hrAnimateObject( HTint idObj, HTfloat fElapsedTime );
	HTRESULT				HT_hrClipObject( HTint idObj, HTint iLTX, HTint iLTY, HTint iRBX, HTint iRBY  );
	HTRESULT				HT_hrClipRotateObject( HTint idObj, HTfloat fRot, HTint iLTX, HTint iLTY, HTint iRBX, HTint iRBY, HTint iPosX, HTint iPosY );

	// Sound
	HTRESULT				HT_hrPlaySound( HTdword dwSoundID, HTint iLoop, HSAMPLE* hSample = HT_NULL );
	HTRESULT				HT_hrPlaySound( HTint iSoundID, HTint iLoopCount, HTvector3& vecPos, H3DSAMPLE* hSound = HT_NULL, HSAMPLE* h2DSound = HT_NULL);
	HTRESULT				HT_hrStopSound( HSAMPLE hSample );
	HTRESULT				HT_hrStartStreamSound();
	HTRESULT				HT_hrStartSampleSound();
	HTRESULT				HT_hrStopStreamSound();
	HTRESULT				HT_hrStopBGM();
	HTRESULT				HT_hrStopSampleSound();
	HTRESULT				HT_hrSetStreamVolume( HTfloat fVolume );
	HTRESULT				HT_hrSetSampleVolume( HTfloat fVolume );
	HTRESULT				HT_hrSetSoundRoomType( HTint iType );

	HTRESULT				HT_hrFlickerObject( HTint idObj, HT_COLOR& clrChange, HTfloat fTime );
	HT_ANIMSTATE			HT_eGetAnimState( HTint idObj );
	HTRESULT				HT_hrSaveObject( HTint idObj, CHTString& strFile );
	HTRESULT				HT_hrGetBoundingBox( HTint idObj, HT_AABB* pBB, HTmatrix* pmatTrasform );
	HTRESULT				HT_hrSetBoundingBox( HTint idObj, HT_AABB* pBB );
	HTRESULT				HT_hrGetBoundingSphere( HTint idObj, HT_SPHERE* pBS );
	HTRESULT				HT_hrRenderBoundingBox( HTint idObj, HT_COLOR* pColor );

	HTRESULT				HT_hrPreload( CHTConfigSystem* pCfg );

	HTRESULT				HT_hrLoadMap( HTdword dwMapID );
	HTRESULT				HT_hrLoadMapSystem( HTdword dwMapID );
	HTRESULT				HT_hrLoadMapObjs( HTdword dwMapID );

	HTRESULT				HT_hrUnloadMap();

	HT_TILE_TYPE			HT_eGetTileType( HTint iX, HTint iZ, HTint iF );
	HTbool					HT_bIsCellSafeZone( HTint iX, HTint iZ, HTint iF );
	HTbool					HT_bIsCellConflict( HTint iX, HTint iZ, HTint iF );
	HTbool					HT_bIsCellPKZone( HTint iX, HTint iZ, HTint iF );
	HTbool					HT_bIsCellTemple( HTint iX, HTint iZ, HTint iF );
	HTbool					HT_bIsCellMoveDisable( HTint iX, HTint iZ, HTint iF );
	//HTbool					HT_bIsCellVishunu( HTint iX, HTint iZ, HTint iF );
	//HTbool					HT_bIsCellSiva( HTint iX, HTint iZ, HTint iF );
	//--------------------------------------------------------------------------
	// HTfloat					HT_fGetObjHeight(HTint iX, HTint iZ, HTint iF )
	// D : �ö� ������Ʈ�� ���� ���
	// I : iX, iZ - ��ǥ, iF - ��
	// R : ������Ʈ�� ����
	//--------------------------------------------------------------------------
	HTword					HT_wGetObjHeight( HTint iX, HTint iZ, HTint iF ); // ��ȣ �߰�

	HTbool					HT_bCanMove( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor );
	HTbool					HT_bCanMove( HT_OBJSIZETYPE eType, HT_CELL_COORD& crdTo, HTbyte byFloor );

	HTbool					HT_bCanAttack( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor );
	HTbool					HT_bCanAttack( HT_OBJSIZETYPE eType, HT_CELL_COORD& crdTo, HTbyte byFloor );

	HTbool					HT_bMonAttackDisable( HT_OBJSIZETYPE eType, HTvector3& vecTo, HTbyte byFloor );
	HTbool					HT_bMonAttackDisable( HT_OBJSIZETYPE eType, HT_CELL_COORD& crdTo, HTbyte byFloor );

	HTvoid					HT_vSetViewPoint( HTvector3& pos ) { m_vPosition = pos; };
	HTvector3&				HT_vecGetViewPoint() { return ( m_vPosition ); }
	HTRESULT				HT_hrSetInitTime( HTdword dwTimeZeroValue );
	HTfloat					HT_fGetCurrentTimeInAllDay() { return this->m_fNowTimeInAllDay; };
	HTvoid					HT_vLoadTimeValue( CHTConfigSystem* pCfg );
	HTRESULT				HT_hrSetMainChar( HTint idObj );
	HTint					HT_idGetMainChar() { return m_idMainCharacter; };

	HTbool					HT_3DCOORD_TO_CELL( HTvector3& vecPos, HT_CELL_COORD& vecCell );
	HTbool					HT_CELL_TO_3DCOORD( HTvector3& vecPos, HT_CELL_COORD& vecCell );

	HTRESULT				HT_hrPathFind( HT_CELL_COORD& rStart, HT_CELL_COORD& rGoal, HTint* nNode, HT_CELL_COORD* arrNode );

	// Equip & Item
	HTRESULT				HT_hrEquipItem( HTint idObj, HTint idTribe, HTint idItem, HTint idLeftHandWeaponItem = 0, HTint iHeadType = 1, HTint idWearItem = 6001 );
	HTRESULT				HT_hrUnEquipItem( HTint idObj, HTint idTribe, HTint idItem, HTint idLeftHandWeaponItem = 0, HTint iHeadType = 1, HTint idWearItem = 6001 );
	HTRESULT				HT_hrChangeHead( HTint idObj, HTint idTribe, HTint iHairType, HTint iFaceType );

	HTdword					HT_dwGetItemUI( HTint idItem );

	// Resource handling
	HTRESULT				HT_hrLoadCharacterData();
	HTRESULT				HT_hrLoadCharacterTexture();
	HTRESULT				HT_hrLoadCharacterBonModelAni( HTdword dwID );
	HTRESULT				HT_hrUnLoadCharacterData();
	HTRESULT				HT_hrLoadItemData();
	HTRESULT				HT_hrUnLoadItemData();
	HTRESULT				HT_hrLoadSoundData();
	HTRESULT				HT_hrUnLoadSoundData();
	HTRESULT				HT_hrLoadIntroUIData();
	HTRESULT				HT_hrUnLoadIntroUIData();
	HTRESULT				HT_hrLoadMainUIData();
	HTRESULT				HT_hrUnLoadMainUIData();
	HTRESULT				HT_hrLoadETCData();
	HTRESULT				HT_hrUnLoadETCData();

	//	���ʹ�.
	HTvoid					HT_vCreate_LoadingBGImage();
	HTvoid					HT_vDestory_LoadingBGImage();
	HTRESULT				HT_hrRenderLoadingBGI();
	HTRESULT				HT_hrRenderLoadingProgress( HTbool bFlip, HTfloat fBarValue );

	HTRESULT				HT_hrPlayIntroBGM();
	HTRESULT				HT_hrStopIntroBGM();

	HTint					HT_iGetCameraID()	{ return m_idCamera; }
	HTint					HT_iCreateUIModel( CHTString& strFile, HT_ENGINEOBJ_TYPE eType );

	HTdword					HT_dwGetSkillType( HTdword dwSkillID );
	HTdword					HT_dwGetSkillActionActivePassive( HTdword dwSKillID );

	HTbool					HT_bIsWeaponBack( HTdword dwSkillID );
	HTRESULT				HT_hrGetSkillAniType( HTdword dwSkillID, HTbool* pbIs1H, HTbool* pbIs2HSword, HTbool* pbIs2HAxe, HTbool* pbIsBow, HTbool* pbIsFist );
	HTRESULT				HT_hrChangeSkillActionAnimation( HTint idObj, HTdword dwSkillID, HTSkillAniSeq eSkillAniSeq, HTint idTribe, HTint idItem, HTint idHead, HTfloat fPlayTime = 0.0f );
	HTRESULT				HT_hrChangeSkillActiveAnimation( HTint idObj, HTdword dwSkillID, HTSkillAniSeq eSkillAniSeq, HTint idTribe, HTint idItem, HTint idHead, HTfloat fPlayTime = 0.0f );
	HTRESULT				HT_hrStartSFX( HTint *pidFX, HTdword dwSkillID, HT_SFX_WHEN eType, HTint idParent, HTbool bLoop, HTint iLevel = 1 );
	HTRESULT				HT_hrStartSFX( HTint *pidFX, HTdword dwFxID, HTint idParent, HTbool bLoop );

	// Ÿ�� �޴� FX ����
	HTRESULT				HT_hrStartSFX( HTdword dwSkillID, HTint idAttacker, HTint idOpponent, HTint iLevel = 1 );

	HTRESULT				HT_hrStartFX( HTint* pidFX, HTdword dwCategory, CHTString& strFX, HTint idParent, HTdword dwPriority, HTbool bLoop );
	HTRESULT				HT_hrStartFX( HTint* pidFX, HTdword dwCategory, CHTString& strFX, CHTString& strSocket, HTint idParent, HTdword dwPriority, HTbool bLoop );

	HTRESULT				HT_hrPauseSFX( HTint idFx );
	HTRESULT				HT_hrPlaySFX( HTint idFx );
	HTRESULT				HT_hrStopSFX( HTint idFx );

	HTRESULT				HT_hrPlayAttackOKSound( HTint idTribe, HTint idItem );
	HTRESULT				HT_hrPlayHitSound( HTint idTribe, HTint idObj );

	HTRESULT				HT_hrChangeAttackAnimation( HTint idObj, HTint idTribe, HTint idItem, HTint iLoop, HTint idLeftHandWeaponItem = 0, HTint idHead = -1, HTint idWearItem = -1, HTint iSequnce = 0, HTfloat fPlayTime = 0.0f );
	HTRESULT				HT_hrChangeSkillAnimation( HTint idObj, HTint idTribe, HTdword dwSkillID, HTint iLoop, HTint idHead = -1, HTint idWearItem = -1, HTfloat fTime = 0.0f );
	//HTdword					HT_dwGetSkillAniType( HTdword dwSkillID );
	HTRESULT				HT_hrChangeMonsterAttackAnimation( HTint idObj, HTdword dwID, HTdword dwSkillID, HTint iLoop = 1, HTfloat fTime = 0.0f );


	//-----------------------------------------------------------------------------------------------------------
	// HTRESULT			HT_hrSetSwordWindOn(HTbool bSwordWindOn)
	// M : GAME DEVELOPE TEAM, Chung Daeho, 20021031
	// D : SWORD WIND ON/OFF
	// I : bSwordWindOn - HT_TRUE/HT_FALSE
	// R : HT_OK/HT_FAIL
	//-----------------------------------------------------------------------------------------------------------
	HTRESULT			HT_hrSetSwordWindOn( HTint idObj, HTbool bSwordWindOn);

	HT_RESOURCE_PATH*	HT_poGetResourcePath() { return &m_oResourcePath; };

	HTRESULT				HT_hrEquipDefault( HTint idObj, HTint idTribe );

	HTdword					HT_dwGetItemEquipSoundID( HTdword dwItemID );
	HTdword					HT_dwGetNPCClickSoundID( HTdword dwNPCID );
	HTint					HT_iGetSpecLevel(){	return m_iSpecLevel; };	// Spec Level�� ����.

	// ������Ʈ�� ���ҽ� ���̵� ����
	HTdword					HT_dwGetResourceID( HTint idObj );

	HTRESULT				HT_hrLoadMapResource( HTdword dwID );
	HTRESULT				HT_hrCreateMapObjsDynamic();

	HTRESULT				HT_hrLoadMapObjsInitial( HTvector3& vecPos );

	// ������ ID���� ���� FX ID�� ���ϱ� ���� �Լ�
	HTdword		HT_dwConvrtMonsterID2MonFXID( HTdword dwMonID );

	HTRESULT				HT_hrCreateFXPCMgr();
	HTRESULT				HT_hrCreateFXMAPMgr( HTdword dwMapID );
	HTRESULT				HT_hrDestoryFXPCMgr();
	HTRESULT				HT_hrDestoryFXMAPMgr();
	HTRESULT				HT_hrLoadFXPCResource();
	HTRESULT				HT_hrUnloadFXPCResource();
	HTRESULT				HT_hrLoadFXMAPResource( HTdword dwMapID );
	HTRESULT				HT_hrUnloadFXMAPResource();

	HTdword					HT_dwGetMonsterSkillAniID( HTdword dwMonSkillID );

	// Only For FX Viewer
	HTint					HT_iGetItemCount( HTbool bIsPC, CHTString& strTable );
	HTdword					HT_dwGetIDByIndex( HTbool bIsPC, CHTString& strTable, HTuint idxRow );
	HTRESULT				HT_hrGetFXName( HTdword dwFXID, CHTString* pstrFX );

	HTbool					HT_bGetItemName( HTdword dwID, CHTString* pstrName );
	HTint					HT_iGetItemCount( CHTString& strTable );
	HTdword					HT_dwGetIDByIndex( CHTString& strTable, HTint i );

	HTRESULT				HT_hrUnarmWeapon( HTint idObj, HTint idTribe, HTint idWeapon, HTint idShield = -1, HTint idLeftHandWeaponItem = 0 );
	HTRESULT				HT_hrShowShadow( HTint idObj, HTbool bShow );

	HTRESULT				HT_hrShowObject( const HTint idObj, HTbool bFlag );

	HTbool					HT_bMinimapLoaded();

	HTfloat					HT_fGetObjHeight( HTint idObj );
	//HTRESULT				HT_hrGetObjSize( HTint idObj, HTfloat* fHeight, HTfloat* fWidth, HTfloat* fDepth );

	HTbool					HT_bIsWeapon( HTdword dwID );
	HTbool					HT_bIsWearItem( HTdword dwID );
	HTbool					HT_bIsGloveItem( HTdword dwID );
	HTbool					HT_bIsDartItem( HTdword dwID );
	HTbool					HT_bIsHatItem( HTdword dwID );
	HTbool					HT_bIsShieldItem( HTdword dwID );
	HTbool					HT_bIsShoesItem( HTdword dwID );
	HTbool					HT_bIsShortSword( HTdword dwID );

	HTvoid					HT_vSetLoadTimes(HTint iTimes);

	HTRESULT				HT_hrDontClickIt( HTint idObj );
	HTbool					HT_bIsWindowCursor();

	HTRESULT				HT_hrLoadGuildMark();
	HTRESULT				HT_hrAttachGuildMark( HTint idParent, HTdword wGuildIdenty );
	HTRESULT				HT_hrDestroyGuildMark( HTint idParent );
	HTdword					HT_dwConvertGuildMarkIdenty( HTint iEmblem, HTint iTitle, HTint iColor );

	HTRESULT				HT_hrAttachGodMark( HTint idParent, HTint idTribe, HTEGodType eGod, HTint iLevel );
	HTRESULT				HT_hrDetachGodMark( HTint idParent );

	HTRESULT				HT_hrSetRederState(HTint idObj, HTint iRenderState);

	HTbool					HT_bGetIndicatedArea(HTint& iPrevAreaID, HTint& iAreaID, CHTString& strAreaName);

	HTRESULT				HT_hrGetNPCName( HTdword dwID, CHTString* pstrName );
	HTRESULT				HT_hrGetPCSkillName( HTdword dwID, CHTString* pstrName );
	HTRESULT				HT_hrGetPCSkillDesc( HTdword dwID, CHTString* pstrName );
	HTRESULT				HT_hrGetMonsterName( HTdword dwID, CHTString* pstrName );

	HTvoid					HT_vOnMouseMove( HTint iX, HTint iY );
	HTRESULT				HT_hrOnMouseWideEffect( HTdword dwFX );
	HTRESULT				HT_hrOffMouseWideEffect();

	HTRESULT				HT_hrAttachItemMainRefineEffect( HTint idObj, HTdword dwIDItem, HTint iMainRefineLevel );
	HTRESULT				HT_hrAttachItemSubRefineEffect( HTint idObj, HTdword dwIDItem, HTESubRefineType eSubRefineType, HTint iSubRefineLevel );
	HTRESULT				HT_hrDetachItemMainRefineEffect( HTint idObj, HTdword dwIDItem );
	HTRESULT				HT_hrDetachItemSubRefineEffect( HTint idObj, HTdword dwIDItem );

	// ���� ���̰� �Ⱥ��̴� ȿ���� ���� �Լ�
	HTvoid					HT_vSetBlind( HTint iMSTime = 1000,
		HTfloat fFogStart = 0.0f, HTfloat fFogEnd = 50.0f,
		HTfloat fFogColorR = 0.0f, HTfloat fFogColorG = 0.0f, HTfloat fFogColorB = 0.0f );
	HTvoid					HT_vSetUnBlind( HTint iMSTime = 1000 );

#ifdef HT_IS_TANTRA_LAUNCHER
	//------------------------------------------------------------------------------//
	//	NPC Script
	//------------------------------------------------------------------------------//
	HTint			HT_nSetActiveNPC(BYTE byNPCType);
	//-------ó�� �ܰ�� �����Ѵ�---------//
	HTint			HT_nSetFirstStep();
	//-------���� �ܰ�� ����-------------//
	HTint			HT_nNextStep(HTint nSelNum);

	HTvoid			HT_vGetQuestion(HTtchar* szText, HTbyte* pbyteParam);
	HTvoid			HT_vGetSelectText(HTint nIndex, CHTString& szText);
	HTint			HT_iGetNowQuestionIndex();

	HTshort			HT_sGetClientEvent();
	HTshort			HT_sGetServerEvent();

	//-------- ���� ����Ʈ ������ ã�´� ----------//
	HTvoid			HT_vGetQuestLevel(BYTE byServerLvl, BYTE& byClientLvl, BYTE& byClientLvlTime);
	//-------- ���� ����Ʈ�� ���� ������ ã�´� ----------//
	HTvoid			HT_vGetNextQuestLevel(BYTE& byClientLvl, BYTE& byClientLvlTime);
#endif

	HTRESULT				HT_hrLoadMapObjsDynamic( HTvector3& vecPos );

	HTint	HT_iGetNumFlocking();
	HTvoid	HT_vGetBaseFlockingInfo( HTint index, HTdword* pdwNPC, HTvector3* pvecBasePos );
	HTvoid	HT_vReleaseBaseFlockingInfo();

#ifdef HT_IS_TANTRA_LAUNCHER
	HTint	HT_iGetGoingPotal(HTdword dwID, HTint iNo, HTdword& dwFee, HTdword& dwLevel);
	HTbool	HT_bGetPotalName(HTdword dwID, CHTString* strName);
	HTdword	HT_dwGetPortalFee(HTdword dwFrom, HTdword dwTo);
	HTdword	HT_dwGetPortalLevel(HTdword dwFrom, HTdword dwTo);
	HTdword HT_dwGetAffectionFXID( HTqword qwCurAffectionID, HTqword qwPrevAffectionID = 0 );
#endif

	HTvoid	HT_vSetStreamVolume(HTfloat fVolume);

#ifndef HT_IS_TANTRA_LAUNCHER
	HTvoid HT_vRestartFieldFX();
#endif

	// seon mi 2004.06.11
	HTint					HT_iGetAreaID() { return m_iAreaID; }
	HTint					HT_iGetPrevAreaID() { return m_iPrevAreaID; }

	// For Web
	HRESULT		JK_hrWebMgr_SetOpenWeb( int iIndex, HWND hWnd, char* szURL, int iSecondToWait, int iLeft, int iTop, int iWidth, int iHight );
	HTRESULT	HT_hrOpenWeb( HWND hWnd, CHTString& strURL, HTint iSecondToWait = 5 );
	HTRESULT	HT_hrOpenWebWithPost( HWND hWnd, CHTString& strURL, CHTString& strPost, HTint iSecondToWait = 5 );
	HTRESULT	HT_hrCloseWeb();
	HTRESULT	HT_hrClearWebCookies();

	// ����� �ʿ��� Guild Mark�� ���� ��߿� �ڱ� ���� �Լ��̴�. �� �Լ��� �ҷ��ָ� �� ������ �ٲپ��ش�. 0���� �����ϸ� ��������.
	HTRESULT	HT_hrSetGuildCastleMark( HTdword dwGMarkUL, HTdword dwGMarkUR, HTdword dwGMarkLL, HTdword dwGMarkLR );

private:
	IWebBrowser2* m_pWebBrowser;
	HWND m_hWndExplorer;

private:
	HTRESULT				HT_hrStartFieldFX( HTint *pidFX, HTdword dwFxID, HTint idParent, HTbool bLoop, HTint iWhen );

	HTRESULT				HT_hrAttachObject( HTint idObj, CHTString& strSocket, HTdword dwModelID, HTfloat fScale = 1.0f, HTdword dwAnimID = 0 );
	HTRESULT				HT_hrDetachObject( HTint idObj, CHTString& strSocket );

#ifndef HT_IS_TANTRA_LAUNCHER
public:
	HTRESULT				HT_hrChangeClothes( HTint idObj, HTint idTribe, HTint idItem );
private:
#else
	HTRESULT				HT_hrChangeClothes( HTint idObj, HTint idTribe, HTint idItem );
#endif
	HTRESULT				HT_hrHideHands( HTint idObj, HTint idTribe, HTint idItem );
	HTRESULT				HT_hrShowHands( HTint idObj, HTint idTribe, HTint idItem );
	HTRESULT				HT_hrChangeShoes( HTint idObj, HTint idTribe, HTint idItem );

	HTfloat					HT_fGetModelScaleFactor( HTint idTribe, HTdword dwModelID );

	HTRESULT				HT_hrInitResource();
	HTRESULT				HT_hrLoadResource( CHTString& strTable, HT_SHAREOBJ_TYPE eType, CHTString& strPath, CHTString& strTexPath );
	HTRESULT				HT_hrUnloadResource( CHTString& strTable );
	HTRESULT				HT_hrLoadTextures( CHTString& strTable, CHTString& strPath, CHTString& strTexPath );

	HTRESULT				HT_hrChangeObject( HTint idObj, HT_EMODELPART ePart, HTint idItem, HTint idTribe );
	HTRESULT				HT_hrHideMeshFace( HTint idObj );
	HTRESULT				HT_hrHideMeshHair( HTint idObj );
	HTRESULT				HT_hrHideMeshUpWear( HTint idObj );
	HTRESULT				HT_hrHideMeshDownWear( HTint idObj );
	HTRESULT				HT_hrHideMeshHandWear( HTint idObj );
	HTRESULT				HT_hrHideMeshShoes( HTint idObj );

	HTRESULT				HT_hrLoadWaterFile( CHTString& strPath, CHTString& strFile );

	HTRESULT				HT_hrUpdateWorldTime( HTfloat fElapsedTime );

	HTRESULT				HT_hrLoadSpecValues( HTint iLevel, CHTConfigSystem* pCfg );

	HTvoid					HT_vGoodMorning();	// �ذ� �ߴ� �ð��� �ҷ����� �Լ� HT_hrUpdateWorldTime ����
	HTvoid					HT_vGoodNight();	// �ذ� ���� �ð��� �ҷ����� �Լ� HT_hrUpdateWorldTime ����

	HTint					HT_iGet3RandomID( HTdword dwID1, HTdword dwID2, HTdword dwID3, HTdword* dwID );
	HTdword					HT_dwGetPCSoundID( HTint idTribe, HT_ANIM_STATE eState, HTint iSeq = 0 );

	HTRESULT				HT_hrUnLoadMapObjs( HTdword dwMapID );

	HTRESULT				HT_hrSetUserSetting( CHTConfigSystem* pCfg );


	HTdword					HT_dwGetPCAniID( HTint idTribe, HT_ANIM_STATE eState );

	HTRESULT				HT_hrUpdateMapSystem();
private:
	HINSTANCE				m_h3DDLL;
	HT_pfnCreate3DMgr		m_pfnCreate3DMgr;
	HT_pfnDestory3DMgr		m_pfnDestroy3DMgr;

	IHT3DMgr*				m_p3DMgr;

	CHTResMgr*				m_pResMgr;
	CHTFXPCResMgr*			m_pFXPCResMgr;
	CHTFXMAPResMgr*			m_pFXMAPResMgr;
	CHTObjResMgr*			m_pObjResMgr;

	CHTConfigSystem*		m_pCfgSpec;

	std::vector<HTint>		m_vectorViewingObjs;
	std::vector<HTint>		m_vectorUpdateObjs;
	HTuint					m_nObjs;

	HTuint					m_nTerrainPolyCount;
	HTuint					m_nModelPolyCount;
	HTuint					m_nRenderObjs;
	HTuint					m_nViewings;

	CHTMapSystem*			m_pMapSystem;
	HTbool					m_bWorldLoaded;
	HTbool					m_bFading;

	HT_RESOURCE_PATH		m_oResourcePath;

	HTint					m_idCamera;
	HTint					m_idFontFPS;
	HTint					m_idFontHanbitNaru30;
	HTint					m_idFontGulim12;
	HTint					m_idFontGulim10;
	HTint					m_idSun;
	HTint					m_idMoon;
	HTint		m_idSubLight;			
	HT_LIGHT	m_SubLight;
	HTvector3	m_vecSubLightStartPosition;
	HTvector3	m_vecSubLightRotationAxis;
	HTvector3	m_vecSubLightCurrentPosition;
	HT_COLOR	m_clrMorningSubLightDiffuse;
	HT_COLOR	m_clrMorningSubLightAmbient;
	HT_COLOR	m_clrNoonSubLightDiffuse;
	HT_COLOR	m_clrNoonSubLightAmbient;
	HT_COLOR	m_clrEveningSubLightDiffuse;
	HT_COLOR	m_clrEveningSubLightAmbient;
	HT_COLOR	m_clrNightSubLightDiffuse;
	HT_COLOR	m_clrNightSubLightAmbient;
	HTint					m_idTerrain;
	HTint					m_idShadow;
	HTint					m_idSkyCloud;
	HTint					m_idSkyTerrain;
	HTint					m_idSky;
	HTint					m_idRain;
	HTint					m_idFog;
	HTint					m_idBGM;
	HTint					m_id2DSound;
	HTint					m_id3DSound;
	HTfloat					m_fElapsedTime;
	//HTint					m_idFadeMask;
	struct HTFadeScreen
	{
		HTFadeScreen() { memset( this, 0, sizeof( HTFadeScreen ) ); }

		HTbool		bIsFadeIn;	// HT_TRUE : ȭ���� ���� ����, HT_FALSE : ȭ���� ���� ������ ����.
		HTint		idFade;

		HTfloat		fTime;
		HTfloat		fFadeTime;

		HT_COLOR	clrFade;
	} m_oFadeScreen;

	struct HTFXMgrID
	{
		HTFXMgrID() { memset( this, -1, sizeof( HTFXMgrID ) ); };

		HTint idField;
		HTint idMonsterSkill;
		HTint idMonsterEtc;
		HTint idPCEtc;
		HTint idPCFree;
		HTint idPCGodBrahma;
		HTint idPCGodShiba;
		HTint idPCGodVishunu;
		HTint idPCRaceAsuRak;
		HTint idPCRaceDevGar;
		HTint idPCRaceNageKin;
		HTint idPCRaceYakGan;
	} m_oIDFXMgr;

	HTbool					m_bMiniMapDrawOn;
	HTint					m_idMiniMap;		// �̴ϸ� ���̵�
	HTvector3				m_vMiniMapPos;		// �̴ϸ� ��ġ
	HTint					m_iMiniMapWidth;	// �̴ϸ� ��
	HTint					m_iMiniMapHeight;	// �̴ϸ� ����
	HTfloat					m_fMinimapZoom;		// �̴ϸ� �� factor


	// ������ �⺻ ����
	HTint					m_idWaterZoro;

	// Water
	HTint*					m_arridWater;
	HTuint					m_iNumWater;

	HTint*					m_arridWaterZoro;
	HTint					m_iNumWaterZoro;

	HTvector3				m_vecFPSText;	// TODO : TEMP
	HT_COLOR				m_clrText;

	HTvector3				m_vPosition;

	HTfloat					m_fLifeTime;	// TODO : TEMP
	HTfloat					m_fCenterRatio;	// TODO : TEMP

	CHTTimer*				m_pTimer;
	HTfloat					m_fRenderTime;
	HTfloat					m_fUpdateTime;
	HTfloat					m_fDebugTime;

	HT_COLOR				m_clrDiffuseObjs, m_clrAmbientObjs, m_clrEmissiveObjs, m_clrSpecularObjs;
	HT_COLOR				m_clrDiffuseTree, m_clrAmbientTree, m_clrEmissiveTree;
	HT_COLOR				m_clrDiffuseLeaf, m_clrAmbientLeaf, m_clrEmissiveLeaf;
	HT_COLOR				m_clrDiffuseChar, m_clrAmbientChar, m_clrEmissiveChar, m_clrSpecularChar;

	// ToDo : �ð��� ���õ� �κ�. ���� �ڵ鷯���� ������ �ٸ� ������ �̵��� ������ �����ȴ�.
	HTdword		m_dwAllInitTimeStartTime;
	HTfloat		m_fNowTimeInAllDay;

	HT_CURRENT_TIME_STATUS	m_eCurretTimeStatus;
	HTbool		m_bUpdateTime;
	HTfloat		m_fDayTime;
	HTfloat		m_fNightTime;
	HTvector3	m_vecSunMoonStartPosition;
	HTvector3	m_vecSunMoonRotationAxis;

	HTfloat		m_fMorningStart;
	HTfloat		m_fMorningEnd;
	HTfloat		m_fEveningStart;
	HTfloat		m_fEveningEnd;

	HT_COLOR	m_clrMorningFog;
	HT_COLOR	m_clrNoonFog;
	HT_COLOR	m_clrEveningFog;
	HT_COLOR	m_clrNightFog;

	HTfloat		m_fMorningSkyHigh, m_fMorningSkyMid, m_fMorningSkyLow;
	HT_COLOR	m_clrMorningSkyHighColor;
	HT_COLOR	m_clrMorningSkyMidColor;
	HT_COLOR	m_clrMorningSkyLowColor;
	HT_COLOR	m_clrMorningCloudColor;
	HTfloat		m_fNoonSkyHigh, m_fNoonSkyMid, m_fNoonSkyLow;
	HT_COLOR	m_clrNoonSkyHighColor;
	HT_COLOR	m_clrNoonSkyMidColor;
	HT_COLOR	m_clrNoonSkyLowColor;
	HT_COLOR	m_clrNoonCloudColor;
	HTfloat		m_fEveningSkyHigh, m_fEveningSkyMid, m_fEveningSkyLow;
	HT_COLOR	m_clrEveningSkyHighColor;
	HT_COLOR	m_clrEveningSkyMidColor;
	HT_COLOR	m_clrEveningSkyLowColor;
	HT_COLOR	m_clrEveningCloudColor;
	HTfloat		m_fNightSkyHigh, m_fNightSkyMid, m_fNightSkyLow;
	HT_COLOR	m_clrNightSkyHighColor;
	HT_COLOR	m_clrNightSkyMidColor;
	HT_COLOR	m_clrNightSkyLowColor;
	HT_COLOR	m_clrNightCloudColor;

	HT_COLOR	m_clrMorningSunDiffuse;
	HT_COLOR	m_clrMorningSunAmbient;
	HT_COLOR	m_clrNoonSunDiffuse;
	HT_COLOR	m_clrNoonSunAmbient;
	HT_COLOR	m_clrEveningSunDiffuse;
	HT_COLOR	m_clrEveningSunAmbient;
	HT_COLOR	m_clrNightSunDiffuse;
	HT_COLOR	m_clrNightSunAmbient;

	HTfloat		m_fMorningFogStart;
	HTfloat		m_fMorningFogEnd;
	HTfloat		m_fNoonFogStart;
	HTfloat		m_fNoonFogEnd;
	HTfloat		m_fEveningFogStart;
	HTfloat		m_fEveningFogEnd;
	HTfloat		m_fNightFogStart;
	HTfloat		m_fNightFogEnd;

	// LOD setting
	HTfloat		m_fLODDistanceLow1, m_fLODDistanceLow2, m_fLODDistanceLow3;
	HTfloat		m_fLODDistanceHigh1, m_fLODDistanceHigh2, m_fLODDistanceHigh3;
	HTfloat		m_fLODDistanceFar, m_fLODDistanceFarSM;
	HTfloat		m_fCharLODDistance1, m_fCharLODDistance2, m_fCharLODDistance3;

	// FX LOD Setting 20021205
	HTfloat		m_fFXCamJitterVisibleDistance;
	HTfloat		m_fFXSpriteSystemVisibleDistance;
	HTfloat		m_fFXSpriteVisibleDistance;
	HTfloat		m_fFXSoundVisibleDistance;
	HTfloat		m_fFXModelVisibleDistance;
	HTfloat		m_fFXDynaLightVisibleDistance;

	// Character Light
	HTint		m_iTypeCharLight;
	HT_COLOR	m_clrSpotDiffuse, m_clrSpotAmbient, m_clrSpotSpecular;
	HTfloat		m_fSpotRange, m_fSmallAngle, m_fLargeAngle;
	HTvector3	m_vecSpotPosition, m_vecSpotRotation;

	// etc
	HTfloat		m_fTerrainLODDetail;
	HTfloat		m_fTerrainTilingDistance;
	HTbool		m_bTerrainDetailTexture;

	HTint		m_idMainCharacter;
	HTint		m_idCharacterLight;
	HT_LIGHT	m_oCharLight;

	std::vector<HTint> m_vectorGrasses;
	HTfloat		m_fGrassarea;
	HTuint		m_nGrassCount;
	HTbool		m_bUpdateByCamera;
	HTfloat		m_fGrassAlphaDistance;

	HTfloat		m_fCameraSpeed;

	HTint		m_iObjDrawSteps;		// ��ȣ 20021128
	HTfloat		m_fMiniMapSpace;		// ��ȣ 20021128

	// Pack file mgr
	CHTPackFileMgr*	m_pPackFileMgr;

	HTint		m_iSpecLevel;
	HTbool		m_bUseRTShadow;
	HTfloat		m_fCameraFarZ;
	HTuint		m_nMaxModelCount;
	HTint		m_iScreenWidth;
	HTint		m_iScreenHeight;
	HTint		m_iScreenColorDepth;
	HTint		m_iTextureDetailLevel;

	CHTString	m_strMapPath;

	// Sound
	HTfloat		m_fStreamVolume;
	HTfloat		m_fStreamFadeVolume;
	HTbool		m_bFadeoutBGM;
	HTdword		m_dwNextBGMID;
	HTint		m_iNextBGMLoopCount;

	CHTUserSetting*		m_pUserSettings;

	HTint		m_iSpeakerType;
	CHTString	m_str3DProvider;

	CHTString	m_strObjResName;
	// DLMap �ε��� ���Ͽ� NPC�� MONster�� ���ҽ� ���̵���� �����Ѵ�.
	std::vector<HTdword>	m_vectorNPCMonsterIDs;
	std::vector<HTdword>	m_vectorNPCMonsterAniIDs;

	HTbool					m_bDynamicLoading;
	HTdword					m_dwCurrentMapID;

	HANDLE								m_hLoadingThread;
	std::map<HTdword,HTbool>			m_mapLoadedOrNot;
	std::set<HTint>						m_setToCreate;
	std::set<HTint>						m_setToLoad;
	HTvector3							m_vecStampPos;
	HTRESULT				HT_hrLoadingProcess();

	HT_COLOR				m_clrClearScreen;
	HT_COLOR				m_clrAmbientLight;
	HTfloat					m_fAniInterpolateTime;

#ifdef HT_IS_TANTRA_LAUNCHER
	HTNPCScriptMgr*			m_pNPCScriptMgr;	// NPC Script
#endif

	//	Loading BackGround Image
	HTint					m_iBGIBalck;
	HTint					m_iLoadingBackGroundImage;
	//	Loading Bar
	HTint					m_iLoadingBox;
	HTint					m_iLoadingBar;

	HTfloat					m_fLoadingStartPercent;
	HTfloat					m_fLoadingNextPercent;
	HTfloat					m_fLoadingCurrentPercent;
	HTbool					m_bRenderLoading;
	HTint					m_iPercent;

	HTbool					m_bUpdateViewingObjs;

	HTdword					m_idIntroBGM;

	HTint					m_iLoadTimes;

	std::set<HTint>			m_setDontClickObjs;
	HTint					m_iAreaID;
	HTint					m_iPrevAreaID;
	//CHTString				m_strAreaName;

	HTint					m_iLoadUINo;
	//-----------------------------------------------------------------------------
	// Resource Pool Handler
	typedef struct _HT_RES_POOL_DATA
	{
		HTbool				bMapDefendent;
		HT_SHAREOBJ_TYPE	eType;
		HTint				iRefCount;
		_HT_RES_POOL_DATA()
		{
			bMapDefendent = HT_FALSE;
			eType = HT_SOBJTYPE_NULL;
			iRefCount = 0;
		}
	} HT_RES_POOL_DATA;

	// NPC/Monster TMD/Anim, ItemTMD, PCMeshTMD, PCTMDModel, PC Anim, Socket Anim ����
	std::map<HTdword,HT_RES_POOL_DATA*> m_mapResPools;

	std::map<HTint,HTdword>				m_mapModelIndex;	// ����������Ʈ���̵�� ������ �������̵�(�ε���)���� �˾Ƴ��� ���� �������
	std::multimap<HTint,HTdword>		m_mapItemIndex;		// ����������Ʈ���̵�� ������ �������ε������� �˾Ƴ��� ���� �������

	HTfloat								m_fUnloadWaitTime;	// ��ε��ϱ⸦ ��ٸ��� �ð� ( ���巹���� ���� ������ )
	std::map<HTdword,HTfloat>			m_mapWaitUnloads;	// ��ε带 �ٷ� ���� �ʰ� �����Ⱓ�� ���� ���� ��ε��ϱ� ���� �������

	HTRESULT	HT_hrLoadToResPool( HTdword dwResID, HTbool bMapDefendent );
	// Monster�� Basic Mesh�� Part Mesh�� ID �뿪���� ���е��� �ʴ´�. ���α׷������� �����ؾ� �ϰڴ�.
	HTRESULT	HT_hrLoadToResPool4MonsterMesh( HTdword dwResID, HTbool bMapDefendent );
	HTRESULT	HT_hrUnloadFromResPool( HTdword dwResID );

	HTRESULT	HT_hrLoadWeaponItemAnim( HTint idObj, HTint idTribe, HTint idItem );
	HTRESULT	HT_hrUnloadWeaponItemAnim( HTint idObj, HTint idItem );

	//-----------------------------------------------------------------------------
	// Helper Functions
	HTdword		HT_dwGetHeadID( HTdword dwID, HTint idHead );
	HTdword		HT_dwGetPCSoundID1( HTdword dwTribe, HT_ANIM_STATE eState );
	HTdword		HT_dwGetPCSoundID2( HTdword dwTribe, HT_ANIM_STATE eState );
	HTdword		HT_dwGetPCSoundID3( HTdword dwTribe, HT_ANIM_STATE eState );
	HTdword		HT_dwGetMonsterAniID( HTdword dwResID, HT_ANIM_STATE eState );
	HTdword		HT_dwGetRandomSoundID( HTdword dwSound1, HTdword dwSound2, HTdword dwSound3 );
	HTdword		HT_dwGetFApronAnimID( HTdword dwTribe, HT_ANIM_STATE eState );
	HTdword		HT_dwGetBApronAnimID( HTdword dwTribe, HT_ANIM_STATE eState );
	HTdword		HT_dwGetMonsterSoundID( HTdword dwFXMonID, HT_ANIM_STATE eState );

	struct HTMousePosFX
	{
		HTint	i2DMouseX, i2DMouseY;
		HTint	idMouseNullModel;

		HTint	idWideFXTargeting;
	};
	HTMousePosFX m_oMousePosFX;

	struct HTFlocking
	{
		HTFlocking()
		{
			dwNPCID = 0;
			vecPos = HTvector3( 0.0f, 0.0f, 0.0f );
		}

		HTFlocking( const HTFlocking& B )
		{
			dwNPCID = B.dwNPCID;
			vecPos = B.vecPos;
		}

		HTdword   dwNPCID;
		HTvector3 vecPos;
	};

	HTbool		m_bUpdateEnable;

	std::vector<HTFlocking> m_vectorFlocking;

	HTvoid		HT_vSetCanModify( HTint id )	{ if ( id >= 0 && id < HT_MAX_EOBJ_COUNT ) m_arrCanModify[id] = HT_TRUE; };
	HTvoid		HT_vSetCanNOTModify( HTint id )	{ if ( id >= 0 && id < HT_MAX_EOBJ_COUNT ) m_arrCanModify[id] = HT_FALSE; };
	HTbool		HT_bGetCanModify( HTint id )	{ if ( id >= 0 && id < HT_MAX_EOBJ_COUNT ) return m_arrCanModify[id]; else return HT_FALSE; };
	HTbool		m_arrCanModify[HT_MAX_EOBJ_COUNT];

	struct HTBlindEffect
	{
		HTBlindEffect() : bToBlind ( HT_FALSE ), fChangePerSecond ( 0.0f ), fChangeFogStart ( 0.0f ), fChangeFogEnd ( 0.0f ), fElapsedPercent ( 0.0f )
		{ clrChangeFog = HT_COLOR( 0.0f, 0.0f, 0.0f, 0.0f ); }

		// T : �Ʒ��� ��ǥ������ ����Ǿ� ����.
		// F : �Ʒ��� ������ ������ ������ ����Ǿ� ����.
		HTbool		bToBlind;

		// � ��ǥ�� �ٲ����, �и��ʴ� ��ŭ�� ����Ǵ���
		HTfloat		fChangePerSecond;
		HTfloat		fChangeFogStart;
		HTfloat		fChangeFogEnd;
		HT_COLOR	clrChangeFog;

		// ���� ���� ���� ǥ��. 1.0f�� ������ ������ �Ϸ�Ȱ�.
		HTfloat		fElapsedPercent;
	}	m_oBlindEffect;

	struct HTFogStatus
	{
		HTFogStatus() : fStart ( 0.0f ), fEnd ( 0.0f )
		{ clr = HT_COLOR( 0.0f, 0.0f, 0.0f, 0.0f ); } 

		HTfloat fStart, fEnd;
		HT_COLOR clr;
	}	m_oCurrectFogStatus;

	HTbool	m_bWindowed;
	HTint	m_iCurrentWindowWidth;
	HTint	m_iCurrentWindowHeight;

	struct HTGuildCastleInfo
	{
		HTdword dwGMarkUL;
		HTdword dwGMarkUR;
		HTdword dwGMarkLL;
		HTdword dwGMarkLR;
	}	m_oGuildCastleInfo;

	friend class CHTApplication;
};

extern CHTEngineHandler* g_pEngineHandler;


#endif	// #ifndef _HTENGINEHANDLER_H_