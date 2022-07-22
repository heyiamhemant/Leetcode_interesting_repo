#include <bits/stdc++.h>
using namespace std;
bool goodPair(int a, int b)
{
    return abs(a - b) <= 1;
}
int pairsBall(vector<int> &A, vector<int> &B)
{
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    int i = 0;
    int j = 0;
    int count = 0;
    int m = A.size();
    int n = B.size();
    while (i < m - 2 and j < n - 2)
    {
        int jmove = j;
        while (not goodPair(A[i], B[jmove]))
            jmove++;
        i++;
        int imove = i;
        while (not goodPair(A[imove], B[j]))
            imove++;
        if (jmove != n)
            count++;
        if (imove != m)
            count++;
        i = imove;
        j = jmove;
    }
    return count;
}
int main()
{
    vector<int> A = {1, 2, 3, 40};
    vector<int> B = {39, 50, 60, 70};
    cout << pairsBall(A, B) << endl;
}