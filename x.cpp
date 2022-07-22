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
void recThreeSum(vector<int> &nums, map<int, int> &chosen, vector<vector<int>> &result, int &sum, int &target)
{
    db1(sum);
    
    if (sum == target) {
        vector<int> array;
        for(int num : nums){
            if(chosen[num] == 1) {
                array.push_back(num);
            }
        }
        result.push_back(array);
        return;
    }

    for (int num : nums)
    {
        chosen[num] = 1;
        sum += num;

        recThreeSum(nums, chosen, result, sum, target);

        sum -= num;
        chosen[num] = 0;
    }
}
vector<int> threeSum(vector<int> &nums, int &target)
{
    map<int, int> chosen;
    for (int num : nums)
        chosen[num] = 0;
    vector<vector<int>> result;
    int sum = 0;
    recThreeSum(nums, chosen, result, sum, target);
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
        int target;
        vector<int> v(n);
        rep(i, n) cin >> v[i];
        cin >> target;
        vector<int> res = threeSum(v, target);
        rep(i, n) cout << res[i] << " ";
        cout << "target : " << target << "\n";
        cout << '\n';
    }
    return 0;
}