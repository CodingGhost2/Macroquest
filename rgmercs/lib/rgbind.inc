|-------------------------------------------------------------------------------------
|- ###################################################################################
|- RG GENERAL BIND SECTION
|- ###################################################################################
|-------------------------------------------------------------------------------------
| - Bind: /automode
| - Auto Mode - A setting of 0 Will Turn off RGmercs Autotargetting/Engage Function
| - Providing a Manual Movement And Targetting ability. Great for Some Encounters.
| - A Setting of 1 Turns on Standard Auto RG mercs Functions and Allows it to target And 
| - Engage as it pleases. , Also Turns off Medding as its Manual!
#bind TooBuffList    /tbmanager
#bind automode /automode
Sub Bind_automode(int value)
    /varset DoAutoTarget[SETTINGVAL] ${value}
    /varset DoAutoEngage[SETTINGVAL] ${value}
    /varset DoMed[SETTINGVAL] ${value}
    /if (!${value}) /echo Auto Mode has Been Turned OFF! - Your in charge now.
    /if (${value}) /echo Auto Mode is Back On - You can relax now.
/return   
| - Bind: /dotank
| - Dotank - Changes War/SHD/Pally Mode to tank or not and checks proper
| - Options Based on Mode.
#bind dotank /dotank 
Sub Bind_dotank(int value)
    /varset DoTank[SETTINGVAL] ${value}
    /call ${Me.Class.ShortName}_CheckOptions
    /if ( ${DoTank[SETTINGVAL]} ) /echo I am now Tanking     
    /if ( !${DoTank[SETTINGVAL]} ) /echo I am now DPSing  
/return  

|----------------------------------------------------------------------------
|- BIND: navto
|- /navto [me|target]
|----------------------------------------------------------------------------
#bind navto /navto
Sub Bind_navto(string to)
    /if (${to.Equal[me]}) {
        /dggae /nav id ${Me.ID}
    } else /if (${to.Equal[target]}) {
        /dggae /nav id ${Target.ID}
    }
/return
|----------------------------------------------------------------------------
|- BIND: levelinfo
|- /levelinfo
|----------------------------------------------------------------------------
#bind levelinfo /levelinfo
Sub Bind_levelinfo
    /call PrintGroupMessage "${Me.Name} is level ${Me.Level} - I Am ${Me.PctExp}% thru My Current Level"
/return

|----------------------------------------------------------------------------
|- BIND: AAinfo
|- /aainfo
|----------------------------------------------------------------------------
#bind aainfo /aainfo
Sub Bind_aainfo
    /call PrintGroupMessage "${Me.Name} I have ${Me.AAPoints} Unspent - I Am ${Me.PctAAExp}% thru My Current AA"
/return

|----------------------------------------------------------------------------
|- BIND: lesson
|- /lesson
|----------------------------------------------------------------------------
#bind lesson /lesson
Sub Bind_lesson
	/if (${RG_AAReady[481]}) {
        /call PrintGroupMessage "${Me.Name} is Activating ${Me.AltAbility[481].Name} now!"
        /alt act 481
    } else { 
        /call PrintGroupMessage "${Me.Name}'s' lesson is unavaialble right now"
    }

/return

|----------------------------------------------------------------------------
|- BIND: Dropinvis
|- /dropinvis
|----------------------------------------------------------------------------
#bind dropinvis /dropinvis
Sub Bind_dropinvis
	/noparse /dgga /makemevis
/return
|----------------------------------------------------------------------------
|- BIND: DropLev
|- /droplev
|----------------------------------------------------------------------------
#bind droplev /droplev
Sub Bind_droplev
	/noparse /dgga /removelev
/return
|----------------------------------------------------------------------------
|- BIND: Droptravel
|- /droptravel
|----------------------------------------------------------------------------
#bind droptravel /droptravel
Sub Bind_droptravel
	/noparse /dgga /removelev
    /noparse /dgga /makemevis
/return

|----------------------------------------------------------------------------
|- BIND: Giveitem
|- /giveitem
|- Gives item item_name to npc_name using a partial match.
|----------------------------------------------------------------------------
#bind giveitem /giveitem
Sub Bind_giveitem(string item_name, int amount, string npc_name)
    /if (!${FindItemCount[${item_name}]}) /return FALSE
    /declare give_spawn_id int local 0
    /if (!${npc_name.Length}) {
        /varset give_spawn_id ${Target.ID}
    } else {
        /varset give_spawn_id ${Spawn[${npc_name}].ID}
    }

    /call GiveTo ${give_spawn_id} "${FindItem[${item_name}].Name}" ${amount} ${Spawn[id ${give_spawn_id}].Type.Equal[Pet]}
/return

|----------------------------------------------------------------------------
|- BIND: GiveMoney
|- /givemoney
|- Gives ${amount} of money with type ${money} to Target.ID.
|- Type must be pp, gp, sp, or cp.
|----------------------------------------------------------------------------
#bind GiveMoney /givemoney
Sub Bind_GiveMoney(int amount, string money, string spawn_name)
    /declare give_spawn_id int local 0
    /if (!${spawn_name.Length}) {
        /varset give_spawn_id ${Target.ID}
    } else {
        /varset give_spawn_id ${Spawn[${spawn_name}].ID}
    }
    /call GiveMoney ${give_spawn_id} ${amount} ${money}
/return

#bind printrotation /printrotation
Sub Bind_printrotation
    /echo Downtime Rotation 
    /call Ordered_Rotation_Print ${Me.Class.ShortName}_Downtime_${ClassMode[SETTINGVAL]}_Rotation
    /echo Debuff Rotation
    /call Ordered_Rotation_Print ${Me.Class.ShortName}_Debuff_${ClassMode[SETTINGVAL]}_Rotation
    /echo DPS Rotation
    /call Ordered_Rotation_Print ${Me.Class.ShortName}_DPS_${ClassMode[SETTINGVAL]}_Rotation
    /echo Burn Rotation
    /call Ordered_Rotation_Print ${Me.Class.ShortName}_Burn_${ClassMode[SETTINGVAL]}_Rotation
/return

|----------------------------------------------------------------------------
|- BIND: kaenform
|- /kaenform
|- Moves group to a moon around you with minimal fuss.
|----------------------------------------------------------------------------
#bind kaenform /kaenform
Sub Bind_kaenform(int radius)
    /declare i int local 0
    /for i 1 to ${Math.Calc[${Group}]}
        /dexecute ${Group.Member[${i}]} /moveto loc ${Math.Calc[${Me.Y} + (8 * ${Math.Sin[${Math.Calc[36*${i}]} + (${Me.Heading.Degrees} - 196)]})]} ${Math.Calc[${Me.X} + (8 * ${Math.Cos[${Math.Calc[36*${i}]} + (${Me.Heading.Degrees} - 196)]})]}
    /next i
/return

|----------------------------------------------------------------------------
|- BIND: randomform
|- /randomform
|- Moves group to a random place around you
|----------------------------------------------------------------------------
#bind randomform /randomform
Sub Bind_randomform(int radius)
    /if (!${radius}) /varset radius 20
    /declare i int local 0
    /for i 1 to ${Math.Calc[${Group}]}
        /dexecute ${Group.Member[${i}]} /moveto loc ${Math.Calc[${Me.Y} ${If[${Math.Rand[1]},+,-]} ${Math.Rand[${radius}]}]} ${Math.Calc[${Me.X} ${If[${Math.Rand[1]},+,-]} ${Math.Rand[${radius}]}]}
    /next i
/return

|----------------------------------------------------------------------------
|- BIND: SheepMove - Credit EQMules mod of kissassist
|- Helper move function for other binds.
|----------------------------------------------------------------------------
#bind SheepMove /sheepmove
Sub Bind_SheepMove(int shepherdID, int l_YLoc, int l_XLoc)
    /echo shepherdID=${shepherdID} l_YLoc=${l_YLoc} l_XLoc=${l_XLoc}
    /if (!${shepherdID}) {  
        /echo cant invoke sheepmove, not enough arguments supplied
        /return
    }
    /declare oldRTC int local 0
    /declare oldChase int local 0
    /if (${Bool[${Plugin[mq2moveutils]}]}==TRUE) {
        /varset oldRTC ${ReturnToCamp[SETTINGVAL]}
        /if (${Bool[${Plugin[mq2advpath]}]}==TRUE) {
                    /play off
        }
        /if (${Bool[${Plugin[mq2navigation]}]}==TRUE || ${Bool[${Plugin[mq2nav]}]}==TRUE) {
                /if (${Navigation.Active}) {
                /nav stop
            }
        }
        /varset ReturnToCamp[SETTINGVAL] 0
        /if (${MoveTo.Moving}) /moveto off
        /if (${Stick.Active}) /squelch /stick off
        /moveto mdist 3
        /moveto loc ${l_YLoc} ${l_XLoc}
        /delay 3s ${MoveTo.Moving}
        /delay 30s !${MoveTo.Moving}
        /delay 1s
        /moveto mdist 5
        /face id ${shepherdID}
        /if (${oldRTC}) /varset ReturnToCamp[SETTINGVAL] 1
    } else {
        /echo \aw SheepMove failed because you don't have \ag mq2moveutils \aw loaded.
    }
