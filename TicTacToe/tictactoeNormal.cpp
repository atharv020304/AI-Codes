#include <iostream>
#include <vector>
using namespace std;

class Game {
public:
    bool winnerFound = false;
    vector<vector<void*>> board;

    Game() : board(3, vector<void*>(3, nullptr)) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = nullptr;
            }
        }
    }

    void checkifwinFound() {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != nullptr && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                winnerFound = true;
                return;
            }
            if (board[0][i] != nullptr && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                winnerFound = true;
                return;
            }
        }
        if (board[0][0] != nullptr && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            winnerFound = true;
            return;
        }
        if (board[0][2] != nullptr && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            winnerFound = true;
            return;
        }
    }

    void Play() {
        int currMove = 0;
        while (true) {
            int i, j;

            cout << "\nCurrent Board:\n";
            for (auto row : board) {
                for (auto cell : row) {
                    if (cell == nullptr) {
                        cout << ". ";
                    } else {
                        cout << (char*)cell << " ";
                    }
                }
                cout << endl;
            }

            if (currMove == 0) {
                cout << "Player one (O), enter row and column: ";
                cin >> i >> j;
                if (i < 0 || i >= 3 || j < 0 || j >= 3 || board[i][j] != nullptr) {
                    cout << "Invalid move. Try again.\n";
                    continue;
                }
                board[i][j] = (void*)"O";
                currMove = 1;
            } else {
                cout << "Player two (X), enter row and column: ";
                cin >> i >> j;
                if (i < 0 || i >= 3 || j < 0 || j >= 3 || board[i][j] != nullptr) {
                    cout << "Invalid move. Try again.\n";
                    continue;
                }
                board[i][j] = (void*)"X";
                currMove = 0;
            }

            checkifwinFound();
            if (winnerFound) {
                cout << "Player " << (currMove == 1 ? "one (O)" : "two (X)") << " wins!\n";
                break;
            }
        }
    }
};

int main() {
    Game b;
    b.Play();
    return 0;
}