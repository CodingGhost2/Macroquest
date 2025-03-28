|- RGwizutil.inc
|- Version 2.0
|- Updated: 2/22/2020
|- Thanks to Saar for additions and bug fixes
|- Updated by No_one for the new casting System

|- Supported wizard modes
#define MODEFIRE 0
#define MODEICE 1
#define MODETLP 2
#define MODEMAGIC 4
#define MODENOONE 3
#define WIZWEAVECHECK "( !${Window[CastingWindow].Open} && !${Me.GemTimer[1]} && !${Me.GemTimer[3]} && !${Me.GemTimer[5]} && !${Me.GemTimer[7]} && !${Me.GemTimer[10]} )"
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub WIZ_Setup
|-List containing BST specific settings settings
    /declare RGList_WIZ         list outer
    
    
    |-Alliance Specific
    |-AllianceAvail is set to true if there are enough members in the group to use Alliance
    /declare AllianceAvail          int    outer 0
    /declare AllianceBuff		    string outer NULL
    /declare AllianceBuff_SpellSet  set    outer NULL   
    /declare ClarityPotion          string outer Distillate of Clarity

    |- Rotations
	/call Ordered_Rotation_New WIZ_DPS_MODEFIRE_Rotation
	/call Ordered_Rotation_New WIZ_Downtime_MODEFIRE_Rotation
    /call Ordered_Rotation_New WIZ_Burn_MODEFIRE_Rotation

    |- Rotations
	/call Ordered_Rotation_New WIZ_DPS_MODEICE_Rotation
	/call Ordered_Rotation_New WIZ_Downtime_MODEICE_Rotation
    /call Ordered_Rotation_New WIZ_Burn_MODEICE_Rotation

    |- Rotations TLP Rotation
	/call Ordered_Rotation_New WIZ_DPS_MODETLP_Rotation
	/call Ordered_Rotation_New WIZ_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New WIZ_Burn_MODETLP_Rotation
    /call Ordered_Rotation_New WIZ_BURN_MODETLP_Rotation
    
    |- Rotations
	/call Ordered_Rotation_New WIZ_DPS_MODEMAGIC_Rotation
	/call Ordered_Rotation_New WIZ_Downtime_MODEMAGIC_Rotation
    /call Ordered_Rotation_New WIZ_Burn_MODEMAGIC_Rotation

    |- Rotations
	/call Ordered_Rotation_New WIZ_DPS_MODENOONE_Rotation
	/call Ordered_Rotation_New WIZ_Downtime_MODENOONE_Rotation
    /call Ordered_Rotation_New WIZ_Burn_MODENOONE_Rotation

|- Items
    /call ItemSet_New Epic  

|- Spells
    /call AbilitySet_New  AllianceSpell
    /call AbilitySet_New  DichoSpell
    /call AbilitySet_New  IceClaw
    /call AbilitySet_New  FireClaw
    /call AbilitySet_New  MagicClaw
    /call AbilitySet_New  CloudburstNuke
    /call AbilitySet_New  FuseNuke
    /call AbilitySet_New  FireEtherealNuke
    /call AbilitySet_New  IceEtherealNuke
    /call AbilitySet_New  MagicEtherealNuke
    /call AbilitySet_New  FireRainLureNuke
    /call AbilitySet_New  ChaosNuke
    /call AbilitySet_New  VortexNuke
    /call AbilitySet_New  WildNuke
    /call AbilitySet_New  FireNuke
    /call AbilitySet_New  IceNuke
    /call AbilitySet_New  MagicNuke
    /call AbilitySet_New  StunSpell
    /call AbilitySet_New  SelfHPBuff
    /call AbilitySet_New  FamiliarBuff
    /call AbilitySet_New  SelfRune1
    /call AbilitySet_New  StripBuffSpell
    /call AbilitySet_New  TwincastSpell
    /call AbilitySet_New  GambitSpell
    /call AbilitySet_New  PetSpell
    /call AbilitySet_New  RootSpell
    /call AbilitySet_New  SnareSpell
    /call AbilitySet_New  EvacSpell 
    /call AbilitySet_New  HarvestSpell
    /call AbilitySet_New  JoltSpell
    |- Lure Spells
    /call AbilitySet_New IceLureNuke
    /call AbilitySet_New FireLureNuke
    /call AbilitySet_New MagicLureNuke
    | - Fast Nukes 
    /call AbilitySet_New FastIceNuke
    /call AbilitySet_New FastFireNuke
    /call AbilitySet_New FastMagicNuke
    | - 
    /call AbilitySet_New IceRainNuke
    /call AbilitySet_New FireRainNuke
    /call AbilitySet_New FireRainLureNuke
    | - Large 8 Second Cast Nukes
    /call AbilitySet_New BigIceNuke
    /call AbilitySet_New BigFireNuke
    /call AbilitySet_New BigMagicNuke

    
    
|- Misc Variables
	/declare Spell1					string outer NULL
	/declare Spell2					string outer NULL
	/declare Spell3					string outer NULL
	/declare Spell4					string outer NULL
	/declare Spell5					string outer NULL
	/declare Spell6					string outer NULL
	/declare Spell7					string outer NULL
	/declare Spell8					string outer NULL
	/declare Spell9					string outer NULL
	/declare Spell10				string outer NULL
	/declare Spell11				string outer NULL
	/declare Spell12				string outer NULL
	/declare Spell13				string outer NULL    
    
|-Config Options    
    /call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = Fire; Set 1 = Ice; Set 2 = Magic;
    /call RGLoadSetting WIZ DoManaBurn 1 Combat "Toggle 0/1 the use of Mana Burn AA"
    /call RGLoadSetting WIZ WeaveAANukes 1 Combat "Toggle 0/1 for weaving aa nukes"
    /call RGLoadSetting WIZ NukeUntilMana 1 "%Mana to nuke until for basic low level nukes. (Default: 1%)"
    /call RGLoadSetting WIZ EmergencyEvac 0 Options "Toggle 0/1 for using emergency evac [UNIMPLEMENTED]"
    /call RGLoadSetting WIZ HarvestManaPct 75 Options "0-100 percentage of mana to harvest"
    /call RGLoadSetting WIZ JoltAtAggro 65 Options "0-100 aggro percent to use Jolt Spell"
    /call RGLoadSetting WIZ DoSnare 0 Debuff "Toggle 0/1 to use wizard snares. Will use roots at lower levels. Starts at 25%HP."
    /call RGLoadSetting WIZ DoMagicNuke 1 Combat "Toggle 0/1 to Turn Of Selected Spells"
    /call RGLoadSetting WIZ DoFireNuke 1 Combat "Toggle 0/1 to Turn Of Selected Spells"
    /call RGLoadSetting WIZ DoIceNuke 1 Combat "Toggle 0/1 to Turn Of Selected Spells"
    /call RGLoadSetting WIZ Manatonuke 30 Combat "% Mana to stop nuking at - Saves mana for BigPulls & names"
    /call RGLoadSetting WIZ DoLure 1 Combat "Toggle 1/0 To turn on or Off Lure nukes"
    /call RGLoadSetting WIZ StopNukeAt 50 Combat "Set to % life to stop using Large Long cast Time Nukes to avoid wasted mana."
    /call RGLoadSetting WIZ DoRain 1 Combat "0/1 Turn rains on or Off"

    
|-Declare spell variables   
    /declare PetAssistTimer         timer   outer   0
    /declare AANukeRecasttimer      timer outer 0
    /declare spellmisc              int outer 8
    /declare spellgem               int outer 1 
    /declare miscspellremem         string outer NULL
    /declare spellrememtimer        timer outer 0
	/declare MedState				int outer 0
    /varset spellmisc ${Me.NumGems}
    /if (${Me.AltAbility[25].Name.Find[disabled]} && ${RG_AAReady[25]}) {
        /alt act 25
        /delay 5
    }
/return

|* ------------------------------------------------------------------------------------------
| SUB: SetupSkills
|------------------------------------------------------------------------------------------ *|
Sub WIZ_SetupSkills
    /echo Choosing All of the best Wizard Spells - This Will take a moment!
	|- Items
	|- Epic
	/call ItemSet_Add "Staff of Phenomenal Power" Epic
	/call ItemSet_Add "Staff of Prismatic Power" Epic
	/call ItemSet_ChooseOuter Epic Epic
|-Ice Lure level 52-111
    /call AbilitySet_Add "Lure of Frost"        IceLureNuke
    /call AbilitySet_Add "Lure of Ice"          IceLureNuke
    /call AbilitySet_Add "Icebane"              IceLureNuke
    /call AbilitySet_Add "Rimelure"             IceLureNuke
    /call AbilitySet_Add "Voidfrost Lure"       IceLureNuke
    /call AbilitySet_Add "Glacial Lure"         IceLureNuke
    /call AbilitySet_Add "Frigid Lure"          IceLureNuke
    /call AbilitySet_Add "Lure of Isaz"         IceLureNuke
    /call AbilitySet_Add "Lure of the Wastes"   IceLureNuke
    /call AbilitySet_Add "Lure of the Depths"   IceLureNuke
    /call AbilitySet_Add "Lure of Travenro"     IceLureNuke
    /call AbilitySet_Add "Lure of Restless Ice" IceLureNuke
    /call AbilitySet_Add "Lure of the Cold Moon" IceLureNuke
    /call AbilitySet_Add "Lure of Winter Memories" IceLureNuke
    /call AbilitySet_ChooseOuter IceLureNuke IceLureNuke

|- Fire Lure (Single Target) level  44-113
    /call AbilitySet_Add "Enticement of Flame"  FireLureNuke
    /call AbilitySet_Add "Lure of Flame"        FireLureNuke 
    /call AbilitySet_Add "Lure of Ro"           FireLureNuke
    /call AbilitySet_Add "Firebane"             FireLureNuke
    /call AbilitySet_Add "Lavalure"             FireLureNuke 
    /call AbilitySet_Add "Pyrolure"             FireLureNuke
    /call AbilitySet_Add "Flarelure"            FireLureNuke
    /call AbilitySet_Add "Flamelure"            FireLureNuke 
    /call AbilitySet_Add "Blazelure"            FireLureNuke
    /call AbilitySet_Add "MagmaLure"            FireLureNuke
    /call AbilitySet_Add "PlasmaLure"           FireLureNuke 
    /call AbilitySet_Add "Lure of Qunard"       FireLureNuke
    /call AbilitySet_Add "Lure of Sontalak"     FireLureNuke
    /call AbilitySet_Add "Lure of Fyrthek"      FireLureNuke
    /call AbilitySet_Add "Lure of the Arcanaforged" FireLureNuke
    /call AbilitySet_ChooseOuter FireLureNuke FireLureNuke
    
|- Magic Lure 60-67
    /call AbilitySet_Add "Lure of Lightning"    MagicLureNuke
    /call AbilitySet_Add "Lure of Thunder"      MagicLureNuke
    /call AbilitySet_Add "Lightningbane"        MagicLureNuke
    /call AbilitySet_Add "Permeating Ether"     MagicLureNuke
    /call AbilitySet_ChooseOuter MagicLureNuke MagicLureNuke

