male(bob).
male(joe).
male(sam).
male(brian).
male(will).
male(philip).

female(amy).
female(lucy).
female(sally).
female(betty).
female(donna).
female(jane).

married(bob,lucy).
married(joe,betty).
married(brian,amy).
married(sam,donna).
married(philip,sally).

spouse(X,Y) :- married(X,Y).
spouse(X,Y) :- married(Y,X).
husband(X,Y) :- male(X), spouse(X,Y).
wife(X,Y) :- female(X), spouse(X,Y).

parent(bob,amy).
parent(lucy,amy).
parent(brian,sally).
parent(amy,sally).
parent(joe,sam).
parent(betty,sam).
parent(donna,will).
parent(sam,will).
parent(philip,jane).
parent(sally,jane).
parent(brian,sally).
parent(amy,sally).

father(X,Y) :- male(X), parent(X,Y).
mother(X,Y) :- female(X), parent(X,Y).

child(X,Y) :- parent(Y,X).
son(X,Y) :- male(X), child(X,Y).
daughter(X,Y) :- female(X), child(X,Y).

sibling(X,Y) :- parent(Z,X), parent(Z,Y), not(X=Y).
brother(X,Y) :- male(X), sibling(X,Y).
sister(X,Y) :- female(X), sibling(X,Y).

grandparent(X,Y) :- parent(X,Z), parent(Z,Y).

grandchild(X,Y) :- grandparent(Y,X).

ancestor(X,Y) :- parent(X,Y).
ancestor(X,Y) :- parent(X,Z), ancestor(Z,Y).
descendant(X,Y) :- ancestor(Y,X).
