/*
 * @lc app=leetcode id=572 lang=cpp
 *
 * [572] Subtree of Another Tree
 *
 * https://leetcode.com/problems/subtree-of-another-tree/description/
 *
 * algorithms
 * Easy (48.88%)
 * Likes:    8326
 * Dislikes: 537
 * Total Accepted:    948.7K
 * Total Submissions: 1.9M
 * Testcase Example:  '[3,4,5,1,2]\n[4,1,2]'
 *
 * Given the roots of two binary trees root and subRoot, return true if there
 * is a subtree of root with the same structure and node values of subRoot and
 * false otherwise.
 * 
 * A subtree of a binary tree tree is a tree that consists of a node in tree
 * and all of this node's descendants. The tree tree could also be considered
 * as a subtree of itself.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [3,4,5,1,2], subRoot = [4,1,2]
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the root tree is in the range [1, 2000].
 * The number of nodes in the subRoot tree is in the range [1, 1000].
 * -10^4 <= root.val <= 10^4
 * -10^4 <= subRoot.val <= 10^4
 * 
 * 
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    /**
     * Checks if two binary trees are identical.
     * 
     * Two trees are considered identical if they are structurally identical and 
     * the nodes have the same values.
     * 
     * @param root The root node of the first tree.
     * @param subRoot The root node of the second tree.
     * @return True if the trees are identical, false otherwise.
     */
    bool isSameTree(TreeNode *root, TreeNode *subRoot){
        if(!root and !subRoot)
            return true;
        if(!root || !subRoot)
            return false;
        return root->val == subRoot->val && isSameTree(root->left, subRoot->left) && isSameTree(root->right, subRoot->right);
    }

    /**
     * Checks if a given binary tree is a subtree of another.
     * 
     * A tree T1 is a subtree of another tree T2 if T1 can be obtained by
     * removing nodes and edges from T2. All the nodes in T1 should be present
     * in T2 and the structure should be the same.
     * 
     * @param root The root node of the main tree.
     * @param subRoot The root node of the subtree.
     * @return True if the subtree is found in the main tree, false otherwise.
     */
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        bool foundSubTree = false;
        if(!root)
            return false;    

        if(root->val == subRoot->val && isSameTree(root, subRoot))
            return true;
        else
            return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);

    }
};
// @lc code=end

