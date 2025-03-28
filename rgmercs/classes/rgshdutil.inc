#define MODETANK 0
#define MODEDPS 1
#define MODETLP 2

#define TAPCHECK "(  ${Me.PctHPs} <= ${Startlifetap[SETTINGVAL]} )"

Sub SHD_Setup
|-List containing SHD specific settings settings
    /declare RGList_SHD         list outer

    |-- Combatskills
    /call AbilitySet_New Mantle        
    /call AbilitySet_New Carapace        
    /call AbilitySet_New Endregen
    /call AbilitySet_New blade        
    /call AbilitySet_New crimson        
    /call AbilitySet_New meleemit        
    /call AbilitySet_New deflection        
    /call AbilitySet_New leechcurse        
    /call AbilitySet_New unholyaura    
    /call AbilitySet_New CurseGuard    
|- SHD spells    
    |-- Self Buffs
    /call AbilitySet_New PetSpell        
    /call AbilitySet_New PetHaste        
    /call AbilitySet_New Shroud            
    /call AbilitySet_New Horror            
    /call AbilitySet_New Skin            
    /call AbilitySet_New SelfDS            
    /call AbilitySet_New Demeanor        
    /call AbilitySet_New Healburn       
    /call AbilitySet_New CloakHP
    /call AbilitySet_New Convenant
    /call AbilitySet_New CallAtk
    |-- Spell Line up
    /call AbilitySet_New AeTaunt
    /call AbilitySet_New PoisonDot            
    /call AbilitySet_New Spearnuke            
    /call AbilitySet_New Bondtap            
    /call AbilitySet_New Diretap            
    /call AbilitySet_New Lifetap            
    /call AbilitySet_New Bufftap            
    /call AbilitySet_New Bitetap            
    /call AbilitySet_New ForPower            
    /call AbilitySet_New Terror            
    /call AbilitySet_New TempHP               
    /call AbilitySet_New Dicho              
    /call AbilitySet_New Torrent
    /call AbilitySet_New SnareDOT
    /call AbilitySet_New Acrimony
    /call AbilitySet_New SpiteStrike
    /call AbilitySet_New ReflexStrike
    /call AbilitySet_New DireDot
    /call AbilitySet_New AllianceNuke
    /call AbilitySet_New InfluenceDisc

    |- ITEM Sets
    /call ItemSet_New Epic
    
|-Set SHD Variables
    |- Rotations
    /call Ordered_Rotation_New SHD_Debuff_MODETANK_Rotation
    /call Ordered_Rotation_New SHD_Heal_MODETANK_Rotation
    /call Ordered_Rotation_New SHD_DPS_MODETANK_Rotation
    /call Ordered_Rotation_New SHD_Downtime_MODETANK_Rotation
    /call Ordered_Rotation_New SHD_Burn_MODETANK_Rotation

    /call Ordered_Rotation_New SHD_Debuff_MODEDPS_Rotation
    /call Ordered_Rotation_New SHD_Heal_MODEDPS_Rotation
    /call Ordered_Rotation_New SHD_DPS_MODEDPS_Rotation
    /call Ordered_Rotation_New SHD_Downtime_MODEDPS_Rotation
    /call Ordered_Rotation_New SHD_Burn_MODEDPS_Rotation

    /call Ordered_Rotation_New SHD_Debuff_MODETLP_Rotation
    /call Ordered_Rotation_New SHD_Heal_MODETLP_Rotation
    /call Ordered_Rotation_New SHD_DPS_MODETLP_Rotation
    /call Ordered_Rotation_New SHD_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New SHD_Burn_MODETLP_Rotation

    /declare spellgem        int    outer 1
    
|-Config Options
    /call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = Tank; Set 1 = DPS
    
    | - Combat/Tank Controls
    /call RGLoadSetting SHD Flashhp 35 Combat "Set Hp% to Shield Flash at. Default 35"
    /call RGLoadSetting SHD DoBandolier 0 Options "Sets whether to use auto bandolier functions. Requires a bandolier called Shield (a shield and 1hd weapon) and one called 2HS"
    /call RGLoadSetting SHD DoTank 1 Combat "Set 1/ tanking 0 for Dpsing"
    /call RGLoadSetting SHD AeTauntCnt 2 Combat "Set to # of mobs before using Aetaunt abilitys"
    | - Pet Controls
    /call RGLoadSetting SHD DoPet 1 Combat "Set 0/1 to summon and use your pet"
    /call RGLoadSetting SHD PetEngagePct 95 Combat "Sets what HP % To Sick pet in combat"
    | - Spell Control
    /call RGLoadSetting SHD DoTorrent 1 combat "Use torrent line of spells 1/0"
    /call RGLoadSetting SHD Startlifetap 100 Combat "Set % you want to Start Lifetapping at Default 100 Will Always tap"
    /call RGLoadSetting SHD Startbigtap 100 Combat "Set % you want to Start casting big lifetaps (Dire and Dicho/Composite). At Default 100 Will Always tap"
    /call RGLoadSetting SHD DoDot 1 Combat "Set 0/1 to use Dot abilities. - Default 1"
    /call RGLoadSetting SHD DoSnare 1 Options "Set 0/1 to use Snare line."
    | - AE Spell Control
    /call RGLoadSetting SHD DoAE 0 Combat "Set 0/1 to Turn on or Off Using Ae taunts and Taps"
    | - Mana Control
    /call RGLoadSetting SHD Manatonuke 30 Combat "%Mana to Use Nukes at"
    /call RGLoadSetting SHD HPStopDOT 30 Combat "%HP to cut off to stop casting dots."
    
    |-Declare spell variables
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
    /declare spellmisc                 int outer 8
    /varset  spellmisc     ${Me.NumGems}
    /declare GroupBuffRecast     int outer 0
    /declare miscspellremem        string outer NULL
    /declare spellrememtimer    timer outer 0
    /declare fparatimer2        timer outer 60s
    /declare groupbufftimer        timer outer 0
    /declare Banestrike        string outer NULL

    |- Enable Combat Subtlety
    /if (${Me.AltAbility[8300].Name.Find[disabled]} && ${RG_AAReady[8300]}) {
        /alt act 8300
        /delay 5
    }
/return

