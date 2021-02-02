global _start

section .data
	get_n_msg db "Iveskite A masyvo dydi (n): ", 0ah
	get_n_msg_l equ $ - get_n_msg
	get_k_msg db "Iveskite maksimalia atsitiktinio skaiciaus reiksme (k): "
	get_k_msg_l equ $ - get_k_msg
	get_m_msg db "Iveskite B masyvo dydi (m): "
	get_m_msg_l equ $ - get_m_msg

section .bss
	n resb 5
	m resb 5
	k resb 5


section .text
_start:

getN:
	mov eax, 4
	mov ebx, 1
	mov ecx, get_n_msg
	mov edx, get_n_msg_l
	int 80h

	mov eax, 3
	mov ebx, 1
	mov ecx, n
	mov edx, 5
	int 80h

	jmp getK

	

getK:	

	mov eax, 1
	int 80h
