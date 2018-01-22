bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fscanf, scanf, fprintf, fopen, fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import fscanf msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    sir resd 30
    lensir db 0
    format_citire db "%d", 0
    format_deschidere_cirire db "r", 0
    format_deschidere_scriere db "w", 0
    format_afis db "%d ", 0
    format_citire_nume db "%s", 0
    nume_fisier_citire resb 30
    nume_fisier_scriere resb 30
    descriptor_citire dd 0
    descriptor_scriere dd 0
    patru db 4
    

; our code starts here
segment code use32 class=code
    start:
        ; se citesc 2 nume de fisiere de intrare si de iesire
        ;din fisierul de intrare se citesc numere si se sciu in fisierul de iesire numerele care au un numar par de biti de 1 in reprezentarea binara
        push nume_fisier_citire
        push format_citire_nume
        call [scanf]
        add esp, 4 * 2
        
        push nume_fisier_scriere
        push format_citire_nume
        call [scanf]
        add esp, 4 * 2
        
        push format_deschidere_cirire
        push nume_fisier_citire
        call [fopen]
        mov [descriptor_citire], eax
        add esp, 4 * 2
        
        push format_deschidere_scriere
        push nume_fisier_scriere
        call [fopen]
        mov [descriptor_scriere], eax
        add esp, 4 * 2
        
        citire_fisier:
            cmp eax, -1
            je next
            
            mov ebx, sir
            mov al, [lensir]
            mul byte [patru]
            cwde
            add eax, ebx
            
            
            push eax
            push format_citire
            push dword [descriptor_citire]
            call [fscanf]
            add esp, 4 * 3
            inc byte [lensir]
            jmp citire_fisier
            
            
        next:
            mov al, [lensir]
            cbw
            cwde
            mov ecx, eax
            mov esi, sir
            dec ecx
            afis:
                cmp ecx, 0
                je final
                push ecx
                lodsd
                cmp eax, 0
                jp  notafis
                
                push eax
                push format_afis
                push dword [descriptor_scriere]
                call [fprintf]
                add esp, 4 * 3
                
                notafis:
                    pop ecx
                    loop afis
                
        
        final:
            push dword [descriptor_citire]
            call [fclose]
            add esp, 4 * 1
            push dword [descriptor_scriere]
            call [fclose]
            add esp, 4 * 1
            
        ; exit(0)
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
