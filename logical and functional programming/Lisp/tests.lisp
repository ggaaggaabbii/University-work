(DEFUN DUP(L e)
    (COND
        (T (APPEND e L e))
    )
)

(DEFUN F(L)
    (COND
        ((NULL L) nil)
        ((LISTP (CAR L)) (DUP (F (CDR L)) (F (CAR L))))
        (T (LIST (CAR L)))
    )
)