|-Fire Claw Nuke - Level Range 98 - 113
    /call AbilitySet_Add "Claw of the Duskflame" FireClaw
    /call AbilitySet_Add "Claw of Sontalak" FireClaw
    /call AbilitySet_Add "Claw of Qunard" FireClaw
    /call AbilitySet_Add "Claw of the Flameweaver" FireClaw
    /call AbilitySet_Add "Claw of the Flamewing" FireClaw
    /call AbilitySet_Add "Claw of Ingot" FireClaw
    /call AbilitySet_ChooseOuter FireClaw FireClaw
    
|-Ice Claw Nuke - Level Range 61 - 115
    /call AbilitySet_Add "Claw of the Void" IceClaw    
    /call AbilitySet_Add "Claw of Gozzrem" IceClaw
    /call AbilitySet_Add "Claw of Travenro" IceClaw
    /call AbilitySet_Add "Claw of the Oceanlord" IceClaw
    /call AbilitySet_Add "Claw of the Icewing" IceClaw
    /call AbilitySet_Add "Claw of the Abyss" IceClaw
    /call AbilitySet_Add "Glacial Claw" IceClaw
    /call AbilitySet_Add "Claw of Selig" IceClaw
    /call AbilitySet_Add "Claw of Selay" IceClaw   
    /call AbilitySet_Add "Claw of Vox" IceClaw
    /call AbilitySet_Add "Claw of Frost" IceClaw
    /call AbilitySet_Add "Claw of Ankexfen" IceClaw      
    /call AbilitySet_ChooseOuter  IceClaw IceClaw
    
|-Magic Claw Nuke - Level Range 96 - 111
    /call AbilitySet_Add "Claw of Itzal" MagicClaw
    /call AbilitySet_Add "Claw of Feshlak" MagicClaw
    /call AbilitySet_Add "Claw of Ellarr" MagicClaw
    /call AbilitySet_Add "Claw of the Indagatori" MagicClaw
    /call AbilitySet_Add "Claw of the Ashwing" MagicClaw
    /call AbilitySet_Add "Claw of the Battleforged" MagicClaw
    /call AbilitySet_ChooseOuter MagicClaw MagicClaw

|-CloudburstNuke - Level Range 72 - 112
    /call AbilitySet_Add "Cloudburst Lightningstrike" CloudburstNuke
    /call AbilitySet_Add "Cloudburst Joltstrike" CloudburstNuke
    /call AbilitySet_Add "Cloudburst Stormbolt" CloudburstNuke
    /call AbilitySet_Add "Cloudburst Thunderbolt" CloudburstNuke
    /call AbilitySet_Add "Cloudburst Stormstrike" CloudburstNuke
    /call AbilitySet_Add "Cloudburst Thunderbolt" CloudburstNuke
    /call AbilitySet_Add "Cloudburst Tempest" CloudburstNuke
    /call AbilitySet_Add "Cloudburst Storm" CloudburstNuke
    /call AbilitySet_Add "Cloudburst Levin" CloudburstNuke
    /call AbilitySet_Add "Cloudburst Bolts" CloudburstNuke   
    /call AbilitySet_Add "Cloudburst Strike" CloudburstNuke
    /call AbilitySet_ChooseOuter CloudburstNuke CloudburstNuke
    
|-FireEtherealNuke - Level Range 70 - 115
    /call AbilitySet_Add "Ethereal Immolation" FireEtherealNuke
    /call AbilitySet_Add "Ethereal Ignition" FireEtherealNuke
    /call AbilitySet_Add "Ethereal Brand" FireEtherealNuke
    /call AbilitySet_Add "Ethereal Skyfire" FireEtherealNuke
    /call AbilitySet_Add "Ethereal Skyblaze" FireEtherealNuke
    /call AbilitySet_Add "Ethereal Incandescence" FireEtherealNuke
    /call AbilitySet_Add "Ethereal Blaze" FireEtherealNuke
    /call AbilitySet_Add "Ethereal Inferno" FireEtherealNuke
    /call AbilitySet_Add "Ethereal Combustion" FireEtherealNuke
    /call AbilitySet_Add "Ethereal Incineration" FireEtherealNuke   
    /call AbilitySet_Add "Ethereal Conflagration" FireEtherealNuke
    /call AbilitySet_Add "Ether Flame" FireEtherealNuke    
    /call AbilitySet_ChooseOuter FireEtherealNuke FireEtherealNuke
    
|-IceEtherealNuke - Level Range 79 - 114
    /call AbilitySet_Add "Lunar Ice Comet" IceEtherealNuke
    /call AbilitySet_Add "Restless Ice Comet" IceEtherealNuke
    /call AbilitySet_Add "Ethereal Icefloe" IceEtherealNuke
    /call AbilitySet_Add "Ethereal Rimeblast" IceEtherealNuke
    /call AbilitySet_Add "Ethereal Hoarfrost" IceEtherealNuke
    /call AbilitySet_Add "Ethereal Frost" IceEtherealNuke
    /call AbilitySet_Add "Ethereal Glaciation" IceEtherealNuke
    /call AbilitySet_Add "Ethereal Iceblight" IceEtherealNuke
    /call AbilitySet_Add "Ethereal Rime" IceEtherealNuke
    /call AbilitySet_Add "Ethereal Freeze" IceEtherealNuke    
    /call AbilitySet_ChooseOuter IceEtherealNuke IceEtherealNuke
    
|-MagicEtherealNuke - Level Range 92 - 112
    /call AbilitySet_Add "Ethereal Mortar" MagicEtherealNuke
    /call AbilitySet_Add "Ethereal Blast" MagicEtherealNuke
    /call AbilitySet_Add "Ethereal Volley" MagicEtherealNuke
    /call AbilitySet_Add "Ethereal Flash" MagicEtherealNuke
    /call AbilitySet_Add "Ethereal Salvo" MagicEtherealNuke
    /call AbilitySet_Add "Ethereal Barrage" MagicEtherealNuke
    /call AbilitySet_Add "Ethereal Blitz" MagicEtherealNuke
    /call AbilitySet_ChooseOuter MagicEtherealNuke MagicEtherealNuke

|-FuseNuke - Level Range 100 - 115
    /call AbilitySet_Add "Ethereal Twist"   FuseNuke
    /call AbilitySet_Add "Ethereal Confluence" FuseNuke
    /call AbilitySet_Add "Ethereal Braid" FuseNuke
    /call AbilitySet_Add "Ethereal Fuse" FuseNuke
    /call AbilitySet_Add "Ethereal Weave" FuseNuke
    /call AbilitySet_Add "Ethereal Plait" FuseNuke
    /call AbilitySet_ChooseOuter FuseNuke FuseNuke

|-FireNuke - Level Range 4 - 115
    /call AbilitySet_Add "Kindleheart's Fire" FireNuke
    /call AbilitySet_Add "The Diabo's Fire" FireNuke
    /call AbilitySet_Add "Dagarn's Fire" FireNuke
    /call AbilitySet_Add "Dragoflux's Fire" FireNuke
    /call AbilitySet_Add "Narendi's Fire" FireNuke
    /call AbilitySet_Add "Gosik's Fire" FireNuke
    /call AbilitySet_Add "Daevan's Fire" FireNuke
    /call AbilitySet_Add "Lithara's Fire" FireNuke
    /call AbilitySet_Add "Klixcxyk's Fire" FireNuke
    /call AbilitySet_Add "Inizen's Fire" FireNuke   
    /call AbilitySet_Add "Sothgar's Flame" FireNuke
    /call AbilitySet_Add "Corona Flare" FireNuke 
    /call AbilitySet_Add "White Fire" FireNuke
    /call AbilitySet_Add "Garrison's Superior Sundering" FireNuke
    /call AbilitySet_Add "Conflagration" FireNuke
    /call AbilitySet_Add "Inferno Shock" FireNuke    
    /call AbilitySet_Add "Flame Shock" FireNuke
    /call AbilitySet_Add "Fire Bolt" FireNuke
    /call AbilitySet_Add "Shock of Fire" FireNuke   
    /call AbilitySet_ChooseOuter FireNuke FireNuke
    
|-IceNuke - Level Range 1 - 114
    /call AbilitySet_Add "Glacial Ice Cascade" IceNuke
    /call AbilitySet_Add "Tundra Ice Cascade" IceNuke
    /call AbilitySet_Add "Restless Ice Cascade" IceNuke
    /call AbilitySet_Add "Icefloe Cascade" IceNuke
    /call AbilitySet_Add "Rimeblast Cascade" IceNuke
    /call AbilitySet_Add "Hoarfrost Cascade" IceNuke
    /call AbilitySet_Add "Rime Cascade" IceNuke
    /call AbilitySet_Add "Glacial Cascade" IceNuke
    /call AbilitySet_Add "Icesheet Cascade" IceNuke
    /call AbilitySet_Add "Glacial Collapse" IceNuke   
    /call AbilitySet_Add "Icefall Avalanche" IceNuke
    /call AbilitySet_Add "Gelidin Comet" IceNuke 
    /call AbilitySet_Add "Ice Meteor" IceNuke
    /call AbilitySet_Add "Ice Spear of Solist" IceNuke
    /call AbilitySet_Add "Frozen Harpoon" IceNuke
    /call AbilitySet_Add "Ice Comet" IceNuke    
    /call AbilitySet_Add "Ice Shock" IceNuke
    /call AbilitySet_Add "Frost Shock" IceNuke
    /call AbilitySet_Add "Shock of Ice" IceNuke   
    /call AbilitySet_Add "Frost Bolt" IceNuke  
    /call AbilitySet_Add "Blast of Cold" IceNuke
    /call AbilitySet_ChooseOuter IceNuke IceNuke 

|-MagicNuke - Level Range 10 - 113
    /call AbilitySet_Add "Lightning Cyclone" MagicNuke
    /call AbilitySet_Add "Lightning Maelstrom"  MagicNuke
    /call AbilitySet_Add "Lightning Roar" MagicNuke
    /call AbilitySet_Add "Lightning Tempest" MagicNuke
    /call AbilitySet_Add "Lightning Storm" MagicNuke
    /call AbilitySet_Add "Lightning Squall" MagicNuke
    /call AbilitySet_Add "Lightning Swarm" MagicNuke
    /call AbilitySet_Add "Lightning Helix" MagicNuke
    /call AbilitySet_Add "Ribbon Lightning" MagicNuke
    /call AbilitySet_Add "Rolling Lightning" MagicNuke
    /call AbilitySet_Add "Ball Lightning" MagicNuke
    /call AbilitySet_Add "Spark of Lightning" MagicNuke   
    /call AbilitySet_Add "Draught of Lightning" MagicNuke
    /call AbilitySet_Add "Elnerick's Electrical Rending" MagicNuke 
    /call AbilitySet_Add "Draught of Jiva" MagicNuke
    /call AbilitySet_Add "Voltaic Draught" MagicNuke
    /call AbilitySet_Add "Rend" MagicNuke
    /call AbilitySet_Add "Lightning Shock" MagicNuke    
    /call AbilitySet_Add "Thunder Strike" MagicNuke
    /call AbilitySet_Add "Garrison's Mighty Mana Shock" MagicNuke
    /call AbilitySet_Add "Lightning Bolt" MagicNuke   
    /call AbilitySet_Add "Shock of Lightning" MagicNuke  
    /call AbilitySet_ChooseOuter MagicNuke MagicNuke

