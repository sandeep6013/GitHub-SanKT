/* Purpose: How to repetedly call a function using timers for every 5Sec 
 * Author : Sandeep Kumar M
 */

#include <stdio.h>
#include <sys/time.h>

void diff_time (long diff)
{
    printf("\n difference : %ld\n",diff);
}

int main()
{
    struct timeval tv;
    int status = 1;
    long triggertime = 5000;
    long Currenttime, last_triggered, diff ;
    
    gettimeofday(&tv, NULL);
    last_triggered = (tv.tv_sec * 1000)+(tv.tv_usec/1000);
    printf("\n last_triggered value: %ld\n",last_triggered);
    while ( status != 0 )
    {
        gettimeofday(&tv, NULL);
        Currenttime = (tv.tv_sec * 1000)+(tv.tv_usec/1000);
        diff = Currenttime - last_triggered;
        if ( diff >= triggertime ){
            diff_time(diff); 
            gettimeofday(&tv, NULL);
            last_triggered = (tv.tv_sec * 1000)+(tv.tv_usec/1000);
            diff = 0;
        }
    }
    printf("\n Current time : %ld\n",Currenttime);
    printf("\n End of timer \n");
    return 0;
}
