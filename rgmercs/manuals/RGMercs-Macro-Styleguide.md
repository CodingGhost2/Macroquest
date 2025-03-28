Modes Must be defined with a #define at the beginning of the INC, e.g.,
```
#define MODETANK 0
#define MODEDPS 1
#define MODEHEAL 2
```
etc...

Standard Rotation Names:
```
   |- Rotations
    /call Ordered_Rotation_New ${Me.Class.ShortName}_Debuff_MODENAME_Rotation
    /call Ordered_Rotation_New ${Me.Class.ShortName}_Heal_MODENAME_Rotation
    /call Ordered_Rotation_New ${Me.Class.ShortName}_DPS_MODENAME_Rotation
    /call Ordered_Rotation_New ${Me.Class.ShortName}_Downtime_MODENAME_Rotation
    /call Ordered_Rotation_New ${Me.Class.ShortName}_Burn_MODENAME_Rotation
```