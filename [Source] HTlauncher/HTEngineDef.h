#ifndef _HTENGINEDEF_H_
#define _HTENGINEDEF_H_

#define	HT_COLORCONVERT(r,g,b,a)	(HT_COLOR((r)/255.0f,(g)/255.0f,(b)/255.0f,(a)/255.0f))

#pragma pack ( push, 1 )

typedef struct _HT_HEADER
{
	HTtchar		szVersion[5];
	HTtchar		szDate[20];
	HTint		nCount;
} HT_HEADER;

typedef struct _HT_CELL_INFO
{
	HTword		wX;			// Cell X 좌표
	HTword		wZ;			// Cell Z 좌표
//	HTbyte		byFloor;	// Cell 층
//	HTword		wHeight;	// Cell 단
	HTword		wObjHeight;	// Cell 위에 존재하는 맵오브젝트의 높이
//	HTbyte		byFeature;	// 지형 유형

	HTword		wState;		// Cell 상태 정보
//	HTdword		dwEvent;	// 이벤트 번호
//	HTdword		dwReserved;	// 예약
} HT_CELL_INFO;

#pragma pack ( pop )

typedef enum _HT_TILE_TYPE
{
	HT_TILE_NONE				= 0x00,
	HT_TILE_GRASS				= 0x01,
	HT_TILE_GRASS_STONE			= 0x02,
	HT_TILE_CLAY_GRAVEL			= 0x03,
	HT_TILE_STONE_GRAVEL_CLAY	= 0x04,
	HT_TILE_BOULDER				= 0x05,
	HT_TILE_GARDEN				= 0x06,
	HT_TILE_VILLAGE				= 0x07,
	HT_TILE_ROAD				= 0x08,
	HT_TILE_FIGURE				= 0x09,
	HT_TILE_FOREST				= 0x0a,
	HT_TILE_DEVIL				= 0x0b,
	HT_TILE_WATER				= 0x0c,
} HT_TILE_TYPE;

typedef enum _HT_CELL_STATE
{
	HT_CELL_SAFE_ZONE			= 0x0001,
	HT_CELL_CONFLICT			= 0x0002,
	HT_CELL_PK_ZONE				= 0x0004,
	HT_CELL_TEMPLE				= 0x0008,
	HT_CELL_MOVE_DISABLE		= 0x0010,
	HT_CELL_ATTACKENABLE		= 0x0020,

	HT_CELL_NOATTACKMONSTER		= 0x2000,

	//HT_MAP_OBJECT_SIT_DISABLE	= 0x2000,
	HT_MAP_OBJECT_MOUNT_DISABLE = 0x4000,

} HT_CELL_STATE;


typedef struct _HT_CELL_NODE
{
//	HTbyte			byFloor;	// Cell 층
//	HTword			wHeight;	// Cell 단
	HTword			wObjHeight;	// Cell 위에 존재하는 맵오브젝트의 높이
//	HTbyte			byFeature;	// 지형 유형
	HTword			wState;		// Cell 상태 정보
//	HTdword			dwEvent;	// 이벤트 번호
	_HT_CELL_NODE*	pNextNode;	// Linked 된 다음 층의 Node

} HT_CELL_NODE;

// 한 타일의 크기, 한 그리드의 크기, 2m 
#define HT_MAP_TILESIZE		20.0f
#define HT_MAP_CELLSIZE		10.0f

typedef struct _HT_CELL_COORD
{
	HTword			x;	
	HTword			y;	
} HT_CELL_COORD;

typedef enum _HT_OBJSIZETYPE
{
	HT_OBJSIZE_SMALL,
	HT_OBJSIZE_MEDIUM,
	HT_OBJSIZE_LARGE,
	HT_OBJSIZE_NONE,
} HT_OBJSIZETYPE;

typedef enum _HT_RESOURCE_TYPE
{
	HT_RESTYPE_CHARACTERMODEL,
	HT_RESTYPE_CHARACTERTEXTURE,
	HT_RESTYPE_CHARACTERANIMATION,

	HT_RESTYPE_MODEL,
	HT_RESTYPE_MODELTEXTURE,
	HT_RESTYPE_ANIMATION,
	HT_RESTYPE_LEVEL,
	HT_RESTYPE_LEVELTEXTURE,
	HT_RESTYPE_SOUND,
	HT_RESTYPE_FX,
	HT_RESTYPE_TEXTURE,
	HT_RESTYPE_ETC,

} HT_RESOURCE_TYPE;

typedef struct _HT_RESOURCE_PATH
{
	CHTString	strCharacterModel;
	CHTString	strCharacterTexture;
	CHTString	strCharacterAnimation;
	CHTString	strItemModel;
	CHTString	strItemTexture;
	CHTString	strNPCModel;
	CHTString	strNPCTexture;
	CHTString	strNPCAnimation;
	CHTString	strMonsterModel;
	CHTString	strMonsterTexture;
	CHTString	strMonsterAnimation;
	CHTString	strObjModel;
	CHTString	strObjTexture;
	CHTString	strFXModel;
	CHTString	strFXTexture;
	CHTString	strFXAnimation;

	CHTString	strLevel;
	CHTString	strLevelTexture;
	CHTString	strSound;
	CHTString	strFX;
	CHTString	strInterface;
	CHTString	strETC;

} HT_RESOURCE_PATH;

typedef enum _HT_OBJECT_TYPE
{
	HT_OBJTYPE_CHARACTER,
	HT_OBJTYPE_NPC,
	HT_OBJTYPE_STRUCTURE,
	HT_OBJTYPE_3DSPRITE,
	HT_OBJTYPE_SFX_MOTIONBLUR,
	HT_OBJTYPE_LIGHT,	// directional light
	HT_OBJTYPE_SPOTLIGHT,
	HT_OBJTYPE_UI_2DSPRITE,
	HT_OBJTYPE_UI_CHARACTER,
	HT_OBJTYPE_UI_OBJECT,
	HT_OBJTYPE_SOUND_BGM,
	HT_OBJTYPE_SOUND_2DEFFECT,

} HT_OBJECT_TYPE;

typedef enum _HT_SFX_TYPE
{
	HT_SFX_MOTIONBLUR,
} HT_SFX_TYPE;

typedef enum _HT_FONT_TYPE
{
	HT_FONT_ARIAL_20,
	HT_FONT_HANBITNARU_30,
	HT_FONT_GULIM_12,
	HT_FONT_GULIM_10,
} HT_FONT_TYPE;

#define HT_OBJ_UI_IDSTART		50000

// 20021101 HK : 임시 데이터였으므로 삭제
//#define HT_SFX_FIRE_A		"FireA"
//#define HT_SFX_FIRE_B		"FireB"
//#define HT_SFX_POT			"Pot"
//#define HT_SFX_MISSLE		"Missle"
//#define HT_SFX_SPARK_A		"SparkA"
//#define HT_SFX_SPARK_B		"SparkB"
//#define HT_SFX_ENERGY_A		"EnergyA"
//#define HT_SFX_ENERGY_B		"EnergyB"

typedef enum _HT_SFX_WHEN
{
	HT_SFX_WHEN_READY,
	HT_SFX_WHEN_CAST,
	HT_SFX_WHEN_ACTIVATE,
	HT_SFX_WHEN_FOLLOW,
	HT_SFX_WHEN_IMPACT,
	HT_SFX_WHEN_STATE
} HT_SFX_WHEN;

#endif	// #ifndef _HTENGINEDEF_H_