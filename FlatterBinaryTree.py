"""Given the root of a binary tree, flatten the tree into a "linked list":

The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
The "linked list" should be in the same order as a pre-order traversal of the binary tree."""
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def reversePreorderLink(root: TreeNode, tolink: TreeNode):
    # right , left , node
    if root:
        reversePreorderLink(root.right, tolink)
        reversePreorderLink(root.left, tolink)
        # pass by reference, to link the previous node in rev preorder
        root.right = tolink
        root.left = None
        tolink = root


def flatten(self, root: TreeNode) -> None:
    """
    Do not return anything, modify root in-place instead.
    """
    # Try reverse preorder to do this
    reversePreorderLink(root, None)
