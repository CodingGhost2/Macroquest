|- RGmnkutil.inc
|- Version 2.0
|- Updated: 4/25/2019

#define MODEDPS 0
#define MODETLP 2

|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub MNK_Setup
    /declare RGList_MNK            list outer 
    | - Live Rotations
    /call Ordered_Rotation_New MNK_DPS_MODEDPS_Rotation
    /call Ordered_Rotation_New MNK_Burn_MODEDPS_Rotation
    /call Ordered_Rotation_New MNK_Downtime_MODEDPS_Rotation
    | - TLP Rotations
    /call Ordered_Rotation_New MNK_DPS_MODETLP_Rotation
    /call Ordered_Rotation_New MNK_Burn_MODETLP_Rotation
    /call Ordered_Rotation_New MNK_Downtime_MODETLP_Rotation
    |- Items
    /call ItemSet_New Epic    

|-Declare AA's and Discs
	/call AbilitySet_New endregen				
	/call AbilitySet_New MonkAura AURA
    /declare MonkAura_Name string outer				
	/call AbilitySet_New DichoSpell			
	/call AbilitySet_New Drunken				
	/call AbilitySet_New Curse					
	/call AbilitySet_New Fang					
	/call AbilitySet_New Fists
    /call AbilitySet_New Precision					
	/call AbilitySet_New Precision1
    /call AbilitySet_New Precision2
    /call AbilitySet_New Precision3				
	/call AbilitySet_New Shuriken				
	/call AbilitySet_New CraneStance					
	/call AbilitySet_New Synergy				
	/call AbilitySet_New Alliance				
	/call AbilitySet_New Storm
    /call AbilitySet_New Breaths
    /call AbilitySet_New FistsWu    

|-Defensives
	/call AbilitySet_New EarthForce				
	/call AbilitySet_New ShadedStep				
	/call AbilitySet_New RejectDeath
    /call AbilitySet_New Dodgebody    

| - Monk Mez
    /call AbilitySet_New MezSpell
|-Declare Main discs
	/call AbilitySet_New Iron					
	/call AbilitySet_New Heel					
	/call AbilitySet_New Speed					
	/call AbilitySet_New Palm					
	/call AbilitySet_New Poise 					

|-Config Options
	/call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = DPS SET 2 = TLP
    /call RGLoadSetting MNK DoIntimidate 0 Combat "Set 0/1 to use Intimidate abliities. Default: 0."
 /return   

|----------------------------------------------------------------------------
|- SUB: SetupDiscs
|---------------------------------------------------------------------------- 
Sub MNK_SetupSkills
|- Items
|- Epic
    /call ItemSet_Add "Transcended Fistwraps of Immortality" Epic
    /call ItemSet_Add "Fistwraps of Celestial Discipline" Epic
    /call ItemSet_ChooseOuter Epic Epic

|--Delay Death line
	/call AbilitySet_Add "Repeal Death" RejectDeath
    /call AbilitySet_Add "Delay Death" RejectDeath
    /call AbilitySet_Add "Defer Death" RejectDeath
    /call AbilitySet_Add "Deny Death" RejectDeath
    /call AbilitySet_Add "Decry Death" RejectDeath
    /call AbilitySet_Add "Forestall Death" RejectDeath
    /call AbilitySet_Add "Refuse Death" RejectDeath
    /call AbilitySet_Add "Reject Death" RejectDeath
    /call AbilitySet_Add "Rescind Death" RejectDeath
    /call AbilitySet_Add "Defy Death" RejectDeath
    /call AbilitySet_ChooseOuter RejectDeath RejectDeath
   
|--EarthForce line - melee Mitigation  Disc
	/call AbilitySet_Add "Earthwalk Discipline" EarthForce
    /call AbilitySet_Add "EarthForce Discipline" EarthForce
    /call AbilitySet_ChooseOuter EarthForce EarthForce

|--ShadedStep line Dodge Bonus 18 Seconds
	/call AbilitySet_Add "Void Step" ShadedStep
    /call AbilitySet_Add "Shaded Step" ShadedStep
    /call AbilitySet_ChooseOuter ShadedStep ShadedStep

|- Veiled Body Line 
    /call AbilitySet_Add "Void Body" Dodgebody
    /call AbilitySet_Add "Veiled Body" Dodgebody
    /call AbilitySet_ChooseOuter Dodgebody Dodgebody
    
|---Strom line
	/call AbilitySet_Add "Eye of the Storm" Storm
    /call AbilitySet_ChooseOuter Storm Storm

