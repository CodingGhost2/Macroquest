|- RGclrutil.inc
|- Version Core 1.0
|- Updated: 4/6/2020
#define MODEHEAL 0
#define MODEBATTLE 1
#define MODETLP 2
|--------------------------------------------------------------------------------------
|-Setup Variable Environment
|--------------------------------------------------------------------------------------
Sub CLR_Setup
    /declare RGList_CLR list outer
|- Items
    /call ItemSet_New Epic     

|- Spell Variables
    /call AbilitySet_New wardspell		     
	/call AbilitySet_New remedyheal	       	       
	/call AbilitySet_New patchheal		      
	/call AbilitySet_New groupfastheal	    
	/call AbilitySet_New groupheal		        
	/call AbilitySet_New grouphealnocure     
	/call AbilitySet_New promheal		        
	/call AbilitySet_New bigheal	       		       
	/call AbilitySet_New yaulpspell		        
	/call AbilitySet_New stunnuke		       
	/call AbilitySet_New healnuke		       	      
	/call AbilitySet_New nukeheal		       		       
    /call AbilitySet_New ReverseDS			
	/call AbilitySet_New SelfBuffhp				
	/call AbilitySet_New GroupHealProcBuff		
	/call AbilitySet_New AegoBuff			
	/call AbilitySet_New GroupBuff				
	/call AbilitySet_New TankBuff				
	/call AbilitySet_New GroupVieBuff			
	/call AbilitySet_New SingleSymbolBuff		
    /call AbilitySet_New SymbolBuff		       
	/call AbilitySet_New HPBuff			        
	/call AbilitySet_New aurabuff1 AURA
    /declare aurabuff1_name string outer 		       
	/call AbilitySet_New aurabuff2
	/call AbilitySet_New DivineBuff		      
    /call AbilitySet_New Icespellcure
	/call AbilitySet_New AllianceBuff
	/call AbilitySet_New Hammerpet
	/call AbilitySet_New SingleHot
	/call AbilitySet_New twincastnuke
    /call AbilitySet_New CurePoison
    /call AbilitySet_New CureDisease
    /call AbilitySet_New CureCurse
    /call AbilitySet_New CureCorrupt
    /call AbilitySet_New RezSpell
    /call AbilitySet_New AERezSpell
    /call AbilitySet_New ClutchHeal
    /call AbilitySet_New InfusionHand
    /call AbilitySet_New MagicNuke
    /call AbilitySet_New AnticipatedHeal
    /call AbilitySet_New GroupHot
    /call AbilitySet_New GroupHotCure
    /call AbilitySet_New SpellBlessing
    /call AbilitySet_New CompHeal
|- Rotations
    /call Ordered_Rotation_New CLR_DPS_MODEHEAL_Rotation
    /call Ordered_Rotation_New CLR_Downtime_MODEHEAL_Rotation
    /call Ordered_Rotation_New CLR_Burn_MODEHEAL_Rotation
    /call Ordered_Rotation_New CLR_Debuff_MODEHEAL_Rotation

    /call Ordered_Rotation_New CLR_DPS_MODEBATTLE_Rotation
    /call Ordered_Rotation_New CLR_Downtime_MODEBATTLE_Rotation
    /call Ordered_Rotation_New CLR_Burn_MODEBATTLE_Rotation
    /call Ordered_Rotation_New CLR_Debuff_MODEBATTLE_Rotation

    /call Ordered_Rotation_New CLR_DPS_MODETLP_Rotation
    /call Ordered_Rotation_New CLR_Downtime_MODETLP_Rotation
    /call Ordered_Rotation_New CLR_Burn_MODETLP_Rotation
    /call Ordered_Rotation_New CLR_Debuff_MODETLP_Rotation
    
|- Initialize Cure Observers
    /call Cure_Init

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
	/declare spellmisc 			int	 outer 8
    /declare Emeralds 			int  outer 0
	/declare Pearls				int  outer 0
	/declare groupbufftimer 	int outer 0
		
    /declare DurationMod        float outer 0
    /declare miscspellremem		string outer NULL
    /declare spellrememtimer	timer outer 0

	/declare epicwand string outer NULL
    /declare tacvihammer string outer NULL
    /declare PromHealTimer timer outer
    /declare TimerDuration int Outer 250
    /if (${FindItem[Water Sprinkler of Nem Ankh].ID}) /varset epicwand "Water Sprinkler of Nem Ankh"
    /if (${FindItem[Weighted Hammer of Conviction].ID}) /varset tacvihammer "Weighted Hammer of Conviction"  
|-Grab Options from INI
    /call LoadCommonConfig
    /varset ClassMode[SETTINGDESC] Set 0 = Heal, 1 = Battle 2 = TLP
| - Toggles - These Toggle Functions on and Off
    /call RGLoadSetting CLR DoHeals 1 Healing "Set 0/1 to heal the group. Checked in the main loop."
    /call RGLoadSetting CLR DoHots 0 Healing " Determines whether or not u want to use HOT heals."
    /call RGLoadSetting CLR DoCure 0 Healing "Set 0/1 to use new DanNet observers Cure system."
    /call RGLoadSetting CLR DoProm 1 Healing "Setting to toggle off Promised heal Functioning Always"
    /call RGLoadSetting CLR DoClutchHeal 0 Healing "Set 0/1 to use of the 11th-17th Line of spells which Only are usable below 35% or 45% Life." 1
    /call RGLoadSetting CLR DoBattleRez 0 Healing "Set 0/1 to Battle Rez."
    /call RGLoadSetting CLR DoAutoWard 1 Healing "Automatically Drops wards when group hurt 0/1"
|   - These Control Various Heal Points for the Cleric - ( Not TLP )
 	/call RGLoadSetting CLR MainHealPoint 95  HealPoint "Healpoints Controlled by Healmode - Only to be changed by Advanced Users" 1
    /call RGLoadSetting CLR BigHealPoint 80 HealPoint "Healpoints Controlled by Healmode - Only to be changed by Advanced Users" 1
	/call RGLoadSetting CLR GroupHealPoint 85 HealPoint "Healpoints Controlled by Healmode - Only to be changed by Advanced Users" 1
    /call RGLoadSetting CLR ClutchHealPoint 34 HealPoint "Must be Below 34/44% to cast Spells. Modify at Your Own Risk!" 1
	/call RGLoadSetting CLR GroupInjureCnt 2 HealPoint "Number of Group Injured by Grouphealpoint % to trigger Using Group Heals - Only to be changed by Advanced Users" 1
| - Nukes On and Setting To Control. 
    /call RGLoadSetting CLR DoNuke 1 Combat "Set 0/1 to use heal nukes."
    /call RGLoadSetting CLR Manatonuke 60 Combat "Minumum Mana to use Nukes"
    /call RGLoadSetting CLR NukePct 90 Combat "Determines what % to begin using Nukes or Heal Nukes of Anykind."
    /call RGLoadSetting CLR DoReverseDS 1 Combat "Set 0/1 to use Cleric Reverse Damage Shield Line 1/0"
| - Quiet Prayer toggle and Value Setting
    /call RGLoadSetting CLR DoQp 1 Options "Set 0/1 to use Quiet Prayer"
    /call RGLoadSetting CLR QPManaPCT 40 HealPoint "% Mana to cast Quiet prayer on QP target" 1
	/call RGLoadSetting CLR VetManaPCT 70 HealPoint "% mana to Autocast Mana Gain AA" 1
	/call RGLoadSetting CLR DivineBuffOn 0 Options "Set 0/1 to use Divine Buffs -- Restart macro to take affect." 
    /call RGLoadSetting CLR DoDruid 0 Options "Set to 1 if Druid In Group to avoid buff conflicts and weird behavior."
| - TLP mode Specific Settings. (For TLP Mode Only)
	/call RGLoadSetting CLR DoCh 0 TLP "Set 0/1 to use Complete Heal spell."
    /call RGLoadSetting CLR TLPStartHealPoint 90 TLP "The Point at which to Start heals" 
    /call RGLoadSetting CLR CompHealPoint  65 TLP "Complete heal start Point" 1
    /call RGLoadSetting CLR LightHealPoint 65 TLP "When Not using Ch what % to begin a Light heal Spell." 1
    /call RGLoadSetting CLR RemedyHealPoint 80 TLP "When to Start Casting Remedy heals" 1
    /call RGLoadSetting CLR DoSymbol 0 TLP "Cast Symbol or Not on tank" 1

|-Set Variables for Character
	/if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==1) /varset DurationMod 1.15
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==2) /varset DurationMod 1.3
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==3) /varset DurationMod 1.5
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==4) /varset DurationMod 1.7
    /if (${Me.AltAbility[Spell Casting Reinforcement].Rank}==5) /varset DurationMod 1.9
    
|- Camp Settings Checkup
	/if (${MakeCamp.Status.Equal[ON]}) /makecamp off
	/if (${ReturnToCamp[SETTINGVAL]}==1) /echo Warning: Cleric is set to Camp
|- Set SpellSlots Availble
    /varset spellmisc ${Me.NumGems}
    
|- Check For Spell Casting Sublety - This Ensures this is On to avoid Aggro.
	/if (${Me.AltAbility[252].Name.Find[disabled]} && ${RG_AAReady[252]}) {
		/alt act 252
		/delay 5
	}    
|- Check for Spell Components
    /varset Emeralds ${FindItem[=Emerald].StackCount}
	/varset Pearls ${FindItem[=Pearl].StackCount}  
/return

|--------------------
|- SUB: CheckSpells
|--------------------
Sub CLR_SetupSkills
|- Items
| - Epic 
    /call ItemSet_Add "Harmony of the Soul" Epic
    /call ItemSet_Add "Aegis of Superior Divinity" Epic
    /call ItemSet_Add "Water Sprinkler of Nem Ankh" Epic
    /call ItemSet_ChooseOuter Epic Epic


