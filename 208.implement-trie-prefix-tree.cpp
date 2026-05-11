/*
 * @lc app=leetcode id=208 lang=cpp
 *
 * [208] Implement Trie (Prefix Tree)
 *
 * https://leetcode.com/problems/implement-trie-prefix-tree/description/
 *
 * algorithms
 * Medium (69.21%)
 * Likes:    12455
 * Dislikes: 164
 * Total Accepted:    1.5M
 * Total Submissions: 2.2M
 * Testcase Example:  '["Trie","insert","search","search","startsWith","insert","search"]\n' +
  '[[],["apple"],["apple"],["app"],["app"],["app"],["app"]]'
 *
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to
 * efficiently store and retrieve keys in a dataset of strings. There are
 * various applications of this data structure, such as autocomplete and
 * spellchecker.
 * 
 * Implement the Trie class:
 * 
 * 
 * Trie() Initializes the trie object.
 * void insert(String word) Inserts the string word into the trie.
 * boolean search(String word) Returns true if the string word is in the trie
 * (i.e., was inserted before), and false otherwise.
 * boolean startsWith(String prefix) Returns true if there is a previously
 * inserted string word that has the prefix prefix, and false otherwise.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input
 * ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
 * [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
 * Output
 * [null, null, true, false, true, null, true]
 * 
 * Explanation
 * Trie trie = new Trie();
 * trie.insert("apple");
 * trie.search("apple");   // return True
 * trie.search("app");     // return False
 * trie.startsWith("app"); // return True
 * trie.insert("app");
 * trie.search("app");     // return True
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= word.length, prefix.length <= 2000
 * word and prefix consist only of lowercase English letters.
 * At most 3 * 10^4 calls in total will be made to insert, search, and
 * startsWith.
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class TrieNode {
public:
    TrieNode * children[26] = {nullptr};
    bool isEndOfWord = false;
    ~TrieNode() {
        for(TrieNode* child : children) delete child;
    }
};
class Trie {
    TrieNode* root;
public:
    Trie() : root(new TrieNode()) {}
    void insert(string word) {
        TrieNode* curr = root;
        for(char &c : word) {
            int index = c - 'a';
            if(!curr->children[index]) 
                curr->children[index] = new TrieNode(); // create new path
            curr = curr->children[index]; // move to the encountered char path
        }
        curr->isEndOfWord = true;
    }
    
    bool search(string word) {
        TrieNode* curr = root;
        for(char &c : word) {
            int index = c - 'a';
            if(!curr->children[index]) // not found
                return false;
            else curr = curr->children[index];
        }
        if(curr->isEndOfWord) return true;
        return false;
    }
    
    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for(char &c : prefix) {
            int index = c - 'a';
            if(!curr->children[index]) return false; // not found;
            else curr = curr->children[index];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

// @lc code=end

