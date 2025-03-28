|--------------------------------------------------------------------
|- SUB: InitRGTwist
|--------------------------------------------------------------------
Sub InitRGTwist
    |- Section for bard Instruments
    |- Not aware of a "singing" instrument mod.
    /call RGLoadSetting BRD HornName NULL Options "The name of your Brass Instrument"
    /call RGLoadSetting BRD DrumName NULL Options "The Name of your Percussion Instrument"
    /call RGLoadSetting BRD LuteName NULL Options "The Name of your String Instrument"
    /call RGLoadSetting BRD FluteName NULL Options "The Name of your Wind Instrument"
    /call RGLoadSetting BRD SecondaryName NULL Options "The Name of the default item you want in your Secondary Slot"
    
    /if (${SecondaryName[SETTINGVAL].Equal[NULL]}) {
        /call RGChangeSetting BRD SecondaryName "${Me.Inventory[SWAPSLOT].Name}"
        /echo NOTICE: Did not see item set for SecondaryName. Setting initial default to ${SecondaryName[SETTINGVAL]}
    }
    
    /declare SwapName string outer ${SecondaryName[SETTINGVAL]}
    /declare SwapID int outer ${FindItem[${SwapName}].ID}
    
    |- Exclusion List for Instrument Mods
    /call SetupExcludes
/return
|----------------------------------------------------------------------------
|- SUB: SongNow - Modified Version of SpellNow to accomodate Songs
|- Returns TRUE if Song returns CAST_SUCCESS, FALSE otherwise.
|- CastResult can be checked after return to figure out failure type.
|---------------------------------------------------------------------------- 
Sub SongNow(string nextsong,int nextid)
    |- Don't cast null spells
    /if (${nextsong.Equal[NULL]}) {
        /return FALSE
    }
    
    |- Check for enough mana -- just in case something has changed by this point...
    /if (${Me.CurrentMana}<${Spell[${nextsong}].Mana}) {
        /return FALSE
    }
    
    |- Check we actually have the spell 
    /if (!${Me.Book[${Spell[${nextsong}].RankName}]}) {
        /echo \arTRAGIC ERROR: Somehow I tried to Play a song I didn't know! ${nextsong}
        /return FALSE
    }
    /call ActionPrep
    
    /varset CastResult CAST_NULL
    /if (${Int[${Me.Gem[${Spell[${nextsong}].RankName}]}]}==0 ) {
        /delay 6s !${Me.Casting.ID}
        /call LoadSpellGem "${nextsong}" ${spellmisc}
        /if (!${XAssist.XTFullHaterCount}) {
            |- We can have a gem timer at 0 but still have the spell not ready for higher latency folks. Forcing
            |- this to wait until the spell is ready.
            /while (!${Me.SpellReady[${Spell[${nextsong}].RankName}]}) {  
                /if (${XAssist.XTFullHaterCount}) {
                    /echo I was interruped by combat while waiting to cast ${nextsong}.
                    /break
                }
                /if ( (${Spawn[pc =${FollowToonName[SETTINGVAL]}].Distance} > ${ChaseDistance[SETTINGVAL]}) && ${FollowToonName[SETTINGVAL].NotEqual[NULL]}) {
                    /echo I was interrupted by my chase target running out of range while waiting to cast ${nextsong}.
                    /call FollowToon
                    /break
                }
                TRIGGERBIND
                /if (${DoMed[SETTINGVAL]}) /call AutoMed FROMHERE
                /delay 1
            }   
        }
    }

    /if ( ${Target.ID}!=${nextid} ) /call SetTarget ${nextid}
    |- If we're combat casting we need to both have the same swimming status
    /if (${Target.FeetWet}!=${Me.FeetWet}) {
        /return FALSE
    }

    /call HandleAcverbose "\ag ${nextsong} \ar =>> \ay ${Spawn[ID ${nextid}].Name} \ar <<="

    /call InstrumentSwap "${nextsong}"
    |- If we get here there is no reason we should not be casting our next song
    DEBUG Singing ${nextsong} [${Me.Song[${nextsong}].Duration.Seconds}] with ${Me.Inventory[SWAPSLOT].Name}

    /declare oldduration int local 0
    /if (${nextid} == ${Me.ID}) {
        /varset oldduration ${Me.Song[${nextsong}].Duration.Seconds}
    } else {
        /varset oldduration ${Target.CachedBuff[${nextsong}].Duration.Seconds}
    }

    /cast "${nextsong}"

    |- Wait for the casting window to open to process initial cast result
    /delay 3s ${Window[CastingWindow].Open}

    GET_CAST_RESULT
    /while (${Window[CastingWindow].Open}) {
        /if (DOFOLLOW) /call FollowToon
        /if (DOCAMP) /call AutoCampCheck
        |- Before this can be used there needs to be a check to make sure nextsong isn't a single target mez spell: /if (${Ok2Engage[]}) /call EngageTarget 
        TRIGGERBIND
        /delay 1
    }
    GET_CAST_RESULT
    
    |- wait for client to settle -- simple check to make sure the new song stuck --
    |- predominantly for self-buffs...
    /if (${nextid} == ${Me.ID}) {
        /delay 5s ${Me.Song[${nextsong}].Duration.Seconds} > ${oldduration}
    }
    
    |- Load the misc spell back into its slot before we return.
    /if ( !${Me.Gem[${miscspellremem}]} && ${Me.Gem[${nextsong}]}==${spellmisc} ) {
        /delay 1s !${Me.Casting.ID}
        /call LoadSpellGem "${miscspellremem}" ${spellmisc}        
    }

    /if (${CastResult.Equal[CAST_SUCCESS]}) {
        DEBUG /echo \awNOTICE:\ax Delaying 1s for the client to mellow before stopping my song.
        /delay 1s
        /stopsong
        /return TRUE
    }
    |- ELSE we stop song and return false by default
    /stopsong
