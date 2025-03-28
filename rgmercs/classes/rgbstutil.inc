|- rgbstutil.inc
|- Version 2.0
|- Updated: Terror of Luclin launch dec 07 2021

| - Mode Dps Is Intended for Levels 1-115 And is Beastlord is Designed with OneModeToRuleThemAll
#define MODEDPS 0
#define MODETLP 2
|--------------------------------------------------------------------------------------
|- Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub BST_Setup
|- List containing BST specific settings settings
    /declare RGList_BST         list outer
|- Items
    /call ItemSet_New Epic

|- Spells
    /call AbilitySet_New SwarmPet
    /call AbilitySet_New FrozenPoi
    /call AbilitySet_New Maelstrom
    /call AbilitySet_New PoiBite
    /call AbilitySet_New Icelance1
    /call AbilitySet_New Icelance2
    /call AbilitySet_New EndemicDot
    /call AbilitySet_New Blooddot
    /call AbilitySet_New Colddot
    /call AbilitySet_New SlowSpell
    /call AbilitySet_New DichoSpell
    /call AbilitySet_New HealSpell
    /call AbilitySet_New PetHealSpell
    /call AbilitySet_New PetSpell
    /call AbilitySet_New PetEnduranceProc
    /call AbilitySet_New PetSpellGuard
    /call AbilitySet_New PetSlowProc
    /call AbilitySet_New PetOffenseBuff
    /call AbilitySet_New PetDefenseBuff
    /call AbilitySet_New PetHaste
    /call AbilitySet_New PetGrowl
    /call AbilitySet_New PetHealProc
    /call AbilitySet_New PetDamageProc
    /call AbilitySet_New UnityBuff
    /call AbilitySet_New KillShotBuff
    /call AbilitySet_New RunSpeedBuff
    /call AbilitySet_New ManaRegenBuff
    /call AbilitySet_New ManaRegenBuffName
    /call AbilitySet_New AtkHPBuffName
    /call AbilitySet_New AllianceDot
    /call AbilitySet_New PetBlockSpell
    /call AbilitySet_New PetBlockAuspice
    /call AbilitySet_New PetHotSpell
    /call AbilitySet_New PetPromisedSpell
    /call AbilitySet_New AvatarSpell
    /call AbilitySet_New PetCrippleBite
| - Single target - broken up into Single and group versions for mana Purposes
    /call AbilitySet_New SingleFocusSpell
    /call AbilitySet_New SingleAtkHPBuff
    /call AbilitySet_New SingleAtkBuff
| - Group Versions of the Above Spells
    /call AbilitySet_New GroupFocusSpell
    /call AbilitySet_New GroupAtkHPBuff
    /call AbilitySet_New GroupAtkBuff
|- discs
    /call AbilitySet_New EndRegenDisc
    /call AbilitySet_New Maul
    /call AbilitySet_New SingleClaws
    /call AbilitySet_New BeastialBuffDisc
    /call AbilitySet_New AEClaws
    /call AbilitySet_New HHEFuryDisc
    /call AbilitySet_New DmgModDisc
    /call AbilitySet_New EndRegenProcDisc
    /call AbilitySet_New Vindisc

|- Live  Rotations
    /call Ordered_Rotation_New BST_Debuff_MODEDPS_Rotation
    /call Ordered_Rotation_New BST_Heal_MODEDPS_Rotation
    /call Ordered_Rotation_New BST_DPS_MODEDPS_Rotation
    /call Ordered_Rotation_New BST_Downtime_MODEDPS_Rotation
    /call Ordered_Rotation_New BST_Burn_MODEDPS_Rotation

|- TLP Rotations
    /call Ordered_Rotation_New BST_Debuff_MODETLP_Rotation
    /call Ordered_Rotation_New BST_Heal_MODETLP_Rotation
    /call Ordered_Rotation_New BST_DPS_MODETLP_Rotation
    /call Ordered_Rotation_New BST_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New BST_Burn_MODETLP_Rotation

|-Config Options
    /call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = DPS Set 2 = TLP
    /call RGLoadSetting BST DoAoe 0 Combat "Determines whether to use AOE attacks that make Break mez Default Off"
    /call RGLoadSetting BST DoRunSpeed 1 Buffs "Set 0/1 the casting of the run speed buff."
    /call RGLoadSetting BST ChestItemName "${Me.Inventory[17].Name}" Item "Name of your chest item -- defaults to the slot"
	/call RGLoadSetting BST DoBandolier 0 Combat "Sets whether to use auto bandolier functions. Requires a bandolier called DW (two 1-hand weapons) and one called 2H"
|- Healing Settings
    /call RGLoadSetting BST DoHeals 1 Combat "Set 0/1 to enable healing. Checked in the Main Loop. "
    /call RGLoadSetting BST LightHealPoint 50 Combat "Sets The % to heal People at"
    /call RGLoadSetting BST PetHealPoint 75 Combat "% Health to start healing your pet."
    /call RGLoadSetting BST DoPara 1 Combat "0/1 Auto Cast Paragon"
| -  Pet Settings
    /call RGLoadSetting BST DoPet 1 Combat "Set 0/1 the use of pets."
    /call RGLoadSetting BST DoPetTank 0 Combat "Set 0/1 to use your pet as a tank."
    /call RGLoadSetting BST DoSwarmPet 1 Combat "Set 0/1 to use the BST swarm pet."
    /call RGLoadSetting BST DoSnare 1 Combat "Set 0/1 to Turn off Hobble of Spirits AA for pet snares"

|- Mana Control Nukes Dots Etc..
    /call RGLoadSetting BST Manatonuke 30 Combat "% Mana to stop nuking at."
    /call RGLoadSetting BST HPStopDOT 30 Combat "%HP to cut off to stop casting dots."
    /call RGLoadSetting BST DoDot 1 Combat "Set 0/1 the use of BST DoTs."
    /call RGLoadSetting BST ParagonManaPct 80 Combat "what % Mana to Use Paragon on a Group member.Uses Focused if Normal is Down."

|- Debuffs
    /call RGLoadSetting BST AutoDebuffAt 99 Debuff "%HP to debuff Mobs." 1
    /call RGLoadSetting BST DoPetSlow 0 Pet "Set 0/1 buffing the BST pet with the slow proc spell."
    /call RGLoadSetting BST DoSlow 1 Combat "Set 0/1 the use of BST Slows."
|- Combat Fero Buff List
    /call RGLoadSetting BST DoCombatFero 0 Combat "Set 0/1 to Enable Doing Fero In Combat" 1
    /call RGLoadSetting BST CfList "NULL" Combat  "Pipe | Delimited priority list of Ferocity During Combat with DoCombatfero=1" 1


|-Declare spell variables
    /declare spellmisc          int outer 8
    /declare GroupBuffRecast    int outer 0
    /declare miscspellremem     string outer NULL
    /declare FeroCheck          timer outer 0

    /declare Spell1     string outer NULL
    /declare Spell2     string outer NULL
    /declare Spell3     string outer NULL
    /declare Spell4     string outer NULL
    /declare Spell5     string outer NULL
    /declare Spell6     string outer NULL
    /declare Spell7     string outer NULL
    /declare Spell8     string outer NULL
    /declare Spell9     string outer NULL
    /declare Spell10    string outer NULL
    /declare Spell11    string outer NULL
    /declare Spell12    string outer NULL
    /declare Spell13    string outer NULL

    /declare spellrememtimer    timer outer 0
    /declare fparatimer2        timer outer 60s
    /declare groupbufftimer     timer outer 0
    /if (${Me.AltAbility[Mnemonic Retention].Rank}==5) /varset spellmisc 13
    /if (${Me.AltAbility[Mnemonic Retention].Rank}==4) /varset spellmisc 12
    /if (${Me.AltAbility[Mnemonic Retention].Rank}==3) /varset spellmisc 11
    /if (${Me.AltAbility[Mnemonic Retention].Rank}==2) /varset spellmisc 10
    /if (${Me.AltAbility[Mnemonic Retention].Rank}==1) /varset spellmisc 9
    /if (${Me.AltAbility[8300].Name.Find[disabled]} && ${RG_AAReady[8300]}) {
        /alt act 8300
        /delay 5
    }
/return

|----------------------------------------------------------------------------
|- SUB: SetupSkills
|----------------------------------------------------------------------------
Sub BST_SetupSkills
|- Items
|- Epic
    /call ItemSet_Add "Savage Lord's Totem"             Epic    | Epic 1.5
    /call ItemSet_Add "Spiritcaller Totem of the Feral" Epic    | Epic 2.0
    /call ItemSet_ChooseOuter Epic Epic
|- Epic Buffs
    | Epic 1.5 Buff
    /declare EpicBuff1 string outer "Savage Wildcaller's Blessing"
    | Epic 2.0 Buff
    /declare EpicBuff2 string outer "Might of the Wild Spirits"

|- Alliance Spell for Beastlords 100+
    /call AbilitySet_Add "Venomous Alliance"    AllianceDot | Level 101
    /call AbilitySet_Add "Venomous Covenant"    AllianceDot | Level 108
    /call AbilitySet_Add "Venomous Coalition"   AllianceDot | Level 113
    /call AbilitySet_Add "Venomous Conjunction" AllianceDot | Level 118
    /call AbilitySet_ChooseOuter AllianceDot AllianceDot

|- Beast Pet Ward Line Timer 10
    /call AbilitySet_Add "Ward of Calliav"          PetBlockSpell   | Level 49
    /call AbilitySet_Add "Guard of Calliav"         PetBlockSpell   | Level 58
    /call AbilitySet_Add "Protection of Calliav"    PetBlockSpell   | Level 64
    /call AbilitySet_Add "Feral Guard"              PetBlockSpell   | Level 69
    /call AbilitySet_Add "Mammoth-Hide Guard"       PetBlockSpell   | Level 71
    /call AbilitySet_Add "Dragonscale Guard"        PetBlockSpell   | Level 76
    /call AbilitySet_Add "Bulwark of Tri'Qaras"     PetBlockSpell   | Level 77
    /call AbilitySet_Add "Spectral Rampart"         PetBlockSpell   | Level 88
    /call AbilitySet_Add "Beastwood Rampart"        PetBlockSpell   | Level 93
    /call AbilitySet_Add "Aegis of Nefori"          PetBlockSpell   | Level 99
    /call AbilitySet_Add "Aegis of Japac"           PetBlockSpell   | Level 104
    /call AbilitySet_Add "Aegis of Zeklor"          PetBlockSpell   | Level 109
    /call AbilitySet_Add "Aegis of Orfur"           PetBlockSpell   | Level 114
    /call AbilitySet_Add "Aegis of Rumblecrush"     PetBlockSpell   | Level 119
    /call AbilitySet_Add "Aegis of Valorforged"     PetBlockSpell   | Level 124
    /call AbilitySet_ChooseOuter PetBlockSpell PetBlockSpell

|- Pet Block Auspice - Timer 16
    /call AbilitySet_Add "Auspice of Shadows"       PetBlockAuspice | Level 96
    /call AbilitySet_Add "Auspice of Eternity"      PetBlockAuspice | Level 102
    /call AbilitySet_Add "Auspice of Esianti"       PetBlockAuspice | Level 107
    /call AbilitySet_Add "Auspice of Kildrukaun"    PetBlockAuspice | Level 112
    /call AbilitySet_Add "Auspice of Valia"         PetBlockAuspice | Level 117
    /call AbilitySet_ChooseOuter PetBlockAuspice PetBlockAuspice

