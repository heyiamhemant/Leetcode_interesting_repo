#include <bits/stdc++.h>
using namespace std;
class C
{
    int member;

public:
    C(int a)
    {
        member = a;
    }
};
class Complex
{
    int real;
    int imag;

public:
    Complex(int a, int b) : real(a), imag(b)
    {
    }
    Complex(const Complex &obj)
    {
        real = obj.real;
        imag = obj.imag;
    }
    friend ostream &operator<<(ostream &out, const Complex &c)
    {
        out << c.real << " + i" << c.imag;
        return out;
    }
    void complexSwap()
    {
        swap(real, imag);
    }
    bool operator<(Complex &c1)
    {
        if (real < c1.real)
            return true;
        return false;
    }
};
int main()
{
    auto i = 5;
    Complex c1(3, 5);
    cout << c1 << endl;
    vector<Complex> cvec{{2, 3}, {4, 6}, {5, 7}, {1, 2}, {3, 5}};
    for (auto &i : cvec)
    {
        i.complexSwap();
        cout << i << endl;
    }
    cout << endl;
    for (auto i : cvec)
    {
        cout << i << endl;
    }
    cout << endl;
    sort(cvec.begin(), cvec.end());
    for (auto i : cvec)
    {
        cout << i << endl;
    }
}