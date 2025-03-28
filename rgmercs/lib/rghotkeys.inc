Sub InitVariables
    /declare IniFileName            string  outer SetSocialKeys.ini
    /declare SetSocialList_Settings list    outer

    /call RGLoadSetting Settings MyInvis     CharName    Hotkeys "Character for group invis"
    /call RGLoadSetting Settings MyUndInvis  CharName    Hotkeys "Character for group undead invis"
    /call RGLoadSetting Settings StartPg     1           Hotkeys "Start social page to clear"
    /call RGLoadSetting Settings EndPg       10          Hotkeys "End social page to clear"
/return

Sub ClearSocials(int startPage, int endPage)
    | Clear all social pages
    /declare totalSocialPgs int local ${endPage}
    /declare socialsPerPage int local 12
    /declare i int local ${startPage}
    /declare j int local 0

    /for i ${startPage} to ${totalSocialPgs}
        /for j 1 to ${socialsPerPage}
            /notify ActionsWindow ASP_SocialButton${j} rightmouseup
            /notify SocialEditWnd SEW_Clear_Button leftmouseup
            /notify SocialEditWnd SEW_Accept_Button leftmouseup
        /next j
        /notify ActionsWindow ASP_SocialPageRightButton leftmouseup
    /next i
/return
|END ClearSocials

Sub Page1
    | ### PAGE 1 ###
    | Page 1 is about 
    |1: Start RGMercs on all characters
    /hotbutton RGStart 14 /dgga /rgstart

    |2: chaseme - makes group chase whom ever gives this command -- handled RG and KA
    /hotbutton StartChase 6 1:0:/dgge /rg chaseon ${Parse[0,${Me.Name}]}

    |3: StopChase - Handles RG & KA or traditional KA w/o specifying person to follow
    /hotbutton StopChase 7 1:0:/dgge /rg chaseoff

    |4: CampHere On
    /hotbutton SetCampOn 2 2:0:/dgga /rg camphere

    |5: Stop Camp
    | Stop camp for both KA and RG
    /hotbutton SetCampOff 4 2:0:/dgga /rg campoff

    |6: Start Pull
    /hotbutton StartPull 5 1:0:/dex ${Parse[0,${Group.Puller.CleanName}]} /docommand /rg DoPull 1

    |7: Start Hunt
    /hotbutton StartHunt 5 1:0:/dex ${Parse[0,${Group.Puller.CleanName}]} /docommand /rg DoPull 2

    |8: Start ChainPull
    /hotbutton StartChain 5 1:0:/dex ${Parse[0,${Group.Puller.CleanName}]} /docommand /rg DoPull 3

    |9: Start Farm
    /hotbutton StartFarm 5 1:0:/dex ${Parse[0,${Group.Puller.CleanName}]} /docommand /rg DoPull 4

    |10: Stop Pull
    /hotbutton StopPull 5 1:0:/dex ${Parse[0,${Group.Puller.CleanName}]} /docommand /rg DoPull 0

    |11: Single Pull Target
    /hotbutton PullTgt 5 1:0:/dex ${Parse[0,${Group.Puller.CleanName}]} /docommand /pulltarget ${Target.ID}

    |12: Single Hunt 
    /hotbutton SingleHunt 5 1:0:/dex ${Parse[0,${Group.Puller.CleanName}]} /docommand /dohunt

/return

Sub Page2
    | ### PAGE 2 ###
    | Group Movement and engagement hotkeys

    | 1: Camp Hard
	/hotbutton HardCampOn 2 2:0:/dgga /rg camphard


    | 2: Yes!
    | Has everyone say Yes to the visibile box
    /hot YES! 10 /dga /yes

    | 3: Switch Target
    /hot SwitchNOW 12 /killtarget

    | 4: StickUW - Stick to me close like we're underwater
    /hot StickUW 8 /dgge /stick id ${Parse[0,${Me.ID}]} 10 uw
    
    | 5: WPToTarget - Nav to target but stop and fight if we get aggro
    /hot WP2Tgt 4 /dgga /wp2tgt ${Parse[0,${Target.ID}]}

    | 6: NavToTarget - Nav to the target I've selected
    /hot Nav2Tgt 4 /dgga /nav id ${Parse[0,${Target.ID}]}

    | 7: Stop Me
    /hot StopMe 13 /squelch /multiline ; /afollow off ; /stick off ; /moveto off ; /nav stop ; /play off

    | 8: Stop Group
    /hot StopGroup 13 /dgga /squelch /multiline ; /afollow off ; /stick off ; /moveto off ; /nav stop ; /play off

    | 9: Stop All
    /hot StopAll 13 /dga /squelch /multiline ; /afollow off ; /stick off ; /moveto off ; /nav stop ; /play off

    | 10: Move2Me - All - Uses mq2advpath -- non-optimal in most situations but could be useful for micro adjustments
    /hot Move2Me 17 /dgge /moveto id ${Parse[0,${Me.ID}]}

    | 11: Nav2Me - All - Uses mq2nav -- preferred
    /hot Nav2Me 18 /dgge /nav id ${Parse[0,${Me.ID}]}

    | 12: NudgeFwd - Moves forward for a second for certain portals or zones where chars don't quite follow -- assumes everyone has come to you.
    /hotbutton NudgeFwd 4 1:0:/dgga /face heading ${Parse[0,${Me.Heading.DegreesCCW}]}
    /hotbutton NudgeFwd 4 2:0:/dgga /keypress forward hold
    /hotbutton NudgeFwd 4 3:0:/dgga /delay 10
    /hotbutton NudgeFwd 4 4:0:/dgga /keypress forward
  
