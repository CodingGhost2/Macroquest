|----------------------------------------------------------------------------  
|- SUB: Bind_RGdebug_printmap 
|- Prints out a map variable.
|----------------------------------------------------------------------------
#bind RGdebug_printmap /printmap
Sub Bind_RGdebug_printmap(string map_name)
    
    /if (${map_name.Equal[NULL]}) /return FALSE
    /declare mi mapiterator local
    /vardata mi ${map_name}.First.Clone
    /echo Printing ${map_name} Size: ${${map_name}.Count}
    /while (!${mi.IsEnd} ) {
        /echo ${mi.Key} -> ${Parse[1,${mi.Value}]} => ${mi.Value}
        /invoke ${mi.Advance}
    }
/return

|----------------------------------------------------------------------------  
|- SUB: Bind_RGdebug_printlist 
|- Prints out a list variable.
|----------------------------------------------------------------------------
#bind RGdebug_printlist /printlist
Sub Bind_RGdebug_printlist(string list_name)
    /if (${list_name.Equal[NULL]}) /return FALSE
    /declare li listiterator local
    /vardata li ${list_name}.First.Clone
    /echo List ${list_name} Size: ${${list_name}.Count}
    /while ( !${li.IsEnd} ) {
        /echo ${li.Value}
        /invoke ${li.Advance}
    }
/return

|----------------------------------------------------------------------------  
|- SUB: Bind_RGdebug_printset 
|- Prints out a set variable
|----------------------------------------------------------------------------
#bind RGdebug_printset /printset
Sub Bind_RGdebug_printset(string set_name)
    /if (${set_name.Equal[NULL]}) /return FALSE
    /declare si setiterator local
    /vardata si ${set_name}.First
    /echo Set ${set_name} Size: ${${set_name}.Count}
    /while ( !${si.IsEnd} ) {
        /echo ${si.Value}
        /invoke ${si.Advance}
    }
/return

|----------------------------------------------------------------------------  
|- [WIP] SUB: Bind_rgdebug_spellinfo 
|- Prints out spell information
|----------------------------------------------------------------------------
#bind rgdebug_spellinfo /printspell
Sub Bind_rgdebug_spellinfo(string spell_name)
    /echo Spell Name:
    /echo Spell Level: 
    /echo Spell Type:
    /echo Target Type:
    /echo Restrictions:
    /echo Number of Attributes
    /echo Spell Number of Triggers:
    /echo Trigger Names:
/return

|----------------------------------------------------------------------------
|- SUB: IsAlive - Returns True if SpawnID is still alive
|----------------------------------------------------------------------------
#bind IsAlive /testisalive
Sub Bind_IsAlive(int spawn_id)
    /declare tgt_spawn spawn local
    /vardata tgt_spawn Spawn[id ${spawn_id}]
    
    /if (!${tgt_spawn.Hovering} && !${tgt_spawn.Dead}) {
        /return TRUE
    }
/return FALSE