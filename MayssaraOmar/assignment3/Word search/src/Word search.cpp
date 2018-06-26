#include <map>
#include "word search.h"
using namespace std;

// internal function
// cache maps a pair of a (cell position (row, col)) and a string (prefix) to a boolean to ensure that (get_words_from_grid) method doesn't run for the same inputs more than once using memoization technique
static void get_words_from_grid(const vector<vector<char> > &grid, int row, int col,
		string prefix, map<pair<int, int>, bool>* visited,
		map<pair<pair<int, int>, string>, bool>* cache, const dictionary &dic,
		unordered_set<string>* words) {

	// boundary check
	if (row < 0 || row >= grid.size() || col < 0 || col >= grid[row].size()) {
		return;
	}
	// result has been already computed for these inputs
	if((*cache)[make_pair(make_pair(row, col), prefix)]){
		return;
	}
	// word exits in dictionary
	if (dic.isWord(prefix + grid[row][col])) {
			words->insert(prefix + grid[row][col]);
	}
	// prefix doesn't exist in dictionary
	if (!dic.isPrefix(prefix + grid[row][col])) {
		return;
	}
	// recurse on all non-visited 8 directions
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (!(*visited)[make_pair(row + i, col + j)]) {
				(*visited)[make_pair(row + i, col + j)] = true;
				get_words_from_grid(grid, row + i, col + j,
						prefix + grid[row][col], visited, cache, dic, words);
				// (row-1 col-1 left up) (row-1 col up) (row-1 col+1 up right)
				// (row col-1 left) (row col current) (row col+1 right)
				// (row+1 col-1 left down) (row+1 col down) (row+1 col+1 down right)
				(*visited)[make_pair(row + i, col + j)] = false;
			}
		}
	}
	(*cache)[make_pair(make_pair(row, col), prefix)] = true;
}

void get_words_from_grid(const vector<vector<char> > &grid, const dictionary &dic,
		unordered_set<string>* words) {
	map<pair<int, int>, bool> visited;
	map<pair<pair<int, int>, string>, bool> cache;
	for (int r = 0; r < grid.size(); r++) {
		for (int c = 0; c < grid[r].size(); c++) {
			get_words_from_grid(grid, r, c, "", &visited, &cache, dic, words);
		}
	}
	return;
}
