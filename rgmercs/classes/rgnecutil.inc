|- necroutil.inc
|- Version 1.0
|- Updated: 2/7/2020
|-----------------------------------------------------------------------------------
|-Setup Variable Enviroment
|-----------------------------------------------------------------------------------
#define MODEDPS 0
#define MODETLP 2
Sub NEC_Setup
|-Create Setting List
    /declare RGList_NEC list outer

|- Live Rotations
	/call Ordered_Rotation_New NEC_Debuff_MODEDPS_Rotation
	/call Ordered_Rotation_New NEC_Heal_MODEDPS_Rotation
	/call Ordered_Rotation_New NEC_DPS_MODEDPS_Rotation
	/call Ordered_Rotation_New NEC_Downtime_MODEDPS_Rotation
    /call Ordered_Rotation_New NEC_Burn_MODEDPS_Rotation

|- Live Rotations
	/call Ordered_Rotation_New NEC_Debuff_MODETLP_Rotation
	/call Ordered_Rotation_New NEC_Heal_MODETLP_Rotation
	/call Ordered_Rotation_New NEC_DPS_MODETLP_Rotation
	/call Ordered_Rotation_New NEC_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New NEC_Burn_MODETLP_Rotation

|-Declare AA and SpellVariables
 |-Buffs
    /call AbilitySet_New SelfHPBuff
    /call AbilitySet_New SelfRune1
    /call AbilitySet_New SelfSpellShield1
    /call AbilitySet_New NecSpellSet

 |-Debuff
    /call AbilitySet_New StripBuffSpell
 |- Items
    /call ItemSet_New Epic  
    /call AbilitySet_New FDSpell
 
 |-DPS
    /call AbilitySet_New AllianceSpell
    /call AbilitySet_New DichoSpell
    /call AbilitySet_New SwarmPet
    /call AbilitySet_New HealthTaps
    /call AbilitySet_New DurationTap
    /call AbilitySet_New GroupLeech
    /call AbilitySet_New PoisonNuke
    /call AbilitySet_New PoisonNuke2
    /call AbilitySet_New FireDot1
    /call AbilitySet_New FireDot1_2
    /call AbilitySet_New FireDot2
    /call AbilitySet_New FireDot2_2
    /call AbilitySet_New FireDot3
    /call AbilitySet_New FireDot4
    /call AbilitySet_New Magic1
    /call AbilitySet_New Magic2
    /call AbilitySet_New Magic2_2
    /call AbilitySet_New Magic3
    /call AbilitySet_New Magic4
    /call AbilitySet_New Disease1
    /call AbilitySet_New Disease1_2
    /call AbilitySet_New Disease2
    /call AbilitySet_New Disease3
    /call AbilitySet_New Poison1
    /call AbilitySet_New Poison2
    /call AbilitySet_New Poison2_2
    /call AbilitySet_New Poison3
    /call AbilitySet_New Corruption1
    /call AbilitySet_New Corruption2
    /call AbilitySet_New Combination1
    /call AbilitySet_New ManaDrain1
    /call AbilitySet_New CripplingTap
    /call AbilitySet_New ChaoticDebuff
    /call AbilitySet_New SnareDOT
    /call AbilitySet_New ScentDebuff
    /call AbilitySet_New LichSpell
    /call AbilitySet_New BestowBuff

 |-Pet
    /call AbilitySet_New PetSpellRog
    /call AbilitySet_New PetSpellWar
    /call AbilitySet_New PetBuff 
    /call AbilitySet_New PetHaste

 |-Config Options
    /call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = DPS Set 2 = TLP
    /call RGLoadSetting NEC DoPet 1 Pet "Set 0/1 to use a pet."
    /call RGLoadSetting NEC PetType "rog" Pet "Set war,rog to use the warrior or rogue type Necro pet. Default: war."
    /call RGLoadSetting NEC DoPetTank 0 Pet "Set 0/1 to enable pet tanking. [UNIMPLEMENTED]"
    /call RGLoadSetting NEC DoPetDrain 0 Pet "Set 0/1 to use the pet buff for health drains. Will perform an AOE disrupting mez so defaults to disabled."
    /call RGLoadSetting NEC DoLich 1 Options "Set 0/1 to turn yourself into a lich (aka manaregen illusion line)."
    /call RGLoadSetting NEC DeathBloomPercent 40 Options "Set %Mana to use the DeathBloom line of spells."
    /call RGLoadSetting NEC DeadMansFloating 1 Options "Set 0/1 to use Dead Man's Floating AA. [UNIMPLEMENTED]"
    /call RGLoadSetting NEC DoSnare 0 Options "Set 0/1 to use Snare. Default: 0 [ONLY affects pulling -- requires macro restart.]"
    /call RGLoadSetting NEC HPStopDOT 30 Combat "%HP to cut off to stop casting dots."
    /call RGLoadSetting NEC Manatonuke 40 Combat "% Mana to stop nuking at."


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
 
    /declare SpellSet                   string outer auto
    /declare spellmisc                  int outer ${Me.NumGems}
    /declare spellgem                   int outer 1
    /declare miscspellremem             string outer NULL
    /declare spellrememtimer            timer outer 0
    /declare groupbufftimer		timer outer 0
    /if (${Me.AltAbility[25].Name.Find[disabled]} && ${RG_AAReady[25]}) {
		/alt act 25
		/delay 5
	}
/return

|--------------------------------------------------------------------------
|- SUB: CheckOptions- Used to sort conflicting options at startup and set basic values if needed
|--------------------------------------------------------------------------
Sub CheckOptions

/return

|* -------------------------------------------------------------------------------------------------------
| SUB: SetNecroSpells
|-------------------------------------------------------------------------------------------------------- *|
Sub NEC_SetupSkills
    /echo Choosing All Necro Spells - this may take a moment

|- Items
|- Epic
    /call ItemSet_Add "Deathwhisper" Epic
    /call ItemSet_Add "Soulwhisper" Epic
    /call ItemSet_ChooseOuter Epic Epic


|- Alliance Spells
    /call AbilitySet_Add "Malevolent Alliance" AllianceSpell
    /call AbilitySet_Add "Malevolent Covenant" AllianceSpell
    /call AbilitySet_Add "Malevolent Coalition" AllianceSpell
    /call AbilitySet_Add "Malevolent Conjunction" AllianceSpell
    /call AbilitySet_ChooseOuter AllianceSpell AllianceSpell

|-Pet Spells Rogue * Var Name: PetSpellRog string outer
    /call AbilitySet_Add "Unrelenting Assassin" PetSpellRog
    /call AbilitySet_Add "Restless Assassin" PetSpellRog
    /call AbilitySet_Add "Reliving Assassin" PetSpellRog
    /call AbilitySet_Add "Restless Assassin" PetSpellRog
    /call AbilitySet_Add "Unearthed Assassin" PetSpellRog
    /call AbilitySet_Add "Reborn Assassin" PetSpellRog
    /call AbilitySet_Add "Raised Assassin" PetSpellRog
    /call AbilitySet_Add "Unliving Murderer" PetSpellRog
    /call AbilitySet_Add "Noxious Servant" PetSpellRog
    /call AbilitySet_Add "Putrescent Servant" PetSpellRog
    /call AbilitySet_Add "Dark Assassin" PetSpellRog
    /call AbilitySet_Add "Child of Bertoxxulous" PetSpellRog
    /call AbilitySet_Add "Saryrn's Companion" PetSpellRog
    /call AbilitySet_Add "Minion of Shadows" PetSpellRog
    /call AbilitySet_ChooseOuter PetSpellRog PetSpellRog

