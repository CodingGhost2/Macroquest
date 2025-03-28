|- RGpalutil.inc - By Morisato
|- Automatic Paladin Bot
|- Version 0.1
|- Updated: 02/09/2020
|- Credit: Toots, Noobhax0r, Maskoi, Ctaylor, Treehuggindruid. A lot of ideas were borrowed and modified from their macros

#define MODETANK 0
#define MODEDPS 1
#define MODETLP 2
#define MODEOAMUK 10
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------

Sub PAL_Setup
/declare RGList_PAL            list outer 
|- Items
    /call ItemSet_New Epic

|-Spells
    /call AbilitySet_New CrushTimer6
    /call AbilitySet_New CrushTimer5
    /call AbilitySet_New HealNuke
    /call AbilitySet_New TempHP
    /call AbilitySet_New Preservation
    /call AbilitySet_New Lowaggronuke
    /call AbilitySet_New Incoming
    /call AbilitySet_New DebuffNuke
    /call AbilitySet_New Healproc
    /call AbilitySet_New FuryProc
    /call AbilitySet_New Aurora
    /call AbilitySet_New StunTimer5
    /call AbilitySet_New StunTimer4
   |/call AbilitySet_New StunTimer53
    /call AbilitySet_New Healstun
    /call AbilitySet_New Healward
   |/call AbilitySet_New GroupAego
    /call AbilitySet_New Aego
    /call AbilitySet_New Brells
    /call AbilitySet_New Splashcure
    /call AbilitySet_New Healtaunt
    /call AbilitySet_New Affirmation
    /call AbilitySet_New Doctrine
    /call AbilitySet_New WaveHeal
    /call AbilitySet_New WaveHeal2
    /call AbilitySet_New Selfheal
    /call AbilitySet_New Reverseds
    /call AbilitySet_New Cleansehot
    /call AbilitySet_New BurstHeal
    /call AbilitySet_New ArmorSelfBuff
    /call AbilitySet_New Righteousstrike
    /call AbilitySet_New Symbol
    /call AbilitySet_New LessonStun
    /call AbilitySet_New Audacity
    /call AbilitySet_New LightHeal
    /call AbilitySet_New TotLightHeal
    /call AbilitySet_New TotLightHeal2
    /call AbilitySet_New Pacify
    /call AbilitySet_New Toucheal
    /call AbilitySet_New Dicho
    /call AbilitySet_New Puritycure
    /call AbilitySet_New Challengetaunt
    /call AbilitySet_New mantle
	/call AbilitySet_New Piety
	/call AbilitySet_New Remorse
    /call AbilitySet_New aurabuff1
	/call AbilitySet_New AntiUndeadNuke
    /call AbilitySet_New AllianceNuke
    /call AbilitySet_New CurseCure
|- Combat Abilitys
   /call AbilitySet_New endregen
   /call AbilitySet_New meleemit
   /call AbilitySet_New Armordisc
   /call AbilitySet_New Undeadburn
   /call AbilitySet_New Pentientarmor
   /call AbilitySet_New Mantle 
   /call AbilitySet_New Holyguard
   /call AbilitySet_New Spellblock
   /call AbilitySet_New Reflexstrike
    
    
    
	|- Rotations
| - Tank Dps Rotation    
	/call Ordered_Rotation_New PAL_Debuff_MODETANK_Rotation
	/call Ordered_Rotation_New PAL_Heal_MODETANK_Rotation
	/call Ordered_Rotation_New PAL_DPS_MODETANK_Rotation
	/call Ordered_Rotation_New PAL_Downtime_MODETANK_Rotation
    /call Ordered_Rotation_New PAL_Burn_MODETANK_Rotation
| - Live Dps Mode Rotation
    /call Ordered_Rotation_New PAL_Debuff_MODEDPS_Rotation
	/call Ordered_Rotation_New PAL_Heal_MODEDPS_Rotation
	/call Ordered_Rotation_New PAL_DPS_MODEDPS_Rotation
	/call Ordered_Rotation_New PAL_Downtime_MODEDPS_Rotation
    /call Ordered_Rotation_New PAL_Burn_MODEDPS_Rotation
|- TLP Mode Rotations
    /call Ordered_Rotation_New PAL_Debuff_MODETLP_Rotation
	/call Ordered_Rotation_New PAL_Heal_MODETLP_Rotation
	/call Ordered_Rotation_New PAL_DPS_MODETLP_Rotation
	/call Ordered_Rotation_New PAL_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New PAL_Burn_MODETLP_Rotation
  
    /call Ordered_Rotation_New PAL_Debuff_MODEOAMUK_Rotation
	/call Ordered_Rotation_New PAL_Heal_MODEOAMUK_Rotation
	/call Ordered_Rotation_New PAL_DPS_MODEOAMUK_Rotation
	/call Ordered_Rotation_New PAL_Downtime_MODEOAMUK_Rotation
    /call Ordered_Rotation_New PAL_Burn_MODEOAMUK_Rotation
    
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
    /varset ClassMode[SETTINGDESC] Set 0 = Tank; Set 1 = DPS;
    /call RGLoadSetting PAL DoHeals 1 Healing "Set 0/1 to heal the group. Checked in the main loop."
    /call RGLoadSetting PAL Flashhp 35 Combat "Set Hp% to Shield Flash at. Default 35"
    /call RGLoadSetting PAL DoBrells 1 Buff "Sets Whether to Use brells 1/0 Default 1"
    /call RGLoadSetting PAL DoNuke 1 Combat "Sets whether to use Nukes or not Default 1"
    /call RGLoadSetting PAL MainHealPoint 70 Combat "Set the % to Cast  heals at" 1
    /call RGLoadSetting PAL LayHandsPct 35 Combat "Set the % to Cast Lay On hands at" 1
	/call RGLoadSetting PAL GroupHealPoint 80 Combat "Sets The % to heal group at when GroupInjureCnt folks are below" 1
	/call RGLoadSetting PAL GroupInjureCnt 3 Combat "Group heal Count" 1
    /call RGLoadSetting PAL ChestItemName "${Me.Inventory[17].Name}" Item "Name of your chest item -- defaults to the slot"
    /call RGLoadSetting PAL SummonArrows 1 Options "Sets Whether to AutoSummon Arrows or Not with Huntsman's quiver"
	/call RGLoadSetting PAL DoBandolier 0 Options "Sets whether to use auto bandolier functions. Requires a bandolier called Shield (a shield and 1hd weapon) and one called 2HS"
    /call RGLoadSetting PAL UseBattleRez 1 Healing "Set 0/1 to cast Gift of Ressurection AA in combat."
    /call RGLoadSetting PAL DoReverseDS 1 Combat "Will Reverse DS mobs Default on. 1/0"
    /call RGLoadSetting PAL DoNukes 1 Combat "Turns off Most DPS only nukes 1/0"
    /call RGLoadSetting PAL DoDruid 0 Combat "Sets whether to use Symbol or hand of Stormwall keeper buff. for Druid Stacking."
	/call RGLoadSetting PAL TotHealPoint 30 Healing "What % to Cast a Target of Target Heal"
    /call RGLoadSetting PAL DoTank 1 Combat  "Tank or Dps Modes. 1 for tanking 0 for not"
    /declare HighestHealPoint int outer 98
|-Declare spell variables
	/declare GroupBuffRecast 		int outer 0
	/declare miscspellremem		    string outer NULL
	/declare tempid					string outer NULL
	/declare spellrememtimer		timer outer 0
	/declare ReadyToCast	  		timer outer 0
	/declare groupbufftimer			timer outer 0
    /declare spellmisc 				int outer 8
	/varset spellmisc ${Me.NumGems}
	

/return
|----------------------------------------------------------------------------
|- SUB: CheckOptions
|---------------------------------------------------------------------------- 
Sub PAL_CheckOptions
|- This is checking if your a tank and Setting Variables properly if you are.

    /if ( ${IsTanking} || ${DoTank[SETTINGVAL]} ) {
        /if (${RG_AAReady[792]} && !${Me.AltAbility[792].Name.Find[enabled]}) {
            /call AANow "792"
        }   
        /varset StayOnTarget[SETTINGVAL] 0
        /varset AutoAssistAt[SETTINGVAL] 100
        /varset DoMelee[SETTINGVAL] 1
        /varset AutoCampRadius[SETTINGVAL] 50
        /stick set DelayStrafe on
        /varset StickHow[SETTINGVAL] 15 moveback
        /varset AllowMezBreak[SETTINGVAL] 1
    } else {
        /if (${RG_AAReady[792]} && ${Me.AltAbility[792].Name.Find[enabled]}) {
            /call AANow "792"
        }
        /varset AutoAssistAt[SETTINGVAL] 98
        /varset DoMelee[SETTINGVAL] 1
        /varset StayOnTarget[SETTINGVAL] 1
        /varset AutoCampRadius[SETTINGVAL] 30
        /varset StickHow[SETTINGVAL] snaproll !front 15 moveback uw 
        /varset AllowMezBreak[SETTINGVAL] 0
    }

/return 

|----------------------------------------------------------------------------
|- SUB: SetupSkills
|----------------------------------------------------------------------------   
Sub PAL_SetupSkills
    /echo Choosing All Paladin Spells - this may take a moment    
|- Spells are Listed from Lowest to Highest for my sanity 
|- Current Spells Are Implmented from level 85 and up for the Most part. Low level Support will be added In Future Updates
|- Items
|- Epic
    /call ItemSet_Add "Nightbane, Sword of the Valiant" Epic
    /call ItemSet_Add "Redemption" 			            Epic
    /call ItemSet_ChooseOuter Epic Epic
	/declare EpicBuff2 string outer "Flames of the Valiant"
	/declare EpicBuff1 string outer "Flames of Redemption"

| - One Off Buffs
	/call AbilitySet_Add "Silent Piety" Piety
	/call AbilitySet_ChooseOuter Piety Piety
|- Remorse
	/call AbilitySet_Add "Remorse for the fallen" Remorse
    /call AbilitySet_Add "Penitence for the Fallen" Remorse
	/call AbilitySet_ChooseOuter Remorse Remorse

|--Aura Buffs
    /call AbilitySet_Add "Blessed Aura" aurabuff1
    /call AbilitySet_Add "Holy Aura" aurabuff1
    /call AbilitySet_ChooseOuter aurabuff1 aurabuff1
| - Pally Alliance Spell
    /call AbilitySet_Add "Holy Alliance" AllianceNuke
    /call AbilitySet_Add "Stormwall Coalition" AllianceNuke
    /call AbilitySet_ChooseOuter AllianceNuke AllianceNuke

    | Timer 6 - Crush (with damage)
    /call AbilitySet_Add "Crush of Compunction"         CrushTimer6     | Level 85
    /call AbilitySet_Add "Crush of Repentance"          CrushTimer6     | Level 90
    /call AbilitySet_Add "Crush of Tides"               CrushTimer6     | Level 95
    /call AbilitySet_Add "Crush of Tarew"               CrushTimer6     | Level 100
    /call AbilitySet_Add "Crush of Povar"               CrushTimer6     | Level 105
    /call AbilitySet_Add "Crush of E'Ci"                CrushTimer6     | Level 110
    /call AbilitySet_Add "Crush of Restless Ice"        CrushTimer6     | Level 115
    /call AbilitySet_Add "Crush of the Umbra"           CrushTimer6     | Level 120
    /call AbilitySet_ChooseOuter CrushTimer6 CrushTimer6

    | Timer 5 - Crush
    /call AbilitySet_Add "Crush of the Crying Seas"     CrushTimer5     | Level 82
    /call AbilitySet_Add "Crush of Marr"                CrushTimer5     | Level 87
    /call AbilitySet_Add "Crush of Oseka"               CrushTimer5     | Level 92
    /call AbilitySet_Add "Crush of the Iceclad"         CrushTimer5     | Level 97
    /call AbilitySet_Add "Crush of the Darkened Sea"    CrushTimer5     | Level 102
    /call AbilitySet_Add "Crush of the Timorous Deep"   CrushTimer5     | Level 107
    /call AbilitySet_Add "Crush of the Grotto"          CrushTimer5     | Level 112
    /call AbilitySet_Add "Crush of the Twilight Sea"    CrushTimer5     | Level 117
    /call AbilitySet_ChooseOuter CrushTimer5 CrushTimer5

    | Timer 7 - HealNuke
    /call AbilitySet_Add "Glorious Vindication"         HealNuke    | Level 85
    /call AbilitySet_Add "Glorious Exoneration"         HealNuke    | Level 90
    /call AbilitySet_Add "Glorious Exculpation"         HealNuke    | Level 95
    /call AbilitySet_Add "Glorious Expurgation"         HealNuke    | Level 100
    /call AbilitySet_Add "Brilliant Vindication"        HealNuke    | Level 105
    /call AbilitySet_Add "Brilliant Exoneration"        HealNuke    | Level 110
    /call AbilitySet_Add "Brilliant Exculpation"        HealNuke    | Level 115
    /call AbilitySet_Add "Brilliant Acquittal"          HealNuke    | Level 120
    /call AbilitySet_ChooseOuter HealNuke HealNuke

