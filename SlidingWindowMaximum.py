"""Hard

Topics
Companies

Hint
You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

 

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length"""

from collections import deque


class Solution:
    def maxSlidingWindow(self, nums, k) -> list[int]:
        # easily could figure out deque needs to be used
        # trick is that, in order to keep track of numbers getting flushed out, wee need to track the indices and not just the numbers
        dq = deque()
        res = []
        for i, num in enumerate(nums):
            # remove any indices that are expired and outside the k size of window
            while dq and dq[0] < i - k + 1:
                dq.popleft()
            # remove any number that doesn't fall into order of increasing,
            # that is any number is deque, should be greater than newly put number, to get max everytime.
            while dq and nums[dq[-1]] < nums[i]:
                dq.pop()
            dq.append(i)
            if i >= k - 1:
                res.append(nums[dq[0]])
        return res
