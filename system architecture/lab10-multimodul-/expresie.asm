%ifndef _EXPRESIE_ASM_
%define _EXPRESIE_ASM_
; our code starts here
    expresie:
    ;calcculeaza (2*a-b)*10-c
        mov eax, 0
        mov ebx, [esp + 4]
        mov al, bl
        mov cl, 2
        mul cl
        
        mov ebx, [esp+8]
        mov cx, bx
        sub ax, cx
        mov cx, 10
        mul cx
        
        mov ebx, [esp + 12]
        sub eax, ebx
        
        push eax
        pop ax
        pop dx
        ret
%endif