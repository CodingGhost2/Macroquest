
## RGMercs Core Commands
* /rg - Displays the list of available commands in case you forget the order/syntax/style. Also shows version
* /rg help - Displays all available settings that can be changed
* /rg advanced - Displays advanced settings.
* /rg debug clear - Clears the debug log. 
* /rg camphere - Sets your current loc as the camp and turns on return to camp. Does not save the setting to the ini. Only returns to camp when outside AutoCampRadius.
* /rg camphard - Like camphere but you'll return to camp every time after combat.
* /rg campoff - Turns off return to camp. Does not save the setting to the ini.
* /rg chaseon <optional: target name> - Turns on chase. Optional parameter is to provide the name to chase. Currently there are no sanity checks on this.
* /rg chaseoff - Turns off chase mode.
* /rg <setting> - Display the current value of a <setting>. All <setting>s are case sensitive.
* /rg <setting> <value> - Set the value of a <setting>. Saves to INI. All <setting>s are case sensitive. 
* /rg <class shortname> <setting> - Get the current value of a class specific <setting>.  All <setting>s are case sensitive.
* /rg <class shortname> <setting> <value> - Set the current value of a class specific <setting>. Saves to INIT.  All <setting>s are case sensitive.
* /rg on - Turn RG Mainloop On
* /rg off - Turn RG Mainloop Off

## RGmercs Binds
Up to date as of 11-18-2020.

* /aainfo - Spits out how Many unspent AA you have and how much % into current one you are - into mq2 window.
* /addignore - Adds target to pull ignore list
* /addpull - Adds target to the pull only list
* /addwp - Adds your current loc as a waypoint.
* /aebanish
* /autotarget
* /backoffmob - Backs off the currently targeted mob. - Must be ran per toon. Use again to disable backoff mode.
* /banish
* /campfire # - Drops a campfire. # specifies the type of campfire.
* /checkalliance - Check for alliances
* /classmode - Change classmodes without restarting the macro.
* /clearignore - Clear the pull ignore list
* /clearpull - Clear the pull only list
* /clickdoor - Clicks the Nearest Door on Whole Group for example Guildhall Door in lobby to enter.
* /combatreset - Resets Combat kill id and target good for Mobs Not inrange but stuck as priamry target
* /configpull - Reconfigure pull abilities
* /corpserun
* /cureice - Special CLR/SHM binds for manually curing ice.
* /defdisc
* /dropinvis
* /droplev
* /droptravel
* /evadedisc
* /giveitem <item name> <#> <name> - Given item name to name.
* /givemoney <#> <pp/gp/sp/cp> <name> - Given money to name.
* /go2ggh - Determines what zone u are in and Takes action to Get to a Known zone and then run to the GGH Automatically.
* /groupbehindme - Group gathers behind you.
* /groupfrontface - makes everyone face Front same heading as your toon yer on.
* /hotkeys - Special bind to set hotkeys. Bind by itself will show help.
* /hunttarget - Does a single hunt on the currnt target.
* /ihc - Displays help for root RGMercs command interface (see above).
* /kaenform - Moves group to a moon around you with minimal fuss. ( named for its creator)
* /killnow
* /killtarget  - Reassigns this mob as Your Kill target.
* /lazylobbyrez - Works Just like the mac. Just type and you will summon yer corpse in the lobby to be rezzed.
* /lesson
* /levelinfo - Spits out Everyone In groups Current name Level and Exp % towards next level. into the mq2 window
* /makeammo # - Ranger Only. Makes Class 1 Silver arrows used as reagents.
* /navto - This will navto Yourself or to your Target.  For Your entire Group
* /nextwp - Tells Farm mode to move to the next waypoint.
* /port - Special portal behind. Like relocate but you don't need to pause the macro.
* /printlist - Debug bind for printing lists.
* /printmap - Debug bind for printing maps.
* /printrotation - Print the abilities in all your rotations.
* /printset  - Debug bind for printing sets.
* /printspell
* /pullinfo - Displays pullinfo for the current zone
* /pulltarget <spawnid> - Pulls <spawnid> (e.g., /pulltarget ${Target.ID})
* /qsay <text> - Tells all your group members to say <text>
* /randomform <distance> - Randomly places your group around you w/ in square of area `(distance*2)^2`.
* /rg - Displays help for root RGMercs command interface (see above).
* /scribe - Bind of the scribe macro. Scribes spells in inventory and buys spells up to your level from an open merchant window.
* /sheepmove
* /singlehunt - Pulls nearest mob and does not return to start location
* /singlepull - Pulls nearest mob and returns to start location
* /summonmerc
* /summonsnacks <#> - Summon snacks macro in bind form.
* /targroup2xtar - Adds target's group to your xtarget list
* /testisalive
* /wp2tgt - Travels to target but will stop for combat on the way. 
* /yes - this clicks yes on windows. For all Toons in party.

## RGmercs Travel System
The RGMercs Travel System is Limited to travelling to the Grand Guild hall because it is not possible in current mq2 to do this feat Automatically.
- /go2ggh - Determines what zone u are in and Takes action to Get to a Known zone and then run to the GGH Automatically.

## RGmercs Portals
The RGMercs portal system is an alternative to mq2relocate for situations where the Macro may conflict with calls to `/relocate`.
`/port` is the root bind. Each argument provides a portal to a different area:
- /port air
- /port fire
- /port stone
- /port pok
- /port lobby -- use throne of heroes.
- /port guildhall
- /port gorowyn
- /port froststone
- /port stratos
- /port fm
- /port ghlobby -- Click your guild house door if in the guild house or use throne of heroes.
- /port poh
- /port tbm -- use the Broken Mirror.
