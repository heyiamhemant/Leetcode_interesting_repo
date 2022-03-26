/*Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.*/
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
void sort012(vector<int> &A)
{
    // two pointers p0 and p2 to mark 0's and 2's
    int n = A.size();
    int p0 = -1;
    int p2 = n;
    int i = 0;
    while(i< p2)
    {
        //keep i greater than 0's marker
        if(A[i]==0){
            swap(A[++p0],A[i++]);
        }
        else if (A[i]==2){
            swap(A[i],A[--p2]);
        }
        // if (A[i]==1) move forward
        else i++;
    }
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
        sort012(v);
        rep(i,n) cout<< v[i]<<" ";
        cout << '\n';
    }
    return 0;
}