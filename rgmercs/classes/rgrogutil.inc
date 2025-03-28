#define MODEDPS 0
#define MODETLP 2

Sub ROG_Setup
   |- ROG Settings Declare
    /declare RGList_ROG list outer

    |- Items
    /call ItemSet_New Epic
    
    |- DiscSets
    /call AbilitySet_New ConditionedReflexes
    /call AbilitySet_New PracticedReflexes
    /call AbilitySet_New Vision
    /call AbilitySet_New Shadowhunter
    /call AbilitySet_New Slice
    /call AbilitySet_New Executioner
    /call AbilitySet_New Executioner2
    /call AbilitySet_New Twisted
    /call AbilitySet_New ProcBuff
    /call AbilitySet_New Frenzied
    /call AbilitySet_New Ambush
    /call AbilitySet_New SneakAttack
    /call AbilitySet_New PoisonBlade
    /call AbilitySet_New FellStrike
    /call AbilitySet_New Pinpoint
    /call AbilitySet_New Puncture
    /call AbilitySet_New EndRegen
    /call AbilitySet_New EdgeDisc
    /call AbilitySet_New AspDisc
    /call AbilitySet_New AimDisc
    /call AbilitySet_New MarkDisc
    /call AbilitySet_New Jugular
    /call AbilitySet_New Phantom
    /call AbilitySet_New SecretBlade
    /call AbilitySet_New DichoSpell
    /call AbilitySet_New Alliance
    
    |- Live Rotations
    /call Ordered_Rotation_New ROG_DPS_MODEDPS_Rotation
    /call Ordered_Rotation_New ROG_Downtime_MODEDPS_Rotation
    /call Ordered_Rotation_New ROG_Burn_MODEDPS_Rotation
    /call Ordered_Rotation_New ROG_Evasion_MODEDPS_Rotation
    /call Ordered_Rotation_New ROG_DEBUFF_MODEDPS_Rotation

    |- TLP Rotations
    /call Ordered_Rotation_New ROG_DPS_MODETLP_Rotation
    /call Ordered_Rotation_New ROG_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New ROG_Burn_MODETLP_Rotation
    /call Ordered_Rotation_New ROG_Evasion_MODETLP_Rotation
    /call Ordered_Rotation_New ROG_DEBUFF_MODETLP_Rotation

    |-Config Options
    /call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = DPS SET 2 = TLP
    /call RGLoadSetting ROG DoOpener 1 Combat "Set 0/1 to use a combat opener."
    /call RGLoadSetting ROG DoHideSneak 1 Options "Set 0/1 to use hide and sneak abilities."
    /call RGLoadSetting ROG DoPickPocket 1 Options "Set 0/1 to use the PickPocket ability (Default On). [UNIMPLEMENTED]"
    /call RGLoadSetting ROG DoDoT 1 Options "Set 0/1 to use the Jugular ability to DoT (Default On)."
    /call RGLoadSetting ROG DoSnare 0 Options "Set 0/1 to use Ligament Slice ability to Snare (Default Off)."
    /call RGLoadSetting ROG DoAmbush 0 Options "Set 0/1 to use Ambush ability to Stun (Default Off)."
    /call RGLoadSetting ROG DoMark 1 Options "Set 0/1 to use Mark ability to Stun and Debuff (Default On)."
    /call RGLoadSetting ROG DoPinpointBurn 1 Options "Set 1 to use Pinpoint ability during burn only, set 0 to use during normal DPS rotation. (Default On)."
    /call RGLoadSetting ROG DoExecBurn 1 Options "Set 1 to use Executioner ability during burn only, set 0 to use during normal DPS rotation. (Default On)."
    /call RGLoadSetting ROG DoIntimidation 1 Options "Set 0/1 to use Intimidation ability, when AA is rank 2 or above (Default On)."
    /call RGLoadSetting ROG DoDisarm 1 Options "Set 0/1 to use Disarm ability (Default On)."

    | Poison buffage
    /declare CheckPoisonTimer	timer outer 
    /call RGLoadSetting ROG ChestItemName "${Me.Inventory[17].Name}" Item "Name of chest item to use."
    /call RGLoadSetting ROG PoisonClicky "NULL" Item "Inventory item name that is clicked to summon rogue poison."
    /call RGLoadSetting ROG PoisonName NULL Item "Set the name of the poison to use."
    /call RGLoadSetting ROG PoisonBuffName NULL Item "Set the name of the poison buff to check for to avoid constant recasting."
    /call RGLoadSetting ROG PoisonItemCount 5 Item "Sets the number of poison items you summon before stopping. Defautlt: 5"
    /call RGLoadSetting ROG DoPoison 0 Item "Set 0/1 to use poisons."
    /call RGLoadSetting ROG AutoDebuffAt 99 DEBUFF "%HP to DEBUFF Mobs. Checked by ." 1 

    | Disable Poisons if we don't have stuff set.
    /if (${PoisonName[SETTINGVAL].Equal[NULL]} || ${PoisonBuffName[SETTINGVAL].Equal[NULL]}) {
        /echo "*** WARNING: If you want to use poisons, please put the poison name and the buff name set in your ini. ***"
        /echo "*** WARNING: Disabling Poison usage ***"
        /varset DoPoison[SETTINGVAL] 0
    }
/return