|-Pet Spells Warrior * Var Name: PetSpellWar string outer
    /call AbilitySet_Add "Luclin's Conqueror" PetSpellWar
    /call AbilitySet_Add "Tserrina's Shade" PetSpellWar
    /call AbilitySet_Add "Adalora's Shade" PetSpellWar
    /call AbilitySet_Add "Miktokla's Shade" PetSpellWar
    /call AbilitySet_Add "Zalifur's Shade" PetSpellWar
    /call AbilitySet_Add "Vak`Ridel's Shade" PetSpellWar
    /call AbilitySet_Add "Aziad's Shade" PetSpellWar
    /call AbilitySet_Add "Bloodreaper's Shade" PetSpellWar
    /call AbilitySet_Add "Relamar's Shade" PetSpellWar
    /call AbilitySet_Add "Riza`farr's Shadow" PetSpellWar
    /call AbilitySet_Add "Lost Soul" PetSpellWar
    /call AbilitySet_Add "Emissary of Thule" PetSpellWar
    /call AbilitySet_Add "Servant of Bones" PetSpellWar
    /call AbilitySet_Add "Invoke Death" PetSpellWar
    /call AbilitySet_Add "Cackling Bones" PetSpellWar
    /call AbilitySet_Add "Malignant Dead" PetSpellWar
    /call AbilitySet_Add "Invoke Shadow" PetSpellWar
    /call AbilitySet_Add "Summon Dead" PetSpellWar
    /call AbilitySet_Add "Haunting Corpse" PetSpellWar
    /call AbilitySet_Add "Animate Dead" PetSpellWar
    /call AbilitySet_Add "Restless Bones" PetSpellWar
    /call AbilitySet_Add "Convoke Shadow" PetSpellWar
    /call AbilitySet_Add "Bone Walk" PetSpellWar
    /call AbilitySet_Add "Leering Corpse" PetSpellWar
    /call AbilitySet_Add "Cavorting Bones" PetSpellWar
    /call AbilitySet_ChooseOuter PetSpellWar PetSpellWar

|-Pet Haste Spell * Var Name: PetHaste string outer
    /call AbilitySet_Add "Sigil of Undeath" PetHaste
    /call AbilitySet_Add "Sigil of Decay" PetHaste
    /call AbilitySet_Add "Sigil of the Arcron" PetHaste
    /call AbilitySet_Add "Sigil of the Doomscale" PetHaste
    /call AbilitySet_Add "Sigil of the Sundered" PetHaste
    /call AbilitySet_Add "Sigil of the Preternatural" PetHaste
    /call AbilitySet_Add "Sigil of the Moribund" PetHaste
    /call AbilitySet_Add "Sigil of the Aberrant" PetHaste
    /call AbilitySet_Add "Sigil of the Unnatural" PetHaste
    /call AbilitySet_Add "Glyph of Darkness" PetHaste
    /call AbilitySet_Add "Rune of Death" PetHaste
    /call AbilitySet_Add "Augmentation of Death" PetHaste
    /call AbilitySet_Add "Augment Death" PetHaste
    /call AbilitySet_Add "Intensify Death" PetHaste
    /call AbilitySet_Add "Focus Death" PetHaste
    /call AbilitySet_ChooseOuter PetHaste PetHaste

|-Pet Buff Spell * Var Name: PetBuff string outer
    /call AbilitySet_Add "Inspire Ally" PetBuff
    /call AbilitySet_Add "Incite Ally" PetBuff
    /call AbilitySet_Add "Infuse Ally" PetBuff
    /call AbilitySet_Add "Imbue Ally" PetBuff
    /call AbilitySet_Add "Sanction Ally" PetBuff
    /call AbilitySet_Add "Empower Ally" PetBuff
    /call AbilitySet_Add "Energize Ally" PetBuff
    /call AbilitySet_Add "Necrotize Ally" PetBuff
    /call AbilitySet_ChooseOuter PetBuff PetBuff

|-Self HP Buff * Var name: SelfHPBuff string outer
    /call AbilitySet_Add "Shield of Shadow" SelfHPBuff
    /call AbilitySet_Add "Shield of Restless Ice" SelfHPBuff
    /call AbilitySet_Add "Shield of Scales" SelfHPBuff
    /call AbilitySet_Add "Shield of the Pellarus" SelfHPBuff
    /call AbilitySet_Add "Shield of the Dauntless" SelfHPBuff
    /call AbilitySet_Add "Shield of Bronze" SelfHPBuff
    /call AbilitySet_Add "Shield of Dreams" SelfHPBuff
    /call AbilitySet_Add "Shield of the Void" SelfHPBuff
    /call AbilitySet_Add "Bulwark of the Crystalwing" SelfHPBuff
    /call AbilitySet_Add "Shield of the Crystalwing" SelfHPBuff
    /call AbilitySet_Add "Ether Shield" SelfHPBuff
    /call AbilitySet_Add "Shield of Maelin" SelfHPBuff
    /call AbilitySet_Add "Shield of the Arcane" SelfHPBuff
    /call AbilitySet_Add "Shield of the Magi" SelfHPBuff
    /call AbilitySet_Add "Arch Shielding" SelfHPBuff
    /call AbilitySet_Add "Greater Shielding" SelfHPBuff
    /call AbilitySet_Add "Major Shielding" SelfHPBuff
    /call AbilitySet_Add "Shielding" SelfHPBuff
    /call AbilitySet_Add "Lesser Shielding" SelfHPBuff
    /call AbilitySet_ChooseOuter SelfHPBuff SelfHPBuff

|-Self Rune Buff * Var name: SelfRune1 string outer
    /call AbilitySet_Add "Carrion Skin" SelfRune1
    /call AbilitySet_Add "Frozen Skin" SelfRune1
    /call AbilitySet_Add "Ashen Skin" SelfRune1
    /call AbilitySet_Add "Deadskin" SelfRune1
    /call AbilitySet_Add "Zombieskin" SelfRune1
    /call AbilitySet_Add "Ghoulskin" SelfRune1
    /call AbilitySet_Add "Grimskin" SelfRune1
    /call AbilitySet_Add "Corpseskin" SelfRune1
    /call AbilitySet_Add "Shadowskin" SelfRune1
    /call AbilitySet_Add "Wraithskin" SelfRune1
    /call AbilitySet_ChooseOuter SelfRune1 SelfRune1

