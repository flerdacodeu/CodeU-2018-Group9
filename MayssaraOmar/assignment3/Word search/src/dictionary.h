#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <unordered_map>
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

class dictionary {
	struct node {
		unordered_map<char, unique_ptr<node> > children;
		bool isEndWord;
		node() {
			isEndWord = false;
		}
	};
	unique_ptr<node> root;
public:
	dictionary();
	void insert(const string &word); // insert a word in the dictionary
	void insert(const vector<string> &words); // insert a vector of words in the dictionary
	void remove(const string &word); // remove a word from the dictionary
	void remove(const vector<string> &words); // remove a vector of words from the dictionary
	bool isPrefix(const string &prefix) const; // returns true if prefix is a prefix of any word in the dictionary or if prefix is a completed word
	bool isWord(const string &word) const; // returns true if word is a completed word that exits in the dictionary
	void clear(); // clears dictionary from all words
	bool empty(); // returns true if dictionary is empty, false otherwise
private:
	bool remove(unique_ptr<node> &current_node, const string &word, int index); // recursive helper function to remove a word, returns true if word is found and removed, false otherwise
};

#endif /* DICTIONARY_H_ */
