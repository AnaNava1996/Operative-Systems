#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(){
  char write_msg[BUFFER_SIZE]="Greetings";
  char read_msg[BUFFER_SIZE];
  int fd[2];
  pid_t pid;

  //create de pipe
  if(pipe(fd)==-1){
    perror("\nError creating pipe: ");
    exit(0);}

  //child process
  pid=fork();

  if(pid<0){
    fprintf(stderr,"Fork Failed");
    return 1;
  }

  if(pid>0){//parent process
    close(fd[READ_END]);//close unused end of the pipe
    write(fd[WRITE_END],write_msg,strlen(write_msg)+1);//escribe en el pipe
    close(fd[WRITE_END]);//cierra el write end del pipe;
  }

  else if(pid==0){//CHILD process
    close(fd[WRITE_END]);//close the unused end of the pipe
    read(fd[READ_END],read_msg,BUFFER_SIZE);//read from the pipe
    printf("\nread %s",read_msg);
    close(fd[READ_END]);//close de read end of the pipe
  }


}