|---Alliance line - Alternates expansions
    /call AbilitySet_Add "Doomwalker's Alliance" Alliance
    /call AbilitySet_Add "Firewalker's Covenant" Alliance 
    /call AbilitySet_Add "Icewalker's Coalition" Alliance | COV
    /call AbilitySet_Add "Bloodwalker's Conjunction" Alliance | NOS 
    /call AbilitySet_ChooseOuter Alliance Alliance

|---Synergy Line
    /call AbilitySet_Add "Fatewalker's Synergy" Synergy | LS 125
    /call AbilitySet_Add "Bloodwalker's Synergy" Synergy | TOL 120
    /call AbilitySet_Add "Calanin's Synergy" Synergy
    /call AbilitySet_Add "Dreamwalker's Synergy" Synergy
    /call AbilitySet_Add "Veilwalker's Synergy" Synergy
    /call AbilitySet_Add "Shadewalker's Synergy" Synergy
    /call AbilitySet_Add "Doomwalker's Synergy" Synergy
    /call AbilitySet_Add "Firewalker's Synergy" Synergy
    /call AbilitySet_Add "Icewalker's Synergy" Synergy
    /call AbilitySet_ChooseOuter Synergy Synergy

|---DM Line - * No Followup
    /call AbilitySet_Add "Drunken Monkey Style" Drunken
    /call AbilitySet_ChooseOuter Drunken Drunken

|---Curse Line - Alternating expansions Nos
	/call AbilitySet_Add "Curse of the Thirteen Fingers" Curse |103 TBM
    /call AbilitySet_Add "Curse of Fourteen Fists" Curse | 108 TBM
    /call AbilitySet_Add "Curse of Fifteen Strikes" Curse | 113 COV
    /call AbilitySet_Add "Curse of Sixteen Shadows" Curse | 118 NOS
    /call AbilitySet_ChooseOuter Curse Curse

|---Fang Line
	/call AbilitySet_Add "Dragon Fang" Fang
    /call AbilitySet_Add "Zalikor's Fang" Fang
    /call AbilitySet_Add "Hoshkar's Fang" Fang
    /call AbilitySet_Add "Zlexak's Fang" Fang
    /call AbilitySet_Add " Uncia's Fang" Fang
    /call AbilitySet_ChooseOuter Fang Fang

|---Fists Line
    /call AbilitySet_Add "Buffeting of Fists" Fists
    /call AbilitySet_Add "Wheel of Fists" Fists
	/call AbilitySet_Add "Whorl of Fists" Fists
	/call AbilitySet_Add "Torrent of Fists" Fists
	/call AbilitySet_Add "Firestorm of Fists" Fists
	/call AbilitySet_Add "Barrage of Fists" Fists
    /call AbilitySet_Add "Flurry of Fists" Fists
    /call AbilitySet_ChooseOuter Fists Fists

|---Precision Line
	/call AbilitySet_Add "Doomwalker's Precision Strike" Precision
    /call AbilitySet_Add "Firewalker's Precision Strike" Precision
    /call AbilitySet_Add "Icewalker's Precision Strike" Precision
    /call AbilitySet_Add "Bloodwalker's Precision Strike" Precision
    /call AbilitySet_ChooseOuter Precision1 Precision
    /call AbilitySet_ChooseOuter Precision2 Precision "${Precision1}"
    /call AbilitySet_ChooseOuter Precision3 Precision "${Precision2}" "${Precision1}"
|---Shuriken Line
	/call AbilitySet_Add "Vigorous Shuriken" Shuriken
    /call AbilitySet_ChooseOuter Shuriken Shuriken
|---Crane Line
	/call AbilitySet_Add "Crane Stance" CraneStance
    /call AbilitySet_Add "Heron Stance" CraneStance
    /call AbilitySet_ChooseOuter CraneStance CraneStance
    
|-Dicho Spell*
	/call AbilitySet_Add "Dichotomic Form" DichoSpell
    /call AbilitySet_Add "Dissident Form" DichoSpell
    /call AbilitySet_Add "Composite Form" DichoSpell
    /call AbilitySet_Add "Ecliptic Form" DichoSpell
    /call AbilitySet_ChooseOuter DichoSpell DichoSpell
    
