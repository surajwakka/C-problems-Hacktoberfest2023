#include <stdio.h>

#define N 9

int isSafe(int board[N][N], int row, int col, int num);

int solveSudoku(int board[N][N]) {
    int row, col;
    
    if (!findUnassignedLocation(board, &row, &col))
        return 1;
    
    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            
            if (solveSudoku(board))
                return 1;
            
            board[row][col] = 0;
        }
    }
    return 0;
}

int findUnassignedLocation(int board[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++)
        for (*col = 0; *col < N; (*col)++)
            if (board[*row][*col] == 0)
                return 1;
    return 0;
}

int isSafe(int board[N][N], int row, int col, int num) {
    return !usedInRow(board, row, num) &&
           !usedInCol(board, col, num) &&
           !usedInBox(board, row - row % 3, col - col % 3, num);
}

int usedInRow(int board[N][N], int row, int num) {
    for (int col = 0; col < N; col++)
        if (board[row][col] == num)
            return 1;
    return 0;
}

int usedInCol(int board[N][N], int col, int num) {
    for (int row = 0; row < N; row++)
        if (board[row][col] == num)
            return 1;
    return 0;
}

int usedInBox(int board[N][N], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (board[row + boxStartRow][col + boxStartCol] == num)
                return 1;
    return 0;
}

void printBoard(int board[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%2d ", board[row][col]);
        }
        printf("\n");
    }
}

int main() {
    int board[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board) == 1)
        printBoard(board);
    else
        printf("No solution exists\n");

    return 0;
}