|-Self Spell Shield Buff * Var name: SelfSpellShield1
    /call AbilitySet_Add "Shield of Inevitability" SelfSpellShield1
    /call AbilitySet_Add "Shield of Destiny" SelfSpellShield1
    /call AbilitySet_Add "Shield of Order" SelfSpellShield1
    /call AbilitySet_Add "Shield of Consequence" SelfSpellShield1
    /call AbilitySet_Add "Shield of Fate" SelfSpellShield1
    /call AbilitySet_ChooseOuter SelfSpellShield1 SelfSpellShield1
  
|-DichoSpell >= LVL101
    /call AbilitySet_Add "Ecliptic Paroxysm" DichoSpell
    /call AbilitySet_Add "Composite Paroxysm" DichoSpell
    /call AbilitySet_Add "Dissident Paroxysm" DichoSpell
    /call AbilitySet_Add "Dichotomic Paroxysm" DichoSpell
    /call AbilitySet_ChooseOuter DichoSpell DichoSpell

|-SwarmPet >= LVL85
    /call AbilitySet_Add "Call Skeleton Mass" SwarmPet
    /call AbilitySet_Add "Call Skeleton Horde" SwarmPet
    /call AbilitySet_Add "Call Skeleton Army" SwarmPet
    /call AbilitySet_Add "Call Skeleton Mob" SwarmPet
    /call AbilitySet_Add "Call Skeleton Throng" SwarmPet
    /call AbilitySet_Add "Call Skeleton Host" SwarmPet
    /call AbilitySet_Add "Call Skeleton Crush" SwarmPet
    /call AbilitySet_Add "Call Skeleton Swarm" SwarmPet
    /call AbilitySet_ChooseOuter SwarmPet SwarmPet

|-HealthTaps >= LVL1
    /call AbilitySet_Add "Soulflay" HealthTaps
    /call AbilitySet_Add "Soulgouge" HealthTaps
    /call AbilitySet_Add "Draw Essence" HealthTaps
    /call AbilitySet_Add "Soulsiphon" HealthTaps
    /call AbilitySet_Add "Consume Essence" HealthTaps
    /call AbilitySet_Add "Soulrend" HealthTaps
    /call AbilitySet_Add "Hemorrhage Essence" HealthTaps
    /call AbilitySet_Add "Plunder Essence" HealthTaps
    /call AbilitySet_Add "Bleed Essence" HealthTaps
    /call AbilitySet_Add "Divert Essence" HealthTaps
    /call AbilitySet_Add "Drain Essence" HealthTaps
    /call AbilitySet_Add "Siphon Essence" HealthTaps
    /call AbilitySet_Add "Drain Life" HealthTaps
    |- /call AbilitySet_Add "Ancient: Touch of Orshilak" HealthTaps
    /call AbilitySet_Add "Soulspike" HealthTaps
    /call AbilitySet_Add "Touch of Mujaki" HealthTaps
    /call AbilitySet_Add "Touch of Night" HealthTaps
    /call AbilitySet_Add "Deflux" HealthTaps
    /call AbilitySet_Add "Drain Soul" HealthTaps
    /call AbilitySet_Add "Drain Spirit" HealthTaps
    /call AbilitySet_Add "Spirit Tap" HealthTaps
    /call AbilitySet_Add "Siphon Life" HealthTaps
    /call AbilitySet_Add "Lifedraw" HealthTaps
    /call AbilitySet_Add "Lifespike" HealthTaps
    /call AbilitySet_Add "Lifetap" HealthTaps
    /call AbilitySet_ChooseOuter HealthTaps HealthTaps

|-GroupLeech >= LVL9
    /call AbilitySet_Add "Twilight Leech" GroupLeech
    /call AbilitySet_Add "Frozen Leech" GroupLeech
    /call AbilitySet_Add "Ashen Leech" GroupLeech
    /call AbilitySet_Add "Dark Leech" GroupLeech
    /call AbilitySet_Add "Leech" GroupLeech
    /call AbilitySet_ChooseOuter GroupLeech GroupLeech

|-DurationTap >= LVL29
    /call AbilitySet_Add "The Protector's Grasp" DurationTap
    /call AbilitySet_Add "Tserrina's Grasp" DurationTap
    /call AbilitySet_Add "Bomoda's Grasp" DurationTap
    /call AbilitySet_Add "Plexipharia's Grasp" DurationTap
    /call AbilitySet_Add "Halstor's Grasp" DurationTap
    /call AbilitySet_Add "Ivrikdal's Grasp" DurationTap
    /call AbilitySet_Add "Arachne's Grasp" DurationTap
    /call AbilitySet_Add "Fellid's Grasp" DurationTap
    /call AbilitySet_Add "Visziaj's Grasp" DurationTap
    /call AbilitySet_Add "Dyn`leth's Grasp" DurationTap
    /call AbilitySet_Add "Fang of Death" DurationTap
    /call AbilitySet_Add "Night's Beckon" DurationTap
    /call AbilitySet_Add "Saryrn's Kiss" DurationTap
    /call AbilitySet_Add "Vexing Mordinia" DurationTap
    /call AbilitySet_Add "Bond of Death" DurationTap
    /call AbilitySet_Add "Vampiric Curse" DurationTap
    /call AbilitySet_ChooseOuter DurationTap DurationTap

|-PoisonNuke >=LVL21
    /call AbilitySet_Add "Embalming Venin" PoisonNuke
    /call AbilitySet_Add "Searing Venin" PoisonNuke
    /call AbilitySet_Add "Effluvial Venin" PoisonNuke
    /call AbilitySet_Add "Liquefying Venin" PoisonNuke
    /call AbilitySet_Add "Dissolving Venin" PoisonNuke
    /call AbilitySet_Add "Blighted Venin" PoisonNuke
    /call AbilitySet_Add "Withering Venin" PoisonNuke
    /call AbilitySet_Add "Ruinous Venin" PoisonNuke
    /call AbilitySet_Add "Venin" PoisonNuke
    /call AbilitySet_Add "Acikin" PoisonNuke
    /call AbilitySet_Add "Neurotoxin" PoisonNuke
    /call AbilitySet_Add "Torbas' Venom Blast" PoisonNuke
    /call AbilitySet_Add "Torbas' Poison Blast" PoisonNuke
    /call AbilitySet_Add "Torbas' Acid Blast" PoisonNuke
    /call AbilitySet_Add "Shock of Poison" PoisonNuke
    /call AbilitySet_ChooseOuter PoisonNuke PoisonNuke

|-PoisonNuke2  >=LVL 75 (DD Increase chance)
    /call AbilitySet_Add "Proclamation for Blood" PoisonNuke2
    /call AbilitySet_Add "Assert for Blood" PoisonNuke2
    /call AbilitySet_Add "Refute for Blood" PoisonNuke2
    /call AbilitySet_Add "Impose for Blood" PoisonNuke2
    /call AbilitySet_Add "Impel for Blood" PoisonNuke2
    /call AbilitySet_Add "Provocation for Blood" PoisonNuke2
    /call AbilitySet_Add "Compel for Blood" PoisonNuke2
    /call AbilitySet_Add "Exigency for Blood" PoisonNuke2
    /call AbilitySet_Add "Supplication of Blood" PoisonNuke2
    /call AbilitySet_Add "Demand for Blood" PoisonNuke2
    /call AbilitySet_ChooseOuter PoisonNuke2 PoisonNuke2

