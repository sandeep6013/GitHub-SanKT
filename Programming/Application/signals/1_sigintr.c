
/* Purpose: show how to  catch interrupt signal.
 * Author : Sandeep Kumar M
 */

# include <stdio.h>
# include <signal.h>

void sighand(int signum){
	printf("Interrupt signal rec'd \n");
}

main(){
	signal(SIGINT,sighand);
	while(1){
	}
}
