#include <iostream>
#include <stdio.h>  
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <stdlib.h>
#include"codeu_test_lib.h"
using namespace std;
bool findDistinctChars(string word1, string word2, char * charFromFirstWord, char * charFromSecondWord) {
	int minLength = min(word1.size(), word2.size());
	int i;
	for (i = 0; i < minLength ; i++)
		if (word1[i] != word2[i])
			break;
	if (i == minLength)
		return false;
	*charFromFirstWord = word1[i];
	*charFromSecondWord = word2[i];
	return true;
}
void findIDSequence(map <int, int> & indegree, map<int, vector<int> > &children, vector<int> * alphabetIDSequence) {
	set<pair<int, int> > sortedIndegrees;
	map <int, int> ::iterator it;
	for (it = indegree.begin(); it != indegree.end(); it++)
		sortedIndegrees.insert(make_pair(it->second,it->first));
	while (sortedIndegrees.size()) {
		set<pair<int, int> > ::iterator cur = sortedIndegrees.begin();
		int curID = cur->second;
		sortedIndegrees.erase(cur);
		(*alphabetIDSequence).push_back(curID);
		for (int i = 0; i < children[curID].size(); i++) {
			pair<int, int> oldPair = make_pair(indegree[children[curID][i]], children[curID][i]);
			sortedIndegrees.erase(oldPair);
			sortedIndegrees.insert(make_pair(--indegree[children[curID][i]], children[curID][i]));
		}
	}

}
void findCharSequence(map <int, char> & charIDInverse, vector<int> & alphabetIDSequence, vector<char> * Alphabet) {
	for (int i = 0; i < alphabetIDSequence.size(); i++) {
		char cur = charIDInverse[alphabetIDSequence[i]];
		(*Alphabet).push_back(cur);
	}
}
int getCharID(char curChar, map <char, int> * charID, map <int, char> * charIDInverse) {
	int static ID = 1;
	if (!(*charID)[curChar]) {
		(*charID)[curChar] = ID;
		(*charIDInverse)[ID] = curChar;
		ID++;
	}
	return (*charID)[curChar];
}
vector<char> FindAlphabet( const vector<string> & words) {
	map <int, int> indegree; //indegree for each char in a topological sort graph
	map <char, int> charID; // assign a unique ID for each char
	map <int, char> charIDInverse;
	map<int, vector<int> >children; //this is my graph
	for (int i = 0; i < words.size()-1; i++) { //compare each word with the next one
		char charFromFirstWord, charFromSecondWord;
		bool found= findDistinctChars(words[i],words[i+1], &charFromFirstWord, &charFromSecondWord); 
		if (!found)
			continue;
		int firstCharID = getCharID(charFromFirstWord, &charID, &charIDInverse);
		int secondCharID = getCharID(charFromSecondWord, &charID, &charIDInverse);
		children[firstCharID].push_back(secondCharID);
		indegree[firstCharID]= indegree[firstCharID]; // do not change if exists or assign 0 
		indegree[secondCharID]++;
	}
	
	vector<int> alphabetIDSequence;
	vector<char> Alphabet;
	findIDSequence(indegree, children, &alphabetIDSequence);
	findCharSequence(charIDInverse,alphabetIDSequence,&Alphabet);
	return Alphabet;
}

void testFindAlphabet_givenCase() {
	vector<char> answer = FindAlphabet({ "ART","RAT","CAT","CAR" });
	bool flag = false;
	vector<char> expected = { 'A','T','R','C' };
	if (answer == expected)
		flag = true;
	EXPECT_EQ(flag,true);
}

int main() {
	testFindAlphabet_givenCase();
	return 0;
}
