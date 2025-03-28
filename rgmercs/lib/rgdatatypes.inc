|- RGdatatypes.inc
|- 
|- This file contains the wrappers for creating, deleting, and modifying
|- the "Classes"/"Objects" that RG uses in its various macros.
|- This is kept seperate from RGsubs as the Subroutines in this file all
|- have data type creation in common.

|-######################################################################################
|----------------------------------------------------------------------------
|- SUB: AbilitySet_New
|- Creates the underlying variables for a new ability set.
|---------------------------------------------------------------------------- 

Sub AbilitySet_New(string name_abilityset, bool is_aura)
    /if (${Defined[${name_abilityset}_AbilitySet]}) /return FALSE
    |- Setting default value to NULL so spell variables can be used for certain conditions checks within spell bar setups.
    /declare ${name_abilityset}_AbilitySet  set  outer
    /if (${is_aura}) /declare ${name_abilityset}_AuraMap map outer
/return TRUE

|----------------------------------------------------------------------------
|- SUB: AbilitySet_Add -- Add an ability to an ability set.
|---------------------------------------------------------------------------- 
Sub AbilitySet_Add(string abilityname, string setname)
    /if (${abilityname.Equal[NULL]}) /return FALSE 

    /declare abilityset string local ${setname}_AbilitySet
    
    |- Store the spell in our set
    /if (!${${abilityset}.Contains[${abilityname}]}) {
        /if (!${${abilityset}.Add[${abilityname}]}) {
            /echo \ar FAILED Adding ${abilityname} to ${abilityset}
            /return FALSE
        }
        DEBUG Adding ${abilityname} to ${abilityset}   
    } else {
        |- Set already contains our item
        /return FALSE
    }
/return TRUE

|----------------------------------------------------------------------------
|- SUB: AbilitySet_AddAura -- Add an aura and its associated aura name to a set.
|---------------------------------------------------------------------------- 
Sub AbilitySet_AddAura(string abilityname, string auraname, string setname)
    /if (!${Defined[${setname}_AuraMap]}) {
        /echo \arERROR:\ax ${setname} is not an aura set. Use AbilitySet_Add.
        /return FALSE
    }
    /call AbilitySet_Add "${abilityname}" "${setname}"
    /if (!${Macro.Return}) /return FALSE

    /if (!${${setname}_AuraMap.Add[${abilityname},${auraname}]}) {
         /echo \ar FAILED Adding Aura Name ${auraname} to ${abilityset}
        /return FALSE       
    }

    DEBUG Adding ${abilityname} [${auraname}] to ${setname} 

/return TRUE

|----------------------------------------------------------------------------
|- SUB: GetAuraName -- Returns an aura name associated with an ability set (aura)
|---------------------------------------------------------------------------- 
Sub GetAuraName(string abilityname, string setname)
    /declare auramap string local ${setname}_AuraMap
    /if (!${Defined[${auramap}]}) {
        /echo \arERROR:\ax ${setname} is not an aura set.
        /return NULL
    }
    /if (!${${auramap}.Contains[${Spell[${abilityname}].BaseName}]}) /return NULL

    /declare mi mapiterator local
    /vardata mi ${auramap}.Find[${Spell[${abilityname}].BaseName}]
/return ${mi.Value}

|**
|----------------------------------------------------------------------------
|- SUB: AbilitySet_ChooseOuter -- works for CombatAbilities too!
|- abilityvar - ability variable name to create and fille
|- abilityset - Ability set object to use.
|- ignore_str - | seperated string of spell names to ignore
|---------------------------------------------------------------------------- 
**|
Sub AbilitySet_ChooseOuter(string abilityvar, string abilityset, string ignore_str)
    /declare curmaxspellvl  int         local 0
    /declare tmpspelllvl    int         local 0
    /declare caplevel	    int         local 0
    /declare tmpspellrank   string      local NULL

    |- Create New Ability Outer if it doesn't already exist
    /if (!${Defined[${abilityvar}]}) /declare ${abilityvar} string      outer NULL
    
    /declare setiter        setiterator local
    /vardata setiter ${abilityset}_AbilitySet.First.Clone  
    
    |- List of spells to ignore when searching for best spell.
    /declare ls_ignore list local
    /invoke ${ls_ignore.Delimiter[|]}
    /if ( ${ignore_str.Length} ) {
        /invoke ${ls_ignore.Append["${ignore_str}"]}
    }
     
    |- Iterate throught the spell set
    /while (!${setiter.IsEnd}) {
        /varset tmpspelllvl ${Spell[${setiter.Value}].Level}
        /varset tmpspellrank ${Spell[${setiter.Value}].RankName}
	/varset caplevel ${Me.Level}
        
        |- Detect mispelled spells
        /if (${setiter.Value.NotEqual[NULL]} && ${tmpspellrank.Equal[NULL]}) {
            /echo \ar MISPELLED SPELL: \ax [${abilityvar}] => ${setiter.Value}
        }
        
        /if (!(${ls_ignore.Contains[${Spell[${tmpspellrank}].BaseName}]} || ${ls_ignore.Contains[${Spell[${tmpspellrank}].RankName}]})) {
            |- If we can cast the spell and its in our book or a valid combat ability for us, see if we should set its
            /if ( ${RGLevel[SETTINGVAL]} >= ${tmpspelllvl} && ${tmpspelllvl} <= ${caplevel}) {
                /if ((${Me.Book[${tmpspellrank}]} || ${Me.CombatAbility[${tmpspellrank}]})) {
                    |- If it's lower than the spell we've already set, ignore.
                    /if (${tmpspelllvl} > ${curmaxspellvl}) {
                        |- This is the value we use for casting and buff checking so must be BaseName. RankName is only
                        |- for memorization and Me.Book checking.
                        /if (${Me.SpellRankCap} > 1) {
                            /varset ${abilityvar} ${Spell[${tmpspellrank}].RankName}
                        } else {
                            /varset ${abilityvar} ${Spell[${tmpspellrank}].BaseName}
                        }
                        /varset curmaxspellvl ${tmpspelllvl}
                    }
                } else {
                    |- Get spells from two eras back if they're missing.
                    /if (${tmpspelllvl} > ${Math.Calc[ ${RGLevel[SETTINGVAL]} - 10 ]}) {
                		/call PrintGroupMessage "${Me.Name} \aw [${abilityvar}] \ax \ar MISSING SPELL \ax -- \ag ${tmpspellrank} \ax -- \aw LVL: ${tmpspelllvl} \ax"
                    }
                }
            }
        }
        /invoke ${setiter.Advance}
    }
