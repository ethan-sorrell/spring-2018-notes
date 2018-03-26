% 1
% remember that the right-side of 'is' should only be known values
inner([], [], 0).
inner([Xh|Xt], [Yh|Yt], Z) :- inner(Xt, Yt, A), Z is A + Xh*Yh.

% 2
outer([], _, []).
outer([Xh|Xt], Y, [Zh|Zt]) :- helper(Xh, Y, Zh), outer(Xt, Y, Zt).

helper(_, [], []).
helper(X, [Y|Yt], [Z|Zt]) :- Z is X*Y, helper(X, Yt, Zt).

%3
scan([],[0]).
scan([L|Lt],[0|Qt]) :- scan(Lt, B), addAll(L, B, Qt).

addAll(_, [], []).
addAll(X, [Y|Yt], [A|At]) :- A is X+Y, addAll(X, Yt, At).

%6
prime(1).
prime(N) :- M is N-1, helper2(N, M).

helper2(_, 1).
helper2(N, M) :- R is mod(N,M), R > 0, L is M-1, helper2(N, L).

%7
% currently not working for some reason
selection_sort([], []).
selection_sort(X, [Y|Yt]) :- min(X, Y), remove(Y, X, Z), selection_sort(Z, Yt).

min([A], A).
min([A,B|C], M) :- A<B, min([A|C], M).
min([A,B|C], M) :- A=>B, min([B|C], M).

remove(A, [A|Lat], Lat).
remove(A, [La|Lat], [La|Lbt] :- not(A=La), remove(A, Lat, Lbt).

% selection_sort([X|Xt], [Y|Yt]) :- helper3(
