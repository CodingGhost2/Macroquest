|- RGmagutil.inc - By Gnits
|- Automatic Magician Bot
|- Version 0.4
|- Updated: 09/28/2020
|- Credit: Toots, Noobhax0r, Maskoi, Ctaylor, Treehuggindruid. A lot of ideas were borrowed and modified from their macros

|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
#define MODEFIRE 0
#define MODEPETTANK 1
#define MODETLP 2
#define MODEMAGIC 99

Sub MAG_Setup
    /declare RGList_MAG            list outer 

|- Rotations
    | - Fire Mode Rotations     
    /call Ordered_Rotation_New MAG_DPS_MODEFIRE_Rotation
    /call Ordered_Rotation_New MAG_Burn_MODEFIRE_Rotation
    /call Ordered_Rotation_New MAG_Downtime_MODEFIRE_Rotation
    /call Ordered_Rotation_New MAG_Debuff_MODEFIRE_Rotation
    | - Magic Mode Rotations
    /call Ordered_Rotation_New MAG_DPS_MODEMAGIC_Rotation
    /call Ordered_Rotation_New MAG_Burn_MODEMAGIC_Rotation
    /call Ordered_Rotation_New MAG_Downtime_MODEMAGIC_Rotation
    /call Ordered_Rotation_New MAG_Debuff_MODEMAGIC_Rotation
    | - Pet Tank Mode Rotations
    /call Ordered_Rotation_New MAG_DPS_MODEPETTANK_Rotation
    /call Ordered_Rotation_New MAG_DPSPET_MODEPETTANK_Rotation
    /call Ordered_Rotation_New MAG_Burn_MODEPETTANK_Rotation
    /call Ordered_Rotation_New MAG_Downtime_MODEPETTANK_Rotation
    /call Ordered_Rotation_New MAG_Debuff_MODEPETTANK_Rotation
    | - TLP Mode Rotations     
    /call Ordered_Rotation_New MAG_DPS_MODETLP_Rotation
    /call Ordered_Rotation_New MAG_Burn_MODETLP_Rotation
    /call Ordered_Rotation_New MAG_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New MAG_Debuff_MODETLP_Rotation
|-Items
    /call ItemSet_New Epic
|-Spells
|- Nukes
    /call AbilitySet_New SwarmPet
    /call AbilitySet_New SpearNuke
    /call AbilitySet_New ChaoticNuke
    /call AbilitySet_New FireNuke
    /call AbilitySet_New MagicNuke
    /call AbilitySet_New SummonNuke
    /call AbilitySet_New FireBoltNuke
    /call AbilitySet_New MagicBoltNuke
    /call AbilitySet_New BeamNuke
    /call AbilitySet_New RainNuke
    /call AbilitySet_New MagicRainNuke
    /call AbilitySet_New VolleyNuke
    /call AbilitySet_New SummonedNuke
    /call AbilitySet_New MaloNuke
|- Buffs
    /call AbilitySet_New SelfShield
    /call AbilitySet_New ShortDurDmgShield
    /call AbilitySet_New LongDurDmgShield
    /call AbilitySet_New ManaRegenBuff
    /call AbilitySet_New AllianceBuff
    /call AbilitySet_New SurgeDS
    /call AbilitySet_New PetAura
    /call AbilitySet_New SingleDS
    /call AbilitySet_New FireShroud
    /call AbilitySet_New PetBodyGuard
    /call AbilitySet_New GatherMana
    
| - Pet Spells Pets & Spells Affecting them   
    /call AbilitySet_New MeleeGuard  
    /call AbilitySet_New DichoSpell
    /call AbilitySet_New PetHealSpell
    /call AbilitySet_New PetPromisedSpell
    /call AbilitySet_New PetStanceSpell
    /call AbilitySet_New PetManaConv
    /call AbilitySet_New PetHaste
    /call AbilitySet_New PetIceFlame
    /call AbilitySet_New EarthPetSpell
    /call AbilitySet_New WaterPetSpell
    /call AbilitySet_New AirPetSpell
    /call AbilitySet_New FirePetSpell
    /call AbilitySet_New AegisBuff
    /call AbilitySet_New PetManaNuke
    
| - Summoned item Spells
    /call AbilitySet_New PetArmorSummon
    /call AbilitySet_New PetWeaponSummon
    /call AbilitySet_New PetHeirloomSummon
    /call AbilitySet_New IceOrbSummon
    /call AbilitySet_New FireOrbSummon
    /call AbilitySet_New EarthPetItemSummon
    /call AbilitySet_New FirePetItemSummon
    /call AbilitySet_New ManaRodSummon
    /call AbilitySet_New SelfManaRodSummon
| - Debuffs     
    /call AbilitySet_New MaloDebuff
    
    /declare TwinCast               string outer ${Spell[Twincast].RankName}
    /declare PetAura                string outer ${Spell[Arcane Distillect].RankName}
    /declare FireOrbItem            string outer NULL
    /declare IceOrbItem             string outer NULL
    /declare EarthPetItem           string outer NULL
    /declare FirePetItem            string outer NULL
    /declare SelfModRod             string outer NULL
    /declare GroupModRod            string outer NULL

|- Misc Variables
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
    
|-Config Options
    /call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = Fire; 1 = Pet Tank. 2 = TLP
    /call RGLoadSetting MAG DoOOWRobe 0 Pet "Set 0/1 to use Omens of War Tier 1/2 Robe for Survivability" 1
|- Nuke Controls
    /call RGLoadSetting MAG DoRain 1  Combat "Turn On AOE rains or Off 0/1"
    /call RGLoadSetting MAG DoMagicNuke 0 Combat "Set to use magic nukes instead of fire"
    /call RGLoadSetting MAG DoForce 1 Combat "Turn on or Off doing Force of Elements"

| - Pet Controls    
    /call RGLoadSetting MAG DoHeals 1 Healing "Set 0/1 to heal your pet. Checked in main loop."
    /call RGLoadSetting MAG PetHealPct 50 Pet "% Health to start healing your pet."
    /call RGLoadSetting MAG DoPet 1 Pet "Set 0/1 to use your pet." 
    /call RGLoadSetting MAG DoPocketPet 0 Pet "Set 0/1 to pocket a pet during downtime." 1
    /call RGLoadSetting MAG DoPetTank 0 Pet "Set 0/1 to enable pet tanking (even if not in optimize pet tank class mode). Requires Macro Restart." 1
    /call RGLoadSetting MAG PetType "Water" Pet "Set to Fire, Water, Earth, or Air to choose pet type. \arCASE SENSITIVE\ax. Default: Water" 0 "ChangePetType" 
| - Summoned Items Control
    /call RGLoadSetting MAG DoGroupToys 0 Options "AutoMatically Summons Swords & Armor for Group pets During Downtime"
    /call RGLoadSetting MAG DoPetArmor 1 Options "Because there is no way to detect if a pet has armor or not This allows u to turn off the feature" 1
    /call RGLoadSetting MAG DoPetHeirloom 1 Options "Because there is no way to detect if a pet has Heirlooms or not This allows u to turn off the feature" 1
    
| - Debuff Control
    /call RGLoadSetting MAG AutoDebuffAt 99 Debuff "%HP to debuff Mobs. Checked by ." 1    
    /call RGLoadSetting MAG DoMalo 1 Debuff "Set 0/1 to use Malo debuff."
    /call RGLoadSetting MAG DoAEMalo 0 Debuff "Set 0/1 to use AoE Malo debuff." 1
| - Mana Control
    /call RGLoadSetting MAG Manatonuke 30 Combat "% Mana to stop nuking at."
    /call RGLoadSetting MAG ManaGatherPct 70 Options "% of Mana to use mana gather abilities."
    /call RGLoadSetting MAG DoCombatRod 1 Options " Set 0/1 to Recast Mod Rods During Combat Both group And Self" 1
    /call RGLoadSetting MAG SummonModRods 1 Options "Set 0/1 to group summon mana rods." 1
    
|-Declare spell variables
    /declare GroupBuffRecast         int outer 0
    /declare miscspellremem        string outer NULL
    /declare tempid                        string outer NULL
    /declare PetTypeName        string outer NULL
    /declare spellrememtimer        timer outer 0
    /declare ReadyToCast              timer outer 0
    /declare groupbufftimer            timer outer 0
    /declare spellmisc                 int outer ${Me.NumGems}
|-Declare other variables
    /declare OowRobeName        string outer NULL
    /declare PocketPet          int outer 0 
/return

Sub ChangePetType
    /varset PetTypeName ${${PetType[SETTINGVAL]}PetSpell}
/return

|----------------------------------------------------------------------------
|- SUB: CheckSpells
|---------------------------------------------------------------------------- 
Sub MAG_SetupSkills
    /echo Choosing All Magician Spells - this may take a moment
|- Mage Epic
    /call ItemSet_Add "Focus of Primal Elements"    Epic
    /call ItemSet_Add "Staff of Elemental Essence"  Epic
    /call ItemSet_ChooseOuter Epic Epic

| - Mage Pet Aura
    /call AbilitySet_Add "Arcane Distillect" PetAura 
    /call AbilitySet_ChooseOuter PetAura PetAura
    
|-Swarm Pet* >= LVL 70
    /call AbilitySet_Add "Ravening Servant" SwarmPet
    /call AbilitySet_Add "Roiling Servant" SwarmPet
    /call AbilitySet_Add "Riotous Servant" SwarmPet
    /call AbilitySet_Add "Reckless Servant" SwarmPet
    /call AbilitySet_Add "Remorseless Servant" SwarmPet
    /call AbilitySet_Add "Relentless Servant" SwarmPet
    /call AbilitySet_Add "Ruthless Servant" SwarmPet
    /call AbilitySet_Add "Ruinous Servant" SwarmPet
    /call AbilitySet_Add "Rumbling Servant" SwarmPet
    /call AbilitySet_Add "Rancorous Servant" SwarmPet
    /call AbilitySet_Add "Rampaging Servant" SwarmPet
    /call AbilitySet_Add "Raging Servant" SwarmPet
    /call AbilitySet_Add "Rage of Zomm" SwarmPet
    /call AbilitySet_ChooseOuter SwarmPet SwarmPet
    
|-Spear Nuke* >= LVL 70
    /call AbilitySet_Add "Spear of Molten Dacite" SpearNuke
    /call AbilitySet_Add "Spear of Molten Luclinite" SpearNuke
    /call AbilitySet_Add "Spear of Molten Komatiite" SpearNuke
    /call AbilitySet_Add "Spear of Molten Arcronite" SpearNuke
    /call AbilitySet_Add "Spear of Molten Shieldstone" SpearNuke
    /call AbilitySet_Add "Spear of Blistersteel" SpearNuke
    /call AbilitySet_Add "Spear of Molten Steel" SpearNuke
    /call AbilitySet_Add "Spear of Magma" SpearNuke
    /call AbilitySet_Add "Spear of Ro" SpearNuke
    /call AbilitySet_ChooseOuter SpearNuke SpearNuke
    /call AbilitySet_ChooseOuter SpearNuke2 SpearNuke "${SpearNuke}" 
    
|-Chaotic Nuke with Beneficial Effect >= LVL69
    /call AbilitySet_Add "Chaotic Magma" ChaoticNuke
    /call AbilitySet_Add "Chaotic Calamity" ChaoticNuke
    /call AbilitySet_Add "Chaotic Pyroclasm" ChaoticNuke
    /call AbilitySet_Add "Chaotic Inferno" ChaoticNuke
    /call AbilitySet_Add "Chaotic Fire" ChaoticNuke
    /call AbilitySet_Add "Fickle Magma" ChaoticNuke
    /call AbilitySet_Add "Fickle Flames" ChaoticNuke
    /call AbilitySet_Add "Fickle Flare" ChaoticNuke
    /call AbilitySet_Add "Fickle Blaze" ChaoticNuke
    /call AbilitySet_Add "Fickle Pyroclasm" ChaoticNuke
    /call AbilitySet_Add "Fickle Inferno" ChaoticNuke
    /call AbilitySet_Add "Fickle Fire" ChaoticNuke
    /call AbilitySet_ChooseOuter ChaoticNuke ChaoticNuke

|- Fire Nuke 1 <= LVL <= 70
    /call AbilitySet_Add "Cremating Sands" FireNuke
    /call AbilitySet_Add "Ravaging Sands" FireNuke
    /call AbilitySet_Add "Incinerating Sands" FireNuke
    /call AbilitySet_Add "Crash of Sand" FireNuke
    /call AbilitySet_Add "Blistering Sands" FireNuke
    /call AbilitySet_Add "Searing Sands" FireNuke
    /call AbilitySet_Add "Broiling Sands" FireNuke
    /call AbilitySet_Add "Blast of Sand" FireNuke
    /call AbilitySet_Add "Burning Sands" FireNuke
    /call AbilitySet_Add "Burst of Sand" FireNuke
    /call AbilitySet_Add "Strike of Sand" FireNuke
    /call AbilitySet_Add "Torrid Sands" FireNuke
    /call AbilitySet_Add "Scorching Sands" FireNuke
    /call AbilitySet_Add "Scalding Sands" FireNuke
    /call AbilitySet_Add "Sun Vortex" FireNuke
    /call AbilitySet_Add "Star Strike" FireNuke
    /call AbilitySet_Add "Ancient: Nova Strike" FireNuke
    /call AbilitySet_Add "Burning Sand" FireNuke
    /call AbilitySet_Add "Shock of Fiery Blades" FireNuke
    /call AbilitySet_Add "Char" FireNuke
    /call AbilitySet_Add "Blaze" FireNuke
    /call AbilitySet_Add "Shock of Flame" FireNuke
    /call AbilitySet_Add "Burn" FireNuke
    /call AbilitySet_Add "Burst of Flame" FireNuke
    /call AbilitySet_ChooseOuter FireNuke1 FireNuke
    /call AbilitySet_ChooseOuter FireNuke2 FireNuke "${FireNuke1}"
    
|- MagicNuke Nuke 1 <= LVL <= 69
    /call AbilitySet_Add "Shock of Memorial Steel" MagicNuke
    /call AbilitySet_Add "Shock of Carbide Steel" MagicNuke
    /call AbilitySet_Add "Shock of Burning Steel" MagicNuke
    /call AbilitySet_Add "Shock of Arcronite Steel" MagicNuke
    /call AbilitySet_Add "Shock of Darksteel" MagicNuke
    /call AbilitySet_Add "Shock of Blistersteel" MagicNuke
    /call AbilitySet_Add "Shock of Argathian Steel" MagicNuke
    /call AbilitySet_Add "Shock of Ethereal Steel" MagicNuke
    /call AbilitySet_Add "Shock of Discordant Steel" MagicNuke
    /call AbilitySet_Add "Shock of Cineral Steel" MagicNuke
    /call AbilitySet_Add "Shock of Silvered Steel" MagicNuke
    /call AbilitySet_Add "Blade Strike" MagicNuke  
    /call AbilitySet_Add "Rock of Taelosia" MagicNuke
    /call AbilitySet_Add "Black Steel" MagicNuke
    /call AbilitySet_Add "Shock of Steel" MagicNuke
    /call AbilitySet_Add "Shock of Swords" MagicNuke
    /call AbilitySet_Add "Shock of Spikes" MagicNuke
    /call AbilitySet_Add "Shock of Blades" MagicNuke
    /call AbilitySet_ChooseOuter MagicNuke1 MagicNuke
    /call AbilitySet_ChooseOuter MagicNuke2 MagicNuke "${MagicNuke1}"

|- Magic Bolt Nukes
    /call AbilitySet_Add "Luclinite Bolt" MagicBoltNuke
    /call AbilitySet_Add "Komatiite Bolt" MagicBoltNuke
    /call AbilitySet_Add "Korascian Bolt" MagicBoltNuke
    /call AbilitySet_Add "Meteoric Bolt" MagicBoltNuke
    /call AbilitySet_Add "Iron Bolt" MagicBoltNuke
    /call AbilitySet_ChooseOuter MagicBoltNuke1 MagicBoltNuke
    /call AbilitySet_ChooseOuter MagicBoltNuke2 MagicBoltNuke "${MagicBoltNuke1}"

