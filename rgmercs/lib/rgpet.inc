| -------------------------------------------------------------------------------------------------
| - Sub: PetAttack - Puller needs to have targetted the mob to attack, or, provide id. If ID
| - provided, use that, in case you want the pet to offtank something while you are on another mob.
| -------------------------------------------------------------------------------------------------
Sub PetAttack(int attackthisid, string FromWhere)

    /if (!PETENGAGE || ${PetAttackOrderTimer}) /return
    /if (!${Target.ID} && !${attackthisid}) /return

    /if (!${attackthisid}) /varset attackthisid ${Target.ID}

    | The wrangler's target
    /declare CurrentTargetID ${Target.ID}
    /if (${CurrentTargetID} != ${attackthisid}) {
        | Change target, if necessary
    }

    /if (${Target.PctHPs} <= ${PetEngagePct[SETTINGVAL]}) {

		/if ((${Pet.Target.ID} != ${attackthisid}) && ${Target.PctHPs} ) {
        	/squelch /pet attack
        	/squelch /pet swarm
			| Mitigate spam. Once attack is given, allow the pet time to change target.
			/varset PetAttackOrderTimer ${PetAttackOrderTime}
		}

    }

    /if (${Target.ID} != ${CurrentTargetID}) {
        | Change wrangler's target back, if necessary
    }

/return