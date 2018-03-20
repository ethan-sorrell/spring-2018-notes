comp f g x = f(g x)

compose [] id = id
compose (f : fs) id = f (compose fs id)
compose' list id = foldr (.) id list

