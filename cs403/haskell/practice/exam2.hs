-- this function has type ((a->b), (c->d), (e->f) -> (a, c, e) -> (b, d, f)
apply3 (a, b, c) (d, e, f) = ((a d), (b e), (c f))

-- this function has type a -> (a->a) -> Int -> [a]
series s f 0 = []
series s f n = 2 : (series (f s) f (n-1))

-- this function has type Int -> Int
mysqrt n = mysqrt' n 0 n
 where mysqrt' n a b = let 
        mid = div (a+b) 2 in
        if m^2 > n then mysqrt' n a (mid-1)
        else if (m+1)^2 <= n then mysqrt' n (mid+1) b
        else m

-- this function has type Int -> [Int]
factorize n = factorize' n 2
    where factorize' n m = 
            if m^2 > n then [n]
            else if mod n m == 0 then m : factorize' (div n m) m
            else factorize' n (m+1)

-- this function has type [a] -> [[a]]
powerset [] = []
powerset (x : xs)  = (map (x:) s) ++ x
    where s = powerset xs

-- this function has type (a->a) -> [a] -> a
foldr' op (x:xs) =  x op foldr' op xs

foldl' op (x0:x1:xs) = foldl' (x0 op x1) xs

-- this function has type (a->b) -> Tree a -> Tree b
data Tree a = Leaf a | Branch [Tree a] 
mapall f Leaf a = Leaf (f a)
mapall f Branch [xs] = Branch (map (mapall f) xs) 

-- this function has type Int -> Tree a -> [a]
level 0 Leaf a = a
level n Branch [x:xs] = level (n-1) x ++ level n (Branch xs)

-- this function has type Int -> [[a]] -> [a]
column k t = [ x!!k | x<-t ]

diagonal t = [ x!!k | (x,k) <- zip(t,[0..])]

-- this function has type a -> [a] -> Int
count a (x:xs) = count' a (x:xs) 0
    where count' a [] n = n;
            count' a (x:xs) n = 
            if x == a then count' a xs (n+1)
            else count' a xs n

data Natural = Zero | Successor Natural

add a Zero = a
add a Successor b = add (Sucessor a) b

mult a Zero = Zero
mult a Successor b = add a (mult a b)


