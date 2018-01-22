bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
%include "prefix.asm"
%include "show.asm"
; declare external functions needed by our program
extern exit, printf            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll        ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db "abracadabra", 0
    b db "abracal", 0
    c db "abdaa", 0
    format db "%c", 0
    newline db 10, 13, 0
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;determinare si afisare prefix primele 2 siruri
        push dword a
        push dword b
        call prefix
        add esp, 4 * 2
        
        push dword a
        push dword edx
        push dword format
        call show
        add esp, 4 * 3;apelam afisarea prefixului dorit
        
        push dword newline
        call [printf]
        add esp, 4 * 1;trecem la urmatoarea linie
        
        
        ;determinare si afisare prefix sir 1 si sir 2
        push dword a
        push dword c
        call prefix
        add esp, 4 * 2
        
        push dword a
        push dword edx
        push dword format
        call show
        add esp, 4 * 3;apelam afisarea prefixului dorit
        
        
        push dword newline
        call [printf]
        add esp, 4 * 1;trecem la urmatoarea linie
        
        ;determinare si afisare prefix sir 2 si sir 3
        push dword b
        push dword c
        call prefix
        add esp, 4 * 2
        
        push dword b
        push dword edx
        push dword format
        call show
        add esp, 4 * 3;apelam afisarea prefixului dorit
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
