"""
    Following is the TreeNode class structure

    class TreeNode:
        def __init__(self, data):
            self.data = data
            self.left = None
            self.right = None
"""
import sys


def findCeil(root, x):
    # Write your code here.
    ceil = sys.maxsize
    # assuming between inf and x
    while root:
        if root.data > x:
            if root.data < ceil:  # we found a closer ceil to x
                ceil = root.data
            root = root.left  # to find a closer ceil
        elif root.data < x:  # even for equal need to find a value greater than x
            root = root.right  # to find a number greater than x
        elif root.data == x:
            ceil = root.data
            break
    if ceil != sys.maxsize:
        return ceil
    return -1
