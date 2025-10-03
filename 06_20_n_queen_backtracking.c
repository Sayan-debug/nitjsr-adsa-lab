#include <stdio.h>
#include <stdlib.h>

int N;   // size of board

// Function to print solution board
void printSolution(int board[N][N]) {
    static int solCount = 1;
    printf("\nSolution %d:\n", solCount++);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 1)
                printf(" Q ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

// Check if queen can be placed at board[row][col]
int isSafe(int board[N][N], int row, int col) {
    int i, j;

    // Check column
    for (i = 0; i < row; i++)
        if (board[i][col] == 1)
            return 0;

    // Check upper left diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return 0;

    // Check upper right diagonal
    for (i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j] == 1)
            return 0;

    return 1;
}

// Solve N Queens using backtracking
int solveNQUtil(int board[N][N], int row) {
    if (row == N) {  // all queens placed
        printSolution(board);
        return 1;
    }

    int res = 0;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;   // place queen
            res = solveNQUtil(board, row + 1) || res; // check next row
            board[row][col] = 0;   // backtrack
        }
    }
    return res;
}

// Main solver
void solveNQ() {
    int board[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    if (solveNQUtil(board, 0) == 0) {
        printf("No solution exists for N = %d\n", N);
    }
}

int main() {
    printf("Enter number of queens (N): ");
    scanf("%d", &N);

    solveNQ();

    return 0;
}