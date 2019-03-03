;1. For a given tree of type (1) return the path from the root node to a certain given node X.
;(A 2 B 0 C 2 D 0 E 0)
;get_path (tree, node, path) = { nil, tree == nil
;                              { reverse(path |_| tree.root), tree.root == node
;                              { get_path(tree.root.child, node, path |_| tree.root), for every child

(DEFUN reverse_list(L)
    (COND
        ((NULL L) nil)
        (T (APPEND (reverse_list (CDR L)) (LIST (CAR L))))
    )
)

(DEFUN eliminate_zeroes(Path NrOfSubtrees)
    (COND 
        ((NULL Path) nil)
        ((EQUAL (CAR NrOfSubtrees) 0) (eliminate_zeroes (CDR Path) (CDR NrOfSubtrees)))
        (T (CONS (CAR Path) (eliminate_zeroes (CDR Path) (CDR NrOfSubtrees))))
    )
)

(DEFUN get_path(Tree Node Path NrOfSubtrees)
    (COND 
        ((NULL Tree) nil)
        ((EQUAL (CAR Tree) Node) (APPEND (reverse_list (eliminate_zeroes Path NrOfSubtrees)) (LIST Node)))
        ((= (CAR NrOfSubtrees) 0) (get_path (CDR (CDR Tree)) Node (CONS (CAR Tree) (CDR Path)) (CONS (CAR (CDR Tree)) (CDR NrOfSubtrees))))
        (T (get_path (CDR (CDR Tree)) Node (CONS (CAR Tree) Path) (CONS (CAR (CDR Tree)) (CONS (- (CAR NrOfSubtrees) 1) (CDR NrOfSubtrees)))))
    )
)
; (get_path '(A 3 B 0 C 1 G 0 D 2 E 1 H 0 F 1 L 0) 'L 'nil '(1))
;4. Write a function that returns the product of numeric atoms in a list, at any level.
;
;prod(l, p) = { p, l = nil
;             { prod (l2, .., p * prod(l1, 1)), l1 = list
;             { prod (l2, .., p * l1), l1 - number
;             { prod (l2, .., p), otherwise


(DEFUN prod(L)
    (COND
        ((NULL L) 1)
        ((NUMBERP L) L)
        ((ATOM L) 1)
        ((LISTP L) (APPLY '* (MAPCAR 'prod L)))
    )
)
