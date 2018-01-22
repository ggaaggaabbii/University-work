bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fprintf, fopen           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    sir1 resb 100
    sir2 resb 100
    sir3 resb 200
    format_citire db "%s", 0
    mod_deschidere db "w", 0
    nume_fisier db "rezultat.txt", 0
    descriptor_fisier dd 0

; our code starts here
segment code use32 class=code
    start:
        ; Se dau doua siruri de caractere ordonate alfabetic s1 si s2. Sa se construiasca prin interclasare sirul ordonat s3 care sa contina toate ;elementele din s1 si s2.
        ;sirurile vor fi citite de la tastatura iar rezultatul va fi afisat in fisierul rezultat.txt
        push sir1
        push format_citire
        call [scanf]
        add esp, 4 * 2
        
        push sir2
        push format_citire
        call [scanf]
        add esp, 4 * 2
        
        push mod_deschidere
        push nume_fisier
        call [fopen]
        mov [descriptor_fisier], eax
        add esp, 4 * 2
        
        mov ebx, sir1
        mov ecx, sir2
        mov edi, sir3
        
        interclasare:
            cmp byte [ebx], 0
            je sfsir1
            
            cmp byte[ecx], 0
            je sfsir2
            
            call compare
            jmp interclasare
        
        compare:
            mov al, [ebx]
            cmp al, [ecx]
            jg compare2
            stosb
            inc ebx
            ret
            
            compare2:
            mov al, [ecx]
            stosb
            inc ecx
            ret
            
    
        ; exit(0)
        sfsir1:
            cmp byte [ecx], 0
            je final
            mov al, [ecx]
            stosb
            inc ecx
            jmp sfsir1
            
        sfsir2:
            cmp byte [ebx], 0
            je final
            mov al, [ebx]
            stosb
            inc ebx
            jmp sfsir2
        
        final:
            push sir3
            push format_citire
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 4 * 3
            
            
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
