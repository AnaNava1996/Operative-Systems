//este es mi hola fork... simplemente cree dos hijos para el mismo padre
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
    pid_t pid1, pid2;
    int status1, status2;
 
    if ( (pid1=fork()) == 0 )
    { /* hijo */
        printf("Soy el primer hijo (%d, hijo de %d)\n",  getpid(), getppid());
    }
    else
    { /*  padre */
        if ( (pid2=fork()) == 0 )
        { /* segundo hijo  */
            printf("Soy el segundo hijo (%d, hijo de %d)\n",  getpid(), getppid());
        }
        else
        { /* padre */
/* Esperamos al primer hijo */
            waitpid(pid1, &status1, 0);
/* Esperamos al segundo hijo */
            waitpid(pid2, &status2, 0);
            printf("Soy el padre (%d, hijo de %d)\n", getpid(), getppid());
        }
    }
 
    return 0;
}
