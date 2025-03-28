|** RGbrdutil.inc

    Version 2.0: Laurion's Song and aemez update, 20231231postleaf
    Update notes:
        added LS songs +
        corrected usage of dps aura (downtime vs combat routine)
        Enabled option to use regen aura
        Enabled option to disable amplification and use 2nd insult song instead
        Added option to toggle push songs (some insult songs currently)
        Modified selection of insult songs slightly. Should help with FTP bards. Future update to add synergy checks back in
        Rearranged gem loadouts to improve support of lower level and FTP bards
        Mez configuration updates, 3 mez modes available now (see usage notes below)

        Mez Notes:
        DoDpsMez is now a toggle with 3 states
            0: default state - uses full features of rgmez
            1: dps mez mode - simple mode that will only mez during combat if there are enough xtargets
            2: no mez mode - this will not use any mez features
          The robust mez mode will probably function best for crowd control because...
                ...it does not need to wait until the autoassistat setting
                ...it uses the features of rgmez which track the mez target list, track immune list, scan for targets, etc
            robust mez mode will probably have lower dps because of the mez scanning functions
          The simple mez mode will probably have higher dps due to not needing to scan for targets and not stopping melee
          The no mez mode will max dps (and be more useful for raid type scenarios) because it will skip all mez functions

    Version 1.2
    Updated: Terror of Luclin launch Dec 7 2021
    Updated 7/16/2023 by noone    
    Update notes:
        Commented out the bard mez songs with push mechanic
        Added Spider Bite logic to downtime routine
        Added 4 dots to the dps rotation, My ideal rotation is 4 dots, insult ,3 buff songs
            mileage may vary as this is just my preference. 
        Changed default ini configurations, and added a toggle for using spider bite poison
            The old defaults required me to make several ini changes.
        Removed Insult2 and corrected the level list of insult. Set insult to pull 2 insults like the dots do
        Completely rewrote the method of choosing the insults to avoid having to make changes to core includes
        Modified frenzied kick so it only fires when we have amplification active since it buffs it
        Added kick ability since to dps rotation since selo's kick is now passive dmg to kick ability

        

        TODO List
            Add the rest of the battle / downtime clickies to the item rotation
                Anguish Chest plate (buff stacks with all the other buffs)
                Kelin's Seven stringed lute (ONLY USE ON NAMED)
                Fermata of Preservation

            Future plans, determine if we are in necro grp, mage/wiz grp, melee dps grp, or Tank grp... 
                This is purely so I can not have to set my modes manually across all of my bards / groups
            Future plan - look over the mez routine, and why single target is not working as I expect it to



**|



#define MODEMELEE 0
|#define MODECC 1
|#define MODETLP 2


#define BUFFSONG "( ${Me.Gem[${mi.Key}]} && (${Float[${Me.Song[${mi.Key}].Duration.TotalSeconds}]} <= ${Math.Calc[${Spell[${Me.Song[${mi.Key}].Name}].MyCastTime.Seconds} + 6]}) )"
#define BUFFBRDSPELL "( ${Me.Gem[${mi.Key}]} && (${Float[${Me.Buff[${mi.Key}].Duration.TotalSeconds}]} <= ${Math.Calc[${Spell[${mi.Key}].MyCastTime.Seconds} + 6]}) )"

#define DEBUFFSONG "( ${Me.Gem[${mi.Key}]} && !${Target.Buff[${mi.Key}].ID} )"
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub BRD_Setup
    |- Bard setting list
    /declare RGList_BRD list outer
    | Note: TO DO - move the insult song stuff to the other setup sub BRD_SetupSkills with other songs setups
    /declare insultsong_timer3 string outer NULL
    /declare insultsong_timer6 string outer NULL
    
    
    

    |- Call to set up twist specific configuration and variables.
    /call InitRGTwist

    |- Rotations
	/call Ordered_Rotation_New BRD_DPS_MODEMELEE_Rotation
	/call Ordered_Rotation_New BRD_Downtime_MODEMELEE_Rotation
    /call Ordered_Rotation_New BRD_Burn_MODEMELEE_Rotation
    /call Ordered_Rotation_New BRD_Debuff_MODEMELEE_Rotation

	/call Ordered_Rotation_New BRD_DPS_MODECC_Rotation
	/call Ordered_Rotation_New BRD_Downtime_MODECC_Rotation
    /call Ordered_Rotation_New BRD_Burn_MODECC_Rotation
    /call Ordered_Rotation_New BRD_Debuff_MODECC_Rotation

    /call Ordered_Rotation_New BRD_DPS_MODETLP_Rotation
	/call Ordered_Rotation_New BRD_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New BRD_Burn_MODETLP_Rotation
    /call Ordered_Rotation_New BRD_Debuff_MODETLP_Rotation

|- Items
    /call ItemSet_New Epic

|- Spells
    /call AbilitySet_New  BardRunBuff
    /call AbilitySet_New  MainAriaSong
    /call AbilitySet_New  SufferingSong
    /call AbilitySet_New  SprySonataSong
    /call AbilitySet_New  CrescendoSong
    /call AbilitySet_New  ArcaneSong


    

    /call AbilitySet_New  DichoSong    
    /call AbilitySet_New  BardDPSAura AURA
    /declare BardDPSAura_name string outer
    /call AbilitySet_New  BardRegenAura AURA
    /declare BardRegenAura_name string outer
    /call AbilitySet_New  PulseRegenSong
    /call AbilitySet_New  ChorusRegenSong
    /call AbilitySet_New  WarMarchSong
    /call AbilitySet_New  CasterAriaSong
    /call AbilitySet_New  SlowSong
    /call AbilitySet_New  AESlowSong
    /call AbilitySet_New  AccelerandoSong
    /call AbilitySet_New  SpitefulSong
    /call AbilitySet_New  RecklessSong
    /call AbilitySet_New  SelfRune1
    /call AbilitySet_New  StripBuffSpell
    /call AbilitySet_New  FateSong
    /call AbilitySet_New  PsalmSong
    /call AbilitySet_New  DotSong
    /call AbilitySet_New  CureSpell
    /call AbilitySet_New  AllianceSong
    /call AbilitySet_New  CharmSong
    /call AbilitySet_New  ReflexStrike
    /call AbilitySet_New  ChordsAE
    /call AbilitySet_New  LowAriaSong
    /call AbilitySet_New  AmpSong
    /call AbilitySet_New  DispelSong
    /call AbilitySet_New  ResistSong
    
    /call AbilitySet_New  MezSpell
    /call AbilitySet_New  MezAESpell
    /declare MezAEAA string outer NULL

|- Misc Variables
	/declare CurrentMelody			string outer NULL
	/declare IniMelody				string outer NULL
	/declare TuneStuckActive		int outer 0
	/declare PlaySongs				int outer 0
	/declare DoBurn					int outer 0
	/declare DoAASelo 			bool		outer		TRUE
       
|-Config Options
	/call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] "NOTE: Only 0 exists currently - Set 0 = Level 85 or Higher AE Mez Only!, 1 = level 85 or Higher CC Melee Mode 2= TLP Below level 85"
    /call RGLoadSetting BRD DoSlow 0 Combat "Set 0/1 to use Bard slow."
    /call RGLoadSetting BRD UseRegenAura 0 Options "Set 0 to use DPS Aura, 1 to use Regen aura." 0 "BRD_RemoveAura"
    /call RGLoadSetting BRD UseAASelo 1 Options "Set 0/1 to use AA Selo's Sonata"
    /call RGLoadSetting BRD DoRunSpeed 1 Options "set 0/1 to use the RunSpeed song buff."
    /call RGLoadSetting BRD UseQuicktime 1 Options "Set 0/1 to toggle the use of the Quicktime spell. Note: Kepping this on can trigger the EQ Client Stuck Gems bug. Defaults to: 1"
    /call RGLoadSetting BRD ReflexManaPct 80 Options "Set Minimum mana PCT to use ReflexStrike"
    /call RGLoadSetting BRD DoDpsMez 1 Options "Set 0/1/2 - 0: robust mez function (keeps mez list, announces actions, less dps), 1: simple mez (no list checks, better dps but still will mez), 2: dps only mode (no mez, raid mode!)"
    /call RGLoadSetting BRD DoIntimidate 0 Combat "Set 0/1 to toggle Intimidate starting at level 26. Used with fear kiting."
    /call RGLoadSetting BRD DoAAPull 1 Combat "Turns off Pulling with AA to allow use of Dispel song to avoid Summonings" 
    /call RGLoadSetting BRD DoAmpSong 1 Options "Turns on using amplifty As a Song in rotation during dps"
    /call RGLoadSetting BRD DoPushSongs 0 Options "Set 0/1 to toggle using insults with push mechanic"
    /call RGLoadSetting BRD AutoDebuffAt 99 Combat "When to Start Debuffs"
	/call RGLoadSetting BRD HPStopDOT 30 Combat "%HP to cut off to stop casting dots."
    /call RGLoadSetting BRD UseSpiderBite 1 Combat "Set 0/1 to use Spider Bite Poisons"

