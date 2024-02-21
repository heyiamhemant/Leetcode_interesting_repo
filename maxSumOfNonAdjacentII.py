"""213. House Robber II
Medium
Topics
Companies
Hint
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

 

Example 1:

Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
Example 2:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
Example 3:

Input: nums = [1,2,3]
Output: 3
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 1000
"""

# same as previous question with variation that first house is connected to the last one.


class Solution(object):
    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # calculate to variations of dp one with last included and first excluded, another with first included and last excluded
        n = len(nums)
        if n == 1:
            return nums[0]
        elif n == 2:
            return max(nums[0], nums[1])
        dp = [0] * n
        # exclude last house
        dp[0] = nums[0]
        dp[1] = max(nums[1],nums[0])
        for i in range(2,n-1):
            dp[i] = max(nums[i] + dp[i-2], dp[i-1])

        #print(dp[n-2])
        print(f"dp1= {dp}")
        res1 = dp[n-2]
        
        #exclude first house
        dp = [0] * n
        dp[0] = 0
        dp[1] = nums[1]
        for i in range(2,n):
            dp[i] = max(nums[i]+ dp[i-2], dp[i-1])
        res2 = dp[n-1]
        print(f"dp2= {dp}")
        return max(res1,res2)

nums = [2,1,1,2]
# nums = [1, 3, 1, 3, 100]
#nums = [4, 1, 2, 7, 5, 3, 1]
sol = Solution()
print(sol.rob(nums))
