%ifndef _SHOW_ASM_
%define _SHOW_ASM_
  
extern printf
import printf msvcrt.dll  
    
    show:
        mov edx, [esp + 4]
        mov esi, [esp + 12]
        mov ecx, [esp + 8]

        afis:
            cmp ecx, 0
            je gata;daca am ajuns la capatul prefixului terminam loopul
            
            mov eax, 0
            lodsb
            
            pushad;salvam starea curenta a registrilor
            
            push dword eax
            push dword edx
            call [printf]
            add esp, 4 * 2;afisam caracterul curent
            
            popad;preluam registrii dinainte de afisare
            
            
            loop afis
            
    gata:     
        ret

%endif