|- Swarm Pet
    /call AbilitySet_Add "Bestial Empathy"      SwarmPet    | Level 68
    /call AbilitySet_Add "Bark at the Moon"     SwarmPet    | Level 75
    /call AbilitySet_Add "Howl at the Moon"     SwarmPet    | Level 80
    /call AbilitySet_Add "Haergen's Feralgia"   SwarmPet    | Level 85
    /call AbilitySet_Add "Tuzil's Feralgia"     SwarmPet    | Level 90
    /call AbilitySet_Add "Yahnoa's Feralgia"    SwarmPet    | Level 95
    /call AbilitySet_Add "Kesar's Feralgia"     SwarmPet    | Level 100
    /call AbilitySet_Add "Krenk's Feralgia"     SwarmPet    | Level 105
    /call AbilitySet_Add "Akalit's Feralgia"    SwarmPet    | Level 110
    /call AbilitySet_Add "Griklor's Feralgia"   SwarmPet    | Level 115
    /call AbilitySet_Add "Ander's Feralgia"     SwarmPet    | Level 120
    /call AbilitySet_Add "SingleMalt's Feralgia" SwarmPet   | Level 125 
    /call AbilitySet_ChooseOuter SwarmPet SwarmPet

|- Cold/Poison Nuke Fast Cast
    /call AbilitySet_Add "Frozen Venom"         FrozenPoi   | Level 84
    /call AbilitySet_Add "Frozen Venin"         FrozenPoi   | Level 89
    /call AbilitySet_Add "Frozen Cyanin"        FrozenPoi   | Level 94
    /call AbilitySet_Add "Frozen Carbomate"     FrozenPoi   | Level 99
    /call AbilitySet_Add "Frozen Miasma"        FrozenPoi   | Level 103
    /call AbilitySet_Add "Frozen Toxin"         FrozenPoi   | Level 108
    /call AbilitySet_Add "Frozen Malignance"    FrozenPoi   | Level 113
    /call AbilitySet_Add "Frozen Blight"        FrozenPoi   | Level 118
    /call AbilitySet_Add "Frozen Creep"         FrozenPoi   | Level 123
    /call AbilitySet_ChooseOuter FrozenPoi FrozenPoi

|- Cold/Poison/Disease Nuke Fast Cast
    /call AbilitySet_Add "Kron's Maelstrom"         Maelstrom   | Level 90
    /call AbilitySet_Add "Bale's Maelstrom"         Maelstrom   | Level 95
    /call AbilitySet_Add "Nak's Maelstrom"          Maelstrom   | Level 100
    /call AbilitySet_Add "Visoracius' Maelstrom"    Maelstrom   | Level 105
    /call AbilitySet_Add "Beramos' Maelstrom"       Maelstrom   | Level 110
    /call AbilitySet_Add "Vkjen's Maelstrom"        Maelstrom   | Level 115
    /call AbilitySet_Add "Va Xakra's Maelstrom"     Maelstrom   | Level 120
    /call AbilitySet_Add "Rimeclaw's Maelstrom"     Maelstrom   | Level 125
    /call AbilitySet_ChooseOuter Maelstrom Maelstrom

|- Poison Nuke Fast Cast
    /call AbilitySet_Add "Bite of the Empress"  PoiBite | Level 73
    /call AbilitySet_Add "Bite of the Borrower" PoiBite | Level 78
    /call AbilitySet_Add "Bite of the Vitrik"   PoiBite | Level 83
    /call AbilitySet_Add "Sarsez' Bite"         PoiBite | Level 88
    /call AbilitySet_Add "Rotsil's Bite"        PoiBite | Level 93
    /call AbilitySet_Add "Poantaar's Bite"      PoiBite | Level 98
    /call AbilitySet_Add "Kreig's Bite"         PoiBite | Level 103
    /call AbilitySet_Add "Mawmun's Bite"        PoiBite | Level 108
    /call AbilitySet_Add "Bloodmaw's Bite"      PoiBite | Level 113
    /call AbilitySet_Add "Zelniak's Bite"       PoiBite | Level 118
    /call AbilitySet_Add "Mortimus' Bite"       PoiBite | Level 123
    /call AbilitySet_ChooseOuter PoiBite PoiBite

|- Lance 1 Timer 7 Ice Nuke Fast Cast
    /call AbilitySet_Add "Blast of Frost"           Icelance1    | Level 12 - Timer 7
    /call AbilitySet_Add "Frost Shard"              Icelance1    | Level 47 - Timer 7
    /call AbilitySet_Add "Blizzard Blast"           Icelance1    | Level 59 - Timer ???
    /call AbilitySet_Add "Frost Spear"              Icelance1    | Level 63 - Timer 7
    /call AbilitySet_Add "Ancient: Frozen Chaos"    Icelance1    | Level 65 - Timer 7
    /call AbilitySet_Add "Ancient: Savage Ice"      Icelance1    | Level 70 - Timer 7
    /call AbilitySet_Add "Jagged Torrent"           Icelance1    | Level 79 - Timer 7
    /call AbilitySet_Add "Glacial Lance"            Icelance1    | Level 89 - Timer 7
    /call AbilitySet_Add "Kromrif Lance"            Icelance1    | Level 99 - Timer 7
    /call AbilitySet_Add "Frostbite Lance"          Icelance1    | Level 107 - Timer 7
    /call AbilitySet_Add "Crystalline Lance"        Icelance1    | Level 117 - Timer 7
    /call AbilitySet_Add "Ankexfen Lance"           Icelance1    | Level 122 - Timer 7
    /call AbilitySet_ChooseOuter Icelance1 Icelance1

|- Lance 2 Timer 11 Ice Nuke Fast Cast
    /call AbilitySet_Add "Ice Spear"                Icelance2    | Level 33 - Timer 11
    /call AbilitySet_Add "Ice Shard"                Icelance2    | Level 54 - Timer 11
    /call AbilitySet_Add "Trushar's Frost"          Icelance2    | Level 65 - Timer 11
    /call AbilitySet_Add "Glacier Spear"            Icelance2    | Level 69 - Timer 11
    /call AbilitySet_Add "Spiked Sleet"             Icelance2    | Level 74 - Timer 11
    /call AbilitySet_Add "Frigid Lance"             Icelance2    | Level 84 - Timer 11
    /call AbilitySet_Add "Frostrift Lance"          Icelance2    | Level 94 - Timer 11
    /call AbilitySet_Add "Kromtus Lance"            Icelance2    | Level 102 - Timer 11
    /call AbilitySet_Add "Restless Lance"           Icelance2    | Level 112 - Timer 11
    /call AbilitySet_ChooseOuter Icelance2 Icelance2

|- Disease DoT Instant Cast
    /call AbilitySet_Add "Sicken"                       EndemicDot    | Level 14
    /call AbilitySet_Add "Malaria"                      EndemicDot    | Level 40
    /call AbilitySet_Add "Plague"                       EndemicDot    | Level 65
    /call AbilitySet_Add "Festering Malady"             EndemicDot    | Level 70
    /call AbilitySet_Add "Fever Spike"                  EndemicDot    | Level 72
    /call AbilitySet_Add "Fever Surge"                  EndemicDot    | Level 77
    /call AbilitySet_Add "Tsetsian Endemic"             EndemicDot    | Level 82
    /call AbilitySet_Add "Shiverback Endemic"           EndemicDot    | Level 87
    /call AbilitySet_Add "Silbar's Endemic"             EndemicDot    | Level 92
    /call AbilitySet_Add "Natigo's Endemic"             EndemicDot    | Level 97
    /call AbilitySet_Add "Hemocoraxius' Endemic"        EndemicDot    | Level 102
    /call AbilitySet_Add "Elkikatar's Endemic"          EndemicDot    | Level 107
    /call AbilitySet_Add "Neemzaq's Endemic"            EndemicDot    | Level 112
    /call AbilitySet_Add "Vampyric Endemic"             EndemicDot    | Level 117
    /call AbilitySet_Add "Fevered Endemic"              EndemicDot    | Level 122  
    /call AbilitySet_ChooseOuter EndemicDot EndemicDot

|- Poison DoT Instant Cast
    /call AbilitySet_Add "Tainted Breath"       Blooddot    | Level 19
    /call AbilitySet_Add "Envenomed Breath"     Blooddot    | Level 35
    /call AbilitySet_Add "Venom of the Snake"   Blooddot    | Level 52
    /call AbilitySet_Add "Scorpion Venom"       Blooddot    | Level 61
    /call AbilitySet_Add "Turepta Blood"        Blooddot    | Level 65
    /call AbilitySet_Add "Chimera Blood"        Blooddot    | Level 66
    /call AbilitySet_Add "Diregriffon's Bite"   Blooddot    | Level 71
    /call AbilitySet_Add "Falrazim's Gnashing"  Blooddot    | Level 76
    /call AbilitySet_Add "Ikaav Blood"          Blooddot    | Level 81
    /call AbilitySet_Add "Spinechiller Blood"   Blooddot    | Level 90
    /call AbilitySet_Add "Binaesa Blood"        Blooddot    | Level 91
    /call AbilitySet_Add "Asp Blood"            Blooddot    | Level 96
    /call AbilitySet_Add "Glistenwing Blood"    Blooddot    | Level 101
    /call AbilitySet_Add "Polybiad Blood"       Blooddot    | Level 106
    /call AbilitySet_Add "Ikatiar's Blood"      Blooddot    | Level 111
    /call AbilitySet_Add "Akhevan Blood"        Blooddot    | Level 116
    /call AbilitySet_Add "Forgebound Blood"     Blooddot    | Level 121
    /call AbilitySet_ChooseOuter Blooddot Blooddot

|- Cold DoT Instant Cast
    /call AbilitySet_Add "Edoth's Chill"        Colddot | Level 99
    /call AbilitySet_Add "Kirchen's Chill"      Colddot | Level 104
    /call AbilitySet_Add "Ekron's Chill"        Colddot | Level 109
    /call AbilitySet_Add "Endaroky's Chill"     Colddot | Level 114
    /call AbilitySet_Add "Sylra Fris' Chill"    Colddot | Level 119
    /call AbilitySet_Add "Lazam's Chill"        Colddot | Level 124
    /call AbilitySet_ChooseOuter Colddot Colddot

|- Dicho Spell
    /call AbilitySet_Add "Dichotomic Fury"  DichoSpell  | Level 101
    /call AbilitySet_Add "Dissident Fury"   DichoSpell  | Level 106
    /call AbilitySet_Add "Composite Fury"   DichoSpell  | Level 111
    /call AbilitySet_Add "Ecliptic Fury"    DichoSpell  | Level 116
    /call AbilitySet_ChooseOuter DichoSpell DichoSpell

|- Slow Spell
    /call AbilitySet_Add "Drowsy"           SlowSpell   | Level 20
    /call AbilitySet_Add "Sha's Lethargy"   SlowSpell   | Level 50
    /call AbilitySet_Add "Sha's Advantage"  SlowSpell   | Level 60
    /call AbilitySet_Add "Sha's Revenge"    SlowSpell   | Level 65
    /call AbilitySet_Add "Sha's Legacy"     SlowSpell   | Level 70
    /call AbilitySet_Add "Sha's Reprisal"   SlowSpell   | Level 87
    /call AbilitySet_ChooseOuter SlowSpell SlowSpell

