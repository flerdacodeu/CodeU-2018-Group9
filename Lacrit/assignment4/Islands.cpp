#include <iostream>
#include <vector>
#include "Islands.h"

int rowInd[] = {-1, 1, 0, 0};
int colInd[] = {0, 0, 1, -1};

Islands::Islands(std::vector<std::vector<bool>> grid) 
{
	this->grid = grid;
	this->rows = grid.size();
	this->cols = grid[0].size();
};

// A function to check if a given cell (row, col) can be included in DFS
bool Islands::isValid(const std::vector<std::vector<bool>> &mat, int row, int col, int rows, int cols, const std::vector<std::vector<bool>> &visited)
{
    return (row >= 0) && (row < rows) && (col >= 0) && (col < cols) && (mat[row][col] && !visited[row][col]); 
}
 
// check 4 neighbours (not diagonally)
void Islands::DFS(const std::vector<std::vector<bool>> &mat, int row, int col, int rows, int cols, std::vector<std::vector<bool>> &visited)
{
    // Mark this cell as visited
    visited[row][col] = true;
 
    // Recur for all connected neighbours
    for (int k = 0; k < 4; ++k)
        if (isValid(mat, row + rowInd[k], col + colInd[k], rows, cols, visited))
            DFS(mat, row + rowInd[k], col + colInd[k], rows, cols, visited);
}
 
// The main function that returns the number of islands in a given boolean 2D matrix
int Islands::countIslands(const std::vector<std::vector<bool>> &mat, int rows, int cols)
{
    // Make a bool array to mark visited cells.
	// Initially all cells are unvisited
	std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    int count = 0;
    for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < cols; j++)
		{
            if (mat[i][j] && !visited[i][j]) // If a cell with value 1 is not visited yet, then new island found
            {                
                DFS(mat, i, j, rows, cols, visited);     // Visit all cells in this island.
                ++count;                     //increment island count
            }
		}
	}
 
    return count;
}

