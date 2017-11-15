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
    a   db  -3 
    b   db  3
    c   db  4
    d   db  6
    x   db  0
; our code starts here
segment code use32 class=code
    start:
        ; c - (a + d) + (b + d), a, b, c, d = bytes
        mov al,[a];mutam valoarea lui a in registrul al
        add al,[d];adaugam valoarea lui d peste valoarea lui a ca sa obtinem (a + d)
        mov ah,[c];punem c in registrul ah
        sub ah,al;din valoarea lui c scadem suma (a + d)
        mov al,ah;;mutam rezultatul inapoi in al, in al vom avea c - (a + d)
        add al,[b];adaugam peste rezultatul curent valoarea lui b si valoarea lui d
        add al,[d]
        mov [x], al;mutam rezultatul final in variabila x
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
