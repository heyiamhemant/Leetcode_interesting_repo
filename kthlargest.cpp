#include <bits/stdc++.h>
using namespace std;
class Heap
{
public:
    void heapify(vector<int> &heap, int i)
    {
        int n = heap.size();
        int large = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (right < n and heap[large] < heap[right])
        {
            large = right;
        }
        if (left < n and heap[large] < heap[left])
        {
            large = left;
        }
        if (large != i)
        {
            swap(heap[large], heap[i]);
            heapify(heap, large);
        }
    }
    void makeHeap(vector<int> &heap)
    {
        int n = heap.size();
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(heap, i);
        }
    }
    void heapop(vector<int> &heap)
    {
        swap(heap[heap.size() - 1], heap[0]);
        heap.pop_back();
    }
    void heappush(vector<int> &heap, int ele)
    {
        swap(heap[heap.size() - 1], heap[0]);
        heap.push_back(ele);
    }
};
int findKthLargest(vector<int> &nums, int k)
{
    Heap heap = Heap();
    heap.makeHeap(nums);
    for (auto i : nums)
    {
        cout << i << ' ';
    }
    cout << "\n";
    for (int i = 0; i < k - 1; i++)
    {
        heap.heapop(nums);
        heap.heapify(nums, 0);
    }
    return nums[0];
}

int main()
{
    vector<int> nums = {2, 3, 4, 5, 1};
    int k = 2;
    cout << findKthLargest(nums, k);
    return 0;
}