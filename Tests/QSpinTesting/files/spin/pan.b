	switch (t->back) {
	default: Uerror("bad return move");
	case  0: goto R999; /* nothing to undo */

		 /* PROC P2 */

	case 3: // STATE 1
		;
		now.in2 = trpt->bup.oval;
		;
		goto R999;

	case 4: // STATE 2
		;
		now.turn = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 6: // STATE 4
		;
		now.in2 = trpt->bup.oval;
		;
		goto R999;

	case 7: // STATE 12
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC P1 */

	case 8: // STATE 1
		;
		now.in1 = trpt->bup.oval;
		;
		goto R999;

	case 9: // STATE 2
		;
		now.turn = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 11: // STATE 4
		;
		now.in1 = trpt->bup.oval;
		;
		goto R999;

	case 12: // STATE 12
		;
		p_restor(II);
		;
		;
		goto R999;
	}

