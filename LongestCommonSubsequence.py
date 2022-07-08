import os

def longestCommonSubsequence(str1, str2):
    # Rules for getting a recursion - Striver
    # 1. Think everything in terms of index.
    # 2. Think about all the possibilities.
    # 3. Pick the best possible among them.
    # so in this question to find lcs, we can say 
    # lcs[a = str1.length,b = str2.length] = lcs ( str1[0.. str1.length] and str2 [0 .. str2.length]) 
    

    # First Recursive soln:
    