/return

Sub Page3
    | ### PAGE 3 ###
    |
    | Class specific hotkeys and a few more utility keys

    | 1: Toggle Burns

    | 2: COTH ME - Tell your mage to cast call of the hero on you

    | 3: InvisUs - Tell your LVL76 wizard, enchanter, or magician to invis you -- requires group perfected invisibility
    /hotbutton InvisUs 12 1:0:/dgga /rg off
    /hotbutton InvisUs 12 2:0:${If[${MyInvis[SETTINGVAL].NotEqual[${Me.CleanName}]},/dex ${MyInvis[SETTINGVAL]},]} /alt act 1210
    /hotbutton InvisUs 12 3:0:${If[${MyUndInvis[SETTINGVAL].NotEqual[${Me.CleanName}]},/dex ${MyUndInvis[SETTINGVAL]},]} /alt act 1212
    /hotbutton InvisUs 12 4:0:/timed 20 /dgga /rg on

    | 4: Remove Invis
    /hotbutton RemInvis 12 1:0:/dgga /makemevisible

    | 5: Remove All Travel Buffs
    
    | 6: Bard: Enter travel mode for lower level bards
    /hotbutton BrdTravel 12 1:0:/noparse /dgga /docommand ${Parse[0,/if (${Me.Class.ShortName.Equal[BRD]}) /rg off]}
    /hotbutton BrdTravel 12 2:0:/noparse /dgga /docommand ${Parse[0,/if (${Me.Class.ShortName.Equal[BRD]}) /melody ${Me.Gem[Selo's Song of Travel]}]}
    
    | 7: HideCorpses - If you need to hide corpses
    /hot HideCorpses 18 /dgga /hidecorpse NPC
    
    | 8:  Click Door
	/hotbutton DoorClick 18 1:0:/dgga /doortarget
	/hotbutton DoorClick 18 2:0:/timed 5 /dgga /click left door

    | 9: RogEscapeCmb - Routine for when manually playing your rogue to leave combat, hide, pickepocket, backstab, and re-enter combat.

    | 11: 

    | 12: 
/return

Sub Page4
    | ### PAGE 4 ###
    |
    | Autoloot hot keys 1-9 presume you have an item on your cursor

    | 1 
    /hot AutoIKeep 12 /SetItem Keep
    
    | 2
    /hot AutoIIgnore 14 /SetItem Ignore

    | 3
    /hot AutoIBarter 2 /SetItem Barter ${If[${Math.Calc[${Cursor.Value}/1000].Int} < 1,1,${Math.Calc[(${Cursor.Value}/1000)+1].Int}]}

    | 4
    /hot AutoISell 2 /SetItem Sell

    | 5
    /hot AutoIDeposit 2 /SetItem Deposit

    | 6
    /hot AutoIDestroy 13 /SetItem Destroy

    | 7
    /hot !DeleteItem! 13 /destroy

    | 8
    /hot AutoIQuest 16 /SetItem Quest 1

    | 9
    /hot AutoIGear 15 /SetItem Gear 
    
    | 10 Click Left On Target -- Useful for quickly trading items on the cursor
    /hot ClickLeft 10 /click left target
    
    | 11 Group Sell -- have your group select your target, open the merchant, and use mq2autoloot to sell.
    /hotbutton GroupSell 4 1:0:/dgge /target id ${Parse[0,${Target.ID}]}
    /hotbutton GroupSell 4 2:0:/timed 5 /dgga /click right target
    /hotbutton GroupSell 4 3:0:/timed 10 /dgga /autoloot sell
    
	| 12 Donate Click -- Optimal for quickly clicking the tribute donate button
	/hotbutton Donate 4 1:0:/notify TributeMasterWnd TMW_DonateButton leftmouseup
	
    | 12 
    | if (${GroundItemCount} && ${Ground[1].Distance} <= 20) /multiline ; /itemtarget ${Ground[1]}; /click left item;
    | /if (${GroundItemCount} && ${Ground[1].Distance} > 20) /multiline ; /itemtarget ${Ground[1]}; /face item; /echo move ${Ground[1].Distance} feet;
    
/return

Sub Page5   
    | ### Page 5 ###

/return

Sub Page6
    | #### Page 6 ###
    |

    | 1 - Run RGMercs install on all your characters
    /hot InstallRGM 4 /multiline ; /noparse /dgge ${Parse[0,/if (${StartSelect}${RGClasses[SETTINGVAL]}${EndSelect}) /mac RGinstall ; /mac RGinstall
    
    | 2 Last Mouse Over
    /hot Mouseover 4 /echo ${EverQuest.LastMouseOver}
    | 3 
    | 4 
    | 5 - 
    | 6 - 
    | 7 - 
    | 8 - RUNAWAY hotkey -- Pauses all macros and tells the group to follow you.
    
    | 9 - KAAbortPull-- Aborts a KA pull and returns to camp
    
    | 10 - PAUSE all macros - resume on the second push
    /hot PAUSE_TGL 7 /dgga /mqp
    
    | 11 Group Give
    /hotbutton GroupGive 4 1:0:/multiline ; /dgga /target id ${Parse[0,${Target.ID}]} ;
    /hotbutton GroupGive 4 2:0:/multiline ; /timed 5 /dgge /itemnotify "${Parse[0,${Cursor.Name}]}" leftmouseup
    /hotbutton GroupGive 4 3:0:/multiline ; /timed 10 /dgga /click left target
    /hotbutton GroupGive 4 4:0:/multiline ; /timed 15 /dgga /yes
    
    | 12 Group Sell -- Has group open up your current merchant and use autoloot sell
/return 

Sub Page7
    /echo PAGE7 NOT YET USED
/return

Sub Page8
    /echo PAGE8 NOT YET USED
/return

Sub Page9
    /echo PAGE9 NOT YET USED
/return

Sub Page10
    /echo PAGE10 NOT YET USED
/return

|-----------------------------------------------------------------------------
|- Sub: Bind_rgmk - Bind that handles settings changes across the
|- Macro suite
|-----------------------------------------------------------------------------
#bind rgmk /hotkeys
Sub Bind_rgmk(string setting_noun, string setting_value, string value)
    |- User provided no setting/noun so display command usage
    /if (${setting_noun.Length} == 0) {
        /goto :USAGEERROR
    }
	
	/if (${Group.Puller.CleanName.Equal[NULL]}) /goto :USAGEERROR
	/if (${Group.MainAssist.CleanName.Equal[NULL]}) /goto :USAGEERROR
    
    /if (${setting_noun.Equal[setgroup]}) {
        /if (${setting_value.Length} == 0) /goto :USAGEERROR
        /call Page${setting_value}
        /return
    } else /if (${setting_noun.Equal[clearpage]}) {
        /if (${setting_value.Length} == 0) /goto :USAGEERROR
        /call ClearSocials ${setting_value}
        /return
    } else /if (${setting_noun.Equal[setall]}) {
        |- Clear all current social pages
        /call ClearSocials ${HotkeyStartPg[SETTINGVAL]} ${HotkeyEndPg[SETTINGVAL]}
        |- Write all our SocialKeys
        /declare cnt int local
        /for cnt ${HotkeyStartPg[SETTINGVAL]} to ${HotkeyEndPg[SETTINGVAL]}
            /call Page${cnt}
        /next cnt
        /return
    }
    
    :USAGEERROR
        /echo \ag/hotkeys USAGE:\ax
        /echo Requires group MainAssist, Tank, and Puller roles are set.
        /echo RGMKeys command arguments:
        /echo \ag/hotkeys setgroup #\ao- Sets hotkey page based on #. Valid # are 1 - 10.
        /echo \ag/hotkeys clearpage #\ao- Clears hotkey page based on #. Valid # are 1 - 10.
        /echo \ag/hotkeys setall \ao- Clears and sets all hotkeys based on StartPg and EndPg settings. Defaults to 1 - 10.
/return