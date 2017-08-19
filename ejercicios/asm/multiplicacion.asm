section .data

	msg db "2 por 3 es: "
	longm equ $ - msg
	msg2 db "9 entre 3 es: "
	longm2 equ $ - msg2
	msg3 db "2 por -3 es: "
	longm3 equ $ - msg3
	msg4 db "9 entre -3 es: "
	longm4 equ $ - msg4
	line db 0xA
	lline equ $ - line

section .bss
	res resb 1


section .text
global _start:
_start:
	;Imprime el mensaje
	mov eax,4                 		;system write
	mov ebx,2                 		;stdout 
	mov ecx,msg                   	;imprimir
	mov edx,longm					;tamano(imprimir)
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

	;imprime nueva línea
	mov eax,4
	mov ebx,1
	mov ecx,line
	int 80h

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	;Imprime el mensaje
	mov eax,4
	mov ebx,2
	mov ecx,msg2
	mov edx,longm2
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

	;imprime nueva línea
	mov eax,4
	mov ebx,1
	mov ecx,line
	int 80h

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	;Imprime el mensaje
	mov eax,4
	mov ebx,2
	mov ecx,msg3
	mov edx,longm3
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

	;imprime nueva línea
	mov eax,4
	mov ebx,1
	mov ecx,line
	int 80h

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	;Imprime el mensaje
	mov eax,4
	mov ebx,2
	mov ecx,msg4
	mov edx,longm4
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

	;imprime nueva línea
	mov eax,4
	mov ebx,1
	mov ecx,line
	int 80h

;;;;Fin blablabla;;;;

	mov eax,1
	mov ebx,0
	int 80h

