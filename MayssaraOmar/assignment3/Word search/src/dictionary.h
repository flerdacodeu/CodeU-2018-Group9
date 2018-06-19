#include <unordered_map>
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;


#ifndef DICTIONARY_H_
#define DICTIONARY_H_

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
	//~dictionary(); no need for a destructor as we use smart pointers right?
	void insert(const string &word);
	void insert(const vector<string> &words);
	void remove(const string &word);
	void remove(const vector<string> &words);
	bool isPrefix(const string &prefix);
	bool isWord(const string &word);
	void clear();
	bool empty();
private:
	bool remove(unique_ptr<node> &current_node, const string &word, int index);
};



#endif /* DICTIONARY_H_ */
