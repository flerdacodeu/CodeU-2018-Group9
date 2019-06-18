#include "UnknownAlphabet.h"
#include "test.h"
using namespace std;

void normal_test() {
  vector<string> dictionary {"ART", "RAT", "CAT", "CAR"};
  UnknownAlphabet unknownAlphabet(dictionary);
  vector<char> expected {'T', 'A', 'R', 'C'};
  EXPECT_EQ(expected, unknownAlphabet.get_ordered_alphabet());
}

void empty_dictionary_test() {
  vector<string> dictionary;
  UnknownAlphabet unknownAlphabet(dictionary);
  vector<char> expected;
  EXPECT_EQ(expected, unknownAlphabet.get_ordered_alphabet());
}

// Upper/lower case characters are treated differently i.e. not considered the same for simplicity
void upper_lower_case_chars_dictionary_test() {
  vector<string> dictionary {"A", "a", "b", "B"};
  UnknownAlphabet unknownAlphabet(dictionary);
  vector<char> expected {'A', 'a', 'b', 'B'};
  EXPECT_EQ(expected, unknownAlphabet.get_ordered_alphabet());
}

void non_english_chars_dictionary_test() {
  vector<string> dictionary {"!@", "!#", "$%^"};
  UnknownAlphabet unknownAlphabet(dictionary);
  vector<char> expected {'^', '%', '!', '@', '$', '#'};
  EXPECT_EQ(expected, unknownAlphabet.get_ordered_alphabet());
}

void inconsistent_dictionary_test() {
  vector<string> dictionary {"A", "M", "A"};
  UnknownAlphabet unknownAlphabet(dictionary);
  vector<char> expected;
  EXPECT_EQ(expected, unknownAlphabet.get_ordered_alphabet());
}

void one_word_dictionary_test() {
  vector<string> dictionary {"cat"};
  UnknownAlphabet unknownAlphabet(dictionary);
  vector<char> expected {'t', 'c', 'a'};
  EXPECT_EQ(expected, unknownAlphabet.get_ordered_alphabet());
}

void duplicate_words_dictionary_test() {
  vector<string> dictionary {"cat", "cat", "cat"};
  UnknownAlphabet unknownAlphabet(dictionary);
  vector<char> expected {'t', 'c', 'a'};
  EXPECT_EQ(expected, unknownAlphabet.get_ordered_alphabet());
}

int main() {
  normal_test();
  empty_dictionary_test();
  upper_lower_case_chars_dictionary_test();
  non_english_chars_dictionary_test();
  inconsistent_dictionary_test();
  one_word_dictionary_test();
  duplicate_words_dictionary_test();
  return 0;
}