| ---- Basic Nuke
    /call AbilitySet_Add "Strike" MagicNuke
    /call AbilitySet_Add "Furor" MagicNuke
    /call AbilitySet_Add "Smite" MagicNuke
    /call AbilitySet_Add "Wrath" MagicNuke
    /call AbilitySet_Add "Retribution" MagicNuke
    /call AbilitySet_Add "Judgment" MagicNuke
    /call AbilitySet_Add "Condemnation" MagicNuke
    /call AbilitySet_Add "Order" MagicNuke
    /call AbilitySet_Add "Reproach" MagicNuke
    /call AbilitySet_Add "Reproval" MagicNuke
    /call AbilitySet_Add "Reprehend" MagicNuke
    /call AbilitySet_Add "Rebuke" MagicNuke
    /call AbilitySet_Add "Remonstrance" MagicNuke
    /call AbilitySet_Add "Castigation" MagicNuke
    /call AbilitySet_Add "Justice" MagicNuke
    /call AbilitySet_Add "Sanction" MagicNuke
    /call AbilitySet_Add "Injunction" MagicNuke
    /call AbilitySet_Add "Divine Writ" MagicNuke
    /call AbilitySet_Add "Decree" MagicNuke
    /call AbilitySet_ChooseOuter MagicNuke MagicNuke    

| - Complete Heal
    /call AbilitySet_Add "Complete Heal" CompHeal
    /call AbilitySet_ChooseOuter CompHeal CompHeal

|---Remedy Slot 1 & 2 Primary Remedy Slot - Picks best Spell
	/call AbilitySet_Add "Minor Healing" remedyheal
    /call AbilitySet_Add "Light Healing" remedyheal
    /call AbilitySet_Add "Healing" remedyheal
    /call AbilitySet_Add "Greater Healing" remedyheal
    /call AbilitySet_Add "Celestial Health" remedyheal
    /call AbilitySet_Add "Superior Healing" remedyheal
    /call AbilitySet_Add "Remedy" remedyheal
    /call AbilitySet_Add "Ethereal Remedy" remedyheal
    /call AbilitySet_Add "Supernal Remedy" remedyheal
    /call AbilitySet_Add "Pious Remedy" remedyheal
    /call AbilitySet_Add "Sacred Remedy" remedyheal
    /call AbilitySet_Add "Solemn Remedy" remedyheal
    /call AbilitySet_Add "Devout Remedy" remedyheal
    /call AbilitySet_Add "Earnest Remedy" remedyheal
    /call AbilitySet_Add "Faithful Remedy" remedyheal
    /call AbilitySet_Add "Graceful Remedy" remedyheal
    /call AbilitySet_Add "Spiritual Remedy" remedyheal
    /call AbilitySet_Add "Merciful Remedy" remedyheal
    /call AbilitySet_Add "Sincere Remedy" remedyheal
    /call AbilitySet_Add "Guileless Remedy" remedyheal
    /call AbilitySet_Add "Avowed Remedy" remedyheal
    /call AbilitySet_ChooseOuter remedyheal1 remedyheal
    /call AbilitySet_ChooseOuter remedyheal2 remedyheal "${remedyheal1}"
 |---Ward Spell Slot 1 or Heal over time for low level 
    /call AbilitySet_Add "Celestial Remedy" wardspell
    /call AbilitySet_Add "Celestial Health" wardspell
    /call AbilitySet_Add "Celestial Healing" wardspell
    /call AbilitySet_Add "Celestial Elixir" wardspell
    /call AbilitySet_Add "Supernal Elixir" wardspell
    /call AbilitySet_Add "Holy Elixir" wardspell
    /call AbilitySet_Add "Pious Elixir" wardspell
    /call AbilitySet_Add "Sacred Elixir" wardspell
    /call AbilitySet_Add "Solemn Elixir" wardspell
    /call AbilitySet_Add "Devout Elixir" wardspell
    /call AbilitySet_Add "Earnest Elixir" wardspell
    /call AbilitySet_Add "Zealous Elixir" wardspell
    /call AbilitySet_Add "Ward of Certitude" wardspell
    /call AbilitySet_Add "Ward of Surety" wardspell
    /call AbilitySet_Add "Ward of Assurance" wardspell
    /call AbilitySet_Add "Ward of Righteousness" wardspell
    /call AbilitySet_Add "Ward of Persistence" wardspell
    /call AbilitySet_Add "Ward of Commitment" wardspell
    /call AbilitySet_ChooseOuter wardspell wardspell "${remedyheal1}" 
    
|---Patch Heals Slot 4 Dissident Blessing
    /call AbilitySet_Add "Healing Light" patchheal
    /call AbilitySet_Add "Divine Light" patchheal
    /call AbilitySet_Add "Ethereal Light" patchheal
    /call AbilitySet_Add "Supernal Light" patchheal
    /call AbilitySet_Add "Holy Light" patchheal
    /call AbilitySet_Add "Pious Light" patchheal
    /call AbilitySet_Add "Ancient: Hallowed Light" patchheal
    /call AbilitySet_Add "Sacred Light" patchheal
    /call AbilitySet_Add "Solemn Light" patchheal
    /call AbilitySet_Add "Devout Light" patchheal
    /call AbilitySet_Add "Earnest Light" patchheal
    /call AbilitySet_Add "Zealous Light" patchheal
    /call AbilitySet_Add "Reverent Light" patchheal
    /call AbilitySet_Add "Ardent Light" patchheal
|    /call AbilitySet_Add "Merciful Light" patchheal
|    /call AbilitySet_Add "Sincere Light" patchheal
    /call AbilitySet_Add "Fervent Light" patchheal
    /call AbilitySet_Add "Undying Life" patchheal
    /call AbilitySet_Add "Dissident Blessing" patchheal
    /call AbilitySet_Add "Composite Blessing" patchheal
    /call AbilitySet_Add "Ecliptic Blessing" patchheal

    /call AbilitySet_ChooseOuter patchheal1 patchheal
    /call AbilitySet_ChooseOuter patchheal2 patchheal "${patchheal1}"

|--- 11th-17th Rejuv Spell Line Clutch Heals Require Life below 35-45% to cast
    /call AbilitySet_Add "Eleventh-Hour" ClutchHeal 
    /call AbilitySet_Add "Twelfth Night" ClutchHeal
    /call AbilitySet_Add "Thirteenth Salve" ClutchHeal
    /call AbilitySet_Add "Fourteenth Catalyst" ClutchHeal
    /call AbilitySet_Add "Fifteenth Emblem" ClutchHeal
    /call AbilitySet_Add "Sixteenth Serenity" ClutchHeal
    /call AbilitySet_Add "Seventeenth Rejuvenation" ClutchHeal
    /call AbilitySet_Add "Eighteenth Rejuvenation" ClutchHeal
    /call AbilitySet_Add "Nineteenth Commandment" ClutchHeal
    /call AbilitySet_ChooseOuter ClutchHeal ClutchHeal
    
|---Group Heals Slot 5 
    /call AbilitySet_Add "Word of Health" groupheal
    /call AbilitySet_Add "Word of Healing" groupheal
    /call AbilitySet_Add "Word of Vigor" groupheal
    /call AbilitySet_Add "Word of Restoration" groupheal
| - 12 second Cast makes this Spell Unfeasible
|   /call AbilitySet_Add "Word of Redemption" groupheal
    /call AbilitySet_Add "Word of Replenishment" groupheal
    /call AbilitySet_Add "Word of Vivification" groupheal
    /call AbilitySet_Add "Word of Vivacity" groupheal
    /call AbilitySet_Add "Word of Recovery" groupheal
    /call AbilitySet_Add "Word of Resurgence" groupheal
    /call AbilitySet_Add "Word of Rehabilitation" groupheal
    /call AbilitySet_Add "Word of Reformation" groupheal
    /call AbilitySet_Add "Word of Greater Reformation" groupheal
    /call AbilitySet_Add "Word of Greater Restoration" groupheal
    /call AbilitySet_Add "Word of Greater Replenishment" groupheal
    /call AbilitySet_Add "Word of Greater Rejuvenation" groupheal
    /call AbilitySet_Add "Word of Greater Vivification" groupheal
    /call AbilitySet_ChooseOuter groupheal groupheal
        
|---Group Heals No Cure Slot 5
	/call AbilitySet_Add "Word of Health" grouphealnocure
    /call AbilitySet_Add "Word of Healing" grouphealnocure
    /call AbilitySet_Add "Word of Vigor" grouphealnocure
    /call AbilitySet_Add "Word of Redemption" grouphealnocure
    /call AbilitySet_Add "Word of Awakening" grouphealnocure
    /call AbilitySet_Add "Word of Recuperation" grouphealnocure
    /call AbilitySet_Add "Word of Renewal" grouphealnocure
    /call AbilitySet_Add "Word of Convalescence" grouphealnocure
    /call AbilitySet_Add "Word of Mending" grouphealnocure
    /call AbilitySet_Add "Word of Soothing" grouphealnocure
    /call AbilitySet_Add "Word of Redress" grouphealnocure
    /call AbilitySet_Add "Word of Acceptance" grouphealnocure
    /call AbilitySet_ChooseOuter grouphealnocure grouphealnocure "${groupheal}"
    
|---Group Fast Heal 103+ Only
    /call AbilitySet_Add "Syllable of Acceptance"       groupfastheal
    /call AbilitySet_Add "Syllable of Convalescence"    groupfastheal
    /call AbilitySet_Add "Syllable of Mending"          groupfastheal
    /call AbilitySet_Add "Syllable of Soothing"         groupfastheal
    /call AbilitySet_Add "Syllable of Invigoration"     groupfastheal
    /call AbilitySet_ChooseOuter groupfastheal groupfastheal

|---Yaulp Setup Pre-91 AA
    /call AbilitySet_Add "Yaulp V" yaulpspell
    /call AbilitySet_Add "Yaulp VI" yaulpspell
    /call AbilitySet_Add "Yaulp VII" yaulpspell
    /call AbilitySet_Add "Yaulp VIII" yaulpspell
    /call AbilitySet_Add "Yaulp IX" yaulpspell
    /call AbilitySet_Add "Yaulp X" yaulpspell
    /call AbilitySet_Add "Yaulp XI" yaulpspell
    /call AbilitySet_ChooseOuter yaulpspell yaulpspell

