Sub CheckTask(string taskname,string npcfilter,string keyword)
	|  - Ok First things first, do we actually have the task?
	:Gettask
	/if (${Task[${taskname}].ID} > 0) {
		/echo we have the ${taskname} task
	} else {
		/call GoToNPC "${taskname}" "${npcfilter}" -1
		/makemevisible
		/delay 1s
		/say ${keyword}
		/delay 10s ${Window[TaskSelectWnd].Open}
		/if (${Window[TaskSelectWnd].Open}) {
			/notify TaskSelectWnd TSEL_TaskList listselect ${Window[TaskSelectWnd].Child[TSEL_TaskList].List[${taskname}]}
			/notify TaskSelectWnd TSEL_AcceptButton leftmouseup
			/delay 5s ${Task[${taskname}].ID} > 0
		}
		/if (${Task[${taskname}].ID} == 0) {
			/delay 5s
			/goto :Gettask
		}
	}
/return
Sub GoToNPC(string ttask,string filter,int stindex,bool dontcheckinvis)
		/nav id ${Spawn[${filter}].ID} dist=20 los=on
		/delay 2s ${Navigation.Active}==TRUE
		/delay 120s ${Navigation.Active}==FALSE
		/target id ${Spawn[${filter}].ID}
		/delay 1s ${Target.ID}==${Spawn[${filter}].ID}
/return
Sub SpeakToNPC(string thetask,string msg,string speakname,int stepidx)
	/if (${Task[${thetask}].Step.Index}==${stepidx}) {
		/call GoToNPC "${thetask}" "${speakname}" ${stepidx}
		/makemevisible
		/delay 5s
		/if (${msg.Equal[Hail]}) {
			/keypress HAIL
		} else {
			/say ${msg}
		}
		/delay 2s ${Task[${thetask}].Step.Index}!=${stepidx}
		/delay 1s
	} else {
		/echo already did step ${stepidx} ${Task[${thetask}].Objective[${stepidx}]}
		/return
	}
/return
Sub Kicktask
		/echo Kicking All Members  
		/squelch /kickp task
		/delay 2s
		/squelch /yes
		/delay 2s
/return
Sub FindMob(string mobfiltera,string mobfilterb)
	/declare mobfilter 		string	local ${mobfiltera}
	/declare MobsInRadius 	int 	local 	${SpawnCount[${mobfilter}]}
	/if (${MobsInRadius} == 0 && ${mobfilterb.Length} > 0) {
		/varset mobfilter ${mobfilterb}
		/varset MobsInRadius ${SpawnCount[${mobfilter}]}
	}
	/echo Found ${MobsInRadius} mobs I can choose from.
	/declare MobCounter 	int 	local 	0
	/declare MobID 			int 	local 	0
	/declare PathLength		float	local	0
	/declare MobIDDistance	float	local	0
	/declare PathCount		int		local	1
	/declare PathShortest	int 	local 	0
	/declare MobIDValid		int		local	0

	| Lets cut down on the time here a bit, we don't need to check more than 10 mobs in our vicinity, everything above that is just unreasonable
	| and when people are in huge zones, it will take forever to parse through...
	/if (${MobsInRadius} > 25) {
		/varset MobsInRadius 25
	}
	/varset KillTargetID 0
	/if (${MobsInRadius} > 0) {
		/for MobCounter 1 to ${MobsInRadius}
			/varset MobID ${NearestSpawn[${MobCounter},${mobfilter}].ID}
			/if (${Select[${Spawn[ID ${MobID}].Type},AURA,BANNER,CAMPFIRE,CORPSE,CHEST,ITEM,TRIGGER,TRAP,TIMER,MOUNT,MERCENARY,OBJECT]}) /continue
			
			/varset PathLength ${Navigation.PathLength[id ${MobID}]}
			/if (${PathLength} > 0) {
				/if (${PathCount}==1) {
					/varset KillTargetID ${MobID}
					/varset PathShortest ${PathLength}
				} else /if (${PathLength} <= ${PathShortest}) {
					/varset KillTargetID ${MobID}
					/varset PathShortest ${PathLength}
				}
				/varcalc PathCount ${PathCount}+1 
			}
		/next MobCounter

		/if (${KillTargetID}) /call PrintGroupMessage "\agPulling \at${Spawn[${KillTargetID}].Name}(${KillTargetID}) \axat \ay${PathShortest} \axfeet"
	} else {
		
	}
