bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import printf msvcrt.dll
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dw 0
    b dw 0
    format db "%d", 0
    format2 db "Cat = %d, rest = %d", 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword a
        push dword format
        call [scanf]
        add esp, 4 * 2; citim valoarea lui a
        
        push dword b
        push dword format
        call [scanf]
        add esp, 4 * 2; citim valoarea lui b
        
        mov ax, [a]
        cwd;convertim a la dx:ax
        
        idiv word [b];calculam catul si restul impartirii
        
        mov [a], ax;copiem valoarea catului
        
        mov ax, dx
        cwde;punem dx in eax
        push dword eax;punem restul pe stiva
        
        mov ax, [a]
        cwde;punem catul in eax
        push dword eax;punem catul pe stiva
        
        push dword format2
        call [printf]
        add esp, 4 * 3;afisam rezultatul
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
