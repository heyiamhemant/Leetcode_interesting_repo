/* Number of Inversions
Moderate
0/80
Average time to solve is 40m
Contributed by
148 upvotes
Problem statement
There is an integer array ‘A’ of size ‘N’.



Number of inversions in an array can be defined as the number of pairs of ‘i’, ‘j’ such that ‘i’ < ‘j’ and ‘A[i]’ > ‘A[j]’.

You must return the number of inversions in the array.



For example,
Input:
A = [5, 3, 2, 1, 4], N = 5
Output:
7
Explanation: 
The pairs satisfying the condition for inversion are (1, 2), (1, 3), (1, 4), (1, 5), (2, 3), (2, 4), and (3, 4). 
The number of inversions in the array is 7.
Detailed explanation ( Input/output format, Notes, Images )
Sample Input 1:
4
4 3 2 1
Sample Output 1:
6
Explanation Of Sample Input 1:
Input:
A = [4, 3, 2, 1], N = 4
Output:
6
Explanation: 
The pairs satisfying the condition for inversion are (1, 2), (1, 3), (1, 4), (2, 3), (2, 4), and (3, 4).    
The number of inversions in the array is 6.
Sample Input 2:
5
1 20 6 4 5
Sample Output 2:
5
Constraints:
1 <= N <= 10^5
1 <= A[i] <= 10^9
Time Limit: 1 sec*/
#include <bits/stdc++.h>
#define db1(x) cerr<<#x<<"="<<x<<'\n'
#define db2(x,y) cerr<<#x<<"="<<x<<","<<#y<<"="<<y<<'\n'
#define db3(x,y,z) cerr<<#x<<"="<<x<<","<<#y<<"="<<y<<","<<#z<<"="<<z<<'\n'
#define rep(i,n) for(ll i=0;i<(n);++i)
#define repA(i,a,n) for(ll i=a;i<=(n);++i)
#define repD(i,a,n) for(ll i=a;i>=(n);--i)
#define mp make_pair
#define sp <<' '<<
#define pb push_back
#define FastIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
using ll = long long;
class Solution{
    vector<int> nums;
    Solution(vector<int> arr){
        nums = arr
    }

    int countInversionsBrute(){
        // if i < j and a[i] > a[j] count++
        count = 0;
        for(int i = 1 ; i < nums.size(); i++){
            for (int j = 0; j < i ; j++){
                if(a[i] > a[j]){
                    count++;
                }
            }
        }
        return count;

    }
}
int main()
{
    FastIO
    ll t;
    cin>>t;
    while(t--){
        ll n;
        cin>>n;
        vector<ll> v(n);
        rep(i,n) cin>>v[i];
        Solution sol = new Solution(v)
        cout << sol.countInversions()
    
        cout<<'\n';
    }
    return 0;
}