%check the equality of 2 sets


%find(L - list, E - integer, R - boolean, output)
%flow model(i, i) - check if the element is insede the list

find([E|_], E).
find([_|T], E):-find(T, E).

%isSet(L - list, R - boolean, output)
%flow model(i) - check if the list is a set
isSet([]).
isSet([H|T]):-not(find(T, H)),
    isSet(T).

%hasAllElems(L1 - list, L2 - list, R - boolean, output)
% flow model(i, i) - returns whether or not the first list contains all
% the elements from the second list
hasAllElems(_, []).
hasAllElems(L, [H|T]):-find(L, H),
    hasAllElems(L, T).

%eqSets(L1 - list, L2 - list, R - boolean, output)
% flow model(i, i) - returns true if the 2 lists are sets and are
% equal
eqSets(L1, L2):-isSet(L1),
    isSet(L2),
    hasAllElems(L1, L2),
    hasAllElems(L2, L1).

%get the nth element from a list
%flow model(i, i, o) - returns the nth element
%flow model(i, i, i) - checks if the given result is correct

nElem([H|_], N, H):-N =:= 1,
    !.
nElem([_|T], N, R):-Nr is N-1,
    nElem(T, Nr, RT),
    R is RT,
    !.

