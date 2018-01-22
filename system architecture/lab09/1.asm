bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, scanf, printf, fclose, gets               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fread msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fclose msvcrt.dll
import gets msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    numeFisier resb 30
    text resb 130
    len equ 130
    descriptorFisier dd 0
    formatCitire db "%s", 0
    formatCitireNume db "%s", 0
    formatAfisare db "%d", 10, 13, 0
    modAcces db "r", 0
    frecvSpatiu dd 0
    mesajEroare db "fisierul nu poate fi deschis", 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword numeFisier
        call [gets]
        add esp, 4 * 1
        
        push dword modAcces
        push dword numeFisier
        call [fopen]
        add esp, 4 * 2
        
        
        mov [descriptorFisier], eax
        cmp dword [descriptorFisier], 0
        je eroare
        
        push dword [descriptorFisier]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4 * 4
        
        mov edi, text
        mov al, ' '
        compara:
            scasb
            je incrementare
            continua:
                cmp byte [edi], 0
                jne compara
            
            
        
        push dword [frecvSpatiu]
        push dword formatAfisare
        call [printf]
        
        
        push dword [descriptorFisier]
        call [fclose]
        
        final:
            ; exit(0)
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
        
        incrementare:
            inc dword [frecvSpatiu]
            jmp continua
          
        eroare:
            push dword mesajEroare
            push dword formatCitire
            call [printf]
            add esp, 4 * 2
            jmp final;afisam mesajul de eroare dupa care sarim la terminarea programului
            