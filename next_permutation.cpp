/*The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be
rearranged as the lowest possible order (i.e., sorted in ascending order).*/
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
void next_permutation(vector<int> &A)
{
    // vector<int> res;
    //  reverse travel to find next greater
    int n = A.size();
    int pi = 0, pj = 0;
    int desc = 1;
    for (int i = n - 1; i > 0; i--)
    {
        if (A[i] > A[i - 1])
        {
            pi = i - 1;
            desc = 0;
            break;
        }
    }
    if (desc)
    {
        reverse(A.begin(), A.end());
        return;
    }
    // db1(pi);
    for (int i = n - 1; i > pi; i--)
    {
        if (A[i] > A[pi])
        {
            pj = i;
            break;
        }
    }
    swap(A[pi], A[pj]);
    // rep(i, n) cout << A[i] << " ";
    reverse(A.begin() + pi + 1, A.end());
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
        next_permutation(v);
        rep(i, n) cout << v[i] << " ";
        cout << '\n';
    }
    return 0;
}