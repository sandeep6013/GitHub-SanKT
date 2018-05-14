/* Purpose: This will show you how to create a new process with clone and share data between processes
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
#define STACK_SIZE  16000

int variable;

int dosomething(void *arg)
{
	printf("\nIn child process\n");
	variable=40;
}

int main()
{
	void *child_stack;
	variable=10;
	printf("\nValue of variable now is %d\n",variable);

    /*get memory for child stack*/
	child_stack=malloc(STACK_SIZE);
	
    if(child_stack==NULL){
		perror("\nError creating \n");
		exit(1);
	}
	
    /*create new child with clone
     * CLONE_VM (since Linux 2.0)
     * If  CLONE_VM is set, the calling process and the child process run in the same memory space.  In particular, memory writes performed
     * by the calling process or by the child process are also visible in the other process.  Moreover, any  memory  mapping  or  unmapping
     * performed with mmap(2) or munmap(2) by the child or calling process also affects the other process.
     *
     * If CLONE_VM is not set, the child process runs in a separate copy of the memory space of the calling process at the time of clone().
     * Memory writes or file mappings/unmappings performed by one of the processes do not affect the other, as with fork(2).
     * 
     * CLONE_FILES (since Linux 2.0)
     * If CLONE_FILES is set, the calling process and the child process share the same file descriptor table.  Any file descriptor  created
     * by the calling process or by the child process is also valid in the other process.  Similarly, if one of the processes closes a file
     * descriptor, or changes its associated flags (using the fcntl(2) F_SETFD operation), the other process is also affected.
     * If CLONE_FILES is not set, the child process inherits a copy of all file descriptors opened in the calling process at  the  time  of
     * clone().   (The duplicated file descriptors in the child refer to the same open file descriptions (see open(2)) as the corresponding
     * file descriptors in the calling process.)  Subsequent operations that open or close file  descriptors,  or  change  file  descriptor
     * flags, performed by either the calling process or the child process do not affect the other process.
     */
	
    clone(dosomething,child_stack+STACK_SIZE,CLONE_VM|CLONE_FILES,NULL);
	
    /* sleep some time so that child can change 'variable' */
	
    sleep(1);
	printf("\n Value of variable now is %d\n",variable);
}


	
	
	
