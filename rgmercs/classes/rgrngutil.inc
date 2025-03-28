|- RGrngutil.inc
|- Version 0.1
|- Updated: 7/3/2019
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
#define MODEDPS 0
#define MODETLP 1
#define MODETANK 2

Sub RNG_Setup
    /declare RGList_RNG list outer

|- Live Rotations
    /call Ordered_Rotation_New RNG_Debuff_MODEDPS_Rotation
    /call Ordered_Rotation_New RNG_Heal_MODEDPS_Rotation
    /call Ordered_Rotation_New RNG_DPS_MODEDPS_Rotation
    /call Ordered_Rotation_New RNG_Downtime_MODEDPS_Rotation
    /call Ordered_Rotation_New RNG_Burn_MODEDPS_Rotation

    /call Ordered_Rotation_New RNG_Debuff_MODETANK_Rotation
    /call Ordered_Rotation_New RNG_Heal_MODETANK_Rotation
    /call Ordered_Rotation_New RNG_DPS_MODETANK_Rotation
    /call Ordered_Rotation_New RNG_Downtime_MODETANK_Rotation
    /call Ordered_Rotation_New RNG_Burn_MODETANK_Rotation

|- TLP Rotations
    /call Ordered_Rotation_New RNG_Debuff_MODETLP_Rotation
    /call Ordered_Rotation_New RNG_Heal_MODETLP_Rotation
    /call Ordered_Rotation_New RNG_DPS_MODETLP_Rotation
    /call Ordered_Rotation_New RNG_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New RNG_Burn_MODETLP_Rotation
|- Items
    /call ItemSet_New Epic
|-Spells
    /call AbilitySet_New ArrowOpener    
    /call AbilitySet_New PullOpener        
    /call AbilitySet_New CalledShotsArrow        
    /call AbilitySet_New FocusedArrows            
    /call AbilitySet_New DichoSpell            
    /call AbilitySet_New SummerNuke                
    /call AbilitySet_New SwarmDot                
    /call AbilitySet_New ShortSwarmDot                
    /call AbilitySet_New UnityBuff
    /call AbilitySet_New Protectionbuff
    /call AbilitySet_New ShoutBuff                
    /call AbilitySet_New AgroBuff                
    /call AbilitySet_New AgroReducerBuff        
    /call AbilitySet_New AggroKick
    /call AbilitySet_New ParryProcBuff            
    /call AbilitySet_New AtkBuff                
    /call AbilitySet_New AtkHPBuff                
    /call AbilitySet_New RunSpeedBuff            
    /call AbilitySet_New KillShotBuff            
    /call AbilitySet_New Eyes        
    /call AbilitySet_New GroupStrengthBuff        
    /call AbilitySet_New GroupPredatorBuff        
    /call AbilitySet_New GroupEnrichmentBuff
    /call AbilitySet_New Rathe
    /call AbilitySet_New BowDisc                
    /call AbilitySet_New MeleeDisc                
    /call AbilitySet_New DefenseDisc            
    /call AbilitySet_New Fireboon               
    /call AbilitySet_New Firenuke               
    /call AbilitySet_New Iceboon               
    /call AbilitySet_New Icenuke               
    /call AbilitySet_New Heartshot              
    /call AbilitySet_New EndRegenDisc
    /call AbilitySet_New Coat
    /call AbilitySet_New Mask
    /call AbilitySet_New hunt
    /call AbilitySet_New Heal
    /call AbilitySet_New Fastheal
    /call AbilitySet_New Totheal
    /call AbilitySet_New SnareSpells
    /call AbilitySet_New FireFist
    /call AbilitySet_New DsBuff
    /call AbilitySet_New SkinLike
    /call AbilitySet_New MoveSpells
    /call AbilitySet_New Alliance
    /call AbilitySet_New AgiBuff
    /call AbilitySet_New Cloak
    /call AbilitySet_New Veil
    
|-Discs
    /call AbilitySet_New JoltingKicks            
    /call AbilitySet_New AEBlades                
    /call AbilitySet_New FocusedBlades            
    /call AbilitySet_New ReflexSlashHeal

|-Special
    /declare FireBoonbuff         string    outer
    /declare IceBoonbuff         string    outer

|-Config Options
    /call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = DPS Set 2 = TLP
    /call RGLoadSetting RNG Manatonuke 5 Combat "%Mana to Nuke until"
    /call RGLoadSetting RNG DoAoe 0 Combat "FILLME"
    /call RGLoadSetting RNG DoOpener 1 Combat "Use Opening Arrow Shot Silent Shot Line"
    /call RGLoadSetting RNG DoPoisonArrow 1 Combat "Set 0/1 to use Poison Aarrow ability."
    /call RGLoadSetting RNG DoReagentArrow 0 Combat "Set 0/1 to use Spell & Opener which require Reagent arrows"
    /call RGLoadSetting RNG HealPoint 65  Healing "When Ranger Should Heal Used Out of Combat or Below level 112 heals."
    /call RGLoadSetting RNG DoHeals 1 Combat "Set 0/1 to enable healing. Checked in the main loop. Default: 1."
    /call RGLoadSetting RNG DoSnare 1 Combat "Set 0/1 to use Snare abilities. Affects pulling only. Restart macro to take effect."
    /call RGLoadSetting RNG DoRunSpeed 1 Options "Set 0/1 to enable the use of the RNG runspeed buffs."
    /call RGLoadSetting RNG HPStopDOT 30 Combat "%HP to cut off to stop casting dots."
    /call RGLoadSetting RNG NavCircle 0 Options    "Enables Use of NavAround Circle for ranged mode or old style Stickmoveback (Nav Circle may cause lag in some zones)"
    /call RGLoadSetting RNG DoAgroReducerBuff 1 Combat "Set 0/1 to use Jolt Buff."


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
    /declare Epic                     string outer NULL
    /declare spellmisc             int outer 8
    /declare GroupBuffRecast     int outer 0
    /declare miscspellremem        string outer NULL
    /declare spellrememtimer    timer outer 0
    /declare ReadyToCast          timer outer 0
    /declare groupbufftimer        timer outer 0
    /varset spellmisc ${Me.NumGems}
   	/declare DoTanking 			bool		outer		FALSE

/return 

|----------------------------------------------------------------------------
|- SUB: CheckSpells
|---------------------------------------------------------------------------- 
Sub RNG_SetupSkills
|-Items
|- Epic - Due to the Comma In the ranger Epic Name and a long standing Mq2 Collections Bug we have to Hard Code this Instead of using a Iterator to determine the better one.
    /if (${FindItem[=Heartwood Blade].ID})  {
            /varset Epic    Heartwood Blade
        } else /if (${FindItem[=Aurora, the Heartwood Blade].ID}) {
            /varset Epic    Aurora, the Heartwood Blade    
        }
| - Ranger Alliance
    /call AbilitySet_Add "Bosquestalker's Alliance" Alliance
    /call AbilitySet_Add "Wildstalker's Covenant" Alliance
    /call AbilitySet_Add "Arbor Stalker's Coalition" Alliance
    /call AbilitySet_Add "Dusksage Stalker's Conjunction" Alliance
    /call AbilitySet_ChooseOuter Alliance Alliance

|-DefenseDisc
    /call AbilitySet_Add "Weapon Shield Discipline" DefenseDisc
    /call AbilitySet_ChooseOuter DefenseDisc DefenseDisc

|-MeleeDisc
    /call AbilitySet_Add "Fernstalker's Discipline" MeleeDisc
    /call AbilitySet_Add "Dusksage Stalker's Discipline" MeleeDisc
    /call AbilitySet_Add "Bosquestalker's Discipline" MeleeDisc
    /call AbilitySet_Add "Copsestalker's Discipline" MeleeDisc
    /call AbilitySet_Add "Wildstalker's Discipline" MeleeDisc
    /call AbilitySet_Add "Arbor Stalker's Discipline" MeleeDisc
    /call AbilitySet_ChooseOuter MeleeDisc MeleeDisc

|-BowDisc
    /call AbilitySet_Add "Trueshot Discipline" BowDisc
    /call AbilitySet_Add "Aimshot Discipline" BowDisc
    /call AbilitySet_Add "Sureshot Discipline" BowDisc
    /call AbilitySet_Add "Pureshot Discipline" BowDisc
    /call AbilitySet_ChooseOuter BowDisc BowDisc
    
|-GroupEnrichmentBuff
    /call AbilitySet_Add "Arbor Stalker's Enrichment" GroupEnrichmentBuff
    /call AbilitySet_Add "Copsestalker's Enrichment" GroupEnrichmentBuff
    /call AbilitySet_Add "Wildstalker's Enrichment" GroupEnrichmentBuff
    /call AbilitySet_ChooseOuter GroupEnrichmentBuff GroupEnrichmentBuff
|----- Single Target DS
    /call AbilitySet_Add "Shield of Thistles" DsBuff
    /call AbilitySet_Add "Shield of Brambles" DsBuff
    /call AbilitySet_Add "Shield of Spikes"      DsBuff
    /call AbilitySet_Add "Shield of Thorns"      DsBuff
    /call AbilitySet_Add "Shield of Briar"      DsBuff
    /call AbilitySet_Add "Shield of Needles"  DsBuff
    /call AbilitySet_Add "Shield of Spurs"      DsBuff
    /call AbilitySet_Add "Shield of DrySpines" DsBuff
    /call AbilitySet_Add "Shield of Nettlespikes" DsBuff
    /call AbilitySet_Add "Shield of Bramblespikes" DsBuff
    /call AbilitySet_Add "Shield of Nettlespines" DsBuff
    /call AbilitySet_Add "Shield of Nettlespears" DsBuff
    /call AbilitySet_Add "Shield of Needlebarbs" DsBuff
    /call AbilitySet_Add "Shield of Rimespurs" DsBuff
    /call AbilitySet_Add "Shield of Shadethorns" DsBuff
    /call AbilitySet_ChooseOuter DsBuff DsBuff

