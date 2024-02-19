"""File Search
Programming
Graph Data Structure & Algorithms
Medium
72.6% Success

56

15

Bookmark
Asked In:
Problem Description
 
 

You are given an assignment to sort out the files of your department today.

A file contains various records. Each record has an (ID, Parent ID).

To make your task easier, you decided to separate records into different sets.

If a set contains a record with (ID, Parent ID) - (X, Y), then both X and Y must be present in the set.

There are A records. You are also given a 2D array B of dimensions N x 2,

where each row is record's (ID, Parent ID).



You have to find the maximum number of sets you can divide the records into.



Problem Constraints
1 <= A, N <= 105
1 <= B[i][0], B[i][1] <= A
There can be duplicate records.
There can be two records (X, Y) and (Y, X).


Input Format
The first argument is the integer A.
The second argument is the 2D integer array B.


Output Format
Return a single integer denoting the maximum number of sets you can break the record into.


Example Input
Input 1:
A = 4
B = [[1, 2], [3, 4]]
Input 2:

A = 4
B = [[1, 2], [3, 4], [2, 4]]


Example Output
Output 1:
2
Output 2:

1"""


# ---> solved using union find algorithm
class UnionFind:
    parent = []
    rank = []

    def __init__(self, A, B):
        # n : number of nodes
        self.parent = [-1] * (A+1)
        self.rank = [0] * (A+1)
        print(self.parent,self.rank)
        for i in range(1, A + 1):
            self.parent[i] = i
            self.rank[i] = 0

    def Union(self, A, B):
        rootA, rootB = self.find(A), self.find(B)
        print(rootA, rootB)
        if rootA == rootB:
            return
        if self.rank[rootA] == self.rank[rootB]:
            self.rank[rootA] = self.rank[rootB] + 1
            self.parent[rootB] = rootA 
        elif self.rank[rootA] < self.rank[rootB]:
            self.parent[rootA] = rootB
        elif self.rank[rootA] > self.rank[rootB]:
            self.parent[rootB] = rootA
    def find(self, node):
        while node != self.parent[node]:
            #root = node
            node = self.parent[node]
            #self.parent[root] = node 
        return node


class Solution:
    def breakRecords(self, A, B):
        obj = UnionFind(A, B)
        for x, y in B:
            #print(f"unionfind ({x}, {y})")
            obj.Union(x, y)
        res = set()
        
        for i in range(1, A + 1):
            #print(f"{i} ={obj.parent[i]}")
            res.add(obj.find(i))
        return len(res)


sol = Solution()
B = [[1, 2], [2, 3], [3, 4]]
A = 4
A = 6
B = [
  [6, 1],
  [5, 6],
  [6, 1],
  [2, 1],
  [4, 3],
  [3, 1],
  [1, 2]
]
print(sol.breakRecords(A, B))
