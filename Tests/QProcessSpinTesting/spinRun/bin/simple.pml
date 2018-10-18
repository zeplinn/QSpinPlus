/* Peterson’s solution to the mutual exclusion problem - 1981 */
bool in1, in2 = 0; byte turn = 1;


active proctype P1() {
do
:: in1 = 1; turn = 2;
/*await*/ (in2 == 0 || turn == 1) ->
/* critical section */
in1 = 0;
/* non-critical section */
if :: skip :: break fi
od
}


active proctype P2() {
do
:: in2 = 1; turn = 1;
/*await*/ (in1 == 0 || turn == 2) ->

/* critical section */
in2 = 0;
/* non-critical section */
if :: skip :: break fi
od

}
