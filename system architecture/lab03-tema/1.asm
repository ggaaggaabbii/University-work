bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    rez dq 0
    a db 3
    b dd 4
    c db 2
    d db 6
    x dq 10
    noua db 9
    zero dd 0
; our code starts here
segment code use32 class=code
    start:
        ; x-(a+b+c*d)/(9-a), a,c,d-byte; b-doubleword; x-qword inmultiri/impartiri unsigend
        mov al, [c];mutam c in al
        mul byte [d];ax ia valoarea c*d (12)
        mov ebx, [zero]
        mov bx, ax;
        mov eax, ebx;convertim valoarea din ax la doubleword si o punem in eax
        add eax, [b];adaugam b peste c*d (16)
        mov [b], eax;mutam b+c*d in b pentru a putea foloso registrii pt alte calcule
        mov al, [a];mutam a in al
        mov ebx, [zero]
        mov bl, al
        mov eax, ebx;convertim a la doubleword
        add eax, [b];adaugam b peste eax unde avem valoarea a+b+c*d (19)
        mov [b], eax;punem inapoi in b rezultatul
        mov al, [noua];punem valoarea 9 in registrul al
        sub al, [a]; scadem a din 9 pt a obtine (9-a) (6)
        mov ebx, [zero]
        mov bl, al;
        mov ax, bx;convertim rezultatul 9-a la word
        mov bx, ax;mutam 9-a in bx
        push dword [b];punem pe stiva valoarea lui b (a+b+c*d)
        pop ax;
        pop dx;punem valoarea a+b+c*d in perechea dx:ax
        div bx;impartim a+b+c*d la 9-a catul va fi in ax iar restul in dx
        mov ebx, [zero]
        mov bx, ax
        mov eax, ebx;convertim catul impartirii a+b+c*d la 9-a la doubleword
        mov ebx, [zero]
        mov edx, ebx;punem 0 in edx pentru a avea rezultatul (a+b+c*d)/(9-a) in edx:eax
        push dword [x];punem pe stiva valoarea lui x
        push dword [x+4];
        pop ebx;
        pop ecx;valoarea lui x va fi pusa pe perechea ebx:ecx
        sub ecx, eax;
        sbb ebx, edx;in perechea e ebx:ecx vom avea rezultatul (7)
        push ebx;
        push ecx;
        pop dword [rez]
        pop dword [rez+4];punem in variabila rez rezultatul final
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
