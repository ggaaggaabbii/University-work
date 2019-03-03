;6.
;a) Write a function to test whether a list is linear.
;b) Write a function to replace the first occurence of an element E in a given list with an other element
;O.
;c) Write a function to replace each sublist of a list with its last element.
; A sublist is an element from the first level, which is a list.
; Example: (a (b c) (d (e (f)))) ==> (a c (e (f))) ==> (a c (f)) ==> (a c f)
; (a (b c) (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)
;d) Write a function to merge two sorted lists without keeping double values.



; a

; check_liniar (L1, L2, ...) =  { true, L = []
;                               { false, L1 = list
;                               { check_liniar(L2, ...), otherwise

(DEFUN check_liniar(L)
    (COND 
        ((NULL L) T)
        ((LISTP (CAR L)) nil)
        (T (check_liniar (CDR L)))
    )
)

; b

; replace_first_oc (L1, L2, ..., E, O) =  { [], L = []
;                                         { O |_| (L2, ...) , L1 = E
;                                         { replace_first_oc(L1, E, O) |_| (L2, ...), L1 = list AND L1 != replace_first_oc(L1, E, O)
;                                         { L1 |_| replace_first_oc(L2, ..., E, O), otherwise
(DEFUN replace_first_oc(L E O)
    (COND 
        ((NULL L) nil)
        ((EQUAL (CAR L) E) (CONS O (CDR L)))
        ((AND (LISTP (CAR L)) 
            (NOT (EQUAL (CAR L) (replace_first_oc (CAR L) E O)))
        )
            (CONS (replace_first_oc (CAR L) E O) (CDR L)))
        (T (CONS (CAR L) (replace_first_oc (CDR L) E O)))
    )
)

; c

; replace_list (L1, L2, ...) =  { nil, L = []
;                               { replace_list(L1) , L1 = list AND (L2, ...) = []
;                               { E,  (L2, ...) = []
;                               { replace_list(L2, ...), otherwise

(DEFUN replace_list (L)
    (COND
        ((NULL L) nil)
        ((AND (NULL (CDR L)) (LISTP (CAR L))) (replace_list (CAR L)))
        ((NULL (CDR L)) (CAR L))
        (T (replace_list (CDR L)))
    )
)

; replace_each_sublist (L1, L2, ...) =  { nil, L = []
;                                       { replace_list(L1) |_|  replace_each_sublist(L2, ...), L1 = list
;                                       { L1 |_|  replace_each_sublist(L2, ...), otherwise

(DEFUN replace_each_sublist (L)
    (COND
        ((NULL L) nil)
        ((LISTP (CAR L)) (CONS (replace_list (CAR L)) (replace_each_sublist (CDR L))))
        (T (CONS (CAR L) (replace_each_sublist (CDR L))))
    )
)

; d

; append_elem (L1, L2, ..., E) =  { [E], L = []
;                                 { L1 |_|  append_elem(L2, ..., E), otherwise

(DEFUN append_elem (L E)
    (COND 
        ((NULL L) (LIST E))
        (T (CONS (CAR L) (append_elem (CDR L) E)))
    )
)

; append_not_keeping_dups (L1, L2, ..., E) =  { append_elem(L1, L2, ..., E), replace_list(L) \= E
;                                             { [L1, L2, ...], otherwise


(DEFUN append_not_keeping_dups (L E)
    (COND 
        ((NOT (EQUAL (replace_list L) E)) (append_elem L E))
        (T L)
    )
)

; merge_lists (L1, L2, ..., l1, l2, ..., REZ) =  { REZ, L = [] AND l = []
;                                                { mergelists(L2, L3, ..., l1, l2, ..., append_not_keeping_dups(REZ, L1)), l = [] OR L1 < l1
;                                                { mergelists(L1, L2, ..., l2, l3, ..., append_not_keeping_dups(REZ, l1)), otherwise

(DEFUN merge_lists (L1 L2 REZ)
    (COND
        ((AND (NULL L1) (NULL L2)) REZ)
        ((NULL L1) (merge_lists L1 (CDR L2) (append_not_keeping_dups REZ (CAR L2))))
        ((NULL L2) (merge_lists (CDR L1) L2 (append_not_keeping_dups REZ (CAR L1))))
        ((< (CAR L1) (CAR L2)) (merge_lists (CDR L1) L2 (append_not_keeping_dups REZ (CAR L1))))
        (T (merge_lists L1 (CDR L2) (append_not_keeping_dups REZ (CAR L2))))
    )
)