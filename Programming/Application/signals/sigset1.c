/* Purpose: usage of  sigset_t.
 * Author : Sandeep Kumar M
 */

# include <stdio.h>
# include <signal.h>

void sighand(int no){
	printf(" I am in sighandler\n");
}
main(){
    /* create instance of sigset_t */
	sigset_t s_set;
	signal(1,sighand);
    /* empty the sigset before adding in to it */
	sigemptyset(&s_set);
    /* sigaddset to place signal in to set, here 1 and 4 are set*/
	sigaddset(&s_set,1);
	perror("sig1");
	sigaddset(&s_set,4);
	perror("sig4");
    /* sigprocmask to block and mark them as pending, during 
     * which signals if arrived are blocked , when application unblocks
     * them , the they were executed */
	sigprocmask(SIG_BLOCK|SIG_SETMASK,&s_set,NULL);
	perror("sigmask");
	printf(" Send me signal one and see the effect now \n");
	getchar();
	getchar();
    /* to unblock the set */
	sigprocmask(SIG_UNBLOCK,&s_set,NULL);
    /* first handles the pending signals and then continues 
     * pending signals have high priority over regular code */
	printf(" Now signals are unblocked \n");
	while(1);
}
