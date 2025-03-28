|- RGshmutil.inc
|- Version 0.1
|- Updated: 5/24/2019
#define MODEHEAL 0
#define MODEDOT 1
#define MODETLP 2

|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub SHM_Setup
|-List containing BST specific settings settings
    /declare RGList_SHM            list outer
|- Items
    /call ItemSet_New Epic
|-Spells
    |- Buff Section
    /call AbilitySet_New FocusSpell
    /call AbilitySet_New RunSpeedBuff
    /call AbilitySet_New HasteBuff
    /call AbilitySet_New GrowthBuff
    /call AbilitySet_New LowLvlStaminaBuff
    /call AbilitySet_New LowLvlAttackBuff
    /call AbilitySet_New LowLvlStrBuff
    /call AbilitySet_New LowLvlDexBuff
    /call AbilitySet_New LowLvlAgiBuff
    |- Debuff Section
    /call AbilitySet_New AEMaloSpell
    /call AbilitySet_New MaloSpell
    /call AbilitySet_New AESlowSpell
    /call AbilitySet_New SlowSpell
    /call AbilitySet_New DieaseSlow
    |- Proc Section
    /call AbilitySet_New GroupHealProcBuff
    /call AbilitySet_New SelfHealProcBuff
    /call AbilitySet_New DichoSpell
    /call AbilitySet_New MeleeProcBuff
    /call AbilitySet_New SlowProcBuff
    /call AbilitySet_New PackSelfBuff
    |- Heal Section
    /call AbilitySet_New AllianceBuff
    /call AbilitySet_New IcefixSpell
    /call AbilitySet_New RecklessHeal
    /call AbilitySet_New AESpiritualHeal
    /call AbilitySet_New RecourseHeal
    /call AbilitySet_New InterventionHeal
    /call AbilitySet_New GroupRenewalHoT
    /call AbilitySet_New CanniSpell
    /call AbilitySet_New CureSpell
    |- Nuke Section
    /call AbilitySet_New TwinHealNuke
    /call AbilitySet_New PoisonNuke
    /call AbilitySet_New FastPoisonNuke
    /call AbilitySet_New FrostNuke
    |- Dot Section
    /call AbilitySet_New ChaoticDoT
    /call AbilitySet_New PandemicDot
    /call AbilitySet_New MaloDot
    /call AbilitySet_New CurseDoT1
    /call AbilitySet_New CurseDoT2
    /call AbilitySet_New FastPoisonDoT
    /call AbilitySet_New SaryrnDot
    /call AbilitySet_New FastDiseaseDoT    
    /call AbilitySet_New UltorDot
    /call AbilitySet_New NectarDot
    |- Pet Spell
    /call AbilitySet_New PetSpell
    /call AbilitySet_New PetBuffSpell
    /call AbilitySet_New TLPCureDisease
    /call AbilitySet_new TLPCurePoison

    |- Rotations
    /call Ordered_Rotation_New SHM_DPS_MODEHEAL_Rotation
    /call Ordered_Rotation_New SHM_Downtime_MODEHEAL_Rotation
    /call Ordered_Rotation_New SHM_Burn_MODEHEAL_Rotation
    /call Ordered_Rotation_New SHM_Debuff_MODEHEAL_Rotation
    /call Ordered_Rotation_New SHM_Splash_MODEHEAL_Rotation

    /call Ordered_Rotation_New SHM_DPS_MODEDOT_Rotation
    /call Ordered_Rotation_New SHM_Downtime_MODEDOT_Rotation
    /call Ordered_Rotation_New SHM_Burn_MODEDOT_Rotation
    /call Ordered_Rotation_New SHM_Debuff_MODEDOT_Rotation
    /call Ordered_Rotation_New SHM_Splash_MODEDOT_Rotation

    /call Ordered_Rotation_New SHM_DPS_MODETLP_Rotation
    /call Ordered_Rotation_New SHM_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New SHM_Burn_MODETLP_Rotation
    /call Ordered_Rotation_New SHM_Debuff_MODETLP_Rotation
    /call Ordered_Rotation_New SHM_Splash_MODETLP_Rotation

    /call Ordered_Rotation_New SHM_DPS_MODEOAMUK_Rotation
    /call Ordered_Rotation_New SHM_Downtime_MODEOAMUK_Rotation
    /call Ordered_Rotation_New SHM_Burn_MODEOAMUK_Rotation
    /call Ordered_Rotation_New SHM_Debuff_MODEOAMUK_Rotation
    /call Ordered_Rotation_New SHM_Splash_MODEOAMUK_Rotation

    |- Initialize Cure Observers
    /call Cure_Init

|- Misc Variables
    /declare Spell1                    string outer NULL
    /declare Spell2                    string outer NULL
    /declare Spell3                    string outer NULL
    /declare Spell4                    string outer NULL
    /declare Spell5                    string outer NULL
    /declare Spell6                    string outer NULL
    /declare Spell7                    string outer NULL
    /declare Spell8                    string outer NULL
    /declare Spell9                    string outer NULL
    /declare Spell10                string outer NULL
    /declare Spell11                string outer NULL
    /declare Spell12                string outer NULL
    /declare Spell13                string outer NULL
    
    /declare WasStickOn                int    outer 0
    /declare PatchHealPoint            int outer 44
    /declare PatchHeal2Point        int outer 34
    /declare ClickHealPoint            int outer 35
    /declare HealPoint                int outer 99
    /declare HoTTimer                timer outer 0
    /declare CureTimer                timer outer 0
    /declare CureCheckTimer            timer outer 10s
    /declare SetHoTDurationTimer    int outer 0
    /declare DurationMod            float outer 1
    /declare oldtank                string outer NULL
    /declare oldtankid                string outer NULL
    /declare newtank                int outer 0
    /declare CureMemberCount        int outer 0
    /declare CureMemberID             int outer 0
    /declare DotSpell               string outer NULL
    /declare NukeSpell              string outer NULL
    /declare AvatarCheck            timer outer
    /declare PantherCheck           timer outer

|- Config Options
    /call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = Healing; 1 = DOT Mode
|- Healing Section    
    /call RGLoadSetting SHM DoHeals 1 Healing "Set 0/1 to heal the group. Checked in main loop."
    /call RGLoadSetting SHM DoCure 0 Healing "Set 0/1 to use cure spells to cure people. Default:0. [UNIMPLEMENTED]"
    /call RGLoadSetting SHM MainHealPoint 90 Healing "Set to 0-100 for health point for Main Heal"
    /call RGLoadSetting SHM GroupHealPoint 85 Healing "Set to 0-100 for health point for Group Heal"
    /call RGLoadSetting SHM BigHealPoint 50 Healing "Set to 0-100 for health point for Intervention"
    /call RGLoadSetting SHM PetHealPoint 30 Healing "Set to 0-100 for health point for Pet Heal"
    /call RGLoadSetting SHM GroupInjureCnt 3 Healing "Number of group members to be injured before using a group heal spell."
    /call RGLoadSetting SHM DoBattleRez 0 Healing "Set 0/1 to toggle use battle rez"
    /call RGLoadSetting SHM DoHot 1 Healing "1/0 Allows u to turn off HOTs"
    /call RGLoadSetting SHM RecklessHealPoint 80 Healing "% to start Reckless heals"
    /call RGLoadSetting SHM TlpHealPoint 80 Healing "Set to 0-100 for health point for tlp Heal"
|- Buffs - Debuffs Section
    /call RGLoadSetting SHM AutoDebuffAt 99 Debuff "%HP to debuff Mobs." 1
    /call RGLoadSetting SHM DoRunSpeed 1 Buffs "Set 0/1 To utilize RunSpeed buffs"
    /call RGLoadSetting SHM DoAura 1 Buffs "Set 0/1 To utilize Shaman Aura" 1
    /call RGLoadSetting SHM DoHaste 1 Buffs "Set0/1 Toggle for casting Haste"
    /call RGLoadSetting SHM DoMalo 0 Debuff "0/1 To perform Malo"
    /call RGLoadSetting SHM DoAoEMalo 1 Debuff "0/1 To perform AoE Malo" 1
    /call RGLoadSetting SHM DoSlow 1 Debuff "0/1 To perform Slow"
    /call RGLoadSetting SHM DoAoESlow 1 Debuff "0/1 To perform AoE Slow" 1
    /call RGLoadSetting SHM DoDieaseSlow 0 Debuff "Use Diease Slow or Not"
    /call RGLoadSetting SHM DoMagicDot 1 Debuff "Use Curse magic Dots if turned off Will use Poison"
| - Low Level Stat Buffs 
    /call RGLoadSetting SHM DoStatBuff 1 Buffs "Set 0/1 to to Talismans buffs for Low level"

|- Combat Section
    /call RGLoadSetting SHM HPStopDOT 30 Combat "%HP to cut off to stop casting dots"
    /call RGLoadSetting SHM Manatonuke 60 Combat "Mana to cast Nukes or Dot Minimum"
    /call RGLoadSetting SHM DoNuke 1 Combat "Set 1/0 to Cast Direct Damage Nukes"
|- Combat Avatar Buff List & Combat Panther
    /call RGLoadSetting SHM DoCombatAvatar 0 Combat " Set 0/1 to Enable Doing Avatar In Combat" 1
    /call RGLoadSetting SHM CaList "NULL" Combat  "Comma delimited priority list of Ferocity During Combat with DoCombatfero=1" 1
    /call RGLoadSetting SHM DoCombatPanther 0 Combat " Set 0/1 to Enable Doing Panther In Combat" 1
    /call RGLoadSetting SHM CpList "NULL" Combat  "Comma delimited priority list of Panther During Combat with DoCombatfero=1" 1

|- General - Items Section
    /call RGLoadSetting SHM DoAACanni 1 General "Set 0/1 to use canni AA"
    /call RGLoadSetting SHM AACanniManaPct 70 General "Set 0-100 for Mana point to use canni AA" 1
    /call RGLoadSetting SHM AACanniMinHP 70 General "Set 0-100 for Min health pct to use canni AA" 1
    /call RGLoadSetting SHM DoSpellCanni 1 General "Set 0/1 to use canni spell between AA canni's"
    /call RGLoadSetting SHM CanniManaPct 90 General "Set 0-100 for Mana point to use canni Spell" 1
    /call RGLoadSetting SHM CanniMinHP 60 General "Set 0-100 for Min health pct to use canni spell" 1
    /call RGLoadSetting SHM DoPet 1 Pet "Set 0/1 to use shaman pet."

    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==1) /varset DurationMod 1.15
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==2) /varset DurationMod 1.3
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==3) /varset DurationMod 1.5
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==4) /varset DurationMod 1.7
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==5) /varset DurationMod 1.9

|-Declare spell variables
    /declare spellmisc             int outer ${Me.NumGems}
    /declare GroupBuffRecast     int outer 0
    /declare miscspellremem        string outer NULL
    /declare tempid                string outer NULL

    /declare spellrememtimer    timer outer 0
    /declare ReadyToCast          timer outer 0
    /declare groupbufftimer        timer outer 0
/return 

|----------------------------------------------------------------------------
|- SUB: CheckSpells
|---------------------------------------------------------------------------- 
Sub SHM_SetupSkills
|-- Shaman Items|
/call ItemSet_Add "Crafted Talisman of Fates" Epic
/call ItemSet_Add "Blessed Spiritstaff of the Heyokah" Epic
/call ItemSet_ChooseOuter Epic Epic




