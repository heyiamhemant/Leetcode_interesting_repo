#include<bits/stdc++.h>
/*543. Diameter of Binary Tree
Easy
Topics
Companies
Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

The length of a path between two nodes is represented by the number of edges between them.

 */

 //Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 using namespace std;
 class Solution
 {
 public:
     int height(TreeNode *root)
     {
         if (!root)
             return 0;
         return (1 + (height(root->left), height(root->right)));
     }
     void calculateDiameter(TreeNode *root, int &diameter)
     {
         if (!root)
             return;
        if(root->left)
            calculateDiameter(root->left, diameter);
        if(root->right)
            calculateDiameter(root->right, diameter);
        diameter = max(diameter, height(root->left)+ height(root->right));
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        // diamter of tree = max(height(node->leftNode) + height(node->rightNode)) for every node
         calculateDiameter(root, diameter);
         return diameter;
    }
};