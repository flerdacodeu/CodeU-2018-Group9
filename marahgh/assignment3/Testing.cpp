#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define EXPECT_EQ(expected, actual)                                       \
  if ((expected) != (actual)) {                                           \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: " << std::endl; \
  }

/********************************Testing***************************************/
/*Testing helping functions*/

Grid gridCreate(vector<char> letters, int m, int n) {
  Grid grid = Grid(letters, m, n);
  return grid;
}

Dictionary DictionaryCreate(vector<string> words) {
  Dictionary dictionary = Dictionary();
  for (string word : words) {
    dictionary.addWord(word);
  }
  return dictionary;
}

/***************************Ivnalid Inputs*************************************/
/*Empty Dictionary*/

Grid testEmptyDictionaryCreateGrid() {
  vector<char> g = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  Grid grid = Grid(g, 4, 2);
  return grid;
}

void testEmptyDictionary() {
  Dictionary dictionary = Dictionary();
  Grid grid = testEmptyDictionaryCreateGrid();
  vector<string> expected = vector<string>();
  EXPECT_EQ(findWords(grid, dictionary), expected);
}

/*Empty Grid*/

Dictionary testEmptyGridDictionaryCreate() {
  vector<string> words = {"hello", "words"};
  Dictionary dictionary = DictionaryCreate(words);
  return dictionary;
}
void testEmptyGrid() {
  Dictionary dictionary = testEmptyGridDictionaryCreate();
  Grid grid = Grid(0, 0);
  vector<string> expected = vector<string>();
  EXPECT_EQ(findWords(grid, dictionary), expected);
}

/*****************************Valid Inputs*************************************/
/*No Valid Words*/

void testNoValidWordsSetUp(Dictionary& dictionary, Grid& grid) {
  vector<string> words = {"hello", "words"};
  dictionary = DictionaryCreate(words);
  vector<char> letters = {'a', 'b', 'c'};
  grid.fillGrid(letters);
}

void testNoValidWords() {
  Dictionary dictionary = Dictionary();
  Grid grid = Grid(1, 3);
  testNoValidWordsSetUp(dictionary, grid);
  vector<string> expected = vector<string>();
  EXPECT_EQ(findWords(grid, dictionary), expected);
}

/*Valid Words Only By Visiting The Same Cell More Than Once*/

void testVisitSameCellSetUp(Dictionary& dictionary, Grid& grid) {
  vector<string> words = {"banana", "marah", "nana"};
  dictionary = DictionaryCreate(words);
  vector<char> letters = {'b', 'x', 'n', 'y', 'a', 'z', 'b', 'x', 'y'};
  grid.fillGrid(letters);
}

void testVisitSameCell() {
  Dictionary dictionary = Dictionary();
  Grid grid = Grid(3, 3);
  testVisitSameCellSetUp(dictionary, grid);
  vector<string> expected = vector<string>();
  EXPECT_EQ(findWords(grid, dictionary), expected);
}
/*Valid Words Appear More Than Once,
(checking if the result is without duplicates)*/
void testSameWordAppearSetUp(Dictionary& dictionary, Grid& grid) {
  vector<string> words = {"banana", "marah", "nana", "cat"};
  dictionary = DictionaryCreate(words);
  vector<char> letters = {'c', 'a', 't', 'c', 'c', 'c', 'a', 't'};
  grid.fillGrid(letters);
}
void testSameWordAppear() {
  Dictionary dictionary = Dictionary();
  Grid grid = Grid(2, 4);
  testSameWordAppearSetUp(dictionary, grid);
  vector<string> expected = vector<string>(1, "cat");
  EXPECT_EQ(findWords(grid, dictionary), expected);
}
/*Genaral Valid Inputs*/

void testGeneralSetUp(Dictionary& dictionary, Grid& grid) {
  vector<string> words = {"car", "card", "cart", "cat"};
  dictionary = DictionaryCreate(words);
  vector<char> letters = {'a', 'a', 'r', 't', 'c', 'd'};
  grid.fillGrid(letters);
}

void testGeneral() {
  Dictionary dictionary = Dictionary();
  Grid grid = Grid(2, 3);
  testGeneralSetUp(dictionary, grid);
  vector<string> expected = {"car", "card", "cat"};
  vector<string> result = findWords(grid, dictionary);
  std::sort(result.begin(), result.end());
  std::sort(expected.begin(), expected.end());
  EXPECT_EQ(result, expected);
}

/******************************************************************************/

int main() {
  testEmptyDictionary();
  testEmptyGrid();
  testNoValidWords();
  testVisitSameCell();
  testSameWordAppear();
  testGeneral();

  return 0;
}
