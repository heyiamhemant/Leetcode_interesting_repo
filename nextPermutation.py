from os import *
from sys import *
from collections import *
from math import *


def nextPermutation(permutation, n) -> list[int]:
    i = 0
    if n > 1:
        i = n - 2
    else:
        return permutation
    point1 = -1
    point2 = -1
    while i >= 0:
        if permutation[i] < permutation[i + 1]:
            point1 = i
            break
        i -= 1
    if point1 == -1:
        return sorted(permutation)
    i = n - 1
    while i > point1:
        if permutation[i] > permutation[point1]:
            point2 = i
            break
        i -= 1
    permutation[point1], permutation[point2] = permutation[point2], permutation[point1]
    permutation[point1 + 1 : n] = reversed(permutation[point1 + 1 : n])
    return permutation


arr = [1, 2, 3, 4]
print(nextPermutation(arr, 4))
