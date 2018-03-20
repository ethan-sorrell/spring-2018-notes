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

%4
child(A, B) :- parent(B, A).
grandchild(A, B) :- child(C, B), child(A, C).
