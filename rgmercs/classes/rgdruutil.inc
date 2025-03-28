|- RGdruutil.inc - By DrWhompd
|- Automatic Druid "Merc"
|- Version 0.1
|- Updated: 03/25/2020
|- Credit: Toots, Noobhax0r, Maskoi, Ctaylor, Treehuggindruid. A lot of ideas were borrowed and modified from their macros
#define MODEHEAL 0
#define MODEDPS 99
#define MODEMANA 1
#define MODETLP 2
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub DRU_Setup
    /declare RGList_DRU            list outer 
    /call Thawmequeue_Setup
    |-Alliance Specific
    |-AllianceAvail is set to true if there are enough members in the group to use Alliance
    /declare AllianceAvail          int    outer 0
|- Items
    /call ItemSet_New Epic 

|-Spells
    /call AbilitySet_New Alliance
    /call AbilitySet_New FireAura
    /call AbilitySet_New IceAura
    /call AbilitySet_New HealingAura
    
    |- Heals
    /call AbilitySet_New SingleTgtCure
    /call AbilitySet_New GroupCure
    /call AbilitySet_New QuickHealSurge
    /call AbilitySet_New QuickHeal
    /call AbilitySet_New LongHeal
    /call AbilitySet_New QuickGroupHeal
    /call AbilitySet_New LongGroupHeal
    /call AbilitySet_New PromHeal
    
    |- Combat Spells
    /call AbilitySet_New FrostDebuff
    /call AbilitySet_New RoDebuff
    /call AbilitySet_New RoDebuffAE
    /call AbilitySet_New IceBreathDebuff
    /call AbilitySet_New SkinDebuff
    /call AbilitySet_New ReptileCombatInnate
    /call AbilitySet_New NaturesWrathDOT
    /call AbilitySet_New HordeDOT
    /call AbilitySet_New SunDOT
    /call AbilitySet_New SunrayDOT
    /call AbilitySet_New MoonBeamDOT
    /call AbilitySet_New RemoteMoonDD
    /call AbilitySet_New RemoteSunDD
    /call AbilitySet_New RoarDD
    /call AbilitySet_New QuickRoarDD
    /call AbilitySet_New DichoSpell
    /call AbilitySet_New WinterFireDD
    /call AbilitySet_New ChillDOT
    /call AbilitySet_New RootSpells
    /call AbilitySet_New SnareSpells
    /call AbilitySet_New TwincastNuke
    /call AbilitySet_New IceNuke
    /call AbilitySet_New IceRainNuke

    |- MODEMANA Changes listed below
	|- Added Spell Lines
	/call AbilitySet_New ShroomPet
	/call AbilitySet_New IceDD
	|- Changed Spell Lines
	/call AbilitySet_New RemoteDD
	/call AbilitySet_New SunMoonDot   
    
    |- Self Buffs
    /call AbilitySet_New SelfShield
    /call AbilitySet_New SelfManaRegen
    
    |- Buffs
    /call AbilitySet_New HPTypeOneGroup
    /call AbilitySet_New TempHPBuff
    /call AbilitySet_New GroupRegenBuff
    /call AbilitySet_New AtkBuff
    /call AbilitySet_New GroupDmgShield
    /call AbilitySet_New MoveSpells
    /call AbilitySet_New ManaBear
 |   /call AbilitySet_New SingleDS

    /declare TwinCast        string outer ${Spell[Twincast].RankName}

|- Rotations
|- Mode 0 Rotations (HEAL)
    /call Ordered_Rotation_New DRU_DPS_MODEHEAL_Rotation
    /call Ordered_Rotation_New DRU_Downtime_MODEHEAL_Rotation
    /call Ordered_Rotation_New DRU_Burn_MODEHEAL_Rotation
    /call Ordered_Rotation_New DRU_Debuff_MODEHEAL_Rotation
| - Mode 1 Rotations (MANA) - DPS
    /call Ordered_Rotation_New DRU_DPS_MODEMANA_Rotation
    /call Ordered_Rotation_New DRU_Downtime_MODEMANA_Rotation
    /call Ordered_Rotation_New DRU_Burn_MODEMANA_Rotation
    /call Ordered_Rotation_New DRU_Debuff_MODEMANA_Rotation
| - Mode 2 Rotations (TLP)
    /call Ordered_Rotation_New DRU_DPS_MODETLP_Rotation
    /call Ordered_Rotation_New DRU_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New DRU_Burn_MODETLP_Rotation
    /call Ordered_Rotation_New DRU_Debuff_MODETLP_Rotation

    |- Initialize Cure Observers
    /call Cure_Init

|- Misc Variables
	/declare Spell1				string outer NULL 
	/declare Spell2				string outer NULL
	/declare Spell3				string outer NULL
	/declare Spell4				string outer NULL
	/declare Spell5				string outer NULL
	/declare Spell6				string outer NULL
	/declare Spell7				string outer NULL
	/declare Spell8				string outer NULL
	/declare Spell9				string outer NULL
	/declare Spell10			string outer NULL
	/declare Spell11			string outer NULL
	/declare Spell12			string outer NULL
	/declare Spell13			string outer NULL	
	
|-Config Options
	/call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = Heal, 1 = DPS 2 = TLP
    /call RGLoadSetting DRU AutoDebuffAt       99 Debuff "%HP to debuff Mobs." 1
    /call RGLoadSetting DRU DoDots             1 Combat "Set 0/1 to use DOT spells."
    /call RGLoadSetting DRU HPStopDOT          50 Combat "%HP of Mob below which you will not DOT."
    /call RGLoadSetting DRU DoHeals            1 Healing "Set 0/1 to heal the group. Checked in the main loop."
    /call RGLoadSetting DRU DoCure             0 Healing "Set 0/1 to use the DanNet observer based cure system."
    /call RGLoadSetting DRU MainHealPoint      85 Healing "%Health of Target to cast slow heal spells & %health to start healing -- setting too low will stop healing." 1
    /call RGLoadSetting DRU SlowHealPoint      85 Healing "%Health of Target to cast slow heal spells & %health to start healing -- setting too low will stop healing." 1
    /call RGLoadSetting DRU GroupHealPoint     70 Healing "%Health of Target to cast group heal spels." 1
    /call RGLoadSetting DRU GroupInjureCnt      3 Healing "Number of group members to be injured before using a group heal spell." 1
    /call RGLoadSetting DRU QuickHealPoint     50 Healing "%Health of Target to cast quick heal spells." 1
    /call RGLoadSetting DRU BigHealPoint       35 healing "%Health of Target to cast Oh Shit! heals." 1
    /call RGLoadSetting DRU UseBattleRez       0 Healing "Set 0/1 to cast 0% XP Battle Rez"
    /call RGLoadSetting DRU ChestItemName      "FILLME" Item "Name of Chest Item Clicky to use"
    /call RGLoadSetting DRU DoSnare            0 Debuff "Set 0/1 to use Snare spells on mobs when they're below 50% HP."
    /call RGLoadSetting DRU DoRunSpeed        1 Options "Set 0/1 to enable the use of the DRU runspeed buffs."
    /call RGLoadSetting DRU DoProm             1 Healing "Turn on Maintaining a promised heal always or not"
    /call RGLoadSetting DRU NukePct            90 Healing "Determines what % to begin using Nukes or Heal Nukes of Anykind."
    /call RGLoadSetting DRU DoNukes            1 Combat "Turns Off Druid Heal Nukes IE RemoteDD IceRend etc.."
    | - Druid Do Fire acts as A Toggle between Fire and Ice based Nuking largely because using both is Not really needed at this level 
    /call RGLoadSetting DRU DoFire         1 Combat " 1 = Fire 0 = Ice Acts as a Toggle"
    /call RGLoadSetting DRU Manatonuke         60 Combat "Requires We have this Much or More Mana to Nuke" 
    /call RGLoadSetting DRU DoRain 1 Combat "0/1 Turn rains on or Off"
|-Declare spell variables
	/declare GroupBuffRecast 		int outer 0
	/declare miscspellremem		string outer NULL
	/declare tempid						string outer NULL
	/declare spellrememtimer		timer outer 0
	/declare ReadyToCast	  		timer outer 0
	/declare groupbufftimer			timer outer 0
    /declare spellmisc 					int outer 8
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==5) /varset spellmisc 13
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==4) /varset spellmisc 12
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==3) /varset spellmisc 11
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==2) /varset spellmisc 10
	/if (${Me.AltAbility[Mnemonic Retention].Rank}==1) /varset spellmisc 9	

/return

