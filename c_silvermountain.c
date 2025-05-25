// -------------------------------------------------------
// This is a C "translation" of The Mystery of Silver 
// Mountain (1984), originally written in BASIC by Chris 
// Oxlade and Judy Tatchell for Usborne Publishing.
//
// This version goes beyond a straightforward BASIC-to-C 
// rewrite: it aims to enhance readability by "decrypting" 
// the original code, which was intentionally 
// obfuscated—both to save space and to avoid revealing 
// spoilers to users typing it into their 8-bit machines. 
// The goal is to make the code easier to understand and 
// more accessible for future translations into other 
// languages or platforms.
//
// That said, this version remains as faithful as possible 
// to the original game logic and structure.No changes have 
// been made to the adventure content itself, except for 
// avoiding the use of GOTO statements in favor of more 
// structured code.
//
// -------------------------------------------------------
// Marco Giorgini (2025)
// -------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------------------------------
// DEFINES
// -------------------------------------------------------
#include "c_silvermountain.h"
// -------------------------------------------------------

// -------------------------------------------------------
// GAME RESOURCES
// -------------------------------------------------------
char XX[6][4 + 1] = {
  "IN",  "NEAR",  "BY",  "ON",  "",  "AT"
};
char YY[6][7 + 1] = {
  "A",  "THE",  "SOME",  "AN",  "",  "A SMALL"
};
char VERBSZ[VERBCOUNT + 1][15] = {
  "",
  "NORTH",  "EAST",  "SOUTH",  "WEST",  "UP",  "DOWN",
  "INVENTORY",
  "GET",  "TAKE",  "EXAMINE",  "READ",  "GIVE",  "SAY",  "PICK",  "WEAR",  "TIE",  "CLIMB",  "RIG",  "USE",  "OPEN",  "LIGHT",  "FILL",  "PLANT",
  "WATER",  "SWING",  "EMPTY",  "ENTER",  "CROSS",  "REMOVE",  "FEED",  "TURN",  "DIVE",  "BAIL",  "LEAVE",  "THROW",  "INSERT",  "BLOW",  "DROP",
  "EAT",  "MOVE",  "INTO",  "RING",  "CUT",  "HOLD",  "BURN",  "POISON",  "SHOW",  "UNLOCK",  "WITH",  "DRINK",  "COUNT",  "PAY",  "MAKE",  "BREAK",
  "STEAL",  "GATHER",  "REFLECT"
};
VERBFUNCT VERBCALL[VERBCOUNT + 1 + 1] = {
 c_FUNCT_NULL,
 c_FUNCT_GOTO, c_FUNCT_GOTO, c_FUNCT_GOTO, c_FUNCT_GOTO, c_FUNCT_GOTO, c_FUNCT_GOTO,
 c_FUNCT_INVENTORY, c_FUNCT_GET, c_FUNCT_TAKE, c_FUNCT_EXAMINE, c_FUNCT_READ, c_FUNCT_GIVE, c_FUNCT_SAY, c_FUNCT_PICK, c_FUNCT_WEAR, c_FUNCT_TIE, c_FUNCT_CLIMB, c_FUNCT_RIG, c_FUNCT_USE, c_FUNCT_OPEN, c_FUNCT_LIGHT, c_FUNCT_FILL, c_FUNCT_PLANT,
 c_FUNCT_WATER, c_FUNCT_SWING, c_FUNCT_EMPTY, c_FUNCT_ENTER, c_FUNCT_CROSS, c_FUNCT_REMOVE, c_FUNCT_FEED, c_FUNCT_TURN, c_FUNCT_DIVE, c_FUNCT_BAIL, c_FUNCT_LEAVE, c_FUNCT_THROW, c_FUNCT_INSERT, c_FUNCT_BLOW, c_FUNCT_DROP,
 c_FUNCT_EAT, c_FUNCT_MOVE, c_FUNCT_INTO, c_FUNCT_RING, c_FUNCT_CUT, c_FUNCT_HOLD, c_FUNCT_BURN, c_FUNCT_POISON, c_FUNCT_SHOW, c_FUNCT_UNLOCK, c_FUNCT_WITH, c_FUNCT_DRINK, c_FUNCT_COUNT, c_FUNCT_PAY, c_FUNCT_MAKE, c_FUNCT_BREAK,
 c_FUNCT_STEAL, c_FUNCT_GATHER, c_FUNCT_REFLECT,
 c_FUNCT_NULL
};
char ROOMSZ[ROOMCOUNT + 1][48] = {
  "",
  "11HALF-DUG GRAVE",  "12GOBLIN GRAVEYARD",  "11HOLLOW TOMB",  "23STALACTITES AND STALAGMITES",  "11MAZE OF TUNNELS",  "11VAULTED CAVERN",  "23HIGH GLASS GATES",  "12ENTRANCE HALL TO THE PALACE",  "31GRARG SENTRY POST",  "12GUARD ROOM",  
  "31MARSHY INLET",  "23RUSTY GATES",  "12GAMEKEEPER'S COTTAGE",  "31MISTY POOL",  "11HIGH-WALLED GARDEN",  "14INSCRIBED CAVERN",  "34ORNATE FOUNTIAN",  "11DANK CORRIDOR",  "12LONG GALLERY",  "12KITCHENS OF THE PALACE",  
  "34OLD KILN",  "44OVERGROWN TRACK",  "31DISUSED WATERWHEEL",  "33SLUICE GATES",  "11GAP BETWEEN SOME BOULDERS",  "41PERILOUS PATH",  "31SILVER BELL IN THE ROCK",  "12DUNGEONS OF THE PALACE",  "11BANQUETING HALL",  "42PALACE BATTLEMENTS",
  "44ISLAND SHORE",  "31BEACHED KETCH",  "13BARREN COUNTRYSIDE",  "33SACKS ON THE UPPER FLOOR",  "46FROZEN POND",  "21MOUNTAIN HUT",  "31ROW OF CASKS",  "11WINE CELLAR",  "12HALL OF TAPESTRIES",  "11DUSTY LIBRARY",
  "13ROUGH WATER",  "11PLOUGHED FIELD",  "55OUTSIDE A WINDMILL",  "42LOWER FLOOR OF THE MILL",  "44ICY PATH",  "41SCREE SLOPE",  "12SILVER CHAMBER",  "12WIZARD'S LAIR",  "11MOSAIC-FLOORED HALL",  "12SILVER THRONE ROOM",  "12MIDDLE OF THE LAKE",
  "42EDGE OF AN ICY LAKE",  "41PITTED TRACK",  "41HIGH PINNACLE",  "55ABOVE A GLACIER",  "21 HUGE FALLEN OAK",  "11TURRET ROOM WITH A SLOT MACHINE",  "11COBWEBBY ROOM",  "31SAFE IN OGBAN'S CHAMBER",  "31CUPBOARD IN A CORNER",  "11NARROW PASSAGE",
  "16CAVE",  "11WOODMAN'S HUT",  "42SIDE OF A WOODED VALLEY",  "21STREAM IN A VALLEY BOTTOM",  "11DEEP DARK WOOD",  "11SHADY HOLLOW",  "34ANCIENT STONE CIRCLE",  "16STABLE",  "14ATTIC BEDROOM",
  "11DAMP WELL BOTTOM",  "32TOP OF A DEEP WELL",  "31BURNT-OUT CAMPFIRE",  "16ORCHARD",  "62END OF A BRIDGE",  "62END OF A BRIDGE",  "61CROSSROADS",  "41WINDING ROAD",  "11VILLAGE OF RUSTIC HOUSES",  "11WHITE COTTAGE"
};
char ORIG_EXITS[ROOMCOUNT + 1][5] = {
  "",
  "E",  "ESW",  "WE",  "EW",  "EW",  "ESW",  "ESW",  "ES",  "EW",  "SW",
  "S",  "N",  "ES",  "SW",  "S",  "NW",  "N",  "N",  "ES",  "NSW",
  "NS",  "E",  "NSW",  "N",  "NES",  "EW",  "W",  "S",  "NS",  "N",
  "NES",  "W",  "NS",  "D",  "NES",  "SW",  "E",  "NW",  "NS",  "S",
  "NS",  "E",  "NSEW",  "WU",  "UD",  "NS",  "E",  "SW",  "NSE",  "NW",
  "NE",  "EW",  "NSW",  "E",  "WN",  "S",  "E",  "NEW",  "NW",  "S",
  "ES",  "SW",  "NES",  "EW",  "SW",  "NE",  "EW",  "ESW",  "SW",  "ND",
  ".",  "E",  "NEW",  "EW",  "NEW",  "EW",  "EW",  "NEW",  "NEW",  "WU"
};
char OBJSZ[OBJCOUNT + 1][24] = {
  "",
  "3COINS",  "1SHEET",  "3BOOTS",  "1HORSESHOE",  "3APPLES",  "1BUCKET",  "4AXE",  "1BOAT",  "1PHIAL",  "3REEDS",  "1BONE",  "1SHIELD",  "3PLANKS",  "1ROPE",  "1RING",  "1JUG",  "1NET",  "1SWORD",  "1SILVER PLATE",  "1UNIFORM",  "1KEY",  "3SEEDS",  "1LAMP",  "3BREAD",  "1BROOCH",  "3MATCHES",  "2STONE OF DESTINY",
  "4APPLE",
  "BED",  "CUPBOARD",  "BRIDGE",  "TREES",  "SAIL",  "KILN",  "KETCH",  "BRICKS",  "WINDMILL",  "SACKS",  "OGBAN'S BOAR",  "WHEEL",  "PONY",  "GRAVESTONES",  "POOL",  "GATES",  "HANDLE",  "HUT",
  "VINE",  "INSCRIPTIONS",  "TROLL",  "RUBBLE",  "HOUND",  "FOUNTAIN",  "CIRCLE",  "MOSAICS",  "BOOKS",  "CASKS",  "WELL",  "WALLS",  "RATS",  "SAFE",  "COBWEBS",  "COIN",  "BELL",  "UP SILVER PLATE",
  "STONES",  "KITCHENS",  "GOBLET",  "WINE",  "GRARGS",  "DOOR",  "AWAKE",  "GUIDE",  "PROTECT",  "LEAD",  "HELP",  "CHEST",  "WATER",  "STABLES",  "SLUICE GATES",  "POT",  "STATUE",  "PINNACLE",  "MUSIC",
  "MAGIC WORDS",  "MISTY POOL",  "WELL BOTTOM",  "OLD KILN",  "MOUNTIAN HUT"
};
int ORIG_OBJLOC[] = {
  0,
  80,  70,  60,  69,  74,  72,  63,  52,  20,  11,  1,  14,  36,  54,  61,  21,  32,  10,  50,  29,  59,  34,  13,  80,  30,  81,  47,  74
};
int ORIG_HIDDENSTATUS[] = {
  1,  2,  3,  4,  5,  9,  12,  13,  16,  17,  20,  21,  22
};
// -------------------------------------------------------
// GAME DATA VAR
// -------------------------------------------------------
int  OBJLOC[g + 1];
char EXITS[ROOMCOUNT + 1][5];
int  FLAGS[70];
char MAZEPATH[2][8 + 1];
// -------------------------------------------------------
// GAME GLOBAL VAR
// -------------------------------------------------------
int  ROOMID, VERBID, DIRID, OBJID;
char szMSG[256];
char szTT[64],szVV[64];
// -------------------------------------------------------