|---Renewal Big Heal Lines
	/call AbilitySet_Add "Desperate Renewal" bigheal
    /call AbilitySet_Add "Frantic Renewal" bigheal
    /call AbilitySet_Add "Frenetic Renewal" bigheal
    /call AbilitySet_Add "Frenzied Renewal" bigheal
    /call AbilitySet_Add "Fervent Renewal" bigheal
    /call AbilitySet_Add "Fraught Renewal" bigheal
    /call AbilitySet_Add "Furial Renewal" bigheal
    /call AbilitySet_Add "Dire Renewal" bigheal
    /call AbilitySet_Add "Determined Renewal" bigheal
    /call AbilitySet_Add "Heroic Renewal" bigheal
    /call AbilitySet_ChooseOuter bigheal1 bigheal
    /call AbilitySet_ChooseOuter bigheal2 bigheal "${bigheal1}"

| - Anticipated Heal Line
    /call AbilitySet_Add "Anticipated Interposition" AnticipatedHeal
    /call AbilitySet_Add "Anticipated Intercession" AnticipatedHeal
    /call AbilitySet_Add "Anticipated Intervention" AnticipatedHeal
    /call AbilitySet_Add "Anticipated Intercalation" AnticipatedHeal
    /call AbilitySet_Add "Anticipated Interdiction" AnticipatedHeal
    /call AbilitySet_ChooseOuter AnticipatedHeal AnticipatedHeal     

|- Group Hot Line - Elixirs No Cure
    /call AbilitySet_Add "Elixir of Expiation" GroupHot
    /call AbilitySet_Add "Elixir of the Ardent" GroupHot
    /call AbilitySet_Add "Elixir of the Beneficent" GroupHot
    /call AbilitySet_Add "Elixir of the Acquittal" GroupHot
    /call AbilitySet_Add "Elixir of the Seas" GroupHot
    /call AbilitySet_Add "Elixir of Wulthan" GroupHot
    /call AbilitySet_Add "Elixir of Transcendence" GroupHot
    /call AbilitySet_Add "Elixir of Benevolence" GroupHot
    /call AbilitySet_Add "Elixir of Realization" GroupHot
    /call AbilitySet_ChooseOuter GroupHot GroupHot

| - Group Hot Line Cure + Hot 99+
    /call AbilitySet_Add "Cleansing Acquittal" GroupHotCure
    /call AbilitySet_Add "Ardent Acquittal" GroupHotCure
    /call AbilitySet_Add "Merciful Acquittal" GroupHotCure
    /call AbilitySet_Add "Sincere Acquittal" GroupHotCure
    /call AbilitySet_Add "Devout Acquittal" GroupHotCure
    /call AbilitySet_Add "Avowed Acquittal" GroupHotCure
    /call AbilitySet_ChooseOuter GroupHotCure GroupHotCure

|---Heal Tank and Nuke Tanks Target _ Intervention Lines
	/call AbilitySet_Add "Holy Intervention" healnuke
    /call AbilitySet_Add "Celestial Intervention" healnuke
    /call AbilitySet_Add "Elysian Intervention" healnuke
    /call AbilitySet_Add "Virtuous Intervention" healnuke
    /call AbilitySet_Add "Mystical Intervention" healnuke
    /call AbilitySet_Add "Merciful Intervention" healnuke
    /call AbilitySet_Add "Sincere Intervention" healnuke
    /call AbilitySet_Add "Atoned Intervention" healnuke
    /call AbilitySet_Add "Avowed Intervention" healnuke
    /call AbilitySet_ChooseOuter healnuke1 healnuke
    /call AbilitySet_ChooseOuter healnuke2 healnuke "${healnuke1}"
        
|---Nuke Target and Heal Tank -  Dps Heals
    /call AbilitySet_Add "Holy Contravention" nukeheal
    /call AbilitySet_Add "Celestial Contravention" nukeheal
    /call AbilitySet_Add "Elysian Contravention" nukeheal
    /call AbilitySet_Add "Virtuous Contravention" nukeheal
    /call AbilitySet_Add "Ardent Contravention" nukeheal
    /call AbilitySet_Add "Merciful Contravention" nukeheal
    /call AbilitySet_Add "Sincere Contravention" nukeheal
    /call AbilitySet_Add "Divine Contravention" nukeheal
    /call AbilitySet_Add "Avowed Contravention" nukeheal
    /call AbilitySet_ChooseOuter nukeheal1 nukeheal
    /call AbilitySet_ChooseOuter nukeheal2 nukeheal "${nukeheal1}"

|---Stun Nukes - DISABLED Auto mem
    /call AbilitySet_Add "Aweshake" stunnuke
    /call AbilitySet_Add "Awecrash" stunnuke
    /call AbilitySet_Add "Aweburst" stunnuke
    /call AbilitySet_Add "Aweclash" stunnuke
    /call AbilitySet_Add "Awecrush" stunnuke
    /call AbilitySet_Add "Awestrike" stunnuke
    /call AbilitySet_Add "Aweflash" stunnuke
    /call AbilitySet_Add "Aweblast" stunnuke
    /call AbilitySet_Add "Awebolt" stunnuke
    /call AbilitySet_ChooseOuter stunnuke stunnuke

|---Hand of Infusion Line
    /call AbilitySet_Add "Hand of Faithful Infusion" InfusionHand
    /call AbilitySet_Add "Hand of Graceful Infusion" InfusionHand
    /call AbilitySet_Add "Hand of Merciful Infusion" InfusionHand
    /call AbilitySet_Add "Hand of Sincere Infusion" InfusionHand
    /call AbilitySet_Add "Hand of Unyielding Infusion" InfusionHand
    /call AbilitySet_Add "Hand of Avowed Infusion" InfusionHand
    /call AbilitySet_ChooseOuter InfusionHand InfusionHand

|---Promised Heals
	/call AbilitySet_Add "Promised Renewal" promheal
    /call AbilitySet_Add "Promised Restoration" promheal
    /call AbilitySet_Add "Promised Recuperation" promheal
    /call AbilitySet_Add "Promised Resurgence" promheal
	/call AbilitySet_Add "Promised Restitution" promheal
    /call AbilitySet_Add "Promised Reformation" promheal
    /call AbilitySet_Add "Promised Rehabilitation" promheal
    /call AbilitySet_Add "Promised Remedy" promheal
	/call AbilitySet_Add "Promised Redemption" promheal
    /call AbilitySet_Add "Promised Reclamation" promheal
    /call AbilitySet_Add "Promised Remediation" promheal
    /call AbilitySet_ChooseOuter promheal promheal

|--Group Buff All Levels starts at 45 - Group Aego Buff
    /call AbilitySet_Add "Courage" AegoBuff
    /call AbilitySet_Add "Center" AegoBuff
    /call AbilitySet_Add "Daring" AegoBuff
    /call AbilitySet_Add "Bravery" AegoBuff
    /call AbilitySet_Add "Valor" AegoBuff
|   /call AbilitySet_Add "Resolution" AegoBuff
    /call AbilitySet_Add "Temperance" AegoBuff
   /call AbilitySet_Add "Blessing of Temperance" AegoBuff
|    /call AbilitySet_Add "Heroic Bond" AegoBuff
    /call AbilitySet_Add "Blessing of Aegolism" AegoBuff
    /call AbilitySet_Add "Hand of Virtue" AegoBuff
    /call AbilitySet_Add "Hand of Conviction" AegoBuff    
    /call AbilitySet_Add "Hand of Tenacity" AegoBuff
    /call AbilitySet_Add "Hand Of Temerity" AegoBuff
    /call AbilitySet_Add "Hand of Gallantry" AegoBuff    
    /call AbilitySet_Add "Hand of Reliance" AegoBuff
    /call AbilitySet_Add "Unified Hand of Credence" AegoBuff
    /call AbilitySet_Add "Unified Hand of Certitude" AegoBuff
    /call AbilitySet_Add "Unified Hand of Surety" AegoBuff   
    /call AbilitySet_Add "Unified Hand of Assurance" AegoBuff
    /call AbilitySet_Add "Unified Hand of Righteousness" AegoBuff
    /call AbilitySet_Add "Unified Hand of Persistence" AegoBuff
    /call AbilitySet_Add "Unified Hand of Helmsbane" AegoBuff
    /call AbilitySet_ChooseOuter AegoBuff AegoBuff
    
|--Self Buff for Mana Regen and armor
    /call AbilitySet_Add "Armor of Protection" SelfBuffhp
	/call AbilitySet_Add "Blessed Armor of the Risen" SelfBuffhp
    /call AbilitySet_Add "Ancient: High Priest's Bulwark" SelfBuffhp
    /call AbilitySet_Add "Armor of the Zealot" SelfBuffhp
    /call AbilitySet_Add "Armor of the Pious" SelfBuffhp
    /call AbilitySet_Add "Armor of the Sacred" SelfBuffhp
    /call AbilitySet_Add "Armor of the Solemn" SelfBuffhp
    /call AbilitySet_Add "Armor of the Devout" SelfBuffhp
    /call AbilitySet_Add "Armor of the Earnest" SelfBuffhp
    /call AbilitySet_Add "Armor of the Zealous" SelfBuffhp
    /call AbilitySet_Add "Armor of the Reverent" SelfBuffhp
    /call AbilitySet_Add "Armor of the Ardent" SelfBuffhp
    /call AbilitySet_Add "Armor of the Merciful" SelfBuffhp
    /call AbilitySet_Add "Armor of Sincerity" SelfBuffhp
    /call AbilitySet_Add "Armor of Penance" SelfBuffhp
    /call AbilitySet_Add "Armor of the Avowed" SelfBuffhp
    /call AbilitySet_ChooseOuter  SelfBuffhp SelfBuffhp
       
|--Self buff casts group heal on AE spell damage
	/call AbilitySet_Add "Divine Consequence" GroupHealProcBuff
    /call AbilitySet_Add "Divine Reaction" GroupHealProcBuff
    /call AbilitySet_Add "Divine Response" GroupHealProcBuff
    /call AbilitySet_Add "Divine Contingency" GroupHealProcBuff
    /call AbilitySet_ChooseOuter GroupHealProcBuff GroupHealProcBuff
    