|- Steely Stance TempHP
    /call AbilitySet_Add "Steely Stance" TempHP
    /call AbilitySet_Add "Stubborn Stance" TempHP
    /call AbilitySet_Add "Stoic Stance" TempHP
    /call AbilitySet_Add "Staunch Stance" TempHP
    /call AbilitySet_Add "Steadfast Stance" TempHP
    /call AbilitySet_Add "Defiant Stance" TempHP
    /call AbilitySet_Add "Stormwall Stance" TempHP
    /call AbilitySet_Add "Adamant Stance" TempHP
    /call AbilitySet_ChooseOuter TempHP TempHP

    | Timer 12 - Preservation
    /call AbilitySet_Add "Ward of Tunare"               Preservation    | Level 70
    /call AbilitySet_Add "Sustenance of Tunare"         Preservation    | Level 80
    /call AbilitySet_Add "Preservation of Tunare"       Preservation    | Level 85
    /call AbilitySet_Add "Preservation of Marr"         Preservation    | Level 90
    /call AbilitySet_Add "Preservation of Oseka"        Preservation    | Level 95
    /call AbilitySet_Add "Preservation of the Iceclad"  Preservation    | Level 100
    /call AbilitySet_Add "Preservation of Rodcet"       Preservation    | Level 110
    /call AbilitySet_Add "Preservation of the Grotto"   Preservation    | Level 115
    /call AbilitySet_Add "Preservation of the Basilica" Preservation    | Level 120
    /call AbilitySet_ChooseOuter Preservation Preservation

|- Nuke Heal Target - Censure
    /call AbilitySet_Add "Denouncement" Lowaggronuke
    /call AbilitySet_Add "Reprimand" Lowaggronuke
    /call AbilitySet_Add "Ostracize" Lowaggronuke
    /call AbilitySet_Add "Admonish" Lowaggronuke
    /call AbilitySet_Add "Censure" Lowaggronuke
    /call AbilitySet_Add "Remonstrate" Lowaggronuke
    /call AbilitySet_Add "Upbraid" Lowaggronuke
    /call AbilitySet_ChooseOuter Lowaggronuke Lowaggronuke

|- Harmonius Blessing - Empires of Kunark spell. Incoming Spell.
    /call AbilitySet_Add "Harmonious Blessing" Incoming
    /call AbilitySet_Add "Concordant Blessing" Incoming
    /call AbilitySet_Add "Confluent Blessing" Incoming
    /call AbilitySet_Add "Penumbral Blessing" Incoming
    /call AbilitySet_ChooseOuter Incoming Incoming

    | Undead DebuffNuke
    /call AbilitySet_Add "Last Rites"       DebuffNuke  | Level 68 - Timer 7
	/call AbilitySet_Add "Burial Rites"     DebuffNuke  | Level 71 - Timer 7
	/call AbilitySet_Add "Benediction"      DebuffNuke  | Level 76
    /call AbilitySet_Add "Eulogy"           DebuffNuke  | Level 81
    /call AbilitySet_Add "Elegy"            DebuffNuke  | Level 86
    /call AbilitySet_Add "Paean"            DebuffNuke  | Level 91
    /call AbilitySet_Add "Laudation"        DebuffNuke  | Level 96
    /call AbilitySet_Add "Consecration"     DebuffNuke  | Level 101
    /call AbilitySet_Add "Remembrance"      DebuffNuke  | Level 106
    /call AbilitySet_Add "Requiem"          DebuffNuke  | Level 111
    /call AbilitySet_Add "Hymnal"           DebuffNuke  | Level 116
    /call AbilitySet_ChooseOuter DebuffNuke DebuffNuke

|- Proc Buff Heal target of Target => LVL 97
    /call AbilitySet_Add "Regenerating Steel" Healproc
    /call AbilitySet_Add "Rejuvenating Steel" Healproc
    /call AbilitySet_Add "Reinvigorating Steel" Healproc
    /call AbilitySet_Add "Revitalizating Steel" Healproc
    /call AbilitySet_Add "Renewing Steel" Healproc
    /Call AbilitySet_ChooseOuter Healproc Healproc

| - Fury Proc Strike  67 - 115
    /call AbilitySet_Add "Wrathful Fury" FuryProc
    /call AbilitySet_Add "Silvered Fury" FuryProc
    /call AbilitySet_Add "Pious Fury" FuryProc
    /call AbilitySet_Add "Righteous Fury" FuryProc
    /call AbilitySet_Add "Devout Fury" FuryProc
    /call AbilitySet_Add "Earnest Fury" FuryProc
    /call AbilitySet_Add "Zealous Fury" FuryProc
    /call AbilitySet_Add "Reverent Fury" FuryProc
    /call AbilitySet_Add "Ardent Fury" FuryProc
    /call AbilitySet_Add "Merciful Fury" FuryProc
    /call AbilitySet_Add "Sincere Fury" FuryProc
    /call AbilitySet_ChooseOuter FuryProc FuryProc

|- Aurora Group heals.
    /call AbilitySet_Add "Aurora of Dawning" Aurora
    /call AbilitySet_Add "Aurora of Dawnlight" Aurora
    /call AbilitySet_Add "Aurora of Daybreak" Aurora
    /call AbilitySet_Add "Aurora of Splendor" Aurora
    /call AbilitySet_Add "Aurora of Sunrise" Aurora
    /call AbilitySet_Add "Aurora of Dayspring" Aurora
    /call AbilitySet_Add "Aurora of Morninglight" Aurora
    /call AbilitySet_Add "Aurora of Wakening" Aurora
    /call AbilitySet_ChooseOuter Aurora Aurora

    | Timer 5 - Hate Stun
    /call AbilitySet_Add "Desist"                       StunTimer5    | Level 13 - Not Timer 5, use for TLP Low Level Stun
    /call AbilitySet_Add "Stun"                         StunTimer5    | Level 28
    /call AbilitySet_Add "Force of Akera"               StunTimer5    | Level 53
    /call AbilitySet_Add "Ancient: Force of Chaos"      StunTimer5    | Level 65
    /call AbilitySet_Add "Ancient: Force of Jeron"      StunTimer5    | Level 70
    /call AbilitySet_Add "Force of Prexus"              StunTimer5    | Level 75
    /call AbilitySet_Add "Force of Timorous"            StunTimer5    | Level 80
    /call AbilitySet_Add "Force of the Crying Seas"     StunTimer5    | Level 85
    /call AbilitySet_Add "Force of Marr"                StunTimer5    | Level 90
    /call AbilitySet_Add "Force of Oseka"               StunTimer5    | Level 95
    /call AbilitySet_Add "Force of the Iceclad"         StunTimer5    | Level 100
    /call AbilitySet_Add "Force of the Darkened Sea"    StunTimer5    | Level 105
    /call AbilitySet_Add "Force of the Timorous Deep"   StunTimer5    | Level 110
    /call AbilitySet_Add "Force of the Grotto"          StunTimer5    | Level 115
    /call AbilitySet_Add "Force of the Umbra"           StunTimer5    | Level 120
    /call AbilitySet_ChooseOuter StunTimer5 StunTimer5

    | Timer 4 - Hate Stun
    /call AbilitySet_Add "Cease"            StunTimer4   | Level 7 - Not Timer 4, use for TLP Low Level Stun
    /call AbilitySet_Add "Force of Akilae"  StunTimer4   | Level 62
    /call AbilitySet_Add "Force of Piety"   StunTimer4   | Level 66
    /call AbilitySet_Add "Sacred Force"     StunTimer4   | Level 71
    /call AbilitySet_Add "Devout Force"     StunTimer4   | Level 81
    /call AbilitySet_Add "Solemn Force"     StunTimer4   | Level 83
    /call AbilitySet_Add "Earnest Force"    StunTimer4   | Level 86
    /call AbilitySet_Add "Zealous Force"    StunTimer4   | Level 91
    /call AbilitySet_Add "Reverent Force"   StunTimer4   | Level 96
    /call AbilitySet_Add "Ardent Force"     StunTimer4   | Level 101
    /call AbilitySet_Add "Merciful Force"   StunTimer4   | Level 106
    /call AbilitySet_Add "Sincere Force"    StunTimer4   | Level 111
    /call AbilitySet_Add "Pious Force"      StunTimer4   | Level 116
    /call AbilitySet_ChooseOuter StunTimer4 StunTimer4
    
|- Heal Stuns T3 12s recast
    /call AbilitySet_Add "Force of Generosity" Healstun
    /call AbilitySet_Add "Force of Reverence" Healstun
    /call AbilitySet_Add "Force of Ardency" Healstun 
    /call AbilitySet_Add "Force of Mercy" Healstun
    /call AbilitySet_Add "Force of Sincerity" Healstun     
    /call AbilitySet_ChooseOuter Healstun Healstun

|- Dissident Stun
    /call AbilitySet_Add "Dichotomic Force" Dicho
    /call AbilitySet_Add "Dissident Force" Dicho    
    /call AbilitySet_Add "Composite Force" Dicho
    /call AbilitySet_Add "Ecliptic Force" Dicho
    /call AbilitySet_ChooseOuter Dicho Dicho

|- Healing ward Heals Target of target and wards self. Divination based heal/ward
    /call AbilitySet_Add "Protective Revelation" Healward
    /call AbilitySet_Add "Protective Confession"  Healward
    /call AbilitySet_Add "Protective Devotion"  Healward
    /call AbilitySet_Add "Protective Dedication"  Healward
    /call AbilitySet_Add "Protective Allegiance"  Healward
    /call AbilitySet_Add "Protective Proclamation"  Healward
    /call AbilitySet_Add "Protective Devotion"  Healward
    /call AbilitySet_Add "Protective Consecration"  Healward
    /call AbilitySet_ChooseOuter Healward Healward
    
|- Pally Aegolism
    /call AbilitySet_Add "Austerity"                        Aego    | Level 55
    /call AbilitySet_Add "Blessing of Austerity"            Aego    | Level 58 - Group
    /call AbilitySet_Add "Guidance"                         Aego    | Level 65
    /call AbilitySet_Add "Affirmation"                      Aego    | Level 70
    /call AbilitySet_Add "Sworn Protector"                  Aego    | Level 75
    /call AbilitySet_Add "Oathbound Protector"              Aego    | Level 80
    /call AbilitySet_Add "Sworn Keeper"                     Aego    | Level 85
    /call AbilitySet_Add "Oathbound Keeper"                 Aego    | Level 90
    /call AbilitySet_Add "Avowed Keeper"                    Aego    | Level 92
    /call AbilitySet_Add "Hand of the Avowed Keeper"        Aego    | Level 95 - Group
    /call AbilitySet_Add "Pledged Keeper"                   Aego    | Level 97
    /call AbilitySet_Add "Hand of the Pledged Keeper"       Aego    | Level 100 - Group
    /call AbilitySet_Add "Stormbound Keeper"                Aego    | Level 102
    /call AbilitySet_Add "Hand of the Stormbound Keeper"    Aego    | Level 105 - Group
    /call AbilitySet_Add "Ashbound Keeper"                  Aego    | Level 107
    /call AbilitySet_Add "Hand of the Ashbound Keeper"      Aego    | Level 110 - Group
    /call AbilitySet_Add "Stormwall Keeper"                 Aego    | Level 112
    /call AbilitySet_Add "Hand of the Stormwall Keeper"     Aego    | Level 115 - Group
    /call AbilitySet_Add "Shadewell Keeper"                 Aego    | Level 117
    /call AbilitySet_Add "Hand of the Dreaming Keeper"      Aego    | Level 120 - Group
    /call AbilitySet_ChooseOuter Aego Aego
    
