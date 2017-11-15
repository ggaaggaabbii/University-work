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
    a db 10011101b
    b db 01111010b
    n db 0
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        ; Se da octetul A. Sa se obtina numarul intreg n reprezentat de bitii 2-4 ai lui A. Sa se obtina apoi in B octetul rezultat prin rotirea spre dreapta a lui A cu n pozitii. Sa se obtina dublucuvantul C: 1. bitii 8-15 ai lui C sunt 0 2. bitii 16-23 ai lui C coincid cu bitii lui B 3. bitii 24-31 ai lui C coincid cu bitii lui A 4. bitii 0-7 ai lui C sunt 1
        mov al, [a];punem a in al
        and al, 00011100b;izolam biti 2-4
        mov [n], al;
        mov al, [a];mutam a inapoi in al
        mov cl, [n];
        ror al, cl;rotim a cu n pozitii
        mov [b], al;preluam valoarea lui b
        mov eax, 0
        or al, 11111111b;confuguram 
        or [c], eax;facem bitii 0-7 a lui c valoarea 1
        mov al, [b];mutam b in al
        shl eax, 16;mutam bitii lui b pe pozitiile 16-23
        or [c], eax;punem bitii lui b in c pe poz corespunzatoare
        mov eax, 0;reconstruim eax
        mov al, [a]
        shl eax, 24;aducem bitii lui a pe pozitiile corespunzatoare
        or [c], eax;punem bitii lui a in c
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
