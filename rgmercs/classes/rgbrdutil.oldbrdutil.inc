|- RGbrdutil.inc
|- Version 1.1
|- Updated: Terror of Luclin launch Dec 7 2021


#define MODEMELEE 0
#define MODECC 1
#define MODETLP 2


#define BUFFSONG "( ${Me.Gem[${mi.Key}]} && (${Float[${Me.Song[${mi.Key}].Duration.TotalSeconds}]} <= ${Math.Calc[${Spell[${Me.Song[${mi.Key}].Name}].MyCastTime.Seconds} + 6]}) )"
#define BUFFBRDSPELL "( ${Me.Gem[${mi.Key}]} && (${Float[${Me.Buff[${mi.Key}].Duration.TotalSeconds}]} <= ${Math.Calc[${Spell[${mi.Key}].MyCastTime.Seconds} + 6]}) )"
|- Special bard defines -- can move them to rgutil but only used for BRD.
|#define BUFFSONG "( ${Me.Gem[${mi.Key}]} && ${Float[${Me.Song[${mi.Key}].Duration.TotalSeconds}]} <= ${Math.Calc[${Spell[${Me.Song[${mi.Key}].Name}].MyCastTime.Seconds} + 6]} )"
|#define BUFFBRDSPELL "( ${Me.Gem[${mi.Key}]} && ${Float[${Me.Buff[${mi.Key}].Duration.Seconds}]} <= ${Math.Calc[${Spell[${mi.Key}].MyCastTime.Seconds} + 6]} )"
#define DEBUFFSONG "( ${Me.Gem[${mi.Key}]} && !${Target.Buff[${mi.Key}].ID} )"
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub BRD_Setup
    |- Bard setting list
    /declare RGList_BRD list outer

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
    /call AbilitySet_New  InsultSong
    /call AbilitySet_New  InsultSong2
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
    /varset ClassMode[SETTINGDESC] Set 0 = Level 85 or Higher AE Mez Only!, 1 = level 85 or Higher CC Melee Mode 2= TLP Below level 85
    /call RGLoadSetting BRD DoSlow 0 Combat "Set 0/1 to use Bard slow."
    /call RGLoadSetting BRD UseRegenAura 0 Options "Set 0 to use DPS Aura, 1 to use Regen aura." 0 "BRD_RemoveAura"
    /call RGLoadSetting BRD UseAASelo 1 Options "Set 0/1 to use AA Selo's Sonata"
    /call RGLoadSetting BRD DoRunSpeed 1 Options "set 0/1 to use the RunSpeed song buff."
    /call RGLoadSetting BRD UseQuicktime 1 Options "Set 0/1 to toggle the use of the Quicktime spell. Note: Kepping this on can trigger the EQ Client Stuck Gems bug. Defaults to: 1"
    /call RGLoadSetting BRD ReflexManaPct 80 Options "Set Minimum mana PCT to use ReflexStrike"
    /call RGLoadSetting BRD DoDpsMez 1 Options "Turns on Dps Mez works best if /rg mezon = 0"
    /call RGLoadSetting BRD DoIntimidate 0 Combat "Set 0/1 to toggle Intimidate starting at level 26. Used with fear kiting."
    /call RGLoadSetting BRD DoAAPull 1 Combat "Turns off Pulling with AA to allow use of Dispel song to avoid Summonings" 
    /call RGLoadSetting BRD DoAmpSong 1 Options "Turns on using amplifty As a Song in rotation during dps"
    /call RGLoadSetting BRD AutoDebuffAt 99 Combat "When to Start Debuffs"
	/call RGLoadSetting BRD HPStopDOT 30 Combat "%HP to cut off to stop casting dots."
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
|- BardDPSAura - Level Ranges 55 - 115
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

|- BardRegenAura - Level Ranges 82 - 112
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

| - Bard Alliance
    /call AbilitySet_Add "Conjunction of Sticks and Stones" AllianceSong
    /call AbilitySet_Add "Alliance of Sticks and Stones" AllianceSong
    /call AbilitySet_Add "Covenant of Sticks and Stones" AllianceSong
    /call AbilitySet_Add "Coalition of Sticks and Stones" AllianceSong
    /call AbilitySet_ChooseOuter AllianceSong AllianceSong  

| - Bard Charm Song
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

| - Resists Song - 
    /call AbilitySet_Add "Psalm of Cooling" ResistSong
    /call AbilitySet_Add "Psalm of Purity" ResistSong
    /call AbilitySet_Add "Psalm of Warmth" ResistSong
    /call AbilitySet_Add "Psalm of Vitality" ResistSong
    /call AbilitySet_Add "Psalm of Veeshan" ResistSong
    /call AbilitySet_Add "Psalm of the Forsaken" ResistSong
    /call AbilitySet_Add "Second Psalm of Veeshan" ResistSong
    /call AbilitySet_Add "Psalm of the Restless" ResistSong
    /call AbilitySet_Add "Psalm of the Pious" ResistSong
    /call AbilitySet_ChooseOuter ResistSong ResistSong       

|- MainAriaSong - Level Ranges 45 - 111
|  What differs between PsalmSong and MainAriaSong ???
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

|- CasterAriaSong - Level Range 72 - 113
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

|- WarMarchSong Level Range 10 - 114
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
  
|- SufferingSong - Level Range 89 - 114
    /call AbilitySet_Add "Shojralen's Song of Suffering" SufferingSong
    /call AbilitySet_Add "Omorden's Song of Suffering" SufferingSong 
    /call AbilitySet_Add "Travenro's Song of Suffering" SufferingSong 
    /call AbilitySet_Add "Fjilnauk's Song of Suffering" SufferingSong
    /call AbilitySet_Add "Kaficus' Song of Suffering" SufferingSong
    /call AbilitySet_Add "Hykast's Song of Suffering" SufferingSong
    /call AbilitySet_Add "Noira's Song of Suffering" SufferingSong    
    /call AbilitySet_ChooseOuter SufferingSong SufferingSong

|- ArcaneSong - Level Range 70 - 115
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

|- SprySonataSong - Level Range 77 - 118
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

|- PulseRegenSong - Level Range 77 - 111 ** -- Low level regens are for TLP users thus preferring mana over health.
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

|- ChorusRegenSong - Level Range 6 - 113
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

