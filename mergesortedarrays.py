from os import *
from sys import *
from collections import *
from math import *


def ninjaAndSortedArrays(arr1, arr2, m, n):
    # Write your code here.
    for ele in arr2:
        arr1.append(ele)
    setSize = ceil((m + n) / 2)
    while setSize > 0:
        it = 0
        while it < m + n - 1 - setSize:
            if arr1[it] > arr1[it + setSize]:
                arr1[it], arr1[it + setSize] = arr1[it + setSize], arr1[it]
            it += 1
        if setSize == 1:
            setSize = 0
        setSize = ceil(setSize / 2)

        print(setSize, arr1)


arr1 = [1, 3, 6, 7, 8, 9]
arr2 = [2, 4, 5, 12]
ninjaAndSortedArrays(arr1, arr2, 5, 5)
print(arr1)
