/* Purpose: PThread Creation & Tremination with pthread_exit routine	
 * Author : Sandeep Kumar M
 */

/* Thread created will execute the following routine
 * Thread operations include thread creation, termination, synchronization (joins,blocking), scheduling, data management and process interaction.
 * A thread does not maintain a list of created threads, nor does it know the thread that created it.
 * All threads within a process share the same address space.
 * Threads in the same process share:
 *    Process instructions
 *    Most data
 *    open files (descriptors)
 *    signals and signal handlers
 *    current working directory
 *    User and group id
 * Each thread has a unique:
 *    Thread ID
 *    set of registers, stack pointer
 *    stack for local variables, return addresses
 *    signal mask
 *    priority
 *    Return value: errno
 * pthread functions return "0" if OK.
 */
 
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void * thread_routine (void *p)
{
   printf("\nHello World!\n");
}

int main ()
{
	// Object to hold thread ID
	pthread_t thread;
	int rv,*exit;
	
	// Routine shell create a new thread
	rv = pthread_create(&thread, NULL, thread_routine, NULL);
	if(rv)
		puts("Failed to create thread");

	puts("Exit Main");

	/* Terminate process with exit(0) after termination of all threads 
     * On most modern Linux machines a call to pthread_exit() from the 
     * initial thread does not terminate the entire process until all 
     * threads termination*/
	pthread_exit(NULL);
}
