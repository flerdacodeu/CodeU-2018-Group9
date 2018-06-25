#include "Grid.h"
using namespace std;

/*A helper function:returns true if the given wordwas found in the given vector,
and false otherwise*/
bool isFoundInVector(vector<string> words, string word) {
  return std::find(words.begin(), words.end(), word) != words.end();
}

/*************The Grid methods Implementations.***************/

/*Fills the grid with the given values*/
bool Grid::fillGrid(vector<char> chars) {
  empty = false;
  if (chars.size() != rows * cols) {
    return false;
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = chars[(i * cols) + j];
    }
  }
  return true;
}
/******************************************************************************/
/*creates an empty grid,
a grid with the given dimensions filled by ' ' charachters*/
Grid::Grid(int rows, int cols)
    : Grid(vector<char>(rows * cols, ' '), rows, cols) {}

/*receives a vector of the charachters to to fill the grid with,
grid's rows number and grid's columns number.
creates the grid if the dimensions are OK , otherwise creats an empty grid*/
Grid::Grid(vector<char> chars, int rows, int cols)
    : matrix(nullptr), rows(rows), cols(cols), empty(false) {
  if (rows >= 0 && cols >= 0 && chars.size() == rows * cols) {
    matrix = new char*[rows];
    for (int i = 0; i < rows; i++) {
      matrix[i] = new char[cols];
    }
    fillGrid(chars);
  }
}

Grid::~Grid() {
  if (matrix == nullptr) {
    return;
  }
  for (int i = 0; i < rows; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

/*returns the grid's rows number*/
int Grid::getRows() { return rows; }

/*returns the grid's columns number*/
int Grid::getCols() { return cols; }

/*return true if the grid is empty, and false otherwise*/
bool Grid::isEmpty() { return empty; }

/*returns the i'th row in the grid if the grid is not empty,and nullptr
 * otherwise*/
char* Grid::operator[](int i) {
  if (isEmpty()) {
    return nullptr;
  }
  return matrix[i];
}