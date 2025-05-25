#if !defined(_C_SILVERMOUNTAIN_H_)
#define _C_SILVERMOUNTAIN_H_

// -----------------------------------------------------
typedef void(*VERBFUNCT)();
// -----------------------------------------------------

#define SCREEN_WIDTH 40
#define OBJCOUNT     88
#define TOBJCOUNT    28
#define VERBCOUNT    57
#define ROOMCOUNT    80
#define g            28

// -----------------------------------------------------
// FLAGS
#define FLAG_BOOTSON 29
#define FLAG_SHEETONBOAT 30
#define FLAG_BUCKETONBOAT 31
#define FLAG_BOARCAPTURED 32
#define FLAG_EMPTYPOOL 33
#define FLAG_BOOTSUSAGE 39
#define FLAG_TIEDSHEET 40
#define FLAG_STABLEDOOR 43
#define FLAG_COINSCOUNT 44
#define FLAG_RUBBLEBLOCKSYOU 45
#define FLAG_TIEDROPE 53
#define FLAG_GRARGSAPPROACHING 55
#define FLAG_YOUAREDEAD 56
#define FLAG_BOATSINKING 67
// GOSUB_REF
void c_FUNCT_GOTO();
void c_FUNCT_GOTO();
void c_FUNCT_GOTO();
void c_FUNCT_GOTO();
void c_FUNCT_GOTO();
void c_FUNCT_GOTO();
void c_FUNCT_INVENTORY();
void c_FUNCT_GET();
void c_FUNCT_TAKE();
void c_FUNCT_EXAMINE();
void c_FUNCT_READ();
void c_FUNCT_GIVE();
void c_FUNCT_SAY();
void c_FUNCT_PICK();
void c_FUNCT_WEAR();
void c_FUNCT_TIE();
void c_FUNCT_CLIMB();
void c_FUNCT_RIG();
void c_FUNCT_USE();
void c_FUNCT_OPEN();
void c_FUNCT_LIGHT();
void c_FUNCT_FILL();
void c_FUNCT_PLANT();
void c_FUNCT_WATER();
void c_FUNCT_SWING();
void c_FUNCT_EMPTY();
void c_FUNCT_ENTER();
void c_FUNCT_CROSS();
void c_FUNCT_REMOVE();
void c_FUNCT_FEED();
void c_FUNCT_TURN();
void c_FUNCT_DIVE();
void c_FUNCT_BAIL();
void c_FUNCT_LEAVE();
void c_FUNCT_THROW();
void c_FUNCT_INSERT();
void c_FUNCT_BLOW();
void c_FUNCT_DROP();
void c_FUNCT_EAT();
void c_FUNCT_MOVE();
void c_FUNCT_INTO();
void c_FUNCT_RING();
void c_FUNCT_CUT();
void c_FUNCT_HOLD();
void c_FUNCT_BURN();
void c_FUNCT_POISON();
void c_FUNCT_SHOW();
void c_FUNCT_UNLOCK();
void c_FUNCT_WITH();
void c_FUNCT_DRINK();
void c_FUNCT_COUNT();
void c_FUNCT_PAY();
void c_FUNCT_MAKE();
void c_FUNCT_BREAK();
void c_FUNCT_STEAL();
void c_FUNCT_GATHER();
void c_FUNCT_REFLECT();

void c_FUNCT_NULL();
void c_FUNCT_INTOMAZE();
void c_FUNCT_PRESSENTER();

void draw_MSG();

// -----------------------------------------------------

// VERBS
#define VERB_NORTH  1
#define VERB_EAST   2
#define VERB_SOUTH   3
#define VERB_WEST   4
#define VERB_UP   5
#define VERB_DOWN   6
#define VERB_INVENTORY   7
#define VERB_GET   8
#define VERB_TAKE   9
#define VERB_EXAMINE   10
#define VERB_READ   11
#define VERB_GIVE   12
#define VERB_SAY   13
#define VERB_PICK   14
#define VERB_WEAR   15
#define VERB_TIE   16
#define VERB_CLIMB   17
#define VERB_RIG   18
#define VERB_USE   19
#define VERB_OPEN   20
#define VERB_LIGHT   21
#define VERB_FILL   22
#define VERB_PLANT   23
#define VERB_WATER   24
#define VERB_SWING   25
#define VERB_EMPTY   26
#define VERB_ENTER   27
#define VERB_CROSS   28
#define VERB_REMOVE   29
#define VERB_FEED   30
#define VERB_TURN   31
#define VERB_DIVE   32
#define VERB_BAIL   33
#define VERB_LEAVE   34
#define VERB_THROW   35
#define VERB_INSERT   36
#define VERB_BLOW   37
#define VERB_DROP   38
#define VERB_EAT   39
#define VERB_MOVE   40
#define VERB_INTO   41
#define VERB_RING   42
#define VERB_CUT   43
#define VERB_HOLD   44
#define VERB_BURN   45
#define VERB_POISON   46
#define VERB_SHOW   47
#define VERB_UNLOCK   48
#define VERB_WITH   49
#define VERB_DRINK   50
#define VERB_COUNT   51
#define VERB_PAY   52
#define VERB_MAKE   53
#define VERB_BREAK   54
#define VERB_STEAL   55
#define VERB_GATHER   56
#define VERB_REFLECT   57

