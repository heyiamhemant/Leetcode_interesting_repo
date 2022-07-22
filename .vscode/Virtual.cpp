#include <bits/stdc++.h>
using namespace std;

class Instrument
{ // abstraction through abstract classes
private:
    int x = 10;

public:
    friend class piano;
    friend int function1(Instrument &);
};
int function1(Instrument &it)
{
    cout << "Taking value from another object=" << it.x << endl;
    return it.x;
}
class piano
{
public:
    void play(Instrument &it)
    {
        cout << it.x << endl;
        cout << "Piano plays...";
    }
};
class accordion
{
public:
    void play()
    {
        cout << "Accordion is playing...";
    }
};
int main()
{
    Instrument i1 = Instrument();
    piano pi1 = piano();
    pi1.play(i1);
    cout << function1(i1);
}
