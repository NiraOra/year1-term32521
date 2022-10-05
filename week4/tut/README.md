## Binary Search tree

- bigger values to the right of the particular node; vice versa for smaller values (in comparison to the node at the point)

- sorted/reverse sorted trees are just linked lists 

Traversals
![](https://cgi.cse.unsw.edu.au/~cs2521/22T3/tut/4/bst-traversals/bst-traversals.svg)
1. in order: sorted
2. Pre order: checks the current node; goes to left (most) then to the right
3. Post order: print the left tree lowermost values; then levels; then go to the right and do the same, then the root node
4. Level order: prints the first level; then the second level; then the third level till you reach height - 1.

- Trees that have the property that their in-order traversal is the saem as their pre-order traversal?: sorted tree; one or two entry/ies

<u>Tree rotation:</u>
![](https://cgi.cse.unsw.edu.au/~cs2521/22T3/tut/4/rotations-1/rotations-1-1.svg)

if A and B with left and right extensions exist;
- right rotation: A's right becomes B's left
- left rotation: B's left becomes A's right

ie; in the picture, a left rotation would mean that 6's right would be what 10's left is: so 8 yadda yadda is linked to 6's right

another example from the same example: 
- a right rotation from 10 to 8 would mean that 8's right would be 10 then 12; and 10's left would be what was once 8's right