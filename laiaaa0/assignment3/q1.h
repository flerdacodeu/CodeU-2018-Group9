#include "Dictionary.h"


#ifndef Q1_H
#define Q1_H
bool InRange (int value, int min_value, int max_value);

bool IsInGrid (int i, int j, const std::vector<std::vector<char> > &grid);

void FindAllWordsRecursive (int x, int y, const Dictionary & d,
                            std::vector<std::vector<char> > &grid,
                            std::vector<std::vector<bool> > &visited,
                            std::string current_word,
                            std::set<std::string> &found_words);

std::set<std::string> FindAllWords(const Dictionary &d, std::vector<std::vector<char> > &grid);

#endif