|-Familiar Buff   
    /call AbilitySet_Add "Greater Familiar" FamiliarBuff
    /call AbilitySet_Add "Familiar" FamiliarBuff
    /call AbilitySet_Add "Lesser Familiar" FamiliarBuff   
    /call AbilitySet_Add "Minor Familiar" FamiliarBuff  
    /call AbilitySet_ChooseOuter FamiliarBuff FamiliarBuff
    
|-Self HP Buff * Var Name: SelfHPBuff string outer
    /call AbilitySet_Add "Shield of Memories" SelfHPBuff
    /call AbilitySet_Add "Shield of Shadow" SelfHPBuff
    /call AbilitySet_Add "Shield of Restless Ice" SelfHPBuff
    /call AbilitySet_Add "Shield of Scales" SelfHPBuff
    /call AbilitySet_Add "Shield of the Pellarus" SelfHPBuff
    /call AbilitySet_Add "Shield of the Dauntless" SelfHPBuff
    /call AbilitySet_Add "Shield of Bronze" SelfHPBuff
    /call AbilitySet_Add "Shield of Dreams" SelfHPBuff
    /call AbilitySet_Add "Shield of the Void" SelfHPBuff
    /call AbilitySet_Add "Bulwark of the Crystalwing" SelfHPBuff
    /call AbilitySet_Add "Shield of the Crystalwing" SelfHPBuff
    /call AbilitySet_Add "Ether Shield" SelfHPBuff   
    /call AbilitySet_Add "Shield of Maelin" SelfHPBuff
    /call AbilitySet_Add "Shield of the Arcane" SelfHPBuff 
    /call AbilitySet_Add "Shield of the Magi" SelfHPBuff
    /call AbilitySet_Add "Arch Shielding" SelfHPBuff
    /call AbilitySet_Add "Greater Shielding" SelfHPBuff
    /call AbilitySet_Add "Major Shielding" SelfHPBuff    
    /call AbilitySet_Add "Shielding" SelfHPBuff
    /call AbilitySet_Add "Lesser Shielding" SelfHPBuff
    /call AbilitySet_Add "Minor Shielding" SelfHPBuff     
    /call AbilitySet_ChooseOuter SelfHPBuff SelfHPBuff
    
|-Self Rune 1 * Var Name: SelfRune1 string outer
    /call AbilitySet_Add "Aegis of Remembrance" SelfRune1
    /call AbilitySet_Add "Aegis of the Umbra" SelfRune1
    /call AbilitySet_Add "Aegis of the Crystalwing" SelfRune1
    /call AbilitySet_Add "Armor of Wirn" SelfRune1   
    /call AbilitySet_Add "Armor of the Codex" SelfRune1
    /call AbilitySet_Add "Armor of the Stonescale" SelfRune1 
    /call AbilitySet_Add "Armor of the Crystalwing" SelfRune1
    /call AbilitySet_Add "Dermis of the Crystalwing" SelfRune1
    /call AbilitySet_Add "Squamae of the Crystalwing" SelfRune1
    /call AbilitySet_Add "Laminae of the Crystalwing" SelfRune1    
    /call AbilitySet_Add "Scales of the Crystalwing" SelfRune1
    /call AbilitySet_Add "Ether Skin" SelfRune1
    /call AbilitySet_Add "Force Shield" SelfRune1     
    /call AbilitySet_ChooseOuter SelfRune1 SelfRune1
    
|-StripBuffSpell
    /call AbilitySet_Add "Annul Magic" StripBuffSpell   
    /call AbilitySet_Add "Nullify Magic" StripBuffSpell
    /call AbilitySet_Add "Cancel Magic" StripBuffSpell     
    /call AbilitySet_ChooseOuter StripBuffSpell StripBuffSpell

|-AllianceSpell
    /call AbilitySet_Add "Frostbound Conjunction" AllianceSpell
    /call AbilitySet_Add "Frostbound Coalition" AllianceSpell
    /call AbilitySet_Add "Frostbound Covenant" AllianceSpell
    /call AbilitySet_Add "Frostbound Alliance" AllianceSpell     
    /call AbilitySet_ChooseOuter AllianceSpell AllianceSpell
    
|-DichoSpell
    /call AbilitySet_Add "Ecliptic Fire" DichoSpell
    /call AbilitySet_Add "Composite Fire" DichoSpell
    /call AbilitySet_Add "Dissident Fire" DichoSpell
    /call AbilitySet_Add "Dichotomic Fire" DichoSpell     
    /call AbilitySet_ChooseOuter DichoSpell DichoSpell
    
|-Root Spell * Var Name: RootSpell string outer
    /call AbilitySet_Add "Greater Fetter" RootSpell
    /call AbilitySet_Add "Fetter" RootSpell
    /call AbilitySet_Add "Paralyzing Earth" RootSpell    
    /call AbilitySet_Add "Immobilize" RootSpell
    /call AbilitySet_Add "Instill" RootSpell
    /call AbilitySet_Add "Root" RootSpell     
    /call AbilitySet_ChooseOuter RootSpell RootSpell
    
|-TwincastSpell
    /call AbilitySet_Add "Twincast" TwincastSpell   
    /call AbilitySet_ChooseOuter TwincastSpell TwincastSpell
    
|-SnareSpell
    /call AbilitySet_Add "Atol's Concussive Shackles" SnareSpell   
    /call AbilitySet_Add "Atol's Spectral Shackles" SnareSpell
    /call AbilitySet_Add "Bonds of Force" SnareSpell  
    /call AbilitySet_ChooseOuter SnareSpell SnareSpell
|
|-JoltSpell - Using Freeze Line 87+
    /call AbilitySet_Add "Spinalfreeze" JoltSpell
    /call AbilitySet_Add "Cerebrumfreeze" JoltSpell
    /call AbilitySet_Add "Neurofreeze" JoltSpell
    /call AbilitySet_Add "Cortexfreeze" JoltSpell   
    /call AbilitySet_Add "Synapsefreeze" JoltSpell
    /call AbilitySet_Add "Flashfreeze" JoltSpell 
    /call AbilitySet_Add "Skullfreeze" JoltSpell
    /call AbilitySet_Add "Thoughtfreeze" JoltSpell
    /call AbilitySet_Add "Brainfreeze" JoltSpell
    /call AbilitySet_Add "Mindfreeze" JoltSpell    
    /call AbilitySet_Add "Concussive Flash" JoltSpell
    /call AbilitySet_Add "Concussive Burst" JoltSpell
    /call AbilitySet_Add "Concussive Blast" JoltSpell 
    /call AbilitySet_Add "Ancient: Greater Concussion" JoltSpell
    /call AbilitySet_Add "Concussion" JoltSpell    
    /call AbilitySet_ChooseOuter JoltSpell JoltSpell    
    
|-HarvestSpell - Level Range 32 -
    /call AbilitySet_Add "Contemplative Harvest" HarvestSpell
    /call AbilitySet_Add "Shadow Harvest" HarvestSpell
    /call AbilitySet_Add "Quiet Harvest" HarvestSpell   
    /call AbilitySet_Add "Musing Harvest" HarvestSpell
    /call AbilitySet_Add "Quiescent Harvest" HarvestSpell 
    /call AbilitySet_Add "Bucolic Harvest" HarvestSpell
    /call AbilitySet_Add "Placid Harvest" HarvestSpell
    /call AbilitySet_Add "Soothing Harvest" HarvestSpell
    /call AbilitySet_Add "Serene Harvest" HarvestSpell    
    /call AbilitySet_Add "Tranquil Harvest" HarvestSpell
    /call AbilitySet_Add "Patient Harvest" HarvestSpell
    /call AbilitySet_Add "Harvest" HarvestSpell     
    /call AbilitySet_ChooseOuter HarvestSpell HarvestSpell
 
|-GambitSpell
    /call AbilitySet_Add "Anodyne Gambit" GambitSpell
    /call AbilitySet_Add "Idyllic Gambit" GambitSpell
    /call AbilitySet_Add "Musing Gambit" GambitSpell
    /call AbilitySet_Add "Quiescent Gambit" GambitSpell   
    /call AbilitySet_Add "Bucolic Gambit" GambitSpell  
    /call AbilitySet_ChooseOuter GambitSpell GambitSpell
    
|-PetSpell - Level Range 59 - 114
    /call AbilitySet_Add "Kindleheart's Pyroblade" PetSpell
    /call AbilitySet_Add "Diabo Xi Fer's Pyroblade" PetSpell
    /call AbilitySet_Add "Ricartine's Pyroblade" PetSpell
    /call AbilitySet_Add "Virnax's Pyroblade" PetSpell   
    /call AbilitySet_Add "Yulin's Pyroblade" PetSpell
    /call AbilitySet_Add "Mul's Pyroblade" PetSpell 
    /call AbilitySet_Add "Burnmaster's Pyroblade" PetSpell
    /call AbilitySet_Add "Lithara's Pyroblade" PetSpell
    /call AbilitySet_Add "Daveron's Pyroblade" PetSpell
    /call AbilitySet_Add "Euthanos' Flameblade" PetSpell    
    /call AbilitySet_Add "Ethantis's Burning Blade" PetSpell
    /call AbilitySet_Add "Solist's Frozen Sword" PetSpell
    /call AbilitySet_Add "Flaming Sword of Xuzl" PetSpell     
    /call AbilitySet_ChooseOuter PetSpell PetSpell

|-WildNuke - Level Range 71 - 111
    /call AbilitySet_Add "Wildspell Strike" WildNuke
    /call AbilitySet_Add "Wildflame Strike" WildNuke
    /call AbilitySet_Add "Wildscorch Strike" WildNuke
    /call AbilitySet_Add "Wildflash Strike" WildNuke 
    /call AbilitySet_Add "Wildflash Barrage" WildNuke
    /call AbilitySet_Add "Wildether Barrage" WildNuke
    /call AbilitySet_Add "Wildspark Barrage" WildNuke
    /call AbilitySet_Add "Wildmana Barrage" WildNuke    
    /call AbilitySet_Add "Wildmagic Blast" WildNuke
    /call AbilitySet_Add "Wildmagic Burst" WildNuke
    /call AbilitySet_Add "Wildmagic Strike" WildNuke     
    /call AbilitySet_ChooseOuter WildNuke WildNuke
    
