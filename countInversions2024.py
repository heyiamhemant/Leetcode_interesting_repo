"""Given an array of integers. Find the Inversion Count in the array. 

Inversion Count: For an array, inversion count indicates how far (or close) the array is from being sorted. If the array is already sorted then the inversion count is 0.
If an array is sorted in the reverse order then the inversion count is the maximum. 
Formally, two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j.
 

Example 1:

Input: N = 5, arr[] = {2, 4, 1, 3, 5}
Output: 3
Explanation: The sequence 2, 4, 1, 3, 5 
has three inversions (2, 1), (4, 1), (4, 3).
Example 2:

Input: N = 5
arr[] = {2, 3, 4, 5, 6}
Output: 0
Explanation: As the sequence is already 
sorted so there is no inversion count.
Example 3:

Input: N = 3, arr[] = {10, 10, 10}
Output: 0
Explanation: As all the elements of array 
are same, so there is no inversion count.
Your Task:

You don't need to read input or print anything.
Your task is to complete the function inversionCount() which takes the array arr[] and the size of the array as inputs and returns the inversion count of the given array.

Expected Time Complexity: O(NLogN).
Expected Auxiliary Space: O(N).

Constraints:
1 ≤ N ≤ 5*105
1 ≤ arr[i] ≤ 1018"""
class Solution:

    def CountInversions(self, arr):
        print("1")
        count = mergeSortAndCount(arr, 0 , len(arr))
        return count

def mergeSortAndCount(arr, start , end, count = 0):

    if start >= end:
        return 0
    print(start, end, count)
    mid = (start + end) //2

    count += mergeSortAndCount(arr, start , mid, count)
    count += mergeSortAndCount(arr, mid+1, end, count) # also add the counts calculated when sorting the subarrays
    count+=mergeAndCount(arr,start, mid , end, count) # count calculated when merging two sorted arrays
    return count


def mergeAndCount(arr, start, mid ,end, count):
    # merge two sorted arrays and count whenever a[i] > a[j] and i < j
    n = end-start
    result = [0 for i in range(n)]
    i, j , k = 0 , mid+1, 0
    while k < n and (i <= mid + 1 or j <= end) :
        if i == mid+1 and j < end:
            result[k] = arr[j]
            j+=1
        elif j == end and i < mid+1:
            result[k] = arr[i]
            i+=1
        elif arr[i] >= arr[j]:
            # The condition for inversion is met
            count+=1
            result[k] = arr[j]
            j+=1
        else:
            result[k] = arr[i]
            i+=1
        k+=1
    return count


sol = Solution()
arr = [9,8,5,6,4,7,3,2,1]
print(sol.CountInversions(arr))