|- Brells Line 
    /call AbilitySet_Add "Brell's Tenacious Barrier" Brells
    /call AbilitySet_Add "Brell's Loamy Ward" Brells
    /call AbilitySet_Add "Brell's Tellurian Rampart" Brells
    /call AbilitySet_Add "Brell's Adamantine Armor" Brells
    /call AbilitySet_Add "Brell's Steadfast Bulwark" Brells
    /call AbilitySet_Add "Brell's Stalwart Bulwark" Brells
    /call AbilitySet_Add "Brell's Blessed Bastion" Brells
    /call AbilitySet_Add "Brell's Blessed Barrier" Brells
    /call AbilitySet_Add "Brell's Earthen Aegis" Brells
    /call AbilitySet_Add "Brell's Stony Guard" Brells
    /call AbilitySet_Add "Brell's Brawny Bulwark" Brells
    /call AbilitySet_Add "Brell's Stalwart Shield" Brells
    /call AbilitySet_Add "Brell's Mountainous Barrier" Brells
    /call AbilitySet_Add "Brell's Steadfast Aegis" Brells
    /call AbilitySet_ChooseOuter Brells Brells

|- Splashcure Spells
    /call AbilitySet_Add "Splash of Repentance" Splashcure
    /call AbilitySet_Add "Splash of Sanctification" Splashcure
    /call AbilitySet_Add "Splash of Purification" Splashcure
    /call AbilitySet_Add "Splash of Cleansing" Splashcure
    /call AbilitySet_Add "Splash of Atonement" Splashcure
    /call AbilitySet_Add "Splash of Depuration" Splashcure
    /call AbilitySet_Add "Splash of Exaltation" Splashcure
    /call AbilitySet_ChooseOuter Splashcure Splashcure

|- Purity Cure Poison/Diease Cure Half Power to curse
    /call AbilitySet_Add "Balanced Purity" Puritycure
    /call AbilitySet_Add "Devoted Purity" Puritycure
    /call AbilitySet_Add "Earnest Purity" Puritycure
    /call AbilitySet_Add "Zealous Purity" Puritycure
    /call AbilitySet_Add "Reverent Purity" Puritycure
    /call AbilitySet_Add "Ardent Purity" Puritycure
    /call AbilitySet_Add "Merciful Purity" Puritycure
    /call AbilitySet_ChooseOuter Puritycure Puritycure
    
|- Challenge Taunt Over time Debuff
    /call AbilitySet_Add "Challenge for Honor" Challengetaunt
    /call AbilitySet_Add "Trial For Honor" Challengetaunt
    /call AbilitySet_Add "Charge for Honor" Challengetaunt
    /call AbilitySet_Add "Confrontation for Honor" Challengetaunt
    /call AbilitySet_Add "Provocation for Honor" Challengetaunt
    /call AbilitySet_Add "Demand for Honor" Challengetaunt
    /call AbilitySet_Add "Impose for Honor" Challengetaunt
    /call AbilitySet_Add "Refute for Honor" Challengetaunt
    /call AbilitySet_Add "Protest for Honor" Challengetaunt
    /call AbilitySet_Add "Parlay for Honor" Challengetaunt
    /call AbilitySet_ChooseOuter Challengetaunt Challengetaunt
    
|- Valiant Taunt With Built in heal.
    /call AbilitySet_Add "Valiant Disruption" Healtaunt
    /call AbilitySet_Add "Valiant Deflection" Healtaunt
    /call AbilitySet_Add "Valiant Defense" Healtaunt
    /call AbilitySet_Add "Valiant Diversion" Healtaunt
    /call AbilitySet_Add "Valiant Deterrence" Healtaunt
    /call AbilitySet_ChooseOuter Healtaunt Healtaunt
    
|- Undead DD 
    /call AbilitySet_Add "Doctrine of Abrogation" Doctrine
    /call AbilitySet_Add "Doctrine of Rescission" Doctrine
    /call AbilitySet_Add "Doctrine of Exculpation" Doctrine
    /call AbilitySet_Add "Doctrine of Abolishment" Doctrine
    /call AbilitySet_ChooseOuter Doctrine Doctrine
    
|- Group Wave heal 39-115
    /call AbilitySet_Add "Wave of Bereavement" WaveHeal
    /call AbilitySet_Add "Wave of Propitiation" WaveHeal
    /call AbilitySet_Add "Wave of Expiation" WaveHeal
    /call AbilitySet_Add "Wave of Grief" WaveHeal
    /call AbilitySet_Add "Wave of Sorrow" WaveHeal
    /call AbilitySet_Add "Wave of Contrition" WaveHeal
    /call AbilitySet_Add "Wave of Penitence" WaveHeal
    /call AbilitySet_Add "Wave of Remitment" WaveHeal
    /call AbilitySet_Add "Wave of Absolution" WaveHeal
    /call AbilitySet_Add "Wave of Forgiveness" WaveHeal
    /call AbilitySet_Add "Wave of Piety" WaveHeal
    /call AbilitySet_Add "Wave of Marr" WaveHeal
    /call AbilitySet_Add "Wave of Trushar" WaveHeal
    /call AbilitySet_Add "Healing Wave of Prexus" WaveHeal
    /call AbilitySet_Add "Wave of Healing" WaveHeal
    /call AbilitySet_Add "Wave of Life" WaveHeal
    /call AbilitySet_ChooseOuter WaveHeal WaveHeal
    /call AbilitySet_ChooseOuter WaveHeal2 WaveHeal "${WaveHeal}"

|- Scaling Selfheal
    /call AbilitySet_Add "Penitence" Selfheal
    /call AbilitySet_Add "Contrition" Selfheal
    /call AbilitySet_Add "Sorrow" Selfheal
    /call AbilitySet_Add "Grief" Selfheal
    /call AbilitySet_Add "Exaltation" Selfheal
    /call AbilitySet_Add "Propitiation" Selfheal
    /call AbilitySet_Add "Culpability" Selfheal
    /call AbilitySet_ChooseOuter Selfheal Selfheal
    
|- Reverse DS
    /call AbilitySet_Add "Mark of the Saint" Reverseds
    /call AbilitySet_Add "Mark of the Crusader" Reverseds
    /call AbilitySet_Add "Mark of the Pious" Reverseds
    /call AbilitySet_Add "Mark of the Pure" Reverseds
    /call AbilitySet_Add "Mark of the Defender" Reverseds
    /call AbilitySet_Add "Mark of the Reverent" Reverseds
    /call AbilitySet_Add "Mark of the Exemplar" Reverseds
    /call AbilitySet_Add "Mark of the Commander" Reverseds
    /call AbilitySet_Add "Mark of the Jade Cohort" Reverseds
    /call AbilitySet_Add "Mark of the Eclipsed Cohort" Reverseds
    /call AbilitySet_ChooseOuter Reverseds Reverseds
    
|- Pally Hot
    /call AbilitySet_Add "Ethereal Cleansing"       Cleansehot  | Level 44
    /call AbilitySet_Add "Celestial Cleansing"      Cleansehot  | Level 59
    /call AbilitySet_Add "Supernal Cleansing"       Cleansehot  | Level 64
    /call AbilitySet_Add "Pious Cleansing"          Cleansehot  | Level 69
    /call AbilitySet_Add "Sacred Cleansing"         Cleansehot  | Level 73
    /call AbilitySet_Add "Solemn Cleansing"         Cleansehot  | Level 78
    /call AbilitySet_Add "Devout Cleansing"         Cleansehot  | Level 93
    /call AbilitySet_Add "Earnest Cleansing"        Cleansehot  | Level 88
    /call AbilitySet_Add "Zealous Cleansing"        Cleansehot  | Level 93
    /call AbilitySet_Add "Reverent Cleansing"       Cleansehot  | Level 98
    /call AbilitySet_Add "Ardent Cleansing"         Cleansehot  | Level 103
    /call AbilitySet_Add "Merciful Cleansing"       Cleansehot  | Level 108
    /call AbilitySet_Add "Sincere Cleansing"        Cleansehot  | Level 113
    /call AbilitySet_Add "Forthright Cleansing"     Cleansehot  | Level 118
    /call AbilitySet_ChooseOuter Cleansehot Cleansehot
 
|- Burst Heal - heals target or Target of target 73-115   
    /call AbilitySet_Add "Burst of Sunlight" BurstHeal
    /call AbilitySet_Add "Burst of Morrow" BurstHeal    
    /call AbilitySet_Add "Burst of Dawnlight" BurstHeal
    /call AbilitySet_Add "Burst of Daybreak" BurstHeal
    /call AbilitySet_Add "Burst of Splendor" BurstHeal
    /call AbilitySet_Add "Burst of Sunrise" BurstHeal
    /call AbilitySet_Add "Burst of Dayspring" BurstHeal
    /call AbilitySet_Add "Burst of Morninglight" BurstHeal
    /call AbilitySet_Add "Burst of Wakening" BurstHeal
    /call AbilitySet_Add "Burst of Dawnbreak" BurstHeal
    /call AbilitySet_ChooseOuter BurstHeal BurstHeal

| - Curse Cure Line
    /call AbilitySet_Add "Remove Minor Curse" CurseCure
    /call AbilitySet_Add "Remove Lesser Curse" CurseCure
    /call AbilitySet_Add "Remove Curse" CurseCure
    /call AbilitySet_Add "Remove Greater Curse" CurseCure
    /call AbilitySet_ChooseOuter CurseCure CurseCure

|- Self Buff Armor Line Ac/Hp/Mana regen
    /call AbilitySet_Add "Aura of the Crusader"         ArmorSelfBuff  | Level 64
    /call AbilitySet_Add "Armor of the Champion"        ArmorSelfBuff  | Level 69
    /call AbilitySet_Add "Armor of Unrelenting Faith"   ArmorSelfBuff  | Level 73
    /call AbilitySet_Add "Armor of Inexorable Faith"    ArmorSelfBuff  | Level 78
    /call AbilitySet_Add "Armor of Unwavering Faith"    ArmorSelfBuff  | Level 83
    /call AbilitySet_Add "Armor of Implacable Faith"    ArmorSelfBuff  | Level 88
    /call AbilitySet_Add "Armor of Formidable Faith"    ArmorSelfBuff  | Level 93
    /call AbilitySet_Add "Armor of Formidable Grace"    ArmorSelfBuff  | Level 98
    /call AbilitySet_Add "Armor of Formidable Spirit"   ArmorSelfBuff  | Level 103
    /call AbilitySet_Add "Armor of Steadfast Faith"     ArmorSelfBuff  | Level 108
    /call AbilitySet_Add "Armor of Steadfast Grace"     ArmorSelfBuff  | Level 113
    /call AbilitySet_Add "Armor of Unyielding Grace"    ArmorSelfBuff  | Level 118
    /call AbilitySet_ChooseOuter ArmorSelfBuff ArmorSelfBuff

|- Pally Symbol Buff
    /call AbilitySet_Add "Symbol of Liako" Symbol
    /call AbilitySet_Add "Symbol of Jeneca" Symbol
    /call AbilitySet_Add "Symbol of Jyleel" Symbol
    /call AbilitySet_Add "Symbol of Erillion" Symbol
    /call AbilitySet_Add "Symbol of Burim" Symbol
    /call AbilitySet_Add "Symbol of Niparson" Symbol
    /call AbilitySet_Add "Symbol of Teralov" Symbol
    /call AbilitySet_Add "Symbol of Sevalak" Symbol
    /call AbilitySet_Add "Symbol of Bthur" Symbol
    /call AbilitySet_Add "Symbol of Jeron" Symbol
    /call AbilitySet_Add "Symbol of Marzin" Symbol
    /call AbilitySet_Add "Symbol of Naltron" Symbol
    /call AbilitySet_Add "Symbol of Pinzarn" Symbol
    /call AbilitySet_Add "Symbol of Ryltan" Symbol
    /call AbilitySet_Add "Symbol of Transal" Symbol
    /Call AbilitySet_ChooseOuter Symbol Symbol

