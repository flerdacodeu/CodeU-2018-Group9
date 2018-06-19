#include <map>
#include "word search.h"
using namespace std;

void get_words_from_grid(vector<vector<char> > &grid, int row, int col,
		string word, map<pair<int, int>, bool> &vis,
		map<pair<pair<int, int>, string>, bool> &memo, dictionary &dic,
		unordered_set<string> &words) {
	if (row < 0 || row >= grid.size() || col < 0 || col >= grid[row].size()) {
		return;
	}
	if (!dic.isPrefix(word + grid[row][col])
			|| memo[make_pair(make_pair(row, col), word)]) {
		return;
	}

	if (dic.isWord(word + grid[row][col])) {
		words.insert(word + grid[row][col]);
	}
	// recurse on all non-visited 8 directions
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (!vis[make_pair(row + i, col + j)]) {
				vis[make_pair(row + i, col + j)] = true;
				get_words_from_grid(grid, row + i, col + j,
						word + grid[row][col], vis, memo, dic, words);
				// (row-1 col-1 left up) (row-1 col up) (row-1 col+1 up right)
				// (row col-1 left) (row col current) (row col+1 right)
				// (row+1 col-1 left down) (row+1 col down) (row+1 col+1 down right)
				vis[make_pair(row + i, col + j)] = false;
			}
		}
	}
	memo[make_pair(make_pair(row, col), word)] = true;

}
void get_words_from_grid(vector<vector<char> > &grid, dictionary &dic,
		unordered_set<string> &words) {
	map<pair<int, int>, bool> vis;
	map<pair<pair<int, int>, string>, bool> memo;
	for (int r = 0; r < grid.size(); r++) {
		for (int c = 0; c < grid[r].size(); c++) {
			get_words_from_grid(grid, r, c, "", vis, memo, dic, words);
		}
	}
	return;
}