|- CrescendoSong - Level Range 75 - 114
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
|- InsultSong1 - Level Range 12 - 112 Timer 3
    /call AbilitySet_Add "Nord's Disdain" InsultSong
    /call AbilitySet_Add "Sogran's Insult" InsultSong
    /call AbilitySet_Add "Yelinak's Insult" InsultSong
    /call AbilitySet_Add "Omorden's Insult" InsultSong   
    /call AbilitySet_Add "Tsaph's Insult" InsultSong
    /call AbilitySet_Add "Fjilnauk's Insult" InsultSong
    /call AbilitySet_Add "Hykast's Insult" InsultSong
    /call AbilitySet_Add "Venimor's Insult" InsultSong 
    |- Below Level 85 This line turns into "bellow" instead of "Insult"
    /call AbilitySet_Add "Bellow of Chaos" InsultSong
    /call AbilitySet_Add "Brusco's Bombastic Bellow" InsultSong   
    /call AbilitySet_Add "Brusco's Boastful Bellow" InsultSong
    /call AbilitySet_ChooseOuter InsultSong1 InsultSong
    
|- Insult Song2 Timer 6
    /call AbilitySet_Add "Lyrin's Insult" InsultSong2
    /call AbilitySet_Add "Garath's Insult" InsultSong2
    /call AbilitySet_Add "Kaficus' Insult" InsultSong2
    /call AbilitySet_Add "Travenro's Insult" InsultSong2
    /call AbilitySet_Add "Sathir's Insult" InsultSong2
    /call AbilitySet_ChooseOuter InsultSong2 InsultSong2

|- DichoSong Level Range - 101 - 106
    /call AbilitySet_Add "Ecliptic Psalm" DichoSong
    /call AbilitySet_Add "Composite Psalm" DichoSong
    /call AbilitySet_Add "Dissident Psalm" DichoSong    
    /call AbilitySet_Add "Dichotomic Psalm" DichoSong
    /call AbilitySet_ChooseOuter DichoSong DichoSong

|- MezSpell - Level Range 15 - 114
    /call AbilitySet_Add "Slumber of the Diabo" MezSpell
    /call AbilitySet_Add "Lullaby of Nightfall" MezSpell
    /call AbilitySet_Add "Lullaby of Zburator" MezSpell
    /call AbilitySet_Add "Slumber of Zburator" MezSpell
    /call AbilitySet_Add "Slumber of Jembel" MezSpell  
    /call AbilitySet_Add "Lullaby of Jembel" MezSpell 
    /call AbilitySet_Add "Slumber of Silisia" MezSpell
    /call AbilitySet_Add "Lullaby of Silisia" MezSpell
    /call AbilitySet_Add "Slumber of Motlak" MezSpell
    /call AbilitySet_Add "Lullaby of the Forsaken" MezSpell    
    /call AbilitySet_Add "Slumber of Kolain" MezSpell
    /call AbilitySet_Add "Lullaby of the Forlorn" MezSpell
    /call AbilitySet_Add "Slumber of Sionachie" MezSpell  
    /call AbilitySet_Add "Lullaby of the Lost" MezSpell    
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

|- MezAESpell - Level Range 85 - 115 **
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

| - Singletarget Assonant Slow Line


|- AESlowSong - Level Range 20 - 114 (Single target works better)  

    /call AbilitySet_Add "Radiwol's Melodic Binding" AESlowSong
    /call AbilitySet_Add "Dekloaz's Melodic Binding" AESlowSong
    /call AbilitySet_Add "Protan's Melodic Binding" AESlowSong  
    /call AbilitySet_Add "Largo's Melodic Binding" AESlowSong    
    /call AbilitySet_ChooseOuter AESlowSong AESlowSong

 |- AccelerandoSong - Level Range 88 - 113 **
    /call AbilitySet_Add "Satisfying Accelerando" AccelerandoSong
    /call AbilitySet_Add "Placating Accelerando" AccelerandoSong
    /call AbilitySet_Add "Atoning Accelerando" AccelerandoSong    
    /call AbilitySet_Add "Allaying Accelerando" AccelerandoSong
    /call AbilitySet_Add "Ameliorating Accelerando" AccelerandoSong
    /call AbilitySet_Add "Assuaging Accelerando" AccelerandoSong  
    /call AbilitySet_Add "Alleviating Accelerando" AccelerandoSong    
    /call AbilitySet_ChooseOuter AccelerandoSong AccelerandoSong

 |- SpitefulSong - Level Range 90 - 
    /call AbilitySet_Add "Von Deek's Spiteful Lyric" SpitefulSong
    /call AbilitySet_Add "Omorden's Spiteful Lyric" SpitefulSong
    /call AbilitySet_Add "Travenro's Spiteful Lyric" SpitefulSong    
    /call AbilitySet_Add "Fjilnauk's Spiteful Lyric" SpitefulSong
    /call AbilitySet_Add "Kaficus' Spiteful Lyric" SpitefulSong
    /call AbilitySet_Add "Hykast's Spiteful Lyric" SpitefulSong  
    /call AbilitySet_Add "Lyrin's Spiteful Lyric" SpitefulSong    
    /call AbilitySet_ChooseOuter SpitefulSong SpitefulSong

 |- RecklessSong - Level Range 93 - 113 **
    /call AbilitySet_Add "Kai's Reckless Renewal" RecklessSong
    /call AbilitySet_Add "Reivaj's Reckless Renewal" RecklessSong    
    /call AbilitySet_Add "Rigelon's Reckless Renewal" RecklessSong
    /call AbilitySet_Add "Rytan's Reckless Renewal" RecklessSong
    /call AbilitySet_Add "Ruaabri's Reckless Renewal" RecklessSong  
    /call AbilitySet_Add "Ryken's Reckless Renewal" RecklessSong    
    /call AbilitySet_ChooseOuter RecklessSong RecklessSong
    
 |- Fatesong - Level Range 77 - 112 **
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

|- DotSong - Level Range 30 - 115  
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
  
    /call AbilitySet_Add "Aria of Absolution" CureSpell    
    /call AbilitySet_ChooseOuter CureSpell  CureSpell
/return