Sub ROG_SetupSkills 

    |- Items
    |- Epic
    /call ItemSet_Add "Fatestealer"                     Epic    | Epic 1.5
    /call ItemSet_Add "Nightshade, Blade of Entropy"    Epic    | Epic 2.0
    /call ItemSet_ChooseOuter Epic Epic

    |- Epic Buffs
    | Epic 1.5 Buff
    /declare EpicBuff1 string outer "Assassin's Taint"
    | Epic 2.0 Buff
    /declare EpicBuff2 string outer "Deceiver's Blight"


    | Whenever: Conditioned Reflexes 
    /call AbilitySet_Add "Conditioned Reflexes" ConditionedReflexes
    /call AbilitySet_Add "Practiced Reflexes"   ConditionedReflexes
    /call AbilitySet_ChooseOuter ConditionedReflexes ConditionedReflexes
    DEBUG Set ConditionedReflexes as ${ConditionedReflexes}
    
    /call AbilitySet_Add "Practiced Reflexes" PracticedReflexes
    /call AbilitySet_ChooseOuter PracticedReflexes PracticedReflexes
    DEBUG Set PracticedReflexes as ${PracticedReflexes}
    

    | Whenever - Thief's Eyes
    /call AbilitySet_Add "Thief's Sight"    Vision  | Level 117
    /call AbilitySet_Add "Thief's Vision"   Vision  | Level 96
    /call AbilitySet_Add "Thief's Eyes"     Vision  | Level 68
    /call AbilitySet_ChooseOuter Vision Vision
    DEBUG Set Vision as ${Vision}

    | Whenever - Shadow Hunter's Dagger
    /call AbilitySet_Add "Shadow-Hunter's Dagger"   Shadowhunter    | Level 102
    /call AbilitySet_ChooseOuter Shadowhunter Shadowhunter
    DEBUG Set Shadowhunter as ${Shadowhunter}

    | Timer 1 - Slice
    /call AbilitySet_Add "Carve"    Slice   | Level 123
    /call AbilitySet_Add "Lance"    Slice   | Level 118
    /call AbilitySet_Add "Slash"    Slice   | Level 113
    /call AbilitySet_Add "Slice"    Slice   | Level 108
    /call AbilitySet_Add "Hack"     Slice   | Level 103
    /call AbilitySet_Add "Gash"     Slice   | Level 98
    /call AbilitySet_Add "Lacerate" Slice   | Level 93
    /call AbilitySet_Add "Wound"    Slice   | Level 88
    /call AbilitySet_Add "Bleed"    Slice   | Level 83
    /call AbilitySet_ChooseOuter Slice Slice
    DEBUG Set Slice as ${Slice}

    | Timer 3 - Executioner
    /call AbilitySet_Add "Executioner Discipline"   Executioner | Level 100
    /call AbilitySet_Add "Eradicator's Discipline"  Executioner | Level 95
    /call AbilitySet_Add "Assassin Discipline"      Executioner | Level 75
    /call AbilitySet_Add "Duelist Discipline"       Executioner | Level 59
    /call AbilitySet_Add "Kinesthetics Discipline"  Executioner | Level 57
    /call AbilitySet_ChooseOuter Executioner Executioner
    /call AbilitySet_ChooseOuter Executioner2 Executioner "Executioner"
    DEBUG Set Executioner as ${Executioner}
    DEBUG Set Executioner2 as ${Executioner2}

    | Timer 4 - Twisted
    /call AbilitySet_Add "Twisted Chance Discipline"    Twisted | Level 65
    /call AbilitySet_Add "Deadeye Discipline"           Twisted | Level 54
    /call AbilitySet_ChooseOuter Twisted Twisted
    DEBUG Set Twisted as ${Twisted}

    | Timer 5 - ProcBuff
    /call AbilitySet_Add "Weapon Covenant"      ProcBuff    | Level 97
    /call AbilitySet_Add "Weapon Bond"          ProcBuff    | Level 92
    /call AbilitySet_Add "Weapon Affiliation"   ProcBuff    | Level 87
    /call AbilitySet_ChooseOuter ProcBuff ProcBuff
    DEBUG Set ProcBuff as ${ProcBuff}

    | Timer 6 - Frenzied
    /call AbilitySet_Add "Frenzied Stabbing Discipline" Frenzied    | Level 70
    /call AbilitySet_ChooseOuter Frenzied Frenzied
    DEBUG Set Frenzied as ${Frenzied}

    | Timer 7 - Ambush
    /call AbilitySet_Add "Bamboozle"        Ambush   | Level 121
    /call AbilitySet_Add "Ambuscade"        Ambush   | Level 116
    /call AbilitySet_Add "Bushwhack"        Ambush   | Level 111
    /call AbilitySet_Add "Lie in Wait"      Ambush   | Level 106
    /call AbilitySet_Add "Surprise Attack"  Ambush   | Level 101
    /call AbilitySet_Add "Beset"            Ambush   | Level 96
    /call AbilitySet_Add "Accost"           Ambush   | Level 91
    /call AbilitySet_Add "Assail"           Ambush   | Level 86
    /call AbilitySet_Add "Ambush"           Ambush   | Level 81
    /call AbilitySet_Add "Waylay"           Ambush   | Level 76
    /call AbilitySet_ChooseOuter Ambush Ambush
    DEBUG Set Ambush as ${Ambush}
    

    | Timer 9 - Sneak Attack
    /call AbilitySet_Add "Daggerslash"              SneakAttack | Level 115
    /call AbilitySet_Add "Daggerslice"              SneakAttack | Level 110
    /call AbilitySet_Add "Daggergash"               SneakAttack | Level 105
    /call AbilitySet_Add "Daggerthrust"             SneakAttack | Level 100
    /call AbilitySet_Add "Daggerstrike"             SneakAttack | Level 95
    /call AbilitySet_Add "Daggerswipe"              SneakAttack | Level 90
    /call AbilitySet_Add "Daggerlunge"              SneakAttack | Level 85
    /call AbilitySet_Add "Swiftblade"               SneakAttack | Level 80
    /call AbilitySet_Add "Razorarc"                 SneakAttack | Level 70
    /call AbilitySet_Add "Daggerfall"               SneakAttack | Level 69
    /call AbilitySet_Add "Ancient: Chaos Strike"    SneakAttack | Level 65
    /call AbilitySet_Add "Kyv Strike"               SneakAttack | Level 65
    /call AbilitySet_Add "Assassin's Strike"        SneakAttack | Level 63
    /call AbilitySet_Add "Thief's Vengeance"        SneakAttack | Level 52
    /call AbilitySet_Add "Sneak Attack"             SneakAttack | Level 20
    /call AbilitySet_ChooseOuter SneakAttack SneakAttack
    DEBUG Set SneakAttack as ${SneakAttack}

    | Timer 8 - PoisonBlade   
    /call AbilitySet_Add "Venomous Blade"       PoisonBlade   | Level 123  
    /call AbilitySet_Add "Netherbian Blade"     PoisonBlade   | Level 118
    /call AbilitySet_Add "Drachnid Blade"       PoisonBlade   | Level 113
    /call AbilitySet_Add "Skorpikis Blade"      PoisonBlade   | Level 108
    /call AbilitySet_Add "Reefcrawler Blade"    PoisonBlade   | Level 103
    /call AbilitySet_Add "Asp Blade"            PoisonBlade   | Level 98
    /call AbilitySet_Add "Toxic Blade"          PoisonBlade   | Level 93
    /call AbilitySet_ChooseOuter PoisonBlade PoisonBlade
    DEBUG Set PoisonBlade as ${PoisonBlade}

    | Timer 9 - Fellstrike
    /call AbilitySet_Add "Mayhem"       FellStrike  | Level 125
    /call AbilitySet_Add "Shadowstrike" FellStrike  | Level 120
    /call AbilitySet_Add "Blitzstrike"  FellStrike  | Level 115
    /call AbilitySet_Add "Fellstrike"   FellStrike  | Level 110
    /call AbilitySet_Add "Barrage"      FellStrike  | Level 105
    /call AbilitySet_Add "Incursion"    FellStrike  | Level 100
    /call AbilitySet_Add "Onslaught"    FellStrike  | Level 95
    /call AbilitySet_Add "Battery"      FellStrike  | Level 90
    /call AbilitySet_Add "Assault"      FellStrike  | Level 85
    |/call AbilitySet_Add "Elbow Strike" FellStrike  | Level 5 - For use before 85
    /call AbilitySet_ChooseOuter FellStrike FellStrike
    DEBUG Set FellStrike as ${FellStrike}

    | Timer 10 - Pinpoint
    /call AbilitySet_Add "Pinpoint Fault"           Pinpoint    | Level 124
    /call AbilitySet_Add "Pinpoint Defects"         Pinpoint    | Level 114
    /call AbilitySet_Add "Pinpoint Shortcomings"    Pinpoint    | Level 109
    /call AbilitySet_Add "Pinpoint Deficiencies"    Pinpoint    | Level 99
    /call AbilitySet_Add "Pinpoint Liabilities"     Pinpoint    | Level 94
    /call AbilitySet_Add "Pinpoint Flaws"           Pinpoint    | Level 89
    /call AbilitySet_Add "Pinpoint Vitals"          Pinpoint    | Level 84
    /call AbilitySet_Add "Pinpoint Weaknesses"      Pinpoint    | Level 79
    /call AbilitySet_Add "Pinpoint Vulnerability"   Pinpoint    | Level 74
    /call AbilitySet_ChooseOuter Pinpoint Pinpoint
    DEBUG Set Pinpoint as ${Pinpoint}

    | Timer 12 - Puncture
    /call AbilitySet_Add "Disorienting Puncture"    Puncture    | Level 119
    /call AbilitySet_Add "Vindictive Puncture"      Puncture    | Level 114
    /call AbilitySet_Add "Vexatious Puncture"       Puncture    | Level 109
    /call AbilitySet_Add "Disassociative Puncture"  Puncture    | Level 104
    /call AbilitySet_ChooseOuter Puncture Puncture
    DEBUG Set Puncture as ${Puncture}

    | Timer 13 - Endurance Regen
    |/call AbilitySet_Add "Convalesce"       EndRegen     | Level 121 - Self Slow for Regen
    |/call AbilitySet_Add "Night's Calming"  EndRegen    | Level 116 - Self Slow for Regen
    |/call AbilitySet_Add "Relax"            EndRegen    | Level 111 - Self Slow for Regen
    |/call AbilitySet_Add "Hiatus"           EndRegen    | Level 106 - Self Slow for Regen
    /call AbilitySet_Add "Breather"         EndRegen    | Level 101
    |/call AbilitySet_Add "Seventh Wind"     EndRegen    | Level 97 - Sac Endurance for Regen
    /call AbilitySet_Add "Rest"             EndRegen    | Level 96
    |/call AbilitySet_Add "Sixth Wind"       EndRegen    | Level 92 - Sac Endurance for Regen
    /call AbilitySet_Add "Reprieve"         EndRegen    | Level 91
    |/call AbilitySet_Add "Fifth Wind"       EndRegen    | Level 87 - Sac Endurance for Regen
    /call AbilitySet_Add "Respite"          EndRegen    | Level 86
    |/call AbilitySet_Add "Fourth Wind"      EndRegen    | Level 82 - Sac Endurance for Regen
    /call AbilitySet_Add "Third Wind"       EndRegen    | Level 77
    /call AbilitySet_Add "Second Wind"      EndRegen    | Level 72
    /call AbilitySet_ChooseOuter EndRegen EndRegen
    DEBUG Set EndRegen as ${EndRegen}

    | Timer 14 - EdgeDisc
    /call AbilitySet_Add "Reckless Edge Discipline" EdgeDisc    | Level 121
    /call AbilitySet_Add "Ragged Edge Discipline"   EdgeDisc    | Level 107
    /call AbilitySet_Add "Razor's Edge Discipline"  EdgeDisc    | Level 92
    /call AbilitySet_ChooseOuter EdgeDisc EdgeDisc
    DEBUG Set EdgeDisc as ${EdgeDisc}

    | Timer 15 - AspDisc
    /call AbilitySet_Add "Crinotoxin Discipline"    AspDisc | Level 124
    /call AbilitySet_Add "Exotoxin Discipline"      AspDisc | Level 119
    /call AbilitySet_Add "Chelicerae Discipline"    AspDisc | Level 114
    /call AbilitySet_Add "Aculeus Discipline"       AspDisc | Level 109
    /call AbilitySet_Add "Arcwork Discipline"       AspDisc | Level 104
    /call AbilitySet_Add "Aspbleeder Discipline"    AspDisc | Level 99
    /call AbilitySet_ChooseOuter AspDisc AspDisc
    DEBUG Set AspDisc as ${AspDisc}

    | Timer 16 - Aim Disc
    /call AbilitySet_Add "Baleful Aim Discipline"   AimDisc |  Level 116
    /call AbilitySet_Add "Lethal Aim Discipline"    AimDisc |  Level 108
    /call AbilitySet_Add "Fatal Aim Discipline"     AimDisc |  Level 98
    /call AbilitySet_Add "Deadly Aim Discipline"    AimDisc |  Level 68
    /call AbilitySet_ChooseOuter AimDisc AimDisc
    DEBUG Set AimDisc as ${AimDisc}

    | Timer 17 - Mark
    /call AbilitySet_Add "Unsuspecting Mark" MarkDisc   | Level 121
    /call AbilitySet_Add "Foolish Mark"     MarkDisc    | Level 116
    /call AbilitySet_Add "Naive Mark"       MarkDisc    | Level 111
    /call AbilitySet_Add "Dim-Witted Mark"  MarkDisc    | Level 106
    /call AbilitySet_Add "Wide-Eyed Mark"   MarkDisc    | Level 101
    /call AbilitySet_Add "Gullible Mark"    MarkDisc    | Level 96
    /call AbilitySet_Add "Gullible Mark"    MarkDisc    | Level 91
    /call AbilitySet_Add "Easy Mark"        MarkDisc    | Level 86
    /call AbilitySet_ChooseOuter MarkDisc MarkDisc
    DEBUG Set MarkDisc as ${MarkDisc}

    | Timer 18 - Jugular

    /call AbilitySet_Add "Jugular Slash"    Jugular | Level 77
    /call AbilitySet_Add "Jugular Slice"    Jugular | Level 82
    /call AbilitySet_Add "Jugular Sever"    Jugular | Level 87
    /call AbilitySet_Add "Jugular Gash"     Jugular | Level 92
    /call AbilitySet_Add "Jugular Lacerate" Jugular | Level 97
    /call AbilitySet_Add "Jugular Hack"     Jugular | Level 102
    /call AbilitySet_Add "Jugular Strike"   Jugular | Level 107
    /call AbilitySet_Add "Jugular Cut"      Jugular | Level 112
	/call AbilitySet_Add "Jugular Rend"     Jugular | Level 117
	/call AbilitySet_ChooseOuter Jugular Jugular
	DEBUG Set Jugular as ${Jugular}


    | Timer 19 - Phantom
    /call AbilitySet_Add "Phantom Assassin" Phantom  | Level 100
    /call AbilitySet_ChooseOuter Phantom Phantom
    DEBUG Set Phantom as ${Phantom}

    | Timer 20 - SecretBlade
    /call AbilitySet_Add "Veiled Blade"     SecretBlade | Level 124
    /call AbilitySet_Add "Obfuscated Blade" SecretBlade | Level 119
    /call AbilitySet_Add "Cloaked Blade"    SecretBlade | Level 114
    /call AbilitySet_Add "Secret Blade"     SecretBlade | Level 109
    /call AbilitySet_Add "Hidden Blade"     SecretBlade | Level 104
    /call AbilitySet_Add "Holdout Blade"    SecretBlade | Level 99
    /call AbilitySet_ChooseOuter SecretBlade SecretBlade
    DEBUG Set SecretBlade as ${SecretBlade}

    | Timer 21 - Alliance (not using) - Including for Others to add Modes.
    /call AbilitySet_Add "Poisonous Covenant"       Alliance    | Level 118
    /call AbilitySet_Add "Poisonous Alliance"       Alliance    | Level 113
    /call AbilitySet_Add "Poisonous Coalition"      Alliance    | Level 108
    /call AbilitySet_Add "Poisonous Conjunction"    Alliance    | Level 103
    /call AbilitySet_ChooseOuter Alliance Alliance
    DEBUG Set Alliance as ${Alliance}

    | Timer 22 - Dicho   
    /call AbilitySet_Add "Ecliptic Weapons"     DichoSpell  | Level 116
    /call AbilitySet_Add "Composite Weapons"    DichoSpell  | Level 111
    /call AbilitySet_Add "Dissident Weapons"    DichoSpell  | Level 106
    /call AbilitySet_Add "Dichotomic Weapons"   DichoSpell  | Level 101
    /call AbilitySet_ChooseOuter DichoSpell DichoSpell
    DEBUG Set DichoSpell as ${DichoSpell}
