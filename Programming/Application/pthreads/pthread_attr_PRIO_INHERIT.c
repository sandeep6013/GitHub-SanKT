/* Purpose: get and set scheduling policies & priority of a thread
 * Author : Sandeep Kumar M
 */


#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;

void *thread1(void *null)
{
	printf("\n In thread1 \n");
	if(pthread_mutex_lock(&mutex)==0)
	{
	    //printf("\n Thread1 lock acquired \n");
	}
	pthread_mutex_unlock(&mutex);
	printf("\n Exit thread1 \n");
	pthread_exit(NULL);
}

void *thread2(void *null)
{
	printf("\n In thread2 \n");
	if(pthread_mutex_lock(&mutex)==0)
	{
	    printf("\n Thread2 lock acquired \n");
		pthread_mutex_unlock(&mutex);
	}
	
	printf("\n Exit thread2 \n");
        pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	pthread_mutexattr_t attrmutex;

	int inherit,policy,priority,rc;
        struct sched_param param;

	pthread_t tid1,tid2,tid3;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
/* --------------------------------------------------------------------------- */
	pthread_mutexattr_init(&attrmutex);
    /* When a thread is blocking higher priority threads because of owning one or 
     * more mutexes with the PTHREAD_PRIO_INHERIT protocol attribute, it shall 
     * execute at the higher of its priority or the priority of the highest priority 
     * thread waiting on any of the mutexes owned by this thread and initialized with this protocol*/
	pthread_mutexattr_setprotocol(&attrmutex,PTHREAD_PRIO_INHERIT);
	pthread_mutex_init(&mutex,&attrmutex);
	//pthread_mutex_init(&mutex,NULL);
/* --------------------------------------------------------------------------- */

	
	// Sets inheritsched attribute 
    /*A useful technique on Linux/Unix systems is changing threads’ scheduling priority. 
     * Linux supports several scheduling policies: SCHED_OTHER, the default scheduling policy, 
     * with round-robin sharing; SCHED_BATCH for batch processing; SCHED_IDLE for extremely 
     * low priority (background) jobs; and the two real-time priority policies SCHED_FIFO and 
     * SCHED_RR for FIFO and round-robin, respectively. In real-time scheduling policies, 
     * threads have a priority from 1 to 99, and higher priority threads always preempt 
     * lower priority threads. The order among waiting threads with the same priority is 
     * determined by the policy (FIFO or round-robin*/

	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
	param.sched_priority=75;
	pthread_setschedparam(pthread_self(),SCHED_FIFO,&param);
	

	param.sched_priority=70;
	pthread_attr_setschedpolicy(&attr,SCHED_RR);
	pthread_attr_setschedparam(&attr,&param);

	pthread_create(&tid1, &attr, thread1, NULL);

	param.sched_priority=90;
        pthread_attr_setschedpolicy(&attr,SCHED_RR);
        pthread_attr_setschedparam(&attr,&param);
	
	pthread_create(&tid2, &attr, thread2, NULL);
	
	rc = pthread_join(tid1,NULL); 	
	rc = pthread_join(tid2,NULL); 	
	
	/* destroy attribute object */
	pthread_attr_destroy(&attr);

	printf("\n Exiting from main Thread\n");
	pthread_exit(NULL);

}


