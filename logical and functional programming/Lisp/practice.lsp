(DEFUN check (L Elem)
    (COND
        ((> (check2 L Elem) 0) T)
        (T nil)
    )
)

(DEFUN check2 (L Elem)
    (COND 
        ((EQUAL L Elem) 1)
        ((ATOM L) 0)
        (T (APPLY ' (MAPCAR #'(lambda(a) (check2 a Elem)) L)))
    )
)


(DEFUN largestNr (L)
    (COND 
        ((NUMBERP L) L)
        ((ATOM L) 0)
        (T (APPLY 'MAX (MAPCAR 'largestNr L)))
    )
)

(DEFUN evenNrOfElems (L)
    (COND
        ((NULL L) T)
        (T (NOT (evenNrOfElems (CDR L))))
    )
)