|- Firenuke - 
    |--- Basic Fire Nuke Line Level 3-
    /call AbilitySet_Add "Flame Lick"        Firenuke
    /call AbilitySet_Add "Burst of Fire"     Firenuke
    /call AbilitySet_Add "Ignite"             Firenuke
    /call AbilitySet_Add "Flaming Arrow"     Firenuke
    /call AbilitySet_Add "Burning Arrow"     Firenuke
    /call AbilitySet_Add "Call of Flame"     Firenuke
    /call AbilitySet_Add "FireStrike"         Firenuke
    /call AbilitySet_Add "Brushfire"         Firenuke
    /call AbilitySet_Add "Sylvan Burn"         Firenuke
    /call AbilitySet_Add "Ancient: Burning Chaos" Firenuke
    /call AbilitySet_Add "Hearth Embers"     Firenuke
    /call AbilitySet_Add "Scorched Earth"     Firenuke
    /call AbilitySet_Add "Volcanic Ash"     Firenuke
    /call AbilitySet_Add "Galvanic Ash"     Firenuke
    /call AbilitySet_Add "Cataclysm Ash"     Firenuke
    /call AbilitySet_Add "Burning Ash"         Firenuke
    /call AbilitySet_Add "Beastwood Ash"     Firenuke
    /call AbilitySet_Add "Vileoak Ash"         Firenuke
    /call AbilitySet_Add "Wildfire Ash"     Firenuke
    /call AbilitySet_Add "Skyfire Ash"         Firenuke
    /call AbilitySet_Add "Pyroclastic Ash"     Firenuke
    /call AbilitySet_Add "Lunarflare Ash"     Firenuke
    /call AbilitySet_ChooseOuter Firenuke Firenuke

|- Fireboon - 
    /call AbilitySet_Add "Ashcloud Boon" Fireboon
    /call AbilitySet_Add "Wildfire Boon" Fireboon
    /call AbilitySet_Add "Skyfire Boon" Fireboon
    /call AbilitySet_Add "Pyroclastic Boon" Fireboon
    /call AbilitySet_Add "Lunarflare Boon" Fireboon
    /call AbilitySet_ChooseOuter Fireboon Fireboon
    /varset FireBoonbuff ${Spell[${Spell[${Fireboon}].AutoCast}].Name}

|- Wind Boon
    /call AbilitySet_Add "Mistral Boon" Iceboon
    /call AbilitySet_Add "Windblast Boon" Iceboon
    /call AbilitySet_Add "Windgale Boon" Iceboon
    /call AbilitySet_Add "Windshear Boon" Iceboon
    /call AbilitySet_Add "Nocturnal Boon" Iceboon
    /call AbilitySet_ChooseOuter Iceboon Iceboon
    /varset IceBoonbuff ${Spell[${Spell[${Iceboon}].AutoCast}].Name}
|- Wind Nuke
    /call AbilitySet_Add "Bitter Wind" Icenuke
    /call AbilitySet_Add "Frozen Wind" Icenuke
    /call AbilitySet_Add "Frigid Wind" Icenuke
    /call AbilitySet_Add "Restless Wind" Icenuke
    /call AbilitySet_Add "Coagulated Wind" Icenuke
    /call AbilitySet_ChooseOuter Icenuke Icenuke

|- Protection buff 29-115
    
    /call AbilitySet_Add "Riftwind's Protection"     Protectionbuff
    /call AbilitySet_Add "Force of Nature"    Protectionbuff
    /call AbilitySet_Add "Warder's Protection"     Protectionbuff
    /call AbilitySet_Add "Protection of the Wild"     Protectionbuff
    /call AbilitySet_Add "Protection of the Minohten" Protectionbuff
    /call AbilitySet_Add "Protection of the Kirkoten" Protectionbuff
    /call AbilitySet_Add "Protection of the Paw" Protectionbuff
    /call AbilitySet_Add "Protection of the Vale" Protectionbuff
    /call AbilitySet_Add "Protection of the Copse" Protectionbuff
    /call AbilitySet_Add "Protection of the Bosque" Protectionbuff
    /call AbilitySet_Add "Protection of the Forest" Protectionbuff
    /call AbilitySet_Add "Protection of the Woodlands" Protectionbuff
    /call AbilitySet_Add "Protection of the Wakening Land" Protectionbuff
    /call AbilitySet_Add "Protection of the Valley" Protectionbuff
    /call AbilitySet_ChooseOuter Protectionbuff Protectionbuff

|- UnityBuff 
    /call AbilitySet_Add "Bosquetender's Unity" UnityBuff
    /call AbilitySet_Add "Copsestalker's Unity" UnityBuff
    /call AbilitySet_Add "Wildstalker's Unity" UnityBuff
    /call AbilitySet_ChooseOuter UnityBuff UnityBuff

|- ShoutBuff
    /call AbilitySet_Add "Shout of the Predator" ShoutBuff
    /call AbilitySet_Add "Shout of the Bosquestalker" ShoutBuff
    /call AbilitySet_Add "Shout of the Copsestalker" ShoutBuff
    /call AbilitySet_Add "Shout of the Wildstalker" ShoutBuff
    /call AbilitySet_Add "Shout of the Arbor Stalker" ShoutBuff
    /call AbilitySet_Add "Shout of the Dusksage Stalker" ShoutBuff
    /call AbilitySet_ChooseOuter ShoutBuff ShoutBuff
    
|- AgroBuff
    /call AbilitySet_Add "Devastating Blades" AgroBuff
    /call AbilitySet_Add "Devastating Edges" AgroBuff
    /call AbilitySet_Add "Devastating Slashes" AgroBuff
    /call AbilitySet_Add "Devastating Impact" AgroBuff
    /call AbilitySet_Add "Devastating Swords" AgroBuff
    /call AbilitySet_Add "Devastating Steel" AgroBuff
    /call AbilitySet_Add "Devastating Velium" AgroBuff
    /call AbilitySet_Add "Devastating Barrage" AgroBuff
    /call AbilitySet_ChooseOuter AgroBuff AgroBuff

|- AgroReducerBuff
    /call AbilitySet_Add "Jolting Blades" AgroReducerBuff
    /call AbilitySet_Add "Jolting Strikes" AgroReducerBuff
    /call AbilitySet_Add "Jolting Swings" AgroReducerBuff
    /call AbilitySet_Add "Jolting Edges" AgroReducerBuff
    /call AbilitySet_Add "Jolting Impact" AgroReducerBuff
    /call AbilitySet_Add "Jolting Shock" AgroReducerBuff
    /call AbilitySet_Add "Jolting Swords" AgroReducerBuff
    /call AbilitySet_Add "Jolting Steel" AgroReducerBuff
    /call AbilitySet_Add "Jolting Velium" AgroReducerBuff
    /call AbilitySet_Add "Jolting Luclinite" AgroReducerBuff
    /call AbilitySet_ChooseOuter AgroReducerBuff AgroReducerBuff

|- AggroKick
    /call AbilitySet_Add "Enraging Roundhouse Kicks" AggroKick
    /call AbilitySet_Add "Enraging Axe Kicks" AggroKick
    /call AbilitySet_Add "Enraging Wheel Kicks" AggroKick
    /call AbilitySet_Add "Enraging Cut Kicks" AggroKick
    /call AbilitySet_Add "Enraging Heel Kicks" AggroKick
    /call AbilitySet_Add "Enraging Crescent Kicks" AggroKick
    /call AbilitySet_ChooseOuter AggroKick AggroKick


|- ParryProcBuff
    /call AbilitySet_Add "Crackling Blades" ParryProcBuff
    /call AbilitySet_Add "Crackling Edges" ParryProcBuff
    /call AbilitySet_Add "Deafening Edges" ParryProcBuff
    /call AbilitySet_Add "Deafening Weapons" ParryProcBuff
    /call AbilitySet_Add "Roaring Weapons" ParryProcBuff
    /call AbilitySet_Add "Roaring Blades" ParryProcBuff
    /call AbilitySet_Add "Howling Blades" ParryProcBuff
    /call AbilitySet_Add "Vociferous Blades" ParryProcBuff
    /call AbilitySet_ChooseOuter ParryProcBuff ParryProcBuff
    
|- RunSpeedBuff
    /call AbilitySet_Add "Spirit of Eagle" RunSpeedBuff
    /call AbilitySet_Add "Spirit of Falcons" RunSpeedBuff
    /call AbilitySet_ChooseOuter RunSpeedBuff RunSpeedBuff

