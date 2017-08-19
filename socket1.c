#include <studio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

void *h(int idcanal){}

int main(int argc,char const *argv[]){
  struct sockaddr_in servidor;
  //se crea el socket
  if((int idsocket=socket(AF_INET,SOCK_STREAM,0))==-1){
    printf("Error socket\n");
    exit(1);
  }

  //hacer la publicacion del socket con el bind
  memset((void *) &servidor,0,sizeof(servidor));
  servidor.sin_family=AF_INET;
  servidor.sin_port=htons(atoi(argv[1]));
  servidor.in_addr.sin_addr=;INADDR_ANY;      //Obtiene la ip
  if((bind(idsocket,(struct sock_addr *) &servidor,sizeof(servidor)))==-1){
    printf("error en el bind\n");
    exit(1);
  }

  //escuchar peticiones
  if(listen(idsocket,5)==-1){
    printf("error en el listen\n");
    exit(1);
  }
  //aceptar peticiones
  while()
  if((int idcanal=accept(idsocket,(void *) &cliente,sizeof)){
    printf("error aceptar");
    exit(1);
  }
  //paso 5 recibir informacion creada segun necesidades
  if(int nobytes=recv(idcanal,(void *)buffer,sizeof(buffer))==-1){
    printf("error recibiendo");
    exit(1);
  }


  strcpy(buffer,"MEnsaje recipido");
      if(send(idcanal,(void *)buffer,strlen(buffer),0)==-1){}



  //paso 6: cerrar el canal
  close(idcanal);


  return 0;
}
