"""1423. Maximum Points You Can Obtain from Cards
Medium

Topics
Companies

Hint
There are several cards arranged in a row, and each card has an associated number of points. The points are given in the integer array cardPoints.

In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.

Your score is the sum of the points of the cards you have taken.

Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

 

Example 1:

Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.
Example 2:

Input: cardPoints = [2,2,2], k = 2
Output: 4
Explanation: Regardless of which two cards you take, your score will always be 4.
Example 3:

Input: cardPoints = [9,7,7,9,7,7,9], k = 7
Output: 55
Explanation: You have to take all the cards. Your score is the sum of points of all cards.
 

Constraints:

1 <= cardPoints.length <= 105
1 <= cardPoints[i] <= 104
1 <= k <= cardPoints.length"""


class Solution:
    def maxScore(self, cardPoints: list[int], k: int) -> int:
        res = 0
        # approach : go do a sliding window on one end to the other end in a cyclic manner, so the ends - k + 1 elements are covered
        # and calculate the max points
        # figured it out on my own
        n = len(cardPoints)
        # start of the window
        start = n - k  # ends up at 0
        emptyWindow = 1
        wSum = 0
        if k == n:
            return sum(cardPoints)
        for i in range(start, start + k + 1): # i should be 0 at the end
            if emptyWindow:
                print("emptyWindow")
                # calculate the initial sum of the window
                for p in range(i, i + k):
                    wSum += cardPoints[p % n]
                emptyWindow = 0

            else:
                # handle the limiting conditions
                wSum += cardPoints[(i + k - 1) % n]
                wSum -= cardPoints[(i - 1 + n) % n]

            print(i, i+k, wSum)

            res = max(res, wSum)

        return res


sol = Solution()
cardPoints = [96, 90, 41, 82, 39, 74, 64, 50, 30]
k = 8
print(sol.maxScore(cardPoints, k))
