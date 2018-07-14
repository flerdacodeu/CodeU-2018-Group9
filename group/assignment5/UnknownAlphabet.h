#include <iostream>
#include <vector>
#include <string>
#include "Graph.h"

using namespace std;

/*UnknownAlphabet:
class members: a graph to be built in the constructor according to a given
dictionary:
letters of the dictionary are vertices in the graph,
an edge (u,v) is added to the graph if u is lexicographicaly smaller than v*/
class UnknownAlphabet {
  Graph dictGraph;
  /*all the letters used in the dictionary*/
  vector<char> letters;
  /*helping method the compares two strings and returns a pair of chars,
  the pair is the first different char between the two strings if foud,
  otherwise returns a piar of empty chars to indicate that there are no
  differnces.*/
  pair<char, char> findFirstDifference(string s1, string s2);
  /*extracts all the letters used in the dictionary to the letters vector.*/
  void getLetters(string s);
  /*checks if the given char is a member of the given vector,
  and returns a boolean value accordingly*/
  bool charExists(vector<char> v, char c);

 public:
  UnknownAlphabet(vector<string> dictionary);

  /*returns a vector of the dictionary alphabet*/
  vector<char> findAlphabet();
};