|-----------------------------------------------------
|- Buff Spell Section
|-----------------------------------------------------
|- FocusSpell - Lower Levels Mix in Single Target, Higher Prefer Group Target
    /call AbilitySet_Add "Inner Fire" FocusSpell                    | Level 1 - Single
    /call AbilitySet_Add "Talisman of Tnarg" FocusSpell             | Level 32 - Single
    /call AbilitySet_Add "Talisman of Altuna" FocusSpell            | Level 40 - Single  
    /call AbilitySet_Add "Talisman of Kragg" FocusSpell             | Level 55 - Single
    /call AbilitySet_Add "Khura's Focusing" FocusSpell              | Level 60 - Group
    /call AbilitySet_Add "Focus of the Seventh" FocusSpell          | Level 65 - Group
    /call AbilitySet_Add "Talisman of Wunshi" FocusSpell            | Level 70 - Group
    /call AbilitySet_Add "Talisman of the Dire" FocusSpell          | Level 75 - Group
    /call AbilitySet_Add "Talisman of the Bloodworg" FocusSpell     | Level 80 - Group
    /call AbilitySet_Add "Talisman of Unity" FocusSpell             | Level 85 - Group
    /call AbilitySet_Add "Talisman of Soul's Unity" FocusSpell      | Level 90 - Group
    /call AbilitySet_Add "Talisman of Kolos' Unity" FocusSpell      | Level 95 - Group
    /call AbilitySet_Add "Talisman of the Courageous" FocusSpell    | Level 100 - Group  
    /call AbilitySet_Add "Talisman of the Doomscale" FocusSpell     | Level 105 - Group
    /call AbilitySet_Add "Talisman of the Wulthan" FocusSpell       | Level 110 - Group
    /call AbilitySet_Add "Unity of the Kromrif"  FocusSpell         | Level 111 - Single
    /call AbilitySet_Add "Talisman of the Ry'Gorr" FocusSpell       | Level 115 - Group
    /call AbilitySet_Add "Unity of the Vampyre" FocusSpell          | Level 116 - Single
    /call AbilitySet_Add "Talisman of the Usurper" FocusSpell       | Level 120 - Group
    /call AbilitySet_Add "Celeritous Unity" FocusSpell              | Level 121 - Single
    /call AbilitySet_Add "Talisman of the Heroic"   FocusSpell      | Level 125 - Group
    /call AbilitySet_ChooseOuter FocusSpell FocusSpell

|- RunSpeedBuff - 9 - 74
    /call AbilitySet_Add "Spirit of Tala'Tak" RunSpeedBuff   
    /call AbilitySet_Add "Spirit of Bih`Li" RunSpeedBuff
    /call AbilitySet_Add "Pack Shrew" RunSpeedBuff
    /call AbilitySet_Add "Spirit of Wolf" RunSpeedBuff
    /call AbilitySet_ChooseOuter RunSpeedBuff RunSpeedBuff

|- HasteBuff - 26 - 64
    /call AbilitySet_Add "Talisman of Celerity" HasteBuff   
    /call AbilitySet_Add "Swift Like the Wind" HasteBuff
    /call AbilitySet_Add "Celerity" HasteBuff
    /call AbilitySet_Add "Quickness" HasteBuff
    /call AbilitySet_ChooseOuter HasteBuff HasteBuff   

|- GrowthBuff 111 -> 81
    /call AbilitySet_Add "Overwhelming Growth" GrowthBuff
    /call AbilitySet_Add "Fervent Growth" GrowthBuff
    /call AbilitySet_Add "Frenzied Growth" GrowthBuff
    /call AbilitySet_Add "Savage Growth" GrowthBuff
    /call AbilitySet_Add "Ferocious Growth" GrowthBuff
    /call AbilitySet_Add "Rampant Growth" GrowthBuff
    /call AbilitySet_Add "Unfettered Growth" GrowthBuff   
    /call AbilitySet_Add "Untamed Growth" GrowthBuff
    /call AbilitySet_Add "Wild Growth" GrowthBuff
    /call AbilitySet_ChooseOuter GrowthBuff  GrowthBuff   
    
|- Low Level Stamina Buff --- Use under Level 85
    /call AbilitySet_Add "Spirit of Bear" LowLvlStaminaBuff
    /call AbilitySet_Add "Spirit of Ox" LowLvlStaminaBuff
    /call AbilitySet_Add "Health" LowLvlStaminaBuff
    /call AbilitySet_Add "Stamina" LowLvlStaminaBuff
    /call AbilitySet_Add "Riotous Health" LowLvlStaminaBuff
    /call AbilitySet_Add "Talisman of the Brute" LowLvlStaminaBuff
    /call AbilitySet_Add "Endurance of the Boar" LowLvlStaminaBuff
    /call AbilitySet_Add "Talisman of the Boar" LowLvlStaminaBuff
    /call AbilitySet_Add "Spirit of Fortitude" LowLvlStaminaBuff
    /call AbilitySet_Add "Talisman of Fortitude" LowLvlStaminaBuff
    /call AbilitySet_Add "Talisman of Persistence" LowLvlStaminaBuff
    /call AbilitySet_Add "Talisman of Vehemence" LowLvlStaminaBuff
    /call AbilitySet_Add "Spirit of Vehemence" LowLvlStaminaBuff
    /call AbilitySet_ChooseOuter LowLvlStaminaBuff LowLvlStaminaBuff
    
|- Low Level Attack Buff --- user under level 85
    /call AbilitySet_Add "Primal Avatar" LowLvlAttackBuff
    /call AbilitySet_Add "Ferine Avatar" LowLvlAttackBuff
    /call AbilitySet_Add "Champion" LowLvlAttackBuff
    /call AbilitySet_ChooseOuter LowLvlAttackBuff LowLvlAttackBuff
    
|- Low Level Strength Buff -- use under evel 85
    /call AbilitySet_Add "Talisman of Might" LowLvlStrBuff
    /call AbilitySet_Add "Spirit of Might" LowLvlStrBuff
    /call AbilitySet_Add "Talisman of the Diaku" LowLvlStrBuff
    /call AbilitySet_Add "Strength of the Diaku" LowLvlStrBuff
    /call AbilitySet_Add "Voice of the Berserker" LowLvlStrBuff
    /call AbilitySet_Add "Talisman of the Rhino" LowLvlStrBuff
    /call AbilitySet_Add "Maniacal Strength" LowLvlStrBuff
    /call AbilitySet_Add "Primal Essence" LowLvlStrBuff
    /call AbilitySet_Add "Strength" LowLvlStrBuff
    /call AbilitySet_Add "Rage" LowLvlStrBuff
    /call AbilitySet_Add "Furious Strength" LowLvlStrBuff
    /call AbilitySet_Add "Tumultuous Strength" LowLvlStrBuff
    /call AbilitySet_Add "Fury" LowLvlStrBuff
    /call AbilitySet_Add "Raging Strength" LowLvlStrBuff
    /call AbilitySet_Add "Frenzy" LowLvlStrBuff
    /call AbilitySet_Add "Spirit Strength" LowLvlStrBuff
    /call AbilitySet_Add "Burst of Strength" LowLvlStrBuff
    /call AbilitySet_ChooseOuter LowLvlStrBuff LowLvlStrBuff
    
|- Low Level Dex Buff -- use under level 70
    /call AbilitySet_Add "Talisman of the Raptor" LowLvlDexBuff
    /call AbilitySet_Add "Mortal Deftness" LowLvlDexBuff
    /call AbilitySet_Add "Dexterity" LowLvlDexBuff
    /call AbilitySet_Add "Deftness" LowLvlDexBuff
    /call AbilitySet_Add "Rising Dexterity" LowLvlDexBuff
    /call AbilitySet_Add "Spirit of Monkey" LowLvlDexBuff
    /call AbilitySet_Add "Dexterous Aura" LowLvlDexBuff
    /call AbilitySet_ChooseOuter LowLvlDexBuff LowLvlDexBuff
     
 |- Low Level AGI Buff -- Use under level 85
    /call AbilitySet_Add "Talisman of Foresight" LowLvlAgiBuff
    /call AbilitySet_Add "Preternatural Foresight" LowLvlAgiBuff
    /call AbilitySet_Add "Talisman of Sense" LowLvlAgiBuff
    /call AbilitySet_Add "Spirit of Sense" LowLvlAgiBuff
    /call AbilitySet_Add "Talisman of the Wrulan" LowLvlAgiBuff
    /call AbilitySet_Add "Agility of the Wrulan" LowLvlAgiBuff
    /call AbilitySet_Add "Talisman of the Cat" LowLvlAgiBuff
    /call AbilitySet_Add "Deliriously Nimble" LowLvlAgiBuff
    /call AbilitySet_Add "Agility" LowLvlAgiBuff
    /call AbilitySet_Add "Nimble" LowLvlAgiBuff
    /call AbilitySet_Add "Spirit of Cat" LowLvlAgiBuff
    /call AbilitySet_Add "Feet like Cat" LowLvlAgiBuff
    /call AbilitySet_ChooseOuter LowLvlAgiBuff LowLvlAgiBuff

|-----------------------------------------------------
|- Debuff Spell Section
|-----------------------------------------------------
|- AEMaloSpell AA Starts at LVL 95
    /call AbilitySet_Add "Wind of Malisene" AEMaloSpell
    /call AbilitySet_Add "Wind of Malis" AEMaloSpell
    /call AbilitySet_ChooseOuter AEMaloSpell AEMaloSpell
    
|- MaloSpell AA Starts at LVL 75
    /call AbilitySet_Add "Malosinera" MaloSpell
    /call AbilitySet_Add "Malosinetra" MaloSpell
    /call AbilitySet_Add "Malosinise" MaloSpell
    /call AbilitySet_Add "Malos" MaloSpell
    /call AbilitySet_Add "Malosinia" MaloSpell
    /call AbilitySet_Add "Malo" MaloSpell
    /call AbilitySet_Add "Malosini" MaloSpell
    /call AbilitySet_Add "Malosi" MaloSpell   
    /call AbilitySet_Add "Malaisement" MaloSpell
    /call AbilitySet_Add "Malaise" MaloSpell
    /call AbilitySet_ChooseOuter MaloSpell MaloSpell  
    
|- AESlowSpell AA Starts at LVL 80 -- TARGET AE
    /call AbilitySet_Add "Tigir's Insects" AESlowSpell
    /call AbilitySet_ChooseOuter AESlowSpell AESlowSpell    

|- SlowSpell AA Starts at LVL 78
    /call AbilitySet_Add "Balance of Discord" SlowSpell
    /call AbilitySet_Add "Balance of the Nihil" SlowSpell
    /call AbilitySet_Add "Turgur's Insects" SlowSpell
    /call AbilitySet_Add "Togor's Insects" SlowSpell
    /call AbilitySet_Add "Tagar's Insects" SlowSpell   
    /call AbilitySet_Add "Walking Sleep" SlowSpell
    /call AbilitySet_Add "Drowsy" SlowSpell
    /call AbilitySet_ChooseOuter SlowSpell SlowSpell

| - Diease Slow 
    /call AbilitySet_Add "Cloud of Grummus" DieaseSlow
    /call AbilitySet_Add "Plague of Insects" DieaseSlow
    /call AbilitySet_ChooseOuter DieaseSlow DieaseSlow

|-----------------------------------------------------
|- Proc Spell Section
|-----------------------------------------------------
|- GroupHealProcBuff
    /call AbilitySet_Add "Watchful Spirit" GroupHealProcBuff
    /call AbilitySet_Add "Responsive Spirit" GroupHealProcBuff
    /call AbilitySet_Add "Attentive Spirit" GroupHealProcBuff
    /call AbilitySet_ChooseOuter GroupHealProcBuff GroupHealProcBuff

