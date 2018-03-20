-- scheme-like implementation
len1 list = if null list then 0 else 1 + len1 (tail list)

-- a more standard haskell implementation using pattern matching
len2 [] = 0
len2 (_:t) = 1 + len2 t
