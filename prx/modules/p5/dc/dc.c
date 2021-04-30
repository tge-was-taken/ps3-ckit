#ifdef GAME_P5
// PS3 system includes
#include <sys/prx.h>
#include <sys/tty.h>
#include <sys/syscall.h>
// Pre-prepared libraries exist in lib
// Common includes things like printf for printing, strlen, etc.
// PRX dont have access to the usual C libraries, so any functionality that you need from it
// will have to be reimplemented in there.
#include "lib/common.h"

// SHK (Static Hook library)
#include "lib/shk.h"

// Include this to use config variables
#include "lib/config.h"

#include "modules/p5/p5.h"
#include "dc.h"

// You need to declare hooks with SHK_HOOK before you can use them.
SHK_HOOK( void, setBlackMaskCueID );
SHK_HOOK( void*, BlackMaskBossVoice, structA* a1 );
SHK_HOOK( void*, LoadPlayerCombatVoicePack, structA* a1 );
SHK_HOOK( void*, LoadPartyPanelSPD, char* a1 );
SHK_HOOK( void*, LoadPartyPanelPLG, char* a1 , u32 a2, u32 a3, char a4);
SHK_HOOK( void*, LoadBCDFunction, char* a1 , u32 a2, u32 a3, int* a4);
SHK_HOOK( void, Load2DUIDDS, u32* a1 , char* a2);
SHK_HOOK( void*, LoadBEDFile, char* a1 , char a2);
SHK_HOOK( void*, LoadCombatCutin, char* a1 , char a2);
SHK_HOOK( int, LoadAnimationPack, u64 param_1, int animationID, char* result, int animationType );
SHK_HOOK( void, CombatPersonaCueID, CueIDThingy* param_1, int param_2, short param_3, char param_4, char param_5);

void* BlackMaskBossVoiceHook( structA* a1 )
{
  idkman* someAddressPointer;
  u64 uVar1;
  undefined8 in_r7;
  undefined8 in_r8;
  u32 uVar2;
  idkman* ppuVar3;
  char acStack2080 [128];
  char acStack1056 [128];

  someAddressPointer = MallocAndReturn(0x20);
  if (someAddressPointer != (void*)0x0) {
  SomethingAboutLoadingVoices(someAddressPointer);
  someAddressPointer->ptr1 = 0x00ba90e4;
  ppuVar3 = someAddressPointer;
  }
  CalculateAddressWithPointer(&ppuVar3->ptr2,a1);
  uVar1 = GetBtlUnitID(a1->field0C->btlUnitPointer);
  uVar2 = uVar1;
  uVar1 = GetSavedataBitflagAlt(0x218f);
  if (uVar1 == 0) {
  sprintf(acStack2080,"sound/battle/be_boss_%04d.acb",uVar2);
  sprintf(acStack1056,"sound/battle/be_boss_%04d.awb",uVar2);
  }
  else {
  sprintf(acStack2080,"sound_JP/battle/be_boss_%04d.acb",uVar2);
  sprintf(acStack1056,"sound_JP/battle/be_boss_%04d.awb",uVar2);
  }
  FUN_0074ae50(ppuVar3,acStack2080,acStack1056,uVar2 | 0x10000,in_r7,in_r8);
  return ppuVar3;
}

void* LoadPlayerCombatVoicePackHook( structA* a1 )
{
  idkman* someAddressPointer;
  u64 uVar1;
  undefined8 in_r7;
  undefined8 in_r8;
  u32 playerID;
  idkman* ppuVar3;
  char acStack2080 [128];
  char acStack1056 [128];

  someAddressPointer = MallocAndReturn(0x20);
  if (someAddressPointer != (void*)0x0) {
  SomethingAboutLoadingVoices(someAddressPointer);
  someAddressPointer->ptr1 = 0xba7d30;
  ppuVar3 = someAddressPointer;
  }
  CalculateAddressWithPointer(&ppuVar3->ptr2,a1);
  uVar1 = GetBtlUnitID(a1->field0C->btlUnitPointer);
  playerID = uVar1;
  uVar1 = GetSavedataBitflagAlt(0x218f);
  if ( playerID == 9 && GetEquippedPersonaFunction(9) != Persona_RobinHood )
  {
    playerID = 69;
  }
  if (uVar1 == 0) 
  {
    sprintf(acStack2080,"sound/battle/bp%02d.acb",playerID);
    sprintf(acStack1056,"sound/battle/bp%02d.awb",playerID);
  }  
  else 
  {
    sprintf(acStack2080,"sound_JP/battle/bp%02d.acb",playerID);
    sprintf(acStack1056,"sound_JP/battle/bp%02d.awb",playerID);
  }
  FUN_0074ae50(ppuVar3,acStack2080,acStack1056,playerID | 0x10000,in_r7,in_r8);
  return ppuVar3;
}