|- SelfHealProcBuff = Self Heal Ward Spells -- LVL 115 -> LVL 80
    /call AbilitySet_Add "Ward of Heroic Deeds" SelfHealProcBuff
    /call AbilitySet_Add "Ward of Recuperation" SelfHealProcBuff
    /call AbilitySet_Add "Ward of Remediation" SelfHealProcBuff
    /call AbilitySet_Add "Ward of Regeneration" SelfHealProcBuff
    /call AbilitySet_Add "Ward of Rejuvenation" SelfHealProcBuff
    /call AbilitySet_Add "Ward of Reconstruction" SelfHealProcBuff
    /call AbilitySet_Add "Ward of Recovery" SelfHealProcBuff
    /call AbilitySet_Add "Ward of Restoration" SelfHealProcBuff   
    /call AbilitySet_Add "Ward of Resurgence" SelfHealProcBuff
    /call AbilitySet_Add "Ward of Rebirth"  SelfHealProcBuff
    /call AbilitySet_ChooseOuter SelfHealProcBuff SelfHealProcBuff
    
|- DichoSpell: Adds Melee Proc & Heal over Time - Level 101 - 106
    /call AbilitySet_Add "Ecliptic Roar" DichoSpell
    /call AbilitySet_Add "Composite Roar" DichoSpell
    /call AbilitySet_Add "Dissident Roar" DichoSpell
    /call AbilitySet_Add "Roar of the Lion" DichoSpell
    /call AbilitySet_ChooseOuter DichoSpell   DichoSpell

|- MeleeProcBuff: Melee Proc Buff - Level 50 - 111
|- To be used when the Shaman does not have Dicho
    /call AbilitySet_Add "Talisman of the Manul"   MeleeProcBuff
    /call AbilitySet_Add "Talisman of the Kerran" MeleeProcBuff
    /call AbilitySet_Add "Talisman of the Lioness" MeleeProcBuff
    /call AbilitySet_Add "Talisman of the Sabretooth" MeleeProcBuff
    /call AbilitySet_Add "Talisman of the Leopard" MeleeProcBuff
    /call AbilitySet_Add "Talisman of the Snow Leopard" MeleeProcBuff
    /call AbilitySet_Add "Talisman of the Lion" MeleeProcBuff
    /call AbilitySet_Add "Talisman of the Tiger" MeleeProcBuff
    /call AbilitySet_Add "Talisman of the Lynx" MeleeProcBuff
    /call AbilitySet_Add "Talisman of the Cougar" MeleeProcBuff
    /call AbilitySet_Add "Talisman of the Panther" MeleeProcBuff
|- Below Level 71 This is a single target buff
    /call AbilitySet_Add "Spirit of the Panther" MeleeProcBuff
    /call AbilitySet_Add "Spirit of the Leopard" MeleeProcBuff
    /call AbilitySet_Add "Spirit of the Jaguar" MeleeProcBuff
    /call AbilitySet_Add "Spirit of the Puma" MeleeProcBuff
    /call AbilitySet_ChooseOuter MeleeProcBuff MeleeProcBuff   

|- SlowProcBuff: Buff for MA - Level 68 - 122
    /call AbilitySet_Add "Moroseness" SlowProcBuff
    /call AbilitySet_Add "Melancholy" SlowProcBuff
    /call AbilitySet_Add "Ennui" SlowProcBuff
    /call AbilitySet_Add "Incapacity" SlowProcBuff
    /call AbilitySet_Add "Sluggishness" SlowProcBuff
    /call AbilitySet_Add "Fatigue" SlowProcBuff
    /call AbilitySet_Add "Apathy" SlowProcBuff
    /call AbilitySet_Add "Lethargy" SlowProcBuff
    /call AbilitySet_Add "Listlessness" SlowProcBuff
    /call AbilitySet_Add "Languor" SlowProcBuff   
    /call AbilitySet_Add "Lassitude" SlowProcBuff
    /call AbilitySet_Add "Lingering Sloth" SlowProcBuff
    /call AbilitySet_ChooseOuter SlowProcBuff SlowProcBuff

|- PackSelfBuff: Proc self buff - Level 90 - 115
    |- Ignoring the LVL 85 Call the Pack buff due to the decrease in mana per tick.
    /call AbilitySet_Add "Pack of Ancestral Beasts" PackSelfBuff
    /call AbilitySet_Add "Pack of Lunar Wolves" PackSelfBuff
    /call AbilitySet_Add "Pack of The Black Fang" PackSelfBuff
    /call AbilitySet_Add "Pack of Mirtuk" PackSelfBuff
    /call AbilitySet_Add "Pack of Olesira" PackSelfBuff
    /call AbilitySet_Add "Pack of Kriegas" PackSelfBuff   
    /call AbilitySet_Add "Pack of Hilnaah" PackSelfBuff
    /call AbilitySet_Add "Pack of Wurt" PackSelfBuff
    /call AbilitySet_ChooseOuter PackSelfBuff PackSelfBuff   

|-----------------------------------------------------
|- Heal Spell Section
|-----------------------------------------------------
|- AllianceBuff
    /call AbilitySet_Add "Ancient Alliance" AllianceBuff
    /call AbilitySet_Add "Ancient Coalition" AllianceBuff
    /call AbilitySet_ChooseOuter AllianceBuff AllianceBuff

|- Eradicate Curse
    /call AbilitySet_Add "Remove Greater Curse" IcefixSpell
    /call AbilitySet_Add "Eradicate Curse" IcefixSpell
    /call AbilitySet_ChooseOuter IcefixSpell IcefixSpell

|- RecklessHeal1
    /call AbilitySet_Add "Reckless Reinvigoration" RecklessHeal
    /call AbilitySet_Add "Reckless Resurgence" RecklessHeal
    /call AbilitySet_Add "Reckless Renewal" RecklessHeal
    /call AbilitySet_Add "Reckless Rejuvenation" RecklessHeal
    /call AbilitySet_Add "Reckless Regeneration" RecklessHeal
    /call AbilitySet_Add "Reckless Restoration" RecklessHeal
    /call AbilitySet_Add "Reckless Remedy" RecklessHeal
    /call AbilitySet_Add "Reckless Mending" RecklessHeal
    /call AbilitySet_Add "Qirik's Mending" RecklessHeal
    /call AbilitySet_Add "Dannal's Mending" RecklessHeal
    /call AbilitySet_Add "Gemmi's Mending" RecklessHeal
    /call AbilitySet_Add "Ahnkaul's Mending" RecklessHeal
    /call AbilitySet_Add "Ancient: Wilslik's Mending" RecklessHeal
    /call AbilitySet_Add "Yoppa's Mending" RecklessHeal
    /call AbilitySet_Add "Daluda's Mending" RecklessHeal
    /call AbilitySet_Add "Tnarg's Mending" RecklessHeal
    /call AbilitySet_Add "Chloroblast" RecklessHeal
    /call AbilitySet_Add "Kragg's Salve" RecklessHeal
    /call AbilitySet_Add "Superior Healing" RecklessHeal
    /call AbilitySet_Add "Spirit Salve" RecklessHeal
    /call AbilitySet_Add "Greater Healing" RecklessHeal
    /call AbilitySet_Add "Healing" RecklessHeal
    /call AbilitySet_Add "Light Healing" RecklessHeal
    /call AbilitySet_Add "Minor Healing" RecklessHeal
    /call AbilitySet_ChooseOuter RecklessHeal1 RecklessHeal
    /call AbilitySet_ChooseOuter RecklessHeal2 RecklessHeal "${RecklessHeal1}"

|- AESpiritualHeal LVL 115-LVL100
    /call AbilitySet_Add "Spiritual Shower" AESpiritualHeal
    /call AbilitySet_Add "Spiritual Squall" AESpiritualHeal   
    /call AbilitySet_Add "Spiritual Swell" AESpiritualHeal
    /call AbilitySet_Add "Spiritual Surge" AESpiritualHeal
    /call AbilitySet_ChooseOuter AESpiritualHeal AESpiritualHeal

|- RecourseHeal LVL115-87
    /call AbilitySet_Add "Grayleaf's Recourse"  RecourseHeal
    /call AbilitySet_Add "Rowain's Recourse"    RecourseHeal
    /call AbilitySet_Add "Zrelik's Recourse"    RecourseHeal
    /call AbilitySet_Add "Eyrzekla's Recourse"  RecourseHeal
    /call AbilitySet_Add "Krasir's Recourse"    RecourseHeal
    /call AbilitySet_Add "Blezon's Recourse"    RecourseHeal   
    /call AbilitySet_Add "Gotikan's Recourse"   RecourseHeal
    /call AbilitySet_Add "Qirik's Recourse"     RecourseHeal
    /call AbilitySet_ChooseOuter RecourseHeal RecourseHeal

|- InterventionHeal LVL 113 -> 78
    /call AbilitySet_Add "Immortal Intervention" InterventionHeal
    /call AbilitySet_Add "Primordial Intervention" InterventionHeal
    /call AbilitySet_Add "Prehistoric Intervention" InterventionHeal
    /call AbilitySet_Add "Historian's Intervention" InterventionHeal
    /call AbilitySet_Add "Antecessor's Intervention" InterventionHeal
    /call AbilitySet_Add "Progenitor's Intervention" InterventionHeal
    /call AbilitySet_Add "Ascendant's Intervention" InterventionHeal
    /call AbilitySet_Add "Antecedent's Intervention" InterventionHeal   
    /call AbilitySet_Add "Ancestral Intervention" InterventionHeal
    /call AbilitySet_Add "Antediluvian Intervention" InterventionHeal
    /call AbilitySet_ChooseOuter InterventionHeal InterventionHeal

|- GroupRenewalHoT |- LVL 115->70 -- Prior to 70 Breath of Trushar as a non-group HoTs will be used including the
|- the Torpor/Stoicism line. LVL 44 is the lowest level.
    /call AbilitySet_Add "Reverie of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Spirit of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Spectre of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Cloud of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Shear of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Wisp of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Phantom of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Penumbra of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Shadow of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Shade of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Specter of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Ghost of Renewal" GroupRenewalHoT
    /call AbilitySet_Add "Spiritual Serenity" GroupRenewalHoT
    /call AbilitySet_Add "Breath of Trushar" GroupRenewalHoT
    /call AbilitySet_Add "Quiescence" GroupRenewalHoT 
    /call AbilitySet_Add "Torpor" GroupRenewalHoT   
    /call AbilitySet_Add "Stoicism" GroupRenewalHoT
    /call AbilitySet_ChooseOuter GroupRenewalHoT GroupRenewalHoT

|- CanniSpell: Convert Health to Mana - Level  23 - 113
    /call AbilitySet_Add "Hoary Agreement" CanniSpell
    /call AbilitySet_Add "Ancient Bargain" CanniSpell
    /call AbilitySet_Add "Tribal Bargain" CanniSpell
    /call AbilitySet_Add "Tribal Pact" CanniSpell
    /call AbilitySet_Add "Ancestral Pact" CanniSpell
    /call AbilitySet_Add "Ancestral Arrangement" CanniSpell
    /call AbilitySet_Add "Ancestral Covenant" CanniSpell
    /call AbilitySet_Add "Ancestral Obligation" CanniSpell   
    /call AbilitySet_Add "Ancestral Hearkening" CanniSpell
    /call AbilitySet_Add "Ancestral Bargain" CanniSpell
    /call AbilitySet_Add "Ancient: Ancestral Calling" CanniSpell
    /call AbilitySet_Add "Pained Memory" CanniSpell
    /call AbilitySet_Add "Ancient: Chaotic Pain" CanniSpell
    /call AbilitySet_Add "Cannibalize IV" CanniSpell
    /call AbilitySet_Add "Cannibalize" CanniSpell
    /call AbilitySet_ChooseOuter CanniSpell CanniSpell

