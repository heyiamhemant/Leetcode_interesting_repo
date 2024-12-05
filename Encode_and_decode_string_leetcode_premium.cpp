/*Encode and Decode Strings
Solved 
Design an algorithm to encode a list of strings to a single string. The encoded string is then decoded back to the original list of strings.

Please implement encode and decode

Example 1:

Input: ["neet","code","love","you"]

Output:["neet","code","love","you"]
Example 2:

Input: ["we","say",":","yes"]

Output: ["we","say",":","yes"]
Constraints:

0 <= strs.length < 100
0 <= strs[i].length < 200
strs[i] contains only UTF-8 characters.
*/
#include<iostream>
#include<string>
using namespace std;
class Solution
{
public:

    /**
     * Encodes a list of strings into a single string by prefixing each string 
     * with its length followed by a '#' character.
     * 
     * @param strs A vector of strings to be encoded.
     * @return A single encoded string representing the list of input strings.
     */
    string encode(vector<string>& strs) {
        stringstream encoded;
        for(string str : strs){
            encoded << str.size() <<  "#" <<str << "#";
    
        }
        return encoded.str();

    }

    /**
     * Decodes a single encoded string into a vector of strings.
     * 
     * Given an encoded string, this function splits it into a vector of strings 
     * by parsing the length of each string prefixed by a '#' character.
     * 
     * @param s A single encoded string to be decoded.
     * @return A vector of decoded strings.
     */
    vector<string>decode(string s) {
        vector<string> decoded;
        int i = 0;
        while(i < s.size()) {
            string toksize;
            while(s[i] != '#') {
                toksize +=s[i++];
            }
            i++;
            int numtoksize = stoi(toksize.c_str());
            string word ;
            //cout << "numtoksize " << numtoksize <<endl;
            int count = i + numtoksize;
            while(i < count){
                word+=s[i++];
            }
            decoded.push_back(word);
            i++;
        }
        return decoded;
    }
};
