|- File: RGsubs.inc
|- Version 2.1
|- Original File: auto_subs.inc
|- Auto-Subs Shared routines across Auto series macros by Noobhaxor
|- Version 6.2
|- Updated: 4/25/2019
|- Modified version of the above file to maintain compatability with the automac's / kissassist
|- Modified to fit the RG mac's and mod's better

Sub PrintGroupMessage(string message)
    /docommand /dgt group_${EverQuest.Server}_${Group.Leader} ${message}
/return

Sub HandleAcverbose(string message)
    /if (${acverbose[SETTINGVAL]}==1) {
        /call PrintGroupMessage "${message}"
    } else /if (${acverbose[SETTINGVAL]}==2) {
        /echo ${message}
    }
/return

|----------------------------------------------------------------------------
|- SUB: RGInit
|- Set macro version variables and ini file name
|----------------------------------------------------------------------------
Sub RGInit(string strClass, string strVersion)
    |- Make sure all our plugins are loaded first thing if we need them.
    /call CheckPlugin MQ2Collections
    /call CheckPlugin MQ2Rez
    /call CheckPlugin MQ2AdvPath
    /call CheckPlugin MQ2MoveUtils
    /call CheckPlugin MQ2Nav
    /call CheckPlugin MQ2DanNet
    /call CheckPlugin MQ2Xassist
    /call CheckPlugin MQ2SpawnMaster
|    /if ( ${DoTwist[SETTINGVAL]} ) /call CheckPlugin MQ2Twist


    |- Plugins that conflict
|    /if ( !${DoTwist[SETTINGVAL]} ) /call UncheckPlugin MQ2Twist
    /call UnCheckPlugin MQ2Melee
    
    /declare MacroName          string outer RG${strClass}
    /declare MacroPath          string outer rgmercs\${MacroName}
    /declare RGVersion         string outer ${strVersion}
    /declare IniFileName        string outer "rgmercs\PCinis\${MacroName}_${EverQuest.Server.Replace[" ",""]}_${Me.CleanName}.ini"
    
    |- List Collection with the core RG settings
    /declare RGList_Settings list outer
    |- Provides the translation from user typed settings to the variables
    /declare Map_TransSetting map outer
    
    |- List Collection with the debug RG settings
    /declare RGList_Debug    list outer

    |- List Collection for Pull settings.
    /declare RGList_Pull list outer

    |- Map Collection for Observers
    /declare Map_Observers map outer

/return

|----------------------------------------------------------------------------
|- SUB: OuterVarInit
|- Initialize all outer variable declarations. These are RG core variables used
|- across the macro.
|----------------------------------------------------------------------------
Sub OuterVarInit

    |- Variables used across RG
    /call RGLoadSetting Settings ReturnToCamp 0 General "Set 0=off; 1=Return to camp when outside AutoCampRadius; 2=Return to camp every time." 1 "TurnChaseOff"
    /call RGLoadSetting Settings DebugLog 0 Debug "Set 0/1/2 to enable debug logging. 1 outputs debug msgs to the log. 2 outputs calltrace msgs to the console." 1
    /call RGLoadSetting Settings ErrorMsg 1 General "Set 0/1 to enable error message printing (messages that help tell you why your character may not perform certain things)." 1
    /call RGLoadSetting Settings MyInvis     CharName    Hotkeys "Character for group invis for invis hotkey" 1
    /call RGLoadSetting Settings MyUndInvis  CharName    Hotkeys "Character for group undead invis for invis hotkey" 1
    /call RGLoadSetting Settings HotkeyStartPg     1           Hotkeys "Starting page for rgmkeys to set hotkeys. Default: 1" 1
    /call RGLoadSetting Settings HotkeyEndPg       10          Hotkeys "Ending page for rgmkeys to set hotkeys. Default: 10" 1
    /call RGLoadSetting Settings CPUThrottle 0 General "Set to 1 or higher to reduce CPU usage at the cost of macro responsiveness (100ms*CPUThrottle). Default: 0" 1
    /call RGLoadSetting Settings RGLevel ${Me.Level} Debug " Used to change Base Spell level of toon to change loadout for testing" 1
    
    |-- Comment the next 3 lines out for debugging spell bars of different levels.
    /if (${RGLevel[SETTINGVAL]} != ${Me.Level}) {
        /call RGChangeSetting Settings RGLevel ${Me.Level}
    }

    /declare MainLoopOn         int outer 1

    |- Used in profiling
    /declare SubstartTime       int outer 
    /declare MovingAvg          float outer
    /declare MovingStdDev       float outer
    /declare DataPoints         list outer

    |- Used to gate pulling to the zone in which its started in as well as autocamphold.
    /declare ZoneID             int outer 0
    
    /declare autotargetid       int outer 0   
    /declare AutoCampX          int outer 0
    /declare AutoCampY          int outer 0
    /declare AutoCampZ          int outer 0

    |- RGMerc Mode Capabilities -- These are used in mode setup subs
    |- and are used as gates in class defined routines.
    /declare IsTanking          bool outer FALSE
    /declare IsHealing          bool outer FALSE
    /declare IsMezzing          bool outer FALSE
    /declare IsCharming         bool outer FALSE
    /declare IsCuring           bool outer FALSE

     |- RG macro's common variables
    /declare assistname         string outer NULL
    /declare assistid           string outer
    /declare BardStartTwist     int    outer       0
    /declare BardWasTwisting    string outer       null
    /declare WasTwisting        bool   outer       FALSE
            /declare Twisting               int         outer       0
    /declare MainAssistType     string outer
    /declare burnnow            int outer 0
    /declare BackOffFlag        int outer 0
    /declare BeforeCombat       string outer NULL
    /declare ShitOnCursor       string outer NULL
    /declare CursorTimer        timer outer 0
    /declare EventSetupFlag     int outer 0
    /declare ExtendedBuffList   string outer
    /if (!${Defined[g_ExtendedBuffList]}) {
        /declare g_ExtendedBuffList string global
    }
    /declare KillTargetID       int outer 0
    /declare DPSRecastTimer     timer outer 0
    /declare CastResult         string outer CAST_NULL
    /declare CanAlliance        bool outer FALSE
    /declare RezTimer 			timer outer 0
    /declare InMedState         bool outer FALSE
    /declare DraggingCorpse     int outer 0
    /declare SitTimer           timer outer 0
    /declare IsMemorizing       bool outer FALSE
    /declare MemTimer           timer outer 0
    /declare WardsPlease        int outer 0
    /declare castReturn         string      outer       CAST_CANCELLED
    /declare BuffTimer          timer outer 0
   | - Doing this Instead of A Define because of a Mq2 Collections Bug. That messes up Parse on Commas. ie the Select.
    /noparse /declare MEZIMMUNEBODY string outer ( ${Target.Body.Name.Equal[Giant]} || ${Target.Named} || ( ${Target.Name.Find[giant]} && ${Select[${Zone.ID},824,827,829]} ) )
    
    |- Used by CheckEpic & all class macros
    |- Epic -> Name of optimal Epic on-hand
  |  /declare Epic               string outer NULL
  |  /declare DoEpic            bool outer FALSE

    | Pet Vars
    /declare PetAttackOrderTimer    timer   outer
    /declare PetAttackOrderTime     string  outer   2s

    |- Used by IsFriendly sub to cache spawn ids
    /declare IsFriendlyIDList       string      outer
    /declare IsHostileIDList        string      outer
    /declare IsMaybeHostileIDList   string      outer
    |
    | When did we last move, and where were we?
    |
    /declare LastSitStand			bool		outer		${Me.Sitting}
    /declare LastMoveHeading		float		outer		0.0
    /declare LastMoveX				float		outer		0.0
    /declare LastMoveY				float		outer		0.0
    /declare LastMoveZ				float		outer		0.0
    /declare LastMoveTime			int			outer		${EverQuest.Running}
    /declare TimeSinceMove			int			outer		60

    /echo -----${MacroName} LOADING------
    |-Check for loaded plugins
    /squelch /rez accept on
    /squelch /rez pct 90

    |- Load DanNet to communicate with other box chars in the same group. 
    /if (${Plugin[MQ2DanNet].Name.Length}) {
        /if (${DanNet.CommandEcho}) /squelch /dnet commandecho off
    }

    /stick set breakontarget on

    |- Initialize the ChatBeg system -- ChatBegs added in Class .inc's
    /call ChatBegList_New ${Me.Class.ShortName}Begs
/return
|----------------------------------------------------------------------------
|- SUB RG Common Config Options - Config options that will be the same across all mac's
|----------------------------------------------------------------------------
Sub LoadCommonConfig
    /call RGLoadSetting Settings DoAutoTarget 1 Combat "Set 0/1 to automatically find enemy target based on RGMerc's built in algorithm. (Turning off enables manaual targeting mode.)" 1
    /call RGLoadSetting Settings SafeTargeting 1 General "Set 0/1. Default: 1. When enabled, makes sure you do not pull or engage another players mob. Treats dannet members, group members, and raid members as safe." 1
    /call RGLoadSetting Settings StayOnTarget 0 Combat "Set 0/1 to stick to your target. Default: 1; Tank Mode Defaults: 0. 0 allows intelligent target swapping based on aggro/named/ etc." 1
    /call RGLoadSetting Settings DoAutoEngage 1 Combat "Set 0/1 to automatically engage target when they enter assist range. (Turning off will break things in unknown ways)" 1
    /if (${Select[${Me.Class.ShortName},RGMELEE]}) {
        /call RGLoadSetting Settings DoMelee 1 Combat "Set 0/1 to enable melee." 1
    } else {
        /call RGLoadSetting Settings DoMelee 0 Combat "Set 0/1 to enable melee."
    }
    /if (${Select[${Me.Class.ShortName},RGTANK]}) {
        /call RGLoadSetting Settings StickHow "front 15 moveback" Combat "Stick command to use in combat." 1
    } else {  /if (${Select[${Me.Class.ShortName},RGMELEE]}) {
        /call RGLoadSetting Settings StickHow "snaproll behind 98%% moveback uw" Combat "Stick command to use in combat." 1
    }
    }
    /call RGLoadSetting Settings FollowMarkTarget 0 Combat "Set 0/1 to automatically target enemies marked by the group main assist instead of following group main assist's target." 1
    /call RGLoadSetting Settings FollowToonName NULL General "Sets the name of the spawn to follow and turns on chase mode when set." 1
    /call RGLoadSetting Settings ChaseDistance 50 General "Sets the distance at which to chase." 0 "TurnCampOff" 1
    /if (${Select[${Me.Class.ShortName},CLR,SHM]}) {
        /call RGLoadSetting Settings acverbose 2 General "Set 0/1/2 to inform Dannet/Self when a spell or ability is used."
    } else {
        /call RGLoadSetting Settings acverbose 0 General "Set 0/1/2 to inform Dannet/Self when a spell or ability is used." 1
    }
    /call RGLoadSetting Settings AssistRange 100 General "Maximum distance before you engage the target (including tanks targeting roamers/incoming pulls)."
    /call RGLoadSetting Settings MAScanZRange 0 General "Maximum Z distance an MA will search to find roamers/pullers. Default: 0 [off]" 1
    /call RGLoadSetting Settings AutoAssistAt 98 General "Sets Mob HP% to start attacking at"
    /call RGLoadSetting Settings AutoCampRadius 30 General "Camp radius in distance -- will return to camp when out of this distance. Also will hold pulls when group outside camp."
    /call RGLoadSetting Settings BurnAlways 0 General "Set 0/1 to always use the burn routine for a class if available"
    /call RGLoadSetting Settings BurnMobCount 3 General "Sets the number of targets to Start auto burn" 1
    /call RGLoadSetting Settings BurnNamed 1 General "Set 0/1 the autoburning of named mobs." 1
    /call RGLoadSetting Settings BurnAuto 1 General "Set 0/1 for auto control of burns" 1
    /call RGLoadSetting Settings BurnSize 0 General "Variable for burnsize when manually burning" 1
    /call RGLoadSetting Settings DoMed 1 General "Set 0/1 to meditate when low on resources. Set 2 = Med During Combat."
    /call RGLoadSetting Settings HPMedPct 20 General "%Health to start meditating."
    /call RGLoadSetting Settings HPMedPctStop 80 General "%Health to stop meditating."
    /call RGLoadSetting Settings EndMedPct 80 General "%Endurance to start meditating."
    /call RGLoadSetting Settings EndMedPctStop 100 General "%Endurance to stop meditating."
    /call RGLoadSetting Settings ManaMedPct 20 General "%Mana to start meditating." 
    /call RGLoadSetting Settings ManaMedPctStop 80 General "%Mana to end meditating." 
    /call RGLoadSetting Settings ModRodManaPct 70 General "%Mana to click the mod rod." 1
    /call RGLoadSetting Settings InstantRelease 0 General "Set 0/1 instantly release after death." 1

    /call RGLoadSetting Settings ShrinkName NULL General "The name of your Shrink Item to use, must set DoShrink to 1" 1
    /call RGLoadSetting Settings DoShrink 0 Options "Set 1 to use your shrink item to auto shrink. Default: 0."  1
    /call RGLoadSetting Settings DoFellow 0 General "Set 0/1 to click fellowship insignia after death." 1
    /if (${Select[${Me.Class.ShortName},RGMODROD]}) {
        /call RGLoadSetting Settings DoModRod 1 General "Set 0/1 to use Mod Rods in inventory."
    } else {
        /call RGLoadSetting Settings DoModRod 0 General "Set 0/1 to use Mod Rods in inventory." 1
    }
     /if (${Select[${Me.Class.ShortName},RGPETCLASS]}) {
         /call RGLoadSetting Settings PetEngagePct 95 Pet " Sets The % Life of Mob to sick pet at."
     }
    /call RGLoadSetting Settings DoZoneLogic 0 General "Set 0/1 to react to zone specific events where implemented. Default: 0." 1
    /call RGLoadSetting Settings ClassMode 0 General "IF YOU ARE SEEING THIS YOUR MACRO AUTHOR DID NOT SETUP THEIR CLASSMODE HELP"
    /call RGLoadSetting Settings DoBuffs 1 Options "Set 0/1 to Cast Buffs." 1
	/call RGLoadSetting Settings AssistOutside 0 Options "	Turn on Out of group support." 
    /call RGLoadSetting Settings OaList "NULL"  Options "Comma delimited priority list of main assist PC names for use when AssistOutside=1" 1
    /call RGLoadSetting Settings BreakInvis 1 Options "Set 0/1 to break invis to heal injured group or out of group members when out of combat only. Healers will always break invis in combat."
    /call RGLoadSetting Settings AllianceCount      3 Combat "Set # of same class to use alliance. Default: 3" 1
    /call RGLoadSetting Settings DoAlliance        0 Combat "Set 0/1 to use Alliance Spell. Default: 0." 1
    /call RGLoadSetting Settings MaintainCampfire   0 General "Set 0/1/2/.../36 => 0: Off; 1: Regular Fellowship; 2: Empowered Fellowship; 36: Scaled Wolf" 1
    /call RGLoadSetting Settings RetryRezDelay      6 Healing "Time in seconds to wait between casting rez spells." 1
    /call RGLoadSetting Settings DoChestClick    0 Item "Set 0/1 to turn on chest clickies. Default: 0."
    /call RGLoadSetting Settings DoMount 0 Mount "Set 0/1/2 1 to use mounts 2 to use mount for buff only."
    /call RGLoadSetting Settings MountItem "NULL" Mount "Item name of mount to use."
    /if (${Select[${Me.Class.ShortName},RGCASTERS]}) {
        /call RGLoadSetting Settings BringYourOwnSpells 0 General "Set 0/1 to select your own spell bar. Spells will only be cast if already part of a rotation (/printrotation)." 1
    }
    /call RGLoadSetting Settings AllowMezBreak 0 Combat "Toggle 0/1 the ability to break mez without MA breaking it first." 1
    /call RGLoadSetting Settings DoMercenary 0 General "Set 0/1 to tell RGMercs you have mercenaries in your group." 
    /call RGLoadSetting Settings DoEpic 1 Item "Toggle use of Class Epic Items effects 0/1"
    /call RGLoadSetting Settings MiscRememDelay 10 General "# of seconds to delay re-memorizing misc spells. Default: 10s." 1
    /call RGLoadSetting Settings DoPetHeals 0 Combat "Toggle use of Pet Healing 0/1 Default off"
    /call RGLoadSetting Settings DoMpgFearTrial 0 ZoneLogic "Turning this on will make the character fear for MPG Group Trials." 1
/return

|----------------------------------------------------------------------------
|- SUB ModeSetup - Common ModeSetup used for all classes. Must be caled after
|- all standard RG setup and the class specific setup. This sets the alliance
|- abilities for the characters that use them, set all abilities for all
|- characters, and memorizes spell bars for the classes with spells.
|----------------------------------------------------------------------------
Sub ModeSetup
    |- Setup Epic Weapon variables before they're checked in ModeConfig
    | /call CheckEpic
    |- Warriors are the only class without an alliance ability.
    /if (!${Select[${Me.Class.ShortName},WAR]}) { 
        /call Bind_CheckForAlliance
    }
    |- Must be defined in the class INIs
    |- TODO: Add !Defined error checks.
    /call ${Me.Class.ShortName}_SetupSkills
    /if (${SubDefined[${Me.Class.ShortName}_ModeConfig${ClassMode[SETTINGVAL]}]}) {
        /call ${Me.Class.ShortName}_ModeConfig${ClassMode[SETTINGVAL]}
    } else {
        /popup ERROR! Invalid ClassMode Detected -- Resetting and restarting.
        /echo \arERROR:\ax Invalid ClassMode Detected -- Resetting and restarting.
        /call RGChangeSetting Settings ClassMode 0
        /rgstart
    }

    /if (${Select[${Me.Class.ShortName},BRD,BST,CLR,DRU,ENC,MAG,NEC,PAL,RNG,SHD,SHM,WIZ]}) {
        /if (!${BringYourOwnSpells[SETTINGVAL]}) {
            /varset miscspellremem ${Spell${Me.NumGems}}
            /if (${Me.Standing}) /sit
            /delay 10 ${Me.Sitting}
            /echo \aw Loading Spell Bar
            
            /declare spell_cnt int local
            /for spell_cnt 1 to ${Me.NumGems}
                /call LoadSpellGem "${Spell${spell_cnt}}" ${spell_cnt}
            /next spell_cnt
        }
    }
    /if (${IsHealing}) /call Heal_SetMaxPoint
    /if (${SubDefined[${Me.Class.ShortName}_CheckOptions]}) /call ${Me.Class.ShortName}_CheckOptions
    |-- Needs to be configured uniqely per class, relied on the class inits.
    /if (${SubDefined[${Me.Class.ShortName}_PullSetup]}) {
        /call ${Me.Class.ShortName}_PullSetup
    } else {
        /echo NOTICE: Could note find PullSetup for ${Me.Class.ShortName}
        |- No gurantee PullSetup correctly inits everything right now until pull is refactored
        /if (!${Defined[Pull_State]}) /call Pull_SetAbility "NULL" Item
    }

    |- Maybe move this into the SHMInit and CLRInit
    /if (${Select[${Me.Class.ShortName},CLR,SHM]}) /call Thawmequeue_Setup
    |- Must be called after SetupSkills and ModeConfig because InitMez requires knowledge of learned MezSpells, AAs, and Mode Capability.
    /if (${IsMezzing}) {
        /call InitMez
        /call AutoConfMezLevels
    }
