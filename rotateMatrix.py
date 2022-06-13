from os import *
from sys import *
from collections import *
from math import *


def rotateMatrix(mat, n, m):

    # Write your code here
    row, col = 0, 0
    count = 0
    while count < int(min(m, n) / 2):
        row = col = count
        prev = mat[row + 1][col]
        for i in range(count, n - count - 1):
            print(row, i)
            curr = mat[row][i]
            mat[row][i] = prev
            prev = curr
        col = n - 1 - count
        for i in range(count, m - count - 1):
            print(i, col)
            curr = mat[i][col]
            mat[i][col] = prev
            prev = curr
        row = m - 1 - count
        for i in range(n - count - 1, count, -1):
            print(row, i)
            curr = mat[row][i]
            mat[row][i] = prev
            prev = curr
        col = count
        for i in range(m - count - 1, count, -1):
            print(i, col)
            curr = mat[i][col]
            mat[i][col] = prev
            prev = curr
        count += 1


mat = [[1, 2, 3, 10], [4, 5, 6, 11], [7, 8, 9, 12], [1, 2, 3, 4]]
rotateMatrix(mat, 4, 4)
print(mat)