| - Anti-Animal/Human Opener
    /call AbilitySet_Add "Heartshot" Heartshot
    /call AbilitySet_Add "Heartsting" Heartshot
    /call AbilitySet_Add "Heartsting" Heartshot
    /call AbilitySet_Add "Heartslice" Heartshot
    /call AbilitySet_Add "Heartslash" Heartshot
    /call AbilitySet_Add "Heartsplit" Heartshot
    /call AbilitySet_Add "Heartcleave" Heartshot
    /call AbilitySet_Add "Heartsunder" Heartshot
    /call AbilitySet_Add "Heartruin" Heartshot
    /call AbilitySet_ChooseOuter Heartshot Heartshot

|- Opening Puller
    /call AbilitySet_Add "Deadfall" PullOpener
    /call AbilitySet_Add "Heartpierce" PullOpener
    /call AbilitySet_Add "Heartrend" PullOpener
    /call AbilitySet_Add "Heartrip" PullOpener
    /call AbilitySet_Add "Heartspike" PullOpener

|- Arrow Opener    
    /call AbilitySet_Add "Silent Shot" ArrowOpener
    /call AbilitySet_Add "Stealthy Shot" ArrowOpener
    /call AbilitySet_ChooseOuter ArrowOpener ArrowOpener
 
|- Called Shot
    /call AbilitySet_Add "Called Shots" CalledShotsArrow 
    /call AbilitySet_Add "Announced Shots" CalledShotsArrow 
    /call AbilitySet_Add "Forecasted Shots" CalledShotsArrow 
    /call AbilitySet_Add "Anticipated Shots" CalledShotsArrow 
    /call AbilitySet_Add "Foreseen Shots" CalledShotsArrow 
    /call AbilitySet_Add "Marked Shots" CalledShotsArrow 
    /call AbilitySet_Add "Claimed Shots" CalledShotsArrow
    /call AbilitySet_Add "Inevitable Shots" CalledShotsArrow
    /call AbilitySet_ChooseOuter CalledShotsArrow CalledShotsArrow
 
|- Focused arrows
    /call AbilitySet_Add "Focused Frenzy of Arrows" FocusedArrows
    /call AbilitySet_Add "Focused Storm of Arrows" FocusedArrows
    /call AbilitySet_Add "Focused Tempest of Arrows" FocusedArrows
    /call AbilitySet_Add "Focused Arrow Swarm" FocusedArrows
    /call AbilitySet_Add "Focused Rain of Arrows" FocusedArrows
    /call AbilitySet_Add "Focused Arrowrain" FocusedArrows
    /call AbilitySet_Add "Focused Arrowgale" FocusedArrows
    /call AbilitySet_Add "Focused Blizzard of Arrows" FocusedArrows
    /call AbilitySet_Add "Focused Whirlwind of Arrows" FocusedArrows
    /call AbilitySet_ChooseOuter FocusedArrows FocusedArrows
 
|- Dicho/Dissident Evoling Spell
    /call AbilitySet_Add "Dichotomic Fusillade" DichoSpell
    /call AbilitySet_Add "Dissident Fusillade" DichoSpell
    /call AbilitySet_Add "Composite Fusillade" DichoSpell
    /call AbilitySet_Add "Ecliptic Fusillade" DichoSpell
    /call AbilitySet_ChooseOuter DichoSpell DichoSpell
 
|- Summer Nuke
    /call AbilitySet_Add "Summer's Deluge" SummerNuke
    /call AbilitySet_Add "Summer's Torrent" SummerNuke
    /call AbilitySet_Add "Summer's Viridity" SummerNuke
    /call AbilitySet_Add "Summer's Mist" SummerNuke
    /call AbilitySet_Add "Summer's Storm" SummerNuke
    /call AbilitySet_Add "Summer's Squall" SummerNuke
    /call AbilitySet_Add "Summer's Gale" SummerNuke
    /call AbilitySet_Add "Summer's Cyclone" SummerNuke
    /call AbilitySet_Add "Summer's Tempest" SummerNuke
    /call AbilitySet_Add "Summer's Sleet" SummerNuke
    /call AbilitySet_ChooseOuter SummerNuke SummerNuke
 
 |- SwarmDot - 25-115
    /call AbilitySet_Add "Stinging Swarm" SwarmDot
    /call AbilitySet_Add "Swarm of Pain" SwarmDot
    /call AbilitySet_Add "Drones of Doom" SwarmDot
    /call AbilitySet_Add "Fire Swarm" SwarmDot
    /call AbilitySet_Add "Drifting Death" SwarmDot
    /call AbilitySet_Add "Locust Swarm" SwarmDot
    /call AbilitySet_Add "Wasp Swarm" SwarmDot
    /call AbilitySet_Add "Hornet Swarm" SwarmDot
    /call AbilitySet_Add "Beetle Swarm" SwarmDot
    /call AbilitySet_Add "Scarab Swarm" SwarmDot
    /call AbilitySet_Add "Vespid Swarm" SwarmDot
    /call AbilitySet_Add "Dreadbeetle Swarm" SwarmDot
    /call AbilitySet_Add "Blisterbeetle Swarm" SwarmDot
    /call AbilitySet_Add "Bonecrawler Swarm" SwarmDot
    /call AbilitySet_Add "Ice Burrower Swarm" SwarmDot
    /call AbilitySet_Add "Bloodbeetle Swarm" SwarmDot
    /call AbilitySet_Add "Hotaria Swarm" SwarmDot
    /call AbilitySet_ChooseOuter SwarmDot SwarmDot

 |- ShortSwarmDot - 85-123
    /call AbilitySet_Add "Swarm of Fernflies" ShortSwarmDot
    /call AbilitySet_Add "Swarm of Bloodflies" ShortSwarmDot
    /call AbilitySet_Add "Swarm of Hyperboreads" ShortSwarmDot
    /call AbilitySet_Add "Swarm of Glistenwings" ShortSwarmDot
    /call AbilitySet_Add "Swarm of Vespines" ShortSwarmDot
    /call AbilitySet_Add "Swarm of Sand Wasps" ShortSwarmDot
    /call AbilitySet_Add "Swarm of Hornets" ShortSwarmDot
    /call AbilitySet_Add "Swarm of Bees" ShortSwarmDot
    /call AbilitySet_ChooseOuter ShortSwarmDot ShortSwarmDot

|- Jolting Kicks
    /call AbilitySet_Add "Jolting Frontkicks" JoltingKicks
    /call AbilitySet_Add "Jolting Hook Kicks" JoltingKicks
    /call AbilitySet_Add "Jolting Crescent Kicks" JoltingKicks
    /call AbilitySet_Add "Jolting Heel Kicks" JoltingKicks
    /call AbilitySet_Add "Jolting Cut Kicks" JoltingKicks
    /call AbilitySet_Add "Jolting Wheel Kicks" JoltingKicks
    /call AbilitySet_Add "Jolting Axe Kicks" JoltingKicks
    /call AbilitySet_Add "Jolting Roundhouse Kicks" JoltingKicks
    /call AbilitySet_Add "Jolting Drop Kicks" JoltingKicks
    /call AbilitySet_ChooseOuter JoltingKicks JoltingKicks
 
 |- Blades AE
    /call AbilitySet_Add "Storm of Blades" AEBlades
    /call AbilitySet_Add "Squall Of Blades" AEBlades
    /call AbilitySet_Add "Gale of Blades" AEBlades
    /call AbilitySet_Add "Blizzard of Blades" AEBlades
    /call AbilitySet_Add "Tempest of Blades" AEBlades
    /call AbilitySet_Add "Maelstrom of Blades" AEBlades
    /call AbilitySet_ChooseOuter AEBlades AEBlades
 
 |- Focused Blades
    /call AbilitySet_Add "Focused Storm of Blades" FocusedBlades
    /call AbilitySet_Add "Focused Squall of Blades" FocusedBlades
    /call AbilitySet_Add "Focused Gale of Blades" FocusedBlades
    /call AbilitySet_Add "Focused Blizzard of Blades" FocusedBlades
    /call AbilitySet_Add "Focused Tempest of Blades" FocusedBlades
    /call AbilitySet_ChooseOuter FocusedBlades FocusedBlades
 
 | - Reflex Slash heal
    /call AbilitySet_Add "Reflexive Bladespurs" ReflexSlashHeal
    /call AbilitySet_Add "Reflexive Nettlespears" ReflexSlashHeal
    /call AbilitySet_Add "Reflexive Rimespurs" ReflexSlashHeal
    /call AbilitySet_ChooseOuter ReflexSlashHeal ReflexSlashHeal

|---Rathe AC line
    /call AbilitySet_Add "Cloak of Needlespikes" Rathe
    /call AbilitySet_Add "Cloak of Bloodbarbs" Rathe
    /call AbilitySet_Add "Shared Cloak of Rimespurs" Rathe
    /call AbilitySet_Add "Cloak of Rimespurs" Rathe
    /call AbilitySet_Add "Shared Cloak of Needlebarbs" Rathe
    /call AbilitySet_Add "Cloak of Needlebarbs" Rathe
    /call AbilitySet_Add "Cloak of Nettlespears" Rathe
    /call AbilitySet_Add "Shared Cloak of Spurs" Rathe
    /call AbilitySet_Add "Cloak of Spurs" Rathe
    /call AbilitySet_Add "Shared Cloak of Burrs" Rathe
    /call AbilitySet_Add "Cloak of Burrs" Rathe
    /call AbilitySet_Add "Cloak of Quills" Rathe
    /call AbilitySet_Add "Cloak of Feathers" Rathe
    /call AbilitySet_Add "Cloak of Scales" Rathe
    /call AbilitySet_Add "Call of the Rathe" Rathe
    /call AbilitySet_Add "Guard of the Earth" Rathe
    /call AbilitySet_Add "Riftwind's Protection" Rathe
    /call AbilitySet_ChooseOuter Rathe Rathe