|-Declare spell variables
	/declare Spell1				    string outer NULL
	/declare Spell2				    string outer NULL
	/declare Spell3				    string outer NULL
	/declare Spell4				    string outer NULL
	/declare Spell5				    string outer NULL
	/declare Spell6				    string outer NULL
	/declare Spell7				    string outer NULL
	/declare Spell8				    string outer NULL
	/declare Spell9				    string outer NULL
	/declare Spell10				string outer NULL
	/declare Spell11				string outer NULL
	/declare Spell12				string outer NULL
	/declare Spell13				string outer NULL
    /declare TuneBonus          int outer 6
	/declare spellmisc 			int outer ${Me.NumGems}
	/declare GroupBuffRecast 	int outer 0
	/declare miscspellremem		string outer NULL
	/declare spellrememtimer	timer outer 0
	/declare groupbufftimer		timer outer 0
	/declare ReadyToCast	  	timer outer 0
    |- Me.NumGems will always return your total number of spell gems
    |- this allows us to get rid of all the lines of checking retention aa.
    |/varset spellmisc ${Me.NumGems}

/return 

|----------------------------------------------------------------------------
|- SUB: CheckSpells
|---------------------------------------------------------------------------- 
Sub BRD_SetupSkills

| To Do - add "echo of" song list
| To Do - add "... burning call" song list (fire based long distance nuke)
| To Do - add silence of the line
| To Do - add resonating barrier line


|- Items 
| - Bard Epic
    /call ItemSet_Add "Prismatic Dragon Blade" Epic
    /call ItemSet_Add "Blade of Vesagran" Epic
    /call ItemSet_ChooseOuter Epic Epic

| - Bard PBAE - Used Only for Level 2 Pull Spell.
    /call AbilitySet_Add "Chords of Dissonance" ChordsAE
    /call AbilitySet_ChooseOuter ChordsAE ChordsAE
|- Bard RunSpeed 
   /call AbilitySet_Add "Selo's Accelerato" BardRunBuff
| * - Song of travel has been removed due to causing Bugs with Invis and rotation. - 
|    /call AbilitySet_Add "Selo's Song of Travel" BardRunBuff
    /call AbilitySet_Add "Selo's Accelerating Chorus" BardRunBuff
    /call AbilitySet_Add "Selo's Accelerando" BardRunBuff
    /call AbilitySet_ChooseOuter BardRunBuff BardRunBuff
|- Bard ReflexStrike - Restores mana to group
    /call AbilitySet_Add "Reflexive Retort" ReflexStrike
    /call AbilitySet_Add "Reflexive Rejoinder" ReflexStrike
    /call AbilitySet_Add "Reflexive Rebuttal" ReflexStrike
    /call AbilitySet_ChooseOuter ReflexStrike ReflexStrike
|- BardDPSAura - Level Ranges 55 - 125 - up to LS
    /call AbilitySet_AddAura "Aura of Tenisbre"        "Aura of Tenisbre" BardDPSAura
    /call AbilitySet_AddAura "Aura of Pli Xin Liako"   "Aura of Pli Xin Liako" BardDPSAura
    /call AbilitySet_AddAura "Aura of Margidor"        "Aura of Margidor"      BardDPSAura   
    /call AbilitySet_AddAura "Aura of Begalru"         "Aura of Begalru"       BardDPSAura
    /call AbilitySet_AddAura "Aura of Maetanrus"       "Aura of Maetanrus"     BardDPSAura 
    /call AbilitySet_AddAura "Aura of Va'Ker"          "Aura of Va'Ker"        BardDPSAura
    /call AbilitySet_AddAura "Aura of the Orator"      "Aura of the Orator"    BardDPSAura
    /call AbilitySet_AddAura "Aura of the Composer"    "Aura of the Composer"  BardDPSAura
    /call AbilitySet_AddAura "Aura of the Poet"        "Aura of the Poet"      BardDPSAura    
    /call AbilitySet_AddAura "Aura of the Artist"      "Aura of the Artist"    BardDPSAura
    /call AbilitySet_AddAura "Aura of the Muse"        "Aura of the Muse"      BardDPSAura
    /call AbilitySet_AddAura "Aura of Insight"         "Aura of Insight"       BardDPSAura     
    /call AbilitySet_ChooseOuter BardDPSAura BardDPSAura
    /varset BardDPSAura_name ${GetAuraName[${BardDPSAura},BardDPSAura]}

|- Amplify Song
    /call AbilitySet_Add "Amplification" AmpSong
    /call AbilitySet_ChooseOuter AmpSong AmpSong

|- BardRegenAura - Level Ranges 82 - 122 - up to LS
    /call AbilitySet_AddAura "Aura of Shalowain"     "Aura of Shalowain" BardRegenAura
    /call AbilitySet_AddAura "Aura of Shei Vinitras" "Aura of Shei Vinitras" BardRegenAura
    /call AbilitySet_AddAura "Aura of Vhal`Sera"   "Aura of Vhal`Sera"   BardRegenAura
    /call AbilitySet_AddAura "Aura of Xigam"       "Aura of Xigam"       BardRegenAura
    /call AbilitySet_AddAura "Aura of Sionachie"   "Aura of Sionachie"   BardRegenAura
    /call AbilitySet_AddAura "Aura of Salarra"     "Aura of Salarra"     BardRegenAura    
    /call AbilitySet_AddAura "Aura of Lunanyn"     "Aura of Lunanyn"     BardRegenAura
    /call AbilitySet_AddAura "Aura of Renewal"     "Aura of Renewal"     BardRegenAura
    /call AbilitySet_AddAura "Aura of Rodcet"      "Aura of Rodcet"      BardRegenAura     
    /call AbilitySet_ChooseOuter BardRegenAura BardRegenAura
    /varset BardRegenAura_name ${GetAuraName[${BardRegenAura},BardRegenAura]}

| - Bard Alliance - up to LS
    /call AbilitySet_Add "Conjunction of Sticks and Stones" AllianceSong
    /call AbilitySet_Add "Alliance of Sticks and Stones" AllianceSong
    /call AbilitySet_Add "Covenant of Sticks and Stones" AllianceSong
    /call AbilitySet_Add "Coalition of Sticks and Stones" AllianceSong
    /call AbilitySet_ChooseOuter AllianceSong AllianceSong  

| - Bard Charm Song - up to 124
    /call AbilitySet_Add "Voice of Suja" CharmSong
    /call AbilitySet_Add "Omiyad's Demand" CharmSong
    /call AbilitySet_Add "Voice of the Diabo" CharmSong
    /call AbilitySet_Add "Silisia's Demand" CharmSong
    /call AbilitySet_Add "Dawnbreeze's Demand" CharmSong
    /call AbilitySet_Add "Desirae's Demand" CharmSong
    /call AbilitySet_ChooseOuter CharmSong CharmSong      

|- Low Level Aria Song - before Combination of Effects Under Level 68
    /call AbilitySet_Add "Battlecry of the Vah Shir" LowAriaSong
    /call AbilitySet_Add "Warsong of the Vah Shir" LowAriaSong
    /call AbilitySet_ChooseOuter LowAriaSong LowAriaSong

| - Resists Song - Note: This list is ascending
    /call AbilitySet_Add "Psalm of Cooling" ResistSong
    /call AbilitySet_Add "Psalm of Purity" ResistSong
    /call AbilitySet_Add "Psalm of Warmth" ResistSong
    /call AbilitySet_Add "Psalm of Vitality" ResistSong
    /call AbilitySet_Add "Psalm of Veeshan" ResistSong
    /call AbilitySet_Add "Psalm of the Forsaken" ResistSong
    /call AbilitySet_Add "Second Psalm of Veeshan" ResistSong
    /call AbilitySet_Add "Psalm of the Restless" ResistSong
    /call AbilitySet_Add "Psalm of the Pious" ResistSong
    /call AbilitySet_Add "Psalm of the Nomad" ResistSong
    /call AbilitySet_ChooseOuter ResistSong ResistSong       

