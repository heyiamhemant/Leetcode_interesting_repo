# array of size N , return Kth smallest and largest element from the array
import heapq
import sys
import math
from typing import List


class Array:
    # private data members
    __arr = []
    __n = 0

    def __init__(self, n: int):
        self.n = n
        self.arr = [int(input()) for i in range(self.n)]

    def __del__(self):
        pass


def KthSmallestAndLargest(arr: List, n: int, k: int, sort: int = 0) -> List:
    # simple approch to sort and get the kth positions from each side
    if sort:
        arr.sort()
        return [arr[k], arr[n - k]]

    # without sorting
    # USING HEAPS!!
    heapq.heapify(arr)
    print(arr)
    for i in range(k - 1):
        heapq.heappop(arr)
        heapq.heapify(arr)

    return arr[0]


n = int(input("Enter n:"))

print("Enter Elements of array")
inst1 = Array(n)
k = int(input("Enter k :"))
# res = KthSmallestAndLargest(arr, n , k , 1)

res = KthSmallestAndLargest(inst1.arr, inst1.n, k)
print(res)