|----------------------------------------------------------------------------
|- SUB: CheckOptions
|---------------------------------------------------------------------------- 
Sub SHD_CheckOptions
|- This is checking if your a tank and Setting Variables properly if you are.

    /if ( ${IsTanking} || ${DoTank[SETTINGVAL]} ) {
        |- Enable Bold Attacks
        /if (${RG_AAReady[793]} && !${Me.AltAbility[793].Name.Find[enabled]}) {
            /call AANow "793"
        }
        /varset StayOnTarget[SETTINGVAL] 0
        /varset AutoAssistAt[SETTINGVAL] 100
        /varset DoMelee[SETTINGVAL] 1
        /varset AutoCampRadius[SETTINGVAL] 50
        /stick set DelayStrafe on
        /varset StickHow[SETTINGVAL] 15 Moveback
        /varset AllowMezBreak[SETTINGVAL] 1
    } else {
        |- Disable Bold Attacks
        /if (${RG_AAReady[793]} && ${Me.AltAbility[793].Name.Find[enabled]}) {
            /call AANow "793"
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
| SUB: SetupSpells
|---------------------------------------------------------------------------- 
Sub SHD_SetupSkills
| - Item Sets Useful for SK Survival.
    /call ItemSet_Add "Innoruuk's Dark Blessing" Epic
    /call ItemSet_Add "Innoruuk's Voice"         Epic
    /call ItemSet_ChooseOuter Epic Epic

|-Disc/Combatability
    |--One off discs
    /call AbilitySet_Add "Leechcurse Discipline" leechcurse
    /call AbilitySet_ChooseOuter leechcurse leechcurse
    
    /call AbilitySet_Add "Deflection Discipline" deflection
    /call AbilitySet_ChooseOuter deflection deflection
    
    /call AbilitySet_Add "Unholy Aura Discipline" unholyaura
    /call AbilitySet_ChooseOuter unholyaura unholyaura

    /call AbilitySet_Add "Cursed Guardian Discipline" CurseGuard
    /call AbilitySet_ChooseOuter CurseGuard CurseGuard

    |- Influence Disc Line
    /call AbilitySet_Add "Insolent Influence" InfluenceDisc
    /call AbilitySet_Add "Impudent Influence" InfluenceDisc
    /call AbilitySet_Add "Impenitent Influence" InfluenceDisc
    /call AbilitySet_Add "Impertinent Influence" InfluenceDisc
    /call AbilitySet_Add "Ignominious Influence" InfluenceDisc
    /call AbilitySet_ChooseOuter InfluenceDisc InfluenceDisc
    
|- Unending Disc - 100% Taunt Control
/call AbilitySet_Add "Undivided Acrimony"        Acrimony
/call AbilitySet_Add "Unbroken Acrimony"         Acrimony
/call AbilitySet_Add "Unflinching Acrimony"      Acrimony
/call AbilitySet_Add "Unyielding Acrimony"       Acrimony
/call AbilitySet_Add "Unending Acrimony"         Acrimony
/call AbilitySet_Add "Unrelenting Acrimony"      Acrimony
/call AbilitySet_Add "Unconditional Acrimony"    Acrimony
/call AbilitySet_ChooseOuter Acrimony Acrimony
   

    |- Spite Strikes - Reduce damage Add heals Proc 
    /call AbilitySet_Add "Spite of Ronak" SpiteStrike
    /call AbilitySet_Add "Spite of Kra`Du" SpiteStrike
    /call AbilitySet_Add "Spite of Mirenilla" SpiteStrike
    /call AbilitySet_ChooseOuter SpiteStrike SpiteStrike
    
    | - Group heal Reflexive Strikes 
    /call AbilitySet_Add "Reflexive Resentment" ReflexStrike
    /call AbilitySet_Add "Reflexive Rancor" ReflexStrike
    /call AbilitySet_Add "Reflexive Revulsion" ReflexStrike
    /call AbilitySet_ChooseOuter ReflexStrike ReflexStrike
        
    |--Carapace/Mantle
    /call AbilitySet_Add "Malarian Mantle"         Mantle
    /call AbilitySet_Add "Gorgon Mantle"         Mantle
    /call AbilitySet_Add "Recondite Mantle"     Mantle
    /call AbilitySet_Add "Bonebrood Mantle"     Mantle
    /call AbilitySet_Add "Doomscale Mantle"     Mantle
    /call AbilitySet_Add "Krellnakor Mantle"     Mantle
    /call AbilitySet_Add "Restless Mantle"         Mantle
    /call AbilitySet_Add "Fyrthek Mantle"        Mantle
    /call AbilitySet_Add "Geomimus Mantle"      Mantle
    /call AbilitySet_ChooseOuter Mantle Mantle

    |- Carapace
    /call AbilitySet_Add "Soul Carapace"         Carapace
    /call AbilitySet_Add "Umbral Carapace"         Carapace
    /call AbilitySet_Add "Malarian Carapace"     Carapace
    /call AbilitySet_Add "Gorgon Carapace"         Carapace
    /call AbilitySet_Add "Sholothian Carapace"     Carapace
    /call AbilitySet_Add "Grelleth's Carapace"     Carapace
    /call AbilitySet_Add "Vizat's Carapace"     Carapace
    /call AbilitySet_Add "Tylix's Carapace"     Carapace
    /call AbilitySet_Add "Cadcane's Carapace"     Carapace
    /call AbilitySet_Add "Xetheg's Carapace"     Carapace
    /call AbilitySet_Add "Kanghammer's Carapace"    Carapace
    /call AbilitySet_ChooseOuter Carapace Carapace
   
    |--Crimson Blade
    /call AbilitySet_Add "Crimson Blade"       crimson
    /call AbilitySet_Add "Scarlet Blade"       crimson
    /call AbilitySet_Add "Carmine Blade"       crimson
    /call AbilitySet_Add "Claret Blade"        crimson
    /call AbilitySet_Add "Cerise Blade"        crimson
    /call AbilitySet_Add "Sanguine Blade"      crimson
    /call AbilitySet_Add "Incarnadine Blade"   crimson
    /call AbilitySet_ChooseOuter crimson crimson
  
    |--Gouging Blade
    /call AbilitySet_Add "Incapacitating Blade" blade
    /call AbilitySet_Add "Grisly Blade"        blade
    /call AbilitySet_Add "Gouging Blade"     blade
    /call AbilitySet_Add "Gashing Blade"     blade
    /call AbilitySet_Add "Lacerating Blade" blade
    /call AbilitySet_Add "Wounding Blade"     blade
    /call AbilitySet_Add "Rending Blade"     blade
    /call AbilitySet_ChooseOuter blade blade
    
    |--Melee Witstand Next X hits with lowered damage
    /call AbilitySet_Add "Withstand" meleemit
    /call AbilitySet_Add "Defy"      meleemit
    /call AbilitySet_Add "Renounce"  meleemit
    /call AbilitySet_Add "Reprove"      meleemit
    /call AbilitySet_Add "Repel"      meleemit
    /call AbilitySet_Add "Spurn"      meleemit
    /call AbilitySet_Add "Thwart"      meleemit
    /call AbilitySet_Add "Repudiate" meleemit
    /call AbilitySet_Add "Gird"     meleemit
    /call AbilitySet_ChooseOuter meleemit meleemit
    
    |---Fast Endurance regen - Update to new Format Once tested
    /call AbilitySet_Add "Second Wind"       Endregen
    /call AbilitySet_Add "Third Wind"       Endregen
    /call AbilitySet_Add "Fourth Wind"       Endregen
    /call AbilitySet_Add "Respite"           Endregen
    /call AbilitySet_Add "Reprieve"       Endregen
    /call AbilitySet_Add "Rest"           Endregen
    /call AbilitySet_Add "Breather"       Endregen
    /call AbilitySet_Add "Hiatus"           Endregen
    /call AbilitySet_Add "Relax"           Endregen
    /call AbilitySet_Add "Night's Calming"  Endregen
    /call AbilitySet_Add "Convalesce"       Endregen
    /call AbilitySet_ChooseOuter Endregen Endregen
    
|-SHD Spells
    |-- Pet Spells
    /call AbilitySet_Add "Leering Corpse"         PetSpell
    /call AbilitySet_Add "Bone Walk"             PetSpell
    /call AbilitySet_Add "Convoke Shadow"         PetSpell
    /call AbilitySet_Add "Restless Bones"         PetSpell
    /call AbilitySet_Add "Animate Dead"         PetSpell
    /call AbilitySet_Add "Summon Dead"             PetSpell
    /call AbilitySet_Add "Malignant Dead"         PetSpell
    /call AbilitySet_Add "Cackling Bones"         PetSpell
    /call AbilitySet_Add "Invoke Death"         PetSpell
    /call AbilitySet_Add "Son of Decay"         PetSpell
    /call AbilitySet_Add "Maladroit Minion"     PetSpell
    /call AbilitySet_Add "Minion of Sebilis"     PetSpell
    /call AbilitySet_Add "Minion of Fear"         PetSpell
    /call AbilitySet_Add "Minion of Sholoth"     PetSpell
    /call AbilitySet_Add "Minion of Grelleth"     PetSpell
    /call AbilitySet_Add "Minion of Vizat"         PetSpell
    /call AbilitySet_Add "Minion of T`Vem"         PetSpell
    /call AbilitySet_Add "Minion of Drendar"     PetSpell
    /call AbilitySet_Add "Minion of Itzal"         PetSpell
    /call AbilitySet_Add "Minion of Fandrel"        PetSpell
    /call AbilitySet_ChooseOuter PetSpell PetSpell
   
    |-- pet Haste
    /call AbilitySet_Add "Gift of Fandrel" PetHaste
    /call AbilitySet_Add "Gift of Itzal"    PetHaste
    /call AbilitySet_Add "Gift of Drendar"     PetHaste
    /call AbilitySet_Add "Gift of T`Vem"     PetHaste
    /call AbilitySet_Add "Gift of Lutzen"     PetHaste
    /call AbilitySet_Add "Gift of Urash"     PetHaste
    /call AbilitySet_Add "Gift of Dyalgem"     PetHaste
    /call AbilitySet_Add "Expatiate Death"     PetHaste
    /call AbilitySet_Add "Amplify Death"     PetHaste
    /call AbilitySet_Add "Rune of Decay"     PetHaste
    /call AbilitySet_Add "Augment Death"     PetHaste
    /call AbilitySet_Add "Strengthen Death"     PetHaste
    /call AbilitySet_ChooseOuter PetHaste PetHaste
    
    |-- Self buffs
    |-- Shrouds
    /call AbilitySet_Add "Shroud of Death"             Shroud
    /call AbilitySet_Add "Shroud of Chaos"             Shroud
    /call AbilitySet_Add "Black Shroud"                 Shroud
    /call AbilitySet_Add "Shroud of Discord"         Shroud
    /call AbilitySet_Add "Shroud of the Gloomborn"     Shroud
    /call AbilitySet_Add "Shroud of the Blightborn"     Shroud
    /call AbilitySet_Add "Shroud of the Plagueborne" Shroud
    /call AbilitySet_Add "Shroud of the Shadeborne"     Shroud
    /call AbilitySet_Add "Shroud of the Darksworn"     Shroud
    /call AbilitySet_Add "Shroud of the Doomscale"     Shroud
    /call AbilitySet_Add "Shroud of the Krellnakor"     Shroud
    /call AbilitySet_Add "Shroud of the Restless"     Shroud
    /call AbilitySet_Add "Shroud of Zelinstein"        Shroud
    /call AbilitySet_Add "Shroud of Rimeclaw"       Shroud
    /call AbilitySet_ChooseOuter Shroud Shroud
         
    |--Horrors
    /call AbilitySet_Add "Mental Horror"         Horror
    /call AbilitySet_Add "Marrowthirst Horror"     Horror
    /call AbilitySet_Add "Soulthirst Horror"     Horror
    /call AbilitySet_Add "Mindshear Horror"     Horror
    /call AbilitySet_Add "Amygdalan Horror"     Horror
    /call AbilitySet_Add "Sholothian Horror"     Horror
    /call AbilitySet_Add "Grelleth's Horror"     Horror
    /call AbilitySet_Add "Vizat's Horror"         Horror
    /call AbilitySet_Add "Tylix's Horror"         Horror
    /call AbilitySet_Add "Cadcane's Horror"     Horror
    /call AbilitySet_Add "Brightfeld's Horror"    Horror
    /call AbilitySet_Add "Mortimus' Horror"     Horror
    /call AbilitySet_ChooseOuter Horror Horror
    
    |--CloakHP
    /call AbilitySet_Add "Cloak of the Akheva"        CloakHP
    /call AbilitySet_Add "Cloak of Luclin"            CloakHP
    /call AbilitySet_Add "Cloak of Discord"           CloakHP
    /call AbilitySet_Add "Cloak of Corruption"        CloakHP
    /call AbilitySet_Add "Drape of Corruption"        CloakHP
    /call AbilitySet_Add "Drape of Korafax"           CloakHP
    /call AbilitySet_Add "Drape of Fear"              CloakHP
    /call AbilitySet_Add "Drape of the Sepulcher"     CloakHP
    /call AbilitySet_Add "Drape of the Fallen"        CloakHP
    /call AbilitySet_Add "Drape of the Wrathforged"   CloakHP
    /call AbilitySet_Add "Drape of the Magmaforged"   CloakHP
    /call AbilitySet_Add "Drape of the Iceforged"     CloakHP
    /call AbilitySet_Add "Drape of the Akheva"        CloakHP
    /call AbilitySet_Add "Drape of the Ankexfen"      CloakHP
    /call AbilitySet_ChooseOuter CloakHP CloakHP

    
    |--SelfDS    
    /call AbilitySet_Add "Banshee Aura" SelfDS
    /call AbilitySet_Add "Banshee Skin" SelfDS
    /call AbilitySet_Add "Ghoul Skin"     SelfDS
    /call AbilitySet_Add "Zombie Skin"     SelfDS
    /call AbilitySet_Add "Helot Skin"     SelfDS
    /call AbilitySet_Add "Specter Skin" SelfDS
    /call AbilitySet_Add "Tekuel Skin"    SelfDS
    /call AbilitySet_Add "Goblin Skin"  SelfDS
    /call AbilitySet_ChooseOuter SelfDS SelfDS

    |- Torrent of Suffering line causes issues with pets. 
    /call AbilitySet_Add "Torrent of Hate"         Torrent
    /call AbilitySet_Add "Torrent of Pain"         Torrent
    /call AbilitySet_Add "Torrent of Agony"     Torrent
    /call AbilitySet_Add "Torrent of Misery"     Torrent
    /call AbilitySet_Add "Torrent of Suffering" Torrent
    /call AbilitySet_Add "Torrent of Anguish"     Torrent
    /call AbilitySet_Add "Torrent of Melancholy" Torrent
    /call AbilitySet_Add "Torrent of Desolation" Torrent
    /call AbilitySet_ChooseOuter Torrent Torrent

    | - SK Alliance Spell Line
    /call AbilitySet_Add "Bloodletting Coalition" AllianceNuke
    /call AbilitySet_Add "Bloodletting Alliance" AllianceNuke
    /call AbilitySet_Add "Bloodletting Covenant" AllianceNuke
    /call AbilitySet_Add "Bloodletting Conjunction" AllianceNuke
    /call AbilitySet_ChooseOuter AllianceNuke AllianceNuke


    |--Demeanor
    /call AbilitySet_Add "Remorseless Demeanor" Demeanor
    /call AbilitySet_Add "Impenitent Demeanor" Demeanor
    /call AbilitySet_ChooseOuter Demeanor Demeanor
  
    |-- Concordant Disruption
    /call AbilitySet_Add "Harmonious Disruption" Healburn
    /call AbilitySet_Add "Concordant Disruption" Healburn
    /call AbilitySet_Add "Confluent Disruption" Healburn
    /call AbilitySet_Add "Penumbral Disruption" Healburn
    /call AbilitySet_ChooseOuter Healburn Healburn
    
    |-- Convenant Line
    /call AbilitySet_Add "Grim Covenant"             Convenant
    /call AbilitySet_Add "Venril's Covenant"         Convenant
    /call AbilitySet_Add "Gixblat's Covenant"         Convenant
    /call AbilitySet_Add "Worag's Covenant"         Convenant
    /call AbilitySet_Add "Falhotep's Covenant"         Convenant
    /call AbilitySet_Add "Livio's Covenant"         Convenant
    /call AbilitySet_Add "Helot Covenant"             Convenant
    /call AbilitySet_Add "Syl`Tor Covenant"         Convenant
    /call AbilitySet_Add "Aten Ha Ra's Covenant"    Convenant
    /call AbilitySet_Add "Kar's Covenant"       Convenant
    /call AbilitySet_ChooseOuter Convenant Convenant
    
    |-- Call Of Atk Buff Line 
    /call AbilitySet_Add "Call of Blight"           CallAtk
    /call AbilitySet_Add "Call of Darkness"         CallAtk
    /call AbilitySet_Add "Call of Dusk"             CallAtk
    /call AbilitySet_Add "Call of Shadow"             CallAtk
    /call AbilitySet_Add "Call of Gloomhaze"         CallAtk
    /call AbilitySet_Add "Call of Nightfall"         CallAtk
    /call AbilitySet_Add "Call of Twilight"         CallAtk
    /call AbilitySet_Add "Penumbral Call"            CallAtk
    /call AbilitySet_ChooseOuter CallAtk CallAtk
    
    |--Spell slot lineup
    |--Gem 1: Posion Dot - Level 44 to 107
    /call AbilitySet_Add "Blood of Pain"             PoisonDot
    /call AbilitySet_Add "Blood of Hate"             PoisonDot
    /call AbilitySet_Add "Blood of Discord"         PoisonDot
    /call AbilitySet_Add "Blood of Inruku"             PoisonDot
    /call AbilitySet_Add "Blood of the Blacktalon"     PoisonDot
    /call AbilitySet_Add "Blood of the Blackwater"     PoisonDot
    /call AbilitySet_Add "Blood of Laarthik"         PoisonDot
    /call AbilitySet_Add "Blood of Malthiasiss"     PoisonDot
    /call AbilitySet_Add "Blood of Korum"             PoisonDot
    /call AbilitySet_Add "Blood of Ralstok"         PoisonDot
    /call AbilitySet_Add "Blood of Bonemaw"         PoisonDot
    /call AbilitySet_Add "Blood of Drakus"             PoisonDot
    /call AbilitySet_Add "Blood of Ikatiar"         PoisonDot
    /call AbilitySet_Add "Blood of Tearc"            PoisonDot
    /call AbilitySet_Add "Blood of Shoru"           PoisonDot
    /call AbilitySet_ChooseOuter PoisonDot PoisonDot

|- Dire Dot Debuff & Diease dot
/call AbilitySet_Add "Dire Constriction"     DireDot
/call AbilitySet_Add "Dire Restriction"      DireDot
/call AbilitySet_Add "Dire Stenosis"         DireDot
/call AbilitySet_Add "Dire Stricture"        DireDot
/call AbilitySet_Add "Dire Strangulation"    DireDot
/call AbilitySet_Add "Dire Coarctation"      DireDot
/call AbilitySet_Add "Dire Convulsion"       DireDot
/call AbilitySet_Add "Dire Seizure"          DireDot
/call AbilitySet_Add "Dire Squelch"          DireDot
/call AbilitySet_ChooseOuter DireDot DireDot

        
|--Gem 2: Disease Nuke - Level 1 to 109
/call AbilitySet_Add "Spike of Disease"     Spearnuke
/call AbilitySet_Add "Spear of Disease"     Spearnuke
/call AbilitySet_Add "Spear of Pain"        Spearnuke
/call AbilitySet_Add "Spear of Plague"      Spearnuke
/call AbilitySet_Add "Spear of Decay"       Spearnuke
/call AbilitySet_Add "Miasmic Spear"        Spearnuke
/call AbilitySet_Add "Spear of Muram"       Spearnuke
/call AbilitySet_Add "Rotroot Spear"        Spearnuke
/call AbilitySet_Add "Rotmarrow Spear"      Spearnuke
/call AbilitySet_Add "Malarian Spear"       Spearnuke
/call AbilitySet_Add "Gorgon Spear"         Spearnuke
/call AbilitySet_Add "Spear of Sholoth"     Spearnuke
/call AbilitySet_Add "Spear of Grelleth"    Spearnuke
/call AbilitySet_Add "Spear of Vizat"       Spearnuke
/call AbilitySet_Add "Spear of Tylix"       Spearnuke
/call AbilitySet_Add "Spear of Cadcane"     Spearnuke
/call AbilitySet_Add "Spear of Bloodwretch" Spearnuke
/call AbilitySet_Add "Spear of Lazam"       Spearnuke
/call AbilitySet_ChooseOuter Spearnuke Spearnuke

    
    |--Gem 3: Duration Tap - Level 57 to 111
    /call AbilitySet_Add "Bond of Tatalros"        Bondtap
    /call AbilitySet_Add "Bond of Bynn"            Bondtap
    /call AbilitySet_Add "Bond of Vulak"           Bondtap
    /call AbilitySet_Add "Bond of Xalgoz"          Bondtap
    /call AbilitySet_Add "Bond of Bonemaw"         Bondtap
    /call AbilitySet_Add "Bond of Ralstok"         Bondtap
    /call AbilitySet_Add "Bond of Korum"           Bondtap
    /call AbilitySet_Add "Bond of Malthiasiss"     Bondtap
    /call AbilitySet_Add "Bond of Laarthik"        Bondtap
    /call AbilitySet_Add "Bond of the Blackwater"  Bondtap
    /call AbilitySet_Add "Bond of the Blacktalon"  Bondtap
    /call AbilitySet_Add "Bond of Inruku"          Bondtap
    /call AbilitySet_Add "Bond of Death"           Bondtap
    /call AbilitySet_Add "Vampiric Curse"          Bondtap
    /call AbilitySet_ChooseOuter Bondtap Bondtap
    
    |--Gem 4,5,6: Life Taps - Level 75 to 115
    |--Gem 4 Dire Tap lvl 85-115 
    /call AbilitySet_Add "Dire Implication"     Diretap
    /call AbilitySet_Add "Dire Accusation"      Diretap
    /call AbilitySet_Add "Dire Allegation"      Diretap
    /call AbilitySet_Add "Dire Insinuation"     Diretap
    /call AbilitySet_Add "Dire Declaration"     Diretap
    /call AbilitySet_Add "Dire Testimony"       Diretap
    /call AbilitySet_Add "Dire Indictment"      Diretap
    /call AbilitySet_Add "Dire Censure"         Diretap
    /call AbilitySet_Add "Dire Rebuke"          Diretap
    /call AbilitySet_ChooseOuter Diretap Diretap
    
    |--Gem 5 - DD Lifetap Level 1-115
    /call AbilitySet_Add "Touch of Flariton"          Lifetap
    /call AbilitySet_Add "Touch of Txiki"             Lifetap 
    /call AbilitySet_Add "Touch of the Wailing Three" Lifetap
    /call AbilitySet_Add "Touch of the Soulbleeder"   Lifetap
    /call AbilitySet_Add "Touch of Lanys"             Lifetap
    /call AbilitySet_Add "Touch of Dyalgem"           Lifetap
    /call AbilitySet_Add "Touch of Urash"             Lifetap
    /call AbilitySet_Add "Touch of Falsin"            Lifetap
    /call AbilitySet_Add "Touch of Lutzen"            Lifetap
    /call AbilitySet_Add "Touch of T`Vem"             Lifetap
    /call AbilitySet_Add "Touch of Drendar"           Lifetap
    /call AbilitySet_Add "Touch of Severan"           Lifetap
    /call AbilitySet_Add "Touch of the Devourer"      Lifetap
    /call AbilitySet_Add "Touch of Draygun"           Lifetap
    /call AbilitySet_Add "Touch of Innoruuk"          Lifetap
    /call AbilitySet_Add "Touch of Volatis"           Lifetap
    /call AbilitySet_Add "Drain Soul"                 Lifetap
    /call AbilitySet_Add "Drain Spirit"               Lifetap
    /call AbilitySet_Add "Spirit Tap"                 Lifetap
    /call AbilitySet_Add "Siphon Life"                Lifetap
    /call AbilitySet_Add "Life Leech"                 Lifetap
    /call AbilitySet_Add "Lifedraw"                   Lifetap
    /call AbilitySet_Add "Lifespike"                  Lifetap
    /call AbilitySet_Add "Lifetap"                    Lifetap
    /call AbilitySet_ChooseOuter Lifetap Lifetap
    
    |--Gem 6 - HP Buff Tap 1-115 secondtap 75-115
    /call AbilitySet_Add "Touch of Mortimus"          Bufftap
    /call AbilitySet_Add "Touch of Namdrows"          Bufftap
    /call AbilitySet_Add "Touch of Zlandicar"         Bufftap
    /call AbilitySet_Add "Touch of the Wailing Three" Bufftap
    /call AbilitySet_Add "Touch of Kildrukaun"        Bufftap
    /call AbilitySet_Add "Touch of Tharoff"           Bufftap
    /call AbilitySet_Add "Touch of Iglum"             Bufftap    
    /call AbilitySet_Add "Touch of Piqiorn"           Bufftap
    /call AbilitySet_Add "Touch of Klonda"            Bufftap
    /call AbilitySet_Add "Touch of Holmein"           Bufftap
    /call AbilitySet_Add "Touch of Hemofax"           Bufftap    
    /call AbilitySet_Add "Siphon Strength"            Bufftap
    /call AbilitySet_Add "Despair"                    Bufftap
    /call AbilitySet_Add "Scream of Hate"             Bufftap
    /call AbilitySet_Add "Scream of Pain"             Bufftap
    /call AbilitySet_Add "Shroud of Hate"             Bufftap
    /call AbilitySet_Add "Shroud of Pain"             Bufftap
    /call AbilitySet_Add "Abduction of Strength"      Bufftap
    /call AbilitySet_Add "Torrent of Hate"            Bufftap
    /call AbilitySet_Add "Torrent of Pain"            Bufftap
    /call AbilitySet_Add "Torrent of Fatigue"         Bufftap
    /call AbilitySet_Add "Aura of Pain"               Bufftap
    /call AbilitySet_Add "Aura of Hate"               Bufftap
    /call AbilitySet_Add "Theft of Pain"              Bufftap
    /call AbilitySet_Add "Theft of Hate"              Bufftap
    /call AbilitySet_Add "Theft of Agony"             Bufftap
    /call AbilitySet_ChooseOuter Bufftap Bufftap

    |--Gem 7: Resource Tap - Level 62 to 111
    /call AbilitySet_Add "Zevfeer's Bite"         Bitetap
    /call AbilitySet_Add "Inruku's Bite"         Bitetap
    /call AbilitySet_Add "Ancient: Bite of Muram" Bitetap
    /call AbilitySet_Add "Blacktalon Bite"         Bitetap
    /call AbilitySet_Add "Blackwater Bite"         Bitetap
    /call AbilitySet_Add "Laarthik's Bite"         Bitetap
    /call AbilitySet_Add "Malthiasiss's Bite"     Bitetap
    /call AbilitySet_Add "Korum's Bite"         Bitetap
    /call AbilitySet_Add "Ralstok's Bite"         Bitetap
    /call AbilitySet_Add "Bonemaw's Bite"         Bitetap
    /call AbilitySet_Add "Xalgoz's Bite"         Bitetap
    /call AbilitySet_Add "Vulak's Bite"         Bitetap
    /call AbilitySet_Add "Cruor's Bite"            Bitetap
    /call AbilitySet_ChooseOuter Bitetap Bitetap

    |--Gem 8: Challenge Hate builder+AC Buff - Level 72 to 122
    /call AbilitySet_Add "Challenge for Power"         ForPower
    /call AbilitySet_Add "Trial for Power"             ForPower
    /call AbilitySet_Add "Charge for Power"         ForPower
    /call AbilitySet_Add "Confrontation for Power"     ForPower
    /call AbilitySet_Add "Provocation for Power"     ForPower
    /call AbilitySet_Add "Demand for Power"         ForPower
    /call AbilitySet_Add "Impose for Power"         ForPower
    /call AbilitySet_Add "Refute for Power"         ForPower | TBL - 107
    /call AbilitySet_Add "Protest for Power"         ForPower | TOV - 112
    /call AbilitySet_Add "Parlay for Power"            ForPower | TOL - 117
    /call AbilitySet_Add "Petition for Power"       ForPower | LS -122
    /call AbilitySet_ChooseOuter ForPower ForPower
  
    |--Gem 9: Terror, instant hate build - Level 33 to 106
    /call AbilitySet_Add "Terror of Darkness"     Terror
    /call AbilitySet_Add "Terror of Shadows"     Terror
    /call AbilitySet_Add "Terror of Death"         Terror
    /call AbilitySet_Add "Terror of Terris"     Terror
    /call AbilitySet_Add "Terror of Thule"         Terror
    /call AbilitySet_Add "Terror of Discord"     Terror
    /call AbilitySet_Add "Terror of Vergalid"     Terror
    /call AbilitySet_Add "Terror of the Soulbleeder" Terror
    /call AbilitySet_Add "Terror of Jelvalak"     Terror
    /call AbilitySet_Add "Terror of Rerekalen"     Terror
    /call AbilitySet_Add "Terror of Desalin"     Terror
    /call AbilitySet_Add "Terror of Poira"         Terror
    /call AbilitySet_Add "Terror of Narus"         Terror
    /call AbilitySet_Add "Terror of Kra`Du"     Terror
    /call AbilitySet_Add "Terror of Mirenilla"     Terror
    /call AbilitySet_Add "Terror of Ander"        Terror
    /call AbilitySet_Add "Terror of Tarantis"      Terror
    /call AbilitySet_ChooseOuter Terror Terror

    | - Aetaunt Line
    /call AbilitySet_Add "Dread Gaze" AeTaunt
    /call AbilitySet_Add "Vilify"    AeTaunt
    /call AbilitySet_Add "Revile"    AeTaunt
    /call AbilitySet_Add "Burst of Spite"    AeTaunt
    /call AbilitySet_Add "Loathing"    AeTaunt
    /call AbilitySet_Add "Abhorrence"    AeTaunt
    /call AbilitySet_Add "Antipathy"    AeTaunt
    /call AbilitySet_Add "Animus"       AeTaunt
    /call AbilitySet_ChooseOuter AeTaunt AeTaunt
    
    
     
|--Gem 10: Stance, Temp hp - Level 84 to 109
/call AbilitySet_Add "Stormwall Stance"      TempHP
/call AbilitySet_Add "Defiant Stance"        TempHP
/call AbilitySet_Add "Staunch Stance"        TempHP
/call AbilitySet_Add "Steadfast Stance"      TempHP
/call AbilitySet_Add "Stoic Stance"          TempHP
/call AbilitySet_Add "Stubborn Stance"       TempHP
/call AbilitySet_Add "Steely Stance"         TempHP
/call AbilitySet_Add "Adamant Stance"        TempHP
/call AbilitySet_Add "Unwavering Stance"     TempHP
/call AbilitySet_ChooseOuter TempHP TempHP

    
    |--Gem 11: Self DS - Level 70 to 110
    /call AbilitySet_Add "Decrepit Skin"     Skin
    /call AbilitySet_Add "Umbral Skin"         Skin
    /call AbilitySet_Add "Malarian Skin"     Skin
    /call AbilitySet_Add "Gorgon Skin"         Skin
    /call AbilitySet_Add "Sholothian Skin"     Skin
    /call AbilitySet_Add "Grelleth's Skin"     Skin
    /call AbilitySet_Add "Vizat's Skin"     Skin
    /call AbilitySet_Add "Tylix's Skin"     Skin
    /call AbilitySet_Add "Cadcane's Skin"     Skin
    /call AbilitySet_Add "Xenacious' Skin"    Skin
    /call AbilitySet_Add "Krizad's Skin"    Skin
    /call AbilitySet_ChooseOuter Skin Skin
    
    |--Gem12: Dicho
    /call AbilitySet_Add "Dichotomic Fang" Dicho
    /call AbilitySet_Add "Dissident Fang" Dicho
    /call AbilitySet_Add "Composite Fang" Dicho
    /call AbilitySet_Add "Ecliptic Fang" Dicho
    /call AbilitySet_ChooseOuter Dicho Dicho

    |-- SnareDOt Line 11-115
    /call AbilitySet_Add "Clinging Darkness" SnareDOT
    /call AbilitySet_Add "Engulfing Darkness" SnareDOT
    /call AbilitySet_Add "Dooming Darkness" SnareDOT
    /call AbilitySet_Add "Cascading Darkness" SnareDOT
    /call AbilitySet_Add "Festering Darkness" SnareDOT
    /call AbilitySet_Add "Despairing Darkness" SnareDOT
    /call AbilitySet_Add "Suppurating Darkness" SnareDOT
    /call AbilitySet_Add "Smoldering Darkness" SnareDOT
    /call AbilitySet_Add "Spreading Darkness" SnareDOT
    /call AbilitySet_Add "Putrefying Darkness" SnareDOT
    /call AbilitySet_Add "Pestilent Darkness" SnareDOT
    /call AbilitySet_Add "Virulent Darkness" SnareDOT
    /call AbilitySet_Add "Vitriolic Darkness" SnareDOT
    /call AbilitySet_ChooseOuter SnareDOT SnareDOT
/return
|----------------------------------------------------------------------------
|- SUB: Spellbar Setup
|-----------------------------------------------------------------------------
Sub SHD_ModeConfigMODETANK
    /varset IsTanking TRUE
| - This Spell bar is not 0-115 friendly ... YET!
    /varset Spell1 ${DireDot}
    /varset Spell2 ${Spearnuke}
    /if (${DoTorrent[SETTINGVAL]}) { 
        /varset Spell3 ${Torrent}
    } else { 
        /varset Spell3 ${Bondtap}
    }
    /if (${Diretap.Equal[NULL]}) {
        /varset Spell4 ${SnareDOT}
    } else {
        /varset Spell4 ${Diretap}
    }
    /varset Spell5 ${Lifetap}
    /varset Spell6 ${Bufftap}
    /varset Spell7 ${Bitetap}
    /varset Spell8 ${ForPower}
    /varset Spell9 ${Terror}
    /varset Spell10 ${TempHP}
    /varset Spell11 ${Skin}    
    /varset Spell12 ${Dicho}
    /varset spellmisc ${Me.NumGems}
  
    /call SHD_DefaultSelfBuffRotationConfig    "SHD_Downtime_MODETANK_Rotation"

|- Burn Routines
    /call AddToRotation SHD_Burn_MODETANK_Rotation "${Acrimony}" DISC ${Parse[0,"( ${Target.Named} )"]}
    /call AddToRotation SHD_Burn_MODETANK_Rotation "${SpiteStrike}" DISC ${Parse[0,"( ${Target.Named} )"]}
    /call SHD_DefaultBurnConfig        "SHD_Burn_MODETANK_Rotation"

| - Bandolier Actions.
    /call AddToRotation SHD_DPS_MODETANK_Rotation   "/bandolier activate Shield"    Command ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Shield].Active} && ${Bool[${Me.Bandolier[Shield].Index}]} && BURNCHECK )"]} 
    /call AddToRotation SHD_DPS_MODETANK_Rotation   "/bandolier activate 2HS"       Command ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[2HS].Active} && ${Bool[${Me.Bandolier[2HS].Index}]} && !BURNCHECK )"]}

