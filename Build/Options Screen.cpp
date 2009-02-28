#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
#else
	#include	"Types.h"
	#include	"Options Screen.h"
	#include	"Video.h"
	#include	"Font Control.h"
	#include	"Game Clock.h"
	#include	"Render Dirty.h"
	#include	"Text Input.h"
	#include	"WordWrap.h"
	#include	"SaveLoadScreen.h"
	#include	"Render Dirty.h"
	#include	"WordWrap.h"
	#include	"WCheck.h"
	#include	"Utilities.h"
	#include	"Slider.h"
	#include	"Debug.h"
	#include	"Music Control.h"
	#include	"Sound Control.h"
	#include	"soundman.h"
	#include	"Ambient Control.h"
	#include	"Worlddat.h"
	#include	"Worlddef.h"
	#include	"GameSettings.h"
	#include	"Game Init.h"
	#include	"English.h"
	#include	"Overhead.h"
	#include	"Gap.h"
	#include	"Cursors.h"
	#include	"SysUtil.h"
	#include	"Exit Grids.h"
	#include	"Text.h"
	#include	"Interface Control.h"
	#include	"Message.h"
	#include	"Language Defines.h"
	#include "Multi Language Graphic Utils.h"
	#include "Map Information.h"
	#include "SmokeEffects.h"
#endif

#include		"line.h" // arynn : Debug Options Screen
#include		"connect.h"
#include		"WorldMan.h"

/////////////////////////////////
//
//	Defines
//
/////////////////////////////////

#define	OPT_MAIN_FONT							FONT10ARIAL
#define	OPT_SLIDER_FONT							FONT12ARIAL

#define	OPT_MAIN_COLOR							OPT_BUTTON_ON_COLOR
#define	OPT_HIGHLIGHT_COLOR						FONT_MCOLOR_WHITE

// these both could be established at run time, then never worry about it again
// derived from "OPTIONSCREENBASE.sti"
#define	OPTIONS_SCREEN_WIDTH					638
#define	OPTIONS_SCREEN_HEIGHT					478

#define	OPTIONS__TOP_LEFT_X						iScreenWidthOffset
#define	OPTIONS__TOP_LEFT_Y						iScreenHeightOffset
#define	OPTIONS__BOTTOM_RIGHT_X					OPTIONS__TOP_LEFT_X + OPTIONS_SCREEN_WIDTH
#define	OPTIONS__BOTTOM_RIGHT_Y					OPTIONS__TOP_LEFT_Y + OPTIONS_SCREEN_HEIGHT

#define	OPT_SAVE_BTN_X							iScreenWidthOffset + 50
#define	OPT_SAVE_BTN_Y							iScreenHeightOffset + 438

#define	OPT_LOAD_BTN_X							iScreenWidthOffset + 120
#define	OPT_LOAD_BTN_Y							OPT_SAVE_BTN_Y

#define	OPT_QUIT_BTN_X							iScreenWidthOffset + 190
#define	OPT_QUIT_BTN_Y							OPT_SAVE_BTN_Y
// arynn : need more option screen toggles : Add in buttons that allow for options column paging
#define	OPT_PREV_BTN_X							iScreenWidthOffset + 310
#define	OPT_PREV_BTN_Y							OPT_SAVE_BTN_Y 

#define	OPT_NEXT_BTN_X							iScreenWidthOffset + 420
#define	OPT_NEXT_BTN_Y							OPT_SAVE_BTN_Y 

#define	OPT_DONE_BTN_X							iScreenWidthOffset + 550
#define	OPT_DONE_BTN_Y							OPT_SAVE_BTN_Y

#define	OPT_GAP_BETWEEN_TOGGLE_BOXES			18

//Text
#define	OPT_TOGGLE_BOX_FIRST_COL_TEXT_X			OPT_TOGGLE_BOX_FIRST_COLUMN_X + OPT_SPACE_BETWEEN_TEXT_AND_TOGGLE_BOX
#define	OPT_TOGGLE_BOX_FIRST_COL_TEXT_Y			OPT_TOGGLE_BOX_FIRST_COLUMN_START_Y

#define	OPT_TOGGLE_BOX_SECOND_TEXT_X			OPT_TOGGLE_BOX_SECOND_COLUMN_X + OPT_SPACE_BETWEEN_TEXT_AND_TOGGLE_BOX
#define	OPT_TOGGLE_BOX_SECOND_TEXT_Y			OPT_TOGGLE_BOX_SECOND_COLUMN_START_Y

//toggle boxes
#define	OPT_SPACE_BETWEEN_TEXT_AND_TOGGLE_BOX	30
#define	OPT_TOGGLE_TEXT_OFFSET_Y				2

#define	OPT_TOGGLE_BOX_FIRST_COLUMN_X			iScreenWidthOffset + 260
#define	OPT_TOGGLE_BOX_FIRST_COLUMN_START_Y		iScreenHeightOffset + 82

#define	OPT_TOGGLE_BOX_SECOND_COLUMN_X			iScreenWidthOffset + 435
#define	OPT_TOGGLE_BOX_SECOND_COLUMN_START_Y	OPT_TOGGLE_BOX_FIRST_COLUMN_START_Y

#define	OPT_TOGGLE_BOX_TEXT_WIDTH				OPT_TOGGLE_BOX_SECOND_COLUMN_X - OPT_TOGGLE_BOX_FIRST_COLUMN_X - 20

// Slider bar defines
#define	OPT_GAP_BETWEEN_SLIDER_BARS				60
#define	OPT_SLIDER_BAR_SIZE						258

#define	OPT_SLIDER_TEXT_WIDTH					45

#define	OPT_SOUND_FX_TEXT_X						iScreenWidthOffset + 38
#define	OPT_SOUND_FX_TEXT_Y						iScreenHeightOffset + 87

#define	OPT_SPEECH_TEXT_X						iScreenWidthOffset + 85
#define	OPT_SPEECH_TEXT_Y						OPT_SOUND_FX_TEXT_Y

#define	OPT_MUSIC_TEXT_X						iScreenWidthOffset + 137
#define	OPT_MUSIC_TEXT_Y						OPT_SOUND_FX_TEXT_Y

#define	OPT_TEXT_TO_SLIDER_OFFSET_Y				25

#define	OPT_SOUND_EFFECTS_SLIDER_X				iScreenWidthOffset + 56
#define	OPT_SOUND_EFFECTS_SLIDER_Y				iScreenHeightOffset + 126

#define	OPT_SPEECH_SLIDER_X						iScreenWidthOffset + 107
#define	OPT_SPEECH_SLIDER_Y						OPT_SOUND_EFFECTS_SLIDER_Y

#define	OPT_MUSIC_SLIDER_X						iScreenWidthOffset + 158
#define	OPT_MUSIC_SLIDER_Y						OPT_SOUND_EFFECTS_SLIDER_Y

#define	OPT_MUSIC_SLIDER_PLAY_SOUND_DELAY		75

#define	OPT_FIRST_COLUMN_TOGGLE_CUT_OFF			18
#define	MAX_NUMBER_OF_OPTION_TOGGLES			OPT_FIRST_COLUMN_TOGGLE_CUT_OFF * 2
#define	MAX_NUMBER_OF_COLUMNS					((NUM_GAME_OPTIONS / OPT_FIRST_COLUMN_TOGGLE_CUT_OFF)-1)

// arynn : added some defines to control feedback during debugging
//#define OPTIONS_SCREEN_DEBUG_DRAWRECT_AROUND_REGION
//#define OPTIONSCREEN_DEBUG_FEEDBACK
//#define OPTIONSCREEN_DEBUG_FEEDBACK2

/////////////////////////////////
//
//	Global Variables
//
/////////////////////////////////


UINT32		guiOptionBackGroundImage;
UINT32		guiOptionsAddOnImages;

UINT32		guiSoundEffectsSliderID;
UINT32		guiSpeechSliderID;
UINT32		guiMusicSliderID;

BOOLEAN		gfOptionsScreenEntry = TRUE;
BOOLEAN		gfOptionsScreenExit	= FALSE;
BOOLEAN		gfRedrawOptionsScreen = TRUE;

CHAR8		gzSavedGameName[ 128 ];
BOOLEAN		gfEnteredFromMapScreen=FALSE;

UINT32		guiOptionsScreen = OPTIONS_SCREEN;
UINT32		guiPreviousOptionScreen = OPTIONS_SCREEN;

BOOLEAN		gfExitOptionsDueToMessageBox=FALSE;
BOOLEAN		gfExitOptionsAfterMessageBox = FALSE;


UINT32		guiSoundFxSliderMoving = 0xffffffff;
UINT32		guiSpeechSliderMoving = 0xffffffff;

INT32		giOptionsMessageBox = -1;			// Options pop up messages index value

INT8		gbHighLightedOptionText = -1;

