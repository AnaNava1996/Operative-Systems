//hara lo del forchetta 2 pero recursivo y hasta la 7ma u 8va generacion
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void commies(int,int,int);

int main(){
int i,n,status;
printf("\nn: ");
scanf("%d",&n);
fflush(stdin);
n-=2;
pid_t pid;
printf("Soy el padre (%d, hijo de %d)\n", getpid(), getppid());
for(i=0;i<2;i++){
pid=fork();
if(pid==0){
	if(i==0){//primera iteracion, primogenito
		printf("Soy el primer hijo (%d, hijo de %d)\n",  getpid(), getppid());
		commies(3,n,0);break;}
	else if(i==1){//segunda iteracion, nace el segundo hijo
		printf("\nSoy el segundo hijo (%d, hijo de %d)\n",  getpid(), getppid());
		commies(4,n,0);break;}}
else{
	if(pid>0){//padre, espera al hijo
		if(i==1){
			while(wait(&status)>0);}}
}}
}

void commies(int d,int n,int cont){//d=derecho o izquierdo, n=nivel, contador...
pid_t pid;
int i,status;
if(cont==n){exit(0);}
for(i=0;i<d;i++){
	pid=fork();
	if(pid==0){
		printf("\nSoy %d, hijo de %d\n",  getpid(), getppid());
		commies(d,n,cont+1);break;}
	else{
		if(pid>0){
			if(i==d-1){
				while(wait(&status)>0);}
}}
}}

/*
nivel =0
for(i=0,i<2,i++){
id=fork()
	id==0{
if(i==0){
nivel++
recursiva(nivel,stop,3)}
break;}
else{recuriva(nivel,stop,4)}
else if(i>0){

if(i==1)
while(wait(&status)>0)}
else printf(ERROR);



*/
