/* Purpose: Program to do matrix multplication using pthreads
 * Author : Sandeep Kumar M
 */

#include <stdio.h>
#include <pthread.h>

#define MAX 2 

int a[MAX][MAX];
int b[MAX][MAX];
int c[MAX][MAX];
int step = 0;

void* multi()
{
    int i, j, k;
    int core = step++;
    for (i = core; i < (core+1) ; i++ ) 
        for ( j = 0; j < MAX; j++ ) 
            for ( k = 0; k < MAX; k++ ) 
                c[i][j] += ( a[i][k] * b[k][j] );
}

int main()
{
    int i, j;

    /* print the matrix */
    printf("MATRIX A\n");
    for ( i = 0; i < MAX ; i++)
    {
        for ( j = 0; j < MAX; j++)
        {
            scanf("%d",&a[i][j]);
        }
    }

    printf("MATRIX B\n");
    for ( i = 0; i < MAX ; i++)
    {
        for ( j = 0; j < MAX; j++)
        {
            scanf("%d",&b[i][j]);
        }
    }

    /* print the matrix */
    printf("MATRIX A\n");
    for ( i = 0; i< MAX ; i++)
    {
        for ( j = 0; j<MAX; j++)
        {
            printf(" %d ",a[i][j]);
        }
        printf("\n");
    }

    printf("MATRIX B\n");
    for ( i = 0; i< MAX ; i++)
    {
        for ( j = 0; j<MAX; j++)
        {
            printf(" %d ",b[i][j]);
        }
        printf("\n");
    }

    /* create threads of final matrix size */

    pthread_t thrd[MAX];

    for ( i = 0; i<MAX; i++ )
    {
        pthread_create(&thrd[i], NULL, &multi, NULL);
    }

    /* syncronize using join */

    for ( i = 0; i<MAX; i++ )
    {
        pthread_join(thrd[i], NULL);
    }
    /* print the final matrix */
    printf("MATRIX C\n");
    for ( i = 0; i< MAX ; i++)
    {
        for ( j = 0; j<MAX; j++)
        {
            printf(" %3d ",c[i][j]);
        }
        printf("\n");
    }
}
