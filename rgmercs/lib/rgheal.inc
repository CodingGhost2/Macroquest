|**
    RG Heal is a self contained set of data types and an API to working with them. Unlike rotations,
    healing setups are similar enough that we don't necessarily need individual macro authors to create
    and manage their own data types. Instead macro authors need only call Heal_Init prior to the main
    loop of their class macro and prior to  initialization functions that will call Heal_AddHealPoint.
    Heal_AddSpell will then be called in the same functions used to configure spell rotations for a class.
    Heal_AddSpell will need to be called after all healing points have been added (as it takes a heal point
    as an argument) and after Heal_Init (because if data types aren't initialized there will be nothing to
    add healing points or spells to).

**|

|----------------------------------------------------------------------------
|- SUB: Heal_Init - Initializes data types for the RG Healing subsystem
|---------------------------------------------------------------------------- 
Sub Heal_Init
    |- Map data layout:
    |- Key = %Health for HealPoint_Map
    |- Value = Variable name of an ordered rotation specifical used for healing
    /declare HealPoint_Map map outer
    
    |- Keeps track of the maximum heal point for priority heal and normal
    |- heal gating.
    /declare HealPoint_MaxPoint int outer 0

    |- Used for zerker skipping in worst hurt.
    /call RGLoadSetting Settings ZerkIgnoreHP 75 Options "%HP, above which, Zerks will be ignored for all heals." 1

/return TRUE

Sub Heal_Clear
    /if (!${HealPoint_Map.Count}) /return FALSE
    |- Delete all the Ordered Rotations Created
    /declare mi_hp mapiterator local
    /vardata mi_hp HealPoint_Map.First.Clone

    /while (!${mi_hp.IsEnd} ) {
        /call Ordered_Rotation_Delete ${mi_hp.Value}
        /invoke ${mi_hp.Advance}
    }
    /invoke ${HealPoint_Map.Clear}
/return TRUE

|----------------------------------------------------------------------------
|- SUB: Heal_AddHealPoint - Creates a heal point in the healing subsystem that can have spells added to it later.
|- in: heal_point -- percent health at which to cast a list of heal spells
|---------------------------------------------------------------------------- 
Sub Heal_AddHealPoint(int heal_point)

    |- Make sure we don't already have a heal_point put in yet
    /if (${HealPoint_Map.Contains[${heal_point}]}) {
        /echo \arERROR:\ax Duplicate heal point attempted.
        /return FALSE
    } 
    
    |- Avoid heal points <10 or == 100 to maintain lexicographical ordering.
    |- usefulness of these heal points is negligable anyway
    /if ( ${heal_point} < 10 || ${heal_point} > 99 ) {
        /echo \arERROR:\ax Healing Point ${heal_point} is <10 or >99. Not adding.
        /return FALSE
    }
    
    /if (!${HealPoint_Map.Add[${heal_point},${heal_point}_OrderedHeal]}) {
        /echo Error: Could not create healpoint
        /return FALSE
    } else {
        |- Wait to create our order type variables until after we've got them in our HealPoint
        /call Ordered_Rotation_New ${heal_point}_OrderedHeal
    }

/return TRUE

|----------------------------------------------------------------------------
|- SUB: Heal_SetMaxPoint - Creates a heal point in the healing subsystem that can have spells added to it later.
|- out: [Reference] Sets the HealPoint_MaxPoint value based on items in the HealPoint_Map
|- return: TRUE on success, FALSE on error.
|---------------------------------------------------------------------------- 
Sub Heal_SetMaxPoint
    |-- Used to keep track of our healing points
    /declare mi_hp mapiterator local
    /vardata mi_hp HealPoint_Map.First.Clone
    /varset HealPoint_MaxPoint 0

    |- Loop through the healing points
    /while (!${mi_hp.IsEnd} ) {
        /if (${mi_hp.Key} > ${HealPoint_MaxPoint}) {
            /varset HealPoint_MaxPoint ${mi_hp.Key}
        }
        /invoke ${mi_hp.Advance}
    }
    /echo \awHealing:\ax \ag${Me.Class.ShortName}\ax will not start healing until Target PC reaches \ar ${HealPoint_MaxPoint}% \ax HP
