|-RGmez.inc
|- Version 2020.03.01
|- The Mez System requires the following spell variables defined in classes using Mez abilities:
|- MezSpell
|- MezAESpell
|- MezAEAA

Sub HandleMezAnnounce(string message)
    /if (${MezAnnounce[SETTINGVAL]}!=0) {
        /call PrintGroupMessage "${message}"
    } else {
        /echo ${message}
    }
/return

|--------------------------------------------------------------------
|- SUB: InitMez
|--------------------------------------------------------------------
Sub InitMez
    DEBUG RG MEZ INITIALIZATION
    /if (!${Defined[MezTracker_List]}) /declare MezTracker_List list outer
    /if (!${Defined[MezImmune_List]}) /declare MezImmune_List list outer
    |- Bard AE mez counter
    /if (!${Defined[_brdAEMezTimer]}) /declare _brdAEMezTimer         timer outer 0    

    |- Make sure Mez Spell Variables are defined or exit out
    /if (!${Defined[MezAESpell]}) {
        /echo \ar MISSING Variable MezAESpell -- EXITING MACRO!
        /end
    }
        |- Make sure Mez Spell Variables are defined or exit out
    /if (!${Defined[MezSpell]}) {
        /echo \ar MISSING Variable MezSpell -- EXITING MACRO!
        /end
    }
    |- Make sure Mez Spell Variables are defined or exit out
    /if (!${Defined[MezAEAA]}) {
        /echo \ar MISSING Variable MezAEAA -- EXITING MACRO!
        /end
    }

|- Multi class variable definitions to avoid replicating the same code
|- into all macro files that use mez.
|- Mez
    /if (!${Defined[MezMod]}) /declare MezMod                 int     outer   0
    /if (!${Defined[MezWatchCircum]}) /declare MezWatchCircum         int     outer   0
    /if (!${Defined[MezWatchZCircum]}) /declare MezWatchZCircum        int     outer   0
    
    /call RGLoadSetting ${Me.Class.ShortName} AutoLevelRange 1 Mez "Set 0/1 to enable automatic mez level detection based on spells."
    /call RGLoadSetting ${Me.Class.ShortName} MezOn 1 Mez "Set 0/1 to use mez spells."
    /call RGLoadSetting ${Me.Class.ShortName} UseSingleTgtMez 1 Mez "Set 0/1 to enable use of single target mez spells/songs. Default: 1."
    /call RGLoadSetting ${Me.Class.ShortName} MezAnnounce 1 Mez "Set 0/1 to announce mez casts."
    /call RGLoadSetting ${Me.Class.ShortName} MezStartCount 2 Mez "Sets # of mobs needed to start using Mez spells. ( Default 2 )"
    /call RGLoadSetting ${Me.Class.ShortName} MezAECount 3 Mez "Sets # of mobs needed on aggro and in range to AE Mez ( Default 3 )"
    /call RGLoadSetting ${Me.Class.ShortName} MaxMezCount 13 Mez "Maximum # of mobs to CC ( Default is 13 )"
    /call RGLoadSetting ${Me.Class.ShortName} MezRadius 100 Mez "Radius for mobs to be in to start Mezing, An area twice this size is monitored for aggro mobs"
    /call RGLoadSetting ${Me.Class.ShortName} MezZRadius 15 Mez "Height radius (z-value) for mobs to be in to start mezzing. An area twice this size is monitored for aggro mobs. If you're enchanter is not mezzing on hills -- increase this value."
    /call RGLoadSetting ${Me.Class.ShortName} MezMinLevel 0 Mez "Minimum Level a mob must be to Mez - Below this lvl are ignored. 0 means no mobs ignored."
    /call RGLoadSetting ${Me.Class.ShortName} MezMaxLevel 0 Mez "Maximum Level a mob must be to Mez - Above this lvl are ignored. 0 means no mobs ignored."
    /call RGLoadSetting ${Me.Class.ShortName} MezStopHPs 80 Mez "Mob HP% to stop trying to mez"     
    /call RGLoadSetting ${Me.Class.ShortName} UseAEAAMez 0 Mez "Toggle 0/1 to use Area Effect AA Mez (Default: 0)."

    
    /varcalc MezWatchCircum ${MezRadius[SETTINGVAL]}*2
    /varcalc MezWatchZCircum ${MezZRadius[SETTINGVAL]}*2
    
    |- Enchanter specific AA's that modify mez mods
    |-Set AA DurationMod for mez timer from Spell Casting Reinforcement AA
    /if (${Me.AltAbility[Mesmerization Mastery].Rank}==1) /varset MezMod 6
    /if (${Me.AltAbility[Mesmerization Mastery].Rank}==2) /varset MezMod 12
    /if (${Me.AltAbility[Mesmerization Mastery].Rank}==3) /varset MezMod 18
    /if (${Me.AltAbility[Mesmerization Mastery].Rank}==4) /varset MezMod 24
    
    |- Use this to block your main loop functions if you want to mezes to
    |- take priority. Will be set to 1 if you have a mob that needs mezzing
    |- but your mez spell wasn't active.
    /if (!${Defined[BlockForMez]}) /declare BlockForMez int outer 0