|- MainAriaSong - Level Ranges 45 - 111
|  What differs between PsalmSong and MainAriaSong ???
    /call AbilitySet_Add "Aria of Tenisbre" MainAriaSong
    /call AbilitySet_Add "Aria of Pli Xin Liako" MainAriaSong
    /call AbilitySet_Add "Aria of Margidor" MainAriaSong 
    /call AbilitySet_Add "Aria of Begalru" MainAriaSong
    /call AbilitySet_Add "Aria of Maetanrus" MainAriaSong
    /call AbilitySet_Add "Aria of Va'Ker" MainAriaSong
    /call AbilitySet_Add "Aria of the Orator" MainAriaSong    
    /call AbilitySet_Add "Aria of the Composer" MainAriaSong
    /call AbilitySet_Add "Aria of the Poet" MainAriaSong
    /call AbilitySet_Add "Ancient: Call of Power" MainAriaSong     
    /call AbilitySet_Add "Aria of the Artist" MainAriaSong   
    /call AbilitySet_Add "Yelhun's Mystic Call" MainAriaSong 
    /call AbilitySet_Add "Ancient: Call of Power" MainAriaSong
    /call AbilitySet_Add "Rizlona's Call of Flame" MainAriaSong
    /call AbilitySet_Add "Rizlona's Fire" MainAriaSong  
    /call AbilitySet_Add "Rizlona's Embers" MainAriaSong  
    /call AbilitySet_ChooseOuter MainAriaSong MainAriaSong

|- CasterAriaSong - Level Range 72 - 122
    /call AbilitySet_Add "Flariton's Aria" CasterAriaSong
    /call AbilitySet_Add "Constance's Aria" CasterAriaSong
    /call AbilitySet_Add "Sontalak's Aria" CasterAriaSong 
    /call AbilitySet_Add "Qunard's Aria" CasterAriaSong 
    /call AbilitySet_Add "Nilsara's Aria" CasterAriaSong
    /call AbilitySet_Add "Gosik's Aria" CasterAriaSong
    /call AbilitySet_Add "Daevan's Aria" CasterAriaSong
    /call AbilitySet_Add "Sotor's Aria" CasterAriaSong    
    /call AbilitySet_Add "Talendor's Aria" CasterAriaSong
    /call AbilitySet_Add "Performer's Explosive Aria" CasterAriaSong
    /call AbilitySet_Add "Weshlu's Chillsong Aria" CasterAriaSong     
    /call AbilitySet_ChooseOuter CasterAriaSong CasterAriaSong

|- WarMarchSong Level Range 10 - 124
    /call AbilitySet_Add "War March of Nokk" WarMarchSong
    /call AbilitySet_Add "War March of Centien Xi Va Xakra" WarMarchSong
    /call AbilitySet_Add "War March of Radiwol" WarMarchSong 
    /call AbilitySet_Add "War March of Dekloaz" WarMarchSong 
    /call AbilitySet_Add "War March of Jocelyn" WarMarchSong
    /call AbilitySet_Add "War March of Protan" WarMarchSong
    /call AbilitySet_Add "War March of Illdaera" WarMarchSong
    /call AbilitySet_Add "War March of Dagda" WarMarchSong    
    /call AbilitySet_Add "War March of Brekt" WarMarchSong
    /call AbilitySet_Add "War March of Meldrath" WarMarchSong
    /call AbilitySet_Add "War March of Muram" WarMarchSong  
    /call AbilitySet_Add "War March of the Mastruq" WarMarchSong
    /call AbilitySet_Add "Warsong of Zek" WarMarchSong
    /call AbilitySet_Add "McVaxius' Rousing Rondo" WarMarchSong
    /call AbilitySet_Add "Vilia's Chorus of Celerity" WarMarchSong    
    /call AbilitySet_Add "Verses of Victory" WarMarchSong
    /call AbilitySet_Add "McVaxius' Berserker Crescendo" WarMarchSong
    /call AbilitySet_Add "Vilia's Verses of Celerity" WarMarchSong  
    /call AbilitySet_Add "Anthem de Arms" WarMarchSong    
    /call AbilitySet_ChooseOuter WarMarchSong WarMarchSong
  
|- SufferingSong - Level Range 89 - 124
    /call AbilitySet_Add "Kanghammer's Song of Suffering" SufferingSong
    /call AbilitySet_Add "Shojralen's Song of Suffering" SufferingSong
    /call AbilitySet_Add "Omorden's Song of Suffering" SufferingSong 
    /call AbilitySet_Add "Travenro's Song of Suffering" SufferingSong 
    /call AbilitySet_Add "Fjilnauk's Song of Suffering" SufferingSong
    /call AbilitySet_Add "Kaficus' Song of Suffering" SufferingSong
    /call AbilitySet_Add "Hykast's Song of Suffering" SufferingSong
    /call AbilitySet_Add "Noira's Song of Suffering" SufferingSong    
    /call AbilitySet_ChooseOuter SufferingSong SufferingSong

|- ArcaneSong - Level Range 70 - 124
    /call AbilitySet_Add "Arcane Rhythm" ArcaneSong
    /call AbilitySet_Add "Arcane Harmony" ArcaneSong
    /call AbilitySet_Add "Arcane Symphony" ArcaneSong  
    /call AbilitySet_Add "Arcane Ballad" ArcaneSong
    /call AbilitySet_Add "Arcane Melody" ArcaneSong
    /call AbilitySet_Add "Arcane Hymn" ArcaneSong
    /call AbilitySet_Add "Arcane Address" ArcaneSong    
    /call AbilitySet_Add "Arcane Chorus" ArcaneSong
    /call AbilitySet_Add "Arcane Arietta" ArcaneSong
    /call AbilitySet_Add "Arcane Anthem" ArcaneSong  
    /call AbilitySet_Add "Arcane Aria" ArcaneSong    
    /call AbilitySet_ChooseOuter ArcaneSong ArcaneSong

|- SprySonataSong - Level Range 77 - 123
    /call AbilitySet_Add "Dhakka's Spry Sonata" SprySonataSong
    /call AbilitySet_Add "Xetheg's Spry Sonata" SprySonataSong
    /call AbilitySet_Add "Kellek's Spry Sonata" SprySonataSong
    /call AbilitySet_Add "Kluzen's Spry Sonata" SprySonataSong    
    /call AbilitySet_Add "Doben's Spry Sonata" SprySonataSong
    /call AbilitySet_Add "Terasal's Spry Sonata" SprySonataSong
    /call AbilitySet_Add "Sionachie's Spry Sonata" SprySonataSong  
    /call AbilitySet_Add "Coldcrow's Spry Sonata" SprySonataSong  
|- Adding misc songs below level 77 to fill in first spell gem  
 |**   /call AbilitySet_Add "Psalm of Veeshan" SprySonataSong    
    /call AbilitySet_Add "Nillipus' March of the Wee" SprySonataSong
    /call AbilitySet_Add "Verses of Victory" SprySonataSong
    /call AbilitySet_Add "Psalm of Mystic Shielding" SprySonataSong  
    /call AbilitySet_Add "Psalm of Cooling" SprySonataSong  
    /call AbilitySet_Add "Psalm of Vitality" SprySonataSong 
    /call AbilitySet_Add "Psalm of Warmth" SprySonataSong
    /call AbilitySet_Add "Guardian Rhythms" SprySonataSong    
    /call AbilitySet_Add "Purifying Rhythms" SprySonataSong
    /call AbilitySet_Add "Elemental Rhythms" SprySonataSong  
    /call AbilitySet_Add "Jonthan's Whistling Warsong" SprySonataSong  
    /call AbilitySet_Add "Chant of Battle" SprySonataSong    
**|
    /call AbilitySet_ChooseOuter SprySonataSong SprySonataSong

