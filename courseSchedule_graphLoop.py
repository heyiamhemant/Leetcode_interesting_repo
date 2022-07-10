# striver : NEED SELF DFS TO DETECT CYCLE IN DIRECTED GRAPH
def dfsDetectLoop(node, adj: list[list[int]], visited: list[int], dfsvisit):
    if visited[node] == 0:
        print("dfs", node, end=" ")
        visited[node] = 1
        dfsvisit[node] = 1
    res = False
    for i in adj[node]:
        if dfsvisit[i] == 1:
            return True
        res = dfsDetectLoop(i, adj, visited, dfsvisit)
    # when returning mark dfsvisit back to false
    dfsvisit[node] = 0
    return res


class Solution:
    def canFinish(self, numCourses: int, prerequisites) -> bool:
        adj = [[] for i in range(numCourses)]
        for i in prerequisites:
            adj[i[0]].append(i[1])
        for i in range(numCourses):
            # dfs with all courses as starting point , since no start course
            visited = [0 for i in range(numCourses)]
            dfsvisit = [0 for i in range(numCourses)]
            if dfsDetectLoop(i, adj, visited, dfsvisit):
                # loop is present, cant do course
                return False
            print()
        # loop not present, can do course
        return True
