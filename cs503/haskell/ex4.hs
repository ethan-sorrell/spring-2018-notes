-- data keyword denotes a more primitive data type
data Color = Red | Green | Blue | Yellow

data Suit = Clubs | Diamonds | Hearts | Spades

data Rank = Ace | Two | Three | Four | Five | Six | Seven | Eight | Nine | Ten | Jack | Queen | King

-- type keyword denotes a derived data type like a struct
type Card = (Rank, Suit)

getsuit :: Card -> Suit -- optional
getsuit (_,s) = s

getrank :: Card -> Rank -- optional
getrank (r,_) = r
