bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        


; our code starts here
segment code use32 public class=code
    expresie:
    ;calcculeaza (2*a-b)*10-c
        mov ebx, [esp + 4]
        mov al, [ebx]
        doi db 2
        mul byte [doi]
        
        cbw
        
        mov ebx, [esp + 8]
        mov cx, [ebx]
        sub ax, cx
        
        zece db 10
        mul word [zece]
        
        cwde
        
        mov ebx, [esp + 12]
        mov ecx, [ebx]
        sub eax, ecx
        ret
        