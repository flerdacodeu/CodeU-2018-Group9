#include <iostream>
#include <vector>
#include "IslandCounter.h"

using namespace std;

/*returns true if the given coordinates ar in the grid's bounds, flase
 * otherwise*/
bool IslandCounter::inBounds(int i, int j) {
  return (i >= 0 && i < grid.size()) && (j >= 0 && j < grid[i].size());
}

/*return true if the given coordinates are of  a legal neighbor,
(up/down/left/right - this happens if |deltaI-deltaJ|=1)
 and false otherwise*/
bool IslandCounter::isLegalNeighbor(int i, int j, int deltaI, int deltaJ) {
  return (inBounds(i, j) && (abs(deltaI - deltaJ) == 1));
}

/*updates the land neighbors cells which belong to the current island*/
void IslandCounter::updateNeighbors(int i, int j) {
  for (int rowDelta : {0, 1, -1}) {
    for (int colDelta : {0, 1, -1}) {
      int newI = i + rowDelta;
      int newJ = j + colDelta;
      if (isLegalNeighbor(newI, newJ, rowDelta, colDelta) && grid[newI][newJ]) {
        grid[newI][newJ] = false;
        updateNeighbors(newI, newJ);
      }
    }
  }
}

/*Calculates the number of islands in the given grid*/
int IslandCounter::countIslands() {
  if (grid.empty()) {
    return 0;
  }
  int count = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j]) {
        grid[i][j] = false;
        count++;
        updateNeighbors(i, j);
      }
    }
  }
  return count;
}
