#include <bits/stdc++.h>
using namespace std;
void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    for (int i = m + 1; i < m + n; i++)
        nums1[i] = INT_MIN;
    int i = m - 1;
    int inserted_p = m + n - 1;
    int j = n - 1;
    while (inserted_p >= 0)
    {

        if (nums1[i] > nums2[j])
        {
            swap(nums1[inserted_p], nums1[i]);
            i--;
        }
        else
        {
            swap(nums1[inserted_p], nums2[j]);
            j--;
        }
        inserted_p--;
        if (i < 0)
            i = 0;
        if (j < 0)
            j = 0;
        for (int i = 0; i < m + n; i++)
            cerr << nums1[i] << ' ';
        cerr << endl;
        for (int i = 0; i < n; i++)
        {
            cerr << nums2[i] << ' ';
        }
        cerr << endl;
    }
}
int main()
{
    vector<int> arr1 = {-1, 0, 0, 3, 3, 3, 0, 0, 0};
    vector<int> arr2 = {1, 2, 2};
    merge(arr1, 4, arr2, arr2.size());
    for (int i : arr1)
        cout << i << ' ';
}