void* LoadPartyPanelSPDHook(char* a1)
{
  if ( strcmp( a1, "battle/gui/p5_battle_partypanel.spd" ) == 0  && GetEquippedPersonaFunction(9) != Persona_RobinHood )
  {
      a1 = "battle/gui/p5r_battle_partypanel.spd";
  }
  return SHK_CALL_HOOK( LoadPartyPanelSPD, a1 );
}

void* LoadBEDFileHook(char* a1, char a2)
{
  if ( strcmp( a1, "battle/effect/bes_gun9.BED" ) == 0  && GetEquippedPersonaFunction(9) != Persona_RobinHood )
  {
    a1 = "battle/effect/bes_gun69.BED";
  }
  else if ( strcmp( a1, "battle/skill/0416.BED" ) == 0  && GetEquippedPersonaFunction(9) != Persona_RobinHood )
  {
    a1 = "battle/skill/0416b.BED";
  }
  return SHK_CALL_HOOK( LoadBEDFile, a1, a2 );
}

void* LoadCombatCutinHook(char* a1 , char a2)
{
  // Combat Cutin
  if ( strcmp( a1, "battle/cutin/bct_p_bc0009.dds" ) == 0  && GetEquippedPersonaFunction(9) != Persona_RobinHood )
  {
      a1 = "battle/cutin/bct_p_bc0069.dds";
  }
  // AoA Start/Jump image
  if ( strcmp( a1, "battle/gui/bksk_p_bc0009.dds" ) == 0  && GetEquippedPersonaFunction(9) != Persona_RobinHood )
  {
      a1 = "battle/gui/bksk_p_bc0069.dds";
  }
  return SHK_CALL_HOOK( LoadCombatCutin, a1, a2 );
}

void CombatPersonaCueIDHook( CueIDThingy* param_1, int param_2, short param_3, char param_4, char param_5 )
{
  u32 uVar1;
  u64 uVar2;
  u64 uVar3;
  u16* puVar5;
  sample_int_struct* puVar4;
  
  uVar1 = (int)param_3 & 0xffff;
  uVar2 = GetBtlUnitID(param_1->Field10->btlUnitPointer);
  u32 unitID = uVar2; // for debugging purposes
  uVar2 = GetEquippedPersonaFunction(uVar2);
  u16 personaID = uVar2;
  printf("CombatPersonaCueIDHook called, character -> %d, persona -> %d, skill -> %d\n", unitID, personaID, param_3);
  if ( personaID == 200 || (personaID & 0x1000) != 0 )
  {
    uVar3 = 0;
  }
  else uVar3 = 1;

  if (((int)uVar3 == 0) || (param_4 != '\0')) 
  {
    uVar3 = FUN_002584cc(uVar1,1);
    if (((int)uVar3 == 0) && (uVar3 = FUN_0025867c(uVar1), (int)uVar3 == 0)) 
    {
      LoadSoundByCueIDCombatVoice(param_1,param_2,0x65,'\0');
    }
    else 
    {
      if ( personaID >= 201 && personaID <= 210 ) // tier 1 personas
      {
        LoadSoundByCueIDCombatVoice(param_1,param_2,0x4f,'\0');
      }
      else if ( personaID >= 211 && personaID <= 220 || personaID == 240 ) // tier 2, 240 -> Vanadis 
      {
        LoadSoundByCueIDCombatVoice(param_1,param_2,0x50,'\0');
      }
      else if ( personaID >= 241 && personaID <= 250) // tier 3 personas
      {
        LoadSoundByCueIDCombatVoice(param_1,param_2,0x4D,'\0');
      }
      else
      {
        LoadSoundByCueIDCombatVoice(param_1,param_2,0x20,'\0'); // no valid Persona found, use generic attack line
        printf("Failed to find valid Party Member persona ID. Result %d\n", personaID);
      }
    }
  }
  else 
  {
    uVar3 = FUN_002584cc(uVar1,1);
    if (((int)uVar3 == 0) && (uVar3 = FUN_0025867c(uVar1), (int)uVar3 == 0)) 
    {
      if ( param_3 == 360 || param_3 == 361 ) // Charge and Concentrate
      {
        LoadSoundByCueIDCombatVoice(param_1,param_2,78,'\0');
      }
      else LoadSoundByCueIDCombatVoice(param_1,param_2,0x65,'\0');
    }
    else 
    {
      uVar3 = 0x20;
      if (param_5 != '\0') 
      {
        uVar3 = 0x68;
      }
      LoadSoundByCueIDCombatVoice(param_1,param_2,uVar3,'\0');
    }
  }
  return;
}

