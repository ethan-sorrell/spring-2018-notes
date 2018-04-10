a := #(5 'hello' #(2 3 7) false).

a do: [:x | x printNl. x class printNl.].

a do: [:x | Transcript display: x ; tab ; display: x class ; cr].

b := Set new.
b add: 5 ; add: 2 ; add: 9 ; add: 11.

c := b collect: [:x | x*x]. 
"this creates a new set c, with the squares of the values in b"

c do: [:x | x printNl.].
