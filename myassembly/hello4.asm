section .text
GLOBAL _start

_start: mov ecx, string
        call toUpper
        call print
        mov eax,1
        mov ebx,0
        int 80h

toUpper:
        mov al,[ecx]      ; ecx is the pointer, so [ecx] the current char
        cmp al,0x0 
        je done
        cmp al,'a'
        jb next
        cmp al,'z'
        ja next
        sub al,0x20       ; move AL upper case and
        mov [ecx],al      ; write it back to string

next:
        inc ecx           ; not al, that's the character. ecx has to
                          ; be increased, to point to next char
        jmp toUpper
done:   ret

print:  mov ecx, string    ; what to print
        mov edx, len       ; length of string to be printed
        mov ebx, 1
        mov eax, 4
        int 80h
        ret

section .data
string: db "suny oneonta",10,0
len:    equ $-string
