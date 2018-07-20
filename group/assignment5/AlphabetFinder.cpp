
#include "AlphabetFinder.h"

// A helping function of the topologicalSort.
void AlphabetFinder::PrecedenceGraph::visit(char c) {
  visited[c] = true;

  // iterating over all chars that should come AFTER char c,
  // when a char is visited,
  // all the chars that should come after it are added to the stack before
  // it,
  // so if we have a<b & b<c,
  // when a is visited, it's not added to the stack, instead, it calls
  // visit(b)
  // when b is visited, it's not added to the stack, instead, it calls
  // visit(c)
  // when c is visited, nothing comes after it, so it's added to the stack,
  // then we go back to b, that called visit(c), and b is added to the
  // stack,
  // then we go back to a, that called visit(b), and a is added to the
  // stack,
  // when we empty the stack, they come out in this order: a b c, which is
  // the correct order
  unordered_set<char>::iterator it;
  for (it = charsMap[c].begin(); it != charsMap[c].end(); it++) {
    if (!visited[*it]) {
      visit(*it);
    }
  }

  alphabetStack.push(c);
}

AlphabetFinder::PrecedenceGraph::PrecedenceGraph(vector<string> words) {
  // getting all graph nodes (all unique chars)
  for (string word : words) {
    for (char c : word) {
      allChars.emplace(c);
    }
  }

  // building the graph,
  // for every pair of adjacent words,
  // go through them simultaneously char by char till reaching the end of
  // any of the 2 words,
  // find only the first mismatching chars (if there are any),
  // map[mismatching letter from the first word] = mismatching letter from
  // the second word,
  // because the letter from the second word should come AFTER the one from
  // the first word
  int firstLoopIterations = words.size() - 1;  // if we have 1 2 3 words,
                                               // the pairs are: 1 2, 2 3,
                                               // so 3 words -> 2 pairs
  for (int i = 0; i < firstLoopIterations; i++) {
    string word1 = words[i];
    string word2 = words[i + 1];
    int secondLoopIterations =
        min(word1.length(), word2.length());  // we'll stop if the end of any of
                                              // the 2 words is reached
    for (int j = 0; j < secondLoopIterations; j++) {
      if (word1[j] != word2[j]) {
        charsMap[word1[j]].emplace(word2[j]);
        break;  // we shouldn't check the rest of the 2 words, so we should
                // move on to another pair
      }
    }
  }
}

// makes a topological Sort on the graph.
// returns a stack of the sorted graph elements.
stack<char> AlphabetFinder::PrecedenceGraph::topologicalSort() {
  if (doneSorting) {
    return alphabetStack;
  }
  // filling the visited map
  unordered_set<char>::iterator it;
  for (it = allChars.begin(); it != allChars.end(); it++) {
    visited[*it] = false;
  }

  // iterating over all chars to visit them
  for (it = allChars.begin(); it != allChars.end(); it++) {
    if (!visited[*it]) {
      visit(*it);
    }
  }

  // when the topoligical sorting is done, that's when the alphabet's ready
  doneSorting = true;
  return alphabetStack;
}

AlphabetFinder::AlphabetFinder(vector<string> dictionary)
    : rules(PrecedenceGraph(dictionary)) {}

vector<char> AlphabetFinder::getAlphabet() {
  stack<char> alphabetStack = rules.topologicalSort();

  // filling the alphabet vector
  while (!alphabetStack.empty()) {
    alphabet.push_back(alphabetStack.top());
    alphabetStack.pop();
  }

  return alphabet;
}

