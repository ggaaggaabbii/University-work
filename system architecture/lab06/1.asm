bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dw 0
    unused dw 0
    b dw 0
    unused2 dw 0
    format1 db "%d", 0
    format2 db "%x", 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
    push dword a
    push dword format1
    call [scanf]
    add esp, 4 * 2;citim a in format zecimal
    
    push dword b
    push dword format2
    call [scanf]
    add esp, 4 * 2;citim b in format hexa
    
    mov ax, [a]
    add ax, [b];facem suma a + b in ax
    
    cwde;convertim rezultatul la dword
    
    push dword eax
    push format1
    call [printf]
    add esp, 4 * 2;afisam rezultatul sumei
    
    
    
    
    push dword a
    push dword format1
    call [scanf]
    add esp, 4 * 2;citim a in format zecimal
    
    push dword b
    push dword format2
    call [scanf]
    add esp, 4 * 2;citim b in format hexa
    
    mov ax, [a]
    add ax, [b];facem suma a + b in ax
    
    cwde;convertim rezultatul la dword
    
    push dword eax
    push format1
    call [printf]
    add esp, 4 * 2;afisam rezultatul sumei
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