|--Tank Buff Traditionally Shining Series of Buffs
    /call AbilitySet_Add "Holy Armor" TankBuff
    /call AbilitySet_Add "Spirit Armor" TankBuff
    /call AbilitySet_Add "Armor of Faith" TankBuff
    /call AbilitySet_Add "Shining Rampart" TankBuff
    /call AbilitySet_Add "Shining Armor" TankBuff
    /call AbilitySet_Add "Shining Bastion" TankBuff
    /call AbilitySet_Add "Shining Bulwark" TankBuff
    /call AbilitySet_Add "Shining Fortress" TankBuff
    /call AbilitySet_Add "Shining Aegis" TankBuff
    /call AbilitySet_Add "Shining Fortitude" TankBuff
    /call AbilitySet_Add "Shining Steel" TankBuff
    /call AbilitySet_ChooseOuter TankBuff TankBuff

|--Group Vie Buff
    /call AbilitySet_Add "Rallied Aegis of Vie" GroupVieBuff
    /call AbilitySet_Add "Rallied Shield of Vie" GroupVieBuff
    /call AbilitySet_Add "Rallied Palladium of Vie" GroupVieBuff
    /call AbilitySet_Add "Rallied Rampart of Vie" GroupVieBuff
    /call AbilitySet_Add "Rallied Armor of Vie" GroupVieBuff
    /call AbilitySet_Add "Rallied Bastion of Vie" GroupVieBuff
    /call AbilitySet_Add "Rallied Greater Ward of Vie" GroupVieBuff
    /call AbilitySet_Add "Rallied Greater Guard of Vie" GroupVieBuff
    /call AbilitySet_Add "Rallied Greater Protection of Vie" GroupVieBuff
    /call AbilitySet_Add "Rallied Greater Aegis of Vie" GroupVieBuff
    /call AbilitySet_ChooseOuter GroupVieBuff GroupVieBuff
    
|--Aura Buffs - Aura Name is seperate than the buff name
    /call AbilitySet_AddAura "Aura of the Pious" "Aura of the Pious" aurabuff1
    /call AbilitySet_AddAura "Aura of the Zealot" "Aura of the Zealot" aurabuff1
    /call AbilitySet_AddAura "Aura of the Reverent" "Reverent Aura" aurabuff1
    /call AbilitySet_AddAura "Aura of the Persistent" "Aura of the Persistent" aurabuff1
    /call AbilitySet_ChooseOuter aurabuff1 aurabuff1
    /varset aurabuff1_name ${GetAuraName[${aurabuff1},aurabuff1]}

|-- Aura Buff 2 - Aura Name is the same as the buff name
    /call AbilitySet_Add "Bastion of Divinity" aurabuff2
    /call AbilitySet_Add "Circle of Divinity" aurabuff2
    /call AbilitySet_Add "Aura of Divinity" aurabuff2
    /call AbilitySet_ChooseOuter aurabuff2 aurabuff2
    
|--Divine Buffs REQUIRES extra spell slot because of the 90s recast
    /call AbilitySet_Add "Death Pact" DivineBuff
    /call AbilitySet_Add "Divine Intervention" DivineBuff
    /call AbilitySet_Add "Divine Intercession" DivineBuff
    /call AbilitySet_Add "Divine Invocation" DivineBuff
    /call AbilitySet_Add "Divine Interposition" DivineBuff
    /call AbilitySet_Add "Divine Indemnification" DivineBuff
    /call AbilitySet_Add "Divine Imposition" DivineBuff
    /call AbilitySet_Add "Divine Intermediation" DivineBuff
    /call AbilitySet_Add "Divine Interference" DivineBuff
    /call AbilitySet_ChooseOuter DivineBuff DivineBuff

|--Reverse Damage Shield Proc (LVL >=85) -- Ignoring the ReverseDS Mark Line
    /call AbilitySet_Add "Erud's Retort" ReverseDS
    /call AbilitySet_Add "Fintar's Retort" ReverseDS
    /call AbilitySet_Add "Galvos' Retort" ReverseDS
    /call AbilitySet_Add "Olsif's Retort" ReverseDS
    /call AbilitySet_Add "Vicarum's Retort" ReverseDS
    /call AbilitySet_Add "Curate's Retort" ReverseDS
    /call AbilitySet_Add "Jorlleag's Retort" ReverseDS
    /call AbilitySet_Add "Axoeviq's Retort" ReverseDS
    /call AbilitySet_ChooseOuter ReverseDS ReverseDS
    
| -- Spell Speed Blessings 15-92(112)Becomes Defunct due to Unifieds.)
 |   /call AbilitySet_Add "Benediction of Resplendence" SpellBlessing
    /call AbilitySet_Add "Blessing of Piety" SpellBlessing
    /call AbilitySet_Add "Blessing of Faith" SpellBlessing
    /call AbilitySet_Add "Blessing of Reverence" SpellBlessing
    /call AbilitySet_Add "Aura of Reverence" SpellBlessing
    /call AbilitySet_Add "Blessing of Devotion" SpellBlessing
    /call AbilitySet_Add "Aura of Devotion" SpellBlessing
    /call AbilitySet_Add "Blessing of Purpose" SpellBlessing
    /call AbilitySet_Add "Aura of Purpose" SpellBlessing
    /call AbilitySet_Add "Blessing of Resolve" SpellBlessing
    /call AbilitySet_Add "Aura of Resolve" SpellBlessing
    /call AbilitySet_Add "Blessing of Loyalty" SpellBlessing
    /call AbilitySet_Add "Aura of Loyalty" SpellBlessing
    /call AbilitySet_Add "Blessing of Will" SpellBlessing
    /call AbilitySet_Add "Hand of Will" SpellBlessing
    /call AbilitySet_Add "Blessing of Fervor" SpellBlessing
    /call AbilitySet_Add "Hand of Fervor" SpellBlessing
    /call AbilitySet_Add "Benediction of Piety" SpellBlessing
    /call AbilitySet_Add "Hand of Zeal" SpellBlessing
    /call AbilitySet_ChooseOuter SpellBlessing SpellBlessing

|--Symbols
	/call AbilitySet_Add "Symbol of Transal" SingleSymbolBuff
    /call AbilitySet_Add "Symbol of Ryltan" SingleSymbolBuff
    /call AbilitySet_Add "Symbol of Pinzarn" SingleSymbolBuff
    /call AbilitySet_Add "Symbol of Naltron" SingleSymbolBuff
    /call AbilitySet_Add "Symbol of Marzin" SingleSymbolBuff	
    /call AbilitySet_Add "Symbol of Kazad" SingleSymbolBuff
    /call AbilitySet_Add "Symbol of Balikor" SingleSymbolBuff
    /call AbilitySet_Add "Symbol of Elushar" SingleSymbolBuff
    /call AbilitySet_Add "Symbol of Kaerra" SingleSymbolBuff	
    /call AbilitySet_Add "Symbol of Darianna" SingleSymbolBuff
    /call AbilitySet_Add "Symbol of Ealdun" SingleSymbolBuff
    /call AbilitySet_Add "Unity of the Triumvirate" SingleSymbolBuff
    /call AbilitySet_Add "Unity of Gezat" SingleSymbolBuff	
    /call AbilitySet_Add "Unity of Nonia" SingleSymbolBuff
    /call AbilitySet_Add "Unity of Emra" SingleSymbolBuff
    /call AbilitySet_Add "Unity of Jorlleag" SingleSymbolBuff
    /call AbilitySet_Add "Unity of Helmsbane" SingleSymbolBuff
    /call AbilitySet_ChooseOuter SingleSymbolBuff SingleSymbolBuff

|--Group Symbols
	/call AbilitySet_Add "Symbol of Transal" SymbolBuff
    /call AbilitySet_Add "Symbol of Ryltan" SymbolBuff
    /call AbilitySet_Add "Symbol of Pinzarn" SymbolBuff
    /call AbilitySet_Add "Symbol of Naltron" SymbolBuff
    /call AbilitySet_Add "Symbol of Marzin" SymbolBuff
    /call AbilitySet_Add "Naltron's Mark" SymbolBuff
    /call AbilitySet_Add "Kazad's Mark" SymbolBuff
    /call AbilitySet_Add "Balikor's Mark" SymbolBuff
    /call AbilitySet_Add "Elushar's Mark" SymbolBuff
    /call AbilitySet_Add "Kaerra's Mark" SymbolBuff
    /call AbilitySet_Add "Darianna's Mark" SymbolBuff
    /call AbilitySet_Add "Ealdun's Mark" SymbolBuff
    /call AbilitySet_Add "Unified Hand of the Triumvirate" SymbolBuff
    /call AbilitySet_Add "Unified Hand of Gezat" SymbolBuff
    /call AbilitySet_Add "Unified Hand of Nonia" SymbolBuff
    /call AbilitySet_Add "Unified Hand of Emra" SymbolBuff
    /call AbilitySet_Add "Unified Hand of Jorlleag" SymbolBuff
    /call AbilitySet_Add "Unified Hand of Assurance" SymbolBuff
    /call AbilitySet_Add "Unified Hand of the Diabo" SymbolBuff
    /call AbilitySet_Add "Unified Hand of Infallibility" SymbolBuff
    /call AbilitySet_ChooseOuter SymbolBuff SymbolBuff
        
|--Single Target HP Buffs
	/call AbilitySet_Add "Courage" HPBuff
    /call AbilitySet_Add "Center" HPBuff
    /call AbilitySet_Add "Daring" HPBuff
    /call AbilitySet_Add "Bravery" HPBuff
    /call AbilitySet_Add "Valor" HPBuff
    /call AbilitySet_Add "Heroism" HPBuff
    /call AbilitySet_Add "Temperance" HPBuff
    /call AbilitySet_Add "Aegolism" HPBuff
    /call AbilitySet_Add "Virtue" HPBuff
    /call AbilitySet_Add "Conviction" HPBuff
    /call AbilitySet_Add "Tenacity" HPBuff
    /call AbilitySet_Add "Temerity" HPBuff
    /call AbilitySet_Add "Gallantry" HPBuff
    /call AbilitySet_Add "Reliance" HPBuff
    /call AbilitySet_Add "Unified Credence" HPBuff
    /call AbilitySet_Add "Unified Certitude" HPBuff
    /call AbilitySet_Add "Unified Surety" HPBuff
    /call AbilitySet_Add "Unified Assurance" HPBuff
    /call AbilitySet_Add "Unified Righteousness" HPBuff
    /call AbilitySet_Add "Unified Persistence" HPBuff
    /call AbilitySet_Add "Unified Commitment" HPBuff
    /call AbilitySet_ChooseOuter HPBuff HPBuff
      
