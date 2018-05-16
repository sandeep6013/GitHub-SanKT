/* Purpose: In this example, common memory is created to allow communication 
 *          b/w two process
 * Author : Sandeep Kumar M 
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int fd = -1, size = 4096, status;
    char *area;
    pid_t pid;
    
    /* mmap helps to share a memory region
     * mmap is called with out a file descriptor
     * mmap is called with size, read-write flag and map shared
     * MAP_ANONYMOUS - allow to map a memory but not a file, it invokes a virtual device file to share 
     * here file is not used so fd = -1*/
 
    /* area is a pointer to shared memory and now is avaliable to both child and parent */
    area = mmap( NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, fd, 0);

    pid = fork();
    if(pid == 0)    /* child */
    {
        strcpy(area, "This is a message from the child");
        printf("Child has written: %s\n",area);
        exit(EXIT_SUCCESS);
    }
    else            /* parent */
    {
        wait (&status);
        printf("parent has read : %s\n",area);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}
