from os import *
from sys import *
from collections import *
from math import *

from sys import stdin, setrecursionlimit

setrecursionlimit(10**7)


def sort012(arr, n):

    # write your code here
    # don't return anything
    p0 = 0
    p1 = 0
    p2 = n - 1
    while p1 < p2:
        if arr[p1] == 0:
            arr[p1], arr[p0] = arr[p0], arr[p1]
            p1 += 1
            p0 += 1
        if arr[p1] == 1:
            p1 += 1
        if arr[p1] == 2:
            arr[p1], arr[p2] = arr[p2], arr[p1]
            p2 -= 1
    return arr


# taking inpit using fast I/O
def takeInput():
    n = int(input().strip())
    if n == 0:
        return list(), 0

    arr = list(map(int, stdin.readline().strip().split(" ")))

    return arr, n


def printAnswer(arr, n):

    for i in range(n):

        print(arr[i], end=" ")

    print()


# main

t = int(input().strip())
for i in range(t):

    arr, n = takeInput()
    sort012(arr, n)
    printAnswer(arr, n)
