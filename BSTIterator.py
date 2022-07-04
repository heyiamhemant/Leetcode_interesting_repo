from operator import truediv
import sys
import os

"""Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
int next() Moves the pointer to the right, then returns the number at the pointer.
Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.

You may assume that next() calls will always be valid. That is, there will be at least a next number in the in-order traversal when next() is called."""


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class BSTIterator:
    Stack = []

    def __pushAll(self, top: TreeNode):
        # the next element is to the right
        # since this element is going to pop, add all elements to left chain of right node, holding next inorder sequence
        while top:
            self.Stack.append(top)  # add all elements to the left chain
            top = top.left

    def __init__(self, root: TreeNode):
        while root:
            self.Stack.append(root)
            root = root.left

    def next(self) -> int:
        top = self.Stack[len(self.Stack) - 1]
        # the next element is among the parents, so need to pop
        tmp = top
        self.Stack.pop()
        self.__pushAll(tmp.right)
        return tmp.val

    def hasNext(self) -> bool:
        if len(self.Stack) > 0:
            return True
        return False


# Your BSTIterator object will be instantiated and called as such:
# obj = BSTIterator(root)
# param_1 = obj.next()
# param_2 = obj.hasNext()