/return TRUE

|----------------------------------------------------------------------------
|- SUB: ItemSet_New -- Create an ItemSet to hold a list of item names to choose from.
|---------------------------------------------------------------------------- 
Sub ItemSet_New(string itemset_name)
    /declare ${itemset_name}_ItemSet  set  outer
/return TRUE

|----------------------------------------------------------------------------
|- SUB: ItemSet_Add -- Add an item name to an ItemSet.
|---------------------------------------------------------------------------- 
Sub ItemSet_Add(string item_name, string itemset_name)
    /if (${item_name.Equal[NULL]}) /return FALSE 
    
    /declare item_set string local ${itemset_name}_ItemSet
    
    |- Store the spell in our set
    /if (!${${item_set}.Add[${item_name}]}) {
        /echo \ar FAILED Adding ${item_name} to ${item_set}
        /return FALSE
    }  
/return TRUE

|----------------------------------------------------------------------------
|- SUB: ItemSet_ChooseOuter -- Choose the highest level item you have in your inventory
|- from the item set.
|- DO NOT USE WITH SUMMONED ITEMS.
|---------------------------------------------------------------------------- 
Sub ItemSet_ChooseOuter(string itemvar, string itemset_name, string ignore_str)
    /declare curmaxitemlvl  int         local 0
    /declare tmpitemlevel   int         local 0
    /declare tmpitemname    string      local NULL

    |- Create New Ability Outer if it doesn't already exist
    /if (!${Defined[${itemvar}]}) /declare ${itemvar} string      outer NULL
    
    /declare setiter        setiterator local
    /vardata setiter ${itemset_name}_ItemSet.First.Clone  
    
    |- List of spells to ignore when searching for best spell.
    /declare ls_ignore list local
    /invoke ${ls_ignore.Delimiter[|]}
    /if ( ${ignore_str.Length} ) {
        /invoke ${ls_ignore.Append["${ignore_str}"]}
    }
     
       |- Iterate throught the spell set
    /while (!${setiter.IsEnd}) {
        |- If we don't have the item, we skip it
        /if (${FindItemCount[=${setiter.Value}]}) {
            |- If we do have the item, we'll make sure it's the best we have.
            /varset tmpitemlevel ${FindItem[=${setiter.Value}].RequiredLevel}
            /varset tmpitemname ${setiter.Value}
            
            /if (!(${ls_ignore.Contains[${tmpitemname}]})) {
                |- Make sure we meet the items required level
                /if ( ${Me.Level} >= ${tmpitemlevel} ) {
                    |- If it's lower than the item we've already set, ignore.
                    /if (${tmpitemlevel} > ${curmaxitemlvl}) {
                        /varset ${itemvar} ${tmpitemname}
                        /varset curmaxitemlvl ${tmpitemlevel}
                    }
                }
            }
        }
        /invoke ${setiter.Advance}
    }
         
/return TRUE

|- ######################################################################################

|----------------------------------------------------------------------------
|- SUB: OrderedRotation_New
|- Creates the underlying variables for a new ordered rotation. This can be used
|- with the Ordered_Rotation line of functions. You can use AddToRotation with this
|- data type as well.
|- in:rotation_name - Name of the rotation you will use
|---------------------------------------------------------------------------- 
Sub Ordered_Rotation_New(string rotation_name)
    |- ability => condition
    /declare ${rotation_name}_Map       map outer
    |- ability => type
    /declare ${rotation_name}_Type_Map   map outer
    |- Tracks priority of the abilities.
    /declare ${rotation_name}_List      list outer
    
    /invoke ${${rotation_name}_List.Delimiter[|]}
    /declare ${rotation_name}_List_Iter listiterator outer
    /vardata ${rotation_name}_List_Iter ${rotation_name}_List.First.Clone
/return

|----------------------------------------------------------------------------
|- SUB: Ordered_Rotation_Clear -- Clears a rotation provided.
|- rotation_name: Name of the rotation to print out
|----------------------------------------------------------------------------
Sub Ordered_Rotation_Clear(string rotation_name)
    /invoke ${${rotation_name}_Map.Clear}
    /invoke ${${rotation_name}_Type_Map.Clear}
    /invoke ${${rotation_name}_List.Clear}
    /vardata ${rotation_name}_List_Iter ${rotation_name}_List.First.Clone