// -------------------------------------------------------
// SCREEN I/O functions
// -------------------------------------------------------

char*c_gets(char*_Buffer, int size)
{
 int len;
 *_Buffer = 0;
 fgets(_Buffer, size, stdin);
 len = (int)strlen(_Buffer);
 if(len>0)
  while (len--)
   if ((_Buffer[len] == '\r') || (_Buffer[len] == '\n'))
    _Buffer[len] = 0;
   else
    break;
 return _Buffer;
}
char*c_strupr(char*str)
{
 while (*str)
 {
  if ((*str >= 'a') && (*str <= 'z'))
   *str = 'A' + (*str - 'a');
  str++;
 }
 return str;
}

void PRINT(const char * msg)
{
 strcpy(szMSG, msg);
 draw_MSG();
}

char INPUTCH() {
 char cmd[64],ch;
 c_gets(cmd, sizeof(cmd));
 c_strupr(cmd);
 ch = cmd[0];
 return ch;
}

int INPUTNUM() {
 while (1)
 {
  char cmd[64], ch;
  c_gets(cmd, sizeof(cmd));
  c_strupr(cmd);
  ch = cmd[0];
  if ((ch >= '0') && (ch <= '9'))
   return ch - '0';
 }
 return 0;
}

void draw_SEPARATOR() {
 int i;
 for (i = 0; i < SCREEN_WIDTH; i++)
  printf("=");
 printf("\n\n");
}

void draw_SCREEN() {
 int i, len;
 char msg[40];
#if defined(WIN32)
 system("cls");
#else
 system("clear");
#endif
 printf("\n");
 strcpy(msg, "MYSTERY OF SILVER");
 len = (int)strlen(msg);
 for (i = 0; i < (SCREEN_WIDTH - len) / 2; i++)
  printf(" ");
 printf("%s\n", msg);
 strcpy(msg, "MOUNTAIN");
 len = (int)strlen(msg);
 for (i = 0; i < (SCREEN_WIDTH - len) / 2; i++)
  printf(" ");
 printf("%s\n", msg);
 draw_SEPARATOR();
}

void draw_MSG() {
 int i = 0, j = 0, l = 0, pi = 0;
 char line[80];
 for (i = 0; szMSG[i]; i++) {
  if ((j > SCREEN_WIDTH) && l) {
   memcpy(line, szMSG + pi, l - pi);
   line[l - pi] = 0;
   strcat(line, "\n");
   printf(line);
   j = 0;
   i = l;
   pi = i + 1;
  }
  else {
   if (szMSG[i] == ' ')
    l = i;
   j++;
  }
 }
 if (i - pi)
  printf(szMSG + pi);
 printf("\n");
}
// -------------------------------------------------------


// -------------------------------------------------------
// FILE I/O functions
// -------------------------------------------------------
int game_LOAD() {
 FILE*f;
 char name[256];
 printf("\nFILE NAME: ");
 c_gets(name, sizeof(name));
 f = fopen(name, "rb");
 if (f)
 {
  fread(&ROOMID, sizeof(ROOMID), 1, f);
  fread(OBJLOC, sizeof(OBJLOC[0]), sizeof(OBJLOC) / sizeof(OBJLOC[0]), f);
  fread(EXITS, sizeof(EXITS[0]), sizeof(EXITS) / sizeof(EXITS[0]), f);
  fread(FLAGS, sizeof(FLAGS[0]), sizeof(FLAGS) / sizeof(FLAGS[0]), f);
  fread(MAZEPATH, sizeof(MAZEPATH[0]), sizeof(MAZEPATH) / sizeof(MAZEPATH[0]), f);
  fclose(f);
  strcpy(szMSG, "OK");
  return 1;
 }
 else
  return 0;
}

int game_SAVE()
{
 FILE*f;
 char name[256];
 printf("\nFILE NAME: ");
 c_gets(name, sizeof(name));
 f = fopen(name, "wb");
 if (f)
 {
  fwrite(&ROOMID, sizeof(ROOMID), 1, f);
  fwrite(OBJLOC, sizeof(OBJLOC[0]), sizeof(OBJLOC) / sizeof(OBJLOC[0]), f);
  fwrite(EXITS, sizeof(EXITS[0]), sizeof(EXITS) / sizeof(EXITS[0]), f);
  fwrite(FLAGS, sizeof(FLAGS[0]), sizeof(FLAGS) / sizeof(FLAGS[0]), f);
  fwrite(MAZEPATH, sizeof(MAZEPATH[0]), sizeof(MAZEPATH) / sizeof(MAZEPATH[0]), f);
  fclose(f);
  strcpy(szMSG, "OK");
  return 1;
 }
 else
  return 0;
}
// -------------------------------------------------------

// -------------------------------------------------------
//
// -------------------------------------------------------

void game_NEW() {
 int i;
 char D[] = "NSEW", RD[] = "SNWE";
 for (i = 0; i < sizeof(ORIG_EXITS) / sizeof(ORIG_EXITS[0]); i++)
  strcpy(EXITS[i], ORIG_EXITS[i]);
 for (i = 0; i < sizeof(ORIG_OBJLOC) / sizeof(ORIG_OBJLOC[0]); i++)
  OBJLOC[i] = ORIG_OBJLOC[i];
 memset(FLAGS, 0, sizeof(FLAGS));
 for (i = 0; i < sizeof(ORIG_HIDDENSTATUS) / sizeof(ORIG_HIDDENSTATUS[0]); i++)
  FLAGS[ORIG_HIDDENSTATUS[i]] = OBJ_STATUS_HIDDEN;
 FLAGS[41] = 1 + (rand() % 900) + 100;
 FLAGS[42] = 1 + (rand() % 3) + 2;
 FLAGS[FLAG_COINSCOUNT] = 4;
 FLAGS[57] = 68;
 FLAGS[58] = 54;
 FLAGS[59] = 15;
 FLAGS[52] = 1 + (rand() % 3);
 ROOMID = ROOM_CROSSROADS;
 strcpy(szMSG, "GOOD LUCK ON YOUR QUEST!");
 // maze directions
 for (i = 0; i < 8; i++) {
  int v = rand() % 4;
  MAZEPATH[0][i] = D[v];
  MAZEPATH[1][i] = RD[v];
 }
 MAZEPATH[0][i] = MAZEPATH[1][i] = 0;
}

void game_START() {
 int ch;
 draw_SCREEN();
 printf("DO YOU WANT TO\n\n");
 printf("1. START A NEW GAME\n");
 printf("OR 2. CONTINUE A SAVED GAME\n");
 printf("\n\nTYPE IN EITHER 1 OR 2\n?");
 while (1) {
  ch = INPUTNUM();
  if ((ch == 1) || (ch == 2))
   break;
 }
 if (ch == 1)
  game_NEW();
 else
  if(game_LOAD()==0)
   game_NEW();
}

