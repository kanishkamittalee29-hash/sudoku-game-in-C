/*
    Sudoku Game 
    Description: A simple console Sudoku where you fill the empty cells.
*/

#include <stdio.h>

#define SIZE 9
#define EMPTY 0

// Prints the Sudoku board
void printBoard(int b[SIZE][SIZE]) {
    printf("\n   1 2 3   4 5 6   7 8 9\n");
    printf("  +-------+-------+-------+\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d | ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            if (b[i][j] == EMPTY) printf(". ");
            else printf("%d ", b[i][j]);
            if ((j + 1) % 3 == 0) printf("| ");
        }
        printf("\n");
        if ((i + 1) % 3 == 0) printf("  +-------+-------+-------+\n");
    }
}

// Checks if a number can be placed safely
int isSafe(int b[SIZE][SIZE], int row, int col, int num) {
    for (int x = 0; x < SIZE; x++)
        if (b[row][x] == num || b[x][col] == num)
            return 0;

    int sr = row - row % 3, sc = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[sr + i][sc + j] == num)
                return 0;

    return 1;
}

// Basic Sudoku puzzle
void setPuzzle(int p[SIZE][SIZE]) {
    int temp[SIZE][SIZE] = {
        {5,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 0,6,0},
        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},
        {0,6,0, 0,0,0, 2,8,0},
        {0,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9}
    };
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            p[i][j] = temp[i][j];
}

// Checks if the board is full
int isFull(int b[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (b[i][j] == EMPTY)
                return 0;
    return 1;
}

int main() {
    int puzzle[SIZE][SIZE];
    setPuzzle(puzzle);

    int row, col, num;
    printf("\n=== Simple Sudoku Game ===\n");
    printf("Enter your move as: row col number (e.g. 1 3 5)\n");
    printf("Enter 0 0 0 to quit.\n");

    while (1) {
        printBoard(puzzle);
        printf("\nYour move: ");
        scanf("%d %d %d", &row, &col, &num);

        if (row == 0 && col == 0 && num == 0) {
            printf("You exited the game. Goodbye!\n");
            break;
        }

        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
            printf("Invalid input! Please enter numbers between 1 and 9.\n");
            continue;
        }

        if (puzzle[row-1][col-1] != EMPTY) {
            printf("This cell is fixed. You cannot change it.\n");
            continue;
        }

        if (!isSafe(puzzle, row-1, col-1, num)) {
            printf("That number breaks Sudoku rules. Try another one.\n");
            continue;
        }

        puzzle[row-1][col-1] = num;
        printf("Move accepted!\n");

        if (isFull(puzzle)) {
            printf("\n Congratulations! You filled all cells!\n");
            printBoard(puzzle);
            break;
        }
    }

    return 0;
}