|- RGwarutil.inc
|- Version 2.0
|- Updated: 4/25/2019
#define MODETANK 0
#define MODEDPS 1
#define MODETLP 2
#define MODETANK115 10
#define DOTANK  "( ${DoTank[SETTINGVAL]} )"
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub WAR_Setup
    /declare RGList_WAR    list outer


	|- Rotations
	| - Warrior Mode Tank Rotations This section Creates the rotations so u can add to them in the Modeconfig
	| - Mode 0 - Default Mode meant to work from 85-115 Possibly More
	/call Ordered_Rotation_New WAR_Debuff_MODETANK_Rotation
	/call Ordered_Rotation_New WAR_Heal_MODETANK_Rotation
	/call Ordered_Rotation_New WAR_DPS_MODETANK_Rotation
	/call Ordered_Rotation_New WAR_Downtime_MODETANK_Rotation
    /call Ordered_Rotation_New WAR_Burn_MODETANK_Rotation
	| - Mode 1 DPS - Live Mode
	/call Ordered_Rotation_New WAR_Debuff_MODEDPS_Rotation
	/call Ordered_Rotation_New WAR_DPS_MODEDPS_Rotation
	/call Ordered_Rotation_New WAR_Downtime_MODEDPS_Rotation
    /call Ordered_Rotation_New WAR_Burn_MODEDPS_Rotation
	
	| - Mode 2 TLP 
	/call Ordered_Rotation_New WAR_Debuff_MODETLP_Rotation
	/call Ordered_Rotation_New WAR_DPS_MODETLP_Rotation
	/call Ordered_Rotation_New WAR_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New WAR_Burn_MODETLP_Rotation

	| - Mode 10 - Optimized for 115 Tank Mode - Unsupported Oakmuk mode.
	/call Ordered_Rotation_New WAR_Debuff_MODETANK115_Rotation
	/call Ordered_Rotation_New WAR_Heal_MODETANK115_Rotation
	/call Ordered_Rotation_New WAR_DPS_MODETANK115_Rotation
	/call Ordered_Rotation_New WAR_Downtime_MODETANK115_Rotation
    /call Ordered_Rotation_New WAR_Burn_MODETANK115_Rotation

|- Items
    /call ItemSet_New Epic  

|-Declare Discs
	/call AbilitySet_New meleemit		
	/call AbilitySet_New missall		
	/call AbilitySet_New absorball		
	/call AbilitySet_New parryall		
	/call AbilitySet_New shieldhit		
	/call AbilitySet_New groupac		
	/call AbilitySet_New groupdodge		
	/call AbilitySet_New defenseac		
	/call AbilitySet_New bmdisc			
	/call AbilitySet_New aeroar			
	/call AbilitySet_New aeselfbuff		
	/call AbilitySet_New aehealhate		
	/call AbilitySet_New singlehealhate	
	/call AbilitySet_New aehitall		
	/call AbilitySet_New AddHate1		
	/call AbilitySet_New AddHate2		
	/call AbilitySet_New Taunt1			
	/call AbilitySet_New StrikeDisc		
	/call AbilitySet_New endregen		
	/call AbilitySet_New waraura		
	/call AbilitySet_New AgroLock
	/call AbilitySet_New AgroPet
	/call AbilitySet_New OnslaughtDisc
	/call AbilitySet_New RuneShield

	/declare ItemOoWBP		string outer NULL
	/declare ItemDipPapers	string outer NULL
