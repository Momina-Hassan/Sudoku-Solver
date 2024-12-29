#include<stdio.h>
#include<stdbool.h>

//Global definitions and variables.  
#define N 9
int row = 0;
int col = 0;
int count = 0;


//This function checks if the number is a valid number to be placed in the cell.
bool is_valid(int grid[N][N], int row, int col, int num) 
{
    //Checks if the number exists in the current row or column.
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    //Checking if the number exists in the 3x3 subgrid.
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    //The number is valid (not present in the row, column, or subgrid)
    return true;
}

bool solveSudoku(int grid[N][N], int row, int col) {
    // counts the number of times the function was called
    count++; 

    //Reached the end of the grid so a solution was found.
    if(row == N-1 && col == N) {
        return true;
    }

    //Reached the end of the row so goes to the next row and resets column to 0.  
    if(col == N) {
        col = 0;
        row++;
    }

    //If the cell already has a value, go to the next column. 
    if(grid[row][col] != 0) {
        return solveSudoku(grid, row, col+1);
    }

    //Go through numbers 1-9 and check if valid. If valid, sets the current cell to num. 
    for(int num = 1; num < 10; num++) {
        if(is_valid(grid, row, col, num)) {

            grid[row][col] = num;

            //Solves for the next column to check if solution is successful.
            if (solveSudoku(grid, row, col + 1)) {
                return true;
            }
            //If not successful, backtracks. 
            grid[row][col] = 0; 
        }
    }
    return false;

}

//Function to print the 9x9 grid.
void printGrid(int grid[N][N]) {

    int counterRow = 0;

    for (int i = 0; i < N; i++) {
        int counterCol = 0;
        for (int j = 0; j < N; j++) {
            printf("%d", grid[i][j]);
            if (counterCol == 2 || counterCol == 5 || counterCol == 8) {
                printf(" | ");
            } else {
                printf(" ");
            }
            counterCol++;
        }

        printf("\n");
        if (counterRow == 2 || counterRow == 5) {
            printf("-----------------------\n");
        }
        counterRow++;
    }
}


int main () {
    // Initializing grid and giving it input.
    int grid[N][N] = {
        {0, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 6, 0, 0, 0, 0, 3},
        {0, 7, 4, 0, 8, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0, 2},
        {0, 8, 0, 0, 4, 0, 0, 1, 0},
        {6, 0, 0, 5, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 7, 8, 0},
        {5, 0, 0, 0, 0, 9, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 4, 0}};
    
    //Printing the unsolved puzzle.
    printf("The input Sudoku puzzle: \n");
    printGrid(grid);
    printf("\n");

    //If solution exists, print the solved puzzle.
    if(solveSudoku(grid, row, col)) {
        // If the puzzle is solved then:
        printf("Solution found after %d iterations: \n", count);
        printGrid(grid);

    } else {
        printf("No solution exists. \n");
    }

    return 0;
}
