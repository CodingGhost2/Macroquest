|- RGevents.inc
|- Version 2.0
|- Updated: 4/25/2019
|-#Event	EventName	"Event Text"
|-Sub Event_EventName	
|- /popcustom 
|- /doevents flush EventName
|-/return

|**

Sub BLOCK General Events

**|

|----------------------------------------------------------------------------
|- SUB: Mana Check
|----------------------------------------------------------------------------
#Event ManaCheck            #*#!mana check#*#
Sub Event_Manacheck
	/declare warstuff 	string local

	/if (${Me.Class.ShortName.Equals[WAR]) {
		/if ( ${RG_AAReady[${meleemit}] ) {
			/varset warstuff "${meleemit} is READY"
		} else /if ( !${RG_AAReady[${meleemit}] ) {
			/varset warstuff "${meleemit} NOT READY - ${Me.AltAbiltyTimer[${meleemit}].TotalSeconds} until ready
		}
	/rs ${Me.Class.ShortName} - ${Me.CurrentEndurance} Endurance - ${warstuff}
	}

	/if ( ${Select[${Me.Class.ShortName},CLR,DRU,SHM]} ) {
	/delay 2s
	/rs ${Me.Class.ShortName} ${Me.PctMana}% - ${Me.CurrentMana}
	}
/return



|----------------------------------------------------------------------------
|- SUB: Event Zoned
|----------------------------------------------------------------------------
#Event Zoned             "LOADING, PLEASE WAIT#*#"
#Event Zoned             "You have entered#*#"
Sub Event_Zoned(Message)
	/call Zoning
	/doevents flush Zoned
/return
Sub Zoning
	/delay 3m !${Me.Zoning}

	|- Clear pull info from the prior zone.
	/invoke ${PullOnly_Set.Clear}
	/invoke ${PullIgnore_Set.Clear}
	/invoke ${Waypoints_List.Clear}

    /if (${Defined[RGCustom_WinTitle]}) {
        /SetWinTitle ${RGCustom_WinTitle}
    } else {
        /SetWinTitle WINDOWTITLE
    }
/return

|----------------------------------------------------------------------------
|- SUB: Event TooClose
|- This is when a bow and arrow is used too closely. Currently is only an
|- issue of concern during pulling.
|----------------------------------------------------------------------------
#Event TooClose          "Your target is too close to use a ranged weapon!"
Sub Event_TooClose
	|- Check if we're in the middle of a pull and use a backup.
	/if (${DoPull[SETTINGVAL]} && ${Pull_State} == PULL_PULLING) {
		/if (${NPCDiscReady[Throw Stone]}) {
			/call DiscNow "Throw Stone" ${Target.ID}
			/delay 1
		} else {
			/if (${NPCAbilityReady[Taunt]}) {
				/nav id ${Target.ID} distance=${Target.MaxRangeTo} lineofsight=on log=off
		        /delay 2s ${Navigation.Active}
				/call AbilityNow "Taunt" ${Target.ID}
				/delay 1
			} else {
				/echo NOTICE (Event_TooClose): Too Close. Cannot Pull. Throw Stone/Taunt not ready.
			}
		}
	}
	|- Only do non-pull code if autoengage is on
	/if (${DoAutoEngage[SETTINGVAL]}) {
		/if (${Me.Class.ShortName.Equal[RNG]} && ${Pull_State} != PULL_PULLING) {
			|- Basic stick code until we implement nav circumference
			/if (!${DoMelee[SETTINGVAL]}) {
				/call NavAroundCircle ${Target.ID} 45 TRUE
			}
		}
	}
	/doevents flush TooClose
/return

|-------------------------------------------------------------------------------------
|- SUB: Torment of Velious Restless Ice. - RG
|-------------------------------------------------------------------------------------
Sub RestlessIce
	/if ( ${Me.Song[Restless Ice].ID} ) { 
		|- /gsay RC
        /call PrintGroupMessage "Restless ICE!"
	}
/return
|----------------------------------------------------------------------------
|- SUB: Event Summoned - If we've been summoned, we need to handle it.
|- If we're pulling we need to handle the summon. If we're not pulling we need
|- to go back to our camp spot if we have one set. We don't want to go back 
|- to camp if we're using melee and not the main assistant, 
|---------------------------------------------------------------------------- 
#Event Summoned "You have been summoned!"
Sub Event_Summoned(string Line,string text)
	|- Placeholder for handling pulling
	
	|- The else if we're not pulling
	/if (${DoAutoEngage[SETTINGVAL]}) {
		/if (!${DoMelee[SETTINGVAL]} && (${Me.ID} != ${assistid}) ) {
			|- Return to camp if we're not meleeing and we're not the RG main assist.
			/if (${ReturnToCamp[SETTINGVAL]}) {
		        /call PrintGroupMessage "${Me.Name} was just summoned -- returning to camp!"
				/call AutoCampCheck
			}
		}
	}
/return

|----------------------------------------------------------------------------
|- SUB: Event Stunned -
|---------------------------------------------------------------------------- 
#Event Stunned  "You are stunned!"
Sub Event_Stunned(string Line,string text)
	|- Placeholder for handling pulling stuff
/return

#Event LvlSet "#*#You are now level #1#!"
Sub Event_LvlSet(string line, string lvl)
	/echo NOTICE: Level change detected. Now LVL ${lvl}
	/call RGChangeSetting Settings RGLevel ${Me.Level}
	/doevents flush LvlSet
/return


|----------------------------------------------------------------------------
|- SUB: Event Gain Something - DanNet message 
|----------------------------------------------------------------------------   
#Event GainSomething     "#*#You have gained|#1#|"
#Event GainSomething     "You have completed achievement: #1# #*#"
Sub Event_GainSomething(string Line,string text)
	/if (${Line.Find["ABILITY POINT!"]}) {
		/call PrintGroupMessage "\aw ${Me.Name} gained an AA, now has ${Me.AAPoints} unspent \ax"
	} else /if (${Line.Find[LEVEL]}) {
		/call PrintGroupMessage "\aw ${Me.Name} gained a level, now is Level ${Me.Level} \ax"
		/if (${LvlAutoCalc[SETTINGVAL]}) {
			/varset PullMinLvl[SETTINGVAL] ${Int[${Math.Calc[${Me.Level}-3]}]}
			/varset PullMaxLvl[SETTINGVAL] ${Int[${Math.Calc[${Me.Level}+3]}]}
			/echo \agAdjusting mob pull levels. Will now pull mobs level \at${PullMinLvl[SETTINGVAL]} \awto \at${PullMaxLvl[SETTINGVAL]}
		}
		/call RGChangeSetting Settings RGLevel ${Me.Level}
	}
	/doevents flush GainSomething
/return 

|----------------------------------------------------------------------------
|- SUB: Event Task Update - DanNet message 
|----------------------------------------------------------------------------    
#Event TaskUpdate        "#*#Your task |#1#| has been updated#*#"
Sub Event_TaskUpdate(string Line,string name) 
    /call HandleAcverbose "\at Task updated...(${name})\ax"
/return
|----------------------------------------------------------------------------
|- SUB: Event Camping - end macro
|----------------------------------------------------------------------------
#Event Camping           "#*#seconds to prepare your camp."
Sub Event_Camping   
	/if (${Me.Casting.ID}) /stopcast
	/end
/return

| ----------------------------------------------------------------------------
| SUB: Event Turn off Mount
| ----------------------------------------------------------------------------
#Event MountOff           "You need to be in a more open area to summon a mount"
#Event MountOff           "You can not summon a mount in this form"
Sub Event_MountOff
	/varset ${DoMount[SETTINGVAL]} 0
/return
| ----------------------------------------------------------------------------
| SUB: Event Too Far
| ----------------------------------------------------------------------------
#Event TooFar           "Your target is too far away, get closer!"
#Event TooFar           "You can't hit them from here."
#Event TooFar 			"You are too far away#*#"
Sub Event_TooFar
	/if (${BackOffFlag}) /return
	/if (${Stick.Active}) /Stick off
	|- Handle one situation where this happens when we're pulling
	/if (${Pull_State} == PULL_PULLING) {
		/nav id ${Target.ID} distance=${Math.Calc[${Target.Distance} * 0.75]} lineofsight=on log=off
		/delay 2s ${Navigation.Active}
	} else {
		/if (${DoAutoEngage[SETTINGVAL]}) {
			|- Only Do this if we're in combat & Auto Engaging.
			/if (${Ok2Engage[]}) {
				/if (${DoMelee[SETTINGVAL]}) {
					DEBUG Meleeing and too far away. Naving to ${Math.Calc[${Target.MaxRangeTo} * 0.9]} away and not sticking.
					/call NavInCombat ${Target.ID} ${Math.Calc[${Target.MaxRangeTo} * 0.9]} TRUE FROMHERE
				}
			}
		}
	}
	/doevents flush TooFar
/return	

| -------------------------------------------------------------------------------------
| SUB: Event CantSee
| -------------------------------------------------------------------------------------

#Event CantSee           "You cannot see your target."
Sub Event_CantSee
	/if (${BackOffFlag}) /return

	| Calltrace stack
	CALLINGSUB
	CALLINGINDEX

	CALLTRACE Entered Event_CantSee

	/if (${Stick.Active}) /Stick off
|	|- Handle one situation where this happens when we're pulling
	/if (${Pull_State} == PULL_PULLING) {
		CALLTRACE We are in Pull_State ${Pull_State} == PULL_PULLING

		/nav id ${Target.ID} distance=${Math.Calc[${Target.Distance}*0.5]} lineofsight=on log=off
		/delay 2s ${Navigation.Active}
		| Does this need a timer?
		/while (${Navigation.Active} && ${XAssist.XTFullHaterCount} == 0) {
			CALLTRACE In while loop :: Navigation.Active ${Navigation.Active} :: XAssist ${XAssist.XTFullHaterCount}
			/doevents
			/delay 1 ${XAssist.XTFullHaterCount} > 0
		}
	} else {
		CALLTRACE We are in combat
		|- Only Do this if we're in combat & Auto Engaging.
		/if (${DoAutoEngage[SETTINGVAL]}) {
			/if ( ${Ok2Engage[]} ) {
				/squelch /face fast
				/if (${DoMelee[SETTINGVAL]}) {
					CALLTRACE Meleeing and Can't See target (${Target.Name} ${Target.ID}). Naving to ${Math.Calc[${Target.MaxRangeTo} * 0.9]} away.
					DEBUG Meleeing and Can't See target. Naving to ${Math.Calc[${Target.MaxRangeTo} * 0.9]} away.
					/call NavInCombat ${Target.ID} ${Math.Calc[${Target.MaxRangeTo} * 0.9]} FALSE FROMHERE
				}
			}
		}
	}
	/doevents flush CantSee

	CALLTRACE Exiting Event_CantSee
/return

#Event ImprovedAA	"You have improved #1# at a cost of #2# ability points."
Sub Event_ImprovedAA(line, aaname, aapoints)
	/call PrintGroupMessage "\aw Spent ${aapoints} on improving ${aaname} -- Have ${Me.AAPoints} unspent \ax"
	/doevents flush ImprovedAA
/return

#Event RaidInvite          "#1# tells you, 'Raid Invite Please'"
Sub Event_RaidInvite(string line,string invitee)
	/echo in Raid Invite Event
	/raidinvite ${invitee}
/return

#Event GroupInvite          "#1# tells you, 'Group Invite Please'"
Sub Event_GroupInvite(string line,string invitee)
	/echo in Group Invite Event
	/invite ${invitee}
/return

|----------------------------------------------------------------------------
|- SUB: MpgFearTrial
|----------------------------------------------------------------------------
Sub MpgFearTrial
|- This Will Requires u to turn on the DoZoneLogic setting to 1 to use the autofear

	/if ( !${DoMpgFearTrial[SETTINGVAL]} ) /return
    /echo This Is intended for use in the MPG Trial of fear group edition.!
    /echo Mem a Fear Spell in gem8 - This Routine will use it to auto fear trial Mobs
    /echo Please make sure its Fears all creature types. and use your fastest cast.
    /declare i local 1
        /for i 1 to ${Me.XTarget}
            /if (${Me.XTarget[${i}].Name.Find[Fearless]} ) /continue 
            /declare spawn_tmp spawn local
			
			/if (!${Me.XTarget[${i}].CachedBuff[${Me.Gem[8]}].Duration} && ${XTarget[${i}].Type.Equal[npc]}) {
                /mqtarget id ${Me.XTarget[${i}].ID}
				/delay 15 ${Target.ID}==${Me.XTarget[${i}].ID}
                /cast 8
                /delay 5 ${Me.Casting.ID}
                /delay ${CastThisSpell.MyCastTime.Float}s !${Me.Casting.ID}
            }
        /next i 

/return 

|----------------------------------------------------------------------------
|- SUB: Event GroupChange
|----------------------------------------------------------------------------
#Event GroupChange	"#*#has left the group#*#"
#Event GroupChange	"#*#has joined the group#*#"
Sub Event_GroupChange
	/call Bind_CheckForAlliance
	/doevents flush GroupChange
/return

|----------------------------------------------------------------------------
|- SUB: Events for Raid
|----------------------------------------------------------------------------
#Event RaidJoin	"#*#You formed a raid#*#"
#Event RaidJoin	"#*#You have joined the raid#*#"
Sub Event_RaidJoin
	/call RGChangeSetting Settings DoRaid 1
	/doevents flush RaidJoin
/return

#Event RaidLeave	"#*#You were removed from the raid#*#"
#Event RaidLeave	"#*#Your riad was disbanded*#"
Sub Event_RaidLeave
	/call RGChangeSetting Settings DoRaid 0
	/doevents flush RaidLeave
/return

#Event EffectResultsInDeath "Casting #1# Effect would result in your death!"
Sub Event_EffectResultsInDeath(string item_name)
	/shift /itemnotify "${item_name}" leftmouseup 
	/popup "Picked up the Mod Rod that would kill you. Type /destroy to get rid of it."
	/doevents flush EffectResultsInDeath
/return

#Event BeginMemorizing "Beginning to memorize #1#..."
Sub Event_BeginMemorizing(string spell_name)
	/varset IsMemorizing TRUE
	/doevents flush BeginMemorizing
/return

#Event EndMemorizing "You have finished memorizing #1##*#"
#Event EndMemorizing "Aborting memorization of spell."
Sub Event_EndMemorizing(string spell_name)
	/varset IsMemorizing FALSE
	/doevents flush EndMemorizing
/return


|**

Sub  BLOCK Spell Events

**|

	|- Alias for DoEvents to make it clear why we're calling it
	#define GET_CAST_RESULT /doevents

	|- CAST_SUCCESS
	#event CAST_SUCCESS                  "You begin casting#*#"
	#event CAST_SUCCESS                  "You begin singing#*#"
	#event CAST_SUCCESS                  "Your #1# begins to glow.#*#"
	sub Event_CAST_SUCCESS(string line)
		DEBUG Casting begun: Defaulting to CAST_SUCCESS
		/varset CastResult CAST_SUCCESS
		/doevents flush CAST_SUCCESS
	/return

	|- CAST_OVERWRITTEN
	#event CAST_OVERWRITTEN			    "Your#*#has been overwritten#*#"
	sub Event_CAST_OVERWRITTEN(string line)
		DEBUG CAST_OVERWRITTEN
		/varset CastResult CAST_OVERWRITTEN
		/doevents flush  CAST_OVERWRITTEN
	/return

	|- CAST_CANCELLED

	|- CAST_COLLAPSE
	#event CAST_COLLAPSE               "Your gate is too unstable, and collapses#*#"
	sub Event_CAST_COLLAPSE(string line)
		DEBUG CAST_COLLAPSE
		/varset CastResult CAST_COLLAPSE
		/doevents flush CAST_COLLAPSE
	/return

	|- CAST_DISTRACTED
	#event CAST_DISTRACTED             "You need to play a#*#instrument for this song#*#"
	#event CAST_DISTRACTED             "You are too distracted to cast a spell now#*#"
	#event CAST_DISTRACTED             "You can't cast spells while invulnerable#*#"
	#event CAST_DISTRACTED             "You *CANNOT* cast spells, you have been silenced#*#"
	#event CAST_DISTRACTED             "You do not have sufficient focus to maintain that ability."
	sub Event_CAST_DISTRACTED(string line)
		DEBUG CAST_DISTRACTED
		/varset CastResult CAST_DISTRACTED
		/doevents flush CAST_DISTRACTED
	/return

	|- CAST_FIZZLE
	#event CAST_FIZZLE                 "Your spell fizzles#*#"
	#event CAST_FIZZLE                 "You miss a note, bringing your song to a close#*#"
	sub Event_CAST_FIZZLE(string line)
		DEBUG CAST_FIZZLE
		/varset CastResult CAST_FIZZLE
		/doevents flush CAST_FIZZLE
	/return

	|- CAST_INTERRUPTED
	#event CAST_INTERRUPTED            "Your spell is interrupted#*#"
	#event CAST_INTERRUPTED            "Your casting has been interrupted#*#"
	#event CAST_INTERRUPTED            "Your #1# spell is interrupted#*#"
	sub Event_CAST_INTERRUPTED(string line)
		DEBUG CAST_INTERRUPTED
		/varset CastResult CAST_INTERRUPTED
		/doevents flush CAST_INTERRUPTED
	/return

	|- CAST_INVISIBLE
	|- CAST_NOTARGET
	#event CAST_NOTARGET               "You must first select a target for this spell#*#"
	#event CAST_NOTARGET               "This spell only works on#*#"
	#event CAST_NOTARGET               "You must first target a group member#*#"
	sub Event_CAST_NOTARGET(string line)
		DEBUG CAST_NOTARGET
		/varset CastResult CAST_NOTARGET
		/doevents flush CAST_NOTARGET
	/return

	|- CAST_NOTREADY
	#event CAST_NOTREADY               "Spell recast time not yet met#*#"
	sub Event_CAST_NOTREADY(string line)
		DEBUG CAST_NOTREADY
		/varset CastResult CAST_NOTREADY
		/doevents flush CAST_NOTREADY
	/return

	|- CAST_OUTOFMANA
	#event CAST_OUTOFMANA              "Insufficient Mana to cast this spell#*#"
	sub Event_CAST_OUTOFMANA(string line)
		DEBUG CAST_OUTOFMANA
		/varset CastResult CAST_OUTOFMANA
		/doevents flush CAST_OUTOFMANA
	/return

	|- CAST_OUTOFRANGE
	#event CAST_OUTOFRANGE             "Your target is out of range, get closer#*#"
	sub Event_CAST_OUTOFRANGE(string line)
		DEBUG CAST_OUTOFRANGE
		/varset CastResult CAST_OUTOFRANGE
		/doevents flush CAST_OUTOFRANGE
	/return

	|- CAST_OUTDOORS
	#event CAST_OUTDOORS               "This spell does not work here#*#"
	#event CAST_OUTDOORS               "You can only cast this spell in the outdoors#*#"
	sub Event_CAST_OUTDOORS(string line)
		DEBUG CAST_NOTOUTDOORS
		/varset CastResult CAST_OUTDOORS
		/doevents flush CAST_OUTDOORS
	/return

	|- CAST_PENDING

	|- CAST_RECOVER
	#event CAST_RECOVER                "You haven't recovered yet#*#"
	#event CAST_RECOVER                "Spell recovery time not yet met#*#"
	sub Event_CAST_RECOVER(string line)
		DEBUG CAST_RECOVER
		/varset CastResult CAST_RECOVER
		/doevents flush CAST_RECOVER
	/return

	|- CAST_RESISTED
	#event CAST_RESISTED               "Your target resisted the #1# spell#*#"
	#event CAST_RESISTED               "#2# resisted your #1#!"
	sub Event_CAST_RESISTED(string line, string spell, string target)
		DEBUG CAST_RESISTED
		/varset CastResult CAST_RESISTED
		/doevents flush CAST_RESISTED
	/return

	|- CAST_STANDING
	#event CAST_STANDING               "You must be standing to cast a spell#*#"
	sub Event_CAST_STANDING(string line)
		DEBUG CAST_STANDING
		/varset CastResult CAST_STANDING
		/doevents flush CAST_STANDING
	/return

	|- CAST_STUNNED
	#event CAST_STUNNED                "You can't cast spells while stunned#*#"
	#event CAST_STUNNED                "You are stunned#*#"
	sub Event_CAST_STUNNED(string line)
		DEBUG CAST_STUNNED
		/varset CastResult CAST_STUNNED
		/doevents flush CAST_STUNNED
	/return

	|- CAST_TAKEHOLD
	#event CAST_TAKEHOLD								"Your #*# did not take hold on #*#. (Blocked by #*#.)"
	#event CAST_TAKEHOLD               "Your spell did not take hold#*#"
	#event CAST_TAKEHOLD               "Your spell would not have taken hold#*#"
	#event CAST_TAKEHOLD               "Your spell is too powerfull for your intended target#*#"
	sub Event_CAST_TAKEHOLD(string line)
		DEBUG CAST_TAKEHOLD
		/varset CastResult CAST_TAKEHOLD
		/doevents flush CAST_TAKEHOLD
	/return

	|- CAST_CANNOTSEE
	#event CAST_CANNOTSEE              "You cannot see your target#*#"
	sub Event_CAST_CANNOTSEE(string line)
		DEBUG CAST_CANNOTSEE
		/varset CastResult CAST_CANNOTSEE
		/doevents flush CAST_CANNOTSEE
	/return

	|- CAST_COMPONENTS
	#event CAST_COMPONENTS             "You are missing some required components#*#"
	#event CAST_COMPONENTS             "Your ability to use this item has been disabled because you do not have at least a gold membership#*#"
	sub Event_CAST_COMPONENTS(string line)
		DEBUG CAST_COMPONENTS
		/varset CastResult CAST_COMPONENTS
		/doevents flush CAST_COMPONENTS
	/return

	|- CAST_ABORTED

	|- CAST_FDFAIL
	#event CAST_FDFAIL                 "#1# has fallen to the ground.#*#"
	sub Event_CAST_FDFAIL(string line)
		DEBUG  CAST_FDFAIL
		/varset CastResult CAST_FDFAIL
		/doevents flush CAST_FDFAIL
	/return

	|- CAST_BLOCKED
	#event CAST_BLOCKED								"Your #*# did not take hold on #*#. (Blocked by #*#.)"
	sub Event_CAST_BLOCKED(string line)
		DEBUG CAST_BLOCKED
		/varset CastResult CAST_BLOCKED
		/doevents flush CAST_BLOCKED
	/return

	|- CAST_IMMUNE
	#event CAST_IMMUNE                 "Your target has no mana to affect#*#"
	#event CAST_IMMUNE                 "Your target is immune to changes in its attack speed#*#"
	#event CAST_IMMUNE                 "Your target is immune to changes in its run speed#*#"
	#event CAST_IMMUNE                 "Your target is immune to snare spells#*#"
	#event CAST_IMMUNE                 "Your target is immune to the stun portion of this effect#*#"
	#event CAST_IMMUNE                 "Your target looks unaffected#*#"
	sub Event_CAST_IMMUNE(string line)
		DEBUG CAST_IMMUNE
		/varset CastResult CAST_IMMUNE
		/doevents flush CAST_IMMUNE
	/return

	|-------------------------------------------------------------------------------------
	|- SUB: EventLogic819 -Brass Palace Mission
	|-------------------------------------------------------------------------------------
	Sub EventLogic819
		/if (${Spawn[Silent Sun].ID}==${Target.ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,SHD,PAL,BRD,BER,WAR]} && ${Target.Buff[Cape of Lava].ID} && !${BackOffFlag}) {
			/call DoBackOff
		} else /if (${Spawn[Silent Sun].ID}==${Target.ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,SHD,PAL,BRD,BER,WAR]} && ${BackOffFlag}) {
			/varset BackOffFlag 0
		}
	/return
	|-------------------------------------------------------------------------------------
	|- SUB: EventLogic820 -Empyr: Realm of Ash - Handles some of the named mob mechanics
	|-------------------------------------------------------------------------------------
	Sub EventLogic820
		/if (${Spawn[Stalwart Flicker].ID}==${Target.ID}) {
			/call FireTrapDebuff
		}
	/return
	|-------------------------------------------------------------------------------------
	|- TBL Debuff Handling Subs
	|-------------------------------------------------------------------------------------
	Sub FireTrapDebuff
		/if (${Me.Buff[Fire Trap].ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,BRD,BER,WAR,PAL,SHD]} && !${BackOffFlag}) {
			/call DoBackOff
		} else /if (${assistid}!=${Me.ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,BRD,BER]} && ${Me.PctHPs}<=50 && !${BackOffFlag}) {
			/call DoBackOff
		} else /if (${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,BRD,BER,WAR,PAL,SHD]} && ${BackOffFlag}) {
			/varset BackOffFlag 0
		}
	/return
	|--------------------------------------------------------------------------------------
	|-Event: DebuffFireTrap
	|--------------------------------------------------------------------------------------
	#Event DebuffFireTrap "#*#threatening to burn you if you attack#*#"
	Sub Event_DebuffFireTrap

		|- /if (${Group}) /gsay !!!FIRE TRAP!!!Backing Off!!!
		/delay 5
		:firetraploop
			/if ((${Me.Buff[Fire Trap].ID} || ${Me.Song[Fire Trap].ID}) && !${BackOffFlag}) /call DoBackOff
			/delay 1s
			/if (${Me.Buff[Fire Trap].ID} || ${Me.Song[Fire Trap].ID}) /goto :firetraploop
		/if (${BackOffFlag}) /varset BackOffFlag 0
		/doevents flush DebuffFireTrap
	/return
	|--------------------------------------------------------------------------------------
	|-Event: RainbowMez
	|--------------------------------------------------------------------------------------
	#Event RainbowMez "#*#You are enthralled by rainbows#*#"
	Sub Event_RainbowMez
		EDEBUG In RainbowMez Event
		/doevents flush RainbowMez
	/return
	|--------------------------------------------------------------------------------------
	|-Event: HotFootDebuff
	|--------------------------------------------------------------------------------------
	#Event HotFootDebuff "#*#You foot is on fire. Run to put it out#*#"
	Sub Event_HotFootDebuff
		|- /if (${Group}) /gsay !!!HOT FOOT Running to put it out!!!
		/call DoBackOff
		:hotfootloop
		/if (${Circle.Status.Equal[OFF]}) /circle on 20
		/delay 1s 
		/if (${Me.Buff[Hot Foot].ID} || ${Me.Song[Hot Foot].ID}) /goto :hotfootloop
		/if (${Circle.Status.Equal[ON]}) /circle off
		/varset BackOffFlag 0
		/doevents flush HotFootDebuff
	/return

	|-------------------------------------------------------------------------------------
	|- SUB: EventLogic795 -Enslaver of Souls
	|-------------------------------------------------------------------------------------
	Sub EventLogic795
		|- /if (${assistid}!=${Me.ID} &&  && ) {
		|-	/stick id ${assistid} 10
		|- }
		|- /if (${Me.XTarget[1].ID} && ${assistid}!=${Me.ID}) {
		|-	/call EngageAttack
		|- }
	/return
	|-------------------------------------------------------------------------------------
	|- SUB: EventLogic815 -Fell Foliage
	|-------------------------------------------------------------------------------------
	Sub EventLogic815
		/if (${assistid}!=${Me.ID} && ${Spawn[Cactiikii].ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,SHD,PAL,BRD,BER]} && ${Me.PctHPs}<=50 && !${BackOffFlag}) {
			/call DoBackOff
		} else /if (${Spawn[Cactiikii].ID} && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,SHD,PAL,BRD,BER]} && ${BackOffFlag}) {
			/varset BackOffFlag 0
		}
	/return
	|-------------------------------------------------------------------------------------
	|- SUB: EventLogic797 -Damsel of Decay
	|-------------------------------------------------------------------------------------
	Sub EventLogic797
		/if (${Zone.ID}==797) {
			/if (${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,ENC,WIZ,MAG,NEC,SHD,PAL,BRD,BER]} && (${Me.Buff[Withering Physicality XIII].ID} || ${Me.Buff[Withering Limbs XIII].ID})) {
				/if (${Me.Buff[Withering Physicality XIII].ID} && ${Me.ItemReady[135331]}) /casting 135331|item
				/if (${Me.Buff[Withering Limbs XIII].ID} && ${Me.ItemReady[35919]}) /casting 35919|item	
			}	
			/if (${Select[${Me.Class.ShortName},CLR,SHM,DRU]} && (${Me.Buff[Withering Physicality XIII].ID} || ${Me.Buff[Withering Faith XIII].ID})) {
				/if (${Me.Buff[Withering Physicality XIII].ID} && ${Me.ItemReady[35919]}) /casting 35919|item
				/if (${Me.Buff[Withering Faith XIII].ID} && ${Me.ItemReady[135331]}) /casting 135331|item
			}
			/if (${Select[${Me.Class.ShortName},WAR,SHD,PAL]} && ${Me.Buff[Withering Physicality XIII].ID}) {
				/if (${Me.Buff[Withering Physicality XIII].ID} && ${Me.ItemReady[35919]}) /casting 35919|item
			}
			/if (${Spawn[Anashti Sul, Damsel of Decay].DistanceZ.Int}>30 && ${Select[${Me.Class.ShortName},BST,RNG,MNK,ROG,ENC,WIZ,MAG,NEC,SHD,PAL,BRD,BER]} && !${Navigation.Active} && !${BackOffFlag}) {
				|-Downstairs
				/if (${Target.Z} < -400) {
					/call DoBackOff
					/delay 5
					/nav locxyz -5.51 -103.89 -421.41
					/delay 1s
					/call NavgationDelay
				} else {
					/call DoBackOff
					/delay 5
					/nav locxyz 29.59 -113.82 -370.70
					/delay 1s
					/call NavgationDelay
				}
			}
			/if (${Spawn[Anashti Sul, Damsel of Decay].DistanceZ.Int}<30 && ${BackOffFlag} && !${Navigation.Active}) /call DoBackOff
		}
	/return
	|--------------------------------------------------------------------------------------
	|-Event: 16th Anniversary Shared Task: Pirates of Timorous Deep
	|--------------------------------------------------------------------------------------
	#Event A16Pirates1 "#*#Captain Turek shouts, 'Prepare to fire the cannon!'"
	Sub Event_A16Pirates1	
		/popcustom 14 !!!MOVE TUREK === CANNONBALL INC === MOVE TUREK!!!
	/return 
	|--------------------------------------------------------------------------------------
	|-Event: Anniversary Shared Task: Pub Crawl
	|--------------------------------------------------------------------------------------
	#Event A16PubCrawl1 "#*#Galdorin Visigothe says, 'My stinky stein has rough dirty lips,'"
	Sub Event_A16PubCrawl1	
		/say My stinky stein has rough dirty lips,
	/return 
	#Event A16PubCrawl2 "#*#Galdorin Visigothe says, 'but she loves a deep carouse.'"
	Sub Event_A16PubCrawl2	
		/say but she loves a deep carouse. 
	/return 
	#Event A16PubCrawl3 "#*#Galdorin Visigothe says, 'Beer or ale are her great trips.'"
	Sub Event_A16PubCrawl3	
		/say Beer or ale are her great trips. 
	/return 
	#Event A16PubCrawl4 "#*#Galdorin Visigothe says, 'No matter how many vows'"
	Sub Event_A16PubCrawl4	
		/say No matter how many vows
	/return 
	#Event A16PubCrawl5 "#*#Galdorin Visigothe says, 'I make or break, my drinking glass'"
	Sub Event_A16PubCrawl5	
		/say I make or break, my drinking glass
	/return 
	#Event A16PubCrawl6 "#*#Galdorin Visigothe says, 'reminds me of my lovely Brasse.'"
	Sub Event_A16PubCrawl6	
		/say reminds me of my lovely Brasse.
	/return 
	|--------------------------------------------------------------------------------------
	|-Event: 15th Anniversary Group Mission: War Games
	|--------------------------------------------------------------------------------------
	#Event A15WarGames1 "#*#A catapult is about to fire in your direction!"
	Sub Event_A15WarGames1	
		/mgax //popcustom 14 !!!MOVE === INC AE ON ${Me.CleanName}=== MOVE!!!
	/return
	|--------------------------------------------------------------------------------------
	|-Event: The Return of King Xorbb
	|--------------------------------------------------------------------------------------
	#Event Xorbb3 "#*#King Xorbb shouts '|${Me.CleanName}|'"
	Sub Event_Xorbb3
		/call PrintGroupMessage "I need to face away from him for a bit"
		/beep
		/if (${Me.Combat}) /squelch /attack off 
		/if (${Stick.Active}) /stick off
		/target id ${Spawn[npc King Xorbb].ID}
		/delay 5
		/squelch /face away
		/delay 16s
	/return
	|- Helper tool for boxing ToV GD mission
	#Event Narandi "#*#Narandi the Restless melts, a pool of water appearing at its feet."
	Sub Event_Narandi
		/if (!${DoZoneLogic[SETTINGVAL]}) /return
		/popup >>> Switch Target ${Target.CleanName} <<<
	/return

	| Icebound Avatar mission
	#Event IceAoW "#*#The ice encrusted Avatar of War shouts that |${Me.DisplayName}| must bend the knee#*#"
	#Event IceAoWUnduck "#*#The Avatar of War nods, accepting the subservience of those that gave it.#*#"
	sub Event_IceAoW()
		/if (!${DoZoneLogic[SETTINGVAL]}) /return
		/declare duckCounter int local 0
		/if (${Select[${Me.Class.ShortName},BRD]} && (${Me.Casting.ID} || ${Me.BardSongPlaying})) {
			/while (${Me.Casting.ID} || ${Me.BardSongPlaying}) {
				
				/stopsong
				/stopcast
				/delay 10 !${Me.Casting.ID}
			}

		} else {
			/if (${Me.Casting.ID}) {
				/stopcast
			}
		}

		/dt ${assistname} (${Me.Animation} != 24)
		/if (${Me.Animation} != 24) {
		/keypress DUCK
		/echo ducking
		}
	/delay 2
	/dt ${assistname} my current animation is ${Me.Animation} and supposed to be 24
	/while (!${Select[${Me.Animation},24]}) {
		/varcalc duckCounter ${duckCounter}+1
		/if (${duckCounter} > 15) {
		/echo Someone messed with the gods and you have been found lacking
		/break
		}
		/keypress left
		/delay 1s
		/if (${Select[${Me.Animation},24]}) {
		/break
		}
	/dt ${assistname} im not ducked
	}
	/dt ${assistname} I am Ducked Finally!

	/delay 8s

	/dt ${assistname} my current animation is ${Me.Animation} and supposed to be 24
		/if (${Select[${Me.Animation},24]}) {
			/keypress DUCK
		}

	/return TRUE