/return TRUE

|----------------------------------------------------------------------------
|- SUB: Heal_AddSpell - Adds a spell to use at a specific heal point
|- in: heal_point -- heal point (% health) to add spell to. This must have already been created with AddHealPoint
|- in: spell_name -- spell name to add at that particular heal point
|- in: condiion -- condition to apply when cast -- make sure to wrap in ${Parse[0, ( )]}
|- in: index -- index to add spell to if not just appending to the end
|---------------------------------------------------------------------------- 
Sub Heal_AddSpell(int heal_point, string spell_name, string condition, string index)

    |- Make sure the heal point exists
    /if (${HealPoint_Map.Contains[heal_point]}) {
        /echo Error: Heal point does not exist!
        /return FALSE
    } 
    
    |- Want to make sure the spell exists and is on our bar
    /if (${spell_name.NotEqual[NULL]} && ${Me.Gem[${spell_name}]}) {
        DEBUG Adding Spell: "${heal_point}_OrderedHeal" "${spell_name}" ${Parse[0,${Parse[1,( ${condition} )]}]} ${index}
        /call AddToRotation "${heal_point}_OrderedHeal" "${spell_name}" Spell "${Parse[1,( ${condition} )]}" ${index}
    } else {
        DEBUG \arERROR:\ax Could not add ${spell_name} to "${heal_point}_OrderedHeal -- Not in a Gem."
    }

/return TRUE

|----------------------------------------------------------------------------
|- SUB: Heal_AddAA - Adds a AA to use at a specific heal point
|- in: heal_point -- heal point (% health) to add spell to. This must have already been created with AddHealPoint
|- in: aa_name -- AA name to add at that particular heal point
|- in: condiion -- condition to apply when cast -- make sure to wrap in ${Parse[0, ( )]}
|- in: index -- index to add spell to if not just appending to the end
|---------------------------------------------------------------------------- 
Sub Heal_AddAA(int heal_point, string aa_name, string condition, string index)

    |- Make sure the heal point exists
    /if (${HealPoint_Map.Contains[heal_point]}) {
        /echo Error: Heal point does not exist!
        /return FALSE
    } 
    
    |- Want to make sure the spell exists and the spell is ready, i.e., on our bar.
    /if (${aa_name.NotEqual[NULL]} && ${RG_CanUseAA[${aa_name}]}) {
        DEBUG Adding AA: "${heal_point}_OrderedHeal" "${aa_name}" ${Parse[0,${Parse[1,( ${condition} )]}]} ${index}
        /call AddToRotation "${heal_point}_OrderedHeal" "${aa_name}" AA "${Parse[1,( ${condition} )]}" ${index}
    } else {
        DEBUG \arERROR:\ax Could not add ${aa_name} to "${heal_point}_OrderedHeal. Rank is 0."
    }

/return TRUE

|----------------------------------------------------------------------------
|- SUB: Heal_AddItem - Adds an Item to use at a specific heal point
|- in: heal_point -- heal point (% health) to add spell to. This must have already been created with AddHealPoint
|- in: item_name -- Item name to add at that particular heal point
|- in: condiion -- condition to apply when cast -- make sure to wrap in ${Parse[0, ( )]}
|- in: index -- index to add spell to if not just appending to the end
|---------------------------------------------------------------------------- 
Sub Heal_AddItem(int heal_point, string item_name, string condition, string index)

    |- Make sure the heal point exists
    /if (${HealPoint_Map.Contains[heal_point]}) {
        /echo Error: Heal point does not exist!
        /return FALSE
    } 
    
    |- Want to make sure the spell exists and the spell is ready, i.e., on our bar.
    /if (${item_name.NotEqual[NULL]} && ${FindItemCount[${item_name}]} > 0) {
        DEBUG Adding Item: "${heal_point}_OrderedHeal" "${item_name}" ${Parse[0,${Parse[1,( ${condition} )]}]} ${index}
        /call AddToRotation "${heal_point}_OrderedHeal" "${item_name}" Item "${Parse[1,( ${condition} )]}" ${index}
    } else {
        DEBUG \arERROR:\ax Could not add ${item_name} to "${heal_point}_OrderedHeal. Don't have item."
    }

