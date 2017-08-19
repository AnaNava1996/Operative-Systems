#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BACKLOG 2

struct sockaddr_in servidor;
struct sockaddr_in cliente;

unsigned char globalbuff[BACKLOG][50];

typedef struct threadArg
{
  int * id_canal;
  int id;
} Arg;

sem_t * semctrl;

void * comunicacion(void * argv){
  char buffer[50];
  Arg * arg=(Arg *)argv;
  int no_bytes;
  //paso 5 recibir informacion
  while(1){
    sem_wait(semctrl);
    for(int i=0;i<BACKLOG;i++)
      {
	if(i!=arg->id && globalbuff[i][0]!='\0')
	  {
	    if(send((*arg->id_canal),(void *)globalbuff[i],sizeof(globalbuff[i]),0)==-1)
	      {printf("\nerror al enviar\n");exit(1);}
	    memset(globalbuff[i],'\0',sizeof(globalbuff[i]));
	  }
      }
    sem_post(semctrl);
    printf("La IP: %s El canal: %d\n", inet_ntoa(cliente.sin_addr),(*arg->id_canal));
    if((no_bytes=recv((*arg->id_canal),(void *)buffer,sizeof(buffer),0))==-1){
      printf("error al recibir\n");
      exit(1);
    }
    else{
      buffer[no_bytes]='\0';
      printf("Mensaje Cliente:%s\n",buffer);
      sem_wait(semctrl);
      strcpy(globalbuff[arg->id],buffer);
      sem_post(semctrl);
      //paso 6 enviar respuesta
      if(strcmp("/q",buffer)==0){
	printf("Cerre Canal %d\n\n",(*arg->id_canal));
	break;
      }
      else printf("\n\n");
      
      

      strcpy(buffer,"\t\t\t(OK)");
      if(send((*arg->id_canal),(void *)buffer,sizeof(buffer),0)==-1){printf("\nerror al enviar\n");exit(1);}
    }
  }
  //paso 7 cerrar el canal
  close((*arg->id_canal));
  free(&arg->id_canal);
  return 0;
}


int main (int argc, char *argv[])
{
  pthread_t *hilos;

  semctrl = sem_open("semctrl",O_CREAT,0666,1);
  memset(globalbuff,'\0',sizeof(globalbuff));
  int *id_canal;
  socklen_t longC;
  Arg args[BACKLOG];
  for(int i=0;i<5;i++)args[i].id = i;
  //paso 1 Creacion del socket
  int id_socket;
  if(argc!=2)
    {
      printf("Uso: %s <puerto>\n",argv[0]);
      exit(1);
    }
  if((id_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
      printf("\n error al crear el socket\n");
      exit(1);
    }
  printf("\nSocket creado\n");
  memset((void *)&servidor,0,sizeof(servidor));
  servidor.sin_family=AF_INET; //la misma familia del socket
  servidor.sin_port=htons(atoi(argv[1])); //transforma el puerto de string a int y luego a host
  servidor.sin_addr.s_addr=INADDR_ANY;
  //paso 2 Hacer la publicacion del socket
  if(bind(id_socket,(struct sockaddr *)&servidor,(socklen_t)sizeof(servidor))==-1)
    {
      printf("\nerror al hacer la publicacion del socket\n");
      close(id_socket);
      exit(1);
    }
  printf("\nsocket abierto\n");
  //paso 3 pornerse a escuchar peticiones
  if(listen(id_socket,BACKLOG)==-1) //el 5 esta casi de mas xdxdx
    {
      printf("\nerror al escuchar en socket\n");
      close(id_socket);
      exit(1);
    }
  longC=sizeof(cliente);
  int id = 0;
  //paso 4 aceptar peticion
  while(1)
    {
      printf("\nEsperando al cliente\n");
      id_canal=(int *)malloc(sizeof(int));

      *id_canal=accept(id_socket,(struct sockaddr *)&cliente,&longC);
      if(*id_canal==-1)
	{

	  printf("\nerror al aceptar la peticion\n");
	  close(id_socket);
	  perror("accept");
	  free(id_canal);
	  exit(1);
	}
      else {args[id].id_canal = id_canal;}
      int res = getpeername(*(args->id_canal), (struct sockaddr *)&cliente, &longC);
      printf("RES: %d\n",res );
      char clientip[20];
      strcpy(clientip, inet_ntoa(cliente.sin_addr));

      printf("IP CLIENTE : %s\n",clientip );


      hilos=(pthread_t *) malloc(sizeof(pthread_t));
      pthread_create(hilos,NULL,comunicacion,(void *)&args[id]);
      id +=1;
      free(hilos);
    }
  return 0;
}
