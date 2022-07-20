class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        adj = [[] for i in range(numCourses)]
        visited = [0 for i in range(numCourses)]
        indegrees = [0 for i in range(numCourses)]
        tstack = [] # to hold the toposort
        for i in prerequisites:
            adj[i[0]].append(i[1])
            indegrees[i[1]]+=1
        def bfs(start):
            queue = []
            for i in range(numCourses):
                if indegrees[i]==0:
                    queue.append(i)
            while len(queue) > 0:
                # visit node and add to tsort stack
                node = queue.pop(0)
                visited[node] =1
                tstack.append(node)
                for i in adj[node]:
                    # reduce indegrees by one for all adjacent, because node removed
                    indegrees[i]-=1
                    if indegrees[i]==0:
                        queue.append(i)
        for i in range(numCourses):
            if not visited[i]:
                bfs(i)
        if len(tstack) != numCourses:
            return False
        # map the indexes
        tsort = {}
        index = 0
        print(tstack)
        for i in tstack:
            tsort[i] = index
            index+=1
        print(tsort)
        for i in range(numCourses):
            for j in adj[i]:
                if tsort[j] < tsort[i]:
                    return False
        return True