|----------------------------------------------------------------------------
|- SUB: CheckSpells
|---------------------------------------------------------------------------- 
Sub DRU_SetupSkills
    /echo Choosing All Druid Spells - this may take a moment

    |- Items
    | - Epic 
    /call ItemSet_Add "Staff of Living Brambles" Epic
    /call ItemSet_Add "Staff of Everliving Brambles" Epic
    /call ItemSet_ChooseOuter Epic Epic

    |- Spell Series >= 87LVL Minimum
    /call AbilitySet_Add "Wildspark Aura" FireAura
    /call AbilitySet_Add "Wildblaze Aura" FireAura
    /call AbilitySet_Add "Wildfire Aura" FireAura
    /call AbilitySet_ChooseOuter FireAura FireAura
    
    | - Promised Heals Line Druid
    /call AbilitySet_Add "Promised Reknit"          PromHeal
    /call AbilitySet_Add "Promised Replenishment"   PromHeal
    /call AbilitySet_Add "Promised Revitalization"  PromHeal
    /call AbilitySet_Add "Promised Recovery"        PromHeal
    /call AbilitySet_Add "Promised Regeneration"    PromHeal
    /call AbilitySet_Add "Promised Rebirth"         PromHeal
    /call AbilitySet_Add "Promised Refreshment"     PromHeal
    /call AbilitySet_Add "Promised Revivification"  PromHeal
    /call AbilitySet_ChooseOuter PromHeal PromHeal

    | - Druid Twincast
    /call AbilitySet_Add "Sundew Blessing" TwincastNuke
    /call AbilitySet_Add "Sunrise Blessing" TwincastNuke
    /call AbilitySet_Add "Sunbreeze Blessing" TwincastNuke
    /call AbilitySet_Add "SunBeam Blessing" TwincastNuke
    /call AbilitySet_Add "SunFire Blessing" TwincastNuke
    /call AbilitySet_Add "SunFlash Blessing" TwincastNuke
    /call AbilitySet_Add "SunRake Blessing" TwincastNuke
    /call AbilitySet_Add "Sunwarmth Blessing" TwincastNuke
    /call AbilitySet_ChooseOuter TwincastNuke TwincastNuke

    |- Spell Series >= 88LVL Minimum -- Only Heroic Aura that will be used
    /call AbilitySet_Add "Icerend Aura" IceAura
    /call AbilitySet_Add "Frostreave Aura" IceAura
    /call AbilitySet_Add "Frostweave Aura" IceAura
    /call AbilitySet_Add "Frostone Aura" IceAura
    /call AbilitySet_Add "Frostcloak Aura" IceAura
    /call AbilitySet_Add "Frostfell Aura" IceAura
    /call AbilitySet_Add "Nightchill Aura" IceAura
    /call AbilitySet_ChooseOuter IceAura IceAura


    | - MoonBeam Dot
    /call AbilitySet_Add "Gelid Moonbeam" MoonBeamDOT
    /call AbilitySet_Add "Algid Moonbeam" MoonBeamDOT
    /call AbilitySet_Add "Frigid Moonbeam" MoonBeamDOT
    /call AbilitySet_Add "Argent Moonbeam" MoonBeamDOT
    /call AbilitySet_Add "Pearlescent Moonbeam" MoonBeamDOT
    /call AbilitySet_Add "Opaline Moonbeam" MoonBeamDOT
    /call AbilitySet_Add "Onyx Moonbeam" MoonBeamDOT
    /call AbilitySet_ChooseOuter MoonBeamDOT MoonBeamDOT
    
    |- Healing Aura >= 55
    /call AbilitySet_Add "Aura of Life" HealingAura
    /call AbilitySet_Add "Aura of the Grove" HealingAura
    /call AbilitySet_ChooseOuter HealingAura HealingAura
    
    |- Single Target Multi-Cure >= 84
    /call AbilitySet_Add "Expurgated Blood" SingleTgtCure
    /call AbilitySet_Add "Unblemished Blood" SingleTgtCure
    /call AbilitySet_Add "Cleansed Blood" SingleTgtCure
    /call AbilitySet_Add "Perfected Blood" SingleTgtCure
    /call AbilitySet_Add "Purged Blood" SingleTgtCure
    /call AbilitySet_Add "Purified Blood" SingleTgtCure
    /call AbilitySet_Add "Sanctified Blood" SingleTgtCure
    /call AbilitySet_ChooseOuter SingleTgtCure SingleTgtCure
    
    |- Group Multi-Cure >=91
    /call AbilitySet_Add "Wildtender's Breeze" GroupCure
    /call AbilitySet_Add "Copsetender's Breeze" GroupCure
    /call AbilitySet_Add "Bosquetender's Breeze" GroupCure
    /call AbilitySet_Add "Fawnwalker's Breeze" GroupCure
    /call AbilitySet_Add "Nightwhisper's Breeze" GroupCure
    /call AbilitySet_ChooseOuter GroupCure GroupCure
    
    |- Main Quick heal >=75
    /call AbilitySet_Add "Adrenaline Deluge" QuickHealSurge
    /call AbilitySet_Add "Adrenaline Barrage" QuickHealSurge
    /call AbilitySet_Add "Adrenaline Torrent" QuickHealSurge
    /call AbilitySet_Add "Adrenaline Rush" QuickHealSurge
    /call AbilitySet_Add "Adrenaline Flood" QuickHealSurge
    /call AbilitySet_Add "Adrenaline Blast" QuickHealSurge
    /call AbilitySet_Add "Adrenaline Burst" QuickHealSurge
    /call AbilitySet_Add "Adrenaline Swell" QuickHealSurge
    /call AbilitySet_Add "Adrenaline Surge" QuickHealSurge
    /call AbilitySet_Add "Adrenaline Spate" QuickHealSurge
    /call AbilitySet_ChooseOuter QuickHealSurge QuickHealSurge

    |- Backup Quick heal >= LVL90
    /call AbilitySet_Add "Rejuvenescence" QuickHeal
    /call AbilitySet_Add "Revitalization" QuickHeal
    /call AbilitySet_Add "Resurgence" QuickHeal
    /call AbilitySet_Add "Vivification" QuickHeal
    /call AbilitySet_Add "Invigoration" QuickHeal
    /call AbilitySet_Add "Rejuvilation" QuickHeal
    /call AbilitySet_Add "Sootheseance" QuickHeal
    /call AbilitySet_ChooseOuter QuickHeal QuickHeal

    |- Long Heal >= 1 -- skipped 10s cast heals.
    /call AbilitySet_Add "Clotavida" LongHeal
    /call AbilitySet_Add "Viridavida" LongHeal
    /call AbilitySet_Add "Curavida" LongHeal
    /call AbilitySet_Add "Panavida" LongHeal
    /call AbilitySet_Add "Sterivida" LongHeal
    /call AbilitySet_Add "Sanavida" LongHeal
    /call AbilitySet_Add "Benevida" LongHeal
    /call AbilitySet_Add "Granvida" LongHeal
    /call AbilitySet_Add "Puravida" LongHeal
    /call AbilitySet_Add "Pure Life" LongHeal
    /call AbilitySet_Add "Chlorotrope" LongHeal
    /call AbilitySet_Add "Sylvan Infusion" LongHeal
    /call AbilitySet_Add "Nature's Infusion" LongHeal
    /call AbilitySet_Add "Nature's Touch" LongHeal
    /call AbilitySet_Add "Chloroblast" LongHeal
    /call AbilitySet_Add "Forest's Renewal" LongHeal
    /call AbilitySet_Add "Superior Healing" LongHeal
    /call AbilitySet_Add "Nature's Renewal" LongHeal
    /call AbilitySet_Add "Healing Water" LongHeal
    /call AbilitySet_Add "Greater Healing" LongHeal
    /call AbilitySet_Add "Healing" LongHeal
    /call AbilitySet_Add "Light Healing" LongHeal
    /call AbilitySet_Add "Minor Healing" LongHeal
    /call AbilitySet_ChooseOuter LongHeal1 LongHeal
    /call AbilitySet_ChooseOuter LongHeal2 LongHeal "${LongHeal1}"
    
    |- Quick Group heal >= LVL78
    /call AbilitySet_Add "Survival of the Favored" QuickGroupHeal
    /call AbilitySet_Add "Survival of the Auspicious" QuickGroupHeal
    /call AbilitySet_Add "Survival of the Serendipitous" QuickGroupHeal
    /call AbilitySet_Add "Survival of the Fortuitous" QuickGroupHeal
    /call AbilitySet_Add "Survival of the Prosperous" QuickGroupHeal
    /call AbilitySet_Add "Survival of the Propitious" QuickGroupHeal
    /call AbilitySet_Add "Survival of the Felicitous" QuickGroupHeal
    /call AbilitySet_Add "Survival of the Fittest" QuickGroupHeal
    /call AbilitySet_Add "Survival of the Unrelenting" QuickGroupHeal
    /call AbilitySet_ChooseOuter QuickGroupHeal QuickGroupHeal
    
    |- Long Group heal >= LVL 70
    /call AbilitySet_Add "Lunalesce" LongGroupHeal
    /call AbilitySet_Add "Lunasalve" LongGroupHeal
    /call AbilitySet_Add "Lunasoothe" LongGroupHeal
    /call AbilitySet_Add "Lunassuage" LongGroupHeal
    /call AbilitySet_Add "Lunalleviation" LongGroupHeal
    /call AbilitySet_Add "Lunamelioration" LongGroupHeal
    /call AbilitySet_Add "Lunulation" LongGroupHeal
    /call AbilitySet_Add "Crescentbloom" LongGroupHeal
    /call AbilitySet_Add "Lunarlight" LongGroupHeal
    /call AbilitySet_Add "Moonshadow" LongGroupHeal
    /call AbilitySet_Add "Lunarush" LongGroupHeal
    /call AbilitySet_ChooseOuter LongGroupHeal LongGroupHeal
    
    |- Frost Debuff Series -- >= 74LVL -- On Bar
    /call AbilitySet_Add "Restless Frost" FrostDebuff
    /call AbilitySet_Add "Glistening Frost" FrostDebuff
    /call AbilitySet_Add "Moonbright Frost" FrostDebuff
    /call AbilitySet_Add "Lustrous Frost" FrostDebuff
    /call AbilitySet_Add "Silver Frost" FrostDebuff
    /call AbilitySet_Add "Argent Frost" FrostDebuff
    /call AbilitySet_Add "Blanched Frost" FrostDebuff
    /call AbilitySet_Add "Gelid Frost" FrostDebuff
    /call AbilitySet_Add "Hoar Frost" FrostDebuff
    /call AbilitySet_Add "Primal Frost" FrostDebuff
    /call AbilitySet_ChooseOuter FrostDebuff FrostDebuff
    
    |- Ro Debuff Series -- >= 37LVL -- AA Starts at LVL (Single Target) -- On Bar Until AA
    /call AbilitySet_Add "Clasp of Ro" RoDebuff
    /call AbilitySet_Add "Cowl of Ro" RoDebuff
    /call AbilitySet_Add "Crush of Ro" RoDebuff
    /call AbilitySet_Add "Cowl of Ro" RoDebuff
    /call AbilitySet_Add "Clutch of Ro" RoDebuff
    /call AbilitySet_Add "Grip of Ro" RoDebuff
    /call AbilitySet_Add "Grasp of Ro" RoDebuff
    /call AbilitySet_Add "Sun's Corona" RoDebuff
    /call AbilitySet_Add "Ro's Illumination" RoDebuff
    /call AbilitySet_Add "Ro's Smoldering Disjunction" RoDebuff
    /call AbilitySet_Add "Fixation of Ro" RoDebuff
    /call AbilitySet_Add "Ro's Fiery Sundering" RoDebuff
    /call AbilitySet_Add "Cinch of Ro" RoDebuff
    /call AbilitySet_ChooseOuter RoDebuff RoDebuff
    
    |- Ro AE Debuff Series -- >= 97LVL -- AA Starts at LVL
    /call AbilitySet_Add "Glare of Ro" RoDebuffAE
    /call AbilitySet_Add "Gaze of Ro" RoDebuffAE
    /call AbilitySet_Add "Column of Ro" RoDebuffAE
    /call AbilitySet_Add "Pillar of Ro" RoDebuffAE
    /call AbilitySet_Add "Scrutiny of Ro" RoDebuffAE
    /call AbilitySet_ChooseOuter RoDebuffAE RoDebuffAE
    
    |- Ice Breath Series >= 63LVL -- On Bar
    /call AbilitySet_Add "Icerend Breath" IceBreathDebuff
    /call AbilitySet_Add "Frostreave Breath" IceBreathDebuff
    /call AbilitySet_Add "Blizzard Breath" IceBreathDebuff
    /call AbilitySet_Add "Frosthowl Breath" IceBreathDebuff
    /call AbilitySet_Add "Encompassing Breath" IceBreathDebuff
    /call AbilitySet_Add "Bracing Breath" IceBreathDebuff
    /call AbilitySet_Add "Coldwhisper Breath" IceBreathDebuff
    /call AbilitySet_Add "Chillvapor Breath" IceBreathDebuff
    /call AbilitySet_Add "Icefall Breath" IceBreathDebuff
    /call AbilitySet_Add "Glacier Breath" IceBreathDebuff
    /call AbilitySet_Add "E`ci's Frosty Breath" IceBreathDebuff
    /call AbilitySet_Add "Twilight Breath" IceBreathDebuff
    /call AbilitySet_ChooseOuter IceBreathDebuff IceBreathDebuff

    |- Skin Debuff Series >= 73LVL -- On Bar
    /call AbilitySet_Add "Skin to Sumac" SkinDebuff
    /call AbilitySet_Add "Skin to Seedlings" SkinDebuff
    /call AbilitySet_Add "Skin to Foliage" SkinDebuff
    /call AbilitySet_Add "Skin to Leaves" SkinDebuff
    /call AbilitySet_Add "Skin to Flora" SkinDebuff
    /call AbilitySet_Add "Skin to Mulch" SkinDebuff
    /call AbilitySet_Add "Skin to Vines" SkinDebuff
    /call AbilitySet_Add "Skin to Lichen" SkinDebuff
    /call AbilitySet_ChooseOuter SkinDebuff SkinDebuff
    
    |- Reptile Combat Innate >= 68LVL -- On Bar
    /call AbilitySet_Add "Defense of the Reptile" ReptileCombatInnate
    /call AbilitySet_Add "Guard of the Reptile" ReptileCombatInnate
    /call AbilitySet_Add "Pellicle of the Reptile" ReptileCombatInnate
    /call AbilitySet_Add "Husk of the Reptile" ReptileCombatInnate
    /call AbilitySet_Add "Hide of the Reptile" ReptileCombatInnate
    /call AbilitySet_Add "Shell of the Reptile" ReptileCombatInnate
    /call AbilitySet_Add "Carapace of the Reptile" ReptileCombatInnate
    /call AbilitySet_Add "Scales of the Reptile" ReptileCombatInnate
    /call AbilitySet_Add "Skin of the Reptile" ReptileCombatInnate
    /call AbilitySet_Add "Bulwark of the Reptile" ReptileCombatInnate
    /call AbilitySet_ChooseOuter ReptileCombatInnate ReptileCombatInnate
    
    |- Natures Wrath DOT Line >= 75LVL -- On Bar
    /call AbilitySet_Add "Nature's Fervid Wrath" NaturesWrathDOT
    /call AbilitySet_Add "Nature's Blistering Wrath" NaturesWrathDOT
    /call AbilitySet_Add "Nature's Fiery Wrath" NaturesWrathDOT
    /call AbilitySet_Add "Nature's Withering Wrath" NaturesWrathDOT
    /call AbilitySet_Add "Nature's Scorching Wrath" NaturesWrathDOT
    /call AbilitySet_Add "Nature's Incinerating Wrath" NaturesWrathDOT
    /call AbilitySet_Add "Nature's Searing Wrath" NaturesWrathDOT
    /call AbilitySet_Add "Nature's Burning Wrath" NaturesWrathDOT
    /call AbilitySet_Add "Nature's Blazing Wrath" NaturesWrathDOT
    /call AbilitySet_Add "Nature's Sweltering Wrath" NaturesWrathDOT
    /call AbilitySet_ChooseOuter NaturesWrathDOT NaturesWrathDOT
    
    |- Horde Dots >= 10LVL -- On Bar
    /call AbilitySet_Add "Horde of Duskwigs" HordeDOT
    /call AbilitySet_Add "Horde of Hyperboreads" HordeDOT
    /call AbilitySet_Add "Horde of Polybiads" HordeDOT
    /call AbilitySet_Add "Horde of Aculeids" HordeDOT
    /call AbilitySet_Add "Horde of Mutillids" HordeDOT
    /call AbilitySet_Add "Horde of Vespids" HordeDOT
    /call AbilitySet_Add "Horde of Scoriae" HordeDOT
    /call AbilitySet_Add "Horde of the Hive" HordeDOT
    /call AbilitySet_Add "Horde of Fireants" HordeDOT
    /call AbilitySet_Add "Swarm of Fireants" HordeDOT
    /call AbilitySet_Add "Wasp Swarm" HordeDOT
    /call AbilitySet_Add "Swarming Death" HordeDOT
    /call AbilitySet_Add "Winged Death" HordeDOT
    /call AbilitySet_Add "Drifting Death" HordeDOT
    /call AbilitySet_Add "Drones of Doom" HordeDOT
    /call AbilitySet_Add "Creeping Crud" HordeDOT
    /call AbilitySet_Add "Stinging Swarm" HordeDOT
    /call AbilitySet_ChooseOuter HordeDOT HordeDOT
    
    |- SUN Dot Line >= 49LVL -- On Bar
    /call AbilitySet_Add "Sunpyre" SunDOT
    /call AbilitySet_Add "Sunshock" SunDOT
    /call AbilitySet_Add "Sunflame" SunDOT
    /call AbilitySet_Add "Sunflash" SunDOT
    /call AbilitySet_Add "Sunblaze" SunDOT
    /call AbilitySet_Add "Sunscorch" SunDOT
    /call AbilitySet_Add "Sunbrand" SunDOT
    /call AbilitySet_Add "Sunsinge" SunDOT
    /call AbilitySet_Add "Sunsear" SunDOT
    /call AbilitySet_Add "Sunscorch" SunDOT
    /call AbilitySet_Add "Vengeance of the Sun" SunDOT
    /call AbilitySet_Add "Vengeance of Tunare" SunDOT
    /call AbilitySet_Add "Vengeance of Nature" SunDOT
    /call AbilitySet_Add "Vengeance of the Wild" SunDOT    
    /call AbilitySet_ChooseOuter SunDOT SunDOT
    
    |- SunrayDOT Line >= 1 LVL
    /call AbilitySet_Add "Tenebrous Sunray" SunrayDOT
    /call AbilitySet_Add "Erupting Sunray" SunrayDOT
    /call AbilitySet_Add "Overwhelming Sunray" SunrayDOT
    /call AbilitySet_Add "Consuming Sunray" SunrayDOT
    /call AbilitySet_Add "Incinerating Sunray" SunrayDOT
    /call AbilitySet_Add "Blazing Sunray" SunrayDOT
    /call AbilitySet_Add "Scorching Sunray" SunrayDOT
    /call AbilitySet_Add "Withering Sunray" SunrayDOT
    /call AbilitySet_Add "Torrid Sunray" SunrayDOT
    /call AbilitySet_Add "Blistering Sunray" SunrayDOT
    /call AbilitySet_Add "Immolation of the Sun" SunrayDOT
    /call AbilitySet_Add "Sylvan Embers" SunrayDOT
    /call AbilitySet_Add "Immolation of Ro" SunrayDOT
    /call AbilitySet_Add "Breath of Ro" SunrayDOT
    /call AbilitySet_Add "Immolate" SunrayDOT
    /call AbilitySet_Add "Flame Lick" SunrayDOT
    /call AbilitySet_ChooseOuter SunrayDOT SunrayDOT
    
    
    |- Remote Sun DD >= 83LVL
    /call AbilitySet_Add "Remote Sunbolt" RemoteSunDD
    /call AbilitySet_Add "Remote Sunshock" RemoteSunDD
    /call AbilitySet_Add "Remote Sunblaze" RemoteSunDD
    /call AbilitySet_Add "Remote Sunflash" RemoteSunDD
    /call AbilitySet_Add "Remote Sunfire" RemoteSunDD
    /call AbilitySet_Add "Remote Sunburst" RemoteSunDD
    /call AbilitySet_Add "Remote Sunflare" RemoteSunDD
    /call AbilitySet_Add "Remote Manaflux" RemoteSunDD
    /call AbilitySet_ChooseOuter RemoteSunDD RemoteSunDD
    
    |- Remote Moon DD >= 99LVL
    /call AbilitySet_Add "Remote Moonchill" RemoteMoonDD
    /call AbilitySet_Add "Remote Moonrake" RemoteMoonDD
    /call AbilitySet_Add "Remote Moonflash" RemoteMoonDD
    /call AbilitySet_Add "Remote Moonflame" RemoteMoonDD
    /call AbilitySet_Add "Remote Moonfire" RemoteMoonDD
    /call AbilitySet_ChooseOuter RemoteMoonDD RemoteMoonDD

    |- Roar DD >= 93LVL
    /call AbilitySet_Add "Bloody Roar" RoarDD
    /call AbilitySet_Add "Typhonic Roar" RoarDD
    /call AbilitySet_Add "Cyclonic Roar" RoarDD
    /call AbilitySet_Add "Anabatic Roar" RoarDD
    /call AbilitySet_Add "Katabatic Roar" RoarDD
    /call AbilitySet_Add "Roar of Kolos" RoarDD
    /call AbilitySet_ChooseOuter RoarDD1 RoarDD
    /call AbilitySet_ChooseOuter RoarDDSecond RoarDD "${RoarDD1}"
    
    |- Quick Cast Roar Series -- will be replaced by roar at lvl 93
    /call AbilitySet_Add "Maelstrom of the Stormborn" QuickRoarDD
    /call AbilitySet_Add "Thunderbolt of the Stormborn" QuickRoarDD
    /call AbilitySet_Add "Typhoon of the Stormborn" QuickRoarDD
    /call AbilitySet_Add "Whirlwind of the Stormborn" QuickRoarDD
    /call AbilitySet_Add "Cyclone of the Stormborn" QuickRoarDD
    /call AbilitySet_Add "Shear of the Stormborn" QuickRoarDD
    /call AbilitySet_Add "Squall of the Stormborn" QuickRoarDD
    /call AbilitySet_Add "Tempest of the Stormborn" QuickRoarDD
    /call AbilitySet_Add "Gale of the Stormborn" QuickRoarDD
    /call AbilitySet_Add "Stormwatch" QuickRoarDD
    /call AbilitySet_Add "Storm's Fury" QuickRoarDD
    /call AbilitySet_Add "Dustdevil" QuickRoarDD
    /call AbilitySet_Add "Fury of Air" QuickRoarDD
    /call AbilitySet_ChooseOuter QuickRoarDD QuickRoarDD
    
    |- Dicho Spell >= 101LVL
    /call AbilitySet_Add "Ecliptic Winds" DichoSpell
    /call AbilitySet_Add "Composite Winds" DichoSpell
    /call AbilitySet_Add "Dissident Winds" DichoSpell
    /call AbilitySet_Add "Dichotomic Winds" DichoSpell
    /call AbilitySet_ChooseOuter DichoSpell DichoSpell
    
    | - Ice Nuke
    /call AbilitySet_Add "Ice" IceNuke
    /call AbilitySet_Add "Frost" IceNuke
    /call AbilitySet_Add "Moonfire" IceNuke
    /call AbilitySet_Add "Winter's Frost" IceNuke
    /call AbilitySet_Add "Glitterfrost" IceNuke
    /call AbilitySet_Add "Rime Crystals" IceNuke
    /call AbilitySet_Add "Hoar Crystals" IceNuke
    /call AbilitySet_Add "Glaciating Crystals" IceNuke
    /call AbilitySet_Add "Argent Crystals" IceNuke
    /call AbilitySet_Add "Sterlingfrost Crystals" IceNuke
    /call AbilitySet_Add "Gelid Crystals" IceNuke
    /call AbilitySet_Add "Frostweave Crystals" IceNuke
    /call AbilitySet_Add "Frostreave Crystals" IceNuke
    /call AbilitySet_Add "Icerend Crystals" IceNuke
    /call AbilitySet_Add "Moonwhisper Crystals" IceNuke
    /call AbilitySet_ChooseOuter IceNuke IceNuke
    
    |- Winters Fire DD Line >= 73LVL -- Using for Low level Fire DD as well
    /call AbilitySet_Add "Winter's Wildbrume" WinterFireDD
    /call AbilitySet_Add "Winter's Wildshock" WinterFireDD
    /call AbilitySet_Add "Winter's Wildblaze" WinterFireDD
    /call AbilitySet_Add "Winter's Wildflame" WinterFireDD
    /call AbilitySet_Add "Winter's Wildfire" WinterFireDD
    /call AbilitySet_Add "Winter's Sear" WinterFireDD
    /call AbilitySet_Add "Winter's Pyre" WinterFireDD
    /call AbilitySet_Add "Winter's Flare" WinterFireDD
    /call AbilitySet_Add "Winter's Blaze" WinterFireDD
    /call AbilitySet_Add "Winter's Flame" WinterFireDD
    /call AbilitySet_Add "Solstice Strike" WinterFireDD
    /call AbilitySet_Add "Sylvan Fire" WinterFireDD
    /call AbilitySet_Add "Summer's Flame" WinterFireDD    
    /call AbilitySet_Add "Wildfire" WinterFireDD
    /call AbilitySet_Add "Scoriae" WinterFireDD
    /call AbilitySet_Add "Starfire" WinterFireDD      
    /call AbilitySet_Add "Firestrike" WinterFireDD
    /call AbilitySet_Add "Combust" WinterFireDD
    /call AbilitySet_Add "Ignite" WinterFireDD 
    /call AbilitySet_Add "Burst of Fire" WinterFireDD
    /call AbilitySet_Add "Burst of Flame" WinterFireDD 
    /call AbilitySet_ChooseOuter WinterFireDD WinterFireDD


    |- Chill DOT Line -- >= 95LVL -- Used for Burns
    /call AbilitySet_Add "Chill of the Dusksage Tender" ChillDOT
    /call AbilitySet_Add "Chill of the Arbor Tender" ChillDOT
    /call AbilitySet_Add "Chill of the Wildtender" ChillDOT
    /call AbilitySet_Add "Chill of the Copsetender" ChillDOT
    /call AbilitySet_Add "Chill of the Visionary" ChillDOT
    /call AbilitySet_Add "Chill of the Natureward" ChillDOT
    /call AbilitySet_ChooseOuter ChillDOT ChillDOT
    
    |- Opaline Group Health
    /call AbilitySet_Add "Luclinite Blessing" HPTypeOneGroup
    /call AbilitySet_Add "Opaline Blessing" HPTypeOneGroup
    /call AbilitySet_Add "Arcronite Blessing" HPTypeOneGroup
    /call AbilitySet_Add "Shieldstone Blessing" HPTypeOneGroup
    /call AbilitySet_Add "Granitebark Blessing" HPTypeOneGroup
    /call AbilitySet_Add "Stonebark Blessing" HPTypeOneGroup
    /call AbilitySet_Add "Blessing of the Timbercore" HPTypeOneGroup
    /call AbilitySet_Add "Blessing of the Heartwood" HPTypeOneGroup
    /call AbilitySet_Add "Blessing of the Ironwood" HPTypeOneGroup
    /call AbilitySet_Add "Blessing of the Direwild" HPTypeOneGroup
    /call AbilitySet_Add "Blessing of Steeloak" HPTypeOneGroup
    /call AbilitySet_Add "Blessing of the Nine" HPTypeOneGroup
    /call AbilitySet_Add "Protection of the Glades" HPTypeOneGroup
    /call AbilitySet_Add "Protection of Nature" HPTypeOneGroup
    /call AbilitySet_Add "Protection of Diamond" HPTypeOneGroup 
    /call AbilitySet_Add "Protection of Steel" HPTypeOneGroup
    /call AbilitySet_Add "Protection of Rock" HPTypeOneGroup
    /call AbilitySet_Add "Protection of Wood" HPTypeOneGroup
    /call AbilitySet_ChooseOuter HPTypeOneGroup HPTypeOneGroup

    | - Druid Mana Bear Growth Line
    | - /call AbilitySet_Add "Nature Walker's Behest" ManaBear
    /call AbilitySet_Add "Nurturing Growth" ManaBear
    /call AbilitySet_Add "Nourishing Growth" ManaBear
    /call AbilitySet_Add "Sustaining Growth" ManaBear
    /call AbilitySet_Add "Bolstered Growth" ManaBear
    /call AbilitySet_ChooseOuter ManaBear ManaBear
   
   	| - Druid Mushroom DOT Pet Line >= 84LVL --used for mana savings
	/call AbilitySet_Add "Saprophyte Assault" ShroomPet
    /call AbilitySet_Add "Chytrid Assault" ShroomPet
    /call AbilitySet_Add "Fungusoid Assault" ShroomPet
    /call AbilitySet_Add "Sporali Storm" ShroomPet
	/call AbilitySet_Add "Sporali Assault" ShroomPet
	/call AbilitySet_Add "Myconid Assault" ShroomPet
	/call AbilitySet_Add "Polyporous Assault" ShroomPet
	/call AbilitySet_Add "Blast of Hypergrowth" ShroomPet
    /call AbilitySet_ChooseOuter ShroomPet ShroomPet
   
    |- Temp Health -- Focus on Tank
    /call AbilitySet_Add "Fervent Growth" TempHPBuff
    /call AbilitySet_Add "Frenzied Growth" TempHPBuff
    /call AbilitySet_Add "Savage Growth" TempHPBuff
    /call AbilitySet_Add "Ferocious Growth" TempHPBuff
    /call AbilitySet_Add "Rampant Growth" TempHPBuff
    /call AbilitySet_Add "Unfettered Growth" TempHPBuff
    /call AbilitySet_Add "Untamed Growth" TempHPBuff
    /call AbilitySet_Add "Wild Growth" TempHPBuff
    /call AbilitySet_ChooseOuter TempHPBuff TempHPBuff
    
    | -  Group Regen Buff - All Have Long Duration HP Regen Buffs. Not Short term Heal.
    /call AbilitySet_Add "Talisman of the Tenacious" GroupRegenBuff
    /call AbilitySet_Add "Talisman of the Enduring" GroupRegenBuff
    /call AbilitySet_Add "Talisman of the Unwavering" GroupRegenBuff
    /call AbilitySet_Add "Talisman of the Faithful" GroupRegenBuff
    /call AbilitySet_Add "Talisman of the Steadfast" GroupRegenBuff
    /call AbilitySet_Add "Talisman of the Indomitable" GroupRegenBuff
    /call AbilitySet_Add "Talisman of the Relentless" GroupRegenBuff
    /call AbilitySet_Add "Talisman of the Resolute" GroupRegenBuff
    /call AbilitySet_Add "Talisman of the Stalwart" GroupRegenBuff 
    /call AbilitySet_Add "Pack Regeneration" GroupRegenBuff
    /call AbilitySet_Add "Pack Chloroplast" GroupRegenBuff
    /call AbilitySet_Add "Regrowth of the Grove"  GroupRegenBuff
    /call AbilitySet_Add "Blessing of Oak"  GroupRegenBuff
    /call AbilitySet_Add "Blessing of Replenishment" GroupRegenBuff
    /call AbilitySet_ChooseOuter GroupRegenBuff GroupRegenBuff

    |- Self mana Regen Buff
    /call AbilitySet_Add "Mask of the Dusksage Tender" SelfManaRegen
    /call AbilitySet_Add "Mask of the Arbor Tender" SelfManaRegen
    /call AbilitySet_Add "Mask of the Wildtender" SelfManaRegen
    /call AbilitySet_Add "Mask of the Copsetender" SelfManaRegen
    /call AbilitySet_Add "Mask of the Bosquetender" SelfManaRegen
    /call AbilitySet_Add "Mask of the Thicket Dweller" SelfManaRegen
    /call AbilitySet_Add "Mask of the Arboreal" SelfManaRegen
    /call AbilitySet_Add "Mask of the Raptor" SelfManaRegen
    /call AbilitySet_Add "Mask of the Shadowcat" SelfManaRegen
    /call AbilitySet_Add "Mask of the Wild" SelfManaRegen
    /call AbilitySet_Add "Mask of the Forest" SelfManaRegen
    /call AbilitySet_Add "Mask of the Hunter" SelfManaRegen
    /call AbilitySet_Add "Mask of the Stalker" SelfManaRegen
    /call AbilitySet_ChooseOuter SelfManaRegen SelfManaRegen
    
    |- Single Target Attack Buff for MeleeGuard
    /call AbilitySet_Add "Mammoth's Force" AtkBuff
    /call AbilitySet_Add "Mammoth's Strength" AtkBuff
    /call AbilitySet_Add "Lion's Strength" AtkBuff
    /call AbilitySet_Add "Nature's Might" AtkBuff
    /call AbilitySet_Add "Girdle of Karana" AtkBuff
    /call AbilitySet_Add "Storm Strength" AtkBuff
    /call AbilitySet_Add "Strength of Stone" AtkBuff
    /call AbilitySet_Add "Strength of Earth" AtkBuff
    /call AbilitySet_ChooseOuter AtkBuff AtkBuff
    
    |- Alliance Buff >= LVL102
    /call AbilitySet_Add "Bosquetender's Alliance" Alliance
    /call AbilitySet_Add "Arbor Tender's Coalition" Alliance
    /call AbilitySet_Add "Arboreal Atonement" Alliance
    /call AbilitySet_ChooseOuter Alliance Alliance
    
    |- Self Shield Buff
    /call AbilitySet_Add "Shadespine Coat" SelfShield
    /call AbilitySet_Add "Icebriar Coat" SelfShield
    /call AbilitySet_Add "Daggerspike Coat" SelfShield
    /call AbilitySet_Add "Daggerspur Coat" SelfShield
    /call AbilitySet_Add "Spikethistle Coat" SelfShield
    /call AbilitySet_Add "Spineburr Coat" SelfShield
    /call AbilitySet_Add "Bonebriar Coat" SelfShield
    /call AbilitySet_Add "Brierbloom Coat" SelfShield
    /call AbilitySet_Add "Viridithorn Coat" SelfShield
    /call AbilitySet_Add "Viridicoat" SelfShield
    /call AbilitySet_Add "Nettlecoat" SelfShield
    /call AbilitySet_Add "Brackencoat" SelfShield
    /call AbilitySet_Add "Bladecoat" SelfShield
    /call AbilitySet_Add "Thorncoat" SelfShield
    /call AbilitySet_Add "Spikecoat" SelfShield
    /call AbilitySet_Add "Bramblecoat" SelfShield
    /call AbilitySet_Add "Barbcoat" SelfShield
    /call AbilitySet_Add "Thistlecoat" SelfShield
    /call AbilitySet_ChooseOuter SelfShield SelfShield
    
    | - Ice Rain Nuke 12 - 114
        /call AbilitySet_Add "Cascade of Hail" IceRainNuke
        /call AbilitySet_Add "Pogonip" IceRainNuke
        /call AbilitySet_Add "Avalanche" IceRainNuke
        /call AbilitySet_Add "Blizzard" IceRainNuke
        /call AbilitySet_Add "Winter's Storm" IceRainNuke
        /call AbilitySet_Add "Tempest Wind" IceRainNuke
        /call AbilitySet_Add "Cloudburst Hail" IceRainNuke
        /call AbilitySet_Add "Torrential Hail" IceRainNuke
        /call AbilitySet_Add "Cascading Hail" IceRainNuke
        /call AbilitySet_Add "Cyclonic Hail" IceRainNuke
        /call AbilitySet_Add "Crashing Hail" IceRainNuke
        /call AbilitySet_Add "Hailstorm" IceRainNuke
        /call AbilitySet_Add "Plummeting Hail" IceRainNuke
        /call AbilitySet_Add "Plunging Hail" IceRainNuke
        /call AbilitySet_Add "Tempestuous Hail" IceRainNuke
        /call AbilitySet_ChooseOuter IceRainNuke IceRainNuke

    |**
    | - Single Target Damage Shield
    /call AbilitySet_Add "Shield of Thistles" SingleDS
    /call AbilitySet_Add "Shield of Barbs" SingleDS
    /call AbilitySet_Add "Shield of Brambles" SingleDS
    /call AbilitySet_Add "Shield of Spikes" SingleDS
    /call AbilitySet_Add "Shield of Thorns" SingleDS
    /call AbilitySet_Add "Shield of Blades" SingleDS
    /call AbilitySet_Add "Shield of Bracken" SingleDS
    /call AbilitySet_Add "Nettle Shield" SingleDS
    /call AbilitySet_Add "Viridifloral Shield" SingleDS
    /call AbilitySet_Add "Viridifloral Bulwark" SingleDS
    /call AbilitySet_Add "Brierbloom Bulwark" SingleDS
    /call AbilitySet_Add "Bonebriar Bulwark" SingleDS
    /call AbilitySet_Add "Spineburr Bulwark" SingleDS
    /call AbilitySet_Add "Spikethistle Bulwark" SingleDS
    /call AbilitySet_Add "Daggerspur Bulwark" SingleDS
    /call AbilitySet_Add "Daggerspike Bulwark" SingleDS
    /call AbilitySet_Add "Icebriar Bulwark" SingleDS
    /call AbilitySet_ChooseOuter SingleDS SingleDS 
    
    |- Group Damage Shield -- Focus on the tank
    /call AbilitySet_Add "Legacy of Icebriars" GroupDmgShield
    /call AbilitySet_Add "Legacy of Daggerspikes" GroupDmgShield
    /call AbilitySet_Add "Legacy of Daggerspurs" GroupDmgShield
    /call AbilitySet_Add "Legacy of Spikethistles" GroupDmgShield
    /call AbilitySet_Add "Legacy of Spineburrs" GroupDmgShield
    /call AbilitySet_Add "Legacy of Bonebriar" GroupDmgShield
    /call AbilitySet_Add "Legacy of Brierbloom" GroupDmgShield
    /call AbilitySet_Add "Legacy of Viridithorns" GroupDmgShield
    /call AbilitySet_Add "Legacy of Viridiflora" GroupDmgShield
    /call AbilitySet_Add "Legacy of Nettles" GroupDmgShield
    /call AbilitySet_Add "Legacy of Bracken" GroupDmgShield
    /call AbilitySet_Add "Legacy of Thorn" GroupDmgShield
    /call AbilitySet_Add "Legacy of Spike" GroupDmgShield
    /call AbilitySet_ChooseOuter GroupDmgShield GroupDmgShield
   **|
    |- Group Damage Shield -- Combined all single and group dammage shields.
    /call AbilitySet_Add "Legacy of Bloodspikes" GroupDmgShield
    /call AbilitySet_Add "Duskthorn" GroupDmgShield
    /call AbilitySet_Add "Legacy of Icebriars" GroupDmgShield
	/call AbilitySet_Add "Icebriar Bulwark" GroupDmgShield
    /call AbilitySet_Add "Legacy of Daggerspikes" GroupDmgShield
	/call AbilitySet_Add "Daggerspike Bulwark" GroupDmgShield
    /call AbilitySet_Add "Legacy of Daggerspurs" GroupDmgShield
	/call AbilitySet_Add "Daggerspur Bulwark" GroupDmgShield
    /call AbilitySet_Add "Legacy of Spikethistles" GroupDmgShield
	/call AbilitySet_Add "Spikethistle Bulwark" GroupDmgShield
    /call AbilitySet_Add "Legacy of Spineburrs" GroupDmgShield
	/call AbilitySet_Add "Spineburr Bulwark" GroupDmgShield
    /call AbilitySet_Add "Legacy of Bonebriar" GroupDmgShield
	/call AbilitySet_Add "Bonebriar Bulwark" GroupDmgShield
    /call AbilitySet_Add "Legacy of Brierbloom" GroupDmgShield
	/call AbilitySet_Add "Brierbloom Bulwark" GroupDmgShield
    /call AbilitySet_Add "Legacy of Viridithorns" GroupDmgShield
	/call AbilitySet_Add "Viridifloral Bulwark" GroupDmgShield
    /call AbilitySet_Add "Legacy of Viridiflora" GroupDmgShield
	/call AbilitySet_Add "Viridifloral Shield" GroupDmgShield
    /call AbilitySet_Add "Legacy of Nettles" GroupDmgShield
	/call AbilitySet_Add "Nettle Shield" GroupDmgShield
    /call AbilitySet_Add "Legacy of Bracken" GroupDmgShield
	/call AbilitySet_Add "Shield of Bracken" GroupDmgShield
    /call AbilitySet_Add "Legacy of Thorn" GroupDmgShield
	/call AbilitySet_Add "Shield of Blades" GroupDmgShield
    /call AbilitySet_Add "Legacy of Spike" GroupDmgShield
	/call AbilitySet_Add "Shield of Thorns" GroupDmgShield
	/call AbilitySet_Add "Shield of Spikes" GroupDmgShield
	/call AbilitySet_Add "Shield of Brambles" GroupDmgShield
	/call AbilitySet_Add "Shield of Barbs" GroupDmgShield
	/call AbilitySet_Add "Shield of Thistles" GroupDmgShield
    /call AbilitySet_ChooseOuter GroupDmgShield GroupDmgShield
    
    |- Group Movement Series Spells -- Mix of group target and single target but will require the same dannet checks
    /call AbilitySet_Add "Flight of Falcons" MoveSpells
    /call AbilitySet_Add "Flight of Eagles" MoveSpells
    |- /call AbilitySet_Add "Spirit of Scale" MoveSpells
    /call AbilitySet_Add "Feral Pack" MoveSpells
    /call AbilitySet_Add "Share Form of the Great Wolf" MoveSpells
    /call AbilitySet_Add "Pack Shrew" MoveSpells
    /call AbilitySet_Add "Pack Spirit" MoveSpells
    /call AbilitySet_Add "Share Wolf Form" MoveSpells
    /call AbilitySet_Add "Spirit of Falcons" MoveSpells
    /call AbilitySet_Add "Spirit of Eagle" MoveSpells
    /call AbilitySet_Add "Spirit of the Shrew" MoveSpells
    |- /call AbilitySet_Add "Scale of Wolf" MoveSpells
    /call AbilitySet_Add "Spirit of Wolf" MoveSpells
    /call AbilitySet_ChooseOuter MoveSpells MoveSpells
    
    |- Root Spells
    /call AbilitySet_Add "Vinelash Assault" RootSpells
    /call AbilitySet_Add "Vinelash Cascade" RootSpells
    /call AbilitySet_Add "Spore Spiral" RootSpells
    /call AbilitySet_Add "Savage Roots" RootSpells
    /call AbilitySet_Add "Earthen Roots" RootSpells
    /call AbilitySet_Add "Entrapping Roots" RootSpells
    /call AbilitySet_Add "Engorging Roots" RootSpells
    /call AbilitySet_Add "Engulfing Roots" RootSpells
    /call AbilitySet_Add "Enveloping Roots" RootSpells
    /call AbilitySet_Add "Ensnaring Roots" RootSpells
    /call AbilitySet_Add "Grasping Roots" RootSpells
    /call AbilitySet_ChooseOuter RootSpells RootSpells
    
    |- Snare Spells
    /call AbilitySet_Add "Thornmaw Vines" SnareSpells
    /call AbilitySet_Add "Hungry Vines" SnareSpells
    /call AbilitySet_Add "Serpent Vines" SnareSpells
    /call AbilitySet_Add "Entangle" SnareSpells
    /call AbilitySet_Add "Mire Thorns" SnareSpells
    /call AbilitySet_Add "Bonds of Tunare" SnareSpells
    /call AbilitySet_Add "Ensnare" SnareSpells
    /if (${EverQuest.Server.Find[zek]}) /call AbilitySet_Add "Tangle" SnareSpells
    /if (${EverQuest.Server.Find[zek]}) /call AbilitySet_Add "Entangle" SnareSpells
    /call AbilitySet_Add "Snare" SnareSpells
    /call AbilitySet_Add "Tangling Weeds" SnareSpells
    /call AbilitySet_ChooseOuter SnareSpells SnareSpells


    | - Spell vars Added for Bobcatts New Mode. - While keeping originals Intact! for other modes.
    /call AbilitySet_Add "Remote Moonrake" RemoteDD
	/call AbilitySet_Add "Remote Sunshock" RemoteDD
    /call AbilitySet_Add "Remote Moonflash" RemoteDD
	/call AbilitySet_Add "Remote Sunblaze" RemoteDD
    /call AbilitySet_Add "Remote Moonflame" RemoteDD
	/call AbilitySet_Add "Remote Sunflash" RemoteDD
    /call AbilitySet_Add "Remote Moonfire" RemoteDD
	/call AbilitySet_Add "Remote Sunfire" RemoteDD
	/call AbilitySet_Add "Remote Sunburst" RemoteDD
	/call AbilitySet_Add "Remote Sunflare" RemoteDD
	/call AbilitySet_Add "Remote Manaflux" RemoteDD
    /call AbilitySet_ChooseOuter RemoteDD RemoteDD

    |- SunMoonDOT Line >= 1 LVL
	/call AbilitySet_Add "Opaline Moonbeam" SunMoonDot
    /call AbilitySet_Add "Erupting Sunray" SunMoonDot
	/call AbilitySet_Add "Pearlescent Moonbeam" SunMoonDot
    /call AbilitySet_Add "Overwhelming Sunray" SunMoonDot
	/call AbilitySet_Add "Argent Moonbeam" SunMoonDot
    /call AbilitySet_Add "Consuming Sunray" SunMoonDot
	/call AbilitySet_Add "Frigid Moonbeam" SunMoonDot
    /call AbilitySet_Add "Incinerating Sunray" SunMoonDot
	/call AbilitySet_Add "Algid Moonbeam" SunMoonDot
    /call AbilitySet_Add "Blazing Sunray" SunMoonDot
	/call AbilitySet_Add "Gelid Moonbeam" SunMoonDot
    /call AbilitySet_Add "Scorching Sunray" SunMoonDot
    /call AbilitySet_Add "Withering Sunray" SunMoonDot
    /call AbilitySet_Add "Torrid Sunray" SunMoonDot
    /call AbilitySet_Add "Blistering Sunray" SunMoonDot
    /call AbilitySet_Add "Immolation of the Sun" SunMoonDot
    /call AbilitySet_Add "Sylvan Embers" SunMoonDot
    /call AbilitySet_Add "Immolation of Ro" SunMoonDot
    /call AbilitySet_Add "Breath of Ro" SunMoonDot
    /call AbilitySet_Add "Immolate" SunMoonDot
    /call AbilitySet_Add "Flame Lick" SunMoonDot
    /call AbilitySet_ChooseOuter SunMoonDot SunMoonDot

    |- Ice Nuke DD --Gap Filler
	/call AbilitySet_Add "Moonfire" IceDD
	/call AbilitySet_Add "Frost" IceDD
	/call AbilitySet_ChooseOuter IceDD IceDD
    
    |- Rush Heal Line
    |- Skipping the rush line as the mana cost is significantly higher than the straight heal. 
    |- This Creates a ChatbegList Object  with the Name DruBegs 
    /call ChatBegList_Add DRUBegs rgc             Spell "${SingleTgtCure}"  sender TRUE
    /call ChatBegList_Add DRUBegs cureme          AA     "Radiant Cure"      sender TRUE
