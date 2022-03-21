/*https://practice.geeksforgeeks.org/problems/remove-loop-in-linked-list/1/?page=1&company[]=Oracle&curated[]=1&sortBy=submissions
 Given a linked list of N nodes such that it may contain a loop.

A loop here means that the last node of the link list is connected to the node at position X. If the link list does not have any loop, X=0.

Remove the loop from the linked list, if it is present.*/
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
    Node *next;
    Node(int x)
    {
        data = x;
        next = NULL;
    }
};

Node *createll(vector<int> &v, int i)
{
    Node *head = new Node(1);
    Node *h = head;
    head->next = new Node(4);
    Node *loop = head->next;
    head = head->next;
    head->next = new Node(3);
    head->next = loop;
    return h;
    /*Node *head = new Node(7);
    Node *h = head;
    head->next = new Node(58);
    Node *loop = head;
    head = head->next;
    head->next = new Node(36);
    head = head->next;
    head->next = new Node(34);
    head = head->next;
    head->next = new Node(16);
    head = head->next;
    head->next = loop;
    return h;

    /*if (i == v.size())
        return NULL;
    Node *node = new Node(v[i]);
    node->next = createll(v, i + 1);
    return node;*/
}
Node *detectandremoveloop(Node *head, Node *point)
{
    cout << point->data << endl;
    Node *it = point->next;
    int k = 1;
    while (it != point)
    {
        k++;
        it = it->next;
    }
    cout << "k=" << k << endl;
    // place one pointer to the kth node and other to the head.
    Node *prev = NULL;
    it = head;
    for (int i = 0; i < k; i++)
    {
        prev = it;
        it = it->next;
    }
    cout << "it->data before loop= " << it->data << endl;
    Node *it2 = head;
    while (it && it2)
    {
        if (it == it2)
        {
            cout << "it->data=" << it->data << endl;
            cout << "prev=" << prev->data << endl;
            prev->next = NULL;
            break;
        }
        it = it->next;
        prev = it2;
        it2 = it2->next;
    }
    return head;
}
Node *removeloop(Node *head)
{
    Node *fast = head;
    Node *slow = head;
    Node *point = NULL;
    // find if loop present or not
    while (fast != NULL && slow != NULL && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
        {
            point = fast;
            break;
        }
    }
    if (point == NULL)
        return NULL;
    // count the number of nodes in the loop.
    return detectandremoveloop(head, point);
}
void displayll(Node *head)
{
    while (head)
    {
        cout << head->data << " ";
        head = head->next;
    }
}
int main()
{
    FastIO
        ll t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<int> v(n);
        rep(i, n) cin >> v[i];
        Node *list = createll(v, 0);
        // displayll(list);

        if (removeloop(list))
        {
            cout << "\nLOOPS REMOVED\n";
            displayll(list);
        }
        else
        {
            cout << "\nNO LOOPS\n";
        }

        cout << '\n';
    }
    return 0;
}