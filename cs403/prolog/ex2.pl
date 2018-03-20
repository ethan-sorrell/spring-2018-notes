rev([],[]).
rev([H|T], Z) :- rev(T,X), append(X,[H], Z).

rev2(L,Z) :- helper(L, [], Z).
helper([], Z, Z).
helper([H|X], Y, Z) := helper(X, [H|Y], Z).

mem(H, [H|_]).
mem(X, [_|T]) :- mem(X, T).

flat([], []).
flat(X, [X]) :- atomic(X), not(X=[]).
flat([H|T], L) :- flat(H,X), flat(T,Y), append(X,Y,L).

del(H, [H|T], T).
del(X, [H|T], [H|Z]) :- del(X,T,Z).

permute([], []).
permute(L, [H|T]) :- member(H, L), del(H,L,Y), permute(Y,T).

ascend([]).
ascend([_]).
ascend([X,Y|T]) :- X=<Y, ascend([Y|T]).

perm_sort(L,X) :- permute(L, X), ascend(X).

repeat(X, L) :- L=[X|L].

make_circ_list(L, C) :- append(L, C, C).

bubblesort([H|T] , [HS1, HS2 | S]) :- member(H,S), HS1 < HS2, bubblesort(T, [HS2|S]).
bsort([], S, S).
bsort([H|T], [Ah| At], S) :- H < Ah, bsort(T, At, S).
bsort([H|T], [Ah| At], S) :- H =< Ah, 

