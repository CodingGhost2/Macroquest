RGMercs attempts to keep its various APIs isolated from each other and independent of the core rgutil.inc file. In not all cases is this successful and API documentation will discuss any expectations on the initialization of core variables.

## Includes
All RGMercs libraries are stored in the lib folder
*  `rgbind.inc` - Includes all RGMercs binds
*  `rgdannet.inc` - Includes RGMercs Dannet APIs
*  `rgdatatypes.inc` - Includes APIs fo RGMercs complex data types (ordered rotations, buffgroup sets, ability sets, etc...)
*  `rgdebug.inc` - Debug binds, defines, and functions
*  `rgevents.inc`- Includes all RGMercs combat-response events, zone events, and cast-outcome events
*  `rgheal.inc` - Includes the healing API
*  `rghotkeys.inc` - Includes the Hotkeys setting system
*  `rgmez.inc` - Includes the Mez API
*  `rgpull.inc` - Includes the pull system
*  `rgsettings.inc` - Includes RGMercs Settings API
*  `rgtov.inc` - Includes curing the ice DoT in ToV
*  `rgtwist.inc` - Includes Bard Twist System and API
*  `rgutil.inc` - Core RGMercs macro functions, rotation execution functions, and utility functions that don't fit in another system

## Pulling Out API Elements
Getting a list of all RGMercs settings:
```
egrep -h -r "\s*(|-){0}\s*/call IHCLoadSetting" * --include=*.inc | egrep -v "\|-" | sed 's/[ ]\+/ /g' | sed 's/^[ \t]*//' | awk -vFPAT='([^ ]*)|("[^"]+")' -vOFS=' ' '{print "["$3"]","[b]"$4"[/b]","==",$7}' | sed 's/${Me.Class.ShortName}/BRD OR ENC/g'
```

Getting a list of all RGMercs binds in alphabetical order:
```
egrep -h -r "\s*#bind" --include=*.inc * | sed 's/[ ]\+/ /g' | cut -d' ' -f3 | sort
```

Getting the changelog for the month:
```
git log --pretty=format:"%cs - %s" --since=MM/DD/YYYY
```

## Core API
There are a number of common functions used in all rgmercs macros.

### IHCInit
Used to set common rgmercs status outer value, necessary lists, and central settings.

### OuterVarInit
Used to set the rest of the common outer values used by the rgmercs.

### LoadCommonConfig
Used to load common INI configuration information and settings. Also provides the help information for those settings.

## Heal API
The intuition behind the Heal API for RGMercs is to allow a class macro author the ability to provide a list of health levels (i.e., heal points) at which to cast a prioritized list of spells. Thus, you can say things like, I want my Shaman two use RecklessHeal1 when any character in my group reaches 80% health. If RecklessHeal1 isn't available, I want my Shaman to cast RecklessHeal2. The goal of the Heal API is to unify the set of functions used to heal across all characters with healing abilities.

Notes:
* The Heal API relies on Ordered Rotations 

### Creating Heal Points
Creating a heal point is done with the Heal_AddHealPoint sub:
```Sub Heal_AddHealPoint(int heal_point)```

The heal_point argument is a health percentage between 1-99. Thus, to add a heal point that will trigger at 60% health or below, you would do:
`/call Heal_AddHealPoint 60`

This is generally done in the Class's SetRotation functional that is called during initialization.

Many RGMercs class macros create heal points based on settings that a user can change and then restart the macro. For example in RGSHM, the MainHealPoint setting is used as a variable to a heal point.
`/call Heal_AddHealPoint ${MainHealPoint[SETTINGVAL]}`

Note: These levels cannot be changed after creation and instead the macro must be restarted.

### Configuring Heal Points
Adding spells to heal points is done with the Heal_AddSpell subroutine:
```Sub Heal_AddSpell(int heal_point, string spell_name, string condition, string index)```

`heal_point` is the numerical value of a heal point set with Heal_AddHealPoint. `spell_name` is the spell name of the heal to cast. `condition` is an MQ2 logical statement that will be evaluated to see if the heal should be cast. `index` is an optional parameter that allows the insertion of heals out of order instead of priority order. All spells added with Heal_AddSpell will be cast with the priority in which they were added (i.e., the first spell added has highest priority, the second spell added has second highest priority, etc...). For example:
```
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${RecklessHeal1}" TRUE
    /call Heal_AddSpell ${MainHealPoint[SETTINGVAL]} "${RecklessHeal2}" TRUE
```
This adds `${RecklessHeal1}` to the Heal Point defined by `${MainHealPoint[SETTINGVAL]}` as the highest priority spell. If `${RecklessHeal1}`, then the heal routine will attempt to cast `${RecklessHeal2}`. The condition set to `TRUE` means that there are no special conditions that need to be set. 

