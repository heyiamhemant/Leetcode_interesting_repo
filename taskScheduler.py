"""You are given an array of CPU tasks, each represented by letters A to Z, and a cooling time, n. Each cycle or interval allows the completion of one task. Tasks can be completed in any order, but there's a constraint: identical tasks must be separated by at least n intervals due to cooling time.

​Return the minimum number of intervals required to complete all tasks.

 

Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2

Output: 8

Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.

After completing task A, you must wait two cycles before doing A again. The same applies to task B. In the 3rd interval, neither A nor B can be done, so you idle. By the 4th cycle, you can do A again as 2 intervals have passed.

Example 2:

Input: tasks = ["A","C","A","B","D","B"], n = 1

Output: 6

Explanation: A possible sequence is: A -> B -> C -> D -> A -> B.

With a cooling interval of 1, you can repeat a task after just one other task.

Example 3:

Input: tasks = ["A","A","A", "B","B","B"], n = 3

Output: 10

Explanation: A possible sequence is: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B.

There are only two types of tasks, A and B, which need to be separated by 3 intervals. This leads to idling twice between repetitions of these tasks.

 

Constraints:

1 <= tasks.length <= 104
tasks[i] is an uppercase English letter.
0 <= n <= 100"""

import heapq as H
from collections import deque

"""How to solve?
First we need to realise how we can have the minimum cycles to complete all the tasks.
Answer is if we schedule the highest freq tasks first--->> we get min time.
Next we convert the jobs to their frequencies.
We use a max_Heap to always get the highest frequency job and then we execute it, we reduce its freq by 1 and add it to a queue.
We also add when the task can be taken up again to the queue.
Next time we check in the queue, if the job can be taken up we add it to the heap."""
class Solution(object):
    def leastInterval(self, tasks, n):
        """
        :type tasks: List[str]
        :type n: int
        :rtype: int
        """
        # convert tasks to their number of occurrences
        tasks.sort()
        prev = tasks[0]
        jobs = [0]
        j = 0
        for task in tasks:
            if task == prev:
                jobs[j] += 1
            else:
                j += 1
                jobs.append(1)
            prev = task

        for i in range(len(jobs)):
            jobs[i] = -jobs[i]
        H.heapify(jobs)
        q = deque()
        t = 0
        #print(jobs)
        while jobs or q:
            #print(f"time = {t}")
            if q:
                j, tJob = q[0]
                if t >= tJob:
                    #print(f"t = {t}, tJob = {tJob} ")
                    q.popleft()
                    #print(f"scheduled {j}")
                    H.heappush(jobs, j)
                    #print(f"jobs = {jobs},  q = {q}")
            if jobs:
                curJob = H.heappop(jobs)
                #print(f"curJob = {curJob}")
                remainingJob = curJob + 1
                if remainingJob != 0:
                    #print(f"added to queue {remainingJob}, {t+n}")
                    q.append((remainingJob, t + n + 1))
                    #print(f"jobs = {jobs},  q = {q}")

            t += 1
            if t > 15:
                break
        return t


sol = Solution()
tasks = ["A", "B", "A", "C", "A", "B"]
n = 2
tasks = ["A", "A", "A", "B", "B", "B"]
n = 2
print(sol.leastInterval(tasks, n))
