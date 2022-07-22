#include <bits/stdc++.h>
using namespace std;

static int l;
class Shape
{
    static const int countShapes = 0;
    int d;

public:
    Shape(int inp)
    {
        d = inp;
    }
    int getDimension()
    {
        return d;
    }
    virtual int Area() = 0;
};
class Triangle : public Shape
{
public:
    Triangle(int d) : Shape d
    {
    }
    int Area()
    {
        int d = getDimension();
        return (float)0.5 * d * d;
    }
};
class Square : public Shape
{
public:
    int Area()
    {
        int d = getDimension();
        return d * d;
    }
};

int functionA(void)
{
}
void functionA(int)
{
}
int main()
{
    Shape *s1 = new Triangle(3);
    delete s1;
}