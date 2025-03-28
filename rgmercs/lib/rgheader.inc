|************************************************************************************|
|-    RGMercs Engine Directive Section
|-
|- RGMercs leverages #define for two predominant cases:
|-  1. Regularly used conditions in order to improve readability of code and reduce maintenance effort.
|-  2. Regularly used spawnsort strings

|- Enable Knightly's new parsing engine. This allows for greater control
|- of passing unparsed variables via the ${Parse[]} TLO and should fix
|- some parser bugs according to Knightly's README. This may have side
|- effects with a corner case of /noparse being used with commands
|- that don't actually parse values.
#warning
#engine parser 2
#turbo 120

| ******************* |
| ***** DEFINES ***** |
| ******************* |

| --------------------
|    MUST BE FIRST
|
| From: rgsettings.inc
| --------------------

|- Defines for easy recollection of the list order for the RG Setting Maps
#define INISECTION   1
#define SETTINGVAL   2
#define SETTINGDESC  3
#define ADVANCED     4
#define CALLBACK     5

|- Defines for easy recollection of print modes for the RGPrintMap function
#define PRINTSETTINGS 100
#define PRINTHELP     101
#define PRINTADVANCED 102

|- Delimiter to use for lists
#define DELIM |

| ---------------------
| From: rgdatatypes.inc
| ---------------------

#define AURA TRUE

| -----------------
| From: rgdebug.inc
| -----------------

#define DEBUG "/if (${DebugLog[SETTINGVAL]}==1) /mqlog |${Me.Class.ShortName}|${Macro.CurSub}|INVIS:${Me.Invis}|-" 
#define EDEBUG "/echo RGMercs Debug: \ar |${Macro.CurSub}\ax|\arINVIS:${Me.Invis}\ax|-" 

#define PROFILESTART    "/varset SubstartTime ${MacroQuest.Running}"
#define PROFILESTOP     "/echo ${Macro.CurSub} TOOK \ar${Math.Calc[((${MacroQuest.Running}-${SubstartTime}) / 10) / 60]}s\ax"

| -----------------
| From: rgdebug.inc
| -----------------

|- Alias for DoEvents to make it clear why we're calling it
#define GET_CAST_RESULT /doevents

| ----------------
| From: rgpull.inc
| ----------------

|- Pull Status defines to avoid magic numbers
#define PULL_INIT -1
#define PULL_IDLE 0
#define PULL_SEARCHING 1
#define PULL_NAVTO 2
#define PULL_PULLING 3
#define PULL_RETURNFROM 4
#define PULL_GROUPWATCH 5
#define PULL_NAVINTERRUPT 6
#define PULL_NAVWP 7

#define PERCENTRANGE 0.99
#define NOTIFICATIONDELAY 300

|- Defines to avoid pull mode magic variables.
#define PMODE_OFF 0
#define PMODE_VANILLA 1
#define PMODE_HUNT 2
#define PMODE_CHAIN 3
#define PMODE_FARM 4

| -----------------
| From: rgtwist.inc
| -----------------

#define SWAPSLOT offhand

| ----------------
| From: rgutil.inc
| ----------------


|- Default Window Title Set -- Can be configured to your preferred setup when using RGMercs.
#define WINDOWTITLE "<${MacroName}>${Me.Name}(${Zone.ShortName}) Assisting: ${assistname} Version: ${RGVersion} PID:${EverQuest.PID}"

