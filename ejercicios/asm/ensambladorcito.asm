section .data

	msg1 db "El incremento de 1 es:",0xA,0xD 
	longm1 equ $ - msg1
	msg2 db "El decremento de 1 es:", 0xA,0xD
	longm2 equ $ - msg2
	msg3 db "La suma de 1+2 es:",0xA,0xD 
	longm3 equ $ - msg3
	msg4 db "La resta de 1-2 es:", 0xA,0xD
	loongm4 equ $ - msg4

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;~# nasm -f elf64 archivito.asm`
;~# nasm -f elf64 archivito.asm` -o operacion
;~# ld -m archivito.o -o exect

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .text
	global _start
	_start:
	
;Imprime mensaje 1
	mov eax,4
	mov ebx,1
	mov ecx,msg1
	mov edx,longml                                 ;es el tamagno del mensaje
	int 80h
;inc osea incremento
	mov eax,1  ; prueba con 4 
	inc eax
	;representacion en ascii de eax
	add eax, '0'
	mov [res],eax
;impresion inc
	mov eax,4
	mov ebx,1
	mov ecx,res
	edx	edx,1
	int 80h

	;dec
	move eax,2	
	dec ebx,1

;suma
mov eax,4; para hacer system write o una vaina asi... investigar
mov ebx,1; std out

add eax,ebx
mov eax,'0'

mov[res],eax
;imprime suma



;termina el programa
	mov eax,1
	mov ebx,0
	int 80h

















