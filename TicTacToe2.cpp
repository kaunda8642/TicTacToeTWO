// TicTacToe2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <vector>
#include <cctype>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];

struct Player {
    char mark;
    string archetype;
};

// ---------- Utility Functions ----------
void initializeBoard() {
    char pos = '1';
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = pos++;
}

void printBoard() {
    cout << "\nCurrent board:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << " " << board[i][j];
            if (j < SIZE - 1) cout << " |";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool getCoordinates(int cell, int& row, int& col) {
    if (cell < 1 || cell > 9) return false;
    row = (cell - 1) / SIZE;
    col = (cell - 1) % SIZE;
    return true;
}

char checkWinner() {
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    bool full = true;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (!isalpha(board[i][j]) && !ispunct(board[i][j]))
                full = false;

    if (full) return 'T';
    return ' ';
}

bool isValidMark(char c) {
    string valid = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz?!*~$%#";
    return valid.find(c) != string::npos;
}

// ---------- Regular Tic-Tac-Toe ----------
void playRegular() {
    initializeBoard();
    char currentPlayer = 'X';
    char winner = ' ';

    while (winner == ' ') {
        printBoard();
        int move;
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        if (!(cin >> move)) {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        int row, col;
        if (!getCoordinates(move, row, col) || board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[row][col] = currentPlayer;
        winner = checkWinner();
        if (winner == ' ') currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    printBoard();
    if (winner == 'T') cout << "It's a tie!\n";
    else cout << "Player " << winner << " wins!\n";
}

// ---------- Battle Tic-Tac-Toe ----------
bool isAdjacent(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) <= 1 && abs(c1 - c2) <= 1 && !(r1 == r2 && c1 == c2);
}

void alchemistSwap() {
    int a, b;
    cout << "Enter two cell numbers to swap (1-9): ";
    cin >> a >> b;

    int r1, c1, r2, c2;
    if (!getCoordinates(a, r1, c1) || !getCoordinates(b, r2, c2)) {
        cout << "Invalid cells!\n";
        return;
    }
    if (board[r1][c1] == board[r2][c2]) {
        cout << "Can't swap identical marks!\n";
        return;
    }
    if (!isalpha(board[r1][c1]) && !ispunct(board[r1][c1])) {
        cout << "Cell " << a << " is empty.\n";
        return;
    }
    if (!isalpha(board[r2][c2]) && !ispunct(board[r2][c2])) {
        cout << "Cell " << b << " is empty.\n";
        return;
    }

    swap(board[r1][c1], board[r2][c2]);
}

void paladinShift() {
    int src, dest;
    cout << "Enter the cell number to shift (1-9): ";
    cin >> src;
    cout << "Enter the destination cell (1-9): ";
    cin >> dest;

    int r1, c1, r2, c2;
    if (!getCoordinates(src, r1, c1) || !getCoordinates(dest, r2, c2)) {
        cout << "Invalid cells!\n";
        return;
    }
    if (!isalpha(board[r1][c1]) && !ispunct(board[r1][c1])) {
        cout << "Source is empty!\n";
        return;
    }
    if (isalpha(board[r2][c2]) || ispunct(board[r2][c2])) {
        cout << "Destination occupied!\n";
        return;
    }
    if (!isAdjacent(r1, c1, r2, c2)) {
        cout << "Destination must be adjacent!\n";
        return;
    }

    board[r2][c2] = board[r1][c1];
    board[r1][c1] = '0' + (src);
}

void playBattle() {
    Player p1, p2;
    initializeBoard();

    cout << "Enter Player 1 mark: ";
    cin >> p1.mark;
    while (!isValidMark(p1.mark)) {
        cout << "Invalid mark! Choose a valid symbol: ";
        cin >> p1.mark;
    }

    cout << "Enter Player 2 mark: ";
    cin >> p2.mark;
    while (!isValidMark(p2.mark) || p2.mark == p1.mark) {
        cout << "Invalid or duplicate mark! Choose another: ";
        cin >> p2.mark;
    }

    cout << "Choose Player 1 archetype (Paladin/Alchemist): ";
    cin >> p1.archetype;
    while (p1.archetype != "Paladin" && p1.archetype != "Alchemist") {
        cout << "Invalid choice! Try again: ";
        cin >> p1.archetype;
    }

    cout << "Choose Player 2 archetype (Paladin/Alchemist): ";
    cin >> p2.archetype;
    while (p2.archetype != "Paladin" && p2.archetype != "Alchemist") {
        cout << "Invalid choice! Try again: ";
        cin >> p2.archetype;
    }

    char winner = ' ';
    Player current = p1;

    while (winner == ' ') {
        printBoard();
        cout << "\n" << current.mark << " (" << current.archetype << ")'s turn.\n";
        cout << "1. Regular move\n2. Special move\nChoose: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int move;
            cout << "Enter move (1-9): ";
            cin >> move;
            int r, c;
            if (!getCoordinates(move, r, c) || isalpha(board[r][c]) || ispunct(board[r][c])) {
                cout << "Invalid move!\n";
                continue;
            }
            board[r][c] = current.mark;
        }
        else if (choice == 2) {
            if (current.archetype == "Alchemist") alchemistSwap();
            else if (current.archetype == "Paladin") paladinShift();
            else cout << "Invalid archetype.\n";
        }
        else {
            cout << "Invalid choice.\n";
            continue;
        }

        winner = checkWinner();
        if (winner == ' ') current = (current.mark == p1.mark) ? p2 : p1;
    }

    printBoard();
    if (winner == 'T') cout << "It's a tie!\n";
    else cout << "Player with mark " << winner << " wins!\n";
}

// ---------- Main ----------
int main() {
    bool playAgain = true;
    while (playAgain) {
        cout << "\n=== TIC-TAC-TOE MENU ===\n";
        cout << "1. Regular Tic-Tac-Toe\n";
        cout << "2. Battle Tic-Tac-Toe\n";
        cout << "Choose a mode: ";
        int choice;
        cin >> choice;

        if (choice == 1) playRegular();
        else if (choice == 2) playBattle();
        else {
            cout << "Invalid choice.\n";
            continue;
        }

        cout << "\nPlay again? (y/n): ";
        char ans;
        cin >> ans;
        playAgain = (ans == 'y' || ans == 'Y');
    }

    cout << "Thanks for playing!\n";
    return 0;
}