/return TRUE

Sub AutoConfMezLevels
    |- Formula Section for calculating Max / Min levels to Mez based on spells
    /if (${MezMinLevel[SETTINGVAL]}>${MezMaxLevel[SETTINGVAL]} || ${AutoLevelRange[SETTINGVAL]}) {
        /call RGChangeSetting ${Me.Class.ShortName} MezMinLevel 0
    }
    /if (${MezMaxLevel[SETTINGVAL]}==0 || ${MezMaxLevel[SETTINGVAL]}>${Spell[${MezSpell}].MaxLevel} || ${AutoLevelRange[SETTINGVAL]}) {
        /call RGChangeSetting ${Me.Class.ShortName} MezMaxLevel ${Spell[${MezSpell}].MaxLevel}
    }
    /if (${MezMinLevel[SETTINGVAL]}==0) {
        /if (${Me.Level}>=40) {
            /call RGChangeSetting ${Me.Class.ShortName} MezMinLevel ${Math.Calc[${Me.Level}-30].Int}
        } else /if (${Me.Level}>=30) {
            /call RGChangeSetting ${Me.Class.ShortName} MezMinLevel ${Math.Calc[${Me.Level}-20].Int}
        } else {
            /call RGChangeSetting ${Me.Class.ShortName} MezMinLevel 1
        }
    } 
/return TRUE

|--------------------------------------------------------------------
|- SUB: AddCCTarget
|--------------------------------------------------------------------
Sub AddCCTarget(int mob_id, int timer_val)
    DEBUG AddCCTarget: Checking ${mob_id} before add.
    
    /if (!${mob_id}) {
        AddCCTarget: DEBUG MOB ID 0, not adding to list.
        /return FALSE
    }
    
    |- Check if we're at our max mez count
    /if (${MezTracker_List.Count} > ${MaxMezCount[SETTINGVAL]}) {
        /echo \ar- DANGER: Max Mez Limit ( ${MaxMezCount[SETTINGVAL]} ) Reached.
        /return FALSE
    }
    
    |- Check that the mob isn't already on the list.
    /if (${MezTracker_List.Contains[${mob_id}]}) {
        AddCCTarget: DEBUG ${mob_id} already on mez list.
        /return FALSE
    }
    
    |- Make sure the mob isn't on the immune list.
    /if (${MezImmune_List.Contains[${mob_id}]}) {
        AddCCTarget: DEBUG ${mob_id} on the immune list.
        /return FALSE
    }
    
    DEBUG AddCCTarget: Passed Timer Val ${timer_val}
    /declare ${mob_id}_MezTimer timer outer ${timer_val}
    
    DEBUG AddCCTarget: Adding ${mob_id} to List.
    |- Add the mob to the mez list 
    /if (!${MezTracker_List.Append[${mob_id}]} ) {
        /echo Could Not Add ${mob_id} to Mez List.
    }
/return TRUE

Sub AddImmuneTarget(int mob_id)
    |- Don't add the mob to our immune list if we are already tracking them
    /if (${MezImmune_List.Contains[${mob_id}]}) {
        /return TRUE
    }
    
    /if (!${MezImmune_List.Append[${mob_id}]}) {
        /echo \arERROR:\ax Failed adding \aw${Target.ID}\ax to MezImmune_List
        /return FALSE
    }
/return TRUE

