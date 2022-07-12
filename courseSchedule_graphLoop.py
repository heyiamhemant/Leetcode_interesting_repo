# striver NEED SELF DFS TO DETECT CYCLE IN DIRECTED GRAPH

# actually this is topological sort, if we add the node to stack when returning


class Solution:
    def canFinish(self, numCourses: int, prerequisites) -> bool:
        adj = [[] for i in range(numCourses)]
        visited = [0 for i in range(numCourses)]
        # dfsvisit = [0 for i in range(numCourses)]
        for i in prerequisites:
            adj[i[0]].append(i[1])

        def dfsDetectLoop(node):
            print(node)
            visited[node] = 1
            for i in adj[node]:

                if visited[i] == 1:  # in this recursion visiting twice
                    return True
                if dfsDetectLoop(i):
                    return True
            visited[node] = 0
            adj[node] = []
            return False

        for i in range(numCourses):
            if dfsDetectLoop(i):
                return False
        return True
