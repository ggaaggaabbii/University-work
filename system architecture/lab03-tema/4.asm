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
    rez dq 0
    a db 3
    b dw 5
    c dd 2
    d dq 4
; our code starts here
segment code use32 class=code
    start:
        ; a-d+b+b+c, a - byte, b - word, c - double word, d - qword, unsigned
        mov al, [a];mutam a in al
        cbw;convertim a la word
        add ax, [b]
        add ax, [b];in ax avem valoarea a+b+b (13)
        cwde;
        add eax, [c];eax avem valoarea a+b+b+c(15)
        cdq;convertim rezultatul la qword in perechea edx:eax
        push dword [d]
        push dword [d+4];punem pe stiva valoarea lui d
        pop ebx;
        pop ecx;punem d in perechea ebx:ecx
        sub eax, ecx
        sbb edx, ebx;scadem perechile edx:eax si ebx:ecx pt a obtine rez final (11)
        push edx;
        push eax;
        pop dword [rez]
        pop dword [rez+4];punem in variabila rez rezultatul final
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
