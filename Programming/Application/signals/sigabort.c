/* Purpose: shows an example of when sigabort will be generated 
 * Author : Sandeep Kumar M
 */
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>

void sighand( int sig_num){
	printf(" abort signal rec'd \n");
	printf(" We can use this to perform clean up op's\n");
}

main(){
	signal(SIGABRT,sighand);
	printf(" some thing has gone worng\n");
	abort();
	printf(" can you see this\n");
}
