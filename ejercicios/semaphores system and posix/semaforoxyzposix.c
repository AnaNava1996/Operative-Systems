#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

char zonacritica[2][6];

sem_t Semcb[4];

struct sembuf operacion;

void * productor(void * argv){ // 2 - 1
  int *id=(int *)argv; //recasteo el argumento...
  for(int p=0;p<5;p++){
    sem_wait(Semcb[0]);//wait al primer contador //
      sem_wait(Semcb[1]);//waitS(1); //wait al productor    //    no puede pasar nadie hasta que el hilo escoja que zona quiere
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
              sem_post(consumidor);//signalS(3);
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

  if(Semcb==-1){//se valida el semaforo en caso de que se cree con error
    printf("Error en el semaforo\n");
    exit(0);}

//semaforo0 contador, semaforo1 binario productor, semaforo2 binario consumidor, semaforo3 contador?
  if(((Semcb[0]=sem_open("contadorP",O_CREAT,00777,3))||(Semcb[1]=sem_open("productor",O_CREAT,00777,1))||(Semcb[2]=sem_open("consumidor",O_CREAT,00777,1))||(Semcb[3]=sem_open("contadorC",O_CREAT,00777,2)))==SEM_FAILED){
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