|-Corruption1 >= LVL77
    /call AbilitySet_Add "Decomposition" Corruption1
    /call AbilitySet_Add "Miasma" Corruption1
    /call AbilitySet_Add "Effluvium" Corruption1
    /call AbilitySet_Add "Liquefaction" Corruption1
    /call AbilitySet_Add "Dissolution" Corruption1
    /call AbilitySet_Add "Mortification" Corruption1
    /call AbilitySet_Add "Fetidity" Corruption1
    /call AbilitySet_Add "Putrescence" Corruption1
    /call AbilitySet_Add "Putrefaction" Corruption1
    /call AbilitySet_ChooseOuter Corruption1 Corruption1

|-FireDot1 >= LVL80
    /call AbilitySet_Add "Scalding Shadow" FireDot1
    /call AbilitySet_Add "Broiling Shadow" FireDot1
    /call AbilitySet_Add "Burning Shadow" FireDot1
    /call AbilitySet_Add "Smouldering Shadow" FireDot1
    /call AbilitySet_Add "Coruscating Shadow" FireDot1
    /call AbilitySet_Add "Blazing Shadow" FireDot1
    /call AbilitySet_Add "Blistering Shadow" FireDot1
    /call AbilitySet_Add "Scorching Shadow" FireDot1
    /call AbilitySet_Add "Searing Shadow" FireDot1
    /call AbilitySet_ChooseOuter FireDot1 FireDot1
    /call AbilitySet_ChooseOuter FireDot1_2 FireDot1 "${FireDot1}"


|-FireDot2 >= LVL10
    /call AbilitySet_Add "Pyre of Va Xakra" FireDot2
    /call AbilitySet_Add "Pyre of Klraggek" FireDot2
    /call AbilitySet_Add "Pyre of the Shadewarden" FireDot2
    /call AbilitySet_Add "Pyre of Jorobb" FireDot2
    /call AbilitySet_Add "Pyre of Marnek" FireDot2
    /call AbilitySet_Add "Pyre of Hazarak" FireDot2
    /call AbilitySet_Add "Pyre of Nos" FireDot2
    /call AbilitySet_Add "Soul Reaper's Pyre" FireDot2
    /call AbilitySet_Add "Reaver's Pyre" FireDot2
    /call AbilitySet_Add "Ashengate Pyre" FireDot2
    /call AbilitySet_Add "Dread Pyre" FireDot2
    /call AbilitySet_Add "Night Fire" FireDot2
    /call AbilitySet_Add "Funeral Pyre of Kelador" FireDot2
    /call AbilitySet_Add "Pyrocruor" FireDot2
    /call AbilitySet_Add "Ignite Blood" FireDot2
    /call AbilitySet_Add "Boil Blood" FireDot2
    /call AbilitySet_Add "Heat Blood" FireDot2
    /call AbilitySet_ChooseOuter FireDot2 FireDot2
    /call AbilitySet_ChooseOuter FireDot2_2 FireDot2 "${FireDot2}"

|-FireDot3 >= LVL88 (QuickDOT)
    /call AbilitySet_Add "Thall Va Kelun's Flashblaze" FireDot3
    /call AbilitySet_Add "Otatomik's Flashblaze" FireDot3
    /call AbilitySet_Add "Azeron's Flashblaze" FireDot3
    /call AbilitySet_Add "Mazub's Flashblaze" FireDot3
    /call AbilitySet_Add "Osalur's Flashblaze" FireDot3
    /call AbilitySet_Add "Brimtav's Flashblaze" FireDot3
    /call AbilitySet_Add "Tenak's Flashblaze" FireDot3
    /call AbilitySet_ChooseOuter FireDot3 FireDot3

|-FireDot4 >= LVL73 DOT
    /call AbilitySet_Add "Pyre of the Neglected" FireDot4
    /call AbilitySet_Add "Pyre of the Wretched" FireDot4
    /call AbilitySet_Add "Pyre of the Fereth" FireDot4
    /call AbilitySet_Add "Pyre of the Lost" FireDot4
    /call AbilitySet_Add "Pyre of the Forsaken" FireDot4
    /call AbilitySet_Add "Pyre of the Piq'a" FireDot4
    /call AbilitySet_Add "Pyre of the Bereft" FireDot4
    /call AbilitySet_Add "Pyre of the Forgotten" FireDot4
    /call AbilitySet_Add "Pyre of the Lifeless" FireDot4
    /call AbilitySet_Add "Pyre of the Fallen" FireDot4
    /call AbilitySet_ChooseOuter FireDot4 FireDot4

|-Poison1 >= LVL86 (QuickDOT)
    /call AbilitySet_Add "Xenacious' Swift Venom" Poison1
    /call AbilitySet_Add "Vilefang's Swift Venom" Poison1
    /call AbilitySet_Add "Nexona's Swift Venom" Poison1
    /call AbilitySet_Add "Serisaria's Swift Venom" Poison1
    /call AbilitySet_Add "Slaunk's Swift Venom" Poison1
    /call AbilitySet_Add "Hyboram's Swift Venom" Poison1
    /call AbilitySet_Add "Burlabis' Swift Venom" Poison1
    /call AbilitySet_ChooseOuter Poison1 Poison1

|-Poison2 >=LVL1 (DOT)
    /call AbilitySet_Add "Hemorrhagic Venom" Poison2
    /call AbilitySet_Add "Crystal Crawler Venom" Poison2
    /call AbilitySet_Add "Polybiad Venom" Poison2
    /call AbilitySet_Add "Glistenwing Venom" Poison2
    /call AbilitySet_Add "Binaesa Venom" Poison2
    /call AbilitySet_Add "Naeya Venom" Poison2
    /call AbilitySet_Add "Argendev's Venom" Poison2
    /call AbilitySet_Add "Slitheren Venom" Poison2
    /call AbilitySet_Add "Venonscale Venom" Poison2
    /call AbilitySet_Add "Vakk`dra's Sickly Mists" Poison2
    /call AbilitySet_Add "Blood of Thule" Poison2
    /call AbilitySet_Add "Envenomed Bolt" Poison2
    /call AbilitySet_Add "Chilling Embrace" Poison2
    /call AbilitySet_Add "Venom of the Snake" Poison2
    /call AbilitySet_Add "Poison Bolt" Poison2
    /call AbilitySet_ChooseOuter Poison2 Poison2
     /call AbilitySet_ChooseOuter Poison2_2 Poison2 "${Poison2}"

