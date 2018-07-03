#include <iostream>
#include <stdio.h>  
#include <string>
#include <queue>
#include <set>
#include <stdlib.h>
#include"codeu_test_lib.h"
using namespace std;
int charIndex(char c) { //map each letter to its alphabetic order starting from 0 to 25
						//case insensitive
	c = tolower(c);
	return c - 'a';
}
bool onlyEnglishLetters(string s) {
	//dictionary class and the grid both contain only english upper and lower chars a-z && A-Z
	for (char &c : s)
		if (!(c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z'))
			return false;
	return true;
}
class Dictionary;
class DictionaryNode {
	friend class Dictionary;
private:
	DictionaryNode * next[26] = { nullptr };
	bool isLeaf = false;
};
class Dictionary {
	//Dictionary class implemented using Trie data structure 
	//this class is case-insensitive
public:
	Dictionary();
	Dictionary(const Dictionary &) = delete;
	Dictionary & operator =(const Dictionary &) = delete;
	~Dictionary();
	bool insert(string &word);
	bool isWord(string & word);
	bool isPrefix(string & word);
	void clear();
	//void prnt();
private:
	void clear(DictionaryNode *);
	DictionaryNode * find(string & word);
	DictionaryNode * root;
};
Dictionary::Dictionary() {
	root = new DictionaryNode;
}
Dictionary::~Dictionary() {
	clear(root);
	delete root;
}
void Dictionary::clear() {
	clear(root);
}
void Dictionary::clear(DictionaryNode * node) {
	if (node == nullptr)
		return;
	for (int i = 0; i < 26; i++)
		clear(node->next[i]);
	if (node != root)
		delete node;
}
bool Dictionary::insert(string & word) {
	if (!onlyEnglishLetters(word) || !word.size())//insert only non-empty words with english letters
		return false;
	DictionaryNode * at = root;
	for (char& c : word) {
		int index = charIndex(c);
		if (at->next[index] == nullptr)
			at->next[index] = new DictionaryNode;
		at = at->next[index];
	}
	at->isLeaf = true;
	return true;
}
DictionaryNode * Dictionary::find(string & word) {
	if (!onlyEnglishLetters(word))
		nullptr;
	auto at = root;
	for (char& c : word) {
		int index = charIndex(c);
		if (at->next[index] == nullptr)
			return nullptr;
		at = at->next[index];
	}
	return at;
}
bool Dictionary::isWord(string & word) {
	//empty strings are not considered words
	auto at = find(word);
	if (at == nullptr)
		return false;
	if (!at->isLeaf)
		return false;
	return true;
}
bool Dictionary::isPrefix(string & word) {
	//empty strings are considered prefixes
	auto at = find(word);
	if (at == nullptr)
		return false;
	return true;
}
void DFS(int curRow, int curCol, string & curWord, vector<vector<bool> > & visited, vector<vector<char> >& charGrid, Dictionary& dictionary_, set<string> & words) {
	int dRow[] = { -1,-1,-1,0,0,1,1,1 }; //change in row for 8 directions
	int dCol[] = { -1,0,1,-1,1,-1,0,1 }; //change in col for 8 directions
	curWord += charGrid[curRow][curCol];
	visited[curRow][curCol] = true;
	if (dictionary_.isPrefix(curWord)) {
		for (int k = 0; k < sizeof(dRow); k++) {
			int newRow = curRow + dRow[k];
			int newCol = curCol + dCol[k];
			if (newRow < 0 || newRow >= charGrid.size() || newCol < 0 || newCol >= charGrid[newRow].size())
				continue;
			if (!visited[newRow][newCol])
				DFS(newRow, newCol, curWord, visited, charGrid, dictionary_, words);
		}
		if (dictionary_.isWord(curWord))
			words.insert(curWord);
	}
	visited[curRow][curCol] = false;
	curWord.pop_back();
}
void findWords(Dictionary& dictionary_, vector<vector<char> >& charGrid, set<string> & words) {
	//fill the words in the set
	words.clear();
	if (!charGrid.size())
		return;
	vector<vector<bool> > visited;
	visited.resize(charGrid.size());
	for (int i = 0; i<charGrid.size(); i++)
		visited[i].resize(charGrid[i].size(), false);
	string curWord = "";
	for (int i = 0; i < charGrid.size(); i++)
		for (int j = 0; j < charGrid[i].size(); j++)
			DFS(i, j, curWord, visited, charGrid, dictionary_, words); //start the word from each cell
}
//////////////////////////////////////////////////
//testing begins here
void testFindWords_fillDictionary(Dictionary & dictionary_) {
	string s[4] = { "CAT","CAR", "CART", "CARD" };
	for (int i = 0; i<4; i++)
		dictionary_.insert(s[i]);
}
void testFindWords_fillCharGrid(int rows, int coloms, string letters, vector<vector<char> >& charGrid) {
	charGrid.resize(rows, vector<char>(coloms));
	for (int i = 0, k = 0; i<rows; i++)
		for (int j = 0; j<coloms; j++, k++)
			charGrid[i][j] = letters[k];
}
void testFindWords_emptyDictionary(Dictionary & dictionary_, vector<vector<char> > & charGrid, set<string> & words) {
	dictionary_.clear();
	findWords(dictionary_, charGrid, words);
	EXPECT_EQ(0, words.size());
}
void testFindWords_emptyCharGrid(Dictionary & dictionary_, vector<vector<char> > & charGrid, set<string> & words) {
	charGrid.clear();
	findWords(dictionary_, charGrid, words);
	EXPECT_EQ(0, words.size());
}
void testFindWords_dictionaryWithDuplicates(Dictionary & dictionary_, vector<vector<char> > & charGrid, set<string> & words) {
	;
	findWords(dictionary_, charGrid, words);
	vector<string>  actual_vec, expected_vec;
	set<string> ::iterator it;
	for (it = words.begin(); it != words.end(); it++)
		expected_vec.push_back(*it);
	string s[2] = { "CAT","CARD" };
	for (int i = 0; i<2; i++)
		dictionary_.insert(s[i]);//add duplicates
	findWords(dictionary_, charGrid, words);
	for (it = words.begin(); it != words.end(); it++)
		actual_vec.push_back(*it);
	//EXPECT_EQ(expected_vec, actual_vec); //not working did not find out why
	if (!(expected_vec==actual_vec))
		cout << "error with dictionary with duplicates case" << endl;
}
void testFindWords_normalCase(Dictionary & dictionary_, vector<vector<char> > & charGrid, set<string> & words) {
	findWords(dictionary_, charGrid, words);
	vector<string>  actual_vec;
	set<string> ::iterator it;
	for (it = words.begin(); it != words.end(); it++)
		actual_vec.push_back(*it);
	vector<string> expected_vec{ "CAR","CARD","CAT" };
	if (!(expected_vec== actual_vec))
		cout << "error with the normal case" << endl;
}
void testFindWords_noMatchWithDictionary(Dictionary & dictionary_, vector<vector<char> > & charGrid, set<string> & words) {
	charGrid.clear();
	testFindWords_fillCharGrid(2, 3, "WWQUFS", charGrid);
	findWords(dictionary_, charGrid, words);
	EXPECT_EQ(0, words.size());
}
void testFindWords_gridOneCell(Dictionary & dictionary_, vector<vector<char> > & charGrid, set<string> & words) {
	charGrid.clear();
	testFindWords_fillCharGrid(1, 1, "C", charGrid);
	findWords(dictionary_, charGrid, words);
	EXPECT_EQ(0, words.size());
}
int main() {
	Dictionary dictionary_;
	vector<vector<char> >charGrid;
	set<string> words;
	set<string> ::iterator it;
	testFindWords_emptyDictionary(dictionary_, charGrid, words);
	testFindWords_fillDictionary(dictionary_);
	testFindWords_emptyCharGrid(dictionary_, charGrid, words);
	testFindWords_fillCharGrid(2, 3, "AARTCD", charGrid);
	testFindWords_dictionaryWithDuplicates(dictionary_, charGrid, words);
	testFindWords_normalCase(dictionary_, charGrid, words);
	testFindWords_noMatchWithDictionary(dictionary_, charGrid, words);
	testFindWords_gridOneCell(dictionary_, charGrid, words);
	return 0;
}