|---Fast Endurance regen
  
    /call AbilitySet_Add "Second Wind" EndRegenDisc
    /call AbilitySet_Add "Third Wind" EndRegenDisc
    /call AbilitySet_Add "Fourth Wind" EndRegenDisc
    /call AbilitySet_Add "Respite" EndRegenDisc
    /call AbilitySet_Add "Reprieve" EndRegenDisc
    /call AbilitySet_Add "Rest" EndRegenDisc
    /call AbilitySet_Add "Breather" EndRegenDisc
    /call AbilitySet_Add "Hiatus" EndRegenDisc
    /call AbilitySet_Add "Relax" EndRegenDisc
    /call AbilitySet_Add "Night's Calming" EndRegenDisc
    /call AbilitySet_Add "Convalesce" EndRegenDisc
    /call AbilitySet_ChooseOuter EndRegenDisc EndRegenDisc

|------Hunt Line----------------- 75,90-115
    /call AbilitySet_Add "Engulfed by the Hunt"         hunt
    /call AbilitySet_Add "Consumed by the Hunt"         hunt
    /call AbilitySet_Add "Invigorated by the Hunt"         hunt
    /call AbilitySet_Add "Galvanized by the Hunt"         hunt
    /call AbilitySet_Add "Inspired by the Hunt"         hunt
    /call AbilitySet_Add "Energized by the Hunt"         hunt
    /call AbilitySet_Add "Spurred by the Hunt"             hunt
    /call AbilitySet_Add "Provoked by the Hunt"         hunt
    /call AbilitySet_Add "Steeled by the Hunt"            hunt
    /call AbilitySet_ChooseOuter hunt hunt

|----- Snares -----------------------------
    /call AbilitySet_Add "Snare"                SnareSpells
    /call AbilitySet_Add "Tangling Weeds"    SnareSpells
    /call AbilitySet_Add "Ensnare"            SnareSpells
    /if (${EverQuest.Server.Find[zek]}) /call AbilitySet_Add "Tangle"            SnareSpells
    /if (${EverQuest.Server.Find[zek]}) /call AbilitySet_Add "Entangle"            SnareSpells
    /call AbilitySet_Add "Earthen Embrace"    SnareSpells
    /call AbilitySet_Add "Earthen Shackles"    SnareSpells
    /call AbilitySet_ChooseOuter     SnareSpells SnareSpells
|----- Agility Buff ----------------
    /call AbilitySet_Add "Feet Like Cat" AgiBuff
    /call AbilitySet_ChooseOuter AgiBuff AgiBuff
|----- Self DS Coat line -------- 13-115
    /call AbilitySet_Add "ThistleCoat" Coat
    /call AbilitySet_Add "Barbcoat" Coat
    /call AbilitySet_Add "Bramblecoat" Coat
    /call AbilitySet_Add "Spikecoat" Coat
    /call AbilitySet_Add "Thorncoat" Coat
    /call AbilitySet_Add "Bladecoat" Coat
    /call AbilitySet_Add "Briarcoat" Coat
    /call AbilitySet_Add "Spinecoat" Coat
    /call AbilitySet_Add "Quillcoat" Coat
    /call AbilitySet_Add "Burrcoat"  Coat
    /call AbilitySet_Add "Spurcoat" Coat
    /call AbilitySet_Add "Nettlespear Coat" Coat
    /call AbilitySet_Add "Needlebarb Coat" Coat
    /call AbilitySet_Add "Rimespur Coat" Coat
    /call AbilitySet_Add "Moonthorn Coat" Coat
    /call AbilitySet_Add "Needlespike Coat" Coat
    /call AbilitySet_ChooseOuter Coat Coat

|-------- Eyes Buff ---------------------- 10-115
    /call AbilitySet_Add "Hawk Eye"     Eyes
    /call AbilitySet_Add "Falcon Eye"     Eyes    
    /call AbilitySet_Add "Eagle Eye"     Eyes
    /call AbilitySet_Add "Eyes of the Owl"     Eyes
    /call AbilitySet_Add "Eyes of the Peregrine"     Eyes
    /call AbilitySet_Add "Eyes of the Nocturnal"     Eyes
    /call AbilitySet_Add "Eyes of the Wolf"     Eyes
    /call AbilitySet_Add "Eyes of the Raptor"     Eyes
    /call AbilitySet_Add "Eyes of the Howler"     Eyes
    /call AbilitySet_Add "Eyes of the Harrier"     Eyes
    /call AbilitySet_Add "Eyes of the Sabertooth"     Eyes
    /call AbilitySet_Add "Eyes of the Visionary"     Eyes
    /call AbilitySet_Add "Eyes of the Senshali" Eyes
    /call AbilitySet_Add "Eyes of the Phoenix" Eyes
    /call AbilitySet_ChooseOuter Eyes Eyes
|----- Self Mana Regen -------- 13-115
    /call AbilitySet_Add "Mask of the Stalker" Mask
    /call AbilitySet_ChooseOuter Mask Mask
|-------- Skin Like Line 7 -59------------------
    /call AbilitySet_Add "Skin Like Wood"         SkinLike
    /call AbilitySet_Add "Skin Like Rock"         SkinLike
    /call AbilitySet_Add "Skin Like Steel"         SkinLike
    /call AbilitySet_Add "Skin Like Diamond"     SkinLike
    /call AbilitySet_Add "Skin Like Nature"     SkinLike
    /call AbilitySet_ChooseOuter SkinLike SkinLike
|--------- FireFist Line -------------------------- 17 - 65 - Merges into Protection At that level.
    /call AbilitySet_Add "Firefist" FireFist
    /call AbilitySet_Add "Nature's Precision" FireFist
    /call AbilitySet_Add "Wolf Form" FireFist
    /call AbilitySet_Add "Greater Wolf Form" FireFist
    /call AbilitySet_Add "Feral Form" FireFist
    /call AbilitySet_ChooseOuter FireFist FireFist

|-------- GroupPredatorBuff ---------------------- 56-115
    /call AbilitySet_Add "Mark of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Call of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Spirit of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Howl of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Snarl of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Gnarl of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Yowl of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Roar of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Cry of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Shout of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Shout of the Bosquestalker" GroupPredatorBuff
    /call AbilitySet_Add "Bellow of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Wail of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Frostroar of the Predator" GroupPredatorBuff
    /call AbilitySet_Add "Shout of the Dusksage Stalker" GroupPredatorBuff
    /call AbilitySet_Add "Shout of the Fernstalker" GroupPredatorBuff
    /call AbilitySet_ChooseOuter GroupPredatorBuff GroupPredatorBuff
    
|-------- GroupStrengthBuff ---------------------- 51-115
    /call AbilitySet_Add "Nature's Precision"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of Nature"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of Tunare"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of the Hunter"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of the Forest Stalker"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of the Gladewalker"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of the Tracker"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of the Thicket Stalker"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of the Gladetender"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of the Bosquestalker"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of the Copsestalker"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of the Wildstalker"     GroupStrengthBuff
    /call AbilitySet_Add "Strength of the Arbor Stalker"     GroupStrengthBuff
    /call AbilitySet_Add "Shout of the Dusksage Stalker" GroupStrengthBuff
    /call AbilitySet_Add "Shout of the Fernstalker"     GroupStrengthBuff
    /call AbilitySet_ChooseOuter GroupStrengthBuff GroupStrengthBuff
    
|--- Heals ---------------------------------
|--- Fast heal    Level 2 - Gem 1
    /call AbilitySet_Add "Elizerain Spring" Heal
    /call AbilitySet_Add "Darkflow Spring" Heal
    /call AbilitySet_Add "Meltwater Spring"     Heal
    /call AbilitySet_Add "Wellspring"     Heal
    /call AbilitySet_Add "Cloudfont"     Heal
    /call AbilitySet_Add "Cloudburst"     Heal
    /call AbilitySet_Add "Purespring"    Heal
    /call AbilitySet_Add "Purefont"     Heal
    /call AbilitySet_Add "Oceangreen Aquifer"     Heal
    /call AbilitySet_Add "Dragonscale Aquifer"     Heal
    /call AbilitySet_Add "Sunderock Springwater"     Heal
    /call AbilitySet_Add "Sylvan Water"     Heal
    /call AbilitySet_Add "Sylvan Light"     Heal
    /call AbilitySet_Add "Chloroblast"     Heal
    /call AbilitySet_Add "Greater Healing"     Heal
    /call AbilitySet_Add "Light Healing"     Heal
    /call AbilitySet_Add "Healing"     Heal
    /call AbilitySet_Add "Minor Healing"     Heal
    /call AbilitySet_Add "Salve"     Heal
    /call AbilitySet_ChooseOuter Heal Heal
    
|--- Normal Heal
    /call AbilitySet_Add "Desperate Quenching"      Fastheal
    /call AbilitySet_Add "Desperate Geyser"        Fastheal
    /call AbilitySet_Add "Desperate Deluge"     Fastheal
    /call AbilitySet_Add "Desperate Downpour"     Fastheal
    /call AbilitySet_Add "Desperate Drenching"     Fastheal
    /call AbilitySet_Add "Desperate Dousing"     Fastheal
    /call AbilitySet_Add "Desperate Dewcloud"     Fastheal
    /call AbilitySet_Add "Desperate Meltwater"     Fastheal
    /call AbilitySet_ChooseOuter Fastheal Fastheal
    
