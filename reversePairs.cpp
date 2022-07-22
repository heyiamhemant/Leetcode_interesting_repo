#include <bits/stdc++.h>
using namespace std;
int countReversePairs(vector<int> &nums, int start, int mid, int end)
{
    auto i = start;
    auto count = 0;
    auto j = mid + 1;
    while (i <= mid and j <= end)
    {
        ll lim = 2 * nums[j];
        if (nums[i] > lim)
        {
            // i is pointer on the first arr, j in pointer on second array.
            count += (mid - i + 1);
            j++;
        }
        else
        {
            i++;
        }
    }
    return count;
}
void merge(vector<int> &nums, int start, int mid, int end)
{
    int i = start, j = mid + 1;
    vector<int> res;
    while (i <= mid and j <= end)
    {
        if (nums[i] <= nums[j])
        {
            res.push_back(nums[i++]);
        }
        else
        {
            res.push_back(nums[j++]);
        }
    }
    int k = -1, rem = -2;
    if (i <= mid)
    {
        k = i;
        rem = mid;
    }
    if (j <= end)
    {
        k = j;
        rem = end;
    }
    while (k <= rem)
    {
        res.push_back(nums[k++]);
    }
    k = start;
    for (int i : res)
        nums[k++] = i;
}
void mergeSort(vector<int> &nums, int start, int end, int &result)
{
    auto c = 0;
    int mid = (start + end) / 2;
    if (start < end)
    {
        mergeSort(nums, start, mid, result);
        mergeSort(nums, mid + 1, end, result);
    }
    if (start <= end)
    {
        c = countReversePairs(nums, start, mid, end);
        merge(nums, start, mid, end);
        result += c;
    }
}
class Solution
{
public:
    int reversePairs(vector<int> &nums)
    {
        int result = 0;
        mergeSort(nums, 0, nums.size() - 1, result);
        return result;
    }
};