|--------------------------------------------------------------------
|- SUB: RemoveCCTarget
|--------------------------------------------------------------------
Sub RemoveCCTarget(int mob_id, int only_delete_timer)
    DEBUG RemoveCCTarget: Removing ${mob_id} from mez list.
    
    /if (!${mob_id}) {
        DEBUG RemoveCCTarget: MOB ID 0, not removing from list.
        /return FALSE
    }
    
    |- Make sure the mob is in our list
    /if ( ${MezTracker_List.Contains[${mob_id}]} ) {
        DEBUG RemoveCCTarget: Deleting Timer ${mob_id}
        /deletevar ${mob_id}_MezTimer
        
        |- Only delete the list entry if we don't have the only
        |- delete timer flag set. This allows us to avoid clobbering
        |- the list iterator in certain situations
        /if (!${only_delete_timer}) {
            /if (!${MezTracker_List.Remove[${mob_id}]}) {
                /echo Could not remove ${mob_id} from Mez List
            } else {
                DEBUG Deleted MezTracker_List entry for ${mob_id}
            }
            |- Delay to let list settle.
            |- /delay 1
        }
    } else {
        /if ( ${Defined[${mob_id}_MezTimer]} ) {
            |- We should never get here.
            DEBUG RemoveCCTarget: MAJOR DANGER - MAJOR DANGER - IMPOSSIBILITY -- TIMER EXISTS FOR MOB NOT ON LIST
            /deletevar ${mob_id}_MezTimer
        }
    }
/return TRUE
|--------------------------------------------------------------------
|- SUB: ResetMezList
|- Called after combat. We need to clean up all our timers and then
|- clear the mez list and mez immune list
|--------------------------------------------------------------------
Sub ResetMezList
    |- No point in garbage collecting if we didn't make any garbage.
    /if (${MezTracker_List.Count} > 0) {
        DEBUG ResetMezList: Resetting Mez List -- ${MezTracker_List.Count}
        /declare li listiterator local NULL
        |- Need to use a clone bcause we're mutating the list with RemoveCCTarget
        /vardata li MezTracker_List.First.Clone
        
        /while (!${li.IsEnd}) {
        
            |- Only delete timers so we don't screw up our list iterator
            /call RemoveCCTarget ${li.Value} 1
            
            /invoke ${li.Advance}
        }
    }
    |- We're doing a non-zero check here AGAIN because mq2collections may not behave correctly
    |- when clearning an empty list
    /if (${MezTracker_List.Count} > 0) {
        DEBUG Calling MezTracker_List Clear
        /invoke ${MezTracker_List.Clear}
    }
    /if (${MezImmune_List.Count} > 0) {
        DEBUG ResetMezList: Resetting Mez Immune list
        /invoke ${MezImmune_List.Clear}
    }
/return TRUE

|--------------------------------------------------------------------
|- SUB: ResetMezTimers
|- Resets all mez timers
|--------------------------------------------------------------------
Sub ResetMezTimers
    /declare li listiterator local NULL
    /vardata li MezTracker_List.First.Clone
    
    DEBUG ResetMezTimers: Resetting All Mez Timers
    
    /while (!${li.IsEnd}) {
        DEBUG ResetMezTimers: Resetting Mez Timer for ${li.Value}
        /varset ${li.Value}_MezTimer 0
        /invoke ${li.Advance}
    }
    
/return TRUE

|--------------------------------------------------------------------
|- Sub: DoMez
|- This is the overall mez loop
|--------------------------------------------------------------------
Sub DoMez
    |- If we've reached this point then we know we have more then MezStarCount in our XTarget list.
    DEBUG Doing Mez Stuff
    
    |- If AEMez is enabled Do an AEMez Check -- we mez if we have more then our count
    |- We're doing an or check here as ENC could have both but BRD can only have one.
    |- Added Bard AE mez timer here because Bards AE mez song has 30 second cooldown
    |- This allows us to avoid going directly into aemez as bard endlessly when aemez is down.
    /if ( ${Me.XTarget} >= ${MezAECount[SETTINGVAL]} && ((${Me.Class.ShortName.Equal[BRD]} && !${_brdAEMezTimer}) || (${Me.SpellReady[${MezAESpell}]} || ${RG_AAReady[${MezAEAA}]})) ) {
        DEBUG Doing AEMez Check
        /call AEMezCheck
    }
    
    |- Update the mez list based on nearby spawns -- but only worth it if we have a big xtarget list
    /if (${Me.XTarget} >= ${MezStartCount[SETTINGVAL]}) {
        DEBUG Doing Mez List Updating
        |- Currently crashes MQ2/EQ
        /call UpdateMezList
    }
    
    |- Process our mez list -- handle mez refreshes if needed
    |- Adjusted to reflect that Bard mez is never "ready" because of twisting but has no cooldown
    /if ( (${Me.Class.ShortName.Equal[BRD]} || ${Me.SpellReady[${MezSpell}]})  && ${MezTracker_List.Count} > 1) {
        DEBUG ${MezSpell} Ready -- Processing Mez List
        /call ProcessMezList
    }
