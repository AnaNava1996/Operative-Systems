#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <sys/mman.h>

typedef struct{
  char zonacritica[4][3];
}zonacritica;
zonacritica * zonita;
int m,n;
int shm_fd;

sem_t * sem1;
sem_t * sem2;
sem_t * sem3;
sem_t * sem4;
sem_t * sem5;
sem_t * sem6;
sem_t * sem7;
sem_t * sem8;

char ID(int id){
  char llama;
    if(id==1){
      llama='P';
    }
    if(id==2){
      llama='L';
    }
    if(id==3){
      llama='A';
    }
    return llama;
}

char compagnia(int contador){
  char compa;
    if(contador==0){
      compa='A';
    }
    if(contador==1){
      compa='M';
    }
    if(contador==2){
      compa='T';
    }
    return compa;
}

void * productor(void *arg){
  int *id=(int *)arg; //recasteo el argumento...
  int valor;
  for(int i=0;i<n;i++){
    for(int contador=0; contador<3; contador++){
    if(sem_getvalue(sem1,&valor)!=0) perror("error");
      else{
        if(valor>0){
          sem_wait(sem1);
          zonita->zonacritica[0][0]=ID(* id);
          zonita->zonacritica[0][1]='L';
          zonita->zonacritica[0][2]=compagnia(contador);
          sem_post(sem5);}
        else{
          if(sem_getvalue(sem2,&valor)!=0) perror("error");
          else{
            if(valor>0){
              sem_wait(sem2);
              zonita->zonacritica[1][0]=ID(* id);
              zonita->zonacritica[1][1]='L';
              zonita->zonacritica[1][2]=compagnia(contador);
              sem_post(sem6);}
            else{
              if(sem_getvalue(sem3,&valor)!=0) perror("error");
              else{
                if(valor>0){
                  sem_wait(sem3);
                  zonita->zonacritica[2][0]=ID(* id);
                  zonita->zonacritica[2][1]='L';
                  zonita->zonacritica[2][2]=compagnia(contador);
                  sem_post(sem7);}
                else{
                  if(sem_getvalue(sem4,&valor)!=0) perror("error");
                  else{
                    if(valor>0){
                      sem_wait(sem4);
                      zonita->zonacritica[3][0]=ID(* id);
                      zonita->zonacritica[3][1]='L';
                      zonita->zonacritica[3][2]=compagnia(contador);
                      sem_post(sem8);}
                    else{
                      contador--;}
                      }
                    }
                  }
                }
              }
            }
          }}}
}
int main(){
  printf("Valor de n: ");
  scanf("%d",&n);
  printf("\n");
  m=(n*3)/2;
  shm_fd=shm_open("/espacioM",O_CREAT | O_RDWR, 00777);//abre un espacio de memoria compartido
  if(shm_fd==-1){perror("\nerror creando espacio de memoria compartido\n");}
  ftruncate(shm_fd,sizeof(zonacritica));
  zonita = mmap(0,sizeof(zonacritica),PROT_READ | PROT_WRITE,MAP_SHARED,shm_fd,0);
  if((void *)zonita==MAP_FAILED){perror("\nerror mapeando espacio de memoria compartido\n");}

  pthread_t hilos[3];//Creacion hilos

  sem1 = sem_open("sem1", O_CREAT,00777,1);
  sem2 = sem_open("sem2", O_CREAT,00777,1);
  sem3 = sem_open("sem3", O_CREAT,00777,1);
  sem4 = sem_open("sem4", O_CREAT,00777,1);
  sem5 = sem_open("sem5", O_CREAT,00777,0);
  sem6 = sem_open("sem6", O_CREAT,00777,0);
  sem7 = sem_open("sem7", O_CREAT,00777,0);
  sem8 = sem_open("sem8", O_CREAT,00777,0);

  if((sem1==SEM_FAILED)||(sem2==SEM_FAILED)||(sem3==SEM_FAILED)||(sem4==SEM_FAILED)||(sem5==SEM_FAILED)||(sem6==SEM_FAILED)||(sem7==SEM_FAILED)||(sem8==SEM_FAILED)){
	sem_close(sem1);sem_close(sem2);sem_close(sem3);sem_close(sem4);sem_close(sem5);sem_close(sem6);sem_close(sem7);sem_close(sem8);
	sem_unlink("sem1");sem_unlink("sem2");sem_unlink("sem3");sem_unlink("sem4");sem_unlink("sem5");sem_unlink("sem6");
	sem_unlink("sem7");sem_unlink("sem8");
	exit(0);
	}

  int v=1,w=2,x=3;
  pthread_create(&hilos[0],NULL,productor,(void *)&v);
  pthread_create(&hilos[1],NULL,productor,(void *)&w);
  pthread_create(&hilos[2],NULL,productor,(void *)&x);

  //esperar hilo
  for(int j=0;j<3;j++){
    pthread_join(hilos[j],NULL);
  }
  //asesinar al semaforo
  sem_close(sem1);sem_close(sem2);sem_close(sem3);sem_close(sem4);sem_close(sem5);sem_close(sem6);sem_close(sem7);sem_close(sem8);
	sem_unlink("sem1");sem_unlink("sem2");sem_unlink("sem3");sem_unlink("sem4");sem_unlink("sem5");sem_unlink("sem6");
	sem_unlink("sem7");sem_unlink("sem8");
  printf("\n");
  return 0;
}
