#include<bits/stdc++.h>
#include<stdlib.h>
#define endl '\n'

using namespace std;

bool anagramWordCheck(string,string,char);
bool anagramSentenceCheck(string,string,char);

int main()
{
    char choice, sensitivity;
    cout<<"Please type 'w' if you'd like to enter 2 words or 's' if you'd like to enter 2 sentences: ";
    cin>>choice;
    if(choice=='w' || choice=='W')
    {
        string word1, word2;
        cout<<"Please enter the first word: ";
        cin>>word1;
        cout<<"Please enter the second word: ";
        cin>>word2;

        cout<<"Please type 's' for Case Sensitive Anagram Checking or 'i' for Case Insensitive Anagram Checking: ";
        cin>>sensitivity;

        cout<<(anagramWordCheck(word1, word2, tolower(sensitivity))?"The two words are anagrams.":"The two words are not anagrams.");
    }

    else if(choice=='s' || choice=='S')
    {
        string sentence1, sentence2;
        cout<<"Please enter the first sentence:\n";
        cin.ignore();
        getline(cin,sentence1);
        cout<<"Please enter the second sentence:\n";
        getline(cin,sentence2);

        cout<<"Please type 's' for Case Sensitive Anagram Checking or 'i' for Case Insensitive Anagram Checking: ";
        cin>>sensitivity;

        cout<<(anagramSentenceCheck(sentence1, sentence2, tolower(sensitivity))?"The two sentences are anagrams.":"The two sentences are not anagrams.");
    }

    return 0;
}


bool anagramWordCheck(string word1, string word2, char sensitivity)
{
    if(word1.length()!=word2.length())
        return false;

    //map: key is a character and value is the list of positions of the character
    map<char,vector<int>> word1_map, word2_map;
    int i, j;
    int length = word1.size();
    for(i=0; i<length; i++)
    {
        if(sensitivity=='i')
        {
            word1[i]=tolower(word1[i]);
            word2[i]=tolower(word2[i]);
        }
        word1_map[word1[i]].push_back(i);
        word2_map[word2[i]].push_back(i);
    }

    bool differentOrder=false;
    bool sameFrequency=true;

    for(i=0; i<length; i++)
    {
        if(word1_map[word1[i]].size() != word2_map[word1[i]].size())
        {
            sameFrequency=false;
            break;
        }

        if (differentOrder==false)
        {
            for(int j=0; j<word1_map[word1[i]].size(); j++)
            {
                if(word1_map[word1[i]][j]!=word2_map[word1[i]][j])
                {
                    differentOrder=true;
                }
            }
        }
    }

    return(differentOrder&&sameFrequency?true:false);
}

//space separated words
bool anagramSentenceCheck(string sentence1, string sentence2, char sensitivity)
{
    if(sentence1.size()!=sentence2.size())
        return false;

    vector<pair<string,bool>> sentence1_words;
    vector<string> sentence2_words;
    string word;
    stringstream ss1(sentence1);
    while(getline(ss1,word,' '))
    {
        sentence1_words.push_back(make_pair(word,false));
    }

    stringstream ss2(sentence2);
    while(getline(ss2,word,' '))
    {
        sentence2_words.push_back(word);
    }

    if(sentence1_words.size()!=sentence2_words.size())
        return false;

    int i, j, number_of_words=sentence1_words.size(), anagramCount=0;
    for(i=0; i<number_of_words; i++)
    {
        for(j=0; j<number_of_words; j++)
        {
            if(sentence1_words[j].second==true)
                continue;
            if(anagramWordCheck(sentence1_words[j].first,sentence2_words[i],sensitivity))
            {
                anagramCount++;
                sentence1_words[j].second=true;
                break;
            }
        }
    }
    return(anagramCount==number_of_words?true:false);
}
