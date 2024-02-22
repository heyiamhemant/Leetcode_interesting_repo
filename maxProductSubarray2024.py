"""152. Maximum Product Subarray
Solved
Medium
Topics
Companies
Given an integer array nums, find a 
subarray
 that has the largest product, and return the product.

The test cases are generated so that the answer will fit in a 32-bit integer.

 

Example 1:

Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
Example 2:

Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 

Constraints:

1 <= nums.length <= 2 * 104
-10 <= nums[i] <= 10
The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer."""


class Solution(object):
    def maxProduct(self, nums):
        """
        :type : nums: List[int]
        :rtype : int
        """
        # intuition is to perform actions whenever the product decreases when iterating through the array
        if len(nums) == 0:
            return 0
        max_prod = nums[0]
        prod_so_far = nums[0]
        min_so_far = nums[0]
        for i in range(1, len(nums)):
            old_prod_so_far = prod_so_far
            prod_so_far = max(
                nums[i] * prod_so_far, nums[i], min_so_far * nums[i]
            )  # Do you add this element to current subarray? or start a new subarray?
            # With min, we note it and integrate it to a suitable number to make it a bigger number later.
            min_so_far = min(min_so_far * nums[i], nums[i], old_prod_so_far * nums[i])
            # just the anti statement of prod_so_far
            # keep track of min subarray product found,
            # so it can match with another -ve number to make a bigger number, meanwhile the positives in between keep accumulating
            print(f"min_so_far = {min_so_far} prod_so_far = {prod_so_far}")
            max_prod = max(prod_so_far, max_prod)
            print(f"max_prod = {max_prod}")

        return max_prod


sol = Solution()
num = [2, 3, 0, -2, 4]
print(sol.maxProduct(num))