|-VortexNuke - WizType use Defined by Debuff, not resist type of spell
|- NOTE: ${Spell[${VortexNuke}].ResistType} can be used to determine which resist type is getting debuffed
    /call AbilitySet_Add "Shadebright Vortex" VortexNuke
    /call AbilitySet_Add "Thaumaturgic Vortex" VortexNuke
    /call AbilitySet_Add "Stormjolt Vortex" VortexNuke
    /call AbilitySet_Add "Shocking Vortex" VortexNuke   
       |- Hoarfrost Vortex has a Fire Debuff
    /call AbilitySet_Add "Hoarfrost Vortex" VortexNuke
    |- Ether Vortex has a Cold Debuff
    /call AbilitySet_Add "Ether Vortex" VortexNuke
    |- Incandescent Vortex has a Magic Debuff
    /call AbilitySet_Add "Incandescent Vortex" VortexNuke
       |- Frost Vortex has a Fire Debuff
    /call AbilitySet_Add "Frost Vortex" VortexNuke
    |- Power Vortex has a Cold Debuff
    /call AbilitySet_Add "Power Vortex" VortexNuke
    |- Flame Vortex has a Magic Debuff
    /call AbilitySet_Add "Flame Vortex" VortexNuke 
    |- Ice Vortex has a Fire Debuff
    /call AbilitySet_Add "Ice Vortex" VortexNuke
    |- Mana Vortex has a Cold Debuff
    /call AbilitySet_Add "Mana Vortex" VortexNuke
    |- Fire Vortex has a Magic Debuff
    /call AbilitySet_Add "Fire Vortex" VortexNuke     
    /call AbilitySet_ChooseOuter VortexNuke VortexNuke
    
|-ChaosNuke - Level Range 70 - 111
    /call AbilitySet_Add "Chaos Flame" ChaosNuke
    /call AbilitySet_Add "Chaos Inferno" ChaosNuke
    /call AbilitySet_Add "Chaos Burn" ChaosNuke 
    /call AbilitySet_Add "Chaos Scintillation" ChaosNuke
    /call AbilitySet_Add "Chaos Incandescence" ChaosNuke
    /call AbilitySet_Add "Chaos Blaze" ChaosNuke
    /call AbilitySet_Add "Chaos Char" ChaosNuke    
    /call AbilitySet_Add "Chaos Conflagration" ChaosNuke
    /call AbilitySet_Add "Chaos Immolation" ChaosNuke
    /call AbilitySet_Add "Chaos Flame" ChaosNuke     
    /call AbilitySet_ChooseOuter ChaosNuke ChaosNuke
    
| - FireRainLureNuke - Level 64 - 115
    /call AbilitySet_Add "Volcanic Burst" FireRainLureNuke
    /call AbilitySet_Add "Tears of Arlyxir" FireRainLureNuke
    /call AbilitySet_Add "Meteor Storm" FireRainLureNuke
    /call AbilitySet_Add "Volcanic Eruption" FireRainLureNuke
    /call AbilitySet_Add "Pyroclastic Eruption" FireRainLureNuke
    /call AbilitySet_Add "Magmatic Eruption" FireRainLureNuke
    /call AbilitySet_Add "Magmatic Downpour" FireRainLureNuke
    /call AbilitySet_Add "Magmatic Outburst" FireRainLureNuke
    /call AbilitySet_Add "Magmatic Vent" FireRainLureNuke
    /call AbilitySet_Add "Magmatic Burst" FireRainLureNuke
    /call AbilitySet_Add "Magmatic Explosion" FireRainLureNuke
    /call AbilitySet_Add "Volcanic Downpour" FireRainLureNuke
    /call AbilitySet_Add "Volcanic Barrage" FireRainLureNuke
    /call AbilitySet_ChooseOuter FireRainLureNuke FireRainLureNuke

| - Rain Spells Listed here are used Primarily for TLP Mode.
| - Magic Rain - Only have 3 of them so Not Sustainable.
| - Ice Rain  Up to LVl 115
    /call AbilitySet_Add "Icestrike" IceRainNuke
    /call AbilitySet_Add "Frost Storm" IceRainNuke
    /call AbilitySet_Add "Tears of Prexus" IceRainNuke
    /call AbilitySet_Add "Tears of Marr" IceRainNuke
    /call AbilitySet_Add "Gelid Rains" IceRainNuke
    /call AbilitySet_Add "Icicle Deluge" IceRainNuke
    /call AbilitySet_Add "Icicle Storm" IceRainNuke
    /call AbilitySet_Add "Icicle Torrent" IceRainNuke
    /call AbilitySet_Add "Hail Torrent" IceRainNuke
    /call AbilitySet_Add "Frost Torrent" IceRainNuke
    /call AbilitySet_Add "Tamagrist Torrent" IceRainNuke
    /call AbilitySet_Add "Darkwater Torrent" IceRainNuke
    /call AbilitySet_Add "Frostbite Torrent" IceRainNuke
    /call AbilitySet_Add "Coldburst Torrent" IceRainNuke
    /call AbilitySet_Add "Hypothermic Torrent" IceRainNuke
    /call AbilitySet_Add "Rimeclaw Torrent" IceRainNuke
    /call AbilitySet_ChooseOuter IceRainNuke IceRainNuke
    
| - Fire Rain  -10 Resist Not Lure tears. 1-111
    /call AbilitySet_Add "Firestorm"        FireRainNuke
    /call AbilitySet_Add "Lava Storm"       FireRainNuke
    /call AbilitySet_Add "Tears of Solusek" FireRainNuke
    /call AbilitySet_Add "Tears of Ro"      FireRainNuke
    /call AbilitySet_Add "Tears of the Sun" FireRainNuke
    /call AbilitySet_Add "Tears of the Betrayed" FireRainNuke
    /call AbilitySet_Add "Tears of the Forsaken" FireRainNuke
    /call AbilitySet_Add "Tears of the Pyrilen" FireRainNuke
    /call AbilitySet_Add "Tears of Flame" FireRainNuke
    /call AbilitySet_Add "Tears of Daevan" FireRainNuke
    /call AbilitySet_Add "Tears of Gosik" FireRainNuke
    /call AbilitySet_Add "Tears of Narendi" FireRainNuke
    /call AbilitySet_Add "Tears of Dragoflux" FireRainNuke
    /call AbilitySet_Add "Tears of Wildfire" FireRainNuke
    /call AbilitySet_Add "Tears of Night Fire" FireRainNuke
    /call AbilitySet_Add "Tears of the Rescued" FireRainNuke
    /call AbilitySet_ChooseOuter FireRainNuke FireRainNuke
    
|-EvacSpell - TODO: verify its using the AA evac if we have it
    /call AbilitySet_Add "Evacuate" EvacSpell
    /call AbilitySet_Add "Lesser Evacuate" EvacSpell   
    /call AbilitySet_ChooseOuter EvacSpell EvacSpell

|-StunSpell - Level Range 19 - 115
    /call AbilitySet_Add "Teladaka" StunSpell
    /call AbilitySet_Add "Teladaja" StunSpell
    /call AbilitySet_Add "Telajaga" StunSpell
    /call AbilitySet_Add "Telanata" StunSpell
    /call AbilitySet_Add "Telanara" StunSpell   
    /call AbilitySet_Add "Telanaga" StunSpell
    /call AbilitySet_Add "Telanama" StunSpell
    /call AbilitySet_Add "Telakama" StunSpell   
    /call AbilitySet_Add "Telajara" StunSpell
    /call AbilitySet_Add "Telajasz" StunSpell 
    /call AbilitySet_Add "Telakisz" StunSpell
    /call AbilitySet_Add "Telekara" StunSpell
    /call AbilitySet_Add "Telaka" StunSpell
    /call AbilitySet_Add "Telekin" StunSpell    
    /call AbilitySet_Add "Markar's Discord" StunSpell
    /call AbilitySet_Add "Markar's Clash" StunSpell
    /call AbilitySet_Add "Tishan's Clash" StunSpell     
    /call AbilitySet_ChooseOuter StunSpell StunSpell

| - Fast Ice Nuke   Ends @ lvl 68 - followed by Ice Claws
    /call AbilitySet_Add "Draught of Ice"   FastIceNuke
    /call AbilitySet_Add "Frost Shock"      FastIceNuke
    /call AbilitySet_Add "Shock of Ice"     FastIceNuke
    /call AbilitySet_Add "Draught of E`ci"  FastIceNuke   
    /call AbilitySet_Add "Black Ice"        FastIceNuke
    /call AbilitySet_Add "Spark of Ice"     FastIceNuke     
    /call AbilitySet_ChooseOuter FastIceNuke FastIceNuke
   
| - Fast Fire Nuke Ends @ lvl Followed Up By Chaos Nukes
    /call AbilitySet_Add "Shock of Fire"    FastFireNuke
    /call AbilitySet_Add "Flame Shock"      FastFireNuke
    /call AbilitySet_Add "Inferno Shock"    FastFireNuke
    /call AbilitySet_Add "Draught of Fire"  FastFireNuke
    /call AbilitySet_Add "Draught of Ro"    FastFireNuke
    /call AbilitySet_Add "Chaos Flame"      FastFireNuke
    /call AbilitySet_Add "Spark of Fire"    FastFireNuke
    /call AbilitySet_ChooseOuter FastFireNuke FastFireNuke
    
| - Fast Magic Nuke Goes to 115
    /call AbilitySet_Add "Voltaic Draught"          FastMagicNuke
    /call AbilitySet_Add "Draught of Lightning"     FastMagicNuke
    /call AbilitySet_Add "Spark of Lightning"       FastMagicNuke  
    /call AbilitySet_Add "Leap of Stormjolts"       FastMagicNuke  
    /call AbilitySet_Add "Leap of Stormbolts"       FastMagicNuke
    /call AbilitySet_Add "Leap of Static Sparks"    FastMagicNuke
    /call AbilitySet_Add "Leap of Plasma"           FastMagicNuke
    /call AbilitySet_Add "Leap of Corposantum"      FastMagicNuke
    /call AbilitySet_Add "Leap of Static Jolts"     FastMagicNuke
    /call AbilitySet_Add "Leap of Static Bolts"     FastMagicNuke
    /call AbilitySet_Add "Leap of Sparks"           FastMagicNuke
    /call AbilitySet_Add "Leap of Levinsparks"      FastMagicNuke
    /call AbilitySet_ChooseOuter FastMagicNuke FastMagicNuke

| - Big Ice Nukes  50-69 
    /call AbilitySet_Add "Ice Comet"                    BigIceNuke
    /call AbilitySet_Add "Ice Spear of Solist"          BigIceNuke
    /call AbilitySet_Add "Ancient: Destruction of Ice"  BigIceNuke       
    /call AbilitySet_Add "Ice Meteor"                   BigIceNuke
    /call AbilitySet_Add "Gelidin Comet"                BigIceNuke
    /call AbilitySet_ChooseOuter BigIceNuke BigIceNuke   

