#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/*Dictionary class.
Dictionary words are lowercase alphabet words*/
class Dictionary {
  vector<string> dictionary;

  /****************************************************************************/

  /*Removes hyphens("-") and converts letters to lower case(returns a legal
  dictionary word)
  if the word contains alphabet letters and hyphens, other wise returns an empty
  word */
  string fixWord(string word);
  /****************************************************************************/
 public:
  /*creates an empty dictionary*/
  Dictionary();

  /*Returns whether the given string is a valid word*/
  bool isWord(const string& word);

  /*Adds a new non- empty word to the dictionary*/
  bool addWord(const string& word);
  /*Returns whether the given string is a prefix of at least one word in the
dictionary*/
  bool isPrefix(const string& word);
};
