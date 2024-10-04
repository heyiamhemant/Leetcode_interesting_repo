/* 49. Group Anagrams
Medium

Topics
Companies
Given an array of strings strs, group the 
anagrams
 together. You can return the answer in any order.

 

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]

Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Explanation:

There is no string in strs that can be rearranged to form "bat".
The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.
Example 2:

Input: strs = [""]

Output: [[""]]

Example 3:

Input: strs = ["a"]

Output: [["a"]]

 

Constraints:

1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] consists of lowercase English letters.*/


#include <iostream>
#include <vector>
using namespace std;

class Solution {
    public : 
    /**
     * @brief Calculates the cost of a string.
     *
     * The cost is a vector of 26 elements, where each element is the number of
     * times the character appears in the string. The index of the element in the
     * vector is the character's position in the alphabet minus 'a'.
     *
     * @param s the string to calculate the cost for
     * @return the cost of the string
     */
    std::array<int, 26> getCost(string s) {
        std::array<int, 26> c;
        c.fill(0);
        for (int i = 0; i < s.size(); i++)
            c[s[i] - 'a']++;
        return c;
    }

    vector <vector<string>> groupAnagrams(vector<string> &strs) {
        vector<vector<string>> res;
        vector<int> visited = vector<int>(strs.size(), 0);
        for (int i = 0; i < strs.size(); i ++) {
            vector<string> anagrams;
            if (visited[i] == 1)
                continue;
            anagrams.push_back(strs[i]);
            visited[i] = 1;
            for (int j = i + 1; j < strs.size(); j ++) {
                if(strs[i].size() != strs[j].size() || visited[j] == 1) continue;
                std::array<int , 26> c1 = getCost(strs[i]);
                std::array<int,26> c2 = getCost(strs[j]);
                if(c1 == c2) {
                    visited[j] = 1;
                    anagrams.push_back(strs[j]);
                }
            }
            res.push_back(anagrams);            
        }
        return res;
    }
};

int main() {

    Solution sol = Solution();
    int n;
    cin >> n;
    while(n--) {

        int m;
        cin >> m;
        vector<string> strs(m);
        for (int i = 0; i < m; i++)
        {
            cin >> strs[i];
        }
        cout << "Solution is : " << endl;
        for(int i = 0; i < sol.groupAnagrams(strs).size(); i++) { 
            for(int j = 0; j < sol.groupAnagrams(strs).size(); j++) {
                cout << sol.groupAnagrams(strs)[i][j] << " ";
            }
            cout << endl;
        }
    }
            
    return 0;
}