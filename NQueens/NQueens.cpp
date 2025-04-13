#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<string>> ans;

    bool check(int rowIdx, int colIdx, vector<vector<int>>& board) {
        int n = board.size();
        for (int i = 0; i < colIdx; i++) {
            if (board[rowIdx][i] == 1) {
                return false;
            }
        }
        for (int i = rowIdx, j = colIdx; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 1) {
                return false;
            }
        }
        for (int i = rowIdx, j = colIdx; i < n && j >= 0; i++, j--) {
            if (board[i][j] == 1) {
                return false;
            }
        }
        return true;
    }

    void helper(int colIdx, vector<vector<int>>& board, int n, vector<string>& temp) {
        if (colIdx == n) {
            ans.push_back(temp);
            return;
        }
        for (int rowIdx = 0; rowIdx < n; rowIdx++) {
            if (check(rowIdx, colIdx, board)) {
                string str(n, '.');
                str[rowIdx] = 'Q';
                temp.push_back(str);
                board[rowIdx][colIdx] = 1;
                helper(colIdx + 1, board, n, temp);
                temp.pop_back();
                board[rowIdx][colIdx] = 0;
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<int>> board(n, vector<int>(n, 0));
        vector<string> temp;
        helper(0, board, n, temp);
        return ans;
    }
};

int main() {
    int n = 6; 

    Solution sol;
    vector<vector<string>> solutions = sol.solveNQueens(n);

    cout << "Found " << solutions.size() << " solutions for N = " << n << ":" << endl;

    for (const auto& solution : solutions) {
        cout << "----- Solution -----" << endl;
        for (const string& row : solution) {
            cout << row << endl;
        }
        cout << endl;
    }

    return 0;
}