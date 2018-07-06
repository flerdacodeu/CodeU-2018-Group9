#include <iostream>
#include <vector>

using namespace std;

class IslandCounter {
  vector<vector<bool>> grid;

  /*returns true if the given coordinates ar in the grid's bounds, flase
   * otherwise*/
  bool inBounds(int i, int j);
  /*return true if the given coordinates are of  a legal neighbor,
  (up/down/left/right - this happens if |deltaI-deltaJ|=1)
   and false otherwise*/
  bool isLegalNeighbor(int i, int j, int deltaI, int deltaJ);
  /*updates the land neighbors cells which belong to the islandNum island*/
  void updateNeighbors(int i, int j);

 public:
  IslandCounter(vector<vector<bool>> grid) : grid(grid) {}
  /*Calculates the number of islands in the given grid*/
  int countIslands();
};