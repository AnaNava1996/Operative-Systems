section .data
	
	msg1 db "El incremento de 4 es: "
	longm1 equ $ - msg1
	msg2 db "El decremento de 4 es: "
	longm2 equ $ - msg2
	msg3 db "La suma de 1 + 2 es: "
	longm3 equ $ - msg3
	msg4 db "La resta de 2 - 1 es: "
	longm4 equ $ - msg4
	line db 0xA
	lline equ $ - line

section .bss
	res resb 1

section .text
	
	
global _start:
	

_start:
	;Imprime el mensaje 1
	mov eax,4
	mov ebx,1
	mov ecx,msg1
	mov edx,longm1
	int 80h
	;inc
	mov eax,4
	inc eax
	;representación ascii
	add eax,'0'
	mov [res],eax
	;impresión inc
	mov eax,4
	mov ebx,1
	mov ecx,res
	mov edx,1
	int 80h
	;imprime nueva línea
	mov eax,4
	mov ebx,1
	mov ecx,line
	;mov edx,lline                                 ;creo que este no hace falta
	int 80h
	
	;Imprime el mensaje 2
	mov eax,4
	mov ebx,1
	mov ecx,msg2
	mov edx,longm2
	int 80h
	;dec
	mov eax,4
	dec eax
	;representación ascii
	add eax,'0'
	mov [res],eax
	;impresión dec
	mov eax,4
	mov ebx,1
	mov ecx,res
	mov edx,1
	int 80h
	;imprime nueva línea
	mov eax,4
	mov ebx,1
	mov ecx,line
	mov edx,lline
	int 80h

	;Imprime el mensaje 3
	mov eax,4
	mov ebx,1
	mov ecx,msg3
	mov edx,longm3
	int 80h
	;add
	mov eax,1
	mov ebx,2
	;representación ascii
	add eax,ebx
	add eax,'0'
	mov [res],eax
	;impresión dec
	mov eax,4
	mov ebx,1
	mov ecx,res
	mov edx,1
	int 80h
	;imprime nueva línea
	mov eax,4
	mov ebx,1
	mov ecx,line
	mov edx,lline
	int 80h
	
	;Imprime el mensaje 4;;;;;;;;;;;;;;;;;;;;;;;;se debe corregir esta parte, es una resta
	mov eax,4
	mov ebx,1
	mov ecx,msg4
	mov edx,longm4
	int 80h
	;add
	mov eax,2
	mov ebx,-1
	;representación ascii
	add eax,ebx
	add eax,'0'
	mov [res],eax
	;impresión dec
	mov eax,4
	mov ebx,1
	mov ecx,res
	mov edx,1
	int 80h
	;imprime nueva línea
	mov eax,4
	mov ebx,1
	mov ecx,line
	mov edx,lline
	int 80h




	;finaliza el programa
	mov eax,1
	mov ebx,0
	int 80h



