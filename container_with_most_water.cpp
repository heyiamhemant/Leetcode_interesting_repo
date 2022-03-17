/*You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.*/
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
int mostwater(vector<int> &height)
{
    int i = 0, j = height.size() - 1;
    int Min, res = INT_MIN;
    int minab;
    while (i < j)
    {
        if (height[i] <= height[j])
        {
            minab = height[i];
            while (height[i] <= minab)
                i++;
        }
        else
        {
            minab = height[j];
            while (height[j] <= minab)
                j--;
        }
        minab = min(height[i], height[j]);
        res = max(res, minab * (j - i));
    }
    return res;
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
        cout << "\n";
        rep(i, n) cout << v[i] << " ";
        cout << mostwater(v);

        cout << '\n';
    }
    return 0;
}