%2
twist(L, L) :- atomic(L).
twist([H|T], R) :- twist(H, S), twist(T, Q), append(Q, [S], R).

%3
mysqrt(N, R) :- helper2(N, 1, N, R).
helper2(N, M, _, []) :- O is M*M, O > N.
helper2(N, M, R) :- N+m
%6 powerset

%7
% redo
level(0, _, []).
level(N, X, []) :- N>0, atomic(X).
level(N, [H|T], C) :- N>0, M is N-1, level(M, H, D), level(N, T, E), append(D,E,C).

%8
helper(_, []).
helper(Item, [H|T]) :- not(Item=H), helper(Item, T).
distinct([H|T]) :- helper(H, T), distinct(T).

disjoint([H|T], L2) :- helper(H, L2), disjoint(T, L2).
