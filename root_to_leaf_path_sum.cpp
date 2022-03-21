/*Given a binary tree and an integer S, check whether there is root to leaf path with its sum as S.*/
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
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
    }
};
int calc_root_to_leaf_sum(Node *root, int sum, int x)
{
    if (sum + root->data == x)
        return 1;
    int l = 0, r = 0;
    if (root->left)
    {
        l = calc_root_to_leaf_sum(root->left, sum + root->data, x);
    }
    if (root->right)
    {
        r = calc_root_to_leaf_sum(root->right, sum + root->data, x);
    }
    return (l or r);
}
int root_to_leaf_sum(Node *root, int x)
{
    return calc_root_to_leaf_sum(root, 0, x);
}
Node *createtree()
{
    Node *root = new Node(1);
    // root->left = new Node(2);
    // root->right = new Node(3);
    return root;
}
void displayinorder(Node *root)
{
    if (root)
    {
        displayinorder(root->left);
        cout << root->data << " ";
        displayinorder(root->right);
    }
}
int main()
{
    FastIO
        ll t;
    cin >> t;
    while (t--)
    {
        int x;
        cin >> x;
        Node *root = createtree();
        cout << root_to_leaf_sum(root, x) << "\n";
        displayinorder(root);
        cout << '\n';
    }
    return 0;
}