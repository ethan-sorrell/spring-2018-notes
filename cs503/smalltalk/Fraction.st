"GNU Smalltalk code"


Number subclass: #MyFraction.
MyFraction instanceVariableNames: 'num den'.
MyFraction extend [
    num [ ^ num ]
    den [ ^ den ]
    num: n den: d [ num:=n. den:=d ]
    + f [ ^ MyFraction new num: (num * f den) + (den * f num) den: (den * f den) ]
    - f [ ^ MyFraction new num: (num * f den) - (den * f num) den: (den * f den) ]
    * f [ ^ MyFraction new num: (num * f num) den: (den * f den) ]
    / f [ ^ MyFraction new num: (num * f den) den: (den * f num) ] 
    = f [ ^ (num * f den) = (den * f num) ]
]

MyFraction extend [
    printOn: aStream [ 
	num printOn: aStream. 
	aStream nextPut: $/. 
	den printOn: aStream. 
	aStream cr ]
    reduce [ |g| 
	g := num gcd: den. 
	den < 0 ifTrue: [ g := 0 - g ]. 
	num := num / g. 
	den := den / g ]
    asFloat [ ^ num asFloat / den asFloat ]
]

f1 := MyFraction new num: 10 den: 4.
f2 := MyFraction new num: 15 den: 6.
f3 := MyFraction new num: -10 den: 4.
f4 := MyFraction new num: 15 den: -6.

f1 printOn: Transcript.
f2 printOn: Transcript.
f3 printOn: Transcript.
f4 printOn: Transcript.
Transcript cr.

f5 := f1 + f2.
f6 := f1 - f2.
f7 := f1 * f2.
f8 := f1 / f2.

f5 printOn: Transcript.
f6 printOn: Transcript.
f7 printOn: Transcript.
f8 printOn: Transcript.
Transcript cr.

f1 = f2 printOn: Transcript.  Transcript cr.
f2 = f3 printOn: Transcript.  Transcript cr.
f3 = f4 printOn: Transcript.  Transcript cr.
Transcript cr.

f1 asFloat printOn: Transcript.  Transcript cr.
f3 asFloat printOn: Transcript.  Transcript cr.
f5 asFloat printOn: Transcript.  Transcript cr.
f7 asFloat printOn: Transcript.  Transcript cr.
Transcript cr.

f1 reduce.
f2 reduce.
f3 reduce.
f4 reduce.

f1 printOn: Transcript.
f2 printOn: Transcript.
f3 printOn: Transcript.
f4 printOn: Transcript.
Transcript cr.

f5 reduce.
f6 reduce.
f7 reduce.
f8 reduce.

f5 printOn: Transcript.
f6 printOn: Transcript.
f7 printOn: Transcript.
f8 printOn: Transcript.
Transcript cr.
