#ifndef WORD_SEARCH_H_
#define WORD_SEARCH_H_

#include <unordered_set>
#include "dictionary.h"

// takes a chars grid, a dictionary and an unordered_set to store the output
// the method finds all the words from the dictionary that can be formed in the grid and insert them in the unordered_set
void get_words_from_grid(const vector<vector<char> > &grid, const dictionary &dic, unordered_set<string>* words);

#endif /* WORD_SEARCH_H_ */