|-Poison3 >= LVL79 DOT
    /call AbilitySet_Add "Zelnithak's Pallid Haze" Poison3
    /call AbilitySet_Add "Dracnia's Pallid Haze" Poison3
    /call AbilitySet_Add "Bomoda's Pallid Haze" Poison3
    /call AbilitySet_Add "Plexipharia's Pallid Haze" Poison3
    /call AbilitySet_Add "Halstor's Pallid Haze" Poison3
    /call AbilitySet_Add "Ivrikdal's Pallid Haze" Poison3
    /call AbilitySet_Add "Arachne's Pallid Haze" Poison3
    /call AbilitySet_Add "Fellid's Pallid Haze" Poison3
    /call AbilitySet_Add "Visziaj's Pallid Haze" Poison3
    /call AbilitySet_Add "Chaos Venom" Poison3
    /call AbilitySet_ChooseOuter Poison3 Poison3

|-Magic1 >= LVL51 SlowDot
    /call AbilitySet_Add "Infected Wounds" Magic1
    /call AbilitySet_Add "Septic Wounds" Magic1
    /call AbilitySet_Add "Cytotoxic Wounds" Magic1
    /call AbilitySet_Add "Mortiferous Wounds" Magic1
    /call AbilitySet_Add "Pernicious Wounds" Magic1
    /call AbilitySet_Add "Necrotizing Wounds" Magic1
    /call AbilitySet_Add "Splirt" Magic1
    /call AbilitySet_Add "Splart" Magic1
    /call AbilitySet_Add "Splort" Magic1
    /call AbilitySet_Add "Splurt" Magic1
    /call AbilitySet_ChooseOuter Magic1 Magic1

|-Magic2 >=LVL67 DOT
    /call AbilitySet_Add "Extinction" Magic2
    /call AbilitySet_Add "Oblivion" Magic2
    /call AbilitySet_Add "Inevitable End" Magic2
    /call AbilitySet_Add "Annihilation" Magic2
    /call AbilitySet_Add "Termination" Magic2
    /call AbilitySet_Add "Doom" Magic2
    /call AbilitySet_Add "Demise" Magic2
    /call AbilitySet_Add "Mortal Coil" Magic2
    /call AbilitySet_Add "Anathema of Life" Magic2
    /call AbilitySet_Add "Curse of Mortality" Magic2
    /call AbilitySet_Add "Ancient: Curse of Mori" Magic2
    /call AbilitySet_Add "Dark Nightmare" Magic2
    /call AbilitySet_Add "Horror" Magic2
    /call AbilitySet_ChooseOuter Magic2 Magic2
    /call AbilitySet_ChooseOuter Magic2_2 Magic2 "Magic2"

|-Magic3 >=LVL87 QuickDot
    /call AbilitySet_Add "Xetheg's Swift Deconstruction" Magic3
    /call AbilitySet_Add "Lexelan's Swift Deconstruction" Magic3
    /call AbilitySet_Add "Adalora's Swift Deconstruction" Magic3
    /call AbilitySet_Add "Marmat's Swift Deconstruction" Magic3
    /call AbilitySet_Add "Itkari's Swift Deconstruction" Magic3
    /call AbilitySet_Add "Hral's Swift Deconstruction" Magic3
    /call AbilitySet_Add "Ninavero's Swift Deconstruction" Magic3
    /call AbilitySet_ChooseOuter Magic3 Magic3

|-Magic4 >=LVL 97 DOT
    /call AbilitySet_Add "Scourge of Destiny" Magic4
    /call AbilitySet_Add "Scourge of Fates" Magic4
    /call AbilitySet_ChooseOuter Magic4 Magic4

|-Decay Line of Disease Spells * Var Name: Disease1 string outer >=LVL56 Slow DOT
    /call AbilitySet_Add "Fleshrot's Decay" Disease1
    /call AbilitySet_Add "Danvid's Decay" Disease1
    /call AbilitySet_Add "Mourgis' Decay" Disease1
    /call AbilitySet_Add "Livianus' Decay" Disease1
    /call AbilitySet_Add "Wuran's Decay" Disease1
    /call AbilitySet_Add "Ulork's Decay" Disease1
    /call AbilitySet_Add "Folasar's Decay" Disease1
    /call AbilitySet_Add "Megrima's Decay" Disease1
    /call AbilitySet_Add "Eranon's Decay" Disease1
    /call AbilitySet_Add "Severan's Rot" Disease1
    /call AbilitySet_Add "Chaos Plague" Disease1
    /call AbilitySet_Add "Dark Plague" Disease1
    /call AbilitySet_Add "Cessation of Cor" Disease1
    /call AbilitySet_ChooseOuter Disease1 Disease1
    /call AbilitySet_ChooseOuter Disease1_2 Disease1 "Disease1"

|-Grip Line of Disease Spells * Var Name: Disease2 string outer >=LVL1 HAS DEBUFF
    /call AbilitySet_Add "Fleshrot's Grip of Decay" Disease2
    /call AbilitySet_Add "Grip of Quietus" Disease2
    /call AbilitySet_Add "Danvid's Grip of Decay" Disease2
    /call AbilitySet_Add "Grip of Zorglim" Disease2
    /call AbilitySet_Add "Grip of Kraz" Disease2
    /call AbilitySet_Add "Grip of Jabaum" Disease2
    /call AbilitySet_Add "Grip of Zalikor" Disease2
    /call AbilitySet_Add "Grip of Zargo" Disease2
    /call AbilitySet_Add "Grip of Mori" Disease2
    /call AbilitySet_Add "Plague" Disease2
    /call AbilitySet_Add "Asystole" Disease2
    /call AbilitySet_Add "Scourge" Disease2
    /call AbilitySet_Add "Infectious Cloud" Disease2
    /call AbilitySet_Add "Heart Flutter" Disease2
    /call AbilitySet_Add "Disease Cloud" Disease2
    /call AbilitySet_ChooseOuter Disease2 Disease2

|-Sickness Life of Disease Spells * Var Name: Disease3 string outer >=LVL89 QuickDOT
    /call AbilitySet_Add "Diabo Tatrua's Swift Sickness" Disease3
    /call AbilitySet_Add "Lairsaf's Swift Sickness" Disease3
    /call AbilitySet_Add "Hoshkar's Swift Sickness" Disease3
    /call AbilitySet_Add "Ilsaria's Swift Sickness" Disease3
    /call AbilitySet_Add "Bora's Swift Sickness" Disease3
    /call AbilitySet_Add "Prox's Swift Sickness" Disease3
    /call AbilitySet_Add "Rilfed's Swift Sickness" Disease3
    /call AbilitySet_ChooseOuter Disease3 Disease3

|- ScentDebuff line needed till >= LVL10 <= LVL85
    /call AbilitySet_Add "Scent of The Grave" ScentDebuff
    /call AbilitySet_Add "Scent of Mortality" ScentDebuff
    /call AbilitySet_Add "Scent of Extinction" ScentDebuff
    /call AbilitySet_Add "Scent of Dread" ScentDebuff
    /call AbilitySet_Add "Scent of Nightfall" ScentDebuff
    /call AbilitySet_Add "Scent of Doom" ScentDebuff
    /call AbilitySet_Add "Scent of Gloom" ScentDebuff
    /call AbilitySet_Add "Scent of Afterlight" ScentDebuff
    /call AbilitySet_Add "Scent of Twilight" ScentDebuff
    /call AbilitySet_Add "Scent of Midnight" ScentDebuff
    /call AbilitySet_Add "Scent of Terris" ScentDebuff
    /call AbilitySet_Add "Scent of Darkness" ScentDebuff
    /call AbilitySet_Add "Scent of Shadow" ScentDebuff
    /call AbilitySet_Add "Scent of Dusk" ScentDebuff
    /call AbilitySet_ChooseOuter ScentDebuff ScentDebuff