/return

|----------------------------------------------------------------------------  
|- SUB: SetControlToon
|----------------------------------------------------------------------------
Sub SetControlToon()
    
    /if ( ${AssistOutside[SETTINGVAL]} ) {
        /if (${OaList[SETTINGVAL].NotEqual[NULL]}) {
            DEBUG Using OaList
            |- Load our |-delimited setting entry into a list so we have
            |- quick ooping w/o lots of Arg parsing.
            /declare list_outsidema list local
            /invoke ${list_outsidema.Delimiter[|]}
            /invoke ${list_outsidema.Append[${OaList[SETTINGVAL]}]}
            /declare li_outsidema listiterator local
            /vardata li_outsidema list_outsidema.First.Clone

            /declare spawn_tmp spawn local
            /if (${list_outsidema.Count}) {
                /while (!${li_outsidema.IsEnd}) {   
                    /if ( ${SpawnCount[pc ${li_outsidema.Value}]}) {
                        /squelch /vardata spawn_tmp Spawn[pc ${li_outsidema.Value}]

                        /if (!${spawn_tmp.Dead} && ${spawn_tmp.Distance} < ${AssistRange[SETTINGVAL]}) {
                            DEBUG OutsideAssist Setting new assist to ${spawn_tmp.CleanName} [${spawn_tmp.ID}]
                            /squelch /xtarget assist ${spawn_tmp.ID}
                            /varset assistname ${spawn_tmp.CleanName}
                            /varset MainAssistType  ${spawn_tmp.Type}
                            /varset assistid ${spawn_tmp.ID}
                            /return TRUE
                        }
                    }
                    /invoke ${li_outsidema.Advance}
                }
            }
        } else {
            |- If we don't use the list we start w/ our preferred assist targeted as set
            |- our assist information
            /if (${assistname.Equal[NULL]}) {
                DEBUG Setting Outside Of Group Conrol Toon: ${Target.Name} [${Target.ID}]
                /squelch /xtarget assist ${Target.ID}
                |- We haven't set any preferred primary and backup targets so just focus on our target.
                /varset assistname      ${Target.Name}
                /varset MainAssistType  ${Target.Type}
                /varset assistid        ${Target.ID}
            }       
        }
    } else {
        |- We only want to set these on startup.
        /if (${assistname.Equal[NULL]}) {
            /if (${Group.MainAssist.ID}) {
                /varset assistname ${Group.MainAssist}
                /varset MainAssistType  ${Group.MainAssist.Type}
                /varset assistid ${Group.MainAssist.ID}
            } else {
                |- No MainAssist ID so fall through to an old school routine
                /if (${Target.ID}) {
                    /varset assistname      ${Target.Name}
                    /varset MainAssistType  ${Target.Type}
                    /varset assistid        ${Target.ID}      
                } else {
                    /varset assistname      ${Me.Name}
                    /varset MainAssistType  ${Me.Type}
                    /varset assistid        ${Me.ID}                
                }
            }
            /if (${Group.MainAssist.ID} != ${Target.ID}) /popup Assisting ${assistname} NOTICE: Group MainAssist != Your Target. Is this on purpose?
        }
    }
    
    /if (${Spawn[pc =${assistname}].ID} && ${Spawn[pc =${assistname}].ID}!=${assistid}) {
        /echo \aw MA ID Mismatch - \ag Updating
        /varset assistid ${Spawn[pc =${assistname}].ID}
    }
/return TRUE

| ---------------------------------------------------------------------------
| SUB: LastMove
| 
| Time since character last moved accessible in TimeSinceMove in tenths of a sec
| ---------------------------------------------------------------------------
Sub LastMove(string FromWhere)
    | Debug call stack removed.

    /if (${Math.Abs[${Math.Calc[${Me.X}-${LastMoveX}]}]}>1 || ${Math.Abs[${Math.Calc[${Me.Y}-${LastMoveY}]}]}>1 || ${Math.Abs[${Math.Calc[${Me.Z}-${LastMoveZ}]}]}>1 || ${Math.Abs[${Math.Calc[${Me.Heading.Degrees}-${LastMoveHeading}]}]}>1 || ${Me.Combat} || ${Me.CombatState.Equal[COMBAT]} || ${Me.Sitting}!=${LastSitStand}) {
        /vardata LastMoveTime   EverQuest.Running
        /vardata LastMoveX 		Me.X
        /vardata LastMoveY 		Me.Y
        /vardata LastMoveZ 		Me.Z
        /vardata LastMoveHeading Me.Heading.Degrees
        /varset LastSitStand	${Me.Sitting}
        /varset TimeSinceMove   0
    } else {
        /varcalc TimeSinceMove (${EverQuest.Running}-${LastMoveTime})/1000
    }
    | Give 60 seconds when first starting
    |/if (${Math.Calc[(${EverQuest.Running}-${BootTime})/1000]}<60) /varset TimeSinceMove 60
/return

|----------------------------------------------------------------------------
|- SUB: FindTarget - Determines the optimal target
|---------------------------------------------------------------------------- 
Sub FindTarget(string FromWhere)

	| Debug call stack
	CALLINGSUB
	CALLINGINDEX
	PUSHCALL

    CALLTRACE Enter from ${FromWhere}

    /if (${Spawn[id ${Me.XTarget[1].ID} pcpet xtarhater].ID}) /call KillPCPet
    |- Handle cases where our autotarget is no longer valid because it isn't a valid spawn or is dead.
    
    |- Reverting where pull choices happen so that we can do an instant find target engagement upon returning versus
    |- waiting for a full mainloop iteration to be done. Should allow groups to sync on a pull faster.
    /if (${DoPull[SETTINGVAL]} == PMODE_CHAIN) {
        /if (${Pull_IsChainReady[]}) {
            /call Pull_DoPull ${DoPull[SETTINGVAL]} 0 FROMHERE
        }
    } else /if (${DoPull[SETTINGVAL]} != PMODE_OFF) {
        /if (!${XAssist.XTFullHaterCount}) {
            |- Check if we have pull enabled
            /call Pull_DoPull ${DoPull[SETTINGVAL]} 0 FROMHERE
        }
    }

    /if (${autotargetid} != 0) {
        /if (${SpawnCount[id ${autotargetid}]} ) {     
            /if (${Spawn[id ${autotargetid}].Type.Equal[Corpse]}) /call ClearTarget
        } else {
            /call ClearTarget
        }
    }
    |- FollowMarkTarget causes RG to have allow RG toons focus on who the group has marked. We'll exit early if this is the case.
    /if (${FollowMarkTarget[SETTINGVAL]}) {
        /if (${Me.GroupMarkNPC[${FollowMarkTarget[SETTINGVAL]}].ID} && ${autotargetid}!=${Me.GroupMarkNPC[${FollowMarkTarget[SETTINGVAL]}].ID}) {
            /varset autotargetid ${Me.GroupMarkNPC[${FollowMarkTarget[SETTINGVAL]}].ID}
            POPCALL
            /return
        }
    } 
    
    |- Now handle normal situations where we need to choose a target because we don't have one.
    /if (${assistid} == ${Me.ID}) {
        |- We need to handle manual targeting and autotargeting seperately
        /if (!${DoAutoTarget[SETTINGVAL]}) {
            |- Manual targetting let the manual user target any npc or npcpet. 
            /if (${autotargetid} != ${Target.ID} && (${Target.Type.Equal[npc]} || ${Target.Type.Equal[npcpet]}) && ${Target.Distance} < ${AssistRange[SETTINGVAL]} && ${Target.DistanceZ} < 20 && ${Target.Aggressive}) {
                /echo Targeting: \ag${Target.CleanName}\ax [ID: \ag${Target.ID}\ax]
                /varset autotargetid ${Target.ID}
            }
        } else {
            |- If we're the main assist, we need to scan our nearby area and choose a target based on our built in algorithm. We
            |- only need to do this if we don't already have a target. Assume if any mob runs into camp, we shouldn't reprioritize
            |- unless specifically told.

            /if (!${autotargetid}) {
                |- If we currently don't have a target, we should see if there's anything nearby we should go after. 
                CALLTRACE Assist Range ${AssistRange[SETTINGVAL]} :: Range to look ${If[${MAScanZRange[SETTINGVAL]},${MAScanZRange[SETTINGVAL]},${AssistRange[SETTINGVAL]}]}
                /call MATargetScan ${AssistRange[SETTINGVAL]} ${If[${MAScanZRange[SETTINGVAL]},${MAScanZRange[SETTINGVAL]},${AssistRange[SETTINGVAL]}]} FROMHERE
                /varset autotargetid ${Macro.Return}
                CALLTRACE MATargetScan returned ${autotargetid} -- Current Target: ${Target.CleanName}[${Target.ID}]
                DEBUG MATargetScan returned ${autotargetid} -- Current Target: ${Target.CleanName}[${Target.ID}]
            } else {
                |- If StayOnTarget is off, we're going to scan if we don't have full aggro. As this is a dev applied setting that defaults to on, it should
                |- Only be turned off by tank modes.
                /if (!${StayOnTarget[SETTINGVAL]}) {
                    /varset autotargetid ${MATargetScan[${AssistRange[SETTINGVAL]},${If[${MAScanZRange[SETTINGVAL]},${MAScanZRange[SETTINGVAL]},${AssistRange[SETTINGVAL]}]}]}
                    CALLTRACE Re-targeting: MATargetScan says we need to target ${Spawn[id ${autotargetid}].CleanName} [${autotargetid}]
                    DEBUG Re-targeting: MATargetScan says we need to target ${Spawn[id ${autotargetid}].CleanName} [${autotargetid}]
                }
            }
        }
    } else {
        |- We're not the main assist so we need to choose our target based on our main assist.
        |- Only change if the group main assist target is an NPC ID that doesn't match the current autotargetid. This prevents us from 
        |- swapping to non-NPCs if the  MA is trying to heal/buff a friendly or themselves.
        /if (${AssistOutside[SETTINGVAL]}) {
            DEBUG FindTarget Assisting ${assistname} [${assistid}] -- Target Aggressive? ${Spawn[${Spawn[id ${assistid}].AssistName}].Aggressive} 
            /if (${Spawn[${Spawn[id ${assistid}].AssistName}].Aggressive} && (${SpawnCount[id ${Spawn[${Spawn[id ${assistid}].AssistName}].ID} npc]} || ${SpawnCount[id ${Spawn[${Spawn[id ${assistid}].AssistName}].ID} npcpet]}) ) {
                DEBUG FindTarget Setting Target To ${Spawn[${Spawn[id ${assistid}].AssistName}].CleanName} [${Spawn[${Spawn[id ${assistid}].AssistName}].ID}]
                /varset autotargetid ${Spawn[${Spawn[id ${assistid}].AssistName}].ID}
            }
        } else /if ((${SpawnCount[id ${Me.GroupAssistTarget.ID} npc]} || ${SpawnCount[id ${Me.GroupAssistTarget.ID} npcpet]}) && ${autotargetid} != ${Me.GroupAssistTarget.ID}) {
            /varset autotargetid ${Me.GroupAssistTarget.ID}
        }
    }
    |--Target the new target we'll do another spawn check just in case. Given we just did our spawn checks,
    |- Assume the target is still valid so we don't do two more spawn checks.
    /if (${autotargetid} && ${Target.ID}!=${autotargetid}) {
        /call SetTarget ${autotargetid}
    }
    CALLTRACE Return to ${FromWhere} :: autotargetid ${autotargetid}
    POPCALL
/return 

|----------------------------------------------------------------------------
|- SUB: MATargetScan - Performs target selection as the group's main assist. 
|- Targets unmezzable mobs first, and highest level mob second. No named checks
|- at the moment as that leads to funkiness in ToV. First we look through nearby
|- spawn searches, then we'll go through our xtarget if the spawn searches fail.
|---------------------------------------------------------------------------- 
Sub MATargetScan(int radius, int zradius, string FromWhere)

	| Debug call stack
	CALLINGSUB
	CALLINGINDEX
	PUSHCALL

    CALLTRACE Enter from ${FromWhere}

    /declare aggrosearch string local "npc radius ${radius} zradius ${zradius} targetable playerstate 4"
    /declare aggrosearchpet string local "npcpet radius ${radius} zradius ${zradius} targetable playerstate 4"
    
    |- We'll target the highest level mob second
    /declare lowesthp_val int local 101
    /declare tokill_id int local 0

    /declare tmp_spawninfo spawn local NULL

    |- TO DO FIX THE DUPLICATION BELOW IN A FUTURE CODE CLEANUP. Use the same
    |- SpawnString Array setup as rgmez.inc line 266-268.
    /declare i int local 1

    CALLTRACE Checking xtargets
    |- Maybe spawn search is failing us -- look through the xtarget list
    /for i 1 to ${Me.XTarget}
        /if (${Me.XTarget[${i}].TargetType.Equal[Auto Hater]} && ${Me.XTarget[${i}].ID}) {
            /squelch /vardata tmp_spawninfo Spawn[id ${Me.XTarget[${i}].ID}]
            DEBUG Found ${tmp_spawninfo.CleanName} [${tmp_spawninfo.ID}] Distance: ${tmp_spawninfo.Distance}
            /if (${tmp_spawninfo.Distance} > ${radius}) /continue

            |- Check for lack of aggro and make sure we get the ones we haven't aggro'd. We can't
            |- get aggro data from the spawn data type.
            
            /if (  ${Me.HaveExpansion[19]} ) {
                /if (${Me.XTarget[${i}].PctAggro}<100 && ${IsTanking}) {
                    |- Coarse check to determine if a mob is _not_ mezzed. No point in waking a mezzed mob if we don't need to.
                    /if (${Select[${Me.XTarget[${i}].Animation},1,5,6,27,43,44,45,80,82,112,134,135]} > 0) {
                        DEBUG Have not fully aggro'd ${tmp_spawninfo.CleanName} -- returning ${tmp_spawninfo.CleanName} [${tmp_spawninfo.ID}]
                        POPCALL
                        /return ${tmp_spawninfo.ID}
                    }
                }
            }    
            
            |- If a name has pulled in we target the name first and return. Named always
            |- take priority.
            /if ( ${tmp_spawninfo.Named} ) {
                DEBUG Found Named: ${tmp_spawninfo.Name} -- returning ${tmp_spawninfo.ID}
                POPCALL
                /return ${tmp_spawninfo.ID}
            }
            
            /if ( ${tmp_spawninfo.Body.Name.Equal[Giant]} ) {
                POPCALL
                /return ${tmp_spawninfo.ID}
            }
            
            |- Select lowest hp mob
            /if ( ${tmp_spawninfo.PctHPs} < ${lowesthp_val} ) {
                /varset tokill_id ${tmp_spawninfo.ID}
                /varset lowesthp_val ${tmp_spawninfo.PctHPs}
            }             
        }
    /next i
    
    CALLTRACE We apparently didn't find anything on xtargets, doing a search for mezzed targets

    |- We didn't find anything to kill yet so spawn search
    /if (!${tokill_id}) {
        DEBUG Falling back on Spawn Searching
        /declare aggro_mobcount int local ${SpawnCount[${aggrosearch}]}
        /declare aggro_petcount int local ${SpawnCount[${aggrosearchpet}]}
        DEBUG NPC Target Scan: ${aggrosearch} ==> ${aggro_mobcount}
        DEBUG NPCPET TargetScan: ${aggrosearchpet} ==> ${aggro_petcount}
        /if ( ${aggro_mobcount} > 0 ) {
            /for i 1 to ${aggro_mobcount}
                
                /squelch /vardata tmp_spawninfo NearestSpawn[${i},${aggrosearch}]
                |- The spawn is already in combat with someone else, we should skip them.
                /if (${SafeTargeting[SETTINGVAL]}) {
                    /if (${IsSpawnFightingStranger[${tmp_spawninfo.ID},${radius}]}) /continue
                }
                
                |- If a name has pulled in we target the name first and return. Named always
                |- take priority. Note: More mobs as of ToL are "named" even though they really aren't.
                /if ( ${tmp_spawninfo.Named} ) {
                    DEBUG Found Named: ${tmp_spawninfo.Name} -- returning ${tmp_spawninfo.ID}
                    /return ${tmp_spawninfo.ID}
                }
                
                |- Second is unmezzables
                /if ( ${tmp_spawninfo.Body.Name.Equal[Giant]} ) {
                    /return ${tmp_spawninfo.ID}
                }
                
                |- Finally -- lowest hp
                /if ( ${tmp_spawninfo.PctHPs} < ${lowesthp_val} ) {
                    /varset tokill_id ${tmp_spawninfo.ID}
                    /varset lowesthp_val ${tmp_spawninfo.PctHPs}
                }
                
            /next i
        }
        /if ( ${aggro_petcount} > 0 ) {
            /for i 1 to ${aggro_petcount}
                /squelch /vardata tmp_spawninfo NearestSpawn[${i},${aggrosearchpet}]

                /if (${SafeTargeting[SETTINGVAL]}) {
                    /if (${IsSpawnFightingStranger[${tmp_spawninfo.ID},${radius}]}) /continue
                }

                /if ( ${tmp_spawninfo.PctHPs} < ${lowesthp_val} ) {
                    /varset tokill_id ${tmp_spawninfo.ID}
                    /varset lowesthp_val ${tmp_spawninfo.PctHPs}
                }    
            /next i
        }
    }
    |- Returning the highest level mob we've found
    CALLTRACE Exit to ${FromWhere} with mob ${Spawn[id ${tokill_id}].CleanName} [${tokill_id}]
