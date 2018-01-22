bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fopen, fscanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    contor dd 0
    numar dd 0
    integer db "%d", 0
    format db "%s", 0
    numefisier resb 30
    modd db "r", 0
    descriptor dd 0
    cuv resb 30
    format2 db "%s ",0
    
    
    vocale db "aeiouAEIOU", 0
    
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push numefisier
        push format
        call [scanf]
        add esp, 4 * 2
        
        push numar
        push integer
        call [scanf]
        add esp, 4 * 2
        
        push modd
        push numefisier
        call [fopen]
        mov [descriptor], eax
        add esp, 4 * 2
        
        citire:
            cmp eax, -1
            je final
            
            push cuv
            push format
            push dword [descriptor]
            call [fscanf]
            
            push eax
            call check
            pop eax
            
            jmp citire
          
        
        ; exit(0)
        check:
            cmp eax, -1
            je fin
            
            
            mov ecx, 0
            mov dword [contor], 0
            
            repet:
                cmp byte [ecx + cuv], 0
                je fin
                
                mov ebx, 0
                repet2:
                    cmp byte [ebx + vocale], 0
                    je next
                    
                    mov al, [ecx + cuv]
                    cmp al, [ebx + vocale]
                    je increment
                    
                    inc ebx
                    jmp repet2
                    
                increment:
                    inc dword [contor]
                    inc ebx
                    jmp repet2
                    
                next:
                    inc ecx
                    jmp repet
            
            
            
            
            fin:
                cmp eax, -1
                je f
               mov eax, [contor]
               
               cmp eax, [numar]
               je afis
               
            f:
               ret
           
        
        afis:
            push cuv
            push format2
            call [printf]
            add esp, 4 * 2
            ret
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