|- Single Target HealSpell
    /call AbilitySet_Add "Salve"                HealSpell   | Level 1
    /call AbilitySet_Add "Minor Healing"        HealSpell   | Level 6
    /call AbilitySet_Add "Light Healing"        HealSpell   | Level 18
    /call AbilitySet_Add "Healing"              HealSpell   | Level 28
    /call AbilitySet_Add "Greater Healing"      HealSpell   | Level 38
    /call AbilitySet_Add "Spirit Salve"         HealSpell   | Level 48
    /call AbilitySet_Add "Chloroblast"          HealSpell   | Level 59
    /call AbilitySet_Add "Trushar's Mending"    HealSpell   | Level 65
    /call AbilitySet_Add "Muada's Mending"      HealSpell   | Level 67
    /call AbilitySet_Add "Minohten Mending"     HealSpell   | Level 72
    /call AbilitySet_Add "Daria's Mending"      HealSpell   | Level 77
    /call AbilitySet_Add "Cadmael's Mending"    HealSpell   | Level 82
    /call AbilitySet_Add "Jorra's Mending"      HealSpell   | Level 87
    /call AbilitySet_Add "Mending of the Izon"  HealSpell   | Level 92
    /call AbilitySet_Add "Jaerol's Mending"     HealSpell   | Level 97
    /call AbilitySet_Add "Sabhattin's Mending"  HealSpell   | Level 102
    /call AbilitySet_Add "Deltro's Mending"     HealSpell   | Level 107
    /call AbilitySet_Add "Bethun's Mending"     HealSpell   | Level 112
    /call AbilitySet_Add "Korah's Mending"      HealSpell   | Level 117
    /call AbilitySet_Add "Thornhost's Mending"  HealSpell   | Level 122
    /call AbilitySet_ChooseOuter HealSpell HealSpell

|- Pet Heal
    /call AbilitySet_Add "Sharik's Replenishing"    PetHealSpell    | Level 9
    /call AbilitySet_Add "Keshuval's Rejuvenation"  PetHealSpell    | Level 15
    /call AbilitySet_Add "Herikol's Soothing"       PetHealSpell    | Level 27
    /call AbilitySet_Add "Yekan's Recovery"         PetHealSpell    | Level 36
    /call AbilitySet_Add "Vigor of Zehkes"          PetHealSpell    | Level 49
    /call AbilitySet_Add "Aid of Khurenz"           PetHealSpell    | Level 52
    /call AbilitySet_Add "Sha's Restoration"        PetHealSpell    | Level 55
    /call AbilitySet_Add "Healing of Sorsha"        PetHealSpell    | Level 61
    /call AbilitySet_Add "Healing of Mikkily"       PetHealSpell    | Level 66
    /call AbilitySet_Add "Healing of Uluanes"       PetHealSpell    | Level 71
    /call AbilitySet_Add "Salve of Feldan"          PetHealSpell    | Level 76
    /call AbilitySet_Add "Salve of Reshan"          PetHealSpell    | Level 81
    /call AbilitySet_Add "Salve of Sevna"           PetHealSpell    | Level 86
    /call AbilitySet_Add "Salve of Yubai"           PetHealSpell    | Level 91
    /call AbilitySet_Add "Salve of Blezon"          PetHealSpell    | Level 96
    /call AbilitySet_Add "Salve of Clorith"         PetHealSpell    | Level 101
    /call AbilitySet_Add "Salve of Artikla"         PetHealSpell    | Level 106
    /call AbilitySet_Add "Salve of Tobart"          PetHealSpell    | Level 111
    /call AbilitySet_Add "Salve of Jaegir"          PetHealSpell    | Level 116
    /call AbilitySet_Add "Salve of Homer"           PetHealSpell    | Level 121
    /call AbilitySet_ChooseOuter PetHealSpell PetHealSpell

|- Pet Promised
    /call AbilitySet_Add "Promised Mending"         PetPromisedSpell    | Level 73
    /call AbilitySet_Add "Promised Recovery"        PetPromisedSpell    | Level 78
    /call AbilitySet_Add "Promised Rejuvenation"    PetPromisedSpell    | Level 83
    /call AbilitySet_Add "Promised Wardmending"     PetPromisedSpell    | Level 88
    /call AbilitySet_Add "Promised Amendment"       PetPromisedSpell    | Level 93
    /call AbilitySet_Add "Promised Amelioration"    PetPromisedSpell    | Level 98
    /call AbilitySet_Add "Promised Invigoration"    PetPromisedSpell    | Level 103
    /call AbilitySet_Add "Promised Alleviation"     PetPromisedSpell    | Level 108
    /call AbilitySet_Add "Promised Healing"         PetPromisedSpell    | Level 113
    /call AbilitySet_Add "Promised Relief"          PetPromisedSpell    | Level 118
    /call AbilitySet_Add "Promised Reconstitution"  PetPromisedSpell    | Level 123
    /call AbilitySet_ChooseOuter PetPromisedSpell PetPromisedSpell

|- Pet Hot Spell
    /call AbilitySet_Add "Minax's Mending"          PetHotSpell | Level 82
    /call AbilitySet_Add "Wilap's Mending"          PetHotSpell | Level 87
    /call AbilitySet_Add "Yurv's Mending"           PetHotSpell | Level 92
    /call AbilitySet_Add "Huaene's Melioration"     PetHotSpell | Level 97
    /call AbilitySet_Add "Tirik's Melioration"      PetHotSpell | Level 102
    /call AbilitySet_Add "Virzak's Melioration"     PetHotSpell | Level 107
    /call AbilitySet_Add "Kallis' Melioration"      PetHotSpell | Level 112
    /call AbilitySet_Add "Cissela's Melioration"    PetHotSpell | Level 117
    /call AbilitySet_ChooseOuter PetHotSpell PetHotSpell

|- Str Stam Dex Buff
    /call AbilitySet_Add "Infusion of Spirit"   AvatarSpell | Level 61
    /call AbilitySet_ChooseOuter AvatarSpell AvatarSpell

|- ATK Buff
    | - Single Ferocity
    /call AbilitySet_Add "Savagery"             SingleAtkBuff   | Level 60
    /call AbilitySet_Add "Ferocity"             SingleAtkBuff   | Level 65
    /call AbilitySet_Add "Ferocity of Irionu"   SingleAtkBuff   | Level 70
    /call AbilitySet_Add "Ruthless Ferocity"    SingleAtkBuff   | Level 75
    /call AbilitySet_Add "Vicious Ferocity"     SingleAtkBuff   | Level 80
    /call AbilitySet_Add "Savage Ferocity"      SingleAtkBuff   | Level 85
    /call AbilitySet_Add "Callous Ferocity"     SingleAtkBuff   | Level 90
    /call AbilitySet_Add "Brutal Ferocity"      SingleAtkBuff   | Level 92
    /call AbilitySet_ChooseOuter SingleAtkBuff SingleAtkBuff
    |- Group Ferocity
    /call AbilitySet_Add "Shared Brutal Ferocity"       GroupAtkBuff    | Level 95
    /call AbilitySet_Add "Shared Merciless Ferocity"    GroupAtkBuff    | Level 100
    /call AbilitySet_ChooseOuter GroupAtkBuff GroupAtkBuff

|- Pet
    /call AbilitySet_Add "Spirit of Sharik"     PetSpell    | Level 8
    /call AbilitySet_Add "Spirit of Khaliz"     PetSpell    | Level 15
    /call AbilitySet_Add "Spirit of Keshuval"   PetSpell    | Level 21
    /call AbilitySet_Add "Spirit of Herikol"    PetSpell    | Level 30
    /call AbilitySet_Add "Spirit of Yekan"      PetSpell    | Level 39
    /call AbilitySet_Add "Spirit of Kashek"     PetSpell    | Level 46
    /call AbilitySet_Add "Spirit of Omakin"     PetSpell    | Level 54
    /call AbilitySet_Add "Spirit of Zehkes"     PetSpell    | Level 56
    /call AbilitySet_Add "Spirit of Khurenz"    PetSpell    | Level 58
    /call AbilitySet_Add "Spirit of Khati Sha"  PetSpell    | Level 60
    /call AbilitySet_Add "Spirit of Arag"       PetSpell    | Level 62
    /call AbilitySet_Add "Spirit of Sorsha"     PetSpell    | Level 64
    /call AbilitySet_Add "Spirit of Alladnu"    PetSpell    | Level 68
    /call AbilitySet_Add "Spirit of Rashara"    PetSpell    | Level 70
    /call AbilitySet_Add "Spirit of Uluanes"    PetSpell    | Level 73
    /call AbilitySet_Add "Spirit of Silverwing" PetSpell    | Level 78
    /call AbilitySet_Add "Spirit of Hoshkar"    PetSpell    | Level 83
    /call AbilitySet_Add "Spirit of Averc"      PetSpell    | Level 88
    /call AbilitySet_Add "Spirit of Kolos"      PetSpell    | Level 93
    /call AbilitySet_Add "Spirit of Lachemit"   PetSpell    | Level 98
    /call AbilitySet_Add "Spirit of Avalit"     PetSpell    | Level 103
    /call AbilitySet_Add "Spirit of Akalit"     PetSpell    | Level 108
    /call AbilitySet_Add "Spirit of Blizzent"   PetSpell    | Level 113
    /call AbilitySet_Add "Spirit of Panthea"    PetSpell    | Level 118
    /call AbilitySet_Add "Spirit of Shae"       PetSpell    | Level 123
    /call AbilitySet_ChooseOuter PetSpell PetSpell

|-Buffs
 |- Focus Spells -
    | -Single target Talismans ( Like Focus)
    /call AbilitySet_Add "Inner Fire"           SingleFocusSpell
    /call AbilitySet_Add "Talisman of Tnarg"    SingleFocusSpell
    /call AbilitySet_Add "Talisman of Altuna"   SingleFocusSpell
    /call AbilitySet_Add "Talisman of Kragg"    SingleFocusSpell
    /call AbilitySet_Add "Focus of Alladnu"     SingleFocusSpell
    /call AbilitySet_ChooseOuter SingleFocusSpell SingleFocusSpell

