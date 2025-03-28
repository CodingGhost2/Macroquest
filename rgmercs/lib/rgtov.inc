|- This include contains code specific to handling the Ice debuff mechanic in ToV

|----------------------------------------------------------------------------
| Sub: Thawmequeue_Setup Setup the thawme queue
|----------------------------------------------------------------------------
Sub Thawmequeue_Setup
    |- This will store group/raid members names that have requested 
    |- thaw ice but were not within spell range to have it cast. It
    |- is a first-in/first-out data structure.
    /if (!${Defined[ThawIce_Queue]}) /declare ThawIce_Queue queue outer
/return	

|----------------------------------------------------------------------------
|- Sub: ThawmeQueueCheck Checks the thawme queue and will cast cureice if it finds
|- Anyone in the queue. Will also allow Shamans to cast restless ice infection if
|- the person has that instead.
|----------------------------------------------------------------------------
Sub ThawmeQueueCheck
    |- If our queue is empty, do nothing and return
    /if (${ThawIce_Queue.IsEmpty}) /return FALSE
    
    |- If we reach this point we have people in our ice queue
    |- to cure.
    
    |- Peek at the queue to get the name of the first person
    |- to request thawme that's out of range.
    /declare thawme_id string local ${ThawIce_Queue.Peek}
    DEBUG spawn: ${ThawIce_Queue.Peek} + name: ${Spawn[pc id ${thawme_id}].Name}
    
    |- Clearing target to force fresh buff population
    /call ClearTarget
    
    |- Target our person and see if they still have ice
    /call SetTarget ${thawme_id}
    /delay 10 (${Target.ID} == ${thawme_id})
    /delay 10 ${Target.BuffsPopulated}==TRUE
    /delay 10 ${Target.CachedBuffCount}!=-1
    
    /if (${Target.Distance} < 100 && ${Target.LineOfSight}) {
        |- See if the target still has restless ice on them
        
        /if (${Spawn[${thawme_id}].CachedBuff[=Restless Ice].ID}) {
            |- Target still has restless ice, cure them
            /call Bind_CureIce ${thawme_id}
        } else /if (${Spawn[${thawme_id}].CachedBuff[=Restless Ice Infection].ID}) {
            |- Buff changed to infection -- changes spell for Shaman, Cleric
            |- does the same old, same old.
            /call Bind_CureIce ${thawme_id} 1
        } else {
            |- Target doesn't have restless ice, remove their
            |- name from the queue
            /call PrintGroupMessage "Removing ${Spawn[id ${ThawIce_Queue.Pop}].CleanName} from Thawme Queue"
        }
    }
/return

Sub AddToThawmeQueue(int groupmem_id)
    /if (!${ThawIce_Queue.Push[${groupmem_id}]}) {
        /echo Failed to add ${Spawn[pc ${groupmem_id}].Name} to ThawIce Queue.
    }
/return
|**
|----------------------------------------------------------------------------
|- Sub: TOV_CheckDNetForIce 
|- Check DanNet peers that are in zone for restless ice. If they have it adds
|- them to the thawme queue.
|----------------------------------------------------------------------------
Sub TOV_CheckDNetForIce
    /declare tmp_spawn spawn local
    /declare i int local
    /for i 1 to ${DanNet.PeerCount}
        /if (${SpawnCount[pc ${DanNet.Peers[${i}]}]}) {
            /vardata tmp_spawn Spawn[pc ${DanNet.Peers[${i}]}]
            /call DNetQueryCheck "${tmp_spawn.CleanName}" "Me.Song[Restless Ice].ID"
            /if (${Bool[${Macro.Return}]}) /call AddToThawmeQueue ${tmp_spawn.ID}
        }
    /next i 
/return FALSE
**|


|----------------------------------------------------------------------------
|- Sub: TOV_CheckDNetForIce 
|- Check DanNet peers that are in zone for restless ice. If they have it adds
|- them to the thawme queue.
|----------------------------------------------------------------------------
Sub TOV_CheckDNetForIce
    /declare tmp_spawn spawn local
    /declare i int local
    /for i 1 to ${DanNet.PeerCount}
        /if (${SpawnCount[pc ${DanNet.Peers[${i}]}]}) {
            /vardata tmp_spawn Spawn[pc ${DanNet.Peers[${i}]}]
            /call DNetQueryCheck "${tmp_spawn.CleanName}" "Me.Song[Restless Ice].ID"
            DEBUG TOV_CheckDNetForIce Macro.Return ${Macro.Return}
            /if (!${Bool[${Macro.Return.Equal[NULL]}]}) /call AddToThawmeQueue ${tmp_spawn.ID}
        }
    /next i 
/return FALSE