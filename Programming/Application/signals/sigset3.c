
/* Purpose: Appending signals with out using SIG_SETMASK, which clears existing set.
 * Author : Sandeep Kumar M
 */

# include <stdio.h>
# include <signal.h>

void check_blocked_sigs(){
	int i,res;
	sigset_t s;
	sigprocmask(SIG_BLOCK,NULL,&s); //first param is not considered
	for(i =1;i<5;i++){
		res = sigismember(&s,i);
		if(res)
			printf(" signal %d is blocked \n",i);
		else
			printf(" signal %d is not blocked \n",i);
	}
}
main(){
	sigset_t s_set;
	sigemptyset(&s_set);
	sigaddset(&s_set,1);
	sigaddset(&s_set,4);
	sigprocmask(SIG_BLOCK|SIG_SETMASK,&s_set,NULL);
	check_blocked_sigs();
	sigemptyset(&s_set);
	sigaddset(&s_set,2);
    /* set signal 2 as block , which is appended with the existing signals 
     * since SIG_SETMASK is not used in below call, it won't clear the existing blocked list*/
	sigprocmask(SIG_BLOCK,&s_set,NULL);
	check_blocked_sigs();
}