| - Stub need to input Poison/Diease Cures for TLP Druid mode begs.
|    /call ChatBegList_Add SHMBegs tlpcurep        Spell  "${TLPCurePoison}"  sender ${Parse[0,"( ${Target.Poisoned} )"]}
|   /call ChatBegList_Add SHMBegs tlpcured        Spell  "${TLPCureDisease}" sender ${Parse[0,"( ${Target.Diseased} )"]}

    /call Cure_AddAll "${SingleTgtCure}" Spell "${SingleTgtCure}" Spell "${SingleTgtCure}" Spell "${SingleTgtCure}" Spell   
/return

|----------------------------------------------------------------------------
|- SUB: Heal spell config
|---------------------------------------------------------------------------- 
Sub DRU_ModeConfigMODEHEAL
    /varset IsHealing TRUE
    /varset IsCuring TRUE
    | - Adjusted healpoint based on user testing
    /varset MainHealPoint[SETTINGVAL] 95
    /varset DoProm[SETTINGVAL] 1
    /Echo Heal Mode Detected 
    /varset Spell1 ${LongHeal1}
    
    /if (${Me.Level} < 75) {
        /varset Spell2 ${LongHeal2}
    } else {
        /varset Spell2 ${QuickHealSurge}
    }
    
    /if (${Me.Level} < 90) {
        /varset Spell3 ${QuickRoarDD}
    } else {
        /varset Spell3 ${QuickHeal}
    }
    
    /if (${Me.Level} < 78) {
        /varset Spell4 ${HordeDOT}
    } else {
        /varset Spell4 ${PromHeal}
    }
    
    /if (${SunDOT.Equal[NULL]}) {
        /varset Spell5 ${SunrayDOT}
    } else {
        /if (${Me.Level} < 70) {
            /varset Spell5 ${SunDOT}
        } else {
            /varset Spell5 ${LongGroupHeal}
        }
    }
    
    /if (${ReptileCombatInnate.Equal[NULL]}) {
        /varset Spell6 ${SnareSpells}
    } else {
        /if (${Me.Level} < 73) {
            /varset Spell6 ${ReptileCombatInnate}
        } else {
            /varset Spell6 ${SunrayDOT}
        }
    }
    
    /if (${Me.Level} < 74) {
        /varset Spell7 ${RoDebuff}
    } else {
        /varset Spell7 ${FrostDebuff}
    }
    
    /varset Spell8 ${TwincastNuke}
    /varset Spell9 ${IceBreathDebuff}
    /varset Spell10 ${TempHPBuff}
    /varset Spell11 ${RemoteSunDD}

    /if (${Me.Level} < 101) {
        /varset Spell12 ${GroupCure}
    } else {
        /varset Spell12 ${DichoSpell}
    }
    
    /if (${DoAlliance[SETTINGVAL]}) {
        /varset Spell13 ${Alliance}
    } else {
        /varset Spell13 NULL
    }

    |- Rotations
    |- Self Buffs
    /call DRU_DefaultSelfBuffRotationConfig ${Me.Class.ShortName}_Downtime_MODEHEAL_Rotation
    |- Group Buffs
    /call DRU_DefaultBuffGroupConfig
    |- Heals
    /call DRU_DefaultHealRotationConfig
 
    |- DPS Rotation -- based on Raid Druid guide. We start on the DOTs then move to DD spells
    |- DOTS: NaturesWrathDOT -> HordeDOT -> SunDOT -> ChillDOT -> 
    |- Nukes: DichoSpell -> RemoteDD -> RoarDD -> Anabatic Roar -> Winter’s Wildblaze
    
	
    /if (${DoFire[SETTINGVAL]}) {
        /varset Spell11 ${RemoteSunDD}
        /varset Spell6 ${SunrayDOT}
       /call AddToRotation DRU_DPS_MODEHEAL_Rotation  "${SunrayDOT}"        Spell ${Parse[0,"( DOTSPELLCHECK && ${DoDots[SETTINGVAL]} && ${FindItemCount[${Spell[${SunrayDOT}].NoExpendReagentID[1]}]} >= 1 )"]}
       /call AddToRotation DRU_DPS_MODEHEAL_Rotation  "Nature's Fire"       AA    ${Parse[0,"( DETSPELLCHECK &&  && ( MANACHECK || BURNCHECK ) && ${DoNukes[SETTINGVAL]} )"]}  
       /call AddToRotation DRU_DPS_MODEHEAL_Rotation  "${RemoteSunDD}"      Spell ${Parse[0,"( DETSPELLCHECK && ${Target.PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNukes[SETTINGVAL]} )"]}
      
    }
    /if (!${DoFire[SETTINGVAL]}) {
        /varset Spell11 ${RemoteMoonDD}
        /varset Spell6 ${MoonBeamDOT}
        /call AddToRotation DRU_DPS_MODEHEAL_Rotation   "${ChillDOT}"          Spell ${Parse[0,"( DOTSPELLCHECK && ${DoDots[SETTINGVAL]} )"]}
        /call AddToRotation DRU_DPS_MODEHEAL_Rotation   "Nature's Frost"       AA    ${Parse[0,"( DETSPELLCHECK &&  &&  ( MANACHECK || BURNCHECK ) && ${DoNukes[SETTINGVAL]} )"]}  
        /call AddToRotation DRU_DPS_MODEHEAL_Rotation   "${RemoteMoonDD}"      Spell ${Parse[0,"( DETSPELLCHECK && ${Target.PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNukes[SETTINGVAL]} )"]}
        
    }
    /call AddToRotation DRU_DPS_MODEHEAL_Rotation  "${DichoSpell}"       Spell ${Parse[0,"( DETSPELLCHECK && ${Target.PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNukes[SETTINGVAL]} )"]}
    
    /call AddToRotation DRU_DPS_MODEHEAL_Rotation  "Silent Casting" AA TRUE
    |- /call AddToRotation "DRU_DPS_MODEHEAL_Rotation" "Nature's Bolt" AA TRUE
    
    |- Debuff Rotation
    |- RoDebuff (or RoAA) will be manual to handle AA & AE mods
    |- SkinDebuff -> FrostDebuff  
    |- BUG NOTE: SkinDebuff needs additional conditions to make sure it is cast on an NPC that it can stick to
    |- Will not work against undead, constructs, elementals and vampires.
    /if (${DoFire[SETTINGVAL]}) {
        /call AddToRotation DRU_Debuff_MODEHEAL_Rotation  "${RoDebuff}"         Spell ${Parse[0,"( DOTSPELLCHECK )"]}
        /call AddToRotation DRU_Debuff_MODEHEAL_Rotation  "Blessing of Ro"      AA ${Parse[0,"( !${Target.Buff[${Spell[Blessing of Ro].Trigger[1]}].ID})"]}
        /call AddToRotation DRU_Debuff_MODEHEAL_Rotation  "${SkinDebuff}"       Spell ${Parse[0,"( DETSPELLCHECK && ${Target.Body.Name.NotEqual[Undead]} && ${Target.Body.Name.NotEqual[Undead Pet]} )"]}
    }
    /if (!${DoFire[SETTINGVAL]}) {
        /call AddToRotation DRU_Debuff_MODEHEAL_Rotation  "${IceBreathDebuff}"  Spell ${Parse[0,"( DETSPELLCHECK && ${Target.PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNukes[SETTINGVAL]} )"]}
        /call AddToRotation DRU_Debuff_MODEHEAL_Rotation  "${FrostDebuff}"     Spell ${Parse[0,"( DETSPELLCHECK && ${Target.PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNukes[SETTINGVAL]} )"]}
    }
    /call AddToRotation DRU_Debuff_MODEHEAL_Rotation  "${SnareSpells}"      Spell ${Parse[0,"( DETSPELLCHECK && ${Target.PctHPs} < 50 )"]}
    /call AddToRotation DRU_Debuff_MODEHEAL_Rotation  "Season's Wrath"     AA ${Parse[0,"( DETSPELLCHECK )"]}
    
    /call AddToRotation DRU_Burn_MODEHEAL_Rotation "${ChestItemName[SETTINGVAL]}"  Item ${Parse[1,"( ${Spell[${FindItem[${ChestItemName[SETTINGVAL]}].Spell}].Stacks} && (!${FindItem[${ChestItemName[SETTINGVAL]}].TimerReady}) && ${DoChestClick[SETTINGVAL]} )"]}
    /call AddToRotation DRU_Burn_MODEHEAL_Rotation "Nature's Boon"             AA TRUE
    /call AddToRotation DRU_Burn_MODEHEAL_Rotation "Spirit of the Wood"        AA TRUE
    /call AddToRotation DRU_Burn_MODEHEAL_Rotation "Swarm of the Fireflies"    AA TRUE
    /call AddToRotation DRU_Burn_MODEHEAL_Rotation "Distant Conflagration"     AA TRUE
    /call AddToRotation DRU_Burn_MODEHEAL_Rotation "Nature's Guardian"         AA TRUE
    /call AddToRotation DRU_Burn_MODEHEAL_Rotation "Spirits of Nature"         AA TRUE
    /call AddToRotation DRU_Burn_MODEHEAL_Rotation "Destructive Vortex"        AA TRUE
    /call AddToRotation DRU_Burn_MODEHEAL_Rotation "Nature's Fury"             AA TRUE
    /call AddToRotation DRU_Burn_MODEHEAL_Rotation "Spire of Nature"           AA TRUE