|- CureSpell
    /call AbilitySet_Add "Blood of Mayong" CureSpell
    /call AbilitySet_Add "Blood of Tevik" CureSpell
    /call AbilitySet_Add "Blood of Rivans" CureSpell
    /call AbilitySet_Add "Blood of Sanera" CureSpell
    /call AbilitySet_Add "Blood of Klar" CureSpell
    /call AbilitySet_Add "Blood of Corbeth" CureSpell   
    /call AbilitySet_Add "Blood of Avoling" CureSpell
    /call AbilitySet_Add "Blood of Nadox" CureSpell
    /call AbilitySet_ChooseOuter CureSpell CureSpell

|-----------------------------------------------------
|- DD Spell Section
|-----------------------------------------------------
|- TwinHealNuke: Nuke the MA Not the assist target - Levels 85 - 115
    /call AbilitySet_Add "Gelid Gift"   TwinHealNuke
    /call AbilitySet_Add "Polar Gift"  TwinHealNuke
    /call AbilitySet_Add "Wintry Gift" TwinHealNuke
    /call AbilitySet_Add "Frostbitten Gift" TwinHealNuke
    /call AbilitySet_Add "Glacial Gift" TwinHealNuke
    /call AbilitySet_Add "Frigid Gift" TwinHealNuke
    /call AbilitySet_Add "Freezing Gift" TwinHealNuke   
    /call AbilitySet_Add "Frozen Gift" TwinHealNuke
    /call AbilitySet_Add "Frost Gift" TwinHealNuke
    /call AbilitySet_ChooseOuter TwinHealNuke TwinHealNuke
 
|- PoisonNuke LVL115->LVL34
    /call AbilitySet_Add "Red Eye's Spear of Venom" PoisonNuke
    /call AbilitySet_Add "Fleshrot's Spear of Venom" PoisonNuke
    /call AbilitySet_Add "Narandi's Spear of Venom" PoisonNuke
    /call AbilitySet_Add "Nexona's Spear of Venom" PoisonNuke
    /call AbilitySet_Add "Serisaria's Spear of Venom" PoisonNuke
    /call AbilitySet_Add "Slaunk's Spear of Venom" PoisonNuke
    /call AbilitySet_Add "Hiqork's Spear of Venom" PoisonNuke
    /call AbilitySet_Add "Spinechiller's Spear of Venom" PoisonNuke   
    /call AbilitySet_Add "Severilous' Spear of Venom" PoisonNuke
    /call AbilitySet_Add "Vestax's Spear of Venom" PoisonNuke
    /call AbilitySet_Add "Ahnkaul's Spear of Venom" PoisonNuke
    /call AbilitySet_Add "Yoppa's Spear of Venom" PoisonNuke
    /call AbilitySet_Add "Spear of Torment" PoisonNuke
    /call AbilitySet_Add "Blast of Venom" PoisonNuke
    /call AbilitySet_Add "Shock of Venom" PoisonNuke   
    /call AbilitySet_Add "Blast of Poison" PoisonNuke
    /call AbilitySet_Add "Shock of the Tainted" PoisonNuke
    /call AbilitySet_ChooseOuter PoisonNuke PoisonNuke
    
|- FastPoisonNuke LVL115->LVL73
    /call AbilitySet_Add "Oka's Bite" FastPoisonNuke
    /call AbilitySet_Add "Ander's Bite" FastPoisonNuke
    /call AbilitySet_Add "Direfang's Bite" FastPoisonNuke
    /call AbilitySet_Add "Mawmun's Bite" FastPoisonNuke
    /call AbilitySet_Add "Reefmaw's Bite" FastPoisonNuke
    /call AbilitySet_Add "Seedspitter's Bite" FastPoisonNuke
    /call AbilitySet_Add "Bite of the Grendlaen" FastPoisonNuke
    /call AbilitySet_Add "Bite of the Blightwolf" FastPoisonNuke
    /call AbilitySet_Add "Bite of the Ukun" FastPoisonNuke   
    /call AbilitySet_Add "Bite of the Brownie" FastPoisonNuke
    /call AbilitySet_Add "Sting of the Queen" FastPoisonNuke
    /call AbilitySet_ChooseOuter FastPoisonNuke FastPoisonNuke
    
|-FrostNuke - Levels 4 - 114
    /call AbilitySet_Add "Ice Barrage" FrostNuke
    /call AbilitySet_Add "Heavy Sleet" FrostNuke
    /call AbilitySet_Add "Ice Salvo" FrostNuke
    /call AbilitySet_Add "Ice Shards" FrostNuke
    /call AbilitySet_Add "Ice Squall" FrostNuke
    /call AbilitySet_Add "Ice Burst" FrostNuke
    /call AbilitySet_Add "Ice Mass" FrostNuke
    /call AbilitySet_Add "Ice Floe" FrostNuke
    /call AbilitySet_Add "Ice Sheet" FrostNuke
    /call AbilitySet_Add "Tundra Crumble" FrostNuke   
    /call AbilitySet_Add "Glacial Avalanche" FrostNuke
    /call AbilitySet_Add "Ice Age" FrostNuke
    /call AbilitySet_Add "Velium Strike" FrostNuke
    /call AbilitySet_Add "Ice Strike" FrostNuke
    /call AbilitySet_Add "Blizzard Blast" FrostNuke
    /call AbilitySet_Add "Winter's Roar" FrostNuke
    /call AbilitySet_Add "Frost Strike" FrostNuke   
    /call AbilitySet_Add "Spirit Strike" FrostNuke
    /call AbilitySet_Add "Frost Rift" FrostNuke
    /call AbilitySet_ChooseOuter FrostNuke FrostNuke

    /call AbilitySet_Add "Cure Disease" TLPCureDisease
    /call AbilitySet_Add "Counteract Disease" TLPCureDisease
    /call AbilitySet_Add "Eradicate Disease" TLPCureDisease
    /call AbilitySet_ChooseOuter TLPCureDisease TLPCureDisease
    
    /call AbilitySet_Add "Counteract Poison" TLPCurePoison
    /call AbilitySet_Add "Abolish Poison" TLPCurePoison
    /call AbilitySet_Add "Eradicate Poison" TLPCurePoison
    /call AbilitySet_ChooseOuter TLPCurePoison TLPCurePoison

|-----------------------------------------------------
|- Dot Spell Section
|-----------------------------------------------------
|- ChaoticDoT Long Dot(42s) LVL 109 -> LVL104
|- Two resist types because it throws 2 dots
|- Stacking: Nectar of Pain - Stacking: Blood of Saryrn 
    /call AbilitySet_Add "Chaotic Poison" ChaoticDoT
    /call AbilitySet_Add "Chaotic Venom" ChaoticDoT
    /call AbilitySet_Add "Chaotic Venin" ChaoticDoT
    /call AbilitySet_Add "Chaotic Toxin" ChaoticDoT
    /call AbilitySet_ChooseOuter ChaoticDoT ChaoticDoT


|- Nectar Dot Line
    /call AbilitySet_Add "Nectar of Obscurity" NectarDot
    /call AbilitySet_Add "Nectar of Pain" NectarDot
    /call AbilitySet_Add "Nectar of Agony" NectarDot
    /call AbilitySet_Add "Nectar of Rancor" NectarDot
    /call AbilitySet_Add "Nectar of the Slitheren" NectarDot
    /call AbilitySet_Add "Nectar of Torment" NectarDot
    /call AbilitySet_Add "Nectar of Sholoth" NectarDot
    /call AbilitySet_Add "Nectar of Anguish" NectarDot
    /call AbilitySet_Add "Nectar of Woe" NectarDot
    /call AbilitySet_Add "Nectar of Suffering" NectarDot
    /call AbilitySet_Add "Nectar of Misery" NectarDot
    /call AbilitySet_Add "Nectar of Destitution" NectarDot
    /call AbilitySet_ChooseOuter NectarDot NectarDot    
    
|- PandemicDot Long Dot(84s) Level 103 - 108
|- Two resist types because it throws 2 dots    
|- Stacking: Kralbor's Pandemic  -    Stacking: Breath of Ultor  
    /call AbilitySet_Add "Skraiw's Pandemic" PandemicDot
    /call AbilitySet_Add "Elkikatar's Pandemic" PandemicDot
    /call AbilitySet_Add "Hemocoraxius' Pandemic" PandemicDot
    /call AbilitySet_Add "Bledrek's Pandemic" PandemicDot
    /call AbilitySet_Add "Doomshade's Pandemic" PandemicDot
    /call AbilitySet_Add "Tegi Pandemic" PandemicDot
    /call AbilitySet_ChooseOuter PandemicDot PandemicDot   
    
|- MaloDot Stacking: Yubai's Affliction - LongDot(96s) Level 99 - 114
    /call AbilitySet_Add "Svartmane's Malosinara" MaloDot
    /call AbilitySet_Add "Rirwech's Malosinata" MaloDot   
    /call AbilitySet_Add "Livio's Malosenia" MaloDot
    /call AbilitySet_Add "Falhotep's Malosenia" MaloDot
    /call AbilitySet_Add "Txiki's Malosinara" MaloDot
    /call AbilitySet_Add "Krizad's Malosinera" MaloDot
    /call AbilitySet_ChooseOuter MaloDot MaloDot

|- CurseDoT2 Stacking: Enalam's Curse - Long Dot(54s) - 100 - 115
    /call AbilitySet_Add "Lenrel's Curse" CurseDoT2
    /call AbilitySet_Add "Marlek's Curse" CurseDoT2
    /call AbilitySet_Add "Erogo's Curse" CurseDoT2
    /call AbilitySet_Add "Sraskus' Curse" CurseDoT2   
    /call AbilitySet_Add "Enalam's Curse" CurseDoT2
    /call AbilitySet_Add "Fandrel's Curse" CurseDoT2
    /call AbilitySet_ChooseOuter  CurseDoT2 CurseDoT2

|- CurseDoT1  Stacking: Curse - Long Dot(30s) - Level 34 - 115
    /call AbilitySet_Add "Malediction" CurseDoT1
    /call AbilitySet_Add "Obeah" CurseDoT1
    /call AbilitySet_Add "Evil Eye" CurseDoT1
    /call AbilitySet_Add "Jinx" CurseDoT1
    /call AbilitySet_Add "Garugaru" CurseDoT1
    /call AbilitySet_Add "Naganaga" CurseDoT1
    /call AbilitySet_Add "Hoodoo" CurseDoT1
    /call AbilitySet_Add "Hex" CurseDoT1
    /call AbilitySet_Add "Mojo" CurseDoT1
    /call AbilitySet_Add "Pocus" CurseDoT1
    /call AbilitySet_Add "Juju" CurseDoT1
    /call AbilitySet_Add "Curse of Sisslak" CurseDoT1
    /call AbilitySet_Add "Bane" CurseDoT1
    /call AbilitySet_Add "Anathema" CurseDoT1   
    /call AbilitySet_Add "Odium" CurseDoT1
    /call AbilitySet_Add "Curse" CurseDoT1
    /call AbilitySet_ChooseOuter CurseDoT1 CurseDoT1