|- Lesson Stun - Timer 6
    /call AbilitySet_Add "Quellious' Word of Tranquility"   LessonStun  | Level 54
    /call AbilitySet_Add "Quellious' Word of Serenity"      LessonStun  | Level 64
    /call AbilitySet_Add "Serene Command"                   LessonStun  | Level 68
    /call AbilitySet_Add "Lesson of Penitence"              LessonStun  | Level 72
    /call AbilitySet_Add "Lesson of Contrition"             LessonStun  | Level 77
    /call AbilitySet_Add "Lesson of Compunction"            LessonStun  | Level 82
    /call AbilitySet_Add "Lesson of Repentance"             LessonStun  | Level 87
    /call AbilitySet_Add "Lesson of Remorse"                LessonStun  | Level 92
    /call AbilitySet_Add "Lesson of Sorrow"                 LessonStun  | Level 97
    /call AbilitySet_Add "Lesson of Grief"                  LessonStun  | Level 102
    /call AbilitySet_Add "Lesson of Expiation"              LessonStun  | Level 107
    /call AbilitySet_Add "Lesson of Propitiation"           LessonStun  | Level 112
    /call AbilitySet_Add "Lesson of Guilt"                  LessonStun  | Level 117
    /call AbilitySet_ChooseOuter LessonStun LessonStun
    
|- Audacity Hate magic Debuff Over time
    /call AbilitySet_Add "Ardent Audacity" Audacity
    /call AbilitySet_Add "Fervent Audacity" Audacity
    /call AbilitySet_Add "Sanctimonious Audacity" Audacity
    /call AbilitySet_Add "Devout Audacity" Audacity
    /call AbilitySet_Add "Righteous Audacity" Audacity
    /call AbilitySet_ChooseOuter Audacity Audacity

|- Target Light Heal
    /call AbilitySet_Add "Salve"            LightHeal    | Level 1
    /call AbilitySet_Add "Minor Healing"    LightHeal    | Level 6
    /call AbilitySet_Add "Light Healing"    LightHeal    | Level 12
    /call AbilitySet_Add "Healing"          LightHeal    | Level 27
    /call AbilitySet_Add "Greater Healing"  LightHeal    | Level 36
    /call AbilitySet_Add "Superior Healing" LightHeal    | Level 48
    /call AbilitySet_ChooseOuter LightHeal LightHeal

|- ToT Light Heal
    /call AbilitySet_Add "Light of Life"    TotLightHeal    | Level 52
    /call AbilitySet_Add "Light of Nife"    TotLightHeal    | Level 63
    /call AbilitySet_Add "Light of Order"   TotLightHeal    | Level 65
    /call AbilitySet_Add "Light of Piety"   TotLightHeal    | Level 68
    /call AbilitySet_Add "Gleaming Light"   TotLightHeal    | Level 72
    /call AbilitySet_Add "Radiant Light"    TotLightHeal    | Level 77
    /call AbilitySet_Add "Shining Light"    TotLightHeal    | Level 82
    /call AbilitySet_Add "Joyous Light"     TotLightHeal    | Level 87
    /call AbilitySet_Add "Brilliant Light"  TotLightHeal    | Level 92
    /call AbilitySet_Add "Dazzling Light"   TotLightHeal    | Level 97
    /call AbilitySet_Add "Blessed Light"    TotLightHeal    | Level 102
    /call AbilitySet_Add "Merciful Light"   TotLightHeal    | Level 107
    /call AbilitySet_Add "Sincere Light"    TotLightHeal    | Level 112
    /call AbilitySet_Add "Raptured Light"   TotLightHeal    | Level 117
    /call AbilitySet_ChooseOuter TotLightHeal TotLightHeal
    /call AbilitySet_ChooseOuter TotLightHeal2 TotLightHeal "${TotLightHeal}"

|- Paladin Pacify LVL10-115
    /call AbilitySet_Add "Placating Words" Pacify
    /call AbilitySet_Add "Tranquil Words" Pacify
    /call AbilitySet_Add "Propitiate" Pacify
    /call AbilitySet_Add "Mollify" Pacify
    /call AbilitySet_Add "Reconcile" Pacify
    /call AbilitySet_Add "Dulcify" Pacify
    /call AbilitySet_Add "Soothe" Pacify
    /call AbilitySet_Add "Pacify" Pacify
    /call AbilitySet_Add "Calm" Pacify
    /call AbilitySet_Add "Lull" Pacify
    /call AbilitySet_ChooseOuter Pacify Pacify

|- Touch Heal Line LVL61 - LVL115
    /call AbilitySet_Add "Touch of Nife" Toucheal
    /call AbilitySet_Add "Touch of Piety" Toucheal
    /call AbilitySet_Add "Sacred Touch" Toucheal
    /call AbilitySet_Add "Solemn Touch" Toucheal
    /call AbilitySet_Add "Devout Touch" Toucheal
    /call AbilitySet_Add "Earnest Touch" Toucheal
    /call AbilitySet_Add "Zealous Touch" Toucheal
    /call AbilitySet_Add "Reverent Touch" Toucheal
    /call AbilitySet_Add "Ardent Touch" Toucheal
    /call AbilitySet_Add "Merciful Touch" Toucheal
    /call AbilitySet_Add "Sincere Touch" Toucheal
    /call AbilitySet_Add "Soothing Touch" Toucheal
    /call AbilitySet_ChooseOuter Toucheal Toucheal

    | Undead Nuke
    /call AbilitySet_Add "Ward Undead"                  AntiUndeadNuke  | Level 14
    /call AbilitySet_Add "Expulse Undead"               AntiUndeadNuke  | Level 30
    /call AbilitySet_Add "Dismiss Undead"               AntiUndeadNuke  | Level 46
    /call AbilitySet_Add "Expel Undead"                 AntiUndeadNuke  | Level 54
    /call AbilitySet_Add "Deny Undead"                  AntiUndeadNuke  | Level 62 - Timer 7
    /call AbilitySet_Add "Spurn Undead"                 AntiUndeadNuke  | Level 67 - Timer 7
    |/call AbilitySet_Add "Wraithguard's Vengeance"      AntiUndeadNuke  | Level 75 - Unobtainable?
    /call AbilitySet_Add "Annihilate the Undead"        AntiUndeadNuke  | Level 86 - Res Debuff / Extra Damage
    /call AbilitySet_Add "Abolish the Undead"           AntiUndeadNuke  | Level 91 - Res Debuff / Extra Damage
    /call AbilitySet_Add "Doctrine of Abrogation"       AntiUndeadNuke  | Level 96
    /call AbilitySet_Add "Abrogate the Undead"          AntiUndeadNuke  | Level 96 - Res Debuff / Extra Damage
    /call AbilitySet_Add "Doctrine of Rescission"       AntiUndeadNuke  | Level 101
    /call AbilitySet_Add "Doctrine of Exculpation"      AntiUndeadNuke  | Level 106
    /call AbilitySet_Add "Doctrine of Abolishment"      AntiUndeadNuke  | Level 111
    /call AbilitySet_Add "Doctrine of Annulment"        AntiUndeadNuke  | Level 116
    /call AbilitySet_ChooseOuter AntiUndeadNuke AntiUndeadNuke

|-  End of Spells 

|- Starting Combat Abilitys Section
|- One Offs we will use
    /call AbilitySet_Add "Holyforge Discipline" Undeadburn
    /call AbilitySet_ChooseOuter Undeadburn Undeadburn
    /call AbilitySet_Add "Sanctification Discipline" Spellblock
    /call AbilitySet_ChooseOuter Spellblock Spellblock
    


|- Withstand Combat Line of Defense - Update to format once tested
    /call AbilitySet_Add "Withstand" meleemit
    /call AbilitySet_Add "Defy" meleemit
    /call AbilitySet_Add "Renounce" meleemit
    /call AbilitySet_Add "Reprove" meleemit
    /call AbilitySet_Add "Repel" meleemit
    /call AbilitySet_Add "Spurn" meleemit
    /call AbilitySet_Add "Thwart" meleemit
    /call AbilitySet_Add "Repudiate" meleemit
    /call AbilitySet_ChooseOuter meleemit meleemit

|---Fast Endurance regen - Update to new Format Once tested
    /call AbilitySet_Add "Second Wind" endregen
    /call AbilitySet_Add "Third Wind" endregen
    /call AbilitySet_Add "Fourth Wind" endregen
    /call AbilitySet_Add "Respite" endregen
    /call AbilitySet_Add "Reprieve" endregen
    /call AbilitySet_Add "Rest" endregen
    /call AbilitySet_Add "Breather" endregen
    /call AbilitySet_Add "Hiatus" endregen
    /call AbilitySet_Add "Relax" endregen
    /call AbilitySet_Add "Night's Calming" endregen
    /call AbilitySet_ChooseOuter endregen endregen

|- Armor Timer 11 - Armor of 
    /call AbilitySet_Add "Armor of the Forthright" Armordisc
    /call AbilitySet_Add "Armor of Sincerity" Armordisc
    /call AbilitySet_Add "Armor of Mercy" Armordisc
    /call AbilitySet_Add "Armor of Ardency" Armordisc
    /call AbilitySet_Add "Armor of Reverence" Armordisc
    /call AbilitySet_Add "Armor of Zeal" Armordisc
    /call AbilitySet_ChooseOuter Armordisc Armordisc

|- Improved Super Taunt - Gets you Aggro for X seconds and reduces other Haters generation.
    /call AbilitySet_Add "Unrelenting Affirmation" Affirmation
    /call AbilitySet_Add "Undivided Affirmation" Affirmation
    /call AbilitySet_Add "Unbroken Affirmation" Affirmation
    /call AbilitySet_Add "Unflinching Affirmation" Affirmation
    /call AbilitySet_Add "Unyielding Affirmation" Affirmation
    /call AbilitySet_Add "Unending Affirmation" Affirmation
    /call AbilitySet_ChooseOuter Affirmation Affirmation
    
|- Righteous Strikes Line 
    /call AbilitySet_Add "Righteous Antipathy" Righteousstrike
    /call AbilitySet_Add "Righteous Fury" Righteousstrike
    /call AbilitySet_Add "Righteous Indignation" Righteousstrike
    /call AbilitySet_Add "Righteous Vexation" Righteousstrike
    /call AbilitySet_Add "Righteous Umbrage" Righteousstrike
    /call AbilitySet_Add "Righteous Condemnation" Righteousstrike
    /call AbilitySet_Add "Righteous Antipathy" Righteousstrike
    /call AbilitySet_ChooseOuter Righteousstrike Righteousstrike

|- Pentient Armor Discipline
    /call AbilitySet_Add "Fervent Penitence" Pentientarmor
    /call AbilitySet_Add "Reverent Penitence" Pentientarmor
    /call AbilitySet_Add "Devout Penitence" Pentientarmor
    /call AbilitySet_Add "Merciful Penitence" Pentientarmor
    /call AbilitySet_Add "Sincere Penitence" Pentientarmor
    /call AbilitySet_ChooseOuter Pentientarmor Pentientarmor

|- Holy Guardian Discipline
    /call AbilitySet_Add "Revered Guardian Discipline" Holyguard
    /call AbilitySet_Add "Blessed Guardian Discipline" Holyguard
    /call AbilitySet_Add "Holy Guardian Discipline" Holyguard
    /call AbilitySet_ChooseOuter Holyguard Holyguard

|- Mantle Line of Discipline Timer 5 defensive burn
    /call AbilitySet_Add "Supernal Mantle" Mantle
    /call AbilitySet_Add "Mantle of the Sapphire Cohort" Mantle
    /call AbilitySet_Add "Kar`Zok Mantle" Mantle
    /call AbilitySet_Add "Skalber Mantle" Mantle
    /call AbilitySet_Add "Brightwing Mantle" Mantle
    /call AbilitySet_Add "Prominent Mantle" Mantle
    /call AbilitySet_Add "Exalted Mantle" Mantle
    /call AbilitySet_Add "Honorific Mantle" Mantle
    /call AbilitySet_Add "Armor of Decorum" Mantle
    /call AbilitySet_Add "Armor of Righteousness" Mantle
    /call AbilitySet_ChooseOuter Mantle Mantle

