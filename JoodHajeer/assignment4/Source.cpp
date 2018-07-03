#include <iostream>
#include <stdio.h>  
#include <string>
#include <queue>
#include <set>
#include <stdlib.h>
#include"codeu_test_lib.h"
using namespace std;

void DFS(int curRow, int curCol, int numberOfRows, int numberOfColumns, vector<vector<bool> > & tilesMap) {
	tilesMap[curRow][curCol] = false; //set this tile visited
	int dr[] = {0,0,1,-1};
	int dc[] = {1,-1,0,0};
	for (int i=0;i<4;i++){
		int newRow = curRow + dr[i];
		int newCol = curCol + dc[i];
		if (newRow < 0 || newRow >= numberOfRows || newCol < 0 || newCol >= numberOfColumns || !tilesMap[newRow][newCol]) // skip tiles that are out on bound or water or already visited 
			continue;
		DFS(newRow, newCol, numberOfRows, numberOfColumns, tilesMap);
	}
}
int countIslands(int numberOfRows, int numberOfColumns, vector<vector<bool> > tilesMap) {
	int numberOfIslands = 0;
	for (int i = 0; i < numberOfRows; i++)
		for (int j = 0; j < numberOfColumns; j++)
			if (tilesMap[i][j]) { //found an island
				DFS(i, j, numberOfRows, numberOfColumns,tilesMap); //color all tiles of the current island
				++numberOfIslands;
			}
	return numberOfIslands;
}

void testCountIslands_emptyTilesMap(int numberOfRows, int numberOfColumns, const vector<vector<bool> > tilesMap) {
	int answer = countIslands(numberOfRows, numberOfColumns, tilesMap);
	EXPECT_EQ(0, answer);
}
void testCountIslands_singleRow(int numberOfRows, int numberOfColumns, const vector<vector<bool> > tilesMap) {
	int answer = countIslands(numberOfRows, numberOfColumns, tilesMap);
	EXPECT_EQ(2, answer);
}
void testCountIslands_singleCol(int numberOfRows, int numberOfColumns, const vector<vector<bool> > tilesMap) {
	int answer = countIslands(numberOfRows, numberOfColumns, tilesMap);
	EXPECT_EQ(2, answer);
}
void testCountIslands_givenCase(int numberOfRows, int numberOfColumns, const vector<vector<bool> > tilesMap) {
	int answer = countIslands(numberOfRows, numberOfColumns, tilesMap);
	EXPECT_EQ(3, answer);
}
int main() {
	testCountIslands_emptyTilesMap(0, 0, {});
	testCountIslands_singleRow(1, 5, { {0, 1, 0, 1, 1} });
	testCountIslands_singleCol(4, 1, { {1} , {0}, {1}, {0} });
	testCountIslands_givenCase(4, 4, { {0,1,0,1},{1,1,0,0},{0,0,1,0},{0,0,1,0} });
	return 0;
}
