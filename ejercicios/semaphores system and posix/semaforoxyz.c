//hacer un semaforo, con dos zonas criticas.

//25x    1---->   | | | |  <-----
//25y    2---->   | | | |  <-----
//25z    3---->            <-----

/*    eficiencia:
  garantizar acceso unico     --->semaforo binario!
  productores quieren entrar cuando las zonas ya estan llenas   ---->
  consumidores quieren entrar cuando no haya datos        ---->
  saber cuando un espacio esta lleno o vacio          ---->
                  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

char zonacritica[2][6];

int Semcb;

struct sembuf operacion;
void waitS(int s){
  operacion.sem_num=s;
  operacion.sem_op=-1;
  operacion.sem_flg=SEM_UNDO;
  semop(Semcb,&operacion,1);}
void signalS(int s){
  operacion.sem_num=s;
  operacion.sem_op=1;
  operacion.sem_flg=SEM_UNDO;
  semop(Semcb,&operacion,1);}

void * productor(void * argv){ // 2 - 1
  int *id=(int *)argv; //recasteo el argumento...
  FILE *archivito;
  archivito = fopen("archivito.txt","a+");
  fprintf(archivito,"\n\nSemaforo XYZ:");
  for(int p=0;p<5;p++){
    printf("\nP %d - %d - %d - %d",semctl(Semcb,0,GETVAL,NULL),semctl(Semcb,1,GETVAL,NULL),semctl(Semcb,2,GETVAL,NULL),semctl(Semcb,3,GETVAL,NULL));
    fprintf(archivito,"\nP %d - %d - %d - %d",semctl(Semcb,0,GETVAL,NULL),semctl(Semcb,1,GETVAL,NULL),semctl(Semcb,2,GETVAL,NULL),semctl(Semcb,3,GETVAL,NULL));
    waitS(0);//wait al primer contador //
    //usleep(100000);
      semctl(Semcb,1,SETVAL,0);//waitS(1); //wait al productor    //    no puede pasar nadie hasta que el hilo escoja que zona quiere
      for(int o=0;o<2;o++){//revisa las zona libres...
        if(zonacritica[o][0]=='v'){
          zonacritica[o][0]='l';  //marca que se esta llenando la zonacritica
          for(int i=1;i<=5;i++){  //asi no se sobreescribe, el problema es el consumidor
            if(*id==1)
              zonacritica[o][i]='x';
            else if(*id==2)
              zonacritica[o][i]='y';
            else if(*id==3)
              zonacritica[o][i]='z';}
              zonacritica[o][0]='e'; // "e" de ya se escribio
              signalS(2);//signalS(3);
              break;}
            else if(o==1 && zonacritica[o][0]!='v'){
              p-=1;
              semctl(Semcb,3,SETVAL,2);
              semctl(Semcb,2,SETVAL,1);}}
          signalS(3);//signalS(2);
          //asi no se traba, tambien se debe activar si ya se escribio (paso por el if)...
              //para el 'else' como el semaforo binario sigue siendo 0, se debe abrir por si ya se leyo alguna vez del consumidor
  }
  fclose(archivito);
  pthread_exit(NULL);}

void * consumidor(void *argv){
  FILE *arch;
  arch=fopen("archivito.txt","a+");
  for(int p=0;p<5;p++){
    printf("\nC %d - %d - %d - %d",semctl(Semcb,0,GETVAL,NULL),semctl(Semcb,1,GETVAL,NULL),semctl(Semcb,2,GETVAL,NULL),semctl(Semcb,3,GETVAL,NULL));
    fprintf(arch,"\nC %d - %d - %d - %d",semctl(Semcb,0,GETVAL,NULL),semctl(Semcb,1,GETVAL,NULL),semctl(Semcb,2,GETVAL,NULL),semctl(Semcb,3,GETVAL,NULL));
    waitS(3);//wait contadorC
    //usleep(100000);
    semctl(Semcb,2,SETVAL,0);//waitS(2);//wait a si mismo, consumidor
    for(int o=0;o<2;o++){
      if(zonacritica[o][0]=='e'){
        printf("\n");
        zonacritica[o][0]='r';
        printf("%c%c%c%c%c",zonacritica[o][1],zonacritica[o][2],zonacritica[o][3],zonacritica[o][4],zonacritica[o][5]);
        fprintf(arch,"\n%c%c%c%c%c",zonacritica[o][1],zonacritica[o][2],zonacritica[o][3],zonacritica[o][4],zonacritica[o][5]);
        zonacritica[o][0]='v';
        signalS(1);//signalS(0)//ya vacie uno, le sumo al primer contador, banquero libre
        break; }
      else if(o==1 && zonacritica[o][0]!='e'){
          p-=1;
          semctl(Semcb,0,SETVAL,2);
          semctl(Semcb,1,SETVAL,1);}}
    signalS(0);//signalS(1)
  }
  fclose(arch);
  pthread_exit(NULL);}

int main(){
  zonacritica[0][0]='v';
  zonacritica[1][0]='v';
  pthread_t hilos[6];//Creacion hilo
  key_t llave;
  llave=ftok("/bin/ls",0);//llave para ligar a los semaforos
  Semcb=semget(llave,4,IPC_CREAT | 0777);//creacion del semaforo

  if(Semcb==-1){//se valida el semaforo en caso de que se cree con error
    printf("Error en el semaforo\n");
    exit(0);}

//semaforo0 contador, semaforo1 binario productor, semaforo2 binario consumidor, semaforo3 contador?
  if((semctl(Semcb,2,SETVAL,3)||semctl(Semcb,1,SETVAL,1)||semctl(Semcb,2,SETVAL,1)||semctl(Semcb,3,SETVAL,2))==-1){
    printf("\nerrorcito al inicializar semaforo\n");
    exit(0);}

int x=1,y=2,z=3;
  pthread_create(&hilos[0],NULL,productor,(void *)&x);
  pthread_create(&hilos[1],NULL,productor,(void *)&y);
  pthread_create(&hilos[2],NULL,productor,(void *)&z);
  usleep(10000);
  pthread_create(&hilos[3],NULL,consumidor,NULL);
  pthread_create(&hilos[4],NULL,consumidor,NULL);
  pthread_create(&hilos[5],NULL,consumidor,NULL);

  //esperar hilo
  for(int j=0;j<6;j++){
    pthread_join(hilos[j],NULL);
  }
  //matar al semaforo... pero si el programa trono antes desde consola hay que matarlo
  printf("\n");
  semctl(Semcb,0,IPC_RMID,0);
}
