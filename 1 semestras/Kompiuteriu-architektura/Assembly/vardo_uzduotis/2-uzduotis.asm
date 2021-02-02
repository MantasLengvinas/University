; 2 užduotis
; Mantas Lengvinas ISI 1k, 1gr, 1pogr

section .data
	lastname db "Lengvinas"
	len equ $- lastname
    letter times len db "M"

section .text
	global _start

_start:

	mov edx, len
	mov ecx, letter
	mov ebx, 1
	mov eax, 4
	int 0x80
    
    mov eax, 1
    int 80h