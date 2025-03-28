|- RGencutil.inc
|- Version 2.0
|- Updated: 4/25/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
#define MODEMEZ 3
#define MODECHARM 1
#define MODEMORI 0
#define MODETLP 2

Sub ENC_Setup
|-Create Setting List
    /declare RGList_ENC list outer

|-Declare AA and Spell variables
    /declare Spell1                string outer NULL 
    /declare Spell2                string outer NULL
    /declare Spell3                string outer NULL
    /declare Spell4                string outer NULL
    /declare Spell5                string outer NULL
    /declare Spell6                string outer NULL
    /declare Spell7                string outer NULL
    /declare Spell8                string outer NULL
    /declare Spell9                string outer NULL
    /declare Spell10            string outer NULL
    /declare Spell11            string outer NULL
    /declare Spell12            string outer NULL
    /declare Spell13            string outer NULL    
    /declare spellmisc          int outer ${Me.NumGems}
    /declare miscspellremem     string outer NULL
    /declare spellrememtimer    timer outer 0
    /declare groupbufftimer     timer outer 0
  
  |- Aura buffs are done in the old school way because we need to hardcode names
  |- Stupid corner cases.
   /call AbilitySet_New AuraBuff1 AURA
   /declare AuraBuff1Name string outer 
   /call AbilitySet_New AuraBuff2 AURA
   /declare AuraBuff2Name string outer 
   /call AbilitySet_New AuraBuff3 AURA
   /declare AuraBuff3Name string outer  

   /declare TwinCastBuff string outer

|- Back to your regularly scheduled programming
    /call AbilitySet_New HasteBuff
    /call AbilitySet_New ManaRegen
    /call AbilitySet_New MezBuff
    
    /call AbilitySet_New NdtBuff
    /declare NdtBuffCount          int     outer   0
    /declare NdtBuffRecastTimer    timer   outer   0
    |- Items
    /call ItemSet_New Epic
    |- Spells
    /call AbilitySet_New SelfHPBuff
    /call AbilitySet_New SelfRune1
    /call AbilitySet_New SelfRune2
    /call AbilitySet_New UnityRune
    /call AbilitySet_New SingleHaste
    /call AbilitySet_New SingleMana
    /call AbilitySet_New SingleRune
    /call AbilitySet_New GroupRune
    /call AbilitySet_New AggroRune
    /call AbilitySet_New AggroBuff
    /call AbilitySet_New SingleSpellShield
    /call AbilitySet_New GroupSpellShield
    /call AbilitySet_New SingleDoTShield
    /call AbilitySet_New GroupDoTShield
    /call AbilitySet_New SingleMeleeShield
    /call AbilitySet_New SelfGuardShield
    /call AbilitySet_New GroupAuspiceBuff
    /call AbilitySet_New AllianceSpell
    /call AbilitySet_New TwinCast
  |-CC
    /declare AEMezReset             int     outer   0
    /call AbilitySet_New PBAEStunSpell
    /call AbilitySet_New TargetAEStun
    /call AbilitySet_New SingleStunSpell1
  |-Charm
    /call AbilitySet_New CharmSpell
    /declare CharmDelay             timer   outer   0
    /declare CharmedID              int     outer   0
    /declare OldCharmedID           int     outer   0
  |-Debuff
    /call AbilitySet_New CrippleSpell
    /call AbilitySet_New SlowSpell
    /call AbilitySet_New StripBuffSpell
    /call AbilitySet_New TashSpell
    /call AbilitySet_New ManaDrainSpell
  |-DPS
    /call AbilitySet_New DichoSpell
    /call AbilitySet_New DoTSpell1
    /call AbilitySet_New ManaDot
    /call AbilitySet_New DebuffDot
    /declare FastNukePct            int     outer   90
    /call AbilitySet_New NukeSpell
    /call AbilitySet_New RuneNuke
    /call AbilitySet_New ManaNuke
    /call AbilitySet_New ChromaNuke
    /call AbilitySet_New CripSlowSpell

  |-Pet
    /call AbilitySet_New PetSpell
    /call AbilitySet_New PetBuffSpell
    /declare PetAssistTimer         timer   outer   0

  |- Mez
    /call AbilitySet_New MezAESpell
    /call AbilitySet_New MezAESpellFast
    /call AbilitySet_New MezPBAESpell
    /call AbilitySet_New MezSpell
    /call AbilitySet_New MezSpellFast
    /declare MezAEAA                string  outer   NULL

  |-Utility
    /call AbilitySet_New BlurSpell
    /call AbilitySet_New AEBlurSpell
    /call AbilitySet_New CalmSpell
    /call AbilitySet_New FearSpell
    /call AbilitySet_New RootSpell
    
    /call Ordered_Rotation_New ENC_DPS_MODEMEZ_Rotation
    /call Ordered_Rotation_New ENC_Downtime_MODEMEZ_Rotation
    /call Ordered_Rotation_New ENC_Burn_MODEMEZ_Rotation
    /call Ordered_Rotation_New ENC_Debuff_MODEMEZ_Rotation
    
    /call Ordered_Rotation_New ENC_DPS_MODECHARM_Rotation
    /call Ordered_Rotation_New ENC_Downtime_MODECHARM_Rotation
    /call Ordered_Rotation_New ENC_Burn_MODECHARM_Rotation
    /call Ordered_Rotation_New ENC_Debuff_MODECHARM_Rotation

    /call Ordered_Rotation_New ENC_DPS_MODETLP_Rotation
    /call Ordered_Rotation_New ENC_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New ENC_Burn_MODETLP_Rotation
    /call Ordered_Rotation_New ENC_Debuff_MODETLP_Rotation

    /call Ordered_Rotation_New ENC_DPS_MODEMORI_Rotation
    /call Ordered_Rotation_New ENC_Downtime_MODEMORI_Rotation
    /call Ordered_Rotation_New ENC_Burn_MODEMORI_Rotation
    /call Ordered_Rotation_New ENC_Debuff_MODEMORI_Rotation


|-Config Options    
    /call LoadCommonConfig 
    /varset ClassMode[SETTINGDESC] Set 0 = Mez Mode; 1 = Charm Pet Mode 2 = TLP 
    /call RGLoadSetting ENC AutoDebuffAt 99 Debuff "%HP to debuff Mobs." 1
    /call RGLoadSetting ENC DoCharmPet 0 Charm "Set 0/1 to Do charm pet. Must be using Charm Pet class mode."
    /call RGLoadSetting ENC CharmMinLvl 0 Charm "Minimum level to use as a charm pet. 0 = no minimum level."
    /call RGLoadSetting ENC CharmMaxLvl 0 Charm "Maximum level to use as a charm pet. 0 = maximum level based on spell."
    /call RGLoadSetting ENC CharmPreStun 1 Charm "Set 0/1 to use stun before charming mob."
    /call RGLoadSetting ENC CharmPreTash 1 Charm "Set 0/1 to use tash before charming mob."
    /call RGLoadSetting ENC CharmMinMobs 2 Charm "Set # to determine number of mobs present before charming."
    /call RGLoadSetting ENC Manatonuke 40 Combat "% Mana to stop nuking at."
    /call RGLoadSetting ENC DoDicho 0 Combat "Set 0/1 to use Dicho spell."
    /call RGLoadSetting ENC DoDot 0 Combat "Set 0/1 to use DoTs in combat."
    /call RGLoadSetting ENC HPStopDOT 30 Combat "%HP to cut off to stop casting dots."
    /call RGLoadSetting ENC DoPet 1 Combat "Set 0/1 to use Pet in combat and summon pet."
    /call RGLoadSetting ENC DoTash 1 Debuff "Set 0/1 to us tash debuffs."
    /call RGLoadSetting ENC DoAATash 0 Debuff "Set 0/1 to us Bite of Tashani debuffs."
    /call RGLoadSetting ENC DoSlow 1 Debuff "Set 0/1 to use slow debuffs."
    /call RGLoadSetting ENC DoCripple 1 Debuff "Set 0/1 to use cripple debuffs." 0 "ENC_ModeConfig${ClassMode}"
    /call RGLoadSetting ENC AutoLevelRange 1 Charm "Set 0/1 to auto determine charm min/max levels based on available spell."
    /call RGLoadSetting ENC DoNDTBuff 1 Options "Set 0/1 to use Melee Proc Buff (Night's Dark Terror Line)."
    /call RGLoadSetting ENC DoLearners 0 Options "Set 0/1 to use the Learner's Aura instead of the Mana Regen Aura." 0 ENC_RemoveAura
    /call RGLoadSetting ENC DoAggroRune 1 Rune "Set 0/1 to use the AggroRune on the tank."
    /call RGLoadSetting ENC DoGroupAbsorb 0 Rune "Set 0/1 to use the Group Absorb line with -Hate Proc."
    /call RGLoadSetting ENC DoStripBuff 1 Combat " Set 0/1 to Remove Beneficial buffs From Enemys."
    |- Mez settings that are ENC specific thus not in RGmez.inc
    /call RGLoadSetting ENC DoTwinCastMez 1 Mez "Set 0/1 to memorize twincast mez spells if available. Restart macro to take effect"
    /call RGLoadSetting ENC DoTwinCastDPS 1 Combat "Set 0/1 Will cast Twincast mez during combat to Increase Chanter DPS Via Use of the Twincast procs."
   
    /if (${Me.AltAbility[25].Name.Find[disabled]} && ${RG_AAReady[25]}) {
        /alt act 25
        /delay 5
    }
/return

|----------------------------------------------------------------------------
|- SUB: CheckOptions - Used to sort conflicting options at startup and set basic values if needed
|---------------------------------------------------------------------------- 
Sub ENC_CheckOptions
    /if ( ${CharmMaxLvl[SETTINGVAL]}==0 || (${CharmMaxLvl[SETTINGVAL]}!=${Spell[${CharmSpell}].MaxLevel} && ${AutoLevelRange[SETTINGVAL]}) ) {
            /call RGChangeSetting ENC CharmMaxLvl ${Spell[${CharmSpell}].MaxLevel}
    }

    /if (${CharmMinLvl[SETTINGVAL]}==0 || ${AutoLevelRange[SETTINGVAL]}) {
        /if (${Me.Level}>=40) {
            /call RGChangeSetting ENC CharmMinLvl ${Math.Calc[${Me.Level}-30].Int}
        } else /if (${Me.Level}>=30) {
            /call RGChangeSetting ENC CharmMinLvl ${Math.Calc[${Me.Level}-20].Int}
        } else {
            /call RGChangeSetting ENC CharmMinLvl 1
        }
    }
    /if (${DoCharmPet[SETTINGVAL]} && ${Me.Pet.ID}) {
        /pet get lost
        /if (${DoPet[SETTINGVAL]}) {
            /call RGChangeSetting ENC DoPet 0
        }
    }
/return

|* ------------------------------------------------------------------------------------------
| SUB: SetEncSpells
|------------------------------------------------------------------------------------------ *|
Sub ENC_SetupSkills
      /echo Choosing All Enchanter Spells - this may take a moment
    |- Items
    | - Epic 
    /call ItemSet_Add "Staff of Eternal Eloquence" Epic
    /call ItemSet_Add "Oculus of Persuasion" Epic
    /call ItemSet_ChooseOuter Epic Epic


    |-AE Mez AA * Var Name : MezAEAA string outer
    /if (${Me.Level}>=85 && ${RG_AAReady[Beam of Slumber]}) {
        /varset MezAEAA Beam of Slumber
    }
    
    |- /call AbilitySet_Add "SPELLNAME" SPELLVAR

    /call AbilitySet_Add "Chaotic Deception" TwinCast
    /call AbilitySet_Add "Chaotic Delusion" TwinCast
    /call AbilitySet_Add "Chaotic Bewildering" TwinCast
    /call AbilitySet_Add "Chaotic Confounding" TwinCast
    /call AbilitySet_Add "Chaotic Confusion" TwinCast
    /call AbilitySet_Add "Chaotic Baffling" TwinCast
    /call AbilitySet_Add "Chaotic Befuddling" TwinCast
    /call AbilitySet_Add "Chaotic Puzzlement" TwinCast
    /call AbilitySet_Add "Chaotic Conundrum" TwinCast
    /call AbilitySet_ChooseOuter TwinCast TwinCast
    /varset TwinCastBuff ${Spell[${Spell[${TwinCast}].AutoCast}].Name}