BOOLEAN		gfHideBloodAndGoreOption=FALSE;		//If a germany build we are to hide the blood and gore option
UINT8		gubFirstColOfOptions=OPT_FIRST_COLUMN_TOGGLE_CUT_OFF;


BOOLEAN		gfSettingOfTreeTopStatusOnEnterOfOptionScreen;
BOOLEAN		gfSettingOfItemGlowStatusOnEnterOfOptionScreen;
BOOLEAN		gfSettingOfDontAnimateSmoke;

// Goto save game Button
void BtnOptGotoSaveGameCallback(GUI_BUTTON *btn,INT32 reason);
UINT32		guiOptGotoSaveGameBtn;
INT32		giOptionsButtonImages;

// Goto load game button
void BtnOptGotoLoadGameCallback(GUI_BUTTON *btn,INT32 reason);
UINT32		guiOptGotoLoadGameBtn;
INT32		giGotoLoadBtnImage;

// QuitButton
void BtnOptQuitCallback(GUI_BUTTON *btn,INT32 reason);
UINT32		guiQuitButton;
INT32		giQuitBtnImage;

// arynn : need more option screen toggles : Add in button that allow for options column paging
// Options Screen globals
INT32	OptionsList_Column_Offset	= 0 ;	// the first column's starting point
INT32	Current_First_Option_Index;			// index of the first (single) option in the first column, used in lookup option vs togglebox
INT32	Last_Count_Of_Toggles_Created;		// index to control destroy toggle box function, basically limit loops to not exceed
void Create_Toggle_Buttons();				// these two are blcok removals from functions, an isolation of toggle create/destroy
void Destroy_Toggle_Buttons();

// Next Button
void BtnOptNextCallback(GUI_BUTTON *btn,INT32 reason);
UINT32		guiOptNextButton;
INT32		giOptNextBtnImage;

// Prev Button
void BtnOptPrevCallback(GUI_BUTTON *btn,INT32 reason);
UINT32		guiOptPrevButton;
INT32		giOptPrevBtnImage;

// Done Button
void BtnDoneCallback(GUI_BUTTON *btn,INT32 reason);
extern UINT32	guiDoneButton; // symbol already declared globally in AimArchives.cpp (jonathanl)
INT32		giDoneBtnImage;


//checkbox to toggle tracking mode on or off
//UINT32	guiOptionsToggles[ NUM_GAME_OPTIONS ]; //old limiter is old ?
UINT32	guiOptionsToggles[ MAX_NUMBER_OF_OPTION_TOGGLES ];
void BtnOptionsTogglesCallback(GUI_BUTTON *btn,INT32 reason);


//Mouse regions for the name of the option
//MOUSE_REGION	gSelectedOptionTextRegion[ NUM_GAME_OPTIONS ]; //old limiter is old ?
MOUSE_REGION	gSelectedOptionTextRegion[ MAX_NUMBER_OF_OPTION_TOGGLES ];
void		SelectedOptionTextRegionCallBack(MOUSE_REGION * pRegion, INT32 iReason );
void		SelectedOptionTextRegionMovementCallBack(MOUSE_REGION * pRegion, INT32 reason );


//Mouse regions for the area around the toggle boxs
MOUSE_REGION	gSelectedToggleBoxAreaRegion;
void		SelectedToggleBoxAreaRegionMovementCallBack(MOUSE_REGION * pRegion, INT32 reason );


/////////////////////////////////
//
//	Function ProtoTypes
//
/////////////////////////////////


BOOLEAN			EnterOptionsScreen();
void			RenderOptionsScreen();
void			ExitOptionsScreen();
void			HandleOptionsScreen();
void			GetOptionsScreenUserInput();
void			SetOptionsExitScreen( UINT32 uiExitScreen );


void			SoundFXSliderChangeCallBack( INT32 iNewValue );
void			SpeechSliderChangeCallBack( INT32 iNewValue );
void			MusicSliderChangeCallBack( INT32 iNewValue );
//BOOLEAN			DoOptionsMessageBox( UINT8 ubStyle, STR16zString, UINT32 uiExitScreen, UINT8 ubFlags, MSGBOX_CALLBACK ReturnCallback );
void			ConfirmQuitToMainMenuMessageBoxCallBack( UINT8 bExitValue );
void			HandleSliderBarMovementSounds();
void			HandleOptionToggle( UINT8 ubButton, BOOLEAN fState, BOOLEAN fDown, BOOLEAN fPlaySound );
void			HandleHighLightedText( BOOLEAN fHighLight );



extern	BOOLEAN CheckIfGameCdromIsInCDromDrive();
extern	void ToggleItemGlow( BOOLEAN fOn );


//ppp

/////////////////////////////////
//
//	Code
//
/////////////////////////////////

UINT32	OptionsScreenInit()
{

	//Set so next time we come in, we can set up
	gfOptionsScreenEntry = TRUE;


	return( TRUE );
}

