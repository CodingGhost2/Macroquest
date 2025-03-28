| ********************************************************
| CALLTRACE is intended for real-time investigation of
| routines which allows one to follow calls throughout
| the macro, along with data you wish to see.
|
| 1) Make this file the first #include
|
| 2) Add these lines right after Sub Main. This sets the
|    defines and trace subs in proper order:
|
|	| Set up the trace call stack. The order is intentional.
|	PUSHCALL
|	CALLINGSUB
|	CALLINGINDEX
| 
| 3) Right before your main loop, add:
|
|   POPCALL
|
| 4) At the very bottom, within the loop add:
|
|   POPCALL
|
| 5) Any errors that occur during execution can be reported as well
|    as the call trace, and other shutdown activities. At the very end
|    of the Main subroutine, prior to the final /return, add:
|
|   :OnExit
|
|        /if (!${MacroQuest.LastCommand.Find[/end]}) {
|            /echo \ay LastCMD:       ${MacroQuest.LastCommand}
|            /echo \ay ErrorDateTime: ${Time.Date} ${Time.Time24}
|            /echo \ay ErrorMsg:      ${MacroQuest.Error}
|            /echo \ay DataError:     ${MacroQuest.MQ2DataError}
|            /echo \ay SyntaxError:   ${MacroQuest.SyntaxError}
|            /echo \ay RunningTime:   ${MacroQuest.Running}
|            /echo \ay BuildDate:     ${MacroQuest.BuildDate}
|            /echo \ay CurrentUI:     ${EverQuest.CurrentUI}
|        }
|
|        /if (${YourDebugFlagVar}) {
|            | Dumps out the stack so you can see the call trace
|            /call Bind_CallStack
|        }
|
|        /if (${Pet.ID} && ${Pet.Stance.NotEqual[follow]}) /pet follow
|
|        | Assuming you use mq2log
|        /mlog off
|
|        /endmacro
|
| 6) At the end of each /call that you want to trace, add FROMHERE. This
|    sets the calling sub name and line number information.
|
|     /call MyMacroSub ... FROMHERE
|
| 7) At the top of the subs you care about, add these lines:
|
|	| Debug call stack
|	CALLINGSUB
|	CALLINGINDEX
|	PUSHCALL
|
| 8) Add 'string FromWhere' to the end of the Sub input variable list
|
|    E.g. Sub MyMacroSub(int this..., string FromWhere)
|
|    Alternatively, you can '/varset FromWhere FROMHERE' in the calling sub.
|
| 9) Now you can use 'CALLTRACE' and provide relevant information.
|    I recommend adding a CALLTRACE at the beginning and end
|    of the sub.
|
|   CALLTRACE Enter from ${FromWhere} :: Your data/note
|
| 10) Prior to each /return, add 'POPCALL'
|
|   CALLTRACE Exit to ${FromWhere} :: Your data/note, ${Macro.Return} for example.
|
|   POPCALL
|   /return
|
| 11) While the macro is running, you can /callstack
|     which will show you where it is running, and the
|     call stack at that moment.
|
| 12) If you see circular calls, you can add the following
|     code to the offending sub, following the code pasted
|     from step 6.
|
|     /if (${CallCircular}) {
|		POPCALL
|		/return
|     }
|
| ********************************************************

| Call trace
#define CURRENTSUB      "${Macro.CurSub.Arg[1,(]}"
#define CALLINGSUB      "/declare CallingSub string local ${CallStack[${CallStackIndex},1]}"
#define CALLINGINDEX    "/declare CallingSubIndex int local ${CallStackIndex}"
#define PUSHCALL        "/call PushCallStack CURRENTSUB"
#define POPCALL         "/varset CallStackIndex ${CallingSubIndex}"
| Calls include the define, and then Subs use a string parameter such as "FromWhere". This allows line tracing.
#define FROMHERE        "${Macro.CurSub.Arg[1,(]}-${Macro.CurLine}"

#define CALLTRACE       "/if (${DebugLog[SETTINGVAL]}==2) /echo \agSub:CURRENTSUB Line:${Macro.CurLine} FromSub:${CallingSub} SubIndex:${CallingSubIndex} Time:${Macro.RunTime} \aw"

| ---------------------------------------------------------------------------
| Sub GetCall
| Helper for debugging. Retrieves the top call from the stack (will be previous sub)
| ---------------------------------------------------------------------------
Sub GetCall
/return ${CallStack[${CallStackIndex},1]}
	
| ---------------------------------------------------------------------------
| Sub PopCallStack
| Helper for debugging. Removes the sub from the stack.
| Usage: /call PopCallStack
| ---------------------------------------------------------------------------
Sub PopCallStack(int CallIndex)
	/while (${CallIndex}>${CallStackIndex}) {
		/varset CallStack[${CallStackIndex},1] NULL
		/varcalc CallStackIndex ${CallStackIndex}-1
	}
/return

| ---------------------------------------------------------------------------
| Sub PushCallStack
| Helper for debugging. Records current sub so next sub can read it.
| Usage: /call PushCallStack CURRENTSUB
| ---------------------------------------------------------------------------
Sub OrigPushCallStack(string SubName)
	/if (${CallStackIndex}==100) {
		/echo CallStack ${SubName} exceeds max stack size 100. Dumping stack and quitting.
		/for iCall 1 to 100
			/echo ${iCall} ${CallStack[${iCall},1]}
		/next iCall
		/endmacro
	}
	/varcalc CallStackIndex ${CallStackIndex}+1
	/varset CallStack[${CallStackIndex},1] ${SubName}
/return

| ---------------------------------------------------------------------------
| Sub PushCallStack
| Helper for debugging. Records current sub so next sub can read it.
| Usage: /call PushCallStack CURRENTSUB
| ---------------------------------------------------------------------------
Sub PushCallStack(string SubName)
	| These have to be defined here because of the boot order
	/if (!${Defined[CallCircular]}) {
		/declare CallCircular           int         outer       0
		/declare CallStack[100,1]	    string	    outer	    null
		/declare CallStackIndex		    int		    outer	    0
		/declare iCall                  int         outer       0
		/declare DisplayStack           int         outer       0
	}
	/if (${CallStackIndex}==100) {
		/echo CallStack ${SubName} exceeds max stack size 100. Dumping stack and quitting.
		/for iCall 1 to 100
			/echo ${iCall} ${CallStack[${iCall},1]}
		/next iCall
		/endmacro
	}
	/varset CallCircular 0
	/for iCall ${CallStackIndex} downto 1
		/if (${CallStack[${iCall},1].Equal[${SubName}]}) {
			/varset CallCircular 1
			/if (${DisplayStack}) {
				/echo \ayDEBUG: Circular call detected: \ar${SubName}
				/call Bind_CallStack
				/delay 1s
			}
		}
	/next iCall
	/varcalc CallStackIndex ${CallStackIndex}+1
	/varset CallStack[${CallStackIndex},1] ${SubName}
/return
