# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def Dfs(self, root: TreeNode, visited: dict) -> bool:
        if not visited.has_key(root.val):
            visited[root.val] = 1
        else:
            return False
        if root.left:
            return self.Dfs(root.left)
        if root.right:
            return self.Dfs(root.right)
        return True

    def isValidBST(self, root: TreeNode) -> bool:
        visited = {}
        return self.Dfs(root, visited)