void game_SHOWSTATUS() {
 char         szJJ[256];
 const char * roomname = ROOMSZ[ROOMID];
 const char * exits = EXITS[ROOMID];
 int          I;
 draw_SCREEN();
 strcat(szMSG, ". YOU ARE ");
 if (*XX[roomname[0] - '1']) {
  strcat(szMSG, XX[roomname[0] - '1']);
  strcat(szMSG, " ");
 }
 if (*YY[roomname[1] - '1']) {
  strcat(szMSG, YY[roomname[1] - '1']);
  strcat(szMSG, " ");
 }
 strcat(szMSG, roomname + 2);

 *szJJ = 0;
 for (I = 1; I < TOBJCOUNT; I++)
  if (FLAGS[I] == 0 && OBJLOC[I] == ROOMID)
  {
   const char * OO = OBJSZ[I] + 1;
   int          ARTID=OBJSZ[I][0]-'1';
   strcat(szJJ, " ");strcat(szJJ, YY[ARTID]);strcat(szJJ, " ");
   strcat(szJJ, OO); strcat(szJJ, ",");
  } 
  if (ROOMID == ROOM_BANQUETING_HALL && FLAGS[48] == 0)
   strcat(szJJ," GRARGS FEASTING,");
 if (ROOMID == ROOM_BANQUETING_HALL && FLAGS[48] == 1)
  strcat(szJJ, " A SLEEPING GRARG,");
 if (ROOMID == ROOM_RUSTY_GATES || ROOMID == ROOM_OVERGROWN_TRACK)
  strcat(szJJ, " A PONY,");
 if (ROOMID == ROOM_SIDE_OF_A_WOODED_VALLEY)
  strcat(szJJ, " A HERMIT,");
 if (ROOMID == ROOM_DANK_CORRIDOR && (strcmp(EXITS[ROOM_DANK_CORRIDOR],"N ")==0))
  strcat(szJJ, " AN OAK DOOR,");
 if (ROOMID == ROOM_SAFE_IN_OGBANS_CHAMBER && FLAGS[68] == 1)
  strcat(szJJ, " OGBAN (DEAD),");
 if (*szJJ)
  {
   strcat(szMSG, ", YOU CAN SEE");
   strcat(szMSG, szJJ);
  }
 strcat(szMSG, " AND YOU CAN GO ");
 I = 0;
 while (exits[I]) {
  char s[2];
  s[0] = exits[I];
  s[1] = 0;
  if (I) strcat(szMSG, ", ");
  strcat(szMSG, s);
  I++;
 }
 draw_MSG();
 PRINT("");
 draw_SEPARATOR();
 PRINT("");
 printf("WHAT WILL YOU DO NOW\n?");  
}

void game_WIN()
{
 draw_SCREEN();
 PRINT("HOOORRRRAAAYYYY!");
 PRINT("");
 PRINT("YOU HAVE SUCCEEDED IN YOUR QUEST AND BROUGHT PEACE TO THE LAND");
 draw_MSG(); 
}

void game_FAILED()
{
 draw_SCREEN();
 draw_MSG();
 PRINT("YOU HAVE FAILED IN YOUR QUEST!");
 PRINT("");
 PRINT("BUT YOU ARE GRANTED ANOTHER TRY");
 c_FUNCT_PRESSENTER();
 game_START();
}

int game_GETCOMMAND()
{
 char cmd[128];
 strcpy(szMSG, "PARDON?");
 c_gets(cmd, sizeof(cmd));
 c_strupr(cmd);
 if ((strcmp(cmd, "SAVE") == 0) || (strcmp(cmd, "SAVE GAME") == 0))
  game_SAVE();
 else
 if ((strcmp(cmd, "LOAD") == 0) || (strcmp(cmd, "LOAD GAME") == 0))
   game_LOAD();
 else
  {
   int I;
   *szVV=*szTT=0;
   VERBID = 0; 
   OBJID = 0;
   for(I=0;cmd[I];I++)
    if (cmd[I] == ' ')
    {
     if(*szVV==0)
      memcpy(szVV, cmd, I);
     strcpy(szTT, cmd + I + 1);
     break;
    }
   if(*szVV==0)
    strcpy(szVV, cmd);
   if(*szVV)
    for (I = 1; I <= VERBCOUNT; I++)
     if( (strcmp(szVV, VERBSZ[I]) == 0) || (memcmp(szVV, VERBSZ[I],3) == 0) )
     {
      VERBID = I; 
      break;
     }  
   if (*szTT)
    for (I = 1; I <= OBJCOUNT; I++)
     if (strcmp(szTT, OBJSZ[I]+(I<TOBJCOUNT)) == 0)
     {
      OBJID = I; 
      break;
     }
   if (VERBID == 0) 
    VERBID = VERBCOUNT + 1;
   if (*szTT==0)
    strcpy(szMSG, "I NEED TWO WORDS");
   if (VERBID > VERBCOUNT)
    strcpy(szMSG, "TRY SOMETHING ELSE");
   if (VERBID > VERBCOUNT  &&  OBJID == 0)
    sprintf(szMSG, "YOU CANNOT %s",cmd);
   if( (OBJID > TOBJCOUNT || OBJID == 0) || (VERBID == VERB_GET || VERBID == VERB_TAKE || VERBID == VERB_PICK || VERBID == VERB_CLIMB || VERBID == VERB_HOLD || VERBID > VERB_BREAK) )
    ;
   else
    if (VERBID < VERBCOUNT  &&  OBJLOC[OBJID] != 0)
     sprintf(szMSG, "YOU DO NOT HAVE THE %s",szTT);
   if (ROOMID == ROOM_HUGE_FALLEN_OAK && FLAGS[35] == 0 && VERBID != VERB_BLOW && VERBID != VERB_MAKE)
    {
     strcpy(szMSG, "THE GHOST OF THE GOBLIN GUARDIAN HAS GOT YOU!"); 
     return 0;
    }
   else
    {
     if (VERBID == VERB_HOLD || VERBID == VERB_SHOW || VERBID == VERB_USE || VERBID == VERB_REFLECT || VERBID == VERB_WITH)
      ;
     else
      if (ROOMID == ROOM_WIZARDS_LAIR && FLAGS[63] == 0)
      {
       strcpy(szMSG, "THE WIZARD HAS YOU IN HIS GLARE");
       return 0;
      }

     VERBCALL[VERBID]();

     if (FLAGS[62] == 1)
      return 1;
     else
      {
       if (ROOMID == ROOM_ROUGH_WATER)
       {
        FLAGS[67] = FLAGS[67] + 1; if (FLAGS[67] == 10)
        {
         FLAGS[FLAG_YOUAREDEAD] = 1; strcpy(szMSG, "YOU SANK!");;
        };
       }
       if (ROOMID == ROOM_HUGE_FALLEN_OAK && FLAGS[35] == 0 && OBJLOC[OBJ_REEDS] != 0)
       {
        strcpy(szMSG, "THE GHOST OF THE GOBLIN GUARDIAN GETS YOU!");
        FLAGS[FLAG_YOUAREDEAD] = 1;
       }
       if (FLAGS[FLAG_YOUAREDEAD] == 0)
        ;
       else
        return 2;
      }
    }          
  }
 return 0;
}

// -------------------------------------------------------
// "Translation" of the original
// BASIC code
// -------------------------------------------------------

void c_FUNCT_NULL(){
}

