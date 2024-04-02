"""Medium

Topics
Companies
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. 
The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k.
Each hour, she chooses some pile of bananas and eats k bananas from that pile. 
If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

 

Example 1:

Input: piles = [3,6,7,11], h = 8
Output: 4
Example 2:

Input: piles = [30,11,23,4,20], h = 5
Output: 30
Example 3:

Input: piles = [30,11,23,4,20], h = 6
Output: 23
 

Constraints:

1 <= piles.length <= 104
piles.length <= h <= 109
1 <= piles[i] <= 109"""

# we know that h > piles.length. So, the binary search will range from min(piles) to max(piles). For each value we check if koko,
# could eat all the piles within h hours or not.
import math as M


class Solution:
    def minEatingSpeed(self, piles, h):
        """
        :type piles: List[int]
        :type h: int
        :rtype: int
        """
        n = len(piles)
        low = 1
        high = max(piles)
        minK = high
        while low <= high:

            mid = (low + high) // 2

            kokoEatTime = kokoAteBananas(piles, mid)
            # print(low,high, mid, kokoEatTime)
            if kokoEatTime > h:
                low = mid + 1
            elif kokoEatTime <= h:
                high = mid - 1
        return low


def kokoAteBananas(piles, k):
    hour = 0
    for pile in piles:
        hour += M.ceil(pile / k)
    return hour