/return ${tokill_id}

|----------------------------------------------------------------------------
|- SUB: IsSpawnFightingStranger
|- Checks all nearby spawns to see if they're fighting a stranger. A stranger is
|- anyone who isn't a merc in our group,isn't in our dannet, or doesn't have an owner on our dannet.
|----------------------------------------------------------------------------
Sub IsSpawnFightingStranger(int spawn_id, int radius)

    /declare tmp_tgtinfo spawn local
    /squelch /vardata tmp_tgtinfo Spawn[id ${spawn_id}]

    /declare pcsearch string local "pc radius ${radius} zradius ${radius}"
    /declare pcpetsearch string local "pcpet radius ${radius} zradius ${radius}"
    /declare mercsearch string local "mercenary radius ${radius} zradius ${radius}"
    /declare pcsearch_count int local ${SpawnCount[${pcsearch}]}
    /declare mercsearch_count int local ${SpawnCount[${mercsearch}]}
    /declare pcpetsearch_count int local ${SpawnCount[${pcpetsearch}]}

    /declare i int local 1
    /declare tmp_spawninfo spawn local

    |- First we check all nearby PCs
    /if (${pcsearch_count} > 0) {
        /for i 1 to ${pcsearch_count}
            /squelch /vardata tmp_spawninfo NearestSpawn[${i},${pcsearch}]
            /if (${tmp_spawninfo.AssistName.Length}) {
                    DEBUG My Interest: ${tmp_tgtinfo.Name} =? Their Interest: ${tmp_spawninfo.AssistName}
                /if (${tmp_tgtinfo.Name.Equal[${tmp_spawninfo.AssistName}]}) {
                    DEBUG [PC] Fighting same mob as: ${tmp_spawninfo.CleanName} Theirs: ${tmp_spawninfo.AssistName} Ours: ${tmp_tgtinfo.Name}
                    |- We know this PC is fighting the same mob as us so let's make sure we know them
                    /if (!${IsPCSafe[${tmp_spawninfo.CleanName}]}) {
                        /echo \ar WARNING: \ax Almost attacked other PCs [${tmp_spawninfo.CleanName}] mob. Not attacking \aw${tmp_spawninfo.AssistName}\ax
                        /return TRUE
                    }
                }
            }
        /next i
    }

    |- Then we check all nearby pcpets
    /if (${pcpetsearch_count} > 0) {
        /for i 1 to ${pcpetsearch_count}
            /squelch /vardata tmp_spawninfo NearestSpawn[${i},${pcpetsearch}]
            /if (${tmp_spawninfo.AssistName.Length}) {
                DEBUG My Interest: ${tmp_tgtinfo.Name} =? Their Interest: ${tmp_spawninfo.AssistName}
                /if (${tmp_tgtinfo.Name.Equal[${tmp_spawninfo.AssistName}]}) {
                    DEBUG [PET] Fighting same mob as: ${tmp_spawninfo.CleanName} [${tmp_spawninfo.Master.CleanName}] Theirs: ${tmp_spawninfo.AssistName} Ours: ${tmp_tgtinfo.Name}
                    |- This merc is fighting the same mob as us, so let's make sure we know their master.
                    /if (!${IsPCSafe[${tmp_spawninfo.Master.CleanName}]}) {
                        /echo \ar WARNING: \ax Almost attacked other PCs [${tmp_spawninfo.Master.CleanName}] mob. Not attacking \aw${tmp_spawninfo.AssistName}\ax
                        /return TRUE
                    }
                }
            }
        /next i
    }

    |- Then we check all nearby mercs
    /if (${mercsearch_count} > 0) {
        /for i 1 to ${mercsearch_count}
            /squelch /vardata tmp_spawninfo NearestSpawn[${i},${mercsearch}]
            /if (${tmp_spawninfo.AssistName.Length}) {
                DEBUG My Interest: ${tmp_tgtinfo.Name} =? Their Interest: ${tmp_spawninfo.AssistName}
                /if (${tmp_tgtinfo.Name.Equal[${tmp_spawninfo.AssistName}]}) {
                    DEBUG [MERC] Fighting same mob as: ${tmp_spawninfo.CleanName} [${tmp_spawninfo.Owner.CleanName}] Theirs: ${tmp_spawninfo.AssistName} Ours: ${tmp_tgtinfo.Name}
                    |- This merc is fighting the same mob as us, so let's make sure we know their owner.
                    /if (!${IsPCSafe[${tmp_spawninfo.Owner.CleanName}]}) {
                        /echo \ar WARNING: \ax Almost attacked other PCs [${tmp_spawninfo.Owner.CleanName}] mob. Not attacking \aw${tmp_spawninfo.AssistName}\ax
                        /return TRUE
                    }
                }
            }
        /next i
    }
/return FALSE

|----------------------------------------------------------------------------
|- SUB: IsPCSafe
|- Returns TRUE if the PC is "safe" (known) or FALSE otherwise.
|- Safe pieces are one or more of the following:
|- On our DanNet or in our OaList
|- In our Group
|- In our Raid
|- In our Guild
|----------------------------------------------------------------------------
Sub IsPCSafe(string pc_name)
    |- Are they in our DanNet?
    /if (${DanNet.Peers.Find[${pc_name}]}) /return TRUE

    |- Are they in our OaList?
    /if (${OaList[SETTINGVAL].Find[${pc_name}]}) /return TRUE 

    |- Are they in our group?
    /if (${Group.Member[${pc_name}].ID}) /return TRUE

    |- Are they in our raid?
    /if (${Raid.Member[${pc_name}].ID}) /return TRUE

    |- Are they in our guild?
    /if (${Spawn[pc ${pc_name}].Guild.Equal[${Me.Guild}]}) /return TRUE

/return FALSE

|----------------------------------------------------------------------------
|- SUB: Ok2Engage - TRUE if it's ok to ENGAGE, FALSE if it is not.
|---------------------------------------------------------------------------- 
Sub Ok2Engage
    |- Make sure we've enabled the auto engagement system
    /if (!${DoAutoEngage[SETTINGVAL]}) /return FALSE
    |- Make sure our current target is our auto target
    /if (${Target.ID}!=${autotargetid}) {
        DEBUG ${Target.ID}!=${autotargetid} --> Not Engaging
        /return FALSE
    }
    |- Is the target mezzed and we can't break mez?
    /if (${Target.Mezzed.ID} && !${AllowMezBreak[SETTINGVAL]}) {
        DEBUG Target Mezzed and !AllowMezBreak --> Not Engaging
        /return FALSE
    }

    |- Are we in combat and not backing off?
    /if ( (${XAssist.XTFullHaterCount} || ${KillTargetID}) && !${BackOffFlag}) {
        |- Is the mob in our assist range?
        /if (${Target.Distance}<${AssistRange[SETTINGVAL]}) {
            |- Obey assist HP Pct unless we're tanking or we're MA.
            /if (${Target.PctHPs}<=${AutoAssistAt[SETTINGVAL]} || ${IsTanking} || ${assistid}==${Me.ID}) {
                DEBUG (${Target.PctHPs}<=${AutoAssistAt[SETTINGVAL]} || IsTanking: ${IsTanking} || IsMA: ${assistid}==${Me.ID}) OK2Assist!
                /return TRUE
            }
            DEBUG Target HPs too high and I'm not Tanking/MA: (${Target.PctHPs}<=${AutoAssistAt[SETTINGVAL]} || ${IsTanking} || ${assistid}==${Me.ID})
        }
        DEBUG AssistRange: (${Target.Distance}<${AssistRange[SETTINGVAL]})
    }
    DEBUG Combat Status: ( (${XAssist.XTFullHaterCount} || ${KillTargetID}) && !${BackOffFlag})
|- Default to not to engage
/return FALSE

|----------------------------------------------------------------------------
|- SUB: Melee Engage Target - 
|---------------------------------------------------------------------------- 
Sub EngageTarget(string FromWhere)
    /if (!${DoAutoEngage[SETTINGVAL]}) /return FALSE
      
	| Debug call stack
	CALLINGSUB
	CALLINGINDEX
	PUSHCALL

    CALLTRACE Enter from ${FromWhere}
    
    /declare tmpspawn spawn local
    /squelch /vardata tmpspawn Spawn[id ${autotargetid}]
    /if (${Me.State.Equal[FEIGN]} && ${Me.Class.ShortName.NotEqual[MNK]}) /stand
    /if (${Target.ID}==${autotargetid} && ${Target.Distance} <= ${AssistRange[SETTINGVAL]}) {
        /if (${DoMelee[SETTINGVAL]}) {
            |- Should have an aggro gate here on this one.
            /if (${Me.Sitting}) {
                DEBUG Standing to Engage Target
                /varset InMedState FALSE
                /stand
            }
            /if ( (${Target.PctHPs}<=${AutoAssistAt[SETTINGVAL]} || ${assistid}==${Me.ID}) && ${Target.PctHPs}>0 ) {
                CALLTRACE Deciding whether to keep moving or to enter combat:  Target distance ${Target.Distance} MaxRangeTo ${Target.MaxRangeTo}
                |- Choosing outer ranges for melee to avoid constant shifting of melee toons. 30 is close to the max melee range.
                /if (${Target.Distance} > ${Target.MaxRangeTo}) {
                    CALLTRACE Moving... Target distance ${Target.Distance} MaxRangeTo ${Target.MaxRangeTo}
                    /if (${SubDefined[${Me.Class.ShortName}_PreEngageRoutine]}) /call ${Me.Class.ShortName}_PreEngageRoutine
                    /call NavInCombat ${autotargetid} ${Target.MaxRangeTo} FALSE FROMHERE
                } else {
                    CALLTRACE Sticking and entering combat
                    /nav stop log=off
                    /if (${Stick.Status.Equal[OFF]}) /call DoStick
                    /if (!${Me.Combat}) {
                        /echo \awNOTICE:\ax Engaging ${Target.CleanName} in mortal combat.
                        /keypress AUTOPRIM
                    }
                    /delay 10 ${Me.Combat}
                }
            } 
        }
    } else {
        /if (!${DoMelee[SETTINGVAL]} && ${Select[${Me.Class.ShortName},RGCASTERS]} && ${Target.Named} && ${Target.Body.Name.Equal[Dragon]} ) {
            /stick pin 40 
            }
        /if (${Stick.Status.Equal[ON]}) /stick off
    }
    POPCALL
/return TRUE

|----------------------------------------------------------------------------
|- SUB: NavInCombat - Navigates to a mob in combat based on a set of rules
|- spawn_id -- mob to nav to
|- distance -- distance away from the mob at our final position
|- dont_stick -- If True, does not re-stick.
|----------------------------------------------------------------------------
Sub NavInCombat(int spawn_id, float distance, bool dont_stick, string FromWhere)
    /if (!${DoAutoEngage[SETTINGVAL]}) /return FALSE
    DEBUG  NavInCombat Nav Path Exisits:${Navigation.PathExists[id ${spawn_id} distance ${distance}]} -- ${spawn_id} ${distance}
    /if (${Stick.Active}) /Stick off
    /if ( ${Navigation.PathExists[id ${spawn_id} distance ${distance}]} ) {
        |- Nav to our mob
        /nav id ${spawn_id} distance=${distance} log=off lineofsight=on
        /delay 2s (${Navigation.Active} && ${Navigation.Velocity} > 0)
        /while (${Navigation.Active} && ${Navigation.Velocity} > 0) {
            TRIGGERBIND
            /delay 1
        }
        DEBUG Done Naving. Now ${Spawn[id ${spawn_id}].Distance} away. LoS: ${Spawn[id ${spawn_id}].LineOfSight}
    } else {
        /moveto id ${Target.ID} uw mdist ${distance}
        /while (${MoveTo.Moving} && !${MoveUtils.Stuck}) {
            TRIGGERBIND
            /delay 1
        }
    }

    |- Once we're in range we'll go back to sticking based on our StickHow.
    |- May want to re-think if we want to reduce stick usage.
    /if (!${dont_stick}) {
        /call DoStick ${spawn_id}
    }
/return TRUE

|----------------------------------------------------------------------------
|- SUB: NavAroundCircle - Navigates to a point on a circle around the mob within ${radius}.
|- Inspired by FindvalidRangeLocation in MuleAssist.mac
|- spawn_id -- mob to nav to
|- radius -- distance away from the mob at our final position
|- dont_stick -- If True, does not re-stick.
|----------------------------------------------------------------------------
Sub NavAroundCircle(int spawn_id, float radius, bool dont_stick)
    /if (!${DoAutoEngage[SETTINGVAL]}) /return FALSE
    /if (!${spawn_id}) /return FALSE
    /if (!${Navigation.MeshLoaded}) {
        /echo \arERROR: \ax Mesh not loaded for ${Zone.Name}, can't Nav.
        /return FALSE
    }

    /if (${SpawnCount[id ${spawn_id}]}) {
        /declare tmp_spawn spawn local
        /squelch /vardata tmp_spawn Spawn[id ${spawn_id}]
        /declare spawn_x float local ${tmp_spawn.X}
        /declare spawn_y float local ${tmp_spawn.Y}
        /declare spawn_z float local ${If[${tmp_spawn.Z}<1,5,${tmp_spawn.Z}]}
    } else {
        DEBUG Spawn ${spawn_id} not found.
        /return FALSE
    }
    /declare tgt_x float local 0
    /declare tgt_y float local 0

    /declare steps int local 0

    |- We need to get the spawn's heading to _us_ based on our heading to the spawn
    |- to nav a circle around it. This is done by inverting the coordinates. E.g.,
    |- If our heading to the mob is 90 degrees CCW, their heading to us is 270 degrees CCW.
    /declare tmp_degrees float local ${Math.Calc[${tmp_spawn.HeadingTo.DegreesCCW}-180]}
    /if (${tmp_degrees} < 0) /varcalc tmp_degrees 360 - ${tmp_degrees}

    /declare steps_to_degrees float local 0
    |- Loop until we find an x,y loc ${radius} away from the mob,
    |- that we can navigate to, and is in LoS
    DEBUG PRE-LOOP: tmp_degrees \aw${tmp_degrees}\ax Me.X \aw${Me.X}\ax Me.Y \aw${Me.Y}\ax
    /for steps 1 to 36
        |- EQ's x coordinates have an opposite number line. Positive x values are to the left of 0, 
        |- negative values are to the right of 0, so we need to - our radius.
        |- EQ's unit circle starts 0 degrees at the top of the unit circle instead of the right, so
        |- the below still finds coordinates rotated counter-clockwise 90 degrees.
        /varset tgt_x ${Math.Calc[${spawn_x} + (-${radius} * ${Math.Cos[${tmp_degrees}]})]}
        /varset tgt_y ${Math.Calc[${spawn_y} + (${radius} * ${Math.Sin[${tmp_degrees}]})]}

        DEBUG steps \aw${steps}\ax tmp_degrees \aw${tmp_degrees}\ax tgt_x \aw${tgt_x}\ax tgt_y \aw${tgt_y}\ax
        |- First check that we can navigate to our new target
        /if (${Navigation.PathExists[locyxz ${tgt_y} ${tgt_x} ${spawn_z}]}) {
            |- Then check if our new spots has line of sight to our target.
            /if (${LineOfSight[${tgt_y},${tgt_x},${spawn_z}:${spawn_y},${spawn_x},${spawn_z}]}) {
                |- Make sure it's a valid loc...
                /if (${EverQuest.ValidLoc[${tgt_x} ${tgt_y} ${spawn_z}]}) {
                    DEBUG Found valid position:  X: \aw${tgt_x}\ax Y \aw${tgt_y}\ax Z: \aw${spawn_z}\ax SpawnX: \aw${spawn_x}\ax SpawnY: \aw${spawn_y}\ax SpawnZ: \aw${spawn_z}\ax
                    /nav locyxz ${tgt_y} ${tgt_x} ${spawn_z} log=off
                    /delay 2s ${Navigation.Active}
                    /delay 10s !${Navigation.Active}
                    /squelch /face fast
                    DEBUG \awTgt.LOS:\ax ${Target.LineOfSight} -- \aw Tgt.Dist:\ax ${Target.Distance}
                    DEBUG: Target.XYZ \aw${Target.X} ${Target.Y} ${Target.Z}\ax
                    /return TRUE
                } else {
                    DEBUG \awValidLoc\ax Check failed
                }
            } else {
                DEBUG \awLineOfSight\ax Check failed
            }
        } else {
            DEBUG \awMQ2Nav\ax Check failed
        }
        |- Increase our check by 10 degrees.
        /varcalc tmp_degrees (${tmp_degrees} + 10) % 360.0
    /next steps
/return FALSE
|--------------------------------------------------------------------------
|- SUB: DoStick - Handles sticking behavior for the macro
|--------------------------------------------------------------------------
Sub DoStick(int spawn_id)
    /declare stick_target int local ${If[${spawn_id},${spawn_id},${Target.ID}]}
    /if (${StickHow[SETTINGVAL].NotEqual[NULL]}) {
        DEBUG Sticking: ${StickHow[SETTINGVAL]} id ${stick_target}
        /stick ${StickHow[SETTINGVAL]} id ${stick_target}
    } else {
        /if (${Me.ID} == ${assistid}) {
            /stick 20 id ${stick_target} moveback uw
        } else {
            /stick 20 id ${stick_target} behindonce moveback uw
        }
    }
/return 

|--------------------------------------------------------------------------
|- SUB: MicroCombat - Miniature combat function for when you want to handle
|- combat events but don't want to return to the full mainloop. This will
|- not leverage the full mainloop and only performs DPS/Debuffs (so no healing).
|- Predominantly a utility function targeted at binds or for rgcustom usage.
|--------------------------------------------------------------------------
Sub MicroCombat
    |- Just to avoid potential issues of pulling NPCs and potential
    |- bugs with MQ2 while loops we'll leave early
    /if (!${XAssist.XTFullHaterCount}) /return
    /while (${XAssist.XTFullHaterCount}) {
        /call FindTarget FROMHERE
        /call EngageTarget
        /if (${SubDefined[RGCustom_Combat_Routine]}) /call RGCustom_Combat_Routine
        /call ${Me.Class.ShortName}_Combat_Routine
        /delay 1
    }