|-Mez Spell * Var Name: MezSpell string outer
    /if (${DoTwinCastMez[SETTINGVAL]}) {
        /call AbilitySet_Add "Chaotic Deception" MezSpell
        /call AbilitySet_Add "Chaotic Delusion" MezSpell
        /call AbilitySet_Add "Chaotic Bewildering" MezSpell
        /call AbilitySet_Add "Chaotic Confounding" MezSpell
        /call AbilitySet_Add "Chaotic Confusion" MezSpell
        /call AbilitySet_Add "Chaotic Baffling" MezSpell
        /call AbilitySet_Add "Chaotic Befuddling" MezSpell
        /call AbilitySet_Add "Chaotic Puzzlement" MezSpell
        /call AbilitySet_Add "Chaotic Conundrum" MezSpell
    }
    /call AbilitySet_Add "Deceive" MezSpell
    /call AbilitySet_Add "Delude" MezSpell
    /call AbilitySet_Add "Bewilder" MezSpell
    /call AbilitySet_Add "Confound" MezSpell
    /call AbilitySet_Add "Mislead" MezSpell
    /call AbilitySet_Add "Baffle" MezSpell
    /call AbilitySet_Add "Befuddle" MezSpell
    /call AbilitySet_Add "Mystify" MezSpell
    /call AbilitySet_Add "Bewilderment" MezSpell
    /call AbilitySet_Add "Euphoria" MezSpell
    /call AbilitySet_Add "Felicity" MezSpell
    /call AbilitySet_Add "Bliss" MezSpell
    /call AbilitySet_Add "Sleep" MezSpell
    /call AbilitySet_Add "Apathy" MezSpell
    /call AbilitySet_Add "Glamour of Kintaz" MezSpell
    /call AbilitySet_Add "Enthrall" MezSpell
    /call AbilitySet_Add "Mesmerize" MezSpell
    /call AbilitySet_ChooseOuter MezSpell MezSpell
    
|-AE Mez * Var Name: MezAESpell string outer
    /call AbilitySet_Add "Neutralizing Wave" MezAESpell
    /call AbilitySet_Add "Perplexing Wave" MezAESpell 
    /call AbilitySet_Add "Deadening Wave" MezAESpell 
    /call AbilitySet_Add "Slackening Wave" MezAESpell 
    /call AbilitySet_Add "Peaceful Wave" MezAESpell 
    /call AbilitySet_Add "Serene Wave" MezAESpell 
    /call AbilitySet_Add "Ensorcelling Wave" MezAESpell 
    /call AbilitySet_Add "Quelling Wave" MezAESpell 
    /call AbilitySet_Add "Wake of Subdual" MezAESpell 
    /call AbilitySet_Add "Wake of Felicity" MezAESpell 
    /call AbilitySet_Add "Bliss of the Nihil" MezAESpell 
    /call AbilitySet_Add "Fascination" MezAESpell 
    /call AbilitySet_Add "Mesmerization" MezAESpell
    /call AbilitySet_Add "Bewildering Wave" MezAESpell
    /call AbilitySet_Add "Stupefying Wave" MezAESpell 
    /call AbilitySet_ChooseOuter MezAESpell MezAESpell
    
|-Tash * Var Name: TashSpell string outer
    /call AbilitySet_Add "Roar of Tashan"   TashSpell
    /call AbilitySet_Add "Edict of Tashan" TashSpell
    /call AbilitySet_Add "Proclamation of Tashan" TashSpell
    /call AbilitySet_Add "Order of Tashan" TashSpell
    /call AbilitySet_Add "Decree of Tashan" TashSpell
    /call AbilitySet_Add "Enunciation of Tashan" TashSpell
    /call AbilitySet_Add "Declaration of Tashan" TashSpell
    /call AbilitySet_Add "Clamor of Tashan" TashSpell
    /call AbilitySet_Add "Bark of Tashan" TashSpell
    /call AbilitySet_Add "Din of Tashan" TashSpell
    /call AbilitySet_Add "Echo of Tashan" TashSpell
    /call AbilitySet_Add "Howl of Tashan" TashSpell
    /call AbilitySet_Add "Tashanian" TashSpell
    /call AbilitySet_Add "Tashania" TashSpell
    /call AbilitySet_Add "Tashani" TashSpell
    /call AbilitySet_Add "Tashina" TashSpell
    /call AbilitySet_ChooseOuter TashSpell TashSpell

|- Slow Cripple Combo Spell - Beginning @ Level 88
    /call AbilitySet_Add "Constraining Coil" CripSlowSpell
    /call AbilitySet_Add "Constraining Helix" CripSlowSpell
    /call AbilitySet_Add "Undermining Helix" CripSlowSpell
    /call AbilitySet_Add "Diminishing Helix" CripSlowSpell
    /call AbilitySet_Add "Attenuating Helix" CripSlowSpell
    /call AbilitySet_Add "Curtailing Helix" CripSlowSpell
    /call AbilitySet_Add "Inhibiting Helix" CripSlowSpell
    /call AbilitySet_ChooseOuter CripSlowSpell CripSlowSpell

|-Slow - * Var Name: SlowSpell string outer -  lvl88 and above this is also cripple spell Starting @ Level 88  Combines With Cripple.
    /call AbilitySet_Add "Desolate Deeds" SlowSpell
    /call AbilitySet_Add "Dreary Deeds" SlowSpell
    /call AbilitySet_Add "Forlorn Deeds" SlowSpell
    /call AbilitySet_Add "Shiftless Deeds" SlowSpell
    /call AbilitySet_Add "Tepid Deeds" SlowSpell
    /call AbilitySet_Add "Languid Pace" SlowSpell
    /call AbilitySet_ChooseOuter SlowSpell SlowSpell
    
|-Nuke 1 * Var Name: NukeSpell1 string outer >= LVL7
    /call AbilitySet_Add "Mindrend" NukeSpell
    /call AbilitySet_Add "Mindreap" NukeSpell
    /call AbilitySet_Add "Mindrift" NukeSpell
    /call AbilitySet_Add "Mindslash" NukeSpell
    /call AbilitySet_Add "Mindsunder" NukeSpell
    /call AbilitySet_Add "Mindcleave" NukeSpell
    /call AbilitySet_Add "Mindscythe" NukeSpell
    /call AbilitySet_Add "Mindblade" NukeSpell
    /call AbilitySet_Add "Spectral Assault" NukeSpell
    /call AbilitySet_Add "Polychaotic Assault" NukeSpell
    /call AbilitySet_Add "Multichromatic Assault" NukeSpell
    /call AbilitySet_Add "Polychromatic Assault" NukeSpell
    /call AbilitySet_Add "Colored Chaos" NukeSpell
    /call AbilitySet_Add "Psychosis" NukeSpell
    /call AbilitySet_Add "Madness of Ikkibi" NukeSpell
    /call AbilitySet_Add "Insanity" NukeSpell
    /call AbilitySet_Add "Dementing Visions" NukeSpell
    /call AbilitySet_Add "Dementia" NukeSpell
    /call AbilitySet_Add "Discordant Mind" NukeSpell
    /call AbilitySet_Add "Anarchy" NukeSpell
    /call AbilitySet_Add "Chaos Flux" NukeSpell
    /call AbilitySet_Add "Sanity Warp" NukeSpell
    /call AbilitySet_Add "Chaotic Feedback" NukeSpell
    /call AbilitySet_Add "Chromarcana" NukeSpell
    /call AbilitySet_Add "Ancient: Neurosis" NukeSpell
    /call AbilitySet_Add "Ancient: Chaos Madness" NukeSpell
    /call AbilitySet_Add "Ancient: Chaotic Visions" NukeSpell
    /call AbilitySet_ChooseOuter NukeSpell1 NukeSpell
    /call AbilitySet_ChooseOuter NukeSpell2 NukeSpell "${NukeSpell1}"
    
|- RUNE - Nuke  - Fast * Var Name: RuneNuke string outer >=LVL86
    /call AbilitySet_Add "Chromatic Spike" RuneNuke
    /call AbilitySet_Add "Chromatic Flare" RuneNuke
    /call AbilitySet_Add "Chromatic Stab" RuneNuke
    /call AbilitySet_Add "Chromatic Flicker" RuneNuke
    /call AbilitySet_Add "Chromatic Blink" RuneNuke
    /call AbilitySet_Add "Chromatic Percussion" RuneNuke
    /call AbilitySet_Add "Chromatic Flash" RuneNuke
    /call AbilitySet_Add "Chromatic Jab" RuneNuke
    /call AbilitySet_ChooseOuter RuneNuke RuneNuke "${NukeSpell1}|${NukeSpell2}"
    
|- Mana Drain Nuke - Fast * Var Name: ManaNuke string outer >=LVL96
    /call AbilitySet_Add "Psychological Appropriation" ManaNuke
    /call AbilitySet_Add "Ideological Appropriation" ManaNuke
    /call AbilitySet_Add "Psychic Appropriation" ManaNuke
    /call AbilitySet_Add "Intellectual Appropriation" ManaNuke
    /call AbilitySet_Add "Mental Appropriation" ManaNuke
    /call AbilitySet_Add "Cognitive Appropriation" ManaNuke
    /call AbilitySet_ChooseOuter ManaNuke ManaNuke

|- Chromatic Lowest Nuke - Normal * Var Name: ChromaNuke string outer >=LVL73
    /call AbilitySet_Add "Polycascading Assault" ChromaNuke
    /call AbilitySet_Add "Polyfluorescent Assault" ChromaNuke
    /call AbilitySet_Add "Polyrefractive Assault" ChromaNuke
    /call AbilitySet_Add "Phantasmal Assault" ChromaNuke
    /call AbilitySet_Add "Arcane Assault" ChromaNuke
    /call AbilitySet_Add "Spectral Assault" ChromaNuke
    /call AbilitySet_Add "Polychaotic Assault" ChromaNuke
    /call AbilitySet_Add "Multichromatic Assault" ChromaNuke
    /call AbilitySet_Add "Polychromatic Assault" ChromaNuke
    /call AbilitySet_ChooseOuter ChromaNuke ChromaNuke "${NukeSpell1}|${NukeSpell2}"

|-DoT 1 * Var Name: DoTSpell1 string outer >=LVL1
    /call AbilitySet_Add "Asphyxiating Grasp" DoTSpell1
    /call AbilitySet_Add "Throttling Grip" DoTSpell1
    /call AbilitySet_Add "Pulmonary Grip" DoTSpell1
    /call AbilitySet_Add "Strangulate" DoTSpell1
    /call AbilitySet_Add "Drown" DoTSpell1
    /call AbilitySet_Add "Stifle" DoTSpell1
    /call AbilitySet_Add "Suffocation" DoTSpell1
    /call AbilitySet_Add "Constrict" DoTSpell1
    /call AbilitySet_Add "Smother" DoTSpell1
    /call AbilitySet_Add "Strangling Air" DoTSpell1
    /call AbilitySet_Add "Thin Air" DoTSpell1
    /call AbilitySet_Add "Arcane Noose" DoTSpell1
    /call AbilitySet_Add "Strangle" DoTSpell1
    /call AbilitySet_Add "Asphyxiate" DoTSpell1
    /call AbilitySet_Add "Gasping Embrace" DoTSpell1
    /call AbilitySet_Add "Suffocate" DoTSpell1
    /call AbilitySet_Add "Choke" DoTSpell1
    /call AbilitySet_Add "Suffocating Sphere" DoTSpell1
    /call AbilitySet_Add "Shallow Breath" DoTSpell1
    /call AbilitySet_ChooseOuter DoTSpell1 DoTSpell1
    
|-DoT 2 * Var Name: ManaDot string outer >= LVL70
    /call AbilitySet_Add "Mind Whirl" ManaDot
    /call AbilitySet_Add "Mind Vortex" ManaDot
    /call AbilitySet_Add "Mind Coil" ManaDot
    /call AbilitySet_Add "Mind Tempest" ManaDot
    /call AbilitySet_Add "Mind Storm" ManaDot
    /call AbilitySet_Add "Mind Squall" ManaDot
    /call AbilitySet_Add "Mind Spiral" ManaDot
    /call AbilitySet_Add "Mind Helix" ManaDot
    /call AbilitySet_Add "Mind Twist" ManaDot
    /call AbilitySet_Add "Mind Oscillate" ManaDot
    /call AbilitySet_Add "Mind Phobiate" ManaDot
    /call AbilitySet_Add "Mind Shatter" ManaDot
    /call AbilitySet_ChooseOuter ManaDot ManaDot
    
|-DoT 3 * Var Name: DebuffDot string outer >= LVL89
    /call AbilitySet_Add "Dismaying Constriction" DebuffDot
    /call AbilitySet_Add "Perplexing Constriction" DebuffDot
    /call AbilitySet_Add "Deceiving Constriction" DebuffDot
    /call AbilitySet_Add "Deluding Constriction" DebuffDot
    /call AbilitySet_Add "Bewildering Constriction" DebuffDot
    /call AbilitySet_Add "Confounding Constriction" DebuffDot
    /call AbilitySet_Add "Confusing Constriction" DebuffDot
    /call AbilitySet_Add "Baffling Constriction" DebuffDot
    /call AbilitySet_ChooseOuter DebuffDot DebuffDot
    
|-Aura Buff 1 * Var Name: AuraBuff1 string outer
    /call AbilitySet_AddAura "Twincast Aura" "Twincast Aura" AuraBuff1
    /call AbilitySet_ChooseOuter AuraBuff1 AuraBuff1
    /varset AuraBuff1Name ${GetAuraName[${AuraBuff1},AuraBuff1]}

