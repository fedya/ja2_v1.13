#ifdef PRECOMPILEDHEADERS
	#include "Tactical All.h"
	#include "language defines.h"
#else
	#include "builddefines.h"
	#include <stdio.h>
	#include <stdarg.h>
	#include <time.h>
	#include "sgp.h"
	#include "gameloop.h"
	#include "himage.h"
	#include "vobject.h"
	#include "sysutil.h"
	#include "overhead.h"
	#include "mousesystem.h"
	#include "Button System.h"
	#include "interface.h"
	#include "vsurface.h"
	#include "wcheck.h"
	#include "input.h"
	#include "Handle UI.h"
	#include "renderworld.h"
	#include "sys globals.h"
	#include "cursors.h"
	#include "radar screen.h"
	#include "worldman.h"
	#include "Font Control.h"
	#include "render dirty.h"
	#include "utilities.h"
	#include "Sound Control.h"
	#include "Interface Panels.h"
	#include "Animation Control.h"
	#include "Soldier Control.h"
	#include "pathai.h"
	#include "weapons.h"
	#include "lighting.h"
	#include "faces.h"
	#include "mapscreen.h"
	#include "message.h"
	#include "text.h"
	#include "Interface Items.h"
	#include "Font Control.h"
	#include "Cursor Control.h"
	#include "interface cursors.h"
	#include "interface utils.h"
	#include "interface items.h"
	#include "wordwrap.h"
	#include "interface control.h"
	#include "vobject_blitters.h"
	#include "world items.h"
	#include "points.h"
	#include "physics.h"
	#include "finances.h"
	#include "ui cursors.h"
	#include "handle ui.h"
	#include "ShopKeeper Interface.h"
	#include "dialogue control.h"
	#include "english.h"
	#include "keys.h"
	#include "Strategicmap.h"
	#include "Arms Dealer Init.h"
	#include "soldier macros.h"
	#include "game clock.h"
	#include "squads.h"
	#include "LaptopSave.h"
	#include "MessageBoxScreen.h"
	#include "Language Defines.h"
	#include "GameSettings.h"
	#include "Map Screen Interface Map Inventory.h"
	#include "Quests.h"
	#include "Map Screen Interface.h"
	#include "Campaign Types.h"
	#include "opplist.h"
	#include "los.h"
	#include "Map Screen Interface Map.h"
#endif

//forward declarations of common classes to eliminate includes
class OBJECTTYPE;
class SOLDIERTYPE;


#define		ITEMDESC_FONT							BLOCKFONT2
#define		ITEMDESC_FONTSHADOW1			MILITARY_SHADOW
#define		ITEMDESC_FONTSHADOW2			32
#define		ITEMDESC_FONTSHADOW3			34
#define		ITEMDESC_FONTFORE1				33
#define		ITEMDESC_FONTFORE2				32

#define		ITEMDESC_FONTAPFORE					218
#define		ITEMDESC_FONTHPFORE					24
#define		ITEMDESC_FONTBSFORE					125
#define		ITEMDESC_FONTHEFORE					75
#define		ITEMDESC_FONTHEAPFORE				76

#define		ITEMDESC_AMMO_FORE					209

#define		ITEMDESC_FONTHIGHLIGHT		FONT_MCOLOR_WHITE

#define			STATUS_BAR_SHADOW				FROMRGB( 140, 136,  119 )
#define			STATUS_BAR							FROMRGB( 201, 172,  133 )
#define			DESC_STATUS_BAR_SHADOW	STATUS_BAR_SHADOW
#define			DESC_STATUS_BAR					STATUS_BAR

#define			MIN_LOB_RANGE						4

#define			INV_BAR_DX							5
#define			INV_BAR_DY							21

#define			RENDER_ITEM_NOSTATUS		20
#define			RENDER_ITEM_ATTACHMENT1	200

#define		ITEM_STATS_WIDTH					26
#define		ITEM_STATS_HEIGHT					8

//LBE node stuff
// Changed some coord defines to INT16s so we can adjust their value based on game options
INT16	ITEMDESC_START_X;
INT16	ITEMDESC_START_Y;
INT16	ITEMDESC_HEIGHT;
INT16	ITEMDESC_WIDTH;
INT16   MAP_ITEMDESC_HEIGHT;
INT16	MAP_ITEMDESC_WIDTH;
extern int SM_ITEMDESC_START_X;
extern int SM_ITEMDESC_START_Y;

//#define		ITEMDESC_START_X					214
//#define		ITEMDESC_START_Y					1 + INV_INTERFACE_START_Y
//#define		ITEMDESC_HEIGHT					133
//#define		ITEMDESC_WIDTH					320
//#define   MAP_ITEMDESC_HEIGHT     268
//#define   MAP_ITEMDESC_WIDTH      272
#define		ITEMDESC_NAME_X					(16 + gsInvDescX)
#define		ITEMDESC_NAME_Y					(67 + gsInvDescY)
#define		ITEMDESC_CALIBER_X			(162 + gsInvDescX)
#define		ITEMDESC_CALIBER_Y			(67 + gsInvDescY)
#define		ITEMDESC_CALIBER_WIDTH	142
#define		MAP_ITEMDESC_CALIBER_X			(105 + gsInvDescX)
#define		MAP_ITEMDESC_CALIBER_Y			(66 + gsInvDescY)
#define		MAP_ITEMDESC_CALIBER_WIDTH	149
#define		ITEMDESC_ITEM_X					(8 + gsInvDescX)
#define		ITEMDESC_ITEM_Y					(11 + gsInvDescY)

#define		CAMO_REGION_HEIGHT			75
#define		CAMO_REGION_WIDTH				75

#define		BULLET_SING_X						(222 + gsInvDescX)
#define		BULLET_SING_Y						(49 + gsInvDescY)
#define		BULLET_BURST_X					(263 + gsInvDescX)
#define		BULLET_BURST_Y					(49 + gsInvDescY)
#define		BULLET_WIDTH						3
#define		BULLET_GAP							5

#define		MAP_BULLET_SING_X				(77 + gsInvDescX)
#define		MAP_BULLET_SING_Y				(135 + gsInvDescY)
#define		MAP_BULLET_BURST_X			(117 + gsInvDescX)
#define		MAP_BULLET_BURST_Y			(135 + gsInvDescY)

#define		MAP_ITEMDESC_NAME_X					(7 + gsInvDescX)
#define		MAP_ITEMDESC_NAME_Y					(65 + gsInvDescY)
#define		MAP_ITEMDESC_ITEM_X					(25 + gsInvDescX)
#define		MAP_ITEMDESC_ITEM_Y					(6 + gsInvDescY)

#define		ITEMDESC_DESC_START_X		(11 + gsInvDescX)
#define		ITEMDESC_DESC_START_Y		(80 + gsInvDescY)
#define		ITEMDESC_PROS_START_X		( 11 + gsInvDescX )
#define		ITEMDESC_PROS_START_Y		(110 + gsInvDescY)
#define		ITEMDESC_CONS_START_X		( 11 + gsInvDescX )
#define		ITEMDESC_CONS_START_Y		(120 + gsInvDescY)
#define		ITEMDESC_ITEM_STATUS_X					( 6 + gsInvDescX )
#define		ITEMDESC_ITEM_STATUS_Y					( 60 + gsInvDescY )
#define		DOTDOTDOT L"..."
#define		COMMA_AND_SPACE L", "

#define		ITEM_PROS_AND_CONS( usItem ) ( ( Item[ usItem ].usItemClass & IC_GUN && !Item[ usItem ].rocketlauncher ) )

#define		MAP_ITEMDESC_DESC_START_X		( 23 + gsInvDescX )
#define		MAP_ITEMDESC_DESC_START_Y		(170 + gsInvDescY)
#define		MAP_ITEMDESC_PROS_START_X		( 23 + gsInvDescX )
#define		MAP_ITEMDESC_PROS_START_Y		(230 + gsInvDescY)
#define		MAP_ITEMDESC_CONS_START_X		( 23 + gsInvDescX )
#define		MAP_ITEMDESC_CONS_START_Y		(240 + gsInvDescY)
#define		MAP_ITEMDESC_ITEM_STATUS_X					( 18 + gsInvDescX )
#define		MAP_ITEMDESC_ITEM_STATUS_Y					( 53 + gsInvDescY )

#define		ITEMDESC_ITEM_STATUS_WIDTH			2
#define		ITEMDESC_ITEM_STATUS_HEIGHT			50
#define   ITEMDESC_ITEM_STATUS_HEIGHT_MAP 40
#define   ITEMDESC_DESC_WIDTH			301
#define   MAP_ITEMDESC_DESC_WIDTH 220
#define		ITEMDESC_ITEM_WIDTH			117
#define		ITEMDESC_ITEM_HEIGHT		54

#define		ITEMDESC_AMMO_X					( 10 + gsInvDescX )
#define		ITEMDESC_AMMO_Y					( 50 + gsInvDescY )
#define		MAP_ITEMDESC_AMMO_X					( 28 + gsInvDescX )
#define		MAP_ITEMDESC_AMMO_Y					( 45 + gsInvDescY )

#define		ITEMDESC_AMMO_TEXT_X	3
#define		ITEMDESC_AMMO_TEXT_Y	1
#define		ITEMDESC_AMMO_TEXT_WIDTH 31

#define		WORD_WRAP_INV_WIDTH			58

#define		ITEM_BAR_WIDTH					2
#define		ITEM_BAR_HEIGHT					20

#define		ITEM_FONT								TINYFONT1

#define EXCEPTIONAL_DAMAGE					40
#define EXCEPTIONAL_WEIGHT					20
#define EXCEPTIONAL_RANGE					400
#define EXCEPTIONAL_MAGAZINE				50
#define EXCEPTIONAL_AP_COST					5
#define EXCEPTIONAL_BURST_SIZE			5
#define EXCEPTIONAL_RELIABILITY			2
#define EXCEPTIONAL_REPAIR_EASE			2
#define EXCEPTIONAL_ACCURACY			4

#define BAD_DAMAGE									23
#define BAD_WEIGHT									45
#define BAD_RANGE									150
#define BAD_MAGAZINE								10
#define BAD_AP_COST									9
#define BAD_RELIABILITY							-2
#define BAD_REPAIR_EASE							-2
#define BAD_ACCURACY							-1

// CHRISL: Adjust coords for layout changes needed for new inventory system
extern int KEYRING_X;
extern int KEYRING_Y;
extern int MAP_KEYRING_X;
extern int MAP_KEYRING_Y;
//#define KEYRING_X 487
//#define KEYRING_Y (105 + INV_INTERFACE_START_Y)
//#define MAP_KEYRING_X 217
//#define MAP_KEYRING_Y 271
#define KEYRING_WIDTH 30
#define KEYRING_HEIGHT 24
#define TACTICAL_INVENTORY_KEYRING_GRAPHIC_OFFSET_X 215
//enum used for the money buttons
enum
{
	M_1000,
	M_100,
	M_10,
	M_DONE,
};

// AN ARRAY OF MOUSE REGIONS, ONE FOR EACH OBJECT POSITION ON BUDDY
MOUSE_REGION				gInvRegions[ NUM_INV_SLOTS ];

extern	MOUSE_REGION    gMPanelRegion;
extern	BOOLEAN					fMapInventoryItem;
extern	BOOLEAN					gfAddingMoneyToMercFromPlayersAccount;
extern	SOLDIERTYPE			*gpSMCurrentMerc;
extern  UINT8 gubSelectSMPanelToMerc;
extern	MOUSE_REGION		gSM_SELMERCMoneyRegion;
extern	UINT32					guiMapInvSecondHandBlockout;

//jackaians: global variables added for the stealing pickup menu
BOOLEAN				gfStealing = FALSE;
SOLDIERTYPE			*gpOpponent = NULL;

MOUSE_REGION				gInvDesc;

OBJECTTYPE		*gpItemPointer = NULL;
extern OBJECTTYPE		gItemPointer; // symbol already defined in mapscreen.cpp (jonathanl)
BOOLEAN				gfItemPointerDifferentThanDefault = FALSE;
extern SOLDIERTYPE		*gpItemPointerSoldier; // symbol already defined in mapscreen.cpp (jonathanl)
INT8					gbItemPointerSrcSlot;
UINT16				gusItemPointer = 255;
UINT16				usItemSnapCursor;
UINT32				guiNewlyPlacedItemTimer = 0;
BOOLEAN				gfBadThrowItemCTGH;
BOOLEAN				gfDontChargeAPsToPickup = FALSE;
BOOLEAN				gbItemPointerLocateGood = FALSE;

// ITEM DESCRIPTION BOX STUFF
UINT32			guiItemDescBox;
UINT32			guiItemDescBoxBackground;
UINT32      guiMapItemDescBox;
UINT32			guiItemGraphic;
UINT32			guiMoneyGraphicsForDescBox;
UINT32			guiBullet;
BOOLEAN			gfInItemDescBox = FALSE;
UINT32			guiCurrentItemDescriptionScreen=0;
OBJECTTYPE	*gpItemDescObject = NULL;
BOOLEAN			gfItemDescObjectIsAttachment = FALSE;
CHAR16			gzItemName[ SIZE_ITEM_NAME ];
CHAR16			gzItemDesc[ SIZE_ITEM_INFO ];
CHAR16			gzItemPros[ SIZE_ITEM_PROS ];
CHAR16			gzItemCons[ SIZE_ITEM_CONS ];
CHAR16			gzFullItemPros[ SIZE_ITEM_PROS ];
CHAR16			gzFullItemCons[ SIZE_ITEM_PROS ];
CHAR16			gzFullItemTemp[ SIZE_ITEM_PROS ]; // necessary, unfortunately
void ItemDescCallback( MOUSE_REGION * pRegion, INT32 iReason );
INT16				gsInvDescX;
INT16				gsInvDescY;
UINT8				gubItemDescStatusIndex;
INT32				giItemDescAmmoButtonImages;
INT32				giItemDescAmmoButton;
BOOLEAN			gfItemAmmoDown = FALSE;
SOLDIERTYPE *gpItemDescSoldier;
BOOLEAN			fItemDescDelete = FALSE;
MOUSE_REGION		gItemDescAttachmentRegions[MAX_ATTACHMENTS];
MOUSE_REGION		gProsAndConsRegions[2];

void				BtnMoneyButtonCallback(GUI_BUTTON *btn,INT32 reason);
UINT32			guiMoneyButtonBtn[MAX_ATTACHMENTS];
INT32				guiMoneyButtonImage;
INT32				guiMoneyDoneButtonImage;

attachmentList	gOriginalAttachments;
SOLDIERTYPE * gpAttachSoldier;
extern BOOLEAN	gfSMDisableForItems;


typedef struct
{
	UINT16 x;
	UINT16 y;
} MoneyLoc;

/*
 * Yes i know thats a little bit compicated but remeber that we have now only tactical screen
 * a little bit dynamic and customizable.
 * gMoneyButtonLoc its a location of money button
 * we need to initialize it in run-time becouse we dona have constant initializer
 * any questions? joker
 */
MoneyLoc			gMoneyButtonLoc;// =			{ (343 + INTERFACE_START_Y), ( 11 + INV_INTERFACE_START_Y ) };
MoneyLoc			gMoneyButtonOffsets[] = { 0,0,  34,0,  0,32, 34,32, 8,22 };
MoneyLoc			gMapMoneyButtonLoc =	{ 174, 115 };

// show the description
extern BOOLEAN fShowDescriptionFlag;
extern BOOLEAN fShowInventoryFlag;

void ItemDescAttachmentsCallback( MOUSE_REGION * pRegion, INT32 iReason );
void ItemDescAmmoCallback(GUI_BUTTON *btn,INT32 reason);
void DeletePool(ITEM_POOL *pItemPool);

// number of keys on keyring, temp for now
#define			NUMBER_KEYS_ON_KEYRING 28
#define			KEY_RING_ROW_WIDTH 7
#define			MAP_KEY_RING_ROW_WIDTH 4
#define			INV_ITEM_ROW_WIDTH 7
#define			MAP_INV_ITEM_ROW_WIDTH 4

// ITEM STACK POPUP STUFF
BOOLEAN			gfInItemStackPopup = FALSE;
BOOLEAN			gfInSectorStackPopup = FALSE;
UINT32			guiItemPopupBoxes;
OBJECTTYPE	*gpItemPopupObject;
INT16				gsItemPopupWidth;
INT16				gsItemPopupHeight;
INT16				gsItemPopupX;
INT16				gsItemPopupY;
MOUSE_REGION				gItemPopupRegions[MAX_OBJECTS_PER_SLOT];
MOUSE_REGION				gKeyRingRegions[ NUMBER_KEYS_ON_KEYRING ];
BOOLEAN							gfInKeyRingPopup = FALSE;
UINT8								gubNumItemPopups = 0;
MOUSE_REGION				gItemPopupRegion;
INT16				gsItemPopupInvX;
INT16				gsItemPopupInvY;
INT16				gsItemPopupInvWidth;
INT16				gsItemPopupInvHeight;

INT16				gsKeyRingPopupInvX;
INT16				gsKeyRingPopupInvY;
INT16				gsKeyRingPopupInvWidth;
INT16				gsKeyRingPopupInvHeight;


SOLDIERTYPE *gpItemPopupSoldier;
extern BOOLEAN fMapScreenBottomDirty;

// inventory description done button for mapscreen
INT32 giMapInvDescButtonImage;
INT32 giMapInvDescButton = -1;

// the done descrition button callback
void ItemDescDoneButtonCallback( GUI_BUTTON *btn, INT32 reason );


extern BOOLEAN fMapInventoryItem;
BOOLEAN	gfItemPopupRegionCallbackEndFix = FALSE;
extern void InternalMAPBeginItemPointer( SOLDIERTYPE *pSoldier );


void	ItemPopupRegionCallback( MOUSE_REGION * pRegion, INT32 iReason );
void ItemPopupFullRegionCallback( MOUSE_REGION * pRegion, INT32 iReason );
BOOLEAN ReloadItemDesc( );


extern void HelpTextDoneCallback( void );
void RemoveMoney();
BOOLEAN	CompatibleItemForApplyingOnMerc( OBJECTTYPE *pTestObject );

extern BOOLEAN MAPInternalInitItemDescriptionBox( OBJECTTYPE *pObject, UINT8 ubStatusIndex, SOLDIERTYPE *pSoldier );
extern void	StartSKIDescriptionBox( void );

void UpdateItemHatches();

extern void BeginInventoryPoolPtr( OBJECTTYPE *pInventorySlot );

UINT8		ubRGBItemCyclePlacedItemColors[] =
{
	25,		25,		25,
	50,		50,		50,
	75,   75,   75,
	100,	100,	100,
	125,	125,	125,
	150,	150,	150,
	175,	175,	175,
	200,	200,	200,
	225,	225,	225,
	250,	250,	250,

	250,	250,	250,
	225,	225,	225,
	200,	200,	200,
	175,	175,	175,
	150,	150,	150,
	125,	125,	125,
	100,	100,	100,
	75,   75,   75,
	50,		50,		50,
	25,		25,		25

};


typedef struct
{
	INT16		sX;
	INT16		sY;
	INT16		sValDx;

} INV_DESC_STATS;

typedef struct
{
	INT16		sX;
	INT16		sY;
	INT16		sHeight;
	INT16		sWidth;
	INT16		sBarDx;
	INT16		sBarDy;

} INV_ATTACHXY;

#define NUM_INV_HELPTEXT_ENTRIES 1

typedef struct
{
	INT32 iXPosition[NUM_INV_HELPTEXT_ENTRIES];
	INT32 iYPosition[NUM_INV_HELPTEXT_ENTRIES];
	INT32 iWidth[NUM_INV_HELPTEXT_ENTRIES];
	STR16 sString1[NUM_INV_HELPTEXT_ENTRIES];
	STR16 sString2[NUM_INV_HELPTEXT_ENTRIES];
} INV_HELPTEXT;


INV_DESC_STATS gWeaponStats[] =
{
	202,		25,			83,
	202,		15,			83,
	202,		15,			83,
	265,		40,			20,
	202,		40,			32,
	202,		50,			32,
	265,		50,			20,
	234,		50,			0,
	290,		50,			0,
};


// displayed AFTER the mass/weight/"Kg" line
INV_DESC_STATS gMoneyStats[] =
{
	202,		14,			78,
	212,		25,			78,
	202,		40,			78,
	212,		51,			78,
};

// displayed AFTER the mass/weight/"Kg" line
INV_DESC_STATS gMapMoneyStats[] =
{
	51,		97,				45,
	61,		107,			75,
	51,		125,			45,
	61,		135,			70,
};


INV_DESC_STATS gMapWeaponStats[] =
{
	72 - 20,		20+80+8,		80,
	72 - 20,		20+80-2,		80,
	72 - 20,		20+80-2,		80,
	72+65 - 20,	40+80+4,		21,
	72 - 20,		40+80+4,		30,
	72 - 20,		53+80+2,			30,
	72+65 - 20,	53+80+2,			25,
	86,					53+80+2,			0,
	145,				53+80+2,			0,

};


INV_ATTACHXY	gItemDescAttachmentsXY[] =
{
	129,		12,		SM_INV_SLOT_HEIGHT,		SM_INV_SLOT_WIDTH,		INV_BAR_DX-1,		INV_BAR_DY+1,
	163,		12,		SM_INV_SLOT_HEIGHT,		SM_INV_SLOT_WIDTH,		INV_BAR_DX-1,		INV_BAR_DY+1,
	129,		39,		SM_INV_SLOT_HEIGHT,		SM_INV_SLOT_WIDTH,		INV_BAR_DX-1,		INV_BAR_DY+1,
	163,		39,		SM_INV_SLOT_HEIGHT,		SM_INV_SLOT_WIDTH,		INV_BAR_DX-1,		INV_BAR_DY+1
};

INV_ATTACHXY gMapItemDescAttachmentsXY[] =
{
  173,		10,		SM_INV_SLOT_HEIGHT,		26,		INV_BAR_DX + 2,		INV_BAR_DY,
	211,		10,		SM_INV_SLOT_HEIGHT,		26,		INV_BAR_DX + 2,		INV_BAR_DY,
	173,		36,		SM_INV_SLOT_HEIGHT,		26,		INV_BAR_DX + 2,		INV_BAR_DY,
	211,		36,		SM_INV_SLOT_HEIGHT,		26,		INV_BAR_DX + 2,		INV_BAR_DY
};

SGPRect gItemDescProsConsRects[] =
{// NB the left value is calculated based on the width of the 'pros' and 'cons' labels
	0, 111, 313, 118,
	0, 119, 313, 126
};

SGPRect gMapItemDescProsConsRects[] =
{
	0, 231, 313, 238,
	0, 239, 313, 246,
};


INV_HELPTEXT gItemDescHelpText =
{
	{ 69 }, // x locations
	{ 12 }, // y locations
	{ 170 }, // widths
	{ Message[STR_ATTACHMENT_HELP] },
	{ Message[STR_ATTACHMENT_INVALID_HELP] },
};

BOOLEAN gfItemDescHelpTextOffset = FALSE;

// ARRAY FOR INV PANEL INTERFACE ITEM POSITIONS (sX,sY get set via InitInvSlotInterface() )
/* CHRISL: Add new region definitions for the new inventory slots needed for the new inventory
system to work properly. */
INV_REGIONS gSMInvData[NUM_INV_SLOTS];


typedef struct
{
	UINT32	uiTotalAmount;
	UINT32	uiMoneyRemaining;
	UINT32	uiMoneyRemoving;

} REMOVE_MONEY;
REMOVE_MONEY gRemoveMoney;

MOUSE_REGION		gSMInvRegion[ NUM_INV_SLOTS ];
MOUSE_REGION		gKeyRingPanel;
MOUSE_REGION		gSMInvCamoRegion;
INT8						gbCompatibleAmmo[ NUM_INV_SLOTS ];
INT8						gbInvalidPlacementSlot[ NUM_INV_SLOTS ];
UINT16					us16BPPItemCyclePlacedItemColors[ 20 ];
// Kaiden: Vehicle Inventory change - Increase this from 4-2 to 5-2
UINT32					guiBodyInvVO[ 5 ][ 2 ];
UINT32					guiGoldKeyVO;
INT8						gbCompatibleApplyItem = FALSE;

BOOLEAN AttemptToAddSubstring( STR16 zDest, STR16 zTemp, UINT32 * puiStringLength, UINT32 uiPixLimit )
{
	UINT32 uiRequiredStringLength, uiTempStringLength;

	uiTempStringLength = StringPixLength( zTemp, ITEMDESC_FONT );
	uiRequiredStringLength = *puiStringLength + uiTempStringLength;
	if (zDest[0] != 0)
	{
		uiRequiredStringLength += StringPixLength( COMMA_AND_SPACE, ITEMDESC_FONT );
	}
	if (uiRequiredStringLength < uiPixLimit)
	{
		if (zDest[0] != 0)
		{
			wcscat( zDest, COMMA_AND_SPACE );
		}
		wcscat( zDest, zTemp );
		*puiStringLength = uiRequiredStringLength;
		return( TRUE );
	}
	else
	{
		wcscat( zDest, DOTDOTDOT );
		return( FALSE );
	}
}

void GenerateProsString( STR16 zItemPros, OBJECTTYPE * pObject, UINT32 uiPixLimit )
{
	UINT32			uiStringLength = 0;
	STR16		zTemp;
	UINT16			usItem = pObject->usItem;
	UINT16				ubWeight;

	zItemPros[0] = 0;

	ubWeight = Item[ usItem ].ubWeight;
	if (Item[ usItem ].usItemClass == IC_GUN)
	{
		ubWeight = ubWeight + Item[ (*pObject)[0]->data.gun.usGunAmmoItem ].ubWeight;
	}

	if (Weapon[usItem].bAccuracy >= EXCEPTIONAL_ACCURACY )
	{
		zTemp = Message[STR_ACCURATE];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (Item[usItem].ubWeight <= EXCEPTIONAL_WEIGHT)
	{
		zTemp = Message[STR_LIGHT];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	//CHRISL: Using "FitsInSmallPocket" in NewInv will result in every item appearing to be "small".  We don't want that so
	// so in this case, even in NewInv, we should look at the items ubPerPocket value.
	//if (FitsInSmallPocket(pObject) == true) // fits in a small pocket
	if (Item[usItem].ubPerPocket >= 1) // fits in a small pocket
	{
		zTemp = Message[STR_SMALL];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( GunRange( pObject ) >= EXCEPTIONAL_RANGE )
	{
		zTemp = Message[STR_LONG_RANGE];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (GetDamage(pObject) >= EXCEPTIONAL_DAMAGE)
	{
		zTemp = Message[STR_HIGH_DAMAGE];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (BaseAPsToShootOrStab( DEFAULT_APS, DEFAULT_AIMSKILL, gpItemDescObject ) <= EXCEPTIONAL_AP_COST)
	{
		zTemp = Message[STR_QUICK_FIRING];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (GetShotsPerBurst(pObject) >= EXCEPTIONAL_BURST_SIZE )//|| usItem == G11)
	{
		zTemp = Message[STR_FAST_BURST];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (GetMagSize(pObject) > EXCEPTIONAL_MAGAZINE)
	{
		zTemp = Message[STR_LARGE_AMMO_CAPACITY];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( Item[usItem].bReliability >= EXCEPTIONAL_RELIABILITY )
	{
		zTemp = Message[STR_RELIABLE];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( Item[usItem].bRepairEase >= EXCEPTIONAL_REPAIR_EASE )
	{
		zTemp = Message[STR_EASY_TO_REPAIR];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (GetAutofireShotsPerFiveAPs(pObject) > 0)
	{
		zTemp = Message[STR_AUTOFIRE];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( zItemPros[0] == 0 )
	{
		// empty string, so display "None"
		if ( ! AttemptToAddSubstring( zItemPros, Message[ STR_NONE ], &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}
}

void GenerateConsString( STR16 zItemCons, OBJECTTYPE * pObject, UINT32 uiPixLimit )
{
	UINT32			uiStringLength = 0;
	STR16		zTemp;
	UINT16				ubWeight;
	UINT16			usItem = pObject->usItem;

	zItemCons[0] = 0;

	if (Weapon[usItem].bAccuracy <= BAD_ACCURACY)
	{
		zTemp = Message[STR_INACCURATE];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( Weapon[usItem].NoSemiAuto )
	{
		zTemp = Message[STR_NO_SEMI_AUTO];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	// calculate the weight of the item plus ammunition but not including any attachments
	ubWeight = Item[ usItem ].ubWeight;
	if (Item[ usItem ].usItemClass == IC_GUN)
	{
		ubWeight = ubWeight + CalculateAmmoWeight((*pObject)[0]->data.gun.usGunAmmoItem, (*pObject)[0]->data.gun.ubGunShotsLeft);
		//ubWeight = ubWeight + Item[ (*pObject)[0]->data.gun.usGunAmmoItem ].ubWeight;
	}

	if (ubWeight >= BAD_WEIGHT)
	{
		zTemp = Message[STR_HEAVY];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( GunRange( pObject ) <= BAD_RANGE)
	{
		zTemp = Message[STR_SHORT_RANGE];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}


	if (GetDamage(pObject) <= BAD_DAMAGE)
	{
		zTemp = Message[STR_LOW_DAMAGE];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (BaseAPsToShootOrStab( DEFAULT_APS, DEFAULT_AIMSKILL, gpItemDescObject ) >= BAD_AP_COST)
	{
		zTemp = Message[STR_SLOW_FIRING];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (GetShotsPerBurst(pObject) == 0)
	{
		zTemp = Message[STR_NO_BURST];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (GetAutofireShotsPerFiveAPs(pObject) == 0)
	{
		zTemp = Message[STR_NO_AUTOFIRE];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (GetMagSize(pObject) < BAD_MAGAZINE)
	{
		zTemp = Message[STR_SMALL_AMMO_CAPACITY];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( Item[usItem].bReliability <= BAD_RELIABILITY )
	{
		zTemp = Message[STR_UNRELIABLE];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( Item[usItem].bRepairEase <= BAD_REPAIR_EASE )
	{
		zTemp = Message[STR_HARD_TO_REPAIR];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}


	if ( zItemCons[0] == 0 )
	{
		// empty string, so display "None"
		if ( ! AttemptToAddSubstring( zItemCons, Message[ STR_NONE ], &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}
}

// CHRISL: New function to setup GSMInvData based on game options
void InitInvData(INV_REGIONS &InvData, BOOLEAN fBigPocket, INT16 sBarDx, INT16 sBarDy, INT16 sWidth, INT16 sHeight, INT16 sX, INT16 sY)
{
	InvData.fBigPocket = fBigPocket;
	InvData.sBarDx = sBarDx;
	InvData.sBarDy = sBarDy;
	InvData.sHeight = sHeight;
	InvData.sWidth = sWidth;
	InvData.sX = sX;
	InvData.sY = sY;
}
void InitInventoryOld()
{
	BODYPOSFINAL		= GUNSLINGPOCKPOS;//RESET in initInventory
	BIGPOCKFINAL		= BIGPOCK5POS;//RESET in initInventory
	MEDPOCKSTART		= SMALLPOCK1POS;//RESET in initInventory
	MEDPOCKFINAL		= SMALLPOCK1POS;//RESET in initInventory
	SMALLPOCKFINAL		= SMALLPOCK9POS;//RESET in initInventory


	InitInvData(gSMInvData[HELMETPOS],		FALSE,	INV_BAR_DX,	INV_BAR_DY,	HEAD_INV_SLOT_WIDTH,	HEAD_INV_SLOT_HEIGHT,	0, 0);	// HELMETPOS
	InitInvData(gSMInvData[VESTPOS],		FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// VESTPOS
	InitInvData(gSMInvData[LEGPOS],			FALSE,	INV_BAR_DX,	INV_BAR_DY,	LEGS_INV_SLOT_WIDTH,	LEGS_INV_SLOT_HEIGHT,	0, 0);	// LEGPOS
	InitInvData(gSMInvData[HEAD1POS],		FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// HEAD1POS
	InitInvData(gSMInvData[HEAD2POS],		FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// HEAD2POS
	InitInvData(gSMInvData[HANDPOS],		TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// HANDPOS
	InitInvData(gSMInvData[SECONDHANDPOS],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// SECONDHANDPOS
	InitInvData(gSMInvData[BIGPOCK1POS],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// BIGPOCK1
	InitInvData(gSMInvData[BIGPOCK2POS],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// BIGPOCK2
	InitInvData(gSMInvData[BIGPOCK3POS],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// BIGPOCK3
	InitInvData(gSMInvData[BIGPOCK4POS],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// BIGPOCK4
	InitInvData(gSMInvData[SMALLPOCK1POS],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK1
	InitInvData(gSMInvData[SMALLPOCK2POS],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK2
	InitInvData(gSMInvData[SMALLPOCK3POS],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK3
	InitInvData(gSMInvData[SMALLPOCK4POS],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK4
	InitInvData(gSMInvData[SMALLPOCK5POS],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK5
	InitInvData(gSMInvData[SMALLPOCK6POS],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK6
	InitInvData(gSMInvData[SMALLPOCK7POS],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK7
	InitInvData(gSMInvData[SMALLPOCK8POS],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK8
}
void InitInventoryNew()
{
	BODYPOSFINAL		= GUNSLINGPOCKPOS;//RESET in initInventory
	BIGPOCKFINAL		= MEDPOCK1POS;//RESET in initInventory
	MEDPOCKSTART		= MEDPOCK1POS;//RESET in initInventory
	MEDPOCKFINAL		= SMALLPOCK1POS;//RESET in initInventory
	SMALLPOCKFINAL		= NUM_INV_SLOTS;//RESET in initInventory

	if(iResolution == 0){
		InitInvData(gSMInvData[0],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	HEAD_INV_SLOT_WIDTH,	HEAD_INV_SLOT_HEIGHT,	0, 0);	// HELMETPOS
		InitInvData(gSMInvData[1],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// VESTPOS
		InitInvData(gSMInvData[2],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	LEGS_INV_SLOT_WIDTH,	LEGS_INV_SLOT_HEIGHT,	0, 0);	// LEGPOS
		InitInvData(gSMInvData[3],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// HEAD1POS
		InitInvData(gSMInvData[4],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// HEAD2POS
		InitInvData(gSMInvData[5],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// HANDPOS
		InitInvData(gSMInvData[6],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// SECONDHANDPOS
		InitInvData(gSMInvData[7],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	30,	20,	0, 0);	// VESTPOCKPOS
		InitInvData(gSMInvData[8],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	30,	20,	0, 0);	// LTHIGHPOCKPOS
		InitInvData(gSMInvData[9],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	30,	20,	0, 0);	// RTHIGHPOCKPOS
		InitInvData(gSMInvData[10],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	30,	20,	0, 0);	// CPACKPOCKPOS
		InitInvData(gSMInvData[11],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	30,	20,	0, 0);	// BPACKPOCKPOS
		InitInvData(gSMInvData[12],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	48,	20,	0, 0);	// GUNSLINGPOCKPOS
		InitInvData(gSMInvData[13],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// KNIFEPOCKPOS
		InitInvData(gSMInvData[14],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	48,	20,	0, 0);	// BIGPOCK1
		InitInvData(gSMInvData[15],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	48,	20,	0, 0);	// BIGPOCK2
		InitInvData(gSMInvData[16],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	48,	20,	0, 0);	// BIGPOCK3
		InitInvData(gSMInvData[17],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	48,	20,	0, 0);	// BIGPOCK4
		InitInvData(gSMInvData[18],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	48,	20,	0, 0);	// BIGPOCK5
		InitInvData(gSMInvData[19],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	48,	20,	0, 0);	// BIGPOCK6
		InitInvData(gSMInvData[20],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	48,	20,	0, 0);	// BIGPOCK7
		InitInvData(gSMInvData[21],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	30,	20,	0, 0);	// MEDPOCK1
		InitInvData(gSMInvData[22],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	30,	20,	0, 0);	// MEDPOCK2
		InitInvData(gSMInvData[23],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	30,	20,	0, 0);	// MEDPOCK3
		InitInvData(gSMInvData[24],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	30,	20,	0, 0);	// MEDPOCK4
		InitInvData(gSMInvData[25],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK1
		InitInvData(gSMInvData[26],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK2
		InitInvData(gSMInvData[27],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK3
		InitInvData(gSMInvData[28],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK4
		InitInvData(gSMInvData[29],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK5
		InitInvData(gSMInvData[30],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK6
		InitInvData(gSMInvData[31],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK7
		InitInvData(gSMInvData[32],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK8
		InitInvData(gSMInvData[33],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK9
		InitInvData(gSMInvData[34],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK10
		InitInvData(gSMInvData[35],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK11
		InitInvData(gSMInvData[36],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK12
		InitInvData(gSMInvData[37],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK13
		InitInvData(gSMInvData[38],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK14
		InitInvData(gSMInvData[39],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK15
		InitInvData(gSMInvData[40],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK16
		InitInvData(gSMInvData[41],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK17
		InitInvData(gSMInvData[42],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK18
		InitInvData(gSMInvData[43],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK19
		InitInvData(gSMInvData[44],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK20
		InitInvData(gSMInvData[45],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK21
		InitInvData(gSMInvData[46],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK22
		InitInvData(gSMInvData[47],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK23
		InitInvData(gSMInvData[48],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK24
		InitInvData(gSMInvData[49],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK25
		InitInvData(gSMInvData[50],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK26
		InitInvData(gSMInvData[51],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK27
		InitInvData(gSMInvData[52],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK28
		InitInvData(gSMInvData[52],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK29
		InitInvData(gSMInvData[54],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	17,	20,	0, 0);	// SMALLPOCK30
	}
	else{
		InitInvData(gSMInvData[0],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	HEAD_INV_SLOT_WIDTH,	HEAD_INV_SLOT_HEIGHT,	0, 0);	// HELMETPOS
		InitInvData(gSMInvData[1],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// VESTPOS
		InitInvData(gSMInvData[2],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	LEGS_INV_SLOT_WIDTH,	LEGS_INV_SLOT_HEIGHT,	0, 0);	// LEGPOS
		InitInvData(gSMInvData[3],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// HEAD1POS
		InitInvData(gSMInvData[4],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// HEAD2POS
		InitInvData(gSMInvData[5],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// HANDPOS
		InitInvData(gSMInvData[6],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// SECONDHANDPOS
		InitInvData(gSMInvData[7],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// VESTPOCKPOS
		InitInvData(gSMInvData[8],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// LTHIGHPOCKPOS
		InitInvData(gSMInvData[9],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// RTHIGHPOCKPOS
		InitInvData(gSMInvData[10],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// CPACKPOCKPOS
		InitInvData(gSMInvData[11],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// BPACKPOCKPOS
		InitInvData(gSMInvData[12],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// GUNSLINGPOCKPOS
		InitInvData(gSMInvData[13],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// KNIFEPOCKPOS
		InitInvData(gSMInvData[14],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// BIGPOCK1
		InitInvData(gSMInvData[15],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// BIGPOCK2
		InitInvData(gSMInvData[16],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// BIGPOCK3
		InitInvData(gSMInvData[17],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// BIGPOCK4
		InitInvData(gSMInvData[18],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// BIGPOCK5
		InitInvData(gSMInvData[19],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// BIGPOCK6
		InitInvData(gSMInvData[20],	TRUE,	INV_BAR_DX,	INV_BAR_DY,	BIG_INV_SLOT_WIDTH,		BIG_INV_SLOT_HEIGHT,	0, 0);	// BIGPOCK7
		InitInvData(gSMInvData[21],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// MEDPOCK1
		InitInvData(gSMInvData[22],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// MEDPOCK2
		InitInvData(gSMInvData[23],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// MEDPOCK3
		InitInvData(gSMInvData[24],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	VEST_INV_SLOT_WIDTH,	VEST_INV_SLOT_HEIGHT,	0, 0);	// MEDPOCK4
		InitInvData(gSMInvData[25],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK1
		InitInvData(gSMInvData[26],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK2
		InitInvData(gSMInvData[27],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK3
		InitInvData(gSMInvData[28],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK4
		InitInvData(gSMInvData[29],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK5
		InitInvData(gSMInvData[30],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK6
		InitInvData(gSMInvData[31],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK7
		InitInvData(gSMInvData[32],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK8
		InitInvData(gSMInvData[33],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK9
		InitInvData(gSMInvData[34],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK10
		InitInvData(gSMInvData[35],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK11
		InitInvData(gSMInvData[36],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK12
		InitInvData(gSMInvData[37],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK13
		InitInvData(gSMInvData[38],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK14
		InitInvData(gSMInvData[39],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK15
		InitInvData(gSMInvData[40],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK16
		InitInvData(gSMInvData[41],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK17
		InitInvData(gSMInvData[42],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK18
		InitInvData(gSMInvData[43],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK19
		InitInvData(gSMInvData[44],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK20
		InitInvData(gSMInvData[45],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK21
		InitInvData(gSMInvData[46],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK22
		InitInvData(gSMInvData[47],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK23
		InitInvData(gSMInvData[48],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK24
		InitInvData(gSMInvData[49],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK25
		InitInvData(gSMInvData[50],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK26
		InitInvData(gSMInvData[51],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK27
		InitInvData(gSMInvData[52],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK28
		InitInvData(gSMInvData[53],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK29
		InitInvData(gSMInvData[54],	FALSE,	INV_BAR_DX,	INV_BAR_DY,	SM_INV_SLOT_WIDTH,		SM_INV_SLOT_HEIGHT,		0, 0);	// SMALLPOCK30
	}
}
void InitInventoryVehicle(INV_REGION_DESC *pRegionDesc, MOUSE_CALLBACK INVMoveCallback, MOUSE_CALLBACK INVClickCallback, BOOLEAN fSetHighestPrioity)
{
	for(int cnt=INV_START_POS; cnt<NUM_INV_SLOTS; cnt++)
	{
		MSYS_RemoveRegion( &gSMInvRegion[ cnt ]);
		if(vehicleInv[cnt])
			InitInvData(gSMInvData[cnt], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, pRegionDesc[cnt].sX, pRegionDesc[cnt].sY);
		else
			InitInvData(gSMInvData[cnt], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, 0, 0);
		MSYS_DefineRegion( &gSMInvRegion[ cnt ], gSMInvData[ cnt ].sX, gSMInvData[ cnt ].sY, (INT16)(gSMInvData[ cnt ].sX + gSMInvData[ cnt ].sWidth), (INT16)(gSMInvData[ cnt ].sY + gSMInvData[ cnt ].sHeight), ( INT8 )( fSetHighestPrioity ? MSYS_PRIORITY_HIGHEST : MSYS_PRIORITY_HIGH ),
							 MSYS_NO_CURSOR, INVMoveCallback, INVClickCallback ); 
		// Add region
		MSYS_AddRegion( &gSMInvRegion[ cnt ] );
		MSYS_SetRegionUserData( &gSMInvRegion[ cnt ], 0, cnt );
	}
}
// CHRISL: Function to recreate inventory mouse regions
void InitInventorySoldier(INV_REGION_DESC *pRegionDesc, MOUSE_CALLBACK INVMoveCallback, MOUSE_CALLBACK INVClickCallback, BOOLEAN fSetHighestPrioity)
{
	InitInventoryNew();
	for(int cnt=INV_START_POS; cnt<NUM_INV_SLOTS; cnt++)
	{
		gSMInvData[ cnt ].sX = pRegionDesc[cnt].sX;
		gSMInvData[ cnt ].sY = pRegionDesc[cnt].sY;
		MSYS_RemoveRegion( &gSMInvRegion[ cnt ]);
		MSYS_DefineRegion( &gSMInvRegion[ cnt ], gSMInvData[ cnt ].sX, gSMInvData[ cnt ].sY, (INT16)(gSMInvData[ cnt ].sX + gSMInvData[ cnt ].sWidth), (INT16)(gSMInvData[ cnt ].sY + gSMInvData[ cnt ].sHeight), ( INT8 )( fSetHighestPrioity ? MSYS_PRIORITY_HIGHEST : MSYS_PRIORITY_HIGH ),
							 MSYS_NO_CURSOR, INVMoveCallback, INVClickCallback ); 
		// Add region
		MSYS_AddRegion( &gSMInvRegion[ cnt ] );
		MSYS_SetRegionUserData( &gSMInvRegion[ cnt ], 0, cnt );
	}
}

BOOLEAN InitInvSlotInterface( INV_REGION_DESC *pRegionDesc , INV_REGION_DESC *pCamoRegion, MOUSE_CALLBACK INVMoveCallback, MOUSE_CALLBACK INVClickCallback, MOUSE_CALLBACK INVMoveCammoCallback, MOUSE_CALLBACK INVClickCammoCallback, BOOLEAN fSetHighestPrioity )
{
	INT32 cnt;
  VOBJECT_DESC    VObjectDesc;

/*
 *  Ok i think that here the money button and window is initialized
 *  so we also will initialize here coord of button
 *  this function is called in tactical screen when SMPanel is initialized
 *  and also in StrategicScreen i think i didnt check it.
 *  any questions? joker
 */

	// CHRISL: Adjusted location of the Money button on the tactical inventory screen
	gMoneyButtonLoc.x = ((UsingNewInventorySystem() == false)) ? (343 + INTERFACE_START_X) : (388 + INTERFACE_START_X);
	gMoneyButtonLoc.y = ( 11 + INV_INTERFACE_START_Y );
	// Load all four body type images
	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\inventory_figure_large_male.sti", VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(guiBodyInvVO[ 1 ][ 0 ] ) ) );

	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\inventory_figure_large_male_H.sti", VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(guiBodyInvVO[ 1 ][ 1 ] ) ) );


	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\inventory_normal_male.sti", VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(guiBodyInvVO[ 0 ][ 0 ] ) ) );

	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\inventory_normal_male_H.sti", VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(guiBodyInvVO[ 0 ][ 1 ] ) ) );


	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\inventory_normal_male.sti", VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(guiBodyInvVO[ 2 ][ 0 ] ) ) );

	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\inventory_normal_male.sti", VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(guiBodyInvVO[ 2 ][ 1 ] ) ) );

	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\inventory_figure_female.sti", VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(guiBodyInvVO[ 3 ][ 0 ] ) ) );

	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\inventory_figure_female_H.sti", VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(guiBodyInvVO[ 3 ][ 1 ] ) ) );

	// Kaiden: Vehicle Inventory change - Added two new STI's for Vehicle Inventory
	// Feel free to change them to more appropriate pictures, I just blanked out
	// the body image for now, I'm no graphics artist.
	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\inventory_figure_Vehicle.sti",
VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(guiBodyInvVO[ 4 ][ 0 ] ) ) );

	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\inventory_figure_Vehicle_h.sti",
VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(guiBodyInvVO[ 4 ][ 1 ] ) ) );

	// add gold key graphic
	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\gold_key_button.sti", VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &guiGoldKeyVO ) );

	// Add cammo region
	MSYS_DefineRegion( &gSMInvCamoRegion, pCamoRegion->sX, pCamoRegion->sY, (INT16)(pCamoRegion->sX + CAMO_REGION_WIDTH ), (INT16)(pCamoRegion->sY + CAMO_REGION_HEIGHT ), MSYS_PRIORITY_HIGH,
						 MSYS_NO_CURSOR, INVMoveCammoCallback, INVClickCammoCallback );
	// Add region
	MSYS_AddRegion( &gSMInvCamoRegion );

	// Add regions for inventory slots
	for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
	{
		// set inventory pocket coordinates from the table passed in
		gSMInvData[ cnt ].sX = pRegionDesc[ cnt ].sX;
		gSMInvData[ cnt ].sY = pRegionDesc[ cnt ].sY;

		MSYS_DefineRegion( &gSMInvRegion[ cnt ], gSMInvData[ cnt ].sX, gSMInvData[ cnt ].sY, (INT16)(gSMInvData[ cnt ].sX + gSMInvData[ cnt ].sWidth), (INT16)(gSMInvData[ cnt ].sY + gSMInvData[ cnt ].sHeight), ( INT8 )( fSetHighestPrioity ? MSYS_PRIORITY_HIGHEST : MSYS_PRIORITY_HIGH ),
							 MSYS_NO_CURSOR, INVMoveCallback, INVClickCallback );
		// Add region
		MSYS_AddRegion( &gSMInvRegion[ cnt ] );
		MSYS_SetRegionUserData( &gSMInvRegion[ cnt ], 0, cnt );
	}

	memset( gbCompatibleAmmo, 0, sizeof( gbCompatibleAmmo ) );

	return( TRUE );
}

void InitKeyRingInterface( MOUSE_CALLBACK KeyRingClickCallback )
{
		MSYS_DefineRegion( &gKeyRingPanel, KEYRING_X, KEYRING_Y, KEYRING_X + KEYRING_WIDTH, KEYRING_Y + KEYRING_HEIGHT, MSYS_PRIORITY_HIGH,
							 MSYS_NO_CURSOR, MSYS_NO_CALLBACK, KeyRingClickCallback );

		SetRegionFastHelpText( &(gKeyRingPanel), TacticalStr[ KEYRING_HELP_TEXT ] );

}

void InitMapKeyRingInterface( MOUSE_CALLBACK KeyRingClickCallback )
{
		MSYS_DefineRegion( &gKeyRingPanel, MAP_KEYRING_X, MAP_KEYRING_Y, MAP_KEYRING_X + KEYRING_WIDTH, MAP_KEYRING_Y + KEYRING_HEIGHT, MSYS_PRIORITY_HIGH,
							 MSYS_NO_CURSOR, MSYS_NO_CALLBACK, KeyRingClickCallback );

		SetRegionFastHelpText( &(gKeyRingPanel), TacticalStr[ KEYRING_HELP_TEXT ] );
}

void EnableKeyRing( BOOLEAN fEnable )
{
	if ( fEnable )
	{
		MSYS_EnableRegion( &gKeyRingPanel );
	}
	else
	{
		MSYS_DisableRegion( &gKeyRingPanel );
	}
}


void ShutdownKeyRingInterface( void )
{
	MSYS_RemoveRegion( &gKeyRingPanel );
	return;
}

void DisableInvRegions( BOOLEAN fDisable )
{
	INT32 cnt;

	for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
	{
		if ( fDisable )
		{
			MSYS_DisableRegion( &gSMInvRegion[ cnt ] );
		}
		else
		{
			MSYS_EnableRegion( &gSMInvRegion[ cnt ] );
		}
	}

	if ( fDisable )
	{
		MSYS_DisableRegion( &gSMInvCamoRegion );

		MSYS_DisableRegion( &gSM_SELMERCMoneyRegion );
		EnableKeyRing( FALSE );
		RenderBackpackButtons(3);	/* CHRISL: Needed for new inventory backpack buttons */
	}
	else
	{
		MSYS_EnableRegion( &gSMInvCamoRegion );

		MSYS_EnableRegion( &gSM_SELMERCMoneyRegion );
		EnableKeyRing( TRUE );
		RenderBackpackButtons(2);	/* CHRISL: Needed for new inventory backpack buttons */
	}

}

void ShutdownInvSlotInterface( )
{
	UINT32		cnt;

	// Kaiden: Vehicle Inventory change - Added 4-0 and 4-1
    // to be deleted as well.

	// Remove all body type panels
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 0 ][ 0 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 2 ][ 0 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 1 ][ 0 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 3 ][ 0 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 4 ][ 0 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 0 ][ 1 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 2 ][ 1 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 1 ][ 1 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 3 ][ 1 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 4 ][ 1 ] );

	DeleteVideoObjectFromIndex( guiGoldKeyVO );

	// Remove regions
	// Add regions for inventory slots
	for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
	{
		// Remove region
		MSYS_RemoveRegion( &gSMInvRegion[ cnt ] );
	}

	// Remove cammo
	MSYS_RemoveRegion( &gSMInvCamoRegion );

}

void RenderInvBodyPanel( SOLDIERTYPE *pSoldier, INT16 sX, INT16 sY )
{
	// Blit body inv, based on body type
	INT8 bSubImageIndex = gbCompatibleApplyItem;

	// Kaiden: Vehicle Inventory change - Added IF Test, Else function call was
	// the original statement
	if ( (gGameExternalOptions.fVehicleInventory) && (pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE) )
	{
		BltVideoObjectFromIndex( guiSAVEBUFFER, guiBodyInvVO[4][0], 0, sX, sY, VO_BLT_SRCTRANSPARENCY, NULL );
	}
	else
	{
		BltVideoObjectFromIndex( guiSAVEBUFFER, guiBodyInvVO[ pSoldier->ubBodyType ][ bSubImageIndex ], 0, sX, sY, VO_BLT_SRCTRANSPARENCY, NULL );

	}
}

void HandleRenderInvSlots( SOLDIERTYPE *pSoldier, UINT8 fDirtyLevel )
{
	INT32	sX, sY;
	static CHAR16					pStr[ 512 ];
	if ( InItemDescriptionBox( ) || InItemStackPopup( ) || InKeyRingPopup( ) )
	{

	}
	else
	{
		for ( UINT32 cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
		{
			if ( fDirtyLevel == DIRTYLEVEL2 )
			{
#       if defined( _DEBUG ) /* Sergeant_Kolja, to be removed later again */
			if( pSoldier->inv[ cnt ][0]->data.gun.ubGunAmmoType >= MAXITEMS )
        {
         	DebugMsg(TOPIC_JA2, DBG_LEVEL_1, String("pObject (%S) corrupted! GetHelpTextForItem() can crash.", (pSoldier->inv[ cnt ].usItem<MAXITEMS) ? Item[pSoldier->inv[ cnt ].usItem].szItemName : L"???" ));
    	    ScreenMsg( MSG_FONT_RED, MSG_DEBUG, L"pObject (%s) corrupted! GetHelpTextForItem() can crash.",    (pSoldier->inv[ cnt ].usItem<MAXITEMS) ? Item[pSoldier->inv[ cnt ].usItem].szItemName : L"???" );
          DebugBreak();
          AssertMsg( 0, "pObject corrupted! GetHelpTextForItem() can crash." );
        }
#       endif

				GetHelpTextForItem( pStr, &( pSoldier->inv[ cnt ] ), pSoldier );

				SetRegionFastHelpText( &(gSMInvRegion[ cnt ]), pStr );
			}

			INVRenderINVPanelItem( pSoldier, (INT16)cnt, fDirtyLevel );
		}

		if ( KeyExistsInKeyRing( pSoldier, ANYKEY, NULL ) )
		{
			// blit gold key here?
			// CHRISL: adjust settings to use variables for coords
			if ( guiCurrentItemDescriptionScreen != MAP_SCREEN )
			{
				sX=((UsingNewInventorySystem() == false))?496:221;
				sY=((UsingNewInventorySystem() == false))?INV_INTERFACE_START_Y+106:INV_INTERFACE_START_Y+5;
			}
			else
			{
				sX=((UsingNewInventorySystem() == false))?217:188;
				sY=((UsingNewInventorySystem() == false))?271:126;
			}
			BltVideoObjectFromIndex( guiSAVEBUFFER, guiGoldKeyVO, 0, sX, sY, VO_BLT_SRCTRANSPARENCY, NULL );
			RestoreExternBackgroundRect( sX, sY, 29, 23 );
		}
	}	
}

// CHRISL: New function to determine whether to activate Combat and Backpack slots
BOOLEAN CheckActivationStatus(SOLDIERTYPE *pSoldier, INT16 cSlot, INT16 bSlot, INT16 sPocket)
{
	INT8	cLevel, bLevel;

	cLevel = LoadBearingEquipment[Item[pSoldier->inv[cSlot].usItem].ubClassIndex].lbeCombo;
	bLevel = LoadBearingEquipment[Item[pSoldier->inv[bSlot].usItem].ubClassIndex].lbeCombo;
	
	if(sPocket==cSlot)
	{
		if(pSoldier->inv[bSlot].exists() == true)
		{
			if(bLevel == NOTHING)
			{
				return(TRUE);
			}
		}
	}
	if(sPocket==bSlot)
	{
		if(pSoldier->inv[cSlot].exists() == true)
		{
			if(cLevel == NOTHING)
			{
				return(TRUE);
			}
		}
	}
	return(FALSE);
}

void INVRenderINVPanelItem( SOLDIERTYPE *pSoldier, INT16 sPocket, UINT8 fDirtyLevel )
{
	// CHRISL: Only run if we're looking at a legitimate pocket
	if((UsingNewInventorySystem() == false) && !oldInv[sPocket])
		return;
	if((pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE) && UsingNewInventorySystem() == true && !vehicleInv[sPocket])
		return;
	INT16 sX, sY, newX, newY;
	INT16	sBarX, sBarY;
	OBJECTTYPE  *pObject;
	BOOLEAN	fOutline = FALSE;
	INT16		sOutlineColor = 0, lbePocket = ITEM_NOT_FOUND;
	UINT8		fRenderDirtyLevel;
	BOOLEAN fHatchItOut = FALSE;
	UINT32		iClass;


	//Assign the screen
	guiCurrentItemDescriptionScreen = guiCurrentScreen;

	pObject = &(pSoldier->inv[ sPocket ]);

	sX = gSMInvData[ sPocket ].sX;
	sY = gSMInvData[ sPocket ].sY;

	if((UsingNewInventorySystem() == true) && !(pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE))
	{
		// If sPocket is not an equiped pocket, gather pocket information
		if(icClass[sPocket] != ITEM_NOT_FOUND)
		{
			switch (icClass[sPocket])
			{
				case THIGH_PACK:
				case VEST_PACK:
				case COMBAT_PACK:
				case BACKPACK:
					lbePocket = (pSoldier->inv[icLBE[sPocket]].exists() == false) ? LoadBearingEquipment[Item[icDefault[sPocket]].ubClassIndex].lbePocketIndex[icPocket[sPocket]] : LoadBearingEquipment[Item[pSoldier->inv[icLBE[sPocket]].usItem].ubClassIndex].lbePocketIndex[icPocket[sPocket]];
					iClass = Item[pSoldier->inv[sPocket].usItem].usItemClass;
					if(icLBE[sPocket] == BPACKPOCKPOS && !(pSoldier->flags.ZipperFlag) && (gTacticalStatus.uiFlags & INCOMBAT))
						lbePocket = 0;
					if (lbePocket == 0)	// Deactivate Pocket
					{
						fHatchItOut = TRUE;
					}
					else if ( pObject->exists() == false )	// Nothing in sPocket.  Display silouhette.
					{
						INVRenderSilhouette( guiSAVEBUFFER, lbePocket, 0, sX, sY, gSMInvData[ sPocket ].sWidth, gSMInvData[ sPocket ].sHeight);
					}
					break;
				case LBE_POCKET:
					if ( pObject->exists() == false )
					{
						if ( sPocket == VESTPOCKPOS )
							lbePocket = 0;
						else if ( sPocket == LTHIGHPOCKPOS )
							lbePocket = 1;
						else if ( sPocket == RTHIGHPOCKPOS )
							lbePocket = 2;
						else if ( sPocket == CPACKPOCKPOS )
							lbePocket = 3;
						else if ( sPocket == BPACKPOCKPOS )
							lbePocket = 4;
						if ( lbePocket != ITEM_NOT_FOUND )
							INVRenderSilhouette( guiSAVEBUFFER, ITEM_NOT_FOUND, lbePocket, sX, sY, gSMInvData[ sPocket ].sWidth, gSMInvData[ sPocket ].sHeight);
					}
					// Removed backpack/gunsling restrictions
					if ( CheckActivationStatus(pSoldier, CPACKPOCKPOS, BPACKPOCKPOS, sPocket)/* ||
						(sPocket == BPACKPOCKPOS && pSoldier->inv[GUNSLINGPOCKPOS].exists() == true)*/)
					{
						fHatchItOut = TRUE;
					}
					break;
				case OTHER_POCKET:
					if ( pObject->exists() == false )
					{
						if ( sPocket == GUNSLINGPOCKPOS ) // Gun Sling
							lbePocket = 1;
						else
							lbePocket = 2;
						INVRenderSilhouette( guiSAVEBUFFER, lbePocket, 0, sX, sY, gSMInvData[ sPocket ].sWidth, gSMInvData[ sPocket ].sHeight);
					}
					break;
				default:
					if ( pObject->exists() == false )
					{
						// Display appropriate silouhette
					}
					break;
			}
		}
	}

	if ( fDirtyLevel == DIRTYLEVEL2 )
	{
		// CHECK FOR COMPATIBILITY WITH MAGAZINES

/*	OLD VERSION OF GUN/AMMO MATCH HIGHLIGHTING
		UINT32	uiDestPitchBYTES;
		UINT8		*pDestBuf;
		UINT16	usLineColor;

		if ( ( Item [ pSoldier->inv[ HANDPOS ].usItem ].usItemClass & IC_GUN )  && ( Item[ pObject->usItem ].usItemClass & IC_AMMO ) )
		{
			// CHECK
			if (Weapon[pSoldier->inv[ HANDPOS ].usItem].ubCalibre == Magazine[Item[pObject->usItem].ubClassIndex].ubCalibre )
			{
				// IT's an OK calibre ammo, do something!
				// Render Item with specific color
				//fOutline = TRUE;
				//sOutlineColor = Get16BPPColor( FROMRGB( 96, 104, 128 ) );
				//sOutlineColor = Get16BPPColor( FROMRGB( 20, 20, 120 ) );

				// Draw rectangle!
				pDestBuf = LockVideoSurface( guiSAVEBUFFER, &uiDestPitchBYTES );
				SetClippingRegionAndImageWidth( uiDestPitchBYTES, 0, 0, 640, 480 );

				//usLineColor = Get16BPPColor( FROMRGB( 255, 255, 0 ) );
				usLineColor = Get16BPPColor( FROMRGB( 230, 215, 196 ) );
				RectangleDraw( TRUE, (sX+1), (sY+1), (sX + gSMInvData[ sPocket ].sWidth - 2 ),( sY + gSMInvData[ sPocket ].sHeight - 2 ), usLineColor, pDestBuf );

				SetClippingRegionAndImageWidth( uiDestPitchBYTES, 0, 0, 640, 480 );

				UnLockVideoSurface( guiSAVEBUFFER );
			}
		}
*/

		if ( gbCompatibleAmmo[ sPocket ] )
		{
			fOutline = TRUE;
			sOutlineColor = Get16BPPColor( FROMRGB( 255, 255, 255 ) );
		}

		// IF it's the second hand and this hand cannot contain anything, remove the second hand position graphic
//		if (sPocket == SECONDHANDPOS && Item[pSoldier->inv[HANDPOS].usItem].fFlags & ITEM_TWO_HANDED)
		if (sPocket == SECONDHANDPOS && Item[pSoldier->inv[HANDPOS].usItem].twohanded )
		{
			// CHRISL: Change coords for STI that covers 2nd hand location when carrying a 2handed weapon
			if( guiCurrentItemDescriptionScreen != MAP_SCREEN )
			{
				newX = ((UsingNewInventorySystem() == false)) ? 217 : 114;
				newY = ((UsingNewInventorySystem() == false)) ? sY : (sY - 1);
				BltVideoObjectFromIndex( guiSAVEBUFFER, guiSecItemHiddenVO, UsingNewInventorySystem(), newX, newY, VO_BLT_SRCTRANSPARENCY, NULL );
				RestoreExternBackgroundRect( newX, newY, 72, 28 );
			}
			else
			{
				newX = ((UsingNewInventorySystem() == false)) ? 14 : 6;
				newY = ((UsingNewInventorySystem() == false)) ? 218 : 217;
				BltVideoObjectFromIndex( guiSAVEBUFFER, guiMapInvSecondHandBlockout, UsingNewInventorySystem(), newX, newY, VO_BLT_SRCTRANSPARENCY, NULL );
				RestoreExternBackgroundRect( newX, newY, 102, 24 );
			}
		}		
	}

	// If we have a new item and we are in the right panel...
	if ( pSoldier->inv.bNewItemCount[ sPocket ] > 0 && gsCurInterfacePanel == SM_PANEL && fInterfacePanelDirty != DIRTYLEVEL2 )
	{
		fRenderDirtyLevel = DIRTYLEVEL0;
		//fRenderDirtyLevel = fDirtyLevel;
	}
	else
	{
		fRenderDirtyLevel = fDirtyLevel;
	}

	//Now render as normal
	//INVRenderItem( guiSAVEBUFFER, pObject, (INT16)(sX + gSMInvData[ sPocket ].sSubX), (INT16)(sY + gSMInvData[ sPocket ].sSubY), gSMInvData[ sPocket ].sWidth, gSMInvData[ sPocket ].sHeight, fDirtyLevel, &(gfSM_HandInvDispText[ sPocket ] ) );
	INVRenderItem( guiSAVEBUFFER, pSoldier, pObject, sX, sY, gSMInvData[ sPocket ].sWidth, gSMInvData[ sPocket ].sHeight, fRenderDirtyLevel, NULL, 0, fOutline, sOutlineColor );

	// CHRISL: Display pocket capacity if we're holding something in the cursor
	if (!gfSMDisableForItems && (UsingNewInventorySystem() == true) && gpItemPointer != NULL)
	{
		int itemSlotLimit = ItemSlotLimit(gpItemPointer, sPocket, pSoldier);
		RenderPocketItemCapacity( guiSAVEBUFFER, itemSlotLimit, sPocket, pSoldier, &pSoldier->inv[sPocket], sX, sY );
		if(itemSlotLimit == 0 && !CanItemFitInPosition(pSoldier, gpItemPointer, (INT8)sPocket, FALSE)) {
			fHatchItOut = TRUE;
		}
	}

	// CHRISL: Change whether we hatch a pocket to be dependant on the current item
	if(gpItemPointer != NULL)
	{
		if(!gfSMDisableForItems && !CanItemFitInPosition(pSoldier, gpItemPointer, (INT8)sPocket, FALSE)){
			if(!ValidAttachment(gpItemPointer->usItem, pObject->usItem)){
				fHatchItOut = TRUE;
			}
			else{
				fHatchItOut = FALSE;
			}
		}
	}
	else if(pObject->exists() == true)
	{
		if(!gfSMDisableForItems && !CanItemFitInPosition(pSoldier, pObject, (INT8)sPocket, FALSE))
			fHatchItOut = TRUE;
	}
	// CHRISL: Don't hatch second hand position if we're holding a two handed item
	if(sPocket == SECONDHANDPOS)
	{
		if(Item[pSoldier->inv[HANDPOS].usItem].twohanded)
			fHatchItOut = FALSE;
	}
#if 0
	if ( gbInvalidPlacementSlot[ sPocket ] )
	{
		if ( sPocket != SECONDHANDPOS )
		{
			// If we are in inv panel and our guy is not = cursor guy...
			if ( !gfSMDisableForItems )
			{
				fHatchItOut = TRUE;
			}
		}
	}
#endif

	//if we are in the shop keeper interface
	if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
	{
		if( ShouldSoldierDisplayHatchOnItem( pSoldier->ubProfile, sPocket ) && !gbInvalidPlacementSlot[ sPocket ] )
		{
			fHatchItOut = TRUE;
		}
	}

	if ( fHatchItOut )
	{
		UINT32 uiWhichBuffer = ( guiCurrentItemDescriptionScreen == MAP_SCREEN ) ? guiSAVEBUFFER : guiRENDERBUFFER;
		DrawHatchOnInventory( uiWhichBuffer, sX, sY, (UINT16)(gSMInvData[ sPocket ].sWidth-1), (UINT16)(gSMInvData[ sPocket ].sHeight-1) );
	}

	// if there's an item in there
	if ( pObject->exists() == true )
	{
		// Add item status bar
		sBarX = sX - gSMInvData[ sPocket ].sBarDx;
		sBarY = sY + gSMInvData[ sPocket ].sBarDy;
		DrawItemUIBarEx( pObject, 0, sBarX, sBarY, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT,	Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , guiSAVEBUFFER);
	}

}


BOOLEAN CompatibleAmmoForGun( OBJECTTYPE *pTryObject, OBJECTTYPE *pTestObject )
{
	if ( ( Item[ pTryObject->usItem ].usItemClass & IC_AMMO ) )
	{
		// CHECK
		if (Weapon[ pTestObject->usItem ].ubCalibre == Magazine[Item[pTryObject->usItem].ubClassIndex].ubCalibre )
		{
			return( TRUE );
		}
	}
	return( FALSE );
}

BOOLEAN CompatibleGunForAmmo( OBJECTTYPE *pTryObject, OBJECTTYPE *pTestObject )
{
	if ( ( Item[ pTryObject->usItem ].usItemClass & IC_GUN ) )
	{
		// CHECK
		if (Weapon[ pTryObject->usItem ].ubCalibre == Magazine[Item[pTestObject->usItem].ubClassIndex].ubCalibre )
		{
			return( TRUE );
		}
	}
	return( FALSE );
}

BOOLEAN	CompatibleItemForApplyingOnMerc( OBJECTTYPE *pTestObject )
{
	UINT16 usItem = pTestObject->usItem;

  // ATE: If in mapscreen, return false always....
	if( guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
  {
     return( FALSE );
  }

	// ATE: Would be nice to have flag here to check for these types....
	if ( Item[usItem].camouflagekit || usItem == ADRENALINE_BOOSTER || usItem == REGEN_BOOSTER ||
			 usItem == SYRINGE_3		 || usItem == SYRINGE_4 || usItem == SYRINGE_5 ||
			 Item[usItem].alcohol  || Item[usItem].canteen || usItem == JAR_ELIXIR )
	{
		return( TRUE );
	}
	else
	{
		return( FALSE );
	}
}



BOOLEAN SoldierContainsAnyCompatibleStuff( SOLDIERTYPE *pSoldier, OBJECTTYPE *pTestObject )
{
	UINT32				cnt;
	OBJECTTYPE  *pObject;

	if( ( Item [ pTestObject->usItem ].usItemClass & IC_GUN ) )
	{
		for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
		{
			pObject = &(pSoldier->inv[ cnt ]);

			if ( CompatibleAmmoForGun( pObject, pTestObject ) )
			{
				return( TRUE );
			}
		}
	}

	if( ( Item [ pTestObject->usItem ].usItemClass & IC_AMMO ) )
	{
		for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
		{
			pObject = &(pSoldier->inv[ cnt ]);

			if ( CompatibleGunForAmmo( pObject, pTestObject ) )
			{
				return( TRUE );
			}
		}
	}

	// ATE: Put attachment checking here.....

	return( FALSE );
}


void HandleAnyMercInSquadHasCompatibleStuff( UINT8 ubSquad, OBJECTTYPE *pObject, BOOLEAN fReset )
{
	INT32 iCounter = 0;

	if ( ubSquad == NUMBER_OF_SQUADS )
	{
		return;
	}

	for( iCounter = 0; iCounter < NUMBER_OF_SOLDIERS_PER_SQUAD; iCounter++ )
	{
		if(  Squad[ iCurrentTacticalSquad ][ iCounter ] != NULL )
		{
			if ( !fReset )
			{
				if ( SoldierContainsAnyCompatibleStuff( Squad[ iCurrentTacticalSquad ][ iCounter ], pObject )	)
				{
					// Get face and set value....
					gFacesData[ Squad[ iCurrentTacticalSquad ][ iCounter ]->iFaceIndex ].fCompatibleItems = TRUE;
				}
			}
			else
			{
				gFacesData[ Squad[ iCurrentTacticalSquad ][ iCounter ]->iFaceIndex ].fCompatibleItems = FALSE;
			}
		}
	}

}

BOOLEAN HandleCompatibleAmmoUIForMapScreen( SOLDIERTYPE *pSoldier, INT32 bInvPos, BOOLEAN fOn, BOOLEAN fFromMerc   )
{
	BOOLEAN			fFound = FALSE;
	UINT32				cnt;
	OBJECTTYPE  *pObject, *pTestObject ;
	BOOLEAN			fFoundAttachment = FALSE;

	if( fFromMerc == FALSE )
	{
		pTestObject = &( pInventoryPoolList[ bInvPos ].object );
	}
	else
	{
		if ( bInvPos == NO_SLOT )
		{
			pTestObject = NULL;
		}
		else
		{
			pTestObject = &(pSoldier->inv[ bInvPos ]);
		}
	}

	// ATE: If pTest object is NULL, test only for existence of syringes, etc...
	if ( pTestObject == NULL )
	{
		for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
		{
			pObject = &(pSoldier->inv[ cnt ]);

			if ( CompatibleItemForApplyingOnMerc( pObject ) )
			{
				if ( fOn != gbCompatibleAmmo[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				gbCompatibleAmmo[ cnt ] = fOn;

			}
		}


		if ( gpItemPointer != NULL )
		{
			if ( CompatibleItemForApplyingOnMerc( gpItemPointer ) )
			{
				// OK, Light up portrait as well.....
				if ( fOn )
				{
					gbCompatibleApplyItem = TRUE;
				}
				else
				{
					gbCompatibleApplyItem = FALSE;
				}

				fFound = TRUE;
			}
		}

		if ( fFound )
		{
			fInterfacePanelDirty = DIRTYLEVEL2;
			//HandleRenderInvSlots( pSoldier, DIRTYLEVEL2 );
		}

		return( fFound );
	}

//	if ( !(Item[ pTestObject->usItem ].fFlags & ITEM_HIDDEN_ADDON) )
	if ( !(Item[ pTestObject->usItem ].hiddenaddon ) )
	{
		// First test attachments, which almost any type of item can have....
		for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
		{
			pObject = &(pSoldier->inv[ cnt ]);

//			if ( Item[ pObject->usItem ].fFlags & ITEM_HIDDEN_ADDON )
			if ( Item[ pObject->usItem ].hiddenaddon  )
			{
				// don't consider for UI purposes
				continue;
			}

			if ( ValidAttachment( pObject->usItem, pTestObject->usItem ) ||
					 ValidAttachment( pTestObject->usItem, pObject->usItem ) ||
					 ValidLaunchable( pTestObject->usItem, pObject->usItem ) ||
					 ValidLaunchable( pObject->usItem, pTestObject->usItem ) )
			{
				fFoundAttachment = TRUE;

				if ( fOn != gbCompatibleAmmo[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				gbCompatibleAmmo[ cnt ] = fOn;
			}
		}
	}


	if ( ( Item [ pTestObject->usItem ].usItemClass & IC_GUN ) )
	{
		for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
		{
			pObject = &(pSoldier->inv[ cnt ]);

			if ( CompatibleAmmoForGun( pObject, pTestObject ) )
			{
				if ( fOn != gbCompatibleAmmo[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				gbCompatibleAmmo[ cnt ] = fOn;
			}
		}
	}
	else if( ( Item [ pTestObject->usItem ].usItemClass & IC_AMMO ) )
	{
		for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
		{
			pObject = &(pSoldier->inv[ cnt ]);

			if ( CompatibleGunForAmmo( pObject, pTestObject ) )
			{
				if ( fOn != gbCompatibleAmmo[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				gbCompatibleAmmo[ cnt ] = fOn;

			}
		}
	}


	return( fFound );
}

BOOLEAN HandleCompatibleAmmoUIForMapInventory( SOLDIERTYPE *pSoldier, INT32 bInvPos, INT32 iStartSlotNumber, BOOLEAN fOn, BOOLEAN fFromMerc   )
{
	// CJC: ATE, needs fixing here!

	BOOLEAN			fFound = FALSE;
	INT32				cnt;
	OBJECTTYPE  *pObject, *pTestObject ;
	BOOLEAN			fFoundAttachment = FALSE;

	if( fFromMerc == FALSE )
	{
		pTestObject = &( pInventoryPoolList[ iStartSlotNumber + bInvPos ].object);
	}
	else
	{
		if ( bInvPos == NO_SLOT )
		{
			pTestObject = NULL;
		}
		else
		{
			pTestObject = &(pSoldier->inv[ bInvPos ]);
		}
	}

	// First test attachments, which almost any type of item can have....
	for ( cnt = 0; cnt < MAP_INVENTORY_POOL_SLOT_COUNT; cnt++ )
	{
		pObject = &( pInventoryPoolList[ iStartSlotNumber + cnt ].object );

//		if ( Item[ pObject->usItem ].fFlags & ITEM_HIDDEN_ADDON )
		if ( Item[ pObject->usItem ].hiddenaddon  )
		{
			// don't consider for UI purposes
			continue;
		}

		if ( ValidAttachment( pObject->usItem, pTestObject->usItem ) ||
				 ValidAttachment( pTestObject->usItem, pObject->usItem ) ||
				 ValidLaunchable( pTestObject->usItem, pObject->usItem ) ||
				 ValidLaunchable( pObject->usItem, pTestObject->usItem ) )
		{
			fFoundAttachment = TRUE;

			if ( fOn != fMapInventoryItemCompatable[ cnt ] )
			{
				fFound = TRUE;
			}

			// IT's an OK calibere ammo, do something!
			// Render Item with specific color
			fMapInventoryItemCompatable[ cnt ] = fOn;
		}
	}


	if( ( Item [ pTestObject->usItem ].usItemClass & IC_GUN ) )
	{
		for ( cnt = 0; cnt < MAP_INVENTORY_POOL_SLOT_COUNT; cnt++ )
		{
			pObject = &( pInventoryPoolList[ iStartSlotNumber + cnt ].object );

			if ( CompatibleAmmoForGun( pObject, pTestObject ) )
			{
				if ( fOn != fMapInventoryItemCompatable[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				fMapInventoryItemCompatable[ cnt ] = fOn;
			}
		}
	}
	else if( ( Item [ pTestObject->usItem ].usItemClass & IC_AMMO ) )
	{
		for ( cnt = 0; cnt < MAP_INVENTORY_POOL_SLOT_COUNT; cnt++ )
		{
			pObject = &( pInventoryPoolList[ iStartSlotNumber + cnt ].object );

			if ( CompatibleGunForAmmo( pObject, pTestObject ) )
			{
				if ( fOn != fMapInventoryItemCompatable[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				fMapInventoryItemCompatable[ cnt ] = fOn;

			}
		}
	}


	return( fFound );
}


BOOLEAN InternalHandleCompatibleAmmoUI( SOLDIERTYPE *pSoldier, OBJECTTYPE *pTestObject, BOOLEAN fOn  )
{
	BOOLEAN			fFound = FALSE;
	UINT32				cnt;
	OBJECTTYPE  *pObject;
	BOOLEAN			fFoundAttachment = FALSE;

	// ATE: If pTest object is NULL, test only for existence of syringes, etc...
	if ( pTestObject == NULL )
	{
		for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
		{
			pObject = &(pSoldier->inv[ cnt ]);

			if ( CompatibleItemForApplyingOnMerc( pObject ) )
			{
				if ( fOn != gbCompatibleAmmo[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				gbCompatibleAmmo[ cnt ] = fOn;

			}
		}


		if ( gpItemPointer != NULL )
		{
			if ( CompatibleItemForApplyingOnMerc( gpItemPointer ) )
			{
				// OK, Light up portrait as well.....
				if ( fOn )
				{
					gbCompatibleApplyItem = TRUE;
				}
				else
				{
					gbCompatibleApplyItem = FALSE;
				}

				fFound = TRUE;
			}
		}

		if ( fFound )
		{
			fInterfacePanelDirty = DIRTYLEVEL2;
			//HandleRenderInvSlots( pSoldier, DIRTYLEVEL2 );
		}

		return( fFound );
	}

	// First test attachments, which almost any type of item can have....
	for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
	{
		pObject = &(pSoldier->inv[ cnt ]);

//		if ( Item[ pObject->usItem ].fFlags & ITEM_HIDDEN_ADDON )
		if ( Item[ pObject->usItem ].hiddenaddon  )
		{
			// don't consider for UI purposes
			continue;
		}

		if ( ValidAttachment( pObject->usItem, pTestObject->usItem ) ||
				 ValidAttachment( pTestObject->usItem, pObject->usItem ) ||
				 ValidLaunchable( pTestObject->usItem, pObject->usItem ) ||
				 ValidLaunchable( pObject->usItem, pTestObject->usItem ) )
		{
			fFoundAttachment = TRUE;

			if ( fOn != gbCompatibleAmmo[ cnt ] )
			{
				fFound = TRUE;
			}

			// IT's an OK calibere ammo, do something!
			// Render Item with specific color
			gbCompatibleAmmo[ cnt ] = fOn;
		}
	}

	//if ( !fFoundAttachment )
	//{
		if( ( Item [ pTestObject->usItem ].usItemClass & IC_GUN ) )
		{
			for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
			{
				pObject = &(pSoldier->inv[ cnt ]);

				if ( CompatibleAmmoForGun( pObject, pTestObject ) )
				{
					if ( fOn != gbCompatibleAmmo[ cnt ] )
					{
						fFound = TRUE;
					}

					// IT's an OK calibere ammo, do something!
					// Render Item with specific color
					gbCompatibleAmmo[ cnt ] = fOn;
				}
			}
		}

		else if( ( Item [ pTestObject->usItem ].usItemClass & IC_AMMO ) )
		{
			for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
			{
				pObject = &(pSoldier->inv[ cnt ]);

				if ( CompatibleGunForAmmo( pObject, pTestObject ) )
				{
					if ( fOn != gbCompatibleAmmo[ cnt ] )
					{
						fFound = TRUE;
					}

					// IT's an OK calibere ammo, do something!
					// Render Item with specific color
					gbCompatibleAmmo[ cnt ] = fOn;

				}
			}
		}
		else if ( CompatibleItemForApplyingOnMerc( pTestObject ) )
		{
			//If we are currently NOT in the Shopkeeper interface
			if( !( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE ) )
			{
				fFound = TRUE;
				gbCompatibleApplyItem = fOn;
			}
		}
	//}


	if ( !fFound )
	{
		for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
		{
			if ( gbCompatibleAmmo[ cnt ] )
			{
				fFound = TRUE;
				gbCompatibleAmmo[ cnt ] = FALSE;
			}

			if ( gbCompatibleApplyItem )
			{
				fFound = TRUE;
				gbCompatibleApplyItem = FALSE;
			}
		}
	}

	if ( fFound )
	{
		fInterfacePanelDirty = DIRTYLEVEL2;
		//HandleRenderInvSlots( pSoldier, DIRTYLEVEL2 );
	}

	return( fFound );

}

void ResetCompatibleItemArray( )
{
	INT32 cnt = 0;

	for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
	{
		if ( gbCompatibleAmmo[ cnt ] )
		{
			gbCompatibleAmmo[ cnt ] = FALSE;
		}
	}
}

BOOLEAN HandleCompatibleAmmoUI( SOLDIERTYPE *pSoldier, INT8 bInvPos, BOOLEAN fOn )
{
	INT32 cnt;
	OBJECTTYPE  *pTestObject;
	BOOLEAN			fFound = FALSE;

	//if we are in the shopkeeper interface
	if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
	{
		// if the inventory position is -1, this is a flag from the Shopkeeper interface screen
		//indicating that we are to use a different object to do the search
		if( bInvPos == -1 )
		{
			if( fOn )
			{
				if( gpHighLightedItemObject )
				{
					pTestObject = gpHighLightedItemObject;
//					gubSkiDirtyLevel = SKI_DIRTY_LEVEL2;
				}
				else
					return( FALSE );
			}
			else
			{
				gpHighLightedItemObject = NULL;

				for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
				{
					if ( gbCompatibleAmmo[ cnt ] )
					{
						fFound = TRUE;
						gbCompatibleAmmo[ cnt ] = FALSE;
					}
				}

				gubSkiDirtyLevel = SKI_DIRTY_LEVEL1;
				return( TRUE );
			}
		}
		else
		{
			if( fOn )
			{
				pTestObject = &(pSoldier->inv[ bInvPos ]);
				gpHighLightedItemObject = pTestObject;
			}
			else
			{
				pTestObject = &(pSoldier->inv[ bInvPos ]);
				gpHighLightedItemObject = NULL;
				gubSkiDirtyLevel = SKI_DIRTY_LEVEL1;
			}
		}
	}
	else
	{
//		if( fOn )

		if ( bInvPos == NO_SLOT )
		{
			pTestObject = NULL;
		}
		else
		{
			pTestObject = &(pSoldier->inv[ bInvPos ]);
		}

	}

	return( InternalHandleCompatibleAmmoUI( pSoldier, pTestObject, fOn ) );

}

void GetSlotInvXY( UINT8 ubPos, INT16 *psX, INT16 *psY )
{
	*psX = gSMInvData[ ubPos ].sX;
	*psY = gSMInvData[ ubPos ].sY;
}

void GetSlotInvHeightWidth( UINT8 ubPos, INT16 *psWidth, INT16 *psHeight )
{
	*psWidth	= gSMInvData[ ubPos ].sWidth;
	*psHeight   = gSMInvData[ ubPos ].sHeight;
}

void HandleNewlyAddedItems( SOLDIERTYPE *pSoldier, BOOLEAN *fDirtyLevel )
{
	// If item description up.... stop
	if ( gfInItemDescBox )
	{
		return;
	}

	UINT32 cnt;
	INT16  sX, sY;
	OBJECTTYPE		*pObject;

	for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
	{
		if ( pSoldier->inv.bNewItemCount[ cnt ] == -2 )
		{
			// Stop
			*fDirtyLevel = DIRTYLEVEL2;
			pSoldier->inv.bNewItemCount[ cnt ] = 0;
		}

		if ( pSoldier->inv.bNewItemCount[ cnt ] > 0 )
		{

			sX = gSMInvData[ cnt ].sX;
			sY = gSMInvData[ cnt ].sY;

			pObject = &(pSoldier->inv[ cnt ]);

			if ( pObject->exists() == false )
			{
				gbNewItem[ cnt ] = 0;
				continue;
			}

			INVRenderItem( guiSAVEBUFFER, pSoldier, pObject, sX, sY, gSMInvData[ cnt ].sWidth, gSMInvData[ cnt ].sHeight, DIRTYLEVEL2, NULL, 0, TRUE, us16BPPItemCyclePlacedItemColors[ pSoldier->inv.bNewItemCycleCount[ cnt ] ] );

		}

	}
}

void CheckForAnyNewlyAddedItems( SOLDIERTYPE *pSoldier )
{
	// OK, l0ok for any new...
	for ( UINT32 cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
	{
		if ( pSoldier->inv.bNewItemCount[ cnt ] == -1 )
		{
			pSoldier->inv.bNewItemCount[ cnt ]	= NEW_ITEM_CYCLES - 1;
		}
	}

}

void DegradeNewlyAddedItems( )
{
	UINT32 uiTime;
	UINT32 cnt, cnt2;
	SOLDIERTYPE		*pSoldier;

	// If time done
	uiTime = GetJA2Clock();

	if ( ( uiTime - guiNewlyPlacedItemTimer ) > 100 )
	{
		guiNewlyPlacedItemTimer = uiTime;

		for ( cnt2 = 0; cnt2 < NUM_TEAM_SLOTS; cnt2++ )
		{
			// GET SOLDIER
			if ( gTeamPanel[ cnt2 ].fOccupied )
			{
				pSoldier = MercPtrs[ gTeamPanel[ cnt2 ].ubID ];

				for ( cnt = 0; cnt < pSoldier->inv.size(); cnt++ )
				{
					if ( pSoldier->inv.bNewItemCount[ cnt ] > 0 )
					{
						// Decrement all the time!
						pSoldier->inv.bNewItemCycleCount[ cnt ]--;

						if ( pSoldier->inv.bNewItemCycleCount[ cnt ] == 0 )
						{
							// OK, cycle down....
							pSoldier->inv.bNewItemCount[ cnt ]--;

							if ( pSoldier->inv.bNewItemCount[ cnt ] == 0 )
							{
								// Stop...
								pSoldier->inv.bNewItemCount[ cnt ] = -2;
							}
							else
							{
								// Reset!
								pSoldier->inv.bNewItemCycleCount[ cnt ]	= NEW_ITEM_CYCLE_COUNT;
								continue;
							}
						}
					}
				}
			}
		}
	}
}


void InitItemInterface( )
{
	UINT32 cnt, cnt2;

	for ( cnt = 0, cnt2 = 0; cnt2 < 20; cnt+=3, cnt2++ )
	{
		us16BPPItemCyclePlacedItemColors[ cnt2 ] = Get16BPPColor( FROMRGB( ubRGBItemCyclePlacedItemColors[ cnt ], ubRGBItemCyclePlacedItemColors[ cnt + 1 ], ubRGBItemCyclePlacedItemColors[ cnt + 2] ) );
	}

}

// CHRISL: Function to display pocket inventory quantity based on object in cursor
void RenderPocketItemCapacity( UINT32 uiWhichBuffer, UINT8 pCapacity, INT16 bPos, SOLDIERTYPE *pSoldier, OBJECTTYPE *pObj, INT16 sX, INT16 sY )
{
	static CHAR16		pStr[ 100 ];

	// Can pocket hold the item in the cursor?
	if(InItemDescriptionBox( ))
		return;
	if(pSoldier != NULL && !CanItemFitInPosition( pSoldier, gpItemPointer, (INT8)bPos, FALSE ))
	{
		// Further check to see if the cursor item is valid ammo or a valid attachment
		if(!CompatibleAmmoForGun(gpItemPointer, &pSoldier->inv[bPos]) && !ValidAttachment(gpItemPointer->usItem, pSoldier->inv[bPos].usItem))
		{
			return;
		}
	}

	// Setup display parameters
	SetFont( ITEM_FONT );
	SetFontBackground( FONT_MCOLOR_BLACK );
	SetFontForeground( FONT_RED );
	if(pSoldier == NULL || (pCapacity != 0 && CanItemFitInPosition(pSoldier, gpItemPointer, (INT8)bPos, FALSE)))
	{
		// Adjust capacity to account for current items
		if(gpItemPointer->usItem == pObj->usItem)
		{
			SetFontForeground( FONT_GREEN );
			pCapacity = pCapacity - pObj->ubNumberOfObjects;
			if(pCapacity > 0)
				swprintf( pStr, L"+%d", pCapacity );
			else
				swprintf( pStr, L"-" );
		}
		else
			swprintf( pStr, L"%d", pCapacity );
	}
	else if(CompatibleAmmoForGun(gpItemPointer, &pSoldier->inv[bPos]) || ValidLaunchable(gpItemPointer->usItem, pSoldier->inv[bPos].usItem))
	{
		SetFontForeground( FONT_YELLOW );
		swprintf( pStr, L"L" );
	}
	else if(ValidAttachment(gpItemPointer->usItem, pSoldier->inv[bPos].usItem))
	{
		SetFontForeground( FONT_YELLOW );
		swprintf( pStr, L"A" );
	}
	sX = sX + 1;

	// Display pocket capacity
	if ( uiWhichBuffer == guiSAVEBUFFER )
	{
		RestoreExternBackgroundRect( sX, sY, 15, 15 );
	}
	mprintf( sX, sY, pStr );
	gprintfinvalidate( sX, sY, pStr );
	return;
}
// CHRISL: New function to render silhouettes
void INVRenderSilhouette( UINT32 uiBuffer, INT16 PocketIndex, INT16 SilIndex, INT16 sX, INT16 sY, INT16 sWidth, INT16 sHeight)
{
	ETRLEObject						*pTrav;
	HVOBJECT						hVObject;
	UINT32							usHeight, usWidth;
	INT16							sCenX, sCenY;
	
	if(gfSMDisableForItems)
		return;
	SetFont( ITEM_FONT );
	GetVideoObject( &hVObject, guiSILHOUETTE );
	if ( PocketIndex != ITEM_NOT_FOUND )
		SilIndex = LBEPocketType[PocketIndex].pSilhouette;

	pTrav = &(hVObject->pETRLEObject[ SilIndex ] );

	usHeight				= (UINT32)pTrav->usHeight;
	usWidth					= (UINT32)pTrav->usWidth;

	// CENTER IN SLOT!
	// CANCEL OFFSETS!
	sCenX =  sX + (INT16)( abs( sWidth - (double)usWidth ) / 2 ) - pTrav->sOffsetX;
	sCenY =  sY + (INT16)( abs( sHeight - (double)usHeight ) / 2 ) - pTrav->sOffsetY;

	BltVideoObjectOutlineFromIndex( uiBuffer, guiSILHOUETTE, SilIndex, sCenX, sCenY, 0 /*sOutlineColor*/, FALSE );

	if ( uiBuffer == FRAME_BUFFER )
	{
		InvalidateRegion( sX, sY, (INT16)(sX + sWidth), (INT16)(sY + sHeight ) );
	}
	else
	{
		RestoreExternBackgroundRect( sX, sY, sWidth, sHeight );
	}
}


void INVRenderItem( UINT32 uiBuffer, SOLDIERTYPE * pSoldier, OBJECTTYPE  *pObject, INT16 sX, INT16 sY, INT16 sWidth, INT16 sHeight, UINT8 fDirtyLevel, UINT8 *pubHighlightCounter, UINT8 ubStatusIndex, BOOLEAN fOutline, INT16 sOutlineColor, UINT8 iter )
{
	UINT16								uiStringLength;
	INVTYPE								*pItem;
  ETRLEObject						*pTrav;
	UINT32								usHeight, usWidth;
	INT16									sCenX, sCenY, sNewY, sNewX;
	HVOBJECT							hVObject;
	BOOLEAN								fLineSplit = FALSE;
	INT16									sFontX2 = 0, sFontY2 = 0;
	INT16									sFontX = 0, sFontY = 0;

	static CHAR16					pStr[ 100 ], pStr2[ 100 ];

	if ( pObject->exists() == false )
	{
		return;
	}

	if ( ubStatusIndex < RENDER_ITEM_ATTACHMENT1 )
	{
		pItem = &Item[ pObject->usItem ];
	}
	else
	{
		pItem = &Item[ (*pObject)[iter]->GetAttachmentAtIndex( ubStatusIndex - RENDER_ITEM_ATTACHMENT1 )->usItem ];
	}

	if ( fDirtyLevel == DIRTYLEVEL2 )
	{
		// TAKE A LOOK AT THE VIDEO OBJECT SIZE ( ONE OF TWO SIZES ) AND CENTER!
		GetVideoObject( &hVObject, GetInterfaceGraphicForItem( pItem ) );
		pTrav = &(hVObject->pETRLEObject[ pItem->ubGraphicNum ] );
		usHeight				= (UINT32)pTrav->usHeight;
		usWidth					= (UINT32)pTrav->usWidth;



		// CENTER IN SLOT!
		// CANCEL OFFSETS!
		sCenX =  sX + (INT16)( abs( sWidth - (double)usWidth ) / 2 ) - pTrav->sOffsetX;
		sCenY =  sY + (INT16)( abs( sHeight - (double)usHeight ) / 2 ) - pTrav->sOffsetY;

		// Shadow area
		if(gGameSettings.fOptions[ TOPTION_SHOW_ITEM_SHADOW ]) BltVideoObjectOutlineShadowFromIndex( uiBuffer, GetInterfaceGraphicForItem( pItem ), pItem->ubGraphicNum, sCenX - 2, sCenY + 2 );

		BltVideoObjectOutlineFromIndex( uiBuffer, GetInterfaceGraphicForItem( pItem ), pItem->ubGraphicNum, sCenX, sCenY, sOutlineColor, fOutline );


		if ( uiBuffer == FRAME_BUFFER )
		{
			InvalidateRegion( sX, sY, (INT16)(sX + sWidth), (INT16)(sY + sHeight ) );
		}
		else
		{
			RestoreExternBackgroundRect( sX, sY, sWidth, sHeight );
		}

	}

	SetFont( ITEM_FONT );

	if ( fDirtyLevel != DIRTYLEVEL0 )
	{

		if ( ubStatusIndex < RENDER_ITEM_ATTACHMENT1 )
		{

			SetFontBackground( FONT_MCOLOR_BLACK );
			SetFontForeground( FONT_MCOLOR_DKGRAY );
#if 1
			//CHRISL: Moved this condition to the start so that stacked guns will show number in stack
			if ( ubStatusIndex != RENDER_ITEM_NOSTATUS )
			{
				// Now display # of items
				if ( pObject->ubNumberOfObjects > 1 )
				{
					SetFontForeground( FONT_GRAY4 );

					sNewY = sY + sHeight - 10;
					swprintf( pStr, L"%d", pObject->ubNumberOfObjects );

					// Get length of string
					uiStringLength=StringPixLength(pStr, ITEM_FONT );

					sNewX = sX + sWidth - uiStringLength - 4;

					if ( uiBuffer == guiSAVEBUFFER )
					{
						RestoreExternBackgroundRect( sNewX, sNewY, 15, 15 );
					}
					mprintf( sNewX, sNewY, pStr );
					gprintfinvalidate( sNewX, sNewY, pStr );
				}

			}
#endif
			// FIRST DISPLAY FREE ROUNDS REMIANING
			if ( pItem->usItemClass == IC_GUN && !Item[pObject->usItem].rocketlauncher )
			{
				sNewY = sY + sHeight - 10;
				sNewX = sX + 1;

				SetFontForeground ( AmmoTypes[(*pObject)[iter]->data.gun.ubGunAmmoType].fontColour );
				//switch ((*pObject)[iter]->data.gun.ubGunAmmoType)
				//{
				//	case AMMO_AP:
				//	case AMMO_SUPER_AP:
				//		SetFontForeground( ITEMDESC_FONTAPFORE );
				//		break;
				//	case AMMO_HP:
				//		SetFontForeground( ITEMDESC_FONTHPFORE );
				//		break;
				//	case AMMO_BUCKSHOT:
				//		SetFontForeground( ITEMDESC_FONTBSFORE );
				//		break;
				//	case AMMO_HE:
				//	case AMMO_GRENADE:
				//		SetFontForeground( ITEMDESC_FONTHEFORE );
				//		break;
				//	case AMMO_HEAT:
				//		SetFontForeground( ITEMDESC_FONTHEAPFORE );
				//		break;
				//	default:
				//		SetFontForeground( FONT_MCOLOR_DKGRAY );
				//		break;
				//}

				swprintf( pStr, L"%d", (*pObject)[iter]->data.gun.ubGunShotsLeft );
				if ( uiBuffer == guiSAVEBUFFER )
				{
					RestoreExternBackgroundRect( sNewX, sNewY, 20, 15 );
				}
				mprintf( sNewX, sNewY, pStr );
				gprintfinvalidate( sNewX, sNewY, pStr );

				SetFontForeground( FONT_MCOLOR_DKGRAY );

				// Display 'JAMMED' if we are jammed
				if ( (*pObject)[iter]->data.gun.bGunAmmoStatus < 0 )
				{
					SetFontForeground( FONT_MCOLOR_RED );

					if ( sWidth >= ( BIG_INV_SLOT_WIDTH - 10 )  )
					{
						swprintf( pStr, TacticalStr[ JAMMED_ITEM_STR ] );
					}
					else
					{
						swprintf( pStr, TacticalStr[ SHORT_JAMMED_GUN ] );
					}

					VarFindFontCenterCoordinates( sX, sY, sWidth, sHeight , ITEM_FONT, &sNewX, &sNewY, pStr );

					mprintf( sNewX, sNewY, pStr );
					gprintfinvalidate( sNewX, sNewY, pStr );
				}
			}
#if 0
			else
			{
				if ( ubStatusIndex != RENDER_ITEM_NOSTATUS )
				{
					// Now display # of items
					if ( pObject->ubNumberOfObjects > 1 )
					{
						SetFontForeground( FONT_GRAY4 );

						sNewY = sY + sHeight - 10;
						swprintf( pStr, L"%d", pObject->ubNumberOfObjects );

						// Get length of string
						uiStringLength=StringPixLength(pStr, ITEM_FONT );

						sNewX = sX + sWidth - uiStringLength - 4;

						if ( uiBuffer == guiSAVEBUFFER )
						{
							RestoreExternBackgroundRect( sNewX, sNewY, 15, 15 );
						}
						mprintf( sNewX, sNewY, pStr );
						gprintfinvalidate( sNewX, sNewY, pStr );
					}

				}
			}
#endif
			if ( ItemHasAttachments( pObject, pSoldier, iter ) )
			{
				if ( !IsGrenadeLauncherAttached( pObject ) )
				{
					SetFontForeground( FONT_GREEN );
				}
				else
				{
					SetFontForeground( FONT_YELLOW );
				}

				sNewY = sY;
				swprintf( pStr, L"*" );

				// Get length of string
				uiStringLength=StringPixLength(pStr, ITEM_FONT );

				sNewX = sX + sWidth - uiStringLength - 4;

				if ( uiBuffer == guiSAVEBUFFER )
				{
					RestoreExternBackgroundRect( sNewX, sNewY, 15, 15 );
				}
				mprintf( sNewX, sNewY, pStr );
				gprintfinvalidate( sNewX, sNewY, pStr );

			}

			if((UsingNewInventorySystem() == true))
			{
				// CHRISL: Display astrisk when LBENODE active
				if ( pObject->HasAnyActiveLBEs(pSoldier, iter) )
				{
					SetFontForeground( FONT_BLUE );

					sNewY = sY;
					swprintf( pStr, L"*" );

					// Get length of string
					uiStringLength=StringPixLength(pStr, ITEM_FONT );

					sNewX = sX + sWidth - uiStringLength - 4;

					if ( uiBuffer == guiSAVEBUFFER )
					{
						RestoreExternBackgroundRect( sNewX, sNewY, 15, 15 );
					}
					mprintf( sNewX, sNewY, pStr );
					gprintfinvalidate( sNewX, sNewY, pStr );

				}
			}

			if ( pSoldier && pObject == &(pSoldier->inv[HANDPOS] ) && pSoldier->bWeaponMode != WM_NORMAL && Item[pSoldier->inv[HANDPOS].usItem].usItemClass == IC_GUN )
			{
				sNewY = sY + 13; // rather arbitrary
				if ( pSoldier->bWeaponMode == WM_BURST )
				{
					swprintf( pStr, New113Message[MSG113_BRST] );
					SetFontForeground( FONT_RED );
				}
				else if(pSoldier->bWeaponMode == WM_AUTOFIRE)
				{
					swprintf( pStr, New113Message[MSG113_AUTO] );
					SetFontForeground( FONT_RED );
				}
				else if(pSoldier->bWeaponMode == WM_ATTACHED_GL)
				{
					swprintf( pStr, New113Message[MSG113_GL] );
					SetFontForeground( FONT_YELLOW );
				}
				else if(pSoldier->bWeaponMode == WM_ATTACHED_GL_BURST)
				{
					swprintf( pStr, New113Message[MSG113_GL_BRST] );
					SetFontForeground( FONT_YELLOW );
				}
				else if(pSoldier->bWeaponMode == WM_ATTACHED_GL_AUTO)
				{
					swprintf( pStr, New113Message[MSG113_GL_AUTO] );
					SetFontForeground( FONT_YELLOW );
				}

				// Get length of string
				uiStringLength=StringPixLength(pStr, ITEM_FONT );

				sNewX = sX + sWidth - uiStringLength - 4;

				if ( uiBuffer == guiSAVEBUFFER )
				{
					RestoreExternBackgroundRect( sNewX, sNewY, 15, 15 );
				}
				mprintf( sNewX, sNewY, pStr );
				gprintfinvalidate( sNewX, sNewY, pStr );

			}
		}
	}

	if ( pubHighlightCounter != NULL )
	{
		SetFontBackground( FONT_MCOLOR_BLACK );
		SetFontForeground( FONT_MCOLOR_LTGRAY );

		// DO HIGHLIGHT
		if ( *pubHighlightCounter )
		{
			// Set string
			if ( ubStatusIndex < RENDER_ITEM_ATTACHMENT1 )
			{
				swprintf( pStr, L"%s", ShortItemNames[ pObject->usItem ] );
			}
			else
			{
				OBJECTTYPE* pAttachment = (*pObject)[iter]->GetAttachmentAtIndex(ubStatusIndex - RENDER_ITEM_ATTACHMENT1);
				if (pAttachment) {
					swprintf( pStr, L"%s", ShortItemNames[ pAttachment->usItem ] );
				}
			}

			fLineSplit = WrapString( pStr, pStr2, WORD_WRAP_INV_WIDTH, ITEM_FONT );

			VarFindFontCenterCoordinates( sX, sY, sWidth, sHeight , ITEM_FONT, &sFontX, &sFontY, pStr );
			sFontY = sY + 1;
			gprintfinvalidate( sFontX, sFontY, pStr );

			if ( fLineSplit )
			{
				VarFindFontCenterCoordinates( sX, sY, sWidth, sHeight , ITEM_FONT, &sFontX2, &sFontY2, pStr2 );
				sFontY2 = sY + 13;
				gprintfinvalidate( sFontX2, sFontY2, pStr2 );
			}

		}

		if ( *pubHighlightCounter == 2 )
		{
			mprintf( sFontX, sFontY, pStr );

			if ( fLineSplit )
			{
				mprintf( sFontX2, sFontY2, pStr2 );
			}
		}
		else if ( *pubHighlightCounter == 1 )
		{
			*pubHighlightCounter = 0;
			gprintfRestore( sFontX, sFontY, pStr );

			if ( fLineSplit )
			{
				gprintfRestore( sFontX2, sFontY2, pStr2 );
			}
		}
	}
}


BOOLEAN InItemDescriptionBox( )
{
	return( gfInItemDescBox );
}

void CycleItemDescriptionItem( INT16 sX, INT16 sY )
{
	INT16 usOldItem;

	// Delete old box...
	DeleteItemDescriptionBox( );

	// Make new item....
	usOldItem = gpItemDescSoldier->inv[ HANDPOS ].usItem;

	if ( _KeyDown( SHIFT ) )
	{
		usOldItem--;

		if ( usOldItem < 1 )
		{
			usOldItem = MAXITEMS-1;
		}

		while ( usOldItem > 0 && ( Item[usOldItem].usItemClass == IC_NONE || Item[usOldItem].usItemClass == 0 ))
		{
			usOldItem--;
			if(usOldItem < 1)
				usOldItem = MAXITEMS-1;
		}
	}
	else
	{
		usOldItem++;

		if ( usOldItem > MAXITEMS )
		{
			usOldItem = 0;
		}

		while (usOldItem < MAXITEMS && (Item[usOldItem].usItemClass == IC_NONE || Item[usOldItem].usItemClass == 0 ))
		{
			usOldItem++;
			if(usOldItem >= MAXITEMS)
				usOldItem = 1;
		}
	}

	CreateItem( (UINT16)usOldItem, 100, &( gpItemDescSoldier->inv[ HANDPOS ] ) );

	InternalInitItemDescriptionBox( &( gpItemDescSoldier->inv[ HANDPOS ] ), sX, sY, gubItemDescStatusIndex, gpItemDescSoldier );
}

BOOLEAN InitItemDescriptionBox( SOLDIERTYPE *pSoldier, UINT8 ubPosition, INT16 sX, INT16 sY, UINT8 ubStatusIndex )
{
	OBJECTTYPE *pObject;

//DEF:
	//if we are in the shopkeeper screen, and we are to use the
	if( guiCurrentScreen == SHOPKEEPER_SCREEN && ubPosition == 255 )
	{
		pObject = pShopKeeperItemDescObject;
	}

	//else use item from the hand position
	else
	{
		pObject = &(pSoldier->inv[ ubPosition ] );
	}

	return( InternalInitItemDescriptionBox( pObject, sX, sY, ubStatusIndex, pSoldier, ubPosition ) );
}

BOOLEAN InitKeyItemDescriptionBox( SOLDIERTYPE *pSoldier, UINT8 ubPosition, INT16 sX, INT16 sY, UINT8 ubStatusIndex )
{
	OBJECTTYPE *pObject;

	AllocateObject( &pObject );
	CreateKeyObject( pObject, pSoldier->pKeyRing[ ubPosition ].ubNumber ,pSoldier->pKeyRing[ ubPosition ].ubKeyID );

	return( InternalInitItemDescriptionBox( pObject, sX, sY, ubStatusIndex, pSoldier ) );
}

BOOLEAN InternalInitItemDescriptionBox( OBJECTTYPE *pObject, INT16 sX, INT16 sY, UINT8 ubStatusIndex, SOLDIERTYPE *pSoldier, UINT8 ubPosition )
{
	VOBJECT_DESC    VObjectDesc;
	CHAR8 ubString[48];
	INT32		cnt;
	CHAR16		pStr[10];
	INT16	usX, usY;
	INT16		sForeColour;
	INT16 sProsConsIndent;

	// CHRISL: Set some initial coords
	ITEMDESC_START_X	= ((UsingNewInventorySystem() == true && iResolution != 0)) ? 259 : 214;	//115:214
	ITEMDESC_START_Y	= ((UsingNewInventorySystem() == true && iResolution != 0)) ? (1 + INV_INTERFACE_START_Y) : (1 + INV_INTERFACE_START_Y);
	ITEMDESC_HEIGHT		= ((UsingNewInventorySystem() == true && iResolution != 0)) ? 195 : 133;	//195:133
	ITEMDESC_WIDTH = 320;
	if(UsingNewInventorySystem() == true)
	{
		if(iResolution == 0)
			ITEMDESC_WIDTH = 526;
		else if(iResolution == 1)
			ITEMDESC_WIDTH = 686;
		else if(iResolution == 2)
			ITEMDESC_WIDTH = 910;
	}
	//ITEMDESC_WIDTH		= ((UsingNewInventorySystem() == true && iResolution != 0)) ? 320 : 320;	//678:320
	MAP_ITEMDESC_HEIGHT	= ((UsingNewInventorySystem() == true && iResolution != 0)) ? 490 : 268;
	MAP_ITEMDESC_WIDTH	= ((UsingNewInventorySystem() == true && iResolution != 0)) ? 272 : 272;

	//CHRISL: We only want this condition to be true when looking at MONEY.  Not IC_MONEY since we can't actually split
	//	things like gold nuggets or wallets.
	// ADB: Make sure the current object isn't money if there's something in hand
	//if (Item[ pObject->usItem].usItemClass & IC_MONEY && gpItemPointer != NULL && gpItemPointer->usItem != 0) {
	if(pObject->usItem == MONEY && gpItemPointer != NULL && gpItemPointer->usItem != 0 && gpItemPointer->usItem != MONEY) {
		//ADB oops, money splits and puts a new item on the cursor, which would replace what's already on the cursor!
//		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Unable to split money due to having an item on your cursor." );
		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, New113Message[MSG113_UNABLETOSPLITMONEY] );
		return FALSE;
	}


	//Set the current screen
	guiCurrentItemDescriptionScreen = guiCurrentScreen;

	// Set X, Y
	if(sX == 0 && sY == 0)
	{
		gsInvDescX = ITEMDESC_START_X;	//sX;
		gsInvDescY = ITEMDESC_START_Y;	//sY;
	}
	else
	{
		gsInvDescX = sX;
		gsInvDescY = sY;
	}

	gpItemDescObject = pObject;
	gubItemDescStatusIndex = ubStatusIndex;
	gpItemDescSoldier = pSoldier;
	fItemDescDelete		= FALSE;

	// Build a mouse region here that is over any others.....
	if (guiCurrentItemDescriptionScreen ==  MAP_SCREEN )
	{

		//return( FALSE );

			MSYS_DefineRegion( &gInvDesc, (UINT16)gsInvDescX, (UINT16)gsInvDescY ,(UINT16)(gsInvDescX + MAP_ITEMDESC_WIDTH), (UINT16)(gsInvDescY + MAP_ITEMDESC_HEIGHT), MSYS_PRIORITY_HIGHEST - 2,
				CURSOR_NORMAL, MSYS_NO_CALLBACK, ItemDescCallback );
		 	MSYS_AddRegion( &gInvDesc);

			giMapInvDescButtonImage=  LoadButtonImage( "INTERFACE\\itemdescdonebutton.sti" ,-1,0,-1,1,-1 );

			// create button
			giMapInvDescButton= QuickCreateButton( giMapInvDescButtonImage, (UINT16)( gsInvDescX + 204 ), (UINT16)( gsInvDescY + 107 ),
										BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
										( GUI_CALLBACK )BtnGenericMouseMoveButtonCallback, (GUI_CALLBACK)ItemDescDoneButtonCallback );

			fShowDescriptionFlag = TRUE;
	}
	else if(guiCurrentItemDescriptionScreen == SHOPKEEPER_SCREEN)
	{
		MSYS_DefineRegion( &gInvDesc, (UINT16)gsInvDescX, (UINT16)gsInvDescY ,(UINT16)(gsInvDescX + ITEMDESC_WIDTH), (UINT16)(gsInvDescY + ITEMDESC_HEIGHT), MSYS_PRIORITY_HIGHEST,
			MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemDescCallback );
		MSYS_AddRegion( &gInvDesc);
	}
	else
	{
		MSYS_DefineRegion( &gInvDesc, (UINT16)SM_ITEMDESC_START_X, (UINT16)SM_ITEMDESC_START_Y ,(UINT16)(SM_ITEMDESC_START_X + ITEMDESC_WIDTH), (UINT16)(SM_ITEMDESC_START_Y + ITEMDESC_HEIGHT), MSYS_PRIORITY_HIGHEST,
			MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemDescCallback );
		MSYS_AddRegion( &gInvDesc);
	}

	// Add region
	if ( (Item[ pObject->usItem ].usItemClass & IC_GUN) && !Item[pObject->usItem].rocketlauncher )
	{
		// Add button
//    if( guiCurrentScreen != MAP_SCREEN )
		//if( guiCurrentItemDescriptionScreen != MAP_SCREEN )
		if ( GetMagSize(gpItemDescObject) <= 99 )
			swprintf( pStr, L"%d/%d", (*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunShotsLeft, GetMagSize(gpItemDescObject));
		else
			swprintf( pStr, L"%d", (*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunShotsLeft );

		FilenameForBPP("INTERFACE\\infobox.sti", ubString);
		 sForeColour = ITEMDESC_AMMO_FORE;

		giItemDescAmmoButtonImages	= LoadButtonImage(ubString,AmmoTypes[(*pObject)[ubStatusIndex]->data.gun.ubGunAmmoType].grayed,AmmoTypes[(*pObject)[ubStatusIndex]->data.gun.ubGunAmmoType].offNormal,-1,AmmoTypes[(*pObject)[ubStatusIndex]->data.gun.ubGunAmmoType].onNormal,-1 );

		//switch( (*pObject)[ubStatusIndex]->data.gun.ubGunAmmoType )
		//{
		//	case AMMO_AP:
		//	case AMMO_SUPER_AP:
		//	 //sForeColour = ITEMDESC_FONTAPFORE;
		//	 giItemDescAmmoButtonImages			= LoadButtonImage(ubString,8,5,-1,7,-1 );
		//	 break;
		//	case AMMO_HP:
		//	 //sForeColour = ITEMDESC_FONTHPFORE;
		//
		//	 giItemDescAmmoButtonImages			= LoadButtonImage(ubString,12,9,-1,11,-1 );
		//	 break;
		//	default:
		//	 //sForeColour = FONT_MCOLOR_WHITE;
		//	 giItemDescAmmoButtonImages			= LoadButtonImage(ubString,4,1,-1,3,-1 );
		//	 break;

		//}

		if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
		{
			// in mapscreen, move over a bit
			giItemDescAmmoButton = CreateIconAndTextButton( giItemDescAmmoButtonImages, pStr, TINYFONT1,
															 sForeColour, FONT_MCOLOR_BLACK,
															 sForeColour, FONT_MCOLOR_BLACK,
															 TEXT_CJUSTIFIED,
															 (INT16)(ITEMDESC_AMMO_X + 18), (INT16)(ITEMDESC_AMMO_Y - 5), BUTTON_TOGGLE ,MSYS_PRIORITY_HIGHEST,
															 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemDescAmmoCallback );

		}
		else
		{

			// not in mapscreen
		 giItemDescAmmoButton = CreateIconAndTextButton( giItemDescAmmoButtonImages, pStr, TINYFONT1,
															 sForeColour, FONT_MCOLOR_BLACK,
															 sForeColour, FONT_MCOLOR_BLACK,
															 TEXT_CJUSTIFIED,
															 (INT16)(ITEMDESC_AMMO_X), (INT16)(ITEMDESC_AMMO_Y), BUTTON_TOGGLE ,MSYS_PRIORITY_HIGHEST,
															 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemDescAmmoCallback );

		 //if we are being called from the
		}
		//if we are being init from the shop keeper screen and this is a dealer item we are getting info from
		if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE && pShopKeeperItemDescObject != NULL )
		{
			//disable the eject button
			SpecifyDisabledButtonStyle( giItemDescAmmoButton, DISABLED_STYLE_HATCHED );

			DisableButton( giItemDescAmmoButton );
			SetButtonFastHelpText( giItemDescAmmoButton, L"\0" );
		}
		else{
			SetButtonFastHelpText( giItemDescAmmoButton, Message[ STR_EJECT_AMMO ] );
			//CHRISL: Include the ubStatusIndex in the region information so we know which object in a stack we're looking at
			MSYS_SetBtnUserData( giItemDescAmmoButton, 1, ubStatusIndex );
		}

		FindFontCenterCoordinates( (INT16)ITEMDESC_AMMO_TEXT_X, (INT16)ITEMDESC_AMMO_TEXT_Y, ITEMDESC_AMMO_TEXT_WIDTH, GetFontHeight( TINYFONT1 ), pStr, TINYFONT1, &usX, &usY);

		SpecifyButtonTextOffsets( giItemDescAmmoButton, (UINT8) usX, (UINT8) usY, TRUE );

		gfItemAmmoDown = FALSE;

	}

	if ( ITEM_PROS_AND_CONS( gpItemDescObject->usItem ) )
	{
		if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
		{
			sProsConsIndent = __max( StringPixLength( gzProsLabel, ITEMDESC_FONT ), StringPixLength( gzConsLabel, ITEMDESC_FONT ) ) + 10;
			for ( cnt = 0; cnt < 2; cnt++ )
			{
				// Add region for pros/cons help text
				MSYS_DefineRegion( &gProsAndConsRegions[ cnt ],
					(INT16)(ITEMDESC_PROS_START_X + sProsConsIndent),
					(INT16)(gsInvDescY + gMapItemDescProsConsRects[ cnt ].iTop),
					(INT16)(gsInvDescX + gMapItemDescProsConsRects[ cnt ].iRight),
					(INT16)(gsInvDescY + gMapItemDescProsConsRects[ cnt ].iBottom),
					MSYS_PRIORITY_HIGHEST, MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemDescCallback );

				MSYS_AddRegion( &gProsAndConsRegions[cnt]);

				if (cnt == 0)
				{
					wcscpy( gzFullItemPros, gzProsLabel );
					wcscat( gzFullItemPros, L" " );
					// use temp variable to prevent an initial comma from being displayed
					GenerateProsString( gzFullItemTemp, gpItemDescObject, 1000 );
					wcscat( gzFullItemPros, gzFullItemTemp );
					SetRegionFastHelpText( &(gProsAndConsRegions[ cnt ]), gzFullItemPros );
				}
				else
				{
					wcscpy( gzFullItemCons, gzConsLabel );
					wcscat( gzFullItemCons, L" " );
					// use temp variable to prevent an initial comma from being displayed
					GenerateConsString( gzFullItemTemp, gpItemDescObject, 1000 );
					wcscat( gzFullItemCons, gzFullItemTemp );
					SetRegionFastHelpText( &(gProsAndConsRegions[ cnt ]), gzFullItemCons );
				}
				SetRegionHelpEndCallback( &(gProsAndConsRegions[ cnt ]), HelpTextDoneCallback );
			}

		}
		else
		{
			sProsConsIndent = __max( StringPixLength( gzProsLabel, ITEMDESC_FONT ), StringPixLength( gzConsLabel, ITEMDESC_FONT ) ) + 10;
			for ( cnt = 0; cnt < 2; cnt++ )
			{
				// Add region for pros/cons help text
				MSYS_DefineRegion( &gProsAndConsRegions[ cnt ],
					(INT16)(ITEMDESC_PROS_START_X + sProsConsIndent),
					(INT16)(gsInvDescY + gItemDescProsConsRects[ cnt ].iTop),
					(INT16)(gsInvDescX + gItemDescProsConsRects[ cnt ].iRight),
					(INT16)(gsInvDescY + gItemDescProsConsRects[ cnt ].iBottom),
					MSYS_PRIORITY_HIGHEST, MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemDescCallback );

				MSYS_AddRegion( &gProsAndConsRegions[cnt]);

				if (cnt == 0)
				{
					wcscpy( gzFullItemPros, gzProsLabel );
					wcscat( gzFullItemPros, L" " );
					// use temp variable to prevent an initial comma from being displayed
					GenerateProsString( gzFullItemTemp, gpItemDescObject, 1000 );
					wcscat( gzFullItemPros, gzFullItemTemp );
					SetRegionFastHelpText( &(gProsAndConsRegions[ cnt ]), gzFullItemPros );
				}
				else
				{
					wcscpy( gzFullItemCons, gzConsLabel );
					wcscat( gzFullItemCons, L" " );
					// use temp variable to prevent an initial comma from being displayed
					GenerateConsString( gzFullItemTemp, gpItemDescObject, 1000 );
					wcscat( gzFullItemCons, gzFullItemTemp );
					SetRegionFastHelpText( &(gProsAndConsRegions[ cnt ]), gzFullItemCons );
				}
				SetRegionHelpEndCallback( &(gProsAndConsRegions[ cnt ]), HelpTextDoneCallback );
			}
		}
	}

	// Load graphic
	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	strcpy( VObjectDesc.ImageFile, "INTERFACE\\infobox_interface.sti" );
	CHECKF( AddVideoObject( &VObjectDesc, &guiItemDescBox) );

	if(ubPosition != 255 && UsingNewInventorySystem() == true)
	{
		VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
		strcpy( VObjectDesc.ImageFile, "INTERFACE\\infobox_background.sti" );
		CHECKF( AddVideoObject( &VObjectDesc, &guiItemDescBoxBackground) );
	}
	else
		guiItemDescBoxBackground = 0;

	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	strcpy( VObjectDesc.ImageFile, "INTERFACE\\iteminfoc.STI" );
	CHECKF( AddVideoObject( &VObjectDesc, &guiMapItemDescBox) );

	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	strcpy( VObjectDesc.ImageFile, "INTERFACE\\bullet.STI" );
	CHECKF( AddVideoObject( &VObjectDesc, &guiBullet) );

	if ( gpItemDescObject->usItem != MONEY  )
	{
		for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
		{
			// Build a mouse region here that is over any others.....
//			if (guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
			if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
				 MSYS_DefineRegion( &gItemDescAttachmentRegions[cnt], (INT16)(gsInvDescX + gMapItemDescAttachmentsXY[cnt].sX), (INT16)(gsInvDescY + gMapItemDescAttachmentsXY[cnt].sY), (INT16)(gsInvDescX + gMapItemDescAttachmentsXY[cnt].sX + gMapItemDescAttachmentsXY[cnt].sWidth), (INT16)(gsInvDescY + gMapItemDescAttachmentsXY[cnt].sY + gMapItemDescAttachmentsXY[cnt].sHeight), MSYS_PRIORITY_HIGHEST,
								 MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemDescAttachmentsCallback );
			else
				 MSYS_DefineRegion( &gItemDescAttachmentRegions[cnt], (INT16)(gsInvDescX + gItemDescAttachmentsXY[cnt].sX), (INT16)(gsInvDescY + gItemDescAttachmentsXY[cnt].sY), (INT16)(gsInvDescX + gItemDescAttachmentsXY[cnt].sX + gItemDescAttachmentsXY[cnt].sBarDx + gItemDescAttachmentsXY[cnt].sWidth), (INT16)(gsInvDescY + gItemDescAttachmentsXY[cnt].sY + gItemDescAttachmentsXY[cnt].sHeight), MSYS_PRIORITY_HIGHEST,
								 MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemDescAttachmentsCallback );
			// Add region
			MSYS_AddRegion( &gItemDescAttachmentRegions[cnt]);
			MSYS_SetRegionUserData( &gItemDescAttachmentRegions[cnt], 0, cnt );

			//CHRISL: Include the ubStatusIndex in the region information so we know which object in a stack we're looking at
			MSYS_SetRegionUserData( &gItemDescAttachmentRegions[cnt], 1, ubStatusIndex );

			// CHRISL: Instead of looking at object 0, let's look at the object we actually right clicked on using ubStatusIndex
			OBJECTTYPE* pAttachment = (*pObject)[ubStatusIndex]->GetAttachmentAtIndex(cnt);
			if (pAttachment) {
				SetRegionFastHelpText( &(gItemDescAttachmentRegions[ cnt ]), ItemNames[ pAttachment->usItem ] );
				SetRegionHelpEndCallback( &(gItemDescAttachmentRegions[ cnt ]), HelpTextDoneCallback );
			}
			else
			{
				SetRegionFastHelpText( &(gItemDescAttachmentRegions[ cnt ]), Message[ STR_ATTACHMENTS ] );
				SetRegionHelpEndCallback( &(gItemDescAttachmentRegions[ cnt ]), HelpTextDoneCallback );
			}
		}
	}
	else
	{
		memset( &gRemoveMoney, 0, sizeof( REMOVE_MONEY ) );
		gRemoveMoney.uiTotalAmount = (*gpItemDescObject)[0]->data.money.uiMoneyAmount;
		gRemoveMoney.uiMoneyRemaining = (*gpItemDescObject)[0]->data.money.uiMoneyAmount;
		gRemoveMoney.uiMoneyRemoving = 0;

		// Load graphic
		VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
		strcpy( VObjectDesc.ImageFile, "INTERFACE\\info_bil.sti" );
		CHECKF( AddVideoObject( &VObjectDesc, &guiMoneyGraphicsForDescBox) );

		//Create buttons for the money
//		if (guiCurrentScreen ==  MAP_SCREEN )
		if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
		{
			guiMoneyButtonImage = LoadButtonImage("INTERFACE\\Info_bil.sti", -1,1,-1,2,-1 );
			for(cnt=0; cnt<MAX_ATTACHMENTS-1; cnt++)
			{
				guiMoneyButtonBtn[cnt] = CreateIconAndTextButton( guiMoneyButtonImage, gzMoneyAmounts[cnt], BLOCKFONT2,
																 5, DEFAULT_SHADOW,
																 5, DEFAULT_SHADOW,
																 TEXT_CJUSTIFIED,
																 (UINT16)(gMapMoneyButtonLoc.x + gMoneyButtonOffsets[cnt].x), (UINT16)(gMapMoneyButtonLoc.y + gMoneyButtonOffsets[cnt].y), BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
																 DEFAULT_MOVE_CALLBACK, BtnMoneyButtonCallback );
				MSYS_SetBtnUserData( guiMoneyButtonBtn[cnt], 0, cnt);
				if( cnt == M_1000 && gRemoveMoney.uiTotalAmount < 1000 )
					DisableButton( guiMoneyButtonBtn[cnt] );
				else if( cnt == M_100 && gRemoveMoney.uiTotalAmount < 100 )
					DisableButton( guiMoneyButtonBtn[cnt] );
				else if( cnt == M_10 && gRemoveMoney.uiTotalAmount < 10 )
					DisableButton( guiMoneyButtonBtn[cnt] );
			}
			//Create the Done button
			guiMoneyDoneButtonImage = UseLoadedButtonImage( guiMoneyButtonImage, -1,3,-1,4,-1 );
			guiMoneyButtonBtn[cnt] = CreateIconAndTextButton( guiMoneyDoneButtonImage, gzMoneyAmounts[cnt], BLOCKFONT2,
															 5, DEFAULT_SHADOW,
															 5, DEFAULT_SHADOW,
															 TEXT_CJUSTIFIED,
															 (UINT16)(gMapMoneyButtonLoc.x + gMoneyButtonOffsets[cnt].x), (UINT16)(gMapMoneyButtonLoc.y + gMoneyButtonOffsets[cnt].y), BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
															 DEFAULT_MOVE_CALLBACK, BtnMoneyButtonCallback );
			MSYS_SetBtnUserData( guiMoneyButtonBtn[cnt], 0, cnt);

		}
		else
		{
			guiMoneyButtonImage = LoadButtonImage("INTERFACE\\Info_bil.sti", -1,1,-1,2,-1 );
			for(cnt=0; cnt<MAX_ATTACHMENTS-1; cnt++)
			{
				guiMoneyButtonBtn[cnt] = CreateIconAndTextButton( guiMoneyButtonImage, gzMoneyAmounts[cnt], BLOCKFONT2,
																 5, DEFAULT_SHADOW,
																 5, DEFAULT_SHADOW,
																 TEXT_CJUSTIFIED,
																 (UINT16)(gMoneyButtonLoc.x + gMoneyButtonOffsets[cnt].x), (UINT16)(gMoneyButtonLoc.y + gMoneyButtonOffsets[cnt].y), BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
																 DEFAULT_MOVE_CALLBACK, BtnMoneyButtonCallback );
				MSYS_SetBtnUserData( guiMoneyButtonBtn[cnt], 0, cnt);
				if( cnt == M_1000 && gRemoveMoney.uiTotalAmount < 1000 )
					DisableButton( guiMoneyButtonBtn[cnt] );
				else if( cnt == M_100 && gRemoveMoney.uiTotalAmount < 100 )
					DisableButton( guiMoneyButtonBtn[cnt] );
				else if( cnt == M_10 && gRemoveMoney.uiTotalAmount < 10 )
					DisableButton( guiMoneyButtonBtn[cnt] );
			}

			//Create the Done button
			guiMoneyDoneButtonImage = UseLoadedButtonImage( guiMoneyButtonImage, -1,3,6,4,5 );
			guiMoneyButtonBtn[cnt] = CreateIconAndTextButton( guiMoneyDoneButtonImage, gzMoneyAmounts[cnt], BLOCKFONT2,
															 5, DEFAULT_SHADOW,
															 5, DEFAULT_SHADOW,
															 TEXT_CJUSTIFIED,
															 (UINT16)(gMoneyButtonLoc.x + gMoneyButtonOffsets[cnt].x), (UINT16)(gMoneyButtonLoc.y + gMoneyButtonOffsets[cnt].y), BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
															 DEFAULT_MOVE_CALLBACK, BtnMoneyButtonCallback );
			MSYS_SetBtnUserData( guiMoneyButtonBtn[cnt], 0, cnt);
		}
	}


	fInterfacePanelDirty = DIRTYLEVEL2;


	gfInItemDescBox = TRUE;

	CHECKF( ReloadItemDesc( ) );

	if ( gpItemPointer )
	{
		gpAttachSoldier = gpItemPointerSoldier;
	}
	else
	{
		gpAttachSoldier = pSoldier;
	}
	//CHRISL: Instead of using attachments on item 0, use attachments on item we right clicked on using ubStatusIndex
	// store attachments that item originally had
	gOriginalAttachments = (*pObject)[ubStatusIndex]->attachments;

	if ( (gpItemPointer != NULL) && (gfItemDescHelpTextOffset == FALSE) && (CheckFact( FACT_ATTACHED_ITEM_BEFORE, 0 ) == FALSE) )
	{
		// set up help text for attachments
		for ( cnt = 0; cnt < NUM_INV_HELPTEXT_ENTRIES; cnt++ )
		{
			gItemDescHelpText.iXPosition[ cnt ] += gsInvDescX;
			gItemDescHelpText.iYPosition[ cnt ] += gsInvDescY;
		}

//		if ( !(Item[ pObject->usItem ].fFlags & ITEM_HIDDEN_ADDON) && ( ValidAttachment( gpItemPointer->usItem, pObject->usItem ) || ValidLaunchable( gpItemPointer->usItem, pObject->usItem ) || ValidMerge( gpItemPointer->usItem, pObject->usItem ) ) )
		if ( !(Item[ pObject->usItem ].hiddenaddon ) && ( ValidAttachment( gpItemPointer->usItem, pObject->usItem ) || ValidLaunchable( gpItemPointer->usItem, pObject->usItem ) || ValidMerge( gpItemPointer->usItem, pObject->usItem ) ) )
		{
			SetUpFastHelpListRegions(
				gItemDescHelpText.iXPosition,
				gItemDescHelpText.iYPosition,
				gItemDescHelpText.iWidth,
				gItemDescHelpText.sString1,
				NUM_INV_HELPTEXT_ENTRIES );
		}
		else
		{
			SetUpFastHelpListRegions(
				gItemDescHelpText.iXPosition,
				gItemDescHelpText.iYPosition,
				gItemDescHelpText.iWidth,
				gItemDescHelpText.sString2,
				NUM_INV_HELPTEXT_ENTRIES );
		}

		StartShowingInterfaceFastHelpText();

		SetFactTrue( FACT_ATTACHED_ITEM_BEFORE );
		gfItemDescHelpTextOffset = TRUE;
	}



	return( TRUE );
}


BOOLEAN ReloadItemDesc( )
{
	if ( !LoadTileGraphicForItem( &(Item[ gpItemDescObject->usItem ]), &guiItemGraphic ) )
	{
		return( FALSE );
	}

	//
	// Load name, desc
	//

	//if the player is extracting money from the players account, use a different item name and description
	if( gfAddingMoneyToMercFromPlayersAccount && gpItemDescObject->usItem == MONEY )
	{
		if ( !LoadItemInfo( MONEY_FOR_PLAYERS_ACCOUNT, gzItemName, gzItemDesc ) )
		{
			return( FALSE );
		}
	}
	else
	{
		if ( !LoadItemInfo( gpItemDescObject->usItem, gzItemName, gzItemDesc ) )
		{
			return( FALSE );
		}
	}

/*
	if (Item[ gpItemDescObject->usItem ].usItemClass & IC_WEAPON)
	{
		// load item pros and cons
		if ( !LoadItemProsAndCons( gpItemDescObject->usItem, gzItemPros, gzItemCons ) )
		{
			return( FALSE );
		}
	}
	else
	{
		wcscpy( gzItemPros, L"" );
		wcscpy( gzItemCons, L"" );
	}
	*/

	return( TRUE );
}


void ItemDescAmmoCallback(GUI_BUTTON *btn,INT32 reason)
{
	static BOOLEAN fRightDown = FALSE;
	CHAR16		pStr[10];
	CHAR8		ubString[48];
	UINT32		ubStatusIndex = MSYS_GetBtnUserData( btn, 1 );

/*	region gets disabled in SKI for shopkeeper boxes.  It now works normally for merc's inventory boxes!
	//if we are currently in the shopkeeper interface, return;
	if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		return;
	}
*/

	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		fRightDown = TRUE;
		gfItemAmmoDown = TRUE;
		btn->uiFlags |= BUTTON_CLICKED_ON;
	}
	else if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP && fRightDown )
	{
		fRightDown = FALSE;
		gfItemAmmoDown = FALSE;

		if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
		{
			//if ( gpItemPointer == NULL && EmptyWeaponMagazine( gpItemDescObject, &gItemPointer, ubStatusIndex ) )
			EmptyWeaponMagazine( gpItemDescObject, &gTempObject, ubStatusIndex );
			if(gpItemPointer == NULL)
			{
				//not holding anything
				gTempObject.MoveThisObjectTo(gItemPointer);
				gpItemPointer = &gItemPointer;
			}
			else
			{
				//holding an item
				if(Magazine[Item[gpItemPointer->usItem].ubClassIndex].ubCalibre == Weapon[Item[gpItemDescObject->usItem].ubClassIndex].ubCalibre)
				{
					ReloadGun(gpItemDescSoldier, gpItemDescObject, gpItemPointer);
				}
				if(gpItemPointer->ubNumberOfObjects == 0)
				{
					// nothing left in cursor
					gTempObject.MoveThisObjectTo(gItemPointer);
					gpItemPointer = &gItemPointer;
					if(gpItemPointer->ubNumberOfObjects == 0)
					{
						// delete object if nothing left
						MAPEndItemPointer( );
					}
				}
				else
				{
					// still holding someting so drop the clip we just pulled from the weapon
					// start by searching merc for a place to put the clip
					if(AutoPlaceObject(gpItemDescSoldier, &gTempObject, TRUE) == FALSE)
					{
						// couldn't find a place on the merc, so drop into the sector
						if(fShowMapInventoryPool)	//sector inventory panel is open
						{
							AutoPlaceObjectInInventoryStash(&gTempObject, gpItemDescSoldier->sGridNo);
							fMapPanelDirty = TRUE;
						}
						else	//sector inventory panel is closed
						{
							AddItemToPool(gpItemDescSoldier->sGridNo, &gTempObject, 1, gpItemDescSoldier->pathing.bLevel, WORLD_ITEM_REACHABLE, 0);
						}
					}
				}
			}
			// OK, END the description box
			//fItemDescDelete = TRUE;
			fInterfacePanelDirty = DIRTYLEVEL2;
			gpItemPointerSoldier = gpItemDescSoldier;

			if ( GetMagSize(gpItemDescObject) <= 99 )
				swprintf( pStr, L"%d/%d", (*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunShotsLeft, GetMagSize(gpItemDescObject));
			else
				swprintf( pStr, L"%d", (*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunShotsLeft );

			FilenameForBPP("INTERFACE\\infobox.sti", ubString);

			UnloadButtonImage(giItemDescAmmoButtonImages);
			giItemDescAmmoButtonImages	= LoadButtonImage(ubString,AmmoTypes[(*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunAmmoType].grayed,AmmoTypes[(*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunAmmoType].offNormal,-1,AmmoTypes[(*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunAmmoType].onNormal,-1 );
			//swprintf( pStr, L"0" );
			SpecifyButtonText( giItemDescAmmoButton, pStr );

			// Set mouse
			if(gpItemPointer->exists() == true)
			{
				guiExternVo = GetInterfaceGraphicForItem( &(Item[ gpItemPointer->usItem ]) );
				gusExternVoSubIndex = Item[ gpItemPointer->usItem ].ubGraphicNum;

				MSYS_ChangeRegionCursor( &gMPanelRegion , EXTERN_CURSOR );
				MSYS_SetCurrentCursor( EXTERN_CURSOR );

				fMapInventoryItem=TRUE;
				fTeamPanelDirty=TRUE;
			}
		}
		else
		{
			// Set pointer to item
			EmptyWeaponMagazine( gpItemDescObject, &gTempObject, ubStatusIndex );
			if(gpItemPointer == NULL)
			{
				//not holding anything
				gTempObject.MoveThisObjectTo(gItemPointer);
				gpItemPointer = &gItemPointer;
			}
			else
			{
				//holding an item
				if(Magazine[Item[gpItemPointer->usItem].ubClassIndex].ubCalibre == Weapon[Item[gpItemDescObject->usItem].ubClassIndex].ubCalibre)
				{
					ReloadGun(gpItemDescSoldier, gpItemDescObject, gpItemPointer);
				}
				if(gpItemPointer->ubNumberOfObjects == 0)
				{
					// nothing left in cursor
					gTempObject.MoveThisObjectTo(gItemPointer);
					gpItemPointer = &gItemPointer;
					if(gpItemPointer->ubNumberOfObjects == 0)
					{
						// delete object if nothing left
						EndItemPointer( );
					}
				}
				else
				{
					// still holding someting so drop the clip we just pulled from the weapon
					// start by searching merc for a place to put the clip
					if(AutoPlaceObject(gpItemDescSoldier, &gTempObject, TRUE) == FALSE)
					{
						AddItemToPool(gpItemDescSoldier->sGridNo, &gTempObject, 1, gpItemDescSoldier->pathing.bLevel, WORLD_ITEM_REACHABLE, 0);
					}
				}
			}
			gpItemPointerSoldier = gpItemDescSoldier;

			// if in SKI, load item into SKI's item pointer
			if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
			{
				// pick up bullets from weapon into cursor (don't try to sell)
				BeginSkiItemPointer( PLAYERS_INVENTORY, -1, FALSE );
			}

			// OK, END the description box
			//fItemDescDelete = TRUE;
			fInterfacePanelDirty = DIRTYLEVEL2;

			if ( GetMagSize(gpItemDescObject) <= 99 )
				swprintf( pStr, L"%d/%d", (*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunShotsLeft, GetMagSize(gpItemDescObject));
			else
				swprintf( pStr, L"%d", (*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunShotsLeft );

			FilenameForBPP("INTERFACE\\infobox.sti", ubString);

			UnloadButtonImage(giItemDescAmmoButtonImages);
			giItemDescAmmoButtonImages	= LoadButtonImage(ubString,AmmoTypes[(*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunAmmoType].grayed,AmmoTypes[(*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunAmmoType].offNormal,-1,AmmoTypes[(*gpItemDescObject)[ubStatusIndex]->data.gun.ubGunAmmoType].onNormal,-1 );
			//swprintf( pStr, L"0" );
			SpecifyButtonText( giItemDescAmmoButton, pStr );

			fItemDescDelete = TRUE;

		}
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

	}

}


//CHRISL: We need to know which item in the stack we're working with.
void DoAttachment( UINT8 subObject )
{
	if ( gpItemDescObject->AttachObject( gpItemDescSoldier, gpItemPointer, TRUE, subObject ) )
	{
		if (gpItemPointer->exists() == false)
		{
			// attachment attached, merge item consumed, etc

			if ( guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
			{
				MAPEndItemPointer( );
			}
			else
			{
				// End Item pickup
				gpItemPointer = NULL;
				EnableSMPanelButtons( TRUE , TRUE );

				MSYS_ChangeRegionCursor( &gSMPanelRegion , CURSOR_NORMAL );
				SetCurrentCursorFromDatabase( CURSOR_NORMAL );

				//if we are currently in the shopkeeper interface
				if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
				{
					//Clear out the moving cursor
					gMoveingItem.initialize();

					//change the curosr back to the normal one
					SetSkiCursor( CURSOR_NORMAL );
				}
			}
		}

		if ( gpItemDescObject->exists() == false )
		{
			// close desc panel panel
			DeleteItemDescriptionBox();
		}
		//Dirty interface
		fInterfacePanelDirty = DIRTYLEVEL2;

		ReloadItemDesc( );
	}

	// re-evaluate repairs
	gfReEvaluateEveryonesNothingToDo = TRUE;
}

void PermanantAttachmentMessageBoxCallBack( UINT8 ubExitValue )
{
	if ( ubExitValue == MSG_BOX_RETURN_YES )
	{
		DoAttachment(0);
	}
	// else do nothing
}

void ItemDescAttachmentsCallback( MOUSE_REGION * pRegion, INT32 iReason )
{
	UINT32					uiItemPos, ubStatusIndex;
	static BOOLEAN	fRightDown = FALSE;

	if ( gfItemDescObjectIsAttachment )
	{
		// screen out completely
		return;
	}

	uiItemPos = MSYS_GetRegionUserData( pRegion, 0 );
	ubStatusIndex = MSYS_GetRegionUserData( pRegion, 1 );
	OBJECTTYPE* pAttachment = (*gpItemDescObject)[ubStatusIndex]->GetAttachmentAtIndex(uiItemPos);

	if (iReason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		// if the item being described belongs to a shopkeeper, ignore attempts to pick it up / replace it
		if( ( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE ) && ( pShopKeeperItemDescObject != NULL ) )
		{
			return;
		}

		// Try to place attachment if something is in our hand
		// require as many APs as to reload
		if ( gpItemPointer != NULL )
		{
			// nb pointer could be NULL because of inventory manipulation in mapscreen from sector inv
			if ( !gpItemPointerSoldier || EnoughPoints( gpItemPointerSoldier, AttachmentAPCost( gpItemPointer->usItem, gpItemDescObject->usItem ), 0, TRUE ) )
			{
//				if ( (Item[ gpItemPointer->usItem ].fFlags & ITEM_INSEPARABLE) && ValidAttachment( gpItemPointer->usItem, gpItemDescObject->usItem ) )
				if ( (Item[ gpItemPointer->usItem ].inseparable ) && ValidAttachment( gpItemPointer->usItem, gpItemDescObject->usItem ) )
				{
					DoScreenIndependantMessageBox( Message[ STR_PERMANENT_ATTACHMENT ], ( UINT8 )MSG_BOX_FLAG_YESNO, PermanantAttachmentMessageBoxCallBack );
					return;
				}

				DoAttachment((UINT8)ubStatusIndex);
			}
		}
		else
		{
			// ATE: Make sure we have enough AP's to drop it if we pick it up!
			if ( pAttachment && EnoughPoints( gpItemDescSoldier, ( AttachmentAPCost( pAttachment->usItem, gpItemDescObject->usItem ) + AP_PICKUP_ITEM ), 0, TRUE ) )
			{
				// Get attachment if there is one
				// The follwing function will handle if no attachment is here
				if ( gpItemDescObject->RemoveAttachment( pAttachment, &gItemPointer, ubStatusIndex ) )
				{
					gpItemPointer = &gItemPointer;
					gpItemPointerSoldier = gpItemDescSoldier;

					if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
					{
						// Set mouse
						guiExternVo = GetInterfaceGraphicForItem( &(Item[ gpItemPointer->usItem ]) );
						gusExternVoSubIndex = Item[ gpItemPointer->usItem ].ubGraphicNum;

						MSYS_ChangeRegionCursor( &gMPanelRegion , EXTERN_CURSOR );
						MSYS_SetCurrentCursor( EXTERN_CURSOR );
						fMapInventoryItem=TRUE;
						fTeamPanelDirty=TRUE;
					}

					//if we are currently in the shopkeeper interface
					else if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
					{
						// pick up attachment from item into cursor (don't try to sell)
						BeginSkiItemPointer( PLAYERS_INVENTORY, -1, FALSE );
					}

					//Dirty interface
					fInterfacePanelDirty = DIRTYLEVEL2;

					// re-evaluate repairs
					gfReEvaluateEveryonesNothingToDo = TRUE;

					UpdateItemHatches();
				}
			}
		}
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_DWN )
	{
		fRightDown = TRUE;
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_UP && fRightDown )
	{
		fRightDown = FALSE;

		if ( pAttachment )
		{
			static OBJECTTYPE Object2;

			BOOLEAN fShopkeeperItem = FALSE;

			// remember if this is a shopkeeper's item we're viewing ( pShopKeeperItemDescObject will get nuked on deletion )
			if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE && pShopKeeperItemDescObject != NULL )
			{
				fShopkeeperItem = TRUE;
			}

			DeleteItemDescriptionBox( );

			Object2 = *pAttachment;
			gfItemDescObjectIsAttachment = TRUE;
			InternalInitItemDescriptionBox( &Object2, gsInvDescX, gsInvDescY, 0, gpItemDescSoldier );

			if ( fShopkeeperItem )
			{
				pShopKeeperItemDescObject = &Object2;
				StartSKIDescriptionBox( );
			}
		}
	}
}

void RenderItemDescriptionBox( )
{
  ETRLEObject						*pTrav;
	UINT32								usHeight, usWidth;
	INT16									sCenX, sCenY, sStrX;
	HVOBJECT							hVObject;
	CHAR16								sTempString[ 128 ];

	UINT16								uiStringLength, uiRightLength;
	static CHAR16					pStr[ 100 ];
	INT32									cnt;
	FLOAT									fWeight;
	INT16								usX, usY;
	UINT8									ubAttackAPs;
	BOOLEAN								fHatchOutAttachments = gfItemDescObjectIsAttachment; // if examining attachment, always hatch out attachment slots
	INT16									sProsConsIndent;
	INT8							showBox=0;

	int status = 0;
	int shotsLeft = 0;
	if (gpItemDescObject && gubItemDescStatusIndex < gpItemDescObject->ubNumberOfObjects) {
		status = (*gpItemDescObject)[ gubItemDescStatusIndex ]->data.objectStatus;
		shotsLeft = (*gpItemDescObject)[ gubItemDescStatusIndex ]->data.ubShotsLeft;
	}

	if( ( guiCurrentItemDescriptionScreen == MAP_SCREEN ) &&(gfInItemDescBox ) )
	{
    	// TAKE A LOOK AT THE VIDEO OBJECT SIZE ( ONE OF TWO SIZES ) AND CENTER!
		GetVideoObject( &hVObject, guiItemGraphic );
		pTrav = &(hVObject->pETRLEObject[ 0 ] );
		usHeight				= (UINT32)pTrav->usHeight;
		usWidth					= (UINT32)pTrav->usWidth;

		// CENTER IN SLOT!
		// REMOVE OFFSETS!
		sCenX = MAP_ITEMDESC_ITEM_X + (INT16)( abs( ITEMDESC_ITEM_WIDTH - (double)usWidth ) / 2 ) - pTrav->sOffsetX;
		sCenY = MAP_ITEMDESC_ITEM_Y + (INT16)( abs( ITEMDESC_ITEM_HEIGHT - (double)usHeight ) / 2 )- pTrav->sOffsetY;

		// CHRISL: Determine if we're looking at an LBENODE and display alternate box graphic
		if((UsingNewInventorySystem() == true) && iResolution != 0)
		{
			if(gpItemDescObject->IsActiveLBE(gubItemDescStatusIndex))
				showBox = gpItemDescObject->GetLBEPointer(gubItemDescStatusIndex)->lbeClass + 1;
			else if(Item[gpItemDescObject->usItem].usItemClass == IC_LBEGEAR)
				showBox = LoadBearingEquipment[Item[gpItemDescObject->usItem].ubClassIndex].lbeClass + 1;
			else
				showBox = 1;
		}
		BltVideoObjectFromIndex( guiSAVEBUFFER, guiMapItemDescBox, showBox, gsInvDescX, gsInvDescY, VO_BLT_SRCTRANSPARENCY, NULL );

		//Display the money 'seperating' border
		if ( gpItemDescObject->usItem == MONEY )
		{
			//Render the money Boxes
			BltVideoObjectFromIndex( guiSAVEBUFFER, guiMoneyGraphicsForDescBox, 0, (UINT16)(gMapMoneyButtonLoc.x + gMoneyButtonOffsets[0].x), (UINT16)(gMapMoneyButtonLoc.y + gMoneyButtonOffsets[0].y), VO_BLT_SRCTRANSPARENCY, NULL );
		}


		// Display item
		if(gGameSettings.fOptions[ TOPTION_SHOW_ITEM_SHADOW ]) BltVideoObjectOutlineShadowFromIndex( guiSAVEBUFFER, guiItemGraphic, 0, sCenX - 2, sCenY + 2  );

		BltVideoObjectFromIndex( guiSAVEBUFFER, guiItemGraphic, 0, sCenX, sCenY, VO_BLT_SRCTRANSPARENCY, NULL );


		// Display ststus
		DrawItemUIBarEx( gpItemDescObject, gubItemDescStatusIndex, (INT16)MAP_ITEMDESC_ITEM_STATUS_X, (INT16)MAP_ITEMDESC_ITEM_STATUS_Y, ITEMDESC_ITEM_STATUS_WIDTH, ITEMDESC_ITEM_STATUS_HEIGHT_MAP, 	Get16BPPColor( DESC_STATUS_BAR ), Get16BPPColor( DESC_STATUS_BAR_SHADOW ), TRUE, guiSAVEBUFFER );

		// CHRISL:  This block will display hatching for inactive LBE pockets
		// Display LBENODE attached items
		if(UsingNewInventorySystem() == true && Item[gpItemDescObject->usItem].usItemClass == IC_LBEGEAR)
		{
			RenderLBENODEItems( gpItemDescObject, gubItemDescStatusIndex );
		}

		if (gpItemPointer)
		{
//			if ( ( Item[ gpItemPointer->usItem ].fFlags & ITEM_HIDDEN_ADDON ) ||
			if ( ( Item[ gpItemPointer->usItem ].hiddenaddon  ) ||

			 ( !ValidItemAttachment( gpItemDescObject, gpItemPointer->usItem, FALSE ) &&
				 !ValidMerge( gpItemPointer->usItem, gpItemDescObject->usItem ) && !ValidLaunchable( gpItemPointer->usItem, gpItemDescObject->usItem ) ) )
			{
				// hatch out the attachment panels
				fHatchOutAttachments = TRUE;
			}
		}

		// Display attachments
		cnt = 0;
		for (attachmentList::iterator iter = (*gpItemDescObject)[gubItemDescStatusIndex]->attachments.begin();
			iter != (*gpItemDescObject)[gubItemDescStatusIndex]->attachments.end(); ++iter, ++cnt) {

			sCenX = (INT16)( gsInvDescX + gMapItemDescAttachmentsXY[cnt].sX + 5 );
			sCenY = (INT16)( gsInvDescY + gMapItemDescAttachmentsXY[cnt].sY - 1 );
			INVRenderItem( guiSAVEBUFFER, NULL, gpItemDescObject, sCenX, sCenY, gMapItemDescAttachmentsXY[cnt].sWidth, gMapItemDescAttachmentsXY[cnt].sHeight, DIRTYLEVEL2, NULL, (UINT8)(RENDER_ITEM_ATTACHMENT1 + cnt), FALSE, 0, gubItemDescStatusIndex );
			sCenX = sCenX - gItemDescAttachmentsXY[cnt].sBarDx;
			sCenY = sCenY + gItemDescAttachmentsXY[cnt].sBarDy;
			DrawItemUIBarEx( gpItemDescObject, (UINT8)(DRAW_ITEM_STATUS_ATTACHMENT1 + cnt), sCenX, sCenY, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT, Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , guiSAVEBUFFER, gubItemDescStatusIndex );
			//this code was the same inside both branches of the if below!
		}
		for (cnt = 0; cnt < MAX_ATTACHMENTS; ++cnt)
		{
			if (fHatchOutAttachments )
			{
				DrawHatchOnInventory( guiSAVEBUFFER, (INT16) (gsInvDescX + gMapItemDescAttachmentsXY[ cnt ].sX), (INT16) (gsInvDescY + gMapItemDescAttachmentsXY[ cnt ].sY - 2), (INT16)(gMapItemDescAttachmentsXY[ cnt ].sWidth + gMapItemDescAttachmentsXY[ cnt ].sBarDx), (INT16) (gMapItemDescAttachmentsXY[ cnt ].sHeight + 2) );
			}
		}

		if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_GUN || Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER )
		{
			// display bullets for ROF
			if ( !Weapon[gpItemDescObject->usItem].NoSemiAuto )
				BltVideoObjectFromIndex( guiSAVEBUFFER, guiBullet, 0, MAP_BULLET_SING_X, MAP_BULLET_SING_Y, VO_BLT_SRCTRANSPARENCY, NULL );

			if (GetShotsPerBurst(gpItemDescObject)> 0)
			{
				for ( cnt = 0; cnt < __min(GetShotsPerBurst(gpItemDescObject),12); cnt++ )
				{
					BltVideoObjectFromIndex( guiSAVEBUFFER, guiBullet, 0, MAP_BULLET_BURST_X + cnt * (BULLET_WIDTH/2 + 1), MAP_BULLET_BURST_Y, VO_BLT_SRCTRANSPARENCY, NULL );
				}
			}
			else if (GetAutofireShotsPerFiveAPs(gpItemDescObject) > 0 )
			{
				for ( cnt = 0; cnt < 10; cnt++ )
				{
					BltVideoObjectFromIndex( guiSAVEBUFFER, guiBullet, 0, MAP_BULLET_BURST_X + cnt * (BULLET_WIDTH/2 + 1), MAP_BULLET_BURST_Y, VO_BLT_SRCTRANSPARENCY, NULL );
				}
			}

		}

		RestoreExternBackgroundRect( gsInvDescX, gsInvDescY, MAP_ITEMDESC_WIDTH, MAP_ITEMDESC_HEIGHT );

		// CHRISL: This block will display misc information for items stored in LBE Pockets
		// Display LBENODE attached items
		if(UsingNewInventorySystem() == true && Item[gpItemDescObject->usItem].usItemClass == IC_LBEGEAR)
		{
			RenderLBENODEItems( gpItemDescObject, gubItemDescStatusIndex );
		}

		// Render font desc
		SetFont( ITEMDESC_FONT );
		SetFontBackground( FONT_MCOLOR_BLACK );
		SetFontForeground( FONT_FCOLOR_WHITE );
		SetFontShadow( ITEMDESC_FONTSHADOW3 );

		// Render name
		#ifdef JA2TESTVERSION
			mprintf( MAP_ITEMDESC_NAME_X, MAP_ITEMDESC_NAME_Y, L"%s (%d)", gzItemName, gpItemDescObject->usItem );
		#else
			mprintf( MAP_ITEMDESC_NAME_X, MAP_ITEMDESC_NAME_Y, L"%s", gzItemName );
		#endif

		SetFontForeground( FONT_BLACK );
		SetFontShadow( ITEMDESC_FONTSHADOW2 );

		DisplayWrappedString( (INT16)MAP_ITEMDESC_DESC_START_X, (INT16)MAP_ITEMDESC_DESC_START_Y, MAP_ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK,  gzItemDesc, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED);

		if ( ITEM_PROS_AND_CONS( gpItemDescObject->usItem ) )
		{
			if ( (Item[gpItemDescObject->usItem].fingerprintid ) && (*gpItemDescObject)[gubItemDescStatusIndex]->data.ubImprintID < NO_PROFILE )
			{
				// add name noting imprint
				swprintf( pStr, L"%s %s (%s)", AmmoCaliber[ Weapon[ gpItemDescObject->usItem ].ubCalibre ], WeaponType[ Weapon[ gpItemDescObject->usItem ].ubWeaponType ], gMercProfiles[ (*gpItemDescObject)[gubItemDescStatusIndex]->data.ubImprintID ].zNickname );
			}
			else
			{
				swprintf( pStr, L"%s %s", AmmoCaliber[ Weapon[ gpItemDescObject->usItem ].ubCalibre ], WeaponType[ Weapon[ gpItemDescObject->usItem ].ubWeaponType ] );
			}

			FindFontRightCoordinates( (INT16) MAP_ITEMDESC_CALIBER_X, (INT16) MAP_ITEMDESC_CALIBER_Y, MAP_ITEMDESC_CALIBER_WIDTH, ITEM_STATS_HEIGHT, pStr, ITEMDESC_FONT, &usX, &usY);
			mprintf( usX, usY, pStr );

			SetFontForeground( FONT_MCOLOR_DKWHITE2 );
			SetFontShadow( ITEMDESC_FONTSHADOW3 );
			mprintf( (INT16)MAP_ITEMDESC_PROS_START_X, (INT16)MAP_ITEMDESC_PROS_START_Y, gzProsLabel );

			sProsConsIndent = __max( StringPixLength( gzProsLabel, ITEMDESC_FONT ), StringPixLength( gzConsLabel, ITEMDESC_FONT ) ) + 10;

			GenerateProsString( gzItemPros, gpItemDescObject, MAP_ITEMDESC_DESC_WIDTH - sProsConsIndent - StringPixLength( DOTDOTDOT, ITEMDESC_FONT ) );
			if (gzItemPros[0] != 0)
			{
				SetFontForeground( FONT_BLACK );
				SetFontShadow( ITEMDESC_FONTSHADOW2 );
				DisplayWrappedString( (INT16)(MAP_ITEMDESC_PROS_START_X + sProsConsIndent), (INT16)MAP_ITEMDESC_PROS_START_Y, (INT16)(ITEMDESC_DESC_WIDTH - sProsConsIndent), 2, ITEMDESC_FONT, FONT_BLACK,  gzItemPros, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED );
			}

			SetFontForeground( FONT_MCOLOR_DKWHITE2 );
			SetFontShadow( ITEMDESC_FONTSHADOW3 );
			mprintf( (INT16)MAP_ITEMDESC_CONS_START_X, (INT16)MAP_ITEMDESC_CONS_START_Y, gzConsLabel );

			GenerateConsString( gzItemCons, gpItemDescObject, MAP_ITEMDESC_DESC_WIDTH - sProsConsIndent - StringPixLength( DOTDOTDOT, ITEMDESC_FONT ) );
			if (gzItemCons[0] != 0)
			{
				SetFontForeground( FONT_BLACK );
				SetFontShadow( ITEMDESC_FONTSHADOW2 );
				DisplayWrappedString( (INT16)(MAP_ITEMDESC_CONS_START_X + sProsConsIndent), (INT16)MAP_ITEMDESC_CONS_START_Y, (INT16)(ITEMDESC_DESC_WIDTH - sProsConsIndent), 2, ITEMDESC_FONT, FONT_BLACK,  gzItemCons, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED);
			}
		}

/*
		DisplayWrappedString( (INT16)MAP_ITEMDESC_PROS_START_X, (INT16)MAP_ITEMDESC_PROS_START_Y, MAP_ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK,  gzProsLabel, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED);
		if (gzItemPros[0] != 0)
		{
			DisplayWrappedString( (INT16)MAP_ITEMDESC_PROS_START_X, (INT16)MAP_ITEMDESC_PROS_START_Y, MAP_ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK,  gzItemPros, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED);
		}

		DisplayWrappedString( (INT16)MAP_ITEMDESC_CONS_START_X, (INT16)MAP_ITEMDESC_CONS_START_Y, MAP_ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK,  gzConsLabel, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED);
		if (gzItemCons[0] != 0)
		{
			DisplayWrappedString( (INT16)MAP_ITEMDESC_CONS_START_X, (INT16)MAP_ITEMDESC_CONS_START_Y, MAP_ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK,  gzItemCons, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED);
		}
*/

		// Get length of string
		uiRightLength=35;


		// Calculate total weight of item and attachments
		fWeight = gpItemDescObject->GetWeightOfObjectInStack(gubItemDescStatusIndex) / 10.0f;

		if ( !gGameSettings.fOptions[ TOPTION_USE_METRIC_SYSTEM ] ) // metric units not enabled
		{
			fWeight = fWeight * 2.2f;
		}

		if ( fWeight < 0.1 && gubItemDescStatusIndex < gpItemDescObject->ubNumberOfObjects )
		{
			fWeight = 0.1f;
		}

		// Render, stat  name
		if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_WEAPON )
		{
			SetFont( BLOCKFONT2 );
			SetFontForeground( 6 );
			SetFontShadow( DEFAULT_SHADOW );

			//LABELS
			swprintf( sTempString, gWeaponStatsDesc[ 0 ], GetWeightUnitString() );
			mprintf( gMapWeaponStats[ 0 ].sX + gsInvDescX, gMapWeaponStats[ 0 ].sY + gsInvDescY, L"%s", sTempString );
			//mprintf( gMapWeaponStats[ 2 ].sX + gsInvDescX, gMapWeaponStats[ 2 ].sY + gsInvDescY, L"%s", gMapWeaponStats[ 2 ].zDesc );
			if ( Item[ gpItemDescObject->usItem ].usItemClass & (IC_GUN | IC_LAUNCHER ) )
			{
				mprintf( gMapWeaponStats[ 3 ].sX + gsInvDescX, gMapWeaponStats[ 3 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 3 ] );
			}
			if ( !(Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER) && !Item[gpItemDescObject->usItem].rocketlauncher )
			{
				mprintf( gMapWeaponStats[ 4 ].sX + gsInvDescX, gMapWeaponStats[ 4 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 4 ] );
			}
			mprintf( gMapWeaponStats[ 5 ].sX + gsInvDescX, gMapWeaponStats[ 5 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 5 ] );
			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_GUN || Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER)
			{
				// equals sign
				if ( !Weapon[gpItemDescObject->usItem].NoSemiAuto )
					mprintf( gMapWeaponStats[ 7 ].sX + gsInvDescX, gMapWeaponStats[ 7 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 7 ] );
			}
			mprintf( gMapWeaponStats[ 1 ].sX + gsInvDescX, gMapWeaponStats[ 1 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 1 ] );


			if (GetShotsPerBurst(gpItemDescObject) > 0 || GetAutofireShotsPerFiveAPs(gpItemDescObject)>0)
			{
				mprintf( gMapWeaponStats[ 8 ].sX + gsInvDescX, gMapWeaponStats[ 8 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 8 ] );
			}

			SetFontForeground( 5 );
			//Status
			// This is gross, but to get the % to work out right...
			swprintf( pStr, L"%2d%%", status);
			FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 1 ].sX + gsInvDescX + gMapWeaponStats[ 1 ].sValDx + 6), (INT16)(gMapWeaponStats[ 1 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
			wcscat( pStr, L"%%" );
			mprintf( usX, usY, pStr );

			// Values
			if (fWeight <= (EXCEPTIONAL_WEIGHT / 10))
			{
				SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
			}
			else
			{
				SetFontForeground( 5 );
			}
			//Weight
			swprintf( pStr, L"%1.1f", fWeight );
			FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 0 ].sX + gsInvDescX + gMapWeaponStats[ 0 ].sValDx+6), (INT16)(gMapWeaponStats[ 0 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );

			if ( Item[ gpItemDescObject->usItem ].usItemClass & (IC_GUN | IC_LAUNCHER) )
			{

				if ( GunRange( gpItemDescObject ) >= EXCEPTIONAL_RANGE)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

				//Range
				 swprintf( pStr, L"%2d", ( GunRange( gpItemDescObject ) ) / 10 );
				 FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 3 ].sX + gsInvDescX + gMapWeaponStats[ 3 ].sValDx), (INT16)(gMapWeaponStats[ 3 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
				 mprintf( usX, usY, pStr );
			}

			if ( !(Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER) && !Item[gpItemDescObject->usItem].rocketlauncher )
			{
				UINT8 ubImpact = GetDamage(gpItemDescObject);

				if ( ubImpact  >= EXCEPTIONAL_DAMAGE)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

				//Damage
			 swprintf( pStr, L"%2d", ubImpact );
			 FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 4 ].sX + gsInvDescX + gMapWeaponStats[ 4 ].sValDx), (INT16)(gMapWeaponStats[ 4 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
			 mprintf( usX, usY, pStr );
		  }

			ubAttackAPs = BaseAPsToShootOrStab( DEFAULT_APS, DEFAULT_AIMSKILL, gpItemDescObject );

			if (ubAttackAPs <= EXCEPTIONAL_AP_COST)
			{
				SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
			}
			else
			{
				SetFontForeground( 5 );
			}

			 //Ap's
			if ( !Weapon[gpItemDescObject->usItem].NoSemiAuto )
			{
				swprintf( pStr, L"%2d", ubAttackAPs );
				FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 5 ].sX + gsInvDescX + gMapWeaponStats[ 5 ].sValDx), (INT16)(gMapWeaponStats[ 5 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}

			 if (GetShotsPerBurst(gpItemDescObject) > 0)
			 {

				if (GetShotsPerBurst(gpItemDescObject) >= EXCEPTIONAL_BURST_SIZE )//|| gpItemDescObject->usItem == G11)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

			  swprintf( pStr, L"%2d", ubAttackAPs + CalcAPsToBurst( DEFAULT_APS, gpItemDescObject ) );
			  FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 6 ].sX + gsInvDescX + gMapWeaponStats[ 6 ].sValDx), (INT16)(gMapWeaponStats[ 6 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
			  mprintf( usX, usY, pStr );
			 }
			 else if (GetAutofireShotsPerFiveAPs(gpItemDescObject) > 0)
			 {

					SetFontForeground( 5 );

					swprintf( pStr, L"%2d", ubAttackAPs + CalcAPsToAutofire( DEFAULT_APS, gpItemDescObject, 3 ) );
					FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 6 ].sX + gsInvDescX + gMapWeaponStats[ 6 ].sValDx), (INT16)(gMapWeaponStats[ 6 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
					mprintf( usX, usY, pStr );
			 }
		}
		else if ( gpItemDescObject->usItem == MONEY )
		{

			SetFontForeground( FONT_FCOLOR_WHITE );
			SetFontShadow( DEFAULT_SHADOW );

			//
			// Display the total amount of money
			//

			// if the player is taking money from their account
			if( gfAddingMoneyToMercFromPlayersAccount )
				swprintf( pStr, L"%ld", LaptopSaveInfo.iCurrentBalance );
			else
				swprintf( pStr, L"%ld", gRemoveMoney.uiTotalAmount );

			InsertCommasForDollarFigure( pStr );
			InsertDollarSignInToString( pStr );
			uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
			sStrX =  MAP_ITEMDESC_NAME_X + ( 245 - uiStringLength );
			mprintf( sStrX, MAP_ITEMDESC_NAME_Y, pStr );

			SetFont( BLOCKFONT2 );

			SetFontForeground( 6 );
			SetFontShadow( DEFAULT_SHADOW );

			//Display the 'Removing'
			mprintf( gMapMoneyStats[ 0 ].sX + gsInvDescX, gMapMoneyStats[ 0 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ MONEY_DESC_AMOUNT ] );
			//Display the 'REmaining'
			mprintf( gMapMoneyStats[ 2 ].sX + gsInvDescX, gMapMoneyStats[ 2 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ MONEY_DESC_AMOUNT_2_SPLIT ] );

			//Display the 'Amt removing'
			mprintf( gMapMoneyStats[ 1 ].sX + gsInvDescX, gMapMoneyStats[ 1 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ MONEY_DESC_REMAINING ] );
			//Display the 'REmaining amount'
			mprintf( gMapMoneyStats[ 3 ].sX + gsInvDescX, gMapMoneyStats[ 3 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ MONEY_DESC_TO_SPLIT ] );

			SetFontForeground( 5 );

			//Display the 'Seperate text'
			mprintf( (UINT16)(gMapMoneyButtonLoc.x + gMoneyButtonOffsets[cnt].x), (UINT16)(gMapMoneyButtonLoc.y + gMoneyButtonOffsets[cnt].y ), gzMoneyAmounts[4] );

			// The Money Remaining
			swprintf( pStr, L"%ld", gRemoveMoney.uiMoneyRemaining );
			InsertCommasForDollarFigure( pStr );
			InsertDollarSignInToString( pStr );
			uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
			sStrX =  gMapMoneyStats[ 1 ].sX + gsInvDescX + gMapMoneyStats[ 1 ].sValDx + ( uiRightLength - uiStringLength );
			mprintf( sStrX, gMapMoneyStats[ 1 ].sY + gsInvDescY, pStr );


			// The money removing
			SetFontForeground( 5 );
			swprintf( pStr, L"%ld", gRemoveMoney.uiMoneyRemoving );
			InsertCommasForDollarFigure( pStr );
			InsertDollarSignInToString( pStr );
			uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
			sStrX =  gMapMoneyStats[ 3 ].sX + gsInvDescX + gMapMoneyStats[ 3 ].sValDx + ( uiRightLength - uiStringLength );
			mprintf( sStrX, gMapMoneyStats[ 3 ].sY + gsInvDescY, pStr );

			// print label for amount

//			SetFontForeground( ITEMDESC_FONTFORE1 );
//			mprintf( gMapMoneyStats[ 1 ].sX + gsInvDescX, gMapMoneyStats[ 1 ].sY + gsInvDescY, L"%s", gMapMoneyStats[ 1 ].zDesc );


		}
		else if ( Item[ gpItemDescObject->usItem ].usItemClass == IC_MONEY )
		{
			SetFontForeground( FONT_FCOLOR_WHITE );
			SetFontShadow( DEFAULT_SHADOW );
			swprintf( pStr, L"%ld", (*gpItemDescObject)[gubItemDescStatusIndex]->data.money.uiMoneyAmount );
			InsertCommasForDollarFigure( pStr );
			InsertDollarSignInToString( pStr );
			uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
			sStrX =  MAP_ITEMDESC_NAME_X + ( 245 - uiStringLength );
			mprintf( sStrX, MAP_ITEMDESC_NAME_Y, pStr );
		}
		else
		{
			//Labels
			SetFont( BLOCKFONT2 );

			SetFontForeground( 6 );
			SetFontShadow( DEFAULT_SHADOW );

			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_AMMO )
			{
				mprintf( gMapWeaponStats[ 2 ].sX + gsInvDescX, gMapWeaponStats[ 2 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 2 ] );
			}
			else
			{
				mprintf( gMapWeaponStats[ 1 ].sX + gsInvDescX, gMapWeaponStats[ 1 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 1 ] );
			}
			swprintf( sTempString, gWeaponStatsDesc[ 0 ], GetWeightUnitString() );
			mprintf( gMapWeaponStats[ 0 ].sX + gsInvDescX, gMapWeaponStats[ 0 ].sY + gsInvDescY, sTempString );

			// Values
			SetFontForeground( 5 );


			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_AMMO )
			{
				// Ammo
					swprintf( pStr, L"%d/%d", shotsLeft, Magazine[ Item[ gpItemDescObject->usItem ].ubClassIndex ].ubMagSize ); //Pulmu: Correct # of rounds for stacked ammo.
					uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
		//			sStrX =  gMapWeaponStats[ 0 ].sX + gsInvDescX + gMapWeaponStats[ 0 ].sValDx + ( uiRightLength - uiStringLength );
					FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 2 ].sX + gsInvDescX + gMapWeaponStats[ 2 ].sValDx+6), (INT16)(gMapWeaponStats[ 2 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &sStrX, &usY);
					mprintf( sStrX, gMapWeaponStats[ 2 ].sY + gsInvDescY, pStr );
			}
			else
			{
				//Status
				swprintf( pStr, L"%2d%%", status);
				uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
	//			sStrX =  gMapWeaponStats[ 1 ].sX + gsInvDescX + gMapWeaponStats[ 1 ].sValDx + ( uiRightLength - uiStringLength );
				FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 1 ].sX + gsInvDescX + gMapWeaponStats[ 1 ].sValDx + 6), (INT16)(gMapWeaponStats[ 1 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &sStrX, &usY);
				wcscat( pStr, L"%%" );
				mprintf( sStrX, gMapWeaponStats[ 1 ].sY + gsInvDescY, pStr );
			}

			//Weight
			swprintf( pStr, L"%1.1f", fWeight );
			uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
//			sStrX =  gMapWeaponStats[ 0 ].sX + gsInvDescX + gMapWeaponStats[ 0 ].sValDx + ( uiRightLength - uiStringLength );
			FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 0 ].sX + gsInvDescX + gMapWeaponStats[ 0 ].sValDx+6), (INT16)(gMapWeaponStats[ 0 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &sStrX, &usY);
			mprintf( sStrX, gMapWeaponStats[ 0 ].sY + gsInvDescY, pStr );

			if ( ( InKeyRingPopup() == TRUE ) || ( Item[ gpItemDescObject->usItem ].usItemClass & IC_KEY ) )
			{
				SetFontForeground( 6 );

				// build description for keys .. the sector found
				swprintf( pStr, L"%s", sKeyDescriptionStrings[ 0 ] );
				mprintf( gMapWeaponStats[ 4 ].sX + gsInvDescX, gMapWeaponStats[ 4 ].sY + gsInvDescY, pStr );
				swprintf( pStr, L"%s", sKeyDescriptionStrings[ 1 ] );
				mprintf( gMapWeaponStats[ 4 ].sX + gsInvDescX, gMapWeaponStats[ 4 ].sY + gsInvDescY + GetFontHeight( BLOCKFONT ) + 2 , pStr );


				SetFontForeground( 5 );
				GetShortSectorString( ( INT16 ) SECTORX( KeyTable[ (*gpItemDescObject)[gubItemDescStatusIndex]->data.key.ubKeyID ].usSectorFound ), ( INT16 ) SECTORY( KeyTable[ (*gpItemDescObject)[gubItemDescStatusIndex]->data.key.ubKeyID ].usSectorFound ), sTempString  );
				swprintf( pStr, L"%s", sTempString );
				FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 4 ].sX + gsInvDescX ), (INT16)(gMapWeaponStats[ 4 ].sY + gsInvDescY ), 110 ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );

				swprintf( pStr, L"%d", KeyTable[ (*gpItemDescObject)[gubItemDescStatusIndex]->data.key.ubKeyID ].usDateFound );
				FindFontRightCoordinates( (INT16)(gMapWeaponStats[ 4 ].sX + gsInvDescX ), (INT16)(gMapWeaponStats[ 4 ].sY + gsInvDescY + GetFontHeight( BLOCKFONT ) + 2 ), 110 ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}

		}

		SetFontShadow( DEFAULT_SHADOW );
	}
	else if ( gfInItemDescBox )
	{

		// TAKE A LOOK AT THE VIDEO OBJECT SIZE ( ONE OF TWO SIZES ) AND CENTER!
		GetVideoObject( &hVObject, guiItemGraphic );
		pTrav = &(hVObject->pETRLEObject[ 0 ] );
		usHeight				= (UINT32)pTrav->usHeight;
		usWidth					= (UINT32)pTrav->usWidth;

		// CENTER IN SLOT!
		sCenX = ITEMDESC_ITEM_X + (INT16)( abs( ITEMDESC_ITEM_WIDTH - (double)usWidth ) / 2 ) - pTrav->sOffsetX;
		sCenY = ITEMDESC_ITEM_Y + (INT16)( abs( ITEMDESC_ITEM_HEIGHT - (double)usHeight ) / 2 ) - pTrav->sOffsetY;

		// CHRISL: Determine if we're looking at an LBENODE and display alternate box graphic
		RenderBackpackButtons(1);	/* CHRISL: Needed for new inventory backpack buttons */
		if((UsingNewInventorySystem() == true) && iResolution != 0)
		{
			if(gpItemDescObject->IsActiveLBE(gubItemDescStatusIndex))
				showBox = gpItemDescObject->GetLBEPointer(gubItemDescStatusIndex)->lbeClass;
			else if(Item[gpItemDescObject->usItem].usItemClass == IC_LBEGEAR)
				showBox = LoadBearingEquipment[Item[gpItemDescObject->usItem].ubClassIndex].lbeClass;
			if(guiItemDescBoxBackground != 0)
				BltVideoObjectFromIndex( guiSAVEBUFFER, guiItemDescBoxBackground, iResolution, SM_ITEMDESC_START_X, SM_ITEMDESC_START_Y, VO_BLT_SRCTRANSPARENCY, NULL );
		}
		// CHRISL: Setup default coords if we haven't initialized them yet
		if(gsInvDescX == NONE && gsInvDescY == NONE)
		{
			gsInvDescX = 115;
			gsInvDescY = (INT16)(INV_INTERFACE_START_Y + 1 );
		}
		BltVideoObjectFromIndex( guiSAVEBUFFER, guiItemDescBox, showBox, gsInvDescX, gsInvDescY, VO_BLT_SRCTRANSPARENCY, NULL );

		if ( gpItemDescObject->usItem == MONEY )
		{
			//Render the money Boxes
			BltVideoObjectFromIndex( guiSAVEBUFFER, guiMoneyGraphicsForDescBox, 0, (UINT16)(gsInvDescX+gItemDescAttachmentsXY[0].sX-1), (UINT16)(gsInvDescY+gItemDescAttachmentsXY[0].sY-2), VO_BLT_SRCTRANSPARENCY, NULL );
		}


		// Display item
		if(gGameSettings.fOptions[ TOPTION_SHOW_ITEM_SHADOW ]) BltVideoObjectOutlineShadowFromIndex( guiSAVEBUFFER, guiItemGraphic, 0, sCenX - 2, sCenY + 2  );
		BltVideoObjectFromIndex( guiSAVEBUFFER, guiItemGraphic, 0, sCenX, sCenY, VO_BLT_SRCTRANSPARENCY, NULL );

		// Display status
		DrawItemUIBarEx( gpItemDescObject, gubItemDescStatusIndex, (INT16)ITEMDESC_ITEM_STATUS_X, (INT16)ITEMDESC_ITEM_STATUS_Y, ITEMDESC_ITEM_STATUS_WIDTH, ITEMDESC_ITEM_STATUS_HEIGHT, 	Get16BPPColor( DESC_STATUS_BAR ), Get16BPPColor( DESC_STATUS_BAR_SHADOW ), TRUE, guiSAVEBUFFER );
	
		// CHRISL:  This block will display hatching for inactive LBE pockets
		// Display LBENODE attached items
		if(UsingNewInventorySystem() == true && Item[gpItemDescObject->usItem].usItemClass == IC_LBEGEAR)
		{
			RenderLBENODEItems( gpItemDescObject, gubItemDescStatusIndex );
		}

		if (gpItemPointer)
		{
//			if ( ( Item[ gpItemPointer->usItem ].fFlags & ITEM_HIDDEN_ADDON ) ||
			if ( ( Item[ gpItemPointer->usItem ].hiddenaddon ) ||

			 ( !ValidItemAttachment( gpItemDescObject, gpItemPointer->usItem, FALSE ) &&
				 !ValidMerge( gpItemPointer->usItem, gpItemDescObject->usItem ) && !ValidLaunchable( gpItemPointer->usItem, gpItemDescObject->usItem ) ) )
			{
				// hatch out the attachment panels
				fHatchOutAttachments = TRUE;
			}
		}

		// Display attachments
		cnt = 0;
		for (attachmentList::iterator iter = (*gpItemDescObject)[gubItemDescStatusIndex]->attachments.begin();
			iter != (*gpItemDescObject)[gubItemDescStatusIndex]->attachments.end(); ++iter, ++cnt) {
			sCenX = (INT16)( gsInvDescX + gItemDescAttachmentsXY[cnt].sX + 5 );
			sCenY = (INT16)( gsInvDescY + gItemDescAttachmentsXY[cnt].sY - 1 );

			INVRenderItem( guiSAVEBUFFER, NULL, gpItemDescObject, sCenX, sCenY, gItemDescAttachmentsXY[cnt].sWidth, gItemDescAttachmentsXY[cnt].sHeight, DIRTYLEVEL2, NULL, (UINT8)(RENDER_ITEM_ATTACHMENT1 + cnt), FALSE, 0, gubItemDescStatusIndex );

			sCenX = sCenX - gItemDescAttachmentsXY[cnt].sBarDx;
			sCenY = sCenY + gItemDescAttachmentsXY[cnt].sBarDy;
			DrawItemUIBarEx( gpItemDescObject, (UINT8)(DRAW_ITEM_STATUS_ATTACHMENT1 + cnt), sCenX, sCenY, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT, Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , guiSAVEBUFFER, gubItemDescStatusIndex );

			SetRegionFastHelpText( &(gItemDescAttachmentRegions[ cnt ]), ItemNames[ iter->usItem ] );
			SetRegionHelpEndCallback( &(gItemDescAttachmentRegions[ cnt ]), HelpTextDoneCallback );
		}
		for (; cnt < MAX_ATTACHMENTS; ++cnt)
		{
			//for the attachments that don't exist
			 SetRegionFastHelpText( &(gItemDescAttachmentRegions[ cnt ]), Message[ STR_ATTACHMENTS ] );
			 SetRegionHelpEndCallback( &(gItemDescAttachmentRegions[ cnt ]), HelpTextDoneCallback );
		}
		for (cnt = 0; cnt < MAX_ATTACHMENTS; ++cnt)
		{
			//now for all attachment slots regardless
			if (fHatchOutAttachments)
			{
				//UINT32 uiWhichBuffer = ( guiCurrentItemDescriptionScreen == MAP_SCREEN ) ? guiSAVEBUFFER : guiRENDERBUFFER;
				DrawHatchOnInventory( guiSAVEBUFFER, (INT16) (gsInvDescX + gItemDescAttachmentsXY[ cnt ].sX), (INT16) (gsInvDescY + gItemDescAttachmentsXY[ cnt ].sY - 2), (INT16)(gItemDescAttachmentsXY[ cnt ].sWidth + gItemDescAttachmentsXY[ cnt ].sBarDx), (INT16) (gItemDescAttachmentsXY[ cnt ].sHeight + 2) );
			}
		}

		if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_GUN || Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER )
		{
			// display bullets for ROF
			if ( !Weapon[gpItemDescObject->usItem].NoSemiAuto )
				BltVideoObjectFromIndex( guiSAVEBUFFER, guiBullet, 0, BULLET_SING_X, BULLET_SING_Y, VO_BLT_SRCTRANSPARENCY, NULL );

			if (GetShotsPerBurst(gpItemDescObject) > 0)
			{
				for ( cnt = 0; cnt < __min(GetShotsPerBurst(gpItemDescObject),12); cnt++ )
				{
					BltVideoObjectFromIndex( guiSAVEBUFFER, guiBullet, 0, BULLET_BURST_X + cnt * (BULLET_WIDTH/2 + 1), BULLET_BURST_Y, VO_BLT_SRCTRANSPARENCY, NULL );
				}
			}
			else if ( GetAutofireShotsPerFiveAPs(gpItemDescObject) > 0 )
			{
				for ( cnt = 0; cnt < 10; cnt++ )
				{
					BltVideoObjectFromIndex( guiSAVEBUFFER, guiBullet, 0, BULLET_BURST_X + cnt * (BULLET_WIDTH/2 + 1), BULLET_BURST_Y, VO_BLT_SRCTRANSPARENCY, NULL );
				}
			}

		}

		if(guiCurrentItemDescriptionScreen == SHOPKEEPER_SCREEN)
			RestoreExternBackgroundRect( gsInvDescX, gsInvDescY, 320, 135 );
		else
			RestoreExternBackgroundRect( SM_ITEMDESC_START_X, SM_ITEMDESC_START_Y, ITEMDESC_WIDTH, ITEMDESC_HEIGHT );

		// CHRISL: This block will display misc information for items stored in LBE Pockets
		// Display LBENODE attached items
		if(UsingNewInventorySystem() == true && Item[gpItemDescObject->usItem].usItemClass == IC_LBEGEAR)
		{
			RenderLBENODEItems( gpItemDescObject, gubItemDescStatusIndex );
		}

		// Render font desc
		SetFont( ITEMDESC_FONT );
		SetFontBackground( FONT_MCOLOR_BLACK );
		SetFontForeground( FONT_FCOLOR_WHITE );
		SetFontShadow( ITEMDESC_FONTSHADOW3 );

		// Render name
		// SET CLIPPING RECT FOR FONTS
		#ifdef JA2TESTVERSION
			mprintf( ITEMDESC_NAME_X, ITEMDESC_NAME_Y, L"%s (%d)", gzItemName, gpItemDescObject->usItem );
		#else
			mprintf( ITEMDESC_NAME_X, ITEMDESC_NAME_Y, L"%s", gzItemName );
		#endif

		// Render caliber and description

		SetFontForeground( FONT_BLACK );
		SetFontShadow( ITEMDESC_FONTSHADOW2 );

		DisplayWrappedString( (INT16)ITEMDESC_DESC_START_X, (INT16)ITEMDESC_DESC_START_Y, ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK,  gzItemDesc, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED);

		if ( ITEM_PROS_AND_CONS( gpItemDescObject->usItem ) )
		{
			if ( ( Item[gpItemDescObject->usItem].fingerprintid ) && (*gpItemDescObject)[gubItemDescStatusIndex]->data.ubImprintID < NO_PROFILE )
			{
				// add name noting imprint
				swprintf( pStr, L"%s %s (%s)", AmmoCaliber[ Weapon[ gpItemDescObject->usItem ].ubCalibre ], WeaponType[ Weapon[ gpItemDescObject->usItem ].ubWeaponType ], gMercProfiles[ (*gpItemDescObject)[gubItemDescStatusIndex]->data.ubImprintID ].zNickname );
			}
			else
			{
				swprintf( pStr, L"%s %s", AmmoCaliber[ Weapon[ gpItemDescObject->usItem ].ubCalibre ], WeaponType[ Weapon[ gpItemDescObject->usItem ].ubWeaponType ] );
			}

			FindFontRightCoordinates( (INT16) ITEMDESC_CALIBER_X, (INT16) ITEMDESC_CALIBER_Y, ITEMDESC_CALIBER_WIDTH, ITEM_STATS_HEIGHT, pStr, ITEMDESC_FONT, &usX, &usY);
			mprintf( usX, usY, pStr );

			SetFontForeground( FONT_MCOLOR_DKWHITE2 );
			SetFontShadow( ITEMDESC_FONTSHADOW3 );
			mprintf( (INT16)ITEMDESC_PROS_START_X, (INT16)ITEMDESC_PROS_START_Y, gzProsLabel );

			sProsConsIndent = __max( StringPixLength( gzProsLabel, ITEMDESC_FONT ), StringPixLength( gzConsLabel, ITEMDESC_FONT ) ) + 10;

			gzItemPros[0] = 0;
			GenerateProsString( gzItemPros, gpItemDescObject, ITEMDESC_DESC_WIDTH - sProsConsIndent - StringPixLength( DOTDOTDOT, ITEMDESC_FONT ) );
			if (gzItemPros[0] != 0)
			{
				SetFontForeground( FONT_BLACK );
				SetFontShadow( ITEMDESC_FONTSHADOW2 );
				DisplayWrappedString( (INT16)(ITEMDESC_PROS_START_X + sProsConsIndent), (INT16)ITEMDESC_PROS_START_Y, (INT16)(ITEMDESC_DESC_WIDTH - sProsConsIndent), 2, ITEMDESC_FONT, FONT_BLACK,  gzItemPros, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED );
			}

			SetFontForeground( FONT_MCOLOR_DKWHITE2 );
			SetFontShadow( ITEMDESC_FONTSHADOW3 );
			mprintf( (INT16)ITEMDESC_CONS_START_X, (INT16)ITEMDESC_CONS_START_Y, gzConsLabel );

			GenerateConsString( gzItemCons, gpItemDescObject, ITEMDESC_DESC_WIDTH - sProsConsIndent - StringPixLength( DOTDOTDOT, ITEMDESC_FONT ) );
			if (gzItemCons[0] != 0)
			{
				SetFontForeground( FONT_BLACK );
				SetFontShadow( ITEMDESC_FONTSHADOW2 );
				DisplayWrappedString( (INT16)(ITEMDESC_CONS_START_X + sProsConsIndent), (INT16)ITEMDESC_CONS_START_Y, (INT16)(ITEMDESC_DESC_WIDTH - sProsConsIndent), 2, ITEMDESC_FONT, FONT_BLACK,  gzItemCons, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED);
			}


		}


		// Get length of string
		uiRightLength=35;

		// Calculate total weight of item and attachments
		fWeight = gpItemDescObject->GetWeightOfObjectInStack(gubItemDescStatusIndex) / 10.0f;

		if ( !gGameSettings.fOptions[ TOPTION_USE_METRIC_SYSTEM ] ) // metric units not enabled
		{
			fWeight = fWeight * 2.2f;
		}

		if ( fWeight < 0.1 && gubItemDescStatusIndex < gpItemDescObject->ubNumberOfObjects )
		{
			fWeight = 0.1f;
		}

		// Render, stat  name
		if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_WEAPON )
		{

			SetFont( BLOCKFONT2 );
			SetFontForeground( 6 );
			SetFontShadow( DEFAULT_SHADOW );

			//LABELS
			swprintf( sTempString, gWeaponStatsDesc[ 0 ], GetWeightUnitString() );
			mprintf( gWeaponStats[ 0 ].sX + gsInvDescX, gWeaponStats[ 0 ].sY + gsInvDescY, sTempString );
//		mprintf( gWeaponStats[ 1 ].sX + gsInvDescX, gWeaponStats[ 1 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 1 ].zDesc );
//		mprintf( gWeaponStats[ 2 ].sX + gsInvDescX, gWeaponStats[ 2 ].sY + gsInvDescY, L"%s", gWeaponStats[ 2 ].zDesc );
			if ( Item[ gpItemDescObject->usItem ].usItemClass & (IC_GUN | IC_LAUNCHER ) )
			{
				mprintf( gWeaponStats[ 3 ].sX + gsInvDescX, gWeaponStats[ 3 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 3 ] );
			}
			if ( !(Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER) && !Item[gpItemDescObject->usItem].rocketlauncher )
			{
				mprintf( gWeaponStats[ 4 ].sX + gsInvDescX, gWeaponStats[ 4 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 4 ] );
			}
			mprintf( gWeaponStats[ 5 ].sX + gsInvDescX, gWeaponStats[ 5 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 5 ] );
			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_GUN || Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER )
			{
				if ( !Weapon[gpItemDescObject->usItem].NoSemiAuto )
					mprintf( gWeaponStats[ 7 ].sX + gsInvDescX, gWeaponStats[ 7 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 7 ] );
			}
			mprintf( gWeaponStats[ 1 ].sX + gsInvDescX, gWeaponStats[ 1 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 1 ] );

			if (GetShotsPerBurst(gpItemDescObject) > 0 || GetAutofireShotsPerFiveAPs(gpItemDescObject))
			{
				mprintf( gWeaponStats[ 8 ].sX + gsInvDescX, gWeaponStats[ 8 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 8 ] );
			}

			// Values
			if (fWeight <= (EXCEPTIONAL_WEIGHT / 10))
			{
				SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
			}
			else
			{
				SetFontForeground( 5 );
			}

			//Status
			swprintf( pStr, L"%2d%%", (*gpItemDescObject)[gubItemDescStatusIndex]->data.gun.bGunStatus );
			FindFontRightCoordinates( (INT16)(gWeaponStats[ 1 ].sX + gsInvDescX + gWeaponStats[ 1 ].sValDx), (INT16)(gWeaponStats[ 1 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
			wcscat( pStr, L"%%" );
			mprintf( usX, usY, pStr );

			//Wieght
			swprintf( pStr, L"%1.1f", fWeight );
			FindFontRightCoordinates( (INT16)(gWeaponStats[ 0 ].sX + gsInvDescX + gWeaponStats[ 0 ].sValDx), (INT16)(gWeaponStats[ 0 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );

			if ( Item[ gpItemDescObject->usItem ].usItemClass & (IC_GUN | IC_LAUNCHER) )
			{
				if ( GunRange( gpItemDescObject ) >= EXCEPTIONAL_RANGE)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

				swprintf( pStr,  L"%2d", ( GunRange( gpItemDescObject ) ) / 10 );
				FindFontRightCoordinates( (INT16)(gWeaponStats[ 3 ].sX + gsInvDescX + gWeaponStats[ 3 ].sValDx), (INT16)(gWeaponStats[ 3 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}

			if ( !(Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER) && !Item[gpItemDescObject->usItem].rocketlauncher )
			{
				UINT8 ubImpact = GetDamage(gpItemDescObject);
				if ( ubImpact  >= EXCEPTIONAL_DAMAGE)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

				swprintf( pStr, L"%2d", ubImpact );
				FindFontRightCoordinates( (INT16)(gWeaponStats[ 4 ].sX + gsInvDescX + gWeaponStats[ 4 ].sValDx), (INT16)(gWeaponStats[ 4 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}

			ubAttackAPs = BaseAPsToShootOrStab( DEFAULT_APS, DEFAULT_AIMSKILL, gpItemDescObject );

			if (ubAttackAPs <= EXCEPTIONAL_AP_COST)
			{
				SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
			}
			else
			{
				SetFontForeground( 5 );
			}

			if ( !Weapon[gpItemDescObject->usItem].NoSemiAuto )
			{
				swprintf( pStr, L"%2d", ubAttackAPs );
				FindFontRightCoordinates( (INT16)(gWeaponStats[ 5 ].sX + gsInvDescX + gWeaponStats[ 5 ].sValDx), (INT16)(gWeaponStats[ 5 ].sY + gsInvDescY ), ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}

			if (GetShotsPerBurst(gpItemDescObject)> 0)
			{
				if (GetShotsPerBurst(gpItemDescObject) >= EXCEPTIONAL_BURST_SIZE )//|| gpItemDescObject->usItem == G11)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

				swprintf( pStr, L"%2d", ubAttackAPs + CalcAPsToBurst( DEFAULT_APS, gpItemDescObject ) );
				FindFontRightCoordinates( (INT16)(gWeaponStats[ 6 ].sX + gsInvDescX + gWeaponStats[ 6 ].sValDx), (INT16)(gWeaponStats[ 6 ].sY + gsInvDescY ), ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY );
				mprintf( usX, usY, pStr );
			}
			else if (GetAutofireShotsPerFiveAPs(gpItemDescObject)> 0)
			{
				SetFontForeground( 5 );
				swprintf( pStr, L"%2d", ubAttackAPs + CalcAPsToBurst( DEFAULT_APS, gpItemDescObject ) );
				FindFontRightCoordinates( (INT16)(gWeaponStats[ 6 ].sX + gsInvDescX + gWeaponStats[ 6 ].sValDx), (INT16)(gWeaponStats[ 6 ].sY + gsInvDescY ), ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY );
				mprintf( usX, usY, pStr );
			}

		}
		else if ( gpItemDescObject->usItem == MONEY )
		{
			//Labels
			SetFont( BLOCKFONT2 );
			SetFontShadow( DEFAULT_SHADOW );

			SetFontForeground( 6 );

			//Display the 'Seperate text'

			//if the player is removing money from the players account
			if( gfAddingMoneyToMercFromPlayersAccount )
				mprintf( (UINT16)(gMoneyButtonLoc.x + gMoneyButtonOffsets[4].x), (UINT16)(gMoneyButtonLoc.y + gMoneyButtonOffsets[4].y), gzMoneyAmounts[5] );
			else
				mprintf( (UINT16)(gMoneyButtonLoc.x + gMoneyButtonOffsets[4].x), (UINT16)(gMoneyButtonLoc.y + gMoneyButtonOffsets[4].y), gzMoneyAmounts[4] );


			// if the player is taking money from their account
			if( gfAddingMoneyToMercFromPlayersAccount )
			{
				//Display the 'Removing'
				mprintf( gMoneyStats[ 0 ].sX + gsInvDescX, gMoneyStats[ 0 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ MONEY_DESC_PLAYERS ] );
				//Display the 'REmaining'
				mprintf( gMoneyStats[ 2 ].sX + gsInvDescX, gMoneyStats[ 2 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ MONEY_DESC_AMOUNT_2_WITHDRAW ] );
			}
			else
			{
				//Display the 'Removing'
				mprintf( gMoneyStats[ 0 ].sX + gsInvDescX, gMoneyStats[ 0 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ 0 ] );
				//Display the 'REmaining'
				mprintf( gMoneyStats[ 2 ].sX + gsInvDescX, gMoneyStats[ 2 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ 2 ] );
			}

			// Total Amount
			SetFontForeground( FONT_WHITE );
			swprintf( pStr, L"%d", gRemoveMoney.uiTotalAmount );
			InsertCommasForDollarFigure( pStr );
			InsertDollarSignInToString( pStr );
			FindFontRightCoordinates( (INT16)(ITEMDESC_NAME_X), (INT16)(ITEMDESC_NAME_Y ), 295,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );

			SetFontForeground( 6 );

			// if the player is taking money from their account
			if( gfAddingMoneyToMercFromPlayersAccount )
			{
				//Display the 'Amt removing'
				mprintf( gMoneyStats[ 1 ].sX + gsInvDescX, gMoneyStats[ 1 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ MONEY_DESC_BALANCE ] );
				//Display the 'REmaining amount'
				mprintf( gMoneyStats[ 3 ].sX + gsInvDescX, gMoneyStats[ 3 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ MONEY_DESC_TO_WITHDRAW ] );
			}
			else
			{
				//Display the 'Amt removing'
				mprintf( gMoneyStats[ 1 ].sX + gsInvDescX, gMoneyStats[ 1 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ 1 ] );
				//Display the 'REmaining amount'
				mprintf( gMoneyStats[ 3 ].sX + gsInvDescX, gMoneyStats[ 3 ].sY + gsInvDescY, L"%s", gMoneyStatsDesc[ 3 ] );
			}



			// Values
			SetFontForeground( 5 );

			//Display the total amount of money remaining
			swprintf( pStr, L"%ld", gRemoveMoney.uiMoneyRemaining );
			InsertCommasForDollarFigure( pStr );
			InsertDollarSignInToString( pStr );
			FindFontRightCoordinates( (INT16)(gMoneyStats[ 1 ].sX + gsInvDescX + gMoneyStats[ 1 ].sValDx), (INT16)(gMoneyStats[ 1 ].sY + gsInvDescY ), (UINT16)(ITEM_STATS_WIDTH-3),ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );

			//Display the total amount of money removing
			swprintf( pStr, L"%ld", gRemoveMoney.uiMoneyRemoving );
			InsertCommasForDollarFigure( pStr );
			InsertDollarSignInToString( pStr );
			FindFontRightCoordinates( (INT16)(gMoneyStats[ 3 ].sX + gsInvDescX + gMoneyStats[ 3 ].sValDx), (INT16)(gMoneyStats[ 3 ].sY + gsInvDescY), (UINT16)(ITEM_STATS_WIDTH-3) ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );

		}
		else if ( Item[ gpItemDescObject->usItem ].usItemClass == IC_MONEY )
		{
			SetFontForeground( FONT_FCOLOR_WHITE );
			SetFontShadow( DEFAULT_SHADOW );
			swprintf( pStr, L"%ld", (*gpItemDescObject)[gubItemDescStatusIndex]->data.money.uiMoneyAmount );
			InsertCommasForDollarFigure( pStr );
			InsertDollarSignInToString( pStr );

			FindFontRightCoordinates( (INT16)(ITEMDESC_NAME_X), (INT16)(ITEMDESC_NAME_Y ), 295,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );
		}
		else
		{
			//Labels
			SetFont( BLOCKFONT2 );
			SetFontForeground( 6 );
			SetFontShadow( DEFAULT_SHADOW );


			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_AMMO )
			{
				//Status
				mprintf( gWeaponStats[ 2 ].sX + gsInvDescX, gWeaponStats[ 2 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 2 ] );
			}
			else
			{
				mprintf( gWeaponStats[ 1 ].sX + gsInvDescX, gWeaponStats[ 1 ].sY + gsInvDescY, L"%s", gWeaponStatsDesc[ 1 ] );
			}

			//Weight
			swprintf( sTempString, gWeaponStatsDesc[ 0 ], GetWeightUnitString() );
			mprintf( gWeaponStats[ 0 ].sX + gsInvDescX, gWeaponStats[ 0 ].sY + gsInvDescY, sTempString );

			// Values
			SetFontForeground( 5 );

			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_AMMO )
			{
				// Ammo - print amount
				//Status
				swprintf( pStr, L"%d/%d", shotsLeft, Magazine[ Item[ gpItemDescObject->usItem ].ubClassIndex ].ubMagSize );		  //Pulmu: Correct # of rounds for stacked ammo
				FindFontRightCoordinates( (INT16)(gWeaponStats[ 2 ].sX + gsInvDescX + gWeaponStats[ 2 ].sValDx), (INT16)(gWeaponStats[ 2 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}
			else
			{
				//Status
				swprintf( pStr, L"%2d%%", status );
				FindFontRightCoordinates( (INT16)(gWeaponStats[ 1 ].sX + gsInvDescX + gWeaponStats[ 1 ].sValDx), (INT16)(gWeaponStats[ 1 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
				wcscat( pStr, L"%%" );
				mprintf( usX, usY, pStr );
			}

			if( ( InKeyRingPopup() == TRUE ) || ( Item[ gpItemDescObject->usItem ].usItemClass & IC_KEY ) )
			{
				SetFontForeground( 6 );

				// build description for keys .. the sector found
				swprintf( pStr, L"%s", sKeyDescriptionStrings[ 0 ] );
				mprintf( gWeaponStats[ 4 ].sX + gsInvDescX, gWeaponStats[ 4 ].sY + gsInvDescY, pStr );
				swprintf( pStr, L"%s", sKeyDescriptionStrings[ 1 ] );
				mprintf( gWeaponStats[ 4 ].sX + gsInvDescX, gWeaponStats[ 4 ].sY + gsInvDescY + GetFontHeight( BLOCKFONT ) + 2 , pStr );


				SetFontForeground( 5 );
				GetShortSectorString( ( INT16 ) SECTORX( KeyTable[ (*gpItemDescObject)[gubItemDescStatusIndex]->data.key.ubKeyID ].usSectorFound ), ( INT16 ) SECTORY( KeyTable[ (*gpItemDescObject)[gubItemDescStatusIndex]->data.key.ubKeyID ].usSectorFound ), sTempString  );
				swprintf( pStr, L"%s", sTempString );
				FindFontRightCoordinates( (INT16)(gWeaponStats[ 4 ].sX + gsInvDescX ), (INT16)(gWeaponStats[ 4 ].sY + gsInvDescY ), 110 ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );

				swprintf( pStr, L"%d", KeyTable[ (*gpItemDescObject)[gubItemDescStatusIndex]->data.key.ubKeyID ].usDateFound );
				FindFontRightCoordinates( (INT16)(gWeaponStats[ 4 ].sX + gsInvDescX ), (INT16)(gWeaponStats[ 4 ].sY + gsInvDescY + GetFontHeight( BLOCKFONT ) + 2 ), 110 ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}




			//Weight
			swprintf( pStr, L"%1.1f", fWeight );
			FindFontRightCoordinates( (INT16)(gWeaponStats[ 0 ].sX + gsInvDescX + gWeaponStats[ 0 ].sValDx), (INT16)(gWeaponStats[ 0 ].sY + gsInvDescY ), ITEM_STATS_WIDTH ,ITEM_STATS_HEIGHT ,pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );
		}

		SetFontShadow( DEFAULT_SHADOW );

	}

}

// CHRISL: New function to display items stored in an LBENODE
void RenderLBENODEItems( OBJECTTYPE *pObj, int subObject )
{
	extern int			PLAYER_INFO_X;
	extern int			PLAYER_INFO_Y;
	INV_REGIONS			LBEInvPocketXY[12];
	SOLDIERTYPE	*pSoldier;
	OBJECTTYPE	*pObject;
	INT16		sX, sY;
	INT16		sBarX, sBarY;
	INT16		lbePocket = ITEM_NOT_FOUND;
	UINT32		lClass;
	bool		activeNode = pObj->IsActiveLBE(subObject);
	bool		wornItem = false;

	// Start by verifying that this item is an LBENODE
	if(Item[pObj->usItem].usItemClass != IC_LBEGEAR || iResolution == 0)
		return;

	// Set selected merc
	if(guiCurrentItemDescriptionScreen == MAP_SCREEN)
		GetSoldier( &pSoldier, gCharactersList[bSelectedInfoChar].usSolID );
	else
		pSoldier = gpSMCurrentMerc;
	
	// Is the object we're looking at currently worn
	for(unsigned int x = VESTPOCKPOS; x <= BPACKPOCKPOS; x++)
	{
		if(pObj == &pSoldier->inv[x])
		{
			wornItem = true;
			break;
		}
	}

	LBENODE* pLBE = NULL;
	if(activeNode == true)
	{
		pLBE = pObj->GetLBEPointer(subObject);
		lClass = pLBE->lbeClass;
	}
	else {
		lClass = LoadBearingEquipment[Item[pObj->usItem].ubClassIndex].lbeClass;
	}

	std::vector<INT8> pocketKey;
	// Setup pocket coords
	switch (lClass)
	{
		case THIGH_PACK:
			if(pObj->IsActiveLBE(subObject) == false && pObj == &pSoldier->inv[RTHIGHPOCKPOS])
				GetLBESlots(RTHIGHPOCKPOS, pocketKey);
			else
				GetLBESlots(LTHIGHPOCKPOS, pocketKey);
			if(guiCurrentItemDescriptionScreen == MAP_SCREEN){
				InitInvData(LBEInvPocketXY[0], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 101, PLAYER_INFO_Y + 287);
				InitInvData(LBEInvPocketXY[1], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 137, PLAYER_INFO_Y + 287);
				InitInvData(LBEInvPocketXY[2], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 101, PLAYER_INFO_Y + 311);
				InitInvData(LBEInvPocketXY[3], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 137, PLAYER_INFO_Y + 311);
				InitInvData(LBEInvPocketXY[4], FALSE, INV_BAR_DX, INV_BAR_DY, VEST_INV_SLOT_WIDTH, VEST_INV_SLOT_HEIGHT, PLAYER_INFO_X + 112, PLAYER_INFO_Y + 335);
			}
			else{
				InitInvData(LBEInvPocketXY[0], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 586, INV_INTERFACE_START_Y + 10);
				InitInvData(LBEInvPocketXY[1], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 622, INV_INTERFACE_START_Y + 10);
				InitInvData(LBEInvPocketXY[2], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 586, INV_INTERFACE_START_Y + 34);
				InitInvData(LBEInvPocketXY[3], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 622, INV_INTERFACE_START_Y + 34);
				InitInvData(LBEInvPocketXY[4], FALSE, INV_BAR_DX, INV_BAR_DY, VEST_INV_SLOT_WIDTH, VEST_INV_SLOT_HEIGHT, INTERFACE_START_X + 597, INV_INTERFACE_START_Y + 58);
			}
			InitInvData(LBEInvPocketXY[5], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			InitInvData(LBEInvPocketXY[6], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			InitInvData(LBEInvPocketXY[7], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			InitInvData(LBEInvPocketXY[8], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			InitInvData(LBEInvPocketXY[9], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			InitInvData(LBEInvPocketXY[10], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			InitInvData(LBEInvPocketXY[11], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			break;
		case VEST_PACK:
			GetLBESlots(VESTPOCKPOS, pocketKey);
			if(guiCurrentItemDescriptionScreen == MAP_SCREEN){
				InitInvData(LBEInvPocketXY[0], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 22, PLAYER_INFO_Y + 299);
				InitInvData(LBEInvPocketXY[1], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 58, PLAYER_INFO_Y + 299);
				InitInvData(LBEInvPocketXY[2], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 94, PLAYER_INFO_Y + 299);
				InitInvData(LBEInvPocketXY[3], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 130, PLAYER_INFO_Y + 299);
				InitInvData(LBEInvPocketXY[4], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 166, PLAYER_INFO_Y + 299);
				InitInvData(LBEInvPocketXY[5], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 22, PLAYER_INFO_Y + 323);
				InitInvData(LBEInvPocketXY[6], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 58, PLAYER_INFO_Y + 323);
				InitInvData(LBEInvPocketXY[7], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 94, PLAYER_INFO_Y + 323);
				InitInvData(LBEInvPocketXY[8], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 130, PLAYER_INFO_Y + 323);
				InitInvData(LBEInvPocketXY[9], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 166, PLAYER_INFO_Y + 323);
				InitInvData(LBEInvPocketXY[10], FALSE, INV_BAR_DX, INV_BAR_DY, VEST_INV_SLOT_WIDTH, VEST_INV_SLOT_HEIGHT, PLAYER_INFO_X + 202, PLAYER_INFO_Y + 299);
				InitInvData(LBEInvPocketXY[11], FALSE, INV_BAR_DX, INV_BAR_DY, VEST_INV_SLOT_WIDTH, VEST_INV_SLOT_HEIGHT, PLAYER_INFO_X + 202, PLAYER_INFO_Y + 323);
			}
			else{
				InitInvData(LBEInvPocketXY[0], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 269, INV_INTERFACE_START_Y + 139);
				InitInvData(LBEInvPocketXY[1], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 305, INV_INTERFACE_START_Y + 139);
				InitInvData(LBEInvPocketXY[2], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 341, INV_INTERFACE_START_Y + 139);
				InitInvData(LBEInvPocketXY[3], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 377, INV_INTERFACE_START_Y + 139);
				InitInvData(LBEInvPocketXY[4], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 413, INV_INTERFACE_START_Y + 139);
				InitInvData(LBEInvPocketXY[5], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 269, INV_INTERFACE_START_Y + 163);
				InitInvData(LBEInvPocketXY[6], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 305, INV_INTERFACE_START_Y + 163);
				InitInvData(LBEInvPocketXY[7], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 341, INV_INTERFACE_START_Y + 163);
				InitInvData(LBEInvPocketXY[8], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 377, INV_INTERFACE_START_Y + 163);
				InitInvData(LBEInvPocketXY[9], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 413, INV_INTERFACE_START_Y + 163);
				InitInvData(LBEInvPocketXY[10], FALSE, INV_BAR_DX, INV_BAR_DY, VEST_INV_SLOT_WIDTH, VEST_INV_SLOT_HEIGHT, INTERFACE_START_X + 449, INV_INTERFACE_START_Y + 139);
				InitInvData(LBEInvPocketXY[11], FALSE, INV_BAR_DX, INV_BAR_DY, VEST_INV_SLOT_WIDTH, VEST_INV_SLOT_HEIGHT, INTERFACE_START_X + 449, INV_INTERFACE_START_Y + 163);
			}
			break;
		case COMBAT_PACK:
			GetLBESlots(CPACKPOCKPOS, pocketKey);
			if(guiCurrentItemDescriptionScreen == MAP_SCREEN){
				InitInvData(LBEInvPocketXY[0], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 101, PLAYER_INFO_Y + 287);
				InitInvData(LBEInvPocketXY[1], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 137, PLAYER_INFO_Y + 287);
				InitInvData(LBEInvPocketXY[2], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 101, PLAYER_INFO_Y + 311);
				InitInvData(LBEInvPocketXY[3], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 137, PLAYER_INFO_Y + 311);
				InitInvData(LBEInvPocketXY[4], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, PLAYER_INFO_X + 104, PLAYER_INFO_Y + 335);
				InitInvData(LBEInvPocketXY[5], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, PLAYER_INFO_X + 104, PLAYER_INFO_Y + 359);
				InitInvData(LBEInvPocketXY[6], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, PLAYER_INFO_X + 104, PLAYER_INFO_Y + 383);
			}
			else{
				InitInvData(LBEInvPocketXY[0], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 585, INV_INTERFACE_START_Y + 10);
				InitInvData(LBEInvPocketXY[1], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 621, INV_INTERFACE_START_Y + 10);
				InitInvData(LBEInvPocketXY[2], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 585, INV_INTERFACE_START_Y + 34);
				InitInvData(LBEInvPocketXY[3], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 621, INV_INTERFACE_START_Y + 34);
				InitInvData(LBEInvPocketXY[4], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, INTERFACE_START_X + 657, INV_INTERFACE_START_Y + 10);
				InitInvData(LBEInvPocketXY[5], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, INTERFACE_START_X + 657, INV_INTERFACE_START_Y + 34);
				InitInvData(LBEInvPocketXY[6], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, INTERFACE_START_X + 657, INV_INTERFACE_START_Y + 58);
			}
			InitInvData(LBEInvPocketXY[7], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			InitInvData(LBEInvPocketXY[8], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			InitInvData(LBEInvPocketXY[9], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			InitInvData(LBEInvPocketXY[10], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			InitInvData(LBEInvPocketXY[11], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, 0, 0);
			break;
		case BACKPACK:
			GetLBESlots(BPACKPOCKPOS, pocketKey);
			if(guiCurrentItemDescriptionScreen == MAP_SCREEN){
				InitInvData(LBEInvPocketXY[0], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 68, PLAYER_INFO_Y + 275);
				InitInvData(LBEInvPocketXY[1], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 68, PLAYER_INFO_Y + 299);
				InitInvData(LBEInvPocketXY[2], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 68, PLAYER_INFO_Y + 323);
				InitInvData(LBEInvPocketXY[3], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 68, PLAYER_INFO_Y + 347);
				InitInvData(LBEInvPocketXY[4], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 104, PLAYER_INFO_Y + 275);
				InitInvData(LBEInvPocketXY[5], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 104, PLAYER_INFO_Y + 299);
				InitInvData(LBEInvPocketXY[6], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 104, PLAYER_INFO_Y + 323);
				InitInvData(LBEInvPocketXY[7], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, PLAYER_INFO_X + 104, PLAYER_INFO_Y + 347);
				InitInvData(LBEInvPocketXY[8], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, PLAYER_INFO_X + 140, PLAYER_INFO_Y + 275);
				InitInvData(LBEInvPocketXY[9], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, PLAYER_INFO_X + 140, PLAYER_INFO_Y + 299);
				InitInvData(LBEInvPocketXY[10], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, PLAYER_INFO_X + 140, PLAYER_INFO_Y + 323);
				InitInvData(LBEInvPocketXY[11], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, PLAYER_INFO_X + 140, PLAYER_INFO_Y + 347);
			}
			else{
				InitInvData(LBEInvPocketXY[0], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 585, INV_INTERFACE_START_Y + 10);
				InitInvData(LBEInvPocketXY[1], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 585, INV_INTERFACE_START_Y + 34);
				InitInvData(LBEInvPocketXY[2], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 585, INV_INTERFACE_START_Y + 58);
				InitInvData(LBEInvPocketXY[3], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 585, INV_INTERFACE_START_Y + 82);
				InitInvData(LBEInvPocketXY[4], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 621, INV_INTERFACE_START_Y + 10);
				InitInvData(LBEInvPocketXY[5], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 621, INV_INTERFACE_START_Y + 34);
				InitInvData(LBEInvPocketXY[6], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 621, INV_INTERFACE_START_Y + 58);
				InitInvData(LBEInvPocketXY[7], FALSE, INV_BAR_DX, INV_BAR_DY, SM_INV_SLOT_WIDTH, SM_INV_SLOT_HEIGHT, INTERFACE_START_X + 621, INV_INTERFACE_START_Y + 82);
				InitInvData(LBEInvPocketXY[8], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, INTERFACE_START_X + 657, INV_INTERFACE_START_Y + 10);
				InitInvData(LBEInvPocketXY[9], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, INTERFACE_START_X + 657, INV_INTERFACE_START_Y + 34);
				InitInvData(LBEInvPocketXY[10], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, INTERFACE_START_X + 657, INV_INTERFACE_START_Y + 58);
				InitInvData(LBEInvPocketXY[11], TRUE, INV_BAR_DX, INV_BAR_DY, BIG_INV_SLOT_WIDTH, BIG_INV_SLOT_HEIGHT, INTERFACE_START_X + 657, INV_INTERFACE_START_Y + 82);
			}
			break;
		default:
			break;
	}
	// Display contents of LBENODE
	for(unsigned int cnt=0; cnt<pocketKey.size(); cnt++)
	{
		sX = LBEInvPocketXY[cnt].sX;
		sY = LBEInvPocketXY[cnt].sY;
		lbePocket = LoadBearingEquipment[Item[pObj->usItem].ubClassIndex].lbePocketIndex[icPocket[pocketKey[cnt]]];
		pObject = NULL;
		if(wornItem == true)
		{
			if(pSoldier->inv[pocketKey[cnt]].exists() == true)
				pObject = &(pSoldier->inv[pocketKey[cnt]]);
		}
		else if(activeNode == true)
		{
			if(pLBE->inv[cnt].exists() == true)
				pObject = &pLBE->inv[cnt];
		}
		if(lbePocket == 0){	// Deactivate Pocket
			DrawHatchOnInventory( guiSAVEBUFFER, sX, sY, (UINT16)(LBEInvPocketXY[cnt].sWidth-1), (UINT16)(LBEInvPocketXY[cnt].sHeight-1), 0 );
		}
		else if(pObject == NULL){	// Nothing in sPocket.  Display silouhette.
			INVRenderSilhouette( guiSAVEBUFFER, lbePocket, 0, sX, sY, LBEInvPocketXY[cnt].sWidth, LBEInvPocketXY[cnt].sHeight);
		}
		else if(pObject != NULL){
			INVRenderItem( guiSAVEBUFFER, pSoldier, pObject, sX, sY, LBEInvPocketXY[cnt].sWidth, LBEInvPocketXY[cnt].sHeight, 2, NULL, 0, 0, 0 );
			sBarX = sX - LBEInvPocketXY[cnt].sBarDx;
			sBarY = sY + LBEInvPocketXY[cnt].sBarDy;
			DrawItemUIBarEx( pObject, 0, sBarX, sBarY, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT,	Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , guiSAVEBUFFER);
		}
//		if (gpItemPointer != NULL)
//			RenderPocketItemCapacity( ItemSlotLimit(gpItemPointer, pocketKey[cnt], pSoldier), pocketKey[cnt], pSoldier);
		//CHRISL: Remove this line for now.  Though we do need something to better show that pockets on this screen are read-only
		//ShadowVideoSurfaceRect(guiSAVEBUFFER,sX,sY,(gSMInvData[ pocketKey[cnt] ].sWidth+sX),(gSMInvData[ pocketKey[cnt] ].sHeight+sY));
	}
}

void HandleItemDescriptionBox( BOOLEAN *pfDirty )
{
	if ( fItemDescDelete )
	{
		DeleteItemDescriptionBox( );
		fItemDescDelete = FALSE;
		*pfDirty = DIRTYLEVEL2;
	}

}


void DeleteItemDescriptionBox( )
{
	INT32 cnt;

	if( gfInItemDescBox == FALSE )
	{
		return;
	}

//	DEF:

	//Used in the shopkeeper interface
	if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
	{
		DeleteShopKeeperItemDescBox();
	}

	// check for any AP costs
	if ( ( gTacticalStatus.uiFlags & TURNBASED ) && ( gTacticalStatus.uiFlags & INCOMBAT ) )
	{
		if (gpAttachSoldier)
		{
			UINT8 ubAPCost = 0;

			// check for change in attachments
			unsigned int originalSize = gOriginalAttachments.size();
			unsigned int newSize = (*gpItemDescObject)[0]->attachments.size();

			if (newSize != originalSize) {
				attachmentList::iterator originalIter;
				attachmentList::iterator newIter;
				//an attachment was changed, find the change
				for (originalIter = gOriginalAttachments.begin(), newIter = (*gpItemDescObject)[0]->attachments.begin();
					originalIter != gOriginalAttachments.end() && newIter != (*gpItemDescObject)[0]->attachments.end();
					++originalIter, ++newIter) {
					if (*originalIter == *newIter) {
						continue;
					}
					else {
						break;
					}
				}
				if (newSize < originalSize) {
					//an attachment was removed, charge APs
					ubAPCost = AttachmentAPCost(originalIter->usItem,gpItemDescObject->usItem);
				}
				else {
					//an attachment was added charge APs
					//lalien: changed to charge AP's for reloading a GL/RL
					if ( Item[ gpItemDescObject->usItem ].usItemClass == IC_LAUNCHER || Item[gpItemDescObject->usItem].cannon )
					{
						ubAPCost = GetAPsToReload( gpItemDescObject );
					}
					else
					{
						ubAPCost = AttachmentAPCost(newIter->usItem,gpItemDescObject->usItem);
					}
				}
			}

			if (ubAPCost)
			{
				DeductPoints( gpAttachSoldier, ubAPCost, 0 );
			}
		}
	}

	//Remove
	DeleteVideoObjectFromIndex( guiItemDescBox );
	if(UsingNewInventorySystem() == true && guiItemDescBoxBackground != 0)
		DeleteVideoObjectFromIndex( guiItemDescBoxBackground );
	DeleteVideoObjectFromIndex( guiMapItemDescBox );
	RenderBackpackButtons(0);	/* CHRISL: Needed for new inventory backpack buttons */
	DeleteVideoObjectFromIndex( guiBullet );
	// Delete item graphic
	DeleteVideoObjectFromIndex( guiItemGraphic );

	gfInItemDescBox = FALSE;

//	if( guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN  )
	if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
	{
		UnloadButtonImage( giMapInvDescButtonImage );
		RemoveButton( giMapInvDescButton );
	}

	// Remove region
	MSYS_RemoveRegion( &gInvDesc);


	if( gpItemDescObject->usItem != MONEY )
	{
		for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
		{
			MSYS_RemoveRegion( &gItemDescAttachmentRegions[cnt]);
		}
	}
	else
	{
		UnloadButtonImage( guiMoneyButtonImage );
		UnloadButtonImage( guiMoneyDoneButtonImage );
		for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
		{
			RemoveButton( guiMoneyButtonBtn[cnt] );
		}
	}

	if ( ITEM_PROS_AND_CONS( gpItemDescObject->usItem ) )
	{
		MSYS_RemoveRegion( &gProsAndConsRegions[0] );
		MSYS_RemoveRegion( &gProsAndConsRegions[1] );
	}

	if(( ( Item[ gpItemDescObject->usItem ].usItemClass & IC_GUN ) && !Item[gpItemDescObject->usItem].rocketlauncher ) )
	{
		// Remove button
		UnloadButtonImage( giItemDescAmmoButtonImages );
		RemoveButton( giItemDescAmmoButton );
	}
//	if(guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
	if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
	{
	 fCharacterInfoPanelDirty=TRUE;
	 fMapPanelDirty = TRUE;
	 fTeamPanelDirty = TRUE;
	 fMapScreenBottomDirty = TRUE;
	}

	if( InKeyRingPopup() == TRUE )
	{
		DeleteKeyObject(gpItemDescObject);
		gpItemDescObject = NULL;
		fShowDescriptionFlag = FALSE;
		fInterfacePanelDirty = DIRTYLEVEL2;
		return;
	}

	fShowDescriptionFlag = FALSE;
	fInterfacePanelDirty = DIRTYLEVEL2;

	if( gpItemDescObject->usItem == MONEY )
	{
		//if there is no money remaining
		if( gRemoveMoney.uiMoneyRemaining == 0 && !gfAddingMoneyToMercFromPlayersAccount )
		{
			//get rid of the money in the slot
			gpItemDescObject->initialize();
			gpItemDescObject = NULL;
		}
	}

	if( gfAddingMoneyToMercFromPlayersAccount )
		gfAddingMoneyToMercFromPlayersAccount = FALSE;

	gfItemDescObjectIsAttachment = FALSE;
	gpItemDescObject = NULL;
}


void InternalBeginItemPointer( SOLDIERTYPE *pSoldier, OBJECTTYPE *pObject, INT8 bHandPos )
{
//	BOOLEAN fOk;

	// If not null return
	if ( gpItemPointer != NULL )
	{
		return;
	}

	// Copy into cursor...
	gItemPointer = *pObject;

	// Dirty interface
	fInterfacePanelDirty = DIRTYLEVEL2;
	gpItemPointer = &gItemPointer;
	gpItemPointerSoldier = pSoldier;
	gbItemPointerSrcSlot = bHandPos;
	gbItemPointerLocateGood = TRUE;

	CheckForDisabledForGiveItem( );

	EnableSMPanelButtons( FALSE, TRUE );

	gfItemPointerDifferentThanDefault = FALSE;

	// re-evaluate repairs
	gfReEvaluateEveryonesNothingToDo = TRUE;
}

void BeginItemPointer( SOLDIERTYPE *pSoldier, UINT8 ubHandPos )
{
	int numToMove = 0;
	if (_KeyDown( SHIFT ))
	{
		// Remove all from soldier's slot
		numToMove = ALL_OBJECTS;
	}
	else
	{
		numToMove = 1;
	}
	pSoldier->inv[ubHandPos].MoveThisObjectTo(gTempObject, numToMove, pSoldier, ubHandPos);

	if ( gTempObject.exists() == false )
	{
		//oops, the move failed.  It might have failed because the object was force placed
		//to a slot where the ItemSizeLimit is 0, try again
		//this method won't work with LBEs in LBE pockets
		pSoldier->inv[ubHandPos].MoveThisObjectTo(gTempObject, numToMove);
	}

	if ( gTempObject.exists() == true )
	{
		InternalBeginItemPointer( pSoldier, &gTempObject, ubHandPos );
	}
}


void BeginKeyRingItemPointer( SOLDIERTYPE *pSoldier, UINT8 ubKeyRingPosition )
{
	BOOLEAN fOk;

	// If not null return
	if ( gpItemPointer != NULL )
	{
		return;
	}

	if (_KeyDown( SHIFT ))
	{
		// Remove all from soldier's slot
		fOk = RemoveKeysFromSlot( pSoldier, ubKeyRingPosition, pSoldier->pKeyRing[ ubKeyRingPosition ].ubNumber, &gItemPointer );
	}
	else
	{
		RemoveKeyFromSlot( pSoldier, ubKeyRingPosition, &gItemPointer );
		fOk = (gItemPointer.ubNumberOfObjects == 1);
	}


	if (fOk)
	{
		// ATE: Look if we are a BLOODIED KNIFE, and change if so, making guy scream...

		// Dirty interface
		fInterfacePanelDirty = DIRTYLEVEL2;
		gpItemPointer = &gItemPointer;
		gpItemPointerSoldier = pSoldier;
		gbItemPointerSrcSlot = ubKeyRingPosition;

		if ( (guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
		{
			guiExternVo = GetInterfaceGraphicForItem( &(Item[ gpItemPointer->usItem ]) );
			gusExternVoSubIndex = Item[ gpItemPointer->usItem ].ubGraphicNum;

			fMapInventoryItem=TRUE;
			MSYS_ChangeRegionCursor( &gMPanelRegion , EXTERN_CURSOR );
			MSYS_SetCurrentCursor( EXTERN_CURSOR );
		}
	}
	else
	{
		//Debug mesg
	}



	gfItemPointerDifferentThanDefault = FALSE;
}

void EndItemPointer( )
{
	if ( gpItemPointer != NULL )
	{
		gpItemPointer = NULL;
		gbItemPointerSrcSlot = NO_SLOT;
		MSYS_ChangeRegionCursor( &gSMPanelRegion , CURSOR_NORMAL );
		MSYS_SetCurrentCursor( CURSOR_NORMAL );

		if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
		{
			gMoveingItem.initialize();
			SetSkiCursor( CURSOR_NORMAL );
		}
		else
		{
			EnableSMPanelButtons( TRUE , TRUE );
		}

		gbItemPointerLocateGood = FALSE;

		// re-evaluate repairs
		gfReEvaluateEveryonesNothingToDo = TRUE;
	}
}

void DrawItemFreeCursor( )
{
	//OBJECTTYPE		*gpItemPointer;
	//UINT16				usItemSnapCursor;

	// Get usIndex and then graphic for item
	guiExternVo = GetInterfaceGraphicForItem( &(Item[ gpItemPointer->usItem ]) );
	gusExternVoSubIndex = Item[ gpItemPointer->usItem ].ubGraphicNum;

	MSYS_ChangeRegionCursor( &gSMPanelRegion , EXTERN_CURSOR );
	MSYS_SetCurrentCursor( EXTERN_CURSOR );
}

void HideItemTileCursor( )
{
//	RemoveTopmost( gusCurMousePos, gusItemPointer );

}

BOOLEAN SoldierCanSeeCatchComing( SOLDIERTYPE *pSoldier, INT16 sSrcGridNo )
{
	return( TRUE );
/*-
	INT32							cnt;
	INT8							bDirection, bTargetDirection;

	bTargetDirection = (INT8)GetDirectionToGridNoFromGridNo( pSoldier->sGridNo, sSrcGridNo );

	// Look 3 directions Clockwise from what we are facing....
	bDirection = pSoldier->bDirection;

	for ( cnt = 0; cnt < 3; cnt++ )
	{
		if ( bDirection == bTargetDirection )
		{
			return( TRUE );
		}

		bDirection = gOneCDirection[ bDirection ];
	}

	// Look 3 directions CounterClockwise from what we are facing....
	bDirection = pSoldier->bDirection;

	for ( cnt = 0; cnt < 3; cnt++ )
	{
		if ( bDirection == bTargetDirection )
		{
			return( TRUE );
		}

		bDirection = gOneCCDirection[ bDirection ];
	}

	// If here, nothing good can happen!
	return( FALSE );
-*/

}

void DrawItemTileCursor( )
{
	INT16						sMapPos;
	UINT16						usIndex;
	UINT8							ubSoldierID;
	INT16							sAPCost;
	BOOLEAN						fRecalc;
	UINT32						uiCursorFlags;
	INT16							sFinalGridNo;
	UINT32						uiCursorId = CURSOR_ITEM_GOOD_THROW;
	SOLDIERTYPE				*pSoldier;
	BOOLEAN						fGiveItem = FALSE;
	INT16							sActionGridNo;
	UINT8							ubDirection;
	static UINT32			uiOldCursorId = 0;
	static UINT16			usOldMousePos = 0;
	INT16							sEndZ = 0;
	INT16							sDist;
	INT8							bLevel;

	if (GetMouseMapPos( &sMapPos) )
	{
		if ( gfUIFullTargetFound )
		{
			// Force mouse position to guy...
			sMapPos = MercPtrs[ gusUIFullTargetID ]->sGridNo;
		}

		gusCurMousePos = sMapPos;

		if( gusCurMousePos != usOldMousePos )
		{
			gfItemPointerDifferentThanDefault = FALSE;
		}

		// Save old one..
		usOldMousePos = gusCurMousePos;

		// Default to turning adjacent area gridno off....
		gfUIHandleShowMoveGrid = FALSE;

		// If we are over a talkable guy, set flag
		if ( IsValidTalkableNPCFromMouse( &ubSoldierID, TRUE, FALSE, TRUE ) )
		{
			fGiveItem = TRUE;
		}


		// WANNE: Prevent duplication of items cheat-bug:
		// You need two mercenaries. You place required item to first mercenary's inventory, 
		// then you take the item and point cursor with the item at the second mercenary. 
		// Then you click right mouse button and then left one. 
		// During the process of giving the item from the first mercenary to the second quicly move the item to the another slot of the inventory. 
		// As a result of it the item will be given to the second mercenary and the first mercenary will still have it.
		
		// OK, if different than default, change....
		//if ( gfItemPointerDifferentThanDefault )
		//{
		//	fGiveItem = !fGiveItem;
		//}


		// Get recalc and cursor flags
		fRecalc = GetMouseRecalcAndShowAPFlags( &uiCursorFlags, NULL );

		// OK, if we begin to move, reset the cursor...
		if ( uiCursorFlags & MOUSE_MOVING )
		{
			EndPhysicsTrajectoryUI( );
		}

		// Get Pyth spaces away.....
		sDist = PythSpacesAway( gpItemPointerSoldier->sGridNo, gusCurMousePos );


		// If we are here and we are not selected, select!
		// ATE Design discussion propably needed here...
		if ( gpItemPointerSoldier->ubID != gusSelectedSoldier )
		{
			SelectSoldier( gpItemPointerSoldier->ubID, FALSE, FALSE );
		}

		// ATE: if good for locate, locate to selected soldier....
		if ( gbItemPointerLocateGood )
		{
			gbItemPointerLocateGood = FALSE;
			LocateSoldier( gusSelectedSoldier, FALSE );
		}

		if ( !fGiveItem )
		{
			if ( UIHandleOnMerc( FALSE ) && sMapPos != gpItemPointerSoldier->sGridNo )
			{
				// We are on a guy.. check if they can catch or not....
				if ( gfUIFullTargetFound )
				{
					// Get soldier
					pSoldier = MercPtrs[ gusUIFullTargetID ];

					// Are they on our team?
					// ATE: Can't be an EPC
					if ( pSoldier->bTeam == gbPlayerNum && !AM_AN_EPC( pSoldier ) && !( pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE ) )
					{
						if ( sDist <= PASSING_ITEM_DISTANCE_OKLIFE )
						{
							// OK, on a valid pass
							gfUIMouseOnValidCatcher = 4;
							gubUIValidCatcherID			= (UINT8)gusUIFullTargetID;
						}
						else
						{
							// Can they see the throw?
							if ( SoldierCanSeeCatchComing( pSoldier, gpItemPointerSoldier->sGridNo ) )
							{
								// OK, set global that this buddy can see catch...
								gfUIMouseOnValidCatcher = TRUE;
								gubUIValidCatcherID			= (UINT8)gusUIFullTargetID;
							}
						}
					}
				}
			}

			// We're going to toss it!
			if ( gTacticalStatus.uiFlags & INCOMBAT )
			{
				gfUIDisplayActionPoints = TRUE;
				gUIDisplayActionPointsOffX = 15;
				gUIDisplayActionPointsOffY = 15;
			}

			// If we are tossing...
			if (  sDist <= 1 && gfUIMouseOnValidCatcher == 0 || gfUIMouseOnValidCatcher == 4 )
			{
				gsCurrentActionPoints = AP_PICKUP_ITEM;
			}
			else
			{
				gsCurrentActionPoints = AP_TOSS_ITEM;
			}

		}
		else
		{
			if ( gfUIFullTargetFound )
			{
				UIHandleOnMerc( FALSE );

				// OK, set global that this buddy can see catch...
				gfUIMouseOnValidCatcher = 2;
				gubUIValidCatcherID			= (UINT8)gusUIFullTargetID;

				// If this is a robot, change to say 'reload'
				if ( MercPtrs[ gusUIFullTargetID ]->flags.uiStatusFlags & SOLDIER_ROBOT )
				{
					gfUIMouseOnValidCatcher = 3;
				}

				if ( !( uiCursorFlags & MOUSE_MOVING ) )
				{
					// Find adjacent gridno...
					sActionGridNo =  FindAdjacentGridEx( gpItemPointerSoldier, gusCurMousePos, &ubDirection, NULL, FALSE, FALSE );
					if ( sActionGridNo == -1 )
					{
						sActionGridNo = gusCurMousePos;
					}

					// Display location...
					gsUIHandleShowMoveGridLocation = sActionGridNo;
					gfUIHandleShowMoveGrid = TRUE;


					// Get AP cost
					if ( MercPtrs[ gusUIFullTargetID ]->flags.uiStatusFlags & SOLDIER_ROBOT )
					{
						sAPCost = GetAPsToReloadRobot( gpItemPointerSoldier, MercPtrs[ gusUIFullTargetID ] );
					}
					else
					{
						sAPCost = GetAPsToGiveItem( gpItemPointerSoldier, sActionGridNo );
					}

					gsCurrentActionPoints = sAPCost;
				}

				// Set value
				if ( gTacticalStatus.uiFlags & INCOMBAT )
				{
					gfUIDisplayActionPoints = TRUE;
					gUIDisplayActionPointsOffX = 15;
					gUIDisplayActionPointsOffY = 15;
				}
			}
		}


		if ( fGiveItem )
		{
			uiCursorId = CURSOR_ITEM_GIVE;
		}
		else
		{
			// How afar away are we?
			if ( sDist <= 1 && gfUIMouseOnValidCatcher == 0 )
			{
				// OK, we want to drop.....

				// Write the word 'drop' on cursor...
				wcscpy( gzIntTileLocation, pMessageStrings[ MSG_DROP ] );
				gfUIIntTileLocation = TRUE;
			}
			else
			{
				if ( sMapPos == gpItemPointerSoldier->sGridNo )
				{
					EndPhysicsTrajectoryUI( );
				}
        else if ( gfUIMouseOnValidCatcher == 4 )
        {
          // ATE: Don't do if we are passing....
        }
        else
				// ( sDist > PASSING_ITEM_DISTANCE_OKLIFE )
				{
					// Write the word 'drop' on cursor...
					if ( gfUIMouseOnValidCatcher == 0 )
					{
						wcscpy( gzIntTileLocation, pMessageStrings[ MSG_THROW ] );
						gfUIIntTileLocation = TRUE;
					}

					gfUIHandlePhysicsTrajectory = TRUE;

					if ( fRecalc && sMapPos != gpItemPointerSoldier->sGridNo )
					{
						if ( gfUIMouseOnValidCatcher )
						{
							switch( gAnimControl[ MercPtrs[ gubUIValidCatcherID ]->usAnimState ].ubHeight )
							{
								case ANIM_STAND:

									sEndZ = 150;
									break;

								case ANIM_CROUCH:

									sEndZ = 80;
									break;

								case ANIM_PRONE:

									sEndZ = 10;
									break;
							}

							if ( MercPtrs[ gubUIValidCatcherID ]->pathing.bLevel > 0 )
							{
								sEndZ = 0;
							}
						}

						// Calculate chance to throw here.....
						if ( !CalculateLaunchItemChanceToGetThrough( gpItemPointerSoldier, gpItemPointer, sMapPos, (INT8)gsInterfaceLevel, (INT16)( ( gsInterfaceLevel * 256 ) + sEndZ ), &sFinalGridNo, FALSE, &bLevel, TRUE ) )
						{
							gfBadThrowItemCTGH = TRUE;
						}
						else
						{
							gfBadThrowItemCTGH = FALSE;
						}

						BeginPhysicsTrajectoryUI( sFinalGridNo, bLevel, gfBadThrowItemCTGH );
					}
				}

				if ( gfBadThrowItemCTGH )
				{
					uiCursorId = CURSOR_ITEM_BAD_THROW;
				}
			}
		}

		//Erase any cursor in viewport
		//MSYS_ChangeRegionCursor( &gViewportRegion , VIDEO_NO_CURSOR );

		// Get tile graphic fro item
		usIndex = GetTileGraphicForItem( &(Item[ gpItemPointer->usItem ]) );

		// ONly load if different....
		if ( usIndex != gusItemPointer || uiOldCursorId != uiCursorId )
		{
			// OK, Tile database gives me subregion and video object to use...
			SetExternVOData( uiCursorId, gTileDatabase[ usIndex ].hTileSurface, gTileDatabase[ usIndex ].usRegionIndex );
			gusItemPointer = usIndex;
			uiOldCursorId = uiCursorId;
		}


		MSYS_ChangeRegionCursor( &gViewportRegion , (UINT16)uiCursorId );

	}
}


BOOLEAN IsValidAmmoToReloadRobot( SOLDIERTYPE *pSoldier, OBJECTTYPE *pObject )
{
	if ( !CompatibleAmmoForGun( pObject, &( pSoldier->inv[ HANDPOS ] ) ) )
	{
		// Build string...
		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[ ROBOT_NEEDS_GIVEN_CALIBER_STR ], AmmoCaliber[ Weapon[ pSoldier->inv[ HANDPOS ].usItem ].ubCalibre ] );

		return( FALSE );
	}

	return( TRUE );
}


BOOLEAN HandleItemPointerClick( INT16 sMapPos )
{
	// Determine what to do
	if ( SelectedGuyInBusyAnimation( ) )
	{
		return( FALSE );
	}

	if ( giUIMessageOverlay != -1 )
	{
		EndUIMessage( );
		return( FALSE );
	}

	// Don't allow if our soldier is a # of things...
	if ( AM_AN_EPC( gpItemPointerSoldier ) || gpItemPointerSoldier->stats.bLife < OKLIFE || gpItemPointerSoldier->MercInDeepWater( ) )
	{
		return( FALSE );
	}

	// This implies we have no path....
	if ( gsCurrentActionPoints == 0 )
	{
		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[ NO_PATH ] );
		return( FALSE );
	}


	UINT8 ubDirection;
	UINT8	ubSoldierID;
	UINT16	  usItem;
	INT16			sAPCost;
	SOLDIERTYPE		*pSoldier=NULL;
	UINT8			ubThrowActionCode=0;
	UINT32		uiThrowActionData=0;
	INT16			sEndZ = 0;
	BOOLEAN		fGiveItem = FALSE;
	INT16			sGridNo;
	INT16			sDist;

	if ( gfUIFullTargetFound )
	{
		// Force mouse position to guy...
		sMapPos = MercPtrs[ gusUIFullTargetID ]->sGridNo;

		if ( gAnimControl[ MercPtrs[ gusUIFullTargetID ]->usAnimState ].uiFlags & ANIM_MOVING )
		{
			return( FALSE );
		}

	}

	// Check if we have APs....
	if ( !EnoughPoints( gpItemPointerSoldier, gsCurrentActionPoints, 0, TRUE ) )
	{
		if ( gfDontChargeAPsToPickup && gsCurrentActionPoints == AP_PICKUP_ITEM )
		{

		}
		else
		{
			return( FALSE );
		}
	}

	// SEE IF WE ARE OVER A TALKABLE GUY!
	if ( IsValidTalkableNPCFromMouse( &ubSoldierID, TRUE, FALSE, TRUE ) )
	{
		fGiveItem = TRUE;
	}

	// WANNE: Prevent duplication of items cheat-bug:
	// You need two mercenaries. You place required item to first mercenary's inventory, 
	// then you take the item and point cursor with the item at the second mercenary. 
	// Then you click right mouse button and then left one. 
	// During the process of giving the item from the first mercenary to the second quicly move the item to the another slot of the inventory. 
	// As a result of it the item will be given to the second mercenary and the first mercenary will still have it.
	// OK, if different than default, change....
	//if ( gfItemPointerDifferentThanDefault )
	//{
	//	fGiveItem = !fGiveItem;
	//}


	// Get Pyth spaces away.....
	sDist = PythSpacesAway( gpItemPointerSoldier->sGridNo, gusCurMousePos );


	if ( fGiveItem )
	{
		usItem = gpItemPointer->usItem;

		// If the target is a robot,
		if ( MercPtrs[ ubSoldierID ]->flags.uiStatusFlags & SOLDIER_ROBOT )
		{
			// Charge APs to reload robot!
			sAPCost = GetAPsToReloadRobot( gpItemPointerSoldier,  MercPtrs[ ubSoldierID ] );
		}
		else
		{
			// Calculate action point costs!
			sAPCost = GetAPsToGiveItem( gpItemPointerSoldier, sMapPos );
		}

		// Place it back in our hands!

		gTempObject = *gpItemPointer;

		if ( gbItemPointerSrcSlot != NO_SLOT )
		{
			PlaceObject( gpItemPointerSoldier, gbItemPointerSrcSlot, gpItemPointer );
			fInterfacePanelDirty = DIRTYLEVEL2;
		}
/*
		//if the user just clicked on an arms dealer
		if( IsMercADealer( MercPtrs[ ubSoldierID ]->ubProfile ) )
		{
			if ( EnoughPoints( gpItemPointerSoldier, sAPCost, 0, TRUE ) )
			{
				//Enter the shopkeeper interface
				EnterShopKeeperInterfaceScreen( MercPtrs[ ubSoldierID ]->ubProfile );

				EndItemPointer( );
			}

			return( TRUE );
		}
*/

		if ( EnoughPoints( gpItemPointerSoldier, sAPCost, 0, TRUE ) )
		{
			// If we are a robot, check if this is proper item to reload!
			if ( MercPtrs[ ubSoldierID ]->flags.uiStatusFlags & SOLDIER_ROBOT )
			{
				// Check if we can reload robot....
				if ( IsValidAmmoToReloadRobot( MercPtrs[ ubSoldierID ], &gTempObject ) )
				{
					 INT16	sActionGridNo;
					 UINT8	ubDirection;
					 INT16	sAdjustedGridNo;

					 // Walk up to him and reload!
					 // See if we can get there to stab
					 sActionGridNo =  FindAdjacentGridEx( gpItemPointerSoldier, MercPtrs[ ubSoldierID ]->sGridNo, &ubDirection, &sAdjustedGridNo, TRUE, FALSE );

					 if ( sActionGridNo != -1 && gbItemPointerSrcSlot != NO_SLOT )
					 {
							// Make a temp object for ammo...
							OBJECTTYPE::CopyToOrCreateAt( &gpItemPointerSoldier->pTempObject, &gTempObject);

							// Remove from soldier's inv...
							gpItemPointerSoldier->inv[ gbItemPointerSrcSlot ].RemoveObjectsFromStack(1);

							gpItemPointerSoldier->aiData.sPendingActionData2  = sAdjustedGridNo;
							gpItemPointerSoldier->aiData.uiPendingActionData1 = gbItemPointerSrcSlot;
							gpItemPointerSoldier->aiData.bPendingActionData3  = ubDirection;
							gpItemPointerSoldier->aiData.ubPendingActionAnimCount = 0;

							// CHECK IF WE ARE AT THIS GRIDNO NOW
							if ( gpItemPointerSoldier->sGridNo != sActionGridNo )
							{
								// SEND PENDING ACTION
								gpItemPointerSoldier->aiData.ubPendingAction = MERC_RELOADROBOT;

								// WALK UP TO DEST FIRST
								gpItemPointerSoldier->EVENT_InternalGetNewSoldierPath( sActionGridNo, gpItemPointerSoldier->usUIMovementMode, FALSE, FALSE );
							}
							else
							{
								gpItemPointerSoldier->EVENT_SoldierBeginReloadRobot( sAdjustedGridNo, ubDirection, gbItemPointerSrcSlot );
							}

							// OK, set UI
							SetUIBusy( gpItemPointerSoldier->ubID );
					 }

				}

				gfDontChargeAPsToPickup = FALSE;
				EndItemPointer( );
			}
			else
			{
				//if (gbItemPointerSrcSlot != NO_SLOT )
				{
					// Give guy this item.....
					SoldierGiveItem( gpItemPointerSoldier, MercPtrs[ ubSoldierID ], &gTempObject, gbItemPointerSrcSlot );

					gfDontChargeAPsToPickup = FALSE;
					EndItemPointer( );

					// If we are giving it to somebody not on our team....
					if ( MercPtrs[ ubSoldierID ]->ubProfile < FIRST_RPC || MercPtrs[ubSoldierID]->ubProfile >= GASTON || RPC_RECRUITED( MercPtrs[ ubSoldierID ] ) )
					{

					}
					else
					{
						SetEngagedInConvFromPCAction( gpItemPointerSoldier );
					}
				}
			}
		}

		return( TRUE );
	}

	// CHECK IF WE ARE NOT ON THE SAME GRIDNO
	if ( sDist <= 1 && !( gfUIFullTargetFound && gusUIFullTargetID != gpItemPointerSoldier->ubID ) )
	{
		// Check some things here....
		// 1 ) are we at the exact gridno that we stand on?
		if ( sMapPos == gpItemPointerSoldier->sGridNo )
		{
			// Drop
			if ( !gfDontChargeAPsToPickup )
			{
				// Deduct points
				DeductPoints( gpItemPointerSoldier, AP_PICKUP_ITEM, 0 );
			}

			SoldierDropItem( gpItemPointerSoldier, gpItemPointer );
		}
		else
		{
			// Try to drop in an adjacent area....
			// 1 ) is this not a good OK destination
			// this will sound strange, but this is OK......
			if ( !NewOKDestination( gpItemPointerSoldier, sMapPos, FALSE, gpItemPointerSoldier->pathing.bLevel ) || FindBestPath( gpItemPointerSoldier, sMapPos, gpItemPointerSoldier->pathing.bLevel, WALKING, NO_COPYROUTE, 0 ) == 1 )
			{
				// Drop
				if ( !gfDontChargeAPsToPickup )
				{
					// Deduct points
					DeductPoints( gpItemPointerSoldier, AP_PICKUP_ITEM, 0 );
				}

				// Play animation....
				// Don't show animation of dropping item, if we are not standing



				switch ( gAnimControl[ gpItemPointerSoldier->usAnimState ].ubHeight )
				{
					case ANIM_STAND:

						OBJECTTYPE::CopyToOrCreateAt( &gpItemPointerSoldier->pTempObject, gpItemPointer);
						if (gpItemPointerSoldier->pTempObject != NULL)
						{
							gpItemPointerSoldier->aiData.sPendingActionData2 = sMapPos;

	 						// Turn towards.....gridno
							gpItemPointerSoldier->EVENT_SetSoldierDesiredDirection( (INT8)GetDirectionFromGridNo( sMapPos, gpItemPointerSoldier ) );

							gpItemPointerSoldier->EVENT_InitNewSoldierAnim( DROP_ADJACENT_OBJECT, 0 , FALSE );
						}
						break;

					case ANIM_CROUCH:
					case ANIM_PRONE:

						AddItemToPool( sMapPos, gpItemPointer, 1, gpItemPointerSoldier->pathing.bLevel, 0 , -1 );
						NotifySoldiersToLookforItems( );
						break;
				}
			}
			else
			{
				// Drop in place...
				if ( !gfDontChargeAPsToPickup )
				{
					// Deduct points
					DeductPoints( gpItemPointerSoldier, AP_PICKUP_ITEM, 0 );
				}

				SoldierDropItem( gpItemPointerSoldier, gpItemPointer );
			}
		}
	}
	else
	{
		sGridNo = sMapPos;

		// Kaiden: Vehicle Inventory change - Commented the following If test:
		//if ( sDist <= PASSING_ITEM_DISTANCE_OKLIFE && gfUIFullTargetFound && MercPtrs[ gusUIFullTargetID ]->bTeam == gbPlayerNum && !AM_AN_EPC( MercPtrs[ gusUIFullTargetID ] ) && !( MercPtrs[ gusUIFullTargetID ]->flags.uiStatusFlags & SOLDIER_VEHICLE ) )

		// And added this one instead:
		if ( ( sDist <= PASSING_ITEM_DISTANCE_OKLIFE && gfUIFullTargetFound && MercPtrs[ gusUIFullTargetID ]->bTeam == gbPlayerNum && !AM_AN_EPC( MercPtrs[ gusUIFullTargetID ] ) ) && !( (!gGameExternalOptions.fVehicleInventory) && (MercPtrs[ gusUIFullTargetID ]->flags.uiStatusFlags & SOLDIER_VEHICLE) ) )
		{
			// OK, do the transfer...
			{
				pSoldier = MercPtrs[ gusUIFullTargetID ];

				{
					// Change to inventory....
					//gfSwitchPanel = TRUE;
					//gbNewPanel = SM_PANEL;
					//gubNewPanelParam = (UINT8)pSoldier->ubID;
					if ( !EnoughPoints( pSoldier, 3, 0, TRUE ) ||
							 !EnoughPoints( gpItemPointerSoldier, 3, 0, TRUE ) )
					{
						return( FALSE );
					}

					// Check LOS....
					if ( !SoldierTo3DLocationLineOfSightTest( pSoldier, gpItemPointerSoldier->sGridNo,  gpItemPointerSoldier->pathing.bLevel, 3, TRUE, CALC_FROM_ALL_DIRS ) )
					{
						return( FALSE );
					}

					// Charge AP values...
					DeductPoints( pSoldier, 3, 0 );
					DeductPoints( gpItemPointerSoldier, 3, 0 );

					usItem = gpItemPointer->usItem;

					// try to auto place object....
					if ( AutoPlaceObject( pSoldier, gpItemPointer, TRUE ) )
					{
						ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[ MSG_ITEM_PASSED_TO_MERC ], ShortItemNames[ usItem ], pSoldier->name );

						// Check if it's the same now!
						if ( gpItemPointer->exists() == false )
						{
							EndItemPointer( );
						}

	    			// OK, make guys turn towards each other and do animation...
			  		{
						  UINT8	ubFacingDirection;

						  // Get direction to face.....
						  ubFacingDirection = (UINT8)GetDirectionFromGridNo( gpItemPointerSoldier->sGridNo, pSoldier );

						  // Stop merc first....
						  pSoldier->EVENT_StopMerc( pSoldier->sGridNo, pSoldier->ubDirection );

						  // WANNE: Also turn merc if he is crouched and he passes an item
						  if ( !pSoldier->MercInWater( ) )
						  {
							  // Turn to face, then do animation....
							  pSoldier->EVENT_SetSoldierDesiredDirection( ubFacingDirection );
							  pSoldier->flags.fTurningUntilDone	 = TRUE;

							 if (gAnimControl[ pSoldier->usAnimState ].ubEndHeight == ANIM_STAND)
							 {
							  pSoldier->usPendingAnimation = PASS_OBJECT;
              }
						 }

						  // WANNE: Also turn merc if he is crouched and he received the passed item
						  if ( !gpItemPointerSoldier->MercInWater(  ) )
						  {
							  gpItemPointerSoldier->EVENT_SetSoldierDesiredDirection( gOppositeDirection[ ubFacingDirection ] );
							  gpItemPointerSoldier->flags.fTurningUntilDone	 = TRUE;

							  if (gAnimControl[ gpItemPointerSoldier->usAnimState ].ubEndHeight == ANIM_STAND)
							  {
							  gpItemPointerSoldier->usPendingAnimation = PASS_OBJECT;
						  }
					  }
					  }

						return( TRUE );
					}
					else
					{
						ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[ MSG_NO_ROOM_TO_PASS_ITEM ], ShortItemNames[ usItem ], pSoldier->name );
  					return( FALSE );
					}
				}
			}
		}
		else
		{
			// CHECK FOR VALID CTGH
			if ( gfBadThrowItemCTGH )
			{
				ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[ CANNOT_THROW_TO_DEST_STR ] );
				return( FALSE );
			}

			// Deduct points
			//DeductPoints( gpItemPointerSoldier, AP_TOSS_ITEM, 0 );
			gpItemPointerSoldier->flags.fDontChargeTurningAPs = TRUE;
			// Will be dome later....

			ubThrowActionCode = NO_THROW_ACTION;

			// OK, CHECK FOR VALID THROW/CATCH
			// IF OVER OUR GUY...
			if ( gfUIFullTargetFound )
			{
				pSoldier = MercPtrs[ gusUIFullTargetID ];

				// Kaiden: Vehicle Inventory change - Commented the following If Test:
				//if ( pSoldier->bTeam == gbPlayerNum && pSoldier->stats.bLife >= OKLIFE && !AM_AN_EPC( pSoldier ) && !( pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE ) )

				// And replaced it with this one:
				if ( ( pSoldier->bTeam == gbPlayerNum && pSoldier->stats.bLife >= OKLIFE && !AM_AN_EPC( pSoldier ) ) && !( ( !gGameExternalOptions.fVehicleInventory ) &&  ( pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE ) ) )
				{
					// OK, on our team,

					// How's our direction?
					if ( SoldierCanSeeCatchComing( pSoldier, gpItemPointerSoldier->sGridNo ) )
					{
						// Setup as being the catch target
						ubThrowActionCode = THROW_TARGET_MERC_CATCH;
						uiThrowActionData = pSoldier->ubID;

						sGridNo = pSoldier->sGridNo;

						switch( gAnimControl[ pSoldier->usAnimState ].ubHeight )
						{
								case ANIM_STAND:

									sEndZ = 150;
									break;

								case ANIM_CROUCH:

									sEndZ = 80;
									break;

								case ANIM_PRONE:

									sEndZ = 10;
									break;
						}

						if ( pSoldier->pathing.bLevel > 0 )
						{
							sEndZ = 0;
						}

						// Get direction
						ubDirection = (UINT8)GetDirectionFromGridNo( gpItemPointerSoldier->sGridNo, pSoldier );

						// ATE: Goto stationary...
						pSoldier->SoldierGotoStationaryStance( );

						// Set direction to turn...
						pSoldier->EVENT_SetSoldierDesiredDirection( ubDirection );

					}
				}
			}


			// CHANGE DIRECTION AT LEAST
			ubDirection = (UINT8)GetDirectionFromGridNo( sGridNo, gpItemPointerSoldier );
			gpItemPointerSoldier->EVENT_SetSoldierDesiredDirection( ubDirection );
			gpItemPointerSoldier->flags.fTurningUntilDone = TRUE;

			// Increment attacker count...
			// gTacticalStatus.ubAttackBusyCount++;
			DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String("Incremtning ABC: Throw item to %d", gTacticalStatus.ubAttackBusyCount) );
			DebugAttackBusy( "Incrementing ABC: Throw item\n" );


			// Given our gridno, throw grenate!
			CalculateLaunchItemParamsForThrow( gpItemPointerSoldier, sGridNo, gpItemPointerSoldier->pathing.bLevel, (INT16)( ( gsInterfaceLevel * 256 ) + sEndZ ), gpItemPointer, 0, ubThrowActionCode, uiThrowActionData );

			// OK, goto throw animation
			HandleSoldierThrowItem( gpItemPointerSoldier, sMapPos );
		}
	}

	gfDontChargeAPsToPickup = FALSE;
	EndItemPointer( );


	return( TRUE );
}

BOOLEAN ItemCursorInLobRange( INT16 sMapPos )
{
	// Draw item depending on distance from buddy
	if ( GetRangeFromGridNoDiff( sMapPos, gpItemPointerSoldier->sGridNo ) > MIN_LOB_RANGE )
	{
		return( FALSE );
	}
	else
	{
		return( TRUE );
	}
}



BOOLEAN InSectorStackPopup( )
{
	return( gfInSectorStackPopup );
}

BOOLEAN InItemStackPopup( )
{
	return( gfInItemStackPopup );
}

BOOLEAN InKeyRingPopup( )
{
	return( gfInKeyRingPopup );
}

BOOLEAN InitSectorStackPopup( WORLDITEM *pInventoryPoolList, INT32 ubPosition, INT16 sInvX, INT16 sInvY, INT16 sInvWidth, INT16 sInvHeight )
{
	VOBJECT_DESC    VObjectDesc;
	SGPRect			aRect;
	ETRLEObject		*pTrav;
	HVOBJECT		hVObject;
	INT32			cnt;
	UINT16			usPopupWidth, usPopupHeight;
	INT16			sOffSetY = 0, sOffSetX = 0;
	INT16			sItemWidth = 0;
	static CHAR16	pStr[ 512 ];

	sItemWidth				= MAP_INV_ITEM_ROW_WIDTH - 1;
	sOffSetY				= 120;

	// Set some globals
	guiCurrentItemDescriptionScreen = guiCurrentScreen;
	gsItemPopupInvX			= sInvX;
	gsItemPopupInvY			= sInvY;
	gsItemPopupInvWidth		= sInvWidth;
	gsItemPopupInvHeight	= sInvHeight;
	// Determine # of items
	gpItemPopupObject		= &(pInventoryPoolList->object );
	gubNumItemPopups		= ItemSlotLimit( gpItemPopupObject, STACK_SIZE_LIMIT );

	// Return false if #objects not >1
	if ( gubNumItemPopups <1 )
		return( FALSE );

	// Load graphics
	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	strcpy( VObjectDesc.ImageFile, "INTERFACE\\extra_inventory.STI" );
	CHECKF( AddVideoObject( &VObjectDesc, &guiItemPopupBoxes) );

	// Get size
	GetVideoObject( &hVObject, guiItemPopupBoxes );
	pTrav = &(hVObject->pETRLEObject[ 0 ] );
	usPopupWidth = 75;
	//usPopupWidth = pTrav->usWidth;
	usPopupHeight = pTrav->usHeight;

	// Get Width, Height
	gsItemPopupWidth		= gubNumItemPopups * usPopupWidth;
	gsItemPopupHeight		= pTrav->usHeight;
	gsItemPopupX			= gsItemPopupInvX;
	gsItemPopupY			= gsItemPopupInvY;

	for ( cnt = 0; cnt < gubNumItemPopups; cnt++ )
	{
		// Build a mouse region here that is over any others.....
		MSYS_DefineRegion( &gItemPopupRegions[cnt],
				(INT16)( gsItemPopupInvX + ( cnt % sItemWidth * usPopupWidth ) + sOffSetX ), // top left
				(INT16)( sInvY + sOffSetY +( cnt / sItemWidth * usPopupHeight ) ), // top right
				(INT16)( gsItemPopupInvX + ( ( cnt % sItemWidth ) + 1 ) * usPopupWidth + sOffSetX ), // bottom left
				(INT16)( sInvY + ( (cnt / sItemWidth + 1) * usPopupHeight ) + sOffSetY ), // bottom right
				MSYS_PRIORITY_HIGHEST,
				MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemPopupRegionCallback );
		// Add region
		MSYS_AddRegion( &gItemPopupRegions[cnt]);
		MSYS_SetRegionUserData( &gItemPopupRegions[cnt], 0, cnt );
		//CHRISL: Include the pockets capacity as UserData 1
		MSYS_SetRegionUserData( &gItemPopupRegions[cnt], 1, gubNumItemPopups );
		// Flag this as a sectory item
		MSYS_SetRegionUserData( &gItemPopupRegions[cnt], 2, -1);
		//CHRISL: Include the pocket we're looking at so we can display the right graphic
		MSYS_SetRegionUserData( &gItemPopupRegions[cnt], 3, ubPosition);
		
		//OK, for each item, set dirty text if applicable!
		//CHRISL:
		if(cnt < gpItemPopupObject->ubNumberOfObjects && gpItemPopupObject->exists() == true){
			GetHelpTextForItem( pStr, gpItemPopupObject, 0, cnt );
			SetRegionFastHelpText( &(gItemPopupRegions[ cnt ]), pStr );
		}
		else{
			SetRegionFastHelpText( &(gItemPopupRegions[ cnt ]), ItemNames[ gpItemPopupObject->usItem ] );
		}
		SetRegionHelpEndCallback( &(gItemPopupRegions[ cnt ]), HelpTextDoneCallback );
		gfItemPopupRegionCallbackEndFix = FALSE;
	}


	// Build a mouse region here that is over any others.....
	MSYS_DefineRegion( &gItemPopupRegion, sInvX, sInvY ,(INT16)(sInvX + sInvWidth), (INT16)(sInvY + sInvHeight), MSYS_PRIORITY_HIGH,
						 MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemPopupFullRegionCallback );
	// Add region
	MSYS_AddRegion( &gItemPopupRegion);

	//Disable all faces
	SetAllAutoFacesInactive( );

	fInterfacePanelDirty = DIRTYLEVEL2;

	gfInSectorStackPopup = TRUE;
	fShowInventoryFlag = TRUE;

	//Reserict mouse cursor to panel
	aRect.iLeft = sInvX + sOffSetX;
	aRect.iTop = sInvY + sOffSetY;
	aRect.iRight = aRect.iLeft + sItemWidth * usPopupWidth;
	aRect.iBottom = aRect.iTop + (INT32)(ceil((float)cnt/(float)sItemWidth)+1) * usPopupHeight;

	RestrictMouseCursor( &aRect );

	return( TRUE );
}

BOOLEAN InitItemStackPopup( SOLDIERTYPE *pSoldier, UINT8 ubPosition, INT16 sInvX, INT16 sInvY, INT16 sInvWidth, INT16 sInvHeight )
{
	VOBJECT_DESC    VObjectDesc;
	SGPRect			aRect;
	ETRLEObject		*pTrav;
	HVOBJECT		hVObject;
	INT32			cnt;
	UINT16			usPopupWidth, usPopupHeight;
	INT16			sOffSetY = 0, sOffSetX = 0;
	INT16			sItemWidth = 0;
	static CHAR16	pStr[ 512 ];

	
	RenderBackpackButtons(1);	/* CHRISL: Needed for new inventory backpack buttons */
	if( guiCurrentScreen == MAP_SCREEN )
	{
		sItemWidth						= MAP_INV_ITEM_ROW_WIDTH;
		sOffSetY						= 120;
	}
	else
	{
		sItemWidth						= INV_ITEM_ROW_WIDTH;
	}

	// Set some globals
	gsItemPopupInvX					= sInvX;
	gsItemPopupInvY					= sInvY;
	gsItemPopupInvWidth				= sInvWidth;
	gsItemPopupInvHeight			= sInvHeight;

	gpItemPopupSoldier = pSoldier;

	// Determine # of items
	gpItemPopupObject = &(pSoldier->inv[ ubPosition ] );
	// CHRISL:
	gubNumItemPopups = ItemSlotLimit( gpItemPopupObject, ubPosition, pSoldier );

	// Return false if #objects not >1
	if ( gubNumItemPopups <1 )
	{
		return( FALSE );
	}

	// Load graphics
	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	strcpy( VObjectDesc.ImageFile, "INTERFACE\\extra_inventory.STI" );
	CHECKF( AddVideoObject( &VObjectDesc, &guiItemPopupBoxes) );

	if(UsingNewInventorySystem() == true)
	{
		VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
		strcpy( VObjectDesc.ImageFile, "INTERFACE\\infobox_background.sti" );
		CHECKF( AddVideoObject( &VObjectDesc, &guiItemDescBoxBackground) );
	}
	else
		guiItemDescBoxBackground = 0;

	// Get size
	GetVideoObject( &hVObject, guiItemPopupBoxes );
	pTrav = &(hVObject->pETRLEObject[ 0 ] );
	usPopupWidth = pTrav->usWidth;
	usPopupHeight = pTrav->usHeight;

	//CHRISL: resize usPopupWidth based on popup stack location
	if(UsingNewInventorySystem() == true)
	{
		if((ubPosition >=BIGPOCKSTART && ubPosition < BIGPOCKFINAL) || (gGameExternalOptions.fVehicleInventory && (pSoldier->flags.uiStatusFlags & SOLDIER_VEHICLE)))
		{
			usPopupWidth = 75;
			if(guiCurrentScreen != MAP_SCREEN)
				sItemWidth -= 2;
			else if(guiCurrentScreen == MAP_SCREEN)
				sItemWidth -= 1;
		}
		else if(ubPosition >=MEDPOCKSTART && ubPosition < MEDPOCKFINAL)
		{
			usPopupWidth = 58;
			if(guiCurrentScreen != MAP_SCREEN)
				sItemWidth -= 1;
		}
	}

	// Determine position, height and width of mouse region, area
	//GetSlotInvXY( ubPosition, &sX, &sY );
	//GetSlotInvHeightWidth( ubPosition, &sItemSlotWidth, &sItemSlotHeight );

	// Get Width, Height
	gsItemPopupWidth	= gubNumItemPopups * usPopupWidth;
	gsItemPopupHeight = pTrav->usHeight;

	gsItemPopupX	= gsItemPopupInvX;
	gsItemPopupY	= gsItemPopupInvY;

	for ( cnt = 0; cnt < gubNumItemPopups; cnt++ )
	{
//				(INT16)( gsItemPopupInvX + ( cnt % gsItemPopupInvWidth * usPopupWidth ) + sOffSetX ), // top left
//				(INT16)( sInvY + sOffSetY +( cnt / gsItemPopupInvWidth * usPopupHeight ) ), // top right
//				(INT16)( gsItemPopupInvX + ( ( cnt % gsItemPopupInvWidth ) + 1 ) * usPopupWidth + sOffSetX ), // bottom left
//				(INT16)( sInvY + ( (cnt / gsItemPopupInvWidth + 1) * usPopupHeight ) + sOffSetY ), // bottom right
//		sX = (INT16)(gsItemPopupX + ( cnt % sItemWidth * usWidth ));
//		sY = (INT16)(gsItemPopupY + sOffSetY + ( cnt / sItemWidth * usHeight ));
		// Build a mouse region here that is over any others.....
		MSYS_DefineRegion( &gItemPopupRegions[cnt],
				(INT16)( gsItemPopupInvX + ( cnt % sItemWidth * usPopupWidth ) + sOffSetX ), // top left
				(INT16)( sInvY + sOffSetY +( cnt / sItemWidth * usPopupHeight ) ), // top right
				(INT16)( gsItemPopupInvX + ( ( cnt % sItemWidth ) + 1 ) * usPopupWidth + sOffSetX ), // bottom left
				(INT16)( sInvY + ( (cnt / sItemWidth + 1) * usPopupHeight ) + sOffSetY ), // bottom right
				MSYS_PRIORITY_HIGHEST,
				MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemPopupRegionCallback );
		// Add region
		MSYS_AddRegion( &gItemPopupRegions[cnt]);
		MSYS_SetRegionUserData( &gItemPopupRegions[cnt], 0, cnt );
		//CHRISL: Include the pockets capacity as UserData 1
		int cap = ItemSlotLimit( &pSoldier->inv[ubPosition], ubPosition, pSoldier );
		MSYS_SetRegionUserData( &gItemPopupRegions[cnt], 1, cap );
		//CHRISL: Let's also include the ubID for this merc as UserData so we can find the merc again if needed
		MSYS_SetRegionUserData( &gItemPopupRegions[cnt], 2, pSoldier->ubID);
		//CHRISL: Also include the pocket we're looking at so we can display the right graphic
		MSYS_SetRegionUserData( &gItemPopupRegions[cnt], 3, ubPosition);
		
		//OK, for each item, set dirty text if applicable!
		//CHRISL:
		if(cnt < pSoldier->inv[ubPosition].ubNumberOfObjects && pSoldier->inv[ubPosition].exists() == true){
			GetHelpTextForItem( pStr, &( pSoldier->inv[ ubPosition ] ), pSoldier, cnt );
			SetRegionFastHelpText( &(gItemPopupRegions[ cnt ]), pStr );
		}
		else{
			SetRegionFastHelpText( &(gItemPopupRegions[ cnt ]), ItemNames[ pSoldier->inv[ ubPosition ].usItem ] );
		}
		SetRegionHelpEndCallback( &(gItemPopupRegions[ cnt ]), HelpTextDoneCallback );
		gfItemPopupRegionCallbackEndFix = FALSE;
	}


	// Build a mouse region here that is over any others.....
	MSYS_DefineRegion( &gItemPopupRegion, sInvX, sInvY ,(INT16)(sInvX + sInvWidth), (INT16)(sInvY + sInvHeight), MSYS_PRIORITY_HIGH,
						 MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemPopupFullRegionCallback );
	// Add region
	MSYS_AddRegion( &gItemPopupRegion);


	//Disable all faces
	SetAllAutoFacesInactive( );


	fInterfacePanelDirty = DIRTYLEVEL2;

	//guiTacticalInterfaceFlags |= INTERFACE_NORENDERBUTTONS;


//	if ( !(guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
	if( guiCurrentItemDescriptionScreen != MAP_SCREEN )
	{
		EnableSMPanelButtons( FALSE, FALSE );
	}

	gfInItemStackPopup = TRUE;

	//Reserict mouse cursor to panel
	aRect.iLeft = sInvX + sOffSetX;
	aRect.iTop = sInvY + sOffSetY;
	aRect.iRight = aRect.iLeft + sItemWidth * usPopupWidth;
	aRect.iBottom = aRect.iTop + (INT32)(ceil((float)cnt/(float)sItemWidth)+1) * usPopupHeight;
	//aRect.iTop = sInvY;
	//aRect.iLeft = sInvX;
	//aRect.iBottom = sInvY + sInvHeight;
	//aRect.iRight = sInvX + sInvWidth;

	RestrictMouseCursor( &aRect );

	return( TRUE );
}

void EndItemStackPopupWithItemInHand( )
{
	if ( gpItemPointer != NULL )
	{
		DeleteItemStackPopup( );
	}
}

void RenderItemStackPopup( BOOLEAN fFullRender )
{
  ETRLEObject						*pTrav;
	UINT32								usHeight, usWidth;
	HVOBJECT							hVObject;
	UINT32								cnt;
	INT16									sX, sY, sNewX, sNewY;
	INT16			sItemWidth = 0, sOffSetY = 0, sWidth = 29;
	UINT8			ubPosition, image = 0;
	int				sID;

	// CHRISL: Setup witdh and offset to layer inventory boxes if necessary
	if( guiCurrentScreen == MAP_SCREEN )
	{
		sItemWidth						= MAP_INV_ITEM_ROW_WIDTH;
		sOffSetY						= 120;
	}
	else
	{
		sItemWidth						= INV_ITEM_ROW_WIDTH;
	}

	if ( gfInItemStackPopup )
	{

		//Disable all faces
		SetAllAutoFacesInactive( );

		// Shadow Area
		if ( fFullRender )
		{
			if(UsingNewInventorySystem() == false || guiCurrentScreen == MAP_SCREEN)
				ShadowVideoSurfaceRect( FRAME_BUFFER, gsItemPopupInvX, gsItemPopupInvY, gsItemPopupInvX + gsItemPopupInvWidth , gsItemPopupInvY + gsItemPopupInvHeight  );
			else if(UsingNewInventorySystem() == true && iResolution != 0 && guiItemDescBoxBackground != 0 && guiCurrentScreen != MAP_SCREEN)
				BltVideoObjectFromIndex( FRAME_BUFFER, guiItemDescBoxBackground, iResolution, SM_ITEMDESC_START_X, SM_ITEMDESC_START_Y, VO_BLT_SRCTRANSPARENCY, NULL );
		}

	}
	//CHRISL: Get ubPosition from mouse region
	sID = MSYS_GetRegionUserData(&gItemPopupRegions[0], 2);
	ubPosition = MSYS_GetRegionUserData(&gItemPopupRegions[0], 3);
	// TAKE A LOOK AT THE VIDEO OBJECT SIZE ( ONE OF TWO SIZES ) AND CENTER!
	GetVideoObject( &hVObject, guiItemPopupBoxes );
	pTrav = &(hVObject->pETRLEObject[ 0 ] );
	usHeight				= (UINT32)pTrav->usHeight;
	usWidth					= (UINT32)pTrav->usWidth;

	//CHRISL: resize usPopupWidth based on popup stack location
	if(UsingNewInventorySystem() == true || sID == -1)
	{
		if(sID == -1 || (ubPosition >=BIGPOCKSTART && ubPosition < BIGPOCKFINAL) || (gGameExternalOptions.fVehicleInventory && (MercPtrs[sID]->flags.uiStatusFlags & SOLDIER_VEHICLE)))
		{
			if(guiCurrentScreen != MAP_SCREEN)
				sItemWidth -= 2;
			else if(guiCurrentScreen == MAP_SCREEN)
				sItemWidth -= 1;
			usWidth = 75;
			sWidth = 60;
			image = 2;
		}
		else if(ubPosition >=MEDPOCKSTART && ubPosition < MEDPOCKFINAL)
		{
			if(guiCurrentScreen != MAP_SCREEN)
				sItemWidth -= 1;
			usWidth = 58;
			sWidth = 43;
			image = 1;
		}
	}

	for ( cnt = 0; cnt < gubNumItemPopups; cnt++ )
	{
		// CHRISL: Layer item boxes if we have too many to display in a single row
		//BltVideoObjectFromIndex( FRAME_BUFFER, guiItemPopupBoxes, 0, gsItemPopupX + ( cnt * usWidth ), gsItemPopupY, VO_BLT_SRCTRANSPARENCY, NULL );
		sX = (INT16)(gsItemPopupX + ( cnt % sItemWidth * usWidth ));
		sY = (INT16)(gsItemPopupY + sOffSetY + ( cnt / sItemWidth * usHeight ));
		BltVideoObjectFromIndex( FRAME_BUFFER, guiItemPopupBoxes, image, (INT16)sX, ( INT16 )sY, VO_BLT_SRCTRANSPARENCY, NULL );

		if ( cnt < gpItemPopupObject->ubNumberOfObjects )
		{
			// CHRISL: Coord updates to work with mutliple rows
			//sX = (INT16)(gsItemPopupX + ( cnt * usWidth ) + 11);
			//sY = (INT16)( gsItemPopupY + 3 );

			INVRenderItem( FRAME_BUFFER, NULL, gpItemPopupObject, sX+11, sY+3, sWidth, 23, DIRTYLEVEL2, NULL, (UINT8)RENDER_ITEM_NOSTATUS, FALSE, 0, cnt );

			// CHRISL: Coord updates to work with mutliple rows
			// Do status bar here...
			sNewX = (INT16)( gsItemPopupX + ( cnt * usWidth ) + 7 );
			sNewY = gsItemPopupY + INV_BAR_DY + 3;
			DrawItemUIBarEx( gpItemPopupObject, (UINT8)cnt, sX+7, sY+INV_BAR_DY+3, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT, Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , FRAME_BUFFER, cnt );

		}
	}

	//RestoreExternBackgroundRect( gsItemPopupInvX, gsItemPopupInvY, gsItemPopupInvWidth, gsItemPopupInvHeight );
	InvalidateRegion( gsItemPopupInvX, gsItemPopupInvY, gsItemPopupInvX + gsItemPopupInvWidth, gsItemPopupInvY + gsItemPopupInvHeight );

}

void HandleItemStackPopup( )
{

}


void DeleteItemStackPopup( )
{
	INT32			cnt;

	//Remove
	DeleteVideoObjectFromIndex( guiItemPopupBoxes );

	MSYS_RemoveRegion( &gItemPopupRegion);


	gfInItemStackPopup = FALSE;
	gfInSectorStackPopup = FALSE;

	for ( cnt = 0; cnt < gubNumItemPopups; cnt++ )
	{
		MSYS_RemoveRegion( &gItemPopupRegions[cnt]);
	}


	fInterfacePanelDirty = DIRTYLEVEL2;

	//guiTacticalInterfaceFlags &= (~INTERFACE_NORENDERBUTTONS);

//	if ( !(guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
	if( guiCurrentItemDescriptionScreen != MAP_SCREEN )
	{
		EnableSMPanelButtons( TRUE, FALSE );
	}

	FreeMouseCursor( );

}


BOOLEAN InitKeyRingPopup( SOLDIERTYPE *pSoldier, INT16 sInvX, INT16 sInvY, INT16 sInvWidth, INT16 sInvHeight )
{
	VOBJECT_DESC    VObjectDesc;
	SGPRect			aRect;
	ETRLEObject		*pTrav;
	HVOBJECT		hVObject;
	INT32			cnt;
	UINT16			usPopupWidth, usPopupHeight;
	INT16			sOffSetY = 0, sOffSetX = 0;
	INT16			sKeyRingItemWidth = 0;

	RenderBackpackButtons(1);	/* CHRISL: Needed for new inventory backpack buttons */
	if( guiCurrentScreen == MAP_SCREEN )
	{
		gsKeyRingPopupInvX				= 0;
		sKeyRingItemWidth						= MAP_KEY_RING_ROW_WIDTH;
		sOffSetX = 40;
		sOffSetY = 15;
	}
	else
	{
		// Set some globals
		gsKeyRingPopupInvX					= sInvX + TACTICAL_INVENTORY_KEYRING_GRAPHIC_OFFSET_X;
		sKeyRingItemWidth						= KEY_RING_ROW_WIDTH;
		sOffSetY = 8;
	}

	gsKeyRingPopupInvY					= sInvY;
	gsKeyRingPopupInvWidth				= sInvWidth;
	gsKeyRingPopupInvHeight				= sInvHeight;

	gpItemPopupSoldier = pSoldier;

	// Load graphics
	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	strcpy( VObjectDesc.ImageFile, "INTERFACE\\extra_inventory.STI" );
	CHECKF( AddVideoObject( &VObjectDesc, &guiItemPopupBoxes) );

	if(UsingNewInventorySystem() == true)
	{
		VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
		strcpy( VObjectDesc.ImageFile, "INTERFACE\\infobox_background.sti" );
		CHECKF( AddVideoObject( &VObjectDesc, &guiItemDescBoxBackground) );
	}
	else
		guiItemDescBoxBackground = 0;

	// Get size
	GetVideoObject( &hVObject, guiItemPopupBoxes );
	pTrav = &(hVObject->pETRLEObject[ 0 ] );
	usPopupWidth = pTrav->usWidth;
	usPopupHeight = pTrav->usHeight;

	// Determine position, height and width of mouse region, area
	//GetSlotInvHeightWidth( ubSlotSimilarToKeySlot, &sItemSlotWidth, &sItemSlotHeight );

	for ( cnt = 0; cnt < NUMBER_KEYS_ON_KEYRING; cnt++ )
	{
		// Build a mouse region here that is over any others.....
		MSYS_DefineRegion( &gKeyRingRegions[cnt],
				(INT16)( gsKeyRingPopupInvX + ( cnt % sKeyRingItemWidth * usPopupWidth ) + sOffSetX ), // top left
				(INT16)( sInvY + sOffSetY +( cnt / sKeyRingItemWidth * usPopupHeight ) ), // top right
				(INT16)( gsKeyRingPopupInvX + ( ( cnt % sKeyRingItemWidth ) + 1 ) * usPopupWidth + sOffSetX ), // bottom left
				(INT16)( sInvY + ( (cnt / sKeyRingItemWidth + 1) * usPopupHeight ) + sOffSetY ), // bottom right
				MSYS_PRIORITY_HIGHEST,
				MSYS_NO_CURSOR, MSYS_NO_CALLBACK, KeyRingSlotInvClickCallback );
		// Add region
		MSYS_AddRegion( &gKeyRingRegions[cnt]);
		MSYS_SetRegionUserData( &gKeyRingRegions[cnt], 0, cnt );
		//gfItemPopupRegionCallbackEndFix = FALSE;
	}


	// Build a mouse region here that is over any others.....
	MSYS_DefineRegion( &gItemPopupRegion, sInvX, sInvY ,(INT16)(sInvX + sInvWidth), (INT16)(sInvY + sInvHeight), MSYS_PRIORITY_HIGH,
						 MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemPopupFullRegionCallback );

	// Add region
	MSYS_AddRegion( &gItemPopupRegion);


	//Disable all faces
	SetAllAutoFacesInactive( );


	fInterfacePanelDirty = DIRTYLEVEL2;

	//guiTacticalInterfaceFlags |= INTERFACE_NORENDERBUTTONS;


//	if ( !(guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
	if( guiCurrentItemDescriptionScreen != MAP_SCREEN )
	{
		EnableSMPanelButtons( FALSE , FALSE );
	}

	gfInKeyRingPopup = TRUE;

	//Reserict mouse cursor to panel
	aRect.iLeft = gsKeyRingPopupInvX + sOffSetX;
	aRect.iTop = sInvY + sOffSetY;
	aRect.iRight = aRect.iLeft + sKeyRingItemWidth * usPopupWidth;
	aRect.iBottom = aRect.iTop + (INT32)(ceil((float)cnt/(float)sKeyRingItemWidth)+1) * usPopupHeight;

	RestrictMouseCursor( &aRect );

	return( TRUE );
}


void RenderKeyRingPopup( BOOLEAN fFullRender )
{
  ETRLEObject						*pTrav;
	UINT32								usHeight, usWidth;
	HVOBJECT							hVObject;
	UINT32								cnt;
	INT16 sKeyRingItemWidth = 0;
	INT16 sOffSetY = 0, sOffSetX = 0;

	if( guiCurrentScreen != MAP_SCREEN )
	{
		sOffSetY = 8;
	}
	else
	{
		sOffSetX = 40;
		sOffSetY = 15;
	}

	if ( gfInKeyRingPopup )
	{

		//Disable all faces
		SetAllAutoFacesInactive( );

		// Shadow Area
		if ( fFullRender )
		{
			if(UsingNewInventorySystem() == false || guiCurrentScreen == MAP_SCREEN)
				ShadowVideoSurfaceRect( FRAME_BUFFER, 0, gsKeyRingPopupInvY, gsKeyRingPopupInvX + gsKeyRingPopupInvWidth , gsKeyRingPopupInvY + gsKeyRingPopupInvHeight );
			else if(UsingNewInventorySystem() == true && iResolution != 0 && guiItemDescBoxBackground != 0 && guiCurrentScreen != MAP_SCREEN)
				BltVideoObjectFromIndex( FRAME_BUFFER, guiItemDescBoxBackground, iResolution, SM_ITEMDESC_START_X, SM_ITEMDESC_START_Y, VO_BLT_SRCTRANSPARENCY, NULL );
		}

	}

	gTempObject.usItem = KEY_1;
	gTempObject[0]->data.objectStatus = 100;

	// TAKE A LOOK AT THE VIDEO OBJECT SIZE ( ONE OF TWO SIZES ) AND CENTER!
	GetVideoObject( &hVObject, guiItemPopupBoxes );
	pTrav = &(hVObject->pETRLEObject[ 0 ] );
	usHeight				= (UINT32)pTrav->usHeight;
	usWidth					= (UINT32)pTrav->usWidth;

	if( guiCurrentScreen == MAP_SCREEN )
	{
		sKeyRingItemWidth						= MAP_KEY_RING_ROW_WIDTH;
	}
	else
	{
		// Set some globals
		sKeyRingItemWidth						= KEY_RING_ROW_WIDTH;
	}

	for ( cnt = 0; cnt < NUMBER_KEYS_ON_KEYRING; cnt++ )
	{
		BltVideoObjectFromIndex( FRAME_BUFFER, guiItemPopupBoxes, 0, (INT16)(gsKeyRingPopupInvX + ( cnt % sKeyRingItemWidth * usWidth ) + sOffSetX ), ( INT16 )( gsKeyRingPopupInvY + sOffSetY + ( cnt / sKeyRingItemWidth * usHeight ) ), VO_BLT_SRCTRANSPARENCY, NULL );

		// will want to draw key here.. if there is one
		if( ( gpItemPopupSoldier->pKeyRing[ cnt ].ubKeyID != INVALID_KEY_NUMBER ) && ( gpItemPopupSoldier->pKeyRing[ cnt ].ubNumber > 0 ) )
		{
			gTempObject.ubNumberOfObjects = gpItemPopupSoldier->pKeyRing[ cnt ].ubNumber;

			// show 100% status for each
			DrawItemUIBarEx( &gTempObject, 0, (INT16)( gsKeyRingPopupInvX + sOffSetX + ( cnt % sKeyRingItemWidth * usWidth ) + 7 ), ( INT16 )( gsKeyRingPopupInvY + sOffSetY + ( cnt / sKeyRingItemWidth * usHeight ) + 24 )
			, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT, 	Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , FRAME_BUFFER );

			// set item type
			gTempObject.usItem = FIRST_KEY + LockTable[ gpItemPopupSoldier->pKeyRing[ cnt].ubKeyID ].usKeyItem;

			// render the item
			INVRenderItem( FRAME_BUFFER, NULL, &gTempObject, (INT16)(gsKeyRingPopupInvX + sOffSetX +( cnt % sKeyRingItemWidth * usWidth ) + 8), ( INT16 )( gsKeyRingPopupInvY + sOffSetY + ( cnt / sKeyRingItemWidth * usHeight ) ),
				( UINT16 )( usWidth - 8 ), ( UINT16 )( usHeight - 2 ) , DIRTYLEVEL2,  NULL, 0, 0, 0 );
		}

		//BltVideoObjectFromIndex( FRAME_BUFFER, guiItemPopupBoxes, 0, (INT16)(gsKeyRingPopupInvX + ( cnt % KEY_RING_ROW_WIDTH * usWidth ) ), ( INT16 )( gsKeyRingPopupInvY + ( cnt / KEY_RING_ROW_WIDTH * usHeight ) ), VO_BLT_SRCTRANSPARENCY, NULL );


	}

	//RestoreExternBackgroundRect( gsItemPopupInvX, gsItemPopupInvY, gsItemPopupInvWidth, gsItemPopupInvHeight );
	InvalidateRegion( gsKeyRingPopupInvX, gsKeyRingPopupInvY, gsKeyRingPopupInvX + gsKeyRingPopupInvWidth, gsKeyRingPopupInvY + gsKeyRingPopupInvHeight );

}


void DeleteKeyRingPopup( )
{
	INT32			cnt;

	if( gfInKeyRingPopup == FALSE )
	{
		// done,
		return;
	}

	//Remove
	DeleteVideoObjectFromIndex( guiItemPopupBoxes );

	MSYS_RemoveRegion( &gItemPopupRegion);


	gfInKeyRingPopup = FALSE;

	for ( cnt = 0; cnt < NUMBER_KEYS_ON_KEYRING; cnt++ )
	{
		MSYS_RemoveRegion( &gKeyRingRegions[cnt]);
	}


	fInterfacePanelDirty = DIRTYLEVEL2;

	//guiTacticalInterfaceFlags &= (~INTERFACE_NORENDERBUTTONS);

//	if ( !(guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
	if( guiCurrentItemDescriptionScreen != MAP_SCREEN )
	{
		EnableSMPanelButtons( TRUE, FALSE );
	}

	FreeMouseCursor( );
}

UINT32 GetInterfaceGraphicForItem( INVTYPE *pItem )
{
	// CHECK SUBCLASS
	if ( pItem->ubGraphicType == 0 )
	{
		return( guiGUNSM );
	}
	else if ( pItem->ubGraphicType == 1 )
	{
		return( guiP1ITEMS );
	}
	else if ( pItem->ubGraphicType == 2 )
	{
		return( guiP2ITEMS );
	}
	else
	{
		return( guiP3ITEMS );
	}

}


UINT16 GetTileGraphicForItem( INVTYPE *pItem )
{
	UINT16 usIndex;

	if ( pItem->ubClassIndex >= M900 )
		DebugMsg(TOPIC_JA2, DBG_LEVEL_3, String("GetTileGraphicForItem: item %d graphic %d",pItem->ubClassIndex, pItem->ubGraphicNum));
	// CHECK SUBCLASS
	if ( pItem->ubGraphicType == 0 )
	{
		GetTileIndexFromTypeSubIndex( GUNS, (INT16)(pItem->ubGraphicNum+1), &usIndex );
	}
	else if ( pItem->ubGraphicType == 1 )
	{
		GetTileIndexFromTypeSubIndex( P1ITEMS, (INT16)(pItem->ubGraphicNum+1), &usIndex );
	}
	else if ( pItem->ubGraphicType == 2 )
	{
		GetTileIndexFromTypeSubIndex( P2ITEMS, (INT16)(pItem->ubGraphicNum+1), &usIndex );
	}
	else
	{
		GetTileIndexFromTypeSubIndex( P3ITEMS, (INT16)(pItem->ubGraphicNum+1), &usIndex );
	}

	if ( pItem->ubClassIndex >= M900  )
		DebugMsg(TOPIC_JA2, DBG_LEVEL_3, String("GetTileGraphicForItem: db index %d",usIndex));
	return( usIndex );
}


BOOLEAN LoadTileGraphicForItem( INVTYPE *pItem, UINT32 *puiVo )
{
	CHAR8	 zName[ 100 ];
	UINT32	uiVo;
	VOBJECT_DESC    VObjectDesc;
	UINT16		ubGraphic;

	DebugMsg(TOPIC_JA2,DBG_LEVEL_3,String("LoadTileGraphicForItem"));

	// CHECK SUBCLASS
	ubGraphic = pItem->ubGraphicNum;

	if ( pItem->ubGraphicType == 0 )
	{
		// CHECK SUBCLASS
		//ubGraphic++;

		if ( ubGraphic < 10 )
		{
			sprintf( zName, "gun0%d.sti", ubGraphic );
		}
		else
		{
			sprintf( zName, "gun%d.sti", ubGraphic );
		}
	}
	else if ( pItem->ubGraphicType == 1 )
	{
		if ( ubGraphic < 10 )
		{
			sprintf( zName, "p1item0%d.sti", ubGraphic );
		}
		else
		{
			sprintf( zName, "p1item%d.sti", ubGraphic );
		}
	}
	else if ( pItem->ubGraphicType == 2 )
	{
		if ( ubGraphic < 10 )
		{
			sprintf( zName, "p2item0%d.sti", ubGraphic );
		}
		else
		{
			sprintf( zName, "p2item%d.sti", ubGraphic );
		}
	}
	else
	{
		if ( ubGraphic < 10 )
		{
			sprintf( zName, "p3item0%d.sti", ubGraphic );
		}
		else
		{
			sprintf( zName, "p3item%d.sti", ubGraphic );
		}
	}

	//Load item
	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	sprintf( VObjectDesc.ImageFile, "BIGITEMS\\%s", zName );
	CHECKF( AddVideoObject( &VObjectDesc, &uiVo) );

	*puiVo = uiVo;

	DebugMsg(TOPIC_JA2,DBG_LEVEL_3,String("LoadTileGraphicForItem: done"));

	return( TRUE );
}

void ItemDescMoveCallback( MOUSE_REGION * pRegion, INT32 iReason )
{
}

void ItemDescCallback( MOUSE_REGION * pRegion, INT32 iReason )
{
	static BOOLEAN fRightDown = FALSE, fLeftDown = FALSE;

	if (iReason & MSYS_CALLBACK_REASON_LBUTTON_DWN)
	{
		fLeftDown = TRUE;
	}
	else if (iReason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		if ( fLeftDown )
		{
			fLeftDown = FALSE;

			//Only exit the screen if we are NOT in the money interface.  Only the DONE button should exit the money interface.
			if( gpItemDescObject->usItem != MONEY )
			{
				DeleteItemDescriptionBox( );
			}
		}
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_DWN)
	{
		fRightDown = TRUE;
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_UP)
	{
		if ( fRightDown )
		{
			fRightDown = FALSE;

			//Only exit the screen if we are NOT in the money interface.  Only the DONE button should exit the money interface.
//			if( gpItemDescObject->usItem != MONEY )
			{
				DeleteItemDescriptionBox( );
			}
		}
	}
}

void ItemDescDoneButtonCallback( GUI_BUTTON *btn, INT32 reason )
{

	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
	  btn->uiFlags|=(BUTTON_CLICKED_ON);
	}
	else if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
  {
    if (btn->uiFlags & BUTTON_CLICKED_ON)
		{
      btn->uiFlags&=~(BUTTON_CLICKED_ON);

			if( gpItemDescObject->usItem == MONEY )
			{
				RemoveMoney();
			}

		  DeleteItemDescriptionBox( );
		}
	}

	if(reason & MSYS_CALLBACK_REASON_RBUTTON_DWN )
	{
	  btn->uiFlags|=(BUTTON_CLICKED_ON);
	}
	else if(reason & MSYS_CALLBACK_REASON_RBUTTON_UP )
  {
    if (btn->uiFlags & BUTTON_CLICKED_ON)
		{
      btn->uiFlags&=~(BUTTON_CLICKED_ON);
		  DeleteItemDescriptionBox( );
		}
	}
}


void ItemPopupRegionCallback( MOUSE_REGION * pRegion, INT32 iReason )
{
	UINT32					uiItemPos;
	UINT32					iItemCap;
	INT32					ubID;

	uiItemPos = MSYS_GetRegionUserData( pRegion, 0 );
	iItemCap = MSYS_GetRegionUserData( pRegion, 1 );
	ubID = MSYS_GetRegionUserData( pRegion, 2 );

	// TO ALLOW ME TO DELETE REGIONS IN CALLBACKS!
	if ( gfItemPopupRegionCallbackEndFix )
	{
		return;
	}

	if (iReason & MSYS_CALLBACK_REASON_LBUTTON_DWN)
	{
		//If something in our hand, see if it's ammo and if we are trying to reload a gun
		if ( gpItemPointer != NULL )
		{
			//CHRISL: Since we can now stack guns, let's make it so we can reload guns in a stack
			if(CompatibleAmmoForGun(gpItemPointer, gpItemPopupObject) || ValidLaunchable(gpItemPointer->usItem, gpItemPopupObject->usItem))
			{
				switch (Item[gpItemPopupObject->usItem].usItemClass)
				{
					case IC_GUN:
						if (Item[gpItemPointer->usItem].usItemClass == IC_AMMO) {
							if (Weapon[gpItemPopupObject->usItem].ubCalibre == Magazine[Item[gpItemPointer->usItem].ubClassIndex].ubCalibre) {
								ReloadGun( MercPtrs[ubID], gpItemPopupObject, gpItemPointer, uiItemPos );
							}
						}
						break;
					case IC_LAUNCHER:
						if ( ValidLaunchable( gpItemPointer->usItem, gpItemPopupObject->usItem ) ) {
							ReloadGun( MercPtrs[ubID], gpItemPopupObject, gpItemPointer, uiItemPos );
						}
						break;
				}
			}
		}
		//If one in our hand, place it
		if ( gpItemPointer != NULL )
		{
			if ( !PlaceObjectAtObjectIndex( gpItemPointer, gpItemPopupObject, (UINT8)uiItemPos, iItemCap ) )
			{
				if ( (guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
				{
					MAPEndItemPointer( );
				}
				else
				{
					gpItemPointer = NULL;
					MSYS_ChangeRegionCursor( &gSMPanelRegion , CURSOR_NORMAL );
					SetCurrentCursorFromDatabase( CURSOR_NORMAL );

					if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
					{
						gMoveingItem.initialize();
						SetSkiCursor( CURSOR_NORMAL );
					}
				}

				// re-evaluate repairs
				gfReEvaluateEveryonesNothingToDo = TRUE;
			}

				//Dirty interface
				//fInterfacePanelDirty = DIRTYLEVEL2;
				//RenderItemStackPopup( FALSE );
		}
		else
		{
			if ( uiItemPos < gpItemPopupObject->ubNumberOfObjects )
			{
				// Here, grab an item and put in cursor to swap
				//RemoveObjFrom( OBJECTTYPE * pObj, UINT8 ubRemoveIndex )

    			if ( (guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
				{
					// pick it up
					if(ubID != -1)
					{
						gpItemPopupObject->RemoveObjectAtIndex( uiItemPos, &gItemPointer );
						InternalMAPBeginItemPointer( gpItemPopupSoldier );
					}
					else
					{
						OBJECTTYPE	tSectorItem;
						gpItemPopupObject->RemoveObjectAtIndex( uiItemPos, &tSectorItem );
						BeginInventoryPoolPtr(&tSectorItem);
						guiCurrentItemDescriptionScreen = MAP_SCREEN;
					}
				}
				else
				{
					gpItemPopupObject->RemoveObjectAtIndex( uiItemPos, &gItemPointer );
					gpItemPointer = &gItemPointer;
					gpItemPointerSoldier = gpItemPopupSoldier;
				}

				//if we are in the shop keeper interface
				if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
				{
					// pick up stacked item into cursor and try to sell it ( unless CTRL is held down )
					BeginSkiItemPointer( PLAYERS_INVENTORY, -1, ( BOOLEAN )!gfKeyState[ CTRL ] );

				}
				// if we've just removed the last one there
				if ( gpItemPopupObject->exists() == false )
				{
					// we must immediately get out of item stack popup, because the item has been deleted (memset to 0), and
					// errors like a right bringing up an item description for item 0 could happen then.  ARM.
					DeleteItemStackPopup( );
				}

				// re-evaluate repairs
				gfReEvaluateEveryonesNothingToDo = TRUE;

				//Dirty interface
				//RenderItemStackPopup( FALSE );
				//fInterfacePanelDirty = DIRTYLEVEL2;
			}
		}

		UpdateItemHatches();
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_UP)
	{
		// Get Description....
		// Some global stuff here - for esc, etc
		//Remove
		gfItemPopupRegionCallbackEndFix = TRUE;


		DeleteItemStackPopup( );

		if ( gpItemPopupObject->ubNumberOfObjects <= uiItemPos )
			fTeamPanelDirty = TRUE;
		else if ( !InItemDescriptionBox( ) )
		{
			// RESTORE BACKGROUND
			RestoreExternBackgroundRect( gsItemPopupInvX, gsItemPopupInvY, gsItemPopupInvWidth, gsItemPopupInvHeight );
			if ( guiCurrentItemDescriptionScreen == MAP_SCREEN )
			{
				MAPInternalInitItemDescriptionBox( gpItemPopupObject, (UINT8)uiItemPos, gpItemPopupSoldier );
			}
			else
			{
				InternalInitItemDescriptionBox( gpItemPopupObject, (INT16) ITEMDESC_START_X, (INT16) ITEMDESC_START_Y, (UINT8)uiItemPos, gpItemPopupSoldier );
			}
		}
	}
}

void ItemPopupFullRegionCallback( MOUSE_REGION * pRegion, INT32 iReason )
{
	UINT32					uiItemPos;

	uiItemPos = MSYS_GetRegionUserData( pRegion, 0 );

	if (iReason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		if ( InItemStackPopup( ) )
		{
			// End stack popup and retain pointer
			EndItemStackPopupWithItemInHand( );
		}
		else if( InKeyRingPopup() )
		{
			// end pop up with key in hand
			DeleteKeyRingPopup( );
			fTeamPanelDirty = TRUE;

		}
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_UP)
	{
		if ( InItemStackPopup( ) || InSectorStackPopup( ) )
		{
			DeleteItemStackPopup( );
			fTeamPanelDirty = TRUE;
		}
		else
		{
			DeleteKeyRingPopup( );
			fTeamPanelDirty = TRUE;
		}
	}
}

#define NUM_PICKUP_SLOTS				6

#define SIZEOF_ITEM_PICKUP_MENU_STRUCT_POD offsetof(ITEM_PICKUP_MENU_STRUCT, endOfPod)
class ITEM_PICKUP_MENU_STRUCT
{
public:
	ITEM_PICKUP_MENU_STRUCT() {initialize();};
	void	initialize() {memset(this, 0, SIZEOF_ITEM_PICKUP_MENU_STRUCT_POD); CompAmmoObject.initialize();};
	ITEM_POOL			*pItemPool;
	INT16					sX;
	INT16					sY;
	INT16					sWidth;
	INT16					sHeight;
	INT8					bScrollPage;
	INT32			  	ubScrollAnchor;
	INT32		  		ubTotalItems;
	INT32		  		bCurSelect;
	UINT8					bNumSlotsPerPage;
	UINT32				uiPanelVo;
	INT32					iUpButtonImages;
	INT32					iDownButtonImages;
	INT32					iAllButtonImages;
	INT32					iCancelButtonImages;
	INT32					iOKButtonImages;
	INT32					iUpButton;
	INT32					iDownButton;
	INT32					iAllButton;
	INT32					iOKButton;
	INT32					iCancelButton;
	BOOLEAN				fCanScrollUp;
	BOOLEAN				fCanScrollDown;
	BOOLEAN				fDirtyLevel;
	INT32					iDirtyRect;
	BOOLEAN				fHandled;
	INT16					sGridNo;
	INT8					bZLevel;
	INT16					sButtomPanelStartY;
	SOLDIERTYPE		*pSoldier;
	ITEM_POOL			*ItemPoolSlots[ NUM_PICKUP_SLOTS ];
	MOUSE_REGION	Regions[ NUM_PICKUP_SLOTS ];
	MOUSE_REGION	BackRegions;
	MOUSE_REGION	BackRegion;
	BOOLEAN				*pfSelectedArray;
	BOOLEAN				fAtLeastOneSelected;
	BOOLEAN				fAllSelected;
	char	endOfPod;
	OBJECTTYPE		CompAmmoObject;
};

#define					ITEMPICK_UP_X				55
#define					ITEMPICK_UP_Y				5
#define					ITEMPICK_DOWN_X			111
#define					ITEMPICK_DOWN_Y			5
#define					ITEMPICK_ALL_X			79
#define					ITEMPICK_ALL_Y			6
#define					ITEMPICK_OK_X				16
#define					ITEMPICK_OK_Y				6
#define					ITEMPICK_CANCEL_X		141
#define					ITEMPICK_CANCEL_Y		6

#define					ITEMPICK_START_X_OFFSET		10
#define					ITEMPICK_START_Y_OFFSET		20

#define					ITEMPICK_GRAPHIC_X			10
#define					ITEMPICK_GRAPHIC_Y			12
#define					ITEMPICK_GRAPHIC_YSPACE	26

#define					ITEMPICK_TEXT_X					56
#define					ITEMPICK_TEXT_Y					22
#define					ITEMPICK_TEXT_YSPACE		26
#define					ITEMPICK_TEXT_WIDTH			109
#define					ITEMPICK_TEXT_HEIGHT		17




ITEM_PICKUP_MENU_STRUCT			gItemPickupMenu;
BOOLEAN											gfInItemPickupMenu = FALSE;

void ItemPickupScrollUp( GUI_BUTTON *btn, INT32 reason );
void ItemPickupScrollDown( GUI_BUTTON *btn, INT32 reason );
void ItemPickupAll( GUI_BUTTON *btn, INT32 reason );
void ItemPickupOK( GUI_BUTTON *btn, INT32 reason );
void ItemPickupCancel( GUI_BUTTON *btn, INT32 reason );
void SetupPickupPage( INT8 bPage );
void ItemPickMenuMouseMoveCallback( MOUSE_REGION * pRegion, INT32 iReason );
void ItemPickMenuMouseClickCallback( MOUSE_REGION * pRegion, INT32 iReason );
void CalculateItemPickupMenuDimensions( );
void ItemPickupBackgroundClick( MOUSE_REGION * pRegion, INT32 iReason );


// STUFF FOR POPUP ITEM INFO BOX
void SetItemPickupMenuDirty( BOOLEAN fDirtyLevel )
{
	gItemPickupMenu.fDirtyLevel = fDirtyLevel;
}


BOOLEAN InitializeItemPickupMenu( SOLDIERTYPE *pSoldier, INT16 sGridNo, ITEM_POOL *pItemPool, INT16 sScreenX, INT16 sScreenY, INT8 bZLevel )
{
  VOBJECT_DESC    VObjectDesc;
	CHAR8						ubString[48];
	ITEM_POOL				*pTempItemPool;
	INT32						cnt;
	INT16						sCenX, sCenY, sX, sY, sCenterYVal;

	gfStealing=FALSE;
	gpOpponent=NULL;

	// Erase other menus....
	EraseInterfaceMenus( TRUE );

	// Make sure menu is located if not on screen
	LocateSoldier( pSoldier->ubID, FALSE );

	// memset values
	gItemPickupMenu.initialize();

	//Set item pool value
	gItemPickupMenu.pItemPool		= pItemPool;

	InterruptTime();
	PauseGame();
	LockPauseState( 18 );
	// Pause timers as well....
	PauseTime( TRUE );


	// Alrighty, cancel lock UI if we havn't done so already
	UnSetUIBusy( pSoldier->ubID );

	// Change to INV panel if not there already...
	gfSwitchPanel = TRUE;
	gbNewPanel = SM_PANEL;
	gubNewPanelParam = (UINT8)pSoldier->ubID;

	//Determine total #
	cnt = 0;
	pTempItemPool = pItemPool;
	while( pTempItemPool != NULL )
	{
		if ( ItemPoolOKForDisplay( pTempItemPool, bZLevel ) )
		{
			cnt++;
		}

		pTempItemPool = pTempItemPool->pNext;
	}
	gItemPickupMenu.ubTotalItems = (UINT8)cnt;

	// Determine # of slots per page
	if ( gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
	{
		gItemPickupMenu.bNumSlotsPerPage = NUM_PICKUP_SLOTS;
	}
	else
	{
		gItemPickupMenu.bNumSlotsPerPage = gItemPickupMenu.ubTotalItems;
	}

	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\itembox.sti", VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(gItemPickupMenu.uiPanelVo) ) );

	// Memalloc selection array...
	 gItemPickupMenu.pfSelectedArray = (BOOLEAN *) MemAlloc(( sizeof( UINT8 ) * gItemPickupMenu.ubTotalItems ) );
	// seto to 0
	memset( gItemPickupMenu.pfSelectedArray, 0, ( sizeof( UINT8 ) * gItemPickupMenu.ubTotalItems ) );

	// Calcualate dimensions
	CalculateItemPickupMenuDimensions( );

	// Get XY
	{
		// First get mouse xy screen location
		if( sGridNo != NOWHERE )
		{
			sX = gusMouseXPos;
			sY = gusMouseYPos;
		}
		else
		{
			 sX = sScreenX;
			 sY = sScreenY;
		}

		// CHECK FOR LEFT/RIGHT
		if ( ( sX + gItemPickupMenu.sWidth ) > SCREEN_WIDTH )
		{
			sX = SCREEN_WIDTH - gItemPickupMenu.sWidth - ITEMPICK_START_X_OFFSET;
		}
		else
		{
			sX = sX + ITEMPICK_START_X_OFFSET;
		}

		// Now check for top
		// Center in the y
		sCenterYVal = gItemPickupMenu.sHeight / 2;

		sY -= sCenterYVal;

		if ( sY < gsVIEWPORT_WINDOW_START_Y )
		{
			sY = gsVIEWPORT_WINDOW_START_Y;
		}

		// Check for bottom
		if ( ( sY + gItemPickupMenu.sHeight ) > INV_INTERFACE_START_Y )
		{
			sY = INV_INTERFACE_START_Y - gItemPickupMenu.sHeight;
		}

	}

	// Set some values
	gItemPickupMenu.sX					= sX;
	gItemPickupMenu.sY					= sY;
	gItemPickupMenu.bCurSelect	= 0;
	gItemPickupMenu.pSoldier		= pSoldier;
	gItemPickupMenu.fHandled		= FALSE;
	gItemPickupMenu.sGridNo			= sGridNo;
	gItemPickupMenu.bZLevel			= bZLevel;
	gItemPickupMenu.fAtLeastOneSelected = FALSE;
	gItemPickupMenu.fAllSelected	= FALSE;

	//Load images for buttons
	FilenameForBPP("INTERFACE\\itembox.sti", ubString );
	gItemPickupMenu.iUpButtonImages			= LoadButtonImage( ubString, -1,5,-1,10,-1 );
	gItemPickupMenu.iDownButtonImages		=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 7, -1, 12, -1 );
	gItemPickupMenu.iAllButtonImages		=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 6, -1,11, -1 );
	gItemPickupMenu.iCancelButtonImages	=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 8, -1, 13, -1 );
	gItemPickupMenu.iOKButtonImages			=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 4, -1, 9, -1 );

/* This region definition must be checked and recalculated!!!
 * i didnt have time for that sorry
 * any questions? joker
 */

	// Build a mouse region here that is over any others.....
	MSYS_DefineRegion( &(gItemPickupMenu.BackRegion ), (INT16)( SCREEN_WIDTH - 108 ), (INT16)( SCREEN_HEIGHT - 133 ), (INT16)( SCREEN_WIDTH  ),(INT16)( SCREEN_HEIGHT ), MSYS_PRIORITY_HIGHEST,
						 CURSOR_NORMAL, MSYS_NO_CALLBACK, MSYS_NO_CALLBACK );
	// Add region
	MSYS_AddRegion( &(gItemPickupMenu.BackRegion ) );


	// Build a mouse region here that is over any others.....
	MSYS_DefineRegion( &(gItemPickupMenu.BackRegions ), (INT16)(gItemPickupMenu.sX ), (INT16)(gItemPickupMenu.sY), (INT16)(gItemPickupMenu.sX + gItemPickupMenu.sWidth ),(INT16)( gItemPickupMenu.sY + gItemPickupMenu.sHeight ), MSYS_PRIORITY_HIGHEST,
						 CURSOR_NORMAL, MSYS_NO_CALLBACK, MSYS_NO_CALLBACK );
	// Add region
	MSYS_AddRegion( &(gItemPickupMenu.BackRegions ) );


	// Create buttons
	if ( gItemPickupMenu.bNumSlotsPerPage == NUM_PICKUP_SLOTS && gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
	{
		gItemPickupMenu.iUpButton	= QuickCreateButton( gItemPickupMenu.iUpButtonImages, (INT16)(sX + ITEMPICK_UP_X), (INT16)(sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_UP_Y),
	 									 BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
	 									 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemPickupScrollUp );

		SetButtonFastHelpText( gItemPickupMenu.iUpButton, ItemPickupHelpPopup[ 1 ] );


		gItemPickupMenu.iDownButton	= QuickCreateButton( gItemPickupMenu.iDownButtonImages, (INT16)(sX + ITEMPICK_DOWN_X), (INT16)(sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_DOWN_Y),
	 									 BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
	 									 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemPickupScrollDown );

		SetButtonFastHelpText( gItemPickupMenu.iDownButton, ItemPickupHelpPopup[ 3 ] );

	}


	gItemPickupMenu.iOKButton	= QuickCreateButton( gItemPickupMenu.iOKButtonImages, (INT16)(sX + ITEMPICK_OK_X), (INT16)(sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_OK_Y),
	 									 BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
	 									 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemPickupOK );
	SetButtonFastHelpText( gItemPickupMenu.iOKButton, ItemPickupHelpPopup[ 0 ] );


	gItemPickupMenu.iAllButton	= QuickCreateButton( gItemPickupMenu.iAllButtonImages, (INT16)(sX + ITEMPICK_ALL_X), (INT16)(sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_ALL_Y),
	 									 BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
	 									 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemPickupAll );
	SetButtonFastHelpText( gItemPickupMenu.iAllButton, ItemPickupHelpPopup[ 2 ] );

	gItemPickupMenu.iCancelButton	= QuickCreateButton( gItemPickupMenu.iCancelButtonImages, (INT16)(sX + ITEMPICK_CANCEL_X), (INT16)(sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_CANCEL_Y),
	 									 BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
	 									 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemPickupCancel );
	SetButtonFastHelpText( gItemPickupMenu.iCancelButton, ItemPickupHelpPopup[ 4 ] );


	DisableButton( gItemPickupMenu.iOKButton );



	// Create regions...
	sCenX = gItemPickupMenu.sX;
	sCenY = gItemPickupMenu.sY + ITEMPICK_GRAPHIC_Y;

	for ( cnt = 0; cnt < gItemPickupMenu.bNumSlotsPerPage; cnt++ )
	{
		// Build a mouse region here that is over any others.....
		MSYS_DefineRegion( &(gItemPickupMenu.Regions[cnt]), (INT16)(sCenX ), (INT16)(sCenY + 1), (INT16)(sCenX + gItemPickupMenu.sWidth ),(INT16)( sCenY + ITEMPICK_GRAPHIC_YSPACE ), MSYS_PRIORITY_HIGHEST,
							 CURSOR_NORMAL, ItemPickMenuMouseMoveCallback, ItemPickMenuMouseClickCallback );
		// Add region
		MSYS_AddRegion( &(gItemPickupMenu.Regions[cnt]) );
		MSYS_SetRegionUserData( &(gItemPickupMenu.Regions[cnt]), 0, cnt );

		sCenY += ITEMPICK_GRAPHIC_YSPACE;
	}

	//Save dirty rect
	//gItemPickupMenu.iDirtyRect = RegisterBackgroundRect( BGND_FLAG_PERMANENT | BGND_FLAG_SAVERECT, NULL, gItemPickupMenu.sX, gItemPickupMenu.sY, (INT16)(gItemPickupMenu.sX + gItemPickupMenu.sWidth ) , (INT16)(gItemPickupMenu.sY + gItemPickupMenu.sHeight ) );


	SetupPickupPage( 0 );

	gfInItemPickupMenu = TRUE;

	// Ignore scrolling
	gfIgnoreScrolling = TRUE;

	HandleAnyMercInSquadHasCompatibleStuff( (INT8) CurrentSquad( ), NULL, TRUE );
	gubSelectSMPanelToMerc = pSoldier->ubID;
	ReEvaluateDisabledINVPanelButtons( );
	DisableTacticalTeamPanelButtons( TRUE );

	//gfSMDisableForItems = TRUE;
	return( TRUE );

}


void SetupPickupPage( INT8 bPage )
{
	INT32 cnt, iStart, iEnd;
	ITEM_POOL				*pTempItemPool;
  INT16           sValue;
	OBJECTTYPE  *pObject;
	static CHAR16 pStr[ 200 ];


	// Zero out page slots
	memset( gItemPickupMenu.ItemPoolSlots, 0, sizeof( gItemPickupMenu.ItemPoolSlots )  );

	// Zero page flags
	gItemPickupMenu.fCanScrollUp		= FALSE;
	gItemPickupMenu.fCanScrollDown  = FALSE;

	// Get lower bound
	iStart = bPage * NUM_PICKUP_SLOTS;
	if ( iStart > gItemPickupMenu.ubTotalItems )
	{
		return;
	}

	if ( bPage > 0 )
	{
		gItemPickupMenu.fCanScrollUp = TRUE;
	}


	iEnd   = iStart + NUM_PICKUP_SLOTS;
	if ( iEnd >= gItemPickupMenu.ubTotalItems )
	{
		iEnd = gItemPickupMenu.ubTotalItems;
	}
	else
	{
		// We can go for more!
		gItemPickupMenu.fCanScrollDown = TRUE;
	}

	// Setup slots!
	// These slots contain an inventory pool pointer for each slot...
	pTempItemPool = gItemPickupMenu.pItemPool;

  // ATE: Patch fix here for crash :(
  // Clear help text!
	for ( cnt = 0; cnt < NUM_PICKUP_SLOTS; cnt++ )
	{
  	SetRegionFastHelpText( &(gItemPickupMenu.Regions[cnt]), L"" );
  }

	for ( cnt = 0; cnt < iEnd; )
	{
		// Move to the closest one that can be displayed....
		if (!gfStealing)
		{
			while( !ItemPoolOKForDisplay( pTempItemPool, gItemPickupMenu.bZLevel ) )
			{
				pTempItemPool = pTempItemPool->pNext;
			}
		}

		if ( cnt >= iStart )
		{
			gItemPickupMenu.ItemPoolSlots[ cnt - iStart ] = pTempItemPool;

			pObject = (gfStealing)? &gpOpponent->inv[pTempItemPool->iItemIndex]
				:&(gWorldItems[ pTempItemPool->iItemIndex ].object );

		  sValue = (*pObject)[0]->data.objectStatus;

	    // Adjust for ammo, other thingys..
	    if( Item[ pObject->usItem ].usItemClass & IC_AMMO || Item[ pObject->usItem ].usItemClass & IC_KEY )
	    {
        swprintf( pStr, L"" );
	    }
      else
      {
        swprintf( pStr, L"%d%%", sValue );
      }

    	SetRegionFastHelpText( &(gItemPickupMenu.Regions[ cnt - iStart ]), pStr );
		}

		cnt++;

		pTempItemPool = pTempItemPool->pNext;
	}

	gItemPickupMenu.bScrollPage		= bPage;
	gItemPickupMenu.ubScrollAnchor	= (UINT8)iStart;

	if ( gItemPickupMenu.bNumSlotsPerPage == NUM_PICKUP_SLOTS && gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
	{
		// Setup enabled/disabled buttons
		if ( gItemPickupMenu.fCanScrollUp )
		{
			EnableButton( gItemPickupMenu.iUpButton );
		}
		else
		{
			DisableButton( gItemPickupMenu.iUpButton );
		}

		// Setup enabled/disabled buttons
		if ( gItemPickupMenu.fCanScrollDown )
		{
			EnableButton( gItemPickupMenu.iDownButton );
		}
		else
		{
			DisableButton( gItemPickupMenu.iDownButton );
		}
	}
	SetItemPickupMenuDirty( DIRTYLEVEL2 );

}


void CalculateItemPickupMenuDimensions( )
{
	INT32			cnt;
	INT16			sX, sY;
	UINT16			usSubRegion, usHeight, usWidth;

	// Build background
	sX = 0;
	sY = 0;

	for ( cnt = 0; cnt < gItemPickupMenu.bNumSlotsPerPage; cnt++ )
	{
		if ( cnt == 0 )
		{
			usSubRegion = 0;
		}
		else
		{
			usSubRegion = 1;
		}

		// Add hieght of object
		GetVideoObjectETRLESubregionProperties( gItemPickupMenu.uiPanelVo, usSubRegion, &usWidth, &usHeight );

		sY += usHeight;

	}
	gItemPickupMenu.sButtomPanelStartY = sY;

	// Do end
	GetVideoObjectETRLESubregionProperties( gItemPickupMenu.uiPanelVo, 2, &usWidth, &usHeight );

	sY += usHeight;

	// Set height, width
	gItemPickupMenu.sHeight				= sY;
	gItemPickupMenu.sWidth				= usWidth;

}


// set pick up menu dirty level
void SetPickUpMenuDirtyLevel( BOOLEAN fDirtyLevel )
{
	gItemPickupMenu.fDirtyLevel = fDirtyLevel;

	return;
}


void RenderItemPickupMenu( )
{
	INT32			cnt;
	UINT16		usItemTileIndex;
	INT16			sX, sY, sCenX, sCenY, sFontX, sFontY, sNewX, sNewY;
	UINT32			uiDestPitchBYTES;
	UINT8				*pDestBuf;
	CHAR16				pStr[ 100 ];
	UINT16			usSubRegion, usHeight, usWidth;
	INVTYPE   *pItem;
	OBJECTTYPE  *pObject;
	UINT16			uiStringLength;


	if ( !gfInItemPickupMenu )
	{
		return;
	}


	// Do everything!
	if ( gItemPickupMenu.fDirtyLevel == DIRTYLEVEL2 )
	{
		MarkButtonsDirty( );

		// Build background
		sX = gItemPickupMenu.sX;
		sY = gItemPickupMenu.sY;

		for ( cnt = 0; cnt < gItemPickupMenu.bNumSlotsPerPage; cnt++ )
		{
			if ( cnt == 0 )
			{
				usSubRegion = 0;
			}
			else
			{
				usSubRegion = 1;
			}

			BltVideoObjectFromIndex( FRAME_BUFFER, gItemPickupMenu.uiPanelVo, usSubRegion, sX, sY, VO_BLT_SRCTRANSPARENCY, NULL );

			// Add hieght of object
			GetVideoObjectETRLESubregionProperties( gItemPickupMenu.uiPanelVo, usSubRegion, &usWidth, &usHeight );

			sY += usHeight;

		}

		// Do end
		if ( gItemPickupMenu.bNumSlotsPerPage == NUM_PICKUP_SLOTS && gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
		{
			BltVideoObjectFromIndex( FRAME_BUFFER, gItemPickupMenu.uiPanelVo, 2, sX, sY, VO_BLT_SRCTRANSPARENCY, NULL );
		}
		else
		{
			BltVideoObjectFromIndex( FRAME_BUFFER, gItemPickupMenu.uiPanelVo, 3, sX, sY, VO_BLT_SRCTRANSPARENCY, NULL );
		}

		// Render items....
		sX = ITEMPICK_GRAPHIC_X + gItemPickupMenu.sX;
		sY = ITEMPICK_GRAPHIC_Y + gItemPickupMenu.sY;

		pDestBuf = LockVideoSurface( FRAME_BUFFER, &uiDestPitchBYTES );

		SetFont( ITEMDESC_FONT );
		SetFontBackground( FONT_MCOLOR_BLACK );
		SetFontShadow( ITEMDESC_FONTSHADOW2 );

		for ( cnt = 0; cnt < gItemPickupMenu.bNumSlotsPerPage; cnt++ )
		{
			if ( gItemPickupMenu.ItemPoolSlots[ cnt ] != NULL )
			{
				// Get item to render
				pObject = (gfStealing)? &gpOpponent->inv[gItemPickupMenu.ItemPoolSlots[ cnt ]->iItemIndex]
					:&(gWorldItems[ gItemPickupMenu.ItemPoolSlots[ cnt ]->iItemIndex ].object );
				pItem = &( Item[ pObject->usItem ] );

				usItemTileIndex = GetTileGraphicForItem( pItem );

				// Render
				sX = ITEMPICK_GRAPHIC_X + gItemPickupMenu.sX;

				sCenX = sX;
				sCenY = sY;

        // ATE: Adjust to basic shade.....
    		gTileDatabase[ usItemTileIndex ].hTileSurface->pShadeCurrent=gTileDatabase[ usItemTileIndex ].hTileSurface->pShades[4];

				//else
				{
					if ( gItemPickupMenu.pfSelectedArray[  cnt + gItemPickupMenu.ubScrollAnchor ] )
					{
						//SetFontForeground( FONT_MCOLOR_LTYELLOW );
						//SetFontShadow( ITEMDESC_FONTSHADOW2 );
						Blt8BPPDataTo16BPPBufferOutline( (UINT16*)pDestBuf, uiDestPitchBYTES, gTileDatabase[ usItemTileIndex ].hTileSurface, sCenX, sCenY, gTileDatabase[ usItemTileIndex ].usRegionIndex, Get16BPPColor( FROMRGB( 255, 255, 0 ) ), TRUE );
					}
					else
					{
						//SetFontForeground( FONT_BLACK );
						//SetFontShadow( ITEMDESC_FONTSHADOW2 );
						Blt8BPPDataTo16BPPBufferOutline( (UINT16*)pDestBuf, uiDestPitchBYTES, gTileDatabase[ usItemTileIndex ].hTileSurface, sCenX, sCenY, gTileDatabase[ usItemTileIndex ].usRegionIndex, 0, FALSE );
					}
        }

        // Draw text.....
      	SetFont( ITEM_FONT );
				if ( pObject->ubNumberOfObjects > 1 )
				{
					SetFontForeground( FONT_GRAY4 );
					SetFontShadow( DEFAULT_SHADOW );

				  sCenX = sX - 4;
				  sCenY = sY + 14;

				  swprintf( pStr, L"%d", pObject->ubNumberOfObjects );

				  VarFindFontRightCoordinates( sCenX, sCenY, 42, 1 , ITEM_FONT, &sFontX, &sFontY, pStr );
				  mprintf_buffer( pDestBuf, uiDestPitchBYTES, ITEM_FONT, sFontX, sFontY, pStr );
				}
      	SetFont( ITEMDESC_FONT );


        // Render attachment symbols
			  if ( ItemHasAttachments( pObject ) )
			  {
				  SetFontForeground( FONT_GREEN );
					SetFontShadow( DEFAULT_SHADOW );

				  sNewY = sCenY + 2;
				  swprintf( pStr, L"*" );

				  // Get length of string
				  uiStringLength=StringPixLength( pStr, ITEM_FONT );

				  sNewX = sCenX + 43 - uiStringLength - 4;

  				mprintf_buffer( pDestBuf, uiDestPitchBYTES, ITEMDESC_FONT, sNewX, sNewY, pStr );
				  //gprintfinvalidate( sNewX, sNewY, pStr );
			  }

			  if((UsingNewInventorySystem() == true))
			  {
				  // CHRISL: Show astrisk for active LBENODE
				  if ( pObject->IsActiveLBE(0))
				  {
					  SetFontForeground( FONT_BLUE );
						SetFontShadow( DEFAULT_SHADOW );

					  sNewY = sCenY + 2;
					  swprintf( pStr, L"*" );

					  // Get length of string
					  uiStringLength=StringPixLength( pStr, ITEM_FONT );

					  sNewX = sCenX + 43 - uiStringLength - 4;

  					mprintf_buffer( pDestBuf, uiDestPitchBYTES, ITEMDESC_FONT, sNewX, sNewY, pStr );
					  //gprintfinvalidate( sNewX, sNewY, pStr );
				  }
			  }

				if ( gItemPickupMenu.bCurSelect == ( cnt + gItemPickupMenu.ubScrollAnchor ) )
				{
					//SetFontForeground( ITEMDESC_FONTSHADOW2 );
					//if ( gItemPickupMenu.pfSelectedArray[  cnt + gItemPickupMenu.ubScrollAnchor ] )
					//{
					//	SetFontForeground( FONT_MCOLOR_LTYELLOW );
					//	SetFontShadow( ITEMDESC_FONTSHADOW2 );
					//}
					//else
					//{
						SetFontForeground( FONT_WHITE );
						SetFontShadow( DEFAULT_SHADOW );
					//}
					// Blt8BPPDataTo16BPPBufferOutline( (UINT16*)pDestBuf, uiDestPitchBYTES, gTileDatabase[ usItemTileIndex ].hTileSurface, sCenX, sCenY, gTileDatabase[ usItemTileIndex ].usRegionIndex, Get16BPPColor( FROMRGB( 255, 0, 0 ) ), TRUE );
					// Blt8BPPDataTo16BPPBufferOutline( (UINT16*)pDestBuf, uiDestPitchBYTES, gTileDatabase[ usItemTileIndex ].hTileSurface, sCenX, sCenY, gTileDatabase[ usItemTileIndex ].usRegionIndex, Get16BPPColor( FROMRGB( 255, 0, 0 ) ), TRUE );
				}
				else
				{
					SetFontForeground( FONT_BLACK );
					SetFontShadow( ITEMDESC_FONTSHADOW2 );
				}

				// Render name
				sCenX = ITEMPICK_TEXT_X + gItemPickupMenu.sX;
				sCenY = ITEMPICK_TEXT_Y + gItemPickupMenu.sY + ( ITEMPICK_TEXT_YSPACE * (INT16)cnt );

				// If we are money...
				if ( Item[ pObject->usItem ].usItemClass == IC_MONEY )
				{
					CHAR16		pStr2[20];
					swprintf( pStr2, L"%ld", (*pObject)[0]->data.money.uiMoneyAmount );
					InsertCommasForDollarFigure( pStr2 );
					InsertDollarSignInToString( pStr2 );

					swprintf( pStr, L"%s (%ls)", ItemNames[ pObject->usItem ], pStr2 );
				}
				else
				{
					swprintf( pStr, L"%s", ShortItemNames[ pObject->usItem ] );
				}
				VarFindFontCenterCoordinates( sCenX, sCenY, ITEMPICK_TEXT_WIDTH, 1 , ITEMDESC_FONT, &sFontX, &sFontY, pStr );
				mprintf_buffer( pDestBuf, uiDestPitchBYTES, ITEMDESC_FONT, sFontX, sFontY, pStr );

				sY += ITEMPICK_GRAPHIC_YSPACE;
			}
		}

		SetFontShadow( DEFAULT_SHADOW );


		UnLockVideoSurface( FRAME_BUFFER );

		InvalidateRegion( gItemPickupMenu.sX, gItemPickupMenu.sY, gItemPickupMenu.sX + gItemPickupMenu.sWidth, gItemPickupMenu.sY + gItemPickupMenu.sHeight );

		gItemPickupMenu.fDirtyLevel = 0;

	}
}


void RemoveItemPickupMenu( )
{
	INT32 cnt;

	if ( gfInItemPickupMenu )
	{
		gfSMDisableForItems = FALSE;

		HandleAnyMercInSquadHasCompatibleStuff( (INT8) CurrentSquad( ), NULL, TRUE );

		UnLockPauseState();
		UnPauseGame();
		// UnPause timers as well....
		PauseTime( FALSE );

		// Unfreese guy!
		gItemPickupMenu.pSoldier->flags.fPauseAllAnimation = FALSE;

		// Remove graphics!
		DeleteVideoObjectFromIndex( gItemPickupMenu.uiPanelVo );

		// Remove buttons
		if ( gItemPickupMenu.bNumSlotsPerPage == NUM_PICKUP_SLOTS && gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
		{
			RemoveButton( gItemPickupMenu.iUpButton );
			RemoveButton( gItemPickupMenu.iDownButton );
		}
		RemoveButton( gItemPickupMenu.iAllButton );
		RemoveButton( gItemPickupMenu.iOKButton );
		RemoveButton( gItemPickupMenu.iCancelButton );

		// Remove button images
		UnloadButtonImage( gItemPickupMenu.iUpButtonImages );
		UnloadButtonImage( gItemPickupMenu.iDownButtonImages );
		UnloadButtonImage( gItemPickupMenu.iAllButtonImages );
		UnloadButtonImage( gItemPickupMenu.iCancelButtonImages );
		UnloadButtonImage( gItemPickupMenu.iOKButtonImages );

		MSYS_RemoveRegion( &(gItemPickupMenu.BackRegions ) );
		MSYS_RemoveRegion( &(gItemPickupMenu.BackRegion ) );

		// Remove regions
		for ( cnt = 0; cnt < gItemPickupMenu.bNumSlotsPerPage; cnt++ )
		{
			MSYS_RemoveRegion( &(gItemPickupMenu.Regions[cnt]));
		}

		// Remove register rect
		if ( gItemPickupMenu.iDirtyRect != -1 )
		{
			//FreeBackgroundRect( gItemPickupMenu.iDirtyRect );
		}

		// Free selection list...
		MemFree( gItemPickupMenu.pfSelectedArray );
		gItemPickupMenu.pfSelectedArray = NULL;


		// Set cursor back to normal mode...
		guiPendingOverrideEvent = A_CHANGE_TO_MOVE;

		// Rerender world
		SetRenderFlags( RENDER_FLAG_FULL );

		gfInItemPickupMenu = FALSE;

		//gfSMDisableForItems = FALSE;
		//EnableButtonsForInItemBox( TRUE );
		EnableSMPanelButtons( TRUE , TRUE );
		gfSMDisableForItems = FALSE;

		fInterfacePanelDirty = DIRTYLEVEL2;

		// Turn off Ignore scrolling
		gfIgnoreScrolling = FALSE;
		DisableTacticalTeamPanelButtons( FALSE );
		gubSelectSMPanelToMerc = gpSMCurrentMerc->ubID;

	}
}


void ItemPickupScrollUp( GUI_BUTTON *btn, INT32 reason )
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
	}
	else if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		SetupPickupPage( (UINT8)( gItemPickupMenu.bScrollPage - 1 ) );
	}
	else if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
	}

}


void ItemPickupScrollDown( GUI_BUTTON *btn, INT32 reason )
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
	}
	else if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		SetupPickupPage( (UINT8)( gItemPickupMenu.bScrollPage + 1 ) );
	}
	else if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
	}
}

void ItemPickupAll( GUI_BUTTON *btn, INT32 reason )
{
	INT32 cnt;


	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
	}
	else if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		gItemPickupMenu.fAllSelected = !gItemPickupMenu.fAllSelected;


		// OK, pickup item....
		//gItemPickupMenu.fHandled = TRUE;
		// Tell our soldier to pickup this item!
		//SoldierGetItemFromWorld( gItemPickupMenu.pSoldier, ITEM_PICKUP_ACTION_ALL, gItemPickupMenu.sGridNo, gItemPickupMenu.bZLevel, NULL );
		for ( cnt = 0; cnt < gItemPickupMenu.ubTotalItems; cnt++ )
		{
			gItemPickupMenu.pfSelectedArray[ cnt ] = gItemPickupMenu.fAllSelected;
		}

		if ( gItemPickupMenu.fAllSelected )
		{
			EnableButton( gItemPickupMenu.iOKButton );
		}
		else
		{
			DisableButton( gItemPickupMenu.iOKButton );
		}

	}
	else if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
	}
}


void ItemPickupOK( GUI_BUTTON *btn, INT32 reason )
{
	UINT16 usLastItem;

	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
	}
	else if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		// OK, pickup item....
		gItemPickupMenu.fHandled = TRUE;

		if (gfStealing)	//jackaians modif
		{
			usLastItem=gpOpponent->inv[HANDPOS].usItem;
			SoldierStealItemFromSoldier( gItemPickupMenu.pSoldier,gpOpponent,gItemPickupMenu.pItemPool, ITEM_PICKUP_SELECTION, gItemPickupMenu.sGridNo, gItemPickupMenu.bZLevel, gItemPickupMenu.pfSelectedArray );
			DeletePool(gItemPickupMenu.pItemPool);
			if ((gpOpponent->inv[HANDPOS].exists() == false ) && (usLastItem!=NOTHING))
				gpOpponent->ReLoadSoldierAnimationDueToHandItemChange( usLastItem, NOTHING );

//			PreventFromTheFreezingBug(gItemPickupMenu.pSoldier);
		}
		else
		{
			// Tell our soldier to pickup this item!
			SoldierGetItemFromWorld( gItemPickupMenu.pSoldier, ITEM_PICKUP_SELECTION, gItemPickupMenu.sGridNo, gItemPickupMenu.bZLevel, gItemPickupMenu.pfSelectedArray );
		}
	}
	else if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
	}
}

void ItemPickupCancel( GUI_BUTTON *btn, INT32 reason )
{

	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
	}
	else if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		// OK, pickup item....
		gItemPickupMenu.fHandled = TRUE;

		// Nonomori: Fix crash-on-cancel by doing this here instead of on the ...LBUTTON_DWN event
		if (gfStealing)		//jackaians modif
		{
			DeletePool(gItemPickupMenu.pItemPool);

//			PreventFromTheFreezingBug(gItemPickupMenu.pSoldier);
		}
	}
	else if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
	}
}


void ItemPickMenuMouseMoveCallback( MOUSE_REGION * pRegion, INT32 iReason )
{
	UINT32					uiItemPos;
	//ITEM_POOL				*pTempItemPool;
	INT32						bPos;
	static					BOOLEAN	bChecked = FALSE;

	uiItemPos = MSYS_GetRegionUserData( pRegion, 0 );


	if (iReason & MSYS_CALLBACK_REASON_MOVE)
	{
		bPos = ( uiItemPos + gItemPickupMenu.ubScrollAnchor );

		if ( bPos < gItemPickupMenu.ubTotalItems )
		{
			// Set current selected guy....
			gItemPickupMenu.bCurSelect = bPos;

			if ( !bChecked )
			{
				// WANNE: There is a big bug in the stealing routine.
				/*
				// Show compatible ammo...
				pTempItemPool = gItemPickupMenu.ItemPoolSlots[ gItemPickupMenu.bCurSelect - gItemPickupMenu.ubScrollAnchor ];

				// Nonomori: Fix crash caused by stealing ammo in a sector with no items loaded.
				// gItemPickupMenu.CompAmmoObject = gWorldItems[ pTempItemPool->iItemIndex ].object;
				if ( gWorldItems && gWorldItems[ pTempItemPool->iItemIndex ].fExists )
				{
					gItemPickupMenu.CompAmmoObject = gWorldItems[ pTempItemPool->iItemIndex ].object ;
				}
				else
				{
					OBJECTTYPE pCompAmmoObject;
					CreateItem( pTempItemPool->iItemIndex, 100, &pCompAmmoObject);
					gItemPickupMenu.CompAmmoObject = pCompAmmoObject;
				}

				// Turn off first...
				HandleAnyMercInSquadHasCompatibleStuff( (INT8) CurrentSquad( ), NULL, TRUE );
				InternalHandleCompatibleAmmoUI( gpSMCurrentMerc, &( gItemPickupMenu.CompAmmoObject ), TRUE );

				// Nonomori: Fix crash caused by stealing ammo in a sector with no items loaded.
				// HandleAnyMercInSquadHasCompatibleStuff( (INT8)CurrentSquad( ), &(gWorldItems[ pTempItemPool->iItemIndex ].object ), FALSE );
				HandleAnyMercInSquadHasCompatibleStuff( (INT8)CurrentSquad( ), pCompAmmoObject, FALSE );
				*/


				SetItemPickupMenuDirty( DIRTYLEVEL2 );

				bChecked = TRUE;
			}
		}
	}
	else if( iReason & MSYS_CALLBACK_REASON_LOST_MOUSE )
	{
		gItemPickupMenu.bCurSelect = 255;

		InternalHandleCompatibleAmmoUI( gpSMCurrentMerc, &( gItemPickupMenu.CompAmmoObject ), FALSE );
		HandleAnyMercInSquadHasCompatibleStuff( (INT8) CurrentSquad( ), NULL, TRUE );

		SetItemPickupMenuDirty( DIRTYLEVEL2 );

		bChecked = FALSE;
	}


}


void ItemPickupBackgroundClick( MOUSE_REGION * pRegion, INT32 iReason )
{
	if (iReason & MSYS_CALLBACK_REASON_RBUTTON_UP)
	{
		// OK, goto team panel....
		ToggleTacticalPanels();
	}
}



void ItemPickMenuMouseClickCallback( MOUSE_REGION * pRegion, INT32 iReason )
{
	INT32				  	uiItemPos;
	UINT8						cnt;
	BOOLEAN					fEnable = FALSE;

	uiItemPos = MSYS_GetRegionUserData( pRegion, 0 );


	if (iReason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		if ( uiItemPos + gItemPickupMenu.ubScrollAnchor < gItemPickupMenu.ubTotalItems )
		{
			// Toggle selection... ONLY IF LEGAL!!
			gItemPickupMenu.pfSelectedArray[ uiItemPos + gItemPickupMenu.ubScrollAnchor ] = !gItemPickupMenu.pfSelectedArray[  uiItemPos + gItemPickupMenu.ubScrollAnchor ];

			// OK, pickup item....
			//gItemPickupMenu.fHandled = TRUE;

			//pTempItemPool = gItemPickupMenu.ItemPoolSlots[ gItemPickupMenu.bCurSelect - gItemPickupMenu.ubScrollAnchor ];

			// Tell our soldier to pickup this item!
			//SoldierGetItemFromWorld( gItemPickupMenu.pSoldier, pTempItemPool->iItemIndex, gItemPickupMenu.sGridNo, gItemPickupMenu.bZLevel );
		}

		// Loop through all and set /unset OK
		for ( cnt = 0; cnt < gItemPickupMenu.ubTotalItems; cnt++ )
		{
			if ( gItemPickupMenu.pfSelectedArray[ cnt ] )
			{
				fEnable = TRUE;
				break;
			}
		}

		if ( fEnable )
		{
			EnableButton( gItemPickupMenu.iOKButton );
		}
		else
		{
			DisableButton( gItemPickupMenu.iOKButton );
		}
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_UP)
	{

	}
}

BOOLEAN HandleItemPickupMenu( )
{

	if ( !gfInItemPickupMenu )
	{
		return( FALSE );
	}

	if ( gItemPickupMenu.fHandled )
	{
		RemoveItemPickupMenu( );
	}

	return( gItemPickupMenu.fHandled );
}


void BtnMoneyButtonCallback(GUI_BUTTON *btn,INT32 reason)
{
	INT8	i;
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_RBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		UINT8	ubButton = (UINT8)MSYS_GetBtnUserData( btn, 0 );

		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		switch( ubButton )
		{
			case M_1000:
				if( gRemoveMoney.uiMoneyRemaining >= 1000 )
				{
					//if the player is removing money from their account, and they are removing more then $20,000
					if( gfAddingMoneyToMercFromPlayersAccount &&  ( gRemoveMoney.uiMoneyRemoving + 1000 ) > MAX_MONEY_PER_SLOT )
					{
						if( guiCurrentScreen == SHOPKEEPER_SCREEN )
							DoMessageBox( MSG_BOX_BASIC_STYLE, gzMoneyWithdrawMessageText[ MONEY_TEXT_WITHDRAW_MORE_THEN_MAXIMUM ], SHOPKEEPER_SCREEN, ( UINT8 )MSG_BOX_FLAG_OK, NULL, NULL );
						else
							DoMessageBox( MSG_BOX_BASIC_STYLE, gzMoneyWithdrawMessageText[ MONEY_TEXT_WITHDRAW_MORE_THEN_MAXIMUM ], GAME_SCREEN, ( UINT8 )MSG_BOX_FLAG_OK, NULL, NULL );
						return;
					}

					gRemoveMoney.uiMoneyRemaining -= 1000;
					gRemoveMoney.uiMoneyRemoving += 1000;
				}
				break;
			case M_100:
				if( gRemoveMoney.uiMoneyRemaining >= 100 )
				{
					//if the player is removing money from their account, and they are removing more then $20,000
					if( gfAddingMoneyToMercFromPlayersAccount &&  ( gRemoveMoney.uiMoneyRemoving + 100 ) > MAX_MONEY_PER_SLOT )
					{
						DoMessageBox( MSG_BOX_BASIC_STYLE, gzMoneyWithdrawMessageText[ MONEY_TEXT_WITHDRAW_MORE_THEN_MAXIMUM ], GAME_SCREEN, ( UINT8 )MSG_BOX_FLAG_OK, NULL, NULL );
						return;
					}

					gRemoveMoney.uiMoneyRemaining -= 100;
					gRemoveMoney.uiMoneyRemoving += 100;
				}
				break;
			case M_10:
				if( gRemoveMoney.uiMoneyRemaining >= 10 )
				{
					//if the player is removing money from their account, and they are removing more then $20,000
					if( gfAddingMoneyToMercFromPlayersAccount &&  ( gRemoveMoney.uiMoneyRemoving + 10 ) > MAX_MONEY_PER_SLOT )
					{
						DoMessageBox( MSG_BOX_BASIC_STYLE, gzMoneyWithdrawMessageText[ MONEY_TEXT_WITHDRAW_MORE_THEN_MAXIMUM ], GAME_SCREEN, ( UINT8 )MSG_BOX_FLAG_OK, NULL, NULL );
						return;
					}

					gRemoveMoney.uiMoneyRemaining -= 10;
					gRemoveMoney.uiMoneyRemoving += 10;
				}
				break;
			case M_DONE:
			{
				RemoveMoney();

				DeleteItemDescriptionBox( );
			}
			break;
		}
		if( ubButton != M_DONE )
		{
			RenderItemDescriptionBox( );
			for( i=0; i<MAX_ATTACHMENTS; i++ )
			{
				MarkAButtonDirty( guiMoneyButtonBtn[ i ] );
			}
		}

		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}


	if(reason & MSYS_CALLBACK_REASON_RBUTTON_UP )
	{
		UINT8	ubButton = (UINT8)MSYS_GetBtnUserData( btn, 0 );

		btn->uiFlags &= (~BUTTON_CLICKED_ON );


		switch( ubButton )
		{
			case M_1000:
				if( gRemoveMoney.uiMoneyRemoving >= 1000 )
				{
					gRemoveMoney.uiMoneyRemaining += 1000;
					gRemoveMoney.uiMoneyRemoving -= 1000;
				}
				break;
			case M_100:
				if( gRemoveMoney.uiMoneyRemoving >= 100 )
				{
					gRemoveMoney.uiMoneyRemaining += 100;
					gRemoveMoney.uiMoneyRemoving -= 100;
				}
				break;
			case M_10:
				if( gRemoveMoney.uiMoneyRemoving >= 10 )
				{
					gRemoveMoney.uiMoneyRemaining += 10;
					gRemoveMoney.uiMoneyRemoving -= 10;
				}
				break;
		}

		RenderItemDescriptionBox( );
		for( i=0; i<MAX_ATTACHMENTS; i++ )
		{
			MarkAButtonDirty( guiMoneyButtonBtn[ i ] );
		}

		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
}

void RemoveMoney()
{
	if( gRemoveMoney.uiMoneyRemoving != 0 )
	{
		//CHRISL: If what we have in the cursor is more money, just add to what we have in the cursor.
		if (gpItemPointer != NULL && gpItemPointer->exists() == true && gpItemPointer->usItem != MONEY) {
			//ADB oops, let's not overwrite what's on the cursor!
			ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"Unable to split money due to having an item on your cursor." );

			//after this returns it will call DeleteItemDescriptionBox which will totally destroy the remaining money
			//if the uiMoneyRemaining is 0, so reset it, because we aren't moving anything!
			gRemoveMoney.uiMoneyRemaining = gRemoveMoney.uiTotalAmount;
			gRemoveMoney.uiMoneyRemoving = 0;

			return;
		}
		//if we are in the shop keeper interface
		if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
		{
			INVENTORY_IN_SLOT InvSlot;

			InvSlot.fActive = TRUE;
			InvSlot.sItemIndex = MONEY;
			InvSlot.bSlotIdInOtherLocation = -1;

			//Create an item to get the money that is being removed
			CreateMoney(gRemoveMoney.uiMoneyRemoving, &InvSlot.ItemObject );

			//Set the amount thast is being removed
			InvSlot.ubIdOfMercWhoOwnsTheItem = gpItemDescSoldier->ubProfile;

			//if we are removing money from the players account
			if( gfAddingMoneyToMercFromPlayersAccount )
			{
				(*gpItemDescObject)[0]->data.money.uiMoneyAmount = gRemoveMoney.uiMoneyRemoving;

				//take the money from the player
				AddTransactionToPlayersBook ( TRANSFER_FUNDS_TO_MERC, gpSMCurrentMerc->ubProfile, GetWorldTotalMin() , -(INT32)( gRemoveMoney.uiMoneyRemoving ) );
			}
			else {
				//Remove the money from the money in the pocket
				(*gpItemDescObject)[0]->data.money.uiMoneyAmount = gRemoveMoney.uiMoneyRemaining;
			}

			gMoveingItem = InvSlot;

			gItemPointer = InvSlot.ItemObject;
			gpItemPointer = &gItemPointer;
			gpItemPointerSoldier = gpSMCurrentMerc;

			// Set mouse
			SetSkiCursor( EXTERN_CURSOR );

			//Restrict the cursor to the proper area
			RestrictSkiMouseCursor();
		}
		else
		{
			if(gpItemPointer->exists() == true)
			{
				CreateMoney( gRemoveMoney.uiMoneyRemoving, &gTempObject );
				gItemPointer.AddObjectsToStack(gTempObject, -1, 0, NUM_INV_SLOTS, MAX_OBJECTS_PER_SLOT);
				gpItemPointer = &gItemPointer;
			}
			else
			{
				CreateMoney( gRemoveMoney.uiMoneyRemoving, &gItemPointer );
				gpItemPointer = &gItemPointer;
			}
			//Asign the soldier to be the currently selected soldier
			gpItemPointerSoldier = gpItemDescSoldier;

			//Remove the money from the money in the pocket
			//if we are removing money from the players account
			if( gfAddingMoneyToMercFromPlayersAccount )
			{
				(*gpItemDescObject)[0]->data.money.uiMoneyAmount = gRemoveMoney.uiMoneyRemoving;

				//take the money from the player
				AddTransactionToPlayersBook ( TRANSFER_FUNDS_TO_MERC, gpSMCurrentMerc->ubProfile, GetWorldTotalMin() , -(INT32)(gRemoveMoney.uiMoneyRemoving) );
			}
			else
				(*gpItemDescObject)[0]->data.money.uiMoneyAmount = gRemoveMoney.uiMoneyRemaining;



			if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
			{
				// Set mouse
				guiExternVo = GetInterfaceGraphicForItem( &(Item[ gpItemPointer->usItem ]) );
				gusExternVoSubIndex = Item[ gpItemPointer->usItem ].ubGraphicNum;

				MSYS_ChangeRegionCursor( &gMPanelRegion , EXTERN_CURSOR );
				MSYS_SetCurrentCursor( EXTERN_CURSOR );
				fMapInventoryItem=TRUE;
				fTeamPanelDirty=TRUE;
			}

		}
	}

//	if( gfAddingMoneyToMercFromPlayersAccount )
//		gfAddingMoneyToMercFromPlayersAccount = FALSE;
}


void GetHelpTextForItem( STR16 pzStr, OBJECTTYPE *pObject, SOLDIERTYPE *pSoldier, int subObject )
{
	CHAR16	pStr[ 250 ];
	UINT16	usItem = pObject->usItem;
	INT32	iNumAttachments = 0;
	INT16	sValue;
	FLOAT	fWeight;

	if( pSoldier != NULL )
	{
		if ( pSoldier->flags.uiStatusFlags & SOLDIER_DEAD )
		{
			swprintf( pStr, L"" );
			swprintf( pzStr, L"%s", pStr );
			return;
		}
	}

/* 2007-05-27, Sergeant_Kolja: code temporarily added for tracking the 
   SKI Tony inventory crash.
   Remove when fixed!
 */
# if defined( _DEBUG )
	if ( ((*pObject)[0]->data.gun.ubGunAmmoType >= MAXITEMS) )
  {
    DebugMsg(TOPIC_JA2, DBG_LEVEL_1, String( "corrupted pObject (%S) found in GetHelpTextForItem()", (usItem<MAXITEMS) ? Item[usItem].szItemName : L"???" ));
  	ScreenMsg( MSG_FONT_RED, MSG_DEBUG, L"corrupted pObject (%s) found in GetHelpTextForItem()"    , (usItem<MAXITEMS) ? Item[usItem].szItemName : L"???" );
    DebugBreak();
    AssertMsg( 0, "GetHelpTextForItem() would crash" );
  }
#endif
    
	if ( pObject->exists() == true )
	{
		// Retrieve the status of the items
		//CHRISL: If looking at an item in stack popup, show just that item
		//CHRISL: Also, determine weight differently if we're looking at a single item in a stack
		if(subObject == -1){
			// Find the minimum status value - not just the first one
			sValue = (*pObject)[0]->data.objectStatus;

			for(INT16 i = 1; i < pObject->ubNumberOfObjects; i++){
				if((*pObject)[ i ]->data.objectStatus < sValue)
				{
					sValue = (*pObject)[ i ]->data.objectStatus;
				}
			}
			//get item weight
			fWeight = (float)(CalculateObjectWeight( pObject )) / 10;
			subObject = 0;
		}
		else {
			sValue = (*pObject)[subObject]->data.objectStatus;
			fWeight = (float)(pObject->GetWeightOfObjectInStack(subObject)) / 10;
		}

		if ( !gGameSettings.fOptions[ TOPTION_USE_METRIC_SYSTEM ] ) // metric units not enabled
		{
			fWeight = fWeight * 2.2f;
		}

		if ( fWeight < 0.1 )
		{
			fWeight = 0.1f;
		}

		switch( Item[ usItem ].usItemClass )
		{
		case MONEY:
			//Money
			{
				swprintf( pStr, L"%ld", (*pObject)[subObject]->data.money.uiMoneyAmount );
				InsertCommasForDollarFigure( pStr );
				InsertDollarSignInToString( pStr );
			}
			break;

		case IC_MONEY:
			// alternate money like silver or gold
			//if ( Item[ usItem ].usItemClass == IC_MONEY )
			{
				CHAR16		pStr2[20];
				swprintf( pStr2, L"%ld", (*pObject)[subObject]->data.money.uiMoneyAmount );
				InsertCommasForDollarFigure( pStr2 );
				InsertDollarSignInToString( pStr2 );

				swprintf( pStr, L"%s (%ls)", ItemNames[ usItem ], pStr2 );
			}
			break;

		case IC_GUN:
			{
				//Calculate AP's
				CHAR16 apStr[20];
				CHAR16 apStr2[20];
				UINT8 ubAttackAPs = BaseAPsToShootOrStab( DEFAULT_APS, DEFAULT_AIMSKILL, pObject );

				if ( Weapon[ usItem ].NoSemiAuto )
				{
					swprintf( apStr, L"-" );
				}
				else
				{
					swprintf( apStr, L"%d", ubAttackAPs );
				}

				if (GetShotsPerBurst(pObject) > 0)
				{
					swprintf( apStr2, L" / %d", ubAttackAPs + CalcAPsToBurst( DEFAULT_APS, pObject ) );
					wcscat( apStr, apStr2 );
				}
				else
				{
					wcscat( apStr, L" / -" );
				}

				if (GetAutofireShotsPerFiveAPs(pObject) > 0)
				{
					swprintf( apStr2, L" / %d", ubAttackAPs + CalcAPsToAutofire( DEFAULT_APS, pObject, 3 ) );
					wcscat( apStr, apStr2 );
				}
				else
				{
					wcscat( apStr, L" / -" );
				}

				//Info for weapons
				swprintf( pStr, L"%s (%s) [%d%%]\n%s %d\n%s %d\n%s %d (%d)\n%s %s\n%s %1.1f %s",
					ItemNames[ usItem ],
					AmmoCaliber[ Weapon[ usItem ].ubCalibre ],
					sValue,
					gWeaponStatsDesc[ 9 ],		//Accuracy String
					Weapon[ usItem ].bAccuracy,
					gWeaponStatsDesc[ 11 ],		//Damage String
					GetDamage(pObject),
					gWeaponStatsDesc[ 10 ],		//Range String
					gGameSettings.fOptions[ TOPTION_SHOW_WEAPON_RANGE_IN_TILES ] ? GunRange( pObject )/10 : GunRange( pObject ),			//Modified Range
					gGameSettings.fOptions[ TOPTION_SHOW_WEAPON_RANGE_IN_TILES ] ? Weapon[ usItem ].usRange/10 : Weapon[ usItem ].usRange,	//Gun Range
					gWeaponStatsDesc[ 5 ],		//AP String
					apStr,						//AP's
					gWeaponStatsDesc[ 12 ],		//Weight String
					fWeight,					//Weight
					GetWeightUnitString()		//Weight units
					);
			}
			break;

		case IC_LAUNCHER:
			{
				//Calculate AP's
				CHAR16 apStr[20];
				CHAR16 apStr2[20];
				UINT8 ubAttackAPs = BaseAPsToShootOrStab( DEFAULT_APS, DEFAULT_AIMSKILL, pObject );

				swprintf( apStr, L"%d", ubAttackAPs );

				if (GetShotsPerBurst(pObject) > 0)
				{
					swprintf( apStr2, L" / %d", ubAttackAPs + CalcAPsToBurst( DEFAULT_APS, pObject ) );
					wcscat( apStr, apStr2 );
				}
				else
				{
					wcscat( apStr, L" / -" );
				}

				if (GetAutofireShotsPerFiveAPs(pObject) > 0)
				{
					swprintf( apStr2, L" / %d", ubAttackAPs + CalcAPsToAutofire( DEFAULT_APS, pObject, 3 ) );
					wcscat( apStr, apStr2 );
				}
				else
				{
					wcscat( apStr, L" / -" );
				}

				//Info for weapons
				swprintf( pStr, L"%s [%d%%]\n%s %d\n%s %d\n%s %d (%d)\n%s %s\n%s %1.1f %s",
					ItemNames[ usItem ],
					sValue,
					gWeaponStatsDesc[ 9 ],		//Accuracy String
					Weapon[ usItem ].bAccuracy,
					gWeaponStatsDesc[ 11 ],		//Damage String
					GetDamage(pObject),
					gWeaponStatsDesc[ 10 ],		//Range String
					gGameSettings.fOptions[ TOPTION_SHOW_WEAPON_RANGE_IN_TILES ] ? GunRange( pObject )/10 : GunRange( pObject ),			//Modified Range
					gGameSettings.fOptions[ TOPTION_SHOW_WEAPON_RANGE_IN_TILES ] ? Weapon[ usItem ].usRange/10 : Weapon[ usItem ].usRange,	//Gun Range
					gWeaponStatsDesc[ 5 ],		//AP String
					apStr,						//AP's
					gWeaponStatsDesc[ 12 ],		//Weight String
					fWeight,					//Weight
					GetWeightUnitString()		//Weight units
					);
			}
			break;

		case IC_BLADE:
		case IC_THROWING_KNIFE:
		case IC_PUNCH:
			{
				swprintf( pStr, L"%s [%d%%]\n%s %d\n%s %d\n%s %1.1f %s",
					ItemNames[ usItem ],
					sValue,
					gWeaponStatsDesc[ 11 ],					//Damage String
					GetDamage(pObject), 					//Melee damage
					gWeaponStatsDesc[ 5 ],					//AP String
					BaseAPsToShootOrStab( DEFAULT_APS, DEFAULT_AIMSKILL, pObject ), //AP's
					gWeaponStatsDesc[ 12 ],					//Weight String
					fWeight,								//Weight
					GetWeightUnitString()					//Weight units
					);
			}
			break;

		case IC_AMMO:
			{
				// The next is for ammunition which gets the measurement 'rnds'
				swprintf( pStr, L"%s [%d rnds]\n%s %1.1f %s",
					ItemNames[ usItem ],		//Item long name
					(*pObject)[subObject]->data.ubShotsLeft,	//Shots left
					gWeaponStatsDesc[ 12 ],		//Weight String
					fWeight,					//Weight
					GetWeightUnitString()		//Weight units
					);

				//Lal: do not delete, commented out for next version
				//swprintf( pStr, L"%s %s %s %d [%d rnds]\n%s %1.1f %s",
				//	AmmoCaliber[ Magazine[ Item[usItem].ubClassIndex ].ubCalibre ],			//Ammo calibre
				//	AmmoTypes[Magazine[ Item[usItem].ubClassIndex ].ubAmmoType].ammoName,	//Ammo type
				//	MagNames[Magazine[ Item[usItem].ubClassIndex ].ubMagType],				//Magazine type
				//	Magazine[ Item[usItem].ubClassIndex ].ubMagSize,						//Magazine capacity
				//	(*pObject)[0]->data.ubShotsLeft,	//Shots left
				//	gWeaponStatsDesc[ 12 ],		//Weight String
				//	fWeight,					//Weight
				//	GetWeightUnitString()		//Weight units
				//	);
			}
			break;

		case IC_GRENADE:
		case IC_BOMB:
			// explosives
			{
				UINT16 explDamage = (UINT16)( Explosive[Item[ usItem ].ubClassIndex].ubDamage + ( (double) Explosive[Item[ usItem ].ubClassIndex].ubDamage / 100) * gGameExternalOptions.ubExplosivesDamageMultiplier );
				UINT16 explStunDamage = (UINT16)( Explosive[Item[ usItem ].ubClassIndex].ubStunDamage + ( (double) Explosive[Item[ usItem ].ubClassIndex].ubStunDamage / 100) * gGameExternalOptions.ubExplosivesDamageMultiplier );

				swprintf( pStr, L"%s [%d%%]\n%s %d\n%s %d\n%s %1.1f %s",
					ItemNames[ usItem ],
					sValue,
					gWeaponStatsDesc[ 11 ],		//Damage String
					explDamage,
					gWeaponStatsDesc[ 13 ],		//Stun Damage String
					explStunDamage,				//Stun Damage
					gWeaponStatsDesc[ 12 ],		//Weight String
					fWeight,					//Weight
					GetWeightUnitString()		//Weight units
					);
			}
			break;

		case IC_ARMOUR:
			{
				//Armor
				INT32 iProtection = EffectiveArmour( pObject );

				switch( Armour[ Item[ usItem ].ubClassIndex ].ubArmourClass )
				{
				case( ARMOURCLASS_HELMET ):
					iProtection = 15 * iProtection / Armour[ Item[ SPECTRA_HELMET_18 ].ubClassIndex ].ubProtection;
					break;

				case( ARMOURCLASS_VEST ):
					iProtection = 65 * iProtection / ( Armour[ Item[ SPECTRA_VEST_18 ].ubClassIndex ].ubProtection + Armour[ Item[ CERAMIC_PLATES ].ubClassIndex ].ubProtection );
					break;

				case( ARMOURCLASS_LEGGINGS ):
					iProtection = 25 * iProtection / Armour[ Item[ SPECTRA_LEGGINGS_18 ].ubClassIndex ].ubProtection;
					break;

				case( ARMOURCLASS_PLATE ):
					iProtection = 65 * iProtection / ( Armour[ Item[ CERAMIC_PLATES ].ubClassIndex ].ubProtection );
					break;
				}

				swprintf( pStr, L"%s [%d%%]\n%s %d%% (%d/%d)\n%s %d%%\n%s %1.1f %s",
					ItemNames[ usItem ],		//Item long name
					sValue,						//Item condition
					pInvPanelTitleStrings[ 4 ],	//Protection string
					iProtection,				//Protection rating in % based on best armor
					Armour[ Item[ usItem ].ubClassIndex ].ubProtection, //Protection (raw data)
					Armour[ Item[ usItem ].ubClassIndex ].ubProtection * sValue / 100,
					pInvPanelTitleStrings[ 3 ],	//Camo string
					GetCamoBonus(pObject)+GetUrbanCamoBonus(pObject)+GetDesertCamoBonus(pObject)+GetSnowCamoBonus(pObject),	//Camo bonus
					gWeaponStatsDesc[ 12 ],		//Weight string
					fWeight,					//Weight
					GetWeightUnitString()		//Weight units
					);
			}
			break;


		case IC_MISC:
		case IC_MEDKIT:
		case IC_KIT:
		case IC_FACE:
		default:
			{
				// The final, and typical case, is that of an item with a percent status
				swprintf( pStr, L"%s [%d%%]\n%s %1.1f %s",
					ItemNames[ usItem ],		//Item long name
					sValue,						//Item condition
					gWeaponStatsDesc[ 12 ],		//Weight String
					fWeight,					//Weight
					GetWeightUnitString()		//Weight units
					);
			}
			break;
		}


		// Fingerprint ID (Soldier Name)
		if ( ( Item[pObject->usItem].fingerprintid ) && (*pObject)[subObject]->data.ubImprintID < NO_PROFILE )
		{
			CHAR16		pStr2[20];
			swprintf( pStr2, L" [%s]", gMercProfiles[ (*pObject)[subObject]->data.ubImprintID ].zNickname );
			wcscat( pStr, pStr2 );
		}


		// Add attachment string....
		for (attachmentList::iterator iter = (*pObject)[subObject]->attachments.begin(); iter != (*pObject)[subObject]->attachments.end(); ++iter) {
			iNumAttachments++;

			if ( iNumAttachments == 1 )
			{
				wcscat( pStr, L"\n[" );
			}
			else
			{
				wcscat( pStr, L", " );
			}

			wcscat( pStr, ItemNames[ iter->usItem ] );
		}

		if ( iNumAttachments > 0 )
		{
			wcscat( pStr, pMessageStrings[ MSG_END_ATTACHMENT_LIST ] );
		}

	}
	else
	{
		swprintf( pStr, L"" );
	}

	// Copy over...
	swprintf( pzStr, L"%s", pStr );
}






void CancelItemPointer( )
{
	// ATE: If we have an item pointer end it!
	if ( gpItemPointer != NULL )
	{
		if ( gbItemPointerSrcSlot != NO_SLOT )
		{
			// Place it back in our hands!
			PlaceObject( gpItemPointerSoldier, gbItemPointerSrcSlot, gpItemPointer );

			// ATE: This could potnetially swap!
			// Make sure # of items is 0, if not, auto place somewhere else...
			if ( gpItemPointer->exists() == true )
			{
				if ( !AutoPlaceObject( gpItemPointerSoldier, gpItemPointer, FALSE ) )
				{
					// Alright, place of the friggen ground!
					AddItemToPool( gpItemPointerSoldier->sGridNo, gpItemPointer, 1, gpItemPointerSoldier->pathing.bLevel, 0 , -1 );
					NotifySoldiersToLookforItems( );
				}
			}
		}
		else
		{
			// We drop it here.....
			AddItemToPool( gpItemPointerSoldier->sGridNo, gpItemPointer, 1, gpItemPointerSoldier->pathing.bLevel, 0 , -1 );
			NotifySoldiersToLookforItems( );
		}
		EndItemPointer( );
	}
}


BOOLEAN LoadItemCursorFromSavedGame( HWFILE hFile )
{
	ITEM_CURSOR_SAVE_INFO		SaveStruct;

	// Load structure
	if ( !SaveStruct.Load(hFile) )
	{
		return( FALSE );
	}

	// Now set things up.....
	// Copy object
	gItemPointer = (SaveStruct.ItemPointerInfo);

	// Copy soldier ID
	if ( SaveStruct.ubSoldierID == NOBODY )
	{
		gpItemPointerSoldier = NULL;
	}
	else
	{
		gpItemPointerSoldier = MercPtrs[ SaveStruct.ubSoldierID ];
	}

	// Inv slot
	gbItemPointerSrcSlot = SaveStruct.ubInvSlot;

	// Boolean
	if ( SaveStruct.fCursorActive )
	{
		gpItemPointer = &( gItemPointer );
		ReEvaluateDisabledINVPanelButtons( );
	}
	else
	{
		gpItemPointer = NULL;
	}

	return( TRUE );
}

BOOLEAN SaveItemCursorToSavedGame( HWFILE hFile )
{
	ITEM_CURSOR_SAVE_INFO		SaveStruct;

	// Setup structure;
	SaveStruct.ItemPointerInfo = gItemPointer;

	// Soldier
	if ( gpItemPointerSoldier != NULL )
	{
		SaveStruct.ubSoldierID = gpItemPointerSoldier->ubID;
	}
	else
	{
		SaveStruct.ubSoldierID = NOBODY;
	}

	// INv slot
	SaveStruct.ubInvSlot = gbItemPointerSrcSlot;

	// Boolean
	if ( gpItemPointer != NULL )
	{
		SaveStruct.fCursorActive = TRUE;
	}
	else
	{
		SaveStruct.fCursorActive = FALSE;
	}

	// save locations of watched points
	if( !SaveStruct.Save(hFile) )
	{
		return( FALSE );
	}

	// All done...

	return( TRUE );
}



void UpdateItemHatches()
{
	SOLDIERTYPE *pSoldier = NULL;

  if ( guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
  {
		if ( fShowInventoryFlag && bSelectedInfoChar >= 0 )
		{
			pSoldier = MercPtrs[ gCharactersList[ bSelectedInfoChar ].usSolID ];
		}
	}
	else
	{
		pSoldier = gpSMCurrentMerc;
	}

	if ( pSoldier != NULL )
	{
		ReevaluateItemHatches( pSoldier, ( BOOLEAN ) ( gpItemPointer == NULL ) );
	}
}

/**
 * jackaians: copied from InitializeItemPickupMenu
 */
BOOLEAN InitializeStealItemPickupMenu( SOLDIERTYPE *pSoldier, SOLDIERTYPE *pOpponent, ITEM_POOL *pItemPool, UINT8 ubCount)
{
  VOBJECT_DESC		VObjectDesc;
	CHAR8			ubString[48];
	INT16			sCenX, sCenY, sX, sY, sCenterYVal;
	INT8 bZLevel	=pOpponent->pathing.bLevel;
	INT16 sGridNo	=pOpponent->sGridNo;
	INT32			cnt;
	gpOpponent		=pOpponent;
	gfStealing		=TRUE;

	// Erase other menus....
	EraseInterfaceMenus( TRUE );

	// Make sure menu is located if not on screen
	LocateSoldier( pOpponent->ubID, FALSE );

	gItemPickupMenu.initialize();

	//Set item pool value
	gItemPickupMenu.pItemPool	= pItemPool;

	InterruptTime();
	PauseGame();
	LockPauseState( 18 );
	// Pause timers as well....
	PauseTime( TRUE );

	// Alrighty, cancel lock UI if we havn't done so already
	UnSetUIBusy( pSoldier->ubID );

	// Change to INV panel if not there already...
	gfSwitchPanel = TRUE;
	gbNewPanel = SM_PANEL;
	gubNewPanelParam = (UINT8)pSoldier->ubID;

	gItemPickupMenu.ubTotalItems = ubCount;

	// Determine # of slots per page
	if ( gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
	{
		gItemPickupMenu.bNumSlotsPerPage = NUM_PICKUP_SLOTS;
	}
	else
	{
		gItemPickupMenu.bNumSlotsPerPage = gItemPickupMenu.ubTotalItems;
	}

	VObjectDesc.fCreateFlags = VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\itembox.sti", VObjectDesc.ImageFile);
	CHECKF( AddVideoObject( &VObjectDesc, &(gItemPickupMenu.uiPanelVo) ) );

	// Memalloc selection array...
	 gItemPickupMenu.pfSelectedArray = (BOOLEAN *)MemAlloc(( sizeof( UINT8 ) * gItemPickupMenu.ubTotalItems ) );
	// seto to 0
	memset( gItemPickupMenu.pfSelectedArray, 0, ( sizeof( UINT8 ) * gItemPickupMenu.ubTotalItems ) );

	// Calcualate dimensions
	CalculateItemPickupMenuDimensions( );

	// Get XY
	{
		// First get mouse xy screen location
		if( sGridNo != NOWHERE )
		{
			sX = gusMouseXPos;
			sY = gusMouseYPos;
		}
		else
		{
			 sX = 0;
			 sY = 0;
		}

		// CHECK FOR LEFT/RIGHT
		if ( ( sX + gItemPickupMenu.sWidth ) > SCREEN_WIDTH )
		{
			sX = SCREEN_WIDTH - gItemPickupMenu.sWidth - ITEMPICK_START_X_OFFSET;
		}
		else
		{
			sX = sX + ITEMPICK_START_X_OFFSET;
		}

		// Now check for top
		// Center in the y
		sCenterYVal = gItemPickupMenu.sHeight / 2;

		sY -= sCenterYVal;

		if ( sY < gsVIEWPORT_WINDOW_START_Y )
		{
			sY = gsVIEWPORT_WINDOW_START_Y;
		}

		// Check for bottom
		if ( ( sY + gItemPickupMenu.sHeight ) > (SCREEN_HEIGHT - INV_INTERFACE_HEIGHT) )
		{
			sY = (SCREEN_HEIGHT - INV_INTERFACE_HEIGHT) - gItemPickupMenu.sHeight;
		}

	}

	// Set some values
	gItemPickupMenu.sX				= sX;
	gItemPickupMenu.sY				= sY;
	gItemPickupMenu.bCurSelect		= 0;
	gItemPickupMenu.pSoldier		= pSoldier;
	gItemPickupMenu.fHandled		= FALSE;
	gItemPickupMenu.sGridNo			= sGridNo;
	gItemPickupMenu.bZLevel			= bZLevel;
	gItemPickupMenu.fAtLeastOneSelected = FALSE;
	gItemPickupMenu.fAllSelected	= FALSE;

	//Load images for buttons
	FilenameForBPP("INTERFACE\\itembox.sti", ubString );
	gItemPickupMenu.iUpButtonImages			= LoadButtonImage( ubString, -1,5,-1,10,-1 );
	gItemPickupMenu.iDownButtonImages		=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 7, -1, 12, -1 );
	gItemPickupMenu.iAllButtonImages		=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 6, -1,11, -1 );
	gItemPickupMenu.iCancelButtonImages		=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 8, -1, 13, -1 );
	gItemPickupMenu.iOKButtonImages			=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 4, -1, 9, -1 );


	// Build a mouse region here that is over any others.....
	/*MSYS_DefineRegion( &(gItemPickupMenu.BackRegion ), (INT16)( 532 ), (INT16)( 367 ), (INT16)( 640 ),(INT16)( 480 ), MSYS_PRIORITY_HIGHEST,
						 CURSOR_NORMAL, MSYS_NO_CALLBACK, MSYS_NO_CALLBACK ); */

	// Build a mouse region here that is over any others.....
	MSYS_DefineRegion( &(gItemPickupMenu.BackRegion ), (INT16)( iScreenWidthOffset + 532 ), (INT16)( iScreenHeightOffset + 367 ), (INT16)( SCREEN_WIDTH ),(INT16)( SCREEN_HEIGHT ), MSYS_PRIORITY_HIGHEST,
						 CURSOR_NORMAL, MSYS_NO_CALLBACK, MSYS_NO_CALLBACK );

	// Add region
	MSYS_AddRegion( &(gItemPickupMenu.BackRegion ) );


	// Build a mouse region here that is over any others.....
	MSYS_DefineRegion( &(gItemPickupMenu.BackRegions ), (INT16)(gItemPickupMenu.sX ), (INT16)(gItemPickupMenu.sY), (INT16)(gItemPickupMenu.sX + gItemPickupMenu.sWidth ),(INT16)( gItemPickupMenu.sY + gItemPickupMenu.sHeight ), MSYS_PRIORITY_HIGHEST,
						 CURSOR_NORMAL, MSYS_NO_CALLBACK, MSYS_NO_CALLBACK );
	// Add region
	MSYS_AddRegion( &(gItemPickupMenu.BackRegions ) );


	// Create buttons
	if ( gItemPickupMenu.bNumSlotsPerPage == NUM_PICKUP_SLOTS && gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
	{
		gItemPickupMenu.iUpButton	= QuickCreateButton( gItemPickupMenu.iUpButtonImages, (INT16)(sX + ITEMPICK_UP_X), (INT16)(sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_UP_Y),
	 									 BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
	 									 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemPickupScrollUp );

		SetButtonFastHelpText( gItemPickupMenu.iUpButton, ItemPickupHelpPopup[ 1 ] );


		gItemPickupMenu.iDownButton	= QuickCreateButton( gItemPickupMenu.iDownButtonImages, (INT16)(sX + ITEMPICK_DOWN_X), (INT16)(sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_DOWN_Y),
	 									 BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
	 									 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemPickupScrollDown );

		SetButtonFastHelpText( gItemPickupMenu.iDownButton, ItemPickupHelpPopup[ 3 ] );

	}


	gItemPickupMenu.iOKButton	= QuickCreateButton( gItemPickupMenu.iOKButtonImages, (INT16)(sX + ITEMPICK_OK_X), (INT16)(sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_OK_Y),
	 									 BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
	 									 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemPickupOK );
	SetButtonFastHelpText( gItemPickupMenu.iOKButton, ItemPickupHelpPopup[ 0 ] );


	gItemPickupMenu.iAllButton	= QuickCreateButton( gItemPickupMenu.iAllButtonImages, (INT16)(sX + ITEMPICK_ALL_X), (INT16)(sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_ALL_Y),
	 									 BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
	 									 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemPickupAll );
	SetButtonFastHelpText( gItemPickupMenu.iAllButton, ItemPickupHelpPopup[ 2 ] );

	gItemPickupMenu.iCancelButton	= QuickCreateButton( gItemPickupMenu.iCancelButtonImages, (INT16)(sX + ITEMPICK_CANCEL_X), (INT16)(sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_CANCEL_Y),
	 									 BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
	 									 DEFAULT_MOVE_CALLBACK, (GUI_CALLBACK)ItemPickupCancel );
	SetButtonFastHelpText( gItemPickupMenu.iCancelButton, ItemPickupHelpPopup[ 4 ] );


	DisableButton( gItemPickupMenu.iOKButton );



	// Create regions...
	sCenX = gItemPickupMenu.sX;
	sCenY = gItemPickupMenu.sY + ITEMPICK_GRAPHIC_Y;

	for ( cnt = 0; cnt < gItemPickupMenu.bNumSlotsPerPage; cnt++ )
	{
		// Build a mouse region here that is over any others.....
		MSYS_DefineRegion( &(gItemPickupMenu.Regions[cnt]), (INT16)(sCenX ), (INT16)(sCenY + 1), (INT16)(sCenX + gItemPickupMenu.sWidth ),(INT16)( sCenY + ITEMPICK_GRAPHIC_YSPACE ), MSYS_PRIORITY_HIGHEST,
							 CURSOR_NORMAL, ItemPickMenuMouseMoveCallback, ItemPickMenuMouseClickCallback );
		// Add region
		MSYS_AddRegion( &(gItemPickupMenu.Regions[cnt]) );
		MSYS_SetRegionUserData( &(gItemPickupMenu.Regions[cnt]), 0, cnt );

		sCenY += ITEMPICK_GRAPHIC_YSPACE;
	}

	//Save dirty rect
	//gItemPickupMenu.iDirtyRect = RegisterBackgroundRect( BGND_FLAG_PERMANENT | BGND_FLAG_SAVERECT, NULL, gItemPickupMenu.sX, gItemPickupMenu.sY, (INT16)(gItemPickupMenu.sX + gItemPickupMenu.sWidth ) , (INT16)(gItemPickupMenu.sY + gItemPickupMenu.sHeight ) );


	SetupPickupPage(0);
	gfInItemPickupMenu = TRUE;

	// Ignore scrolling
	gfIgnoreScrolling = TRUE;

	HandleAnyMercInSquadHasCompatibleStuff( (INT8) CurrentSquad( ), NULL, TRUE );
	gubSelectSMPanelToMerc = pSoldier->ubID;
	ReEvaluateDisabledINVPanelButtons( );
	DisableTacticalTeamPanelButtons( TRUE );

	//gfSMDisableForItems = TRUE;
	return( TRUE );

}
void DeletePool(ITEM_POOL *pItemPool)
{
	ITEM_POOL *pItemPoolToDelete;
	while(pItemPool!=NULL)
	{
		pItemPoolToDelete=pItemPool;
		pItemPool=pItemPool->pNext;
		MemFree(pItemPoolToDelete);
	}
}
