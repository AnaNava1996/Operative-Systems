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
#include <fcntl.h>

#define BACKLOG 5

struct sockaddr_in conexion_servidor;
pthread_t * hilo;

void * entradas(void * tmp)
{
  char buffer[50];
  int * socket = (int *)tmp;
  while(1)
    {
      buffer[0]='\0';
      recv(*socket,(void *)buffer,sizeof(buffer),O_NONBLOCK);
      printf("%s\n",buffer);
      sleep(1);
    }
}

int main (int argc, char *argv[]){
  char buffer[50];
  //paso 1 Creacion del socket
  int id_socket;
  if(argc!=3)
    {
      printf("Modo de uso: %s <puerto> <ip del servidor>\n",argv[0]);
      exit(1);
    }
	
  if((id_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
      printf("\n error al crear el socket\n");
      exit(1);
    }
  printf("\nSocket creado\n");
  memset((void *)&conexion_servidor,0,sizeof(conexion_servidor));
  conexion_servidor.sin_family=AF_INET; //la misma familia del socket
  conexion_servidor.sin_port=htons(atoi(argv[1])); //transforma el puerto de string a int y  a host
  conexion_servidor.sin_addr.s_addr=inet_addr(argv[2]);



  //paso 2 conectarse al socket
  if(connect(id_socket,
	     (struct sockaddr *)&conexion_servidor,
	     (socklen_t)sizeof(conexion_servidor))==-1)
    {
      printf("\nerror al conectarse al socket\n");
      exit(1);
    }
  //paso 3 enviar informacion
  hilo = (pthread_t *)malloc(sizeof(pthread_t));
  pthread_create(hilo,NULL,entradas,(void *)&id_socket);
  
  printf("\nSe ha conectado con el servidor con socket %d\n\n",id_socket);
  printf("Mi IP: %s\n", inet_ntoa(conexion_servidor.sin_addr));
  while(1){
    memset(buffer,'\0',sizeof(buffer));
    printf("Guest: ");scanf("%[^\n]s",buffer);while(getchar()!='\n');
    if(send(id_socket,(void *)buffer,strlen(buffer),O_NONBLOCK)==-1)
      {
	printf("[error al enviar]\n");
	continue;
      }
    //printf("Mensaje Enviado:%s\n\n",buffer);
    if(strcmp("/q",buffer)==0){
      printf("Desconectado de Socket [%d]\n",id_socket);
      break;
    }
    //paso 4 recibir respuesta
    //int aux = recv(id_socket,(void *)buffer,sizeof(buffer),0);
    //printf("%d\n",aux);
    //if(aux==-1){printf("\nerror al recibir\n");}
    //else printf("%s\n",buffer);
  }
  //paso 5 cerrar el canal
  close(id_socket);
  //free(buffer);
  return 0;
}
