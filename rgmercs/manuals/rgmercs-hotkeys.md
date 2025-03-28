# RGMercs Hotkeys
If you like creating hotbuttons, we've some suggestions below on hotbbuttons to create. This leverages the `/hotbutton` command from MQ2.

## Movement hotkeys

#### Turning on Chase
If you want your group to chase you:
```
/hotbutton ChaseOn 6 2:0:/dgge /rg chaseon ${Me.Name}
```

#### Turning off Chase
```
/hotbutton Chaseoff 7 2:0:/dgge /rg chaseoff
```
## Toggle hotkeys

#### Toggling Slow on ENC
This hotbutton looks at the current value of DoSlow and will toggle it. A similar pattern can be used with all of the
RGMercs 0/1 toggles. 

**Note: ** settings are case sensitive.
```
/hotbutton TglSlow 7 1:0:/noparse /dex MyEnc ${If[${DoSlow[2]},/rg ENC DoSlow 0,/rg ENC DoSlow 1]}
```