| - DPS Tank Spells 
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Endregen}"         DISC ${Parse[0,"( ${Me.PctEndurance}<15 )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "Explosion of Hatred" AA ${Parse[0,"( ${SpawnCount[NPC radius 50 zradius 50]}>=${AeTauntCnt[SETTINGVAL]} && ${XAssist.XTFullHaterCount}>=${AeTauntCnt[SETTINGVAL]} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "Explosion of Spite"     AA ${Parse[0,"( ${SpawnCount[NPC radius 50 zradius 50]}>=${AeTauntCnt[SETTINGVAL]} && ${XAssist.XTFullHaterCount}>=${AeTauntCnt[SETTINGVAL]} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "Shield Flash"         AA      ${Parse[0,"( ${Me.PctHPs} <= ${Flashhp[SETTINGVAL]} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "Taunt"                 Ability ${Parse[0,"( ${Me.AbilityReady[Taunt]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Terror}"             Spell ${Parse[0,"( ${Me.SecondaryPctAggro}>60 )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${meleemit}"         Disc  TRUE
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${ForPower}"         Spell ${Parse[0,"( DOTSPELLCHECK )"]}
| - Add AA snare option if availible
    /call AddToRotation SHD_DPS_MODETANK_Rotation "Encroaching Darkness"         AA ${Parse[0,"( ${DoSnare[SETTINGVAL]} && DETAACHECK )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${SnareDOT}"         Spell ${Parse[0,"( ${DoSnare[SETTINGVAL]} && DETSPELLCHECK )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Epic}"             item ${Parse[0,"( !${Me.ActiveDisc.Name.Find[${leechcurse}]} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${leechcurse}"         Disc ${Parse[0,"( !${Me.ActiveDisc.Name.Find[${deflection}]} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${deflection}"         Disc ${Parse[0,"( !${Me.ActiveDisc.Name.Find[${leechcurse}]} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Mantle}"             Disc ${Parse[0,"( ( ${Target.Named} ||  ${SpawnCount[NPC radius 60 zradius 50]}>2 ) && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Carapace}"         Disc ${Parse[0,"( ( ${Target.Named} ||  ${SpawnCount[NPC radius 60 zradius 50]}>2 ) && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${CurseGuard}"         Disc ${Parse[0,"( ( ${Target.Named} ||  ${SpawnCount[NPC radius 60 zradius 50]}>2 ) && !${Me.ActiveDisc.ID} )"]}
|    /call AddToRotation SHD_DPS_MODETANK_Rotation "${unholyaura}"         Disc ${Parse[0,"( ${Target.Named} ||  ${SpawnCount[NPC radius 60 zradius 50]}>2 && !${Me.ActiveDisc.ID} )"]}

|- DPS - DOT
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${PoisonDot}"     Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${DireDot}"         Spell ${Parse[0,"( DOTSPELLCHECK )"]}    
|- DPS - DD 
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Torrent}"                Spell ${Parse[0,"( ${DoTorrent[SETTINGVAL]} && !${Me.Buff[${Spell[${Torrent}].BaseName}].ID} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Spearnuke}"            Spell ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Bondtap}"                Spell ${Parse[0,"( !${DoTorrent[SETTINGVAL]} && !${Me.Buff[${Bondtap}Recourse].ID} )"]}    
    /call AddToRotation SHD_DPS_MODETANK_Rotation "Vicious Bite of Chaos"     AA ${Parse[0,"( ${Target.PctHPs}>5 && ${Target.Distance} < 35 )"]}    
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${blade}"                Disc ${Parse[0,"( ${Target.PctHPs}>5 && ${Target.Distance} < 35 )"]}    
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${crimson}"                Disc ${Parse[0,"( ${Target.PctHPs}>5 && ${Target.Distance} < 35 )"]}    
    
|- DPS - Lifetaps
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Dicho}"     Spell ${Parse[0,"( ${Me.PctHPs} <= ${Startbigtap[SETTINGVAL]} )"]}    
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Diretap}"     Spell ${Parse[0,"( ${Me.PctHPs} <= ${Startbigtap[SETTINGVAL]} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Bufftap}"     Spell ${Parse[0,"( ${Me.PctHPs} <= ${Startlifetap[SETTINGVAL]} && DETSPELLCHECK)"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Bitetap}"     Spell ${Parse[0,"( ${Me.PctHPs} <= ${Startlifetap[SETTINGVAL]} )"]}
    /call AddToRotation SHD_DPS_MODETANK_Rotation "${Lifetap}"     Spell ${Parse[0,"( ${Me.PctHPs} <= ${Startlifetap[SETTINGVAL]} )"]}

|- Chat Begs
/return

Sub SHD_ModeConfigMODEDPS
|    /varset IsTanking False

    |--Gem 1: Posion Dot - Level 44 to 107
    /varset Spell1 ${PoisonDot}
    |--Gem 2: Disease Nuke - Level 1 to 109
    /varset Spell2 ${Spearnuke}
    |--Gem 3: Duration Tap - Level 57 to 106
    /if (${DoTorrent[SETTINGVAL]}) { 
        /varset Spell3 ${Torrent}
    } else { 
        /varset Spell3 ${Bondtap}
    }
    |--Gem 4,5,6: Life Taps - Level 65 to 110
    /varset Spell4 ${Diretap}
    /varset Spell5 ${Lifetap}
    /varset Spell6 ${Bufftap}
    |--Gem 7: Resource Tap - Level 62 to 106
    /varset Spell7 ${Bitetap}
    |--Gem 8: Challenge Hate builder+AC Buff - Level 72 to 107
    /varset Spell8 ${ForPower}
    |--Gem 9: Terror, instant hate build - Level 33 to 106
    /varset Spell9 ${Terror}
    |--Gem 10: Stance, Temp hp - Level 84 to 109
    /varset Spell10 ${TempHP}
    |--Gem 11: Concordant - Level 103 up!
    /varset Spell11 ${Skin}    
    |--Gem 12: Dicho
    /varset Spell12 ${Dicho}
    /varset spellmisc ${Me.NumGems}
  
    /call SHD_DefaultSelfBuffRotationConfig    "SHD_Downtime_MODEDPS_Rotation"

|- Burn Routines
    /call SHD_DefaultBurnConfig    "SHD_Burn_MODEDPS_Rotation"

|- DPS - DD 
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "${Torrent}"                 Spell ${Parse[0,"( ${DoTorrent[SETTINGVAL]} )"]}    
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "${Spearnuke}"                 Spell ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "${Bondtap}"                 Spell ${Parse[0,"( !${Me.Buff[${Bondtap}Recourse].ID} )"]}    
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "Vicious Bite of Chaos"     AA ${Parse[0,"( ${Target.PctHPs}>5 && ${Target.Distance} < 35 )"]}    
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "${blade}"                     Disc ${Parse[0,"( ${Target.PctHPs}>5 && ${Target.Distance} < 35 )"]}    
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "${crimson}"                 Disc ${Parse[0,"( ${Target.PctHPs}>5 && ${Target.Distance} < 35 )"]}    
    
|- DPS - DOT
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "${PoisonDot}"     Spell ${Parse[0,"( !${Target.Buff[${PoisonDot}].ID} && ${DoDot[SETTINGVAL]} )"]}    

|- DPS - Lifetaps
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "${Diretap}"     Spell ${Parse[0,"( ${Me.PctHPs} <= ${Startlifetap[SETTINGVAL]} )"]}
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "${Bufftap}"     Spell ${Parse[0,"( ${Me.PctHPs} <= ${Startlifetap[SETTINGVAL]} && DETSPELLCHECK)"]}
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "${Bitetap}"     Spell ${Parse[0,"( ${Me.PctHPs} <= ${Startlifetap[SETTINGVAL]} )"]}
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "${Dicho}"     Spell ${Parse[0,"( ${Me.PctHPs} <= ${Startlifetap[SETTINGVAL]} )"]}    
    /call AddToRotation SHD_DPS_MODEDPS_Rotation "${Lifetap}"     Spell ${Parse[0,"( ${Me.PctHPs} <= ${Startlifetap[SETTINGVAL]} )"]}


|- Downtime Rotation
    
|- Chat Begs
/return
Sub SHD_ModeConfigMODETLP
    /varset IsTanking TRUE
    /varset Spell1 ${Terror}
    /varset Spell2 ${Spearnuke}
    /varset Spell3 ${Lifetap}
    /varset Spell4 ${Bitetap}
    /varset Spell5 ${Bufftap}
    /varset Spell6 ${PoisonDot}
    /varset Spell7 ${SnareDOT}
    /if ( ${Me.NumGems} > 8 ) {
        /varset Spell8 ${AeTaunt}
    } else {
        /varset Spell 8 NULL
    }
    /if ( ${Me.NumGems} > 9 ) {
        /varset Spell9 NULL
    } else {
        /varset Spell9 NULL
    }

    
    /varset spellmisc ${Me.NumGems}
  
    /call SHD_DefaultSelfBuffRotationConfig    "SHD_Downtime_MODETLP_Rotation"

/echo Welcome To TLP Mode ShadowKnight - As with all RGmercs TLP Tanks There is 2 modes in 1
/echo You Can control Whether your the Tank or not with a Simple /dotank 1/0
/if  ( ${DoTank[SETTINGVAL]} ) { 
    /echo I am In TLP Tank Mode
} else {
    /echo I am In TLP Dps Mode 
}


|- Burn Routines
    /call AddToRotation SHD_Burn_MODETLP_Rotation "${Acrimony}" DISC ${Parse[0,"( ${Target.Named} )"]}
    /call AddToRotation SHD_Burn_MODETLP_Rotation "${SpiteStrike}" DISC ${Parse[0,"( ${Target.Named} )"]}
    /call SHD_DefaultBurnConfig        "SHD_Burn_MODETLP_Rotation"

| - Bandolier Actions.
    /call AddToRotation SHD_DPS_MODETLP_Rotation   "/bandolier activate Shield"    Command ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Shield].Active} && ${Bool[${Me.Bandolier[Shield].Index}]} && BURNCHECK )"]} 
    /call AddToRotation SHD_DPS_MODETLP_Rotation   "/bandolier activate 2HS"       Command ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[2HS].Active} && ${Bool[${Me.Bandolier[2HS].Index}]} && ${XAssist.XTFullHaterCount}<${BurnMobCount[SETTINGVAL]} && !${Target.Named} )"]}


| - DPS Tank Spells 
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Endregen}"             DISC ${Parse[0,"( ${Me.PctEndurance}<15 )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Epic}"                 Item ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) ${Me.PctHPs} <= ${Flashhp[SETTINGVAL]} )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "Taunt"                 Ability ${Parse[0,"( ${DoTank[SETTINGVAL]} &&  ${Me.AbilityReady[Taunt]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Terror}"             Spell ${Parse[0,"( ${DoTank[SETTINGVAL]} &&  ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${AeTaunt}"             Spell ${Parse[0,"( ${DoAE[SETTINGVAL]} && ${SpawnCount[NPC radius 60 zradius 50]} >= ${AeTauntCnt[SETTINGVAL]} )"]}
    
    | - Add AA snare option if availible
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${SnareDOT}"             Spell ${Parse[0,"( ${DoSnare[SETTINGVAL]} && DETSPELLCHECK )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${leechcurse}"         Disc ${Parse[0,"( !${Me.ActiveDisc.Name.Find[${deflection}]} && BURNCHECK )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${deflection}"         Disc ${Parse[0,"( !${Me.ActiveDisc.Name.Find[${leechcurse}]} )"]}
|**    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Mantle}"             Disc ${Parse[0,"( ( ${Target.Named} ||  ${SpawnCount[NPC radius 60 zradius 50]}>2 ) && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Carapace}"             Disc ${Parse[0,"( ( ${Target.Named} ||  ${SpawnCount[NPC radius 60 zradius 50]}>2 ) && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${CurseGuard}"         Disc ${Parse[0,"( ( ${Target.Named} ||  ${SpawnCount[NPC radius 60 zradius 50]}>2 ) && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${unholyaura}"         Disc ${Parse[0,"( ${Target.Named} ||  ${SpawnCount[NPC radius 60 zradius 50]}>2 && !${Me.ActiveDisc.ID} )"]}
**|

|- DPS - DOT
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${PoisonDot}"     Spell ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && DOTSPELLCHECK && MANACHECK  )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Torrent}"        Spell ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${DoTorrent[SETTINGVAL]} )"]}    
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Spearnuke}"        Spell ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && MANACHECK )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Bondtap}"        Spell ${Parse[0,"( !${DoTorrent[SETTINGVAL]} && !${Me.Buff[${Bondtap}Recourse].ID} )"]}    
    /call AddToRotation SHD_DPS_MODETLP_Rotation "Vicious Bite of Chaos"     AA ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${Target.PctHPs}>5 && ${Target.Distance} < 35 )"]}    
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${blade}"            Disc ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${Target.PctHPs}>5 && ${Target.Distance} < 35 )"]}    
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${crimson}"        Disc ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${Target.PctHPs}>5 && ${Target.Distance} < 35 )"]}    
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Diretap}"     Spell ${Parse[0,"( TAPCHECK )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Bufftap}"     Spell ${Parse[0,"( ( MANACHECK || BURNCHECK ) && DOTSPELLCHECK)"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Bitetap}"     Spell ${Parse[0,"( ( MANACHECK || BURNCHECK ) )"]}
    /call AddToRotation SHD_DPS_MODETLP_Rotation "${Lifetap}"     Spell ${Parse[0,"( TAPCHECK )"]}

|- Chat Begs
/return

SUB SHD_DefaultBurnConfig(string rotationname)
    /call AddToRotation ${rotationname} "${ReflexStrike}"    Disc ${Parse[0,"( ${Target.Named} )"]}
    /call AddToRotation ${rotationname} "Harm Touch"        AA ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} && ${Target.Named} ) || BIGBURN )"]}    
    /call AddToRotation ${rotationname} "Thought Leech"        AA TRUE
    /call AddToRotation ${rotationname} "Visage of Death"    AA TRUE
    /call AddToRotation ${rotationname} "Leech Touch"        AA TRUE
    /call AddToRotation ${rotationname} "T`Vyl's Resolve"    AA TRUE
/return
Sub SHD_DefaultBuffGroupConfig
    |- No BuffGroup configuration yet.
/return

Sub SHD_DefaultSelfBuffRotationConfig(string rotationname)
    |- Self Buff Rotation Setup

    /if (${Spell[${Shroud}].Level}<=${Spell[${Me.AltAbility[Dark Lord's Unity (Azia)].Spell.Trigger[1].BaseName}].Level} && ${RG_CanUseAA[Dark Lord's Unity (Azia)]}) {
        /call AddToRotation ${rotationname} "Dark Lord's Unity (Azia)" AA ${Parse[0,"( !${Me.Buff[${Me.AltAbility[Dark Lord's Unity (Azia)].Spell.Trigger[1].BaseName}].ID} )"]}

    } else { 
        /call AddToRotation  ${rotationname} "${Skin}"         Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation  ${rotationname} "${Horror}"     Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation  ${rotationname} "${Demeanor}"     Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation  ${rotationname} "${CloakHP}"     Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation  ${rotationname} "${SelfDS}"     Spell ${Parse[0,"( SELFBUFFCHECK && && ${FindItemCount[${Spell[${SelfDS}].NoExpendReagentID[1]}]} >= 1)"]}
        /call AddToRotation  ${rotationname} "${Shroud}"     Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation  ${rotationname} "${Convenant}" Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation  ${rotationname} "${CallAtk}"     Spell ${Parse[0,"( SELFBUFFCHECK )"]}
    }
        /call AddToRotation "${rotationname}" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
        /call AddToRotation "${rotationname}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
        /call AddToRotation "${rotationname}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==1 && ${Me.Mount.ID} && ${DoMelee[SETTINGVAL]} )"]}
        /call AddToRotation  ${rotationname} "${Skin}"         Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation  ${rotationname} "${TempHP}"         Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation  ${rotationname} "${Healburn}"         Spell ${Parse[0,"( SELFBUFFCHECK )"]}
        /call AddToRotation  ${rotationname} "Voice of Thule" AA ${Parse[0,"( SELFBUFFAACHECK && (${target_id} == ${Group.MainTank.ID}) )"]}
        /call AddToRotation     ${rotationname} "${PetSpell}"    Spell ${Parse[0,"(!${Me.Pet.ID} && ${DoPet[SETTINGVAL]} && ${FindItemCount[${Spell[${PetSpell}].ReagentID[1]}]} )"]}
    |- Pet Buff Rotation 
    /call AddToRotation  ${rotationname} "${PetHaste}" Spell ${Parse[0,"( SELFBUFFPETCHECK )"]}
/return

Sub SHD_Combat_Routine
    /if (!DODPS && ${IsTanking}) /call PetAttack

    | Should pet be in here?
    /if (DODPS) {
        /if (${IsTanking}) /call PetAttack

|        /if (${Me.PctHPs}<=${Flashhp[SETTINGVAL]})    /call AAnow "Shield Flash"
|        /if (${FindItem[=${Epic}].TimerReady} && ${Me.PctHPs}<=${Flashhp[SETTINGVAL]}) /call ItemNow "${Epic}"
        /if ( BURNCHECK ) {
            /call Ordered_Rotation_Follow SHD_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE FROMHERE
        }
        /call Ordered_Rotation_Follow SHD_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE FROMHERE
    }
/return FALSE

Sub SHD_Downtime_Routine
    |- Call Self buffs
    /call FollowRotation  SHD_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}

    /if (${Me.Pet.ID}) {
        /call FollowRotation  SHD_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.Pet.ID}
    } 
/return FALSE

Sub FacePull
    /if (${Me.Level}>20 && ${Me.AbilityReady[Taunt]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30) {
        /call AbilityNow "Taunt" ${autotargetid}
    } else {
        /if (!${Me.Combat}) /attack on
    }
/return

Sub SHD_PullSetup
    /if (${Me.Pet.ID} && ${DoPetPull[SETTINGVAL]} ) {
        /call Pull_SetAbility "pullpet" "Special"
    } else /if (${Me.Inventory[ranged].Type.Equal[Archery]} && ${Me.Inventory[ammo].Stack} > 50) {
        /call Pull_SetAbility "pullrange" "Special"
    } else /if (${ForPower.NotEqual[NULL]}&&${Me.Gem[${ForPower}]}) {
        /call Pull_SetAbility "${ForPower}" Spell 
    } else /if (${Terror.NotEqual[NULL]}&&${Me.Gem[${Terror}]}) {
        /call Pull_SetAbility "${Terror}" Spell 
    } else /if (${DoSnare[SETTINGVAL]} && ${Me.Gem[${SnareDOT}]}) {
        /call Pull_SetAbility "${SnareDOT}" Spell 
    } else {
        /call Pull_SetAbility "/call FacePull" Command
    }
/return