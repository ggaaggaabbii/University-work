bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fscanf, printf, fopen               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    character dd 0
    numefisier resb 30
    descriptor dd 0
    formatcitire db "%s", 0
    moddesc db "r", 0
    formatcitire2 db "%c", 0
    impare db "13579", 0
    contor dd 0
    formatscriere db "%d", 10, 13, 0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push numefisier
        push formatcitire
        call [scanf]
        add esp, 4 * 2
        
        push moddesc
        push numefisier
        call [fopen]
        mov [descriptor], eax
        add esp, 4 * 2
        
        citire:
            cmp eax, -1
            jle final
            
            push character
            push formatcitire2
            push dword [descriptor]
            call [fscanf]
            
            call isimpar
            
            jmp citire
    
        ; exit(0)
        
        isimpar:
            mov ecx, 0
            l:
              cmp ecx, 5
              je fin
              
              mov bl, [impare + ecx]
              cmp bl, [character]
              je increment
              
              
              inc ecx
              jmp l
              
              increment:
                inc ecx
                inc dword [contor]
                jmp l
             
            fin:
                ret
        
        
        final:
        push dword [contor]
        push formatscriere
        call [printf]
        add esp, 4 * 2
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
