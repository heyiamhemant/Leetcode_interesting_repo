#include <bits/stdc++.h>
#define db1(x) cerr << #x << "=" << x << '\n'
#define db2(x, y) cerr << #x << "=" << x << "," << #y << "=" << y << '\n'
#define db3(x, y, z) cerr << #x << "=" << x << "," << #y << "=" << y << "," << #z << "=" << z << '\n'
#define rep(i, n) for (ll i = 0; i < (n); ++i)
#define repA(i, a, n) for (ll i = a; i <= (n); ++i)
#define repD(i, a, n) for (ll i = a; i >= (n); --i)
#define mp make_pair
#define sp << ' ' <<
#define pb push_back
#define FastIO               \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
using namespace std;
using ll = long long;
void nextPermutation(vector<int> &nums)
{
    int n = nums.size();
    int index1 = n - 1;
    int index2 = n - 1;
    while (index1 >= 0)
    {
        index2 = index1 + 1;
        int minMaxNum = nums[index1];
        int minMaxPos = index1;
        int found = 0;
        while (index2 < n)
        {
            if (nums[index1] < nums[index2])
            {
                minMaxNum = min(minMaxNum, nums[index2]);
                minMaxPos = index2;
                found = 1;
            }
            index2++;
        }
        if (found)
        {
            cout << minMaxNum << endl;
            swap(nums[index1], nums[minMaxPos]);
            sort(nums.begin() + index1 + 1, nums.end());
            break;
        }
        index1--;
    }
    rep(i, n) cout << nums[i] << " ";
    cout << endl;
}
int main()
{
    FastIO
        ll t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<int> v(n);
        rep(i, n) cin >> v[i];
        nextPermutation(v);
        rep(i, n) cout << v[i] << " ";
        cout << '\n';
    }
    return 0;
}