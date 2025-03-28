# Binary-Search-Trees
This repository has a basic implementation of Binary Search Trees(BST) and another implementation using Red-Black Trees(RBT).
<br>
BSTs are just binary trees for which the left subtree of any node within the tree only contains values less than that node and the right subtree only contains values greater than that node. The main advantage of BSTs is the fast searching times which linked lists cannot provide. This is because at every step we split the search in half, kind of like binary search.

## Regular BST
For the regular BST implementaion I just made it so the values are inserted in the BST in the order they are inserted. If the nodes are inserted in the right way then for a balanced tree we'll get a searching time complexity of $O(log(N))$, where N is the number of nodes, however, we cannot guarantee a perfectly balanced tree which means that the actual time complexity is $O(H)$, where H is the height of the tree. In the worst case scenerio H is equal to N.

### Insertion
For insertion the asymptotic time complexity is just $O(H)$, where H is the tree height and in the worst case scenerio it is equal to N.

### Deletion
For deletion, we need to pick the inorder predecessor or inorder successor of the node to be deleted and substitute in that node so that the subtree connections are not destroyed. That is the case for a node having two children, if it has none, then we can just delete it and remove its parent link, and if it has one child then we can just replace it with its child. In the worst-case scenerio, the time complexity will be $O(H)$, where H is the height of the tree and in the worst-case it will be equal to N-1.


## Red-Black Trees
Red-Black Trees are self-balancing trees, so when inserting or deleting a node they do some extra operations to keep the tree approximately balanced. RBTs are not always perfectly balanced, however, they guarantee that the height of the tree will be at most 2 times the length of the path from the root to the closest leaf node. This means that the asymptotic time notation for the deletions and insertions will just happen in $O(H)$, but in this case we can say that $H=log(N)$ so it is just $O(log(N))$. The same goes for searching.

## How they work
RBTs are a bit more complicated in the way they work. For each node they include a color, either black or red. The rules of the tree are the following:
- The root and the NIL(nullptr) nodes are always black
- Any path from a node to any given leaf node has the same number of black nodes
- Red nodes cannot have red children


