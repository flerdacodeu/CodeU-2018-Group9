#include <iostream>
#include <vector>
#include "UnknownAlphabet.h"
using namespace std;

/****************************Testing*******************************************/

#define EXPECT_EQ(expected, actual)                                       \
  if ((expected) != (actual)) {                                           \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: " << std::endl; \
  }

void GenaralDictionaryTest1() {
  UnknownAlphabet a({"ART", "RAT", "CAT", "CAR"});
  vector<char> expected = {'A', 'T', 'R', 'C'};
  EXPECT_EQ(expected, a.findAlphabet());
}

void GenaralDictionaryTest2() {
  UnknownAlphabet a({"abc", "$$"});
  vector<char> expected = {'a', '$', 'b', 'c'};
  EXPECT_EQ(expected, a.findAlphabet());
}

void oneWordDictionaryTest() {
  UnknownAlphabet a({"xyzr"});
  vector<char> expected = {'x', 'y', 'z', 'r'};
  EXPECT_EQ(expected, a.findAlphabet());
}

void emptyDictionaryTest() {
  UnknownAlphabet a({""});
  vector<char> expected = {};
  EXPECT_EQ(expected, a.findAlphabet());
}

void GenaralDictionaryTest3() {
  UnknownAlphabet a({"xa", "xaby", "xac", "c", "a"});
  vector<char> expected = {'b', 'x', 'c', 'a', 'y'};
  EXPECT_EQ(expected, a.findAlphabet());
}

void oneLetterDictionary() {
  UnknownAlphabet a({"aaaa", "a", "aa"});
  vector<char> expected = {'a'};
  EXPECT_EQ(expected, a.findAlphabet());
}

int main() {
  GenaralDictionaryTest1();
  GenaralDictionaryTest2();
  oneWordDictionaryTest();
  emptyDictionaryTest();
  oneLetterDictionary();
  GenaralDictionaryTest3();
  return 0;
}
