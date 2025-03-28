|- RGberutil.inc
|- Version 2.0
|- Updated: Terror of Luclin Launch Dec 07 2021

#define MODEDPS 0
#define MODENOONE 1
#define MODETLP 2

|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub BER_Setup
    /declare RGList_BER list outer

    |- Rotations
	/call Ordered_Rotation_New BER_DPS_MODENOONE_Rotation
	/call Ordered_Rotation_New BER_Downtime_MODENOONE_Rotation
    /call Ordered_Rotation_New BER_Burn_MODENOONE_Rotation

    /call Ordered_Rotation_New BER_DPS_MODEDPS_Rotation
	/call Ordered_Rotation_New BER_Downtime_MODEDPS_Rotation
    /call Ordered_Rotation_New BER_Burn_MODEDPS_Rotation

    /call Ordered_Rotation_New BER_DPS_MODETLP_Rotation
	/call Ordered_Rotation_New BER_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New BER_Burn_MODETLP_Rotation
|- Items
    /call ItemSet_New Epic

|- Declare AA's and Discs
	/call AbilitySet_New endregen
	/call AbilitySet_New beraura
	/call AbilitySet_New Dicho
	/call AbilitySet_New Dfrenzy
	/call AbilitySet_New Dvolley
	/call AbilitySet_New Daxethrow
	/call AbilitySet_New Daxeof
	/call AbilitySet_New Phantom
	/call AbilitySet_New Alliance
	/call AbilitySet_New CheapShot
	/call AbilitySet_New AESlice
	/call AbilitySet_New AEVicious
	/call AbilitySet_New FrenzyBoost
	/call AbilitySet_New FrenzyBoostBuff
	/call AbilitySet_New RageStrike
	/call AbilitySet_New SharedBuff
	/call AbilitySet_New SharedBuffName
	/call AbilitySet_New PrimaryBurnDisc
	/call AbilitySet_New CleavingDisc
	/call AbilitySet_New CleavingDisc_2
	/call AbilitySet_New FlurryDisc
	/call AbilitySet_New DisconDisc
	/call AbilitySet_New ResolveDisc
	/call AbilitySet_New HHEBuff
    /call AbilitySet_New CryDmg
	/call AbilitySet_New AutoAxe
	/call AbilitySet_New DichoAxe
    /call AbilitySet_New Tendon
    /call AbilitySet_New SappingStrike
    /call AbilitySet_New ReflexDisc
    /call AbilitySet_New RestFrenzy
    /call AbilitySet_New RetaliationDodge
    /call AbilitySet_New TempleStun
    /call AbilitySet_New JarringStrike


    /declare PrimaryBurnDiscID		int outer 0    
    /declare CleavingDiscID			int outer 0
	/declare FlurryDiscID			int outer 0
	/declare ResolveDiscID			int outer 0
	/declare DisconDiscID			int outer 0

    /declare BraxiDebuff            string outer null
	
|- Config Options
	/call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = DPS
    /call RGLoadSetting BER DoBattleLeap 1 Combat "Set 0/1 to use battle leap AA"
    /call RGLoadSetting BER DoAoe 0 Combat "Set 0/1 to use AoE abilities"
    /call RGLoadSetting BER DoIntimidate 0 Combat "Set 0/1 to use the intimidate ability. Default: 0"
    /call RGLoadSetting BER DoOpener 1 Combat "Set 0/1 to use cheap shot opener"
    /call RGLoadSetting BER DoPet 1 Combat "Set 0/1 to Summon BER phantom"
    /call RGLoadSetting BER PoisonName NULL Item "Name of the poison item you will use"
    /call RGLoadSetting BER PoisonBuffName NULL Item "Name of the poison buff that's applied to your weapon"
    /call RGLoadSetting BER DoPoison 0 Item "Set 0/1 to put poison on your axes"
	/call RGLoadSetting BER SummonAxes 1 Options "Sets Whether to AutoSummon Axes or Not"
	/call RGLoadSetting BER SummonAxes2 1 Options "Sets Whether to AutoSummon Secondary Axe or Not"
	/call RGLoadSetting BER SummonDichoAxes 1 Options "Sets Whether to AutoSummon Dicho Axe or Not"
    /call RGLoadSetting BER AutoAxeCount 300 Options "Max quantity of primary axe to summon"
    /call RGLoadSetting BER AutoAxeMin 60 Options "Minimum quantity to start summoning axes [UNUSED]"  
    /call RGLoadSetting BER AutoAxe2Count 300 Options "Max quantity of secondary axe to summon"
    /call RGLoadSetting BER AutoAxe2Min 60 Options "Minimum quantity to start summoning secondary axes [UNUSED]"
    /call RGLoadSetting BER DichoAxeCount 300 Options "Max quantity of dicho axe to summon"
    /call RGLoadSetting BER DichoAxeMin 60 Options "Minimum quantity to start summoning axes [UNUSED]"  
    /call RGLoadSetting BER ChestItemName "${Me.Inventory[17].Name}" Item "Name of your chest item -- defaults to the slot"
    
	/declare AutoAxeComponent  int outer 0
    /declare AutoAxe2Component int outer 0
    /declare DichoAxeComponent int outer 0
	
	/declare ZerkerCount			int outer 1
/return 

|----------------------------------------------------------------------------
|- SUB: Prengage Routine 
|---------------------------------------------------------------------------- 
Sub BER_PreEngageRoutine
  /if (${Me.CombatAbilityReady[${CheapShot}]} && ${Me.PctEndurance}>=5 && ${DoOpener[SETTINGVAL]} && ${Target.Distance}<50) {
    /call DiscNow "${CheapShot}" ${autotargetid}
  }
/return

