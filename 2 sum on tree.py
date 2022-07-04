import sys

"""Given the root of a Binary Search Tree and a target number k, 
return true if there exist two elements in the BST such that their sum is equal 
to the given target.

 """


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# can be done using array , take inorder traversal into array and find two sum like usual
# can be done using inorder pre and inorder success but t(n) = nlogn, s(n) = 1
# can be done using BST Iterator which is most optimal, t(n) = n and s(n) = O(log n)