| ----------------------------------------------------------------------------
| SUB: Event AskForBuffs
| ----------------------------------------------------------------------------
#Event AskForBuffs       "#1# tells you,#*#Buffs Please!#*#"
#Event AskForBuffs       "#1# says,#*#Buffs Please!#*#"
    
	Sub Event_AskForBuffs(string Line, AFBCaller)
        DEBUGBUFF AskForBuffs: Enter
        /declare WorkID int local ${Int[${Spawn[${AFBCaller}].ID}]}
        /if (!${AFBCaller.Length} || ${AFBCaller.Equal[null]} || !${WorkID} || ${WorkID}==${Me.ID}) /return
        /if (${Group.Member[${AFBCaller}].Index} || ${Spawn[id ${WorkID}].Type.NotEqual[PC]}) /return
        /if ( (${Raid.Member[${AFBCaller}].Group}) || (${Me.Fellowship.Member[${AFBCaller}].Level}) || (${Me.Guild.Equal[${Spawn[${AFBCaller}].Guild}]}) || (${Friends.Friend[${AFBCaller}]}) ) {
            /call Bind_TooBuffList add ${WorkID}
        } else {
		    /call PrintGroupMessage "Some Schmuck named ${AFBCaller} is trying to ask for buffs"
            DEBUGBUFF AskForBuffs: Exit
		}
    /return

