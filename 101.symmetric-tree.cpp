/*
 * @lc app=leetcode id=101 lang=cpp
 *
 * [101] Symmetric Tree
 *
 * https://leetcode.com/problems/symmetric-tree/description/
 *
 * algorithms
 * Easy (60.80%)
 * Likes:    16773
 * Dislikes: 457
 * Total Accepted:    2.8M
 * Total Submissions: 4.6M
 * Testcase Example:  '[1,2,2,3,4,4,3]'
 *
 * Given the root of a binary tree, check whether it is a mirror of itself
 * (i.e., symmetric around its center).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,2,2,3,4,4,3]
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1,2,2,null,3,null,3]
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 1000].
 * -100 <= Node.val <= 100
 * 
 * 
 * 
 * Follow up: Could you solve it both recursively and iteratively?
 */

// @lc code=start
#include<iostream>
using namespace std;
// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        
        return checkSameNodeRec(root->left, root->right);
    }
    bool checkSameNodeRec(TreeNode* it1, TreeNode* it2) {
        if(!it1 && !it2) return true;
        if(!it1 || !it2) return false;
        if(it1->val != it2->val) 
            return false;
        //cout<<it1->val << "," << it2->val << "\n";
        return checkSameNodeRec(it1->left, it2->right) && checkSameNodeRec(it1->right, it2->left);
    }
};
// @lc code=end

