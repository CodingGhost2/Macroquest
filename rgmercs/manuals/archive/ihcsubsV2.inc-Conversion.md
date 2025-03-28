# Converting to ihcsubsV2.inc

The 'ihcsubsV2.inc' file is a short-term file name for the reworked IHC core API. This "temporary" file allows for unconverted class macros to continue operating side-by-side with converted macros. Switching to 'ihcsubsV2.inc' will improve the organization of the macro, allow usage of the whole new settings & help system, and allow for easy implementation of new and performant features to make your macro even better!

If you would like to see an example of a converted macro, please refer to `IHCBST.mac` and `ihcbstutil.inc`.

## Steps for conversion
* [ ] Add `#include IHCMercs\ihcsettings.inc` at the top of your .mac
* [ ] Add `#include IHCMercs\ihcsubsV2.inc` at the top of your .mac
* [ ]  `/declare ihcList_<class short name> list outer` in ihc<class short name>util.inc
* [ ] Remove `/call LoadIni Combat StickHow  string behind`
* [ ] Remove `/call LoadIni Combat DoMelee  int 0`
* [ ] Convert the Config Options section to use the new IHCLoadSetting API by replacing `/call LoadIni` with `/call IHCLoadSetting` -- **this requires changing the argument passing format as well. IHCSubsV2.inc, ihcbstutil.inc, and ihcshmutil.inc have examples.
* [ ] For every Config Option changed (**including those in IHCSubsV2.inc**, make sure to find and add [SETTINGVAL] to the end of the variable name. For example, for `${DoHeals}` you now have `${DoHeals[SETTINGVAL]}`
* [ ] Replace `/declare MacroName`, `/declare MacroPath`, `/declare IHCVersion`, and `/declare IniFileName` with `/call IHCInit <shortname> <version>`
* [ ] Change `/call VarSetup` to `/call OuterVarInit` and that OuterVarInit is called before `/call <classhortname>Setup`
* [ ] Change `/call CastSpell` and `/call SpellQueue` to `/call SpellNow`
* [ ] Change `/call DiscQueue` to `/call DiscNow`
* [ ] Remove `/if (${changetoini}==1) /call INIChanges`
* [ ] ~~Replace the following TLOs for DPS/Debuff casting checks with `${DetSpellReady[<spell variable]}`: `SpellReady`, `CurrentMana`, `Type.Equal[Corpse]`, `Me.Casting.ID`, `Target.LineOfSight`, `Cast.Status`. You can look at IHCSHM & IHCBST for examples.~~ Currently triggers an MQ2 Parser crash when used in else /if's. Trying to work with MQ2 folks to find it and fix it.
* [ ] ~~Remove `!Me.Book` TLO checks as they're now in the SpellNow function.~~
* [ ] Remove any binds or aliases related to help and setting value changes from the macro as they will now be done by the new settings API.
* [ ] Change `#turbo 80` to `#turbo 120`