/return

|--------------------------------------------------------------------------
|- SUB: FindValidMeshLoc - Finds valid location on mesh if we're stuck off
|- mesh while attempting to navigate in combat or elsewhere. Then uses
|- moveto to get there.
|- in [optional] xyz - |X|Y|Z| loc to use instead of default to spawn anchor.
|- Based off of/Inspired by: FindvalidRangeLocation in MuleAssist
|--------------------------------------------------------------------------
Sub ReturnToMesh(string xyz)

    /if (${xyz.Length} > 0) {
.
    } else {
        |- We're going to choose a nearby spawn as the target anchor. We 
        |- assume the spawn is on the mesh
    }

    |- We're going to try and move outward in circle radius around us using moveto
    |- At each point we'll see if we have a path to the NPC

/return

| ----------------------------------------------------------------------------
| SUB: Check and Fix Stuck Gems
| ----------------------------------------------------------------------------
Sub CheckStuckGems
    |- delay 2 seconds to account for server sync delays
    |- break out of delay if we register we stop casting (IE: gems are not locked)
    /delay 20 !${Me.Casting.ID}
    
    |- If we have a casting window, or we are not casting return -- we probably triggered on the GCD
    /if (${Window[CastingWindow].Open} || !${Me.Casting.ID}) /return
    
    |- If origin is ready we should Cast origin, then delay 5 seconds
    |- OR until we have a casting window, then cancel cast and return
    /if (${Me.AltAbilityReady[origin]}) {
        /alt act ${Me.AltAbility[origin].ID}
        /delay 50 ${Window[CastingWindow].Open}
        /stopcast
        
        |- Set up an opportunity to exit early.
        /delay 10 !${Window[CastingWindow].Open}
        /call PrintGroupMessage "Gem Detection Code Executed"
    } else {
        /echo Origin AA not ready.
        |- /delay 20
    }
/return

|----------------------------------------------------------------------------
|- SUB: FollowToon
|---------------------------------------------------------------------------- 
Sub FollowToon
    /declare followspawn spawn local 
    /vardata followspawn Spawn[pc =${FollowToonName[SETTINGVAL]}]
    
    /if (${followspawn.ID} && !${followspawn.Dead}) {
        /if (${Me.Dead}) /return FALSE
        /if (${followspawn.Distance} < ${ChaseDistance[SETTINGVAL]}) /return FALSE
        
        |- Use MQ2Nav with moveto as a failover if we have a mesh. We'll use a nav
        |- command if the mesh is loaded and we have a path. If we don't have a path
        |- we'll use a moveto. This will hopefully get us over spots of the mesh that
        |- are missing with minimal issues.
        /if (${Navigation.MeshLoaded}) {
            /if (!${Navigation.Active}) {
                /if ( ${Navigation.PathExists[id ${followspawn.ID}]} ) {
                    /squelch /nav id ${followspawn.ID} | log=critical distance=${ChaseDistance[SETTINGVAL]} lineofsight=${If[${Select[${Me.Class.ShortName},RGCASTERS]},on,off]}
                } else {
                    |- Assuming no line of site problems.
                    |- Moveto underwater style until 20 units away
                    /squelch /moveto id ${followspawn.ID}  uw mdist ${ChaseDistance[SETTINGVAL]}
                }
                |- NOTE: At this point KA actually has a further failover if
                |- there was no line of sight for moveto and the mesh failed.
                |- In the future we oculd do a /goto trampoline into afollow 
                |- as an error failover if needed.
            }
        } else /if (${followspawn.Distance}>${ChaseDistance[SETTINGVAL]} && ${followspawn.Distance}<400) {
            |- If we don't have a mesh we're using afollow as legacy RG behavior.
            /squelch /afollow spawn ${followspawn.ID}
            /squelch /afollow ${ChaseDistance[SETTINGVAL]}
            /delay 2s ${followspawn.Distance}<${ChaseDistance[SETTINGVAL]}
            /if (${followspawn.Distance}<${ChaseDistance[SETTINGVAL]}) {
                /squelch /afollow off
            }
        }
    } else {
        /return FALSE
    }
/return TRUE
|----------------------------------------------------------------------------
|- SUB: AutoCampCheck
|- Automatically retuns to camp when conditions are met. 
|-
|- Returns false when we aren't going to camp, true when we do return to camp.
|----------------------------------------------------------------------------
Sub AutoCampCheck
    |- Don't camp if return to camp is off
    /if (!${ReturnToCamp[SETTINGVAL]}) /return FALSE

    |- If we're casting and we're not a bard, don't camp.
    /if (${Me.Casting.ID} && ${Me.Class.ShortName.NotEqual[BRD]}) /return FALSE

    |- If we're following someone, don't camp.
    /if (${Spawn[=${FollowToonName[SETTINGVAL]}].ID}) /return FALSE

    |- Don't return to camp if we're not in the zone we set camp in
    /if (${Zone.ID} != ${ZoneID}) /return FALSE

    |- Don't return to camp if we're over 400 from our original camp point.
    /if (${Math.Distance[${Me.Y},${Me.X}:${AutoCampY},${AutoCampX}]}>=400) {
        /call PrintGroupMessage "I'm over 400 units from camp, not returning!"
        /rg campoff
        /return FALSE
    }

    |- ReturnToCamp mode 1 we will only return to camp afer getting beyond camp radius.
    /if (${ReturnToCamp[SETTINGVAL]} == 1) {
        /if (${Math.Distance[${Me.Y},${Me.X}:${AutoCampY},${AutoCampX}]} < ${AutoCampRadius[SETTINGVAL]}) /return FALSE
    }

    |- At this point we're going to return to camp unless we're within a marginal distance to deal with mq2nav distance error
    /if (${Math.Distance[${Me.Y},${Me.X}:${AutoCampY},${AutoCampX}]} > 5) {
        /if (${Navigation.PathExists[locyxz ${AutoCampY} ${AutoCampX} ${AutoCampZ}]}) {
            /nav locxyz ${AutoCampX} ${AutoCampY} ${AutoCampZ} distance=5 log=off
            /while (${Navigation.Active}) {
                TRIGGERBIND
                /delay 1
            }
        } else {
            /moveto loc ${AutoCampY} ${AutoCampX}|on
            /while (${MoveTo.Moving}) {
                TRIGGERBIND
                /delay 1
            }

        }
    }
/return TRUE

|----------------------------------------------------------------------------
|- SUB: TurnChaseOff
|- Callback when setting ReturnToCamp. Turns of Chase mode if on.
|----------------------------------------------------------------------------
Sub TurnChaseOff
    /if (${FollowToonName[SETTINGVAL].NotEqual[NULL]}) {
        /echo \awNOTICE:\ax Detected Chase is on. Turning off for Camp.
        /varset FollowToonName[SETTINGVAL] NULL 
        /return TRUE
    }
/return FALSE

|----------------------------------------------------------------------------
|- SUB: TurnCampOff
|- Callback when setting FollowToonName. Turns off ReturnToCamp.
|----------------------------------------------------------------------------
Sub TurnCampOff
    /if (${ReturnToCamp[SETTINGVAL]}) {
        /echo \awNOTICE:\ax Detected Camp is on. Turning off for Chase.
        /varset ReturnToCamp[SETTINGVAL] 0
        /return TRUE
    }
/return FALSE

|----------------------------------------------------------------------------
|- SUB: BagModRods
|----------------------------------------------------------------------------
Sub BagModRods
    /if ((${Cursor.ID}) && ${CursorTimer}==0 && ${ShitOnCursor.Equal[NULL]} && (${Me.FreeInventory}>1)) {
        /varset ShitOnCursor ${Cursor}
        /varset CursorTimer 1m
    } else /if (${Cursor.ID} && ${CursorTimer}==0 && ${ShitOnCursor.NotEqual[NULL]} && (${Me.FreeInventory}>1)) {
        /echo \aw Something has been left on cursor for over a minute Bagging it
        /autoinventory
        /varset ShitOnCursor NULL
    } else /if (${Cursor.ID} && ${ShitOnCursor.Find[Transvergence]} && (${Me.FreeInventory}>1)) {
        /echo \aw Bagging Mod Rod
        /autoinventory
        /varset ShitOnCursor NULL
    } else /if (${Cursor.ID} && ${ShitOnCursor.Find[Modulation]} && (${Me.FreeInventory}>1)) {
        /echo \aw Bagging Mod Rod
        /autoinventory
        /varset ShitOnCursor NULL
    }
/return

|----------------------------------------------------------------------------
|- SUB: Check Plugin
|----------------------------------------------------------------------------
Sub CheckPlugin(string pluginname)
    /if (!${Bool[${Plugin[${pluginname}]}]}) {
        /squelch /plugin ${pluginname} noauto
        /echo \aw ${pluginname} \ar not detected! \aw This macro requires it! Loading ...
    }
/return 

|----------------------------------------------------------------------------
|- SUB: UnCheck Plugin
|----------------------------------------------------------------------------
Sub UnCheckPlugin(string pluginname)
    /if (${Bool[${Plugin[${pluginname}]}]}) {
        /squelch /plugin ${pluginname} unload noauto
        /echo \ar ${pluginname} detected! \aw Unloading it due to known conflicts with RGMercs! UnLoading ...
    }
/return 

|----------------------------------------------------------------------------
|- SUB: ReloadPlugin 
|----------------------------------------------------------------------------
Sub ReloadPlugin(string pluginame)
    /echo \ar ${pluginame} being reloaded!\ax
    /call UnCheckPlugin ${pluginame}
    /delay 30 
    /call CheckPlugin ${pluginame} 
    /delay 30 
/return
|----------------------------------------------------------------------------
|- SUB: Death Sub
|----------------------------------------------------------------------------
Sub DeathSub
    /echo You are sleeping with the fishes.
    /call ClearTarget
    /if (${FollowToonName[SETTINGVAL].NotEqual[NULL]}) {
        /echo \awNOTICE:\ax You're dead. I'm not chasing ${FollowToonName[SETTINGVAL]} anymore.
        /varset FollowToonName[SETTINGVAL] NULL
    }
	
	|- Cancel any current pull and reset pull status
	/if (${DoPull[SETTINGVAL]} && ${Pull_State}) {
        /call PrintGroupMessage "\awNOTICE:\ax I'm dead. Aborting pull"
		/varset AbortSignal TRUE
	}
		
	
    /while (${Me.Hovering}) {
        /if (${Window[RespawnWnd].Open} && ${InstantRelease[SETTINGVAL]}==1) {
            /nomodkey /notify RespawnWnd RW_OptionsList listselect 1 
            /delay 1s
            /nomodkey /notify RespawnWnd RW_SelectButton leftmouseup
            /delay 5s ${Me.Zoning}
        }
        /delay 1
    }
    /delay 1m !${Me.Zoning}
    /if (${DoFellow[SETTINGVAL]}==1) {
        /if (${FindItem["Fellowship Registration Insignia"].Timer}==0) {
            /delay 30s ${Me.CombatState.Equal[ACTIVE]}
            /useitem "Fellowship Registration Insignia"
            /delay 2s ${FindItem["Fellowship Registration Insignia"].Timer}!=0
        } else {
            /echo \aw Bummer, Insignia on cooldown, you must really suck at this game...
        }
    } else {
        /echo \aw Waiting on someone that knows how to heal to \ar rez me
    }
/return

|----------------------------------------------------------------------------
|- SUB: AutoMed - Modified SitCheck from auto subs, user configureable end/mana % to start medding at 
|- Need: EndMedPct[SETTINGVAL] and MedPct variables to use. Also, note the order of conditions
|- in this function are necessary. 
|---------------------------------------------------------------------------- 
Sub AutoMed(string FromWhere)
    | Bailing out of here if we are already ready. We should be able to stand and sit them manually if need be. Otherwise they pop back up.
    /if (!${DoMed[SETTINGVAL]}) /return
    | Sing your restore song...
    /if (${Me.Class.ShortName.Equal[BRD]} && ${Me.Level}>5) /return

	| Debug call stack
	CALLINGSUB
	CALLINGINDEX
	PUSHCALL

	/if (${CallCircular}) {
		POPCALL
		/return
	}

    CALLTRACE Enter from ${FromWhere}

    | We are on a mount
    /if (${DoMount[SETTINGVAL]}==1 && ${Me.Mount.ID} && !${Zone.Indoor}) {
        /varset SitTimer 0
        /varset InMedState FALSE
        CALLTRACE We are on a mount. Exiting.
        POPCALL
        /return
    }

    /call LastMove

    |-If we're moving/following/navigating/sticking, don't med.
    /if (${Me.Moving} || ${Stick.Active} || ${Navigation.Active} || ${MoveTo.Moving} || ${AdvPath.Following}) {
        | They may have been in a medstate, so preserve that for now.
        CALLTRACE We are moving. Exiting.
        POPCALL
        /return
    }

    | Allow sufficient time for the player to do something before char plunks down. Spreads out med sitting too.
    /if (${TimeSinceMove}<${Math.Calc[7+${Math.Rand[5]}].Int}) /return

    /if (!${Me.Moving} && !${XAssist.XTFullHaterCount} && ${InMedState} && ${Me.Standing} && ${Me.State.NotEqual[MOUNT]}) {
        CALLTRACE We were moving, starting again if conditions are right. Giving 3s
        /echo \awNOTICE [${Time.Time24}]:\ax Something outside RGMercs stood me up while medding.
        /if (!${SitTimer}) {
            /echo \awNOTICE:\ax Delaying sitting for 3 seconds because maybe you wanted to do something.
            /varset SitTimer 30
            POPCALL
            /return
        }
    } 

    | If we were in a medstate, then we should resume sitting and medding.

    |- The default is we med
    /declare enablesit int local 1

    /if (${Select[${Me.Class.ShortName},RGHYBRID]}) {

        |- Handle the case where we're a Hybrid. We need to check mana and endurance. Needs to be done after
        |- the original stat checks.
        CALLTRACE Hybrid check RGHYBRID :: Mana ${Me.PctMana} :: ManaMedPct ${ManaMedPct[SETTINGVAL]} :: Endurance ${Me.PctEndurance} :: EndPct ${EndMedPct[SETTINGVAL]}
    
        /if ( ${Me.PctHPs} >= ${HPMedPctStop[SETTINGVAL]} && ${Me.PctMana} >= ${ManaMedPctStop[SETTINGVAL]} && ${Me.PctEndurance} >= ${EndMedPctStop[SETTINGVAL]} ) {
            POPCALL
            CALLTRACE We are all medded up.
            /varset InMedState FALSE
            /return

        } else /if ( ${Me.PctHPs} <= ${HPMedPct[SETTINGVAL]} || ${Me.PctMana} <= ${ManaMedPct[SETTINGVAL]} || ${Me.PctEndurance} <= ${EndMedPct[SETTINGVAL]} ) {
            CALLTRACE We need to sit
            DEBUG Hybrid Standing: Mana @ ${Me.PctMana} > ${ManaMedPct[SETTINGVAL]} // End. @ ${Me.PctEndurance} > ${EndMedPct[SETTINGVAL]}
        }

    } else /if (${Select[${Me.Class.ShortName},RGCASTERS]} ) {

        |- Handle the case where we're a Hybrid. We may have max END, but not mana
        CALLTRACE Am I a caster? RGCASTERS
    
        CALLTRACE Do I have enough mana? ${Me.PctMana} >= ${ManaMedPctStop[SETTINGVAL]}
        /if ( ${Me.PctHPs} >= ${HPMedPctStop[SETTINGVAL]} && ${Me.PctMana} >= ${ManaMedPctStop[SETTINGVAL]} ) {
            CALLTRACE I dont need to med.
            POPCALL
            /varset InMedState FALSE
            /return

        } else /if (${Me.PctHPs} <= ${HPMedPct[SETTINGVAL]} || ${Me.PctMana} <= ${ManaMedPct[SETTINGVAL]}) {
            CALLTRACE Im supposed to sit
            DEBUG Caster Standing: Mana @ ${Me.PctMana} > ${ManaMedPct[SETTINGVAL]}
        }

    } else /if ( ${Select[${Me.Class.ShortName},RGMELEE]}) {

        CALLTRACE Am I a melee? RGMELEE
    
        CALLTRACE Do I have enough endurance? ${Me.PctEndurance} >= ${EndMedPctStop[SETTINGVAL]}
        /if ( ${Me.PctHPs} >= ${HPMedPctStop[SETTINGVAL]} && ${Me.PctEndurance} >= ${EndMedPctStop[SETTINGVAL]} ) {
            /varset InMedState FALSE
            CALLTRACE Standing up soon
            POPCALL
            /return
        } else /if (${Me.PctHPs} <= ${HPMedPct[SETTINGVAL]} || ${Me.PctEndurance} <= ${EndMedPct[SETTINGVAL]}) {
            CALLTRACE Sitting down soon
        }

    } else {
        /echo \arYour character class is not in the type list(s): rghybrid, rgcasters, rgmelee. That's a problem for a dev.
        POPCALL
        /varset InMedState FALSE
        /return
    }

    |-If we're in combat...
    /if (${XAssist.XTFullHaterCount}) {
        |- Don't med if we're meleeing not matter what
        /if (${DoMelee[SETTINGVAL]}) {
            DEBUG Standing because I'm in Combat.
            /varset enablesit 0
        } else {
            |- Don't med in combat unless DoMed==2
            /if (${DoMed[SETTINGVAL]}!=2) {
                DEBUG Standing because I'm in Combat.
                /varset enablesit 0
            }
        }
    }
  
    |- Are we sitting? Should we be standing? Stand
    CALLTRACE Sitting ${Me.Sitting} :: enablesit ${enablesit}
    /if (${Me.Sitting} && !${enablesit}) {
        DEBUG Med Says I should be standing now
        /varset InMedState FALSE
        /stand
        | Just to be safe we dont pong
        POPCALL
        CALLTRACE Exiting to ${FromWhere} - I am now standing
        /return
    }
    
    |- Are we standing? Should we be sitting? Sit
    /if (!${Me.Sitting} && ${enablesit}) {
        DEBUG Med Says I should be sitting now
        /varset InMedState TRUE
        /sit
        CALLTRACE I am now sitting.
    }

    POPCALL
    CALLTRACE Exit back to ${FromWhere}