|  - Group Focus Spells
    /call AbilitySet_Add "Focus of Amilan"  GroupFocusSpell
    /call AbilitySet_Add "Focus of Zott"    GroupFocusSpell
    /call AbilitySet_Add "Focus of Yemall"  GroupFocusSpell
    /call AbilitySet_Add "Focus of Emiq"    GroupFocusSpell
    /call AbilitySet_Add "Focus of Klar"    GroupFocusSpell
    /call AbilitySet_Add "Focus of Sanera"  GroupFocusSpell
    /call AbilitySet_Add "Focus of Okasi"   GroupFocusSpell
    /call AbilitySet_Add "Focus of Artikla" GroupFocusSpell
    /call AbilitySet_Add "Focus of Tobart"  GroupFocusSpell
    /call AbilitySet_Add "Focus of Jaegir"  GroupFocusSpell
    /call AbilitySet_Add "Focus of Skull Crusher" GroupFocusSpell
    /call AbilitySet_ChooseOuter GroupFocusSpell GroupFocusSpell

 |- Unity Mana/Hp/End Regen + Atk/HP Buff*
    /call AbilitySet_Add "Spiritual Unity"      UnityBuff
    /call AbilitySet_Add "Stormblood's Unity"   UnityBuff
    /call AbilitySet_Add "Feralist's Unity"     UnityBuff
    /call AbilitySet_Add "Reclaimer's Unity"    UnityBuff
    /call AbilitySet_Add "Chieftain's Unity"    UnityBuff
    /call AbilitySet_Add "Wildfang's Unity"     UnityBuff
    /call AbilitySet_ChooseOuter  UnityBuff UnityBuff

 |-Mana/Hp/End Regen Buff*
    /call AbilitySet_Add "Spiritual Light"          ManaRegenBuff
    /call AbilitySet_Add "Spiritual Radiance"       ManaRegenBuff
    /call AbilitySet_Add "Spiritual Purity"         ManaRegenBuff
    /call AbilitySet_Add "Spiritual Dominion"       ManaRegenBuff
    /call AbilitySet_Add "Spiritual Ascendance"     ManaRegenBuff
    /call AbilitySet_Add "Spiritual Enlightenment"  ManaRegenBuff
    /call AbilitySet_Add "Spiritual Epiphany"       ManaRegenBuff
    /call AbilitySet_Add "Spiritual Edification"    ManaRegenBuff
    /call AbilitySet_Add "Spiritual Enhancement"    ManaRegenBuff
    /call AbilitySet_Add "Spiritual Enrichment"     ManaRegenBuff
    /call AbilitySet_Add "Spiritual Evolution"      ManaRegenBuff
    /call AbilitySet_Add "Spiritual Elaboration"    ManaRegenBuff
    /call AbilitySet_Add "Spiritual Empowerment"    ManaRegenBuff
    /call AbilitySet_Add "Spiritual Enhancement"    ManaRegenBuff
    /call AbilitySet_Add "Spiritual Insight"        ManaRegenBuff
    /call AbilitySet_Add "Spiritual Erudition"      ManaRegenBuff
    /call AbilitySet_Add "Spiritual Enduement"      ManaRegenBuff
    /call AbilitySet_ChooseOuter ManaRegenBuff ManaRegenBuff

 |-Atk+HP Buff* - Does Not Stack with Pally brells or Ranger Buff - is Middle ground Buff has HP & Atk
    |- Single Target Atk+HpBuff
    /call AbilitySet_Add "Spiritual Brawn"       SingleAtkHPBuff
    /call AbilitySet_Add "Spiritual Strength"    SingleAtkHPBuff
    /call AbilitySet_ChooseOuter SingleAtkHPBuff SingleAtkHPBuff
    |- Group Attack+ Hp Buff
    /call AbilitySet_Add "Spiritual Vigor"          GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Vitality"       GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Vim"            GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Vivacity"       GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Verve"          GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Valor"          GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Valiance"       GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Vindication"    GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Vivification"   GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Vibrancy"       GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Vehemence"      GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Vigor"          GroupAtkHPBuff
    /call AbilitySet_Add "Spiritual Valiancy"       GroupAtkHPBuff
    /call AbilitySet_ChooseOuter GroupAtkHPBuff GroupAtkHPBuff

 |-Pet Dmg Absorb + HoT buff*
    /call AbilitySet_Add "Natural Collaboration"    KillShotBuff
    /call AbilitySet_Add "Natural Cooperation"      KillShotBuff
    /call AbilitySet_Add "Natural Affiliation"      KillShotBuff
    /call AbilitySet_Add "Natural Cooperation"      KillShotBuff
    /call AbilitySet_Add "Natural Alliance"         KillShotBuff
    /call AbilitySet_Add "Symbiotic Alliance"       KillShotBuff
    /call AbilitySet_Add "Warder's Alliance"        KillShotBuff
    /call AbilitySet_ChooseOuter KillShotBuff KillShotBuff

|-Pet Buffs
 |-Pet Group End Regen Proc*
    /call AbilitySet_Add "Fatiguing Bite"   PetEnduranceProc
    /call AbilitySet_Add "Exhausting Bite"  PetEnduranceProc
    /call AbilitySet_Add "Depleting Bite"   PetEnduranceProc
    /call AbilitySet_Add "Wearying Bite"    PetEnduranceProc
    /call AbilitySet_Add "Sapping Bite"     PetEnduranceProc
    /call AbilitySet_ChooseOuter PetEnduranceProc PetEnduranceProc

 |-Pet Growl Buff* 69-115
    /call AbilitySet_Add "Growl of the Panther"      PetGrowl
    /call AbilitySet_Add "Growl of the Puma"         PetGrowl
    /call AbilitySet_Add "Growl of the Jaguar"       PetGrowl
    /call AbilitySet_Add "Growl of the Tiger"        PetGrowl
    /call AbilitySet_Add "Growl of the Lion"         PetGrowl
    /call AbilitySet_Add "Growl of the Snow Leopard" PetGrowl
    /call AbilitySet_Add "Growl of the Leopard"      PetGrowl
    /call AbilitySet_Add "Growl of the Sabretooth"   PetGrowl
    /call AbilitySet_Add "Growl of the Lioness"      PetGrowl
    /call AbilitySet_Add "Growl of the Clouded Leopard" PetGrowl
    /call AbilitySet_ChooseOuter PetGrowl PetGrowl

 |-Pet Mitigate Spell Damage*
    /call AbilitySet_Add "Spellbreaker's Guard"     PetSpellGuard
    /call AbilitySet_Add "Spellbreaker's Bulwark"   PetSpellGuard
    /call AbilitySet_Add "Spellbreaker's Aegis"     PetSpellGuard
    /call AbilitySet_Add "Spellbreaker's Rampart"   PetSpellGuard
    /call AbilitySet_Add "Spellbreaker's Armor"     PetSpellGuard
    /call AbilitySet_Add "Spellbreaker's Ward"      PetSpellGuard
    /call AbilitySet_Add "Spellbreaker's Palisade"  PetSpellGuard
    /call AbilitySet_Add "Spellbreaker's Keep"      PetSpellGuard
    /call AbilitySet_Add "Spellbreaker's Citadel"   PetSpellGuard
    /call AbilitySet_Add "Spellbreaker's Fortress"  PetSpellGuard
    /call AbilitySet_Add "Spellbreaker's Synergy"   PetSpellGuard
    /call AbilitySet_ChooseOuter PetSpellGuard PetSpellGuard

 |-Pet Slow Proc*
    /call AbilitySet_Add "Steeltrap Jaws" PetSlowProc
    /call AbilitySet_Add "Lockfang Jaws"  PetSlowProc
    /call AbilitySet_Add "Fellgrip Jaws"  PetSlowProc
    /call AbilitySet_Add "Deadlock Jaws"  PetSlowProc
    /call AbilitySet_ChooseOuter PetSlowProc PetSlowProc

| Pet Cripple Bite
    /call AbilitySet_Add "Dire Bite" PetCrippleBite
    /call AbilitySet_ChooseOuter    PetCrippleBite PetCrippleBite

 |-Pet DPS buff*
    /call AbilitySet_Add "Neivr's Aggression"    PetOffenseBuff
    /call AbilitySet_Add "Mea's Aggression"      PetOffenseBuff
    /call AbilitySet_Add "Plakt's Aggression"    PetOffenseBuff
    /call AbilitySet_Add "Sekmoset's Aggression" PetOffenseBuff
    /call AbilitySet_Add "Virzak's Aggression"   PetOffenseBuff
    /call AbilitySet_Add "Horasug's Aggression"  PetOffenseBuff
    /call AbilitySet_Add "Panthea's Aggression"  PetOffenseBuff
    /call AbilitySet_Add "Magna's Aggression"   PetOffenseBuff
    /call AbilitySet_ChooseOuter PetOffenseBuff PetOffenseBuff

 |-Pet Tanking buff*
    /call AbilitySet_Add "Neivr's Protection"       PetDefenseBuff
    /call AbilitySet_Add "Mea's Protection"         PetDefenseBuff
    /call AbilitySet_Add "Plakt's Protection"       PetDefenseBuff
    /call AbilitySet_Add "Sekmoset's Protection"    PetDefenseBuff
    /call AbilitySet_Add "Virzak's Protection"      PetDefenseBuff
    /call AbilitySet_Add "Horasug's Protection"     PetDefenseBuff
    /call AbilitySet_Add "Panthea's Protection"     PetDefenseBuff
    /call AbilitySet_Add "Magna's Protection"       PetDefenseBuff
    /call AbilitySet_ChooseOuter PetDefenseBuff PetDefenseBuff

 |-Pet Haste*
    /call AbilitySet_Add "Yekan's Quickening"       PetHaste
    /call AbilitySet_Add "Bond of The Wild"         PetHaste
    /call AbilitySet_Add "Omakin's Alacrity"        PetHaste
    /call AbilitySet_Add "Sha's Ferocity"           PetHaste
    /call AbilitySet_Add "Arag's Celerity"          PetHaste
    /call AbilitySet_Add "Growl of the Beast"       PetHaste
    /call AbilitySet_Add "Unparalleled Voracity"    PetHaste
    /call AbilitySet_Add "Peerless Penchant"        PetHaste
    /call AbilitySet_Add "Unrivaled Rapidity"       PetHaste
    /call AbilitySet_Add "Incomparable Velocity"    PetHaste
    /call AbilitySet_Add "Exceptional Velocity"     PetHaste
    /call AbilitySet_Add "Extraordinary Velocity"   PetHaste
    /call AbilitySet_Add "Tremendous Velocity"      PetHaste
    /call AbilitySet_Add "Astounding Velocity"      PetHaste
    /call AbilitySet_Add "Unsurpassed Velocity"     PetHaste
    /call AbilitySet_Add "Insatiable Voracity"      PetHaste
    /call AbilitySet_ChooseOuter PetHaste PetHaste

 |-Pet Heal proc buff*
    /call AbilitySet_Add "Protective Warder"    PetHealProc
    /call AbilitySet_Add "Sympathetic Warder"   PetHealProc
    /call AbilitySet_Add "Convivial Warder"     PetHealProc
    /call AbilitySet_Add "Mending Warder"       PetHealProc
    /call AbilitySet_Add "Invigorating Warder"  PetHealProc
    /call AbilitySet_Add "Empowering Warder"    PetHealProc
    /call AbilitySet_Add "Bolstering Warder"    PetHealProc
    /call AbilitySet_Add "Friendly Pet" PetHealProc
    /call AbilitySet_ChooseOuter PetHealProc PetHealProc

 |-Pet Damage Proc Buff*
    /call AbilitySet_Add "Spirit of Shoru"          PetDamageProc
    /call AbilitySet_Add "Spirit of Lightning"      PetDamageProc
    /call AbilitySet_Add "Spirit of the Blizzard"   PetDamageProc
    /call AbilitySet_Add "Spirit of Inferno"        PetDamageProc
    /call AbilitySet_Add "Spirit of the Scorpion"   PetDamageProc
    /call AbilitySet_Add "Spirit of Vermin"         PetDamageProc
    /call AbilitySet_Add "Spirit of Wind"           PetDamageProc
    /call AbilitySet_Add "Spirit of the Storm"      PetDamageProc
    /call AbilitySet_Add "Spirit of Snow"           PetDamageProc
    /call AbilitySet_Add "Spirit of Flame"          PetDamageProc
    /call AbilitySet_Add "Spirit of Rellic"         PetDamageProc
    /call AbilitySet_Add "Spirit of Irionu"         PetDamageProc
    /call AbilitySet_Add "Spirit of Oroshar"        PetDamageProc
    /call AbilitySet_Add "Spirit of Lairn"          PetDamageProc
    /call AbilitySet_Add "Spirit of Jeswin"         PetDamageProc
    /call AbilitySet_Add "Spirit of Vaxztn"         PetDamageProc
    /call AbilitySet_Add "Spirit of Kron"           PetDamageProc
    /call AbilitySet_Add "Spirit of Bale"           PetDamageProc
    /call AbilitySet_Add "Spirit of Nak"            PetDamageProc
    /call AbilitySet_Add "Spirit of Visoracius"     PetDamageProc
    /call AbilitySet_Add "Spirit of Beramos"        PetDamageProc
    /call AbilitySet_Add "Spirit of Mandrikai"      PetDamageProc
    /call AbilitySet_Add "Spirit of Siver"          PetDamageProc
