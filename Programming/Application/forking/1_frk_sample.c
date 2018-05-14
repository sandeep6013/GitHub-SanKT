/* Purpose: Shows how to use Fork system call 
 * Author : Sandeep Kumar M 
 */

# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>

# define CHILD 0

main(){
    
    pid_t pid;

	printf(" Parent My pid = %d \n", getpid());
	pid = fork();
	printf(" My pid = %d \n", getpid());
	getchar();
	if( pid == CHILD){
        getchar();
		printf(" child: My pid = %d \n", getpid());
		//while(1);
	}
	// parent
	else{
        getchar();
		printf(" My pid = %d \n", getpid());
		printf(" Newly created child pid = %d \n", pid);
		while(1);
	}
}
		