|-Aura Buff 2 * Var Name: AuraBuff2 string outer
    /call AbilitySet_AddAura "Mana Ripple Aura" "Mana Ripple" AuraBuff2
    /call AbilitySet_AddAura "Mana Radix Aura" "Mana Radix" AuraBuff2
    /call AbilitySet_AddAura "Mana Replication Aura" "Mana Replication" AuraBuff2
    /call AbilitySet_AddAura "Mana Repetition Aura" "Mana Repetition" AuraBuff2
    /call AbilitySet_AddAura "Mana Reciprocation Aura" "Mana Reciprocation" AuraBuff2
    /call AbilitySet_AddAura "Mana Reverberation Aura" "Mana Rev. Aura" AuraBuff2
    /call AbilitySet_AddAura "Mana Repercussion Aura" "Mana Rep. Aura" AuraBuff2
    /call AbilitySet_AddAura "Mana Reiteration Aura" "Mana Recursion" AuraBuff2
    /call AbilitySet_AddAura "Mana Reiterate Aura" "Mana Reiterate" AuraBuff2
    /call AbilitySet_AddAura "Mana Resurgence Aura" "Mana Resurgence" AuraBuff2
    /call AbilitySet_AddAura "Mystifier's Aura" "Mystifier's" AuraBuff2
    /call AbilitySet_AddAura "Entrancer's Aura" "Entrancer's" AuraBuff2
    /call AbilitySet_AddAura "Illusionist's Aura" "Illusionist's" AuraBuff2
    /call AbilitySet_AddAura "Beguiler's Aura" "Beguiler's" AuraBuff2
    /call AbilitySet_ChooseOuter AuraBuff2 AuraBuff2
    /varset AuraBuff2Name ${GetAuraName[${AuraBuff2},AuraBuff2]}
  
|-Aura Buff 3 * Var Name: AuraBuff3 string outer
    /call AbilitySet_AddAura "Learner's Aura" "Learner's" AuraBuff3
    /call AbilitySet_ChooseOuter AuraBuff3 AuraBuff3
    /varset AuraBuff3Name ${GetAuraName[${AuraBuff3},AuraBuff3]}

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
    /call AbilitySet_Add "Spellbound Shield" SelfHPBuff
    /call AbilitySet_Add "Sorcerous Shield" SelfHPBuff
    /call AbilitySet_Add "Mystic Shield" SelfHPBuff
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
    
|-Group Mana * Var Name: ManaRegen string outer
    /call AbilitySet_Add "Voice of Preordination" ManaRegen
    /call AbilitySet_Add "Voice of Perception" ManaRegen
    /call AbilitySet_Add "Voice of Sagacity" ManaRegen
    /call AbilitySet_Add "Voice of Perspicacity" ManaRegen
    /call AbilitySet_Add "Voice of Precognition" ManaRegen
    /call AbilitySet_Add "Voice of Foresight" ManaRegen
    /call AbilitySet_Add "Voice of Premeditation" ManaRegen
    /call AbilitySet_Add "Voice of Forethought" ManaRegen
    /call AbilitySet_Add "Voice of Prescience" ManaRegen
    /call AbilitySet_Add "Voice of Cognizance" ManaRegen
    /call AbilitySet_Add "Voice of Intuition" ManaRegen
    /call AbilitySet_Add "Voice of Clairvoyance" ManaRegen
    /call AbilitySet_Add "Voice of Quellious" ManaRegen
    /call AbilitySet_Add "Tranquility" ManaRegen
|   /call AbilitySet_Add "Gift of Brilliance" ManaRegen - Removed because the Map Defaults to it Instead of Koadics 
    /call AbilitySet_Add "Koadic's Endless Intellect" ManaRegen
    /call AbilitySet_Add "Gift of Pure Thought" ManaRegen
    /call AbilitySet_Add "Sagacity" ManaRegen
    /call AbilitySet_Add "Perspicacity" ManaRegen
    /call AbilitySet_Add "Precognition" ManaRegen
    /call AbilitySet_Add "Foresight" ManaRegen
    /call AbilitySet_Add "Premeditation" ManaRegen
    /call AbilitySet_Add "Forethought" ManaRegen
    /call AbilitySet_Add "Prescience" ManaRegen
    /call AbilitySet_Add "Seer's Cognizance" ManaRegen
    /call AbilitySet_Add "Seer's Intuition" ManaRegen
    /call AbilitySet_Add "Clairvoyance" ManaRegen
    /call AbilitySet_Add "Gift of Insight" ManaRegen
    /call AbilitySet_Add "Clarity II" ManaRegen
    /call AbilitySet_Add "Clarity" ManaRegen
    /call AbilitySet_Add "Breeze" ManaRegen
    /call AbilitySet_ChooseOuter ManaRegen ManaRegen
    
|-Group Haste * Var Name: HasteBuff string outer
    /call AbilitySet_Add "Hastening of Margator" HasteBuff
    /call AbilitySet_Add "Hastening of Jharin" HasteBuff
    /call AbilitySet_Add "Hastening of Cekenar" HasteBuff
    /call AbilitySet_Add "Hastening of Milyex" HasteBuff
    /call AbilitySet_Add "Hastening of Prokev" HasteBuff
    /call AbilitySet_Add "Hastening of Sviir" HasteBuff
    /call AbilitySet_Add "Hastening of Aransir" HasteBuff
    /call AbilitySet_Add "Hastening of Novak" HasteBuff
    /call AbilitySet_Add "Hastening of Erradien" HasteBuff
    /call AbilitySet_Add "Hastening of Ellowind" HasteBuff
    /call AbilitySet_Add "Hastening of Salik" HasteBuff
    /call AbilitySet_Add "Vallon's Quickening" HasteBuff
    /call AbilitySet_Add "Speed of the Brood" HasteBuff
    /call AbilitySet_Add "Speed of Cekenar" HasteBuff
    /call AbilitySet_Add "Speed of Milyex" HasteBuff
    /call AbilitySet_Add "Speed of Prokev" HasteBuff
    /call AbilitySet_Add "Speed of Sviir" HasteBuff
    /call AbilitySet_Add "Speed of Aransir" HasteBuff
    /call AbilitySet_Add "Speed of Novak" HasteBuff
    /call AbilitySet_Add "Speed of Erradien" HasteBuff
    /call AbilitySet_Add "Speed of Ellowind" HasteBuff
    /call AbilitySet_Add "Speed of Salik" HasteBuff
    /call AbilitySet_Add "Speed of Vallon" HasteBuff
    /call AbilitySet_Add "Visions of Grandeur" HasteBuff
    /call AbilitySet_Add "Wondrous Rapidity" HasteBuff
    /call AbilitySet_Add "Aanya's Quickening" HasteBuff
    /call AbilitySet_Add "Swift Like the Wind" HasteBuff
    /call AbilitySet_Add "Celerity" HasteBuff
    /call AbilitySet_Add "Augmentation" HasteBuff
    /call AbilitySet_Add "Alacrity" HasteBuff
    /call AbilitySet_Add "Quickness" HasteBuff
    /call AbilitySet_ChooseOuter HasteBuff HasteBuff
    
|- Unity Self Rune * Var Name: UnityRune string outer =>115
    /call AbilitySet_Add "Esoteric Unity" UnityRune
    /call AbilitySet_Add "Deviser's Unity" UnityRune
    /call AbilitySet_Add "Marvel's Unity"  UnityRune
    /call AbilitySet_ChooseOuter UnityRune UnityRune
    
|-Self Rune 1 * Var Name: SelfRune1 string outer
    /call AbilitySet_Add "Esoteric Rune" SelfRune1
    /call AbilitySet_Add "Marvel's Rune" SelfRune1
    /call AbilitySet_Add "Deviser's Rune" SelfRune1
    /call AbilitySet_Add "Transfixer's Rune" SelfRune1
    /call AbilitySet_Add "Enticer's Rune" SelfRune1
    /call AbilitySet_Add "Mastermind's Rune" SelfRune1
    /call AbilitySet_Add "Arcanaward's Rune" SelfRune1
    /call AbilitySet_Add "Spectral Rune" SelfRune1
    /call AbilitySet_Add "Pearlescent Rune" SelfRune1
    /call AbilitySet_Add "Opalescent Rune" SelfRune1
    /call AbilitySet_Add "Draconic Rune" SelfRune1
    /call AbilitySet_Add "Ethereal Rune" SelfRune1
    /call AbilitySet_Add "Arcane Rune" SelfRune1
    /call AbilitySet_ChooseOuter SelfRune1 SelfRune1
    
|-Self Rune 2 * Var Name: SelfRune2 string outer
    /call AbilitySet_Add "Polyradiant Rune" SelfRune2
    /call AbilitySet_Add "Polyluminous Rune" SelfRune2
    /call AbilitySet_Add "Polycascading Rune" SelfRune2
    /call AbilitySet_Add "Polyfluorescent Rune" SelfRune2
    /call AbilitySet_Add "Polyrefractive Rune" SelfRune2
    /call AbilitySet_Add "Polyiridescent Rune" SelfRune2
    /call AbilitySet_Add "Polyarcanic Rune" SelfRune2
    /call AbilitySet_Add "Polyspectral Rune" SelfRune2
    /call AbilitySet_Add "Polychaotic Rune" SelfRune2
    /call AbilitySet_Add "Multichromatic Rune" SelfRune2
    /call AbilitySet_Add "Polychromatic Rune" SelfRune2
    /call AbilitySet_ChooseOuter SelfRune2 SelfRune2
    
|-Single Rune * Var Name: SingleRune string outer
    /call AbilitySet_Add "Rune of Zoraxmen" SingleRune
    /call AbilitySet_Add "Rune of Tearc" SingleRune
    /call AbilitySet_Add "Rune of Kildrukaun" SingleRune
    /call AbilitySet_Add "Rune of Skrizix" SingleRune
    /call AbilitySet_Add "Rune of Lucem" SingleRune
    /call AbilitySet_Add "Rune of Xolok" SingleRune
    /call AbilitySet_Add "Rune of Tonmek" SingleRune
    /call AbilitySet_Add "Rune of Novak" SingleRune
    /call AbilitySet_Add "Rune of Yozan" SingleRune
    /call AbilitySet_Add "Rune of Erradien" SingleRune
    /call AbilitySet_Add "Rune of Ellowind" SingleRune
    /call AbilitySet_Add "Rune of Salik" SingleRune
    /call AbilitySet_Add "Rune of Zebuxoruk" SingleRune
    /call AbilitySet_Add "Rune V" SingleRune
    /call AbilitySet_Add "Rune IV" SingleRune
    /call AbilitySet_Add "Rune III" SingleRune
    /call AbilitySet_Add "Rune II" SingleRune
    /call AbilitySet_Add "Rune I" SingleRune
    /call AbilitySet_ChooseOuter SingleRune SingleRune
    
|-Mez Buff * Var Name: MezBuff string outer
    /call AbilitySet_Add "Ward of the Stupefier" MezBuff
    /call AbilitySet_Add "Ward of the Beguiler" MezBuff
    /call AbilitySet_Add "Ward of the Deviser" MezBuff
    /call AbilitySet_Add "Ward of the Transfixer" MezBuff
    /call AbilitySet_Add "Ward of the Enticer" MezBuff
    /call AbilitySet_Add "Ward of the Mastermind" MezBuff
    /call AbilitySet_Add "Ward of Arctending" MezBuff
    /call AbilitySet_Add "Ward of Bafflement" MezBuff
    /call AbilitySet_Add "Ward of Befuddlement" MezBuff
    /call AbilitySet_Add "Ward of Mystifying" MezBuff
    /call AbilitySet_Add "Ward of Bewilderment" MezBuff
    /call AbilitySet_Add "Ward of Bedazzlement" MezBuff
    /call AbilitySet_ChooseOuter MezBuff MezBuff

|-Proc Buff * Var Name: NdtBuff string outer >=LVL40 Must Be On bar
    /call AbilitySet_Add "Night's Perpetual Terror" NdtBuff
    /call AbilitySet_Add "Night's Endless Terror" NdtBuff
    /call AbilitySet_Add "Night's Dark Terror" NdtBuff
    /call AbilitySet_Add "Boon of the Garou" NdtBuff
    /call AbilitySet_ChooseOuter NdtBuff NdtBuff