void c_FUNCT_GOTO() {
 int OM,I;

 DIRID = VERBID;
 if (DIRID == VERB_UP)
  DIRID = VERB_NORTH;
 else
  if (DIRID == VERB_DOWN)
   DIRID = VERB_SOUTH;

 if (!((ROOMID == ROOM_WEST_END_OF_A_BRIDGE && DIRID == VERB_EAST) || (ROOMID == ROOM_EAST_END_OF_A_BRIDGE && DIRID == VERB_WEST)) || FLAGS[64] == 1)
  ;
 else {
  strcpy(szMSG, "A TROLL STOPS YOU CROSSING");
  return;
 }
 if (FLAGS[64] == 1)
  FLAGS[64] = 0;
 if (FLAGS[51] == 1 || FLAGS[FLAG_BOOTSON] == 1)
  ;
 else {
  if (FLAGS[55] == 1) {
   FLAGS[FLAG_YOUAREDEAD] = 1;
   strcpy(szMSG, "GRARGS HAVE GOT YOU!");
   return;
  }
  if (ROOMID == ROOM_BANQUETING_HALL && FLAGS[48] == 0) {
   strcpy(szMSG, "GRARGS WILL SEE YOU!");
   return;
  }
  if (ROOMID == ROOM_BURNTOUT_CAMPFIRE || ROOMID == ROOM_PLOUGHED_FIELD || ROOMID == ROOM_GRARG_SENTRY_POST || ROOMID == ROOM_GUARD_ROOM) {
   strcpy(szMSG, "A GRARG PATROL APPROACHES");
   FLAGS[55] = 1;
   return;
  }
 }
 if (OBJLOC[OBJ_BOAT] == ROOM_INVENTORY && ((ROOMID == ROOM_EDGE_OF_AN_ICY_LAKE && DIRID == VERB_EAST) || (ROOMID == ROOM_ISLAND_SHORE && DIRID != VERB_SOUTH))) {
  strcpy(szMSG, "THE BOAT IS TOO HEAVY");
  return;
 }
 if (OBJLOC[OBJ_BOAT] != 0 && ((ROOMID == ROOM_EDGE_OF_AN_ICY_LAKE && DIRID == VERB_WEST) || (ROOMID == ROOM_ISLAND_SHORE && DIRID == VERB_SOUTH))) {
  strcpy(szMSG, "YOU CANNOT SWIM");
  return;
 }
 if (ROOMID == ROOM_EDGE_OF_AN_ICY_LAKE && OBJLOC[OBJ_BOAT] == ROOM_INVENTORY && DIRID == VERB_WEST && FLAGS[FLAG_SHEETONBOAT] == 0) {
  strcpy(szMSG, "NO POWER!");
  return;
 }
 if (ROOMID == ROOM_ROUGH_WATER && DIRID == VERB_SOUTH && FLAGS[FLAG_BUCKETONBOAT] == 0) {
  strcpy(szMSG, "THE BOAT IS SINKING!");
  return;
 }
 if (ROOMID == ROOM_BARREN_COUNTRYSIDE && DIRID == VERB_NORTH && FLAGS[FLAG_BOARCAPTURED] == 0) {
  strcpy(szMSG, "OGBAN'S BOAR BLOCKS YOUR PATH");
  return;
 }
 if (((ROOMID == ROOM_HOLLOW_TOMB && DIRID == VERB_EAST) || (ROOMID == ROOM_STALACTITES_AND_STALAGMITES && DIRID == VERB_WEST)) && FLAGS[45] == 0) {
  strcpy(szMSG, "A PILE OF RUBBLE BLOCKS YOUR PATH");
  return;
 }
 if (ROOMID == ROOM_FROZEN_POND && OBJLOC[OBJ_PLANKS] != ROOMID) {
  strcpy(szMSG, "THE ICE IS BREAKING!");
  return;
 }
 if (ROOMID == ROOM_MAZE_OF_TUNNELS && (DIRID == VERB_EAST || DIRID == VERB_WEST))
  c_FUNCT_INTOMAZE();
 if (ROOMID == ROOM_STALACTITES_AND_STALAGMITES && DIRID == VERB_WEST) {
  strcpy(szMSG, "PASSAGE IS TOO STEEP");
  return;
 }
 if (ROOMID == ROOM_HIGH_GLASS_GATES && DIRID == VERB_EAST && FLAGS[46] == 0) {
  strcpy(szMSG, "A HUGE HOUND BARS YOUR WAY");
  return;
 }
 if ((ROOMID == ROOM_WINE_CELLAR || ROOMID == ROOM_ROW_OF_CASKS) && FLAGS[50] == 0) {
  strcpy(szMSG, "IT IS TOO DARK");
  return;
 }
 if (ROOMID == ROOM_MOSAICFLOORED_HALL && DIRID == VERB_EAST && FLAGS[54] == 0) {
  strcpy(szMSG, "MYSTERIOUS FORCES HOLD YOU BACK");
  return;
 }
 if (ROOMID == ROOM_MOSAICFLOORED_HALL && DIRID == VERB_SOUTH && FLAGS[68] == 0) {
  strcpy(szMSG, "YOU MET OGBAN!!!");
  FLAGS[FLAG_YOUAREDEAD] = 1;
  return;
 }
 if (ROOMID == ROOM_WINE_CELLAR && FLAGS[65] == 0) {
  strcpy(szMSG, "RATS NIBBLE YOUR ANKLES");
  return;
 }
 if (ROOMID == ROOM_COBWEBBY_ROOM && (DIRID == VERB_NORTH || DIRID == VERB_WEST) && FLAGS[66] == 0) {
  strcpy(szMSG, "YOU GET CAUGHT IN THE COBWEBS!");
  return;
 }
 if (ROOMID == ROOM_WIZARDS_LAIR && DIRID == VERB_WEST && FLAGS[70] == 0) {
  strcpy(szMSG, "THE DOOR DOES NOT OPEN");
  return;
 }
 if (ROOMID == ROOM_DUSTY_LIBRARY && FLAGS[47] == 1)
  FLAGS[68] = 1;
 if (ROOMID == ROOM_ROW_OF_CASKS && DIRID == VERB_WEST && (strcmp(EXITS[ROOM_ROW_OF_CASKS], "EW ") == 0)) {
  ROOMID = ROOM_SHADY_HOLLOW;
  strcpy(szMSG, "THE PASSAGE WAS STEEP!");
  return;
 }
 if (ROOMID == ROOM_BANQUETING_HALL && DIRID == VERB_SOUTH) {
  FLAGS[48] = 1;
  FLAGS[OBJ_UNIFORM] = OBJ_STATUS_VISIBLE;
 }
 if (ROOMID == ROOM_ENTRANCE_HALL_TO_THE_PALACE && DIRID == VERB_EAST)
  FLAGS[46] = 0;
 OM = ROOMID;
 for (I = 0; EXITS[ROOMID][I]; I++) {
  char KK = EXITS[ROOMID][I];
  if ((KK == 'N' || KK == 'U') && DIRID == VERB_NORTH) {
   ROOMID = ROOMID - 10;
   break;
  }
  else
   if (KK == 'E' && DIRID == VERB_EAST) {
    ROOMID = ROOMID + 1;
    break;
   }
   else
    if ((KK == 'S' || KK == 'D') && DIRID == VERB_SOUTH) {
     ROOMID = ROOMID + 10;
     break;
    }
    else
     if (KK == 'W' && DIRID == VERB_WEST) {
      ROOMID = ROOMID - 1;
      break;
     }
 }
 strcpy(szMSG, "OK");
 if (ROOMID == OM)
  strcpy(szMSG, "YOU CANNOT GO THAT WAY");

 if (((OM == ROOM_WEST_END_OF_A_BRIDGE && DIRID == VERB_EAST) || (OM == ROOM_EAST_END_OF_A_BRIDGE && DIRID == VERB_WEST)))
  strcpy(szMSG, "OK. YOU CROSSED");
 if (FLAGS[FLAG_BOOTSON] == 1)
  FLAGS[FLAG_BOOTSUSAGE]++;
 if (FLAGS[FLAG_BOOTSUSAGE] > 5 && FLAGS[FLAG_BOOTSON] == 1) {
  strcpy(szMSG, "BOOTS HAVE WORN OUT");
  FLAGS[FLAG_BOOTSON] = 0;
  OBJLOC[OBJ_BOOTS] = ROOM_NOWHERE;
 }
}

void c_FUNCT_PRESSENTER() {
 PRINT("PRESS ENTER TO CONTINUE");
 INPUTCH();
}

void c_FUNCT_INVENTORY() { 
 int I,OC;
 OC = 0;
 strcpy(szMSG, "YOU HAVE ");
 for (I = 1; I <= TOBJCOUNT; I++) {
  const char * OO = OBJSZ[I] + 1;
  if (I == 1 && OBJLOC[OBJ_COINS] == ROOM_INVENTORY && FLAGS[FLAG_COINSCOUNT] == 1)
   OO = "COIN";
  if (I == TOBJCOUNT && OBJLOC[OBJ_APPLES] == ROOM_INVENTORY)
   ;
  else
   if (OBJLOC[I] == ROOM_INVENTORY) {
    if (OC)
     strcat(szMSG,",");
    strcat(szMSG, OO);
    OC++;
   }
 }
 if (OC == 0)
  strcat(szMSG, "NOTHING");
 draw_MSG();
 *szMSG = 0;
 draw_MSG();
 c_FUNCT_PRESSENTER();
 return;
}

void c_FUNCT_STEAL() {
 c_FUNCT_GET();
}
void c_FUNCT_GATHER() {
 c_FUNCT_GET();
}
void c_FUNCT_TAKE() {
 c_FUNCT_GET();
}
void c_FUNCT_GET() {
 int CO, I;
 if (((ROOMID == ROOM_STREAM_IN_A_VALLEY_BOTTOM) && (OBJID == OBJ_WATER))) {
  strcpy(szMSG, "HOW?");
  return;
 }
 if (((ROOMID == ROOM_ROUGH_WATER) && (OBJID == OBJ_WATER)) || ((ROOMID == ROOM_MIDDLE_OF_THE_LAKE) && (OBJID == OBJ_WATER))) {
  OBJID = OBJ_JUG;
  c_FUNCT_FILL();
  return;
 }
 if (OBJID == OBJ_SACKS) {
  strcpy(szMSG, "TOO HEAVY!");
  return;
 }
 if (OBJID == OBJ_HORSESHOE && FLAGS[43] == 0) {
  strcpy(szMSG, "IT IS FIRMLY NAILED ON!");
  return;
 }
 CO = 0;
 for (I = 1; I < TOBJCOUNT; I++)
  if (OBJLOC[I] == ROOM_INVENTORY)
   CO++;
 if (CO > 13) {
  strcpy(szMSG, "YOU CANNOT CARRY ANY MORE");
  return;
 }
 if (OBJID > TOBJCOUNT) {
  sprintf(szMSG, "YOU CANNOT GET THE %s", szTT);
  return;
 }
 if (OBJID == 0)
  return;
 if (OBJLOC[OBJID] != ROOMID)
  strcpy(szMSG, "IT IS NOT HERE!");
 if (FLAGS[OBJID] == OBJ_STATUS_HIDDEN)
  sprintf(szMSG, "WHAT %s?", szTT);
 if (OBJLOC[OBJID] == ROOM_INVENTORY)
  strcpy(szMSG, "YOU ALREADY HAVE IT");
 if (OBJLOC[OBJID] == ROOMID && FLAGS[OBJID] == OBJ_STATUS_VISIBLE ) {
  OBJLOC[OBJID] = ROOM_INVENTORY;
  sprintf(szMSG, "YOU HAVE THE %s", szTT);
 }
 if (OBJID == OBJ_APPLE)
  OBJLOC[OBJ_APPLES] = ROOM_NOWHERE;
 if (OBJID == OBJ_APPLES)
  OBJLOC[OBJ_APPLE] = ROOM_INVENTORY;
 if (OBJLOC[OBJ_HORSESHOE] == ROOM_INVENTORY && OBJLOC[OBJ_SHIELD] == ROOM_INVENTORY && OBJLOC[OBJ_RING] == ROOM_INVENTORY)
  FLAGS[54] = 1;
 if (OBJID == OBJ_BOAT && FLAGS[FLAG_SHEETONBOAT] == 1)
  OBJLOC[OBJ_SHEET] = ROOM_INVENTORY;
 if (OBJID == OBJ_SHEET)
  FLAGS[FLAG_SHEETONBOAT] = 0;
}

