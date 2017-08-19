section .data
	msg db "hola",0xA
	longm equ $ - msg



section .bss


section .text
global _start:
_start:

mov	cx, 10

L1:
	push cx
	mov eax,4
	mov ebx,2
	mov ecx,msg
	mov edx,longm
	int 80h
	pop cx
	dec	cx
	cmp cx,0
	JNZ	L1


mov eax,1
mov ebx,0
int 80h