/return

|----------------------------------------------------------------------------
|- SUB: FollowRotation -- Loops through a rotation map casting everything where the condition is met -- has wrappers for convenience. Ignores priority order.
|- Used for downtime non-combat situations. WILl OVERRIDE DoAutoTarget.
|- rotation_name -- Name of the map to rotate through. Probably should improve this variable name later.
|- target_id -- Target to cast the spell on
|- conditions -- Conditions to check. Should be passed in the call wrapped in Parse, e.g., ${Parse[0,"cond1 && cond2"]}
|- DoNotStop -- Default behavior of the function is to stop after the first ability found to increase responsiveness. Set DoNotStop to 1 to activate all abilities ready to use.
|----------------------------------------------------------------------------
Sub FollowRotation(string rotation_name, int target_id, string conditions, bool DoNotStop)   
    /if (!${RotationSize[${rotation_name}]}) /return FALSE
    /declare rotationMap string local ${rotation_name}_Map
    /declare rotationTypeMap string local ${rotation_name}_Type_Map
    /declare actionsub string local
    /declare result bool local FALSE
    |- Many conditions throughout RG expect this variable to be named mi. Changing this variable will break
    |- a considerable number of rotation conditions. DO NOT CHANGE. Yes, I know this is fragile and could be done better. - Dr. Who
    /declare mi mapiterator local
    /vardata mi ${rotationMap}.First.Clone  
    /declare mi_type mapiterator local
    /vardata mi_type ${rotationTypeMap}.First.Clone
    
    /if (${conditions.Length} == 0) /varset conditions TRUE

    /if (${${rotationMap}.Count} != ${${rotationTypeMap}.Count}) {
        /echo \arERROR: Rotation maps are out of sync... this shouldn't happen!\ax
    }

    |- Override user's DoAutoTarget setting 
    /declare old_autotarget int local ${DoAutoTarget[SETTINGVAL]}
    /varset DoAutoTarget[SETTINGVAL] 1

    /while (!${mi.IsEnd} ) {     
        DEBUG ${mi.Key} --> (${mi.Value} && ${conditions} && ${PC${${rotationTypeMap}.Find[${mi.Key}].Value}Ready[${mi.Key}]}) --> ${If[(${mi.Value} && ${conditions} && ${PC${${rotationTypeMap}.Find[${mi.Key}].Value}Ready[${mi.Key}]}),TRUE,FALSE]}
        /if (${mi.Value} && ${conditions} && ${PC${${rotationTypeMap}.Find[${mi.Key}].Value}Ready[${mi.Key}]}) {
            /varset actionsub ${${rotationTypeMap}.Find[${mi.Key}].Value}Now
            |- Currently a workaround for AA's as AANow is the only function that
            |- takes an int insead of a string. This will require a class macro
            |- wide refactor to fix.
            /if (${actionsub.Equal[AANow]}) {
                DEBUG -- call ${actionsub} "${mi.Key}" ${target_id}
                /call ${actionsub} ${Me.AltAbility[${mi.Key}].ID} ${target_id}
                /varset result TRUE
            } else {
                DEBUG -- call ${actionsub} "${mi.Key}" ${target_id}
                /call ${actionsub} "${mi.Key}" ${target_id}
                /varset result TRUE
            }
            |- Check if we just summoned something to the cursor
            |- Probably should replace with the following condition if confirmed to be correct
            |- SPA32: CreateItem; SPA109: CreateItemInBag
            |- (${Spell[${mi.Key}].HasSPA[32]} || ${Spell[${mi.Key}].HasSPA[109]})
            /if (${Spell[${mi.Key}].HasSPA[32]}) {
                |- Short delay in case something is summoning an item and 
                |- we want to wait for a server response. Shouldn't affect
                |- responsiveness.
                /delay 2
                |- In case our rotation summons items we'll inventory them.
                /if (${Cursor.ID}) {
                    /autoinventory
                    /delay 5s !${Cursor.ID}
                }
            }
            /if (${CPUThrottle[SETTINGVAL]}) /delay ${CPUThrottle[SETTINGVAL]}
            /if (!${DoNotStop}) {

                |- Reset DoAutoTarget
                /varset DoAutoTarget[SETTINGVAL] ${old_autotarget}
                /return ${result}
            }
        }
        /invoke ${mi.Advance}
    }
    DEBUG Rotation End: ${rotation_name}

    |- Reset DoAutoTarget
    /varset DoAutoTarget[SETTINGVAL] ${old_autotarget}
/return ${result}

|-----------------------------------------------------------------
|-SUB: Ordered_Rotation_Reset  
|- in: rotation_name -- Name of the rotation created
|-
|- This function is used in Ordered Rotations to reset the list iterator to the first element
|- of the rotation. This is particularly useful with Ordered_Rotation_StepOnCast where you
|- want to cast spells in a very specific order such that you know the previous spell has been cast
|- before casting the current.
|-----------------------------------------------------------------     
Sub Ordered_Rotation_Reset(string rotation_name)
    /if (!${RotationSize[${rotation_name}]}) /return FALSE
    /declare listIterName string local ${rotation_name}_List_Iter
    /invoke ${${listIterName}.Reset}
    
/return TRUE
|-----------------------------------------------------------------
|-SUB: Ordered_Rotation_StepOnCast - Do a single step in a DPS rotation
|- if, and only if, the spell can be cast.
|- in: rotation_name -- Name of the rotation created
|- in: act_type -- AA,Item,Disc,Spell,Ability
|- in: target_id -- target to cast against
|- in: conditions -- any additional conditions to check
|-----------------------------------------------------------------
Sub Ordered_Rotation_StepOnCast(string rotation_name, int target_id, string conditions)
    /if (${conditions.Length} == 0) /varset conditions TRUE
    |- TODO: Move this to a generic RGSubs set of function calls.
    |- First our Spell Rotation
    |- Cast the spell in our current rotation slot
    /declare listIterName string local ${rotation_name}_List_Iter
    
    |- Used to get our conditions for the spell -- variable name kept short
    |- for that reason
    |- Many conditions throughout RG expect this variable to be named mi. Changing this variable will break
    |- a considerable number of rotation conditions. DO NOT CHANGE. Yes, I know this is fragile and could be done better. - Dr. Who
    /declare mi mapiterator local 
    /vardata mi ${rotation_name}_Map.Find[${${listIterName}.Value}]
    /declare mi_type mapiterator local
    /vardata mi_type ${rotation_name}_Type_Map.Find[${${listIterName}.Value}]
    /declare actionsub string local ${mi_type.Value}Now
    /declare result bool local FALSE

    |- The Det check is what makes this a DPS specific rotation. If we wanted to generalize it we could 
    |- pass the Det check as a condition if we wanted to arbitrarily single step through a map and perform
    |- an action on each element.
    /if (${mi.Value} && ${conditions} && ${NPC${mi_type.Value}Ready[${${listIterName}.Value}]}) {
        /if (${actionsub.Equal[AANow]}) {
            /call ${actionsub} ${Me.AltAbility[${${listIterName}.Value}].ID} ${target_id}
            /varset result TRUE
        } else {
            /call ${actionsub} "${${listIterName}.Value}" ${target_id}
            /varset result TRUE
        }
        |- Move to the next slot
        /invoke ${${listIterName}.Advance}
    }
    
    |- If we're at the end of the map, loop us back to the beginning.
    /if (${${listIterName}.IsEnd}) {
        /invoke ${${listIterName}.Reset}
    }
