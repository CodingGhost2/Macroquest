|----------------------------------------------------------------------------
|- SUB: Pull_Init
|- ability: Name of ability/Item to use, e.g., "Throw Stone". Special pull types
|--     allow are:
|--     * pullpet -- Use pet based pulling
|--     * pullrange -- Use your bow/range attack to pull
|--     * pullmelee -- Use plain old melee attacks to pull
|- ability_type: Spell,Disc,Ability,AA,Item,Special -- Special isn't used but can denote the use of a special pull type.
|---------------------------------------------------------------------------- 
Sub Pull_Init
    |- Setting container
    /call RGLoadSetting Settings DoPull 0 Pull "0 = Pull Off [RESET to 0 ON MACRO START]. 1 = Pull On. 2 = Hunt On. 3 = Chain On. 4 = Farm On." 0 Pull_SetZoneID
    /call RGLoadSetting Pull PullRad 1000 Pull "Max X/Y radius to pull BASED ON MQ2NAV TRAVEL DISTANCE." 0 Pull_OnPullRadChange
    /call RGLoadSetting Pull PullFarmRad 200 Pull "Max X/Y radius to pull around our locs in farm mode BASED ON MQ2NAV TRAVEL DISTANCE." 1
    /call RGLoadSetting Pull PullZRad 100 Pull "Max Z radius to pull BASED ON MQ2NAV TRAVEL DISTANCE.." 1
    /call RGLoadSetting Pull PullArc 0 Pull "Pull Arc calculated +/- from where the macro is started. UNUSED" 1
    /call RGLoadSetting Pull PullMinLvl 1 Pull "Minimum level of mob to pull."
    /call RGLoadSetting Pull PullMaxLvl 120 Pull "Maximum level of mob to pull."
    /call RGLoadSetting Pull LvlAutoCalc 0 Pull "Set 0/1 to autocalcualte minimum and maximum pull levels between -4 and +4. (Requires Macro Restart)" 1
    /call RGLoadSetting Pull GroupWatch 0 Pull "0 - Group Watch off; 1 - Wait for SHM/DRU/CLR/Myself to med to 90% Mana/Health; 2- Wait for any caster/melee to med to 90% mana/end/health."
    /call RGLoadSetting Pull GroupWatchPct 80 Pull "% Resource (End/Mana/Health) to wait for when GroupWatch is on." 1
    /call RGLoadSetting Pull ChainPct 20  Pull "%HP the group's solo target should reach before chain pulling." 1
    /call RGLoadSetting Pull ChainCount 1 Pull "Won't chain pull if you have > than this many mobs in your hater list." 1
    /call RGLoadSetting Pull DoPetPull 0 Pull "Set 0/1 to use Pet as Primary Pull Method [DEFAULT: 0]" 0 "${Me.Class.ShortName}_PullSetup" 
    /call RGLoadSetting Pull PullDelay 0 Pull "Tenths of seconds to wait between pulls. Ex. To delay 5 seconds, set to 50." 1

    |- INI Loaded sets
    /declare PullIgnore_Set set outer
    /declare PullOnly_Set set outer
    /declare Waypoints_List list outer

    |- Used for FARM mode to keep track of what waypoint we're on.
    /declare Pull_FarmWPNum int outer 0

    |- Pull ability configuration items
    /declare Pull_Ability string outer NULL
    |- AA, Spell, Disc, Song, Item, or Ability
    /declare Pull_AbilityType string outer NULL
    |- Set our pull range based on our ability_type
    /declare Pull_AbilityRange int outer 0

    |- Don't spam pull notifications
    /declare Pull_MsgTimer timer outer 0

    /declare Pull_DelayTimer timer outer 0

    |- Keeps track of pull state (See Defines at the top of the file)
    /declare Pull_State int outer PULL_INIT
    
    |- LOS Toggle for Pulling w/ Nav (on/off)
    /declare PullLoS string outer on
    |- Use pet ghold if available
    /declare PetHold bool outer FALSE

    |- Signal that can be set via a bind to abort a pull.
    /declare AbortSignal bool outer FALSE
    
    |- Reset DoPull on Initialization if someone forgot to turn it off
    /call RGChangeSetting Settings DoPull PMODE_OFF

    |- Reset GroupWatch if we're not in a group
    /if (!${Group} && ${GroupWatch[SETTINGVAL]}) {
        /echo RGPULL: Not in group, turning off GroupWatch.
        /call RGChangeSetting Pull GroupWatch 0
    }

    |- Use Kissassist's file for PullIgnore and PullOnly. Used by both KA and MuleAssist.
    /declare Pull_INI string outer rgmercs\RGPull_Info.ini
    
    /call LoadPullIni
    
    /echo \ar PULL:*ALPHA* NOT TAKING ANY SUPPORT OR BUG REQUESTS ON PULL SYSTEM *ALPHA* \ax
    /echo \aw NOT READY FOR PRIME TIME \ax
    
/return TRUE

