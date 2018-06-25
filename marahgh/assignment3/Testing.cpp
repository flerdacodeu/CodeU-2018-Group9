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

void testEmptyDictionary() {
  /*Test setUp*/
  Dictionary dictionary = Dictionary();
  vector<char> g = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  Grid grid = Grid(g, 4, 2);
  vector<string> expected = vector<string>();

  EXPECT_EQ(findWords(grid, dictionary), expected);
}

/*Empty Grid*/

void testEmptyGrid() {
  /*Test setUp*/
  vector<string> words = {"hello", "words"};
  Dictionary dictionary = DictionaryCreate(words);
  Grid grid = Grid(0, 0);
  vector<string> expected = vector<string>();

  EXPECT_EQ(findWords(grid, dictionary), expected);
}

/*****************************Valid Inputs*************************************/
/*No Valid Words*/

void testNoValidWords() {
  /*Test setUp*/
  vector<string> words = {"hello", "words"};
  Dictionary dictionary = DictionaryCreate(words);
  Grid grid = Grid({'a', 'b', 'c'}, 1, 3);
  vector<string> expected = vector<string>();

  EXPECT_EQ(findWords(grid, dictionary), expected);
}

/*Valid Words Only By Visiting The Same Cell More Than Once*/

void testVisitSameCell() {
  /*Test setUp*/
  vector<string> words = {"banana", "marah", "nana"};
  Dictionary dictionary = DictionaryCreate(words);
  Grid grid = Grid({'b', 'x', 'n', 'y', 'a', 'z', 'b', 'x', 'y'}, 3, 3);
  vector<string> expected = vector<string>();

  EXPECT_EQ(findWords(grid, dictionary), expected);
}

/*Valid Words Appear More Than Once,
(checking if the result is without duplicates)*/
void testSameWordAppear() {
  /*Test setUp*/
  vector<string> words = {"banana", "marah", "nana", "cat"};
  Dictionary dictionary = DictionaryCreate(words);
  Grid grid = Grid({'c', 'a', 't', 'c', 'c', 'c', 'a', 't'}, 2, 4);
  vector<string> expected = vector<string>(1, "cat");

  EXPECT_EQ(findWords(grid, dictionary), expected);
}

/*Genaral Valid Inputs*/
void testGeneral() {
  /*Test setUp*/
  vector<string> words = {"car", "card", "cart", "cat"};
  Dictionary dictionary = DictionaryCreate(words);
  Grid grid = Grid({'a', 'a', 'r', 't', 'c', 'd'}, 2, 3);
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
