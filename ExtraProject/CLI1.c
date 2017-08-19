#include <sys/socket.h>//borrar las partes de servidor, y hacerlo cliente
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int Lectura(int,int,int,char*);

int main(int argc,char * argv[])
{
  if(argc!=4){printf("USO: [cliente] <puerto> <IP servidor> <archivo>\n");exit(1);}
  int socket_id;
  int bytes = 0;
  struct sockaddr_in serv_addr;
  char sendBuff[1025];
  int numrv,id_canal=0;

  /////MEDIR TAMAGNO/////
  int tamagno; // declaro la variable que recibira el tamanio.
  FILE* arch; // declaro un puntero de tipo FILE.
  arch=fopen(argv[3], "rb"); // abro el archivo de solo lectura.
  if(arch==NULL){perror("archivito");exit(1);}
  fseek(arch,0,SEEK_END);            // me ubico en el final del archivo.
  tamagno=ftell(arch);                     // obtengo su tamanio en BYTES.
  rewind(arch);
  fclose(arch);                               // cierro el archivo.

  if((socket_id = socket(AF_INET, SOCK_STREAM, 0))==-1){perror("Socket");exit(1);}

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(atoi(argv[1]));
  serv_addr.sin_addr.s_addr = inet_addr(argv[2]);

  if(connect(socket_id, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)//buscar un socket publicado
    {perror("Connect");exit(1);}
  int * bufbuf = malloc(sizeof(int));
  recv(socket_id,bufbuf,sizeof(int),0);
  printf("%d\n",*bufbuf);
  FILE *fp;
  fp = fopen(argv[3], "rb");
  if(NULL == fp){printf("Error opening file");exit(1);}

  // while((bytes = read(socket_id, recvBuff, 256)) > 0){
  //   fwrite(recvBuff, 1,bytes,fp);}

  if(bytes < 0) perror("Lectura");

  id_canal = accept(socket_id, (struct sockaddr*)NULL ,NULL);

  if(*bufbuf==1){
    Lectura(1,tamagno,id_canal,argv[3]);}
  else
    if(*bufbuf==2){
    Lectura(2,tamagno,id_canal,argv[3]);
    }
    else
    Lectura(3,tamagno,id_canal,argv[3]);




  return 0;
}




int Lectura(int id, int tamagno, int id_canal, char * argv){
  int desde;
  int hasta;
  printf("%d\n",tamagno);
  unsigned char buff[256];
  desde=(tamagno/3)*(id-1);
  hasta=(tamagno/3)*id;
  if(id==3){hasta=tamagno;}
  FILE *fp = fopen(argv,"rb");
  if(fp==NULL){perror("Archivo:");}
  fseek ( fp ,desde, SEEK_SET );
int i=desde;
printf("desde:%d hasta:%d\n",desde,hasta);
  while(i<hasta)
    {
printf("Enviando...\n");
memset(buff, '\0', sizeof(buff));//???
int nread = fread(buff,1,256,fp);// 1 por el tamaño del caracter, 256 caracteres...
if(nread > 0)write(id_canal, buff, nread);
printf("%s\n",buff);
if (nread < 256)
        {
    if (feof(fp))printf("terminado\n");
    if (ferror(fp))printf("Lectura\n");
    break;
        }
i=ftell(fp);

    }

  close(id_canal);

  fclose(fp);
}
