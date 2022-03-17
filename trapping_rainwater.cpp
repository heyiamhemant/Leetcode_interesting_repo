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
int trap(vector<int> &height)
{
    int total = 0;
    int i = 0, sum = 0, sumi = 0, sumj = 0;
    int j = height.size() - 1;
    int x = 0, y = 0;
    int end = height.size();
    int min = 0;
    while (i < end)
    {
        min = height[i];
        sum = 0;
        while (x < end && height[x] < min)
        {
            sum += (min - height[x++]);
        }
        if (x != end)
        {
            total += sum;
            cout << "total=" << total << "\n" i = x;
        }
    }
    while (j > i)
    {
        while (j < i)
        {
        }
        min = height[j];
        sum = 0;
        while (y >= 0 && height[y] < min)
        {
            sum += (min - height[y--]);
        }
        if (((y >= 0)))
        {
            total += sum;
            cout << "total=" << total << "\n" j = y;
        }
    }
    cout << "total =" << total << "\n";
    return total;
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
        rep(i, n) cout << v[i] << " ";
        cout << trap(v);
        cout << '\n';
    }
    return 0;
}