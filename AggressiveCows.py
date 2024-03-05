"""AGGRCOW - Aggressive cows
#binary-search
Farmer John has built a new long barn, with N (2 <= N <= 100,000) stalls. The stalls are located along a straight line at positions x1 ... xN (0 <= xi <= 1,000,000,000).

His C (2 <= C <= N) cows don't like this barn layout and become aggressive towards each other once put into a stall. To prevent the cows from hurting each other, FJ wants to assign the cows to the stalls, such that the minimum distance between any two of them is as large as possible. What is the largest minimum distance?
Input
t – the number of test cases, then t test cases follows.
* Line 1: Two space-separated integers: N and C
* Lines 2..N+1: Line i+1 contains an integer stall location, xi
Output
For each test case output one integer: the largest minimum distance.
Example
Input:

1
5 3
1
2
8
4
9
Output:

3
Output details:

FJ can put his 3 cows in the stalls at positions 1, 4 and 8,
resulting in a minimum distance of 3."""
class Solution:
    def AggressiveCow(self, stalls , cows ):
        # we need maximum spacing between the cows , in the stalls. Answer is the maximum of the minimum distance possible.
        # Brute Force : Place cows with distance between then slowly increasing from 1 to maxdistance = max(arr) -min(arr). If all cows placed, then move on to larger distance.
        # The max possible distance is the answer.

        # make sure the stalls are in increasing order
        sort(stalls)
        max_distance = - float(inf)
        def placeCowsLinear():
            for dist in range(1, max(stalls) - min(stalls)):
                countCow = 0
                lastStall = stall[0] # first placement of cow
                for stall in stalls:
                    if stall - lastStall >= dist:
                        countCow+=1 # sucessfull placement of next cow
            if countCow == cows:
                max_distance = max(dist, max_distance)

        return max_distance
    
sol = Solution()
stalls = [1,4,5,8,9]
cows = 3
print(sol.AggressiveCow(stalls, cows))
            