|- PulseRegenSong - Level Range 77 - 121 ** -- Low level regens are for TLP users thus preferring mana over health.
    /call AbilitySet_Add "Pulse of August" PulseRegenSong
    /call AbilitySet_Add "Pulse of Nikolas" PulseRegenSong
    /call AbilitySet_Add "Pulse of Vhal`Sera" PulseRegenSong
    /call AbilitySet_Add "Pulse of Xigam" PulseRegenSong
    /call AbilitySet_Add "Pulse of Sionachie" PulseRegenSong
    /call AbilitySet_Add "Pulse of Salarra" PulseRegenSong    
    /call AbilitySet_Add "Pulse of Lunanyn" PulseRegenSong
    /call AbilitySet_Add "Pulse of Renewal" PulseRegenSong
    /call AbilitySet_Add "Pulse of Rodcet" PulseRegenSong  
    /call AbilitySet_Add "Cassindra's Chorus of Clarity" PulseRegenSong
    /call AbilitySet_Add "Cassindra's Chant of Clarity" PulseRegenSong
    /call AbilitySet_Add "Rhythm of Restoration" PulseRegenSong    
    /call AbilitySet_ChooseOuter PulseRegenSong PulseRegenSong

|- ChorusRegenSong - Level Range 6 - 123
    /call AbilitySet_Add "Chorus of Shalowain" ChorusRegenSong
    /call AbilitySet_Add "Chorus of Shei Vinitras" ChorusRegenSong
    /call AbilitySet_Add "Chorus of Vhal`Sera" ChorusRegenSong
    /call AbilitySet_Add "Chorus of Xigam" ChorusRegenSong  
    /call AbilitySet_Add "Chorus of Sionachie" ChorusRegenSong 
    /call AbilitySet_Add "Chorus of Salarra" ChorusRegenSong
    /call AbilitySet_Add "Chorus of Lunanyn" ChorusRegenSong
    /call AbilitySet_Add "Chorus of Renewal" ChorusRegenSong
    /call AbilitySet_Add "Chorus of Rodcet" ChorusRegenSong    
    /call AbilitySet_Add "Cantata of Rodcet" ChorusRegenSong
    /call AbilitySet_Add "Chorus of Restoration" ChorusRegenSong
    /call AbilitySet_Add "Cantata of Restoration" ChorusRegenSong  
    /call AbilitySet_Add "Erollisi's Cantata" ChorusRegenSong    
    /call AbilitySet_Add "Chorus of Life" ChorusRegenSong
    /call AbilitySet_Add "Cantata of Life" ChorusRegenSong
    /call AbilitySet_Add "Chorus of Marr" ChorusRegenSong
    /call AbilitySet_Add "Wind of Marr" ChorusRegenSong    
    /call AbilitySet_Add "Chorus of Replenishment" ChorusRegenSong
    /call AbilitySet_Add "Cantata of Replenishment" ChorusRegenSong
    /call AbilitySet_Add "Cantata of Soothing" ChorusRegenSong  
    /call AbilitySet_Add "Hymn of Restoration" ChorusRegenSong    
    /call AbilitySet_ChooseOuter ChorusRegenSong ChorusRegenSong

|- Dispel Song - For pulling to avoid Summons
    /call AbilitySet_Add "Syvelian's Anti-Magic Aria" DispelSong
    /call AbilitySet_Add "Druzzil's Disillusionment" DispelSong
    /call AbilitySet_ChooseOuter DispelSong DispelSong

|- CrescendoSong - Level Range 75 - 124
    /call AbilitySet_Add "Regar's Lively Crescendo" CrescendoSong
    /call AbilitySet_Add "Zelinstein's Lively Crescendo" CrescendoSong
    /call AbilitySet_Add "Zburator's Lively Crescendo" CrescendoSong  
    /call AbilitySet_Add "Jembel's Lively Crescendo" CrescendoSong
    /call AbilitySet_Add "Silisia's Lively Crescendo" CrescendoSong
    /call AbilitySet_Add "Motlak's Lively Crescendo" CrescendoSong
    /call AbilitySet_Add "Kolain's Lively Crescendo" CrescendoSong    
    /call AbilitySet_Add "Lyssa's Lively Crescendo" CrescendoSong
    /call AbilitySet_Add "Gruber's Lively Crescendo" CrescendoSong
    /call AbilitySet_Add "Kaerra's Spirited Crescendo" CrescendoSong  
    /call AbilitySet_Add "Veshma's Lively Crescendo" CrescendoSong    
    /call AbilitySet_ChooseOuter CrescendoSong CrescendoSong

|- Seperated the Insult Songs Since they are on 2 different timers and the new one with them as one would Pick 2 Insult Timer 3 songs by Default.
    | 20231220 - postleaf - new attempt to get insult songs based on timers filter
    | Timer 3 insults, level, synergy focus rank, pushback
        | Eoreg's Insult, 122, 16/15, 1
        | Yelinak's Insult, 115, 16/15/14/13, 0
        | Omorden's Insult, 112, 15/14/13/12, 1
        | Tsaph's Insult, 105, <=12, 0
        | Fjilnauk's Insult, 102, <=11, 1
        | Hykast's Insult, 95, none, 1
        | Venimor's Insult, 85, none, 1 

        | Timer 6 insults, level, synergy focus rank, pushback
        | Nords' Disdain, 118, 16/15, 0
        | Sogran's Insult, 117, 16/15/14, 1
        | Sathir's Insult, 110, 14/13/12/11, 0
        | Travenro's Insult, 107, 13/12/11, 1
        | Kaficus' Insult, 100, <=10, 1
        | Garath's Insult, 97, <=10, 0
        | Lyrin's Insult, 90, none, 1 

    | Note: Created list of all insult songs that share either timer 3 or timer 6
    |         This list will need to be updated for each new expansion (or until a better method is created)
    /varset insultsong_timer3 Eoreg's Insult|Yelinak's Insult|Omorden's Insult|Tsaph's Insult|Fjilnauk's Insult|Hykast's Insult|Venimor's Insult
    /varset insultsong_timer6 Nords' Disdain|Sogran's Insult|Sathir's Insult|Travenro's Insult|Kaficus' Insult|Garath's Insult|Lyrin's Insult
    /call AbilitySet_New InsultSong
    /call AbilitySet_New InsultSong1
    /call AbilitySet_New InsultSong2

    | Select list of songs based on push settings
    | To Do - add selection criteria based on focus Troubadours synergy rank (needed to max DPS but also continue FTP bard support)
    |         - A better method may be to loop through a list and select songs based on flags like push and synergy rank
    /if (${DoPushSongs[SETTINGVAL]}==1) {
        /call AbilitySet_Add "Eoreg's Insult" InsultSong
        /call AbilitySet_Add "Nord's Disdain" InsultSong
        /call AbilitySet_Add "Sogran's Insult" InsultSong
        /call AbilitySet_Add "Yelinak's Insult" InsultSong
        /call AbilitySet_Add "Omorden's Insult" InsultSong 
        /call AbilitySet_Add "Sathir's Insult" InsultSong
        /call AbilitySet_Add "Travenro's Insult" InsultSong  
        /call AbilitySet_Add "Tsaph's Insult" InsultSong
        /call AbilitySet_Add "Fjilnauk's Insult" InsultSong
        /call AbilitySet_Add "Kaficus' Insult" InsultSong
        /call AbilitySet_Add "Garath's Insult" InsultSong
        /call AbilitySet_Add "Hykast's Insult" InsultSong
        /call AbilitySet_Add "Lyrin's Insult" InsultSong
        /call AbilitySet_Add "Venimor's Insult" InsultSong    
    } else {
        /call AbilitySet_Add "Nord's Disdain" InsultSong        
        /call AbilitySet_Add "Yelinak's Insult" InsultSong        
        /call AbilitySet_Add "Sathir's Insult" InsultSong        
        /call AbilitySet_Add "Tsaph's Insult" InsultSong
        /call AbilitySet_Add "Garath's Insult" InsultSong    
    }       
    | Add low level (<66) insult line aka bellows
    /call AbilitySet_Add "Bellow of Chaos" InsultSong
    /call AbilitySet_Add "Brusco's Bombastic Bellow" InsultSong   
    /call AbilitySet_Add "Brusco's Boastful Bellow" InsultSong
    | Choose song from set list and from shared timer lists        
    /call AbilitySet_ChooseOuter InsultSong1 InsultSong "${insultsong_timer6}"
    /call AbilitySet_ChooseOuter InsultSong2 InsultSong "${insultsong_timer3}"

    /echo ------- TIMER 3 song --- ${InsultSong1}
    /echo ------- TIMER 6 song --- ${InsultSong2}




|- DichoSong Level Range - 101 - 106
    /call AbilitySet_Add "Ecliptic Psalm" DichoSong
    /call AbilitySet_Add "Composite Psalm" DichoSong
    /call AbilitySet_Add "Dissident Psalm" DichoSong    
    /call AbilitySet_Add "Dichotomic Psalm" DichoSong
    /call AbilitySet_ChooseOuter DichoSong DichoSong

