#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p = (int *)malloc(sizeof(int));

    pid_t pid;
	int childstatus;
    pid = fork();
    if( pid == 0)
    {
        *p = 25;
        printf("\nChild %d: %d %p\n",getpid(), *p, p);
    }
    else
    {
		wait(&childstatus);
        *p = 15;
        printf("\nParent %d: %d %p\n",getpid(), *p, p);
		printf("Child status = %d\n",WEXITSTATUS(childstatus));
    }
}