|-Charm Spell * Var Name: CharmSpell string outer
    /call AbilitySet_Add "Esoteric Command" CharmSpell
    /call AbilitySet_Add "Marvel's Demand" CharmSpell
    /call AbilitySet_Add "Marvel's Command" CharmSpell
    /call AbilitySet_Add "Inveigle" CharmSpell
    /call AbilitySet_Add "Deviser's Demand" CharmSpell
    /call AbilitySet_Add "Deviser's Command" CharmSpell
    /call AbilitySet_Add "Transfixer's Command" CharmSpell
    /call AbilitySet_Add "Spellbinding" CharmSpell
    /call AbilitySet_Add "Enticer's Command" CharmSpell
    /call AbilitySet_Add "Enticer's Demand" CharmSpell
    /call AbilitySet_Add "Captivation" CharmSpell
    /call AbilitySet_Add "Impose" CharmSpell
    /call AbilitySet_Add "Temptation" CharmSpell
    /call AbilitySet_Add "Enforce" CharmSpell
    /call AbilitySet_Add "Compelling Edict" CharmSpell
    /call AbilitySet_Add "Subjugate" CharmSpell
    /call AbilitySet_Add "Deception" CharmSpell
    /call AbilitySet_Add "Dominate" CharmSpell
    /call AbilitySet_Add "Seduction" CharmSpell
    /call AbilitySet_Add "Haunting Whispers" CharmSpell
    /call AbilitySet_Add "Cajole" CharmSpell
    /call AbilitySet_Add "Dyn`leth's Whispers" CharmSpell
    /call AbilitySet_Add "Coax" CharmSpell
    |- /call AbilitySet_Add "Ancient Voice of Muram" CharmSpell
    /call AbilitySet_Add "True Name" CharmSpell
    /call AbilitySet_Add "Compel" CharmSpell
    /call AbilitySet_Add "Command of Druzzil" CharmSpell
    /call AbilitySet_Add "Beckon" CharmSpell
    /call AbilitySet_Add "Dictate" CharmSpell
    /call AbilitySet_Add "Boltran's Agacerie" CharmSpell
    /call AbilitySet_Add "Ordinance" CharmSpell
    /call AbilitySet_Add "Allure" CharmSpell
    /call AbilitySet_Add "Cajoling Whispers" CharmSpell
    /call AbilitySet_Add "Beguile" CharmSpell
    /call AbilitySet_Add "Charm" CharmSpell
    /call AbilitySet_ChooseOuter CharmSpell CharmSpell
    
|-Cripple Spell * Var Name: CrippleSpell string outer >= LVL4 Starting @ Level 88 combines with Slow Spells.
    /call AbilitySet_Add "Splintered Consciousness" CrippleSpell
    /call AbilitySet_Add "Fragmented Consciousness" CrippleSpell
    /call AbilitySet_Add "Shattered Consciousness" CrippleSpell
    /call AbilitySet_Add "Fractured Consciousness" CrippleSpell
    /call AbilitySet_Add "Synapsis Spasm" CrippleSpell
    /call AbilitySet_Add "Cripple" CrippleSpell
    /call AbilitySet_Add "Incapacitate" CrippleSpell
    /call AbilitySet_Add "Listless Power" CrippleSpell
    /call AbilitySet_Add "Disempower" CrippleSpell
    /call AbilitySet_Add "Enfeeblement" CrippleSpell
    /call AbilitySet_ChooseOuter CrippleSpell CrippleSpell
    
|-Strip Buff Spell * Var Name: StripBuffSpell string outer >= LVL1
    /call AbilitySet_Add "Eradicate Magic" StripBuffSpell
    /call AbilitySet_Add "Recant Magic" StripBuffSpell
    /call AbilitySet_Add "Pillage Enchantment" StripBuffSpell
    /call AbilitySet_Add "Nullify Magic" StripBuffSpell
    /call AbilitySet_Add "Strip Enchantment" StripBuffSpell
    /call AbilitySet_Add "Cancel Magic" StripBuffSpell
    /call AbilitySet_Add "Taper Enchantment" StripBuffSpell
    /call AbilitySet_ChooseOuter StripBuffSpell StripBuffSpell
    
|-Pet Spell * Var Name: PetSpell string outer
    /call AbilitySet_Add "Flariton's Animation" PetSpell
    /call AbilitySet_Add "Constance's Animation" PetSpell
    /call AbilitySet_Add "Omica's Animation" PetSpell
    /call AbilitySet_Add "Nureya's Animation" PetSpell
    /call AbilitySet_Add "Gordianus' Animation" PetSpell
    /call AbilitySet_Add "Xorlex's Animation" PetSpell
    /call AbilitySet_Add "Seronvall's Animation" PetSpell
    /call AbilitySet_Add "Novak's Animation" PetSpell
    /call AbilitySet_Add "Yozan's Animation" PetSpell
    /call AbilitySet_Add "Erradien's Animation" PetSpell
    /call AbilitySet_Add "Ellowind's Animation" PetSpell
    /call AbilitySet_Add "Salik's Animation" PetSpell
    /call AbilitySet_Add "Aeldorb's Animation" PetSpell
    /call AbilitySet_Add "Zumaik's Animation" PetSpell
    /call AbilitySet_Add "Kintaz's Animation" PetSpell
    /call AbilitySet_Add "Yegoreff's Animation" PetSpell
    /call AbilitySet_Add "Aanya's Animation" PetSpell
    /call AbilitySet_Add "Boltran's Animation" PetSpell
    /call AbilitySet_Add "Uleen's Animation" PetSpell
    /call AbilitySet_Add "Sagar's Animation" PetSpell
    /call AbilitySet_Add "Sisna's Animation" PetSpell
    /call AbilitySet_Add "Shalee's Animation" PetSpell
    /call AbilitySet_Add "Kilan's Animation" PetSpell
    /call AbilitySet_Add "Mircyl's Animation" PetSpell
    /call AbilitySet_Add "Juli's Animation" PetSpell
    /call AbilitySet_Add "Pendril's Animation" PetSpell
    /call AbilitySet_ChooseOuter PetSpell PetSpell
    
|-Pet Buff Spell * Var Name: PetBuffSpell string outer
    /call AbilitySet_Add "Speed of Margator"    PetBuffSpell
    /call AbilitySet_Add "Speed of Vallon"      PetBuffSpell
    /call AbilitySet_Add "Visions of Grandeur"  PetBuffSpell
    /call AbilitySet_Add "Wondrous Rapidity"    PetBuffSpell
    /call AbilitySet_Add "Aanya's Quickening"   PetBuffSpell
    /call AbilitySet_Add "Swift Like the Wind"  PetBuffSpell
    /call AbilitySet_Add "Celerity"             PetBuffSpell
    /call AbilitySet_Add "Augmentation"         PetBuffSpell
    /call AbilitySet_Add "Alacrity"             PetBuffSpell
    /call AbilitySet_Add "Quickness"            PetBuffSpell 
    /call AbilitySet_Add "Infused Minion"       PetBuffSpell
    /call AbilitySet_Add "Empowered Minion"     PetBuffSpell
    /call AbilitySet_Add "Invigorated Minion"   PetBuffSpell
    |- Speed of the Brood won't take effect properly on pets. Unless u Purchase the AA
    /call AbilitySet_ChooseOuter PetBuffSpell PetBuffSpell "Speed of the Brood" 
    
|-Dicho Spell * Var Name: DichoSpell string outer
    /call AbilitySet_Add "Ecliptic Reinforcement" DichoSpell
    /call AbilitySet_Add "Composite Reinforcement" DichoSpell
    /call AbilitySet_Add "Dissident Reinforcement" DichoSpell
    /call AbilitySet_Add "Dichotomic Reinforcement" DichoSpell
    /call AbilitySet_ChooseOuter DichoSpell DichoSpell
    
|-Group Rune * Var Name: GroupRune string outer
    /call AbilitySet_Add "Gloaming Rune" GroupRune
    /call AbilitySet_Add "Eclipsed Rune" GroupRune
    /call AbilitySet_Add "Crepuscular Rune" GroupRune
    /call AbilitySet_Add "Tenebrous Rune" GroupRune
    /call AbilitySet_Add "Darkened Rune" GroupRune
    /call AbilitySet_Add "Umbral Rune" GroupRune
    /call AbilitySet_Add "Shadowed Rune" GroupRune
    /call AbilitySet_Add "Twilight Rune" GroupRune
    /call AbilitySet_Add "Rune of the Void" GroupRune
    /call AbilitySet_Add "Rune of the Deep" GroupRune
    /call AbilitySet_Add "Rune of the Kedge" GroupRune
    /call AbilitySet_Add "Rune of Rikkukin" GroupRune
    /call AbilitySet_Add "Rune of the Scale" GroupRune
    /call AbilitySet_ChooseOuter GroupRune GroupRune
    
|-Aggro Rune * Var Name: AggroRune string outer
    /call AbilitySet_Add "Disquieting Rune" AggroRune
    /call AbilitySet_Add "Ghastly Rune" AggroRune
    /call AbilitySet_Add "Horrendous Rune" AggroRune
    /call AbilitySet_Add "Dreadful Rune" AggroRune
    /call AbilitySet_Add "Frightening Rune" AggroRune
    /call AbilitySet_Add "Terrifying Rune" AggroRune
    /call AbilitySet_Add "Horrifying Rune" AggroRune
    /call AbilitySet_ChooseOuter AggroRune AggroRune
    
|-Aggro Buff * Var Name: AggroBuff string outer
    /call AbilitySet_Add "Horrifying Visage" AggroBuff
    /call AbilitySet_Add "Haunting Visage" AggroBuff
    /call AbilitySet_ChooseOuter AggroBuff AggroBuff
    
|-Single Spell Shield * Var Name: SingleSpellShield string outer
    /call AbilitySet_Add "Aegis of Elmara" SingleSpellShield
    /call AbilitySet_Add "Aegis of Sefra" SingleSpellShield
    /call AbilitySet_Add "Aegis of Omica" SingleSpellShield
    /call AbilitySet_Add "Aegis of Nureya" SingleSpellShield
    /call AbilitySet_Add "Aegis of Gordianus" SingleSpellShield
    /call AbilitySet_Add "Aegis of Xorbb" SingleSpellShield
    /call AbilitySet_Add "Aegis of Soliadal" SingleSpellShield
    /call AbilitySet_Add "Aegis of Zykean" SingleSpellShield
    /call AbilitySet_Add "Aegis of Xadrith" SingleSpellShield
    /call AbilitySet_Add "Aegis of Qandieal" SingleSpellShield
    /call AbilitySet_Add "Aegis of Alendar" SingleSpellShield
    /call AbilitySet_Add "Wall of Alendar" SingleSpellShield
    /call AbilitySet_Add "Bulwark of Alendar" SingleSpellShield
    /call AbilitySet_Add "Protection of Alendar" SingleSpellShield
    /call AbilitySet_Add "Guard of Alendar" SingleSpellShield
    /call AbilitySet_Add "Ward of Alendar" SingleSpellShield
    /call AbilitySet_ChooseOuter SingleSpellShield SingleSpellShield
    
|-Group Spell Shield * Var Name: GroupSpellShield string outer
    /call AbilitySet_Add "Legion of Ogna" GroupSpellShield
    /call AbilitySet_Add "Legion of Liako" GroupSpellShield
    /call AbilitySet_Add "Legion of Kildrukaun" GroupSpellShield
    /call AbilitySet_Add "Legion of Skrizix" GroupSpellShield
    /call AbilitySet_Add "Legion of Lucem" GroupSpellShield
    /call AbilitySet_Add "Legion of Xolok" GroupSpellShield
    /call AbilitySet_Add "Legion of Tonmek" GroupSpellShield
    /call AbilitySet_Add "Legion of Zykean" GroupSpellShield
    /call AbilitySet_Add "Legion of Xadrith" GroupSpellShield
    /call AbilitySet_Add "Legion of Qandieal" GroupSpellShield
    /call AbilitySet_Add "Legion of Alendar" GroupSpellShield
    /call AbilitySet_Add "Circle of Alendar" GroupSpellShield
    /call AbilitySet_ChooseOuter GroupSpellShield GroupSpellShield
    
|-Sing DoT Shield * Var Name: SingleDoTShield string outer
    /call AbilitySet_Add "Aegis of Xetheg" SingleDoTShield
    /call AbilitySet_Add "Aegis of Cekenar" SingleDoTShield
    /call AbilitySet_Add "Aegis of Milyex" SingleDoTShield
    /call AbilitySet_Add "Aegis of the Indagator" SingleDoTShield
    /call AbilitySet_Add "Aegis of the Keeper" SingleDoTShield
    /call AbilitySet_ChooseOuter SingleDoTShield SingleDoTShield
    
|-Group DoT Shield * Var Name: GroupDoTShield string outer
    /call AbilitySet_Add "Legion of Dhakka" GroupDoTShield
    /call AbilitySet_Add "Legion of Xetheg" GroupDoTShield
    /call AbilitySet_Add "Legion of Cekenar" GroupDoTShield
    /call AbilitySet_Add "Legion of Milyex" GroupDoTShield
    /call AbilitySet_Add "Legion of the Indagator" GroupDoTShield
    /call AbilitySet_Add "Legion of the Keeper" GroupDoTShield
    /call AbilitySet_ChooseOuter GroupDoTShield GroupDoTShield
    
|-Group Auspice - Dmg Shield Reduction + DoT Shield * Var Name: GroupAuspiceBuff string outer
    /call AbilitySet_Add "Marvel's Auspice" GroupAuspiceBuff
    /call AbilitySet_Add "Deviser's Auspice" GroupAuspiceBuff
    /call AbilitySet_Add "Transfixer's Auspice" GroupAuspiceBuff
    /call AbilitySet_Add "Enticer's Auspice" GroupAuspiceBuff
    /call AbilitySet_ChooseOuter GroupAuspiceBuff GroupAuspiceBuff
 
