# Definition for a binary tree node.
from sys import maxsize


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def traversal(root: TreeNode, MIN: int, MAX: int) -> bool:
    if root and root.val < MAX and root.val > MIN:
        left, right = True, True
        if root.left:
            left = traversal(root.left, MIN, root.val)
        if root.right:
            right = traversal(root.right, root.val, MAX)
        return left and right
    return False


class Solution:
    def isValidBST(self, root: TreeNode) -> bool:
        return traversal(root, -maxsize - 1, maxsize)
