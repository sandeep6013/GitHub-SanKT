/* Shows how to use Fork system call 
Version : 1.0
Author : Team -C
In this example, child should acquire the file descriptors table 
                 means even though open is done before fork, the 
                 fd should be avaliable to child 
 */

# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# define CHILD 0

main(){
	int fd;
	char buf[2];
        pid_t pid;	
	int childstatus;
	
	fd = open("./test",O_RDONLY);
	pid = fork();	
//	fd = open("./test",O_RDONLY);
	if( pid == CHILD){
		pread(fd,buf,2,0);
		printf(" in child %c\n",buf[0]);
		printf(" in child %c\n",buf[1]);
		close(fd); // COW
	}
	// parent
	else{
		wait(&childstatus);
		pread(fd,buf,2,0);
		printf(" in parent %c\n",buf[0]);
		printf(" in parent %c\n",buf[1]);
		close(fd);
	}
}
		