/return TRUE

|--------------------------------------------------------------------
|- SUB: UpdateMezList
|--------------------------------------------------------------------
Sub UpdateMezList
    |- To reduce duplicate code we're going to create an array of the two type of searches
    |- we want to do as we can't search for both npcs and npcpets at the same time. This allows us to have an outer for loop that chooses which search string we use.
    /declare SearchStrings[2] string local
    /varset SearchStrings[1] npc
    /varset SearchStrings[2] npcpet

    |- We want to look for any NPCs or NPC pets within circumfrences dictated by user settings. We only want mobs we can actually cast mez on. We want mobs we can target and are angry at us.
    /declare mezspawnsearch_npc string local "npc radius ${MezWatchCircum} zradius ${MezWatchZCircum} range ${MezMinLevel[SETTINGVAL]} ${MezMaxLevel[SETTINGVAL]} targetable playerstate 4"
    /declare mezspawnsearch_npcpet string local "npcpet radius ${MezWatchCircum} zradius ${MezWatchZCircum} range ${MezMinLevel[SETTINGVAL]} ${MezMaxLevel[SETTINGVAL]} targetable playerstate 4"
   
    |- This tmp data gets regularly overwritten so only declaring it once out here as
    |- it has a NULL value and is set via vardata instead of having it created every
    |- loop iteration.
    /declare tmp_spawninfo spawn local NULL
    
    |- Declares for the inner for loop
    /declare tmp_searchstr string local NULL
    /declare tmp_mobcount int local NULL
    
    |- outer for loop
    /declare strcnt int local 0
    |- Inner for loop
    /declare i int local 0
    /for strcnt 1 to ${SearchStrings.Size}
        |- Let's get a total count of all the NPC's nearby and loop through them to see
        |- if we need to mez them. 
        /varset tmp_searchstr ${mezspawnsearch_${SearchStrings[${strcnt}]}}
        /vardata tmp_mobcount SpawnCount[${tmp_searchstr}]
        
        DEBUG UpdateMezList: Search String: ${tmp_searchstr} -- Count ${tmp_mobcount}
        
        /if (${tmp_mobcount}==0) {
            DEBUG UpdateMezList: MobCount 0 -- Continuing
            /continue
        }
       
        /for i 1 to ${tmp_mobcount}
            
            DEBUG UpdateMezList: Calling NearestSpawn[${i},${tmp_searchstr}]
            |- We need to get the spawn in question we're concerned with
            /squelch /vardata tmp_spawninfo NearestSpawn[${i},${tmp_searchstr}]
            
            DEBUG UpdateMezList: Processing MobCount ${i} -- ID: ${tmp_spawninfo.ID} Name: ${tmp_spawninfo.Name} Level: ${tmp_spawninfo.Level} BodyType: ${tmp_spawninfo.Body.Name}
            
            |- Is the mob ID in our mez immune list? If so, skip.
            /if (${MezImmune_List.Count} > 0) {
                /if (${MezImmune_List.Contains[${tmp_spawninfo.ID}]}) {
                    DEBUG UpdateMezList: Mob ${tmp_spawninfo.ID} on immune list.
                    /continue
                }
            }
            
            |- Here's where we can add a necro check to see if the spawn is undead or not. If it's not
            |- undead it gets added to the mez immune list.
                
            |- If the mob's a giant add to our mez immune list and skip.
            /if (${tmp_spawninfo.Body.Name.Equal[Giant]}) {
                DEBUG UpdateMezList: Giants are immune. Adding ${tmp_spawninfo.ID} to mezimmune list.
                /call AddImmuneTarget ${tmp_spawninfo.ID}
                /continue
            }
            
            |- Is the mob out of LOS? If so, skip but call out an error.
            /if (!${tmp_spawninfo.LineOfSight}) {
                /echo Can't Mez Mob \ay ${tmp_spawninfo.Name} [${tmp_spawninfo.ID}] -- MQ2 says not in LOS
                /continue
            }
            
            |- Is the mob below our health % check, if so, skip. 
            /if (${tmp_spawninfo.PctHPs} < ${MezStopHPs[SETTINGVAL]}) {
                DEBUG UpdateMezList: [${tmp_spawninfo.ID}] too low hp => ${tmp_spawninfo.PctHPs} < ${MezStopHPs[SETTINGVAL]}
                /continue
            }
            
            |- Is the mob still too far away to cast mez on?
            /if (${tmp_spawninfo.Distance} > ${MezRadius[SETTINGVAL]}) {
                DEBUG UpdateMezList: [${tmp_spawninfo.ID}] too far away => ${tmp_spawninfo.Distance} > ${MezRadius[SETTINGVAL]}
                /continue
            }
            
            |- Is the mob ID is not in our mez list, add them and then set whatever
            |- mez duration they currently have on them -- we might have AE Mezed.
            /if (!${MezTracker_List.Contains[${tmp_spawninfo.ID}]}) {
                DEBUG UpdateMezList: Need to add ${tmp_spawninfo.Name} [${tmp_spawninfo.ID} - ${tmp_spawninfo.Level}] to Mez List
                /call AddCCTarget ${tmp_spawninfo.ID} 
            }
        /next i
    /next strcnt
    TRIGGERBIND
