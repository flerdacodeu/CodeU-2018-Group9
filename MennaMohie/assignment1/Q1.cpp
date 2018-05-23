#include<bits/stdc++.h>
#include<stdlib.h>

using namespace std;

bool anagramWordCheck(string,string,bool);
bool anagramSentenceCheck(string,string,bool);

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

        bool caseSensitive;
        sensitivity=tolower(sensitivity);
        if(sensitivity=='i')
            caseSensitive=false;
        else if (sensitivity=='s')
            caseSensitive=true;

        bool areAnagrams = anagramWordCheck(word1, word2, caseSensitive);
        cout<<(areAnagrams?"The two words are anagrams.":"The two words are not anagrams.");
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

        bool caseSensitive;
        sensitivity=tolower(sensitivity);
        if(sensitivity=='i')
            caseSensitive=false;
        else if (sensitivity=='s')
            caseSensitive=true;

        bool areAnagrams = anagramSentenceCheck(sentence1, sentence2, caseSensitive);
        cout<<(areAnagrams?"The two sentences are anagrams.":"The two sentences are not anagrams.");
    }

    return 0;
}


bool anagramWordCheck(string word1, string word2, bool caseSensitive)
{
    if(word1.length()!=word2.length())
        return false;

    //map: key is a character and value is the frequency of the character
    map<char,int> word1_map, word2_map;
    int i, j;
    int length = word1.size();
    for(i=0; i<length; i++)
    {
        if(!caseSensitive)
        {
            word1[i]=tolower(word1[i]);
            word2[i]=tolower(word2[i]);
        }

        word1_map[word1[i]]++;
        word2_map[word2[i]]++;
    }

    bool sameFrequency=true;
    for(i=0; i<length; i++)
    {
        if(word1_map[word1[i]] != word2_map[word1[i]])
        {
            sameFrequency=false;
            break;
        }
    }

    return(word1!=word2 && sameFrequency);
}

//space separated words
bool anagramSentenceCheck(string sentence1, string sentence2, bool caseSensitive)
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

    int number_of_words=sentence1_words.size(), anagramCount=0;
    for(const string &Word : sentence2_words)
    {
        for(int j=0; j<number_of_words; j++)
        {
            if(sentence1_words[j].second==true)
                continue;
            if(anagramWordCheck(sentence1_words[j].first,Word,caseSensitive))
            {
                anagramCount++;
                sentence1_words[j].second=true;
                break;
            }
        }
    }
    return(anagramCount==number_of_words);
}
