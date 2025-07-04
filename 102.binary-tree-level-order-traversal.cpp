/*
 * @lc app=leetcode id=102 lang=cpp
 *
 * [102] Binary Tree Level Order Traversal
 *
 * https://leetcode.com/problems/binary-tree-level-order-traversal/description/
 *
 * algorithms
 * Medium (68.86%)
 * Likes:    16204
 * Dislikes: 349
 * Total Accepted:    2.8M
 * Total Submissions: 4M
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given the root of a binary tree, return the level order traversal of its
 * nodes' values. (i.e., from left to right, level by level).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [3,9,20,null,null,15,7]
 * Output: [[3],[9,20],[15,7]]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1]
 * Output: [[1]]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: root = []
 * Output: []
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [0, 2000].
 * -1000 <= Node.val <= 1000
 * 
 * 
 * 
 * 
 */

// @lc code=start
/**
 * Definition for a binary tree node.

 */

 struct TreeNode {
    int val;
    TreeNode *left;
   TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#include<iostream>
using namespace std;
class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        queue<TreeNode *> Q;
        vector<vector<int>> res;
        if (root)
            Q.push(root);
        while (!Q.empty())
        {
            int levelSize = Q.size();
            vector<int> level;
            for (int i = 0; i < levelSize; i++)
            {
                TreeNode *node = Q.front();
                Q.pop();
                level.push_back(node->val);
                if (node->left)
                    Q.push(node->left);
                if (node->right)
                    Q.push(node->right);
            }
            res.push_back(level);
        }
        return res;
    }
};
// @lc code=end

