/* Purpose: This will show you how to create a new process with clone and share open files  between processes
 * Author : Sandeep Kumar M
 */

#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define STACK_SIZE 16000

int fd;
int dosomething(void *arg)
{
	printf("\nIn child process\n");
	/*close the file */
	close(fd);
}

int main()
{
	int ret;
	void *child_stack;
	char buf[100]={};
	
    fd=open("test.txt",O_RDWR);
	if(fd==-1){
		perror("");
		exit(1);
	}

	/*get memory for child stack*/
	child_stack=malloc(STACK_SIZE);
	if(child_stack==NULL){
		perror("\nError creating \n");
		exit(1);
	}
	/*create new child with clone
     * If CLONE_PARENT is set, then the parent of the new child (as returned by getppid(2)) will  be  the  same  as  that  of  the  calling
     * process.
     * If CLONE_PARENT is not set, then (as with fork(2)) the child's parent is the calling process.
     * Note  that it is the parent process, as returned by getppid(2), which is signaled when the child terminat*/

	clone(dosomething,child_stack+STACK_SIZE,CLONE_VM|CLONE_FILES,NULL);
	
    sleep(2);
	ret=read(fd,buf,100);
	printf("\nret val%d\n",ret);
	if(ret<=0){
		perror("Read error");
		exit(1);
	}
	printf("\nData : %s\n",buf);
}


	
	
	
