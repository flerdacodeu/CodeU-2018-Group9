

#ifndef WORD_SEARCH_H_
#define WORD_SEARCH_H_

#include <unordered_set>
#include "dictionary.h"

void get_words_from_grid(vector<vector<char> > &grid, dictionary &dic,unordered_set<string> &ans);

#endif /* WORD_SEARCH_H_ */
