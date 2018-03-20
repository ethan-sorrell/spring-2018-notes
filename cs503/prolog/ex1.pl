inc(Y,Z) :- Z is Y+1.
double(Y,Z) :- Z is Y*2.
square(Y,Z) :- Z is Y*Y.

fact(0,1).
fact(N, R) :- N>0, M is N-1, fact(M, S), R is N*S.

fib(0,1).
fib(1,1).
fib(N,R) :- N>1, A is N-1, fib(A,X), B is N-2, fib(B, Y), R is X+Y.

fib2(N,R) :- help(N, 1, 1, R).
help(0,A,_,A).
help(N,A,B,R) :- N>0, M is N-1, C is A+B, help(M, B, C, R).

sum([], 0).
sum([H|T], R) :- number(H), sum(T,S), R is H+S.
sum([H|T], R) :- not(number(H)), sum(T,R).

map(_, [], []).
map(F, [H|T], [X|Y]) :- call(F,H,X), map(F,T,Y).

take(0,_,[]).
take(N, [H|T], [H|Z]) :- N>0, M is N-1, take(M,T,Z).

app([], L, L).
app([H|T1], L, [H|T2]) :- app(T1,L,T2).

