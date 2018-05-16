/* Purpose: show how to  catch multiple signals
 * Author : Sandeep Kumar M
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

/* our signal handlers */

void sig_int (int what)
{
    printf ("We have received SIGINT: Continuing Anyway, Boss.\n");
}
void sig_quit (int what)
{
    printf ("We have received SIGQUIT: Aborting.\n");
    abort ();
}

int main (int argc, char *argv[])
{
    /* Install signal handlers */
    signal (SIGINT, sig_int);   /* for CTRL-C */
    signal (SIGQUIT, sig_quit); /* for CTRL-\ */

    /* Do something pointless, forever */
    for (;;) {
        //printf ("This is a pointless message.\n");
        sleep (1);
    }
    exit (0);
}
