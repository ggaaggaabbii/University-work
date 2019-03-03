;; Return the level (depth) of a node in a tree of type (1). The level of the root element is 0.
 
 (DEFUN subarbori ( l n m )
    (COND
        ((NULL l) nil)
        ((EQ n (+ 1 m)) (LIST l))
        (T (APPEND (APPEND (LIST (CAR l)) (LIST (CADR l))) (subarbori (CDDR l) (+ 1 n) (+ m (CADR l)))))
    )
 )
 
 (DEFUN depth (l a r)
    (COND
        ((NULL l) nil)
        ((EQ (CAR l) a) r)
        ((NOT (NULL (MEMBER a (drept (subarbori (CDDR l) 0 0))))) (depth (drept (subarbori (CDDR l) 0 0)) a (+ 1 r)))
        (T (depth (stang (subarbori (cddr l) 0 0)) a (+ 1 r)))
    )
 )
 
 
 (DEFUN stang (l)
    (COND
        ((NULL l) nil)
        ((ATOM (CAR l)) (CONS (CAR l) (stang (CDR l))))
    )
 )
 
 (DEFUN drept(l)
    (COND
        ((NULL l ) nil)
        ((LISTP (CAR l)) (CAR l))
        (T (drept (CDR l)))
    )
)