|--- Spell Cure------|
    /call AbilitySet_Add "Expurgated Blood" Icespellcure
    /call AbilitySet_Add "Unblemished Blood" Icespellcure
    /call AbilitySet_Add "Cleansed Blood" Icespellcure
    /call AbilitySet_Add "Perfected Blood" Icespellcure
    /call AbilitySet_Add "Purged Blood" Icespellcure
    /call AbilitySet_Add "Sanctified Blood" Icespellcure
    /Call AbilitySet_ChooseOuter Icespellcure Icespellcure

|--AllianceBuff
    /call AbilitySet_Add "Sincere Coalition" AllianceBuff
    /call AbilitySet_Add "Divine Alliance"  AllianceBuff
    /call AbilitySet_ChooseOuter AllianceBuff AllianceBuff
|- Heal over time Elixir Spell
	/call AbilitySet_Add "Celestial Remedy" SingleHot
    /call AbilitySet_Add "Celestial Health" SingleHot
    /call AbilitySet_Add "Celestial Healing" SingleHot
    /call AbilitySet_Add "Celestial Elixir" SingleHot
    /call AbilitySet_Add "Supernal Elixir" SingleHot
    /call AbilitySet_Add "Holy Elixir" SingleHot
    /call AbilitySet_Add "Pious Elixir" SingleHot
    /call AbilitySet_Add "Sacred Elixir" SingleHot
    /call AbilitySet_Add "Solemn Elixir" SingleHot
    /call AbilitySet_Add "Devout Elixir" SingleHot
    /call AbilitySet_Add "Earnest Elixir" SingleHot
    /call AbilitySet_Add "Zealous Elixir" SingleHot
	/call AbilitySet_Add "Reverent Elixir" SingleHot
	/call AbilitySet_Add "Ardent Elixir" SingleHot
	/call AbilitySet_Add "Merciful Elixir" SingleHot
	/call AbilitySet_Add "Sincere Elixir" SingleHot
    /call AbilitySet_Add "Hallowed Elixir" SingleHot
    /call AbilitySet_Add "Avowed Elixir" SingleHot
	/call AbilitySet_ChooseOuter SingleHot SingleHot "${wardspell}"
|- DPS Spells
|- Hammer Pet
	/call AbilitySet_Add "Unswerving Hammer of Faith" Hammerpet
	/call AbilitySet_Add "Unswerving Hammer of Retribution" Hammerpet
	/call AbilitySet_Add "Unflinching Hammer of Zeal" Hammerpet
	/call AbilitySet_Add "Indomitable Hammer of Zeal" Hammerpet
	/call AbilitySet_Add "Unwavering Hammer of Zeal" Hammerpet
	/call AbilitySet_Add "Devout Hammer of Zeal" Hammerpet
	/call AbilitySet_Add "Infallible Hammer of Zeal" Hammerpet
	/call AbilitySet_Add "Infallible Hammer of Reverence" Hammerpet
	/call AbilitySet_Add "Ardent Hammer of Zeal" Hammerpet
	/call AbilitySet_Add "Unyielding Hammer of Zeal" Hammerpet
	/call AbilitySet_Add "Unyielding Hammer of Obliteration" Hammerpet
    /call AbilitySet_Add "Incorruptible Hammer of Obliteration" Hammerpet
    /call AbilitySet_Add "Unrelenting Hammer of Zeal" Hammerpet
	/call AbilitySet_ChooseOuter Hammerpet Hammerpet
	
|- Censure Healing TwinCast Nuke used for Battle Mode
	/call AbilitySet_Add "Glorious Denunciation" twincastnuke
	/call AbilitySet_Add "Glorious Censure" twincastnuke
	/call AbilitySet_Add "Glorious Admonition" twincastnuke
	/call AbilitySet_Add "Glorious Rebuke" twincastnuke
	/call AbilitySet_Add "Glorious Judgment" twincastnuke
	/call AbilitySet_Add "Unyielding Judgment" twincastnuke
	/call AbilitySet_Add "Unyielding Censure" twincastnuke
    /call AbilitySet_Add "Unyielding Rebuke" twincastnuke
    /call AbilitySet_Add "Unyielding Admonition" twincastnuke
	/call AbilitySet_ChooseOuter twincastnuke twincastnuke
	
| - Single target Curse Removal Line.
    /call AbilitySet_Add "Remove Minor Curse" CureCurse
    /call AbilitySet_Add "Remove Lesser Curse" CureCurse
    /call AbilitySet_Add "Remove Curse" CureCurse
    /call AbilitySet_Add "Remove Greater Curse" CureCurse
    /call AbilitySet_Add "Eradicate Curse" CureCurse
    /call AbilitySet_Add "Purged Blood" CureCurse
    /call AbilitySet_Add "Perfected Blood" CureCurse
    /call AbilitySet_Add "Cleansed Blood" CureCurse
    /call AbilitySet_Add "Unblemished Blood" CureCurse
    /call AbilitySet_Add "Expurgated Blood" CureCurse
    /call AbilitySet_Add "Sanctified Blood" CureCurse
    /call AbilitySet_ChooseOuter CureCurse CureCurse

| - Cure Corrupt Single Target Cures. begins at level 74 and Evolves into Blood Line for Cureall.
    /call AbilitySet_Add "Expunge Corruption" CureCorrupt
    /call AbilitySet_Add "Vitiate Corruption" CureCorrupt
    /call AbilitySet_Add "Abolish Corruption" CureCorrupt
    /call AbilitySet_Add "Pristine Blood" CureCorrupt
    /call AbilitySet_Add "Dissolve Corruption" CureCorrupt
    /call AbilitySet_Add "Perfected Blood" CureCorrupt
    /call AbilitySet_Add "Cleansed Blood" CureCorrupt
    /call AbilitySet_Add "Unblemished Blood" CureCorrupt
    /call AbilitySet_Add "Expurgated Blood" CureCorrupt
    /call AbilitySet_Add "Purged Blood" CureCorrupt
    /call AbilitySet_Add "Sanctified Blood" CureCorrupt
    /call AbilitySet_ChooseOuter CureCorrupt CureCorrupt

    |- Cure Diease Lines Single Target
    /call AbilitySet_Add "Cure Disease" CureDisease
    /call AbilitySet_Add "Counteract Disease" CureDisease
    /call AbilitySet_Add "Pure Blood" CureDisease
    /call AbilitySet_Add "Eradicate Disease" CureDisease
    /call AbilitySet_Add "Purified Blood" CureDisease
    /call AbilitySet_Add "Purged Blood" CureDisease
    /call AbilitySet_Add "Perfected Blood" CureDisease
    /call AbilitySet_Add "Cleansed Blood" CureDisease
    /call AbilitySet_Add "Unblemished Blood" CureDisease
    /call AbilitySet_Add "Expurgated Blood" CureDisease
    /call AbilitySet_Add "Sanctified Blood" CureDisease
    /call AbilitySet_ChooseOuter CureDisease CureDisease
    
    |- Cure Poison Lines Single target
    /call AbilitySet_Add "Cure Poison" CurePoison
    /call AbilitySet_Add "Counteract Poison" CurePoison
    /call AbilitySet_Add "Abolish Poison" CurePoison
    /call AbilitySet_Add "Eradicate Poison" CurePoison
    /call AbilitySet_Add "Antidote" CurePoison
    /call AbilitySet_Add "Purged Blood" CurePoison
    /call AbilitySet_Add "Perfected Blood" CurePoison
    /call AbilitySet_Add "Cleansed Blood" CurePoison
    /call AbilitySet_Add "Unblemished Blood" CurePoison
    /call AbilitySet_Add "Expurgated Blood" CurePoison
    /call AbilitySet_Add "Sanctified Blood" CurePoison
    /call AbilitySet_ChooseOuter CurePoison CurePoison

|- Rez Spell Lines 
    /call AbilitySet_Add "Superior Reviviscence" AERezSpell
    /call AbilitySet_Add "Eminent Reviviscence" AERezSpell
    /call AbilitySet_Add "Greater Reviviscence" AERezSpell
    /call AbilitySet_Add "Larger Reviviscence" AERezSpell
    /call AbilitySet_ChooseOuter AERezSpell AERezSpell


    /call AbilitySet_Add "Reviviscence" RezSpell
    /call AbilitySet_Add "Resurrection" RezSpell
    /call AbilitySet_Add "Restoration" RezSpell
    /call AbilitySet_Add "Resuscitate" RezSpell
    /call AbilitySet_Add "Renewal" RezSpell
    /call AbilitySet_Add "Revive" RezSpell
    /call AbilitySet_Add "Reparation" RezSpell
    /call AbilitySet_Add "Reconstitution" RezSpell
    /call AbilitySet_Add "Reanimation" RezSpell
    /call AbilitySet_ChooseOuter RezSpell RezSpell

	|- THis creates a ChatBegList object with the name 'CLRBegs'
    /call ChatBegList_Add CLRBegs tlpcurep Spell "${CurePoison}"    sender TRUE
    /call ChatBegList_Add CLRBegs tlpcured Spell "${CureDisease}"   sender TRUE
	/call ChatBegList_Add CLRBegs cureme   AA    "Radiant Cure"     sender TRUE
    /call ChatBegList_Add CLRBegs rgc      Spell "${Icespellcure}"  sender TRUE
    /call ChatBegList_Add CLRBegs purifyme AA    "Purify Soul"      sender TRUE
    |- Configure Cure Spells
    |- All Cures eventually become the Same Spell But have there own variables Still And for until that Occurs.
   /if (${RG_CanUseAA[Radiant Cure]}) {
        /call Cure_AddAll  "Radiant Cure" AA "Radiant Cure" AA "Radiant Cure" AA "Radiant Cure" AA
    } else {
        /call Cure_AddAll "${CureDisease}" Spell "${CurePoison}" Spell "${CureCurse}" Spell "${CureCorrupt}" Spell
    }
/return

