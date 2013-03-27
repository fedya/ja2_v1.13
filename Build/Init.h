#ifndef _INIT_H
#define _INIT_H

UINT32 InitializeJA2( );
void ShutdownJA2( );

BOOLEAN LoadExternalGameplayData(STR directoryName);
void SetupMaxActionPointsAnimation();
 
//This is an enum to reference to array of ints that holds the values for all these constants.  Gotthard 1/18/07

enum {
AP_MAXIMUM,
AP_MINIMUM,
MIN_APS_TO_INTERRUPT,
AP_MONSTER_MAXIMUM,
AP_VEHICLE_MAXIMUM,
MAX_AP_CARRIED,
AP_YOUNG_MONST_FACTOR,
AP_MONST_FRENZY_FACTOR,
AP_CLAUSTROPHOBE,
AP_AFRAID_OF_INSECTS,
AP_EXCHANGE_PLACES,
AP_REVERSE_MODIFIER,
AP_STEALTH_MODIFIER,
AP_STEAL_ITEM,
AP_TAKE_BLOOD,
AP_TALK,
AP_MOVEMENT_FLAT,
AP_MOVEMENT_GRASS,
AP_MOVEMENT_BUSH,
AP_MOVEMENT_RUBBLE,
AP_MOVEMENT_SHORE,
AP_MOVEMENT_LAKE,
AP_MOVEMENT_OCEAN,
AP_MODIFIER_RUN,
AP_MODIFIER_WALK,
AP_MODIFIER_SWAT,
AP_MODIFIER_CRAWL,
AP_MODIFIER_PACK,
AP_MODIFIER_READY,
AP_CHANGE_FACING,
AP_CHANGE_TARGET,
AP_TOSS_ITEM,
AP_REFUEL_VEHICLE,
AP_RADIO,
AP_CROUCH,
AP_PRONE,
AP_LOOK_STANDING,
AP_LOOK_CROUCHED,
AP_LOOK_PRONE,
AP_READY_KNIFE,
AP_READY_DUAL,
AP_MIN_AIM_ATTACK,
AP_DROP_BOMB,
AP_RELOAD_GUN,
AP_START_FIRST_AID,
AP_START_REPAIR,
AP_GET_WOUNDED_DIVISOR,
AP_FALL_DOWN,
AP_OPEN_DOOR,
AP_PICKLOCK,
AP_EXAMINE_DOOR,
AP_BOOT_DOOR,
AP_USE_CROWBAR,
AP_UNLOCK_DOOR,
AP_LOCK_DOOR,
AP_EXPLODE_DOOR,
AP_UNTRAP_DOOR,
AP_USEWIRECUTTERS,
AP_CLIMBROOF,
AP_CLIMBOFFROOF,
AP_JUMPFENCE,
AP_JUMPFENCEBPACK,
AP_USE_REMOTE,
AP_PULL_TRIGGER,
AP_PUNCH,
AP_PICKUP_ITEM,
AP_GIVE_ITEM,
AP_BURY_MINE,
AP_DISARM_MINE,
AP_DRINK,
AP_CAMOFLAGE,
AP_START_RUN_COST,
AP_ATTACH_CAN,
AP_JUMP_OVER,
AP_BACK_PACK,
AP_OPEN_ZIPPER,
AP_CLOSE_ZIPPER,
AP_CLICK_AIM,
// HEADROCK HAM 3.1: Eight different settings for each aiming click with a scope.
AP_FIRST_CLICK_AIM_SCOPE,
AP_SECOND_CLICK_AIM_SCOPE,
AP_THIRD_CLICK_AIM_SCOPE,
AP_FOURTH_CLICK_AIM_SCOPE,
AP_FIFTH_CLICK_AIM_SCOPE,
AP_SIXTH_CLICK_AIM_SCOPE,
AP_SEVENTH_CLICK_AIM_SCOPE,
AP_EIGHTH_CLICK_AIM_SCOPE,
AP_RELOAD_LOOSE,
AP_UNJAM,

AP_JUMPWINDOW, //WANNE: jump window APs

AP_WRONG_MAG,
AP_MAX_SUPPRESSED,
AP_MAX_TURN_SUPPRESSED,
AP_MIN_LIMIT,
AP_LOST_PER_MORALE_DROP,
AP_SUPPRESSION_MOD,
// HEADROCK HAM 3.5: Ratio of AP loss to Suppression Shock gain.
AP_SUPPRESSION_SHOCK_DIVISOR,
// HEADROCK HAM 3.3: AP loss per point of damage, inflicted when a character is knocked down by a hit to the legs.
AP_LOSS_PER_LEGSHOT_DAMAGE,

AUTOFIRE_SHOTS_AP_VALUE,
BAD_AP_COST,
//Cost to take item from position
AP_INV_FROM_NONE,
AP_INV_FROM_HANDS,
AP_INV_FROM_EQUIPMENT,
AP_INV_FROM_VEST,
AP_INV_FROM_RIG,
AP_INV_FROM_CPACK,
AP_INV_FROM_BPACK,
AP_INV_FROM_SLING,
AP_INV_FROM_KNIFE,
AP_INV_FROM_FACE,
AP_INV_FROM_BIG_POCKET,
AP_INV_FROM_SMALL_POCKET,
//Cost to move item to position
AP_INV_TO_NONE,
AP_INV_TO_HANDS,
AP_INV_TO_EQUIPMENT,
AP_INV_TO_VEST,
AP_INV_TO_RIG,
AP_INV_TO_CPACK,
AP_INV_TO_BPACK,
AP_INV_TO_SLING,
AP_INV_TO_KNIFE,
AP_INV_TO_FACE,
AP_INV_TO_BIG_POCKET,
AP_INV_TO_SMALL_POCKET,
//Max inventory cost
AP_INV_MAX_COST,
AP_JUMPWALL,
AP_JUMPOFFWALL,
AP_FORTIFICATION,
AP_REMOVE_FORTIFICATION,
AP_FILL_SANDBAG,
AP_EAT,
AP_CLEANINGKIT,
AP_DISGUISE,
AP_HANDCUFF,
AP_APPLYITEM,
AP_INVENTORY_ARM,

DEFAULT_APS,
DEFAULT_AIMSKILL,
BP_RATIO_RED_PTS_TO_NORMAL,
BP_RUN_ENERGYCOSTFACTOR,
BP_WALK_ENERGYCOSTFACTOR,
BP_SWAT_ENERGYCOSTFACTOR,
BP_CRAWL_ENERGYCOSTFACTOR,
BP_RADIO,
BP_USE_DETONATOR,
BP_PER_AP_NO_EFFORT,
BP_PER_AP_MIN_EFFORT,
BP_PER_AP_LT_EFFORT,
BP_PER_AP_MOD_EFFORT,
BP_MOVEMENT_FLAT,
BP_MOVEMENT_GRASS,
BP_MOVEMENT_BUSH,
BP_MOVEMENT_RUBBLE,
BP_MOVEMENT_SHORE,
BP_MOVEMENT_LAKE,
BP_MOVEMENT_OCEAN,
BP_MOVEMENT_READY,
BP_CROUCH,
BP_PRONE,
BP_CLIMBROOF,
BP_CLIMBOFFROOF,
BP_JUMPFENCE,
BP_JUMPFENCEBPACK,
BP_STEAL_ITEM,
BP_START_FIRST_AID,
BP_GET_HIT,
BP_GET_WOUNDED,
BP_FALL_DOWN,
BP_OPEN_DOOR,
BP_PICKLOCK,
BP_EXAMINE_DOOR,
BP_BOOT_DOOR,
BP_USE_CROWBAR,
BP_UNLOCK_DOOR,
BP_EXPLODE_DOOR,
BP_UNTRAP_DOOR,
BP_LOCK_DOOR,
BP_USEWIRECUTTERS,
BP_DROP_BOMB,
BP_BURY_MINE,
BP_DISARM_MINE,
BP_JUMP_OVER,
BP_BACK_PACK,
BP_WORK_ZIPPER,
BP_UNJAM,
BP_JUMPOFFWALL,
BP_JUMPWALL,
BP_FORTIFICATION,
BP_REMOVE_FORTIFICATION,
BP_FILL_SANDBAG,
BP_HANDCUFF,
BP_APPLYITEM,
BP_INVENTORY_ARM,
TOTAL_APBP_VALUES
};
#endif
