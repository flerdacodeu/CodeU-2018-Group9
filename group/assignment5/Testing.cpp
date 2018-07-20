#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "TestingMacros.h"

void givenTest() {
  AlphabetFinder AF({"ART", "RAT", "CAT", "CAR"});
  vector<char> expected = {'T', 'A', 'R', 'C'};
  vector<char> actual = AF.getAlphabet();
  for (char c : actual) cout << c << "-";
  EXPECT_EQ(expected, actual);
}

void oneLetterTest() {
  AlphabetFinder AF({"!", "!!!", "!!!!"});
  vector<char> expected = {'!'};
  vector<char> actual = AF.getAlphabet();
  EXPECT_EQ(expected, actual);
}

void simpleTest() {
  AlphabetFinder AF({"fg", "ab", "ca", "bc", "gf"});
  vector<char> expected = {'f', 'a', 'c', 'b', 'g'};
  vector<char> actual = AF.getAlphabet();
  EXPECT_EQ(expected, actual);
}

void minCapTest() {
  AlphabetFinder AF({"Ar", "rA", "cA", "car"});
  vector<char> expected = {'A', 'r', 'c', 'a'};
  vector<char> actual = AF.getAlphabet();
  EXPECT_EQ(expected, actual);
}

void symbolsTest() {
  AlphabetFinder AF({"*&^", "*&%", "%%%", "&**", "&*@"});
  vector<char> expected = {'^', '*', '@', '%', '&'};
  vector<char> actual = AF.getAlphabet();
  EXPECT_EQ(expected, actual);
}

void runAllTests() {
  givenTest();
  oneLetterTest();
  simpleTest();
  minCapTest();
  symbolsTest();
}

int main() {
  runAllTests();

  return 0;
}