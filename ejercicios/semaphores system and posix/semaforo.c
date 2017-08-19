#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int zonacritica[10];
int semaforo;

struct sembuf operacion; //la estructura ya existe, solo hay que declararla
void * productor(void *argv){
  waitS(0);//wait a si mismo
  signalS(1);//signal al consumidor
  pthread_exit();
}
void * consumidor(void *argv){
  waitS(1);//wait a si mismo
  signalS(0);//signal al consumidor
  pthread_exit();
}

void waitS(int s){
  operacion.sem_num=s;
  operacion.sem_op=-1;
  operacion.sem_flg=SEM_UNDO;
  semop(semaforo,&operacion,1);
}

void signalS(int s){
  operacion.sem_num=s;
  operacion.sem_op=1;
  operacion.sem_flg=SEM_UNDO;
  semop(semaforo,&operacion,1);
}

int main(){
  pthread_t hilos[2];
  //Creacion hilo
  key_t llave;
  llave=ftok("/bin/ls",0);//llave para ligar a los semaforos
  //1 creacion del semaforo
  //si lo busco el semaforo ya existe... debo destruir el semaforo porque si no ya queda inicializado con valores de antes...
  semaforo=semget(llave,2,IPC_CREAT | 0777);
  //se valida el semaforo en caso de que se cree con error
  if(semaforo==-1)
  {
    printf("Error en el semaforo\n")
    exit(0);
  }
  if((semctl(semaforo,0,SETVAL,1) || semctl(semaforo,1,SETVAL,0))==-1){
    printf("\nerrorcito al inicializar semaforo\n");
    exit(0);
  }
  //Creacion del hilo
  pthread_create(&hilos[0],NULL,productor,NULL);
  pthread_create(&hilos[1],NULL,consumidor,NULL);
  //esperar hilo
  for(int j=0;j<2;j++){
    pthread_join(hilos[j],NULL);
  }
  //matar al semaforo... pero si el programa trono antes desde consola hay que matarlo... o antes del exit(0)
  semctl(semaforo,0,IPC_RMID,0);
}
