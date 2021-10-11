/*You are given a string s. We want to partition the string into as many parts as possible so that each letter appears in at most one part.

Return a list of integers representing the size of these parts.*/

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
vector<int> partition_labels(string s)
{
    vector<int> res;

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
        vector<ll> v(n);
        string s;
        rep(i, n) cin >> s;
        vector<int> res = partition_labels(s);
        rep(i, n) cout << res[i] << ' ';
        cout << '\n';
    }
    return 0;
}