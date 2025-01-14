/*
 * @lc app=leetcode id=20 lang=cpp
 *
 * [20] Valid Parentheses
 *
 * https://leetcode.com/problems/valid-parentheses/description/
 *
 * algorithms
 * Easy (41.26%)
 * Likes:    25025
 * Dislikes: 1842
 * Total Accepted:    5.5M
 * Total Submissions: 13.3M
 * Testcase Example:  '"()"'
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 * 
 * An input string is valid if:
 * 
 * 
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 * Every close bracket has a corresponding open bracket of the same type.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "()"
 * 
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "()[]{}"
 * 
 * Output: true
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "(]"
 * 
 * Output: false
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: s = "([])"
 * 
 * Output: true
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^4
 * s consists of parentheses only '()[]{}'.
 * 
 * 
 */
#include<iostream>
#include<stack>
using namespace std;
#include<set>
// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        stack<char> Stack;
        for (char c : s)
        {
            if( c == '(' || c == '[' || c == '{' )
                Stack.push(c);
            else if( c == ')' && !Stack.empty() && Stack.top() == '(')
                Stack.pop();
            else if(c =='}' && !Stack.empty() && Stack.top() == '{')
                Stack.pop();
            else if (c == ']' && !Stack.empty() &&  Stack.top() == '[')
                Stack.pop();
            else return false;
        }

        if (Stack.empty())
            return true;
        else return false;
    }
};
// @lc code=end

