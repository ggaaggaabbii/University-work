bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fprintf, fopen, fscanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fscanf msvcrt.dll
    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    sir resd 15
    dp resd 15
    format_citire db "%d", 0
    format_scriere db "%d ", 0
    format_citire_nume db "%s", 0
    mod_citire db "r", 0
    mod_scriere db "w", 0
    descriptor_citire dd 0
    descriptor_scriere dd 0
    nume_input resb 40
    nume_output resb 40
    len_sir dd 0
    patru dd 4
    minus1 dd -1
    aux dd 0
    maxim dd 0
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        push nume_input
        push format_citire_nume
        call [scanf]
        add esp, 4 * 2
        
        push nume_output
        push format_citire_nume
        call [scanf]
        add esp, 4 * 2
        
        push mod_citire
        push nume_input
        call [fopen]
        mov [descriptor_citire], eax
        add esp, 4 * 2
        
        push mod_scriere
        push nume_output
        call [fopen]
        mov [descriptor_scriere], eax
        add esp, 4 * 2
        
        citire:
            cmp eax, -1
            je next
            mov ebx, sir
            mov eax, [len_sir]
            mul word [patru]
            add eax, ebx
            
            push eax
            push format_citire
            push dword [descriptor_citire]
            call [fscanf]
            add esp, 4 * 3
            inc dword [len_sir]
            jmp citire
           
            
        next:
            dec dword [len_sir]
            mov ecx, [len_sir]
            dinamica:
                mov ebx, dp
                mov eax, [len_sir]
                sub eax, ecx
                mul word [patru]
                
                add ebx, eax
                
                loopback:
                    mov eax, dp
                    cmp ebx, eax
                    jb nextstep
                    
                    call updatedinamica
                    sub ebx, 4
                    
                    jmp loopback
                    
                    
                nextstep:
                    loop dinamica
        jmp final
            
        updatedinamica:
            
            mov eax, [len_sir]
            sub eax, ecx
            mul word [patru]
            add eax, dp
            mov edx, [ebx - 60]
            
            cmp edx, [eax - 60]
            jbe finish
            
            mov edx, [ebx]
            inc edx
            cmp edx, [eax]
            jbe finish
            ;mov edx, [dp + eax - ecx * 4]
            mov [eax], edx
            
            finish:
            ret
            
        ; exit(0)
        final:
        mov ecx, [len_sir]
            afis:
                mov ebx, dp
                mov eax, [len_sir]
                sub eax, ecx
                mul dword [patru]
                
                add ebx, eax
            
                mov eax, [ebx]
            
                cmp eax, [maxim]
                jle finalloop
                mov [maxim], eax
            
                finalloop:
                    loop afis
            
        push dword [maxim]
        push format_scriere
        push dword [descriptor_scriere]
        call [fprintf]
        add esp, 4 * 3
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
