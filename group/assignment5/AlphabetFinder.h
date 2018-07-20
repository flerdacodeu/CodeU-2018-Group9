#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class AlphabetFinder {
  // PrecedenceGraph:a graph of precedence rules of the letter of a given
  // dictionart.
  class PrecedenceGraph {
    // the actual graph, map value: set of chars that are lexicographically
    // AFTER the key char
    unordered_map<char, unordered_set<char>> charsMap;

    // this set can be thought of as the set of IDs of the graph nodes
    unordered_set<char> allChars;
    // for the topological sorting
    stack<char> alphabetStack;
    map<char, bool> visited;

    bool doneSorting = false;
    friend class AlphabetFinder;

    // A helping function of the topologicalSort.
    void visit(char c);

   public:
    PrecedenceGraph(vector<string> words);

    // makes a topological Sort on the graph.
    // returns a stack of the sorted graph elements.
    stack<char> topologicalSort();
  };

  PrecedenceGraph rules;
  vector<char> alphabet;

 public:
  AlphabetFinder(vector<string> dictionary);

  // returns the alphabet of a given dictionary
  vector<char> getAlphabet();
};