|- MezSpell - Level Range 15 - 124
    /call AbilitySet_Add "Slumber of Suja" MezSpell
    /call AbilitySet_Add "Lullaby of the Forgotten" MezSpell
    /call AbilitySet_Add "Slumber of the Diabo" MezSpell
    |- /call AbilitySet_Add "Lullaby of Nightfall" MezSpell
    |- /call AbilitySet_Add "Lullaby of Zburator" MezSpell
    /call AbilitySet_Add "Slumber of Zburator" MezSpell
    /call AbilitySet_Add "Slumber of Jembel" MezSpell  
    |- /call AbilitySet_Add "Lullaby of Jembel" MezSpell 
    /call AbilitySet_Add "Slumber of Silisia" MezSpell
    |- /call AbilitySet_Add "Lullaby of Silisia" MezSpell
    /call AbilitySet_Add "Slumber of Motlak" MezSpell
    |- /call AbilitySet_Add "Lullaby of the Forsaken" MezSpell    
    /call AbilitySet_Add "Slumber of Kolain" MezSpell
    |- /call AbilitySet_Add "Lullaby of the Forlorn" MezSpell
    /call AbilitySet_Add "Slumber of Sionachie" MezSpell  
    |- /call AbilitySet_Add "Lullaby of the Lost" MezSpell    
    /call AbilitySet_Add "Slumber of the Mindshear" MezSpell
    /call AbilitySet_Add "Serenity of Oceangreen" MezSpell
    /call AbilitySet_Add "Amber's Last Lullaby" MezSpell
    /call AbilitySet_Add "Queen Eletyl's Screech" MezSpell
    /call AbilitySet_Add "Command of Queen Veneneu" MezSpell
    /call AbilitySet_Add "Aelfric's Last Lullaby" MezSpell    
    /call AbilitySet_Add "Vulka's Lullaby" MezSpell
    /call AbilitySet_Add "Creeping Dreams" MezSpell
    /call AbilitySet_Add "Luvwen's Lullaby" MezSpell  
    /call AbilitySet_Add "Lullaby of Morell" MezSpell    
    /call AbilitySet_Add "Dreams of Terris" MezSpell
    /call AbilitySet_Add "Dreams of Thule" MezSpell  
    /call AbilitySet_Add "Dreams of Ayonae" MezSpell   
    /call AbilitySet_Add "Song of Twilight" MezSpell
    /call AbilitySet_Add "Sionachie's Dreams" MezSpell  
    /call AbilitySet_Add "Crission's Pixie Strike" MezSpell   
    /call AbilitySet_Add "Kelin's Lucid Lullaby" MezSpell 
    /call AbilitySet_ChooseOuter MezSpell MezSpell

|- MezAESpell - Level Range 85 - 125 **
    /call AbilitySet_Add "Wave of Stupor" MezAESpell
    /call AbilitySet_Add "Wave of Nocturn" MezAESpell
    /call AbilitySet_Add "Wave of Sleep" MezAESpell
    /call AbilitySet_Add "Wave of Somnolence" MezAESpell
    /call AbilitySet_Add "Wave of Torpor" MezAESpell    
    /call AbilitySet_Add "Wave of Quietude" MezAESpell
    /call AbilitySet_Add "Wave of the Conductor" MezAESpell
    /call AbilitySet_Add "Wave of Dreams" MezAESpell  
    /call AbilitySet_Add "Wave of Slumber" MezAESpell    
    /call AbilitySet_ChooseOuter MezAESpell MezAESpell

|- SlowSong - We only get 1 single target slow
    /call AbilitySet_Add "Requiem of Time" SlowSong    
    /call AbilitySet_ChooseOuter SlowSong SlowSong

| - Singletarget Assonant Slow Line - To Do: add these

| - Single target Assonant Binding Line - To Do: add these


|- AESlowSong - Level Range 20 - 124 (Single target works better)  
    /call AbilitySet_Add "Zinnia's Melodic Binding" AESlowSong
    /call AbilitySet_Add "Radiwol's Melodic Binding" AESlowSong
    /call AbilitySet_Add "Dekloaz's Melodic Binding" AESlowSong
    /call AbilitySet_Add "Protan's Melodic Binding" AESlowSong  
    /call AbilitySet_Add "Largo's Melodic Binding" AESlowSong    
    /call AbilitySet_ChooseOuter AESlowSong AESlowSong

 |- AccelerandoSong - Level Range 88 - 123 **
    /call AbilitySet_Add "Appeasing Accelerando" AccelerandoSong
    /call AbilitySet_Add "Satisfying Accelerando" AccelerandoSong
    /call AbilitySet_Add "Placating Accelerando" AccelerandoSong
    /call AbilitySet_Add "Atoning Accelerando" AccelerandoSong    
    /call AbilitySet_Add "Allaying Accelerando" AccelerandoSong
    /call AbilitySet_Add "Ameliorating Accelerando" AccelerandoSong
    /call AbilitySet_Add "Assuaging Accelerando" AccelerandoSong  
    /call AbilitySet_Add "Alleviating Accelerando" AccelerandoSong    
    /call AbilitySet_ChooseOuter AccelerandoSong AccelerandoSong

 |- SpitefulSong - Level Range 90 - 125 - LS max
    /call AbilitySet_Add "Tatalros' Spiteful Lyric" SpitefulSong
    /call AbilitySet_Add "Von Deek's Spiteful Lyric" SpitefulSong
    /call AbilitySet_Add "Omorden's Spiteful Lyric" SpitefulSong
    /call AbilitySet_Add "Travenro's Spiteful Lyric" SpitefulSong    
    /call AbilitySet_Add "Fjilnauk's Spiteful Lyric" SpitefulSong
    /call AbilitySet_Add "Kaficus' Spiteful Lyric" SpitefulSong
    /call AbilitySet_Add "Hykast's Spiteful Lyric" SpitefulSong  
    /call AbilitySet_Add "Lyrin's Spiteful Lyric" SpitefulSong    
    /call AbilitySet_ChooseOuter SpitefulSong SpitefulSong

 |- RecklessSong - Level Range 93 - 123 **
    /call AbilitySet_Add "Grayleaf's Reckless Renewal" RecklessSong
    /call AbilitySet_Add "Kai's Reckless Renewal" RecklessSong
    /call AbilitySet_Add "Reivaj's Reckless Renewal" RecklessSong    
    /call AbilitySet_Add "Rigelon's Reckless Renewal" RecklessSong
    /call AbilitySet_Add "Rytan's Reckless Renewal" RecklessSong
    /call AbilitySet_Add "Ruaabri's Reckless Renewal" RecklessSong  
    /call AbilitySet_Add "Ryken's Reckless Renewal" RecklessSong    
    /call AbilitySet_ChooseOuter RecklessSong RecklessSong
    
 |- Fatesong - Level Range 77 - 122 **
    /call AbilitySet_Add "Fatesong of Zoraxmen" FateSong
    /call AbilitySet_Add "Fatesong of Lucca" FateSong
    /call AbilitySet_Add "Fatesong of Radiwol" FateSong
    /call AbilitySet_Add "Fatesong of Dekloaz" FateSong 
    /call AbilitySet_Add "Fatesong of Jocelyn" FateSong
    /call AbilitySet_Add "Fatesong of Protan" FateSong    
    /call AbilitySet_Add "Fatesong of Illdaera" FateSong
    /call AbilitySet_Add "Fatesong of Fergar" FateSong
    /call AbilitySet_Add "Fatesong of the Gelidran" FateSong  
    /call AbilitySet_Add "Garadell's Fatesong" FateSong    
    /call AbilitySet_ChooseOuter FateSong FateSong
    
 |- PsalmSong - Level Range 69 - 112 **
|  What differs between PsalmSong and MainAriaSong ???
    /call AbilitySet_Add "Tatalros' Psalm of Potency" PsalmSong
    /call AbilitySet_Add "Fyrthek Fior's Psalm of Potency" PsalmSong
    /call AbilitySet_Add "Velketor's Psalm of Potency" PsalmSong
    /call AbilitySet_Add "Akett's Psalm of Potency" PsalmSong  
    /call AbilitySet_Add "Horthin's Psalm of Potency" PsalmSong
    /call AbilitySet_Add "Siavonn's Psalm of Potency" PsalmSong 
    /call AbilitySet_Add "Wasinai's Psalm of Potency" PsalmSong
    /call AbilitySet_Add "Lyrin's Psalm of Potency" PsalmSong    
    /call AbilitySet_Add "Druzzil's Psalm of Potency" PsalmSong
    /call AbilitySet_Add "Erradien's Psalm of Potency" PsalmSong
    /call AbilitySet_Add "Performer's Psalm of Pyrotechnics" PsalmSong  
    /call AbilitySet_Add "Ancient: Call of Power" PsalmSong 
    /call AbilitySet_Add "Eriki's Psalm of Power" PsalmSong    
    /call AbilitySet_ChooseOuter PsalmSong    PsalmSong

