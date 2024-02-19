"""Problem Description
 
 

Given a graph of A nodes. Also given the weighted edges in the form of array B.

You are also given starting point C and destination point D.

Also given are some extra edges in the form of vector E.

You need to find the length of the shortest path from C to D if you can use maximum one road from the given roads in E.

All roads are bidirectional.



Problem Constraints
1 <= A <= 100000

1 <= |B| <= 100000

1 <= C, D <= A

1 <= |E| <= 300

All lengths of the roads lie between 1 and 1000.



Input Format
First argument is the integer A.

Second argument is the vector of vectors B.

Third argument is the integer C.

Fourth argument is the integer D.

Fifth argument is the vector of vectors E.



Output Format
Return -1 if C is not reachable from D. Else return the shortest distance between them.



Example Input
Input 1:

 A = 3
B = [   [1, 2, 1]
        [2, 3, 2]
    ]
C = 1
D = 3
E = [   [1, 3, 2]
    ]
Input 2:

 A = 4
B = [   [1, 2, 1]
        [2, 3, 2]
        [3, 1, 4]
    ]
C = 1
D = 4
E = [   [1, 3, 2]
    ]


Example Output
Output 1:

 2
Output 2:

 -1


Example Explanation
Explanation 1:

 Use the direct edge from 1 to 3. It has shortest path from 1 to 3.
Explanation 2:

 4 cannot be reached from 1.
"""


# -----------> question to be solved using graph + dp

from queue import Queue


class Solution:
    # @param A : integer
    # @param B : list of list of integers
    # @param C : integer
    # @param D : integer
    # @param E : list of list of integers
    # @return an integer
    def solve(self, A, B, C, D, E):
        # create adjacency list
        def createAdjListAndExtraEdges(adjList, extraEdges):
            for fro, to, wt in B:
                # print(fro, to, wt)
                if fro in adjList:
                    adjList[fro].append(wt)
                else:
                    adjList[fro] = [wt]
            for to, fro, wt in E:
                edge = set({to,fro})
                extraEdges[edge] = wt

        adjList = {}
        extraEdges = {}
        createAdjListAndExtraEdges(adjList, extraEdges)

        # dijikstra algorithm
        visited = set()
        distance = [float("inf") for i in range(0, A + 1)]
        q = Queue()
        q.put(C)
        distance[C] = 0
        while not q.empty():
            ele = q.get()
            print(f"visiting {ele}")
            print(f"ele = {ele}, D = {D}")
            if ele == D:
                print("returning")
                return distance[ele]

            if ele in visited:
                continue
            visited.add(ele)
            print(f"visited= {visited}")
            print(ele, D, extraEdges)
            if ele in extraEdges:
                eFro, eWt = extraEdges[ele]
                distance[eFro] = min(distance[eFro], distance[ele] + eWt )

            if ele in adjList:
                for adj, wt in adjList[ele]:
                    q.put(adj)
                    distance[adj] = min(distance[adj], distance[ele] + wt)
            print(f"distance = {distance}")
        return -1


obj = Solution()
A = 3
B = [[1, 2, 1], [2, 3, 2]]
C = 1
D = 3
E = [[1, 3, 2]]
A = 7
B = [[1, 2, 1], [2, 3, 1], [3, 4, 1], [4, 5, 1], [5, 6, 1], [6, 7, 1]]
C = 1
D = 6
E = [[1, 4, 1]]

print(obj.solve(A, B, C, D, E))