/return

|----------------------------------------------------------------------------
|- SUB: Ordered_Rotation_Delete -- Deletes the rotation provided by rotation_name
|- rotation_name: Name of the rotation to print out
|----------------------------------------------------------------------------
Sub Ordered_Rotation_Delete(string rotation_name)
    /deletevar ${rotation_name}_Map
    /deletevar ${rotation_name}_Type_Map
    /deletevar ${rotation_name}_List
    /deletevar ${rotation_name}_List_Iter
/return

|----------------------------------------------------------------------------
|- SUB: Ordered_Rotation_Print -- Prints out the elements of an ordered rotation in cast order.
|- rotation_name: Name of the rotation to print out
|----------------------------------------------------------------------------
Sub Ordered_Rotation_Print(string rotation_name)
    /if (!${Defined[${rotation_name}_List]}) {
        /echo ${rotation_name} does not exist.
        /return FALSE
    }
    /if (!${${rotation_name}_List.Count}) {
        /echo ${rotation_name} empty.
        /return FALSE
    }
    /declare li listiterator local NULL
    /vardata li ${rotation_name}_List.First.Clone

    /declare idx int local 1
    /while (!${li.IsEnd}) {
        /echo \ag${idx}.. \ax\aw${li.Value}\ax
        /varcalc idx ${idx}+1
        /invoke ${li.Advance}
    }
/return 