|- FastPoisonDoT Stacking: Blood of Saryrn - Fast Dot(12s) - Level 89 - 115
    /call AbilitySet_Add "Korsh's Venom"   FastPoisonDoT
    /call AbilitySet_Add "Namdrows' Venom" FastPoisonDoT
    /call AbilitySet_Add "Xalgoti's Venom" FastPoisonDoT
    /call AbilitySet_Add "Mawmun's Venom" FastPoisonDoT
    /call AbilitySet_Add "Serpentil's Venom" FastPoisonDoT
    /call AbilitySet_Add "Banescale's Venom" FastPoisonDoT
    /call AbilitySet_Add "Stranglefang's Venom" FastPoisonDoT   
    /call AbilitySet_Add "Undaleen's Venom" FastPoisonDoT
    /call AbilitySet_ChooseOuter FastPoisonDoT FastPoisonDoT

|- SaryrnDot Stacking: Blood of Saryrn - Long Dot(42s) - Level 8 - 115
    /call AbilitySet_Add "Desperate Vampyre Blood" SaryrnDot
    /call AbilitySet_Add "Restless Blood" SaryrnDot
    /call AbilitySet_Add "Reef Crawler Blood" SaryrnDot
    /call AbilitySet_Add "Phase Spider Blood" SaryrnDot
    /call AbilitySet_Add "Naeya Blood" SaryrnDot
    /call AbilitySet_Add "Spinechiller Blood" SaryrnDot   
    /call AbilitySet_Add "Blood of Jaled'Dar" SaryrnDot
    /call AbilitySet_Add "Blood of Kerafyrm" SaryrnDot
    /call AbilitySet_Add "Vengeance of Ahnkaul" SaryrnDot
    /call AbilitySet_Add "Blood of Yoppa" SaryrnDot
    /call AbilitySet_Add "Blood of Saryrn" SaryrnDot
    /call AbilitySet_Add "Ancient: Scourge of Nife" SaryrnDot   
    /call AbilitySet_Add "Bane of Nife" SaryrnDot    
    /call AbilitySet_Add "Envenomed Bolt" SaryrnDot
    /call AbilitySet_Add "Venom of the Snake" SaryrnDot
    /call AbilitySet_Add "Envenomed Breath" SaryrnDot
    /call AbilitySet_Add "Tainted Breath" SaryrnDot
    /call AbilitySet_ChooseOuter SaryrnDot SaryrnDot     

|- FastDiseaseDoT Stacking: Breath of Ultor - Fast Dot(12s) - Level 87 - 115
    /call AbilitySet_Add "Krizad's Malady" FastDiseaseDoT
    /call AbilitySet_Add "Cruor's Malady" FastDiseaseDoT
    /call AbilitySet_Add "Malvus's Malady" FastDiseaseDoT
    /call AbilitySet_Add "Hoshkar's Malady" FastDiseaseDoT
    /call AbilitySet_Add "Sephry's Malady" FastDiseaseDoT
    /call AbilitySet_Add "Elsrop's Malady" FastDiseaseDoT
    /call AbilitySet_Add "Giaborn's Malady" FastDiseaseDoT   
    /call AbilitySet_Add "Nargul's Malady" FastDiseaseDoT
    /call AbilitySet_ChooseOuter  FastDiseaseDoT FastDiseaseDoT

|- UltorDot Stacking: Breath of Ultor - Long Dot(84s) - Level 4 - 111
    /call AbilitySet_Add "Breath of the Hotariton" UltorDot
    /call AbilitySet_Add "Breath of the Tegi" UltorDot
    /call AbilitySet_Add "Breath of Bledrek" UltorDot
    /call AbilitySet_Add "Breath of Hemocoraxius" UltorDot
    /call AbilitySet_Add "Breath of Natigo" UltorDot
    /call AbilitySet_Add "Breath of Silbar" UltorDot
    /call AbilitySet_Add "Breath of the Shiverback" UltorDot   
    /call AbilitySet_Add "Breath of Queen Malarian" UltorDot
    /call AbilitySet_Add "Breath of Big Bynn" UltorDot
    /call AbilitySet_Add "Breath of Ternsmochin" UltorDot
    /call AbilitySet_Add "Breath of Wunshi" UltorDot
    /call AbilitySet_Add "Breath of Ultor" UltorDot
    /call AbilitySet_Add "Pox of Bertoxxulous" UltorDot   
    /call AbilitySet_Add "Plague" UltorDot    
    /call AbilitySet_Add "Scourge" UltorDot
    /call AbilitySet_Add "Affliction" UltorDot
    /call AbilitySet_Add "Sicken" UltorDot    
    /call AbilitySet_ChooseOuter UltorDot UltorDot

|-----------------------------------------------------
|- Pet Spells
|-----------------------------------------------------
|- PetSpell - 32 - 112
    /call AbilitySet_Add "Suja's Faithful" PetSpell
    /call AbilitySet_Add "Diabo Sivuela's Faithful" PetSpell
    /call AbilitySet_Add "Grondo's Faithful" PetSpell
    /call AbilitySet_Add "Mirtuk's Faithful" PetSpell
    /call AbilitySet_Add "Olesira's Faithful" PetSpell
    /call AbilitySet_Add "Kriegas' Faithful" PetSpell   
    /call AbilitySet_Add "Hilnaah's Faithful" PetSpell
    /call AbilitySet_Add "Wurt's Faithful" PetSpell
    /call AbilitySet_Add "Aina's Faithful" PetSpell
    /call AbilitySet_Add "Vegu's Faithful" PetSpell
    /call AbilitySet_Add "Kyrah's Faithful" PetSpell
    /call AbilitySet_Add "Farrel's Companion" PetSpell
    /call AbilitySet_Add "True Spirit" PetSpell
    /call AbilitySet_Add "Spirit of the Howler" PetSpell
    /call AbilitySet_Add "Frenzied Spirit" PetSpell
    /call AbilitySet_Add "Guardian spirit" PetSpell   
    /call AbilitySet_Add "Vigilant Spirit" PetSpell
    /call AbilitySet_Add "Companion Spirit" PetSpell
    /call AbilitySet_ChooseOuter PetSpell PetSpell

|- PetBuffSpell - 50 - 112
    /call AbilitySet_Add "Spirit Augmentation" PetBuffSpell
    /call AbilitySet_Add "Spirit Reinforcement" PetBuffSpell
    /call AbilitySet_Add "Spirit Bracing" PetBuffSpell   
    /call AbilitySet_Add "Spirit Bolstering" PetBuffSpell
    /call AbilitySet_Add "Spirit Quickening" PetBuffSpell
    /call AbilitySet_ChooseOuter PetBuffSpell PetBuffSpell
    
    |- Chat Begs
    /if (${RG_CanUseAA[Shrink]}) {
        /call ChatBegList_Add SHMBegs shrinkme      AA     "Shrink"         sender TRUE
    } else {
        /call ChatBegList_Add SHMBegs shrinkme      Spell    "Shrink"       sender TRUE
    }
    /call ChatBegList_Add SHMBegs shrinkgroup     AA     "Group Shrink"     sender TRUE
    /call ChatBegList_Add SHMBegs sow             AA     "Lupine Spirit"    sender TRUE
    /call ChatBegList_Add SHMBegs Sow             Spell  "${RunSpeedBuff}"  sender TRUE
    /call ChatBegList_Add SHMBegs rgc             Spell  "${IcefixSpell}"   sender ${Parse[0,"( ${Target.Cursed} )"]}
    /call ChatBegList_Add SHMBegs cureme          AA     "Radiant Cure"      sender TRUE
    /call ChatBegList_Add SHMBegs tlpcurep        Spell  "${TLPCurePoison}"  sender ${Parse[0,"( ${Target.Poisoned} )"]}
    /call ChatBegList_Add SHMBegs tlpcured        Spell  "${TLPCureDisease}" sender ${Parse[0,"( ${Target.Diseased} )"]}

    /call Cure_AddAll "${CureSpell}" Spell "${CureSpell}" Spell "${CureSpell}" Spell "${CureSpell}" Spell
/return

