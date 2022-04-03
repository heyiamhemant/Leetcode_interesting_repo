/*You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively.

Merge nums1 and nums2 into a single array sorted in non-decreasing order.*/
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
void Insert(vector<int> &A, int pos, int ele)
{
    int size = A.size();
    A.insert(A.begin()+pos,ele);
    A.resize(size);
}
void merge_gap(vector<int> &A, vector<int> &B, int m,int n){
    // O((m+n)log(m+n))
    for(int i=m,j=0;i<A.size();i++,j++){
        A[i] = B[j];
    }
    rep(i,A.size()) cout<<A[i]<<" ";
    cout<<endl;
    float gap= m+n;
    do{
        
        // NEED TO REMEMBER : CEIL NOT FLOOR
        gap = ceil(gap/2);
        for(int i=0;i<A.size()-gap;i++){
            if(A[i]>A[i+gap]){
                swap(A[i],A[i+gap]);
            }
        }
    }while(gap!=1);
}
void merge(vector<int> &A, vector<int> &B, int m, int n)
{
    //simple approach
    A[m] = INT_MAX;
    B.push_back(INT_MAX);
    n++;
    int j = 0;
    for (int i = 0; i < m + n; i++)
    {
        if (A[i] >= B[j])
        {
            cerr << "calling insert\n";
            Insert(A, i, B[j++]);
        }
        rep(i, m + n) cerr << A[i] << " ";
        cerr << endl;
    }
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
        cin >> m >> n;
        vector<int> A(m + n, 0);
        vector<int> B(n);
        rep(i, m) cin >> A[i];
        rep(i, n) cin >> B[i];
        vector<int> A1 = A;
        vector<int> B1 =B;
        rep(i, m + n) cout << A[i] << " ";
        cout << endl;
        rep(i, n) cout << B[i] << " ";
        cout << endl;
        //merge(A, B, m, n);
        rep(i, A.size()) cout << A[i] << " ";
        cout << '\n';
        merge_gap(A1,B1,m,n);
        rep(i,A1.size()) cout<<A1[i]<< " ";
    }
    return 0;
}