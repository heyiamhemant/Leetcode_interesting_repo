/*Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Clarification:

What should we return when needle is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().
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
int strStr(string haystack, string needle)
{
    if (needle.size() == 0)
        return 0;
    int i = 0, j = 0, pos = 0;
    while (i != haystack.size())
    {
        int found = 0;
        // gateway
        if (needle[j] == haystack[i])
        {
            // assume that needle is found
            found = 1;
            pos = i;
            // check if needle is found in haystack
            while (j != needle.size() && i != haystack.size())
            {
                if (needle[j] == haystack[i])
                {
                    i++;
                    j++;
                }
                else
                { // assumption was wrong, reset needle counter
                    found = 0;
                    j = 0;
                    i = pos + 1;
                }
            }
        }
        else
        { // if first character not same , then check ahead in haystack
            i++;
        }
        if (found && j == needle.size())
            return pos; // if found then return pos , else continue, needle should completely be there
    }
    return -1;
}
int main()
{
    FastIO
        ll t;
    cin >> t;
    while (t--)
    {
        string v, nee;
        cin >> v >> nee;
        cout << strStr(v, nee);
        cout << v << "\n"
             << nee << "\n";
        cout << '\n';
    }
    return 0;
}