|   /call AbilitySet_Add "Ally's Unity" PetDamageProc
|   /call AbilitySet_Add "Comrade's Unity"  PetDamageproc
    /call AbilitySet_ChooseOuter PetDamageProc PetDamageProc

    |- RunSpeedBuff
    /call AbilitySet_Add "Spirit of wolf" RunSpeedBuff
| - Spirit of the Shrew Is Only 30% Speed Flat So Removed it from the List as its To Slow
|   /call AbilitySet_Add "Spirit of the Shrew" RunSpeedBuff
|   /call AbilitySet_Add "Pack Shrew" RunSpeedBuff
    /call AbilitySet_Add "Spirit of Tala'Tak" RunSpeedBuff
    /call AbilitySet_ChooseOuter RunSpeedBuff RunSpeedBuff

    |------Discs*
    |- Maul Disc - This is Used with Beastlord Synergy Buffs
    /call AbilitySet_Add "Rake"     Maul
    /call AbilitySet_Add "Harrow"   Maul
    /call AbilitySet_Add "Foray"    Maul
    /call AbilitySet_Add "Rush"     Maul
    /call AbilitySet_Add "Barrage"  Maul
    /call AbilitySet_Add "Pummel"   Maul
    /call AbilitySet_Add "Maul"     Maul
    /call AbilitySet_Add "Mangle"   Maul
    /call AbilitySet_Add "Batter"   Maul
    /call AbilitySet_Add "Clobber"  Maul
    /call AbilitySet_Add "Wallop"   Maul
    /call AbilitySet_ChooseOuter Maul Maul

    |-AE Claws*
    /call AbilitySet_Add "Flurry of Claws"      AEClaws
    /call AbilitySet_Add "Tumult of Claws"      AEClaws
    /call AbilitySet_Add "Clamor of Claws"      AEClaws
    /call AbilitySet_Add "Tempest of Claws"     AEClaws
    /call AbilitySet_Add "Storm of Claws"       AEClaws
    /call AbilitySet_Add "Maelstrom of Claws"   AEClaws
    /call AbilitySet_Add "Eruption of Claws"    AEClaws
    /call AbilitySet_Add "Barrage of Claws"     AEClaws
    /call AbilitySet_ChooseOuter AEClaws AEClaws

    |-Single target claws*
    /call AbilitySet_Add "Focused Clamor of Claws" SingleClaws
    /call AbilitySet_ChooseOuter SingleClaws SingleClaws

    |-Beastial Buff*
    /call AbilitySet_Add "Bestial Vivisection"  BeastialBuffDisc
    /call AbilitySet_Add "Bestial Rending"      BeastialBuffDisc
    /call AbilitySet_Add "Bestial Evulsing"     BeastialBuffDisc
    /call AbilitySet_Add "Bestial Savagery"     BeastialBuffDisc
    /call AbilitySet_Add "Bestial Fierceness"   BeastialBuffDisc
    /call AbilitySet_ChooseOuter BeastialBuffDisc BeastialBuffDisc

    |-HHE Burn Disc* - Dicho/Dissident Replace this @ 101
    /call AbilitySet_Add "Nature's Fury"    HHEFuryDisc
    /call AbilitySet_Add "Kolos' Fury"      HHEFuryDisc
    /call AbilitySet_Add "Ruaabri's Fury"   HHEFuryDisc
    /call AbilitySet_ChooseOuter HHEFuryDisc HHEFuryDisc

    |-All Skills Damage Modifier*
    /call AbilitySet_Add "Bestial Fury Discipline"  DmgModDisc
    /call AbilitySet_Add "Empathic Fury"            DmgModDisc
    /call AbilitySet_Add "Savage Fury"              DmgModDisc
    /call AbilitySet_Add "Savage Rage"              DmgModDisc
    /call AbilitySet_Add "Savage Rancor"            DmgModDisc
    /call AbilitySet_ChooseOuter DmgModDisc DmgModDisc

    |- Vindication DISC
    /call AbilitySet_Add "Al`ele's Vindication"     Vindisc
    /call AbilitySet_Add "Venon's Vindication"      Vindisc
    /call AbilitySet_Add "Ikatiar's Vindication"    Vindisc
    /call AbilitySet_Add "Kejaan's Vindication"     Vindisc
    /call AbilitySet_Add "Ikatiar's Vindication"    Vindisc
    /call AbilitySet_ChooseOuter Vindisc Vindisc

    |-Group End Regen*
    /call AbilitySet_Add "Reflexive Rending"    EndRegenProcDisc
    /call AbilitySet_Add "Reflexive Sundering"  EndRegenProcDisc
    /call AbilitySet_Add "Reflexive Riving"     EndRegenProcDisc
    /call AbilitySet_ChooseOuter EndRegenProcDisc EndRegenProcDisc

    |-End Regen -
    /call AbilitySet_Add "Respite"  EndRegenDisc
    /call AbilitySet_Add "Reprieve" EndRegenDisc
    /call AbilitySet_Add "Rest"     EndRegenDisc
    /call AbilitySet_Add "Breather" EndRegenDisc
    /call AbilitySet_Add "Hiatus"   EndRegenDisc
    /call AbilitySet_Add "Relax"    EndRegenDisc
    /call AbilitySet_Add "Night's Calming" EndRegenDisc
    /call AbilitySet_Add "Convalesce"   EndRegenDisc
    /call AbilitySet_ChooseOuter EndRegenDisc EndRegenDisc
/return


Sub BST_ModeConfigMODEDPS
    /varset IsHealing TRUE

    | For TLP we may not yet have Swarm Pet so turn it off
    /if (${SwarmPet.Equal[NULL]}) {
        /echo No Usable Swarm Pet Ability. Turning off DoSwarmPet.
        /varset DoSwarmPet[SETTINGVAL] 0
    }

