#include <stdio.h>    //lo mismoq ue el anterior, solo dos hilos y un solo semaforo en lugar de dos
#include <stdlib.h>   //el semaforo binario regula cuando es momento de entrar y cuando no
#include <unistd.h>   //1 se puede entrar 0 nop
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int zonacritica[10];
int semaforo;
struct sembuf operacion; //la estructura ya existe, solo hay que declararla

void waitS(int s){//entra el semaforo
  operacion.sem_num=s;//se actua en este caso sobre semafor 0 o 1...
  operacion.sem_op=-1;
  operacion.sem_flg=SEM_UNDO;
  semop(semaforo,&operacion,1);}

void signalS(int s){
  operacion.sem_num=s;
  operacion.sem_op=1;//le sumo
  operacion.sem_flg=SEM_UNDO;
  semop(semaforo,&operacion,1);}

void * productor(void *argv){
  waitS(0);//wait a productor
  for(int i=0;i<10;i++){
    zonacritica[i]=i;
    printf("Holi");
  }
  signalS(0);//signal al consumidor
  pthread_exit(NULL);}

void * consumidor(void *argv){
  waitS(0);//wait a si mismo
  printf("\n");
  for(int i=0;i<10;i++){
  printf("%d",zonacritica[i]);
  zonacritica[i]=0;}
  signalS(0);//signal al productor
  pthread_exit(NULL);}


int main(){
  pthread_t hilos[2];
  //Creacion hilo
  key_t llave;
  llave=ftok("/bin/ls",0);//llave para ligar a los semaforos
  //creacion del semaforo
  //si lo busco el semaforo ya existe... debo destruir el semaforo porque si no ya queda inicializado con valores de antes...
  semaforo=semget(llave,1,IPC_CREAT | 0777);

  //se valida el semaforo en caso de que se cree con error
  if(semaforo==-1)
    {printf("Error en el semaforo\n");
    exit(0);}
  if((semctl(semaforo,0,SETVAL,1)==-1)){//se inicializa
    printf("\nerrorcito al inicializar semaforo\n");
    exit(0);}

  pthread_create(&hilos[0],NULL,productor,NULL);
  sleep(1);//por si entra el consumidor antes
  pthread_create(&hilos[1],NULL,consumidor,NULL);


  for(int j=0;j<2;j++){//esperar al hilo
    pthread_join(hilos[j],NULL);}

  semctl(semaforo,0,IPC_RMID,0);
}
