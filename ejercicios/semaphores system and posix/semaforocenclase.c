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
void waitS(int s){//entra el semaforo
  operacion.sem_num=s;//se actua en este caso sobre semafor 0 o 1...
  operacion.sem_op=-1;
  operacion.sem_flg=SEM_UNDO;
  semop(semaforo,&operacion,1);
}
/* El proceso que quiera acceder a un recurso común debe primero decrementar el semáforo.
Para ello utilizará la función int semop (int, strcut sembuf *, size_t). El primer parámetro
es el identificador del array de semáforos obtenido con semget(). El segundo parámetro es un
array de operaciones sobre el semáforo. Para decrementarlo, bastará con un array de una única posición.
El tercer parámetro es el número de elementos en el array, es decir, 1.
La estructura del segundo parámetro contiene tres campos:\
    short sem_num que es el índice del array del semáforo sobre el que queremos actuar.
    short sem_op que es el valor en el que queremos decrementar el semáforo. En nuestro caso, -1.
    short sem_flg son flags que afectan a la operación.
*/
void signalS(int s){
  operacion.sem_num=s;
  operacion.sem_op=1;//le sumo
  operacion.sem_flg=SEM_UNDO;
  semop(semaforo,&operacion,1);
}
void * productor(void *argv){
  waitS(0);//wait a si mismo//el cero es del semaforo
  printf("\nParte I hilo: %d",(int)pthread_self());
  for(int i=0;i<10;i++){
    zonacritica[i]=i;}
  signalS(1);//signal al consumidor
  waitS(0);
  printf("\nParte II hilo: %d",(int)pthread_self());
  for(int i=0;i<10;i++){
    zonacritica[i]=9-i;}
  signalS(1);
  pthread_exit(NULL);
}
void * consumidor(void *argv){
  waitS(1);//wait a si mismo
  printf("\nHilo: %d\n",(int)pthread_self());
  for(int i=0;i<10;i++){
    printf("%d",zonacritica[i]);}
  signalS(0);//signal al productor
  waitS(1);//wait a si mismo
  printf("\nHilo ii: %d\n",(int)pthread_self());
  for(int i=0;i<10;i++){
    printf("%d",zonacritica[i]);}
  signalS(0);//signal al productor
  pthread_exit(NULL);
}

int main(){
  pthread_t hilos[4];
  //Creacion hilo
  key_t llave;
  llave=ftok("/bin/ls",0);//llave para ligar a los semaforos
  //1 creacion del semaforo
  //si lo busco el semaforo ya existe... debo destruir el semaforo porque si no ya queda inicializado con valores de antes...
  semaforo=semget(llave,2,IPC_CREAT | 0777);
  //se valida el semaforo en caso de que se cree con error
  if(semaforo==-1)
  {
    printf("Error en el semaforo\n");
    exit(0);
  }
  if((semctl(semaforo,0,SETVAL,1) || semctl(semaforo,1,SETVAL,0))==-1){
    printf("\nerrorcito al inicializar semaforo\n");
    exit(0);
  }
  //Creacion del hilo
  pthread_create(&hilos[0],NULL,productor,NULL);
  pthread_create(&hilos[1],NULL,productor,NULL);
  pthread_create(&hilos[2],NULL,consumidor,NULL);
  pthread_create(&hilos[3],NULL,consumidor,NULL);

  //esperar hilo
  for(int j=0;j<4;j++){
    pthread_join(hilos[j],NULL);
  }
  //matar al semaforo... pero si el programa trono antes desde consola hay que matarlo... o antes del exit(0)
  semctl(semaforo,0,IPC_RMID,0);
  printf("\n");
}
