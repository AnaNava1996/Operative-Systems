#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
  int NFA,NCA,NFB,NCB,num,numa,k,l,i,j,nump,tareas,residuo;
  pid_t pid;
  printf("\numero de filas matriz A: ");
  scanf("%d",&NFA);
  printf("\nnumero de columnas A= numero de filas B: ");
  scanf("%d",&NCA);
  NFB=NCA;
  printf("\nnumero de columnas B: ");
  scanf("%d",&NCB);
  printf("\nnumero de procesos:\n");
  scanf("%d",&nump);
  int matrizA[NFA][NCA];
  int matrizB[NFB][NCB];
  int matrizC[NFA][NCB];


   for (i = 0; i < NFA; i++){//Creo la matriz A
      for (j = 0; j < NCA; j++){
        matrizA[i][j]=1+rand()%(9);
		printf("matrizA[%d][%d]: %d \n",i,j,matrizA[i][j]);}}
   for (i = 0; i < NFB; i++){//Creo la matriz B
      for (j = 0; j < NCB; j++){
        matrizB[i][j]=1+rand()%(9);
		printf("matrizB[%d][%d]: %d \n",i,j,matrizB[i][j]);}}


tareas=NFA/nump;
residuo=NFA%nump;

int (*fd)[2];
fd=malloc(NFA*sizeof(int[2]));
for(i=0;i<NFA;i++){
  pipe(fd[i]);
}
char string[255];
for(i=1;i<=nump;i++){
  pid=fork();
  if(pid==0){
    printf("d: %d h: %d\n",tareas*(i-1),(tareas*i+residuo)-1);
    if(residuo>0 && i==nump){
        char str[255];
      for (l=tareas*(i-1);l<=(tareas*i+residuo)-1;l++){
        str[0]='\0';
        close(fd[l][0]);
        for(j=0;j<NCB;j++){
          num=0;
          for(k=0;k<NFB;k++){
            numa=matrizA[l][k]*matrizB[k][j];
            num+=numa;}
          matrizC[l][j]=num;
          sprintf(str + strlen(str)," %d ",num);}
        write(fd[l][1], str, (strlen(str)+1));
        }
        exit(0);
    }
    else{
      char str[255];
      for (l=tareas*(i-1);l<=(tareas*i)-1;l++){
        close(fd[l][0]);
        str[0]='\0';
        for(j=0;j<NCB;j++){
          num=0;
          for(k=0;k<NFB;k++){
            numa=matrizA[l][k]*matrizB[k][j];
            num+=numa;}
          //matrizC[l][j]=num;
          sprintf(str + strlen(str)," %d ",num);}
        write(fd[l][1], str, (strlen(str)+1));}
      exit(0);}
  }
  else if(pid>0){
    if(i==nump){
    while(wait(NULL)>0);
  }}
  else{
    perror("\nErrorzito: ");}
  }

for(l=0;l<NFA;l++){//voy a LER :v
  close(fd[l][1]);
  read(fd[l][0], string, sizeof(string));
  printf("%s\n",string);
  //close(fd[l][0]);
}
return 0;
}


/*
for (i=0;i<NFA;i++){
  for(j=0;j<NCB;j++){
    num=0;
    for(k=0;k<NFB;k++){
      numa=matrizA[i][k]*matrizB[k][j];
      num+=numa;}
    matrizC[i][j]=num;
    printf("matrizC[%d][%d]: %d \n",i,j,matrizC[i][j]);}}*/
