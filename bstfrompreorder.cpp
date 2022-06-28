#include <bits/stdc++.h>
using namespace std;
class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL){};
};
TreeNode *toBSTPreorder(vector<int> &preorder, vector<int> &inorder, int start_pre, int end_pre, int start_in, int end_in)
{
    int n = preorder.size();
    if (start_in > end_in or start_pre > end_pre or start_pre < 0 or start_in < 0 or end_in >= n or end_pre >= n)
        return NULL;

    int root = preorder[start_pre];
    int pos = lower_bound(inorder.begin() + start_in, inorder.begin() + end_in + 1, root) - inorder.begin();

    int ltree = pos - start_in;
    int rtree = end_in - pos;
    cerr << root << ' ' << pos << ' ' << start_pre << ' ' << end_pre << ' ' << start_in << ' ' << end_in << endl;
    TreeNode *Node = new TreeNode(root);
    Node->left = toBSTPreorder(preorder, inorder, start_pre + 1, end_pre - rtree, start_in, pos - 1);
    Node->right = toBSTPreorder(preorder, inorder, start_pre + ltree + 1, end_pre, pos + 1, end_in);
    return Node;
}
TreeNode *bstFromPreorder(vector<int> &preorder)
{
    vector<int> inorder = preorder;
    int n = preorder.size();
    sort(inorder.begin(), inorder.end());
    return toBSTPreorder(preorder, inorder, 0, n - 1, 0, n - 1);
}
void inorderDisplay(TreeNode *root)
{
    if (root)
    {
        inorderDisplay(root->left);
        cout << root->val << ' ';
        inorderDisplay(root->right);
    }
}
int main()
{
    vector<int> preorder = {8, 5, 1, 7, 10, 12};
    TreeNode *root = bstFromPreorder(preorder);
    inorderDisplay(root);
}