|-Config Options
	/call LoadCommonConfig
	/varset ClassMode[SETTINGDESC] Set 0 = Tank Set 1 = DPS
    /call RGLoadSetting WAR DoAeHate 0 Buffs "Set 0/1 to use AE Hate Buffs."
    /call RGLoadSetting WAR DoAEAggro 0 Combat "Set 0/1 to use AE Aggro Abilities.."
    /call RGLoadSetting WAR DoBattleLeap 1 Combat "Set 0/1 to use battle leap.."
    /call RGLoadSetting WAR DoDefense 1 Combat "Set 0/1 to use Defense abilities."
    /call RGLoadSetting WAR DoAutoPDH 1 Options "Set 0/1 to use well known defensive clickie items."
    /call RGLoadSetting WAR SummonArrows 1 Options "Set 0/1 to AutoSummon Arrows or Not with Huntsman's quiver"
	/call RGLoadSetting WAR DoBandolier 0 Options "Set 0/1 to use auto bandolier functions. Requires a bandolier called Shield (a shield and 1hd weapon) and one called Agro (2 1hd weapons)"
	/call RGLoadSetting WAR DoSnare 1 Options "Set 0/1 to use Call Challenege AA for Snare."
	/call RGLoadSetting WAR DoTank 1 Combat "Set 1/0 to turn on Tanking - TLP Mode Only"
	
	/if (${FindItem[Gladiator's Plate Chestguard of War].ID}) /varset ItemOoWBP Gladiator's Plate Chestguard of War
	/if (${FindItem[Diplomatic Papers].ID}) /varset ItemDipPapers Diplomatic Papers
/return 

|----------------------------------------------------------------------------
|- SUB: CheckOptions
|---------------------------------------------------------------------------- 
Sub WAR_CheckOptions
	/if (${IsTanking} || ${DoTank[SETTINGVAL]} ) {
		/varset AutoAssistAt[SETTINGVAL] 100
		/varset DoAutoTarget[SETTINGVAL] 1
		/varset DoAutoEngage[SETTINGVAL] 1
		/varset AllowMezBreak[SETTINGVAL] 1
		/varset StickHow[SETTINGVAL] 15 moveback
		/varset DoMelee[SETTINGVAL] 1
		/varset StayOnTarget[SETTINGVAL] 0
		/if (${Me.AltAbility[692].Name.Find[disabled]} && ${RG_AAReady[692]}) {
			/alt act 692
			/delay 2s
		}
		/if (${Me.AltAbility[684].Name.Find[disabled]} && ${RG_AAReady[684]}) {
			/alt act 684
			/delay 2s
		}
		/if (${Me.AltAbility[1126].Name.Find[disabled]} && ${RG_AAReady[1126]}) {
			/alt act 1126
			/delay 2s
		}
		/if (${Me.AltAbility[2001].Name.Find[disabled]} && ${RG_AAReady[2001]}) {
			/alt act 2001
			/delay 2s
		}
	} else {
		/varset AutoAssistAt[SETTINGVAL] 98
		/varset DoAutoTarget[SETTINGVAL] 1
		/varset DoAutoEngage[SETTINGVAL] 1
		/varset AllowMezBreak[SETTINGVAL] 0
		/varset StickHow[SETTINGVAL] snaproll !front 15 moveback uw
		/varset DoMelee[SETTINGVAL] 1
		/varset StayOnTarget[SETTINGVAL] 1
		/if (${Me.AltAbility[692].Name.Find[enabled]} && ${RG_AAReady[692]}) {
			/alt act 692
			/delay 2s
		}
		/if (${Me.AltAbility[684].Name.Find[enabled]} && ${RG_AAReady[684]}) {
			/alt act 684
			/delay 2s
		}
		/if (${Me.AltAbility[1126].Name.Find[enabled]} && ${RG_AAReady[1126]}) {
			/alt act 1126
			/delay 2s
		}
		/if (${Me.AltAbility[2001].Name.Find[enabled]} && ${RG_AAReady[2001]}) {
			/alt act 2001
			/delay 2s
		}		
	}
/return

|----------------------------------------------------------------------------
|- SUB: SetupDiscs
|---------------------------------------------------------------------------- 
Sub WAR_SetupSkills
	|- Items
	|- Epic
	/call ItemSet_Add "Kreljnok's Sword of Eternal Power" Epic
	/call ItemSet_Add "Champion's Sword of Eternal Power" Epic
	/call ItemSet_ChooseOuter Epic Epic

	
	|--One off discs
	|- Fortitude
	/call AbilitySet_Add "Fortitude Discipline"	missall
	/call AbilitySet_ChooseOuter missall missall

	|-Flash
	/call AbilitySet_Add "Flash of Anger"		parryall
	/call AbilitySet_ChooseOuter parryall parryall

	|- Commanding Voice
	/call AbilitySet_Add "Commanding Voice"		groupdodge
	/call AbilitySet_ChooseOuter groupdodge groupdodge

	|-Wade
	/call AbilitySet_Add "Wade into Battle"		aeselfbuff
	/call AbilitySet_Add "Wade into Conflict"	aeselfbuff
	/call AbilitySet_ChooseOuter aeselfbuff aeselfbuff

	|- Dicho
	/call AbilitySet_Add "Ecliptic Shield" 		bmdisc
	/call AbilitySet_Add "Composite Shield"		bmdisc
	/call AbilitySet_Add "Dissident Shield"		bmdisc
	/call AbilitySet_Add "Dichotomic Shield" 	bmdisc
	/call AbilitySet_ChooseOuter bmdisc bmdisc

	|- Absorball Ability
	/call AbilitySet_Add "Finish the Fight"		absorball
	/call AbilitySet_Add "Pain Doesn't Hurt"		absorball
	/call AbilitySet_Add "No Time to Bleed"		absorball
	/call AbilitySet_ChooseOuter absorball absorball

	|- Precision
	/call AbilitySet_Add "Penumbral Precision"	singlehealhate
	/call AbilitySet_Add "Confluent Precision"	singlehealhate
	/call AbilitySet_Add "Concordant Precision"	singlehealhate
	/call AbilitySet_Add "Harmonious Precision"	singlehealhate
	/call AbilitySet_ChooseOuter singlehealhate singlehealhate

	|- Expanse
	/call AbilitySet_Add "Penumbral Expanse" 	aehealhate
	/call AbilitySet_Add "Confluent Expanse"	aehealhate
	/call AbilitySet_Add "Concordant Expanse"	aehealhate
	/call AbilitySet_Add "Harmonious Expanse"	aehealhate
	/call AbilitySet_ChooseOuter aehealhate aehealhate

	|---Melee Mitigation Disc
	/call AbilitySet_Add "Climactic Stand" meleemit
	/call AbilitySet_Add "Resolute Stand"	meleemit
	/call AbilitySet_Add "Ultimate Stand Discipline"		meleemit
	/call AbilitySet_Add "Culminating Stand Discipline"	meleemit
	/call AbilitySet_Add "Last Stand Discipline"			meleemit
	/call AbilitySet_Add "Final Stand Discipline"		meleemit
|	/call AbilitySet_Add "Stonewall Discipline"			meleemit
	/call AbilitySet_Add "Defensive Discipline"			meleemit
	/call AbilitySet_ChooseOuter meleemit meleemit

	|---Defense AC Disc
	/call AbilitySet_Add "Vigorous Defense"		defenseac
	/call AbilitySet_Add "Primal Defense"		defenseac
	/call AbilitySet_Add "Courageous Defense"	defenseac
	/call AbilitySet_Add "Resolute Defense"		defenseac
	/call AbilitySet_Add "Stout Defense"			defenseac
	/call AbilitySet_Add "Steadfast Defense"		defenseac
	/call AbilitySet_Add "Stalwart Defense"		defenseac
	/call AbilitySet_Add "Staunch Defense"		defenseac
	/call AbilitySet_Add "Bracing Defense"		defenseac
	/call AbilitySet_ChooseOuter defenseac defenseac

	|---Group AC Disc
	/call AbilitySet_Add "Field Bulwark"		groupac
	/call AbilitySet_Add "Full Moon's Champion"	groupac
	/call AbilitySet_Add "Paragon Champion"		groupac
	/call AbilitySet_Add "Field Champion"		groupac
	/call AbilitySet_Add "Field Protector"		groupac
	/call AbilitySet_Add "Field Guardian"		groupac
	/call AbilitySet_Add "Field Defender"		groupac
	/call AbilitySet_Add "Field Outfitter"		groupac
	/call AbilitySet_Add "Field Armorer"			groupac
	/call AbilitySet_ChooseOuter groupac groupac
	
	|---AddHate1
	/call AbilitySet_Add "Mortimus' Roar"			AddHate1
	/call AbilitySet_Add "Namdrows' Roar"			AddHate1
	/call AbilitySet_Add "Kragek's Roar"			AddHate1
	/call AbilitySet_Add "Kluzen's Roar"			AddHate1
	/call AbilitySet_Add "Cyclone Roar"				AddHate1
	/call AbilitySet_Add "Krondal's Roar"			AddHate1
	/call AbilitySet_Add "Grendlaen Roar"			AddHate1
	/call AbilitySet_Add "Bazu Roar"				AddHate1
	/call AbilitySet_Add "Ancient: Chaos Cry"		AddHate1
	/call AbilitySet_Add "Bazu Bluster"				AddHate1
	/call AbilitySet_Add "Bazu Bellow"				AddHate1
	/call AbilitySet_Add "Bellow of the Mastruq"	AddHate1
	/call AbilitySet_Add "Incite"					AddHate1
	/call AbilitySet_Add "Berate"					AddHate1
	/call AbilitySet_Add "Bellow"					AddHate1
	/call AbilitySet_Add "Provoke"					AddHate1
	/call AbilitySet_ChooseOuter AddHate1 AddHate1

	|---AE Taunt
	/call AbilitySet_Add "Roar of Challenge"		aeroar
	/call AbilitySet_Add "Rallying Roar"			aeroar
	/call AbilitySet_ChooseOuter aeroar aeroar

	|---AddHate2
	/call AbilitySet_Add "Distressing Shout" AddHate2
	/call AbilitySet_Add "Twilight Shout"	AddHate2
	/call AbilitySet_Add "Oppressing Shout"		AddHate2
	/call AbilitySet_Add "Burning Shout"			AddHate2
	/call AbilitySet_Add "Tormenting Shout"		AddHate2
	/call AbilitySet_Add "Harassing Shout"		AddHate2
	/call AbilitySet_ChooseOuter AddHate2 AddHate2
	|-Wade
	/call AbilitySet_Add "Phantom Aggressor"		AgroPet
	/call AbilitySet_ChooseOuter AgroPet AgroPet

	|---Agro Lock
	/call AbilitySet_Add "Unending Attention"		 AgroLock
	/call AbilitySet_Add "Unyielding Attention"		 AgroLock
	/call AbilitySet_Add "Unflinching Attention"	 AgroLock
	/call AbilitySet_Add "Unbroken Attention"		 AgroLock
	/call AbilitySet_Add "Undivided Attention"		 AgroLock
	/call AbilitySet_Add "Unrelenting Attention"	 AgroLock
	/call AbilitySet_Add "Unconditional Attention"   AgroLock
	/call AbilitySet_ChooseOuter AgroLock AgroLock
	
	|---Taunt1
	/call AbilitySet_Add "Infuriate"	Taunt1
	/call AbilitySet_Add "Bristle"		Taunt1
	/call AbilitySet_Add "Aggravate"	Taunt1
	/call AbilitySet_Add "Slander"		Taunt1
	/call AbilitySet_Add "Insult"		Taunt1
	/call AbilitySet_Add "Ridicule"		Taunt1
	/call AbilitySet_Add "Scorn"		Taunt1
	/call AbilitySet_Add "Scoff"		Taunt1
	/call AbilitySet_Add "Jeer"			Taunt1
	/call AbilitySet_Add "Sneer"		Taunt1
	/call AbilitySet_Add "Scowl"		Taunt1
	/call AbilitySet_Add "Mock"			Taunt1
	/call AbilitySet_ChooseOuter Taunt1 Taunt1

	|---Strike
	/call AbilitySet_Add "Decisive Strike"			StrikeDisc
	/call AbilitySet_Add "Precision Strike"			StrikeDisc
	/call AbilitySet_Add "Cunning Strike"			StrikeDisc
	/call AbilitySet_Add "Calculated Strike"		StrikeDisc
	/call AbilitySet_Add "Vital Strike"				StrikeDisc
	/call AbilitySet_Add "Strategic Strike"			StrikeDisc
	/call AbilitySet_Add "Opportunistic Strike"		StrikeDisc
	/call AbilitySet_Add "Exploitive Strike"		StrikeDisc
	/call AbilitySet_ChooseOuter StrikeDisc StrikeDisc

	|---AE Hit all
	/call AbilitySet_Add "Tempest Blades"		aehitall
	/call AbilitySet_Add "Dragonstrike Blades"	aehitall
	/call AbilitySet_Add "Stormstrike Blades"	aehitall
	/call AbilitySet_Add "Stormwheel Blades"	aehitall
	/call AbilitySet_Add "Cyclonic Blades"		aehitall
	/call AbilitySet_Add "Wheeling Blades"		aehitall
	/call AbilitySet_Add "Maelstrom Blade"		aehitall
	/call AbilitySet_Add "Whorl Blade"			aehitall
	/call AbilitySet_Add "Vortex Blade"			aehitall
	/call AbilitySet_Add "Cyclone Blade"		aehitall
	/call AbilitySet_Add "Whirlwind Blade"		aehitall
	/call AbilitySet_Add "Hurricane Blades"		aehitall
	/call AbilitySet_Add "Spiraling Blades"		aehitall
	/call AbilitySet_ChooseOuter aehitall aehitall

	|--- Shield Hit and Block
	/call AbilitySet_Add "Shield Sunder"	shieldhit
	/call AbilitySet_Add "Shield Break"		shieldhit
	/call AbilitySet_Add "Shield Topple"	shieldhit
	/call AbilitySet_Add "Shield Splinter"	shieldhit
	/call AbilitySet_Add "Shield Rupture" 	shieldhit
	/call AbilitySet_ChooseOuter shieldhit shieldhit

	|---Fast Endurance regen
	/call AbilitySet_Add "Convalesce" 		endregen
	/call AbilitySet_Add "Night's Calming"	endregen
	/call AbilitySet_Add "Hiatus"			endregen
	/call AbilitySet_Add "Breather"			endregen
	/call AbilitySet_Add "Rest"				endregen
	/call AbilitySet_Add "Reprieve"			endregen
	/call AbilitySet_Add "Respite"			endregen
	/call AbilitySet_Add "Fourth Wind"		endregen
	/call AbilitySet_Add "Third Wind"		endregen
	/call AbilitySet_Add "Second Wind"		endregen
	/call AbilitySet_ChooseOuter endregen endregen

	|---Aura usage
	/call AbilitySet_Add "Champion's Aura"		waraura
	/call AbilitySet_Add "Myrmidon's Aura"		waraura
	/call AbilitySet_ChooseOuter waraura waraura

	| - Onslaught Disc
	/call AbilitySet_Add "Savage Onslaught Discipline" OnslaughtDisc
	/call AbilitySet_Add "Brutal Onslaught Discipline" OnslaughtDisc
	/call AbilitySet_Add "Brightfeld's Onslaught Discipline" OnslaughtDisc
	/call AbilitySet_ChooseOuter OnslaughtDisc OnslaughtDisc

	| - Warriors Rampart
	/call AbilitySet_Add "Warrior's Resolve" RuneShield
	/call AbilitySet_Add "Warrior's Rampart" RuneShield
	/call AbilitySet_Add "Warrior's Aegis"	RuneShield
	/call AbilitySet_ChooseOuter RuneShield RuneShield

/return

Sub WAR_ModeConfigMODETANK
	/varset IsTanking TRUE

	|- Rotations
	|- Downtime Rotation
	/call AddToRotation WAR_Downtime_MODETANK_Rotation "${defenseac}" 				"Disc" 		${Parse[0,"( !${Me.ActiveDisc.ID} && ${PCDiscReady[${defenseac}]} )"]}
	/call AddToRotation WAR_Downtime_MODETANK_Rotation "${waraura}" 				"Disc" 		${Parse[0,"( !${Spell[${Me.Aura[1]}].ID} && ${Me.CombatAbility[${Spell[${waraura}].RankName}]} && ${Me.PctEndurance}>10 )"]}
    /call AddToRotation WAR_Downtime_MODETANK_Rotation "${groupac}" 				"Disc" 		${Parse[0,"( ${PCDiscReady[${groupac}]} && !${Me.Song[${Spell[${groupac}].BaseName}].ID} )"]}
	/call AddToRotation WAR_Downtime_MODETANK_Rotation "${groupdodge}"  			"Disc" 		${Parse[0,"( ${PCDiscReady[${groupdodge}]} && !${Me.Song[Commanding Voice].ID} )"]}
	/call AddToRotation WAR_Downtime_MODETANK_Rotation "${endregen}" 				"Disc" 		${Parse[0,"( ${Me.PctEndurance}<15 && ${PCDiscReady[${endregen}]} )"]}  
	/call AddToRotation WAR_Downtime_MODETANK_Rotation "/autoinventory" 			"Command" 	${Parse[0,"( ${Cursor.ID}  && ${Cursor.ID}==121336)"]}
	/call AddToRotation WAR_Downtime_MODETANK_Rotation "Huntsman's Ethereal Quiver" "Item" 		${Parse[0,"( ${FindItemCount[Huntsman's Ethereal Quiver]} && ${FindItemCount[Ethereal Arrow]}<1 && ${SummonArrows[SETTINGVAL]}  )"]}
	/call AddToRotation WAR_Downtime_MODETANK_Rotation "${MountItem[SETTINGVAL]}" 	"Item"  	${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation WAR_Downtime_MODETANK_Rotation "/dismount" 					"Command"   ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
	
	| - Burn Rotation( Named or More Than BurnCount Variable will trigger- Unless Specific for Named IE Single Big Nukes etc..)
	/call AddToRotation WAR_Burn_MODETANK_Rotation "${meleemit}"  	    	"Disc"	${Parse[0,"( ${PCDiscReady[${meleemit}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "${parryall}" 	    	"Disc"	${Parse[0,"( ${PCDiscReady[${parryall}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "${missall}"   	    	"Disc"	${Parse[0,"( ${PCDiscReady[${missall}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]}
	/call AddToRotation WAR_Burn_MODETANK_Rotation "${bmdisc}"           	"Disc"	${Parse[0,"( ${PCDiscReady[${bmdisc}]} && ${Me.PctEndurance}>20 && !${Me.Buff[bmdisc].ID} )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "Brace for Impact"    	"AA" 	${Parse[0,"( ${PCAAReady[Brace For Impact]} )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "Imperator's Command" 	"AA" 	${Parse[0,"( ${PCAAReady[Imperator's Command]} )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "${aehealhate}" 			"Disc" 	${Parse[0,"( ${PCDiscReady[${aehealhate}]} && !${Me.Buff[${aehealhate}].ID} && !${Me.Buff[${aeselfbuff}].ID} && ${Me.PctEndurance}>10 )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "${aeselfbuff}" 			"Disc" 	${Parse[0,"( ${PCDiscReady[${aeselfbuff}]} && !${Me.Buff[${aehealhate}].ID} && !${Me.Buff[${aeselfbuff}].ID} && ${Me.PctEndurance}>10 )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "Warlord's Bravery"   	"AA" 	${Parse[0,"( ${PCAAReady[Warlord's Bravery]} )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "Warlord's Tenacity"  	"AA" 	${Parse[0,"( ${PCAAReady[Warlord's Tenacity]} )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "Warlord's Resurgence"	"AA" 	${Parse[0,"( ${PCAAReady[Warlord's Resurgence]} )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "Warlord's Fury"  		"AA" 	${Parse[0,"( ${NPCAAReady[Warlord's Fury]} )"]}
	/call AddToRotation WAR_Burn_MODETANK_Rotation "War Sheol's Heroic Blade" "AA" 	${Parse[0,"( ${NPCAAReady[War Sheol's Heroic Blade]} )"]} 
	
	| - TankMode DPS Aggro Rotation 
	| - AOE Aggro Abilities.
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${aeroar}" 					"Disc" 		${Parse[0,"( ( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} ) && ${PCDiscReady[${aeroar}]} && ${DoAEAggro[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${aehitall}" 				"Disc"		${Parse[0,"( ( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} ) && ${PCDiscReady[${aehitall}]} && ${DoAEAggro[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Area Taunt" 					"AA" 		${Parse[0,"( ( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} ) && ${NPCAAReady[Area Taunt]} && ${DoAEAggro[SETTINGVAL]} )"]} 	

	| - Single Target Aggro Rotation
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${endregen}" 				"Disc" 		${Parse[0,"( ${Me.PctEndurance}<15 && ${PCDiscReady[${endregen}]} )"]}  
	/call AddToRotation WAR_DPS_MODETANK_Rotation "/bandolier activate Shield" 	"Command" 	${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Shield].Active} && ${Bool[${Me.Bandolier[Shield].Index}]} && BURNCHECK )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "/bandolier activate Agro" 	"Command" 	${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Agro].Active} && ${Bool[${Me.Bandolier[Agro].Index}]} && ${XAssist.XTFullHaterCount}<${BurnMobCount[SETTINGVAL]} && !${Target.Named} )"]}
| - /call AddToRotation WAR_DPS_MODETANK_Rotation "${missall}" "Disc" ${Parse[0,"( ${Target.ID}==${Spawn[=Anashti Sul, Damsel of Decay].ID} && ${PCDiscReady[${missall}]} && ${Target.PctHPs}<=36 )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Taunt" 						"Ability" 	${Parse[0,"( ${Me.AbilityReady[Taunt]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]}
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${AgroLock}" 				"Disc" 		${Parse[0,"( ${PCDiscReady[${AgroLock}]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${Taunt1}" 					"Disc" 		${Parse[0,"( ${PCDiscReady[${Taunt1}]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Blast of Anger" 				"AA" 		${Parse[0,"( ${NPCAAReady[Blast of Anger]} && ${Me.SecondaryPctAggro}>70 && ${Target.Distance}<80 )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${AddHate1}" 				"Disc" 		${Parse[0,"( ${PCDiscReady[${AddHate1}]} && DETSPELLCHECK )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${AddHate2}" 				"Disc" 		${Parse[0,"( ${PCDiscReady[${AddHate2}]} && ${Me.SecondaryPctAggro}>70 && ${Me.Endurance}>500 && ${Target.Distance}<${Spell[${AddHate2}].Range} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${aehealhate}" 				"Disc" 		${Parse[0,"( ${DoAeHate[SETTINGVAL]} && !${Me.Buff[${aehealhate}].ID} && ${PCDiscReady[${aehealhate}]} && !${Me.Buff[${singlehealhate}].ID} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${singlehealhate}" 			"Disc" 		${Parse[0,"( !${Me.Buff[${aehealhate}].ID} && ${PCDiscReady[${singlehealhate}]} && !${Me.Buff[${singlehealhate}].ID} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${absorball}"				"Disc" 		${Parse[0,"( ${Me.PctHPs}<30 && ${PCDiscReady[${absorball}]} )"]}
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${defenseac}" 				"Disc" 		${Parse[0,"( !${Me.ActiveDisc.ID} && ${PCDiscReady[${defenseac}]} )"]}
	
	/if (${DoAutoPDH[SETTINGVAL]}) {
		/call AddToRotation WAR_DPS_MODETANK_Rotation "${absorball}" 	 "Disc" ${Parse[0,"( ${PCDiscReady[${absorball}]} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Diplomatic Immunity].ID} )"]} 
		/call AddToRotation WAR_DPS_MODETANK_Rotation "${ItemOoWBP}" 	 "Item" ${Parse[0,"( ${FindItem[${ItemOoWBP}].ID} && ${FindItem[${ItemOoWBP}].Timer}==0 && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Diplomatic Immunity].ID} )"]} 
		/call AddToRotation WAR_DPS_MODETANK_Rotation "${ItemDipPapers}" "Item" ${Parse[0,"( ${FindItem[${ItemDipPapers}].ID} && ${FindItem[${ItemDipPapers}].Timer}==0 && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Guardian's Bravery].ID} )"]} 
	}
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Brace for Impact" 	 "AA" 	${Parse[0,"( !${Me.Buff[Brace for Impact].ID} && ${PCAAReady[Brace for Impact]} && ${DoBuffs[SETTINGVAL]} && !${DoDefense[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Blade Guardian" 		 "AA" 	${Parse[0,"( !${Me.Song[Blade Guardian].ID} && ${PCAAReady[Blade Guardian]} && ${DoBuffs[SETTINGVAL]} && !${DoDefense[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Battle Leap" 		 "AA" 	${Parse[0,"( ${NPCAAReady[Battle Leap]} && !${Me.Song[Battle Leap].ID} && !${Me.Song[Group Bestial Alignment].ID} && ${Target.MaxRangeTo}>=${Target.Distance} && ${DoBuffs[SETTINGVAL]} && ${DoBattleLeap[SETTINGVAL]} )"]} 

	| - Buttons to Mash For DMG 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Rampage" 			"AA" 		${Parse[0,"( ${DoAEAggro[SETTINGVAL]} && ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} )"]}
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${shieldhit}" 		"Disc" 		${Parse[0,"( ${PCDiscReady[${shieldhit}]} && !${Target.Buff[Sarnak Finesse].ID} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Bash" 				"Ability" 	${Parse[0,"( ${Me.AbilityReady[Bash]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Me.Inventory[14].Type.Equal[Shield]} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Kick" 				"Ability" 	${Parse[0,"( ${Me.AbilityReady[Kick]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Knee Strike" 		"AA" 		${Parse[0,"( ${NPCAAReady[Knee Strike]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Gut Punch" 			"AA" 		${Parse[0,"( ${NPCAAReady[Gut Punch]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Call of Challenge" 	"AA" 		${Parse[0,"( ${NPCAAReady[Call of Challenge]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${DoSnare[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Disarm" 				"Ability" 	${Parse[0,"( ${Me.AbilityReady[Disarm]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${StrikeDisc}" 		"Disc" 		${Parse[0,"( ${PCDiscReady[${StrikeDisc}]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Target.PctHPs}<=20 )"]} 
/return

Sub WAR_ModeConfigMODEDPS
	/varset IsTanking false

	|- Rotations
	|- Downtime Rotation
	/call AddToRotation WAR_Downtime_MODEDPS_Rotation "${defenseac}" 				"Disc" 		${Parse[0,"( !${Me.ActiveDisc.ID} && ${PCDiscReady[${defenseac}]} )"]}
	/call AddToRotation WAR_Downtime_MODEDPS_Rotation "${waraura}" 				"Disc" 		${Parse[0,"( !${Spell[${Me.Aura[1]}].ID} && ${Me.CombatAbility[${Spell[${waraura}].RankName}]} && ${Me.PctEndurance}>10 )"]}
    /call AddToRotation WAR_Downtime_MODEDPS_Rotation "${groupac}" 				"Disc" 		${Parse[0,"( ${PCDiscReady[${groupac}]} && !${Me.Song[${Spell[${groupac}].BaseName}].ID} )"]}
	/call AddToRotation WAR_Downtime_MODEDPS_Rotation "${groupdodge}"  			"Disc" 		${Parse[0,"( ${PCDiscReady[${groupdodge}]} && !${Me.Song[Commanding Voice].ID} )"]}
	/call AddToRotation WAR_Downtime_MODEDPS_Rotation "${endregen}" 				"Disc" 		${Parse[0,"( ${Me.PctEndurance}<15 && ${PCDiscReady[${endregen}]} )"]}  
	/call AddToRotation WAR_Downtime_MODEDPS_Rotation "/autoinventory" 			"Command" 	${Parse[0,"( ${Cursor.ID}  && ${Cursor.ID}==121336)"]}
	/call AddToRotation WAR_Downtime_MODEDPS_Rotation "Huntsman's Ethereal Quiver" "Item" 		${Parse[0,"( ${FindItemCount[Huntsman's Ethereal Quiver]} && ${FindItemCount[Ethereal Arrow]}<1 && ${SummonArrows[SETTINGVAL]}  )"]}
	/call AddToRotation WAR_Downtime_MODEDPS_Rotation "${MountItem[SETTINGVAL]}" 	"Item"  	${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation WAR_Downtime_MODEDPS_Rotation "/dismount" 					"Command"   ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
	
	| - Burn Rotation( Named or More Than BurnCount Variable will trigger- Unless Specific for Named IE Single Big Nukes etc..)
	|**
	/call AddToRotation WAR_Burn_MODETANK_Rotation "${meleemit}"  	    	"Disc"	${Parse[0,"( ${PCDiscReady[${meleemit}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "${parryall}" 	    	"Disc"	${Parse[0,"( ${PCDiscReady[${parryall}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "${missall}"   	    	"Disc"	${Parse[0,"( ${PCDiscReady[${missall}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]}
	/call AddToRotation WAR_Burn_MODETANK_Rotation "${bmdisc}"           	"Disc"	${Parse[0,"( ${PCDiscReady[${bmdisc}]} && ${Me.PctEndurance}>20 && !${Me.Buff[bmdisc].ID} )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "Brace for Impact"    	"AA" 	${Parse[0,"( ${PCAAReady[Brace For Impact]} )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "Imperator's Command" 	"AA" 	${Parse[0,"( ${PCAAReady[Imperator's Command]} )"]} 
	/call AddToRotation WAR_Burn_MODETANK_Rotation "${aehealhate}" 			"Disc" 	${Parse[0,"( ${PCDiscReady[${aehealhate}]} && !${Me.Buff[${aehealhate}].ID} && !${Me.Buff[${aeselfbuff}].ID} && ${Me.PctEndurance}>10 )"]} 
	**|
	/call AddToRotation WAR_Burn_MODEDPS_Rotation "${aeselfbuff}" 			"Disc" 	${Parse[0,"( ${PCDiscReady[${aeselfbuff}]} && !${Me.Buff[${aehealhate}].ID} && !${Me.Buff[${aeselfbuff}].ID} && ${Me.PctEndurance}>10 )"]} 
	/call AddToRotation WAR_Burn_MODEDPS_Rotation "Warlord's Bravery"   	"AA" 	${Parse[0,"( ${PCAAReady[Warlord's Bravery]} )"]} 
	/call AddToRotation WAR_Burn_MODEDPS_Rotation "Warlord's Tenacity"  	"AA" 	${Parse[0,"( ${PCAAReady[Warlord's Tenacity]} )"]} 
	/call AddToRotation WAR_Burn_MODEDPS_Rotation "Warlord's Resurgence"	"AA" 	${Parse[0,"( ${PCAAReady[Warlord's Resurgence]} )"]} 
	/call AddToRotation WAR_Burn_MODEDPS_Rotation "Warlord's Fury"  		"AA" 	${Parse[0,"( ${NPCAAReady[Warlord's Fury]} )"]}
	/call AddToRotation WAR_Burn_MODEDPS_Rotation "War Sheol's Heroic Blade" "AA" 	${Parse[0,"( ${NPCAAReady[War Sheol's Heroic Blade]} )"]} 
	
	| - TankMode DPS Aggro Rotation 
	|**
	| - AOE Aggro Abilities.
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${aeroar}" 					"Disc" 		${Parse[0,"( ( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} ) && ${PCDiscReady[${aeroar}]} && ${DoAEAggro[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${aehitall}" 				"Disc"		${Parse[0,"( ( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} ) && ${PCDiscReady[${aehitall}]} && ${DoAEAggro[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Area Taunt" 					"AA" 		${Parse[0,"( ( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} ) && ${NPCAAReady[Area Taunt]} && ${DoAEAggro[SETTINGVAL]} )"]} 	

	| - Single Target Aggro Rotation
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${endregen}" 				"Disc" 		${Parse[0,"( ${Me.PctEndurance}<15 && ${PCDiscReady[${endregen}]} )"]}  
	/call AddToRotation WAR_DPS_MODETANK_Rotation "/bandolier activate Shield" 	"Command" 	${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Shield].Active} && ${Bool[${Me.Bandolier[Shield].Index}]} && BURNCHECK )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "/bandolier activate Agro" 	"Command" 	${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Agro].Active} && ${Bool[${Me.Bandolier[Agro].Index}]} && ${XAssist.XTFullHaterCount}<${BurnMobCount[SETTINGVAL]} && !${Target.Named} )"]}
| - /call AddToRotation WAR_DPS_MODETANK_Rotation "${missall}" "Disc" ${Parse[0,"( ${Target.ID}==${Spawn[=Anashti Sul, Damsel of Decay].ID} && ${PCDiscReady[${missall}]} && ${Target.PctHPs}<=36 )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Taunt" 						"Ability" 	${Parse[0,"( ${Me.AbilityReady[Taunt]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]}
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${AgroLock}" 				"Disc" 		${Parse[0,"( ${PCDiscReady[${AgroLock}]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${Taunt1}" 					"Disc" 		${Parse[0,"( ${PCDiscReady[${Taunt1}]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Blast of Anger" 				"AA" 		${Parse[0,"( ${NPCAAReady[Blast of Anger]} && ${Me.SecondaryPctAggro}>70 && ${Target.Distance}<80 )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${AddHate1}" 				"Disc" 		${Parse[0,"( ${PCDiscReady[${AddHate1}]} && DETSPELLCHECK )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${AddHate2}" 				"Disc" 		${Parse[0,"( ${PCDiscReady[${AddHate2}]} && ${Me.SecondaryPctAggro}>70 && ${Me.Endurance}>500 && ${Target.Distance}<${Spell[${AddHate2}].Range} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${aehealhate}" 				"Disc" 		${Parse[0,"( ${DoAeHate[SETTINGVAL]} && !${Me.Buff[${aehealhate}].ID} && ${PCDiscReady[${aehealhate}]} && !${Me.Buff[${singlehealhate}].ID} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${singlehealhate}" 			"Disc" 		${Parse[0,"( !${Me.Buff[${aehealhate}].ID} && ${PCDiscReady[${singlehealhate}]} && !${Me.Buff[${singlehealhate}].ID} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${absorball}"				"Disc" 		${Parse[0,"( ${Me.PctHPs}<30 && ${PCDiscReady[${absorball}]} )"]}
	/call AddToRotation WAR_DPS_MODETANK_Rotation "${defenseac}" 				"Disc" 		${Parse[0,"( !${Me.ActiveDisc.ID} && ${PCDiscReady[${defenseac}]} )"]}
	/if (${DoAutoPDH[SETTINGVAL]}) {
		/call AddToRotation WAR_DPS_MODETANK_Rotation "${absorball}" 	 "Disc" ${Parse[0,"( ${PCDiscReady[${absorball}]} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Diplomatic Immunity].ID} )"]} 
		/call AddToRotation WAR_DPS_MODETANK_Rotation "${ItemOoWBP}" 	 "Item" ${Parse[0,"( ${FindItem[${ItemOoWBP}].ID} && ${FindItem[${ItemOoWBP}].Timer}==0 && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Diplomatic Immunity].ID} )"]} 
		/call AddToRotation WAR_DPS_MODETANK_Rotation "${ItemDipPapers}" "Item" ${Parse[0,"( ${FindItem[${ItemDipPapers}].ID} && ${FindItem[${ItemDipPapers}].Timer}==0 && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Guardian's Bravery].ID} )"]} 
	}

	/call AddToRotation WAR_DPS_MODETANK_Rotation "Brace for Impact" 	 "AA" 	${Parse[0,"( !${Me.Buff[Brace for Impact].ID} && ${PCAAReady[Brace for Impact]} && ${DoBuffs[SETTINGVAL]} && !${DoDefense[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Blade Guardian" 		 "AA" 	${Parse[0,"( !${Me.Song[Blade Guardian].ID} && ${PCAAReady[Blade Guardian]} && ${DoBuffs[SETTINGVAL]} && !${DoDefense[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETANK_Rotation "Battle Leap" 		 "AA" 	${Parse[0,"( ${NPCAAReady[Battle Leap]} && !${Me.Song[Battle Leap].ID} && !${Me.Song[Group Bestial Alignment].ID} && ${Target.MaxRangeTo}>=${Target.Distance} && ${DoBuffs[SETTINGVAL]} && ${DoBattleLeap[SETTINGVAL]} )"]} 
		**|	

	| - Buttons to Mash For DMG 
	/call AddToRotation WAR_DPS_MODEDPS_Rotation "Rampage" 			"AA" 		${Parse[0,"( ${DoAEAggro[SETTINGVAL]} && ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} )"]}
	/call AddToRotation WAR_DPS_MODEDPS_Rotation "${shieldhit}" 		"Disc" 		${Parse[0,"( ${PCDiscReady[${shieldhit}]} && !${Target.Buff[Sarnak Finesse].ID} )"]} 
	/call AddToRotation WAR_DPS_MODEDPS_Rotation "Bash" 				"Ability" 	${Parse[0,"( ${Me.AbilityReady[Bash]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Me.Inventory[14].Type.Equal[Shield]} )"]} 
	/call AddToRotation WAR_DPS_MODEDPS_Rotation "Kick" 				"Ability" 	${Parse[0,"( ${Me.AbilityReady[Kick]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODEDPS_Rotation "Knee Strike" 		"AA" 		${Parse[0,"( ${NPCAAReady[Knee Strike]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODEDPS_Rotation "Gut Punch" 			"AA" 		${Parse[0,"( ${NPCAAReady[Gut Punch]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODEDPS_Rotation "Call of Challenge" 	"AA" 		${Parse[0,"( ${NPCAAReady[Call of Challenge]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${DoSnare[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODEDPS_Rotation "Disarm" 				"Ability" 	${Parse[0,"( ${Me.AbilityReady[Disarm]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODEDPS_Rotation "${StrikeDisc}" 		"Disc" 		${Parse[0,"( ${PCDiscReady[${StrikeDisc}]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Target.PctHPs}<=20 )"]} 
/return

Sub WAR_ModeConfigMODETLP
	/varset IsTanking false

	/echo Welcome To TLP Mode Warrior - As with all RGmercs TLP Tanks There is 2 modes in 1
	/echo You Can control Whether your the Tank or not with a Simple /dotank 1/0
	/if  ( ${DoTank[SETTINGVAL]} ) { 
    	/echo I am In TLP Tank Mode
	} else {
    	/echo I am In TLP Dps Mode 
	}


	|- Rotations
	|- Downtime Rotation
	/call AddToRotation WAR_Downtime_MODETLP_Rotation "${defenseac}" 				"Disc" 		${Parse[0,"( !${Me.ActiveDisc.ID} && ${PCDiscReady[${defenseac}]} )"]}
	/call AddToRotation WAR_Downtime_MODETLP_Rotation "${waraura}" 				"Disc" 		${Parse[0,"( !${Spell[${Me.Aura[1]}].ID} && ${Me.CombatAbility[${Spell[${waraura}].RankName}]} && ${Me.PctEndurance}>10 )"]}
    /call AddToRotation WAR_Downtime_MODETLP_Rotation "${groupac}" 				"Disc" 		${Parse[0,"( ${PCDiscReady[${groupac}]} && !${Me.Song[${Spell[${groupac}].BaseName}].ID} )"]}
	/call AddToRotation WAR_Downtime_MODETLP_Rotation "${groupdodge}"  			"Disc" 		${Parse[0,"( ${PCDiscReady[${groupdodge}]} && !${Me.Song[Commanding Voice].ID} )"]}
	/call AddToRotation WAR_Downtime_MODETLP_Rotation "${endregen}" 				"Disc" 		${Parse[0,"( ${Me.PctEndurance}<15 && ${PCDiscReady[${endregen}]} )"]}  
	/call AddToRotation WAR_Downtime_MODETLP_Rotation "/autoinventory" 			"Command" 	${Parse[0,"( ${Cursor.ID}  && ${Cursor.ID}==121336)"]}
	/call AddToRotation WAR_Downtime_MODETLP_Rotation "Huntsman's Ethereal Quiver" "Item" 		${Parse[0,"( ${FindItemCount[Huntsman's Ethereal Quiver]} && ${FindItemCount[Ethereal Arrow]}<1 && ${SummonArrows[SETTINGVAL]}  )"]}
	/call AddToRotation WAR_Downtime_MODETLP_Rotation "${MountItem[SETTINGVAL]}" 	"Item"  	${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation WAR_Downtime_MODETLP_Rotation "/dismount" 					"Command"   ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
	
	| - Burn Rotation( Named or More Than BurnCount Variable will trigger- Unless Specific for Named IE Single Big Nukes etc..)
	
|	/call AddToRotation WAR_Burn_MODETLP_Rotation "${meleemit}"  	    	"Disc"	${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCDiscReady[${meleemit}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]} 
|	/call AddToRotation WAR_Burn_MODETLP_Rotation "${parryall}" 	    	"Disc"	${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCDiscReady[${parryall}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]} 
|	/call AddToRotation WAR_Burn_MODETLP_Rotation "${missall}"   	    	"Disc"	${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCDiscReady[${missall}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]}
	/call AddToRotation WAR_Burn_MODETLP_Rotation "${bmdisc}"           	"Disc"	${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCDiscReady[${bmdisc}]} && ${Me.PctEndurance}>20 && !${Me.Buff[bmdisc].ID} )"]} 
	/call AddToRotation WAR_Burn_MODETLP_Rotation "Brace for Impact"    	"AA" 	${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCAAReady[Brace For Impact]} )"]} 
	/call AddToRotation WAR_Burn_MODETLP_Rotation "Imperator's Command" 	"AA" 	${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCAAReady[Imperator's Command]} )"]} 
	/call AddToRotation WAR_Burn_MODETLP_Rotation "${aehealhate}" 			"Disc" 	${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCDiscReady[${aehealhate}]} && !${Me.Buff[${aehealhate}].ID} && !${Me.Buff[${aeselfbuff}].ID} && ${Me.PctEndurance}>10 )"]} 

	/call AddToRotation WAR_Burn_MODETLP_Rotation "${aeselfbuff}" 			"Disc" 	${Parse[0,"( ${PCDiscReady[${aeselfbuff}]} && !${Me.Buff[${aehealhate}].ID} && !${Me.Buff[${aeselfbuff}].ID} && ${Me.PctEndurance}>10 )"]} 
	/call AddToRotation WAR_Burn_MODETLP_Rotation "Warlord's Bravery"   	"AA" 	${Parse[0,"( ${PCAAReady[Warlord's Bravery]} )"]} 
|	/call AddToRotation WAR_Burn_MODETLP_Rotation "Warlord's Tenacity"  	"AA" 	${Parse[0,"( ${PCAAReady[Warlord's Tenacity]} )"]} 
	/call AddToRotation WAR_Burn_MODETLP_Rotation "Warlord's Resurgence"	"AA" 	${Parse[0,"( ${PCAAReady[Warlord's Resurgence]} )"]} 
	/call AddToRotation WAR_Burn_MODETLP_Rotation "Warlord's Fury"  		"AA" 	${Parse[0,"( ${NPCAAReady[Warlord's Fury]} )"]}
	/call AddToRotation WAR_Burn_MODETLP_Rotation "War Sheol's Heroic Blade" "AA" 	${Parse[0,"( ${NPCAAReady[War Sheol's Heroic Blade]} )"]} 
	
	| - TankMode DPS Aggro Rotation 

	| - AOE Aggro Abilities.
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${aeroar}" 					"Disc" 		${Parse[0,"( ${DoTank[SETTINGVAL]} &&  ( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} ) && ${PCDiscReady[${aeroar}]} && ${DoAEAggro[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${aehitall}" 				"Disc"		${Parse[0,"( ${DoTank[SETTINGVAL]} &&  ( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} ) && ${PCDiscReady[${aehitall}]} && ${DoAEAggro[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Area Taunt" 					"AA" 		${Parse[0,"( ${DoTank[SETTINGVAL]} &&  ( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} ) && ${NPCAAReady[Area Taunt]} && ${DoAEAggro[SETTINGVAL]} )"]} 	

	| - Single Target Aggro Rotation
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${endregen}" 				"Disc" 		${Parse[0,"( ${DoTank[SETTINGVAL]} && ${Me.PctEndurance}<15 && ${PCDiscReady[${endregen}]} )"]}  
	/call AddToRotation WAR_DPS_MODETLP_Rotation "/bandolier activate Shield" 	"Command" 	${Parse[0,"( ${DoTank[SETTINGVAL]} && ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Shield].Active} && ${Bool[${Me.Bandolier[Shield].Index}]} && BURNCHECK )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "/bandolier activate Agro" 	"Command" 	${Parse[0,"( ${DoTank[SETTINGVAL]} && ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Agro].Active} && ${Bool[${Me.Bandolier[Agro].Index}]} && ${XAssist.XTFullHaterCount}<${BurnMobCount[SETTINGVAL]} && !${Target.Named} )"]}
| - /call AddToRotation WAR_DPS_MODETLP_Rotation "${missall}" 					"Disc" 		${Parse[0,"( ${DoTank[SETTINGVAL]} && ${Target.ID}==${Spawn[=Anashti Sul, Damsel of Decay].ID} && ${PCDiscReady[${missall}]} && ${Target.PctHPs}<=36 )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Taunt" 						"Ability" 	${Parse[0,"( ${DoTank[SETTINGVAL]} && ${Me.AbilityReady[Taunt]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]}
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${AgroLock}" 				"Disc" 		${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCDiscReady[${AgroLock}]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${Taunt1}" 					"Disc" 		${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCDiscReady[${Taunt1}]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Blast of Anger" 				"AA" 		${Parse[0,"( ${DoTank[SETTINGVAL]} && ${NPCAAReady[Blast of Anger]} && ${Me.SecondaryPctAggro}>70 && ${Target.Distance}<80 )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${AddHate1}" 				"Disc" 		${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCDiscReady[${AddHate1}]} && DETSPELLCHECK )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${AddHate2}" 				"Disc" 		${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCDiscReady[${AddHate2}]} && ${Me.SecondaryPctAggro}>70 && ${Me.Endurance}>500 && ${Target.Distance}<${Spell[${AddHate2}].Range} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${aehealhate}" 				"Disc" 		${Parse[0,"( ${DoTank[SETTINGVAL]} && ${DoAeHate[SETTINGVAL]} && !${Me.Buff[${aehealhate}].ID} && ${PCDiscReady[${aehealhate}]} && !${Me.Buff[${singlehealhate}].ID} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${singlehealhate}" 			"Disc" 		${Parse[0,"( ${DoTank[SETTINGVAL]} && !${Me.Buff[${aehealhate}].ID} && ${PCDiscReady[${singlehealhate}]} && !${Me.Buff[${singlehealhate}].ID} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${absorball}"				"Disc" 		${Parse[0,"( ${DoTank[SETTINGVAL]} && ${Me.PctHPs}<30 && ${PCDiscReady[${absorball}]} )"]}
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${defenseac}" 				"Disc" 		${Parse[0,"( ${DoTank[SETTINGVAL]} && !${Me.ActiveDisc.ID} && ${PCDiscReady[${defenseac}]} )"]}
	/if (${DoAutoPDH[SETTINGVAL]}) {
		/call AddToRotation WAR_DPS_MODETLP_Rotation "${absorball}" 	 "Disc" ${Parse[0,"( ${DoTank[SETTINGVAL]} && ${PCDiscReady[${absorball}]} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Diplomatic Immunity].ID} )"]} 
		/call AddToRotation WAR_DPS_MODETLP_Rotation "${ItemOoWBP}" 	 "Item" ${Parse[0,"( ${DoTank[SETTINGVAL]} && ${FindItem[${ItemOoWBP}].ID} && ${FindItem[${ItemOoWBP}].Timer}==0 && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Diplomatic Immunity].ID} )"]} 
		/call AddToRotation WAR_DPS_MODETLP_Rotation "${ItemDipPapers}" "Item" ${Parse[0,"( ${DoTank[SETTINGVAL]} && ${FindItem[${ItemDipPapers}].ID} && ${FindItem[${ItemDipPapers}].Timer}==0 && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Guardian's Bravery].ID} )"]} 
	}

	/call AddToRotation WAR_DPS_MODETLP_Rotation "Brace for Impact" 	 "AA" 	${Parse[0,"( ${DoTank[SETTINGVAL]} && !${Me.Buff[Brace for Impact].ID} && ${PCAAReady[Brace for Impact]} && ${DoBuffs[SETTINGVAL]} && !${DoDefense[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Blade Guardian" 		 "AA" 	${Parse[0,"( ${DoTank[SETTINGVAL]} && !${Me.Song[Blade Guardian].ID} && ${PCAAReady[Blade Guardian]} && ${DoBuffs[SETTINGVAL]} && !${DoDefense[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Battle Leap" 		 "AA" 	${Parse[0,"( ${DoTank[SETTINGVAL]} && ${NPCAAReady[Battle Leap]} && !${Me.Song[Battle Leap].ID} && !${Me.Song[Group Bestial Alignment].ID} && ${Target.MaxRangeTo}>=${Target.Distance} && ${DoBuffs[SETTINGVAL]} && ${DoBattleLeap[SETTINGVAL]} )"]} 
	

	| - Buttons to Mash For DMG 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Rampage" 			"AA" 		${Parse[0,"( ${DoAEAggro[SETTINGVAL]} && ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} )"]}
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${shieldhit}" 		"Disc" 		${Parse[0,"( ${PCDiscReady[${shieldhit}]} && !${Target.Buff[Sarnak Finesse].ID} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Bash" 				"Ability" 	${Parse[0,"( ${Me.AbilityReady[Bash]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Me.Inventory[14].Type.Equal[Shield]} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Kick" 				"Ability" 	${Parse[0,"( ${Me.AbilityReady[Kick]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Knee Strike" 		"AA" 		${Parse[0,"( ${NPCAAReady[Knee Strike]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Gut Punch" 			"AA" 		${Parse[0,"( ${NPCAAReady[Gut Punch]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Call of Challenge" 	"AA" 		${Parse[0,"( ${NPCAAReady[Call of Challenge]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${DoSnare[SETTINGVAL]} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "Disarm" 				"Ability" 	${Parse[0,"( ${Me.AbilityReady[Disarm]} && ${Target.Distance}<=${Target.MaxRangeTo} )"]} 
	/call AddToRotation WAR_DPS_MODETLP_Rotation "${StrikeDisc}" 		"Disc" 		${Parse[0,"( ${PCDiscReady[${StrikeDisc}]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Target.PctHPs}<=20 )"]} 
/return


Sub WAR_ModeConfigMODETANK115
/varset IsTanking TRUE

	|- Rotations
	|- Downtime Rotation

	/call AddToRotation WAR_Downtime_MODETANK115_Rotation "${defenseac}" "Disc" ${Parse[0,"( !${Me.ActiveDisc.ID} && ${PCDiscReady[${defenseac}]} )"]}
	/call AddToRotation WAR_Downtime_MODETANK115_Rotation "${waraura}" "Disc" ${Parse[0,"( !${Spell[${Me.Aura[1]}].ID} && ${Me.CombatAbility[${Spell[${waraura}].RankName}]} && ${Me.PctEndurance}>10 )"]}
    /call AddToRotation WAR_Downtime_MODETANK115_Rotation "${groupac}" "Disc" ${Parse[0,"( ${PCDiscReady[${groupac}]} && !${Me.Song[${Spell[${groupac}].BaseName}].ID} )"]}
	/call AddToRotation WAR_Downtime_MODETANK115_Rotation "${groupdodge}" "Disc" ${Parse[0,"( ${PCDiscReady[${groupdodge}]} && !${Me.Song[Commanding Voice].ID} )"]}
	/call AddToRotation WAR_Downtime_MODETANK115_Rotation "${endregen}" "Disc" ${Parse[0,"( ${Me.PctEndurance}<15 && ${PCDiscReady[${endregen}]} )"]}  
	/call AddToRotation WAR_Downtime_MODETANK115_Rotation "${MountItem[SETTINGVAL]}" Item   ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID}) ) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation WAR_Downtime_MODETANK115_Rotation "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
	/call AddToRotation WAR_Downtime_MODETANK115_Rotation "/autoinventory" "Command" ${Parse[0,"( ${Cursor.ID}  && ${Cursor.ID}==121336)"]}
	/call AddToRotation WAR_Downtime_MODETANK115_Rotation "Huntsman's Ethereal Quiver" "Item" ${Parse[0,"( ${FindItemCount[Huntsman's Ethereal Quiver]} && ${FindItemCount[Ethereal Arrow]}<1 && ${SummonArrows[SETTINGVAL]}  )"]}
	
	|- DPS Rotation
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "/bandolier activate Shield" "Command" ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Shield].Active} && ${Bool[${Me.Bandolier[Shield].Index}]} && BURNCHECK )"]} 
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "/bandolier activate Agro" "Command" ${Parse[0,"( ${DoBandolier[SETTINGVAL]} && !${Me.Bandolier[Agro].Active} && ${Bool[${Me.Bandolier[Agro].Index}]} && ${XAssist.XTFullHaterCount}<${BurnMobCount[SETTINGVAL]} && !${Target.Named} )"]}
	|/call AddToRotation WAR_DPS_MODETANK115_Rotation "${missall}" "Disc" ${Parse[0,"( ${Target.ID}==${Spawn[=Anashti Sul, Damsel of Decay].ID} && ${PCDiscReady[${missall}]} && ${Target.PctHPs}<=36 )"]} 
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "${parryall}" "Disc" ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]}>2 || ${Target.Named}) && ${PCDiscReady[${parryall}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]} 
	/if (${IsTanking}) {
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${meleemit}" "Disc" ${Parse[0,"( BURNCHECK && ${PCDiscReady[${meleemit}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${missall}" "Disc" ${Parse[0,"( BURNCHECK && ${PCDiscReady[${missall}]} && (${Me.ActiveDisc.Name.Find[Defense]} || !${Me.ActiveDisc.ID}) )"]}
		
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Resplendent Glory" "AA" ${Parse[0,"( ${RG_AAReady[Resplendent Glory]} && ${Me.ActiveDisc.Name.Find[${meleemit}]} )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Brace for Impact" "AA" ${Parse[0,"( ${Me.ActiveDisc.Name.Find[${meleemit}]} && ${RG_AAReady[Brace for Impact]} )"]} 
		/if (${DoAutoPDH[SETTINGVAL]}) {
			/call AddToRotation WAR_DPS_MODETANK115_Rotation "${absorball}" "Disc" ${Parse[0,"( ${PCDiscReady[${absorball}]} && !${Me.Buff[Guardian's Bravery].ID} && !${Me.Buff[Diplomatic Immunity].ID} )"]} 
			/call AddToRotation WAR_DPS_MODETANK115_Rotation "${ItemOoWBP}" "Item" ${Parse[0,"( ${FindItem[${ItemOoWBP}].ID} && ${FindItem[${ItemOoWBP}].Timer}==0 && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Diplomatic Immunity].ID} )"]} 
			/call AddToRotation WAR_DPS_MODETANK115_Rotation "${ItemDipPapers}" "Item" ${Parse[0,"( ${FindItem[${ItemDipPapers}].ID} && ${FindItem[${ItemDipPapers}].Timer}==0 && !${Me.Song[Pain Doesn't Hurt].ID} && !${Me.Buff[Guardian's Bravery].ID} )"]} 
		}	
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Imperator's Command" "AA" ${Parse[0,"( BURNCHECK &&  ${Me.ActiveDisc.Name.Find[${defenseac}]} && ${RG_AAReady[Imperator's Command]} && !${Me.Buff[${bmdisc}].ID} )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Velium Infused Legionnaire Breastplate" "Item" ${Parse[0,"( BURNCHECK && ${FindItem[Velium Infused Legionnaire Breastplate].ID} && ${FindItem[Velium Infused Legionnaire Breastplate].Timer}==0 && ${Me.ActiveDisc.Name.Find[${defenseac}]} && !${Me.Buff[${bmdisc}].ID} )"]} 
		/if (${bmdisc.Equal[Dissident Shield]}) {
			/call AddToRotation WAR_DPS_MODETANK115_Rotation "/disc 57800" "Command" ${Parse[0,"( BURNCHECK && ${Me.ActiveDisc.Name.Find[${defenseac}]} && ${PCDiscReady[${bmdisc}]} && !${Me.Song[Finish the Fight].ID} )"]} 
		} else {
			/call AddToRotation WAR_DPS_MODETANK115_Rotation "${bmdisc}" "Disc" ${Parse[0,"(  BURNCHECK && ${Me.ActiveDisc.Name.Find[${defenseac}]} && ${PCDiscReady[${bmdisc}]} && !${Me.Song[Finish the Fight].ID} )"]} 
		}
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Spire of the Warlord" "AA" ${Parse[0,"( BURNCHECK && ${RG_AAReady[Spire of the Warlord]} && ${Me.Buff[${bmdisc}].ID} )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Warrior's Rampart" "AA" ${Parse[0,"( BURNCHECK && ${RG_AAReady[Warrior's Rampart]} && ${Me.Buff[${bmdisc}].ID} )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${defenseac}" "Disc" ${Parse[0,"( !${Me.ActiveDisc.ID} && ${PCDiscReady[${defenseac}]} )"]}
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Blade Guardian" "AA" ${Parse[0,"( !${Me.Song[Blade Guardian].ID} && ${RG_AAReady[Blade Guardian]} && ${DoBuffs[SETTINGVAL]} && !${DoDefense[SETTINGVAL]} )"]}
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Warlord's Tenacity" "AA" ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]}>2 || ${Target.Named}) && !${Me.Buff[Brace for Impact].ID} && ${RG_AAReady[Warlord's Tenacity]} )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${aehealhate}" "Disc" ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]}>1 || ${Target.Named}) && ${PCDiscReady[${aehealhate}]} && !${Me.Buff[${aehealhate}].ID} && !${Me.Buff[${aeselfbuff}].ID} && ${Me.PctEndurance}>10 )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${aeselfbuff}" "Disc" ${Parse[0,"( (${SpawnCount[NPC radius 60 zradius 50]}>1 || ${Target.Named}) && ${PCDiscReady[${aeselfbuff}]} && !${Me.Buff[${aehealhate}].ID} && !${Me.Buff[${aeselfbuff}].ID} && ${Me.PctEndurance}>10 )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Battle Leap" "AA" ${Parse[0,"( ${RG_AAReady[Battle Leap]} && !${Me.Song[Battle Leap].ID} && !${Me.Song[Group Bestial Alignment].ID} && ${Target.MaxRangeTo}>=${Target.Distance} && ${DoBuffs[SETTINGVAL]} && ${DoBattleLeap[SETTINGVAL]} )"]} 

	}

	
	/if (${IsTanking}) {
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${aehealhate}" "Disc" ${Parse[0,"( ${DoAeHate[SETTINGVAL]} && !${Me.Buff[${aehealhate}].ID} && ${PCDiscReady[${aehealhate}]} && !${Me.Buff[${singlehealhate}].ID} )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${singlehealhate}" "Disc" ${Parse[0,"( !${Me.Buff[${aehealhate}].ID} && ${PCDiscReady[${singlehealhate}]} && !${Me.Buff[${singlehealhate}].ID} )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${aehitall}" "Disc" ${Parse[0,"( ${SpawnCount[NPC radius 60 zradius 50]}>1 && (${Me.XTAggroCount} > 0) && ${PCDiscReady[${aehitall}]} && ${DoAEAggro[SETTINGVAL]} )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${aeroar}" "Disc" ${Parse[0,"( ${SpawnCount[NPC radius 60 zradius 50]}>1 && (${Me.XTAggroCount} > 0) && ${PCDiscReady[${aeroar}]})"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Area Taunt" "AA" ${Parse[0,"( ${SpawnCount[NPC radius 60 zradius 50]}>1 && (${Me.XTAggroCount} > 0) && ${RG_AAReady[Area Taunt]} )"]}
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Rage of Rallos Zek" "AA" ${Parse[0,"( ${RG_AAReady[Rage of Rallos Zek]})"]}
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Blast of Anger" "AA" ${Parse[0,"( ${RG_AAReady[Blast of Anger]} && ${Me.SecondaryPctAggro}>70 && ${Target.Distance}<80 )"]}
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Ageless Enmity" "AA" ${Parse[0,"( ${RG_AAReady[Ageless Enmity]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${AgroLock}" "Disc" ${Parse[0,"( ${PCDiscReady[${AgroLock}]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Taunt" "Ability" ${Parse[0,"( ${Me.AbilityReady[Taunt]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${Taunt1}" "Disc" ${Parse[0,"( ${PCDiscReady[${Taunt1}]} && ${Me.TargetOfTarget.ID}!=${Me.ID} && ${Target.Distance}<30 )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "Projection of Fury" "AA" ${Parse[0,"( ${RG_AAReady[Blast of Anger]} && ${Me.SecondaryPctAggro}>70 && ${Target.Distance}<80 )"]}
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${AgroPet}" "Disc" ${Parse[0,"( ${PCDiscReady[${AgroPet}]} && ${Me.SecondaryPctAggro}>70 && ${Target.Distance}<80 )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${AddHate1}" "Disc" ${Parse[0,"( ${PCDiscReady[${AddHate1}]} && ${Me.SecondaryPctAggro}>70 && ${Me.Endurance}>500 && ${Target.Distance}<${Spell[${AddHate1}].Range} )"]} 
		/call AddToRotation WAR_DPS_MODETANK115_Rotation "${AddHate2}" "Disc" ${Parse[0,"( ${PCDiscReady[${AddHate2}]} && ${Me.SecondaryPctAggro}>70 && ${Me.Endurance}>500 && ${Target.Distance}<${Spell[${AddHate2}].Range} )"]} 
	}
	|Mash
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "Rampage" "AA" ${Parse[0,"( ${DoAEAggro[SETTINGVAL]} || ${SpawnCount[npc radius 30 playerstate 4]} => 3 )"]}
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "${shieldhit}" "Disc" ${Parse[0,"( ${PCDiscReady[${shieldhit}]} && !${Target.Buff[Sarnak Finesse].ID} )"]} 
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "Bash" "Ability" ${Parse[0,"( ${Me.AbilityReady[Bash]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Me.Combat} && ${Me.Inventory[14].Type.Equal[Shield]} )"]} 
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "Kick" "Ability" ${Parse[0,"( ${Me.AbilityReady[Kick]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Me.Combat} )"]} 
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "Knee Strike" "AA" ${Parse[0,"( ${RG_AAReady[Knee Strike]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Me.Combat} )"]} 
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "Gut Punch" "AA" ${Parse[0,"( ${RG_AAReady[Gut Punch]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Me.Combat} )"]} 
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "Call of Challenge" "AA" ${Parse[0,"( ${RG_AAReady[Call of Challenge]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Me.Combat} )"]} 
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "Disarm" "Ability" ${Parse[0,"( ${Me.AbilityReady[Disarm]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Me.Combat} )"]} 
	/call AddToRotation WAR_DPS_MODETANK115_Rotation "${StrikeDisc}" "Disc" ${Parse[0,"( ${PCDiscReady[${StrikeDisc}]} && ${Target.Distance}<=${Target.MaxRangeTo} && ${Target.PctHPs}<=20 && ${Me.Combat} )"]} 
/return

|----------------------------------------------------------------------------
|-SUB: BIND DefenseDisc - 
|----------------------------------------------------------------------------
#bind DefenseDisc    /defdisc
Sub Bind_DefenseDisc
	/if (${PCDiscReady[${meleemit}]}) {
		/if (${Me.Buff[Night's Endless Terror].ID}) {
			/docommand /removebuff "Night's Endless Terror"
			/delay 5
			/call DiscQueue "${meleemit}"
		} else { 
			/call DiscQueue "${meleemit}"
		}
	} else {
		/echo \ar COOL DOWN \ag >> \aw ${meleemit} \ag << 
	}
/return 
|----------------------------------------------------------------------------
|-SUB: BIND FortitudeDisc - 
|----------------------------------------------------------------------------
#bind FortitudeDisc  /evadedisc
Sub Bind_FortitudeDisc
	/if (${PCDiscReady[${missall}]}) {
		/call DiscQueue "${missall}"
	} else {
		/echo \ar COOL DOWN \ag >> \aw ${missall} \ag << 
	}
/return  

Sub WAR_Combat_Routine
	/if (${Target.ID} && ${Target.ID}==${Spawn[=Anashti Sul, Damsel of Decay].ID} && ${PCDiscReady[${missall}]} && ${Target.PctHPs}<=36) /call DiscNow "${missall}"
	
	/if (DODPS) {
		/if ( BURNCHECK ) {
			/call Ordered_Rotation_Follow WAR_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE TRUE
		}
	/call Ordered_Rotation_Follow WAR_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE TRUE
	}
/return FALSE

Sub WAR_Downtime_Routine
	/call FollowRotation WAR_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID} TRUE 1
/return FALSE

Sub FacePull
	/call AbilityNow "Taunt" ${autotargetid}
/return


Sub WAR_PullSetup
/if (${Me.Inventory[ranged].Type.Equal[Archery]} && ${Me.Inventory[ammo].Stack} > 50) {
        /call Pull_SetAbility "pullrange" "Special"
    } else /if (${Me.CombatAbilityReady[Throw Stone]}) {
        /call Pull_SetAbility "Throw Stone" "Disc"
|    } else {
|		/call Pull_SetAbility "/call FacePull"  "Command"
	}
/return