|- Universal BURN Conditions used throughout RGMercs to check for burn mode
| /if ( ${MacroQuest.InternalName.Equal[Next]} ) {
|#define BURNCHECK "( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} || (${SpawnMaster.HasTarget} && ${BurnNamed[SETTINGVAL]}) || ${BurnAlways[SETTINGVAL]} || ${burnnow} )"
| } else {
#define BURNCHECK "( ( ${BurnAuto[SETTINGVAL]} && ( ${XAssist.XTFullHaterCount}>=${BurnMobCount[SETTINGVAL]} ||  ${Target.Named} && ${BurnNamed[SETTINGVAL]}  || ${BurnAlways[SETTINGVAL]} && ${BurnAuto[SETTINGVAL]} ) ) ||  ( !${BurnAuto[SETTINGVAL]} && ${BurnSize[SETTINGVAL]} ) )"    

|}
|-- Standard Main Loop Condition Checks.
#define FINDTARGETCHECK     "( ( ${XAssist.XTFullHaterCount} || ( ${assistid}==${Me.ID} ) || ${FollowMarkTarget[SETTINGVAL]} || ${DoPull[SETTINGVAL]}) && !${BackOffFlag} )"
#define DOMEZCHECK          "( ${MezOn[SETTINGVAL]} && ${XAssist.XTFullHaterCount}>=${MezStartCount[SETTINGVAL]} )"
#define DOHEALCHECK         "( !${Me.Casting.ID} && ( (!${XAssist.XTFullHaterCount} && ${Me.Invis} && ${BreakInvis[SETTINGVAL]}) || ${XAssist.XTFullHaterCount} || !${Me.Invis} ) )"
|- #define DOCOMBATACTIONS     "( ${autotargetid} && (${XAssist.XTFullHaterCount} || ${KillTargetID}) && ${Spawn[id ${autotargetid}].Distance}<${AssistRange[SETTINGVAL]} && !${BackOffFlag} )"
#define DOCOMBATACTIONS     "( ${DoCombatActions[]} )"
|- #define DODEBUFF            "( (${XAssist.XTFullHaterCount} || ${KillTargetID}) && ${Target.ID} == ${autotargetid} && ${Target.Distance}<${AssistRange[SETTINGVAL]} && ${Target.PctHPs}<=${AutoDebuffAt[SETTINGVAL]} && !${BackOffFlag} )"
#define DODEBUFF            "( ${DoDebuffCheck[]} )"
|- #define DODPS               "( (${XAssist.XTFullHaterCount} || ${KillTargetID}) && ${Target.ID} == ${autotargetid} && ${Target.Distance}<${AssistRange[SETTINGVAL]} && (${Target.PctHPs}<=${AutoAssistAt[SETTINGVAL]} || ${Me.ID} == ${assistid}) && !${BackOffFlag} )"
#define DODPS               "( ${DoDPSCheck[]} )"
#define DOFOLLOW            "( ${Spawn[=${FollowToonName[SETTINGVAL]}].ID} && !${MoveTo.Moving} && (!${Me.Casting.ID} || ${Me.Class.ShortName.Equal[BRD]}) && (!${XAssist.XTFullHaterCount} || ${Spawn[id ${assistid}].Distance}>${ChaseDistance[SETTINGVAL]}) )"
|#define DOFOLLOW            "( ${Spawn[=${FollowToonName[SETTINGVAL]}].ID} && !${MoveTo.Moving} && (!${Me.Casting.ID} || ${Me.Class.ShortName.Equal[BRD]}) && (!${XAssist.XTFullHaterCount} || ${Spawn[id ${assistid}].Distance}>${AssistRange[SETTINGVAL]} || !${Spawn[id ${assistid}].LineOfSight}) )"
|#define DOBUFFS             "( ${DoBuffCheck[]} )"
#define DOCAMP              "( !${XAssist.XTFullHaterCount} && !${KillTargetID} )"
|- KILLTGTRESET Used to determine when to reset information set by the KillTarget bind in RGbinds 
#define KILLTGTRESET        "( ( (!${Spawn[targetable id ${KillTargetID}].ID}) || ${Spawn[corpse id ${KillTargetID}].ID} ) && ${KillTargetID}!=0 )"
#define MANAGEAGGROCHECK    "( ${Math.Calc[${XAssist.XTXAggroCount[101]} - ${XAssist.XTXAggroCount[60]}]} > 0 )"
#define MODRODCHECK 		"( ${DoModRod[SETTINGVAL]} )"
#define MEDCHECK			"( ${DoMed[SETTINGVAL]} )"
#define TANKAGGROCHECK		"( (${XAssist.XTFullHaterCount} || ${KillTargetID}) && !${BackOffFlag} && ${IsTanking} )"

#define HOVERCHECK			"( ${Me.Hovering} )"
#define ZONECHECK			"( ${Me.Zoning} )"
#define CURSORCHECK			"( ${Cursor.ID} )"
#define ICECHECK			"( ${Me.Song[Restless Ice].ID} )"

|- Standard Pet Defines
#define PETENGAGE 			"((!${Me.Pet.Combat} || ${Pet.Target.ID}!=${autotargetid}) && ${Me.Pet.ID} && ${Target.CleanName.NotEqual[NULL]} && ${Target.Type.Equal[NPC]} && (${Target.PctHPs}<=${PetEngagePct[SETTINGVAL]} || (${assistid} == ${Me.ID} && ${IsTanking})) &&  ${DoPet[SETTINGVAL]})"
#define PETBACKOFF			 "( ${Me.Pet.ID} && ${Me.Pet.Combat} && !${BackOffFlag} && !${Ok2Engage[]})"

