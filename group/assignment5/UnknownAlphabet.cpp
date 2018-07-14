#include "UnknownAlphabet.h"

/*helping method the compares two strings and returns a pair of chars,
the pair is the first different char between the two strings if foud,
otherwise returns a piar of empty chars to indicate that there are no
differnces.*/
pair<char, char> UnknownAlphabet::findFirstDifference(string s1, string s2) {
  int size = min(s1.size(), s2.size());
  pair<char, char> p(' ', ' ');
  for (int i = 0; i < size; i++) {
    if (s1[i] != s2[i]) {
      p.first = s1[i];
      p.second = s2[i];
      return p;
    }
  }
  return p;
}

/*extracts all the letters used in the dictionary to the letters vector.*/
void UnknownAlphabet::getLetters(string s) {
  for (char c : s) {
    letters.push_back(c);
  }
}
/*checks if the given char is a member of the given vector,
and returns a boolean value accordingly*/
bool UnknownAlphabet::charExists(vector<char> v, char c) {
  for (char ch : v) {
    if (ch == c) {
      return true;
    }
  }
  return false;
}

UnknownAlphabet::UnknownAlphabet(vector<string> dictionary)
    : dictGraph(Graph()) {
  for (int i = 0; i < dictionary.size() - 1; i++) {
    pair<char, char> p = findFirstDifference(dictionary[i], dictionary[i + 1]);
    dictGraph.addEdge(p.first, p.second);
  }
  for (string word : dictionary) {
    getLetters(word);
  }
}

/*returns a vector of the dictionary alphabet*/
vector<char> UnknownAlphabet::findAlphabet() {
  vector<char> alphabet = dictGraph.topologicalSort();
  for (char c : letters) {
    if (!charExists(alphabet, c)) {
      alphabet.push_back(c);
    }
  }
  return alphabet;
}
