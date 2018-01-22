bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fprintf, fopen, fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
    sir1 resb 30
    sir2 resb 30
    sir3 resb 60
    nume resb 30
    modd db "w", 0
    format db "%s", 0
    format2 db "%c", 0
    contor dd 0
    descriptor dd 0
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push sir1
        push format
        call [scanf]
        add esp, 4 * 2
        
        push sir2
        push format
        call [scanf]
        add esp, 4 * 2
        
        push nume
        push format
        call [scanf]
        add esp, 4 * 2
        
        push modd
        push nume
        call [fopen]
        mov [descriptor], eax
        add esp, 4 * 2
        
        mov ebx, sir1
        mov ecx, sir2
        
        
        scriere:
            cmp byte [ebx], 0
            je finsir1
            
            cmp byte [ecx], 0
            je finsir2
            
            call comp
            
            jmp scriere
            
        
        comp:
            mov al, [ecx]
            
            cmp al, [ebx]
            ja s2
            inc dword [contor]
            mov edx, [contor]
            
            mov [sir3 + edx], al
            inc ecx
            
            ret
            
            s2:
              mov al, [ebx]
              inc dword [contor]
              mov edx, [contor]
                
              mov [sir3 + edx], al
              inc ebx
              ret
           
        finsir1:
            cmp byte [ecx], 0
            je final
            
            inc dword [contor]
            mov al, [ecx]
            mov edx, [contor]
            mov [edx + sir3], al
            inc ecx
            jmp finsir1
            
        finsir2:
            cmp byte [ebx], 0
            je final
            
            inc dword [contor]
            mov al, [ebx]
            mov edx, [contor]
            mov [edx + sir3], al
            inc ebx
            jmp finsir2
        
        
        final:
            mov ecx, [contor]
            
            afis:
                push ecx
                
                push dword [sir3 + ecx]
                push format2
                push dword [descriptor]
                call [fprintf]
                add esp, 4 * 3
                
                pop ecx
                loop afis
                
        push dword [descriptor]
        call [fclose]
        add esp, 4 * 1
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