|-Sing Melee Shield * Var Name: SingleMeleeShield string outer
    /call AbilitySet_Add "Gloaming Auspice" SingleMeleeShield
    /call AbilitySet_Add "Eclipsed Auspice" SingleMeleeShield
    /call AbilitySet_Add "Crepuscular Auspice" SingleMeleeShield
    /call AbilitySet_Add "Tenebrous Auspice" SingleMeleeShield
    /call AbilitySet_Add "Darkened Auspice" SingleMeleeShield
    /call AbilitySet_Add "Umbral Auspice" SingleMeleeShield
    /call AbilitySet_ChooseOuter SingleMeleeShield SingleMeleeShield
    
|-Self Guard Shield * Var Name: SelfGuardShield string outer
    /call AbilitySet_Add "Shield of Inescapability" SelfGuardShield
    /call AbilitySet_Add "Shield of Shadow" SelfGuardShield
    /call AbilitySet_Add "Shield of Destiny" SelfGuardShield
    /call AbilitySet_Add "Shield of Order" SelfGuardShield
    /call AbilitySet_Add "Shield of Consequence" SelfGuardShield
    /call AbilitySet_Add "Shield of Fate" SelfGuardShield
    /call AbilitySet_ChooseOuter SelfGuardShield SelfGuardShield
    
|-PBAE Stun Spell * Var Name: PBAEStunSpell string outer >=LVL3
    /call AbilitySet_Add "Color Calibration" PBAEStunSpell
    /call AbilitySet_Add "Color Conflagration" PBAEStunSpell
    /call AbilitySet_Add "Color Cascade" PBAEStunSpell
    /call AbilitySet_Add "Color Congruence" PBAEStunSpell
    /call AbilitySet_Add "Color Concourse" PBAEStunSpell
    /call AbilitySet_Add "Color Confluence" PBAEStunSpell
    /call AbilitySet_Add "Color Convergence" PBAEStunSpell
    /call AbilitySet_Add "Color Clash" PBAEStunSpell
    /call AbilitySet_Add "Color Conflux" PBAEStunSpell
    /call AbilitySet_Add "Color Cataclysm" PBAEStunSpell
    /call AbilitySet_Add "Color Collapse" PBAEStunSpell
    /call AbilitySet_Add "Color Snap" PBAEStunSpell
    /call AbilitySet_Add "Color Cloud" PBAEStunSpell
    /call AbilitySet_Add "Color Slant" PBAEStunSpell
    /call AbilitySet_Add "Color Skew" PBAEStunSpell
    /call AbilitySet_Add "Color Shift" PBAEStunSpell
    /call AbilitySet_Add "Color Flux" PBAEStunSpell 
    /call AbilitySet_ChooseOuter PBAEStunSpell PBAEStunSpell
    
|-Target AE Stun * Var Name: TargetAEStun string outer >=LVL92
    /call AbilitySet_Add "Remote Color Calibration" TargetAEStun
    /call AbilitySet_Add "Remote Color Conflagration" TargetAEStun
    /call AbilitySet_Add "Remote Color Cascade" TargetAEStun
    /call AbilitySet_Add "Remote Color Congruence" TargetAEStun
    /call AbilitySet_Add "Remote Color Concourse" TargetAEStun
    /call AbilitySet_Add "Remote Color Confluence" TargetAEStun
    /call AbilitySet_Add "Remote Color Convergence" TargetAEStun
    /call AbilitySet_ChooseOuter TargetAEStun TargetAEStun
    
|-Single Stun Spell * Var Name: SingleStunSpell1 string outer >= LVL9
    /call AbilitySet_Add "Dizzying Spindle" SingleStunSpell1
    /call AbilitySet_Add "Dizzying Vortex" SingleStunSpell1
    /call AbilitySet_Add "Dizzying Coil" SingleStunSpell1
    /call AbilitySet_Add "Dizzying Wheel" SingleStunSpell1
    /call AbilitySet_Add "Dizzying Storm" SingleStunSpell1
    /call AbilitySet_Add "Dizzying Squall" SingleStunSpell1
    /call AbilitySet_Add "Dizzying Gyre" SingleStunSpell1
    /call AbilitySet_Add "Dizzying Helix" SingleStunSpell1
    /call AbilitySet_Add "The Downward Spiral" SingleStunSpell1
    /call AbilitySet_Add "Whirling into the Hollow" SingleStunSpell1
    /call AbilitySet_Add "Spinning into the Void" SingleStunSpell1
    /call AbilitySet_Add "Largarn's Lamentation" SingleStunSpell1
    /call AbilitySet_Add "Dyn's Dizzying Draught" SingleStunSpell1
    /call AbilitySet_Add "Whirl till you hurl" SingleStunSpell1
    /call AbilitySet_ChooseOuter SingleStunSpell1 SingleStunSpell1

|-Mana Drain DoT * Var Name: ManaDrainSpell string outer >=LVL30
    /call AbilitySet_Add "Tears of Kasha" ManaDrainSpell
    /call AbilitySet_Add "Tears of Xenacious" ManaDrainSpell
    /call AbilitySet_Add "Tears of Aaryonar" ManaDrainSpell
    /call AbilitySet_Add "Tears of Skrizix" ManaDrainSpell
    /call AbilitySet_Add "Tears of Visius" ManaDrainSpell
    /call AbilitySet_Add "Tears of Syrkl" ManaDrainSpell
    /call AbilitySet_Add "Tears of Wreliard" ManaDrainSpell
    /call AbilitySet_Add "Tears of Zykean" ManaDrainSpell
    /call AbilitySet_Add "Tears of Xadrith" ManaDrainSpell
    /call AbilitySet_Add "Tears of Qandieal" ManaDrainSpell
    /call AbilitySet_Add "Torment of Scio" ManaDrainSpell
    /call AbilitySet_Add "Torment of Argli" ManaDrainSpell
    /call AbilitySet_Add "Scryer's Trespass" ManaDrainSpell
    /call AbilitySet_Add "Wandering Mind" ManaDrainSpell
    /call AbilitySet_Add "Mana Sieve" ManaDrainSpell
    /call AbilitySet_ChooseOuter ManaDrainSpell ManaDrainSpell
    
|-AE Mez Fast Cast * Var Name: MezAESpellFast string outer
    /call AbilitySet_Add "Vexing Glance" MezAESpellFast
    /call AbilitySet_Add "Confounding Glance" MezAESpellFast
    /call AbilitySet_Add "Neutralizing Glance" MezAESpellFast
    /call AbilitySet_Add "Perplexing Glance" MezAESpellFast
    /call AbilitySet_Add "Slackening Glance" MezAESpellFast
    /call AbilitySet_ChooseOuter MezAESpellFast MezAESpellFast

|-PBAE Mez Spell * Var Name: MezPBAESpell string outer >=LVL30
    /call AbilitySet_Add "Neutralize" MezPBAESpell
    /call AbilitySet_Add "Perplex" MezPBAESpell
    /call AbilitySet_Add "Bafflement" MezPBAESpell
    /call AbilitySet_Add "Disorientation" MezPBAESpell
    /call AbilitySet_Add "Confusion" MezPBAESpell
    /call AbilitySet_Add "Serenity" MezPBAESpell
    /call AbilitySet_Add "Docility" MezPBAESpell
    /call AbilitySet_Add "Visions of Kirathas" MezPBAESpell
    /call AbilitySet_Add "Dreams of Veldyn" MezPBAESpell
    /call AbilitySet_Add "Circle of Dreams" MezPBAESpell
    /call AbilitySet_Add "Word of Morell" MezPBAESpell
    /call AbilitySet_Add "Entrancing Lights" MezPBAESpell
    /call AbilitySet_Add "Bewilderment" MezPBAESpell
    /call AbilitySet_Add "Wonderment" MezPBAESpell
    /call AbilitySet_ChooseOuter MezPBAESpell MezPBAESpell
    
|-Single Mez Fast Cast * Var Name: MezSpellFast string outer
    /call AbilitySet_Add "Deceiving Flash" MezSpellFast
    /call AbilitySet_Add "Deluding Flash" MezSpellFast
    /call AbilitySet_Add "Bewildering Flash" MezSpellFast
    /call AbilitySet_Add "Confounding Flash" MezSpellFast
    /call AbilitySet_Add "Misleading Flash" MezSpellFast
    /call AbilitySet_Add "Baffling Flash" MezSpellFast
    /call AbilitySet_Add "Befuddling Flash" MezSpellFast
    /call AbilitySet_Add "Mystifying Flash" MezSpellFast
    /call AbilitySet_Add "Perplexing Flash" MezSpellFast
    /call AbilitySet_Add "Addling Flash" MezSpellFast
    /call AbilitySet_Add "Flummoxing Flash" MezSpellFast
    /call AbilitySet_ChooseOuter MezSpellFast MezSpellFast

|-Mem Blur Single * Var Name: BlurSpell string outer >= LVL10
    /call AbilitySet_Add "Memory Flux" BlurSpell
    /call AbilitySet_Add "Reoccurring Amnesia" BlurSpell
    /call AbilitySet_Add "Memory Blur" BlurSpell
    /call AbilitySet_ChooseOuter BlurSpell BlurSpell
    
|-Mem Blur AoE * Var Name: AEBlurSpell string outer
    /call AbilitySet_Add "Blanket of Forgetfulness" AEBlurSpell
    /call AbilitySet_Add "Mind Wipe" AEBlurSpell
    /call AbilitySet_ChooseOuter AEBlurSpell AEBlurSpell
    
|-Calm Spell * Var Name: CalmSpell string outer >= LVL1
    /call AbilitySet_Add "Docile Mind" CalmSpell
    /call AbilitySet_Add "Still Mind" CalmSpell
    /call AbilitySet_Add "Serene Mind" CalmSpell
    /call AbilitySet_Add "Mollified Mind" CalmSpell
    /call AbilitySet_Add "Pacified Mind" CalmSpell
    /call AbilitySet_Add "Quiescent Mind" CalmSpell
    /call AbilitySet_Add "Halcyon Mind" CalmSpell
    /call AbilitySet_Add "Bucolic Mind" CalmSpell
    /call AbilitySet_Add "Hushed Mind" CalmSpell
    /call AbilitySet_Add "Silent Mind" CalmSpell
    /call AbilitySet_Add "Quiet Mind" CalmSpell
    /call AbilitySet_Add "Placate" CalmSpell
    /call AbilitySet_Add "Pacification" CalmSpell
    /call AbilitySet_Add "Pacify" CalmSpell
    /call AbilitySet_Add "Calm" CalmSpell
    /call AbilitySet_Add "Soothe" CalmSpell
    /call AbilitySet_Add "Lull" CalmSpell
    /call AbilitySet_ChooseOuter CalmSpell CalmSpell
    
|-Fear Spell * Var Name: FearSpell string outer >= LVL3
    /call AbilitySet_Add "Anxiety Attack" FearSpell
    /call AbilitySet_Add "Jitterskin" FearSpell
    /call AbilitySet_Add "Phobia" FearSpell
    /call AbilitySet_Add "Trepidation" FearSpell
    /call AbilitySet_Add "Invoke Fear" FearSpell
    /call AbilitySet_Add "Chase the Moon" FearSpell
    /call AbilitySet_Add "Fear" FearSpell
    /call AbilitySet_ChooseOuter FearSpell FearSpell
    
|-Root Spell * Var Name: RootSpell string outer >= LVL6
    /call AbilitySet_Add "Greater Fetter" RootSpell
    /call AbilitySet_Add "Fetter" RootSpell
    /call AbilitySet_Add "Paralyzing Earth" RootSpell
    /call AbilitySet_Add "Immobilize" RootSpell
    /call AbilitySet_Add "Instill" RootSpell
    /call AbilitySet_Add "Root" RootSpell
    /call AbilitySet_ChooseOuter RootSpell RootSpell
| - Alliance Spell
    /call AbilitySet_Add "Chromatic Conjunction" AllianceSpell
    /call AbilitySet_Add "Chromatic Coalition" AllianceSpell
    /call AbilitySet_Add "Chromatic Covenant" AllianceSpell
    /call AbilitySet_Add "Chromatic Alliance" AllianceSpell
    /call AbilitySet_ChooseOuter AllianceSpell AllianceSpell
    
