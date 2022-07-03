import sys

#''
#    ------- Binary Tree node structure -------
class BinaryTreeNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

    def __del__(self):
        if self.left:
            del self.left
        if self.right:
            del self.right


#'''


def predecessorSuccessor(root, key):

    # Write your code here.
    # inorder successor
    suc, pre = sys.maxsize, -sys.maxsize - 1
    ptr = root
    while ptr:
        if key >= ptr.data:
            ptr = ptr.right
        elif key < ptr.data:
            if ptr.data < suc:
                suc = ptr.data
            ptr = ptr.left
    ptr = root
    while ptr:
        if key <= ptr.data:
            ptr = ptr.left
        elif key > ptr.data:
            if ptr.data > pre:
                pre = ptr.data
            ptr = ptr.right
    if pre == -sys.maxsize - 1:
        pre = -1
    if suc == sys.maxsize:
        suc = -1
    return [pre, suc]


# main
root = BinaryTreeNode(2)
root.left = BinaryTreeNode(1)
root.right = BinaryTreeNode(3)
root.right.right = BinaryTreeNode(4)
predecessorSuccessor(root, 4)
predecessorSuccessor(root, 1)
predecessorSuccessor(root, 2)
predecessorSuccessor(root, 3)
