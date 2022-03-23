/* Set Matrix Zeroes
https://leetcode.com/problems/set-matrix-zeroes/
Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.

You must do it in place.

*/

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
void func(vector<vector<int>> &matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> cprod(n, 1);
    vector<int> rprod(m, 1);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cprod[j] *= matrix[i][j];
        }
    }
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            rprod[i] *= matrix[i][j];
        }
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (cprod[j] == 0 || rprod[i] == 0)
                matrix[i][j] = 0;
}
int main()
{
    FastIO
        ll t;
    cin >> t;
    while (t--)
    {
        ll n, m;
        cin >> m >> n;
        vector<vector<int>> v(m, vector<int>(n));
        rep(i, m) rep(j, n) cin >> v[i][j];
        func(v);
        rep(i, m)
        {
            rep(j, n) cout << v[i][j] << " ";
            cout << endl;
        }
    }
    return 0;
}