/return 
|* ------------------------------------------------------------------------------------------
|- SUB: ModeConfigMODEMEZ
|- Unused Spells in Ench.Mac:
|- PBAEStunSpell
|- MezPBAESpell
|- RootSpell
|------------------------------------------------------------------------------------------ *|
Sub ENC_ModeConfigMODEMEZ
    /varset IsMezzing TRUE

    /echo Leveraging ${Me.Class.Name} MEZ Mode
    /varset Spell1 ${MezSpell}
    /varset Spell2 ${MezAESpell}
    /varset Spell3 ${TashSpell}
    /if (${RG_CanUseAA[Slowing Helix]} == FALSE && ${Me.Level} < 88) {
        /varset Spell4 ${SlowSpell}
    } else {
        /varset Spell4 ${ManaNuke}
    }
    /varset Spell5 ${NdtBuff}
    /varset Spell6 ${NukeSpell1}
    /varset Spell7 ${DoTSpell1}
    /if (${DoCripple[SETTINGVAL]} && ${Me.Level} < 88) {
        /varset Spell8 ${CrippleSpell}
    } else /if ( ${DoStripBuff[SETTINGVAL]} ) {
        /varset Spell8 ${StripBuffSpell}
    } else {
        /varset Spell8 ${NukeSpell2}
    }
    /varset Spell9 ${ManaDot}
    /varset Spell10 ${RuneNuke}
    /varset Spell11 ${DebuffDot}
    /varset Spell12 ${DichoSpell}
    /if (${DoAlliance[SETTINGVAL]}) {
        /varset Spell13 ${AllianceSpell}
    } else {
        /varset Spell13 ${ManaDrainSpell}
    }

    |-- The first 9 AA's are Aggro controls
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Glyphy Spray"    AA   ${Parse[0,"( (${Target.Named} && ${Target.Level}>${Me.Level}) || (${Spawn[id ${assistid}].PctHPs}<45 && ${Spawn[id ${assistid}].PctHPs}>5) )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Reactive Rune"    AA   ${Parse[0,"( (${Target.Named} && ${Target.Level}>${Me.Level}) || (${Spawn[id ${assistid}].PctHPs}<45 && ${Spawn[id ${assistid}].PctHPs}>5) )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Self Stasis" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 30 )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Dimensional Instability" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 30 )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Beguiler's Directed Banishment" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 40 )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Beguiler's Banishment" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 50 && ${SpawnCount[npc radius 20]} > 2)"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Doppelganger" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 60 )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Phantasmal Opponent" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 60 )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Dimensional Shield" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 80 )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Arcane Whisper" AA ${Parse[0,"( ${Me.PctAggro}>=90 )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Silent Casting" AA ${Parse[0,"( ${Me.PctAggro}>=90 )"]}
    
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "Focus of Arcanum"    AA   ${Parse[0,"( TRUE )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "${DebuffDot}"    Spell   ${Parse[0,"( ${DoDot[SETTINGVAL]} && !${Target.Buff[${DebuffDot}].ID} &&  ( ${Target.PctHPs} > ${HPStopDOT[SETTINGVAL]}) )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "${ManaDot}"    Spell   ${Parse[0,"( ${DoDot[SETTINGVAL]} && !${Target.Buff[${ManaDot}].ID} && ( ${Target.PctHPs} > ${HPStopDOT[SETTINGVAL]}) )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "${DoTSpell1}"    Spell   ${Parse[0,"( ${DoDot[SETTINGVAL]} && !${Target.Buff[${DoTSpell1}].ID}  && ( ${Target.PctHPs} > ${HPStopDOT[SETTINGVAL]}) )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "${DichoSpell}"    Spell   ${Parse[0,"(  ${DoDicho[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "${ManaNuke}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "${RuneNuke}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "${NukeSpell2}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODEMEZ_Rotation" "${NukeSpell1}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}

    |- Fill in other rotations with across-mode defaults because we aren't going to 
    |- customize for this mode.
    /call ENC_DefaultBurnConfig "ENC_Burn_MODEMEZ_Rotation"
    /call ENC_DefaultDebuffGroupConfig "ENC_Debuff_MODEMEZ_Rotation"
    /call ENC_DefaultSelfBuffRotationConfig ENC_Downtime_MODEMEZ_Rotation"
    /call ENC_DefaultBuffGroupConfig
/return 

Sub ENC_ModeConfigMODECHARM
    /varset IsMezzing TRUE
    /varset IsCharming TRUE
    /echo Leveraging ${Me.Class.Name} CHARM Mode
    /varset Spell1 ${MezSpell}
    /varset Spell2 ${MezAESpell}
    /varset Spell3 ${TashSpell}
   
    /if (${RG_CanUseAA[Slowing Helix]} == FALSE) {
        /varset Spell4 ${SlowSpell}
    } else {
        /varset Spell4 ${ManaNuke}
    }
    /varset Spell5 ${SingleStunSpell1}
    /varset Spell6 ${CharmSpell}
    /varset Spell7 ${DoTSpell1}
    /if (${DoCripple[SETTINGVAL]}) {
        /varset Spell8 ${CrippleSpell}
    } else {
        /varset Spell8 ${NukeSpell2}
    }
    /varset Spell9 ${ManaDot}
    /varset Spell10 ${RuneNuke}
    /varset Spell11 ${DebuffDot}
    /varset Spell12 ${DichoSpell}
    /if (${DoAlliance[SETTINGVAL]}) {
        /varset Spell13 ${AllianceSpell}
    } else {
        /varset Spell13 ${ManaDrainSpell}
    }
    
       |-- The first 9 AA's are Aggro controls
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Glyphy Spray"    AA   ${Parse[0,"( (${Target.Named} && ${Target.Level}>${Me.Level}) || (${Spawn[id ${assistid}].PctHPs}<45 && ${Spawn[id ${assistid}].PctHPs}>5) )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Reactive Rune"    AA   ${Parse[0,"( (${Target.Named} && ${Target.Level}>${Me.Level}) || (${Spawn[id ${assistid}].PctHPs}<45 && ${Spawn[id ${assistid}].PctHPs}>5) )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Self Stasis" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 30 )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Dimensional Instability" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 30 )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Beguiler's Directed Banishment" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 40 )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Beguiler's Banishment" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 50 && ${SpawnCount[npc radius 20]} > 2)"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Doppelganger" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 60 )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Phantasmal Opponent" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 60 )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Dimensional Shield" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 80 )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Arcane Whisper" AA ${Parse[0,"( ${Me.PctAggro}>=90 )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Silent Casting" AA ${Parse[0,"( ${Me.PctAggro}>=90 )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Azure Mind Crystal"       Item   ${Parse[0,"( ${Me.PctMana}<=${ModRodManaPct[SETTINGVAL]} && ${FindItem[Azure Mind Crystal].ID} )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Focus of Arcanum"    AA   ${Parse[0,"( TRUE )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "Chromatic Haze"    AA   ${Parse[0,"( BURNCHECK )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "${DebuffDot}"    Spell   ${Parse[0,"( ${DoDot[SETTINGVAL]} && !${Target.Buff[${DebuffDot}].ID} )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "${ManaDot}"    Spell   ${Parse[0,"( ${DoDot[SETTINGVAL]} && !${Target.Buff[${ManaDot}].ID} )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "${DoTSpell1}"    Spell   ${Parse[0,"( ${DoDot[SETTINGVAL]} && !${Target.Buff[${DoTSpell1}].ID} )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "${DichoSpell}"    Spell   ${Parse[0,"(  ${DoDicho[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "${ManaNuke}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "${RuneNuke}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "${NukeSpell2}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODECHARM_Rotation" "${NukeSpell1}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    |- Fill in other rotations with across-mode defaults because we aren't going to 
    |- customize for this mode.
    /call ENC_DefaultBurnConfig "ENC_Burn_MODECHARM_Rotation"
    /call ENC_DefaultDebuffGroupConfig "ENC_Debuff_MODECHARM_Rotation"
    /call ENC_DefaultSelfBuffRotationConfig ENC_Downtime_MODECHARM_Rotation"
    /call ENC_DefaultBuffGroupConfig
/return 

Sub ENC_ModeConfigMODEMORI 
    /varset IsMezzing TRUE
    /call InitMez
    /echo You may See This Mode Mention Some Variables are Already Defined This Is Normal! Enjoy RG Enchanter!
    /varset Spell1 ${MezSpell}
    /varset Spell2 ${MezAESpell}
    /varset Spell3 ${TashSpell}
    /if (${RG_CanUseAA[Slowing Helix]} == FALSE && ${Me.Level} < 88) {
        /varset Spell4 ${SlowSpell}
    } else { 
        /if (${RG_CanUseAA[Slowing Helix]} == FALSE && ${Me.Level} >= 88) {
            /varset Spell4 ${CripSlowSpell} 
        } else {      
            /varset Spell4 ${ManaDrainSpell}
        }
    }
    /varset Spell5 ${NdtBuff}
    /varset Spell6 ${NukeSpell1}
    /varset Spell7 ${DoTSpell1}
    /if (${DoCripple[SETTINGVAL]} && ${Me.Level} < 88) {
        /varset Spell8 ${CrippleSpell}
    } else {
        /varset Spell8 ${StripBuffSpell}
    }
    /varset Spell9 ${MezAESpellFast}
    /varset Spell10 ${UnityRune}
    /varset Spell11 ${DebuffDot}
    /varset Spell12 ${DichoSpell}
    /if (${DoAlliance[SETTINGVAL]}) {
        /varset Spell13 ${AllianceSpell}
    } else {
        /varset Spell13 NULL
    }
    
    |-- The first 9 AA's are Aggro controls
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Glyphy Spray"    AA    ${Parse[0,"( (${Target.Named} && ${Target.Level}>${Me.Level}) || (${Spawn[id ${assistid}].PctHPs}<45 && ${Spawn[id ${assistid}].PctHPs}>5) )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Reactive Rune"   AA    ${Parse[0,"( (${Target.Named} && ${Target.Level}>${Me.Level}) || (${Spawn[id ${assistid}].PctHPs}<45 && ${Spawn[id ${assistid}].PctHPs}>5) )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Self Stasis"     AA    ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 30 )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Dimensional Instability"        AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 30 )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Beguiler's Directed Banishment" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 40 )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Beguiler's Banishment" AA  ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 50 && ${SpawnCount[npc radius 20]} > 2)"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Doppelganger"          AA  ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 60 )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Phantasmal Opponent"   AA  ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 60 )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Dimensional Shield"    AA  ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 80 )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Arcane Whisper"        AA  ${Parse[0,"( ${Me.PctAggro}>=90 )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Silent Casting"        AA  ${Parse[0,"( ${Me.PctAggro}>=90 )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Focus of Arcanum"      AA  ${Parse[0,"( TRUE )"]}
|   This is a Seperator I put in Below is the Spell Rotation Above is Primarily All AA
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "${TashSpell}"     Spell   ${Parse[0,"( ${DoTash[SETTINGVAL]} && DETSPELLCHECK && !${Target.Tashed.ID})"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "Bite of Tashani"    AA    ${Parse[0,"( ${DoAATash[SETTINGVAL]} && DETAACHECK && !${Target.Tashed.ID} )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "${TwinCast}"      Spell   ${Parse[0,"(  ${DoTwinCastDPS[SETTINGVAL]} && !${Me.Buff[${TwinCastBuff}].ID} && !${Me.Buff[Improved Twincast].ID}  && !${MEZIMMUNEBODY} && !${MezImmune_List.Contains[${Target.ID}]} )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "${DoTSpell1}"     Spell   ${Parse[0,"( ${DoDot[SETTINGVAL]} &&  ( !${Target.Buff[${DoTSpell1}].ID} || ${Me.Song[Gift of Mana].ID} )  )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "${DichoSpell}"    Spell   ${Parse[0,"(  ${DoDicho[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "${NukeSpell1}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "${NukeSpell2}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
|   /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "${ManaDrainSpell}" Spell  ${Parse[0,"( ${Target.CurrentMana} > 10 )"]}

      |- I decided to Define my own Selfbuff Routine for this Mode to make use of my Unity Spell Since i did the work to fit it on the bar p:)
    /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${SelfHPBuff}"      Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
    /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${MezBuff}"         Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
    /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    
    |**
    /if ( ${UnityRune.NotEqual[NULL]} ) {
        /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${UnityRune}" Spell ${Parse[0,"( ${Me.SpellReady[${Spell[${UnityRune}].RankName}]} && !${Me.Buff[${SelfRune1}].ID} || !${Me.Buff[${SelfRune2}].ID}  )"]}
    } else {
        /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${SelfRune1}"       Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${SelfRune2}"       Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
    } 
    **| 
    /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "Veil of Mindshadow"     AA      ${Parse[0,"( SELFBUFFAACHECK )"]}
    /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${PetBuffSpell}"        Spell   ${Parse[0,"( SELFBUFFPETCHECK )"]}
    /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "Azure Mind Crystal"     AA      ${Parse[0,"( ${Me.PctMana}>90 && !${FindItem[Azure Mind Crystal].ID} )"]}
    /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "Gather Mana"            AA      ${Parse[0,"( ${Me.PctMana}<60 )"]}
    /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${AuraBuff1}" Spell ${Parse[0,"( ${AuraBuff1.NotEqual[NULL]} && !${Me.Aura[1].Name.Find[${AuraBuff1Name}]} && !${Me.Aura[2].Name.Find[${AuraBuff1Name}]} && ${PCSpellReady[${AuraBuff1}]} )"]}
    /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${AuraBuff2}" Spell ${Parse[0,"( !${DoLearners[SETTINGVAL]} && ${AuraBuff2.NotEqual[NULL]} && !${Me.Aura[1].Name.Find[${AuraBuff2Name}]} && !${Me.Aura[2].Name.Find[${AuraBuff2Name}]} && ${PCSpellReady[${AuraBuff2}]})"]}
    /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${AuraBuff3}" Spell ${Parse[0,"( ${DoLearners[SETTINGVAL]} && ${AuraBuff3.NotEqual[NULL]}  && !${Me.Aura[1].Name.Find[${AuraBuff3Name}]} && !${Me.Aura[2].Name.Find[${AuraBuff3Name}]} && ${PCSpellReady[${AuraBuff3}]})"]}

  

    |- Fill in other rotations with across-mode defaults because we aren't going to 
    |- customize for this mode.
    /call ENC_DefaultBurnConfig         "ENC_Burn_MODEMORI_Rotation"
    /call ENC_DefaultDebuffGroupConfig  "ENC_Debuff_MODEMORI_Rotation"
    /call ENC_DefaultBuffGroupConfig    "ENC_BuffGroupConfig_MODEMORI_Rotation"
/return 

Sub ENC_ModeConfigMODETLP
    /varset IsMezzing TRUE
| - TLP SPELL BAR SETUP
    /varset Spell1 ${MezSpell}
    /varset Spell2 ${MezAESpell}
    /varset Spell3 ${TashSpell}
    /if (${RG_CanUseAA[Slowing Helix]} == FALSE && ${Me.Level} < 88) {
        /varset Spell4 ${SlowSpell}
    } else { 
        /if (${RG_CanUseAA[Slowing Helix]} == FALSE && ${Me.Level} >= 88) {
            /varset Spell4 ${CripSlowSpell} 
        } else {      
            /varset Spell4 ${ManaDrainSpell}
        }
    }
    /varset Spell5 ${NdtBuff}
    /varset Spell6 ${NukeSpell1}
    /varset Spell7 ${DoTSpell1}
    /if ( ${Me.NumGems} > 8 ) {
        /varset Spell8 ${CrippleSpell}
    } else {
         /varset Spell8 NULL 
    }
    /varset Spell9 NULL
    
    |-- The first 9 AA's are Aggro controls
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Glyphy Spray"             AA       ${Parse[0,"( (${Target.Named} && ${Target.Level}>${Me.Level}) || (${Spawn[id ${assistid}].PctHPs}<45 && ${Spawn[id ${assistid}].PctHPs}>5) )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Reactive Rune"            AA       ${Parse[0,"( (${Target.Named} && ${Target.Level}>${Me.Level}) || (${Spawn[id ${assistid}].PctHPs}<45 && ${Spawn[id ${assistid}].PctHPs}>5) )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Self Stasis"              AA       ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 30 )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Dimensional Instability"  AA       ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 30 )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Beguiler's Directed Banishment" AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 40 )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Beguiler's Banishment"          AA ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 50 && ${SpawnCount[npc radius 20]} > 2)"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Doppelganger"             AA       ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 60 )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Phantasmal Opponent"      AA       ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 60 )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Dimensional Shield"       AA       ${Parse[0,"( ${Me.TargetOfTarget.ID}==${Me.ID} && ${Target.ID}==${autotargetid} && ${Me.PctHPs} <= 80 )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Arcane Whisper"           AA       ${Parse[0,"( ${Me.PctAggro}>=90 )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Silent Casting"           AA       ${Parse[0,"( ${Me.PctAggro}>=90 )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Focus of Arcanum"         AA       ${Parse[0,"( TRUE )"]}
|   This is a Seperator I put in Below is the Spell Rotation Above is Primarily All AA
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "${TashSpell}"     Spell   ${Parse[0,"( ${DoTash[SETTINGVAL]} && DETSPELLCHECK && !${Target.Tashed.ID})"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "Bite of Tashani"  AA      ${Parse[0,"( ${DoAATash[SETTINGVAL]} && DETAACHECK && !${Target.Tashed.ID} )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "${TwinCast}"      Spell   ${Parse[0,"(  ${DoTwinCastDPS[SETTINGVAL]} && !${Me.Buff[${TwinCastBuff}].ID} && !${Me.Buff[Improved Twincast].ID}  && !${MEZIMMUNEBODY} && !${MezImmune_List.Contains[${Target.ID}]} )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "${DoTSpell1}"     Spell   ${Parse[0,"( ${DoDot[SETTINGVAL]} &&  ( !${Target.Buff[${DoTSpell1}].ID} || ${Me.Song[Gift of Mana].ID} )  )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "${DichoSpell}"    Spell   ${Parse[0,"(  ${DoDicho[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "${NukeSpell1}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    /call AddToRotation "ENC_DPS_MODETLP_Rotation" "${NukeSpell2}"    Spell   ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
|    /call AddToRotation "ENC_DPS_MODEMORI_Rotation" "${ManaDrainSpell}" Spell  ${Parse[0,"( ${Target.CurrentMana} > 10 )"]}

      |- I decided to Define my own Selfbuff Routine for this Mode to make use of my Unity Spell Since i did the work to fit it on the bar p:)
    /call AddToRotation "ENC_Downtime_MODETLP_Rotation" "${SelfHPBuff}"      Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
    /call AddToRotation "ENC_Downtime_MODETLP_Rotation" "${MezBuff}"         Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
    /call AddToRotation "ENC_Downtime_MODETLP_Rotation" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "ENC_Downtime_MODETLP_Rotation" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    
    |**
    /if ( ${UnityRune.NotEqual[NULL]} ) {
        /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${UnityRune}" Spell ${Parse[0,"( ${Me.SpellReady[${Spell[${UnityRune}].RankName}]} && !${Me.Buff[${SelfRune1}].ID} || !${Me.Buff[${SelfRune2}].ID}  )"]}
    } else {
        /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${SelfRune1}"       Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation "ENC_Downtime_MODEMORI_Rotation" "${SelfRune2}"       Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
    } 
    **| 
    /call AddToRotation "ENC_Downtime_MODETLP_Rotation" "Veil of Mindshadow"     AA      ${Parse[0,"( SELFBUFFAACHECK )"]}
    /call AddToRotation "ENC_Downtime_MODETLP_Rotation" "${PetBuffSpell}"        Spell   ${Parse[0,"( SELFBUFFPETCHECK )"]}
    /call AddToRotation "ENC_Downtime_MODETLP_Rotation" "Azure Mind Crystal"     AA      ${Parse[0,"( ${Me.PctMana}>90 && !${FindItem[Azure Mind Crystal].ID} )"]}
    /call AddToRotation "ENC_Downtime_MODETLP_Rotation" "Gather Mana"            AA      ${Parse[0,"( ${Me.PctMana}<60 )"]}
    /call AddToRotation "ENC_Downtime_MODETLP_Rotation" "${AuraBuff1}" Spell ${Parse[0,"( ${AuraBuff1.NotEqual[NULL]} && !${Me.Aura[1].Name.Find[${AuraBuff1Name}]} && !${Me.Aura[2].Name.Find[${AuraBuff1Name}]} && ${PCSpellReady[${AuraBuff1}]} )"]}
    /call AddToRotation "ENC_Downtime_MODETLP_Rotation" "${AuraBuff2}" Spell ${Parse[0,"( !${DoLearners[SETTINGVAL]} && ${AuraBuff2.NotEqual[NULL]} && !${Me.Aura[1].Name.Find[${AuraBuff2Name}]} && !${Me.Aura[2].Name.Find[${AuraBuff2Name}]} && ${PCSpellReady[${AuraBuff2}]})"]}
    /call AddToRotation "ENC_Downtime_MODETLP_Rotation" "${AuraBuff3}" Spell ${Parse[0,"( ${DoLearners[SETTINGVAL]} && ${AuraBuff3.NotEqual[NULL]}  && !${Me.Aura[1].Name.Find[${AuraBuff3Name}]} && !${Me.Aura[2].Name.Find[${AuraBuff3Name}]} && ${PCSpellReady[${AuraBuff3}]})"]}

  

    |- Fill in other rotations with across-mode defaults because we aren't going to 
    |- customize for this mode.
    /call ENC_DefaultBurnConfig         "ENC_Burn_MODETLP_Rotation"
    /call ENC_DefaultDebuffGroupConfig  "ENC_Debuff_MODETLP_Rotation"
    /call ENC_DefaultBuffGroupConfig    "ENC_BuffGroupConfig_MODETLP_Rotation"
/return 

Sub ENC_DefaultBurnConfig(string rotation_name)
    /call AddToRotation "${rotation_name}" "Illusions of Grandeur"  AA ${Parse[0,"( TRUE )"]}
    /call AddToRotation "${rotation_name}" "Spire of Enchantment"   AA ${Parse[0,"( TRUE )"]}
    /call AddToRotation "${rotation_name}" "Improved Twincast"      AA ${Parse[0,"( TRUE )"]}
    /call AddToRotation "${rotation_name}" "Forceful Rejuvenation"  AA ${Parse[0,"( TRUE )"]}
    /call AddToRotation "${rotation_name}" "Calculated Insanity"    AA ${Parse[0,"( TRUE )"]}
    /call AddToRotation "${rotation_name}" "Forceful Rejuvenation"  AA ${Parse[0,"( TRUE )"]}
    /call AddToRotation "${rotation_name}" "Mental Contortion"      AA ${Parse[0,"( ${Target.Named} )"]}
    /call AddToRotation "${rotation_name}" "Chromatic Haze"         AA ${Parse[0,"( TRUE )"]} 

/return

Sub ENC_DefaultDebuffGroupConfig(string rotation_name)
    /call AddToRotation "${rotation_name}" "${TashSpell}"       Spell   ${Parse[0,"( ${DoTash[SETTINGVAL]} && DETSPELLCHECK && !${Target.Tashed.ID})"]}
    /call AddToRotation "${rotation_name}" "Bite of Tashani"    AA      ${Parse[0,"( ${DoAATash[SETTINGVAL]} && DETAACHECK && !${Target.Tashed.ID} )"]}
|     /call AddToRotation "${rotation_name}" "${StripBuffSpell}"  Spell   ${Parse[0,"( ( ${Target.Beneficial} )&& ${DoStripBuff[SETTINGVAL]} )"]}
    /call AddToRotation "${rotation_name}" "Enveloping Helix"   AA      ${Parse[0,"( ${DoSlow[SETTINGVAL]} && DETAACHECK && ${XAssist.XTFullHaterCount} > 2 )"]}
    /call AddToRotation "${rotation_name}" "Slowing Helix"      AA      ${Parse[0,"( ${DoSlow[SETTINGVAL]} && DETAACHECK && ( !${NPCAAReady[Enveloping Helix]} || ${XAssist.XTFullHaterCount} < 2)  )"]}
    /call AddToRotation "${rotation_name}" "${CripSlowSpell}"   Spell   ${Parse[0,"( (${DoSlow[SETTINGVAL]} || ${DoCripple[SETTINGVAL]}) && DETSPELLCHECK )"]}
    /call AddToRotation "${rotation_name}" "${SlowSpell}"       Spell   ${Parse[0,"( ${DoSlow[SETTINGVAL]} && DETSPELLCHECK )"]}
    /call AddToRotation "${rotation_name}" "${CrippleSpell}"    Spell   ${Parse[0,"( ${DoCripple[SETTINGVAL]} && DETSPELLCHECK )"]}
|    /call AddToRotation "${rotation_name}" "${ManaDrainSpell}"  Spell   ${Parse[0,"( DETSPELLCHECK && ${Target.CurrentMana} > 10 )"]}
    |- Blur & Dispel are left out. Blur had no room on the spell bar, Dispel is too difficult to program in a way that
    |- avoids removing beneficial spells.
/return

Sub ENC_DefaultBuffGroupConfig
    |- Setup our group buffs that will need Dannet
    |- We will have 6 buffs for the group
    /call BuffGroup_Init 9
    /call BuffGroup_Set 1 "${ManaRegen}" "RGCASTERS" ${Parse[0,TRUE]}
    /call BuffGroup_Set 2 "${HasteBuff}" "RGMELEE" ${Parse[0,TRUE]}
    /call BuffGroup_Set 3 "${GroupSpellShield}"  "${Parse[0,"(${FindItemCount[${Spell[${GroupSpellShield}].ReagentID[1]}]} >= 1)"]}
    /call BuffGroup_Set 4 "${GroupDoTShield}"  ${Parse[0,"(${FindItemCount[${Spell[${GroupDoTShield}].ReagentID[1]}]} >= 1)"]}
    /call BuffGroup_Set 5 "${GroupAuspiceBuff}" ${Parse[0,"(${FindItemCount[${Spell[${GroupAuspiceBuff}].ReagentID[1]}]} >= 1)"]}
    /call BuffGroup_Set 6 "${NdtBuff}" "RGMELEE" ${Parse[0,"(${DoNDTBuff[SETTINGVAL]})"]}
    /call BuffGroup_Set 7 "${SingleRune}" "RGTANK" ${Parse[0,"(${FindItemCount[${Spell[${SingleRune}].ReagentID[1]}]} >= 1)"]}
    /call BuffGroup_Set 8 "${GroupRune}" "RGCASTERS" ${Parse[0,"(${DoGroupAbsorb[SETTINGVAL]} && ${FindItemCount[${Spell[${GroupRune}].ReagentID[1]}]} >= 2)"]}
    /call BuffGroup_Set 9 "${AggroRune}" "RGTANK" ${Parse[0,"(${DoAggroRune[SETTINGVAL]})"]} "single"

    |- Chat Begs
    /call ChatBegList_Add ENCBegs crack Spell "${ManaRegen}" sender TRUE
    /call ChatBegList_Add ENCBegs speed AA "${HasteBuff}" sender TRUE
/return

Sub ENC_DefaultSelfBuffRotationConfig(string rotation_name)
    /call AddToRotation "${rotation_name}" "${SelfHPBuff}"      Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
    /call AddToRotation "${rotation_name}" "${MezBuff}"         Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
 |  To Handle Unitys This is a example of how to do it While checking for Both Unity Buffs. Works great Problem is in Enchanters Case The Unity Has a 30 Second CD after mem making it to Slow to be Used Via a Misc Slot.
 |  I am Leaving this Stub As a Example of How to Choose Between Unitys or Singles in a rotational Format.
 |   /if ( ${UnityRune.NotEqual[NULL]} ) {
 |                   /call AddToRotation "${rotation_name}" "${UnityRune}" Spell ${Parse[0,"( !${Me.Buff[${SelfRune1}].ID} || !${Me.Buff[${SelfRune2}].ID}  )"]}
 |   }
    /call AddToRotation "${rotation_name}" "${SelfRune1}"       Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
    /call AddToRotation "${rotation_name}" "${SelfRune2}"       Spell   ${Parse[0,"( SELFBUFFCHECK )"]}
        
    /call AddToRotation "${rotation_name}" "Veil of Mindshadow"    AA   ${Parse[0,"( SELFBUFFAACHECK )"]}
    /call AddToRotation "${rotation_name}" "${PetBuffSpell}"       Spell   ${Parse[0,"( SELFBUFFPETCHECK )"]}
    /call AddToRotation "${rotation_name}" "Azure Mind Crystal"       AA   ${Parse[0,"( ${Me.PctMana}>90 && !${FindItem[Azure Mind Crystal].ID} )"]}
    /call AddToRotation "${rotation_name}" "Gather Mana"         AA     ${Parse[0,"( ${Me.PctMana}<60 )"]}
    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    /call AddToRotation "${rotation_name}" "${AuraBuff1}" Spell ${Parse[0,"( ${AuraBuff1.NotEqual[NULL]} && !${Me.Aura[1].Name.Find[${AuraBuff1Name}]} && !${Me.Aura[2].Name.Find[${AuraBuff1Name}]} && ${PCSpellReady[${AuraBuff1}]} )"]}
    /call AddToRotation "${rotation_name}" "${AuraBuff2}" Spell ${Parse[0,"( !${DoLearners[SETTINGVAL]} && ${AuraBuff2.NotEqual[NULL]} && !${Me.Aura[1].Name.Find[${AuraBuff2Name}]} && !${Me.Aura[2].Name.Find[${AuraBuff2Name}]} && ${PCSpellReady[${AuraBuff2}]})"]}
    /call AddToRotation "${rotation_name}" "${AuraBuff3}" Spell ${Parse[0,"( ${DoLearners[SETTINGVAL]} && ${AuraBuff3.NotEqual[NULL]}  && !${Me.Aura[1].Name.Find[${AuraBuff3Name}]} && !${Me.Aura[2].Name.Find[${AuraBuff3Name}]} && ${PCSpellReady[${AuraBuff3}]})"]}

/return

Sub ENC_Combat_Routine
    /if (${IsCharming}) /call CharmCheck
    /call PetAttack
    /if (DODEBUFF) {
        /call Ordered_Rotation_Follow ENC_Debuff_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        |/if (${Macro.Return}) /return
    }
    /if ( DODPS !${IsTanking} ) {      
        /if ( BURNCHECK ) {
            /call Ordered_Rotation_Follow ENC_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        }
        /call Ordered_Rotation_Follow ENC_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }
    
/return FALSE

Sub ENC_Downtime_Routine
    /if (!${Me.Pet.ID} && ${DoPet[SETTINGVAL]}) {
        |- Make sure we have Reagents
        /if (${FindItemCount[Tiny Dagger]} > 0) {
            /if (${PCSpellReady[${PetSpell}]}) {
                /call SpellNow "${PetSpell}" ${Me.ID}
            }
        } else {
            /echo \ar YOU DON'T HAVE ANY TINY DAGGERS! WHAT'S WRONG WITH YOU!?
            /echo NO PET FOR YOU -- Temporarily turning off DoPet
            /varset DoPet[SETTINGVAL] 0
        }
    }
    |- Call Self buffs -- and this is where I realized we need to optimize FollowRotation so that it is focused on beneficial spells vs. OrderedRotation which isn't...
    |- This will allow Bene<thing>Ready be built into the Rotation call like Ordered Rotation.
    /call FollowRotation  ENC_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}

    /if (${Me.Pet.ID}) {
        /call FollowRotation  ENC_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.Pet.ID}
    } 
/return FALSE

|----------------------------------------------------------------------------
|- SUB: CharmCheck
|----------------------------------------------------------------------------
Sub CharmCheck
    /if (${CharmDelay}) /return
    /if (${CharmedID} && !${Spawn[ID ${CharmedID}].ID}) /varset CharmedID 0
    
    |- We're only going to charm a new pet if we don't have a current pet, our charm spell is ready, and we actually have a charm spell.
    /if (${DoCharmPet[SETTINGVAL]} && !${Me.Pet.ID} && ${CharmSpell.NotEqual[NULL]} && ${Me.SpellReady[${CharmSpell}]}) {
        |- We have a mob we're trying to charm so lets keep tabs on it and charm it again if our main assist isn't beating on it.
        /if (${CharmedID} && ${Spawn[${CharmedID}].ID} && ${Spawn[${CharmedID}].Type.Equal[NPC]} && ${Spawn[${CharmedID}].Distance}<${Math.Calc[${Spell[${CharmSpell}].Range}-25]} && ${CharmedID}!=${Me.GroupAssistTarget.ID}) {
            DEBUG CharmCheck: Retargeting mob after failed charm.
            /call SetTarget ${CharmedID}
        } else {
            |- We don't have a target in mind so we need to go searching -- this uses a less robust search than in the RGmez.inc
            /declare mezspawnsearch_npc string local "npc radius ${MezWatchCircum} zradius ${MezWatchZCircum} range ${CharmMinLvl[SETTINGVAL]} ${CharmMaxLvl[SETTINGVAL]} targetable playerstate 4"
            /declare tmp_spawninfo spawn local NULL
            /declare tmp_mobcount int local ${SpawnCount[${mezspawnsearch_npc}]}
            DEBUG CharmCheck: Looking for MOB ${tmp_mobcount} STRING: ${mezspawnsearch_npc}
            |- First we make sure there are mobs to mez around us and want more than the min mobs as the first mob will most likely be engaged by our tank.
            /if (${tmp_mobcount} >= ${CharmMinMobs[SETTINGVAL]}) {
                DEBUG CharmCheck Found ${tmp_mobcount} >= ${CharmMinMobs[SETTINGVAL]}
                /declare i int local 0
                /for i 1 to ${tmp_mobcount}
                    |- We'll go from nearest to farthest spawns and choose the first spawn that meets our criteria
                    /squelch /vardata tmp_spawninfo NearestSpawn[${i},${mezspawnsearch_npc}]
                    
                    DEBUG CharmCheck: Checking Mob ${tmp_spawninfo.ID}
                    
                    |- Skip the mob if they're not within assist range and LOS
                    /if (${tmp_spawninfo.LineOfSight} && ${tmp_spawninfo.Distance} <= ${AssistRange[SETTINGVAL]}) {
                        DEBUG Mob not in LOS or too far away
                        /continue
                    }
                    
                    |- Mob must be in LOS and Assist Range to reach this piece of code
                    |- Set them as our target if the main assist isn't going after them.
                    /if (${tmp_spawninfo.ID} != ${Me.GroupAssistTarget.ID}) {
                        
                        /varset CharmedID ${tmp_spawninfo.ID}
                        /call SetTarget ${CharmedID}
                        DEBUG CharmCheck: Mob found -- ${Target.ID}==${CharmedID} [${tmp_spawninfo.ID}]
                        |- Ready to get out
                        /break
                    }
                /next i
            }
        }
        |- This IF is original RGENC making EXTRA sure stuff didn't screw up. Within it is where we get down to business with the Charm and
        |- any extra abilities to assist
        /if (${Target.ID}==${CharmedID} && ${Target.Type.Equal[NPC]}) {
            DEBUG CharmCheck: In charm loop
            /if (${CharmPreStun[SETTINGVAL]} && ${SingleStunSpell1.NotEqual[NULL]} && ${Me.SpellReady[${SingleStunSpell1}]}) {
                /call PrintGroupMessage "Charming: Stunning ${Target.Name}"
                /call SpellNow "${SingleStunSpell1}" ${Target.ID} Charm
            }
            /if (${CharmPreTash[SETTINGVAL]} && ${TashSpell.NotEqual[NULL]} && ${Me.SpellReady[${TashSpell}]}) {
                /call PrintGroupMessage "Charming: Tashing ${Target.Name}"
                /call SpellNow "${TashSpell}" ${Target.ID} Charm
            }
            /echo Charming: Trying Tto Charm ${Target.Name}
            /call SpellNow "${CharmSpell}" ${Target.ID} Charm
            /if (${CastResult.Equal[CAST_SUCCESS]}) {
                /call PrintGroupMessage "Charming: Successfully Charmed ${Me.Pet.CleanName} | ${Me.Pet.ID}"
                /varset CharmedID 0
            } else {
                /call PrintGroupMessage "Failed to Charm ${Spawn[${CharmedID}].CleanName} | ${CharmedID} -- Will try again"
            }
        }
    }
/return 

|----------------------------------------------------------------------------
|-SUB: BIND  - SingleBanish
|----------------------------------------------------------------------------
#bind SingleBanish      /banish
Sub Bind_SingleBanish(string BanishID)
    /call SetTarget ${BanishID}
    /delay 10 ${Target.ID}==${BanishID}
    /if (!${Target.LineOfSight}) {
        /call PrintGroupMessage "I Can Not See the Target"
    } else /if (${RG_AAReady[Beguiler's Directed Banishment]} && ${BanishID}) {
        /call PrintGroupMessage "\ar BANISHING \ag -> \ay ${Spawn[${BanishID}].CleanName} \ag <- \ar ID:${BanishID} \ax"
        /face fast
        /call SpellNow "Beguiler's Directed Banishment" ${BanishID}
    } else {
        /call PrintGroupMessage "\ar COOL DOWN \ag >> \aw Beguiler's Directed Banishment \ag << "
    }
    /call ClearTarget
/return
|----------------------------------------------------------------------------
|-SUB: BIND  - AEBanish
|----------------------------------------------------------------------------
#bind AEBanish          /aebanish
Sub Bind_AEBanish(string AEBanishID)
    /call SetTarget ${AEBanishID}
    /delay 10 ${Target.ID}==${AEBanishID}
    /if (!${Target.LineOfSight}) {
        /call PrintGroupMessage "I Can Not See the Target"
    } else /if (${RG_AAReady[Beguiler's Banishment]} && ${AEBanishID}) {
        /call PrintGroupMessage "\ar AE Banishing \ag -> \ay ${Spawn[${AEBanishID}].CleanName} \ag <- \ar ID:${AEBanishID} \ax"
        /face fast
        /call SpellNow "Beguiler's Banishment" ${AEBanishID}
    } else {
        /call PrintGroupMessage "\ar COOL DOWN \ag >> \aw Beguiler's Banishment \ag << "
    }
    /call ClearTarget
/return

Sub ENC_PullSetup
    /if (${Me.Pet.ID} && ${DoPetPull[SETTINGVAL]} ) {
        /call Pull_SetAbility "pullpet" "Special"
    } else /if (${RG_CanUseAA[Slowing Helix]}) {
            /call Pull_SetAbility "Slowing Helix" "AA" 
    } else /if (${SlowSpell.NotEqual[NULL]}&&${Me.Gem[${SlowSpell}]}) {
            /call Pull_SetAbility "${SlowSpell}" Spell
    } else /if (${TashSpell.NotEqual[NULL]}&&${Me.Gem[${TashSpell}]}) {
            /call Pull_SetAbility "${TashSpell}" Spell
    }   
/return

Sub ENC_RemoveAura
    /docommand /removeaura ${AuraBuff1Name}
    /docommand /removeaura ${AuraBuff2Name}
    /docommand /removeaura ${AuraBuff3Name}
/return