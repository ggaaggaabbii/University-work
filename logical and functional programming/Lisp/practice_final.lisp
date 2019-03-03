(DEFUN F(L)
    (MAX (CAR L) (CADDR L))
)

(DEFUN replace_tree(L Elem Lvl)
    (COND
        ((NULL L) nil)
        ((AND (EQUAL Lvl 0) (ATOM (CAR L))) (APPEND (LIST Elem) (replace_tree (CDR L) Elem Lvl)))
        ((ATOM (CAR L)) (APPEND (LIST (CAR L)) (replace_tree (CDR L) Elem Lvl)))
        ((LISTP (CAR L)) (APPEND (LIST (replace_tree (CAR L) Elem (- Lvl 1))) (replace_tree (CDR L) Elem Lvl)))
    )
)

(defun G(L)
	(+ (car l) (cadr l))
)