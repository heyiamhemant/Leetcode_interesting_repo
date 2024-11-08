/*
 * @lc app=leetcode id=566 lang=cpp
 *
 * [566] Reshape the Matrix
 *
 * https://leetcode.com/problems/reshape-the-matrix/description/
 *
 * algorithms
 * Easy (63.45%)
 * Likes:    3546
 * Dislikes: 418
 * Total Accepted:    398.4K
 * Total Submissions: 627.9K
 * Testcase Example:  '[[1,2],[3,4]]\n1\n4'
 *
 * In MATLAB, there is a handy function called reshape which can reshape an m x
 * n matrix into a new one with a different size r x c keeping its original
 * data.
 * 
 * You are given an m x n matrix mat and two integers r and c representing the
 * number of rows and the number of columns of the wanted reshaped matrix.
 * 
 * The reshaped matrix should be filled with all the elements of the original
 * matrix in the same row-traversing order as they were.
 * 
 * If the reshape operation with given parameters is possible and legal, output
 * the new reshaped matrix; Otherwise, output the original matrix.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: mat = [[1,2],[3,4]], r = 1, c = 4
 * Output: [[1,2,3,4]]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: mat = [[1,2],[3,4]], r = 2, c = 4
 * Output: [[1,2],[3,4]]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == mat.length
 * n == mat[i].length
 * 1 <= m, n <= 100
 * -1000 <= mat[i][j] <= 1000
 * 1 <= r, c <= 300
 * 
 * 
 */

// @lc code=start
class Solution {
public:
/**
 * Reshapes a given m x n matrix `mat` into a new matrix with dimensions r x c.
 * 
 * The reshaped matrix retains the original matrix data in a row-traversing order.
 * If the reshape operation is not feasible with the provided dimensions `r` and `c`,
 * the function returns the original matrix.
 * 
 * @param mat The original m x n matrix to be reshaped.
 * @param r The number of rows in the desired reshaped matrix.
 * @param c The number of columns in the desired reshaped matrix.
 * @return A new matrix with dimensions r x c if reshaping is possible; 
 * otherwise, the original matrix.
 */
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        vector<vector<int>> res(r, vector<int>(c));
        if (mat.size() * mat[0].size() != r * c)
            return mat;
        int index = 0;
        for (int i = 0; i < mat.size(); i++)
        {
            for (int j = 0; j < mat[0].size(); j++){
                res[index / c ][index % c] = mat[i][j];
                index += 1;
            }
        }
        return res;
    }

};
// @lc code=end

