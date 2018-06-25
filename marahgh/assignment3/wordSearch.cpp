#include <iostream>
#include <vector>
#include <algorithm>
#include "Grid.h"
#include "Dictionary.h"
using namespace std;

/*An auxiliary function of find word, receives a grid,
cell cordinates to start searchnig a word from, a dictionary.
returns the legal words starts form cell i,j int the words vector*/
void findWord(Grid& grid, Grid& visited, int i, int j, Dictionary dictionary,
              string word, vector<string>& words) {
  if (i < 0 || j < 0 || i >= grid.getRows() || j >= grid.getCols() ||
      visited[i][j] == '1' || grid.isEmpty()) {
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

  visited[i][j] = '1';
  findWord(grid, visited, i, j - 1, dictionary, word, words);
  findWord(grid, visited, i, j + 1, dictionary, word, words);
  findWord(grid, visited, i - 1, j - 1, dictionary, word, words);
  findWord(grid, visited, i - 1, j, dictionary, word, words);
  findWord(grid, visited, i - 1, j + 1, dictionary, word, words);
  findWord(grid, visited, i + 1, j - 1, dictionary, word, words);
  findWord(grid, visited, i + 1, j, dictionary, word, words);
  findWord(grid, visited, i + 1, j + 1, dictionary, word, words);
  visited[i][j] = '0';
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

      Grid visited = Grid(vector<char>(grid.getRows() * grid.getCols(), '0'),
                          grid.getRows(), grid.getCols());
      findWord(grid, visited, i, j, dictionary, word, words);
    }
  }
  return words;
}