|-----------------------------------------------------------------------------
|- SUB - meleeSpellConfig - Configure Spell Gems for base Melee Twist
|-----------------------------------------------------------------------------
Sub BRD_ModeConfigMODEMELEE
    /varset IsMezzing FALSE
    /call InitMez

    /echo Mez is Default Combat only in this Mode Singletarget mez is Off. - For a CC/Melee Combo Mode try /rg Classmode 1    
    /if (${DoSlow[SETTINGVAL]}) {
        /if (${SlowSong.Equal[NULL]}) {
            /varset Spell1 ${AESlowSong}
        } else {
            /varset Spell1 ${SlowSong}
        }
    } else {
        /varset Spell1 ${InsultSong1}
    }
    /varset Spell2 ${SprySonataSong}
    /varset Spell3 ${WarMarchSong}
    /varset Spell4 ${ChorusRegenSong}
    /varset Spell5 ${MezSpell}
    /if (${Me.Level} <=63) {
        /varset Spell6 ${LowAriaSong}
    } else {
        /varset Spell6 ${MainAriaSong}
    }
    /varcalc DoAASelo ${UseAASelo[SETTINGVAL]} && ${RG_CanUseAA[Selo's Sonata]}

    /if (!${DoAASelo}) {
        /varset Spell7 ${BardRunBuff}
    } else {
        /varset Spell7 ${DichoSong}
    }
    /if (${CureSpell.NotEqual[NULL]}) {
        /varset Spell8 ${CureSpell}
    } else {
        /varset Spell8 ${BardDPSAura}
    }

    
    | - This call has to be Above the Songs in all modes - Otherwise it never Gets to the Combat routines.
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${MezAESpell}"                  Song ${Parse[0,"( ${DoDpsMez[SETTINGVAL]} && (${XAssist.XTFullHaterCount} >= ${MezAECount[SETTINGVAL]}) )"]}

    |-Aggro Drops
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Fading Memories"                AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Hymn of the Last Stand"         AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Shield of Notes"                AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]}
    
    |- Main Tank Dead Stepping in to Keep folks alive.
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Dissonant Chord"                AA ${Parse[0,"( ${SpawnCount[pccorpse ${assistid}]} )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "/call BRD_ReflexStrikeManaCheck"    Command ${Parse[0,"( ${NPCDiscReady[${ReflexStrike}]} )"]}
    | - DPs AAs'a
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Boastful Bellow"                AA ${Parse[0,"( !${Target.Buff[${Me.AltAbility[Boastful Bellow].ID}].} && ${Target.PctHPs}>90 )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Song of Stone"                  AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Lyrical Prankster"              AA ${Parse[0,"( TRUE )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Cacophony"                      AA ${Parse[0,"( ${Target.Named} && DOTSPELLCHECK )"]}  
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Bladed Song"                    AA ${Parse[0,"( TRUE )"]}     
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Fierce Eye"                     AA ${Parse[0,"( !${Me.Buff[Fierce Eye].ID} )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Spire of the Minstrels"         AA ${Parse[0,"( !${Me.Buff[Spire of the Minstrels].ID} )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Quick Time"                     AA ${Parse[0,"( ${UseQuicktime[SETTINGVAL]} )"]}     

    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${MountItem[SETTINGVAL]}"       Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "/dismount"                      Command ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    /if (${Me.Level}>=20) {
        /call AddToRotation BRD_DPS_MODEMELEE_Rotation "Intimidation"                   Ability ${Parse[0,"( ${DoIntimidate[SETTINGVAL]} )"]}
    }
    |- Items Map
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${Epic}"                                  Item       ${Parse[0,"( ${Spell[${FindItem[${Epic}].Spell}].Stacks} && (!${FindItem[${Epic}].TimerReady}) )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${FindItem[${Me.Inventory[Chest].Name}]}" Item       ${Parse[0,"( ${DoChestClick[SETTINGVAL]} && ${Spell[${FindItem[${Me.Inventory[Chest].Name}].Spell}].Stacks} && (!${FindItem[${Me.Inventory[Chest].Name}].TimerReady}) )"]}   
    |- Combat Twist
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${AccelerandoSong}"             Song ${Parse[0,"( BUFFSONG )"]}     
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${RecklessSong}"                Song ${Parse[0,"( BUFFSONG )"]}    
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${SlowSong}"                    Song ${Parse[0,"( DEBUFFSONG && !${Target.Slowed.ID} )"]} 
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${AESlowSong}"                  Song ${Parse[0,"( DEBUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${ResistSong}"                  Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${InsultSong1}"                 Song ${Parse[0,"( (${Me.PctMana}>50 && ${Target.PctHPs}>50) )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${InsultSong2}"                 Song ${Parse[0,"( (${Me.PctMana}>50 && ${Target.PctHPs}>50) )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${WarMarchSong}"                Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${SufferingSong}"               Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${SprySonataSong}"              Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${MainAriaSong}"                Song ${Parse[0,"( BUFFSONG )"]}     
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${CasterAriaSong}"              Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${PulseRegenSong}"              Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${ChorusRegenSong}"             Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${ArcaneSong}"                  Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${DichoSong}"                   Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${SpitefulSong}"                Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${FateSong}"                    Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODEMELEE_Rotation "${PsalmSong}"                   Song ${Parse[0,"( BUFFSONG )"]} 


    | - Down time buffs
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${AccelerandoSong}"                    Song  ${Parse[0,"( BUFFSONG  )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${BardDPSAura}"                        Song  ${Parse[0,"( !${Me.Aura[1].Name.Find[${BardDPSAura_name}]} && !${UseRegenAura[SETTINGVAL]}  )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${BardRegenAura}"                      Song  ${Parse[0,"( !${Me.Aura[1].Name.Find[${BardRegenAura_name}]} && ${UseRegenAura[SETTINGVAL]}  )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${BardRunBuff}"                        Song  ${Parse[0,"( !${DoAASelo} && ${DoRunSpeed[SETTINGVAL]} && BUFFBRDSPELL )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${CrescendoSong}"                      Song  ${Parse[0,"( !${Me.GemTimer[${Me.Gem[${CrescendoSong}]}]} && BUFFSONG && ${Me.PctMana}<75 )"]}    
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${PulseRegenSong}"                     Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${ChorusRegenSong}"                    Song ${Parse[0,"( BUFFSONG )"]}    
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${ResistSong}"                         Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${WarMarchSong}"                  	Song ${Parse[0,"( BUFFSONG )"]} 
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${MainAriaSong}"                  	Song ${Parse[0,"( BUFFSONG )"]} 
 
    | - Down time item clicks
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${FindItem[Spider's Bite].Name}"       Item  ${Parse[1,"( !${Me.Buff[${Spell[${FindItem[Spider's Bite].Spell}]}].ID} && ${Spell[${FindItem[Spider's Bite].Spell}].Stacks} )"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${FindItem[Rapier of Somber Notes]}"   Item  ${Parse[0,"( ${Spell[${FindItem[Rapier of Somber Notes].Spell}].Stacks} && (!${FindItem[Rapier of Somber Notes].TimerReady} ))"]}
    /call AddToRotation BRD_Downtime_MODEMELEE_Rotation "${FindItem[Songblade of the Eternal]}" Item  ${Parse[0,"( ${Spell[${FindItem[Songblade of the Eternal].Spell}].Stacks} && (!${FindItem[Songblade of the Eternal].TimerReady} ))"]}    



    /call AddToRotation BRD_Burn_MODEMELEE_Rotation "Dance of Blades"                AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation BRD_Burn_MODEMELEE_Rotation "Flurry of Notes"                AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation BRD_Burn_MODEMELEE_Rotation "Frenzied Kicks"                 AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation BRD_Burn_MODEMELEE_Rotation "Funeral Dirge"                  AA ${Parse[0,"( ${Target.Named} )"]}  

/return
|-----------------------------------------------------------------------------
|- SUB -CCSPELLConfig - Configure Spell Gems for base CC/Melee Twist
|-----------------------------------------------------------------------------
Sub BRD_ModeConfigMODECC
    /varset IsMezzing TRUE
  
    /echo In this Mode we Support Melee And Mez with Both AE and Singletarget
    /echo This Will effect Bard Performance on larger Pulls!
    /if (${DoSlow[SETTINGVAL]}) {
        /if (${SlowSong.Equal[NULL]}) {
            /varset Spell1 ${AESlowSong}
        } else {
            /varset Spell1 ${SlowSong}
        }
    } else {
        /varset Spell1 ${InsultSong1}
    }
    /varset Spell2 ${SprySonataSong}
    /varset Spell3 ${WarMarchSong}
    /varset Spell4 ${ChorusRegenSong}
    /varset Spell5 ${MezSpell}
    /varset Spell6 ${MainAriaSong}
    /varset DoAASelo ${RG_CanUseAA[Selo's Sonata]}


    /if (!${DoAASelo}) {
        /varset Spell7 ${BardRunBuff}
    } else {
        /varset Spell7 ${DichoSong}
    }

    /varset Spell9 ${InsultSong2}
    /varset Spell10 ${MezAESpell}
    /varset Spell11 ${CrescendoSong}
    /varset Spell12 ${SufferingSong}
    /varset Spell13 ${ArcaneSong}
    
    | - This call has to be Above the Songs in all modes - Otherwise it never Gets to the Combat routines.
    /call BRD_DefaultDownRotationConfig BRD_Downtime_MODECC_Rotation
    /call BRD_DefaultBurnRotationConfig BRD_Burn_MODECC_Rotation
    /call BRD_DefaultDPSRotationConfig BRD_DPS_MODECC_Rotation
   
/return 

|-----------------------------------------------------------------------------
|- SUB -TLP Mode
|-----------------------------------------------------------------------------
Sub BRD_ModeConfigMODETLP
    /varset IsMezzing TRUE
    /echo This Is TLP Mode Bard! 

    /if (${DoSlow[SETTINGVAL]}) {
        /if (${SlowSong.Equal[NULL]}) {
            /varset Spell1 ${AESlowSong}
        } else {
            /varset Spell1 ${SlowSong}
        }
    } else {
        /varset Spell1 ${DispelSong}
    }

    /varset Spell2 ${ResistSong}
    /varset Spell3 ${MainAriaSong}
    /varset Spell4 ${WarMarchSong}
    /varset Spell5 ${ChorusRegenSong}
    /varset Spell6 ${AmpSong}
    /varset Spell7 ${MezSpell}
    /varset DoAASelo  ${RG_CanUseAA[Selo's Sonata]}


    /if (!${DoAASelo}) {
        /varset Spell8 ${BardRunBuff}
    } else {
        /varset Spell9 NULL
    }

    
    | - This call has to be Above the Songs in all modes - Otherwise it never Gets to the Combat routines.
        
    |-Aggro Drops
  |**
    None of these will work in a tlp bard. as there is no PCTaggro yet till expansion 19
    /call AddToRotation BRD_DPS_MODETLP_Rotation "Fading Memories"                AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]} 
    /call AddToRotation BRD_DPS_MODETLP_Rotation "Hymn of the Last Stand"         AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]} 
    /call AddToRotation BRD_DPS_MODETLP_Rotation "Shield of Notes"                AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]}
 **|   
    |- Main Tank Dead Stepping in to Keep folks alive.
    | - DPs AAs'a
    /call AddToRotation BRD_DPS_MODETLP_Rotation "Boastful Bellow"                AA ${Parse[0,"( !${Target.Buff[${Me.AltAbility[Boastful Bellow].ID}].} && ${Target.PctHPs}>90 )"]}
    /call AddToRotation BRD_DPS_MODETLP_Rotation "${MountItem[SETTINGVAL]}"       Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]} ) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID} ) ) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation BRD_DPS_MODETLP_Rotation "/dismount"                      Command ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    | /if (${Me.Level}>=20) {
    |     /call AddToRotation BRD_DPS_MODETLP_Rotation "Intimidation"                Ability ${Parse[0,"( ${DoIntimidate[SETTINGVAL]} )"]}
    | }
    |- Items Map
    /call AddToRotation BRD_DPS_MODETLP_Rotation "${Epic}"                                   Item       ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${Spell[${FindItem[${Epic}].Spell}].Stacks} && (!${FindItem[${Epic}].TimerReady}) )"]} 
    /call AddToRotation BRD_DPS_MODETLP_Rotation "${FindItem[${Me.Inventory[Chest].Name}]}"  Item       ${Parse[0,"( ${DoChestClick[SETTINGVAL]} && ${Spell[${FindItem[${Me.Inventory[Chest].Name}].Spell}].Stacks} && (!${FindItem[${Me.Inventory[Chest].Name}].TimerReady}) )"]}   
    /call AddToRotation BRD_DPS_MODETLP_Rotation "Songblade of the Eternal"                  Item       ${Parse[0,"( ${Spell[${FindItem[Songblade of the Eternal].Spell}].Stacks} && (!${FindItem[Songblade of the Eternal].TimerReady}) )"]} 
    /call AddToRotation BRD_DPS_MODETLP_Rotation "Rapier of Somber Notes"                    Item       ${Parse[0,"( ${Spell[${FindItem[Rapier of Somber Notes].Spell}].Stacks} && (!${FindItem[Rapier of Somber Notes].TimerReady}) )"]} 
    |- Combat Twist
    /call AddToRotation BRD_DPS_MODETLP_Rotation "${AmpSong}"                               Song ${Parse[0,"( BUFFSONG && ${DoAmpSong[SETTINGVAL]} )"]}
    /call AddToRotation BRD_DPS_MODETLP_Rotation "${ResistSong}"                            Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODETLP_Rotation "${WarMarchSong}"                          Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_DPS_MODETLP_Rotation "${MainAriaSong}"                          Song ${Parse[0,"( BUFFSONG )"]}     
    /call AddToRotation BRD_DPS_MODETLP_Rotation "${ChorusRegenSong}"                       Song ${Parse[0,"( BUFFSONG )"]}
    | - POR song removed for now.
    | /call AddToRotation BRD_DPS_MODETLP_Rotation "${ArcaneSong}"                            Song ${Parse[0,"( BUFFSONG )"]}
  
    | - Down time buffs
    /call AddToRotation BRD_Downtime_MODETLP_Rotation "${BardDPSAura}"                        Song ${Parse[0,"( !${Me.Aura[1].Name.Find[${BardDPSAura_name}]} && !${UseRegenAura[SETTINGVAL]}  )"]}
    /call AddToRotation BRD_Downtime_MODETLP_Rotation "${BardRegenAura}"                      Song ${Parse[0,"( !${Me.Aura[1].Name.Find[${BardRegenAura_name}]} && ${UseRegenAura[SETTINGVAL]}  )"]}
    /call AddToRotation BRD_Downtime_MODETLP_Rotation "${BardRunBuff}"                        Song ${Parse[0,"( !${DoAASelo} && ${DoRunSpeed[SETTINGVAL]} && BUFFBRDSPELL )"]}
    /call AddToRotation BRD_Downtime_MODETLP_Rotation "${CrescendoSong}"                      Song ${Parse[0,"( !${Me.GemTimer[${Me.Gem[${CrescendoSong}]}]} && BUFFSONG && ${Me.PctMana}<75 )"]}    
    /call AddToRotation BRD_Downtime_MODETLP_Rotation "${ChorusRegenSong}"                    Song ${Parse[0,"( BUFFSONG )"]}    
    /call AddToRotation BRD_Downtime_MODETLP_Rotation "${ResistSong}"                         Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation BRD_Downtime_MODETLP_Rotation "${WarMarchSong}"                  	  Song ${Parse[0,"( BUFFSONG )"]} 
    /call AddToRotation BRD_Downtime_MODETLP_Rotation "${MainAriaSong}"                  	  Song ${Parse[0,"( BUFFSONG )"]} 
 
    | - Down time item clicks
    /call AddToRotation BRD_Downtime_MODETLP_Rotation "${FindItem[Spider's Bite].Name}"       Item  ${Parse[1,"( !${Me.Buff[${Spell[${FindItem[Spider's Bite].Spell}]}].ID} && ${Spell[${FindItem[Spider's Bite].Spell}].Stacks} )"]}
    /call AddToRotation BRD_Downtime_MODETLP_Rotation "${FindItem[Rapier of Somber Notes]}"   Item  ${Parse[0,"( ${Spell[${FindItem[Rapier of Somber Notes].Spell}].Stacks} && (!${FindItem[Rapier of Somber Notes].TimerReady} ))"]}
    /call AddToRotation BRD_Downtime_MODETLP_Rotation "${FindItem[Songblade of the Eternal]}" Item  ${Parse[0,"( ${Spell[${FindItem[Songblade of the Eternal].Spell}].Stacks} && (!${FindItem[Songblade of the Eternal].TimerReady} ))"]}    


    | - Debuff Rotation
    /call AddToRotation BRD_Debuff_MODETLP_Rotation "${RecklessSong}"                Song ${Parse[0,"( BUFFSONG )"]}    
    /call AddToRotation BRD_Debuff_MODETLP_Rotation "${SlowSong}"                    Song ${Parse[0,"( ${DoSlow[SETTINGVAL]} && DEBUFFSONG && !${Target.Slowed.ID} )"]} 
    /call AddToRotation BRD_Debuff_MODETLP_Rotation "${AESlowSong}"                  Song ${Parse[0,"( ${DoSlow[SETTINGVAL]} && DEBUFFSONG )"]}


    |- Burns
    /call AddToRotation BRD_Burn_MODETLP_Rotation "Dance of Blades"                AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation BRD_Burn_MODETLP_Rotation "Flurry of Notes"                AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation BRD_Burn_MODETLP_Rotation "Frenzied Kicks"                 AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation BRD_Burn_MODETLP_Rotation "Funeral Dirge"                  AA ${Parse[0,"( ${Target.Named} )"]}  
   
