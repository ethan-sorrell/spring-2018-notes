fib 0 = 1
fib 1 = 1
fib n = fib (n-1) + fib (n-2)

-- optimized fib function
-- in braces+semicolons then whitespace only (the standard)
fib2 n = helper n 1 1 where 
    {
    helper 0 a _ = a;
    helper n a b = helper (n-1) b (a+b); 
    }

fib3 n = helper n 1 1 where 
    helper 0 a _ = a
    helper n a b = helper (n-1) b (a+b);

fib4 n = let
        helper 0 a _ = a
        helper n a b = helper (n-1) b (a+b)
    in helper n 1 1
