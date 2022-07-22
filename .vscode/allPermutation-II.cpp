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
void allPermutations(std::map<int, int> &chosen, vector<int> &nums, vector<int> &result, vector<vector<int>> &allResults)
{
    if (result.size() == nums.size())
    {
        allResults.push_back(result);
        return;
    }

    // iterate over nums and call next recursion after chosing one non-chosen element
    for (int ele : nums)
    {
        cout << ele << endl;
        if (chosen[ele] == 0)
        {
            chosen[ele] = 1;
            result.push_back(ele);
            if (result.empty())
                cout << "results are empty\n";
            rep(i, result.size()) cout << result[i] << " ";
            cout << endl;
            allPermutations(chosen, nums, result, allResults);
            result.erase(result.end() - 1);
            chosen[ele] = 0;
        }
    }
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
    allPermutations(chosen, nums, result, allResults);
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
        vector<vector<int>> results;
        results = permute(v);
        for (int i = 0; i < results.size(); i++)
        {

            for (int j = 0; j < n; j++)
                cout << results[i][j] << " ";

            cout << endl;
        }

        cout << '\n';
    }
    return 0;
}