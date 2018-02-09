app [] list = list
app (h:t) list = h:(app t list)

-- this is an inefficient way to do reverse O(n^2)
rev [] = []
rev (h:t) = rev t ++ [h]

-- this is an efficient implementation
rev2 list = helper list [] where 
    helper [] list = list
    helper (h:t) list = helper t (h:list)
