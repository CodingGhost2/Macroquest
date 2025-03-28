|----------------------------------------------------------------------------
|- SUB: RGLoadSetting
|- Setting feld format:
|- [0: INI Section Name, 1: Setting Value, 2: Description of Setting]
|- Requires an IniFileName be initialized, and strListPostfix to be initialized
|- with the name RGList_<some post fix passed to the function>
|-
|- Adds a setting to the macros setting list and then configures default values
|- either based on information loaded from an INI if it exists or values passed to
|- the function
|-
|- strListPostfix - Settings list that holds the value
|- strSetting - Name of the setting
|- strValue - Setting value
|- strSection - INI section to save to
|- strDescription - Help information for the setting
|- bAdvanced - Display only in the advanced menu
|- funcCallback - Function to call when the setting is changed
|----------------------------------------------------------------------------
Sub RGLoadSetting(string strListPostfix, string strSetting, string strValue, string strSection, string strDescription, bool bAdvanced, string funcCallback)

    |- Determine which setting record list to add the new variable
    /declare settingsList string local RGList_${strListPostfix}
    
    |- Don't define the setting if it's already defined
    /if (${Defined[${strSetting}]}) {
        /echo ${strSetting} already loaded: ${${strSetting}[SETTINGVAL]}. Not reloading.
        /return
    }

    |- Declare an array specifically for the added setting then add the setting to our
    |- RGlist record.
    /declare ${strSetting}[5] string outer
    /varset ${strSetting}[INISECTION] ${strSection}
    /varset ${strSetting}[SETTINGDESC] ${strDescription}
    /varset ${strSetting}[ADVANCED] ${bAdvanced}
    /if (${funcCallback.Length} > 0) {
        /varset ${strSetting}[CALLBACK] ${funcCallback}
    } else {
        /varset ${strSetting}[CALLBACK] NULL
    }
   
    |- See if we already have a defined value in our ini
    /declare tmpIniVal string local
    /varset tmpIniVal ${Ini[${IniFileName},${strSection},${strSetting}]}
    
    |- Is our IniVal Null?
    /if (${tmpIniVal.Equal[NULL]}) {
        |- If our IniVal is null, set ini to be our default value
        /ini "${IniFileName}" "${strSection}" "${strSetting}" "${strValue}"
        /varset ${strSetting}[SETTINGVAL] ${strValue}
        /echo \aoDEFAULT: \at${strSetting} \aoSetting To \ag${strValue}
    } else {
        |- If our IniVal is not null, set our program value to the one from the ini
        /varset ${strSetting}[SETTINGVAL] ${tmpIniVal}
        /echo \aoLOAD: \at${strSetting} \aoLoading To \ag${tmpIniVal}
    }
    
    |- Store the arayy in the provided list record of all settings
    /if (!${${settingsList}.Append[${strSetting}]}) {
        /echo \ar FAILED RGLoadSetting -- ADDING TO ${settingsList} -- CLOSING MACRO \ar
    }

    |- Store the setting name in our setting translation map
    /if (!${Map_TransSetting.Add[${strSetting.Lower},${strSetting}]}) {
        /echo \arERROR:\ax Could not add ${settingsList} to translation list.
    }    
    
/return

| ---------------------------------------------------------------------------
| - SUB: StringPad -- Add characters after a string
| ---------------------------------------------------------------------------
Sub StringPad(string Text, int Width, string WithChar)

    /declare NewText  string local ${Text}
    /declare NumChars int    local ${Math.Calc[${Width} - ${Text.Length}]}

    /declare i        int    local 0

    /for i 1 to ${NumChars}
        /varset NewText ${NewText}${WithChar}
    /next i

/return ${NewText}

|----------------------------------------------------------------------------
|- SUB: RGPrintMap -- Loop through the Map and print the value associated with each setting
|----------------------------------------------------------------------------
Sub RGPrintMap(string strListPostfix, int intPrintType, bool printAdvanced)
    
    /declare StringBuffer string local

    |- Declare an iterator and set it to the first element in our settings map
    /declare settingsList string local RGList_${strListPostfix}
    
    /declare listIter listiterator local
    /vardata listIter ${settingsList}.First.Clone
    
    |- Loop through the map until we hit our final element, print out the setting name and its value
    /declare listNode list local
    /invoke ${listNode.Delimiter["DELIM"]}
    
    /while (!${listIter.IsEnd}) {
        /if ( ${intPrintType} == PRINTSETTINGS ) {
            /echo \at ${listIter.Value} \ao Set To \ag${${listIter.Value}[SETTINGVAL]}
        } else /if (${intPrintType} == PRINTADVANCED) {
            /if (${${listIter.Value}[ADVANCED]}) {
                /call StringPad ${listIter.Value} 20 " "
                /varset StringBuffer  \ag ${Macro.Return} \at
                /call StringPad ${${listIter.Value}[SETTINGVAL]} 5 " "
                /varset StringBuffer ${StringBuffer}\aw${Macro.Return}\ay ${${listIter.Value}[SETTINGDESC]}
                /echo ${StringBuffer}
            }
        } else {
            /if (!${${listIter.Value}[ADVANCED]}) {
                /call StringPad ${listIter.Value} 20 " "
                /varset StringBuffer  \ag ${Macro.Return} \at
                /call StringPad ${${listIter.Value}[SETTINGVAL]} 5 " "
                /varset StringBuffer ${StringBuffer}\aw${Macro.Return}\ay ${${listIter.Value}[SETTINGDESC]}
                /echo ${StringBuffer}
            }
        }
        
        |- Move to next element in the map
        /invoke ${listIter.Advance}
    }
