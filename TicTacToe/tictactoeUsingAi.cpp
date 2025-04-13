#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Game {
public:
    bool winnerFound = false;
    vector<vector<char>> board;

    Game() : board(3, vector<char>(3, ' ')) {}

    void displayBoard() {
        cout << "\nCurrent Board:\n";
        for (auto row : board) {
            for (auto cell : row) {
                cout << (cell == ' ' ? '.' : cell) << " ";
            }
            cout << endl;
        }
    }

    char checkWinner() {
       
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return board[i][0];
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return board[0][i];
        }
       
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return board[0][0];
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return board[0][2];
        return ' ';
    }

    bool isFull() {
        for (auto row : board)
            for (auto cell : row)
                if (cell == ' ')
                    return false;
        return true;
    }

    int minimax(bool isMaximizing) {
        char winner = checkWinner();
        if (winner == 'X') return +1;
        if (winner == 'O') return -1;
        if (isFull()) return 0;

        if (isMaximizing) {
            int bestScore = numeric_limits<int>::min();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'X';
                        int score = minimax(false);
                        board[i][j] = ' ';
                        bestScore = max(bestScore, score);
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = numeric_limits<int>::max();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'O';
                        int score = minimax(true);
                        board[i][j] = ' ';
                        bestScore = min(bestScore, score);
                    }
                }
            }
            return bestScore;
        }
    }

    void bestMove() {
        int bestScore = numeric_limits<int>::min();
        int moveRow = -1, moveCol = -1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(false);
                    board[i][j] = ' ';
                    if (score > bestScore) {
                        bestScore = score;
                        moveRow = i;
                        moveCol = j;
                    }
                }
            }
        }
        board[moveRow][moveCol] = 'X';
        cout << "AI (X) plays: " << moveRow << " " << moveCol << endl;
    }

    void Play() {
        int currMove = 0;
        while (true) {
            displayBoard();
            char winner = checkWinner();
            if (winner != ' ') {
                cout << "Player " << (winner == 'O' ? "One (O)" : "Two (X)") << " wins!\n";
                break;
            }
            if (isFull()) {
                cout << "It's a draw!\n";
                break;
            }

            int i, j;
            if (currMove == 0) {
                cout << "Player one (O), enter row and column: ";
                cin >> i >> j;
                if (i < 0 || i >= 3 || j < 0 || j >= 3 || board[i][j] != ' ') {
                    cout << "Invalid move. Try again.\n";
                    continue;
                }
                board[i][j] = 'O';
                currMove = 1;
            } else {
                bestMove(); 
                currMove = 0;
            }
        }
    }
};

int main() {
    Game b;
    b.Play();
    return 0;
}
