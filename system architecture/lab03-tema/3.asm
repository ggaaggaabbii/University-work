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
    zero dd 0
; our code starts here
segment code use32 class=code
    start:
        ; a-d+b+b+c, a - byte, b - word, c - double word, d - qword, unsigned
        mov ebx, [zero]
        mov bx, [b]
        mov eax, ebx;mutam in eax valoarea lui be
        add eax, ebx;in eax avem valoarea b + b (10)
        mov ebx, [zero]
        mov bl, [a]
        add eax, ebx;adunam a la b+b -> eax = a+b+b (13)
        add eax, [c];adunam c -> eax = a+b+b+c (15)
        push dword [d]
        push dword [d+4];punem valoarea lui d pe stiva
        pop ebx;
        pop ecx;punem d in perechea ebx:ecx
        mov edx, [zero];punem 0 edx pentru a avea suma a+b+b+c in perechea edx:eax
        sub eax, ecx
        sbb edx, ebx;scadem perechile edx:eax si ebx:ecx pt a obtine rez final (11)
        push edx;
        push eax;
        pop dword [rez]
        pop dword [rez+4];punem in variabila rez rezultatul final
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
