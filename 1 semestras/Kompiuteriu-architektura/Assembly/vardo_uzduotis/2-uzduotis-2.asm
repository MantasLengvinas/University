; 2 užduotis (naudojant cikla)
; Mantas Lengvinas ISI 1k, 1gr, 1pogr

section .data
	lastname db "Lengvinas"
	len equ $- lastname
    letter db "M"

section .text
	global _start

_start:

	mov edi, len ; Nustatomas ciklo ilgis edi registre

ciklas:
	
	mov edx, 1
	mov ecx, letter
	mov eax, 4
	mov ebx, 1
	int 80h

	dec edi ; Mažina reikšmę vienetu reikšmę esančią edi registre (ciklo pakartojimų skaičius)
	jg ciklas
    
    mov eax, 1
    int 80h

	