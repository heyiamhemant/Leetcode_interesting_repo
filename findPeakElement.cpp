#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isIncreasing(vector<int> &nums, int pos){
        if(pos < 0 or pos >= nums.size()){
            return false;
        }
        if(pos == 0) {
            return nums[pos] < nums[pos+1];
        }
        if(pos == nums.size()-1){
            // cannot be increasing
            return false; 
        }
        return nums[pos] > nums[pos-1] && nums[pos] < nums[pos+1]  ;
    }
    bool isPeak(vector<int> &nums, int pos){
        if(pos < 0 or pos >= nums.size()){
            return false;
        }
        if(pos == 0) {
            return nums[pos] > nums[pos+1];
        }
        if(pos == nums.size()-1){
            return nums[pos-1] < nums[pos]; 
        }
        return nums[pos] > nums[pos-1] && nums[pos] > nums[pos+1]  ;
    }
    bool isDecreasing(vector<int> &nums, int pos){
        if(pos < 0 or pos >= nums.size()){
            return false;
        }
        if(pos == 0) {
            // cannot be decreasing
            return false;
        }
        if(pos == nums.size()-1){
            return nums[pos-1] > nums[pos]; 
        }
        return nums[pos] < nums[pos-1] && nums[pos] > nums[pos+1]  ;
    }
    int findPeakElement(vector<int>& nums) {
        if(nums.size() == 1){
            return 0;
        }
        // use monotonicity to find the peak element, if monotonically increasing ===> peak is to the right, else left
        int low = 0;
        int high = nums.size() - 1;
        while (low <= high) {
            int mid = (low + high )/2;
            std::cout << "mid " << mid <<endl;
            if (isIncreasing(nums, mid)){
                std::cout << "inc"<<endl;
                // means the peak is ahead
                low = mid+1;
            } else if (isDecreasing(nums,mid)){
                std::cout << "dec"<<endl;
                // means the peak is behind
                high = mid -1;
            } else if (isPeak(nums, mid)){
                std::cout << "peak"<<endl;
                return mid;
            } else // minima condition
                low = mid+1;
        }
        return 0;
    }

};