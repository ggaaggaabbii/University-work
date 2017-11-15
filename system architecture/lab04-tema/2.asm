bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    b db 10011100b
    a dw 1000111010110101b

; our code starts here
segment code use32 class=code
    start:
        ; Sa se inlocuiasca bitii 0-3 ai octetului B cu bitii 8-11 ai cuvantului A.
        mov ax, [a];punem a in ax
        mov cl, 8;
        shr ax, cl;deplasam a cu 8 pozitii spre drapta
        or al, 00001111b; separam bitii lui a de pe poz 8-11
        and byte [b], 11110000b; resetam bitii 0-3 ai lui b
        or [b], al;punem bitii din a de pe poz 8-11 pe poz 0-3 in b
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
