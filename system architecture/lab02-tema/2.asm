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
    a db 3
    b db 2
    c db 7
    d dw 3
    x db 0
    os db 100
    cc db 5
    sc db 75
; our code starts here
segment code use32 class=code
    start:
        ; (100*a+d-75*b)/(c-5) a, b, c - bytes, d - word
        mov al,[a];mutam valoarea lui a in registrul al
        mul byte [os];inmultim registrul al cu 100 si rezultatu (100*a) va fi pus in ax
        add ax,[d];in ax avem 100 * a + d
        mov [d], ax; d ia valoarea 100 * a + d
        mov al,[b];mutam pe b in albits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

        mul byte [sc];ax are valoarea 75 * b
        mov bx, [d];bx = 100 * a + d
        sub bx, ax;bx ia valoarea 100 * a + d - 75 * b
        mov al, [c]; al ia val lui c
        sub al, [cc]; scadem 5 din c
        mov [c], al;punem inapoi in c valoarea c - 5
        mov ax, bx; punem in ax valoarea 100 * a + d - 75 * b pentru a putea face impartirea
        div byte [c];se imparte ax(100 * a + d - 75 * b) la c (c - 5) al := catul impartirii, ah := restul impartirii
        mov [x],al;punem rezultatul final in x
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