| - Big Fire Nukes
    /call AbilitySet_Add "Conflagration"                    BigFireNuke
    /call AbilitySet_Add "Sunstrike"                        BigFireNuke
    /call AbilitySet_Add "Garrison's Superior Sundering"    BigFireNuke
    /call AbilitySet_Add "Strike of Solusek"                BigFireNuke
    /call AbilitySet_Add "White Fire"                       BigFireNuke
    /call AbilitySet_Add "Ether Flame"                      BigFireNuke    
    /call AbilitySet_Add "Corona Flare"                     BigFireNuke
    /call AbilitySet_ChooseOuter BigFireNuke BigFireNuke

| - Big Magic Nukes
    /call AbilitySet_Add "Rend"                             BigMagicNuke
    /call AbilitySet_Add "Elnerick's Electrical Rending"    BigMagicNuke
    /call AbilitySet_Add "Agnarr's Thunder"                 BigMagicNuke
    /call AbilitySet_Add "Shock of Magic"                   BigMagicNuke
    /call AbilitySet_Add "Thundaka"                         BigMagicNuke
    /call AbilitySet_Add "Mana Weave"                       BigMagicNuke
    /call AbilitySet_ChooseOuter BigMagicNuke BigMagicNuke



    /call ChatBegList_Add WIZBegs bindme Spell "Bind Affinity" sender TRUE 
    /call ChatBegList_Add WIZBegs gatenorth Spell "North Gate" sender TRUE
    /call ChatBegList_Add WIZBegs gatefay Spell "Fay Gate" sender TRUE
    /call ChatBegList_Add WIZBegs portalnorth Spell "North Portal" sender TRUE 
    /call ChatBegList_Add WIZBegs portalfay Spell "Fay Portal" sender TRUE 
    /call ChatBegList_add WIZBegs portallcea Spell "Lceanium Portal" sender TRUE 
/return 

|-----------------------------------------------------------------------------
|- SUB - fireSpellConfig - Configure Spell Gems for Magic Wizard Type
|-----------------------------------------------------------------------------
Sub WIZ_ModeConfigMODEFIRE
    /if (${FireClaw.Equal[NULL]} && ${IceClaw.NotEqual[NULL]}) {
        /varset FireClaw ${IceClaw}
        /varset Spell1 ${IceClaw}
    } else /if (${FireClaw.Equal[NULL]} && ${StunSpell.NotEqual[NULL]}) {
        /varset FireClaw ${StunSpell}
        /varset Spell1 ${StunSpell}
    } else {
        /varset Spell1 ${FireClaw}
    }
 
    /if (${FireEtherealNuke.Equal[NULL]} && ${FireNuke.NotEqual[NULL]}) {
        /varset Spell2 ${FireNuke}
    } else {
        /varset Spell2 ${FireEtherealNuke}
    } 

    |- If for some reason you Do not have Dissodent flame etc.. Load a stun
    /if (${DichoSpell.NotEqual[NULL]}) {
        /varset Spell3 ${DichoSpell}
    } else {
        /varset Spell3 ${MagicNuke}
    }    

    /if (${FuseNuke.Equal[NULL]} && ${IceNuke.NotEqual[NULL]}) {
        /varset Spell4 ${IceNuke}
    } else {
        /varset Spell4 ${FuseNuke}
    }     
    
    /if (${TwincastSpell.Equal[NULL]} && ${FireClaw.NotEqual[${StunSpell}]}) {
        /varset Spell5 ${StunSpell}
    } else /if (${TwincastSpell.Equal[NULL]} && ${FireClaw.Equal[${StunSpell}]} && ${SnareSpell.NotEqual[NULL]}) {
        /varset Spell5 ${SnareSpell}
    } else /if (${TwincastSpell.Equal[NULL]} && ${FireClaw.Equal[${StunSpell}]} && ${RootSpell.NotEqual[NULL]}) {
        /varset Spell5 ${RootSpell}
    } else {
        /varset Spell5 ${TwincastSpell}
    }    
    
    |- Check for Gambit version first, if not there use regular harvest.
    /if (${GambitSpell.NotEqual[NULL]}) {
        /varset Spell6 ${GambitSpell}
    } else {
        /varset Spell6 ${HarvestSpell}
    }

    |- If you do not have Vortex (debuff nuke) load a fast cast nuke
    |- Does not conflict with fastcast load above, because you cannot obtain 11 spell gems before level 84
    /if (${VortexNuke.NotEqual[NULL]}) {
        /varset Spell7 ${VortexNuke}
    } else {
        /varset Spell7 ${FastMagicNuke}
    }
    
    /varset Spell8 ${JoltSpell}

    | Use our Summon Sword Pet if we do not have cold ethereal nuke yet
    /if (${Me.Level}<79 || ${IceEtherealNuke.Equal[NULL]}) {
        /varset Spell9 ${PetSpell}
    } else {
        /varset Spell9 ${IceEtherealNuke}
    }       

    /varset Spell10 ${FireRainLureNuke}
    /varset Spell11 ${ChaosNuke}

    /if (${FuseNuke.NotEqual[${FireNuke}]} && ${CloudburstNuke.Equal[NULL]}) {
        /varset Spell12 ${FireNuke}
    } else {
        /varset Spell12 ${CloudburstNuke}
    }
    
    |- Check to see if fire ice or magic nuke are not used yet
    /if ( ${FireNuke.NotEqual[${FireClaw}]} && ${FireNuke.NotEqual[NULL]} ) {
        /varset Spell13 ${FireNuke}
    } else /if ( ${IceNuke.NotEqual[${FuseNuke}]} && ${IceNuke.NotEqual[NULL]} ) {
        /varset Spell13 ${IceNuke}
    } else /if ( ${DichoSpell.NotEqual[NULL]} && ${MagicNuke.NotEqual[NULL]}) {
        /varset Spell13 ${MagicNuke}
    } else {
        /varset Spell13 ${RootSpell}
    }
    
    /call WIZ_DefaultSelfBuffRotationConfig WIZ_Downtime_MODEFIRE_Rotation
    /call WIZ_DefaultDPSRotationConfig WIZ_DPS_MODEFIRE_Rotation
/return  

|-----------------------------------------------------------------------------
|- SUB - iceSpellConfig - Configure Spell Gems for Magic Wizard Type
|-----------------------------------------------------------------------------
Sub WIZ_ModeConfigMODEICE
    /if (${IceClaw.Equal[NULL]} && ${MagicClaw.NotEqual[NULL]}) {
        /varset IceClaw ${MagicClaw}
        /varset Spell1 ${MagicClaw}
    } else /if (${IceClaw.Equal[NULL]} && ${StunSpell.NotEqual[NULL]}) {
        /varset IceClaw ${StunSpell}
        /varset Spell1 ${StunSpell}
    } else {
        /varset Spell1 ${IceClaw}
    }
 
    /if (${IceEtherealNuke.Equal[NULL]} && ${IceNuke.NotEqual[NULL]}) {
        /varset Spell2 ${IceNuke}
    } else {
        /varset Spell2 ${IceEtherealNuke}
    } 

    |- If for some reason you Do not have Dissodent flame etc.. Load a stun
    /if (${DichoSpell.NotEqual[NULL]}) {
        /varset Spell3 ${DichoSpell}
    } else {
        /varset Spell3 ${MagicNuke}
    }    

    /if (${FuseNuke.Equal[NULL]} && ${FireNuke.NotEqual[NULL]}) {
        /varset Spell4 ${FireNuke}
    } else {
        /varset Spell4 ${FuseNuke}
    }     
    
    /if (${TwincastSpell.Equal[NULL]} && ${IceClaw.NotEqual[${StunSpell}]}) {
        /varset Spell5 ${StunSpell}
    } else /if (${TwincastSpell.Equal[NULL]} && ${IceClaw.Equal[${StunSpell}]} && ${SnareSpell.NotEqual[NULL]}) {
        /varset Spell5 ${SnareSpell}
    } else /if (${TwincastSpell.Equal[NULL]} && ${IceClaw.Equal[${StunSpell}]} && ${RootSpell.NotEqual[NULL]}) {
        /varset Spell5 ${RootSpell}
    } else {
        /varset Spell5 ${TwincastSpell}
    }    
    
    |- Check for Gambit version first, if not there use regular harvest.
    /if (${GambitSpell.NotEqual[NULL]}) {
        /varset Spell6 ${GambitSpell}
    } else {
        /varset Spell6 ${HarvestSpell}
    }

    |- If you do not have Vortex (debuff nuke) load a fast cast nuke
    |- Does not conflict with fastcast load above, because you cannot obtain 11 spell gems before level 84
    /if (${VortexNuke.NotEqual[NULL]}) {
        /varset Spell7 ${VortexNuke}
    } else {
        /varset Spell7 ${FastMagicNuke}
    }
    
    /varset Spell8 ${JoltSpell}

    | Use our Summon Sword Pet if we do not have cold ethereal nuke yet
    /if (${Me.Level}<79 || ${MagicEtherealNuke.Equal[NULL]}) {
        /varset Spell9 ${PetSpell}
    } else {
        /varset Spell9 ${MagicEtherealNuke}
    }       

    /varset Spell10 ${FireRainLureNuke}
    /varset Spell11 ${ChaosNuke}

    /if (${FuseNuke.NotEqual[${FireNuke}]} && ${CloudburstNuke.Equal[NULL]}) {
        /varset Spell12 ${FireNuke}
    } else {
        /varset Spell12 ${CloudburstNuke}
    }
    
    |- Check to see if fire ice or magic nuke are not used yet
    /if (${FireNuke.NotEqual[${FireClaw}]} && ${FireNuke.NotEqual[NULL]}) {
        /varset Spell13 ${FireNuke}
    } else /if (${IceNuke.NotEqual[${FuseNuke}]} && ${IceNuke.NotEqual[NULL]}) {
        /varset Spell13 ${IceNuke}
    } else /if (${DichoSpell.NotEqual[NULL]} && ${MagicNuke.NotEqual[NULL]}) {
        /varset Spell13 ${MagicNuke}
    } else {
        /varset Spell13 ${RootSpell}
    }

    /call WIZ_DefaultSelfBuffRotationConfig WIZ_Downtime_MODEICE_Rotation
    /call WIZ_DefaultDPSRotationConfig WIZ_DPS_MODEICE_Rotation

/return  

