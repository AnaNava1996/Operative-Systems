section .data                           ;USANDO JMP

	msg db "Elija opcion 1 incremento, 2 decremento, 3 Suma, 4 Resta, 5 Muli, 6 Mul, 7 Divi, 8 Div, 9 salir: "
	longm equ $ - msg
	msg1 db "El incremento de 4 es: "
	longm1 equ $ - msg1
	msg2 db "El decremento de 4 es: "
	longm2 equ $ - msg2
	msg3 db "La suma de 1 + 2 es: "
	longm3 equ $ - msg3
	msg4 db "La resta de 2 - 1 es: "
	longm4 equ $ - msg4
	msg11 db "2 por 3 es: "
	longm11 equ $ - msg11
	msg33 db "9 entre 3 es: "
	longm22 equ $ - msg22
	msg22 db "2 por -3 es: "
	longm33 equ $ - msg33
	msg44 db "9 entre -3 es: "
	longm44 equ $ - msg44
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

	;lee la opcion
	mov eax,3                 		;system read.... 4 es para write, 3 para leer... 1 para salir
	mov ebx,0                 		;stdin
	mov ecx,num   	               	;numero a leer
	mov edx,2						;tamano(imprimir)
	int 80h


mov al,[num]

    ;Es 1
    mov ah,"1"
    cmp byte al , ah
    je incremento
    ;Es 2
    mov ah,"2"
    cmp byte al , ah
    je decremento
    ;Es 3
    mov ah,"3"
    cmp byte al , ah
    je suma
    ;Es 4
    mov ah,"4"
    cmp byte al , ah
    je resta
    ;Es 5
    mov ah,"5"
    cmp byte al , ah
    je Mul
    ;Es 6
    mov ah,"6"
    cmp byte al , ah
    je Muli
    ;Es 7
    mov ah,"7"
    cmp byte al , ah
    je Div
    ;Es 8
    mov ah,"8"
    cmp byte al , ah
    je Divi
	;Es 9
	mov ah,"9"
	cmp byte al, ah
	je Fin


	incremento:
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
		jmp _start
	decremento:
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
		jmp _start
	suma:
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
		jmp _start
	resta:
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
		jmp _start


	Mul:
		mov eax,4                 		;system write
		mov ebx,2                 		;stdout 
		mov ecx,msg11                  	;imprimir
		mov edx,longm11					;tamano(imprimir)
		int 80h
		;mul
		mov al,2
		mov bl,3
		mul bl
		;representación ascii
		add ax,'0'
		mov [res],eax
		;impresión dec
		mov eax,4
		mov ebx,1
		mov ecx,res
		mov edx,1
		int 80h
		jmp _start
	Muli:
		mov eax,4
		mov ebx,2
		mov ecx,msg22
		mov edx,longm22
		int 80h
		;imul
		mov al,2
		mov bl,-3
		imul bl
		;representación ascii
		add ax,'0'
		mov [res],eax
		;impresión dec
		mov eax,4
		mov ebx,1
		mov ecx,res
		mov edx,1
		int 80h
		jmp _start
	Div:
		mov eax,4
		mov ebx,2
		mov ecx,msg33
		mov edx,longm33
		int 80h
		;div
		mov al,9
		mov bl,3
		div bl
		;representación ascii
		add ax,'0'
		mov [res],eax
		;impresión dec
		mov eax,4
		mov ebx,1
		mov ecx,res
		mov edx,1
		int 80h
		jmp _start
	Divi:
		mov eax,4
		mov ebx,2
		mov ecx,msg44
		mov edx,longm44
		int 80h
		;idiv
		mov al,9
		mov bl,-3
		idiv bl
		;representación ascii
		add ax,'0'
		mov [res],eax
		;impresión dec
		mov eax,4
		mov ebx,1
		mov ecx,res
		mov edx,1
		int 80h
		jmp _start





	Fin:
		mov eax,1
		mov ebx,0
		int 80h
