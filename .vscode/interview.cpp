
// common.h
int function(int a, int b);
// common.cpp
int function(int a, int b)
{

    return a + b;
}
// game1.cpp
#include <common.h>
// game2.cpp
#include <common.h>
g++ - c game1.cpp g++ - c game2.cpp g++ - c common.cpp g++ - o game game1.o game2.o common.o

                                                             unsigned long long
                                                             strlen(const char *input);
// stlen return the lenght of string input(given as char array).
// the input remains constant,cannot be modified.
// if empty, returns 0.
// if different type of input parameter provided, produces error.

unsigned long long strlen(const char *input)
{

    unsigned long long length = 0;
    int i = 0;
    for (i = 0; input[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}

unsigned long long strlen1(const char *input)
{
    // aa\abc
    unsigned long long i = 0;
    for (i = 0; input[i] != '\0'; i++)
        ;
    return i;
}
unsigned long long strlen2(const char *input)
{
    // abcde
    // static unsigned long long i = 0;
    if (*input == '\0')
        return 0;
    // i++;
    return 1 + strlen(input + 1);
}

// setbit , input : int , offset :

// setbit(0,3)

1000(2, 3)10->1010

    // (6,4)   110 -> 10110  (110 + 10000(2^4))
    // (2,3)   10 -> 1010   (10+1000 (2^3))
    // (2,1)   10 -> 10   (10 + 10(2^1))

    using ll = long long;
ll setbit(ll input, ll offset)
{
    return input | pow(2, offset);
}

func()
{
    vector<ll> arr(100);
    for (ll i = 0; i < arr.size(); i++)
    {
        arr[i] = i;
    }
    bool found = false;
    auto it = arr.find(ele);
    if (it != arr.end())
    {
        found = true;
        (*it)++;
    }
    cout << found;
}