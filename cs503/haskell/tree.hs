data BinaryTree a = Null | BinaryNode a (BinaryTree a) (BinaryTree a)
    deriving (Eq, Ord, Show, Read)

inorder Null = []
inorder (BinaryNode x left right) = inorder left ++ [x] ++ inorder right

binarytree1 = BinaryNode 20 (BinaryNode 10 Null Null) (BinaryNode 30 Null Null)
binarytree2 = BinaryNode 40 
    (BinaryNode 20 (BinaryNode 10 Null Null) (BinaryNode 30 Null Null))
    (BinaryNode 60 (BinaryNode 50 Null Null) (BinaryNode 70 Null Null))

binarytree3 = BinaryNode 'd' 
    (BinaryNode 'b' (BinaryNode 'a' Null Null) (BinaryNode 'c' Null Null))
    (BinaryNode 'f' (BinaryNode 'e' Null Null) (BinaryNode 'g' Null Null))
------------------------------------
--

data Tree a = Node a [Tree a]
    deriving (Eq, Ord, Show, Read)

preorder (Node x ts) = x: foldl (++) [] [preorder t | t <- ts]

postorder (Node x ts) = foldl (++) [] [postorder t | t <- ts] ++ [x]

tree1 = Node 20 [Node 10 [], Node 30 []]
tree2 = Node 40 [Node 10 [Node 20 []], Node 30 [], Node 50 [], Node 70 [ Node 60 []]]
