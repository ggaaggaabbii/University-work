bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
%include "expresie.asm"
; declare external functions needed by our program
extern exit, scanf, printf, fopen, fprintf, fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 public class=data
    ; ...
    a db 0, 0, 0, 0
    b dw 0, 0
    c dd 0
    formatCitire db "%d", 0
    numeFisier db "output.txt", 0
    moddeschidere db "w", 0
    formatafisare db "%d", 10, 13, 0
    descriptordisier dd 0
    rez dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword a
        push dword formatCitire
        call [scanf]
        add esp, 4 * 2
        
        push dword b
        push dword formatCitire
        call [scanf]
        add esp, 4 * 2
        
        push dword c
        push dword formatCitire
        call [scanf]
        add esp, 4 * 2
                
        push dword [c]
        push dword [b]
        push dword [a]
        call expresie
        add esp, 4 * 3
        
        mov [rez], eax
        
        push dword eax
        push dword formatCitire
        call [printf]
        add esp, 4 * 2

        
        
        push dword moddeschidere
        push dword numeFisier
        call [fopen]
        add esp, 4 * 2
        
        mov [descriptordisier], eax
        mov bx, 10
        mov edx, 0
        mov eax, [rez]
        
        show:
            mov edx, 0
            div bx
            pushad
            
            push edx
            push dword formatafisare
            push dword [descriptordisier]
            call [fprintf]
            add esp, 4 * 3
            
            popad
            cmp ax, 0
            jne show
            
        
        push dword [descriptordisier]
        call [fclose]
        add esp, 4 * 1
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
