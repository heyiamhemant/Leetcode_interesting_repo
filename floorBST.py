import sys


def floorInBST(root, X):
    # Write your Code here.
    floor = -sys.maxsize - 1
    while root:
        if root.data > X:  # look for element lesser than x
            root = root.left
        elif root.data < X:  # look for a better floor closer to x
            if root.data > floor:
                floor = root.data
            root = root.right
        else:  # floor is the element itself
            floor = root.data
            break
    return floor
