#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 
const int rows = 5;
const int cols = 5;

// A function to check if a given cell (row, col) can be included in DFS
int isValid(int mat[rows][cols], int row, int col, bool visited[rows][cols])
{
    // row number is in range, column number is in range and value is 1 
    // and not yet visited
    return (row >= 0) && (row < rows) &&     
           (col >= 0) && (col < cols) &&      
           (mat[row][col] && !visited[row][col]); 
}
 
// check all 8 neighbours
void DFS(int mat[rows][cols], int row, int col, bool visited[rows][cols])
{
    // These arrays are used to get row and column numbers of 8 neighbours 
    // of a given cell
    static int rowInd[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    static int colInd[] = {-1,  0,  1, -1, 1, -1, 0, 1};
 
    // Mark this cell as visited
    visited[row][col] = true;
 
    // Recur for all connected neighbours
    for (int k = 0; k < 8; ++k)
        if (isValid(mat, row + rowInd[k], col + colInd[k], visited) )
            DFS(mat, row + rowInd[k], col + colInd[k], visited);
}
 
// The main function that returns count of islands in a given boolean
// 2D matrix
int countIslands(int mat[rows][cols])
{
    // Make a bool array to mark visited cells.
    bool visited[5][5];
    memset(visited, 0, sizeof(visited));
 
    int count = 0;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (mat[i][j] && !visited[i][j]) // If a cell with value 1 is not
            {                         // visited yet, then new island found
                DFS(mat, i, j, visited);     // Visit all cells in this island.
                ++count;                   // and increment island count
            }
 
    return count;
}

int main()
{
    int mat[rows][cols]= 
	{   {1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1}
    };
	// TODO: unit tests 
    printf("Number of islands is: %d\n", countIslands(mat));
 
    return 0;
}
