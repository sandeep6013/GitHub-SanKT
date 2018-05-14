/*
 * FIFO's
 *
 * have your program Create a node using mkfifo or mknod function
 * call. Fork and then have the child stuff a message in the FIFO and
 * have the parent read it and print it out.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define DEATH(mess) { perror(mess); exit(errno); }
#define FIFO_NAME "/tmp/myfifo"

int main( int argc, char *argv[])
{
    char message[] = "Hello World on a FIFO";
    int fd;
    pid_t pid;

    if (mkfifo (FIFO_NAME, 0666) < 0) /* creating pipe using mkfifo function*/
        DEATH (FIFO_NAME);

    printf("FIFO created: %s\n", FIFO_NAME);

    fflush (stdout);
    pid = fork ();

    if (pid == 0)   /* child*/
    {
        fd = open (FIFO_NAME, O_WRONLY);
        printf("The child is sending: %s ***\n", message);

        if (write (fd, message, sizeof (message)) < 0 )
            DEATH("write error from child to fifo");

        close (fd);
        exit( EXIT_SUCCESS );
    }
    else            /* parent */
    {
        fd = open (FIFO_NAME, O_RDONLY);
        if (read (fd, message, sizeof(message)) < 0 )
            DEATH("read error in parent from fifo");

        printf ("The parent received: %s *** \n", message);
        close (fd);

        if (unlink (FIFO_NAME))
            DEATH("Had trouble removing fifo");
        
        exit( EXIT_SUCCESS );
    }

    DEATH ("fork");
}
