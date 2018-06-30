#include "Dictionary.h"
using namespace std;

/**********************Dictionary class Methods Implemetatons*****************/

/*Removes hyphens("-") and converts letters to lower case(returns a legal
dictionary word)
if the word contains alphabet letters and hyphens, other wise returns an empty
word */
string Dictionary::fixWord(string word) {
  /*a loop to remove hyphens*/
  for (int i = 0; i < word.size(); i++) {
    if (word[i] != '-') {
      word[i] = tolower(word[i]);

      /*checks if the fixed word is dictionary legal word:
      (contains only lowercase alphabet letters)*/
      if (word[i] < 'a' || word[i] > 'z') {
        return "";
      }
    }
  }
  return word;
}

/*creates an empty dictionary*/
Dictionary::Dictionary() { dictionary = vector<string>(); }

/*Returns whether the given string is a valid word*/
bool Dictionary::isWord(const string& word) {
  return isFoundInVector(dictionary, fixWord(word));
}

/*Adds a new non- empty word to the dictionary*/
bool Dictionary::addWord(const string& word) {
  string fixed = fixWord(word);
  if (isWord(fixed) || fixed.empty()) {
    return false;
  }
  dictionary.push_back(fixed);
  return true;
}

/*Returns whether the given string is a prefix of at least one word in the
dictionary*/
bool Dictionary::isPrefix(const string& word) {
  for (string w : dictionary) {
    if (w.compare(0, word.size(), word) == 0) {
      return true;
    }
  }
  return false;
}
