/*Given a matrix mat[][] of size N x M, where every row and column is sorted in increasing order, and a number X is given.
The task is to find whether element X is present in the matrix or not.*/
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
int bin_search(vector<vector<ll>> &mat, int i, int x)
{
    int l = 0, mid = 0;
    int r = mat[i].size();
    while (l < r)
    {
        mid = (l + r) / 2;
        if (mat[i][mid] == x)
            return 1;
        if (mat[i][mid] > x)
            r = mid;
        else if (mat[i][mid] < x)
            l = mid;
    }
    return 0;
}
int search_matrix(vector<vector<ll>> &mat, int N, int M, int X)
{
    for (int i = 0; i < N; i++)
    {
        if (mat[i][0] == X || mat[i][N - 1] == X)
            return 1;
        else if (mat[i][0] < X && mat[i][N - 1] > X) // present in this iteration
        {
            return bin_search(mat, i, X); // return 1 if found , else 0.
        }
        else if (mat[i][0] > X) // it is less , should have been found in earlier iterations
            return 0;
        else if (mat[i][N - 1] < X) // should be in higher iteration
            continue;
        else
        {
            cout << "\nINPUT matrix not sorted\n"; // other conditions not possible
        }
    }
    return 0;
}
int main()
{
    FastIO
        ll t;
    cin >> t;
    while (t--)
    {
        ll m;
        ll n;
        ll X;
        cin >> m >> n;
        cin >> X;
        vector<vector<ll>>
            v(m, vector<ll>(n));
        rep(i, m) rep(j, n) cin >> v[i][j];
        cout << search_matrix(v, m, n, X);

        cout << '\n';
    }
    return 0;
}