/return FALSE

|----------------------------------------------------------------------------
|- SUB: DetSongReady - Makes common checks for detrimental songs
|----------------------------------------------------------------------------
Sub NPCSongReady(string nextsong)
    |DEBUG [${nextsong}] SpellReady ${Me.SpellReady[${Spell[${nextsong}].RankName}]} * Mana ${Me.CurrentMana}>${Spell[${nextsong}].Mana}
    /if ( ${Me.SpellReady[${nextsong}]} && ${Me.CurrentMana}>${Spell[${nextsong}].Mana} ) {
         /if ( !${Me.Casting.ID} && ((!${Target.Type.Equal[Corpse]} && ${Target.LineOfSight} && ${Target.ID}) || ${Spell[${nextsong}].SpellType.NotEqual[Detrimental]}) ) {
            |- DEBUG RETURNING TRUE
            /return TRUE
        }      
    }
/return FALSE
Sub PCSongReady(string nextsong)
    |DEBUG [${nextsong}] SpellReady ${Me.SpellReady[${Spell[${nextsong}].RankName}]} * Mana ${Me.CurrentMana}>${Spell[${nextsong}].Mana}
    /if ( ${Me.CurrentMana}>${Spell[${nextsong}].Mana} && !${Me.Casting.ID}) {
        /return TRUE
    }
/return FALSE
|-----------------------------------------------------------------------------
|- SUB - SetupExcludes - Sets up the list for songs to ignore Instrument swap
|-----------------------------------------------------------------------------
Sub SetupExcludes
    /declare ModExclude list outer
    /invoke ${ModExclude.Insert[0,Requiem of Time]}
    /invoke ${ModExclude.Append[Selo's Rhythm of Speed]}
    /invoke ${ModExclude.Append[Selo`s Assonant Strane]}
    /invoke ${ModExclude.Append[Song of Sustenance]}
    /invoke ${ModExclude.Append[Alenia`s Disenchanting Melody]}
    /invoke ${ModExclude.Append[Wind of Marr]}
/return
|-----------------------------------------------------------------------
|- SUB instrumentSwap - 
|- Pass in the Song name that is about to play
|- This will swap the instrument specified in the ini file to match
|- the songs instrument type. 
|-----------------------------------------------------------------------
Sub InstrumentSwap(string _tmpSongName)
    |- Check to make sure that an instrument was passed in otherwise return
    /if ( ${_tmpSongName.Equal[NULL]} ) {
        DEBUG tmpSongName is null.
        /return FALSE
    }

    |- If the SWAPSLOT does not match what we think 
    |- is the primary weapon then we need to put correct it.
    /if ( ${Me.Inventory[SWAPSLOT].Name.NotEqual[${SwapName}]} && ${FindItem[${SwapName}].ID} ) {
        /squelch /call Exchange "${SwapName}" SWAPSLOT
        /return TRUE
    }
    
    /if ( ${ModExclude.Contains["${_tmpSongName}"]} ) {
        DEBUG Song ${_tmpSongName} on bard swap exclude list
        |- We are getting out of here if we are configured to ignore instrument mods
        /return TRUE
    }

    |- If the primary weapon is in the main hand then it is time to determine which Instrument we need to equip
    /if ( ${Me.Inventory[SWAPSLOT].Name.Equal[${SwapName}]} ) {
        DEBUG Need to swap instruments for skill: ${Spell[${_tmpSongName}].Skill}
        |- We have our multiple Instruments from the ini file
        |- they are each associated with a specific type of song
        /if ( ${Spell[${_tmpSongName}].Skill.Equal[Wind Instruments]} && ${FluteName[SETTINGVAL].NotEqual[NULL]} ) {
            DEBUG BRD Swap: Wind Instrument ==> ${FluteName[SETTINGVAL]}
            /squelch /call Exchange "${FluteName[SETTINGVAL]}" SWAPSLOT
            /return TRUE        
        }
        /if ( ${Spell[${_tmpSongName}].Skill.Equal[Brass Instruments]} && ${HornName[SETTINGVAL].NotEqual[NULL]} ) {
            DEBUG BRD Swap: Brass Instrument ==> ${HornName[SETTINGVAL]}
            /squelch /call Exchange "${HornName[SETTINGVAL]}" SWAPSLOT
            /return TRUE        
        }
        /if ( ${Spell[${_tmpSongName}].Skill.Equal[Stringed Instruments]} && ${LuteName[SETTINGVAL].NotEqual[NULL]} ) {
            DEBUG BRD Swap: Stringed Instrument ==> ${LuteName[SETTINGVAL]}
            /squelch /call Exchange "${LuteName[SETTINGVAL]}" SWAPSLOT
            /return TRUE        
        }
        /if ( ${Spell[${_tmpSongName}].Skill.Equal[Percussion Instruments]} && ${DrumName[SETTINGVAL].NotEqual[NULL]} ) {
            DEBUG BRD Swap: Percussion Instrument ==> ${DrumName[SETTINGVAL]}
            /squelch /call Exchange "${DrumName[SETTINGVAL]}" SWAPSLOT
            /return TRUE        
        }        
    }
/return FALSE
    