| - BarSetup
    | - Gem1 - Always a heal Spell
    /varset Spell1 ${HealSpell}

    | - Gem2 - Always a PetHeal
    /varset Spell2 ${PetHealSpell}

    | - Gem3 & Gem 4 - Always Ice Lance
    /varset Spell3 ${Icelance1}
    /varset Spell4 ${Icelance2}

    |- Gem 5 - Always Blood DOT Spell
    /varset Spell5 ${Blooddot}

    | - Gem 6 - Ferocity
    |           95+ Group Version is Available, till then use Single
    /if (${GroupAtkBuff.NotEqual[NULL]}) {
        /varset Spell6 ${GroupAtkBuff}
    } else {
        /varset Spell6 ${SingleAtkBuff}
    }

    | - Gem 7 Slow Until We get the AA At 100. - Then it Becomes XXX?
    /if ( ${DoSlow[SETTINGVAL]} && !${Me.AltAbility[Sha's Reprisal].ID} ) {
        /varset Spell7 ${SlowSpell}
    } else {
        /varset Spell7 ${DichoSpell}
    }
    
    | - Gem 8 - PoitBite
    |           Swarm or Growl
    |   Only 8 Slots - If we only have 8 slots we are probably pre-OOW. No PoiBite, Swarm, or Growl yet.
    |                  Use as Misc Slot. If for some reason it is post-OOW and you have those abilities, buy your spell slot AA!
    |   9+ Slots     - If we are post-OOW try to use PoiBite if we have it (post-TBS). Otherwise fall back to slotting in Swarm (DoDH) or Growl (DoN).
    |                  Between OOW and DoN we don't have anything so will continue to be a misc slot.
    /if (${Me.NumGems} == 8) {
        /varset Spell8 NULL
    } else {
        /if (${PoiBite.NotEqual[NULL]}) {
            /varset Spell8 ${PoiBite}
        } else {
            /if (${DoSwarmPet[SETTINGVAL]}) {
                /varset Spell8 ${SwarmPet}
            } else {
                /varset Spell8 ${PetGrowl}
            }
        }
    }

    | - Gem 9 - Swarm or Growl
    |   OOW Unlock
    |   Only 9 Slots - If we are between OOW and TBS we don't have PoiBite yet. Between DoN and TBS we have Swarm or Growl,
    |                  but should be in Slot 8. Slot Misc till we have PoiBite. Before SoF slot 10 unlock this will also
    |                  get used as Misc slot even with having Swarm or Growl in here. "Shouldn't" cause issues.
    |   10+ Slots    - If we are post-SoF we should have PoiBite, Swarm, and Growl.  Try to use Swarm or Growl here.
    /if (${Me.NumGems} == 9) {
        | PoiBite is in Slot 8, try to use Swarm or Growl
        /if (${Spell8.Equal[${PoiBite}]}) {
            /if (${DoSwarmPet[SETTINGVAL]}) {
                /varset Spell9 ${SwarmPet}
            } else {
                /varset Spell9 ${PetGrowl}
            }
        | PoiBite not in Slot 8, Swarm or Growl might be, just set slot to Misc
        } else {
            /varset Spell9 NULL
        }
    } else {
        /if (${DoSwarmPet[SETTINGVAL]}) {
            /varset Spell9 ${SwarmPet}
        } else {
            /varset Spell9 ${PetGrowl}
        }
    }

    | - Gem 10 - FrozenPoi
    |   SoF Unlock at Level 75
    | Will be Misc Slot until FrozenPoi at 84 in Underfoot. At that point we should have
    | slots 11 and 12 available.
    /if (${Me.NumGems} == 10) {
        /varset Spell10 NULL
    } else {
        /varset Spell10 ${FrozenPoi}
    }

    | - Gem 11 - Maelstrom
    |   UF Unlock at Level 80
    | Will be Misc Slot until Maelstrom at 90 in House of Thule.
    /if (${Me.NumGems} == 11) {
        /varset Spell11 NULL
    } else {
        /varset Spell11 ${Maelstrom}
    }

    | - Gem 12 - Colddot
    |   UF Unlock at Level 80
    | Will be Misc Slot until Colddot at 99 in Rain of Fear.
    /if (${Me.NumGems} == 12) {
        /varset Spell12 NULL
    } else {
        /varset Spell12 ${Colddot}
    }

    | - Gem 13 - Always NULL
    |   ROS Unlock
    /varset Spell13 NULL

    |- Rotations
    |- Self Buffs
    /call BST_DefaultSelfBuffRotationConfig BST_Downtime_MODEDPS_Rotation
    |- Pet Buffs
    /call BST_DefaultPetBuffRotationConfig BST_Downtime_MODEDPS_Rotation
    |- Group Buffs
    /call BST_DefaultBuffGroupConfig
    |- Heals
    /call BST_DefaultHealRotationConfig
    | - Debuffs -
    /call BST_DefaultDebuffRotationConfig "BST_Debuff_MODEDPS_Rotation"

|- Burn Routines

| - Burn Series 1
    | Besial Alignment (65+) when HHEFuryDisc (88+) and Ferociousness (105+) not active
    /call AddToRotation BST_Burn_MODEDPS_Rotation "Bestial Alignment"   AA      ${Parse[0,"( !${Me.Song[${HHEFuryDisc}].ID} && !${Me.Song[Bestial Alignment].ID} && !${Me.Buff[Ferociousness].ID} )"]}
    | Vindisc (102+) when HHEFuryDisc (88+) and Ferociousness (105+) not active, but Besial Alignment active
    /call AddToRotation BST_Burn_MODEDPS_Rotation "${Vindisc}"          DISC    ${Parse[0,"( !${Me.Song[${HHEFuryDisc}].ID} && ${Me.Song[Bestial Alignment].ID} && !${Me.Buff[Ferociousness].ID} )"]}
    | Frenzy of Spirit (59+) when HHEFuryDisc (88+) and Ferociousness (105+) not active, but Besial Alignment active
    /call AddToRotation BST_Burn_MODEDPS_Rotation "Frenzy of Spirit"    AA      ${Parse[0,"( !${Me.Song[${HHEFuryDisc}].ID} && ${Me.Song[Bestial Alignment].ID} && !${Me.Buff[Ferociousness].ID} )"]}
    | Bloodlust (95+) when HHEFuryDisc (88+) and Ferociousness (105+) not active, but Besial Alignment active
    /call AddToRotation BST_Burn_MODEDPS_Rotation "Bloodlust"           AA      ${Parse[0,"( !${Me.Song[${HHEFuryDisc}].ID} && ${Me.Song[Bestial Alignment].ID} && !${Me.Buff[Ferociousness].ID} )"]}
    | Frenzied Swipes (100+) when HHEFuryDisc (88+) and Ferociousness (105+) not active, but Besial Alignment active
    /call AddToRotation BST_Burn_MODEDPS_Rotation "Frenzied Swipes"     AA      ${Parse[0,"( !${Me.Song[${HHEFuryDisc}].ID} && ${Me.Song[Bestial Alignment].ID} && !${Me.Buff[Ferociousness].ID} )"]}

|-  Burn Series 2
    | HHEFuryDisc (88+) when Besial Alignment (65+) down and not active, and Ferociousness (105+) not active
    /call AddToRotation BST_Burn_MODEDPS_Rotation "${HHEFuryDisc}"                  DISC    ${Parse[0,"( !${Me.Song[${HHEFuryDisc}].ID} && !${Me.Song[Bestial Alignment].ID} && !${Me.Buff[Ferociousness].ID} && !${PCAAReady[Bestial Alignment]} )"]}
    | Spire of the Savage Lord (85+) when Besial Alignment (65+) and Ferociousness (105+) not active, but HHEFuryDisc active
    /call AddToRotation BST_Burn_MODEDPS_Rotation "Spire of the Savage Lord"        AA      ${Parse[0,"( ${Me.Song[${HHEFuryDisc}].ID} && !${Me.Song[Bestial Alignment].ID} && !${Me.Buff[Ferociousness].ID} )"]}
    | DmgModDisc (60+) when Besial Alignment (65+) and Ferociousness (105+) not active, but HHEFuryDisc active
    /call AddToRotation BST_Burn_MODEDPS_Rotation "${DmgModDisc}"                   Disc    ${Parse[0,"( ${Me.Song[${HHEFuryDisc}].ID} && !${Me.Song[Bestial Alignment].ID} && !${Me.Buff[Ferociousness].ID} )"]}
    | Chest Click when Besial Alignment (65+) and Ferociousness (105+) not active, but HHEFuryDisc active (When we dont have HHEFuryDisc, fire off when available)
    /call AddToRotation BST_Burn_MODEDPS_Rotation "${ChestItemName[SETTINGVAL]}"    Item    ${Parse[1,"( (${Me.Song[${HHEFuryDisc}].ID} || !${Me.CombatAbility[${HHEFuryDisc}]}) && ${Spell[${FindItem[${ChestItemName[SETTINGVAL]}].Spell}].Stacks} && (!${FindItem[${ChestItemName[SETTINGVAL]}].TimerReady}) && ${DoChestClick[SETTINGVAL]} )"]}

| - Burn Series 3
    | Ferociousness (105+) when Besial Alignment (65+) and HHEFuryDisc (88+) down and not active
    /call AddToRotation BST_Burn_MODEDPS_Rotation "Ferociousness"               AA      ${Parse[0,"( !${Me.Song[${HHEFuryDisc}].ID} && !${Me.Song[Bestial Alignment].ID} && !${Me.Buff[Ferociousness].ID} & !${PCAAReady[Bestial Alignment]} && !${PCDiscReady[${HHEFuryDisc}]} )"]}
    | Companion's Fury (86+) when Ferociousness (105+) active and HHEFuryDisc (88+) and Besial Alignment (65+) not active (When we dont have Ferociousness, fire off when other conditions met)
    /call AddToRotation BST_Burn_MODEDPS_Rotation "Companion's Fury"            AA      ${Parse[0,"( !${Me.Song[${HHEFuryDisc}].ID} && !${Me.Song[Bestial Alignment].ID} && (${Me.Buff[Ferociousness].ID} || !${RG_CanUseAA[Ferociousness]}) )"]}
    | Group Bestial Alignment (83+) when Ferociousness (105+) active and HHEFuryDisc (88+) and Besial Alignment (65+) not active (When we dont have Ferociousness, fire off when other conditions met)
    /call AddToRotation BST_Burn_MODEDPS_Rotation "Group Bestial Alignment"     AA      ${Parse[0,"( !${Me.Song[${HHEFuryDisc}].ID} && !${Me.Song[Bestial Alignment].ID} && (${Me.Buff[Ferociousness].ID} || !${RG_CanUseAA[Ferociousness]}) )"]}


    |- Dps Ferocity Check
    /call AddtoRotation BST_DPS_MODEDPS_Rotation "/call VerifyFerocity"     Command     ${Parse[0,"( ${DoCombatFero[SETTINGVAL]} && ${NPCSpellReady[${SingleAtkBuff}]} && ${CfList[SETTINGVAL].NotEqual[NULL]} )"]}
    |- DPS ToT Heal
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${HealSpell}"     Spell   ${Parse[0,"( ${Me.TargetOfTarget.PctHPs} < ${LightHealPoint[SETTINGVAL]} )"]}
    /if (${DoSwarmPet[SETTINGVAL]}) {
        /call AddToRotation BST_DPS_MODEDPS_Rotation "${SwarmPet}"  Spell   ${Parse[0,"( !${Me.Song[${Spell[${Spell[${Spell[${SwarmPet}].Trigger[2].BaseName}].AutoCast}].Name}].ID} )"]}
        | - The Swarm Cast autocasts 2 Which Then Autocasts The PetGrowl onto the tank. I can trace it to The Trigger[2] As shown below And it being the autocast it provides a .id Which i cannot Seem to Check for made Logic leap for myself.
        | - ${Spell[${Spell[${SwarmPet}].Trigger[2].BaseName}].AutoCast}
    } else {
        /call AddToRotation BST_DPS_MODEDPS_Rotation "${PetGrowl}"  Spell   ${Parse[0,"( !${Me.Song[${PetGrowl}].ID} )"]}
    }

| - Bandolier Actions.
    /call AddToRotation BST_DPS_MODEDPS_Rotation   "/bandolier activate 2H"     Command     ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[2H].Active} && ${Bool[${Me.Bandolier[2H].Index}]} && ${Me.Buff[${Vindisc}].ID} )"]} 
    /call AddToRotation BST_DPS_MODEDPS_Rotation   "/bandolier activate DW"     Command     ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[DW].Active} && ${Bool[${Me.Bandolier[DW].Index}]} && !${Me.Buff[${Vindisc}].ID} )"]}

    | Kick / Round Kick
    | Use Round Kick if we have Feral Swipe AA - TODO: When Rank >= 3? Add toggle if user wants to autoskill?
    /if ( ${RG_CanUseAA[Feral Swipe]} ) {
        /call AddToRotation BST_DPS_MODEDPS_Rotation "Round Kick"   Ability  ${Parse[0,"( ${Me.AbilityReady[Round Kick]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]}
    } else {
        /call AddToRotation BST_DPS_MODEDPS_Rotation "Kick"         Ability  ${Parse[0,"( ${Me.AbilityReady[Kick]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]}
    }

    | Dragon Punch / Eagle Strike / Tiger Claw
    | Based off if we have AA and setting? Toggle for autoskill?

    /call AddToRotation BST_DPS_MODEDPS_Rotation "${Blooddot}"          Spell   ${Parse[0,"( ${Me.ActiveDisc[${Vindisc}].ID} )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "Enduring Frenzy"      AA      ${Parse[0,"( ${Target.PctHPs} > 90 )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${EndRegenProcDisc}"  Disc    ${Parse[0,"( ${Me.PctEndurance} < 10 )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "Chameleon Strike"     AA      ${Parse[0,"( TRUE )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${SingleClaws}"       Disc    ${Parse[0,"( !${DoAoe[SETTINGVAL]} )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${AEClaws}"           Disc    ${Parse[0,"( ${DoAoe[SETTINGVAL]} )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${Maul}"              Disc    ${Parse[0,"( TRUE )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${BeastialBuffDisc}"  Disc    ${Parse[0,"( !${Me.Buff[${BeastialBuffDisc}].ID} )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${DichoSpell}"        Spell   ${Parse[0,"( TRUE )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${Maelstrom}"         Spell   ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${PoiBite}"           Spell   ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${FrozenPoi}"         Spell   ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${Icelance1}"         Spell   ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${Icelance2}"         Spell   ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${Colddot}"           Spell   ${Parse[0,"( DOTSPELLCHECK && MANACHECK )"]}
    /call AddToRotation BST_DPS_MODEDPS_Rotation "${Blooddot}"          Spell   ${Parse[0,"( DOTSPELLCHECK && MANACHECK )"]}
/return

Sub BST_ModeConfigMODETLP
/varset IsHealing TRUE

| For TLP we may not yet have Swarm Pet so turn it off
/if (${SwarmPet.Equal[NULL]}) {
    /echo No Usable Swarm Pet Ability. Turning off DoSwarmPet.
    /varset DoSwarmPet[SETTINGVAL] 0
}

| - BarSetup
    | - Gem 1 - Always a heal Spell
    /varset Spell1 ${HealSpell}

    | - Gem 2 - Always a PetHeal
    /varset Spell2 ${PetHealSpell}

    | - Gem 3 & Gem 4 - Always Ice Lance
    /varset Spell3 ${Icelance1}
    /varset Spell4 ${Icelance2}

    | - Gem 5 - Always Blood DOT Spell
    /varset Spell5 ${Blooddot}

    | - Gem 6 - Ferocity
    |           For TLP Mode will never have Group version before we should swap to standard modes.
    |           Use Group if we for some reason have it, otherwise slot in Single.
    /if (${GroupAtkBuff.NotEqual[NULL]}) {
        /varset Spell6 ${GroupAtkBuff}
    } else {
        /varset Spell6 ${SingleAtkBuff}
    }

    | - Gem 7 - Slow
    |           EndemicDot (When DoSlow Disabled and DoDot Enabled)
    |           Misc (When DoSlow Disabled and DoDot Disabled)
    /if ( ${DoSlow[SETTINGVAL]} ) {
        /varset Spell7 ${SlowSpell}
    } else {
        /if ( ${DoDot[SETTINGVAL]} ) {
            /varset Spell7 ${EndemicDot}
        } else {
            /varset Spell7 NULL
        }
    }

    | - Gem 8 - PoitBite
    |           Swarm or Growl
    |   Only 8 Slots - If we only have 8 slots we are probably pre-OOW. No PoiBite, Swarm, or Growl yet.
    |                  Use as Misc Slot. If for some reason it is post-OOW and you have those abilities, buy your spell slot AA!
    |   9+ Slots     - If we are post-OOW try to use PoiBite if we have it (post-TBS). Otherwise fall back to slotting in Swarm (DoDH) or Growl (DoN).
    |                  Between OOW and DoN we don't have anything so will continue to be a misc slot.
    /if (${Me.NumGems} == 8) {
        /varset Spell8 NULL
    } else {
        /if (${PoiBite.NotEqual[NULL]}) {
            /varset Spell8 ${PoiBite}
        } else {
            /if (${DoSwarmPet[SETTINGVAL]}) {
                /varset Spell8 ${SwarmPet}
            } else {
                /varset Spell8 ${PetGrowl}
            }
        }
    }

    | - Gem 9 - Swarm or Growl
    |   OOW Unlock
    |   Only 9 Slots - If we are between OOW and TBS we don't have PoiBite yet. Between DoN and TBS we have Swarm or Growl,
    |                  but should be in Slot 8. Slot Misc till we have PoiBite. Before SoF slot 10 unlock this will also
    |                  get used as Misc slot even with having Swarm or Growl in here. "Shouldn't" cause issues.
    |   10+ Slots    - If we are post-SoF we should have PoiBite, Swarm, and Growl.  Try to use Swarm or Growl here.
    /if (${Me.NumGems} == 9) {
        | PoiBite is in Slot 8, try to use Swarm or Growl
        /if (${Spell8.Equal[${PoiBite}]}) {
            /if (${DoSwarmPet[SETTINGVAL]}) {
                /varset Spell9 ${SwarmPet}
            } else {
                /varset Spell9 ${PetGrowl}
            }
        | PoiBite not in Slot 8, Swarm or Growl might be, just set slot to Misc
        } else {
            /varset Spell9 NULL
        }
    } else {
        /if (${DoSwarmPet[SETTINGVAL]}) {
            /varset Spell9 ${SwarmPet}
        } else {
            /varset Spell9 ${PetGrowl}
        }
    }

    | - Gem 10 - FrozenPoi At Level 84
    |   SoF Unlock at Level 75
    | Will probably be NULL unless you are leveling after UF release and buy this additional
    | spell slot. Even then youll have FrozenPoi for 1 level before you should swap to non TLP mode.
    /if (${Me.NumGems} == 10) {
        /varset Spell10 NULL
    } else {
        /varset Spell10 ${FrozenPoi}
    }

    | - Gem 11 - Maelstrom
    |   UF Unlock at Level 80
    | At this point should not be using TLP mode unless leveling. Only case you will have
    | this gem slot is if UF is unlocked and you bought the AA at level 80.
    | Even then Maelstrom starts at level 90. So slot will most likely be NULL.
    /if (${Me.NumGems} == 11) {
        /varset Spell11 NULL
    } else {
        /varset Spell11 ${Maelstrom}
    }

    | - Gem 12 - Colddot
    |   UF Unlock at Level 80
    | At this point should not be using TLP mode unless leveling. Only case you will have
    | this gem slot is if UF is unlocked and you bought the AA at level 80.
    | Even then Colddot starts at level 99. So slot will most likely be NULL.
    /if (${Me.NumGems} == 12) {
        /varset Spell12 NULL
    } else {
        /varset Spell12 ${Colddot}
    }

    | - Gem 13 - Always NULL
    |   ROS Unlock
    /varset Spell13 NULL



    |- Rotations
    |- Self Buffs
    /call BST_DefaultSelfBuffRotationConfig BST_Downtime_MODETLP_Rotation
    |- Pet Buffs
    /call BST_DefaultPetBuffRotationConfig BST_Downtime_MODETLP_Rotation
    |- Group Buffs
    /call BST_DefaultBuffGroupConfig
    |- Heals
    /call BST_DefaultHealRotationConfig
    | - Debuffs -
    /call BST_DefaultDebuffRotationConfig "BST_Debuff_MODETLP_Rotation"

|- Burn Routines
| - Burn Series 1
    /call AddToRotation BST_Burn_MODETLP_Rotation "Bestial Alignment"   "AA"    ${Parse[0,"( !${Me.Song[Bestial Alignment].ID} )"]}
    | No Vindisc, Starts at Level 102
    /call AddToRotation BST_Burn_MODETLP_Rotation "Frenzy of Spirit"    "AA"    ${Parse[0,"( ${Me.Song[Bestial Alignment].ID} )"]}
    | No Bloodlust, Starts at Level 95
    | No Frenzied Swipes, Starts at Level 100
| -  Burn Series 2
    | No HHEFuryDisc, Starts at Level 88
    | No Spire of the Savage Lord, Starts at Level 85
    /call AddToRotation BST_Burn_MODETLP_Rotation "${DmgModDisc}"                               "Disc"  ${Parse[0,"( !${Me.Song[Bestial Alignment].ID} )"]}
    /call AddToRotation BST_Burn_MODETLP_Rotation "${ChestItemName[SETTINGVAL]}" Item ${Parse[1,"( ${Spell[${FindItem[${ChestItemName[SETTINGVAL]}].Spell}].Stacks} && (!${FindItem[${ChestItemName[SETTINGVAL]}].TimerReady}) && ${DoChestClick[SETTINGVAL]} )"]}
| - Burn Series 3
    | No Ferociousness, Starts at Level 105
    | No Active Companion's Fury AA, Starts at Rank Available at Level 86
    | Group Bestial Alignment Starts at Level 83
    /call AddToRotation BST_Burn_MODETLP_Rotation "Group Bestial Alignment"         "AA"    ${Parse[0,"( !${Me.Song[Bestial Alignment].ID} )"]}

|- DPS Routine
    |- Dps Ferocity Check
    /call AddtoRotation BST_DPS_MODETLP_Rotation "/call VerifyFerocity"  "Command"  ${Parse[0,"( ${DoCombatFero[SETTINGVAL]} && !${FeroCheck} && ${Me.SpellReady[${SingleAtkBuff}]} && ${CfList[SETTINGVAL].NotEqual[NULL]} )"]}
    |- DPS ToT Heal
    /call AddToRotation BST_DPS_MODETLP_Rotation "${HealSpell}"          "Spell"    ${Parse[0,"( ${Me.TargetOfTarget.PctHPs} < ${LightHealPoint[SETTINGVAL]} )"]}
    /if (${DoSwarmPet[SETTINGVAL]}) {
        /call AddToRotation BST_DPS_MODETLP_Rotation "${SwarmPet}"           "Spell"    ${Parse[0,"( !${Me.Song[${Spell[${Spell[${Spell[${SwarmPet}].Trigger[2].BaseName}].AutoCast}].Name}].ID} )"]}
        | - The Swarm Cast autocasts 2 Which Then Autocasts The PetGrowl onto the tank. I can trace it to The Trigger[2] As shown below And it being the autocast it provides a .id Which i cannot Seem to Check for made Logic leap for myself.
        | - ${Spell[${Spell[${SwarmPet}].Trigger[2].BaseName}].AutoCast}
    } else {
        /call AddToRotation BST_DPS_MODETLP_Rotation "${PetGrowl}"       "Spell"    ${Parse[0,"( !${Me.Song[${PetGrowl}].ID} )"]}
    }

    | Kick / Round Kick
    | Use Round Kick if we have Feral Swipe AA - TODO: When Rank >= 3? Add toggle if user wants to autoskill?
    /if ( ${RG_CanUseAA[Feral Swipe]} ) {
        /call AddToRotation BST_DPS_MODETLP_Rotation "Round Kick"   Ability  ${Parse[0,"( ${Me.AbilityReady[Round Kick]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]}
    } else {
        /call AddToRotation BST_DPS_MODETLP_Rotation "Kick"         Ability  ${Parse[0,"( ${Me.AbilityReady[Kick]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]}
    }

    | Dragon Punch / Eagle Strike / Tiger Claw
    | Based off if we have AA and setting? Toggle for autoskill?
    
    | No Blooddot with Vindisc, Vindisc Starts at Level 102
    | No Enduring Frenzy AA, Starts at 85
    | No EndRegenProcDisc, Starts at Level 100
    | No Chameleon Strike, Starts at Level 85
    | No SingleClaws, Starts at Level 98
    | No AEClaws, Starts at Level 87
    /call AddToRotation BST_DPS_MODETLP_Rotation "${Maul}"               "Disc"     ${Parse[0,"( TRUE )"]}
    | No BeastialBuffDisc, Starts at Level 86
    | No Maelstrom, Starts at Level 90
    | PoiBite Starts at Level 73
    /call AddToRotation BST_DPS_MODETLP_Rotation "${PoiBite}"       "Spell"    ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    | FrozenPoi Starts at Level 84
    /call AddToRotation BST_DPS_MODETLP_Rotation "${FrozenPoi}"         "Spell"    ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    /call AddToRotation BST_DPS_MODETLP_Rotation "${Icelance1}"          "Spell"    ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    /call AddToRotation BST_DPS_MODETLP_Rotation "${Icelance2}"          "Spell"    ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    | No Colddot, Starts at Level 99
    /call AddToRotation BST_DPS_MODETLP_Rotation "${Blooddot}"           "Spell"    ${Parse[0,"( DOTSPELLCHECK && MANACHECK )"]}
    /call AddToRotation BST_DPS_MODETLP_Rotation "${EndemicDot}"         "Spell"    ${Parse[0,"( DOTSPELLCHECK && MANACHECK )"]}
    | No Dichotomic Fury, Starts at Level 101
/return

Sub BST_DefaultSelfBuffRotationConfig(string rotation_name)
|- Self Buff Rotation Setup
    /call AddToRotation "${rotation_name}" "${KillShotBuff}"            "Spell" ${Parse[0,"( SELFBUFFCHECK && !${Me.Buff[${KillShotBuff}].ID} )"]}
    /call AddToRotation "${rotation_name}" "Pact of The Wurine"         "AA" ${Parse[0,"( SELFBUFFAACHECK && (${Me.PctEndurance}<21 && ${Me.Endurance}>313))"]}
    /call AddToRotation "${rotation_name}" "Consumption of Spirit"      "AA" ${Parse[0,"( SELFBUFFAACHECK && (${Me.PctHPs}>70 && ${Me.PctMana}<80) )"]}
    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}"   "Item"  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount"                  "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    /call AddToRotation "${rotation_name}" "/dismount"                  "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==1 && ${Me.Mount.ID} && ${DoMelee[SETTINGVAL]} )"]}
    /call AddtoRotation "${rotation_name}" "/call VerifyFerocity"       "Command"   ${Parse[0,"( ${DoCombatFero[SETTINGVAL]} && ${NPCSpellReady[${SingleAtkBuff}]} && ${CfList[SETTINGVAL].NotEqual[NULL]} )"]}
/return

Sub BST_DefaultPetBuffRotationConfig(string rotation_name)
|- Pet Buff Rotation
    /call AddToRotation "${rotation_name}" "${Epic}"            "Item"  ${Parse[0,"( ${DoEpic[SETTINGVAL]} && (!${Me.PetBuff[${EpicBuff1}]} || !${Me.PetBuff[${EpicBuff2}]}) )"]}
    /call AddToRotation "${rotation_name}" "Hobble of Spirits"  "AA"    ${Parse[0,"( ${DoSnare[SETTINGVAL]} && !${Me.PetBuff[${Me.AltAbility[Hobble of Spirits].Spell}]} )"]}
    /call AddToRotation "${rotation_name}" "${AvatarSpell}"     "Spell" ${Parse[0,"( SELFBUFFPETCHECK )"]}
    /call AddToRotation "${rotation_name}" "${RunSpeedBuff}"    "Spell" ${Parse[0,"( ${DoRunSpeed[SETTINGVAL]} && SELFBUFFPETCHECK )"]}
    /call AddToRotation "${rotation_name}" "${PetOffenseBuff}"  "Spell" ${Parse[0,"( !${DoPetTank[SETTINGVAL]} && SELFBUFFPETCHECK )"]}
    /call AddToRotation "${rotation_name}" "${PetDefenseBuff}"  "Spell" ${Parse[0,"( ${DoPetTank[SETTINGVAL]} && SELFBUFFPETCHECK )"]}
    /call AddToRotation "${rotation_name}" "${PetSlowProc}"     "Spell" ${Parse[0,"( ${DoPetSlow[SETTINGVAL]} && SELFBUFFPETCHECK )"]}
    /call AddToRotation "${rotation_name}" "${PetHaste}"        "Spell" ${Parse[0,"(SELFBUFFPETCHECK )"]}
    /call AddToRotation "${rotation_name}" "${PetDamageProc}"   "Spell" ${Parse[0,"( !${DoPetTank[SETTINGVAL]} && SELFBUFFPETCHECK )"]}
    /call AddToRotation "${rotation_name}" "${PetHealProc}"     "Spell" ${Parse[0,"( SELFBUFFPETCHECK )"]}
    /call AddToRotation "${rotation_name}" "${PetSpellGuard}"   "Spell" ${Parse[0,"( SELFBUFFPETCHECK )"]}
    /if (!${DoSwarmPet[SETTINGVAL]}) /call AddToRotation "${rotation_name}" "${PetGrowl}"       "Spell" ${Parse[0,"( !${Me.Song[${PetGrowl}].ID} && ${Me.Pet.ID} )"]}
/return

Sub BST_DefaultHealRotationConfig
|- Setup heals
|    /call Heal_AddHealPoint    ${PetHealpoint[SETTINGVAL]}
    /call Heal_AddHealPoint     ${LightHealPoint[SETTINGVAL]}
    /call Heal_AddSpell         ${LightHealPoint[SETTINGVAL]} "${HealSpell}" ${Parse[0,"( ${Me.Level} < 112  )"]}

/return

Sub BST_DefaultBuffGroupConfig
    | - Setup Buff Group List
    | - if Below level
    /call BuffGroup_Init 6
    /call BuffGroup_Set 1 "${RunSpeedBuff}" "ALL" ${Parse[0,"( ${DoRunSpeed[SETTINGVAL]} )"]}
    /call BuffGroup_Set 2 "${ManaRegenBuff}" "ALL" ${Parse[0,"( TRUE )"]}
    /call BuffGroup_Set 3 "${AvatarSpell}" "RGMELEE" ${Parse[0,"( !${Spell[${GroupFocusSpell}].ID} )"]}
    | - Determines based on if the GroupVariables are Defined and Casts those if so otherwise uses Singles On tanks Only.

    /if ( ${Spell[${GroupAtkBuff}].ID} ) {
        /call BuffGroup_Set 4 "${GroupAtkBuff}" "ALL" ${Parse[0,"( TRUE )"]}
        } else {
        /call BuffGroup_Set 4 "${SingleAtkBuff}" "WAR,PAL,SHD" ${Parse[0,"( !${DoCombatFero[SETTINGVAL]} )"]}
    }

    /if ( ${Spell[${GroupAtkHPBuff}].ID} ) {
        /call BuffGroup_Set 5 "${GroupAtkHPBuff}" "ALL" ${Parse[0,"( TRUE )"]}
    } else {
        /call BuffGroup_Set 5 "${SingleAtkHPBuff}" "WAR,PAL,SHD" ${Parse[0,"( TRUE )"]}
    }

    /if ( ${Spell[${GroupFocusSpell}].ID} ) {
        /call BuffGroup_Set 6 "${GroupFocusSpell}" "ALL"
        } else {
        /call BuffGroup_Set 6 "${SingleFocusSpell}" "WAR,PAL,SHD"
    }



|- Chat Begs
    /call ChatBegList_Add BSTBegs shrinkme AA "Shrink" sender TRUE
    /call ChatBegList_Add BSTBegs shrinkgroup AA "Group Shrink" sender TRUE
/return

Sub BST_DefaultDebuffRotationConfig(string rotation_name)
/call AddToRotation "${rotation_name}" "${SlowSpell}"  Spell ${Parse[0,"( ${DoSlow[SETTINGVAL]} && !${RG_CanUseAA[Sha's Reprisal]} && ${Spell[${SlowSpell}].SlowPct}>${Target.Slowed.SlowPct})"]}
/call AddToRotation "${rotation_name}" "Sha's Reprisal"  AA  ${Parse[0,"( ${DoSlow[SETTINGVAL]}  &&  ${Me.AltAbility[Sha's Reprisal].Spell.SlowPct}>${Target.Slowed.SlowPct} )"]}
/return

Sub BST_Combat_Routine
    /doevents

    /if (DODEBUFF) {
        /call Ordered_Rotation_Follow BST_Debuff_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }
    | For some reason pet is in the DoDPS check... should all pet wielders be the same?
    |- Pet Attack
    /if (DODPS) {
        /call PetAttack
        /if (!${Me.Pet.ID} && ${DoPet[SETTINGVAL]} && ${PCSpellReady[${PetSpell}]}) {
            /call SpellNow "${PetSpell}" ${Me.ID}
        }
        /if ( BURNCHECK ) {
            /call Ordered_Rotation_Follow BST_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        }
        /call Ordered_Rotation_Follow BST_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }
/return FALSE


| ----------------------------------------------------------------------------
| SUB: Verify Ferocity
| ----------------------------------------------------------------------------
Sub VerifyFerocity
    /if  ( ${CfList[SETTINGVAL].NotEqual[NULL]} ) {
        |- Load our | delimited setting entry into a list so we have
        |- quick looping w/o lots of Arg parsing.
        /declare list_ferocombat list local
        /declare tmp_FeroCheck int local
        /invoke ${list_ferocombat.Delimiter[|]}
        /invoke ${list_ferocombat.Append[${CfList[SETTINGVAL]}]}
        /declare li_ferocombat listiterator local
        /vardata li_ferocombat list_ferocombat.First.Clone

        /declare spawn_tmp spawn local
        /if (${list_ferocombat.Count}) {
            /while (!${li_ferocombat.IsEnd}) {
                /if ( ${SpawnCount[pc ${li_ferocombat.Value}]}) {
                    /squelch /vardata spawn_tmp Spawn[PC ${li_ferocombat.Value}]

                    /if ( !${spawn_tmp.CachedBuff[${SingleAtkBuff}].Duration}  ) {
                        /call SpellNow "${SingleAtkBuff}" ${spawn_tmp.ID}
                        /varset FeroCheck 0
                        /return TRUE
                    } else {
                        /if ( ${tmp_FeroCheck} < ${spawn_tmp.CachedBuff[${SingleAtkBuff}].Duration} ) {
                            /varset tmp_FeroCheck ${spawn_tmp.CachedBuff[${SingleAtkBuff}].Duration}
                        }
                    }
                }
                /invoke ${li_ferocombat.Advance}
            }
            /varset FeroCheck ${tmp_FeroCheck}
        }
    }
/return

Sub BST_Downtime_Routine
 |- First, do a pet check. If we don't have a pet, make sure we have a pet. If we don't have the items to cast a pet
    |- scream bloody murder.
    /if (!${Me.Pet.ID} && ${DoPet[SETTINGVAL]} && ${PCSpellReady[${PetSpell}]}) {
        /call SpellNow "${PetSpell}" ${Me.ID}
    }

    /call FollowRotation  BST_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}

    /if (${Me.Pet.ID}) {
        /call FollowRotation  BST_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.Pet.ID}
    }
/return FALSE

Sub BST_Heal_Routine
    |- If we're a member of a group, heal our group first.
    /call HealNow ${WorstHurtGroup[${HealPoint_MaxPoint}]}
    /if (${Me.Pet.ID}) {
        |- Petheals Combined Into Do heals. since beastlord has not got a ton of heals anyways
        /if (${PCSpellReady[${PetHealSpell}]} && (${Me.Pet.PctHPs} <= ${PetHealPoint[SETTINGVAL]}) ) {
            /call SpellNow "${PetHealSpell}" ${Me.Pet.ID}
        }
    }

    | - Paragon Mana Check
    /if (!${DoPara[SETTINGVAL]}) /return
    /declare paratarget int local ${WorstHurtMana[${ParagonManaPct[SETTINGVAL]}]}
    /if (${RG_AAReady[Paragon of Spirit]} && !${Me.Song[${Me.AltAbility[Paragon of Spirit].Spell}].ID} && ${paratarget}) /call AANow ${AltAbility[Paragon of Spirit].ID} ${paratarget}
    /if (!${RG_AAReady[Paragon of Spirit]} && ${RG_AAReady[Focused Paragon of Spirits]} && ${paratarget} && !${Me.Song[${Me.AltAbility[Paragon of Spirit].Spell}].ID} ) /call AANow ${AltAbility[Focused Paragon of Spirits].ID} ${paratarget}

    |- Now check xtargets.
    /if (${AssistOutside[SETTINGVAL]}) {
        /call HealNow ${WorstHurtXT[${HealPoint_MaxPoint}]}
        |- In case we pissed someone off
        /if (${Me.PctHPs} <= ${HealPoint_MaxPoint} ) {
            /call HealNow ${Me.ID}
        }
    }
/return ${Macro.Return}

Sub BST_PullSetup
    /if (${Me.Pet.ID} && ${DoPetPull[SETTINGVAL]}) {
        /call Pull_SetAbility "pullpet" "Special"
    } else /if (${RG_CanUseAA[Sha's Reprisal]}) {
        /call Pull_SetAbility "Sha's Reprisal" "AA"
    } else /if (${SlowSpell.NotEqual[NULL]} && ${Me.Gem[${SlowSpell}]}) {
        /call Pull_SetAbility "${SlowSpell}" Spell
    } else {
        /call Pull_SetAbility "Kick" "Ability"
    }
/return