Sub Pull_SetAbility(string ability, string ability_type)
    /varset Pull_Ability ${ability}
    /varset Pull_AbilityType ${ability_type}
    |- PetHold toggle for pulling.
    /if (${Pull_AbilityType.Equal[Special]}) {
        /if (${Pull_Ability.Equal[pullpet]}) {
            |
            | This needs to be a variable
            |
            /varset Pull_AbilityRange 150
            /varset PullLoS off
            /if (${RG_CanUseAA[Companion's Discipline]}) /varset PetHold TRUE
        } else /if (${Pull_Ability.Equal[pullrange]}) {
            /varset Pull_AbilityRange ${Math.Calc[${Me.Inventory[ranged].Range}*PERCENTRANGE]}  
        } 
    } else {
        /if ( ${Select[${Pull_AbilityType},Spell,Disc,Ability]} ) {
            /varset Pull_AbilityRange ${Math.Calc[${Spell[${Pull_Ability}].Range}*PERCENTRANGE]}
        } else /if (${Pull_AbilityType.Equal[AA]}) {
            /varset Pull_AbilityRange ${Math.Calc[${Me.AltAbility[${Pull_Ability}].Spell.Range}*PERCENTRANGE]}  
            |- AANOW works w/ IDs instead of Names...
            /varset Pull_Ability ${AltAbility[${Pull_Ability}].ID}
        } else /if (${Pull_AbilityType.Equal[Item]}) {
            /echo Item Pulling Not Implemented
        } else /if (${Pull_AbilityType.Equal[Command]}) {
            /varset Pull_AbilityRange 5
        } else {
            /echo \arERROR: ${Pull_AbilityType} not valid pull type. Talk to your local Macro Dev.\ax
        }
    }
/return TRUE

#bind DoPull /singlepull
Sub Bind_DoPull
    |- Make sure to let Pull know we're pulling in this zone
    /varset ZoneID ${Zone.ID}
    /call Pull_DoPull PMODE_VANILLA 0 FROMHERE
/return
#bind DoHunt /singlehunt
Sub Bind_DoHunt
    |- Make sure to let Pull know we're pulling in this zone
    /varset ZoneID ${Zone.ID}
    /call Pull_DoPull PMODE_HUNT 0 FROMHERE
/return

#bind PullTarget /pulltarget
Sub Bind_PullTarget(int spawnid)
    /if (!${Target.ID} && !${spawnid}) {
        /echo \awNOTICE:\ax Can't Pull Target without Target
        /return FALSE
    }
    /if (!${spawnid}) /varset spawnid ${Target.ID}

    |- Make sure to let Pull know we're pulling in this zone
    /varset ZoneID ${Zone.ID}
    /call Pull_DoPull PMODE_VANILLA ${spawnid} FROMHERE
/return

#bind HuntTarget /hunttarget
Sub Bind_HuntTarget(int spawnid)
    /if (!${Target.ID} && !${spawnid}) {
        /echo \awNOTICE:\ax Can't Hunt Target without Target
        /return FALSE
    }
    /if (!${spawnid}) /varset spawnid ${Target.ID}
    |- Make sure to let Pull know we're pulling in this zone
    /varset ZoneID ${Zone.ID}
    /call Pull_DoPull PMODE_HUNT ${spawnid} FROMHERE
/return

#bind DelayPull /delaypull
Sub Bind_DelayPull(int delaytime)
    /if (!${delaytime}) {
        |- Defaulting to 5s
        /varset Pull_DelayTimer 50
    } else {
        /varset Pull_DelayTimer ${delaytime}
    }
    /echo \awNOTICE:\ax Will not pull until ${Math.Calc[${delaytime}/10]}s elapse from \agnow\ax.
/return

#bind AbortPull /abortpull
Sub Bind_AbortPull
    /varset AbortSignal TRUE
/return

|----------------------------------------------------------------------------
|- SUB: Pull_DoPull
|- mode: 1 = pull back to camp, 2 = hunter mode (don't return to camp), 3 = chain pull mode, 4 = farming mode
|- spawn_id: (OPTIONAL) specific spawn to pull
|---------------------------------------------------------------------------- 
Sub Pull_DoPull (int mode, int spawn_id, string FromWhere)
    /if (${Pull_DelayTimer}) {
        /call PullNotification "Pulls delayed for ${Math.Calc[${Pull_DelayTimer}/10]} seconds."
        /return FALSE
    } 

	| Debug call stack
	CALLINGSUB
	CALLINGINDEX
	PUSHCALL

    CALLTRACE Enter from ${FromWhere} :: mode ${mode} :: spawn_id ${spawn_id}

    /declare pull_id int local 0
    /declare abort_pull bool local FALSE

    |- Chain Pull specific variables
    /declare old_xtars string local EMPTY
    /declare new_xtars string local EMPTY
    
    |- Make sure we're in the zone where pulling was started
    /if (${ZoneID} != ${Zone.ID}) /return
    /call LoadPullIni

    |- This code should not be necessary, or, the code in rgevents is...
    /if (${LvlAutoCalc[SETTINGVAL]}) {
        /varset PullMinLvl[SETTINGVAL] ${Int[${Math.Calc[${Me.Level}-3]}]}
        /varset PullMaxLvl[SETTINGVAL] ${Int[${Math.Calc[${Me.Level}+3]}]}
    }

    |- GROUPWATCH and NAVINTERRUPT are the two states we can't reset. In the future it may be best to
    |- limit this to only the states we know should be transitionable to the IDLE state.
    /if (${Pull_State} != PULL_GROUPWATCH && ${Pull_State} != PULL_NAVINTERRUPT) /varset Pull_State PULL_IDLE

    |- Make sure the zone has a nav mesh, if not disable pulling and throw an error
    /if (!${Navigation.MeshLoaded}) {
        /echo \ar ERROR: There's no mesh for this zone. Can't pull. \ax
        /echo \ar Disabling Pulling. \ax
        /call RGChangeSetting Settings DoPull PMODE_OFF
        POPCALL
        /return
    }
    /if ( ${Pull_Ability.Equal[pullpet]} && !${Me.Pet.ID} ) {
        /call PullNotification "Need to create a new pet to throw as mob fodder."
        POPCALL
        /return
    }
    |- Check our personal conditions, if any are true, don't pull:
    |- || ${Me.Slowed.ID}
    |- Added health watch and a mana check so puller wouldnt just kill itself or be unable to cast if groupwatch was off. 
    /if ((${GroupWatch[SETTINGVAL]}==0 && ${Me.PctHPs}<${GroupWatchPct[SETTINGVAL]}) || ${Me.Song[=Restless Ice].ID} || ${Me.Song[=Restless Ice Infection].ID} || ${Me.Buff[Resurrection Sickness].ID} || ${Me.Snared.ID} || ${Me.Rooted.ID}  || ( ${Me.Poisoned.ID} && !${Me.Tashed.ID} ) || ${Me.Diseased.ID} || ${Me.Cursed.ID} || ${Me.Corrupted.ID} ) {
        /call PullNotification "Currently afflicated by a status (Low HPs, Snare, Rez Sicknes, or DoT) that is preventing me from pulling."
        POPCALL
        /return
    } 

    |- Check our Group Watch:
    /if (${GroupWatch[SETTINGVAL]} == 1) {
        |- Only look for CLR, DRU, SHM Mana > ${GroupWatchPct[SETTINGVAL]}%, Health > ${GroupWatchPct[SETTINGVAL]}%.
        /call CheckGroupForPull "CLR,DRU,SHM" 20 ${GroupWatchPct[SETTINGVAL]}
        /if (!${Macro.Return}) {
            /call PullNotification "Waiting for CLR, DRU, SHM, or ${Me.CleanName} to med to ${GroupWatchPct[SETTINGVAL]}% Mana or heal to ${GroupWatchPct[SETTINGVAL]}% Health"
            /varset Pull_State PULL_GROUPWATCH
            POPCALL
            /return
        }
    } else /if (${GroupWatch[SETTINGVAL]} == 2) {
        |- Look for all members Mana/End > ${GroupWatchPct[SETTINGVAL]}%, Health > ${GroupWatchPct[SETTINGVAL]}%
        /call CheckGroupForPull "BRD,BST,BER,CLR,DRU,ENC,MAG,MNK,NEC,PAL,RNG,ROG,SHD,SHM,WAR,WIZ" 20 ${GroupWatchPct[SETTINGVAL]}
        /if (!${Macro.Return}) {
            /call PullNotification "Waiting for group mate or ${Me.CleanName} to med to ${GroupWatchPct[SETTINGVAL]}% Mana/Endurance or heal to ${GroupWatchPct[SETTINGVAL]}% Health"
            /varset Pull_State PULL_GROUPWATCH
            POPCALL
            /return
        }
    }
    |- We're ready to pull, but first, check if we're in farm mode and if we were interrupted
    /if (${mode} == PMODE_FARM) {
        /if ( ${Mercenary.State.Equal[DEAD]} ) {
            /if (${Window[MMGW_ManageWnd].Child[MMGW_SuspendButton].Enabled}) {
                /notify MMGW_ManageWnd MMGW_SuspendButton LeftMouseUp
            } else {
                POPCALL
                /return
            }
        }
        /if (${Waypoints_List.Count} == 0 ) {
            /echo You have no waypoints configured for this zone. \ar Disabling Pulling. \ax
            /call RGChangeSetting Settings DoPull PMODE_OFF
            POPCALL
            /return
        }
        
        /if (${Pull_State} == PULL_NAVINTERRUPT) {
            |- We're not ready to pull yet as we haven't made it to our waypoint. Keep navigating if we don't have a full inventory
            /if (${Me.FreeInventory} == 0 ) /call FarmFullInvActions
            
            /if (${SubDefined[${Zone.ShortName}_PreNav_${Pull_FarmWPNum}]}) /call ${Zone.ShortName}_PreNav_${Pull_FarmWPNum}

            /call NavToWaypoint ${GetWaypoint[${Pull_FarmWPNum}]}
            
            /if (!${Macro.Return}) {
                |- We've been interrupted by a mob, return after setting state.
                /varset Pull_State PULL_NAVINTERRUPT
                POPCALL
                /return
            } else {
                /if (${SubDefined[${Zone.ShortName}_PostNav_${Pull_FarmWPNum}]}) /call ${Zone.ShortName}_PostNav_${Pull_FarmWPNum}
                |- We're back in our IDLE state.
                /varset Pull_State PULL_IDLE
            }

           
        }
        
        |- We're not in an interrupted state if we make it this far -- so
        |- now make sure we have free inventory or not.
        /if (${Me.FreeInventory} == 0 ) /call FarmFullInvActions
    } 

    |- Find our target
    /if (${spawn_id} > 0) {
        DEBUG Pulling based on agument
        /varset pull_id ${spawn_id}
    } else {
        DEBUG Finding Pull Target
        /if (${mode} == PMODE_FARM) {
            CALLTRACE FindTarget :: Mode: ${mode} Farm :: pullradius ${PullFarmRad[SETTINGVAL]} pullzradius ${PullZRad[SETTINGVAL]} lowlvl ${PullMinLvl[SETTINGVAL]} highlvl ${PullMaxLvl[SETTINGVAL]} use_only_nav 1 arc 0 xyz ${GetWaypoint[${Pull_FarmWPNum}]}
            /call Pull_FindTarget ${PullFarmRad[SETTINGVAL]} ${PullZRad[SETTINGVAL]} ${PullMinLvl[SETTINGVAL]} ${PullMaxLvl[SETTINGVAL]} 1 0 "${GetWaypoint[${Pull_FarmWPNum}]}" FROMHERE
        } else {
            CALLTRACE FindTarget :: Mode: ${mode} :: pullradius ${PullRad[SETTINGVAL]} pullzradius ${PullZRad[SETTINGVAL]} lowlvl ${PullMinLvl[SETTINGVAL]} highlvl ${PullMaxLvl[SETTINGVAL]} use_only_nav 1 arc 0 xyz NA
            /call Pull_FindTarget ${PullRad[SETTINGVAL]} ${PullZRad[SETTINGVAL]} ${PullMinLvl[SETTINGVAL]} ${PullMaxLvl[SETTINGVAL]} 1 0 "" FROMHERE
        }
        /varset pull_id ${Macro.Return}
    }
    DEBUG Pull_FindTarget returned ${Spawn[id ${pull_id}].CleanName}[${pull_id}]
    /if (${pull_id} == 0) {
        /if (${mode} == PMODE_FARM) {
            |- Increment our waypoint
            
            /if (${Pull_FarmWPNum} >= ${Waypoints_List.Count}) {
                |- We've reached the end of our waypoints list, go back to the beginning!
                /varset Pull_FarmWPNum 0
            }
            |- Here we want to nav to our current waypoint. If we engage an enemy while 
            |- we are currently traveling to our waypoint, we need to set our state to
            |- PULL_NAVINTERRUPT so that when Pulling re-engages after combat, we continue
            |- to travel to our next waypoint.
            /if (${SubDefined[${Zone.ShortName}_PreNav_${Pull_FarmWPNum}]}) /call ${Zone.ShortName}_PreNav_${Pull_FarmWPNum}

            /call NavToWaypoint ${GetWaypoint[${Pull_FarmWPNum}]}
            /if (!${Macro.Return}) {
                |- We've been interrupted by a mob, return.
                /varset Pull_State PULL_NAVINTERRUPT
                POPCALL
                /return
            } else {

                /if (${SubDefined[${Zone.ShortName}_AtWaypoint_${Pull_FarmWPNum}]}) /call ${Zone.ShortName}_AtWaypoint_${Pull_FarmWPNum}
                /varset Pull_FarmWPNum ${Math.Calc[${Pull_FarmWPNum}+1]}
            }
        } else {
            /call PullNotification "Couldn't find a target to pull. Aborting."
        }
        POPCALL
        /return
    }
    
    /call SetTarget ${pull_id}
     
    |- Save our current location as camp if we haven't done /rg camphere
    /if (${ReturnToCamp[SETTINGVAL]}) {
        /declare me_x int local ${AutoCampX}
        /declare me_y int local ${AutoCampY}
        /declare me_z int local ${AutoCampZ}

    } else {
        /declare me_x int local ${Me.X}
        /declare me_y int local ${Me.Y}
        /declare me_z int local ${Me.Z}
    }
    
    |- Nav to within range of our target or closer if we need LOS.
    /if (${Me.Sitting}) {
        /varset InMedState FALSE
        /stand
    } 
    /varset old_xtars ${GetXTHaterList[]}
    /nav ID ${pull_id} distance=${Pull_AbilityRange} lineofsight=${PullLoS} log=off
    /varset Pull_State PULL_NAVTO
    /delay 1s ${Navigation.Active}
    /while (${Navigation.Active}) {
        /if (${mode} == PMODE_CHAIN) {
            /varset new_xtars ${GetXTHaterList[]}
            /if (${XAssist.XTFullHaterCount} > ${ChainCount[SETTINGVAL]}) {
                /varset abort_pull TRUE
                /echo \awNOTICE:\ax Gained aggro -- aborting chain pull!
                /break
            }
            /if (${DiffXTHaterList[${old_xtars},${new_xtars}]}) {
                /varset abort_pull TRUE
                /echo \awNOTICE:\ax XTarget List Changed -- abborting chain pull!
                /break
            }
            /varset old_xtars ${new_xtars}
        } else {
            /if (${XAssist.XTFullHaterCount}) {
                /varset abort_pull TRUE
                /echo \awNOTICE:\ax Gained aggro -- aborting pull!
                /break
            }
        }
        /if (${CheckForAbort[${pull_id}]}) {
            /varset abort_pull TRUE
            /break
        }
        TRIGGERBIND
        /delay 1
    }
    /delay 2s !${Me.Moving}
    /if (${SubDefined[${Me.Class.ShortName}_PrePullAtTarget]}) /call ${Me.Class.ShortName}_PrePullAtTarget ${pull_id}
    /call SetTarget ${pull_id}

    /if (${SafeTargeting[SETTINGVAL]}) {
        |- Hard coding 500 units as our radius as it's probably twice our effective spell range.
        /if (${IsSpawnFightingStranger[${pull_id},500]}) {
            /echo ${Spawn[id ${pull_id}].CleanName} [${pull_id}] already fighting someone else [${Me.TargetOfTarget.CleanName}]. Aborting.
            /varset abort_pull TRUE
        }
    }
    /if (!${abort_pull}) {
        /echo Pulling ${Spawn[id ${pull_id}].CleanName} [${pull_id}]
        /varset Pull_State PULL_PULLING

        |- Our delays need to know when we've succeeded in pull so we can return to camp.
        |- This success condition is slightly different for chain pulling so we're setting
        |- a shortcut to it here to avoid a bunch of  duplicate typing for each of the special
        |- pull cases.
        /declare success_cond string local
        /if (${mode} == PMODE_CHAIN) {
            /varset success_cond ${Parse[0,(${XAssist.XTFullHaterCount} > ${ChainCount[SETTINGVAL]})]}
        } else {
            /varset success_cond ${Parse[0,(${XAssist.XTFullHaterCount})]}
        }
        |- Pet pulling speical pull
        /if (${Pull_Ability.Equal[pullpet]}) { 
            /call PetAttack
            /while (!${success_cond}) {
                /varset new_xtars ${GetXTHaterList[]}
                /call PetAttack
                TRIGGERBIND
                /if (${mode} == PMODE_CHAIN && ${DiffXTHaterList[${old_xtars},${new_xtars}]}) /break
                /varset old_xtars ${new_xtars}
                /if (${CheckForAbort[${pull_id}]}) /break
                /delay 1
            }

            /if (${PetHold}) /squelch /pet ghold on
            /squelch /pet back off   
            /delay 1s (${Me.Pet.PlayerState} == 0)
            /squelch /pet follow
        } else /if ( ${Pull_Ability.Equal[pullrange]} ) {
            |- Make sure we're looking straight ahead at our mob and delay
            |- until we're facing them.
            /look 0
            /delay 3s ${Me.Heading.ShortName.Equal[${Target.HeadingTo}]}

            |- We will continue to fire arrows until we aggro our target
            /while (!${success_cond} && !${SpawnCount[npccorpse id ${pull_id}]} && ${SpawnCount[id ${pull_id}]}) {
                /varset new_xtars ${GetXTHaterList[]}
                /ranged ${pull_id}
                TRIGGERBIND
                /if (${mode} == PMODE_CHAIN && ${DiffXTHaterList[${old_xtars},${new_xtars}]}) /break
                /varset old_xtars ${new_xtars}
                /if (${CheckForAbort[${pull_id}]}) /break
                /delay 1
            }
        } else {
            |- Using an AA, Item, Spell, Disc, or Ability
            /delay 5 !${Me.Moving}
            /while (!${success_cond}) {
                /varset new_xtars ${GetXTHaterList[]}
                DEBUG newxtars now ${new_xtars} ---- ${old_xtars}
                /target ID ${pull_id}
                /if (${PC${Pull_AbilityType}Ready[${Pull_Ability}]}) {
                    /call ${Pull_AbilityType}Now "${Pull_Ability}" ${pull_id}
                } else {
                    /if (!${Target.LineOfSight}) {
                        /call NavInCombat ${pull_id} ${Math.Calc[${Target.Distance}*0.80]} FALSE FROMHERE
                    }
                }
                GET_CAST_RESULT
                TRIGGERBIND
                /if (${mode} == PMODE_CHAIN && ${DiffXTHaterList[${old_xtars},${new_xtars}]}) /break
                /varset old_xtars ${new_xtars}
                DEBUG oldxtars now ${old_xtars} -- ${new_xtars}
                /if (${CheckForAbort[${pull_id}]}) /break
                /delay 1
            }
        }
        /echo pew pew
        |- Check for range too close event.
        TRIGGERBIND
    } else {
        |- We're aborting!
        /nav stop log=off
        /delay 2s !${Navigation.Active}
    }
    
    /if (${mode} == PMODE_VANILLA || ${mode} == PMODE_CHAIN) {
        |- Nav back to camp
        /varset Pull_State PULL_RETURNFROM
        /nav locyxz ${me_y} ${me_x} ${me_z} log=off
        /delay 5s ${Navigation.Active}
        /while (${Navigation.Active}) {
            /if (${Me.State.Equal[FEIGN]} || ${Me.Sitting}) {
                DEBUG Standing to Engage Target
                /varset InMedState FALSE
                /stand
                /nav locyxz ${me_y} ${me_x} ${me_z} log=off
                /delay 5s ${Navigation.Active}
            }
            TRIGGERBIND
            /delay 1 !${Navigation.Active}
        }
        /face id ${pull_id}
        /if (${SubDefined[${Me.Class.ShortName}_PostPullAtCamp]}) /call ${Me.Class.ShortName}_PostPullAtCamp ${pull_id}
    }
    
    |- We may want to turn ghold off here if it was set.
    POPCALL
/return

|----------------------------------------------------------------------------
|- SUB: CheckForAbort -- Basic function that checks for uncommon abort conditions
|- Returns TRUE if we need to abort the pull.
|---------------------------------------------------------------------------- 
Sub CheckForAbort(int pull_id)
    |- Abort signal received, catch it, reset it, and return
    /if (${AbortSignal}) {
        DEBUG AbortSignal received, aborting pull.
        /echo \awNOTICE:\ax Received Abort Signal! Heading home!
        /varset AbortSignal FALSE
        /return TRUE
    }
    |- Mob warped
    /if ( (${Spawn[id ${pull_id}].Distance} > ${PullRad[SETTINGVAL]}) || (${DoPull[SETTINGVAL]} == PMODE_FARM && ${Spawn[id ${pull_id}].Distance} > ${PullFarmRad[SETTINGVAL]}) ) {
        DEBUG Spawn warped, aborting pull
        /echo \awNOTICE:\ax Spawn warped. Aborting Pull.
        /return TRUE
    }
    |- Mob is fighting a stranger
    /if (${SafeTargeting[SETTINGVAL]}) {
        /if (${IsSpawnFightingStranger[${pull_id},500]}) {
            DEBUG Spawn fighting stranger, aborting pull.
            /echo \awNOTICE:\ax Spawn fighting stranger. Aborting Pull.
            /return TRUE
        }
    }
/return FALSE

|----------------------------------------------------------------------------
|- SUB: Pull_FindTarget
|---------------------------------------------------------------------------- 
Sub Pull_FindTarget(int pullradius, int pullzradius, int lowlvl, int highlvl, bool use_only_nav, int arc, string xyz, string FromWhere)
    |- /varset Pull_State PULL_SEARCHING
      
	| Debug call stack
	CALLINGSUB
	CALLINGINDEX
	PUSHCALL

    CALLTRACE Enter from ${FromWhere}

    /declare pull_id int local 0
    /if (${xyz.Length} > 0) {
        /declare pullsearch string local "npc radius ${pullradius} targetable zradius ${pullzradius} range ${lowlvl} ${highlvl} playerstate 0 loc ${xyz.Arg[1,|]} ${xyz.Arg[2,|]} ${xyz.Arg[3,|]}"
    } else {
        /declare pullsearch string local "npc radius ${pullradius} targetable zradius ${pullzradius} range ${lowlvl} ${highlvl} playerstate 0"
    }
    /declare pullcount int local ${SpawnCount[${pullsearch}]}
    
    CALLTRACE pullcount ${pullcount} :: pullsearch ${pullsearch}

    /declare spawn_Map map local
   
    /varset Pull_State PULL_SEARCHING
    /if ( ${pullcount} ) {
        /declare i int local 0
        /declare tmp_distance int local 0
        /declare spawn_tmp spawn local NULL
        /for i 1 to ${pullcount}
            /squelch /vardata spawn_tmp NearestSpawn[${i},${pullsearch}]

            /if (${DoPull[SETTINGVAL]} == PMODE_CHAIN) {
                /if (${IsSpawnOnXtarget[${spawn_tmp.ID}]}) {
                    CALLTRACE ${spawn_tmp.CleanName} [${spawn_tmp.ID}] Already on XTarget. Skipping.
                    DEBUG ${spawn_tmp.CleanName} [${spawn_tmp.ID}] Already on XTarget. Skipping.
                    /continue
                }
            }
            | If no navpath, we could get the xyz coords instead.
            CALLTRACE Nav path exists? ${Navigation.PathExists[id ${spawn_tmp.ID}]}
            /if (${Navigation.PathExists[id ${spawn_tmp.ID}]}) {
                /varset tmp_distance ${Navigation.PathLength[id ${spawn_tmp.ID}]}
                | Should this be using distance3d rather than pullradius? I thought if the pathlength was extremely small or neg, it means no path exists.
                | Adding 100000 wouldn't do a thing but confuse the puller in that case, i think?
                CALLTRACE tmp_distance ${Navigation.PathLength[id ${spawn_tmp.ID}]} :: pullradius :: ${pullradius}
                /if ( ${tmp_distance} < ${pullradius}) {
                    |- Adding 100000 takes advantage of map's inherent lexigraphical sorting to give us shortest distance
                    /varcalc tmp_distance ${tmp_distance} + 100000
                    CALLTRACE Potential Pull ${spawn_tmp.Name} [${spawn_tmp.ID}] --> Distance ${Navigation.PathLength[id ${spawn_tmp.ID}]}
                    DEBUG Potential Pull ${spawn_tmp.Name} --> Distance ${Navigation.PathLength[id ${spawn_tmp.ID}]}
                    |- PullOnly mode if we have only specific targets for this zone.
                    /if (${PullOnly_Set.Count} > 0) {
                        /if (${PullOnly_Set.Contains[${spawn_tmp.CleanName}]}) {
                            CALLTRACE PullOnly Adding To list: ${spawn_tmp.Name} [${spawn_tmp.ID}] --> Distance ${Navigation.PathLength[id ${spawn_tmp.ID}]}
                            DEBUG PullOnly Adding To list: ${spawn_tmp.Name} --> Distance ${Navigation.PathLength[id ${spawn_tmp.ID}]}
                            /invoke ${spawn_Map.Add[${tmp_distance},${spawn_tmp.ID}]}
                        }
                    } else {
                        |- We don't have a white list for the zone so fall back on blacklist mode
                        /if ( !${PullIgnore_Set.Contains[${spawn_tmp.CleanName}]} ) {
                            CALLTRACE Adding to list: ${spawn_tmp.Name} [${spawn_tmp.ID}] --> Distance ${Navigation.PathLength[id ${spawn_tmp.ID}]}
                            DEBUG Adding to list: ${spawn_tmp.Name} --> Distance ${Navigation.PathLength[id ${spawn_tmp.ID}]}
                            /invoke ${spawn_Map.Add[${tmp_distance},${spawn_tmp.ID}]}
                        } else {
                            CALLTRACE ${spawn_tmp.Name} [${spawn_tmp.ID}] on the ignore list.
                            DEBUG ${spawn_tmp.Name} on the ignore list.
                        }
                    }
                }
            }
        /next i      
    }
    | Can mi.Value be set with an invalid mob and fall through?
    /declare mi mapiterator local
    /vardata mi spawn_Map.First.Clone
    CALLTRACE Pulling ${Spawn[id ${mi.Value}].Name} [${mi.Value}] --> Distance ${Navigation.PathLength[id ${mi.Value}]}
    DEBUG Pulling ${mi.Value}
/return ${mi.Value}

|- Sub: Pull_SetZoneID
|- Call back to configure ZoneID fo when pulling is started ot make sure pulling only occurs in the
|- zone in which it was started. ZoneID also leveraged for AutoCamping.
Sub Pull_SetZoneID
    /if (${DoPull[SETTINGVAL]} > 0) {
        /varset ZoneID ${Zone.ID}
    }
/return

|- Sub: Pull_OnPullRadChange
|- Automaticlly changes the M
Sub Pull_OnPullRadChange
    /mapfilter spellradius ${PullRad[SETTINGVAL]}
/return

|- Sub: Pull_ChainReady
|- Returns true if we're ready to chain pull, false otherwise.
Sub Pull_IsChainReady
    /if (${Me.PctAggro} > 99) /return FALSE
    /if (${XAssist.XTFullHaterCount} > ${ChainCount[SETTINGVAL]}) /return FALSE

    /declare i int local 0
    /for i 1 to ${Me.XTarget}
        /if (${Me.XTarget[${i}].TargetType.Equal[Auto Hater]} && ${Me.XTarget[${i}].ID}) {
            /if ( ${Me.XTarget[${i}].PctHPs} >= ${ChainPct[SETTINGVAL]}) /return FALSE
        }
    /next i
/return TRUE

Sub FarmFullInvActions
    |- Bags are full. We now try and do the following...
    |- 1. Call a specifical sub defined in rgcustom.inc if it exists
    |- 2. Call origin if we have it and its ready so we can go home and sell
    |- 3. Stop farming
    /if (${SubDefined[Farm_${Zone.ShortName}_FullInventory]}) {
        /call Farm_${Zone.ShortName}_FullInventory
    } else /if (${RG_AAReady[Origin]}) {
        /call AANow ${Me.AltAbility[Origin].ID} ${Me.ID}
    } else {
        /echo Bags are full, can't origin back home. Stopping and beeping.
        /rg DoPull 0
        /beep
    }
/return

Sub LoadPullIni
    /declare ini_mobstopull string local ${Ini[${Pull_INI},${Zone.ShortName},MobsToPull]}
    /declare ini_mobstoignore string local ${Ini[${Pull_INI},${Zone.ShortName},MobsToIgnore]}
    /declare ini_waypoints string local ${Ini[${Pull_INI},${Zone.ShortName},Waypoints]}

    /if (${ini_mobstopull.Equal[NULL]} && ${ini_mobstoignore.Equal[NULL]} && ${ini_waypoints.Equal[NULL]}) {
        /call SavePullIni
    } else {
        /if ( ${ini_mobstopull.NotEqual[NULL]} ) {
            DEBUG Loading ini_mobstopull ${ini_mobstopull}
            /invoke ${PullOnly_Set.Clear}
            /invoke ${PullOnly_Set.Add[${ini_mobstopull}]}
        }
        /if ( ${ini_mobstoignore.NotEqual[NULL]} ) {
            DEBUG Loading ini_mobstoignore ${ini_mobstoignore}
            /invoke ${PullIgnore_Set.Clear}
            /invoke ${PullIgnore_Set.Add[${ini_mobstoignore}]}
        }
        /if ( ${ini_waypoints.NotEqual[NULL]} ) {
            DEBUG Loading ini_waypoints ${ini_waypoints}
            /invoke ${Waypoints_List.Clear}
            /invoke ${Waypoints_List.Append[${ini_waypoints}]}
        }
    }
/return

Sub SavePullIni
    /ini "${Pull_INI}" "${Zone.ShortName}" "MobsToPull" "${SetToString[PullOnly_Set]}"
    /ini "${Pull_INI}" "${Zone.ShortName}" "MobsToIgnore" "${SetToString[PullIgnore_Set]}"
    /ini "${Pull_INI}" "${Zone.ShortName}" "Waypoints" "${ListToString[Waypoints_List]}"
/return

Sub GetWaypoint(int waypoint_num)
    /if (${waypoint_num} < ${Waypoints_List.Count}) {
        /return ${Waypoints_List.Item[${waypoint_num}]}
    }
/return FALSE

|- Returns TRUE if we made it to our destination, FALSE if we were interrupted by a mob. 
Sub NavToWaypoint(string xyz, bool ignoreaggro)
    /if (${Me.Sitting}) {
        /varset InMedState FALSE
        /stand
    } 
    /nav locyxz ${xyz.Arg[2,|]} ${xyz.Arg[1,|]} ${xyz.Arg[3,|]} log=off
    /delay 2s ${Navigation.Active}
    /while (${Navigation.Active}) {
        DEBUG NavToWaypoint Aggro Count: ${XAssist.XTFullHaterCount})
        /if (${XAssist.XTFullHaterCount} && !${ignoreaggro}) {
            |- Figure out a good way of triggering binds here.
            DEBUG Enemies during NavToWaypoint -- returning FALSE
            /echo Interrupted by enemies! Stopping to exterimante!
            /nav stop log=off
            /return FALSE
        }
        /if (${Navigation.Velocity} == 0) {
            DEBUG NavToWaypoint Velocity 0
        }
        TRIGGERBIND
        /delay 1
    }
/return TRUE
#bind WaypointNav2Tgt /wp2tgt
Sub Bind_WaypointNav2Tgt
    /call NavToWaypoint "${Target.X}|${Target.Y}|${Target.Z}"
/return

|----------------------------------------------------------------------------
|- SUB: Bind_PullInfo 
|- Display pull information from the zone. Function modified from the original in KA12.
|---------------------------------------------------------------------------- 
#bind PullInfo /pullinfo
Sub Bind_PullInfo
    /echo -------------------------------------------------------------------------
    /echo  ${Zone.Name} - (${Zone.ShortName})
    /echo -------------------------------------------------------------------------
    /echo MobsToPull: ${Ini[${Pull_INI},${Zone.ShortName},MobsToPull]}
    /echo MobsToIgnore: ${Ini[${Pull_INI},${Zone.ShortName},MobsToIgnore]}
    /echo Waypoints: ${Ini[${Pull_INI},${Zone.ShortName},Waypoints]}
    /echo -------------------------------------------------------------------------
    /echo Pulling With: ${Pull_Ability} [${Pull_AbilityType}] @ Range: ${Pull_AbilityRange}
    /echo -------------------------------------------------------------------------
/return

#bind AddIgnore /addignore
Sub Bind_AddIgnore
    /if (${Target.ID}) /invoke ${PullIgnore_Set.Add[${Target.CleanName}]}
    /echo \aw ${Target.CleanName}\ax\a-y added to Ignore List 
    /call SavePullIni
/return

#bind AddPull /addpull
Sub Bind_AddPull
    /if (${Target.ID}) /invoke ${PullOnly_Set.Add[${Target.CleanName}]}
    /echo \aw ${Target.CleanName}\ax\a-y added to PullOnly list
    /call SavePullIni
/return

#bind ClearPull /clearpull
Sub Bind_ClearPull
    /invoke ${PullOnly_Set.Clear}
    /call SavePullIni
/return

#bind ClearIgnore /clearignore
Sub Bind_ClearIgnore
    /invoke ${PullIgnore_Set.Clear}
    /call SavePullIni
/return

#bind AddWaypoint /addwp
Sub Bind_AddWaypoint(string xyz)
    /if (${Ini[${Pull_INI},${Zone.ShortName},Waypoints].Length} > 2000) {
        /echo \ar NOTICE: \ax cannot add more waypoints before hitting MQ2 character limit.
    } else {
        /if (!${xyz.Length}) {
            |- use our current xyz
            /echo \aw${Me.X}|${Me.Y}|${Me.Z}\ax\a-y added to Waypoint List
            /invoke ${Waypoints_List.Append[${Me.X}|${Me.Y}|${Me.Z}]}
        } else {
            |- use the provided xyz
            /echo \aw${xyz}\ax\a-y added to Waypoint List
            /invoke ${Waypoints_List.Append[${xyz]}
        }
        /call SavePullIni
    }
/return

#bind NextWaypoint /nextwp
Sub Bind_NextWaypoint
    |- Increment our waypoint
    /varset Pull_FarmWPNum ${Math.Calc[${Pull_FarmWPNum}+1]}
    /if (${Pull_FarmWPNum} >= ${Waypoints_List.Count}) {
        |- We've reached the end of our waypoints list, go back to the beginning!
        /varset Pull_FarmWPNum 0
    }
/return

Sub SetToString(string pSetName)
    /declare ret_string string local 
    
    /if (${${pSetName}.Count} > 0) {
        /declare si setiterator local NULL 
        /vardata si ${pSetName}.First.Clone
        
        /while (!${si.IsEnd}) {
            /if (${si.Value.NotEqual[NULL]}) /varset ret_string ${ret_string}${si.Value},
            /invoke ${si.Advance}
        }
    } else {
        /return ""
    }
/return ${ret_string.Left[-1]}

Sub ListToString(string pListName)
    /declare ret_string string local 
    
    /if (${${pListName}.Count} > 0) {
        /declare li listiterator local NULL 
        /vardata li ${pListName}.First.Clone
        
        /while (!${li.IsEnd}) {
            /if (${li.Value.NotEqual[NULL]}) /varset ret_string ${ret_string}${li.Value},
            /invoke ${li.Advance}
        }
    } else {
        /return ""
    }
/return ${ret_string.Left[-1]}

|- Return TRUE if it is OK to pull, FALSE otherwise.
Sub CheckGroupForPull(string st_classlist, int int_startlvl, int int_stoplvl)
    /declare i int local 0
    /for i 0 to ${Group}
        |- We check the selected class list for the group AND will always check ourselves (we're group member 0)
        /if (${Select[${Group.Member[${i}].Class.ShortName},${st_classlist}]} || ${i} == 0) {
            |- Group member is what we want to check... make sure they have
            |- above 90% of their resources.
            |- We use class members to determine the statistics types because the SPAWN TLO will not return
            |- the right information for all group characters.
            /if (${Pull_State} == PULL_IDLE) {
                /if (${Select[${Group.Member[${i}].Class.ShortName},PAL,SHD,MNK,BER,ROG,BST,RNG,BRD]}) {
                    /if (${Group.Member[${i}].PctEndurance} < ${int_startlvl} || ${Group.Member[${i}].PctHPs} < ${int_startlvl}) {
                        /return FALSE
                    }
                }
                /if (${Select[${Group.Member[${i}].Class.ShortName},MAG,ENC,NEC,WIZ,DRU,SHM,CLR,BST,PAL,SHD,RNG,BRD]}) {
                    /if (${Group.Member[${i}].PctMana} < ${int_startlvl} || ${Group.Member[${i}].PctHPs} < ${int_startlvl}) {
                        /return FALSE
                    }
                }
            }
            /if (${Pull_State} == PULL_GROUPWATCH) {
                /if (${Select[${Group.Member[${i}].Class.ShortName},PAL,SHD,MNK,BER,ROG,BST,RNG,BRD]}) {
                    /if (${Group.Member[${i}].PctEndurance} < ${int_stoplvl} || ${Group.Member[${i}].PctHPs} < ${int_stoplvl}) {
                        /return FALSE
                    }
                }
                /if (${Select[${Group.Member[${i}].Class.ShortName},MAG,ENC,NEC,WIZ,DRU,SHM,CLR,BST,PAL,SHD,RNG,BRD]}) {
                    /if (${Group.Member[${i}].PctMana} < ${int_stoplvl} || ${Group.Member[${i}].PctHPs} < ${int_stoplvl}) {
                        /return FALSE
                    }
                }                
            }

            |- Make sure they're not dead (hovering) and they're in zone.
            /if (${Group.Member[${i}].Hovering}) {
                /call PullNotification "${Group.Member[${i}].CleanName} is dead. Holding pulls."
                /return FALSE
            } 
            /if (${Group.Member[${i}].OtherZone}) {
                /call PullNotification "${Group.Member[${i}].CleanName} is out of zone. Holding pulls."
                /return FALSE
            } 
            /if (${Group.Member[${i}].Distance} > ${Math.Calc[${AutoCampRadius[SETTINGVAL]}*2]}) {
                /call PullNotification "${Group.Member[${i}].CleanName} is beyond AutoCampRadius*2: ${Math.Calc[${AutoCampRadius[SETTINGVAL]}*2]}. Holding pulls."
                /return FALSE
            }

            /if (${DoPull[SETTINGVAL]} == PMODE_CHAIN) {
                /if ( ${Group.Member[${i}].ID} == ${assistid} ) {
                    /if (${ReturnToCamp[SETTINGVAL]}) {
                        /if (${Math.Distance[${Group.Member[${i}].Y},${Group.Member[${i}].X},${Group.Member[${i}].Z}:${AutoCampY},${AutoCampX},${AutoCampZ}]} > ${Math.Calc[${AutoCampRadius[SETTINGVAL]}]}) {
                            /call PullNotification "${Group.Member[${i}].CleanName} is beyond AutoCampRadius from ${AutoCampY},${AutoCampX},${AutoCampZ}: ${Math.Calc[${AutoCampRadius[SETTINGVAL]}]}. Holding pulls."
                            /return FALSE
                        }
                    } else {
                        /if (${Math.Distance[${Group.Member[${i}].Y},${Group.Member[${i}].X},${Group.Member[${i}].Z}:${Me.Y},${Me.X},${Me.Z}]} > ${Math.Calc[${AutoCampRadius[SETTINGVAL]}]}) {
                            /call PullNotification "${Group.Member[${i}].CleanName} is beyond AutoCampRadius from me: ${Math.Calc[${AutoCampRadius[SETTINGVAL]}]}. Holding pulls."
                            /return FALSE
                        }                        
                    }
                }
            }
        }
    /next i
/return TRUE

Sub PullNotification(string st_message)
    /if (!${Pull_MsgTimer}) {
        /echo \ag- ${st_message} \ax
        /varset Pull_MsgTimer NOTIFICATIONDELAY
    }
/return

|----------------------------------------------------------------------------
|- SUB: GetXTHaterList 
|- Returns a list of xtarget mob-names (comma seperated)
|---------------------------------------------------------------------------- 
Sub GetXTHaterList
    /declare xthater_list string local
    /declare i int local 1
    /if (${Me.XTarget}) {
        /for i 1 to ${Me.XTarget}
            /if (${Me.XTarget[${i}].TargetType.Equal[Auto Hater]} && ${Me.XTarget[${i}].ID}) {
                /varset xthater_list ${Me.XTarget[${i}].Name}|${xthater_list}
            }
        /next i
    } else {
        /varset xthater_list EMPTY
    }
    DEBUG Returning ${xthater_list}
/return ${xthater_list}

|----------------------------------------------------------------------------
|- SUB: DiffXTHaterList 
|- list_one = First comma seperated mob name list
|- list_two = Second comma seperated mob name list
|- Returns TRUE if the lists are different, FALSE if they are the same
|---------------------------------------------------------------------------- 
Sub DiffXTHaterList(string old_list, string new_list)
    /if (${old_list.NotEqual[${new_list}]} && ${new_list.NotEqual[EMPTY]}) {
        DEBUG ${old_list} != ${new_list}
        /return TRUE
    } else {
        DEBUG ${old_list} == ${new_list}
    }
/return FALSE
