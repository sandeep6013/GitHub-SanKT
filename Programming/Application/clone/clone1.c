/* Purpose: This will show you how to create a new process with clone
 * Author : Sandeep Kumar M*/

#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STACK_SIZE 16000

int dosomething(void *arg)
{
	printf("\nIn child process\n");
	getchar();
}

int main()
{
	void *child_stack;
	
    /*get memory for child stack
     * The main use of clone() is to implement threads: multiple threads of control in a program that run concurrently in a shared memory space.
     *
     * When the child process is created with clone(), it executes the function fn(arg). (This differs from fork(2), 
     * where execution continues in the child from the point of the fork(2) call.) 
     * The fn argument is a pointer to a function that is called by the child process at the beginning of its execution. 
     * The arg argument is passed to the fn function.
     *
     * When the fn(arg) function application returns, the child process terminates. 
     * The integer returned by fn is the exit code for the child process. 
     * The child process may also terminate explicitly by calling exit(2) or after receiving a fatal signal.
     *
     * The child_stack argument specifies the location of the stack used by the child process. 
     * Since the child and calling process may share memory, it is not possible for the child process to execute in the 
     * same stack as the calling process. The calling process must therefore set up memory space for the child stack and 
     * pass a pointer to this space to clone(). Stacks grow downward on all processors that run Linux (except the HP PA 
     * processors), so child_stack usually points to the topmost address of the memory space set up for the child stack. 
     */

     child_stack=malloc(STACK_SIZE);
	
    if(child_stack==NULL){
		perror("\nError creating \n");
		exit(1);
	}
	
    /*create new child with clone*/
	clone ( dosomething, child_stack+STACK_SIZE, CLONE_VM|CLONE_FILES, NULL);
	getchar();
	printf("\nIn Parent process\n");
}	