|----------------------------------------------------------------------------
|- SUB: SetupSkills
|---------------------------------------------------------------------------- 
Sub BER_SetupSkills
|- Items
    /varset BraxiDebuff  ${Me.AltAbility[Braxi's Howl].Spell}

|-- Epic
    /call ItemSet_Add "Vengeful Taelosian Blood Axe" Epic
    /call ItemSet_Add "Raging Taelosian Alloy Axe" Epic
    /call ItemSet_ChooseOuter Epic Epic

|---One off abilities
	/call AbilitySet_Add "Phantom Assailant" Phantom
    /call AbilitySet_ChooseOuter Phantom Phantom
    
|-  Alliance Abilty   
    /call AbilitySet_Add "Demolisher's Alliance" Alliance
    /call AbilitySet_Add "Mangler's Covenant"   Alliance
    /call AbilitySet_Add "Vindicator's Coalition" Alliance
    /call AbilitySet_Add "Conqueror's Conjunction" Alliance
    /call AbilitySet_ChooseOuter Alliance Alliance


|-- Jarring Line - Hate Decreaser 
    /call AbilitySet_Add "Jarring Crash" JarringStrike
    /call AbilitySet_Add "Jarring Strike" JarringStrike
    /call AbilitySet_Add "Jarring Smash" JarringStrike
    /call AbilitySet_Add "Jarring Clash" JarringStrike
    /call AbilitySet_Add "Jarring Slam" JarringStrike
    /call AbilitySet_Add "Jarring Blow" JarringStrike
    /call AbilitySet_Add "Jarring Crush" JarringStrike
    /call AbilitySet_Add "Jarring Smite" JarringStrike
    /call AbilitySet_Add "Jarring Jolt" JarringStrike
    /call AbilitySet_Add "Jarring Shock" JarringStrike
    /call AbilitySet_Add "Jarring Impact" JarringStrike
    /call AbilitySet_ChooseOuter JarringStrike JarringStrike

|- Sapping Strikes
    /call AbilitySet_Add "Sapping Strikes" SappingStrike
    /call AbilitySet_Add "Shriveling Strikes" SappingStrike
    /call AbilitySet_ChooseOuter SappingStrike SappingStrike    

|-- Reflexive Retaliation
    /call AbilitySet_Add "Reflexive Retaliation" ReflexDisc
    /call AbilitySet_Add "Instinctive Retaliation" ReflexDisc
    /call AbilitySet_ChooseOuter ReflexDisc ReflexDisc

|- Retaliation Dodge
    /call AbilitySet_Add "Preemptive Retaliation" RetaliationDodge
    /call AbilitySet_Add "Primed Retaliation"   RetaliationDodge
    /call AbilitySet_Add "Premature Retaltion"  RetaliationDodge
    /call AbilitySet_Add "Proactive Retaliation" RetaliationDodge
    /call AbilitySet_Add "Prior Retaliation"    RetaliationDodge
    /call AbilitySet_Add "Advanced Retaliation"  RetaliationDodge
    /call AbilitySet_Add "Early Retaliation"     RetaliationDodge
    /call AbilitySet_ChooseOuter RetaliationDodge RetaliationDodge

|-- Temple Stun
    /call AbilitySet_Add "Temple Shatter"   TempleStun
    /call AbilitySet_Add "Temple Bash"      TempleStun
    /call AbilitySet_Add "Temple Blow"      TempleStun
    /call AbilitySet_Add "Temple Chop"      TempleStun
    /call AbilitySet_Add "Temple Crack"     TempleStun
    /call AbilitySet_Add "Temple Crush"     TempleStun
    /call AbilitySet_Add "Temple Demolish"  TempleStun
    /call AbilitySet_Add "Temple Shatter"   TempleStun
    /call AbilitySet_Add "Temple Slam"      TempleStun
    /call AbilitySet_Add "Temple Smash"     TempleStun
    /call AbilitySet_Add "Temple Strike"    TempleStun
    /call AbilitySet_ChooseOuter TempleStun TempleStun
    

|---Battle Cry - HHE Buff
    /call AbilitySet_Add "Battle Cry" HHEBuff
    /call AbilitySet_Add "War Cry" HHEBuff
    /call AbilitySet_Add "Battle Cry of Dravel" HHEBuff
    /call AbilitySet_Add "War Cry of Dravel" HHEBuff
    /call AbilitySet_Add "Battle Cry of the Mastruq" HHEBuff
    /call AbilitySet_Add "Ancient: Cry of Chaos" HHEBuff
    /call AbilitySet_ChooseOuter HHEBuff HHEBuff

|---Cry - HHE Buff
    /call AbilitySet_Add "Cry Havoc" CryDmg
    /call AbilitySet_Add "Cry Carnage" CryDmg
    /call AbilitySet_ChooseOuter CryDmg CryDmg

|---Primary Burn Disc Setup - Expanded for lower level use
    /call AbilitySet_Add "Berserking Discipline" PrimaryBurnDisc
    /call AbilitySet_Add "Sundering Discipline" PrimaryBurnDisc
    /call AbilitySet_Add "Brutal Discipline" PrimaryBurnDisc
    /call AbilitySet_ChooseOuter PrimaryBurnDisc PrimaryBurnDisc

|---Cleaving Disc
    /call AbilitySet_Add "Cleaving Rage Discipline" CleavingDisc
    /call AbilitySet_Add "Cleaving Anger Discipline" CleavingDisc
    /call AbilitySet_Add "Cleaving Acrimony Discipline" CleavingDisc
    /call AbilitySet_ChooseOuter CleavingDisc CleavingDisc
    /call AbilitySet_ChooseOuter CleavingDisc_2 CleavingDisc "CleavingDisc"
    
|---Flurry Disc
    /call AbilitySet_Add "Vengeful Flurry Discipline" FlurryDisc
    /call AbilitySet_Add "Avenging Flurry Discipline" FlurryDisc
    /call AbilitySet_ChooseOuter FlurryDisc FlurryDisc

|---Disconcerting
    /call AbilitySet_Add "Disconcerting Discipline" DisconDisc
    /call AbilitySet_ChooseOuter DisconDisc DisconDisc
    
|---Resolve Disc
	/call AbilitySet_Add "Frenzied Resolve Discipline" ResolveDisc
    /call AbilitySet_ChooseOuter ResolveDisc ResolveDisc
    
|---Frenzy Boost - Updated for Tov and Expanded for lower level 124
    /call AbilitySet_Add "Augmented Frenzy" FrenzyBoost
    /call AbilitySet_Add "Amplified Frenzy" FrenzyBoost
    /call AbilitySet_Add "Bolstered Frenzy" FrenzyBoost
    /call AbilitySet_Add "Magnified Frenzy" FrenzyBoost
    /call AbilitySet_Add "Buttressed Frenzy" FrenzyBoost
    /call AbilitySet_Add "Heightened Frenzy" FrenzyBoost
    /call AbilitySet_ChooseOuter FrenzyBoost FrenzyBoost
    
|---SharedBuff - Updated for Tov and Expanded for lower level
    /call AbilitySet_Add "Shared Barbarism" SharedBuff
	/call AbilitySet_Add "Shared Bloodlust" SharedBuff
    /call AbilitySet_Add "Shared Brutality" SharedBuff
    /call AbilitySet_Add "Shared Savagery" SharedBuff
    /call AbilitySet_Add "Shared Viciousness" SharedBuff
    /call AbilitySet_Add "Shared Cruelty" SharedBuff
    /call AbilitySet_Add "Shared Ruthlessness" SharedBuff
    /call AbilitySet_Add "Shared Atavism" SharedBuff
    /call AbilitySet_Add "Shared Violence" SharedBuff
    /call AbilitySet_ChooseOuter SharedBuff SharedBuff
    
|---RageStrike - Updated for RoS and Expanded for lower level
    /call AbilitySet_Add "Roiling Rage" RageStrike
    /call AbilitySet_Add "Festering Rage" RageStrike
    /call AbilitySet_Add "Bubbling Rage" RageStrike
    /call AbilitySet_Add "Smoldering Rage" RageStrike
    /call AbilitySet_Add "Seething Rage" RageStrike
	/call AbilitySet_Add "Frothing Rage" RageStrike
    /call AbilitySet_ChooseOuter RageStrike RageStrike

|---CheapShot ability EX: Kick in the shins - Updated for RoS
    /call AbilitySet_Add "Slap in the Face" CheapShot
    /call AbilitySet_Add "Kick in the Teeth" CheapShot
    /call AbilitySet_Add "Punch in The Throat" CheapShot
    /call AbilitySet_Add "Kick in the Shins" CheapShot
    /call AbilitySet_Add "Sucker Punch" CheapShot
    /call AbilitySet_Add "Rabbit Punch" CheapShot
    /call AbilitySet_Add "Swift Punch" CheapShot
    /call AbilitySet_ChooseOuter CheapShot CheapShot

|- Dicho Disc*
    /call AbilitySet_Add "Dichotomic Rage" Dicho
    /call AbilitySet_Add "Dissident Rage" Dicho
    /call AbilitySet_Add "Composite Rage" Dicho
    /call AbilitySet_Add "Ecliptic Rage" Dicho
    /call AbilitySet_ChooseOuter Dicho Dicho

|-- Restless Frenzy Ability (Level 125)
    /call AbilitySet_Add "Desperate Frenzy" RestFrenzy
    /call AbilitySet_Add "Blinding Frenzy" RestFrenzy
    /call AbilitySet_Add "Restless Frenzy" RestFrenzy 
    /call AbilitySet_ChooseOuter RestFrenzy RestFrenzy

|---Frenzy Combat Ability not normal Frenzy - Updated for RoS
    /call AbilitySet_Add "Eviscerating Frenzy" Dfrenzy
    /call AbilitySet_Add "Heightened Frenzy" Dfrenzy
	/call AbilitySet_Add "Oppressing Frenzy" Dfrenzy
    /call AbilitySet_Add "Overpowering Frenzy" Dfrenzy
    /call AbilitySet_Add "Overwhelming Frenzy" Dfrenzy
    /call AbilitySet_Add "Conquering Frenzy" Dfrenzy
    /call AbilitySet_Add "Vanquishing Frenzy" Dfrenzy
    /call AbilitySet_Add "Demolishing Frenzy" Dfrenzy
    /call AbilitySet_Add "Mangling Frenzy" Dfrenzy
    /call AbilitySet_Add "Vindicating Frenzy" Dfrenzy
    /call AbilitySet_ChooseOuter Dfrenzy Dfrenzy
    
|---Volley - Updated for RoS
	/call AbilitySet_Add "Rage Volley" Dvolley
    /call AbilitySet_Add "Destroyer's Volley" Dvolley
    /call AbilitySet_Add "Annihilator's Volley" Dvolley
    /call AbilitySet_Add "Decimator's Volley" Dvolley
    /call AbilitySet_Add "Eradicator's Volley" Dvolley
    /call AbilitySet_Add "Savage Volley" Dvolley
    /call AbilitySet_Add "Sundering Volley" Dvolley
    /call AbilitySet_Add "Brutal Volley" Dvolley
    /call AbilitySet_Add "Demolishing Volley" Dvolley
    /call AbilitySet_Add "Mangling Volley" Dvolley
    /call AbilitySet_Add "Vindicating Volley" Dvolley
    /call AbilitySet_Add "Pulverizing Volley" Dvolley
    /call AbilitySet_Add "Eviscerating Volley" Dvolley
    /call AbilitySet_ChooseOuter Dvolley Dvolley
    
|---Axe Throw - Updated for RoS
	/call AbilitySet_Add "Maiming Axe Throw" Daxethrow
    /call AbilitySet_Add "Vigorous Axe Throw" Daxethrow
    /call AbilitySet_Add "Energetic Axe Throw" Daxethrow
    /call AbilitySet_Add "Spirited Axe Throw" Daxethrow
    /call AbilitySet_Add "Brutal Axe Throw" Daxethrow
    /call AbilitySet_Add "Demolishing Axe Throw" Daxethrow
    /call AbilitySet_Add "Mangling Axe Throw" Daxethrow
    /call AbilitySet_Add "Vindicating Axe Throw" Daxethrow
    /call AbilitySet_Add "Rending Axe Throw" Daxethrow
    /call AbilitySet_ChooseOuter Daxethrow Daxethrow
    
|---Axe of  - Update but changed level - 
    /call AbilitySet_Add "Axe of Rallos" Daxeof
    /call AbilitySet_Add "Axe of Graster" Daxeof
    /call AbilitySet_Add "Axe of Illdaera" Daxeof
    /call AbilitySet_Add "Axe of Zurel" Daxeof
    /call AbilitySet_Add "Axe of the Aeons" Daxeof
    /call AbilitySet_Add "Axe of Empyr" Daxeof
    /call AbilitySet_Add "Axe of Derakor" Daxeof
    /call AbilitySet_Add "Axe of Xin Diabo" Daxeof
    /call AbilitySet_Add "Axe of Orrak" Daxeof
    /call AbilitySet_ChooseOuter Daxeof Daxeof
        
|---AE Slice Attack - 4 targets or less DIRECTIONAL Range 40
	/call AbilitySet_Add "Arcblade" AESlice
    /call AbilitySet_Add "Arcslice" AESlice
    /call AbilitySet_Add "Arcsteel" AESlice
    /call AbilitySet_Add "Arcslash" AESlice
    /call AbilitySet_Add "Arcshear" AESlice
    /call AbilitySet_ChooseOuter AESlice AESlice
    
|---AE Viscious Attack - Up to 12 targets Range 25
	/call AbilitySet_Add "Vicious Spiral" AEVicious
    /call AbilitySet_Add "Vicious Cyclone" AEVicious
    /call AbilitySet_Add "Vicious Cycle" AEVicious
    /call AbilitySet_Add "Vicious Revolution" AEVicious
    /call AbilitySet_Add "Vicious Whirl" AEVicious
    /call AbilitySet_ChooseOuter AEVicious AEVicious
    
|---Fast Endurance regen 
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
    /call AbilitySet_Add "Convalesce" endregen
    /call AbilitySet_ChooseOuter endregen endregen

|- Aura Set up	
    /call AbilitySet_Add "Aura of Rage" beraura
    /call AbilitySet_Add "Bloodlust Aura" beraura
    /call AbilitySet_ChooseOuter beraura beraura

|- Tendon Slice Ability
    /call AbilitySet_Add "Tendon Slice" Tendon
    /call AbilitySet_Add "Tendon Shred" Tendon
    /call AbilitySet_Add "Tendon Cleave" Tendon
    /call AbilitySet_Add "Tendon Sever" Tendon
    /call AbilitySet_Add "Tendon Shear" Tendon
    /call AbilitySet_Add "Tendon Lacerate" Tendon
    /call AbilitySet_Add "Tendon Slash" Tendon
    /call AbilitySet_Add "Tendon Gash" Tendon
    /call AbilitySet_Add "Tendon Tear" Tendon
    /call AbilitySet_Add "Tendon Rupture" Tendon
    /call AbilitySet_Add "Tendon Rip" Tendon
    /call AbilitySet_ChooseOuter Tendon Tendon   

|- AutoAxe Setup
	/call AbilitySet_Add "Corroded Axe" AutoAxe
	/call AbilitySet_Add "Blunt Axe" AutoAxe
	/call AbilitySet_Add "Steel Axe" AutoAxe
	/call AbilitySet_Add "Bearded Axe" AutoAxe
	/call AbilitySet_Add "Mithril Axe" AutoAxe
	/call AbilitySet_Add "Balanced War Axe" AutoAxe
	/call AbilitySet_Add "Bonesplicer Axe" AutoAxe
	/call AbilitySet_Add "Fleshtear Axe" AutoAxe
	/call AbilitySet_Add "Cold Steel Cleaving Axe" AutoAxe
	/call AbilitySet_Add "Mithril Bloodaxe" AutoAxe
	/call AbilitySet_Add "Rage Axe" AutoAxe
	/call AbilitySet_Add "Bloodseeker's Axe" AutoAxe
	/call AbilitySet_Add "Battlerage Axe" AutoAxe
	/call AbilitySet_Add "Deathfury Axe" AutoAxe
	/call AbilitySet_Add "Tainted Axe of Hatred" AutoAxe
	/call AbilitySet_Add "Axe of The Destroyer" AutoAxe
	/call AbilitySet_Add "Axe of The Annihilator" AutoAxe
	/call AbilitySet_Add "Axe of The Decimator" AutoAxe
	/call AbilitySet_Add "Axe of The Eradicator" AutoAxe
	/call AbilitySet_Add "Axe of The Savage" AutoAxe
	/call AbilitySet_Add "Axe of the Sunderer" AutoAxe
	/call AbilitySet_Add "Axe of The Brute" AutoAxe
	/call AbilitySet_Add "Axe of The Demolisher" AutoAxe
	/call AbilitySet_Add "Axe of The Mangler" AutoAxe
	/call AbilitySet_Add "Axe of The Vindicator" AutoAxe
    /call AbilitySet_Add "Axe of the Conqueror" AutoAxe
    /call AbilitySet_Add "Axe of the Eviscerator" AutoAxe
	/call AbilitySet_ChooseOuter AutoAxe1 AutoAxe
    /call AbilitySet_ChooseOuter AutoAxe2 AutoAxe "${AutoAxe1}"

	/varset AutoAxeComponent ${Spell[${AutoAxe1}].ReagentID[1]}
    /varset AutoAxe2Component ${Spell[${AutoAxe2}].ReagentID[1]}

|- DichoAxe Setup
	/call AbilitySet_Add "Axe of The Demolisher" DichoAxe
	/call AbilitySet_Add "Axe of The Mangler" DichoAxe
	/call AbilitySet_Add "Axe of the Conqueror" DichoAxe
    /call AbilitySet_ChooseOuter DichoAxe DichoAxe

    /varset DichoAxeComponent ${Spell[${Dicho}].ReagentID[1]}
    
/return

Sub BER_ModeConfigMODEDPS
    |- Rotations
    |- Self Buffs
    /call BER_DefaultSelfBuffRotationConfig BER_Downtime_MODEDPS_Rotation
    
    |- DPS Rotations
 |  Frenzy, Vindicating Frenzy, Vindicating Volley, Axe of Derakor, Vindicating Axe Throw, Shared Atavism, Seething Rage, Phantom Assailant, Sapping Strikes, Binding Axe, Intimidation, War Cry of Braxi, Dissident Rage, and Arcsteel
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${Epic}"          "Item" ${Parse[0,"( ${DoEpic[SETTINGVAL]} && ${Spell[${FindItem[${Epic}].Spell}].Stacks} && (${FindItem[${Epic}].TimerReady} == 0) )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "Battle Leap"      "AA" ${Parse[0,"( !${Me.Song[Battle Leap Warcry].ID} && !${Me.Song[Group Bestial Alignment].ID} && ${DoBattleLeap[SETTINGVAL]} )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "Frenzy"           "Ability" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${Dfrenzy}"       "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${Dvolley}"       "Disc" ${Parse[0,"( ( ${Spell[${Dvolley}].NoExpendReagentID[1]} == -1 || ${FindItemCount[${Spell[${Dvolley}].NoExpendReagentID[1]}]} > 0 ) && ${PCDiscReady[${Dvolley}]} )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${Daxeof}"        "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${Daxethrow}"     "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${SharedBuff}"    "Disc" ${Parse[0,"( !${Me.Song[${SharedBuff}].ID} )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${RageStrike}"    "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${Phantom}"       "Disc" ${Parse[0,"( ${DoPet[SETTINGVAL]} )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${SappingStrike}" "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "Binding Axe"      "AA"   ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "Intimidation"     "Ability" ${Parse[0,"( ${DoIntimidate[SETTINGVAL]} )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${AESlice}"       "Disc" ${Parse[0,"( ${DoAoe[SETTINGVAL]} || ${SpawnCount[npc radius 60 playerstate 4]} == 1 )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${Alliance}"      "Disc" ${Parse[0,"( !${Target.Buff[${Spell[${Alliance}].ID}]} && ${DoAlliance[SETTINGVAL]} && ${CanAlliance} )"]} 
    | Should be tied together so You Only use Dicho right after you cast braxis Howl.
    /call AddToRotation BER_DPS_MODEDPS_Rotation "/call BER_BraxiChain" Command ${Parse[0,"( ${PCAAReady[Braxi's Howl]} )"]}
    |- Not spammable attacks But they do have a Buff Usecase for most or a Use to lower life to allow another to function.
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${DisconDisc}"    "Disc" ${Parse[0,"( !${Me.ActiveDisc.ID} )"]}  
    /call AddToRotation BER_DPS_MODEDPS_Rotation "Bloodfury"        "AA" ${Parse[0,"( ${PCDiscReady[${FrenzyBoost}]} && ${Me.PctHPs}>=90 )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${FrenzyBoost}"   "Disc" ${Parse[0,"( !${Me.Buff[${FrenzyBoost}].ID} )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${CryDmg}"        "Disc" ${Parse[0,"( !${Me.Song[${CryDmg}].ID} )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "Drawn to Blood"   "AA" ${Parse[0,"( ${Target.Distance} > 15 )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "Communion of Blood"   "AA" ${Parse[0,"( ${Me.PctEndurance} <= 75 )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "${Spell[Reflexive Retaliation].RankName}" "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODEDPS_Rotation "Intimidation" "Ability" ${Parse[0,"( ${DoIntimidate[SETTINGVAL]} )"]}
    
    |- Burn Rotations    
    | - Main Burn
    /call AddToRotation BER_Burn_MODEDPS_Rotation "${PrimaryBurnDisc}"                   "Disc" ${Parse[0,"( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Savage Spirit"                        "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Juggernaut Surge"                     "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Blood Pact"                           "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Blinding Fury"                        "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Silent Strikes"                       "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Spire of the Juggernaut"              "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Desperation"                          "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Focused Furious Rampage"              "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Untamed Rage"                         "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Cohort's Warmonger Coat"              "Item" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} && ${FindItemCount[=Cohort's Warmonger Coat]} > 0)"]}
    | - Secondary Burn
    /call AddToRotation BER_Burn_MODEDPS_Rotation "${CleavingDisc}"                      "Disc" ${Parse[0,"( ( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} ) && !${PCDiscReady[${PrimaryBurnDisc}]} )"]}  
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Reckless Abandon"                     "AA"  ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${CleavingDisc}]} )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "Vehement Rage"                        "AA"  ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${CleavingDisc}]} )"]} 
    /call AddToRotation BER_Burn_MODEDPS_Rotation "${ResolveDisc}"                       "Disc" ${Parse[0,"( ( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} ) && !${PCDiscReady[${PrimaryBurnDisc}]} && !${PCDiscReady[${CleavingDisc}]}  )"]}
    /call AddToRotation BER_Burn_MODEDPS_Rotation "${FlurryDisc}"                        "Disc" ${Parse[0,"( ( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} ) && !${PCDiscReady[${PrimaryBurnDisc}]} &&  !${PCDiscReady[${CleavingDisc}]} && !${PCDiscReady[${ResolveDisc}]} )"]}
/return

Sub BER_ModeConfigMODENOONE
    |- Rotations
    |- Self Buffs
    /call BER_DefaultSelfBuffRotationConfig BER_Downtime_MODENOONE_Rotation

    |- DPS Rotation
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${Epic}"          "Item" ${Parse[0,"( ${DoEpic[SETTINGVAL]} && ${Spell[${FindItem[${Epic}].Spell}].Stacks} && (${FindItem[${Epic}].TimerReady} == 0) )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${SharedBuff}"    "Disc" ${Parse[0,"( !${Me.Song[${SharedBuff}].ID} )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${CryDmg}"        "Disc" ${Parse[0,"( !${Me.Song[${CryDmg}].ID} )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${DisconDisc}"    "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "Bloodfury"        "AA" ${Parse[0,"( ${PCDiscReady[${FrenzyBoost}]} && ${Me.PctHPs}>=90 )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${FrenzyBoost}"   "Disc" ${Parse[0,"( !${Me.Buff[${FrenzyBoost}].ID} && ${Me.PctHPs}<90 )"]}
   | Should be tied together so You Only use Dicho right after you cast braxis Howl.
    /call AddToRotation BER_DPS_MODENOONE_Rotation "/call BER_BraxiChain" Command ${Parse[0,"( ${PCAAReady[Braxi's Howl]} )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "Battle Leap"      "AA" ${Parse[0,"( !${Me.Song[Battle Leap Warcry].ID} && !${Me.Song[Group Bestial Alignment].ID} && ${DoBattleLeap[SETTINGVAL]} )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${SappingStrike}" "Disc" ${Parse[0,"( ${Me.PctEndurance} <= 90 )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "Frenzy"           "Ability" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${Dfrenzy}"       "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${Dvolley}"       "Disc" ${Parse[0,"( ( ${Spell[${Dvolley}].NoExpendReagentID[1]} == -1 || ${FindItemCount[${Spell[${Dvolley}].NoExpendReagentID[1]}]} > 0 ) && ${PCDiscReady[${Dvolley}]} )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${Daxeof}"        "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${Daxethrow}"     "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${RageStrike}"    "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODENOONE_Rotation "${Phantom}"       "Disc" ${Parse[0,"( ${DoPet[SETTINGVAL]} )"]}


    |- Main Burn Rotation
    /call AddToRotation BER_Burn_MODENOONE_Rotation "Desperation"                          "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "Blood Pact"                           "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "Spire of the Juggernaut"              "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "${ChestItemName[SETTINGVAL]}"         Item ${Parse[1,"( ${DoChestClick[SETTINGVAL]} && ${Spell[${FindItem[${ChestItemName[SETTINGVAL]}].Spell}].Stacks} && (${FindItem[${ChestItemName[SETTINGVAL]}].TimerReady} == 0) )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "${ResolveDisc}"                       "Disc" ${Parse[0,"( ( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} ) && !${PCDiscReady[${PrimaryBurnDisc}]} && !${PCDiscReady[${CleavingDisc}]}  )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "Savage Spirit"                        "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "Reckless Abandon"                     "AA"  ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${CleavingDisc}]} )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "Focused Furious Rampage"              "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "Juggernaut Surge"                     "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "Silent Strikes"                       "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    |- Secondary Burn Rotation
    /call AddToRotation BER_Burn_MODENOONE_Rotation "Blinding Fury"                        "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "${PrimaryBurnDisc}"                   "Disc" ${Parse[0,"( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "${CleavingDisc}"                      "Disc" ${Parse[0,"( ( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} ) && !${PCDiscReady[${PrimaryBurnDisc}]} )"]}  
    /call AddToRotation BER_Burn_MODENOONE_Rotation "${ResolveDisc}"                       "Disc" ${Parse[0,"( ( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} ) && !${PCDiscReady[${PrimaryBurnDisc}]} && !${PCDiscReady[${CleavingDisc}]}  )"]}
    /call AddToRotation BER_Burn_MODENOONE_Rotation "${FlurryDisc}"                        "Disc" ${Parse[0,"( ( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} ) && !${PCDiscReady[${PrimaryBurnDisc}]} &&  !${PCDiscReady[${CleavingDisc}]} && !${PCDiscReady[${ResolveDisc}]} )"]}

/return

Sub BER_ModeConfigMODETLP
    |- Rotations
    |- Self Buffs
    /call BER_DefaultSelfBuffRotationConfig BER_Downtime_MODETLP_Rotation
    
    |- DPS Rotations
 |  Frenzy, Vindicating Frenzy, Vindicating Volley, Axe of Derakor, Vindicating Axe Throw, Shared Atavism, Seething Rage, Phantom Assailant, Sapping Strikes, Binding Axe, Intimidation, War Cry of Braxi, Dissident Rage, and Arcsteel
    /call AddToRotation BER_DPS_MODETLP_Rotation "${Epic}"          		     "Item" ${Parse[0,"( ${DoEpic[SETTINGVAL]} && ${Spell[${FindItem[${Epic}].Spell}].Stacks} && ${FindItem[${Epic}].TimerReady} == 0 )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "Frenzy"           "Ability" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${Dfrenzy}"       "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${Dvolley}"       "Disc" ${Parse[0,"( ( ${Spell[${Dvolley}].NoExpendReagentID[1]} == -1 || ${FindItemCount[${Spell[${Dvolley}].NoExpendReagentID[1]}]} > 0 ) && ${PCDiscReady[${Dvolley}]} )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${Daxeof}"        "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${Daxethrow}"     "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${SharedBuff}"    "Disc" ${Parse[0,"( !${Me.Song[${SharedBuff}].ID} )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${RageStrike}"    "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${Phantom}"       "Disc" ${Parse[0,"( ${DoPet[SETTINGVAL]} )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${SappingStrike}" "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "Binding Axe"      "AA"   ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "Intimidation"     "Ability" ${Parse[0,"( ${DoIntimidate[SETTINGVAL]} )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${AESlice}"       "Disc" ${Parse[0,"( ${DoAoe[SETTINGVAL]} || ${SpawnCount[npc radius 60 playerstate 4]} == 1 )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${Alliance}"      "AA" ${Parse[0,"( !${Target.Buff[${Spell[${Alliance}].ID}]} && ${DoAlliance[SETTINGVAL]} && ${CanAlliance} )"]} 
    | Should be tied together so You Only use Dicho right after you cast braxis Howl.
    /call AddToRotation BER_DPS_MODETLP_Rotation "/call BER_BraxiChain" Command ${Parse[0,"( ${PCAAReady[Braxi's Howl]} )"]}
    |- Not spammable attacks But they do have a Buff Usecase for most or a Use to lower life to allow another to function.
    /call AddToRotation BER_DPS_MODETLP_Rotation "${DisconDisc}"    "Disc" ${Parse[0,"( TRUE )"]}  
    /call AddToRotation BER_DPS_MODETLP_Rotation "Bloodfury"        "AA" ${Parse[0,"( ${PCDiscReady[${FrenzyBoost}]} && ${Me.PctHPs}>=90 )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${FrenzyBoost}"   "Disc" ${Parse[0,"( !${Me.Buff[${FrenzyBoost}].ID} )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${CryDmg}"        "Disc" ${Parse[0,"( !${Me.Song[${CryDmg}].ID} )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "Drawn to Blood"   "AA" ${Parse[0,"( ${Target.Distance} > 15 )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "Communion of Blood"   "AA" ${Parse[0,"( ${Me.PctEndurance} <= 75 )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "${Spell[Reflexive Retaliation].RankName}" "Disc" ${Parse[0,"( TRUE )"]}
    /call AddToRotation BER_DPS_MODETLP_Rotation "Intimidation" "Ability" ${Parse[0,"( ${DoIntimidate[SETTINGVAL]} )"]}
    
    |- Burn Rotations    
    | - Main Burn
    /if (!${Me.HaveExpansion[Dragons of Norrath]} && ${Me.HaveExpansion[Omens of War]}) {
        /call AddToRotation BER_Burn_MODETLP_Rotation "Untamed Rage"                 "AA" ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && !${Me.ActiveDisc.ID} && ${RG_AAReady[Untamed Rage]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "Savage Spirit"                "AA" ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && !${Me.ActiveDisc.ID}  && ${RG_AAReady[Savage Spirit]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "Desperation"                  "AA" ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && !!${Me.ActiveDisc.ID} && ${RG_AAReady[Desperation]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "Blood Pact"                   "AA" ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && !${Me.ActiveDisc.ID} && ${RG_AAReady[Blood Pact]})"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "${FlurryDisc}"                "Disc" ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && !${Me.ActiveDisc.ID} && ${Me.CombatAbilityReady[${FlurryDisc}]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "${HHEBuff}"       		 "Disc" ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && !${Me.ActiveDisc.ID} && ${Me.CombatAbilityReady[${HHEBuff}]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "${CleavingDisc}"              "Disc" ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || MEDBURN ) && !${Me.ActiveDisc.ID} && ${Me.CombatAbilityReady[${CleavingDisc}]} )"]}  
        /call AddToRotation BER_Burn_MODETLP_Rotation "${CleavingDisc_2}"            "Disc" ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && !${Me.ActiveDisc.ID} && ${Me.CombatAbilityReady[${CleavingDisc_2}]} )"]}  
        /call AddToRotation BER_Burn_MODETLP_Rotation "Cohort's Warmonger Coat"      "Item" ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${FindItemCount[=Cohort's Warmonger Coat]} > 0 )"]}
    } else {
        |- Main Burn Rotation
        /call AddToRotation BER_Burn_MODETLP_Rotation "Desperation"                          "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "Blood Pact"                           "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "Spire of the Juggernaut"              "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "${ChestItemName[SETTINGVAL]}"         Item ${Parse[1,"( ${DoChestClick[SETTINGVAL]} && ${Spell[${FindItem[${ChestItemName[SETTINGVAL]}].Spell}].Stacks} && (${FindItem[${ChestItemName[SETTINGVAL]}].TimerReady} == 0) )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "${ResolveDisc}"                       "Disc" ${Parse[0,"( ( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} ) && !${PCDiscReady[${PrimaryBurnDisc}]} && !${PCDiscReady[${CleavingDisc}]}  )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "Savage Spirit"                        "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "Reckless Abandon"                     "AA"  ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${CleavingDisc}]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "Focused Furious Rampage"              "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "Juggernaut Surge"                     "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "Silent Strikes"                       "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
        |- Secondary Burn Rotation
        /call AddToRotation BER_Burn_MODETLP_Rotation "Blinding Fury"                        "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Equal[${PrimaryBurnDisc}]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "${PrimaryBurnDisc}"                   "Disc" ${Parse[0,"( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "${CleavingDisc}"                      "Disc" ${Parse[0,"( ( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} ) && !${PCDiscReady[${PrimaryBurnDisc}]} )"]}  
        /call AddToRotation BER_Burn_MODETLP_Rotation "${ResolveDisc}"                       "Disc" ${Parse[0,"( ( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} ) && !${PCDiscReady[${PrimaryBurnDisc}]} && !${PCDiscReady[${CleavingDisc}]}  )"]}
        /call AddToRotation BER_Burn_MODETLP_Rotation "${FlurryDisc}"                        "Disc" ${Parse[0,"( ( !${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${DisconDisc}]} ) && !${PCDiscReady[${PrimaryBurnDisc}]} &&  !${PCDiscReady[${CleavingDisc}]} && !${PCDiscReady[${ResolveDisc}]} )"]}
	}

/return

Sub BER_DefaultSelfBuffRotationConfig(string rotation_name)
    | - Axes first to avoid issues with TLP 
    /call AddToRotation "${rotation_name}" "/call BER_SummonAutoAxe1"   "Command" ${Parse[0,"( ${SummonAxes[SETTINGVAL]} )"]}
    /call AddToRotation "${rotation_name}" "/call BER_SummonAutoAxe2"   "Command" ${Parse[0,"( ${SummonAxes2[SETTINGVAL]} )"]}
    /call AddToRotation "${rotation_name}" "/call BER_SummonDichoAxe"   "Command" ${Parse[0,"( ${SummonDichoAxes[SETTINGVAL]} )"]}
    /call AddToRotation "${rotation_name}" "Communion of Blood"         "AA" ${Parse[0,"( ${RG_AAReady[Communion of Blood]} && ${Me.PctEndurance}<=75 && ${Me.PctHPs}>=50 && ${Me.MaxHPs}>50000 && !${Me.Song[${endregen}].ID} && !${Me.Moving} && !${Me.Invis} )"]}
    /call AddToRotation "${rotation_name}" "${endregen}"                "Disc" ${Parse[0,"( ${Me.CombatAbilityReady[${endregen}]} && ${Me.PctEndurance}<21 && ${Me.Endurance}>313 && ${Me.CombatAbilityReady[${endregen}]} && !${Me.CombatState.Equal[combat]} && !${Me.Invis} )"]}
    /call AddToRotation "${rotation_name}" "${beraura}"                 "Disc" ${Parse[0,"( !${Spell[${Me.Aura[1]}].ID} && ${Me.CombatAbility[${Spell[${beraura}].RankName}]} && ${Me.PctEndurance}>10 )"]}
    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}"   "Item"  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount"                  "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
/return



Sub BER_Combat_Routine
    /if (${Target.AggroHolder.ID}==${Me.ID} && ${Me.PctAggro}>90 && (${Target.PctHPs}>20 || ${Target.Named}) && ${Target.Level}>=105 && ${RG_AAReady[Uncanny Resilience]}) {
		/echo Looks like I'm Tanking, GL!
		/call AANow ${Me.AltAbility[Uncanny Resilience].ID}
	}

    /if ( DODPS ) {
        |-- Burn Routine Moved above dps so it parses first in the event want to burn.
        |-- Add this back in when I get burn to loc into rotation
        |-  && (!${Me.ActiveDisc.ID} || ${Me.ActiveDisc.Name.Equal[${Spell[Disconcerting Discipline].RankName}]}) 
        /if ( BURNCHECK ) {
            /call Ordered_Rotation_Follow BER_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE TRUE
        }

        /call Ordered_Rotation_Follow BER_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE TRUE
    }
/return FALSE

Sub BER_Downtime_Routine
    /call FollowRotation BER_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID} TRUE 1
    | Use Poison control    
    /if (${DoPoison[SETTINGVAL]} && ${FindItem[${PoisonName[SETTINGVAL]}].ID} && ${Me.ItemReady[${PoisonName[SETTINGVAL]}]} && !${Me.Buff[${PoisonBuffName[SETTINGVAL]}].ID}) {
        /call ItemNow "${PoisonName[SETTINGVAL]}"
    } else /if (${DoPoison[SETTINGVAL]} && !${FindItem[${PoisonName[SETTINGVAL]}].ID}) {
        /echo \awNo Poison Found in Inventory - \arDisabling
        /varset DoPoison[SETTINGVAL] 0
    }
/return FALSE

Sub BER_PullSetup
    /if (${Tendon.NotEqual[NULL]}) {
        /call Pull_SetAbility "${Tendon}" "Disc"
    } else /if ( (${FindItemCount[${AutoAxe1}]} > 0 || ${FindItemCount[${AutoAxe2}]} > 0) && ${Me.Inventory[ammo].Stack} > 5) {
        /call Pull_SetAbility "pullrange" "Special"
    } else {     
        /call Pull_SetAbility "Throw Stone" "Disc"
    }
/return
|- Braxi WarHowl Chain Sub
|- This sub is used to always Use Braxi's Howl with your Dicho so they remain on the same timer.
Sub BER_BraxiChain
    /if (${PCAAReady[Braxi's Howl]}) {
        /call AANow ${AltAbility[Braxi's Howl].ID} ${autotargetid}
        /call DiscNow "${Dicho}" ${autotargetid}
    } else {
        /return
    }
/return

|- Sumnmon Autoaxe Routines
Sub BER_SummonAutoAxe1
    /if (!${PCDiscReady[${AutoAxe1}]}) /return
    /if (${FindItemCount[${AutoAxe1}]} > ${AutoAxeCount[SETTINGVAL]}) /return
    /if (${AutoAxeCount[SETTINGVAL]} == 0) /return
    /if (${FindItemCount[${AutoAxeComponent}]} == 0) /return

    /call DiscNow "${AutoAxe1}"

    /autoinventory
/return

Sub BER_SummonAutoAxe2
    /if (!${PCDiscReady[${AutoAxe2}]}) /return
    /if (${FindItemCount[${AutoAxe2}]} > ${AutoAxe2Count[SETTINGVAL]}) /return
    /if (${AutoAxe2Count[SETTINGVAL]} == 0) /return
    /if (${FindItemCount[${AutoAxe2Component}]} == 0) /return

    /call DiscNow "${AutoAxe2}"

    /autoinventory
/return

Sub BER_SummonDichoAxe
    /if (!${PCDiscReady[${DichoAxe}]}) /return
    /if (${FindItemCount[${DichoAxe}]} > ${DichoAxeCount[SETTINGVAL]}) /return
    /if (${DichoAxeCount[SETTINGVAL]} == 0) /return
    /if (${FindItemCount[${DichoAxeComponent}]} == 0) /return

    /call DiscNow "${DichoAxe}"

    /autoinventory
/return