void c_FUNCT_COUNT() {
 c_FUNCT_EXAMINE();
}
void c_FUNCT_READ() {
 c_FUNCT_EXAMINE();
}
void c_FUNCT_EXAMINE() {
 strcpy(szMSG, "YOU SEE WHAT YOU MIGHT EXPECT!");
 if (OBJID > 0)
  strcpy(szMSG, "NOTHING SPECIAL");
 if (OBJID == OBJ_HUT || OBJID == OBJ_MOUNTIAN_HUT)
  c_FUNCT_ENTER();
 if (((ROOMID == ROOM_WHITE_COTTAGE) && (OBJID == OBJ_CHEST)))
  strcpy(szMSG, "IT IS EMPTY");
 if (((ROOMID == ROOM_WHITE_COTTAGE) && (OBJID == OBJ_POT))) {
  strcpy(szMSG, "AHA!");
  FLAGS[OBJ_COINS] = OBJ_STATUS_VISIBLE;
 }
 if (((ROOMID == ROOM_ATTIC_BEDROOM) && (OBJID == OBJ_BED))) {
  strcpy(szMSG, "OK");
  FLAGS[OBJ_SHEET] = OBJ_STATUS_VISIBLE;
 }
 if (OBJID == OBJ_UNIFORM) {
  strcpy(szMSG, "MATCHES IN POCKET");
  OBJLOC[OBJ_MATCHES] = ROOM_INVENTORY;
 }
 if (((ROOMID == ROOM_INSCRIBED_CAVERN) && (OBJID == OBJ_INSCRIPTIONS))) 
  sprintf(szMSG, "THERE ARE SOME LETTERS '%s'", MAZEPATH[2]); 
 if (((ROOMID == ROOM_ORCHARD) && (OBJID == OBJ_TREES))) {
  strcpy(szMSG, "THEY ARE APPLE TREES");
  FLAGS[OBJ_APPLES] = OBJ_STATUS_VISIBLE;
 }
 if (((ROOMID == ROOM_OLD_KILN) && (OBJID == OBJ_KILN)) || ((ROOMID == ROOM_OLD_KILN) && (OBJID == OBJ_OLD_KILN))) {
  strcpy(szMSG, "OK");
  FLAGS[OBJ_JUG] = OBJ_STATUS_VISIBLE;
 }
 if (OBJID == OBJ_KETCH) {
  strcpy(szMSG, "IT IS FISHY!");
  FLAGS[OBJ_NET] = OBJ_STATUS_VISIBLE;
 }
 if (((ROOMID == ROOM_SACKS_ON_THE_UPPER_FLOOR) && (OBJID == OBJ_SACKS))) {
  strcpy(szMSG, "OK");
  FLAGS[OBJ_SEEDS] = OBJ_STATUS_VISIBLE;
 }
 if (((ROOMID == ROOM_GOBLIN_GRAVEYARD) && (OBJID == OBJ_GRAVESTONES)))
  strcpy(szMSG, "A FADED INSCRIPTION");
 if ((((ROOMID == ROOM_MISTY_POOL) && (OBJID == OBJ_POOL)) || ((ROOMID == ROOM_MISTY_POOL) && (OBJID == OBJ_MISTY_POOL))) && FLAGS[FLAG_EMPTYPOOL] == 0)
  strcpy(szMSG, "A GLIMMERING FROM THE DEPTHS"); 
 if ((((ROOMID == ROOM_MISTY_POOL) && (OBJID == OBJ_POOL)) || ((ROOMID == ROOM_MISTY_POOL) && (OBJID == OBJ_MISTY_POOL))) && FLAGS[FLAG_EMPTYPOOL] == 1) {
  strcpy(szMSG, "SOMETHING HERE....");
  FLAGS[OBJ_SHIELD] = OBJ_STATUS_VISIBLE;
 }
 if (((ROOMID == ROOM_SLUICE_GATES) && (OBJID == OBJ_SLUICE_GATES)) || ((ROOMID == ROOM_SLUICE_GATES) && (OBJID == OBJ_GATES)))
  strcpy(szMSG, "THERE IS A HANDLE");
 if (OBJID == OBJ_PHIAL)
  strcpy(szMSG, "THE LABEL READS 'POISON'");
 if (((ROOMID == ROOM_DUSTY_LIBRARY) && (OBJID == OBJ_BOOKS))) {
  const char*roomname = ROOMSZ[FLAGS[FLAGS[52] + ROOM_TURRET_ROOM_WITH_A_SLOT_MACHINE]];
  sprintf(szMSG, "MAGIC WORDS LIE AT THE CROSSROADS, THE FOUNTAIN AND THE %s", roomname+2);
 }
 if (((ROOMID == ROOM_BANQUETING_HALL) && (OBJID == OBJ_GRARGS)) && FLAGS[48] == 1) {
  strcpy(szMSG, "VERY UGLY!");
 }
 if (((ROOMID == ROOM_DAMP_WELL_BOTTOM) && (OBJID == OBJ_WALLS)) || ((ROOMID == ROOM_DAMP_WELL_BOTTOM) && (OBJID == OBJ_WELL_BOTTOM))) 
  strcpy(szMSG, "THERE ARE LOOSE BRICKS"); 
 if (ROOMID == ROOM_MOSAICFLOORED_HALL) 
  strcpy(szMSG, "VERY INTERSTING!"); 
 if (OBJID == OBJ_FOUNTAIN || OBJID == OBJ_PINNACLE || OBJID == OBJ_STATUE) 
  strcpy(szMSG, "INTERESTING!");
 if (((ROOMID == ROOM_STABLE) && (OBJID == OBJ_STABLES))) 
  strcpy(szMSG, "THERE IS A WOODEN DOOR"); 
 if (((ROOMID == ROOM_STABLE) && (OBJID == OBJ_DOOR))) {
  strcpy(szMSG, "YOU FOUND SOMETHING");
  FLAGS[OBJ_HORSESHOE] = OBJ_STATUS_VISIBLE;
 }
 if (((ROOMID == ROOM_KITCHENS_OF_THE_PALACE) && (OBJID == OBJ_KITCHENS))) 
  strcpy(szMSG, "A LARGE CUPBOARD IN THE CORNER"); 
 if (((ROOMID == ROOM_ANCIENT_STONE_CIRCLE) && (OBJID == OBJ_STONES)) || ((ROOMID == ROOM_ANCIENT_STONE_CIRCLE) && (OBJID == OBJ_CIRCLE))) 
  strcpy(szMSG, "THERE ARE NINE STONES"); 
 if (((ROOMID == ROOM_GOBLIN_GRAVEYARD) && (OBJID == OBJ_INSCRIPTIONS))) 
  strcpy(szMSG, "A FADED WORD - 'M R H S'"); 
}
void c_FUNCT_GIVE() {
 if (ROOMID == ROOM_SIDE_OF_A_WOODED_VALLEY) {
  strcpy(szMSG, "HE GIVES IT BACK!");
 }
 if (((ROOMID == ROOM_SIDE_OF_A_WOODED_VALLEY) && (OBJID == OBJ_BROOCH))) {
  sprintf(szMSG, "HE TAKES IT AND SAYS %d RINGS ARE NEEDED'", FLAGS[42]);
  OBJLOC[OBJ_BROOCH] = ROOM_NOWHERE;
 }
 if (ROOMID == ROOM_WEST_END_OF_A_BRIDGE || ROOMID == ROOM_EAST_END_OF_A_BRIDGE) {
  strcpy(szMSG, "HE DOES NOT WANT IT");
 }
 if (OBJID == OBJ_COIN && FLAGS[FLAG_COINSCOUNT] == 0) {
  strcpy(szMSG, "YOU HAVE RUN OUT!");
 }
 if ((((ROOMID == ROOM_WEST_END_OF_A_BRIDGE) && (OBJID == OBJ_COIN)) || ((ROOMID == ROOM_EAST_END_OF_A_BRIDGE) && (OBJID == OBJ_COIN))) && FLAGS[FLAG_COINSCOUNT] > 0 && OBJLOC[OBJ_COINS] == ROOM_INVENTORY) {
  strcpy(szMSG, "HE TAKES IT");
  FLAGS[64] = 1;
 }
 if (FLAGS[64] == 1) {
  FLAGS[FLAG_COINSCOUNT] = FLAGS[FLAG_COINSCOUNT] - 1;
  if (FLAGS[FLAG_COINSCOUNT] == 0) {
   OBJLOC[OBJ_COINS] = ROOM_NOWHERE;
  };
 }
 if (OBJID == OBJ_COINS) {
  strcpy(szMSG, "HE TAKES THEM ALL!");
  OBJLOC[OBJ_COINS] = ROOM_NOWHERE;
  FLAGS[64] = 1;
  FLAGS[FLAG_COINSCOUNT] = 0;
 }
 if (((ROOMID == ROOM_OVERGROWN_TRACK) && (OBJID == OBJ_APPLE)) && OBJLOC[OBJ_APPLES] == ROOM_NOWHERE) {
  strcpy(szMSG, "HE LEADS YOU NORTH");
  OBJLOC[OBJ_APPLE] = ROOM_NOWHERE;
  ROOMID = ROOM_RUSTY_GATES;
 }
 if ((((ROOMID == ROOM_OVERGROWN_TRACK) && (OBJID == OBJ_APPLE)) && OBJLOC[OBJ_APPLES] == ROOM_INVENTORY) || ((ROOMID == ROOM_OVERGROWN_TRACK) && (OBJID == OBJ_APPLES))) {
  strcpy(szMSG, "HE LEADS YOU NORTH");
  ROOMID = ROOM_RUSTY_GATES;
 }
 if ((((ROOMID == ROOM_RUSTY_GATES) && (OBJID == OBJ_APPLE)) && OBJLOC[OBJ_APPLES] == ROOM_INVENTORY) || ((ROOMID == ROOM_RUSTY_GATES) && (OBJID == OBJ_APPLES))) {
  strcpy(szMSG, "HE LEADS YOU SOUTH");
  ROOMID = ROOM_OVERGROWN_TRACK;
 }
 if (((ROOMID == ROOM_WINE_CELLAR) && (OBJID == OBJ_APPLES)) || ((ROOMID == ROOM_WINE_CELLAR) && (OBJID == OBJ_BREAD))) {
  strcpy(szMSG, "THEY SCURRY AWAY");
  OBJLOC[OBJID] = ROOM_NOWHERE;
  FLAGS[65] = 1;
 }
 if (((ROOMID == ROOM_HIGH_GLASS_GATES) && (OBJID == OBJ_BONE))) {
  FLAGS[46] = 1;
  strcpy(szMSG, "HE IS DISTRACTED");
 }
 if (OBJID == 0 || OBJID > TOBJCOUNT)
  return;
 if (ROOMID == ROOM_HIGH_GLASS_GATES || ROOMID == ROOM_BARREN_COUNTRYSIDE) {
  strcpy(szMSG, "HE EATS IT!");
  OBJLOC[OBJID] = ROOM_NOWHERE;
 }
}

