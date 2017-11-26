bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    sir dd 12345678h, 1256ABCDh, 12AB4344h, 31246752h
    len equ ($ - sir) / 4
    contor dd 0
    format db "%x", 10, 13, 0
    patru dd 4
    aux dd 0
    
; our code starts here
segment code use32 class=code
    start:
        mov ecx, len - 1;initializam numarul de iteratii din primul for
        ; ...
        for1:

            mov esi, sir
            mov eax, [contor]
            mul dword [patru]
            add esi, eax;calculam pozitia relativa al lui v[i]
            
            mov edi, esi
            
            mov eax, [contor]
            mov [aux], eax
            inc dword [aux];initializam inceputul celui de al doilea for
            
            for2:
                add edi, 4;incrementam pentru a avea corect v[j]
                
                cmpsw;comparam cele 2 elemente
                
                jb swap
                
                sub edi, 2
                sub esi, 2
                
                endfor2:
                    inc dword [aux]
                    cmp dword [aux], len
                    je endfor1
                    jne for2
                    
            endfor1:
                inc dword [contor]
            
                loop for1
        
        mov ecx, 0
        mov [contor], ecx
        mov ecx, len;initializam forul pentru afisare
    
        show:
            mov [aux], ecx
               
            mov esi, sir
            mov eax, [contor]
            mul dword [patru]
            add esi, eax;calculam pozitia relativa a elementului care trebuie afisat
            
            push dword [esi]
            push dword format
            call [printf]
            add esp, 4 * 2;afisam elementul
            
            inc dword [contor]
            
            mov ecx, [aux]
        loop show
            
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
            
        swap:
            sub edi, 2
            sub esi, 2
            mov bx, [edi]
            movsw
            sub edi, 2 
            sub esi, 2
            mov [esi], bx
            
            jmp endfor2;facem swap intre v[i] si v[j]
        