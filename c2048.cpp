//All the changes in this version is external help taken from multiple sources 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring> // for memcpy

using namespace std;

const int SIZE = 4;
int grid[SIZE][SIZE] = {0};
int score = 0;

void initializeGame() {
    srand(time(0));
    int placed = 0;
    while (placed < 2) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (grid[x][y] == 0) {
            grid[x][y] = (rand() % 2 + 1) * 2;
            placed++;
        }
    }
}

void displayGrid() {
    system("cls"); // Use "clear" on Unix/Linux/Mac
    cout << "2048 Game\t\tScore: " << score << "\n\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == 0)
                cout << ".\t";
            else
                cout << grid[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void addNewTile() {
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (grid[x][y] != 0);
    grid[x][y] = (rand() % 2 + 1) * 2;
}

bool canMove() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == 0)
                return true;
            if (i < SIZE - 1 && grid[i][j] == grid[i + 1][j])
                return true;
            if (j < SIZE - 1 && grid[i][j] == grid[i][j + 1])
                return true;
        }
    }
    return false;
}

bool gridsEqual(int a[SIZE][SIZE], int b[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (a[i][j] != b[i][j])
                return false;
    return true;
}

void moveLeft() {
    bool merged[SIZE][SIZE] = {false};
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 1; j < SIZE; ++j) {
            if (grid[i][j] != 0) {
                int k = j;
                while (k > 0 && grid[i][k - 1] == 0) {
                    grid[i][k - 1] = grid[i][k];
                    grid[i][k] = 0;
                    k--;
                }
                if (k > 0 && grid[i][k - 1] == grid[i][k] && !merged[i][k - 1]) {
                    grid[i][k - 1] *= 2;
                    score += grid[i][k - 1];
                    grid[i][k] = 0;
                    merged[i][k - 1] = true;
                }
            }
        }
    }
}

void moveRight() {
    bool merged[SIZE][SIZE] = {false};
    for (int i = 0; i < SIZE; ++i) {
        for (int j = SIZE - 2; j >= 0; --j) {
            if (grid[i][j] != 0) {
                int k = j;
                while (k < SIZE - 1 && grid[i][k + 1] == 0) {
                    grid[i][k + 1] = grid[i][k];
                    grid[i][k] = 0;
                    k++;
                }
                if (k < SIZE - 1 && grid[i][k + 1] == grid[i][k] && !merged[i][k + 1]) {
                    grid[i][k + 1] *= 2;
                    score += grid[i][k + 1];
                    grid[i][k] = 0;
                    merged[i][k + 1] = true;
                }
            }
        }
    }
}

void moveUp() {
    bool merged[SIZE][SIZE] = {false};
    for (int j = 0; j < SIZE; ++j) {
        for (int i = 1; i < SIZE; ++i) {
            if (grid[i][j] != 0) {
                int k = i;
                while (k > 0 && grid[k - 1][j] == 0) {
                    grid[k - 1][j] = grid[k][j];
                    grid[k][j] = 0;
                    k--;
                }
                if (k > 0 && grid[k - 1][j] == grid[k][j] && !merged[k - 1][j]) {
                    grid[k - 1][j] *= 2;
                    score += grid[k - 1][j];
                    grid[k][j] = 0;
                    merged[k - 1][j] = true;
                }
            }
        }
    }
}

void moveDown() {
    bool merged[SIZE][SIZE] = {false};
    for (int j = 0; j < SIZE; ++j) {
        for (int i = SIZE - 2; i >= 0; --i) {
            if (grid[i][j] != 0) {
                int k = i;
                while (k < SIZE - 1 && grid[k + 1][j] == 0) {
                    grid[k + 1][j] = grid[k][j];
                    grid[k][j] = 0;
                    k++;
                }
                if (k < SIZE - 1 && grid[k + 1][j] == grid[k][j] && !merged[k + 1][j]) {
                    grid[k + 1][j] *= 2;
                    score += grid[k + 1][j];
                    grid[k][j] = 0;
                    merged[k + 1][j] = true;
                }
            }
        }
    }
}

int main() {
    initializeGame();

    while (true) {
        displayGrid();

        if (!canMove()) {
            cout << "Game Over! Final Score: " << score << endl;
            break;
        }

        cout << "Use WASD to move (W=Up, A=Left, S=Down, D=Right): ";
        string move;
        cin >> move;

        int backup[SIZE][SIZE];
        memcpy(backup, grid, sizeof(grid));

        if (move == "a" || move == "A") moveLeft();
        else if (move == "d" || move == "D") moveRight();
        else if (move == "w" || move == "W") moveUp();
        else if (move == "s" || move == "S") moveDown();
        else {
            cout << "Invalid move! Use W, A, S, or D." << endl;
            continue;
        }

        if (!gridsEqual(backup, grid)) {
            addNewTile();
        } else {
            // Grid didn't change, check again for game over
            if (!canMove()) {
                displayGrid();
                cout << "Game Over! Final Score: " << score << endl;
                break;
            }
        }
    }

    return 0;
}