/return


|----------------------------------------------------------------------------
|- BIND: GroupFrontFace /GroupFrontFace - Credit EQMules mod of kissassist
|----------------------------------------------------------------------------
#bind GroupFrontFace /groupfrontface
Sub Bind_GroupFrontFace(string radius)
    /declare GrpCount int local 0
    /call PlayersInGroup
    /varset GrpCount ${Macro.Return}
    /if (!${GrpCount}) {
        /echo no members in the group to order around, returning
        /return
    }
    /declare i int local 0
    /declare XOff float local 0
    /declare YOff float local 0
    /declare XMove float local 0
    /declare YMove float local 0
    /declare BaseRadians local
    /declare Multiplier local 90
    /if (${GrpCount}==2) {
        /varset Multiplier 45
    } else /if (${GrpCount}==3) {
        /varset Multiplier 30
    } else /if (${GrpCount}==4) {
        /varset Multiplier 23
    } else /if (${GrpCount}==5) {
        /varset Multiplier 18
    }
    /declare MyHeading float local ${Math.Calc[${Me.Heading.Degrees} - ${Multiplier}]}
    /declare BaseRadian float local ${Math.Calc[180 / ${GrpCount}]}
    /for i 1 to ${Group.Members}
        /if (${Group.Member[${i}].Type.Equal[PC]}) {
            /varcalc XMove ${Math.Cos[ ${BaseRadian} * ${Float[${i}]} + (${MyHeading}) ]}
            /varcalc YMove ${Math.Sin[ ${BaseRadian} * ${Float[${i}]} + (${MyHeading}) ]}
            /varcalc XOff ${Me.X} + ( ${Int[${radius}]} * ${XMove} )
            /varcalc YOff ${Me.Y} + ( ${Int[${radius}]} * ${YMove} )
            /dexecute ${Group.Member[${i}]} /sheepmove ${Me.ID} ${YOff} ${XOff}
        }
    /next i
/return

|----------------------------------------------------------------------------  
|- SUB: /combatreset
|----------------------------------------------------------------------------    
#bind combatreset           /combatreset
Sub Bind_combatreset  
    /call KillReset
/return
|----------------------------------------------------------------------------  
|- SUB: /backoffmob - Back Off and stop melee  New Version
|----------------------------------------------------------------------------    
#bind BackOff           /backoffmob
Sub Bind_BackOff  
    /call DoBackOff
/return

Sub DoBackOff
    /if (${BackOffFlag}) {
        /echo \aw Resetting. No Longer Backing off. \ar OFF
        /varset BackOffFlag 0
    } else {
        /echo \aw Resetting. Backing off. \ag ON
        /if (${Target.ID}) /target clear
        /if (${Me.Combat}) /squelch /attack off 
        /if (${Stick.Active}) /stick off
        /if (${Me.Pet.ID}) /pet back off
        /if (${Navigation.Active}) /nav stop
        /if (${DoMercenary[SETTINGVAL]}) /stance passive
        /varset BackOffFlag 1
        /call AutoCampCheck
    }
    /doevents flush Event_BackOff  
/return

|----------------------------------------------------------------------------
|- BIND: GroupBehindMe /GroupBehindMe - Credit EQMules mod of kissassist
|----------------------------------------------------------------------------
#bind GroupBehindMe /groupbehindme
Sub Bind_GroupBehindMe(string radius)
    /declare GrpCount int local 0
    /call PlayersInGroup
    /varset GrpCount ${Macro.Return}
    /if (!${GrpCount}) {
        /echo no members in the group to order around, returning
        /return
    }
    /declare i int local 0
    /declare XOff float local 0
    /declare YOff float local 0
    /declare XMove float local 0
    /declare YMove float local 0
    /declare BaseRadians local
    /declare Multiplier local 270
    /if (${GrpCount}==2) {
        /varset Multiplier 224
    } else /if (${GrpCount}==3) {
        /varset Multiplier 208
    } else /if (${GrpCount}==4) {
        /varset Multiplier 200
    } else /if (${GrpCount}==5) {
        /varset Multiplier 196
    }
    /declare MyHeading float local ${Math.Calc[${Me.Heading.Degrees} - ${Multiplier}]}
    /declare BaseRadian float local ${Math.Calc[180 / ${GrpCount}]}
    /for i 1 to ${Group.Members}
        /if (${Group.Member[${i}].Type.Equal[PC]}) {
            /varcalc XMove ${Math.Cos[ ${BaseRadian} * ${Float[${i}]} + (${MyHeading}) ]}
            /varcalc YMove ${Math.Sin[ ${BaseRadian} * ${Float[${i}]} + (${MyHeading}) ]}
            /varcalc XOff ${Me.X} + ( ${Int[${radius}]} * ${XMove} )
            /varcalc YOff ${Me.Y} + ( ${Int[${radius}]} * ${YMove} )
            /dexecute ${Group.Member[${i}]} /sheepmove ${Me.ID} ${YOff} ${XOff}
        }
    /next i
/return

|----------------------------------------------------------------------------
|- SUB: Campfire /campfireRG ${Window[FellowshipWnd].Child[FP_CampPage].Child[FP_CampsiteViewer].Text}
|----------------------------------------------------------------------------
#bind Campfire          /campfire
Sub Bind_Campfire(int camptype)
    /if (${camptype} == -1) {
        /call DestroyCampfire
        /return TRUE
    }
    /if (${Select[${Zone.ID},33506]}) /return
    /if ( !${Me.Fellowship} || ${Me.Fellowship.Campfire} ) {
        /echo \arNot in a fellowship or already have a campfire -- not putting one down.
        /return
    }
    /declare FellowCount int local 0
    /declare i int local
    /declare j int local

     /if (${MaintainCampfire[SETTINGVAL]}>1) {
        /if (${FindItemCount[Fellowship Campfire Materials]}<1) {
            /call RGChangeSetting Settings MaintainCampfire 1
            /echo Fellowship Campfire Materials Not Found. Setting to Regular Fellowship.
        }
    }
    /for i 1 to ${SpawnCount[pc radius 50]}
        /for j 1 to ${Me.Fellowship.Members}
            /if (${NearestSpawn[${i},PC radius 50].CleanName.Equal[${Me.Fellowship.Member[${j}]}]}) /varcalc FellowCount ${FellowCount}+1
        /next j
    /next i
    
    /if (${FellowCount}>=3) {
        /windowstate FellowshipWnd open
        /delay 3s ${Window[FellowshipWnd].Open}
        /nomodkey /notify FellowshipWnd FP_Subwindows tabselect 2
        /if (${Me.Fellowship.Campfire}) {
            /if (!${Select[${Me.Fellowship.CampfireZone.ID},${Zone.ID}]}) {
                /nomodkey /notify FellowshipWnd FP_DestroyCampsite leftmouseup
                /delay 5s ${Window[ConfirmationDialogBox].Open}
                /if (${Window[ConfirmationDialogBox].Open}) {
                    /nomodkey /notify ConfirmationDialogBox Yes_Button leftmouseup
                }
                /delay 5s !${Me.Fellowship.Campfire}
            }
        }
        /nomodkey /notify FellowshipWnd FP_RefreshList leftmouseup
        /delay 1s
        /nomodkey /notify FellowshipWnd FP_CampsiteKitList listselect ${If[${MaintainCampfire[SETTINGVAL]},${MaintainCampfire[SETTINGVAL]},${camptype}]}
        /delay 1s
        /nomodkey /notify FellowshipWnd FP_CreateCampsite leftmouseup
        /delay 5s ${Me.Fellowship.Campfire}
        /windowstate FellowshipWnd close
        /if (${Me.Fellowship.Campfire}) /echo Campfire Dropped
    } else {
        /echo Can't create campfire. Only ${FellowCount} nearby. Setting MaintainCampfire to 0.
        /varset MaintainCampfire[SETTINGVAL] 0
    }
