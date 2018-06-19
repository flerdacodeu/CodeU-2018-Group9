#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*A helper function:returns true if the given word
was found in the given vector, and false otherwise*/
bool isFoundInVector(vector<string> words, string word) {
  if (std::find(words.begin(), words.end(), word) != words.end()) {
    return true;
  }
  return false;
}

/*The grid class,
contains lower-case letters from whichever alphabet the dictionary uses.*/
class Grid {
  char** matrix;
  int rows;
  int cols;
  bool empty;

 public:
  /*creates an empty grid,
  a grid with the given dimensions filled by ' ' charachters*/
  Grid(int rows, int cols)
      : matrix(nullptr), rows(rows), cols(cols), empty(true) {
    matrix = new char*[rows];
    for (int i = 0; i < rows; i++) {
      matrix[i] = new char[cols];
    }
    vector<char> chars = vector<char>((rows * cols), ' ');
    empty = true;
    fillGrid(chars);
  }

  /*receives a vector of the charachters to to fill the grid with,
  grid's rows number and grid's columns number.
  creates the grid if the dimensions are OK , otherwise creats an empty grid*/
  Grid(vector<char> chars, int rows, int cols)
      : matrix(nullptr), rows(rows), cols(cols), empty(false) {
    if (rows >= 0 && cols >= 0 && chars.size() == rows * cols) {
      matrix = new char*[rows];
      for (int i = 0; i < rows; i++) {
        matrix[i] = new char[cols];
      }
      fillGrid(chars);
    }
  }
  /*Fills the grid with the given values*/
  bool fillGrid(vector<char> chars) {
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
  /*Grid's destructor*/
  ~Grid() {
    if (matrix == nullptr) {
      return;
    }
    for (int i = 0; i < rows; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  /*returns the grid's rows number*/
  int getRows() { return rows; }

  /*returns the grid's columns number*/
  int getCols() { return cols; }

  /*return true if the grid is empty, and false otherwise*/
  bool isEmpty() { return empty; }
  /*returns the i'th row in the grid if the grid is not empty,and nullptr
   * otherwise*/
  char* operator[](int i) {
    if (isEmpty()) {
      return nullptr;
    }
    return matrix[i];
  }
};

/*Dictionary class.
Dictionary words are lowercase alphabet words*/
class Dictionary {
  vector<string> dictionary;

  /****************************************************************************/
  /* a private auxiliary method of isPrefix,
  checks whether w2 is a prefix of w1*/
  bool isWordPrefix(string w1, string w2) {
    if (w1.size() < w2.size()) {
      return false;
    }
    for (int i = 0; i < w2.size(); i++) {
      if (w1[i] != w2[i]) {
        return false;
      }
    }
    return true;
  }

  /*Removes hyphens("-") and converts letters to lower case(returns a legal
  dictionary word)
  if the word contains alphabet letters and hyphens, other wise returns an empty
  word */
  string fixWord(string word) {
    string fixed = "";
    /*a loop to remove hyphens*/
    for (char c : word) {
      if (c != '-') {
        fixed.append(1, tolower(c));
      }
    }
    /*checks if the fixed word is dictionary legal word
    (contains only lowercase alphabet letters)*/
    for (char c : fixed) {
      if (c < 'a' || c > 'z') {
        return "";
      }
    }
    return fixed;
  }
  /****************************************************************************/
 public:
  /*creates an empty dictionary*/
  Dictionary() { dictionary = vector<string>(); }

  /*Returns whether the given string is a valid word*/
  bool isWord(string word) {
    return isFoundInVector(dictionary, fixWord(word));
  }

  /*Adds a new non- empty word to the dictionary*/
  bool addWord(string word) {
    string fixed = fixWord(word);
    if (isWord(fixed) || fixed.empty()) {
      return false;
    }
    dictionary.push_back(fixed);
    return true;
  }

  /*Returns whether the given string is a prefix of at least one word in the
dictionary*/
  bool isPrefix(string word) {
    for (string w : dictionary) {
      if (isWordPrefix(w, word)) {
        return true;
      }
    }
    return false;
  }
};

/*An auxiliary function of find word, receives a grid,
cell cordinates to start searchnig a word from, a dictionary.
returns the legal words starts form cell i,j int the words vector*/
void findWord(Grid& grid, int i, int j, Dictionary dictionary, string word,
              vector<string>& words) {
  if (i < 0 || j < 0 || i >= grid.getRows() || j >= grid.getCols() ||
      grid[i][j] == '*' || grid.isEmpty()) {
    return;
  }
  word.append(1, grid[i][j]);
  if (!(dictionary.isPrefix(word))) {
    word.pop_back();
    return;
  }
  if (dictionary.isWord(word)) {
    if (!isFoundInVector(words, word)) {
      words.push_back(word);
    }
  }
  char c = grid[i][j];
  grid[i][j] = '*';
  findWord(grid, i, j - 1, dictionary, word, words);
  findWord(grid, i, j + 1, dictionary, word, words);
  findWord(grid, i - 1, j - 1, dictionary, word, words);
  findWord(grid, i - 1, j, dictionary, word, words);
  findWord(grid, i - 1, j + 1, dictionary, word, words);
  findWord(grid, i + 1, j - 1, dictionary, word, words);
  findWord(grid, i + 1, j, dictionary, word, words);
  findWord(grid, i + 1, j + 1, dictionary, word, words);
  grid[i][j] = c;
}

/*Given a grid of letters and a dictionary,
the function finds all the words from the dictionary that can be
formed in the grid.*/
vector<string> findWords(Grid& grid, Dictionary dictionary) {
  vector<string> words = vector<string>();
  if (grid.isEmpty()) {
    return words;
  }
  for (int i = 0; i < grid.getRows(); i++) {
    for (int j = 0; j < grid.getCols(); j++) {
      string word = "";
      findWord(grid, i, j, dictionary, word, words);
    }
  }
  return words;
}