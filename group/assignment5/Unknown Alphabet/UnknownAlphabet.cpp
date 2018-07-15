#include "UnknownAlphabet.h"
#include <iostream>
using namespace std;

UnknownAlphabet::UnknownAlphabet(const vector<string> &dictionary) {
  this->dictionary = &dictionary;
}

pair<char, char> UnknownAlphabet::mismatch(string s1, string s2) {
    int it1 = 0, it2 = 0;
    while(it1<s1.length() && it2<s2.length() && s1[it1] == s2[it2]) {
      it1++;
      it2++;
    }
    if(it1 == s1.length() || it2 == s2.length()) { // no mismatch chars are found
      return make_pair('\0','\0');
    }
    return make_pair(s1[it1], s2[it2]);
  }

void UnknownAlphabet::build_graph(unordered_map<char, unordered_set<char>>* graph, unordered_map<char, int>* indegree) { 
  for(int i = 0; i < (signed) (*dictionary).size()-1; i++) {
    pair<char, char> mismatch_chars = mismatch((*dictionary)[i], (*dictionary)[i+1]);
    if(mismatch_chars.first != '\0') { // there is a mismatch
      (*graph)[mismatch_chars.first].insert(mismatch_chars.second);
      (*indegree)[mismatch_chars.second]++; // increase indegree of the mismach char in second word by one
    }
  }
}

unordered_set<char> UnknownAlphabet::get_unordered_alphabet(){
  unordered_set<char> unordered_alphabet;
    for(const string word : (*dictionary)) {
      for(const char letter : word) {
        unordered_alphabet.insert(letter);
      }
    }
  return unordered_alphabet;
}
  
// Unordered_map isn't passed as a const parameter here because the operator[] method is non-const as it might add a default value when the item looked up is not found  
// the default value is zero which doens't contradict the purpose of this method
queue<char> UnknownAlphabet::get_zero_indegree_chars(const unordered_set<char> &unordered_alphabet, unordered_map<char, int> &indegree) {
  queue<char> zero_indegree_chars;
  for(const char letter: unordered_alphabet){
    if(!indegree[letter]){
      zero_indegree_chars.push(letter);
    }
  }
  return zero_indegree_chars;
}

vector<char> UnknownAlphabet::get_ordered_alphabet() {
  // build a letters directed graph from dictionary
  unordered_map<char, unordered_set<char>> graph;
  unordered_map<char, int> indegree;
  build_graph(&graph, &indegree);
  // get zero indegree chars i.e. letters that can be placed at the begining of the alphabet 
  unordered_set<char> unordered_alphabet = get_unordered_alphabet();
  queue<char> zero_indegree_chars = get_zero_indegree_chars(unordered_alphabet, indegree);
  // topological sort 
  vector<char> ordered_alphabet;
  while(!zero_indegree_chars.empty()){
    char current_letter = zero_indegree_chars.front();
    // decrease all adjacent letters indegrees by one
    for(char letter : graph[current_letter]){
      indegree[letter]--;
      if(!indegree[letter]){ // if letter's indegree is zero, push to zero_indegree_chars queue 
        zero_indegree_chars.push(letter);
      }
    }
    ordered_alphabet.push_back(current_letter);
    zero_indegree_chars.pop();
  }
  if(ordered_alphabet.size() != unordered_alphabet.size()){ //dictionary is inconsistent
    return {};
  }
  return ordered_alphabet;
}