|--- Totheal
    /call AbilitySet_Add "Desperate Quenching"  Totheal
    /call AbilitySet_Add "Desperate Geyser"     Totheal
    /call AbilitySet_Add "Darkflow Spring" Totheal
    /call AbilitySet_Add "Desperate Meltwater"     Totheal
    /call AbilitySet_Add "Meltwater Spring"    Totheal
    /call AbilitySet_ChooseOuter Totheal Totheal

|- Movement Series Spells -- Mix of group target and single target but will require the same dannet checks
    /call AbilitySet_Add "Spirit of Falcons" MoveSpells
    /call AbilitySet_Add "Spirit of Eagle" MoveSpells
    /call AbilitySet_Add "Pack Shrew" MoveSpells
    /call AbilitySet_Add "Spirit of the Shrew" MoveSpells
    /call AbilitySet_Add "Spirit of Wolf" MoveSpells
    /call AbilitySet_ChooseOuter MoveSpells MoveSpells

|- cloak 
    /call AbilitySet_Add "Shalowain's Crucible Cloak" Cloak
    /call AbilitySet_Add "Luclin's Darkfire Cloak" Cloak
    /call AbilitySet_Add "Outrider's Ever-Burning Cloak" Cloak
    /call AbilitySet_Add "Lavastorm Cloak" Cloak
    /call AbilitySet_Add "Ro's Burning Cloak" Cloak
    /call AbilitySet_ChooseOuter Cloak Cloak

|- Veil
    /call AbilitySet_Add "Shadowveil" Veil
    /call AbilitySet_Add "Duskveil" Veil
    /call AbilitySet_Add "Frostveil" Veil
    /call AbilitySet_Add "Vaporous Veil" Veil
    /call AbilitySet_Add "Shimmering Veil" Veil
    /call AbilitySet_Add "Arbor Veil" Veil
    /call AbilitySet_Add "Veil of Alaris" Veil
    /call AbilitySet_Add "Nature Veil" Veil
    /call AbilitySet_ChooseOuter Veil Veil

/return



