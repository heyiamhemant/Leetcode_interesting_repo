"""169. Majority Element
Easy

Topics
Companies
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
 

Constraints:

n == nums.length
1 <= n <= 5 * 104
-109 <= nums[i] <= 109
 

Follow-up: Could you solve the problem in linear time and in O(1) space?"""
class Solution:
    def majorityElement(self, arr , n):
        # solved using the logic that only two elements in array can have more than n/3 elements
        # in moore's voting algorithm, the element that does not get cancelled, by other elements is a candidate to be majority.
        # e.g.  3 , 4 , 1 , 1 , 5 , 6 , 1 , 1
        # ele   3 , 3 , 1 , 1 , 1 , 1 , 1 , 1
        # count 1 , 0 , 1 , 2 , 1 , 0 , 1 , 2
        # means only candidate to be majority is 1, go by array again and verify if its count > len(arr) / 2.
        a , b = 0,0
        counta, countb = 0,0
        for ele in arr
            a = ele
            counta +=1
            if ele != a:
                