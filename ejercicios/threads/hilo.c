#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

typedef struct matricita
{
  int ini,fin;}mt;

void *multiplicacion(void* arg);

int **matrizA;
int **matrizB;
int **matrizC;
int NFA,NCA,NFB,NCB;

int main(void)
{
  int num,numa,i,j,k,l,nump,tareas,residuo;
  pid_t pid;
  printf("\nnumero de filas matriz A: ");
  scanf("%d",&NFA);
  printf("\nnumero de columnas A= numero de filas B: ");
  scanf("%d",&NCA);
  NFB=NCA;
  printf("\nnumero de columnas B: ");
  scanf("%d",&NCB);
  printf("\nnumero de procesos/hilos:\n");
  scanf("%d",&nump);
  tareas=NFA/nump;
  residuo=NFA%nump;

  matrizA=malloc(NFA*sizeof(int*));//al numero de filas le doy un numero indeterminado de espacios
    for(i=0;i<NFA;i++){//a cada fila, le doy
      matrizA[i]=malloc(NCA*sizeof(int));//el numero de columnas que es
    }
  matrizB=malloc(NFB*sizeof(int*));//al numero de filas le doy un numero indeterminado de espacios
    for(i=0;i<NFB;i++){//a cada fila, le doy
      matrizB[i]=malloc(NCB*sizeof(int));//el numero de columnas que es
    }
  matrizC=malloc(NFA*sizeof(int*));//al numero de filas le doy un numero indeterminado de espacios
    for(i=0;i<NFA;i++){//a cada fila, le doy
      matrizC[i]=malloc(NCB*sizeof(int));//el numero de columnas que es
    }

     for (i = 0; i < NFA; i++){//lleno la matriz A
        for (j = 0; j < NCA; j++){
          matrizA[i][j]=1+rand()%(9);
  		printf("matrizA[%d][%d]: %d \n",i,j,matrizA[i][j]);}}
     for (i = 0; i < NFB; i++){//lleno la matriz B
        for (j = 0; j < NCB; j++){
          matrizB[i][j]=1+rand()%(9);
  		printf("matrizB[%d][%d]: %d \n",i,j,matrizB[i][j]);}}

pthread_t hilo[nump];
mt arre[nump]; //arreglo de structs

for(i=1;i<=nump;i++){
if(residuo>0 && i==nump){
  arre[i-1].ini =tareas*(i-1);
  arre[i-1].fin =(tareas*i+residuo)-1;}
else{
  arre[i-1].ini =tareas*(i-1);
  arre[i-1].fin =(tareas*i)-1;}
pthread_create(&hilo[i-1],NULL,multiplicacion,(void*)&arre[i-1]);//castearlo como void
}
for(l=0;l<nump;l++){
  pthread_join(hilo[l],NULL);}
}


void *multiplicacion(void * arg){
mt * arre = (mt *) arg;
for (int l=arre->ini;l<=arre->fin;l++){
  for(int j=0;j<NCB;j++){
    int numa=0;
    for(int k=0;k<NFB;k++){
      numa+=(matrizA[l][k]*matrizB[k][j]);}
    matrizC[l][j]=numa;
    printf("matrizC[%d][%d]=%d\n",l,j,numa);
}}}