| ----------------------------------------------------------------------------
| SUB: Buff List
| ----------------------------------------------------------------------------
   Sub Bind_TooBuffList(string Action, int ActionID)
        DEBUGBUFF TooBuffList: Enter
        /declare WorkOnID int local ${Int[${ActionID}]}
        /declare WorkOnName string local
        /declare j1 int local 0
        /if (!${WorkOnID}) /varset WorkOnID ${Target.ID}
        DEBUGBUFF TooBuffList: Action: ${Action} ActionID: ${ActionID} WorkOnID: ${WorkOnID}
        /if (!${WorkOnID} && ${Select[${Action},add,remove]}>0) {
            /echo Invalid ID. Please target a Character or use a proper ID.
            /return
        }
        /varset WorkOnName ${Spawn[id ${WorkOnID}].CleanName}
        /if (!${Action.Length} || ${Action.Equal[null]} || ${Select[${Action},add,remove,reset,clear]}==0) {
            /echo Invalid Action for Too Buff List, please use add, remove, reset or clear.
            /return
        }
        /if (${Action.Equal[reset]}) {
            /if (${ExtendedBuffList.Count[|]}>0) {
                /varset j1 1
                /while (${ExtendedBuffList.Arg[${j1},|].Length} && ${ExtendedBuffList.Arg[${j1},|].NotEqual[null]}) {
                    /if (!${Spawn[=${ExtendedBuffList.Arg[${j1},|]}].ID}) {
                        /echo Removed ${ExtendedBuffList.Arg[${j1},|]} from the Too Buff List.
                        /varset ExtendedBuffList ${ExtendedBuffList.Replace[${ExtendedBuffList.Arg[${j1},|]}|,]}
                    } else {
                        /varcalc j1 ${j1}+1
                    }
                }
            }
        } else /if (${Action.Equal[remove]}) {
            /if (${ExtendedBuffList.Find[${WorkOnName}|]}) {
                /varset ExtendedBuffList ${ExtendedBuffList.Replace[${WorkOnName}|,]}
                /echo Removed ${WorkOnName} from Too Buff List.
            } else {
                /echo ${WorkOnName} Not Found on the Too Buff List.
            }
        } else /if (${Action.Equal[clear]}) {
            /echo Too Buff List Cleared.
            /varset ExtendedBuffList
        } else {
            /if (${ExtendedBuffList.Count[|]}>49) {
                /echo There is a limit of 50 ID's. Please remove some before trying to add more.
                /return
            }
            /if (${ExtendedBuffList.Find[${WorkOnName}|]}) {
                /echo ${WorkOnName} Found on Too Buff List. No Need to add again.
                /return
            }
            /if (${Macro.IsTLO[DanNet]}) {
                |/if (${DanNet.Peers[all].Find[${WorkOnName}|]}) {
                /if (${DanNet.Peers[all].Find[${WorkOnName}|]}) {
                    /echo ${WorkOnName} Found on DanNet Peers[all] List. No Need to add.
                    /return
                }
            }
            /varset ExtendedBuffList ${ExtendedBuffList}${WorkOnName}|
            /echo Added ${WorkOnName} to the Too Buff List.
        }
        /varset g_ExtendedBuffList ${ExtendedBuffList}
        DEBUGBUFF TooBuffList: Exit
    /return
