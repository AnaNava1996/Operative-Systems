section .data
	msg db 0xA,0xD,"introduzca numero: "
	longm equ $ - msg
	line db 0xA
	lline equ $ - line


section .bss
	num resb 1
	res resb 1


section .text
global _start:
_start:

	;imprime linea
	mov eax,4
	mov ebx,2
	mov ecx,line
	mov edx,lline
	int 80h

	;Imprime el mensaje menu
	mov eax,4
	mov ebx,2
	mov ecx,msg
	mov edx,longm
	int 80h

;lee digito :P
mov eax,3
mov ebx,0
mov ecx,[num]                       ;solo se captura
mov edx,2
int 80h


mov rcx,10                          ;se mueve el registro de 10


mifor:
	mov rax,[num]
	sub rax,'0'
	mul rcx                         ;multiplicar ecx con eax
	add rax,'0'
	mov [res],rax		    ;
	int 80h	
	push rcx

	mov rax,4
	mov rbx,1
	mov rcx,res
	mov rdx,1
	int 80h

	pop rcx

loop mifor



mov eax,1
mov ebx,0
int 80h
