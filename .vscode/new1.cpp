#include <bits/stdc++.h>
using namespace std;

class MySingleton
{
    static int counter;

private:
    MySingleton()
    {
        if (++counter > 1)
    }
};