// -----------------------------------------------------

// OBJECTS
#define OBJ_STATUS_VISIBLE 0
#define OBJ_STATUS_HIDDEN  1

#define OBJ_COINS 1
#define OBJ_SHEET 2
#define OBJ_BOOTS 3
#define OBJ_HORSESHOE 4
#define OBJ_APPLES 5
#define OBJ_BUCKET 6
#define OBJ_AXE 7
#define OBJ_BOAT 8
#define OBJ_PHIAL 9
#define OBJ_REEDS 10
#define OBJ_BONE 11
#define OBJ_SHIELD 12
#define OBJ_PLANKS 13
#define OBJ_ROPE 14
#define OBJ_RING 15
#define OBJ_JUG 16
#define OBJ_NET 17
#define OBJ_SWORD 18
#define OBJ_SILVER_PLATE 19
#define OBJ_UNIFORM 20
#define OBJ_KEY 21
#define OBJ_SEEDS 22
#define OBJ_LAMP 23
#define OBJ_BREAD 24
#define OBJ_BROOCH 25
#define OBJ_MATCHES 26
#define OBJ_STONE_OF_DESTINY 27
#define OBJ_APPLE 28
#define OBJ_BED 29
#define OBJ_CUPBOARD 30
#define OBJ_BRIDGE 31
#define OBJ_TREES 32
#define OBJ_SAIL 33
#define OBJ_KILN 34
#define OBJ_KETCH 35
#define OBJ_BRICKS 36
#define OBJ_WINDMILL 37
#define OBJ_SACKS 38
#define OBJ_OGBANS_BOAR 39
#define OBJ_WHEEL 40
#define OBJ_PONY 41
#define OBJ_GRAVESTONES 42
#define OBJ_POOL 43
#define OBJ_GATES 44
#define OBJ_HANDLE 45
#define OBJ_HUT 46
#define OBJ_VINE 47
#define OBJ_INSCRIPTIONS 48
#define OBJ_TROLL 49
#define OBJ_RUBBLE 50
#define OBJ_HOUND 51
#define OBJ_FOUNTAIN 52
#define OBJ_CIRCLE 53
#define OBJ_MOSAICS 54
#define OBJ_BOOKS 55
#define OBJ_CASKS 56
#define OBJ_WELL 57
#define OBJ_WALLS 58
#define OBJ_RATS 59
#define OBJ_SAFE 60
#define OBJ_COBWEBS 61
#define OBJ_COIN 62
#define OBJ_BELL 63
#define OBJ_UP_SILVER_PLATE 64
#define OBJ_STONES 65
#define OBJ_KITCHENS 66
#define OBJ_GOBLET 67
#define OBJ_WINE 68
#define OBJ_GRARGS 69
#define OBJ_DOOR 70
#define OBJ_AWAKE 71
#define OBJ_GUIDE 72
#define OBJ_PROTECT 73
#define OBJ_LEAD 74
#define OBJ_HELP 75
#define OBJ_CHEST 76
#define OBJ_WATER 77
#define OBJ_STABLES 78
#define OBJ_SLUICE_GATES 79
#define OBJ_POT 80
#define OBJ_STATUE 81
#define OBJ_PINNACLE 82
#define OBJ_MUSIC 83
#define OBJ_MAGIC_WORDS 84
#define OBJ_MISTY_POOL 85
#define OBJ_WELL_BOTTOM 86
#define OBJ_OLD_KILN 87
#define OBJ_MOUNTIAN_HUT 88

// -----------------------------------------------------