|-----------------------------------------------------------------------------
|- SUB - healSpellConfig - Configure Spell Gems for the healing shaman
|-----------------------------------------------------------------------------
Sub SHM_ModeConfigMODEHEAL 
    /varset IsHealing TRUE
    /varset IsCuring TRUE
    /varset AutoAssistAt[SETTINGVAL] 90

    |- Low Level Heal spells and heals spells that will always be on bar even if not a main healer.
    /varset Spell1 ${RecklessHeal1}
    /if ( !${Me.AltAbility[Turgur's Swarm].ID} ) {
        /varset Spell2 ${SlowSpell}
    } else {
        /varset Spell2 ${RecklessHeal2}
    }
    
    |- Recourse Heal Starts at Level 87
    /if (${RecourseHeal.NotEqual[NULL]}) {
        /varset Spell3 ${RecourseHeal}
    } else {
        /varset Spell3 ${GroupRenewalHoT}
    }
    
    |- Intervention Heal Starts at Level 78
    /varset Spell4 ${InterventionHeal}
    
    |- Chaotic Dot Line starts at Level 104
    /if (${ChaoticDoT.NotEqual[NULL]}) {
        /varset Spell5 ${ChaoticDoT}
    } else {
        /varset Spell5 ${SaryrnDot}
    }     
    
    |- Cannibalize Spell for use between aa uses
    /varset Spell6 ${CanniSpell}
    
    |- Tank Melee Slow Proc Spell starts at level 68
    /varset Spell7 ${GrowthBuff}

    |- Group Renewal Hot Starts at Level 44
    /if (${RecourseHeal.NotEqual[NULL]}) {
        /varset Spell8 ${GroupRenewalHoT}
    } else {
        /varset Spell8 ${FocusSpell}
    }

     |- Pandemic Dot Line Starts at level 103 - IcefixSpell 
    /if (${IcefixSpell.NotEqual[NULL]}) {
        /varset Spell9 ${IcefixSpell}
    } else /if (${PandemicDot.NotEqual[NULL]}) {
        /varset Spell9 ${PandemicDot}
    } else {
        /varset Spell9 ${UltorDot}
    }    
    
    |- Dicho Spell Starts at Level 101
    /if (${DichoSpell.NotEqual[NULL]}) {
        /varset Spell10 ${DichoSpell}
    } else {
        /varset Spell10 ${MeleeProcBuff}
    }    
    
    |- Area Affect Heal starts at level 100
    /varset Spell11 ${AESpiritualHeal}
    
    |- Nuke to proc TwinHeal Starts at level 85
    /varset Spell12 ${TwinHealNuke}
    
    |- Temp HP Buff Spell starts at level 81
    /varset Spell13 Null

    |- Rotations
    |- Downtime Rotation - Handles self buffs, pet, canni
    /call SHM_DefaultDownRotationConfig SHM_Downtime_MODEHEAL_Rotation
    /call SHM_DefaultBuffGroupConfig
    |- Heals
    /call SHM_DefaultHealRotationConfig
    /call SHM_DefaultSplashRotationConfig "SHM_Splash_MODEHEAL_Rotation"
    |- Debuff Spells
    /call SHM_DefaultDebuffRotationConfig "SHM_Debuff_MODEHEAL_Rotation"
    |- DPS Rotation
    /call SHM_DefaultDPSRotationConfig "SHM_DPS_MODEHEAL_Rotation"

/return

|-----------------------------------------------------------------------------
|- SUB - dotSpellConfig - Configure Spell Gems for the healing shaman
|-----------------------------------------------------------------------------
Sub SHM_ModeConfigMODEDOT  
    /varset IsHealing TRUE
    /varset IsCuring TRUE

    /varset Spell1 ${RecklessHeal1}
    
    |- Frost Nuke starts at level 4
    /varset Spell2 ${FrostNuke}
    
    |- Recourse Heal Starts at Level 87
    /if (${RecourseHeal.NotEqual[NULL]}) {
        /varset Spell3 ${RecourseHeal}
    } else {
        /varset Spell3 ${GroupRenewalHoT}
    }
    
    |- Intervention Heal Starts at Level 78
    /varset Spell4 ${InterventionHeal}
    
    |- Chaotic Dot Line starts at Level 104
    /if (${ChaoticDoT.NotEqual[NULL]}) {
        /varset Spell5 ${ChaoticDoT}
    } else {
        /varset Spell5 ${SaryrnDot}
    }     
    
    |- Cannibalize Spell for use between aa uses
    /varset Spell6 ${CanniSpell}
    
    |- Tank Melee Slow Proc Spell starts at level 68
    /varset Spell7 ${SlowProcBuff}

    |- Group Renewal Hot Starts at Level 44
    /if (${CurseDoT1.NotEqual[NULL]}) {
        /varset Spell8 ${CurseDoT1}
    } else {
        /varset Spell8 ${FocusSpell}
    }

    |- Pandemic Dot Line Starts at level 103
    /if (${PandemicDot.NotEqual[NULL]}) {
        /varset Spell9 ${PandemicDot}
    } else {
        /varset Spell9 ${UltorDot}
    }    
    
    |- Dicho Spell Starts at Level 101
    /if (${DichoSpell.NotEqual[NULL]}) {
        /varset Spell10 ${DichoSpell}
    } else {
        /varset Spell10 ${MeleeProcBuff}
    }    
    
    |- Curse Dot 2 starts at level 100
    /varset Spell11 ${CurseDoT2}
    
    /if (${IcefixSpell.NotEqual[NULL]}) {
        /varset Spell12 ${IcefixSpell}
    } else {
        /varset Spell12 ${PoisonNuke}
    }
    
    |- Temp HP Buff Spell starts at level 81
    /varset Spell13 ${GrowthBuff}

    |- Rotations
    |- Downtime Rotation - Handles self buffs, pet, canni
    /call SHM_DefaultDownRotationConfig SHM_Downtime_MODEDOT_Rotation
    /call SHM_DefaultBuffGroupConfig
    |- Heals
    /call SHM_DefaultHealRotationConfig
    /call SHM_DefaultSplashRotationConfig "SHM_Splash_MODEDOT_Rotation"
    |- Debuff Spells
    /call SHM_DefaultDebuffRotationConfig "SHM_Debuff_MODEDOT_Rotation"
    /call SHM_DefaultDPSRotationConfig "SHM_DPS_MODEDOT_Rotation"
/return

Sub SHM_ModeConfigMODETLP
    /varset IsHealing TRUE
    /varset IsCuring TRUE
    |- Heals
    /varset Spell1 ${RecklessHeal1}
    /varset Spell2 ${GroupRenewalHoT}
    /if ( ${DoMagicDot[SETTINGVAL]} ) {
        /varset Spell3 ${CurseDoT1}
    } else {
        /varset Spell3 ${SaryrnDot}
    }
    /varset Spell4 ${UltorDot}
    /if ( ${DoDieaseSlow[SETTINGVAL]} ) {
        /varset Spell5 ${DieaseSlow}
    } else {
    /varset Spell5 ${SlowSpell}
    }
    /varset Spell6 ${LowLvlAttackBuff}     
    /varset Spell7 ${CanniSpell} 
    /varset Spell8 ${MaloSpell}
    /varset Spell9 NULL
    |- Rotations
    |- Downtime Rotation - Handles self buffs, pet, canni
    /call SHM_DefaultDownRotationConfig SHM_Downtime_MODETLP_Rotation
    /call SHM_DefaultBuffGroupConfig
    |- Heals
       |- Setup Heals
    /call Heal_AddHealPoint ${TlpHealPoint[SETTINGVAL]}
 
    /call Heal_AddSpell ${TlpHealPoint[SETTINGVAL]} "${RecklessHeal1}"  ${Parse[0,"( ${Spawn[id ${target_id}].PctHPs}<=${RecklessHealPoint[SETTINGVAL]} )"]}
    /call Heal_AddSpell     ${TlpHealPoint[SETTINGVAL]} "${GroupRenewalHoT}" ${Parse[0,"( !${Spawn[id ${target_id}].CachedBuff[${GroupRenewalHoT}].ID} )"]}
    /call Heal_AddAA     ${TlpHealPoint[SETTINGVAL]} "Call of the Ancients" ${Parse[0,"( ${WardsPlease} )"]}
   
    |- Debuff Spells
        |- DPS Group Buffs
    |- Debuffs
    /call SHM_DefaultDebuffRotationConfig "SHM_Debuff_MODETLP_Rotation"
| - Dps - Rotation
   /call AddtoRotation "SHM_DPS_MODETLP_Rotation" "/call VerifyAvatar" "Command"    ${Parse[0,"( ${DoCombatAvatar[SETTINGVAL]} && !${AvatarCheck} && ${Me.SpellReady[${LowLvlAttackBuff}]} && ${CaList[SETTINGVAL].NotEqual[NULL]} )"]}
   /call AddtoRotation "SHM_DPS_MODETLP_Rotation" "/call VerifyPanther" "Command"    ${Parse[0,"( ${DoCombatPanther[SETTINGVAL]} && !${PantherCheck} && ${Me.SpellReady[${MeleeProcBuff}]} && ${CpList[SETTINGVAL].NotEqual[NULL]} )"]}
    
   | - Group Buffs
    /call AddToRotation "SHM_DPS_MODETLP_Rotation" "${Epic}"         Item  ${Parse[0,"( ${BurnAuto[SETTINGVAL]} || SMALLBURN )"]}
    | - Dots & DD
    /call AddToRotation "SHM_DPS_MODETLP_Rotation" "${SaryrnDot}"    Spell ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && DOTSPELLCHECK && MANACHECK )"]}
    /call AddToRotation "SHM_DPS_MODETLP_Rotation" "${CurseDoT1}"    Spell ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && DOTSPELLCHECK && MANACHECK )"]}
    /call AddToRotation "SHM_DPS_MODETLP_Rotation" "${FrostNuke}"    Spell ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${DoNuke[SETTINGVAL]} && MANACHECK )"]}   
    |- Mana Regen
    /call AddToRotation "SHM_DPS_MODETLP_Rotation" "Cannibalization" AA ${Parse[0,"( ${DoAACanni[SETTINGVAL]} && ${Me.PctMana}<${AACanniManaPct[SETTINGVAL]} && ${Me.PctHPs}>=${AACanniMinHP[SETTINGVAL]} && ${RG_AAReady[Cannibalization]} )"]} 
    /call AddToRotation "SHM_DPS_MODETLP_Rotation" "${CanniSpell}"   Spell ${Parse[0,"( ${DoSpellCanni[SETTINGVAL]} && ${Me.PctMana}<${CanniManaPct[SETTINGVAL]} && ${Me.PctHPs}>=${CanniMinHP[SETTINGVAL]} && ${Me.SpellReady[${CanniSpell}]} )"]}
    
   
    | - Burn Rotation
    /call AddToRotation "SHM_Burn_MODETLP_Rotation" "Ancestral Aid"      AA ${Parse[0,"( ${BurnAuto[SETTINGVAL]} || MEDBURN )"]}   
    /call AddToRotation "SHM_Burn_MODETLP_Rotation" "Spirit Call"      AA ${Parse[0,"( ${BurnAuto[SETTINGVAL]} || SMALLBURN )"]}  
    /call AddToRotation "SHM_Burn_MODETLP_Rotation" "Rabid Bear"      AA ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${PCAAReady[Rabid Bear]} && ${DoMelee[SETTINGVAL]} && ${Me.Combat} )"]}   
    /call AddToRotation "SHM_Burn_MODETLP_Rotation" "${UltorDot}"    Spell ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && DOTSPELLCHECK && MANACHECK )"]}
    
/return

|-----------------------------------------------------------------------------
|- SUB - healSpellConfig - Configure Spell Gems for the healing shaman
|-----------------------------------------------------------------------------
Sub SHM_ModeConfigMODEOAMUK
    /varset IsHealing TRUE
    /varset IsCuring TRUE

    /varset Spell1 ${RecklessHeal1}
    /varset Spell2 ${RecklessHeal2}
    /varset Spell3 ${RecourseHeal}
    /varset Spell4 ${InterventionHeal}
    /varset Spell5 ${GroupRenewalHoT}
    /varset Spell6 ${IcefixSpell}
    /varset Spell7 ${CanniSpell}
    /varset Spell8 ${SlowProcBuff}
    /varset Spell9 ${DichoSpell}
    /varset Spell10 ${TwinHealNuke}
    /varset Spell11 ${AESpiritualHeal}
    /varset Spell12 ${ChaoticDoT}
    /varset Spell13 ${MaloDot}

   |- Rotations
    |- Self Buffs
    /call SHM_DefaultDownRotationConfig SHM_Downtime_MODEOAMUK_Rotation
    /call AddToRotation "SHM_Downtime_MODEOAMUK_Rotation" "${GroupRenewalHoT}" Spell ${Parse[0,"( !${Me.Song[${GroupRenewalHoT}].ID} )"]}
    |- Group Buffs
    /call SHM_DefaultBuffGroupConfig
    |- Setup Heals
    /call Heal_AddHealPoint ${MainHealPoint[SETTINGVAL]}
    /call Heal_AddHealPoint ${GroupHealPoint[SETTINGVAL]}
    /call Heal_AddHealPoint ${BigHealPoint[SETTINGVAL]}

    /call Heal_AddSpell ${GroupHealPoint[SETTINGVAL]} "${RecourseHeal}" ${Parse[1,"( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]} )"]}
    /call Heal_AddSpell ${BigHealPoint[SETTINGVAL]} "${InterventionHeal}" ${Parse[1,"( ${Target.PctHPs}<65 )"]}
    /call Heal_AddAA    ${BigHealPoint[SETTINGVAL]} "Soothsayer's Intervention" TRUE
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${RecklessHeal1}" TRUE
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${RecklessHeal2}" TRUE
    /call Heal_AddAA    ${MainHealPoint[SETTINGVAL]} "Spirit Guardian" TRUE
    /call Heal_AutoBackFill

    | - Twincast Rotation
    /call AddToRotation SHM_Splash_MODEOAMUK_Rotation "${TwinHealNuke}"       Spell ${Parse[0,"( ${IsHealing} && !${Me.Song[Healing Twincast].ID} )"]}
    /call AddToRotation SHM_Splash_MODEOAMUK_Rotation "${AESpiritualHeal}"    Spell ${Parse[0,"( ${IsHealing} && ${Me.Song[Healing Twincast].ID} )"]}
    /call AddToRotation SHM_Splash_MODEOAMUK_Rotation "${GroupRenewalHoT}"    Spell ${Parse[0,"( ${IsHealing} && ${Me.Song[${GroupRenewalHoT}].ID} )"]}
    
    |- Debuff Spells
    /call SHM_DefaultDPSRotationConfig "SHM_DPS_MODEOAMUK_Rotation"
    /call SHM_DefaultDebuffRotationConfig "SHM_Debuff_MODEOAMUK_Rotation"
    
