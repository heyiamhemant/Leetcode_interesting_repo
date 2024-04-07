"""Medium

Topics
Companies
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

 

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.
 

Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size."""


class Solution:
    def topKFrequent(self, nums: list[int], k: int) -> list[int]:
        res = [0 for i in range(k)]
        # has to be better than O(nlogn), that is sorting
        # approach: using map, still how will we know if one number comes before the other?
        # can we use heap ? it is possible to pair {number , count} and then use key as the count for heap, the t(n) will be O(klogn)
        # we can also use a bucket, which maps from (count) -> [list of elements], as this count(i) < len(array).

        n = len(nums)
        bucket = [
            [] for i in range(n + 1)
        ]  # map from count -> list of elements with that count
        count = {}

        #  count every element how many times do each element occur?
        for num in nums:
            if num in count:
                count[num] += 1
            else:
                count[num] = 1

        # print(count)
        res = []
        # put every element in a bucket, all elements than occur n times in bucket n
        for ele, c in count.items():
            bucket[c].append(ele)

        # print(bucket)

        # add to the result the most frequent k elements
        countToK = 0
        for i in range(n, 0, -1):
            for j in range(len(bucket[i])):
                if countToK < k:
                    countToK += 1
                    res.append(bucket[i][j])
        return res