/return TRUE

|----------------------------------------------------------------------------
|- SUB: Heal_AutoBackFill - Automatically back fills low percentage healing points
|- with the spells added to the healing points above it. 
|-
|- Useful for macro authors to automatically back fill their healing rotations with
|- backup spells at more critical heal points.
|---------------------------------------------------------------------------- 
Sub Heal_AutoBackFill

    |-- Used to keep track of our healing points
    /declare mi_hp mapiterator local
    /vardata mi_hp HealPoint_Map.First.Clone
    
    |- Used to keep track of the healing points used in the inner loop
    /declare ordered_rotation_list string local
    /declare mi_hp_inner mapiterator local
    /declare li_rotation listiterator local
    
    |- Used to keep track of insert position into the heal ordered rotations so we maintain priority
    /declare insert_index int local
    /declare iter_insert_index int local
    
    |- Loop through the healing points
    /while (!${mi_hp.IsEnd} ) {

        |- This saves the index of where we want our highest priority backup heals to go.
        /varset insert_index ${RotationSize[${mi_hp.Value}]}
        
        |- Loop through the healing points again to add our backup spells
        /vardata mi_hp_inner HealPoint_Map.First.Clone
        /while (!${mi_hp_inner.IsEnd}) {
        
            |-- Don't re-add spells from the current level and don't add spells from lower levels
            /if ( ${mi_hp_inner.Key.NotEqual[${mi_hp.Key}]} && (${mi_hp_inner.Key} >  ${mi_hp.Key}) ) {
                |- Setup our inner loop rotation -- this list loops through the ordered spell names by priority
                /varset ordered_rotation_list ${mi_hp_inner.Value}_List
                /vardata li_rotation ${ordered_rotation_list}.First.Clone
                
                |- Reset our inner loop priority index for insertion
                /varset iter_insert_index ${insert_index}
                
                 |- Loop through the spell priority list
                /while ( !${li_rotation.IsEnd} ) {
                    |-  heal_point, spell name, condition-parsed twice->first to resolve variables-then sub return value, index to insert at
                    /call Heal_AddSpell "${mi_hp.Key}" "${li_rotation.Value}" "${Parse[2,${GetRotationCondition[${mi_hp_inner.Value},"${li_rotation.Value}"]}]}" ${iter_insert_index} 
                    
                    |- Increment our iteration index so the next spell gets inserted after the one we just added, not before
                    /varcalc iter_insert_index ${iter_insert_index}+1
                    
                    /invoke ${li_rotation.Advance}
                }
            }
            /invoke ${mi_hp_inner.Advance}
        }
        /invoke ${mi_hp.Advance}
    }
/return TRUE