void c_FUNCT_SAY() {
 strcpy(szMSG, "YOU SAID IT");
 if (OBJID == OBJ_MAGIC_WORDS) {
  strcpy(szMSG, "YOU MUST SAY THEM ONE BY ONE!");
  return;
 }
 if (ROOMID != ROOM_SILVER_CHAMBER || OBJID < OBJ_AWAKE || OBJID > OBJ_HELP || OBJLOC[OBJ_STONE_OF_DESTINY] != 0)
  return;
 if (OBJID == OBJ_AWAKE && FLAGS[60] == 0) {
  strcpy(szMSG, "THE MOUNTAIN RUMBLES!");
  FLAGS[60] = 1;
  return;
 }
 if (OBJID == OBJ_GUIDE && FLAGS[60] == 1 && FLAGS[61] == 0) {
  strcpy(szMSG, "TOWERS FALL DOWN!");
  FLAGS[61] = 1;
  return;
 }
 if (OBJID == (FLAGS[52] + 73) && FLAGS[60] == 1 && FLAGS[61] == 1) {
  FLAGS[62] = 1;
  return;
 }
 strcpy(szMSG, "THE WRONG SACRED WORD!");
 FLAGS[FLAG_YOUAREDEAD] = 1;
}

void c_FUNCT_PICK() {
 if (OBJID == OBJ_APPLES || OBJID == OBJ_REEDS || OBJID == OBJ_APPLE)
  c_FUNCT_GET();
}
void c_FUNCT_WEAR() {
 if (OBJID == OBJ_BOOTS) {
  FLAGS[FLAG_BOOTSON] = 1;
  strcpy(szMSG, "YOU ARE INVISIBLE");
  FLAGS[55] = 0;
 }
 if (OBJID == OBJ_UNIFORM) {
  FLAGS[51] = 1;
  strcpy(szMSG, "YOU ARE DISGUISED");
  FLAGS[55] = 0;
 }
}

void c_FUNCT_TIE() {
 if (OBJID == OBJ_SHEET || OBJID == OBJ_ROPE) {
  strcpy(szMSG, "NOTHING TO TIE IT TO!");
 }
 if (((ROOMID == ROOM_TOP_OF_A_DEEP_WELL) && (OBJID == OBJ_ROPE))) {
  strcpy(szMSG, "IT IS TIED");
  OBJLOC[OBJ_ROPE] = ROOM_TOP_OF_A_DEEP_WELL;
  FLAGS[53] = 1;
 }
 if (((ROOMID == ROOM_TOP_OF_A_DEEP_WELL) && (OBJID == OBJ_SHEET))) {
  strcpy(szMSG, "OK");
  FLAGS[FLAG_TIEDSHEET] = 1;
  OBJLOC[OBJ_SHEET] = ROOM_TOP_OF_A_DEEP_WELL;
 }
}

void c_FUNCT_CLIMB() {
 if (((ROOMID == ROOM_HIGHWALLED_GARDEN) && (OBJID == OBJ_VINE)) && FLAGS[38] == 1) {
  strcpy(szMSG, "ALL RIGHT");
  ROOMID = ROOM_INSCRIBED_CAVERN;
 }
 if (OBJID == OBJ_ROPE || OBJID == OBJ_SHEET) {
  strcpy(szMSG, "NOT ATTACHED TO ANYTHING!");
 }
 if (((ROOMID == ROOM_HIGH_PINNACLE) && (OBJID == OBJ_ROPE)) && OBJLOC[OBJ_ROPE] == ROOM_HIGH_PINNACLE) {
  strcpy(szMSG, "YOU ARE AT THE TOP");
 }
 if (((ROOMID == ROOM_TOP_OF_A_DEEP_WELL) && (OBJID == OBJ_ROPE)) && FLAGS[53] == 1) {
  strcpy(szMSG, "GOING DOWN");
  ROOMID = ROOM_DAMP_WELL_BOTTOM;
 }
 if (((ROOMID == ROOM_TOP_OF_A_DEEP_WELL) && (OBJID == OBJ_SHEET)) && FLAGS[FLAG_TIEDSHEET] == 1) {
  ROOMID = ROOM_DAMP_WELL_BOTTOM;
  strcpy(szMSG, "IT IS TORN");
  OBJLOC[OBJ_SHEET] = ROOM_NOWHERE;
  FLAGS[FLAG_TIEDSHEET] = 0;
 }
 if (((ROOMID == ROOM_DAMP_WELL_BOTTOM) && (OBJID == OBJ_ROPE)) && FLAGS[53] == 1) {
  OBJLOC[OBJ_ROPE] = ROOM_DAMP_WELL_BOTTOM;
  FLAGS[53] = 0;
  strcpy(szMSG, "IT FALLS DOWN - BUMP!");
 }
}

void c_FUNCT_WITH() {
 c_FUNCT_USE();
}
void c_FUNCT_USE() {
 if (((ROOMID == ROOM_EDGE_OF_AN_ICY_LAKE) && (OBJID == OBJ_SHEET))) {
  strcpy(szMSG, "OK");
  FLAGS[FLAG_SHEETONBOAT] = 1;
 }
 if (OBJID == OBJ_COINS || OBJID == OBJ_COIN || OBJID == OBJ_APPLES || OBJID == OBJ_APPLE || OBJID == OBJ_BONE || OBJID == OBJ_BREAD) {
  c_FUNCT_GIVE();
 }
 if (((ROOMID == ROOM_ROUGH_WATER) && (OBJID == OBJ_BUCKET))) {
  strcpy(szMSG, "YOU HAVE KEPT AFLOAT");
  FLAGS[FLAG_BUCKETONBOAT] = 1;
  return;
 }
 if (((ROOMID == ROOM_ROUGH_WATER) && (OBJID == OBJ_JUG))) {
  strcpy(szMSG, "IT IS NOT BIG ENOUGH!");
  return;
 }
 if (OBJID == OBJ_SWORD || OBJID == OBJ_AXE) {
  c_FUNCT_SWING();
 }
 if (OBJID == OBJ_PLANKS) {
  c_FUNCT_LEAVE();
 }
 if (OBJID == OBJ_SILVER_PLATE) {
  c_FUNCT_HOLD();
 }
 if (OBJID == OBJ_REEDS) {
  c_FUNCT_RIG();
 }
 if (OBJID == OBJ_JUG || OBJID == OBJ_BUCKET) {
  c_FUNCT_FILL();
 }
}