void Load2DUIDDSHook(u32* a1, char* a2)
{
  if ( strcmp( a2, "camp/wanted/wanted_09.dds") == 0 && GetEquippedPersonaFunction(9) != Persona_RobinHood )
  {
    a2 = "camp/wanted/wanted_69.dds";
  }
  else if ( strcmp( a2, "camp/charaTex/c_chara_09.dds") == 0 && GetEquippedPersonaFunction(9) != Persona_RobinHood )
  {
    a2 = "camp/charaTex/c_chara_09b.dds";
  }
  SHK_CALL_HOOK( Load2DUIDDS, a1, a2 );
}

void* LoadBCDFunctionHook( char* a1 , u32 a2, u32 a3, int* a4 )
{
  if ( strcmp( a1, "battle/event/BCD/goodbye/bksk_aketi.BCD" ) == 0 && GetEquippedPersonaFunction(9) != Persona_RobinHood )
  {
    a1 = "battle/event/BCD/goodbye/bksk_aketi_b.BCD";
  }
  else if ( strcmp( a1, "battle/event/BCD/0316/000/bes_0316_000.BCD" ) == 0 )
  {
    if ( EncounterIDGlobal == 831 || EncounterIDGlobal == 832 || EncounterIDGlobal == 833 )
    {
      a1 = "battle/event/BCD/03c9/100/bes_03c9_100.BCD";
    }
    else a1 = "battle/event/BCD/0316/000/bes_0316_000.BCD";
  }
  return SHK_CALL_HOOK( LoadBCDFunction, a1, a2, a3, a4 );
}

void* LoadPartyPanelPLGHook(char* a1, u32 a2, u32 a3, char a4)
{
  if ( strcmp( a1, "battle/gui/battle_active_pp.plg" ) == 0 && GetEquippedPersonaFunction(9) != Persona_RobinHood )
  {
      a1 = "battle/gui/battle_active_p5.plg";
  }
  return SHK_CALL_HOOK( LoadPartyPanelPLG, a1, a2, a3, a4 );
}