/return TRUE

|--------------------------------------------------------------------
|- SUB: ProcessMezList
|-
|- Asummptions
|- Mez Spell/Song Variable called ${MezSpell}
|- AE Mez Spell/Song Variable called ${MezAESpell}
|--------------------------------------------------------------------
Sub ProcessMezList
    |- Assume by default we never need to block for mez. We'll set this if-and-only-if
    |- we need to mez but our ability is on cooldown.
    /varset BlockForMez 0
    
    |- If we have only one spawn we're tracking, we don't need to be mezzing
    /if (${MezTracker_List.Count} > 1) {
        |- This is a local iterator we'll be using for both the main meztracker list loop
        |- and the list loop for removing items from the mez tracker.
        /declare li listiterator local NULL
        
        |- We create a clone because that's what you need to do for mq2collections not to
        |- break in one way 
        /vardata li MezTracker_List.First.Clone
        DEBUG ProcessMezList: MezTracker_List Size ${MezTracker_List.Count}
        
        |- We create a temporary list that tracks what needs to be removed. If we 
        |- remove items in our first loop, it corrupts the list iterator and mq2collections
        |- throws a kernelbase exception that it doesn't handle in-house
        /declare tmp_mezrem_list list local
        
        /declare tmp_spawn spawn local
        /while (!${li.IsEnd}) {
             DEBUG ProcessMezList: Checking ${li.Value}
            |- See if the spawn is still valid, if so, do our vardata. If not,
            |- do a RemoveCC and skip the loop.
            /if (${SpawnCount[id ${li.Value}]}) {
                DEBUG ProcessMezList: Spawn ${li.Value} exists. Setting vardata.
                /squelch /vardata tmp_spawn Spawn[id ${li.Value}]
            } else {
                DEBUG ProcessMezList: Spawn doesn't exist.
                |- Here we mark the spawn for removal because if we remove it here we'll corrupt
                |- our list iterator
                /invoke ${tmp_mezrem_list.Append[${li.Value}]}
                |- Here we're using a GoTo to jump to the end of the while loop. We
                |- Want to skip the rest of the processing but /continue would also
                |- Skip the li.Advance so we need to use a goto.
                /goto :nextitem
            }
            
            |- If the mob ended up on our mezimmune list, cue it for removal and skip to next items. There
            |- should be no reason for the ID to end back up on the MezTracker_list as the Function that keeps
            |- track of spawn skips items on Mezimmune.
            /if (${MezImmune_List.Contains[${li.Value}]}) {
                DEBUG ProcessMezList: ${li.Value} found in Mez Immune. Adding to removal queue.
                /invoke ${tmp_mezrem_list.Append[${li.Value}]}
            }
            
            /if (!${tmp_spawn.ID} || ${tmp_spawn.Type.Equal[Corpse]}) {
                DEBUG ProcessMezList: Spawn [${tmp_spawn.ID}] NULL or Dead [${tmp_spawn.Type.Equal[Corpse]}] Removing from CC
                |- The spawn either no longer exists or is dead. Either case, don't CC. Or our spawn search couldn't find it.
                |- Here we mark the spawn for removal because if we remove it here we'll corrupt
                |- our list iterator
                /invoke ${tmp_mezrem_list.Append[${li.Value}]}
                /goto :nextitem
            }

            |- Our mob is still alive, but their mez timer isn't up or they're out of x/y range
            |- Only worry about mezzing if their mez timer less than the time it will take to cast
            |- the mez spell. MyCastTime is in ms, timer is in deciseconds.
            |- We already fudge the mez timer when we set it.
            /if ( ${${li.Value}_MezTimer} > ${Math.Calc[${Spell[${MezSpell}].MyCastTime}/100]} || (${tmp_spawn.Distance} > ${MezRadius[SETTINGVAL]}) || !${tmp_spawn.LineOfSight} ) {
                DEBUG ProcessMezList: Mez timer >${Math.Calc[${Spell[${MezSpell}].MyCastTime}/100]} ( ${${li.Value}_MezTimer} ) -- (${tmp_spawn.Distance} > ${MezRadius[SETTINGVAL]}) -- !${tmp_spawn.LineOfSight}
                /goto :nextitem
            } 

            |-- If this Target is our main assists target, skip.
            /if (${li.Value} == ${Me.GroupAssistTarget.ID}) {
                DEBUG ProcessMezList: Mob is MA's target, skipping
                /goto :nextitem
            }

            |-- If we've turned off single target mezzing, skip the rest of our processing
            /if (!${UseSingleTgtMez[SETTINGVAL]}) {
                DEBUG ProcessMezList: Single target mezzing turned off, moving to next item in list.
                /goto :nextitem
            }
            
            |- Checking to see if we are auto attacking, or if we are actively casting a spell
            |- purpose for this is to catch auto attacking enchaters (who have lost their mind)
            |- And bards who never are not casting.
            /if ( ${Me.Combat} || ${Me.Casting.ID} ) {
                /echo \awNOTICE:\ax Stopping Melee/Singing -- must retarget to start mez.
                /attack off
                /delay 3s !${Me.Combat}
                /stopcast
                /stopsong
                /delay 3s !${Window[CastingWindow].Open}
            }
            |- At this point we know the mob's a valid spawn ID so let's target it to get more buff info.
            /call SetTarget ${li.Value}
            /delay 20 ${Target.BuffsPopulated}

            |- At this point their timer is up, they're within range, and we have line of sight
            |- We better mez them -- we're not in the AE function so we'll single target and not use
            |- an AA
            /if (${NPCSpellReady[${MezSpell}]}) {
                /call MezNow ${li.Value} 0 0
            } else {
                DEBUG ProcessMezList: Setting BlockForMez. Ability not ready but we need a mez.
                /varset BlockForMez 1
            }
            |- If our target is mezzed, reset the timer to the duration of the mez it has. Use that
            |- as a character agnostic way to keep track of when we need to mez next.
            /if ( ${Target.Mezzed.ID} ) {
                DEBUG ProcessMezList: Target already mezzed with ${Target.Mezzed.Name}
                /varcalc ${Target.ID}_MezTimer (${Target.BuffDuration[${Target.Mezzed.Name}].TotalSeconds}*10)*0.85
                DEBUG ProcessMezList: Reset Timer to ${${Target.ID}_MezTimer}
            }
            :nextitem
            /invoke ${li.Advance}
        }
        
        |- Handle the collected list of mobs to remove from our canonical mez list
        /if ( ${tmp_mezrem_list.Count} > 0 ) {
            /vardata li tmp_mezrem_list.First.Clone
            
            /while (!${li.IsEnd}) {
                |- In this case we are wanting to remove both timers AND the list elements
                |- themselves as we don't have to worry about clobbering the iterator for
                |- tmp_mezrem_list
                /call RemoveCCTarget ${li.Value} 0
                
                /invoke ${li.Advance}
            }
        }
    }
    TRIGGERBIND
