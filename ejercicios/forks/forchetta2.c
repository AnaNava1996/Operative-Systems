//este es mi hola fork... simplemente cree dos hijos para el mismo padre
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


//////////////////////////////////////////
//////////////////////////////////////////


int main()
{
    pid_t pid1, pid2, pid3,pid4,pid5,pid6,pid7,pid8,pid9;
    int status1, status2, status3,status4,status5,status6,status7,status8,status9;
 
    if ( (pid1=fork()) == 0 ){ /* hijo */
        printf("Soy el primer hijo (%d, hijo de %d)\n",  getpid(), getppid());
		if((pid3=fork())==0){
			printf("Soy el primer nieto(%d, hijo de %d)\n",getpid(),getppid());}
		else{if((pid4=fork())==0){
				printf("Soy el segundo nieto (%d, hijo de %d)\n",  getpid(), getppid());}
				else{if((pid5=fork())==0){
					printf("Soy el tercer nieto (%d, hijo de %d)\n",  getpid(), getppid());}
					else{
						waitpid(pid3, &status3, 0);
						waitpid(pid4, &status4, 0);
						waitpid(pid5, &status5, 0);
						printf("Soy el padre (%d, hijo de %d)\n", getpid(), getppid());}}}}
    else{ /*  padre */
        if ( (pid2=fork()) == 0 ){ /* segundo hijo  */
            printf("Soy el segundo hijo (%d, hijo de %d)\n",  getpid(), getppid());
			if((pid6=fork())==0){
			printf("Soy el primer nieto(%d, hijo de %d)\n",getpid(),getppid());}
			else{if((pid7=fork())==0){
					printf("Soy el segundo nieto (%d, hijo de %d)\n",  getpid(), getppid());}
					else{if((pid8=fork())==0){
						printf("Soy el tercer nieto (%d, hijo de %d)\n",  getpid(), getppid());}
						else{if((pid8=fork())==0){
						printf("Soy el tercer nieto (%d, hijo de %d)\n",  getpid(), getppid());}
							else{
								waitpid(pid6, &status6, 0);
								waitpid(pid7, &status7, 0);
								waitpid(pid8, &status8, 0);
								waitpid(pid9, &status9, 0);
								printf("Soy el padre (%d, hijo de %d)\n", getpid(), getppid());}}}}}
        else{
            waitpid(pid1, &status1, 0);
            waitpid(pid2, &status2, 0);
			waitpid(pid3, &status3, 0);
			waitpid(pid4, &status4, 0);
			waitpid(pid5, &status5, 0);
			waitpid(pid3, &status6, 0);
			waitpid(pid4, &status7, 0);
			waitpid(pid5, &status8, 0);
			waitpid(pid9, &status9, 0);
            printf("Soy el padre (%d, hijo de %d)\n", getpid(), getppid());}}
 
    return 0;
}

