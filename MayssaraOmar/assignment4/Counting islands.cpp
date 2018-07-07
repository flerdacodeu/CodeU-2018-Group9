#include "test.h"
#include <iostream>
#include <vector>
using namespace std;

static void markIsland(const vector<vector<bool>> &grid, int row, int col, vector<vector<bool>> *visited) {
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

// helping method to convert a vector of strings to a vector of vector of bool
static vector<vector<bool>> stringToBool(const vector<string> &input){
  vector<vector<bool>> ret(input.size());
  for(int i=0; i<input.size(); i++){
    for(char c: input[i]){
      ret[i].push_back(c=='T'? true : false);
    }
  }
  return ret;
}

void emptyGrid_test() {
	vector<vector<bool>> grid;
	EXPECT_EQ(0, getIslandsCount(grid));
}

void landGrid_test() {
  vector<vector<bool>> grid = stringToBool(vector<string> (3, "TTT"));
	EXPECT_EQ(1, getIslandsCount(grid));
}

void waterGrid_test() {
	vector<vector<bool>> grid = stringToBool(vector<string> (3, "FFF"));
	EXPECT_EQ(0, getIslandsCount(grid));
}

void normalGrid_test() {
  vector<string> grid = {"FTFT",
                         "TTFF",
                         "FFTF",
                         "FFTF"};
	EXPECT_EQ(3, getIslandsCount(stringToBool(grid)));
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
  vector<string> grid = {"FFTF",
                         "FTFF",
                         "FFTF",
                         "FTFF"};
	EXPECT_EQ(4, getIslandsCount(stringToBool(grid)));
}

void diagonalLandGrid_test() {
  vector<string> grid = {"TFFF",
                         "FTFF",
                         "FFTF",
                         "FFFT"};
	EXPECT_EQ(4, getIslandsCount(stringToBool(grid)));
}

void diagonalWaterGrid_test() {
  vector<string> grid = {"TTTF",
                         "TTFT",
                         "TFTT",
                         "FTTT"};
	EXPECT_EQ(2, getIslandsCount(stringToBool(grid)));
}

void unevenGrid_test() {
  vector<string> grid = {"TT",
                         "TTFT",
                         "F",
                         "FTT"};
	EXPECT_EQ(3, getIslandsCount(stringToBool(grid)));
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