|---Fast Endurance regen - No Update
	/call AbilitySet_Add "Second Wind" endregen
    /call AbilitySet_Add "Third Wind" endregen
    /call AbilitySet_Add "Fourth Wind" endregen
    /call AbilitySet_Add "Respite" endregen
    /call AbilitySet_Add "Reprieve" endregen
    /call AbilitySet_Add "Rest" endregen
    /call AbilitySet_Add "Breather" endregen
    /call AbilitySet_Add "Relax" endregen
    /call AbilitySet_Add "Night's Calming" endregen
    /call AbilitySet_Add "Convalesce" endregen
    /call AbilitySet_ChooseOuter endregen endregen

|-Aura Set up	
	/call AbilitySet_AddAura "Disciple's Aura" "Disciple's Aura Effect" MonkAura
    /call AbilitySet_AddAura "Master's Aura" "Master's Aura Effect" MonkAura
    /call AbilitySet_ChooseOuter MonkAura MonkAura
    /varset MonkAura_Name ${GetAuraName[${MonkAura},MonkAura]}
|-Ironfist line
    /call AbilitySet_Add "Ashenhand Discipline" Iron
    /call AbilitySet_Add "Scaledfist Discipline" Iron
    /call AbilitySet_Add "Ironfist Discipline" Iron
    /call AbilitySet_ChooseOuter Iron Iron

|-Heel line
    /call AbilitySet_Add "Rapid Kick Discipline" Heel
    /call AbilitySet_Add "Heel of Kanji" Heel
    /call AbilitySet_Add "Heel of Kai" Heel
    /call AbilitySet_Add "Heel of Kojai" Heel
    /call AbilitySet_Add "Heel of Zagali" Heel
    /call AbilitySet_ChooseOuter Heel Heel
    
|-Speed line
    /call AbilitySet_Add "Hundred Fists Discipline" Speed
    /call AbilitySet_Add "Speed Focus Discipline" Speed
    /call AbilitySet_ChooseOuter Speed Speed

|- Fists of Wu Double Attack Line
    /call AbilitySet_Add "Fists Of Wu" FistsWu    
    /call AbilitySet_ChooseOuter FistsWu FistsWu

|-Palm line
	/call AbilitySet_Add "Innerflame Discipline" Palm
	/call AbilitySet_Add "Crystalpalm Discipline" Palm
    /call AbilitySet_Add "Diamondpalm Discipline" Palm
    /call AbilitySet_Add "Terrorpalm Discipline" Palm
    /call AbilitySet_ChooseOuter Palm Palm

|-Tiger's Poise/Symmetry line
    /call AbilitySet_Add "Dragon's Poise" Poise
    /call AbilitySet_Add "Tiger's Poise" Poise
    /call AbilitySet_Add "Eagle's Poise" Poise
    /call AbilitySet_Add "Tiger's Symmetry" Poise
    /call AbilitySet_ChooseOuter Poise Poise

| - New Monk mez
    /call AbilitySet_Add "Echo of Disorientation" MezSpell
    /call AbilitySet_Add "Echo of Flinching" MezSpell
    /call AbilitySet_Add "Echo of Diversion" MezSpell
    /call AbilitySet_ChooseOuter MezSpell MezSpell

|- Breaths Endurance Line 
    /call AbilitySet_Add "Five Breaths" Breaths
    /call AbilitySet_Add "Six Breaths" Breaths
    /call AbilitySet_Add "Seven Breaths" Breaths
    /call AbilitySet_Add "Eight Breaths" Breaths
    /call AbilitySet_Add "Nine Breaths" Breaths
    /call AbilitySet_Add "Breath of Tranquility" Breaths
    /call AbilitySet_Add "Breath of Stillness" Breaths
    /call AbilitySet_Add "Moment of Stillness" Breaths
    /call AbilitySet_ChooseOuter Breaths Breaths    
/return

