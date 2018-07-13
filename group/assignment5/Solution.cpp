#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include"Testing.h"
using namespace std;

class AlphabetFinder
{
	vector<string> words;
	vector<char> alphabet;
	bool foundAlphabet = false;

	unordered_set<char> allChars;

	//map value: set of chars that are lexicographically AFTER the key char
	unordered_map<char, unordered_set<char>> charsMap;

	//for the topological sorting
	stack<char> alphabetStack;
	map<char, bool> visited;

	void findAllChars()
	{
		for (string word : words)
		{
			for (char c : word)
			{
				allChars.emplace(c);
			}
		}
	}

	void fillMap()
	{
		//check every pair of adjacent words,
		//go through them simultaneously char by char till reaching the end of any of the 2 words,
		//find only the first mismatching chars (if there is any), 
		//add to the charsMap.
		int firstLoopIterations = words.size() - 1;
		for (int i = 0; i < firstLoopIterations; i++)
		{
			string word1 = words[i];
			string word2 = words[i + 1];
			int secondLoopIterations = min(word1.length(), word2.length());
			for (int j = 0; j < secondLoopIterations; j++)
			{
				if (word1[j] != word2[j])
				{
					charsMap[word1[j]].emplace(word2[j]);
					break;
				}
			}
		}
	}

	void visit(char c)
	{
		visited[c] = true;

		//iterating over all chars that should come AFTER c
		unordered_set<char>::iterator it;
		for (it = charsMap[c].begin(); it!=charsMap[c].end(); it++)
		{
			if (!visited[*it])
			{
				visit(*it);
			}
		}

		alphabetStack.push(c);
	}

public:
	AlphabetFinder(vector<string> w) :words(w) {
		findAllChars();
		fillMap();
	}

	vector<char> getAlphabet()
	{
		if (foundAlphabet) {
			return alphabet;
		}

		//filling the visited map
		unordered_set<char>::iterator it;
		for (it = allChars.begin(); it != allChars.end(); it++)
		{
			visited[*it] = false;
		}

		//iterating over all chars
		for (it = allChars.begin(); it!=allChars.end(); it++)
		{
			if (!visited[*it])
			{
				visit(*it);
			}
		}

		foundAlphabet = true;

		//filling the alphabet vector
		while (!alphabetStack.empty())
		{
			alphabet.push_back(alphabetStack.top());
			alphabetStack.pop();
		}

		return alphabet;
	}
};

void givenTest()
{
	AlphabetFinder AF({ "ART", "RAT", "CAT", "CAR" });
	vector<char> expected = { 'T', 'A', 'R', 'C' };
	vector<char> actual = AF.getAlphabet();
	EXPECT_EQ(expected, actual);
}

void oneLetterTest()
{
	AlphabetFinder AF({ "!", "!!!", "!!!!" });
	vector<char> expected = { '!' };
	vector<char> actual = AF.getAlphabet();
	EXPECT_EQ(expected, actual);
}

void simpleTest()
{
	AlphabetFinder AF({ "fg", "ab", "ca", "bc", "gf" });
	vector<char> expected = { 'f', 'a', 'c', 'b', 'g' };
	vector<char> actual = AF.getAlphabet();
	EXPECT_EQ(expected, actual);
}

void minCapTest()
{
	AlphabetFinder AF({ "Ar", "rA", "cA", "car" });
	vector<char> expected = { 'A', 'r', 'c', 'a' };
	vector<char> actual = AF.getAlphabet();
	EXPECT_EQ(expected, actual);
}

void symbolsTest()
{
	AlphabetFinder AF({ "*&^", "*&%", "%%%", "&**", "&*@" });
	vector<char> expected = { '^', '*', '@', '%', '&'};
	vector<char> actual = AF.getAlphabet();
	EXPECT_EQ(expected, actual);
}

void runAllTests()
{
	givenTest();
	oneLetterTest();
	simpleTest();
	minCapTest();
	symbolsTest();
}

int main()
{
	runAllTests();
  
	return 0;
}
