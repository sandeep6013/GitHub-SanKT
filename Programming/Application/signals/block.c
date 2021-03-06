/* Purpose: Usage of signal handlers
 * Author : Sandeep Kumar M
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define DEATH(mess) { perror(mess); exit(errno); }

/* our signal handlers */
void sig_int (int what)
{
    printf ("We have received SIGINT:"
            "Will sleep for 5  seconds and continue\n");
    sleep (20);
    printf (" done sleeping\n");
}

void sig_quit (int what)
{
    printf ("We have received SIGQUIT: Aborting.\n");
    abort ();
}

int main (int argc, char *argv[])
{
    int rc;
    struct sigaction act_quit, act_int;
    sigset_t sigmask;

    memset (&act_quit, 0, sizeof (act_quit));
    memset (&act_int, 0, sizeof (act_int));

    /* set up signal mask to block SIGQUIT during SIGINT */

    rc = sigemptyset (&sigmask);
    printf ("rc = %d from sigemptyset\n", rc);
    rc = sigaddset (&sigmask, SIGQUIT);
    printf ("rc = %d from sigaddset\n", rc);

    /* Install signal handlers */
    act_int.sa_handler = sig_int;
    act_int.sa_mask = sigmask;

    if (sigaction (SIGINT, &act_int, NULL) < 0) /* for CTRL-C */
        DEATH ("sigaction");
    printf ("Successfully installed signal handler for SIGINT\n");

    act_quit.sa_handler = sig_quit;
    if (sigaction (SIGQUIT, &act_quit, NULL) < 0)   /* for CTRL-\ */
        DEATH ("sigaction");

    printf ("Successfully installed signal handler for SIGQUIT\n");

    /* Do something pointless, forever */
    for (;;) {
        printf ("This is a pointless message.\n");
        sleep (1);
    }

    exit (0);
}
