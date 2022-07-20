# striver NEED SELF DFS TO DETECT CYCLE IN DIRECTED GRAPH


class Solution:
    def canFinish(self, numCourses: int, prerequisites) -> bool:
        adj = [[] for i in range(numCourses)]
        visited = [0 for i in range(numCourses)]
        dfsvisit = [0 for i in range(numCourses)]
        for i in prerequisites:
            adj[i[0]].append(i[1])
        # USING TOPOLOGICAL SORT DFS
        stack = []
        for i in prerequisites:
            adj[i[0]].append(i[1])
        def dfstoposort(node):
            print(node)
            visited[node] = 1
            #dfsvisit[node] = 1
            for i in adj[node]:
                if not visited[i] :
                    dfstoposort(i)
            stack.append(node)
        
        for i in range(numCourses):
            if not visited[i]:
                dfstoposort(i)
        tsort = {}
        i = 0
        while len(stack) > 0:
            tsort[stack[-1]] = i
            i+=1
            stack.pop()
        print(tsort)
        for i in range(numCourses):
            for j in adj[i]:
                if tsort[i] >= tsort[j]:
                    return False
        return True
        '''
        def dfsDetectLoop(node):
            visited[node] = 1
            dfsvisit[node] = 1
            for i in adj[node]:
                if not visited[i] :
                    if dfsDetectLoop(i):
                        return True
                elif dfsvisit[i]:
                    return True
            dfsvisit[node] = 0
            return False
            
        for i in range(numCourses):
            if not visited[i] and dfsDetectLoop(i):
                return False
        return True'''