/return

Sub SHM_DefaultHealRotationConfig
 |- Setup Heals
    /call Heal_AddHealPoint ${MainHealPoint[SETTINGVAL]}

    |- Main Heals
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${RecourseHeal}" ${Parse[0,"( ${Spawn[id ${target_id}].ID} == ${assistid} )"]}
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${AESpiritualHeal}" ${Parse[0,"( ${Spawn[id ${target_id}].ID} == ${assistid} )"]}
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${GroupRenewalHoT}" ${Parse[0,"( ${DoHot[SETTINGVAL]} && ${Spell[${GroupRenewalHoT}].StacksTarget} && !${Spawn[id ${target_id}].CachedBuff[${GroupRenewalHoT}].ID} && ${Spawn[pc id ${target_id}].ID} && ${target_id} == ${Spawn[id ${target_id}].ID} )"]}
    /call Heal_AddAA    ${MainHealPoint[SETTINGVAL]} "Spirit Guardian" ${Parse[0,"( ${Spawn[id ${target_id}].ID} == ${assistid} )"]}
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${RecklessHeal1}"  ${Parse[0,"( ${Spawn[id ${target_id}].PctHPs}<=${RecklessHealPoint[SETTINGVAL]} )"]} 
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${RecklessHeal2}" TRUE
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${InterventionHeal}" ${Parse[0,"( ${Spawn[id ${target_id}].PctHPs}<${BigHealPoint[SETTINGVAL]} )"]}
    /call Heal_AddAA    ${MainHealPoint[SETTINGVAL]} "Soothsayer's Intervention" TRUE
  
/return

Sub SHM_DefaultSplashRotationConfig(string rotation_name)
    /call AddToRotation "${rotation_name}" "${TwinHealNuke}"       Spell ${Parse[0,"( ${IsHealing} && ${Spawn[id ${autotargetid}].Distance}<${AssistRange[SETTINGVAL]} && !${Me.Song[Healing Twincast].ID} && ${Spawn[${autotargetid}].PctHPs} <= ${AutoAssistAt[SETTINGVAL]})"]}
    /call AddToRotation "${rotation_name}" "${AESpiritualHeal}"    Spell ${Parse[0,"( ${IsHealing} && ${Me.Song[Healing Twincast].ID} )"]}

/return

Sub SHM_DefaultDebuffRotationConfig(string rotation_name)
    /call AddToRotation "${rotation_name}" "${AEMaloSpell}"             Spell ${Parse[0,"( ${DoMalo[SETTINGVAL]} && ${DoAoEMalo[SETTINGVAL]} )"]}
    /call AddToRotation "${rotation_name}" "${MaloSpell}"               Spell ${Parse[0,"( ${DoMalo[SETTINGVAL]} && DETSPELLCHECK )"]}    
    /call AddToRotation "${rotation_name}" "${AESlowSpell}"             Spell ${Parse[0,"( ${DoSlow[SETTINGVAL]} && ${DoAoESlow[SETTINGVAL]})"]}
    /call AddToRotation "${rotation_name}" "${SlowSpell}"               Spell ${Parse[0,"( ${DoSlow[SETTINGVAL]} && DETSPELLCHECK )"]}  
    /call AddToRotation "${rotation_name}" "Turgur's Virulent Swarm"    AA ${Parse[0,"( ${DoSlow[SETTINGVAL]} && ${DoAoESlow[SETTINGVAL]} )"]}  
    /call AddToRotation "${rotation_name}" "Turgur's Swarm"             AA ${Parse[0,"( ${DoSlow[SETTINGVAL]} && !${DoAoESlow[SETTINGVAL]} && !${Target.Buff[${Spell[Turgur's Swarm].Trigger[1]}].ID} )"]}  
    /call AddToRotation "${rotation_name}" "Wind of Malaise"            AA ${Parse[0,"( ${DoMalo[SETTINGVAL]} && ${DoAoEMalo[SETTINGVAL]} )"]}  
    /call AddToRotation "${rotation_name}" "Malaise"                    AA ${Parse[0,"( ${DoMalo[SETTINGVAL]} && !${DoAoEMalo[SETTINGVAL]}  && !${Target.Buff[${Spell[Malaise].Trigger[1]}].ID} )"]}  
    /call AddToRotation "${rotation_name}" "${DieaseSlow}"              Spell ${Parse[0,"( ${DoSlow[SETTINGVAL]} && DETSPELLCHECK )"]}
/return
Sub SHM_DefaultDPSRotationConfig(string rotation_name) 
    | - Twincast Rotation
    /call AddToRotation "${rotation_name}" "${AESpiritualHeal}"         Spell ${Parse[0,"( ${IsHealing} && ${Me.Song[Healing Twincast].ID} )"]}    
    |- DPS Group Buffs
    /call AddToRotation "${rotation_name}" "${MeleeProcBuff}"           Spell ${Parse[0,"( SELFBUFFCHECK )"]}
    |- Debuffs
    |- Mana Regen
    /call AddToRotation "${rotation_name}" "Cannibalization"            AA ${Parse[0,"( ${DoAACanni[SETTINGVAL]} && ${Me.PctMana}<${AACanniManaPct[SETTINGVAL]} && ${Me.PctHPs}>=${AACanniMinHP[SETTINGVAL]} && ${RG_AAReady[Cannibalization]} )"]} 
    /call AddToRotation "${rotation_name}" "${CanniSpell}"              Spell ${Parse[0,"( ${DoSpellCanni[SETTINGVAL]} && ${Me.PctMana}<${CanniManaPct[SETTINGVAL]} && ${Me.PctHPs}>=${CanniMinHP[SETTINGVAL]} && ${Me.SpellReady[${CanniSpell}]} )"]}
    |- DPS
    /call AddToRotation "${rotation_name}" "${Epic}"                    Item  ${Parse[0,"( TRUE )"]}
    /call AddToRotation "${rotation_name}" "${DichoSpell}"              Spell ${Parse[0,"( SELFBUFFCHECK )"]}
    |- Dots
 |   /call AddToRotation "${rotation_name}" "${ChaoticDoT}"              Spell ${Parse[0,"( (${Target.PctHPs}>${HPStopDOT[SETTINGVAL]}) && DETGOMCHECK )"]}
    /call AddToRotation "${rotation_name}" "Rabid Bear"                 AA ${Parse[0,"( ${PCAAReady[Rabid Bear]} && ${DoMelee[SETTINGVAL]} && ${Me.Combat} )"]}
    /call AddToRotation "${rotation_name}" "${PandemicDot}"             Spell ${Parse[0,"( DOTSPELLCHECK && DETGOMCHECK )"]}
    /call AddToRotation "${rotation_name}" "${CurseDoT2}"               Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation "${rotation_name}" "${CurseDoT1}"               Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation "${rotation_name}" "${ChaoticDoT}"              Spell ${Parse[0,"( (${Target.PctHPs}>${HPStopDOT[SETTINGVAL]}) && ${Me.PctMana}>50 )"]}
    /call AddToRotation "${rotation_name}" "${PandemicDot}"             Spell ${Parse[0,"( DOTSPELLCHECK && ${Me.PctMana}>50 )"]}    
    /call AddToRotation "${rotation_name}" "${FastPoisonDoT}"           Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation "${rotation_name}" "${SaryrnDot}"               Spell ${Parse[0,"( DOTSPELLCHECK )"]}    
    /call AddToRotation "${rotation_name}" "${FastDiseaseDoT}"          Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation "${rotation_name}" "${UltorDot}"                Spell ${Parse[0,"( DOTSPELLCHECK )"]}    
    /call AddToRotation "${rotation_name}" "${MaloDot}"                 Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    |- Nukes
    /call AddToRotation "${rotation_name}" "${PoisonNuke}"              Spell ${Parse[0,"( TRUE )"]}
    /call AddToRotation "${rotation_name}" "${FastPoisonNuke}"          Spell ${Parse[0,"( TRUE )"]}
    /call AddToRotation "${rotation_name}" "${FrostNuke}"               Spell ${Parse[0,"( TRUE )"]}    
      
/return 

Sub SHM_DefaultBuffGroupConfig
    /call BuffGroup_Init 9
    /call BuffGroup_Set 1 "${GrowthBuff}" "WAR" 
    /call BuffGroup_Set 2 "${SlowProcBuff}" "WAR,SHD,PAL"
    /call BuffGroup_Set 3 "${LowLvlStaminaBuff}" "WAR,SHD,PAL" ${Parse[0,"( ${DoStatBuff[SETTINGVAL]} && ${Me.Level} <= 85 )"]}
    /call BuffGroup_Set 4 "${LowLvlAttackBuff}" "WAR,SHD,PAL,ROG,MNK,BER,RNG,BST" ${Parse[0,"( !${DoCombatAvatar[SETTINGVAL]} && ${Me.Level} <= 85 )"]}
    /call BuffGroup_Set 5 "${LowLvlStrBuff}" "WAR,SHD,PAL,ROG,MNK,BER,RNG,BST" ${Parse[0,"( ${DoStatBuff[SETTINGVAL]} && ${Me.Level} <= 85 && !${Spell[${LowLvlAgiBuff}].Level} >= 71 )"]}
    /call BuffGroup_Set 6 "${LowLvlAgiBuff}" "WAR,SHD,PAL,ROG,MNK,BER,RNG,BST" ${Parse[0,"( ${DoStatBuff[SETTINGVAL]} && ${Me.Level} <= 85 )"]}
    /call BuffGroup_Set 7 "${LowLvlDexBuff}" "WAR,SHD,PAL,ROG,MNK,BER,RNG,BST" ${Parse[0,"(${DoStatBuff[SETTINGVAL]} && ${Me.Level} <= 70 )"]}
    /call BuffGroup_Set 8 "${FocusSpell}" "ALL" 
    /call BuffGroup_Set 9 "${HasteBuff}" "WAR,SHD,PAL,ROG,MNK,BER,RNG,BST" ${Parse[0,"( ${DoHaste[SETTINGVAL]} && ${Spell[${FocusSpell}].Level}<=111 )"]}
/return

Sub SHM_DefaultDownRotationConfig(string rotation_name)
    |- Pet Stuff
    
    /call AddToRotation "${rotation_name}" "${PetSpell}"            Spell ${Parse[0,"( !${Me.Pet.ID} && ${DoPet[SETTINGVAL]} )"]}
