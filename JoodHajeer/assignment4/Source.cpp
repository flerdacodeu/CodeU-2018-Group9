#include <iostream>
#include <stdio.h>  
#include <string>
#include <queue>
#include <set>
#include <stdlib.h>
#include"codeu_test_lib.h"
using namespace std;

void DFS(int curRow, int curCol, vector<vector<bool> > * tilesMap) {
	(*tilesMap)[curRow][curCol] = false; //set this tile visited
	int dr[] = {0,0,1,-1};
	int dc[] = {1,-1,0,0};
	for (int i=0;i<4;i++){
		int newRow = curRow + dr[i];
		int newCol = curCol + dc[i];
		if (newRow < 0 || newRow >= (*tilesMap).size() || newCol < 0 || newCol >= (*tilesMap)[newRow].size() || !(*tilesMap)[newRow][newCol] ) // skip tiles that are out on bound or water or already visited 
			continue;
		DFS(newRow, newCol , tilesMap);
	}
}
int countIslands(vector<vector<bool> > tilesMap) {
	int numberOfIslands = 0;
	for (int i = 0; i < tilesMap.size(); i++)
		for (int j = 0; j < tilesMap[i].size(); j++)
			if (tilesMap[i][j]) { //found an island
				DFS(i, j, &tilesMap); //color all tiles of the current island
				++numberOfIslands;
			}
	return numberOfIslands;
}
void testCountIslands_emptyTilesMap() {
	int answer = countIslands({});
	EXPECT_EQ(0, answer);
}
void testCountIslands_singleRow() {
	int answer = countIslands({ { 0, 1, 0, 1, 1 } });
	EXPECT_EQ(2, answer);
}
void testCountIslands_singleCol() {
	int answer = countIslands({ { 1 } ,{ 0 },{ 1 },{ 0 } });
	EXPECT_EQ(2, answer);
}
void testCountIslands_givenCase() {
	int answer = countIslands({ { 0,1,0,1 },{ 1,1,0,0 },{ 0,0,1,0 },{ 0,0,1,0 } });
	EXPECT_EQ(3, answer);
}
int main() {
	testCountIslands_emptyTilesMap();
	testCountIslands_singleRow();
	testCountIslands_singleCol();
	testCountIslands_givenCase();
	return 0;
}