/return TRUE

|--------------------------------------------------------------------
|- SUB: MezNow
|--------------------------------------------------------------------
Sub MezNow(int mob_id, int do_ae, int use_aa)
    |- First thing we target the mob if we haven't already targeted them.
    /call SetTarget ${mob_id}
    
    /if (${do_ae}) {
        DEBUG Performing AE MEZ --> ${mob_id}
        |- Only Enchanters have an AA AE Mez but we'll prefer the AE Spell if we can.
        |- TODO CHECK IF ITS READY
        /if (${use_aa} && ${Me.Class.ShortName.Equal[ENC]} && !${NPCSpellReady[${MezAESpell}]} && ${RG_AAReady[${MezAEAA}]} && ${UseAEAAMez[SETTINGVAL]}) {
            |- This is a beam AE so I need ot face the target and  cast.
            /face fast
            |- Delay to wait till face finishes
            /delay 5
            /call HandleMezAnnounce "\aw I AM \ar AE AA MEZZING \ag ${MezAEAA}"
            /call AANow ${AltAbility[${MezAEAA}].ID} ${mob_id}
            /call HandleMezAnnounce "\aw I JUST CAST \ar AE AA MEZ \ag ${MezAEAA}"
            /call ResetMezTimers
        } else {
            /if (${NPCSpellReady[${MezAESpell}]}) {
                |- If we're here we're not doing AA-based AE Mezzing. We're either using our bard song or 
                |- ENCH/NEC Spell
                /call HandleMezAnnounce "\aw I AM \ar AE SPELL MEZZING \ag ${MezAESpell}"
                |- Added this If loop to avoid rewriting SpellNow to be bard friendly.
                |- we can just invoke The bard SongNow which already accounts for all the weird bard stuff
                |- Setting the recast time for the bard ae song after cast.
                /if ( ${Me.Class.ShortName.Equal[BRD]} ) {
                    /call SongNow "${MezAESpell}" ${mob_id}
                    /varset _brdAEMezTimer 30s
                } else {
                    /call SpellNow "${MezAESpell}" ${mob_id}
                }
                /call HandleMezAnnounce "\aw I JUST CAST \ar AE SPELL MEZ \ag ${MezAESpell}"
            }
        }
        |- In case they're mez immune
        TRIGGERBIND
    } else {
        |- Single Target mezzing
        DEBUG Single Target Mezzing --> ${mob_id}
        /if (${use_aa} && ${Me.Class.ShortName.Equal[BRD]} && ${RG_AAReady[Dirge of the Sleepwalker]}) {
            |- Bard AA Mez is Dirge of the Sleepwalker
            |- Only bards have single target AA Mez
            |- Cast and Return
            /call HandleMezAnnounce "\aw I AM USING \ar BRD AA MEZ \ag Dirge of the Sleepwalker"
            /call AANOW ${Me.AltAbility[Dirge of the Sleepwalker].ID} ${mob_id}
            /call HandleMezAnnounce "\aw I JUST CAST \ar BRD AA MEZ \ag Dirge of the Sleepwalker"
            TRIGGERBIND
            /return 
        }

        |- Added this If loop to avoid rewriting SpellNow to be bard friendly.
        |- we can just invoke The bard SongNow which already accounts for all the weird bard stuff
        /if ( ${Me.Class.ShortName.Equal[BRD]} ) {
            /call SongNow "${MezSpell}" ${mob_id}
        } else {
        |- This may not work for Bards but will work for NEC/ENCs
            /call SpellNow "${MezSpell}" ${mob_id}
        }
        /if (${CastResult.Equal[CAST_SUCCESS]}) {
            /call HandleMezAnnounce "\ar JUST MEZZED \aw -> \ag ${MezSpell} \aw on \ay ${Spawn[${mob_id}].CleanName} \aw : \ar ${mob_id}"
        }
        /if (${CastResult.Equal[CAST_RESIST]}) {
            /call HandleMezAnnounce "\ar MEZ Resisted \ag -> \ay ${Spawn[${mob_id}].CleanName} \ag <- \ar ID:${mob_id}"
        }
        |- In case our target resists
        TRIGGERBIND
    }
