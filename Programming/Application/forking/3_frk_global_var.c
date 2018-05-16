/* Purpose: Shows how to use Fork system call, 
 *          with exit status in parent and a change in global variable 
 * Author : Sandeep Kumar M 
 */

# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# define CHILD 0

int global;

main(){
        
    pid_t pid;	
	int childstatus;
	global = 1;
	pid = fork();
	if( pid == CHILD){
		global = 10;
		printf(" in child global %d\n",global);
	}
	// parent
	else{
		wait(&childstatus);
		printf("Child status = %d\n",WEXITSTATUS(childstatus));
		printf(" in parent global %d\n",global);
	}
}
		