|- MaloDebuff line < LVL 75 @ LVL75 use the AA
    /call AbilitySet_Add "Malosinera" MaloDebuff
    /call AbilitySet_Add "Malosinetra" MaloDebuff
    /call AbilitySet_Add "Malosinara" MaloDebuff
    /call AbilitySet_Add "Malosinata" MaloDebuff
    /call AbilitySet_Add "Malosenete" MaloDebuff
    /call AbilitySet_Add "Malosenia" MaloDebuff
    /call AbilitySet_Add "Maloseneta" MaloDebuff
    /call AbilitySet_Add "Malosene" MaloDebuff
    /call AbilitySet_Add "Malosenea" MaloDebuff
    /call AbilitySet_Add "Malosinatia" MaloDebuff
    /call AbilitySet_Add "Malosinise" MaloDebuff
    /call AbilitySet_Add "Malosinia" MaloDebuff
    /call AbilitySet_Add "Mala" MaloDebuff
    /call AbilitySet_Add "Malosini" MaloDebuff
    /call AbilitySet_Add "Malosi" MaloDebuff
    /call AbilitySet_Add "Malaisement" MaloDebuff
    /call AbilitySet_Add "Malaise" MaloDebuff
    /call AbilitySet_ChooseOuter MaloDebuff MaloDebuff

| - Shock/Malo Combo Line
    /call AbilitySet_Add "Memorial Steel Malosinera" MaloNuke
    /call AbilitySet_Add "Carbide Malosinetra" MaloNuke
    /call AbilitySet_Add "Blistersteel Malosenia" MaloNuke
    /call AbilitySet_Add "Darksteel Malosenete" MaloNuke
    /call AbilitySet_Add "Arcronite Malosinata" MaloNuke
    /call AbilitySet_Add "Burning Malosinara" MaloNuke
    /call AbilitySet_ChooseOuter MaloNuke MaloNuke



|- Unnatural Nukes >70
    /call AbilitySet_Add "Dismantle the Unnatural" SummonedNuke
    /call AbilitySet_Add "Unmend the Unnatural" SummonedNuke
    /call AbilitySet_Add "Obliterate the Unnatural" SummonedNuke
    /call AbilitySet_Add "Repudiate the Unnatural" SummonedNuke
    /call AbilitySet_Add "Eradicate the Unnatural" SummonedNuke
    /call AbilitySet_Add "Exterminate the Unnatural" SummonedNuke
    /call AbilitySet_Add "Abolish the Divergent" SummonedNuke
    /call AbilitySet_Add "Annihilate the Divergent" SummonedNuke
    /call AbilitySet_Add "Annihilate the Anomalous" SummonedNuke
    /call AbilitySet_Add "Annihilate the Aberrant" SummonedNuke
    /call AbilitySet_Add "Annihilate the Unnatural" SummonedNuke
    /call AbilitySet_ChooseOuter SummonedNuke1 SummonedNuke
    /call AbilitySet_ChooseOuter SummonedNuke2 SummonedNuke "${SummonedNuke1}"
    /call AbilitySet_ChooseOuter SummonedNuke3 SummonedNuke "${SummonedNuke1}|${SummonedNuke2}"

|- Fire Bolt Nukes
    /call AbilitySet_Add "Bolt of Molten Dacite" FireBoltNuke
    /call AbilitySet_Add "Bolt of Molten Olivine" FireBoltNuke
    /call AbilitySet_Add "Bolt of Molten Komatiite" FireBoltNuke
    /call AbilitySet_Add "Bolt of Skyfire" FireBoltNuke
    /call AbilitySet_Add "Bolt of Molten Shieldstone" FireBoltNuke
    /call AbilitySet_Add "Bolt of Molten Magma" FireBoltNuke
    /call AbilitySet_Add "Bolt of Molten Steel" FireBoltNuke
    /call AbilitySet_Add "Bolt of Rhyolite" FireBoltNuke
    /call AbilitySet_Add "Bolt of Molten Scoria" FireBoltNuke
    /call AbilitySet_Add "Bolt of Molten Dross" FireBoltNuke
    /call AbilitySet_Add "Bolt of Molten Slag" FireBoltNuke
    /call AbilitySet_Add "Bolt of Jerikor" FireBoltNuke
    /call AbilitySet_Add "Firebolt of Tallon" FireBoltNuke
    /call AbilitySet_Add "Seeking Flame of Seukor" FireBoltNuke
    /call AbilitySet_Add "Scars of Sigil" FireBoltNuke
    /call AbilitySet_Add "Lava Bolt" FireBoltNuke    
    /call AbilitySet_Add "Cinder Bolt" FireBoltNuke
    /call AbilitySet_Add "Bolt of Flame" FireBoltNuke
    /call AbilitySet_Add "Flame Bolt" FireBoltNuke
    /call AbilitySet_ChooseOuter FireBoltNuke FireBoltNuke

|-Beam Frontal AOE Spell*
    /call AbilitySet_Add "Beam of Molten Dacite" BeamNuke
    /call AbilitySet_Add "Beam of Molten Olivine" BeamNuke
    /call AbilitySet_Add "Beam of Molten Komatiite" BeamNuke
    /call AbilitySet_Add "Beam of Molten Rhyolite" BeamNuke
    /call AbilitySet_Add "Beam of Molten Shieldstone" BeamNuke
    /call AbilitySet_Add "Beam of Brimstone" BeamNuke
    /call AbilitySet_Add "Beam of Molten Steel" BeamNuke
    /call AbilitySet_Add "Beam of Rhyolite" BeamNuke
    /call AbilitySet_Add "Beam of Molten Scoria" BeamNuke
    /call AbilitySet_Add "Beam of Molten Dross" BeamNuke
    /call AbilitySet_Add "Beam of Molten Slag" BeamNuke
    /call AbilitySet_ChooseOuter BeamNuke BeamNuke

|-Rain AOE Spell*
    /call AbilitySet_Add "Rain of Molten Dacite" RainNuke
    /call AbilitySet_Add "Rain of Molten Olivine" RainNuke
    /call AbilitySet_Add "Rain of Molten Komatiite" RainNuke
    /call AbilitySet_Add "Rain of Molten Rhyolite" RainNuke
    /call AbilitySet_Add "Coronal Rain" RainNuke
    /call AbilitySet_Add "Rain of Blistersteel" RainNuke
    /call AbilitySet_Add "Rain of Molten Steel" RainNuke
    /call AbilitySet_Add "Rain of Rhyolite" RainNuke
    /call AbilitySet_Add "Rain of Molten Scoria" RainNuke
    /call AbilitySet_Add "Rain of Molten Dross" RainNuke
    /call AbilitySet_Add "Rain of Molten Slag" RainNuke
    /call AbilitySet_Add "Rain of Jerikor" RainNuke
    /call AbilitySet_Add "Sun Storm" RainNuke
    /call AbilitySet_Add "Sirocco" RainNuke
    /call AbilitySet_Add "Rain of Lava" RainNuke
    /call AbilitySet_Add "Rain of Fire" RainNuke
    /call AbilitySet_ChooseOuter RainNuke RainNuke

| - Magic Rain
    /call AbilitySet_Add "rain of Kukris" MagicRainNuke
    /call AbilitySet_Add "Rain of Falchions" MagicRainNuke
    /call AbilitySet_Add "Rain of Blades" MagicRainNuke
    /call AbilitySet_Add "Rain of Spikes" MagicRainNuke
    /call AbilitySet_Add "Rain Of Swords" MagicRainNuke
    /call AbilitySet_Add "ManaStorm" MagicRainNuke
    /call AbilitySet_Add "Maelstrom of Electricity" MagicRainNuke
    /call AbilitySet_Add "Maelstrom of Thunder" MagicRainNuke
    /call AbilitySet_ChooseOuter MagicRainNuke MagicRainNuke    
    
|-Volley Nuke - Pet buff*
    /call AbilitySet_Add "Fusillade of Many" VolleyNuke
    /call AbilitySet_Add "Barrage of Many" VolleyNuke
    /call AbilitySet_Add "Shockwave of Many" VolleyNuke
    /call AbilitySet_Add "Volley of Many" VolleyNuke
    /call AbilitySet_Add "Storm of Many" VolleyNuke
    /call AbilitySet_Add "Salvo of Many" VolleyNuke
    /call AbilitySet_Add "Strike of Many" VolleyNuke
    /call AbilitySet_Add "Clash of Many" VolleyNuke
    /call AbilitySet_Add "Jolt of Many" VolleyNuke
    /call AbilitySet_Add "Shock of Many" VolleyNuke
    /call AbilitySet_ChooseOuter VolleyNuke VolleyNuke
    
|-Dicho Spell*
    /call AbilitySet_Add "Ecliptic Companion" DichoSpell
    /call AbilitySet_Add "Composite Companion" DichoSpell
    /call AbilitySet_Add "Dissident Companion" DichoSpell
    /call AbilitySet_Add "Dichotomic Companion" DichoSpell
    /call AbilitySet_ChooseOuter DichoSpell DichoSpell

|-Pet Heal*
    /call AbilitySet_Add "Renewal of Shoru" PetHealSpell
    /call AbilitySet_Add "Renewal of Iilivina " PetHealSpell
    /call AbilitySet_Add "Renewal of Evreth" PetHealSpell
    /call AbilitySet_Add "Renewal of Ioulin" PetHealSpell
    /call AbilitySet_Add "Renewal of Calix" PetHealSpell
    /call AbilitySet_Add "Renewal of Hererra" PetHealSpell
    /call AbilitySet_Add "Renewal of Sirqo" PetHealSpell
    /call AbilitySet_Add "Renewal of Volark" PetHealSpell
    /call AbilitySet_Add "Renewal of Cadwin" PetHealSpell
    /call AbilitySet_Add "Revival of Aenro" PetHealSpell
    /call AbilitySet_Add "Renewal of Aenda" PetHealSpell
    /call AbilitySet_Add "Renewal of Jerikor" PetHealSpell
    /call AbilitySet_Add "Planar Renewal" PetHealSpell
    /call AbilitySet_Add "Transon's Elemental Renewal" PetHealSpell
    /call AbilitySet_Add "Transon's Elemental Infusion" PetHealSpell
    /call AbilitySet_Add "Refresh Summoning" PetHealSpell
    /call AbilitySet_Add "Renew Summoning" PetHealSpell
    /call AbilitySet_Add "Renew Elements" PetHealSpell
    /call AbilitySet_ChooseOuter PetHealSpell PetHealSpell

|-Pet Promised*
    /call AbilitySet_Add "Promised Reconstitution" PetPromisedSpell
    /call AbilitySet_Add "Promised Relief" PetPromisedSpell
    /call AbilitySet_Add "Promised Healing" PetPromisedSpell
    /call AbilitySet_Add "Promised Alleviation" PetPromisedSpell
    /call AbilitySet_Add "Promised Invigoration" PetPromisedSpell
    /call AbilitySet_Add "Promised Amelioration" PetPromisedSpell
    /call AbilitySet_Add "Promised Amendment" PetPromisedSpell
    /call AbilitySet_Add "Promised Wardmending" PetPromisedSpell
    /call AbilitySet_Add "Promised Rejuvenation" PetPromisedSpell
    /call AbilitySet_Add "Promised Recovery" PetPromisedSpell
    /call AbilitySet_ChooseOuter PetPromisedSpell PetPromisedSpell

|-Pet Stance*
    /call AbilitySet_Add "Omphacite Stance" PetStanceSpell
    /call AbilitySet_Add "Kanoite Stance" PetStanceSpell
    /call AbilitySet_Add "Pyroxene Stance" PetStanceSpell
    /call AbilitySet_Add "Rhyolite Stance" PetStanceSpell
    /call AbilitySet_Add "Shieldstone Stance" PetStanceSpell
    /call AbilitySet_Add "Groundswell Stance" PetStanceSpell
    /call AbilitySet_Add "Steelstance" PetStanceSpell
    /call AbilitySet_Add "Tellurian Stance" PetStanceSpell
    /call AbilitySet_Add "Earthen Stance" PetStanceSpell
    /call AbilitySet_Add "Grounded Stance" PetStanceSpell
    /call AbilitySet_Add "Granite Stance" PetStanceSpell
    /call AbilitySet_ChooseOuter PetStanceSpell PetStanceSpell
    
|--- Earth Pet*
    /call AbilitySet_Add "Recruitment of Earth" EarthPetSpell    
    /call AbilitySet_Add "Conscription of Earth" EarthPetSpell
    /call AbilitySet_Add "Manifestation of Earth" EarthPetSpell
    /call AbilitySet_Add "Embodiment of Earth" EarthPetSpell
    /call AbilitySet_Add "Convocation of Earth" EarthPetSpell
    /call AbilitySet_Add "Shard of Earth" EarthPetSpell
    /call AbilitySet_Add "Facet of Earth" EarthPetSpell
    /call AbilitySet_Add "Construct of Earth" EarthPetSpell
    /call AbilitySet_Add "Aspect of Earth" EarthPetSpell
    /call AbilitySet_Add "Core of Earth" EarthPetSpell
    /call AbilitySet_Add "Essence of Earth" EarthPetSpell
    /call AbilitySet_Add "Child of Earth" EarthPetSpell
    /call AbilitySet_Add "Greater Vocaration: Earth" EarthPetSpell
    /call AbilitySet_Add "Vocarate: Earth" EarthPetSpell
    /call AbilitySet_Add "Conjuration: Earth" EarthPetSpell
    /call AbilitySet_Add "Lesser Conjuration: Earth" EarthPetSpell
    /call AbilitySet_Add "Minor Conjuration: Earth" EarthPetSpell
    /call AbilitySet_Add "Greater Summoning: Earth" EarthPetSpell
    /call AbilitySet_Add "Summoning: Earth" EarthPetSpell
    /call AbilitySet_Add "Lesser Summoning: Earth" EarthPetSpell
    /call AbilitySet_Add "Minor Summoning: Earth" EarthPetSpell
    /call AbilitySet_Add "Elemental: Earth" EarthPetSpell
    /call AbilitySet_Add "Elementaling: Earth" EarthPetSpell
    /call AbilitySet_Add "Elementalkin: Earth" EarthPetSpell
    /call AbilitySet_ChooseOuter EarthPetSpell EarthPetSpell
 
|--- Water Pet*
    /call AbilitySet_Add "Recruitment of Water" WaterPetSpell
    /call AbilitySet_Add "Conscription of Water" WaterPetSpell
    /call AbilitySet_Add "Manifestation of Water" WaterPetSpell
    /call AbilitySet_Add "Embodiment of Water" WaterPetSpell
    /call AbilitySet_Add "Convocation of Water" WaterPetSpell
    /call AbilitySet_Add "Shard of Water" WaterPetSpell
    /call AbilitySet_Add "Facet of Water" WaterPetSpell
    /call AbilitySet_Add "Construct of Water" WaterPetSpell
    /call AbilitySet_Add "Aspect of Water" WaterPetSpell
    /call AbilitySet_Add "Core of Water" WaterPetSpell
    /call AbilitySet_Add "Essence of Water" WaterPetSpell
    /call AbilitySet_Add "Child of Water" WaterPetSpell
    /call AbilitySet_Add "Servant of Marr" WaterPetSpell
    /call AbilitySet_Add "Greater Vocaration: Water" WaterPetSpell
    /call AbilitySet_Add "Vocarate: Water" WaterPetSpell
    /call AbilitySet_Add "Greater Conjuration: Water" WaterPetSpell
    /call AbilitySet_Add "Conjuration: Water" WaterPetSpell
    /call AbilitySet_Add "Lesser Conjuration: Water" WaterPetSpell
    /call AbilitySet_Add "Minor Conjuration: Water" WaterPetSpell
    /call AbilitySet_Add "Greater Summoning: Water" WaterPetSpell
    /call AbilitySet_Add "Summoning: Water" WaterPetSpell
    /call AbilitySet_Add "Lesser Summoning: Water" WaterPetSpell
    /call AbilitySet_Add "Minor Summoning: Water" WaterPetSpell
    /call AbilitySet_Add "Elemental: Water" WaterPetSpell
    /call AbilitySet_Add "Elementaling: Water" WaterPetSpell
    /call AbilitySet_Add "Elementalkin: Water" WaterPetSpell
    /call AbilitySet_ChooseOuter WaterPetSpell WaterPetSpell

