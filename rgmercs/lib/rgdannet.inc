|-------------------------------------------------------------------------------------
|- ###################################################################################
|- RG DANNET INTERFACE SECTION
|- ###################################################################################
|-------------------------------------------------------------------------------------

|----------------------------------------------------------------------------
|- SUB: DNetCreateObserver - 
|- Requires Map_Observers to be defined as a global mq2collections map type.
|----------------------------------------------------------------------------
Sub DNetCreateObserver(string toonname, string query, string observername, string typename)
    |- Do not create observers if the toon isn't on dannet
    /if (!${DanNet.Peers.Find[${toonname.Lower}]}) {
        /echo NOTICE: ${toonname.Lower} not on DanNet. Cannot create observer ${observername}.
        /return FALSE
    } 
    
    |- Do not create the observer if we've already created it -- we should modify an observer
    |- already in existence in this case
    /if (${Map_Observers.Contains[${observername}]}) {
        /echo NOTICE: Observer ${observername} already exists.
        /return FALSE
    }

    |- create the variable with the provided type for use with the observer
    /if (!${Defined[${observername}]} ) {
        /declare ${observername} ${typename} outer
        DEBUG Declaring ${observername} as ${typename}
    }
    /declare peername string local ${EverQuest.Server.Lower}_${toonname.Lower}
    /if (${Map_Observers.Add[${observername},${peername}|${query}]}) {
        DEBUG Creating Observer: /dobserve ${peername} -q ${query} -o ${observername}
        /dobserve ${peername} -q ${query} -o ${observername}
    } else {
        /echo \arERROR\ax: Couldn't create ${observername}.
        /deletevar ${observername}
        /return FALSE
    }
/return TRUE

|----------------------------------------------------------------------------
|- SUB: DNetDropObserver - 
|----------------------------------------------------------------------------
Sub DNetDropObserver(string observername)
    /if (!${Map_Observers.Contains[${observername}]}) /return FALSE
    
    /declare mi mapiterator local
    /vardata mi Map_Observers.Find[${observername}]

    /dobserve ${mi.Value.Arg[1,|]} -q ${mi.Value.Arg[2,|]} -drop
    /if (${Map_Observers.Remove[${observername}]}) {
        /deletevar ${observername}
    } else {
        /echo \arERROR\ax: Couldn't remove ${observername} from map. You must manually delete Observer_${observername}
    }
/return TRUE

|----------------------------------------------------------------------------
|- SUB: DNetIsObserver - 
|----------------------------------------------------------------------------
Sub DNetIsObserver(string observername)
    /if (!${Map_Observers.Contains[${observername}]}) /return FALSE
/return TRUE

|----------------------------------------------------------------------------
|- SUB: DNetGetObserverValue - Looks up an Observer value based on its TLO
|----------------------------------------------------------------------------
Sub DNetGetObserverValue(string observername)
    /if (!${Map_Observers.Contains[${observername}]}) /return FALSE
    
    /declare mi mapiterator local
    /vardata mi Map_Observers.Find[${observername}]
    DEBUG Looking up ${mi.Value.Arg[1,|]} -> ${mi.Value.Arg[2,|]} (${DanNet[${mi.Value.Arg[1,|]}].O[${mi.Value.Arg[2,|]}]} => ${${observername}})
/return ${DanNet[${mi.Value.Arg[1,|]}].O[${mi.Value.Arg[2,|]}]}

|----------------------------------------------------------------------------
|- SUB: DNetGetObserverReceived - Looks up the last time an observer was received based on observername
|- in: just_tlostr => If set to True, returns the STRING that can be resolved  instead of the actual time.
|-                    This is useful as a precursor to delays as you cannot use inline-sub calls in delays.
|-                    predominanlty added as a hack for CureNow.
|----------------------------------------------------------------------------
Sub DNetGetObserverReceived(string observername, bool just_tlostr)
    EDEBUG Checking ${observername}
    /if (!${Map_Observers.Contains[${observername}]}) /return FALSE
    
    /declare mi mapiterator local
    /vardata mi Map_Observers.Find[${observername}]
    DEBUG Looking up ${mi.Value.Arg[1,|]} -> ${mi.Value.Arg[2,|]} (${DanNet[${mi.Value.Arg[1,|]}].O[${mi.Value.Arg[2,|]}].Received} => ${${observername}})
    /if (${just_tlostr}) /return DanNet[${mi.Value.Arg[1,|]}].O[${mi.Value.Arg[2,|]}].Received
