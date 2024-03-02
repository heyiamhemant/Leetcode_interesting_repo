"""Allocate Books
Programming
Binary Search
Medium
25.7% Success

861

20

Bookmark
Asked In:
Problem Description
 
 

Given an array of integers A of size N and an integer B.

The College library has N books. The ith book has A[i] number of pages.

You have to allocate books to B number of students so that the maximum number of pages allocated to a student is minimum.

A book will be allocated to exactly one student.
Each student has to be allocated at least one book.
Allotment should be in contiguous order, for example: A student cannot be allocated book 1 and book 3, skipping book 2.
Calculate and return that minimum possible number.

NOTE: Return -1 if a valid assignment is not possible.



Problem Constraints
1 <= N <= 105
 1 <= A[i], B <= 105



Input Format
The first argument given is the integer array A.
The second argument given is the integer B.



Output Format
Return that minimum possible number.



Example Input
Input 1:
A = [12, 34, 67, 90]
B = 2
Input 2:
A = [5, 17, 100, 11]
B = 4


Example Output
Output 1:
113
Output 2:
100


Example Explanation
Explanation 1:
There are two students. Books can be distributed in following fashion : 
1)  [12] and [34, 67, 90]
    Max number of pages is allocated to student 2 with 34 + 67 + 90 = 191 pages
2)  [12, 34] and [67, 90]
    Max number of pages is allocated to student 2 with 67 + 90 = 157 pages 
3)  [12, 34, 67] and [90]
    Max number of pages is allocated to student 1 with 12 + 34 + 67 = 113 pages
    Of the 3 cases, Option 3 has the minimum pages = 113.
"""


"""Optimization min-max problem, to be solved using binary search. We want min of max allotted pages to a student, books being alloted to every student.
we need to know a min and max to perform bisection.
Without considering the no. of students to be allotted, the min possible result would be the max(all books)
The max possible result without considering no. of students is the sum(all books)"""

class Solution():
    def books(self, A, B):
        if len(A) < B:
            return -1
        minVal = max(A)
        maxVal = sum(A)
        while minVal < maxVal:
            mid = (minVal + maxVal)//2
            allocated = StudentsAllocated(A, mid)
            #print(allocated, minVal, maxVal)
            if allocated > B: # means we assigned less books per student
                minVal = mid + 1
            else:
                maxVal = mid
        return minVal
                
            
        # if every one get allotted even one book the max would be max(A[i]), not considering the one book rule here.


def StudentsAllocated(A, books): # books will get the mid value
    count = 0
    students = 1
    for x in A:
        count+=x
        if count > books:
            students+=1 # now the new student's allotment for books
            count = x # reset the sum           
    return students
    
sol = Solution()
A = [12, 34 ,67,90]
B = 2
print(sol.books(A, B))
