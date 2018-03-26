
%2
%should probably redo, didn't fully understand 
twist(X,X) :- atomic(X).
twist([L|Lt],R) :- twist(L, A), twist(Lt, B), append(B, [A], R).

%3 
%had no intuition about cut being required, last case was unintuitive
mysqrt(N,R) :- helper(N, 0, N, R).

helper(N, A, B, R) :- M is div(A+B, 2), M*M > N, helper(N, M, B, R), !.
helper(N, A, B, R) :- M is div(A+B, 2)+1, M*M <= N, helper(N, A, M, R), !.
helper(_, A, B, M) :- M is div(A+B, 2). 

%4 

factorize(N, R) :- M is sqrt(N), helper2(N, 2, R).

helper2(N, M, [N]) :- M*M > N, !.
helper2(N, M, [M|Mt]) :- R is mod(N, M), R = 0, S is div(N,M), helper2(S, M, Mt), !.
helper2(N, M, L) :- R is mod(N, M), R > 0, O is M+1, helper2(N, O, L).

%5
% added an unnecessary base case that caused the program not to work
% (despite being an accurate case description afaik)
countall([], 0).
countall(X,1) :- atomic(X), not(X=[]).
countall([L|Lt], R) :- countall(L, T), countall(Lt, S), R is S+T.

%6
powerset(S,R) :- 