Sub CLR_ModeConfigMODEHEAL
    /varset IsHealing TRUE
    /varset IsCuring TRUE
    /if (${Me.Level} <66) {
        /echo - Try /rg classmode 2 for TLP/LowLevel healing Modes.
    } else { 
        /echo Healer Mode is turned on Melee is By Default off. Nukes are on Starting @ 90%  u can Also Try /rg ClassMode 1 for Cleric Battle Mode.
    }
    /varset AutoAssistAt[SETTINGVAL] 90
    /varset DoNuke[SETTINGVAL] 1
    /varset NukePct[SETTINGVAL] 90
    /varset DoMelee[SETTINGVAL] 0
    
    | - Spellbar setup for Cleric
    |**
    /varset Spell1 ${remedyheal1}
    /varset Spell2 ${remedyheal2}
    /varset Spell3 ${patchheal1}
    /varset Spell4 ${patchheal2}
    /varset Spell5 ${wardspell}
    /varset Spell6 ${groupheal}
    /varset Spell7 ${HPBuff}
    /if (${Me.NumGems}>=9) { 
        /varset Spell8 ${MagicNuke}
        } else { 
        /varset Spell8 NULL
    }
    **|
    /varset Spell1 ${remedyheal1}
    /varset Spell2 ${remedyheal2}
     /if (${DivineBuffOn[SETTINGVAL]}) {
        /varset Spell3 ${DivineBuff}
        } else {
        /if (!${DivineBuffOn[SETTINGVAL]}) {
            /if (!${DoClutchHeal[SETTINGVAL]} && ${DoHots[SETTINGVAL]})  /varset Spell3 ${SingleHot}
        } else {
                /varset Spell3 ${ClutchHeal}
        }
    /varset Spell4 ${patchheal1} 
    /varset Spell5 ${twincastnuke}
    | - A level check if should go here to mem wardspell 2 for Rizlona and Lower levels.

    /if ( ${RG_CanUseAA[Yaulp]} && (${Spell[${yaulpspell}].Level}<=${Spell[${Me.AltAbility[Yaulp].Spell.BaseName}].Level}) ) {
            |${Spell[${Me.AltAbility[Yaulp].Spell.Trigger[1].BaseName}].Level}
            /varset Spell6 ${Icespellcure}
        } else {
            /varset Spell6 ${yaulpspell}
        }
    /if (${DoHots[SETTINGVAL]}) {
            /varset Spell7 ${GroupHot}
        } else {
            /varset Spell7 ${groupheal}
        }
    /varset Spell8 ${groupfastheal}
    /varset Spell9 ${healnuke1}
    /varset Spell10 ${nukeheal1}
    /varset Spell11 ${ReverseDS}
    /varset Spell12 ${promheal}
    /varset Spell13 ${GroupHealProcBuff}
    }
 
    |- Rotations
    |- Self Buffs
    /call CLR_DefaultSelfBuffRotationConfig CLR_Downtime_MODEHEAL_Rotation
    |- Group Buffs
    /call CLR_DefaultBuffGroupConfig
    |- Heals
    /call CLR_DefaultHealRotationConfig
  
	|- DPS heals
	/call AddToRotation CLR_DPS_MODEHEAL_Rotation "Turn Undead"       AA   ${Parse[0,"( ${Target.Body.Name.Equal[Undead]} )"]}
    /call AddToRotation CLR_DPS_MODEHEAL_Rotation "${nukeheal1}"    Spell  ${Parse[0,"( ${Target.PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNuke[SETTINGVAL]} )"]}
	/call AddToRotation CLR_DPS_MODEHEAL_Rotation "${nukeheal2}"    Spell  ${Parse[0,"( ${Target.PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNuke[SETTINGVAL]} )"]}
	/call AddToRotation CLR_DPS_MODEHEAL_Rotation "${twincastnuke}" Spell  ${Parse[0,"( (${Target.PctHPs}<=${NukePct[SETTINGVAL]}) && (${DoNuke[SETTINGVAL]}) )"]}


	| - Burn AA Rotation
	/call AddToRotation CLR_Burn_MODEHEAL_Rotation 		"Celestial Hammer" AA TRUE
	/call AddToRotation CLR_Burn_MODEHEAL_Rotation 		"Flurry of Life" AA TRUE
	/call AddToRotation CLR_Burn_MODEHEAL_Rotation 		"Spire of the Vicar" AA TRUE
	/call AddToRotation CLR_Burn_MODEHEAL_Rotation 		"Turn Undead" AA ${Parse[0,"( ${Target.Body.Name.Equal[Undead]} )"]}
    /call AddToRotation CLR_Burn_MODEHEAL_Rotation      "Divine Avatar" AA  ${Parse[0,"( ${DoMelee[SETTINGVAL]} )"]}
    /call AddToRotation CLR_Burn_MODEHEAL_Rotation      "Divine Retribution" AA  ${Parse[0,"( TRUE )"]}

/return 
|---------------------------------|
Sub CLR_ModeConfigMODEBATTLE
    /varset IsHealing TRUE
    /Echo Battle Mode Detected to Turn on Melee try Melee Has Been Turned on As has Nuking. - Also You Recomended you Summon your Summoned Hammer weapon if Meleeing.
    /Echo This Mode is Intended for Heroic Level 85+ Toons. Default Values Are Adjusted for This Mode. 
    /varset AutoAssistAt[SETTINGVAL] 98
    /varset DoNuke[SETTINGVAL] 1
    /varset NukePct[SETTINGVAL] 95
    /varset DoMelee[SETTINGVAL] 1
    /varset Spell1 ${remedyheal1}
    /varset Spell2 ${remedyheal2}
    /varset Spell3 ${nukeheal1}
    /varset Spell4 ${nukeheal2}
    /varset Spell5 ${promheal}
    /varset Spell6 ${healnuke1}
    /varset Spell7 ${groupfastheal}
    /varset Spell8 ${patchheal1}
    /varset Spell9 ${ReverseDS}
    /varset Spell10 ${Icespellcure}
    /if (${DoHots[SETTINGVAL]}) {
    /varset Spell11 ${SingleHot}
    } else { 
    /varset Spell11 ${healnuke2}    
    }
    /varset Spell12 ${twincastnuke}
    /varset Spell13 Null
    |- Self Buffs
    /call CLR_DefaultSelfBuffRotationConfig CLR_Downtime_MODEHEAL_Rotation
    |- Group Buffs
    /call CLR_DefaultBuffGroupConfig
    |- Heals
    /call CLR_DefaultHealRotationConfig
    | - Burn AA Rotation
	/call AddToRotation CLR_Burn_MODEBATTLE_Rotation 	  "Celestial Hammer" AA TRUE
	/call AddToRotation CLR_Burn_MODEBATTLE_Rotation 	  "Flurry of Life" AA TRUE
	/call AddToRotation CLR_Burn_MODEBATTLE_Rotation 	  "Spire of the Vicar" AA TRUE
    /call AddToRotation CLR_Burn_MODEBATTLE_Rotation      "Divine Avatar" AA  ${Parse[0,"( ${DoMelee[SETTINGVAL]} )"]}
    /call AddToRotation CLR_Burn_MODEBATTLE_Rotation      "Divine Retribution" AA  ${Parse[0,"( TRUE )"]}
    /call AddToRotation CLR_Burn_MODEBATTLE_Rotation      "BattleFrenzy" AA  ${Parse[0,"( TRUE )"]}

	|- DPS heals
	/call AddToRotation CLR_DPS_MODEBATTLE_Rotation "Turn Undead" AA ${Parse[0,"( ${Target.Body.Name.Equal[Undead]} )"]}
    /call AddToRotation CLR_DPS_MODEBATTLE_Rotation "${nukeheal1}"    Spell   ${Parse[0,"( ${Target.PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNuke[SETTINGVAL]} )"]}
	/call AddToRotation CLR_DPS_MODEBATTLE_Rotation "${nukeheal2}"    Spell   ${Parse[0,"( ${Target.PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNuke[SETTINGVAL]} )"]}
	/call AddToRotation CLR_DPS_MODEBATTLE_Rotation "${InfusionHand}" Spell   ${Parse[0,"( ${Target.PctHPs}<=${AutoAssistAt[SETTINGVAL]} )"]}
    /call AddToRotation CLR_DPS_MODEBATTLE_Rotation "${twincastnuke}" Spell   ${Parse[0,"( ${Target.PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNuke[SETTINGVAL]} )"]}

/return

 

Sub CLR_ModeConfigMODETLP
    /varset IsHealing TRUE
    /varset IsCuring TRUE
    /Echo This Mode is Intended for ***TLP*** Type Servers Or Low Levels. It will not be Efficent at Higher Levels!
    /Echo Gem 8 is purposely left open for HotSwap.
    /varset AutoAssistAt[SETTINGVAL] 90  
    | - 1-65 spell bar Setup    
    |- Spell bar Is Determined By CH on or Off. as a Single Change to modify the Whole bar.
    /if ( ${DoCh[SETTINGVAL]}) {
        /varset Spell1 ${CompHeal}
    } else {
        /varset Spell1 ${wardspell}
    }
    /varset Spell2 ${remedyheal1}
    /varset Spell3 ${patchheal1}
    /varset Spell4 ${groupheal}
    /varset Spell5 ${yaulpspell}
    /varset Spell6 ${Hammerpet}
    /varset Spell7 ${MagicNuke}
	/if ( ${FindItem[=${epicwand}].TimerReady} ) {
	/varset Spell8 ${AERezSpell}
	} else {
	/varset Spell8 ${RezSpell}
	}
    /varset Spell9 Null
   
 
    |- Rotations
    |- Self Buffs
    /call CLR_DefaultSelfBuffRotationConfig CLR_Downtime_MODETLP_Rotation
    |- Group Buffs
    |- Setup Buff Group List
    /call BuffGroup_Init 2
    /call BuffGroup_Set 1 "${SymbolBuff}" "WAR,SHD,PAL"  ${Parse[0,"( ${DoSymbol[SETTINGVAL]} )"]}    
    /call BuffGroup_Set 2 "${AegoBuff}" "ALL" ${Parse[0,"( !${DoDruid[SETTINGVAL]})"]}
 

    |- Heals - because this is Intended for TLP and levels 1-84 all 85+ AAs& Spells Are Not present.
    |- Setup heals

    /call Heal_AddHealPoint ${TLPStartHealPoint[SETTINGVAL]}
    | - Darby & Epic Darby - First heals to use so if we have Incoming issues we try to not aggro.
    /call Heal_AddAA     ${TLPStartHealPoint[SETTINGVAL]} "Divine Arbitration"      ${Parse[0,"( ${Group.Member[${Target.Name}].Index} && ${RG_AAReady[Divine Arbitration]} && ${Spawn[id ${target_id}].PctHPs}<=${LightHealPoint[SETTINGVAL]} )"]}
    /call Heal_AddItem   ${TLPStartHealPoint[SETTINGVAL]} "${Epic}"                 ${Parse[0,"( !${FindItem[=${Epic}].TimerReady} && ${DoEpic[SETTINGVAL]} )"]}
