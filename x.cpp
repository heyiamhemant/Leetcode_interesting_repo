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
    print(root.data)
    sucparent, preparent = None, None
    Suc, Pre = None, None
    # successor
    while 1:
        print(root.data)
        if root.data < key and root.right:
            print("right")
            preparent = root
            root = root.right
        elif root.data > key and root.left:
            print("left")
            sucparent = root
            root = root.left
        else:
            print("here")
            if root.right:
                Suc = root.right
                while Suc.left:
                    Suc = Suc.left
            else:
                Suc = sucparent

            if root.left:
                Pre = root.left
                while Pre.right:
                    Pre = Pre.right
            else:
                Pre = preparent
            break
    if Suc:
        print(Suc.data, end=" ")
    else:
        print(-1, end=" ")
    if Pre:
        print(Pre.data)
    else:
        print(-1)


# main
root = BinaryTreeNode(2)
root.left = BinaryTreeNode(1)
root.right = BinaryTreeNode(3)
root.right.right = BinaryTreeNode(4)
predecessorSuccessor(root, 3)
