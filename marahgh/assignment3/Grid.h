#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//*****************************************************************************

/*A helper function:returns true if the given wordwas found in the given vector,
and false otherwise*/
bool isFoundInVector(vector<string> words, string word);

/*The grid class,
contains lower-case letters from whichever alphabet the dictionary uses.*/
class Grid {
  char** matrix;
  int rows;
  int cols;
  /*a member that can be true if the Grid is empty,and false otherwise. */
  bool empty;
  /*Fills the grid with the given values*/
  bool fillGrid(vector<char> chars);
  
 public:
  /*creates an empty grid,
  a grid with the given dimensions filled by ' ' charachters*/
  Grid(int rows, int cols);
  /*receives a vector of the charachters to to fill the grid with,
  grid's rows number and grid's columns number.
  creates the grid if the dimensions are OK , otherwise creats an empty grid*/
  Grid(vector<char> chars, int rows, int cols);
  ~Grid();
  /*returns the grid's rows number*/
  int getRows();
  /*returns the grid's columns number*/
  int getCols();
  /*return true if the grid is empty, and false otherwise*/
  bool isEmpty();
  /*returns the i'th row in the grid if the grid is not empty,and nullptr
   * otherwise*/
  char* operator[](int i);
};