/return ${result}
|-----------------------------------------------------------------
|-SUB: Ordered_Rotation_Follow - Loops through a detrimental rotation and casts
|- the first spell ready.
|- in: rotation_name -- Name of the rotation created
|- in: target_id -- target to cast against
|- in (optional - Default: TRUE): conditions -- any additional conditions to check
|- in (optional - Default: FALSE): donotstop -- If True, will cycle through the whole rotation between returning.
|-----------------------------------------------------------------
Sub Ordered_Rotation_Follow(string rotation_name, int target_id, string conditions, bool donotstop, string rotation_type, string FromWhere)
    /if (!${RotationSize[${rotation_name}]}) /return FALSE

	| Debug call stack
	CALLINGSUB
	CALLINGINDEX
	PUSHCALL

    CALLTRACE Enter from ${FromWhere} :: rotation_name ${rotation_name} :: target_id ${target_id} :: conditions ${Parse[1, ${conditions}]} :: donotstop ${donotstop} :: rotation_type ${rotation_type}

    /declare result bool local FALSE
    |- Reset our rotation as we want to go thorugh it from beginning to end
    /call Ordered_Rotation_Reset ${rotation_name}

    /if (${conditions.Length} == 0) /varset conditions TRUE


    |- TODO: Move this to a generic RGSubs set of function calls.
    |- First our Spell Rotation
    |- Cast the spell in our current rotation slot
    /declare listIterName string local ${rotation_name}_List_Iter
    |- The Det check is what makes this a DPS specific rotation. If we wanted to generalize it we could 
    |- pass the Det check as a condition if we wanted to arbitrarily single step through a map and perform
    |- an action on each element.
    |- Used to get our conditions for the spell -- variable name kept short
    |- for that reason    
    |- Many conditions throughout RG expect this variable to be named mi. Changing this variable will break
    |- a considerable number of rotation conditions. DO NOT CHANGE. Yes, I know this is fragile and could be done better. - Dr. Who
    /declare mi mapiterator local 
    /declare mi_type mapiterator local
    
    |- DEBUG Value: ${${listIterName}.Value} Is End? ${${listIterName}.IsEnd} Position: ${${rotation_name}_List.Index[${${listIterName}.Value}]}
    |- DEBUG Value: ${${listIterName}.Value} Is End? ${${listIterName}.IsEnd} Position: ${${rotation_name}_List.Index[${${listIterName}.Value}]}
    /declare actionsub string local
    /while ( !${${listIterName}.IsEnd} ) {
        /vardata mi ${rotation_name}_Map.Find[${${listIterName}.Value}]  
        /vardata mi_type ${rotation_name}_Type_Map.Find[${${listIterName}.Value}]
        /varset actionsub ${mi_type.Value}Now
        DEBUG ${${listIterName}.Value} --> (${mi.Value} && ${conditions} && ${NPC${mi_type.Value}Ready[${${listIterName}.Value},${target_id},${Bool[${rotation_type.Find[heal]}]}]}) --> ${If[(${mi.Value} && ${conditions} && ${NPC${mi_type.Value}Ready[${${listIterName}.Value},${target_id},${Bool[${rotation_type.Find[heal]}]}]}),TRUE,FALSE]} 
        |- FUTURE TODO: Instead of hard coding 'NPC' See if we can set it based on some information in the spell TLO
        |- If we're a heal rotation, let the NPC<ability>Ready function know.
        /if (${mi.Value} && ${conditions} && ${NPC${mi_type.Value}Ready[${${listIterName}.Value},${target_id},${Bool[${rotation_type.Find[heal]}]}]}) {
            |- Currently a workaround for AA's as AANow is the only function that
            |- takes an int insead of a string. This will require a class macro
            |- wide refactor to fix.
            /if (${actionsub.Equal[AANow]}) {
                |- DEBUG Ordered_Rotation_Follow: Casting ${${listIterName}.Value} ID: ${Me.AltAbility[${${listIterName}.Value}].ID 
                /call ${actionsub} ${Me.AltAbility[${${listIterName}.Value}].ID} ${target_id}
                /if (${CPUThrottle[SETTINGVAL]}) /delay ${CPUThrottle[SETTINGVAL]}
                /varset result TRUE
            } else {
                /call ${actionsub} "${${listIterName}.Value}" ${target_id}
                /if (${CPUThrottle[SETTINGVAL]}) /delay ${CPUThrottle[SETTINGVAL]}
                /varset result TRUE
            }
            /if (!${donotstop}) {
                |- We've found our spell to cast. Reset.
                /return ${result}
            }
        }   
        |- Move to the next slot
        /invoke ${${listIterName}.Advance}
    }
    DEBUG Rotation End: ${rotation_name}
/return ${result}
|----------------------------------------------------------------------------
|- SUB: ActionPrep -- Performs a number of common checks and actions used in multiple <action>Now subs
|----------------------------------------------------------------------------
Sub ActionPrep
    |- Make sure nothing stops us from casting the ability
    /if (!${Me.Standing}) {
        DEBUG Action Prep Standing up.
        /stand
        /delay 10 ${Me.Standing}
        /varset InMedState FALSE
    }

    /if (${Window[SpellBookWnd].Open}) /windowstate spellbookwnd close
/return

|----------------------------------------------------------------------------
|- SUB: SpellNow - Modified to use memspell replacement sub and return a cast result
|- Returns TRUE on a CAST_SUCCESS
|- Return FALSE on any other result
|- CastResult holds the outcome of the spell
|---------------------------------------------------------------------------- 
Sub SpellNow(string nextspell,int nextid)
    |- We're skipping Clerics because their hammer pet is a self spell but they need to target the mob.
    /if (${Spell[${nextspell}].TargetType.Equal[Self]} && ${Me.Class.ShortName.NotEqual[CLR]} && !${Spell[${nextspell}].HasSPA[33]}) /varset nextid ${Me.ID}
    |- Don't cast null spells
    /if (${nextspell.Equal[NULL]}) {
        /return FALSE
    }
    
    |- Check for enough mana -- just in case something has changed by this point...
    /if (${Me.CurrentMana}<${Spell[${nextspell}].Mana}) {
        /return FALSE
    }
    
    |- Check we actually have the spell -- Me.Book always needs to use RankName
    /if (!${Me.Book[${Spell[${nextspell}].RankName}]}) {
        /echo \arTRAGIC ERROR: Somehow I tried to cast a spell I didn't know! ${nextspell}
        /return FALSE
    }  
    
    |- Reset Cast Result
    /varset CastResult CAST_NULL
    /if (${Int[${Me.Gem[${Spell[${nextspell}].RankName}]}]}==0 ) {
        /delay 1s !${Me.Casting.ID}
        /call LoadSpellGem "${nextspell}" ${spellmisc}
        /if (!${XAssist.XTFullHaterCount} && ${Macro.Return}) {
            |- We can have a gem timer at 0 but still have the spell not ready for higher latency folks. Forcing
            |- this to wait until the spell is ready.
            /while (!${Me.SpellReady[${Spell[${nextspell}].RankName}]}) {  
                /if (${XAssist.XTFullHaterCount}) {
                    /echo I was interruped by combat while waiting to cast ${nextspell}.
                    /break
                }
                /if ( (${Spawn[pc =${FollowToonName[SETTINGVAL]}].Distance} > ${ChaseDistance[SETTINGVAL]}) && ${FollowToonName[SETTINGVAL].NotEqual[NULL]}) {
                    /echo I was interrupted by my chase target running out of range while waiting to cast ${nextspell}.
                    /call FollowToon
                    /break
                }
                /if (${DoMed[SETTINGVAL]}) /call AutoMed FROMHERE
                TRIGGERBIND
                /delay 1
            }   
        }
    }
    
    /if (${Me.SpellReady[${Spell[${nextspell}].RankName}]}) {    
        /if (${Target.ID}!=${nextid}) {
            /if (${Me.Combat} && ${Spawn[pc id ${nextid}].ID}) {
                /echo \awNOTICE:\ax Turning off autoattack to cast on a PC.
                /squelch /attack off
                /delay 2s !${Me.Combat}
            }
            /call SetTarget ${nextid}
            
            |- If we're combat casting we need to both have the same swimming status
            /if (${Target.FeetWet}!=${Me.FeetWet}) {
                /return FALSE
            }
        }
        /call ActionPrep
        
        /call HandleAcverbose "Casting Spell \ag ${nextspell} \ar =>> \ay ${Spawn[ID ${nextid}].Name} \ar <<="

        DEBUG Casting Spell \ag ${nextspell} \ar =>> \ay ${Spawn[ID ${nextid}].Name} \ar <<=
        /cast "${nextspell}"
        /delay 10 ${Window[CastingWindow].Open}
        GET_CAST_RESULT
        |- The while loop has been adjusted to account for stuck spell gems.
        /declare stuckgem_value int local 0
        |- Value is in seconds. It starts with the seconds for cast time then calculates a round trip time estimate based on a user's ping and then adds 1 as the conversion to Integer rounds down all values.
        /varcalc stuckgem_value ${Spell[${nextspell}].MyCastTime.Seconds}+${Int[${Math.Calc[(${EverQuest.Ping}*2/100)+1]}]}
        /declare stuckgems_timer timer local ${stuckgem_value}s
        /while (${Me.Casting.ID}) {
            |- A slightly more intensive delay loop 
            /if (${SpawnCount[npccorpse id ${Target.ID}]} || ${Target.ID} != ${nextid}) {
                |-/interrupt
                /stopcast
            }
            /delay 3 !${Me.Casting.ID}
            /if (${Me.Casting.ID} && !${Window[CastingWindow].Open} && !${stuckgems_timer}) {
                DEBUG : StuckGem Data::: ${Me.Casting.ID} - Casting Window: ${Window[CastingWindow].Open} - Assist Target ID: ${autotargetid}
                /alt act 511
                /delay 1
                /stopcast     
            }
            TRIGGERBIND
        }
        GET_CAST_RESULT
        |- added this varset to stagger spell casting for wizard enabling proper weaving of AA Nukes
        |- DEBUG SpellNow Cast Result: ${CastResult}
        /if (${CastResult.Equal[CAST_SUCCESS]}) {
            |- Only return TRUE on CAST_SUCCESS
            /return TRUE
        }
    } else {
		DEBUG SPELL NOT READY -- GemTimer: ${Me.GemTimer[${Spell[${nextspell}].RankName}]}
	}
    |- Return FALSE on any other failure -- now in alignment with the rest of *Now.
/return FALSE

|----------------------------------------------------------------------------
|- SUB: IsDisc -- Returns true is parameter is a Discipline and false if it is a Combat Ability or something else
|- For most situations Disciplines will be true if it is a skill, has a duration, and targets yourself. StacksWithDiscs will return True for certain abilities like Rest
|- that meet all prior criteria but will still stack.
|----------------------------------------------------------------------------
Sub IsDisc(string name) 
    /if (${Spell[${name}].IsSkill} && ${Spell[${name}].Duration} && !${Spell[${name}].StacksWithDiscs} && ${Spell[${name}].TargetType.Equal[Self]}) {
    /return TRUE
    }
/return FALSE

|----------------------------------------------------------------------------
|- SUB: DiscNow
|---------------------------------------------------------------------------- 
Sub DiscNow(string nextdisc)

    |- Don't cast null discs
    /if (${nextdisc.Equal[NULL]}) /return FALSE
    |- We're already casting someting
    /if (${Window[CastingWindow].Open}) /return FALSE
    |- Make sure we have enough endurance for the ability
    /if (${Me.CurrentEndurance} < ${Spell[${nextdisc}].EnduranceCost}) /return FALSE
    DEBUG Trying to cast ${nextdisc}
    /call ActionPrep
    
    |- If we're casting a discipline -- stop the current discipline if one is running
    /if (${IsDisc[${nextdisc}]}) {
        DEBUG Cancelling Disc for ${nextdisc} -- Active Disc: [${Me.ActiveDisc.Name}]
        /if (${Me.ActiveDisc.ID}) /stopdisc
        /delay 20 !${Me.ActiveDisc.ID}
    }

    
    /squelch /doability "${nextdisc}"
    /delay ${Math.Calc[${Spell[${nextdisc}].MyCastTime}/100]} (!${Me.CombatAbilityReady[${nextdisc}]} && !${Me.Casting.ID})
    
    |- If this is a timed disc -- wait for it to show up
    /if (${IsDisc[${nextdisc}]}) {
        /delay 20 ${Me.ActiveDisc.ID}
    }
    
    /call HandleAcverbose "\aw Casting \ag ${nextdisc}"
/return TRUE
|----------------------------------------------------------------------------
|- SUB: AANow
|---------------------------------------------------------------------------- 
Sub AANow(int nextaa,int aatargetid)
    |- DEBUG AANOW: Casting ${nextaa}
    /if ( ${Window[CastingWindow].Open} || ${Me.Casting.ID}) {
        /if (${Me.Class.ShortName.Equal[BRD]}) {
            /delay 3s !${Window[CastingWindow].Open}
            /delay 10
            /stopsong
        } else {
            DEBUG CANT CAST AA - Casting Window Open
            /return FALSE
        }
    }
    
    /declare spawn_target spawn local NULL
    /if (${aatargetid} && ${SpawnCount[id ${aatargetid}]}) {
        /squelch /vardata spawn_target Spawn[id ${aatargetid}]
    }
    
    /if ( ${spawn_target.FeetWet}!=${Me.FeetWet} && ${spawn_target.ID} ) {
        /return FALSE
    }
    DEBUG Trying to cast ${Me.AltAbility[${nextaa}].Name} on ${aatargetid}
    /call ActionPrep
    
    |- Make sure we select our target if we have a targeted AA
    /if (${Target.ID}!=${aatargetid} && ${spawn_target.ID}) {
        /if (${Me.Combat} && ${Spawn[pc id ${aatargetid}].ID}) {
            /echo \awNOTICE:\ax Turning off autoattack to cast on a PC.
            /squelch /attack off
            /delay 2s !${Me.Combat}
        }
        /call SetTarget ${aatargetid}
    }

    /alt act ${nextaa}
    /call HandleAcverbose "Casting AA \ao =>> \ag ${Me.AltAbility[${nextaa}].Name} \ao <<= \ax"
    /delay 5 !${RG_AAReady[${nextaa}]}
    /if (${Me.AltAbility[${nextaa}].Spell.MyCastTime}) {
        /while ( ${Me.Casting.ID} ) {
            /if ( ${Pull_State} == PULL_PULLING ) {
                /if ( ${DoPull[SETTINGVAL]} == PMODE_CHAIN && ${XAssist.XTFullHaterCount} < ${ChainCount[SETTINGVAL]} ) {
                    /echo \awPULL\ax ${Target.CleanName} . \aw CHAIN\ax ${XAssist.XTFullHaterCount} / ${ChainCount[SETTINGVAL]}
                    /delay 10
                } else /if ( ${XAssist.XTFullHaterCount} ) {
                    /echo \awPULL\ax ${Target.CleanName} ... \aw ABORT have\ax ${XAssist.XTFullHaterCount}
                    /stopcast
                    /break
                }
            }
            TRIGGERBIND
        }
        /delay ${Math.Calc[${Me.AltAbility[${nextaa}].Spell.MyCastTime.Float}+5]}s !${Me.Casting.ID}
    }
/return TRUE

|----------------------------------------------------------------------------
|- SUB: AbilityNow
|---------------------------------------------------------------------------- 
Sub AbilityNow(string nextability)
    /squelch /doability "${nextability}"
    /delay 8 !${Me.AbilityReady[${nextability}]}

    /call HandleAcverbose "Using Ability \ao =>> \ag ${nextability} \ao <<="
/return TRUE

|----------------------------------------------------------------------------
|- SUB: ItemNow
|---------------------------------------------------------------------------- 
Sub ItemNow(string nextitem)
    /if ( ${Window[CastingWindow].Open} || ${Me.Casting.ID}) {
        /if (${Me.Class.ShortName.Equal[BRD]}) {
            /delay 3s !${Window[CastingWindow].Open}
            /delay 10
            /stopsong
        } else {
            DEBUG CANT CAST Item - Casting Window Open
            /return FALSE
        }
    }

    |- Make sure the item is worth using - inspired by exspes007 (Do not remove Credit)
    /if (${Me.Buff[${Spell[${FindItem[=${nextitem}].Clicky.SpellID}].Name}].ID}) {
        /return FALSE
    }
    /if (${Me.Buff[${FindItem[=${nextitem}].Spell}].ID}) {
        /return FALSE
    }
    /if (${Me.Song[${FindItem[=${nextitem}].Spell}].ID}) {
        /return FALSE
    }
    
    /call ActionPrep
    |- Only use an item if it's ready  
    /if (${Me.ItemReady[${nextitem}]}) {
        /call HandleAcverbose "\aw Using Item \ag ${nextitem}"

        /useitem "${nextitem}"
        /delay 2
        
        |- Handle cast time delays - inspired by exspes007 (Do not remove Credit)
        /if (!${FindItem[=${nextitem}].CastTime}) {
            |- We have no cast time - slight 400ms delay so client can catch up
            /delay 4
            /if (${Cursor.ID}) /autoinv
            /return TRUE
        } else {
            |- We have a cast time
            |- Handle a bit of server lag and at this point we may have finished casting.
            /delay 8
            /delay ${Math.Calc[${FindItem[=${nextitem}].CastTime.Float}+5]}s !${Me.Casting.ID}
            /while (${Me.Casting.ID} || ${Window[CastingWindow].Open}) {
                |- Handle a bit more server lag 100ms at a time.
                /delay 5
                TRIGGERBIND
            }
            /if (${Cursor.ID}) /autoinv
            /return TRUE
        }
    }
    
/return TRUE

|----------------------------------------------------------------------------
|- SUB: CommandNow - Executes a slash-command
|----------------------------------------------------------------------------
Sub CommandNow(string nextcommand)
    /docommand ${nextcommand}
    
    /call HandleAcverbose "\aw Calling Command \ag ${nextcommand}"
/return TRUE

|**************************************************************************************|
|- Ability Ready API
|- NPC<Type>Ready checks are predominantly focused on combat-oriented on-bar abilities.
|- --> Can assume a Target is selected and correct.
|-
|- PC<Type>Ready checks are predominantly focused on downtime or off-bar abilities.
|- --> CANNOT assume a Target is selected.
|----------------------------------------------------------------------------
|- SUB: NPCCommandReady - Determiens if we're ready to execute a slash command
|----------------------------------------------------------------------------
Sub NPCCommandReady(string nextcommand)
    |- Used so general mq2 commands can be used in rotations
    |- Placeholder if there are universal conditions that need to be checked prior
    |- the execution of /docommand
/return TRUE
Sub PCCommandReady(string nextcommand)
/return TRUE

|----------------------------------------------------------------------------
|- SUB: NPCSpellReady - Makes common checks for detrimental/NPC Targeted spells.
|- This is predominantly combat focused in its checks so it performs a SpellReady.
|----------------------------------------------------------------------------
Sub NPCSpellReady(string nextspell, int spawn_id, bool is_healing_spell)
    /if (${Me.Stunned}) /return FALSE
    /if (${spawn_id} == 0) {
        DEBUG spawn_id = ${spawn_id} --> Using Target.ID = ${Target.ID}[${Target.CleanName}]
        /varset spawn_id ${Target.ID}
    }
    /if (${SpawnCount[id ${spawn_id}]}) {
        /declare tmp_spawn spawn local
        /squelch /vardata tmp_spawn Spawn[id ${spawn_id}]

        DEBUG [${nextspell}] SpellReady: ${Me.SpellReady[${nextspell}]} -- Mana ${Me.CurrentMana}>${Spell[${nextspell}].Mana}
        /if ( ${Me.SpellReady[${nextspell}]} && ${Me.CurrentMana}>${Spell[${nextspell}].Mana} ) {
            DEBUG ^----> LOS ${tmp_spawn.LineOfSight} -- Target ${tmp_spawn.CleanName} [${Target.ID}]
            /if ( !${Me.Moving} && !${Me.Casting.ID} && !${tmp_spawn.Type.Equal[Corpse]} && ${tmp_spawn.ID}  && !${tmp_spawn.Hovering}) {
                /if (${tmp_spawn.LineOfSight}) {
                    |- DEBUG RETURNING TRUE
                    /return TRUE
                } else {
                    |- We don't have line of sight, but it's a healing spell so we're good.
                    /if (${is_healing_spell}) {
                        DEBUG Spell Ready Check: Attempting to cast healing spell w/o LoS. Returning TRUE.
                        /return TRUE
                    }
                }
            }
        }
    }
/return FALSE
|----------------------------------------------------------------------------
|- SUB: PCSpellReady - Maks common checks for beneficial spells
|- Will NOT check that the spell is in your book -- assumes you're passing a spell variable.
|----------------------------------------------------------------------------  
Sub PCSpellReady(string nextspell)
    /if (${Me.Stunned}) /return FALSE
    |- We cannot include a SpellReady check here because it will return FALSE if the spell needs to be memmed in the case of a buff.
    /if ( ${Me.CurrentMana}>${Spell[${nextspell}].Mana} && !${Me.Casting.ID} && ${Me.Book[${Spell[${nextspell}].RankName}]} && !${Me.Moving}) {
        /return TRUE
    }
/return FALSE

|----------------------------------------------------------------------------
|- SUB: NPCAAReady - Makes common checks for detrimental spells
|----------------------------------------------------------------------------
Sub NPCAAReady(string nextaaa, int spawn_id, bool is_healing_aa)
    /if (${spawn_id} == 0) /varset spawn_id ${Target.ID}
    /if (${SpawnCount[id ${spawn_id}]}) {   
        /declare tmp_spawn spawn local
        /squelch /vardata tmp_spawn Spawn[id ${spawn_id}]
        |- DEBUG [${nextaaa}] AAReady ${RG_AAReady[${nextaaa}]} * Mana ${Me.CurrentMana}>${Me.AltAbility[${nextaaa}].Spell.Mana}
        /if ( ${RG_AAReady[${nextaaa}]} && (${Me.CurrentMana}>${Me.AltAbility[${nextaaa}].Spell.Mana} || ${Me.CurrentEndurance}>${Spell[${nextaaa}].EnduranceCost})) {
            |DEBUG [${nextaaa}] * Moving !${Me.Moving} * Casting !${Me.Casting.ID} * CorpseCheck !${Target.Type.Equal[Corpse]} * LOS ${Target.LineOfSight} * Target ${Target.ID} * Cast Status - ${Cast.Status}
            /if ( !${tmp_spawn.Type.Equal[Corpse]} && ${tmp_spawn.ID} && !${tmp_spawn.Hovering}) {
                |- Minor change to account for the bards special nature
                |- If I am not a bard make sure I am not moving, or casting
                /if ( ${Me.Class.ShortName.Equal[BRD]} || (!${Me.Moving} && !${Me.Casting.ID}) ) {
                    /if (${tmp_spawn.LineOfSight}) {
                        |- DEBUG RETURNING TRUE
                        /return TRUE
                    } else {
                        |- We don't have line of sight, but it's a healing spell so we're good.
                        /if (${is_healing_aa}) /return TRUE
                    }  
                }
            }
        }
    }
/return FALSE
|----------------------------------------------------------------------------
|- SUB: PCAAReady - Maks common checks for beneficial AA's
|----------------------------------------------------------------------------  
Sub PCAAReady(string nextaaa)
    /if ( ${RG_AAReady[${nextaaa}]} && (${Me.CurrentMana}>${Me.AltAbility[${nextaaa}].Spell.Mana} || ${Me.CurrentEndurance}>${Spell[${nextaaa}].EnduranceCost})) /return TRUE
/return FALSE

|----------------------------------------------------------------------------
|- SUB: NPCDiscReady - Makes common checks for detrimental spells
|----------------------------------------------------------------------------
Sub NPCDiscReady(string nextdisc, int spawn_id)
    /if (${spawn_id} == 0) /varset spawn_id ${Target.ID}
    /if (${SpawnCount[id ${spawn_id}]}) {   
        /declare tmp_spawn spawn local
        /squelch /vardata tmp_spawn Spawn[id ${spawn_id}]
        |- DEBUG [${nextdisc}] AAReady ${RG_AAReady[${nextdisc}]} * Mana ${Me.CurrentMana}>${Me.AltAbility[${nextdisc}].Spell.Mana}
        /if ( ${Me.CombatAbilityReady[${nextdisc}]} && ${Me.CurrentEndurance}>${Spell[${nextdisc}].EnduranceCost} ) {
            |DEBUG [${nextdisc}] * Moving !${Me.Moving} * Casting !${Me.Casting.ID} * CorpseCheck !${Target.Type.Equal[Corpse]} * LOS ${Target.LineOfSight} * Target ${Target.ID} * Cast Status - ${Cast.Status}
            /if ( !${tmp_spawn.Type.Equal[Corpse]} && ${tmp_spawn.LineOfSight} && ${tmp_spawn.ID} && !${tmp_spawn.Hovering}) {
                    |- DEBUG RETURNING TRUE
                    /return TRUE  
            }
        }
    }
/return FALSE
|----------------------------------------------------------------------------
|- SUB: PCDiscReady - Maks common checks for beneficial discs. Includes
|- a Disc Ready as disc's do not need to be memmed.
|----------------------------------------------------------------------------  
Sub PCDiscReady(string nextdisc)
    /if ( ${Me.CombatAbilityReady[${nextdisc}]} && ${Me.CurrentEndurance}>${Spell[${nextdisc}].EnduranceCost} ) /return TRUE
/return FALSE

|----------------------------------------------------------------------------
|- SUB: NPCAbilityReady - Makes common checks for detrimental Abilities
|----------------------------------------------------------------------------
Sub NPCAbilityReady(string nextability)
    /if ( ${Me.AbilityReady[${nextability}]} ) /return TRUE
/return FALSE
|----------------------------------------------------------------------------
|- SUB: PCAbilityReady - Makes common checks for downtime abilities
|----------------------------------------------------------------------------
Sub PCAbilityReady(string nextability)
    /call NPCAbilityReady "${nextability}"
/return ${Macro.Return}

|----------------------------------------------------------------------------
|- SUB: NPCItemReady - Makes common checks for detrimental item clickies
|----------------------------------------------------------------------------
Sub NPCItemReady(string nextitem,int spawn_id)
    /if (${Me.Casting.ID}) /return FALSE
    /if (${spawn_id} == 0) /varset spawn_id ${Target.ID}
    /if (${SpawnCount[id ${spawn_id}]}) {   
        /declare tmp_spawn spawn local
        /squelch /vardata tmp_spawn Spawn[id ${spawn_id}]
        /if ( ${Me.ItemReady[${nextitem}]} && ${tmp_spawn.LineOfSight} && ${FindItemCount[${nextitem}]} > 0) /return TRUE
    }
/return FALSE
|----------------------------------------------------------------------------
|- SUB: PCItemReady - Makes common checks for downtime items
|----------------------------------------------------------------------------
Sub PCItemReady(string nextitem)
    /if (${Me.Casting.ID}) /return FALSE
    /if ( ${Me.ItemReady[${nextitem}]} && ${FindItemCount[${nextitem}]} > 0) /return TRUE
/return ${Macro.Return}


|----------------------------------------------------------------------------
|- SUB: NPCSongReady - Makes common checks for detrimental item clickies
|----------------------------------------------------------------------------
Sub NPCSongReady(string nextsong)
    /if ( ${Me.CurrentMana}>=${Spell[${nextsong}].Mana} && !${Target.Type.Equal[Corpse]} && ${Me.SpellReady[${Spell[${nextsong}].RankName}]}) /return TRUE
/return FALSE
|----------------------------------------------------------------------------
|- SUB: PCSongReady - Makes common checks for downtime items
|----------------------------------------------------------------------------
Sub PCSongReady(string nextsong)
    /if ( ${Me.CurrentMana}>=${Spell[${nextsong}].Mana} && !${Target.Type.Equal[Corpse]} && ${Me.Book[${Spell[${nextsong}].RankName}]}) /return TRUE
/return FALSE


|----------------------------------------------------------------------------
|- SUB: SetTarget - Simple function that sets a target based on the input spawn_id
|---------------------------------------------------------------------------- 
Sub SetTarget(int spawn_id)
    /if (${DoAutoTarget[SETTINGVAL]}) {
        /if (${Target.ID}!=${spawn_id}) {
            /target id ${spawn_id}
            /delay 10 ${Target.ID}==${spawn_id}
        }
    }
/return

|----------------------------------------------------------------------------
|- SUB: ClearTarget - Clears our target
|---------------------------------------------------------------------------- 
Sub ClearTarget
    /if (${DoAutoTarget[SETTINGVAL]}) {
        /varset autotargetid 0
        /if (${Stick.Status.Equal[ON]}) /stick off
        /if (${burnnow}) /varset burnnow 0
        /squelch /target clear
    }
/return

|----------------------------------------------------------------------------
|- SUB: Kill PC Pet when it is on the Xtarget. A crude work around until we get a better fix. 
|---------------------------------------------------------------------------- 
Sub KillPCPet
    /echo in Kill Pet
	/declare problempet string local NULL
	/call SetTarget ${Me.XTarget[1].ID}
	/varset problempet ${Spawn[id ${Me.XTarget[1].ID}].Master.CleanName}
	/dexecute ${problempet} /pet leave
/return

|------------------------------------------------------------------------------------------
|- SUB: Check Epic - Checks for each Classes Epic and Sets The var. - now Universal - Not all macs use but all macs now set
|------------------------------------------------------------------------------------------
|** Sub CheckEpic
	/if (${Me.Class.ShortName.Equal[BER]}) { 	
		/if (${FindItem[=Vengeful Taelosian Blood Axe].ID}) {
			/varset Epic	Vengeful Taelosian Blood Axe	
			/varset DoEpic TRUE
		} else /if (${FindItem[=Raging Taelosian Alloy Axe].ID}) {
			/varset Epic	Raging Taelosian Alloy Axe
			/varset DoEpic TRUE
		}
	}
	/if (${Me.Class.ShortName.Equal[SHM]}) { 
		/if (${FindItem[=Crafted Talisman of Fates].ID}) {
			/varset Epic	Crafted Talisman of Fates	
			/varset DoEpic TRUE
		} else /if (${FindItem[=Blessed Spiritstaff of the Heyokah].ID}) {
			/varset Epic	Blessed Spiritstaff of the Heyokah
			/varset DoEpic TRUE
		}
	}
	/if (${Me.Class.ShortName.Equal[BRD]}) { 
		/if (${FindItem[=Prismatic Dragon Blade].ID}) {
			/varset Epic	Prismatic Dragon Blade	
			/varset DoEpic TRUE
		} else /if (${FindItem[=Blade of Vesagran].ID}) {
			/varset Epic	Blade of Vesagran
			/varset DoEpic TRUE
		}
	}
	/if (${Me.Class.ShortName.Equal[RNG]}) { 
		/if (${FindItem[=Aurora, the Heartwood Blade].ID}) {
			/varset Epic	Aurora, the Heartwood Blade	
			/varset DoEpic TRUE
		} else /if (${FindItem[=Heartwood Blade].ID}) {
			/varset Epic	Heartwood Blade
			/varset DoEpic TRUE
		}
	}
	/if (${Me.Class.ShortName.Equal[CLR]}) { 
		/if (${FindItem[Harmony of the Soul].ID}) {
			/varset Epic Harmony of the Soul
		} else /if (${FindItem[Aegis of Superior Divinity].ID}) {
			/varset Epic Aegis of Superior Divinity
		}
	}
	/if (${Me.Class.ShortName.Equal[BST]}) { 
		/if (${FindItem[=Spiritcaller Totem of the Feral].ID}) {
			/varset Epic Spiritcaller Totem of the Feral		
			/varset DoEpic TRUE
		} else /if (${FindItem[=Savage Lord's Totem].ID}) {
			/varset Epic Savage Lord's Totem
			/varset DoEpic TRUE
		}
	}
	/if (${Me.Class.ShortName.Equal[ENC]}) { 
		/if (${FindItem[=Staff of Eternal Eloquence].ID}) {
			/varset Epic Staff of Eternal Eloquence 		
			/varset DoEpic TRUE
		} else /if (${FindItem[=Oculus of Persuasion ].ID}) {
			/varset Epic Oculus of Persuasion 
			/varset DoEpic TRUE
		}
	}
	/if (${Me.Class.ShortName.Equal[DRU]}) { 
		/if (${FindItem[=Staff of Everliving Brambles].ID}) {
			/varset Epic Staff of Everliving Brambles 		
			/varset DoEpic TRUE
		} else /if (${FindItem[=Staff of Living Brambles].ID}) {
			/varset Epic Staff of Living Brambles
			/varset DoEpic TRUE
		}
	}
	/if (${Me.Class.ShortName.Equal[NEC]}) { 
		/if (${FindItem[=Deathwhisper].ID}) {
			/varset Epic Deathwhisper		
			/varset DoEpic TRUE
		} else /if (${FindItem[=Soulwhisper].ID}) {
			/varset Epic Soulwhisper
			/varset DoEpic TRUE
		}
	}
	/if (${Me.Class.ShortName.Equal[MAG]}) { 
		/if (${FindItem[=Focus of Primal Elements].ID}) {
			/varset Epic Focus of Primal Elements 		
			/varset DoEpic TRUE
		} else /if (${FindItem[=Staff of Elemental Essence].ID}) {
			/varset Epic Staff of Elemental Essence
			/varset DoEpic TRUE
		}
	}
	/if (${Me.Class.ShortName.Equal[MNK]}) { 
		/if (${FindItem[=Transcended Fistwraps of Immortality].ID}) {
			/varset Epic Transcended Fistwraps of Immortality
			/varset DoEpic TRUE
		} else /if (${FindItem[=Fistwraps of Celestial Discipline].ID}) {
			/varset Epic Fistwraps of Celestial Discipline
			/varset DoEpic TRUE
		}
	}
	/if (${Me.Class.ShortName.Equal[PAL]}) { 
		/if (${FindItem[=Nightbane, Sword of the Valiant].ID}) {
			/varset Epic Nightbane, Sword of the Valiant		
			/varset DoEpic TRUE
		} else /if (${FindItem[=Redemption].ID}) {
			/varset Epic Redemption
			/varset DoEpic TRUE
		}
	}
	/if (${Me.Class.ShortName.Equal[ROG]}) { 
		/if (${FindItem[=Nightshade, Blade of Entropy].ID}) {
			/varset Epic Nightshade, Blade of Entropy		
			/varset DoEpic TRUE
		} else /if (${FindItem[=Fatestealer].ID}) {
			/varset Epic Fatestealer
			/varset DoEpic TRUE
		}
	}
		/if (${Me.Class.ShortName.Equal[SHD]}) { 
		/if (${FindItem[=Innoruuk's Dark Blessing].ID}) {
			/varset Epic Innoruuk's Dark Blessing		
			/varset DoEpic TRUE
		} else /if (${FindItem[=Innoruuk's Voice].ID}) {
			/varset Epic Innoruuk's Voice 
			/varset DoEpic TRUE
		}
	}
		/if (${Me.Class.ShortName.Equal[WAR]}) { 
		/if (${FindItem[=Kreljnok's Sword of Eternal Power].ID}) {
			/varset Epic Kreljnok's Sword of Eternal Power		
			/varset DoEpic TRUE
		} else /if (${FindItem[=Champion's Sword of Eternal Power].ID}) {
			/varset Epic Champion's Sword of Eternal Power
			/varset DoEpic TRUE
		}
	}
		/if (${Me.Class.ShortName.Equal[WIZ]}) { 
		/if (${FindItem[=Staff of Phenomenal Power].ID}) {
			/varset Epic Staff of Phenomenal Power		
			/varset DoEpic TRUE
		} else /if (${FindItem[=Staff of Prismatic Power].ID}) {
			/varset Epic Staff of Prismatic Power
			/varset DoEpic TRUE
		}
	}

/return
**|
|------------------------------------------------------------------------------------------
|- SUB: LoadSpellGem - Replaces memspell sub
|------------------------------------------------------------------------------------------

Sub LoadSpellGem(string SpellToMem, int memgem)
    |- We want to pop out quickly if we're in combat or moving -- exept if we're trying to remember our saved spell in the miscspell slot
    /if ( ( ${XAssist.XTFullHaterCount} || ${AdvPath.Following} || ${MoveTo.Moving} || ${Me.Moving} || ${Navigation.Active} ) && ${SpellToMem.NotEqual[${miscspellremem}]} ) /return
    |- Need to use RankName with Me.Book and /memspell
    /varset SpellToMem ${Spell[${SpellToMem}].RankName}

    /if (${SpellToMem.Length} && ${SpellToMem.NotEqual[null]}) {
        /if (${Me.Book[${SpellToMem}]}) {
            /if (!${Me.Gem[${memgem}].ID} || ${Me.Gem[${memgem}].Name.NotEqual[${SpellToMem}]}) {
                /echo \ag Meming \aw ${SpellToMem} in \ag slot ${memgem}  
                /memspell ${memgem} "${SpellToMem}"
                |- Client settle delay to avoid getting stuck in loading spell gems.
                /delay 30 ${Window[SpellBookWnd].Open}
                TRIGGERBIND
                /varset MemTimer 50
                /while (!${IsMemorizing} && ${MemTimer}) {
                    TRIGGERBIND
                }

                |- We only care if this is our misc spell gem though.
                /while (!${Me.Gem[${memgem}].Name.Equal[${SpellToMem}]} && ${IsMemorizing}) {
                    /if (${XAssist.XTFullHaterCount}) {
                        /echo I was interruped by combat while waiting to memorize ${SpellToMem}.
                        /return FALSE
                    }
                    /if ( (${Spawn[pc =${FollowToonName[SETTINGVAL]}].Distance} > ${ChaseDistance[SETTINGVAL]}) && ${FollowToonName[SETTINGVAL].NotEqual[NULL]}) {
                        /echo I was interrupted by my chase target running out of range while waiting to memorize ${SpellToMem}.
                        /call FollowToon
                        /return FALSE
                    }
                    /if (!${Window[SpellBookWnd].Open}) {
                        /echo My Spellbook Window closed while I tried to memorize a spell.
                        /return FALSE
                    }
                    |- ${Window[SpellBookWnd].Child[SBW_Memorize_Gauge]} Contains if we're actively memorizing or not in its 'Last frame value' property.
                    |- This is currently not accessible from a TLO. If we delay until this has a value, once it hits 0 we've completed memorizing. If
                    |- it never gets a value, we haven't started.
                    TRIGGERBIND
                    /delay 1 ${Me.Gem[${memgem}].Name.Equal[${SpellToMem}]}    
                }
            }
            |- EDEBUG  ${SpellToMem} -- ${memgem} -- ${miscspellremem} -- ${Me.Gem[${memgem}].Name} -- (!${Int[${Me.Gem[${memgem}].Name.Length}]} || ${Me.Gem[${memgem}].Name.NotEqual[${SpellToMem}]})
        } else {
                /echo \aw Could Not find the spell ${SpellToMem} in your spell book.
        }
    } else {
        DEBUG Invalid SpellToMem ${SpellToMem} 
    }
/return ${Me.Gem[${memgem}].Name.Equal[${SpellToMem}]}

|------------------------------------------------------------------------------------------
|- SUB: MiscGemRemem - Checks to see if we should remem our miscspell after buffing. Used by all classes w/ spell buffs.
|------------------------------------------------------------------------------------------
Sub MiscGemRemem
    /if (!${Me.Gem[${spellmisc}].Name.Equal[${miscspellremem}]} && ${spellrememtimer}==0 && ${miscspellremem.NotEqual[NULL]}) {
        /call LoadSpellGem "${miscspellremem}" ${spellmisc}
        /varset spellrememtimer ${MiscRememDelay[SETTINGVAL]}s
	}
/return

|-------------------------------------------------------------------------------------
|- SUB: ClickModRoD - 
|-------------------------------------------------------------------------------------
Sub ClickModRoD
    /if (${FindItem[Modulation Shard].ID} && ${FindItem[Modulation Shard].Timer}==0 && ${Me.PctMana}<=${ModRodManaPct[SETTINGVAL]} && ${Me.PctHPs}>=60 ) /useitem "${FindItem[Modulation Shard]}"
    /if (${FindItem[Transvergence].ID} && ${FindItem[Transvergence].Timer}==0 && ${Me.PctMana}<=${ModRodManaPct[SETTINGVAL]} && ${Me.PctHPs}>=60 ) /useitem "${FindItem[Transvergence]}"
    /if (${FindItem[Modulation].ID} && ${FindItem[Modulation].Timer}==0 && ${Me.PctMana}<=${ModRodManaPct[SETTINGVAL]} && ${Me.PctHPs}>=60 ) /useitem "${FindItem[Modulation]}"
    /if (${FindItem[Modulating].ID} && ${FindItem[Modulating].Timer}==0 && ${Me.PctMana}<=${ModRodManaPct[SETTINGVAL]} && ${Me.PctHPs}>=60 ) /useitem "${FindItem[Modulating]}"
/return 
|-------------------------------------------------------------------------------------
|- SUB: PlayersInGroup - Checking for PC vs Merc
|-------------------------------------------------------------------------------------
Sub PlayersInGroup
    /declare i int local 0
    /declare gcnt int local 0
    /for i 1 to ${Group.Members}
        /if (${Group.Member[${i}].Type.Equal[PC]}) {
            /varcalc gcnt ${gcnt}+1
        }
    /next i
/return ${gcnt}

|-------------------------------------------------------------------------------------
|- SUB: Welcome Message
|-------------------------------------------------------------------------------------
Sub WelcomeMsg
    /if (${Defined[RGCustom_WinTitle]}) {
        /SetWinTitle ${RGCustom_WinTitle}
    } else {
        /SetWinTitle WINDOWTITLE
    }
    /echo \aw****************************
    /echo \awWelcome to \ag${MacroName}
    /echo \awVersion \ag${RGVersion}
    /echo \aw****************************
    /echo \aw use \ag /rg \aw for a list of commands
/return
|-------------------------------------------------------------------------------------
|- SUB: NavgationDelay
|-------------------------------------------------------------------------------------
Sub NavgationDelay
    :naving
    /delay 1s
    |-/echo Navigating...
    /if (${Navigation.Active}) /goto :naving
    |-/echo Navigation Finished!
/return 
|-------------------------------------------------------------------------------------
|- SUB: KillTarget
|-------------------------------------------------------------------------------------
Sub KillTarget(int spawn_id)
    /if (${spawn_id}) {
        /varset autotargetid ${spawn_id}
        /varset KillTargetID ${spawn_id}
    } else {
        /if (${assistid} == ${Me.ID}) {
            /varset autotargetid ${Target.ID}
            /varset KillTargetID ${Target.ID}
        } else {
            /varset autotargetid ${Me.GroupAssistTarget.ID}
            /varset KillTargetID ${Me.GroupAssistTarget.ID}
        }
    }
/return

|----------------------------------------------------------------------------
|- SUB: AllianceCheck - do a class alliance check
|- Returns True if alliance can be used
|- Returns FALSE if not
|---------------------------------------------------------------------------- 
Sub RGAllianceCheck(string shortname, int minimum)
    /declare i int local
    /declare classcount int local 0
    /for i 0 to ${Group}
        /if (${Group.Member[${i}].Class.ShortName.Equal[${shortname}]}) {
            /varcalc classcount ${classcount}+1
        }
    /next i
    /if (${classcount}>= ${minimum}) {
        /return TRUE
    } else {
        /return FALSE
    }
/return FALSE

|-------------------------------------------------------------------------------------
|- SUB: KillReset
|-------------------------------------------------------------------------------------
Sub KillReset
    /varset KillTargetID 0
    /varset autotargetid 0
/return

|-------------------------------------------------------------------------------------
|- SUB: SpellHasTriggers -- Returns true if spellname has triggers.
|-------------------------------------------------------------------------------------
Sub SpellHasTriggers(string spellname)
    /if (${Spell[${spellname}].HasSPA[470]} || ${Spell[${spellname}].HasSPA[374]} || ${Spell[${spellname}].HasSPA[340]}) {
        /return TRUE
    }
/return FALSE

|-----------------------------------------------------------------------------
|- Swap Code based off of Entropy -- written by @exspes, modified for RGMercs.
|- item_name: Name of item to pickup
|- to_slotname: Slotname to place item_name into
|- Return: TRUE on successful swap, FALSE on failure.
|- SUB: Exchange -- Exchanges an item in to_slotname with item_name
Sub Exchange(string item_name, string to_slotname)
    /declare int_packnum int local 0
    /declare int_slotnum int local 0
    /declare bool_inbag bool local FALSE

    /if (${to_slotname.Length} == 0) {
        /echo \ar ERROR \ax no slot name provided for Exchange ${item_name}
        /return FALSE
    }

    |- Find our item in our inventory
	/if (${InvSlot[pack${Select[${FindItem[=${item_name}].ItemSlot},23,24,25,26,27,28,29,30,31,32]}].Item.Container}) {
		/varset int_packnum ${Int[${Math.Calc[${FindItem[=${item_name}].ItemSlot}-22]}]}
		/varset int_slotnum ${Int[${Math.Calc[${FindItem[=${item_name}].ItemSlot2}+1]}]}
		/varset bool_inbag TRUE
	} else /if (${FindItem[=${item_name}].InvSlot}) {
		/varset int_slotnum ${FindItem[=${item_name}].InvSlot}
		/varset bool_inbag FALSE
	} else {
        |- We should never get here... item will be in bag or top slot
        EDEBUG ${item_name} not in inventory. Cannot Item_Swap!
        /return FALSE
	}

    |- Pickup our item
	/if (${bool_inbag}) {
		/squelch /nomodkey /shiftkey /itemnotify in pack${int_packnum} ${int_slotnum} leftmouseup
	} else {
        /squelch /nomodkey /shiftkey /itemnotify ${int_slotnum} leftmouseup
    }
	/delay 1s ${Cursor.ID}

    |- Swap item with equipment slot provided
	/nomodkey /shiftkey /itemnotify ${to_slotname} leftmouseup
	/delay 1s ${Cursor.ID}

	| Place the prior item back where it needs to go
	/if (${Cursor.ID}) {
        /if (${bool_inbag}) {
            /squelch /nomodkey /shiftkey /itemnotify in pack${int_packnum} ${int_slotnum} leftmouseup
        } else {
            /squelch /nomodkey /shiftkey /itemnotify ${int_slotnum} leftmouseup
        }
        /delay 1s !${Cursor.ID}
	}
/return TRUE

Sub TriggerBinds
    /doevents
    |- This functions sole duty is to trigger bind processing.
/return TRUE

|-------------------------------------------------------------------------------------
|- SUB: IsSpellTooPowerful -- Returns true if spellname is too powerful for target
|-------------------------------------------------------------------------------------
Sub IsSpellTooPowerful(string spellname, int target_level)
    /if (${Spell[${spellname}].HasSPA[0]}) /return FALSE
    /declare spelllvl int local ${Spell[${spellname}].Level}
    DEBUG Checking ${spellname} [${spelllvl}] against ${target_level}
    |- PC LVL 1 -> 45
    /if (${target_level} <= 45) {
        /if (${spelllvl} > 50) {
            DEBUG SpellTooPowerful: Spell > 50, Player <= 45
            /return TRUE
        }
    }
    |- PC LVL 46 -> 60
    /if (${target_level} <= 60) {
        /if (${spelllvl} > 65) {
            DEBUG SpellTooPowerful: Spell > 65, Player <= 60
            /return TRUE
        }
    }
    |- PC LVL 61 -> 65
    /if (${target_level} <= 65) {
        /if (${spelllvl} > 95) {
            DEBUG SpellTooPowerful: Spell > 95, Player <= 65 
            /return TRUE
        }
    }
/return FALSE


|-------------------------------------------------------------------------------------
|- SUB: GiveTo -- Hands item_name to spawn_id using an exact match.
|- spawn_id : ID of spawn to hand item to
|- item_name : Name of the item
|- amount : Number of items to give
|- is_pet : Is the spawn a pet?
|-------------------------------------------------------------------------------------
Sub GiveTo(int spawn_id, string item_name, int amount, bool is_pet)
    |- Target our intended recipient
    /if (${Target.ID} != ${spawn_id}) /call SetTarget ${spawn_id}
    
    |- Nav to our intended recipient -- probably should check for a mesh and use
    |- moveto as backup...
    |- Should also probably include a campradius check...
    /if (${Target.Distance} >= 25) {
        /echo GiveTo: Too far away from recipient... moving closer
        /nav id ${spawn_id} |log=off dist=10
        /delay 10s ${Navigation.Active}
    }
    
    /while (!${Cursor.ID}) {
        /shift /itemnotify "${item_name}" leftmouseup 
        /delay 20 ${Cursor.ID}
    }
    
    |- Click on our intended recipient and wait for trade window
    /while (${Cursor.ID}) {
        /if (${Cursor.ID} == ${FindItem[=${item_name}].ID}) {
            /nomodkey /click left target
        }
        /delay 15 !${Cursor.ID}
    }
    
    |- Click OK on trade window and wait for it to go away
    /if (${Spawn[id ${spawn_id}].Type.Equal[PC]}) {
        /delay 5s ${Window[TradeWnd].Open}
        /notify TradeWnd TRDW_Trade_Button leftmouseup
        /delay 5s !${Window[TradeWnd].Open}
    } else {
        /delay 5s ${Window[GiveWnd].Open}
        /notify GiveWnd GVW_Give_Button leftmouseup
        /delay 5s !${Window[GiveWnd].Open}
    }
    
    |- We're giving something to a pet. In this case if the pet gives it back,
    |- get rid of it.
    /if (${is_pet}) {
        |- Wait 2 seconds in case the pet wants to give us the item back.
        /delay 2s
        /if ( ${Cursor.ID} && (${Cursor.NoRent}) && (${Cursor.ID} == ${FindItem[=${item_name}].ID}) ) {
            /echo Pet Returned Item -- Getting rid of ${item_name}
            /destroy
            /delay 10 !${Cursor.ID}
        }
    }
/return TRUE


|-------------------------------------------------------------------------------------
|- SUB: GiveMoney -- Hands money to spawn_id.
|- spawn_id : ID of spawn to hand money to.
|- amount : number of coins to give.
|- money : pp, gp, sp, cp -- money of coin.
|-------------------------------------------------------------------------------------
Sub GiveMoney(int spawn_id, int amount, string money)
    /if (!${amount}) {
        /echo \arERROR:\ax Must provide an amount of money > 0
        /return FALSE
    }

    /if (${money.Equal[pp]}) {
        /if (${Me.Platinum} < ${amount}) /goto :AMOUNTERROR
    } else /if (${money.Equal[gp]}) {
        /if (${Me.Gold} < ${amount}) /goto :AMOUNTERROR
    } else /if (${money.Equal[sp]}) {
        /if (${Me.Silver} < ${amount}) /goto :AMOUNTERROR
    } else /if (${money.Equal[cp]}) {
        /if (${Me.Copper} < ${amount}) /goto :AMOUNTERROR
    } else {
        /echo \arERROR:\ax Must provide money type as pp, gp, sp, or cp
        /return FALSE
    }
    /call SetTarget ${spawn_id}
    /if (${Target.Distance} >= 25) {
        /echo GiveMoney: Too far away from recipient... moving closer
        /nav id ${spawn_id} |log=off dist=10
        /delay 10s ${Navigation.Active}
    }

    /declare money_idx int local ${Math.Calc[${Select[${money},pp,gp,sp,cp]}-1]}
    EDEBUG Picking ${amount} ${money} from window ${money_idx}

    /notify InventoryWindow IW_Money${money_idx} leftmouseup
    /delay 2s ${Window[QuantityWnd].Open}
    /notify QuantityWnd QTYW_Slider newvalue ${amount}
    /delay 2s ${Window[QuantityWnd].Child[QTYW_SliderInput].Text} == ${amount}
    /notify QuantityWnd QTYW_Accept_Button leftmouseup
    /delay 2s !${Window[QuantityWnd].Open}
    /click left target

    /if (${Spawn[id ${spawn_id}].Type.Equal[PC]}) {
        /delay 5s ${Window[TradeWnd].Open}
        /notify TradeWnd TRDW_Trade_Button leftmouseup
        /delay 5s !${Window[TradeWnd].Open}
    } else {
        /delay 5s ${Window[GiveWnd].Open}
        /notify GiveWnd GVW_Give_Button leftmouseup
        /delay 5s !${Window[GiveWnd].Open}
    }

    /return TRUE

    :AMOUNTERROR
        /echo \awNOTICE:\ax Not enough ${money}. Cannot Give Money.
        /return FALSE
/return

|-------------------------------------------------------------------------------------
|- SUB: IsSpawnOnXtarget -- If spawn_id is on XTarget list, return true, else false.
|-------------------------------------------------------------------------------------
Sub IsSpawnOnXtarget(int spawn_id)
    /declare i int local 0
    /for i 1 to ${Me.XTarget}
        /if (${Me.XTarget[${i}].ID} == ${spawn_id}) /return TRUE
    /next i
/return FALSE

|-------------------------------------------------------------------------------------
|- SUB: DoBuffCheck -- Return TRUE  if we should be buffing, FALSE otherwise.
|-------------------------------------------------------------------------------------
Sub DoBuffCheck
    /if (!${DoBuffs[SETTINGVAL]}) /return FALSE
    /if (${Me.Invis}) /return FALSE

    |- If we're in-combat or focusing on a kill target, don't buff.
    /if (${XAssist.XTFullHaterCount} || ${KillTargetID}) /return FALSE

    |- If we're moving and we're not a bard, don't buff.
    /if ( (${MoveTo.Moving} || ${Me.Moving} || ${AdvPath.Following} || ${Navigation.Active}) && ${Me.Class.ShortName.NotEqual[BRD]}) /return FALSE

    |- If we're a casting, only buff when we're above 30% Mana to keep some in reserve for combat.
    /if (${Select[${Me.Class.ShortName},RGCASTERS]}) {
        /if (${Me.PctMana} < 10) /return FALSE
    }
/return TRUE

|-------------------------------------------------------------------------------------
|- SUB: DoDPSCheck -- Commbat conditions to perform combat actions (both dps/debuf/others)
|- 
|- Return TRUE  if we should be combat actions, FALSE otherwise.
|-------------------------------------------------------------------------------------
Sub DoCombatActions
    /if (${BackOffFlag}) /return FALSE
    /if (!${autotargetid}) /return FALSE
    /if (!${XAssist.XTFullHaterCount}) /return FALSE
    |- We can't assume our target is our autotargetid for where this sub is used.
    /if (${Spawn[id ${autotargetid}].Distance} > ${AssistRange[SETTINGVAL]}) /return FALSE
/return TRUE

|-------------------------------------------------------------------------------------
|- SUB: DoDPSCheck -- Return TRUE  if we should be DPSing, FALSE otherwise.
|-------------------------------------------------------------------------------------
Sub DoDPSCheck
    /if (!${DoCombatActions[]}) /return FALSE
    |- We should have our target set at this point
    /if (${Target.ID} != ${autotargetid}) /return FALSE
    /if (${Target.PctHPs} > ${AutoAssistAt[SETTINGVAL]} && ${Me.ID} != ${assistid}) /return FALSE
/return TRUE

|-------------------------------------------------------------------------------------
|- SUB: DoDebuffCheck -- Return TRUE  if we should be DPSing, FALSE otherwise.
|-------------------------------------------------------------------------------------
Sub DoDebuffCheck
    /if (!${DoCombatActions[]}) /return FALSE
    |- We should have our target set at this point
    /if (${Target.ID} != ${autotargetid}) /return FALSE
    /if (${Target.PctHPs} > ${AutoDebuffAt[SETTINGVAL]}) /return FALSE
/return TRUE

|-------------------------------------------------------------------------------------
|- SUB: PriorityHealing -- Return TRUE  if we should be prioritizing healing, FALSE otherwise.
|-------------------------------------------------------------------------------------
Sub PriorityHealing
    |- If we're not healing we're never priority healing.
    /if (${IsHealing}) {
        /if (${AssistOutside[SETTINGVAL]}) {
            /if (${WorstHurtXT[${HealPoint_MaxPoint}]}) /return TRUE
        }
        /if (${WorstHurtGroup[${HealPoint_MaxPoint}]}) /return TRUE
    }
/return FALSE

|-------------------------------------------------------------------------------------
|- SUB: PriorityMezzing -- Return TRUE  if we should be prioritizing mezzing, FALSE otherwise.
|-------------------------------------------------------------------------------------
Sub PriorityMezzing
    /if (${IsMezzing}) {
        /if (${BlockForMez}) /return TRUE
    }
/return FALSE

|-------------------------------------------------------------------------------------
|- SUB: CorpseCheckAndDrag --Searches nearby for corpses to drag and drags them back to camp.
|-------------------------------------------------------------------------------------
Sub CorpseCheckAndDrag
    |- Stop dragging if we're close to camp
    /if (${ReturnToCamp[SETTINGVAL]}) {
        /if ( ${Math.Distance[${Me.Y},${Me.X}:${AutoCampY},${AutoCampX}]} <= 5 ) {
            /return FALSE
        }
    }

    /declare saved_tgt int local ${Target.ID}
    /declare corpse_count int local ${SpawnCount[pc corpse group radius 90]}
    /declare i int local 0
    EDEBUG Found ${corpse_count} corpses
    |- Check if we have a corpse in dragging radius -- limited to the group for now
    /if (${corpse_count}) {
        /for i 1 to ${corpse_count} 
            EDEBUG Dragging ${NearestSpawn[${i},pc corpse group radius 90].CleanName}
            /call SetTarget ${NearestSpawn[${i},pc corpse group radius 90].ID}
            /corpse
            /delay 1
        /next i
    }
    /call SetTarget ${saved_tgt}
/return TRUE

|-------------------------------------------------------------------------------------
|- SUB: ManhattanDist_Calc -- Returns the Manhattan Distance between two points.
|-------------------------------------------------------------------------------------
Sub ManhattanDist_Calc(int x1, int y1, int x2, int y2)
    /declare dist int 0
    /varcalc dist ${Math.Abs[${Math.Calc[${x1} - ${x2}]}]} + ${Math.Abs[${Math.Calc[${y1} - ${y2}]}]}
/return ${dist}

Sub ManhattanDist_MeSpawn(spawn tgt)
    /declare dist int 0
    /varcalc dist ${Math.Abs[${Math.Calc[${tgt.X} - ${Me.X}]}]} + ${Math.Abs[${Math.Calc[${tgt.Y} - ${Me.Y}]}]}
/return ${dist}

Sub ManhattanDist_MeGroup(int idx) 
    /declare dist int 0
    /varcalc dist ${Math.Abs[${Math.Calc[${Group.Member[${idx}].X} - ${Me.X}]}]} + ${Math.Abs[${Math.Calc[${Group.Member[${idx}].Y} - ${Me.Y}]}]}
/return ${dist}

|-------------------------------------------------------------------------------------
|- SUB: CheckTankClass
|-------------------------------------------------------------------------------------
Sub CheckTankClass(string toonname)
    /if (!${SpawnCount[pc ${toonname}]}) {
        /return FALSE
    }
    /if (${DanNet.Peers.Find[${toonname.Lower}]}) {
        /declare peername string local ${EverQuest.Server.Lower}_${toonname.Lower}
        /declare response string local

        |- Will return the value of the query sent
        DEBUG DNet Sending ${query} to ${peername}
        /dquery ${peername} -q "${query}" -o TankClass
    } 
 
/return

|----------------------------------------------------------------------------
|- SUB: BURNCHECK - Makes common checks for AutoBurn or Defers to, Burnsize for manual Burning.
|----------------------------------------------------------------------------
Sub BurnCheck string, assistid
/if  ( !${BurnAuto[SETTINGVAL]} && !${BurnSize[SETTINGVAL]} ) /return false
/if  ( !${BurnAuto[SETTINGVAL]} && ( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} ||  ${Target.Named} && ${BurnNamed[SETTINGVAL]}  || ${BurnAlways[SETTINGVAL]} && ${BurnAuto[SETTINGVAL]} ) ) /return TRUE 
/if  ( !${BurnAuto[SETTINGVAL]} && ${BurnSize[SETTINGVAL]} )  /return TRUE

/return false

| -------------------------------------------------------------------------------------------------
| Sub:AddFriendly
| -------------------------------------------------------------------------------------------------
Sub AddFriendly(int SpawnID)
    /if (!${SpawnID}) /return
    /if (!${IsFriendlyIDList.Find[|${SpawnID}|]}) {
        /varset IsFriendlyIDList ${IsFriendlyIDList}|${SpawnID}|
    }
/return

| -------------------------------------------------------------------------------------------------
| Sub:AddHostile
| -------------------------------------------------------------------------------------------------
Sub AddHostile(int SpawnID)
    /if (!${SpawnID}) /return
    /if (!${IsHostileIDList.Find[|${SpawnID}|]}) {
        /varset IsHostileIDList ${IsHostileIDList}|${SpawnID}|
    }
/return

| -------------------------------------------------------------------------------------------------
| Sub:AddMaybeHostile
| -------------------------------------------------------------------------------------------------
Sub AddMaybeHostile(int SpawnID)
    /if (!${SpawnID}) /return
    /if (!${IsMaybeHostileIDList.Find[|${SpawnID}|]}) {
        /varset IsMaybeHostileIDList ${IsMaybeHostileIDList}|${SpawnID}|
    }
/return

| -------------------------------------------------------------------------------------
| SUB: IsFriendly
|
| Looks at the spawnID given, or the target, and decides whether it may be a threat.
| -------------------------------------------------------------------------------------
Sub IsFriendly(int SpawnID, string FromWhere)
    | Debug call stack
    CALLINGSUB
    CALLINGINDEX

    CALLTRACE Enter from ${FromWhere} - Target Name:${Target.CleanName} ID:${Target.ID} Spawn Name: ${Spawn[id ${SpawnID}].CleanName} ID:${SpawnID}

    | Have we seen this id before?
    /if (${SpawnID} && ${IsMaybeHostileIDList.Find[|${SpawnID}|]}) /return MAY-BE-HOSTILE
    /if (${SpawnID} && ${IsFriendlyIDList.Find[|${SpawnID}|]}) /return FRIENDLY
    /if (!${SpawnID} && ${Target.ID} && ${IsFriendlyIDList.Find[|${Target.ID}|]}) /return FRIENDLY
    /if (${SpawnID} && !${Spawn[id ${SpawnID}].ID} || ${Spawn[id ${SpawnID}].Type.Equal[Corpse]}) /return DEAD-SPAWN

    /declare 	j 					int 	local	0
    /declare 	MobID 				int 	local 	0
    /declare 	MobMasterID 		int 	local 	0
    /declare	MobTarget			string	local

    CALLTRACE Validate Friendlies
    
    /if (${SpawnID}) {
        CALLTRACE SpawnID ${SpawnID} provided
        /varset MobTarget ${Spawn[id ${SpawnID}].DoTarget}
        /delay 5
        /varset MobID ${Spawn[id ${SpawnID}].ID}
        /varset MobMasterID ${Spawn[id ${SpawnID}].Master.ID}
        CALLTRACE MobID ${MobID} MobMasterID ${MobMasterID} (in case a pet)
    } else {
        CALLTRACE SpawnID not provided. Using Target
        /varset MobID ${Target.ID}
        /varset MobMasterID ${Target.Master.ID}
    }

    CALLTRACE MobID ${MobID} MobMasterID ${MobMasterID}
    
    /if (!${MobID}) /return NO-SPAWN
    /if (${Spawn[id ${MobID}].Type.Equal[CORPSE]}) /return DEAD-SPAWN

    CALLTRACE Spawn is present and not a corpse.

    |
    | Are we looking at anything that is me?
    |
    /if (${MobMasterID}==${Me.ID} || ${MobID}==${Me.ID} || ${MobID}==${Me.Mercenary.ID} || ${MobID}==${Pet.ID} || ${MobID}==${Me.Mount.ID}) {
        /call AddFriendly ${MobID}
        /call AddFriendly ${MobMasterID}
        /return FRIENDLY
    }
    
    CALLTRACE It's not me apparently
    
    /if (${Spawn[id ${MobID} group].ID}>0) {
        /call AddFriendly ${MobID}
        /call AddFriendly ${MobMasterID}
        /return FRIENDLY
    }
    
    CALLTRACE Not in the group apparently
    
    /if (${MobMasterID}) {
        /for j 1 to ${Group.Members}
            /if (${MobMasterID}==${Group.Member[${j}].ID} || ${MobMasterID}==${Group.Member[${j}].Master.ID} || ${MobMasterID}==${Group.Member[${j}].Pet.ID}) {
                /call AddFriendly ${MobID}
                /call AddFriendly ${MobMasterID}
                /return FRIENDLY
            }
        /next j
    }

    CALLTRACE Not a groupmember, pet, or whatever... returning MAY-BE-HOSTILE

    /call AddMaybeHostile ${MobID}
    /call AddMaybeHostile ${MobMasterID}

    CALLTRACE Leave :: MAY-BE-HOSTILE
/return MAY-BE-HOSTILE