void c_FUNCT_OPEN() {
 if (OBJID == OBJ_CHEST || OBJID == OBJ_SACKS) {
  c_FUNCT_EXAMINE();
 }
 if (((ROOMID == ROOM_KITCHENS_OF_THE_PALACE) && (OBJID == OBJ_CUPBOARD))) {
  FLAGS[OBJ_PHIAL] = OBJ_STATUS_VISIBLE;
  strcpy(szMSG, "OK");
 }
 if (((ROOMID == ROOM_CUPBOARD_IN_A_CORNER) && (OBJID == OBJ_CUPBOARD))) {
  strcpy(szMSG, "OK");
  FLAGS[OBJ_BOOTS] = OBJ_STATUS_VISIBLE;
 }
 if (((ROOMID == ROOM_SLUICE_GATES) && (OBJID == OBJ_GATES)) || ((ROOMID == ROOM_DANK_CORRIDOR) && (OBJID == OBJ_DOOR))) {
  strcpy(szMSG, "YOU ARE NOT STRONG ENOUGH");
 }
 if (((ROOMID == ROOM_ROW_OF_CASKS) && (OBJID == OBJ_CASKS))) {
  strcpy(szMSG, "A PASSAGE!");
  strcpy(EXITS[ROOM_ROW_OF_CASKS], "EW");
 }
 if (((ROOMID == ROOM_SAFE_IN_OGBANS_CHAMBER) && (OBJID == OBJ_SAFE))) {
  int CN;
  PRINT("");
  PRINT("WHAT IS THE CODE");
  CN = INPUTNUM();
  strcpy(szMSG, "WRONG!");
  if (CN == FLAGS[41]) {
   strcpy(szMSG, "IT OPENS");
   FLAGS[OBJ_KEY] = OBJ_STATUS_VISIBLE;
  }
 }
 if (((ROOMID == ROOM_STABLE) && (OBJID == OBJ_DOOR))) {
  strcpy(szMSG, "IT FALLS OF ITS HINGES");
 }
 if (((ROOMID == ROOM_WIZARDS_LAIR) && (OBJID == OBJ_DOOR))) {
  strcpy(szMSG, "IT IS LOCKED");
 }
}

void c_FUNCT_BURN() {
 c_FUNCT_LIGHT();
}
void c_FUNCT_LIGHT() {
 if (OBJID > TOBJCOUNT) {
  strcpy(szMSG, "IT DOES NOT BURN");
 }
 if (OBJID == OBJ_MATCHES) {
  strcpy(szMSG, "YOU LIT THEM");
 }
 if (((ROOMID == ROOM_WINE_CELLAR) && (OBJID == OBJ_MATCHES))) {
  strcpy(szMSG, "NOT BRIGHT ENOUGH");
 }
 if ((OBJID == OBJ_LAMP || ((ROOMID == ROOM_STABLE) && (OBJID == OBJ_DOOR))) && OBJLOC[OBJ_MATCHES] != 0) {
  strcpy(szMSG, "NO MATCHES");
 }
 if (OBJID == OBJ_LAMP && OBJLOC[OBJ_MATCHES] == ROOM_INVENTORY) {
  sprintf(szMSG, "A BRIGHT %s", szVV);
  FLAGS[50] = 1;
 }
 if (((ROOMID == ROOM_STABLE) && (OBJID == OBJ_DOOR)) && OBJLOC[OBJ_MATCHES] == ROOM_INVENTORY) {
  FLAGS[43] = 1;
  strcpy(szMSG, "IT HAS TURNED TO ASHES");
 }
}

void c_FUNCT_FILL() {
 if ((OBJID == OBJ_JUG || OBJID == OBJ_BUCKET) && (ROOMID == ROOM_ROUGH_WATER || ROOMID == ROOM_MIDDLE_OF_THE_LAKE)) {
  strcpy(szMSG, "YOU CAPSIZED!");
  FLAGS[FLAG_YOUAREDEAD] = 1;
 }
 if (((ROOMID == ROOM_STREAM_IN_A_VALLEY_BOTTOM) && (OBJID == OBJ_JUG)) && OBJLOC[OBJ_JUG] == ROOM_INVENTORY) {
  strcpy(szMSG, "IT IS NOW FULL");
  FLAGS[34] = 1;
 }
 if (((ROOMID == ROOM_STREAM_IN_A_VALLEY_BOTTOM) && (OBJID == OBJ_BUCKET))) {
  strcpy(szMSG, "IT LEAKS OUT!");
 }
}

void c_FUNCT_PLANT() {
 if (OBJID != OBJ_SEEDS || ROOMID != ROOM_HIGHWALLED_GARDEN) {
  strcpy(szMSG, "DO NOT GROW!");
  return;
 }
 strcpy(szMSG, "OK");
 FLAGS[37] = 1;
}

void c_FUNCT_WATER() {
 if (OBJID == OBJ_SEEDS && FLAGS[37] == 1 && FLAGS[34] == 1) {
  strcpy(szMSG, "A LARGE VINE GROWS IN SECONDS!");
  FLAGS[38] = 1;
 }
}

void c_FUNCT_SWING() {
 if (OBJID == OBJ_AXE || OBJID == OBJ_SWORD) {
  strcpy(szMSG, "THWACK!");
 }
 if (((ROOMID == ROOM_COBWEBBY_ROOM) && (OBJID == OBJ_SWORD))) {
  strcpy(szMSG, "YOU CLEARED THE COBWEBS");
  FLAGS[66] = 1;
 }
 if (((ROOMID == ROOM_DANK_CORRIDOR) && (OBJID == OBJ_AXE))) {
  strcpy(szMSG, "THE DOOR BROKE!");
  strcpy(EXITS[ROOM_DANK_CORRIDOR], "NS");
  strcpy(EXITS[ROOM_DUNGEONS_OF_THE_PALACE], "NS");
 }
 if (((ROOMID == ROOM_DAMP_WELL_BOTTOM) && (OBJID == OBJ_AXE))) {
  strcpy(szMSG, "YOU BROKE THROUGH");
  strcpy(EXITS[ROOM_DAMP_WELL_BOTTOM], "N");
 }
}

void c_FUNCT_EMPTY() {
 if (OBJID == OBJ_JUG) {
  OBJID = OBJ_SEEDS;
  c_FUNCT_WATER();
 }
 if (((ROOMID == ROOM_MOSAICFLOORED_HALL) && (OBJID == OBJ_PHIAL))) {
  strcpy(szMSG, "WHERE?");
 }
}

void c_FUNCT_ENTER() {
 if (((ROOMID == ROOM_OUTSIDE_A_WINDMILL) && (OBJID == OBJ_WINDMILL))) {
  VERBID = VERB_EAST;
  c_FUNCT_GOTO();
  return;
 }
 if (ROOMID == ROOM_MOUNTAIN_HUT) {
  strcpy(szMSG, "YOU FOND SOMETHING");
  FLAGS[OBJ_PLANKS] = OBJ_STATUS_VISIBLE;
 }
}

void c_FUNCT_CROSS() {
 if (ROOMID == ROOM_EAST_END_OF_A_BRIDGE) {
  VERBID = VERB_WEST;
  c_FUNCT_GOTO();
  return;
 }
 if (ROOMID == ROOM_WEST_END_OF_A_BRIDGE) {
  VERBID = VERB_EAST;
  c_FUNCT_GOTO();
 }
}

void c_FUNCT_REMOVE() {
 if ((OBJID == OBJ_BOOTS && FLAGS[FLAG_BOOTSON] == 1)) {
  strcpy(szMSG, "TAKEN OFF");
  FLAGS[FLAG_BOOTSON] = 0;
 }
 if ((OBJID == OBJ_UNIFORM && FLAGS[51] == 1)) {
  strcpy(szMSG, "OK");
  FLAGS[51] = 0;
 }
 if (OBJID == OBJ_BRICKS || OBJID == OBJ_RUBBLE) {
  c_FUNCT_MOVE();
 }
}

void c_FUNCT_FEED() {
 if (((ROOMID == ROOM_WINE_CELLAR) && (OBJID == OBJ_RATS)) || ((ROOMID == ROOM_RUSTY_GATES) && (OBJID == OBJ_PONY)) || ((ROOMID == ROOM_OVERGROWN_TRACK) && (OBJID == OBJ_PONY)) || ((ROOMID == ROOM_BARREN_COUNTRYSIDE) && (OBJID == OBJ_OGBANS_BOAR)) || ((ROOMID == ROOM_HIGH_GLASS_GATES) && (OBJID == OBJ_HOUND)))
  strcpy(szMSG, "WITH WHAT?");
}

void c_FUNCT_TURN() {
 if (((ROOMID == ROOM_DISUSED_WATERWHEEL) && (OBJID == OBJ_WHEEL)))
  strcpy(szMSG, "IT GOES ROUND");
 if (((ROOMID == ROOM_SLUICE_GATES) && (OBJID == OBJ_HANDLE))) {
  strcpy(szMSG, "THE GATES OPEN, THE POOL EMPTIES");
  FLAGS[FLAG_EMPTYPOOL] = 1;
 }
}

void c_FUNCT_DIVE() {
 if (ROOMID == ROOM_MISTY_POOL || ROOMID == ROOM_MIDDLE_OF_THE_LAKE) {
  strcpy(szMSG, "YOU HAVE DROWNED");
  FLAGS[FLAG_YOUAREDEAD] = 1;
 }
}

void c_FUNCT_BAIL() {
 strcpy(szMSG, "HOW?");
}

