bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s db 1, 5, 3, 8, 2, 9
    d1 : times 10 db 0
    d2 : times 10 db 0
    format db "%d ", 0
    endline db 13, 10, 0
    text db "The 2 result lists are: ", 13, 10, 0
    format1 db "%s", 0   
    
; our code starts here
segment code use32 class=code

    start:
        ; ...
        mov esi, 0
        mov edi, 0
        mov edx, 0
        mov cx, 6
       
        
        repeta:
            mov al, [s + esi]
            inc esi
 
            mov bl, al
            shr bl, 1
            shl bl, 1;verificam daca numarul este par
            
            dec cx
            cmp cx, -1
            je final;daca ajungem la sfarsitul loopului apelam zona finala
            
            cmp bl, al
            jne impare
            je pare;apelam functia corespunzatoare numerelor pare sau impare
            
        
        impare:
            mov [d2 + edx], al
            inc edx
            jmp repeta;punem numerele impare in al doilea vector
        
        pare:
            mov [d1 + edi], al
            inc edi
            jmp repeta;punem numerele pare in primul vector
        
        
        ; exit(0)
        final:
            push dword text
            push dword format1
            call [printf]
            add esp, 4 * 2;afisam mesajul initial
            
            mov esi, 0
            mov edi, 0
            
            list1:
                cmp byte [d1 + esi], 0
                je nextline;daca ajungem la capatul sirului apelam functia nextline
                
                mov eax, 0
                mov al, [d1 + esi]
                inc esi;punem in eax elementul care trebuie afisat
                
                push eax
                push dword format
                call [printf]
                add esp, 4 * 2;afisam continutul lui eax sub forma de integer
                
                jmp list1;reapelam functia list1
            
            list2:
                cmp byte [d2 + edi], 0
                je stop;daca ajungem la capatul sirului apelam functia stop
               
                mov eax, 0
                mov al, [d2 + edi]
                inc edi;punem in eax elementul care trebuie afisat
                
                push eax
                push dword format
                call [printf]
                add esp, 4 * 2;afisam continutul lui eax sub forma de integer
                
                jmp list2;reapelam functia list2
                
            nextline:
                push dword endline
                push dword format1
                call [printf]
                add esp, 4 * 2
                
                jmp list2
            
        stop:
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
