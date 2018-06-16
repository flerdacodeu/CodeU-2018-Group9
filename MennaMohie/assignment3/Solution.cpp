#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include<set>
#include"Testing.h" //test macros + overloaded insertion operator for sets
using namespace std;

enum checkType { wordCheck, prefixCheck };

const int gridCols = 3;

class Trie;

class TrieNode
{
	char character;
	bool terminates = false;
	unordered_map<char, TrieNode*> children;

	void addWord(string word)
	{
		int wordSize = word.length();

		if (wordSize == 0)
			return;

		char firstChar = word[0];
		TrieNode *child = children[firstChar];
		if (child == nullptr)
		{
			child = new TrieNode(firstChar);
			children[firstChar] = child;
		}
		if(wordSize>1)
			child->addWord(word.substr(1, wordSize - 1));
		else
			child->terminates = true;
	}

	bool hasChild(char c)
	{
		return children.find(c) != children.end();
	}

public:
	TrieNode() {}
	TrieNode(char c) :character(c){}
	
	friend class Trie;	
};

class Trie
{
	TrieNode *root;

public:

	Trie(vector<string> words)
	{
		root = new TrieNode();
		for (string word : words)
		{
			root->addWord(word);
		}
	}

	bool isWord(string word, checkType type = wordCheck)
	{
		if (word.length() == 0)
			return false;

		TrieNode *node = root;

		for (char c : word)
		{
			if (!node->hasChild(c))
				return false;
			node = node->children[c];

			//if we're doing a wordCheck and we've reached the last letter in the word we need to check its terminates boolean
			if (type == wordCheck && c == word[word.length() - 1] && node->terminates == false)
				return false;
		}

		return true;
	}

	bool isPrefix(string prefix)
	{
		return isWord(prefix, prefixCheck);
	}
};

bool formWords(string word, Trie dictionary, char grid[][gridCols], int rows, int currentRow, int currentCol, vector<string> &words)
{
	if (!dictionary.isPrefix(word))
		return false;

	string updatedWord;
	int updatedRow, updatedCol;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			updatedRow = currentRow + x;
			updatedCol = currentCol + y;
			if ((y != 0 || x != 0) && updatedRow>=0 && updatedRow<rows && updatedCol>=0 && updatedCol<gridCols)
			{
				updatedWord = word + grid[currentRow + x][currentCol + y];
				if (dictionary.isWord(updatedWord))
				{
					words.push_back(updatedWord);
				}
				formWords(updatedWord, dictionary, grid, rows, updatedRow, updatedCol, words);
			}
		}
	}
	return words.size() != 0;
}

set<string> formedWords(Trie dictionary, char grid[][3], int rows)
{
	set<string> allFormedWords;
	vector<string> words;
	string word;

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < gridCols; c++)
		{
			words.clear();
			word = grid[r][c];
			if (formWords(word, dictionary, grid, rows, r, c, words))
			{
				for (string word : words)
				{
					allFormedWords.emplace(word);
				}
			}
			
		}
	}
	return allFormedWords;
}

int main()
{
	vector<string> v = { "CAR", "CARD", "CART", "CAT" };
	Trie dict(v);

	EXPECT_TRUE(dict.isPrefix("C"));
	EXPECT_TRUE(dict.isPrefix("CAT"));
	EXPECT_FALSE(dict.isPrefix(""));

	EXPECT_TRUE(dict.isWord("CART"));
	EXPECT_FALSE(dict.isWord("CA"));
	EXPECT_FALSE(dict.isWord(""));

	char arr[2][gridCols] = { 'A','A','R','T','C','D' };

	set<string> expected = { "CAT", "CARD", "CAR" };
	set<string> actual = formedWords(dict, arr, 2);
	EXPECT_EQ(expected, actual);
	

	return 0;
}