|- DotSong - Level Range 30 - 125
    /call AbilitySet_Add "Kindleheart's Chant of Flame" DotSong
    /call AbilitySet_Add "Marsin's Chant of Poison" DotSong
    /call AbilitySet_Add "Swarn's Chant of Frost" DotSong
    /call AbilitySet_Add "Goremand's Chant of Disease" DotSong    
    /call AbilitySet_Add "Shak Dathor's Chant of Flame" DotSong
    /call AbilitySet_Add "Cruor's Chant of Poison" DotSong
    /call AbilitySet_Add "Sylra Fris' Chant of Frost" DotSong
    /call AbilitySet_Add "Coagulus' Chant of Disease" DotSong
    /call AbilitySet_Add "Sontalak's Chant of Flame" DotSong
    /call AbilitySet_Add "Malvus's Chant of Poison" DotSong  
    /call AbilitySet_Add "Yelinak's Chant of Frost" DotSong    
    /call AbilitySet_Add "Zlexak's Chant of Disease" DotSong
    /call AbilitySet_Add "Qunard's Chant of Flame" DotSong
    /call AbilitySet_Add "Nexona's Chant of Poison" DotSong
    /call AbilitySet_Add "Ekron's Chant of Frost" DotSong    
    /call AbilitySet_Add "Hoshkar's Chant of Disease" DotSong
    /call AbilitySet_Add "Nilsara's Chant of Flame" DotSong
    /call AbilitySet_Add "Serisaria's Chant of Poison" DotSong  
    /call AbilitySet_Add "Kirchen's Chant of Frost" DotSong
    /call AbilitySet_Add "Horthin's Chant of Disease" DotSong  
    /call AbilitySet_Add "Gosik's Chant of Flame" DotSong 
    /call AbilitySet_Add "Slaunk's Chant of Poison" DotSong
    /call AbilitySet_Add "Edoth's Chant of Frost" DotSong
    /call AbilitySet_Add "Siavonn's Chant of Disease" DotSong
    /call AbilitySet_Add "Daevan's Chant of Flame" DotSong    
    /call AbilitySet_Add "Hiqork's Chant of Poison" DotSong
    /call AbilitySet_Add "Kalbrok's Chant of Frost" DotSong
    /call AbilitySet_Add "Wasinai's Chant of Disease" DotSong  
    /call AbilitySet_Add "Sotor's Chant of Flame" DotSong    
    /call AbilitySet_Add "Spinechiller's Chant of Poison" DotSong
    /call AbilitySet_Add "Fergar's Chant of Frost" DotSong
    /call AbilitySet_Add "Shiverback's Chant of Disease" DotSong
    /call AbilitySet_Add "Talendor's Chant of Flame" DotSong    
    /call AbilitySet_Add "Severilous' Chant of Poison" DotSong
    /call AbilitySet_Add "Gorenaire's Chant of Frost" DotSong
    /call AbilitySet_Add "Trakanon's Chant of Disease" DotSong  
    /call AbilitySet_Add "Tjudawos' Chant of Flame" DotSong   
    /call AbilitySet_Add "Kildrukaun's Chant of Poison" DotSong
    /call AbilitySet_Add "Zeixshi-Kar's Chant of Frost" DotSong  
    /call AbilitySet_Add "Vyskudra's Chant of Disease" DotSong 
    /call AbilitySet_Add "Ancient: Chaos Chant" DotSong 
    /call AbilitySet_Add "Vulka's Chant of Flame" DotSong
    /call AbilitySet_Add "Vulka's Chant of Poison" DotSong
    /call AbilitySet_Add "Vulka's Chant of Frost" DotSong
    /call AbilitySet_Add "Vulka's Chant of Disease" DotSong    
    /call AbilitySet_Add "Ancient: Chaos Chant" DotSong
    /call AbilitySet_Add "Tuyen's Chant of Fire" DotSong
    /call AbilitySet_Add "Tuyen's Chant of Ice" DotSong  
    /call AbilitySet_Add "Tuyen's Chant of Venom" DotSong    
    /call AbilitySet_Add "Tuyen's Chant of the Plague" DotSong
    /call AbilitySet_Add "Angstlich's Assonance" DotSong
    /call AbilitySet_Add "Fufil's Diminishing Dirge" DotSong
    /call AbilitySet_Add "Tuyen's Chant of Poison" DotSong    
    /call AbilitySet_Add "Tuyen's Chant of Frost" DotSong
    /call AbilitySet_Add "Tuyen's Chant of Disease" DotSong
    /call AbilitySet_Add "Tuyen's Chant of Flame" DotSong  
    /call AbilitySet_Add "Fufil's Curtailing Chant" DotSong    
    /call AbilitySet_ChooseOuter Dot1Song DotSong    
    /call AbilitySet_ChooseOuter Dot2Song DotSong "${Dot1Song}"  
    /call AbilitySet_ChooseOuter Dot3Song DotSong "${Dot1Song}|${Dot2Song}"  
    /call AbilitySet_ChooseOuter Dot4Song DotSong "${Dot1Song}|${Dot2Song}|${Dot3Song}"  
  
    /call AbilitySet_Add "Aria of Absolution" CureSpell    
    /call AbilitySet_ChooseOuter CureSpell  CureSpell
/return

