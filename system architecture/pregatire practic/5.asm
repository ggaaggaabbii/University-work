bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fprintf, fopen               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    nume_fisier resb 30
    cuv resb 30
    descriptor dd 0
    mod_deschidere db "w", 0
    format_citire db "%s", 0
    format_scriere db "%s", 10, 13, 0
    
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push nume_fisier
        push format_citire
        call [scanf]
        add esp, 4 * 2
        
        push mod_deschidere
        push nume_fisier
        call [fopen]
        mov [descriptor], eax
        add esp, 4 * 2
        
        citire:
            cmp byte [cuv], '$'
            je final
            
            push cuv
            push format_citire
            call [scanf]
            add esp, 4 * 2
            
            cmp byte [cuv], '$'
            je final
            
            push cuv
            push format_scriere
            push dword [descriptor]
            call [fprintf]
            add esp, 4 * 3
            
            jmp citire
        
        
        ; exit(0)
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