/return

|----------------------------------------------------------------------------
|- SUB: MANA spell config
|---------------------------------------------------------------------------- 

Sub DRU_ModeConfigMODEMANA
    /varset IsHealing TRUE
    /varset MainHealPoint[SETTINGVAL] 60
    /varset DoProm[SETTINGVAL] 0
	
    /echo New DPS Mode Detected - Old Mode can be Found Under /rg classmode 99
    /if (${Me.Level} < 101) {
        |- "Attaching" IsHealing Capability to the heal spell to provide conext.
        /varset Spell1 ${LongHeal1}
	} else {
        /varset Spell1 ${DichoSpell}
    }
    
    /if (${Me.Level} < 75) {
        /varset Spell2 ${SnareSpells}
    } else {
        /varset Spell2 ${QuickHeal}
    }
    
    /varset Spell3 ${WinterFireDD}
	
	/if (${Me.Level} < 84) {
        /varset Spell4 ${QuickRoarDD}
    } else {
        /varset Spell4 ${ShroomPet}
    }
	
	/varset Spell5 ${HordeDOT}
    
    /if (${Me.Level} < 83) {
        /varset Spell6 ${RoDebuff}
    } else {
        /varset Spell6 ${RemoteDD}
    }
    
	/varset Spell7 ${SunMoonDot}
	
    /if (${Me.Level} < 49) {
        /varset Spell8 ${RootSpells}
    } else {
        /varset Spell8 ${SunDOT}
    }
    
    /if (${Me.Level} < 63) {
        /varset Spell9 ${IceDD}
    } else {
        /varset Spell9 ${IceBreathDebuff}
    }
    
    /varset Spell10 ${NaturesWrathDOT}
    /varset Spell11 ${TempHPBuff}
    /if (${Me.Level} > 100) {
        /varset Spell12 ${LongHeal1}
    } else {
        /varset Spell12 ${ChillDOT}
    }
    /if (${DoAlliance[SETTINGVAL]}) /varset Spell13 ${Alliance}

    |- Rotations
    |- Self Buffs
    /call DRU_DefaultSelfBuffRotationConfig ${Me.Class.ShortName}_Downtime_MODEMANA_Rotation
    |- Group Buffs
    /call DRU_DefaultBuffGroupConfig
    |- Heals
    /call DRU_DefaultHealRotationConfig

    |- DPS Rotation -- Costomized to save Mana.
    |- DOTS:
    |- Nukes:
	|- Conditionals go inbetween here ${Parse[0,("Condition")]}
	
    /call AddToRotation DRU_DPS_MODEMANA_Rotation "Silent Casting"         AA TRUE
    /call AddToRotation DRU_DPS_MODEMANA_Rotation "Season's Wrath"         AA ${Parse[0,"( DETSPELLCHECK && ${Target.PctHPs} > 75)"]}
	/call AddToRotation DRU_DPS_MODEMANA_Rotation "${ChestItemName[SETTINGVAL]}" Item ${Parse[1,"( ${Spell[${FindItem[${ChestItemName[SETTINGVAL]}].Spell}].Stacks} && (!${FindItem[${ChestItemName[SETTINGVAL]}].TimerReady}) && ${DoChestClick[SETTINGVAL]} )"]}
	/call AddToRotation DRU_DPS_MODEMANA_Rotation "${SunDOT}"           Spell ${Parse[0,"( DOTSPELLCHECK && ${DoDots[SETTINGVAL]} )"]}
	/call AddToRotation DRU_DPS_MODEMANA_Rotation "${HordeDOT}"         Spell ${Parse[0,"( DOTSPELLCHECK && ${DoDots[SETTINGVAL]} )"]}
	/call AddToRotation DRU_DPS_MODEMANA_Rotation "${DichoSpell}"       Spell ${Parse[0,"( DETSPELLCHECK && ${DoDots[SETTINGVAL]} && ${Target.PctHPs} > 60 && ${Me.PctMana} > 50 )"]}
	/call AddToRotation DRU_DPS_MODEMANA_Rotation "${RemoteDD}"         Spell ${Parse[0,"( DETSPELLCHECK && ${Target.PctHPs} > 40 && ${Me.PctMana} > 40 )"]}
	/call AddToRotation DRU_DPS_MODEMANA_Rotation "${SunMoonDot}"       Spell ${Parse[0,"( DOTSPELLCHECK && ${DoDots[SETTINGVAL]} && ( ${Target.ConColor.Equal[WHITE]} || ${Target.ConColor.Equal[YELLOW]} || ${Target.ConColor.Equal[RED]} ) )"]}
	/call AddToRotation DRU_DPS_MODEMANA_Rotation "${NaturesWrathDOT}"  Spell ${Parse[0,"( DOTSPELLCHECK && ${DoDots[SETTINGVAL]} )"]}
	/call AddToRotation DRU_DPS_MODEMANA_Rotation "${ShroomPet}"        Spell ${Parse[0,"( DETSPELLCHECK && ${Me.PctMana} < 60 )"]}
	/call AddToRotation DRU_DPS_MODEMANA_Rotation "${WinterFireDD}"     Spell ${Parse[0,"( DETSPELLCHECK )"]}
	/call AddToRotation DRU_DPS_MODEMANA_Rotation "Nature's Frost"         AA ${Parse[0,"( DETAACHECK && ${Me.PctMana} > 50 )"]}
	/call AddToRotation DRU_DPS_MODEMANA_Rotation "Nature's Fire"          AA ${Parse[0,"( DETAACHECK && ${Me.PctMana} > 50 )"]}
    /call AddToRotation DRU_DPS_MODEMANA_Rotation "Nature's Bolt"          AA ${Parse[0,"( DETAACHECK && ${Me.PctMana} > 50 )"]}
        
    |- Debuff Rotation
    |- RoDebuff (or RoAA) will be manual to handle AA & AE mods
    |- SkinDebuff -> FrostDebuff  
    |- BUG NOTE: SkinDebuff needs additional conditions to make sure it is cast on an NPC that it can stick to
    |- Will not work against undead, constructs, elementals and vampires.
	/call AddToRotation DRU_Debuff_MODEMANA_Rotation "Blessing of Ro"         AA ${Parse[0,"( !${Target.Buff[${Spell[Blessing of Ro].Trigger[1]}].ID} && !${Target.Buff[${Spell[Blessing of Ro].Trigger[2]}].ID})"]}
    /call AddToRotation DRU_Debuff_MODEMANA_Rotation "${RoDebuff}"         Spell ${Parse[0,"( DETSPELLCHECK )"]}
    /call AddToRotation DRU_Debuff_MODEMANA_Rotation "${IceBreathDebuff}"  Spell ${Parse[0,"( DETSPELLCHECK )"]}
	/call AddToRotation DRU_Debuff_MODEMANA_Rotation "${FrostDebuff}"      Spell ${Parse[0,"( DETSPELLCHECK )"]}
    /call AddToRotation DRU_Debuff_MODEMANA_Rotation "${SnareSpells}"      Spell ${Parse[0,"( DETSPELLCHECK && ${Target.PctHPs} < 50 && ${DoSnare[SETTINGVAL]})"]}
    /call AddToRotation DRU_Debuff_MODEMANA_Rotation "${SkinDebuff}"       Spell ${Parse[0,"( DETSPELLCHECK && ${Target.Body.Name.NotEqual[Undead]} && ${Target.Body.Name.NotEqual[Undead Pet]} )"]}
	
    
    

    /call AddToRotation DRU_Burn_MODEMANA_Rotation "Nature's Boon"             AA TRUE
    /call AddToRotation DRU_Burn_MODEMANA_Rotation "Spirit of the Wood"        AA TRUE
    /call AddToRotation DRU_Burn_MODEMANA_Rotation "Swarm of the Fireflies"    AA TRUE
    /call AddToRotation DRU_Burn_MODEMANA_Rotation "Distant Conflagration"     AA TRUE
    /call AddToRotation DRU_Burn_MODEMANA_Rotation "Nature's Guardian"         AA TRUE
    /call AddToRotation DRU_Burn_MODEMANA_Rotation "Spirits of Nature"         AA TRUE
    /call AddToRotation DRU_Burn_MODEMANA_Rotation "Destructive Vortex"        AA TRUE
    /call AddToRotation DRU_Burn_MODEMANA_Rotation "Nature's Fury"             AA TRUE
    /call AddToRotation DRU_Burn_MODEMANA_Rotation "Spire of Nature"           AA TRUE
