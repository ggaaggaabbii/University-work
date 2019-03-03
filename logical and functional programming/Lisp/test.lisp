(DEFUN impar(L)
    (COND
        ((NULL L) nil)
        (T (NOT (impar (CDR L))))
    )
)

(DEFUN isLiniar(L)
    (COND
        ((NULL L) T)
        ((LISTP (CAR L)) nil)
        (T (isLiniar (CDR L)))
    )
)

(DEFUN sterge(L)
    (COND
        ((NULL L) nil)
        ((ATOM (CAR L)) (CONS (CAR L) (sterge (CDR L))))
        ((AND (isLiniar (CAR L)) (impar (CAR L))) (sterge (CDR L)))
        ((isLiniar (CAR L)) (CONS (CAR L) (sterge (CDR L))))
        ((AND (NOT (NULL (sterge (CAR L)))) (NOT (NULL (sterge (CDR L))))) (LIST (sterge (CAR L)) (sterge (CDR L))))
        ((NOT (NULL (sterge (CAR L))))(LIST (sterge (CAR L))))
        (T (sterge (CDR L)))
    )
)