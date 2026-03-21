/*
 * @lc app=leetcode id=394 lang=cpp
 *
 * [394] Decode String
 *
 * https://leetcode.com/problems/decode-string/description/
 *
 * algorithms
 * Medium (62.31%)
 * Likes:    13966
 * Dislikes: 701
 * Total Accepted:    1.2M
 * Total Submissions: 1.9M
 * Testcase Example:  '"3[a]2[bc]"'
 *
 * Given an encoded string, return its decoded string.
 * 
 * The encoding rule is: k[encoded_string], where the encoded_string inside the
 * square brackets is being repeated exactly k times. Note that k is guaranteed
 * to be a positive integer.
 * 
 * You may assume that the input string is always valid; there are no extra
 * white spaces, square brackets are well-formed, etc. Furthermore, you may
 * assume that the original data does not contain any digits and that digits
 * are only for those repeat numbers, k. For example, there will not be input
 * like 3a or 2[4].
 * 
 * The test cases are generated so that the length of the output will never
 * exceed 10^5.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "3[a]2[bc]"
 * Output: "aaabcbc"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "3[a2[c]]"
 * Output: "accaccacc"
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "2[abc]3[cd]ef"
 * Output: "abcabccdcdcdef"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 30
 * s consists of lowercase English letters, digits, and square brackets
 * '[]'.
 * s is guaranteed to be a valid input.
 * All the integers in s are in the range [1, 300].
 * 
 * 
 */

 #include<stack>
 #include<iostream>
using namespace std;

class Solution {

public:
    bool isNum(char &c) {
        return  c - '0' >= 0 && c - '0' <= 9 ;
    }
    string decodeString(string s) {
        stack<char> st;
        for(int i = 0; i < s.size() ; i++) {
            if(s[i] == ']') { // detect ]
                //cout << "]" <<endl;
                string current;
                while(!st.empty() && !isNum(st.top())) {
                    if(st.top() != '[') {
                        current = st.top() + current;             
                        //cout << st.top() << " : pop" << endl; 
                    } 
                    st.pop();
                }
                //cout << "current : " << current << endl;
                string strnum;
                while(!st.empty() && isNum(st.top())){
                    strnum = st.top() + strnum;
                    //cout << st.top() << " : pop" << endl;
                    st.pop();
                }
                //cout<< "strnum : " << strnum << endl;
                int num = stoi(strnum);
                for(int j =0 ; j < num ; j++) // num number of times push the characters of string obtained
                    for(int k = 0 ; k < current.size() ; k++) {
                        st.push(current[k]);
                        //cout << current[k] << " : push\n";
                    }
            } else {
                st.push(s[i]);
                //cout << s[i] << ": push" << endl;
            }
        }
        //cout << "getresult \n";
        std::string result;
        while(!st.empty()) {
            result = st.top() + result;
            //cout << st.top() << ": pop" << endl;
            st.pop();
        }
        return result;
    }

    string decodeStringbeat100percent(string s) {
        // two stack solution, one for numbers and one for strings
        stack<int> numStack;
        stack<string> strStack;
        string currentStr;
        int currentNum = 0;

        for (char c : s) {
            if (isdigit(c)) {
                currentNum = currentNum * 10 + (c - '0');
            } else if (c == '[') {
                numStack.push(currentNum);
                strStack.push(currentStr);
                currentNum = 0;
                currentStr.clear();  // reset for inner part
            } else if (c == ']') {
                int repeat = numStack.top(); numStack.pop();
                string prevStr = strStack.top(); strStack.pop();

                string repeated;
                repeated.reserve(currentStr.size() * repeat);  // optional: faster
                for (int i = 0; i < repeat; ++i) {
                    repeated += currentStr;
                }
                currentStr = prevStr + repeated;
            } else {
                currentStr += c;
            }
        }
        return currentStr;
    }
};
// @lc code=end

