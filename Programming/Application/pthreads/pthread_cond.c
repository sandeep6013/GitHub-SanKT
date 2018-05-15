/* Purpose:	Implementing conditional variables for signaling b/n threads
 * Author : Sandeep Kumar M
 */
/* A condition variable allows one thread to wake another up from a wait. 
 * They work only if there is a thread waiting at the moment when you trigger the condition. 
 * The way to ensure that this is the case is for the waiting thread to lock a mutex which 
 * is linked to the condition, and for the signalling thread to lock that mutex before 
 * triggering the condition. In other words, the signalling thread can only lock the mutex 
 * and trigger the condition if the other thread had the mutex locked but is now waiting.*/

/*The blocked thread can be awakened by a pthread_cond_signal(), a pthread_cond_broadcast(), or when interrupted by delivery of a signal.
 *
 * Any change in the value of a condition associated with the condition variable cannot be inferred by the return of pthread_cond_wait(), 
 * and any such condition must be reevaluated.
 *
 * The pthread_cond_wait() routine always returns with the mutex locked and owned by the calling thread, even when returning an error.
 *
 * This function blocks until the condition is signaled. It atomically releases the associated mutex lock before blocking, 
 * and atomically acquires it again before returning.
 *
 * In typical use, a condition expression is evaluated under the protection of a mutex lock. When the condition expression is false, 
 * the thread blocks on the condition variable. The condition variable is then signaled by another thread when it changes the condition 
 * value. This causes one or all of the threads waiting on the condition to unblock and to try to acquire the mutex lock again.
 *
 * Because the condition can change before an awakened thread returns from pthread_cond_wait(), the condition that caused the wait 
 * must be retested before the mutex lock is acquired
 * The scheduling policy determines the order in which blocked threads are awakened. For SCHED_OTHER, threads are awakened in priority order.
 *
 * When no threads are blocked on the condition variable, calling pthread_cond_signal() has no effect
 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

struct critical_data {        /* Defines "structure" of shared memory */
        int len;
        char buf[MAX_LEN];
}data[2];



typedef struct 
{
	// pthread mutex object
	pthread_mutex_t mutex;
	// pthread conditonal variable 
	pthread_cond_t cond;
	unsigned short conditionMet;
} my_lock_t;

my_lock_t lock = {PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER,0}; 

// Threads created will execute the following routines
 
void * write_thread (void *p)
{
	sleep(5);
	printf("\n In Write thread\n");
	if(lock.conditionMet==0)
	{
		if(pthread_mutex_lock(&lock.mutex)==0)
		{
			printf("\n\t Entering critical section in Write thread \n");
	                strcpy(data[0].buf,"Veda Solutions");
	                data[0].len=strlen("Veda Solutions");
	                strcpy(data[1].buf,"Solutions");
	                //getchar();
	                data[1].len=strlen("Solutions");
			lock.conditionMet = 1;
			pthread_cond_signal(&lock.cond);
			pthread_mutex_unlock(&lock.mutex);
	                printf ("\t Leaving critical section in Write thread\n");
		}
	}
	pthread_exit(NULL);	
}

void * read_thread(void *p)
{
	sleep(1);
       	printf("\n In Read thread \n");
	if(pthread_mutex_lock(&lock.mutex)==0)
	{
		while(lock.conditionMet!=1)
		{
            printf("\nCondition Met\n");
			pthread_cond_wait(&lock.cond,&lock.mutex);
		}
		printf("\n\t Entering critical section in Read thread \n");
                printf("\n\t %d %s \n",data[0].len,data[0].buf);
                printf("\n\t %d %s \n",data[1].len,data[1].buf);
		pthread_mutex_unlock(&lock.mutex);
	}
		
		printf(" Read job is over\n");
        	pthread_exit(NULL);
	
}

int main ()
{
	// Object to hold thread ID
	pthread_t tid1,tid2;
	int rv;
	// Routine shell create a new thread
	rv = pthread_create(&tid1, NULL, write_thread, NULL);
	if(rv)
		puts("Failed to create thread");

	rv = pthread_create(&tid2, NULL, read_thread, NULL);
        if(rv)
                puts("Failed to create thread");

	// suspend execution of the intial thread until the target threads terminates
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	puts(" Exit Main");
	return 0;
}
