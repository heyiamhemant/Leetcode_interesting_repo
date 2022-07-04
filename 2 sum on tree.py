import sys

"""Given the root of a Binary Search Tree and a target number k, 
return true if there exist two elements in the BST such that their sum is equal 
to the given target.

 """


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# can be done using array , take inorder traversal into array and find two sum like usual
# can be done using inorder pre and inorder success but t(n) = nlogn, s(n) = 1
# can be done using BST Iterator which is most optimal, t(n) = n and s(n) = O(log n)


class nextBstIterator:
    __Stack = []

    def __pushAll(self, top: TreeNode):
        while top:
            self.__Stack.append(top)
            top = top.left

    def __init__(self, root: TreeNode):
        while root:
            self.__Stack.append(root)
            root = root.left

    def next(self, root: TreeNode):
        tmp = self.__Stack[len(self.__Stack) - 1]
        self.__Stack.pop()
        self.__pushAll(tmp.right)
        return tmp.val

    def hasnext(self):
        if len(self.__Stack) == 0:
            return False
        return True


class beforeBstIterator:
    __Stack = []

    def __pushAll(self, top: TreeNode):
        while top:
            self.__Stack.append(top)
            top = top.right

    def __init__(self, root: TreeNode):
        while root:
            self.__Stack.append(root)
            root = root.right

    def before(self, root: TreeNode) -> int:
        tmp = self.__Stack[len(self.__Stack) - 1]
        self.__Stack.pop()
        self.__pushAll(tmp.left)
        return tmp.val

    def hasbefore(self) -> bool:
        if len(self.__Stack) == 0:
            return False
        return True


class Solution:
    def findTarget(self, root: TreeNode, k: int) -> bool:
        sum = k
        N = nextBstIterator(root)
        B = beforeBstIterator(root)
        BstSum = -1
        Next, Before = N.next(root), B.before(root)
        while Next != Before and N.hasnext() and B.hasbefore():
            BstSum = Next + Before
            if BstSum < sum:
                Next = N.next(root)
            elif BstSum > sum:
                Before = B.before(root)
            elif BstSum == sum:
                return True
        return False
