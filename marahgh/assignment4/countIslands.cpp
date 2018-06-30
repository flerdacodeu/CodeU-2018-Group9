#include <iostream>
#include <vector>

using namespace std;

/*returns true if the given coordinates ar in the grid's bounds, flase
 * otherwise*/
bool inBounds(int rows, int cols, int i, int j) {
  return (i >= 0 && i < rows) && (j >= 0 && j < cols);
}

/*return true if the given coordinates are of  a legal neighbor of (i,j),
  and false otherwise*/
bool isLegalNeighbor(int rows, int cols, int i, int j, int deltaI, int deltaJ) {
  return (inBounds(rows, cols, i, j) && (abs(deltaI - deltaJ) == 1));
}

/*Calculates the number of island which the given coordinates belong to*/
int findIslandNum(int rows, int cols, int i, int j, vector<vector<bool>> grid,
                  vector<vector<int>>* visited, int count) {
  int islandNum = 0;
  for (int rowDelta : {0, 1, -1}) {
    for (int colDelta : {0, 1, -1}) {
      int newI = i + rowDelta;
      int newJ = j + colDelta;
      if (isLegalNeighbor(rows, cols, newI, newJ, rowDelta, colDelta)) {
        if ((*visited)[newI][newJ] != 0) {
          islandNum = (*visited)[newI][newJ];
        }
      }
    }
  }
  if (islandNum == 0) {
    islandNum = count;
  }
  return islandNum;
}

/*updates the land neighbors cells which belong to the islandNum island*/
void updateNeighbors(int rows, int cols, int i, int j,
                     vector<vector<bool>> grid, vector<vector<int>>* visited,
                     int islandNum) {
  for (int rowDelta : {0, 1, -1}) {
    for (int colDelta : {0, 1, -1}) {
      int newI = i + rowDelta;
      int newJ = j + colDelta;
      if (isLegalNeighbor(rows, cols, newI, newJ, rowDelta, colDelta) &&
          grid[newI][newJ]) {
        (*visited)[newI][newJ] = islandNum;
      }
    }
  }
}

/*Calculates the number of islands in the given grid*/
int countIslands(int rows, int cols, vector<vector<bool>> grid) {
  if (rows <= 0 || cols <= 0 || grid.empty() ||
      (rows * cols != grid.size() * grid[0].size())) {
    return 0;
  }
  vector<vector<int>> visited(rows, vector<int>(cols, 0));
  int count = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j]) {
        int islandNum = findIslandNum(rows, cols, i, j, grid, &visited, count);
        if (islandNum == count) {
          count++;
        }
        visited[i][j] = islandNum;
        updateNeighbors(rows, cols, i, j, grid, &visited, islandNum);
      }
    }
  }
  return (count - 1);
}

/****************************Testing*******************************************/

#define EXPECT_EQ(expected, actual)                                       \
  if ((expected) != (actual)) {                                           \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: " << std::endl; \
  }

/* empty grid*/
void emptyGridTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{}};

  EXPECT_EQ(countIslands(0, 0, grid), 0);
}

/* wrong demenisions*/
void wrongDemenisionsTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{true, false, false, true},
                               {false, false, false, false},
                               {true, false, false, false},
                               {true, true, false, true}};

  EXPECT_EQ(countIslands(3, 4, grid), 0);
}

/*island only on the bounds*/
void islandsOnlyOnBoundsTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{true, false, false, true},
                               {false, false, false, false},
                               {true, false, false, false},
                               {true, true, false, true}};

  EXPECT_EQ(countIslands(4, 4, grid), 4);
}

/*only diagonally islands*/
void onlyDiagonallyIslandsTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{true, false}, {false, true}};

  EXPECT_EQ(countIslands(2, 2, grid), 2);
}

/*one island on the whole grid*/
void wholeGridOneIslandTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{true, true, true, true},
                               {true, true, true, true},
                               {true, true, true, true},
                               {true, true, true, true}};

  EXPECT_EQ(countIslands(4, 4, grid), 1);
}

/*general input*/
void generalInputTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{false, true, false, true},
                               {true, true, false, false},
                               {false, false, true, false},
                               {false, false, true, false}};

  EXPECT_EQ(countIslands(4, 4, grid), 3);
}

int main() {
  emptyGridTest();
  wrongDemenisionsTest();
  islandsOnlyOnBoundsTest();
  onlyDiagonallyIslandsTest();
  wholeGridOneIslandTest();
  generalInputTest();

  return 0;
}