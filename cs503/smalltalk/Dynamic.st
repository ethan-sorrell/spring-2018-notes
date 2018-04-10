"adds method m and n to Object"
Object extend [
    m [^1] 
    n [^self m] "note that self refers to the calling class, even if this method is inheritted"
]

"creates new subclass A of object with methods p and q"
Object subclass: A [
    p [^self n]
    q [^super m] "note that super is more static than self and will behave the same
    even if the method is inherrited"
]

"overrides the m method"
A subclass: B [
    m [^2]
]

"overrides p and q methods"
B subclass: C [
    p [^super q]
    q [^super p]
]

"overrides m method"
C subclass: D [
    m [^3]
]

"overrides n method"
D subclass: E [
    n [^4]
]

x:=Array new: 5.
x at: 1 put: A new; at: 2 put: B new; at: 3 put: C new; at: 4 put: D new; at: 5 put: E new.
1 to: 5 do: [:j | y:=x at: j. Transcript display: y m; display: y n; display: y p; display: y q; cr].
