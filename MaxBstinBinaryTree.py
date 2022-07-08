import sys

INT_MIN = -sys.maxsize - 1
INT_MAX = sys.maxsize
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


import sys

# Can be done using ValidateBst in O(n2) time


def maxSumBstRec(root: TreeNode):
    if root:
        res = [0] * 3
        resleft = maxSumBstRec(root.left)  # return Max, Min, Size
        resright = maxSumBstRec(root.right)
        if root.val > resleft[0] and root.val < resright[1]:  # Maxleft and minright
            res[0] = resright[1]  # max constraint is minright
            res[1] = resleft[0]  # min constraint is maxleft
            res[2] = (
                resleft[2] + resright[2] + 1
            )  # leftsize + rightsize + 1 = total size of bst
        else:
            res[0] = INT_MAX
            res[1] = INT_MIN
            res[2] = max(
                resleft[2], resright[2]
            )  # this is not a bst, size = max subtree size which is bst
        return res
    return [INT_MIN, INT_MAX, 0]


def maxSumBST(self, root: TreeNode) -> int:
    max = [-sys.maxsize - 1]
    maxSumBstRec(root, max)
    return max[0]
