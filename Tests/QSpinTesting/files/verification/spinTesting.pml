/* DTU Course 02158 Concurrent Programming
 *   Lab 2
 *   spin4.pml
 *     PROMELA model of modified Share.2 (now correct)
 */

bool c1 = false, c2 = false;
byte incrit = 0;             /* For verification of mutual exlusion */

active proctype P1()
{
	do
	::	skip;  /* Dummy statement to allow label at entry point */

entry:
		do
		::	c1 = !c2;  /* atomic! */
			if 
			:: !c1 -> skip
			::  c1 -> break    /* until c1 */
			fi
		od;
	
crit:		/* Critical section */
		incrit++;
		assert(incrit == 1);
		incrit--;

		c1 = false;

		/* Non-critical section (may or may not terminate) */
		do :: true -> skip :: break od

	od;
}

active proctype P2()
{
	do
	::	skip;  /* Dummy statement to allow label at entry point */

entry:
		do
		::  
			c2 = !c1;  /* atomic! */
			if 
			:: !c2 -> skip
			::  c2 -> break   /* until c2 */
			fi
		od;
	
crit:		/* Critical section */
		incrit++;
		assert(incrit == 1);
		incrit--;
  	
		c2 = false;

		/* Non-critical section (may or may not terminate) */
		do :: true -> skip :: break od

	od;
}

/* Liveness properties (uncomment to verify) */

// ltl obl1  { [] (((P1@entry) && [] (!P2@entry) ) -> <> (P1@crit)) } 
// ltl res   { [] ( (P1@entry || P2@entry) -> <> (P1@crit || P2@crit) ) }
// ltl fair1 { [] ( (P1@entry) -> <>  (P1@crit) ) } 