|-----------------------------------------------------------------------------
|- SUB - meleeSpellConfig - Configure Spell Gems for base Melee Twist
|-----------------------------------------------------------------------------
Sub BRD_ModeConfigMODEMELEE
    |- Setting IzMezzing to false, because the logic causes problems locking down single pulls
    |- If IsMezzing = TRUE, bard will use AE mez spell. Mezzing toggle is then via DoDpsMez = 0/1
    |    -> This if condition requires a macro restart
    |       -> if the IsMezzing var is true, then the mez announce stuff doesnt work because the MezNow sub isnt used
    |    -> the ae mez song in the dps rotation has a check for dodpsmez and is perhaps a 2nd way to mez
    |       -> Need more investigation to see if these 2 settings are competing with each other. we really only
    |          should have 1 method for mezzing so this code is not so confusing and hard to debug
    |    -> new features: only want to use 1 method of mezzing, so do dps on or off will toggle between rgmez stuff or simple ae mez rotation song
    |   Note: The DoDpsMez setting can be updated by user in real time and the IsMezzing var will be updated appropriatly via the rotation_reset sub
    /if (${DoDpsMez[SETTINGVAL]}==0) {
        /varset IsMezzing TRUE
        /echo DoDpsMez is mode 0, Setting variable IsMezzing to TRUE, robust mez mode
    } else /if (${DoDpsMez[SETTINGVAL]}==1) {
        /varset IsMezzing FALSE
        /echo DoDpsMez is mode 1, Setting variable IsMezzing to FALSE, simple mez mode
    } else /if (${DoDpsMez[SETTINGVAL]}==2) {
        /varset IsMezzing FALSE
        /echo DoDpsMez is mode 2, Setting variable IsMezzing to FALSE, no mez mode
    }

    /call InitMez

    |/echo Mez is Default Combat only in this Mode Singletarget mez is Off. - For a CC/Melee Combo Mode try /rg Classmode 1    
    /if (${DoSlow[SETTINGVAL]}) {
        /if (${SlowSong.Equal[NULL]}) {
            /varset Spell1 ${AESlowSong}
        } else {
            /varset Spell1 ${SlowSong}
        }
    } else {
        /varset Spell1 ${InsultSong1}
    }
    | To Do: need to add another option if the user is too low for amp and has only 1 insult song...
    /if (${DoAmpSong[SETTINGVAL]}) {
        /varset Spell2 ${AmpSong}
    } else {
        /varset Spell2 ${InsultSong2}
    }
    /varset Spell3 ${WarMarchSong}
    /varset Spell4 ${Dot1Song}
    | Note: Setting AE mez to spell 5 to reduce issues with low levels and/or FTP
    /if (${Me.Level} < 85) {
        /varset Spell13 ${ChorusRegenSong}
    } else {                
        | Note: first ae mez song is level 85
        /varset Spell5 ${MezAESpell}
    }
    /if (${Me.Level} <=63) {
        /varset Spell6 ${LowAriaSong}
    } else {
        /varset Spell6 ${MainAriaSong}
    }
    
    /varcalc DoAASelo ${UseAASelo[SETTINGVAL]} && ${RG_CanUseAA[Selo's Sonata]}
    | Note: First dicho song is level 101. Probably need a better loadout for level < 101
    /if (!${DoAASelo}) {
        /varset Spell7 ${BardRunBuff}
    } else {
        /varset Spell7 ${DichoSong}
    }

    | Setup regen song in gem last gem for lower level or FTP bards until mnemonic retention level 4
    | Note: Crescendo song has long (~40s gem refresh after mem, dont put in swap slot)
    /if (${Me.NumGems}<9) {
        /varset Spell8 ${ChorusRegenSong}
    } else {
        /varset Spell8 ${CrescendoSong}
    }    
    /if (${Me.NumGems}<10) {
        /varset Spell9 ${ChorusRegenSong}
    } else {
        /varset Spell9 ${Dot2Song}    
    }
    /if (${Me.NumGems}<11) {
        /varset Spell10 ${ChorusRegenSong}
    } else {
        /varset Spell10 ${Dot3Song}    
    }
    /if (${Me.NumGems}<12) {
        /varset Spell11 ${ChorusRegenSong}
    } else {
        /varset Spell11 ${Dot4Song}    
    }    
    /varset Spell12 ${ChorusRegenSong}            
    | Single target MezSpell in last slot since its not currently supported, may move in the future or create a 'single target' mez class mode option
    /varset Spell13 ${MezSpell}
    
    
    | - This call has to be Above the Songs in all modes - Otherwise it never Gets to the Combat routines.
    | - see mez usage features in DoDpsMode user notes above
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${MezAESpell}"                  Song ${Parse[0,"( (${DoDpsMez[SETTINGVAL]}==1) && (${XAssist.XTFullHaterCount} >= ${MezAECount[SETTINGVAL]}) )"]}

    |-Aggro Drops
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Fading Memories"                AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Hymn of the Last Stand"         AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Shield of Notes"                AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]}
    
    |- Main Tank Dead Stepping in to Keep folks alive.
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Dissonant Chord"                AA ${Parse[0,"( ${SpawnCount[pccorpse ${assistid}]} )"]}
    |/call AddToRotation BRD_DPS_MODEMELEE_Rotation "/call BRD_ReflexStrikeManaCheck"    Command ${Parse[0,"( ${NPCDiscReady[${ReflexStrike}]} )"]}
    | - DPs AAs'a
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Boastful Bellow"                AA ${Parse[0,"( !${Target.Buff[${Me.AltAbility[Boastful Bellow].ID}].} && ${Target.PctHPs}>90 )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Song of Stone"                  AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Lyrical Prankster"              AA ${Parse[0,"( TRUE )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Cacophony"                      AA ${Parse[0,"( ${Target.Named} && DOTSPELLCHECK )"]}  
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Bladed Song"                    AA ${Parse[0,"( TRUE )"]}     
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Fierce Eye"                     AA ${Parse[0,"( !${Me.Buff[Fierce Eye].ID} )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Spire of the Minstrels"         AA ${Parse[0,"( !${Me.Buff[Spire of the Minstrels].ID} )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Quick Time"                     AA ${Parse[0,"( ${UseQuicktime[SETTINGVAL]} )"]}         
    | - Frenzied kicks will be used only when amp song is active or always if user is not using amp song 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Frenzied Kicks"                 AA ${Parse[0,"( ${Me.Song[${AmpSong}].ID} || !${DoAmpSong[SETTINGVAL]})"]}

    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${MountItem[SETTINGVAL]}"       Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "/dismount"                      Command ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    /if (${Me.Level}>=20) {
        /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Intimidation"               Ability ${Parse[0,"( ${DoIntimidate[SETTINGVAL]} )"]}
    }
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Kick"              Ability ${Parse[0,"( TRUE )"]}
    
    |- Items Map
    |- This item map contains all of the "required" clickies for bards based on my research
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${Epic}"                                    Item       ${Parse[0,"( ${Spell[${FindItem[${Epic}].Spell}].Stacks} && (!${FindItem[${Epic}].TimerReady}) )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${FindItem[${Me.Inventory[Chest].Name}]}"   Item       ${Parse[0,"( ${DoChestClick[SETTINGVAL]} && ${Spell[${FindItem[${Me.Inventory[Chest].Name}].Spell}].Stacks} && (!${FindItem[${Me.Inventory[Chest].Name}].TimerReady}) )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Miniature Horn of Unity"                    Item       ${Parse[0,"( ${Spell[${FindItem[Miniature Horn of Unity].Spell}].Stacks} && (!${FindItem[Miniature Horn of Unity].TimerReady}) )"]}   
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Unified Phoenix Feather"                    Item       ${Parse[0,"( ${Spell[${FindItem[Unified Phoenix Feather].Spell}].Stacks} && (!${FindItem[Unified Phoenix Feather].TimerReady}) )"]}   
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Signet of Gannar"                           Item       ${Parse[0,"( ${Spell[${FindItem[Signet of Gannar].Spell}].Stacks} && (!${FindItem[Signet of Gannar].TimerReady}) )"]}   
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Rage of Rolfron"                            Item       ${Parse[0,"( ${Spell[${FindItem[Rage of Rolfron].Spell}].Stacks} && (!${FindItem[Rage of Rolfron].TimerReady}) )"]}   
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Bottled Essence of Vex"                     Item       ${Parse[0,"( ${Spell[${FindItem[Bottled Essence of Vex].Spell}].Stacks} && (!${FindItem[Bottled Essence of Vex].TimerReady}) )"]}   
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Whisper-Wrought Plate Breastplate"          Item       ${Parse[0,"( ${Spell[${FindItem[Whisper-Wrought Plate Breastplate].Spell}].Stacks} && (!${FindItem[Whisper-Wrought Plate Breastplate].TimerReady}) )"]}   
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Possessed Dreadstone Minstrel's Rapier"     Item       ${Parse[0,"( ${Spell[${FindItem[Possessed Dreadstone Minstrel's Rapier].Spell}].Stacks} && (!${FindItem[Possessed Dreadstone Minstrel's Rapier].TimerReady}) )"]}   

    |- Combat Twist    
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${AccelerandoSong}"             Song ${Parse[0,"( BUFFSONG )"]}     
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${RecklessSong}"                Song ${Parse[0,"( BUFFSONG )"]}    
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${SlowSong}"                    Song ${Parse[0,"( DEBUFFSONG && !${Target.Slowed.ID} )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${AESlowSong}"                  Song ${Parse[0,"( DEBUFFSONG )"]}
    |- Correcting the order, so that songs cast in the order I want them to
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${WarMarchSong}"                Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${MainAriaSong}"                Song ${Parse[0,"( BUFFSONG )"]}     
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${Dot1Song}"                    Song ${Parse[0,"( DEBUFFSONG && ${Target.Buff[${Dot1Song}].Duration} < 3 )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${InsultSong1}"                 Song ${Parse[0,"( (${Me.PctMana}>50 && ${Target.PctHPs}>50) )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${InsultSong2}"                 Song ${Parse[0,"( (${Me.PctMana}>50 && ${Target.PctHPs}>50) )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${AmpSong}"                     Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${Dot2Song}"                    Song ${Parse[0,"( DEBUFFSONG && ${Target.Buff[${Dot2Song}].Duration} < 3 )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${Dot3Song}"                    Song ${Parse[0,"( DEBUFFSONG && ${Target.Buff[${Dot3Song}].Duration} < 3 )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${Dot4Song}"                    Song ${Parse[0,"( DEBUFFSONG && ${Target.Buff[${Dot4Song}].Duration} < 3 )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${DichoSong}"                   Song ${Parse[0,"( BUFFSONG )"]}
    |- Below this is the stuff that I do not use in my twist. Keeping it here in case someone decides to adjust things later
    |/call AddToRotation BRD_DPS_MODEMELEE_Rotation "${SufferingSong}"               Song ${Parse[0,"( BUFFSONG )"]}
    |/call AddToRotation BRD_DPS_MODEMELEE_Rotation "${SprySonataSong}"              Song ${Parse[0,"( BUFFSONG )"]}
    |/call AddToRotation BRD_DPS_MODEMELEE_Rotation "${CasterAriaSong}"              Song ${Parse[0,"( BUFFSONG )"]}
    |/call AddToRotation BRD_DPS_MODEMELEE_Rotation "${PulseRegenSong}"              Song ${Parse[0,"( BUFFSONG )"]}
    |/call AddToRotation BRD_DPS_MODEMELEE_Rotation "${ChorusRegenSong}"             Song ${Parse[0,"( BUFFSONG )"]}
    |/call AddToRotation BRD_DPS_MODEMELEE_Rotation "${ArcaneSong}"                  Song ${Parse[0,"( BUFFSONG )"]}
    |/call AddToRotation BRD_DPS_MODEMELEE_Rotation "${ResistSong}"                  Song ${Parse[0,"( BUFFSONG )"]}
    |/call AddToRotation BRD_DPS_MODEMELEE_Rotation "${SpitefulSong}"                Song ${Parse[0,"( BUFFSONG )"]}
    |/call AddToRotation BRD_DPS_MODEMELEE_Rotation "${FateSong}"                    Song ${Parse[0,"( BUFFSONG )"]}
    |/call AddToRotation BRD_DPS_MODEMELEE_Rotation "${PsalmSong}"                   Song ${Parse[0,"( BUFFSONG )"]} 


    | - Down time buffs

    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${BardDPSAura}"                        Song  ${Parse[0,"( !${Me.Aura[1].Name.Find[${BardDPSAura_name}]} && !${UseRegenAura[SETTINGVAL]}  )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${BardRegenAura}"                      Song  ${Parse[0,"( !${Me.Aura[1].Name.Find[${BardRegenAura_name}]} && ${UseRegenAura[SETTINGVAL]}  )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${ChorusRegenSong}"                    Song ${Parse[0,"( BUFFSONG && !${DoMed[SETTINGVAL]} )"]}    
    | Run song is here, mostly for low level bards, SeloAA call is in the downtime sub...
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${BardRunBuff}"                        Song  ${Parse[0,"( !${DoAASelo} && ${DoRunSpeed[SETTINGVAL]} && BUFFBRDSPELL )"]}
    |**
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${AccelerandoSong}"                    Song  ${Parse[0,"( BUFFSONG  )"]}
    
    
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${BardRunBuff}"                        Song  ${Parse[0,"( !${DoAASelo} && ${DoRunSpeed[SETTINGVAL]} && BUFFBRDSPELL )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${CrescendoSong}"                      Song  ${Parse[0,"( !${Me.GemTimer[${Me.Gem[${CrescendoSong}]}]} && BUFFSONG && ${Me.PctMana}<75 )"]}    
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${PulseRegenSong}"                     Song ${Parse[0,"( BUFFSONG )"]}
    
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${ResistSong}"                         Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${WarMarchSong}"                  	    Song ${Parse[0,"( BUFFSONG )"]} 
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${MainAriaSong}"                  	    Song ${Parse[0,"( BUFFSONG )"]} 
    **|
    
    | - Down time item clicks
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${FindItem[Spider's Bite].Name}"       Item  ${Parse[1,"( !${Me.Buff[${Spell[${FindItem[Spider's Bite].Spell}]}].ID} && ${Spell[${FindItem[Spider's Bite].Spell}].Stacks} )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${FindItem[Rapier of Somber Notes]}"   Item  ${Parse[0,"( ${Spell[${FindItem[Rapier of Somber Notes].Spell}].Stacks} && (!${FindItem[Rapier of Somber Notes].TimerReady} ))"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${FindItem[Songblade of the Eternal]}" Item  ${Parse[0,"( ${Spell[${FindItem[Songblade of the Eternal].Spell}].Stacks} && (!${FindItem[Songblade of the Eternal].TimerReady} ))"]}    



    /call AddToRotation BRD_Burn_MODEMELEE_Rotation "Dance of Blades"                AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation BRD_Burn_MODEMELEE_Rotation "Flurry of Notes"                AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation BRD_Burn_MODEMELEE_Rotation "Frenzied Kicks"                 AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation BRD_Burn_MODEMELEE_Rotation "Funeral Dirge"                  AA ${Parse[0,"( ${Target.Named} )"]}  

/return


Sub BRD_Combat_Routine  

|**    
    /if ( !${Me.Buff[Selo's Accelerando].ID} && !${Me.Buff[Selo's Accelerato].ID} && ${RG_AAReady[Selo's Sonata]} && ${DoAASelo} ) {
    |- Cast Selo's AA if we do not have the buff
        /call AANow 3704 ${Me.ID}
    }
**|    
    /if (DODEBUFF) {
        /call Ordered_Rotation_Follow BRD_Debuff_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        |/if (${Macro.Return}) /return
    }

    /if ( DODPS ) {
        /call EngageTarget
        /if ( BURNCHECK ) {
            /call Ordered_Rotation_Follow BRD_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        }
        /call Ordered_Rotation_Follow BRD_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }

/return FALSE







Sub BRD_Downtime_Routine

    |- Check for DPS Aura if we are supposed to be using Regen Aura and Remove it
    /if ( ${Me.Song[${BardDPSAura}].Duration.Seconds} && ${UseRegenAura[SETTINGVAL]} ) /removebuff ${Me.Song[${BardDPSAura}].ID}
    /if ( !${Me.Buff[Selo's Accelerando].ID} && !${Me.Buff[Selo's Accelerato].ID} && ${RG_AAReady[Selo's Sonata]} && ${DoAASelo}) {
        |- Cast Selo's AA if we do not have the buff
        /call AANow 3704 ${Me.ID}
    } 
    |/if ( !${Me.Buff[ChorusRegenSong].ID} ) /call SongNow "${ChorusRegenSong}"" ${Me.ID}

    /call FollowRotation BRD_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID} TRUE 0

/return FALSE

Sub BRD_PullSetup
    /if ( ${DoAAPull[SETTINGVAL]} && ${RG_CanUseAA[Sonic Disturbance]}) {
	    /call Pull_SetAbility "Sonic Disturbance" "AA"
    } else /if (${InsultSong1.NotEqual[NULL]} && ${Me.Gem[${InsultSong1}]}) {
        /call Pull_SetAbility "${InsultSong1}" Spell
    } else /if ( ${Me.Gem[${DispelSong}]} ) {
        /call Pull_SetAbility "${DispelSong}" "Spell"
    } else {
		/call Pull_SetAbility "${ChordsAE}" "Spell"
	}
/return

Sub BRD_RemoveAura
    /docommand /removeaura ${BardDPSAura}
    /docommand /removeaura ${BardRegenAura}
/return

| Interim solution sub for mez config reset
| Bard really needs a way to easily toggle between different mez styles since bards are 'jack of all trades'
| This sub will allow user to use /rg DoDpsMez setting to easily toggle the mez mode config
| The default setup for the bard will be DoDpsMez = 0 which will be defined as using the rgmez stuff
|
| Implementation details:
|   Future will need an alternate method since the _Reset_Rotations call in the main loop is marked for removal
|     -> hopefully the plan is to move the <class name>_Reset_Rotations call into the Reset_Rotations sub in the main rgmercs.mac file
|     -> however, Probable best solution is to setup the Reset_Variables sub in the rgmercs.mac main file
| Options for mez mode are: DoDpsMez = 0/1/2 -> 0: robust rgmez mode (mez list, announcing mez, etc) 1: mez in dps rotation (no list checking, no announcing, higher dps performance), 2: No mez at all
Sub BRD_Reset_Rotations    
    /if ( (${DoDpsMez[SETTINGVAL]}==0) && !${IsMezzing} ) {
        /echo \awBardRgMezMode \ax(robust mez mode) selected -> DoDpsMez is 0, Reseting IsMezzing to TRUE
        /varset IsMezzing TRUE
    } else /if ( (${DoDpsMez[SETTINGVAL]}==1) && ${IsMezzing} ) {
        /echo \awBardDpsMezMode \ax(simple bard mez mode) selected -> DoDpsMez is 1, Reseting IsMezzing to FALSE
        /varset IsMezzing FALSE
    } else /if ( (${DoDpsMez[SETTINGVAL]}==2) && ${IsMezzing} ) {
        /echo \awBardNoMezMode \ax(bard mez off) selected -> DoDpsMez is 2, Reseting IsMezzing to FALSE
        /varset IsMezzing FALSE
    }
/return