Sub MNK_ModeConfigMODEDPS
    |- Choose are best punch and kick ability for us on TLPs. Abiliies
    |- are purposefully slotted so lower level abilities are lower indicies
    |- and higher abilities are hgiher indicies -- do not modify
    /declare arr_punchabilities[4] string local
    /varset arr_punchabilities[1] Tiger Claw
    /varset arr_punchabilities[2] Eagle Strike
    /varset arr_punchabilities[3] Dragon Punch
    /varset arr_punchabilities[4] Tail Rake
    /declare st_punchability string local

    /declare arr_kickabilities[3] string local
    /varset arr_kickabilities[1] Kick
    /varset arr_kickabilities[2] Round Kick
    /varset arr_kickabilities[3] Flying Kick
    /declare st_kickability string local

    /declare i int local 0
    /for i 1 to ${arr_punchabilities.Size}
        /if (${Me.SkillCap[${arr_punchabilities[${i}]}]} > 0) {
            /varset st_punchability ${arr_punchabilities[${i}]}
        }
    /next i
    /for i 1 to ${arr_kickabilities.Size}
        /if (${Me.SkillCap[${arr_kickabilities[${i}]}]} > 0) {
            /varset st_kickability ${arr_kickabilities[${i}]}
        }
    /next i
    /echo Monk: Using Punch Ability ${st_punchability}
    /echo Monk: Using Kick Ability ${st_kickability}
    |---------------------------------------------------------------------
    |- TODO: Optimize Burn Conditions.
    |- Monk Burn Routine copied verbatim from contributed  MNK macro.
    |- /call AddToRotation MNK_Burn_MODEDPS_Rotation "ABILITY" "TYPE" ${Parse[0, "( )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Silent Strikes"            "AA" TRUE
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Swift Tails' Chant"        "AA" TRUE
    |- First grouping
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Infusion of Thunder"       "AA"    ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Spire of the Sensei"       "AA"    ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${DichoSpell}"             "Disc"  ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${CraneStance}"                  "Disc"  ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Five Point Palm"           "AA"    ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${Heel}"                   "Disc"  ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    |- Second grouping
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Focused Destructive Force" "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${Poise}"                  "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${DichoSpell}"             "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${CraneStance}"                  "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Five Point Palm"           "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${Palm}"                   "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    |- Third grouping
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Infusion of Thunder"       "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Spire of the Sensei"       "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Ton Po's Stance"           "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${DichoSpell}"             "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${CraneStance}"                  "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Five Point Palm"           "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${Speed}"                  "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    |- Fourth grouping
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Focused Destructive Force" "AA"    ${Parse[0, "( !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${Poise}"                  "Disc"  ${Parse[0, "( !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Infusion of Thunder"       "AA"    ${Parse[0, "( !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "Spire of the Sensei"       "AA"    ${Parse[0, "( !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODEDPS_Rotation "${Storm}"                  "Disc"  ${Parse[0, "( !${Me.ActiveDisc.ID} )"]}

    |- /call AddToRotation MNK_DPS_MODEDPS_Rotation "ABILITY" "TYPE" ${Parse[0,"( )"]}
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "Mend" "Ability" ${Parse[0,"( ${Me.PctHPs} < 45 )"]}
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${FistsWu}" "Disc" ${Parse[0,"( !${Me.Song[${FistsWu}].ID} )"]}
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${Alliance}" "Disc" ${Parse[0,"( (!${Target.Buff[Firewalker's Covenant Trigger].ID} || !${Target.Buff[Doomwalker's Alliance Trigger].ID}) && ${DoAlliance[SETTINGVAL]} && ${CanAlliance} )"]}  
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "Vehement Rage" "AA" ${Parse[0,"( ${Target.PctHPs}>10 && !${Me.ActiveDisc.ID} )"]} 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${Iron}" "Disc" ${Parse[0,"( !${Me.ActiveDisc.ID} && !${Target.Named} )"]} 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${DichoSpell}" "Disc" TRUE 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${CraneStance}" "Disc" TRUE 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "Five Point Palm" "AA" TRUE
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${st_punchability}" "Ability" TRUE 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${st_kickability}" "Ability" TRUE 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "Zan Fi's Whistle" "AA" TRUE
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "Two-Finger Wasp Touch" "AA" TRUE 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${Drunken}" "Disc" ${Parse[0,"( ${Me.PctEndurance}>=20 && ${Target.PctHPs}>10 )"]} 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${Curse}" "Disc" ${Parse[0,"( ${Target.PctHPs}>5 )"]} 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${Synergy}" "Disc" TRUE 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${Fang}" "Disc" TRUE
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${Fists}" "Disc" TRUE 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${Precision1}" "Disc" TRUE
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${Precision2}" "Disc" TRUE
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${Precision3}" "Disc" TRUE
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "${Shuriken}" "Disc" TRUE 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "Intimidation" "Ability" ${Parse[0,"( ${DoIntimidate[SETTINGVAL]} )"]} 
    /call AddToRotation MNK_DPS_MODEDPS_Rotation "Disarm" "Ability" ${Parse[0,"( ${Me.AbilityReady[Disarm]} )"]}

    /call AddToRotation MNK_Downtime_MODEDPS_Rotation "${MonkAura}" "Disc" ${Parse[0,"( !${Spell[${Me.Aura[1]}].ID} && ${Me.PctEndurance}>10 )"]}
    /call AddToRotation MNK_Downtime_MODEDPS_Rotation "${Breaths}" "Disc" ${Parse[0,"( ${Me.PctEndurance}<=75 && ${Me.CombatAbilityReady[${Breaths}]} )"]}
    /call AddToRotation MNK_Downtime_MODEDPS_Rotation "${endregen}" "Disc" ${Parse[0,"( ${Me.PctEndurance}<15 && ${Me.CombatAbilityReady[${endregen}]} )"]}  
    /call AddToRotation MNK_Downtime_MODEDPS_Rotation "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation MNK_Downtime_MODEDPS_Rotation "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}


/return

Sub MNK_ModeConfigMODETLP
    |- Choose are best punch and kick ability for us on TLPs. Abiliies
    |- are purposefully slotted so lower level abilities are lower indicies
    |- and higher abilities are hgiher indicies -- do not modify
    /declare arr_punchabilities[4] string local
    /varset arr_punchabilities[1] Tiger Claw
    /varset arr_punchabilities[2] Eagle Strike
    /varset arr_punchabilities[3] Tail Rake
    /varset arr_punchabilities[4] Dragon Punch

    /declare st_punchability string local

    /declare arr_kickabilities[3] string local
    /varset arr_kickabilities[1] Kick
    /varset arr_kickabilities[2] Round Kick
    /varset arr_kickabilities[3] Flying Kick
    /declare st_kickability string local

    /declare i int local 0
    /for i 1 to ${arr_punchabilities.Size}
        /if (${Me.SkillCap[${arr_punchabilities[${i}]}]} > 0) {
            /varset st_punchability ${arr_punchabilities[${i}]}
        }
    /next i
    /for i 1 to ${arr_kickabilities.Size}
        /if (${Me.SkillCap[${arr_kickabilities[${i}]}]} > 0) {
            /varset st_kickability ${arr_kickabilities[${i}]}
        }
    /next i
    /echo Monk: Using Punch Ability ${st_punchability}
    /echo Monk: Using Kick Ability ${st_kickability}

/if (!${Me.HaveExpansion[Dragons of Norrath]} && ${Me.HaveExpansion[Omens of War]}) {
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${Speed}"                     Disc   ${Parse[0, "( ( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && ${Me.CombatAbilityReady[${Speed}]}  && !${Me.ActiveDisc.ID} )"]} 
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Focused Destructive Force"    AA     ${Parse[0, "( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${Me.ActiveDisc.Name.Equal[${Spell[Speed Focus Discipline].RankName}]} )"]} 
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${Heel}"                      Disc   ${Parse[0, "( ( ${BurnAuto[SETTINGVAL]} || MEDBURN ) && ${Me.CombatAbilityReady[${Heel}]}   && !${Me.ActiveDisc.ID} )"]}   
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${Palm}"                      Disc   ${Parse[0, "( ( ${BurnAuto[SETTINGVAL]} || MEDBURN ) && !${Me.CombatAbilityReady[${Heel}]}  && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID})"]} 
    /call AddToRotation MNK_DPS_MODETLP_Rotation  "${Iron}"                      Disc   ${Parse[0, "( ( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && !${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} && !${Target.Named} )"]} 
    /call AddToRotation MNK_DPS_MODETLP_Rotation  "Thunderkick Discipline"       Disc   ${Parse[0, "( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && !${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} && !${Target.Named} )"]} 
    /call AddToRotation MNK_DPS_MODETLP_Rotation "Mend" Ability      ${Parse[0,"( ${Me.PctHPs} < 55 )"]}
    /call AddToRotation MNK_DPS_MODETLP_Rotation "${st_punchability}" "Ability" TRUE 
    /call AddToRotation MNK_DPS_MODETLP_Rotation "${st_kickability}" "Ability" TRUE 
    /call AddToRotation MNK_DPS_MODETLP_Rotation "Elbow Strike" "Disc" TRUE 	
    /call AddToRotation MNK_Downtime_MODETLP_Rotation "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation MNK_Downtime_MODETLP_Rotation "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
} else {
    |---------------------------------------------------------------------
    |- TODO: Optimize Burn Conditions.
    |- Monk Burn Routine copied verbatim from contributed  MNK macro.
    |- /call AddToRotation MNK_Burn_MODEDPS_Rotation "ABILITY" "TYPE" ${Parse[0, "( )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Silent Strikes"            "AA" TRUE
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Swift Tails' Chant"        "AA" TRUE
    |- First grouping
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Infusion of Thunder"       "AA"    ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Spire of the Sensei"       "AA"    ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${DichoSpell}"             "Disc"  ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${CraneStance}"            "Disc"  ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Five Point Palm"           "AA"    ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${Heel}"                   "Disc"  ${Parse[0, "( ${Me.CombatAbilityReady[${Heel}]} && !${Me.ActiveDisc.ID} )"]}
    |- Second grouping
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Focused Destructive Force" "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${Poise}"                  "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${DichoSpell}"             "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${CraneStance}"            "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Five Point Palm"           "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${Palm}"                   "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && ${Me.CombatAbilityReady[${Palm}]} && !${Me.ActiveDisc.ID} )"]}
    |- Third grouping
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Infusion of Thunder"       "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Spire of the Sensei"       "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Ton Po's Stance"           "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${DichoSpell}"             "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${CraneStance}"            "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Five Point Palm"           "AA"    ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${Speed}"                  "Disc"  ${Parse[0, "( !${Me.CombatAbilityReady[${Heel}]} && !${Me.CombatAbilityReady[${Palm}]} && ${Me.CombatAbilityReady[${Speed}]} && !${Me.ActiveDisc.ID} )"]}
    |- Fourth grouping
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Focused Destructive Force" "AA"    ${Parse[0, "( !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${Poise}"                  "Disc"  ${Parse[0, "( !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Infusion of Thunder"       "AA"    ${Parse[0, "( !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "Spire of the Sensei"       "AA"    ${Parse[0, "( !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation MNK_Burn_MODETLP_Rotation "${Storm}"                  "Disc"  ${Parse[0, "( !${Me.ActiveDisc.ID} )"]}

    |- /call AddToRotation MNK_DPS_MODEDPS_Rotation "ABILITY" "TYPE" ${Parse[0,"( )"]}
    /call AddToRotation MNK_DPS_MODETLP_Rotation "Mend" "Ability" ${Parse[0,"( ${Me.PctHPs} < 55 )"]}
    /call AddToRotation MNK_DPS_MODETLP_Rotation "${st_punchability}" "Ability" TRUE 
    /call AddToRotation MNK_DPS_MODETLP_Rotation "${st_kickability}" "Ability" TRUE 
    /call AddToRotation MNK_DPS_MODETLP_Rotation "${Fists}" "Disc" TRUE 
    /call AddToRotation MNK_DPS_MODETLP_Rotation "${Precision1}" "Disc" TRUE
    /call AddToRotation MNK_DPS_MODETLP_Rotation "${Precision2}" "Disc" TRUE
    /call AddToRotation MNK_DPS_MODETLP_Rotation "${Precision3}" "Disc" TRUE
    /call AddToRotation MNK_DPS_MODETLP_Rotation "Intimidation" "Ability" ${Parse[0,"( ${DoIntimidate[SETTINGVAL]} )"]} 
    /call AddToRotation MNK_DPS_MODETLP_Rotation "Disarm" "Ability" ${Parse[0,"( ${Me.AbilityReady[Disarm]} )"]}

    /call AddToRotation MNK_Downtime_MODETLP_Rotation "${MonkAura}" "Disc" ${Parse[0,"( !${Spell[${Me.Aura[1]}].ID} && ${Me.PctEndurance}>10 )"]}
    /call AddToRotation MNK_Downtime_MODETLP_Rotation "${Breaths}" "Disc" ${Parse[0,"( ${Me.PctEndurance}<=75 && ${Me.CombatAbilityReady[${Breaths}]} )"]}
    /call AddToRotation MNK_Downtime_MODETLP_Rotation "${endregen}" "Disc" ${Parse[0,"( ${Me.PctEndurance}<15 && ${Me.CombatAbilityReady[${endregen}]} )"]}  
    /call AddToRotation MNK_Downtime_MODETLP_Rotation "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation MNK_Downtime_MODETLP_Rotation "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
}

/return

Sub MNK_Combat_Routine
    /if (DODPS) {
        /if (BURNCHECK) {
            /call Ordered_Rotation_Follow MNK_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE 1
        }
        /call Ordered_Rotation_Follow MNK_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        
    }
/return ${Macro.Return}

Sub MNK_Downtime_Routine
|- Call Self buffs
    
    /call FollowRotation  MNK_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}
/return ${Macro.Return}

Sub MNK_PullSetup
    /if ( ${RG_CanUseAA[Distant Strike]}  ) {
        /call Pull_SetAbility "Distant Strike" AA
    } else {
        /call Pull_SetAbility "Throw Stone" "Disc"
    }
/return