// ROOMS
#define ROOM_INVENTORY 0
#define ROOM_HALFDUG_GRAVE 1
#define ROOM_GOBLIN_GRAVEYARD 2
#define ROOM_HOLLOW_TOMB 3
#define ROOM_STALACTITES_AND_STALAGMITES 4
#define ROOM_MAZE_OF_TUNNELS 5
#define ROOM_VAULTED_CAVERN 6
#define ROOM_HIGH_GLASS_GATES 7
#define ROOM_ENTRANCE_HALL_TO_THE_PALACE 8
#define ROOM_GRARG_SENTRY_POST 9
#define ROOM_GUARD_ROOM 10
#define ROOM_MARSHY_INLET 11
#define ROOM_RUSTY_GATES 12
#define ROOM_GAMEKEEPERS_COTTAGE 13
#define ROOM_MISTY_POOL 14
#define ROOM_HIGHWALLED_GARDEN 15
#define ROOM_INSCRIBED_CAVERN 16
#define ROOM_ORNATE_FOUNTIAN 17
#define ROOM_DANK_CORRIDOR 18
#define ROOM_LONG_GALLERY 19
#define ROOM_KITCHENS_OF_THE_PALACE 20
#define ROOM_OLD_KILN 21
#define ROOM_OVERGROWN_TRACK 22
#define ROOM_DISUSED_WATERWHEEL 23
#define ROOM_SLUICE_GATES 24
#define ROOM_GAP_BETWEEN_SOME_BOULDERS 25
#define ROOM_PERILOUS_PATH 26
#define ROOM_SILVER_BELL_IN_THE_ROCK 27
#define ROOM_DUNGEONS_OF_THE_PALACE 28
#define ROOM_BANQUETING_HALL 29
#define ROOM_PALACE_BATTLEMENTS 30
#define ROOM_ISLAND_SHORE 31
#define ROOM_BEACHED_KETCH 32
#define ROOM_BARREN_COUNTRYSIDE 33
#define ROOM_SACKS_ON_THE_UPPER_FLOOR 34
#define ROOM_6FROZEN_POND 35
#define ROOM_MOUNTAIN_HUT 36
#define ROOM_ROW_OF_CASKS 37
#define ROOM_WINE_CELLAR 38
#define ROOM_HALL_OF_TAPESTRIES 39
#define ROOM_DUSTY_LIBRARY 40
#define ROOM_ROUGH_WATER 41
#define ROOM_PLOUGHED_FIELD 42
#define ROOM_55OUTSIDE_A_WINDMILL 43
#define ROOM_LOWER_FLOOR_OF_THE_MILL 44
#define ROOM_ICY_PATH 45
#define ROOM_SCREE_SLOPE 46
#define ROOM_SILVER_CHAMBER 47
#define ROOM_WIZARDS_LAIR 48
#define ROOM_MOSAICFLOORED_HALL 49
#define ROOM_SILVER_THRONE_ROOM 50
#define ROOM_MIDDLE_OF_THE_LAKE 51
#define ROOM_EDGE_OF_AN_ICY_LAKE 52
#define ROOM_PITTED_TRACK 53
#define ROOM_HIGH_PINNACLE 54
#define ROOM_55ABOVE_A_GLACIER 55
#define ROOM_HUGE_FALLEN_OAK 56
#define ROOM_TURRET_ROOM_WITH_A_SLOT_MACHINE 57
#define ROOM_COBWEBBY_ROOM 58
#define ROOM_SAFE_IN_OGBANS_CHAMBER 59
#define ROOM_CUPBOARD_IN_A_CORNER 60
#define ROOM_NARROW_PASSAGE 61
#define ROOM_CAVE 62
#define ROOM_WOODMANS_HUT 63
#define ROOM_SIDE_OF_A_WOODED_VALLEY 64
#define ROOM_STREAM_IN_A_VALLEY_BOTTOM 65
#define ROOM_DEEP_DARK_WOOD 66
#define ROOM_SHADY_HOLLOW 67
#define ROOM_ANCIENT_STONE_CIRCLE 68
#define ROOM_STABLE 69
#define ROOM_ATTIC_BEDROOM 70
#define ROOM_DAMP_WELL_BOTTOM 71
#define ROOM_TOP_OF_A_DEEP_WELL 72
#define ROOM_BURNTOUT_CAMPFIRE 73
#define ROOM_ORCHARD 74
#define ROOM_WEST_END_OF_A_BRIDGE 75
#define ROOM_EAST_END_OF_A_BRIDGE 76
#define ROOM_CROSSROADS 77
#define ROOM_WINDING_ROAD 78
#define ROOM_VILLAGE_OF_RUSTIC_HOUSES 79
#define ROOM_WHITE_COTTAGE 80
#define ROOM_NOWHERE 81

// -----------------------------------------------------

#endif