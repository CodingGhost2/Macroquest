RGMercs pulling is both robust and simple. It requires a zone have a mesh and uses mq2nav. If there is no mesh for a zone, you will not be able to pull. If you have a bad mesh for the zone, you will probably not be pulling well. RGMercs will automatically choose your pulling ability for you (it's RGMercs after all). You can see what ability is being used by looking at `/pullinfo`.

RGMercs has four pull modes:
1. Vanilla - Your basic out and back pulling mode.
2. Hunt - Don't return to camp after attacking your target.
3. Chain - Leave to pull a target before the current fight is over.
4. Farm - Advanced route-based farming mode with custom callback options.

### Restricting Pulling Targets
RGMercs has two different ways to restrict the pulling of targets.

1. Pull-Only List (highest priority): If this list is not empty, RGMercs will _only_ pull mobs that are on this list and will ignore _all other_ mobs in the zone. This is perfect if you only have a few specific types of mobs you are wanting to hunt or pull.

2. Pull-Ignore List (lowest priority): Any mob placed in this list will be ignored when pulling. This is perfect for ignoring peaceful NPCs, chests, or any other targetable entity that you don't want to or can't kill. This list has no effect if the Pull-Only list is not empty.

The Pull-Only and Pull-Ignore lists are reloaded and checked every time the macro attempts to find a pull target so you can modify these lists and see their effects without restarting the macro.

Executing `/pullinfo` will show you your current lists for the current zones.

### Common Settings
* `GroupWatch` and `GroupWatchPct` are leveraged to manage pausing of pulls when your resources are low. They also make sure you don't pull if you're afflicted with a number of negative status conditions or the group is too dispersed across the zone.

* `PullRad`, `PullZRad`, `PullMinLvl`, `PullMaxLvl` -- These help you determine your pulling distance range (based on mq2nav travel distance -- i.e., you'll even pull the nearest mob in dungeons) and pulling level range.

* `DoPetPull` -- You'll want to set this to 1 if you want to pet pull with a pet pulling class.

* At any time you can call `/configpull` to re-initialize the pull ability used after changing a setting.

## Vanilla Pulling
Turn on with `/rg DoPull 1`.

Vanilla pulling is straight forward. You will run out, aggro a mob, and run back to the x,y,z loc you started from. It is strongly suggested you set up camp prior to setting this pull mode.

## Hunt Mode
Turn on with `/rg DoPull 2`.

Hunt mode is also straight forward. This will run out, aggro a mob, and then beat it up in place. You _do not_ return to camp in hunt mode. This is great for having your group follow you (e.g., `/dgge /rg chaseon`) while you run around a zone and beat stuff up.

## Chain Mode
Turn on with `/rg DoPull 3`.

Chain mode is Vanilla pulling but will leave to pull more enemies before the current enemy is dead.

Chain mode requires some additional settings be tuned to your liking:
1. ChainPct - This is the percentage of HP your last xtarget mob will get to before you go out to pull again. The current default is 20 percent.
2. ChainCount - You will pull until your hater count is larger than this number. The current default is 1 so you will pull until you have 2 mobs on your xtarget list.

## Farm Mode
Advanced Pull Mode. This mode runs between pre-defined waypoints and kills enemies near the waypoint. It also provides certain callbacks that can be added to `rgcustom.inc` to allow for quest assistance and other more powerful features. Full write-up specific to this mode in [HOWTO: RG Farm Mode](HOWTO_RGFarmMode)

## Pulling Tricks

### Death and Pulling
Pulling is disabled when you change zones but not disabled when you die. If you do not have rez sickness and return to the zone you started pulling in, you will commence to continue pulling. If you die and want to make sure you do not pull until you want to again, you should turn pulling off: `/rg DoPull 0`. You can always set up an mq2react to do this for you.

### Auto-calculate Pull Levels
Setting `LvlAutoCalc` to 1 will autocalculate levels to be -3 to +3 of your level to maximize XP. Your level range will automatically update as you level.

### Setting a delay between pulls
If you would like to do a temporary delay before the next pull you can use the `/delaypull` bind. This bind takes a #in tenths of seconds (e.g., 10 would be 1 second). This will set a timer at the execution of the bind and will not pull until the timer hits 0.

You can also set the PullDelay setting to a non-zero number. This will delay a certain numbers of tenths of seconds (e.g., `/rg PullDelay 10` would delay 1s between pulls after the mob is dead).

### Stop Pulling When You're Not Alone
One of the powerful things about pulling in RGMercs compared to KA/MA (at the time of this manual) is that you can pause pulling at any time by doing `/rg DoPull 0`. You can use tools such as mq2posse combined with mq2react to automatically pause pulling if another group gets too close to your favorite spot. The mq2react condition would leverage the mq2posse TLOs and the action would set `/rg DoPull 0`. When the group moves away you could have another react that turns it back on.