/return TRUE

|--------------------------------------------------------------------
|- SUB: DoAEMez
|--------------------------------------------------------------------
Sub AEMezCheck
    |- We want to make sure all the mobs that are angry with us are within assist range and we need
    |- to check and make sure to check both npcs and npc pets
    /declare ae_count int local 0
    /varcalc ae_count ${SpawnCount[npc radius ${MezRadius[SETTINGVAL]} targetable los playerstate 4]} + ${SpawnCount[npcpet radius ${MezRadius[SETTINGVAL]} targetable los playerstate 4]} - ${SpawnCount[npc radius ${MezRadius[SETTINGVAL]} targetable los playerstate 4 body Giant]}
    
    |- Make sure the mobs of concern are within range
    DEBUG AEMezCheck: AE Mob Count ${ae_count}
    /if (${ae_count} < ${MezAECount[SETTINGVAL]}) {
        /return
    }
    
    |- Get the nearest spawn meeting our npc search criteria
    /declare mez_tgt_spawn spawn local NULL
    /squelch /vardata mez_tgt_spawn NearestSpawn[1, npc radius ${MezRadius[SETTINGVAL]} targetable los playerstate 4]
    
    |- Next make sure casting our AE won't anger ore mobs -- I'm lazy and not checking the AERange of the AA. I'm gonna assume if the 
    |- AERange of the normal spell will piss them off, then the AA probably would too. 
    /declare cnt_angered_mobs int local ${SpawnCount[npc xtarhater loc ${mez_tgt_spawn.X} ${mez_tgt_spawn.Y} radius ${Spell[${MezAESpell}].AERange}]}
    /declare cnt_chill_mobs int local ${SpawnCount[npc loc ${mez_tgt_spawn.X} ${mez_tgt_spawn.Y} radius ${Spell[${MezAESpell}].AERange}]}
    DEBUG AEMezCheck: Angry mobs ${cnt_angered_mobs} -- Chill Mobs ${cnt_chill_mobs}
    /if ( ${cnt_angered_mobs} >= ${cnt_chill_mobs} ) {
    
            |- Checking to see if we are auto attacking, or if we are actively casting a spell
            |- purpose for this is to catch auto attacking enchaters (who have lost their mind)
            |- And bards who never are not casting.
            /if ( ${Me.Combat} || ${Me.Casting.ID} ) {
                |- We keep attacking as 
                /echo \awNOTICE:\ax Stopping Singing so I can cast AE mez.
                |- /attack off 
                /stopcast
                /stopsong
            }
            |-- Call MezNow and pass the AE flag and allow it to use the AA if the Spell isn't ready.
            |- This won't effect bards at all.
            |- We target autoassist id as we don't want to swap targets and we want to continue meleeing
            /echo \awNOTICE:\ax Re-targeting to our main assist's mob.
            /if (${SetControlToon[]} && FINDTARGETCHECK) /call FindTarget FROMHERE
            /call SetTarget ${autotargetid}
			/call MezNow ${autotargetid} 1 1
    }
    |- In case our target resists
    TRIGGERBIND
