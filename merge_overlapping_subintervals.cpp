/*Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of
 the non-overlapping intervals that cover all the intervals in the input.*/
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
vector<vector<int>> merge_overlapping_subintervals(vector<vector<int>> &A)
{
    vector<vector<int>> result;
    rep(i, A.size()) cerr << A[i][0] << A[i][1] << "\n";

    // sort according to the first elements
    sort(A.begin(), A.end(), [](const auto &x, const auto &y)
         { return x[0] < y[0]; });
    vector<int> p(2);
    p = {A[0][0], A[0][1]};
    for (int i = 1; i < A.size(); i++)
    {

        // if overlapping then merge and form new pair to check
        if (p[1] >= A[i][0])
        {
            p = {min(p[0], A[i][0]), max(p[1], A[i][1])};
        }
        else // not overlapping then push to result, and take new pair from input for
        // checking forward
        {
            result.push_back(p);
            p = {A[i][0], A[i][1]};
        }
    }
    result.push_back(p);

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
        vector<vector<int>> v(n, vector<int>(2, 0));
        rep(i, n)
        {
            cin >> v[i][0];
            cin >> v[i][1];
        }
        vector<vector<int>> result = merge_overlapping_subintervals(v);
        rep(i, result.size()) cout << "[" << result[i][0] << "," << result[i][1] << "]"
                                   << ",";
        cout << '\n';
    }
    return 0;
}