/return

|----------------------------------------------------------------------------
|- SUB: Mode TLP CONFIG
|---------------------------------------------------------------------------- 
Sub DRU_ModeConfigMODETLP
    /varset IsHealing TRUE
    /varset IsCuring TRUE
    | - Adjusted healpoint based on user testing
    /varset MainHealPoint[SETTINGVAL] 50
    /varset DoProm[SETTINGVAL] 0
    /Echo Tlp Mode Detected - Acting as a Wizzie with Patch heals.
    | - Tlp Spell bar Loadout
    /varset Spell1 ${LongHeal1}
    /if (!${DoFire[SETTINGVAL]}) {
        /varset Spell2 ${IceNuke}
    } else { 
        /varset Spell2 ${WinterFireDD}
    }
    /varset Spell3 ${IceRainNuke}
    /if (!${DoFire[SETTINGVAL]}) {
        /varset Spell4 ${IceBreathDebuff}
    } else { 
        /varset Spell4 ${RoDebuff}
    }
    
    /varset Spell5 ${SunrayDOT}
    /varset Spell6 ${HordeDOT}
    /varset Spell7 ${SnareSpells}
    /varset Spell8 NULL


    |- Rotations
    | - Debuff Rotation
    /call AddToRotation DRU_Debuff_MODETLP_Rotation "${IceBreathDebuff}"    Spell ${Parse[0,"( !${DoFire[SETTINGVAL]} && DOTSPELLCHECK )"]} 
    /call AddToRotation DRU_Debuff_MODETLP_Rotation "${RoDebuff}"           Spell ${Parse[0,"( ${DoFire[SETTINGVAL]} && DOTSPELLCHECK )"]}
    /call AddToRotation DRU_Debuff_MODETLP_Rotation "${SnareSpells}"        Spell ${Parse[0,"( ${DoSnare[SETTINGVAL]} && DOTSPELLCHECK )"]}
    |- DPS Rotation
    /call AddToRotation DRU_DPS_MODETLP_Rotation "${WinterFireDD}"  Spell ${Parse[0,"( ${DoFire[SETTINGVAL]}  && DETSPELLCHECK && ( MANACHECK || BURNCHECK ) )"]}
    /call AddToRotation DRU_DPS_MODETLP_Rotation "${IceRainNuke}"   Spell ${Parse[0,"( ${DoRain[SETTINGVAL]} && !${DoFire[SETTINGVAL]} && DETSPELLCHECK && ( MANACHECK || BURNCHECK ) )"]}
    /call AddToRotation DRU_DPS_MODETLP_Rotation "${IceNuke}"       Spell ${Parse[0,"( !${DoFire[SETTINGVAL]} && DETSPELLCHECK && ( MANACHECK || BURNCHECK ) )"]}
    |-  Burn Rotation
    /call AddToRotation DRU_Burn_MODETLP_Rotation "${HordeDOT}"     Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    
    |- Self Buffs
    /call DRU_DefaultSelfBuffRotationConfig DRU_Downtime_MODETLP_Rotation
    |- Group Buffs
    /call DRU_DefaultBuffGroupConfig
    |- Heals
    /call DRU_DefaultHealRotationConfig
 