#define MERCENGAGE          "( ${Target.ID} && ${Target.ID} == ${autotargetid} && (${Target.PctHPs}<=${AutoAssistAt[SETTINGVAL]} || ${Me.Mercenary.Class.ShortName.Equal[CLR]} || (${Me.Mercenary.Class.ShortName.Equal[WAR]} && ${Group.MainTank.ID} == ${Me.Mercenary.ID}) ) && ${Target.Distance}<${AssistRange[SETTINGVAL]} )"

|-- Standard Healer defines
#define REZSEARCHGROUP 		"pccorpse group radius 100 zradius 50"
#define REZSEARCHME 		"pccorpse ${Me} radius 100 zradius 50"
#define OUTOFGROUPREZ       "pccorpse radius 100 zradius 50"
#define DOPRIORITYHEAL       "( ${IsHealing} && ( ${WorstHurtGroup[${HealPoint_MaxPoint}]} || (${AssistOutside[SETTINGVAL]} && ${WorstHurtXT[${HealPoint_MaxPoint}]}) ) )"

|- CON Color Checks
#define CONGLBWYR	        "( ${Target.ConColor.Equal[GREEN]} || ${Target.ConColor.Equal[LIGHT BLUE]} || ${Target.ConColor.Equal[BLUE]} || ${Target.ConColor.Equal[WHITE]} || ${Target.ConColor.Equal[YELLOW]} || ${Target.ConColor.Equal[RED]} )"
#define CONLBWYR	        "( ${Target.ConColor.Equal[LIGHT BLUE]} || ${Target.ConColor.Equal[BLUE]} || ${Target.ConColor.Equal[WHITE]} || ${Target.ConColor.Equal[YELLOW]} || ${Target.ConColor.Equal[RED]} )"
#define CONBWYR	            "( ${Target.ConColor.Equal[BLUE]} || ${Target.ConColor.Equal[WHITE]} || ${Target.ConColor.Equal[YELLOW]} || ${Target.ConColor.Equal[RED]} )"
#define CONWYR	            "( ${Target.ConColor.Equal[WHITE]} || ${Target.ConColor.Equal[YELLOW]} || ${Target.ConColor.Equal[RED]} )"
#define CONYR		        "( ${Target.ConColor.Equal[YELLOW]} || ${Target.ConColor.Equal[RED]} )"
#define CONR		        "( ${Target.ConColor.Equal[RED]} )"

|- Useful Conditions for all rotations
#define GEMCHECK            "( ${Me.Gem[${mi.Key}]} && !${Me.GemTimer[${Me.Gem[${mi.Key}]}]} )"

|- Useful Conditions For Downtime Rotations

#define HASBUFFGROUPCHECK   "()"
#define SELFBUFFCHECK       "( !${Me.Buff[${mi.Key}].ID} && ${Spell[${mi.Key}].Stacks} )"
#define SELFBUFFPETCHECK    "( !${Me.PetBuff[${mi.Key}]} && ${Spell[${mi.Key}].StacksPet} && ${target_id} == ${Me.Pet.ID} && ${Me.Pet.ID} )"
#define SELFFBUFFTRIGGER    "( !${Me.Buff[${Spell[${mi.Key}].Trigger[1]}].ID} && ${Spell[${mi.Key}].Trigger[1].Stacks} )"
#define SELFBUFFAACHECK     "( (!${Me.Buff[${Spell[${Me.AltAbility[${mi.Key}].Spell}].RankName}].ID} && !${Me.Buff[${Me.AltAbility[${mi.Key}].Spell.Trigger[1]}].ID} && !${Me.Buff[${Spell[${mi.Key}].RankName}].ID} && !${Me.Aura[${Spell[${mi.Key}].RankName}].ID}) && ( ${Spell[${Spell[${Me.AltAbility[${mi.Key}].Spell}].RankName}].Stacks} || ${Spell[${Me.AltAbility[${mi.Key}].Spell.Trigger[1]}].Stacks} ) )"
|- Useful Conditions for DPS Rotations
#define MANACHECK           "( ${Me.PctMana} > ${Manatonuke[SETTINGVAL]} )"
#define DETSPELLCHECK       "( !${Target.Buff[${mi.Key}].ID} && ${Spell[${mi.Key}].StacksTarget} )"
#define DOTSPELLCHECK       "( DETSPELLCHECK && (${Target.PctHPs}>${HPStopDOT[SETTINGVAL]}) )"
#define DETAACHECK          "( (!${Target.Buff[${Me.AltAbility[${mi.Key}].Spell}].ID} && !${Target.Buff[${Me.AltAbility[${mi.Key}].Spell.Trigger[1]}].ID}) && (${Spell[${Me.AltAbility[${mi.Key}].Spell}].StacksTarget} || ${Spell[${Me.AltAbility[${mi.Key}].Spell.Trigger[1]}].StacksTarget}) )"
#define DETGOMCHECK         "( ${Me.Song[Gift of Mana].ID} && ${Me.Gem[${mi.Key}]} && (${Spell[${Me.Song[Gift of Mana]}].Base[3]} >= ${Me.Spell[${mi.Key}].Level})  )"
#define DETSTUNCHECK         " ( !${Target.Stunned} && DETSPELLCHECK )"
|#define MEZIMMUNEBODY       "( ${Target.Body.Name.Equal[Giant]} || ${Target.Named} || ( ${Target.Name.Find[giant]} && ${Select[${Zone.ID},824,827,829]} ) ) "
|- Conditions for manual burn contorl
#define SMALLBURN   "( ${BurnSize[SETTINGVAL]}>=1 )"
#define MEDBURN     "( ${BurnSize[SETTINGVAL]}>=2 )"
#define BIGBURN     "( ${BurnSize[SETTINGVAL]}>=3 )"