|- ChaoticDebuff Line >= LVL93
|- Chaotic Contgion
    /call AbilitySet_Add "Chaotic Acridness" ChaoticDebuff
    /call AbilitySet_Add "Chaotic Miasma" ChaoticDebuff
    /call AbilitySet_Add "Chaotic Effluvium" ChaoticDebuff
    /call AbilitySet_Add "Chaotic Liquefaction" ChaoticDebuff
    /call AbilitySet_Add "Chaotic Corruption" ChaoticDebuff
    /call AbilitySet_Add "Chaotic Contagion" ChaoticDebuff
    /call AbilitySet_ChooseOuter ChaoticDebuff ChaoticDebuff

|- CripplingTap >= LVL56 Crippling Claudication
    /call AbilitySet_Add "Crippling Paraplegia" CripplingTap
    /call AbilitySet_Add "Crippling Incapacity" CripplingTap
    /call AbilitySet_Add "Crippling Claudication" CripplingTap
    /call AbilitySet_ChooseOuter CripplingTap CripplingTap

|- SnareDOT >= LVL4 -> <= LVL70
    /call AbilitySet_Add "Harrowing Darkness" SnareDOT
    /call AbilitySet_Add "Tormenting Darkness" SnareDOT
    /call AbilitySet_Add "Gnawing Darkness" SnareDOT
    /call AbilitySet_Add "Grasping Darkness" SnareDOT
    /call AbilitySet_Add "Clutching Darkness" SnareDOT
    /call AbilitySet_Add "Viscous Darkness" SnareDOT
    /call AbilitySet_Add "Tenuous Darkness" SnareDOT
    /call AbilitySet_Add "Clawing Darkness" SnareDOT
    /call AbilitySet_Add "Auroral Darkness" SnareDOT
    /call AbilitySet_Add "Coruscating Darkness" SnareDOT
    /call AbilitySet_Add "Desecrating Darkness" SnareDOT
    /call AbilitySet_Add "Embracing Darkness" SnareDOT
    /call AbilitySet_Add "Devouring Darkness" SnareDOT
    /call AbilitySet_Add "Cascading Darkness" SnareDOT
    /call AbilitySet_Add "Scent of Darkness" SnareDOT
    /call AbilitySet_Add "Dooming Darkness" SnareDOT
    /call AbilitySet_Add "Engulfing Darkness" SnareDOT
    /call AbilitySet_Add "Clinging Darkness" SnareDOT
    /call AbilitySet_ChooseOuter SnareDOT SnareDOT

 | - Fd Spell

    /call AbilitySet_Add "Death Peace" FDSpell
    /call AbilitySet_ChooseOuter FDSpell FDSpell
 
  |- LichForm Spell

    /call AbilitySet_Add "Lunaside" LichSpell   
    /call AbilitySet_Add "Gloomside" LichSpell
    /call AbilitySet_Add "Contraside" LichSpell
    /call AbilitySet_Add "Forgottenside" LichSpell
    /call AbilitySet_Add "Forsakenside" LichSpell
    /call AbilitySet_Add "Shadowside" LichSpell
    /call AbilitySet_Add "Darkside" LichSpell
    /call AbilitySet_Add "Netherside" LichSpell
    /call AbilitySet_Add "Spectralside" LichSpell
    /call AbilitySet_Add "Otherside" LichSpell
    /call AbilitySet_Add "Dark Possession" LichSpell
    /call AbilitySet_Add "Grave Pact" LichSpell
    /call AbilitySet_Add "Seduction of Saryrn" LichSpell
    /call AbilitySet_Add "Arch Lich" LichSpell
    /call AbilitySet_Add "Demi Lich" LichSpell
    /call AbilitySet_Add "Lich" LichSpell
    /call AbilitySet_Add "Call of Bones" LichSpell
    /call AbilitySet_Add "Allure of Death" LichSpell
    /call AbilitySet_Add "Dark Pact" LichSpell
    /call AbilitySet_ChooseOuter LichSpell LichSpell
    
    | - Bestow Line
    /call AbilitySet_Add "Bestow Rot" BestowBuff
    /call AbilitySet_Add "Bestow Dread" BestowBuff
    /call AbilitySet_Add "Bestow Relife" BestowBuff
    /call AbilitySet_Add "Bestow Doom" BestowBuff
    /call AbilitySet_Add "Bestow Mortality" BestowBuff
    /call AbilitySet_Add "Bestow Decay" BestowBuff
    /call AbilitySet_Add "Bestow Unlife" BestowBuff
    /call AbilitySet_Add "Bestow Undeath" BestowBuff
    /call AbilitySet_ChooseOuter BestowBuff BestowBuff

/return