/return

Sub DRU_DefaultBuffGroupConfig
    |- Setup our group buffs that will need Dannet
    |- We will have 6 buffs for the group
    /call BuffGroup_Init 8
   
    /call BuffGroup_Set 1 "${GroupDmgShield}"
    /call BuffGroup_Set 2 "${MoveSpells}" "ALL" "${Parse[0, ${DoRunSpeed[SETTINGVAL]}]}"
    /call BuffGroup_Set 3 "${AtkBuff}" "WAR,SHD,PAL,ROG,BER,RNG,BRD,MNK"
    /call BuffGroup_Set 4 "${TempHPBuff}" "WAR,SHD,PAL"
    /call BuffGroup_Set 5 "${HPTypeOneGroup}" 
    /call BuffGroup_Set 6 "${ReptileCombatInnate}" "WAR,SHD"
    /call BuffGroup_Set 7 "${GroupRegenBuff}" 
    /call BuffGroup_Set 8 "Wrath of the Wild" "WAR,SHD,PAL" ${Parse[0, ( ${Target.ID} == ${Group.MainAssist.ID} )" ]}
 /return

Sub DRU_DefaultSelfBuffRotationConfig(string rotation_name)
   |- Self buff rotation
    /call AddToRotation "${rotation_name}" "Nature's Boon"                  AA	 ${Parse[0,"( ${WardsPlease} )"]}
    /call AddToRotation "${rotation_name}" "${SelfShield}"                  Spell ${Parse[0,"( SELFBUFFCHECK )"]}
    /call AddToRotation "${rotation_name}" "${SelfManaRegen}"               Spell ${Parse[0,"( SELFBUFFCHECK ) && ${Zone.Outdoor}"]}
    /call AddToRotation "${rotation_name}" "${IceAura}"                     Spell ${Parse[0,"( !${Me.Aura[1].Name.Find[${Spell[${mi.Key}].BaseName}]} && !${Me.Aura[2].Name.Find[${Spell[${mi.Key}].BaseName}]} )"]}
    /call AddToRotation "${rotation_name}" "${ManaBear}"                    Spell ${Parse[0,"( ${Spell[${ManaBear}].MyCastTime} < 30000 )"]}
    /call AddToRotation "${rotation_name}" "Group Spirit of the Great Wolf" AA    ${Parse[0,"( SELFBUFFAACHECK )"]}
    /call AddToRotation "${rotation_name}" "Spirit of the Great Wolf"       AA    ${Parse[0,"( SELFBUFFAACHECK )"]}
    /call AddToRotation "${rotation_name}" "Preincarnation"                 AA    ${Parse[0,"( SELFBUFFAACHECK )"]}
    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}"       Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount"                  "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}

/return

Sub DRU_DefaultHealRotationConfig
    |- Setup heals
    /call Heal_AddHealPoint ${MainHealPoint[SETTINGVAL]}
    
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${QuickHeal}"           TRUE
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${LongHeal1}"           TRUE
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${QuickHealSurge}"      TRUE
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${LongHeal2}"           TRUE
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${QuickGroupHeal}"      ${Parse[0, "(${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
    /call Heal_AddAA    ${MainHealPoint[SETTINGVAL]} "Wildtender's Survival"  ${Parse[0, "(${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${QuickGroupHeal}"      ${Parse[0,"( ${Target.PctHPs} < ${BigHealPoint[SETTINGVAL]} )"]}  
    /call Heal_AddAA    ${MainHealPoint[SETTINGVAL]} "Blessing of Tunare"     ${Parse[0,"( ${Target.PctHPs} < ${BigHealPoint[SETTINGVAL]} )"]}
    /call Heal_AddAA    ${MainHealPoint[SETTINGVAL]} "Convergence of Spirits" ${Parse[0,"( ${Target.PctHPs} < ${BigHealPoint[SETTINGVAL]} )"]}
  |  /call Heal_AutoBackFill
/return

Sub DRU_Combat_Routine
    /if (DODEBUFF) /call Ordered_Rotation_Follow ${Me.Class.ShortName}_Debuff_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    /if (DODPS) { 
        /if (!${Me.Song[Healing Twincast].ID} && ${PCSPELLReady[${TwincastNuke}]}) {
            /call SpellNow "${TwincastNuke}" ${assistid}
            /delay 20 !${Me.Casting.ID}
        }
        /if ( BURNCHECK ) /call Ordered_Rotation_Follow ${Me.Class.ShortName}_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        /call Ordered_Rotation_Follow ${Me.Class.ShortName}_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }
/return FALSE

Sub DRU_Downtime_Routine
|- Call Self buffs
    /call FollowRotation  ${Me.Class.ShortName}_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}
/return FALSE

Sub DRU_Heal_Routine
    /if ( ${XAssist.XTFullHaterCount} >= 1 ) {
        /call DNetBuffCheck ${assistname} "Wrath of the Wild"
        /if ( ${Macro.Return} && ${NPCAAReady[Wrath of the Wild]}) {
            /call AANow ${Me.AltAbility[Wrath of the Wild].ID} ${assistid}
        }
    }
    |- Do a rez check if we're out of combat
    /if (${RezTimer} == 0) {
        /if (${SpawnCount[REZSEARCH]}) {
            /call DRU_DoRez ${NearestSpawn[REZSEARCH].ID}
        }
        /if (${SpawnCount[REZSEARCHME]}) {
            /call DRU_DoRez ${NearestSpawn[REZSEARCHME].ID}
        }
        /if (${AssistOutside[SETTINGVAL]}) {
            /call Heal_OOGCheckAndRez
        }
    }

    |- If we're a member of a group, heal our group first.
    /if ( ${DoProm[SETTINGVAL]} && !${Spawn[id ${assistid}].CachedBuff[${PromHeal}].ID} && ${PCSpellReady[${PromHeal}]} && ${Spawn[id ${assistid}].Type.NotEqual[Corpse]} &&  ${Spawn[id ${assistid}].Distance}<${AssistRange[SETTINGVAL]}) /call SpellNow "${PromHeal}" ${assistid} 
    /call HealNow ${WorstHurtGroup[${HealPoint_MaxPoint}]}
    
    |- Now check xtargets.
    /if (${AssistOutside[SETTINGVAL]}) {
        /call HealNow ${WorstHurtXT[${HealPoint_MaxPoint}]}
        |- In case we pissed someone off
        /if (${Me.PctHPs} <= ${HealPoint_MaxPoint} ) {
            /call HealNow ${Me.ID}
        }
    }     

    /if (${IsCuring} && !${DoCure[SETTINGVAL]}) /call TOV_CheckDNetForIce
    /if (${IsCuring} && ${DoCure[SETTINGVAL]}) /call CureNow

/return ${Macro.Return}

|---------------------------------------------------------------------------
|- SUB: DoRez
|- Handle Rez Logic.
|---------------------------------------------------------------------------- 
Sub DRU_DoRez(int corpse_id)
    /call SetTarget ${corpse_id}
    /if (${Target.Distance}>25) /corpse

    /if (${Me.CombatState.Equal[COMBAT]} && (${Select[${Spawn[id ${corpse_id}].Class.ShortName},DRU,CLR]} || ${UseBattleRez[SETTINGVAL]}) ) {
        /if (${FindItem[Staff of Forbidden Rites].ID} && ${Me.ItemReady[=Staff of Forbidden Rites]}) {
            /call ItemNow "Staff of Forbidden Rites" ${corpse_id}
            /return ${Macro.Return}
        } else /if (${RG_AAReady[Call of the Wild]}) {
            /call AANow ${Me.AltAbility[Call of the Wild].ID} ${corpse_id}
            /return ${Macro.Return}
        }  
    } else {
        |- Non-Combat Rez Handling
        /if (${RG_CanUseAA[Rejuvenation of Spirit]}) {
            /if (${RG_AAReady[Rejuvenation of Spirit]}) {
                /call AANow ${Me.AltAbility[Rejuvenation of Spirit].ID} ${corpse_id}
                /return ${Macro.Return}
            }
        } else {
            /if (${PCSpellReady[Incarnate Anew]}) {
                /call SpellNow "Incarnate Anew" ${corpse_id}
                /return ${Macro.Return}
            }
        }   
    }    
/return FALSE
|- SUB: SingleCure
|----------------------------------------------------------------------------
|-Thawme wrapper because it's easier then refactoring everything around again
#bind CureIce /cureice
Sub Bind_CureIce(int cureid)
    /if (${PCSpellReady[${SingleTgtCure}]}) {
            /call SpellNow "${SingleTgtCure}" ${cureid}
    }
/return


Sub DRU_PullSetup
    /if (${RG_CanUseAA[Entrap]} && ${DoSnare[SETTINGVAL]}) {
		/call Pull_SetAbility "Entrap" "AA"
    } else /if (${SnareSpells.NotEqual[NULL]} && ${DoSnare[SETTINGVAL]} && ${Me.Gem[${SnareSpells}]}) {
		/call Pull_SetAbility "${SnareSpells}" "Spell"
	} else /if (${RoDebuff.NotEqual[NULL]} && ${Me.Gem[${RoDebuff}]}) {
        /call Pull_SetAbility "${RoDebuff}" Spell
    } 
/return