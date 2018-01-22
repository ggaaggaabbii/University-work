%ifndef _PREFIX_ASM_
%define _PREFIX_ASM_

    prefix:
        mov esi, [esp + 4]
        mov edi, [esp + 8]
        mov edx, 0
        
        repeta:
            cmp byte [esi], 0;verificam daca primul sir este gata
            je final
            cmp byte [edi], 0;verificam daca al doilea sir este gata
            je final
            cmpsb;verificam daca pe pozitia curenta se afla acelasi caracter
            jne final
            inc edx
            jmp repeta
            
            
        final:
            ret
    
%endif