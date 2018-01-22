bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fopen, fclose, printf, fprintf, gets         ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import gets msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    numeFisier resb 30
    descriptorFisier dd 0
    text resb 120
    formatCitire db "%s", 0
    formatScriere db "w", 0
    mesajEroare db "fisierul nu poate fi creat", 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword numeFisier
        call [gets]
        add esp, 4 * 2;citim numele fisierului
        
        push dword text
        call [gets]
        add esp, 4 * 2;citim continutul fisierului
        
        push dword formatScriere        
        push dword numeFisier
        call [fopen]
        add esp, 4 * 2;deschidem fisierul de scriere
        
        mov [descriptorFisier], eax
        
        cmp dword [descriptorFisier], 0
        je eroare;verificam daca fisierul poate fi creat si afisam un mesaj corespunzator
        
        push dword text
        push dword [descriptorFisier]
        call [fprintf]
        add esp, 4 * 2;scriem mesajul in fisier;        
        
        
        push dword [descriptorFisier]
        call [fclose]
        add esp, 4 * 1;inchidem fisierul
        
        final:
            ; exit(0)
            
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
        
        eroare:
            push dword mesajEroare
            push dword formatCitire
            call [printf]
            add esp, 4 * 2
            jmp final;afisam mesajul de eroare dupa care sarim la terminarea programului
            