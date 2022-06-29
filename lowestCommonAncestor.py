# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:
    def lowestCommonAncestor(
        self, root: "TreeNode", p: "TreeNode", q: "TreeNode"
    ) -> "TreeNode":
        low = p.val
        high = q.val
        p = root
        q = root
        lca = None
        while (p and p.val != low) or (q and q.val != high):
            if p and q and p == q:
                lca = p
            if p:
                # print(p.val, end = ' ')
                if p.val < low:
                    p = p.right
                elif p.val > low:
                    p = p.left
            if q:
                # print(q.val)
                if q.val > high:
                    q = q.left
                elif q.val < high:
                    q = q.right

        return lca