|-----------------------------------------------------------------------------
|- SUB - magicSpellConfig - Configure Spell Gems for Magic Wizard Type
|-----------------------------------------------------------------------------
Sub WIZ_ModeConfigMODEMAGIC  
    /if (${MagicClaw.Equal[NULL]} && ${IceClaw.NotEqual[NULL]}) {
        /varset MagicClaw ${IceClaw}
        /varset Spell1 ${IceClaw}
    } else /if (${MagicClaw.Equal[NULL]} && ${StunSpell.NotEqual[NULL]}) {
        /varset MagicClaw ${StunSpell}
        /varset Spell1 ${StunSpell}
    } else {
        /varset Spell1 ${MagicClaw}
    }
 
    /if (${MagicEtherealNuke.Equal[NULL]} && ${MagicNuke.NotEqual[NULL]}) {
        /varset Spell2 ${MagicNuke}
    } else {
        /varset Spell2 ${MagicEtherealNuke}
    } 

    |- If for some reason you Do not have Dissodent flame etc.. Load a stun
    /if (${DichoSpell.NotEqual[NULL]}) {
        /varset Spell3 ${DichoSpell}
    } else {
        /varset Spell3 ${IceNuke}
    }    

    /if (${FuseNuke.Equal[NULL]} && ${FireNuke.NotEqual[NULL]}) {
        /varset Spell4 ${FireNuke}
    } else {
        /varset Spell4 ${FuseNuke}
    }     
    
    /if (${TwincastSpell.Equal[NULL]} && ${MagicClaw.NotEqual[${StunSpell}]}) {
        /varset Spell5 ${StunSpell}
    } else /if (${TwincastSpell.Equal[NULL]} && ${MagicClaw.Equal[${StunSpell}]} && ${SnareSpell.NotEqual[NULL]}) {
        /varset Spell5 ${SnareSpell}
    } else /if (${TwincastSpell.Equal[NULL]} && ${MagicClaw.Equal[${StunSpell}]} && ${RootSpell.NotEqual[NULL]}) {
        /varset Spell5 ${RootSpell}
    } else {
        /varset Spell5 ${TwincastSpell}
    }    
    
    |- Check for Gambit version first, if not there use regular harvest.
    /if (${GambitSpell.NotEqual[NULL]}) {
        /varset Spell6 ${GambitSpell}
    } else {
        /varset Spell6 ${HarvestSpell}
    }

    |- If you do not have Vortex (debuff nuke) load a fast cast nuke
    |- Does not conflict with fastcast load above, because you cannot obtain 11 spell gems before level 84
    /if (${VortexNuke.NotEqual[NULL]}) {
        /varset Spell7 ${VortexNuke}
    } else {
        /varset Spell7 ${FastMagicNuke}
    }
    
    /varset Spell8 ${JoltSpell}

    | Use our Summon Sword Pet if we do not have cold ethereal nuke yet
    /if (${Me.Level}<79 || ${IceEtherealNuke.Equal[NULL]}) {
        /varset Spell9 ${PetSpell}
    } else {
        /varset Spell9 ${IceEtherealNuke}
    }       

    /varset Spell10 ${FireRainLureNuke}
    /varset Spell11 ${ChaosNuke}

    /if (${FuseNuke.NotEqual[${FireNuke}]} && ${CloudburstNuke.Equal[NULL]}) {
        /varset Spell12 ${FireNuke}
    } else {
        /varset Spell12 ${CloudburstNuke}
    }
    
    |- Check to see if fire ice or magic nuke are not used yet
    /if (${FireNuke.NotEqual[${FireClaw}]} && ${FireNuke.NotEqual[NULL]}) {
        /varset Spell13 ${FireNuke}
    } else /if (${IceNuke.NotEqual[${FuseNuke}]} && ${IceNuke.NotEqual[NULL]}) {
        /varset Spell13 ${IceNuke}
    } else /if (${DichoSpell.NotEqual[NULL]} && ${MagicNuke.NotEqual[NULL]}) {
        /varset Spell13 ${MagicNuke}
    } else {
        /varset Spell13 ${RootSpell}
    }

    /call WIZ_DefaultSelfBuffRotationConfig WIZ_Downtime_MODEMAGIC_Rotation
    /call WIZ_DefaultDPSRotationConfig WIZ_DPS_MODEMAGIC_Rotation

/return 