Sub RNG_DefaultDPSRotationConfig(string rotation_name)
    |- DPS Rotation
    /if (${RG_CanUseAA[Entrap]}) {
        /call AddToRotation "${rotation_name}" "Entrap" AA ${Parse[0,"( ${DoSnare[SETTINGVAL]} && ${Target.PctHPs} < 50 && DETAACHECK )"]}
    } else {
        /call AddToRotation "${rotation_name}" "${SnareSpells}" Spell ${Parse[0,"( ${DoSnare[SETTINGVAL]} && ${Target.PctHPs} < 50 && DETSPELLCHECK )"]}
    }

    /call AddToRotation  "${rotation_name}" "Guardian of the Forest" AA ${Parse[0,"( !${Me.Song[Group Guardian of the Forest].ID} && !${Me.Song[Outrider's Accuracy].ID} )"]}
    /call AddToRotation  "${rotation_name}" "Outrider's Accuracy" AA  ${Parse[0,"( !${Me.Song[Guardian of the Forest].ID}  && !${Me.Song[Group Guardian of the Forest].ID} ) "]}
    /call AddToRotation  "${rotation_name}" "Group Guardian of the Forest" AA ${Parse[0,"( !${Me.Song[Guardian of the Forest].ID} && !${Me.Song[Outrider's Accuracy].ID} )"]}

    /call AddToRotation "${rotation_name}" "${Epic}" Item ${Parse[0,"( ${DoEpic[SETTINGVAL]} )"]}
    /call AddToRotation "${rotation_name}" "${CalledShotsArrow}" Spell ${Parse[0,"( !${Target.Buff[Called Shots Effect].ID} )"]}
    /call AddToRotation "${rotation_name}" "${FocusedArrows}" Spell ${Parse[0,"( ${Target.Buff[Called Shots Effect].ID} )"]}
    /call AddToRotation "${rotation_name}" "${DichoSpell}" Spell  ${Parse[0,"( ${Target.Buff[Called Shots Effect].ID} )"]}
    /call AddToRotation "${rotation_name}" "${Heartshot}" Spell  ${Parse[0,"( ${DoReagentArrow[SETTINGVAL]} && ${Target.Buff[Called Shots Effect].ID} )"]}
    /call AddToRotation "${rotation_name}" "${Fireboon}" Spell  ${Parse[0,"( !${Me.Buff[${FireBoonbuff}].ID} )"]}
    /if (${Me.Level}<98) {
        /call AddToRotation "${rotation_name}" "${Firenuke}" Spell ${Parse[0,"( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    } else { 
        /call AddToRotation "${rotation_name}" "${Firenuke}" Spell ${Parse[0,"( ${Me.Buff[${FireBoonbuff}].ID} && ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    }
    /call AddToRotation "${rotation_name}" "${Totheal}" Spell     ${Parse[0,"( ${Me.TargetOfTarget.PctHPs}<${HealPoint[SETTINGVAL]})"]}
    /call AddToRotation "${rotation_name}" "Elemental Arrow" AA    TRUE        
    /call AddToRotation "${rotation_name}" "${AEBlades}" Disc ${Parse[0,"( ${Target.Distance}<=50 && !${Me.Moving} && ${DoAoe[SETTINGVAL]} )"]}
    /call AddToRotation "${rotation_name}" "${FocusedBlades}" Disc ${Parse[0,"( ${Target.Distance}<=50 && !${Me.Moving} )"]}
    /call AddToRotation "${rotation_name}" "${ReflexSlashHeal}"  Disc ${Parse[0,"( ${Target.Distance}<=${Target.MaxRangeTo} && ${Me.Combat} )"]}
    |- Dot
    /call AddToRotation "${rotation_name}" "${SwarmDot}" Spell  ${Parse[0,"( DOTSPELLCHECK )"]}
    |- aggro
    /if (${DoTanking}) {
    	/call AddToRotation "${rotation_name}" "Taunt" 				Ability ${Parse[0,"( ${Me.AbilityReady[Taunt]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
        /call AddToRotation "${rotation_name}" "${AggroKick}" Disc ${Parse[0,"( ${Target.Distance}<=50 && !${Me.Moving} && ( ${Me.PctAggro}<100 || ${Target.SecondaryPctAggro} > 50 ) )"]}
        /call AddToRotation "${rotation_name}" "${SummerNuke}" Spell  ${Parse[0,"(  ( ${Me.PctAggro}<100 || ${Target.SecondaryPctAggro} > 50 ) || (${Me.Level}>=98 && ${Me.Buff[${FireBoonbuff}].ID} && ${Me.PctMana} > ${Manatonuke[SETTINGVAL]}) ) "]}
    } else {
        /call AddToRotation "${rotation_name}" "${JoltingKicks}" Disc ${Parse[0,"( ${Target.Distance}<=50 && !${Me.Moving} && ${Me.PctAggro} > 30 )"]}
        /call AddToRotation "${rotation_name}" "Imbued Ferocity" AA ${Parse[0,"( ${Me.PctAggro} > 45 )"]}
        /call AddToRotation "${rotation_name}" "Silent Strikes" AA ${Parse[0,"( ${Me.PctAggro} > 60 )"]}
        /call AddToRotation "${rotation_name}" "Chameleon's Gift" AA ${Parse[0,"( ${Me.PctAggro} > 70  && ${Me.PctHPs} < 50)"]}
        /call AddToRotation "${rotation_name}" "${SummerNuke}" Spell  ${Parse[0,"( ( ${Me.PctAggro} < 60 && ${Me.Level}>=98 && ${Me.Buff[${FireBoonbuff}].ID} ) && ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}

    }

    |- defense
    /call AddToRotation "${rotation_name}" "${DefenseDisc}"         Disc ${Parse[0,"(${Me.PctHPs} < 20 && !${Me.ActiveDisc.ID} )"]}
    /call AddToRotation "${rotation_name}" "Outrider's Evasion"         AA ${Parse[0,"(${Me.PctHPs} < 30 )"]}
    /call AddToRotation "${rotation_name}" "Protection of the Spirit Wolf"         AA ${Parse[0,"(${Me.PctHPs} < 40 )"]}
    /call AddToRotation "${rotation_name}" "Bulwark of the Brownies"         AA ${Parse[0,"(${Me.PctHPs} < 50 )"]}


/return

Sub RNG_DefaultBurnRotationConfig(string rotation_name)
    | - Burn AA Rotation
    /call AddToRotation  "${rotation_name}" "Pack Hunt" AA TRUE
    /call AddToRotation  "${rotation_name}" "Entropy of Nature" AA TRUE
    /call AddToRotation  "${rotation_name}" "Spire of the Pathfinders" AA TRUE
    /call AddToRotation  "${rotation_name}" "Scarlet Cheetah's Fang" AA TRUE
    /call AddToRotation  "${rotation_name}" "Empowered Blades" AA TRUE
    /call AddToRotation  "${rotation_name}" "Auspice of the Hunter" AA TRUE
    /call AddToRotation  "${rotation_name}" "${BowDisc}" Disc ${Parse[0,"( !${DoMelee[SETTINGVAL]} )"]}
    /call AddToRotation  "${rotation_name}" "${MeleeDisc}" Disc ${Parse[0,"( ${DoMelee[SETTINGVAL]} )"]}
/return


Sub RNG_TankDownRotationConfig(string rotation_name)
    |- Self buff rotation

    /if (${Spell[${GroupStrengthBuff}].Level}<=${Spell[${Me.AltAbility[Wildstalker's Unity (Azia)].Spell.Trigger[3].BaseName}].Level} ) {
        /call AddToRotation "${rotation_name}" "Wildstalker's Unity (Azia)" AA ${Parse[0,"( !${Me.Buff[${Me.AltAbility[Wildstalker's Unity (Azia)].Spell.Trigger[3].BaseName}].ID} && ${Spell[${Me.AltAbility[Wildstalker's Unity (Azia)].Spell.Trigger[3].BaseName}].Stacks} )"]}
    } else { 
        /call AddToRotation "${rotation_name}" "${AgroBuff}"  Spell  ${Parse[0,"(SELFBUFFCHECK)"]}
        /call AddToRotation "${rotation_name}" "${hunt}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}
        /call AddToRotation "${rotation_name}" "${Protectionbuff}" Spell  ${Parse[0,"(SELFBUFFCHECK)"]}
        /call AddToRotation "${rotation_name}" "${Eyes}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}
        /call AddToRotation "${rotation_name}" "${Coat}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}        
        /call AddToRotation "${rotation_name}" "${DsBuff}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}  
    }
    /call AddToRotation "${rotation_name}" "${Cloak}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}
    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==1 && ${Me.Mount.ID} && ${DoMelee[SETTINGVAL]} )"]}
    /call AddToRotation "${rotation_name}" "Poison Arrows" AA ${Parse[0,"( ${DoPoisonArrow[SETTINGVAL]} && !${Me.Buff[Poison Arrows].ID}  )"]}
/return


Sub RNG_DefaultDownRotationConfig(string rotation_name)
    |- Self buff rotation

    /if (${Spell[${GroupStrengthBuff}].Level}<=${Spell[${Me.AltAbility[Wildstalker's Unity (Beza)].Spell.Trigger[3].BaseName}].Level} ) {
        /call AddToRotation "${rotation_name}" "Wildstalker's Unity (Beza)" AA ${Parse[0,"( !${Me.Buff[${Me.AltAbility[Wildstalker's Unity (Beza)].Spell.Trigger[3].BaseName}].ID} && ${Spell[${Me.AltAbility[Wildstalker's Unity (Beza)].Spell.Trigger[3].BaseName}].Stacks} )"]}
    } else { 
        /if (!${DoAgroReducerBuff[SETTINGVAL]}) {
            /call AddToRotation "${rotation_name}" "${ParryProcBuff}"  Spell  ${Parse[0,"(SELFBUFFCHECK)"]}
        }
        /call AddToRotation "${rotation_name}" "${hunt}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}
        /if ( ${Me.Level} < 74  ) {
            /call AddToRotation "${rotation_name}" "${Mask}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}    
        }
        /call AddToRotation "${rotation_name}" "${Protectionbuff}" Spell  ${Parse[0,"(SELFBUFFCHECK)"]}
        /call AddToRotation "${rotation_name}" "${Eyes}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}
        /call AddToRotation "${rotation_name}" "${Coat}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}  
        /call AddToRotation "${rotation_name}" "${DsBuff}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}  
    }

    /if (${DoAgroReducerBuff[SETTINGVAL]}) {
        /call AddToRotation "${rotation_name}" "${AgroReducerBuff}"  Spell  ${Parse[0,"(SELFBUFFCHECK)"]}
    }
    /call AddToRotation "${rotation_name}" "${Cloak}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}
    /call AddToRotation "${rotation_name}" "${Veil}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}
    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==1 && ${Me.Mount.ID} && ${DoMelee[SETTINGVAL]} )"]}
    /call AddToRotation "${rotation_name}" "Poison Arrows" AA ${Parse[0,"( ${DoPoisonArrow[SETTINGVAL]} && !${Me.Buff[Poison Arrows].ID}  )"]}
/return

Sub RNG_DefaultHealRotationConfig
 |- Setup Heals
    /call Heal_AddHealPoint     ${HealPoint[SETTINGVAL]}
    |- Light Heal Point Spells
    /call Heal_AddSpell             ${HealPoint[SETTINGVAL]} "${Heal}" ${Parse[0,"( ${Me.Level} < 111  )"]}
    /call Heal_AddSpell            ${HealPoint[SETTINGVAL]} "${Fastheal}" ${Parse[0,"( ${Me.Level} < 114  )"]}
    /call Heal_AddAA            ${HealPoint[SETTINGVAL]} "Convergence of Spirits" ${Parse[0,"( ${Spawn[id ${target_id}].ID} == ${assistid} )"]}
  
/return

Sub RNG_DefaultGroupBuffConfig
    |- Group Buffs
    
    /call BuffGroup_Init 6
    /call BuffGroup_Set 1 "${Rathe}"  "WAR,SHD,PAL,RNG" TRUE
    /call BuffGroup_Set 2 "${GroupEnrichmentBuff}" "WAR,SHD,PAL,ROG,MNK,BER,RNG,BST" TRUE
    /call BuffGroup_Set 3 "${MoveSpells}" "ALL" ${Parse[0, "${DoRunSpeed[SETTINGVAL]}"]}
    /call BuffGroup_Set 4 "${GroupStrengthBuff}" "ALL" TRUE
    /call BuffGroup_Set 5 "${DsBuff}" "ALL" TRUE
    /call BuffGroup_Set 6 "${GroupPredatorBuff}" "ALL" TRUE
/return

Sub RNG_ModeConfigMODEDPS
   /varset IsHealing TRUE
   /varset DoTanking FALSE

   |- Spell Gem 1 Is For Our Heal gem from 3 and CHanges over to fast heal @ 89.
      /if ( ${Fastheal.NotEqual[NULL]} ) {
        /varset Spell1 ${Fastheal} 
    } else { 
        /varset Spell1 ${Heal}
    }
    | - SpellGem2 - Is Our Standard Fire Nuke 3-115
    /varset Spell2 ${Firenuke}
    | - SpellGem 3 - This is Our Swarm Dot From 25 to 115
    /if ( ${Fireboon.NotEqual[NULL]} ) {
         /varset Spell3 ${Fireboon}
    } else { 
        /varset Spell3 ${ShortSwarmDot}
    }
    /if ( ${ArrowOpener.NotEqual[NULL]}) {
        /varset Spell4 ${ArrowOpener} 
    } else { 
        /varset Spell4 ${SnareSpells}
    }
    /varset Spell5 ${DichoSpell}
    /varset Spell6 ${CalledShotsArrow}
    /varset Spell7 ${FocusedArrows}
    /varset Spell8 ${Heartshot}
    /varset Spell9 ${SummerNuke}
    /if ( ${Fireboon.NotEqual[NULL]} ) {
        /if ( ${Me.Level} > 82  ) {
            /varset Spell10 ${ShortSwarmDot} 
            /varset SwarmDot ${ShortSwarmDot} 
            } else {
            /varset Spell10 ${SwarmDot} 
        }
    }
    /varset Spell11 ${Iceboon}
    /varset Spell12 ${Icenuke}
    /varset Spell13 ${Alliance}  

    /call RNG_DefaultDPSRotationConfig RNG_DPS_MODEDPS_Rotation DoTanking
    /call RNG_DefaultBurnRotationConfig RNG_Burn_MODEDPS_Rotation
    /call RNG_DefaultDownRotationConfig RNG_Downtime_MODEDPS_Rotation
    /call RNG_DefaultHealRotationConfig
    /call RNG_DefaultGroupBuffConfig

/return

|-- MODETANK

Sub RNG_ModeConfigMODETANK
   /varset IsHealing TRUE
   /varset DoTanking TRUE

   |- Spell Gem 1 Is For Our Heal gem from 3 and CHanges over to fast heal @ 89.
      /if ( ${Fastheal.NotEqual[NULL]} ) {
        /varset Spell1 ${Fastheal} 
    } else { 
        /varset Spell1 ${Heal}
    }
    | - SpellGem2 - Is Our Standard Fire Nuke 3-115
    /varset Spell2 ${Firenuke}
    | - SpellGem 3 - This is Our Swarm Dot From 25 to 115
    /if ( ${Fireboon.NotEqual[NULL]} ) {
         /varset Spell3 ${Fireboon}
    } else { 
        /varset Spell3 ${ShortSwarmDot}
    }
    /if ( ${ArrowOpener.NotEqual[NULL]}) {
        /varset Spell4 ${ArrowOpener} 
    } else { 
        /varset Spell4 ${SnareSpells}
    }
    /varset Spell5 ${DichoSpell}
    /varset Spell6 ${CalledShotsArrow}
    /varset Spell7 ${FocusedArrows}
    /varset Spell8 ${Heartshot}
    /varset Spell9 ${SummerNuke}
    /if ( ${Fireboon.NotEqual[NULL]} ) {
        /if ( ${Me.Level} > 82  ) {
            /varset Spell10 ${ShortSwarmDot} 
            /varset SwarmDot ${ShortSwarmDot} 
            } else {
            /varset Spell10 ${SwarmDot} 
        }
    }
    /varset Spell11 ${Iceboon}
    /varSet Spell12 ${Icenuke}  
    /varset Spell13 ${Alliance}  


    /call RNG_DefaultDPSRotationConfig RNG_DPS_MODETANK_Rotation DoTanking
    /call RNG_DefaultBurnRotationConfig RNG_Burn_MODETANK_Rotation
    /call RNG_TankDownRotationConfig RNG_Downtime_MODETANK_Rotation
    /call RNG_DefaultHealRotationConfig
    /call RNG_DefaultGroupBuffConfig

/return



Sub RNG_ModeConfigMODETLP
   /varset IsHealing TRUE

   |- Spell Gem 1 Is For Our Heal gem from 3 and CHanges over to fast heal @ 89.
      /if ( ${Fastheal.NotEqual[NULL]} ) {
        /varset Spell1 ${Fastheal} 
    } else { 
        /varset Spell1 ${Heal}
    }
    | - SpellGem2 - Is Our Standard Fire Nuke 3-115
    /varset Spell2 ${Firenuke}
    | - SpellGem3 - Is Our Standard Ice Nuke 3-115
    /varset Spell2 ${Icenuke}
    | - SpellGem 3 - This is Our Swarm Dot From 25 to 115
    /if ( ${Fireboon.NotEqual[NULL]} ) {
         /varset Spell4 ${Fireboon}
    } else { 
        /varset Spell4 ${SwarmDot}
    }
    /varset Spell5 ${Mask}
    /if ( ${ArrowOpener.NotEqual[NULL]}) {
        /varset Spell4 ${ArrowOpener} 
    } else { 
        /varset Spell4 ${SnareSpells}
    }
    /varset Spell6 ${Eyes}
    /varset Spell7 ${GroupPredatorBuff}
    /varset Spell8 ${GroupStrengthBuff}
    /varset Spell9 ${MoveSpells}

    |- Self buff rotation
    /if (${Spell[${ParryProcBuff}].Level}<=${Spell[${Me.AltAbility[Wildstalker's Unity (Beza)].Spell.Trigger[1].BaseName}].Level} ) {
        /call AddToRotation RNG_Downtime_MODETLP_Rotation "Wildstalker's Unity (Beza)" AA ${Parse[0,"( !${Me.Buff[${Me.AltAbility[Wildstalker's Unity (Beza)].Spell.Trigger[1].BaseName}].ID} && ${Spell[${Me.AltAbility[Wildstalker's Unity (Beza)].Spell.Trigger[1].BaseName}].Stacks} )"]}
    } else { 
        /call AddToRotation RNG_Downtime_MODETLP_Rotation "${ParryProcBuff}"  Spell          ${Parse[0,"(SELFBUFFCHECK)"]}
        /call AddToRotation RNG_Downtime_MODETLP_Rotation "${hunt}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}
        /call AddToRotation RNG_Downtime_MODETLP_Rotation "${Protectionbuff}" Spell      ${Parse[0,"(SELFBUFFCHECK)"]}
        /call AddToRotation RNG_Downtime_MODETLP_Rotation "${Eyes}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}
        /call AddToRotation RNG_Downtime_MODETLP_Rotation "${Coat}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}    
        /call AddToRotation RNG_Downtime_MODETLP_Rotation "${Mask}"              Spell    ${Parse[0,"(SELFBUFFCHECK)"]}    
        /call AddToRotation RNG_Downtime_MODETLP_Rotation "Elemental Arrow" AA    ${Parse[0,"(SELFBUFFCHECK)"]}        
    }
    /call AddToRotation RNG_Downtime_MODETLP_Rotation "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation RNG_Downtime_MODETLP_Rotation "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    /call AddToRotation RNG_Downtime_MODETLP_Rotation "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==1 && ${Me.Mount.ID} && ${DoMelee[SETTINGVAL]} )"]}
    /call AddToRotation RNG_Downtime_MODETLP_Rotation "Poison Arrows" AA ${Parse[0,"( ${DoPoisonArrow[SETTINGVAL]} && !${Me.Buff[Poison Arrows].ID}  )"]}
        
    | - Burn AA Rotation
/if (!${Me.HaveExpansion[Dragons of Norrath]} && ${Me.HaveExpansion[Omens of War]}) {
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "Guardian of the Forest" AA ${Parse[0,"( ${BurnAuto[SETTINGVAL]} || MEDBURN )"]}
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "Mass Group Buff" AA     ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && ${RG_AAReady[Auspice of the Hunter]}  )"]} 
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "Auspice of the Hunter" AA ${Parse[0,"( ${BurnAuto[SETTINGVAL]} ||| BIGBURN )"]}
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "${BowDisc}" Disc     ${Parse[0,"( ( ${BurnAuto[SETTINGVAL]} || BIGBURN ) && !${DoMelee[SETTINGVAL]} )"]} 
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "${SummerNuke}" Spell  ${Parse[0,"( ( !${Me.ActiveDisc.ID} && ${Target.PctHPs}>20 )"]}
    } else {
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "Scarlet Cheetah's Fang" AA TRUE
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "Scout's Mastery of the Elements" AA TRUE
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "Guardian of the Forest" AA TRUE
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "Outrider's Accuracy" AA TRUE
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "Group Guardian of the Forest" AA TRUE
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "Outrider's Attack" AA TRUE
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "Imbued Ferocity" AA TRUE
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "Auspice of the Hunter" AA TRUE
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "${BowDisc}" Disc ${Parse[0,"( !${DoMelee[SETTINGVAL]} )"]}
    /call AddToRotation  RNG_Burn_MODETLP_Rotation "${MeleeDisc}" Disc ${Parse[0,"( ${DoMelee[SETTINGVAL]} )"]}

}
    |- Setup heals
    /call Heal_AddHealPoint     ${HealPoint[SETTINGVAL]}
    |- Light Heal Point Spells
    /call Heal_AddSpell             ${HealPoint[SETTINGVAL]} "${Heal}" ${Parse[0,"( ${Me.Level} < 111  )"]}
    /call Heal_AddSpell            ${HealPoint[SETTINGVAL]} "${Fastheal}" ${Parse[0,"( ${Me.Level} < 114  )"]}

    |- DPS Rotation
    /if (${RG_CanUseAA[Entrap]}) {
        /call AddToRotation RNG_DPS_MODETLP_Rotation "Entrap" AA ${Parse[0,"( ${DoSnare[SETTINGVAL]} && ${Target.PctHPs} < 50 && DETAACHECK )"]}
    } else {
        /call AddToRotation RNG_DPS_MODETLP_Rotation "${SnareSpells}" Spell ${Parse[0,"( ${DoSnare[SETTINGVAL]} && ${Target.PctHPs} < 50 && DETSPELLCHECK )"]}
    }
    
    /call AddToRotation RNG_DPS_MODETLP_Rotation "${Epic}" Item ${Parse[0,"( ${DoEpic[SETTINGVAL]} )"]}
    /call AddToRotation RNG_DPS_MODETLP_Rotation "${CalledShotsArrow}" Spell ${Parse[0,"( !${Target.Buff[Called Shots Effect].ID} )"]}
    /call AddToRotation RNG_DPS_MODETLP_Rotation "${FocusedArrows}" Spell ${Parse[0,"( ${Target.Buff[Called Shots Effect].ID} )"]}
    /call AddToRotation RNG_DPS_MODETLP_Rotation "${DichoSpell}" Spell  ${Parse[0,"( ${Target.Buff[Called Shots Effect].ID} )"]}
    /call AddToRotation RNG_DPS_MODETLP_Rotation "${Heartshot}" Spell  ${Parse[0,"( ${DoReagentArrow[SETTINGVAL]} && ${Target.Buff[Called Shots Effect].ID} )"]}
    /call AddToRotation RNG_DPS_MODETLP_Rotation "${Fireboon}" Spell  ${Parse[0,"( !${Me.Buff[${FireBoonbuff}].ID} )"]}
    /if (${Me.Level}<98) {
        /call AddToRotation RNG_DPS_MODETLP_Rotation "${Firenuke}" Spell ${Parse[0,"( (${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
        /call AddToRotation RNG_DPS_MODETLP_Rotation "${Icenuke}" Spell ${Parse[0,"( (${BurnAuto[SETTINGVAL]} || SMALLBURN ) && ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    } else { 
        /call AddToRotation RNG_DPS_MODETLP_Rotation "${Firenuke}" Spell ${Parse[0,"( ${Me.Buff[${FireBoonbuff}].ID} && ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
    }

    /call AddToRotation RNG_DPS_MODETLP_Rotation "${Totheal}" Spell     ${Parse[0,"( ${Me.TargetOfTarget.PctHPs}<${HealPoint[SETTINGVAL]})"]}
    /call AddToRotation RNG_DPS_MODETLP_Rotation "Elemental Arrow" AA    TRUE        
    /call AddToRotation RNG_DPS_MODETLP_Rotation "${JoltingKicks}" Disc ${Parse[0,"( ${Target.Distance}<=50 && !${Me.Moving} )"]}
    /call AddToRotation RNG_DPS_MODETLP_Rotation "${AEBlades}" Disc ${Parse[0,"( ${Target.Distance}<=50 && !${Me.Moving} && ${DoAoe[SETTINGVAL]} )"]}
    /call AddToRotation RNG_DPS_MODETLP_Rotation "${FocusedBlades}" Disc ${Parse[0,"( ${Target.Distance}<=50 && !${Me.Moving} )"]}
    /call AddToRotation RNG_DPS_MODETLP_Rotation "${ReflexSlashHeal}"  Disc ${Parse[0,"( ${Target.Distance}<=${Target.MaxRangeTo} && ${Me.Combat} )"]}
    |- Group Buffs
    
    /call BuffGroup_Init 5
    /call BuffGroup_Set 1 "${GroupStrengthBuff}" 
    /call BuffGroup_Set 2 "${GroupPredatorBuff}" 
    /call BuffGroup_Set 3 "${GroupEnrichmentBuff}"
    /call BuffGroup_Set 4 "${MoveSpells}" "ALL" "${Parse[0, ${DoRunSpeed[SETTINGVAL]}]}"
    /call BuffGroup_Set 5 "${Rathe}" "War,shd,pal" TRUE
/return


Sub RNG_Combat_Routine
    |- Check for Ranged Dps Mode
    /if (!${DoMelee[SETTINGVAL]}) {
        /if (!${Me.Combat} && !${Me.AutoFire} ) /call RNG_PreEngageRoutine
    }
    
    /if ( DODPS ) {
        /if (!${DoMelee[SETTINGVAL]}) {
            /if (!${Me.AutoFire} && !${DoMelee[SETTINGVAL]}) {
                /squelch    /face
                /squelch    /autofire on
            }
            /if (${NavCircle[SETTINGVAL]} &&  (${Target.Distance}<=30 || ${Target.Distance}>=75)) {
                    /call NavAroundCircle ${Target.ID} 45 TRUE
            }     
            /if (!${NavCircle[SETTINGVAL]} && ${Target.Distance}<=30) {
                /stick 45 moveback
            }
            /if (!${NavCircle[SETTINGVAL]} && ${Target.Distance}>=75) {
                /squelch /nav id ${autotargetid} |Distance=45
                }
        }

        /if (!${Me.AutoFire} && !${DoMelee[SETTINGVAL]}) {
                /squelch    /face
                /squelch    /autofire on
        }
        /if ( BURNCHECK ) {
            /if (!${Me.AutoFire} && !${DoMelee[SETTINGVAL]}) {
                /squelch    /face
                /squelch    /autofire on
            }
            /call Ordered_Rotation_Follow ${Me.Class.ShortName}_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        }
        /if (!${Me.AutoFire} && !${DoMelee[SETTINGVAL]}) {
                /squelch    /face
                /squelch    /autofire on
        }
        /call Ordered_Rotation_Follow ${Me.Class.ShortName}_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }    
/return ${Macro.Return}

|----------------------------------------------------------------------------
|- SUB: Opening Move
|---------------------------------------------------------------------------- 
Sub RNG_PreEngageRoutine
    /if (${DoOpener[SETTINGVAL]} && ${Me.PctMana}>=${Manatonuke[SETTINGVAL]}) {
        /if (${NPCSpellReady[${ArrowOpener}]}) {
            /squelch /face 
            /call SpellNow "${ArrowOpener}" ${autotargetid}
        }
    }    
/return

Sub RNG_Downtime_Routine
    |- Call Self buffs
    |- Arrow Reagent Check
    /if  (${FindItem[CLASS 3 Wood Silver Tip Arrow].StackCount} && !${DoReagentArrow[SETTINGVAL]}) {
        /call RGChangeSetting RNG DoReagentArrow 1
        /call PrintGroupMessage "I Have Arrows In My bags So I am Going to use Heartshot & Silent Shot! Until I run out!"
    } else /if (!${FindItem[CLASS 3 Wood Silver Tip Arrow].StackCount} && ${DoReagentArrow[SETTINGVAL]}) { 
        /call RGChangeSetting RNG DoReagentArrow 0
        /call PrintGroupMessage "I Have Run Out of Arrows for Openers - Try /makeammo 100 to make More Class 3 Wood Silver tip Arrows."
    }
        /call FollowRotation  ${Me.Class.ShortName}_Downtime_${ClassMode[SETTINGVAL]}_Rotation  ${Me.ID}
/return ${Macro.Return}

Sub RNG_Heal_Routine
    |- If we're a member of a group, heal our group first.
    /call HealNow ${WorstHurtGroup[${HealPoint_MaxPoint}]}
    
    |- Now check xtargets.
    /if (${AssistOutside[SETTINGVAL]}) {
        /call HealNow ${WorstHurtXT[${HealPoint_MaxPoint}]}
        |- In case we pissed someone off
        /if (${Me.PctHPs} <= ${HealPoint_MaxPoint} ) {
            /call HealNow ${Me.ID}
        }
    }     
/return ${Macro.Return}

#bind makeammo /makeammo
| - makes Ammo for Special Opener Shows - /makeammo # makes that many arrows.
Sub Bind_makeammo(int amount)
    /declare Combined            int    local     0
    /declare Slot                int    local    0
    /declare IngredientSlot1    int    local    0
    /declare IngredientSlot2    int    local    0
    /declare IngredientSlot3    int    local    0
    /declare IngredientSlot4    int    local    0
    /declare i                     int local
    
    /cleanup
    /keypress OPEN_INV_BAGS 
|---Determine where our Fletching Kit Is
    /for Slot 1 to 10
        /if (${Me.Inventory[pack${Slot}].Type.Equal[Fletching]}) {
            /if (${Slot} == 1) {
                /echo \ar!!!\awPlease make sure the fletchking kit is not in the first inventory slot, as autoinventory will drop the completed arrows into the bag.\ar!!!
                /return
            } else /if (${Me.Inventory[pack${Slot}].Items}) {
                /echo \ar!!! \awPlease empty out \am${Me.Inventory[pack${Slot}].Name}\ax before starting \ar!!! 
                /return
            } else /break
        }
    /next Slot
    /if (${Slot}==11) {
        /echo could not find a Fletching combiner! In a Top Inventory Slot!
        /return
    }
    |- Start our while loop, Until we have However many arrows specified by typing /makeammo XXX
    /call PrintGroupMessage "Begining Reloading Ammo!  Making ${amount} of Wooden Silver Tipped Arrows - During this time I will Do nothing else."
    /while (${FindItem[CLASS 3 Wood Silver Tip Arrow].StackCount}<${amount}) {
        /varset IngredientSlot1 ${FindItem[Silver Tipped Arrowheads].InvSlot}
        /if (${IngredientSlot1}) {
            /nomodkey /ctrl /itemnotify ${IngredientSlot1} leftmouseup
            /itemn in pack${Slot} 1 leftmouseup
        } else {
            /echo could not find Silver Tipped Arrowheads
            /return
        }
        /delay 1
        /varset IngredientSlot2 ${FindItem[Bundled Wooden Arrow Shafts].InvSlot}
        /if (${IngredientSlot2}) {
            /nomodkey /ctrl /itemnotify ${IngredientSlot2} leftmouseup
            /itemn in pack${Slot} 2 leftmouseup
        } else {
            /echo could not find Bundled Wooden Arrow Shafts
            /return
        }   
        /varset IngredientSlot3 ${FindItem[Several Shield Cut Fletchings].InvSlot}
        /if (${IngredientSlot3}) {
            /nomodkey /ctrl /itemnotify ${IngredientSlot3} leftmouseup
            /itemn in pack${Slot} 3 leftmouseup
        } else {
            /echo could not find Several Shield Cut Fletchings
            /return
        }
        /delay 1    
        /varset IngredientSlot4 ${FindItem[Small Groove Nocks].InvSlot}
        /if (${IngredientSlot4}) {
            /nomodkey /ctrl /itemnotify ${IngredientSlot4} leftmouseup
            /itemn in pack${Slot} 4 leftmouseup
        } else {
            /echo could not find Small Groove Nocks
            /return
        }
        /delay 1    
    | -- Actual Combine
        /delay 25
        /combine pack${Slot}
        /delay 10 ${Cursor.ID}
        /if (${Cursor.ID}) {
            /varset Combined 1
        } else {
            /varset Combined 0
        }
        /delay 1
    
    |-- Cleansup Cursor or emptys kit as needed.
        /if (${Combined}) {
            /while (${Cursor.ID}) {
                /autoinventory
                /delay 2
            }
        } else {
            /for i 1 to ${Me.Inventory[pack${Slot}].Container}
                /if (!${Me.Inventory[pack${Slot}].Item[${i}].ID}) /continue
                |/echo in kit ${i}::${Me.Inventory[pack${Slot}].Item[${i}].ID}
                /nomodkey /shift /itemnotify in pack${Slot} ${i} leftmouseup
                /delay 20 ${Cursor.ID}
                /while (${Cursor.ID}) {
                    /autoinventory
                /delay 2
                }
            /next i
        }
    }
    /call PrintGroupMessage "I Have Made ${amount} Class 3 Wood Silver Tipped Arrows to use with My Openers. Returning to normal Operational Mode."

/return

Sub RNG_PullSetup
     /if (${RG_CanUseAA[Entrap]} && ${DoSnare[SETTINGVAL]}) {
        /call Pull_SetAbility "Entrap" "AA"
    } else /if (${SnareSpells.NotEqual[NULL]} && ${DoSnare[SETTINGVAL]}&&${Me.Gem[${SnareSpells}]}) {
        /call Pull_SetAbility "${SnareSpells}" "Spell"
    } else /if (${Me.Inventory[ranged].Type.Equal[Archery]} && ${Me.Inventory[ammo].Stack} >= 1) {
        /call Pull_SetAbility "pullrange" "Special"
    } 
/return

