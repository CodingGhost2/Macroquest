Below is an example HUD for RGMercs that can be used with mq2hud. It's predominantly designed to help debug the macro but should provide a strong foundation for those who want a HUD with RGMercs.

Copy and paste the below hud to the top of your mq2hud.ini.

You _should_ be able to turn on this hud in game then by doing /loadhud rgmercs_hud and hitting F11 or the equivalent hud key.

See https://www.redguides.com/community/resources/mq2hud.133/ for how to use mq2hud.

```
[rgmercs_hud]
Last=Elements
SkipParse=1
CheckINI=10
UpdateInBackground=off
ClassHUD=off
ZoneHUD=off
GMIndicator=3,660,14,255,255,255,GM - ${NearestSpawn[GM]}
GameTime=3,660,26,255,255,255,GameTime: ${GameTime.Hour}:${GameTime.Minute} - ${If[${Bool[${GameTime.Night}]},Night,Day]}
Movement1=3,660,38,0,240,0,MoveTo: ${MoveTo.Moving} || NAV: ${Navigation.Active}
Speed=3,660,50,0,240,0,Speed - ${Int[${Me.Speed}]} || ${Int[${Navigation.Velocity}]}
Movement2=3,660,62,150,250,150,Stuck: ${MoveUtils.Stuck} || Stick: ${Stick} || LOS: ${Target.LineOfSight}
NS=3,660,74,255,255,255,~~~~~~~ Target Info ~~~~~~~
maxmelee=3,660,86,255,255,255,${If[${Target.ID},Max Melee Range: ${Target.MaxRange},]}
TargetDist=3,660,98,255,255,255,${If[${Target.ID},Target Distance:    ${Target.Distance},]}
NS2=3,660,110,255,255,255,~~~~~~~ PC Info ~~~~~~~
LvlInfo=3,660,122,180,180,180,LVL: ${Me.Level} -> ${Math.Calc[100-${Me.PctExp}]}% to ${Math.Calc[${Me.Level}+1].Int} || Unspent AA: ${Me.AAPoints}
StatuEffects=3,660,134,180,180,180,|${If[${Me.Poisoned.ID},POISONED,]}|${If[${Me.Diseased.ID},DISEASED,]}|${If[${Me.Mezzed.ID},MEZZED,]}|${If[${Me.Tashed.ID},TASHED,]}|${If[${Me.Maloed.ID},MALOED,]}|${If[${Me.Charmed.ID},CHARMED,]}|${If[${Me.Corrupted.ID},CORRUPTED,]}|${If[${Me.Cursed.ID},CURSED,]}|${If[${Me.Corrupted.ID},CORRUPTED,]}|${If[${Me.Dotted.ID},DOTTED,]}|${If[${Me.Rooted.ID},ROOTED,]}|${If[${Me.Slowed.ID},SLOWED,]}|${If[${Me.Snared.ID},SNARED,]}|
InventorySlots=3,660,146,80,255,255,Inventory Free: ${Me.FreeInventory} || SubDays: ${Me.SubscriptionDays}
ZoneInfo=3,660,158,255,255,0,Zone - ${Zone} - ${Zone.ShortName}
GroupLeader=3,660,170,255,255,255,${If[${Group},Group Leader : ${Group.Leader.Name},]}
Raid1=3,660,182,180,180,180,${If[${Raid},Raid Leader: ${Raid.Leader},]}

CurSub=19,900,14,180,180,180,CurSub: ${Macro.CurSub}
Command=19,900,28,180,180,180,CurCommand: ${Macro.CurCommand}
NS3=3,900,40,255,0,0,~~~~~~~ RGMercs Info ~~~~~~~
Targeting=19,900,52,153,255,204,AutoTarget?: ${If[${DoAutoTarget[2]},AUTO,MANUAL]} ${If[${autotargetid},${Spawn[id ${autotargetid}].CleanName}[${autotargetid}],]}
CampChase=19,900,64,153,255,204,Chase: ${If[${FollowToonName[2].NotEqual[NULL]},ON <${FollowToonName[2]}>,OFF]} || Camp:${If[!${ReturnToCamp[2]},OFF,]}${If[${ReturnToCamp[2]}==1,SOFT,]}${If[${ReturnToCamp[2]}==2,HARD,]} ${If[${ReturnToCamp[2]},X:${AutoCampX} Y:${AutoCampY} Z:${AutoCampZ},]}
MedMode=19,900,76,122,255,255,ClassMode: ${ClassMode[2]} DoMed: ${DoMed[2]}
MainAssist=19,900,88,255,102,178,${If[${Defined[assistname]},Main Assist: ${assistname} || A.Rng: ${AssistRange[2]},]}
AssistOutsideInfo=19,900,100,122,255,255,AssistOutside: ${If[${AssistOutside[2]},ON <${Math.Calc[${OutsideAssistList[2].Count[|]}+1].Int} MA Backups>,OFF]}
Ok2Assist=19,900,112,122,255,255,[[BackOff?:${If[${BackOffFlag},ON,OFF]}]]
BurnModeOFF=19,900,124,0,255,0,BURNMODE: ${If[ !(${XAssist.XTFullHaterCount}>=${BurnMobCount[2]} || (${Target.Named} && ${BurnNamed[2]}) || ${BurnAlways[2]} || ${burnnow}),OFF,]}
BurnModeON=19,900,124,255,0,0,BURNMODE: ${If[ (${XAssist.XTFullHaterCount}>=${BurnMobCount[2]}  || (${Target.Named} && ${BurnNamed[2]}) || ${BurnAlways[2]} || ${burnnow}),ON,]}
PullInfo=19,900,136,255,178,102,Pull Mode: ${DoPull[2]} ${If[${DoPull[2]}==4,WP: ${Pull_FarmWPNum} FARMRad: ${PullFarmRad[2]}/${PullZRad[2]},Rad:${PullRad[2]}/${PullZRad[2]}]} 
PullInfo2=19,900,148,255,178,102,${If[${LvlAutoCalc[2]},AUTO,]}LVL:${PullMinLvl[2]}-${PullMaxLvl[2]} GroupWatch:${GroupWatch[2]}
CapeSet=19,900,160,122,255,255,|${If[${IsTanking},TANKING,]}|${If[${IsHealing},HEALING,]}|${If[${IsMezzing},MEZZING,]}|${If[${IsCharming},CHARMING,]}|${If[${IsCuring},CURING,]}|

```