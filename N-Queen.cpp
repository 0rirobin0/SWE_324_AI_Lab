#include <iostream>
#include <vector>

using namespace std;

// Function to check if a queen can be safely placed at board[row][col]
bool isSafe(const vector<string>& board, int row, int col, int n) {
    // Check if there's a queen in the same column
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 'Q') {
            return false;
        }
    }

    // Check the upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    // Check the upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    return true;
}

// Recursive function to solve the N-Queens problem
void solveNQueens(vector<string>& board, int row, int n) {
    // Base case: if all queens are placed
    if (row == n) {
        // Print the solution
        for (const string& line : board) {
            cout << line << endl;
        }
        cout << endl;
        return;
    }

    // Try placing a queen in each column of the current row
    for (int col = 0; col < n; ++col) {
        if (isSafe(board, row, col, n)) {
            // Place a queen at board[row][col]
            board[row][col] = 'Q';
            // Recursively place queens in the next row
            solveNQueens(board, row + 1, n);
            // Backtrack: remove the queen from board[row][col]
            board[row][col] = '.';
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;

    // Initialize the board with '.'
    vector<string> board(n, string(n, '.'));

    // Start solving from the first row
    solveNQueens(board, 0, n);

    return 0;
}
