#include <iostream>
#include <vector>
using namespace std;
const int BOARD_SIZE = 3;
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = ' ';
// Represents a move on the board
struct Move
{
    int row;
    int col;
};
// Represents the game board
struct Board
{
    vector<vector<char>> cells;
    Board()
    {
        cells.resize(BOARD_SIZE,
                     vector<char>(BOARD_SIZE, EMPTY));
    }
    bool isFull() const
    {
        for (const auto &row : cells)
        {
            for (const auto &cell : row)
            {
                if (cell == EMPTY)
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool isWinningMove(const Move &move, char player)
        const
    {
        int row = move.row;
        int col = move.col;
        // Check row
        if (cells[row][0] == player && cells[row][1] == player && cells[row][2] == player)
        {
            return true;
        }
        // Check column
        if (cells[0][col] == player && cells[1][col] == player && cells[2][col] == player)
        {
            return true;
        }
        // Check diagonals
        if (row == col)
        {
            if (cells[0][0] == player && cells[1][1] == player && cells[2][2] == player)
            {
                return true;
            }
        }
        if (row + col == 2)
        {
            if (cells[0][2] == player && cells[1][1] == player && cells[2][0] == player)
            {
                return true;
            }
        }
        return false;
    }
    void print() const
    {
        for (const auto &row : cells)
        {
            for (const auto &cell : row)
            {
                cout << cell << ' ';
            }
            cout << endl;
        }
    }
};
// Evaluates the current state of the board
int evaluate(const Board &board)
{
    // Check rows
    for (const auto &row : board.cells)
    {
        if (row[0] == row[1] && row[1] == row[2])
        {
            if (row[0] == PLAYER_X)
            {
                return 1;
            }
            else if (row[0] == PLAYER_O)
            {
                return -1;
            }
        }
    }
    // Check columns
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        if (board.cells[0][col] == board.cells[1][col] &&
            board.cells[1][col] == board.cells[2][col])
        {
            if (board.cells[0][col] == PLAYER_X)
            {
                return 1;
            }
            else if (board.cells[0][col] == PLAYER_O)
            {
                return -1;
            }
        }
    }

    // Check diagonals
    if (board.cells[0][0] == board.cells[1][1] &&
        board.cells[1][1] == board.cells[2][2])
    {
        if (board.cells[0][0] == PLAYER_X)
        {
            return 1;
        }
        else if (board.cells[0][0] == PLAYER_O)
        {
            return -1;
        }
    }
    if (board.cells[0][2] == board.cells[1][1] &&
        board.cells[1][1] == board.cells[2][0])
    {
        if (board.cells[0][2] == PLAYER_X)
        {
            return 1;
        }
        else if (board.cells[0][2] == PLAYER_O)
        {
            return -1;
        }
    }
    // No winner
    return 0;
}
// Minimax algorithm implementation
int minimax(Board &board, int depth, bool isMaximizingPlayer)
{
    int score = evaluate(board);
    // If the game is over, return the score
    if (score != 0)
    {
        return score;
    }
    // If the board is full, it's a tie
    if (board.isFull())
    {
        return 0;
    }
    // If it's the maximizing player's turn
    if (isMaximizingPlayer)
    {
        int bestScore = -1000;
        // Find the maximum score by recursively
        // evaluating each possible move 
        for (int row = 0; row < BOARD_SIZE; ++row)
        {
            for (int col = 0; col < BOARD_SIZE; ++col)
            {
                if (board.cells[row][col] == EMPTY)
                {
                    board.cells[row][col] = PLAYER_X;
                    bestScore = max(bestScore, minimax(board,
                                                       depth + 1, false));
                    board.cells[row][col] = EMPTY;
                }
            }
        }
        return bestScore;
    }
    // If it's the minimizing player's turn
    else
    {
        int bestScore = 1000;
        // Find the minimum score by recursively evaluating
        // each possible move
        for (int row = 0; row < BOARD_SIZE; ++row)
        {
            for (int col = 0; col < BOARD_SIZE; ++col)
            {
                if (board.cells[row][col] == EMPTY)
                {
                    board.cells[row][col] = PLAYER_O;
                    bestScore = min(bestScore, minimax(board,
                                                       depth + 1, true));
                    board.cells[row][col] = EMPTY;
                }
            }
        }
        return bestScore;
    }
}
// Determines the best move for the AI player using the
// Minimax algorithm
Move findBestMove(Board &board)
{
    int bestScore = -1000;
    Move bestMove;
    // Find the move with the maximum score
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (board.cells[row][col] == EMPTY)
            {
                board.cells[row][col] = PLAYER_X;
                int score = minimax(board, 0, false);
                board.cells[row][col] = EMPTY;
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove.row = row;
                    bestMove.col = col;
                }
            }
        }
    }
    return bestMove;
}
int main()
{
    Board board;

    // Play the game until there's a winner or a tie
    while (true)
    {
        // Player's move
        int row, col;
        cout << "Enter your move (row and column): ";
        cin >> row >> col;
        if (board.cells[row][col] == EMPTY)
        {
            board.cells[row][col] = PLAYER_O;
        }
        else
        {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board.print();
        if (board.isWinningMove({row, col}, PLAYER_O))
        {
            cout << "You win!" << endl;
            break;
        }
        if (board.isFull())
        {

            cout << "It's a tie!" << endl;
            break;
        }
        // AI player's move
        cout << "AI player's move:" << endl;
        Move aiMove = findBestMove(board);
        board.cells[aiMove.row][aiMove.col] = PLAYER_X;
        board.print();
        if (board.isWinningMove(aiMove, PLAYER_X))
        {
            cout << "AI player wins!" << endl;
            break;
        }
        if (board.isFull())
        {
            cout << "It's a tie!" << endl;
            break;
        }
    }
    return 0;
}