|--- Air Pet*
    /call AbilitySet_Add "Recruitment of Air" AirPetSpell
    /call AbilitySet_Add "Conscription of Air" AirPetSpell
    /call AbilitySet_Add "Manifestation of Air" AirPetSpell
    /call AbilitySet_Add "Embodiment of Air" AirPetSpell
    /call AbilitySet_Add "Convocation of Air" AirPetSpell
    /call AbilitySet_Add "Shard of Air" AirPetSpell
    /call AbilitySet_Add "Facet of Air" AirPetSpell
    /call AbilitySet_Add "Construct of Air" AirPetSpell
    /call AbilitySet_Add "Aspect of Air" AirPetSpell
    /call AbilitySet_Add "Core of Air" AirPetSpell
    /call AbilitySet_Add "Essence of Air" AirPetSpell
    /call AbilitySet_Add "Child of Wind" AirPetSpell
    /call AbilitySet_Add "Ward of Xegony" AirPetSpell
    /call AbilitySet_Add "Greater Vocaration: Air" AirPetSpell
    /call AbilitySet_Add "Vocarate: Air" AirPetSpell
    /call AbilitySet_Add "Greater Conjuration: Air" AirPetSpell
    /call AbilitySet_Add "Conjuration: Air" AirPetSpell
    /call AbilitySet_Add "Lesser Conjuration: Air" AirPetSpell
    /call AbilitySet_Add "Minor Conjuration: Air" AirPetSpell
    /call AbilitySet_Add "Greater Summoning: Air" AirPetSpell
    /call AbilitySet_Add "Summoning: Air" AirPetSpell
    /call AbilitySet_Add "Lesser Summoning: Air" AirPetSpell
    /call AbilitySet_Add "Minor Summoning: Air" AirPetSpell
    /call AbilitySet_Add "Elemental: Air" AirPetSpell
    /call AbilitySet_Add "Elementaling: Air" AirPetSpell
    /call AbilitySet_Add "Elementalkin: Air" AirPetSpell
    /call AbilitySet_ChooseOuter AirPetSpell AirPetSpell
    
|--- Fire Pet*
    /call AbilitySet_Add "Recruitment of Fire" FirePetSpell
    /call AbilitySet_Add "Conscription of Fire" FirePetSpell
    /call AbilitySet_Add "Manifestation of Fire" FirePetSpell
    /call AbilitySet_Add "Embodiment of Fire" FirePetSpell
    /call AbilitySet_Add "Convocation of Fire" FirePetSpell
    /call AbilitySet_Add "Shard of Fire" FirePetSpell
    /call AbilitySet_Add "Facet of Fire" FirePetSpell
    /call AbilitySet_Add "Construct of Fire" FirePetSpell
    /call AbilitySet_Add "Aspect of Fire" FirePetSpell
    /call AbilitySet_Add "Core of Fire" FirePetSpell
    /call AbilitySet_Add "Essence of Fire" FirePetSpell
    /call AbilitySet_Add "Child of Fire" FirePetSpell
    /call AbilitySet_Add "Child of Ro" FirePetSpell
    /call AbilitySet_Add "Greater Vocaration: Fire" FirePetSpell
    /call AbilitySet_Add "Vocarate: Fire" FirePetSpell
    /call AbilitySet_Add "Greater Conjuration: Fire" FirePetSpell
    /call AbilitySet_Add "Conjuration: Fire" FirePetSpell
    /call AbilitySet_Add "Lesser Conjuration: Fire" FirePetSpell
    /call AbilitySet_Add "Minor Conjuration: Fire" FirePetSpell
    /call AbilitySet_Add "Greater Summoning: Fire" FirePetSpell
    /call AbilitySet_Add "Summoning: Fire" FirePetSpell
    /call AbilitySet_Add "Lesser Summoning: Fire" FirePetSpell
    /call AbilitySet_Add "Minor Summoning: Fire" FirePetSpell
    /call AbilitySet_Add "Elemental: Fire" FirePetSpell
    /call AbilitySet_Add "Elementaling: Fire" FirePetSpell
    /call AbilitySet_Add "Elementalkin: Fire" FirePetSpell
    /call AbilitySet_ChooseOuter FirePetSpell FirePetSpell

|-Pet Aegis Shield Buff (Short Duration)*
    /call AbilitySet_Add "Aegis of Valorforged" AegisBuff
    /call AbilitySet_Add "Auspice of Valia" AegisBuff
    /call AbilitySet_Add "Aegis of Rumblecrush" AegisBuff
    /call AbilitySet_Add "Auspice of Kildrukaun" AegisBuff
    /call AbilitySet_Add "Aegis of Orfur" AegisBuff
    /call AbilitySet_Add "Auspice of Esianti" AegisBuff
    /call AbilitySet_Add "Aegis of Zeklor" AegisBuff
    /call AbilitySet_Add "Aegis of Japac" AegisBuff
    /call AbilitySet_Add "Auspice of Eternity" AegisBuff
    /call AbilitySet_Add "Aegis of Nefori" AegisBuff
    /call AbilitySet_Add "Auspice of Shadows" AegisBuff
    /call AbilitySet_Add "Aegis of Kildrukaun" AegisBuff
    /call AbilitySet_Add "Aegis of Calliav" AegisBuff
    /call AbilitySet_Add "Bulwark of Calliav" AegisBuff
    /call AbilitySet_Add "Protection of Calliav" AegisBuff
    /call AbilitySet_Add "Guard of Calliav" AegisBuff
    /call AbilitySet_Add "Ward of Calliav" AegisBuff
    /call AbilitySet_ChooseOuter AegisBuff AegisBuff
    
|- SelfShield
    /call AbilitySet_Add "Shield of Memories" SelfShield
    /call AbilitySet_Add "Shield of Shadow" SelfShield
    /call AbilitySet_Add "Shield of Restless Ice" SelfShield
    /call AbilitySet_Add "Shield of Scales" SelfShield
    /call AbilitySet_Add "Shield of the Pellarus" SelfShield
    /call AbilitySet_Add "Shield of the Dauntless" SelfShield
    /call AbilitySet_Add "Shield of Bronze" SelfShield
    /call AbilitySet_Add "Shield of Dreams" SelfShield
    /call AbilitySet_Add "Shield of the Void" SelfShield
    /call AbilitySet_Add "Prime Guard" SelfShield
    /call AbilitySet_Add "Prime Shielding" SelfShield
    /call AbilitySet_Add "Elemental Aura" SelfShield
    /call AbilitySet_Add "Shield of Maelin" SelfShield
    /call AbilitySet_Add "Shield of the Arcane" SelfShield
    /call AbilitySet_Add "Shield of the Magi" SelfShield
    /call AbilitySet_Add "Arch Shielding" SelfShield
    /call AbilitySet_Add "Greater Shielding" SelfShield
    /call AbilitySet_Add "Major Shielding" SelfShield
    /call AbilitySet_Add "Shielding" SelfShield
    /call AbilitySet_Add "Lesser Shielding" SelfShield
    /call AbilitySet_Add "Minor Shielding" SelfShield
    /call AbilitySet_ChooseOuter SelfShield SelfShield

|- PetBodyGuard Innate
    /call AbilitySet_Add "ValorForged Bodyguard" PetBodyGuard
    /call AbilitySet_Add "Ophiolite Bodyguard" PetBodyGuard
    /call AbilitySet_Add "Pyroxenite Bodyguard" PetBodyGuard
    /call AbilitySet_Add "Rhyolitic Bodyguard" PetBodyGuard
    /call AbilitySet_Add "Shieldstone Bodyguard" PetBodyGuard
    /call AbilitySet_Add "Groundswell Bodyguard" PetBodyGuard
    /call AbilitySet_Add "Steelbound Bodyguard" PetBodyGuard
    /call AbilitySet_Add "Tellurian Bodyguard" PetBodyGuard
    /call AbilitySet_Add "Hulking Bodyguard" PetBodyGuard
    /call AbilitySet_ChooseOuter PetBodyGuard PetBodyGuard
    
|- PetManaConv
    /call AbilitySet_Add "Valiant Symbiosis" PetManaConv
    /call AbilitySet_Add "Relentless Symbiosis" PetManaConv
    /call AbilitySet_Add "Restless Symbiosis" PetManaConv
    /call AbilitySet_Add "Burning Symbiosis" PetManaConv
    /call AbilitySet_Add "Dark Symbiosis" PetManaConv
    /call AbilitySet_Add "Phantasmal Symbiosis" PetManaConv
    /call AbilitySet_Add "Arcane Symbiosis" PetManaConv
    /call AbilitySet_Add "Spectral Symbiosis" PetManaConv
    /call AbilitySet_Add "Ethereal Symbiosis" PetManaConv
    /call AbilitySet_Add "Prime Symbiosis" PetManaConv
    /call AbilitySet_Add "Elemental Symbiosis" PetManaConv
    /call AbilitySet_Add "Elemental Simulacrum" PetManaConv
    /call AbilitySet_Add "Elemental Siphon" PetManaConv
    /call AbilitySet_Add "Elemental Draw" PetManaConv
    /call AbilitySet_ChooseOuter PetManaConv PetManaConv
    
|- PetHaste
    /call AbilitySet_Add "Burnout XVI" PetHaste
    /call AbilitySet_Add "Burnout XV" PetHaste
    /call AbilitySet_Add "Burnout XIV" PetHaste
    /call AbilitySet_Add "Burnout XIII" PetHaste
    /call AbilitySet_Add "Burnout XII" PetHaste
    /call AbilitySet_Add "Burnout XI" PetHaste
    /call AbilitySet_Add "Burnout XI" PetHaste
    /call AbilitySet_Add "Burnout IX" PetHaste
    /call AbilitySet_Add "Burnout VIII" PetHaste
    /call AbilitySet_Add "Burnout VII" PetHaste
    /call AbilitySet_Add "Burnout VI" PetHaste
    /call AbilitySet_Add "Elemental Fury" PetHaste
    /call AbilitySet_Add "Burnout V" PetHaste
    /call AbilitySet_Add "Burnout IV" PetHaste
    /call AbilitySet_Add "Elemental Empathy" PetHaste
    /call AbilitySet_Add "Burnout III" PetHaste
    /call AbilitySet_Add "Burnout II" PetHaste
    /call AbilitySet_Add "Burnout" PetHaste
    /call AbilitySet_ChooseOuter PetHaste PetHaste
    
|- PetIceFlame
    /call AbilitySet_Add "IceFlame Palisade" PetIceFlame
    /call AbilitySet_Add "Iceflame Barricade " PetIceFlame
    /call AbilitySet_Add "Iceflame Rampart" PetIceFlame
    /call AbilitySet_Add "Iceflame Keep" PetIceFlame
    /call AbilitySet_Add "Iceflame Armaments" PetIceFlame
    /call AbilitySet_Add "Iceflame Eminence" PetIceFlame
    /call AbilitySet_Add "Iceflame Armor" PetIceFlame
    /call AbilitySet_Add "Iceflame Ward" PetIceFlame
    /call AbilitySet_Add "Iceflame Efflux" PetIceFlame
    /call AbilitySet_Add "Iceflame Tenement" PetIceFlame
    /call AbilitySet_Add "Iceflame Body" PetIceFlame
    /call AbilitySet_Add "Iceflame Guard" PetIceFlame
    /call AbilitySet_ChooseOuter PetIceFlame PetIceFlame
   
|- AllianceBuff Spell
    /call AbilitySet_Add "Firebound Conjunction" AllianceBuff
    /call AbilitySet_Add "Firebound Coalition" AllianceBuff
    /call AbilitySet_Add "Firebound Covenant" AllianceBuff
    /call AbilitySet_Add "Firebound Alliance" AllianceBuff
    /call AbilitySet_ChooseOuter AllianceBuff AllianceBuff
    
|- FireShroud Defensive Proc 3-6m Buff
    /call AbilitySet_Add "Igneous Veil" FireShroud
    /call AbilitySet_Add "Volcanic Veil" FireShroud
    /call AbilitySet_Add "Exothermic Veil" FireShroud
    /call AbilitySet_Add "Skyfire Veil" FireShroud
    /call AbilitySet_Add "Magmatic Veil" FireShroud
    /call AbilitySet_Add "Molten Veil" FireShroud
    /call AbilitySet_Add "Burning Veil" FireShroud
    /call AbilitySet_Add "Burning Pyroshroud" FireShroud
    /call AbilitySet_Add "Burning Brimbody" FireShroud
    /call AbilitySet_Add "Burning Aura" FireShroud
    /call AbilitySet_ChooseOuter FireShroud FireShroud
    
|- MeleeGuard
    /call AbilitySet_Add "Shield of Inescapability" MeleeGuard
    /call AbilitySet_Add "Shield of Inevitability" MeleeGuard
    /call AbilitySet_Add "Shield of Destiny" MeleeGuard
    /call AbilitySet_Add "Shield of Order" MeleeGuard
    /call AbilitySet_Add "Shield of Consequence" MeleeGuard
    /call AbilitySet_Add "Shield of Fate" MeleeGuard
    /call AbilitySet_ChooseOuter MeleeGuard MeleeGuard
    
|- ShortDurDmgShield - Use at the start of the DPS loop
    /call AbilitySet_Add "Boiling Skin" ShortDurDmgShield
    /call AbilitySet_Add "Scorching Skin" ShortDurDmgShield
    /call AbilitySet_Add "Burning Skin" ShortDurDmgShield
    /call AbilitySet_Add "Blistering Skin" ShortDurDmgShield
    /call AbilitySet_Add "Coronal Skin" ShortDurDmgShield
    /call AbilitySet_Add "Infernal Skin" ShortDurDmgShield
    /call AbilitySet_Add "Molten Skin" ShortDurDmgShield
    /call AbilitySet_Add "Blazing Skin" ShortDurDmgShield
    /call AbilitySet_Add "Torrid Skin" ShortDurDmgShield
    /call AbilitySet_Add "Brimstoneskin" ShortDurDmgShield
    /call AbilitySet_Add "Searing Skin" ShortDurDmgShield
    /call AbilitySet_Add "Scorching Skin" ShortDurDmgShield
    /call AbilitySet_Add "Ancient: Veil of Pyrilonus" ShortDurDmgShield
    /call AbilitySet_Add "Pyrilen Skin" ShortDurDmgShield
    /call AbilitySet_ChooseOuter ShortDurDmgShield ShortDurDmgShield

| - Single target Dmg Shields For Pets
    /call AbilitySet_Add "Forgefire Coat"         SingleDS  
    /call AbilitySet_Add "Emberweave Coat"        SingleDS  
    /call AbilitySet_Add "Igneous Coat"           SingleDS
    /call AbilitySet_Add "Inferno Coat"           SingleDS
    /call AbilitySet_Add "Flameweave Coat"        SingleDS
    /call AbilitySet_Add "Flameskin"              SingleDS
    /call AbilitySet_Add "Embercoat"              SingleDS
    /call AbilitySet_Add "Dreamfire Coat"         SingleDS
    /call AbilitySet_Add "Brimstoneskin"          SingleDS
    /call AbilitySet_Add "Lavaskin"               SingleDS
    /call AbilitySet_Add "Magmaskin"              SingleDS
    /call AbilitySet_Add "Fireskin"               SingleDS
    /call AbilitySet_Add "FlameShield of Ro"      SingleDS
    /call AbilitySet_Add "Cadeau of Flame"        SingleDS 
    /call AbilitySet_Add "Shield of Lava"         SingleDS
    /call AbilitySet_Add "Barrier of Combustion"  SingleDS
    /call AbilitySet_Add "Inferno Shield"         SingleDS
    /call AbilitySet_Add "Shield of Flame"        SingleDS
    /call AbilitySet_Add "Shield of Fire"         SingleDS
    /call AbilitySet_ChooseOuter SingleDS SingleDS