void c_FUNCT_DROP() {
 c_FUNCT_LEAVE();
}
void c_FUNCT_LEAVE() {
 if (OBJID == 0 || OBJID > TOBJCOUNT)
  return;
 OBJLOC[OBJID] = ROOMID;
 strcpy(szMSG, "DONE");
 if (((ROOMID == ROOM_ROUGH_WATER) && (OBJID == OBJ_BOAT)) || ((ROOMID == ROOM_MIDDLE_OF_THE_LAKE) && (OBJID == OBJ_BOAT))) {
  strcpy(szMSG, "YOU DROWNED!");
  FLAGS[FLAG_YOUAREDEAD] = 1;
 }
 if (OBJID == OBJ_BOAT && FLAGS[FLAG_SHEETONBOAT] == 1)
  OBJLOC[OBJ_SHEET] = ROOMID;
 if (OBJID == OBJ_JUG && FLAGS[34] == 1) {
  strcpy(szMSG, "YOU LOST THE WATER!");
  FLAGS[34] = 0;
 }
 if (OBJID == OBJ_SHEET && FLAGS[FLAG_SHEETONBOAT] == 1)
  FLAGS[FLAG_SHEETONBOAT] = 0;
}

void c_FUNCT_INSERT() {
 if (OBJID == OBJ_COIN && FLAGS[FLAG_COINSCOUNT] == 0)
  strcpy(szMSG, "YOU DO NOT HAVE ANY");
 if (((ROOMID == ROOM_TURRET_ROOM_WITH_A_SLOT_MACHINE) && (OBJID == OBJ_COIN)) && OBJLOC[OBJ_COINS] == ROOM_INVENTORY && FLAGS[FLAG_COINSCOUNT] > 0) {
  FLAGS[FLAG_COINSCOUNT] = FLAGS[FLAG_COINSCOUNT] - 1;
  sprintf(szMSG, "A NUMBER APPEARS - %d", FLAGS[41]);
  if (FLAGS[FLAG_COINSCOUNT] == 0)
   OBJLOC[OBJ_COINS] = ROOM_NOWHERE;
 }
}

void c_FUNCT_THROW() {
 if (OBJID == 0 || OBJID > TOBJCOUNT)
  return;
 strcpy(szMSG, "DID NOT GO FAR!");
 OBJLOC[OBJID] = ROOMID;
 if (((ROOMID == ROOM_BARREN_COUNTRYSIDE) && (OBJID == OBJ_NET))) {
  strcpy(szMSG, "YOU CAUGHT THE BOAR");
  FLAGS[FLAG_BOARCAPTURED] = 1;
 }
}

void c_FUNCT_RIG() {
 c_FUNCT_MAKE();
}
void c_FUNCT_BLOW() {
 c_FUNCT_MAKE();
}
void c_FUNCT_MAKE() {
 if (OBJID == OBJ_REEDS)
  strcpy(szMSG, "A NICE TUNE");
 if (((ROOMID == ROOM_EDGE_OF_AN_ICY_LAKE) && (OBJID == OBJ_SAIL)))
  strcpy(szMSG, "WHAT WITH?");
 if (OBJID == OBJ_MUSIC)
  strcpy(szMSG, "HOW, O MUSICAL ONE?");
 if (((ROOMID == ROOM_HUGE_FALLEN_OAK) && (OBJID == OBJ_REEDS))) {
  FLAGS[35] = 1;
  strcpy(szMSG, "THE GHOST OF THE GOBLIN GUARDIAN IS FREE");
  strcpy(EXITS[ROOM_HUGE_FALLEN_OAK], "NS");
 }
}

void c_FUNCT_EAT() {
 if (OBJID == 0 || OBJID > TOBJCOUNT)
  return;
 if (OBJID == OBJ_APPLES || OBJID == OBJ_BREAD) {
  strcpy(szMSG, "YUM YUM!");
  OBJLOC[OBJID] = ROOM_NOWHERE;
 }
}

void c_FUNCT_MOVE() {
 if (ROOMID == ROOM_STALACTITES_AND_STALAGMITES && OBJID == OBJ_RUBBLE) {
  FLAGS[45] = 1;
  strcpy(szMSG, "YOU REVEALED A STEEP PASSAGE");
 }
 if (ROOMID == ROOM_HOLLOW_TOMB && OBJID == OBJ_RUBBLE)
  strcpy(szMSG, "YOU CANNOT MOVE RUBBLE FROM HERE");
 if (((ROOMID == ROOM_DAMP_WELL_BOTTOM) && (OBJID == OBJ_BRICKS)))
  strcpy(szMSG, "THEY ARE WEDGED IN!");
}

void c_FUNCT_POISON() {
 c_FUNCT_INTO();
}
void c_FUNCT_INTO() {
 if ((OBJID == OBJ_GOBLET || OBJID == OBJ_WINE) && OBJLOC[OBJ_PHIAL] == ROOM_INVENTORY && ROOMID == ROOM_MOSAICFLOORED_HALL) {
  strcpy(szMSG, "OK");
  FLAGS[47] = 1;
 }
}

void c_FUNCT_RING() {
 int MR;
 if (ROOMID != ROOM_SILVER_BELL_IN_THE_ROCK || OBJID != OBJ_BELL)
  return;
 while (1) {
  PRINT("");
  PRINT("HOW MANY TIMES?");
  MR = INPUTNUM();
  if (MR == 0)
   PRINT("A NUMBER");
  else
   break;
 }
 if (MR == FLAGS[42]) {
  strcpy(szMSG, "A ROCK DOOR OPENS");
  strcpy(EXITS[ROOM_SILVER_BELL_IN_THE_ROCK], "EW");
  return;
 }
 strcpy(szMSG, "YOU HAVE MISTREATED THE BELL!");
 FLAGS[FLAG_YOUAREDEAD] = 1;
}
void c_FUNCT_CUT() {
 if ((((ROOMID == ROOM_COBWEBBY_ROOM) && (OBJID == OBJ_COBWEBS))) || ((ROOMID == ROOM_COBWEBBY_ROOM) && (OBJID == OBJ_SWORD)))
  c_FUNCT_SWING();
}

void c_FUNCT_SHOW() {
 c_FUNCT_HOLD();
}
void c_FUNCT_HOLD() {
 if ((((ROOMID == ROOM_WIZARDS_LAIR) && (OBJID == OBJ_UP_SILVER_PLATE)) || ((ROOMID == ROOM_WIZARDS_LAIR) && (OBJID == OBJ_SILVER_PLATE))) && OBJLOC[OBJ_SILVER_PLATE] == ROOM_INVENTORY) {
  strcpy(szMSG, "YOU REFLECTED THE WIZARD'S GLARE! HE IS DEAD");
  FLAGS[63] = 1;
 }
 if (OBJID == OBJ_STONE_OF_DESTINY) 
  c_FUNCT_GET(); 
}

void c_FUNCT_PAY() {
 if (((ROOMID == ROOM_WEST_END_OF_A_BRIDGE) && (OBJID == OBJ_TROLL)) || ((ROOMID == ROOM_EAST_END_OF_A_BRIDGE) && (OBJID == OBJ_TROLL))) {
  strcpy(szMSG, "WHAT WITH?");
 }
 if (OBJID == OBJ_COINS || OBJID == OBJ_COIN) 
  c_FUNCT_GIVE(); 
}

void c_FUNCT_UNLOCK() {
 if (((ROOMID == ROOM_WIZARDS_LAIR) && (OBJID == OBJ_DOOR)) && OBJLOC[OBJ_KEY] == ROOM_INVENTORY) {
  strcpy(szMSG, "THE KEY TURNS!");
  FLAGS[70] = 1;
 }
}

void c_FUNCT_BREAK() {
 if (((ROOMID == ROOM_DANK_CORRIDOR) && (OBJID == OBJ_DOOR))) 
  strcpy(szMSG, "HOW?"); 
}

void c_FUNCT_REFLECT() {
 if (ROOMID == ROOM_WIZARDS_LAIR) 
  strcpy(szMSG, "HOW?"); 
}

void c_FUNCT_DRINK() {
 strcpy(szMSG, "ARE YOU THIRSTY?");
}

void c_FUNCT_INTOMAZE() {
 char JJ[16];
 int NG = 0;
 strcpy(JJ, "SSSSSSSS");
 while (1) {
  char WW;
  int MP = DIRID / 2;
  draw_SCREEN();
  PRINT("YOU ARE LOST IN THE TUNNELS");
  PRINT("WHICH WAY? (N,S,E,W)");
  if (NG > 15)
   PRINT("(OR G TO GIVE UP!)");
  PRINT("");
  WW = INPUTCH();
  memmove(JJ + 1, JJ, 9);
  JJ[8] = WW;
  if (WW == 'G') {
   FLAGS[FLAG_YOUAREDEAD] = 1;
   return;
  }
  if (strcmp(JJ, MAZEPATH[MP]) == 0) {
   NG = NG + 1;
   continue;
  }
  else
   break;
 }
}

// -------------------------------------------------------
// main()
// -------------------------------------------------------

int main(int argc, const char * argv[]) {
 game_START();
 while (1) {
  int ret = 0;
  game_SHOWSTATUS();
  ret=game_GETCOMMAND();
  if (ret == 0)
   continue;
  else
   if (ret == 1)
   {
    game_WIN();
    break;
   }
   else
    game_FAILED();
 } 
 return 1;
}

// -------------------------------------------------------