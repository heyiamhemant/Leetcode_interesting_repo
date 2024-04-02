"""You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list where edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of success of traversing that edge succProb[i].

Given two nodes start and end, find the path with the maximum probability of success to go from start to end and return its success probability.

If there is no path from start to end, return 0. Your answer will be accepted if it differs from the correct answer by at most 1e-5.

 

Example 1:



Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
Output: 0.25000
Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.
Example 2:



Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
Output: 0.30000
Example 3:



Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
Output: 0.00000
Explanation: There is no path between 0 and 2.
 

Constraints:

2 <= n <= 10^4
0 <= start, end < n
start != end
0 <= a, b < n
a != b
0 <= succProb.length == edges.length <= 2*10^4
0 <= succProb[i] <= 1
There is at most one edge between every two nodes"""

from sys import maxsize
class Solution(object):
    def maxProbability(self, n, edges, succProb, start_node, end_node):
        """
        :type n: int
        :type edges: List[List[int]]
        :type succProb: List[float]
        :type start_node: int
        :type end_node: int
        :rtype: float
        """
        E = len(edges)
        V = E + 1
        # perform a bellman ford algorithm

        # Bellman for is simply processing every edges and optimizing every distance , whenever we find a better value
        # so since for V vertices, there are E = V-1 edges

        distance = [maxsize for i in range(V)]
        distance[start_node] = 0
        for i in range(E):
            Fro, To = edges[i]
            # relax the edge
            if distance[Fro] + succProb[i] < distance[To]:
                distance[i] = succProb[i] + distance[Fro]

        # check negative cycles
        # Repeat the algo again, and if any distance optimizes, then negative edge present
        for i in range(E):
            Fro, To = edges[i]
            # check if get optimized
            if distance[Fro] + succProb[i] < distance[To]:
                distance[i] = - maxsize

        return distance[end_node]