/return TRUE

|--------------------------------------------------------------------
|- SUB: Event_MezBroke
|--------------------------------------------------------------------
#Event MezBroke          "#1# has been awakened by #2#."
Sub Event_MezBroke(meztext, mezmob, mezbreaker)
    /if (${IsMezzing}) {
        /if (!${MezOn[SETTINGVAL]}) /return
        
        |- Target the newly unmezzed mob -- we assume the person who broke the mez is still targetting them
        /assist ${mezbreaker}
        /delay 5s ${Me.AssistComplete}==TRUE
        DEBUG Woke Mob ${mezmob} Target Name ${mezbreaker}
        
        /if (${MezTracker_List.Count}) {
            /call HandleMezAnnounce "\ag >> \ar ${Spawn[${mezbreaker}].CleanName} \ag << \aw has awakened \ag -> \ay ${mezmob} \ag <-"
        }

        |- If the target is in our mez tracking list reset the timer.
        /if (${MezTracker_List.Contains[${Target.ID}]}) {
            /varset ${Target.ID}_MezTimer 0
        }
    }
    /doevents flush MezBroke
/return TRUE
|-------------------------------------------------------------------------------------
|- SUB: Event MezImmune
|-------------------------------------------------------------------------------------
#Event MezImmune                 "Your target cannot be mesmerized#*#"
Sub Event_MezImmune(string line, string spell, string target)

    DEBUG ${Target.Name} [${Target.ID} LVL: ${Target.Level}] Is Immune To Mez. Removing from CC List.
    /echo Adding ${Target.Name} [${Target.ID}] to MezImmune List.
    /call AddImmuneTarget  ${Target.ID}
    
    |- Note you can't RemoveCCTarget here as it will potentially invalidate the iterator in MQ2Collections
    |- and crash everything.
    
    /doevents flush MezImmune
/return TRUE