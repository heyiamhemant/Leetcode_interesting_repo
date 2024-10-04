/*217. Contains Duplicate
Solved
Easy

Topics
Companies
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

 

Example 1:

Input: nums = [1,2,3,1]

Output: true

Explanation:

The element 1 occurs at the indices 0 and 3.

Example 2:

Input: nums = [1,2,3,4]
Output: false

Explanation:

All elements are distinct.

Example 3:

Input: nums = [1,1,1,3,3,4,3,2,4,2]

Output: true

 

Constraints:

1 <= nums.length <= 105
-109 <= nums[i] <= 109 */

#include<iostream>
#include <vector>
#include <unordered_set>
using ll = long long;
using namespace std;
bool containsDuplicate(vector<ll> &nums) {
    unordered_set<ll> seen;
    for(ll num : nums) {
        if (seen.find(num) != seen.end()){
            return true;
        } else {
            seen.insert(num);
        }
    }
    return false;
}
int main(){

    vector <ll> nums = { 1, 2, 3, 3, 4, 5 };
    cout << "for nums results is : " << containsDuplicate(nums);
    return 0;
}