|- LongDurDmgShield - Preferring group buffs for ease. Included all Single target Now as well.
    /call AbilitySet_Add "Circle of Forgefire Coat" LongDurDmgShield
    /call AbilitySet_Add "Forgefire Coat" LongDurDmgShield
    /call AbilitySet_Add "Circle of Emberweave Coat" LongDurDmgShield
    /call AbilitySet_Add "Emberweave Coat" LongDurDmgShield
    /call AbilitySet_Add "Circle of Igneous Skin" LongDurDmgShield
    /call AbilitySet_Add "Igneous Coat" LongDurDmgShield
    /call AbilitySet_Add "Circle of the Inferno" LongDurDmgShield
    /call AbilitySet_Add "Inferno Coat" LongDurDmgShield
    /call AbilitySet_Add "Circle of Flameweaving" LongDurDmgShield
    /call AbilitySet_Add "Flameweave Coat" LongDurDmgShield
    /call AbilitySet_Add "Circle of Flameskin" LongDurDmgShield
    /call AbilitySet_Add "Flameskin" LongDurDmgShield
    /call AbilitySet_Add "Circle of Embers" LongDurDmgShield
    /call AbilitySet_Add "Embercoat" LongDurDmgShield
    /call AbilitySet_Add "Circle of Dreamfire" LongDurDmgShield
    /call AbilitySet_Add "Dreamfire Coat" LongDurDmgShield
    /call AbilitySet_Add "Circle of Brimstoneskin" LongDurDmgShield
    /call AbilitySet_Add "Brimstoneskin" LongDurDmgShield
    /call AbilitySet_Add "Circle of Lavaskin" LongDurDmgShield
    /call AbilitySet_Add "Lavaskin" LongDurDmgShield
    /call AbilitySet_Add "Circle of Magmaskin" LongDurDmgShield
    /call AbilitySet_Add "Magmaskin" LongDurDmgShield
    /call AbilitySet_Add "Circle of Fireskin" LongDurDmgShield
    /call AbilitySet_Add "Fireskin" LongDurDmgShield
    /call AbilitySet_Add "Maelstrom of Ro" LongDurDmgShield
    /call AbilitySet_Add "FlameShield of Ro" LongDurDmgShield
    /call AbilitySet_Add "Aegis of Ro" LongDurDmgShield
    /call AbilitySet_Add "Cadeau of Flame" LongDurDmgShield
    /call AbilitySet_Add "Boon of Immolation" LongDurDmgShield
    /call AbilitySet_Add "Shield of Lava" LongDurDmgShield
    /call AbilitySet_Add "Barrier of Combustion" LongDurDmgShield
    /call AbilitySet_Add "Inferno Shield" LongDurDmgShield
    /call AbilitySet_Add "Shield of Flame" LongDurDmgShield
    /call AbilitySet_Add "Shield of Fire" LongDurDmgShield
    /call AbilitySet_ChooseOuter LongDurDmgShield LongDurDmgShield
    
