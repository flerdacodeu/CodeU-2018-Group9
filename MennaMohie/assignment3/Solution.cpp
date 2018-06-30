#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include<set>
#include"Testing.h" //test macros + overloaded insertion operator for sets
using namespace std;

enum checkType { wordCheck, prefixCheck };

class Trie;

class TrieNode
{
	bool terminates = false;
	unordered_map<char, TrieNode*> children;

	//passing the original word and the current index instead of making a different string for each call
	void addWord(const string &word, int currentIndex=0)
	{
		int wordSize = word.length()-currentIndex;

		if (wordSize == 0)
			return;

		char firstChar = word[currentIndex];
		TrieNode *child = children[firstChar];
		if (child == nullptr)
		{
			child = new TrieNode();
			children[firstChar] = child;
		}
		if(wordSize>1)
			child->addWord(word,++currentIndex);
		else
			child->terminates = true;
	}

	bool hasChild(char c)
	{
		return children.find(c) != children.end();
	}

public:

	friend class Trie;	
};

class Trie
{
	TrieNode *root;

	bool check(string word, checkType type)
	{
		if (word.empty())
			return false;

		TrieNode *node = root;

		for (char c : word)
		{
			if (!node->hasChild(c))
				return false;
			node = node->children[c];
		}

		//if we're doing a wordCheck we need to check the terminates boolean of the last character
		if (type == wordCheck && node->terminates == false)
			return false;

		return true;
	}

public:

	Trie(const vector<string> &words)
	{
		root = new TrieNode();
		for (string word : words)
		{
			root->addWord(word);
		}
	}

	bool isWord(string word)
	{
		return check(word, wordCheck);
	}

	bool isPrefix(string prefix)
	{
		return check(prefix, prefixCheck);
	}
};

class Finder
{
	Trie dictionary;
	vector<vector<char>> grid;
	int rows;
	int cols;
	vector<vector<bool>> visited;

	bool formWords(string &word, int currentRow, int currentCol, set<string> &words)
	{
		if (!dictionary.isPrefix(word))
			return false;

		visited[currentRow][currentCol] = true;

		string updatedWord;
		int updatedRow, updatedCol;
		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				updatedRow = currentRow + x;
				updatedCol = currentCol + y;
				if (updatedRow >= 0 && updatedRow < rows && updatedCol >= 0 && updatedCol < cols && !visited[updatedRow][updatedCol])
				{
					updatedWord = word + grid[updatedRow][updatedCol];
					if (dictionary.isWord(updatedWord))
					{
						words.emplace(updatedWord);
					}
					formWords(updatedWord, updatedRow, updatedCol, words);
				}
			}
		}
		return words.size() != 0;
	}

public:

	Finder(const Trie &d, const vector<vector<char>> &g) :dictionary(d), grid(g)
	{
		rows = g.size();
		cols = g[0].size();
	}

	set<string> formedWords()
	{
		set<string> words;
		string word;

		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				visited.clear();
				visited.resize(rows,vector<bool>(cols,false));
				
				word = grid[r][c];
				formWords(word, r, c, words);
			}
		}
		return words;
	}
};

int main()
{
	Trie dict1({ "CAR", "CARD", "CART", "CAT" });

	EXPECT_TRUE(dict1.isPrefix("C"));
	EXPECT_TRUE(dict1.isPrefix("CA"));
	EXPECT_TRUE(dict1.isPrefix("CAT"));
	EXPECT_TRUE(dict1.isPrefix("CAR"));
	EXPECT_FALSE(dict1.isPrefix("ca"));
	EXPECT_FALSE(dict1.isPrefix("RA"));
	EXPECT_FALSE(dict1.isPrefix("CR"));
	EXPECT_FALSE(dict1.isPrefix("D"));
	EXPECT_FALSE(dict1.isPrefix("TA"));

	EXPECT_TRUE(dict1.isWord("CART"));
	EXPECT_TRUE(dict1.isWord("CARD"));
	EXPECT_TRUE(dict1.isWord("CAT"));
	EXPECT_FALSE(dict1.isWord("cat"));
	EXPECT_FALSE(dict1.isWord("CA"));
	EXPECT_FALSE(dict1.isWord("TA"));
	EXPECT_FALSE(dict1.isWord(""));

	vector<vector<char>> grid1;
	grid1.push_back({ 'A', 'A', 'R' });
	grid1.push_back({ 'T', 'C', 'D' });

	Finder finder1(dict1, grid1);

	set<string> actual1 = finder1.formedWords();
	set<string> expected1 = { "CAT", "CARD", "CAR" };
	EXPECT_EQ(expected1, actual1);

	Trie dict2({ "banana","mango","grapes","apple" });

	EXPECT_TRUE(dict2.isPrefix("ban"));
	EXPECT_TRUE(dict2.isPrefix("mang"));
	EXPECT_TRUE(dict2.isPrefix("a"));
	EXPECT_TRUE(dict2.isPrefix("grapes"));
	EXPECT_FALSE(dict2.isPrefix("Gra"));
	EXPECT_FALSE(dict2.isPrefix("C"));

	EXPECT_TRUE(dict2.isWord("banana"));
	EXPECT_TRUE(dict2.isWord("mango"));
	EXPECT_FALSE(dict2.isWord("grape"));
	EXPECT_FALSE(dict2.isWord("Apple"));

	vector<vector<char>> grid2;
	grid2.push_back({ 'p','a','h','f' });
	grid2.push_back({ 'p','n','a','e' });
	grid2.push_back({ 'l','g','o','n' });
	grid2.push_back({ 'e','n','a','d' });
	grid2.push_back({ 'm','a','c','b' });

	Finder finder2(dict2, grid2);

	set<string> actual2 = finder2.formedWords();
	set<string> expected2 = { "banana", "apple", "mango" };
	EXPECT_EQ(expected2, actual2);

	return 0;
}
