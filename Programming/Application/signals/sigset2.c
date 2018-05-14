
/* Purpose: usage of  sigset_t, sigprocmask to get info of added signals.
 * Author : Sandeep Kumar M
 */

# include <stdio.h>
# include <signal.h>
/* code is to query PCB ( kernel ) to find which singal are blocked*/
void check_blocked_sigs(){
	int i,res;
	sigset_t s;
    /* previous usage of sigprocmask passes second argument , where as here
     * third argument is passed  which is considered as out param */
	sigprocmask(SIG_BLOCK,NULL,&s); //first param is not considered
	for(i =1;i<5;i++){
        /* sigismember to know whether it is a member of sigset_t or not*/
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
	sigprocmask(SIG_UNBLOCK,&s_set,NULL);
	check_blocked_sigs();
}
