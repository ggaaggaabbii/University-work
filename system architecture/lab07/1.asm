bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dw 12h, 3h, 0fh, 0ffh
    d db 88h, 0ah, 12h
    b dw 8, 5, 3, -4, -8
    c dd 543a8feh
    len equ ($ - a)
    n db 0
    m db 0
    aux dd 0
    format db "%d", 10, 13, 0
    format1 db "%x", 10, 13, 0
    mesaj db "octetul din memorie de pe pozitia %d este: %x", 10, 13, 0
    mesajpar db "DA", 10, 13, 0
    mesajimpar db "NU", 10, 13, 0
    sir times 30 db 0 
    min1 db -1
    contor db 0
    
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov eax, [c]
        or [n], al
        and byte [n], 11110000b
        shl eax, 28
        and al, 00001111b
        xor al, 00001111b
        or [n], al
        
        mov al, [n]
        cbw
        cwde
        
        push dword eax
        push dword format
        call [printf]
        add esp, 4 * 2
        
        
        mov al, [n]
        mov bl, [min1]
        imul bl

        cwde
        add eax, 1
        mov [n], al
        
        
        push dword eax
        push dword format
        call [printf]
        add esp, 4 * 2
        
        
        mov eax, 0
        mov al, [n]
        mov esi, eax
        
        mov eax, 0
        mov al, [a + esi]
        
        mov eax, 0
        mov al, [a + esi]
        
        push dword eax
        
        mov eax, 0
        mov al, [n]
        
        push dword eax
        push dword mesaj
        call [printf]
        add esp, 4 * 3
        
        mov ecx, len
        
        mov esi, 0
        
        repeta:
            mov [aux], ecx
            mov ebx, len
            sub ebx, ecx
            
            push ebx
            pop ax
            pop dx
            div word [n]
            cmp dx, 0
            jne skip
            
            mov eax, ebx
             
            mov esi, ebx
            mov al, [a + esi]
            
            
            
            mov dl, al
            
            shr al, 1
            shl al, 1
            
            cmp al, dl
            je par
            jne impar
            
            endloop:
            mov ecx, [aux]
            loop repeta
            
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
    
    par:
        push dword mesajpar
        call [printf]
        add esp, 4 * 1
        jmp endloop
        
    impar:
        push dword mesajimpar
        call [printf]
        add esp, 4 * 1
        jmp endloop
        
    skip:
        jmp endloop
        