|-----------------------------------------------------------------------------
|- SUB - fireSpellConfig - Configure Spell Gems for Magic Wizard Type
|-----------------------------------------------------------------------------
Sub WIZ_ModeConfigMODENOONE

    /if (${FireClaw.Equal[NULL]} && ${IceClaw.NotEqual[NULL]}) {
        /varset FireClaw ${IceClaw}
        /varset Spell1 ${IceClaw}
    } else /if (${FireClaw.Equal[NULL]} && ${StunSpell.NotEqual[NULL]}) {
        /varset FireClaw ${StunSpell}
        /varset Spell1 ${StunSpell}
    } else {
        /varset Spell1 ${FireClaw}
    }
 
    /if (${FireEtherealNuke.Equal[NULL]} && ${FireNuke.NotEqual[NULL]}) {
        /varset Spell2 ${FireNuke}
    } else {
        /varset Spell2 ${FireEtherealNuke}
    } 

    |- If for some reason you Do not have Dissodent flame etc.. Load a stun
    /if (${DichoSpell.NotEqual[NULL]}) {
        /varset Spell3 ${DichoSpell}
    } else {
        /varset Spell3 ${MagicNuke}
    }    

    /if (${FuseNuke.Equal[NULL]} && ${IceNuke.NotEqual[NULL]}) {
        /varset Spell4 ${IceNuke}
    } else {
        /varset Spell4 ${FuseNuke}
    }     
    
    /if (${TwincastSpell.Equal[NULL]} && ${FireClaw.NotEqual[${StunSpell}]}) {
        /varset Spell5 ${StunSpell}
    } else /if (${TwincastSpell.Equal[NULL]} && ${FireClaw.Equal[${StunSpell}]} && ${SnareSpell.NotEqual[NULL]}) {
        /varset Spell5 ${SnareSpell}
    } else /if (${TwincastSpell.Equal[NULL]} && ${FireClaw.Equal[${StunSpell}]} && ${RootSpell.NotEqual[NULL]}) {
        /varset Spell5 ${RootSpell}
    } else {
        /varset Spell5 ${TwincastSpell}
    }    
    
    |- Check for Gambit version first, if not there use regular harvest.
    /if (${GambitSpell.NotEqual[NULL]}) {
        /varset Spell6 ${GambitSpell}
    } else {
        /varset Spell6 ${HarvestSpell}
    }

    |- If you do not have Vortex (debuff nuke) load a fast cast nuke
    |- Does not conflict with fastcast load above, because you cannot obtain 11 spell gems before level 84
    /if (${VortexNuke.NotEqual[NULL]}) {
        /varset Spell7 ${VortexNuke}
    } else {
        /varset Spell7 ${FastMagicNuke}
    }
    
    /varset Spell8 ${JoltSpell}

    | Use our Summon Sword Pet if we do not have cold ethereal nuke yet
    /if (${Me.Level}<79 || ${IceEtherealNuke.Equal[NULL]}) {
        /varset Spell9 ${PetSpell}
    } else {
        /varset Spell9 ${IceEtherealNuke}
    }       

    /varset Spell10 ${FireRainLureNuke}
    /varset Spell11 ${ChaosNuke}

    /if (${FuseNuke.NotEqual[${FireNuke}]} && ${CloudburstNuke.Equal[NULL]}) {
        /varset Spell12 ${FireNuke}
    } else {
        /varset Spell12 ${CloudburstNuke}
    }
    
    |- Check to see if fire ice or magic nuke are not used yet
    /if ( ${FireNuke.NotEqual[${FireClaw}]} && ${FireNuke.NotEqual[NULL]} ) {
        /varset Spell13 ${FireNuke}
    } else /if ( ${IceNuke.NotEqual[${FuseNuke}]} && ${IceNuke.NotEqual[NULL]} ) {
        /varset Spell13 ${IceNuke}
    } else /if ( ${DichoSpell.NotEqual[NULL]} && ${MagicNuke.NotEqual[NULL]}) {
        /varset Spell13 ${MagicNuke}
    } else {
        /varset Spell13 ${RootSpell}
    }
    
    | DPS Section
    |- Aggro Management
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "A Hole in Space" AA           ${Parse[0,"( (${Me.PctAggro}>99 && ${Target.AggroHolder.CleanName.Equal[${Me.CleanName}]}) )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "Mind Crash" AA                ${Parse[0,"( (${Me.PctAggro}>85) )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "Concussion" AA                ${Parse[0,"( (${Me.PctAggro}>${JoltAtAggro[SETTINGVAL]}) )"]}    
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${JoltSpell}" Spell           ${Parse[0,"( (${Me.PctAggro}>${JoltAtAggro[SETTINGVAL]}) )"]}
    
    |- Mana Management
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${GambitSpell}" Spell ${Parse[0,"( ${Me.PctMana}<${ModRodManaPct[SETTINGVAL]} )"]}


    |- AA Burn Section
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "Arcane Whisper" AA            ${Parse[0,"( BURNCHECK && ${Target.PctHPs}>10 )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "Silent Casting" AA            ${Parse[0,"( BURNCHECK )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "Arcane Destruction" AA        ${Parse[0,"( !${Me.Song[Frenzied Devastation].ID} && BURNCHECK )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "Arcane Fury" AA               ${Parse[0,"( (BURNCHECK && !${Me.Song[Chromatic Haze].ID} && !${Me.Song[Gift of Chromatic Haze].ID} && (${Me.Song[Arcane Destruction].ID} || ${Me.Song[Frenzied Devastation].ID})))"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "Improved Twincast" AA         ${Parse[0,"( (BURNCHECK && !${Me.Buff[Twincast].ID}) )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "Mana Burn" AA                 ${Parse[0,"( (BURNCHECK && ${Target.BuffsPopulated} && !${Target.Buff[Mana Burn].ID}) && ${DoManaBurn[SETTINGVAL]} )"]}
    
    |- Cast with GOM Proc
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${FuseNuke}" Spell            ${Parse[0,"( DETGOMCHECK )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${FireEtherealNuke}" Spell    ${Parse[0,"( DETGOMCHECK )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${IceEtherealNuke}" Spell     ${Parse[0,"( DETGOMCHECK )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${DichoSpell}" Spell          ${Parse[0,"( DETGOMCHECK )"]}
    |- Cast with Gambit buff
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${CloudburstNuke}" Spell      ${Parse[0,"( ${Me.Song[${GambitSpell}].ID} || ${Me.Song[Evoker's Synergy I].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${WildNuke}" Spell            ${Parse[0,"( ${Me.Song[${GambitSpell}].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${ChaosNuke}" Spell           ${Parse[0,"( ${Me.Song[${GambitSpell}].ID} )"]}
    |- Cast Big nukes first, until low mana
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${TwincastSpell}" Spell       ${Parse[0,"( !${Me.Buff[Twincast].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${VortexNuke}" Spell          ${Parse[0,"( (${Target.BuffsPopulated} && !${Target.Buff[${VortexNuke}].ID}) )"]}
    
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${DichoSpell}" Spell          ${Parse[0,"( (!${Me.Song[${GambitSpell}].ID}) && (!${Me.Buff[Twincast].ID}) && (!${Me.Buff[Improved Twincast].ID}) )"]} 
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${FireClaw}" Spell            ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]}) "]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${FuseNuke}" Spell            ${Parse[0,"( !${Me.Song[${GambitSpell}].ID} && !${Me.SpellReady[${FireClaw}]} )"]}
    
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${FireNuke}" Spell            ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} && !${Me.Song[${GambitSpell}].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${IceNuke}" Spell             ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} && !${Me.Song[${GambitSpell}].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${MagicNuke}" Spell           ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} && !${Me.Song[${GambitSpell}].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "${FastMagicNuke}" Spell          ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} )"]}

    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "Force of Flame" AA            ${Parse[0,"( ${WeaveAANukes[SETTINGVAL]} && ${Me.SpellInCooldown} && !${RG_AAReady[Force of Ice]} && !${RG_AAReady[Force of Will]} )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "Force of Ice" AA              ${Parse[0,"( ${WeaveAANukes[SETTINGVAL]} && ${Me.SpellInCooldown} && !${RG_AAReady[Force of Flame]} )"]}
    /call AddToRotation "WIZ_DPS_MODENOONE_Rotation" "Force of Will" AA             ${Parse[0,"( ${WeaveAANukes[SETTINGVAL]} && ${Me.SpellInCooldown} && !${RG_AAReady[Force of Flame]} && !${RG_AAReady[Force of Ice]} )"]}

    /call WIZ_DefaultSelfBuffRotationConfig WIZ_Downtime_MODENOONE_Rotation
    |/call WIZ_DefaultDPSRotationConfig WIZ_DPS_MODENOONE_Rotation

/return  
|-----------------------------------------------------------------------------
|- SUB - TLPSpellConfig - Configure Spell Gems for Magic Wizard Type
|-----------------------------------------------------------------------------
Sub WIZ_ModeConfigMODETLP
    | TLP  Spell bar uses 3 variables DoMagicNuke,DoFireNuke,DoIceNuke u can have all 3 on or selectively turn off a type if u want.
    |- First 3 Spells Stay The Same regardless of toggles Use the Settings to determine cast Via Conditions
    /if (!${DoLure[SETTINGVAL]}) {
        /varset Spell1 ${BigFireNuke}
    } else {
      /varset Spell1 ${FireLureNuke}  
    }

    /if (!${DoLure[SETTINGVAL]}) {
        /varset Spell2 ${BigIceNuke}
    } else {
        /varset Spell2 ${IceLureNuke}
    }   

    /if (!${DoLure[SETTINGVAL]}) {
        /varset Spell3 ${BigMagicNuke}
    } else {
        /varset Spell3 ${MagicLureNuke}
    }   
    | Gems 4,5,6 Are Set to Fast Draught Based Spells for Filling in The gap if our Big Nukes are on CD
    /varset Spell4 ${FastFireNuke}
    /varset Spell5 ${FastIceNuke}
    /varset Spell6 ${FastMagicNuke}

    | /varset Spell7 ${JoltSpell}
    | - For Gem 7 Default is FireRain, Ice Rain Secondary. if Lures are on will be a Fire Lure Rain. Or ice Rain.
    /if ( ${DoLure[SETTINGVAL]} && ${DoFireNuke[SETTINGVAL]} ) {
        /varset Spell7 ${FireRainLureNuke}
    } else /if (${DoFireNuke[SETTINGVAL]}) {
        /varset Spell7 ${FireRainNuke}
    } else {
        /varset Spell7 ${IceRainNuke}
    }
	/varset Spell8 ${HarvestSpell}
    | - Spell 9 is used as a Hotswap gem for Short Buffs etc. so not memmed
        /varset Spell9 Null

    | DPS Section
    |- Aggro Management
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "Mind Crash" AA                ${Parse[0,"(  ${Me.TargetOfTarget.ID} == ${Me.ID} )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${JoltSpell}" Spell           ${Parse[0,"(  ${Me.TargetOfTarget.ID} == ${Me.ID} )"]}
    | - Lure Spells - Standard Burnchecks/mana Check Gate Plus a Do Lure Check.
    | - This Includes 3 SingleTarget lures. and 1 FireRain.
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${FireLureNuke}"        Spell     ${Parse[0,"( ${DoLure[SETTINGVAL]} && ${DoFireNuke[SETTINGVAL]} && ( MANACHECK || BURNCHECK) )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${FireRainLureNuke}"    Spell     ${Parse[0,"( ${DoLure[SETTINGVAL]} && ${DoFireNuke[SETTINGVAL]} && ${DoRain[SETTINGVAL]} && ${XAssist.XTFullHaterCount} < 2 && ( MANACHECK || BURNCHECK ))"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${IceLureNuke}"         Spell     ${Parse[0,"( ${DoLure[SETTINGVAL]} && ${DoIceNuke[SETTINGVAL]} && ( MANACHECK || BURNCHECK) )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${MagicLureNuke}"       Spell     ${Parse[0,"( ${DoLure[SETTINGVAL]} && ${DoMagicNuke[SETTINGVAL]} && ( MANACHECK || BURNCHECK) )"]}

    | - Wizzie Rotation TLP
    | - Rain Nuke Spells - Cast First Them Follow Up With Big Hard Nukes if On.
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${FireRainNuke}"   Spell     ${Parse[0,"( ${DoFireNuke[SETTINGVAL]} && ${DoRain[SETTINGVAL]} && ${XAssist.XTFullHaterCount} < 2 && ( MANACHECK || BURNCHECK ))"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${IceRainNuke}"    Spell     ${Parse[0,"( ${DoIceNuke[SETTINGVAL]} && ${DoRain[SETTINGVAL]} && ${XAssist.XTFullHaterCount} < 2 && ( MANACHECK || BURNCHECK ))"]}
  
    | - Big Nuke Spells - Gated by a BurnCheck with a built in 30% Mana Reserve using Manatonuke and due to long cast times a Mob life Check of 50% or more.
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${BigMagicNuke}"  Spell         ${Parse[0,"( ${Spawn[${autotargetid}].PctHPs} > ${StopNukeAt[SETTINGVAL]} && ${DoMagicNuke[SETTINGVAL]} && ( MANACHECK || BURNCHECK ))"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${BigFireNuke}"   Spell         ${Parse[0,"( ${Spawn[${autotargetid}].PctHPs} > ${StopNukeAt[SETTINGVAL]} && ${DoFireNuke[SETTINGVAL]}  && ( MANACHECK || BURNCHECK ))"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${BigIceNuke}"    Spell         ${Parse[0,"( ${Spawn[${autotargetid}].PctHPs} > ${StopNukeAt[SETTINGVAL]} && ${DoIceNuke[SETTINGVAL]}   && ( MANACHECK || BURNCHECK ))"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "Harvest of Druzzil" AA         ${Parse[0,"( ${Me.PctMana}<${ModRodManaPct[SETTINGVAL]} && ${RG_AAReady[Harvest of Druzzil]} )"]} 
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${HarvestSpell}" Spell         ${Parse[0,"( ${Me.PctMana}<${ModRodManaPct[SETTINGVAL]} && ${Me.SpellReady[${HarvestSpell}]} )"]} 
    
    | - Concussion every round to avoid aggro
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${JoltSpell}" Spell           ${Parse[0,"(  TRUE)"]}
    
    | - Fast Nuke spells - Gated by a BurnCheck with a built in 30% Mana Reserve using Manatonuke 
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${FastFireNuke}"   Spell        ${Parse[0,"( !${DoLure[SETTINGVAL]} && ${DoFireNuke[SETTINGVAL]} && ( MANACHECK || BURNCHECK) )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${FastIceNuke}"    Spell        ${Parse[0,"( !${DoLure[SETTINGVAL]} && ${DoIceNuke[SETTINGVAL]} && ( MANACHECK || BURNCHECK) )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${FastMagicNuke}"  Spell        ${Parse[0,"( !${DoLure[SETTINGVAL]} && ${DoMagicNuke[SETTINGVAL]} && ( MANACHECK || BURNCHECK) )"]}

    | - Wizzie Burn Mode Rotation TLP - growing as My Wizzie Grows P:)    
    /call AddToRotation "WIZ_BURN_MODETLP_Rotation" "Mana Burn" AA                   ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && ${Target.BuffsPopulated} && !${Target.Buff[Mana Burn].ID}  && ${DoManaBurn[SETTINGVAL]} && ( ${Target.Named} || ${SpawnMaster.HasTarget} ) )"]}
    /call AddToRotation "WIZ_BURN_MODETLP_Rotation" "Call of Xuzl" AA                   ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ( ${Target.Named} || ${SpawnMaster.HasTarget} ) )"]}
    

   |**
    |- AA Burn Section
    /call AddToRotation "WIZ_BURN_MODETLP_Rotation" "Arcane Destruction" AA          ${Parse[0,"( !${Me.Song[Frenzied Devastation].ID} && BURNCHECK )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "Arcane Whisper" AA            ${Parse[0,"( BURNCHECK )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "Silent Casting" AA            ${Parse[0,"( BURNCHECK )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "Arcane Fury" AA               ${Parse[0,"( (BURNCHECK && !${Me.Song[Chromatic Haze].ID} && !${Me.Song[Gift of Chromatic Haze].ID} && (${Me.Song[Arcane Destruction].ID} || ${Me.Song[Frenzied Devastation].ID})))"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "Improved Twincast" AA         ${Parse[0,"( (BURNCHECK && !${Me.Buff[Twincast].ID}) )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "Mana Burn" AA                 ${Parse[0,"( (( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && ${Target.BuffsPopulated} && !${Target.Buff[Mana Burn].ID}) && ${DoManaBurn[SETTINGVAL]} && ( ${Target.Named} || (${SpawnMaster.HasTarget} ) )"]}
    
    |- Cast with Gambit buff
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${CloudburstNuke}" Spell      ${Parse[0,"( ${Me.Song[${GambitSpell}].ID} || ${Me.Song[Evoker's Synergy I].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${WildNuke}" Spell            ${Parse[0,"( ${Me.Song[${GambitSpell}].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${ChaosNuke}" Spell           ${Parse[0,"( ${Me.Song[${GambitSpell}].ID} )"]}
    |- Cast Big nukes first, until low mana
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${TwincastSpell}" Spell       ${Parse[0,"( !${Me.Buff[Twincast].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${VortexNuke}" Spell          ${Parse[0,"( (${Target.BuffsPopulated} && !${Target.Buff[${VortexNuke}].ID}) )"]}
    
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${DichoSpell}" Spell          ${Parse[0,"( (!${Me.Song[${GambitSpell}].ID}) && (!${Me.Buff[Twincast].ID}) && (!${Me.Buff[Improved Twincast].ID}) )"]} 
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${FireClaw}" Spell            ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]}) "]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${FuseNuke}" Spell            ${Parse[0,"( !${Me.Song[${GambitSpell}].ID} && !${Me.SpellReady[${FireClaw}]} )"]}
    
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${FireNuke}" Spell            ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} && !${Me.Song[${GambitSpell}].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${IceNuke}" Spell             ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} && !${Me.Song[${GambitSpell}].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${MagicNuke}" Spell           ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} && !${Me.Song[${GambitSpell}].ID} )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "${FastMagicNuke}" Spell           ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} )"]}

    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "Force of Flame" AA            ${Parse[0,"( ${WeaveAANukes[SETTINGVAL]} && ${Me.SpellInCooldown} && !${RG_AAReady[Force of Ice]} && !${RG_AAReady[Force of Will]} )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "Force of Ice" AA              ${Parse[0,"( ${WeaveAANukes[SETTINGVAL]} && ${Me.SpellInCooldown} && !${RG_AAReady[Force of Flame]} )"]}
    /call AddToRotation "WIZ_DPS_MODETLP_Rotation" "Force of Will" AA             ${Parse[0,"( ${WeaveAANukes[SETTINGVAL]} && ${Me.SpellInCooldown} && !${RG_AAReady[Force of Flame]} && !${RG_AAReady[Force of Ice]} )"]}

    |/call WIZ_DefaultDPSRotationConfig WIZ_DPS_MODETLP_Rotation
    **|
    /call WIZ_DefaultSelfBuffRotationConfig WIZ_Downtime_MODETLP_Rotation
    
/return  

Sub WIZ_DefaultSelfBuffRotationConfig(string rotation_name)
    |- Buff Rotations
    /if (${Spell[${SelfHPBuff}].Level}>${Spell[${Me.AltAbility[Etherealist's Unity].Spell.Trigger[1].BaseName}].Level}) {
        /call AddToRotation "${rotation_name}" "${SelfHPBuff}" Spell    ${Parse[0,"( SELFBUFFCHECK )"]}
        } else {    
        /call AddToRotation "${rotation_name}" "Etherealist's Unity" AA ${Parse[0,"( SELFBUFFAACHECK )"]} 
    }
    
    /call AddToRotation "${rotation_name}" "${SelfRune1}" Spell        ${Parse[0,"( (!${Me.Buff[${Spell[${SelfRune1}].BaseName}].ID}) && ${Spell[${SelfRune1}].Stacks} )"]}
    /if (${Spell[${FamiliarBuff}].Level}>${Me.AltAbility[Improved Familiar].MinLevel}) {
        /call AddToRotation "${rotation_name}" "${FamiliarBuff}" Spell     ${Parse[0,"( !${Me.Buff[${Spell[${FamiliarBuff}].BaseName}].ID} )"]}
        } else {
        /call AddToRotation "${rotation_name}" "Improved Familiar"   AA      ${Parse[0,"( SELFBUFFAACHECK )"]}
    }
    |- Spell Map for Mana checks (not including gambit since that is handled during dps)
    /call AddToRotation "${rotation_name}" "Harvest of Druzzil" AA         ${Parse[0,"( ${Me.PctMana}<${ModRodManaPct[SETTINGVAL]} && ${RG_AAReady[Harvest of Druzzil]} )"]} 
    /call AddToRotation "${rotation_name}" "${HarvestSpell}" Spell         ${Parse[0,"( ${Me.PctMana}<${ModRodManaPct[SETTINGVAL]} && ${Me.SpellReady[${HarvestSpell}]} )"]} 
    /call AddToRotation "${rotation_name}" "${FindItem[${Me.Inventory[Chest].Name}]}" Item         ${Parse[0,"( ${DoChestClick[SETTINGVAL]} && ${Spell[${FindItem[${Me.Inventory[Chest].Name}].Spell}].Stacks} && (!${FindItem[${Me.Inventory[Chest].Name}].TimerReady}) )"]} 
    /call AddToRotation "${rotation_name}" "${FindItem[${ClarityPotion}].Name}" Item  ${Parse[0,"( ${Spell[${FindItem[${ClarityPotion}].Spell}].Stacks} && (!${Me.Buff[${Spell[${FindItem[Distillate of Clarity].Spell}].Name}].ID}) )"]}
    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
/return TRUE

Sub WIZ_DefaultDPSRotationConfig(string rotation_name)
    /call AddToRotation "${rotation_name}" "Etherealist's Unity" AA ${Parse[0,"( SELFBUFFAACHECK )"]} 
    |- Aggro Management
    /call AddToRotation "${rotation_name}" "A Hole in Space" AA           ${Parse[0,"( (${Me.PctAggro}>99 && ${Target.AggroHolder.CleanName.Equal[${Me.CleanName}]}) )"]}
    /call AddToRotation "${rotation_name}" "Mind Crash" AA                ${Parse[0,"( (${Me.PctAggro}>85) )"]}
    /call AddToRotation "${rotation_name}" "Concussion" AA                ${Parse[0,"( (${Me.PctAggro}>${JoltAtAggro[SETTINGVAL]}) )"]}    
    /call AddToRotation "${rotation_name}" "${JoltSpell}" Spell           ${Parse[0,"( (${Me.PctAggro}>${JoltAtAggro[SETTINGVAL]}) )"]}
    /call AddToRotation "${rotation_name}" "${SelfRune1}" Spell           ${Parse[0,"( (!${Me.Buff[${Spell[${SelfRune1}].BaseName}].ID}) && ${Spell[${SelfRune1}].Stacks} )"]}
    
    |- Mana Management
    /call AddToRotation "${rotation_name}" "${GambitSpell}" Spell ${Parse[0,"( ${Me.PctMana}<${ModRodManaPct[SETTINGVAL]} )"]}


    |- AA Burn Section
    /call AddToRotation "${rotation_name}" "Arcane Whisper" AA            ${Parse[0,"( BURNCHECK && ${Target.PctHPs}>10 )"]}
    /call AddToRotation "${rotation_name}" "Silent Casting" AA            ${Parse[0,"( BURNCHECK )"]}
    /call AddToRotation "${rotation_name}" "Arcane Destruction" AA        ${Parse[0,"( !${Me.Song[Frenzied Devastation].ID} && BURNCHECK )"]}
    /call AddToRotation "${rotation_name}" "Arcane Fury" AA               ${Parse[0,"( (BURNCHECK && !${Me.Song[Chromatic Haze].ID} && !${Me.Song[Gift of Chromatic Haze].ID} && (${Me.Song[Arcane Destruction].ID} || ${Me.Song[Frenzied Devastation].ID})))"]}
    /call AddToRotation "${rotation_name}" "Improved Twincast" AA         ${Parse[0,"( (BURNCHECK && !${Me.Buff[Twincast].ID}) )"]}
    /call AddToRotation "${rotation_name}" "Mana Burn" AA                 ${Parse[0,"( (BURNCHECK && ${Target.BuffsPopulated} && !${Target.Buff[Mana Burn].ID}) && ${DoManaBurn[SETTINGVAL]} )"]}
    
    |- Cast with GOM Proc
    /call AddToRotation "${rotation_name}" "${FuseNuke}" Spell            ${Parse[0,"( DETGOMCHECK )"]}
    /call AddToRotation "${rotation_name}" "${FireEtherealNuke}" Spell    ${Parse[0,"( DETGOMCHECK )"]}
    /call AddToRotation "${rotation_name}" "${IceEtherealNuke}" Spell     ${Parse[0,"( DETGOMCHECK )"]}
    /call AddToRotation "${rotation_name}" "${DichoSpell}" Spell          ${Parse[0,"( DETGOMCHECK )"]}
    |- Cast with Gambit buff
    /call AddToRotation "${rotation_name}" "${CloudburstNuke}" Spell      ${Parse[0,"( ${Me.Song[${GambitSpell}].ID} || ${Me.Song[Evoker's Synergy I].ID} )"]}
    /call AddToRotation "${rotation_name}" "${WildNuke}" Spell            ${Parse[0,"( ${Me.Song[${GambitSpell}].ID} )"]}
    /call AddToRotation "${rotation_name}" "${ChaosNuke}" Spell           ${Parse[0,"( ${Me.Song[${GambitSpell}].ID} )"]}
    |- Cast Big nukes first, until low mana
    /call AddToRotation "${rotation_name}" "${VortexNuke}" Spell          ${Parse[0,"( ${Target.BuffsPopulated} && !${Target.Buff[${VortexNuke}].ID} )"]}

    /call AddToRotation "${rotation_name}" "${VortexNuke}" Spell          ${Parse[0,"( ${Target.BuffsPopulated} && !${Target.Buff[${VortexNuke}].ID} )"]}
    /call AddToRotation "${rotation_name}" "${TwincastSpell}" Spell       ${Parse[0,"( !${Me.Buff[Twincast].ID} )"]}
    /call AddToRotation "${rotation_name}" "${DichoSpell}" Spell          ${Parse[0,"( (!${Me.Song[${GambitSpell}].ID}) && (!${Me.Buff[Twincast].ID}) && (!${Me.Buff[Improved Twincast].ID}) )"]} 
    /call AddToRotation "${rotation_name}" "${FireClaw}" Spell            ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]}) "]}
    /call AddToRotation "${rotation_name}" "${FuseNuke}" Spell            ${Parse[0,"( !${Me.Song[${GambitSpell}].ID} && !${Me.SpellReady[${FireClaw}]} )"]}
    
    /call AddToRotation "${rotation_name}" "${FireNuke}" Spell            ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} && !${Me.Song[${GambitSpell}].ID} )"]}
    /call AddToRotation "${rotation_name}" "${AllianceSpell}" Spell       ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} )"]}
    /call AddToRotation "${rotation_name}" "${PetSpell}" Spell            ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} )"]}
    /call AddToRotation "${rotation_name}" "${StunSpell}" Spell           ${Parse[0,"( ${Me.PctMana} > ${NukeUntilMana[SETTINGVAL]} )"]}    
    /call AddToRotation "${rotation_name}" "Force of Flame" AA            ${Parse[0,"( ${WeaveAANukes[SETTINGVAL]} && ${Me.SpellInCooldown} && !${RG_AAReady[Force of Ice]} && !${RG_AAReady[Force of Will]} )"]}
    /call AddToRotation "${rotation_name}" "Force of Ice" AA              ${Parse[0,"( ${WeaveAANukes[SETTINGVAL]} && ${Me.SpellInCooldown} && !${RG_AAReady[Force of Flame]} )"]}
    /call AddToRotation "${rotation_name}" "Force of Will" AA             ${Parse[0,"( ${WeaveAANukes[SETTINGVAL]} && ${Me.SpellInCooldown} && !${RG_AAReady[Force of Flame]} && !${RG_AAReady[Force of Ice]} )"]}
    /call AddToRotation "${rotation_name}" "${FireEtherealNuke}" Spell    ${Parse[0,"( !${Me.Song[${GambitSpell}].ID} && ${Me.PctMana}>50 && !${Me.SpellReady[${FireClaw}]} )"]}




/return TRUE

Sub WIZ_Combat_Routine
    /if (${MedState} && (${Me.PctMana} < 10) ) /varset MedState 1
    /if (!${MedState} && (${Me.PctMana} > 95) ) /varset MedState 0
    /if ( DODPS && !${MedState} ) {
        /call Ordered_Rotation_Follow WIZ_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }
/return ${Macro.Return}

Sub WIZ_Downtime_Routine
    |- Call Self buffs
    /call FollowRotation  WIZ_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}
/return ${Macro.Return}

Sub WIZ_PullSetup
    /if (${RG_CanUseAA[Lower Element]}) {
		/call Pull_SetAbility "Lower Element" "AA"
    }
/return