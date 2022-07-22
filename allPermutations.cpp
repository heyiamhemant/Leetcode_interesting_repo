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
void allPermutations(int index1, int index2, vector<int> &nums, vector<vector<int>> &allResults)
{
    cout << index1 << ":" << index2 << endl;
    swap(nums[index1], nums[index2]);
    if (index1 == index2)
        allResults.push_back(nums);
    int n = nums.size();
    for (int i = index1; i < n; i++)
    {

        for (int j = index2 + 1; j < n; j++)
        {
            allPermutations(i, j, nums, allResults);
        }
    }
    swap(nums[index1], nums[index2]);
}
vector<vector<int>> permute(vector<int> &nums)
{

    // T(c) = n! x n - iterating n times for n! permutations
    //  s(c) = O(n)
    vector<vector<int>> allResults;
    // result is empty
    vector<int> result;
    // nothing is chosen
    map<int, int> chosen;
    // init
    cout << "the array is :\n";
    for (int num : nums)
    {
        cout << num << " ";
        chosen[num] = 0;
    }
    cout << endl;
    allPermutations(0, 0, nums, allResults);
    return allResults;
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
        vector<vector<int>> res;
        res = permute(v);
        cout << "printing results now\n";
        for (int i = 0; i < res.size(); i++)
        {
            for (int j = 0; j < n; j++)
                cout << res[i][j] << " ";
            cout << endl;
        }

        cout << '\n';
    }
    return 0;
}