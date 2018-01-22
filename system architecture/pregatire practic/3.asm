bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fprintf, fopen               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    format db "%d", 0
    numefisier db "text.txt", 0
    formatdeschidere db "w", 0
    descriptor dd 0
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        
        
        push formatdeschidere
        push numefisier
        call [fopen]
        mov [descriptor], eax
        add esp, 4 * 2
        
        mov eax, 0
        mov al, 5
        
        push eax
        push format
        push dword [descriptor]
        call [fprintf]
        add esp, 4 * 3
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