|*-----------------------------------------------------------------------------
|-SUB: SpellSlotConfig
|------------------------------------------------------------------------------*|
Sub NEC_ModeConfigMODEDPS
    /varset Spell1 ${Disease2}
    
    /if (${Me.Level} < 86) {
        /varset Spell2 ${Poison2}
    } else {
        /varset Spell2 ${Poison1}
    }
    
    /if (${Me.Level} < 51) {
        /varset Spell3 ${FireDot2}
    } else {
        /varset Spell3 ${Magic1}
    }
    
    /if (${Me.Level} < 75) {
        /varset Spell4 ${PoisonNuke}
    } else {
        /varset Spell4 ${PoisonNuke2}
    }

    /varset Spell5 ${HealthTaps}
    /varset Spell6 ${DurationTap}
    
    /if (${Me.Level} < 89) {
        /varset Spell7 ${ScentDebuff}
    } else {
        /varset Spell7 ${Disease3}
    }    

    /if (${Me.Level} < 70) {
        /varset Spell8 ${SnareDOT}
    } else /if (${Me.Level} >= 70 && ${Me.Level} < 87) {
        /varset Spell8 ${Magic1}
    } else {
        /varset Spell8 ${Magic3}
    }

    /if (${Me.Level} < 89) {
        /varset Spell9 ${FireDot2}
    } else {
        /varset Spell9 ${FireDot3}
    }    
    
    /if (${Me.Level} < 85) {
        /varset Spell10 ${Poison3}
    } else {
        /varset Spell10 ${SwarmPet}
    }  
    
    /if (${Me.Level} < 93) {
        /varset Spell11 ${Poison3}
    } else {
        /varset Spell11 ${ChaoticDebuff}
    }
    
    /varset Spell12 ${DichoSpell}
    /varset Spell13 ${AllianceSpell}

    |- Self Buff Rotations
    /call AddToRotation NEC_Downtime_MODEDPS_Rotation "Mortifier's Unity" AA ${Parse[0,"(SELFBUFFAACHECK)"]}
    /call AddToRotation NEC_Downtime_MODEDPS_Rotation "${SelfHPBuff}" Spell ${Parse[0,"(SELFBUFFCHECK)"]}
    /call AddToRotation NEC_Downtime_MODEDPS_Rotation "${SelfRune1}" Spell ${Parse[0,"(SELFBUFFCHECK)"]}
    /call AddToRotation NEC_Downtime_MODEDPS_Rotation "${SelfSpellShield1}" Spell ${Parse[0,"(SELFBUFFCHECK)"]}
    /call AddToRotation NEC_Downtime_MODEDPS_Rotation "${LichSpell}" Spell ${Parse[0, "(SELFBUFFCHECK && ${RG_CanUseAA[Mortifier's Unity]} == FALSE) && ${DoLich[SETTINGVAL]}"]}
    /call AddToRotation NEC_Downtime_MODEDPS_Rotation "Death Bloom" AA ${Parse[0, "( ${Me.PctMana}<${DeathBloomPercent[SETTINGVAL]} )"]}
    |/call AddToRotation NEC_Downtime_MODEDPS_Rotation "${BestowBuff}" ${Parse[0, "( !${Me.Song[${BestowBuff}].ID} )"]}
    
    /call AddToRotation NEC_Downtime_MODEDPS_Rotation "${PetHaste}" Spell ${Parse[0,"(SELFBUFFPETCHECK)"]}
    /call AddToRotation NEC_Downtime_MODEDPS_Rotation "${PetBuff}" Spell ${Parse[0,"( SELFBUFFPETCHECK && ${DoPetDrain[SETTINGVAL]} )"]}
    /call AddToRotation NEC_Downtime_MODEDPS_Rotation "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation NEC_Downtime_MODEDPS_Rotation "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}

    
    |- AABurnDPS
    /call AddToRotation NEC_Burn_MODEDPS_Rotation "Funeral Pyre" AA TRUE
    /call AddToRotation NEC_Burn_MODEDPS_Rotation "Hand of Death" AA TRUE
    /call AddToRotation NEC_Burn_MODEDPS_Rotation "Mercurial Torment" AA TRUE
    /call AddToRotation NEC_Burn_MODEDPS_Rotation "Heretic's Twincast" AA ${Parse[0,"( (!${Target.Buff[Heretic's Twincast].ID}) )"]}
    /call AddToRotation NEC_Burn_MODEDPS_Rotation "Gathering Dusk" AA "TRUE"
    /call AddToRotation NEC_Burn_MODEDPS_Rotation "Swarm of Decay" AA "TRUE"
    /call AddToRotation NEC_Burn_MODEDPS_Rotation "Companion's Fury" AA "TRUE"
    /call AddToRotation NEC_Burn_MODEDPS_Rotation "Rise of Bones" AA "TRUE"
    /call AddToRotation NEC_Burn_MODEDPS_Rotation "Focus of Arcanum" AA "TRUE"
    /call AddToRotation NEC_Burn_MODEDPS_Rotation "Forceful Rejuvenation" AA "TRUE"
    /call AddToRotation NEC_Burn_MODEDPS_Rotation "Spire of Necromancy" AA "TRUE"

    |- DPS Rotation
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "Wake the Dead" AA ${Parse[0,"${SpawnCount[corpse radius 100]}"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "Death Bloom" AA ${Parse[0, "( ${Me.PctMana}<${DeathBloomPercent[SETTINGVAL]} && ${Me.PctHPs} > 50 )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "Scent of Thule" AA "${Parse[0, ${XAssist.XTFullHaterCount} > 1 ]}"
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "Encroaching Darkness" AA "${Target.PctHPs} < 50"
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "Dying Grasp" AA "${Parse[0, ${Me.PctAggro}<50 ]}"
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "Silent Casting" AA "${Parse[0, ${XAssist.XTFullHaterCount} > 1 ]}"
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "Life Burn" AA "${Parse[0, ${Me.PctAggro}<=25 ]}"
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${ScentDebuff}" Spell ${Parse[0,"( DETSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${ChaoticDebuff}" Spell ${Parse[0,"( (!${Target.Buff[${Spell[${Spell[${ChaoticDebuff}].Trigger[2]}]}].ID}) && ${Spell[${Spell[${ChaoticDebuff}].Trigger[2]}].StacksTarget} )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${CripplingTap}" Spell ${Parse[0,"( DETSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${DichoSpell}" Spell "TRUE"
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${SwarmPet}" Spell "TRUE"
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${SnareDOT}" Spell ${Parse[0,"( DOTSPELLCHECK && ${DoSnare[SETTINGVAL]} )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${Disease3}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${Magic3}"  Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${FireDot3}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${Disease2}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${Poison1}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${Poison2}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${Poison3}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${Magic1}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${PoisonNuke2}" Spell ${Parse[0,"( ${Target.PctHPs}>50 && ${Me.PctMana} > ${Manatonuke[SETTINGVAL]})"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${PoisonNuke}" Spell ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${HealthTaps}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${DurationTap}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${FireDot1}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${FireDot2}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${FireDot4}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${GroupLeech}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${Corruption1}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODEDPS_Rotation "${DurationTap}" Spell ${Parse[0,"( DOTSPELLCHECK )"]}
/return

|*-----------------------------------------------------------------------------
|-SUB: SpellSlotConfig
|------------------------------------------------------------------------------*|
Sub NEC_ModeConfigMODETLP
	/if (!${Me.HaveExpansion[Dragons of Norrath]} && ${Me.HaveExpansion[Omens of War]}) {
	    /varset Spell1 ${Poison3}
	    /varset Spell2 ${FireDot2}
	    /varset Spell3 ${FireDot2_2}
	    /varset Spell4 ${Poison2_2}
	    /varset Spell5 ${Poison2}
	    /varset Spell6 ${Magic2}
	    /varset Spell7 ${Disease1}
	    /varset Spell8 ${HealthTaps}
	    /varset Spell9 ${FDSpell}

	} else {

	    /varset Spell1 ${Disease2}
    
	    /if (${Me.Level} < 86) {
	        /varset Spell2 ${Poison2}
	    } else {
	        /varset Spell2 ${Poison1}
	    }
    
	    /if (${Me.Level} < 51) {
	        /varset Spell3 ${FireDot2}
	    } else {
	        /varset Spell3 ${Magic1}
	    }
    
	    /if (${Me.Level} < 75) {
	        /varset Spell4 ${PoisonNuke}
	    } else {
	        /varset Spell4 ${PoisonNuke2}
	    }

	    /varset Spell5 ${HealthTaps}
	    /varset Spell6 ${DurationTap}
    
	    /if (${Me.Level} < 89) {
	        /varset Spell7 ${ScentDebuff}
	    } else {
	        /varset Spell7 ${Disease3}
	    }    

	    /if (${Me.Level} < 70) {
	        /varset Spell8 ${SnareDOT}
	    } else /if (${Me.Level} >= 70 && ${Me.Level} < 87) {
	        /varset Spell8 ${Magic1}
	    } else {
	        /varset Spell8 ${Magic3}
	    }

	    /if (${Me.Level} < 89) {
	        /varset Spell9 ${FireDot2}
	    } else {
	        /varset Spell9 ${FireDot3}
	    }    
    
	    /if (${Me.Level} < 85) {
	        /varset Spell10 ${Poison3}
	    } else {
	        /varset Spell10 ${SwarmPet}
	    }  
    
	    /if (${Me.Level} < 93) {
	        /varset Spell11 ${Poison3}
	    } else {
	        /varset Spell11 ${ChaoticDebuff}
	    }
    
	    /varset Spell12 ${DichoSpell}
	    /varset Spell13 ${AllianceSpell}
	}

    |- Self Buff Rotations
    /call AddToRotation NEC_Downtime_MODETLP_Rotation "${SelfHPBuff}"       Spell ${Parse[0,"(SELFBUFFCHECK)"]}
    /call AddToRotation NEC_Downtime_MODETLP_Rotation "${SelfRune1}"        Spell ${Parse[0,"(SELFBUFFCHECK)"]}
    /call AddToRotation NEC_Downtime_MODETLP_Rotation "${SelfSpellShield1}" Spell ${Parse[0,"(SELFBUFFCHECK)"]}

    /call AddToRotation NEC_Downtime_MODETLP_Rotation "${LichSpell}"        Spell ${Parse[0, "(SELFBUFFCHECK && ${RG_CanUseAA[Mortifier's Unity]} == FALSE) && ${DoLich[SETTINGVAL]}"]}
    /call AddToRotation NEC_Downtime_MODETLP_Rotation "${BestowBuff}"       Spell ${Parse[0, "( !${Me.Song[${BestowBuff}].ID} )"]}
    
    | - Mounts & Pets
    /call AddToRotation NEC_Downtime_MODETLP_Rotation "${PetHaste}"              Spell ${Parse[0,"(SELFBUFFPETCHECK)"]}
    /call AddToRotation NEC_Downtime_MODETLP_Rotation "${PetBuff}"               Spell ${Parse[0,"( SELFBUFFPETCHECK && ${DoPetDrain[SETTINGVAL]} )"]}
    /call AddToRotation NEC_Downtime_MODETLP_Rotation "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation NEC_Downtime_MODETLP_Rotation "/dismount"                Command ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}

    /call AddToRotation NEC_Burn_MODETLP_Rotation "${Poison3}"       Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_Burn_MODETLP_Rotation "${FireDot2}"      Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_Burn_MODETLP_Rotation "${FireDot2_2}"    Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_Burn_MODETLP_Rotation "${Poison2_2}"     Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_Burn_MODETLP_Rotation "${Poison2}"       Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_Burn_MODETLP_Rotation "${Disease1}"      Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_Burn_MODETLP_Rotation "${Magic2_2}"      Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_Burn_MODETLP_Rotation "Swarm of Decay"   AA    ${Parse[0,"( TRUE )"]}
    /call AddToRotation NEC_Burn_MODETLP_Rotation "Life Burn"        AA    ${Parse[0,"( TRUE )"]} 

    |- DPS Rotation
    /call AddToRotation NEC_DPS_MODETLP_Rotation "${ScentDebuff}"   Spell ${Parse[0,"( DETSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODETLP_Rotation "${SnareDOT}"      Spell ${Parse[0,"( DOTSPELLCHECK && ${DoSnare[SETTINGVAL]} )"]}
    /call AddToRotation NEC_DPS_MODETLP_Rotation "${Magic2}"        Spell ${Parse[0,"( DOTSPELLCHECK )"]}
    /call AddToRotation NEC_DPS_MODETLP_Rotation "${HealthTaps}"    Spell ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}



/return

Sub NEC_Combat_Routine
    /call PetAttack
    /if ( ${Target.ID}==${Me.GroupAssistTarget.ID} && ${Me.PctHPs}< 75 &&  ( ${Me.PctAggro}>=80 || ${Me.TargetOfTarget.ID}==${Me.ID} )  ) {
		/if (${RG_AAReady[Death Peace]}) {
			/call AANow ${Me.AltAbility[Death Peace].ID} ${Target.ID}
		} else /if (${RG_AAReady[Harmshield]}) {
			/call AANow ${Me.AltAbility[Harmshield].ID} ${Me.ID}
		} 
	}
    /if ( ${Me.State.Equal[feign]} && ( ${Me.PctAggro}<90 || ${Me.TargetOfTarget.ID}==!${Me.ID} ) ) /stand
    /if ( DODPS ) {
        /if ( BURNCHECK ) {
            /call Ordered_Rotation_Follow ${Me.Class.ShortName}_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE TRUE
        }
        /call Ordered_Rotation_Follow ${Me.Class.ShortName}_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }
/return FALSE

Sub NEC_Downtime_Routine
    |- TO DO ADD BONECHIPS CHECK THEN DISABLE DoPet IF NOT ENOUGH BONECHIPS.
    /if (${DoPet[SETTINGVAL]} && !${Me.Pet.ID} ) {
        /if (${PetType[SETTINGVAL].Equal[war]}) {
            /if (${PCSpellReady[${PetSpellWar}]}) {
               /call SpellNow "${PetSpellWar}" ${Me.ID}
               /varset spellrememtimer 5s 
            }
        } else /if (${PetType[SETTINGVAL].Equal[rog]}) {
            /if (${PCSpellReady[${PetSpellRog}]}) {
               /call SpellNow "${PetSpellRog}" ${Me.ID}
               /varset spellrememtimer 5s
           }
        } else {
            /echo \arERROR: \ax Bad pet type chosen. Disabling pets but not changing the INI setting.
            /varset DoPet[SETTINGVAL] 0
        }
    }
    |- Call Self buffs
    /call FollowRotation  ${Me.Class.ShortName}_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}

    /if (${Me.Pet.ID}) {
        /call FollowRotation  ${Me.Class.ShortName}_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.Pet.ID}
    } 
/return FALSE

Sub NEC_PullSetup
    |- DoPetPull defined in rgpull.inc -- Defaults to 0.
    /if (${Me.Pet.ID} && ${DoPetPull[SETTINGVAL]}) {
        /call Pull_SetAbility "pullpet" "Special"
    } else /if (${SnareDOT.NotEqual[NULL]} && ${DoSnare[SETTINGVAL]}&&${Me.Gem[${SnareDOT}]}) { 
		/call Pull_SetAbility "${SnareDOT}" "Spell" 
    } else /if (${ScentDebuff.NotEqual[NULL]}&&${Me.Gem[${ScentDebuff}]}) {
        /call Pull_SetAbility "${ScentDebuff}" Spell
    } else {
        /echo \awNOTICE:\ax No Pull Ability Available. Disabling Pulling. Suggestion: /rg DoPetPull 1.
        /varset DoPull[SETTINGVAL] PMODE_OFF
    }
/return