void setBlackMaskCueIDHook( CueIDThingy* param_1, u32 param_2, u16 skill_ID )
{
  u16 uVar1;
  u64 uVar2;
  u32 Custom;

  Custom = ActualGetCount(420);
  if (Custom > 0)
  {
    LoadSoundByCueIDCombatVoice(param_1,param_2,Custom,'\0');
    return;
  }
  
  if (skill_ID < 0x48) {
    if (skill_ID < 0x18) {
      if (skill_ID < 0xe) {
        if (skill_ID < 10) {
          return;
        }
      }
      else {
        if (0x13 < skill_ID) 
        {
            LoadSoundByCueIDCombatVoice(param_1,param_2,2,'\0');
            return;
        }
        if (0xf < skill_ID) {
          return;
        }
      }
      LoadSoundByCueIDCombatVoice(param_1,param_2,3,'\0');
      return;
    }
    if (skill_ID < 0x40) {
      if (0x3b < skill_ID) {
        LoadSoundByCueIDCombatVoice(param_1,param_2,7,'\0');
        return;
      }
      if (0x19 < skill_ID) {
        return;
      }
    LoadSoundByCueIDCombatVoice(param_1,param_2,2,'\0');
      return;
    }
    if (skill_ID < 0x43) {
      if (skill_ID < 0x42) {
        return;
      }
      LoadSoundByCueIDCombatVoice(param_1,param_2,7,'\0');
      return;
    }
    if (skill_ID < 0x46) {
      return;
    }
  }
  else {
    if (0x10f < skill_ID) {
      if (skill_ID == 0x2a2) {
        LoadSoundByCueIDCombatVoice(param_1,param_2,10,'\0');
        return;
      }
      if (skill_ID == 0x2a1) {
        LoadSoundByCueIDCombatVoice(param_1,param_2,0xb,'\0');
        return;
      }
      if (skill_ID == 0x173) {
        uVar2 = 0xb;
        uVar1 = param_1->Field1C;
        param_1->Field1C = uVar1 + 1;
        if ((uVar1 & 1) != 0) {
          uVar2 = 10;
        }
        LoadSoundByCueIDCombatVoice(param_1,param_2,uVar2,'\0');
        return;
      }
      if (skill_ID != 0x172) {
        if (skill_ID == 0x15c) {
          LoadSoundByCueIDCombatVoice(param_1,param_2,8,'\0');
          return;
        }
        if (skill_ID != 0x110) {
          return;
        }
        LoadSoundByCueIDCombatVoice(param_1,param_2,6,'\0');
        return;
      }
      uVar2 = 0xb;
      uVar1 = param_1->Field1C;
      param_1->Field1C = uVar1 + 1;
      if ((uVar1 & 1) != 0) {
        uVar2 = 10;
      }
      LoadSoundByCueIDCombatVoice(param_1,param_2,uVar2,'\0');
      return;
    }
    if (skill_ID == 0x106) {
      LoadSoundByCueIDCombatVoice(param_1,param_2,6,'\0');
      return;
    }
    if (skill_ID == 0xf3) {
      LoadSoundByCueIDCombatVoice(param_1,param_2,5,'\0');
      return;
    }
    if (skill_ID == 0xd4) {
      LoadSoundByCueIDCombatVoice(param_1,param_2,4,'\0');
      return;
    }
    if (skill_ID == 0xca) {
      LoadSoundByCueIDCombatVoice(param_1,param_2,4,'\0');
      return;
    }
    if (skill_ID != 0x48) {
      return;
    }
  }
  LoadSoundByCueIDCombatVoice(param_1,param_2,9,'\0');
  return;
}

int LoadAnimationPackHook( u64 param_1, int animationID, char* result, int animationType )
{
  u32 animType = (u32)(param_1 >> 0x3a);
  if ( animType == 2 )
  {
      u32 unitID = (u32)(param_1 >> 0x14) & 0xffff;
      if( unitID == 6 && GetEquippedPersonaFunction(6) != Persona_Anat )
      {
          animationID = 52;
      }
      else if( unitID == 9 && GetEquippedPersonaFunction(9) != Persona_RobinHood )
      {
          animationID = 52;
      }
  }
  return SHK_CALL_HOOK( LoadAnimationPack, param_1, animationID, result, animationType);
}

// The start function of the PRX. This gets executed when the loader loads the PRX at boot.
// This means game data is not initialized yet! If you want to modify anything that is initialized after boot,
// hook a function that is called after initialisation.
void dcInit( void )
{
  // Hooks must be 'bound' to a handler like this in the start function.
  // If you don't do this, the game will crash.
  SHK_BIND_HOOK( setBlackMaskCueID, setBlackMaskCueIDHook );
  SHK_BIND_HOOK( BlackMaskBossVoice, BlackMaskBossVoiceHook );
  SHK_BIND_HOOK( LoadPlayerCombatVoicePack, LoadPlayerCombatVoicePackHook );
  SHK_BIND_HOOK( LoadPartyPanelSPD, LoadPartyPanelSPDHook );
  SHK_BIND_HOOK( LoadPartyPanelPLG, LoadPartyPanelPLGHook );
  SHK_BIND_HOOK( Load2DUIDDS, Load2DUIDDSHook );
  SHK_BIND_HOOK( LoadBEDFile, LoadBEDFileHook );
  SHK_BIND_HOOK( LoadCombatCutin, LoadCombatCutinHook );
  SHK_BIND_HOOK( LoadAnimationPack, LoadAnimationPackHook );
  SHK_BIND_HOOK( LoadBCDFunction, LoadBCDFunctionHook );
  SHK_BIND_HOOK( CombatPersonaCueID, CombatPersonaCueIDHook );
}

void dcShutdown( void )
{
  // Executed when the PRX module is unloaded.    
}
#endif