/return

Sub RGPrintSettings(string strListPostfix)
    /call RGPrintMap ${strListPostfix} PRINTSETTINGS
/return

Sub RGPrintHelp(string strListPostfix)
    /call RGPrintMap ${strListPostfix} PRINTHELP
/return

Sub RGPrintAdvanced(string strListPostfix)
    /call RGPrintMap ${strListPostfix} PRINTADVANCED
/return

|----------------------------------------------------------------------------
|- SUB: RGPrintSetting -- Print an individual setting
|----------------------------------------------------------------------------
Sub RGPrintSetting(string strListPostfix, string strSetting)
    |- Declare an iterator and set it to the first element in our settings map
    /declare settingsList string local RGList_${strListPostfix}
    /varset strSetting ${strSetting.Lower}

        |- Make sure the setting exists at all...
    /if (!${Map_TransSetting.Contains[${strSetting}]}) {
        /echo \arERROR:\ax Setting ${strSetting} not found.
        /return FALSE
    }

    |- Translate user provided setting to the variable name
    /declare mi mapiterator local
    /vardata mi Map_TransSetting.Find[${strSetting}]
    |- Change our setting to the appropriate capitalization
    /varset strSetting ${mi.Value}

    |- Does the setting exist?
    /if (${${settingsList}.Contains[${strSetting}]}) {
        /echo \ag ${strSetting} \aw -- \ag ${${strSetting}[SETTINGVAL]}
        /return TRUE
    } else {
        /echo Setting ${strSetting} Not Found in category \aw${strListPostfix}\ax.
        /echo Setting names \arARE CASE SENSITIVE
        /return FALSE
    }
/return FALSE

|----------------------------------------------------------------------------
|- SUB: RGChangeSetting - Change an individual setting and save it to the INI
|----------------------------------------------------------------------------
Sub RGChangeSetting(string strListPostfix, string strSetting, string strValue)

    |- Declare an iterator and set it to the first element in our settings map
    /declare settingsList string local RGList_${strListPostfix}
    /varset strSetting ${strSetting.Lower}

    |- Make sure the setting exists at all...
    /if (!${Map_TransSetting.Contains[${strSetting}]}) {
        /echo \arERROR:\ax Setting ${strSetting} not found.
        /return FALSE
    }

    |- Translate user provided setting to the variable name
    /declare mi mapiterator local
    /vardata mi Map_TransSetting.Find[${strSetting}]
    |- Change our setting to the appropriate capitalization
    /varset strSetting ${mi.Value}

    |- parse the strValue for common typos/errors
    /if (${Select[${strValue},"off","no"]}) /varset strValue 0
    /if (${Select[${strValue},"on","yes"]}) /varset strValue 1

    |- Does the setting exist in our list...
    /if (${${settingsList}.Contains[${strSetting}]}) {
        |- Setting exists so lets change it and save to the INI
        /declare oldsetting string local ${${strSetting}[SETTINGVAL]}
        /varset ${strSetting}[SETTINGVAL] ${strValue}
        /ini "${IniFileName}" "${${strSetting}[INISECTION]}" "${strSetting}" "${${strSetting}[SETTINGVAL]}"
        /echo \aoSET: \at${strSetting} \aoTo \ag${strValue} \ao(Old ${oldsetting})
        |- Must always be called after setting the new setting value
        /if (${SubDefined[${${strSetting}[CALLBACK]}]}) {
            /call ${${strSetting}[CALLBACK]}
        }
        /return TRUE
    } else {
        /echo Setting ${strSetting} Not Found in category \aw${strListPostfix}\ax.
        /echo Setting names \arARE CASE SENSITIVE
        /return FALSE
    }
/return FALSE

|----------------------------------------------------------------------------
|- SUB: RGSaveSettings - Save all settings to the INI
|----------------------------------------------------------------------------
Sub RGSaveSettings(string strListPostfix, string strIniFileName)
    |- Declare an iterator and set it to the first element in our settings map
    /declare settingsList string local RGList_${strListPostfix}
    
    /echo \ar RGSaveSettings NOT YET IMPLEMENTED
/return