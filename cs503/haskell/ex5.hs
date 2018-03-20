-- Circle Float denotes that circle has an attribute that is a floating point
-- Rectangle Float Float denotes that Rectangle has 2 floating point attributes
data Shape = Circle Float | Rectangle Float Float
            deriving (Eq, Ord, Show, Read)

-- Now we can define functions on this type
area (Circle radius) = pi * radius^2
area (Rectangle length width) = length * width

-- a redefinition the list type
data List a = Nil | Cons a (List a) 
    deriving (Eq, Ord, Show, Read)

len Nil = 0
len (Cons _ xs) = 1 + len xs

app Nil ys = ys
app (Cons x xs) list2 = Cons x (app xs list2)

rev Nil = Nil
rev (Cons x xs) = app (rev xs) (Cons x Nil)
