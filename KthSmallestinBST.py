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


def recursive(ptr: BinaryTreeNode, Q: list, k: int):
    if ptr and ptr.data < Q[len(Q) - 1]:
        Q.append(ptr.data)
        if len(Q) > k:
            Q.pop(0)
    if ptr.left:
        recursive(ptr.left, Q)
    if ptr.right:
        recursive(ptr.right, Q)


def KthSmallestElementBST(root: BinaryTreeNode, k: int):
    Q = []
    Q.append(sys.maxsize)
    recursive(root, Q, k)


# main
root = BinaryTreeNode(2)
root.left = BinaryTreeNode(1)
root.right = BinaryTreeNode(3)
root.right.right = BinaryTreeNode(4)