/return 
|**
|-----------------------------------------------------------------------------
|- SUB - CasterSpellConfig - Configure Spell Gems for base Caster Twist
|-----------------------------------------------------------------------------
Sub BRD_ModeConfigMODECASTER
    /varset IsMezzing TRUE
    /if (${DoSlow[SETTINGVAL]}) {
        /if (${SlowSong.Equal[NULL]}) {
            /varset Spell1 ${AESlowSong}
        } else {
            /varset Spell1 ${SlowSong}
        }
    } else {
        /varset Spell1 ${InsultSong1}
    }
    /varset Spell2 ${SprySonataSong}
    /varset Spell3 ${WarMarchSong}
    /varset Spell4 ${CasterAriaSong}
    /varset Spell5 ${MezSpell}
    /varset Spell6 ${MainAriaSong}
    /varset DoAASelo ${RG_CanUseAA[Selo's Sonata]}


    /if (!${DoAASelo}) {
        /varset Spell7 ${BardRunBuff}
    } else {
        /varset Spell7 ${DichoSong}
    }
    /if (${CureSpell.NotEqual[NULL]}) {
        /varset Spell8 ${CureSpell}
    } else {
        /varset Spell8 ${BardDPSAura}
    }
    /varset Spell9 ${InsultSong2}
    /varset Spell10 ${MezAESpell}
    /varset Spell11 ${CrescendoSong}
    /varset Spell12 ${SufferingSong}
    /varset Spell13 ${ArcaneSong}

    | - This call has to be Above the Songs in all modes - Otherwise it never Gets to the Combat routines.
    /call BRD_DefaultDownRotationConfig BRD_Downtime_MODECASTER_Rotation 
    /call BRD_DefaultBurnRotationConfig BRD_Burn_MODECASTER_Rotation 
    /call BRD_DefaultDPSRotationConfig BRD_DPS_MODECASTER_Rotation
/return 


|-----------------------------------------------------------------------------
|- SUB - tankSpellConfig - Configure Spell Gems for Hybrid Group
|-----------------------------------------------------------------------------
Sub BRD_ModeConfigMODETANK
    /varset IsMezzing TRUE
    /if (${DoSlow[SETTINGVAL]}) {
        /if (${SlowSong.Equal[NULL]}) {
            /varset Spell1 ${AESlowSong}
        } else {
            /varset Spell1 ${SlowSong}
        }
    } else {
        /varset Spell1 ${InsultSong1}
    }
    /varset Spell2 ${SprySonataSong}
    /varset Spell3 ${WarMarchSong}
    /varset Spell4 ${ChorusRegenSong}
    /varset Spell5 ${MezSpell}
    /varset Spell6 ${RecklessSong}
    /varset DoAASelo  ${RG_CanUseAA[Selo's Sonata]}


    /if (!${DoAASelo}) {
        /varset Spell7 ${BardRunBuff}
    } else {
        /varset Spell7 ${DichoSong}
    }

    /varset Spell10 ${MezAESpell}
    /varset Spell11 ${CrescendoSong}
    /varset Spell12 ${SpitefulSong}
    /varset Spell13 ${PulseRegenSong}

    | - This call has to be Above the Songs in all modes - Otherwise it never Gets to the Combat routines.
    /call BRD_DefaultDownRotationConfig BRD_Downtime_MODETANK_Rotation
    /call BRD_DefaultBurnRotationConfig BRD_Burn_MODETANK_Rotation 
    /call BRD_DefaultDPSRotationConfig BRD_DPS_MODETANK_Rotation
/return 

|-----------------------------------------------------------------------------
|- SUB - HybridSpellConfig - Configure Spell Gems for tank
|-----------------------------------------------------------------------------
Sub BRD_ModeConfigMODEHYBRID
    /varset IsMezzing TRUE
    /if (${DoSlow[SETTINGVAL]}) {
        /if (${SlowSong.Equal[NULL]}) {
            /varset Spell1 ${AESlowSong}
        } else {
            /varset Spell1 ${SlowSong}
        }
    } else {
        /varset Spell1 ${InsultSong1}
    }
    /varset Spell2 ${SprySonataSong}
    /varset Spell3 ${WarMarchSong}
    /varset Spell4 ${ChorusRegenSong}
    /varset Spell5 ${MezSpell}
    /varset Spell6 ${MainAriaSong}
    /varset DoAASelo  ${RG_CanUseAA[Selo's Sonata]}


    /if (!${DoAASelo}) {
        /varset Spell7 ${BardRunBuff}
    } else {
        /varset Spell7 ${DichoSong}
    }
    /varset Spell8 ${CasterAriaSong}
    /varset Spell9 ${InsultSong2}
    /varset Spell10 ${MezAESpell}
    /varset Spell11 ${CrescendoSong}
    /varset Spell12 ${SufferingSong}
    /varset Spell13 ${ArcaneSong}

    | - This call has to be Above the Songs in all modes - Otherwise it never Gets to the Combat routines.
    /call BRD_DefaultDownRotationConfig BRD_Downtime_MODEHYBRID_Rotation
    /call BRD_DefaultBurnRotationConfig BRD_Burn_MODEHYBRID_Rotation  
    /call BRD_DefaultDPSRotationConfig BRD_DPS_MODEHYBRID_Rotation
/return 

|-----------------------------------------------------------------------------
|- SUB - beastmodeSpellConfig - Configure Spell Gems for Beast Mode (No_one) Setup
|-----------------------------------------------------------------------------
Sub BRD_ModeConfigMODEBEAST
    /varset IsMezzing TRUE
    /if (${DoSlow[SETTINGVAL]}) {
        /if (${SlowSong.Equal[NULL]}) {
            /varset Spell1 ${AESlowSong}
        } else {
            /varset Spell1 ${SlowSong}
        }
    } else {
        /varset Spell1 ${InsultSong1}
    }
    /varset Spell2 ${SprySonataSong}
    /varset Spell3 ${WarMarchSong}
    /varset Spell4 ${ChorusRegenSong}
    /varset Spell5 ${MezSpell}
    /varset Spell6 ${MainAriaSong}
    /varset DoAASelo  ${RG_CanUseAA[Selo's Sonata]}


    /if (!${DoAASelo}) {
        /varset Spell7 ${BardRunBuff}
    } else {
        /varset Spell7 ${DichoSong}
    }
    /if (${CureSpell.NotEqual[NULL]}) {
        /varset Spell8 ${CureSpell}
    } else {
        /varset Spell8 ${BardDPSAura}
    }
    /varset Spell9 ${Dot1Song}
    /varset Spell10 ${MezAESpell}
    /varset Spell11 ${CrescendoSong}
    /varset Spell12 ${SufferingSong}
    /varset Spell13 ${Dot2Song}

    | - This call has to be Above the Songs in all modes - Otherwise it never Gets to the Combat routines.
    /call BRD_DefaultDownRotationConfig BRD_Downtime_MODEBEAST_Rotation
    /call BRD_DefaultBurnRotationConfig BRD_Burn_MODEBEAST_Rotation 
    /call BRD_DefaultDPSRotationConfig BRD_DPS_MODEBEAST_Rotation
/return 

|-----------------------------------------------------------------------------
|- SUB - beastmodeSpellConfig - Configure Spell Gems for Beast Mode (No_one) Setup
|-----------------------------------------------------------------------------
Sub BRD_ModeConfigMODEPULL
    /varset IsMezzing FALSE
    /if (${DoSlow[SETTINGVAL]}) {
        /if (${SlowSong.Equal[NULL]}) {
            /varset Spell1 ${AESlowSong}
        } else {
            /varset Spell1 ${SlowSong}
        }
    } else {
        /varset Spell1 ${InsultSong1}
    }
    /varset Spell2 ${SprySonataSong}
    /varset Spell3 ${WarMarchSong}
    /varset Spell4 ${ChorusRegenSong}
    /varset Spell5 ${MezSpell}
    /varset Spell6 ${MainAriaSong}
    /varset DoAASelo ${RG_CanUseAA[Selo's Sonata]}


    /if (!${DoAASelo}) {
        /varset Spell7 ${BardRunBuff}
    } else {
        /varset Spell7 ${DichoSong}
    }
    /if (${CureSpell.NotEqual[NULL]}) {
        /varset Spell8 ${CureSpell}
    } else {
        /varset Spell8 ${BardDPSAura}
    }
    /varset Spell9 ${Dot1Song}
    /varset Spell10 ${MezAESpell}
    /varset Spell11 ${CrescendoSong}
    /varset Spell12 ${SufferingSong}
    /varset Spell13 ${Dot2Song}

    | - This call has to be Above the Songs in all modes - Otherwise it never Gets to the Combat routines.
    | - commented out config calls because this is the puller only mode
    |/call BRD_DefaultDownRotationConfig BRD_Downtime_MODEBEAST_Rotation
    |/call BRD_DefaultBurnRotationConfig BRD_Burn_MODEBEAST_Rotation 
    |/call BRD_DefaultDPSRotationConfig BRD_DPS_MODEBEAST_Rotation
/return 

**|

Sub BRD_DefaultDownRotationConfig(string rotation_name)
    | - Down time buffs
    /call AddToRotation "${rotation_name}" "${BardDPSAura}"                        Song  ${Parse[0,"( !${Me.Aura[1].Name.Find[${BardDPSAura_name}]} && !${UseRegenAura[SETTINGVAL]}  )"]}
    /call AddToRotation "${rotation_name}" "${AmpSong}"                            Song ${Parse[0,"( BUFFSONG && ${DoAmpSong[SETTINGVAL]} )"]}  
    /call AddToRotation "${rotation_name}" "${BardRegenAura}"                      Song  ${Parse[0,"( !${Me.Aura[1].Name.Find[${BardRegenAura_name}]} && ${UseRegenAura[SETTINGVAL]}  )"]}
    /call AddToRotation "${rotation_name}" "${BardRunBuff}"                        Song  ${Parse[0,"( ${DoRunSpeed[SETTINGVAL]} && BUFFBRDSPELL )"]}
    /call AddToRotation "${rotation_name}" "${CrescendoSong}"                      Song  ${Parse[0,"( !${Me.GemTimer[${Me.Gem[${CrescendoSong}]}]} && BUFFSONG && ${Me.PctMana}<75 )"]}    
    /call AddToRotation "${rotation_name}" "${PulseRegenSong}"                     Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${ChorusRegenSong}"                    Song ${Parse[0,"( BUFFSONG )"]}    
    /call AddToRotation "${rotation_name}" "${AccelerandoSong}"                    Song ${Parse[0,"( BUFFSONG )"]}     

    | - Down time item clicks
    /call AddToRotation "${rotation_name}" "${FindItem[Spider's Bite].Name}"       Item  ${Parse[1,"( !${Me.Buff[${Spell[${FindItem[Spider's Bite].Spell}]}].ID} && ${Spell[${FindItem[Spider's Bite].Spell}].Stacks} )"]}
    /call AddToRotation "${rotation_name}" "${FindItem[Rapier of Somber Notes]}"   Item  ${Parse[0,"( ${Spell[${FindItem[Rapier of Somber Notes].Spell}].Stacks} && (!${FindItem[Rapier of Somber Notes].TimerReady} ))"]}
    /call AddToRotation "${rotation_name}" "${FindItem[Songblade of the Eternal]}" Item  ${Parse[0,"( ${Spell[${FindItem[Songblade of the Eternal].Spell}].Stacks} && (!${FindItem[Songblade of the Eternal].TimerReady} ))"]}    
/return

Sub BRD_DefaultBurnRotationConfig(string rotation_name)
    /call AddToRotation "${rotation_name}" "Dance of Blades"                AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation "${rotation_name}" "Flurry of Notes"                AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation "${rotation_name}" "Frenzied Kicks"                 AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation "${rotation_name}" "Funeral Dirge"                  AA ${Parse[0,"( ${Target.Named} )"]}  
/return

Sub BRD_DefaultDPSRotationConfig(string rotation_name)

    | #define BUFFSONG "( ${Me.Gem[${mi.Key}]} && ${Float[${Me.Song[${mi.Key}].Duration.Seconds}]} <= ${Math.Calc[${Spell[${Me.Song[${mi.Key}].Name}].MyCastTime.Seconds} + 6]} )"
    | #define BUFFBRDSPELL "( ${Me.Gem[${mi.Key}]} && ${Float[${Me.Buff[${mi.Key}].Duration.Seconds}]} <= ${Math.Calc[${Spell[${mi.Key}].MyCastTime.Seconds} + 6]} )"
    | #define DEBUFFSONG "( ${Me.Gem[${mi.Key}]} && !${Target.Buff[${mi.Key}].ID} )"
    | - Ae mez
|    /call AddToRotation "${rotation_name}" "${MezAESpell}"                  Song ${Parse[0,"( ${DoDpsMez[SETTINGVAL]} && (${XAssist.XTFullHaterCount} >= ${DPSMezAECount[SETTINGVAL]}) )"]}

    |-Aggro Drops
    /call AddToRotation "${rotation_name}" "Fading Memories"                AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]} 
    /call AddToRotation "${rotation_name}" "Hymn of the Last Stand"         AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]} 
    /call AddToRotation "${rotation_name}" "Shield of Notes"                AA ${Parse[0,"( !${SpawnCount[pccorpse ${assistid}]} && ${Me.PctAggro}>90 )"]}
    
    |- Main Tank Dead Stepping in to Keep folks alive.
    /call AddToRotation "${rotation_name}" "Dissonant Chord"                    AA ${Parse[0,"( ${SpawnCount[pccorpse ${assistid}]} )"]}
|    /call AddToRotation "${rotation_name}" "/call BRD_ReflexStrikeManaCheck"    Command ${Parse[0,"( TRUE )"]}
|   /call AddToRotation "${rotation_name}" "/call BRD_ReflexStrikeManaCheck"   Command ${Parse[0,"( ${NPCDiscReady[${ReflexStrike}]} )"]}
    | - DPs AAs'a
    /call AddToRotation "${rotation_name}" "Boastful Bellow"                AA ${Parse[0,"( !${Target.Buff[${Me.AltAbility[Boastful Bellow].ID}].} && ${Target.PctHPs}>90 )"]}
    /call AddToRotation "${rotation_name}" "Song of Stone"                  AA ${Parse[0,"( TRUE )"]} 
    /call AddToRotation "${rotation_name}" "Lyrical Prankster"              AA ${Parse[0,"( TRUE )"]}
    /call AddToRotation "${rotation_name}" "Cacophony"                      AA ${Parse[0,"( ${Target.Named} && DOTSPELLCHECK  )"]}  
    /call AddToRotation "${rotation_name}" "Bladed Song"                    AA ${Parse[0,"( TRUE )"]}     
    /call AddToRotation "${rotation_name}" "Fierce Eye"                     AA ${Parse[0,"( !${Me.Buff[Fierce Eye].ID} )"]} 
    /call AddToRotation "${rotation_name}" "Spire of the Minstrels"         AA ${Parse[0,"( !${Me.Buff[Spire of the Minstrels].ID} )"]} 
    /call AddToRotation "${rotation_name}" "Quick Time"                     AA ${Parse[0,"( ${UseQuicktime[SETTINGVAL]} )"]}     

    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}

    | Bards get it at level 26
    /if (${Me.Level}>=20) {
        /call AddToRotation "${rotation_name}" "Intimidation"                   "Ability" ${Parse[0,"( ${DoIntimidate[SETTINGVAL]} )"]}
    }
    |- Items Map
    /call AddToRotation "${rotation_name}" "${Epic}"                        Item ${Parse[0,"( ${Spell[${FindItem[${Epic}].Spell}].Stacks} && (!${FindItem[${Epic}].TimerReady}) )"]} 
    /call AddToRotation "${rotation_name}" "${FindItem[${Me.Inventory[Chest].Name}]}" Item       ${Parse[0,"( ${DoChestClick[SETTINGVAL]} && ${Spell[${FindItem[${Me.Inventory[Chest].Name}].Spell}].Stacks} && (!${FindItem[${Me.Inventory[Chest].Name}].TimerReady}) )"]}   
    |- Combat Twist
    /call AddToRotation "${rotation_name}" "${AccelerandoSong}"             Song ${Parse[0,"( BUFFSONG )"]}     
    /call AddToRotation "${rotation_name}" "${RecklessSong}"                Song ${Parse[0,"( BUFFSONG )"]}    
    /call AddToRotation "${rotation_name}" "${SlowSong}"                    Song ${Parse[0,"( DEBUFFSONG && !${Target.Slowed.ID} )"]} 
    /call AddToRotation "${rotation_name}" "${AESlowSong}"                  Song ${Parse[0,"( DEBUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${InsultSong1}"                 Song ${Parse[0,"( (${Me.PctMana}>50 && ${Target.PctHPs}>50) )"]}
    /call AddToRotation "${rotation_name}" "${InsultSong2}"                 Song ${Parse[0,"( (${Me.PctMana}>50 && ${Target.PctHPs}>50) )"]}
    /if (${rotation_name.Equal[BRD_DPS_MODEBEAST_Rotation]} || ${BringYourOwnSpells[SETTINGVAL]}) /call AddToRotation "${rotation_name}" "${Dot1Song}" Song ${Parse[0,"( DEBUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${WarMarchSong}"                Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${SufferingSong}"               Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${SprySonataSong}"              Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${MainAriaSong}"                Song ${Parse[0,"( BUFFSONG )"]}     
    /call AddToRotation "${rotation_name}" "${CasterAriaSong}"              Song ${Parse[0,"( BUFFSONG )"]}
    /if (${rotation_name.Equal[BRD_DPS_MODEBEAST_Rotation]} || ${BringYourOwnSpells[SETTINGVAL]}) /call AddToRotation "${rotation_name}" "${Dot2Song}" Song ${Parse[0,"( DEBUFFSONG )"]}    
    /call AddToRotation "${rotation_name}" "${PulseRegenSong}"              Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${ChorusRegenSong}"             Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${ArcaneSong}"                  Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${DichoSong}"                   Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${SpitefulSong}"                Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${FateSong}"                    Song ${Parse[0,"( BUFFSONG )"]}
    /call AddToRotation "${rotation_name}" "${PsalmSong}"                   Song ${Parse[0,"( BUFFSONG )"]}    
/return

Sub BRD_ReflexStrikeManaCheck
/declare Reflextarget int local ${WorstHurtMana[${ReflexManaPct[SETTINGVAL]}]}
/if ( ${NPCDiscReady[${ReflexStrike}]} && ${Reflextarget} ) {
    /call DiscNow "${ReflexStrike}" ${autotargetid}
}

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
        /call BRD_ReflexStrikeManaCheck
    }

/return FALSE







Sub BRD_Downtime_Routine

    |- Check for DPS Aura if we are supposed to be using Regen Aura and Remove it
    /if ( ${Me.Song[${BardDPSAura}].Duration.Seconds} && ${UseRegenAura[SETTINGVAL]} ) /removebuff ${Me.Song[${BardDPSAura}].ID}
    /if ( !${Me.Buff[Selo's Accelerando].ID} && !${Me.Buff[Selo's Accelerato].ID} && ${RG_AAReady[Selo's Sonata]} && ${DoAASelo}) {
        |- Cast Selo's AA if we do not have the buff
        /call AANow 3704 ${Me.ID}
    } 
	|-Apply poison to weapon if enabled
    |- NOTES: Change PoisonName ini 
    |/call FollowRotation BuffItem ${autotargetid} TRUE 
      
    /call FollowRotation BRD_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID} TRUE 1

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