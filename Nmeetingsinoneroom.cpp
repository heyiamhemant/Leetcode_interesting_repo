/*There is one meeting room in a firm. There are N meetings in the form of (start[i], end[i]) where start[i] is start time of meeting i and end[i] is finish time of meeting i.
What is the maximum number of meetings that can be accommodated in the meeting room when only one meeting can be held in the meeting room at a particular time?

Note: Start time of one chosen meeting can't be equal to the end time of the other chosen meeting*/
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
bool greater_func(const pair<int, int> &a, const pair<int, int> &b)
{
    return (a.second < b.second);
}
vector<int> func(vector<int> &s, vector<int> &e)
{
    vector<int> result;
    int n = s.size();
    int start = 0, end = n;
    vector<pair<int, int>> diff(n);
    for (int i = 0; i < n; i++)
    {
        diff[i].first = i;
        diff[i].second = e[i] - s[i];
    }
    sort(diff.begin(), diff.end(), greater_func);
    rep(i, n) cout << diff[i].first << " ";
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        start = s[i];
        if (start != end)
        {
            result.push_back(diff[i].first + 1);
        }
        end = e[i];
    }
    return result;
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
        vector<int> s(n);
        vector<int> e(n);
        rep(i, n) cin >> s[i];
        rep(i, n) cin >> e[i];
        vector<int> res = func(s, e);
        rep(i, res.size()) cout << res[i] << " ";

        cout << '\n';
    }
    return 0;
}