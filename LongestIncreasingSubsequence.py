"""Given an integer array nums, return the length of the longest strictly increasing 
subsequence
.

 

Example 1:

Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
Example 2:

Input: nums = [0,1,0,3,2,3]
Output: 4
Example 3:

Input: nums = [7,7,7,7,7,7,7]
Output: 1
 

Constraints:

1 <= nums.length <= 2500
-104 <= nums[i] <= 104
 

Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?"""
from sys import maxsize


class Solution(object):
    def lengthOfLIS(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        Lis = [1 for i in range(n)]
        for i in range(n - 2, -1, -1):  # from end to beginning
            for j in range(i + 1, n):
                # Update only if an increasing subsequence possible
                if nums[i] < nums[j]:
                    # Lis[i] denotes Longest increasing subsequence starting at index i
                    # eg. [4,10,3,8,9] , 0->1 | 0->2 | 0->3, 0->4 , is possible, but 1->anything is not possible, so Lis[1] = 1. and Lis[0] = max(all possible) 
                    Lis[i] = max(Lis[i], 1 + Lis[j])
        print(Lis)
        
        return max(Lis)


sol = Solution()
nums = [0, 1, 0, 3, 2, 3]
print(sol.lengthOfLIS(nums))
