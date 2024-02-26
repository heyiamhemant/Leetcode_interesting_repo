"""236. Lowest Common Ancestor of a Binary Tree
Medium
Topics
Companies
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes B and C as the lowest node in T that has both B and C as descendants (where we allow a node to be a descendant of itself).”

 

Example 1:


Input: A = [3,5,1,6,2,0,8,null,null,7,4], B = 5, C = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:


Input: A = [3,5,1,6,2,0,8,null,null,7,4], B = 5, C = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
Example 3:

Input: A = [1,2], B = 1, C = 2
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [2, 105].
-109 <= Node.val <= 109
All Node.val are unique.
B != C
B and C will exist in the tree."""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
class TreeNode:
    val = 0
    def __init__(self, val):
        self.val = val
        self.right = None
        self.left = None


class Solution:
    def lowestCommonAncestor(
        self, root: "TreeNode", p: "TreeNode", q: "TreeNode"
    ) -> "TreeNode":
        if not root:
            return None
        path1, path2, found = [], [], [False]
        visitMatch(
            root, p.val, path1, found
        )  # there is always one path from root to a node in a binary tree
        # print()
        found = [False]
        """print( "in orginal fn:", end = "" )
        print ([x.val for x in path1])
        print()"""
        visitMatch(
            root, q.val, path2, found
        )  # get the paths for both p and q and find whats common
        """print ([x.val for x in path2])
        print()"""
        lca = None
        for x in range(min(len(path1), len(path2))):
            if path1[x] == path2[x]:
                lca = path1[x]
        return lca


def visitMatch(A, target, path, found):
    if found[0] == True:
        return
    path.append(A)
    # [print(x.val, end = ",") for x in path]
    # print()
    if A.val == target:
        found[0] = True

    if A.left and not found[0]:
        visitMatch(A.left, target, path, found)
        if len(path) and not found[0]:
            path.pop()
    if A.right and not found[0]:
        visitMatch(A.right, target, path, found)
        if len(path) and not found[0]:
            path.pop()


A = TreeNode(3)
A.right = TreeNode(5)
A.left = TreeNode(4)
sol = Solution()
res = sol.lca(A, A.right, A)
if res:
    print(res.val)
else:
    print("NULL value")
