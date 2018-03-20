power(M, 0, 1).
power(M, 1, M).
power(M, N, X) :- O is M * M, L is N-1, power(O, L, X).

% not working properly
comb(N, 1, N).
comb(N, K, X) :- O is N-1, L is K-1, P is div(N, K), comb(O, L, Y), X is Y * P.
