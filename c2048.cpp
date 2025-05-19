#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int SIZE = 4; // Size of the grid
int grid[SIZE][SIZE] = {0}; // Initialize the grid

void initializeGame() {
    srand(time(0));
    for (int i = 0; i < 2; ++i) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        grid[x][y] = (rand() % 2 + 1) * 2; // Place a 2 or 4
    }
}

void displayGrid() {
    system("cls"); // Clear the console
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == 0)
                cout << ".\t";
            else
                cout << grid[i][j] << "\t";
        }
        cout << endl;
    }
}

void addNewTile() {
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (grid[x][y] != 0);
    grid[x][y] = (rand() % 2 + 1) * 2; // Place a 2 or 4
}

bool canMove() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == 0) return true; // Empty space exists
            if (i < SIZE - 1 && grid[i][j] == grid[i + 1][j]) return true; // Vertical merge possible
            if (j < SIZE - 1 && grid[i][j] == grid[i][j + 1]) return true; // Horizontal merge possible
        }
    }
    return false; // No moves left
}


void moveLeft() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 1; j < SIZE; ++j) {
            if (grid[i][j] != 0) {
                int k = j;
                while (k > 0 && grid[i][k - 1] == 0) {
                    grid[i][k - 1] = grid[i][k];
                    grid[i][k] = 0;
                    k--;
                }
                if (k > 0 && grid[i][k - 1] == grid[i][k]) {
                    grid[i][k - 1] *= 2;
                    grid[i][k] = 0;
                }
            }
        }
    }
}

void moveRight() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = SIZE - 2; j >= 0; --j) {
            if (grid[i][j] != 0) {
                int k = j;
                while (k < SIZE - 1 && grid[i][k + 1] == 0) {
                    grid[i][k + 1] = grid[i][k];
                    grid[i][k] = 0;
                    k++;
                }
                if (k < SIZE - 1 && grid[i][k + 1] == grid[i][k]) {
                    grid[i][k + 1] *= 2;
                    grid[i][k] = 0;
                }
            }
        }
    }
}

void moveUp() {
    for (int j = 0; j < SIZE; ++j) {
        for (int i = 1; i < SIZE; ++i) {
            if (grid[i][j] != 0) {
                int k = i;
                while (k > 0 && grid[k - 1][j] == 0) {
                    grid[k - 1][j] = grid[k][j];
                    grid[k][j] = 0;
                    k--;
                }
                if (k > 0 && grid[k - 1][j] == grid[k][j]) {
                    grid[k - 1][j] *= 2;
                    grid[k][j] = 0;
                }
            }
        }
    }
}

void moveDown() {
    for (int j = 0; j < SIZE; ++j) {
        for (int i = SIZE - 2; i >= 0; --i) {
            if (grid[i][j] != 0) {
                int k = i;
                while (k < SIZE - 1 && grid[k + 1][j] == 0) {
                    grid[k + 1][j] = grid[k][j];
                    grid[k][j] = 0;
                    k++;
                }
                if (k < SIZE - 1 && grid[k + 1][j] == grid[k][j]) {
                    grid[k + 1][j] *= 2;
                    grid[k][j] = 0;
                }
            }
        }
    }
}

int main() {
    initializeGame();
    displayGrid();
    
    while (canMove()) {
        char move;
        cout << "Use WASD to move (W=Up, A=Left, S=Down, D=Right): ";
        cin >> move; // Get user input

        switch (move) {
            case 'a': moveLeft(); break;
            case 'd': moveRight(); break;
            case 'w': moveUp(); break;
            case 's': moveDown(); break;
            default: cout << "Invalid move! Use W, A, S, or D." << endl; continue;
        }
        addNewTile();
        displayGrid();
    }

    cout << "Game Over!" << endl;
    return 0;
}