/return
Sub DestroyCampfire
    /windowstate FellowshipWnd open
    /delay 3s ${Window[FellowshipWnd].Open} 
    /nomodkey /notify FellowshipWnd FP_Subwindows tabselect 2     
    /nomodkey /notify FellowshipWnd FP_DestroyCampsite leftmouseup
    /delay 5s ${Window[ConfirmationDialogBox].Open}
    /if (${Window[ConfirmationDialogBox].Open}) {
        /nomodkey /notify ConfirmationDialogBox Yes_Button leftmouseup
    }
    /delay 5s !${Me.Fellowship.Campfire}
    /windowstate FellowshipWnd close
/return TRUE
|-------------------------------------------------------------------------------------
|- SUB: BIND KillMATarget
|-------------------------------------------------------------------------------------
#bind KillMATarget /killtarget
Sub Bind_KillMATarget
    /call KillTarget
/return

|-------------------------------------------------------------------------------------
|- SUB: BIND killnow
|-------------------------------------------------------------------------------------
#bind killnow /killnow
Sub Bind_killnow
    /call SetControlToon
    /call SetTarget ${Spawn[${Spawn[id ${assistid}].AssistName}].ID}
    /delay 1s ${Target.ID} == ${Spawn[${Spawn[id ${assistid}].AssistName}].ID}
    /face fast
    /varset autotargetid ${Target.ID}
    /call EngageTarget
/return

|-------------------------------------------------------------------------------------
|- SUB: BIND SetAutoTargetID
|-------------------------------------------------------------------------------------
#bind SetAutoTargetID /autotarget
Sub Bind_SetAutoTargetID
    /varset autotargetid ${Target.ID}
/return

|-------------------------------------------------------------------------------------
|- SUB: BIND QuestSay
|-------------------------------------------------------------------------------------
#bind QuestSay /qsay
Sub Bind_QuestSay(string QSayText)
    /squelch /dggaexecute /target id ${Target.ID}
    /delay 5
    /squelch /dggaexecute /say ${QSayText}
    /delay 5
/return

|-----------------------------------------------------------------------------
|- Sub: Bind_port
|- /port [pok|guildhall|lobby|air|fire|stone|gorowyn|froststone|stratos|fm|skyfire|ghlobby|poh|tbm] 
|- cred: Exspes
|-----------------------------------------------------------------------------