|- Reflexive Strike Heal
    /call AbilitySet_Add "Reflexive Redemption" Reflexstrike
    /call AbilitySet_Add "Reflexive Righteousness" Reflexstrike
    /call AbilitySet_Add "Reflexive Reverence" Reflexstrike
    /call AbilitySet_ChooseOuter Reflexstrike Reflexstrike
/return

Sub PAL_ModeConfigMODETANK
    /varset IsTanking TRUE
    /varset IsHealing TRUE
    /if ( ${CrushTimer6.NotEqual[NULL]} ) {
        /varset Spell1 ${CrushTimer6}
    } else { 
        /varset Spell1 ${StunTimer5}
    }
    /if ( ${CrushTimer5.NotEqual[NULL]} ) {
        /varset Spell2 ${CrushTimer5}
    } else { 
        /varset Spell2 ${StunTimer4}
    }
    /if ( ${Healtaunt.NotEqual[NULL]} ) {
        /varset Spell3 ${Healtaunt}
    } else { 
        /varset Spell3 ${LessonStun}
    }
    /varset Spell4 ${Lowaggronuke}
    /if ( ${HealNuke.NotEqual[NULL]} ) {
        /varset Spell5 ${HealNuke}
    } else { 
        /varset Spell5 ${AntiUndeadNuke}
    }
    /varset Spell6 ${WaveHeal}
    /varset Spell7 ${TotLightHeal}
    /varset Spell8 ${BurstHeal}
    /if (${Me.NumGems} >=9) {    
        /varset Spell9 ${Challengetaunt}
    }
    /if (${Me.NumGems} >=10) {
        /varset Spell10 ${TempHP}
    }
    /if (${Me.NumGems} >=11) {    
        /varset Spell11 ${Preservation}
    }
    /if (${Me.NumGems} >=12) {
        /varset Spell12 ${Dicho}
    }
    /if (${Me.NumGems} >=13) {
        /varset Spell13 Null
    }
    
    
    /call Ordered_Rotation_Clear PAL_Downtime_MODETANK_Rotation
    /call Ordered_Rotation_Clear PAL_Burn_MODETANK_Rotation
    /call Ordered_Rotation_Clear PAL_DPS_MODETANK_Rotation

    |- Self Buffs
    /call PAL_DefaultSelfBuffRotationConfig PAL_Downtime_MODETANK_Rotation
    |- Group Buffs
    /call PAL_DefaultBuffGroupConfig
    |- Heals
    /call PAL_DefaultHealRotationConfig

    | - Burn AA Rotation
    | - Based on personal testing for Maximum DPS. 
    /call AddToRotation PAL_Burn_MODETANK_Rotation  "Valorous Rage"                 AA      ${Parse[0,"( TRUE )"]}
    /call AddToRotation PAL_Burn_MODETANK_Rotation  "Inquisitor's Judgment"         AA      ${Parse[0,"( TRUE )"]}
    /call AddToRotation PAL_Burn_MODETANK_Rotation  "Thunder of Karana"             AA      ${Parse[0,"( ${DoNuke[SETTINGVAL]} )"]}
    /call AddToRotation PAL_Burn_MODETANK_Rotation  "Group Armor of The Inquisitor" AA      ${Parse[0,"( TRUE )"]}
    /call AddToRotation PAL_Burn_MODETANK_Rotation  "${Undeadburn}"                 Disc    ${Parse[0,"( ${Undeadburn.NotEqual[NULL]} && !${Me.ActiveDisc.ID} && ${ClassMode[SETTINGVAL]} )"]}
    /call AddToRotation PAL_Burn_MODETANK_Rotation  "${Righteousstrike}"            Disc    ${Parse[0,"( ${Righteousstrike.NotEqual[NULL]} && !${Me.ActiveDisc.ID} )"]}

    | - DPS Rotations
    | - Bandolier Actions.
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "/bandolier activate Shield"    Command ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Shield].Active} && ${Bool[${Me.Bandolier[Shield].Index}]} && BURNCHECK )"]} 
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "/bandolier activate 2HS"       Command ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[2HS].Active} && ${Bool[${Me.Bandolier[2HS].Index}]} && ${XAssist.XTFullHaterCount}<${BurnMobCount[SETTINGVAL]} && !${Target.Named} )"]}

    |- Start With Emergency Mitgation Abilities.
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "Shield Flash"                  AA      ${Parse[0,"( ${Me.PctHPs} <= ${Flashhp[SETTINGVAL]} )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${Mantle}"                     Disc    ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Mantle}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${Holyguard}"                  Disc    ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Holyguard}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${Armordisc}"                  Disc    ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Armordisc}]} && !${Me.ActiveDisc.ID}  )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${Pentientarmor}"              Disc    ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Pentientarmor}]} && !${Me.ActiveDisc.ID}  )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${meleemit}"                   Disc    ${Parse[0,"( TRUE )"]} 
    /call AddToRotation	PAL_DPS_MODETANK_Rotation   "${TotLightHeal}"               Spell   ${Parse[0,"(  ${Me.TargetOfTarget.PctHPs} < ${TotHealPoint[SETTINGVAL]}  )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${BurstHeal}"                  Spell   ${Parse[0,"(  ${Me.TargetOfTarget.PctHPs} < ${TotHealPoint[SETTINGVAL]}  )"]}

    | - Followed By taunts to gain Aggro
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "Hallowed Lodestar"             AA      ${Parse[0,"( ${XAssist.XTFullHaterCount}>2 && ${Me.XTAggroCount} > 0 && ${Me.AltAbilityReady[Hallowed Lodestar]} )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "Beacon of the Righteous"       AA      ${Parse[0,"( ${XAssist.XTFullHaterCount}>2 && ${Me.XTAggroCount} > 0 && ${Me.AltAbilityReady[Beacon of the Righteous]} )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "Heroic Leap"                   AA      ${Parse[0,"( ${XAssist.XTFullHaterCount}>2 && ${Me.XTAggroCount} > 0 && ${Me.AltAbilityReady[Heroic Leap]} )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "Force of Disruption"           AA      ${Parse[0,"( ${Me.AltAbility[Force of Disruption].Rank} >= 7 && !${Me.Buff[Knight's yaulp].ID} && ${Target.Distance} < 30 )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "Taunt"                         Ability ${Parse[0,"( ${Me.AbilityReady[Taunt]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${Challengetaunt}"             Spell   ${Parse[0,"( !${Target.Buff[${Challengetaunt}].ID} )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${StunTimer4}"                 Spell   ${Parse[0,"( DETSTUNCHECK )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${StunTimer5}"                 Spell   ${Parse[0,"( DETSTUNCHECK )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${LessonStun}"                 Spell   ${Parse[0,"( DETSTUNCHECK )"]}   
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${CrushTimer5}"                  Spell   ${Parse[0,"( TRUE )"]}  
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${CrushTimer6}"                Spell   ${Parse[0,"( TRUE )"]} 

    | - DPs/Heal items - Not Oh Shits or taunts.
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "Armor of the Inquisitor"       AA      ${Parse[0,"( TRUE )"]} 
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${Healtaunt}"                  Spell   ${Parse[0,"( TRUE )"]} 
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${HealNuke}"                   Spell   ${Parse[0,"( TRUE )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${Lowaggronuke}"               Spell   ${Parse[0,"( TRUE )"]}  
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${Dicho}"                      Spell	${Parse[0,"( TRUE )"]}      
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${AntiUndeadNuke}"             Spell   ${Parse[0,"( ${Target.Body.Name.Equal[undead]} )"]}
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "Vanquish The Fallen"           AA      ${Parse[0,"( ${Target.Body.Name.Equal[undead]} )"]} 
    /call AddToRotation PAL_DPS_MODETANK_Rotation   "${ChestItemName[SETTINGVAL]}"  Item    ${Parse[1,"( ${Spell[${FindItem[${ChestItemName[SETTINGVAL]}].Spell}].Stacks} && (!${FindItem[${ChestItemName[SETTINGVAL]}].TimerReady}) && ${DoChestClick[SETTINGVAL]} )"]}
/return


Sub PAL_ModeConfigMODEDPS
    /varset IsHealing TRUE
    /if ( ${CrushTimer6.NotEqual[NULL]} ) {
        /varset Spell1 ${CrushTimer6}
    } else { 
        /varset Spell1 ${StunTimer5}
    }
    /varset Spell2 ${Lowaggronuke}
    /if ( ${HealNuke.NotEqual[NULL]} ) {
        /varset Spell3 ${HealNuke}
    } else { 
        /varset Spell3 ${LessonStun}
    }
    /varset Spell4 ${AntiUndeadNuke}
    /varset Spell5 ${WaveHeal}
    /varset Spell6 ${TotLightHeal}
    /varset Spell7 ${BurstHeal}
    /varset Spell8 ${Reverseds}
    /if (${Me.NumGems} >=9) {    
        /varset Spell9 ${DebuffNuke}
    }
    /if (${Me.NumGems} >=10) {
        /varset Spell10 ${Healproc}
    }
    /if (${Me.NumGems} >=11) {    
        /varset Spell11 ${Aurora}
    }
    /if (${Me.NumGems} >=12) {
        /varset Spell12 ${Dicho}
    }
    /if (${Me.NumGems} >=13) {
        /varset Spell13 Null
    }
    
  

    /call Ordered_Rotation_Clear PAL_Downtime_MODEDPS_Rotation
    /call Ordered_Rotation_Clear PAL_Burn_MODEDPS_Rotation
    /call Ordered_Rotation_Clear PAL_DPS_MODEDPS_Rotation

    /call PAL_DefaultSelfBuffRotationConfig PAL_Downtime_MODEDPS_Rotation
    |- Group Buffs
    /call PAL_DefaultBuffGroupConfig
    |- Heals
    /call PAL_DefaultHealRotationConfig

	| - Burn AA Rotation
	| - Based on personal testing for Maximum DPS. 
	/call AddToRotation PAL_Burn_MODEDPS_Rotation  "Valorous Rage" AA TRUE
	/call AddToRotation PAL_Burn_MODEDPS_Rotation  "Inquisitor's Judgment" AA TRUE
	/call AddToRotation PAL_Burn_MODEDPS_Rotation  "Thunder of Karana" AA ${Parse[0,"( ${DoNuke[SETTINGVAL]} )"]}
	/call AddToRotation PAL_Burn_MODEDPS_Rotation  "Group Armor of The Inquisitor" AA TRUE
	/call AddToRotation PAL_Burn_MODEDPS_Rotation  "${Undeadburn}" Disc ${Parse[0,"( ${Undeadburn.NotEqual[NULL]} && !${Me.ActiveDisc.ID} && ${ClassMode[SETTINGVAL]} )"]}
	/call AddToRotation PAL_Burn_MODEDPS_Rotation  "${Righteousstrike}" Disc  ${Parse[0,"( ${Righteousstrike.NotEqual[NULL]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation PAL_Burn_MODEDPS_Rotation  "${Healproc}" Spell ${Parse[0,"( ${PCSpellReady[Healproc]} )"]}

	| - DPS Mode Rotation
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "Marr's Gift" AA ${Parse[0,"( ${Me.PctMana} <=60 )"]}
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "${Dicho}" Spell ${Parse[0,"( ${Me.TargetOfTarget.PctHPs} <= 35  )"]}
    /call AddToRotation	PAL_DPS_MODEDPS_Rotation    "${TotLightHeal}" Spell ${Parse[0,"( ( ${Me.Level} >= 112 ) && ${Me.TargetOfTarget.PctHPs} < ${MainHealPoint[SETTINGVAL]} )"]}
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "${BurstHeal}"  Spell ${Parse[0,"( ( ${Me.Level} >= 113 ) &&${Me.TargetOfTarget.PctHPs} < ${MainHealPoint[SETTINGVAL]} )"]}
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "${DebuffNuke}" Spell ${Parse[0,"( ( ${Target.Body.Name.Equal[undead]} || ${Me.Level} >=96 )  && !${Target.Buff[${DebuffNuke}].ID} && ${DoNukes[SETTINGVAL]} )"]}
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "${AntiUndeadNuke}" Spell ${Parse[0,"( ${Target.Body.Name.Equal[undead]} )"]}
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "${Reverseds}" Spell ${Parse[0,"( !${Target.Buff[${Reverseds}].ID} && ${DoReverseDS[SETTINGVAL]} )"]}
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "${Lowaggronuke}" Spell ${Parse[0,"( ${DoNukes[SETTINGVAL]} )"]}  
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "${CrushTimer6}" Spell  ${Parse[0,"( ${DoNukes[SETTINGVAL]} && ${Me.SecondaryPctAggro}>60 )"]}  
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "${HealNuke}" Spell  TRUE
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "Vanquish The Fallen" AA ${Parse[0,"( ${Target.Body.Name.Equal[undead]} )"]}
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "Disruptive Persecution" AA ${Parse[0,"( (${Me.AltAbility[Disruptive Persecution].Rank}>=3 && !${Me.Buff[Knight's yaulp].ID}) )"]}
    /call AddToRotation PAL_DPS_MODEDPS_Rotation    "${ChestItemName[SETTINGVAL]}" Item ${Parse[1,"( ${Spell[${FindItem[${ChestItemName[SETTINGVAL]}].Spell}].Stacks} && (!${FindItem[${ChestItemName[SETTINGVAL]}].TimerReady}) && ${DoChestClick[SETTINGVAL]} )"]}

/return
Sub PAL_ModeConfigMODETLP

    /echo Welcome To TLP Mode Paladin - As with all RGmercs TLP Tanks There is 2 modes in 1
    /echo You Can control Whether your the Tank or not with a Simple /dotank 1/0

    /if  ( ${DoTank[SETTINGVAL]} ) { 
        /echo I am in TLP Tank Mode
        /varset IsTanking TRUE
    } else {
        /echo I am in TLP DPS Mode 
        /varset IsTanking FALSE
    }

    /varset IsHealing TRUE

| SpellBar Setup

    | Set up Gems based on if we have Challengetaunt, since it shifts everything down by 1
    /if ( ${Challengetaunt.NotEqual[NULL]} ) { 
        | - Gem 1 - Challengetaunt
        /varset Spell1 ${Challengetaunt}
        
        | - Gem 2 - StunTimer4
        |           Timer 4
        /varset Spell2 ${StunTimer4}

        | - Gem 3 - StunTimer5 / CrushTimer5
        |           Timer 5, StunTimer5 until CrushTimer5 available at 82 (SoD)
        /if ( ${CrushTimer5.NotEqual[NULL]} ) {
            /varset Spell3 ${CrushTimer5}
        } else { 
            /varset Spell3 ${StunTimer5}
        }

        | - Gem 4 - LessonStun / CrushTimer6
        |           Timer 6, LessonStun until CrushTimer6 available at 85 (SoD)
        /if ( ${CrushTimer6.NotEqual[NULL]} ) {
            /varset Spell4 ${CrushTimer6}
        } else { 
            /varset Spell4 ${LessonStun}
        }

        | - Gem 5 - TotLightHeal
        /varset Spell5 ${TotLightHeal}

        | - Gem 6 - BurstHeal
        /varset Spell6 ${BurstHeal}

        | - Gem 7 - Preservation
        /varset Spell7 ${Preservation}

        | - Gem 8 - TempHP
        |           SoD Start
        /varset Spell8 ${TempHP}

        | - Gem 9 - Healward
        |           UF Start
        /varset Spell9 ${Healward}

        | - Gem 10 - HealNuke
        |            UF Start
        /varset Spell10 ${HealNuke}

        | - Gem 11 - DebuffNuke
        /varset Spell11 ${DebuffNuke}

        | - Gem 12 - NULL
        /varset Spell12 NULL

        | - Gem 13 - Always NULL
        |   ROS Unlock
        /varset Spell13 NULL

    } else {
        | - Gem 2 - StunTimer4
        |           Timer 4
        /varset Spell1 ${StunTimer4}

        | - Gem 2 - StunTimer5 / CrushTimer5
        |           Timer 5, StunTimer5 until CrushTimer5 available at 82 (SoD)
        /if ( ${CrushTimer5.NotEqual[NULL]} ) {
            /varset Spell2 ${CrushTimer5}
        } else { 
            /varset Spell2 ${StunTimer5}
        }

        | - Gem 3 - LessonStun / CrushTimer6
        |           Timer 6, LessonStun until CrushTimer6 available at 85 (SoD)
        /if ( ${CrushTimer6.NotEqual[NULL]} ) {
            /varset Spell3 ${CrushTimer6}
        } else { 
            /varset Spell3 ${LessonStun}
        }

        | - Gem 4 - TotLightHeal
        /varset Spell4 ${TotLightHeal}

        | - Gem 5 - BurstHeal
        |           Since BurstHeal starts at 73, load up second ToT Heal till then?
        /if ( ${BurstHeal.NotEqual[NULL]} ) {
            /varset Spell5 ${BurstHeal}
        } else { 
            /varset Spell5 ${TotLightHeal2}
        }

        | - Gem 6 - WaveHeal
        |           For TLP Mode we dont see a HealNuke before level 85
        /varset Spell6 ${WaveHeal}


        | - Gem 7 - Reverseds (When Enabled & Have Spell)
        |           Cleansehot when Rerverseds off or missing
        /if (${DoReverseDS[SETTINGVAL]} && ${Reverseds.NotEqual[NULL]}) {
            /varset Spell7 ${Reverseds}
        } else {
            /varset Spell7 ${Cleansehot}
        }

        | - Gem 8 - Preservation
        |           If we only have 8 Gem Slots leave as NULL
        /if ( ${Me.NumGems} == 8 ) {    
            /varset Spell8 NULL
        } else { 
            | Challengetaunt if we have it, if not WaveHeal2?
            /if ( ${Challengetaunt.NotEqual[NULL]} ) { 
                /varset Spell8 ${Challengetaunt}
            } else {
                /varset Spell8 ${WaveHeal2}   
            }
        }  

        | - Gem 9 - Challengetaunt
        |           If we only have 9 Gem Slots leave as NULL
        /if ( ${Me.NumGems} == 9 ) {    
            /varset Spell9 NULL
        } else {
            /varset Spell9 ${Preservation}
        } 

        | - Gem 10 - TempHP At Level 84
        |   SoF Unlock at Level 75
        | Will probably be NULL unless you are leveling after UF release and buy this additional
        | spell slot. Even then youll have TempHP for 1 level before you should swap to non TLP mode
        /if ( ${Me.NumGems} == 10 ) {
            /varset Spell10 NULL
        } else {
            /varset Spell10 ${TempHP}
        }

        | - Gem 11 - AntiUndeadNuke
        |   UF Unlock at Level 80
        | At this point should not be using TLP mode unless leveling. Only case you will have
        | this gem slot is if UF is unlocked and you bought the AA at level 80
        | Might as well load up AntiUndeadNuke!
        /if ( ${Me.NumGems} == 11 ) {
            /varset Spell11 NULL
        } else {
            /varset Spell11 ${AntiUndeadNuke}
        }

        | - Gem 12 - Dicho
        |   UF Unlock at Level 80
        | At this point should not be using TLP mode unless leveling. Only case you will have
        | this gem slot is if UF is unlocked and you bought the AA at level 80
        | Even then Dicho starts at level 111. So slot will most likely be NULL
        /if ( ${Me.NumGems} == 12 ) {
            /varset Spell12 NULL
        } else {
            /varset Spell12 ${Dicho}
        }

        | - Gem 13 - Always NULL
        |   ROS Unlock
        /varset Spell13 NULL
    }

|- Rotation Setup
    /call Ordered_Rotation_Clear PAL_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_Clear PAL_Burn_MODETLP_Rotation
    /call Ordered_Rotation_Clear PAL_DPS_MODETLP_Rotation

    |- Self Buffs
    /call PAL_DefaultSelfBuffRotationConfig PAL_Downtime_MODETLP_Rotation

    |- Group Buffs
    /call PAL_DefaultBuffGroupConfig

    |- Heals
    /call PAL_DefaultHealRotationConfig

    | - Bandolier Actions.
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "/bandolier activate Shield"    Command ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Shield].Active} && ${Bool[${Me.Bandolier[Shield].Index}]} && BURNCHECK )"]} 
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "/bandolier activate 2HS"       Command ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[2HS].Active} && ${Bool[${Me.Bandolier[2HS].Index}]} && ${XAssist.XTFullHaterCount}<${BurnMobCount[SETTINGVAL]} && !${Target.Named} )"]}

    |- Start With Emergency Mitgation Abilities.
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "Shield Flash"                  AA      ${Parse[0,"( ${DoTank[SETTINGVAL]} && ${Me.PctHPs} <= ${Flashhp[SETTINGVAL]} )"]}
	/call AddToRotation PAL_DPS_MODETLP_Rotation   "${Mantle}"                     Disc    ${Parse[0,"( ${DoTank[SETTINGVAL]} && (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Mantle}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "${Holyguard}"                  Disc    ${Parse[0,"( ${DoTank[SETTINGVAL]} && (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Holyguard}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "${Armordisc}"                  Disc    ${Parse[0,"( ${DoTank[SETTINGVAL]} && (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Armordisc}]} && !${Me.ActiveDisc.ID}  )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "${Pentientarmor}"              Disc    ${Parse[0,"( ${DoTank[SETTINGVAL]} && (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Pentientarmor}]} && !${Me.ActiveDisc.ID}  )"]}
	/call AddToRotation PAL_DPS_MODETLP_Rotation   "${meleemit}"                   Disc    ${Parse[0,"( ${DoTank[SETTINGVAL]} )"]} 
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "Guard of Righteousness"        Disc    ${Parse[0,"( ${DoTank[SETTINGVAL]} && (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) )"]} 
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "Armor of the Inquisitor"       AA      ${Parse[0,"( ${DoTank[SETTINGVAL]} && (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) )"]} 
<<<<<<< rgmercs/classes/rgpalutil.inc
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "${Epic}"                       "Item"  ${Parse[0,"( ${DoEpic[SETTINGVAL]} && ${FindItem[${Epic}].Spell.Stacks} && (!${FindItem[${Epic}].TimerReady}) && (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ))"]}
=======
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "${Epic}"                       Item    ${Parse[0,"( ${DoEpic[SETTINGVAL]} && ${Spell[${FindItem[${Epic}].Spell}].Stacks} && (!${FindItem[${Epic}].TimerReady}) && (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ))"]}
>>>>>>> rgmercs/classes/rgpalutil.inc
   
    |- TOT Heals Usable On Independant timers Not Locked to tanking or not
    /call AddToRotation	PAL_DPS_MODETLP_Rotation   "${TotLightHeal}"               Spell   ${Parse[0,"( ${Me.TargetOfTarget.PctHPs} < ${TotHealPoint[SETTINGVAL]}  )"]}
    /call AddToRotation	PAL_DPS_MODETLP_Rotation   "${TotLightHeal2}"              Spell   ${Parse[0,"( ${Me.TargetOfTarget.PctHPs} < ${TotHealPoint[SETTINGVAL]}  )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "${BurstHeal}"                  Spell   ${Parse[0,"( ${Me.TargetOfTarget.PctHPs} < ${TotHealPoint[SETTINGVAL]}  )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "${Cleansehot}"                 Spell   ${Parse[0,"( ${Me.TargetOfTarget.PctHPs} < ${TotHealPoint[SETTINGVAL]}  )"]}
    
    | - Followed By taunts to gain Aggro
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "Hallowed Lodestar"             AA      ${Parse[0,"( ${DoTank[SETTINGVAL]} && ${XAssist.XTFullHaterCount}>2 && ${Me.XTAggroCount} > 0 && ${RG_AAReady[Hallowed Lodestar]} )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "Beacon of the Righteous"       AA      ${Parse[0,"( ${DoTank[SETTINGVAL]} && ${XAssist.XTFullHaterCount}>2 && ${Me.XTAggroCount} > 0 && ${RG_AAReady[Beacon of the Righteous]} )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "Heroic Leap"                   AA      ${Parse[0,"( ${DoTank[SETTINGVAL]} && ${XAssist.XTFullHaterCount}>2 && ${Me.XTAggroCount} > 0 && ${RG_AAReady[Heroic Leap]} )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "Force of Disruption"           AA      ${Parse[0,"( ${DoTank[SETTINGVAL]} && ${Me.AltAbility[Force of Disruption].Rank} >= 7 && !${Me.Buff[Knight's yaulp].ID} && ${Target.Distance} < 30 )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "Taunt"                         Ability ${Parse[0,"( ${DoTank[SETTINGVAL]} && ${Me.AbilityReady[Taunt]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "${Challengetaunt}"             Spell   ${Parse[0,"( ${DoTank[SETTINGVAL]} && !${Target.Buff[${Challengetaunt}].ID} )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "${StunTimer4}"                 Spell   ${Parse[0,"( ${DoTank[SETTINGVAL]} && DETSTUNCHECK )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "${StunTimer5}"                 Spell   ${Parse[0,"( ${DoTank[SETTINGVAL]} && DETSTUNCHECK )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation   "${LessonStun}"                 Spell   ${Parse[0,"( ${DoTank[SETTINGVAL]} && DETSTUNCHECK )"]}   
	/call AddToRotation PAL_DPS_MODETLP_Rotation   "${CrushTimer5}"                  Spell   ${Parse[0,"( ${DoTank[SETTINGVAL]} )"]}  
	/call AddToRotation PAL_DPS_MODETLP_Rotation   "${CrushTimer6}"                Spell   ${Parse[0,"( ${DoTank[SETTINGVAL]} )"]} 
    	       
   	| - DPS Mode Rotation
    /call AddToRotation PAL_DPS_MODETLP_Rotation    "Marr's Gift"                  AA      ${Parse[0,"( ${Me.PctMana} <=60 )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation    "${Dicho}"                     Spell   ${Parse[0,"( ${Me.TargetOfTarget.PctHPs} <= 35  )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation    "${DebuffNuke}"                Spell   ${Parse[0,"( ( ${Target.Body.Name.Equal[undead]} || ${Me.Level} >=96 )  && !${Target.Buff[${DebuffNuke}].ID} && ${DoNukes[SETTINGVAL]} )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation    "${AntiUndeadNuke}"            Spell   ${Parse[0,"( ${Target.Body.Name.Equal[undead]} )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation    "${Reverseds}"                 Spell   ${Parse[0,"( !${Target.Buff[${Reverseds}].ID} && ${DoReverseDS[SETTINGVAL]} )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation    "${Lowaggronuke}"              Spell   ${Parse[0,"( ${DoNukes[SETTINGVAL]} )"]}  
    /call AddToRotation PAL_DPS_MODETLP_Rotation    "${CrushTimer6}"               Spell   ${Parse[0,"( ${DoNukes[SETTINGVAL]} && ${Me.SecondaryPctAggro}>60 )"]}  
    /call AddToRotation PAL_DPS_MODETLP_Rotation    "${HealNuke}"                  Spell   ${Parse[0,"( TRUE )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation    "Vanquish The Fallen"          AA      ${Parse[0,"( ${Target.Body.Name.Equal[undead]} )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation    "Disruptive Persecution"       AA      ${Parse[0,"( (${Me.AltAbility[Disruptive Persecution].Rank}>=3 && !${Me.Buff[Knight's yaulp].ID}) )"]}
    /call AddToRotation PAL_DPS_MODETLP_Rotation    "${ChestItemName[SETTINGVAL]}" Item    ${Parse[1,"( ${Spell[${FindItem[${ChestItemName[SETTINGVAL]}].Spell}].Stacks} && (!${FindItem[${ChestItemName[SETTINGVAL]}].TimerReady}) && ${DoChestClick[SETTINGVAL]} )"]}

    | - Burn AA Rotation
	| - Based on personal testing for Maximum DPS. 
    /call AddToRotation PAL_Burn_MODETLP_Rotation  "Spire of Chivalry"             AA      ${Parse[0,"( ${RG_AAReady[Spire of Chivalry]} && !${Me.Song[Group Armor of the Inquisitor].ID} && !${Me.Song[Armor of the Inquisitor].ID} && !${Me.Buff[Spire of Chivalry].ID} )"]}
	/call AddToRotation PAL_Burn_MODETLP_Rotation  "Valorous Rage"                 AA      ${Parse[0,"( TRUE )"]}
	/call AddToRotation PAL_Burn_MODETLP_Rotation  "Inquisitor's Judgment"         AA      ${Parse[0,"( TRUE )"]}
	/call AddToRotation PAL_Burn_MODETLP_Rotation  "Thunder of Karana"             AA      ${Parse[0,"( ${DoNuke[SETTINGVAL]} )"]}
	/call AddToRotation PAL_Burn_MODETLP_Rotation  "Group Armor of The Inquisitor" AA      ${Parse[0,"( TRUE )"]}
	/call AddToRotation PAL_Burn_MODETLP_Rotation  "${Undeadburn}"                 Disc    ${Parse[0,"( ${Undeadburn.NotEqual[NULL]} && !${Me.ActiveDisc.ID} && ${ClassMode[SETTINGVAL]} )"]}
	/call AddToRotation PAL_Burn_MODETLP_Rotation  "${Righteousstrike}"            Disc    ${Parse[0,"( ${Righteousstrike.NotEqual[NULL]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation PAL_Burn_MODETLP_Rotation  "${Healproc}"                   Spell   ${Parse[0,"( ${PCSpellReady[Healproc]} )"]}

/return

Sub PAL_ModeConfigMODEOAMUK
    |- Only for 13 gem slots
    /if (${Me.NumGems} < 13) {
        /echo MODE OAMUK ONLY WORKS WITH 13 GEMS. PLEASE CHANGE MODES OR EXPERIENCE BAD BEHAVIOR.
    }
    /varset IsTanking TRUE
    |/varset IsHealing TRUE
|**
    Gem1=Protest for Honor
    Gem2=Valiant Diversion
    Gem3=Crush of Restless Ice
    Gem4=Crush of the Grotto
    Gem5=Brilliant Exculpation
    Gem6=Dissident Force
    Gem7=Remonstrate
    Gem8=Stormwall Stance
    Gem9=Harmonious Blessing
    Gem10=Protective Consecration
    Gem11=Wave of Propitiation
    Gem12=Aurora of Wakening
    Gem13=Preservation of the Grotto
**|
    /varset Spell1 ${Challengetaunt}
    /varset Spell2 ${Healtaunt}
    /varset Spell3 ${CrushTimer6}
    /varset Spell4 ${CrushTimer5}
    /varset Spell5 ${HealNuke}
    /varset Spell6 ${Dicho}
    /varset Spell7 ${Lowaggronuke}
    /varset Spell8 ${TempHP}
    /varset Spell9 ${Preservation}
    /varset Spell10 ${Healward}
    /varset Spell11 ${WaveHeal}
    /varset Spell12 ${TotLightHeal}
    /varset Spell13 Null

    /call Ordered_Rotation_Clear PAL_Downtime_MODEOAMUK_Rotation
    /call Ordered_Rotation_Clear PAL_Burn_MODEOAMUK_Rotation
    /call Ordered_Rotation_Clear PAL_DPS_MODEOAMUK_Rotation

    |- Self Buffs
    /call PAL_DefaultSelfBuffRotationConfig PAL_Downtime_MODEOAMUK_Rotation
    |- Group Buffs
    /call PAL_DefaultBuffGroupConfig
    |- Heals
    |- Setup heals
    /call Heal_AddHealPoint 	${MainHealPoint[SETTINGVAL]}
    /call Heal_AddSpell 	 	${MainHealPoint[SETTINGVAL]}   "${WaveHeal}"       ${Parse[0, "( ${SpawnCount[npc radius 30 playerstate 4 targetable]} == 0 )" ]}
    
	| - Burn AA Rotation
	| - Based on personal testing for Maximum DPS. 
	/call AddToRotation PAL_Burn_MODEOAMUK_Rotation  "Valorous Rage" AA TRUE
	/call AddToRotation PAL_Burn_MODEOAMUK_Rotation  "Inquisitor's Judgment" AA TRUE
	/call AddToRotation PAL_Burn_MODEOAMUK_Rotation  "Thunder of Karana" AA ${Parse[0,"( ${DoNuke[SETTINGVAL]} )"]}
	/call AddToRotation PAL_Burn_MODEOAMUK_Rotation  "Group Armor of The Inquisitor" AA TRUE
	/call AddToRotation PAL_Burn_MODEOAMUK_Rotation  "${Undeadburn}" Disc ${Parse[0,"( ${Undeadburn.NotEqual[NULL]} && !${Me.ActiveDisc.ID} && !${IsTanking} )"]}
	/call AddToRotation PAL_Burn_MODEOAMUK_Rotation  "${Righteousstrike}" Disc  ${Parse[0,"( ${Righteousstrike.NotEqual[NULL]} && !${Me.ActiveDisc.ID} )"]}
	| - Tank Mode Rotations
|${Math.Calc[${DoBandolier[2]} && ${Me.Bandolier[2HS].Active} && ${Bool[${Me.Bandolier[Shield].Index}]} && ( ${Me.XTarget}>=${BurnMobCount[2]} || ${Target.Named}]}
|${Math.Calc[${DoBandolier[2]} && ${Me.Bandolier[Shield].Active} && ${Bool[${Me.Bandolier[2HS].Index}]} && ${Me.XTarget}<${BurnMobCount[2]} && !${Target.Named}]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "/bandolier activate Shield"    Command ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && ${Me.Bandolier[2HS].Active} && ( ${Me.XTarget}>=${BurnMobCount[SETTINGVAL]} || ${Target.Named} )  )"]}
    |&& ${Bool[${Me.Bandolier[Shield].Index}]} && ( ${Me.XTarget}>=${BurnMobCount[SETTINGVAL]} || ${Target.Named} ) 
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "/bandolier activate 2HS"       Command ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && ${Me.Bandolier[Shield].Active} && ${Me.XTarget}<${BurnMobCount[SETTINGVAL]} && !${Target.Named} )"]}
    | && ${Bool[${Me.Bandolier[2HS].Index}]} && ${Me.XTarget}<${BurnMobCount[SETTINGVAL]} && !${Target.Named} 
	/call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Shield Flash"                  AA    ${Parse[0,"( ${Me.PctHPs} <= ${Flashhp[SETTINGVAL]} )"]}
	/call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${Mantle}"                     Disc ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Mantle}]} && !${Me.ActiveDisc.ID} && ${IsTanking} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${Holyguard}"                  Disc ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Holyguard}]} && !${Me.ActiveDisc.ID} && ${IsTanking} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${Armordisc}"                  Disc ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Armordisc}]} && !${Me.ActiveDisc.ID} && ${IsTanking} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${Pentientarmor}"              Disc ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]} > 2 || ${Target.Named} ) && ${Me.CombatAbilityReady[${Pentientarmor}]} && !${Me.ActiveDisc.ID} && ${IsTanking} )"]}
	/call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Silver-Scribed Plate Breastplate"  ITEM ${Parse[0,"( ${FindItemCount[Silver-Scribed Plate Breastplate]} && ${Me.ItemReady[=Silver-Scribed Plate Breastplate]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Armor of the Inquisitor"       AA ${Parse[0,"( ${RG_AAReady[Armor of the Inquisitor]} && !${Me.Song[Group Armor of the Inquisitor].ID} && !${Me.Song[Armor of the Inquisitor].ID} && !${Me.Buff[Spire of Chivalry].ID} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Group Armor of the Inquisitor" AA ${Parse[0,"( ${RG_AAReady[Group Armor of the Inquisitor]} && !${Me.Song[Group Armor of the Inquisitor].ID} && !${Me.Song[Armor of the Inquisitor].ID} && !${Me.Buff[Spire of Chivalry].ID} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Spire of Chivalry"             AA ${Parse[0,"( ${RG_AAReady[Spire of Chivalry]} && !${Me.Song[Group Armor of the Inquisitor].ID} && !${Me.Song[Armor of the Inquisitor].ID} && !${Me.Buff[Spire of Chivalry].ID} )"]}
    |/call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Nightbane, Sword of the Valiant"     ITEM ${Parse[0,"( ${Me.Buff[Spire of Chivalry].ID} && ${FindItemCount[Nightbane, Sword of the Valiant]} && ${Me.ItemReady[=Nightbane, Sword of the Valiant]} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${ChestItemName[SETTINGVAL]}"  Item ${Parse[1,"( ${Spell[${FindItem[${ChestItemName[SETTINGVAL]}].Spell}].Stacks} && (!${FindItem[${ChestItemName[SETTINGVAL]}].TimerReady}) && ${DoChestClick[SETTINGVAL]} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${meleemit}"                   Disc TRUE
    /call AddToRotation	PAL_DPS_MODEOAMUK_Rotation   "${TotLightHeal}"               Spell ${Parse[0,"( ${Me.TargetOfTarget.PctHPs} < ${MainHealPoint[SETTINGVAL]} )"]}
    |/call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${Aurora}"                     Spell  ${Parse[0,"( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]} )"]} 
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${WaveHeal}"                   Spell ${Parse[0, "( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]} )" ]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Lay on Hands"                  AA   ${Parse[0,"( ${Me.TargetOfTarget.PctHPs} < ${LayHandsPct[SETTINGVAL]} )"]}
	/call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Gift of Life"                  AA  ${Parse[0,"( ${RG_AAReady[Gift of Life]} && ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]} )"]}
	/call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Hand of Piety"                 AA ${Parse[0,"( ${RG_AAReady[Hand of Piety]} && ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Hallowed Lodestar"             AA  ${Parse[0,"( ${XAssist.XTFullHaterCount}>2 && ${Me.XTAggroCount} > 0 && ${RG_AAReady[Hallowed Lodestar]}  )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Beacon of the Righteous"       AA  ${Parse[0,"( ${XAssist.XTFullHaterCount}>2 && ${Me.XTAggroCount} > 0 && ${RG_AAReady[Beacon of the Righteous]}  )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Heroic Leap"                   AA  ${Parse[0,"( ${XAssist.XTFullHaterCount}>2 && ${Me.XTAggroCount} > 0 && ${RG_AAReady[Heroic Leap]} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Taunt"                         Ability  ${Parse[0,"( ${Me.AbilityReady[Taunt]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Force of Disruption"           AA  ${Parse[0,"( ${Me.AltAbility[Force of Disruption].Rank} >= 7 && ${Target.Distance} < 30 )"]}
	/call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Ageless Enmity"                AA   ${Parse[0,"( ${RG_AAReady[Ageless Enmity]} && ${Me.TargetOfTarget.ID}!=${Me.ID})"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${Affirmation}"          Disc   ${Parse[0,"( ${Me.CombatAbilityReady[${Affirmation}]} && ${Me.TargetOfTarget.ID}!=${Me.ID})"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${HealNuke}"                   Spell  TRUE
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${Healward}"                   Spell  ${Parse[0,"( ${Me.CombatAbilityReady[${Healward}]} && !${Me.Song[Protective Consecration Guard].ID} )"]}  
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${Challengetaunt}"             Spell  ${Parse[0,"( !${Target.Buff[${Challengetaunt}].ID} )"]} 
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${CrushTimer5}"                  Spell  ${Parse[0,"( ${Me.SecondaryPctAggro}>60 )"]}  
	/call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${CrushTimer6}"                Spell  ${Parse[0,"( ${Me.SecondaryPctAggro}>60 )"]}  
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${HealNuke}"                   Spell  TRUE
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${Lowaggronuke}"               Spell  ${Parse[0,"( ${Me.TargetOfTarget.PctHPs} < ${MainHealPoint[SETTINGVAL]} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${Healtaunt}"                  Spell  TRUE 
	/call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "${Dicho}"                      Spell	TRUE     
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Darkened Deepwater Bracer"     ITEM ${Parse[0,"( ${FindItemCount[Darkened Deepwater Bracer]} && ${Me.ItemReady[=Darkened Deepwater Bracer]} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Darkened Deepwater Vambraces"  ITEM ${Parse[0,"( ${FindItemCount[Darkened Deepwater Vambraces]} && ${Me.ItemReady[=Darkened Deepwater Vambraces]} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Vanquish The Fallen"           AA ${Parse[0,"( ${Target.Body.Name.Equal[undead]} )"]}
    /call AddToRotation PAL_DPS_MODEOAMUK_Rotation   "Disruptive Persecution"        AA ${Parse[0,"( (${Me.AltAbility[Disruptive Persecution].Rank}>=3 && !${Me.Buff[Knight's yaulp].ID}) )"]}
     
/return

|- Self buff rotation
Sub PAL_DefaultSelfBuffRotationConfig(string rotation_name)
    
    | Aura
    /call AddToRotation "${rotation_name}" "${aurabuff1}" "Spell" ${Parse[0,"( !${Spell[${Me.Aura[1]}].ID} && ${Me.Spell[${Spell[${aurabuff1}].RankName}].ID} && ${Me.PctEndurance}>10 )"]}
    
    | AA or Individual Self Buffs
    | Needs to be changed to do AA if Rank 1 but cast FuryProc separete (not part of AA)
    | Rank 2+ all 4 are covered under AA
    /if (${Spell[${FuryProc}].Level}<=${Spell[${Me.AltAbility[Divine Protector's Unity].Spell.Trigger.BaseName}].Level} ) {
        /call AddToRotation "${rotation_name}" "Divine Protector's Unity" AA ${Parse[0,"( !${Me.Buff[${Me.AltAbility[Divine Protector's Unity].Spell.Trigger[1].BaseName}].ID} )"]}
    } else { 
        /call AddToRotation "${rotation_name}" "${ArmorSelfBuff}"     Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation "${rotation_name}" "${FuryProc}" Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation "${rotation_name}" "${Remorse}"        Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation "${rotation_name}" "${Piety}"          Spell ${Parse[0,"( SELFBUFFCHECK )"]}
    }
    
    | Preservation
    /call AddToRotation "${rotation_name}" "${Preservation}"       Spell   ${Parse[0,"( ${IsTanking} && SELFBUFFCHECK )"]}
    
	/call AddToRotation "${rotation_name}" "${TempHP}"          Spell   ${Parse[0,"( ${IsTanking} && SELFBUFFCHECK )"]}
    /call AddToRotation "${rotation_name}" "${Incoming}"        Spell   ${Parse[0,"( ${IsTanking} && SELFBUFFCHECK )"]}

    /call AddToRotation "${rotation_name}" "/autoinventory" "Command"   ${Parse[0,"( ${Cursor.ID} && ${Cursor.ID}==121336 )"]}
	/call AddToRotation "${rotation_name}" "Huntsman's Ethereal Quiver" "Item" ${Parse[0,"( ${FindItemCount[Huntsman's Ethereal Quiver]} && ${FindItemCount[Ethereal Arrow]}<1 && ${SummonArrows[SETTINGVAL]}  )"]}
    
    | Mount - If Enabled
    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
/return

Sub PAL_DefaultHealRotationConfig
    /call Heal_Clear

     |- Setup heals
    /call Heal_AddHealPoint 	${MainHealPoint[SETTINGVAL]}

    /call Heal_AddSpell 	 	${MainHealPoint[SETTINGVAL]}   "${WaveHeal}"       ${Parse[0, "( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
    /call Heal_AddSpell 	 	${MainHealPoint[SETTINGVAL]}   "${WaveHeal2}"      ${Parse[0, "( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
    /call Heal_AddSpell 	 	${MainHealPoint[SETTINGVAL]}   "${Aurora}"         ${Parse[0, "( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
   	/call Heal_AddAA            ${MainHealPoint[SETTINGVAL]}   "Gift of Life"      ${Parse[0,"( ( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]} ) && ${RG_AAReady[Gift of Life]} )"]}
	/call Heal_AddAA            ${MainHealPoint[SETTINGVAL]}   "Hand of Piety"     ${Parse[0,"( ( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]} ) && ${RG_AAReady[Hand of Piety]} )"]}
    /call Heal_AddAA            ${MainHealPoint[SETTINGVAL]}   "Lay on Hands"      ${Parse[0,"( ${PCAAReady[Lay on Hands]} && ( ${Target.PctHPs} < ${LayHandsPct[SETTINGVAL]} ) )"]}

/return

Sub PAL_DefaultBuffGroupConfig
    |- Setup our group buffs that will need Dannet
    |- We will have 6 buffs for the group
    /call BuffGroup_Init 3
    /call BuffGroup_Set 1 "${Brells}" "ALL" ${Parse[0, "( ${DoBrells[SETTINGVAL]} )"]}
    /call BuffGroup_Set 2 "${Aego}" "ALL" ${Parse[0, "( !${DoDruid[SETTINGVAL]} )"]}
    /call BuffGroup_Set 3 "${Symbol}" "ALL" ${Parse[0, "( ${DoDruid[SETTINGVAL]} )"]}
/return

Sub PAL_Heal_Routine
|- Do a rez check if we're out of combat
    /if (${RezTimer} == 0) {
        /if (${SpawnCount[REZSEARCHGROUP]}) {
            /call PAL_DoRez ${NearestSpawn[REZSEARCHGROUP].ID}
        }
        /if (${SpawnCount[REZSEARCHME]}) {
            /call PAL_DoRez ${NearestSpawn[REZSEARCHME].ID}
        }
        /if (${AssistOutside[SETTINGVAL]}) {
            /call Heal_OOGCheckAndRez
        }
    }
    /call HealNow ${WorstHurtGroup[${HealPoint_MaxPoint}]}
    /if (${AssistOutside[SETTINGVAL]}) {
        /call HealNow ${WorstHurtXT[${HealPoint_MaxPoint}]}
        |- In case we pissed someone off
        /if (${Me.PctHPs} <= ${HealPoint_MaxPoint} ) {
            /call HealNow ${Me.ID}
        }
    }
/return ${Macro.Return}

Sub PAL_Combat_Routine
    /if ( DODPS ) {
        /if ( BURNCHECK ) {
            /call Ordered_Rotation_Follow PAL_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        }
        /call Ordered_Rotation_Follow PAL_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }
/return FALSE

Sub PAL_Downtime_Routine
    |- Call Self buffs
    /call FollowRotation  PAL_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}
/return FALSE

|---------------------------------------------------------------------------
|- SUB: DoRez
|---------------------------------------------------------------------------- 
Sub PAL_DoRez(int corpse_id)
    /if (${Me.CombatState.Equal[COMBAT]}) {
        | We are in combat.  Only Rez if AA available
        /if ( ${UseBattleRez[SETTINGVAL]} && ${RG_AAReady[Gift of Resurrection]}) {
            | Target corpse and get it near
            /call SetTarget ${corpse_id}
            /if (${Target.Distance}>25) /corpse

            | Rez with AA
            /call AANow ${Me.AltAbility[Gift Of Resurrection].ID} ${corpse_id}
            
            /return ${Macro.Return}
        }
    } else {
        | We are not in combat
        | Prefer Rez AA if available
        /if (${RG_AAReady[Gift of Resurrection]}) {
            | Target corpse and get it near
            /call SetTarget ${corpse_id}
            /if (${Target.Distance}>25) /corpse

            | Rez with AA
            /call AANow ${Me.AltAbility[Gift Of Resurrection].ID} ${corpse_id}
            
        | Use spell if Rez AA is not available
        } else {
            /if (${PCSpellReady[Resurrection]} && !${RG_CanUseAA[Gift of Resurrection]}) {
            
            | Target corpse and get it near
            /call SetTarget ${corpse_id}
            /if (${Target.Distance}>25) /corpse

            | Rez with Spell
            /call SpellNow "Resurrection" ${corpse_id}
            
            }
        }
        /return ${Macro.Return}
    }
/return FALSE

Sub FacePull
	/call AbilityNow "Taunt" ${autotargetid}
/return

Sub PAL_PullSetup
    /if  (${Challengetaunt.NotEqual[NULL]}&&${Me.Gem[${Challengetaunt}]}) {
		/call Pull_SetAbility "${Challengetaunt}" Spell 
	} else /if (${Me.Inventory[ranged].Type.Equal[Archery]} && ${Me.Inventory[ammo].Stack} > 50) {
        /call Pull_SetAbility "pullrange" "Special"
    } else {
        |- Should become the pulling of last resort
        /call Pull_SetAbility "Taunt" "Ability"
	}
/return