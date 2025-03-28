[What is the rg custom file, what can you do in it?]

## RGCustom_Init
```
Sub RGCustom_Init
    /declare RGCustom_WinTitle string outer
    /varset RGCustom_WinTitle (${Me.CleanName})<Stuff> <More Stuff> <Other Stuff>

    /declare My_Special_Custom_Var string outer 
    /varset My_Special_Custom_Var I will use this later somewhere
/return
```
[Chat Begs in RG Custom]

[Defines for any of your stuff]

## Custom Class Modes
[ Define capabilities ]
[ Define Spell Bar ]
[ If healing: Define Heal Points & Heals]
[ Define rotations ]

## RGCustom_Combat_Routine
[ Custom Combat stuff ]

## Farm_<Zone ShortName>_FullInventory

[ This is called with Farm_${Zone.ShortName}_FullInventory ]

## Custom Binds and Events