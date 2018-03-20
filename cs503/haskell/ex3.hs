-- infinite list using list comprehension
evens = [x | x<-[0..], mod x 2 == 0]
odds = [x | x<-[0..], mod x 2 /= 0]
-- infinite list using recursion
evens' = 0 : map (+2) evens'
odds' = 1 : map (+2) odds'
powers_of_2 = 1 : map (*2) powers_of_2

factlist = map fact [0..] where
    fact 0 = 1
    fact n | n>0 = n*fact(n-1)

factlist' = 1 : zipWith (*) factlist' [1..]

fiblist = 1 : 1 : zipWith (+) fiblist (tail fiblist)

primelist = checkdiv [2..] where
    checkdiv (p:xs) = p : checkdiv [x | x<-xs, mod x p > 0]

-- defining new data types
data Color = Red | Green | Blue | Yellow 
    -- defines a new types that takes 4 possible values
    -- this is an enumerated type

