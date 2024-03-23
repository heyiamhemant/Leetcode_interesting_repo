"""Medium

Topics
Companies
There are n cities connected by some number of flights. You are given an array flights where flights[i] = [fromi, toi, pricei]
indicates that there is a flight from city fromi to city toi with cost pricei.

You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops. 
If there is no such route, return -1.

 

Example 1:


Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
Output: 700
Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.
Example 2:


Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
Output: 200
Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 2 is marked in red and has cost 100 + 100 = 200.
Example 3:


Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
Output: 500
Explanation:
The graph is shown above.
The optimal path with no stops from city 0 to 2 is marked in red and has cost 500.
 

Constraints:

1 <= n <= 100
0 <= flights.length <= (n * (n - 1) / 2)
flights[i].length == 3
0 <= fromi, toi < n
fromi != toi
1 <= pricei <= 104
There will not be any multiple flights between two cities.
0 <= src, dst, k < n
src != dst"""


# Bellman ford algorithm
# maintain the stops that you have encountered.
# Use a queue to perform a bfs on the graph
# if stops < k, then calculate the minimum on the distance array.
import collections as C


class Solution:
    def findCheapestPrice(
        self, n: int, flights: List[List[int]], src: int, dst: int, k: int
    ) -> int:
        """
        :type n: int
        :type flights: List[List[int]]
        :type src: int
        :type dst: int
        :type k: int
        :rtype: int
        """

        graph = C.defaultdict(list)
        # Create a adjacency list
        for flight in flights:
            fro, to, cost = flight
            graph[fro].append((to, cost))

        print(graph)

        # perform Bellman ford algo
        distance = [1e9 for i in range(n)]
        distance[src] = 0
        q = C.deque()  # intitialise with the src node, (stop, node, distance)
        q.append((0, src, 0))
        # visited = set()
        while q:
            nodeFro = q.popleft()
            stopFro, eleFro, dFro = nodeFro
            if stopFro > k:
                continue
            for adj in graph[eleFro]:
                eleTo, dTo = adj
                # print(f"for {eleFro} adj is {eleTo}, stop is {stopFro +1}")
                # print(f"distance to org = {distance[eleTo]} , new_distance = {dFro + dTo}")
                if dFro + dTo < distance[eleTo] and stopFro <= k:
                    distance[eleTo] = min(distance[eleTo], dFro + dTo)
                    q.append((stopFro + 1, eleTo, distance[eleTo]))
        # print(distance)
        if distance[dst] == 1e9:
            return -1
        return distance[dst]


sol = Solution()
n = 4
flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]]
src = 0
dst = 3
k = 1
print(sol.findCheapestPrice(n , flights, src, dst, k))
