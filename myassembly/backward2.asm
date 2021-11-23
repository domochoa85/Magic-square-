section	.text
   global _start        ;must be declared for using gcc
	
_start:	                ;tell linker entry point
   mov eax, '8'
   mov [tenthnum], al

   mov ecx,10
   mov eax, '0'

Lone:
   mov [onethnum], al
   push ecx
   
   mov eax, 4
   mov ebx, 1
   mov ecx, tenthnum        
   mov edx, 1        
   int 0x80
  
   mov eax, 4
   mov ebx, 1
   mov ecx, onethnum        
   mov edx, 1        
   int 0x80
    
   mov eax, 4
   mov ebx, 1
   mov ecx, dilimiter        
   mov edx, len        
   int 80h

   mov al, [onethnum]
   sub eax, '0'
   inc eax
   add eax, '0'
   pop ecx
   dec ecx
  CMP	ECX, 0	; Compares whether the counter has reached 0
  JNE	Lone  
  ;loop Lone
	
   mov eax,1             ;system call number (sys_exit)
   int 0x80              ;call kernel

section	.bss
onethnum resb 1
tenthnum resb 1

section .data
dilimiter db ':)'  ;string to be printed
len equ $ - dilimiter     ;length of the string 


