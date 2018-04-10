d := #(5 2 9 11).
" lets creates an OrderedCollection from this array"
f := OrderedCollection new.
f addAll: d.

g := f collect: [:x | x*x].

"let's use inject to get the sum of elements in d"
dsum := d inject: 0 into: [:x :y | x+y].
dsum printNl.

"let's select elements in d that are greater than 8"
dselect := d select: [:x | x>8].
dselect printNl.

"now let's select all elements other than those greater than 8"
dreject := d reject: [:x | x>8].
dreject printNl.

"now let's give an example of a while loop, in this case 
it is also like a for loop"
k := 10.
[k<40] whileTrue: [k printNl. k:=k+5].

"now a look at how to use dictionaries"
h := Dictionary new.
h at: 'cat' put: 'animal'.
h at: 'hat' put: 'object'.
h at: 3 put: 'number'.
h at: #symbol put: 'language-construct'.
h printNl.

"now a look at a Bag, like a set, but each value has a count as well"
y := Bag new.
y add: 7.
y add: 7.
y add: 9 ; add: 9 ; add: 9.
y printNl.