/return ${DanNet[${mi.Value.Arg[1,|]}].O[${mi.Value.Arg[2,|]}].Received}
|----------------------------------------------------------------------------
|- SUB: DNetInitObservers - 
|- Re-initializes all recorded observers. Useful after zoning to reconnect
|- a DNet observer to its underlying outer variable. Uses our record of
|- observers.
|----------------------------------------------------------------------------
Sub DNetInitObservers
    /declare mi mapiterator local
    /vardata mi Map_Observers.First.Clone

    /while (!${mi.IsEnd}) {
        /dobserve ${mi.Value.Arg[1,|]} -q ${mi.Value.Arg[2,|]} -o ${mi.Key}
        /invoke ${mi.Advance}
    }
/return TRUE

|----------------------------------------------------------------------------
|- SUB: DNetGetObserverPeername - 
|----------------------------------------------------------------------------
Sub DNetGetObserverPeername(string observername)
    /if (!${Map_Observers.Contains[${observername}]}) /return NULL
    /declare mi mapiterator local
    /vardata mi Map_Observers.Find[${observername}]
/return ${mi.Value.Arg[1,|]} 

|----------------------------------------------------------------------------
|- SUB: DNetGetObserverQuery - 
|----------------------------------------------------------------------------
Sub DNetGetObserverQuery(string observername)
    /if (!${Map_Observers.Contains[${observername}]}) /return NULL
    /declare mi mapiterator local
    /vardata mi Map_Observers.Find[${observername}]
/return ${mi.Value.Arg[2,|]}

|----------------------------------------------------------------------------
|- SUB: DNIsPeer - 
|----------------------------------------------------------------------------
Sub DNIsPeer(string peerName)
    /if (${DanNet[peerName]}) {
      /return TRUE
    }
/return FALSE

|----------------------------------------------------------------------------
|- SUB: DNetBuffCheck - Returns True if you need to cast the buff on the dannet peer passed, false otherwise.
|- peername: DanNet Peer in full format Ex. ${EverQuest.Server.Lower}_${Target.Name}
|- buffname: Spelllname of the buff
|----------------------------------------------------------------------------
Sub DNetBuffCheck(string toonname, string buffname)

    /if (!${SpawnCount[pc ${toonname}]}) {
        /return FALSE
    }

    /if (${DanNet.Peers.Find[${toonname.Lower}]}) {
        /declare peername string local ${EverQuest.Server.Lower}_${toonname.Lower}
        /declare buffid int local
        /declare willstack string local true
        /declare tmpquery string local
        /declare isblocked int local

        |- Will return a value if the target has the buff already
        /varset tmpquery "Me.Buff[${buffname}].ID"
        DEBUG DNet Sending ${tmpquery} to ${peername}
        /dquery ${peername} -q ${tmpquery} -o buffid
        /delay 20 ${DanNet[${peername}].Query["${tmpquery}"].Received}

        |- Will return true if the buff will stack on the target
        /varset tmpquery "Spell[${buffname}].Stacks"
         DEBUG DNet Sending ${tmpquery} to ${peername}
        /dquery ${peername} -q ${tmpquery} -o willstack
        /delay 20 ${DanNet[${peername}].Query["${tmpquery}"].Received}

        |- Don't perform the block checks on spells that have the Change Form SPA.
        /if (!${Spell[${buffname}].HasSPA[58]}) {
            |- Will return a value if the buff is in the blocked list
            /varset tmpquery "Me.BlockedBuff[${buffname}].ID"
            DEBUG DNET Sending ${tmpquery} to ${peername}
            /dquery ${peername} -q ${tmpquery} -o isblocked
            /delay 20 ${DanNet[${peername}].Query["${tmpquery}"].Received}
        } else {
            DEBUG ${buffname} as Change Form SPA.
            /varset isblocked FALSE
        }

        |- If the target doesn't have the buff and it will stack, return true
        DEBUG DNet returned => buffid ${buffid} -- willstack ${willstack} -- isblocked ${isblocked}
        /if ( !${buffid} && ${willstack} && !${isblocked} ) {
            /return TRUE
        } 
    } else {
        /if (${ErrorMsg[SETTINGVAL]}) {
            /echo \arERROR:\ax \awCould not find ${toonname} on DanNet and thus will not casting ${buffname} on ${toonname}. Please '/plugin mq2dannet load' on ${toonname}. Turn this message off with '/rg ErrorMsg 0'.
        }
    }
    |- Defaults to not casting
