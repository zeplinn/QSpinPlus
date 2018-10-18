#define rand	pan_rand
#define pthread_equal(a,b)	((a)==(b))
#if defined(HAS_CODE) && defined(VERBOSE)
	#ifdef BFS_PAR
		bfs_printf("Pr: %d Tr: %d\n", II, t->forw);
	#else
		cpu_printf("Pr: %d Tr: %d\n", II, t->forw);
	#endif
#endif
	switch (t->forw) {
	default: Uerror("bad forward move");
	case 0:	/* if without executable clauses */
		continue;
	case 1: /* generic 'goto' or 'skip' */
		IfNotBlocked
		_m = 3; goto P999;
	case 2: /* generic 'else' */
		IfNotBlocked
		if (trpt->o_pm&1) continue;
		_m = 3; goto P999;

		 /* PROC P2 */
	case 3: // STATE 1 - simple.pml:19 - [in2 = 1] (0:0:1 - 1)
		IfNotBlocked
		reached[1][1] = 1;
		(trpt+1)->bup.oval = ((int)now.in2);
		now.in2 = 1;
#ifdef VAR_RANGES
		logval("in2", ((int)now.in2));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 4: // STATE 2 - simple.pml:19 - [turn = 1] (0:0:1 - 1)
		IfNotBlocked
		reached[1][2] = 1;
		(trpt+1)->bup.oval = ((int)now.turn);
		now.turn = 1;
#ifdef VAR_RANGES
		logval("turn", ((int)now.turn));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 5: // STATE 3 - simple.pml:20 - [(((in1==0)||(turn==2)))] (0:0:0 - 1)
		IfNotBlocked
		reached[1][3] = 1;
		if (!(((((int)now.in1)==0)||(((int)now.turn)==2))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 6: // STATE 4 - simple.pml:23 - [in2 = 0] (0:0:1 - 1)
		IfNotBlocked
		reached[1][4] = 1;
		(trpt+1)->bup.oval = ((int)now.in2);
		now.in2 = 0;
#ifdef VAR_RANGES
		logval("in2", ((int)now.in2));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 7: // STATE 12 - simple.pml:28 - [-end-] (0:0:0 - 2)
		IfNotBlocked
		reached[1][12] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC P1 */
	case 8: // STATE 1 - simple.pml:7 - [in1 = 1] (0:0:1 - 1)
		IfNotBlocked
		reached[0][1] = 1;
		(trpt+1)->bup.oval = ((int)now.in1);
		now.in1 = 1;
#ifdef VAR_RANGES
		logval("in1", ((int)now.in1));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 9: // STATE 2 - simple.pml:7 - [turn = 2] (0:0:1 - 1)
		IfNotBlocked
		reached[0][2] = 1;
		(trpt+1)->bup.oval = ((int)now.turn);
		now.turn = 2;
#ifdef VAR_RANGES
		logval("turn", ((int)now.turn));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 10: // STATE 3 - simple.pml:8 - [(((in2==0)||(turn==1)))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][3] = 1;
		if (!(((((int)now.in2)==0)||(((int)now.turn)==1))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 11: // STATE 4 - simple.pml:10 - [in1 = 0] (0:0:1 - 1)
		IfNotBlocked
		reached[0][4] = 1;
		(trpt+1)->bup.oval = ((int)now.in1);
		now.in1 = 0;
#ifdef VAR_RANGES
		logval("in1", ((int)now.in1));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 12: // STATE 12 - simple.pml:14 - [-end-] (0:0:0 - 2)
		IfNotBlocked
		reached[0][12] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */
	case  _T5:	/* np_ */
		if (!((!(trpt->o_pm&4) && !(trpt->tau&128))))
			continue;
		/* else fall through */
	case  _T2:	/* true */
		_m = 3; goto P999;
#undef rand
	}

