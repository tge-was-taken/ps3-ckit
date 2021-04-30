#ifdef GAME_P5
#ifndef P5E_H
#define P5E_H

// PS3 system includes
#include "lib/common.h"
#include "lib/shk.h"

bool isAmbush;

void p5eInit( void );
void p5eShutdown( void );

typedef struct
{
  u32 modelID;
  u32 bgmId;
} btlEquipBgmTableEntry;

btlEquipBgmTableEntry btlEquipBgmTable[20];

typedef struct
{
  u32 modelId[5];
} CharModelReplacementTable;

CharModelReplacementTable charModelReplacementTable[10];

#endif
#endif