| * - for some reason the heal never completes. 
|    /call Heal_AddItem   ${TLPStartHealPoint[SETTINGVAL]} "${tacvihammer}"          ${Parse[0,"( !${FindItem[=${tacvihammer}].TimerReady} )"]}
    |- Next we use Group AA Then Spell heals if nessicary These are all gated By Checks to ensure they are needed.
    /call Heal_AddAA     ${TLPStartHealPoint[SETTINGVAL]} "Celestial Regeneration"  ${Parse[0,"( ${Group.Member[${Target.Name}].Index} && ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})"]}
  	/call Heal_AddAA     ${TLPStartHealPoint[SETTINGVAL]} "Exquisite Benediction"   ${Parse[0,"( ${WardsPlease} || ${DoAutoWard[SETTINGVAL]} && ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})"]}
    /call Heal_AddSpell  ${TLPStartHealPoint[SETTINGVAL]} "${groupheal}"            ${Parse[0, "( ${Group.Member[${Target.Name}].Index} && ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
   | - A Light heal and a Remedy Heal
    /call Heal_AddSpell	 ${TLPStartHealPoint[SETTINGVAL]} "${patchheal1}"       ${Parse[0,"( ${Spawn[id ${target_id}].PctHPs}<=${LightHealPoint[SETTINGVAL]}  && ( ${target_id}!=${assistid} || !${DoCh[SETTINGVAL]} )  )"]}    
    /call Heal_AddSpell	 ${TLPStartHealPoint[SETTINGVAL]} "${remedyheal1}"      ${Parse[0,"( ${Spawn[id ${target_id}].PctHPs}<=${RemedyHealPoint[SETTINGVAL]} && ( ${target_id}!=${assistid} || !${DoCh[SETTINGVAL]} )  )"]}
    /call Heal_AddSpell	 ${TLPStartHealPoint[SETTINGVAL]} "${remedyheal2}"      ${Parse[0,"( ${Spawn[id ${target_id}].PctHPs}<=${RemedyHealPoint[SETTINGVAL]} && ( ${target_id}!=${assistid} || !${DoCh[SETTINGVAL]} )  )"]}
    /call Heal_AddSpell	 ${TLPStartHealPoint[SETTINGVAL]} "${CompHeal}"         ${Parse[0,"( ${Spawn[id ${assistid}].PctHPs}<=${CompHealPoint[SETTINGVAL]} && ${target_id}==${assistid} && ${DoCh[SETTINGVAL]} )"]}
  
   | - Next is a HotSpell ( Wardspell is Hots at Low level) - it only casts on the Tank.
    /call Heal_AddSpell	 ${TLPStartHealPoint[SETTINGVAL]} "${wardspell}"        ${Parse[0,"( !${Spawn[id ${target_id}].CachedBuff[${wardspell}].ID} && ${target_id}==${assistid})"]}
   | - Optional CH for those Choosing to use it with the /rg DoCh 1 
    
	|- DPS heals
	/call AddToRotation CLR_DPS_MODETLP_Rotation "${yaulpspell}"   Spell  ${Parse[0,"( ${DoMount[SETTINGVAL]}==1 && ${Zone.Indoor} )"]} 
    /call AddToRotation CLR_DPS_MODETLP_Rotation "${MagicNuke}"    Spell  ${Parse[0,"( ${Target.PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNuke[SETTINGVAL]} && ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"]}
	/call AddToRotation CLR_DPS_MODETLP_Rotation "Turn Undead"       AA   ${Parse[0,"( ${Target.Body.Name.Equal[Undead]} )"]}

	| - Burn AA Rotation
	/call AddToRotation CLR_Burn_MODETLP_Rotation 	"Celestial Hammer"      AA  TRUE
	/call AddToRotation CLR_Burn_MODETLP_Rotation 	"Turn Undead"           AA  ${Parse[0,"( ${Target.Body.Name.Equal[Undead]} )"]}
    /call AddToRotation CLR_Burn_MODETLP_Rotation   "${Hammerpet}"    AA  ${Parse[0,"( ${BurnAuto[SETTINGVAL]} || SMALLBURN )"]}
    /call AddToRotation CLR_Burn_MODETLP_Rotation   "Divine Avatar"         AA  ${Parse[0,"( ${DoMelee[SETTINGVAL]} )"]}
    /call AddToRotation CLR_Burn_MODETLP_Rotation   "Divine Retribution"    AA  ${Parse[0,"( TRUE )"]}




/return 


Sub CLR_DefaultSelfBuffRotationConfig(string rotation_name)
    |- Aura checks require a bool mapping. 
| -- old using equal
| -- /if (${RG_CanUseAA[Spirit Mastery]}) /call AddToRotation "${rotation_name}" "${aurabuff1}" "Spell" ${Parse[0,"( !${Bool[${Me.Aura[1].Name.Equal[${aurabuff1_name}]}]} && !${Bool[${Me.Aura[2].Name.Equal[${aurabuff1_name}]}]} )"]}
| -- new line uses find, like in the enc util
    /if (${RG_CanUseAA[Spirit Mastery]}) /call AddToRotation "${rotation_name}" "${aurabuff1}" "Spell" ${Parse[0,"( !${Bool[${Me.Aura[1].Name.Find[${aurabuff1_name}]}]} && !${Bool[${Me.Aura[2].Name.Find[${aurabuff1_name}]}]} )"]}    /call AddToRotation "${rotation_name}" "${aurabuff2}" "Spell" ${Parse[0,"( !${Bool[${Me.Aura[1].Name.Equal[${aurabuff2}]}]} && !${Bool[${Me.Aura[2].Name.Equal[${aurabuff2}]}]} )"]}
    /call AddToRotation "${rotation_name}" "${MountItem[SETTINGVAL]}" Item  ${Parse[0,"( ( (${DoMount[SETTINGVAL]}==1 && !${DoMelee[SETTINGVAL]}) || (${DoMount[SETTINGVAL]}==2 && !${Me.Buff[Mount Blessing].ID})) && !${Me.Mount.ID} && ${Zone.Outdoor} && (${FindItem[${MountItem[SETTINGVAL]}].ID} || ${Mount[${MountItem[SETTINGVAL]}].Index}) )"]}
    /call AddToRotation "${rotation_name}" "/dismount" "Command" ${Parse[0,"( ${DoMount[SETTINGVAL]}==2 && ${Me.Mount.ID} && ${Me.Buff[Mount Blessing].ID} )"]}
    /if ( (${Spell[${SelfBuffhp}].Level}<=${Spell[${Me.AltAbility[Saint's Unity].Spell.Trigger[1].BaseName}].Level}) && ${RG_CanUseAA[Saint's Unity]} ) {
		/call AddToRotation "${rotation_name}" "Saint's Unity"    AA    ${Parse[0,"( !${Me.Buff[${Me.AltAbility[Saint's Unity].Spell.Trigger[1].BaseName}].ID} && ${Spell[${Me.AltAbility[Saint's Unity].Spell.Trigger[1].BaseName}].Stacks} )"]}
    } else { 
        /call AddToRotation "${rotation_name}" "${SelfBuffhp}"    Spell ${Parse[0,"( !${DoDruid[SETTINGVAL]} && ${Spell[${SelfBuffhp}].Stacks} && !${Me.Buff[${SelfBuffhp}].ID} )"]}
    }

	/call AddToRotation "${rotation_name}" "${GroupHealProcBuff}" Spell ${Parse[0,"( ${Spell[${GroupHealProcBuff}].Stacks} && !${Me.Buff[${GroupHealProcBuff}].ID}  )"]}

/return

Sub CLR_DefaultHealRotationConfig
    |- Setup heals
    /call Heal_AddHealPoint 	${MainHealPoint[SETTINGVAL]}
	/call Heal_AddHealPoint 	${BigHealPoint[SETTINGVAL]}
	
  |- Main Heal Point Order - This is Normal heal Rotation.
    /call Heal_AddSpell 	 ${MainHealPoint[SETTINGVAL]} "${groupfastheal}"	    ${Parse[0, "( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
    /call Heal_AddSpell 	 ${MainHealPoint[SETTINGVAL]} "${groupheal}"		    ${Parse[0, "( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
    /call Heal_AddSpell 	 ${MainHealPoint[SETTINGVAL]} "${GroupHot}"		    ${Parse[0, "( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
    /call Heal_AddAA         ${MainHealPoint[SETTINGVAL]} "Celestial Regeneration"  ${Parse[0,"( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})""]}
  	/call Heal_AddAA         ${MainHealPoint[SETTINGVAL]} "Beacon of Life"          ${Parse[0,"( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})""]}
	/call Heal_AddAA         ${MainHealPoint[SETTINGVAL]} "Exquisite Benediction"   ${Parse[0,"( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})""]}
    /call Heal_AddAA         ${MainHealPoint[SETTINGVAL]} "Focused Celestial Regeneration"      ${Parse[0,"( ${RG_AAReady[Focused Celestial Regeneration]} && ${Target.Distance}<100 )"]}
    /if (${DoHots[SETTINGVAL]})  /call Heal_AddSpell	 ${MainHealPoint[SETTINGVAL]} "${SingleHot}" ${Parse[0,"( ${DoHots[SETTINGVAL]} && !${Spawn[id ${target_id}].CachedBuff[${SingleHot}].ID} )"]}
    /if (${DoNuke[SETTINGVAL]})  /call Heal_AddSpell	    ${MainHealPoint[SETTINGVAL]} "${healnuke1}" ${Parse[0,"( ${Spawn[id ${autotargetid}].PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNuke[SETTINGVAL]} )"]}
|	/call Heal_AddSpell 	 ${MainHealPoint[SETTINGVAL]} "${healnuke2}" ${Parse[0,"( ${Spawn[id ${autotargetid}].PctHPs}<=${NukePct[SETTINGVAL]} && ${DoNuke[SETTINGVAL]} )"]}
    /call Heal_AddSpell		 ${MainHealPoint[SETTINGVAL]} "${remedyheal1}" TRUE
	/call Heal_AddSpell		 ${MainHealPoint[SETTINGVAL]} "${remedyheal2}" TRUE

| - Big Heal Point - This is the Ohshit i took a big hit rotation - Differences here are DA, EPIC, Burst of Life, Dissident Blessing. Then Remedys. Potentionally if your Tank was really weak u could
| - CHange /rg bighealpoint 95 and Put main heal to 1 and it would Use a single healpoint of this healpoint.
    /call Heal_AddSpell 	 ${BigHealPoint[SETTINGVAL]} "${groupfastheal}"	     ${Parse[0, "(${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
    /call Heal_AddSpell 	 ${BigHealPoint[SETTINGVAL]} "${groupheal}"		     ${Parse[0, "(${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
    /call Heal_AddSpell 	 ${BigHealPoint[SETTINGVAL]} "${GroupHot}"		    ${Parse[0, "( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})" ]}
    /call Heal_AddAA         ${BigHealPoint[SETTINGVAL]} "Celestial Regeneration"  ${Parse[0,"( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})"]}
  	/call Heal_AddAA         ${BigHealPoint[SETTINGVAL]} "Beacon of Life"          ${Parse[0,"( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})"]}
	/call Heal_AddAA         ${BigHealPoint[SETTINGVAL]} "Exquisite Benediction"   ${Parse[0,"( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]})"]}
    /call Heal_AddItem       ${BigHealPoint[SETTINGVAL]} "${Epic}"                  ${Parse[0,"( !${FindItem[=${Epic}].TimerReady} && ${DoEpic[SETTINGVAL]} )"]}
    /call Heal_AddAA         ${BigHealPoint[SETTINGVAL]} "Divine Arbitration"      ${Parse[0,"( ${RG_AAReady[Divine Arbitration]} )"]}
    /call Heal_AddAA         ${BigHealPoint[SETTINGVAL]} "Burst Of Life"        ${Parse[0,"( ${RG_AAReady[Burst of Life]} )"]}
	/if (${DoClutchHeal[SETTINGVAL]}) /call Heal_AddSpell      ${BigHealPoint[SETTINGVAL]} "${ClutchHeal}"           ${Parse[0,"( ${Target.PctHPs}<=${ClutchHealPoint[SETTINGVAL]} )"]}
    /call Heal_AddSpell		 ${BigHealPoint[SETTINGVAL]} "${patchheal1}"        TRUE
    /call Heal_AddSpell		 ${BigHealPoint[SETTINGVAL]} "${healnuke1}"     ${Parse[0,"( ${Spawn[id ${autotargetid}].PctHPs}<=${AutoAssistAt[SETTINGVAL]} && ${DoNuke[SETTINGVAL]} && ${XAssist.XTFullHaterCount})"]}
	/call Heal_AddSpell 	 ${BigHealPoint[SETTINGVAL]} "${healnuke2}"     ${Parse[0,"( ${Spawn[id ${autotargetid}].PctHPs}<=${AutoAssistAt[SETTINGVAL]} && ${DoNuke[SETTINGVAL]} && ${XAssist.XTFullHaterCount})"]}
    /call Heal_AddSpell		 ${BigHealPoint[SETTINGVAL]} "${remedyheal1}"   TRUE
	/call Heal_AddSpell		 ${BigHealPoint[SETTINGVAL]} "${remedyheal2}"   TRUE
/return

Sub CLR_DefaultBuffGroupConfig
    |- Setup Buff Group List
    /call BuffGroup_Init 6
    /call BuffGroup_Set 1 "${ReverseDS}" "WAR,SHD,PAL" ${Parse[0,"( ${DoReverseDS[SETTINGVAL]} )"]} "single"
    /call BuffGroup_Set 2 "${TankBuff}" "WAR,SHD,PAL"
|   /call BuffGroup_Set 3 "${SymbolBuff}" "ALL" ${Parse[0,"(  )"]}
    /call BuffGroup_Set 3 "${AegoBuff}" "ALL" ${Parse[0,"( !${DoDruid[SETTINGVAL]})"]}
    /call BuffGroup_Set 4 "${GroupVieBuff}"
    /call BuffGroup_Set 5 "${DivineBuff}"  "WAR,SHD,PAL,CLR" ${Parse[0,"( ${DivineBuffOn[SETTINGVAL]} && ${FindItemCount[${Spell[${DivineBuff}].ReagentID[1]}]} >= 2)"]}
    /call BuffGroup_Set 6 "${SpellBlessing}" "RGCASTERS" ${Parse[0,"( ${Me.Level} < 91 )"]}
/return

Sub CLR_Combat_Routine
    /if ( DODPS ) {
        /if ( BURNCHECK ) {
            /if (${RG_AAReady[Divine Guardian]}) /call AANow ${Me.AltAbility[Divine Guardian].ID} ${assistid} 
            /call Ordered_Rotation_Follow CLR_Burn_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
        }
        /call Ordered_Rotation_Follow CLR_DPS_${ClassMode[SETTINGVAL]}_Rotation ${autotargetid} TRUE
    }
/return FALSE

Sub CLR_Downtime_Routine
    |- Call Self buffs
|   - Ward Spell takes a full 2 mins to refresh the Gem and Is Not worthwhile overall for the gem Slot. 
|    /if (!${Spawn[id ${assistid}].CachedBuff[${wardspell}].ID} && && ${PCSpellReady[${promheal}]} && ${Spawn[id ${assistid}].Type.NotEqual[Corpse]} && ${Spawn[id ${assistid}].Distance}<${AssistRange[SETTINGVAL]}) { 
|    /call SpellNow "${wardspell}" ${assistid}
|    }
    /call FollowRotation  CLR_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.ID}
        /if (${Me.Pet.ID}) {
        /call FollowRotation  CLR_Downtime_${ClassMode[SETTINGVAL]}_Rotation ${Me.Pet.ID}
    } 
/return FALSE

Sub CLR_Heal_Routine
	|-  Veturika Call
    /if (${RG_AAReady[Veturika's Perseverance]} && ${Me.PctMana}<=${VetManaPCT[SETTINGVAL]}) /call AANow ${AltAbility[Veturika's Perseverance].ID} ${Me.ID}
    
    |-  Quiet Prayer Code
	| - Declare is used to Define if a valid QP target exists before calling the AA 
    /declare qptarget int local ${WorstHurtMana[${QPManaPCT[SETTINGVAL]}]}
    /if (${RG_AAReady[Quiet Prayer]} && ${DoQp[SETTINGVAL]} && ${qptarget}) /call AANow ${AltAbility[Quiet Prayer].ID} ${qptarget}
    
    |- If we're a member of a group, heal our group first.
   
|   Cast the spell if conditions are met and timer is not running
    /if ( ${DoProm[SETTINGVAL]} && ${PCSpellReady[${promheal}]} && ${Spawn[id ${assistid}].Type.NotEqual[Corpse]} && ${Spawn[id ${assistid}].Distance}<${AssistRange[SETTINGVAL]} && !${PromHealTimer}) {
        /call SpellNow "${promheal}" ${assistid}
        /varset PromHealTimer ${TimerDuration}
    }
    
    /call HealNow ${WorstHurtGroup[${HealPoint_MaxPoint}]}
    
    /if (${AssistOutside[SETTINGVAL]}) {
        /call HealNow ${WorstHurtXT[${HealPoint_MaxPoint}]}
        |- In case we pissed someone off
        /if (${Me.PctHPs} <= ${HealPoint_MaxPoint} ) {
            /call HealNow ${Me.ID}
        }
    }
    /if (${IsCuring} && !${DoCure[SETTINGVAL]}) /call TOV_CheckDNetForIce
    /if (${IsCuring} && ${DoCure[SETTINGVAL]}) /call CureNow
/return ${Macro.Return}
|---------------------------------------------------------------------------
|- SUB: DoRez
|---------------------------------------------------------------------------- 
Sub CLR_DoRez(int corpse_id)
    /if ( ${DoBattleRez[SETTINGVAL]} || ${DoBuffCheck[]} ) {
        /call SetTarget ${corpse_id}
        /if (${Target.Distance} > 25) /corpse

    |- Non-Combat Rez Handling
   
        /if ( ${RG_AAReady[Blessing of Resurrection]} ) {
            /call AANow ${Me.AltAbility[Blessing of Resurrection].ID} ${corpse_id}
            /return ${Macro.Return}
	    } else { 
            /if ( ${Me.ItemReady[${epicwand}]} ) {
                /call ItemNow ${epicwand} ${corpse_id}
            /return ${Macro.Return}	
        } else {
            /if (${PCSpellReady[${RezSpell}]}&& !${XAssist.XTFullHaterCount} && !${RG_CanUseAA[Blessing of Resurrection]}) {
                /call SpellNow "${RezSpell}" ${corpse_id}
            /return ${Macro.Return}
            }
        }
    }
}      

/return FALSE

|----------------------------------------------------------------------------
|- SUB: CLR_SpecialChats Special Chat events specific to Cleric and not buff begs.
|----------------------------------------------------------------------------
Sub CLR_SpecialChats(string chat_text, int sender_id)
    /if (${chat_text.Find[thawme]}) /call AddToThawmeQueue ${sender_id}
/return

|- SUB: SingleCure
|----------------------------------------------------------------------------
|-Thawme wrapper because it's easier then refactoring everything around again
#bind CureIce /cureice
Sub Bind_CureIce(int cureid)
    /if (${RG_AAReady[Purify Soul]} && !${Me.Casting.ID}) {
		/call AANow ${Me.AltAbility[Purify Soul].ID} ${cureid}
    } else {
        /if (${PCSpellReady[${Icespellcure}]}) {
            /call SpellNow "${Icespellcure}" ${cureid}
        } else {
            /if (${RG_AAReady[Group Purify Soul]}) /call AANow ${Me.AltAbility[Group Purify Soul].ID} ${cureid}
        }
    }
/return