|    /call AddToRotation "${rotation_name}" "${PetBuffSpell}"        Spell ${Parse[0,"( ${Me.Pet.ID} && !${Me.Pet.Buff[${PetBuffSpell}]} && ${DoPet[SETTINGVAL]} && ${Spell[${PetBuffSpell}].StacksPet})"]}
    
    |- Mana Regen
    /call AddtoRotation "${rotation_name}" "/call VerifyAvatar"        "Command"    ${Parse[0,"( ${DoCombatAvatar[SETTINGVAL]} && !${AvatarCheck} && ${Me.SpellReady[${LowLvlAttackBuff}]} && ${CaList[SETTINGVAL].NotEqual[NULL]} )"]}
    /call AddtoRotation "SHM_DPS_MODETLP_Rotation" "/call VerifyPanther" "Command"    ${Parse[0,"( ${DoCombatPanther[SETTINGVAL]} && !${PantherCheck} && ${Me.SpellReady[${MeleeProcBuff}]} && ${CpList[SETTINGVAL].NotEqual[NULL]} )"]}
   
    /call AddToRotation "${rotation_name}" "Cannibalization"        AA ${Parse[0,"( ${DoAACanni[SETTINGVAL]} && ${Me.PctMana}<${AACanniManaPct[SETTINGVAL]} && ${Me.PctHPs}>=${AACanniMinHP[SETTINGVAL]} && ${RG_AAReady[Cannibalization]} )"]} 
    /call AddToRotation "${rotation_name}" "${CanniSpell}"          Spell ${Parse[0,"( ${DoSpellCanni[SETTINGVAL]} && ${Me.PctMana}<${CanniManaPct[SETTINGVAL]} && ${Me.PctHPs}>=${CanniMinHP[SETTINGVAL]} && ${Me.SpellReady[${CanniSpell}]} )"]}


    /call AddToRotation "${rotation_name}" "Pact of the Wolf"       AA ${Parse[0,"( ${DoAura[SETTINGVAL]} && !${Me.Song[pact of the wolf].ID} )"]} 
    /call AddToRotation "${rotation_name}" "Talisman of Celerity"   AA ${Parse[0,"( ${DoHaste[SETTINGVAL]} && !${Me.Haste} && SELFBUFFAACHECK)"]} 
    /if (!${RG_CanUseAA[Lupine Spirit]}) {
        /call AddToRotation "${rotation_name}" "${RunSpeedBuff}"    Spell ${Parse[0,"( ${DoRunSpeed[SETTINGVAL]} && SELFBUFFCHECK )"]}
    } else {
        /call AddToRotation "${rotation_name}" "Lupine Spirit"      AA   ${Parse[0,"( ${DoRunSpeed[SETTINGVAL]} && SELFBUFFAACHECK && !${Me.Buff[${Spell[${Me.AltAbility[Lupine Spirit].Spell.Trigger[1]}]}].ID} )"]}
    }
    /call AddToRotation "${rotation_name}" "Preincarnation"         AA    ${Parse[0,"( ${Me.AltAbility[Preincarnation].Rank}>=2 && SELFBUFFAACHECK && !${Me.Buff[${Spell[${Me.AltAbility[Preincarnation].Spell.Trigger[1]}]}].ID})"]}

    |- Mount
    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==1 && ${Me.Mount.ID} && ${DoMelee[SETTINGVAL]} )"]}

    |- Setup Buff Group List
    /call AddToRotation "${rotation_name}" "${PackSelfBuff}"       Spell ${Parse[0,"( SELFBUFFCHECK )"]}
    /call AddToRotation "${rotation_name}" "${SelfHealProcBuff}"   Spell ${Parse[0,"( SELFBUFFCHECK )"]}
    /call AddToRotation "${rotation_name}" "${GroupHealProcBuff}"  Spell ${Parse[0,"( SELFBUFFCHECK )"]}    

/return

Sub SHM_Combat_Routine
    /call PetAttack
    /if (DODEBUFF) {
        /call Ordered_Rotation_Follow SHM_Debuff_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        |/if (${Macro.Return}) /return
    }
    /if (DODPS) {
        /if ( BURNCHECK ) {
            /call Ordered_Rotation_Follow SHM_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        }
        /call Ordered_Rotation_Follow SHM_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }
/return ${Macro.Return}

Sub SHM_Downtime_Routine
    |- Call Self buffs
    /call FollowRotation  SHM_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}

    /if (${Me.Pet.ID}) {
        /call FollowRotation  SHM_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.Pet.ID}
    } 
/return ${Macro.Return}

Sub SHM_Heal_Routine
    |- If we're a member of a group, heal our group first.
    
    /call HealNow ${WorstHurtGroup[${HealPoint_MaxPoint}]}
    | - Splash Rotation moved here out of the Combat Section.
    /if ( ${XAssist.XTFullHaterCount}>0 ) /call Ordered_Rotation_Follow SHM_Splash_${ClassMode[SETTINGVAL]}_Rotation ${assistid} TRUE    
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
|- Routine to perform a rez
|---------------------------------------------------------------------------- 
Sub SHM_DoRez(int corpse_id)
    |- If we don't have a rez ability, get out of here. Needed for low levels
    /if ( !${PCSpellReady[Incarnate Anew]} && !${FindItem[Staff of Forbidden Rites].ID} && !${RG_CanUseAA[Rejuvenation of Spirit]} ) {
        /return FALSE
    }
    /call SetTarget ${corpse_id}
    /if (${Target.Distance}>25) /corpse

    /if (${Me.CombatState.Equal[COMBAT]} && (${Select[${Spawn[id ${corpse_id}].Class.ShortName},DRU,CLR]} || ${DoBattleRez[SETTINGVAL]}) ) {
        /if (${FindItem[Staff of Forbidden Rites].ID} && ${Me.ItemReady[=Staff of Forbidden Rites]}) {
            /call ItemNow "Staff of Forbidden Rites" ${corpse_id}
            /return ${Macro.Return}
        } else /if (${RG_AAReady[Call of the Wild]}) {
            /call AANow ${Me.AltAbility[Call of the Wild].ID} ${corpse_id}
            /return ${Macro.Return}
        }  
    } else {
        |- Non-Combat Rez Handling
        /if ( (${RG_CanUseAA[Rejuvenation of Spirit]} > 0) && !${Me.CombatState.Equal[COMBAT]} ) {
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
|----------------------------------------------------------------------------
|- SUB: BIND BNDSingleCure - 
|----------------------------------------------------------------------------
Sub Bind_BNDSingleCure(int RequestorID)
    /call SingleCure ${RequestorID}
/return 

|----------------------------------------------------------------------------
|- SUB: SHM_SpecialChats Special Chat events specific to shaman and not buff begs.
|----------------------------------------------------------------------------
Sub SHM_SpecialChats(string chat_text, int sender_id)
    /if (${chat_text.Find[thawme]}) /call AddToThawmeQueue ${sender_id}
    
/return

| ----------------------------------------------------------------------------
| SUB: Verify Avatar
| ----------------------------------------------------------------------------
Sub VerifyAvatar
            /if  ( ${CaList[SETTINGVAL].NotEqual[NULL]} ) {
                |- Load our |-delimited setting entry into a list so we have
                |- quick ooping w/o lots of Arg parsing.
                /declare tmp_AvatarCheck int local 0
                /declare list_avatarcombat list local 
                /invoke ${list_avatarcombat.Delimiter[|]}
                /invoke ${list_avatarcombat.Append[${CaList[SETTINGVAL]}]}
                /declare li_avatarcombat listiterator local
                /vardata li_avatarcombat list_avatarcombat.First.Clone

                /declare spawn_tmp spawn local
                /if (${list_avatarcombat.Count}) {
                    /while (!${li_avatarcombat.IsEnd}) {   
                        /if ( ${SpawnCount[pc ${li_avatarcombat.Value}]} ) {
                            /squelch /vardata spawn_tmp Spawn[PC ${li_avatarcombat.Value}]
                                
                                /if ( !${spawn_tmp.CachedBuff[${LowLvlAttackBuff}].Duration}  ) {
                                    /call SpellNow "${LowLvlAttackBuff}" ${spawn_tmp.ID}
                                    /varset AvatarCheck 0
                                 /return TRUE
                            } else { 
                                /if ( ${tmp_AvatarCheck} < ${spawn_tmp.CachedBuff[${LowLvlAttackBuff}].Duration} ) {
                                    /varset tmp_AvatarCheck ${spawn_tmp.CachedBuff[${LowLvlAttackBuff}].Duration}
                                }
                                
                            }
                        }
                     /invoke ${li_avatarcombat.Advance}
                    }     
            /varset AvatarCheck ${tmp_AvatarCheck}
           }
        }
/return    

| ----------------------------------------------------------------------------
| SUB: Verify Panther
| ----------------------------------------------------------------------------
Sub VerifyPanther
            /if  ( ${CpList[SETTINGVAL].NotEqual[NULL]} ) {
                |- Load our |-delimited setting entry into a list so we have
                |- quick ooping w/o lots of Arg parsing.
                /declare tmp_PantherCheck int local 0
                /declare list_panthercombat list local 
                /invoke ${list_panthercombat.Delimiter[|]}
                /invoke ${list_panthercombat.Append[${CaList[SETTINGVAL]}]}
                /declare li_panthercombat listiterator local
                /vardata li_panthercombat list_panthercombat.First.Clone

                /declare spawn_tmp spawn local
                /if (${list_panthercombat.Count}) {
                    /while (!${li_panthercombat.IsEnd}) {   
                        /if ( ${SpawnCount[pc ${li_panthercombat.Value}]} ) {
                            /squelch /vardata spawn_tmp Spawn[PC ${li_panthercombat.Value}]
                                
                                /if ( !${spawn_tmp.CachedBuff[${MeleeProcBuff}].Duration}  ) {
                                    /call SpellNow "${MeleeProcBuff}" ${spawn_tmp.ID}
                                    /varset PantherCheck 0
                                 /return TRUE
                            } else { 
                                /if ( ${tmp_PantherCheck} < ${spawn_tmp.CachedBuff[${LowLvlAttackBuff}].Duration} ) {
                                    /varset tmp_PantherCheck ${spawn_tmp.CachedBuff[${LowLvlAttackBuff}].Duration}
                                }
                                
                            }
                        }
                     /invoke ${li_panthercombat.Advance}
                    }     
            /varset PantherCheck ${tmp_PantherCheck}
           }
        }
/return    


|----------------------------------------------------------------------------
|- SUB: Cureice
|----------------------------------------------------------------------------
#bind Cureice /cureice
Sub Bind_CureIce(int cureid, int isinfection)
    /if (${isinfection}) {
        /if (${Me.SpellReady[${CureSpell}]}) {
            /call SpellNow "${CureSpell}" ${cureid}
            /gsay Curing Restless Ice Infection!
        }
    } else {
        /if (${Me.SpellReady[${IcefixSpell}]}) {
            /call SpellNow "${IcefixSpell}" ${cureid}
            /gsay Curing Restless Ice!
        } else {
            /echo \arMissing Spell: Eradicate Curse -- Cannot Cure Ice
        }
    }
/return

Sub FacePull
    /if (!${Me.Combat}) /attack on
/return

Sub SHM_PullSetup
    /if (${Me.Pet.ID} && ${DoPetPull[SETTINGVAL]}) {
        /call Pull_SetAbility "pullpet" "Special"
        /return
    }

    /if (${Me.Level}>20 && !${DoMelee[SETTINGVAL]}) {
        /if (${RG_CanUseAA[Turgur's Swarm]}) {
            /call Pull_SetAbility "Turgur's Swarm" "AA" 
        } else /if (${RG_CanUseAA[Malaise]}) {
            /call Pull_SetAbility "Malaise" AA
        } else /if (${SlowSpell.NotEqual[NULL]}&&${Me.Gem[${SlowSpell}]}) {
            /call Pull_SetAbility "${SlowSpell}" Spell
        } else /if (${MaloSpell.NotEqual[NULL]}&&${Me.Gem[${MaloSpell}]}) {
            /call Pull_SetAbility "${MaloSpell}" Spell
        } else /if (${Me.Gem[${FrostNuke}]}) {
            /call Pull_SetAbility "${FrostNuke}" "Spell"
        }
    } else /if (${DoMelee[SETTINGVAL]}) {
        | Need this as a last resort esp for super lowbies
        /call Pull_SetAbility "/call FacePull" Command
    }

/return