|- ManaRegenBuff - LVL58 (Transon's Phantasmal Protection) and up to avoid reagent usage
    /call AbilitySet_Add "Courageous Guardian" ManaRegenBuff
    /call AbilitySet_Add "Relentless Guardian" ManaRegenBuff
    /call AbilitySet_Add "Restless Guardian" ManaRegenBuff    
    /call AbilitySet_Add "Burning Guardian" ManaRegenBuff
    /call AbilitySet_Add "Praetorian Guardian" ManaRegenBuff
    /call AbilitySet_Add "Phantasmal Guardian" ManaRegenBuff
    /call AbilitySet_Add "Splendrous Guardian" ManaRegenBuff
    /call AbilitySet_Add "Cognitive Guardian" ManaRegenBuff
    /call AbilitySet_Add "Empyrean Guardian" ManaRegenBuff
    /call AbilitySet_Add "Eidolic Guardian" ManaRegenBuff
    /call AbilitySet_Add "Phantasmal Warden" ManaRegenBuff
    /call AbilitySet_Add "Phantom Shield" ManaRegenBuff
    /call AbilitySet_Add "Xegony's Phantasmal Guard" ManaRegenBuff
    /call AbilitySet_Add "Transon's Phantasmal Protection" ManaRegenBuff
    /call AbilitySet_ChooseOuter ManaRegenBuff ManaRegenBuff
    
|- PetArmorSummon >=LVL71
    /call AbilitySet_Add "Grant The Alloy's Plate" PetArmorSummon
    /call AbilitySet_Add "Grant the Centien's Plate" PetArmorSummon
    /call AbilitySet_Add "Grant Ocoenydd's Plate" PetArmorSummon
    /call AbilitySet_Add "Grant Wirn's Plate" PetArmorSummon
    /call AbilitySet_Add "Grant Thassis' Plate" PetArmorSummon
    /call AbilitySet_Add "Grant Frightforged Plate" PetArmorSummon 
    /call AbilitySet_Add "Grant Manaforged Plate" PetArmorSummon
    /call AbilitySet_Add "Grant Spectral Plate" PetArmorSummon
    /call AbilitySet_Add "Summon Plate of the Prime" PetArmorSummon
    /call AbilitySet_Add "Summon Plate of the Elements" PetArmorSummon
    /call AbilitySet_ChooseOuter PetArmorSummon PetArmorSummon
    
|- PetWeaponSummon >=LVL73
    /call AbilitySet_Add "Grant Goliath's Armaments" PetWeaponSummon
    /call AbilitySet_Add "Grant Shak Dathor's Armaments" PetWeaponSummon
    /call AbilitySet_Add "Grant Yalrek's Armaments" PetWeaponSummon
    /call AbilitySet_Add "Grant Wirn's Armaments" PetWeaponSummon
    /call AbilitySet_Add "Grant Thassis' Armaments" PetWeaponSummon
    /call AbilitySet_Add "Grant Frightforged Armaments" PetWeaponSummon
    /call AbilitySet_Add "Grant Manaforged Armaments" PetWeaponSummon
    /call AbilitySet_Add "Grant Spectral Armaments" PetWeaponSummon
    /call AbilitySet_Add "Summon Ethereal Armaments" PetWeaponSummon
    /call AbilitySet_Add "Summon Prime Armaments" PetWeaponSummon
    /call AbilitySet_Add "Summon Elemental Armaments" PetWeaponSummon
    /call AbilitySet_ChooseOuter PetWeaponSummon PetWeaponSummon

|- PetHeirloomSummon Level 76+
    /call AbilitySet_Add "Grant Ankexfen's Heirlooms" PetHeirloomSummon
    /call AbilitySet_Add "Grant the Diabo's Heirlooms" PetHeirloomSummon
    /call AbilitySet_Add "Summon Nastel's Heirlooms" PetHeirloomSummon
    /call AbilitySet_Add "Summon Zabella's Heirlooms" PetHeirloomSummon
    /call AbilitySet_Add "Grant Enibik's Heirlooms" PetHeirloomSummon
    /call AbilitySet_Add "Grant Atleris' Heirlooms" PetHeirloomSummon
    /call AbilitySet_Add "Grant Nint's Heirlooms" PetHeirloomSummon
    /call AbilitySet_Add "Grant Calix's Heirlooms" PetHeirloomSummon
    /call AbilitySet_Add "Grant Ioulin's Heirlooms" PetHeirloomSummon
    /call AbilitySet_Add "Grant Crystasia's Heirlooms" PetHeirloomSummon
    /call AbilitySet_ChooseOuter PetHeirloomSummon PetHeirloomSummon    
    
|- IceOrbSummon
     /call AbilitySet_Add "Grant Frostbound Paradox" IceOrbSummon
     /call AbilitySet_Add "Grant Icebound Paradox" IceOrbSummon
     /call AbilitySet_Add "Grant Frostrift Paradox" IceOrbSummon
     /call AbilitySet_Add "Grant Glacial Paradox" IceOrbSummon
     /call AbilitySet_Add "Summon Frigid Paradox" IceOrbSummon
     /call AbilitySet_Add "Summon Gelid Paradox" IceOrbSummon
     /call AbilitySet_Add "Summon Wintry Paradox" IceOrbSummon
     /call AbilitySet_ChooseOuter IceOrbSummon IceOrbSummon
     /varset IceOrbItem ${FindItem[${Spell[${IceOrbSummon}].Base[1]}].Name}
     
|- FireOrbSummon
    /call AbilitySet_Add "Summon Molten Komatiite Orb" FireOrbSummon
    /call AbilitySet_Add "Summon Firebound Orb" FireOrbSummon
    /call AbilitySet_Add "Summon Blazing Orb" FireOrbSummon
    /call AbilitySet_Add "Summon: Molten Orb" FireOrbSummon
    /call AbilitySet_Add "Summon: Lava Orb" FireOrbSummon
    /call AbilitySet_ChooseOuter FireOrbSummon FireOrbSummon
    /varset FireOrbItem ${FindItem[${Spell[${FireOrbSummon}].Base[1]}].Name}
|- EarthPetItemSummon
     /call AbilitySet_Add "Summon Valorous Servant" EarthPetItemSummon
     /call AbilitySet_Add "Summon Forbearing Servant" EarthPetItemSummon
     /call AbilitySet_Add "Summon Imperative Servant" EarthPetItemSummon
     /call AbilitySet_Add "Summon Insurgent Servant" EarthPetItemSummon
     /call AbilitySet_Add "Summon Mutinous Servant" EarthPetItemSummon
     /call AbilitySet_Add "Summon Imperious Servant" EarthPetItemSummon
     /call AbilitySet_Add "Summon Exigent Servant" EarthPetItemSummon
     /call AbilitySet_ChooseOuter EarthPetItemSummon EarthPetItemSummon
     /varset EarthPetItem ${FindItem[${Spell[${EarthPetItemSummon}].Base[1]}].Name}
|- FirePetItemSummon
    /call AbilitySet_Add "Summon Valorous Minion" FirePetItemSummon
    /call AbilitySet_Add "Summon Forbearing Minion" FirePetItemSummon
    /call AbilitySet_Add "Summon Imperative Minion" FirePetItemSummon
    /call AbilitySet_Add "Summon Insurgent Minion" FirePetItemSummon
    /call AbilitySet_Add "Summon Mutinous Minion" FirePetItemSummon
    /call AbilitySet_Add "Summon Imperious Minion" FirePetItemSummon
    /call AbilitySet_Add "Summon Exigent Minion" FirePetItemSummon
    /call AbilitySet_ChooseOuter FirePetItemSummon FirePetItemSummon
    /varset FirePetItem ${FindItem[${Spell[${FirePetItemSummon}].Base[1]}].Name}

|- ManaRodSummon - Focuses on group mana rod summon for ease. _ 
|  - no TOL spell?
    /call AbilitySet_Add "Mass Dark Transvergence" ManaRodSummon
    /call AbilitySet_Add "Mass Dark Transvergence" ManaRodSummon
    /call AbilitySet_Add "Mass Arcane Transvergence" ManaRodSummon
    /call AbilitySet_Add "Mass Spectral Transvergence" ManaRodSummon
    /call AbilitySet_Add "Mass Ethereal Transvergence" ManaRodSummon
    /call AbilitySet_Add "Mass Prime Transvergence" ManaRodSummon
    /call AbilitySet_Add "Mass Elemental Transvergence" ManaRodSummon
    /call AbilitySet_Add "Mass Mystical Transvergence" ManaRodSummon
    /call AbilitySet_Add "Modulating Rod" ManaRodSummon
    /call AbilitySet_ChooseOuter ManaRodSummon ManaRodSummon

|- SelfManaRodSummon - Focuses on self mana rod summon separate from other timers. >95
    /call AbilitySet_Add "Rod of Courageous Modulation" SelfManaRodSummon
    /call AbilitySet_Add "Sickle of Umbral Modulation" SelfManaRodSummon
    /call AbilitySet_Add "Wand of Frozen Modulation" SelfManaRodSummon
    /call AbilitySet_Add "Wand of Burning Modulation" SelfManaRodSummon
    /call AbilitySet_Add "Wand of Dark Modulation" SelfManaRodSummon
    /call AbilitySet_Add "Wand of Phantasmal Modulation" SelfManaRodSummon
    /call AbilitySet_ChooseOuter SelfManaRodSummon SelfManaRodSummon
    /varset SelfModRod ${FindItem[${Spell[${SelfManaRodSummon}].Base[1]}].Name}

|- GatherMana line
    /call AbilitySet_Add "Gather Zeal" GatherMana
    /call AbilitySet_Add "Gather Vigor" GatherMana
    /call AbilitySet_Add "Gather Potency" GatherMana
    /call AbilitySet_Add "Gather Capability" GatherMana
    /call AbilitySet_Add "Gather Magnitude" GatherMana
    /call AbilitySet_Add "Gather Capacity" GatherMana
    /call AbilitySet_Add "Gather Potential" GatherMana
    /call AbilitySet_ChooseOuter GatherMana GatherMana
    
|- PetManaNuke
    /call AbilitySet_Add "Thaumatize Pet" PetManaNuke
    /call AbilitySet_ChooseOuter PetManaNuke PetManaNuke

|- ShortDuration DS (Slot 4)
    /call AbilitySet_Add "Surge of Shadow" SurgeDS
    /call AbilitySet_Add "Surge of Arcanum" SurgeDS
    /call AbilitySet_Add "Surge of Shadowflares" SurgeDS
    /call AbilitySet_Add "Surge of Thaumacretion" SurgeDS
    /call AbilitySet_ChooseOuter SurgeDS1 SurgeDS 
    /call AbilitySet_ChooseOuter SurgeDS2 SurgeDS "${SurgeDS1}"

|- Chat Beg Setup Example
    |- This adds call of the hero AA to the MagBegs object. It'll cast on the sender of the chat text message and will also cast (TRUE condition)
    /call ChatBegList_Add MAGBegs cothme AA "Call of the Hero" sender TRUE
    /call ChatBegList_Add MAGBegs RodMe AA "Summon Modulation Shard" sender TRUE
    
    |- target_id is available to determine the id of the message sender. Assume's the senders pet is nearby
    |- the sender.
    /call ChatBegList_Add MAGBegs shroudpet Spell "${FireShroud}" senderpet ${Parse[0,"( ${Spawn[id ${target_id}].Distance < 100} )"]}

/return
Sub Mag_Itemvars
    /varset FireOrbItem ${FindItem[${Spell[${FireOrbSummon}].Base[1]}].Name}
    /varset EarthPetItem ${FindItem[${Spell[${EarthPetItemSummon}].Base[1]}].Name}
    /varset FirePetItem ${FindItem[${Spell[${FirePetItemSummon}].Base[1]}].Name}
    /varset SelfModRod ${FindItem[${Spell[${SelfManaRodSummon}].Base[1]}].Name}
    /varset IceOrbItem ${FindItem[${Spell[${IceOrbSummon}].Base[1]}].Name} 
/return

Sub MAG_ModeConfigMODEFIRE
    | - Mage One Mode For Live Working on pet tanking and Magic Mode Working Via Toggles Instead of Class Modes
    /varset IsHealing TRUE
    /call Mag_Itemvars
    /pet taunt off
    /echo - Welcome to RGMercs Mage One Mage ! - /rg DoMagicnuke 1 will Toggle using magic Instead
    /echo - Fire is the Better DPS Mode and Ideal Magic is for Niche Situations.
    
    /if (${DoMagicNuke[SETTINGVAL]}) {
    |- Magic Spell Bar
        |- Spell1
        /varset Spell1 ${MagicNuke1}
        |- Spell2
        /varset Spell2 ${MagicNuke2}      
        |- Spell3
        /if ( ${Me.Level} >= 70 ) {
            /varset Spell3 ${SwarmPet}
        } else {
        }
        |- Spell4
        /if ( ${Me.Level} >= 98 ) {
            /varset Spell4 ${MagicBoltNuke1}
        } else {
        }
        |- Spell5
        /if ( ${Me.Level} >= 103 ) {
            /varset Spell5 ${MagicBoltNuke2}
        } 
        | - Spell 6
        /if ( ${Me.Level} >= 100 ) {
            /varset Spell5 ${MaloNuke}
        } 
        
    } else {
    |- Fire Spell Bar
        /if ( ${Me.Level} >= 70 ) {
            /varset Spell1 ${SpearNuke}
        } else {
            /varset Spell1 ${FireNuke1}
        }
        
        |- Spell2
        /if ( ${Me.Level} >= 69 ) {
            /varset Spell2 ${ChaoticNuke}
        } else {
            /varset Spell2 ${FireNuke2}
        }
        
        |- Spell3
        /if ( ${Me.Level} >= 70 ) {
            /varset Spell3 ${SwarmPet}
        } else {
            /varset Spell3 ${FireNuke1}
        }
        
        |- Spell4
        /if ( ${Me.Level} >= 75 ) {
            /varset Spell4 ${VolleyNuke}
        } else {
            /varset Spell4 ${MagicNuke1}
        }

        |- Spell5
        /if ( ${Me.Level} >= 75 ) {
            /varset Spell5 ${SpearNuke2}
        } else {
            /varset Spell5 ${MagicNuke2}
        }
        /if ( ${Me.Level} >= 75  && (${Me.AltAbility[Malaise].ID} || !${DoMalo[SETTINGVAL]}) ) {
            /if ( ${DoAlliance[SETTINGVAL]} ) {
                /varset Spell6 ${AllianceBuff}
            } else {
                /varset Spell6 ${FireOrbSummon}
            } else {
            /varset Spell6 ${MaloDebuff}
            }
        }
    }    

|- Below Spells Shared By Both bars!        
|- Spell7 - We'll keep Malo on the bar for F2P players if we're casting malo
|- Since Alliance is Fire based It is Not Used or In use In magic Mode.
    /varset Spell7 ${SelfManaRodSummon}
    /varset Spell8 ${PetHealSpell}
    /varset Spell9  ${DichoSpell}
    /varset Spell10 ${TwinCast}
    /varset Spell11 ${PetManaNuke}
    /varset Spell12 ${GatherMana}

    /call MAG_DefaultDownTimeRotationConfig MAG_Downtime_MODEFIRE_Rotation
    /call MAG_DefaultDebuffRotationConfig MAG_Debuff_MODEFIRE_Rotation
    /call MAG_DefaultBuffGroupConfig
    /call Heal_AddHealPoint ${PetHealPct[SETTINGVAL]}
    /call Heal_AddSpell ${PetHealPct[SETTINGVAL]} "${PetHealSpell}" ${Parse[0,"( ${Me.Pet.ID} && ${target_id} == ${Me.Pet.ID} )"]}

    |- The order in which spells are added to a Rotation Map are added is the order in which they are cast
    |- assuming that every condition is met. Due to a bug in mq2collections, make sure there are no commas
    |- within the condition statements -- this means no Select[], ${SubCall[arg1,arg2]}, or similar until
    |- typepun fixes the comma bug. The AddToRotation function also will avoid adding null
    |- spell variables so you shouldn't have to worry, for example, of swarmpet or
    |- spear nuke not working on lower level players
    
    |- Below you'll see examples of the new ${Parse[#,string]} TLO
    |- from knightly. This is similar to the NoParse command as the goal
    |- is to make sure our conditions are not parsed until they are finally used
    |- in our rotation evaluation. These examples will be explained as necessary

    |- Adding Combat recasting of pet
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation "/call MAG_PetManagement_Routine" Command ${Parse[0,"( !${Me.Pet.ID}  && ${DoPet[SETTINGVAL]} && ${PocketPet})"]} 
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${SelfModRod}" Item ${Parse[0, "( ${FindItemCount[${SelfModRod}]} == 1 && ${Me.PctMana}<=${ModRodManaPct[SETTINGVAL]} && ${Me.PctHPs}>=60 )"]}
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${PetTypeName}" Spell ${Parse[0,"( ${FindItemCount[Malachite]} > 0 && !${Me.Pet.ID} && ${DoPet[SETTINGVAL]} )"]}    

    |- Here is an example of telling the parser to only make one pass so it resolves ${Me.Name} and not ${Spawn[]}
    |- We do this to reduce the load on the parser in the DPS loop because ${Me.Name} is not a situational condition,
    |- i.e., our name will not change. ${Spawn[]} however is situational and could be different every timer
    |-  we check so we want that to be parsed in our DPS rotation.
    | - Mage Twincast Rotation - Conditinally controlled to allow for better dps in Twincasts
     
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation  "${VolleyNuke}"     Spell TRUE
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation  "${SwarmPet}"       Spell TRUE
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation  "${ChaoticNuke}"    Spell ${Parse[0,"( !${Me.Buff[Improved Twincast].ID} )"]}
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation  "Force of Elements" AA    ${Parse[0,"(${DoForce[SETTINGVAL]} )"]}
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation  "${SpearNuke}"      Spell TRUE
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation  "${SpearNuke2}"     Spell ${Parse[0,"( BURNCHECK )"]}
    
    |- Should be in the Main util Under Click ModRods.
    |- Here's an example of how to handle low level rotations with the AddtoRotations
    |- function and the Ordered_Rotation object.
    /if (${Me.Level} < 70) {
        /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${FireNuke1}"     Spell TRUE
        /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${FireNuke2}"     Spell TRUE
        /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${FireBoltNuke}"  Spell TRUE
        /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${MagicNuke1}"    Spell TRUE
        /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${MagicNuke2}"    Spell TRUE
        } else {
            /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${FireNuke1}"   Spell TRUE
        }   
   
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${FireOrbItem}"      Item ${Parse[0,"( ${FindItemCount[${Spell[${FireOrbSummon}].Base[1]}]} == 1) "]}
 | - The Grant Frost Spell was removed from our rotation due to its Ineffectiveness No ability to Cast Focus or crit with it for mages.
 |   /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${IceOrbItem}"      Item ${Parse[0,"( ${FindItemCount[${Spell[${IceOrbSummon}].Base[1]}]} == 1) "]}
 | - Temporarily Blocking Force of Elements to Free up rotation speed
 |   /call AddToRotation MAG_DPS_MODEFIRE_Rotation "Force of Elements"   AA TRUE
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation "Turn Summoned"       AA ${Parse[0, "(${Target.Body.Name.Equal[Undead Pet]})"]}
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${PetManaNuke}"      Spell ${Parse[0, "( ${Me.PctMana}<=90 && !${Me.Buff[Thaumatize Pet Mana Regen].ID} )"]}
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${TwinCast}"         Spell ${Parse[0, "( SELFBUFFCHECK && !${Me.Buff[Improved Twincast].ID} )"]}
    /call AddToRotation MAG_DPS_MODEFIRE_Rotation "${AllianceBuff}"     Spell  ${Parse[0, "( ${Target.Named} && !${Target.Buff[${Spell[${AllianceBuff}].ID}]} && ${DoAlliance[SETTINGVAL]} && ${CanAlliance} )"]}
   

    |- Debuffs - Moved to Universal Config for all Modes.
    |- BurnAA Rotation
    /call AddToRotation MAG_Burn_MODEFIRE_Rotation "${FindItem[${Spell[${EarthPetItemSummon}].Base[1]}].Name}" Item TRUE
    /call AddToRotation MAG_Burn_MODEFIRE_Rotation "${FindItem[${Spell[${FirePetItemSummon}].Base[1]}].Name}" Item TRUE
    /call AddToRotation MAG_Burn_MODEFIRE_Rotation "${FindItem[${Me.Inventory[Chest].Name}]}" Item ${Parse[0,"( ${Spell[${FindItem[${Me.Inventory[Chest].Name}].Spell}].Stacks} && (!${FindItem[${Me.Inventory[Chest].Name}].TimerReady}) )"]}
    /call AddToRotation MAG_Burn_MODEFIRE_Rotation "${AllianceBuff}" Spell  ${Parse[0, "( ${Target.Named} && !${Target.Buff[${Spell[${AllianceBuff}].ID}]} && ${DoAlliance[SETTINGVAL]} && ${CanAlliance} )"]}
    /call AddToRotation MAG_Burn_MODEFIRE_Rotation "Companion's Fury" AA TRUE
    /call AddToRotation MAG_Burn_MODEFIRE_Rotation "Host of the Elements" AA TRUE
    /call AddToRotation MAG_Burn_MODEFIRE_Rotation "Spire of Elements"  AA TRUE
    /call AddToRotation MAG_Burn_MODEFIRE_Rotation "Heart of Skyfire" AA TRUE
|   /call AddToRotation MAG_Burn_MODEFIRE_Rotation "Thaumaturge's Focus" AA TRUE
    /call AddToRotation MAG_Burn_MODEFIRE_Rotation "Focus of Arcanum" AA TRUE
    /call AddToRotation MAG_Burn_MODEFIRE_Rotation "Improved Twincast" AA TRUE
    /call AddToRotation MAG_Burn_MODEFIRE_Rotation "Servant of Ro" AA TRUE

/return

Sub MAG_ModeConfigMODEPETTANK
    /varset IsHealing TRUE
    /varset IsTanking TRUE
    
    /pet taunt on
    /pet resume on

    |- Spell1 -4
    /if ( ${Me.Level} <= 69 ) {
        /varset Spell1 ${FireNuke1}
        /varset Spell2 ${FireBoltNuke}
        /varset Spell3 ${FireNuke2}
        /varset Spell4 ${LongDurDmgShield}
    } else {
        /varset Spell1 ${SpearNuke}
        /varset Spell2 ${SwarmPet}
        /varset Spell3 ${ChaoticNuke}
        /varset Spell4 ${VolleyNuke}
    }
    |- Spell2
    /if ( ${Me.Level} <= 69 ) {
        /varset Spell1 ${FireBoltNuke}
    } else {
        /varset Spell1 ${SwarmPet}
    }
    
    |- Spell3
    /if ( ${Me.Level} <= 69 ) {
        /varset Spell3 ${FireNuke2}
    } else {
    }

    |- Spell4
    /if ( ${Me.Level} <= 69 ) {
        /varset Spell4 ${LongDurDmgShield}
    } else /if ( (${Me.Level} >= 70 ) && (${Me.Level} <= 72 ) ) {
        /varset Spell4 ${FireNuke2}
    } else /if ( ${Me.Level} >= 73 ) {
        /varset Spell4 ${PetStanceSpell}
    }

    |- Spell6 - We'll keep Malo on the bar for F2P players if we're casting malo
    /varset Spell5 ${PetHealSpell}

    |- Spell7
    /if ( ${Me.Level} <= 77 ) {
        /varset Spell6 ${ManaRodSummon}
    } else {
        /varset Spell6 ${PetPromisedSpell}
    }

    |- Spell7
    /varset Spell7 ${AirPetSpell}

    |- Spell8
    /if ( ${spellmisc} > 8 ) {
        /varset Spell8 ${ShortDurDmgShield}
    }

    |- Spell9
    /if ( ( ${spellmisc} > 9 ) && ( ${Me.Level} < 90 ) ) {
        /varset Spell9 ${FireShroud}
    } else {
        /varset Spell9 ${GatherMana}
    }

    |- Spell10
    /if ( ${spellmisc} > 10 ) {
        /varset Spell10 ${PetManaNuke}
    }

    |- Spell11
    /if ( ${spellmisc} > 11 ) {
        /varset Spell11 ${SurgeDS1}
    }

    |- Spell12
    /if ( ${spellmisc} > 12 ) {
        /varset Spell12 ${SurgeDS2}
    }

    |-
    |-  Check spell list (internal note)
    |-

    /call Heal_AddHealPoint ${PetHealPct[SETTINGVAL]}
    /call Heal_AddSpell ${PetHealPct[SETTINGVAL]} "${PetHealSpell}" ${Parse[0,"( ${Me.Pet.ID} && ${target_id} == ${Me.Pet.ID} )"]}
    /call MAG_DefaultBuffGroupConfig
    /call MAG_DefaultDownTimeRotationConfig MAG_Downtime_MODEPETTANK_Rotation
    /call MAG_DefaultDebuffRotationConfig MAG_Debuff_MODEPETTANK_Rotation


    |- The order in which spells are added to a Rotation Map are added is the order in which they are cast
    |- assuming that every condition is met. Due to a bug in mq2collections, make sure there are no commas
    |- within the condition statements -- this means no Select[], ${SubCall[arg1,arg2]}, or similar until
    |- typepun fixes the comma bug. The AddToRotation function also will avoid adding null
    |- spell variables so you shouldn't have to worry, for example, of swarmpet or
    |- spear nuke not working on lower level players
    
    |- Below you'll see examples of the new ${Parse[#,string]} TLO
    |- from knightly. This is similar to the NoParse command as the goal
    |- is to make sure our conditions are not parsed until they are finally used
    |- in our rotation evaluation. These examples will be explained as necessary

    |- Here is an example of telling the parser to only make one pass so it resolves ${Me.Name} and not ${Spawn[]}
    |- We do this to reduce the load on the parser in the DPS loop because ${Me.Name} is not a situational condition,
    |- i.e., our name will not change. ${Spawn[]} however is situational and could be different every timer
    |-  we check so we want that to be parsed in our DPS rotation. 

    /if ( ${DoOOWRobe[SETTINGVAL]} == 1) {
        /if (${FindItemCount[Runemaster's Robe]}) /varset OowRobeName Runemaster's Robe
        /if (${FindItemCount[Glyphwielder's Tunic of the Summoner]}) /varset OowRobeName Glyphwielder's Tunic of the Summoner
    }

    |- Pet Defensive type spells (Mitigation, Damage Shield) These are spells that require the pet to be targeted.
    /if (${IsTanking}) {
        /call AddToRotation MAG_DPSPET_MODEPETTANK_Rotation "${OowRobeName}"          Item  ${Parse[0,"( ${DoOOWRobe[SETTINGVAL]} && !${Me.PetBuff[${PetStanceSpell}]} )"]}
        /call AddToRotation MAG_DPSPET_MODEPETTANK_Rotation "${PetStanceSpell}"       Spell ${Parse[0,"( !${Me.PetBuff[${PetStanceSpell}]} && !${Me.PetBuff[${Spell[${OowRobeName}].Base[1]}].Name} )"]}
        /call AddToRotation MAG_DPSPET_MODEPETTANK_Rotation "${SurgeDS1}"          Spell ${Parse[0,"( !${Me.PetBuff[${SurgeDS1}]} && !${Me.PetBuff[${SurgeDS2}]} )"]}
        /call AddToRotation MAG_DPSPET_MODEPETTANK_Rotation "${SurgeDS2}"          Spell ${Parse[0,"( !${Me.PetBuff[${SurgeDS1}]} && !${Me.PetBuff[${SurgeDS2}]} )"]}
        /call AddToRotation MAG_DPSPET_MODEPETTANK_Rotation "${ShortDurDmgShield}"    Spell ${Parse[0,"( !${Me.PetBuff[${ShortDurDmgShield}]} )"]}
        /call AddToRotation MAG_DPSPET_MODEPETTANK_Rotation "${FireShroud}"           Spell ${Parse[0,"( !${Me.PetBuff[${PetPromisedSpell}]} )"]}
    }

    |- Offensive Spells
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${PetPromisedSpell}"     Spell ${Parse[0, "( !${Me.PetBuff[${PetPromisedSpell}]} && (${Me.Pet.PctHPs} <= 95 )  )" ]}
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${SwarmPet}"      Spell TRUE

    |- Adding Combat recasting of pet - in pettank mode, haste and iceflame are important! After Swarm pet so agro can be maintained.
    /call AddToRotation MAG_DPSPET_MODEPETTANK_Rotation "/call MAG_PetManagement_Routine" Command ${Parse[0,"( !${Me.Pet.ID}  && ${DoPet[SETTINGVAL]} && ${PocketPet})"]} 
    /call AddToRotation MAG_DPSPET_MODEPETTANK_Rotation "${PetTypeName}" Spell ${Parse[0,"( ${FindItemCount[Malachite]} > 0 && !${Me.Pet.ID} && ${DoPet[SETTINGVAL]} )"]}    
    /call AddToRotation MAG_DPSPET_MODEPETTANK_Rotation "${PetIceFlame}" Spell ${Parse[0,"( SELFBUFFPETCHECK )"]} 
    /call AddToRotation MAG_DPSPET_MODEPETTANK_Rotation "${PetHaste}"    Spell ${Parse[0,"( SELFBUFFPETCHECK )"]}     

    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${SelfModRod}"    Item ${Parse[0, "( ${FindItemCount[${SelfModRod}]} == 1 && ${Me.PctMana}<=${ModRodManaPct[SETTINGVAL]} && ${Me.PctHPs}>=60 )"]}
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${SpearNuke}"     Spell ${Parse[0,"( ${Me.Song[Conjurer's Synergy].ID} )"]}
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${ChaoticNuke}"   Spell TRUE
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${FireBoltNuke}"  Spell TRUE
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${FireNuke1}"     Spell TRUE
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${FireNuke2}"     Spell TRUE
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${FireOrbItem}"   Item ${Parse[0,"( ${FindItemCount[${Spell[${FireOrbSummon}].Base[1]}]} == 1) "]}
|   /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${IceOrbItem}"    Item ${Parse[0,"( ${FindItemCount[${Spell[${IceOrbSummon}].Base[1]}]} == 1) "]}
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "Force of Elements" AA TRUE
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "Turn Summoned" AA ${Parse[0, "(${Target.Body.Name.Equal[Undead Pet]})"]}
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${PetManaNuke}"   Spell ${Parse[0, "( ${Me.PctMana}<=90 && ${PCSpellReady[${PetManaNuke}]} && ${Me.SpellReady[${PetManaNuke}]} )"]}
    /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${TwinCast}"   Spell ${Parse[0, "( SELFBUFFCHECK )"]}
    |- /call AddToRotation MAG_DPS_MODEPETTANK_Rotation "${FindItem[${Spell[${SelfManaRodSummon}].Base[1]}].Name}" Item ${Parse[0, "(  ${Me.PctMana} <= ${ModRodManaPct[SETTINGVAL]} && ${Me.PctHPs} >=60 )"]}

    |- Here's an example of how to handle low level rotations with the AddtoRotations
    |- function and the Ordered_Rotation object.

    |- Need to test lower leverl mage rotations
    /call AddToRotation MAG_Downtime_MODEPETTANK_Rotation "${PetStanceSpell}" Spell ${Parse[0,"( SELFBUFFPETCHECK )"]}


    |- Debuffs - Moved to Universal Config for all Modes.

    |- BurnAA Rotation
    /call AddToRotation MAG_Burn_MODEPETTANK_Rotation "${EarthPetItem}" Item ${Parse[0,"( ${FindItemCount[${Spell[${EarthPetItemSummon}].Base[1]}]} == 1) "]}
    /call AddToRotation MAG_Burn_MODEPETTANK_Rotation "${FirePetItem}" Item ${Parse[0,"( ${FindItemCount[${Spell[${FirePetItemSummon}].Base[1]}]} == 1) "]}
    /call AddToRotation MAG_Burn_MODEPETTANK_Rotation "Companion's Fury" AA TRUE
    /call AddToRotation MAG_Burn_MODEPETTANK_Rotation "Host of the Elements" AA TRUE
    /call AddToRotation MAG_Burn_MODEPETTANK_Rotation "Spire of Elements"  AA TRUE
    /call AddToRotation MAG_Burn_MODEPETTANK_Rotation "Heart of Skyfire" AA TRUE
    /call AddToRotation MAG_Burn_MODEPETTANK_Rotation "Thaumaturge's Focus" AA TRUE
    /call AddToRotation MAG_Burn_MODEPETTANK_Rotation "Focus of Arcanum" AA TRUE
    /call AddToRotation MAG_Burn_MODEPETTANK_Rotation "Improved Twincast" AA TRUE
    /call AddToRotation MAG_Burn_MODEPETTANK_Rotation "Servant of Ro" AA TRUE
/return

Sub MAG_ModeConfigMODEMAGIC
    /varset IsHealing TRUE
    /pet taunt off
    |- Spell1
    /varset Spell1 ${MagicNuke1}
    
    |- Spell2
    /if ( ${Me.Level} >= 98 ) {
        /varset Spell2 ${MagicBoltNuke1}
    } else {
        /varset Spell2 ${MagicNuke2}
    }
    
    |- Spell3
    /if ( ${Me.Level} >= 70 ) {
        /varset Spell3 ${SwarmPet}
    } else {
    }
    
    |- Spell4
    /if ( ${Me.Level} >= 103 ) {
        /varset Spell4 ${MagicBoltNuke2}
    } else {
    }

    |- Spell5
    /if ( ${Me.Level} >= 98 ) {
        /varset Spell5 ${MagicNuke2}
    } else {
    }
    
    |- Spell6 - We'll keep Malo on the bar for F2P players if we're casting malo
    /if ( ${Me.Level} >= 75  && (${Me.AltAbility[Malaise].ID} || !${DoMalo[SETTINGVAL]}) ) {
        /if ( ${DoAlliance[SETTINGVAL]} ) {
            /varset Spell6 ${AllianceBuff}
        } else {
        }
    } else {
        /varset Spell6 ${MaloDebuff}
    }

    |-
    |-  Check spell list (internal note)
    |-

    /varset Spell7 ${SelfManaRodSummon}
    /varset Spell8 ${PetHealSpell}
    /varset Spell9  ${DichoSpell}
    /varset Spell10 ${TwinCast}
    /varset Spell11 ${PetManaNuke}
    /varset Spell12 ${GatherMana}

    /call MAG_DefaultDownTimeRotationConfig MAG_Downtime_MODEMAGIC_Rotation
    /call MAG_DefaultDebuffRotationConfig MAG_Debuff_MODEMAGIC_Rotation

    /call Heal_AddHealPoint ${PetHealPct[SETTINGVAL]}
    /call Heal_AddSpell ${PetHealPct[SETTINGVAL]} "${PetHealSpell}" ${Parse[0,"( ${Me.Pet.ID} && ${target_id} == ${Me.Pet.ID} )"]}

    |- The order in which spells are added to a Rotation Map are added is the order in which they are cast
    |- assuming that every condition is met. Due to a bug in mq2collections, make sure there are no commas
    |- within the condition statements -- this means no Select[], ${SubCall[arg1,arg2]}, or similar until
    |- typepun fixes the comma bug. The AddToRotation function also will avoid adding null
    |- spell variables so you shouldn't have to worry, for example, of swarmpet or
    |- spear nuke not working on lower level players

    |- Adding Combat recasting of pet
    /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "/call MAG_PetManagement_Routine" Command ${Parse[0,"( !${Me.Pet.ID}  && ${DoPet[SETTINGVAL]} && ${PocketPet})"]} 
    /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${SelfModRod}" Item ${Parse[0, "( ${FindItemCount[${SelfModRod}]} == 1 && ${Me.PctMana}<=${ModRodManaPct[SETTINGVAL]} && ${Me.PctHPs}>=60 )"]}
    /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${PetTypeName}" Spell ${Parse[0,"( ${FindItemCount[Malachite]} > 0 && !${Me.Pet.ID} && ${DoPet[SETTINGVAL]} )"]}    
    
    |- Below you'll see examples of the new ${Parse[#,string]} TLO
    |- from knightly. This is similar to the NoParse command as the goal
    |- is to make sure our conditions are not parsed until they are finally used
    |- in our rotation evaluation. These examples will be explained as necessary
    |- Here is an example of telling the parser to only make one pass so it resolves ${Me.Name} and not ${Spawn[]}
    |- We do this to reduce the load on the parser in the DPS loop because ${Me.Name} is not a situational condition,
    |- i.e., our name will not change. ${Spawn[]} however is situational and could be different every timer
    |-  we check so we want that to be parsed in our DPS rotation. 

    /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${MagicNuke1}"      Spell TRUE
    /if (${Me.Level} >=  98) { /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${MagicBoltNuke1}"   Spell TRUE
        } else {
            /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${MagicNuke2}"
        }
    /if (${Me.Level} >=  70) { 
        /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${SwarmPet}"         Spell TRUE
        }
    /if (${Me.Level} >= 103) { 
        /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${MagicBoltNuke2}"   Spell TRUE
        }
    /if (${Me.Level} >=  98) { 
        /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${MagicNuke2}"       Spell TRUE
        }

    |- Here's an example of how to handle low level rotations with the AddtoRotations
    |- function and the Ordered_Rotation object.

    /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${FireOrbItem}"    Item ${Parse[0,"( ${FindItemCount[${Spell[${FireOrbSummon}].Base[1]}]} == 1) "]}
|   /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${IceOrbItem}"     Item ${Parse[0,"( ${FindItemCount[${Spell[${IceOrbSummon}].Base[1]}]} == 1) "]}
    /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "Force of Elements" AA TRUE
    /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "Turn Summoned" AA ${Parse[0, "(${Target.Body.Name.Equal[Undead Pet]})"]}
    /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${PetManaNuke}"   Spell ${Parse[0, "( ${Me.PctMana}<=90 && ${PCSpellReady[${PetManaNuke}]} && ${Me.SpellReady[${PetManaNuke}]} )"]}
    /call AddToRotation MAG_DPS_MODEMAGIC_Rotation "${TwinCast}"   Spell ${Parse[0, "( SELFBUFFCHECK )"]}

    |- Debuffs - Moved to Universal Config for all Modes.
    
    |- BurnAA Rotation
    /call AddToRotation MAG_Burn_MODEMAGIC_Rotation "${EarthPetItem}" Item ${Parse[0,"( ${FindItemCount[${Spell[${EarthPetItemSummon}].Base[1]}]} == 1) "]}
    /call AddToRotation MAG_Burn_MODEMAGIC_Rotation "${FirePetItem}" Item ${Parse[0,"( ${FindItemCount[${Spell[${FirePetItemSummon}].Base[1]}]} == 1) "]}
    /call AddToRotation MAG_Burn_MODEMAGIC_Rotation "Companion's Fury" AA TRUE
    /call AddToRotation MAG_Burn_MODEMAGIC_Rotation "Host of the Elements" AA TRUE
    /call AddToRotation MAG_Burn_MODEMAGIC_Rotation "Spire of Elements"  AA TRUE
    /call AddToRotation MAG_Burn_MODEMAGIC_Rotation "Heart of Skyfire" AA TRUE
    /call AddToRotation MAG_Burn_MODEMAGIC_Rotation "Thaumaturge's Focus" AA TRUE
    /call AddToRotation MAG_Burn_MODEMAGIC_Rotation "Focus of Arcanum" AA TRUE
    /call AddToRotation MAG_Burn_MODEMAGIC_Rotation "Improved Twincast" AA TRUE
    /call AddToRotation MAG_Burn_MODEMAGIC_Rotation "Servant of Ro" AA TRUE

/return

Sub MAG_ModeConfigMODETLP
    /varset IsHealing TRUE
    /call Mag_Itemvars
    /pet taunt off
    | - Mage TLP Spellbar Setup
    /if ( ${DoMagicNuke[SETTINGVAL]} ) {
        /varset Spell1 ${MagicNuke1}
    } else {
        /varset Spell1 ${FireNuke1} 
    }
    /if (${Me.Level}>=70 && ${Spell[${SwarmPet}].Level} > 68 ) {
        /varset Spell2 ${SwarmPet}
    } else {
        /if ( ${DoMagicNuke[SETTINGVAL]} ) {
            /varset Spell2 ${MagicNuke2}
    } else {
            /varset Spell2 ${FireNuke2} 
    }
    }
    |- Spell3
    /if ( ${DoMagicNuke[SETTINGVAL]} ) {
        /varset Spell3 ${MagicRainNuke}
    } else {
        /varset Spell3 ${RainNuke} 
    }
    |- Spell4
    /varset Spell4 ${PetHealSpell}
    |- Spell5
    /varset Spell5 ${ManaRodSummon}
    
    |- Spell6 - We'll keep Malo on the bar for F2P players if we're casting malo
    /if ( ${Me.Level} >= 75  && (${Me.AltAbility[Malaise].ID} || !${DoMalo[SETTINGVAL]}) ) {
        /if ( ${DoAlliance[SETTINGVAL]} ) {
            /varset Spell6 ${AllianceBuff}
        } else {
            /varset Spell6 ${FireOrbSummon}
        }
    } else {
        /varset Spell6 ${MaloDebuff}
    }
    | - Spell 7 - Damage Shield
    /varset Spell7 ${LongDurDmgShield}
    |- Spell 8 - Gem Hotswap so Remains Null
    /varset Spell8 Null
    

    /call MAG_DefaultDownTimeRotationConfig MAG_Downtime_MODETLP_Rotation
    /call MAG_DefaultDebuffRotationConfig MAG_Debuff_MODETLP_Rotation
|    /call MAG_DefaultBuffGroupConfig
    /call BuffGroup_Init 1
    /call BuffGroup_Set 1 "${LongDurDmgShield}" "WAR,PAL,SHD"  


|- Adding Combat recasting of pet
    /call AddToRotation MAG_DPS_MODETLP_Rotation "/call MAG_PetManagement_Routine"  Command ${Parse[0,"( !${Me.Pet.ID}  && ${DoPet[SETTINGVAL]} && ${PocketPet})"]} 
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${PetTypeName}"   Spell   ${Parse[0,"( ${FindItemCount[Malachite]} > 0 && !${Me.Pet.ID} && ${DoPet[SETTINGVAL]} )"]}    
    /call AddToRotation MAG_DPS_MODETLP_Rotation "/pet taunt ON"    Command ${Parse[0,"( ${Spawn[${assistid}].Dead} && !${Pet.Taunt} )"]}
    /call AddToRotation MAG_DPS_MODETLP_Rotation "/pet taunt OFF"   Command ${Parse[0,"( !${Spawn[${assistid}].Dead} && ${Pet.Taunt} )"]}
    | - Rains Cast first when not up spam Singletarget 
    | - Starting @ DON we have Fire orbs So we Start Using them in Rotation
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${FireOrbItem}"   Item ${Parse[0,"( ${FindItemCount[${Spell[${FireOrbSummon}].Base[1]}]} == 1) "]}
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${RainNuke}"      Spell ${Parse[0,"( ${DoRain[SETTINGVAL]} && ${XAssist.XTFullHaterCount} < 2 && (MANACHECK || BURNCHECK ) )"]}
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${MagicRainNuke}" Spell ${Parse[0,"( ${DoRain[SETTINGVAL]} && ${XAssist.XTFullHaterCount} < 2 && (MANACHECK || BURNCHECK ) )"]}
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${SwarmPet}"      Spell ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${FireNuke1}"     Spell ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${MagicNuke1}"    Spell ${Parse[0,"( MANACHECK || BURNCHECK )"]}
   
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${FireNuke2}"     Spell ${Parse[0,"( MANACHECK || BURNCHECK )"]}
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${MagicNuke2}"    Spell ${Parse[0,"( MANACHECK || BURNCHECK )"]}
       
| - Temporarily Blocking Force of Elements to Free up rotation speed
|   /call AddToRotation MAG_DPS_MODEFIRE_Rotation "Force of Elements"   AA TRUE

    /call AddToRotation MAG_DPS_MODETLP_Rotation "Turn Summoned"       AA      ${Parse[0, "(${Target.Body.Name.Equal[Undead Pet]})"]}
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${PetManaNuke}"      Spell   ${Parse[0, "( ${Me.PctMana}<=90 && !${Me.Buff[Thaumatize Pet Mana Regen].ID} )"]}
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${TwinCast}"         Spell   ${Parse[0, "( SELFBUFFCHECK && !${Me.Buff[Improved Twincast].ID} )"]}
    /call AddToRotation MAG_DPS_MODETLP_Rotation "${AllianceBuff}"     Spell   ${Parse[0, "( ${Target.Named} && !${Target.Buff[${Spell[${AllianceBuff}].ID}]} && ${DoAlliance[SETTINGVAL]} && ${CanAlliance} )"]}
  
    |- Debuffs - Moved to Universal Config for all Modes.

    |- BurnAA Rotation
    /call AddToRotation MAG_Burn_MODETLP_Rotation "Companion's Fury"     AA ${Parse[0, "( ${BurnAuto[SETTINGVAL]} || MEDBURN )"]}
    /call AddToRotation MAG_Burn_MODETLP_Rotation "Host of the Elements" AA ${Parse[0, "( ${BurnAuto[SETTINGVAL]} || MEDBURN )"]}
    /call AddToRotation MAG_Burn_MODETLP_Rotation "Heart of Skyfire"     AA ${Parse[0, "( ${BurnAuto[SETTINGVAL]} || SMALLBURN )"]}
    /call AddToRotation MAG_Burn_MODETLP_Rotation "Focus of Arcanum"     AA ${Parse[0, "( ${BurnAuto[SETTINGVAL]} || SMALLBURN )"]}
    /call AddToRotation MAG_Burn_MODETLP_Rotation "Improved Twincast"    AA ${Parse[0, "( ${BurnAuto[SETTINGVAL]} || SMALLBURN )"]}
    /call AddToRotation MAG_Burn_MODETLP_Rotation "Servant of Ro"        AA ${Parse[0, "( ${BurnAuto[SETTINGVAL]} || SMALLBURN )"]}
|   /call AddToRotation MAG_Burn_MODETLP_Rotation "Thaumaturge's Focus" AA ${Parse[0, "( ${BurnAuto[SETTINGVAL]} || SMALLBURN )"]}
|    /call AddToRotation MAG_Burn_MODETLP_Rotation "Spire of Elements"  AA ${Parse[0, "( ${BurnAuto[SETTINGVAL]} || SMALLBURN )"]}
|    /call AddToRotation MAG_Burn_MODETLP_Rotation "${FindItem[${Spell[${EarthPetItemSummon}].Base[1]}].Name}" Item TRUE
|    /call AddToRotation MAG_Burn_MODETLP_Rotation "${FindItem[${Spell[${FirePetItemSummon}].Base[1]}].Name}" Item TRUE
|    /call AddToRotation MAG_Burn_MODETLP_Rotation "${FindItem[${Me.Inventory[Chest].Name}]}" Item ${Parse[0,"( ${Spell[${FindItem[${Me.Inventory[Chest].Name}].Spell}].Stacks} && (!${FindItem[${Me.Inventory[Chest].Name}].TimerReady}) )"]}
|    /call AddToRotation MAG_Burn_MODETLP_Rotation "${AllianceBuff}" Spell  ${Parse[0, "( ${Target.Named} && !${Target.Buff[${Spell[${AllianceBuff}].ID}]} && ${DoAlliance[SETTINGVAL]} && ${CanAlliance} )"]}

|-  Mage Heal Setup for Pet.    
    /call Heal_AddHealPoint ${PetHealPct[SETTINGVAL]}
    /call Heal_AddSpell     ${PetHealPct[SETTINGVAL]}   "${PetHealSpell}" ${Parse[0,"( ${Me.Pet.ID} && ${target_id} == ${Me.Pet.ID} )"]}
/return



Sub MAG_Combat_Routine
    /call PetAttack
    |- Keep Dicho up if we have it
    /if (${NPCSpellReady[${DichoSpell}]}) {
        /call SpellNow "${DichoSpell}" ${Me.Pet.ID}
    }

    /if ( DODEBUFF ) {
        /call Ordered_Rotation_Follow MAG_Debuff_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }
    /if ( ${ClassMode[SETTINGVAL]} == MODEPETTANK) {
        /call Ordered_Rotation_Follow MAG_DPSPET_${ClassMode[SETTINGVAL]}_Rotation ${Me.Pet.ID} TRUE
    }

    |Note: DPS needs an aggro regulator in here to reduce dps rate until aggro regained.
    /if ( DODPS ) {
        | This is all sorts of wrong.
        |/if (${IsTanking}) {
        |    |- If we're tanking, we want to wait a bit longer before DPSing to make sure the pet gets aggro
        |    /if ( ${Spawn[${autotargetid}].PctHPs} <= 90) {
        |        /call MAG_DoDPSRoations
        |    }
        |} else {
            /call MAG_DoDPSRoations
        |}
    }
/return FALSE

Sub MAG_DoDPSRoations
    /if ( BURNCHECK ) {
        /call Ordered_Rotation_Follow MAG_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }
        /call Ordered_Rotation_Follow MAG_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE    
/return


Sub MAG_Downtime_Routine
    /if (${Me.Pet.ID}) {
        /call HandlePetToys
    }
   /if (${DoGroupToys[SETTINGVAL]}) /call Bind_HandleGroupToys
  | - Call Pet Managment Routine in Downtime Directly Not in Rotation as its the First thing we should do if we are missing a pet.
    /if ( ${FindItemCount[Malachite]} > 0 && ${DoPet[SETTINGVAL]} &&  !${Me.Pet.ID} ) /call MAG_PetManagement_Routine
  | - Now call Our Downtime Rotation  
    /call FollowRotation MAG_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}
  | - If we have a Pet We Call The pet Downtime Now.
    /if (${Me.Pet.ID}) {
        /call FollowRotation MAG_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.Pet.ID}
    }

/return FALSE

Sub MAG_PetSummon_Routine 
    /varset PetTypeName ${${PetType[SETTINGVAL]}PetSpell}
    EDEBUG Summoning ${PetTypeName}
    /if (${FindItemCount[Malachite]} > 0) {
        /if (${PCSpellReady[${PetTypeName}]}) {
            /call SpellNow "${PetTypeName}" ${Me.ID}
        }
    } else {
        /echo \ar YOU DON'T HAVE ANY MALACHITE! WHAT'S WRONG WITH YOU!?
        /echo NO PET FOR YOU -- Temporarily turning off DoPet
        /varset DoPet[SETTINGVAL] 0
    }
/return FALSE


Sub MAG_PetManagement_Routine
| - Combined some of the Checks that all Returned false into 1 Check.
    /if ( !${DoPet[SETTINGVAL]} || (!${RG_AAReady[Companion's Suspension]} && ${RG_CanUseAA[Companion's Suspension]}) ) {
   
        /return FALSE
    }
| - Low Level Check - In 2 cases Your to lowlevel to Know Suspend companion and have no pet or You've Turned off Usepocket pet.    
    /if ( !${Me.Pet.ID} && (!${RG_CanUseAA[Companion's Suspension]} || !${DoPocketPet[SETTINGVAL]})  ) {
   
        /call MAG_PetSummon_Routine
    }
  
| - Pocket Pet Stuff Begins. -  Added Check for DoPocketPet to be Positive Rather than Assuming
    /if ( ${DoPocketPet[SETTINGVAL]} ) {

        /if ( ${PocketPet} && !${Me.Pet.ID} && ${XAssist.XTFullHaterCount}) {   
            /call AANow 176 ${Me.ID}
            /varset PocketPet 0
            /return FALSE
        }
        |- Case 1 - No pocket pet and no pet up
        /if (!${PocketPet} && !${Me.Pet.ID} && !${XAssist.XTFullHaterCount} ) {
        |- Make sure we have malachite
            /echo PetMGMT I have Zero Pets - Summoning Pets Now.
            /call MAG_PetSummon_Routine
        |- Set the fact that we have a pocketed pet now
        /varset PocketPet 0
            /if ( ${Me.AltAbility[Companion's Suspension].Rank} >= 2 ) {
                /echo Need to Buff
                    /if (${Bool[${PetHaste}]}) {
                        /call SpellNow "${PetHaste}" ${Me.Pet.ID}
                    }
                    /if (${Bool[${PetIceFlame}]}) {
                        /call SpellNow "${PetIceFlame}" ${Me.Pet.ID}
                    }
                    /if (${Me.Pet.ID}) {
                        /call HandlePetToys
                    }
                /call AANow 176 ${Me.ID}
                /varset PocketPet 1
                }
                /return FALSE
            }

        |- Case 2 - No pocket pet and pet up
        /if (!${PocketPet} && ${Me.Pet.ID} && !${XAssist.XTFullHaterCount} ) {
            /echo PetMGMT I Have No Pocket Pet.
        |- Make sure we have malachite
            /call AANow 176 ${Me.ID}
            /if (!${Me.Pet.ID}) {
                /call MAG_PetSummon_Routine
            }
            |- Set the fact that we have a pocketed pet now
            /varset PocketPet 1
            /return FALSE
        }

        |- Case 3 - Pocket Pet and no pet up
        /if (${PocketPet} && !${Me.Pet.ID} && !${XAssist.XTFullHaterCount} ) {
            /echo PetMGMT - I have a Pet in the Pocket but Non pet Up.
            /call MAG_PetSummon_Routine
        }

        |- Cast 4 - Pocket Pet and Pet up
    }

/return FALSE

Sub MAG_Heal_Routine
    /if (${Me.Pet.PctHPs} <= ${PetHealPct[SETTINGVAL]}) {
        /if (${PCSpellReady[${PetHealSpell}]}) {
            /call HealNow ${Me.Pet.ID}
        }
    }
/return ${Macro.Return}

|----------------------------------------------------------------------------
|- SUB: HandlePetToys - Handles Summoning and Provisioning of Pet Toys
|- Some included logic based on PetToys subroutines in KA12.
|----------------------------------------------------------------------------
Sub HandlePetToys
    |- Check if the pet need toys by checking if the pet has weapons.
    |- Assume if the pet has weapons they probably have optimal toys.
    /if (!${Me.Pet.Equipment[primary]}) {
        DEBUG Handle Pet Toys
        |- Check to make sure there's an open inventory slot not filled with a bag
        |- Make sure we at least have two free inventory slots so we can
        |- perform our pet toys.
        /if (${Me.FreeInventory} < 2) {
            DEBUG Not Enough Free Inventory
            /return FALSE
        }
        
        |- Given we detect based on pet weapons, and the pet weapons spell we'll use
        |- starts at level 73, there's no point right now in doing anything if we're
        |- lower level than 73.
        /if (${Me.Level} < 73) {
            /return FALSE
        }
        
        /declare id_openslot  int local ${GetOpenInvSlot[]}
        DEBUG OpenSlot: ${id_openslot}  
        |- /call SummonPetArmor ${Me.Pet.ID} ${id_openslot}
        |- /call SummonPetToys Armor ${Me.Pet.ID} ${id_openslot}
        
        |- Developer note from Dr. Whom
        |- Have only been able to test this personally on my mage up to level 85 and was
        |- giving the other testers problems so this is currently
        |- May have a different open slot
        /varset id_openslot ${GetOpenInvSlot[]}
        DEBUG OpenSlot: ${id_openslot}  
        |- /call SummonPetWeapons ${Me.Pet.ID} ${id_openslot}
        /if (${id_openslot} && ${Me.CombatState.NotEqual[COMBAT]}) {
            /call SummonPetToys Weapon ${Me.Pet.ID} ${id_openslot}
        }
    }
/return

|- Optional argument <pcname> to only givegrouptoys to a specific pc
#bind HandleGroupToys /givegrouptoys
Sub Bind_HandleGroupToys(string pcname)
    /declare id_openslot  int local ${GetOpenInvSlot[]}
       /declare i int local 1
    |- first Things first see if i can even Make Pet toys. if i am To Low Level or have no Inventory Return          
    /if ( (${Me.FreeInventory} < 2) || ( ${Me.Level} < 73 ) ) {
        DEBUG Not Enough Free Inventory Or Level 72 And Under
        /return FALSE
    } else {
        /if (${pcname.Length}) {
            /if (!${Spawn[pc ${pcname}].Pet.Equipment[primary]} && ${Spawn[pc ${pcname}].Pet.ID}) {
                    /varset id_openslot ${GetOpenInvSlot[]}
                    DEBUG OpenSlot: ${id_openslot} 
                    /if (${id_openslot} && ${Me.CombatState.NotEqual[COMBAT]}) {
                        /echo ${Spawn[pc ${pcname}].Pet.ID} ${Spawn[pc ${pcname}].Pet.Name}
                        /call SummonPetToys Weapon ${Spawn[pc ${pcname}].Pet.ID} ${id_openslot}
                        /echo Gave Toys to ${Spawn[pc ${pcname}].Pet.ID}
                        /if (${DoPetArmor[SETTINGVAL]}) /call SummonPetToys Armor ${Spawn[pc ${pcname}].Pet.ID} ${id_openslot}
                                
                    }
            }      
        } else {
            |- Check if the Groups pet need toys by checking if the pet has weapons.
            |- If they Are Not a Mage - Also Give them Armor
            DEBUG OpenSlot: ${id_openslot}  
            /for i 1 to ${Group.Members} 
                /if (!${Group.Member[${i}].Pet.Equipment[primary]} && ${Group.Member[${i}].Pet.ID}) {
                    /varset id_openslot ${GetOpenInvSlot[]}
                    DEBUG OpenSlot: ${id_openslot} 
                    /if (${id_openslot} && ${Me.CombatState.NotEqual[COMBAT]}) {
                        /echo ${Group.Member[${i}].Pet.ID} ${Group.Member[${i}].Pet.Name}
                        /call SummonPetToys Weapon ${Group.Member[${i}].Pet.ID} ${id_openslot}
                        /echo Gave Toys to ${Group.Member[${i}].Pet.ID}
                        /if (${DoPetArmor[SETTINGVAL]}) /call SummonPetToys Armor ${Group.Member[${i}].Pet.ID} ${id_openslot}
                        /echo Gave Armor to ${Group.Member[${i}].Pet.ID}
                        /if (${DoPetHeirloom[SETTINGVAL]}) /call SummonPetToys Heirloom ${Group.Member[${i}].Pet.ID} ${id_openslot}        
                        /echo Gave Heirlooms to ${Group.Member[${i}].Pet.ID}
                    }
                }      
            /next i 
        }
    }
/return
|- This Sub Handles Arming the Groups pets with Weapons and Armors
|**
Sub HandleGroupToys
       /declare i int local 1
    |- first Things first see if i can even Make Pet toys. if i am To Low Level or have no Inventory Return          
    /if ( (${Me.FreeInventory} < 2) || ( ${Me.Level} < 73 ) ) {
        DEBUG Not Enough Free Inventory Or Level 72 And Under
        /return FALSE
    } else {
    |- Check if the Groups pet need toys by checking if the pet has weapons.
    |- If they Are Not a Mage - Also Give them Armor
        /declare id_openslot  int local ${GetOpenInvSlot[]}
        DEBUG OpenSlot: ${id_openslot}  
        /for i 1 to ${Group.Members} 
            /if (!${Group.Member[${i}].Pet.Equipment[primary]} && ${Group.Member[${i}].Pet.ID}) {
                /varset id_openslot ${GetOpenInvSlot[]}
                DEBUG OpenSlot: ${id_openslot} 
                /if (${id_openslot} && ${Me.CombatState.NotEqual[COMBAT]}) {
                    /echo ${Group.Member[${i}].Pet.ID} ${Group.Member[${i}].Pet.Name}
                    /call SummonPetToys Weapon ${Group.Member[${i}].Pet.ID} ${id_openslot}
                    /echo Gave Toys to ${Group.Member[${i}].Pet.ID}
                    /if (${DoPetArmor[SETTINGVAL]}) /call SummonPetToys Armor ${Group.Member[${i}].Pet.ID} ${id_openslot}
                            
                }
            }      
        /next i 
    }
/return
**|
Sub SummonPetToys(string toy_type, int pet_id, int pack_id)
    /if (${toy_type.NotEqual[Weapon]} && ${toy_type.NotEqual[Armor]} && ${toy_type.NotEqual[Heirloom]}) {
        /return FALSE
    }

    /declare packname string local pack${pack_id}
    DEBUG Using pack name ${packname}
    /declare spellvar string local ${Pet${toy_type}Summon}
    DEBUG Using spell ${spellvar}
 
    |- Make sure our spell is defined. Could be used to summon armor or weapons and
    |- there is no assurance it will be called from HandlePetToys so we check here
    |- as well versus a raw level check.
    /if (${spellvar.Equal[NULL]}) {
        /return FALSE
    }
    
    |- Make sure we're high enough level to use the spell -- the rare case where we
    |- de-level
    /if (${Me.Level} < ${Spell[${spellvar}].Level}) {
        /return FALSE
    }
    
    /if (${PCSpellReady[${spellvar}]}) {
        DEBUG Casting "${spellvar}"
        /call SpellNow "${spellvar}" ${Me.ID}   
        DEBUG Spell Return ${CastResult}
        /if (${CastResult.NotEqual[CAST_SUCCESS]}) {
            |- If the summon failed, get the heck out of here.
            /return FALSE
        }
        |- Wait till we have an item on our cursor
        /delay 5s ${Cursor.ID}
    } else {
        |- If the spell's not ready, get out.
        /return FALSE
    }
    |- Now we need to exchange the bag with our top-level slot.
    /if (${InvSlot[pack${pack_id}].Item.ID}) {
        DEBUG Item Found in Top Level Slot ${packname} -- Picking up
        /shiftkey /itemnotify ${packname} leftmouseup
        |- Try and autoinventory the item we picked up
        /while (${Cursor.ID}) {
            /autoinventory
            /delay 1s !${Cursor.ID}
        }
    } else {
        DEBUG Item not found - just dropping bag
        |- Drop our bag in the empty slot - some code duplication here
        /while (${Cursor.ID}) {
            /nomodkey /itemnotify ${packname} leftmouseup
            /delay 1s !${Cursor.ID}
        }
    }
    
    |- What happens if the bag is a Folded Pack
    /while (${InvSlot[${packname}].Item.Name.Find[Folded Pack]}) {
        /nomodkey /itemnotify ${packname} rightmouseup
        |- Folded backs end up on our cursor.
        /delay 5s ${Cursor.ID}
        |- Drop the unfolded pack back in our inventory
        /while (${Cursor.ID}) {
            /nomodkey /itemnotify ${packname} leftmouseup
            /delay 1s !${Cursor.ID}
        }
    }
    
    |- Hand Toy off to the Pet
    |- Open our pack
    /nomodkey /itemnotify ${packname} rightmouseup
    |- TODO: Need a condition to check if the pack window has opened
    /delay 1s 
    
    /if (${toy_type.Equal[Armor]} || ${toy_type.Equal[Heirloom]} ) {
        |- Loop through each item in our bag and give it to the pet
        /declare slotnum int local 0
        /for slotnum 1 to ${InvSlot[${packname}].Item.Container}
            DEBUG Item Name ${InvSlot[${packname}].Item.Item[${slotnum}].Name}
        /if (${InvSlot[${packname}].Item.Item[${slotnum}].Name.NotEqual[NULL]}) {
            /call GiveTo ${pet_id} "${InvSlot[${packname}].Item.Item[${slotnum}].Name}" 1 TRUE
        }
        /next slotnum
    } else {
        |- Must be a weapon
        |- Hand Weapons off to the pet
        /if (${DoPetTank[SETTINGVAL]}) {
            |- If we're pet tanking, give the pet the hate swords in bag slots
            |- 7 and 8. At higher levels this only ends up with one aggro swords
            |- so perhaps there's a way of generalizing later.
            DEBUG Item Name ${InvSlot[${packname}].Item.Item[7].Name}
            /call GiveTo ${pet_id} "${InvSlot[${packname}].Item.Item[7].Name}" 1 TRUE
            DEBUG Item Name ${InvSlot[${packname}].Item.Item[8].Name}
            /call GiveTo ${pet_id} "${InvSlot[${packname}].Item.Item[8].Name}" 1 TRUE
        } else {
            |- Otherwise do the first and third
            DEBUG Item Name ${InvSlot[${packname}].Item.Item[2].Name}
            /call GiveTo ${pet_id} "${InvSlot[${packname}].Item.Item[2].Name}" 1 TRUE
            DEBUG Item Name ${InvSlot[${packname}].Item.Item[4].Name}
            /call GiveTo ${pet_id} "${InvSlot[${packname}].Item.Item[4].Name}" 1 TRUE
        }
    }
    |- Delete the satchel if it's still there
    /if (${InvSlot[${packname}].Item.ID}) {
        /nomodkey /itemnotify ${packname} leftmouseup
        /delay 5s ${Cursor.ID}
        |- Just double check and make sure it's a temporary
        /if (${Cursor.NoRent}) {
            DEBUG Destroying ${Cursor.Name}
            /destroy
            /delay 30 !${Cursor.ID}
        }
    }   
/return

Sub GetOpenInvSlot
        /declare i int local 1
        /for i 1 to 10
            /if (${InvSlot[pack${i}].Item.Container}) /continue
            /if (!${InvSlot[pack${i}].Item.Container} || ${InvSlot[pack${i}].Item.ID}==0) {
                /return ${i}
            }
        /next i 
/return FALSE

Sub MAG_PullSetup
    /if (${Me.Pet.ID} && ${DoPetPull[SETTINGVAL]}) {
        /call Pull_SetAbility "pullpet" "Special"
    } else /if (${RG_CanUseAA[Malaise]}) {
        /call Pull_SetAbility "Malaise" "AA"
    } else /if (${MaloDebuff.NotEqual[NULL]} && ${Me.Gem[${MaloDebuff}]}) {
        /call Pull_SetAbility "${MaloDebuff}" "Spell"    
    } else {
        |- all encompassing default
        /if (${Me.Gem[${FireNuke1}]}) {
            /call Pull_SetAbility "${FireNuke1}" "Spell"
        } else {
            /call Pull_SetAbility "${MagicNuke1}" "Spell"
        }
    }
/return

|----------------------------------------------------------------------------
|- SUB: CheckOptions
|---------------------------------------------------------------------------- 
Sub MAG_CheckOptions
    /if (${DoPetTank[SETTINGVAL]} ) {
        /echo I am Pet Tanking!
        /varset AutoAssistAt[SETTINGVAL] 100
        /varset IsTanking 1
        /varset DoAutoTarget[SETTINGVAL] 1
        /varset StayOnTarget[SETTINGVAL] 0
        /varset DoAutoEngage[SETTINGVAL] 1
        /varset AllowMezBreak[SETTINGVAL] 1
        /varset DoMelee[SETTINGVAL] 0
        |- Mage Specific additions
        |- /varset PetType[SETTINGVAL] Air
        /varset PetTypeName ${${PetType[SETTINGVAL]}PetSpell}
    } else {
        /varset IsTanking 0
    |   /varset PetType[SETTINGVAL] Air
        /varset AutoAssistAt[SETTINGVAL] 98
        /varset PetTypeName ${${PetType[SETTINGVAL]}PetSpell}
        /varset StayOnTarget[SETTINGVAL] 1
    }
/return
Sub MAG_DefaultDebuffRotationConfig(string rotation_name)
    |- Debuffs
    /call AddToRotation "${rotation_name}" "Malaise" AA ${Parse[0,"( ${DoMalo[SETTINGVAL]} && DETAACHECK )"]} 
    /call AddToRotation "${rotation_name}" "${MaloDebuff}" Spell ${Parse[0,"( ${DoMalo[SETTINGVAL]} && DETSPELLCHECK )"]} 
    /call AddToRotation "${rotation_name}" "Wind of Malaise" AA ${Parse[0,"( ( ${DoMalo[SETTINGVAL]} && ${DoAEMalo[SETTINGVAL]} ) DETAACHECK && ${XAssist.XTFullHaterCount} > 2 )"]}

/return

Sub MAG_DefaultDownTimeRotationConfig(string rotation_name)
|- Stubbing out Downtime rotation as they appear to be similar in all modes
|- Rearranged so it Starts With Fast Things and Finishes with The Super Longer Gather spells for mana regen So it can do the Quick Things first
    /call AddToRotation "${rotation_name}" "${PetAura}"             Spell ${Parse[0,"( !${Me.Aura[1].Name.Find[${Spell[${PetAura}].BaseName}]} && !${Me.Aura[2].Name.Find[${Spell[${PetAura}].BaseName}]} )"]}
    /call AddToRotation "${rotation_name}" "Elemental Conversion"   AA ${Parse[0, "( ${Me.PctMana}<=${ManaGatherPct[SETTINGVAL]} && ${RG_AAReady[Elemental Conversion]} && ${Me.Pet.ID} )"]}
    /call AddToRotation "${rotation_name}" "Forceful Rejuvenation"  AA ${Parse[0, "( ${Me.PctMana}<=${ManaGatherPct[SETTINGVAL]} && !${Me.SpellReady[${GatherMana}]} && ${RG_AAReady[Forceful Rejuvenation]} )"]}
    /if (!${Me.AltAbility[Summon Modulation Shard].ID}) {
        /call AddToRotation "${rotation_name}" "${ManaRodSummon}"  Spell ${Parse[1,"( (${FindItemCount[${Spell[${ManaRodSummon}].Base[1]}]} == 0) && !${Cursor.ID} && ${SummonModRods[SETTINGVAL]} )"]}
        /varset GroupModRod ${FindItem[${Spell[${ManaRodSummon}].Base[1]}].Name}
    } else {
        /call AddToRotation "${rotation_name}" "Summon Modulation Shard" AA ${Parse[0,"( (${FindItemCount[${Me.AltAbility[Summon Modulation Shard].Spell.Base[1]}]} == 0) && !${Cursor.ID} &&  ${SummonModRods[SETTINGVAL]} )"]}
        /varset GroupModRod ${FindItem[${Me.AltAbility[Summon Modulation Shard].Spell.Base[1]}].Name}
    }
    |** need to identify Trigger spell and make a If/else for the mage Unity AA so that it uses it or the 4 spells. depending on trigger. 
    /if (${Spell[${Shroud}].Level}<=${Spell[${Me.AltAbility[Thaumaturge's Unity].Spell.Trigger[1].BaseName}].Level} && ${RG_CanUseAA[Thaumaturge's Unity]}) {
        /call AddToRotation ${rotationname} "Thaumaturge's Unity" AA ${Parse[0,"( !${Me.Buff[${Me.AltAbility[Thaumaturge's Unity)].Spell.Trigger[1].BaseName}].ID} )"]}
    } else {
      /call AddToRotation "${rotation_name}" "${ManaRegenBuff}"         Spell ${Parse[0,"( SELFBUFFCHECK )"]}   
      /call AddToRotation "${rotation_name}" "${SelfShield}"            Spell ${Parse[0,"( SELFBUFFCHECK )"]}
      /call AddToRotation "${rotation_name}" "${}"            Spell ${Parse[0,"( SELFBUFFCHECK )"]} 
      /call AddToRotation "${rotation_name}" "${}"            Spell ${Parse[0,"( SELFBUFFCHECK )"]}    
    **|
    /call AddToRotation "${rotation_name}" "${SelfManaRodSummon}"   Spell ${Parse[0,"( ( ${FindItemCount[${Spell[${SelfManaRodSummon}].Base[1]}]} == 0) && !${Cursor.ID} )"]}
    /call AddToRotation "${rotation_name}" "${GatherMana}"          Spell ${Parse[0, "( ${Me.PctMana}<=${ManaGatherPct[SETTINGVAL]} && ${PCSpellReady[${GatherMana}]} && ${Me.SpellReady[${GatherMana}]} )"]}
    /call AddToRotation "${rotation_name}" "${ManaRegenBuff}"         Spell ${Parse[0,"( SELFBUFFCHECK )"]} 
    /call AddToRotation "${rotation_name}" "${SelfShield}"            Spell ${Parse[0,"( SELFBUFFCHECK )"]} 
    /call AddToRotation "${rotation_name}" "Thaumaturge's Unity"    AA ${Parse[0,"( SELFBUFFAACHECK )"]}
|    /call AddToRotation "${rotation_name}" "${IceOrbSummon}"        Spell ${Parse[0,"( ${FindItemCount[${Spell[${IceOrbSummon}].Base[1]}]} == 0 && ${target_id} == ${Me.ID} )"]}
    /call AddToRotation "${rotation_name}" "${FireOrbSummon}"       Spell ${Parse[0,"( ${FindItemCount[${Spell[${FireOrbSummon}].Base[1]}]} == 0 )"]}
    /call AddToRotation "${rotation_name}" "${EarthPetItemSummon}"  Spell ${Parse[0,"( ${FindItemCount[${Spell[${EarthPetItemSummon}].Base[1]}]} == 0 )"]}
    /call AddToRotation "${rotation_name}" "${FirePetItemSummon}"   Spell ${Parse[0,"( ${FindItemCount[${Spell[${FirePetItemSummon}].Base[1]}]} == 0 )"]}
    /call AddToRotation "${rotation_name}" "${LongDurDmgShield}"    Spell ${Parse[0,"( SELFBUFFCHECK )"]}
    /call AddToRotation "${rotation_name}" "${PetManaConv}"         Spell ${Parse[2,"( !${Me.Buff[${Spell[${Spell[${PetManaConv}].AutoCast}].Name}].ID} && ${Me.Pet.ID})"]}
    /call AddToRotation "${rotation_name}" "Elemental Form"         AA ${Parse[0,"( SELFBUFFAACHECK )"]}
    |- Only use 


    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}

    |- PetBuff Rotation
    /call AddToRotation "${rotation_name}" "${Epic}"                Item  ${Parse[0,"( !${Me.PetBuff[Primal Fusion]} && !${Me.PetBuff[Elemental Conjuction]} && !${FindItem[=${Epic}].TimerReady}  && ${Me.Pet.ID} && SELFBUFFPETCHECK )"]} 
    /call AddToRotation "${rotation_name}" "${PetIceFlame}"         Spell ${Parse[0,"( SELFBUFFPETCHECK )"]} 
    /call AddToRotation "${rotation_name}" "${PetHaste}"            Spell ${Parse[0,"( SELFBUFFPETCHECK )"]} 
    /call AddToRotation "${rotation_name}" "${LongDurDmgShield}"    Spell ${Parse[0,"( SELFBUFFPETCHECK && ${Me.AltAbility[Companions Discipline =>3]} )"]}
    /call AddToRotation "${rotation_name}" "Second Wind Ward"       AA ${Parse[0,"( SELFBUFFPETCHECK )"]} 
    /call AddToRotation "${rotation_name}" "Host in the Shell"      AA ${Parse[0,"( SELFBUFFPETCHECK  && ${DoPetTank[SETTINGVAL]})"]} 
    /call AddToRotation "${rotation_name}" "Companion's Aegis"      AA ${Parse[0,"( SELFBUFFPETCHECK && ${DoPetTank[SETTINGVAL]} )"]} 
    /call AddToRotation "${rotation_name}" "Companion's Intervening Divine Aura" AA ${Parse[0,"( SELFBUFFPETCHECK && ${DoPetTank[SETTINGVAL]} )"]} 

    |- Create Pets - is better Not in the rotation for Downtime but Directly In the Routine. So it can be called Before All this ^^^^^    

/return
Sub MAG_DefaultBuffGroupConfig
    |- Setup our group buffs that will need Dannet
    |- We will have 6 buffs for the group
    /call BuffGroup_Init 1
    /call BuffGroup_Set 1 "${LongDurDmgShield}" "All"  
/return