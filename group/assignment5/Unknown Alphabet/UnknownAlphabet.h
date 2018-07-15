#ifndef UNKNOWNALPHAET_H_
#define UNKNOWNALPHAET_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <utility>

class UnknownAlphabet{
  const std::vector<std::string>* dictionary;
public:
  explicit UnknownAlphabet(const std::vector<std::string> &dictionary); // constructor
  std::vector<char> get_ordered_alphabet(); // returns one of the possible ordered alphabet if the dictionary is consistent, elsewise it returns an empty vector 
private:
  std::pair<char, char> mismatch(std::string s1, std::string s2); // returns the first 2 mismtached chars in 2 strings in the form of pair where the its first member is the mismatched char in the first string and its second member is the mismatched char in the second string 
  void build_graph(std::unordered_map<char, std::unordered_set<char>>* graph, std::unordered_map<char, int>* indegree); // build a directed chars graph from dictionary to use in topological sort
  std::unordered_set<char> get_unordered_alphabet(); // returns a set of all chars in the alphabet unordered
  std::queue<char> get_zero_indegree_chars(const std::unordered_set<char> &unordered_alphabet, std::unordered_map<char, int> &indegree); // returns zero indegree chars
};

#endif /* UNKNOWNALPHAET_H_ */