#include <bits/stdc++.h>
using namespace std;
using ll = long long;
bool StrStr(const string input, const string tofind)
{

    // "aaabbccc" , "ab"
    // "Hemant" , "em"
    int i = 0, j = 0;
    ll count = 0;
    while (i < input.size())
    {
        if (input[i] == tofind[j])
        {
            i++;
            j++;
            if (j == tofind.size())
            {
                count++;
                j = 0;
            }
        }
        else
        {
            j = 0;
            i++;
        }
    }
    return false;
}