/return

Sub ROG_ModeConfigMODEDPS
    |- Debuff Rotation
    | Rogue Sneak Attack Opener, requires being hidden (90 and under hidden "for a few seconds")
    /call AddToRotation ROG_DEBUFF_MODEDPS_Rotation "${SneakAttack}"    Disc    ${Parse[0,"( ${DoOpener[SETTINGVAL]} && (${Me.AbilityReady[Hide]} && ${Me.Invis}) )"]}


    |- DPS Rotation
    | Epic Click 
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${Epic}" Item    ${Parse[0,"( (${DoEpic[SETTINGVAL]} == 2) && ${Spell[${FindItem[${Epic}].Spell}].Stacks} && (!${FindItem[${Epic}].TimerReady}) )"]}
    | Check for Chaotic Stab for Backstab, without we need to avoid backstabbing from the front
    /if (${RG_CanUseAA[Chaotic Stab]}) {
        /call AddToRotation ROG_DPS_MODEDPS_Rotation "Backstab"             Ability ${Parse[0,"( TRUE )"]}
    } else {
        /call AddToRotation ROG_DPS_MODEDPS_Rotation "Backstab"             Ability ${Parse[0,"(${Stick.Behind})"]}
    }
    | Endurance Regen (72+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${EndRegen}"              Disc ${Parse[0,"( ${Me.PctEndurance} < 21 )"]}

    | Intimidation - AA Rank 2 (70+ RoS) For Debuff
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "Intimidation"             Ability ${Parse[0,"( ${DoIntimidation[SETTINGVAL]} && (${Me.AltAbility[Intimidation].Rank} >= 2) )"]}
    | Disarm
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "Disarm"                   Ability ${Parse[0,"( ${DoDisarm[SETTINGVAL]} )"]}

    | Timer 7 - Ambush Stun (76+) - Usable on targets +4 levels from ability level. 81 and under version of ability require out of combat check
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${Ambush}"                Disc ${Parse[0,"( ${DoAmbush[SETTINGVAL]} && ( (${Me.PctEndurance} >= 5) && (${Target.PctHPs} >= 90) && (${Target.Distance} < 50) && (${Target.Level} <= ${Math.Calc[${Spell[${Ambush}].Level}+4]}) && ((${Spell[${Ambush}].Level} <= 81) && !${Me.CombatState.Equal[COMBAT]}) ))"]}
    | Conditioned Reflexes (97+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${ConditionedReflexes}"   Disc ${Parse[0,"( !${Me.Buff[Conditioned Reflexes Effect].ID} )"]}
    | Practiced Reflexes (97+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${PracticedReflexes}"     Disc ${Parse[0,"( !${Me.Buff[${PracticedReflexes}].ID} )"]}
    | Timer 16 - Aim Disc (68+) - Ranged Attack Proc Disc, bother using?
    |/call AddToRotation ROG_DPS_MODEDPS_Rotation "${AimDisc}"               Disc ${Parse[0,"( !${Me.ActiveDisc.ID} )"]}
    | Timer 16 - Knifeplay Disc (98+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "Knifeplay Discipline"     Disc ${Parse[0,"( !${Me.ActiveDisc.ID} )"]}
    | Thief's Eyes Buff (68+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${Vision}"                Disc ${Parse[0,"( !${Me.Song[${Vision}].ID} )"]}
    | Executioner Disc (57+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${Executioner}"           Disc ${Parse[0,"( !${DoExecBurn[SETTINGVAL]} && !${Me.ActiveDisc.ID} )"]}
    | Timer 20 - Secret Blade (99+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${SecretBlade}"           Disc ${Parse[0,"( TRUE )"]}
    | Timer 10 - Pinpoint Debuff (74+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${Pinpoint}"              Disc ${Parse[0,"( !${DoPinpointBurn[SETTINGVAL]} )"]}
    | Timer 17 - Mark (86+) - Usable on targets +4 levels from ability level
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${MarkDisc}"              Disc ${Parse[0,"( ${DoMark[SETTINGVAL]} && (${Target.Level} <= ${Math.Calc[${Spell[${MarkDisc}].Level}+4]}) )"]}
    | Timer 18 - Jugular - 82 and below version requires out of combat check
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${Jugular}"               Disc ${Parse[0,"( ${DoDoT[SETTINGVAL]} && ((${Spell[${Jugular}].Level} > 82) || ((${Spell[${Jugular}].Level} <= 82) && !${Me.CombatState.Equal[COMBAT]})) )"]}
    | Timer 12 - Puncture (104+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${Puncture}"              Disc ${Parse[0,"( TRUE )"]}
    | Timer 9 - Fellstrike  (85+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${FellStrike}"            Disc ${Parse[0,"( TRUE )"]}
    | Timer 8 - Poison Blade (93+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${PoisonBlade}"           Disc ${Parse[0,"( TRUE )"]}
    | Timer 1 - Slice (83+)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${Slice}"                 Disc ${Parse[0,"( TRUE )"]}
    | Shadow Hunter Throw
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${Shadowhunter}"          Disc ${Parse[0,"( TRUE )"]}
    | Twisted Shank AA (71+ TSS)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "Twisted Shank"            AA   ${Parse[0,"( TRUE )"]}
    | Dicho
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${DichoSpell}"            Disc ${Parse[0,"( TRUE )"]}
    | Ligament Slice AA (71+ TSS)
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "Ligament Slice"           AA ${Parse[0,"( ${DoSnare[SETTINGVAL]} )"]}
    | Poison Use
    /call AddToRotation ROG_DPS_MODEDPS_Rotation "${PoisonName[SETTINGVAL]}"    Item ${Parse[0,"( ${FindItemCount[=${PoisonName[SETTINGVAL]}]} >= 1 && ${FindItem[${PoisonName[SETTINGVAL]}].Timer}==0 && !${Me.Buff[${PoisonBuffName[SETTINGVAL]}].ID} )"]}


    |- Burn Rotation
    | Shadow's Flanking AA (106+ RoS)
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "Shadow's Flanking"       AA      ${Parse[0,"( TRUE )"]}
    | Focused Rake's Rampage AA (96+ CotF)
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "Focused Rake's Rampage"  AA      ${Parse[0,"( TRUE )"]}
    | Rogue's Fury AA (73+ SoF)
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "Rogue's Fury"            AA      ${Parse[0,"( TRUE )"]}
    | Spire of the Rake AA (85+ SoD)
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "Spire of the Rake"       AA      ${Parse[0,"( TRUE )"]}
    | Chest Click
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "${ChestItemName[SETTINGVAL]}"    Item    ${Parse[1,"( ${Spell[${FindItem[${ChestItemName[SETTINGVAL]}].Spell}].Stacks} && (!${FindItem[${ChestItemName[SETTINGVAL]}].TimerReady}) && ${DoChestClick[SETTINGVAL]} )"]}
    | Epic Click
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "${Epic}"                 Item    ${Parse[0,"( (${DoEpic[SETTINGVAL]} == 1) && ${Spell[${FindItem[${Epic}].Spell}].Stacks} && (!${FindItem[${Epic}].TimerReady}) )"]}
    | Timer 10 - Pinpoint Debuff (74+)
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "${Pinpoint}"             Disc    ${Parse[0,"( ${DoPinpointBurn[SETTINGVAL]} )"]}
    | Frenzied Disc (111+)
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "${Frenzied}"             Disc    ${Parse[0,"( !${Me.ActiveDisc.ID} )"]}
    | Twisted Disc (111+)
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "${Twisted}"              Disc    ${Parse[0,"( !${Me.ActiveDisc.ID} )"]}
    | Timer 16 - Aim Disc (68+) - Ranged Attack Proc Disc, bother using?
    |/call AddToRotation ROG_Burn_MODEDPS_Rotation "${AimDisc}"              Disc    ${Parse[0,"( !${Me.ActiveDisc.ID} )"]}
    | Executioner Disc (57+)
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "${Executioner}"          Disc    ${Parse[0,"( ${DoExecBurn[SETTINGVAL]} && !${Me.ActiveDisc.ID} )"]}
    | Executioner Disc 2 (57+)
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "${Executioner2}"         Disc    ${Parse[0,"( ${DoExecBurn[SETTINGVAL]} && !${Me.ActiveDisc.ID} )"]}
    | EdgeDisc (92+)
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "${EdgeDisc}"             Disc    ${Parse[0,"( !${Me.ActiveDisc.ID} )"]}
    | AspDisc (99+)
    /call AddToRotation ROG_Burn_MODEDPS_Rotation "${AspDisc}"              Disc    ${Parse[0,"( !${Me.ActiveDisc.ID} )"]}


    |- Downtime Rotation
    | Timer 13 - Endurance Regen
    /call AddToRotation ROG_Downtime_MODEDPS_Rotation "${EndRegen}"                 Disc        ${Parse[0,"(${Me.PctEndurance}<21)"]}
    | Mount Buff Refresh
    /call AddToRotation ROG_Downtime_MODEDPS_Rotation "${MountItem[SETTINGVAL]}"    Item        ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation ROG_Downtime_MODEDPS_Rotation "/dismount"                   Command     ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    | Poison Summon
    /call AddToRotation ROG_Downtime_MODEDPS_Rotation "${PoisonClicky[SETTINGVAL]}" Item        ${Parse[0,"( ${FindItemCount[=${PoisonName[SETTINGVAL]}]} < ${PoisonItemCount[SETTINGVAL]} && ${FindItem[${PoisonClicky[SETTINGVAL]}].Timer}==0 )"]}
    | Poison Use
    /call AddToRotation ROG_Downtime_MODEDPS_Rotation "${PoisonName[SETTINGVAL]}"   Item        ${Parse[0,"( ${FindItemCount[=${PoisonName[SETTINGVAL]}]} >= 1 && ${FindItem[${PoisonName[SETTINGVAL]}].Timer}==0 && !${Me.Buff[${PoisonBuffName[SETTINGVAL]}].ID} )"]}


    |- Evasion Rotation
    | Escape (59+ SoL)
    /call AddToRotation ROG_Evasion_MODEDPS_Rotation "Escape"                       AA      ${Parse[0,"( ${SpawnCount[id ${assistid}]} && ${Me.PctAggro}>90 )"]}
    | Counterattack Disc (53+)
    /call AddToRotation ROG_Evasion_MODEDPS_Rotation "Counterattack Discipline"     Disc    ${Parse[0,"(!${SpawnCount[id ${assistid}]} || ${Spawn[id ${assistid}].Type.Equal[Corpse]})"]}
    | Tumble (75+ TSS)
    /call AddToRotation ROG_Evasion_MODEDPS_Rotation "Tumble"                       AA      ${Parse[0,"( ${SpawnCount[id ${assistid}]} && ${Me.PctAggro}>90 )"]}
    | Timer 19 - Phantom (100+)
    /call AddToRotation ROG_Evasion_MODEDPS_Rotation "${Phantom}"                   Disc    ${Parse[0,"( ${SpawnCount[id ${assistid}]} && ${Me.PctAggro}>90 )"]}
/return

Sub ROG_ModeConfigMODETLP
|- Rogue Primer/DEBUFF Routine Used for Priming Openers Before Combat
    /call AddToRotation ROG_DEBUFF_MODETLP_Rotation "${SneakAttack}"	Disc ${Parse[0,"( ${DoOpener[SETTINGVAL]} && ${Me.Level}<76 && ${Me.Invis} )"]}

|- DPS Rotation
    /if (${RG_CanUseAA[Chaotic Stab]} ) {
        /call AddToRotation ROG_DPS_MODETLP_Rotation "Backstab"				Ability ${Parse[0,"( TRUE )"]}
    } else {
        |- If we don't have chaotic stab, avoid backstabbing from the front.
        /call AddToRotation ROG_DPS_MODETLP_Rotation "Backstab"				Ability ${Parse[0,"(${Stick.Behind})"]}
    }
    
    | EndRegen Starts at Level 72
    /call AddToRotation ROG_DPS_MODETLP_Rotation "${EndRegen}" 				Disc ${Parse[0,"(${Me.PctEndurance}<21)"]}
    | Timer 7 Ambush Starts at Level 76, 76 and 81 version require combat check
    /call AddToRotation ROG_DPS_MODETLP_Rotation "${Ambush}" 					Disc ${Parse[0,"( ${Me.PctEndurance}>=5 && ${Target.PctHPs}>=90 && ${Target.Distance}<50 && (${Target.Level} <= ${Math.Calc[${Spell[${Ambush}].Level}+4]}) && ((${Spell[${Ambush}].Level} <= 81) && !${Me.CombatState.Equal[COMBAT]}))"]}
    | No ConditionedReflexes Starts at Level 97
    | No PracticedReflexes Starts at Level 97
    /call AddToRotation ROG_DPS_MODETLP_Rotation "${AimDisc}" 				Disc ${Parse[0,"( !${Me.ActiveDisc.ID} )"]}
    | Vision Starts at 68
    /call AddToRotation ROG_DPS_MODETLP_Rotation "${Vision}" 					Disc ${Parse[0,"( !${Me.Song[${Vision}].ID} )"]}
    | No SecretBlade Starts at Level 99
    | Pinpoint Starts at Level 74
    /call AddToRotation ROG_DPS_MODETLP_Rotation "${Pinpoint}"			 	Disc ${Parse[0,"( TRUE )"]}
    | No MarkDisc Starts at Level 86
    | Jugular Starts at Level 77, for 77 and 82 version require combat check
    /call AddToRotation ROG_DPS_MODETLP_Rotation "${Jugular}" 				Disc ${Parse[0,"( TRUE && ((${Spell[${Jugular}].Level} <= 82) && !${Me.CombatState.Equal[COMBAT]}))"]}
    | No Puncture Starts at Level 104
    | FellStrike technically starts at Level 85, Elbow Strike for below level 20
    /call AddToRotation ROG_DPS_MODETLP_Rotation "${FellStrike}" 				Disc ${Parse[0,"( ${Me.Level}<=20 )"]}
    | No Toxic Blade Starts at level 93
    /call AddToRotation ROG_DPS_MODETLP_Rotation "${Slice}" 					Disc ${Parse[0,"( TRUE )"]}
    | No Shadowhunter Starts at Level 102
    | Twisted Shank Starts at Level 71
    /call AddToRotation ROG_DPS_MODETLP_Rotation "Twisted Shank" 				AA 	${Parse[0,"( TRUE )"]}
    | No DichoSpell Starts at Level 101
    | Ligament Slice Starts at Level 71
    /call AddToRotation ROG_DPS_MODETLP_Rotation "Ligament Slice" 			AA ${Parse[0,"( TRUE )"]}
    /call AddToRotation ROG_DPS_MODETLP_Rotation "${PoisonName[SETTINGVAL]}" 	Item ${Parse[0,"( ${FindItemCount[=${PoisonName[SETTINGVAL]}]} >= 1 && ${FindItem[${PoisonName[SETTINGVAL]}].Timer}==0 && !${Me.Buff[${PoisonBuffName[SETTINGVAL]}].ID} )"]}

|- Burn Rotation
    | No Shadow's Flanking Starts at Level 106
    | No Focused Rake's Rampage Starts at Level 96
    | Rogue's Fury Starts at Level 73
    /call AddToRotation ROG_Burn_MODETLP_Rotation "Rogue's Fury" 				AA ${Parse[0,"( TRUE )"]}
    | No Spire of the Rake Starts at Level 85
    /call AddToRotation ROG_Burn_MODETLP_Rotation "${ChestItemName[SETTINGVAL]}" 		Item ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${DoChestClick[SETTINGVAL]} )"]}
    /call AddToRotation ROG_Burn_MODETLP_Rotation "${Epic}"          "Item" ${Parse[0,"( ${DoEpic[SETTINGVAL]} && ${Spell[${FindItem[${Epic}].Spell}].Stacks} && (!${FindItem[${Epic}].TimerReady}) )"]}
    | Frenzied Starts at Level 70
    /call AddToRotation ROG_Burn_MODETLP_Rotation "${Frenzied}" 						Disc ${Parse[0, "( ( ${BurnAuto[SETTINGVAL]} || BIGBURN )  && !${Me.ActiveDisc.ID} && ${Me.CombatAbilityReady[${Frenzied}]} )"]}
    /call AddToRotation ROG_Burn_MODETLP_Rotation "${Twisted}" 						Disc ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && !${Me.ActiveDisc.ID} && ${Me.CombatAbilityReady[${Twisted}]} )"]}
|	/call AddToRotation ROG_Burn_MODETLP_Rotation "${AimDisc}" 						Disc ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation ROG_Burn_MODETLP_Rotation "${Executioner}" 						Disc ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || MEDBURN ) && !${Me.ActiveDisc.ID} && ${Me.CombatAbilityReady[${Executioner}]} )"]}
    /call AddToRotation ROG_Burn_MODETLP_Rotation "${Executioner2}" 					Disc ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && !${Me.ActiveDisc.ID} && ${Me.CombatAbilityReady[${Executioner2}]} )"]}
    | EdgeDisc Starts at Level 92
    | No AspDisc Starts at Level 99

|- Downtime Rotation
    | EndRegen Starts at Level 72
    /call AddToRotation ROG_Downtime_MODETLP_Rotation "${EndRegen}" 					Disc ${Parse[0,"(${Me.PctEndurance}<21)"]}
    /call AddToRotation ROG_Downtime_MODETLP_Rotation "${MountItem[SETTINGVAL]}" 		Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation ROG_Downtime_MODETLP_Rotation "/dismount" 				"Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    /call AddToRotation ROG_Downtime_MODETLP_Rotation "${PoisonClicky[SETTINGVAL]}" 	Item ${Parse[0,"( ${FindItemCount[=${PoisonName[SETTINGVAL]}]} < ${PoisonItemCount[SETTINGVAL]} && ${FindItem[${PoisonClicky[SETTINGVAL]}].Timer}==0 )"]}
    /call AddToRotation ROG_Downtime_MODETLP_Rotation "${PoisonName[SETTINGVAL]}" 	Item ${Parse[0,"( ${FindItemCount[=${PoisonName[SETTINGVAL]}]} >= 1 && ${FindItem[${PoisonName[SETTINGVAL]}].Timer}==0 && !${Me.Buff[${PoisonBuffName[SETTINGVAL]}].ID} )"]}
    
    |- Evasion Rotation
    | Escape (59+ SoL)
    /call AddToRotation ROG_Evasion_MODETLP_Rotation "Escape"                       AA      ${Parse[0,"( ${SpawnCount[id ${assistid}]} && ${Me.PctAggro}>90 )"]}
    | Counterattack Disc (53+)
    /call AddToRotation ROG_Evasion_MODETLP_Rotation "Counterattack Discipline"     Disc    ${Parse[0,"(!${SpawnCount[id ${assistid}]} || ${Spawn[id ${assistid}].Type.Equal[Corpse]})"]}
    | Tumble (75+ TSS)
    /call AddToRotation ROG_Evasion_MODETLP_Rotation "Tumble"                       AA      ${Parse[0,"( ${SpawnCount[id ${assistid}]} && ${Me.PctAggro}>90 )"]}
    | Timer 19 - Phantom (100+)
    /call AddToRotation ROG_Evasion_MODETLP_Rotation "${Phantom}"                   Disc    ${Parse[0,"( ${SpawnCount[id ${assistid}]} && ${Me.PctAggro}>90 )"]}
    /return


Sub ROG_Combat_Routine
    /if (DODPS) {
        /if ( DODEBUFF ) {
            /call Ordered_Rotation_Follow ROG_DEBUFF_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        }
        /if (BURNCHECK) {
            /call Ordered_Rotation_Follow ROG_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE 1
        }
        /call Ordered_Rotation_Follow ROG_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE 1
    }
/return FALSE

Sub ROG_Downtime_Routine
    /call FollowRotation  ROG_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}
    /if (${DoHideSneak[SETTINGVAL]}) {
        /if (${Me.AbilityReady[hide]} && ${Me.AbilityReady[sneak]}) {
            /doability hide
            /doability sneak
        }
    }

/return FALSE

|----------------------------------------------------------------------------
|- SUB: Event GotHit
|----------------------------------------------------------------------------
#Event GotHit       "#*# bashes YOU for #*# points of damage.#*#"
#Event GotHit       "#*# crushes YOU for #*# points of damage.#*#"
#Event GotHit       "#*# hits YOU for #*# points of damage.#*#"
#Event GotHit       "#*# kicks YOU for #*# points of damage.#*#"
#Event GotHit       "#*# mauls YOU for #*# points of damage.#*#"
#Event GotHit       "#*# pierces YOU for #*# points of damage.#*#"
#Event GotHit       "#*# punches YOU for #*# points of damage.#*#"
#Event GotHit       "#*# slashes YOU for #*# points of damage.#*#"
#Event GotHit       "#*# bites YOU for #*# points of damage.#*#"
#Event GotHit       "#*# tries to #*# YOU, but #*#"
#event GotHit       "#*#smashes YOU for#*#"
#event GotHit       "#*#gores YOU for#*#"
#event GotHit       "#*#rampages YOU for#*#" 
Sub Event_GotHit
    |- Temporary gate until we get TLO based includes
    /if (${Me.Class.ShortName.Equal[ROG]}) /call Ordered_Rotation_Follow ROG_Evasion_MODEDPS_Rotation ${autotargetid} TRUE
    /doevents flush GotHit
/return

Sub ROG_PullSetup
   /if (${Me.Inventory[ranged].Type.Equal[Archery]} && ${Me.Inventory[ammo].Stack} > 50) {
        /call Pull_SetAbility "pullrange" "Special"
    } else /if (${Me.CombatAbilityReady[Throw Stone]}) {
        /call Pull_SetAbility "Throw Stone" "Disc"
    }
/return

#bind CorpseRun /corpserun
Sub Bind_CorpseRun
    /echo Not Yet Implemented
/return 