UINT32	OptionsScreenHandle()
{
	StartFrameBufferRender();

	if( gfOptionsScreenEntry )
	{
		PauseGame();
		EnterOptionsScreen();
		gfOptionsScreenEntry = FALSE;
		gfOptionsScreenExit = FALSE;
		gfRedrawOptionsScreen = TRUE;
		RenderOptionsScreen();

		//Blit the background to the save buffer
		BlitBufferToBuffer( guiRENDERBUFFER, guiSAVEBUFFER, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
		InvalidateRegion( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
	}

	RestoreBackgroundRects();

	GetOptionsScreenUserInput();

	HandleOptionsScreen();

	if( gfRedrawOptionsScreen )
	{
		RenderOptionsScreen();
		RenderButtons();

		gfRedrawOptionsScreen = FALSE;
	}

	//Render the active slider bars
	RenderAllSliderBars();

	// render buttons marked dirty
	MarkButtonsDirty( );
	RenderButtons( );

	// ATE: Put here to save RECTS before any fast help being drawn...
	SaveBackgroundRects( );
	RenderButtonsFastHelp();


	ExecuteBaseDirtyRectQueue();
	EndFrameBufferRender();


	if( gfOptionsScreenExit )
	{
		ExitOptionsScreen();
		gfOptionsScreenExit = FALSE;
		gfOptionsScreenEntry = TRUE;

		UnPauseGame();
	}

	return( guiOptionsScreen );
}

UINT32	OptionsScreenShutdown()
{
	return( TRUE );
}

void Create_Toggle_Buttons()
{
	UINT16	usPosY;
	UINT8	cnt;
	UINT16	usTextWidth, usTextHeight;

	//
	// Toggle Boxes
	//
	Current_First_Option_Index = OptionsList_Column_Offset * OPT_FIRST_COLUMN_TOGGLE_CUT_OFF;

	usTextHeight = GetFontHeight( OPT_MAIN_FONT );

	//Create the first column of check boxes
	usPosY = OPT_TOGGLE_BOX_FIRST_COLUMN_START_Y;

	for( cnt=0; cnt<OPT_FIRST_COLUMN_TOGGLE_CUT_OFF; cnt++)
	{
		//if this is the blood and gore option, and we are to hide the option
		if( cnt == TOPTION_BLOOD_N_GORE && gfHideBloodAndGoreOption )
		{
			gubFirstColOfOptions++;

			//advance to the next
			continue;
		}

		if( !(cnt + Current_First_Option_Index < NUM_GAME_OPTIONS ))
		{
			//we have no more toggles to add
			break;
		}
		//Check box to toggle tracking mode
		guiOptionsToggles[ cnt ] = CreateCheckBoxButton( OPT_TOGGLE_BOX_FIRST_COLUMN_X, usPosY,
															"INTERFACE\\OptionsCheckBoxes_12x12.sti", 
															MSYS_PRIORITY_HIGH+10,
															BtnOptionsTogglesCallback );

		MSYS_SetBtnUserData( guiOptionsToggles[ cnt ], 0, cnt );


		usTextWidth = StringPixLength( zOptionsToggleText[ cnt + Current_First_Option_Index ], OPT_MAIN_FONT );

		if( usTextWidth > OPT_TOGGLE_BOX_TEXT_WIDTH )
		{
			//Get how many lines will be used to display the string, without displaying the string
			UINT8	ubNumLines = (UINT8) (	DisplayWrappedString( 0, 0, OPT_TOGGLE_BOX_TEXT_WIDTH, 2, OPT_MAIN_FONT, OPT_HIGHLIGHT_COLOR, 
											zOptionsToggleText[ cnt + Current_First_Option_Index ], FONT_MCOLOR_BLACK, TRUE, 
											LEFT_JUSTIFIED | DONT_DISPLAY_TEXT ) / GetFontHeight( OPT_MAIN_FONT ) );

			usTextWidth = OPT_TOGGLE_BOX_TEXT_WIDTH;

			//Create mouse regions for the option toggle text
			MSYS_DefineRegion(	&gSelectedOptionTextRegion[cnt], OPT_TOGGLE_BOX_FIRST_COLUMN_X+13, usPosY, 
								(UINT16)(OPT_TOGGLE_BOX_FIRST_COL_TEXT_X+usTextWidth), (UINT16)(usPosY+usTextHeight*ubNumLines), MSYS_PRIORITY_HIGH,
								CURSOR_NORMAL, SelectedOptionTextRegionMovementCallBack, SelectedOptionTextRegionCallBack );
			MSYS_AddRegion( &gSelectedOptionTextRegion[cnt]);
			MSYS_SetRegionUserData( &gSelectedOptionTextRegion[ cnt ], 0, cnt);
		}
		else
		{
			//Create mouse regions for the option toggle text
			MSYS_DefineRegion(	&gSelectedOptionTextRegion[cnt], OPT_TOGGLE_BOX_FIRST_COLUMN_X+13, usPosY, 
								(UINT16)(OPT_TOGGLE_BOX_FIRST_COL_TEXT_X+usTextWidth), (UINT16)(usPosY+usTextHeight), MSYS_PRIORITY_HIGH,
								CURSOR_NORMAL, SelectedOptionTextRegionMovementCallBack, SelectedOptionTextRegionCallBack );
			MSYS_AddRegion( &gSelectedOptionTextRegion[cnt]);
			MSYS_SetRegionUserData( &gSelectedOptionTextRegion[ cnt ], 0, cnt);
		}


		SetRegionFastHelpText( &gSelectedOptionTextRegion[ cnt ], zOptionsScreenHelpText[ cnt+ Current_First_Option_Index ] );
		SetButtonFastHelpText( guiOptionsToggles[ cnt ], zOptionsScreenHelpText[ cnt + Current_First_Option_Index ] );

		usPosY += OPT_GAP_BETWEEN_TOGGLE_BOXES;
	}


	//Create the 2nd column of check boxes
	usPosY = OPT_TOGGLE_BOX_FIRST_COLUMN_START_Y;

	for( ; cnt<MAX_NUMBER_OF_OPTION_TOGGLES; cnt++)
	{
		if( !(cnt + Current_First_Option_Index < NUM_GAME_OPTIONS ))
		{
			//we have no more toggles to add
			break;
		}
		//Check box to toggle tracking mode
		guiOptionsToggles[ cnt ] = CreateCheckBoxButton( OPT_TOGGLE_BOX_SECOND_COLUMN_X, usPosY,
														"INTERFACE\\OptionsCheckBoxes_12x12.sti", MSYS_PRIORITY_HIGH+10,
														BtnOptionsTogglesCallback );
		MSYS_SetBtnUserData( guiOptionsToggles[ cnt ], 0, cnt );


		//
		// Create mouse regions for the option toggle text
		//


		usTextWidth = StringPixLength( zOptionsToggleText[ cnt + Current_First_Option_Index ], OPT_MAIN_FONT );

		if( usTextWidth > OPT_TOGGLE_BOX_TEXT_WIDTH )
		{
			//Get how many lines will be used to display the string, without displaying the string
			UINT8	ubNumLines = (UINT8) (	DisplayWrappedString( 0, 0, OPT_TOGGLE_BOX_TEXT_WIDTH, 2, OPT_MAIN_FONT, OPT_HIGHLIGHT_COLOR, 
											zOptionsToggleText[ cnt + Current_First_Option_Index ], FONT_MCOLOR_BLACK, TRUE, 
											LEFT_JUSTIFIED | DONT_DISPLAY_TEXT ) / GetFontHeight( OPT_MAIN_FONT ) );

			usTextWidth = OPT_TOGGLE_BOX_TEXT_WIDTH;

			MSYS_DefineRegion(	&gSelectedOptionTextRegion[cnt], OPT_TOGGLE_BOX_SECOND_COLUMN_X+13, usPosY, 
								(UINT16)(OPT_TOGGLE_BOX_SECOND_TEXT_X+usTextWidth), (UINT16)(usPosY+usTextHeight*ubNumLines), 
								MSYS_PRIORITY_HIGH, CURSOR_NORMAL, SelectedOptionTextRegionMovementCallBack, 
								SelectedOptionTextRegionCallBack );
			MSYS_AddRegion( &gSelectedOptionTextRegion[cnt]);
			MSYS_SetRegionUserData( &gSelectedOptionTextRegion[ cnt ], 0, cnt );
		}
		else
		{
			MSYS_DefineRegion(	&gSelectedOptionTextRegion[cnt], OPT_TOGGLE_BOX_SECOND_COLUMN_X+13, usPosY, 
								(UINT16)(OPT_TOGGLE_BOX_SECOND_TEXT_X+usTextWidth), (UINT16)(usPosY+usTextHeight), 
								MSYS_PRIORITY_HIGH,	CURSOR_NORMAL, SelectedOptionTextRegionMovementCallBack, 
								SelectedOptionTextRegionCallBack );
			MSYS_AddRegion( &gSelectedOptionTextRegion[cnt]);
			MSYS_SetRegionUserData( &gSelectedOptionTextRegion[ cnt ], 0, cnt );
		}


		SetRegionFastHelpText( &gSelectedOptionTextRegion[ cnt ], zOptionsScreenHelpText[ cnt+ Current_First_Option_Index ] );
		SetButtonFastHelpText( guiOptionsToggles[ cnt ], zOptionsScreenHelpText[ cnt + Current_First_Option_Index ] );

		usPosY += OPT_GAP_BETWEEN_TOGGLE_BOXES;
	}

	Last_Count_Of_Toggles_Created = cnt;

}

void Destroy_Toggle_Buttons()
{
	UINT8	cnt;

	//Remove the toggle buttons
	for( cnt=0; cnt<MAX_NUMBER_OF_OPTION_TOGGLES; cnt++)
	{
		//if this is the blood and gore option, and we are to hide the option
		if( cnt == TOPTION_BLOOD_N_GORE && gfHideBloodAndGoreOption )
		{
			//advance to the next
			continue;
		}

		if( cnt >=  Last_Count_Of_Toggles_Created )
		{
			break;
		}

		RemoveButton( guiOptionsToggles[ cnt ] );

	MSYS_RemoveRegion( &gSelectedOptionTextRegion[cnt]);
	}

}

BOOLEAN EnterOptionsScreen()
{
	VOBJECT_DESC	VObjectDesc;

	// WANNE: Do not draw the blackground back
	//ColorFillVideoSurfaceArea( FRAME_BUFFER, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );

	//Default this to off
	gfHideBloodAndGoreOption=FALSE;

#ifndef BLOOD_N_GORE_ENABLED
	//This will hide blood and gore option
	gfHideBloodAndGoreOption = TRUE;

/*
Uncomment this to enable the check for files to activate the blood and gore option for the german build
	if( !FileExists( "Germany.dat" ) && FileExists( "Lecken.dat" ) )
	{
		gfHideBloodAndGoreOption = FALSE;
	}
	else
*/
	{
		gGameSettings.fOptions[ TOPTION_BLOOD_N_GORE ] = FALSE;
	}
#endif


	//if we are coming from mapscreen
	if( guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
	{
		guiTacticalInterfaceFlags &= ~INTERFACE_MAPSCREEN;
		gfEnteredFromMapScreen = TRUE;
	}


	// Stop ambients...
	StopAmbients( );

	guiOptionsScreen = OPTIONS_SCREEN;

	//Init the slider bar;
	InitSlider();

	if( gfExitOptionsDueToMessageBox )
	{
		gfRedrawOptionsScreen = TRUE;
		gfExitOptionsDueToMessageBox = FALSE;
		return( TRUE );
	}

	gfExitOptionsDueToMessageBox = FALSE;

	// load the options screen background graphic and add it
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\OptionScreenBase.sti", VObjectDesc.ImageFile);
	CHECKF(AddVideoObject(&VObjectDesc, &guiOptionBackGroundImage));

	// load button, title graphic and add it
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	GetMLGFilename( VObjectDesc.ImageFile, MLG_OPTIONHEADER );
	CHECKF(AddVideoObject(&VObjectDesc, &guiOptionsAddOnImages));

	//Save game button
	giOptionsButtonImages = LoadButtonImage("INTERFACE\\OptionScreenAddons2.sti", -1,2,-1,3,-1 );
	guiOptGotoSaveGameBtn = CreateIconAndTextButton( giOptionsButtonImages, zOptionsText[OPT_SAVE_GAME], OPT_BUTTON_FONT2,
													OPT_BUTTON_ON_COLOR, DEFAULT_SHADOW,
													OPT_BUTTON_OFF_COLOR, DEFAULT_SHADOW,
													TEXT_CJUSTIFIED,
													OPT_SAVE_BTN_X, OPT_SAVE_BTN_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,
													DEFAULT_MOVE_CALLBACK, BtnOptGotoSaveGameCallback);
	SpecifyDisabledButtonStyle( guiOptGotoSaveGameBtn, DISABLED_STYLE_HATCHED );
	if( guiPreviousOptionScreen == MAINMENU_SCREEN || !CanGameBeSaved() )
	{
		DisableButton( guiOptGotoSaveGameBtn );
	}

	//Load game button
	giGotoLoadBtnImage = UseLoadedButtonImage( giOptionsButtonImages, -1,2,-1,3,-1 );
	guiOptGotoLoadGameBtn = CreateIconAndTextButton( giGotoLoadBtnImage, zOptionsText[OPT_LOAD_GAME], OPT_BUTTON_FONT2,
													OPT_BUTTON_ON_COLOR, DEFAULT_SHADOW,
													OPT_BUTTON_OFF_COLOR, DEFAULT_SHADOW,
													TEXT_CJUSTIFIED,
													OPT_LOAD_BTN_X, OPT_LOAD_BTN_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,
													DEFAULT_MOVE_CALLBACK, BtnOptGotoLoadGameCallback);
//	SpecifyDisabledButtonStyle( guiBobbyRAcceptOrder, DISABLED_STYLE_SHADED );

	//Quit to main menu button
	giQuitBtnImage = UseLoadedButtonImage( giOptionsButtonImages, -1,2,-1,3,-1 );
	guiQuitButton = CreateIconAndTextButton( giQuitBtnImage, zOptionsText[OPT_MAIN_MENU], OPT_BUTTON_FONT2,
													OPT_BUTTON_ON_COLOR, DEFAULT_SHADOW,
													OPT_BUTTON_OFF_COLOR, DEFAULT_SHADOW,
													TEXT_CJUSTIFIED,
													OPT_QUIT_BTN_X, OPT_QUIT_BTN_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,
													DEFAULT_MOVE_CALLBACK, BtnOptQuitCallback);
	SpecifyDisabledButtonStyle( guiQuitButton, DISABLED_STYLE_HATCHED );
//	DisableButton( guiQuitButton );

// arynn : need more option screen toggles : Add in buttons that allow for options column paging
	// Previous Column of options
 	giOptPrevBtnImage = UseLoadedButtonImage( giOptionsButtonImages, -1,2,-1,3,-1 );                         
 	guiOptPrevButton = CreateIconAndTextButton( giOptPrevBtnImage, zOptionsText[OPT_PREV], OPT_BUTTON_FONT2,
 													OPT_BUTTON_ON_COLOR, DEFAULT_SHADOW,                                                      
 													OPT_BUTTON_OFF_COLOR, DEFAULT_SHADOW,                                                     
 													TEXT_CJUSTIFIED,                                                                          
 													OPT_PREV_BTN_X, OPT_PREV_BTN_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,                        
 													DEFAULT_MOVE_CALLBACK, BtnOptPrevCallback);                                               
 	SpecifyDisabledButtonStyle( guiOptPrevButton, DISABLED_STYLE_HATCHED );  
	if( OptionsList_Column_Offset == 0 )
	{
		DisableButton( guiOptPrevButton );
	}

	// Next Column of options
 	giOptNextBtnImage = UseLoadedButtonImage( giOptionsButtonImages, -1,2,-1,3,-1 );                         
 	guiOptNextButton = CreateIconAndTextButton( giOptNextBtnImage, zOptionsText[OPT_NEXT], OPT_BUTTON_FONT2,
 													OPT_BUTTON_ON_COLOR, DEFAULT_SHADOW,                                                      
 													OPT_BUTTON_OFF_COLOR, DEFAULT_SHADOW,                                                     
 													TEXT_CJUSTIFIED,                                                                          
 													OPT_NEXT_BTN_X, OPT_NEXT_BTN_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,                        
 													DEFAULT_MOVE_CALLBACK, BtnOptNextCallback);                                               
 	SpecifyDisabledButtonStyle( guiOptNextButton, DISABLED_STYLE_HATCHED );   
	if( OptionsList_Column_Offset >= MAX_NUMBER_OF_COLUMNS )
	{
		DisableButton( guiOptNextButton );
	}

	//Done button
	giDoneBtnImage = UseLoadedButtonImage( giOptionsButtonImages, -1,2,-1,3,-1 );
	guiDoneButton = CreateIconAndTextButton( giDoneBtnImage, zOptionsText[OPT_DONE], OPT_BUTTON_FONT2,
													OPT_BUTTON_ON_COLOR, DEFAULT_SHADOW,
													OPT_BUTTON_OFF_COLOR, DEFAULT_SHADOW,
													TEXT_CJUSTIFIED,
													OPT_DONE_BTN_X, OPT_DONE_BTN_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,
													DEFAULT_MOVE_CALLBACK, BtnDoneCallback);
//	SpecifyDisabledButtonStyle( guiBobbyRAcceptOrder, DISABLED_STYLE_SHADED );

	Create_Toggle_Buttons(); // arynn : moved block out of func

	//Create a mouse region so when the user leaves a togglebox text region we can detect it then unselect the region
	MSYS_DefineRegion( &gSelectedToggleBoxAreaRegion, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, MSYS_PRIORITY_NORMAL,
							CURSOR_NORMAL, SelectedToggleBoxAreaRegionMovementCallBack, MSYS_NO_CALLBACK );
	MSYS_AddRegion( &gSelectedToggleBoxAreaRegion );


	//Render the scene before adding the slider boxes
	RenderOptionsScreen();

	//Add a slider bar for the Sound Effects
	guiSoundEffectsSliderID = AddSlider(	SLIDER_VERTICAL_STEEL, CURSOR_NORMAL, OPT_SOUND_EFFECTS_SLIDER_X, OPT_SOUND_EFFECTS_SLIDER_Y, 
											OPT_SLIDER_BAR_SIZE, 127, MSYS_PRIORITY_HIGH, SoundFXSliderChangeCallBack, 0 );
	AssertMsg( guiSoundEffectsSliderID, "Failed to AddSlider" );
	SetSliderValue( guiSoundEffectsSliderID, GetSoundEffectsVolume() );

	//Add a slider bar for the Speech
	guiSpeechSliderID = AddSlider(	SLIDER_VERTICAL_STEEL, CURSOR_NORMAL, OPT_SPEECH_SLIDER_X, OPT_SPEECH_SLIDER_Y, 
									OPT_SLIDER_BAR_SIZE, 127, MSYS_PRIORITY_HIGH, SpeechSliderChangeCallBack, 0 );
	AssertMsg( guiSpeechSliderID, "Failed to AddSlider" );
	SetSliderValue( guiSpeechSliderID, GetSpeechVolume() );

	//Add a slider bar for the Music
	guiMusicSliderID = AddSlider(	SLIDER_VERTICAL_STEEL, CURSOR_NORMAL, OPT_MUSIC_SLIDER_X, OPT_MUSIC_SLIDER_Y, 
									OPT_SLIDER_BAR_SIZE, 127, MSYS_PRIORITY_HIGH, MusicSliderChangeCallBack, 0 );
	AssertMsg( guiMusicSliderID, "Failed to AddSlider" );
	SetSliderValue( guiMusicSliderID, MusicGetVolume() );



	//Remove the mouse region over the clock
	RemoveMouseRegionForPauseOfClock(	);

	//Draw the screen
	gfRedrawOptionsScreen = TRUE;

	//Set the option screen toggle boxes
	SetOptionsScreenToggleBoxes();

	DisableScrollMessages();

	//reset
	gbHighLightedOptionText = -1;

	//get the status of the tree top option
	gfSettingOfTreeTopStatusOnEnterOfOptionScreen = gGameSettings.fOptions[ TOPTION_TOGGLE_TREE_TOPS ];

	//Get the status of the item glow option
	gfSettingOfItemGlowStatusOnEnterOfOptionScreen = gGameSettings.fOptions[ TOPTION_GLOW_ITEMS ];

	gfSettingOfDontAnimateSmoke = gGameSettings.fOptions[ TOPTION_ANIMATE_SMOKE ];
	return( TRUE );
}

void ExitOptionsScreen()
{

	if( gfExitOptionsDueToMessageBox )
	{
		gfOptionsScreenExit = FALSE;

		if( !gfExitOptionsAfterMessageBox )
			return;
		gfExitOptionsAfterMessageBox = FALSE;
		gfExitOptionsDueToMessageBox = FALSE;
	}

	//Get the current status of the toggle boxes
	GetOptionsScreenToggleBoxes();
	//The save the current settings to disk
	// arynn : note : if dynamic options (dif option sets for dif builds) is used, SaveGameSettings(), LoadGameSettings()
	// arynn : note : is going to require differing JA2.set names for each build, this is because of settings order/organization/quantity
	SaveGameSettings(); 

	//Create the clock mouse region
	CreateMouseRegionForPauseOfClock( CLOCK_REGION_START_X, CLOCK_REGION_START_Y );

	if( guiOptionsScreen == GAME_SCREEN )
		EnterTacticalScreen( );

	RemoveButton( guiOptGotoSaveGameBtn );
	RemoveButton( guiOptGotoLoadGameBtn );
	RemoveButton( guiQuitButton );
	RemoveButton( guiOptNextButton );// arynn : more option screen toggles
	RemoveButton( guiOptPrevButton );
	RemoveButton( guiDoneButton );

	UnloadButtonImage( giOptionsButtonImages );
	UnloadButtonImage( giGotoLoadBtnImage );
	UnloadButtonImage( giQuitBtnImage );
	UnloadButtonImage( giOptNextBtnImage );// arynn : more option screen toggles
	UnloadButtonImage( giOptPrevBtnImage );
	UnloadButtonImage( giDoneBtnImage );

	DeleteVideoObjectFromIndex( guiOptionBackGroundImage );
	DeleteVideoObjectFromIndex( guiOptionsAddOnImages );


	Destroy_Toggle_Buttons(); // arynn : moved block out of func


	//REmove the slider bars
	RemoveSliderBar( guiSoundEffectsSliderID );
	RemoveSliderBar( guiSpeechSliderID );
	RemoveSliderBar( guiMusicSliderID );


	MSYS_RemoveRegion( &gSelectedToggleBoxAreaRegion );

	ShutDownSlider();

	//if we are coming from mapscreen
	if( gfEnteredFromMapScreen )
	{
		gfEnteredFromMapScreen = FALSE;
		guiTacticalInterfaceFlags |= INTERFACE_MAPSCREEN;
	}

	//if the user changed the	TREE TOP option, AND a world is loaded
	if( gfSettingOfTreeTopStatusOnEnterOfOptionScreen != gGameSettings.fOptions[ TOPTION_TOGGLE_TREE_TOPS ] && gfWorldLoaded )
	{
		SetTreeTopStateForMap();
	}

	//if the user has changed the item glow option AND a world is loaded
	if( gfSettingOfItemGlowStatusOnEnterOfOptionScreen != gGameSettings.fOptions[ TOPTION_GLOW_ITEMS ] && gfWorldLoaded )
	{
		ToggleItemGlow( gGameSettings.fOptions[ TOPTION_GLOW_ITEMS ] );
	}

	if( gfSettingOfDontAnimateSmoke != gGameSettings.fOptions[ TOPTION_ANIMATE_SMOKE ] && gfWorldLoaded )
	{
	UpdateSmokeEffectGraphics( );
	}

}

void			HandleOptionsScreen()
{
	HandleSliderBarMovementSounds();

	HandleHighLightedText( TRUE );
}

void RenderOptionsScreen()
{
	HVOBJECT hPixHandle;
	UINT16	usPosY;
	UINT8	cnt;
	UINT16	usWidth=0;
#ifdef OPTIONS_SCREEN_DEBUG_DRAWRECT_AROUND_REGION
	UINT32 uiDestPitchBYTES;	// arynn : needed by draw functions that show up in debug
	UINT8 *pDestBuf;
#endif

	//Get and display the background image
	GetVideoObject(&hPixHandle, guiOptionBackGroundImage);
	BltVideoObject(FRAME_BUFFER, hPixHandle, 0, iScreenWidthOffset, iScreenHeightOffset, VO_BLT_SRCTRANSPARENCY,NULL);

	//Get and display the titla image
	GetVideoObject(&hPixHandle, guiOptionsAddOnImages);
	BltVideoObject(FRAME_BUFFER, hPixHandle, 0, iScreenWidthOffset, iScreenHeightOffset, VO_BLT_SRCTRANSPARENCY,NULL);
	BltVideoObject(FRAME_BUFFER, hPixHandle, 1, iScreenWidthOffset, iScreenHeightOffset + 434, VO_BLT_SRCTRANSPARENCY,NULL);

#ifdef OPTIONS_SCREEN_DEBUG_DRAWRECT_AROUND_REGION
	{
	// arynn : this block draws a rect and line thru the zone that should encompass the whole options screen diag box
	pDestBuf = LockVideoSurface( FRAME_BUFFER, &uiDestPitchBYTES );
	SetClippingRegionAndImageWidth( uiDestPitchBYTES, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
	LineDraw(	TRUE, OPTIONS__TOP_LEFT_X, OPTIONS__TOP_LEFT_Y, OPTIONS__BOTTOM_RIGHT_X,  OPTIONS__BOTTOM_RIGHT_Y, 
				Get16BPPColor( FROMRGB( 200, 200, 200 )), pDestBuf);
	RectangleDraw(	TRUE, OPTIONS__TOP_LEFT_X, OPTIONS__TOP_LEFT_Y, OPTIONS__BOTTOM_RIGHT_X,  OPTIONS__BOTTOM_RIGHT_Y, 
					Get16BPPColor( FROMRGB( 200, 200, 200 )), pDestBuf);
	UnLockVideoSurface( FRAME_BUFFER );
	}
#endif

	//
	// Text for the toggle boxes
	//

	usPosY = OPT_TOGGLE_BOX_FIRST_COLUMN_START_Y + OPT_TOGGLE_TEXT_OFFSET_Y;

	//Display the First column of toggles
	for( cnt=0; cnt<OPT_FIRST_COLUMN_TOGGLE_CUT_OFF; cnt++)
	{
		//if this is the blood and gore option, and we are to hide the option
		if( cnt == TOPTION_BLOOD_N_GORE && gfHideBloodAndGoreOption )
		{
		//advance to the next
			continue;
		}
		if( cnt >=  Last_Count_Of_Toggles_Created )
		{
			break;
		}


		usWidth = StringPixLength( zOptionsToggleText[ cnt + Current_First_Option_Index ], OPT_MAIN_FONT );

		//if the string is going to wrap, move the string up a bit
		if( usWidth > OPT_TOGGLE_BOX_TEXT_WIDTH )
			DisplayWrappedString(	OPT_TOGGLE_BOX_FIRST_COL_TEXT_X, usPosY, OPT_TOGGLE_BOX_TEXT_WIDTH, 2, OPT_MAIN_FONT, OPT_MAIN_COLOR, 
									zOptionsToggleText[ cnt + Current_First_Option_Index ], FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED );
		else
			DrawTextToScreen(	zOptionsToggleText[ cnt + Current_First_Option_Index ], OPT_TOGGLE_BOX_FIRST_COL_TEXT_X, usPosY, 0, 
								OPT_MAIN_FONT, OPT_MAIN_COLOR, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED	);

		usPosY += OPT_GAP_BETWEEN_TOGGLE_BOXES;
	}


	usPosY = OPT_TOGGLE_BOX_SECOND_COLUMN_START_Y + OPT_TOGGLE_TEXT_OFFSET_Y;

	//Display the 2nd column of toggles
	for( cnt=OPT_FIRST_COLUMN_TOGGLE_CUT_OFF; cnt<MAX_NUMBER_OF_OPTION_TOGGLES; cnt++)	{

		if( cnt >=  Last_Count_Of_Toggles_Created )
		{
			break;
		}

		usWidth = StringPixLength( zOptionsToggleText[ cnt + Current_First_Option_Index ], OPT_MAIN_FONT );

		//if the string is going to wrap, move the string up a bit
		if( usWidth > OPT_TOGGLE_BOX_TEXT_WIDTH )
			DisplayWrappedString(	OPT_TOGGLE_BOX_SECOND_TEXT_X, usPosY, OPT_TOGGLE_BOX_TEXT_WIDTH, 2, OPT_MAIN_FONT, OPT_MAIN_COLOR, 
									zOptionsToggleText[ cnt + Current_First_Option_Index ], FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED );
		else
			DrawTextToScreen(	zOptionsToggleText[ cnt + Current_First_Option_Index ], OPT_TOGGLE_BOX_SECOND_TEXT_X, usPosY, 0, 
								OPT_MAIN_FONT, OPT_MAIN_COLOR, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED	);

		usPosY += OPT_GAP_BETWEEN_TOGGLE_BOXES;
	}


	//
	// Text for the Slider Bars
	//

	//Display the Sound Fx text
	DisplayWrappedString(	OPT_SOUND_FX_TEXT_X, OPT_SOUND_FX_TEXT_Y, OPT_SLIDER_TEXT_WIDTH, 2, OPT_SLIDER_FONT, OPT_MAIN_COLOR, 
							zOptionsText[ OPT_SOUND_FX ], FONT_MCOLOR_BLACK, FALSE, CENTER_JUSTIFIED	);

	//Display the Speech text
	DisplayWrappedString(	OPT_SPEECH_TEXT_X, OPT_SPEECH_TEXT_Y, OPT_SLIDER_TEXT_WIDTH, 2, OPT_SLIDER_FONT, OPT_MAIN_COLOR, 
							zOptionsText[ OPT_SPEECH ], FONT_MCOLOR_BLACK, FALSE, CENTER_JUSTIFIED	);

	//Display the Music text
	DisplayWrappedString(	OPT_MUSIC_TEXT_X, OPT_MUSIC_TEXT_Y, OPT_SLIDER_TEXT_WIDTH, 2, OPT_SLIDER_FONT, OPT_MAIN_COLOR, 
							zOptionsText[ OPT_MUSIC ], FONT_MCOLOR_BLACK, FALSE, CENTER_JUSTIFIED );

	InvalidateRegion( OPTIONS__TOP_LEFT_X, OPTIONS__TOP_LEFT_Y, OPTIONS__BOTTOM_RIGHT_X, OPTIONS__BOTTOM_RIGHT_Y);

}

void GetOptionsScreenUserInput()
{
	InputAtom Event;
	POINT	MousePos;

	GetCursorPos(&MousePos);
	ScreenToClient(ghWindow, &MousePos); // In window coords!

	while( DequeueEvent( &Event ) )
	{
		// HOOK INTO MOUSE HOOKS
		switch( Event.usEvent)
	{
			case LEFT_BUTTON_DOWN:
				MouseSystemHook(LEFT_BUTTON_DOWN, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
			case LEFT_BUTTON_UP:
				MouseSystemHook(LEFT_BUTTON_UP, (INT16)MousePos.x, (INT16)MousePos.y ,_LeftButtonDown, _RightButtonDown);
				break;
			case RIGHT_BUTTON_DOWN:
				MouseSystemHook(RIGHT_BUTTON_DOWN, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
			case RIGHT_BUTTON_UP:
				MouseSystemHook(RIGHT_BUTTON_UP, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
			case RIGHT_BUTTON_REPEAT:
				MouseSystemHook(RIGHT_BUTTON_REPEAT, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
			case LEFT_BUTTON_REPEAT:
				MouseSystemHook(LEFT_BUTTON_REPEAT, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
		}

		if( !HandleTextInput( &Event ) && Event.usEvent == KEY_DOWN )
		{
			switch( Event.usParam )
			{
				case ESC:
					SetOptionsExitScreen( guiPreviousOptionScreen );
					break;

				//Enter the save game screen
				case 's':
				case 'S':
					//if the save game button isnt disabled
					if( ButtonList[ guiOptGotoSaveGameBtn ]->uiFlags & BUTTON_ENABLED )
					{
						SetOptionsExitScreen( SAVE_LOAD_SCREEN );
						gfSaveGame = TRUE;
					}
					break;

				//Enter the Load game screen
				case 'l':
				case 'L':
					SetOptionsExitScreen( SAVE_LOAD_SCREEN );
					gfSaveGame = FALSE;
					break;


#ifdef JA2TESTVERSION

				case 'r':
					gfRedrawOptionsScreen = TRUE;
					break;

				case 'i':
					InvalidateRegion( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
					break;

					//Test keys

				case 'y':
					{
					static	UINT32	uiTest2 = NO_SAMPLE;
					if( !SoundIsPlaying( uiTest2 ) )
						uiTest2 = PlayJA2SampleFromFile( "Sounds\\RAID Dive.wav", RATE_11025, HIGHVOLUME, 1 , MIDDLEPAN );
					}
					break;
				case 't':
				{
/*
					{
						CHAR8		zCdromRootDrive[512];
						HWFILE	hFile;

						if( !GetCdromLocationFromIniFile( zCdromRootDrive ) )
							return;

						//Check if a file exists on the cdrom
						sprintf( zCdromRootDrive, "%sData\\NPC_Speech.slf", zCdromRootDrive );

				//		if( FileExistsNoDB( zCdromRootDrive ) )
						hFile = FileOpen( zCdromRootDrive, FILE_ACCESS_READ | FILE_OPEN_EXISTING, FALSE );
						if( hFile != 0 )
						{
							FileClose( hFile );
							sprintf( zCdromRootDrive, "%sData\\NPC_Speech.slf", zCdromRootDrive );
						}
						else
						{
							sprintf( zCdromRootDrive, "%sData\\NPC_Speech.slf", zCdromRootDrive );
						}

						uiLastTimeToCheckCDromDrive = GetJA2Clock();
					}
*/
				}
				break;


				case 'z':
					SetErrorMode( SEM_FAILCRITICALERRORS );
					break;

				case 'q':
//					ShouldMercSayPrecedentToRepeatOneSelf( 11, 99 );
					break;
#endif
			}
		}
	}
}

void SetOptionsExitScreen( UINT32 uiExitScreen )
{
	guiOptionsScreen = uiExitScreen;
	gfOptionsScreenExit	= TRUE;
}

void BtnOptGotoSaveGameCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		SetOptionsExitScreen( SAVE_LOAD_SCREEN );
		gfSaveGame = TRUE;

		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
}

void BtnOptGotoLoadGameCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		SetOptionsExitScreen( SAVE_LOAD_SCREEN );
		gfSaveGame = FALSE;

		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
}

void BtnOptQuitCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		//Confirm the Exit to the main menu screen
		DoOptionsMessageBox(	MSG_BOX_BASIC_STYLE, zOptionsText[OPT_RETURN_TO_MAIN], OPTIONS_SCREEN, MSG_BOX_FLAG_YESNO, 
								ConfirmQuitToMainMenuMessageBoxCallBack );

///		SetOptionsExitScreen( MAINMENU_SCREEN );

		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
}

// arynn : need more option screen toggles : Functions for button callbacks
void BtnOptPrevCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		ExitOptionsScreen();

		OptionsList_Column_Offset--;
		if(OptionsList_Column_Offset < 0) OptionsList_Column_Offset = 0;

		OptionsScreenInit();	// arynn : This is important to refresh the screen properly, it indicates that we are to store a new SAVE_BUFFER
//		OptionsScreenHandle();	// arynn : unsure about forcing this function now, or letting gameloop's screen management handle

#if defined OPTIONSCREEN_DEBUG_FEEDBACK	
		CHAR16	Information_String1[200];
		CHAR16	Information_String2[200];

		swprintf( Information_String1, L"OptionsList_Column_Offset : %d _ Current_First_Option_Index : %d _ Last_Count_Of_Toggles_Created : %d", 
			OptionsList_Column_Offset,
			Current_First_Option_Index,
			Last_Count_Of_Toggles_Created
			);		
		swprintf( Information_String2, L"%s", Information_String1);

		DoOptionsMessageBox( MSG_BOX_BASIC_STYLE, Information_String2, OPTIONS_SCREEN, MSG_BOX_FLAG_OK, NULL );
		gfExitOptionsDueToMessageBox = FALSE;
#endif



		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
}

void BtnOptNextCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		ExitOptionsScreen();

		OptionsList_Column_Offset++;
		if(OptionsList_Column_Offset > 	MAX_NUMBER_OF_COLUMNS) 
			OptionsList_Column_Offset = MAX_NUMBER_OF_COLUMNS;

		OptionsScreenInit();	// arynn : This is important to refresh the screen properly, it indicates that we are to store a new SAVE_BUFFER
//		OptionsScreenHandle();	// arynn : unsure about forcing this function now, or letting gameloop's screen management handle

#if defined OPTIONSCREEN_DEBUG_FEEDBACK	
		CHAR16	Information_String1[200];
		CHAR16	Information_String2[200];

		swprintf( Information_String1, L"OptionsList_Column_Offset : %d _ Current_First_Option_Index : %d _ Last_Count_Of_Toggles_Created : %d", 
			OptionsList_Column_Offset,
			Current_First_Option_Index,
			Last_Count_Of_Toggles_Created
			);
		//swprintf( Information_String1, L"%d / %d = %d _____ %d / %d = %d ", 
		//	NUM_GAME_OPTIONS, OPT_FIRST_COLUMN_TOGGLE_CUT_OFF, ( (NUM_GAME_OPTIONS / OPT_FIRST_COLUMN_TOGGLE_CUT_OFF)),
		//	OPT_FIRST_COLUMN_TOGGLE_CUT_OFF, NUM_GAME_OPTIONS, ( (OPT_FIRST_COLUMN_TOGGLE_CUT_OFF / NUM_GAME_OPTIONS))
		//	);
		swprintf( Information_String2, L"%s", Information_String1);

		DoOptionsMessageBox( MSG_BOX_BASIC_STYLE, Information_String2, OPTIONS_SCREEN, MSG_BOX_FLAG_OK, NULL );
		gfExitOptionsDueToMessageBox = FALSE;
#endif
#if defined OPTIONSCREEN_DEBUG_FEEDBACK2
		CHAR16	Information_String1[200];
		CHAR16	Information_String2[200];

		swprintf( Information_String1, L"iScreenWidthOffset : %d \n iScreenHeightOffset : %d ", 
			iScreenWidthOffset,
			iScreenHeightOffset
			);
		swprintf( Information_String2, L"%s", Information_String1);

		DoOptionsMessageBox( MSG_BOX_BASIC_STYLE, Information_String2, OPTIONS_SCREEN, MSG_BOX_FLAG_OK, NULL );
		gfExitOptionsDueToMessageBox = FALSE;
#endif

		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
}


void BtnDoneCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );

		SetOptionsExitScreen( guiPreviousOptionScreen );

		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
}

void BtnOptionsTogglesCallback( GUI_BUTTON *btn, INT32 reason )
{
	UINT8	ubButton = (UINT8)MSYS_GetBtnUserData( btn, 0 );

	if( reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		if( btn->uiFlags & BUTTON_CLICKED_ON )
		{
			HandleOptionToggle( ubButton, TRUE, FALSE, FALSE );

//			gGameSettings.fOptions[ ubButton ] = TRUE;
			btn->uiFlags |= BUTTON_CLICKED_ON;
		}
		else
		{
			btn->uiFlags &= ~BUTTON_CLICKED_ON;

			HandleOptionToggle( ubButton, FALSE, FALSE, FALSE);
		}
	}
	else if( reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		if( btn->uiFlags & BUTTON_CLICKED_ON )
		{
			HandleOptionToggle( ubButton, TRUE, TRUE, FALSE );

			btn->uiFlags |= BUTTON_CLICKED_ON;
		}
		else
		{
			btn->uiFlags &= ~BUTTON_CLICKED_ON;

			HandleOptionToggle( ubButton, FALSE, TRUE, FALSE );
		}
	}

}

void HandleOptionToggle( UINT8 ubButton, BOOLEAN fState, BOOLEAN fDown, BOOLEAN fPlaySound )
{
	static UINT32	uiOptionToggleSound = NO_SAMPLE;
//	static	BOOLEAN	fCheckBoxDrawnDownLastTime = FALSE;

	if( fState )
	{
		gGameSettings.fOptions[ ubButton + Current_First_Option_Index ] = TRUE;

		ButtonList[ guiOptionsToggles[ ubButton ] ]->uiFlags |= BUTTON_CLICKED_ON;

		if( fDown )
			DrawCheckBoxButtonOn( guiOptionsToggles[ ubButton ] );
	}
	else
	{
		gGameSettings.fOptions[ ubButton + Current_First_Option_Index ] = FALSE;

		ButtonList[ guiOptionsToggles[ ubButton ] ]->uiFlags &= ~BUTTON_CLICKED_ON;

		if( fDown )
			DrawCheckBoxButtonOff( guiOptionsToggles[ ubButton ] );

		//check to see if the user is unselecting either the spech or subtitles toggle
		if( ubButton + Current_First_Option_Index == TOPTION_SPEECH	|| ubButton + Current_First_Option_Index == TOPTION_SUBTITLES )
		{
			//make sure that at least of of the toggles is still enabled
			// arynn : use of TOPTION_SPEECH and TOPTION_SUBTITLES relies on the fact that,
			//			(ubButton + Current_First_Option_Index) == TOPTION_SPEECH || TOPTION_SUBTITLES
			if( !(ButtonList[ guiOptionsToggles[ TOPTION_SPEECH ] ]->uiFlags & BUTTON_CLICKED_ON) )
			{
				if( !( ButtonList[ guiOptionsToggles[ TOPTION_SUBTITLES ] ]->uiFlags & BUTTON_CLICKED_ON ) )
				{
					gGameSettings.fOptions[ ubButton + Current_First_Option_Index  ] = TRUE;
					ButtonList[ guiOptionsToggles[ ubButton ] ]->uiFlags |= BUTTON_CLICKED_ON;

					//Confirm the Exit to the main menu screen
					DoOptionsMessageBox(	MSG_BOX_BASIC_STYLE, zOptionsText[OPT_NEED_AT_LEAST_SPEECH_OR_SUBTITLE_OPTION_ON], 
											OPTIONS_SCREEN, MSG_BOX_FLAG_OK, NULL );
					gfExitOptionsDueToMessageBox = FALSE;
				}
			}
		}
	}



	//stop the sound if
//	if( SoundIsPlaying( uiOptionToggleSound ) && !fDown )
	{
		SoundStop( uiOptionToggleSound );
	}


	if( fPlaySound )
	{
		if( fDown )
		{
		//				case BTN_SND_CLICK_OFF:
			PlayJA2Sample( BIG_SWITCH3_IN, RATE_11025, BTNVOLUME, 1, MIDDLEPAN );
		}
		else
		{
		//		case BTN_SND_CLICK_ON:
			PlayJA2Sample( BIG_SWITCH3_OUT, RATE_11025, BTNVOLUME, 1, MIDDLEPAN );
		}
	}
}

void SoundFXSliderChangeCallBack( INT32 iNewValue )
{
	SetSoundEffectsVolume( iNewValue );

	guiSoundFxSliderMoving = GetJA2Clock();
}

void SpeechSliderChangeCallBack( INT32 iNewValue )
{
	SetSpeechVolume( iNewValue );

	guiSpeechSliderMoving = GetJA2Clock();
}

void MusicSliderChangeCallBack( INT32 iNewValue )
{
	MusicSetVolume( iNewValue );
}

BOOLEAN DoOptionsMessageBoxWithRect(	UINT8 ubStyle, const STR16 zString, UINT32 uiExitScreen, UINT16 usFlags, 
										MSGBOX_CALLBACK ReturnCallback, SGPRect *pCenteringRect )
{
	// reset exit mode
	gfExitOptionsDueToMessageBox = TRUE;

	// do message box and return
	giOptionsMessageBox = DoMessageBox(	ubStyle,	zString,	uiExitScreen, ( UINT16 ) ( usFlags| MSG_BOX_FLAG_USE_CENTERING_RECT ),	
										ReturnCallback,	pCenteringRect );

	// send back return state
	return( ( giOptionsMessageBox != -1 ) );
}

BOOLEAN DoOptionsMessageBox( UINT8 ubStyle, const STR16 zString, UINT32 uiExitScreen, UINT16 usFlags, MSGBOX_CALLBACK ReturnCallback )
{
	SGPRect CenteringRect= {0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1 };

	// reset exit mode
	gfExitOptionsDueToMessageBox = TRUE;

	// do message box and return
	giOptionsMessageBox = DoMessageBox(	ubStyle,	zString,	uiExitScreen, ( UINT16 ) ( usFlags| MSG_BOX_FLAG_USE_CENTERING_RECT ),	
										ReturnCallback,	&CenteringRect );

	// send back return state
	return( ( giOptionsMessageBox != -1 ) );
}

void ConfirmQuitToMainMenuMessageBoxCallBack( UINT8 bExitValue )
{
	// yes, Quit to main menu
	if( bExitValue == MSG_BOX_RETURN_YES )
	{
		gfEnteredFromMapScreen = FALSE;
		gfExitOptionsAfterMessageBox = TRUE;
		SetOptionsExitScreen( MAINMENU_SCREEN );

		if (is_networked)
		{
			// haydent
			server_disconnect();
			client_disconnect();

		}

		//We want to reinitialize the game
		ReStartingGame();
	}
	else
	{
		gfExitOptionsAfterMessageBox = FALSE;
		gfExitOptionsDueToMessageBox = FALSE;
	}
}

void SetOptionsScreenToggleBoxes()
{
	UINT8	cnt;


// arynn : careful, toggle button[cnt] no longer means gGameSettings.fOptions[cnt], its offset now based on global column offset
	for( cnt=0; cnt<Last_Count_Of_Toggles_Created; cnt++)
	{
		if( gGameSettings.fOptions[ cnt + Current_First_Option_Index ] )
			ButtonList[ guiOptionsToggles[ cnt ] ]->uiFlags |= BUTTON_CLICKED_ON;
		else
			ButtonList[ guiOptionsToggles[ cnt ] ]->uiFlags &= (~BUTTON_CLICKED_ON );
	}
}

void GetOptionsScreenToggleBoxes()
{
	UINT8	cnt;

	for( cnt=0; cnt<Last_Count_Of_Toggles_Created; cnt++)
	{
		if( ButtonList[ guiOptionsToggles[ cnt ] ]->uiFlags & BUTTON_CLICKED_ON )
			gGameSettings.fOptions[ cnt + Current_First_Option_Index ] = TRUE;
		else
			gGameSettings.fOptions[ cnt + Current_First_Option_Index ] = FALSE;
	}
}

void HandleSliderBarMovementSounds()
{
	static UINT32	uiLastSoundFxTime=0;
	static UINT32	uiLastSpeechTime=0;
	static UINT32	uiLastPlayingSoundID = NO_SAMPLE;
	static UINT32	uiLastPlayingSpeechID = NO_SAMPLE;

	if( ( uiLastSoundFxTime - OPT_MUSIC_SLIDER_PLAY_SOUND_DELAY ) > guiSoundFxSliderMoving )
	{
		guiSoundFxSliderMoving = 0xffffffff;

		//The slider has stopped moving, reset the ambient sector sounds ( so it will change the volume )
		if( !DidGameJustStart() )
			HandleNewSectorAmbience( gTilesets[ giCurrentTilesetID ].ubAmbientID );

		if( !SoundIsPlaying( uiLastPlayingSoundID ) )
			uiLastPlayingSoundID = PlayJA2SampleFromFile( "Sounds\\Weapons\\LMG Reload.wav", RATE_11025, HIGHVOLUME, 1 , MIDDLEPAN );
	}
	else
		uiLastSoundFxTime = GetJA2Clock();


	if( ( uiLastSpeechTime - OPT_MUSIC_SLIDER_PLAY_SOUND_DELAY ) > guiSpeechSliderMoving )
	{
		guiSpeechSliderMoving = 0xffffffff;

		if( !SoundIsPlaying( uiLastPlayingSpeechID ) )
			uiLastPlayingSpeechID = PlayJA2GapSample( "BattleSnds\\m_cool.wav", RATE_11025, HIGHVOLUME, 1, MIDDLEPAN, NULL );
	}
	else
		uiLastSpeechTime = GetJA2Clock();

}

void SelectedOptionTextRegionCallBack(MOUSE_REGION * pRegion, INT32 iReason )
{
	UINT8	ubButton = (UINT8)MSYS_GetRegionUserData( pRegion, 0 );

	if (iReason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		HandleOptionToggle( ubButton, (BOOLEAN)(!gGameSettings.fOptions[ ubButton + Current_First_Option_Index ]), FALSE, TRUE );

		InvalidateRegion(pRegion->RegionTopLeftX, pRegion->RegionTopLeftY, pRegion->RegionBottomRightX, pRegion->RegionBottomRightY);
	}


	else if( iReason & MSYS_CALLBACK_REASON_LBUTTON_DWN )//iReason & MSYS_CALLBACK_REASON_LBUTTON_REPEAT ||
	{
		if( gGameSettings.fOptions[ ubButton ] )
		{
			HandleOptionToggle( ubButton, TRUE, TRUE, TRUE );
		}
		else
		{
			HandleOptionToggle( ubButton, FALSE, TRUE, TRUE );
		}
	}
}

void SelectedOptionTextRegionMovementCallBack(MOUSE_REGION * pRegion, INT32 reason )
{
	INT8	bButton = (INT8)MSYS_GetRegionUserData( pRegion, 0 );

	if( reason & MSYS_CALLBACK_REASON_LOST_MOUSE )
	{

		HandleHighLightedText( FALSE );

		gbHighLightedOptionText = -1;

		InvalidateRegion(pRegion->RegionTopLeftX, pRegion->RegionTopLeftY, pRegion->RegionBottomRightX, pRegion->RegionBottomRightY);
	}
	else if( reason & MSYS_CALLBACK_REASON_GAIN_MOUSE )
	{
		gbHighLightedOptionText = bButton;

		InvalidateRegion(pRegion->RegionTopLeftX, pRegion->RegionTopLeftY, pRegion->RegionBottomRightX, pRegion->RegionBottomRightY);
	}
}

void HandleHighLightedText( BOOLEAN fHighLight )
{
	UINT16		usPosX=0;
	UINT16		usPosY=0;
	UINT8		ubCnt;
	INT8		bHighLight=-1;
	UINT16		usWidth;

	static	INT8	bLastRegion = -1;

	if( gbHighLightedOptionText == -1 )
		fHighLight = FALSE;

	//if the user has the mouse in one of the checkboxes
	for( ubCnt=0; ubCnt<Last_Count_Of_Toggles_Created;ubCnt++)
	{
		if( ubCnt == TOPTION_BLOOD_N_GORE && gfHideBloodAndGoreOption )
		{
			//advance to the next
			continue;
		}

		if( ButtonList[ guiOptionsToggles[ ubCnt ] ]->Area.uiFlags & MSYS_MOUSE_IN_AREA )
		{
			gbHighLightedOptionText = ubCnt;
			fHighLight = TRUE;
		}
	}

	// If there is a valid section being highlighted
	if( gbHighLightedOptionText != -1 )
	{
		bLastRegion = gbHighLightedOptionText;
	}

	bHighLight = gbHighLightedOptionText;


	if( bLastRegion != -1 && gbHighLightedOptionText == -1 )
	{
		fHighLight = FALSE;
		bHighLight = bLastRegion;
		bLastRegion = -1;
	}

	//If we are to hide the blood and gore option, and we are to highlight an option past the blood and gore option
	//reduce the highlight number by 1
	if( bHighLight >= TOPTION_BLOOD_N_GORE && gfHideBloodAndGoreOption )
	{
		bHighLight--;
	}

	if( bHighLight != -1 )
	{
		if( bHighLight < OPT_FIRST_COLUMN_TOGGLE_CUT_OFF )
		{
			usPosX = OPT_TOGGLE_BOX_FIRST_COL_TEXT_X;
			usPosY = OPT_TOGGLE_BOX_FIRST_COLUMN_START_Y + OPT_TOGGLE_TEXT_OFFSET_Y + ( bHighLight * OPT_GAP_BETWEEN_TOGGLE_BOXES ) ;
		}
		else
		{
			usPosX = OPT_TOGGLE_BOX_SECOND_TEXT_X;
			usPosY = OPT_TOGGLE_BOX_SECOND_COLUMN_START_Y + OPT_TOGGLE_TEXT_OFFSET_Y + 
					 ( ( bHighLight - OPT_FIRST_COLUMN_TOGGLE_CUT_OFF ) * OPT_GAP_BETWEEN_TOGGLE_BOXES ) ;
		}

		//If we are to hide the blood and gore option, and we are to highlight an option past the blood and gore option
		//reduce the highlight number by 1
		if( bHighLight >= TOPTION_BLOOD_N_GORE && gfHideBloodAndGoreOption )
		{
			bHighLight++;
		}


		usWidth = StringPixLength( zOptionsToggleText[ bHighLight + Current_First_Option_Index ], OPT_MAIN_FONT );

		//if the string is going to wrap, move the string up a bit
		if( usWidth > OPT_TOGGLE_BOX_TEXT_WIDTH )
		{
			if( fHighLight )
				DisplayWrappedString(	usPosX, usPosY, OPT_TOGGLE_BOX_TEXT_WIDTH, 2, OPT_MAIN_FONT, OPT_HIGHLIGHT_COLOR, 
										zOptionsToggleText[ bHighLight + Current_First_Option_Index ], FONT_MCOLOR_BLACK, TRUE, LEFT_JUSTIFIED );

//				DrawTextToScreen( zOptionsToggleText[ bHighLight ], usPosX, usPosY, 0, OPT_MAIN_FONT, OPT_HIGHLIGHT_COLOR, 
//																					FONT_MCOLOR_BLACK, TRUE, LEFT_JUSTIFIED	);
			else
				DisplayWrappedString(	usPosX, usPosY, OPT_TOGGLE_BOX_TEXT_WIDTH, 2, OPT_MAIN_FONT, OPT_MAIN_COLOR, 
										zOptionsToggleText[ bHighLight + Current_First_Option_Index ], FONT_MCOLOR_BLACK, TRUE, LEFT_JUSTIFIED );

//				DrawTextToScreen( zOptionsToggleText[ bHighLight ], usPosX, usPosY, 0, OPT_MAIN_FONT, OPT_MAIN_COLOR, 
//																				FONT_MCOLOR_BLACK, TRUE, LEFT_JUSTIFIED	);
		}
		else
		{
			if( fHighLight )
				DrawTextToScreen(	zOptionsToggleText[ bHighLight + Current_First_Option_Index ], usPosX, usPosY, 0, 
									OPT_MAIN_FONT, OPT_HIGHLIGHT_COLOR, FONT_MCOLOR_BLACK, TRUE, LEFT_JUSTIFIED	);
			else
				DrawTextToScreen(	zOptionsToggleText[ bHighLight + Current_First_Option_Index ], usPosX, usPosY, 0, 
									OPT_MAIN_FONT, OPT_MAIN_COLOR, FONT_MCOLOR_BLACK, TRUE, LEFT_JUSTIFIED	);
		}
	}
}

void SelectedToggleBoxAreaRegionMovementCallBack(MOUSE_REGION * pRegion, INT32 reason )
{
	if( reason & MSYS_CALLBACK_REASON_LOST_MOUSE )
	{
	}
	else if( reason & MSYS_CALLBACK_REASON_GAIN_MOUSE )
	{
		UINT8	ubCnt;

		//loop through all the toggle box's and remove the in area flag
		for( ubCnt=0;ubCnt<Last_Count_Of_Toggles_Created;ubCnt++)
		{
			ButtonList[ guiOptionsToggles[ ubCnt ] ]->Area.uiFlags &= ~MSYS_MOUSE_IN_AREA;
		}

		gbHighLightedOptionText = -1;

		InvalidateRegion(pRegion->RegionTopLeftX, pRegion->RegionTopLeftY, pRegion->RegionBottomRightX, pRegion->RegionBottomRightY);
	}
}
