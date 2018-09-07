#include "dictionary.h"

dictionary::dictionary() {
	root = unique_ptr<node>(new node);
}

void dictionary::insert(const string &word) {
	node* ptr = root.get();
	for (char c : word) {
		if (!ptr->children[c]) {
			ptr->children[c] = unique_ptr<node>(new node);
		}
		ptr = ptr->children[c].get();
	}
	ptr->isEndWord = true;
}

void dictionary::insert(const vector<string> &words) {
	for (string word : words) {
		insert(word);
	}
}

void dictionary::remove(const string &word) {
	remove(root, word, 0);
}

void dictionary::remove(const vector<string> &words) {
	for (string word : words) {
		remove(word);
	}
}

bool dictionary::remove(unique_ptr<node> &current_node, const string &word,
		int index) {
	if (!current_node) {
		return false;
	}
	if (index == word.length() && current_node->isEndWord) {
		current_node->isEndWord = false;
		return true;
	}
	if (index >= word.length()
			|| !remove(current_node->children[word[index]], word, index + 1)) {
		return false;
	}
	if (current_node->children[word[index]]->children.empty()) {
		current_node->children.erase(word[index]);
	}
	return true;
}

bool dictionary::isWord(const string &word) const {
	node* ptr = root.get();
	for (char c : word) {
		if (!ptr->children[c]) {
			return false;
		}
		ptr = ptr->children[c].get();
	}
	return ptr->isEndWord;
}

bool dictionary::isPrefix(const string &word) const {
	node* ptr = root.get();
	for (char c : word) {
		if (!ptr->children[c]) {
			return false;
		}
		ptr = ptr->children[c].get();
	}
	return true;
}

void dictionary::clear() {
	root.reset(new node);
}

bool dictionary::empty() {
	return root->children.empty();
}