The following example contains a condition for group healing:
```
/call Heal_AddSpell ${GroupHealPoint[SETTINGVAL]} "${RecourseHeal}" ${Parse[1,"( ${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]} )"]}
```

This adds the `${RecourseHeal}` to the `${GroupHealPoint[SETTINGVAL]}` but will only cast it if the number of people in the group injured to ``${GroupHealPoint[SETTINGVAL]}`%HP or below is greater than the number of individuals defined by `${GroupInjureCnt[SETTINGVAL]}`. You'll also notice usage of the `Parse` TLO. Parse TLO allows us explicit control on how the MQ2 parser engine handles parsing MQ2 statements. It is a more refined version of `/noparse`. Here we use it to make sure the condition does not get fully parsed until we're ready to check it during spell Cast. The Parse TLO is used in the form of:
```
${Parse[<# of parser iterations>,"( <boolean conditions> )"]}
```
Changing the # of parser iterations allows us to limit the number of evaluations we must do at cast time thus making the macro more responsive. In this case we want the parser to run only once over the statement `${Group.Injured[${GroupHealPoint[SETTINGVAL]}]} > ${GroupInjureCnt[SETTINGVAL]}`. We do this because GroupHealPoint will require restarting the macro to effectively change, thus, we can tell MQ2 to resolve `${GroupHealPoint[SETTINGVAL]}` (it will be parsed first as it is the most 'inner' statement), but not the rest of the condition. If you're uncomfortable with leveraging the Parse TLO it is always save to just say `${Parse[0,"( <boolean conditions> )"]}`.

You'll see these Parse conditions when we discuss the Rotations API and the Buff Groups API. It's common pattern in rgmercs. 

To reduce the amount of work a class macro author has to do, the `Heal_AutoBackFill` sub exists:
```
Sub Heal_AutoBackFill
```
This sub automatically backfills the low %HP healing points with the spells from the higher %HP healing points. The goal of this macro is to provide a best alternative set of healing spells in case the preferred spells are on cool down. This *must* be used after all calls to `Heal_AddSpell`.

Note: You can only use Heal_AddSpell after creating a heal point with Heal_AddHealPoint

### Casting Heals
Casting heals is now very easy. Just use the HealNow subroutine:
```Sub HealNow(int target_id)```

`target_id` is the target you want to cast a heal on. The `HealNow` subroutine chooses the closest `HealPoint` to the targets health (rounded up). If you pass `0` to the HealNow routine, it will return before processing anything.

The general pattern for calling `HealNow` is to use the `WorstHurtGroup` to determine the best person to cast the heal on in the group:
```Sub WorstHurtGroup(int min_health_loss)```

`min_health_loss` is the %HP level that you start caring about healing them.
Returns: Spawn ID of the worst hurt group member or 0 if no one meets `min_health_loss`. This is taken advantage of in HealNow and HealAA.

In RGSHM this looks like:
```
    /call HealNow ${WorstHurtGroup[${HoTPoint[SETTINGVAL]}]}
```

Here we don't worry about any group member until they're at `${HoTPoint[SETTINGVAL]}` %HP or below. When they reach below that %HP that character will get healed using a spell from the nearest `HealPoint` rounded up.

Note: HealNow will target `target_id` prior to executing the rotation so this could lead to rapid target flipping if you don't have any heals ready to cast.

## DanNet API

### DanNet Observers

### DanNet Queries

## Rotations API

### Creating Rotation Objects

### Adding spells, abilities, etc... to rotations

### Using rotations in class macros

## BuffGroup API

### Creating BuffGroup types

### Adding spells, abilities, etc... to buffgroups

### Calling buffgroups

## AbilitySet API

### Creating AbilitySet types

### Choosing Abilities

## Settings API

### Creating a Setting

### Changing Settings within a macro

## TOV Restless Ice API

## ChatBeg API

### Creating a ChatBeg Type

### Adding Chat Begs

### Calling the ChatBeg API