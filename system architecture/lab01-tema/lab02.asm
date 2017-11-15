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
    a db 10
    b db 40
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; E = (b/a*2+10)*b-b*15
        mov AX, [b]
        div byte [a]
        mov BL, 2
        mul BL ; ax = b/a*2
        add AX, 10
        mov BX, b
        mul BX ; DX:AX = ()*b
        push DX ;punem dx pe stiva(dl sus, dh jos)
        push AX 
        pop EBX ;ebx ia val dx ax
        mov AX, 15
        mul word [b]
        push DX
        push AX
        pop ECX
        sub EBX, ECX ;rez in EBX
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