/return
Sub CheckInvis
	/if (${invisspell.Equal[NULL]}) {
		/return
	}
	/declare needinvis int local 0
:NEEDINVIS
	/if (${Me.Invis}==TRUE) /return
	/varset needinvis 0
	|/if (${Me.Invis}==FALSE && ${Select[${Me.Class.ShortName},SHD,MAG,DRU]}) {
	/if (${Me.Invis}==FALSE) {
		/varset needinvis 1
	}
	/if (${needinvis}) {
		/if (${Me.Casting.ID}==0) {
			/if (${RG_AAReady[${invisspell}]}) {
				/alt act ${Me.AltAbility[${invisspell}].ID}
				|/echo whups im not AA invis, lets fix that
				/delay 5
			} else {
				/if (${FindItem[Cloudy Potion].ID}) {
					/useitem "Cloudy Potion"
					/echo whups im not invis lets fix that
					/delay 5
				}
				/if (${FindItem[Philter of Shadows].ID}) {
					/useitem "Philter of Shadows"
					/echo whups im not invis lets fix that
					/delay 5
				}
				/if (!${FindItem[Cloudy Potion].ID} && !${FindItem[Philter of Shadows].ID}) {
					/echo No Potions Continue without them
					/return
					/delay 5
				}
				
				}
				/delay 1
			}
		} else {
			/delay 1
		}
		/goto :NEEDINVIS
	
/return
Sub KillAndLoot(string thtask,string mobfilter,int LootID,int steidx)
	/declare i int local 1
	:kill_loop
	/if (${Task[${thtask}].Objective[${steidx}].CurrentCount} == ${Task[${thtask}].Objective[${steidx}].RequiredCount} ) {
		/echo already did step ${steidx} ${Task[${thtask}].Objective[${steidx}]}
		/return
	}
	/if (${AdvLoot.PCount}) {
		/for i 1 to ${AdvLoot.PCount}
			|/echo ${AdvLoot.PList[${i}].Name}
			/if (${AdvLoot.PList[${i}].ID}==${LootID}) {
				/beep
				/echo we got a ${AdvLoot.PList[${i}].Name}!
				/advloot personal ${i} loot
				/delay 3s !${AdvLoot.LootInProgress}
				/if (${Task[${thtask}].Objective[${steidx}].CurrentCount} == ${Task[${thtask}].Objective[${steidx}].RequiredCount} ) {
					/return
				}
			}
		/next i
	}
	/varset KillTargetID 0
	/call FindMob "${mobfilter}"
	/if (${KillTargetID}) {
		/call GoToNPC "${thtask}" "id ${KillTargetID}" ${steidx}
		/attack on
		/delay 5s ${Me.XTarget}
		/while (${Me.XTarget}) {
			/delay 1
			/if (!${Me.Combat} && ${Target.ID}) {
				/attack on
			}
			/if (${Target.ID} && ${Target.State.Equal[FEIGN]}) {
				/attack off
				/squelch /target clear
				/delay 1s !${Target.ID}
			}
			/if (${Target.ID} && ${Target.Type.Equal[Corpse]}) {
				/squelch /target clear
				/delay 1s !${Target.ID}
			}
			/if (!${Target.ID} && ${Me.XTarget}) {
				/tar id ${Me.XTarget[1].ID}
				/delay 2s ${Target.ID}==${Me.XTarget[1].ID}
			}
		}
		/if (${AdvLoot.PCount}) {
			/for i 1 to ${AdvLoot.PCount}
				/if (${AdvLoot.PList[${i}].ID}==${LootID}) {
					/beep
					/echo we got a ${AdvLoot.PList[${i}].Name}!
					/advloot personal ${i} loot
					/delay 3s !${AdvLoot.LootInProgress}
					/if (${Task[${thtask}].Objective[${steidx}].CurrentCount} == ${Task[${thtask}].Objective[${steidx}].RequiredCount} ) {
						/return
					}
				}
			/next i
		}
	}
	/goto :kill_loop
/return
Sub KillNPC(string tname,string kmobfilter,int kstep)
	:step_loop
	/makemevisible
	/delay 5s
	/if (${Task[${tname}].Step.Index}==${kstep}) {
		/varset KillTargetID 0
		/echo [${Time}] time to grab a ${kmobfilter}
		/call FindMob "${kmobfilter}"
		/if (${KillTargetID}) {
			/call GoToNPC "${tname}" "id ${KillTargetID}" ${kstep}
			/attack on
			/delay 5s ${Me.XTarget}
			/while (${Me.XTarget}) {
				/delay 5
				/if (!${Me.Combat} && ${Target.ID}) {
					/attack on
				}
				/if (${Target.ID} && ${Target.State.Equal[FEIGN]}) {
					/attack off
					/squelch /target clear
					/delay 1s !${Target.ID}
				}
				/if (${Target.ID} && ${Target.Type.Equal[Corpse]}) {
					/squelch /target clear
					/delay 1s !${Target.ID}
				}
				/if (!${Target.ID} && ${Me.XTarget}) {
					/tar id ${Me.XTarget[1].ID}
					/delay 5s ${Target.ID}==${Me.XTarget[1].ID}
				}
			}
		}
		/delay 5s
		
		/goto :step_loop
	} else {
		/echo already did step ${kstep} ${Task[${tname}].Objective[${kstep}]}
	}
/return

Sub KillNPC2(string tname,string kmobfilter1,string kmobfilter2,int kstep)
	:step_loop
	/if (${Task[${tname}].Step.Index}==${kstep}) {
		/varset KillTargetID 0
		/echo [${Time}] time to grab ${kmobfilter1} and ${kmobfilter2}
		/call FindMob "${kmobfilter1}" "${kmobfilter2}"
		/if (${KillTargetID}) {
			/call GoToNPC "${tname}" "id ${KillTargetID}" ${kstep}
			/attack on
			/delay 5s ${Me.XTarget}
			/while (${Me.XTarget}) {
				/delay 1
				/if (!${Me.Combat} && ${Target.ID}) {
					/attack on
				}
				/if (${Target.ID} && ${Target.State.Equal[FEIGN]}) {
					/attack off
					/squelch /target clear
					/delay 1s !${Target.ID}
				}
				/if (${Target.ID} && ${Target.Type.Equal[Corpse]}) {
					/squelch /target clear
					/delay 1s !${Target.ID}
				}
				/if (!${Target.ID} && ${Me.XTarget}) {
					/tar id ${Me.XTarget[1].ID}
					/delay 1s ${Target.ID}==${Me.XTarget[1].ID}
				}
			}
		}
		/delay 1s
		
		/goto :step_loop
	} else {
		/echo already did step ${kstep} ${Task[${tname}].Objective[${kstep}]}
	}
/return
Sub Collect(string tname,string what,int stinde)
	:collect_loop
	/while (${Cursor.ID}) {
		/autoinv
		/delay 1s !${Cursor.ID}
		/delay 1s
	}
	/if (${Task[${tname}].Step.Index}==${stinde}) {
		/itemtarget ${what}
		/delay 2s ${Ground.ID}
		/if (${Ground.DisplayName.Equal[*Red Mushroom]}) {
			/nav item
			/delay 2s ${Navigation.Active}==TRUE
			/delay 60s ${Navigation.Active}==FALSE
			/click left item
		}
		/delay 1s
		/goto :collect_loop
	} else {
		/echo already did step ${stinde} ${Task[${tname}].Objective[${stinde}]}
	}
/return