|- Common Class list
#define RGCASTERS   "BRD,BST,CLR,DRU,ENC,MAG,NEC,PAL,RNG,SHD,SHM,WIZ"
#define RGMELEE     "BRD,SHD,PAL,WAR,ROG,BER,MNK,RNG,BST"
#define RGHYBRID    "SHD,PAL,RNG",BST,BRD"
#define RGTANK      "WAR,SHD,PAL"
#define RGMODROD    "BST,CLR,DRU,SHM,MAG,ENC,WIZ,NEC,PAL,RNG,SHD"
#define RGPETCLASS  "BST,NEC,MAG,SHM,ENC,SHD"
|- Class Specific Define'settings
|- Beastlord
#define DOPARAGON "( !${Me.Casting.ID} && ${fparatimer2}==0 && (!${Me.Invis}) && !${MoveTo.Moving} && !${AdvPath.Following} && (${Me.AltAbilityReady[Focused Paragon of Spirits]} || ${Me.AltAbilityReady[Paragon of Spirits]})) "

#define TRIGGERBIND "/call TriggerBinds"


|----------------------------------------------------------------------------  
|- SUB: Bind_RGdebug_printset 
|- Prints out a set variable
|----------------------------------------------------------------------------
#bind RGdebug_printset /printset

|AA extended checks
Sub RG_CanUseAA(string cast_item)
/declare ret bool local TRUE
	/varcalc ret ${AltAbility[${cast_item}].MinLevel} <=  ${Me.Level} && ${AltAbility[${cast_item}].Rank} > 0
/return ${ret}

Sub RG_AAReady(string cast_item)
    /declare ret bool local FALSE
    /varcalc ret ${RG_CanUseAA[${cast_item}]} && ${Me.AltAbilityReady[${cast_item}]}
/return ${ret}


| ******************** |
| ***** INCLUDES ***** |
| ******************** |

| Real-time call tracing in large macros
#include rgmercs\lib\rgtrace.inc

#include rgmercs\lib\rgsettings.inc

|- Add Debug printout -- can be expanded upon later.
#include rgmercs\lib\rgdebug.inc
#include rgmercs\lib\rgevents.inc

#include rgmercs\lib\rgdatatypes.inc
#include rgmercs\lib\rgdannet.inc
#include rgmercs\lib\rgbind.inc
#include rgmercs\lib\rgpull.inc
#include rgmercs\lib\rgheal.inc
#include rgmercs\lib\rgtwist.inc
#include rgmercs\lib\rgmez.inc
#include rgmercs\lib\rgpet.inc
#include rgmercs\lib\rgtov.inc
#include rgmercs\lib\rghotkeys.inc
#include rgmercs\lib\rgquest.inc

|- Must always be included after RGsettings.inc
#include rgmercs\lib\rgutil.inc

|- Class macros
#include rgmercs\classes\rg${Me.Class.ShortName.Lower}util.inc