|----------------------------------------------------------------------------
|- SUB: Heal_OOGCheckAndRez - Checks nearby out of group spawns and determines if
|- they should be rezzed. Only rezzes those:
|- 1. They're in our out of group assistname
|- 2. They're in our Xassist list -- STILL TO DO --
|- 3. They're in our OaList
|- 4. They're in our Raid 
|-
|---------------------------------------------------------------------------- 
Sub Heal_OOGCheckAndRez()
    /declare rezcnt int local ${SpawnCount[OUTOFGROUPREZ]}
    /declare rezcnter int local 0
    /declare tmp_corpse spawn local
    /declare tmp_corpse_name string local
    /if (${rezcnt}) {
        /for rezcnter 1 to ${rezcnt}
            /squelch /vardata tmp_corpse NearestSpawn[${rezcnter},OUTOFGROUPREZ]
            |- Splits off the 's Corpse possessive.
            /varset tmp_corpse_name ${tmp_corpse.CleanName.Arg[1,']}
            |- We can replace the below condition with ${IsPCSafe[${tmp_corpse_name}]}
            /if ( ${tmp_corpse_name.Equal[${assistname}]} || ${OaList[SETTINGVAL].Find[${tmp_corpse_name}]} || ${Raid.Member[${tmp_corpse_name}].ID} || ${DanNet.Peers.Find[${tmp_corpse_name}]}) {
                /call ${Me.Class.ShortName}_DoRez ${Spawn[pc corpse ${tmp_corpse}].ID}
                /if (${Macro.Return}) {
                    /echo \awNOTICE:\ax Just rezzed. Resetting Rez Timer to ${RetryRezDelay[SETTINGVAL]}s
                    /varset RezTimer ${RetryRezDelay[SETTINGVAL]}s
                    /return TRUE
                }                               
            }
        /next rezcnter
    }
/return FALSE

|----------------------------------------------------------------------------
|- SUB: Cure_Init - Initializes the cure systems observers and outer variables
|----------------------------------------------------------------------------
Sub Cure_Init()
    /declare Cure_Map_Abilities map outer

    |- No one else is on Dannet.
    /if (${DanNet.PeerCount} <= 1 ) {
        /echo \awNOTICE:\ax Cannot initilaize cure system. You have no DanNet peers. Restart RGMercs after checking your DanNet configuration if you need cures. 
        /return FALSE
    }

    /declare i int local 0
    /for i 1 to ${DanNet.PeerCount}
        /call DNetCreateObserver ${DanNet.Peers[${i}]} "Me.Poisoned.ID" "CureObs${Me.CleanName}_${DanNet.Peers[${i}]}_poison" string
        /call DNetCreateObserver ${DanNet.Peers[${i}]} "Me.Diseased.ID" "CureObs${Me.CleanName}_${DanNet.Peers[${i}]}_disease" string
        /call DNetCreateObserver ${DanNet.Peers[${i}]} "Me.Cursed.ID" "CureObs${Me.CleanName}_${DanNet.Peers[${i}]}_curse" string
        /call DNetCreateObserver ${DanNet.Peers[${i}]} "Me.Corrupted.ID" "CureObs${Me.CleanName}_${DanNet.Peers[${i}]}_corruption" string
    /next i 
/return TRUE

|----------------------------------------------------------------------------
|- SUB: Cure_AddCure - Adds a spell to use at a specific heal point
|- in: effect_type -- 
|- in: cure_name --
|- in: ability_type -- 
|---------------------------------------------------------------------------- 
Sub Cure_AddCure(string effect_type, string cure_name, string ability_type)
    /if (!${Select[${effect_type},disease,poison,curse,corruption]}) {
        /echo \arERROR:\ax AddCure invalid effect_type ${effect_type}
        /return FALSE
    }
    /if (!${Cure_Map_Abilities.Add[${effect_type},${cure_name}|${ability_type}]}) {
        /echo \arERROR:\ax Could not add ${cure_name}|${ability_type} to cure ${effect_type}
        /return FALSE
    }
/return TRUE

|----------------------------------------------------------------------------
|- SUB: Cure_AddAll - Adds a spell to use at a specific heal point
|- in: disease_cure --
|- in: disease_type --
|- in: poison_cure --
|- in: poison_type --
|- in: curse_cure --
|- in: curse_type --
|- in: corruption_cure --
|- in: corruption_type --
|---------------------------------------------------------------------------- 
Sub Cure_AddAll(string disease_cure, string disease_type, string poison_cure, string poison_type, string curse_cure, string curse_type, string corruption_cure, string corruption_type)
    /call Cure_AddCure "disease" "${disease_cure}" "${disease_type}"
    /call Cure_AddCure "poison" "${poison_cure}" "${poison_type}"
    /call Cure_AddCure "curse" "${curse_cure}" "${curse_type}"
    /call Cure_AddCure "corruption" "${corruption_cure}" "${corruption_type}"
/return

|----------------------------------------------------------------------------
|- SUB: CureQuery - Looks through everyone on the dannet and Queries them to see if they need a cure.
|---------------------------------------------------------------------------- 
Sub CureQuery
    |- /declare mi mapiterator local
    /declare effects string local disease,poison,curse,corruption
    /declare tmp_name string local
    /declare tmp_type string local
    /declare tmp_effect string local
    /declare tmp_recvtlostr string local
    /declare tmp_peer string local

    /declare j int local 0
    /declare i int local 0
    /for i 1 to ${DanNet.PeerCount}
        /varset tmp_peer ${DanNet.Peers[${i}]}
        /if (!${SpawnCount[pc ${tmp_peer} radius 150]}) {
            DEBUG ${DanNet.Peers[${i}]} is not within range or in zone.
            /continue
        }

        /for j 1 to ${Math.Calc[${effects.Count[,]}+1].Int}
            /if (${tmp_peer.Equal[NULL]}) {
                EDEBUG Received NULL Peer at Index ${i}
                /continue
            } 
            /varset tmp_effect ${effects.Arg[${j},,]}
            DEBUG CureNow Checking ${tmp_peer} for ${tmp_effect} [${DNetGetObserverValue[CureObs${Me.CleanName}_${tmp_peer}_${tmp_effect}]}]
            /if (!${Defined[CureObs${Me.CleanName}_${tmp_peer}_${tmp_effect}]}) {
                /echo NOTICE: Could not find Observer CureObs${Me.CleanName}_${tmp_peer}_${tmp_effect}
                /continue
            }


                    /if (${NPC${tmp_type}Ready[${tmp_name}]}) {
                        DEBUG Curing ${tmp_effect} ${tmp_name}|${tmp_type}
                        /call ${tmp_type}Now "${tmp_name}" ${Spawn[pc ${tmp_peer}].ID}
                }
                
            
        /next j
    /next i
/return


|----------------------------------------------------------------------------
|- SUB: CureNow - Looks through everyone on the dannet observers list and sees if they need a cure.
|---------------------------------------------------------------------------- 
Sub CureNow
    |- /declare mi mapiterator local
    /declare effects string local disease,poison,curse,corruption
    /declare tmp_name string local
    /declare tmp_type string local
    /declare tmp_effect string local
    /declare tmp_recvtlostr string local
    /declare tmp_peer string local

    /declare j int local 0
    /declare i int local 0
    /for i 1 to ${DanNet.PeerCount}
        /varset tmp_peer ${DanNet.Peers[${i}]}
        /if (!${SpawnCount[pc ${tmp_peer} radius 150]}) {
            DEBUG ${DanNet.Peers[${i}]} is not within range or in zone.
            /continue
        }

        /for j 1 to ${Math.Calc[${effects.Count[,]}+1].Int}
            /if (${tmp_peer.Equal[NULL]}) {
                EDEBUG Received NULL Peer at Index ${i}
                /continue
            } 
            /varset tmp_effect ${effects.Arg[${j},,]}
            DEBUG CureNow Checking ${tmp_peer} for ${tmp_effect} [${DNetGetObserverValue[CureObs${Me.CleanName}_${tmp_peer}_${tmp_effect}]}]
            /if (!${Defined[CureObs${Me.CleanName}_${tmp_peer}_${tmp_effect}]}) {
                /echo NOTICE: Could not find Observer CureObs${Me.CleanName}_${tmp_peer}_${tmp_effect}
                /continue
            }
            /if (${CureObs${Me.CleanName}_${tmp_peer}_${tmp_effect}.Length} == 0) {
                /echo \awNOTICE: CureObs${Me.CleanName}_${tmp_peer}_${tmp_effect} returned 0 length
        		/call PrintGroupMessage "\arDanNet Broke\ax \awReloading DanNet and Ending Macro -- RESTART ME NOW!!!\ax"
                /call UnCheckPlugin "mq2dannet"
                /delay 30
                /call CheckPlugin "mq2dannet"
                /delay 2s ${DanNet.PeerCount}
                /continue
            }
            /if (${DNetGetObserverValue[CureObs${Me.CleanName}_${tmp_peer}_${tmp_effect}]}) {
                /if (${Cure_Map_Abilities.Contains[${tmp_effect}]}) {
                    /varset tmp_name ${Cure_Map_Abilities.Find[${tmp_effect}].Value.Arg[1,|]}
                    /varset tmp_type ${Cure_Map_Abilities.Find[${tmp_effect}].Value.Arg[2,|]}
                    DEBUG ${tmp_peer} needs a cure for ${tmp_effect}
                    /if (${NPC${tmp_type}Ready[${tmp_name}]}) {
                        DEBUG Curing ${tmp_effect} ${tmp_name}|${tmp_type}
                        /call ${tmp_type}Now "${tmp_name}" ${Spawn[pc ${tmp_peer}].ID}
                    }
                }
            }
        /next j
    /next i
/return

|----------------------------------------------------------------------------
|- SUB: HealNow - Chooses and casts a healing spell based on available healing spells and the current health of the target.
|- This algorithm will choose the highest heal_point that is less than the targets health checked at the start of the function. This means a heal WILL ALWAYS BE CAST if HealNow is called.
|- in: target_id - Spawn ID of our target
|-
|- NOTE: The reason we do not pass a health value to this function is to delay the calculation of health for as long as possible
|- so we cast the most effective heal possible upon the spell cast
|---------------------------------------------------------------------------- 
Sub HealNow(int target_id)
    
    /if (!${target_id}) {
        DEBUG HealNow Received target_id of 0 (${target_id}) RETURNING
        /return FALSE
    }

    |- Calculate the spawn health
    /declare target_health int local ${Spawn[id ${target_id}].PctHPs}
    
    |- DEBUG Healing ${target_id} [${Spawn[id ${target_id}].Name}] ==> ${target_health}
    
    |- Loop through the HealPoint Map to determine our most effective heal rotation -- pull out it's name
    /declare mi mapiterator local
    /vardata mi HealPoint_Map.First.Clone
    
    |- We keep track of the current rotation name each iteration and break out when we've passed the lowest health point.
    |- Default values are the lowest HP healpoint and its associated rotation name
    /declare rotation_name string local ${mi.Value}
    /declare heal_point int local ${mi.Key}
    
    |- MQ2 whiles will always execute once even if you're already at the end
    /while (!${mi.IsEnd} ) {
        |- Making a note there's a potential benefit to updating the target's HP in this loop
        
        |- Here we want to update the healing rotation we will use to make sure two requirements hold:
        |- 1. We are casting the most optimal rotation for the targets health
        |- 2. We only cast rotations that actually have available spells even if it is not the most optimal rotation
        /if ( (${mi.Key} < ${target_health}) ) {
            |- We only want to update our rotation if it has spells in it, it's possible none of the heals were on the bar when
            |- we added them to the rotation.
            |- DEBUG ${rotation_name} Size: ${RotationSize[${rotation_name}]} 
            /if ( ${RotationSize[${mi.Value}]} ) {            
                /varset rotation_name ${mi.Value}
                /varset heal_point ${mi.Key}
            }
        } else {
            /break
        }
        /invoke ${mi.Advance}
    }
    
    |- Set our target if we haven't already
    |- /call SetTarget ${target_id}
    
    |- Cast our rotation
    |- DEBUG Calling rotation "${rotation_name}" On ${target_id} [${target_health}%HP] -- Current Target ${Target.Name} [${Target.ID}] -- ${heal_point}
    
    /if ( ${RotationSize[${rotation_name}]} ) {
        DEBUG Calling rotation "${rotation_name}" On ${target_id} [${target_health}%HP] -- Current Target ${Spawn[id ${target_id}].Name} [${Target.ID}] -- ${heal_point} -- Range Check: (${Spawn[id ${target_id}].Distance}<${AssistRange[SETTINGVAL]})
        |- If we're assisting outside and our main assist is too low level, we may not be able to heal their group effectively
        |- because of spell too powerful outcomes. We don't want to always spend the horsepower on these checks, however,
        |- thus the following gate.
        /if (${AssistOutside[SETTINGVAL]} && ${Spawn[id ${assistid}].Level} <= 65) {
            |- The IsSpellTooPowerful condition needs to apply only if we're casting a spell thus the type check. AA's could cause
            |- and incorrect return and a spell not to be cast. This would be bad. 
            /call Ordered_Rotation_Follow "${rotation_name}" ${target_id} ${Parse[0,"(${Spawn[id ${target_id}].Distance}<${AssistRange[SETTINGVAL]} && (!${IsSpellTooPowerful[${mi.Key},${Spawn[id ${target_id}].Level}]} && ${mi_type.Value.Equal[Spell]}) )"]} 0 "heal"
        } else {
            /call Ordered_Rotation_Follow "${rotation_name}" ${target_id} ${Parse[0,"(${Spawn[id ${target_id}].Distance}<${AssistRange[SETTINGVAL]} )"]} 0 "heal"

        }
    } else {
        DEBUG Error: No spell rotation has an available healing spell.
        /return FALSE
    }
/return ${Macro.Return}

|----------------------------------------------------------------------------
|- SUB: WorstHurtMana - Reports back Group member With least mana. - used for things Like Necro mana Tap and Quiet Prayer on clerics.
|- in: min_health_loss - This function will return false unless someone in the group has strictly LESS THAN this amount of heal
|-                          Note -> min_health_loss should be strictly LESS THAN your highest heal point
|- out: ${worsthurt_id} -- Returns the Spawn ID of the worst hurt
|---------------------------------------------------------------------------- 
Sub WorstHurtMana(int min_mana_loss)
    /declare worsthurt_id int local 0
    /declare worstpct int local ${min_mana_loss}
    
    /declare i int local 0
    /for i 0 to ${Group.Members}
        
        |- Special handling of All Non mana Based Classes

        /if (${Select[${Group.Member[${i}].Class.ShortName},BER,WAR,MNK,ROG,BRD]}) {
            /continue
        }

        /if ( (${Group.Member[${i}].PctMana} < ${worstpct}) && !${Group.Member[${i}].Hovering} && !${Group.Member[${i}].Dead}) {
            /varset worstpct ${Group.Member[${i}].PctMana}
            /varset worsthurt_id ${Group.Member[${i}].ID}
            
        }
    /next i
/return ${worsthurt_id}

|----------------------------------------------------------------------------
|- SUB: WorstHurtGroup - Chooses and casts a healing spell based on available healing spells and the current health of the target.
|- in: min_health_loss - This function will return false unless someone in the group has strictly LESS THAN this amount of heal
|-                          Note -> min_health_loss should be strictly LESS THAN your highest heal point
|- out: ${worsthurt_id} -- Returns the Spawn ID of the worst hurt
|---------------------------------------------------------------------------- 
Sub WorstHurtGroup(int min_health_loss)
    /declare worsthurt_id int local 0
    /declare worstpct int local ${min_health_loss}
    
    /declare i int local 0
    /for i 0 to ${Group.Members}
        
        |- Special handling of zerkers for rage
        /if (${Group.Member[${i}].Class.ShortName.Equal[BER]}) {
            /if (${SkipZerker[${Group.Member[${i}].ID}]}) /continue
        }

        /if ( (${Group.Member[${i}].PctHPs} < ${worstpct}) && !${Group.Member[${i}].Hovering} && !${Group.Member[${i}].Dead}) {
            /varset worstpct ${Group.Member[${i}].PctHPs}
            /varset worsthurt_id ${Group.Member[${i}].ID}
        }    
            |- Add a pet check
        /if (${DoPetHeals[SETTINGVAL]} && ${Group.Member[${i}].Pet.ID}) {
            /if (${Group.Member[${i}].Pet.PctHPs} < ${worstpct}) {
                /varset worstpct ${Group.Member[${i}].Pet.PctHPs}
                /varset worsthurt_id ${Group.Member[${i}].Pet.ID}
            }
        }
        
    /next i
/return ${worsthurt_id}

|----------------------------------------------------------------------------
|- SUB: WorstHurtXT - Chooses and casts a healing spell based on available healing spells and the current health of the target. Looks through the xtarget list.
|- in: min_health_loss - This function will return false unless someone in the group has strictly LESS THAN this amount of heal
|-                          Note -> min_health_loss should be strictly LESS THAN your highest heal point
|- out: ${worsthurt_id} -- Returns the Spawn ID of the worst hurt
|---------------------------------------------------------------------------- 
Sub WorstHurtXT(int min_health_loss)
    /declare worsthurt_id int local 0
    /declare worstpct int local ${min_health_loss}
    /declare petHPs int local
    
    /declare i int local 0
    |- We will always go through the full set in case mq2xassist numbers aren't starting at 1.
    /for i 1 to ${Me.XTargetSlots}
        /if (${Me.XTarget[${i}].Type.Equal[PC]}) {
            DEBUG Slot ${i}[ID: ${Me.XTarget[${i}].ID}] -- Type: ${Me.XTarget[${i}].Type} -- HPs: ${Me.XTarget[${i}].PctHPs}
            /if (${Me.XTarget[${i}].Class.ShortName.Equal[BER]}) {
                /if (${SkipZerker[${Me.XTarget[${i}].ID}]}) /continue
            }   

            /if ( (${Me.XTarget[${i}].PctHPs} < ${worstpct}) && !${Me.XTarget[${i}].Hovering} && !${Me.XTarget[${i}].Dead}) {
                /varset worstpct ${Me.XTarget[${i}].PctHPs}
                /varset worsthurt_id ${Me.XTarget[${i}].ID}
            }        

            |- Add a pet check
            /if (${Me.XTarget[${i}].Pet.ID} > 0) {
                /if (${DNIsPeer[${Me.XTarget[${i}].Name}]}) {
                    /call DNetPetHps ${Me.XTarget[${i}].Name}
                    /varset petHPs ${Macro.Return}

                    /if (${petHPs} && ${petHPs} < ${worstpct}) {
                        /varset worstpct ${petHPs}
                        /varset worsthurt_id ${Me.XTarget[${i}].Pet.ID}
                    }
                }
            }
        }            
        
    /next i
    DEBUG WorstHurtXT returning ${Spawn[id ${worsthurt_id}].CleanName}[${worsthurt_id}]
/return ${worsthurt_id}

|----------------------------------------------------------------------------
|- SUB: SkipZerker - Determines if a zerker should be skipped. Pulled this out as a seperate sub as it will be used across worst hurts.
|- in: member - Groupmember object of the zerker in question
|- out: TRUE if we shouldn't heal the zerker, FALSE if they should be looked at
|---------------------------------------------------------------------------- 
Sub SkipZerker(spawn member)
    |- 89% is the worst case HP for zerkers with their abilities going so we start there.
    |- Setting 85% based on old cleric/shm heal points and to make sure when they get healed there's less
    |- of a chance they'll jump too far above 89%
    |- Open Wounds starts at 96 with ritual sacrification at 106.

    /if (${member.PctHPs} >= ${ZerkIgnoreHP[SETTINGVAL]} &&${member.Level} >= 96) {
        /return TRUE
    }
/return FALSE