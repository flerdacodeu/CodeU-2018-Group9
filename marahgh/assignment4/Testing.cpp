#include <iostream>
#include <vector>
#include "IslandCounter.h"
using namespace std;

/****************************Testing*******************************************/

#define EXPECT_EQ(expected, actual)                                       \
  if ((expected) != (actual)) {                                           \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: " << std::endl; \
  }

/* empty grid*/
void emptyGridTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{}};
  IslandCounter islandConter(grid);
  EXPECT_EQ(islandConter.countIslands(), 0);
}

/*island only on the bounds*/
void islandsOnlyOnBoundsTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{true, false, false, true},
                               {false, false, false, false},
                               {true, false, false, false},
                               {true, true, false, true}};
  IslandCounter islandConter(grid);
  EXPECT_EQ(islandConter.countIslands(), 4);
}

/*only diagonally islands*/
void onlyDiagonallyIslandsTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{true, false}, {false, true}};
  IslandCounter islandConter(grid);
  EXPECT_EQ(islandConter.countIslands(), 2);
}

/*one island on the whole grid*/
void wholeGridOneIslandTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{true, true, true, true},
                               {true, true, true, true},
                               {true, true, true, true},
                               {true, true, true, true}};
  IslandCounter islandConter(grid);
  EXPECT_EQ(islandConter.countIslands(), 1);
}

/* general input*/
void generalInputTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{false, true, false, true},
                               {true, true, false, false},
                               {false, false, true, false},
                               {false, false, true, false}};
  IslandCounter islandConter(grid);
  EXPECT_EQ(islandConter.countIslands(), 3);
}

/*big island*/
void BigIsland1Test() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{
                                   true, false, true,
                               },
                               {true, true, true}};
  IslandCounter islandConter(grid);
  EXPECT_EQ(islandConter.countIslands(), 1);
}

/*big island*/
void BigIsland2Test() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {{true, false, true, true, true},
                               {true, true, true, false, true}};
  IslandCounter islandConter(grid);
  EXPECT_EQ(islandConter.countIslands(), 1);
}

/*big different rows length*/
void DifferentRowsLengthTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {
      {true, false, true, true, true}, {true, true, true}, {false, true}};
  IslandCounter islandConter(grid);
  EXPECT_EQ(islandConter.countIslands(), 1);
}

/*check the same grid twice to make sure it was not overriden*/
void GridNotOverridenTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {
      {true, false, true, true, true}, {true, true, true}, {false, true}};
  IslandCounter islandConter1(grid);
  EXPECT_EQ(islandConter1.countIslands(), 1);

  IslandCounter islandConter2(grid);
  EXPECT_EQ(islandConter2.countIslands(), 1);
}

/*No islands exist*/
void NoIslandsExistsTest() {
  /*Test Set-Up*/
  vector<vector<bool>> grid = {
      {false, false, false}, {false, false, false}, {false, false, false}};
  IslandCounter islandConter(grid);
  EXPECT_EQ(islandConter.countIslands(), 0);
}

int main() {
  emptyGridTest();
  islandsOnlyOnBoundsTest();
  onlyDiagonallyIslandsTest();
  wholeGridOneIslandTest();
  generalInputTest();
  BigIsland1Test();
  BigIsland2Test();
  DifferentRowsLengthTest();
  GridNotOverridenTest();
  NoIslandsExistsTest();

  return 0;
}