/return FALSE

|----------------------------------------------------------------------------
|- SUB: DNetTriggerBuffheck - Returns True if you need to cast the buff on the dannet peer passed, false otherwise. Specifically designed for 
|- checking triggered buffs like the cleric unity line.
|- peername: DanNet Peer in full format Ex. ${EverQuest.Server.Lower}_${Target.Name}
|- buffname: Spelllname of the buff
|----------------------------------------------------------------------------
 Sub DNetTriggerBuffCheck(string toonname, string buffname)
    /if (${SpellHasTriggers[${buffname}]}) {
        /declare i int local
        /declare _triggername string local NULL
        /for i 1 to ${Spell[${buffname}].NumEffects}
            /if (${Spell[${buffname}].Attrib[${i}]} == 470 || ${Spell[${buffname}].Attrib[${i}]} == 374 || ${Spell[${buffname}].Attrib[${i}]} == 340 ) {
                /varset _triggername ${Spell[${buffname}].Trigger[${i}].Name}
                DEBUG DNetTrigger detect ${_triggername} for ${buffname}
                /call DNetBuffCheck ${toonname} "${_triggername}"
                /if (!${Macro.Return}) /return FALSE
            }
        /next i
    } else {
        /if (${ErrorMsg[SETTINGVAL]}) {
            /echo \arERROR:\ax \awCould not find ${toonname} on DanNet and thus will not casting ${buffname} on ${toonname}. Please '/plugin mq2dannet load' on ${toonname}. Turn this message off with '/rg ErrorMsg 0'.
        }
    }
 
 |- Defaults to returning true because DNetBuffCheck will default to returning to false if we don't
 |- need to cast the buff.
 /return TRUE

|----------------------------------------------------------------------------
|- SUB: DNetQueryCheck - Returns True if you need to cast the buff on the dannet peer passed, false otherwise.
|- peername: DanNet Peer in full format Ex. ${EverQuest.Server.Lower}_${Target.Name}
|- query: query to send dannet. Use the same syntax as vardatas, e.g., Me.Buff[${buffname}].ID
|----------------------------------------------------------------------------
Sub DNetQueryCheck(string toonname, string query)
    /if (!${SpawnCount[pc ${toonname}]}) {
        /return FALSE
    }
    /if (${DanNet.Peers.Find[${toonname.Lower}]}) {
        /declare peername string local ${EverQuest.Server.Lower}_${toonname.Lower}
        /declare response string local

        |- Will return the value of the query sent
        DEBUG DNet Sending ${query} to ${peername}
        /dquery ${peername} -q "${query}" -o response
        /delay 20 ${DanNet[${peername}].Query["${query}"].Received}

        |- If the target doesn't have the buff and it will stack, return true
        /return ${response}
    } else {
        /if (${ErrorMsg[SETTINGVAL]}) {
            /echo \arERROR:\ax \awCould not find ${toonname} on DanNet and thus will not casting on ${toonname}. Please '/plugin mq2dannet load' on ${toonname}. Turn this message off with '/rg ErrorMsg 0'.
        }
    }
    |- Defaults to not casting
/return FALSE

|----------------------------------------------------------------------------
|- SUB: DNetPetHps - Returns the hps of the charater's pet
|- peername: DanNet Peer in full format Ex. ${EverQuest.Server.Lower}_${Target.Name}
|----------------------------------------------------------------------------
Sub DNetPetHps(string toonname)

    /if (!${SpawnCount[pc ${toonname}]}) {
        /return NULL
    }

    /if (${DanNet.Peers.Find[${toonname.Lower}]}) {
        /declare peername string local ${EverQuest.Server.Lower}_${toonname.Lower}
        /declare petHPs int local

        |- Will return a value if the target has the buff already
        /declare tmpquery string local "Me.Pet.PctHPs"
        DEBUG DNet Sending ${tmpquery} to ${peername}
        /dquery ${peername} -q ${tmpquery} -o petHPs
        /delay 20 ${DanNet[${peername}].Query["${tmpquery}"].Received}

        /return ${petHPs}
    } else {
        /if (${ErrorMsg[SETTINGVAL]}) {
            /echo \arERROR:\ax \awCould not find ${toonname} on DanNet
        }
    }
    |- Defaults to NULL
/return NULL