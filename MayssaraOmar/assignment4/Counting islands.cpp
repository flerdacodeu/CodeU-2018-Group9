#include "test.h"
#include <iostream>
#include <vector>
using namespace std;

static void markIsland(
	const vector<vector<bool>> &grid,
	int row,
	int col,
	vector<vector<bool>> *visited) {
	// boundary check
	if (row < 0 || row >= grid.size() || col < 0 || col >= grid[row].size()) {
		return;
	}
	if ((*visited)[row][col] || !grid[row][col]) {
		return;
	}
	(*visited)[row][col] = true;
	markIsland(grid, row - 1, col, visited); // up
	markIsland(grid, row + 1, col, visited); // down
	markIsland(grid, row, col - 1, visited); // left
	markIsland(grid, row, col + 1, visited); // right
}

int getIslandsCount(const vector<vector<bool>> &grid) {
	vector<vector<bool>> visited(grid.size());
	for (int i = 0; i < grid.size(); i++) {
		visited[i].resize(grid[i].size(), false);
	}
	int count = 0;
	for (int r = 0; r < grid.size(); r++) {
		for (int c = 0; c < grid[r].size(); c++) {
			if (grid[r][c] && !visited[r][c]) {
				count++;
				markIsland(grid, r, c, &visited);
			}
		}
	}
	return count;
}

// tests
void emptyGrid_test() {
	vector<vector<bool>> grid;
	EXPECT_EQ(0, getIslandsCount(grid));
}

void landGrid_test() {
	vector<vector<bool>> grid = {{true, true, true},
                                 {true, true, true},
                                 {true, true, true}};
	EXPECT_EQ(1, getIslandsCount(grid));
}

void waterGrid_test() {
	vector<vector<bool>> grid = {{false, false, false},
                                 {false, false, false},
                                 {false, false, false}};
	EXPECT_EQ(0, getIslandsCount(grid));
}

void normalGrid_test() {
	vector<vector<bool>> grid = {{false, true, false, true},
                                 {true, true, false, false},
                                 {false, false, true, false},
                                 {false, false, true, false}};
	EXPECT_EQ(3, getIslandsCount(grid));
}

void oneLandTile_test() {
	vector<vector<bool>> grid = {{true}};
	EXPECT_EQ(1, getIslandsCount(grid));
}

void oneWaterTile_test() {
	vector<vector<bool>> grid = {{false}};
	EXPECT_EQ(0, getIslandsCount(grid));
}

void zigzagGrid_test() {
	vector<vector<bool>> grid = {{false, false, true, false},
                                 {false, true, false, false},
                                 {false, false, true, false},
                                 {false, true, false, false}};
	EXPECT_EQ(4, getIslandsCount(grid));
}

void diagonalLandGrid_test() {
	vector<vector<bool>> grid = {{true, false, false, false},
                                 {false, true, false, false},
                                 {false, false, true, false},
                                 {false, false, false, true}};
	EXPECT_EQ(4, getIslandsCount(grid));
}

void diagonalWaterGrid_test() {
	vector<vector<bool>> grid = {{true, true, true, false},
                                 {true, true, false, true},
                                 {true, false, true, true},
                                 {false, true, true, true}};
	EXPECT_EQ(2, getIslandsCount(grid));
}

void unevenGrid_test() {
	vector<vector<bool>> grid = {{true, true},
                                 {true, true, false, true},
                                 {false},
                                 {false, true, true}};
	EXPECT_EQ(3, getIslandsCount(grid));
}
int main() {
	// tests
	emptyGrid_test();
	landGrid_test();
	waterGrid_test();
	normalGrid_test();
	oneLandTile_test();
	oneWaterTile_test();
	zigzagGrid_test();
	diagonalLandGrid_test();
	diagonalWaterGrid_test();
	unevenGrid_test();
	return 0;
}