#bind port /port
sub Bind_port(string _location)

    /declare _tmpItem string local
    /if (${Me.Sitting}) {
        /varset InMedState FALSE
        /stand
    }

    /if (${_location.Equal[air]}) {
        /while (!${FindItem[Wishing Lamp: Zephyr's Flight].ID}) {
            /convertitem Wishing Lamp:
            /delay 1s                   
        }
        /varset _tmpItem Wishing Lamp: Zephyr's Flight
        
    } else /if (${_location.Equal[fire]}) {
        /while (!${FindItem[Wishing Lamp: Palace of Embers].ID}) {
            /convertitem Wishing Lamp:
            /delay 1s                   
        }
        /varset _tmpItem Wishing Lamp: Palace of Embers
        
    } else /if (${_location.Equal[stone]}) {
        /while (!${FindItem[Wishing Lamp: The Stone Demesne].ID}) {
            /convertitem Wishing Lamp:
            /delay 1s                   
        }
        /varset _tmpItem Wishing Lamp: The Stone Demesne               
    } else /if (${_location.Equal[pok]}) {
        /call ItemNow "Drunkard's Stein"
    } else /if (${_location.Equal[lobby]}) {
        /if (${RG_AAReady[511]}) {
            /call AANow 511

        } else {
            /echo Throne of Hero's is not ready
        }
    } else /if (${_location.Equal[guildhall]}) {
        /if (${Me.ItemReady[=Primary Anchor Transport Device]}) {
            /call ItemNow "Primary Anchor Transport Device"
        } else /if (${Me.ItemReady[=Secondary Anchor Transport Device]}) {
            /call ItemNow "Secondary Anchor Transport Device"
        } else {
            /echo Guild Hall clickies are down
        }
    } else /if (${_location.Equal[gorowyn]}) {
        /itemtarget "Gorowyn Translocator Lantern"
        /delay 1s
        /nav item
        /delay 1s
        /while (${Navigation.Active}) {
            /delay 1s
        }
        /click right item
        /delay 1s
        /notify "teleport to" menuselect
    } else /if (${_location.Equal[froststone]}) {
        /itemtarget "Froststone Crystal Echo"
        /delay 1s
        /nav item
        /delay 1s
        /while (${Navigation.Active}) {
            /delay 1s
        }
        /click right item
        /delay 1s
        /notify "teleport to" menuselect
    } else /if (${_location.Equal[stratos]}) {
        /itemtarget "Stratos Fire Platform"
        /delay 1s
        /nav item
        /delay 1s
        /while (${Navigation.Active}) {
            /delay 1s
        }
        /click right item
        /delay 1s
        /notify "teleport to" menuselect
    } else /if (${_location.Equal[fm]}) {
        /itemtarget "Ancient Iksar Translocator Statue"
        /delay 1s
        /nav item
        /delay 1s
        /while (${Navigation.Active}) {
            /delay 1s
        }
        /click right item
        /delay 1s
        /notify "teleport to" menuselect
    } else /if (${_location.Equal[ghlobby]}) {
		/if (${Zone.ShortName.Find[guildhall]}) {
			/itemtarget "Shabby Lobby Door"
			/delay 1s
			/nav item
			/delay 1s
			/while (${Navigation.Active}) {
				/delay 1s
			}
			/click right item
			/delay 1s
			/notify "open the door" menuselect
		} else {
			/if (${PCAAReady[Throne of Heroes]}) {
				/call AANow ${Me.AltAbility[Throne of Heroes].ID} ${Me.ID}
			} else {
				/echo \awNOTICE:\ax Throne of Heroes not ready.
			}
		}
    } else /if (${_location.Equal[poh]}) {
        /itemtarget "Cynosure of Health"
        /delay 1s
        /nav item
        /delay 1s
        /while (${Navigation.Active}) {
            /delay 1s
        }
        /click right item
        /delay 1s
        /notify "teleport to" menuselect
    } else /if (${_location.Equal[tbm]}) {
        /call ItemNow "Mirror Fragment of Anashti Sul"
    } else /if (${_location.Equal[fellowship]}) {
		/call ItemNow "Fellowship Registration Insignia"
	}
/return
|-----------------------------------------------------------------------------
|- Sub: Bind_yes
|- /yes
|- 
|-----------------------------------------------------------------------------

#bind yes /yes
sub Bind_yes()
/dggaexecute /notify LargeDialogWindow LDW_YesButton leftmouseup
/dggaexecute /notify LargeDialogWindow LDW_OkButton leftmouseup
/dggaexecute /notify ConfirmationDialogBox CD_Yes_Button leftmouseup
/dggaexecute /notify ConfirmationDialogBox CD_OK_Button leftmouseup
/dggaexecute /notify TradeWND TRDW_Trade_Button leftmouseup
/dggaexecute /notify GiveWnd GVW_Give_Button leftmouseup 
/dggaexecute /notify ProgressionSelectionWnd ProgressionTemplateSelectAcceptButton leftmouseup ; /notify TaskSelectWnd TSEL_AcceptButton leftmouseup
/dggaexecute /notify RaidWindow RAID_AcceptButton leftmouseup
/return

|-----------------------------------------------------------------------------
|- Sub: Bind_door
|- /door
|- 
|-----------------------------------------------------------------------------

#bind clickdoor /clickdoor
sub Bind_clickdoor
/dggae /doortarget
/delay 1s
/dggae /click left door
/return

|-------------------------------------------------------------------------------------
|- SUB: BIND Bind_lazylobbyrez
|- credit: TreeHuginDruid RIP
|-------------------------------------------------------------------------------------
#bind lazylobbyrez /lazylobbyrez
Sub Bind_lazylobbyrez
    /declare SoulStoneMerchant     	string local   "A Disciple of Luclin"
	/declare CorpseSummoner 	    string local   "A Priestess of Luclin"
	/declare RangeDist              int    local   8
	/declare SoulStoneName		    string local
	/declare bag               	    string local
	/declare slot              	    string local
	/declare ItemToGet              string local
	/declare MercClass              string local
	/declare i			            int    local

	/squelch /target clear
	/delay 10

    /if (!${Plugin[MQ2Nav].Name.Equal[MQ2Nav]}) {
		/echo Loading MQ2Nav
		/squelch /plugin MQ2Nav load
		/delay 1s
		/if (!${Plugin[MQ2Nav].Name.Equal[MQ2Nav]}) {
			/beep
			/echo Unable to load MQ2MoveUtils plugin, stopping.
			/return
		}
	} else {
		/echo MQ2Nav plugin is loaded.
	}
    /if (!${Zone.Name.Equal[Guild Lobby]}) {
        /echo Get your lazy self to the Guild Lobby!
        /return
    }

    /if (${Me.Level}<=115) /varset SoulStoneName Velium Soulstone
	/if (${Me.Level}<=110) /varset SoulStoneName Draconic Soulstone
	/if (${Me.Level}<=105) /varset SoulStoneName Torrential Soulstone
	/if (${Me.Level}<=100) /varset SoulStoneName Coalescent Soulstone
	/if (${Me.Level}<=95) /varset SoulStoneName Luminous Soulstone
	/if (${Me.Level}<=90) /varset SoulStoneName Phantasmal Soulstone
	/if (${Me.Level}<=85) /varset SoulStoneName Iridescent Soulstone
	/if (${Me.Level}<=80) /varset SoulStoneName Prismatic Soulstone
	/if (${Me.Level}<=75) /varset SoulStoneName Glowing Soulstone
	/if (${Me.Level}<=70) /varset SoulStoneName Pristine Soulstone
	/if (${Me.Level}<=55) /varset SoulStoneName Faceted Soulstone
	/if (${Me.Level}<=50) /varset SoulStoneName Greater Soulstone
	/if (${Me.Level}<=40) /varset SoulStoneName Soulstone
	/if (${Me.Level}<=30) /varset SoulStoneName Lesser Soulstone
	/if (${Me.Level}<=20) /varset SoulStoneName Minor Soulstone
	/delay 10
	/echo Soulstone for my level (${Me.Level}) is (${SoulStoneName}).

    /if (${FindItem[${SoulStoneName}].ID}) {
		/echo I already have a (${SoulStoneName}).
	} 
    /if (!${FindItem[${SoulStoneName}].ID}) {
		/echo I do not have a (${SoulStoneName}).

        /nav spawn npc ${SoulStoneMerchant}
        /while (${Navigation.Active}) {
        /if (${Spawn[npc ${SoulStoneMerchant}].Distance3D} < 20) /break
        /delay 5
        }
        /squelch /target npc ${SoulStoneMerchant}
        /delay 2s ${Target.ID}==${Spawn[npc ${SoulStoneMerchant}].ID}
        /face
    } 

    /echo We have arrived at ${SoulStoneMerchant}
	/nomodkey /click right target
	/delay 10s ${Merchant.ItemsReceived}

	/if (${Merchant.ItemsReceived}) {
		/delay 3s
		/varset ItemToGet ${Window[MerchantWnd].Child[ItemList].List[=${SoulStoneName},2]}
	}

	/if (!${ItemToGet}) {
		/echo I couldn't find (${SoulStoneName})  to purchase!
		/return
	} else {
		/echo Found (${SoulStoneName}) to purchase!
		/notify MerchantWnd ItemList listselect ${ItemToGet}
		/delay 10
		/notify MerchantWnd ItemList LeftMouseUp ${ItemToGet}
		/delay 10
		/nomodkey /notify MerchantWnd MW_Buy_Button LeftMouseUp
		/delay 10
	}
    :CloseMerchantWnd1
	/if (${Window[MerchantWnd].Open}) {
		/nomodkey /notify MerchantWnd MW_Done_Button LeftMouseUp
		/delay 10
		/if (${Window[MerchantWnd].Open}) /goto :CloseMerchantWnd1
	}

    /nav spawn npc ${CorpseSummoner}
    /while (${Navigation.Active}) {
        /if (${Spawn[npc ${CorpseSummoner}].Distance3D} < 20) /break
        /delay 5
    }
    /squelch /target npc ${CorpseSummoner}
    /delay 2s ${Target.ID}==${Spawn[npc ${CorpseSummoner}].ID}
    /face

	/echo Attempting to grab (${SoulStoneName}).
	/if (!${Window[InventoryWindow].Open}) /keypress Inventory
	/delay 5
	/itemnotify "${SoulStoneName}" leftmouseup
	/delay 5

	/if (${Cursor.ID} && ${Cursor.Name.Equal[${SoulStoneName}]}) {
		/echo I have (${SoulStoneName}) on my cursor.
		/echo Giving (${Cursor.Name}) to (${Target.CleanName}).
    }
	:OpenGiveWindowB
		/nomodkey /click left target
		/delay 5s ${Window[GiveWnd].Open}
		/if (!${Window[GiveWnd].Open}) /goto :OpenGiveWindowB
	:GiveSoulStone
		/if (${Window[GiveWnd].Open}) {
			/notify GiveWnd GVW_Give_Button leftmouseup
			/delay 3s
			/if (${Window[GiveWnd].Open}) /goto :GiveSoulStone
		}
	:CloseInvWnd
    	/if (${Window[InventoryWindow].Open}) {
			/nomodkey /notify InventoryWindow IW_DoneButton LeftMouseUp
			/delay 5
			/if (${Window[InventoryWindow].Open}) /goto :CloseInvWnd
		} else {
		/echo I couldn't find (${SoulStoneName}) on my cursor!
		/return
	}
	/if (${Window[InventoryWindow].Open}) /nomodkey /notify InventoryWindow IW_DoneButton LeftMouseUp
	/delay 5
	/squelch /target clear
	/delay 10

/return

#bind TarGroup2XTar /targroup2xtar
Sub Bind_TarGroup2XTar
    /if (!${AssistOutside[SETTINGVAL]}) /return FALSE
    /if (!${DanNet.Peers.Find[${assistname}]}) /return FALSE

    /declare tgt_groupcount int local
    /call DNetQueryCheck ${assistname} "Group"
    /varset tgt_groupcount ${Macro.Return}

    /declare tmp_spawnid string local
    /declare i int local
    /for i 1 to ${tgt_groupcount}
        /call DNetQueryCheck ${assistname} "Group.Member[${i}].ID"
        /varset tmp_spawnid ${Macro.Return}

        /call SetTarget ${tmp_spawnid}
        /xtarget add
        /delay 2
    /next i
    /call SetTarget ${assistid}
    /xtarget add
    /delay 2
/return

#bind CheckForAlliance /checkalliance
Sub Bind_CheckForAlliance
	/if (${RGAllianceCheck[${Me.Class.ShortName},${AllianceCount[SETTINGVAL]}]}) {
		/echo \aw Alliance possible if ${Me.Class.ShortName} Supports \ax - Enable with \ag /rg DoAlliance 1 \ax.
		/varset CanAlliance TRUE
	} else {
        /echo \ar Alliance Not Possible \ax - Do not have \ag${AllianceCount[SETTINGVAL]}\ax ${Me.Class.ShortName}. 
        /echo Either lower \awAllianceCount\ax (and run \aw/checkalliance\ax) or get more \ag${Me.Class.ShortName}\ax
    }
/return

#bind PullSet /configpull
Sub Bind_PullSet
    /call ${Me.Class.ShortName}_PullSetup
/return

#bind UnsuspendMerc /summonmerc
Sub Bind_UnsuspendMerc
    /notify MMGW_ManageWnd MMGW_SuspendButton leftmouseup
/return

#bind MercAssist /mercassist
Sub Bind_MercAssist
    /notify MMGW_ManageWnd MMGW_CallForAssistButton leftmouseup
/return

|----------------------------------------------------------------------------
|- SUB: Bind_ReloadMode -- Called when the mode is changed in game. Currently using to work around
|- classes that may not support mode changes without restarts
|- Temporarily configured as a bind due to bugs in MQ2 Live.
|----------------------------------------------------------------------------
#bind ReloadMode /classmode
Sub Bind_ReloadMode(string mode_number)
    |**
    /if (${Select[${Me.Class.ShortName},ENC,BRD,PAL]}) {
        /echo WARNING: ${Me.Class.ShortName} does not support mode changes without restarting.
        /echo Please restart RGMERCs to enact the mode change.
    } else {
        /call ModeSetup
    }**|

    /if (${mode_number.Length} > 0) {
        /call RGChangeSetting Settings ClassMode ${mode_number}
    }
    |- Currently only PAL supports mode w/o restarting.
    /if (${Select[${Me.Class.ShortName},PAL]}) {
        /call ModeSetup
    } else {
        /echo \awNOTICE:\ax\ag Please run /rgstart to finish classmode change.\ax
    }
/return

|**

Sub  <=======> BLOCK Settings Bind <=======>

**|

|-----------------------------------------------------------------------------
|- Sub: Bind_RGSettings - Bind that handles settings changes across the
|- Macro suite
|-----------------------------------------------------------------------------
#bind   RGSettings   /RG
#bind   RGSettings   /rg
Sub Bind_RGSettings(string setting_noun, string setting_value, string value)

    |- User provided no setting/noun so display command usage
    /if (${setting_noun.Length} == 0) {
            /call RG_UsageError
            /return
    }
    
    /if (${setting_noun.Equal[help]}) {
        |- Print Help
        /echo ==-- \arR\ax\awG\ax\arMercs\ax Settings --==
        /call RGPrintHelp Settings
        /echo -- \amPull\ax Settings --
        /call RGPrintHelp Pull
        /echo -- \aw${Me.Class.ShortName}\ax Settings --
        /call RGPrintHelp ${Me.Class.ShortName}
        /return
    }
    /if (${setting_noun.Equal[advanced]}) {
        /echo ==-- \arR\ax\awG\ax\arMercs\ax Advanced Settings --==
        /call RGPrintAdvanced Settings
        /echo -- \amPull\ax Advanced Settings --
        /call RGPrintAdvanced Pull
        /echo -- \aw${Me.Class.ShortName}\ax Advanced Settings --
        /call RGPrintAdvanced ${Me.Class.ShortName}
        /return
    }
    /if (${setting_noun.Equal[debug]}) {
        /if (${setting_value.Equal[clear]}) {
            /mqlog clear
        } else {
            |- We're setting debug getter/setters
            |- use setting_value/value
            /echo Use /rg DebugLog 1 to enable debug printing to a log file. DebugLog 2 outputs call trace to the console.
        }
        /return
    }
    /if (${setting_noun.Equal[camphere]}) {
        /call TurnChaseOff
        |- Provides temporary return to camp change. This will be reset to the default ini
        |- value when the macro is restarted. Also updates the camp location.
        /varset ZoneID ${Zone.ID}
        /varset AutoCampX ${Me.X}
        /varset AutoCampY ${Me.Y}
        /varset AutoCampZ ${Me.Z}
        /echo Camping On: (X: ${AutoCampX} ; Y: ${AutoCampY})
        /varset ReturnToCamp[SETTINGVAL] 1
        /return
    }
    /if (${setting_noun.Equal[camphard]}) {
        /call TurnChaseOff
        |- Provides temporary return to camp change. This will be reset to the default ini
        |- value when the macro is restarted. Also updates the camp location.
        /varset ZoneID ${Zone.ID}
        /varset AutoCampX ${Me.X}
        /varset AutoCampY ${Me.Y}
        /varset AutoCampZ ${Me.Z}
        /echo Hard Camp On: (X: ${AutoCampX} ; Y: ${AutoCampY})
        /varset ReturnToCamp[SETTINGVAL] 2
        /return
    }
    /if (${setting_noun.Equal[campoff]}) {
        |- Provides temporary return to camp change. This will be reset to the default ini
        |- value when the macro is restarted.
        /echo Turning Camp Off
        /varset ReturnToCamp[SETTINGVAL] 0
        /return
    }
    /if (${setting_noun.Equal[chaseon]}) {
        /call TurnCampOff
        |- Starts chasing and stop returning to camp.
        /if (${setting_value.Length} == 0) {
            /echo \ao Now Chasing \ag ${assistname}
            /varset FollowToonName[SETTINGVAL] ${assistname}
        } else {
            /echo \ao Now Chasing \ag ${setting_value}
            /varset FollowToonName[SETTINGVAL] ${setting_value}
        }
        /return
    }
    /if (${setting_noun.Equal[chaseoff]}) {
        /echo \ao No longer chasing \ag ${FollowToonName[SETTINGVAL]}
        /varset FollowToonName[SETTINGVAL] NULL
        /return
    }
    /if (${setting_noun.Equal[on]}) {
        /echo \ao RGMercs is\ax \agON\ax
        /if (!${MainLoopOn}) /varset autotargetid 0
        /varset MainLoopOn 1
        /return
    }
    /if (${setting_noun.Equal[off]}) {
        /echo \ao RGMercs is\ax \arOFF\ax
        /varset MainLoopOn 0
        /if (${Me.Casting.ID} || ${Window[CastingWindow].Open}) {
            /stopcast
            /stopsong
            /delay 5s !${Window[CastingWindow].Open}
        }
        /return
    }
    /if (${setting_noun.Equal[${Me.Class.ShortName}]}) {
        |- We're in class specific settings
        |- use setting_value/value
        |- No Setting Name provided -- remind them of the command usage
        /if (${setting_value.Length} == 0) {
            /call RG_UsageError
            /return
        }
        
    /if (${setting_noun.Equal[burnauto]}) {
		/if (!${setting_value} = 1 || !${setting_value} = 0) {
		    /echo Blast! You've broken it!  Try setting to 1 (ON) or 0 (Off) you goat!
		} else {
            /call RGChangeSetting Settings BurnAuto ${setting_value}
		    /if (${setting_value} = 1) /echo Automatic Burn is ON! RG Mercs will take care of burns
		    /if (${setting_value} = 0) /echo Automatic Burn is OFF! Manual burns engaged.
		}
	/return
	}

    /if (${setting_noun.Equal[smallburn]}) {
        /varset BurnSize[SETTINGVAL] 1
	    /echo Small Burn - Throwing the toaster
	    /return
	}

    /if (${setting_noun.Equal[mediumburn]}) {
        /varset BurnSize[SETTINGVAL] 2
	    /echo Medium Burn - Throwing the toaster
	    /return
	}

    /if (${setting_noun.Equal[bigburn]}) {
        /varset BurnSize[SETTINGVAL] 3
    	/echo Small Burn - Throwing the toaster
	    /return
	}

        /if (${value.Length} == 0) {
            /call RGPrintSetting ${Me.Class.ShortName} ${setting_value}
        } else {
            /call RGChangeSetting ${Me.Class.ShortName} ${setting_value} "${value}"
        }
        /return
    }



    
    |- We're configuring/printing a normal setting
    |- Using setting_noun, setting_value
    /if (${setting_value.Length} == 0) {
        /if (!${RGPrintSetting[Settings,${setting_noun}]}) {
            /if (!${RGPrintSetting[Pull,${setting_noun}]}) {
                /echo Checking if you forgot to add \ag${Me.Class.ShortName}...
                /call RGPrintSetting ${Me.Class.ShortName} ${setting_noun}
            }
        }
    } else {
        /if (!${RGChangeSetting[Settings,${setting_noun},${setting_value}]}) {
            /if (!${RGChangeSetting[Pull,${setting_noun},${setting_value}]}) {
                /echo Checking if you forgot to add \ag${Me.Class.ShortName}...
                /call RGChangeSetting ${Me.Class.ShortName} ${setting_noun} "${setting_value}"
            }
        }
    }
    /return

Sub RG_UsageError 
        /echo \arR\awG\arMercs \ayCommand Usage:
        /echo \amVERSION:\ax \aw${RGVersion}\ax
        /echo \ag/rg help \ax- Print help for each setting
        /echo \ag/rg advanced \ax- Print help for each \awadvanced\ax setting
        /echo \ag/rg camphere \ax- Set your camp to this location and return after leaving AutoCampRadius.
        /echo \ag/rg camphard \ax- Set your camp to this location and return every time.
        /echo \ag/rg campoff \ax- Turn off ReturnToCamp
        /echo \ag/rg chaseon \ax- Start chasing your main assist (uses afollow)
        /echo \ag/rg chaseon <target> \ax- Start chasing target (uses afollow)
        /echo \ag/rg chaseoff \ax- Stops chasing
        /echo \ag/rg on \ax- Turn mainloop and RGMercs behavior on.
        /echo \ag/rg off \ax- Turn mainloop and RGMercs behavior off. Macro stays running.
        /echo \ag/rg <setting> <value> \ax- Change a general RGMercs setting
        /echo \ag/rg <setting> \ax- Print a general RGMercs setting
        /echo \ag/rg Pull <setting> <value> \ax- Change a \amPull\ax category specific setting
        /echo \ag/rg Pull <setting> \ax- Print a \amPull\ax category specific setting
        /echo \ag/rg ${Me.Class.ShortName} <setting> <value>  \ax- Change \aw${Me.Class.ShortName}\ax specific setting
        /echo \ag/rg ${Me.Class.ShortName} <setting>  \ax- Print a \aw${Me.Class.ShortName}\ax specific setting
/return


|**

Sub  <=======> BLOCK Scribe Bind <=======>

**|

#bind ScribeSpells /scribe
Sub Bind_ScribeSpells(int minlvl, int maxlvl)
	/declare HasVoA int local 0
	/declare InvScribeSlot int local 1

	/declare MyDeity string local ${Me.Deity}
	/declare MaxInvSlots int local 10
	/declare MinLevel int local 1
	/declare MaxLevel int local ${Me.Level}
	/declare DoLoop int local 0
	/declare mName string local
    /declare a int local
    /declare b int local
    /declare c int local
    /declare SpellName string local
    /declare Bag int local
    /declare Slot int local
	/if (${minlvl}) /varset MinLevel ${minlvl}
	/if (${maxlvl}) /varset MaxLevel ${maxlvl}
	/if (${Me.HaveExpansion[Veil of Alaris]}) /varset HasVoA 1

:Start
	/varset DoLoop 0
	/if (${Merchant.Open}) {
		/varset mName ${Merchant.Name}
		/echo Buying all ${Me.Class} spells/tomes for levels ${MinLevel} to ${MaxLevel}
		/if (!${Select[${Me.Class.ShortName},CLR,DRU,SHM,ENC,WIZ,MAG,NEC]}) {
            /if (!${Merchant.Open}) /return
            /delay 2s
            /if (!${Merchant.Items}) /return

            /for a 1 to ${Merchant.Items}
                /if (!${Me.FreeInventory}) /return
                /varset c 0
                /varset SpellName ${Merchant.Item[${a}].Spell.Name}
                /if (${SpellName.Find[ Rk. II ]}) /varset SpellName ${Merchant.Item[${a}].Spell.Name.Replace[ Rk. II ,]}
                /if (${SpellName.Find[ Rk. III ]}) /varset SpellName ${Merchant.Item[${a}].Spell.Name.Replace[ Rk. III ,]}
            |/echo Item ${a} is ${Merchant.Item[${a}].Spell.Name}

                /if (${Merchant.Item[${a}].Type.Equal[Scroll]} && ${Merchant.Item[${a}].Spell.Level} >= ${MinLevel} && ${Merchant.Item[${a}].Spell.Level} <= ${MaxLevel} && ${Math.Calc[${Merchant.Item[${a}].BuyPrice}\1000]} < ${Me.Platinum}) {

                    /if (${Me.CombatAbility[${SpellName}]}) {
                        /echo :: I already know ${SpellName}
                    /continue
                    }

                    /if (${FindItemCount[${Merchant.Item[${a}]}]}) {
                        /echo :: I already have ${Merchant.Item[${a}]} in inventory
                    /continue
                    }

                    /if (${Me.CombatAbility[${SpellName} Rk. II]} || ${FindItemCount[${Merchant.Item[${a}]} Rk. II]}) {
                        /echo :: Skipping lower rank of ${SpellName}
                    /continue
                    }

                    /if (${Me.CombatAbility[${SpellName} Rk. III]} || ${FindItemCount[${Merchant.Item[${a}]} Rk. III]}) {
                        /echo :: I already have the highest rank of ${SpellName}
                    /continue
                    }

                | this loop is needed because the merchant item number doesn't match up to the interface line number
                    /for b 1 to ${Window[MerchantWnd].Child[MW_ItemList].Items}
                        /if (${Window[MerchantWnd].Child[MW_ItemList].List[${b},2].Equal[${Merchant.Item[${a}]}]}) /varset c ${b}
                    /next b

                | merchant line number matches what we are looking to buy, buy 1 copy of it
                    /if (${c}) {
                        /echo Buying ${Window[MerchantWnd].Child[MW_ItemList].List[${c},2]}
                        /notify MerchantWnd MW_ItemList listselect ${c}
                        /nomodkey /ctrlkey /notify MerchantWnd MW_Buy_Button leftmouseup
                        /delay 1s
                        TRIGGERBIND
                    }
                }
            /next a
        }
		/if (!${Select[${Me.Class.ShortName},WAR,BER,MNK,ROG]}) {
            /if (!${Merchant.Open}) /return
            /delay 2s
            /if (!${Merchant.Items}) /return

            /for a 1 to ${Merchant.Items}
                /if (!${Me.FreeInventory}) /return
                /if (!${Merchant.Open}) /return
                /varset c 0
                /varset SpellName ${Merchant.Item[${a}].Spell.Name}
                /if (${SpellName.Find[ Rk. II ]}) /varset SpellName ${Merchant.Item[${a}].Spell.Name.Replace[ Rk. II ,]}
                /if (${SpellName.Find[ Rk. III ]}) /varset SpellName ${Merchant.Item[${a}].Spell.Name.Replace[ Rk. III ,]}

                /if (${Merchant.Item[${a}].Type.Equal[Scroll]} && ${Merchant.Item[${a}].Spell.Level} >= ${MinLevel} && ${Merchant.Item[${a}].Spell.Level} <= ${MaxLevel} && ${Math.Calc[${Merchant.Item[${a}].BuyPrice}\1000]} < ${Me.Platinum} && !${Me.Book[${Merchant.Item[${a}].Spell.Name}]} && !${FindItemCount[${Merchant.Item[${a}]}]}) {
                    /if (${Me.CombatAbility[${SpellName}]}) {
                        /echo :: I already know ${SpellName}
                    /continue
                    }

                    /if (${FindItemCount[${Merchant.Item[${a}]}]}) {
                        /echo :: I already have ${Merchant.Item[${a}]} in inventory
                    /continue
                    }

                    /if (${Me.CombatAbility[${SpellName} Rk. II]} || ${FindItemCount[${Merchant.Item[${a}]} Rk. II]}) {
                        /echo :: Skipping lower rank of ${SpellName}
                    /continue
                    }

                    /if (${Me.CombatAbility[${SpellName} Rk. III]} || ${FindItemCount[${Merchant.Item[${a}]} Rk. III]}) {
                        /echo :: Skipping lower rank of ${SpellName}
                    /continue
                    }

                    /if (${Merchant.Item[${a}].Deities} && ${MyDeity.NotEqual[${Merchant.Item[${a}].Deity[1]}]}) {
                        /echo Unable to use ${SpellName} because of deity
                    /continue
                    }
                    /if (${Me.Book[${SpellName} Rk. II]} || ${FindItemCount[${SpellName} Rk. II]}) {
                        /echo Skipping lower rank of ${SpellName}
                    /continue
                    }
                    /if (${Me.Book[${SpellName} Rk. III]} || ${FindItemCount[${SpellName} Rk. III]}) {
                        /echo Skipping lower rank of ${SpellName}
                    /continue
                    }

                | this loop is needed because the merchant item number doesn't match up to the interface line number
                    /for b 1 to ${Window[MerchantWnd].Child[MW_ItemList].Items}
                        /if (${Window[MerchantWnd].Child[MW_ItemList].List[${b},2].Equal[${Merchant.Item[${a}]}]}) /varset c ${b}
                    /next b

                | merchant line number matches what we are looking to buy, buy 1 copy of it
                    /if (${c}) {
                        /echo Buying ${Window[MerchantWnd].Child[MW_ItemList].List[${c},2]}
                        /notify MerchantWnd MW_ItemList listselect ${c}
                        /nomodkey /ctrlkey /notify MerchantWnd MW_Buy_Button leftmouseup
                        /delay 1s
                        TRIGGERBIND
                    }
                }
            /next a
        }
        /delay 2s
	}
	/if (${Merchant.Open}) {
		/notify MerchantWnd MW_Done_Button leftmouseup
		/delay 1s !${Merchant.Open}
	}
	/if (!${Select[${Me.Class.ShortName},CLR,DRU,SHM,ENC,WIZ,MAG,NEC]}) {
        /if (${Cursor.ID}) /autoinv
        /if (!${HasVoA} && ${InvSlot[pack${InvScribeSlot}].Item.Type.Equal[Scroll]} && ${InvSlot[pack${InvScribeSlot}].Item.Spell.Level} <= ${Me.Level} && !${Me.Book[${InvSlot[pack${InvScribeSlot}].Item.Spell.Name}]}) /nomodkey /ctrlkey /itemnotify ${InvSlot[pack${InvScribeSlot}]} rightmouseup
        /for Bag 1 to ${MaxInvSlots}
            /if (${InvSlot[pack${Bag}].Item.Container}) {
                /if (!${Window[Pack${Bag}].Open}) /itemnotify pack${Bag} rightmouseup
                /delay 1s ${Window[Pack${Bag}].Open}
                /for Slot 1 to ${InvSlot[pack${Bag}].Item.Container}
                    /if (${InvSlot[pack${Bag}].Item.Item[${Slot}].Name.Find[Tome]} && ${InvSlot[pack${Bag}].Item.Item[${Slot}].Type.Equal[Scroll]} && ${InvSlot[pack${Bag}].Item.Item[${Slot}].Spell.Level} <= ${Me.Level} && !${Me.Book[${InvSlot[pack${Bag}].Item.Item[${Slot}].Spell.Name}]}) {
                        /if (${HasVoA}) {
                            /nomodkey /ctrlkey /itemnotify in pack${Bag} ${Slot} rightmouseup
                            /delay 1s !${InvSlot[pack${Bag}].Item.Item[${Slot}].ID}
                        } else {
                            /nomodkey /ctrlkey /itemnotify in pack${Bag} ${Slot} leftmouseup
                            /delay 1s ${Cursor.ID}
                            /nomodkey /ctrlkey /itemnotify ${InvSlot[pack${InvScribeSlot}]} leftmouseup
                            /delay 1s !${Cursor.ID}
                            /nomodkey /ctrlkey /itemnotify ${InvSlot[pack${InvScribeSlot}]} rightmouseup
                            /delay 1s !${InvSlot[pack${InvScribeSlot}].ID}
                        }
                    }
                /next Slot

            }
            /if (${Window[Pack${Bag}].Open}) /itemnotify pack${Bag} rightmouseup
        /next Bag
        /if (${Cursor.ID}) /autoinv   
    }
	/if (!${Select[${Me.Class.ShortName},WAR,BER,MNK,ROG]}) {
        /if (${Cursor.ID}) /autoinv
        |** Opening your inventory for access bag slots **|
        /if (!${Window[InventoryWindow].Open}) {
            /windowstate InventoryWindow open
        }
        |** Open all bags **|
        /keypress OPEN_INV_BAGS
        |** Check Top Level Inventory Slot for bag/no bag **|
        /for Bag 1 to ${MaxInvSlots}
            |** If it's a bag do this **|
            /if (${InvSlot[pack${Bag}].Item.Container}) {
                /if (!${Window[Pack${Bag}].Open}) /itemnotify pack${Bag} rightmouseup
                /delay 1s ${Window[Pack${Bag}].Open}
                /delay 5

                /for Slot 1 to ${InvSlot[pack${Bag}].Item.Container}
                    /if (${InvSlot[pack${Bag}].Item.Item[${Slot}].Type.Equal[Scroll]} && ${InvSlot[pack${Bag}].Item.Item[${Slot}].Spell.Level} <= ${Me.Level} && !${Me.Book[${InvSlot[pack${Bag}].Item.Item[${Slot}].Spell.Name}]}) {
                        /nomodkey /ctrlkey /itemnotify in pack${Bag} ${Slot} rightmouseup
                        /delay 1s ${Cursor.ID}
                        /if (${Cursor.ID}) /call doScribe
                    }
                /next Slot
                |** Close the bag I just checked **|
                /if (${Window[Pack${Bag}].Open}) /itemnotify pack${Bag} rightmouseup
            } else {
                |** If it's not a bag, do this **|
                | Debug message /echo TopLevel Inv Slot ~ IsAScroll: ${InvSlot[pack${Bag}].Item.Type.Equal[Scroll]} && Item Spell level: ${InvSlot[pack${Bag}].Item.Spell.Level} <= My Level: ${Me.Level} && Scribed Already: !${Me.Book[${InvSlot[pack${Bag}].Item.Spell.Name}]}
                /if (${InvSlot[pack${Bag}].Item.Type.Equal[Scroll]} && ${InvSlot[pack${Bag}].Item.Spell.Level} <= ${Me.Level} && !${Me.Book[${InvSlot[pack${Bag}].Item.Spell.Name}]}) {
                    /echo Scribing: ${InvSlot[Pack${Bag}].Item.Name}
                    /nomodkey /ctrlkey /itemnotify pack${Bag} rightmouseup
                    /delay 1s ${Cursor.ID}
                    /if (${Cursor.ID}) /call doScribe
                }
            }
        /next Bag
        /if (${Window[SpellBookWnd].Open}) /squelch /windowstate SpellBookWnd close        
    }
	/if (${DoLoop}) {
		/target ${mName}
		/delay 2s ${Target.ID}
		/click right target
		/delay 1s
		/goto :Start
	}
/return TRUE

| --------------------------------------------------------------------------------------------
| SUB: doScribe
| --------------------------------------------------------------------------------------------
Sub doScribe
	/declare tOut timer local 10s
:WaitFinished
	/if (${Window[ConfirmationDialogBox].Open} && ${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[${Cursor.Spell.Name} will replace]}) /notify ConfirmationDialogBox Yes_Button leftmouseup
	/if (!${tOut}) /autoinv
	/delay 2
	TRIGGERBIND
	/if (${Cursor.ID}) /goto :WaitFinished
/return

| --------------------------------------------------------------------------------------------
| SUB: Event_NotGold
| --------------------------------------------------------------------------------------------
#event NotGold "#*#you do not have at least a gold membership#*#"
Sub Event_NotGold
	/autoinv
/return


| --------------------------------------------------------------------------------------------
| SUB: Event_WrongDiety
| --------------------------------------------------------------------------------------------
#event WrongDiety "#*#You do not worship#*#"
Sub Event_WrongDiety
	/autoinv
/return

| --------------------------------------------------------------------------------------------
| SUB: Event_FullInventory
| --------------------------------------------------------------------------------------------
#event FullInventory "#*#Your inventory appears full!#*#"
Sub Event_FullInventory
	/if (${Merchant.Open}) {
		/notify MerchantWnd MW_Done_Button leftmouseup
		/delay 1s !${Merchant.Open}
	}
	/varset DoLoop 1

/return


|**

Sub  <=======> BLOCK SummonSnacks Bind <=======>

**|
#bind SummonSnacks /summonsnacks
Sub Bind_SummonSnacks(int itemcount)
    |- If we can summon food, screw it. 
    /if (!${Select[${Me.Class.ShortName},CLR,DRU,SHM,MAG,BST]}) {
        /echo You can't summon food, sorry.
        /return
    }
    /if (${itemcount} == 0 ) {
        /echo You need to set an item count.
        /return
    }
    /echo Summoning Snacks for my group!
    |- switch to the spell you want to cast
    /declare summonorder string local food drink
    /declare foodSpell string local
    /if (${Me.Book[Cornucopia]}) {
        /varset foodSpell Cornucopia
    } else {
        /varset foodSpell Summon Food
    }
    /declare drinkSpell string local
    /if (${Me.Book[Everfount]}) {
        /varset drinkSpell Everfount
    } else {
        /varset drinkSpell Summon Drink
    }
    /declare foodItem string local Summoned: Black Bread
    /declare drinkItem string local Summoned: Globe of Water

    /declare TellCMD string local ${Parse[0,/dt ${Group.Member[${i}].Name} /nomodkey /notify TradeWnd TRDW_Trade_Button leftmouseup]}

    /if (${Me.FreeInventory} < 2) {
        /echo Must have two free inventory spaces to run.
        /return
    }

    /echo \atStarting Summoning
    /declare i int local
    /declare j int local
    /declare tmpstep string local
    /for j 1 to 2
        /varset tmpstep ${summonorder.Arg[${j}]}
        /for i 1 to ${Group.Members}
            /delay 1s ${PCSpellReady[${tmpstep}Spell]}
            /echo Summoning ${tmpstep} for ${Group.Member[${i}]}
            /call SummonItem "${${tmpstep}Spell}" "${${tmpstep}Item}" ${itemcount}

            /while (${Cursor.ID} && ${Me.FreeInventory}) {
                /autoinv
                /delay 1
            }
            
            | Pickup the bread, wait until the bread is picked up, click on the target to trade, wait until the bread is dropped in the trade window,
            | and finally click yes on the trade. Do the same for the 
            /call SetTarget ${Group.Member[${i}].ID}
            | Navigate to my group member and delay further action until the Navigation stops
            /if (${Target.Distance} > 15) {
                /echo Too far away from ${Target.Name}, moving closer
                /nav id ${Group.Member[${i}].ID} log=off distance=5
                /delay 10s ${Navigation.Active}
            }
            /echo Handing ${Target.Name} ${tmpstep}
            /while (!(${Cursor.ID}==${FindItem[${${tmpstep}Item}].ID})) {
                /itemnotify "${${tmpstep}Item}" leftmouseup 
                /delay 10
            }
            /while (!${Window[TradeWnd]}) {
                /click left target
                /delay 2
            }
            /delay 5s !${Cursor.ID}
            /notify TradeWnd TRDW_Trade_Button leftmouseup
            |Delay until trade says yes
            /docommand ${TellCMD}
            /delay 5s !${Window[TradeWnd]}
        /next i

        /echo Summoning ${tmpstep} for ${Me.CleanName}
        /call SummonItem "${${tmpstep}Spell}" "${${tmpstep}Item}" ${itemcount}
    |END for
    /next j
/return
#bind GO2GGH /go2ggh
sub Bind_GO2GGH
	/echo \ag--> \atMoving to Neighbourhood Guild Hall \ag<--
	/if (!${Select[${Zone.ShortName},PoKnowledge,potranquility,Stratos,guildlobby,moors,crescent,guildhalllrg_int]}) /call useorigin
	/if (${Zone.ShortName.Equal[crescent]}) /call crescent
	/if (${Zone.ShortName.Equal[moors]}) /call moors
	/if (${Zone.ShortName.Equal[Stratos]}) /call Stratos
    /if (${Zone.ShortName.Equal[potranquility]}) /call potranquility
    /if (${Zone.ShortName.Equal[PoKnowledge]}) /call PoKnowledge
    /if (${Zone.ShortName.Equal[guildlobby]}) /call guildlobby
	/if (${Zone.ShortName.Equal[guildhalllrg_int]}) /call guildhalllrg
	/delay 2
	/echo \ag --> \atYou made it \ag<--
	
/return

Sub useorigin
	/if (${FindItem[=Drunkard's Stein].ID} && ${Me.ItemReady[=Drunkard's Stein]}) {
		/echo \ag--\atFound a Drunkard's Stein, using that to get to PoK\ag--
		/useitem "Drunkard's Stein"
		/delay 1s
		/delay 180s ${Zone.ShortName.Equal[PoKnowledge]}==TRUE
    } else { 
        /if (${RG_AAReady[Throne of Heroes]}) {
    	/echo \ag--\atUsing Throne of Heroes to get to Guild Lobby\ag--
		/echo \ag--\atAs you not within a zone we know\ag--
		/alt act 511
		/delay 5
		/while (${Me.Casting.ID}) {
			/delay 2s
		}
		/delay 180s ${Zone.ShortName.Equal[guildlobby]}==TRUE
		/delay 2s 
	} else {  	
		/echo \ag--\atUsing Origin to get to Cresent Reach\ag--
		/echo \ag--\atAs you not within a zone we know\ag--
		/alt act 331
		/delay 5
		/while (${Me.Casting.ID}) {
			/delay 1s
		}
	 
     	/delay 180s ${Zone.ShortName.Equal[crescent]}==TRUE
		/delay 2s 
	}
    }
/return

Sub guildhalllrg
	/echo \ag--\atGoing to Pool \ag--
	/moveto loc 1 1 3
	/while (${Me.Moving}) {
		/delay 1s
	}
/return

Sub guildlobby
	/echo \ag--\atMoving to Guildhall \ag--
	/squelch /nav door id 1 click
	/while (${Navigation.Active}) {
		/delay 1s
	}
	/delay 180s ${Zone.ShortName.Equal[guildhalllrg_int]}==TRUE
	/delay 1s
/return

Sub Stratos
	/echo \ag--\atZoning into PoTranq \ag--
	/squelch /travelto potranquility
	/while (${Navigation.Active}) {
		/delay 1s
	}
	/delay 180s ${Zone.ShortName.Equal[PoTranquility]}==TRUE
	/delay 1s
/return
Sub Potranquility
	/echo \ag--\atZoning into PoTranq \ag--
	/squelch /travelto PoKnowledge
	/while (${Navigation.Active}) {
		/delay 1s
	}
	/delay 180s ${Zone.ShortName.Equal[Poknowledge]}==TRUE
	/delay 1s
/return 

Sub PoKnowledge
	/echo \ag--\atMoving to Guild Lobby \ag--
	/squelch /nav door id 17 click
	/while (${Navigation.Active}) {
		/delay 1s
	}
	/delay 180s ${Zone.ShortName.Equal[guildlobby]}==TRUE
	/delay 1s
/return

Sub moors
	/echo \ag--\atZoning into PoK \ag--
	/squelch /nav door id 68 click
	/while (${Navigation.Active}) {
		/delay 1s
	}
	/delay 180s ${Zone.ShortName.Equal[PoKnowledge]}==TRUE
	/delay 1s
/return
 
Sub crescent
	/echo \ag--\atZoning to Moors \ag--
	/squelch /nav loc -631 -2868 -29
	/while (${Navigation.Active}) {
		/delay 1s
	}
	/delay 180s ${Zone.ShortName.Equal[Moors]}==TRUE
	/delay 1s
/return


Sub SummonItem(string spellname, string summonitem, int howmany)
    /declare MyManaRequired int local  0 
    /while (${FindItemCount[${summonitem}]} < ${howmany}) {
        /delay 20s ${PCSpellReady[${spellname}]}
        /call SpellNow "${spellname}" ${Me.ID}
        /delay 10s !${Me.Casting.ID}
        /delay 2
        TRIGGERBIND

        | If OutofMana - calculate how much mana needed, and med till you have it
        /if (${CastResult.Equal[CAST_OUTOFMANA]}) {
            /echo Idle -- Out Of Mana -- Sitting!
            /while (!${Me.Sitting}) {
                /sit
                /delay 1
            }
            |how much mana do I need - spell mana times how many casts I need to made            
            /varcalc MyManaRequired ${Spell[${spellname}].Mana}*(${howmany}-${FindItemCount[${item}]})
            /echo Need ${MyManaRequired} mana - have ${Me.CurrentMana} now
            /while (${Me.CurrentMana} < ${MyManaRequired}) {
                /echo Waiting 1 tic
                /delay 6s
            }   
        }
        /if (${CastResult.Equal[CAST_FIZZLE]}) {
            /echo Woops, I fizzled!
        }
        /if (!${PCSpellReady[${spellname}]}) /delay 2
        /while (${Cursor.ID} && ${Me.FreeInventory}) {
            /autoinv
            /delay 1
        }
        /echo Summoned ${FindItemCount[${summonitem}]} out of ${howmany} ${summonitem}
        /delay 5s ${PCSpellReady[${spellname}]}
    }
/return
#bind showbonuses /showbonuses
Sub Bind_showbonuses
    /echo 
    /echo Stats Bonuses:
    /echo --------------
    
    /echo HP: +${Me.HPBonus}
    
    /echo Mana: +${Me.ManaBonus}
    
    /echo Endurance: +${Me.EnduranceBonus}
    
    /echo HP Regen: +${Me.HPRegenBonus} / 45
    
    /declare MaxManaRegen int local
    /varcalc MaxManaRegen (15 + ${Me.AltAbility[Expansive Mind].Rank})
    /echo Mana Regen: +${Me.ManaRegenBonus} / ${MaxManaRegen}
    
    
    /echo 
    
    
    /echo Offensive Bonuses:
    /echo ------------------
    
    /echo Haste: ${Math.Calc[${Me.AttackSpeed}-100].Int}%
    
    /declare MaxAttackBonus int local
    /varcalc MaxAttackBonus (250 + (10 * ${Me.AltAbility[Enhanced Aggression].Rank}))
    /echo Attack: +${Me.AttackBonus} / ${MaxAttackBonus}
    
    /echo Accuracy: +${Me.AccuracyBonus} / 150
    
    /echo Damage Shield: +${Me.DamageShieldBonus} / 30
    
    /echo Strikethrough: +${Me.StrikeThroughBonus}% / 35%
    
    /echo Combat Effects: +${Me.CombatEffectsBonus} / 100?
    
    
    /echo 
    
    
    /echo Defensive Bonuses:
    /echo ------------------
    
    /echo Avoidance: +${Me.AvoidanceBonus} / 100
    
    /echo Shielding: +${Me.ShieldingBonus}% / 35%
    
    /echo Spellshield: +${Me.SpellShieldBonus}% / 35%
    
    /echo Stun Resist: +${Me.StunResistBonus}% / 35%
    
    /echo DoT Shielding: +${Me.DoTShieldBonus}% / 35%
    
/return

