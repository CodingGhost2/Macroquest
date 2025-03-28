## An Introduction to RGMercs
RGMercs is a set of class specific macros designed to be easy to use "out of the box" with minimal configuration. They were originally based on the Auto series of macros and compiled into the IHC omnibus by @ihc385. When @ihc385 departed, @morisato took over as maintainer due to his passion and love for the macro's usability. RGMercs are designed to be lean, mean, fighting (or healing) machines. They will accomplish at least 80% of whatever you throw at them. RGMercs characters are designed to behave a more efficient and advanced mercenaries. As such do not expect them to look or act like humans. This also means "driving" (boxing terminology for actively performing most of a characters actions) an RGMercs toon may require more effort in some cases (you can find a driving howto [here](HOWTO_DrivingRGMercs). 

RGMercs is for, as mentioned prior, users who want a minimal configuration out of the box experience. It will provide sensible default values and a set of in-game (or ini-based) configuration toggles for cases where you need to turn certain behaviors on and off. If you are leveling up you need just restart the macro after learning new spells/abilities to use them -- there is no per-level configuration required. This makes RGMercs perfect when you want to quickly add another member to your group, try out a new class with your current team without a lot of configuration, or have a pocket farmer with a heftier combat routine.

RGMercs will not be for users who want lots of customization or have specific opinions on how a class should play. RGMercs is not designed to be configured to your specific needs. You cannot easily change rotations to exactly what you want to use. If you need a more configurable macro, please look at Entropy, Modbot, Mule Assist, and Kissassist. Any configuration options we will provide will require you to write your own code in an `rgcustom.inc` file so we expect this will only be done by advanced users. If you have potential design suggestions, you can put a 'Request' up to the RGMercs forum for discussion (https://www.redguides.com/community/forums/rgmercs.134/).

The goal of this initial RGMercs manual is to get you up and running with RGMercs. It will go through installing RGMercs, setting your group up for the first time, moving around, fighting, and some simple questing. Other intermediate and advanced guides will walk you through other features.

## Installing RGMercs

By this point we're going to assume you've watched the following videos:
* https://www.redguides.com/community/resources/multiboxing-everquest-the-red-guide-videos.1603/

Installing RGMercs is easy. It involves heading to the RedGuies site, watching the RGMercs macro page so you can download the macro with your launcher, and running the Installer macro for the first time to add helper alias commands to your macroquest.ini.

1. Head to: https://www.redguides.com/community/resources/rgmercs.1013/
2. Click the 'Watch' button on the right side of the page, it's next to "Leave a rating".
3. Download the macro via the RedGuides Launcher.
4. Run the `RGMercsInstall.mac` on all your characters (`/bcaa //mac RGMercsInstall.mac`)

While running `RGMercsInstall.mac` is technically optional, it does a number of helpful things:
1. Enables the DanNet plugin on the character who runs it.
2. Creates the `/rgstart` alias for quickly starting rgmercs on one character.
3. Creates the `/rgroup` alias for quickly starting rgmercs for your whole group.
4. Creates the `/mgx` (Execute command on all but myself), `/mgax` (Execute command on all including myself), `/mgt` (send DNet tell to group leader) aliases so @ihc385 had DanNet commands that felt more like EQBC.

If you do not want to run `RGMercsInstall.mac` you will need to manually start RGMercs with `/mac rgmercs/RGMERC.mac` on every character you want to run the macro on.

RGMercs will load the following plugins on first use:
* MQ2Collections
* MQ2Exchange
* MQ2Rez
* MQ2AdvPath
* MQ2MoveUtils
* MQ2Nav
* MQ2DanNet
* MQ2Xassist

RGMercs will **unload* the following plugins due to known conflicts:
* MQ2Twist
* MQ2Melee

## Starting RGMercs for the first time

Pre-requisites:
1. Make sure the Main Assist role is set for your group. This is necessary for RGMercs to know who to follow for targeting. If RGMercs is running on the Main Assist it lets them know that they need to seek out threats against the group.
2. Set your puller and tank modes. These are used when setting hotkeys.
3. RGMercs **does not** allow you to target a pet or a mercenary as main assist. If you do this you will beak things so don't do it!

Assumptions:
1. Never target a pet and start RGMercs. Pets should not be your Main Assist.
2. Never target a Mercenary and start RGMercs. Mercenaries should not be your Main Assist.

## Changing Settings
Unlike other macros, RGMercs expects you to change your settings **in-game via the `/rg` interface**. INI-based editing is best done only when you're comfortable using RGMercs are and are aware of what changes **are not reset** when the macro is started. *ALL* INI based settings changes require a macro restart.

You can see instructions for getting the current settings values and changing settings values by typing `/rg`. You can get help information by typing `/rg help` for basic settings and `/rg advanced` for advanced settings. If you're wondering what a setting does follow this mantra: `When in doubt: /rg help`. Keep in mind all settings are case sensitive and must be typed with the casting provided in the help menu or via the INI.

_**ALL SETTINGS ARE CASE SENSITIVE AND THIS WILL NEVER CHANGE!!!!!**_

_**I REPEAT: ALL SETTINGS ARE CASE SENSITIVE!!!!!**_

The macro will even tell you in your mq2 window if it thinks you do not have the case sensitivity correct. **So please pay attention.**

Changing settings always follows the same format:
```
/rg TheSettingYouWantToChange <value>
```

For example, to turn off the `acverbose` core setting you would do:
```
/rg acverbose 0
```
To turn it on:
```
/rg acverbose 1
```
Many settings help will say "Set 0/1" you'll see this sort of pattern regularly.


If you want to be exact you can change your specific class setting by issuing:
```
/rg <Class Short Name> TheSettingYouWantToChange <value>
```

For example to disable Heal Nukes for the CLR, you would issue the following command:
```
/rg CLR UseHealNukes 0
```

Generally you can avoid putting the class short name (or Pull for pull setting) and RGMercs will figure it out. It will issue you a warning as it really would prefer you to be specific.

### Setting tanks engagement range

RGMercs is different than KissAssist or MuleAssist. All RGMercs use `AssistRange` to determine how far out they will engage aggressive enemies. This includes tanks. By default `AssistRange` is 100 for everyone. Some tank modes may decrease this. You can determine what your currently engagement range is by typing: `/rg AssistRange`. If this is too short you can raise the value, if it's too long, you can decrease it. For example, to set your AssistRange to 50 you can do:
```
/rg AssistRange 50
```

For dungeon zones with close together floors and highly dense mobs (e.g., **Estate of Unrest**, you may need to change your `MAScanZRange`. This is an advanced setting defined as: "Maximum Z distance an MA will search to find roamers/pullers. Default: 0 [off]". This means it will only ever effect your play if it is set to a non-zero positive value (1-infinity). For zones like *Estate of Unrest** you may want to try setting this to 10. A good way to test what a z-value setting should be (pulling or here) is to use the Height Filter feature of your EQ map. This will display what spawns are "visible" in the height range you specify in the two boxes. In each box put the number you'd like to set MAScanZRange to. If it only shows the mobs you want, you're good, if not, change the numbers. When it is finally appropriate, you can set MAScanZRange via:
```
/rg MAScanZRange 10
```

### Class Mode Changes
Many RGMercs classes have class modes. Class modes allow you to change your role in the group or style of play of the class. These are set with the `ClassMode` setting. For example, PAL has a tank class mode (the default 0), a DPS class mode (1), and an optimized high level end-game tank mode (10). Each of these modes may define different capabilities (healing, tanking, mezzing, curing) that will cause RGMercs to perform different things as part of its normal operation. After changing your ClassMode **you must restart the macro**.

You can see what class modes your class offers by looking at the help menu: `/rg help` and looking for the ClassMode setting.

For a PAL, for example, if you wanted to change to the DPS class mode you would:
1. Type `/rg ClassMode 1` 
2. Restart the macro `/rgstart`.

Setting ClassMode to a number not listed in your help information (or a class mode you've created yourself -- beyond the scope of this beginner's manual), the macro will crash and you will need to manually edit the setting in your ini file.

### Advanced Settings
RGMercs has a number of advanced settings that do not show with the normal `/rg help`. These settings generally do not need to be changed and thus not shown on the normal menu to avoid clutter. You can view the advanced settings for a class by typing `/rg advanced`. You'll also see Pull system and general RGMercs advanced settings.

For example, if you're noticing that your client starts getting choppy when you start RGMercs, you can enable the CPUThrottle advanced setting to slow the macro down a bit and give your system time to catch-up. This may be necessary depending upon your eqclient.ini configuration, the phases of the moon, or other odd issues beyond our control. To do this you could do the following:
1. Type `/rg advanced` and look towards the top of the list (you may need to scroll/expand your mq2 chat window) to read the settings help information and look at its specific name.
2. After reading the settings help you decide you can deal with a decrease in responsiveness so you type `/rg CPUThrottle 1` to add a minor delay. 
3. You realize that you'd still like a little more CPU reduction so you add `/rg CPUThrottle 2`.
4. You find this is good enough and continue playing.

## Moving and Fighting with RGMercs

Moving and fighting with RGMercs is as easy as other macros. You have options for camping and chasing, you have the ability to back-off if you need to stop engagement, the ability to specifically target something to kill, and you have a few handy questing utilities.

### Camping and Chasing
Camping in rgmercs is easy. When camped, RGMercs toons will only return to camp when they leave your `AutoCampRadius`. If you ever need to remember how to camp, look at the help info in `/rg`

To set camp: `/rg camphere`
To stop camping: `/rg campoff`

To decrease or increase your camp radius you can set the `AutoCampRadius` setting. 
If you'd like your RGMercs to return to camp after every single combat you will need to do: `/rg camphard`. This "hard" camps you and will return you to your exact loc after every combat. Given this looks more "suspicious" it is not the default behavior.

Chasing is just as easy to use as RGMercs. RGMercs chasing will use a mq2nav to follow whenever possible. It will use `/moveto` as a backup if you're in a bad spot on the navigation mesh or `/afollow` if there's no mesh at all.

To start chasing: `/rg chaseon` -- this will automatically chase your main assist
To stop chasing: `/rg chaseoff`
To start chasing a specific toon named ExampleToon instead of your main assist: `/rg chaseon ExampleToon`

To change your chase distance, you can change the `ChaseDistance` setting.

For added ease of use, if you start chasing while camping, RGMercs will disable camping. If you set camp while chasing, RGMercs will stop chasing. 

### Backing Off
There are times due to a quest script or other instances you need your group to stop attacking the mob you either were fighting or are currently fighting. To do that use the `/backoffmob` bind (or simply `/backoff`). This will turn on the back-off flag and your RGMercs will not engage the target until you call `/backoff` again. You will see a status message in your MQ2 window when you issue these commands.

If you're just wanting to clear the ID of the mob your RGMerc is fighting so they can switch to your MA's new one. You can call `/combatreset`. `/combatreset` **does not** guarantee you will back-off and exit combat.

Sometimes turning off the main loop for RGMercs is necessary. In this case they will respond to binds but they won't perform any normal activities. To disable the main loop you type `/rg off`. This will disable following, combat, buffing, healing, mezzing, medding, and every other activity RGMercs automates for you. When you are ready to re-engage RGMercs you type `/rg on`. This is sometimes very useful for traveling if you don't like traveling in chase mode but you don't want to pause the full macro.

### Killing Specific Targets
RGMercs has historically worked better in an assisting role versus your driving toon. We've provided some mildly improved quality of life features to help with further targeting. 

If you are driving your main assist and want to enable manual targeting you need to turn off RGMercs autotargeting feature. To do this you set DoAutoTarget to 0: `/rg DoAutoTarget 0`. Now when RGMercs determines you've changed targets it will set your auto target to be the target you selected. As main assist, all toons assisting you will switch targets as well as soon as they call FindTarget again. To speed this up you can ask them to initiate one of the binds discussed at the end of this section.

Helper binds for targeting:
* `/killnow` -- Any RGMerc who issues this command will reset their main assist, target the main assist's mob, set that as their autotarget, and engage in combat.
* `/autotarget` -- Set your auto target to your current target.
* `/killtarget` -- Focus on your current target and ignore others until its dead.

### Questing Utilities
There are three binds that you may find useful while questing with RGMercs:

For when you need your group to all say the same text phrase:
```
/qsay "This is the sample quest text"
```
Note: because this is multiple words, you need to put quotes around them.

For when you need to give an item to someone or something there's `/giveitem`. In the following example we're giving 1 item (Example Item) to the Example NPC.
```
/giveitem "Example Item" 1 "Example NPC"
```
The `/giveitem` command also works to exchange items between your group members.

For when you need to give money to someone or something there's `/givemoney`. In the following example we're giving 5pp to the Example NPC. Other available denominations are: gp, sp, cp.
```
/givemoney 5 pp "Example NPC"
```
The `/givemoney` command also works to exchange items between your group members.

### Very Vanilla Pulling

RGMerc also supports pulling. We'll only discuss Very Vanilla pulling in this section. This is the traditional style of set camp, find mob, pull mob, and return to camp. Other pull modes will be discussed in a specific advanced pulling guide.

First, you need to get your PCs into a camp. Using tools such as `/kaenform <distance>` and `/randomform <distance>` (where <distance> is an numerical value) can help with this. Then you need to start your camp (see the section on camping).

You then have two options:
1. To enable constant pulling you set DoPull to 1: `/rg DoPull 1`  (To pause pulling, just put the setting to 0: `/rg DoPull 0`)
2. To perform a single pull you can call `/singlepull`

To keep you safe and in control, the DoPull setting will reset to 0 whenever you restart the macro or leave the zone. It will restart pulling upon your return to zone. This is so that if you die, return to your bind point, but then are rezzed, you'll get back to pulling. This may continue to change in the future to avoid unwanted edge cases of suicidal PCs.

RGMercs also offers wo different group watch modes:
* `/rg GroupWatch 1` -- Make sure you and any healing classes are above the group watch threshold to continue pulling.
* `/rg GroupWatch 2` -- Make sure any group mates are about the group watch threshold to continue pulling.

RGMercs defaults to an allow listing approach (PullOnly) and falls back on an ignore list approach (PullIgnore). If your allow list is empty and your ignore list is empty, it will pull everything it finds. 

If you add mobs to your allow list, it will **ignore all other mobs in the zone** and only target those on the list. To add a mob to your allow list, target it and type `/addpull`.

If your allow list is empty, you can add mobs to the deny list. RGMercs will never pull a mob on your deny list. To add a mob to this list, target it and type `/addignore`.

To quickly clear either of these lists and restart you can call `/clearpull` and `/clearignore`. If you only want to remove a single mob from either list, you will need to edit the pull info configuration file manually. You'll see a discussion of that shortly.

You can find more pull settings in `/rg help` and `/rg advanced`. If you require further details, you can find them in the more detailed pulling manual

RGMercs pulling information is setup per zone and stored in the `RGPull_Info.ini` file. Details of this file will be discussed in the specific pulling manual. For new users it's suggested you use the binds discussed earlier to add and remove things from your list.