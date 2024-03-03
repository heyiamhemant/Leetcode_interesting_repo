"""209. Minimum Size Subarray Sum
Medium
Topics
Companies
Given an array of positive integers nums and a positive integer target, return the minimal length of a 
subarray
 whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

 

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.
Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1
Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
 

Constraints:

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 104
 

Follow up: If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log(n))."""

# Solution approach : sliding window by trying to get a target of t in out sliding window. .
from math import floor
class Solution:
    def minSubArrayLen(self, target: int, nums) -> int:
        minWindow = float('inf')
        windowSum =0 
        left = 0
        right = 0
        for right in range(len(nums)):
            #print(right, left, windowSum, minWindow)
            # keep adding the rightmost element
            windowSum+=nums[right]
            while(windowSum >= target):
                # if window value exceeds the target, reduce it till it is less that target, while calculating minWindow
                minWindow = min(minWindow, right - left + 1)
                windowSum-=nums[left]
                left+=1

        if minWindow == float('inf') :
            return 0
        else:
            return floor( minWindow)


sol  = Solution()
nums  = [2, 3, 1, 2, 4, 3]

# nums = [1, 1, 1, 1, 1, 1, 1, 1]
target = 7
print(sol.minSubArrayLen(target ,nums))