|----------------------------------------------------------------------------
|- SUB: AddToRotation -- 
|- rotation_name: Name of the Rotation to add the item to.
|- cast_item: Name of spell or disc. ID of the AA. Do not store different types of actions in the
|- cast_type: AA,Spell,Ability,Disc,Item,Song
|- same rotation. Keep spells with spells, AAs with AAs, etc...
|- condition: Condition to test in the DPS or buff routine.
|- index: Only used if rotation_name is an ordered rotation. Inserts the cast_item at the 'index' in the rotation. 0 being first.
|----------------------------------------------------------------------------
Sub AddToRotation(string rotation_name, string cast_item, string cast_type, string condition, string index) 
    DEBUG Adding ${cast_item} [${cast_type}] to ${rotation_name} @ ${index}
    /if (${cast_item.Equal[NULL]}) {
        /return FALSE
    }

    |- Declares for values that can be used in conditions but values/real definitions are local to the Rotation functions only.
    /declare mi mapiterator local NULL
    /declare target_id int local 0
    /declare cannotUseAA  bool local FALSE

    /if (${condition.Length} < 1) {
        /echo \ar Missing condition on ${rotation_name} [${cast_item}] -- setting to TRUE.\ax
        /varset condition TRUE
    }
    /if (!${Select[${cast_type},AA,Spell,Ability,Disc,Item,Song,Command]}) {
        /echo \ar ERROR: Could not add ${cast_item} to ${rotation_name} --> bad cast_type: ${cast_type}\ax
        /return FALSE
    }

    |- Check to make sure Command types start with a /
    /if (${cast_type.Equal[Command]}) {
        /if (${cast_item.Left[1].NotEqual[/]}) {
            /echo ERROR: Commands must start with a '/'
            /return FALSE
        }
    }
	| we check the AA can be used
    /if (${cast_type.Equal[AA]}) {
      /varcalc cannotUseAA ${RG_CanUseAA[${cast_item}]} == FALSE
        /if (${cannotUseAA}) {
            /echo cannot use  AA ${cast_item}
            /return FALSE
        }
    }


    |- Force a test of the condition on load to check for syntax errors
    /if (${condition}) {
        |- We've forced the condition to evaluate by this point so it shouldn't be an issue
    }
    
    |- The map stores the spells and their conditions.
    |- The list stores the order of the spells.
    /declare rotationMap string local ${rotation_name}_Map
    /declare rotationTypeMap string local ${rotation_name}_Type_Map
    /declare rotationList string local ${rotation_name}_List
    
    |- Parse[1 -- This parses ${condition} so that it resolves to the original
    |- condition string we passed in, but will not continue to parse the condition
    |- string.
    /if (!${${rotationMap}.Add[${cast_item},"${Parse[1,${condition}]}"]}) {
        /echo Could not add ${cast_item} to ${rotationMap}
        /return FALSE
    }
    /if (!${${rotationTypeMap}.Add[${cast_item},${cast_type}]}) {
        /echo Could not add ${cast_item} to ${rotationTypeMap}
        /return FALSE
    }
    
    |- Check to see if we have a list for the rotation. I'm assuming not all rotations will have
    |- lists because we don't care the order for buffs but we may for DPS Spells.
    /if (${Defined[${rotationList}]}) {
        /if (${index.Length}) {
            DEBUG Inserting ${cast_item} at ${index}
            /if ( !${${rotationList}.Insert["${index}","${cast_item}"]} ) {
                /echo Could not add ${cast_item} to ${rotationList} at slot ${index}
                /return FALSE
            }
        } else {
            |- Not an insert, just an append
            /if ( !${${rotationList}.Append["${cast_item}"]} ) {
                /echo Could not add ${cast_item} to ${rotationList}
                /return FALSE
            }
        }
    }

/return TRUE

|----------------------------------------------------------------------------
|- SUB: IsInRotation -- 
|- rotation_name: Name of the Rotation to check
|- action_name: Name of the item to check for
|-
|- Returns TRUE if action existed in the rotation, false if otherwise.
|----------------------------------------------------------------------------
Sub IsInRotation(string rotation_name, string action_name)
    /if (${${rotation_name}_Map.Contains[${action_name}]}) /return TRUE
/return FALSE

|----------------------------------------------------------------------------
|- SUB: ClearRotation -- 
|- rotation_name: Name of the Rotation to add the item to.
|-
|- This subroutine clears a rotation. If it's an ordered rotation also clears the
|- associated list. This will allow a safe changing of a rotation without having to
|- restart the macro.
|----------------------------------------------------------------------------
Sub ClearRotation(string rotation_name)
    /if (${rotation_name.Equal[NULL]}) {
        /return FALSE
    }

    |- The map stores the spells and their conditions.
    |- The list stores the order of the spells.
    /declare rotationMap string local ${rotation_name}_Map
    /declare rotationTypeMap string local ${rotation_name}_Type_Map
    /declare rotationList string local ${rotation_name}_List
    /declare rotationLI listiterator local ${rotation_name}_List_Iter
    
    |- Clear the map and the list if the list is defined because
    |- it's an ordered rotation
    /invoke ${${rotationMap}.Clear}
    /invoke ${${rotationTypeMap}.Clear}
    /if (${Defined[${rotationList}]}) {
        /invoke ${${rotationList}.Clear}
        |- To be safe also reset the list iterator as we know we know one must
        |- have been created as this is an Ordered Rotation
        /vardata ${rotationLI} ${rotationList}.First
    }
/return

|----------------------------------------------------------------------------
|- SUB: RotationSize -- Returns # of items in a rotation
|----------------------------------------------------------------------------
Sub RotationSize(string rotation_name)
    /declare rotationMap string local ${rotation_name}_Map
/return ${${rotationMap}.Count}

|----------------------------------------------------------------------------
|- SUB: GetRotationCondition -- Returns condition of the provided rotation_name
|----------------------------------------------------------------------------
Sub GetRotationCondition(string rotation_name, string item_name) 
    /declare rotationMap string local ${rotation_name}_Map
    /declare mi mapiterator local
    /vardata mi ${rotationMap}.Find[${item_name}]
    
    |- We parse once to resolve mi.Value to the underlying string but not fully resolve the condition it represents
/return ${Parse[1,${mi.Value}]}

Sub GetRotationType(string rotation_name, string item_name)
    /declare rotationTypeMap string local ${rotation_name}_Type_Map
    /declare mi mapiterator local
    /vardata mi ${rotationMap}.Find[${item_name}]
/return ${mi.Value}

|- ######################################################################################

|----------------------------------------------------------------------------
|- SUB: ChatBegList_New -- Creates a ChatBegList data type for use with ChatBegList functions. 
|----------------------------------------------------------------------------
Sub ChatBegList_New(string chatbeglist_name)
    /declare ${chatbeglist_name}_Map map outer
/return

|----------------------------------------------------------------------------
|- SUB: ChatBegList_New -- Add a new chat trigger to a ChatBegList
|- Arguments:
|- chatbeglist_name -- name of the structure passed to ChatBegList_New
|- trigger -- single word trigger that will be checked against in the proc functions
|- type -- AA, Item, Spell, Disc (Maps to the *Now functions in RGsubsV2)
|- ability -- Name of the AA, Item, Spell, or Disc to use when triggered
|- target_type -- sender [target the person who sent the message], senderpet [target the pet of the person who sent the message]
|- condition -- a condition to check when triggered -- can't use Target TLO based conditions. 
|----------------------------------------------------------------------------
Sub ChatBegList_Add(string chatbeglist_name, string trigger, string _type, string ability, string target_type, string condition)
    /declare begmap string local ${chatbeglist_name}_Map
    /declare data_array string local ${chatbeglist_name}_${trigger}_Array

    /if (!${${begmap}.Contains[${trigger}]}) {
        |- Map doesn't contain our trigger so lets create a new array and populate the info
        /if (!${Defined[${data_array}]}) /declare ${data_array}[4] string outer
        
        |- 1 -- Type
        /varset ${data_array}[1] ${_type}
        |- 2 -- Ability Name
        /varset ${data_array}[2] ${ability}
        |- 3 -- Target Type "Enum"
        /varset ${data_array}[3] ${target_type}
        |- 4 -- condition -- must Parse once to retrieve the passed variable text but anymore parsing ruins the condition
        /varset ${data_array}[4] ${Parse[1,${condition}]}
        
        /if (!${${begmap}.Add[${trigger},${data_array}]}) {
            |- Map add failed so delete the array we created
            /echo \ar CHATBEGLIST_ADD FAILED
            /deletevar ${data_array}
        }
        
    } else {
        |- Map already contains our trigger so we'll just update our array
        |- 1 -- Type
        /varset ${data_array}[1] ${_type}
        |- 2 -- Ability Name
        /varset ${data_array}[2] ${ability}
        |- 3 -- Target Type "Enum"
        /varset ${data_array}[3] ${target_type}
        |- 4 -- condition -- must Parse once to retrieve the passed variable text but anymore parsing ruins the condition
        /varset ${data_array}[4] ${Parse[1,${condition}]}
    }
/return

|----------------------------------------------------------------------------
|- SUB: ChatBegList_Proc -- Execute an ability specified in the chat_text
|- chatbeglist_name - variable name created with ChatBegList_New
|- chat_text - single word chat_text to trigger one
|- target_id - spawn ID of the character who sent the chat_text -- leveraged for condition checks so changing this variable name can and will break someone's chatbeg conditions. Yes I know this is fragile and could be done better. - Dr. Whom
|----------------------------------------------------------------------------
Sub ChatBegList_Proc(string chatbeglist_name, string chat_text, int target_id)
    /declare begmap string local ${chatbeglist_name}_Map
    
    |- Handles the MQ2 bug of chat events on FV having extra characters.
    /if (${chat_text.Find[']}) {
        /if (${chat_text.Arg[2,'].NotEqual[NULL]}) {
            /varset chat_text ${chat_text.Arg[2,']}
        } else {
            /varset chat_text ${chat_text.Arg[1,']}
        }
    }

    DEBUG BegList Proc: ${chat_text}
    /if (${${begmap}.Contains[${chat_text}]}) {
        |- our chatbeglist contains our trigger text, need to execute it
        |- First we need to get our data array
        /declare data_array string local ${chatbeglist_name}_${chat_text}_Array
        /declare proctarget int local 0
        DEBUG BegList Proc Condition: ${${data_array}[4]}
        |- Make sure the condition is true and we'll execute
        /if (${${data_array}[4]}) {
            |- Set our target based on target_type. Current valid types are sender and
            |- senderpet. Further types could be added to this else if.
            /if (${${data_array}[3].Equal[sender]}) {
                /varset proctarget ${target_id}
            } else /if (${${data_array}[3].Equal[senderpet]}) {
                /varset proctarget ${Spawn[id ${target_id}].Pet.ID}
            } else {
                /echo \ar ERROR: No Chat beg target type passed. Yell at the devs.
                /return FALSE
            }
            
            DEBUG BegList Proc Target: ${${data_array}[3]} --> ${proctarget} [${Spawn[id ${proctarget}].Name}]
            
            |- Override current DoAutoTarget to make sure we target for proc buffs
            /declare old_autotarget int local ${DoAutoTarget[SETTINGVAL]}
            /varset DoAutoTarget[SETTINGVAL] 1

            |- Now to use the appropriate ability on our target
            /declare actionsub string local ${${data_array}[1]}Now
            /if (${${data_array}[1].Equal[AA]}) {
                DEBUG Casting ${${data_array}[3]} [${Me.AltAbility[${${data_array}[2]}].ID}] --> ${proctarget} [${Spawn[id ${proctarget}].Name}]
                /call ${actionsub} ${Me.AltAbility[${${data_array}[2]}].ID} ${proctarget}
            } else {
                DEBUG Casting ${${data_array}[3]} [${${data_array}[2]}] --> ${proctarget} [${Spawn[id ${proctarget}].Name}]
                /call ${actionsub} "${${data_array}[2]}" ${proctarget}
            }

            /varset DoAutoTarget[SETTINGVAL] ${old_autotarget}
        }
    }
/return

|- ######################################################################################
|- BuffCheckArray
|- [1] Buff Name
|- [2] Class List
|- [3] Caster Condition Check
|- [4] Buff Tag Attribute -- Used to force "single" vs. "dual" if a buff has triggers
|-      Valid Tags: single -- Force a non-trigger check
|-                  dual -- Force a trigger check
|-                  ALL -- Perform the default
|----------------------------------------------------------------------------
|- SUB: BuffGroup_Init -- Declare and initialize the BuffCheckArray for buffing groups & xtargets
|- buff_cnt -- # of buffs you will want to set and cast for buffing the group
|----------------------------------------------------------------------------
Sub BuffGroup_Init (int buff_cnt)
    /if (${Defined[BuffCheckArray]}) {
        /if (${BuffCheckArray.Size[1]} != ${buff_cnt}) {
            /deletevar BuffCheckArray
            /declare BuffCheckArray[${buff_cnt},4] string outer ALL
        }
    } else {
        |- We default fill with ALL to alllow for the classlist arg in BuffGroup_Set
        |- to be optional
        /declare BuffCheckArray[${buff_cnt},4] string outer ALL
    }
/return TRUE

|----------------------------------------------------------------------------
|- SUB: BuffGroup_Set -- Set a buff spell and optional short class name restrictions. DOES NOT SUPPORT UNITY BUFFS such as Cleric's high level HP buffs.
|- buff_idx -- Buff slot to save spell to. This must be less than or equal too the buff_cnt in BuffGroup_Init
|- spellname -- Name of the spell to save
|- classlist -- (OPTIONAL) Comma delimited list of class shortnames to check when casting the buff. Won't cast if they aren't one of the specified classes.
|- condition -- (OPTIONAL) Conditions for the CASTER to CAST the buff.
|----------------------------------------------------------------------------
Sub BuffGroup_Set (int buff_idx, string spellname, string classlist, string condition, string tag)
    /varset BuffCheckArray[${buff_idx},1]  ${Spell[${spellname}].RankName}
    |- classlist is an optional argument
    /if ( ${classlist.Length} ) {
        /varset BuffCheckArray[${buff_idx},2]  ${classlist}
    }
    
    /if ( ${condition.Length} ) {
        |- Need to parse once to parse the argument to the subroutine
        /varset BuffCheckArray[${buff_idx},3] "${Parse[1,( ${condition} )]}"
    } else {
        /varset BuffCheckArray[${buff_idx},3] TRUE
    }

    /if ( ${tag.Length} ) /varset BuffCheckArray[${buff_idx},4] ${tag}
/return TRUE

|----------------------------------------------------------------------------
|- SUB: BuffGroup_GetSpell -- Return the spell name associated with a buff slot
|- buff_idx -- index of a spell
|----------------------------------------------------------------------------
Sub BuffGroup_GetSpell (int buff_idx)
/return ${BuffCheckArray[${buff_idx},1]}

|----------------------------------------------------------------------------
|- SUB: BuffGroup_GetClass -- Return the class listed associated with a buff slot
|- buff_idx -- index of a spell
|----------------------------------------------------------------------------
Sub BuffGroup_GetClass (int buff_idx)
/return ${BuffCheckArray[${buff_idx},2]}

Sub BuffGroup_GetTag (int buff_idx)
/return ${BuffCheckArray[${buff_idx},4]}

|----------------------------------------------------------------------------
|- SUB: BuffGroup_ParseCondition -- Parses the condition for a buff slot
|- buff_idx -- index of a spell
|----------------------------------------------------------------------------
Sub BuffGroup_ParseCondition (int buff_idx)
    /declare result int local ${If[${BuffCheckArray[${buff_idx},3]},1,0]}
/return ${result}

|----------------------------------------------------------------------------
|- SUB: BuffGroup_GroupCheckThenCast -- Sees if a group member needs any buffs from the buff list and casts them
|- memberidx -- group member index from the Group.Member TLO -- Pass -1 to just self buff if not in a group.
|----------------------------------------------------------------------------
Sub BuffGroup_GroupCheckThenCast(int memberidx)
    /declare spawntobuff spawn local NULL
    /declare curmember_name string local NULL

    /if (${Group.Member[${memberidx}].Mercenary} && !${DoMercenary[SETTINGVAL]}) /return FALSE

    /if (${memberidx} > 0 && ${Group.Member[${memberidx}].Spawn.ID}) {
        /varset curmember_name ${Group.Member[${memberidx}].Name.Lower}
        /squelch /vardata spawntobuff Group.Member[${memberidx}].Spawn
    } else {
        /varset curmember_name ${Me.Name.Lower}
        /squelch /vardata spawntobuff Me.Spawn
    }
    /declare classlist string local
    /declare spellname string local 
    /declare tag string local
    
    |- Invalid info, we're kicking out early
    /if (${curmember_name.Equal[NULL]}) /return FALSE
    
    |- Used for overriding autotarget
    /declare old_autotarget int local ${DoAutoTarget[SETTINGVAL]}
    /declare buffidx int local
    /for buffidx 1 to ${BuffCheckArray.Size[1]} 
        /varset classlist ${BuffGroup_GetClass[${buffidx}]}
        /varset spellname ${BuffCheckArray[${buffidx},1]}
        /varset tag ${BuffCheckArray[${buffidx},4]}

        /if (${spellname.Equal[ALL]}) {
            /echo \ar ERROR: Buff Group Index ${buffidx} not configured -- Spell Name is ALL
            /continue
        }
        /if (${spellname.Equal[NULL]}) {
            |- Don't have the spell yet so skip the slot.
            /continue
        }
        |- Skip casting the buff if we don't meet the class requirements
        /if (${classlist.NotEqual[ALL]}) {
            /if (!${Select[${spawntobuff.Class.ShortName},${classlist}]}) {
                /continue
            }
        }
        |- Check our conditions, if they're false, skip the buffing.
        /if (!(${BuffGroup_ParseCondition[${buffidx}]}) ) {
            /continue
        }

        /if (${XAssist.XTFullHaterCount}) /return FALSE 
        /if (${SpellHasTriggers[${spellname}]} && ${tag.NotEqual[single]}) {
            DEBUG BuffGroup Checking triggers for ${spellname}  [tag: ${tag}] [cond: ${BuffGroup_ParseCondition[${buffidx}]}]
            |- We cannot use dannet with mercenaries
            /if (${Group.Member[${memberidx}].Mercenary}) {
                /call BuffGroup_MercTriggerBuffCheck ${Group.Member[${memberidx}].ID} "${spellname}"
            } else {
                
                /call DNetTriggerBuffCheck ${curmember_name} "${spellname}"
            }
        } else {
            DEBUG BuffGroup Checking buff for ${spellname}  [tag: ${tag}] [cond: ${BuffGroup_ParseCondition[${buffidx}]}]
            |- We cannot use dannet with mercenaries
            /if (${Group.Member[${memberidx}].Mercenary}) {
                /call BuffGroup_MercBuffCheck  ${Group.Member[${memberidx}].ID} "${spellname}"
            } else {            
                
                /call DNetBuffCheck ${curmember_name} "${spellname}"
            }
        }
        DEBUG Check returned: ${Macro.Return}
        /if (${Macro.Return} && !${XAssist.XTFullHaterCount}) {
            |- Override current DoAutoTarget to make sure we target for proc buffs
|            /declare old_autotarget int local ${DoAutoTarget[SETTINGVAL]}
            /varset DoAutoTarget[SETTINGVAL] 1
            /if (${PCSpellReady[${spellname}]}) {
                /call SpellNow "${spellname}" ${spawntobuff.ID}
            }
            /varset DoAutoTarget[SETTINGVAL] ${old_autotarget}
            /if (${XAssist.XTFullHaterCount}) /return FALSE
        } 
    /next buffidx
/return TRUE

|----------------------------------------------------------------------------
|- SUB: BuffGroup_XTCheckThenCast -- Checks if an xtarget or their group needs a buff from the buff list and casts it. Will only cast single target and Group V2 buffs.
|----------------------------------------------------------------------------
Sub BuffGroup_XTCheckThenCast
    |- Don't do anything if I'm the Outside Assist MA
    /if (${assistid}==${Me.ID}) /return FALSE
    /if (!${assistid}) /return FALSE

    /declare xtspawn spawn local
    /squelch /vardata xtspawn Spawn[id ${assistid}]
    
    |- Ignore if a mercenary
    /if (${xtspawn.Type.Equal[Mercenary]} && !${DoMercenary[SETTINGVAL]}) /return FALSE

    |- AssistID is in my group, skip.
    /if (${Group.Member[${xtspawn.CleanName}].Index}) /return FALSE

    |- Used for overriding autotarget
    /declare old_autotarget int local ${DoAutoTarget[SETTINGVAL]}
    /declare classlist string local
    /declare spellname string local 
    /declare tag string local
    /declare buffidx int local
    /for buffidx 1 to ${BuffCheckArray.Size[1]} 
        /varset classlist ${BuffGroup_GetClass[${buffidx}]}
        /varset spellname ${BuffGroup_GetSpell[${buffidx}]}
        /varset tag ${BuffGroup_GetTag[${buffidx}]}
        /if (${spellname.Equal[ALL]}) {
            /echo \ar ERROR: XT Buff Group Index ${buffidx} not configured -- Spell Name is ALL
            /continue
        }

        |- Because we are casting buffs out of group only single target and Group v2 buffs will land.
        /if (${Spell[${spellname}].TargetType.NotEqual[Group v2]} && ${Spell[${spellname}].TargetType.NotEqual[Single]} ) {
            DEBUG Not casting ${spellname} -- Not Group v2 or Single.
            /continue
        }
        
        |- Skip casting the buff if we don't meet the class requirements
        /if (${classlist.NotEqual[ALL]}) {
            /if (!${Select[${xtspawn.Class.ShortName},${classlist}]}) {
                /continue
            }
        }
        |- Check our conditions, if they're false, skip the buffing.
        /if (!(${BuffGroup_ParseCondition[${buffidx}]}) ) {
            /continue
        }

        /if (${XAssist.XTFullHaterCount}) /return FALSE 
        /if (${SpellHasTriggers[${spellname}]} && ${tag.NotEqual[single]}) {
            DEBUG XTBuffGroup ${xtspawn.CleanName} Checking triggers for ${spellname} [tag: ${tag}]
            |- We cannot use dannet with mercenaries
            /if (${xtspawn.Type.Equal[Mercenary]}) {
                /call BuffGroup_MercTriggerBuffCheck ${Group.Member[${memberidx}].ID} "${spellname}"
            } else {
                /call DNetTriggerBuffCheck ${xtspawn.CleanName} "${spellname}"
            }
        } else {
            DEBUG XTBuffGroup ${xtspawn.CleanName} Checking buff for ${spellname} [tag: ${tag}]
            |- We cannot use dannet with mercenaries
            /if (${xtspawn.Type.Equal[Mercenary]}) {
                /call BuffGroup_MercBuffCheck  ${Group.Member[${memberidx}].ID} "${spellname}"
            } else {
                /call DNetBuffCheck ${xtspawn.CleanName} "${spellname}"
            }
        }
        DEBUG XTCheck returned: ${Macro.Return}
        /if (${Macro.Return} && !${XAssist.XTFullHaterCount}) {
            |- Override current DoAutoTarget to make sure we target for proc buffs
            /declare old_autotarget3 int local ${DoAutoTarget[SETTINGVAL]}
            /varset DoAutoTarget[SETTINGVAL] 1

            |- IsSpellTooPowerful will make sure target isn't too low level. Only in XTCheckThenCast because
            |- why the heck would you group with someone THAT low level?
            /if (${PCSpellReady[${spellname}]} && !${IsSpellTooPowerful[${spellname},${xtspawn.Level}]} ) {
                /call SpellNow "${spellname}" ${xtspawn.ID}
            }

            /varset DoAutoTarget[SETTINGVAL] ${old_autotarget3}
        }
        /if (${XAssist.XTFullHaterCount}) /return FALSE 
    /next buffidx
/return TRUE

Sub BuffGroup_Defined
    /if (${Defined[BuffCheckArray]}) {
        /return TRUE
    }
/return FALSE

Sub BuffGroup_MercTriggerBuffCheck(int merc_spawn_id, string buffname)
    /if (${SpellHasTriggers[${buffname}]}) {
        /declare i int local
        /declare _triggername string local NULL
        /for i 1 to ${Spell[${buffname}].NumEffects}
            /if (${Spell[${buffname}].Attrib[${i}]} == 470 || ${Spell[${buffname}].Attrib[${i}]} == 374 || ${Spell[${buffname}].Attrib[${i}]} == 340 ) {
                /varset _triggername ${Spell[${buffname}].Trigger[${i}].Name}
                DEBUG BuffGroup_MercBuffCheck detect ${_triggername} for ${buffname}
                /call BuffGroup_MercBuffCheck ${merc_spawn_id} "${_triggername}"
                /if (!${Macro.Return}) /return FALSE
            }
        /next i
    } else {
        /echo \arERROR:\ax Just got a call to BuffGroup_MercTriggerBuffCheck on a buff without triggers.
    }
/return TRUE

Sub BuffGroup_MercBuffCheck(int merc_spawn_id, string buffname)
    /if (!${SpawnCount[id ${merc_spawn_id}]}) {
        /return FALSE
    }

    
    
    /if (!${Spawn[id ${merc_spawn_id}].CachedBuffCount}) {
        DEBUG Mercenary CachedBuffCount empty, targeting to renew.
        
        |- Override current DoAutoTarget to make sure we target for proc buffs
        /declare old_autotarget int local ${DoAutoTarget[SETTINGVAL]}
        /varset DoAutoTarget[SETTINGVAL] 1

        /call SetTarget ${merc_spawn_id}
        /delay 2s ${Target.BuffsPopulated}

        /varset DoAutoTarget[SETTINGVAL] ${old_autotarget}
    }

    /if (${Spawn[id ${merc_spawn_id}].CachedBuff[${buffname}].ID}) {
        DEBUG Mercenary already has ${buffname}
        /return FALSE
    } else {
        |- Merc doesn't have the buff so we'll target them, update our cache, and make sure it stacks.
        |-/call SetTarget ${merc_spawn_id}
        |-/delay 2s ${Target.BuffsPopulated}
        /if (!${Spell[${buffname}].StacksSpawn[${merc_spawn_id}]}) {
            DEBUG ${buffname} will not stack on Mercenary.
            /return FALSE
        }
    }


    DEBUG Mercenary does not have ${buffname} and it will stack.
|- Default is to cast the buff
/return TRUE


|----------------------------------------------------------------------------
|- SUB: BuffGroup_NoDanNet -- Checks if any on the non-Dannet list needs a buff from the buff list and casts it. Will only cast single target and Group V2 buffs.
|----------------------------------------------------------------------------
Sub BuffGroup_NoDanNet


    /if ( !${ExtendedBuffList.Length} ) /return FALSE

    /declare xtspawn spawn local
    /squelch /vardata xtspawn Spawn[id ${assistid}]
    
    |- AssistID is in my group, skip.
    /if (${Group.Member[${xtspawn.CleanName}].Index}) /return FALSE

    |- Used for overriding autotarget
    /declare old_autotarget2 int local ${DoAutoTarget[SETTINGVAL]}
    /declare classlist string local
    /declare spellname string local 
    /declare tag string local
    /declare buffidx int local
	/declare ExtList string local
	/declare ExtName string local
	/declare ExtID string local
	/declare ExtCount int local
	/declare l int local
        /declare i int local
        /declare k int local
        /declare numEffects int local
                    /varset ExtList ${ExtendedBuffList}
                    /varset ExtCount ${ExtendedBuffList.Count[|]}
    /for buffidx 1 to ${BuffCheckArray.Size[1]} 
        /varset classlist ${BuffGroup_GetClass[${buffidx}]}
        /varset spellname ${BuffGroup_GetSpell[${buffidx}]}
        /varset tag ${BuffGroup_GetTag[${buffidx}]}
	/for l 1 to ${ExtCount}

                    /varset ExtName ${ExtendedBuffList.Arg[${l},|]}
                    /varset ExtID ${Spawn[=${ExtendedBuffList.Arg[${l},|]}].ID}
         /squelch /vardata xtspawn Spawn[${ExtID}]

        /if (${spellname.Equal[ALL]}) {
            /echo \ar ERROR: XT Buff Group Index ${buffidx} not configured -- Spell Name is ALL
            /continue
        }
        |- Because we are casting buffs out of group only single target and Group v2 buffs will land.
        /if (${Spell[${spellname}].TargetType.NotEqual[Group v2]} && ${Spell[${spellname}].TargetType.NotEqual[Single]} ) {
            DEBUG Not casting ${spellname} -- Not Group v2 or Single.
            /continue
        }
        |- Skip casting the buff if we don't meet the class requirements
        /if (${classlist.NotEqual[ALL]}) {
            /if (!${Select[${xtspawn.Class.ShortName},${classlist}]}) {
                /continue
            }
        }
        |- Check our conditions, if they're false, skip the buffing.
        /if (!(${BuffGroup_ParseCondition[${buffidx}]}) ) {
            /continue
        }
            |- Override current DoAutoTarget to make sure we target for proc buffs
        |- Check if spell can even be cast

        |- Populate Target to verify buffs
            /varset old_autotarget2 int local ${DoAutoTarget[SETTINGVAL]}
            /varset DoAutoTarget[SETTINGVAL] 1
     /target id ${xtspawn.ID}
	/while ( !${Target.BuffsPopulated} ) {
		/delay 10
		}
       /if (!${Target.Buff[${spellname}].ID}) {
  		/for i 1 to 85
                /if (${Target.Buff[${i}].Name.Length}) {
                    /if (!${Spell[${spellname}].WillStack[${Target.Buff[${i}]}]}) {
		/return FALSE
                }
            }
        /next i
                /call SpellNow "${spellname}" ${xtspawn.ID}
           | Does buff have children spells like Unified Hand of Assurance or Talisman of the Wulthan
        } else /if (${AltAbility[${spellname}].Spell.Trigger[1].ID}) {
            /if (!${Target.Buff[${AltAbility[${spellname}].Spell.Trigger[1].Name}].ID}) {
                  /call SpellNow "${spellname}" ${xtspawn.ID}
            }
        } 
 |              /call SpellNow "${spellname}" ${xtspawn.ID}
		/varset DoAutoTarget[SETTINGVAL] ${old_autotarget2}
		/target id ${Me.ID}
		/delay 5
       	/next l
    /next buffidx
/return TRUE









