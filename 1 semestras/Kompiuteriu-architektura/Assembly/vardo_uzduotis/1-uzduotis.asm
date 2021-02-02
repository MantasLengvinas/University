; 1 užduotis
; Mantas Lengvinas ISI 1k, 1gr, 1pogr

section	.data
	msg db "Mantas Lengvinas", 0xa
	len equ $ - msg

section	.text
   global _start     
	
_start:	  

	; Vardo ir pavardes isvedimas

	mov	edx, len     
	mov	ecx, msg     
	mov	ebx, 1       
	mov	eax, 4       
	int	0x80

	mov eax, 1
	int 0x80
