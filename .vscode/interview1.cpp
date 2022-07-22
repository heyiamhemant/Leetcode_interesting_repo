#include <bits/stdc++.h>
using namespace std;

int **createArray(int m, int n)
{
    int **arr = new int *[m];
    for (int i = 0; i < m; i++)
    {
        arr[i] = new int[n];
    }
    return arr;
}
int freeArray(int **arr, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        delete arr[i];
    }
    delete *arr;
}

// 0000001111111 -> 7
//

int getPos(int arr[], int n)
{
    int low = 0;
    int high = n - 1;
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (mid < n - 1 and arr[mid] != arr[mid + 1])
        {
            return mid + 1;
        }
        else if (mid < n - 1 and arr[mid] == arr[mid + 1] and arr[mid] == 1)
        {
            high = mid - 1;
        }
        else if (mid < n - 1 and arr[mid] == arr[mid + 1] and arr[mid] == 0)
        {
            low = mid + 1;
        }
    }
    return -1;
}

void preorder(Node head)
{
    stack<Node> S;
    Node *node = head;
}
class Complex
{
    int real;
    int imag;

public:
    Complex operator+(Complex &obj)
    {
        real += obj.real;
        imag += obj.imag;
    }
    string operator<<(Complex &obj)
    {
        string res = to_string(obj.real) + 'i' + to_string(obj.imag);
        return res;
    }
};

int main()
{
    Complex c1 = Complex(1, 2);
    Complex c2 = Complex(3, 4)
        Complex c3 = c1 + c2;
    cout << c3;
}

(1 + 2i) + (3 + 4i)

    // -1 3 4 -1 -2 -3
    // -1 3 4 5 -6 -7
    vector<int> SeperatePosNeg(vector<int> &inp)
{
    int i = -1;
    int j = 0;
    while (j < inp.size())
    {
        if (inp[j] < 0)
        {
            i++;
            swap(inp[i], inp[j]);
        }
        j++;
    }
}